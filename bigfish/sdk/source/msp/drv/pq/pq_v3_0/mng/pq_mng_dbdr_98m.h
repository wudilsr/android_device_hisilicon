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
\brief     :��ʼ��DNRģ��

\attention :ֻ��ʼ��IDΪ0��ʵ���������ʵ������ĳ�ʼ�����ϲ�ʵ��

\param[in] :��

\param[out]:��

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_InitDNR(HI_VOID);

/**
\brief     :ȥ��ʼ��DNRģ��

\attention :��

\param[in] :��

\param[out]:��

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_DeinitDNR(HI_VOID);


/**
\brief     :����DBģ��

\attention :��

\param[in] :bOnOff,[HI_TRUE ����/HI_FALSE �ر�]

\param[out]:��

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDB(HI_BOOL bOnOff);


/**
\brief     :��ȡDBģ��ʹ��״̬

\attention :��

\param[in] :��

\param[out]:*pbOnOff,[HI_TRUE ����/HI_FALSE �ر�]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDBEnableFlag(HI_BOOL* pbOnOff);


/**
\brief     :����ʼ��DRģ��

\attention :��

\param[in] :��

\param[out]:��

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_DeinitDR(HI_VOID);


/**
\brief     :����DRģ��

\attention :��

\param[in] :bOnOff,[HI_TRUE ����/HI_FALSE �ر�]

\param[out]:��

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDR(HI_BOOL bOnOff);


/**
\brief     :��ȡDRģ��ʹ��״̬

\attention :��

\param[in] :��

\param[out]:*pbOnOff,[HI_TRUE ����/HI_FALSE �ر�]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDREnableFlag(HI_BOOL* pbOnOff);


/**
\brief     :����DR Demoģʽ

\attention :��

\param[in] :bOnOff,[HI_TRUE ����/HI_FALSE �ر�]

\param[out]:��

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDRDemo(HI_BOOL bOnOff);


/**
\brief     :��ȡDRģ��Demo����״̬

\attention :��

\param[in] :��

\param[out]:*pbOnOff,[HI_TRUE ����/HI_FALSE �ر�]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDRDemoFlag(HI_BOOL* pbOnOff);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __MNG_PQ_DBDR_H__ */



