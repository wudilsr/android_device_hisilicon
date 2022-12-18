/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_csc.c
  Version       : Initial Draft
  Author        : l00212594
  Created       : 2013/10/15
  Description   :

******************************************************************************/
#ifndef  __PQ_PLATFORM_BOOT__
#include <linux/slab.h>      /* kmalloc() */
#include <linux/string.h>    /* memcpy() */
#endif
#include "hi_type.h"
#include "hi_debug.h"
#include "pq_hal_csc.h"
#include "pq_mng_csc.h"
#include "pq_hal_comm.h"

static HI_U32 PQ_TRACE_RANGE = HI_LOG_LEVEL_ERROR;
static PICTURE_SETTING_S   sg_stSDPictureSetting = {128, 128, 128, 128};
static PICTURE_SETTING_S   sg_stHDPictureSetting = {128, 128, 128, 128};
static COLOR_TEMPERATURE_S sg_stColorTemp = {128, 128, 128, 128, 128, 128};
static COLOR_SPACE_S       sg_stCSCMode[HAL_DISP_LAYER_BUTT] =
{
//  {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE},//VP0
//  {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE},//VP1
    {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE},//V0
    {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE},//V1
    {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE},//V2
    {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE},//V3
    {OPTM_CS_eXvYCC_601, OPTM_CS_eXvYCC_601, HI_FALSE} //V4
};

/**
 \brief 获取CSC色彩空间转换;
 \attention \n
无

 \param[in] enDisplayId
 \param[out] *pstCscMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetCSCMode(HAL_DISP_LAYER_E enDisplayId, CSC_MODE_S* pstCscMode)
{
    return PQ_HAL_GetCSCMode(enDisplayId, pstCscMode);
}

/**
 \brief 设置CSC色彩空间转换;
 \attention \n
无

 \param[in] enDisplayId
 \param[in] *pstCscMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_SetCSCMode(HAL_DISP_LAYER_E enDisplayId, CSC_MODE_S* pstCscMode)
{

    return PQ_MNG_SetCSC(enDisplayId, pstCscMode);
}

/**
 \brief 设置标清CSC图像设定;
 \attention \n
无

 \param[in] *pstPictureSetting;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_SetSDPictureSetting(PICTURE_SETTING_S* pstPictureSetting, COLOR_TEMPERATURE_S* pstColorTemp)
{
    CSC_PARA_S stV3CSCParameter;
    CSC_PARA_S stV4CSCParameter;

    if ((pstPictureSetting == NULL) || (pstColorTemp == NULL))
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstPictureSetting is Null poniter!\n");
        return HI_FAILURE;
    }

    sg_stSDPictureSetting.u16Brightness = pstPictureSetting->u16Brightness;
    sg_stSDPictureSetting.u16Contrast   = pstPictureSetting->u16Contrast;
    sg_stSDPictureSetting.u16Saturation = pstPictureSetting->u16Saturation;
    sg_stSDPictureSetting.u16Hue        = pstPictureSetting->u16Hue;
    sg_stColorTemp.s16RedGain     = pstColorTemp->s16RedGain;
    sg_stColorTemp.s16GreenGain   = pstColorTemp->s16GreenGain;
    sg_stColorTemp.s16BlueGain    = pstColorTemp->s16BlueGain;
    sg_stColorTemp.s16RedOffset   = pstColorTemp->s16RedOffset;
    sg_stColorTemp.s16GreenOffset = pstColorTemp->s16GreenOffset;
    sg_stColorTemp.s16BlueOffset  = pstColorTemp->s16BlueOffset;

    /* adjust brightness/contrast in V3/V4 CSC*/
    stV3CSCParameter.u16Brightness = sg_stSDPictureSetting.u16Brightness;
    stV3CSCParameter.u16Contrast   = sg_stSDPictureSetting.u16Contrast;
    stV3CSCParameter.u16Saturation = sg_stSDPictureSetting.u16Saturation;
    stV3CSCParameter.u16Hue        = sg_stSDPictureSetting.u16Hue;
    stV3CSCParameter.as16ColorTempGain[COLORTEMP_R]   = 128;
    stV3CSCParameter.as16ColorTempGain[COLORTEMP_G]   = 128;
    stV3CSCParameter.as16ColorTempGain[COLORTEMP_B]   = 128;
    stV3CSCParameter.as16ColorTempOffset[COLORTEMP_R] = 128;
    stV3CSCParameter.as16ColorTempOffset[COLORTEMP_G] = 128;
    stV3CSCParameter.as16ColorTempOffset[COLORTEMP_B] = 128;
    stV3CSCParameter.u16InputColorSpace  = sg_stCSCMode[HAL_DISP_LAYER_V3].u16InputColorSpace;
    stV3CSCParameter.u16OutputColorSpace = sg_stCSCMode[HAL_DISP_LAYER_V3].u16OutputColorSpace;
    stV3CSCParameter.bFullRange          = sg_stCSCMode[HAL_DISP_LAYER_V3].bFullRange;

    stV4CSCParameter.u16Brightness = sg_stSDPictureSetting.u16Brightness;
    stV4CSCParameter.u16Contrast   = sg_stSDPictureSetting.u16Contrast;
    stV4CSCParameter.u16Saturation = sg_stSDPictureSetting.u16Saturation;
    stV4CSCParameter.u16Hue        = sg_stSDPictureSetting.u16Hue;
    stV4CSCParameter.as16ColorTempGain[COLORTEMP_R]   = 128;
    stV4CSCParameter.as16ColorTempGain[COLORTEMP_G]   = 128;
    stV4CSCParameter.as16ColorTempGain[COLORTEMP_B]   = 128;
    stV4CSCParameter.as16ColorTempOffset[COLORTEMP_R] = 128;
    stV4CSCParameter.as16ColorTempOffset[COLORTEMP_G] = 128;
    stV4CSCParameter.as16ColorTempOffset[COLORTEMP_B] = 128;
    stV4CSCParameter.u16InputColorSpace  = sg_stCSCMode[HAL_DISP_LAYER_V4].u16InputColorSpace;
    stV4CSCParameter.u16OutputColorSpace = sg_stCSCMode[HAL_DISP_LAYER_V4].u16OutputColorSpace;
    stV4CSCParameter.bFullRange          = sg_stCSCMode[HAL_DISP_LAYER_V4].bFullRange;

    PQ_HAL_SetCSCPictureParam(HAL_DISP_LAYER_V3, &stV3CSCParameter);
    PQ_HAL_SetCSCPictureParam(HAL_DISP_LAYER_V4, &stV4CSCParameter);

    return HI_SUCCESS;
}

/**
 \brief 设置高清CSC图像设定;
 \attention \n
无

 \param[in] *pstPictureSetting;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_SetHDPictureSetting(PICTURE_SETTING_S* pstPictureSetting, COLOR_TEMPERATURE_S* pstColorTemp)
{
    //CSC_PARA_S stVP0CSCParameter;
    //CSC_PARA_S stVP1CSCParameter;
    CSC_PARA_S stV0CSCParameter;
    CSC_PARA_S stV1CSCParameter;

    if ((pstPictureSetting == NULL) || (pstColorTemp == NULL))
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstPictureSetting is Null poniter!\n");
        return HI_FAILURE;
    }

    sg_stHDPictureSetting.u16Brightness = pstPictureSetting->u16Brightness;
    sg_stHDPictureSetting.u16Contrast   = pstPictureSetting->u16Contrast;
    sg_stHDPictureSetting.u16Saturation = pstPictureSetting->u16Saturation;
    sg_stHDPictureSetting.u16Hue        = pstPictureSetting->u16Hue;
    sg_stColorTemp.s16RedGain     = pstColorTemp->s16RedGain;
    sg_stColorTemp.s16GreenGain   = pstColorTemp->s16GreenGain;
    sg_stColorTemp.s16BlueGain    = pstColorTemp->s16BlueGain;
    sg_stColorTemp.s16RedOffset   = pstColorTemp->s16RedOffset;
    sg_stColorTemp.s16GreenOffset = pstColorTemp->s16GreenOffset;
    sg_stColorTemp.s16BlueOffset  = pstColorTemp->s16BlueOffset;

    /* adjust brightness/contrast in V0/V1 CSC*/
    /* In 98M and CV200 HD Setting CSC at VP_0 and VP_1 */
    /* In 98C and HiFoneB2 HD Setting CSC at V0 and V1 */
    /* unified processed as V0 and V1, divide that at hal layer*/
    stV0CSCParameter.u16Brightness = sg_stHDPictureSetting.u16Brightness;
    stV0CSCParameter.u16Contrast   = sg_stHDPictureSetting.u16Contrast;
    stV0CSCParameter.u16Saturation = sg_stHDPictureSetting.u16Saturation;
    stV0CSCParameter.u16Hue        = sg_stHDPictureSetting.u16Hue;
    stV0CSCParameter.as16ColorTempGain[COLORTEMP_R]   = 128;
    stV0CSCParameter.as16ColorTempGain[COLORTEMP_G]   = 128;
    stV0CSCParameter.as16ColorTempGain[COLORTEMP_B]   = 128;
    stV0CSCParameter.as16ColorTempOffset[COLORTEMP_R] = 128;
    stV0CSCParameter.as16ColorTempOffset[COLORTEMP_G] = 128;
    stV0CSCParameter.as16ColorTempOffset[COLORTEMP_B] = 128;
    stV0CSCParameter.u16InputColorSpace  = sg_stCSCMode[HAL_DISP_LAYER_V0].u16InputColorSpace;
    stV0CSCParameter.u16OutputColorSpace = sg_stCSCMode[HAL_DISP_LAYER_V0].u16OutputColorSpace;
    stV0CSCParameter.bFullRange          = sg_stCSCMode[HAL_DISP_LAYER_V0].bFullRange;

    stV1CSCParameter.u16Brightness = sg_stHDPictureSetting.u16Brightness;
    stV1CSCParameter.u16Contrast   = sg_stHDPictureSetting.u16Contrast;
    stV1CSCParameter.u16Saturation = sg_stHDPictureSetting.u16Saturation;
    stV1CSCParameter.u16Hue        = sg_stHDPictureSetting.u16Hue;
    stV1CSCParameter.as16ColorTempGain[COLORTEMP_R]   = 128;
    stV1CSCParameter.as16ColorTempGain[COLORTEMP_G]   = 128;
    stV1CSCParameter.as16ColorTempGain[COLORTEMP_B]   = 128;
    stV1CSCParameter.as16ColorTempOffset[COLORTEMP_R] = 128;
    stV1CSCParameter.as16ColorTempOffset[COLORTEMP_G] = 128;
    stV1CSCParameter.as16ColorTempOffset[COLORTEMP_B] = 128;
    stV1CSCParameter.u16InputColorSpace  = sg_stCSCMode[HAL_DISP_LAYER_V1].u16InputColorSpace;
    stV1CSCParameter.u16OutputColorSpace = sg_stCSCMode[HAL_DISP_LAYER_V1].u16OutputColorSpace;
    stV1CSCParameter.bFullRange          = sg_stCSCMode[HAL_DISP_LAYER_V1].bFullRange;

    /*printk("u16Brightness=%d,u16Contrast=%d,u16Saturation=%d,u16Hue=%d\n", \
           sg_stHDPictureSetting.u16Brightness, \
           sg_stHDPictureSetting.u16Contrast, \
           sg_stHDPictureSetting.u16Saturation, \
           sg_stHDPictureSetting.u16Hue);*/

    PQ_HAL_SetCSCPictureParam(HAL_DISP_LAYER_V0, &stV0CSCParameter);
    PQ_HAL_SetCSCPictureParam(HAL_DISP_LAYER_V1, &stV1CSCParameter);

    return HI_SUCCESS;
}

/**
 \brief 获取CSC图像设定;
 \attention \n
无

 \param[out] *pstPictureSetting;
 \param[out] *pstColorTemp;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetSDPictureSetting(PICTURE_SETTING_S* pstPictureSetting, COLOR_TEMPERATURE_S* pstColorTemp)
{
    pstPictureSetting->u16Brightness = sg_stSDPictureSetting.u16Brightness;
    pstPictureSetting->u16Contrast   = sg_stSDPictureSetting.u16Contrast;
    pstPictureSetting->u16Hue        = sg_stSDPictureSetting.u16Hue;
    pstPictureSetting->u16Saturation = sg_stSDPictureSetting.u16Saturation;

    pstColorTemp->s16RedGain     = sg_stColorTemp.s16RedGain;
    pstColorTemp->s16GreenGain   = sg_stColorTemp.s16GreenGain;
    pstColorTemp->s16BlueGain    = sg_stColorTemp.s16BlueGain;
    pstColorTemp->s16RedOffset   = sg_stColorTemp.s16RedOffset;
    pstColorTemp->s16GreenOffset = sg_stColorTemp.s16GreenOffset;
    pstColorTemp->s16BlueOffset  = sg_stColorTemp.s16BlueOffset;

    return HI_SUCCESS;
}

/**
 \brief 获取高清CSC图像设定;
 \attention \n
无

 \param[out] *pstPictureSetting;
 \param[out] *pstColorTemp;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetHDPictureSetting(PICTURE_SETTING_S* pstPictureSetting, COLOR_TEMPERATURE_S* pstColorTemp)
{
    pstPictureSetting->u16Brightness = sg_stHDPictureSetting.u16Brightness;
    pstPictureSetting->u16Contrast   = sg_stHDPictureSetting.u16Contrast;
    pstPictureSetting->u16Hue        = sg_stHDPictureSetting.u16Hue;
    pstPictureSetting->u16Saturation = sg_stHDPictureSetting.u16Saturation;

    pstColorTemp->s16RedGain     = sg_stColorTemp.s16RedGain;
    pstColorTemp->s16GreenGain   = sg_stColorTemp.s16GreenGain;
    pstColorTemp->s16BlueGain    = sg_stColorTemp.s16BlueGain;
    pstColorTemp->s16RedOffset   = sg_stColorTemp.s16RedOffset;
    pstColorTemp->s16GreenOffset = sg_stColorTemp.s16GreenOffset;
    pstColorTemp->s16BlueOffset  = sg_stColorTemp.s16BlueOffset;

    return HI_SUCCESS;
}

/**
 \brief 设置CSC转换模式;
 \attention \n
无

 \param[in] enDisplayId
 \param[in] *pstCscMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_SetCSC(HAL_DISP_LAYER_E enDisplayId, CSC_MODE_S* pstCscMode)
{
    if (pstCscMode == NULL)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstCscMode is Null poniter!\n");
        return HI_FAILURE;
    }

    if (enDisplayId >= HAL_DISP_LAYER_BUTT)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "Error, Select Wrong CSC ID!\n");
        return HI_FAILURE;
    }

    /*配置色彩空间*/
    if (pstCscMode->enCSC == HAL_CSC_YUV2RGB_709)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eItu_R_BT_709;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eRGB;
    }
    else if (pstCscMode->enCSC == HAL_CSC_YUV2RGB_601)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eXvYCC_601;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eRGB;
    }
    else if (pstCscMode->enCSC == HAL_CSC_RGB2RGB)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eRGB;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eRGB;
    }
    else if (pstCscMode->enCSC == HAL_CSC_RGB2YUV_709)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eRGB;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eItu_R_BT_709;
    }
    else if (pstCscMode->enCSC == HAL_CSC_RGB2YUV_601)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eRGB;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eXvYCC_601;
    }
    else if (pstCscMode->enCSC == HAL_CSC_YUV2YUV)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eItu_R_BT_709;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eItu_R_BT_709;
    }
    else if (pstCscMode->enCSC == HAL_CSC_YUV2YUV_709_601)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eItu_R_BT_709;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eXvYCC_601;
    }
    else if (pstCscMode->enCSC == HAL_CSC_YUV2YUV_601_709)
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eXvYCC_601;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eItu_R_BT_709;
    }
    else
    {
        sg_stCSCMode[enDisplayId].u16InputColorSpace  = OPTM_CS_eUnknown;
        sg_stCSCMode[enDisplayId].u16OutputColorSpace = OPTM_CS_eUnknown;
    }

    /*配置颜色范围*/
    if (pstCscMode->enCSC >= HAL_CSC_YUV2RGB_601_FULL && pstCscMode->enCSC <= HAL_CSC_RGB2YUV_709_FULL)
    {
        sg_stCSCMode[enDisplayId].bFullRange = HI_TRUE;
    }
    else
    {
        sg_stCSCMode[enDisplayId].bFullRange = HI_FALSE;
    }

    PQ_HAL_SetCSCMode(enDisplayId, pstCscMode->enCSC);
    PQ_HAL_EnableCSC(enDisplayId, pstCscMode->bCSCEn);

    /*reload picture setting for DTV request*/
    if (pstCscMode->bCSCEn == HI_TRUE)
    {
        PQ_MNG_SetSDPictureSetting(&sg_stSDPictureSetting, &sg_stColorTemp);
        PQ_MNG_SetHDPictureSetting(&sg_stHDPictureSetting, &sg_stColorTemp);
    }
    return HI_SUCCESS;
}

