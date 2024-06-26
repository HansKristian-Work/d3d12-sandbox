/*** Autogenerated by WIDL 8.0 from ../include/vkd3d_swapchain_factory.idl - Do not edit ***/

#ifdef _WIN32
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif
#include <rpc.h>
#include <rpcndr.h>
#endif

#ifndef COM_NO_WINDOWS_H
#include <windows.h>
#include <ole2.h>
#endif

#ifndef __vkd3d_swapchain_factory_h__
#define __vkd3d_swapchain_factory_h__

#ifndef __WIDL_INLINE
#if defined(__cplusplus) || defined(_MSC_VER)
#define __WIDL_INLINE inline
#elif defined(__GNUC__)
#define __WIDL_INLINE __inline__
#endif
#endif

/* Forward declarations */

#ifndef __IDXGIVkSurfaceFactory_FWD_DEFINED__
#define __IDXGIVkSurfaceFactory_FWD_DEFINED__
typedef interface IDXGIVkSurfaceFactory IDXGIVkSurfaceFactory;
#ifdef __cplusplus
interface IDXGIVkSurfaceFactory;
#endif /* __cplusplus */
#endif

#ifndef __IDXGIVkSwapChain_FWD_DEFINED__
#define __IDXGIVkSwapChain_FWD_DEFINED__
typedef interface IDXGIVkSwapChain IDXGIVkSwapChain;
#ifdef __cplusplus
interface IDXGIVkSwapChain;
#endif /* __cplusplus */
#endif

#ifndef __IDXGIVkSwapChainFactory_FWD_DEFINED__
#define __IDXGIVkSwapChainFactory_FWD_DEFINED__
typedef interface IDXGIVkSwapChainFactory IDXGIVkSwapChainFactory;
#ifdef __cplusplus
interface IDXGIVkSwapChainFactory;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <vkd3d_windows.h>
#include <vkd3d_dxgibase.h>
#include <vkd3d_dxgi1_5.h>
#include <vkd3d_vk_includes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DXGI_VK_HDR_METADATA {
    DXGI_HDR_METADATA_TYPE Type;
    __C89_NAMELESS union {
        DXGI_HDR_METADATA_HDR10 HDR10;
    } __C89_NAMELESSUNIONNAME;
} DXGI_VK_HDR_METADATA;
/*****************************************************************************
 * IDXGIVkSurfaceFactory interface
 */
#ifndef __IDXGIVkSurfaceFactory_INTERFACE_DEFINED__
#define __IDXGIVkSurfaceFactory_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGIVkSurfaceFactory, 0x1e7895a1, 0x1bc3, 0x4f9c, 0xa6,0x70, 0x29,0x0a,0x4b,0xc9,0x58,0x1a);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("1e7895a1-1bc3-4f9c-a670-290a4bc9581a")
IDXGIVkSurfaceFactory : public IUnknown
{
    virtual VkResult STDMETHODCALLTYPE CreateSurface(
        VkInstance instance,
        VkPhysicalDevice adapter,
        VkSurfaceKHR *pSurface) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDXGIVkSurfaceFactory, 0x1e7895a1, 0x1bc3, 0x4f9c, 0xa6,0x70, 0x29,0x0a,0x4b,0xc9,0x58,0x1a)
#endif
#else
typedef struct IDXGIVkSurfaceFactoryVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDXGIVkSurfaceFactory *This,
        REFIID riid,
        void **object);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDXGIVkSurfaceFactory *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDXGIVkSurfaceFactory *This);

    /*** IDXGIVkSurfaceFactory methods ***/
    VkResult (STDMETHODCALLTYPE *CreateSurface)(
        IDXGIVkSurfaceFactory *This,
        VkInstance instance,
        VkPhysicalDevice adapter,
        VkSurfaceKHR *pSurface);

    END_INTERFACE
} IDXGIVkSurfaceFactoryVtbl;

interface IDXGIVkSurfaceFactory {
    CONST_VTBL IDXGIVkSurfaceFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDXGIVkSurfaceFactory_QueryInterface(This,riid,object) (This)->lpVtbl->QueryInterface(This,riid,object)
#define IDXGIVkSurfaceFactory_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDXGIVkSurfaceFactory_Release(This) (This)->lpVtbl->Release(This)
/*** IDXGIVkSurfaceFactory methods ***/
#define IDXGIVkSurfaceFactory_CreateSurface(This,instance,adapter,pSurface) (This)->lpVtbl->CreateSurface(This,instance,adapter,pSurface)
#else
/*** IUnknown methods ***/
static __WIDL_INLINE HRESULT IDXGIVkSurfaceFactory_QueryInterface(IDXGIVkSurfaceFactory* This,REFIID riid,void **object) {
    return This->lpVtbl->QueryInterface(This,riid,object);
}
static __WIDL_INLINE ULONG IDXGIVkSurfaceFactory_AddRef(IDXGIVkSurfaceFactory* This) {
    return This->lpVtbl->AddRef(This);
}
static __WIDL_INLINE ULONG IDXGIVkSurfaceFactory_Release(IDXGIVkSurfaceFactory* This) {
    return This->lpVtbl->Release(This);
}
/*** IDXGIVkSurfaceFactory methods ***/
static __WIDL_INLINE VkResult IDXGIVkSurfaceFactory_CreateSurface(IDXGIVkSurfaceFactory* This,VkInstance instance,VkPhysicalDevice adapter,VkSurfaceKHR *pSurface) {
    return This->lpVtbl->CreateSurface(This,instance,adapter,pSurface);
}
#endif
#endif

#endif


#endif  /* __IDXGIVkSurfaceFactory_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IDXGIVkSwapChain interface
 */
#ifndef __IDXGIVkSwapChain_INTERFACE_DEFINED__
#define __IDXGIVkSwapChain_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGIVkSwapChain, 0xe4a9059e, 0xb569, 0x46ab, 0x8d,0xe7, 0x50,0x1b,0xd2,0xbc,0x7f,0x7a);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("e4a9059e-b569-46ab-8de7-501bd2bc7f7a")
IDXGIVkSwapChain : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE GetDesc(
        DXGI_SWAP_CHAIN_DESC1 *pDesc) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetAdapter(
        REFIID riid,
        void **ppvObject) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetDevice(
        REFIID riid,
        void **ppDevice) = 0;

    virtual HRESULT STDMETHODCALLTYPE GetImage(
        UINT BufferId,
        REFIID riid,
        void **ppBuffer) = 0;

    virtual UINT STDMETHODCALLTYPE GetImageIndex(
        ) = 0;

    virtual UINT STDMETHODCALLTYPE GetFrameLatency(
        ) = 0;

    virtual HANDLE STDMETHODCALLTYPE GetFrameLatencyEvent(
        ) = 0;

    virtual HRESULT STDMETHODCALLTYPE ChangeProperties(
        const DXGI_SWAP_CHAIN_DESC1 *pDesc,
        const UINT *pNodeMasks,
        IUnknown *const *ppPresentQueues) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetPresentRegion(
        const RECT *pRegion) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetGammaControl(
        UINT NumControlPoints,
        const DXGI_RGB *pControlPoints) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetFrameLatency(
        UINT MaxLatency) = 0;

    virtual HRESULT STDMETHODCALLTYPE Present(
        UINT SyncInterval,
        UINT PresentFlags,
        const DXGI_PRESENT_PARAMETERS *pPresentParameters) = 0;

    virtual UINT STDMETHODCALLTYPE CheckColorSpaceSupport(
        DXGI_COLOR_SPACE_TYPE ColorSpace) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetColorSpace(
        DXGI_COLOR_SPACE_TYPE ColorSpace) = 0;

    virtual HRESULT STDMETHODCALLTYPE SetHDRMetaData(
        const DXGI_VK_HDR_METADATA *pMetaData) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDXGIVkSwapChain, 0xe4a9059e, 0xb569, 0x46ab, 0x8d,0xe7, 0x50,0x1b,0xd2,0xbc,0x7f,0x7a)
#endif
#else
typedef struct IDXGIVkSwapChainVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDXGIVkSwapChain *This,
        REFIID riid,
        void **object);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDXGIVkSwapChain *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDXGIVkSwapChain *This);

    /*** IDXGIVkSwapChain methods ***/
    HRESULT (STDMETHODCALLTYPE *GetDesc)(
        IDXGIVkSwapChain *This,
        DXGI_SWAP_CHAIN_DESC1 *pDesc);

    HRESULT (STDMETHODCALLTYPE *GetAdapter)(
        IDXGIVkSwapChain *This,
        REFIID riid,
        void **ppvObject);

    HRESULT (STDMETHODCALLTYPE *GetDevice)(
        IDXGIVkSwapChain *This,
        REFIID riid,
        void **ppDevice);

    HRESULT (STDMETHODCALLTYPE *GetImage)(
        IDXGIVkSwapChain *This,
        UINT BufferId,
        REFIID riid,
        void **ppBuffer);

    UINT (STDMETHODCALLTYPE *GetImageIndex)(
        IDXGIVkSwapChain *This);

    UINT (STDMETHODCALLTYPE *GetFrameLatency)(
        IDXGIVkSwapChain *This);

    HANDLE (STDMETHODCALLTYPE *GetFrameLatencyEvent)(
        IDXGIVkSwapChain *This);

    HRESULT (STDMETHODCALLTYPE *ChangeProperties)(
        IDXGIVkSwapChain *This,
        const DXGI_SWAP_CHAIN_DESC1 *pDesc,
        const UINT *pNodeMasks,
        IUnknown *const *ppPresentQueues);

    HRESULT (STDMETHODCALLTYPE *SetPresentRegion)(
        IDXGIVkSwapChain *This,
        const RECT *pRegion);

    HRESULT (STDMETHODCALLTYPE *SetGammaControl)(
        IDXGIVkSwapChain *This,
        UINT NumControlPoints,
        const DXGI_RGB *pControlPoints);

    HRESULT (STDMETHODCALLTYPE *SetFrameLatency)(
        IDXGIVkSwapChain *This,
        UINT MaxLatency);

    HRESULT (STDMETHODCALLTYPE *Present)(
        IDXGIVkSwapChain *This,
        UINT SyncInterval,
        UINT PresentFlags,
        const DXGI_PRESENT_PARAMETERS *pPresentParameters);

    UINT (STDMETHODCALLTYPE *CheckColorSpaceSupport)(
        IDXGIVkSwapChain *This,
        DXGI_COLOR_SPACE_TYPE ColorSpace);

    HRESULT (STDMETHODCALLTYPE *SetColorSpace)(
        IDXGIVkSwapChain *This,
        DXGI_COLOR_SPACE_TYPE ColorSpace);

    HRESULT (STDMETHODCALLTYPE *SetHDRMetaData)(
        IDXGIVkSwapChain *This,
        const DXGI_VK_HDR_METADATA *pMetaData);

    END_INTERFACE
} IDXGIVkSwapChainVtbl;

interface IDXGIVkSwapChain {
    CONST_VTBL IDXGIVkSwapChainVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDXGIVkSwapChain_QueryInterface(This,riid,object) (This)->lpVtbl->QueryInterface(This,riid,object)
#define IDXGIVkSwapChain_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDXGIVkSwapChain_Release(This) (This)->lpVtbl->Release(This)
/*** IDXGIVkSwapChain methods ***/
#define IDXGIVkSwapChain_GetDesc(This,pDesc) (This)->lpVtbl->GetDesc(This,pDesc)
#define IDXGIVkSwapChain_GetAdapter(This,riid,ppvObject) (This)->lpVtbl->GetAdapter(This,riid,ppvObject)
#define IDXGIVkSwapChain_GetDevice(This,riid,ppDevice) (This)->lpVtbl->GetDevice(This,riid,ppDevice)
#define IDXGIVkSwapChain_GetImage(This,BufferId,riid,ppBuffer) (This)->lpVtbl->GetImage(This,BufferId,riid,ppBuffer)
#define IDXGIVkSwapChain_GetImageIndex(This) (This)->lpVtbl->GetImageIndex(This)
#define IDXGIVkSwapChain_GetFrameLatency(This) (This)->lpVtbl->GetFrameLatency(This)
#define IDXGIVkSwapChain_GetFrameLatencyEvent(This) (This)->lpVtbl->GetFrameLatencyEvent(This)
#define IDXGIVkSwapChain_ChangeProperties(This,pDesc,pNodeMasks,ppPresentQueues) (This)->lpVtbl->ChangeProperties(This,pDesc,pNodeMasks,ppPresentQueues)
#define IDXGIVkSwapChain_SetPresentRegion(This,pRegion) (This)->lpVtbl->SetPresentRegion(This,pRegion)
#define IDXGIVkSwapChain_SetGammaControl(This,NumControlPoints,pControlPoints) (This)->lpVtbl->SetGammaControl(This,NumControlPoints,pControlPoints)
#define IDXGIVkSwapChain_SetFrameLatency(This,MaxLatency) (This)->lpVtbl->SetFrameLatency(This,MaxLatency)
#define IDXGIVkSwapChain_Present(This,SyncInterval,PresentFlags,pPresentParameters) (This)->lpVtbl->Present(This,SyncInterval,PresentFlags,pPresentParameters)
#define IDXGIVkSwapChain_CheckColorSpaceSupport(This,ColorSpace) (This)->lpVtbl->CheckColorSpaceSupport(This,ColorSpace)
#define IDXGIVkSwapChain_SetColorSpace(This,ColorSpace) (This)->lpVtbl->SetColorSpace(This,ColorSpace)
#define IDXGIVkSwapChain_SetHDRMetaData(This,pMetaData) (This)->lpVtbl->SetHDRMetaData(This,pMetaData)
#else
/*** IUnknown methods ***/
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_QueryInterface(IDXGIVkSwapChain* This,REFIID riid,void **object) {
    return This->lpVtbl->QueryInterface(This,riid,object);
}
static __WIDL_INLINE ULONG IDXGIVkSwapChain_AddRef(IDXGIVkSwapChain* This) {
    return This->lpVtbl->AddRef(This);
}
static __WIDL_INLINE ULONG IDXGIVkSwapChain_Release(IDXGIVkSwapChain* This) {
    return This->lpVtbl->Release(This);
}
/*** IDXGIVkSwapChain methods ***/
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_GetDesc(IDXGIVkSwapChain* This,DXGI_SWAP_CHAIN_DESC1 *pDesc) {
    return This->lpVtbl->GetDesc(This,pDesc);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_GetAdapter(IDXGIVkSwapChain* This,REFIID riid,void **ppvObject) {
    return This->lpVtbl->GetAdapter(This,riid,ppvObject);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_GetDevice(IDXGIVkSwapChain* This,REFIID riid,void **ppDevice) {
    return This->lpVtbl->GetDevice(This,riid,ppDevice);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_GetImage(IDXGIVkSwapChain* This,UINT BufferId,REFIID riid,void **ppBuffer) {
    return This->lpVtbl->GetImage(This,BufferId,riid,ppBuffer);
}
static __WIDL_INLINE UINT IDXGIVkSwapChain_GetImageIndex(IDXGIVkSwapChain* This) {
    return This->lpVtbl->GetImageIndex(This);
}
static __WIDL_INLINE UINT IDXGIVkSwapChain_GetFrameLatency(IDXGIVkSwapChain* This) {
    return This->lpVtbl->GetFrameLatency(This);
}
static __WIDL_INLINE HANDLE IDXGIVkSwapChain_GetFrameLatencyEvent(IDXGIVkSwapChain* This) {
    return This->lpVtbl->GetFrameLatencyEvent(This);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_ChangeProperties(IDXGIVkSwapChain* This,const DXGI_SWAP_CHAIN_DESC1 *pDesc,const UINT *pNodeMasks,IUnknown *const *ppPresentQueues) {
    return This->lpVtbl->ChangeProperties(This,pDesc,pNodeMasks,ppPresentQueues);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_SetPresentRegion(IDXGIVkSwapChain* This,const RECT *pRegion) {
    return This->lpVtbl->SetPresentRegion(This,pRegion);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_SetGammaControl(IDXGIVkSwapChain* This,UINT NumControlPoints,const DXGI_RGB *pControlPoints) {
    return This->lpVtbl->SetGammaControl(This,NumControlPoints,pControlPoints);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_SetFrameLatency(IDXGIVkSwapChain* This,UINT MaxLatency) {
    return This->lpVtbl->SetFrameLatency(This,MaxLatency);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_Present(IDXGIVkSwapChain* This,UINT SyncInterval,UINT PresentFlags,const DXGI_PRESENT_PARAMETERS *pPresentParameters) {
    return This->lpVtbl->Present(This,SyncInterval,PresentFlags,pPresentParameters);
}
static __WIDL_INLINE UINT IDXGIVkSwapChain_CheckColorSpaceSupport(IDXGIVkSwapChain* This,DXGI_COLOR_SPACE_TYPE ColorSpace) {
    return This->lpVtbl->CheckColorSpaceSupport(This,ColorSpace);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_SetColorSpace(IDXGIVkSwapChain* This,DXGI_COLOR_SPACE_TYPE ColorSpace) {
    return This->lpVtbl->SetColorSpace(This,ColorSpace);
}
static __WIDL_INLINE HRESULT IDXGIVkSwapChain_SetHDRMetaData(IDXGIVkSwapChain* This,const DXGI_VK_HDR_METADATA *pMetaData) {
    return This->lpVtbl->SetHDRMetaData(This,pMetaData);
}
#endif
#endif

#endif


#endif  /* __IDXGIVkSwapChain_INTERFACE_DEFINED__ */

/*****************************************************************************
 * IDXGIVkSwapChainFactory interface
 */
#ifndef __IDXGIVkSwapChainFactory_INTERFACE_DEFINED__
#define __IDXGIVkSwapChainFactory_INTERFACE_DEFINED__

DEFINE_GUID(IID_IDXGIVkSwapChainFactory, 0xe7d6c3ca, 0x23a0, 0x4e08, 0x9f,0x2f, 0xea,0x52,0x31,0xdf,0x66,0x33);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("e7d6c3ca-23a0-4e08-9f2f-ea5231df6633")
IDXGIVkSwapChainFactory : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE CreateSwapChain(
        IDXGIVkSurfaceFactory *pSurfaceFactory,
        const DXGI_SWAP_CHAIN_DESC1 *pDesc,
        IDXGIVkSwapChain **ppSwapChain) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(IDXGIVkSwapChainFactory, 0xe7d6c3ca, 0x23a0, 0x4e08, 0x9f,0x2f, 0xea,0x52,0x31,0xdf,0x66,0x33)
#endif
#else
typedef struct IDXGIVkSwapChainFactoryVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        IDXGIVkSwapChainFactory *This,
        REFIID riid,
        void **object);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        IDXGIVkSwapChainFactory *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        IDXGIVkSwapChainFactory *This);

    /*** IDXGIVkSwapChainFactory methods ***/
    HRESULT (STDMETHODCALLTYPE *CreateSwapChain)(
        IDXGIVkSwapChainFactory *This,
        IDXGIVkSurfaceFactory *pSurfaceFactory,
        const DXGI_SWAP_CHAIN_DESC1 *pDesc,
        IDXGIVkSwapChain **ppSwapChain);

    END_INTERFACE
} IDXGIVkSwapChainFactoryVtbl;

interface IDXGIVkSwapChainFactory {
    CONST_VTBL IDXGIVkSwapChainFactoryVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define IDXGIVkSwapChainFactory_QueryInterface(This,riid,object) (This)->lpVtbl->QueryInterface(This,riid,object)
#define IDXGIVkSwapChainFactory_AddRef(This) (This)->lpVtbl->AddRef(This)
#define IDXGIVkSwapChainFactory_Release(This) (This)->lpVtbl->Release(This)
/*** IDXGIVkSwapChainFactory methods ***/
#define IDXGIVkSwapChainFactory_CreateSwapChain(This,pSurfaceFactory,pDesc,ppSwapChain) (This)->lpVtbl->CreateSwapChain(This,pSurfaceFactory,pDesc,ppSwapChain)
#else
/*** IUnknown methods ***/
static __WIDL_INLINE HRESULT IDXGIVkSwapChainFactory_QueryInterface(IDXGIVkSwapChainFactory* This,REFIID riid,void **object) {
    return This->lpVtbl->QueryInterface(This,riid,object);
}
static __WIDL_INLINE ULONG IDXGIVkSwapChainFactory_AddRef(IDXGIVkSwapChainFactory* This) {
    return This->lpVtbl->AddRef(This);
}
static __WIDL_INLINE ULONG IDXGIVkSwapChainFactory_Release(IDXGIVkSwapChainFactory* This) {
    return This->lpVtbl->Release(This);
}
/*** IDXGIVkSwapChainFactory methods ***/
static __WIDL_INLINE HRESULT IDXGIVkSwapChainFactory_CreateSwapChain(IDXGIVkSwapChainFactory* This,IDXGIVkSurfaceFactory *pSurfaceFactory,const DXGI_SWAP_CHAIN_DESC1 *pDesc,IDXGIVkSwapChain **ppSwapChain) {
    return This->lpVtbl->CreateSwapChain(This,pSurfaceFactory,pDesc,ppSwapChain);
}
#endif
#endif

#endif


#endif  /* __IDXGIVkSwapChainFactory_INTERFACE_DEFINED__ */

/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __vkd3d_swapchain_factory_h__ */
