/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: gfx2d_ctl.c
* Description: Graphic 2D engine ctl code.
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-10-23              NULL         Create this file.
*******************************************************************************/
#include <linux/mutex.h>

#include "hi_gfx2d_type.h"
#include "gfx2d_hal.h"
#include "gfx2d_list.h"
#include "gfx2d_mem.h"
#include "gfx2d_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

static HI_U32 gs_u32DevRef = 0;
static DEFINE_MUTEX(gs_stDevRefMutex);

HI_S32 GFX2D_CTL_Init(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 u32MemSize;

    u32MemSize = GFX2D_CONFIG_GetMemSize();

    s32Ret = GFX2D_MEM_Init(u32MemSize);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    s32Ret = GFX2D_HAL_Init();
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR;
    }

    s32Ret = GFX2D_LIST_Init();
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR1;
    }

    return HI_SUCCESS;

ERR1:
    (HI_VOID)GFX2D_HAL_Deinit();
ERR:
    (HI_VOID)GFX2D_MEM_Deinit();

    return s32Ret;
}

HI_S32 GFX2D_CTL_Deinit(HI_VOID)
{
    (HI_VOID)GFX2D_LIST_Deinit();

    (HI_VOID)GFX2D_HAL_Deinit();

    (HI_VOID)GFX2D_MEM_Deinit();

    return HI_SUCCESS;
}

HI_S32 GFX2D_CTL_Open(HI_VOID)
{
    HI_S32 s32Ret;

    mutex_lock(&gs_stDevRefMutex);

    /*dev has opened!*/
    if (gs_u32DevRef > 1)
    {
        mutex_unlock(&gs_stDevRefMutex);
        return HI_SUCCESS;
    }

    s32Ret = GFX2D_MEM_Open();
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = GFX2D_HAL_Open();
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR;
    }

    s32Ret = GFX2D_LIST_Open();
    if (HI_SUCCESS != s32Ret)
    {
        goto ERR1;
    }

    gs_u32DevRef++;

    mutex_unlock(&gs_stDevRefMutex);

    return HI_SUCCESS;

ERR1:
    (HI_VOID)GFX2D_HAL_Close();
ERR:
    (HI_VOID)GFX2D_MEM_Close();

    mutex_unlock(&gs_stDevRefMutex);

    return s32Ret;
}

HI_S32 GFX2D_CTL_Close(HI_VOID)
{
    mutex_lock(&gs_stDevRefMutex);

    /*dev not opened!*/
    if (0 == gs_u32DevRef)
    {
        mutex_unlock(&gs_stDevRefMutex);
        return HI_SUCCESS;
    }

    gs_u32DevRef--;

    /*still used by some module!*/
    if (gs_u32DevRef > 0)
    {
        mutex_unlock(&gs_stDevRefMutex);
        return HI_SUCCESS;
    }

    (HI_VOID)GFX2D_LIST_Close();
    (HI_VOID)GFX2D_HAL_Close();
    (HI_VOID)GFX2D_MEM_Close();

    mutex_unlock(&gs_stDevRefMutex);

    return HI_SUCCESS;
}

HI_S32 GFX2D_CTL_ComposeSync(const HI_GFX2D_DEV_ID_E enDevId,
                             HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                             HI_GFX2D_SURFACE_S *pstDstSurface,
                             const HI_U32 u32Timeout)
{
    HI_S32 s32Ret;
    HI_VOID *pNode = NULL;
    GFX2D_HAL_DEV_TYPE_E enNodeType;

    s32Ret = GFX2D_HAL_Compose(enDevId, pstComposeList, pstDstSurface, &pNode, &enNodeType);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = GFX2D_LIST_SubNode(enDevId, pNode, enNodeType, HI_TRUE, u32Timeout);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    return HI_SUCCESS;
}


HI_S32 GFX2D_CTL_ComposeAsync(const HI_GFX2D_DEV_ID_E enDevId,
                              HI_GFX2D_COMPOSE_LIST_S *pstComposeList,
                              HI_GFX2D_SURFACE_S *pstDstSurface)
{
    HI_S32 s32Ret;
    HI_VOID *pNode = NULL;
    GFX2D_HAL_DEV_TYPE_E enNodeType;

    s32Ret = GFX2D_HAL_Compose(enDevId, pstComposeList, pstDstSurface, &pNode, &enNodeType);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    s32Ret = GFX2D_LIST_SubNode(enDevId, pNode, enNodeType, HI_FALSE, 0);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 GFX2D_CTL_WaitAllDone(const HI_GFX2D_DEV_ID_E enDevId,
                             const HI_U32 u32Timeout)
{
    return GFX2D_LIST_WaitAllDone(enDevId, u32Timeout);
}

#ifndef GFX2D_PROC_UNSUPPORT
HI_S32 GFX2D_CTL_ReadProc(struct seq_file *p, HI_VOID *v)
{

    if (NULL == p)
    {
       return HI_FAILURE;
    }

    (HI_VOID)GFX2D_MEM_ReadProc(p, v);

    (HI_VOID)GFX2D_LIST_ReadProc(p, v);

    (HI_VOID)GFX2D_HAL_ReadProc(p, v);

    return HI_SUCCESS;
}

HI_S32 GFX2D_CTL_WriteProc(struct file * file, const char __user * buf,
                           size_t count, loff_t *ppos)
{
    (HI_VOID)GFX2D_MEM_WriteProc(file, buf, count, ppos);

    (HI_VOID)GFX2D_LIST_WriteProc(file, buf, count, ppos);

    (HI_VOID)GFX2D_HAL_WriteProc(file, buf, count, ppos);

    return HI_SUCCESS;
}
#endif


HI_BOOL GFX2D_CTL_CheckOpen(HI_VOID)
{
    return (gs_u32DevRef > 0) ? HI_TRUE : HI_FALSE;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/
