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

/* TDE基本操作模式 */
typedef enum hiTDE_DRV_BASEOPT_MODE_E
{
    /*快速填充*/
    TDE_QUIKE_FILL,

    /*快速拷贝*/
    TDE_QUIKE_COPY,

    /*普通单源填充*/
    TDE_NORM_FILL_1OPT,

    /*普通单源操作搬移*/
    TDE_NORM_BLIT_1OPT,

    /*填充色与位图运算操作搬移*/
    TDE_NORM_FILL_2OPT,

    /*普通双源操作搬移 */
    TDE_NORM_BLIT_2OPT,

    /*宏块操作*/
    TDE_MB_C_OPT,    /*宏块色度缩放*/
    TDE_MB_Y_OPT,    /*宏块亮度缩放*/
    TDE_MB_2OPT,      /*宏块合并操作*/

    /*单源模式填充操作*/
    TDE_SINGLE_SRC_PATTERN_FILL_OPT,

    /*双源模式填充操作*/
    TDE_DOUBLE_SRC_PATTERN_FILL_OPT
} TDE_DRV_BASEOPT_MODE_E;

/* 中断状态类型定义 */
typedef enum hiTDE_DRV_INT_STATS_E
{
    TDE_DRV_LINK_COMPLD_STATS = 0x1,
    TDE_DRV_NODE_COMPLD_STATS = 0x2,
    TDE_DRV_LINE_SUSP_STATS = 0x4,
    TDE_DRV_RDY_START_STATS = 0x8,
    TDE_DRV_SQ_UPDATE_STATS = 0x10,
    TDE_DRV_INT_ALL_STATS = 0x800F001F
} TDE_DRV_INT_STATS_E;

/* 硬件需要的ColorKey模式 */
typedef enum hiTDE_DRV_COLORKEY_MODE_E
{
    TDE_DRV_COLORKEY_BACKGROUND = 0,          /* 对背景位图进行color key*/
    TDE_DRV_COLORKEY_FOREGROUND_BEFORE_CLUT = 2,  /* 对前景位图进行color key,在Clut前*/
    TDE_DRV_COLORKEY_FOREGROUND_AFTER_CLUT = 3    /* 对前景位图进行color key,在Clut后*/
} TDE_DRV_COLORKEY_MODE_E;

/* color key 设置参数 */
typedef struct hiTDE_DRV_COLORKEY_CMD_S
{
    TDE_DRV_COLORKEY_MODE_E enColorKeyMode;        /*color key方式*/
    TDE2_COLORKEY_U        unColorKeyValue;       /*color key设置值*/
} TDE_DRV_COLORKEY_CMD_S;

/* 抗闪烁滤波模式 */
typedef enum hiTDE_DRV_FLICKER_MODE
{
    TDE_DRV_FIXED_COEF0 = 0,   /*使用固定系数0进行抗闪烁*/
    TDE_DRV_AUTO_FILTER,       /*使用自适应抗闪烁滤波器*/
    TDE_DRV_TEST_FILTER        /*使用测试模式抗闪烁滤波器*/
} TDE_DRV_FLICKER_MODE;

/* 分块类型,配置数值参考寄存器手册 */
typedef enum hiTDE_SLICE_TYPE_E
{
    TDE_NO_BLOCK_SLICE_TYPE = 0,         /* 不需要分块 */
    TDE_FIRST_BLOCK_SLICE_TYPE = 0x3,    /* 第一块 */
    TDE_LAST_BLOCK_SLICE_TYPE = 0x5,     /* 最后一块 */
    TDE_MID_BLOCK_SLICE_TYPE = 0x1       /* 中间块 */
} TDE_SLICE_TYPE_E;
/* 垂直/水平滤波模式:只对缩放有效 */
typedef enum hiTDE_DRV_FILTER_MODE_E
{
    TDE_DRV_FILTER_NONE = 0,    /*不进行滤波*/
    TDE_DRV_FILTER_COLOR,       /*只对颜色值滤波*/
    TDE_DRV_FILTER_ALPHA,       /*只对Alpha值滤波*/
    TDE_DRV_FILTER_ALL          /*对颜色和Alpha值滤波*/
} TDE_DRV_FILTER_MODE_E;

/* 抗闪烁操作设置 */
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


/* 缩放操作设置 */
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

/* 裁减操作设置 */
typedef struct hiTDE_DRV_CLIP_CMD_S
{
    HI_U16  u16ClipStartX;
    HI_U16  u16ClipStartY;
    HI_U16  u16ClipEndX;
    HI_U16  u16ClipEndY;
    HI_BOOL bInsideClip;
} TDE_DRV_CLIP_CMD_S;

/* clut操作使用模式 */
typedef enum hiTDE_DRV_CLUT_MODE_E
{
    /* 颜色扩展 */
    TDE_COLOR_EXP_CLUT_MODE = 0,

    /* 颜色校正 */
    TDE_COLOR_CORRCT_CLUT_MODE
} TDE_DRV_CLUT_MODE_E;

/* clut操作设置*/
typedef struct hiTDE_DRV_CLUT_CMD_S
{
    TDE_DRV_CLUT_MODE_E enClutMode;
    HI_U8*          pu8PhyClutAddr;
} TDE_DRV_CLUT_CMD_S;

/* 宏块格式操作模式 */
typedef enum hiTDE_DRV_MB_OPT_MODE_E
{
    TDE_MB_Y_FILTER = 0, /*对亮度作滤波*/
    TDE_MB_CbCr_FILTER = 2,  /*对色度作滤波*/
    TDE_MB_UPSAMP_CONCA = 4, /*先作上采样再亮色连接*/
    TDE_MB_CONCA_FILTER = 6, /*先作亮色连接再作滤波*/
    TDE_MB_RASTER_OPT = 1    /*宏块光栅作运算*/
} TDE_DRV_MB_OPT_MODE_E;

/* 宏块格式操作设置 */
typedef struct hiTDE_DRV_MB_CMD_S
{
    TDE_DRV_MB_OPT_MODE_E enMbMode;        /*宏块格式操作模式*/
} TDE_DRV_MB_CMD_S;

/* plane mask操作设置 */
typedef struct hiTDE_DRV_PLMASK_CMD_S
{
    HI_U32 u32Mask;
} TDE_DRV_PLMASK_CMD_S;

/* 颜色空间转换设置*/
typedef struct hiTDE_DRV_CONV_MODE_CMD_S
{
    /*输入色彩转换使用的矩阵:图形:0/视频:1*/
    HI_U8 bInMetrixVid;

    /*输入色彩转换标准:IT-U601:0/ITU-709:1*/
    HI_U8 bInMetrix709;

    /*输出色彩转换使用的矩阵:图形:0/视频:1*/
    HI_U8 bOutMetrixVid;

    /*输出色彩转换标准:IT-U601:0/ITU-709:1*/
    HI_U8 bOutMetrix709;

    /*是否启用输入颜色空间转换*/
    HI_U8 bInConv;

    /*是否启用输出颜色空间转换*/
    HI_U8 bOutConv;
    HI_U8 bInSrc1Conv;

    /*输入色彩转换方向*/
    HI_U8 bInRGB2YC;
} TDE_DRV_CONV_MODE_CMD_S;

/*垂直扫描方向*/
typedef enum hiTDE_DRV_VSCAN_E
{
    TDE_SCAN_UP_DOWN = 0,/*由上向下*/
    TDE_SCAN_DOWN_UP = 1 /*由下向上*/
} TDE_DRV_VSCAN_E;

/*水平扫描方向*/
typedef enum hiTDE_DRV_HSCAN_E
{
    TDE_SCAN_LEFT_RIGHT = 0,/*由左向右*/
    TDE_SCAN_RIGHT_LEFT = 1 /*由右向左*/
} TDE_DRV_HSCAN_E;

/* 扫描方向定义 */
typedef struct hiTDE_SCANDIRECTION_S
{
    /* 垂直扫描方向 */
    TDE_DRV_VSCAN_E enVScan;

    /* 水平扫描方向 */
    TDE_DRV_HSCAN_E enHScan;
} TDE_SCANDIRECTION_S;

/* 驱动需要设置的位图信息结构,
   用户设置的位图和设置给硬件的信息并不一定相同,
   如,当为宏块格式时用户设置的一个位图信息会被分解为
   硬件需要的两个位图信息:src1, src2.
   亮度首地址,pu8PhyCbCr在驱动层不再使用,被分解为源1,源2首地址 */
typedef struct hiTDE_DRV_SURFACE_S
{
    /* 位图首地址 */
    HI_U32 u32PhyAddr;

    /* 颜色格式 */
    TDE_DRV_COLOR_FMT_E enColorFmt;

    /* 起始位置X坐标 */
    HI_U32 u32Xpos;

    /* 起始位置Y坐标 */
    HI_U32 u32Ypos;

    /* 位图高度 */
    HI_U32 u32Height;

    /* 位图宽度 */
    HI_U32 u32Width;

    /* 位图跨度 */
    HI_U32 u32Pitch;

    /* 位图alpha最大值为255还是128 */
    HI_BOOL bAlphaMax255;

    /* 垂直扫描方向 */
    TDE_DRV_VSCAN_E enVScan;

    /* 水平扫描方向 */
    TDE_DRV_HSCAN_E enHScan;
} TDE_DRV_SURFACE_S;

/* 宏块位图信息 */
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

/* ALU模式 */
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
    TDE_ALU_NONE /*寄存器没有此设置,软件用作最后标记*/
} TDE_DRV_ALU_MODE_E;


/*按照TDE_UPDATE的顺序建立的节点配置信息*/
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
    HI_U64 u64TDE_UPDATE; /* 最后用来记录哪些设置有更新 */
} TDE_HWNode_S;

/* 子节点中的缩放模式 */
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

/* 宏块格式子节点中亮/色位置调整时需要的信息 */
typedef struct hiTDE_MBSTART_ADJ_INFO_S
{
    HI_U32 u32StartInX;     /*宏块格式调整后输入起始X,Y坐标*/
    HI_U32 u32StartInY;
    HI_U32 u32StartOutX;    /*宏块格式调整后输出起始X, Y坐标*/
    HI_U32 u32StartOutY;
    TDE_DRV_COLOR_FMT_E enFmt; /*宏块格式需要根据格式恢复亮度起始位置或色度起始位置*/
    TDE_CHILD_SCALE_MODE_E enScaleMode;
} TDE_MBSTART_ADJ_INFO_S;

/* 双源分块时需要的调整信息 */
typedef struct hiTDE_DOUBLESRC_ADJ_INFO_S
{
    HI_BOOL bDoubleSource;   
    HI_S32 s32DiffX;    /*  s32DiffX = S1x - Tx         */
    HI_S32 s32DiffY;    /*  s32DiffY = S1y - Ty         */ 
}TDE_DOUBLESRC_ADJ_INFO_S;
/*
 * 设置子节点时的配置信息
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
/*                             TDE 寄存器宏定义                             */
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

#define TDE_SQ_MASK_DISABLE_ALL 0  /*00000：中断屏蔽*/
#define TDE_SQ_CUR_LINE_MASK_EN 1  /*00001：使能同步链表当前节点当前行完成中断 */
#define TDE_SQ_RD_NODE_MASK_EN 2   /*00010：使能同步链表读取完成最新的node命令信息，还没有开始执行图象操作时的中断*/
#define TDE_SQ_COMP_NODE_MASK_EN 4 /*00100：使能同步链表当前节点完成中断 */
#define TDE_SQ_COMP_LIST_MASK_EN 8 /*01000：使能同步链表完成中断*/
#define TDE_SQ_UPDATE_MASK_EN 16   /*10000：使能同步链表头更新完成中断*/

#define TDE_AQ_MASK_DISABLE_ALL 0  /*0000：中断屏蔽*/
#define TDE_AQ_SUSP_MASK_EN 1      /*0001：使能异步链表当前节点执行到某一行挂起中断*/
#define TDE_AQ_RD_NODE_MASK_EN 2   /*0010：使能异步链表读取完成最新的node命令信息，还没有开始执行图象操作时的中断*/
#define TDE_AQ_COMP_NODE_MASK_EN 4 /*0100：使能异步链表当前节点完成中断*/
#define TDE_AQ_COMP_LIST_MASK_EN 8 /*1000：使能异步链表完成中断*/

/*节点对应的handle值*/
/*由于需要查询当前正在执行的软件节点 而寄存器中只有正在执行的节点的物理地址 
因此在物理buffer的头部添加4个字节，保存软件节点指针*/
#define TDE_NODE_HEAD_BYTE 16

/*下一节点的地址、更新信息，占用字节数*/
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
* Description:   主要用于映射TDE基地址
* Input:         u32BaseAddr:寄存器基地址
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32  TdeHalInit(HI_U32 u32BaseAddr);

/*****************************************************************************
* Function:      TdeHalOpen
* Description:   主要用于初始化必须的寄存器
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32 TdeHalOpen(HI_VOID);

/*****************************************************************************
* Function:      TdeHalRelease
* Description:   主要用于释放映射的TDE基地址
* Input:         无
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_VOID TdeHalRelease(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlIsIdle
* Description:   查询TDE是否处于IDLE状态
* Input:         无
* Output:        无
* Return:        True: Idle/False: Busy
* Others:        无
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdle(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlIsIdleSafely
* Description:   循环多次查询, 确保TDE是否处于IDLE状态
* Input:         无
* Output:        无
* Return:        True: Idle/False: Busy
* Others:        无
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdleSafely(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlCurNode
* Description:   获取TDE操作挂起时执行到的节点的物理地址
* Input:         enListType: 设置Sq/Aq的类型
* Output:        无
* Return:        链表执行当前节点的物理地址
* Others:        无
*****************************************************************************/

//HI_U32 TdeHalCtlCurNode(TDE_LIST_TYPE_E enListType);

/*****************************************************************************
* Function:      TdeHalCtlIntMask
* Description:   设置Sq/Aq的中断掩码
* Input:         enListType: 设置Sq/Aq的类型
*                u32Mask: 中断位掩码
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

//HI_VOID TdeHalCtlIntMask(TDE_LIST_TYPE_E enListType, HI_U32 u32Mask);

/*****************************************************************************
* Function:      TdeHalCtlIntMask
* Description:   获取Sq/Aq的中断状态
* Input:         enListType: 设置Sq/Aq的类型
* Output:        无
* Return:        Sq/Aq中断状态
* Others:        无
*****************************************************************************/
HI_U32  TdeHalCtlIntStats(HI_VOID);

/*****************************************************************************
* Function:      TdeHalResetStatus
* Description:   复位TDE HAL所有状态,清除所有链表
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalResetStatus(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlReset
* Description:   软复位，请中断状态
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalCtlReset(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCtlIntClear
* Description:   清相应的中断状态
* Input:         enListType: 设置Sq/Aq的类型
*                u32Stats: 清相应的中断状态
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalCtlIntClear(TDE_LIST_TYPE_E enListType, HI_U32 u32Stats);

/*****************************************************************************
* Function:      TdeHalCtlGetRunningSwNode
* Description:   获取当前正在执行的软件节点,如果此链表未运行则返回NULL
* Input:         enListType: 当前执行的链表类型
* Output:        无
* Return:        当前正在执行的软件节点指针
* Others:        无
*****************************************************************************/
HI_BOOL TdeHalCtlGetRunningSwNode(TDE_LIST_TYPE_E enListType, HI_S32 *ps32Handle, HI_VOID **ppstSwNode);

/*****************************************************************************
*Description: 查询TDE的工作队列是同步还是异步
*****************************************************************************/
HI_BOOL TdeHalIsSqWork(HI_VOID);

/****************************************************************************/
/*                             TDE hal node functions define                */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeHalNodeInitNd
* Description:   初始化软件缓存的一个TDE操作节点所需的结构
* Input:         pHWNode: 软件用于缓存的节点结构指针
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeInitNd(TDE_HWNode_S* pHWNode, HI_BOOL bChild);

HI_VOID TdeHalNodeInitChildNd(TDE_HWNode_S* pHWNode, HI_U32 u32TDE_CLIP_START, HI_U32 u32TDE_CLIP_STOP);

HI_VOID TdeHalNodeSetCsc(TDE_HWNode_S* pHWNode, TDE2_CSC_OPT_S *pstCscOpt);

/*****************************************************************************
* Function:      TdeHalNodeGetNdSize
* Description:   获取当前功能配置下的节点所需多少个字(4字节)
* Input:         pHWNode: 软件用于缓存的节点结构指针
* Output:        无
* Return:        返回所需字节数
* Others:        无
*****************************************************************************/
HI_U32  TdeHalNodeGetNdSize(TDE_HWNode_S* pHWNode);

/*****************************************************************************
* Function:      TdeHalNodeMakeNd
* Description:   由当前功能配置下的节点pHWNode,制作成可以直接配置的节点到pBuf中
* Input:         pBuf: 制作节点后缓存节点的buffer
*                pHWNode: 软件用于缓存的节点结构指针
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32  TdeHalNodeMakeNd(HI_VOID* pBuf, TDE_HWNode_S* pHWNode);

/*****************************************************************************
* Function:      TdeHalNodeEnableCompleteInt
* Description:   启用节点操作完成中断
* Input:         pBuf: 需要操作的节点Buffer内存
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeEnableCompleteInt(HI_VOID* pBuf, TDE_LIST_TYPE_E enType);

/*****************************************************************************
* Function:      TdeHalNodeComplteAqList
* Description:   通知硬件Aq链表已经完成
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeComplteAqList(HI_VOID);

HI_VOID TdeHalNodeComplteNd(TDE_LIST_TYPE_E enListType);

/*****************************************************************************
* Function:      TdeHalNodeSetSrc1
* Description:   设置源1位图信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvSurface: 用于设置的位图信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc1(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface);

/*****************************************************************************
* Function:      TdeHalNodeSetSrc2
* Description:   设置源2位图信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvSurface: 用于设置的位图信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc2(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface);

/*****************************************************************************
* Function:      TdeHalNodeSetSrcMbY
* Description:   设置宏块格式源位图亮度信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvMbY: 用于设置的亮度位图信息
*                enMbOpt: 宏块模式选项
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetSrcMbY(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbY, TDE_DRV_MB_OPT_MODE_E enMbOpt);

/*****************************************************************************
* Function:      TdeHalNodeSetSrcMbCbCr
* Description:   设置宏块格式源位图色度信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvMbCbCr: 色度信息
*                enMbOpt: 宏块模式选项
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetSrcMbCbCr(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbCbCr, TDE_DRV_MB_OPT_MODE_E enMbOpt);

/*****************************************************************************
* Function:      TdeHalNodeSetTgt
* Description:   设置目的位图信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvSurface: 用于设置的位图信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetTgt(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, TDE_DRV_OUTALPHA_FROM_E enAlphaFrom);

/*****************************************************************************
* Function:      TdeHalNodeSetBaseOperate
* Description:   设置基本操作类型
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                enMode: 基本操作模式
*                enAlu: ALU模式
*                u32FillData: 如果基本操作模式中有填充操作,则读取此值
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetBaseOperate(TDE_HWNode_S* pHWNode, TDE_DRV_BASEOPT_MODE_E enMode,
                                 TDE_DRV_ALU_MODE_E enAlu, TDE_DRV_COLORFILL_S *pstColorFill);

/*****************************************************************************
* Function:      TdeHalNodeSetGlobalAlpha
* Description:   设置Alpha混合参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                u8Alpha: Alpha混合设置值
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetGlobalAlpha(TDE_HWNode_S* pHWNode, HI_U8 u8Alpha);

/*****************************************************************************
* Function:      TdeHalNodeSetExpAlpha
* Description:   当对RGB5551作Alpha扩展时,扩展为alpha0, alpha1的设置
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                u8Alpha: Alpha混合设置值
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetExpAlpha(TDE_HWNode_S* pHWNode, TDE_DRV_SRC_E enSrc, HI_U8 u8Alpha0, HI_U8 u8Alpha1);
/*****************************************************************************
* Function:      TdeHalNodeSetAlphaBorder
* Description:   设置是否使能Alplha边界处理
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                bEnable: 是否使能Alplha边界
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetAlphaBorder(TDE_HWNode_S* pHWNode, HI_BOOL bVEnable, HI_BOOL bHEnable);

/*****************************************************************************
* Function:      TdeHalNodeSetRop
* Description:   设置ROP运算参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                enRopCode: ROP运算码
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetRop(TDE_HWNode_S* pHWNode, TDE2_ROP_CODE_E enRgbRop, TDE2_ROP_CODE_E enAlphaRop);

/*****************************************************************************
* Function:      TdeHalNodeSetColorExp
* Description:   设置颜色扩展或颜色校正参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pClutCmd: Clut操作所需参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetClutOpt(TDE_HWNode_S* pHWNode, TDE_DRV_CLUT_CMD_S* pClutCmd, HI_BOOL bReload);

/*****************************************************************************
* Function:      TdeHalNodeSetColorKey
* Description:   根据当前的颜色格式设置color key 操作所需的参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                enFmt: 颜色格式
*                pColorKey: color key 设置值指针
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetColorKey(TDE_HWNode_S* pHWNode, TDE_COLORFMT_CATEGORY_E enFmtCat, 
                              TDE_DRV_COLORKEY_CMD_S* pColorKey);

/*****************************************************************************
* Function:      TdeHalNodeSetClipping
* Description:   设置矩形裁减操作参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pClip: 裁减矩形范围
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetClipping(TDE_HWNode_S* pHWNode, TDE_DRV_CLIP_CMD_S* pClip);

/*****************************************************************************
* Function:      TdeHalNodeSetFlicker
* Description:   设置抗闪烁滤波运算参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pFlicker: 抗闪烁系数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetFlicker(TDE_HWNode_S* pHWNode, TDE_DRV_FLICKER_CMD_S* pFlicker);

/*****************************************************************************
* Function:      TdeHalNodeSetResize
* Description:   设置缩放滤波运算参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pResize: 缩放系数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetResize(TDE_HWNode_S* pHWNode, TDE_DRV_RESIZE_CMD_S* pResize,TDE_NODE_SUBM_TYPE_E enNodeType);

/*****************************************************************************
* Function:      TdeHalNodeSetResize
* Description:   设置颜色空间转换所需参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pConv: 颜色空间转换参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetColorConvert(TDE_HWNode_S* pHWNode, TDE_DRV_CONV_MODE_CMD_S* pConv);

/*****************************************************************************
* Function:      TdeHalNodeAddChild
* Description:   在滤波操作时添加子节点
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pChildInfo: 添加子节点的配置信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeAddChild(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo);

/*****************************************************************************
* Function:      TdeHalNodeSetMbMode
* Description:   设置宏块处理所需参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pMbCmd: 宏块处理参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetMbMode(TDE_HWNode_S* pHWNode, TDE_DRV_MB_CMD_S* pMbCmd);

/*****************************************************************************
* Function:      TdeHalNodeSuspend
* Description:   挂起链表操作时,保存当前执行到的节点和行以保证能够恢复执行
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSuspend(HI_VOID);


/*获取被挂起的软件节点地址*/
HI_VOID TdeHalGetSuspendNode(HI_VOID **ppstSuspendNode);

/*****************************************************************************
* Function:      TdeHalSetDeflicerLevel
* Description:   设置抗闪烁级别
* Input:         eDeflickerLevel:抗闪烁级别
* Output:        无
* Return:        成功 / 失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalSetDeflicerLevel(TDE_DEFLICKER_LEVEL_E eDeflickerLevel);

/*****************************************************************************
* Function:      TdeHalGetDeflicerLevel
* Description:   设置抗闪烁级别
* Input:        
* Output:        pDeflicerLevel:抗闪烁级别
* Return:        成功 / 失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalGetDeflicerLevel(TDE_DEFLICKER_LEVEL_E *pDeflicerLevel);

/*****************************************************************************
* Function:      TdeHalSetAlphaThreshold
* Description:   设置alpha阈值
* Input:         u8ThresholdValue:alpha阈值
* Output:        
* Return:        成功 / 失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalSetAlphaThreshold(HI_U8 u8ThresholdValue);

/*****************************************************************************
* Function:      TdeHalGetAlphaThreshold
* Description:   获取alpha阈值
* Input:         
* Output:        pu8ThresholdValue:alpha阈值
* Return:        成功 / 失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalGetAlphaThreshold(HI_U8 * pu8ThresholdValue);

/*****************************************************************************
* Function:      TdeHalGetAlphaThresholdState
* Description:   设置alpha阈值判决开关状态
* Input:         bEnAlphaThreshold:alpha开关状态
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold);

/*****************************************************************************
* Function:      TdeHalGetAlphaThresholdState
* Description:   获取alpha阈值判决开关状态
* Input:         无
* Output:        pbEnAlphaThreshold:alpha判决阈值
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalGetAlphaThresholdState(HI_BOOL *pbEnAlphaThreshold);

/*****************************************************************************
* Function:      TdeHalNodeExecute
* Description:   启动TDE链表
* Input:         enListType: 链表类型
*                u32NodePhyAddr: 链表首节点地址
*                u32Update:链表首节点更新标识
*                bAqUseBuff: 是否使用临时buffer
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalNodeExecute(TDE_LIST_TYPE_E enListType, HI_U32 u32NodePhyAddr, HI_U64 u64Update, HI_BOOL bAqUseBuff);

/*****************************************************************************
* Function:      TdeHalRestoreAloneNode
* Description:   恢复节点操作，该节点为独立节点
* Input:         无
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_S32 TdeHalRestoreAloneNode(HI_VOID);

/*****************************************************************************
* Function:      TdeHalCurNode
* Description:   获取寄存器中当前执行的节点
* Input:         enListType: 链表类型
* Output:        节点物理地址
* Return:        无
* Others:        无
*****************************************************************************/
HI_U32 TdeHalCurNode(TDE_LIST_TYPE_E enListType);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif  /* _TDE_HAL_H_ */
