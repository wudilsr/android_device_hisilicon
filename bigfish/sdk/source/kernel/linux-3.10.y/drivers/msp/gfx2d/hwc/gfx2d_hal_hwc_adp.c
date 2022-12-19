/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: gfx2d_hal_hwc_adp.c
* Description: hwc adp code
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-10-23              NULL         Create this file.
*******************************************************************************/
#include "gfx2d_hal_hwc_adp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

static HWC_CAPABILITY_S gs_stCapability = 
{
    7,
    6,
    1,
    {0x00c043d0,0xfe7efc},
    {0x0c040c0,0x200},
    1,
    0xffff,
    16,
    1,
#if defined(CHIP_TYPE_hi3798cv100) || defined(CHIP_TYPE_hi3796cv100)
    3840,
#else
    2560,
#endif
    1,
#if defined(CHIP_TYPE_hi3798cv100) || defined(CHIP_TYPE_hi3796cv100)
    2160,
#else
    1600,
#endif
    32,
    32,
    256,
    16,
    2,
    {0x400000,0x0}
};

HI_S32 HWC_ADP_GetCapability(HWC_CAPABILITY_S *pstCapability)
{
    memcpy(pstCapability, &gs_stCapability, sizeof(HWC_CAPABILITY_S));
    
    return HI_SUCCESS;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/
