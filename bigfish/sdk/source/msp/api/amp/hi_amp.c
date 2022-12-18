/*****************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_aenc.c
* Description: Describe main functionality and purpose of this file.
*
* History:
* Version   Date         Author     DefectNum    Description
* 0.01      
*
*****************************************************************************/


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_debug.h"
#include "hi_module.h"
#include "hi_mpi_mem.h"
#include "hi_drv_struct.h"
#include "hi_error_mpi.h"

#include "hi_drv_amp.h"
#include "drv_amp_ioctl.h"

static HI_S32 g_s32AMPFd = -1;
static const HI_CHAR g_acAMPDevName[] = "/dev/" UMAP_DEVNAME_AMP;

HI_S32 HI_AMP_Init(HI_VOID)
{
    if (g_s32AMPFd < 0)
    {
        g_s32AMPFd = open(g_acAMPDevName, O_RDWR, 0);
        if (g_s32AMPFd < 0)    
        {
            HI_FATAL_AMP("OpenAMPDevice err\n");
            g_s32AMPFd = -1;
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32   HI_AMP_DeInit(HI_VOID)
{
    if(g_s32AMPFd > 0)  //verify
    {
        close(g_s32AMPFd);
        g_s32AMPFd = -1;
    }

    return HI_SUCCESS;
}

HI_S32   HI_AMP_SetMute(HI_BOOL bMute)
{    
    return ioctl(g_s32AMPFd, CMD_AMP_SETMUTE, &bMute);
}

HI_S32 HI_AMP_GetMute(HI_BOOL *pbMute)
{
    HI_S32 s32Ret;
    HI_BOOL bMute;
    
    CHECK_AMP_NULL_PTR(pbMute);

    s32Ret = ioctl(g_s32AMPFd, CMD_AMP_GETMUTE, &bMute);
    if(HI_SUCCESS == s32Ret)
    {
        *pbMute = bMute;
    }
    
    return s32Ret;
}

HI_S32 HI_AMP_SetSubWooferVol(HI_U32 u32Volume)
{    
    return ioctl(g_s32AMPFd, CMD_AMP_SETSUBWOOFERVOL, &u32Volume);
}
    
HI_S32 HI_AMP_GetSubWooferVol(HI_U32 *pu32Volume)
{
    HI_S32 s32Ret;
    HI_U32 u32Volume;
    
    CHECK_AMP_NULL_PTR(pu32Volume);

    s32Ret = ioctl(g_s32AMPFd, CMD_AMP_GETSUBWOOFERVOL, &u32Volume);
    if(HI_SUCCESS == s32Ret)
    {
        *pu32Volume = u32Volume;
    }
    
    return s32Ret;
}

HI_S32 HI_AMP_WriteReg(HI_U32 u32RegAddr, HI_U32 u32ByteSize, HI_U8 *pu8Value)
{
    AMP_REG_OPERATE_PARAM_S stRegParam;

    CHECK_AMP_NULL_PTR(pu8Value);

    stRegParam.u32RegAddr = u32RegAddr;
    stRegParam.u32ByteSize = u32ByteSize;
    stRegParam.pu8Value   = pu8Value;

    return ioctl(g_s32AMPFd, CMD_AMP_WRITEREG, &stRegParam);
}

HI_S32 HI_AMP_ReadReg(HI_U32 u32RegAddr, HI_U32 u32ByteSize, HI_U8 *pu8Value)
{
    AMP_REG_OPERATE_PARAM_S stRegParam;

    CHECK_AMP_NULL_PTR(pu8Value);

    stRegParam.u32RegAddr = u32RegAddr;
    stRegParam.u32ByteSize = u32ByteSize;
    stRegParam.pu8Value   = pu8Value;
    
    return ioctl(g_s32AMPFd, CMD_AMP_READREG, &stRegParam);
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */
