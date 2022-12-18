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



/*SNR ��LUT��*/
typedef struct	hiSNR_LUT_S
{
    HI_U16 u16SNRMotionEdge[16][16];		/*4bit	 motion-edge lut*/
    HI_U16 u16SNRColorBase[16][16]; 	 /*4bit   color-base lut*/
} SNR_LUT_S;


/*TNR ��LUT��*/
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


//tnr global motion api ��������ṹ
typedef struct
{
    HI_U32 u32HdlNo;	//ʵ����ID
    HI_U32 u32Width;	//����ͼ����
    HI_U32 u32Height;	//����ͼ��߶�
    S_VPSSWB_REGS_TYPE* pstMotionReg;	//�Ĵ�����ַ
} TNR_MOTION_PARAM_IN_S;


/**
 \brief ��ʼ��NRģ��
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitNr(HI_VOID);


/**
 \brief ȥ��ʼ��NRģ��
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeinitNr(HI_VOID);


/**
 \brief ���ý���ǿ��
 \attention \n
��

 \param[in] s32NrStr  ����ǿ��ֵ��ȡֵ��Χ[0,255]

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_SetNrStrength(HI_S32 s32NrStr);

/**
 \brief ��ȡ����ǿ��
 \attention \n
��

 \param[in] none
 \param[out]


 \retval ::����ǿ��,����ֵ��Χ[0,255]

 */
HI_S32 PQ_MNG_GetNrStrength(HI_S32* ps32NrStr);


/**
 \brief ����NRģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableNr(HI_BOOL bOnOff);


/**
 \brief ����TNRģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */


HI_S32 PQ_MNG_EnableTNr(HI_BOOL bOnOff);


/**
 \brief ����SNRģ��
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableSNr(HI_BOOL bOnOff);


/**
 \brief ��ȡTNRʹ��״̬
 \attention \n
��

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetTNREnableFlag(HI_BOOL* pbOnOff);


/**
 \brief ��ȡSNRʹ��״̬
 \attention \n
��

 \param[out] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_GetSNREnableFlag(HI_BOOL* pbOnOff);



/**
 \brief ����NRģ��DEMOģʽ
 \attention \n
��

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableNrDemo(HI_BOOL bOnOff);




/**
  \brief ����SNR��PIXMEAN-RATIO����
  \attention \n
 ��

  \param[in] pstSNR_Pixmean2Ratio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetSnrPixmeanToRatio(SNR_PIXMEAN_2_RATIO_S* pstSNR_Pixmean2Ratio);



/**
  \brief ��ȡSNR��PIXMEAN-RATIO����
  \attention \n
 ��

  \param[out] pstSNR_Pixmean2Ratio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetSnrPixmeanToRatio(SNR_PIXMEAN_2_RATIO_S* pstSNR_Pixmean2Ratio);




/**
  \brief ����SNR��PIXDIFF-EDGESTR����
  \attention \n
 ��

  \param[in] pstSNR_Pixdiff2Edgestr

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetSnrPixdiffToEdgestr(SNR_PIXDIFF_2_EDGESTR_S* pstSNR_Pixdiff2Edgestr);





/**
  \brief ��ȡSNR��PIXDIFF-EDGESTR����
  \attention \n
 ��

  \param[out] pstSNR_Pixdiff2Edgestr

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetSnrPixdiffToEdgestr(SNR_PIXDIFF_2_EDGESTR_S* pstSNR_Pixdiff2Edgestr);






/**
  \brief ����TNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrYMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_YMotionPixmeanRatio);






/**
  \brief ��ȡTNR��PixMean-Ratio For YMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_YMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrYMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_YMotionPixmeanRatio);






/**
  \brief ����TNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrCMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_CMotionPixmeanRatio);





/**
  \brief ��ȡTNR��PixMean-Ratio For CMotion Detection����
  \attention \n
 ��

  \param[in] pstTNR_CMotionPixmeanRatio

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrCMotionPixMeanRatio(TNR_MAPPING_S* pstTNR_CMotionPixmeanRatio);






/**
  \brief ����TNR��YMotionMapping����
  \attention \n
 ��

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrYMotionMapping(TNR_MAPPING_S* pstTNR_YMotionMapping);







/**
  \brief ��ȡTNR��YMotionMapping����
  \attention \n
 ��

  \param[in] pstTNR_YMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrYMotionMapping(TNR_MAPPING_S* pstTNR_YMotionMapping);









/**
  \brief ����TNR��CMotonMapping ����
  \attention \n
 ��

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrCMotionMapping(TNR_MAPPING_S* pstTNR_CMotionMapping);








/**
  \brief ��ȡTNR��CMotonMapping����
  \attention \n
 ��

  \param[in] pstTNR_CMotionMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrCMotionMapping(TNR_MAPPING_S* pstTNR_CMotionMapping);






/**
  \brief ����TNR��Final Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrFnlMotionYMapping(TNR_MAPPING_S* pstTNR_FnlMotionYMapping);







/**
  \brief ��ȡTNR��Final Y Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionYMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrFnlMotionYMapping(TNR_MAPPING_S* pstTNR_FnlMotionYMapping);






/**
  \brief ����TNR��Final C Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_SetTnrFnlMotionCMapping(TNR_MAPPING_S* pstTNR_FnlMotionCMapping);







/**
  \brief ��ȡTNR��Final C Motion Mapping����
  \attention \n
 ��

  \param[in] pstTNR_FnlMotionCMapping

  \retval ::HI_SUCCESS

  */

HI_S32 PQ_MNG_GetTnrFnlMotionCMapping(TNR_MAPPING_S* pstTNR_FnlMotionCMapping);



/**
\brief     :Tnr��Global Motion���㷨API

\attention :
			���㷨�ο�DEIģ�������ֲ
			�㷨�ṩ���ᳯ�� p00188942����ֲ&ά���������� l00268071

\param[in] :pstParamIn�ṹ����������Ԫ��
			u32HdlNo ʵ����ID
			u32Width ����ͼ����
			u32Height ����ͼ��߶�
			pstMotionReg �Ĵ�����ַ

\param[out]:pstMotionResult�ṹ����������Ԫ��
			u32GlobalMotion ����Ĵ���VPSS_TNR_TFM_PARA�е�tfm_globalmotion
			u32AdjustGain

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_TnrGetGlobalMotion(TNR_MOTION_PARAM_IN_S* pstParamIn, TNR_MOTION_RESULT_S* pstMotionResult);

/**
\brief     :����Nr�Զ����빦�ܿ���

\attention :��ʵ������һ������

\param[in] :bEnFlag  ���ܿ��أ�HI_TRUE�Զ����빦�ܴ򿪣�HI_FALSE���ܹر�

\param[out]:��

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_EnableAutoNr(HI_BOOL bEnFlag);

/**
\brief     :��ȡNr�Զ����빦�ܿ���

\attention :��ʵ������һ������

\param[in] :��

\param[out]:pbFlag  ���ܿ���״̬��HI_TRUE�Զ����빦�ܴ򿪣�HI_FALSE���ܹر�

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetAutoNrFlag(HI_BOOL* pbFlag);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_NR_H__ */



