/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_hal.h
* Description:TDE hal interface define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/

#ifndef _TDE_HAL_H_
#define _TDE_HAL_H_

#include "hi_tde_type.h"
#include "tde_define.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

/****************************************************************************/
/*                             TDE hal types define                         */
/****************************************************************************/
typedef enum hiTDE_DRV_COLOR_FMT_E
{
    TDE_DRV_COLOR_FMT_RGB444   = 0,
    TDE_DRV_COLOR_FMT_RGB555   = 1,
    TDE_DRV_COLOR_FMT_RGB565   = 2,
    TDE_DRV_COLOR_FMT_RGB888   = 3,
    TDE_DRV_COLOR_FMT_ARGB4444 = 4,
    TDE_DRV_COLOR_FMT_ARGB1555 = 5,
    TDE_DRV_COLOR_FMT_ARGB8565 = 6,
    TDE_DRV_COLOR_FMT_ARGB8888 = 7,
    TDE_DRV_COLOR_FMT_CLUT1   = 8,
    TDE_DRV_COLOR_FMT_CLUT2   = 9,
    TDE_DRV_COLOR_FMT_CLUT4   = 10,
    TDE_DRV_COLOR_FMT_CLUT8   = 11,
    TDE_DRV_COLOR_FMT_ACLUT44 = 12,
    TDE_DRV_COLOR_FMT_ACLUT88 = 13,
    TDE_DRV_COLOR_FMT_A1 = 16,
    TDE_DRV_COLOR_FMT_A8 = 17,
    TDE_DRV_COLOR_FMT_YCbCr888   = 18,
    TDE_DRV_COLOR_FMT_AYCbCr8888 = 19,
    TDE_DRV_COLOR_FMT_YCbCr422 = 20,
    TDE_DRV_COLOR_FMT_byte = 22,
    TDE_DRV_COLOR_FMT_halfword = 23,
    TDE_DRV_COLOR_FMT_YCbCr400MBP = 24,
    TDE_DRV_COLOR_FMT_YCbCr422MBH = 25,
    TDE_DRV_COLOR_FMT_YCbCr422MBV = 26,
    TDE_DRV_COLOR_FMT_YCbCr420MB = 27,
    TDE_DRV_COLOR_FMT_YCbCr444MB = 28,
    TDE_DRV_COLOR_FMT_BUTT
} TDE_DRV_COLOR_FMT_E;

/* TDE��������ģʽ */
typedef enum hiTDE_DRV_BASEOPT_MODE_E
{
    /*�������*/
    TDE_QUIKE_FILL,

    /*���ٿ���*/
    TDE_QUIKE_COPY,

    /*��ͨ��Դ���*/
    TDE_NORM_FILL_1OPT,

    /*��ͨ��Դ��������*/
    TDE_NORM_BLIT_1OPT,

    /*���ɫ��λͼ�����������*/
    TDE_NORM_FILL_2OPT,

    /*��ͨ˫Դ�������� */
    TDE_NORM_BLIT_2OPT,

    /*������*/
    TDE_MB_C_OPT,    /*���ɫ������*/
    TDE_MB_Y_OPT,    /*�����������*/
    TDE_MB_2OPT,      /*���ϲ�����*/

    /*��Դģʽ������*/
    TDE_SINGLE_SRC_PATTERN_FILL_OPT,

    /*˫Դģʽ������*/
    TDE_DOUBLE_SRC_PATTERN_FILL_OPT
} TDE_DRV_BASEOPT_MODE_E;

/* �ж�״̬���Ͷ��� */
typedef enum hiTDE_DRV_INT_STATS_E
{
    TDE_DRV_LINK_COMPLD_STATS = 0x1,
    TDE_DRV_NODE_COMPLD_STATS = 0x2,
    TDE_DRV_LINE_SUSP_STATS = 0x4,
    TDE_DRV_RDY_START_STATS = 0x8,
    TDE_DRV_SQ_UPDATE_STATS = 0x10,
    TDE_DRV_INT_ALL_STATS = 0x800F001F
} TDE_DRV_INT_STATS_E;

/* Ӳ����Ҫ��ColorKeyģʽ */
typedef enum hiTDE_DRV_COLORKEY_MODE_E
{
    TDE_DRV_COLORKEY_BACKGROUND = 0,          /* �Ա���λͼ����color key*/
    TDE_DRV_COLORKEY_FOREGROUND_BEFORE_CLUT = 2,  /* ��ǰ��λͼ����color key,��Clutǰ*/
    TDE_DRV_COLORKEY_FOREGROUND_AFTER_CLUT = 3    /* ��ǰ��λͼ����color key,��Clut��*/
} TDE_DRV_COLORKEY_MODE_E;

/* color key ���ò��� */
typedef struct hiTDE_DRV_COLORKEY_CMD_S
{
    TDE_DRV_COLORKEY_MODE_E enColorKeyMode;        /*color key��ʽ*/
    TDE2_COLORKEY_U        unColorKeyValue;       /*color key����ֵ*/
} TDE_DRV_COLORKEY_CMD_S;

/* ����˸�˲�ģʽ */
typedef enum hiTDE_DRV_FLICKER_MODE
{
    TDE_DRV_FIXED_COEF0 = 0,   /*ʹ�ù̶�ϵ��0���п���˸*/
    TDE_DRV_AUTO_FILTER,       /*ʹ������Ӧ����˸�˲���*/
    TDE_DRV_TEST_FILTER        /*ʹ�ò���ģʽ����˸�˲���*/
} TDE_DRV_FLICKER_MODE;

/* �ֿ�����,������ֵ�ο��Ĵ����ֲ� */
typedef enum hiTDE_SLICE_TYPE_E
{
    TDE_NO_BLOCK_SLICE_TYPE = 0,         /* ����Ҫ�ֿ� */
    TDE_FIRST_BLOCK_SLICE_TYPE = 0x3,    /* ��һ�� */
    TDE_LAST_BLOCK_SLICE_TYPE = 0x5,     /* ���һ�� */
    TDE_MID_BLOCK_SLICE_TYPE = 0x1       /* �м�� */
} TDE_SLICE_TYPE_E;
/* ��ֱ/ˮƽ�˲�ģʽ:ֻ��������Ч */
typedef enum hiTDE_DRV_FILTER_MODE_E
{
    TDE_DRV_FILTER_NONE = 0,    /*�������˲�*/
    TDE_DRV_FILTER_COLOR,       /*ֻ����ɫֵ�˲�*/
    TDE_DRV_FILTER_ALPHA,       /*ֻ��Alphaֵ�˲�*/
    TDE_DRV_FILTER_ALL          /*����ɫ��Alphaֵ�˲�*/
} TDE_DRV_FILTER_MODE_E;

/* ����˸�������� */
typedef struct hiTDE_DRV_FLICKER_CMD_S
{
    TDE_DRV_FLICKER_MODE enDfeMode;
    TDE_DRV_FILTER_MODE_E enFilterV;
    HI_U8            u8Coef0LastLine;
    HI_U8            u8Coef0CurLine;
    HI_U8            u8Coef0NextLine;
    HI_U8            u8Coef1LastLine;
    HI_U8            u8Coef1CurLine;
    HI_U8            u8Coef1NextLine;
    HI_U8            u8Coef2LastLine;
    HI_U8            u8Coef2CurLine;
    HI_U8            u8Coef2NextLine;
    HI_U8            u8Coef3LastLine;
    HI_U8            u8Coef3CurLine;
    HI_U8            u8Coef3NextLine;
    HI_U8            u8Threshold0;
    HI_U8            u8Threshold1;
    HI_U8            u8Threshold2;
    TDE2_DEFLICKER_MODE_E enDeflickerMode;
} TDE_DRV_FLICKER_CMD_S;


/* ���Ų������� */
typedef struct hiTDE_DRV_RESIZE_CMD_S
{
    HI_U32            u32OffsetX;
    HI_U32            u32OffsetY;
    HI_U32            u32StepH;
    HI_U32            u32StepV;
    HI_BOOL           bCoefSym;
    HI_BOOL           bVfRing;
    HI_BOOL           bHfRing;
    TDE_DRV_FILTER_MODE_E enFilterV;
    TDE_DRV_FILTER_MODE_E enFilterH;
    HI_BOOL           bFirstLineOut;
    HI_BOOL           bLastLineOut;   
} TDE_DRV_RESIZE_CMD_S;

/* �ü��������� */
typedef struct hiTDE_DRV_CLIP_CMD_S
{
    HI_U16  u16ClipStartX;
    HI_U16  u16ClipStartY;
    HI_U16  u16ClipEndX;
    HI_U16  u16ClipEndY;
    HI_BOOL bInsideClip;
} TDE_DRV_CLIP_CMD_S;

/* clut����ʹ��ģʽ */
typedef enum hiTDE_DRV_CLUT_MODE_E
{
    /* ��ɫ��չ */
    TDE_COLOR_EXP_CLUT_MODE = 0,

    /* ��ɫУ�� */
    TDE_COLOR_CORRCT_CLUT_MODE
} TDE_DRV_CLUT_MODE_E;

/* clut��������*/
typedef struct hiTDE_DRV_CLUT_CMD_S
{
    TDE_DRV_CLUT_MODE_E enClutMode;
    HI_U8*          pu8PhyClutAddr;
} TDE_DRV_CLUT_CMD_S;

/* ����ʽ����ģʽ */
typedef enum hiTDE_DRV_MB_OPT_MODE_E
{
    TDE_MB_Y_FILTER = 0, /*���������˲�*/
    TDE_MB_CbCr_FILTER = 2,  /*��ɫ�����˲�*/
    TDE_MB_UPSAMP_CONCA = 4, /*�����ϲ�������ɫ����*/
    TDE_MB_CONCA_FILTER = 6, /*������ɫ���������˲�*/
    TDE_MB_RASTER_OPT = 1    /*����դ������*/
} TDE_DRV_MB_OPT_MODE_E;

/* ����ʽ�������� */
typedef struct hiTDE_DRV_MB_CMD_S
{
    TDE_DRV_MB_OPT_MODE_E enMbMode;        /*����ʽ����ģʽ*/
} TDE_DRV_MB_CMD_S;

/* plane mask�������� */
typedef struct hiTDE_DRV_PLMASK_CMD_S
{
    HI_U32 u32Mask;
} TDE_DRV_PLMASK_CMD_S;

/* ��ɫ�ռ�ת������*/
typedef struct hiTDE_DRV_CONV_MODE_CMD_S
{
    /*����ɫ��ת��ʹ�õľ���:ͼ��:0/��Ƶ:1*/
    HI_U8 bInMetrixVid;

    /*����ɫ��ת����׼:IT-U601:0/ITU-709:1*/
    HI_U8 bInMetrix709;

    /*���ɫ��ת��ʹ�õľ���:ͼ��:0/��Ƶ:1*/
    HI_U8 bOutMetrixVid;

    /*���ɫ��ת����׼:IT-U601:0/ITU-709:1*/
    HI_U8 bOutMetrix709;

    /*�Ƿ�����������ɫ�ռ�ת��*/
    HI_U8 bInConv;

    /*�Ƿ����������ɫ�ռ�ת��*/
    HI_U8 bOutConv;
    HI_U8 bInSrc1Conv;

    /*����ɫ��ת������*/
    HI_U8 bInRGB2YC;
} TDE_DRV_CONV_MODE_CMD_S;

/*��ֱɨ�跽��*/
typedef enum hiTDE_DRV_VSCAN_E
{
    TDE_SCAN_UP_DOWN = 0,/*��������*/
    TDE_SCAN_DOWN_UP = 1 /*��������*/
} TDE_DRV_VSCAN_E;

/*ˮƽɨ�跽��*/
typedef enum hiTDE_DRV_HSCAN_E
{
    TDE_SCAN_LEFT_RIGHT = 0,/*��������*/
    TDE_SCAN_RIGHT_LEFT = 1 /*��������*/
} TDE_DRV_HSCAN_E;

/* ɨ�跽���� */
typedef struct hiTDE_SCANDIRECTION_S
{
    /* ��ֱɨ�跽�� */
    TDE_DRV_VSCAN_E enVScan;

    /* ˮƽɨ�跽�� */
    TDE_DRV_HSCAN_E enHScan;
} TDE_SCANDIRECTION_S;

/* ������Ҫ���õ�λͼ��Ϣ�ṹ,
   �û����õ�λͼ�����ø�Ӳ������Ϣ����һ����ͬ,
   ��,��Ϊ����ʽʱ�û����õ�һ��λͼ��Ϣ�ᱻ�ֽ�Ϊ
   Ӳ����Ҫ������λͼ��Ϣ:src1, src2.
   �����׵�ַ,pu8PhyCbCr�������㲻��ʹ��,���ֽ�ΪԴ1,Դ2�׵�ַ */
typedef struct hiTDE_DRV_SURFACE_S
{
    /* λͼ�׵�ַ */
    HI_U32 u32PhyAddr;

    /* ��ɫ��ʽ */
    TDE_DRV_COLOR_FMT_E enColorFmt;

    /* ��ʼλ��X���� */
    HI_U32 u32Xpos;

    /* ��ʼλ��Y���� */
    HI_U32 u32Ypos;

    /* λͼ�߶� */
    HI_U32 u32Height;

    /* λͼ��� */
    HI_U32 u32Width;

    /* λͼ��� */
    HI_U32 u32Pitch;

    /* λͼalpha���ֵΪ255����128 */
    HI_BOOL bAlphaMax255;

    /* ��ֱɨ�跽�� */
    TDE_DRV_VSCAN_E enVScan;

    /* ˮƽɨ�跽�� */
    TDE_DRV_HSCAN_E enHScan;
} TDE_DRV_SURFACE_S;

/* ���λͼ��Ϣ */
typedef struct hiTDE_DRV_MB_S
{
    TDE_DRV_COLOR_FMT_E enMbFmt;
    HI_U32              u32YPhyAddr;
    HI_U32              u32YWidth;
    HI_U32              u32YHeight;
    HI_U32              u32YStride;
    HI_U32              u32CbCrPhyAddr;
    HI_U32              u32CbCrStride;
} TDE_DRV_MB_S;

/* ALUģʽ */
typedef enum hiTDE_DRV_ALU_MODE_E
{
    TDE_SRC1_BYPASS = 0,
    TDE_ALU_ROP,
    TDE_ALU_BLEND,
    TDE_ALU_BLEND_SRC2,
    TDE_ALU_MASK_ROP1,
    TDE_ALU_MASK_BLEND,
    TDE_ALU_CONCA,
    TDE_SRC2_BYPASS,
    TDE_ALU_MASK_ROP2,
    TDE_ALU_NONE /*�Ĵ���û�д�����,������������*/
} TDE_DRV_ALU_MODE_E;


/*����TDE_UPDATE��˳�����Ľڵ�������Ϣ*/
typedef struct hiTDE_HWNode_S
{
    HI_U32 u32TDE_INS;
    HI_U32 u32TDE_S1_ADDR;
    HI_U32 u32TDE_S1_TYPE;
    HI_U32 u32TDE_S1_XY;
    HI_U32 u32TDE_S1_FILL;
    HI_U32 u32TDE_S2_ADDR;
    HI_U32 u32TDE_S2_TYPE;
    HI_U32 u32TDE_S2_XY;
    HI_U32 u32TDE_S2_SIZE;
    HI_U32 u32TDE_S2_FILL;
    HI_U32 u32TDE_TAR_ADDR;
    HI_U32 u32TDE_TAR_TYPE;
    HI_U32 u32TDE_TAR_XY;
    HI_U32 u32TDE_TS_SIZE;
    HI_U32 u32TDE_COLOR_CONV;
    HI_U32 u32TDE_CLUT_ADDR;
    HI_U32 u32TDE_2D_RSZ;
    HI_U32 u32TDE_HF_COEF_ADDR;
    HI_U32 u32TDE_VF_COEF_ADDR;
#ifdef TDE_VERSION_MPW
    HI_U32 u32TDE_RSZ_STEP;
#else
    HI_U32 u32TDE_RSZ_HSTEP;
#endif
    HI_U32 u32TDE_RSZ_Y_OFST;
    HI_U32 u32TDE_RSZ_X_OFST;
    HI_U32 u32TDE_DFE_COEF0;
    HI_U32 u32TDE_DFE_COEF1;
    HI_U32 u32TDE_DFE_COEF2;
    HI_U32 u32TDE_DFE_COEF3;
    HI_U32 u32TDE_ALU;
    HI_U32 u32TDE_CK_MIN;
    HI_U32 u32TDE_CK_MAX;
    HI_U32 u32TDE_CLIP_START;
    HI_U32 u32TDE_CLIP_STOP;
#if defined (TDE_VERSION_PILOT) || defined (TDE_VERSION_FPGA)
    HI_U32 u32TDE_Y1_ADDR;
    HI_U32 u32TDE_Y1_PITCH;
    HI_U32 u32TDE_Y2_ADDR;
    HI_U32 u32TDE_Y2_PITCH;
    HI_U32 u32TDE_RSZ_VSTEP;
    HI_U32 u32TDE_ARGB_ORDER;
    HI_U32 u32TDE_CK_MASK;
    HI_U32 u32TDE_COLORIZE;
    HI_U32 u32TDE_ALPHA_BLEND;
    HI_U32 u32TDE_ICSC_ADDR;
    HI_U32 u32TDE_OCSC_ADDR;	
#endif
    HI_U64 u64TDE_UPDATE; /* ���������¼��Щ�����и��� */
} TDE_HWNode_S;

/* �ӽڵ��е�����ģʽ */
typedef enum hiTDE_CHILD_SCALE_MODE_E
{
    TDE_CHILD_SCALE_NORM = 0,
    TDE_CHILD_SCALE_MBY,
    TDE_CHILD_SCALE_MBC,
    TDE_CHILD_SCALE_MB_CONCA_H,
    TDE_CHILD_SCALE_MB_CONCA_M,
    TDE_CHILD_SCALE_MB_CONCA_L,
    TDE_CHILD_SCALE_MB_CONCA_CUS
} TDE_CHILD_SCALE_MODE_E;

/* ����ʽ�ӽڵ�����/ɫλ�õ���ʱ��Ҫ����Ϣ */
typedef struct hiTDE_MBSTART_ADJ_INFO_S
{
    HI_U32 u32StartInX;     /*����ʽ������������ʼX,Y����*/
    HI_U32 u32StartInY;
    HI_U32 u32StartOutX;    /*����ʽ�����������ʼX, Y����*/
    HI_U32 u32StartOutY;
    TDE_DRV_COLOR_FMT_E enFmt; /*����ʽ��Ҫ���ݸ�ʽ�ָ�������ʼλ�û�ɫ����ʼλ��*/
    TDE_CHILD_SCALE_MODE_E enScaleMode;
} TDE_MBSTART_ADJ_INFO_S;

/* ˫Դ�ֿ�ʱ��Ҫ�ĵ�����Ϣ */
typedef struct hiTDE_DOUBLESRC_ADJ_INFO_S
{
    HI_BOOL bDoubleSource;   
    HI_S32 s32DiffX;    /*  s32DiffX = S1x - Tx         */
    HI_S32 s32DiffY;    /*  s32DiffY = S1y - Ty         */ 
}TDE_DOUBLESRC_ADJ_INFO_S;
/*
 * �����ӽڵ�ʱ��������Ϣ
 * u32Update :
 * _________________________________________
 * |    |    |    |    |    |    |    |    |
 * | ...| 0  | 0  | 1  | 1  | 1  | 1  |  1 |
 * |____|____|____|____|____|____|____|____|
 *                   |    |    |    |    |
 *                  \/   \/   \/   \/   \/
 *                u32Wo u32Xo HOfst u32Wi u32Xi
 *                u32Ho u32Yo VOfst u32Hi u32Yi
 */
typedef struct hiTDE_CHILD_INFO
{
    HI_U32 u32Xi;
    HI_U32 u32Yi;
    HI_U32 u32Wi;
    HI_U32 u32Hi;
    HI_U32 u32HOfst;
    HI_U32 u32VOfst;
    HI_U32 u32Xo;
    HI_U32 u32Yo;
    HI_U32 u32Wo;
    HI_U32 u32Ho;
    HI_U64 u64Update;
    TDE_MBSTART_ADJ_INFO_S stAdjInfo;
    TDE_DOUBLESRC_ADJ_INFO_S stDSAdjInfo;
    TDE_SLICE_TYPE_E enSliceType;
} TDE_CHILD_INFO;

typedef struct hiTDE_DRV_COLORFILL_S
{
    TDE_DRV_COLOR_FMT_E enDrvColorFmt;
    HI_U32              u32FillData;
} TDE_DRV_COLORFILL_S;

typedef enum hiTDE_DRV_INT_E
{
	TDE_DRV_INT_lIST_COMP_AQ = 0x10000,
	TDE_DRV_INT_lIST_COMP_SQ = 0x1,
	TDE_DRV_INT_NODE_COMP_AQ = 0x20000,
	TDE_DRV_INT_NODE_COMP_SQ = 0x2,
	TDE_DRV_INT_SUSPEND_LINE_AQ = 0x40000,
	TDE_DRV_INT_SUSPEND_LINE_SQ = 0x4,
 	TDE_DRV_INT_HEAD_UPDATE_SQ = 0x10,
 	TDE_DRV_INT_ERROR = 0x80000000,
}TDE_DRV_INT_E;

typedef TDE2_OUTALPHA_FROM_E TDE_DRV_OUTALPHA_FROM_E;

typedef enum hiTDE_DRV_SRC_E
{
    TDE_DRV_SRC_NONE = 0,
    TDE_DRV_SRC_S1 = 0x1,
    TDE_DRV_SRC_S2 = 0x2,
    TDE_DRV_SRC_T = 0x4,
}TDE_DRV_SRC_E;

/****************************************************************************/
/*                             TDE �Ĵ����궨��                             */
/****************************************************************************/
#define TDE_BASE_ADDR 0x1013
#define TDE_VER 0x0800
#define TDE_RST 0x0804
#define TDE_CTRL 0x0808
#define TDE_SQ_ADDR 0x080C
#define TDE_AQ_ADDR 0x0810
#define TDE_STA 0x0814
#define TDE_INT 0x0818
#define TDE_SQ_CTRL 0x081C
#define TDE_SQ_NADDR 0x0820
#define TDE_SQ_UPDATE 0x0824
#define TDE_SQ_OFFSET 0x0828
#define TDE_AQ_CTRL 0x082C
#define TDE_AQ_NADDR 0x0830
#define TDE_AQ_UPDATE 0x0834
#define TDE_NADDR 0x0838
#define TDE_UPDATE 0x083C
#define TDE_SQ_RPT_ADDR 0x0840
#define TDE_BUS_LIMITER 0x0844
#define TDE_BUS_MONITOR 0x0848

#define TDE_SQ_UPDATE2 0x0858
#define TDE_AQ_UPDATE2 0x085c

#define TDE_AXI_ID                  0x086c
#define TDE_INS 0x0880
#define TDE_S1_ADDR 0x0884
#define TDE_S1_TYPE 0x0888
#define TDE_S1_XY 0x088C
#define TDE_S1_FILL 0x0890
#define TDE_S2_ADDR 0x0894
#define TDE_S2_TYPE 0x0898
#define TDE_S2_XY 0x089C
#define TDE_S2_SIZE 0x08A0
#define TDE_S2_FILL 0x08A4
#define TDE_TAR_ADDR 0x08A8
#define TDE_TAR_TYPE 0x08AC
#define TDE_TAR_XY 0x08B0
#define TDE_TS_SIZE 0x08B4
#define TDE_COLOR_CONV 0x08B8
#define TDE_CLUT_ADDR 0x08BC
#define TDE_2D_RSZ 0x08C0
#define TDE_HCOEF_ADDR 0x08C4
#define TDE_VCOEF_ADDR 0x08C8
#define TDE_RSZ_STEP 0x08CC
#define TDE_RSZ_Y_OFST 0x08D0
#define TDE_RSZ_X_OFST 0x08D4
#define TDE_DFE_COEF0 0x08D8
#define TDE_DFE_COEF1 0x08DC
#define TDE_DFE_COEF2 0x08E0
#define TDE_DFE_COEF3 0x08E4
#define TDE_ALU 0x08E8
#define TDE_CK_MIN 0x08EC
#define TDE_CK_MAX 0x08F0
#define TDE_CLIP_START 0x08F4
#define TDE_CLIP_STOP 0x08F8
#define TDE_Y1_ADDR 0x08FC
#define TDE_Y1_PITCH 0x0900
#define TDE_Y2_ADDR 0x0904
#define TDE_Y2_PITCH 0x0908
#define TDE_RSZ_VSTEP 0x090C
#define TDE_ARGB_ORDER 0x0910
#define TDE_CK_MASK 0x0914
#define TDE_COLORIZE 0x0918
#define TDE_ALPHA_BLEND 0x091C
#define TDE_ICSC_ADDR 0x0920
#define TDE_OCSC_ADDR 0x0924

#define TDE_SQ_MASK_DISABLE_ALL 0  /*00000���ж�����*/
#define TDE_SQ_CUR_LINE_MASK_EN 1  /*00001��ʹ��ͬ������ǰ�ڵ㵱ǰ������ж� */
#define TDE_SQ_RD_NODE_MASK_EN 2   /*00010��ʹ��ͬ�������ȡ������µ�node������Ϣ����û�п�ʼִ��ͼ�����ʱ���ж�*/
#define TDE_SQ_COMP_NODE_MASK_EN 4 /*00100��ʹ��ͬ������ǰ�ڵ�����ж� */
#define TDE_SQ_COMP_LIST_MASK_EN 8 /*01000��ʹ��ͬ����������ж�*/
#define TDE_SQ_UPDATE_MASK_EN 16   /*10000��ʹ��ͬ������ͷ��������ж�*/

#define TDE_AQ_MASK_DISABLE_ALL 0  /*0000���ж�����*/
#define TDE_AQ_SUSP_MASK_EN 1      /*0001��ʹ���첽����ǰ�ڵ�ִ�е�ĳһ�й����ж�*/
#define TDE_AQ_RD_NODE_MASK_EN 2   /*0010��ʹ���첽�����ȡ������µ�node������Ϣ����û�п�ʼִ��ͼ�����ʱ���ж�*/
#define TDE_AQ_COMP_NODE_MASK_EN 4 /*0100��ʹ���첽����ǰ�ڵ�����ж�*/
#define TDE_AQ_COMP_LIST_MASK_EN 8 /*1000��ʹ���첽��������ж�*/

/*�ڵ��Ӧ��handleֵ*/
/*������Ҫ��ѯ��ǰ����ִ�е�����ڵ� ���Ĵ�����ֻ������ִ�еĽڵ�������ַ 
���������buffer��ͷ�����4���ֽڣ���������ڵ�ָ��*/
#define TDE_NODE_HEAD_BYTE 16

/*��һ�ڵ�ĵ�ַ��������Ϣ��ռ���ֽ���*/
#ifdef TDE_VERSION_MPW
#define TDE_NODE_TAIL_BYTE 8
#else
#define TDE_NODE_TAIL_BYTE 12
#endif

/****************************************************************************/
/*                             TDE hal ctl functions define                 */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeHalInit
* Description:   ��Ҫ����ӳ��TDE����ַ
* Input:         u32BaseAddr:�Ĵ�������ַ
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32  TdeHalInit(HI_U32 u32BaseAddr);

/*****************************************************************************
* Function:      TdeHalOpen
* Description:   ��Ҫ���ڳ�ʼ������ļĴ���
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalOpen(HI_VOID);

/*****************************************************************************
* Function:      TdeHalRelease
* Description:   ��Ҫ�����ͷ�ӳ���TDE����ַ
* Input:         ��
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalRelease(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlIsIdle
* Description:   ��ѯTDE�Ƿ���IDLE״̬
* Input:         ��
* Output:        ��
* Return:        True: Idle/False: Busy
* Others:        ��
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdle(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlIsIdleSafely
* Description:   ѭ����β�ѯ, ȷ��TDE�Ƿ���IDLE״̬
* Input:         ��
* Output:        ��
* Return:        True: Idle/False: Busy
* Others:        ��
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdleSafely(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlCurNode
* Description:   ��ȡTDE��������ʱִ�е��Ľڵ�������ַ
* Input:         enListType: ����Sq/Aq������
* Output:        ��
* Return:        ����ִ�е�ǰ�ڵ�������ַ
* Others:        ��
*****************************************************************************/

//HI_U32 TdeHalCtlCurNode(TDE_LIST_TYPE_E enListType);

/*****************************************************************************
* Function:      TdeHalCtlIntMask
* Description:   ����Sq/Aq���ж�����
* Input:         enListType: ����Sq/Aq������
*                u32Mask: �ж�λ����
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/

//HI_VOID TdeHalCtlIntMask(TDE_LIST_TYPE_E enListType, HI_U32 u32Mask);

/*****************************************************************************
* Function:      TdeHalCtlIntMask
* Description:   ��ȡSq/Aq���ж�״̬
* Input:         enListType: ����Sq/Aq������
* Output:        ��
* Return:        Sq/Aq�ж�״̬
* Others:        ��
*****************************************************************************/
HI_U32  TdeHalCtlIntStats(HI_VOID);

/*****************************************************************************
* Function:      TdeHalResetStatus
* Description:   ��λTDE HAL����״̬,�����������
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalResetStatus(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlReset
* Description:   ��λ�����ж�״̬
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalCtlReset(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlIntClear
* Description:   ����Ӧ���ж�״̬
* Input:         enListType: ����Sq/Aq������
*                u32Stats: ����Ӧ���ж�״̬
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalCtlIntClear(TDE_LIST_TYPE_E enListType, HI_U32 u32Stats);

/*****************************************************************************
* Function:      TdeHalCtlGetRunningSwNode
* Description:   ��ȡ��ǰ����ִ�е�����ڵ�,���������δ�����򷵻�NULL
* Input:         enListType: ��ǰִ�е���������
* Output:        ��
* Return:        ��ǰ����ִ�е�����ڵ�ָ��
* Others:        ��
*****************************************************************************/
HI_BOOL TdeHalCtlGetRunningSwNode(TDE_LIST_TYPE_E enListType, HI_S32 *ps32Handle, HI_VOID **ppstSwNode);

/*****************************************************************************
*Description: ��ѯTDE�Ĺ���������ͬ�������첽
*****************************************************************************/
HI_BOOL TdeHalIsSqWork(HI_VOID);

/****************************************************************************/
/*                             TDE hal node functions define                */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeHalNodeInitNd
* Description:   ��ʼ����������һ��TDE�����ڵ�����Ľṹ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeInitNd(TDE_HWNode_S* pHWNode, HI_BOOL bChild);

HI_VOID TdeHalNodeInitChildNd(TDE_HWNode_S* pHWNode, HI_U32 u32TDE_CLIP_START, HI_U32 u32TDE_CLIP_STOP);

HI_VOID TdeHalNodeSetCsc(TDE_HWNode_S* pHWNode, TDE2_CSC_OPT_S *pstCscOpt);

/*****************************************************************************
* Function:      TdeHalNodeGetNdSize
* Description:   ��ȡ��ǰ���������µĽڵ�������ٸ���(4�ֽ�)
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
* Output:        ��
* Return:        ���������ֽ���
* Others:        ��
*****************************************************************************/
HI_U32  TdeHalNodeGetNdSize(TDE_HWNode_S* pHWNode);

/*****************************************************************************
* Function:      TdeHalNodeMakeNd
* Description:   �ɵ�ǰ���������µĽڵ�pHWNode,�����ɿ���ֱ�����õĽڵ㵽pBuf��
* Input:         pBuf: �����ڵ�󻺴�ڵ��buffer
*                pHWNode: ������ڻ���Ľڵ�ṹָ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_S32  TdeHalNodeMakeNd(HI_VOID* pBuf, TDE_HWNode_S* pHWNode);

/*****************************************************************************
* Function:      TdeHalNodeEnableCompleteInt
* Description:   ���ýڵ��������ж�
* Input:         pBuf: ��Ҫ�����Ľڵ�Buffer�ڴ�
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeEnableCompleteInt(HI_VOID* pBuf, TDE_LIST_TYPE_E enType);

/*****************************************************************************
* Function:      TdeHalNodeComplteAqList
* Description:   ֪ͨӲ��Aq�����Ѿ����
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeComplteAqList(HI_VOID);

HI_VOID TdeHalNodeComplteNd(TDE_LIST_TYPE_E enListType);

/*****************************************************************************
* Function:      TdeHalNodeSetSrc1
* Description:   ����Դ1λͼ��Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvSurface: �������õ�λͼ��Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc1(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface);

/*****************************************************************************
* Function:      TdeHalNodeSetSrc2
* Description:   ����Դ2λͼ��Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvSurface: �������õ�λͼ��Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc2(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface);

/*****************************************************************************
* Function:      TdeHalNodeSetSrcMbY
* Description:   ���ú���ʽԴλͼ������Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvMbY: �������õ�����λͼ��Ϣ
*                enMbOpt: ���ģʽѡ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetSrcMbY(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbY, TDE_DRV_MB_OPT_MODE_E enMbOpt);

/*****************************************************************************
* Function:      TdeHalNodeSetSrcMbCbCr
* Description:   ���ú���ʽԴλͼɫ����Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvMbCbCr: ɫ����Ϣ
*                enMbOpt: ���ģʽѡ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetSrcMbCbCr(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbCbCr, TDE_DRV_MB_OPT_MODE_E enMbOpt);

/*****************************************************************************
* Function:      TdeHalNodeSetTgt
* Description:   ����Ŀ��λͼ��Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvSurface: �������õ�λͼ��Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetTgt(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, TDE_DRV_OUTALPHA_FROM_E enAlphaFrom);

/*****************************************************************************
* Function:      TdeHalNodeSetBaseOperate
* Description:   ���û�����������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                enMode: ��������ģʽ
*                enAlu: ALUģʽ
*                u32FillData: �����������ģʽ����������,���ȡ��ֵ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetBaseOperate(TDE_HWNode_S* pHWNode, TDE_DRV_BASEOPT_MODE_E enMode,
                                 TDE_DRV_ALU_MODE_E enAlu, TDE_DRV_COLORFILL_S *pstColorFill);

/*****************************************************************************
* Function:      TdeHalNodeSetGlobalAlpha
* Description:   ����Alpha��ϲ���
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                u8Alpha: Alpha�������ֵ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetGlobalAlpha(TDE_HWNode_S* pHWNode, HI_U8 u8Alpha);

/*****************************************************************************
* Function:      TdeHalNodeSetExpAlpha
* Description:   ����RGB5551��Alpha��չʱ,��չΪalpha0, alpha1������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                u8Alpha: Alpha�������ֵ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetExpAlpha(TDE_HWNode_S* pHWNode, TDE_DRV_SRC_E enSrc, HI_U8 u8Alpha0, HI_U8 u8Alpha1);
/*****************************************************************************
* Function:      TdeHalNodeSetAlphaBorder
* Description:   �����Ƿ�ʹ��Alplha�߽紦��
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                bEnable: �Ƿ�ʹ��Alplha�߽�
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetAlphaBorder(TDE_HWNode_S* pHWNode, HI_BOOL bVEnable, HI_BOOL bHEnable);

/*****************************************************************************
* Function:      TdeHalNodeSetRop
* Description:   ����ROP�������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                enRopCode: ROP������
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetRop(TDE_HWNode_S* pHWNode, TDE2_ROP_CODE_E enRgbRop, TDE2_ROP_CODE_E enAlphaRop);

/*****************************************************************************
* Function:      TdeHalNodeSetColorExp
* Description:   ������ɫ��չ����ɫУ������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pClutCmd: Clut�����������
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetClutOpt(TDE_HWNode_S* pHWNode, TDE_DRV_CLUT_CMD_S* pClutCmd, HI_BOOL bReload);

/*****************************************************************************
* Function:      TdeHalNodeSetColorKey
* Description:   ���ݵ�ǰ����ɫ��ʽ����color key ��������Ĳ���
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                enFmt: ��ɫ��ʽ
*                pColorKey: color key ����ֵָ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetColorKey(TDE_HWNode_S* pHWNode, TDE_COLORFMT_CATEGORY_E enFmtCat, 
                              TDE_DRV_COLORKEY_CMD_S* pColorKey);

/*****************************************************************************
* Function:      TdeHalNodeSetClipping
* Description:   ���þ��βü���������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pClip: �ü����η�Χ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetClipping(TDE_HWNode_S* pHWNode, TDE_DRV_CLIP_CMD_S* pClip);

/*****************************************************************************
* Function:      TdeHalNodeSetFlicker
* Description:   ���ÿ���˸�˲��������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pFlicker: ����˸ϵ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetFlicker(TDE_HWNode_S* pHWNode, TDE_DRV_FLICKER_CMD_S* pFlicker);

/*****************************************************************************
* Function:      TdeHalNodeSetResize
* Description:   ���������˲��������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pResize: ����ϵ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetResize(TDE_HWNode_S* pHWNode, TDE_DRV_RESIZE_CMD_S* pResize,TDE_NODE_SUBM_TYPE_E enNodeType);

/*****************************************************************************
* Function:      TdeHalNodeSetResize
* Description:   ������ɫ�ռ�ת���������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pConv: ��ɫ�ռ�ת������
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetColorConvert(TDE_HWNode_S* pHWNode, TDE_DRV_CONV_MODE_CMD_S* pConv);

/*****************************************************************************
* Function:      TdeHalNodeAddChild
* Description:   ���˲�����ʱ����ӽڵ�
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pChildInfo: ����ӽڵ��������Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeAddChild(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo);

/*****************************************************************************
* Function:      TdeHalNodeSetMbMode
* Description:   ���ú�鴦���������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pMbCmd: ��鴦�����
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetMbMode(TDE_HWNode_S* pHWNode, TDE_DRV_MB_CMD_S* pMbCmd);

/*****************************************************************************
* Function:      TdeHalNodeSuspend
* Description:   �����������ʱ,���浱ǰִ�е��Ľڵ�����Ա�֤�ܹ��ָ�ִ��
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSuspend(HI_VOID);


/*��ȡ�����������ڵ��ַ*/
HI_VOID TdeHalGetSuspendNode(HI_VOID **ppstSuspendNode);

/*****************************************************************************
* Function:      TdeHalSetDeflicerLevel
* Description:   ���ÿ���˸����
* Input:         eDeflickerLevel:����˸����
* Output:        ��
* Return:        �ɹ� / ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalSetDeflicerLevel(TDE_DEFLICKER_LEVEL_E eDeflickerLevel);

/*****************************************************************************
* Function:      TdeHalGetDeflicerLevel
* Description:   ���ÿ���˸����
* Input:        
* Output:        pDeflicerLevel:����˸����
* Return:        �ɹ� / ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalGetDeflicerLevel(TDE_DEFLICKER_LEVEL_E *pDeflicerLevel);

/*****************************************************************************
* Function:      TdeHalSetAlphaThreshold
* Description:   ����alpha��ֵ
* Input:         u8ThresholdValue:alpha��ֵ
* Output:        
* Return:        �ɹ� / ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalSetAlphaThreshold(HI_U8 u8ThresholdValue);

/*****************************************************************************
* Function:      TdeHalGetAlphaThreshold
* Description:   ��ȡalpha��ֵ
* Input:         
* Output:        pu8ThresholdValue:alpha��ֵ
* Return:        �ɹ� / ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalGetAlphaThreshold(HI_U8 * pu8ThresholdValue);

/*****************************************************************************
* Function:      TdeHalGetAlphaThresholdState
* Description:   ����alpha��ֵ�о�����״̬
* Input:         bEnAlphaThreshold:alpha����״̬
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);

/*****************************************************************************
* Function:      TdeHalGetAlphaThresholdState
* Description:   ��ȡalpha��ֵ�о�����״̬
* Input:         ��
* Output:        pbEnAlphaThreshold:alpha�о���ֵ
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalGetAlphaThresholdState(HI_BOOL *pbEnAlphaThreshold);

/*****************************************************************************
* Function:      TdeHalNodeExecute
* Description:   ����TDE����
* Input:         enListType: ��������
*                u32NodePhyAddr: �����׽ڵ��ַ
*                u32Update:�����׽ڵ���±�ʶ
*                bAqUseBuff: �Ƿ�ʹ����ʱbuffer
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalNodeExecute(TDE_LIST_TYPE_E enListType, HI_U32 u32NodePhyAddr, HI_U64 u64Update, HI_BOOL bAqUseBuff);

/*****************************************************************************
* Function:      TdeHalRestoreAloneNode
* Description:   �ָ��ڵ�������ýڵ�Ϊ�����ڵ�
* Input:         ��
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalRestoreAloneNode(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCurNode
* Description:   ��ȡ�Ĵ����е�ǰִ�еĽڵ�
* Input:         enListType: ��������
* Output:        �ڵ������ַ
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_U32 TdeHalCurNode(TDE_LIST_TYPE_E enListType);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_HAL_H_ */
