/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: gfx2d_mem.h
* Description: 
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-08-02              NULL         Create this file.
*******************************************************************************/
#ifndef _GFX2D_MEM_H_
#define _GFX2D_MEM_H_

#include "gfx2d_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/*******************************************************************************
* Function:      GFX2D_MEM_Init
* Description:   内存层初始化
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
HI_S32 GFX2D_MEM_Init(const HI_U32 u32Size);

/*******************************************************************************
* Function:      GFX2D_MEM_Deinit
* Description:   内存层去初始化
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
HI_S32 GFX2D_MEM_Deinit(HI_VOID);

/*******************************************************************************
* Function:      GFX2D_MEM_Open
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
HI_S32 GFX2D_MEM_Open(HI_VOID);

/*******************************************************************************
* Function:      GFX2D_MEM_Close
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
HI_S32 GFX2D_MEM_Close(HI_VOID);

/*******************************************************************************
* Function:      GFX2D_MEM_Register
* Description:   注册固定大小的内存块
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
HI_S32 GFX2D_MEM_Register(const HI_U32 u32MemSize, const HI_U32 u32BlockSize);

/*******************************************************************************
* Function:      GFX2D_Mem_UnRegister
* Description:   注销固定大小的内存块
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
HI_S32 GFX2D_Mem_UnRegister(const HI_U32 u32BlockSize);

/*******************************************************************************
* Function:      GFX2D_MEM_Alloc
* Description:   分配内存
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
HI_VOID *GFX2D_MEM_Alloc(const HI_U32 u32Size);

/*******************************************************************************
* Function:      GFX2D_MEM_Free
* Description:   释放内存
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
HI_S32 GFX2D_MEM_Free(HI_VOID *pBuf);

/*******************************************************************************
* Function:      GFX2D_MEM_GetPhyaddr
* Description:   获取内存物理地址
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
HI_U32 GFX2D_MEM_GetPhyaddr(HI_VOID *pBuf);

#ifndef GFX2D_PROC_UNSUPPORT
/*******************************************************************************
* Function:      GFX2D_MEM_ReadProc
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
HI_S32 GFX2D_MEM_ReadProc(struct seq_file *p, HI_VOID *v);

/*******************************************************************************
* Function:      GFX2D_MEM_WriteProc
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
HI_S32 GFX2D_MEM_WriteProc(struct file * file, const char __user * buf,\
                           size_t count, loff_t *ppos);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#endif  /*_GFX2D_MEM_H_*/
