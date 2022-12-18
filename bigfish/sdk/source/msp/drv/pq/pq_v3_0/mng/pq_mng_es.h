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
	 \brief 初始化NR模块
	 \attention \n
	无
	
	 \param[in] none;
	
	 \retval ::HI_SUCCESS
	
	 */
	
	HI_S32 PQ_MNG_InitES();
	
	
	/**
	 \brief 去初始化NR模块
	 \attention \n
	无
	
	 \param[in] none;
	
	 \retval ::HI_SUCCESS
	
	 */
	
	HI_S32 PQ_MNG_DeinitES();
	
	
	/**
	 \brief 设置降噪强度
	 \attention \n
	无
	
	 \param[in] s32NrStr  降噪强度值，取值范围[0,198]
	
	 \retval ::HI_SUCCESS
	
	 */
	HI_S32 PQ_MNG_SetESStrength(HI_S32 s32NrStr);
	
	/**
	 \brief 获取降噪强度
	 \attention \n
	无
	
	 \param[in] none
	 \param[out]
	
	
	 \retval ::降噪强度,返回值范围[0,198]
	
	 */
	HI_S32 PQ_MNG_GetESStrength(HI_S32 *ps32NrStr);
	
	
	/**
	 \brief 开关NR模块
	 \attention \n
	无
	
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



