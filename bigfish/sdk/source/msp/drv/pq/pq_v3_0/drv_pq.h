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

/*用户PQ 数据结构*/
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
 \brief 去初始化客户PQ模块;
 \attention \n
  无

 \param[in]

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Comsumer_DeInit(HI_VOID);

/**
 \brief 初始化客户PQ模块;
 \attention \n
  无

 \param[in] pszPath: PQ Table文件路径, 如果pszPath参数为空指针, 会采用PQ SDK内部默认参数;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_Comsumer_Init(HI_CHAR* pszPath);

/**
 \brief 显示PQ状态信息
 \attention \n
无

 \param[in] *s;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_ProcRead(struct seq_file* s, HI_VOID* data);

/**
 \brief 获取标清亮度
 \attention \n
无

 \param[out] pu32Brightness 亮度值,有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDBrightness(HI_U32* pu32Brightness);

/**
 \brief 设置标清亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDBrightness(HI_U32 u32Brightness);

/**
 \brief 获取标清对比度
 \attention \n
无

 \param[out] pu32Contrast 对比度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDContrast(HI_U32* pu32Contrast);

/**
 \brief 设置标清对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDContrast(HI_U32 u32Contrast);

/**
 \brief 获取标清色调
 \attention \n
无

 \param[out] pu32Hue  色调, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDHue(HI_U32* pu32Hue);

/**
 \brief 设置标清色调
 \attention \n
无

 \param[in] u32Hue   色调, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDHue(HI_U32 u32Hue);

/**
 \brief 获取标清饱和度
 \attention \n
无

 \param[out] pu32Saturation  饱和度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSDSaturation(HI_U32* pu32Saturation);

/**
 \brief 设置标清饱和度
 \attention \n
无

 \param[in] u32Saturation 饱和度,有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSDSaturation(HI_U32 u32Saturation);

/**
 \brief 获取高清亮度
 \attention \n
无

 \param[out] pu32Brightness 亮度值,有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDBrightness(HI_U32* pu32Brightness);

/**
 \brief 设置高清亮度
 \attention \n
无

 \param[in] u32Brightness, 亮度值,有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDBrightness(HI_U32 u32Brightness);

/**
 \brief 获取高清对比度
 \attention \n
无

 \param[out] pu32Contrast 对比度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDContrast(HI_U32* pu32Contrast);

/**
 \brief 设置高清对比度
 \attention \n
无

 \param[in] u32Contrast, 对比度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHDContrast(HI_U32 u32Contrast);

/**
 \brief 获取高清色调
 \attention \n
无

 \param[out] pu32Hue  色调, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDHue(HI_U32* pu32Hue);

/**
 \brief 设置高清色调
 \attention \n
无

 \param[in] u32Hue   色调, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDHue(HI_U32 u32Hue);

/**
 \brief 获取高清饱和度
 \attention \n
无

 \param[out] pu32Saturation  饱和度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHDSaturation(HI_U32* pu32Saturation);

/**
 \brief 设置高清饱和度
 \attention \n
无

 \param[in] u32Saturation 饱和度,有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetHDSaturation(HI_U32 u32Saturation);

/**
 \brief 获取清晰度
 \attention \n
无

 \param[out] pu32Sharpness  清晰度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSharpness(HI_U32* pu32Sharpness);

/**
 \brief 设置清晰度
 \attention \n
无

 \param[in] u32Sharpness, 清晰度, 有效范围: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSharpness(HI_U32 u32Sharpness);


/**
 \brief 获取色温参数
 \attention \n
无

 \param[in] pstColorTemp: 色温属性

 \retval::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetColorTemp(HI_PQ_COLOR_TEMP_S* pstColorTemp);

/**
 \brief 设置色温参数
 \attention \n
无

 \param[out] pstColorTemp: 色温属性

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetColorTemp(HI_PQ_COLOR_TEMP_S* pstColorTemp);

/**
 \brief 获取降噪强度
 \attention \n
无

 \param[out] pu32NRLevel: 降噪等级, 有效范围: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetNRLevel(HI_U32* pu32NRLevel);



/**
 \brief 获取块降噪De-blocking强度
 \attention \n
无

 \param[out] *pu32DBLevel: 降噪等级, 有效范围: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetDeBlocking(HI_U32* pu32DBLevel);

/**
 \brief 设置块降噪de-blocking强度
 \attention \n
无

 \param[in] u32DBLevel: 降噪等级, 有效范围: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDeBlocking(HI_U32 u32DBLevel);

/**
 \brief 获取去纹躁de-ringing强度
 \attention \n
无

 \param[out] *pu32DBLevel: 降噪等级, 有效范围: 0~255


 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetDeRinging(HI_U32* pu32DRLevel);

/**
 \brief 设置去纹躁de-ringing强度
 \attention \n
无

 \param[in] u32DBLevel: 降噪等级, 有效范围: 0~255

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDeRinging(HI_U32 u32DRLevel);

/**
 \brief 获取颜色增强
 \attention \n
无

 \param[out] pu32ColorGainLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetColorEhance(HI_U32* pu32ColorGainLevel);

/**
 \brief 设置颜色增强
 \attention \n
无

 \param[in] u32ColorGainLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetColorEhance(HI_U32 u32ColorGainLevel);

/**
 \brief 获取肤色增强
 \attention \n
  无

 \param[out] pu32FleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetFleshToneLevel(HI_U32* pu32FleshToneLevel);

/**
 \brief 设置肤色增强
 \attention \n
  无

 \param[in] enFleshToneLevel

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetFleshToneLevel(HI_PQ_FLESHTONE_E enFleshToneLevel);

/**
 \brief 设置DCI强度增益等级
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDCILevelGain(HI_U32 u32DCILevelGain);

/**
 \brief 设置DCI配置曲线
 \attention \n
无

 \param[in] pstDciCoef;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDCIWgtLut(DCI_WGT_S* pstDciCoef);

/**
 \brief 获取NR 自动开关状态
 \attention \n
  无

 \param[out] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetNrAutoMode(HI_U32* pu32OnOff);

/**
 \brief 设置NR自动开关
 \attention \n
  无

 \param[in] u32OnOff 开关

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetNrAutoMode(HI_U32 u32OnOff);

/**
 \brief 获取3D Sharpness 模式状态
 \attention \n
  无

 \param[out] pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_Get3DSharpMode(HI_U32* pu32OnOff);

/**
 \brief 设置3D Sharpness 模式
 \attention \n
  无

 \param[in] u32OnOff 开关

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_Set3DSharpMode(HI_U32 u32OnOff);

/**
 \brief 获取各通道的CSC(用于调试)
 \attention \n
无

 \param[in] enDisplayId
 \param[out] pstCSCMode

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_GetCSCMode(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S* pstCSCMode);


/**
 \brief 设置卖场模式开关
 \attention \n
无

 \param[in] enFlags

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetDemoMode(HI_PQ_DEMO_E enFlags, HI_BOOL bOnOff);

/**
 \brief 获取PQ模块开关状态
 \attention \n
  无

 \param[in] enFlags
 \param[out] *pu32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetPQModule(HI_PQ_MODULE_E enFlags, HI_U32* pu32OnOff);

/**
 \brief 设置PQ模块开关
 \attention \n
  无

 \param[in] enFlags
 \param[in] u32OnOff

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetPQModule(HI_PQ_MODULE_E enFlags, HI_U32 u32OnOff);

/**
 \brief 获取SR演示模式开关
 \attention \n
无

 \param[in] ps32Type

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSRMode(HI_S32* ps32Type);

/**
 \brief 设置SR演示模式开关
 \attention \n
无

 \param[in] eSRMode: SR演示模式0-只ZME;1-右边SR；2-左边SR；3-SR开

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetSRMode(HI_PQ_SR_DEMO_E eSRMode);

/**
 \brief 获取PQBin 的物理地址
 \attention \n
无

 \param[in] pu32Addr:

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetBinPhyAddr(HI_U32* pu32Addr);

/**
 \brief 设置ACM 的Luma 曲线查找表
 \attention \n
无

 \param[in] pstAttr:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAcmLuma(HI_PQ_ACM_LUT_S* pstAttr);

/**
 \brief 设置ACM 的Hue 曲线查找表
 \attention \n
无

 \param[in] pstAttr:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAcmHue(HI_PQ_ACM_LUT_S* pstAttr);

/**
 \brief 设置ACM 的Sat 曲线查找表
 \attention \n
无

 \param[in] pstAttr:

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetAcmSat(HI_PQ_ACM_LUT_S* pstAttr);

/**
 \brief 六基色控制设置
 \attention \n
  无

 \param[in] enSixColorType;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSixBaseColorLevel(HI_PQ_SIX_BASE_S* pstSixBaseColorOffset);

/**
 \brief 颜色增强模式设置
 \attention \n
  无

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
