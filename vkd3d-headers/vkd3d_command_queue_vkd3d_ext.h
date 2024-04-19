/*** Autogenerated by WIDL 8.0 from ../include/vkd3d_command_queue_vkd3d_ext.idl - Do not edit ***/

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

#ifndef __vkd3d_command_queue_vkd3d_ext_h__
#define __vkd3d_command_queue_vkd3d_ext_h__

#ifndef __WIDL_INLINE
#if defined(__cplusplus) || defined(_MSC_VER)
#define __WIDL_INLINE inline
#elif defined(__GNUC__)
#define __WIDL_INLINE __inline__
#endif
#endif

/* Forward declarations */

#ifndef __ID3D12CommandQueueExt_FWD_DEFINED__
#define __ID3D12CommandQueueExt_FWD_DEFINED__
typedef interface ID3D12CommandQueueExt ID3D12CommandQueueExt;
#ifdef __cplusplus
interface ID3D12CommandQueueExt;
#endif /* __cplusplus */
#endif

/* Headers for imported files */

#include <vkd3d_d3d12.h>
#include <vkd3d_vk_includes.h>

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * ID3D12CommandQueueExt interface
 */
#ifndef __ID3D12CommandQueueExt_INTERFACE_DEFINED__
#define __ID3D12CommandQueueExt_INTERFACE_DEFINED__

DEFINE_GUID(IID_ID3D12CommandQueueExt, 0x40ed3f96, 0xe773, 0xe9bc, 0xfc,0x0c, 0xe9,0x55,0x60,0xc9,0x9a,0xd6);
#if defined(__cplusplus) && !defined(CINTERFACE)
MIDL_INTERFACE("40ed3f96-e773-e9bc-fc0c-e95560c99ad6")
ID3D12CommandQueueExt : public IUnknown
{
    virtual HRESULT STDMETHODCALLTYPE NotifyOutOfBandCommandQueue(
        D3D12_OUT_OF_BAND_CQ_TYPE type) = 0;

};
#ifdef __CRT_UUID_DECL
__CRT_UUID_DECL(ID3D12CommandQueueExt, 0x40ed3f96, 0xe773, 0xe9bc, 0xfc,0x0c, 0xe9,0x55,0x60,0xc9,0x9a,0xd6)
#endif
#else
typedef struct ID3D12CommandQueueExtVtbl {
    BEGIN_INTERFACE

    /*** IUnknown methods ***/
    HRESULT (STDMETHODCALLTYPE *QueryInterface)(
        ID3D12CommandQueueExt *This,
        REFIID riid,
        void **object);

    ULONG (STDMETHODCALLTYPE *AddRef)(
        ID3D12CommandQueueExt *This);

    ULONG (STDMETHODCALLTYPE *Release)(
        ID3D12CommandQueueExt *This);

    /*** ID3D12CommandQueueExt methods ***/
    HRESULT (STDMETHODCALLTYPE *NotifyOutOfBandCommandQueue)(
        ID3D12CommandQueueExt *This,
        D3D12_OUT_OF_BAND_CQ_TYPE type);

    END_INTERFACE
} ID3D12CommandQueueExtVtbl;

interface ID3D12CommandQueueExt {
    CONST_VTBL ID3D12CommandQueueExtVtbl* lpVtbl;
};

#ifdef COBJMACROS
#ifndef WIDL_C_INLINE_WRAPPERS
/*** IUnknown methods ***/
#define ID3D12CommandQueueExt_QueryInterface(This,riid,object) (This)->lpVtbl->QueryInterface(This,riid,object)
#define ID3D12CommandQueueExt_AddRef(This) (This)->lpVtbl->AddRef(This)
#define ID3D12CommandQueueExt_Release(This) (This)->lpVtbl->Release(This)
/*** ID3D12CommandQueueExt methods ***/
#define ID3D12CommandQueueExt_NotifyOutOfBandCommandQueue(This,type) (This)->lpVtbl->NotifyOutOfBandCommandQueue(This,type)
#else
/*** IUnknown methods ***/
static __WIDL_INLINE HRESULT ID3D12CommandQueueExt_QueryInterface(ID3D12CommandQueueExt* This,REFIID riid,void **object) {
    return This->lpVtbl->QueryInterface(This,riid,object);
}
static __WIDL_INLINE ULONG ID3D12CommandQueueExt_AddRef(ID3D12CommandQueueExt* This) {
    return This->lpVtbl->AddRef(This);
}
static __WIDL_INLINE ULONG ID3D12CommandQueueExt_Release(ID3D12CommandQueueExt* This) {
    return This->lpVtbl->Release(This);
}
/*** ID3D12CommandQueueExt methods ***/
static __WIDL_INLINE HRESULT ID3D12CommandQueueExt_NotifyOutOfBandCommandQueue(ID3D12CommandQueueExt* This,D3D12_OUT_OF_BAND_CQ_TYPE type) {
    return This->lpVtbl->NotifyOutOfBandCommandQueue(This,type);
}
#endif
#endif

#endif


#endif  /* __ID3D12CommandQueueExt_INTERFACE_DEFINED__ */

/* Begin additional prototypes for all interfaces */


/* End additional prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __vkd3d_command_queue_vkd3d_ext_h__ */