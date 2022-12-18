/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_pq_mng_dbdr.h
  Version       : Initial Draft
  Author        : 
  Created       : 2014-12-23
  Description   : De-blocking and De-Ringning

******************************************************************************/


#ifndef __DRV_PQ_MNG_DBDR_H__
#define __DRV_PQ_MNG_DBDR_H__


#include "pq_hal_dbdr.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* End of #ifdef __cplusplus */


/**
\brief     :初始化DNR模块

\attention :只初始化ID为0的实例，其余多实例情况的初始化在上层实现

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_InitDNR(HI_VOID);

/**
\brief     :去初始化DNR模块

\attention :无

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_DeinitDNR(HI_VOID);


/**
\brief     :开关DB模块

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDB(HI_BOOL bOnOff);


/**
\brief     :获取DB模块使能状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDBEnableFlag(HI_BOOL* pbOnOff);


/**
\brief     :反初始化DR模块

\attention :无

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_DeinitDR(HI_VOID);


/**
\brief     :开关DR模块

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDR(HI_BOOL bOnOff);


/**
\brief     :获取DR模块使能状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDREnableFlag(HI_BOOL* pbOnOff);


/**
\brief     :开关DR Demo模式

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDRDemo(HI_BOOL bOnOff);


/**
\brief     :获取DR模块Demo开关状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDRDemoFlag(HI_BOOL* pbOnOff);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_DBDR_H__ */



