/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_dbdr.h
  Version       : Initial Draft
  Author        : l00268071 lvmingjun
  Created       : 2014/01/28
  Description   : De-blocking and De-Ringning

******************************************************************************/

#ifndef __DRV_PQ_HAL_DBDR_H__
#define __DRV_PQ_HAL_DBDR_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/**********************************define dbdr**************************************/
typedef struct hi_PQ_DNR_CTRL_S
{
    HI_U32 u32Dr_en;                          //DR filter enbale
    HI_U32 u32Dr_Demo_en;                     //DR filter Demo enbale
    HI_U32 u32Db_en;                          //DB filter enbale
    HI_U32 u32Db_en_vert;                     //DB vertical filter enable:0-off;1-on
    HI_U32 u32Db_en_hor;                      //DB horizontal filter enable:0-off;1-on
} PQ_DNR_CTRL_S;

typedef struct hi_PQ_DNR_DR_FILTER_S
{
    HI_U32 u32Dr_thr_flat3x3zone;             //contrast threshold for DR 3*3 block
    HI_U32 u32Dr_thr_maxsimilarpixdiff;       //pixel difference similarity threshold for DR
    HI_U32 u32Dr_betascale;                   //beta factor for DR
    HI_U32 u32Dr_alphascale;                  //alpha factor for DR
} PQ_DNR_DR_FILTER_S;

typedef struct hi_PQ_DNR_DB_FILTER_S
{
    HI_U32 u32db_thr_maxgrad;                  //maximum gratitude threshold for DB filter
    HI_U32 u32db_thr_edge;                     //edge threshold for DB filter
    HI_U32 u32picest_qp;                       //Qp for DB filter
    HI_U32 u32db_text_en;                      //texture filter enable for DB
    HI_U32 u32db_useweakflt;                   //strong filter mode select for DB:0- 9 tap strong filter;1- 7 tap strong filter
    HI_U32 u32db_thr_maxdiffvert;              //maximum block different of vertical direction  for DB
    HI_U32 u32db_thr_leastblkdiffvert;         //maximum block different of vertical direction  for DB
    HI_U32 u32db_thr_maxdiffhor;               //maximum block different of horizontal direction  for DB
    HI_U32 u32db_thr_leastblkdiffhor;          //maximum block different of horizontal direction  for DB
    HI_U32 u32db_betascale;                    //beta factor for DB
    HI_U32 u32db_alphascale;                   //alpha factor for DB
    HI_U32 u32db_thr_largesmooth;              //smooth region threshold for DB
    HI_U32 u32detail_img_qpthr;                //Qp threshold for DB
} PQ_DNR_DB_FILTER_S;

typedef struct hi_PQ_DNR_INFO_S
{
    HI_U32 u32thd_cntrst8;                     //contrast threshold of 8*8 block for selecting DR block
    HI_U32 u32thd_maxgrad;                     //maximum gratitude threshold of 8*8 block for selecting DR
    HI_U32 u32thr_intl_cnt;                    //counter threshold of one column for IP detection
    HI_U32 u32thr_intl_colcnt;                 //counter threshold of one block for IP detection
} PQ_DNR_INFO_S;

typedef struct hi_PQ_DNR_COEF_S
{
    PQ_DNR_CTRL_S      stPqDnrCtrl;
    PQ_DNR_DB_FILTER_S stPqDnrDbFilter;
    PQ_DNR_DR_FILTER_S stPqDnrDrFilter;
    PQ_DNR_INFO_S      stPqDnrInfo;
} PQ_DNR_COEF_S;


/**
\brief     :设置DNR模块默认的参数值

\attention :无

\param[in] :u32HandleNo 实例ID;  pstDBPara 参数的默认值

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_HAL_SetDnrParamRegister(HI_U32 u32HandleNo, PQ_DNR_COEF_S* pstDnrPara);


/**
\brief     :设置DB功能开关

\attention :无

\param[in] :u32HandleNo 实例ID;
            bDBOnOff HI_TRUE为功能打开，HI_FALSE为功能关闭
\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_HAL_EnableDB(HI_U32 u32HandleNo, HI_BOOL bDBOnOff);


/**
\brief     :设置DR功能开关

\attention :无

\param[in] :u32HandleNo 实例ID;
            bDROnOff HI_TRUE为功能打开，HI_FALSE为功能关闭
\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_HAL_EnableDR(HI_U32 u32HandleNo, HI_BOOL bDROnOff);


/**
\brief     :设置DR Demo功能开关

\attention :无

\param[in] :u32HandleNo 实例ID;
            bDROnOff HI_TRUE为功能打开，HI_FALSE为功能关闭
\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_HAL_EnableDRDemo(HI_U32 u32HandleNo, HI_BOOL bDRDemoOnOff);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

