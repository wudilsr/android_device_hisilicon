/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_dbdm.h
  Version       : Initial Draft
  Author        :
  Created       : 2014-10-16
  Description   : De-blocking and De-Ringning

******************************************************************************/

#ifndef __PQ_MNG_DBDM_H__
#define __PQ_MNG_DBDM_H__

#include "pq_hal_dbdr.h"
#include "pq_hal_comm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define MAXLINESIZE 4096
#define NR_MIN(x, y) (((x) > (y)) ? (y) : (x))
#define NR_MAX(x, y) (((x) > (y)) ? (x) : (y))
#define NR_CLIP3(low,high,x)  (NR_MAX(NR_MIN((high),(x)),(low)))

typedef struct DetblkInfo_s
{
    HI_S8  Detsize;
    HI_U32 CounterBorder;
} DetblkInfo_s;

typedef struct  DetStaticUsing_S
{
    /* 结合时域信息之后，检测的结果 */
    HI_S8  UsingSizeHy ;
    HI_S8  UsingSizeHchr;
    HI_S8  UsingSizeVy ;
    HI_U32 UsingHyCounterBorder;
    HI_U32 UsingVyCounterBorder;

    HI_U32 UsingHchrCounterBorder;
    HI_U8  UsingBorderIndex[MAXLINESIZE];
    HI_U8*  ptrUsingHyBorderIndex;
    HI_U8*  ptrUsingVyBorderIndex;
    HI_U8*  ptrUsingHchrBorderIndex;

    HI_U8  NumberWindow; /* 时间窗口 */
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
    HI_S8*  ptrHyCnt;
    HI_S8*  ptrHchrCnt;
    HI_S8*  ptrVyCnt;
    HI_U8  frmsCntTempHy;
    HI_U8  frmsCntTempHchr;
    HI_U8  frmsCntTempVy;
    HI_U8  frmsWindowTemp;
    HI_U8  frmsSatWindowTemp;

    HI_S32 FillBorderNumHy;
    HI_S32 FillBorderNumVy;
    HI_S32 FillBorderNumHchr;
} DetStaticUsing_S;

typedef struct
{
    /* basic info, might be modified */
    HI_S32 s32LumWidth;
    HI_S32 s32LumHeight;
    HI_S32 s32ChrWidth;
    HI_S32 s32ChrHeight;
    HI_S32 s32LumHBlkNum; /* [0,480] */
    HI_S32 s32LumVBlkNum; /* [0,180] */
    HI_S32 s32ChrHBlkNum; /* [0,480] */

    HI_S32 det_size_en;
    HI_S32 det_hy_en;
    HI_S32 det_hc_en;
    HI_S32 det_vy_en;

    /* from wbc stt infor */
    HI_S32 hy_counter;
    HI_S32 hy_size;
    HI_S32 vy_counter;
    HI_S32 vy_size;
    HI_S32 hc_counter;
    HI_S32 hc_size;
    HI_S32 db_border[128];
    HI_S32 db_hy_counter[1920];

} DB_DET_INFO_S;

typedef struct DetResultInfo_S
{
    //HI_U32* ptrHyStrRow;
    HI_U32 ptrHyStrRow[MAXLINESIZE];
    HI_U32 HyCounterBorder;            /* [0,1023] */
    HI_U32 HchrCounterBorder;          /* [0,1023] */
    HI_U32 VyCounterBorder;            /* [0,1023] */
    HI_S8  detsize_hy;                 /* [-1,63]  */
    HI_S8  detsize_hchr;               /* [-1,63]  */
    HI_S8  detsize_vy;                 /* [-1,63]  */
    HI_U8  BorderIndex[MAXLINESIZE];
    HI_U8* ptrHyBorderIndex;           /* [0,1]    */
    HI_U8* ptrHchrBorderIndex;         /* [0,1]    */
    HI_U8* ptrVyBorderIndex;           /* [0,1]    */
} DetResultInfo_S;

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


/* Init DBDM */
HI_S32 PQ_MNG_InitDNR(HI_VOID);
/* Deinit DBDM */
HI_S32 PQ_MNG_DeinitDNR(HI_VOID);
HI_S32 PQ_MNG_EnableDB(HI_BOOL bOnOff);
/* Get DB Enable state */
HI_S32 PQ_MNG_GetDBEnableFlag(HI_BOOL* pbOnOff);
/* DB DEMO Enable */
HI_S32 PQ_MNG_EnableDBDemo(HI_BOOL bOnOff);
/* Set DM Enable */
HI_S32 PQ_MNG_EnableDM(HI_BOOL bOnOff);
/* Get DM Enable state */
HI_S32 PQ_MNG_GetDMEnableFlag(HI_BOOL* pbOnOff);
/* Enable DM DEMO */
HI_S32 PQ_MNG_EnableDMDemo(HI_BOOL bOnOff);
/* Set DR Enable */
HI_S32 PQ_MNG_EnableDR(HI_BOOL bOnOff);
/* Get DR Enable state */
HI_S32 PQ_MNG_GetDREnableFlag(HI_BOOL* pbOnOff);
/* Enable DR DEMO */
HI_S32 PQ_MNG_EnableDRDemo(HI_BOOL bOnOff);

HI_S32 PQ_MNG_SetDbmDemoMode(DBM_DEMO_MODE_E enMode);
HI_S32 PQ_MNG_GetDbmDemoMode(DBM_DEMO_MODE_E* penMode);

HI_S32 PQ_MNG_DBCfgRefresh(HI_U32 u32HandleNo, HI_U32 u32Height, HI_U32 u32Width, HI_U32 u32FRate);
HI_S32 PQ_MNG_DBCalcConfigCfg(DB_CALC_INFO_S* pstDbCalcInfo);
HI_S32 PQ_MNG_DMCalcConfigCfg(DB_CALC_INFO_S* pstDmCalcInfo);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

