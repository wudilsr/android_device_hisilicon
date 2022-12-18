/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_pq_mng_dbdr.h
  Version       : Initial Draft
  Author        : 
  Created       : 2014-10-16
  Description   : De-blocking and De-Ringning

******************************************************************************/


#ifndef __PQ_MNG_DBDR_H__
#define __PQ_MNG_DBDR_H__


#include "pq_hal_dbdr.h"
#include "pq_hal_comm.h"

    
#ifdef __cplusplus
 #if __cplusplus
    extern "C" {
 #endif
#endif /* End of #ifdef __cplusplus */


/******************************* MNG De-Blocking Definition Start **********************************/

#if defined(CHIP_TYPE_hi3798cv200_a)
#define MAXLINESIZE 4096
#define NR_MIN(x, y) (((x) > (y)) ? (y) : (x))
#define NR_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define NR_CLIP3(low,high,x)  (NR_MAX(NR_MIN((high),(x)),(low)))
typedef struct DetblkInfo_s 
{
    HI_S8  Detsize;
    HI_U32 CounterBorder;
}DetblkInfo_s ;

typedef struct  DetStaticUsing_S
{
    //结合时域信息之后，检测的结果
    HI_S8  UsingSizeHy ;
    HI_S8  UsingSizeHchr;
    HI_S8  UsingSizeVy ;
    HI_U32 UsingHyCounterBorder;     
    HI_U32 UsingVyCounterBorder;

    HI_U32 UsingHchrCounterBorder;
    HI_U8  UsingBorderIndex[MAXLINESIZE] ;
    HI_U8  *ptrUsingHyBorderIndex ; 
    HI_U8  *ptrUsingVyBorderIndex ;  
    HI_U8  *ptrUsingHchrBorderIndex ;

    HI_U8  NumberWindow ; // 时间窗口
    HI_U8  SaturatWindow;

    HI_U8  HyMINBlkNum;
    HI_U8  HchrMINBlkNum;
    HI_U8  VyMINBlkNum;

    HI_U32 frms_NumsHy;
    HI_U32 frms_NumsHchr;
    HI_U32 frms_NumsVy;
    HI_U8  keyfrm_num;
    HI_U8  HyBordCountThreshold;
    HI_U8  HchrBordCountThreshold;
    HI_U8  VyBordCountThreshold;

    DetblkInfo_s Hy[16];
    DetblkInfo_s Vy[16];
    DetblkInfo_s Hchr[16];

    HI_S8  BorderCnt[MAXLINESIZE];
    HI_S8  *ptrHyCnt;
    HI_S8  *ptrHchrCnt;
    HI_S8  *ptrVyCnt;
    HI_U8  frmsCntTempHy;
    HI_U8  frmsCntTempHchr;
    HI_U8  frmsCntTempVy;
    HI_U8  frmsWindowTemp;
    HI_U8  frmsSatWindowTemp;
    
    HI_S32 FillBorderNumHy;     
    HI_S32 FillBorderNumVy;
    HI_S32 FillBorderNumHchr;
}DetStaticUsing_S;

typedef struct
{
    //basic info, might be modified
    HI_S32 s32LumWidth;
    HI_S32 s32LumHeight;
    HI_S32 s32ChrWidth;
    HI_S32 s32ChrHeight;
    HI_S32 s32LumHBlkNum; // [0,480]
    HI_S32 s32LumVBlkNum; // [0,180]
    HI_S32 s32ChrHBlkNum; // [0,480]

    HI_S32 det_size_en;
    HI_S32 det_hy_en;
    HI_S32 det_hc_en;
    HI_S32 det_vy_en;

    //from wbc stt infor
    HI_S32 hy_counter;
    HI_S32 hy_size;
    HI_S32 vy_counter;
    HI_S32 vy_size;
    HI_S32 hc_counter;
    HI_S32 hc_size;
    HI_S32 db_border[128] ;
    HI_S32 db_hy_counter[1920];

} DB_DET_INFO_S;

typedef struct DetResultInfo_S
{
	HI_U32 ptrHyStrRow[MAXLINESIZE];
	//HI_U32* ptrHyStrRow ;
    HI_U32 HyCounterBorder;            //[0,1023]
    HI_U32 HchrCounterBorder;          //[0,1023]
    HI_U32 VyCounterBorder;            //[0,1023]
    HI_S8  detsize_hy;                 //[-1,63]
    HI_S8  detsize_hchr;               //[-1,63]
    HI_S8  detsize_vy;                 //[-1,63]
    HI_U8  BorderIndex[MAXLINESIZE];
    HI_U8  *ptrHyBorderIndex;          //[0,1]
    HI_U8  *ptrHchrBorderIndex;        //[0,1]
    HI_U8  *ptrVyBorderIndex;          //[0,1]
}DetResultInfo_S;


typedef struct
{
    HI_U16 PixValAdjGain;
    HI_U16 HFDiffCore;
    HI_U16 HFDiffGain1;
    HI_U16 HFDiffGain2;
    HI_U16 HFVarCore;
    HI_U16 HFVarGain1;
    HI_U16 HFVarGain2;
    HI_U16 BordAdjGain;
    HI_U16 GradSubRatio;
} DB_DynmcPara;

#endif  //#ifdef CHIP_TYPE_hi3798cv200_a


/**
\brief     :初始化DB模块

\attention :只初始化ID为0的实例，其余多实例情况的初始化在上层实现

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_InitDB(HI_VOID);
    
    
/**
\brief     :反初始化DB模块

\attention :无

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_DeinitDB(HI_VOID);
    
    
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
HI_S32 PQ_MNG_GetDBEnableFlag(HI_BOOL *pbOnOff);    
    
    
/**
\brief     :开关DB模块DEMO模式

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDBDemo(HI_BOOL bOnOff); 
    
    
/**
\brief     :获取DB Demo 模块使能状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDBDemoEnableFlag(HI_BOOL *pbOnOff);    
    
    
/**
\brief     :设置DB强度

\attention :多实例公用一个强度设置值

\param[in] :s32DBStr  降噪强度值，取值范围[0,255]

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_SetDBStrength(HI_S32 s32DBStr);


/**
\brief     :获取DB强度

\attention :多实例公用一个强度设置值

\param[in] :无

\param[out]:ps32DBStr  降噪强度值地址，强度取值范围[0,255]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDBStrength(HI_S32 *ps32DBStr);


/**
 \brief 刷新DB API 全局变量
 \attention \n
无

 \param[in]  

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_DBCfgRefresh(HI_U32 u32HandleNo, HI_U32 u32Height, HI_U32 u32Width, HI_U32 u32FRate);

HI_S32 PQ_MNG_DBCalcConfigCfg(DB_CALC_INFO_S * pstDbCalcInfo);



/******************************* MNG De-Blocking Definition End **********************************/


/******************************* MNG De-Ringing Definition Start **********************************/

/**
\brief     :初始化DR模块

\attention :只初始化ID为0的实例，其余多实例情况的初始化在上层实现

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_InitDR(HI_VOID);
    
    
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
HI_S32 PQ_MNG_GetDREnableFlag(HI_BOOL *pbOnOff);


/**
\brief     :开关DR模块DEMO模式

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableDRDemo(HI_BOOL bOnOff);


/**
\brief     :获取DR Demo 模块使能状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDRDemoEnableFlag(HI_BOOL *pbOnOff);


/**
\brief     :设置DR强度

\attention :多实例公用一个强度设置值

\param[in] :s32DRStr  降噪强度值，取值范围[0,255]

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_SetDRStrength(HI_S32 s32DRStr);
    

/**
\brief     :获取DR强度

\attention :多实例公用一个强度设置值

\param[in] :无

\param[out]:ps32DRStr  降噪强度值地址，强度取值范围[0,255]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetDRStrength(HI_S32 *ps32DRStr);
    

/********************************* MNG De-Ringing Definition End **********************************/

/******************************* MNG SD De-Ringing Definition Start **********************************/


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
HI_S32 PQ_MNG_EnableSDDB(HI_BOOL bOnOff);


/**
\brief     :获取DB模块使能状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetSDDBEnableFlag(HI_BOOL* pbOnOff);


/**
\brief     :反初始化DR模块

\attention :无

\param[in] :无

\param[out]:无

\retval    :HI_SUCCESS

*/
HI_S32 PQ_MNG_DeinitSDDR(HI_VOID);


/**
\brief     :开关DR模块

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableSDDR(HI_BOOL bOnOff);


/**
\brief     :获取DR模块使能状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetSDDREnableFlag(HI_BOOL* pbOnOff);


/**
\brief     :开关DR Demo模式

\attention :无

\param[in] :bOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\param[out]:无

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_EnableSDDRDemo(HI_BOOL bOnOff);


/**
\brief     :获取DR模块Demo开关状态

\attention :无

\param[in] :无

\param[out]:*pbOnOff,[HI_TRUE 开启/HI_FALSE 关闭]

\retval    :HI_SUCCESS/HI_FAILURE

*/
HI_S32 PQ_MNG_GetSDDRDemoFlag(HI_BOOL* pbOnOff);


/******************************* MNG SD De-Ringing Definition End **********************************/


                
#ifdef __cplusplus
 #if __cplusplus
    }
 #endif
#endif /* End of #ifdef __cplusplus */
    
#endif /*End of #ifndef __MNG_PQ_DBDR_H__ */

