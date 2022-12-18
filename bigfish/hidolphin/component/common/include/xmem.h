/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : xmem.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/09/17
  Description   : xmem.c header file
  History       :
  1.Date        : 2009/09/17
    Author      : dvb
    Modification: Created file

******************************************************************************/

#ifndef __XMEM_H__
#define __XMEM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_ref_mod.h"
#include "hi_unf_version.h"
#include "hi_common.h"

extern void *x_alloc(HI_HANDLE handle, HI_U32 size);
extern HI_S32 x_free(HI_HANDLE handle, void *addr);
extern HI_S32 x_get_mem_status(HI_HANDLE handle);
extern HI_S32 x_init_mem(HI_U32 modid, HI_U32 buf_len, HI_HANDLE *pHandle);
extern HI_S32 x_release_mem(HI_HANDLE handle);

extern HI_S32 x_reset_mem(HI_HANDLE handle);
//#ifndef HI_ADVCA_FUNCTION_RELEASE
#if (UNF_VERSION_CODE >= UNF_VERSION(3, 1))
HI_S32  xmem_CmdProc(HI_PROC_SHOW_BUFFER_S * pstBuf, HI_VOID *pPrivData);
#else
#ifndef HI_ADVCA_FUNCTION_RELEASE
HI_S32  xmem_CmdProc(HI_U32 u32Handle,int argc, const char* argv[]);
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __XMEM_H__ */
