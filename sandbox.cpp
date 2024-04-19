#include "SDL3/SDL.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include <stdio.h>
#include <memory>
#include <exception>
#include <utility>
template <typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

struct WindowDestroyer { void operator()(SDL_Window *window) { if (window) SDL_DestroyWindow(window); } };

struct ContextHolder
{
	ContextHolder() { if (SDL_Init(SDL_INIT_VIDEO) < 0) std::terminate(); }
	~ContextHolder() { SDL_Quit(); }
};

struct Context
{
	ContextHolder ctx_holder;
	std::unique_ptr<SDL_Window, WindowDestroyer> window;
	ComPtr<IDXGIFactory2> factory;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<ID3D12Device4> device;
	ComPtr<ID3D12CommandQueue> queue;
	ComPtr<ID3D12GraphicsCommandList> list;
	ComPtr<IDXGISwapChain3> swapchain;

	ComPtr<ID3D12DescriptorHeap> rtv_heap;
	ComPtr<ID3D12Fence> fence;
	uint64_t timeline = 0;

	struct
	{
		ComPtr<ID3D12Resource> backbuffer;
		D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle = {};
		ComPtr<ID3D12CommandAllocator> allocator;
		uint64_t wait_value = 0;
	} frames[2];

	bool init();
};

bool Context::init()
{
	HRESULT hr;

	window.reset(SDL_CreateWindow("D3D12 sandbox", 1280, 720, 0));
	if (!window)
	{
		fprintf(stderr, "Failed to create window.\n");
		return false;
	}

	{
		ComPtr<ID3D12Debug1> debug;
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug))))
			debug->EnableDebugLayer();
	}

	if (FAILED(hr = CreateDXGIFactory1(IID_PPV_ARGS(&factory))))
	{
		fprintf(stderr, "Failed to create DXGI factory, hr #%x.\n", unsigned(hr));
		return false;
	}

	if (FAILED(factory->EnumAdapters(0, &adapter)))
	{
		fprintf(stderr, "Failed to enumerate adapter.\n");
		return false;
	}

	if (FAILED(hr = D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device))))
	{
		fprintf(stderr, "Failed to create D3D12Device, hr #%x.\n", unsigned(hr));
		return false;
	}

	D3D12_COMMAND_QUEUE_DESC queue_desc = {};
	queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	if (FAILED(hr = device->CreateCommandQueue(&queue_desc, IID_PPV_ARGS(&queue))))
	{
		fprintf(stderr, "Failed to create command queue, hr #%x.\n", unsigned(hr));
		return false;
	}

	if (FAILED(hr = device->CreateCommandList1(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&list))))
	{
		fprintf(stderr, "Failed to create command list, hr #%x.\n", unsigned(hr));
		return false;
	}

	if (FAILED(hr = device->CreateFence(0, D3D12_FENCE_FLAG_SHARED, IID_PPV_ARGS(&fence))))
	{
		fprintf(stderr, "Failed to create shared fence, hr #%x.\n", unsigned(hr));
		return false;
	}

	DXGI_SWAP_CHAIN_DESC1 desc = {};
	desc.Width = 1280;
	desc.Height = 720;
	desc.BufferCount = 2;
	desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	desc.SampleDesc.Count = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	auto props = SDL_GetWindowProperties(window.get());
	SDL_LockProperties(props);
	auto hwnd = static_cast<HWND>(SDL_GetProperty(props, "SDL.window.win32.hwnd", nullptr));
	SDL_UnlockProperties(props);

	ComPtr<IDXGISwapChain1> swapchain1;
	if (FAILED(hr = factory->CreateSwapChainForHwnd(queue.Get(), hwnd, &desc, nullptr, nullptr, &swapchain1)))
	{
		fprintf(stderr, "Failed to create swapchain.\n");
		return false;
	}

	if (FAILED(swapchain1.As(&swapchain)))
	{
		fprintf(stderr, "Failed to query IDXGISwapChain2.\n");
		return false;
	}

	D3D12_DESCRIPTOR_HEAP_DESC heap_desc = {};
	heap_desc.NumDescriptors = 2;
	heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	if (FAILED(device->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(&rtv_heap))))
	{
		fprintf(stderr, "Failed to create descriptor heap.\n");
		return false;
	}

	for (unsigned i = 0; i < 2; i++)
	{
		if (FAILED(hr = swapchain->GetBuffer(i, IID_PPV_ARGS(&frames[i].backbuffer))))
		{
			fprintf(stderr, "Failed to get backbuffer.\n");
			return false;
		}

		frames[i].rtv_handle = rtv_heap->GetCPUDescriptorHandleForHeapStart();
		frames[i].rtv_handle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV) * i;
		device->CreateRenderTargetView(frames[i].backbuffer.Get(), nullptr, frames[i].rtv_handle);

		if (FAILED(hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&frames[i].allocator))))
		{
			fprintf(stderr, "Failed to create command allocator.\n");
			return false;
		}
	}

	return true;
}

struct Pipeline
{
	ComPtr<ID3D12PipelineState> pso;
	ComPtr<ID3D12CommandSignature> signature;
	ComPtr<ID3D12RootSignature> rootsig;
};

struct IndirectCommand
{
	float vert[3];
	float frag[3];
	D3D12_DRAW_INDEXED_ARGUMENTS draw;
};

static Pipeline create_pipeline(Context &ctx)
{
	Pipeline pipeline;
	D3D12_ROOT_SIGNATURE_DESC rs_desc = {};
	D3D12_ROOT_PARAMETER rs_param[2] = {};

	rs_param[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	rs_param[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	rs_param[0].Constants.Num32BitValues = 3;
	rs_param[0].Constants.ShaderRegister = 0;

	rs_param[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
	rs_param[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	rs_param[1].Constants.Num32BitValues = 3;
	rs_param[1].Constants.ShaderRegister = 1;

	rs_desc.NumParameters = 2;
	rs_desc.pParameters = rs_param;

	ComPtr<ID3D10Blob> blob, errblob;
	D3D12SerializeRootSignature(&rs_desc, D3D_ROOT_SIGNATURE_VERSION_1_0, &blob, &errblob);

	if (FAILED(ctx.device->CreateRootSignature(0, blob->GetBufferPointer(), blob->GetBufferSize(), IID_PPV_ARGS(&pipeline.rootsig))))
	{
		fprintf(stderr, "Failed to create root signature.\n");
		return {};
	}

#include "shaders/headers/vert.h"
#include "shaders/headers/frag.h"

	D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
	pso_desc.pRootSignature = pipeline.rootsig.Get();
	pso_desc.BlendState.RenderTarget[0].RenderTargetWriteMask = 0xf;
	pso_desc.NumRenderTargets = 1;
	pso_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	pso_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	pso_desc.VS = vert_dxil;
	pso_desc.PS = frag_dxil;
	pso_desc.SampleDesc.Count = 1;
	pso_desc.SampleMask = ~0u;
	pso_desc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	pso_desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;

	if (FAILED(ctx.device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(&pipeline.pso))))
	{
		fprintf(stderr, "Failed to create PSO.\n");
		return {};
	}

	D3D12_INDIRECT_ARGUMENT_DESC argument_desc[3] = {};
	argument_desc[0].Type = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT;
	argument_desc[0].Constant.Num32BitValuesToSet = 3;
	argument_desc[0].Constant.RootParameterIndex = 0;
	argument_desc[1].Type = D3D12_INDIRECT_ARGUMENT_TYPE_CONSTANT;
	argument_desc[1].Constant.Num32BitValuesToSet = 3;
	argument_desc[1].Constant.RootParameterIndex = 1;
	argument_desc[2].Type = D3D12_INDIRECT_ARGUMENT_TYPE_DRAW_INDEXED;
	D3D12_COMMAND_SIGNATURE_DESC sig_desc = {};
	sig_desc.pArgumentDescs = argument_desc;
	sig_desc.NumArgumentDescs = 3;
	sig_desc.ByteStride = sizeof(IndirectCommand);

	if (FAILED(ctx.device->CreateCommandSignature(&sig_desc, pipeline.rootsig.Get(), IID_PPV_ARGS(&pipeline.signature))))
	{
		fprintf(stderr, "Failed to create command signature.\n");
		return {};
	}

	return pipeline;
}

static ComPtr<ID3D12Resource> create_buffer(Context &ctx, const void *data, size_t size)
{
	D3D12_RESOURCE_DESC desc = {};
	desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	desc.Width = size;
	desc.Height = 1;
	desc.DepthOrArraySize = 1;
	desc.Format = DXGI_FORMAT_UNKNOWN;
	desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	desc.SampleDesc.Count = 1;
	desc.MipLevels = 1;

	ComPtr<ID3D12Resource> buffer, upload;
	D3D12_HEAP_PROPERTIES heap_props = {};
	heap_props.Type = D3D12_HEAP_TYPE_UPLOAD;
	
	if (FAILED(ctx.device->CreateCommittedResource(&heap_props, D3D12_HEAP_FLAG_CREATE_NOT_ZEROED, &desc,
		D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&upload))))
	{
		fprintf(stderr, "Failed to create buffer.\n");
		return {};
	}

	heap_props.Type = D3D12_HEAP_TYPE_DEFAULT;

	if (FAILED(ctx.device->CreateCommittedResource(&heap_props, D3D12_HEAP_FLAG_CREATE_NOT_ZEROED, &desc,
		D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&buffer))))
	{
		fprintf(stderr, "Failed to create buffer.\n");
		return {};
	}

	void *ptr;
	if (FAILED(upload->Map(0, nullptr, &ptr)))
	{
		fprintf(stderr, "Failed to map.\n");
		return {};
	}

	memcpy(ptr, data, size);
	upload->Unmap(0, nullptr);

	ctx.fence->SetEventOnCompletion(ctx.timeline, nullptr);
	auto &frame = ctx.frames[0];
	frame.allocator->Reset();
	ctx.list->Reset(frame.allocator.Get(), nullptr);
	ctx.list->CopyResource(buffer.Get(), upload.Get());
	ctx.list->Close();
	ID3D12CommandList *list = ctx.list.Get();
	ctx.queue->ExecuteCommandLists(1, &list);
	ctx.queue->Signal(ctx.fence.Get(), ++ctx.timeline);
	frame.wait_value = ctx.timeline;
	ctx.fence->SetEventOnCompletion(ctx.timeline, nullptr);

	return buffer;
}

static void render_test(Context &ctx)
{
	auto pipeline = create_pipeline(ctx);

	IndirectCommand cmd = {};
	cmd.vert[0] = -0.5f;
	cmd.vert[1] = -0.5f;
	cmd.vert[2] = 0.2f;
	cmd.frag[0] = 1.0f;
	cmd.frag[1] = 0.5f;
	cmd.frag[2] = 0.2f;
	cmd.draw.IndexCountPerInstance = 3;
	cmd.draw.InstanceCount = 2;
	auto argument = create_buffer(ctx, &cmd, sizeof(cmd));

	uint32_t count = 1;
	auto count_buffer = create_buffer(ctx, &count, sizeof(count));

	const uint32_t index_data[3] = { 0, 1, 2 };
	auto index_buffer = create_buffer(ctx, index_data, sizeof(index_data));

	bool alive = true;
	while (alive)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_EVENT_QUIT)
				alive = false;
		}

		unsigned backbuffer = ctx.swapchain->GetCurrentBackBufferIndex();
		auto &frame = ctx.frames[backbuffer];
		ctx.fence->SetEventOnCompletion(frame.wait_value, nullptr);

		frame.allocator->Reset();
		ctx.list->Reset(frame.allocator.Get(), nullptr);
		{
			D3D12_RESOURCE_BARRIER barrier = {};
			barrier.Transition.pResource = frame.backbuffer.Get();
			barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
			barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
			barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
			barrier.Transition.Subresource = -1u;

			ctx.list->ResourceBarrier(1, &barrier);

			const float blue[4] = { 0.1f, 0.2f, 0.3f, 1.0f };
			ctx.list->OMSetRenderTargets(1, &frame.rtv_handle, TRUE, nullptr);
			ctx.list->ClearRenderTargetView(frame.rtv_handle, blue, 0, nullptr);
			ctx.list->SetGraphicsRootSignature(pipeline.rootsig.Get());
			ctx.list->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			ctx.list->SetPipelineState(pipeline.pso.Get());

			D3D12_INDEX_BUFFER_VIEW ibv = {};
			ibv.BufferLocation = index_buffer->GetGPUVirtualAddress();
			ibv.Format = DXGI_FORMAT_R32_UINT;
			ibv.SizeInBytes = index_buffer->GetDesc().Width;
			ctx.list->IASetIndexBuffer(&ibv);

			D3D12_VIEWPORT vp = {};
			vp.Width = 1280;
			vp.Height = 720;
			vp.MinDepth = 0.0f;
			vp.MaxDepth = 1.0f;
			ctx.list->RSSetViewports(1, &vp);

			D3D12_RECT sci = {};
			sci.right = 1280;
			sci.bottom = 720;
			ctx.list->RSSetScissorRects(1, &sci);

			ctx.list->ExecuteIndirect(pipeline.signature.Get(), 1, argument.Get(), 0, nullptr, 0);

			std::swap(barrier.Transition.StateBefore, barrier.Transition.StateAfter);
			ctx.list->ResourceBarrier(1, &barrier);
		}

		ctx.list->Close();
		ID3D12CommandList *list = ctx.list.Get();
		ctx.queue->ExecuteCommandLists(1, &list);
		ctx.queue->Signal(ctx.fence.Get(), ++ctx.timeline);
		frame.wait_value = ctx.timeline;

		if (FAILED(ctx.swapchain->Present(1, 0)))
		{
			fprintf(stderr, "Failed to present.\n");
			break;
		}
	}

	ctx.queue->Signal(ctx.fence.Get(), ++ctx.timeline);
	ctx.fence->SetEventOnCompletion(ctx.timeline, nullptr);
}

int main()
{
	Context ctx;
	if (!ctx.init())
		return EXIT_FAILURE;

	render_test(ctx);
}