/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq.c
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/04/01
  Author      : p00203646
******************************************************************************/

#include <linux/pm.h>

#include "drv_pq.h"
#include "drv_pdm_ext.h"
#include "drv_pq_ext.h"
#include "hi_drv_dev.h"


PQ_PARAM_S*     g_pstPqParam = HI_NULL; /*PQ BIN */
MMZ_BUFFER_S    g_stPqBinBuf;
HI_BOOL         g_bLoadPqBin;

static HI_DRV_PQ_PARAM_S stPqParam;
static HI_U32 sg_u32SourceMode = SOURCE_MODE_NO;
static HI_U32 sg_u32OutputMode = OUTPUT_MODE_NO;
static HI_U32 sg_u32Zme2LThl = 4; /*Zme二级缩放门限值 */
static HI_BOOL sg_bFastBoot = HI_FALSE; 



static HI_S32 DRV_PQ_CheckChipName(HI_CHAR* pchChipName);
static HI_S32 DRV_PQ_GetFlashPqBin(PQ_PARAM_S* pstPqParam);
static HI_S32 DRV_PQ_GetPicSetting(HI_VOID);

HI_S32 DRV_PQ_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    if (PM_EVENT_FREEZE == state.event)
    {
        sg_bFastBoot = HI_TRUE;
    }
    else
    {
        sg_bFastBoot = HI_FALSE;
    }

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_Resume(PM_BASEDEV_S *pdev)
{
    HI_S32 s32Ret;

    if (HI_TRUE == sg_bFastBoot)
    {
        s32Ret = DRV_PQ_GetPicSetting();
        if (HI_SUCCESS != s32Ret)
        {
            HI_WARN_PQ("ERR: DRV_PQ_GetPicSetting failed!\n"); 
        }
    }

    return HI_SUCCESS;
}


PQ_EXPORT_FUNC_S   g_PqExportFuncs =
{
    .pfnPQ_GetPqParam             = DRV_PQ_GetPqParam,
    .pfnPQ_UpdateVpssPQ           = DRV_PQ_UpdateVpssPQ,
    .pfnPQ_UpdateVdpPQ            = DRV_PQ_UpdateVdpPQ,
    .pfnPQ_UpdateVdpCSC           = DRV_PQ_UpdateVdpCSC,
    .pfnPQ_UpdateDCIWin           = DRV_PQ_UpdateDCIWin,
    .pfnPQ_GetVpssScalerCoef      = DRV_PQ_GetVpssScalerCoef,
    .pfnPQ_GetScalerCoef          = DRV_PQ_GetScalerCoef,
    .pfnPQ_GetWbcScalerCoef       = DRV_PQ_GetWbcScalerCoef,
    .pfnPQ_SetZme                 = DRV_PQ_SetZme,
    .pfnPQ_SetVpssZme             = DRV_PQ_SetVpssZme,
    .pfnPQ_GetCSCCoef             = DRV_PQ_GetCSCCoef,
    .pfnPQ_Get8BitCSCCoef         = DRV_PQ_Get8BitCSCCoef,
    .pfnPQ_GetWbcInfo             = DRV_PQ_GetWbcInfo,
    .pfnPQ_SetAlgCalcCfg          = DRV_PQ_SetAlgCalcCfg,
    .pfnPQ_GGetTnrGlobalMotion    = DRV_PQ_GetTnrGlobalMotion,
    .pfnPQ_GetAdaptiveDBStrength  = DRV_PQ_GetAdaptiveDBStrength,
    .pfnPQ_PfmdDetect             = DRV_PQ_PfmdDetect,
    .pfnPQ_IfmdDect               = DRV_PQ_IfmdDect,
    .pfnPQ_GetDciHistgram         = DRV_PQ_GetDciHistgram,
    .pfnPQ_GetHDPictureSetting    = DRV_PQ_GetHDPictureSetting,
    .pfnPQ_GetSDPictureSetting    = DRV_PQ_GetSDPictureSetting,
    .pfnPQ_SetHDPictureSetting    = DRV_PQ_SetHDPictureSetting,
    .pfnPQ_SetSDPictureSetting    = DRV_PQ_SetSDPictureSetting
};

/**
 \brief 去初始化PQ模块;
 \attention \n
  无

 \param[in]

 \retval ::HI_SUCCESS

 */
HI_S32 HI_DRV_PQ_DeInit(HI_VOID)
{
    HI_S32 s32Ret;

    HI_DRV_MODULE_UnRegister(HI_ID_PQ);
    HI_DRV_MMZ_UnmapAndRelease((MMZ_BUFFER_S*)(&g_stPqBinBuf));

    s32Ret = PQ_MNG_DeinitSharpen();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit SHARPEN error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_DeInitDei();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit DEI error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_DeinitDNR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit DNR error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeinitSR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit SR error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitIfmd();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Ifmd error!\n");
        return HI_FAILURE;
    }

#if 0
    s32Ret = PQ_MNG_DeinitNr();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Nr error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_DeInitPFmd();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit PFmd error!\n");
        return HI_FAILURE;
    }
#endif
    s32Ret = PQ_MNG_DeInitUA();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit UA error!\n");
        return HI_FAILURE;
    }
    s32Ret = DRV_PQ_Comsumer_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Comsumer PQ error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_HAL_Deinit();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit PQ device error!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

/**
 \brief 初始化PQ模块;
 \attention \n
  无

 \param[in] pszPath: PQ Table文件路径, 如果pszPath参数为空指针, 会采用PQ SDK内部默认参数;

 \retval ::HI_SUCCESS

 */
HI_S32 HI_DRV_PQ_Init(HI_CHAR* pszPath)
{
    HI_S32 s32Ret;
    HI_S32 i;
    g_bLoadPqBin = HI_FALSE;
    g_pstPqParam = HI_NULL;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_PQ, PQ_NAME, (HI_VOID*)&g_PqExportFuncs);

    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_PQ("ERR: HI_DRV_MODULE_Register!\n");
        return s32Ret;
    }

    s32Ret = HI_DRV_MMZ_AllocAndMap("PQ_FLASH_BIN", HI_NULL, sizeof(PQ_PARAM_S), 0, (MMZ_BUFFER_S*)(&g_stPqBinBuf));
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_PQ("ERR: Pqdriver mmz memory failed!\n");
        g_bLoadPqBin = HI_FALSE;
        return s32Ret;
    }

    g_pstPqParam = (PQ_PARAM_S*)g_stPqBinBuf.u32StartVirAddr;
    HI_INFO_PQ("\ng_stPqBinBuf.u32StartVirAddr = 0x%x,g_stPqBinBuf.u32StartVirAddr = 0x%x\n", g_stPqBinBuf.u32StartPhyAddr, g_stPqBinBuf.u32StartVirAddr);

    s32Ret = DRV_PQ_GetFlashPqBin(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Load PQBin failed!\n");
        g_bLoadPqBin = HI_FALSE;
    }
    else
    {
        g_bLoadPqBin = HI_TRUE;
    }

    s32Ret = DRV_PQ_GetPicSetting();
    if (HI_SUCCESS != s32Ret)
    {
        HI_WARN_PQ("ERR: DRV_PQ_GetPicSetting failed!\n");
        stPqParam.stSDPictureSetting.u16Brightness = 128;
        stPqParam.stSDPictureSetting.u16Contrast   = 128;
        stPqParam.stSDPictureSetting.u16Hue        = 128;
        stPqParam.stSDPictureSetting.u16Saturation = 128;
        stPqParam.stHDPictureSetting.u16Brightness = 128;
        stPqParam.stHDPictureSetting.u16Contrast   = 128;
        stPqParam.stHDPictureSetting.u16Hue        = 128;
        stPqParam.stHDPictureSetting.u16Saturation = 128;
    }

    s32Ret = PQ_HAL_Init();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init PQ device error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitPQTable(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init PQ table failure!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitDei();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init DEI error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_InitSharpen(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init SHARPEN error!\n");
        return HI_FAILURE;
    }

    /* SD DR add from HiFoneB2 */
    s32Ret = PQ_MNG_InitDNR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init DNR error!\n");
        return HI_FAILURE;
    }


    s32Ret = PQ_MNG_InitIfmd(g_pstPqParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init Ifmd error!\n");
        return HI_FAILURE;
    }

#if 0
    s32Ret = PQ_MNG_InitPfmd();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init Pfmd error!\n");
        return HI_FAILURE;
    }
    s32Ret = PQ_MNG_InitNr();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init Nr error!\n");
        return HI_FAILURE;
    }
#endif

    s32Ret = PQ_MNG_InitSR();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init SR failure!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitUA();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init UA failure!\n");
        return HI_FAILURE;
    }

    s32Ret = DRV_PQ_Comsumer_Init(pszPath);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init Comsumer PQ  failure!\n");
        return HI_FAILURE;
    }

    /*Init Customer PQ setting*/
    stPqParam.stColorTemp.s16RedGain     = 128;
    stPqParam.stColorTemp.s16GreenGain   = 128;
    stPqParam.stColorTemp.s16BlueGain    = 128;
    stPqParam.stColorTemp.s16RedOffset   = 128;
    stPqParam.stColorTemp.s16GreenOffset = 128;
    stPqParam.stColorTemp.s16BlueOffset  = 128;

    stPqParam.stDciWin.u16HStar = 0;
    stPqParam.stDciWin.u16HEnd  = 0;
    stPqParam.stDciWin.u16VStar = 0;
    stPqParam.stDciWin.u16VEnd  = 0;

    stPqParam.u32NRLevel        = 128;
    stPqParam.u32Sharpness      = 128;
    stPqParam.u32DBLevel        = 128;
    stPqParam.u32DRLevel        = 128;
    stPqParam.u32ColorGainLevel = 128;
    stPqParam.u323dSharpen      = HI_FALSE;
    stPqParam.u32NrAuto         = HI_FALSE;
    stPqParam.u32DCILevelGain   = 50;
    stPqParam.stColorEnhance.enColorEnhanceType      = HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
    stPqParam.stColorEnhance.unColorGain.enColorMode = HI_PQ_COLOR_MODE_RECOMMEND;

    for (i = 0; i < HI_PQ_DEMO_BUTT; i++)
    {
        stPqParam.bDemoOnOff[i] = HI_FALSE;
    }

    for (i = 0; i < HI_PQ_MODULE_BUTT; i++)
    {
        stPqParam.bModuleOnOff[i] = HI_FALSE;
    }

    stPqParam.bModuleOnOff[HI_PQ_MODULE_SR] = HI_TRUE;

    return HI_SUCCESS;
}

/**
 \brief 去初始化客户PQ模块;
 \attention \n
  无

 \param[in]

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Comsumer_DeInit(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = PQ_MNG_DeinitDCI();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit DCI error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitColor();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit Color error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_DeInitPQTable();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Deinit PQ table error!\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

/**
 \brief 初始化客户PQ模块;
 \attention \n
  无

 \param[in] pszPath: PQ Table文件路径, 如果pszPath参数为空指针, 会采用PQ SDK内部默认参数;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Comsumer_Init(HI_CHAR* pszPath)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = PQ_MNG_InitDCI(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init DCI error!\n");
        return HI_FAILURE;
    }

    s32Ret = PQ_MNG_InitColor(g_pstPqParam, !g_bLoadPqBin);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Init Color failure!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


/**
 \brief 获取标清亮度
 \attention \n
无

 \param[out] pu32Brightness 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDBrightness(HI_U32* pu32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Brightness);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);

    return HI_SUCCESS;
}

/**
 \brief 设置标清亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDBrightness(HI_U32 u32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Brightness > 255)
    {
        HI_ERR_PQ("%d:u32Brightness is over range!\n", u32Brightness);
        return HI_FAILURE;
    }

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Brightness level %d\n", u32Brightness);
    stPqParam.stSDPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);
    return HI_SUCCESS;
}

/**
 \brief 获取标清对比度
 \attention \n
无

 \param[out] pu32Contrast 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDContrast(HI_U32* pu32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Contrast);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);

    return HI_SUCCESS;
}

/**
 \brief 设置标清对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDContrast(HI_U32 u32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Contrast > 255)
    {
        HI_ERR_PQ("%d:u32Contrast is over range!\n", u32Contrast);
        return HI_FAILURE;
    }

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Contrast level %d\n", u32Contrast);
    stPqParam.stSDPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    return HI_SUCCESS;
}

/**
 \brief 获取标清色调
 \attention \n
无

 \param[out] pu32Hue  色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDHue(HI_U32* pu32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Hue);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);

    return HI_SUCCESS;
}

/**
 \brief 设置标清色调
 \attention \n
无

 \param[in] u32Hue   色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDHue(HI_U32 u32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Hue > 255)
    {
        HI_ERR_PQ("%d:u32Hue is over range!\n", u32Hue);
        return HI_FAILURE;
    }

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Hue level %d\n", u32Hue);
    stPqParam.stSDPictureSetting.u16Hue = LEVEL2NUM(u32Hue);
    return HI_SUCCESS;
}

/**
 \brief 获取标清饱和度
 \attention \n
无

 \param[out] pu32Saturation  饱和度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDSaturation(HI_U32* pu32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Saturation);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    return HI_SUCCESS;
}

/**
 \brief 设置标清饱和度
 \attention \n
无

 \param[in] u32Saturation 饱和度,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDSaturation(HI_U32 u32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Saturation > 255)
    {
        HI_ERR_PQ("%d:u32Saturation is over range!\n", u32Saturation);
        return HI_FAILURE;
    }

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Saturation level %d\n", u32Saturation);
    stPqParam.stSDPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);
    return HI_SUCCESS;
}

/**
 \brief 获取高清亮度
 \attention \n
无

 \param[out] pu32Brightness 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDBrightness(HI_U32* pu32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Brightness);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);

    return HI_SUCCESS;
}

/**
 \brief 设置高清亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDBrightness(HI_U32 u32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Brightness > 255)
    {
        HI_ERR_PQ("%d:u32Brightness is over range!\n", u32Brightness);
        return HI_FAILURE;
    }

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Brightness level %d\n", u32Brightness);
    stPqParam.stHDPictureSetting.u16Brightness = LEVEL2NUM(u32Brightness);
    return HI_SUCCESS;
}

/**
 \brief 获取高清对比度
 \attention \n
无

 \param[out] pu32Contrast 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDContrast(HI_U32* pu32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Contrast);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Contrast = NUM2LEVEL(stPictureSetting.u16Contrast);

    return HI_SUCCESS;
}

/**
 \brief 设置高清对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDContrast(HI_U32 u32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Contrast > 255)
    {
        HI_ERR_PQ("%d:u32Contrast is over range!\n", u32Contrast);
        return HI_FAILURE;
    }

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Contrast level %d\n", u32Contrast);
    stPqParam.stHDPictureSetting.u16Contrast = LEVEL2NUM(u32Contrast);
    return HI_SUCCESS;
}


/**
 \brief 获取高清色调
 \attention \n
无

 \param[out] pu32Hue  色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDHue(HI_U32* pu32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Hue);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Hue = NUM2LEVEL(stPictureSetting.u16Hue);

    return HI_SUCCESS;
}


/**
 \brief 设置高清色调
 \attention \n
无

 \param[in] u32Hue   色调, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDHue(HI_U32 u32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Hue > 255)
    {
        HI_ERR_PQ("%d:u32Hue is over range!\n", u32Hue);
        return HI_FAILURE;
    }

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Hue = LEVEL2NUM(u32Hue);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Hue level %d\n", u32Hue);
    stPqParam.stHDPictureSetting.u16Hue = LEVEL2NUM(u32Hue);
    return HI_SUCCESS;
}


/**
 \brief 获取高清饱和度
 \attention \n
无

 \param[out] pu32Saturation  饱和度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDSaturation(HI_U32* pu32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pu32Saturation);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    *pu32Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    return HI_SUCCESS;
}


/**
 \brief 设置高清饱和度
 \attention \n
无

 \param[in] u32Saturation 饱和度,有效范围: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDSaturation(HI_U32 u32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (u32Saturation > 255)
    {
        HI_ERR_PQ("%d:u32Saturation is over range!\n", u32Saturation);
        return HI_FAILURE;
    }

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Saturation level %d\n", u32Saturation);
    stPqParam.stHDPictureSetting.u16Saturation = LEVEL2NUM(u32Saturation);
    return HI_SUCCESS;
}


/**
 \brief 获取高清亮度/对比度/色调/饱和度/色温
 \attention \n
无

 \param[out] u32Hue   亮度/对比度/色调/饱和度/色温

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetHDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pstPictureSetting);

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    pstPictureSetting->u16Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
    pstPictureSetting->u16Contrast   = NUM2LEVEL(stPictureSetting.u16Contrast);
    pstPictureSetting->u16Hue        = NUM2LEVEL(stPictureSetting.u16Hue);
    pstPictureSetting->u16Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    pstPictureSetting->s16RedGain     = NUM2LEVEL(stColorTemp.s16BlueGain);
    pstPictureSetting->s16GreenGain   = NUM2LEVEL(stColorTemp.s16GreenGain);
    pstPictureSetting->s16BlueGain    = NUM2LEVEL(stColorTemp.s16BlueGain);
    pstPictureSetting->s16RedOffset   = NUM2LEVEL(stColorTemp.s16RedOffset);
    pstPictureSetting->s16GreenOffset = NUM2LEVEL(stColorTemp.s16GreenOffset);
    pstPictureSetting->s16BlueOffset  = NUM2LEVEL(stColorTemp.s16BlueOffset);

    return HI_SUCCESS;
}


/**
 \brief 获取标清亮度/对比度/色调/饱和度/色温
 \attention \n
无

 \param[out] u32Hue   亮度/对比度/色调/饱和度/色温

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetSDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_CHECK_NULL_PTR(pstPictureSetting);

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    pstPictureSetting->u16Brightness = NUM2LEVEL(stPictureSetting.u16Brightness);
    pstPictureSetting->u16Contrast   = NUM2LEVEL(stPictureSetting.u16Contrast);
    pstPictureSetting->u16Hue        = NUM2LEVEL(stPictureSetting.u16Hue);
    pstPictureSetting->u16Saturation = NUM2LEVEL(stPictureSetting.u16Saturation);

    pstPictureSetting->s16RedGain     = NUM2LEVEL(stColorTemp.s16BlueGain);
    pstPictureSetting->s16GreenGain   = NUM2LEVEL(stColorTemp.s16GreenGain);
    pstPictureSetting->s16BlueGain    = NUM2LEVEL(stColorTemp.s16BlueGain);
    pstPictureSetting->s16RedOffset   = NUM2LEVEL(stColorTemp.s16RedOffset);
    pstPictureSetting->s16GreenOffset = NUM2LEVEL(stColorTemp.s16GreenOffset);
    pstPictureSetting->s16BlueOffset  = NUM2LEVEL(stColorTemp.s16BlueOffset);

    return HI_SUCCESS;
}


/**
 \brief 设置高清亮度/对比度/色调/饱和度/色温
 \attention \n
无

 \param[in] u32Hue   亮度/对比度/色调/饱和度/色温;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp = {0};

    PQ_CHECK_NULL_PTR(pstPictureSetting);

    stPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);

    /*
    stColorTemp.s16RedGain     = LEVEL2NUM(pstPictureSetting->s16RedGain);
    stColorTemp.s16GreenGain   = LEVEL2NUM(pstPictureSetting->s16GreenGain);
    stColorTemp.s16BlueGain    = LEVEL2NUM(pstPictureSetting->s16BlueGain);
    stColorTemp.s16RedOffset   = LEVEL2NUM(pstPictureSetting->s16RedOffset);
    stColorTemp.s16GreenOffset = LEVEL2NUM(pstPictureSetting->s16GreenOffset);
    stColorTemp.s16BlueOffset  = LEVEL2NUM(pstPictureSetting->s16BlueOffset);
    */

    PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n", \
                pstPictureSetting->u16Brightness, \
                pstPictureSetting->u16Contrast, \
                pstPictureSetting->u16Hue, \
                pstPictureSetting->u16Saturation);

    stPqParam.stHDPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPqParam.stHDPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPqParam.stHDPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPqParam.stHDPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);
    return HI_SUCCESS;
}


/**
 \brief 设置标清亮度/对比度/色调/饱和度/色温
 \attention \n
无

 \param[in] u32Hue   亮度/对比度/色调/饱和度/色温;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp = {0};

    PQ_CHECK_NULL_PTR(pstPictureSetting);

    stPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);

    /*
    stColorTemp.s16RedGain     = LEVEL2NUM(pstPictureSetting->s16RedGain);
    stColorTemp.s16GreenGain   = LEVEL2NUM(pstPictureSetting->s16GreenGain);
    stColorTemp.s16BlueGain    = LEVEL2NUM(pstPictureSetting->s16BlueGain);
    stColorTemp.s16RedOffset   = LEVEL2NUM(pstPictureSetting->s16RedOffset);
    stColorTemp.s16GreenOffset = LEVEL2NUM(pstPictureSetting->s16GreenOffset);
    stColorTemp.s16BlueOffset  = LEVEL2NUM(pstPictureSetting->s16BlueOffset);
    */

    PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    HI_DEBUG_PQ("Set Brightness:%d, Contrast:%d, Hue:%d, Saturation:%d\n", \
                pstPictureSetting->u16Brightness, \
                pstPictureSetting->u16Contrast, \
                pstPictureSetting->u16Hue, \
                pstPictureSetting->u16Saturation);

    stPqParam.stSDPictureSetting.u16Brightness = LEVEL2NUM(pstPictureSetting->u16Brightness);
    stPqParam.stSDPictureSetting.u16Contrast   = LEVEL2NUM(pstPictureSetting->u16Contrast);
    stPqParam.stSDPictureSetting.u16Hue        = LEVEL2NUM(pstPictureSetting->u16Hue);
    stPqParam.stSDPictureSetting.u16Saturation = LEVEL2NUM(pstPictureSetting->u16Saturation);
    return HI_SUCCESS;
}

#if 0
/**
 \brief 刷新DB API 全局变量
 \attention \n
无

 \param[in]  HI_PQ_WBC_INFO_S* pstWbcInfo

 \retval ::HI_SUCCESS

 */
static HI_S32 DRV_PQ_DBCfgRefresh(HI_U32 u32HandleNo, HI_U32 u32Height, HI_U32 u32Width, HI_U32 u32FRate)
{
    //API Init 场景切换刷新DB全局变量值，这个不是每帧都刷新，运算值会存储在全局变量中
    PQ_MNG_DB_API_Init(u32HandleNo, u32Height, u32Width, u32FRate);

    return HI_SUCCESS;
}
#endif

/**
 \brief 获取清晰度
 \attention \n
无

 \param[out] pu32Sharpness  清晰度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSharpness(HI_U32* pu32Sharpness)
{
    *pu32Sharpness = NUM2LEVEL(stPqParam.u32Sharpness);
    return HI_SUCCESS;
}

/**
 \brief 设置清晰度
 \attention \n
无

 \param[in] u32Sharpness, 清晰度, 有效范围: 0~100;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSharpness(HI_U32 u32Sharpness)
{
    HI_S32 s32Ret;
    HI_U32 u32Num = LEVEL2NUM(u32Sharpness);//0~100 trans to 0~255

    s32Ret = PQ_MNG_SetSharpenStr(u32Num, sg_u32SourceMode, sg_u32OutputMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("error in setting sharpness strength\n");
        return s32Ret;
    }

    stPqParam.u32Sharpness = u32Num;
    HI_DEBUG_PQ("Set sharpen level %d\n", u32Sharpness);

    return HI_SUCCESS;
}



/**
 \brief 获取色温参数
 \attention \n
无

 \param[in] pstColorTemp: 色温属性

 \retval::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetColorTemp(HI_PQ_COLOR_TEMP_S* pstColorTemp)
{
    return HI_SUCCESS;
}


/**
 \brief 设置色温参数
 \attention \n
无

 \param[out] pstColorTemp: 色温属性

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetColorTemp(HI_PQ_COLOR_TEMP_S* pstColorTemp)
{
    return HI_SUCCESS;
}


/**
 \brief 获取颜色增强
 \attention \n
无

 \param[out] pu32ColorGainLevel

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetColorEhance(HI_U32* pu32ColorGainLevel)
{
    HI_S32 s32Ret;
    PQ_CHECK_NULL_PTR(pu32ColorGainLevel);

    s32Ret = PQ_MNG_GetColorGainLevel(pu32ColorGainLevel);
    *pu32ColorGainLevel = NUM2LEVEL(*pu32ColorGainLevel);

    return s32Ret;
}


/**
 \brief 设置颜色增强
 \attention \n
无

 \param[in] u32ColorGainLevel

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetColorEhance(HI_U32 u32ColorGainLevel)
{
    HI_U32 u32Num = LEVEL2NUM(u32ColorGainLevel);

    stPqParam.u32ColorGainLevel = u32Num;
    HI_DEBUG_PQ("Set ColorGainLevel level %d\n", u32ColorGainLevel);
    return PQ_MNG_SetColorGainLevel(u32Num);
}

/**
 \brief 获取肤色增强
 \attention \n
  无

 \param[out] pu32FleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetFleshToneLevel(HI_U32* pu32FleshToneLevel)
{
    PQ_CHECK_NULL_PTR(pu32FleshToneLevel);
    return PQ_MNG_GetFleshToneLevel(pu32FleshToneLevel);
}

/**
 \brief 设置肤色增强
 \attention \n
  无

 \param[in] enFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetFleshToneLevel(HI_PQ_FLESHTONE_E enFleshToneLevel)
{
    stPqParam.stColorEnhance.enColorEnhanceType = HI_PQ_COLOR_ENHANCE_FLESHTONE;
    stPqParam.stColorEnhance.unColorGain.enFleshtone = enFleshToneLevel;

    HI_DEBUG_PQ("Set FleshTone level %d\n", enFleshToneLevel);
    return PQ_MNG_SetFleshToneLevel(enFleshToneLevel, sg_u32SourceMode);
}

/**
 \brief 六基色控制设置
 \attention \n
  无

 \param[in] enSixColorType;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSixBaseColorLevel(HI_PQ_SIX_BASE_S* pstSixBaseColorOffset)
{
    PQ_CHECK_NULL_PTR(pstSixBaseColorOffset);

    stPqParam.stColorEnhance.enColorEnhanceType = HI_PQ_COLOR_ENHANCE_SIX_BASE;
    stPqParam.stColorEnhance.unColorGain.stSixBase = *pstSixBaseColorOffset;

    HI_DEBUG_PQ("Set SixBaseColor u32Red = %d, u32Green = %d, u32Blue = %d, u32Cyan = %d, u32Magenta = %d, u32Yellow = %d\n", \
                pstSixBaseColorOffset->u32Red, \
                pstSixBaseColorOffset->u32Green, \
                pstSixBaseColorOffset->u32Blue, \
                pstSixBaseColorOffset->u32Cyan, \
                pstSixBaseColorOffset->u32Magenta, \
                pstSixBaseColorOffset->u32Yellow);
    return PQ_MNG_SetSixBaseColorLevel((SIX_BASE_COLOR_OFFSET_S*)pstSixBaseColorOffset, sg_u32SourceMode);
}

/**
 \brief 颜色增强模式设置
 \attention \n
  无

 \param[in] enColorSpecMode 0-RECOMMEND;1-BLUE;2-GREEN;3-BG;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode)
{
    stPqParam.stColorEnhance.enColorEnhanceType = HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE;
    stPqParam.stColorEnhance.unColorGain.enColorMode = enColorSpecMode;

    HI_DEBUG_PQ("Set ColorEnhanceMode = %d\n", enColorSpecMode);
    return PQ_MNG_SetColorEnhanceMode(enColorSpecMode, sg_u32SourceMode);
}


/**
 \brief 设置DCI强度增益等级
 \attention \n
无

 \param[in] u32DCILevelGain;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDCILevelGain(HI_U32 u32DCILevelGain)
{
    stPqParam.u32DCILevelGain = u32DCILevelGain;
    HI_DEBUG_PQ("Set DCILevelGain level %d\n", u32DCILevelGain);
    return PQ_MNG_SetDCILevelGain(u32DCILevelGain, sg_u32SourceMode);
}


/**
 \brief 设置DCI配置曲线
 \attention \n
无

 \param[in] pstDciCoef;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetDCIWgtLut(DCI_WGT_S* pstDciCoef)
{
    g_pstPqParam->stPQCoef.stDciCoef.stPqDciLut = *(PQ_DCI_LUT_S*)pstDciCoef;
    return PQ_HAL_SetDCIWgtLut(pstDciCoef);
}


/**
 \brief 设置卖场模式开关
 \attention \n
无

 \param[in] enFlags
 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetDemoMode(HI_PQ_DEMO_E enFlags, HI_BOOL bOnOff)
{
    SR_DEMO_E enDemo;
    if (enFlags == HI_PQ_DEMO_DBDR)
    {
        /* From HiFoneB2, It Exist SD DR, So in HiFoneB2, Enable HDDR、SDDR and HDDB together */
        //PQ_MNG_EnableDBDemo(bOnOff);
        //PQ_MNG_EnableDRDemo(bOnOff);
        //PQ_MNG_EnableSDDRDemo(bOnOff);

        HI_DEBUG_PQ("DBDR demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_COLOR)
    {
        PQ_MNG_ColorDemoMode(bOnOff);
        HI_DEBUG_PQ("COLOR demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_NR)
    {
        //PQ_MNG_EnableNrDemo(bOnOff);
        //HI_DEBUG_PQ("NR demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_SHARPNESS)
    {
        PQ_MNG_EnableSharpenDemo(bOnOff);
        HI_DEBUG_PQ("Sharpeness demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_DCI)
    {
        PQ_MNG_DCIDemoMode(bOnOff);
        HI_DEBUG_PQ("DCI demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_SR)
    {
        if ( stPqParam.bModuleOnOff[HI_PQ_MODULE_SR] == HI_TRUE )
        {
            enDemo = (bOnOff == HI_TRUE) ? SR_ENABLE_R : SR_ENABLE_A;
        }
        else
        {
            enDemo = SR_DISABLE;
        }
        PQ_MNG_EnableSRDemo(enDemo);
        HI_DEBUG_PQ("SR demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_WCG)
    {
        //PQ_MNG_EnableWCGDemo(bOnOff);
        //HI_DEBUG_PQ("WCG demo %s\n", bOnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_DEMO_ALL)
    {
        //PQ_MNG_EnableNrDemo(bOnOff);
        //PQ_MNG_EnableWCGDemo(bOnOff);
        //PQ_MNG_EnableDBDemo(bOnOff);
        /* can set DR Demo in 98M, But not emerge API */
        //PQ_MNG_EnableDRDemo(bOnOff);
        /* From HiFoneB2, It Exist SD DR, So in HiFoneB2, Enable HDDR、SDDR and HDDB together */
        //PQ_MNG_EnableSDDRDemo(bOnOff);

        if ( stPqParam.bModuleOnOff[HI_PQ_MODULE_SR] == HI_TRUE )
        {
            enDemo = (bOnOff == HI_TRUE) ? SR_ENABLE_R : SR_ENABLE_A;
        }
        else
        {
            enDemo = SR_DISABLE;
        }
        PQ_MNG_EnableSRDemo(enDemo);
        PQ_MNG_ColorDemoMode(bOnOff);
        PQ_MNG_EnableSharpenDemo(bOnOff);
        PQ_MNG_DCIDemoMode(bOnOff);

        stPqParam.bDemoOnOff[HI_PQ_DEMO_SR]        = bOnOff;
        stPqParam.bDemoOnOff[HI_PQ_DEMO_SHARPNESS] = bOnOff;
        stPqParam.bDemoOnOff[HI_PQ_DEMO_DCI]       = bOnOff;
        stPqParam.bDemoOnOff[HI_PQ_DEMO_COLOR]     = bOnOff;

        HI_DEBUG_PQ("ALL demo %s\n", bOnOff ? "on" : "off");
    }
    stPqParam.bDemoOnOff[enFlags] = bOnOff;
    return HI_SUCCESS;
}


/**
 \brief 获取PQ模块开关状态
 \attention \n
  无

 \param[in] enFlags
 \param[out] *pu32OnOff

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetPQModule(HI_PQ_MODULE_E enFlags, HI_U32* pu32OnOff)
{
    if (enFlags == HI_PQ_MODULE_DCI)
    {
        PQ_MNG_GetDCIEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_COLOR)
    {
        PQ_HAL_GetACMEnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_TNR)
    {
        //PQ_MNG_GetTNREnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_SNR)
    {
        //PQ_MNG_GetSNREnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_DB)
    {
        PQ_MNG_GetDBEnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_DR)
    {
        PQ_MNG_GetDREnableFlag(pu32OnOff);
        //From HiFoneB2, It Exist SD DR, So in HiFoneB2, This Enable of DR is HD DR
        //PQ_MNG_GetSDDREnableFlag(pu32OnOff)
    }
    else if (enFlags == HI_PQ_MODULE_HSHARPNESS)
    {
        //PQ_MNG_GetHSharpenEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_SHARPNESS)
    {
        //PQ_HAL_GetSharpEnable(0, (HI_U8*)pu32OnOff);
        PQ_MNG_GetSharpenEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_CCCL)
    {
        //PQ_MNG_EnableCCCL(u32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_GAMMA)
    {
        //PQ_HAL_GetGammaEnableFlag(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_DBC)
    {
        //PQ_HAL_GetDimEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_BLUE_STRETCH)
    {
        //PQ_MNG_GetBlueStretchEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_ES)
    {
        //PQ_MNG_GetEdgeSmoothEnable(pu32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_SR)
    {
        PQ_MNG_GetSRDemo(pu32OnOff);
        //*pu32OnOff = stPqParam.bModuleOnOff[HI_PQ_MODULE_SR];
    }
    else if (enFlags == HI_PQ_MODULE_WCG)
    {
        //PQ_MNG_EnableWCG(u32OnOff);
    }

    return HI_SUCCESS;
}


/**
 \brief 设置PQ模块开关
 \attention \n
  无

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetPQModule(HI_PQ_MODULE_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;
    SR_DEMO_E enDemo;

    if (enFlags == HI_PQ_MODULE_DCI)
    {
        s32Ret = PQ_MNG_EnableDCI(u32OnOff);
        HI_DEBUG_PQ("Set DCI  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_COLOR)
    {
        s32Ret = PQ_MNG_EnableColorEnhance(u32OnOff);
        HI_DEBUG_PQ("Set COLOR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_TNR)
    {
        //PQ_MNG_EnableTNr(u32OnOff);
        //HI_DEBUG_PQ("Set TNR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_SNR)
    {
        //PQ_MNG_EnableSNr(u32OnOff);
        //HI_DEBUG_PQ("Set SNR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DB)
    {
        /* VPSS CTRL DB
        * From HiFoneB2, It Exist SD DR, So Open HD and SD DR together,
        * It Does not Exist SD DB, But Keep the API of DB and DR stay the same
        */
        PQ_MNG_EnableDB(u32OnOff);
        //PQ_MNG_EnableSDDB(u32OnOff);
        HI_DEBUG_PQ("Set DB  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DR)
    {
        /* VPSS CTRL DR and SD DR */ /* SD DR要不要一个单独的开关 */
        /*From HiFoneB2, It Exist SD DR, So Open HD and SD DR together*/
        PQ_MNG_EnableDR(u32OnOff);
        //PQ_MNG_EnableSDDR(u32OnOff);
        HI_DEBUG_PQ("Set DR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_HSHARPNESS)
    {
        //PQ_MNG_EnableHSharpen(u32OnOff);
        //HI_DEBUG_PQ("Set HSHARPEN  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_SHARPNESS)
    {
        /* include Sharpen and HSharpen in VPSS */
        s32Ret = PQ_MNG_EnableSharpen(u32OnOff);
        HI_DEBUG_PQ("Set SHARPEN  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_CCCL)
    {
        //PQ_MNG_EnableCCCL(u32OnOff);
        //HI_DEBUG_PQ("Set CCCL  %s\n",u32OnOff?"on":"off");
    }
    else if (enFlags == HI_PQ_MODULE_GAMMA)
    {
        //PQ_MNG_EnableGamma(u32OnOff);
        //HI_DEBUG_PQ("Set GAMMA  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_DBC)
    {
        //PQ_MNG_Dim_SetDynamicBackLight(u32OnOff);
        //HI_DEBUG_PQ("Set DBC  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_BLUE_STRETCH)
    {
        //PQ_MNG_EnableBlueStretch(u32OnOff);
    }
    else if (enFlags == HI_PQ_MODULE_ES)
    {
        //PQ_MNG_EnableEdgeSmooth(u32OnOff);
        //HI_DEBUG_PQ("Set ES  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_SR)
    {
        /* VDP CTRL SR */
        //s32Ret = PQ_MNG_EnableSR(u32OnOff);
        //HI_INFO_PQ("Set SR  %s\n", u32OnOff ? "on" : "off");

        if ( stPqParam.bDemoOnOff[HI_PQ_DEMO_SR] == HI_TRUE )
        {
            enDemo = (u32OnOff == HI_TRUE) ? SR_ENABLE_R : SR_DISABLE;
        }
        else
        {
            enDemo = (u32OnOff == HI_TRUE) ? SR_ENABLE_A : SR_DISABLE;
        }
        s32Ret = PQ_MNG_EnableSRDemo(enDemo);
        HI_DEBUG_PQ("Set SR  %s\n", u32OnOff ? "on" : "off");
    }
    else if (enFlags == HI_PQ_MODULE_WCG)
    {
        //PQ_MNG_EnableWCG(u32OnOff);
        //HI_DEBUG_PQ("Set WCG  %s\n",u32OnOff?"on":"off");
    }

    stPqParam.bModuleOnOff[enFlags] = u32OnOff;
    return s32Ret;
}

/**
 \brief Timming变化后进行VPSS PQ参数更新
 \attention \n
无

 \param[in]  *u32HandleNo:   VPSS通道号
 \param[in]  *pstTimingInfo: Timming Info
 \param[in]  *pstVPSSReg:    VPSS 虚拟寄存器地址
 \param[out] *pstPQModule:   PQ传给驱动的开关参数

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVpssPQ(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S* pstTimingInfo, PQ_VPSS_CFG_REG_S* pstVPSSReg, PQ_VPSS_WBC_REG_S* pstWbcReg, HI_PQ_VPSS_MODULE_S* pstPQModule)
{
    HI_S32 s32Ret;

    PQ_HAL_UpdateVpssReg(u32HandleNo, pstVPSSReg, pstWbcReg);
    PQ_HAL_UpdatePQModule((PQ_HAL_MODULE_S*)pstPQModule);
    if (pstVPSSReg != NULL && pstTimingInfo != NULL)
    {
        /* Load VPSS Physical Register */
        sg_u32SourceMode = PQ_MNG_CheckSourceMode(pstTimingInfo->u32Width, pstTimingInfo->u32Height);
        s32Ret = PQ_MNG_LoadPhyList(REG_TYPE_VPSS, sg_u32SourceMode, sg_u32OutputMode, PQ_MODULE_ALL);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_LoadPhyList VDP failed!\n");
            return s32Ret;
        }

        PQ_MNG_IFMD_SofewareParaInitByHandleNo(u32HandleNo);
        //PQ_MNG_UpdataVpssPQ(u32HandleNo, pstTimingInfo);
        //PQ_MNG_IFMD_SofewareParaInitByHandleNo(u32HandleNo);
        //PQ_MNG_PFMD_SoftwareParaInitByHandleNo(u32HandleNo);

        /* reset vpss customer pq setting */
        //s32Ret = DRV_PQ_SetNRLevel(stPqParam.u32NRLevel);
        //s32Ret |= DRV_PQ_SetDeBlocking(stPqParam.u32DBLevel);
        //s32Ret |= DRV_PQ_SetDeRinging(stPqParam.u32DRLevel);

        /* Set Sharp include HSharpen and Sharpen*/
        PQ_MNG_EnableSharpen(stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS]);
        PQ_MNG_EnableSharpenDemo(stPqParam.bDemoOnOff[HI_PQ_DEMO_SHARPNESS]);
        s32Ret = DRV_PQ_SetSharpness(NUM2LEVEL(stPqParam.u32Sharpness));
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("DRV_PQ_SetSharpness failed!\n");
            return s32Ret;
        }
#if defined(CHIP_TYPE_hi3798cv200_a)
        /* Refresh DB API CFG */
        s32Ret = PQ_MNG_DBCfgRefresh(u32HandleNo, pstTimingInfo->u32Height, pstTimingInfo->u32Width, pstTimingInfo->u32FrameRate);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_DBCfgRefresh failed!\n");
            return s32Ret;
        }
#endif
    }

    return HI_SUCCESS;
}

/**
 \brief Timming变化后进行VDP PQ参数更新
 \attention \n
无

 \param[in] pstTimingInfo: Timming Info
 \param[in] *pstVDPReg:VDP 虚拟寄存器地址

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVdpPQ(HI_U32 u32DisplayId, HI_VDP_PQ_INFO_S* pstTimingInfo, S_VDP_REGS_TYPE* pstVDPReg)
{
    HI_S32 s32Ret;

    /* Update VDP Register point */
    PQ_HAL_UpdateVdpReg(pstVDPReg);

    if (pstVDPReg != NULL && pstTimingInfo != NULL)
    {
        /* Load VDP Physical Register */
        sg_u32SourceMode = PQ_MNG_CheckSourceMode(pstTimingInfo->u32Width, pstTimingInfo->u32Height);
        sg_u32OutputMode = PQ_MNG_CheckOutputMode(pstTimingInfo->bSRState);

        s32Ret = PQ_MNG_LoadPhyList(REG_TYPE_VDP, sg_u32SourceMode, sg_u32OutputMode, PQ_MODULE_ALL);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_LoadPhyList VDP failed!\n");
            return s32Ret;
        }

        //PQ_MNG_UpdataVdpPQ(pstTimingInfo);
        //PQ_MNG_UpdateSRSpMode(pstTimingInfo->u32Width, pstTimingInfo->u32Height);

        /*************************************************************************
             *   reset VDP customer pq setting
             **************************************************************************/
        /* Set Picture Setting*/
        s32Ret  = PQ_MNG_SetSDPictureSetting(&stPqParam.stSDPictureSetting, &stPqParam.stColorTemp);
        s32Ret |= PQ_MNG_SetHDPictureSetting(&stPqParam.stHDPictureSetting, &stPqParam.stColorTemp);
        if (s32Ret != HI_SUCCESS)
        {
            HI_ERR_PQ("set VDP customer pq setting error!\n");
        }

        /* Set Module */
        DRV_PQ_SetPQModule(HI_PQ_MODULE_SR, stPqParam.bModuleOnOff[HI_PQ_MODULE_SR]);
        PQ_MNG_EnableDCI(stPqParam.bModuleOnOff[HI_PQ_MODULE_DCI]);
        PQ_MNG_EnableColorEnhance(stPqParam.bModuleOnOff[HI_PQ_MODULE_COLOR]);

        /* Set Demo */
        DRV_PQ_SetDemoMode(HI_PQ_DEMO_SR, stPqParam.bDemoOnOff[HI_PQ_DEMO_SR]);
        PQ_MNG_DCIDemoMode(stPqParam.bDemoOnOff[HI_PQ_DEMO_DCI]);
        PQ_MNG_ColorDemoMode(stPqParam.bDemoOnOff[HI_PQ_DEMO_COLOR]);

        /* Set DCI Level */
        s32Ret = PQ_MNG_SetDCILevelGain(stPqParam.u32DCILevelGain, sg_u32SourceMode);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("PQ_MNG_SetDCILevelGain failed!\n");
            return s32Ret;
        }

        /* Set Color Enhance */
        if (HI_PQ_COLOR_ENHANCE_FLESHTONE == stPqParam.stColorEnhance.enColorEnhanceType)
        {
            s32Ret = PQ_MNG_SetFleshToneLevel(stPqParam.stColorEnhance.unColorGain.enFleshtone, sg_u32SourceMode);
        }
        else if (HI_PQ_COLOR_ENHANCE_SIX_BASE == stPqParam.stColorEnhance.enColorEnhanceType)
        {
            HI_PQ_SIX_BASE_S* pstPQSixBase = &(stPqParam.stColorEnhance.unColorGain.stSixBase);
            s32Ret = PQ_MNG_SetSixBaseColorLevel((SIX_BASE_COLOR_OFFSET_S*)pstPQSixBase, sg_u32SourceMode);
        }
        else if (HI_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == stPqParam.stColorEnhance.enColorEnhanceType)
        {
            s32Ret = PQ_MNG_SetColorEnhanceMode(stPqParam.stColorEnhance.unColorGain.enColorMode, sg_u32SourceMode);
        }

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_PQ("Set ColorEnhance failed!\n");
            return s32Ret;
        }

        /* Update Coef */
        PQ_HAL_UpdateDCICoef(VDP_LAYER_VP0);
        PQ_HAL_UpdatACMCoef(VDP_LAYER_VP0);
    }

    /*
    DEBUG: Close ACM and DCI before Tuning
    */
    //DRV_PQ_SetPQModule(HI_PQ_MODULE_DCI, HI_FALSE);
    //DRV_PQ_SetPQModule(HI_PQ_MODULE_COLOR, HI_FALSE);

    return HI_SUCCESS;
}

/**
 \brief 设置各通道的CSC
 \attention \n
无

 \param[in] enDisplayId:
 \param[in] pstCscMode: 色彩空间

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateVdpCSC(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S* pstCscMode)
{
    CSC_MODE_S stCscMode = {HI_FALSE, HAL_CSC_BUTT};

    if (pstCscMode == NULL)
    {
        HI_ERR_PQ("pstCscMode is null!\n");
        return HI_FAILURE;
    }

    PQ_MNG_GetCSCMode(enDisplayId, &stCscMode);
    if ((stCscMode.bCSCEn == pstCscMode->bCSCEn)
        && ((HI_PQ_CSC_MODE_E)stCscMode.enCSC == pstCscMode->enCSC))
    {
        return HI_SUCCESS;
    }
    return PQ_MNG_SetCSCMode(enDisplayId, (CSC_MODE_S*)pstCscMode);
}

/**
 \brief 更新DCI直方图统计窗口
 \attention \n
无

 \param[in] *pstWin;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_UpdateDCIWin(HI_PQ_DCI_WIN_S* pstWin, HI_BOOL bDciEnable)
{
    //HI_S32 s32Ret  = HI_FAILURE;
    //HI_BOOL bOnOff = HI_FALSE;

    if (pstWin == NULL)
    {
        HI_ERR_PQ("pstWin is NULL point!.\n");
        return HI_FAILURE;
    }
    memcpy(&(stPqParam.stDciWin), pstWin, sizeof(HI_PQ_DCI_WIN_S));

    /*PQ_HAL_GetDCIEnable(VDP_LAYER_VP0, &bOnOff);

    s32Ret = PQ_MNG_EnableDCI(bDciEnable && bOnOff);
    if (HI_FAILURE == s32Ret)
    {
        HI_ERR_PQ("PQ_MNG_EnableDCI is error!.\n");
        return HI_FAILURE;
    }*/

    return PQ_MNG_UpdateDCIWin((DCI_WIN_S*)pstWin);
}

/**
 \brief 获取CSC系数
 \attention \n
无

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetCSCCoef(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S* pstCSCCoef, HI_PQ_CSC_DCCOEF_S* pstCSCDCCoef)
{
    return PQ_HAL_GetCscCoef(enCSCMode, (CSC_COEF_S*)pstCSCCoef, (CSC_DCCOEF_S*)pstCSCDCCoef);
}

/**
 \brief 获取8bit CSC系数
 \attention \n
无

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Get8BitCSCCoef(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S* pstCSCCoef, HI_PQ_CSC_DCCOEF_S* pstCSCDCCoef)
{
    return PQ_HAL_Get8BitCscCoef(enCSCMode, (CSC_COEF_S*)pstCSCCoef, (CSC_DCCOEF_S*)pstCSCDCCoef);
}

HI_S32 DRV_PQ_SetZme(HI_PQ_ZME_LAYER_E e32LayerId, HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_BOOL  bFirEnable)
{
    PQ_MNG_SetVdpZme(e32LayerId, (ALG_VZME_DRV_PARA_S*)pstZmeDrvPara, bFirEnable);
    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetVpssZme(HI_PQ_VPSS_ZME_LAYER_E e32LayerId, S_CAS_REGS_TYPE* pstReg, HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_BOOL  bFirEnable)
{
    PQ_MNG_SetVpssZme(e32LayerId, pstReg, (ALG_VZME_DRV_PARA_S*)pstZmeDrvPara, bFirEnable);
    return HI_SUCCESS;
}

/**
 \brief VPSS ZME二级缩放校验;
 \attention \n
无

 \param[in]
 u32InWitdh: 输入宽; u32InHeigh: 输入高; stZmeWin: 各层输出宽高;

 \param[out]
 u32OutWitdh 输出宽; u32OutHeigh 输出高;

 \retval :
HI_SUCCESS : 需要二级缩放
HI_FAILURE : 不需要二级缩放

 */
HI_S32 DRV_PQ_ZME_2L_Check(HI_U32 u32InWitdh, HI_U32 u32InHeigh, HI_PQ_ZME_WIN_S stZmeWin, HI_U32* pu32OutWitdh, HI_U32* pu32OutHeigh)
{
    HI_U32 u32Port0WitdhNum, u32Port0HeighNum, u32Port1WitdhNum, u32Port1HeighNum;

    if ((0 == stZmeWin.stPort0Win.u32Width * stZmeWin.stPort0Win.u32Height)
        || (0 == stZmeWin.stPort1Win.u32Width * stZmeWin.stPort1Win.u32Height))
    {
        return HI_FAILURE;
    }

    u32Port0WitdhNum = u32InWitdh / stZmeWin.stPort0Win.u32Width;
    u32Port0HeighNum = u32InHeigh / stZmeWin.stPort0Win.u32Height;
    u32Port1WitdhNum = u32InWitdh / stZmeWin.stPort1Win.u32Width;
    u32Port1HeighNum = u32InHeigh / stZmeWin.stPort1Win.u32Height;


    if ((u32Port0WitdhNum >= sg_u32Zme2LThl)
        && (u32Port1WitdhNum >= sg_u32Zme2LThl)
        && (u32Port0HeighNum >= sg_u32Zme2LThl)
        && (u32Port1HeighNum >= sg_u32Zme2LThl)) /*HD和SD需要2级缩放*/
    {
        *pu32OutWitdh = u32InWitdh / 2;
        *pu32OutHeigh = u32InHeigh / 2;

        HI_DEBUG_PQ("Port0 set 2L ZME, Port1 set 2L ZME\n");
    }
    else if (((u32Port0WitdhNum < sg_u32Zme2LThl)
              || (u32Port0HeighNum < sg_u32Zme2LThl))
             && (u32Port1WitdhNum >= sg_u32Zme2LThl)
             && (u32Port0HeighNum >= sg_u32Zme2LThl))/*SD需要2级缩放,HD不需要2级缩放*/
    {
        *pu32OutWitdh = stZmeWin.stPort0Win.u32Width;
        *pu32OutHeigh = stZmeWin.stPort0Win.u32Height;

        HI_DEBUG_PQ("Port0 not set 2L ZME, Port1 set 2L ZME\n");
    }
    else if (((u32Port0WitdhNum < sg_u32Zme2LThl)
              || (u32Port0HeighNum < sg_u32Zme2LThl))
             && ((u32Port1WitdhNum < sg_u32Zme2LThl)
                 || (u32Port1HeighNum < sg_u32Zme2LThl))) /*HD和SD都不需要2级缩放*/
    {
        *pu32OutWitdh = 0;
        *pu32OutHeigh = 0;

        HI_DEBUG_PQ("Port0 not set 2L ZME, Port1 not set 2L ZME\n");
    }
    else   /*其他情况,HD和SD都不需要2级缩放*/
    {
        *pu32OutWitdh = 0;
        *pu32OutHeigh = 0;

        HI_DEBUG_PQ("not set 2L ZME,Port0 Witdh:%d, Port0 Heigh:%d, Port1 Witdh:%d, Port1 Heigh:%d\n", \
                    u32Port0WitdhNum, u32Port0HeighNum, u32Port1WitdhNum, u32Port1HeighNum);
    }

    return HI_SUCCESS;
}

/**
 \brief 获取VPSS scaler分块缩放的配置参数
 \attention \n
无

 \param[in] pstZmeDrvPara:缩放输入信息
 \param[out] pstZmeSplitPara:分块缩放的配置信息

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSplitBlockZme(HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_PQ_SPLIT_ZME_PARA_S* pstZmeSplitPara)
{
    HI_U32 u32WIn, u32HIn, u32WOut, u32HOut;
    HI_U32 u32CWIn, u32CHIn, u32CWOut, u32CHOut;
    HI_U32 u32HStep, u32CHStep;
    HI_U32 u32HOffset, u32CHOffset;
    ALG_VZME_RTL_PARA_S stZmeRtlPara = {0};
    HI_U32 u32Tmp;

    u32WIn   = pstZmeDrvPara->u32ZmeFrmWIn;
    u32HIn   = pstZmeDrvPara->u32ZmeFrmHIn;
    u32WOut  = pstZmeDrvPara->u32ZmeFrmWOut;
    u32HOut  = pstZmeDrvPara->u32ZmeFrmHOut;
    u32CWIn  = (pstZmeDrvPara->u8ZmeYCFmtIn == 2) ? u32WIn : (u32WIn / 2);
    u32CHIn  = (pstZmeDrvPara->u8ZmeYCFmtIn == 1) ? (u32HIn / 2) : u32HIn;
    u32CWOut = (pstZmeDrvPara->u8ZmeYCFmtOut == 2) ? u32WOut : u32WOut / 2;
    u32CHOut = (pstZmeDrvPara->u8ZmeYCFmtOut == 1) ? (u32HOut / 2) : u32HOut;

    ALG_VZmeComnSet( (ALG_VZME_DRV_PARA_S*)pstZmeDrvPara, &stZmeRtlPara);

    memcpy(&(pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara), &stZmeRtlPara, sizeof(ALG_VZME_DRV_PARA_S));
    memcpy(&(pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara), &stZmeRtlPara, sizeof(ALG_VZME_DRV_PARA_S));

    /*分别计算亮度和色度的水平缩放步长*/
    u32HStep = stZmeRtlPara.u32ZmeRatioHL;
    u32CHStep = stZmeRtlPara.u32ZmeRatioHC;


    /*计算左边分块的相关信息*/
    pstZmeSplitPara->stPQSplitZmePara[0].u32PosXStart = 0;
    pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara.s32ZmeOffsetHL += 0;
    pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara.s32ZmeOffsetHC += 0;
    pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara.u32ZmeWIn  = u32WIn / 2 + 4;
    pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara.u32ZmeWOut = u32WOut / 2;
    pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara.u32ZmeHIn  = u32HIn;
    pstZmeSplitPara->stPQSplitZmePara[0].stZmeRtlPara.u32ZmeHOut = u32HOut;


    /*计算右边分块的相关信息*/
    u32HOffset = stZmeRtlPara.s32ZmeOffsetHL;
    u32CHOffset = stZmeRtlPara.s32ZmeOffsetHC;
    u32Tmp = ((((u32CHStep * (u32CWOut / 2)) + u32CHOffset) >> 20) - 3 );
    pstZmeSplitPara->stPQSplitZmePara[1].u32PosXStart = 2 * ( u32Tmp & 0xffffffe0 );
    pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara.s32ZmeOffsetHL = ((u32HStep * (u32WOut / 2) + u32HOffset) & 0xfffff) + 3 + (u32Tmp - pstZmeSplitPara->stPQSplitZmePara[1].u32PosXStart);
    pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara.s32ZmeOffsetHC = ((u32CHStep * (u32CWOut / 2) + u32CHOffset) & 0xfffff) + 3 + (u32Tmp - pstZmeSplitPara->stPQSplitZmePara[1].u32PosXStart) / 2;
    pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara.u32ZmeWIn  = u32WIn - pstZmeSplitPara->stPQSplitZmePara[1].u32PosXStart;
    pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara.u32ZmeWOut = u32WOut / 2;
    pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara.u32ZmeHIn  = u32HIn;
    pstZmeSplitPara->stPQSplitZmePara[1].stZmeRtlPara.u32ZmeHOut = u32HOut;

    return HI_SUCCESS;
}


/**
 \brief 获取VPSS scaler缩放系数
 \attention \n
无

 \param[in] pstScalerInfo:缩放信息
 \param[out] pvCoefAddr:缩放系数地址

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetVpssScalerCoef(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pLCoefAddr, HI_VOID* pCCoefAddr)
{
    HI_S32 s32Ret;

    s32Ret =  PQ_MNG_GetVpssScalerCoef(pstScalerInfo, pLCoefAddr, pCCoefAddr);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Get scalercoef failed!\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}
/**
 \brief 获取VDP scaler缩放系数
 \attention \n
无

 \param[in] pstScalerInfo:缩放信息
 \param[out] pvCoefAddr:缩放系数地址

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetScalerCoef(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pLCoefAddr, HI_VOID* pCCoefAddr)
{
    HI_S32 s32Ret;

    s32Ret =  PQ_MNG_GetVdpScalerCoef(pstScalerInfo, pLCoefAddr, pCCoefAddr);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Get scalercoef failed!\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}
/**
 \brief 获取wbc scaler缩放系数
 \attention \n
无

 \param[in] pstScalerInfo:缩放信息
 \param[out] pvCoefAddr:缩放系数地址

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetWbcScalerCoef(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pLCoefAddr, HI_VOID* pCCoefAddr)
{
    HI_S32 s32Ret;

    s32Ret =  PQ_MNG_GetWbcScalerCoef(pstScalerInfo, pLCoefAddr, pCCoefAddr);

    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("Get scalercoef failed!\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

/**
 \brief 获取各通道的CSC(用于调试)
 \attention \n
无

 \param[in] enDisplayId
 \param[out] pstCSCMode

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetCSCMode(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S* pstCSCMode)
{
    if (pstCSCMode == NULL)
    {
        HI_ERR_PQ("get CSC point is null!\n");
    }

    if (enDisplayId >= HI_PQ_VDP_CSC_BUTT)
    {
        HI_ERR_PQ("Error,Select Wrong CSC!\n");
        return HI_FAILURE;
    }

    return PQ_MNG_GetCSCMode(enDisplayId, (CSC_MODE_S*)pstCSCMode);
}

/**
 \brief 获取SR演示模式开关
 \attention \n
无

 \param[in] ps32Type

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSRMode(HI_S32* ps32Type)
{
    if (ps32Type == NULL)
    {
        HI_ERR_PQ("SR ps32Type is null point !\n");
        return HI_FAILURE;
    }
    return PQ_MNG_GetSRDemo(ps32Type);
}

/**
 \brief 设置SR演示模式开关
 \attention \n
无

 \param[in] eSRMode: SR演示模式0-只ZME;1-右边SR；2-左边SR；3-SR开

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSRMode(HI_PQ_SR_DEMO_E eSRMode)
{
    HI_S32 s32Ret;

    s32Ret = PQ_MNG_EnableSRDemo(eSRMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("error in setting sr mode!\n");
        return HI_FAILURE;
    }
    HI_DEBUG_PQ("Set SR mode is %d\n", eSRMode);

    return HI_SUCCESS;
}

#if 0
/**
 \brief 读取DB运算所需的寄存器信息，配置到寄存器
 \attention \n
无

 \param[in]  HI_PQ_WBC_INFO_S* pstWbcInfo

 \retval ::HI_SUCCESS

 */
static HI_S32 DRV_PQ_DBCalcCfg(HI_PQ_DB_CALC_INFO_S* pstDbCalcInfo)
{
    if (pstDbCalcInfo == NULL)
    {
        HI_ERR_PQ("get Db Calc Info pointer is null!\n");
        return HI_FAILURE;
    }

    PQ_MNG_DBCalcConfigCfg((DB_CALC_INFO_S*)pstDbCalcInfo);

    return HI_SUCCESS;
}
#endif
/**
 \brief 获取WbcInfo信息
 \attention \n
无

 \param[in]  HI_PQ_WBC_INFO_S* pstWbcInfo

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetWbcInfo(HI_PQ_WBC_INFO_S* pstVpssWbcInfo)
{
    /* Glboal motion */
    MOTION_INPUT_S stMotionInput;

    if (pstVpssWbcInfo == NULL)
    {
        HI_ERR_PQ("get Wbc Info pointer is null!\n");
        return HI_FAILURE;
    }

    /* Glboal motion Calc 数据解析*/
    stMotionInput.u32HandleNo  = pstVpssWbcInfo->u32HandleNo;
    stMotionInput.u32Height    = pstVpssWbcInfo->u32Height;
    stMotionInput.u32Width     = pstVpssWbcInfo->u32Width;
    stMotionInput.pstMotionReg = pstVpssWbcInfo->pstVPSSWbcReg;
    /* Global Motion After Calc Set AdjustGain to Reg */
    PQ_MNG_GetGlobalMotion(&stMotionInput);

    return HI_SUCCESS;
}
#if 0
/**
 \brief 获取Globa Motion信息
 \attention \n
无

 \param[in]  *pstMotionHist:直方图
 \param[out] *pstMotionResult:运动信息

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetDeiGlobalMotion(HI_PQ_MOTION_INPUT_S* pstMotionInput, HI_PQ_MOTION_INFO_S* pstMotionResult)
{
    if (pstMotionInput == NULL || pstMotionResult == NULL)
    {
        HI_ERR_PQ("get Globa Motion point is null!\n");
        return HI_FAILURE;
    }

    return PQ_MNG_GetGlobalMotion((MOTION_INPUT_S*)pstMotionInput, (MOTION_RESULT_S*)pstMotionResult);
}
#endif

/**
 \brief 设置算法运算完之后的寄存器
 \attention \n
无

 \param[in]  *pstWbcInfo
 \param[out] *pstVpssCfgInfo
 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAlgCalcCfg(HI_PQ_WBC_INFO_S* pstVpssWbcInfo, HI_PQ_CFG_INFO_S* pstVpssCfgInfo)
{
    /* IFMD */
    HI_PQ_IFMD_CALC_S     stIfmdCalcInfo;
    HI_PQ_IFMD_PLAYBACK_S stIfmdCalcResult = {0};
    /* DB */
    HI_PQ_DB_CALC_INFO_S  stDbCalcInfo;
    /* HSharpen or Sharpen */
    static HI_U32 s_u32InMode  = SOURCE_MODE_NO;
    static HI_U32 s_u32OutMode = OUTPUT_MODE_NO;

    if (pstVpssWbcInfo == NULL)
    {
        HI_ERR_PQ("Wbc Info pointer is null!\n");

        return HI_FAILURE;
    }

    if (0 == pstVpssWbcInfo->bProgressive)
    {
        /* IFMD Calc 数据解析*/
        stIfmdCalcInfo.u32HandleNo       = pstVpssWbcInfo->u32HandleNo;
        stIfmdCalcInfo.u32WidthY         = pstVpssWbcInfo->u32Width;
        stIfmdCalcInfo.u32HeightY        = pstVpssWbcInfo->u32Height;
        stIfmdCalcInfo.s32FieldOrder     = pstVpssWbcInfo->s32FieldOrder;
        stIfmdCalcInfo.s32FieldMode      = pstVpssWbcInfo->s32FieldMode;
        stIfmdCalcInfo.u32FrameRate      = pstVpssWbcInfo->u32FrameRate;
        stIfmdCalcInfo.bPreInfo          = pstVpssWbcInfo->bPreInfo;
        stIfmdCalcInfo.pstIfmdHardOutReg = pstVpssWbcInfo->pstVPSSWbcReg;
        memcpy(&(stIfmdCalcInfo.stVdecInfo), &(pstVpssWbcInfo->stVdecInfo), sizeof(PQ_VDEC_INFO_S));

        /* FMD After Calc Set CFG Reg to Reg */
        DRV_PQ_IfmdDect(&stIfmdCalcInfo, &stIfmdCalcResult);

        /* fmdCalcResult Tran to Vpss CFG */
        pstVpssCfgInfo->die_reset        = stIfmdCalcResult.die_reset;
        pstVpssCfgInfo->die_stop         = stIfmdCalcResult.die_stop;
        pstVpssCfgInfo->dir_mch          = stIfmdCalcResult.dir_mch;
        pstVpssCfgInfo->die_out_sel      = stIfmdCalcResult.die_out_sel;
        pstVpssCfgInfo->s32FieldOrder    = stIfmdCalcResult.s32FieldOrder;
        pstVpssCfgInfo->s32SceneChanged  = stIfmdCalcResult.s32SceneChanged;
        pstVpssCfgInfo->s32FilmType      = stIfmdCalcResult.s32FilmType;
        pstVpssCfgInfo->u32KeyValue      = stIfmdCalcResult.u32KeyValue;

    }

    /* DB Clac 数据的解析*/
    stDbCalcInfo.u32HandleNo     = pstVpssWbcInfo->u32HandleNo;
    stDbCalcInfo.u32Width        = pstVpssWbcInfo->u32Width;
    stDbCalcInfo.u32Height       = pstVpssWbcInfo->u32Height;
    stDbCalcInfo.pstDbCalcWbcReg = pstVpssWbcInfo->pstVPSSWbcReg;

#if defined(CHIP_TYPE_hi3798cv200_a)
    /* DB After Calc Set CFG Reg to Reg */
    PQ_MNG_DBCalcConfigCfg((DB_CALC_INFO_S*)(&stDbCalcInfo));
#endif
    /* DNR After Calc Tran to Vpss CFG in above function */

    /* HSharpen or Sharpen */
    if ((s_u32InMode != sg_u32OutputMode) || (s_u32OutMode != sg_u32SourceMode))
    {
        (HI_VOID)PQ_MNG_LoadPhyList(REG_TYPE_VPSS, sg_u32SourceMode, sg_u32OutputMode, PQ_MODULE_HSHARPEN);

        s_u32InMode  = sg_u32OutputMode;
        s_u32OutMode = sg_u32SourceMode;

        PQ_MNG_EnableSharpen(stPqParam.bModuleOnOff[HI_PQ_MODULE_SHARPNESS]);
        PQ_MNG_EnableSharpenDemo(stPqParam.bDemoOnOff[HI_PQ_DEMO_SHARPNESS]);
        (HI_VOID)DRV_PQ_SetSharpness(NUM2LEVEL(stPqParam.u32Sharpness));
    }

    return HI_SUCCESS;
}


/**
\brief     :Tnr的Global Motion软算法API

\attention :
            本算法参考DEI模块进行移植
            算法提供：裴朝科 p00188942；移植&维护：吕明君 l00268071

\param[in] :pstParamIn结构，包含如下元素
            u32HdlNo 实例的ID
            u32Width 输入图像宽度
            u32Height 输入图像高度
            pstMotionReg 寄存器地址

\param[out]:pstMotionResult结构，包含如下元素
            u32GlobalMotion 配给寄存器VPSS_TNR_TFM_PARA中的tfm_globalmotion
            u32AdjustGain

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 DRV_PQ_GetTnrGlobalMotion(HI_PQ_TNR_MOTION_PARAM_IN_S* pstParamIn, HI_PQ_TNR_MOTION_RESULT_S* pstMotionResult)
{
#if 0
    if (pstParamIn == NULL || pstMotionResult == NULL)
    {
        HI_ERR_PQ("DRV_PQ_GetTnrGlobalMotion param-pointer is null!\n");
        return HI_FAILURE;
    }

    return PQ_MNG_TnrGetGlobalMotion((TNR_MOTION_PARAM_IN_S*)pstParamIn, (TNR_MOTION_RESULT_S*)pstMotionResult);
#else
    return HI_SUCCESS;
#endif
}


/**
\brief     :根据Global Motion获取DB的自适应强度值API

\attention :函数内对多实例的ID u32HdlNo 不做活动性检测，仅判断阈值
            隔行或者逐行信号源所采用的Global Motion不同；
            算法内已经将输出参数u8HWeight和u8VWeight配到寄存器VPSS_DB_WEIGHT中
            算法提供：晏秀梅 y00224511；移植&维护：吕明君 l00268071

\param[in] :pstParamIn结构，包含如下元素
            u32HdlNo 实例的ID
            u8SCDStr 是根据SCD的api计算得出的一个值[0,255]
            pstReg   global motion 寄存器地址
            eType 数据源类型，隔行或逐行，是否做DEI

\param[out]:pstDBstr  DB强度值。对应寄存器VPSS_DB_WEIGHT，分别为u8HWeight和u8VWeight

\retval    :HI_SUCCESS/HI_FAILURE

*/
extern HI_S32 DRV_PQ_GetAdaptiveDBStrength(HI_PQ_DB_STR_PARAM_IN_S* pstParamIn, HI_PQ_DB_WEIGHT_S* pstDBstr)
{
    return HI_SUCCESS;
}


/**
 \brief 逐行FMD模式检测
 \attention \n
无

 \param[in] pstVPSSReg: VPSS物理寄存器地址

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_PfmdDetect(HI_PQ_PFMD_CALC_S* pstPfmdCalc, HI_PQ_PFMD_PLAYBACK_S* pstPfmdResult)
{
    return HI_SUCCESS;
}

/**
 \brief 隔行FMD模式检测
 \attention \n
无

 \param[in] pstIfmdCalc  算法所需参数(统计信息地址，场序，顶底场标识等)
 \param[out] pstIfmdResult IFMD计算结果
 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_IfmdDect(HI_PQ_IFMD_CALC_S* pstIfmdCalc, HI_PQ_IFMD_PLAYBACK_S* pstIfmdResult)
{
    static IFMD_TotalHardPara IfmdTotalHardPara;

    PQ_CHECK_NULL_PTR(pstIfmdResult);
    PQ_CHECK_NULL_PTR(pstIfmdCalc);
    /* From VPSS Get IfmdTotalHardPara */
    PQ_HAL_GetIFmdStatInfo((PQ_REG_IFMD_CALC_S*)pstIfmdCalc, &IfmdTotalHardPara);
    /* Clac to pstIfmdResult */
    PQ_MNG_IFMD_GetPlayBackConfig(&IfmdTotalHardPara, (PQ_IFMD_CALC_S*)pstIfmdCalc, (REG_PLAYBACK_CONFIG_S*)pstIfmdResult);
    /* Set pstIfmdResult to CFG Reg */
    PQ_HAL_SetIFmdInfo(pstIfmdCalc->u32HandleNo, (REG_PLAYBACK_CONFIG_S*)pstIfmdResult);
    PQ_HAL_SetEdgeSmoothEn(pstIfmdCalc->u32HandleNo, pstIfmdResult->u32EdgeSmoothEn);

    return HI_SUCCESS;
}

/**
 \brief 获取DCI直方图
 \attention \n
无

 \param[in] *pstDciHist:0-255

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetDciHistgram(HI_PQ_HISTGRAM_S* pstDciHist)
{
    if (pstDciHist == NULL)
    {
        HI_ERR_PQ("pstDciHist param-pointer is null!\n");
        return HI_FAILURE;
    }
    return PQ_HAL_GetDCIHistgram((DCI_HISTGRAM_S*)pstDciHist);
}

/**
 \brief 显示PQ状态信息
 \attention \n
无

 \param[in] *s;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_ProcRead(struct seq_file* s, HI_VOID* data)
{
    HI_U32 u32SDBrightness = 0;
    HI_U32 u32SDContrast = 0;
    HI_U32 u32SDHue = 0;
    HI_U32 u32SDSaturation = 0;
    HI_U32 u32HDBrightness = 0;
    HI_U32 u32HDContrast = 0;
    HI_U32 u32HDHue = 0;
    HI_U32 u32HDSaturation = 0;
    HI_U32 u32Sharpness = 0;
    HI_U32 u32FleshTone = 0;
    HI_U32 u32DciLevelGain = 0;
    HI_U32 u32OnOff = 0;

    PROC_PRINT(s, "\n------------------------ PQ  Driver info --------------------------\n");
    PROC_PRINT(s, "------------ PQ Driver Version = %s\n", PQ_VERSION);
    PROC_PRINT(s, "------------ PQ Driver Bin Size = %d\n", sizeof(PQ_PARAM_S));

    if (HI_FALSE == g_bLoadPqBin)
    {
        PROC_PRINT(s, "------------ Load PQ Bin Failure\n");
    }
    else
    {
        PROC_PRINT(s, "------------ PQ Driver Get Flash Data : Success\n");
        PROC_PRINT(s, "------------ PQ Bin Info Version = %s\n", g_pstPqParam->stPQFileHeader.u8Version);
        PROC_PRINT(s, "------------ PQ Bin Info Chipname = %s\n", g_pstPqParam->stPQFileHeader.u8ChipName);
        PROC_PRINT(s, "------------ PQ Bin Info Sdkversion = %s\n", g_pstPqParam->stPQFileHeader.u8SDKVersion);
        PROC_PRINT(s, "------------ PQ Bin Info Author = %s\n", g_pstPqParam->stPQFileHeader.u8Author);
        PROC_PRINT(s, "------------ PQ Bin Info Describe = %s\n", g_pstPqParam->stPQFileHeader.u8Desc);
        PROC_PRINT(s, "------------ PQ Bin Info Time = %s\n", g_pstPqParam->stPQFileHeader.u8Time);
    }

    if (SOURCE_MODE_SD == sg_u32SourceMode)
    {
        PROC_PRINT(s, "------------ Source Type : SD\n");
    }
    else if (SOURCE_MODE_HD == sg_u32SourceMode)
    {
        PROC_PRINT(s, "------------ Source Type : HD\n");
    }
    if (SOURCE_MODE_UHD == sg_u32SourceMode)
    {
        PROC_PRINT(s, "------------ Source Type : UHD\n");
    }

    if (OUTPUT_MODE_SD == sg_u32OutputMode)
    {
        PROC_PRINT(s, "------------ Output Type : SD\n");
    }
    else if (OUTPUT_MODE_HD == sg_u32OutputMode)
    {
        PROC_PRINT(s, "------------ Output Type : HD\n");
    }
    if (OUTPUT_MODE_UHD == sg_u32OutputMode)
    {
        PROC_PRINT(s, "------------ Output Type : UHD\n");
    }


    /* Picture Setting Information */
    //PROC_PRINT(s, "\n---------------Picture Setting Information---------------\n");

    DRV_PQ_GetSDBrightness(&u32SDBrightness);
    DRV_PQ_GetSDContrast(&u32SDContrast);
    DRV_PQ_GetSDHue(&u32SDHue);
    DRV_PQ_GetSDSaturation(&u32SDSaturation);
    DRV_PQ_GetHDBrightness(&u32HDBrightness);
    DRV_PQ_GetHDContrast(&u32HDContrast);
    DRV_PQ_GetHDHue(&u32HDHue);
    DRV_PQ_GetHDSaturation(&u32HDSaturation);
    DRV_PQ_GetSharpness(&u32Sharpness);
    DRV_PQ_GetFleshToneLevel(&u32FleshTone);
    PQ_MNG_GetDCILevelGain(&u32DciLevelGain);

    PROC_PRINT(s, "\n---------------------------Dispaly 0-------------------------------\n");
    PROC_PRINT(s, "Brightness = %d\n" "Contrast = %d\n" "Hue = %d\n" "Saturation = %d\n", \
               u32SDBrightness, u32SDContrast, \
               u32SDHue,  u32SDSaturation);

    PROC_PRINT(s, "\n---------------------------Dispaly 1-------------------------------\n");
    PROC_PRINT(s, "Brightness = %d\n" "Contrast = %d\n" "Hue = %d\n" "Saturation = %d\n", \
               u32HDBrightness, u32HDContrast, u32HDHue, u32HDSaturation);
    PROC_PRINT(s, "\n");
    PROC_PRINT(s, "Sharpness = %d\n" "DciLevelGain = %d\n", u32Sharpness, u32DciLevelGain);

    if (0 == u32FleshTone)
    {
        PROC_PRINT(s, "FleshTone = off\n");
    }
    else if (1 == u32FleshTone)
    {
        PROC_PRINT(s, "FleshTone = low\n");
    }
    else if (2 == u32FleshTone)
    {
        PROC_PRINT(s, "FleshTone = middle\n");
    }
    if (3 == u32FleshTone)
    {
        PROC_PRINT(s, "FleshTone = high\n");
    }

    PROC_PRINT(s, "\n");
    DRV_PQ_GetPQModule(HI_PQ_MODULE_SHARPNESS, &u32OnOff);
    PROC_PRINT(s, "Module Sharpness: %s\n",  u32OnOff ? "on" : "off");
    DRV_PQ_GetPQModule(HI_PQ_MODULE_DCI, &u32OnOff);
    PROC_PRINT(s, "Module DCI      : %s\n",  u32OnOff ? "on" : "off");
    DRV_PQ_GetPQModule(HI_PQ_MODULE_COLOR, &u32OnOff);
    PROC_PRINT(s, "Module Color    : %s\n",  u32OnOff ? "on" : "off");
    DRV_PQ_GetPQModule(HI_PQ_MODULE_SR, &u32OnOff);
    PROC_PRINT(s, "Module SR       : %s\n",  u32OnOff ? "on" : "off");

    PROC_PRINT(s, "\n-------------------------------------------------------------------\n");

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetPqParam(HI_VOID)
{

    return HI_SUCCESS;
}

static HI_S32 DRV_PQ_GetFlashPqBin(PQ_PARAM_S* pstPqParam)
{
    HI_S32 s32Ret;
    PQ_FILE_HEADER_S* pstPqFileHead = HI_NULL;
    HI_U32 u32CheckSize = 0;
    HI_U32 u32CheckPos  = 0;
    HI_U32 u32CheckSum  = 0;
    HI_U32 u32PqAddr    = 0;
    HI_U32 u32PqLen     = 0;
    PDM_EXPORT_FUNC_S*   pstPdmFuncs = HI_NULL;
    PQ_PARAM_S* pstPqBinParam = HI_NULL;

    memset((HI_VOID*)pstPqParam, 0x0, sizeof(PQ_PARAM_S));

    //get pq bin from pdm
    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID**)&pstPdmFuncs);
    if (s32Ret != HI_SUCCESS)
    {
        HI_FATAL_PQ("HI_DRV_MODULE_GetFunction failed!\n");
        return HI_FAILURE;
    }

    if (NULL == pstPdmFuncs)
    {
        HI_FATAL_PQ("\npstPdmFuncs is NULL\n");
        return HI_FAILURE;
    }

    if (NULL == pstPdmFuncs->pfnPDM_GetData)
    {
        HI_ERR_PQ("\npstPdmFuncs->pfnPDM_GetData is NULL\n");
        return HI_FAILURE;
    }

    s32Ret = pstPdmFuncs->pfnPDM_GetData(PQ_DEF_NAME, &u32PqAddr, &u32PqLen);

    if ((HI_SUCCESS != s32Ret) || (HI_NULL == u32PqAddr) )
    {
        HI_ERR_PQ("PQ bin param may not burned\r\n");
        return HI_FAILURE;
    }

    pstPqBinParam = (PQ_PARAM_S*)u32PqAddr;
    pstPqFileHead = &(pstPqBinParam->stPQFileHeader);

    u32CheckPos = (HI_U8*) & (pstPqBinParam->stPQCoef) - (HI_U8*)pstPqBinParam;
    u32CheckSize = pstPqFileHead->u32ParamSize;

    if (u32CheckSize != sizeof(PQ_PARAM_S))
    {
        HI_ERR_PQ( "check PQbin size error, Param Size = %d,sizeof(PQ_PARAM_S) = %d\n", u32CheckSize, sizeof(PQ_PARAM_S));
        return HI_FAILURE;
    }

    if (0 != strncmp(pstPqFileHead->u8Version, PQ_VERSION, strlen(PQ_VERSION)))
    {
        HI_ERR_PQ( "check PQbin Version[%s] error\n", PQ_VERSION);
        return HI_FAILURE;
    }

    if (HI_SUCCESS != DRV_PQ_CheckChipName(pstPqFileHead->u8ChipName))
    {
        HI_ERR_PQ( "check PQbin ChipName[%s] error\n", pstPqFileHead->u8ChipName);
        return HI_FAILURE;
    }

    while (u32CheckPos < u32CheckSize)
    {
        u32CheckSum += *(HI_U8*)(((HI_U8*)pstPqBinParam) + u32CheckPos);
        u32CheckPos++;
    }

    if (u32CheckSum != pstPqFileHead->u32FileCheckSum)
    {
        HI_ERR_PQ( "PQbin checksum error,declare checksum = %d,calcsum = %d\r\n", pstPqFileHead->u32FileCheckSum, u32CheckSum);
        //pstPdmFuncs->pfnPDM_ReleaseReserveMem(PQ_DEF_NAME);
        return HI_FAILURE;
    }

    memcpy((HI_VOID*)(pstPqParam), (HI_VOID*)pstPqBinParam, sizeof(PQ_PARAM_S));

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetBinPhyAddr(HI_U32* pu32Addr)
{
    *pu32Addr = g_stPqBinBuf.u32StartPhyAddr;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_GetPicSetting(HI_VOID)
{
    HI_S32 s32Ret;
    HI_DISP_PARAM_S stSDDispParam;
    HI_DISP_PARAM_S stHDDispParam;
    PDM_EXPORT_FUNC_S* pstPdmFuncs = HI_NULL;

    s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_PDM, (HI_VOID**)&pstPdmFuncs);
    if (s32Ret != HI_SUCCESS)
    {
        HI_FATAL_PQ("HI_DRV_MODULE_GetFunction failed!\n");
        return HI_FAILURE;
    }

    if (NULL == pstPdmFuncs)
    {
        HI_FATAL_PQ("\npstPdmFuncs is NULL\n");
        return HI_FAILURE;
    }

    if (NULL == pstPdmFuncs->pfnPDM_GetDispParam)
    {
        HI_ERR_PQ("\npstPdmFuncs->pfnPDM_GetDispParam is NULL\n");
        return HI_FAILURE;
    }

    s32Ret = pstPdmFuncs->pfnPDM_GetDispParam(HI_UNF_DISPLAY0, &stSDDispParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("pfnPDM_GetDispParam fail\r\n");
        return HI_FAILURE;
    }

    stPqParam.stSDPictureSetting.u16Brightness = (stSDDispParam.u32Brightness * 255 + 50) / 100;
    stPqParam.stSDPictureSetting.u16Contrast   = (stSDDispParam.u32Contrast * 255 + 50) / 100;
    stPqParam.stSDPictureSetting.u16Hue        = (stSDDispParam.u32HuePlus * 255 + 50) / 100;
    stPqParam.stSDPictureSetting.u16Saturation = (stSDDispParam.u32Saturation * 255 + 50) / 100;

    s32Ret = pstPdmFuncs->pfnPDM_GetDispParam(HI_UNF_DISPLAY1, &stHDDispParam);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PQ("pfnPDM_GetDispParam fail\r\n");
        return HI_FAILURE;
    }

    stPqParam.stHDPictureSetting.u16Brightness = (stHDDispParam.u32Brightness * 255 + 50) / 100;
    stPqParam.stHDPictureSetting.u16Contrast   = (stHDDispParam.u32Contrast * 255 + 50) / 100;
    stPqParam.stHDPictureSetting.u16Hue        = (stHDDispParam.u32HuePlus * 255 + 50) / 100;
    stPqParam.stHDPictureSetting.u16Saturation = (stHDDispParam.u32Saturation * 255 + 50) / 100;

    return HI_SUCCESS;
}

HI_S32 DRV_PQ_SetAcmLuma(HI_PQ_ACM_LUT_S* pstAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32RegCmd;
    PQ_ACM_MODE_S* pstModeLut;

    PQ_CHECK_NULL_PTR(pstAttr);
    PQ_CHECK_NULL_PTR(g_pstPqParam);

    u32RegCmd = pstAttr->u32LutType;
    pstModeLut = &(g_pstPqParam->stPQCoef.stAcmCoef.stModeLut);

    switch (u32RegCmd)
    {
        case PQ_CMD_VIRTUAL_ACM_RECMD_LUT:
            memcpy(pstModeLut->stModeRecmd.as16Y, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BLUE_LUT:
            memcpy(pstModeLut->stModeBlue.as16Y, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_GREEN_LUT:
            memcpy(pstModeLut->stModeGreen.as16Y, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BG_LUT:
            memcpy(pstModeLut->stModeBG.as16Y, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_FLESH_LUT:
            memcpy(pstModeLut->stModeFleshtone.as16Y, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT:
            memcpy(pstModeLut->stMode6BColor.as16Y, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        default:
            HI_ERR_PQ("%s:u32RegCmd[0x%x] is error!\n", __FUNCTION__, u32RegCmd);
            break;
    }

    s32Ret = PQ_HAL_SetACMLumaTbl((COLOR_LUT_S*)pstAttr->as16Lut);

    return s32Ret;
}

HI_S32 DRV_PQ_SetAcmHue(HI_PQ_ACM_LUT_S* pstAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32RegCmd;
    PQ_ACM_MODE_S* pstModeLut;

    PQ_CHECK_NULL_PTR(pstAttr);
    PQ_CHECK_NULL_PTR(g_pstPqParam);

    u32RegCmd = pstAttr->u32LutType;
    pstModeLut = &(g_pstPqParam->stPQCoef.stAcmCoef.stModeLut);

    switch (u32RegCmd)
    {
        case PQ_CMD_VIRTUAL_ACM_RECMD_LUT:
            memcpy(pstModeLut->stModeRecmd.as16H, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BLUE_LUT:
            memcpy(pstModeLut->stModeBlue.as16H, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_GREEN_LUT:
            memcpy(pstModeLut->stModeGreen.as16H, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BG_LUT:
            memcpy(pstModeLut->stModeBG.as16H, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_FLESH_LUT:
            memcpy(pstModeLut->stModeFleshtone.as16H, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT:
            memcpy(pstModeLut->stMode6BColor.as16H, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        default:
            HI_ERR_PQ("%s:u32RegCmd[0x%x] is error!\n", __FUNCTION__, u32RegCmd);
            break;
    }

    s32Ret = PQ_HAL_SetACMHueTbl((COLOR_LUT_S*)pstAttr->as16Lut);

    return s32Ret;
}

HI_S32 DRV_PQ_SetAcmSat(HI_PQ_ACM_LUT_S* pstAttr)
{
    HI_S32 s32Ret;
    HI_U32 u32RegCmd;
    PQ_ACM_MODE_S* pstModeLut;

    PQ_CHECK_NULL_PTR(pstAttr);
    PQ_CHECK_NULL_PTR(g_pstPqParam);

    u32RegCmd = pstAttr->u32LutType;
    pstModeLut = &(g_pstPqParam->stPQCoef.stAcmCoef.stModeLut);

    switch (u32RegCmd)
    {
        case PQ_CMD_VIRTUAL_ACM_RECMD_LUT:
            memcpy(pstModeLut->stModeRecmd.as16S, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BLUE_LUT:
            memcpy(pstModeLut->stModeBlue.as16S, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_GREEN_LUT:
            memcpy(pstModeLut->stModeGreen.as16S, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_BG_LUT:
            memcpy(pstModeLut->stModeBG.as16S, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_FLESH_LUT:
            memcpy(pstModeLut->stModeFleshtone.as16S, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        case PQ_CMD_VIRTUAL_ACM_6BCOLOR_LUT:
            memcpy(pstModeLut->stMode6BColor.as16S, pstAttr->as16Lut, sizeof(COLOR_LUT_S));
            break;
        default:
            HI_ERR_PQ("%s:u32RegCmd[0x%x] is error!\n", __FUNCTION__, u32RegCmd);
            break;
    }

    s32Ret = PQ_HAL_SetACMSatTbl((COLOR_LUT_S*)pstAttr->as16Lut);

    return s32Ret;
}


HI_S32 DRV_PQ_SetReg(HI_PQ_REGISTER_S* pstAttr)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 s32Num = -1;

    PQ_CHECK_NULL_PTR(g_pstPqParam);
    s32Num = PQ_MNG_UpdatePhyList(pstAttr->u32RegAddr, pstAttr->u8Lsb, pstAttr->u8Msb, \
                                  pstAttr->u8SourceMode, pstAttr->u8OutputMode, pstAttr->u32Value);
    if (HI_FAILURE == s32Num)
    {
        HI_WARN_PQ("Warning! not find Register[Address:0x%x, Bit:%d~%d],SourceMode:[%d],OutputMode:[%d]\n", \
                   pstAttr->u32RegAddr, pstAttr->u8Lsb, pstAttr->u8Msb, pstAttr->u8SourceMode, pstAttr->u8OutputMode);
    }
    else
    {
        if ((SOURCE_MODE_NO != g_pstPqParam->stPQPhyReg[s32Num].u8SourceMode) \
            && (pstAttr->u8SourceMode != sg_u32SourceMode))
        {
            HI_WARN_PQ("Warning! Current Source Mode:[%d], Set Source Mode:[%d],Not Set Physical Reg\n", \
                       sg_u32SourceMode, pstAttr->u8SourceMode);
            return HI_SUCCESS;
        }

        if ((OUTPUT_MODE_NO != g_pstPqParam->stPQPhyReg[s32Num].u8OutputMode) \
            && (pstAttr->u8OutputMode != sg_u32OutputMode))
        {
            HI_WARN_PQ("Warning! Current Output Mode:[%d], Set Output Mode:[%d],Not Set Physical Reg\n", \
                       sg_u32OutputMode, pstAttr->u8OutputMode);
            return HI_SUCCESS;
        }
    }

    if (PQ_HAL_IsVpssReg(pstAttr->u32RegAddr) == HI_TRUE)
    {
        s32Ret = PQ_MNG_SetVpssReg(pstAttr->u32RegAddr, pstAttr->u8Lsb, \
                                   pstAttr->u8Msb, pstAttr->u32Value);
    }
    else if (PQ_HAL_IsVdpReg(pstAttr->u32RegAddr) == HI_TRUE)
    {
        s32Ret = PQ_MNG_SetVdpReg(pstAttr->u32RegAddr, pstAttr->u8Lsb, \
                                  pstAttr->u8Msb, pstAttr->u32Value);
    }
    else if (PQ_HAL_IsSpecialReg(pstAttr->u32RegAddr) == HI_TRUE)
    {
        if (pstAttr->u32RegAddr == PQ_CMD_SPECIAL_IP_DETECT)
        {
            s32Ret = PQ_MNG_IFMD_SetIPDetect(pstAttr->u32RegAddr, pstAttr->u8Lsb, \
                                             pstAttr->u8Msb, pstAttr->u32Value);
        }
    }
    else
    {
        HI_ERR_PQ("not VPSS/VDP/Special Register!\n");
        return HI_FAILURE;
    }

    return s32Ret;
}


HI_S32 DRV_PQ_GetReg(HI_PQ_REGISTER_S* pstAttr)
{
    HI_U32 u32Addr, u32Value;
    HI_U8  u8Lsb, u8Msb, u8SourceMode, u8OutputMode;
    HI_U32 i;

    PQ_CHECK_NULL_PTR(g_pstPqParam);

    for (i = 0; i < PHY_REG_MAX; i++)
    {
        u32Addr       = g_pstPqParam->stPQPhyReg[i].u32RegAddr;
        u32Value      = g_pstPqParam->stPQPhyReg[i].u32Value;
        u8Lsb         = g_pstPqParam->stPQPhyReg[i].u8Lsb;
        u8Msb         = g_pstPqParam->stPQPhyReg[i].u8Msb;
        u8SourceMode  = g_pstPqParam->stPQPhyReg[i].u8SourceMode;
        u8OutputMode  = g_pstPqParam->stPQPhyReg[i].u8OutputMode;

        if (u32Addr != pstAttr->u32RegAddr)
        {
            continue;
        }

        if (u8Lsb != pstAttr->u8Lsb)
        {
            continue;
        }

        if (u8Msb != pstAttr->u8Msb)
        {
            continue;
        }

        if ((SOURCE_MODE_NO != u8SourceMode) && (u8SourceMode != pstAttr->u8SourceMode))
        {
            continue;
        }

        if ((OUTPUT_MODE_NO != u8OutputMode) && (u8OutputMode != pstAttr->u8OutputMode))
        {
            continue;
        }

        pstAttr->u32Value = u32Value;
        return HI_SUCCESS;
        //HI_INFO_PQ("Load RegType:%d, SourceMode:%d, Module:%d\n", enRegType, u32SourceMode, u32Module);
    }

    HI_ERR_PQ("Error! not find Phy Register List[Address:0x%x, Bit:%d~%d],SourceMode:[%d], OutputMode:[%d]\n", \
              pstAttr->u32RegAddr, pstAttr->u8Lsb, pstAttr->u8Msb, pstAttr->u8SourceMode, \
              pstAttr->u8OutputMode);

    return HI_FAILURE;
}

static HI_S32 DRV_PQ_CheckChipName(HI_CHAR* pchChipName)
{
    HI_S32 s32Ret = HI_FAILURE;
    PQ_CHECK_NULL_PTR(pchChipName);

#if defined(CHIP_TYPE_hi3716mv400)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3716M", strlen("HI_CHIP_TYPE_HI3716M"));
#elif defined(CHIP_TYPE_hi3716cv200)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3716C", strlen("HI_CHIP_TYPE_HI3716C"));
#elif defined(CHIP_TYPE_hi3718cv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3718C", strlen("HI_CHIP_TYPE_HI3718C"));
#elif defined(CHIP_TYPE_hi3718mv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3718M", strlen("HI_CHIP_TYPE_HI3718M"));
#elif defined(CHIP_TYPE_hi3719cv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3719C", strlen("HI_CHIP_TYPE_HI3719C"));
#elif defined(CHIP_TYPE_hi3719mv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3719M", strlen("HI_CHIP_TYPE_HI3719M"));
#elif defined(CHIP_TYPE_hi3796cv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3796C", strlen("HI_CHIP_TYPE_HI3796C"));
#elif defined(CHIP_TYPE_hi3798cv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3798C", strlen("HI_CHIP_TYPE_HI3798C"));
#elif defined(CHIP_TYPE_hi3798mv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3798M", strlen("HI_CHIP_TYPE_HI3798M"));
#elif defined(CHIP_TYPE_hi3796mv100)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3796M", strlen("HI_CHIP_TYPE_HI3796M"));
#elif defined(CHIP_TYPE_hi3798cv200_a)
    s32Ret = strncmp(pchChipName , "HI_CHIP_TYPE_HI3798C_A", strlen("HI_CHIP_TYPE_HI3798C_A"));

#else
    HI_ERR_PQ("unknown Chip Type \r\n");
    return HI_FAILURE;
#endif

    if (0 != s32Ret)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

MODULE_LICENSE("GPL");

EXPORT_SYMBOL(DRV_PQ_UpdateVpssPQ);
EXPORT_SYMBOL(DRV_PQ_UpdateVdpPQ);
EXPORT_SYMBOL(DRV_PQ_UpdateVdpCSC);
EXPORT_SYMBOL(DRV_PQ_UpdateDCIWin);
EXPORT_SYMBOL(DRV_PQ_GetVpssScalerCoef);
EXPORT_SYMBOL(DRV_PQ_GetScalerCoef);
EXPORT_SYMBOL(DRV_PQ_GetWbcScalerCoef);
EXPORT_SYMBOL(DRV_PQ_GetWbcInfo);
EXPORT_SYMBOL(DRV_PQ_SetAlgCalcCfg);
//EXPORT_SYMBOL(DRV_PQ_SetDeiGlobalMotion);
EXPORT_SYMBOL(DRV_PQ_GetTnrGlobalMotion);
EXPORT_SYMBOL(DRV_PQ_GetAdaptiveDBStrength);
EXPORT_SYMBOL(DRV_PQ_GetCSCCoef);
EXPORT_SYMBOL(DRV_PQ_Get8BitCSCCoef);
EXPORT_SYMBOL(DRV_PQ_PfmdDetect);
EXPORT_SYMBOL(DRV_PQ_IfmdDect);
EXPORT_SYMBOL(DRV_PQ_GetDciHistgram);
EXPORT_SYMBOL(DRV_PQ_GetHDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_GetSDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetZme);
EXPORT_SYMBOL(DRV_PQ_SetVpssZme);
EXPORT_SYMBOL(DRV_PQ_SetHDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetSDPictureSetting);
EXPORT_SYMBOL(DRV_PQ_SetSplitBlockZme);
EXPORT_SYMBOL(DRV_PQ_ZME_2L_Check);



