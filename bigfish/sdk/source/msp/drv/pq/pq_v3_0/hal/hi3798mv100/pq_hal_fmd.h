/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_hal_fmd.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/2/18
  Description   :

******************************************************************************/

#ifndef __PQ_HAL_FMD_H__
#define __PQ_HAL_FMD_H__

#include "hi_type.h"
#include "pq_hal_comm.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

typedef struct hi_PQ_FMD_CTRL_S
{
    HI_U32 u32ifmd_en;             /* iFmd Ctrl enalbe */
    HI_U32 u32Pd32_en;             /* pulldown 3:2 detection enable */
    HI_U32 u32Pd22_en;             /* pulldown 2:2 detection enable */
    HI_U32 u32Pd22_mode;           /* pulldown 2:2 detection mode   */
    HI_U32 u32Fod_en_mode;         /* field order detection enable  */
    HI_U32 u32Edge_smooth_en;      /* edgesmooth enable */
    HI_U32 u32Edge_smooth_ratio;   /* edgesmooth ratio */
    HI_U32 u32Bitsmov2r;           /* iCHD calculation para-right shift bits: 0：right shift 6bit; */

} PQ_FMD_CTRL_S;

typedef struct hi_PQ_FMD_HISTBIN_THD_S
{
    HI_U32 u32Hist_thd0;          /* histgram threshold 0 */
    HI_U32 u32Hist_thd1;          /* histgram threshold 1 */
    HI_U32 u32Hist_thd2;          /* histgram threshold 2 */
    HI_U32 u32Hist_thd3;          /* histgram threshold 3 */
    HI_U32 u32Mon_start_idx;      /* start bin number mark for calculating bin-monotonic:1-15 */
    HI_U32 u32Mon_tkr_thr;        /* bin-monotonic threshold */
    HI_U32 u32Diff_movblk_thd;    /* difference threshold of moving block */
    HI_U32 u32Stillblk_thd;       /* still block threshold */

} PQ_FMD_HISTBIN_THD_S;

typedef struct hi_PQ_FMD_PCC_THD_S
{
    HI_U32 u32Mov_coring_norm;    /* moving coring value for normal pixel */
    HI_U32 u32Mov_coring_tkr;     /* moving coring value for texture */
    HI_U32 u32Coring_norm;        /* pilority change coring for  normal pixel */
    HI_U32 u32Coring_tkr;         /* pilority change coring for texture pixel */
    HI_U32 u32Pcc_hthd;           /* horizontal threshold */
    HI_U32 u32Pcc_vthd0;          /* vertical threshold 0 */
    HI_U32 u32Pcc_vthd1;          /* vertical threshold 1 */
    HI_U32 u32Pcc_vthd2;          /* vertical threshold 2 */
    HI_U32 u32Pcc_vthd3;          /* vertical threshold 3 */
} PQ_FMD_PCC_THD_S;

typedef struct hi_PQ_FMD_PCC_BLK_S
{
    HI_U32 u32Blk_x0;             /* x value of the top left pixel */
    HI_U32 u32Blk_y0;             /* y value of the top left pixel */
    HI_U32 u32Blk_x1;             /* x value of the bottom right pixel */
    HI_U32 u32Blk_y1;             /* y value of the bottom right pixel */
    HI_U32 u32Mov_coring_blk;     /* moving coring value of block computation */
    HI_U32 u32Coring_blk;         /* pilority change coring value of block computation */

} PQ_FMD_PCC_BLK_S;

typedef struct hi_PQ_FMD_UM_THD_S
{
    HI_U32 u32Um_thd0;            /* match threshold 0 */
    HI_U32 u32Um_thd1;            /* match threshold 1 */
    HI_U32 u32Um_thd2;            /* match threshold 2 */

} PQ_FMD_UM_THD_S;

typedef struct hi_PQ_FMD_ITDIFF_THD_S
{
    HI_U32 u32Itdiff_vthd0;       /* match threshold 0 */
    HI_U32 u32Itdiff_vthd1;       /* IT different threshold 1 */
    HI_U32 u32Itdiff_vthd2;       /* IT different threshold 2 */
    HI_U32 u32Itdiff_vthd3;       /* IT different threshold 3 */

} PQ_FMD_ITDIFF_THD_S;

typedef struct hi_PQ_FMD_LASI_THD_S
{
    HI_U32 u32Lasi_mode;          /* lasi computation mode:0-new mode;1-old */
    HI_U32 u32Lasi_thd;           /* lasi threshold */
    HI_U32 u32Edge_thd;           /* edge threshold */
    HI_U32 u32Lasi_mov_thr;       /* moving threshold of lasi */
    HI_U32 u32LasiTxtAlpha;
    HI_U32 u32LasiTxtCoring;
    HI_U32 u32LasiTxtThd0;
    HI_U32 u32LasiTxtThd1;
    HI_U32 u32LasiTxtThd2;
    HI_U32 u32LasiTxtThd3;

} PQ_FMD_LASI_THD_S;

typedef struct hi_PQ_FMD_REGION_S
{
    HI_U32 u32Region1YStt;
    HI_U32 u32Region1YEnd;
}PQ_FMD_REGION_S;

typedef struct hi_PQ_FMD_COEF_S
{
    PQ_FMD_CTRL_S        stPqFmdCtrl;
    PQ_FMD_HISTBIN_THD_S stPqFmdHistbinThd;
    PQ_FMD_PCC_THD_S     stPqFmdPccThd;
    PQ_FMD_PCC_BLK_S     stPqFmdPccBlk;
    PQ_FMD_UM_THD_S      stPqFmdUmThd;
    PQ_FMD_ITDIFF_THD_S  stPqFmdItdiffThd;
    PQ_FMD_LASI_THD_S    stPqFmdLashThd;
    PQ_FMD_REGION_S      stPqFmdRegion;

} PQ_FMD_COEF_S;


typedef struct
{
    HI_S32 lasiCnt14;
    HI_S32 lasiCnt32;
    HI_S32 lasiCnt34;
} REG_LASI_STAT_S;

typedef struct
{
    HI_S32 PCC_FFWD;
    HI_S32 PCC_FWD;
    HI_S32 PCC_BWD;
    HI_S32 PCC_CRSS;
    HI_S32 pixel_weave;
    HI_S32 PCC_FWD_TKR;
    HI_S32 PCC_BWD_TKR;
    HI_S32 PCCBLK_FWD[9];
    HI_S32 PCCBLK_BWD[9];
} REG_PCC_STAT_S;

typedef struct
{
    HI_S32 HISTOGRAM_BIN_1;
    HI_S32 HISTOGRAM_BIN_2;
    HI_S32 HISTOGRAM_BIN_3;
    HI_S32 HISTOGRAM_BIN_4;
} REG_HISTOGRAM_STAT_S;

typedef struct
{
    HI_S32 match_UM;
    HI_S32 nonmatch_UM;
    HI_S32 match_UM2;
    HI_S32 nonmatch_UM2;
} REG_UM_STAT_S;

typedef struct
{
    HI_S32 StillBlkCnt;
    HI_S32 BlkSad[16];
} REG_STILLBLK_STAT_S;

typedef struct
{
    HI_S32 iCHD;
} REG_SCENCHG_STAT_S;


typedef struct
{
    HI_S32               frmITDiff;
    REG_UM_STAT_S        frmUm;
    REG_PCC_STAT_S       frmPcc;
    REG_HISTOGRAM_STAT_S frmHstBin;
    REG_LASI_STAT_S      lasiStat;
    REG_STILLBLK_STAT_S  StillBlkInfo;
    REG_SCENCHG_STAT_S   SceneChangeInfo;
    REG_PCC_STAT_S       frmPcc2;
    REG_LASI_STAT_S      lasiStat2;
} ALG_FMD_RTL_STATPARA_S;


typedef struct
{
    HI_U32 u32MotionHist[32];         /* output of logic, 32bit unsigned */
    HI_U32 u32SmallMtnNum;            /* output of logic, 32bit unsigned */
    HI_U32 u32SmallMtnSum;            /* output of logic, 32bit unsigned */
    HI_U32 u32LargeMtnNum;            /* output of logic, 32bit unsigned */
    HI_U32 u32LargeMtnSum;            /* output of logic, 32bit unsigned */
    HI_U32 u32MidMtnNum0;            
    HI_U32 u32MidMtnSum0; 
    HI_U32 u32MidMtnNum1;            
    HI_U32 u32MidMtnSum1;
    HI_U32 u32MidMtnNum2;
    HI_U32 u32MidMtnSum2;

} ALG_MAD_RTL_STATPARA_S;


typedef struct
{
    ALG_FMD_RTL_STATPARA_S stFmdRtlStatPara; /* 需要从逻辑读的统计信息 */
    ALG_MAD_RTL_STATPARA_S stMadRtlStatPara; /* 需要从逻辑读的统计信息 */
} IFMD_TotalHardPara;

typedef struct
{
    HI_S32 IsProgressiveSeq;
    HI_S32 IsProgressiveFrm;
    HI_S32 RealFrmRate;
    
} VDEC_TRAN_INFO_S;

/*IFMD软算法所需驱动传入参数，VPSS->PQ*/
typedef struct hi_PQ_REG_IFMD_CALC_S
{
    HI_U32  u32HandleNo;
    HI_U32  u32WidthY;
    HI_U32  u32HeightY;
    HI_S32  s32FieldOrder;                 /* 顶底场序 顶场优先底场优先 */
    HI_S32  s32FieldMode;                  /* 顶底场标志 */
    HI_U32  u32FrameRate;
    HI_BOOL bPreInfo;                      /* DEI逻辑处理timeout，仍旧处理上一场 */
    VDEC_TRAN_INFO_S  stVdecTranInfo;
    S_VPSSWB_REGS_TYPE* pstIfmdHardOutReg; /* 读取ifmd的状态寄存器 */
    
} PQ_REG_IFMD_CALC_S;

typedef struct
{
    HI_S32 die_reset;
    HI_S32 die_stop;
    HI_S32 dir_mch;
    HI_S32 die_out_sel;
    HI_S32 jud_en;
    //HI_S32  ChromaVertFltEn;
    HI_S32 s32FieldOrder;      /* 顶底场序 */
    HI_S32 s32SceneChanged;    /* 场景切换信息 */
    HI_S32 s32FilmType;        /* 电影模式 */
    HI_U32 u32KeyValue;        /* 输出关键帧信息*/
    HI_U32 u32EdgeSmoothEn;

} REG_PLAYBACK_CONFIG_S;


HI_S32  PQ_HAL_SetIFmdRegist(HI_U32 u32HandleNo, PQ_FMD_COEF_S* pstFmdDectCfg);
HI_VOID PQ_HAL_GetIFmdStatInfo(PQ_REG_IFMD_CALC_S* pstIfmdCalcInfo, IFMD_TotalHardPara* pIfmdTotalHardPara);
HI_S32  PQ_HAL_SetIFmdInfo(HI_U32 u32HandleNo, REG_PLAYBACK_CONFIG_S* NewCfg);
HI_S32 PQ_HAL_SetEdgeSmoothEn(HI_U32 u32HandleNo, HI_BOOL bEdgeSmoothEn);



#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* __HAL_PQ_SHARP_H__ */

