/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_pq_mng_db.h
  Version       : Initial Draft
  Author        : l00191147
  Created       : 2013/10/11
  Description   :

******************************************************************************/


#ifndef __DRV_PQ_MNG_DB_H__
#define __DRV_PQ_MNG_DB_H__

#include "hi_type.h"
#include "pq_hal_db.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


/**
 \brief 初始化CCCL模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitCCCL();


/**
 \brief 去初始化CCCL模块
 \attention \n
无

 \param[in] none;

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_DeinitCCCL();




/**
 \brief 开关NR模块
 \attention \n
无

 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_EnableCCCL(HI_BOOL bOnOff);




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_NR_H__ */



