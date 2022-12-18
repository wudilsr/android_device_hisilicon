/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: gfx2d_os.c
* Description: 
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-08-02              NULL         Create this file.
*******************************************************************************/
#include "gfx2d_config.h"
#include "hi_gfx_comm_k.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

#define GFX2D_CONFIG_DEFAULT_MEMSIZE 60 * 1024

/*Mem size(KByte)*/
static HI_U32 gs_u32MemSize = GFX2D_CONFIG_DEFAULT_MEMSIZE;

#ifndef GFX2D_PROC_UNSUPPORT
static struct timeval gs_stStartTime,gs_stEndTime;
static HI_BOOL gs_bProcEnable = HI_TRUE;
#endif

#ifndef GFX2D_CHECK_UNSUPPORT
static HI_BOOL gs_bCheckEnable = HI_TRUE;
#endif

HI_S32 GFX2D_CONFIG_SetMemSize(HI_U32 u32MemSize)
{
    if (0 == u32MemSize)
    {
#ifdef CFG_HI_GFX2D_MEM_SIZE
        u32MemSize = CFG_HI_GFX2D_MEM_SIZE;
#else
        u32MemSize = GFX2D_CONFIG_DEFAULT_MEMSIZE;
#endif
    }
    else if (u32MemSize < 1024)
    {
        HI_GFX_COMM_LOG_ERROR(HIGFX_GFX2D_ID, "Mem not enough to work!\n");
        return HI_FAILURE;
    }

    gs_u32MemSize = u32MemSize;
    
    return HI_SUCCESS;
}

HI_U32 GFX2D_CONFIG_GetMemSize(HI_VOID)
{
    return gs_u32MemSize;
}


HI_U32 GFX2D_CONFIG_GetNodeNum(HI_VOID)
{
    /*A node occupy 1K byte,so node num can be calculated by mem_size/1024.
    Node size is affected by logic mainly,but also the software node mangment structure.
    1K is not a accurate size of a node, that means a smaller size may also works.Why 1K?
    1.It obligate space for future change of node size,generate by logic design or software design.
    2.It is easy to explain and remember the relation between node num and mem size.*/
    return gs_u32MemSize / 1024;
}

#ifndef GFX2D_CHECK_UNSUPPORT
HI_BOOL GFX2D_CONFIG_IsCheckOn(HI_VOID)
{
    return gs_bCheckEnable;
}
#endif

#ifndef GFX2D_PROC_UNSUPPORT
HI_VOID GFX2D_CONFIG_StartTime(HI_VOID)
{
    do_gettimeofday(&gs_stStartTime);
}

HI_U32 GFX2D_CONFIG_EndTime(HI_VOID)
{
    do_gettimeofday(&gs_stEndTime);

    return (gs_stEndTime.tv_sec - gs_stStartTime.tv_sec) * 1000000 + (gs_stEndTime.tv_usec - gs_stStartTime.tv_usec);
}

HI_BOOL GFX2D_CONFIG_IsProcOn(HI_VOID)
{
    return gs_bProcEnable;
}

HI_S32 GFX2D_CONFIG_WriteProc(struct file * file, const char __user * buf,
                              size_t count, loff_t *ppos)
{
    if (strncasecmp(buf, "proc on", strlen("proc on")) == 0)
    {
        gs_bProcEnable = HI_TRUE;
    }
    else if (strncasecmp(buf, "proc off", strlen("proc off")) == 0)
    {
        gs_bProcEnable = HI_FALSE;
    }
    else
    {
        if (!gs_bProcEnable)
        {
            return HI_SUCCESS;
        }

#ifndef GFX2D_CHECK_UNSUPPORT
        if (strncasecmp(buf, "check on", strlen("check on")) == 0)
        {
            gs_bCheckEnable = HI_TRUE;
        }
        else if (strncasecmp(buf, "check off", strlen("check off")) == 0)
        {
            gs_bCheckEnable = HI_FALSE;
        }
#endif
    }

    return HI_SUCCESS;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/
