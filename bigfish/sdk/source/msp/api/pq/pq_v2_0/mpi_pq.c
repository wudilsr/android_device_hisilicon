/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : mpi_pq.c
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/04/01
  Description   : MPI层封装函数

******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#include "hi_type.h"
#include "hi_mpi_pq.h"



/* PQ设备文件描述符 */
static HI_S32 sg_s32PQFd = -1;

static HI_BOOL sg_bPQInitFlag = HI_FALSE;

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 \PQ初始化
 \attention \n

 \param[in] pszPath:PQ配置文件路径
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_Init(HI_CHAR* pszPath)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_PATE_S stPqPath;

    if (HI_TRUE == sg_bPQInitFlag)
    {
        return HI_SUCCESS;
    }

    /* PQ设备初始化 */
    sg_s32PQFd = open("/dev/hi_pq", O_RDWR | O_NONBLOCK);
    if (sg_s32PQFd <= 0)
    {
        HI_ERR_PQ("PQ device open error!");
        return HI_FAILURE;
    }
    sg_bPQInitFlag = HI_TRUE;

    /* PQ配置文件路径*/
    if (pszPath != NULL)
    {
        memset(&stPqPath, 0, sizeof(HI_PQ_PATE_S));
        strncpy(stPqPath.cPqPath, pszPath, sizeof(stPqPath.cPqPath) - 1);
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_PQ_PATH, &stPqPath);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PQ("set pq bin path error!");
        }
    }
    else
    {
        //HI_ERR_PQ("pq bin path is invalid,Use default PQ setting!");
    }
    return HI_SUCCESS;
}

/**
 \PQ去初始化
 \attention \n

 \param[in]
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_FALSE == sg_bPQInitFlag)
    {
        return HI_SUCCESS;
    }

    sg_bPQInitFlag = HI_FALSE;
    s32Ret = close(sg_s32PQFd);
    return s32Ret;
}

/**
 \brief 获取亮度
 \attention \n
无

 \param[in] pu32Brightness 亮度值,有效范围: 0~100;
 \param[out]

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetBrightness(HI_DRV_DISPLAY_E enChan, HI_U32* pu32Brightness)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RetNum = 0;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_BRIGHTNESS, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_BRIGHTNESS, &u32RetNum);
    }

    *pu32Brightness = u32RetNum;
    return s32Ret;
}

/**
 \brief 设置亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetBrightness(HI_DRV_DISPLAY_E enChan, HI_U32 u32Brightness)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 Brightness = u32Brightness;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_BRIGHTNESS, &Brightness);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_BRIGHTNESS, &Brightness);
    }

    return s32Ret;
}


/**
 \brief 获取对比度
 \attention \n
无

 \param[in]
 \param[out] pu32Contrast 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetContrast(HI_DRV_DISPLAY_E enChan, HI_U32* pu32Contrast)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RetNum = 0;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_CONTRAST, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_CONTRAST, &u32RetNum);
    }

    *pu32Contrast = u32RetNum;
    return s32Ret;
}

/**
 \brief 设置对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetContrast(HI_DRV_DISPLAY_E enChan, HI_U32 u32Contrast)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 Contrast = u32Contrast;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_CONTRAST, &Contrast);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_CONTRAST, &Contrast);
    }

    return s32Ret;
}

/**
 \brief 获取饱和度
 \attention \n
无

 \param[out] pu32Saturation：饱和度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSaturation(HI_DRV_DISPLAY_E enChan, HI_U32* pu32Saturation)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RetNum = 0;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_SATURATION, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_SATURATION, &u32RetNum);
    }

    *pu32Saturation = u32RetNum;
    return s32Ret;
}

/**
 \brief 设置饱和度
 \attention \n
无

 \param[in] u32Saturation：饱和度,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSaturation(HI_DRV_DISPLAY_E enChan, HI_U32 u32Saturation)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 Saturation = u32Saturation;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_SATURATION, &Saturation);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_SATURATION, &Saturation);
    }

    return s32Ret;
}

/**
 \brief 获取色调
 \attention \n
无

 \param[in]
 \param[out] pu32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetHue(HI_DRV_DISPLAY_E enChan, HI_U32* pu32Hue)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RetNum = 0;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SD_HUE, &u32RetNum);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_HD_HUE, &u32RetNum);
    }

    *pu32Hue = u32RetNum;
    return s32Ret;
}

/**
 \brief 设置色调
 \attention \n
无

 \param[in] u32Hue：色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetHue(HI_DRV_DISPLAY_E enChan, HI_U32 u32Hue)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 Hue = u32Hue;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (HI_DRV_DISPLAY_0 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SD_HUE, &Hue);
    }
    else if (HI_DRV_DISPLAY_1 == enChan)
    {
        s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_HD_HUE, &Hue);
    }

    return s32Ret;
}

/**
 \brief 获取降噪强度
 \attention \n
无

 \param[out] pu32NRLevel: 降噪等级, 有效范围: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetNR(HI_U32* pu32NRLevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_NR, pu32NRLevel);

    return s32Ret;
}

/**
 \brief 设置降噪强度
 \attention \n
无

 \param[in] u32NRLevel: 降噪等级, 有效范围: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetNR(HI_U32 u32NRLevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_NR, &u32NRLevel);

    return s32Ret;
}

/**
 \brief 获取自动降噪开关状态
 \attention \n
无

 \param[out] pu32OnOff


 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetNRAutoMode(HI_U32* pu32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_NR_AUTO, pu32OnOff);

    return s32Ret;
}

/**
 \brief 设置降噪自动模式开关
 \attention \n
无

 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetNRAutoMode(HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_NR_AUTO, &u32OnOff);

    return s32Ret;
}

/**
 \brief 获取SR演示类型
 \attention \n
无

 \param[out] *penType


 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSRMode(HI_PQ_SR_DEMO_E* penType)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SR_DEMO, penType);

    return s32Ret;
}

/**
 \brief 设置SR演示类型
 \attention \n
无

 \param[in] enType

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSRMode(HI_PQ_SR_DEMO_E enType)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SR_DEMO, &enType);

    return s32Ret;
}

/**
 \brief 获取清晰度
 \attention \n
无

 \param[out] pu32Sharpness：清晰度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSharpness(HI_U32* pu32Sharpness)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Num = 0;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SHARPNESS, &u32Num);
    *pu32Sharpness = u32Num;

    return s32Ret;
}

/**
 \brief 设置清晰度
 \attention \n
无

 \param[in] u32Sharpness：清晰度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSharpness(HI_U32 u32Sharpness)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Num = u32Sharpness;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SHARPNESS, &u32Num);

    return s32Ret;
}

/**
 \brief 获取块降噪De-blocking强度
 \attention \n
无

 \param[out] pu32DBlevel：降噪等级, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDeBlocking(HI_U32* pu32DBlevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DB, pu32DBlevel);

    return s32Ret;
}

/**
 \brief 设置块降噪De-blocking强度
 \attention \n
无

 \param[in] u32DBlevel:降噪等级, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDeBlocking(HI_U32 u32DBlevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DB, &u32DBlevel);

    return s32Ret;
}

/**
 \brief 获取去除蚊虫噪声de-ringing强度
 \attention \n
无

 \param[out] pu32DRlevel:降噪等级, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDeRinging(HI_U32* pu32DRlevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DR, pu32DRlevel);

    return s32Ret;
}


/**
 \brief 设置去除蚊虫噪声de-ringing强度
 \attention \n
无

 \param[in] u32DRlevel:降噪等级, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDeRinging(HI_U32 u32DRlevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DR, &u32DRlevel);

    return s32Ret;
}

/**
 \brief 获取色温参数
 \attention \n
无

 \param[in] pstColorTemp：色温参数
 \param[out]

 \retval ::HI_SUCCESS

 */

/*HI_S32 HI_MPI_PQ_GetColorTemp( HI_UNF_PQ_COLOR_TEMP_S *pstColorTemp)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_COLOR_TEMP_S stColorTemp = {0};

    if(sg_bPQInitFlag==HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd,HIIOC_PQ_G_COLORTEMP,&stColorTemp);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    pstColorTemp->u32BlueGain    = (HI_U32)stColorTemp.s16BlueGain;
    pstColorTemp->u32GreenGain   = (HI_U32)stColorTemp.s16GreenGain;
    pstColorTemp->u32RedGain     = (HI_U32)stColorTemp.s16RedGain;
    pstColorTemp->u32BlueOffset  = (HI_U32)stColorTemp.s16BlueOffset;
    pstColorTemp->u32GreenOffset = (HI_U32)stColorTemp.s16GreenOffset;
    pstColorTemp->u32RedOffset   = (HI_U32)stColorTemp.s16RedOffset;

    return HI_SUCCESS;
}
*/


/**
 \brief 设置色温参数
 \attention \n
无

 \param[in] pstColorTemp:色温参数
 \param[out]

 \retval ::HI_SUCCESS

 */

/*HI_S32 HI_MPI_PQ_SetColorTemp(HI_UNF_PQ_COLOR_TEMP_S *pstColorTemp)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_COLOR_TEMP_S stColorTemp = {0};

    if(sg_bPQInitFlag==HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    stColorTemp.s16BlueGain    = (HI_S16)pstColorTemp->u32BlueGain;
    stColorTemp.s16GreenGain   = (HI_S16)pstColorTemp->u32GreenGain;
    stColorTemp.s16RedGain     = (HI_S16)pstColorTemp->u32RedGain;
    stColorTemp.s16BlueOffset  = (HI_S16)pstColorTemp->u32BlueOffset;
    stColorTemp.s16GreenOffset = (HI_S16)pstColorTemp->u32GreenOffset;
    stColorTemp.s16RedOffset   = (HI_S16)pstColorTemp->u32RedOffset;
    s32Ret = ioctl(sg_s32PQFd,HIIOC_PQ_S_COLORTEMP,&stColorTemp);

    return HI_SUCCESS;
}*/


/**
 \brief 获取颜色增强
 \attention \n
无

 \param[out] pu32ColorGainLevel 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetColorGain(HI_U32* pu32ColorGainLevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Num = 0;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_COLORGAIN, &u32Num);
    *pu32ColorGainLevel = u32Num;

    return s32Ret;
}

/**
 \brief 设置颜色增强
 \attention \n
无

 \param[in] u32ColorGainLevel 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetColorGain(HI_U32 u32ColorGainLevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Num = u32ColorGainLevel;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_COLORGAIN, &u32Num);

    return s32Ret;
}

/**
 \brief 获取肤色增强
 \attention \n
  无

 \param[out] penFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetFleshTone(HI_UNF_PQ_FLESHTONE_E* penFleshToneLevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_FLESHTONE, penFleshToneLevel);

    return s32Ret;
}

/**
 \brief 设置肤色增强
 \attention \n
  无

 \param[in] enFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetFleshTone( HI_UNF_PQ_FLESHTONE_E enFleshToneLevel)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_FLESHTONE, &enFleshToneLevel);

    return s32Ret;
}


/**
 \brief 设置颜色增强类型
 \attention \n
  无

 \param[in] enSixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorMode)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_COLOR_ENHANCE_MODE, &enColorMode);

    return s32Ret;
}


/**
 \brief 获取颜色增强类型
 \attention \n
  无

 \param[in] enSixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetColorEnhanceMode(HI_UNF_PQ_COLOR_SPEC_MODE_E* penColorMode)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }


    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_COLOR_ENHANCE_MODE, penColorMode);

    return s32Ret;
}

/**
 \brief 获取六基色类型
 \attention \n
  无

 \param[out] pu32SixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetSixBaseColor(HI_UNF_PQ_SIX_BASE_S* pstSixBaseColor)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SIXBASECOLOR, pstSixBaseColor);

    return s32Ret;
}

/**
 \brief 设置六基色类型
 \attention \n
  无

 \param[in] enSixBaseColor

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSixBaseColor(HI_PQ_SIX_BASE_COLOR_S* pstSixBaseColor)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SIXBASECOLOR, pstSixBaseColor);

    return s32Ret;
}

/**
 \brief 获取PQ模块开关
 \attention \n
  无

 \param[in] enFlags
 \param[in] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32* pu32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_MODULE_S stPQModule = {HI_PQ_MODULE_SHARPNESS, 0};

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }


    if (HI_UNF_PQ_MODULE_SHARPNESS == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SHARPNESS;
    }
    else if (HI_UNF_PQ_MODULE_DCI == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DCI;
    }
    else if (HI_UNF_PQ_MODULE_COLOR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_COLOR;
    }
    else if (HI_UNF_PQ_MODULE_SR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SR;
    }
    else
    {
        HI_ERR_PQ("PQ MODULE is error!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_MODULE, &stPQModule);
    *pu32OnOff = stPQModule.u32OnOff;

    return s32Ret;
}

/**
 \brief 设置PQ模块开关
 \attention \n
  无

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_MODULE_S stPQModule = {HI_PQ_MODULE_SHARPNESS, 0};

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    stPQModule.u32OnOff = u32OnOff;

    if (HI_UNF_PQ_MODULE_SHARPNESS == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SHARPNESS;
    }
    else if (HI_UNF_PQ_MODULE_DCI == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_DCI;
    }
    else if (HI_UNF_PQ_MODULE_COLOR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_COLOR;
    }
    else if (HI_UNF_PQ_MODULE_SR == enFlags)
    {
        stPQModule.enModule = HI_PQ_MODULE_SR;
    }
    else
    {
        HI_ERR_PQ("PQ MODULE is error!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_MODULE, &stPQModule);

    return s32Ret;
}

/**
 \brief 设置卖场模式开关
 \attention \n
无

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDemo( HI_UNF_PQ_DEMO_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_DEMO_S stDemo;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    if (1 == u32OnOff)
    {
        stDemo.bOnOff = HI_TRUE;
    }
    else
    {
        stDemo.bOnOff = HI_FALSE;
    }

    if (HI_UNF_PQ_DEMO_SHARPNESS == enFlags)
    {
        stDemo.enModule = HI_PQ_DEMO_SHARPNESS;
    }
    else if (HI_UNF_PQ_DEMO_DCI == enFlags)
    {
        stDemo.enModule = HI_PQ_DEMO_DCI;
    }
    else if (HI_UNF_PQ_DEMO_COLOR == enFlags)
    {
        stDemo.enModule = HI_PQ_DEMO_COLOR;
    }
    else if (HI_UNF_PQ_DEMO_SR == enFlags)
    {
        stDemo.enModule = HI_PQ_DEMO_SR;
    }
    else if (HI_UNF_PQ_DEMO_ALL == enFlags)
    {
        stDemo.enModule = HI_PQ_DEMO_ALL;
    }
    else
    {
        HI_ERR_PQ("PQ DEMO is error!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DEMO, &stDemo);
    return s32Ret;
}

/**
 \brief 设置PQ寄存器
 \attention \n
无

 \param[in] u32RegAddr
 \param[in] u32Data

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_WritePQRegister(HI_U32 u32RegAddr, HI_U32 u32Data)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_REGISTER_S stRegister = {0};

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    stRegister.u32RegAddr = u32RegAddr;
    stRegister.u32Value = u32Data;
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_REGISTER, &stRegister);
    return s32Ret;
}

/**
 \brief 获取PQ寄存器
 \attention \n
无

 \param[in] u32RegAddr
 \param[in] *pu32Value

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_ReadPQRegister(HI_U32 u32RegAddr, HI_U32* pu32Value)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_REGISTER_S stRegister = {0};

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    stRegister.u32RegAddr = u32RegAddr;
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_REGISTER, &stRegister);
    *pu32Value = stRegister.u32Value;
    return s32Ret;
}

/**
 \brief 获取ACM曲线
 \attention \n
  无

 \param[in] *pstGammaTable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetAcmTable( MPI_ACM_PARAM_S* pstColorTable)
{
    HI_S32 s32Ret = HI_FAILURE;

    /*HI_PQ_COLOR_S stColorLuma, stColorHue, stColorSat;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_ACM_LUMA, &stColorLuma);
    s32Ret |= ioctl(sg_s32PQFd, HIIOC_PQ_G_ACM_HUE, &stColorHue);
    s32Ret |= ioctl(sg_s32PQFd, HIIOC_PQ_G_ACM_SAT, &stColorSat);

    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    memcpy(pstColorTable->as16Luma, &stColorLuma, sizeof(HI_PQ_COLOR_S));
    memcpy(pstColorTable->as16Hue, &stColorHue, sizeof(HI_PQ_COLOR_S));
    memcpy(pstColorTable->as16Sat, &stColorSat, sizeof(HI_PQ_COLOR_S));*/
    return s32Ret;
}

/**
 \brief 设置ACM曲线
 \attention \n
  无

 \param[in] *pstGammaTable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetAcmTable(HI_U32 u32RegAddr, MPI_ACM_PARAM_S* pstColorTable)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_ACM_LUT_S* pstAcmLut = HI_NULL;

    if (HI_NULL == pstColorTable)
    {
        HI_ERR_PQ("%s:pstColorTable is Null poniter!\n", __FUNCTION__);
        return HI_FAILURE;
    }

    pstAcmLut = (HI_PQ_ACM_LUT_S*)malloc(sizeof(HI_PQ_ACM_LUT_S));
    if (HI_NULL == pstAcmLut)
    {
        HI_ERR_PQ("%s:pstAcmLut is Null poniter!\n", __FUNCTION__);
        return HI_FAILURE;
    }
    pstAcmLut->u32LutType = u32RegAddr;

    if (HI_FALSE == sg_bPQInitFlag)
    {
        HI_ERR_PQ("PQ not  init!");
        free(pstAcmLut);
        pstAcmLut = HI_NULL;
        return HI_FAILURE;
    }

    memcpy(pstAcmLut->as16Lut, pstColorTable->as16Luma, sizeof(pstAcmLut->as16Lut));
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_ACM_LUMA, pstAcmLut);

    memcpy(pstAcmLut->as16Lut, pstColorTable->as16Hue, sizeof(pstAcmLut->as16Lut));
    s32Ret |= ioctl(sg_s32PQFd, HIIOC_PQ_S_ACM_HUE, pstAcmLut);

    memcpy(pstAcmLut->as16Lut, pstColorTable->as16Sat, sizeof(pstAcmLut->as16Lut));
    s32Ret |= ioctl(sg_s32PQFd, HIIOC_PQ_S_ACM_SAT, pstAcmLut);

    free(pstAcmLut);
    pstAcmLut = HI_NULL;

    return s32Ret;
}

/**
 \brief 获取DCI曲线
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDciTable( HI_PQ_DCI_WGT_S* pstDCITable)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DCI, (HI_PQ_DCI_WGT_S*)pstDCITable);

    return s32Ret;
}

/**
 \brief 设置DCI曲线
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetDciTable( HI_PQ_DCI_WGT_S* pstDCITable)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DCI, (HI_PQ_DCI_WGT_S*)pstDCITable);

    return s32Ret;
}

/**
 \brief 获取DCI直方图
 \attention \n
  无

 \param[in] *pstDCIHistgram

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetHistgram( HI_PQ_DCI_HISTGRAM_S* pstDCIHistgram)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DCI_HIST, (HI_PQ_DCI_HISTGRAM_S*)pstDCIHistgram);

    return s32Ret;
}

/**
 \brief 获取DCI LEVEL
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_GetDciLevel(HI_U32* pu32DCIlevel)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_DCI_LEVEL, pu32DCIlevel);

    return s32Ret;
}

/**
 \brief 设置DCI LEVEL
 \attention \n
  无

 \param[in] *pstDCITable

 \retval ::HI_SUCCESS

 */


HI_S32 HI_MPI_PQ_SetDciLevel( HI_U32 u32DCIlevel)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_DCI_LEVEL, &u32DCIlevel);

    return s32Ret;
}

/**
 \brief 获取TNR的亮度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRLumaPixMean2Ratio( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_Y_PIXMEAN_2_RATIO, (HI_PQ_TNR_S*)pstTnrData);
    return s32Ret;
}
/**
 \brief 设置TNR的亮度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRLumaPixMean2Ratio( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_Y_PIXMEAN_2_RATIO, (HI_PQ_TNR_S*)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的色度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRChromPixMean2Ratio( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_C_PIXMEAN_2_RATIO, (HI_PQ_TNR_S*)pstTnrData);
    return s32Ret;
}
/**
 \brief 设置TNR的色度PixMean-to-Ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRChromPixMean2Ratio( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_C_PIXMEAN_2_RATIO, (HI_PQ_TNR_S*)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的亮度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRLumaMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_Y_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);
    return s32Ret;
}
/**
 \brief 设置TNR的亮度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRLumaMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_Y_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的色度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRChromMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_C_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);
    return s32Ret;
}
/**
 \brief 设置TNR的色度MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRChromMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_C_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的亮度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRLumaFinalMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_Y_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);
    return s32Ret;
}
/**
 \brief 设置TNR的亮度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRLumaFinalMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_Y_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取TNR的色度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetTNRChromFinalMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_TNR_C_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);
    return s32Ret;
}
/**
 \brief 设置TNR的色度FINAL MotionMapping曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetTNRChromFinalMotionMapping( HI_PQ_TNR_S* pstTnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_TNR_C_FINAL_MOTION_MAPPING, (HI_PQ_TNR_S*)pstTnrData);

    return s32Ret;
}

/**
 \brief 获取SNR的pixmean-ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetSNRPixmean2Ratio( HI_PQ_SNR_PIXMEAN_2_RATIO_S* pstSnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SNR_PIXMEAN_2_RATIO, (HI_PQ_SNR_PIXMEAN_2_RATIO_S*)pstSnrData);
    return s32Ret;
}
/**
 \brief 设置SNR的pixmean-ratio曲线
 \attention \n
  无

 \param[in] *pstTnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSNRPixmean2Ratio( HI_PQ_SNR_PIXMEAN_2_RATIO_S* pstSnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SNR_PIXMEAN_2_RATIO, (HI_PQ_SNR_PIXMEAN_2_RATIO_S*)pstSnrData);

    return s32Ret;
}

/**
 \brief 获取SNR的pixdiff-edgestr曲线
 \attention \n
  无

 \param[in] *pstSnrData

 \retval ::HI_SUCCESS

 */
HI_S32 HI_MPI_PQ_GetSNRPixdiff2Edgestr( HI_PQ_SNR_PIXDIFF_2_EDGESTR_S* pstSnrData)
{
    HI_S32 s32Ret = HI_FAILURE;
    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }
    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_G_SNR_PIXDIFF_2_EDGESTR, (HI_PQ_SNR_PIXDIFF_2_EDGESTR_S*)pstSnrData);
    return s32Ret;
}
/**
 \brief 设置SNR的pixdiff-edgestr曲线
 \attention \n
  无

 \param[in] *pstSnrData

 \retval ::HI_SUCCESS

 */

HI_S32 HI_MPI_PQ_SetSNRPixdiff2Edgestr( HI_PQ_SNR_PIXDIFF_2_EDGESTR_S* pstSnrData)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (sg_bPQInitFlag == HI_FALSE)
    {
        HI_ERR_PQ("PQ not  init!");
        return HI_FAILURE;
    }

    s32Ret = ioctl(sg_s32PQFd, HIIOC_PQ_S_SNR_PIXDIFF_2_EDGESTR, (HI_PQ_SNR_PIXDIFF_2_EDGESTR_S*)pstSnrData);

    return s32Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
