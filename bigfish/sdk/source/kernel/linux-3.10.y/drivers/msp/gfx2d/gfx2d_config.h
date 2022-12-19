/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: gfx2d_hal_hwc.c
* Description: Graphic 2D engine hwc interface declaration
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-08-02              NULL         Create this file.
*******************************************************************************/
#include <linux/fs.h>

#include "hi_type.h"

#ifndef _GFX2D_CONFIG_H_
#define _GFX2D_CONFIG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#ifdef HI_ADVCA_FUNCTION_RELEASE
#define GFX2D_PROC_UNSUPPORT
#endif

/*******************************************************************************
* Function:      GFX2D_CONFIG_SetMemSize
* Description:   
* Input:         in_para1     parameter description
*                in_para2     parameter description
* Output:        out_para1    parameter description
*                out_para2    parameter description
* Return:        HI_OK:                         success
*                HI_ERR_SYSM_NOMEMORY:          Allocate memory fail.
*                HI_ERR_SYSM_NODISKSPACE:       Disk space full.
*                HI_ERR_SYSM_FILEWRITE:         File write error.
* Others:        in_para1 should be none-zero
*******************************************************************************/
HI_S32 GFX2D_CONFIG_SetMemSize(HI_U32 u32MemSize);

/*******************************************************************************
* Function:      GFX2D_CONFIG_SetMemSize
* Description:   
* Input:         in_para1     parameter description
*                in_para2     parameter description
* Output:        out_para1    parameter description
*                out_para2    parameter description
* Return:        HI_OK:                         success
*                HI_ERR_SYSM_NOMEMORY:          Allocate memory fail.
*                HI_ERR_SYSM_NODISKSPACE:       Disk space full.
*                HI_ERR_SYSM_FILEWRITE:         File write error.
* Others:        in_para1 should be none-zero
*******************************************************************************/
HI_U32 GFX2D_CONFIG_GetMemSize(HI_VOID);

/*******************************************************************************
* Function:      GFX2D_CONFIG_SetMemSize
* Description:   
* Input:         in_para1     parameter description
*                in_para2     parameter description
* Output:        out_para1    parameter description
*                out_para2    parameter description
* Return:        HI_OK:                         success
*                HI_ERR_SYSM_NOMEMORY:          Allocate memory fail.
*                HI_ERR_SYSM_NODISKSPACE:       Disk space full.
*                HI_ERR_SYSM_FILEWRITE:         File write error.
* Others:        in_para1 should be none-zero
*******************************************************************************/
HI_U32 GFX2D_CONFIG_GetNodeNum(HI_VOID);

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_CONFIG_StartTime(HI_VOID);

HI_U32 GFX2D_CONFIG_EndTime(HI_VOID);

HI_BOOL GFX2D_CONFIG_IsProcOn(HI_VOID);

HI_S32 GFX2D_CONFIG_WriteProc(struct file * file, const char __user * buf,
                              size_t count, loff_t *ppos);
#endif

#ifndef GFX2D_CHECK_UNSUPPORT
HI_BOOL GFX2D_CONFIG_IsCheckOn(HI_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif
