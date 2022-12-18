/***********************************************************************************
*              Copyright 2006 - 2006, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_out.h
* Description: out model .
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.1       2006-04-07   q63946  NULL         Create this file.
***********************************************************************************/

#ifndef __HI_OUT_H__
#define __HI_OUT_H__

#include <stdarg.h>
#include "hi_type.h"
#include "hi_adp_interface.h"
#include "hi_ref_mod.h"
#include "hi_ref_errno.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define HI_ERR_OUT_NOFOUND      HI_EPAERM

typedef HI_VA_LIST OUT_VA_LIST;
typedef void * (*Print_FUN)(void* pDest, char* fmt, OUT_VA_LIST pstruArg);

#define DEMO_NAME_SIZE 17
typedef struct demoOUT_Reg_S
{
    HI_U32      u32Handle;
    Print_FUN   pfunPrint;
    HI_VOID     *pDest;
    struct demoOUT_Reg_S *pstruNext;
} OUT_Reg_S;

/*注册打印输出处理接口*/
HI_S32 HI_OUT_Register( Print_FUN pfunPrint, HI_VOID* pDest, HI_U32* pu32Handle);
/*注销打印输出处理接口*/
HI_S32 HI_OUT_Deregister(HI_U32 u32Handle);
/*修改打印输出处理接口*/
HI_S32 HI_OUT_Editregister(HI_U32 u32Handle, Print_FUN pfunPrint, HI_VOID* pDest);
/*提供给其他模块的打印输出接口*/
HI_S32 HI_OUT_Printf(HI_U32 u32Handle, const  HI_CHAR* fmt, ...);
/*去初始化打印输出处理接口*/
HI_S32 OUT_DeINIT();


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_OUT_H__ */
