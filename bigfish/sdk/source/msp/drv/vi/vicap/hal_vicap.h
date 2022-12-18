/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_vicap.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/147
  Description   : 
  History       :
  1.Date        : 2013/11/14
    Author      : w00248302/c186004
    Modification: Created file
******************************************************************************/

#ifndef __HAL_VICAP_H__
#define __HAL_VICAP_H__

#include "hi_drv_video.h"
#include "hi_reg_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define VICAP_HAL_NO_HSCALE_STEP 1048576
#define VICAP_HAL_NO_VSCALE_STEP 1

#define VICAP_REGS_ADDR        0xFF200000
#define VICAP_REGS_SIZE        0x10000

#define MAXPT    2
#define MAXCHN   2

/*�˿�*/
#define   VICAP_PHYPT_PT0   0
#define   VICAP_PHYPT_PT1  1   

/*ͨ��*/
#define   VICAP_PHYCHN_CHN0  0x01
#define   VICAP_PHYCHN_CHN1  0x02

typedef enum hiVICAP_FRAME_FILED_E
{
    VICAP_FRAME_FILED_TOP = 0,
    VICAP_FRAME_FILED_BOTTOM,
    VICAP_FRAME_FILED_FRAME,
    
    VICAP_FRAME_FILED_BUTT,
} VICAP_FRAME_FILED_E;


typedef enum hiVICAP_OUT_STANDING_E
{
    VICAP_OUT_ONE = 0,
    VICAP_OUT_TWO,
    VICAP_OUT_THREE,
    VICAP_OUT_FOUR,
    VICAP_OUT_FIVE,
    VICAP_OUT_SIX,
    VICAP_OUT_SEVEN,
    VICAP_OUT_EIGHT,
    
    VICAP_OUT_BUTT,
} VICAP_OUT_STANDING_E;


/* �ж�ʹ��������ж�״̬λ */
typedef enum hiVICAP_CHN_INT_E
{
    VICAP_CHN_INT_FRAMESTART = 0x0001,/* [0]����ʼ�ж�*/
    VICAP_CHN_INT_CC         = 0x0002,/* [1]��ȡ����ж�״̬*/
    VICAP_CHN_INT_BUFOVF     = 0x0004,/* [2]�ڲ�FIFO��������ж�״̬*/ 
    VICAP_CHN_INT_FIELDTHROW = 0x0008,/* [3]�����ݶ�ʧ�ж�*/        
    VICAP_CHN_INT_UPDATECFG  = 0x0010,/* [4]�����Ĵ��������ж�*/                        
    VICAP_CHN_INT_YBUSERR    = 0x0020,/* [5]Y����ͨ·���ߴ����ж�״̬*/  
    VICAP_CHN_INT_CBUSERR    = 0x0040,/* [6]C����ͨ·���ߴ����ж�״̬*/ 

    VICAP_CHN_INT_BUTT,
} VICAP_CHN_INT_E;

typedef enum hiVICAP_FIELD_SEL_E
{
    VICAP_FIELD_SEL_FIELD = 0,  /* ��ż���ź� */
    VICAP_FIELD_SEL_VSYNC,      /* ��ͬ���ź� */
    VICAP_FIELD_SEL_VSYNC_HSYNC,/* ����vsync��hsync�Ĺ�ϵ��� */
    VICAP_FIELD_SEL_ZERO,       /* FIELD�ź�ʼ��Ϊ0 */
    
    VICAP_FIELD_SEL_BUTT,
} VICAP_FIELD_SEL_E;

typedef enum hiVICAP_VSYNC_MODE_E
{
    VICAP_VSYNC_MODE_OFF = 0,      /* ������ */
    VICAP_VSYNC_MODE_SINGLE_UP,    /* �����ش���һ��Ϊһ��VSYNC */
    VICAP_VSYNC_MODE_SINGLE_DOUBLE,/* ˫��ģʽ����һ��Ϊһ��VSYNC */
    
    VICAP_VSYNC_MODE_BUTT,
} VICAP_VSYNC_MODE_E;

typedef enum hiVICAP_VSYNC_SEL_E
{
    VICAP_VSYNC_SEL_VSYNC = 0,/* ��ͬ���ź� */    
    VICAP_VSYNC_SEL_FIELD,    /* ��ż���ź� */  
    VICAP_VSYNC_SEL_ZERO,     /* VSYNC�ź�ʼ��Ϊ0 */
    
    VICAP_VSYNC_SEL_BUTT,
} VICAP_VSYNC_SEL_E;

typedef enum hiVICAP_HSYNC_MODE_E
{
    VICAP_HSYNC_MODE_OFF = 0,  /* ������ */
    VICAP_HSYNC_MODE_SINGLE_UP,/* �����ش���һ��Ϊһ��HSYNC */
    
    VICAP_HSYNC_MODE_BUTT,
} VICAP_HSYNC_MODE_E;

typedef enum hiVICAP_HSYNC_AND_E
{
    VICAP_HSYNC_AND_OFF = 0, /* ������ */
    VICAP_HSYNC_AND_VSYNCINV,/* hsync��vsync�������� */
    VICAP_HSYNC_XOR_VSYNCINV,/* hsync��vsync������� */
    
    VICAP_HSYNC_AND_BUTT,
} VICAP_HSYNC_AND_E;

typedef enum hiVICAP_HSYNC_SEL_E
{
    VICAP_HSYNC_SEL_HSYNC = 0,/* ˮƽͬ���ź� */    
    VICAP_HSYNC_SEL_DE,       /* ������Ч�ź� */
    VICAP_HSYNC_SEL_ZERO,     /* HSYNC�ź�ʼ��Ϊ0 */
    
    VICAP_HSYNC_SEL_BUTT,
} VICAP_HSYNC_SEL_E;

typedef enum hiVICAP_DE_SEL_E
{
    VICAP_DE_SEL_DE = 0,   /* ������Ч�ź� */
    VICAP_DE_SEL_HSYNC_AND,/* hsync��vsync���Դ����Ľ�� */
    VICAP_DE_SEL_ONE,      /* HSYNC�ź�ʼ��Ϊ1 */
    VICAP_DE_SEL_ZERO,     /* HSYNC�ź�ʼ��Ϊ0 */
    
    VICAP_DE_SEL_BUTT,
} VICAP_DE_SEL_E;

typedef struct hiSIZE_S
{
    HI_U32 u32Width;
    HI_U32 u32Height;
} SIZE_S;

typedef enum hiVICAP_DITHER_CFG_E
{
    VICAP_DITHER_10BIT = 0,/* 10bit��� */
    VICAP_DITHER_8BIT,   /* 8bit��� */
    
    VICAP_DITHER_BUTT,
} VICAP_DITHER_CFG_E;

/*����������Զ���*/
typedef enum hiVICAP_CHN_SCALE_OBJ_E
{
    VICAP_CHN_SCALE_OBJ_YH = 0,
    VICAP_CHN_SCALE_OBJ_CH,
    
    VICAP_CHN_SCALE_OBJ_BUTT,
} VICAP_CHN_SCALE_OBJ_E;

/*����ģʽ*/
typedef enum hiVICAP_CHN_SCALE_MODE_E
{
    VICAP_CHN_SCALE_MODE_FILT = 0,
    VICAP_CHN_SCALE_MODE_COPY,
    
    VICAP_CHN_SCALE_MODE_BUTT,
} VICAP_CHN_SCALE_MODE_E;

typedef enum hiVICAP_CHN_COEF_UPDATE_E
{
    VICAP_CHN_LHCOEF_UPDATE = 0,
    VICAP_CHN_CHCOEF_UPDATE,
    
    VICAP_CHN_COEF_BUTT,
} VICAP_CHN_COEF_UPDATE_E;


typedef enum hiVICAP_UPDATE_SCALE_TYPE_E
{
    VICAP_UPDATE_SCALE_PARAM = 0,/*���³�����ϵ������������Ų���*/
    VICAP_UPDATE_SCALE_COEF,     /*��������ϵ��*/
    
    VICAP_UPDATE_SCALE_BUTT,
} VICAP_UPDATE_SCALE_TYPE_E;


/*port ����ʱ��FVHDE����*/
typedef struct hiVICAP_SYNC_CFG_S
{
    HI_BOOL            bFieldInv;  /* ��ż���źŵļ��� */  
    VICAP_FIELD_SEL_E  enFieldSel; /* ��ż���źŵ�ѡ�� */
    VICAP_VSYNC_MODE_E enVsyncMode;/* ��ֱͬ������ģʽ */
    HI_BOOL            bVsyncInv;  /* ��ֱͬ���źż��� */     
    VICAP_VSYNC_SEL_E  enVsyncSel; /* ��ֱͬ���źŵ�ѡ�� */
    VICAP_HSYNC_MODE_E enHsyncMode;/* ��ͬ������ģʽ */
    VICAP_HSYNC_AND_E  enHsyncAnd; /* ��ͬ���볡ͬ�����ԵĴ��� */ 
    HI_BOOL            bHsyncInv;  /* ��ͬ���źŵļ��� */
    VICAP_HSYNC_SEL_E  enHsyncSel; /* ��ͬ���źŵ�ѡ�� */
    HI_BOOL            bDeInv;     /* ������Ч�źŵļ��� */
    VICAP_DE_SEL_E     enDeSel;    /* ������Ч�źŵ�ѡ�� */
} VICAP_SYNC_CFG_S;

/* �ӿ�ģʽ */
typedef enum hiVICAP_INTF_MODE_E
{
    VICAP_INTF_MODE_FVHDE = 0,
    VICAP_INTF_MODE_BT601,
    VICAP_INTF_MODE_BT656,
    VICAP_INTF_MODE_BT1120,
    
    VICAP_INTF_MODE_BUTT
} VICAP_INTF_MODE_E;


typedef enum hiVICAP_COMP_MODE_E
{
    VICAP_COMP_MODE_SINGLE = 0,/* ������ */
    VICAP_COMP_MODE_DOUBLE,    /* ˫���� */
    VICAP_COMP_MODE_THREE,     /* ������ */
    
    VICAP_COMP_MODE_BUTT,   
} VICAP_COMP_MODE_E;

typedef enum hiVICAP_FILED_MODE_E
{
    VICAP_FILED_MODE_TOP = 0,   /* ���� */
    VICAP_FILED_MODE_BOTTOM,    /* �׳� */
    
    VICAP_FILED_MODE_BUTT,   
} VICAP_FILED_MODE_E;

typedef enum hiVICAP_HEDTWORD_MODE_E
{
    VICAP_HEDTWORD_MODE_128BIT = 0,
    VICAP_HEDTWORD_MODE_256BIT,
    
    VICAP_HEDTWORD_MODE_BUTT,
} VICAP_HEDTWORD_MODE_E;

typedef enum hiVICAP_CMP_MODE_E
{
    VICAP_CMP_MODE_128pix = 0,
    VICAP_CMP_MODE_192pix_256pix,
    
    VICAP_CMP_MODE_BUTT,
} VICAP_CMP_MODE_E;

/*VICAPͼ��洢��Ϣ*/
typedef struct hiVICAP_ADDR_S
{
    HI_U32 u32YAddr;
    HI_U32 u32CAddr;
    //HI_U32 u32YStride;
    //HI_U32 u32CStride;
} VICAP_ADDR_S;

typedef enum hiVICAP_WCH_MODE_E
{
    VICAP_WCH_MODE_Y = 0,
    VICAP_WCH_MODE_C,
        
    VICAP_WCH_MODE_BUTT,

}VICAP_WCH_MODE_E;


/*WCH_CFG*/
typedef struct hiVICAP_WCH_CFG_S
{
    HI_BOOL                 bInterlace;
    VICAP_FILED_MODE_E      enFiled;
    HI_DRV_PIXEL_BITWIDTH_E enBitWidth;
    VICAP_HEDTWORD_MODE_E   enHeadTword;
    VICAP_CMP_MODE_E        enCmpMode;
    HI_BOOL                 benableCmp;
}VICAP_WCH_CFG_S;


typedef struct hiVICAP_SCALE_ATTR_S
{
    HI_U32 u32InImgWidth;/*����ͼ����*/
    HI_U32 u32InImgHeight;/*����ͼ��߶�*/
    HI_U32 u32OutImgWidth;/*���ͼ����*/
    HI_U32 u32OutImgHeight;/*����ͼ��߶�*/
    HI_DRV_PIX_FORMAT_E enPixFormat;/*���ظ�ʽ*/ 
    HI_DRV_PIX_FORMAT_E  enVideoFmt;/*��Ƶ�洢��ʽ*/
} VICAP_SCALE_ATTR_S;

typedef struct hiVICAP_SCALE_SIZE_S
{
    HI_U32 u32YInPixel;/*����ͼ��Y���*/
    HI_U32 u32YInLine;/*����ͼ��Y�߶�*/
    HI_U32 u32YOutPixel;/*���ͼ��Y���*/
    HI_U32 u32YOutLine;/*����ͼ��Y�߶�*/
    HI_U32 u32CInPixel;/*����ͼ��Y���*/
    HI_U32 u32CInLine;/*����ͼ��Y�߶�*/
    HI_U32 u32COutPixel;/*���ͼ��Y���*/
    HI_U32 u32COutLine;/*����ͼ��Y�߶�*/
} VICAP_SCALE_SIZE_S;

/* ͨ���ü����� */
typedef struct hiVICAP_CROP_CFG_S
{
    HI_BOOL   bCropEn[2];   /* ͨ���������ü�����Ŀ��� */
    HI_RECT_S stCropRect[2];/* ͨ���������ü����� */
} VICAP_CROP_CFG_S;

/*CSC ����ϵ���ṹ*/
typedef struct  hiVICAP_CSC_COEF_S
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
} VICAP_CSC_COEF_S;

typedef struct  hiVICAP_CSC_DCCOEF_S
{
    HI_S32 csc_in_dc0;
    HI_S32 csc_in_dc1;
    HI_S32 csc_in_dc2;

    HI_S32 csc_out_dc0;
    HI_S32 csc_out_dc1;
    HI_S32 csc_out_dc2;
} VICAP_CSC_DCCOEF_S;

typedef enum hiVICAP_FILED_FRAME_E
{
    VICAP_FILED_FRAME_TOP = 0,
    VICAP_FILED_FRAME_BOTTOM,
    VICAP_FILED_FRAME_FRAME,
    
    VICAP_FILED_FRAME_BUTT,
} VICAP_FILED_FRAME_E;

/* Wch���� */
typedef struct hiVICAP_CHN_WCH_CFG_S
{
   VICAP_FILED_FRAME_E      enField; 
   HI_BOOL                  bInterlace;
   HI_DRV_PIXEL_BITWIDTH_E  enDstBitWidth;
} VICAP_CHN_WCH_CFG_S;

typedef enum hiVICAP_SCALE_COEFPARA_E
{
    VICAP_SCALE_COEFPARA_NO = 0,
    VICAP_SCALE_COEFPARA_2X,
    VICAP_SCALE_COEFPARA_3X,
    VICAP_SCALE_COEFPARA_4X,
    VICAP_SCALE_COEFPARA_OTHER,
        
    VICAP_SCALE_COEFPARA_BUTT,

}VICAP_SCALE_COEFPARA_E;

/* CRG����ʱ���ſ� */
HI_VOID VICAP_HAL_SetBusClken(HI_BOOL bEnable);
/* CRG PT ʱ���ſ� */ 
HI_VOID VICAP_HAL_SetPtClken(HI_U32 u32PtIndex, HI_BOOL bEnable);
/* CRG PPC ʱ���ſ� */ 
HI_VOID VICAP_HAL_SetPpcClken(HI_U32 u32ChnIndex, HI_BOOL bEnable);

/* CRG���߸�λ */
HI_VOID VICAP_HAL_SetBusReset(HI_BOOL bEnable);
/* CRG PT ��λ */
HI_VOID VICAP_HAL_SetPtReset(HI_U32 u32PtIndex, HI_BOOL bEnable);
/* CRG PPC ��λ */
HI_VOID VICAP_HAL_SetPpcReset(HI_U32 u32ChnIndex, HI_BOOL bEnable);


/* ��ʼ�� */
HI_S32 VICAP_HAL_BoardInit(HI_VOID);

/* ȥ��ʼ�� */
HI_VOID VICAP_HAL_BoardDeInit(HI_VOID);

/*����ж�*/
HI_VOID VICAP_HAL_ClrChnIntStatus(HI_U32 s32ChnIndex, HI_U32 u32ClrInt);

/*��ȡ�ж�״̬*/
HI_S32 VICAP_HAL_GetChnIntStatus(HI_U32 s32ChnIndex);

/*�˿��Ƿ�ʹ��*/
HI_S32  VICAP_HAL_GetPtIntfMode(HI_U32 s32PtIndex);

/*yuv422�ϲ�����YUV444*/
HI_VOID VICAP_HAL_SetPortUpToYuv444(HI_U32 u32PtIndex,HI_BOOL bUptoYuv444);

/* ���ýӿ�ģʽ */
HI_VOID VICAP_HAL_SetPortIntfMode(HI_U32 u32PtIndex,VICAP_INTF_MODE_E enIntfMode);

/* ���ö˿ڵķ���ģʽ */
HI_VOID VICAP_HAL_SetPortCompMode(HI_U32 u32PtIndex,VICAP_COMP_MODE_E enCompMode);

/* ���ö˿���������ƫ��/���� */
HI_VOID VICAP_HAL_SetPortDataLayout(HI_U32 u32PtIndex,HI_U32 au32Offset[3], HI_U32 au32CompMask[3]);

/* ���ö˿�FVHDEͬ���źŵ����� */
HI_VOID VICAP_HAL_SetPortSyncCfg(HI_U32 u32PtIndex,VICAP_SYNC_CFG_S *pstSyncCfg);

/* ���ö˿��ж�mask */
HI_VOID VICAP_HAL_SetPortIntMask(HI_U32 u32PtIndex,HI_U32 u32IntMask);

/* ����/ʹ�ܶ˿� */
HI_VOID VICAP_HAL_SetPortEn(HI_U32 u32PtIndex,HI_BOOL bEnalbe);

/* ����ͨ��������SKIP��Ϣ */
HI_VOID VICAP_HAL_SetSkipYCfg(HI_U32 s32ChnIndex, HI_U32 u32SkipCfg);

/* ����ͨ����ɫ��SKIP��Ϣ*/
HI_VOID VICAP_HAL_SetSkipCCfg(HI_U32 s32ChnIndex, HI_U32 u32SkipCfg);

/*Y�������*/
HI_VOID VICAP_HAL_SetWchYStride(HI_U32 s32ChnIndex, HI_U32 u32YStride);

/*C�������*/
HI_VOID VICAP_HAL_SetWchCStride(HI_U32 s32ChnIndex, HI_U32 u32CStride);

/* VIȫ���ж�mask */
HI_VOID VICAP_HAL_SetVicapIntChnMask(HI_U32 u32ChnIndex,HI_BOOL bValid);
HI_VOID VICAP_HAL_SetVicapIntPtMask(HI_U32 u32PtIndex,HI_BOOL bValid);



/*ͨ���ж�mask*/
HI_VOID VICAP_HAL_SetChnIntMask(HI_U32 s32ChnIndex, HI_U32 u32IntMask);

/*ʹ��/����ͨ��*/
HI_VOID VICAP_HAL_SetChnEn(HI_U32 s32ChnIndex, HI_BOOL bEn);

/*��ȡͨ��ʹ��״̬*/
HI_S32 VICAP_HAL_GetChnEnStatus(HI_U32 s32ChnIndex);

/* ��ȡ��ǰ���Ƿ�Ϊ����(�泡)�������ź���Ч */
VICAP_FRAME_FILED_E VICAP_HAL_IsTopField(HI_U32 u32PtIndex);

/* 
 * ����ͨ���ü�����
 * ͼ��һ�еĿ��(������Ϊ��λ)������ֵΪʵ��ֵ��1 
 * ��ȡͼ��ĸ߶�(����Ϊ��λ)������ֵΪʵ��ֵ��1
 */
HI_VOID VICAP_HAL_SetChnCrop(HI_U32 s32ChnIndex, VICAP_CROP_CFG_S *pstCropCfg);

/* ����ͨ��DITHERģʽ��Ϣ */
HI_VOID VICAP_HAL_SetDitherCfg(HI_U32 s32ChnIndex, VICAP_DITHER_CFG_E enDitherCfg);

/*CSCʹ��*/
HI_VOID VICAP_HAL_SetChnCscEn(HI_U32 s32ChnIndex, HI_BOOL bEnableCsc);


/*����CSC����*/
HI_VOID VICAP_HAL_SetChnCsc(HI_U32 s32ChnIndex, VICAP_CSC_COEF_S *pstVicapCSCCoef, VICAP_CSC_DCCOEF_S *pstVicapCSCDCCoef);


/* ������������������ */
HI_S32 VICAP_HAL_SetScaleSize(HI_S32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, VICAP_SCALE_SIZE_S *pstScaleSize);

/*ˮƽ��������*/
HI_S32 VICAP_HAL_SetHScale(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_U32 u32Ratio,VICAP_CHN_SCALE_MODE_E enMode, HI_BOOL bMidEn, HI_BOOL bScaleEn);

/*��ֱ��������*/
HI_S32 VICAP_HAL_SetVScale(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_U32 u32Ratio,HI_BOOL bScaleEn);

/* ˮƽ����ʹ�� */
HI_S32 VICAP_HAL_HScaleEn(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, HI_BOOL bEn);

/*��ֱ����ʹ��*/
HI_S32 VICAP_HAL_VScaleEn(HI_U32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj,HI_BOOL bScaleEn);

/* ����ˮƽ����8��ϵ�� */
HI_S32 VICAP_HAL_SetHScaleCoef8Phase(HI_S32 s32ChnIndex, VICAP_CHN_SCALE_OBJ_E enObj, VICAP_SCALE_COEFPARA_E eYCoefPara);

/* ����ˮƽ���Ų������� */
HI_S32 VICAP_HAL_SetCoefUpdate(HI_S32 s32ChnIndex, VICAP_CHN_COEF_UPDATE_E enMod);


HI_VOID VICAP_HAL_SetChnWchSize(HI_U32 s32ChnIndex,HI_U32 u32Width, HI_U32 u32Height,VICAP_WCH_MODE_E enWchMode);

HI_VOID VICAP_HAL_SetChnWchCfg(HI_U32 s32ChnIndex,VICAP_CHN_WCH_CFG_S *stWchCfg,VICAP_WCH_MODE_E enWchMode);

HI_VOID VICAP_HAL_SetChnWchAddr(HI_U32 s32ChnIndex,VICAP_ADDR_S *stVicapAddr,VICAP_WCH_MODE_E enWchMode);

/* ����ͨ�����¼Ĵ��� */
HI_VOID VICAP_HAL_SetRegNewer(HI_S32 s32ChnIndex);

/* ��ʼ��Ӳ�� */
HI_VOID VICAP_HAL_Init(HI_VOID);

/*�˿�ʱ��ѡ��*/
HI_VOID VICAP_HAL_SetPtClk(HI_U32 u32PtIndex);

/*ͨ��ʱ��ѡ��*/
HI_VOID VICAP_HAL_SetChnClk(HI_U32 u32PtIndex,HI_U32 u32ChnIndex);

HI_VOID VicapHalDumpReg(HI_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif/* __HAL_VICAP_H__ */

