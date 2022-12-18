/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq.h
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/04/01
  Description   :

******************************************************************************/

#ifndef __DRV_PQ_H__
#define __DRV_PQ_H__

#include "hi_osal.h"
#include "hi_debug.h"
#include "hi_type.h"

#include "hi_drv_pq.h"
#include "hi_drv_proc.h"
#include "hi_drv_mem.h"
#include "hi_drv_mmz.h"
#include "hi_drv_module.h"

#include "pq_mng_acm.h"
//#include "pq_mng_nr.h"
#include "pq_mng_sharpen.h"
#include "pq_mng_csc.h"
#include "pq_mng_dei.h"
#include "pq_mng_dci.h"
#include "pq_mng_scaler.h"
#include "pq_mng_ifmd.h"
//#include "pq_mng_pfmd.h"
#include "pq_mng_sr.h"
#include "pq_mng_pq_table.h"
#include "pq_mng_ua.h"

#include "pq_hal_comm.h"
#include "pq_hal_acm.h"
#include "pq_hal_dci.h"
#include "pq_hal_sharpen.h"
#include "pq_hal_sr.h"
//#include "pq_hal_fmd.h"
#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
#include "pq_mng_dbdr_98m.h"
#else
#include "pq_mng_dbdr.h"
#endif




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define PQ_NAME            "HI_PQ"

#define NUM2LEVEL(Num)   ((Num) * 100 + 127) / 255
#define LEVEL2NUM(Level) ((Level) * 255 + 50) / 100

/*�û�PQ ���ݽṹ*/
typedef struct  hiDRV_PQ_PARAM_S
{
    PICTURE_SETTING_S   stSDPictureSetting;
    PICTURE_SETTING_S   stHDPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;
    HI_PQ_DCI_WIN_S     stDciWin;
    HI_U32  u32NRLevel;
    HI_U32  u32Sharpness;
    HI_U32  u32DBLevel;
    HI_U32  u32DRLevel;
    HI_U32  u32ColorGainLevel;
    HI_U32  u32DCILevelGain;
    HI_U32  u323dSharpen;
    HI_U32  u32NrAuto;
    HI_BOOL bDemoOnOff[HI_PQ_DEMO_BUTT];
    HI_BOOL bModuleOnOff[HI_PQ_MODULE_BUTT];
    HI_PQ_COLOR_ENHANCE_S stColorEnhance;
} HI_DRV_PQ_PARAM_S;


/**
 \brief ȥ��ʼ���ͻ�PQģ��;
 \attention \n
  ��

 \param[in]

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Comsumer_DeInit(HI_VOID);

/**
 \brief ��ʼ���ͻ�PQģ��;
 \attention \n
  ��

 \param[in] pszPath: PQ Table�ļ�·��, ���pszPath����Ϊ��ָ��, �����PQ SDK�ڲ�Ĭ�ϲ���;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Comsumer_Init(HI_CHAR* pszPath);

/**
 \brief ��ʾPQ״̬��Ϣ
 \attention \n
��

 \param[in] *s;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_ProcRead(struct seq_file* s, HI_VOID* data);

/**
 \brief ��ȡ��������
 \attention \n
��

 \param[out] pu32Brightness ����ֵ,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDBrightness(HI_U32* pu32Brightness);

/**
 \brief ���ñ�������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDBrightness(HI_U32 u32Brightness);

/**
 \brief ��ȡ����Աȶ�
 \attention \n
��

 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDContrast(HI_U32* pu32Contrast);

/**
 \brief ���ñ���Աȶ�
 \attention \n
��

 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDContrast(HI_U32 u32Contrast);

/**
 \brief ��ȡ����ɫ��
 \attention \n
��

 \param[out] pu32Hue  ɫ��, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDHue(HI_U32* pu32Hue);

/**
 \brief ���ñ���ɫ��
 \attention \n
��

 \param[in] u32Hue   ɫ��, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDHue(HI_U32 u32Hue);

/**
 \brief ��ȡ���履�Ͷ�
 \attention \n
��

 \param[out] pu32Saturation  ���Ͷ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDSaturation(HI_U32* pu32Saturation);

/**
 \brief ���ñ��履�Ͷ�
 \attention \n
��

 \param[in] u32Saturation ���Ͷ�,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDSaturation(HI_U32 u32Saturation);

/**
 \brief ��ȡ��������
 \attention \n
��

 \param[out] pu32Brightness ����ֵ,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDBrightness(HI_U32* pu32Brightness);

/**
 \brief ���ø�������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDBrightness(HI_U32 u32Brightness);

/**
 \brief ��ȡ����Աȶ�
 \attention \n
��

 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDContrast(HI_U32* pu32Contrast);

/**
 \brief ���ø���Աȶ�
 \attention \n
��

 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDContrast(HI_U32 u32Contrast);

/**
 \brief ��ȡ����ɫ��
 \attention \n
��

 \param[out] pu32Hue  ɫ��, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDHue(HI_U32* pu32Hue);

/**
 \brief ���ø���ɫ��
 \attention \n
��

 \param[in] u32Hue   ɫ��, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDHue(HI_U32 u32Hue);

/**
 \brief ��ȡ���履�Ͷ�
 \attention \n
��

 \param[out] pu32Saturation  ���Ͷ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDSaturation(HI_U32* pu32Saturation);

/**
 \brief ���ø��履�Ͷ�
 \attention \n
��

 \param[in] u32Saturation ���Ͷ�,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDSaturation(HI_U32 u32Saturation);

/**
 \brief ��ȡ������
 \attention \n
��

 \param[out] pu32Sharpness  ������, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSharpness(HI_U32* pu32Sharpness);

/**
 \brief ����������
 \attention \n
��

 \param[in] u32Sharpness, ������, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSharpness(HI_U32 u32Sharpness);


/**
 \brief ��ȡɫ�²���
 \attention \n
��

 \param[in] pstColorTemp: ɫ������

 \retval::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetColorTemp(HI_PQ_COLOR_TEMP_S* pstColorTemp);

/**
 \brief ����ɫ�²���
 \attention \n
��

 \param[out] pstColorTemp: ɫ������

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetColorTemp(HI_PQ_COLOR_TEMP_S* pstColorTemp);

/**
 \brief ��ȡ����ǿ��
 \attention \n
��

 \param[out] pu32NRLevel: ����ȼ�, ��Ч��Χ: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetNRLevel(HI_U32* pu32NRLevel);



/**
 \brief ��ȡ�齵��De-blockingǿ��
 \attention \n
��

 \param[out] *pu32DBLevel: ����ȼ�, ��Ч��Χ: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetDeBlocking(HI_U32* pu32DBLevel);

/**
 \brief ���ÿ齵��de-blockingǿ��
 \attention \n
��

 \param[in] u32DBLevel: ����ȼ�, ��Ч��Χ: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDeBlocking(HI_U32 u32DBLevel);

/**
 \brief ��ȡȥ����de-ringingǿ��
 \attention \n
��

 \param[out] *pu32DBLevel: ����ȼ�, ��Ч��Χ: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetDeRinging(HI_U32* pu32DRLevel);

/**
 \brief ����ȥ����de-ringingǿ��
 \attention \n
��

 \param[in] u32DBLevel: ����ȼ�, ��Ч��Χ: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDeRinging(HI_U32 u32DRLevel);

/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
��

 \param[out] pu32ColorGainLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetColorEhance(HI_U32* pu32ColorGainLevel);

/**
 \brief ������ɫ��ǿ
 \attention \n
��

 \param[in] u32ColorGainLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetColorEhance(HI_U32 u32ColorGainLevel);

/**
 \brief ��ȡ��ɫ��ǿ
 \attention \n
  ��

 \param[out] pu32FleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetFleshToneLevel(HI_U32* pu32FleshToneLevel);

/**
 \brief ���÷�ɫ��ǿ
 \attention \n
  ��

 \param[in] enFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetFleshToneLevel(HI_PQ_FLESHTONE_E enFleshToneLevel);

/**
 \brief ����DCIǿ������ȼ�
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDCILevelGain(HI_U32 u32DCILevelGain);

/**
 \brief ����DCI��������
 \attention \n
��

 \param[in] pstDciCoef;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDCIWgtLut(DCI_WGT_S* pstDciCoef);

/**
 \brief ��ȡNR �Զ�����״̬
 \attention \n
  ��

 \param[out] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetNrAutoMode(HI_U32* pu32OnOff);

/**
 \brief ����NR�Զ�����
 \attention \n
  ��

 \param[in] u32OnOff ����

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetNrAutoMode(HI_U32 u32OnOff);

/**
 \brief ��ȡ3D Sharpness ģʽ״̬
 \attention \n
  ��

 \param[out] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_Get3DSharpMode(HI_U32* pu32OnOff);

/**
 \brief ����3D Sharpness ģʽ
 \attention \n
  ��

 \param[in] u32OnOff ����

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_Set3DSharpMode(HI_U32 u32OnOff);

/**
 \brief ��ȡ��ͨ����CSC(���ڵ���)
 \attention \n
��

 \param[in] enDisplayId
 \param[out] pstCSCMode

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetCSCMode(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S* pstCSCMode);


/**
 \brief ��������ģʽ����
 \attention \n
��

 \param[in] enFlags

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDemoMode(HI_PQ_DEMO_E enFlags, HI_BOOL bOnOff);

/**
 \brief ��ȡPQģ�鿪��״̬
 \attention \n
  ��

 \param[in] enFlags
 \param[out] *pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetPQModule(HI_PQ_MODULE_E enFlags, HI_U32* pu32OnOff);

/**
 \brief ����PQģ�鿪��
 \attention \n
  ��

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetPQModule(HI_PQ_MODULE_E enFlags, HI_U32 u32OnOff);

/**
 \brief ��ȡSR��ʾģʽ����
 \attention \n
��

 \param[in] ps32Type

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSRMode(HI_S32* ps32Type);

/**
 \brief ����SR��ʾģʽ����
 \attention \n
��

 \param[in] eSRMode: SR��ʾģʽ0-ֻZME;1-�ұ�SR��2-���SR��3-SR��

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSRMode(HI_PQ_SR_DEMO_E eSRMode);

/**
 \brief ��ȡPQBin �������ַ
 \attention \n
��

 \param[in] pu32Addr:

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetBinPhyAddr(HI_U32* pu32Addr);

/**
 \brief ����ACM ��Luma ���߲��ұ�
 \attention \n
��

 \param[in] pstAttr:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAcmLuma(HI_PQ_ACM_LUT_S* pstAttr);

/**
 \brief ����ACM ��Hue ���߲��ұ�
 \attention \n
��

 \param[in] pstAttr:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAcmHue(HI_PQ_ACM_LUT_S* pstAttr);

/**
 \brief ����ACM ��Sat ���߲��ұ�
 \attention \n
��

 \param[in] pstAttr:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAcmSat(HI_PQ_ACM_LUT_S* pstAttr);

/**
 \brief ����ɫ��������
 \attention \n
  ��

 \param[in] enSixColorType;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSixBaseColorLevel(HI_PQ_SIX_BASE_S* pstSixBaseColorOffset);

/**
 \brief ��ɫ��ǿģʽ����
 \attention \n
  ��

 \param[in] enColorSpecMode 0-RECOMMEND;1-BLUE;2-GREEN;3-BG;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetColorEnhanceMode(HI_PQ_COLOR_SPEC_MODE_E enColorSpecMode);


HI_S32 DRV_PQ_SetReg(HI_PQ_REGISTER_S* pstAttr);

HI_S32 DRV_PQ_GetReg(HI_PQ_REGISTER_S* pstAttr);

HI_S32 DRV_PQ_GetPqParam(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_PQ_H__ */
