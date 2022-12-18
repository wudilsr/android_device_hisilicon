/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_pq_mng_nr.h
  Version       : Initial Draft
  Author        : l00191147
  Created       : 2013/10/11
  Description   :

******************************************************************************/


#ifndef __PQ_MNG_NR_H__
#define __PQ_MNG_NR_H__

#include "hi_type.h"
#include "pq_hal_nr.h"
#include "pq_hal_comm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */



/*SNR 的LUT表*/
typedef struct	hiSNR_LUT_S
{
    HI_U16 u16SNRMotionEdge[16][16];		/*4bit	 motion-edge lut*/
    HI_U16 u16SNRColorBase[16][16]; 	 /*4bit   color-base lut*/
} SNR_LUT_S;


/*TNR 的LUT表*/
typedef struct	hiTNR_LUT_S
{
    HI_U16 u16TNRMotionEdge[16][16];		/*4bit	 motion-edge lut*/
    HI_U16 u16TNRMotionNoise[16][16]; 	 /*4bit   motion-noise lut*/
} TNR_LUT_S;


//input of sofeware
typedef struct
{
    HI_U16 u16GlobalMotionEn;
    HI_U16 au16GlobalMotionThd[6];
    HI_U16 au16GlobalMotionRatio[5];
    HI_S16 as16GlobalMotionSlope[4];
    HI_U16 u16MaxGlobalMotionRatio;
    HI_U16 u16MinGlobalMotionRatio;
} TNR_MOTION_CALC_S; //MotionCalc_S;


//tnr global motion api 输入参数结构
typedef struct
{
    HI_U32 u32HdlNo;	//实例的ID
    HI_U32 u32Width;	//输入图像宽度
    HI_U32 u32Height;	//输入图像高度
    S_VPSSWB_REGS_TYPE* pstMotionReg;	//寄存器地址
} TNR_MOTION_PARAM_IN_S;


/**
 \brief 初始化NR模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitNr(HI_VOID);


/**
 \brief 去初始化NR模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeinitNr(HI_VOID);


/**
 \brief 设置降噪强度
 \attention \n
无

 \param[in] s32NrStr  降噪强度值，取值范围[0,255]

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetNrStrength(HI_S32 s32NrStr);

/**
 \brief 获取降噪强度
 \attention \n
无

 \param[in] none
 \param[out]


 \retval ::降噪强度,返回值范围[0,255]

 */
HI_S32 PQ_MNG_GetNrStrength(HI_S32* ps32NrStr);


/**
 \brief 开关NR模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableNr(HI_BOOL bOnOff);


/**
 \brief 开关TNR模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */


HI_S32 PQ_MNG_EnableTNr(HI_BOOL bOnOff);


/**
 \brief 开关SNR模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableSNr(HI_BOOL bOnOff);


/**
 \brief 获取TNR使能状态
 \attention \n
无

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetTNREnableFlag(HI_BOOL* pbOnOff);


/**
 \brief 获取SNR使能状态
 \attention \n
无

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetSNREnableFlag(HI_BOOL* pbOnOff);



/**
 \brief 开关NR模块DEMO模式
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableNrDemo(HI_BOOL bOnOff);




/**
  \brief 设置SNR的PIXMEAN-RATIO参数
  \attention \n
 无

  \param[in] pstSNR_Pixmean2Ratio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetSnrPixmeanToRatio(SNR_PIXMEAN_2_RATIO_S* pstSNR_Pixmean2Ratio);



/**
  \brief 获取SNR的PIXMEAN-RATIO参数
  \attention \n
 无

  \param[out] pstSNR_Pixmean2Ratio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetSnrPixmeanToRatio(SNR_PIXMEAN_2_RATIO_S* pstSNR_Pixmean2Ratio);




/**
  \brief 设置SNR的PIXDIFF-EDGESTR参数
  \attention \n
 无

  \param[in] pstSNR_Pixdiff2Edgestr

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetSnrPixdiffToEdgestr(SNR_PIXDIFF_2_EDGESTR_S* pstSNR_Pixdiff2Edgestr);





/**
  \brief 获取SNR的PIXDIFF-EDGESTR参数
  \attention \n
 无

  \param[out] pstSNR_Pixdiff2Edgestr

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetSnrPixdiffToEdgestr(SNR_PIXDIFF_2_EDGESTR_S* pstSNR_Pixdiff2Edgestr);






/**
  \brief 设置TNR的PixMean-Ratio For YMotion Detection参数
  \attention \n
 无

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrYMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_YMotionPixmeanRatio);






/**
  \brief 获取TNR的PixMean-Ratio For YMotion Detection参数
  \attention \n
 无

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrYMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_YMotionPixmeanRatio);






/**
  \brief 设置TNR的PixMean-Ratio For CMotion Detection参数
  \attention \n
 无

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrCMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_CMotionPixmeanRatio);





/**
  \brief 获取TNR的PixMean-Ratio For CMotion Detection参数
  \attention \n
 无

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrCMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_CMotionPixmeanRatio);






/**
  \brief 设置TNR的YMotionMapping参数
  \attention \n
 无

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrYMotionMapping(TNR_MAPPING_S* pstTNR_YMotionMapping);







/**
  \brief 获取TNR的YMotionMapping参数
  \attention \n
 无

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrYMotionMapping(TNR_MAPPING_S* pstTNR_YMotionMapping);









/**
  \brief 设置TNR的CMotonMapping 参数
  \attention \n
 无

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrCMotionMapping(TNR_MAPPING_S* pstTNR_CMotionMapping);








/**
  \brief 获取TNR的CMotonMapping参数
  \attention \n
 无

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrCMotionMapping(TNR_MAPPING_S* pstTNR_CMotionMapping);






/**
  \brief 设置TNR的Final Y Motion Mapping参数
  \attention \n
 无

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrFnlMotionYMapping(TNR_MAPPING_S* pstTNR_FnlMotionYMapping);







/**
  \brief 获取TNR的Final Y Motion Mapping参数
  \attention \n
 无

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrFnlMotionYMapping(TNR_MAPPING_S* pstTNR_FnlMotionYMapping);






/**
  \brief 设置TNR的Final C Motion Mapping参数
  \attention \n
 无

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrFnlMotionCMapping(TNR_MAPPING_S* pstTNR_FnlMotionCMapping);







/**
  \brief 获取TNR的Final C Motion Mapping参数
  \attention \n
 无

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrFnlMotionCMapping(TNR_MAPPING_S* pstTNR_FnlMotionCMapping);



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
HI_S32 PQ_MNG_TnrGetGlobalMotion(TNR_MOTION_PARAM_IN_S* pstParamIn, TNR_MOTION_RESULT_S* pstMotionResult);

/**
\brief     :设置Nr自动降噪功能开关

\attention :多实例公用一个开关

\param[in] :bEnFlag  功能开关：HI_TRUE自动降噪功能打开，HI_FALSE功能关闭

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_EnableAutoNr(HI_BOOL bEnFlag);

/**
\brief     :获取Nr自动降噪功能开关

\attention :多实例公用一个开关

\param[in] :无

\param[out]:pbFlag  功能开关状态：HI_TRUE自动降噪功能打开，HI_FALSE功能关闭

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetAutoNrFlag(HI_BOOL* pbFlag);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_NR_H__ */



