

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for .\IComTest.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0628 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __IComTest_h__
#define __IComTest_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IComTest_FWD_DEFINED__
#define __IComTest_FWD_DEFINED__
typedef interface IComTest IComTest;

#endif 	/* __IComTest_FWD_DEFINED__ */


#ifndef __IGDV_FWD_DEFINED__
#define __IGDV_FWD_DEFINED__
typedef interface IGDV IGDV;

#endif 	/* __IGDV_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IComTest_INTERFACE_DEFINED__
#define __IComTest_INTERFACE_DEFINED__

/* interface IComTest */
/* [helpstring][version][uuid][object] */ 


EXTERN_C const IID IID_IComTest;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0C62619-3BC1-4095-9B9A-84503E37DAA5")
    IComTest : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE WhoAmI( 
            /* [out] */ LPWSTR *pwszWhoAmI) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IComTestVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComTest * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComTest * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComTest * This);
        
        DECLSPEC_XFGVIRT(IComTest, WhoAmI)
        HRESULT ( STDMETHODCALLTYPE *WhoAmI )( 
            IComTest * This,
            /* [out] */ LPWSTR *pwszWhoAmI);
        
        END_INTERFACE
    } IComTestVtbl;

    interface IComTest
    {
        CONST_VTBL struct IComTestVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComTest_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComTest_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComTest_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComTest_WhoAmI(This,pwszWhoAmI)	\
    ( (This)->lpVtbl -> WhoAmI(This,pwszWhoAmI) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComTest_INTERFACE_DEFINED__ */


#ifndef __IGDV_INTERFACE_DEFINED__
#define __IGDV_INTERFACE_DEFINED__

/* interface IGDV */
/* [helpstring][version][uuid][object] */ 


EXTERN_C const IID IID_IGDV;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AEC109A3-62A1-4FAA-BFDC-C433B1C4CF70")
    IGDV : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE getThirdDigitFromEnd( 
            /* [in] */ int x,
            /* [retval][out] */ int *result) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IGDVVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IGDV * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IGDV * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IGDV * This);
        
        DECLSPEC_XFGVIRT(IGDV, getThirdDigitFromEnd)
        HRESULT ( STDMETHODCALLTYPE *getThirdDigitFromEnd )( 
            IGDV * This,
            /* [in] */ int x,
            /* [retval][out] */ int *result);
        
        END_INTERFACE
    } IGDVVtbl;

    interface IGDV
    {
        CONST_VTBL struct IGDVVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IGDV_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IGDV_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IGDV_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IGDV_getThirdDigitFromEnd(This,x,result)	\
    ( (This)->lpVtbl -> getThirdDigitFromEnd(This,x,result) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IGDV_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


