/******************************************************************************
 Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : mng_pq_sharp.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2013/10/12
Last Modified :
Description   : PQ MNG��SHARPENģ��� ���ݽṹ�ͽӿں���
Function List :
History       :
******************************************************************************/

#ifndef __PQ_MNG_SHARPEN_H__
#define __PQ_MNG_SHARPEN_H__

#include "hi_type.h"
#include "pq_hal_sharpen.h"

//#include "drv_pq_define.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */



/**
 \brief ��ʼ��SHARPENģ��
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitSharpen(PQ_PARAM_S* pstPqParam);


/**
 \brief ȥ��ʼ��SHARPENģ��
 \attention \n
��

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeinitSharpen(HI_VOID);


/**
 \brief ����������ǿ��
 \attention \n
��

 \param[in] u32ShpStr  ������ǿ��ֵ��ȡֵ��Χ[0,255]

 \retval ::HI_SUCCESS

 */
 HI_S32 PQ_MNG_SetSharpenStr(HI_S32 s32ShpStr, HI_U32 u32SourceMode, HI_U32 u32OutputMode);

/**
 \brief ��ȡ������ǿ��
 \attention \n

 \param[in] none
 \param[out]


 \retval ::������ǿ��,����ֵ��Χ[0,255]

 */
HI_S32 PQ_MNG_GetSharpenStr(HI_S32* ps32ShpStr);

/**
 \brief ����SHARPENģ��
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSharpen(HI_U8 u8Enable);

/**
 \brief ��ȡSharpen����
 \attention \n
��

 \param[in]*bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_GetSharpenEnable(HI_BOOL* pbOnOff);

/**
 \brief ����SHARPENģ��DEMOģʽ
 \attention \n

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_EnableSharpenDemo(HI_BOOL bOnOff);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

