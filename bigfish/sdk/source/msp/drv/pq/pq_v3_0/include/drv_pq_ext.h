/******************************************************************************
*
* Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved.
*
* This program is confidential and proprietary to Hisilicon  Technologies Co., Ltd. (Hisilicon),
*  and may not be copied, reproduced, modified, disclosed to others, published or used, in
* whole or in part, without the express prior written permission of Hisilicon.
*
*****************************************************************************

  File Name     : drv_pq_ext.h
  Version       : Initial Draft
  Author        : p00203646
  Created       : 2014/04/01
  Description   :

******************************************************************************/

#ifndef __DRV_PQ_EXT_V3_H__
#define __DRV_PQ_EXT_V3_H__

#include "hi_type.h"
#include "hi_drv_video.h"
#include "hi_reg_common.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


typedef S_CAS_REGS_TYPE PQ_VPSS_CFG_REG_S;
typedef S_VPSSWB_REGS_TYPE PQ_VPSS_WBC_REG_S ;


/* VPSS��Ƶ��Ϣ */
typedef struct hiHI_VPSS_PQ_INFO_S
{
    HI_DRV_SOURCE_E     enInputSrc;         /* �ź�Դ���� */
    HI_U32              u32Width;           /* ͼ���� */
    HI_U32              u32Height;          /* ͼ��߶� */
    HI_U32              u32FrameRate;       /* ����֡�� */
    HI_BOOL             bInterlace;         /* �Ƿ�����ź� */
    HI_DRV_COLOR_SYS_E  enColorSys;         /* ATV�źŵ�Color System */
} HI_VPSS_PQ_INFO_S;

/*VDP��Ƶ��Ϣ */
typedef struct hiHI_VDP_PQ_INFO_S
{
    HI_DRV_SOURCE_E             enInputSrc;         /* �ź�Դ���� */
    HI_U32                      u32Width;           /* ͼ���� */
    HI_U32                      u32Height;          /* ͼ��߶� */
    HI_U32                      u32FrameRate;       /* ����֡�� */
    HI_BOOL                     bInterlace;         /* �Ƿ�����ź� */
    HI_BOOL                     b3dType;            /* �Ƿ�ԭ��3D���� */
    HI_BOOL                     bPcTiming;          /* �Ƿ�ΪPC Timing */
    HI_DRV_COLOR_SYS_E          enColorSys;         /* ATV�źŵ�Color System */
    HI_U32                      u32OutWidth;        /* ���ͼ���� */
    HI_U32                      u32OutHeight;       /* ���ͼ��߶� */
    HI_BOOL                     bSRState;           /* SR ���� */
} HI_VDP_PQ_INFO_S;


/* PQģ�鿪����Ϣ */
typedef struct hiPQ_VPSS_MODULE_S
{
    HI_BOOL                     bFMD;         /* FMD���� */
    HI_BOOL                     bTNR;         /* NR���� */
    HI_BOOL                     bCCCL;        /* CCCL���� */
} HI_PQ_VPSS_MODULE_S;

/* ɫ�ʿռ�ת������ */
typedef enum hiPQ_CSC_MODE_
{
    HI_PQ_CSC_YUV2RGB_601 = 0,          /* YCbCr_601 LIMIT-> RGB */
    HI_PQ_CSC_YUV2RGB_709,              /* YCbCr_709 LIMIT-> RGB */
    HI_PQ_CSC_RGB2YUV_601,              /* RGB->YCbCr_601 LIMIT */
    HI_PQ_CSC_RGB2YUV_709,              /* RGB->YCbCr_709 LIMIT */
    HI_PQ_CSC_YUV2YUV_709_601,          /* YCbCr_709 LIMIT->YCbCr_601 LIMIT */
    HI_PQ_CSC_YUV2YUV_601_709,          /* YCbCr_601 LIMIT->YCbCr_709 LIMIT */
    HI_PQ_CSC_YUV2YUV,                  /* YCbCr LIMIT->YCbCr LIMIT */
    HI_PQ_CSC_YUV2RGB_601_FULL,         /* YCbCr_601 FULL-> RGB */
    HI_PQ_CSC_YUV2RGB_709_FULL,         /* YCbCr_709 FULL-> RGB */
    HI_PQ_CSC_RGB2YUV_601_FULL,         /* RGB->YCbCr_601 FULL */
    HI_PQ_CSC_RGB2YUV_709_FULL,         /* RGB->YCbCr_709 FULL */
    HI_PQ_CSC_RGB2RGB,                  /* RGB->RGB */

    HI_PQ_CSC_BUTT
} HI_PQ_CSC_MODE_E;

/*VDP CSC ID*/
typedef enum hiPQ_CSC_ID_E
{
    HI_PQ_VDP_CSC_V0 = 0 ,
    HI_PQ_VDP_CSC_V1     ,
    HI_PQ_VDP_CSC_V2     ,
    HI_PQ_VDP_CSC_V3     ,
    HI_PQ_VDP_CSC_V4     ,
    //HI_PQ_VDP_CSC_VP0  ,
    //HI_PQ_VDP_CSC_VP1  ,

    HI_PQ_VDP_CSC_BUTT
} HI_PQ_CSC_ID_E;

/* VDP CSC ����*/
typedef struct  hiPQ_VDP_CSC_S
{
    HI_BOOL  bCSCEn;
    HI_PQ_CSC_MODE_E  enCSC;
} HI_PQ_VDP_CSC_S;


/* ����YUV���ݽṹ��444 422 420 */
typedef enum hiPQ_ZME_FORMAT_E
{
    HI_PQ_ALG_PIX_FORMAT_SP420 = 0,
    HI_PQ_ALG_PIX_FORMAT_SP422,
    HI_PQ_ALG_PIX_FORMAT_SP444,

    HI_PQ_ALG_PIX_FORMAT_BUTT,
} ZME_FORMAT_E;

/* SCALER ��Ϣ */
typedef struct  hiPQ_SCALER_S
{
    HI_BOOL bHorizontal;
    HI_BOOL bYUV;
    HI_BOOL b3Dtype;
    HI_U32  u32YRatio;
    HI_U32  u32CRatio;
    ZME_FORMAT_E enInFmt;
    ZME_FORMAT_E enOutFmt;
} HI_PQ_SCALER_S;

/* DCIֱ��ͼ�ṹ */
typedef struct hiPQ_HISTGRAM_S
{
    HI_S32 s32HistGram[32];
} HI_PQ_HISTGRAM_S;

/* CSC ����ϵ���ṹ */
typedef struct  hiPQ_CSC_COEF_S
{
    HI_S32 csc_coef00;
    HI_S32 csc_coef01;
    HI_S32 csc_coef02;

    HI_S32 csc_coef10;
    HI_S32 csc_coef11;
    HI_S32 csc_coef12;

    HI_S32 csc_coef20;
    HI_S32 csc_coef21;
    HI_S32 csc_coef22;
} HI_PQ_CSC_COEF_S;

typedef struct  hiPQ_CSC_DCCOEF_S
{
    HI_S32 csc_in_dc0;
    HI_S32 csc_in_dc1;
    HI_S32 csc_in_dc2;

    HI_S32 csc_out_dc0;
    HI_S32 csc_out_dc1;
    HI_S32 csc_out_dc2;
} HI_PQ_CSC_DCCOEF_S;

/* DCIͳ�ƴ��� */
typedef struct  hiPQ_DCI_WIN_S
{
    HI_U16      u16HStar;
    HI_U16      u16HEnd;
    HI_U16      u16VStar;
    HI_U16      u16VEnd;
} HI_PQ_DCI_WIN_S;

/* DEI ȫ���˶���Ϣ */
typedef struct hiPQ_MOTION_INFO_S
{
    HI_U32 u32GlobalMotion;
    HI_U32 u32AdjustGain;
} HI_PQ_MOTION_INFO_S;


//tnr global motion api ��������ṹ
typedef struct
{
    HI_U32 u32HdlNo;                   /* ʵ����ID */
    HI_U32 u32Width;                   /* ����ͼ���� */
    HI_U32 u32Height;                  /* ����ͼ��߶� */
    //S_VPSSWB_REGS_TYPE* pstMotionReg;    /* �Ĵ�����ַ */
} HI_PQ_TNR_MOTION_PARAM_IN_S;

/* Tnr global motion result */
typedef struct
{
    HI_U32 u32GlobalMotion;
    HI_U32 u32AdjustGain;
} HI_PQ_TNR_MOTION_RESULT_S;

/* DBǿ��ֵ,��ӦVPSS_DB_WEIGHT�Ĵ��� */
typedef struct
{
    HI_U8    u8HWeight;        /* 6bits [0,63] */
    HI_U8    u8VWeight;        /* 6bits [0,63] */
} HI_PQ_DB_WEIGHT_S;

/* image signal type of interlacing or non-interlacing */
typedef enum
{
    HI_PQ_DB_INTERLACE = 0,    /* ����DEI ,���� */
    HI_PQ_DB_PROGRESSIVE       /* ������DEI ,���� */
} HI_PQ_DB_SIG_TYPE_E;


/* DBǿ�� API����������ṹ */
typedef struct
{
    HI_U8                 u8SCDStr;    /* ����SCD��api����ó���һ��ֵ[0,255] */
    HI_U32                u32HdlNo;    /* ʵ����ID */
    HI_PQ_DB_SIG_TYPE_E   eType;       /* ����Դ���ͣ����л����У��Ƿ���DEI */
    //S_VPSSWB_REGS_TYPE*  pstReg;     /* global motion �Ĵ�����ַ */

} HI_PQ_DB_STR_PARAM_IN_S;


typedef struct
{
    HI_S32 IsProgressiveSeq;
    HI_S32 IsProgressiveFrm;
    HI_S32 RealFrmRate;

} PQ_VDEC_INFO_S;

/*IFMD���㷨�����������������VPSS->PQ*/
typedef struct hi_PQ_IFMD_CALC_S
{
    HI_U32  u32HandleNo;
    HI_U32  u32WidthY;
    HI_U32  u32HeightY;
    HI_S32  s32FieldOrder;                 /* ���׳��� �������ȵ׳����� */
    HI_S32  s32FieldMode;                  /* ���׳���־ */
    HI_U32  u32FrameRate;
    HI_BOOL bPreInfo;                      /* DEI�߼�����timeout���Ծɴ�����һ�� */
    PQ_VDEC_INFO_S stVdecInfo;
    S_VPSSWB_REGS_TYPE* pstIfmdHardOutReg; /* ��ȡifmd��״̬�Ĵ��� */

} HI_PQ_IFMD_CALC_S;

typedef struct
{
    HI_S32  die_reset;
    HI_S32  die_stop;
    HI_S32  dir_mch;
    HI_S32  die_out_sel;
    HI_S32  jud_en;
    //HI_S32  ChromaVertFltEn;
    HI_S32  s32FieldOrder;    /* ���س��� */
    HI_S32  s32SceneChanged;  /* �����л���Ϣ */
    HI_S32  s32FilmType;      /* ��Ӱģʽ */
    HI_U32  u32KeyValue;      /* �ؼ�֡ */
    HI_U32  u32EdgeSmoothEn;

} HI_PQ_IFMD_PLAYBACK_S;


/* PFMD���㷨�����������������VPSS->PQ */
typedef struct hi_PQ_PFMD_CALC_S
{
    HI_U32  u32HandleNo;
    HI_U32  u32WidthY;
    HI_U32  u32HeightY;
    HI_S32  s32FieldOrder; /* ���׳��� �������ȵ׳����� */
    HI_S32  s32FieldMode;  /* ���׳���־ */
    //S_VPSSWB_REGS_TYPE* pstpfmdHardOutReg; /* ��ȡpfmd��״̬�Ĵ��� */

} HI_PQ_PFMD_CALC_S;

typedef struct
{
    HI_S32  s32SceneChanged; /* �����л���Ϣ */
    HI_S32  s32FilmType;     /* ��Ӱģʽ */
    HI_U32  u32KeyValue;     /* �ؼ�֡ */
} HI_PQ_PFMD_PLAYBACK_S;

/*����/�Աȶ�/ɫ��/���Ͷ��趨*/
typedef struct hiPQ_PICTURE_SETTING_S
{
    HI_U16 u16Brightness;
    HI_U16 u16Contrast;
    HI_U16 u16Hue;
    HI_U16 u16Saturation;

    /*ɫ���趨*/
    HI_S16 s16RedGain;
    HI_S16 s16GreenGain;
    HI_S16 s16BlueGain;
    HI_S16 s16RedOffset;
    HI_S16 s16GreenOffset;
    HI_S16 s16BlueOffset;
} HI_PQ_PICTURE_SETTING_S;


typedef struct
{
    HI_U32    u32ZmeFrmWIn;      /* zme  input frame width  */
    HI_U32    u32ZmeFrmHIn;      /* zme  input frame height */
    HI_U32    u32ZmeFrmWOut;     /* zme output frame width  */
    HI_U32    u32ZmeFrmHOut;     /* zme output frame height */

    HI_U8     u8ZmeYCFmtIn;      /* video format for zme  input: 0-422; 1-420; 2-444 */
    HI_U8     u8ZmeYCFmtOut;     /* video format for zme Output: 0-422; 1-420; 2-444 */

    HI_BOOL   bZmeFrmFmtIn;      /* Frame format for zme  input: 0-field; 1-frame */
    HI_BOOL   bZmeFrmFmtOut;     /* Frame format for zme Output: 0-field; 1-frame */
    HI_BOOL   bZmeBFIn;          /* Input  field polar when input  is field format: 0-top field; 1-bottom field */
    HI_BOOL   bZmeBFOut;         /* Output field polar when Output is field format: 0-top field; 1-bottom field */

    HI_RECT_S stOriRect;
    HI_U32    u32InRate;         /* Vpss out Rate  RealRate*1000 */
    HI_U32    u32OutRate;        /* Disp Rate      RealRate*1000 */
    HI_BOOL   bDispProgressive;  /* 1:Progressive 0:Interlace */
    HI_U32    u32Fidelity;       /* rwzb info >0:is rwzb */
    /*
     1.OriRect
     2.InFrameRate
     3.OutRate
     4.Out I/P
     */
} HI_PQ_ZME_PARA_IN_S;

typedef struct
{
    HI_BOOL bZmeEnHL;    /* zme enable of horizontal luma: 0-off; 1-on */
    HI_BOOL bZmeEnHC;
    HI_BOOL bZmeEnVL;
    HI_BOOL bZmeEnVC;

    HI_BOOL bZmeMdHL;    /* zme mode of horizontal luma: 0-copy mode; 1-FIR filter mode */
    HI_BOOL bZmeMdHC;
    HI_BOOL bZmeMdVL;
    HI_BOOL bZmeMdVC;

    HI_BOOL bZmeMedHL;   /* zme Median filter enable of horizontal luma: 0-off; 1-on */
    HI_BOOL bZmeMedHC;
    HI_BOOL bZmeMedVL;
    HI_BOOL bZmeMedVC;

    HI_S32 s32ZmeOffsetHL;
    HI_S32 s32ZmeOffsetHC;
    HI_S32 s32ZmeOffsetVL;
    HI_S32 s32ZmeOffsetVC;
    HI_S32 s32ZmeOffsetVLBtm;
    HI_S32 s32ZmeOffsetVCBtm;

    HI_U32 u32ZmeWIn;
    HI_U32 u32ZmeHIn;
    HI_U32 u32ZmeWOut;
    HI_U32 u32ZmeHOut;

    HI_U32 u32ZmeRatioHL;
    HI_U32 u32ZmeRatioVL;
    HI_U32 u32ZmeRatioHC;
    HI_U32 u32ZmeRatioVC;

    HI_BOOL bZmeOrder;    /* zme order of hzme and vzme: 0-hzme first; 1-vzme first */
    HI_BOOL bZmeTapVC;    /* zme tap of vertical chroma: 0-4tap; 1-2tap */

    HI_U8 u8ZmeYCFmtIn;   /* video format for zme input: 0-422; 1-420; 2-444 */
    HI_U8 u8ZmeYCFmtOut;  /* video format for zme output: 0-422; 1-420; 2-444 */

    HI_U32 u32ZmeCoefAddrHL;
    HI_U32 u32ZmeCoefAddrHC;
    HI_U32 u32ZmeCoefAddrVL;
    HI_U32 u32ZmeCoefAddrVC;
} HI_PQ_ZME_RTL_S;

typedef struct
{
    HI_PQ_ZME_RTL_S stZmeRtlPara;
    HI_U32  u32PosXStart;
} HI_PQ_SPLIT_ZME_PARA_UNIT_S;

/*�ֿ����ŵ�������Ϣ*/
typedef struct
{
    HI_PQ_SPLIT_ZME_PARA_UNIT_S stPQSplitZmePara[2]; /* �������������������������Ϣ*/
} HI_PQ_SPLIT_ZME_PARA_S;

typedef enum hiPQ_ZME_LAYER_E
{
    HI_PQ_DISP_V0_LAYER_ZME = 0,
    HI_PQ_DISP_V1_LAYER_ZME    ,
    HI_PQ_DISP_V2_LAYER_ZME    ,
    HI_PQ_DISP_V3_LAYER_ZME    ,
    HI_PQ_DISP_V4_LAYER_ZME    ,
    HI_PQ_DISP_WBC0_LAYER_ZME  ,
    HI_PQ_DISP_SR_LAYER_ZME    ,

    HI_PQ_DISP_LAYER_ZME_BUTT
} HI_PQ_ZME_LAYER_E;


/* ��ע:Port�ĸ����HSCL�ǲ�ͬ�ģ�VPSS������Ӧ�������������
   ���ŵ������Լ����ŵ�δ֪(PORT) */
typedef enum hiPQ_VPSS_ZME_LAYER_E
{
    HI_PQ_VPSS_PORT0_LAYER_ZME = 0 ,
    HI_PQ_VPSS_PORT1_LAYER_ZME     ,
    HI_PQ_VPSS_PORT2_LAYER_ZME     ,
    HI_PQ_VPSS_HSCL_LAYER_ZME      ,

    HI_PQ_VPSS_LAYER_ZME_BUTT
} HI_PQ_VPSS_ZME_LAYER_E;

#if 0
typedef enum hiPQ_VPSS_REG_PORT_E
{
    HI_PQ_VPSS_REG_HD = 0 ,
    HI_PQ_VPSS_REG_SD     ,
    HI_PQ_VPSS_REG_STR    ,

    HI_PQ_VPSS_REG_BUTT
} HI_PQ_VPSS_REG_PORT_E;
#endif

/* PORT���ŵĴ��ڴ�С */
typedef struct hiPQ_PORT_WIN_S
{
    HI_U32    u32Height;
    HI_U32    u32Width;
} HI_PQ_PORT_WIN_S;

/* ZME��Layer���Ŵ��ڴ�С*/
typedef struct hiPQ_ZME_WIN_S
{
    HI_PQ_PORT_WIN_S    stPort0Win;
    HI_PQ_PORT_WIN_S    stPort1Win;
    HI_PQ_PORT_WIN_S    stPort2Win;
    HI_PQ_PORT_WIN_S    stHSCLWin;
} HI_PQ_ZME_WIN_S;



/* VPSS �����������Ϣ */
typedef struct hiPQ_WBC_INFO_S
{
    /* Common */
    HI_U32   u32HandleNo;
    HI_U32   u32Width;
    HI_U32   u32Height;
    HI_BOOL  bProgressive;              /* ��������Ϣ */
    S_VPSSWB_REGS_TYPE* pstVPSSWbcReg;  /* ifmd ��Globlal Motion and DB�Ļ�д��Ϣ */
    /* GlobalMotion */

    /* IFMD */
    HI_S32   s32FieldOrder;              /* ���׳��� �������ȵ׳����� */
    HI_S32   s32FieldMode;               /* ���׳���־ */
    HI_U32   u32FrameRate;               /* ֡�� */
    HI_BOOL  bPreInfo;                   /* DEI�߼�����timeout���Ծɴ�����һ�� */
    PQ_VDEC_INFO_S stVdecInfo;           /* VDEC ���ݵĸ�������Ϣ */

    /* DNR */

} HI_PQ_WBC_INFO_S;


/* PQ Calc ����VPSS��������Ϣ */
typedef struct hiPQ_CFG_INFO_S
{
    /* GlobalMotion */

    /* IFMD */
    HI_S32  die_reset;
    HI_S32  die_stop;
    HI_S32  dir_mch;
    HI_S32  die_out_sel;
    HI_S32  jud_en;
    HI_S32  ChromaVertFltEn;
    HI_S32  s32FieldOrder;    /* ���س��� */
    HI_S32  s32SceneChanged;  /* �����л���Ϣ */
    HI_S32  s32FilmType;      /* ��Ӱģʽ */
    HI_U32  u32KeyValue;      /* �ؼ�֡ */
    /* DNR */

} HI_PQ_CFG_INFO_S;

/* VPSS WBC ���ݸ�De-Blocking����������Ϣ */
typedef struct hiPQ_DB_CALC_INFO_S
{

    HI_U32 u32HandleNo;
    HI_U32 u32Width;
    HI_U32 u32Height;
    S_VPSSWB_REGS_TYPE* pstDbCalcWbcReg;

} HI_PQ_DB_CALC_INFO_S;



typedef HI_S32 (*FN_PQ_GetPqParam)(HI_VOID);
typedef HI_S32 (*FN_PQ_UpdateVpssPQ)(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S* pstTimingInfo, PQ_VPSS_CFG_REG_S* pstVPSSReg, PQ_VPSS_WBC_REG_S* pstWbcReg, HI_PQ_VPSS_MODULE_S* pstPQModule);
typedef HI_S32 (*FN_PQ_UpdateVdpPQ)(HI_U32 u32DisplayId, HI_VDP_PQ_INFO_S* pstTimingInfo, S_VDP_REGS_TYPE* pstVDPReg);
typedef HI_S32 (*FN_PQ_UpdateVdpCSC)(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S* pstCscMode);
typedef HI_S32 (*FN_PQ_UpdateDCIWin)(HI_PQ_DCI_WIN_S* pstWin, HI_BOOL bDciEnable);
typedef HI_S32 (*FN_PQ_GetVpssScalerCoef)(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pvCoefAddrY, HI_VOID* pvCoefAddrC);
typedef HI_S32 (*FN_PQ_GetScalerCoef)(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pvCoefAddrY, HI_VOID* pvCoefAddrC);
typedef HI_S32 (*FN_PQ_GetWbcScalerCoef)(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pvCoefAddrY, HI_VOID* pvCoefAddrC);
typedef HI_S32 (*FN_PQ_SetZme)(HI_PQ_ZME_LAYER_E u32LayerId, HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_BOOL  bFirEnable);
typedef HI_S32 (*FN_PQ_SetVpssZme)(HI_PQ_VPSS_ZME_LAYER_E e32LayerId, S_CAS_REGS_TYPE* pstReg, HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_BOOL  bFirEnable);
typedef HI_S32 (*FN_PQ_GetCSCCoef)(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S* pstCSCCoef, HI_PQ_CSC_DCCOEF_S* pstCSCDCCoef);
typedef HI_S32 (*FN_PQ_Get8BitCSCCoef)(HI_PQ_CSC_MODE_E  enCSCMode, HI_PQ_CSC_COEF_S* pstCSCCoef, HI_PQ_CSC_DCCOEF_S* pstCSCDCCoef);
typedef HI_S32 (*FN_PQ_DBCalcCfg)(HI_PQ_DB_CALC_INFO_S* pstDbCalcInfo);
typedef HI_S32 (*FN_PQ_GetWbcInfo)(HI_PQ_WBC_INFO_S* pstVpssWbcInfo);
typedef HI_S32 (*FN_PQ_SetAlgCalcCfg)(HI_PQ_WBC_INFO_S* pstVpssWbcInfo, HI_PQ_CFG_INFO_S* pstVpssCfgInfo);
typedef HI_S32 (*FN_PQ_GetTnrGlobalMotion)(HI_PQ_TNR_MOTION_PARAM_IN_S* pstParamIn, HI_PQ_TNR_MOTION_RESULT_S* pstMotionResult);
typedef HI_S32 (*FN_PQ_GetAdaptiveDBStrength)(HI_PQ_DB_STR_PARAM_IN_S* pstParamIn, HI_PQ_DB_WEIGHT_S* pstDBstr);
typedef HI_S32 (*FN_PQ_GetPfmdDetect)(HI_PQ_PFMD_CALC_S* pstPfmdCalc, HI_PQ_PFMD_PLAYBACK_S* pstPfmdResult);
typedef HI_S32 (*FN_PQ_IfmdDect)(HI_PQ_IFMD_CALC_S* pstIfmdCalc, HI_PQ_IFMD_PLAYBACK_S* pstIfmdResult);
typedef HI_S32 (*FN_PQ_GetDciHistgram)(HI_PQ_HISTGRAM_S* pstDciHist);
typedef HI_S32 (*FN_PQ_GetHDPictureSetting)(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);
typedef HI_S32 (*FN_PQ_GetSDPictureSetting)(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);
typedef HI_S32 (*FN_PQ_SetHDPictureSetting)(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);
typedef HI_S32 (*FN_PQ_SetSDPictureSetting)(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);


typedef struct tagPQ_EXPORT_FUNC_S
{
    FN_PQ_GetPqParam              pfnPQ_GetPqParam;
    FN_PQ_UpdateVpssPQ            pfnPQ_UpdateVpssPQ;
    FN_PQ_UpdateVdpPQ             pfnPQ_UpdateVdpPQ;
    FN_PQ_UpdateVdpCSC            pfnPQ_UpdateVdpCSC;
    FN_PQ_UpdateDCIWin            pfnPQ_UpdateDCIWin;
    FN_PQ_GetVpssScalerCoef       pfnPQ_GetVpssScalerCoef;
    FN_PQ_GetScalerCoef           pfnPQ_GetScalerCoef;
    FN_PQ_GetWbcScalerCoef        pfnPQ_GetWbcScalerCoef;
    FN_PQ_SetZme                  pfnPQ_SetZme;
    FN_PQ_SetVpssZme              pfnPQ_SetVpssZme;
    FN_PQ_GetCSCCoef              pfnPQ_GetCSCCoef;
    FN_PQ_Get8BitCSCCoef          pfnPQ_Get8BitCSCCoef;
    FN_PQ_DBCalcCfg               pfnPQ_DBCalcCfg;
    FN_PQ_GetWbcInfo              pfnPQ_GetWbcInfo;
    FN_PQ_SetAlgCalcCfg           pfnPQ_SetAlgCalcCfg;
    FN_PQ_GetTnrGlobalMotion      pfnPQ_GGetTnrGlobalMotion;
    FN_PQ_GetAdaptiveDBStrength   pfnPQ_GetAdaptiveDBStrength;
    FN_PQ_GetPfmdDetect           pfnPQ_PfmdDetect;
    FN_PQ_IfmdDect                pfnPQ_IfmdDect;
    FN_PQ_GetDciHistgram          pfnPQ_GetDciHistgram;
    FN_PQ_GetHDPictureSetting     pfnPQ_GetHDPictureSetting;
    FN_PQ_GetSDPictureSetting     pfnPQ_GetSDPictureSetting;
    FN_PQ_SetHDPictureSetting     pfnPQ_SetHDPictureSetting;
    FN_PQ_SetSDPictureSetting     pfnPQ_SetSDPictureSetting;

} PQ_EXPORT_FUNC_S;


/**
\brief Timming�仯�����VPSS PQ��������
\attention \n
��

\param[in] *u32HandleNo:VPSSͨ����
\param[in] *pstTimingInfo: Timming Info
\param[in] *pstVPSSReg:VPSS ����Ĵ�����ַ�����ΪNULL�����ʾ���ٸ�·��ַ,
һ��handleNo��Ӧһ����ַ������ַ�����仯���Ż����¸���ʼֵ�����򲻸���ʼֵ��
\param[out] *pstPQModule:PQ���������Ŀ��ز���

\retval ::HI_SUCCESS

*/

extern HI_S32 DRV_PQ_UpdateVpssPQ(HI_U32 u32HandleNo, HI_VPSS_PQ_INFO_S* pstTimingInfo, PQ_VPSS_CFG_REG_S* pstVPSSReg, PQ_VPSS_WBC_REG_S* pstWbcReg, HI_PQ_VPSS_MODULE_S* pstPQModule);

/**
 \brief Timming�仯�����VDP PQ��������
 \attention \n
��

 \param[in] u32DisplayId
 \param[in] pstTimingInfo: Timming Info
 \param[in] *pstVDPReg:VDP ����Ĵ�����ַ

 \retval ::HI_SUCCESS

 */

extern HI_S32 DRV_PQ_UpdateVdpPQ(HI_U32 u32DisplayId, HI_VDP_PQ_INFO_S* pstTimingInfo, S_VDP_REGS_TYPE* pstVDPReg);

/**
 \brief ����VDP��ͨ����CSC
 \attention \n
��

 \param[in] enDisplayId:
 \param[in] pstCscMode: ɫ�ʿռ�

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_UpdateVdpCSC(HI_PQ_CSC_ID_E enDisplayId, HI_PQ_VDP_CSC_S* pstCscMode);

/**
 \brief ����DCIֱ��ͼͳ�ƴ���
 \attention \n
��

 \param[in] *pstWin;

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_UpdateDCIWin(HI_PQ_DCI_WIN_S* pstWin, HI_BOOL bDciEnable);

/**
 \brief ����VPSS scalerϵ��
 \attention \n
��

 \param[in] pstScalerInfo:������Ϣ
 \param[out] pvCoefAddr:����ϵ����ַ

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetVpssScalerCoef(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pvCoefAddrY, HI_VOID* pvCoefAddrC);
/**
 \brief ����VDP scalerϵ��
 \attention \n
��

 \param[in] pstScalerInfo:������Ϣ
 \param[out] pvCoefAddr:����ϵ����ַ

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetScalerCoef(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pvCoefAddrY, HI_VOID* pvCoefAddrC);
/**
 \brief ����WBC scalerϵ��
 \attention \n
��

 \param[in] pstScalerInfo:������Ϣ
 \param[out] pvCoefAddr:����ϵ����ַ

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetWbcScalerCoef(HI_PQ_SCALER_S* pstScalerInfo, HI_VOID* pvCoefAddrY, HI_VOID* pvCoefAddrC);

/**
 \brief ����ZME
 \attention \n
��

 \param[in] u32LayerId:
 \param[in] pstZmeDrvPara:
 \param[in] bFirEnable

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_SetZme(HI_PQ_ZME_LAYER_E e32LayerId, HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_BOOL bFirEnable);

/**
 \brief ����ZME
 \attention \n
��

 \param[in] u32LayerId:
 \param[in] pstZmeDrvPara:
 \param[in] bFirEnable

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_SetVpssZme(HI_PQ_VPSS_ZME_LAYER_E e32LayerId, S_CAS_REGS_TYPE* pstReg, HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_BOOL bFirEnable);

/**
 \brief ��ȡCSCϵ��
 \attention \n
��

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetCSCCoef(HI_PQ_CSC_MODE_E enCSCMode, HI_PQ_CSC_COEF_S* pstCSCCoef, HI_PQ_CSC_DCCOEF_S* pstCSCDCCoef);

/**
 \brief ��ȡ8bit CSCϵ��
 \attention \n
��

 \param[in] enCSCMode:
 \param[out] pstCSCCoef:
 \param[out] pstCSCDCCoef:

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_Get8BitCSCCoef(HI_PQ_CSC_MODE_E enCSCMode, HI_PQ_CSC_COEF_S* pstCSCCoef, HI_PQ_CSC_DCCOEF_S* pstCSCDCCoef);

#if 0
/**
 \brief ���д�DEI��ȡ��Global Motion��Ϣ
 \attention \n
��

 \param[in] *pstMotionHist:ֱ��ͼ
 \param[out] *pstMotionResult:�˶���Ϣ

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_SetDeiGlobalMotion(HI_PQ_WBC_INFO_S* pstWbcInfo, HI_PQ_MOTION_INFO_S* pstMotionResult);
#endif


/**
 \brief �����㷨������֮��ļĴ���
 \attention \n
��

 \param[in]  *pstWbcInfo
 \param[out]
 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_SetAlgCalcCfg(HI_PQ_WBC_INFO_S* pstVpssWbcInfo, HI_PQ_CFG_INFO_S* pstVpssCfgInfo);

/**
 \brief ��ȡWbcInfo��Ϣ
 \attention \n
��

 \param[in]  HI_PQ_WBC_INFO_S* pstWbcInfo

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetWbcInfo(HI_PQ_WBC_INFO_S* pstVpssWbcInfo);

/**
\brief     :Tnr��Global Motion���㷨API

\attention :
            ���㷨�ο�DEIģ�������ֲ
            �㷨�ṩ���ᳯ�� p00188942����ֲ&ά���������� l00268071
            �㷨���Ѿ���u32GlobalMotion��u32AdjustGain�䵽��Ӧ�Ĵ�����

\param[in] :pstParamIn�ṹ����������Ԫ��
            u32HdlNo ʵ����ID
            u32Width ����ͼ����
            u32Height ����ͼ��߶�
            pstMotionReg �Ĵ�����ַ

\param[out]:pstMotionResult�ṹ����������Ԫ��
            u32GlobalMotion
            u32AdjustGain

\retval    :HI_SUCCESS/HI_FAILURE

*/
extern HI_S32 DRV_PQ_GetTnrGlobalMotion(HI_PQ_TNR_MOTION_PARAM_IN_S* pstParamIn, HI_PQ_TNR_MOTION_RESULT_S* pstMotionResult);


/**
\brief     :����Global Motion��ȡDB������Ӧǿ��ֵAPI

\attention :�����ڶԶ�ʵ����ID u32HdlNo ������Լ�⣬���ж���ֵ
            ���л��������ź�Դ�����õ�Global Motion��ͬ��
            �㷨���Ѿ����������u8HWeight��u8VWeight�䵽�Ĵ���VPSS_DB_WEIGHT��
            �㷨�ṩ������÷ y00224511����ֲ&ά���������� l00268071

\param[in] :pstParamIn�ṹ����������Ԫ��
            u32HdlNo ʵ����ID
            u8SCDStr �Ǹ���SCD��api����ó���һ��ֵ[0,255]
            pstReg   global motion �Ĵ�����ַ
            eType ����Դ���ͣ����л����У��Ƿ���DEI

\param[out]:pstDBstr  DBǿ��ֵ����Ӧ�Ĵ���VPSS_DB_WEIGHT���ֱ�Ϊu8HWeight��u8VWeight

\retval    :HI_SUCCESS/HI_FAILURE

*/
extern HI_S32 DRV_PQ_GetAdaptiveDBStrength(HI_PQ_DB_STR_PARAM_IN_S* pstParamIn, HI_PQ_DB_WEIGHT_S* pstDBstr);


/**
 \brief ����FMDģʽ���
 \attention \n
��

 \param[in] pstVPSSReg: VPSS����Ĵ�����ַ

 \retval ::HI_SUCCESS

 */

extern HI_S32 DRV_PQ_PfmdDetect(HI_PQ_PFMD_CALC_S* pstPfmdCalc, HI_PQ_PFMD_PLAYBACK_S* pstPfmdResult);

/**
 \brief ����FMDģʽ���
 \attention \n
��

 \param[in] pstVPSSReg: VPSS����Ĵ�����ַ

 \retval ::HI_SUCCESS

 */

//extern HI_S32 DRV_PQ_IFMDDetect(S_CAS_REGS_TYPE *pstVPSSReg);
extern HI_S32 DRV_PQ_IfmdDect(HI_PQ_IFMD_CALC_S* pstIfmdCalc, HI_PQ_IFMD_PLAYBACK_S* pstIfmdResult);

/**
 \brief ��ȡDCIֱ��ͼ
 \attention \n
��

 \param[in] *pstDciHist:0-255

 \retval ::HI_SUCCESS

 */

extern HI_S32 DRV_PQ_GetDciHistgram(HI_PQ_HISTGRAM_S* pstDciHist);


/**
 \brief ��ȡ��������/�Աȶ�/ɫ��/���Ͷ�/ɫ��
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�/ɫ��

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetHDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);

/**
 \brief ��ȡ��������/�Աȶ�/ɫ��/���Ͷ�/ɫ��
 \attention \n
��

 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�/ɫ��

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_GetSDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);


/**
 \brief ���ø�������/�Աȶ�/ɫ��/���Ͷ�/ɫ��
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�/ɫ��

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_SetHDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);

/**
 \brief ���ñ�������/�Աȶ�/ɫ��/���Ͷ�/ɫ��
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�/ɫ��

 \retval ::HI_SUCCESS

 */
extern HI_S32 DRV_PQ_SetSDPictureSetting(HI_PQ_PICTURE_SETTING_S* pstPictureSetting);

/**
 \brief VPSS ZME��������У��;
 \attention \n
��

 \param[in]
 u32InWitdh: �����; u32InHeigh: �����; stZmeWin: ����������;

 \param[out]
 pu32OutWitdh �����; pu32OutHeigh �����;

 \retval :
HI_SUCCESS : ��Ҫ��������
HI_FAILURE : ����Ҫ��������

 */
extern HI_S32 DRV_PQ_ZME_2L_Check(HI_U32 u32InWitdh, HI_U32 u32InHeigh, HI_PQ_ZME_WIN_S stZmeWin, HI_U32* pu32OutWitdh, HI_U32* pu32OutHeigh);


/**
 \brief ��ʼ��PQģ��;
 \attention \n
��

 \param[in] pszPath: PQ Table�ļ�·��, ���pszPath����Ϊ��ָ��, �����PQ SDK�ڲ�Ĭ�ϲ���;

 \retval ::HI_SUCCESS

 */

extern HI_S32 HI_DRV_PQ_Init(HI_CHAR* pszPath);

/**
 \brief ȥ��ʼ��PQģ��;
 \attention \n
  ��

 \param[in]

 \retval ::HI_SUCCESS

 */
extern HI_S32 HI_DRV_PQ_DeInit(HI_VOID);

extern HI_S32 PQ_DRV_ModInit(HI_VOID);
extern HI_VOID PQ_DRV_ModuleExit(HI_VOID);

extern HI_S32 DRV_PQ_SetSplitBlockZme(HI_PQ_ZME_PARA_IN_S* pstZmeDrvPara, HI_PQ_SPLIT_ZME_PARA_S* pstZmeSplitPara);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* End of #ifndef __DRV_PQ_EXT_H__ */
