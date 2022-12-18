/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : hi_unf_pq.c
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/04/01
  Description   : UNF���װ����

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hi_type.h"
#include "hi_unf_pq.h"
#include "hi_mpi_pq.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**
 \brief ��ʼ��PQ
 \attention \n
��

 \param[in] pszPath:PQ�����ļ�·��

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_Init(HI_VOID)
{
    HI_CHAR* pszPath = HI_NULL;
    return HI_MPI_PQ_Init(pszPath);
}


/**
 \brief ȥ��ʼ��PQ
 \attention \n
��

 \param[in] none

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_DeInit(HI_VOID)
{
    return HI_MPI_PQ_DeInit();
}


/**
 \brief Set PQ mode . CNcomment: ����ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[in] enImageMode Destination DISP channel PQ mode CNcomment: Ŀ��ͨ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode)
{

    return HI_SUCCESS;
}


/**
 \brief Get PQ mode . CNcomment: ��ȡͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_GetImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E* penImageMode)
{
    MPI_PQ_CHECK_NULL_PTR(penImageMode);

    return HI_SUCCESS;
}


/**
 \brief Init PQ mode . CNcomment: ��ʼ��ͼ��ģʽ CNend
 \attention \n
 \param[in] enChan Destination DISP channel CNcomment: Ŀ��ͨ���� CNend
 \param[out] penImageMode  pointer of image mode CNcomment: ָ�����ͣ�ָ��ͼ��ģʽ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_InitImageMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_MODE_E enImageMode)
{

    return HI_SUCCESS;
}


/**
 \brief Set channel option. CNcomment: ����ͨ��optionֵ CNend
 \attention \n
 \param[in] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_SetChanOption(const HI_UNF_PQ_OPT_CHANS_S* pstChanOption)
{
    HI_UNF_DISP_E enChan;

    MPI_PQ_CHECK_NULL_PTR(pstChanOption);

    enChan = pstChanOption->enChan;

    HI_MPI_PQ_SetBrightness((HI_DRV_DISPLAY_E)enChan, pstChanOption->stChanOpt.u32Brightness );
    HI_MPI_PQ_SetContrast((HI_DRV_DISPLAY_E)enChan, pstChanOption->stChanOpt.u32Contrast );
    HI_MPI_PQ_SetHue((HI_DRV_DISPLAY_E)enChan, pstChanOption->stChanOpt.u32Hue);
    HI_MPI_PQ_SetSaturation((HI_DRV_DISPLAY_E)enChan, pstChanOption->stChanOpt.u32Saturation);

    return HI_SUCCESS;
}


/**
 \brief Set channel option. CNcomment: ��ȡͨ��optionֵ CNend
 \attention \n
 \param[out] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_GetChanOption(HI_UNF_PQ_OPT_CHANS_S* pstChanOption)
{
    HI_UNF_DISP_E enChan;
    HI_U32 u32Brightness = 0;
    HI_U32 u32Contrast = 0;
    HI_U32 u32Hue = 0;
    HI_U32 u32Saturation = 0;

    MPI_PQ_CHECK_NULL_PTR(pstChanOption);

    enChan = pstChanOption->enChan;

    HI_MPI_PQ_GetBrightness((HI_DRV_DISPLAY_E)enChan, &u32Brightness);
    HI_MPI_PQ_GetContrast((HI_DRV_DISPLAY_E)enChan, &u32Contrast);
    HI_MPI_PQ_GetHue((HI_DRV_DISPLAY_E)enChan, &u32Hue);
    HI_MPI_PQ_GetSaturation((HI_DRV_DISPLAY_E)enChan, &u32Saturation);

    pstChanOption->stChanOpt.u32Brightness = u32Brightness;
    pstChanOption->stChanOpt.u32Contrast = u32Contrast;
    pstChanOption->stChanOpt.u32Hue = u32Hue;
    pstChanOption->stChanOpt.u32Saturation = u32Saturation;
    pstChanOption->stChanOpt.u32Colortemperature = 0;
    pstChanOption->stChanOpt.u32GammaMode = 0;
    pstChanOption->stChanOpt.u32DynamicContrast = 0;
    pstChanOption->stChanOpt.u32IntelligentColor = 0;

    return HI_SUCCESS;
}


/**
 \brief Set channel common option. CNcomment: ����ͨ�� common optionֵ CNend
 \attention \n
 \param[in] pstCommOption pointer of channel common option CNcomment: ָ�����ͣ�ָ��ͨ��common optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_SetCommOption(const HI_UNF_PQ_OPT_COMMON_S* pstCommOption)
{
    MPI_PQ_CHECK_NULL_PTR(pstCommOption);

    return HI_MPI_PQ_SetSharpness(pstCommOption->u32Sharpeness);
}


/**
 \brief Set channel option. CNcomment: ��ȡͨ��common optionֵ CNend
 \attention \n
 \param[out] pstChanOption pointer of channel option CNcomment: ָ�����ͣ�ָ��ͨ��common optionֵ CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_GetCommOption(HI_UNF_PQ_OPT_COMMON_S* pstCommOption)
{
    HI_S32 s32Ret;
    HI_U32 u32Sharpness = 0;

    MPI_PQ_CHECK_NULL_PTR(pstCommOption);

    s32Ret = HI_MPI_PQ_GetSharpness(&u32Sharpness);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    pstCommOption->u32Sharpeness = u32Sharpness;
    pstCommOption->u32Denoise = 0;
    pstCommOption->u32FilmMode = 0;

    return s32Ret;
}



/**
 \brief Modifies the basic configuration information.  CNcomment:����PQ��������Ϣ CNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
 N/A CNcomment: �� CNend
 */

HI_S32 HI_UNF_PQ_UpdatePqParam(HI_VOID)
{

    return HI_SUCCESS;
}


/**
 \brief Set the default PQ configuration for video parameter test.  CNcomment: Ϊ����ָ���������PQ ��Ĭ��ֵCNend
 \attention \n
 \param[in] N/A CNcomment: �� CNend
 \retval ::HI_SUCCESS Success CNcomment: �ɹ� CNend
 \see \n
 N/A CNcomment: �� CNend
 */
HI_S32 HI_UNF_PQ_SetDefaultParam(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 u32OnOff = 0;

    s32Ret = HI_MPI_PQ_SetBrightness(HI_DRV_DISPLAY_0, 50);
    s32Ret |= HI_MPI_PQ_SetBrightness(HI_DRV_DISPLAY_1, 50);
    s32Ret |= HI_MPI_PQ_SetContrast(HI_DRV_DISPLAY_0, 50);
    s32Ret |= HI_MPI_PQ_SetContrast(HI_DRV_DISPLAY_1, 50);
    s32Ret |= HI_MPI_PQ_SetSaturation(HI_DRV_DISPLAY_0, 50);
    s32Ret |= HI_MPI_PQ_SetSaturation(HI_DRV_DISPLAY_1, 50);
    s32Ret |= HI_MPI_PQ_SetHue(HI_DRV_DISPLAY_0, 50);
    s32Ret |= HI_MPI_PQ_SetHue(HI_DRV_DISPLAY_1, 50);

    s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_SHARPNESS, u32OnOff);
    s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_DCI, u32OnOff);
    s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_COLOR, u32OnOff);
    s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_SR, u32OnOff);

    return s32Ret;
}

/**
 \brief ��ȡ����
 \attention \n
��

 \param[in] pu32Brightness ����ֵ,��Ч��Χ: 0~100;
 \param[out]

 \retval ::HI_SUCCESS

 */
HI_S32 HI_UNF_PQ_GetBrightness(HI_UNF_DISP_E enChan, HI_U32* pu32Brightness)
{
    HI_S32 s32Ret;
    HI_U32 u32Brightness = 0;

    MPI_PQ_CHECK_NULL_PTR(pu32Brightness);

    s32Ret = HI_MPI_PQ_GetBrightness((HI_DRV_DISPLAY_E)enChan, &u32Brightness);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    *pu32Brightness = u32Brightness;
    return s32Ret;
}

/**
 \brief ��������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetBrightness(HI_UNF_DISP_E enChan, HI_U32 u32Brightness)
{
    if ( u32Brightness > 100)
    {
        HI_ERR_PQ("The brightness is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetBrightness((HI_DRV_DISPLAY_E)enChan, u32Brightness);
}


/**
 \brief ��ȡ�Աȶ�
 \attention \n
��

 \param[in]
 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetContrast(HI_UNF_DISP_E enChan, HI_U32* pu32Contrast)
{
    HI_S32 s32Ret;
    HI_U32 u32Contrast = 0;

    MPI_PQ_CHECK_NULL_PTR(pu32Contrast);

    s32Ret = HI_MPI_PQ_GetContrast((HI_DRV_DISPLAY_E)enChan, &u32Contrast);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    *pu32Contrast = u32Contrast;
    return s32Ret;
}

/**
 \brief ���öԱȶ�
 \attention \n
��

 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetContrast(HI_UNF_DISP_E enChan, HI_U32 u32Contrast)
{
    if ( u32Contrast > 100)
    {
        HI_ERR_PQ("The Contrast is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetContrast((HI_DRV_DISPLAY_E)enChan, u32Contrast);
}

/**
 \brief ��ȡɫ��
 \attention \n
��

 \param[in]
 \param[out] pu32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetHue(HI_UNF_DISP_E enChan, HI_U32* pu32Hue)
{
    HI_S32 s32Ret;
    HI_U32 u32Hue = 0;

    MPI_PQ_CHECK_NULL_PTR(pu32Hue);

    s32Ret = HI_MPI_PQ_GetHue((HI_DRV_DISPLAY_E)enChan, &u32Hue);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    *pu32Hue = u32Hue;
    return s32Ret;
}

/**
 \brief ����ɫ��
 \attention \n
��

 \param[in] u32Hue��ɫ��, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetHue(HI_UNF_DISP_E enChan, HI_U32 u32Hue)
{
    if ( u32Hue > 100)
    {
        HI_ERR_PQ("The Hue level is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetHue((HI_DRV_DISPLAY_E)enChan, u32Hue);
}

/**
 \brief ����ͼ���������
 \attention \n
��
 \param[in] enType: Graph or Video  CNcomment: ���õ���ͼ�λ�����Ƶ CNend
 \param[in] enChan: Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[in] stParam:Basic Image Param CNcomment:ͼ���������CNend


 \retval ::HI_SUCCESS CNcomment: �ɹ� CNend

 */


HI_S32 HI_UNF_PQ_SetBasicImageParam(HI_UNF_PQ_IMAGE_TYPE_E enType, HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_PARAM_S stParam)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_PQ_IMAGE_PARAM_S stImageParam;

    stImageParam.u16Brightness = stParam.u32Brightness;
    stImageParam.u16Contrast   = stParam.u32Contrast;
    stImageParam.u16Hue        = stParam.u32Hue;
    stImageParam.u16Saturation = stParam.u32Saturation;

    s32Ret = HI_MPI_PQ_SetBasicImageParam((HI_MPI_PQ_IMAGE_TYPE_E)enType, (HI_DRV_DISPLAY_E)enChan, stImageParam);

    return s32Ret;
}

/**
 \brief ��ȡͼ���������
 \attention \n
��
 \param[in] enType: Graph or Video  CNcomment: ѡ�����ͼ�λ�����Ƶ CNend
 \param[in] enChan: Destination DISP channel  CNcomment: Ŀ��ͨ���� CNend
 \param[in] pstParam:Basic Image Param CNcomment:ͼ��������� CNend


 \retval ::HI_SUCCESS CNcomment: �ɹ� CNend

 */


HI_S32 HI_UNF_PQ_GetBasicImageParam(HI_UNF_PQ_IMAGE_TYPE_E enType, HI_UNF_DISP_E enChan, HI_UNF_PQ_IMAGE_PARAM_S* pstParam)
{
    HI_S32 s32Ret;
    HI_PQ_IMAGE_PARAM_S stImageParam = {0};

    MPI_PQ_CHECK_NULL_PTR(pstParam);

    s32Ret = HI_MPI_PQ_GetBasicImageParam((HI_MPI_PQ_IMAGE_TYPE_E)enType, (HI_DRV_DISPLAY_E)enChan, &stImageParam);

    pstParam->u32Brightness = stImageParam.u16Brightness;
    pstParam->u32Contrast   = stImageParam.u16Contrast;
    pstParam->u32Hue        = stImageParam.u16Hue;
    pstParam->u32Saturation = stImageParam.u16Saturation;

    return s32Ret;
}

/**
 \brief ��ȡ���Ͷ�
 \attention \n
��

 \param[out] pu32Saturation�����Ͷ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetSaturation(HI_UNF_DISP_E enChan, HI_U32* pu32Saturation)
{
    HI_S32 s32Ret;
    HI_U32 u32Saturation = 0;

    MPI_PQ_CHECK_NULL_PTR(pu32Saturation);

    s32Ret = HI_MPI_PQ_GetSaturation((HI_DRV_DISPLAY_E)enChan, &u32Saturation);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *pu32Saturation = u32Saturation;
    return s32Ret;
}

/**
 \brief ���ñ��Ͷ�
 \attention \n
��

 \param[in] u32Saturation�����Ͷ�,��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetSaturation(HI_UNF_DISP_E enChan, HI_U32 u32Saturation)
{
    if ( u32Saturation > 100)
    {
        HI_ERR_PQ("The Saturation level is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetSaturation((HI_DRV_DISPLAY_E)enChan, u32Saturation);
}

/**
 \brief ��ȡ����ǿ��
 \attention \n
��

 \param[out] pu32NRLevel: ����ȼ�, ��Ч��Χ: 0~100


 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetNR(HI_UNF_DISP_E enChan, HI_U32* pu32NRLevel)
{
    MPI_PQ_CHECK_NULL_PTR(pu32NRLevel);

    return HI_MPI_PQ_GetTNR(pu32NRLevel);
}

/**
 \brief ���ý���ǿ��
 \attention \n
��

 \param[in] u32NRLevel: ����ȼ�, ��Ч��Χ: 0~100

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetNR(HI_UNF_DISP_E enChan, HI_U32 u32NRLevel)
{
    if ( u32NRLevel > 100)
    {
        HI_ERR_PQ("The NR level is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetTNR(u32NRLevel);
}

/**
 \brief ��ȡ�Զ����뿪��״̬
 \attention \n
��

 \param[out] pu32OnOff


 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetNRAutoMode(HI_UNF_DISP_E enChan, HI_U32* pu32OnOff)
{
    if ( NULL == pu32OnOff)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_GetNRAutoMode(pu32OnOff);
}

/**
 \brief ���ý����Զ�ģʽ����
 \attention \n
��

 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetNRAutoMode(HI_UNF_DISP_E enChan, HI_U32 u32OnOff)
{
    return HI_MPI_PQ_SetNRAutoMode(u32OnOff);
}

/**
 \brief ��ȡSR��ʾ����
 \attention \n
��

 \param[out] *penType


 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E* penType)
{
    MPI_PQ_CHECK_NULL_PTR(penType);


    return HI_MPI_PQ_GetSRMode((HI_PQ_SR_DEMO_E*)penType);
}

/**
 \brief ����SR��ʾ����
 \attention \n
��

 \param[in] enType

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetSRMode(HI_UNF_DISP_E enChan, HI_UNF_PQ_SR_DEMO_E enType)
{
    return HI_MPI_PQ_SetSRMode((HI_PQ_SR_DEMO_E)enType);
}

/**
 \brief ��ȡ������
 \attention \n
��

 \param[out] pu32Sharpness��������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetSharpness(HI_UNF_DISP_E enChan, HI_U32* pu32Sharpness)
{
    HI_S32 s32Ret;
    HI_U32 u32Sharpness = 0;

    MPI_PQ_CHECK_NULL_PTR(pu32Sharpness);

    s32Ret = HI_MPI_PQ_GetSharpness(&u32Sharpness);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    *pu32Sharpness = u32Sharpness;
    return s32Ret;
}

/**
 \brief ����������
 \attention \n
��

 \param[in] u32Sharpness��������, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetSharpness(HI_UNF_DISP_E enChan, HI_U32 u32Sharpness)
{
    if ( u32Sharpness > 100)
    {
        HI_ERR_PQ("The Sharpness level is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetSharpness(u32Sharpness);
}

/**
 \brief ��ȡ�齵��De-blockingǿ��
 \attention \n
��

 \param[out] pu32DBlevel������ȼ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetDeBlocking(HI_UNF_DISP_E enChan, HI_U32* pu32DBlevel)
{
    if ( NULL == pu32DBlevel)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_GetDeBlocking(pu32DBlevel);
}

/**
 \brief ���ÿ齵��De-blockingǿ��
 \attention \n
��

 \param[in] u32DBlevel:����ȼ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDeBlocking(HI_UNF_DISP_E enChan, HI_U32 u32DBlevel)
{
    if ( u32DBlevel > 255)
    {
        HI_ERR_PQ("The DB level is out of range!");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetDeBlocking(u32DBlevel);
}

/**
 \brief ��ȡȥ���ó�����de-ringingǿ��
 \attention \n
��

 \param[out] pu32DRlevel:����ȼ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetDeRinging(HI_UNF_DISP_E enChan, HI_U32* pu32DRlevel)
{
    if ( NULL == pu32DRlevel)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_GetDeRinging(pu32DRlevel);
}


/**
 \brief ����ȥ���ó�����de-ringingǿ��
 \attention \n
��

 \param[in] u32DRlevel:����ȼ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDeRinging(HI_UNF_DISP_E enChan, HI_U32 u32DRlevel)
{
    if ( u32DRlevel > 255)
    {
        HI_ERR_PQ("The DR level is out of range!");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetDeRinging(u32DRlevel);
}


/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
��

 \param[out] pu32ColorGainLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetColorGain(HI_UNF_DISP_E enChan, HI_U32* pu32ColorGainLevel)
{
    HI_S32 s32Ret;
    HI_U32 u32ColorGainLevel = 0;

    MPI_PQ_CHECK_NULL_PTR(pu32ColorGainLevel);

    s32Ret = HI_MPI_PQ_GetColorGain(&u32ColorGainLevel);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }

    *pu32ColorGainLevel = u32ColorGainLevel;
    return s32Ret;
}

/**
 \brief ������ɫ��ǿ
 \attention \n
��

 \param[in] enColorGainLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetColorGain(HI_UNF_DISP_E enChan, HI_U32 u32ColorGainLevel)
{
    if ( u32ColorGainLevel > 100)
    {
        HI_ERR_PQ("The ColorGain level is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetColorGain(u32ColorGainLevel);
}

/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
  ��

 \param[out] pu32FleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetFleshTone(HI_UNF_DISP_E enChan, HI_UNF_PQ_FLESHTONE_E* pu32FleshToneLevel)
{
    MPI_PQ_CHECK_NULL_PTR(pu32FleshToneLevel);

    return HI_MPI_PQ_GetFleshTone(pu32FleshToneLevel);
}

/**
 \brief ���÷�ɫ��ǿ
 \attention \n
  ��

 \param[in] enFleshToneLevel���ο�HI_COLOR_GAIN_E

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetFleshTone(HI_UNF_DISP_E enChan, HI_UNF_PQ_FLESHTONE_E enFleshToneLevel)
{
    if ( enFleshToneLevel >= HI_UNF_PQ_FLESHTONE_GAIN_BUTT)
    {
        HI_ERR_PQ("The FleshTone level is out of range!\n");

        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetFleshTone(enFleshToneLevel);
}

/**
 \brief ��ȡPQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32* pu32OnOff)
{
    MPI_PQ_CHECK_NULL_PTR(pu32OnOff);

    if (enFlags >= HI_UNF_PQ_MODULE_BUTT)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_GetPQModule(enFlags, pu32OnOff);
}

/**
 \brief ����PQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetPQModule( HI_UNF_PQ_MODULE_E enFlags, HI_U32 u32OnOff)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_UNF_PQ_MODULE_BUTT <= enFlags)
    {
        return HI_FAILURE;
    }

    if (HI_UNF_PQ_MODULE_ALL == enFlags)
    {
        s32Ret  = HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_SHARPNESS, u32OnOff);
        s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_DCI, u32OnOff);
        s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_COLOR, u32OnOff);
        s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_SR, u32OnOff);
        s32Ret |= HI_MPI_PQ_SetPQModule(HI_UNF_PQ_MODULE_TNR, u32OnOff);
    }
    else
    {
        s32Ret  = HI_MPI_PQ_SetPQModule(enFlags, u32OnOff);
    }

    return s32Ret;
}

/**
 \brief ��������ģʽ����
 \attention \n
��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDemo( HI_UNF_PQ_DEMO_E enFlags, HI_U32 u32OnOff)
{
    if (HI_UNF_PQ_DEMO_BUTT <= enFlags)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetDemo(enFlags, u32OnOff);
}

/**
 \brief ��������ģʽ��ʾ��ʽ
 \attention \n
��

 \param[in] enChan
 \param[in] enMode

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDemoMode( HI_UNF_DISP_E enChan, HI_UNF_PQ_DEMO_MODE_E enMode)
{
    return HI_MPI_PQ_SetDemoMode((HI_DRV_DISPLAY_E)enChan, (HI_PQ_DEMO_MODE_E)enMode);
}


/**
 \brief ��ȡ����ģʽ��ʾ��ʽ
 \attention \n
��

 \param[in] enChan
 \param[in] enMode

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetDemoMode( HI_UNF_DISP_E enChan, HI_UNF_PQ_DEMO_MODE_E* penMode)
{
    if (HI_NULL == penMode)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_GetDemoMode((HI_DRV_DISPLAY_E)enChan, (HI_PQ_DEMO_MODE_E*)penMode);
}

/**
 \brief ��ȡ��ɫ��ǿ�����ͺ�ǿ��
 \attention \n
��

 \param[out] pstColorEnhanceParam:��ɫ��ǿ�����ͺ�ǿ��;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S* pstColorEnhanceParam)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_UNF_PQ_COLOR_ENHANCE_E    enType;
    HI_UNF_PQ_FLESHTONE_E enFleshToneLevel = HI_UNF_PQ_FLESHTONE_GAIN_OFF;
    HI_UNF_PQ_SIX_BASE_S stSixBase = {0};
    HI_UNF_PQ_COLOR_SPEC_MODE_E enColorMode = HI_UNF_PQ_COLOR_MODE_RECOMMEND;

    MPI_PQ_CHECK_NULL_PTR(pstColorEnhanceParam);

    enType = pstColorEnhanceParam->enColorEnhanceType;

    if (HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE == enType)
    {
        s32Ret = HI_MPI_PQ_GetFleshTone(&enFleshToneLevel);
        if (HI_FAILURE == s32Ret )
        {
            return HI_FAILURE;
        }
        pstColorEnhanceParam->unColorGain.enFleshtone = enFleshToneLevel;
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE == enType)
    {
        s32Ret = HI_MPI_PQ_GetSixBaseColor(&stSixBase);
        if (HI_FAILURE == s32Ret )
        {
            return HI_FAILURE;
        }

        pstColorEnhanceParam->unColorGain.stSixBase = stSixBase;
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == enType)
    {
        s32Ret = HI_MPI_PQ_GetColorEnhanceMode(&enColorMode);
        if (HI_FAILURE == s32Ret )
        {
            return HI_FAILURE;
        }

        pstColorEnhanceParam->unColorGain.enColorMode = enColorMode;
    }

    return s32Ret;
}


/**
 \brief ������ɫ��ǿ�����ͺ�ǿ��
 \attention \n
��

 \param[out] enColorEnhanceType:��ɫ��ǿ�����ͺ�ǿ��;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetColorEnhanceParam(HI_UNF_PQ_COLOR_ENHANCE_S stColorEnhanceParam)
{
    HI_UNF_PQ_COLOR_ENHANCE_E    enType;
    enType = stColorEnhanceParam.enColorEnhanceType;
    HI_UNF_PQ_SIX_BASE_S stSixBaseColor;
    HI_UNF_PQ_COLOR_SPEC_MODE_E enColorSpecMode;

    if (HI_UNF_PQ_COLOR_ENHANCE_FLESHTONE == enType)
    {
        return HI_MPI_PQ_SetFleshTone(stColorEnhanceParam.unColorGain.enFleshtone);
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SIX_BASE == enType)
    {
        stSixBaseColor = stColorEnhanceParam.unColorGain.stSixBase;
        return HI_MPI_PQ_SetSixBaseColor((HI_PQ_SIX_BASE_COLOR_S*)&stSixBaseColor);
    }
    else if (HI_UNF_PQ_COLOR_ENHANCE_SPEC_COLOR_MODE == enType)
    {
        enColorSpecMode = stColorEnhanceParam.unColorGain.enColorMode;
        return HI_MPI_PQ_SetColorEnhanceMode((HI_PQ_COLOR_SPEC_MODE_E)enColorSpecMode);
    }

    return HI_FAILURE;
}


/**
 \brief ��ȡDCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ
 \attention \n
��

 \param[out] pu32DCIlevel:��̬�Աȶȵȼ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_GetDynamicContrast(HI_U32* pu32DCIlevel)
{
    MPI_PQ_CHECK_NULL_PTR(pu32DCIlevel);

    return HI_MPI_PQ_GetDciLevel(pu32DCIlevel);
}


/**
 \brief ����DCI����̬�Աȶ���ǿ����ǿ�ȷ�Χ
 \attention \n
��

 \param[in] u32DCIlevel:��̬�Աȶȵȼ�, ��Ч��Χ: 0~100;

 \retval ::HI_SUCCESS

 */

HI_S32 HI_UNF_PQ_SetDynamicContrast(HI_U32 u32DCIlevel)
{
    if (u32DCIlevel > 100)
    {
        return HI_FAILURE;
    }

    return HI_MPI_PQ_SetDciLevel(u32DCIlevel);
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

