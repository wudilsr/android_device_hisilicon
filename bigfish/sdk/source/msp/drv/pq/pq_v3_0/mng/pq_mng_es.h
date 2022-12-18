/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_pq_mng_nr.h
  Version       : Initial Draft
  Author        : l00191147
  Created       : 2013/10/11
  Description   : 

******************************************************************************/

	
#ifndef __DRV_PQ_MNG_ES_H__
#define __DRV_PQ_MNG_ES_H__
	
#include "hi_type.h"
#include "pq_hal_es.h"
	
#ifdef __cplusplus
 #if __cplusplus
	extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */
	
	
	/**
	 \brief ��ʼ��NRģ��
	 \attention \n
	��
	
	 \param[in] none;
	
	 \retval ::HI_SUCCESS
	
	 */
	
	HI_S32 PQ_MNG_InitES();
	
	
	/**
	 \brief ȥ��ʼ��NRģ��
	 \attention \n
	��
	
	 \param[in] none;
	
	 \retval ::HI_SUCCESS
	
	 */
	
	HI_S32 PQ_MNG_DeinitES();
	
	
	/**
	 \brief ���ý���ǿ��
	 \attention \n
	��
	
	 \param[in] s32NrStr  ����ǿ��ֵ��ȡֵ��Χ[0,198]
	
	 \retval ::HI_SUCCESS
	
	 */
	HI_S32 PQ_MNG_SetESStrength(HI_S32 s32NrStr);
	
	/**
	 \brief ��ȡ����ǿ��
	 \attention \n
	��
	
	 \param[in] none
	 \param[out]
	
	
	 \retval ::����ǿ��,����ֵ��Χ[0,198]
	
	 */
	HI_S32 PQ_MNG_GetESStrength(HI_S32 *ps32NrStr);
	
	
	/**
	 \brief ����NRģ��
	 \attention \n
	��
	
	 \param[in] bOnOff
	
	 \retval ::HI_SUCCESS
	
	 */
	
	HI_S32 PQ_MNG_EnableES(HI_BOOL bOnOff);
	
	

	
	
	
#ifdef __cplusplus
 #if __cplusplus
	}
 #endif
#endif /* End of #ifdef __cplusplus */
	
#endif /*End of #ifndef __MNG_PQ_NR_H__ */



