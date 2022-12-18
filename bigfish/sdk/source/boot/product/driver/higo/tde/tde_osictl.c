/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_osictl.c
* Description:  TDE osi ctl
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/
#include "tde_define.h"
#include "tde_osictl.h"
#include "tde_osilist.h"
#include "tde_hal.h"
#include "wmalloc.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif  /* __cplusplus */
#endif  /* __cplusplus */
STATIC int s_bSrc1Conv = 0;

/****************************************************************************/
/*                             TDE osi ctl 宏定义                           */
/****************************************************************************/
#define TDE_NO_SCALE_STEP 0x1000
#define TDE_FLOAT_BITLEN 12
#define TDE_MAX_SLICE_WIDTH 256
#define TDE_MAX_SLICE_NUM 20
#define TDE_MAX_RECT_WIDTH 0xfff
#define TDE_MAX_RECT_HEIGHT 0xfff
#define TDE_MAX_SURFACE_PITCH 0xffff
#define TDE_MAX_ZOOM_OUT_STEP 8

#ifdef TDE_VERSION_MPW
#define TDE_MAX_MINIFICATION_H  15
#define TDE_MAX_MINIFICATION_V  15
#else
#define TDE_MAX_MINIFICATION_H  255
#define TDE_MAX_MINIFICATION_V  255
#endif

#define TDE_MAX_TMPBUFF_WIDTH   720
#define TDE_MAX_TMPBUFF_HEIGHT  576

#define TDE_MIN(a, b) \
    (((a) > (b)) ? (b) : (a))
        
#define TDE_CALC_MAX_SLICE_NUM(bFF, vstep, in_w) \
    ((HI_FALSE == (bFF) && TDE_NO_SCALE_STEP == (vstep)) ? (1) : ((in_w) / 118 + 5)) /*AI7D02711*/

#define TDE_FILLUP_RECT_BY_DRVSURFACE(rect, drvSur) \
    do {\
        (rect).s32Xpos   = (HI_S32)(drvSur).u32Xpos; \
        (rect).s32Ypos   = (HI_S32)(drvSur).u32Ypos; \
        (rect).u32Width  = (drvSur).u32Width; \
        (rect).u32Height = (drvSur).u32Height; \
    } while (0)

/*AI7D02579 beg*/
#define TDE_CHANGE_DIR_BY_MIRROR(pDirect, enMirror) \
    do{\
        switch (enMirror)\
        {\
        case TDE2_MIRROR_HORIZONTAL:\
            (pDirect)->enHScan = !((pDirect)->enHScan);\
            break;\
        case TDE2_MIRROR_VERTICAL:\
            (pDirect)->enVScan = !((pDirect)->enVScan);\
            break;\
        case TDE2_MIRROR_BOTH:\
            (pDirect)->enHScan = !((pDirect)->enHScan);\
            (pDirect)->enVScan = !((pDirect)->enVScan);\
            break;\
        default:\
            break;\
        }\
    } while(0)
/*AI7D02579 end*/

#define TDE_SET_CLIP(phwNode, pstOpt) \
    do {\
        if (TDE2_CLIPMODE_NONE != (pstOpt)->enClipMode)\
        {\
            TDE_DRV_CLIP_CMD_S stClipCmd; \
            stClipCmd.u16ClipStartX = (HI_U16)(pstOpt)->stClipRect.s32Xpos; \
            stClipCmd.u16ClipStartY = (HI_U16)(pstOpt)->stClipRect.s32Ypos; \
            stClipCmd.u16ClipEndX = ((pstOpt)->stClipRect.s32Xpos \
                                     + (pstOpt)->stClipRect.u32Width - 1); \
            stClipCmd.u16ClipEndY = (pstOpt)->stClipRect.s32Ypos \
                                    + (pstOpt)->stClipRect.u32Height - 1; \
            stClipCmd.bInsideClip = (TDE2_CLIPMODE_INSIDE == (pstOpt)->enClipMode) \
                                    ? HI_TRUE : HI_FALSE; \
            TdeHalNodeSetClipping(phwNode, &stClipCmd); \
        } \
    } while (0)

/*
start % 4 = 0: (h-1)/4 + 1
start % 4 = 1: (h/4) + 1
start % 4 = 2: (h+1)/4 + 1
start % 4 = 3: (h+2)/4 + 1
 */
#define TDE_ADJ_SIZE_BY_START_I(start, size) \
    (((size) + (((start) % 4) - 1)) / 4 + 1)

/*
底场时,调整高度,只按照起始位置为4的整数来处理, 
因此, start预留没有用到
*/
#define TDE_ADJ_B_SIZE_BY_START_I(start, size) \
    ((size >> 2) + ((size % 4) >> 1))
/*
start 偶: (w-1)/2 +1
start 奇: w/2 + 1
 */
#define TDE_ADJ_SIZE_BY_START_P(start, size) \
    (((size) + (((start) % 2) - 1)) / 2 + 1)

/*
    if ((0 == (y) % 2) && (0 == (h) % 2))\
    {\
        (retH) = (h) / 2; \
    } \
    else \
    {\
        (retH) = (h) / 2 + 1; \
    } \
*/
#define TDE_ADJ_FIELD_HEIGHT_BY_START(y, h) \
    ((h) / 2 + (((y) & 1) | ((h) & 1)))
/*
    if ((1 == (y) % 2) && (1 == (h) % 2))\
    {\
        (retH) = (h) / 2 + 1; \
    } \
    else \
    {\
        (retH) = (h) / 2; \
    } \
*/
#define TDE_ADJ_B_FIELD_HEIGHT_BY_START(y, h) \
    ((h) / 2 + (((y) & 1) & ((h) & 1)))

/* AI7D02880
    返回YCbCr422R填充值
      ------------
      |Y'|Cb|Y|Cr|
      ------------
       ^_____|
      copy Y to Y'
*/
#define TDE_GET_YC422R_FILLVALUE(value) \
        ((value) & 0xffffff) | ((((value) >> 8) & 0xff) << 24)

#define TDE_UNIFY_RECT(psrcRect, pdstRect)\
    do{\
        if ((psrcRect)->u32Height != (pdstRect)->u32Height)\
        {\
            (psrcRect)->u32Height = TDE_MIN((psrcRect)->u32Height, (pdstRect)->u32Height);\
            (pdstRect)->u32Height = (psrcRect)->u32Height;\
        }\
        if((psrcRect)->u32Width != (pdstRect)->u32Width)\
        {\
            (psrcRect)->u32Width = TDE_MIN((psrcRect)->u32Width, (pdstRect)->u32Width);\
            (pdstRect)->u32Width = (psrcRect)->u32Width;\
        }\
    }while(0)

#define TDE_CHECK_COLORFMT(enColorFmt) \
    do{\
        if(TDE2_COLOR_FMT_BUTT <= enColorFmt)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "color format error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_MBCOLORFMT(enMbColorFmt) \
    do{\
        if(TDE2_MB_COLOR_FMT_BUTT <= enMbColorFmt)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "mb color format error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_OUTALPHAFROM(enOutAlphaFrom) \
    do{\
        if(TDE2_OUTALPHA_FROM_BUTT <= enOutAlphaFrom)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enOutAlphaFrom error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_ROPCODE(enRopCode) \
    do{\
        if(TDE2_ROP_BUTT <= enRopCode)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enRopCode error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_ALUCMD(enAluCmd) \
    do{\
        if(TDE2_ALUCMD_BUTT <= enAluCmd)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enAluCmd error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_MIRROR(enMirror) \
    do{\
        if(TDE2_MIRROR_BUTT <= enMirror)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enMirror error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_CLIPMODE(enClipMode) \
    do{\
        if(TDE2_CLIPMODE_BUTT <= enClipMode)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enClipMode error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_MBRESIZE(enMbResize) \
    do{\
        if(TDE2_MBRESIZE_BUTT <= enMbResize)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enMbResize error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_MBPICMODE(enMbPicMode) \
    do{\
        if(TDE_PIC_MODE_BUTT <= enMbPicMode)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enMbPicMode error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_COLORKEYMODE(enColorKeyMode) \
    do{\
        if(TDE2_COLORKEY_MODE_BUTT <= enColorKeyMode)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enColorKeyMode error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_FILTERMODE(enFilterMode) \
    do{\
        if(TDE2_FILTER_MODE_BUTT <= enFilterMode)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enFilterMode error:%d!\n",enFilterMode);\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_ROTATE(enRotate) \
    do{\
        if(TDE_ROTATE_BUTT <= enRotate)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "enRotate error!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
    }while(0)

#define TDE_CHECK_SUBBYTE_STARTX(startx, w, outFmt) \
    do {\
        HI_S32 s32Bpp;\
        s32Bpp = TdeOsiGetbppByFmt(outFmt);\
        if (0 > s32Bpp)\
        {\
            TDE_TRACE(TDE_KERN_ERR, "Unkown color format!\n");\
            return HI_ERR_TDE_INVALID_PARA;\
        }\
        \
        if (s32Bpp < 8)\
        {\
            /* 写操作时, subbyte格式对齐要求起始点字节对齐 */\
            if (((startx) * s32Bpp % 8) || ((w) * s32Bpp % 8))\
            {\
                TDE_TRACE(TDE_KERN_ERR, "Subbyte's start or width for writing is not aligned!\n");\
                return HI_ERR_TDE_INVALID_PARA;\
            }\
        }\
    }while(0)

        
/****************************************************************************/
/*                             TDE osi ctl 结构定义                         */
/****************************************************************************/

/* 象素格式转换类型 */
typedef enum hiTDE_COLORFMT_TRANSFORM_E
{
    TDE_COLORFMT_TRANSFORM_ARGB_ARGB = 0,
    TDE_COLORFMT_TRANSFORM_ARGB_YCbCr,
    TDE_COLORFMT_TRANSFORM_CLUT_ARGB,
    TDE_COLORFMT_TRANSFORM_CLUT_YCbCr,
    TDE_COLORFMT_TRANSFORM_CLUT_CLUT,
    TDE_COLORFMT_TRANSFORM_YCbCr_ARGB,
    TDE_COLORFMT_TRANSFORM_YCbCr_YCbCr,
    TDE_COLORFMT_TRANSFORM_An_An,
    TDE_COLORFMT_TRANSFORM_ARGB_An,
    TDE_COLORFMT_TRANSFORM_YCbCr_An,
    TDE_COLORFMT_TRANSFORM_BUTT,
} TDE_COLORFMT_TRANSFORM_E;

/* CLUT表用途 */
typedef enum hiTDE_CLUT_USAGE_E
{
    TDE_CLUT_COLOREXPENDING = 0,    /* 颜色扩展 */
    TDE_CLUT_COLORCORRECT,      /* 颜色校正 */
    TDE_CLUT_CLUT_BYPASS,
    TDE_CLUT_USAGE_BUTT
} TDE_CLUT_USAGE_E;

/* 帧/场处理模式 */
typedef enum hiTDE_PIC_MODE_E
{
    TDE_FRAME_PIC_MODE = 0,     /* 帧处理模式 */
    TDE_BOTTOM_FIELD_PIC_MODE,  /* 底场处理模式 */
    TDE_TOP_FIELD_PIC_MODE,     /* 顶场处理模式 */
    TDE_PIC_MODE_BUTT
} TDE_PIC_MODE_E;

typedef struct hiTDE_SLICE_INFO
{
    HI_U32 u32SliceXi;
    HI_U32 u32SliceWi;
    HI_U32 s32SliceHOfst;
    HI_U32 u32SliceXo;
    HI_U32 u32SliceWo;
    TDE_SLICE_TYPE_E enSliceType;
} TDE_SLICE_INFO;

typedef struct hiTDE_FILTER_OPT
{
    HI_U32  u32HStep;
    HI_U32  u32VStep;
    HI_S32  s32HOffset;
    HI_S32  s32VOffset;
    HI_U32  u32Bppi;
    HI_U32  u32WorkBufNum;
    HI_U32  bBadLastPix;   /*分块时,每块最后一点是否有效,用于YC422R分块 AI7D02579*/
    HI_BOOL bVRing;
    HI_BOOL bHRing;
    HI_BOOL bEvenStartInX;    /*当输入需要上采样时,bEvenStartInX 为 HI_TRUE*/
    HI_BOOL bEvenStartOutX;   /*当输出需要降采样时,bEvenStartOutX为 HI_TRUE*/
    HI_BOOL bCoefSym;       /*系数是否对称, 使用场景*/
    HI_BOOL b2OptCbCr;
    TDE_SCANDIRECTION_S stSrcDire;
    TDE_SCANDIRECTION_S stDstDire;
    TDE_MBSTART_ADJ_INFO_S stAdjInfo;
    TDE_DOUBLESRC_ADJ_INFO_S stDSAdjInfo;
    TDE_DRV_FILTER_MODE_E enFilterMode;
    HI_BOOL bFirstLineOut;
    HI_BOOL bLastLineOut;
} TDE_FILTER_OPT;

typedef enum hiTDE_OPERATION_CATEGORY_E
{
    TDE_OPERATION_SINGLE_SRC1 = 0,
    TDE_OPERATION_SINGLE_SRC2,
    TDE_OPERATION_DOUBLE_SRC,
    TDE_OPERATION_BUTT
} TDE_OPERATION_CATEGORY_E;
typedef enum hiTDE_PATTERN_OPERATION_CATEGORY_E
{
    TDE_PATTERN_OPERATION_SINGLE_SRC = 0,
    TDE_PATTERN_OPERATION_DOUBLE_SRC,
    TDE_PATTERN_OPERATION_BUTT
}TDE_PATTERN_OPERATION_CATEGORY_E;

/****************************************************************************/
/*                             TDE osi ctl 内部变量定义                     */
/****************************************************************************/
#ifdef TDE_PROC_ENABLE
/* used for proc */
extern TDE_HWNode_S *g_pstTdeHwNode;
extern HI_U32 g_u32TdeNdCurProcNum;
#define TDE_PROC_PRINT_ND_PARA(pNd) \
do{\
        TdeOsiPrintNode2Proc(pNd);\
}while(0)

#else
#define TDE_PROC_PRINT_ND_PARA(pNd)
#endif

/*
STATIC TDE_DRV_COLOR_FMT_E g_enTdeCommonDrvColorFmt[TDE2_COLOR_FMT_BUTT + 1] = {
    TDE_DRV_COLOR_FMT_RGB444,   TDE_DRV_COLOR_FMT_RGB555,   TDE_DRV_COLOR_FMT_RGB565,
    TDE_DRV_COLOR_FMT_RGB888,
    TDE_DRV_COLOR_FMT_ARGB4444,
    TDE_DRV_COLOR_FMT_ARGB1555, TDE_DRV_COLOR_FMT_ARGB8565, TDE_DRV_COLOR_FMT_ARGB8888,
    TDE_DRV_COLOR_FMT_CLUT1,
    TDE_DRV_COLOR_FMT_CLUT2,
    TDE_DRV_COLOR_FMT_CLUT4,    TDE_DRV_COLOR_FMT_CLUT8,    TDE_DRV_COLOR_FMT_ACLUT44,
    TDE_DRV_COLOR_FMT_ACLUT88,  TDE_DRV_COLOR_FMT_A1,
    TDE_DRV_COLOR_FMT_A8,       TDE_DRV_COLOR_FMT_YCbCr888, TDE_DRV_COLOR_FMT_AYCbCr8888,
    TDE_DRV_COLOR_FMT_YCbCr422, TDE_DRV_COLOR_FMT_byte,
    TDE_DRV_COLOR_FMT_halfword, TDE_DRV_COLOR_FMT_BUTT
};*/
STATIC TDE_DRV_COLOR_FMT_E g_enTdeCommonDrvColorFmt[] = {
#ifndef HIGO_CODE_CUT
    TDE_DRV_COLOR_FMT_RGB444,   TDE_DRV_COLOR_FMT_RGB444,
    TDE_DRV_COLOR_FMT_RGB555,   TDE_DRV_COLOR_FMT_RGB555,
    TDE_DRV_COLOR_FMT_RGB565,   TDE_DRV_COLOR_FMT_RGB565,
    TDE_DRV_COLOR_FMT_RGB888,   TDE_DRV_COLOR_FMT_RGB888,
    TDE_DRV_COLOR_FMT_ARGB4444, TDE_DRV_COLOR_FMT_ARGB4444, TDE_DRV_COLOR_FMT_ARGB4444, TDE_DRV_COLOR_FMT_ARGB4444,
#else
    TDE_DRV_COLOR_FMT_RGB565,
    TDE_DRV_COLOR_FMT_ARGB1555, 
#endif
#ifndef HIGO_CODE_CUT
    TDE_DRV_COLOR_FMT_ARGB1555, TDE_DRV_COLOR_FMT_ARGB1555, TDE_DRV_COLOR_FMT_ARGB1555,
    TDE_DRV_COLOR_FMT_ARGB8565, TDE_DRV_COLOR_FMT_ARGB8565, TDE_DRV_COLOR_FMT_ARGB8565, TDE_DRV_COLOR_FMT_ARGB8565,
#endif
    TDE_DRV_COLOR_FMT_ARGB8888, 
#ifndef HIGO_CODE_CUT
    TDE_DRV_COLOR_FMT_ARGB8888, TDE_DRV_COLOR_FMT_ARGB8888, TDE_DRV_COLOR_FMT_ARGB8888,
    TDE_DRV_COLOR_FMT_ARGB8888,
    TDE_DRV_COLOR_FMT_CLUT1,    TDE_DRV_COLOR_FMT_CLUT2,    TDE_DRV_COLOR_FMT_CLUT4,    
    TDE_DRV_COLOR_FMT_CLUT8,    TDE_DRV_COLOR_FMT_ACLUT44,  TDE_DRV_COLOR_FMT_ACLUT88,  
    TDE_DRV_COLOR_FMT_A1,       TDE_DRV_COLOR_FMT_A8,  
#endif    
    TDE_DRV_COLOR_FMT_YCbCr888, TDE_DRV_COLOR_FMT_AYCbCr8888,TDE_DRV_COLOR_FMT_YCbCr422, 
#ifndef HIGO_CODE_CUT  
    TDE_DRV_COLOR_FMT_byte,     TDE_DRV_COLOR_FMT_halfword,
#endif    
    TDE_DRV_COLOR_FMT_YCbCr400MBP,
    TDE_DRV_COLOR_FMT_YCbCr422MBH, TDE_DRV_COLOR_FMT_YCbCr422MBV,
    TDE_DRV_COLOR_FMT_YCbCr420MB,  TDE_DRV_COLOR_FMT_YCbCr420MB,  TDE_DRV_COLOR_FMT_YCbCr420MB,
    TDE_DRV_COLOR_FMT_YCbCr420MB,
    TDE_DRV_COLOR_FMT_YCbCr444MB, TDE_DRV_COLOR_FMT_BUTT
};
STATIC TDE_DRV_COLOR_FMT_E g_enTdeMbDrvColorFmt[TDE2_MB_COLOR_FMT_BUTT + 1] = {
    TDE_DRV_COLOR_FMT_YCbCr400MBP,
    TDE_DRV_COLOR_FMT_YCbCr422MBH, TDE_DRV_COLOR_FMT_YCbCr422MBV,
    TDE_DRV_COLOR_FMT_YCbCr420MB,  TDE_DRV_COLOR_FMT_YCbCr420MB,  TDE_DRV_COLOR_FMT_YCbCr420MB,
    TDE_DRV_COLOR_FMT_YCbCr420MB,
    TDE_DRV_COLOR_FMT_YCbCr444MB,  TDE_DRV_COLOR_FMT_BUTT
};

STATIC TDE_DRV_FILTER_MODE_E g_enTdeFilterMode[TDE2_FILTER_MODE_BUTT + 1] = {
    TDE_DRV_FILTER_COLOR, TDE_DRV_FILTER_ALPHA, TDE_DRV_FILTER_ALL, TDE_DRV_FILTER_ALL
};

/*是否局部抗闪烁标志*/
//STATIC HI_BOOL s_bRegionDeflicker = HI_FALSE;
/****************************************************************************/
/*                             TDE osi ctl 内部接口定义                     */
/****************************************************************************/
STATIC TDE_COLORFMT_CATEGORY_E   TdeOsiGetFmtCategory(TDE2_COLOR_FMT_E enFmt);

STATIC TDE_COLORFMT_TRANSFORM_E  TdeOsiGetFmtTransType(TDE2_COLOR_FMT_E enSrc2Fmt, TDE2_COLOR_FMT_E enDstFmt);

STATIC HI_S32                    TdeOsiGetScanInfo(TDE2_SURFACE_S *pSrc, TDE2_RECT_S *pstSrcRect,
                                                   TDE2_SURFACE_S *pstDst,
                                                   TDE2_RECT_S *pstDstRect, TDE2_OPT_S* pstOpt,
                                                   TDE_SCANDIRECTION_S *pstSrcDirection,
                                                   TDE_SCANDIRECTION_S *pstDstDirection);


STATIC  HI_S32             TdeOsiSetMbPara(TDE_HANDLE s32Handle, TDE_HWNode_S* pHWNode,
                                                 TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect,
                                                 TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                                                 TDE2_MBOPT_S* pMbOpt);

STATIC  HI_S32             TdeOsiAdjQuality(TDE_DRV_SURFACE_S* pS1Tmp, TDE_DRV_SURFACE_S* pS2Tmp,
                                                  TDE2_MB_S* pstMB, TDE2_RECT_S* pstMbRect, 
                                                  TDE2_SURFACE_S* pstDst, TDE2_RECT_S* pstDstRect,
                                                  TDE_PIC_MODE_E enPicMode, TDE2_MBOPT_S* pMbOpt);

STATIC  HI_U32             TdeOsiMbCalcHStep(HI_U32 u32Wi, HI_U32 u32Wo,
                                                   TDE2_MB_COLOR_FMT_E enInFmt, TDE2_MB_COLOR_FMT_E enOutFmt, HI_BOOL bCbCr);

STATIC  HI_U32             TdeOsiMbCalcVStep(HI_U32 u32Hi, HI_U32 u32Ho,
                                                   TDE2_MB_COLOR_FMT_E enInFmt, TDE2_MB_COLOR_FMT_E enOutFmt, HI_BOOL bCbCr);

STATIC  HI_S32             TdeOsiMbCalcHOffset(HI_U32 u32Xi, TDE2_MB_COLOR_FMT_E enFmt, HI_BOOL bCbCr);

STATIC  HI_S32             TdeOsiMbCalcVOffset(HI_U32 u32Yi, TDE2_MB_COLOR_FMT_E enFmt,
                                                     TDE_PIC_MODE_E enPicMode, HI_BOOL bCbCr);

STATIC  HI_U32             TdeOsiCalcNoLapSlice(TDE_SLICE_INFO *pSliceInfo, HI_U32 u32MaxNum, HI_U32 u32Xi, 
                                                      HI_U32 u32Xo, HI_U32 u32BmpW, /*AI7D02711*/
                                                      TDE_FILTER_OPT* pstFilterOpt);

STATIC  HI_U32             TdeOsiCalcOverLapSlice(TDE_SLICE_INFO *pSliceInfo, HI_U32 u32MaxNum, HI_U32 u32BmpXi, HI_U32 u32BmpWi, 
                                                        HI_U32 u32BmpXo, HI_U32 u32BmpWo, /*AI7D02711*/
                                                        TDE_FILTER_OPT* pstFilterOpt);

STATIC HI_S32                    TdeOsiSetFilterChildNode(TDE_HANDLE s32Handle, TDE_HWNode_S* pNode,
                                                          TDE2_RECT_S* pInRect,
                                                          TDE2_RECT_S*  pOutRect,
                                                          TDE2_DEFLICKER_MODE_E enDeflickerMode,
                                                          TDE_FILTER_OPT* pstFilterOpt);

STATIC HI_S32                    TdeOsiSetFilterNode(TDE_HANDLE s32Handle, TDE_HWNode_S* pNode,
                                                     TDE2_SURFACE_S *pstForeGround, TDE2_SURFACE_S *pstDst,
                                                     TDE2_RECT_S* pInRect, TDE2_RECT_S*  pOutRect,
                                                     TDE2_DEFLICKER_MODE_E enDeflickerMode, TDE_FILTER_OPT *pstFilterOpt);

STATIC HI_S32                    TdeOsi1SourceFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S *pstDst,
                                                   TDE2_RECT_S  *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor,
                                                   TDE2_OPT_S *pstOpt);
#if 0
STATIC HI_S32                    TdeOsi2SourceFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstSrc,
                                                   TDE2_RECT_S  *pstSrcRect,
                                                   TDE2_SURFACE_S *pstDst,
                                                   TDE2_RECT_S  *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor,
                                                   TDE2_OPT_S *pstOpt);
#endif
STATIC  HI_S32             TdeOsiCheckYc422RPara(TDE2_SURFACE_S* pstSrcSurface, TDE2_RECT_S *pstSrcRect, 
                                                       TDE2_SURFACE_S* pstDstSurface, TDE2_RECT_S *pstDstRect, 
                                                       HI_BOOL bDeflicker, HI_BOOL bResize);

STATIC TDE_OPERATION_CATEGORY_E  TdeOsiGetOptCategory(TDE2_SURFACE_S * pstBackGround, TDE2_RECT_S *pstBackGroundRect,
                                                      TDE2_SURFACE_S * pstForeGround, TDE2_RECT_S *pstForeGroundRect,
                                                      TDE2_SURFACE_S *pstDst,
                                                      TDE2_RECT_S *pstDstRect,
                                                      TDE2_OPT_S * pstOpt);

STATIC  HI_VOID            TdeOsiConvertSurface(TDE2_SURFACE_S *pstSur, TDE2_RECT_S *pstRect,
                                                      TDE_SCANDIRECTION_S *pstScanInfo,
                                                      TDE_DRV_SURFACE_S *pstDrvSur,
                                                      TDE2_RECT_S *pstOperationArea);

STATIC HI_S32                    TdeOsiConvertMbSurface(TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect,
                                                        TDE_DRV_SURFACE_S *pstDrvY,
                                                        TDE_DRV_SURFACE_S *pstDrvCbCr,
                                                        TDE_PIC_MODE_E enPicMode, HI_BOOL bCbCr2Opt);

STATIC  HI_VOID            TdeOsiCalcMbFilterOpt(TDE_FILTER_OPT* pstFilterOpt, TDE2_MB_COLOR_FMT_E enInFmt,
                                                       TDE2_MB_COLOR_FMT_E enOutFmt,
                                                       TDE2_RECT_S* pInRect, TDE2_RECT_S*  pOutRect, HI_BOOL bCbCr,
                                                       HI_BOOL bCus, TDE_PIC_MODE_E enPicMode);

STATIC HI_S32                   TdeOsiSetClipPara(TDE2_SURFACE_S * pstBackGround, TDE2_RECT_S *pstBGRect,
                                                   TDE2_SURFACE_S * pstForeGround,
                                                   TDE2_RECT_S *pstFGRect, TDE2_SURFACE_S * pstDst,
                                                   TDE2_RECT_S *pstDstRect,
                                                   TDE2_OPT_S * pstOpt,
                                                   TDE_HWNode_S *pstHwNode);

#ifndef HIGO_CODE_CUT
STATIC HI_S32                    TdeOsiMbSetClipPara(TDE2_RECT_S * pstDstRect, TDE2_MBOPT_S *pstMbOpt,
                                                     TDE_HWNode_S *pstHwNode);
#endif

STATIC HI_VOID                   TdeOsiSetBaseOptParaForBlit(TDE2_OPT_S * pstOpt, TDE2_SURFACE_S* pstSrc1, TDE2_SURFACE_S* pstSrc2,
                                                             TDE_OPERATION_CATEGORY_E enOptCategory, TDE_HWNode_S *pstHwNode);

STATIC  HI_VOID            TdeOsiSetResizePara(TDE_HWNode_S* pstHwNode, TDE_FILTER_OPT* pstFilterOpt,TDE_NODE_SUBM_TYPE_E enNodeType);
STATIC        HI_S32             TdeOsiAdjClipPara(TDE_HWNode_S* pHWNode);
STATIC  HI_VOID            TdeOsiSetDeflickerPara(TDE_HWNode_S* pstHwNode, TDE2_DEFLICKER_MODE_E enDeflickerMode, TDE_FILTER_OPT* pstFilterOpt);

STATIC HI_S32                    TdeOsiSetNodeFinish(TDE_HANDLE s32Handle, TDE_HWNode_S* pHWNode,
                                                     HI_U32 u32WorkBufNum, TDE_NODE_SUBM_TYPE_E enSubmType);

STATIC  HI_S32             TdeOsiCheckResizePara(HI_U32 u32InWidth, HI_U32 u32InHeight,
                                                       HI_U32 u32OutWidth, HI_U32 u32OutHeight);
STATIC  HI_BOOL            TdeOsiWhetherContainAlpha(TDE2_COLOR_FMT_E enColorFmt);
STATIC  HI_VOID            TdeOsiSetFilterOptAdjInfo(TDE_DRV_SURFACE_S *pInSur, TDE_DRV_SURFACE_S* pOutSur, 
                                                           TDE_FILTER_OPT* pstFilterOpt, TDE_CHILD_SCALE_MODE_E enScaleMode);
STATIC  HI_VOID            TdeOsiSetExtAlpha(TDE2_SURFACE_S *pstBackGround, TDE2_SURFACE_S *pstForeGround,
                                                   TDE_HWNode_S *pstHwNode);
STATIC HI_S32                    TdeOsiYC422TmpOpt(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                                                   TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pstOpt);
extern HI_VOID  TdeOsiListPutPhyBuff(HI_U32 u32BuffNum);
extern HI_U32 TdeOsiListGetPhyBuff(TDE_BUFFER_USAGE_E enBuffUsage);
#ifdef TDE_DEBUG
/* DEBUG functions for Node params */
STATIC  HI_VOID TdeOsiPrintNodeInfo(TDE_HWNode_S* pHWNode)
{
    printf("\n");
        if(pHWNode->u64TDE_UPDATE & 0x1)
        printf("01 u32TDE_INS          \t0x%x\n" ,pHWNode->u32TDE_INS);
        if((pHWNode->u64TDE_UPDATE >> 1) & 0x1)
        printf("02 u32TDE_S1_ADDR      \t0x%x\n" , pHWNode->u32TDE_S1_ADDR);
        if((pHWNode->u64TDE_UPDATE >> 2) & 0x1)
        printf("03 u32TDE_S1_TYPE      \t0x%x\n" , pHWNode->u32TDE_S1_TYPE);
        if((pHWNode->u64TDE_UPDATE >> 3) & 0x1)
        printf("04 u32TDE_S1_XY        \t0x%x\n" , pHWNode->u32TDE_S1_XY);
        if((pHWNode->u64TDE_UPDATE >> 4) & 0x1)
        printf("05 u32TDE_S1_FILL      \t0x%x\n" , pHWNode->u32TDE_S1_FILL);
        if((pHWNode->u64TDE_UPDATE >> 5) & 0x1)
        printf("06 u32TDE_S2_ADDR      \t0x%x\n" , pHWNode->u32TDE_S2_ADDR);
        if((pHWNode->u64TDE_UPDATE >> 6) & 0x1)
        printf("07 u32TDE_S2_TYPE      \t0x%x\n" , pHWNode->u32TDE_S2_TYPE);
        if((pHWNode->u64TDE_UPDATE >> 7) & 0x1)
        printf("08 u32TDE_S2_XY        \t0x%x\n" , pHWNode->u32TDE_S2_XY);
        if((pHWNode->u64TDE_UPDATE >> 8) & 0x1)
        printf("09 u32TDE_S2_SIZE      \t0x%x\n" , pHWNode->u32TDE_S2_SIZE);
        if((pHWNode->u64TDE_UPDATE >> 9) & 0x1)
        printf("10 u32TDE_S2_FILL      \t0x%x\n" , pHWNode->u32TDE_S2_FILL);
        if((pHWNode->u64TDE_UPDATE >> 10) & 0x1)
        printf("11 u32TDE_TAR_ADDR     \t0x%x\n" , pHWNode->u32TDE_TAR_ADDR);
        if((pHWNode->u64TDE_UPDATE >> 11) & 0x1)
        printf("12 u32TDE_TAR_TYPE     \t0x%x\n" , pHWNode->u32TDE_TAR_TYPE);
        if((pHWNode->u64TDE_UPDATE >> 12) & 0x1)
        printf("13 u32TDE_TAR_XY       \t0x%x\n" , pHWNode->u32TDE_TAR_XY);
        if((pHWNode->u64TDE_UPDATE >> 13) & 0x1)
        printf("14 u32TDE_TS_SIZE      \t0x%x\n" , pHWNode->u32TDE_TS_SIZE);
        if((pHWNode->u64TDE_UPDATE >> 14) & 0x1)
        printf("15 u32TDE_COLOR_CONV   \t0x%x\n" , pHWNode->u32TDE_COLOR_CONV);
        if((pHWNode->u64TDE_UPDATE >> 15) & 0x1)
        printf("16 u32TDE_CLUT_ADDR    \t0x%x\n" , pHWNode->u32TDE_CLUT_ADDR);
        if((pHWNode->u64TDE_UPDATE >> 16) & 0x1)
        printf("17 u32TDE_2D_RSZ       \t0x%x\n" , pHWNode->u32TDE_2D_RSZ);
        if((pHWNode->u64TDE_UPDATE >> 17) & 0x1)
        printf("18 u32TDE_HF_COEF_ADDR \t0x%x\n" , pHWNode->u32TDE_HF_COEF_ADDR);
        if((pHWNode->u64TDE_UPDATE >> 18) & 0x1)
        printf("19 u32TDE_VF_COEF_ADDR \t0x%x\n" , pHWNode->u32TDE_VF_COEF_ADDR);
        if((pHWNode->u64TDE_UPDATE >> 19) & 0x1)
#ifdef TDE_VERSION_MPW
        printf("20 u32TDE_RSZ_STEP     \t0x%x\n" , pHWNode->u32TDE_RSZ_STEP);
#else
        printf("20 u32TDE_RSZ_STEP     \t0x%x\n" , pHWNode->u32TDE_RSZ_HSTEP);
#endif
        if((pHWNode->u64TDE_UPDATE >> 20) & 0x1)
        printf("21 u32TDE_RSZ_Y_OFST   \t0x%x\n" , pHWNode->u32TDE_RSZ_Y_OFST);
        if((pHWNode->u64TDE_UPDATE >> 21) & 0x1)
        printf("22 u32TDE_RSZ_X_OFST   \t0x%x\n" , pHWNode->u32TDE_RSZ_X_OFST);
        if((pHWNode->u64TDE_UPDATE >> 22) & 0x1)
        printf("23 u32TDE_DFE_COEF0    \t0x%x\n" , pHWNode->u32TDE_DFE_COEF0);
        if((pHWNode->u64TDE_UPDATE >> 23) & 0x1)
        printf("24 u32TDE_DFE_COEF1    \t0x%x\n" , pHWNode->u32TDE_DFE_COEF1);
        if((pHWNode->u64TDE_UPDATE >> 24) & 0x1)
        printf("25 u32TDE_DFE_COEF2    \t0x%x\n" , pHWNode->u32TDE_DFE_COEF2);
        if((pHWNode->u64TDE_UPDATE >> 25) & 0x1)
        printf("26 u32TDE_DFE_COEF3    \t0x%x\n" , pHWNode->u32TDE_DFE_COEF3);
        if((pHWNode->u64TDE_UPDATE >> 26) & 0x1)
        printf("27 u32TDE_ALU          \t0x%x\n" , pHWNode->u32TDE_ALU);
        if((pHWNode->u64TDE_UPDATE >> 27) & 0x1)
        printf("28 u32TDE_CK_MIN       \t0x%x\n" , pHWNode->u32TDE_CK_MIN);
        if((pHWNode->u64TDE_UPDATE >> 28) & 0x1)
        printf("29 u32TDE_CK_MAX       \t0x%x\n" , pHWNode->u32TDE_CK_MAX);
        if((pHWNode->u64TDE_UPDATE >> 29) & 0x1)
        printf("30 u32TDE_CLIP_START   \t0x%x\n" , pHWNode->u32TDE_CLIP_START);
        if((pHWNode->u64TDE_UPDATE >> 30) & 0x1)
        printf("31 u32TDE_CLIP_STOP    \t0x%x\n" , pHWNode->u32TDE_CLIP_STOP);
        //if((pHWNode->u64TDE_UPDATE >> 31) & 0x1)
        printf("32 u32TDE_UPDATE       \t0x%x\n" , (HI_U32)(pHWNode->u64TDE_UPDATE & 0xffffffff));
    printf("\n");
}
#endif



/*****************************************************************************
* Function:      TdeOsiCheckResizePara
* Description:   检查缩放比例限制
* Input:         pstInRect: 缩放前区域大小
*                pstOutRect: 缩放后区域大小
* Output:        无
* Return:        TDE_COLORFMT_CATEGORY_E 象素格式分类
* Others:        无
*****************************************************************************/
STATIC  HI_S32 TdeOsiCheckResizePara(HI_U32 u32InWidth, HI_U32 u32InHeight,
                                           HI_U32 u32OutWidth, HI_U32 u32OutHeight)
{
    if (((u32OutWidth * TDE_MAX_MINIFICATION_H) < u32InWidth)
        || ((u32OutHeight * TDE_MAX_MINIFICATION_V) < u32InHeight))
    {
        TDE_TRACE(TDE_KERN_ERR, "Resize parameter error!\n");
        return -1;
    }
    else
    {
        return 0;
    }
}

/*****************************************************************************
* Function:      TdeOsiGetFmtCategory
* Description:   获得象素格式分类信息
* Input:         enFmt 象素格式
* Output:        无
* Return:        TDE_COLORFMT_CATEGORY_E 象素格式分类
* Others:        无
*****************************************************************************/
STATIC TDE_COLORFMT_CATEGORY_E TdeOsiGetFmtCategory(TDE2_COLOR_FMT_E enFmt)
{
    /* 目标是ARGB格式 */
    if (enFmt <= TDE2_COLOR_FMT_ARGB8888)
    {
        return TDE_COLORFMT_CATEGORY_ARGB;
    }
#ifndef HIGO_CODE_CUT
    /* 目标是查找表格式 */
    else if (enFmt <= TDE2_COLOR_FMT_ACLUT88)
    {
        return TDE_COLORFMT_CATEGORY_CLUT;
    }
    /* 目标是alpha查找表格式 */
    else if (enFmt <= TDE2_COLOR_FMT_A8)
    {
        return TDE_COLORFMT_CATEGORY_An;
    }
#endif    
    /*目标是YCbCr格式 */
    else if (enFmt <= TDE2_COLOR_FMT_YCbCr422)
    {
        return TDE_COLORFMT_CATEGORY_YCbCr;
    }
#ifndef HIGO_CODE_CUT   
    /* byte格式 */
    else if (enFmt == TDE2_COLOR_FMT_byte)
    {
        return TDE_COLORFMT_CATEGORY_BYTE;
    }
   
    /* halfword格式 */
    else if (enFmt == TDE2_COLOR_FMT_halfword)
    {
        return TDE_COLORFMT_CATEGORY_HALFWORD;
    }
#endif    
    /* 错误格式 */
    else
    {
        return TDE_COLORFMT_CATEGORY_BUTT;
    }
}

/*****************************************************************************
* Function:      TdeOsiGetFmtTransType
* Description:   获取象素格式转换类型
* Input:         enSrc2Fmt 前景象素格式
                 enDstFmt 目标象素格式
* Output:        无
* Return:        TDE_COLORFMT_TRANSFORM_E 象素格式转换类型
* Others:        无
*****************************************************************************/
STATIC TDE_COLORFMT_TRANSFORM_E TdeOsiGetFmtTransType(TDE2_COLOR_FMT_E enSrc2Fmt, TDE2_COLOR_FMT_E enDstFmt)
{
    TDE_COLORFMT_CATEGORY_E enSrcCategory;
    TDE_COLORFMT_CATEGORY_E enDstCategory;

    /* 获取前景象素格式分类 */
    enSrcCategory = TdeOsiGetFmtCategory(enSrc2Fmt);

    /* 获取目标象素格式分类 */
    enDstCategory = TdeOsiGetFmtCategory(enDstFmt);

    switch (enSrcCategory)
    {
    case TDE_COLORFMT_CATEGORY_ARGB:
    {
        if (TDE_COLORFMT_CATEGORY_ARGB == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_ARGB_ARGB;
        }

        if (TDE_COLORFMT_CATEGORY_YCbCr == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_ARGB_YCbCr;
        }

        if (TdeOsiWhetherContainAlpha(enDstFmt))
        {
            return TDE_COLORFMT_TRANSFORM_YCbCr_An;
        }

        return TDE_COLORFMT_TRANSFORM_BUTT;
    }
#ifndef HIGO_CODE_CUT
    case TDE_COLORFMT_CATEGORY_CLUT:
    {
        if (TDE_COLORFMT_CATEGORY_ARGB == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_CLUT_ARGB;
        }

        if (TDE_COLORFMT_CATEGORY_YCbCr == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_CLUT_YCbCr;
        }

        if (TDE_COLORFMT_CATEGORY_CLUT == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_CLUT_CLUT;
        }

        return TDE_COLORFMT_TRANSFORM_BUTT;
    }
#endif
    case TDE_COLORFMT_CATEGORY_YCbCr:
    {
        if (TDE_COLORFMT_CATEGORY_ARGB == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_YCbCr_ARGB;
        }

        if (TDE_COLORFMT_CATEGORY_YCbCr == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_YCbCr_YCbCr;
        }

        if (TdeOsiWhetherContainAlpha(enDstFmt))
        {
            return TDE_COLORFMT_TRANSFORM_YCbCr_An;
        }

        return TDE_COLORFMT_TRANSFORM_BUTT;
    }
#ifndef HIGO_CODE_CUT
    case TDE_COLORFMT_CATEGORY_An:
    {
        if (TDE_COLORFMT_CATEGORY_An == enDstCategory)
        {
            return TDE_COLORFMT_TRANSFORM_An_An;
        }

        return TDE_COLORFMT_TRANSFORM_BUTT;
    }
#endif
    default:
        return TDE_COLORFMT_TRANSFORM_BUTT;
    }
}
#ifndef HIGO_CODE_CUT
/*****************************************************************************
* Function:      TdeOsiIsSingleSrc2Rop
* Description:   查询rop操作是否为单源2操作
* Input:         enRop rop操作类型
* Output:        无
* Return:        HI_TRUE 单源ROP；HI_FALSE 非单源ROP
* Others:        无
*****************************************************************************/
STATIC  HI_BOOL TdeOsiIsSingleSrc2Rop(TDE2_ROP_CODE_E enRop)
{
    switch (enRop)
    {
    case TDE2_ROP_BLACK:
    case TDE2_ROP_NOTCOPYPEN:
    case TDE2_ROP_COPYPEN:
    case TDE2_ROP_WHITE:
        return HI_TRUE;

    default:
        return HI_FALSE;
    }
}

/*****************************************************************************
* Function:      TdeOsiGetClutUsage
* Description:   获取查找表用途
* Input:         enSrc2Fmt 前景象素格式
                 enDstFmt  目标象素格式
* Output:        无
* Return:        TDE_CLUT_USAGE_E 查找表用途
* Others:        无
*****************************************************************************/
STATIC  TDE_CLUT_USAGE_E TdeOsiGetClutUsage(TDE2_COLOR_FMT_E enSrcFmt, TDE2_COLOR_FMT_E enDstFmt)
{
    TDE_COLORFMT_TRANSFORM_E enColorTransType;

    enColorTransType = TdeOsiGetFmtTransType(enSrcFmt, enDstFmt);

    switch (enColorTransType)
    {
    case TDE_COLORFMT_TRANSFORM_CLUT_ARGB:
    case TDE_COLORFMT_TRANSFORM_CLUT_YCbCr:
        return TDE_CLUT_COLOREXPENDING;         /* 颜色扩展 */

    case TDE_COLORFMT_TRANSFORM_ARGB_ARGB:
    case TDE_COLORFMT_TRANSFORM_YCbCr_YCbCr:
        return TDE_CLUT_COLORCORRECT;           /* 颜色校正 */

    case TDE_COLORFMT_TRANSFORM_CLUT_CLUT:
        return TDE_CLUT_CLUT_BYPASS;

    default:
        return TDE_CLUT_USAGE_BUTT;
    }
}
#endif
STATIC  HI_BOOL TdeOsiWhetherContainAlpha(TDE2_COLOR_FMT_E enColorFmt)
{
    switch (enColorFmt)
    {
#ifndef HIGO_CODE_CUT
    case TDE2_COLOR_FMT_ARGB4444:
    case TDE2_COLOR_FMT_ARGB8565:
#endif
    case TDE2_COLOR_FMT_ARGB1555:

    case TDE2_COLOR_FMT_ARGB8888:
    case TDE2_COLOR_FMT_AYCbCr8888:
        return HI_TRUE;

    default:
        return HI_FALSE;
    }
}

/*****************************************************************************
* Function:      TdeOsiSetFilterOptAdjInfo
* Description:   设置宏块格式位图每块计算时需要调整的信息
* Input:         pInSur:  输入亮度信息
*                pOutSur: 输出位图信息
*                pstFilterOpt:    滤波信息
*                enScaleMode:     子节点缩放模式
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC  HI_VOID TdeOsiSetFilterOptAdjInfo(TDE_DRV_SURFACE_S *pInSur, TDE_DRV_SURFACE_S* pOutSur, 
                                                TDE_FILTER_OPT* pstFilterOpt, TDE_CHILD_SCALE_MODE_E enScaleMode)
{
    pstFilterOpt->stAdjInfo.enScaleMode = enScaleMode;
    pstFilterOpt->stAdjInfo.u32StartInX = pInSur->u32Xpos;
    pstFilterOpt->stAdjInfo.u32StartInY = pInSur->u32Ypos;
    pstFilterOpt->stAdjInfo.u32StartOutX = pOutSur->u32Xpos;
    pstFilterOpt->stAdjInfo.u32StartOutY = pOutSur->u32Ypos;
    pstFilterOpt->stAdjInfo.enFmt = pInSur->enColorFmt;

    if (TDE_CHILD_SCALE_MB_CONCA_L == enScaleMode 
        && (TDE_DRV_COLOR_FMT_YCbCr420MB == pInSur->enColorFmt 
            || TDE_DRV_COLOR_FMT_YCbCr422MBH == pInSur->enColorFmt))
    {
        pstFilterOpt->bEvenStartInX = HI_TRUE;
        pstFilterOpt->bBadLastPix = HI_TRUE;
    }
#if 1
    if (TDE_DRV_COLOR_FMT_YCbCr422 == pOutSur->enColorFmt)
    {
        pstFilterOpt->bEvenStartOutX = HI_TRUE;
    }
#endif
}

/*****************************************************************************
* Function:      TdeOsiCheckSingleSrc2Opt
* Description:   检查前景单源操作参数是否合法
* Input:         enSrc2Fmt 前景象素格式
                 enDstFmt  目标象素格式
                 pstOpt      操作属性指针
* Output:        无
* Return:        0  合法参数;
                 -1 非法参数
* Others:        无
*****************************************************************************/
STATIC HI_S32  TdeOsiCheckSingleSrc2Opt(TDE2_COLOR_FMT_E enSrc2Fmt, TDE2_COLOR_FMT_E enDstFmt,
                                        TDE2_OPT_S* pstOpt)
{
#ifndef HIGO_CODE_CUT
    TDE_COLORFMT_TRANSFORM_E enColorTransType;

    /* 如果color key使能，返回参数错误 */
    if (TDE2_COLORKEY_MODE_NONE != pstOpt->enColorKeyMode)
    {
        TDE_TRACE(TDE_KERN_ERR, "It doesn't support colorkey in single source mode!\n");
        return -1;
    }

    /* 如果运算类型为ROP且该ROP运算不是单源2ROP运算，返回参数错误 */
    if (TDE2_ALUCMD_ROP == pstOpt->enAluCmd)
    {
        if ((!TdeOsiIsSingleSrc2Rop(pstOpt->enRopCode_Alpha))
            || (!TdeOsiIsSingleSrc2Rop(pstOpt->enRopCode_Color)))
        {
            TDE_TRACE(TDE_KERN_ERR, "Only support single s2 rop!\n");
            return -1;
        }
    }
    else if(TDE2_ALUCMD_NONE != pstOpt->enAluCmd)
    {
        TDE_TRACE(TDE_KERN_ERR, "Alu mode error!\n");
        return -1;
    }

    enColorTransType = TdeOsiGetFmtTransType(enSrc2Fmt, enDstFmt);
    if(TDE_COLORFMT_TRANSFORM_BUTT == enColorTransType)
    {
        TDE_TRACE(TDE_KERN_ERR, "Unkown color transport type!\n");
        return -1;
    }

    if(TDE_COLORFMT_TRANSFORM_CLUT_CLUT == enColorTransType)
    {
        /* 不支持抗闪烁和缩放,不支持ROP,不支持镜象 */
        if ((pstOpt->enDeflickerMode != TDE2_DEFLICKER_MODE_NONE)
            || (pstOpt->bResize)
            || (TDE2_ALUCMD_ROP == pstOpt->enAluCmd)
            /*|| (TDE2_MIRROR_NONE != pstOpt->enMirror)*/) /*AI7D02892 去掉Mirror限制*/
        {
            TDE_TRACE(TDE_KERN_ERR, "It doesn't support deflicker or ROP or mirror!\n");
            return -1;
        }
    }
#if 0
    else if(TDE_COLORFMT_TRANSFORM_An_An == enColorTransType)
    {
        if (enSrc2Fmt != enDstFmt)
        {
            TDE_TRACE(TDE_KERN_ERR, "s2 color format and target color format are not equal!\n");
            return -1;
        }
    }
#endif
#endif
    return 0;
}


/*****************************************************************************
* Function:      TdeOsiCheckDoubleSrcOpt
* Description:   检查双源操作参数是否合法
* Input:         enSrc1Fmt 背景象素格式
                 enSrc2Fmt 前景象素格式
                 enDstFmt  目标象素格式
                 pstOpt      操作属性指针
* Output:        无
* Return:        0  合法参数;
                 -1 非法参数
* Others:        无
*****************************************************************************/
STATIC HI_S32  TdeOsiCheckDoubleSrcOpt(TDE2_COLOR_FMT_E enSrc1Fmt, TDE2_COLOR_FMT_E enSrc2Fmt,
                                       TDE2_COLOR_FMT_E enDstFmt, TDE2_OPT_S* pstOpt)
{
#ifndef HIGO_CODE_CUT
    TDE_COLORFMT_CATEGORY_E enSrc1Category;
    TDE_COLORFMT_CATEGORY_E enSrc2Category;
    TDE_COLORFMT_CATEGORY_E enDstCategory;

    /* 获取背景象素格式分类 */
    enSrc1Category = TdeOsiGetFmtCategory(enSrc1Fmt);

    /* 获取前景象素格式分类 */
    enSrc2Category = TdeOsiGetFmtCategory(enSrc2Fmt);

    /* 获取目标象素格式分类 */
    enDstCategory = TdeOsiGetFmtCategory(enDstFmt);

    if ((TDE_COLORFMT_CATEGORY_BYTE <= enSrc1Category)
        || (TDE_COLORFMT_CATEGORY_BYTE <= enSrc2Category)
        || (TDE_COLORFMT_CATEGORY_BYTE <= enDstCategory))
    {
        TDE_TRACE(TDE_KERN_ERR, "unkown format!\n");
        return -1;
    }

    if (TDE_COLORFMT_CATEGORY_ARGB == enSrc1Category)
    {
        if (TDE_COLORFMT_CATEGORY_An == enSrc2Category)
        {
            /* 目标必须带alpha位*/
            if (!TdeOsiWhetherContainAlpha(enDstFmt))
            {
                TDE_TRACE(TDE_KERN_ERR, "Target must have alpha component!\n");
                return -1;
            }
        }
    }
    else if ((TDE2_COLOR_FMT_YCbCr888 == enSrc1Fmt)
             || (TDE2_COLOR_FMT_AYCbCr8888 == enSrc1Fmt))
    {
        if (TDE_COLORFMT_CATEGORY_An == enSrc2Category)
        {
            /* 目标必须带alpha位*/
            if (!TdeOsiWhetherContainAlpha(enDstFmt))
            {
                TDE_TRACE(TDE_KERN_ERR, "Target must have alpha component!\n");
                return -1;
            }
        }
    }
    else if (TDE_COLORFMT_CATEGORY_CLUT == enSrc1Category)
    {
        if ((TDE_COLORFMT_CATEGORY_CLUT != enSrc2Category)
            || (TDE_COLORFMT_CATEGORY_CLUT != enDstCategory))
        {
            TDE_TRACE(TDE_KERN_ERR, "Unsupported operation!\n");
            return -1;
        }

        /* 不支持抗闪烁和缩放,不支持ROP,支持镜象 */
        if ((pstOpt->enDeflickerMode != TDE2_DEFLICKER_MODE_NONE)|| (pstOpt->bResize)
            || (TDE2_ALUCMD_NONE != pstOpt->enAluCmd)
            /*|| (TDE2_MIRROR_NONE != pstOpt->enMirror)*/) /*AI7D02892去掉Mirror限制*/
        {
            TDE_TRACE(TDE_KERN_ERR, "It doesn't support deflicker or ROP or mirror!\n");
            return -1;
        }
    }
    else if((TDE_COLORFMT_CATEGORY_An == enSrc1Category)
        && (TDE_COLORFMT_CATEGORY_An == enSrc2Category)
        && (TDE_COLORFMT_CATEGORY_An == enDstCategory))
    {
        /* 不支持ROP,不支持叠加,支持镜象 */
        if ((TDE2_ALUCMD_NONE != pstOpt->enAluCmd)
            /*|| (TDE2_MIRROR_NONE != pstOpt->enMirror)*/) /*AI7D02892去掉Mirror限制*/
        {
            TDE_TRACE(TDE_KERN_ERR, "It doesn't support ROP or mirror!\n");
            return -1;
        }
    }
#endif    
    return 0;
}

/*****************************************************************************
* Function:      TdeOsiDoubleSrcGetOptCode
* Description:   获取双源操作的编码
* Input:         enSrc1Fmt 背景象素格式
                 enSrc2Fmt 前景象素格式
                 enDstFmt  目标象素格式
* Output:        无
* Return:        编码值
* Others:        无
*****************************************************************************/
STATIC HI_U16 TdeOsiDoubleSrcGetOptCode(TDE2_COLOR_FMT_E enSrc1Fmt, TDE2_COLOR_FMT_E enSrc2Fmt,
                                        TDE2_COLOR_FMT_E enDstFmt)
{
    HI_U16 u16Code1 = 0x0;
    HI_U16 u16Code2 = 0x0;
    TDE_COLORFMT_TRANSFORM_E enColorTransType;

    enColorTransType = TdeOsiGetFmtTransType(enSrc2Fmt, enSrc1Fmt);
    switch (enColorTransType)
    {
    case TDE_COLORFMT_TRANSFORM_ARGB_ARGB:
        u16Code1 = 0x0;
        break;

    case TDE_COLORFMT_TRANSFORM_ARGB_YCbCr:
        u16Code1 = 0x5;
        break;

    case TDE_COLORFMT_TRANSFORM_CLUT_ARGB:
        u16Code1 = 0x8;
        break;

    case TDE_COLORFMT_TRANSFORM_YCbCr_ARGB:
        u16Code1 = 0x1;
        break;

    case TDE_COLORFMT_TRANSFORM_YCbCr_YCbCr:
        u16Code1 = 0x0;
        break;

    default:
        u16Code1 = 0x8000;
        return u16Code1;
    }

    enColorTransType = TdeOsiGetFmtTransType(enSrc1Fmt, enDstFmt);
    switch (enColorTransType)
    {
    case TDE_COLORFMT_TRANSFORM_ARGB_ARGB:
        u16Code2 = 0x0;
        break;

    case TDE_COLORFMT_TRANSFORM_ARGB_YCbCr:
        u16Code2 = 0x2;
        break;

    case TDE_COLORFMT_TRANSFORM_CLUT_ARGB:
        u16Code2 = 0x8;
        break;

    case TDE_COLORFMT_TRANSFORM_CLUT_YCbCr:
        u16Code2 = 0xa;
        break;

    case TDE_COLORFMT_TRANSFORM_YCbCr_ARGB:
        u16Code2 = 0x6;
        break;

    case TDE_COLORFMT_TRANSFORM_YCbCr_YCbCr:
        u16Code2 = 0x0;
        break;

    default:
        u16Code2 = 0x8000;
        return u16Code2;
    }

    return (u16Code1 | u16Code2);
}

/*****************************************************************************
* Function:      TdeOsiSingleSrc2GetOptCode
* Description:   获取双源操作的编码
* Input:         enSrc2Fmt 前景象素格式
                 enDstFmt  目标象素格式
* Output:        无
* Return:        编码值,编码值的语法如下:

|------0-----|------1-----|------2-------|------3-----|
|-----ICSC---|-----OCSC---|(in)RGB->YCbCr|-----CLUT---|

* Others:        无
*****************************************************************************/
STATIC HI_U16 TdeOsiSingleSrc2GetOptCode(TDE2_COLOR_FMT_E enSrc2Fmt, TDE2_COLOR_FMT_E enDstFmt)
{
    HI_U16 u16Code = 0;
    TDE_COLORFMT_TRANSFORM_E enColorTransType;

    enColorTransType = TdeOsiGetFmtTransType(enSrc2Fmt, enDstFmt);

    switch (enColorTransType)
    {
    case TDE_COLORFMT_TRANSFORM_ARGB_ARGB:
        u16Code = 0x0;
        break;

    case TDE_COLORFMT_TRANSFORM_ARGB_YCbCr:
        u16Code = 0x5;
        break;

    case TDE_COLORFMT_TRANSFORM_CLUT_ARGB:
        u16Code = 0x8;
        break;

    case TDE_COLORFMT_TRANSFORM_CLUT_CLUT:
        u16Code = 0x0;
        break;

    case TDE_COLORFMT_TRANSFORM_CLUT_YCbCr:
        u16Code = 0xA;
        break;

    case TDE_COLORFMT_TRANSFORM_YCbCr_ARGB:
        u16Code = 0x1;
        break;

    case TDE_COLORFMT_TRANSFORM_YCbCr_YCbCr:
        u16Code = 0x0;
        break;

    default:
        u16Code = 0x8000;
    }

    return u16Code;
}

/*****************************************************************************
* Function:      TdeOsiGetConvbyCode
* Description:   通过格式转换码获取格式转换方式
* Input:         u16Code  格式转换码
*                pstConv  格式转换方式结构
* Output:        无
* Return:        编码值
* Others:        无
*****************************************************************************/
STATIC HI_VOID TdeOsiGetConvbyCode(HI_U16 u16Code, TDE_DRV_CONV_MODE_CMD_S *pstConv)
{
    pstConv->bInConv   = u16Code & 0x1;
    pstConv->bOutConv  = (u16Code >> 1) & 0x1;
    pstConv->bInRGB2YC = ((u16Code >> 2) & 0x1);
    pstConv->bInSrc1Conv = s_bSrc1Conv;

    return;
}

/*****************************************************************************
* Function:      TdeOsiGetbppByFmt
* Description:   获取象素格式每象素所占的bit数
* Input:         enFmt  目标象素格式
* Output:        无
* Return:        -1 失败；其他:每象素所占的bit数
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiGetbppByFmt(TDE2_COLOR_FMT_E enFmt)
{
    switch (enFmt)
    {
#ifndef HIGO_CODE_CUT  
    case TDE2_COLOR_FMT_RGB444:
    case TDE2_COLOR_FMT_RGB555:
    case TDE2_COLOR_FMT_ARGB4444:
#endif   
    case TDE2_COLOR_FMT_RGB565:
    case TDE2_COLOR_FMT_ARGB1555:
#ifndef HIGO_CODE_CUT
    case TDE2_COLOR_FMT_ACLUT88:
    case TDE2_COLOR_FMT_YCbCr422:     //???
    case TDE2_COLOR_FMT_halfword:
#endif        
        return 16;
#ifndef HIGO_CODE_CUT
    case TDE2_COLOR_FMT_RGB888:
    case TDE2_COLOR_FMT_ARGB8565:
#endif
    case TDE2_COLOR_FMT_YCbCr888:    
        return 24;
    case TDE2_COLOR_FMT_ARGB8888:
    case TDE2_COLOR_FMT_AYCbCr8888:
        return 32;
#ifndef HIGO_CODE_CUT
    case TDE2_COLOR_FMT_CLUT1:
    case TDE2_COLOR_FMT_A1:
        return 1;

    case TDE2_COLOR_FMT_CLUT2:
        return 2;

    case TDE2_COLOR_FMT_CLUT4:
        return 4;

    case TDE2_COLOR_FMT_CLUT8:
    case TDE2_COLOR_FMT_ACLUT44:
    case TDE2_COLOR_FMT_A8:
    case TDE2_COLOR_FMT_byte:
        return 8;
#endif
    default:
        return -1;
    }
}

/*****************************************************************************
* Function:      TdeOsiGetScanInfo
* Description:   获取扫描方向，防止重叠
* Input:         pSrc  源位图
                 pstDst  目标位图
                 enMirror 镜象类型
* Output:        pstSrcDirection 源扫描信息
                 pstDstDirection 目标扫描信息
* Return:        0  成功
                 -1 失败
* Others:        AI7D02579增加对YCbCr422R所需反扫描处理
*****************************************************************************/
STATIC HI_S32 TdeOsiGetScanInfo(TDE2_SURFACE_S *pSrc, TDE2_RECT_S *pstSrcRect, TDE2_SURFACE_S *pstDst,
                                TDE2_RECT_S *pstDstRect, TDE2_OPT_S* pstOpt,
                                TDE_SCANDIRECTION_S *pstSrcDirection,
                                TDE_SCANDIRECTION_S *pstDstDirection)
{
    HI_U32 u32SrcAddr;
    HI_U32 u32DstAddr;
    HI_U32 u32AddrDiff;
    HI_BOOL bFilter = HI_FALSE;
    TDE2_MIRROR_E enMirror = TDE2_MIRROR_NONE;
    HI_S32 s32SrcdBpp, s32DstBpp;

    TDE_ASSERT(NULL != pSrc);
    TDE_ASSERT(NULL != pstSrcRect);
    TDE_ASSERT(NULL != pstDst);
    TDE_ASSERT(NULL != pstDstRect);
    TDE_ASSERT(NULL != pstSrcDirection);
    TDE_ASSERT(NULL != pstDstDirection);

    /* 写操作时, subbyte格式对齐要求起始点字节对齐 */
#ifndef HIGO_CODE_CUT
    TDE_CHECK_SUBBYTE_STARTX(pstDstRect->s32Xpos, pstDstRect->u32Width, pstDst->enColorFmt);
#endif
    /* 默认扫描方向 */
    pstSrcDirection->enHScan = TDE_SCAN_LEFT_RIGHT;
    pstSrcDirection->enVScan = TDE_SCAN_UP_DOWN;
    pstDstDirection->enHScan = TDE_SCAN_LEFT_RIGHT;
    pstDstDirection->enVScan = TDE_SCAN_UP_DOWN;

    if (HI_NULL != pstOpt)
    {
        if ((pstOpt->enDeflickerMode != TDE2_DEFLICKER_MODE_NONE) || pstOpt->bResize)
        {
            bFilter = HI_TRUE;
        }
        #if 0
        if ((pstOpt->enDeflickerMode != TDE2_DEFLICKER_MODE_NONE)
            || (pstOpt->bResize && pstSrcRect->u32Height != pstDstRect->u32Height))
        {
            /* 如果输出格式为YCbCr422, 且为垂直滤波, 则使用反扫描 */
            if (TDE2_COLOR_FMT_YCbCr422 == pstDst->enColorFmt)
            {
                pstSrcDirection->enHScan = TDE_SCAN_RIGHT_LEFT;
                pstDstDirection->enHScan = TDE_SCAN_RIGHT_LEFT;
            }
        }
        #endif
        enMirror = pstOpt->enMirror;
    }

    if (enMirror && bFilter)
    {
        TDE_TRACE(TDE_KERN_ERR, "Could not support VF/FF/HF and Mirror\n!");
        return -1;
    }
#if 0
    /* 设置默认扫描方向, YC422R输出时从右向左扫描,否则从左到右扫描 */
    if (TDE2_COLOR_FMT_YCbCr422 == pstDst->enColorFmt)
    {
        pstSrcDirection->enHScan = TDE_SCAN_RIGHT_LEFT;
        pstDstDirection->enHScan = TDE_SCAN_RIGHT_LEFT;
    }
    else
    {
        pstSrcDirection->enHScan = TDE_SCAN_LEFT_RIGHT;
        pstDstDirection->enHScan = TDE_SCAN_LEFT_RIGHT;
    }
#endif

    if (bFilter) /* 如果使用了启用了滤波,则使用默认扫描方向 */
    {
        return 0;
    }

    if (TDE2_MIRROR_NONE != enMirror)
    {
        TDE_CHANGE_DIR_BY_MIRROR(pstSrcDirection, enMirror);
    }
    else
    {
        /* 只有在stride相同的情况下才能做转换 */
        if (pSrc->u32Stride != pstDst->u32Stride)
        {
            return 0;
        }

        s32SrcdBpp = TdeOsiGetbppByFmt(pSrc->enColorFmt);
        s32DstBpp = TdeOsiGetbppByFmt(pstDst->enColorFmt);

        if ((s32DstBpp < 0) || (s32SrcdBpp < 0))
        {
            TDE_TRACE(TDE_KERN_ERR, "bits per pixel less than 0!\n");
            return -1;
        }

        u32SrcAddr = pSrc->u32PhyAddr + pstSrcRect->s32Ypos * pSrc->u32Stride
                     + ((pstSrcRect->s32Xpos * s32SrcdBpp) >> 3);
        u32DstAddr = pstDst->u32PhyAddr + pstDstRect->s32Ypos * pstDst->u32Stride \
                     + ((pstDstRect->s32Xpos * s32DstBpp) >> 3);

        /* 源在目标的上方或同一方向的左边 */
        if (u32SrcAddr < u32DstAddr)
        {
            u32AddrDiff = u32DstAddr - u32SrcAddr;

            /* 源在目标的上方 */
            if (u32AddrDiff > pSrc->u32Stride)
            {
                pstSrcDirection->enVScan = TDE_SCAN_DOWN_UP;
                pstDstDirection->enVScan = TDE_SCAN_DOWN_UP;
            }
            else     /* 源在目标的同一方向的左边 */
            {
                pstSrcDirection->enHScan = TDE_SCAN_RIGHT_LEFT;
                pstDstDirection->enHScan = TDE_SCAN_RIGHT_LEFT;
            }
        }
    }

    return 0;
}
#ifndef HIGO_CODE_CUT
/*****************************************************************************
* Function:      TdeOsiGetInterRect
* Description:   获取两个矩形的公共区域
* Input:         pRect1  输入矩形1
                 pRect2  输入矩形2
* Output:        pInterRect 输出公共矩形
* Return:        0  有公共区域
                 -1 无公共区域
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiGetInterRect(TDE2_RECT_S *pRect1, TDE2_RECT_S *pRect2, TDE2_RECT_S *pInterRect)
{
    HI_S32 s32Left, s32Top, s32Right, s32Bottom;
    HI_S32 s32Right1, s32Bottom1, s32Right2, s32Bottom2;

    s32Left = (pRect1->s32Xpos > pRect2->s32Xpos) ? pRect1->s32Xpos : pRect2->s32Xpos;
    s32Top = (pRect1->s32Ypos > pRect2->s32Ypos) ? pRect1->s32Ypos : pRect2->s32Ypos;

    s32Right1 = pRect1->s32Xpos + pRect1->u32Width - 1;  /* AI7D02635 */
    s32Right2 = pRect2->s32Xpos + pRect2->u32Width - 1;  /* AI7D02635 */
    s32Right = (s32Right1 > s32Right2) ? s32Right2 : s32Right1;

    s32Bottom1 = pRect1->s32Ypos + pRect1->u32Height - 1; /* AI7D02635 */
    s32Bottom2 = pRect2->s32Ypos + pRect2->u32Height - 1; /* AI7D02635 */
    s32Bottom = (s32Bottom1 > s32Bottom2) ? s32Bottom2 : s32Bottom1;

    if ((s32Left > s32Right) || (s32Top > s32Bottom))
    {
        return -1;
    }

    pInterRect->s32Xpos   = s32Left;
    pInterRect->s32Ypos   = s32Top;
    pInterRect->u32Width  = s32Right - s32Left + 1;
    pInterRect->u32Height = s32Bottom - s32Top + 1;

    return 0;
}

/*****************************************************************************
* Function:      TdeOsiIsRect1InRect2
* Description:   Rect1是否在Rect2内
* Input:         pRect1  输入矩形1
                 pRect2  输入矩形2
* Output:        无
* Return:        1  有公共区域
                 0 无公共区域
* Others:        无
*****************************************************************************/
STATIC  HI_BOOL TdeOsiIsRect1InRect2(TDE2_RECT_S *pRect1, TDE2_RECT_S *pRect2)
{
    HI_S32 s32Right1, s32Bottom1, s32Right2, s32Bottom2;

    s32Right1 = pRect1->s32Xpos + pRect1->u32Width - 1; /* AI7D02635 */
    s32Right2 = pRect2->s32Xpos + pRect2->u32Width - 1; /* AI7D02635 */

    s32Bottom1 = pRect1->s32Ypos + pRect1->u32Height - 1; /* AI7D02635 */
    s32Bottom2 = pRect2->s32Ypos + pRect2->u32Height - 1; /* AI7D02635 */

    if((pRect1->s32Xpos >= pRect2->s32Xpos)
        &&(pRect1->s32Ypos >= pRect2->s32Ypos)
        &&(s32Right1 <= s32Right2)
        &&(s32Bottom1 <= s32Bottom2))
    {
        return HI_TRUE;
    }
    
    return HI_FALSE;
}
#endif
/*****************************************************************************
* Function:      TdeOsiSetMbPara
* Description:   宏块操作配置参数接口
* Input:         s32Handle: 任务句柄
*                pHWNode: 配置节点
*                pstMB:    亮度块信息结构
*                pstMbRect: 宏块位图操作区域
*                pstDst:  目标位图信息结构
*                pstDstRect: 目标位图操作区域
*                pMbOpt:  运算参数设置结构
*                enPicMode: 图像顶场/底场/帧
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiSetMbPara(TDE_HANDLE s32Handle, TDE_HWNode_S* pHWNode,
                                     TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect,
                                     TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect,
                                     TDE2_MBOPT_S* pMbOpt)
{
    TDE_DRV_SURFACE_S stDrvS1;
    TDE_DRV_SURFACE_S stDrvS2;
    TDE_DRV_SURFACE_S stDrvS1Tmp = {0};
    TDE_DRV_SURFACE_S stDrvS2Tmp = {0};
    TDE_DRV_CONV_MODE_CMD_S stConv = {0};
    TDE_DRV_SURFACE_S stDrvDst;
    TDE2_RECT_S stInRect;
#ifndef HIGO_CODE_CUT    
    TDE2_RECT_S stOutRect;
#endif
    HI_U16 u16Code;

    TDE2_RECT_S stAdjFieldRect;
    TDE_DRV_MB_CMD_S stMbCmd;
    HI_S32 s32Ret;
    TDE_SCANDIRECTION_S stScan = {0};    /*宏块模式总是使用上->下,左->右的方式*/
    TDE_FILTER_OPT stFilterOpt = {0};
    TDE_PIC_MODE_E enPicMode = TDE_FRAME_PIC_MODE;
    HI_U32 u32WorkBufNum = 0;
    TDE2_OUTALPHA_FROM_E enAlphaFrom = TDE2_OUTALPHA_FROM_NORM;
    TDE2_CSC_OPT_S stCscOpt = {0};

    /* AI7D02555 */
    if (pMbOpt->bSetOutAlpha)
    {
        enAlphaFrom = TDE2_OUTALPHA_FROM_GLOBALALPHA;
    }

    /*判断是否需要按场计算*/
    if ((TDE2_MB_COLOR_FMT_MP1_YCbCr420MBP == pstMB->enMbFmt)
        || (TDE2_MB_COLOR_FMT_MP2_YCbCr420MBP == pstMB->enMbFmt)
        || (TDE2_MB_COLOR_FMT_MP2_YCbCr420MBI == pstMB->enMbFmt))
    {
        enPicMode = TDE_TOP_FIELD_PIC_MODE;
    }
#if 0
    if((pstDstRect->u32Height == pstMbRect->u32Height)
        &&(pstDstRect->u32Width == pstMbRect->u32Width))
    {
        pMbOpt->enResize = TDE2_MBRESIZE_NONE;
    }
    else if(TDE2_MBRESIZE_NONE == pMbOpt->enResize)
    {
        TDE_UNIFY_RECT(pstMbRect, pstDstRect);
    }
#endif

    /* 设置驱动层需要的目的位图格式 */
    TdeOsiConvertSurface(pstDst, pstDstRect, &stScan, &stDrvDst, NULL);

    /* 调用TdeOsiSingleSrc2GetOptCode获取编码 */
    u16Code = TdeOsiDoubleSrcGetOptCode(TDE2_COLOR_FMT_YCbCr888, TDE2_COLOR_FMT_YCbCr888,
                                        pstDst->enColorFmt);

    TdeOsiGetConvbyCode(u16Code, &stConv);
    /* 如果格式为400MB则直接对亮度作处理 */
    if (TDE2_MB_COLOR_FMT_JPG_YCbCr400MBP == pstMB->enMbFmt)
    {
        /* 将亮度设置驱动层需要的目的位图格式 */
        if (TdeOsiConvertMbSurface(pstMB, pstMbRect, &stDrvS1, HI_NULL, TDE_FRAME_PIC_MODE, HI_FALSE) < 0)
        {
            TDE_TRACE(TDE_KERN_ERR, "TdeOsiConvertMbSurface error!\n");\
            return HI_ERR_TDE_INVALID_PARA;
        }

        /* 只需对亮度作处理 */
        TdeHalNodeInitNd(pHWNode, HI_FALSE);

        /* 前景的大小需要设置为亮度的大小 */
        TdeHalNodeSetSrcMbY(pHWNode, &stDrvS1, TDE_MB_Y_FILTER);
        TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS1, TDE_MB_Y_FILTER);
        TdeHalNodeSetTgt(pHWNode, &stDrvDst, enAlphaFrom);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_Y_OPT, TDE_ALU_NONE, 0);
        stMbCmd.enMbMode = TDE_MB_CONCA_FILTER;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);
        TdeHalNodeSetGlobalAlpha(pHWNode, pMbOpt->u8OutAlpha);

#ifndef HIGO_CODE_CUT
        if ((s32Ret = TdeOsiMbSetClipPara(pstDstRect, pMbOpt, pHWNode)) < 0)
        {
            return s32Ret;
        }
#endif

        TdeHalNodeSetColorConvert(pHWNode, &stConv);
        /* 如果没有作滤波操作,直接完成节点设置 */
        if ((TDE2_MBRESIZE_NONE == pMbOpt->enResize) && (HI_FALSE == pMbOpt->bDeflicker))
        {
            return TdeOsiSetNodeFinish(s32Handle, pHWNode, 0, TDE_NODE_SUBM_ALONE);
        }
        else
        {
            TDE2_DEFLICKER_MODE_E enDeflickerMode = ((pMbOpt->bDeflicker)?(TDE2_DEFLICKER_MODE_RGB):(TDE2_DEFLICKER_MODE_NONE));
            TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS1);
            TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                                  pstMbRect, pstDstRect, HI_FALSE, HI_FALSE, TDE_FRAME_PIC_MODE);
            stFilterOpt.stAdjInfo.enScaleMode = TDE_CHILD_SCALE_MBY;
            return TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, pstDstRect, enDeflickerMode,
                                            &stFilterOpt);
        }
    }

    if (TdeOsiConvertMbSurface(pstMB, pstMbRect, &stDrvS1, &stDrvS2, enPicMode, HI_FALSE) < 0)
    {
        TDE_TRACE(TDE_KERN_ERR, "could not transfer mb paras!\n");
        return HI_ERR_TDE_INVALID_PARA;
    }

    /* 根据是否按场缩放调整宽高 */
    stAdjFieldRect.s32Xpos   = pstMbRect->s32Xpos;
    stAdjFieldRect.s32Ypos   = pstMbRect->s32Ypos;
    stAdjFieldRect.u32Width  = stDrvS1.u32Width;
    stAdjFieldRect.u32Height = stDrvS1.u32Height;

    /* 通过颜色格式和能否获得临时buffer调整缩放质量 */
    s32Ret = TdeOsiAdjQuality(&stDrvS1Tmp, &stDrvS2Tmp, pstMB, pstMbRect, 
                              pstDst, pstDstRect, enPicMode, pMbOpt);
    if (-1 == s32Ret)
    {
        return HI_ERR_TDE_UNSUPPORTED_OPERATION;
    }
    u32WorkBufNum = (HI_U32)s32Ret;
    TDE_TRACE(TDE_KERN_DEBUG, "u32WorkBufNum:%d\n", u32WorkBufNum);

    switch (pMbOpt->enResize)
    {
#ifndef HIGO_CODE_CUT
    case TDE2_MBRESIZE_QUALITY_HIGH:
    {
        TDE2_DEFLICKER_MODE_E enDeflickerMode = ((pMbOpt->bDeflicker)?(TDE2_DEFLICKER_MODE_RGB):(TDE2_DEFLICKER_MODE_NONE));
        TDE_TRACE(TDE_KERN_DEBUG, "High Quality Mb Resize!\n");
        /* pass1. 先作亮度缩放(抗闪烁)*/
        TdeHalNodeInitNd(pHWNode, HI_FALSE);
        TdeHalNodeSetSrcMbY(pHWNode, &stDrvS1, TDE_MB_Y_FILTER);
        TdeHalNodeSetTgt(pHWNode, &stDrvS1Tmp, enAlphaFrom);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_Y_OPT, TDE_ALU_NONE, 0);
        stMbCmd.enMbMode = TDE_MB_Y_FILTER;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);
        TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                              &stAdjFieldRect, pstDstRect, HI_FALSE, HI_FALSE, enPicMode);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS1);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stOutRect, stDrvS1Tmp);
        TdeOsiSetFilterOptAdjInfo(&stDrvS1, &stDrvS1Tmp, &stFilterOpt, TDE_CHILD_SCALE_MBY);
        if ((s32Ret = TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, &stOutRect, enDeflickerMode,
                                          &stFilterOpt)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            TDE_TRACE(TDE_KERN_ERR, "mb high quality pass1 fail\n!");
            return s32Ret;
        }

        /* pass2. 再作色度缩放 */
        TdeHalNodeInitNd(pHWNode, HI_FALSE);

        /* 前景的大小恢复为色度的大小 */
        TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS2, TDE_MB_CbCr_FILTER);
        TdeHalNodeSetTgt(pHWNode, &stDrvS2Tmp, enAlphaFrom);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_C_OPT, TDE_ALU_NONE, 0);
        stMbCmd.enMbMode = TDE_MB_CbCr_FILTER;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);

        /* 计算色度step和offset,
           注意:step的计算需要使用亮度宽高, offset计算需要使用用户初始传入的起始位置 */
        TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                              &stAdjFieldRect, pstDstRect, HI_TRUE, HI_FALSE, enPicMode);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS2);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stOutRect, stDrvS2Tmp);
        TdeOsiSetFilterOptAdjInfo(&stDrvS2, &stDrvS2Tmp, &stFilterOpt, TDE_CHILD_SCALE_MBC);
        if ((s32Ret = TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, &stOutRect, HI_FALSE /*pMbOpt->bDeflicker*/,
                                          &stFilterOpt)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            TDE_TRACE(TDE_KERN_ERR, "mb high quality pass2 fail\n!");
            return s32Ret;
        }

        /* pass3. 亮色合并 */
        TdeHalNodeInitNd(pHWNode, HI_FALSE);
        TdeHalNodeSetColorConvert(pHWNode, &stConv);
        TdeHalNodeSetSrcMbY(pHWNode, &stDrvS1Tmp, TDE_MB_CONCA_FILTER);
        TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS2Tmp, TDE_MB_CONCA_FILTER);
        TdeHalNodeSetTgt(pHWNode, &stDrvDst, enAlphaFrom);
        TdeHalNodeSetGlobalAlpha(pHWNode, pMbOpt->u8OutAlpha);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_2OPT, TDE_ALU_NONE, 0);
        stMbCmd.enMbMode = TDE_MB_CONCA_FILTER;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);
        TdeOsiSetFilterOptAdjInfo(&stDrvS1Tmp, &stDrvDst, &stFilterOpt, TDE_CHILD_SCALE_MB_CONCA_H);

#ifndef HIGO_CODE_CUT
        if ((s32Ret = TdeOsiMbSetClipPara(pstDstRect, pMbOpt, pHWNode)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            return s32Ret;
        }
#endif

        if ((s32Ret = TdeOsiSetNodeFinish(s32Handle, pHWNode, u32WorkBufNum, TDE_NODE_SUBM_ALONE)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            return s32Ret;
        }

        break;
    }
    case TDE2_MBRESIZE_QUALITY_MIDDLE:
    {
        TDE2_DEFLICKER_MODE_E enDeflickerMode = ((pMbOpt->bDeflicker)?(TDE2_DEFLICKER_MODE_RGB):(TDE2_DEFLICKER_MODE_NONE));
        TDE_TRACE(TDE_KERN_DEBUG, "Middle Quality Mb Resize!\n");
        /* pass1. 作色度上采样 */
        TdeHalNodeInitNd(pHWNode, HI_FALSE);
        TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS2, TDE_MB_CbCr_FILTER);
        TdeHalNodeSetTgt(pHWNode, &stDrvS1Tmp, enAlphaFrom);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_C_OPT, TDE_ALU_NONE, 0);
        stMbCmd.enMbMode = TDE_MB_CbCr_FILTER;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);

        /* 计算色度step和offset,
           注意:由于为色度上采样,按照亮度尺寸作缩放,且输入输出为同一尺寸 */
        TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                              &stAdjFieldRect, &stAdjFieldRect, HI_TRUE, HI_TRUE, enPicMode);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS2);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stOutRect, stDrvS1Tmp);
        stFilterOpt.stAdjInfo.enScaleMode = TDE_CHILD_SCALE_MBC;
        TdeOsiSetFilterOptAdjInfo(&stDrvS2, &stDrvS1Tmp, &stFilterOpt, TDE_CHILD_SCALE_MBC);
        if ((s32Ret = TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, &stOutRect, HI_FALSE,
                                          &stFilterOpt)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            TDE_TRACE(TDE_KERN_ERR, "mb middle quality pass1 fail\n!");
            return s32Ret;
        }

        /* pass2. 亮色合并后缩放 */
        TdeHalNodeInitNd(pHWNode, HI_FALSE);
        /* 调用TdeHalNodeSetColorConvert设置编码 */
        TdeHalNodeSetColorConvert(pHWNode, &stConv);
        stDrvS1.enColorFmt = TDE_DRV_COLOR_FMT_YCbCr444MB;
        TdeHalNodeSetSrcMbY(pHWNode, &stDrvS1, TDE_MB_CONCA_FILTER);
        TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS1Tmp, TDE_MB_CONCA_FILTER);
        TdeHalNodeSetTgt(pHWNode, &stDrvDst, enAlphaFrom);
        TdeHalNodeSetGlobalAlpha(pHWNode, pMbOpt->u8OutAlpha);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_2OPT, TDE_ALU_NONE, 0);
        stMbCmd.enMbMode = TDE_MB_CONCA_FILTER;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);

#ifndef HIGO_CODE_CUT
        if ((s32Ret = TdeOsiMbSetClipPara(pstDstRect, pMbOpt, pHWNode)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            return s32Ret;
        }
#endif

        TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                              &stAdjFieldRect, pstDstRect, HI_FALSE, HI_FALSE, TDE_FRAME_PIC_MODE);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS1);
        stFilterOpt.u32WorkBufNum = u32WorkBufNum;
        TdeOsiSetFilterOptAdjInfo(&stDrvS1, &stDrvDst, &stFilterOpt, TDE_CHILD_SCALE_MB_CONCA_M);
        if((s32Ret = TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, pstDstRect, 
                                        enDeflickerMode, &stFilterOpt)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            return s32Ret;
        }
        
        break;
    }
#endif
        case TDE2_MBRESIZE_QUALITY_LOW:
        {
            TDE2_DEFLICKER_MODE_E enDeflickerMode = ((pMbOpt->bDeflicker)?(TDE2_DEFLICKER_MODE_RGB):(TDE2_DEFLICKER_MODE_NONE));
            TDE_TRACE(TDE_KERN_DEBUG, "Low Quality Mb Resize!\n");
            /* pass1. 先作连接再作缩放 */
            TdeHalNodeInitNd(pHWNode, HI_FALSE);
            /* 调用TdeHalNodeSetColorConvert设置编码 */
            TdeHalNodeSetColorConvert(pHWNode, &stConv);
            TdeHalNodeSetCsc(pHWNode, &stCscOpt);
            TdeHalNodeSetSrcMbY(pHWNode, &stDrvS1, TDE_MB_CONCA_FILTER);

            /* 前景的大小需要设置为亮度的大小 */
            TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS2, TDE_MB_CONCA_FILTER);
            TdeHalNodeSetTgt(pHWNode, &stDrvDst, enAlphaFrom);
            TdeHalNodeSetGlobalAlpha(pHWNode, pMbOpt->u8OutAlpha);
            TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_2OPT, TDE_ALU_NONE, 0);
            stMbCmd.enMbMode = TDE_MB_CONCA_FILTER;
            TdeHalNodeSetMbMode(pHWNode, &stMbCmd);

#ifndef HIGO_CODE_CUT
            if ((s32Ret = TdeOsiMbSetClipPara(pstDstRect, pMbOpt, pHWNode)) < 0)
            {
                TdeOsiListPutPhyBuff(u32WorkBufNum);
                return s32Ret;
            }
 #endif
 
            TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                                  &stAdjFieldRect, pstDstRect, HI_FALSE, HI_FALSE, TDE_FRAME_PIC_MODE);
            TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS1);
            TdeOsiSetFilterOptAdjInfo(&stDrvS1, &stDrvDst, &stFilterOpt, TDE_CHILD_SCALE_MB_CONCA_L);
            if((s32Ret = TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, pstDstRect, 
                                            enDeflickerMode, &stFilterOpt)) < 0)
            {
                TdeOsiListPutPhyBuff(u32WorkBufNum);
                return s32Ret;
            }
            
            break;
        }
    default:     /*TDE_MBRESIZE_NONE*/
    {
#if 1
        TDE2_DEFLICKER_MODE_E enDeflickerMode = ((pMbOpt->bDeflicker)?(TDE2_DEFLICKER_MODE_RGB):(TDE2_DEFLICKER_MODE_NONE));
        TDE_TRACE(TDE_KERN_DEBUG, "Mb CUS by Filter!\n");
        TDE_TRACE(TDE_KERN_DEBUG, "Mb CUS by Filter!\n");
        /* 先作上采样,再作连接 */
        TdeHalNodeInitNd(pHWNode, HI_FALSE);
        /* 调用TdeHalNodeSetColorConvert设置编码 */
        TdeHalNodeSetColorConvert(pHWNode, &stConv);
		TdeHalNodeSetCsc(pHWNode, &stCscOpt);
        TdeHalNodeSetSrcMbY(pHWNode, &stDrvS1, TDE_MB_UPSAMP_CONCA);
        TdeHalNodeSetSrcMbCbCr(pHWNode, &stDrvS2, TDE_MB_UPSAMP_CONCA);
        TdeHalNodeSetTgt(pHWNode, &stDrvDst, enAlphaFrom);
        TdeHalNodeSetGlobalAlpha(pHWNode, pMbOpt->u8OutAlpha);
        TdeHalNodeSetBaseOperate(pHWNode, TDE_MB_2OPT, TDE_ALU_CONCA, 0);
        stMbCmd.enMbMode = TDE_MB_UPSAMP_CONCA;
        TdeHalNodeSetMbMode(pHWNode, &stMbCmd);

        #ifndef HIGO_CODE_CUT
        if ((s32Ret = TdeOsiMbSetClipPara(pstDstRect, pMbOpt, pHWNode)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            return s32Ret;
        }
        #endif

        
        TdeOsiCalcMbFilterOpt(&stFilterOpt, pstMB->enMbFmt, TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP, 
                              &stAdjFieldRect, &stAdjFieldRect, HI_TRUE, HI_TRUE, enPicMode);
        TDE_FILLUP_RECT_BY_DRVSURFACE(stInRect, stDrvS2);
        TdeOsiSetFilterOptAdjInfo(&stDrvS1, &stDrvDst, &stFilterOpt, TDE_CHILD_SCALE_MB_CONCA_CUS);
        if((s32Ret = TdeOsiSetFilterChildNode(s32Handle, pHWNode, &stInRect, pstDstRect, 
                                        enDeflickerMode, &stFilterOpt)) < 0)
        {
            TdeOsiListPutPhyBuff(u32WorkBufNum);
            return s32Ret;
        }
#else
	break;
#endif
    }

    }

    return HI_SUCCESS;
}

/*****************************************************************************
* Function:      TdeOsiAdjQuality
* Description:   根据传入的参数配置滤波类型
* Input:         pS1Tmp: 背景临时位图buffer结构
*                pS2Tmp: 前景临时位图buffer结构
*                pstMB:  宏块位图信息
*                pstMbRect: 宏块位图操作区域
*                pstDstRect:  目标位图操作区域
*                pMbOpt:  运算参数设置结构
* Output:        无
* Return:        临时Buffer的数量/ -1失败
* Others:        无
*****************************************************************************/
STATIC  HI_S32 TdeOsiAdjQuality(TDE_DRV_SURFACE_S* pS1Tmp, TDE_DRV_SURFACE_S* pS2Tmp,
                                      TDE2_MB_S* pstMB, TDE2_RECT_S* pstMbRect, 
                                      TDE2_SURFACE_S* pstDst, TDE2_RECT_S* pstDstRect,
                                      TDE_PIC_MODE_E enPicMode, TDE2_MBOPT_S* pMbOpt)
{
    HI_U32 u32WorkBufferNum = 0;
    HI_BOOL bMustUseBuf = HI_FALSE;
#if 0
    /* 如果是YCbCr444则不需要上采样, 直接采用TDE2_MBRESIZE_QUALITY_LOW */
    if (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == pstMB->enMbFmt)
    {
        pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
        return 0;
    }

    /* 由于输出格式为YC422R时不支持分块
       因此, 如果输出颜色格式为YC422R则自动调整为高质量模式 */
    if (TDE2_COLOR_FMT_YCbCr422 == pstDst->enColorFmt)
    {
        pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_HIGH;
    }
#endif
    /* 不需要缩放*/
    if ((TDE2_MBRESIZE_NONE == pMbOpt->enResize)
        ||((pstMbRect->u32Height == pstDstRect->u32Height)
            &&(pstMbRect->u32Width == pstDstRect->u32Width)))
    {
        /* 如果是YCbCr444MB则不需要上采样, 直接采用TDE2_MBRESIZE_QUALITY_LOW */
        if (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == pstMB->enMbFmt)
        {
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
            return 0;
        }
        /* 输入为非YCbCr444MB,输出为YCbCr422R(输出YC422R不支持分块),需要用中质量缩放完成 */
        else if (TDE2_COLOR_FMT_YCbCr422 == pstDst->enColorFmt)
        {
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_HIGH;
            bMustUseBuf = HI_TRUE;
        }
        else
        {
            /* 如果没作缩放,但打开抗闪烁,或者不缩放但使用场模式,则使用中质量滤波 */
            if (pMbOpt->bDeflicker || TDE_FRAME_PIC_MODE != enPicMode)
            {
                pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_MIDDLE;
            }
            else
            {
                /* 如果没作缩放,也没有抗闪烁,则不使用滤波 */
                pMbOpt->enResize = TDE2_MBRESIZE_NONE;
                return 0;
            }
        }
    }
    else /*需要缩放*/
    {
        /* 如果是YCbCr444MB,输出非YC422R则不需要上采样, 直接采用TDE2_MBRESIZE_QUALITY_LOW */
        if (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == pstMB->enMbFmt
            && TDE2_COLOR_FMT_YCbCr422 != pstDst->enColorFmt)
        {
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
            return 0;
        }
        /* 缩放时,输出为YCbCr422R(输出YC422R不支持分块),需要用高质量缩放完成 */
        else if (TDE2_COLOR_FMT_YCbCr422 == pstDst->enColorFmt)
        {
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_HIGH;
            bMustUseBuf = HI_TRUE;
        }
    }

    /* 获取临时位图大小,如果获取失败,则使用低质量缩放 */
    if (TDE2_MBRESIZE_QUALITY_HIGH == pMbOpt->enResize)
    {
        if((pstDstRect->u32Height * pstDstRect->u32Width) > (TDE_MAX_TMPBUFF_HEIGHT*TDE_MAX_TMPBUFF_WIDTH))
        {
            /* 临时buffer内存不够，使用低质量缩放 */
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
            return 0;
        }
        
        pS1Tmp->u32PhyAddr = TdeOsiListGetPhyBuff(TDE_BUFFER_USAGE_Y);
        if (0 == pS1Tmp->u32PhyAddr)
        {
            if (bMustUseBuf)
            {
                TDE_TRACE(TDE_KERN_ERR, "must use buffer, high qulity get buffer fail!\n");
                return -1;
            }
            else
            {
                pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
                return 0;
            }
        }
        else
        {
            /* 只要第一次获取成功,第二次一定会成功 */
            pS2Tmp->u32PhyAddr = TdeOsiListGetPhyBuff(TDE_BUFFER_USAGE_CbCr);
            TDE_ASSERT(HI_NULL != pS2Tmp->u32PhyAddr);
        }

        pS1Tmp->enColorFmt = TDE_DRV_COLOR_FMT_YCbCr444MB;/*高质量缩放结果总是444MB*/
        pS2Tmp->enColorFmt = TDE_DRV_COLOR_FMT_YCbCr444MB;

        /* 高质量滤波后亮色尺寸相同 */
        pS1Tmp->u32Width  = pS2Tmp->u32Width = pstDstRect->u32Width;
        pS1Tmp->u32Pitch  = (pS1Tmp->u32Width + 3) & (0xfffffffc); /*pitch需要按照4字节对齐*/
        pS2Tmp->u32Pitch  = (pS2Tmp->u32Width * 2 + 3) & (0xfffffffc);
        pS1Tmp->u32Height = pS2Tmp->u32Height = pstDstRect->u32Height;
        u32WorkBufferNum = 2;
    }
    else if (TDE2_MBRESIZE_QUALITY_MIDDLE == pMbOpt->enResize)
    {
        if((pstMbRect->u32Height * pstMbRect->u32Width) > (TDE_MAX_TMPBUFF_HEIGHT*TDE_MAX_TMPBUFF_WIDTH))
        {
            /* 临时buffer内存不够，使用低质量缩放 */
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
            return 0;
        }
        pS1Tmp->enColorFmt = TDE_DRV_COLOR_FMT_YCbCr444MB;/*中质量缩放结果总是444MB*/
        pS1Tmp->u32Width  = pstMbRect->u32Width;
        if (TDE_FRAME_PIC_MODE != enPicMode)
        {
            pS1Tmp->u32Height = TDE_ADJ_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height);
        }
        else
        {
            pS1Tmp->u32Height = pstMbRect->u32Height;
        }
        pS1Tmp->u32Pitch   = (pS1Tmp->u32Width * 2 + 3) & (0xfffffffc);/*pitch需要按照4字节对齐*/
        pS1Tmp->u32PhyAddr = TdeOsiListGetPhyBuff(TDE_BUFFER_USAGE_CbCr);
        if (0 == pS1Tmp->u32PhyAddr)
        {
            pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
            return 0;
        }

        u32WorkBufferNum = 1;
    }
    else
    {
        pMbOpt->enResize = TDE2_MBRESIZE_QUALITY_LOW;
    }

    return u32WorkBufferNum;
}

/*****************************************************************************
* Function:      TdeOsiMbCalcHStep
* Description:   计算水平缩放步长
* Input:         u32Wi: 输入位图宽度
*                u32Wo: 输出位图宽度
*                enFmt: 位图格式
*                bCbCr: 计算色度/亮度水平缩放步长
* Output:        无
* Return:        计算后步长,预乘因子:2^12
* Others:        无
*****************************************************************************/
STATIC  HI_U32 TdeOsiMbCalcHStep(HI_U32 u32Wi, HI_U32 u32Wo,
                                       TDE2_MB_COLOR_FMT_E enInFmt, TDE2_MB_COLOR_FMT_E enOutFmt, HI_BOOL bCbCr)
{
    if (1 >= u32Wo)
    {
        return 0;
    }
    if (enInFmt != enOutFmt && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enOutFmt)
    {
        TDE_TRACE(TDE_KERN_ERR, "Can't calc Hstep from format:%d to format:%d\n", enInFmt, enOutFmt);
        //return 0;
    }

    /*计算亮度水平缩放步长,需要对定点化的步长进行四舍五入*/
    if (bCbCr && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == enOutFmt)
    {
        if ((TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP != enInFmt) && (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enInFmt))
        {
            return (((u32Wi - 1) << TDE_FLOAT_BITLEN) / (u32Wo - 1) + 1) >> 1;
        }
    }

    if (bCbCr && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == enInFmt)
    {
        if ((TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP != enOutFmt) && (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enOutFmt))
        {
            return (((u32Wi - 1) << TDE_FLOAT_BITLEN) / (u32Wo - 1) ) << 1;
        }
    }

    return (((u32Wi - 1) << (TDE_FLOAT_BITLEN + 1)) / (u32Wo - 1) + 1) >> 1;
}

/*****************************************************************************
* Function:      TdeOsiMbCalcVStep
* Description:   计算垂直缩放步长
* Input:         u32Hi: 输入位图宽度
*                u32Ho: 输出位图宽度
*                enFmt: 位图格式
*                bCbCr: 计算色度/亮度水平缩放步长
* Output:        无
* Return:        计算后步长,预乘因子:2^12
* Others:        无
*****************************************************************************/
STATIC  HI_U32 TdeOsiMbCalcVStep(HI_U32 u32Hi, HI_U32 u32Ho,
                                       TDE2_MB_COLOR_FMT_E enInFmt, TDE2_MB_COLOR_FMT_E enOutFmt, HI_BOOL bCbCr)
{
    if (1 >= u32Ho)
    {
        return 0;
    }
    if (enInFmt != enOutFmt && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enOutFmt)
    {
        TDE_TRACE(TDE_KERN_ERR, "Can't calc Vstep from format:%d to format:%d\n", enInFmt, enOutFmt);
        //return 0;
    }

    /*计算亮度缩放垂直步长,需要对定点化的步长进行四舍五入*/
    if (bCbCr && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == enOutFmt)
    {
        if ((TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP != enInFmt) && (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enInFmt))
        {
            return (((u32Hi - 1) << TDE_FLOAT_BITLEN) / (u32Ho - 1) + 1) >> 1;  /* 0.5 * step */
        }
    }

    if (bCbCr && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == enInFmt)
    {
        if ((TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP != enOutFmt) && (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enOutFmt))
        {
            return (((u32Hi - 1) << (TDE_FLOAT_BITLEN)) / (u32Ho - 1) ) << 1;  /* 2 * step */
        }
    }

#if 0
	/** deal with codecc **/
    if (bCbCr && TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP == enOutFmt)
    {
        if (TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP == enInFmt)
        {
            return (((u32Hi - 1) << TDE_FLOAT_BITLEN) / (u32Ho - 1) + 1) >> 1;  /* 0.5 * step */
        }
    }
    if (bCbCr && TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP == enOutFmt)
    {
        if ((TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP == enInFmt)
        || (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == enInFmt))
        {
            return (((u32Hi - 1) << (TDE_FLOAT_BITLEN)) / (u32Ho - 1) ) << 1;  /* 2 * step */
        }
    }
#endif
    return (((u32Hi - 1) << (TDE_FLOAT_BITLEN + 1)) / (u32Ho - 1) + 1) >> 1;    /* step */
}

/*****************************************************************************
* Function:      TdeOsiMbCalcHOffset
* Description:   计算垂直缩放步长
* Input:         u32Xi: 输入位图水平起始位置
*                enFmt: 位图格式
*                bCbCr: 是否计算色度的offset
* Output:        无
* Return:        计算后Offset,预乘因子:2^12
* Others:        无
*****************************************************************************/
STATIC  HI_S32 TdeOsiMbCalcHOffset(HI_U32 u32Xi, TDE2_MB_COLOR_FMT_E enFmt, HI_BOOL bCbCr)
{
    if (!bCbCr)
    {
        return 0;
    }

    if ((TDE2_MB_COLOR_FMT_MP1_YCbCr420MBP == enFmt)
        || (TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP == enFmt))
    {
        if ( 1 == (u32Xi & 0x1) )
        {
            return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 2));    /* 0.25 * 2^12 */
        }

        return (HI_S32)((-1) << (TDE_FLOAT_BITLEN - 2));    /* -0.25 * 2^12 */
    }

    if ((TDE2_MB_COLOR_FMT_MP2_YCbCr420MBP == enFmt)
             || (TDE2_MB_COLOR_FMT_MP2_YCbCr420MBI == enFmt)
             || (TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP == enFmt))
    {
        if( 1 == (u32Xi & 0x1))
        {
            return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 * 2^12 */
        }
    }

    return 0;

}

/*****************************************************************************
* Function:      TdeOsiMbCalcVOffset
* Description:   计算垂直缩放步长
* Input:         u32Yi: 输入位图起始高度
*                enFmt: 位图格式
*                enPicMode: 帧图/底场/顶场
*                bCbCr: 是否计算色度的offset
* Output:        无
* Return:        计算后Offset,预乘因子:2^12
* Others:        无
*****************************************************************************/
STATIC  HI_S32 TdeOsiMbCalcVOffset(HI_U32 u32Yi, TDE2_MB_COLOR_FMT_E enFmt,
                                         TDE_PIC_MODE_E enPicMode, HI_BOOL bCbCr)
{
    if (bCbCr)
    {
        if (TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP == enFmt)
        {
            switch (u32Yi & 0x1)
            {
            case 1:
                return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 2));    /* 0.25 * 2^12 */
            default:
                return (HI_S32)((-1) << (TDE_FLOAT_BITLEN - 2));    /* -0.25 * 2^12 */
            }
        }
        else if ((TDE2_MB_COLOR_FMT_MP2_YCbCr420MBI == enFmt)
                || (TDE2_MB_COLOR_FMT_MP1_YCbCr420MBP == enFmt)
                || (TDE2_MB_COLOR_FMT_MP2_YCbCr420MBP == enFmt))
        {
            switch (u32Yi & 0x3)
            {
            case 0:
            {
                if (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode)
                {
                    return (HI_S32)((-5) << (TDE_FLOAT_BITLEN - 3));    /* -0.625 * 2^12 */
                }
                else
                {
                    return (HI_S32)((-1) << (TDE_FLOAT_BITLEN - 3));    /* -0.125 * 2^12 */
                }
            }
            case 1:
            {
                if (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode)
                {
                    return (HI_S32)((-3) << (TDE_FLOAT_BITLEN - 3));    /* -0.375 * 2^12 */
                }
                else
                {
                    return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 3));    /* 0.125 * 2^12 */
                }
            }
            case 2:
            {
                if (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode)
                {
                    return (HI_S32)((-1) << (TDE_FLOAT_BITLEN - 3));    /* -0.125 * 2^12 */
                }
                else
                {
                    return (HI_S32)(3 << (TDE_FLOAT_BITLEN - 3));    /* 0.375 * 2^12 */
                }
            }
            case 3:
            {
                if (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode)
                {
                    return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 3));    /* 0.125 * 2^12 */
                }
                else
                {
                    return (HI_S32)(5 << (TDE_FLOAT_BITLEN - 3));    /* 0.625 * 2^12 */
                }
            }
            default:
                return 0;
            }
        }
        else if (TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP == enFmt)
        {
            switch (u32Yi & 0x1)
            {
            case 1:
                return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 * 2^12 */
            default:
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if ((TDE2_MB_COLOR_FMT_MP2_YCbCr420MBI == enFmt)
            || (TDE2_MB_COLOR_FMT_MP1_YCbCr420MBP == enFmt)
            || (TDE2_MB_COLOR_FMT_MP2_YCbCr420MBP == enFmt))
        {
            switch (u32Yi & 0x3)
            {
            case 0:
            case 2:
            {
                if (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode)
                {
                    return (HI_S32)((-1) << (TDE_FLOAT_BITLEN - 1));    /* -0.5 * 2^12 */
                }
                else
                {
                    return 0;
                }
            }
            case 1:
            case 3:
            {
                if (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode)
                {
                    return 0;
                }
                else
                {
                    return (HI_S32)(1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 * 2^12 */
                }
            }
            default:
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
}

/*****************************************************************************
* Function:      TdeOsiCalcNoLapSlice
* Description:   计算分块没有重叠情况下的数值
* Input:         pu32WFirst: 返回第一块的长度
*                pu32WLast: 返回最后一块的长度
*                u32Xi: 输入位图水平起始坐标
*                u32BmpW: 位图宽度(没有作水平缩放,输入输出宽度一致)
*                u32Bppi: 输入位图每像素位宽
* Output:        无
* Return:        返回分块的个数
* Others:        AI7D02711 改为动态分配
                 AI7D02579 增加对YC422R所需反扫描和最后一点的处理
*****************************************************************************/
STATIC  HI_U32 TdeOsiCalcNoLapSlice(TDE_SLICE_INFO *pSliceInfo, HI_U32 u32MaxNum, HI_U32 u32Xi, HI_U32 u32Xo,
                                          HI_U32 u32BmpW, TDE_FILTER_OPT* pstFilterOpt)
{
#define TDE_GET_STARTX_BY_SCANINFO(hScan, sliceW, x) \
        ((hScan) ? (HI_U32)((x) + (sliceW) - 1) : ((HI_U32)(x)))

    /* HI_U32 u32SliceNum; */
    HI_U32 u32BmpXo = u32Xo;
    HI_U32 u32OverLapPix = (pstFilterOpt->bEvenStartInX && pstFilterOpt->bEvenStartOutX) ? 4 : 2;
    HI_U32 n = 1;
        
    if (TDE_MAX_SLICE_WIDTH >= u32BmpW)
    {
        pSliceInfo[0].u32SliceWi = u32BmpW;
        pSliceInfo[0].u32SliceXi = TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stSrcDire.enHScan, pSliceInfo[0].u32SliceWi, u32Xi);;
        pSliceInfo[0].s32SliceHOfst = pstFilterOpt->s32HOffset;
        pSliceInfo[0].u32SliceWo = u32BmpW;
        pSliceInfo[0].u32SliceXo = TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stDstDire.enHScan, pSliceInfo[0].u32SliceWo, u32Xo);;
        
        pSliceInfo[0].enSliceType = TDE_NO_BLOCK_SLICE_TYPE;
        return 1;
    }
    else
    {
        HI_U32 u32OfstWord;
        /* HI_U32 u32WFirst; */
        /* HI_U32 u32W64SliceNum;*/    /* 不包含第一块 */

        /* 计算起始位置与Word的偏移*/
        u32OfstWord = (u32Xi * pstFilterOpt->u32Bppi % 32) / pstFilterOpt->u32Bppi;
        if (pstFilterOpt->bEvenStartInX)
        {
            u32OfstWord &= (~0x1);
        }

        pSliceInfo[0].enSliceType = TDE_FIRST_BLOCK_SLICE_TYPE;

        pSliceInfo[0].u32SliceWi = TDE_MAX_SLICE_WIDTH - u32OfstWord;
        pSliceInfo[0].u32SliceXi = 
            TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stSrcDire.enHScan, pSliceInfo[0].u32SliceWi, u32Xi);
        pSliceInfo[0].s32SliceHOfst = pstFilterOpt->s32HOffset;
        pSliceInfo[0].u32SliceWo = pSliceInfo[0].u32SliceWi;
        pSliceInfo[0].u32SliceXo = 
            TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stDstDire.enHScan, pSliceInfo[0].u32SliceWo, u32Xo);
        u32Xo += (pstFilterOpt->bBadLastPix) ? (pSliceInfo[0].u32SliceWo - u32OverLapPix) : (pSliceInfo[0].u32SliceWo);
        u32Xi += (pstFilterOpt->bBadLastPix) ? (pSliceInfo[0].u32SliceWi - u32OverLapPix) : (pSliceInfo[0].u32SliceWi);
        
        for (n = 1; n <= u32MaxNum + 1; n++) /* u32MaxNum 保护内存不越界 */
        {
            if ((HI_S32)(u32BmpW - u32Xo + u32BmpXo) <= TDE_MAX_SLICE_WIDTH)
            {
                break;
            }
            pSliceInfo[n].enSliceType = TDE_MID_BLOCK_SLICE_TYPE;
            pSliceInfo[n].u32SliceWi = TDE_MAX_SLICE_WIDTH;
            pSliceInfo[n].u32SliceXi = 
                TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stSrcDire.enHScan, pSliceInfo[n].u32SliceWi, u32Xi);
            pSliceInfo[n].s32SliceHOfst = pstFilterOpt->s32HOffset;
            pSliceInfo[n].u32SliceWo = pSliceInfo[n].u32SliceWi;
            pSliceInfo[n].u32SliceXo = 
                TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stDstDire.enHScan, pSliceInfo[n].u32SliceWo, u32Xo);
            u32Xo += (pstFilterOpt->bBadLastPix) ? (pSliceInfo[n].u32SliceWo - u32OverLapPix) : (pSliceInfo[n].u32SliceWo);
            u32Xi += (pstFilterOpt->bBadLastPix) ? (pSliceInfo[n].u32SliceWi - u32OverLapPix) : (pSliceInfo[n].u32SliceWi);
        }
        
        if ((HI_S32)(u32BmpW - u32Xo + u32BmpXo) > 0)
        {
            /* 最后一块重新计算为剩余的宽度 */
            pSliceInfo[n].enSliceType = TDE_LAST_BLOCK_SLICE_TYPE;
            pSliceInfo[n].u32SliceWi = u32BmpW - u32Xo + u32BmpXo;
            pSliceInfo[n].u32SliceXi = 
                TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stDstDire.enHScan, pSliceInfo[n].u32SliceWi, u32Xi);
            pSliceInfo[n].s32SliceHOfst = pstFilterOpt->s32HOffset;
            pSliceInfo[n].u32SliceWo = pSliceInfo[n].u32SliceWi;
            
            pSliceInfo[n].u32SliceXo = 
                TDE_GET_STARTX_BY_SCANINFO(pstFilterOpt->stDstDire.enHScan, pSliceInfo[n].u32SliceWo, u32Xo);
        }
    }
    return n + 1;
}

/*****************************************************************************
* Function:      TdeOsiCalcOverLapSlice
* Description:   计算分块有重叠情况下的数值
* Input:         pSliceInfo: 得到每块的信息
*                u32BmpXi: 输入位图水平起始位置
*                u32BmpWi: 输入位图宽度
*                u32BmpHStep: 水平步长
*                s32HOffset: 水平偏移
*                u32BmpXo: 输出位图水平起始位置
*                u32BmpWo: 输出位图宽度
*                u32Bppi: 输入位图每像素位宽
* Output:        无
* Return:        返回分块的个数
* Others:        AI7D02711 改为动态分配
*****************************************************************************/
STATIC  HI_U32 TdeOsiCalcOverLapSlice(TDE_SLICE_INFO *pSliceInfo, HI_U32 u32MaxNum, HI_U32 u32BmpXi, HI_U32 u32BmpWi, 
                                            HI_U32 u32BmpXo, HI_U32 u32BmpWo, TDE_FILTER_OPT* pstFilterOpt)
{
    HI_U32 u32Xi = u32BmpXi;
    HI_U32 u32Wi;
    HI_U32 s32HOfst = pstFilterOpt->s32HOffset;
    HI_U32 u32Xo = u32BmpXo;
    HI_U32 u32Wo;
    HI_U32 u32OfstWord = 0;
    HI_U32 u32LeftWi = u32BmpWi;
    HI_U32 u32LeftWo = u32BmpWo;
    HI_U32 u32CalcWi = 0;
    HI_U32 u32CalcWo = 0;
    HI_U32 u32BackPix = (pstFilterOpt->bEvenStartInX) ? 2 : 0; /* u32BackPix在h2版本为2 */
    /* 不对称偏差为0, 否则偏差为0.5 * 2^12 */
    HI_U32 u32HOfstDiff = 0;//(pstFilterOpt->bCoefSym) ? (0) : (1 << (TDE_FLOAT_BITLEN - 1));
    HI_U32 n;

    if (0 == pstFilterOpt->u32HStep)
    {
        pSliceInfo[0].u32SliceXi = u32Xi;
        pSliceInfo[0].u32SliceWi = u32BmpWi;
        pSliceInfo[0].s32SliceHOfst = pstFilterOpt->s32HOffset;
        pSliceInfo[0].u32SliceXo = u32Xo;
        pSliceInfo[0].u32SliceWo = u32BmpWo;
        pSliceInfo[0].enSliceType = TDE_NO_BLOCK_SLICE_TYPE;
        return 1;
    }

    /* u32MaxNum: 保护内存不越界 */
    for (n = 0; n < u32MaxNum; n++) /*AI7D02711*/
    {
        /* step1. 由Xi, HOfst, Xo计算得到Wi, Wo */
        if (TDE_MAX_SLICE_WIDTH >= u32LeftWi)
        {
            u32Wi = u32LeftWi;
        }
        else
        {
            /* 计算起始位置与Word的偏移*/
            u32OfstWord = (u32Xi * pstFilterOpt->u32Bppi % 32) / pstFilterOpt->u32Bppi;
            u32Wi = TDE_MAX_SLICE_WIDTH - u32OfstWord;
        }

        if (0 > (HI_S32)((u32Wi - 5 - u32BackPix) * TDE_NO_SCALE_STEP - s32HOfst - u32HOfstDiff))
        {
            u32Wo = u32LeftWo;
        }
        else
        {
            if (TDE_MAX_SLICE_WIDTH >= u32LeftWi)
            {
                u32Wo = u32LeftWo;
            }
            else
            {
                u32Wo = ((u32Wi - 5 - u32BackPix) * TDE_NO_SCALE_STEP - s32HOfst - u32HOfstDiff) / pstFilterOpt->u32HStep + 1;
                /* 如果输出需要降采样时,需要保证输出为偶数 */
                u32Wo = (pstFilterOpt->bEvenStartOutX) ? (u32Wo & (~0x1)) : (u32Wo);
            }
        }

        if (u32Wo > u32LeftWo)
        {
            u32Wo = u32LeftWo;
        }
/*
        if (pstFilterOpt->bEvenStartInX)
        {
            u32CalcWi = u32Wi;
        }
        else
*/
        {
            /* 输出Wo的数值需要计算准确的Wi的值, 遗留: 需要分析中间块的CalcWi是否会超过64 */
            u32CalcWi = ((s32HOfst + u32HOfstDiff + pstFilterOpt->u32HStep*(u32Wo - 1)) >> TDE_FLOAT_BITLEN) + 5;
        }

        /* 保护判断,输出W不超出位图W */
        if (u32CalcWi > u32LeftWi)
        {
            u32CalcWi = u32LeftWi;
        }

        /* step2. 得到第n组系数: Xi, Wi, HOfst, Xo, Wo */
        pSliceInfo[n].s32SliceHOfst = s32HOfst;
        pSliceInfo[n].u32SliceWi = (pstFilterOpt->bEvenStartInX) ? ((u32CalcWi + 3) & (~0x1)) : (u32CalcWi);
        pSliceInfo[n].u32SliceWo = u32Wo;
        pSliceInfo[n].u32SliceXi = u32Xi;
        pSliceInfo[n].u32SliceXo = u32Xo;
        pSliceInfo[n].enSliceType = TDE_MID_BLOCK_SLICE_TYPE;

        /* 如果剩余宽度为0, break */
        if (((u32BmpXi + u32BmpWi) <= (u32Xi + u32CalcWi/*u32Wi*/))
            || ((u32BmpXo + u32BmpWo) <= (u32Xo + u32Wo)))
        {
            n++; /*AI7D02711*/
            break;
        }

        /* step3. 根据上一块的系数更新下一块的Xi, HOfst, Xo */
        u32CalcWo = (pstFilterOpt->bEvenStartOutX) ? (u32Wo - 2) : u32Wo;
        u32Xi = ((s32HOfst + pstFilterOpt->u32HStep * u32CalcWo) >> TDE_FLOAT_BITLEN) - 3 + u32Xi;
        s32HOfst = ((s32HOfst + pstFilterOpt->u32HStep * u32CalcWo) & 0x0fff) + 3 * TDE_NO_SCALE_STEP;
        
        if (pstFilterOpt->bEvenStartInX && (u32Xi & 0x1))
        {
            u32Xi -= 1;
            s32HOfst += TDE_NO_SCALE_STEP;
        }

        /* 有下采样时, 由于Xo为偶数, CalcWo也调整为偶数,因此, Xo不需要调整直接使用 */
        u32Xo = u32Xo + u32CalcWo;

        /* 更新LeftWi、u32LeftWo */
        u32LeftWi = u32BmpXi + u32BmpWi - u32Xi;
        u32LeftWo = u32BmpXo + u32BmpWo - u32Xo;
    }
    pSliceInfo[0].enSliceType = TDE_FIRST_BLOCK_SLICE_TYPE;
    pSliceInfo[n-1].enSliceType = TDE_LAST_BLOCK_SLICE_TYPE;
    if (n == 1)
    {
        pSliceInfo[0].enSliceType = TDE_NO_BLOCK_SLICE_TYPE;
    }

    return n;
}

/*****************************************************************************
* Function:      TdeOsiSetFilterChildNode
* Description:   计算分块的子节点并加到任务链表中
* Input:         s32Handle: 表示任务的链表句柄
*                pNode: 节点配置参数
*                pInRect: 输入位图区域
*                pOutRect: 输出位图区域
*                bDeflicker: 是否抗闪烁
*                pstFilterOpt: 滤波配置参数
* Output:        无
* Return:        返回分块的个数
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiSetFilterChildNode(TDE_HANDLE s32Handle, TDE_HWNode_S* pNode, TDE2_RECT_S* pInRect,
                                       TDE2_RECT_S*  pOutRect,
                                       TDE2_DEFLICKER_MODE_E enDeflickerMode,
                                       TDE_FILTER_OPT* pstFilterOpt)
{
    TDE_SLICE_INFO* sliceInfo = HI_NULL;
    TDE_CHILD_INFO stChildInfo = {0};
    HI_U32 u32SliceNum = 1;
    HI_BOOL bDeflicker = (TDE2_DEFLICKER_MODE_NONE == enDeflickerMode)?HI_FALSE:HI_TRUE;
    HI_U32 u32MaxSliceNum = 
           TDE_CALC_MAX_SLICE_NUM(bDeflicker, pstFilterOpt->u32VStep, pInRect->u32Width);
    HI_U32 u32FirstNum;
    HI_S32 s32Ret;
    HI_S32 i;
    HI_U32 u32TDE_CLIP_START = pNode->u32TDE_CLIP_START;
    HI_U32 u32TDE_CLIP_STOP = pNode->u32TDE_CLIP_STOP;

    /*AI7D02711 beg*/
    sliceInfo = TDE_MALLOC(u32MaxSliceNum * sizeof(TDE_SLICE_INFO));
    TDE_TRACE(TDE_KERN_DEBUG, "slice calc u32MaxSliceNum: %d!\n", u32MaxSliceNum);

    if (HI_NULL == sliceInfo)
    {
        return HI_ERR_TDE_NO_MEM;
    }

    memset(sliceInfo, 0, u32MaxSliceNum * sizeof(TDE_SLICE_INFO));
    /*AI7D02711 end*/

    /* 设置子节点缩放的模式 */
    memcpy(&stChildInfo.stAdjInfo, &pstFilterOpt->stAdjInfo, sizeof(TDE_MBSTART_ADJ_INFO_S));
    memcpy(&stChildInfo.stDSAdjInfo, &pstFilterOpt->stDSAdjInfo, sizeof(TDE_DOUBLESRC_ADJ_INFO_S));
    /*  u32ChildUpdate :
     * _________________________________________
     * |    |    |    |    |    |    |    |    |
     * | ...| 0  | 0  | 1  | 1  | 1  | 1  |  1 |
     * |____|____|____|____|____|____|____|____|
     *                   |    |    |    |    |
     *                  \/   \/   \/   \/   \/
     *                u32Wo u32Xo HOfst u32Wi u32Xi
     *                u32Ho u32Yo VOfst u32Hi u32Yi
     */

    /* 是否使用分块/如何分块的条件判断 */
    /* 只作水平缩放,不作抗闪烁和垂直缩放时不需要分块 */
    if ((HI_FALSE == bDeflicker)
        && (TDE_NO_SCALE_STEP == pstFilterOpt->u32VStep))
    {
        TDE_TRACE(TDE_KERN_DEBUG, "one slice block for filter!\n");
        u32SliceNum = 1;
        sliceInfo[0].s32SliceHOfst = pstFilterOpt->s32HOffset;
        sliceInfo[0].u32SliceWi = pInRect->u32Width;
        sliceInfo[0].u32SliceWo = pOutRect->u32Width;
        sliceInfo[0].u32SliceXi = pInRect->s32Xpos;
        sliceInfo[0].u32SliceXo = pOutRect->s32Xpos;
        sliceInfo[0].enSliceType = TDE_NO_BLOCK_SLICE_TYPE;
    }
    /* 不作水平缩放,作抗闪烁或垂直缩放时使用非重叠分块 */
    else if ((TDE_NO_SCALE_STEP == pstFilterOpt->u32HStep) 
             && ((bDeflicker) || (TDE_NO_SCALE_STEP != pstFilterOpt->u32VStep)))
    {
        TDE_TRACE(TDE_KERN_DEBUG, "NoLap slice block for filter!\n");
        u32SliceNum = TdeOsiCalcNoLapSlice(sliceInfo, u32MaxSliceNum, (HI_U32)(pInRect->s32Xpos), 
                                           (HI_U32)(pOutRect->s32Xpos),
                                           pInRect->u32Width, pstFilterOpt);
        stChildInfo.u64Update = 0x1B;

    }
    /* 作水平缩放, 也作垂直缩放或抗闪烁时使用重叠分块 */
    else if ((TDE_NO_SCALE_STEP != pstFilterOpt->u32HStep) 
             && ((bDeflicker) || (TDE_NO_SCALE_STEP != pstFilterOpt->u32VStep)))
    {
        TDE_TRACE(TDE_KERN_DEBUG, "OverLap slice block for filter!\n");
        u32SliceNum = TdeOsiCalcOverLapSlice(sliceInfo, u32MaxSliceNum, pInRect->s32Xpos,
                                             pInRect->u32Width, (HI_U32)pOutRect->s32Xpos, 
                                             pOutRect->u32Width, pstFilterOpt);
        TDE_TRACE(TDE_KERN_DEBUG, "slice real u32SliceNum: %d!\n", u32SliceNum);
        stChildInfo.u64Update = 0x1F;
    }

    /* 配置父节点的滤波参数信息 */
    TdeOsiSetResizePara(pNode, pstFilterOpt, TDE_NODE_SUBM_PARENT);

    if (bDeflicker)
    {
        TdeOsiSetDeflickerPara(pNode, enDeflickerMode, pstFilterOpt);
    }

    /* 如果是水平放大,分块从右到左进行滤波 */
    if ((TDE_SCAN_RIGHT_LEFT == pstFilterOpt->stDstDire.enHScan) || (pInRect->u32Width < pOutRect->u32Width))
    {
        u32FirstNum = u32SliceNum - 1;
    }
    else     /* 否则,分块从左到右进行滤波 */
    {
        u32FirstNum = 0;
    }

    stChildInfo.u32Xi = sliceInfo[u32FirstNum].u32SliceXi;
    stChildInfo.u32Yi = (HI_U32)pInRect->s32Ypos;
    stChildInfo.u32Wi = sliceInfo[u32FirstNum].u32SliceWi;
    stChildInfo.u32Hi = pInRect->u32Height;
    stChildInfo.u32HOfst = sliceInfo[u32FirstNum].s32SliceHOfst;
    stChildInfo.u32VOfst = pstFilterOpt->s32VOffset;
    stChildInfo.u32Xo = sliceInfo[u32FirstNum].u32SliceXo;
    stChildInfo.u32Yo = (HI_U32)pOutRect->s32Ypos;
    stChildInfo.u32Wo = sliceInfo[u32FirstNum].u32SliceWo;
    stChildInfo.u32Ho = pOutRect->u32Height;
    stChildInfo.enSliceType = sliceInfo[u32FirstNum].enSliceType;
    TdeHalNodeAddChild(pNode, &stChildInfo);
    s32Ret = TdeOsiSetNodeFinish(s32Handle, pNode, pstFilterOpt->u32WorkBufNum, TDE_NODE_SUBM_PARENT);
    if (HI_SUCCESS != s32Ret)
    {
        TDE_FREE(sliceInfo);
        return s32Ret;
    }

    /* 根据每块子节点的信息设置寄存器,第一个节点已经在父节点设置,从第2个节点开始配置 */
    if (0 == u32FirstNum)    /*从左到右*/
    {
        for (i = u32FirstNum + 1; i < (HI_S32)u32SliceNum; i++)
        {
            /* AE5D03390:软件规避区域外clip bug */
            TdeHalNodeInitChildNd(pNode,u32TDE_CLIP_START, u32TDE_CLIP_STOP);
            /*配置子节点的滤波参数信息*/
            TdeOsiSetResizePara(pNode, pstFilterOpt, TDE_NODE_SUBM_CHILD);
            stChildInfo.u32Xi = sliceInfo[i].u32SliceXi;
            stChildInfo.u32Yi = (HI_U32)pInRect->s32Ypos;
            stChildInfo.u32Wi = sliceInfo[i].u32SliceWi;
            stChildInfo.u32Hi = pInRect->u32Height;
            stChildInfo.u32HOfst = sliceInfo[i].s32SliceHOfst;
            stChildInfo.u32VOfst = pstFilterOpt->s32VOffset;
            stChildInfo.u32Xo = sliceInfo[i].u32SliceXo;
            stChildInfo.u32Yo = (HI_U32)pOutRect->s32Ypos;
            stChildInfo.u32Wo = sliceInfo[i].u32SliceWo;
            stChildInfo.u32Ho = pOutRect->u32Height;
            stChildInfo.enSliceType = sliceInfo[i].enSliceType;
            TdeHalNodeAddChild(pNode, &stChildInfo);
            s32Ret = TdeOsiSetNodeFinish(s32Handle, pNode, 0, TDE_NODE_SUBM_CHILD);
            if (HI_SUCCESS != s32Ret)
            {
                TDE_FREE(sliceInfo);
                return s32Ret;
            }
        }
    }
    else     /*从右到左*/
    {
        for (i = u32FirstNum - 1; i >= 0; i--)
        {
            /* AE5D03390:软件规避区域外clip bug */
            TdeHalNodeInitChildNd(pNode,u32TDE_CLIP_START, u32TDE_CLIP_STOP);
            TdeOsiSetResizePara(pNode, pstFilterOpt, TDE_NODE_SUBM_CHILD);
            stChildInfo.u32Xi = sliceInfo[i].u32SliceXi;
            stChildInfo.u32Yi = (HI_U32)pInRect->s32Ypos;
            stChildInfo.u32Wi = sliceInfo[i].u32SliceWi;
            stChildInfo.u32Hi = pInRect->u32Height;
            stChildInfo.u32HOfst = sliceInfo[i].s32SliceHOfst;
            stChildInfo.u32VOfst = pstFilterOpt->s32VOffset;
            stChildInfo.u32Xo = sliceInfo[i].u32SliceXo;
            stChildInfo.u32Yo = (HI_U32)pOutRect->s32Ypos;
            stChildInfo.u32Wo = sliceInfo[i].u32SliceWo;
            stChildInfo.u32Ho = pOutRect->u32Height;
            stChildInfo.enSliceType = sliceInfo[i].enSliceType;
            TdeHalNodeAddChild(pNode, &stChildInfo);
            s32Ret = TdeOsiSetNodeFinish(s32Handle, pNode, 0, TDE_NODE_SUBM_CHILD);
            if (HI_SUCCESS != s32Ret)
            {
                TDE_FREE(sliceInfo);
                return s32Ret;
            }
        }
    }

    TDE_FREE(sliceInfo);
    return HI_SUCCESS;
}

typedef struct tagUpdateConfig
{
    HI_S32 ori_in_width; //original image width
    HI_S32 ori_in_height; //original image height 
	HI_S32 zme_out_width; //output full image width
	HI_S32 zme_out_height; //output full image height

	HI_S32 update_instart_w; //the start_x of update area in original image 
	HI_S32 update_instart_h; //the start_y of update area in original image
	HI_S32 update_in_width;  //the width of update area in original image
	HI_S32 update_in_height;  //the height of update area in original image 
}UpdateConfig;

typedef struct tagUpdateInfo
{
    HI_S32 zme_instart_w;  //the start_x of needed readin area in original image 
	HI_S32 zme_instart_h;  //the start_y of needed readin area in original image
	HI_S32 zme_in_width;   //the width of needed readin area in original image
	HI_S32 zme_in_height;  //the height of needed readin area in original image

	HI_S32 zme_outstart_w; //the start_x of needed update area in output image  
	HI_S32 zme_outstart_h; //the start_y of needed update area in output image
	HI_S32 zme_out_width;  //the width of needed update area in output image
	HI_S32 zme_out_height; //the height of needed update area in output image

	HI_S32 zme_hphase; //the start phase of horizontal scale 
	HI_S32 zme_vphase; //the start phase of vertical scale
	HI_S32 def_offsetup; //the up offset of deflicker
	HI_S32 def_offsetdown; //the down offset of deflicker
}UpdateInfo;

#if 0
static void TdeOsiGetHUpdateInfo(UpdateConfig *reg, UpdateInfo *info, int scaler_en)
{
	HI_S32 zme_hinstart=0, zme_hinstop=0;
	HI_S32 zme_houtstart=0, zme_houtstop=0;
	HI_S32 update_hstart=reg->update_instart_w;
	HI_S32 update_hstop=update_hstart+reg->update_in_width-1;
	HI_S32 zme_hphase=0;
    //HI_S32 ratio=(HI_S32)(4096*(reg->ori_in_width-1.0)/(reg->zme_out_width-1.0)+0.5);
    HI_S32 ratio=(HI_S32)(4096*(reg->ori_in_width-1)/(reg->zme_out_width-1)+1/2);
	HI_S32 dratio=4096*(reg->zme_out_width-1)/(reg->ori_in_width-1); 
	//TDE_ASSERT(update_hstart>=0 && update_hstop<reg->ori_in_width);
	TDE_TRACE(TDE_KERN_DEBUG, "update_start:%d, update_hstop:%d, ori_in_width:%d\n", \
	 update_hstart, update_hstop, reg->ori_in_width);

	if(1 != scaler_en)  /*hor_scaler not enable*/
    {
        info->zme_instart_w = reg->update_instart_w;
        info->zme_outstart_w = reg->update_instart_w;
        info->zme_in_width = reg->update_in_width;
        info->zme_out_width = reg->update_in_width;
        info->zme_hphase = 0;

        return;
    }

	//hor_scaler enable
	if(update_hstart>=0 && update_hstart<4) 
	{
        /*update outstretched area exceed left limit bordline*/
		zme_hinstart = 0;
		zme_houtstart = 0;
		zme_hphase = 0;
	}
	else  
	{
        /*update outstretched area didn't exceed the left limit bordline*/
		zme_hinstart = (update_hstart-4)*dratio;
		zme_houtstart = (zme_hinstart%4096)==0 ? (zme_hinstart>>12): ((zme_hinstart>>12)+1);
		zme_hinstart = zme_houtstart*ratio>>12;	
		if(zme_hinstart-3<0)  
		{
            /*the left few point need mirror pixels when scale*/
			zme_hphase = (zme_houtstart*ratio)%4096+zme_hinstart*4096;
			zme_hinstart = 0;
		}
		else 
		{
            /*the left few point not need mirror pixels when scale*/
            zme_hphase = (zme_houtstart*ratio)%4096+3*4096;
			zme_hinstart = zme_hinstart - 3;
		}	
	}

	if( update_hstop>(reg->ori_in_width-4) && update_hstop<reg->ori_in_width)
	{
        /*update outstretched area exceed the right limit bordline*/
		zme_hinstop = reg->ori_in_width - 1;
		zme_houtstop = reg->zme_out_width - 1;
	}
	else 
	{
        /*update outstretched area didn't exceed the right limit bordline*/
		zme_hinstop = (update_hstop+3+1)*dratio;
		zme_houtstop = (zme_hinstop%4096)==0 ? ((zme_hinstop>>12)-1): (zme_hinstop>>12);
		zme_hinstop = zme_houtstop*ratio>>12;
		if(zme_hinstop+4>(reg->ori_in_width-1)) 
		{
            /*the right few point need mirror pixels when scale*/
			zme_hinstop = reg->ori_in_width - 1;
		}
		else
		{
            /*the right few point need mirror pixels when scale*/
			zme_hinstop = zme_hinstop + 4;
		}
	}
				
	info->zme_instart_w = zme_hinstart;
	info->zme_outstart_w = zme_houtstart;
	info->zme_in_width = zme_hinstop - zme_hinstart +1;
	info->zme_out_width = zme_houtstop - zme_houtstart +1;
	info->zme_hphase = zme_hphase;

    return ;
}


static void TdeOsiGetVUpdateInfo(UpdateConfig *reg, UpdateInfo *info, int scaler_en, int deflicker_en)
{
	HI_S32 zme_vinstart=0, zme_vinstop=0;
	HI_S32 zme_voutstart=0, zme_voutstop=0;
	HI_S32 update_vstart=reg->update_instart_h;
	HI_S32 update_vstop=update_vstart+reg->update_in_height-1;
	HI_S32 zme_vphase=0;
	//HI_S32 ratio=(HI_S32)(4096*(reg->ori_in_height-1.0)/(reg->zme_out_height-1.0)+0.5);
	HI_S32 ratio=(HI_S32)(4096*(reg->ori_in_height-1)/(reg->zme_out_height-1)+1/2);
	HI_S32 dratio=4096*(reg->zme_out_height-1)/(reg->ori_in_height-1);
	//TDE_ASSERT(update_vstart>=0 && update_vstop<reg->ori_in_height);
	TDE_TRACE(TDE_KERN_DEBUG, "update_vstart:%d, update_vstop:%d, ori_in_height:%d, ratio:%d，dratio:%d\n",\
	update_vstart, update_vstop, reg->ori_in_height, ratio, dratio);

	if(scaler_en==0 && deflicker_en==1)
	{
        /*ver_scale not enable & deflicker enable*/
		if(update_vstart<2)
		{
            /*the update outstreatched area exceed the up limit bordline*/
			zme_vinstart = 0;
			zme_voutstart = 0;
			info->def_offsetup = 0;
		}
		else
		{
            /*the update outstreatched area didn't exceed the up limit bordline*/
			zme_vinstart = update_vstart - 2;
			zme_voutstart = reg->update_instart_h -1;
			info->def_offsetup = 1;
		}
		
		if(update_vstop>(reg->ori_in_height-3))
		{
            /*the update outstreatched area exceed the down limit bordline*/
            zme_vinstop = reg->ori_in_height - 1;
			zme_voutstop = reg->ori_in_height - 1; 
			info->def_offsetdown = 0;
		}
		else
		{
            /*the update outstreatched area didn't exceed the down limit bordline*/
			zme_vinstop = update_vstop + 2;
			zme_voutstop = zme_vinstop - 1;
			info->def_offsetdown = 1;
		}

		info->zme_in_height = zme_vinstop - zme_vinstart +1;
		info->zme_instart_h = zme_vinstart;		
		info->zme_outstart_h = zme_voutstart;
		info->zme_out_height = zme_voutstop - zme_voutstart + 1;
		info->zme_vphase = 0;

	}
	else if(scaler_en==1 && deflicker_en==0)
	{
        /*ver_scale enable & deflicker not enable*/
		if(update_vstart>=0 && update_vstart<2)
		{
            /*the update outstreatched area exceed the up limit bordline*/
			zme_vinstart = 0;
			zme_voutstart = 0;
			zme_vphase = 0;
		}
		else 
		{
            /*the update outstreatched area didn't exceed the up limit bordline*/
            zme_vinstart = (update_vstart-2)*dratio;
			zme_voutstart = (zme_vinstart%4096)==0 ? (zme_vinstart>>12): ((zme_vinstart>>12)+1);
			zme_vinstart = zme_voutstart*ratio>>12;
			if(zme_vinstart-2<0)
			{
                /*the up few point need mirror pixels when scale*/
				zme_vphase = (zme_voutstart*ratio)%4096+zme_vinstart*4096; 
				zme_vinstart = 0;
			}
			else
			{
                /*the up few point not need mirror pixels when scale*/
				zme_vphase = (zme_voutstart*ratio)%4096+2*4096; 
				zme_vinstart = zme_vinstart - 2;
			}	
		}
		
		if(update_vstop>(reg->ori_in_height-3) && update_vstop<reg->ori_in_height)
		{
            /*the update outstreatched area exceed the down limit bordline*/
			zme_vinstop = reg->ori_in_height - 1;
			zme_voutstop = reg->zme_out_height - 1;
            TDE_TRACE(TDE_KERN_DEBUG, "update_vstop:%d zme_voutstop:%d\n", update_vstop, zme_voutstop);
		}
		else
		{
            /*the update outstreatched area didn't exceed the down limit bordline*/
			zme_vinstop = (update_vstop+2+1)*dratio;
            zme_voutstop = (zme_vinstop%4096)==0 ? (zme_vinstop>>12): (zme_vinstop>>12) + 1; 
            TDE_TRACE(TDE_KERN_DEBUG, "update_vstop:%d zme_voutstop:%d\n", update_vstop, zme_voutstop);
			zme_vinstop = zme_voutstop*ratio>>12;
			if(zme_vinstop+2>(reg->ori_in_height-1))
			{
                /*the down few point need mirror pixels when scale*/
				zme_vinstop = reg->ori_in_height - 1;
			}
			else
			{
                /*the down few point not need mirror pixels when scale*/
				zme_vinstop = zme_vinstop + 2;
			}
            if(zme_voutstop>=reg->zme_out_height)
            {
            //    zme_voutstop = reg->zme_out_height -1;
            }		
		}
				
		info->zme_in_height = zme_vinstop - zme_vinstart +1;
		info->zme_instart_h = zme_vinstart;
        TDE_TRACE(TDE_KERN_DEBUG, "zme_voutstart:%d, zme_voutstop:%d\n", zme_voutstart, zme_voutstop);
		info->zme_outstart_h = zme_voutstart;
		info->zme_out_height = zme_voutstop - zme_voutstart +1;
		info->zme_vphase = zme_vphase;
		info->def_offsetup = 0;
		info->def_offsetdown = 0;
	}
	else if(scaler_en==1 && deflicker_en==1)
	{
        /*ver_scale enable & deflicker enable*/
        if(update_vstart>=0 && update_vstart<=2)
		{
            /*the update outstreatched area exceed the up limit bordline*/
			zme_vinstart = 0;
			zme_voutstart = 0;
			zme_vphase = 0;
			info->def_offsetup = 0;
		}
		else 
		{
            /*the update outstreatched area didn't exceed the up limit bordline*/
            zme_vinstart = (update_vstart-2)*dratio;
			zme_voutstart = ((zme_vinstart%4096)==0 ? (zme_vinstart>>12): ((zme_vinstart>>12)+1)) - 1;
			if(zme_voutstart<=1)
			{
                /*the update outstreatched deflicker area exceed the up limit bordline*/
				zme_vinstart = 0;
				zme_vphase = 0;
				info->def_offsetup = (zme_voutstart==0)?0: 1;
			}
			else
			{
                /*the update outstreatched deflicker area didn't exceed the up limit bordline*/
				zme_vinstart = (zme_voutstart-1)*ratio>>12;
				if(zme_vinstart<2)
				{
                    /*the up few point need mirror pixels when scale*/
					zme_vphase = ( (zme_voutstart-1)*ratio )%4096+zme_vinstart*4096; 
					zme_vinstart = 0;
				}
				else
				{
                    /*the up few point not need mirror pixels when scale*/
					zme_vphase = ( (zme_voutstart-1)*ratio )%4096+2*4096; 
					zme_vinstart = zme_vinstart - 2;
				}
				info->def_offsetup = 1;
			}		
		}
 
		if(update_vstop>(reg->ori_in_height-3) && update_vstop<reg->ori_in_height)
		{
            /*the update outstreatched area exceed the down limit bordline*/
			zme_vinstop = reg->ori_in_height - 1;
			zme_voutstop = reg->zme_out_height - 1;
			info->def_offsetdown = 0;
		}
		else
		{
            /*the update outstreatched area didn't exceed the down limit bordline*/
			zme_vinstop = (update_vstop+2+1)*dratio;
            zme_voutstop = ((zme_vinstop%4096)==0 ? (zme_vinstop>>12): (zme_vinstop>>12)) + 2; 
		    if(zme_voutstop>(reg->zme_out_height-3))
			{
                /*the update outstreatched deflicker area exceed the down limit bordline*/
				zme_vinstop = reg->ori_in_height - 1;
				info->def_offsetdown = (zme_voutstop>=(reg->zme_out_height-1))?0: 1;
			}
			else
			{
				zme_vinstop = (zme_voutstop+1)*ratio>>12;
				zme_vinstop = (zme_vinstop>(reg->ori_in_height-3))?(reg->ori_in_height-1): (zme_vinstop + 2);
			    info->def_offsetdown = 1;
			}

            if(zme_voutstop>=reg->zme_out_height)
            {
                zme_voutstop = reg->zme_out_height -1;
            }	
		}

				
		info->zme_instart_h = zme_vinstart;		
		info->zme_outstart_h = zme_voutstart;
		info->zme_in_height = zme_vinstop - zme_vinstart +1;
		info->zme_out_height = zme_voutstop - zme_voutstart +1;
		info->zme_vphase = zme_vphase;
	}
	else
	{
		info->zme_instart_h = reg->update_instart_h;
		info->zme_in_height = reg->update_in_height;
		info->zme_outstart_h = reg->update_instart_h;
		info->zme_out_height = reg->update_in_height;
		info->zme_vphase = 0;
		info->def_offsetup = 0;
		info->def_offsetdown = 0;
	}
	
}
#endif

/*****************************************************************************
* Function:      TdeOsiSetFilterNode
* Description:   进行滤波操作(包括VF/HF/FF)
* Input:         s32Handle: 需要操作的Job的头节点指针
*                pNode: 配置父节点的滤波参数信息
*                pInSurface: 输入位图信息
*                pOutSurface: 输出位图信息
*                bDeflicker: 是否作抗闪烁
*                pstOpt: 滤波操作所需配置选项
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiSetFilterNode(TDE_HANDLE s32Handle, TDE_HWNode_S* pNode, TDE2_SURFACE_S *pstForeGround, TDE2_SURFACE_S *pstDst, 
                                  TDE2_RECT_S* pInRect, TDE2_RECT_S*  pOutRect, TDE2_DEFLICKER_MODE_E enDeflickerMode, TDE_FILTER_OPT *pstFilterOpt)
{
    TDE2_COLOR_FMT_E enInFmt;
    TDE2_COLOR_FMT_E enOutFmt;

    //UpdateConfig reg;
    //UpdateInfo info;

    //TDE2_RECT_S stUpdateInRect;
    //TDE2_RECT_S stUpdateOutRect;

    //HI_BOOL bDeflicker;
    //HI_BOOL bScale = HI_FALSE;
    
    enInFmt = pstForeGround->enColorFmt;
    enOutFmt = pstDst->enColorFmt;
    //bDeflicker = (TDE2_DEFLICKER_MODE_NONE == enDeflickerMode)?HI_FALSE:HI_TRUE;
    
    /* 计算垂直/水平步长和垂直水平offset */
    if (1 >= pOutRect->u32Width)
    {
        pstFilterOpt->u32HStep = 0;
    }
    else
    {
        pstFilterOpt->u32HStep = ((pInRect->u32Width - 1) << TDE_FLOAT_BITLEN) / (pOutRect->u32Width - 1);
    }

    if (1 >= pOutRect->u32Height)
    {
        pstFilterOpt->u32VStep = 0;
    }
    else
    {
        pstFilterOpt->u32VStep = ((pInRect->u32Height - 1) << TDE_FLOAT_BITLEN) / (pOutRect->u32Height - 1);
    }

    pstFilterOpt->s32HOffset = 0;
    pstFilterOpt->s32VOffset = 0;
    pstFilterOpt->stAdjInfo.enScaleMode = TDE_CHILD_SCALE_NORM;
    pstFilterOpt->u32Bppi = TdeOsiGetbppByFmt(enInFmt);
    if (TDE2_COLOR_FMT_YCbCr422 == enInFmt || TDE2_COLOR_FMT_YCbCr422 == enOutFmt)
    {
        pstFilterOpt->bEvenStartInX = HI_TRUE; /* YCbCr422要求每块起始和宽度为偶数 */
        pstFilterOpt->bBadLastPix = HI_TRUE;  /* YCbCr422要求分块时每块覆盖2个无效像素点 */
    }
    if (TDE2_COLOR_FMT_YCbCr422 == enOutFmt)
    {
        pstFilterOpt->bEvenStartOutX = HI_TRUE;
        pstFilterOpt->bBadLastPix = HI_TRUE;   /* YCbCr422要求分块时每块覆盖2个无效像素点 */
    }


    /* 判断中值滤波是否使能,使能方式由算法组提供 */
    if (TDE_NO_SCALE_STEP > pstFilterOpt->u32VStep)
    {
        pstFilterOpt->bVRing = HI_TRUE;
    }

    if (TDE_NO_SCALE_STEP > pstFilterOpt->u32HStep)
    {
        pstFilterOpt->bHRing = HI_TRUE;
    }

    pstFilterOpt->bCoefSym = HI_TRUE; /* 算法提供场景,始终打开不对称 */

#if 0

    reg.ori_in_height = pstForeGround->u32Height;
    reg.ori_in_width = pstForeGround->u32Width;
    reg.zme_out_height = pstDst->u32Height;
    reg.zme_out_width = pstDst->u32Width;
    reg.update_instart_w = pInRect->s32Xpos;
    reg.update_instart_h = pInRect->s32Ypos;
    reg.update_in_width = pInRect->u32Width;
    reg.update_in_height = pInRect->u32Height;
    
    TDE_TRACE(TDE_KERN_DEBUG, "InHeight:%d, InWidth:%d, OutHeight:%d, OutWidth:%d,UpdateX:%d, UpdateY:%d,\
        UpdateW:%d, UpdateH:%d\n", reg.ori_in_height, reg.ori_in_width, reg.zme_out_height, reg.zme_out_width,\
        reg.update_instart_w, reg.update_instart_h, reg.update_in_width, reg.update_in_height);
    /*局部抗闪烁*/

	/** deal with codecc,s_bRegionDeflicker not set true **/

    if (((pstForeGround->u32Width != pInRect->u32Width) || (pstForeGround->u32Height != pInRect->u32Height))
        && s_bRegionDeflicker)
    {
        if (1 >= pstDst->u32Width)
        {
            pstFilterOpt->u32HStep = 0;
        }
        else
        {
            pstFilterOpt->u32HStep = ((pstForeGround->u32Width - 1) << TDE_FLOAT_BITLEN) / (pstDst->u32Width - 1);
        }

        if (1 >= pstDst->u32Height)
        {
            pstFilterOpt->u32VStep = 0;
        }
        else
        {
            pstFilterOpt->u32VStep = ((pstForeGround->u32Height - 1) << TDE_FLOAT_BITLEN) / (pstDst->u32Height - 1);
        }

        if (TDE_NO_SCALE_STEP > pstFilterOpt->u32VStep)
        {
            pstFilterOpt->bVRing = HI_TRUE;
        }

        if (TDE_NO_SCALE_STEP > pstFilterOpt->u32HStep)
        {
            pstFilterOpt->bHRing = HI_TRUE;
        }

        if (TDE_NO_SCALE_STEP != pstFilterOpt->u32HStep)
        {
            bScale = HI_TRUE;
        }
        
        TDE_TRACE(TDE_KERN_DEBUG, "bHScale:%x\n", bScale);
        TdeOsiGetHUpdateInfo(&reg, &info, bScale);

        bScale = HI_FALSE;
        if (TDE_NO_SCALE_STEP != pstFilterOpt->u32VStep)
        {
            bScale = HI_TRUE;
        }
        TDE_TRACE(TDE_KERN_DEBUG, "bVScale:%x\n", bScale);
        TdeOsiGetVUpdateInfo(&reg, &info, bScale, bDeflicker);
        TDE_TRACE(TDE_KERN_DEBUG, "zme_instart_w:%d, zme_instart_h:%d, zme_in_width:%d, \
            zme_in_height:%d, zme_outstart_w:%d, zme_outstart_h:%d, zme_out_width:%d, \
            zme_out_height:%d, zme_hphase:%d, zme_vphase:%d, def_offsetup:%d, def_offsetdown:%d\n",
            info.zme_instart_w, info.zme_instart_h, info.zme_in_width, info.zme_in_height, \
            info.zme_outstart_w, info.zme_outstart_h, info.zme_out_width, info.zme_out_height, \
            info.zme_hphase, info.zme_vphase, info.def_offsetup, info.def_offsetdown);

        stUpdateInRect.s32Xpos = info.zme_instart_w;
        stUpdateInRect.s32Ypos = info.zme_instart_h;
        stUpdateInRect.u32Width = info.zme_in_width;
        stUpdateInRect.u32Height = info.zme_in_height;

        stUpdateOutRect.s32Xpos = info.zme_outstart_w;
        stUpdateOutRect.s32Ypos = info.zme_outstart_h;
        stUpdateOutRect.u32Width = info.zme_out_width;
        stUpdateOutRect.u32Height = info.zme_out_height;

        pstFilterOpt->s32HOffset = info.zme_hphase;
        pstFilterOpt->s32VOffset = info.zme_vphase;
        pstFilterOpt->bFirstLineOut = (info.def_offsetup & 0x1);
        pstFilterOpt->bLastLineOut = (info.def_offsetdown & 0x1);

        return TdeOsiSetFilterChildNode(s32Handle, pNode, &stUpdateInRect, &stUpdateOutRect, enDeflickerMode, pstFilterOpt);
    }
    else
#endif
    {
        return TdeOsiSetFilterChildNode(s32Handle, pNode, pInRect, pOutRect, enDeflickerMode, pstFilterOpt);
    }
    
}

/*****************************************************************************
* Function:      TdeOsiCalcMbFilterOpt
* Description:   宏块操作时计算滤波系数
* Input:         pstFilterOpt: 滤波系数结构
*                enInFmt: 输入位图格式信息
*                pInRect: 输入位图操作区域
*                pOutRect: 输出位图操作区域
*                bCbCr: 是否色度操作
*                bCus:  是否色度上采样
*                enPicMode: 位图操作模式:帧/顶场/底场
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC  HI_VOID TdeOsiCalcMbFilterOpt(TDE_FILTER_OPT* pstFilterOpt, TDE2_MB_COLOR_FMT_E enInFmt, TDE2_MB_COLOR_FMT_E enOutFmt,
                                            TDE2_RECT_S* pInRect, TDE2_RECT_S*  pOutRect, HI_BOOL bCbCr,
                                            HI_BOOL bCus, TDE_PIC_MODE_E enPicMode)
{
    //(HI_VOID)memset((HI_VOID*)pstFilterOpt, 0, sizeof(TDE_FILTER_OPT));

    pstFilterOpt->enFilterMode = TDE_DRV_FILTER_ALL;

    /* 计算垂直/水平步长和垂直水平offset, 亮度step计算需要用亮度宽高 */
    if (bCbCr && bCus)    /* 色度上采样单独计算step */
    {
        switch (enInFmt)
        {
        case TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP:
            pstFilterOpt->u32HStep = (1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 */
            pstFilterOpt->u32VStep = TDE_NO_SCALE_STEP;    /* 1 */
            break;
        case TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP:
            pstFilterOpt->u32HStep = TDE_NO_SCALE_STEP;    /* 1 */
            pstFilterOpt->u32VStep = (1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 */
            break;
        case TDE2_MB_COLOR_FMT_MP1_YCbCr420MBP:
        case TDE2_MB_COLOR_FMT_MP2_YCbCr420MBP:
        case TDE2_MB_COLOR_FMT_MP2_YCbCr420MBI:
        case TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP:
            pstFilterOpt->u32HStep = (1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 */
            pstFilterOpt->u32VStep = (1 << (TDE_FLOAT_BITLEN - 1));    /* 0.5 */
            break;
        default:
            pstFilterOpt->u32HStep = TDE_NO_SCALE_STEP;    /* 1 */
            pstFilterOpt->u32VStep = TDE_NO_SCALE_STEP;    /* 1 */
            break;
        }
    }
    else
    {
        if (pstFilterOpt->b2OptCbCr)
        {
            pstFilterOpt->u32HStep = TdeOsiMbCalcHStep(pInRect->u32Width, pOutRect->u32Width, enInFmt, enOutFmt, HI_FALSE);
            pstFilterOpt->u32VStep = TdeOsiMbCalcVStep(pInRect->u32Height, pOutRect->u32Height, enInFmt, enOutFmt, HI_FALSE);
        }
        else
        {
            pstFilterOpt->u32HStep = TdeOsiMbCalcHStep(pInRect->u32Width, pOutRect->u32Width, enInFmt, enOutFmt, bCbCr);
            pstFilterOpt->u32VStep = TdeOsiMbCalcVStep(pInRect->u32Height, pOutRect->u32Height, enInFmt, enOutFmt, bCbCr);
        }
    }

    if (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP == enOutFmt && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enInFmt)
    {
    pstFilterOpt->s32HOffset = TdeOsiMbCalcHOffset(pInRect->s32Xpos, enInFmt, bCbCr);
    pstFilterOpt->s32VOffset = TdeOsiMbCalcVOffset(pInRect->s32Ypos, enInFmt, enPicMode, bCbCr);
    }
    else if (TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enOutFmt && TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP != enInFmt
             && enOutFmt == enInFmt)
    {
        pstFilterOpt->s32HOffset = 0;
        pstFilterOpt->s32VOffset = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ? 
                                   /*            step / 2         -  0.5  */
                                   ((pstFilterOpt->u32VStep >> 1) - (1 << (TDE_FLOAT_BITLEN - 1))) : (0);
    }
    else
    {
        /* 其他情况不做处理,按照0计算 */
        pstFilterOpt->s32HOffset = 0;
        pstFilterOpt->s32VOffset = 0;
    }
#if 0
    if (bCus && (TDE_FRAME_PIC_MODE == enPicMode) && (1 == (pInRect->s32Ypos & 1)))
    {
        pstFilterOpt->s32VOffset += (pstFilterOpt->u32VStep >> 1);
    }
#endif
    /* 宏块格式色度Bpp为half word, 亮度Bpp为Byte宽度 */
    if (bCbCr)
    {
        pstFilterOpt->u32Bppi = 16;

        /* 判断中值滤波是否使能,使能方式由算法组提供 */
        if (TDE_NO_SCALE_STEP > pstFilterOpt->u32VStep)
        {
            pstFilterOpt->bVRing = HI_TRUE;
        }

        if (TDE_NO_SCALE_STEP > pstFilterOpt->u32HStep)
        {
            pstFilterOpt->bHRing = HI_TRUE;
        }
    }
    else
    {
        pstFilterOpt->u32Bppi = 8;

        /* 判断中值滤波是否使能,使能方式由算法组提供 */
        if (TDE_NO_SCALE_STEP > pstFilterOpt->u32HStep)
        {
            pstFilterOpt->bHRing = HI_TRUE;
        }
    }
    
    pstFilterOpt->bCoefSym = HI_TRUE; /* 算法提供场景,始终打开不对称 */
    pstFilterOpt->enFilterMode = TDE_DRV_FILTER_COLOR;
    TDE_TRACE(TDE_KERN_DEBUG, "\n");
}
#ifndef HIGO_CODE_CUT
/*****************************************************************************
* Function:      TdeOsiAdjPara4YCbCr422R
* Description:   当填充色为YCbCr422R时需要按照word填充
* Input:         pstDst: 目标位图信息结构
*                pstDstRect: 目标操作区域
*                pstFillColor: 填充色
*                
* Output:        无
* Return:        无
* Others:        AI7D02880加入软件填充YCbCr422时按word填充功能
*****************************************************************************/
static HI_VOID TdeOsiAdjPara4YCbCr422R(TDE2_SURFACE_S *pstDst, TDE2_RECT_S *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor)
{
    if (TDE2_COLOR_FMT_YCbCr422 != pstDst->enColorFmt)
    {
        return;
    }

    /* 将格式调整为word格式的位图 */
    pstDst->enColorFmt = TDE2_COLOR_FMT_AYCbCr8888;
    pstDst->bAlphaMax255 = HI_TRUE;
    pstFillColor->enColorFmt = TDE2_COLOR_FMT_AYCbCr8888;

    /* 位图宽度减半 */
    pstDst->u32Width /= 2;

    /* 操作区域起始位置和宽度减半 */
    pstDstRect->u32Width /= 2;
    pstDstRect->s32Xpos /= 2;

    /* 调整填充颜色值 */
    pstFillColor->u32FillColor = TDE_GET_YC422R_FILLVALUE(pstFillColor->u32FillColor);
}
#endif
/*****************************************************************************
* Function:      TdeOsi1SourceFill
* Description:   单源的填充运算，源1为填充色，目标位图为pstDst，支持源1与填充色做ROP或alpha blending到目标位图，不支持镜象、colorkey
*                如果src位图为宏块格式则只能支持单源操作,即只设置pstBackGround或只设置pstForeGround
* Input:         s32Handle: 任务句柄
*                pSrc: 背景位图信息结构
*                pstDst: 前景位图信息结构
*                pstFillColor:  目标位图信息结构
*                pstOpt:  运算参数设置结构
* Output:        无
* Return:        HI_SUCCESS/HI_FAILURE
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsi1SourceFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S *pstDst,
                                TDE2_RECT_S  *pstDstRect, TDE2_FILLCOLOR_S *pstFillColor, TDE2_OPT_S *pstOpt)
{
    TDE_DRV_BASEOPT_MODE_E enBaseMode = {0};
    TDE_DRV_ALU_MODE_E enAluMode = {0};
    TDE_HWNode_S stHWNode = {0};
    TDE_DRV_SURFACE_S stDrvSurface = {0};
    TDE_DRV_COLORFILL_S stDrvColorFill = {0};
    TDE_SCANDIRECTION_S stScanInfo = {0};
    TDE_DRV_OUTALPHA_FROM_E enOutAlphaFrom = TDE2_OUTALPHA_FROM_NORM;

    if ((NULL == pstDst) || (NULL == pstDstRect) || (NULL == pstFillColor))
    {
        TDE_TRACE(TDE_KERN_ERR, "NULL pointer!\n");
        return HI_ERR_TDE_NULL_PTR;
    }

    /* 调用TdeHalNodeInitNd(&stHWNode)初始化节点 */
    TdeHalNodeInitNd(&stHWNode, HI_FALSE);

    //TdeOsiSetExtAlpha(pstDst, NULL, &stHWNode); /* AI7D02681 */

    enAluMode = TDE_ALU_NONE;

    if (NULL == pstOpt)
    {
        if (pstFillColor->enColorFmt == pstDst->enColorFmt)
        {
            enBaseMode = TDE_QUIKE_FILL;
        }
        else
        {
            enBaseMode = TDE_NORM_FILL_1OPT;
        }

        enOutAlphaFrom = TDE2_OUTALPHA_FROM_NORM;
    }
    else
    {
#ifndef HIGO_CODE_CUT
        enBaseMode = TDE_NORM_FILL_1OPT;
        if (TDE2_ALUCMD_ROP == pstOpt->enAluCmd)
        {
            TDE_CHECK_ROPCODE(pstOpt->enRopCode_Color);
            TDE_CHECK_ROPCODE(pstOpt->enRopCode_Alpha);

            enAluMode = TDE_ALU_ROP;

            /* 调用TdeHalNodeSetRop设置ROP */
            TdeHalNodeSetRop(&stHWNode, pstOpt->enRopCode_Color, pstOpt->enRopCode_Alpha);
        }
		/*增加alpha叠加处理分支，解决目的图像不能和fill数据做alpha叠加问题， add by w54723*/
		else if (/*TDE2_ALUCMD_BLEND_PREMUL == pstOpt->enAluCmd || */TDE2_ALUCMD_BLEND == pstOpt->enAluCmd)
	    {
	       /* if (TDE2_ALUCMD_BLEND_PREMUL == pstOpt->enAluCmd)
	        {
	            enAluMode = TDE_ALU_BLEND_SRC2;
	        }
	        else*/
	        {
	            enAluMode = TDE_ALU_BLEND;
	        }
        }
        else if(TDE2_ALUCMD_NONE == pstOpt->enAluCmd)
        {
            if (pstFillColor->enColorFmt == pstDst->enColorFmt)
            {
                enBaseMode = TDE_QUIKE_FILL;
            }
            else
            {
                enBaseMode = TDE_NORM_FILL_1OPT;
            }
        }
        else
        {
            TDE_TRACE(TDE_KERN_ERR, "invalid alu command!\n");
            return HI_ERR_TDE_INVALID_PARA;
        }

        enOutAlphaFrom = pstOpt->enOutAlphaFrom;
        TDE_CHECK_OUTALPHAFROM(enOutAlphaFrom);
        if(TDE2_OUTALPHA_FROM_FOREGROUND == enOutAlphaFrom)
        {
            TDE_TRACE(TDE_KERN_ERR, "enOutAlphaFrom error!\n");
            return HI_ERR_TDE_INVALID_PARA;
            
        }

        TdeHalNodeSetGlobalAlpha(&stHWNode, pstOpt->u8GlobalAlpha);
        
        /* 设置clip信息，可能会调整surface大小 */
        if(TdeOsiSetClipPara(NULL, NULL, pstDst, pstDstRect, pstDst, pstDstRect, pstOpt, &stHWNode) < 0)
        {
            return HI_ERR_TDE_CLIP_AREA;
        }
        #endif
    }

    stDrvColorFill.u32FillData = pstFillColor->u32FillColor;
	stDrvColorFill.enDrvColorFmt = g_enTdeCommonDrvColorFmt[pstFillColor->enColorFmt];


    /* 调用TdeHalNodeSetBaseOperate设置基本操作命令 */
    TdeHalNodeSetBaseOperate(&stHWNode, enBaseMode, enAluMode, &stDrvColorFill);

    /* 设置扫描信息 */
    stScanInfo.enHScan = TDE_SCAN_LEFT_RIGHT;
    stScanInfo.enVScan = TDE_SCAN_UP_DOWN;

    /* 转换surface */
    TdeOsiConvertSurface(pstDst, pstDstRect, &stScanInfo, &stDrvSurface, NULL);
#ifndef HIGO_CODE_CUT
    if (TDE_NORM_FILL_1OPT == enBaseMode)
    {
        /* 设置背景信息 */
        TdeHalNodeSetSrc1(&stHWNode, &stDrvSurface);
    }
   #endif
    /* 设置目标信息 */
    TdeHalNodeSetTgt(&stHWNode, &stDrvSurface, enOutAlphaFrom);

	TdeOsiSetExtAlpha(pstDst, NULL, &stHWNode); /* AI7D02681 */
    /* 提交节点 */
    return TdeOsiSetNodeFinish(s32Handle, &stHWNode, 0, TDE_NODE_SUBM_ALONE);
}


/*****************************************************************************
* Function:      TdeOsiCheckYc422RPara
* Description:   由于Yc422R格式有很多限制,统一检查
* Input:         pstSurface: 位图信息
*                pstRect: 位图操作区域
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
static HI_S32 TdeOsiCheckYc422RPara(TDE2_SURFACE_S* pstSrcSurface, TDE2_RECT_S *pstSrcRect, 
                                           TDE2_SURFACE_S* pstDstSurface, TDE2_RECT_S *pstDstRect, HI_BOOL bDeflicker, HI_BOOL bResize)
{
   // printf("src fmt=%d,destfmt=%d\n",pstSrcSurface->enColorFmt,pstDstSurface->enColorFmt );
    /* 输入输出都为YCbCr422 */
    if(TDE2_COLOR_FMT_YCbCr422 == pstSrcSurface->enColorFmt 
       && TDE2_COLOR_FMT_YCbCr422 == pstDstSurface->enColorFmt)
    {
        /* 如果输入和输出都为YCbCr422R时,不能分块 */
        if (bDeflicker || (bResize && pstSrcRect->u32Height != pstDstRect->u32Height))
        {
            return -1;
        }
    }
    /* 输入不为YCbCr422R,输出为YCbCr422R */
    else if (TDE2_COLOR_FMT_YCbCr422 != pstSrcSurface->enColorFmt 
             && TDE2_COLOR_FMT_YCbCr422 == pstDstSurface->enColorFmt)
    {
        /* 如果输出为YCbCr422R时,不能有重叠分块,可以有非重叠分块 */
        if ( (bDeflicker && bResize && pstSrcRect->u32Width != pstDstRect->u32Width)
             || (bResize && pstSrcRect->u32Width != pstDstRect->u32Width && pstSrcRect->u32Height != pstDstRect->u32Height))
        {
            return -1;
        }
    }
    /* 其他情况下都可以一个pass做完 */

    return 0;
}

/*****************************************************************************
* Function:      TdeOsiGetOptCategory
* Description:   分析TDE操作的类型
* Input:         pstBackGround: 背景位图信息
*                pstBackGroundRect: 背景位图操作区域
*                pstForeGround: 前景位图信息
*                pstForeGroundRect: 前景位图操作区域
*                pstDst: 目的位图信息
*                pstDstRect: 目的位图操作区域
*                pstOpt: 操作选项
* Output:        无
* Return:        TDE操作类型
* Others:        无
*****************************************************************************/
STATIC TDE_OPERATION_CATEGORY_E  TdeOsiGetOptCategory(TDE2_SURFACE_S * pstBackGround,
                                                      TDE2_RECT_S *    pstBackGroundRect,
                                                      TDE2_SURFACE_S * pstForeGround,
                                                      TDE2_RECT_S *    pstForeGroundRect,
                                                      TDE2_SURFACE_S * pstDst,
                                                      TDE2_RECT_S *    pstDstRect,
                                                      TDE2_OPT_S *     pstOpt)
{
#ifndef HIGO_CODE_CUT
    TDE2_SURFACE_S *pTmpSrc2;
    TDE2_RECT_S *pTmpSrc2Rect;
#endif
    if ((NULL == pstDst) || (NULL == pstDstRect))
    {
        TDE_TRACE(TDE_KERN_ERR, "\n");
        return TDE_OPERATION_BUTT;
    }

    /* 双源判断 */
    if ((NULL != pstBackGround) && (NULL != pstForeGround))
    {
        if ((NULL == pstBackGroundRect) || (NULL == pstForeGroundRect) || (NULL == pstOpt))
        {
            TDE_TRACE(TDE_KERN_ERR, "\n");
            return TDE_OPERATION_BUTT;
        }

        /* 双源操作时目标操作区域必须和背景操作区域大小一致 */
        if ((pstBackGroundRect->u32Height != pstDstRect->u32Height)
            || (pstBackGroundRect->u32Width != pstDstRect->u32Width))
        {
            TDE_TRACE(TDE_KERN_ERR, "\n");
            return TDE_OPERATION_BUTT;
        }

        if (!pstOpt->bResize)
        {
            /* 高度调整 */
            if (pstBackGroundRect->u32Height != pstForeGroundRect->u32Height)
            {
                pstBackGroundRect->u32Height = TDE_MIN(pstBackGroundRect->u32Height, pstForeGroundRect->u32Height);
                pstDstRect->u32Height = pstBackGroundRect->u32Height;
                pstForeGroundRect->u32Height = pstBackGroundRect->u32Height;
            }

            /* 宽度调整 */
            if (pstBackGroundRect->u32Width != pstForeGroundRect->u32Width)
            {
                pstBackGroundRect->u32Width = TDE_MIN(pstBackGroundRect->u32Width, pstForeGroundRect->u32Width);
                pstDstRect->u32Width = pstBackGroundRect->u32Width;
                pstForeGroundRect->u32Width = pstBackGroundRect->u32Width;
            }
        }

        return TDE_OPERATION_DOUBLE_SRC;
    }
#ifndef HIGO_CODE_CUT
    /* 单源判断开始 */

    if ((NULL != pstBackGround) && (NULL == pstForeGround))
    {
        pTmpSrc2 = pstBackGround;
        pTmpSrc2Rect = pstBackGroundRect;
    }
    else if ((NULL == pstBackGround) && (NULL != pstForeGround))
    {
        pTmpSrc2 = pstForeGround;
        pTmpSrc2Rect = pstForeGroundRect;
    }
    else
    {
        TDE_TRACE(TDE_KERN_ERR, "null pointer in single source 2 operation!");
        return TDE_OPERATION_BUTT;
    }

    if (NULL == pTmpSrc2Rect)
    {
        TDE_TRACE(TDE_KERN_ERR, "\n");
        return TDE_OPERATION_BUTT;
    }

    if ((NULL == pstOpt) || !pstOpt->bResize)
    {
        TDE_UNIFY_RECT(pTmpSrc2Rect, pstDstRect);
    }

    if ((NULL == pstOpt)
        && (pTmpSrc2->enColorFmt == pstDst->enColorFmt))
    {
        return TDE_OPERATION_SINGLE_SRC1;
    }
    
    /* 单源2操作时必须有操作属性 */
    if (NULL == pstOpt)
    {
        TDE_TRACE(TDE_KERN_ERR, "pstOpt can not be NULL in single source 2 operation!\n");
    
        return TDE_OPERATION_BUTT;
    }

    return TDE_OPERATION_SINGLE_SRC2;
#else  
    return TDE_OPERATION_BUTT;
#endif
}

/*****************************************************************************
* Function:      TdeOsiConvertSurface
* Description:   将用户传入的光栅位图信息转换为驱动硬件层需要的位图信息
* Input:         pstSur: 用户传入的光栅位图信息
*                pstRect: 用户传入的光栅位图的操作区域
*                pstScanInfo: 方向扫描信息
*                pstDrvSur: 转换后硬件驱动层需要的位图信息
* Output:        pstOperationArea:根据扫描方向确定的新操作区域
* Return:        无
* Others:        无
*****************************************************************************/
static HI_VOID TdeOsiConvertSurface(TDE2_SURFACE_S *pstSur, TDE2_RECT_S *pstRect,
                                           TDE_SCANDIRECTION_S *pstScanInfo,
                                           TDE_DRV_SURFACE_S *pstDrvSur,
                                           TDE2_RECT_S *pstOperationArea)
{
    pstDrvSur->enColorFmt = g_enTdeCommonDrvColorFmt[pstSur->enColorFmt];

    //TdeOsiConvertFormat(pstSur->enColorFmt, pstDrvSur->enColorFmt);
    pstDrvSur->u32Width  = pstRect->u32Width;
    pstDrvSur->u32Height = pstRect->u32Height;
    pstDrvSur->u32Pitch  = pstSur->u32Stride;
    pstDrvSur->bAlphaMax255 = pstSur->bAlphaMax255;
    pstDrvSur->enHScan = pstScanInfo->enHScan;
    pstDrvSur->enVScan = pstScanInfo->enVScan;
    pstDrvSur->u32PhyAddr = pstSur->u32PhyAddr;

    
    /* 根据扫描方向调整水平起始坐标 */
    if(TDE_SCAN_RIGHT_LEFT == pstScanInfo->enHScan)
    {
        pstDrvSur->u32Xpos = (HI_U32)pstRect->s32Xpos + pstRect->u32Width - 1;
    }
    else
    {
        pstDrvSur->u32Xpos   = (HI_U32)pstRect->s32Xpos;
    }
    
    /* 根据扫描方向调整垂直起始坐标 */
    if(TDE_SCAN_DOWN_UP == pstScanInfo->enVScan)
    {
        pstDrvSur->u32Ypos = (HI_U32)pstRect->s32Ypos + pstRect->u32Height - 1;
    }
    else
    {
        pstDrvSur->u32Ypos   = (HI_U32)pstRect->s32Ypos;
    }

    if(NULL != pstOperationArea)
    {
        /* 缩放滤波模块必须始终用最左边的点 */
        pstOperationArea->s32Xpos = pstRect->s32Xpos;//(HI_S32)pstDrvSur->u32Xpos;
        pstOperationArea->s32Ypos = (HI_S32)pstDrvSur->u32Ypos;
        pstOperationArea->u32Width = pstDrvSur->u32Width;
        pstOperationArea->u32Height = pstDrvSur->u32Height;
    }
    
    return;
}

/*****************************************************************************
* Function:      TdeOsiConvertMbSurface
* Description:   将宏块位图信息转换为驱动硬件层需要的位图信息
* Input:         pstMB: 宏块位图信息
*                pstMbRect: 宏块位图操作区域
*                pstDrvY: 亮度位图信息
*                pstDrvCbCr: 色度位图信息
*                enPicMode: 图像模式:帧/底场/顶场
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiConvertMbSurface(TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect, TDE_DRV_SURFACE_S *pstDrvY,
                                     TDE_DRV_SURFACE_S *pstDrvCbCr, TDE_PIC_MODE_E enPicMode, HI_BOOL bCbCr2Opt)
{
    TDE_DRV_COLOR_FMT_E enAdjColorFmt;

    if ((HI_NULL == pstMB) || (HI_NULL == pstMbRect))
    {
        TDE_TRACE(TDE_KERN_ERR, "null ptr!\n");
        return -1;
    }

    if (HI_NULL != pstDrvY)
    {
        (HI_VOID)memset((HI_VOID*)pstDrvY, 0, sizeof(TDE_DRV_SURFACE_S));
        pstDrvY->enColorFmt = g_enTdeMbDrvColorFmt[pstMB->enMbFmt];
        pstDrvY->u32Width = pstMbRect->u32Width;
        pstDrvY->u32Xpos = (HI_U32)pstMbRect->s32Xpos;
        pstDrvY->u32PhyAddr = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ? 
                              (pstMB->u32YPhyAddr + pstMB->u32YStride) : (pstMB->u32YPhyAddr);
        /* 亮度帧处理模式不需要调整 */
        if (TDE_FRAME_PIC_MODE == enPicMode)
        {
            pstDrvY->u32Height = pstMbRect->u32Height;
            pstDrvY->u32Pitch = pstMB->u32YStride;
            pstDrvY->u32Ypos = (HI_U32)pstMbRect->s32Ypos;
        }
        else     /* 亮度场处理模式需要调整高度和Y的起始位置 */
        {
            pstDrvY->u32Height = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ? 
                TDE_ADJ_B_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height) :
                TDE_ADJ_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height);
            pstDrvY->u32Pitch = pstMB->u32YStride * 2;
            pstDrvY->u32Ypos = ((HI_U32)(pstMbRect->s32Ypos / 2));
        }
    }

    if (HI_NULL == pstDrvCbCr)
    {
        return 0;
    }

    enAdjColorFmt = g_enTdeMbDrvColorFmt[pstMB->enMbFmt];
    (HI_VOID)memset((HI_VOID*)pstDrvCbCr, 0, sizeof(TDE_DRV_SURFACE_S));
    pstDrvCbCr->enColorFmt = g_enTdeMbDrvColorFmt[pstMB->enMbFmt];
    pstDrvCbCr->u32PhyAddr = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ? 
                             (pstMB->u32CbCrPhyAddr + pstMB->u32CbCrStride) : (pstMB->u32CbCrPhyAddr);
#if 0
	/** deal with codecc **/
    if (bCbCr2Opt)
    {
        enAdjColorFmt = TDE_DRV_COLOR_FMT_YCbCr444MB;
    }
#endif

    if (TDE_FRAME_PIC_MODE == enPicMode)
    {
        pstDrvCbCr->u32Pitch = pstMB->u32CbCrStride;

        /* 帧图处理模式下,根据格式计算色度宽高 */
        switch (enAdjColorFmt)
        {
        case TDE_DRV_COLOR_FMT_YCbCr400MBP:
            return -1;
        case TDE_DRV_COLOR_FMT_YCbCr422MBH:
        {
            pstDrvCbCr->u32Xpos  = (HI_U32)pstMbRect->s32Xpos / 2;
            pstDrvCbCr->u32Ypos  = (HI_U32)pstMbRect->s32Ypos;
            pstDrvCbCr->u32Width =
                TDE_ADJ_SIZE_BY_START_P(pstMbRect->s32Xpos, pstMbRect->u32Width);
            pstDrvCbCr->u32Height = pstMbRect->u32Height;
        }
            break;
        case TDE_DRV_COLOR_FMT_YCbCr422MBV:
        {
            pstDrvCbCr->u32Xpos   = (HI_U32)pstMbRect->s32Xpos;
            pstDrvCbCr->u32Ypos   = (HI_U32)pstMbRect->s32Ypos / 2;
            pstDrvCbCr->u32Width  = pstMbRect->u32Width;
            pstDrvCbCr->u32Height =
                TDE_ADJ_SIZE_BY_START_P(pstMbRect->s32Ypos, pstMbRect->u32Height);
        }
            break;
        case TDE_DRV_COLOR_FMT_YCbCr420MB:
        {
            pstDrvCbCr->u32Xpos  = (HI_U32)pstMbRect->s32Xpos / 2;
            pstDrvCbCr->u32Ypos  = (HI_U32)pstMbRect->s32Ypos / 2;
            pstDrvCbCr->u32Width =
                TDE_ADJ_SIZE_BY_START_P(pstMbRect->s32Xpos, pstMbRect->u32Width);
            pstDrvCbCr->u32Height =
                TDE_ADJ_SIZE_BY_START_P(pstMbRect->s32Ypos, pstMbRect->u32Height);
            TDE_TRACE(TDE_KERN_DEBUG, "W:0x%x, H:0x%x\n", pstDrvCbCr->u32Width, 
            pstDrvCbCr->u32Height);    
        }
            break;
        case TDE_DRV_COLOR_FMT_YCbCr444MB:
        {
            pstDrvCbCr->u32Xpos   = (HI_U32)pstMbRect->s32Xpos;
            pstDrvCbCr->u32Ypos   = (HI_U32)pstMbRect->s32Ypos;
            pstDrvCbCr->u32Width  = pstMB->u32YWidth;
            pstDrvCbCr->u32Height = pstMbRect->u32Height;
        }
            break;
        default:
            TDE_TRACE(TDE_KERN_ERR, "Unspport color format!\n");
            return -1;
        }

        return 0;
    }
    
    pstDrvCbCr->u32Pitch = pstMB->u32CbCrStride * 2;

    /* 场图处理模式下,根据格式计算色度宽高 */
    switch (enAdjColorFmt)
    {
    case TDE_DRV_COLOR_FMT_YCbCr400MBP:
        return -1;
    case TDE_DRV_COLOR_FMT_YCbCr422MBH:
    {
        pstDrvCbCr->u32Xpos  = (HI_U32)pstMbRect->s32Xpos / 2;
        pstDrvCbCr->u32Ypos  = ((HI_U32)pstMbRect->s32Ypos / 2);
        pstDrvCbCr->u32Width =
            TDE_ADJ_SIZE_BY_START_P(pstMbRect->s32Xpos, pstMbRect->u32Width);
        pstDrvCbCr->u32Height = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ?
            TDE_ADJ_B_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height) :
            TDE_ADJ_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height);
    }
        break;
    case TDE_DRV_COLOR_FMT_YCbCr422MBV:
    {
        pstDrvCbCr->u32Xpos   = (HI_U32)pstMbRect->s32Xpos;
        pstDrvCbCr->u32Ypos   = ((HI_U32)pstMbRect->s32Ypos / 4);
        pstDrvCbCr->u32Width  = pstMbRect->u32Width;
        pstDrvCbCr->u32Height = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ?
            TDE_ADJ_B_SIZE_BY_START_I(pstMbRect->s32Ypos, pstMbRect->u32Height) :
            TDE_ADJ_SIZE_BY_START_I(pstMbRect->s32Ypos, pstMbRect->u32Height);
    }
        break;
    case TDE_DRV_COLOR_FMT_YCbCr420MB:
    {
        pstDrvCbCr->u32Xpos  = (HI_U32)pstMbRect->s32Xpos / 2;
        pstDrvCbCr->u32Ypos  = ((HI_U32)pstMbRect->s32Ypos / 4);
        pstDrvCbCr->u32Width =
            TDE_ADJ_SIZE_BY_START_P(pstMbRect->s32Xpos, pstMbRect->u32Width);
        pstDrvCbCr->u32Height = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ?
            TDE_ADJ_B_SIZE_BY_START_I(pstMbRect->s32Ypos, pstMbRect->u32Height) :
            TDE_ADJ_SIZE_BY_START_I(pstMbRect->s32Ypos, pstMbRect->u32Height);
        TDE_TRACE(TDE_KERN_DEBUG, "W:0x%x, H:0x%x\n", pstDrvCbCr->u32Width, 
        pstDrvCbCr->u32Height);    
    }
        break;
    case TDE_DRV_COLOR_FMT_YCbCr444MB:
    {
        pstDrvCbCr->u32Xpos   = (HI_U32)pstMbRect->s32Xpos;
        pstDrvCbCr->u32Ypos  = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ?
                               ((HI_U32)(pstMbRect->s32Ypos / 2 + 1)) : ((HI_U32)pstMbRect->s32Ypos / 2);
        pstDrvCbCr->u32Width = pstMB->u32YWidth;
        pstDrvCbCr->u32Height = (TDE_BOTTOM_FIELD_PIC_MODE == enPicMode) ?
            TDE_ADJ_B_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height) :
            TDE_ADJ_FIELD_HEIGHT_BY_START(pstMbRect->s32Ypos, pstMbRect->u32Height);
    }
        break;
    default:
        TDE_TRACE(TDE_KERN_ERR, "Unspport color format!\n");
        return -1;
    }

    return 0;
}

/*****************************************************************************
* Function:      TdeOsiSetClipPara
* Description:   设置Clip裁减区域参数
* Input:         pstBackGround: 背景位图信息
*                pstBGRect: 背景位图操作区域
*                pstForeGround: 前景位图信息
*                pstFGRect: 前景位图操作区域
*                pstDst: 目的位图信息
*                pstDstRect: 目的位图操作信息
*                pstOpt: 操作选项
*                pstHwNode: 硬件操作节点
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeOsiSetClipPara(TDE2_SURFACE_S * pstBackGround, TDE2_RECT_S *pstBGRect,
                                 TDE2_SURFACE_S * pstForeGround,
                                 TDE2_RECT_S *pstFGRect, TDE2_SURFACE_S * pstDst, TDE2_RECT_S *pstDstRect,
                                 TDE2_OPT_S * pstOpt,
                                 TDE_HWNode_S *pstHwNode)
{
#ifndef HIGO_CODE_CUT
    TDE_DRV_CLIP_CMD_S stClip = {0};
    TDE2_RECT_S stInterRect = {0};
    
    TDE_ASSERT(NULL != pstForeGround);
    TDE_ASSERT(NULL != pstDst);
    TDE_ASSERT(NULL != pstOpt);
    TDE_ASSERT(NULL != pstHwNode);

    /* 区域内裁减并且没有缩放 */
    if ((TDE2_CLIPMODE_INSIDE == pstOpt->enClipMode) && (!pstOpt->bResize))
    {
        /* 调用TdeOsiGetInterRect获取目标surface的操作区域和clip区域的公共区域 */
        if (TdeOsiGetInterRect(pstDstRect, &pstOpt->stClipRect, &stInterRect) < 0)
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inrerrect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }

        if (NULL != pstBackGround)
        {
            /* 调整背景的大小 */
            pstBGRect->s32Xpos += stInterRect.s32Xpos - pstDstRect->s32Xpos;
            pstBGRect->s32Ypos  += stInterRect.s32Ypos - pstDstRect->s32Ypos;
            pstBGRect->u32Height = stInterRect.u32Height;
            pstBGRect->u32Width = stInterRect.u32Width;
        }

        /* 调整前景的大小 */
        pstFGRect->s32Xpos += stInterRect.s32Xpos - pstDstRect->s32Xpos;
        pstFGRect->s32Ypos  += stInterRect.s32Ypos - pstDstRect->s32Ypos;
        pstFGRect->u32Height = stInterRect.u32Height;
        pstFGRect->u32Width = stInterRect.u32Width;

        /* 将目标surface的操作区域改为公共区域，去掉clip操作 */
        *pstDstRect = stInterRect;
    }
    else if (TDE2_CLIPMODE_INSIDE == pstOpt->enClipMode)/* 有缩放时区域内裁减，不能优化 */
    {
        /* 调用TdeOsiGetInterRect获取目标surface的操作区域和clip区域的公共区域 */
        if (TdeOsiGetInterRect(pstDstRect, &pstOpt->stClipRect, &stInterRect) < 0)
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inter-rect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }
        
        stClip.bInsideClip   = HI_TRUE ;
        stClip.u16ClipStartX = pstOpt->stClipRect.s32Xpos;
        stClip.u16ClipStartY = pstOpt->stClipRect.s32Ypos;
        stClip.u16ClipEndX = pstOpt->stClipRect.s32Xpos + pstOpt->stClipRect.u32Width - 1;
        stClip.u16ClipEndY = pstOpt->stClipRect.s32Ypos + pstOpt->stClipRect.u32Height - 1;

        /* 调用TdeHalNodeSetClipping设置clip */
        TdeHalNodeSetClipping(pstHwNode, &stClip);
    }
    else if(TDE2_CLIPMODE_OUTSIDE == pstOpt->enClipMode) /* 区域外裁减 */
    {
        if (TdeOsiIsRect1InRect2(pstDstRect, &pstOpt->stClipRect))
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inter-rect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }

        /* 如果目的区域和Clip区域没有公共部分,由于是区域外裁减,不需要作clip操作,直接返回正确 AI7D02798 */
        if (TdeOsiGetInterRect(pstDstRect, &pstOpt->stClipRect, &stInterRect) < 0)
        {
            return 0;
        }

        stClip.bInsideClip   = HI_FALSE;
        stClip.u16ClipStartX = pstOpt->stClipRect.s32Xpos;
        stClip.u16ClipStartY = pstOpt->stClipRect.s32Ypos;
        stClip.u16ClipEndX = pstOpt->stClipRect.s32Xpos + pstOpt->stClipRect.u32Width - 1;
        stClip.u16ClipEndY = pstOpt->stClipRect.s32Ypos + pstOpt->stClipRect.u32Height - 1;

        /* 调用TdeHalNodeSetClipping设置clip */
        TdeHalNodeSetClipping(pstHwNode, &stClip);
    }
    else if(pstOpt->enClipMode >= TDE2_CLIPMODE_BUTT)
    {
        TDE_TRACE(TDE_KERN_ERR, "error clip mode!\n");
        return HI_ERR_TDE_INVALID_PARA;
    }
#endif
    return 0;
}

#if 0
STATIC HI_S32 TdeOsiSetPatternClipPara(TDE2_SURFACE_S * pstBackGround, TDE2_RECT_S *pstBGRect,
                                 TDE2_SURFACE_S * pstForeGround,
                                 TDE2_RECT_S *pstFGRect, TDE2_SURFACE_S * pstDst, TDE2_RECT_S *pstDstRect,
                                 TDE2_PATTERN_FILL_OPT_S * pstOpt,
                                 TDE_HWNode_S *pstHwNode)
{
    TDE_DRV_CLIP_CMD_S stClip;
    TDE2_RECT_S stInterRect;
    
    TDE_ASSERT(NULL != pstForeGround);
    TDE_ASSERT(NULL != pstDst);
    TDE_ASSERT(NULL != pstOpt);
    TDE_ASSERT(NULL != pstHwNode);

    TDE_CHECK_CLIPMODE(pstOpt->enClipMode);
    /* 区域内裁减并且没有缩放 */
    if (TDE2_CLIPMODE_INSIDE == pstOpt->enClipMode)
    {
        /* 调用TdeOsiGetInterRect获取目标surface的操作区域和clip区域的公共区域 */
        if (TdeOsiGetInterRect(pstDstRect, &pstOpt->stClipRect, &stInterRect) < 0)
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inrerrect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }

#if 0
        if (NULL != pstBackGround)
        {
            /* 调整背景的大小 */
            pstBGRect->s32Xpos += stInterRect.s32Xpos - pstDstRect->s32Xpos;
            pstBGRect->s32Ypos  += stInterRect.s32Ypos - pstDstRect->s32Ypos;
            pstBGRect->u32Height = stInterRect.u32Height;
            pstBGRect->u32Width = stInterRect.u32Width;
        }
#if 1
        /* 调整前景的大小 */
        pstFGRect->s32Xpos += stInterRect.s32Xpos - pstDstRect->s32Xpos;
        pstFGRect->s32Ypos  += stInterRect.s32Ypos - pstDstRect->s32Ypos;
        pstFGRect->u32Height = stInterRect.u32Height;
        pstFGRect->u32Width = stInterRect.u32Width;
#endif
        /* 将目标surface的操作区域改为公共区域，去掉clip操作 */
        *pstDstRect = stInterRect;
#endif

#if 1
            stClip.bInsideClip   = HI_TRUE;
            stClip.u16ClipStartX = pstOpt->stClipRect.s32Xpos;
            stClip.u16ClipStartY = pstOpt->stClipRect.s32Ypos;
            stClip.u16ClipEndX = pstOpt->stClipRect.s32Xpos + pstOpt->stClipRect.u32Width - 1;
            stClip.u16ClipEndY = pstOpt->stClipRect.s32Ypos + pstOpt->stClipRect.u32Height - 1;
    
            /* 调用TdeHalNodeSetClipping设置clip */
            TdeHalNodeSetClipping(pstHwNode, &stClip);
#endif            


        
    }
    else if(TDE2_CLIPMODE_OUTSIDE == pstOpt->enClipMode) /* 区域外裁减 */
    {
        if (TdeOsiIsRect1InRect2(pstDstRect, &pstOpt->stClipRect))
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inter-rect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }

        /* 如果目的区域和Clip区域没有公共部分,由于是区域外裁减,不需要作clip操作,直接返回正确 AI7D02798 */
        if (TdeOsiGetInterRect(pstDstRect, &pstOpt->stClipRect, &stInterRect) < 0)
        {
            return 0;
        }

        stClip.bInsideClip   = HI_FALSE;
        stClip.u16ClipStartX = pstOpt->stClipRect.s32Xpos;
        stClip.u16ClipStartY = pstOpt->stClipRect.s32Ypos;
        stClip.u16ClipEndX = pstOpt->stClipRect.s32Xpos + pstOpt->stClipRect.u32Width - 1;
        stClip.u16ClipEndY = pstOpt->stClipRect.s32Ypos + pstOpt->stClipRect.u32Height - 1;

        /* 调用TdeHalNodeSetClipping设置clip */
        TdeHalNodeSetClipping(pstHwNode, &stClip);
    }
    else if(pstOpt->enClipMode >= TDE2_CLIPMODE_BUTT)
    {
        TDE_TRACE(TDE_KERN_ERR, "error clip mode!\n");
        return HI_ERR_TDE_INVALID_PARA;
    }

    return 0;
}
#endif


#ifndef HIGO_CODE_CUT
/*****************************************************************************
* Function:      TdeOsiMbSetClipPara
* Description:   MB操作设置Clip裁减区域参数
* Input:         pstDstRect: 背景位图操作区域
*                pstMbOpt: 配置参数
*                pstHwNode: 硬件操作节点
* Output:        无
* Return:        无
* Others:        注:宏块操作不涉及Clip区域软件优化
*****************************************************************************/
STATIC HI_S32 TdeOsiMbSetClipPara(TDE2_RECT_S * pstDstRect, TDE2_MBOPT_S *pstMbOpt,
                                 TDE_HWNode_S *pstHwNode)
{
    TDE2_RECT_S stInterRect = {0};
    
    TDE_ASSERT(NULL != pstDstRect);
    TDE_ASSERT(NULL != pstMbOpt);
    TDE_ASSERT(NULL != pstHwNode);

    if (TDE2_CLIPMODE_INSIDE == pstMbOpt->enClipMode)
    {
        /* 调用TdeOsiGetInterRect获取目标surface的操作区域和clip区域的公共区域 */
        if (TdeOsiGetInterRect(pstDstRect, &pstMbOpt->stClipRect, &stInterRect) < 0)
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inter-rect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }
        TDE_SET_CLIP(pstHwNode, pstMbOpt);
    }
    else if(TDE2_CLIPMODE_OUTSIDE == pstMbOpt->enClipMode) /* 区域外裁减 */
    {
        if (TdeOsiIsRect1InRect2(pstDstRect, &pstMbOpt->stClipRect))
        {
            TDE_TRACE(TDE_KERN_ERR, "clip and operation area have no inter-rect!\n");
            return HI_ERR_TDE_CLIP_AREA;
        }
        
        TDE_SET_CLIP(pstHwNode, pstMbOpt);
    }
    else if(pstMbOpt->enClipMode >= TDE2_CLIPMODE_BUTT)
    {
        TDE_TRACE(TDE_KERN_ERR, "error clip mode!\n");
        return HI_ERR_TDE_INVALID_PARA;
    }
    return 0;
}
#endif


/*****************************************************************************
 Prototype       : TdeOsiSetExtAlpha
 Description     : 设置ARGB1555格式时的两个alpha值
 Input           : pstBackGround  **
                   pstForeGround  **
                   pstHwNode      **
 Output          : None
 Return Value    : 
 Global Variable   
    Read Only    : 
    Read & Write : 
  History         
  1.Date         : 2008/6/10
    Author       : 可以单个执行的框架
    Modification : Created function

*****************************************************************************/
STATIC  HI_VOID TdeOsiSetExtAlpha(TDE2_SURFACE_S *pstBackGround, TDE2_SURFACE_S *pstForeGround,
                                        TDE_HWNode_S *pstHwNode)
{
    TDE_DRV_SRC_E enSrc = TDE_DRV_SRC_NONE;

    if((NULL != pstForeGround)
        && (pstForeGround->bAlphaExt1555)
        && (TDE2_COLOR_FMT_ARGB1555 == pstForeGround->enColorFmt))
    {
        enSrc |= TDE_DRV_SRC_S2;
    }
    
    if((NULL != pstBackGround)
        && (pstBackGround->bAlphaExt1555)
        && (TDE2_COLOR_FMT_ARGB1555 == pstBackGround->enColorFmt))
    {
        enSrc |= TDE_DRV_SRC_S1;
    }

    /*
      如果 S1 S2都设置了 Alpha0/1,优先以S1为主进行设置;
      其他情况下, S1, S2根据各自参数设置Alpha0/1
    */
    if(enSrc & TDE_DRV_SRC_S1)
    {
        TdeHalNodeSetExpAlpha(pstHwNode, enSrc, pstBackGround->u8Alpha0, pstBackGround->u8Alpha1);
    }
    else if(enSrc & TDE_DRV_SRC_S2)
    {
        TdeHalNodeSetExpAlpha(pstHwNode, enSrc, pstForeGround->u8Alpha0, pstForeGround->u8Alpha1);
    }
}


/*****************************************************************************
* Function:      TdeOsiSetBaseOptParaForBlit
* Description:   设置基本操作类型的封装函数
* Input:         pstOpt: 操作选项
*                enOptCategory: 操作分类
*                pstHwNode: 硬件操作节点
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

STATIC HI_VOID TdeOsiSetBaseOptParaForBlit(TDE2_OPT_S * pstOpt, TDE2_SURFACE_S* pstSrc1, TDE2_SURFACE_S* pstSrc2,
                                           TDE_OPERATION_CATEGORY_E enOptCategory, TDE_HWNode_S *pstHwNode)
{
    TDE_DRV_BASEOPT_MODE_E enBaseOpt = {0};
    TDE_DRV_ALU_MODE_E enAlu = TDE_ALU_NONE;

    if (HI_NULL == pstHwNode || HI_NULL == pstOpt)
    {
        return;
    }

/** deal with codecc,not return TDE_COLORFMT_CATEGORY_An**/
#ifndef HIGO_CODE_CUT
    if (HI_NULL != pstSrc1 && HI_NULL != pstSrc2)
    {
    	
        if (   (TDE_COLORFMT_CATEGORY_An == TdeOsiGetFmtCategory(pstSrc2->enColorFmt))
            && (  TDE_COLORFMT_CATEGORY_ARGB == TdeOsiGetFmtCategory(pstSrc1->enColorFmt)
               || TDE_COLORFMT_CATEGORY_YCbCr == TdeOsiGetFmtCategory(pstSrc1->enColorFmt)) )
        {
            enAlu = TDE_SRC1_BYPASS;
        }
    }
#endif

    if (TDE2_ALUCMD_ROP == pstOpt->enAluCmd)
    {
        /* 调用TdeHalNodeSetRop设置ROP */
        TdeHalNodeSetRop(pstHwNode, pstOpt->enRopCode_Color, pstOpt->enRopCode_Alpha);

        enAlu = TDE_ALU_ROP;
    }
    else if (/*TDE2_ALUCMD_BLEND_PREMUL == pstOpt->enAluCmd || */TDE2_ALUCMD_BLEND == pstOpt->enAluCmd)
    {
       /* if (TDE2_ALUCMD_BLEND_PREMUL == pstOpt->enAluCmd)
        {
            enAlu = TDE_ALU_BLEND_SRC2;
        }
        else*/
        {
            enAlu = TDE_ALU_BLEND;
        }
    }

    if (TDE_OPERATION_DOUBLE_SRC == enOptCategory)
    {
        enBaseOpt = TDE_NORM_BLIT_2OPT;
    }
    else
    {
        enBaseOpt = TDE_NORM_BLIT_1OPT;
    }

    /* 调用TdeHalNodeSetBaseOperate设置基本操作命令 */
    TdeHalNodeSetBaseOperate(pstHwNode, enBaseOpt, enAlu, 0);

    /* 调用TdeHalNodeSetGlobalAlpha设置blit参数 */
    TdeHalNodeSetGlobalAlpha(pstHwNode, pstOpt->u8GlobalAlpha);

    return;
}


/*****************************************************************************
* Function:      TdeOsiSetResizePara
* Description:   设置缩放系数到硬件节点
* Input:         pstHwNode: 需要配置的节点
*                pstFilterOpt: 滤波参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC  HI_VOID TdeOsiSetResizePara(TDE_HWNode_S* pstHwNode, TDE_FILTER_OPT* pstFilterOpt, TDE_NODE_SUBM_TYPE_E enNodeType)
{
    TDE_DRV_RESIZE_CMD_S stResizeCmd = {0};

    /* 设置stResizeCmd */
    stResizeCmd.bCoefSym = pstFilterOpt->bCoefSym;
    stResizeCmd.bHfRing = pstFilterOpt->bHRing;
    stResizeCmd.bVfRing = pstFilterOpt->bVRing;
    if (TDE_NO_SCALE_STEP == pstFilterOpt->u32HStep)
    {
        stResizeCmd.enFilterH = TDE_DRV_FILTER_NONE;
    }
    else
    {
        stResizeCmd.enFilterH = pstFilterOpt->enFilterMode;//TDE_DRV_FILTER_ALL;
    }

    if (TDE_NO_SCALE_STEP == pstFilterOpt->u32VStep)
    {
        stResizeCmd.enFilterV = TDE_DRV_FILTER_NONE;
    }
    else
    {
        stResizeCmd.enFilterV = pstFilterOpt->enFilterMode;//TDE_DRV_FILTER_ALL;
    }

    /* 设置参数 */
    stResizeCmd.u32OffsetX = (HI_U32)pstFilterOpt->s32HOffset;
    stResizeCmd.u32OffsetY = (HI_U32)pstFilterOpt->s32VOffset;
    stResizeCmd.u32StepH = pstFilterOpt->u32HStep;
    stResizeCmd.u32StepV = pstFilterOpt->u32VStep;

    stResizeCmd.bFirstLineOut = pstFilterOpt->bFirstLineOut;
    stResizeCmd.bLastLineOut = pstFilterOpt->bLastLineOut;
    TdeHalNodeSetResize(pstHwNode, &stResizeCmd, enNodeType);
}

/*****************************************************************************
* Function:      TdeOsiSetDeflickerPara
* Description:   设置抗闪烁系数到硬件节点
* Input:         pstHwNode: 需要配置的节点
*
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

STATIC  HI_VOID TdeOsiSetDeflickerPara(TDE_HWNode_S* pstHwNode, TDE2_DEFLICKER_MODE_E enDeflickerMode, TDE_FILTER_OPT* pstFilterOpt)
{

    TDE_DRV_FLICKER_CMD_S stFlickerCmd;
    HI_BOOL bDeflicker = (TDE2_DEFLICKER_MODE_NONE == enDeflickerMode)?HI_FALSE:HI_TRUE;

#ifndef __TDE_CHECK_SLICE_DATA__
    HI_U8 u8DefTable[] = {0, 64, 0, 12, 40, 12, 15, 37, 15, 17, 34, 17,
                          2, 4, 7};
#else
    HI_U8 u8DefTable[] = {0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0,
                          0, 64, 0};
#endif

    memset(&stFlickerCmd, 0, sizeof(TDE_DRV_FLICKER_CMD_S));
    /* 根据算法提供的参数和各个阀值设置stFlicker */
    if (HI_TRUE == bDeflicker){
        stFlickerCmd.enDfeMode = TDE_DRV_AUTO_FILTER;
    }

    stFlickerCmd.u8Coef0LastLine = u8DefTable[0];
    stFlickerCmd.u8Coef0CurLine  = u8DefTable[1];
    stFlickerCmd.u8Coef0NextLine = u8DefTable[2];
    stFlickerCmd.u8Coef1LastLine = u8DefTable[3];
    stFlickerCmd.u8Coef1CurLine  = u8DefTable[4];
    stFlickerCmd.u8Coef1NextLine = u8DefTable[5];
    stFlickerCmd.u8Coef2LastLine = u8DefTable[6];
    stFlickerCmd.u8Coef2CurLine  = u8DefTable[7];
    stFlickerCmd.u8Coef2NextLine = u8DefTable[8];
    stFlickerCmd.u8Coef3LastLine = u8DefTable[9];
    stFlickerCmd.u8Coef3CurLine  = u8DefTable[10];
    stFlickerCmd.u8Coef3NextLine = u8DefTable[11];
    stFlickerCmd.u8Threshold0    = u8DefTable[12];
    stFlickerCmd.u8Threshold1    = u8DefTable[13];
    stFlickerCmd.u8Threshold2    = u8DefTable[14];
    
    stFlickerCmd.enFilterV = pstFilterOpt->enFilterMode;
    stFlickerCmd.enDeflickerMode = enDeflickerMode;
    TdeHalNodeSetFlicker(pstHwNode, &stFlickerCmd);

}




/* AE5D03390:软件规避区域外clip bug */
STATIC HI_S32 TdeOsiAdjClipPara(TDE_HWNode_S* pHWNode)
{
	/* 区域外裁减需要调整clip矩形*/
	if(pHWNode->u32TDE_CLIP_START >> 31)
	{
		HI_U32 u32ClipStartX, u32ClipStartY, u32ClipEndX, u32ClipEndY;
		HI_U32 u32OutStartX, u32OutStartY, u32OutEndX, u32OutEndY;
		HI_U32 u32StartX, u32StartY, u32EndX, u32EndY;

		u32ClipStartX = pHWNode->u32TDE_CLIP_START & 0xfff;
		u32ClipStartY = (pHWNode->u32TDE_CLIP_START >> 16) & 0xfff;
		u32ClipEndX = pHWNode->u32TDE_CLIP_STOP & 0xfff;
		u32ClipEndY = (pHWNode->u32TDE_CLIP_STOP >> 16) & 0xfff;

		u32OutStartX = pHWNode->u32TDE_TAR_XY & 0xfff;
		u32OutStartY = (pHWNode->u32TDE_TAR_XY >> 16) & 0xfff;
		u32OutEndX = u32OutStartX + (pHWNode->u32TDE_TS_SIZE & 0xfff) - 1;
		u32OutEndY = u32OutStartY + ((pHWNode->u32TDE_TS_SIZE >> 16) & 0xfff) - 1;

		u32StartX = (u32ClipStartX > u32OutStartX) ? u32ClipStartX : u32OutStartX;
		u32StartY = (u32ClipStartY > u32OutStartY) ? u32ClipStartY : u32OutStartY;
		u32EndX = (u32ClipEndX < u32OutEndX) ? u32ClipEndX : u32OutEndX;
		u32EndY = (u32ClipEndY < u32OutEndY) ? u32ClipEndY : u32OutEndY;

		//printk("u32StartX=%x, u32StartY=%x, u32EndX=%x,u32EndY=%x\n", u32StartX, u32StartY, u32EndX, u32EndY);

		if((u32StartX > u32EndX) || (u32StartY > u32EndY))
		{
			pHWNode->u32TDE_INS = pHWNode->u32TDE_INS & 0xffffbfff; /* 关闭clip 功能*/
		}
		else
		{
			pHWNode->u32TDE_CLIP_START = ((0x80000000) | (u32StartX & 0xfff) | ((u32StartY & 0xfff) << 16));
			pHWNode->u32TDE_CLIP_STOP = ( (u32EndX & 0xfff) | ((u32EndY & 0xfff) << 16));
			//printk("u32TDE_CLIP_STOP=%x\n", pHWNode->u32TDE_CLIP_STOP );
		}
	
	}

	return HI_SUCCESS;

}

/*****************************************************************************
* Function:      TdeOsiSetNodeFinish
* Description:   完成节点配置,把节点加入到handle标记的list中
* Input:         s32Handle: 任务句柄,表示提交的链表
*                pHWNode: 配置的节点
*                u32WorkBufNum: 临时buffer的个数
*                enSubmType: 提交节点的类型
* Output:        无
* Return:        返回分块的个数
* Others:        节点结构如下:
*                 ----------------------
*                 |  软件节点指针(4)   |
*                 ----------------------
*                 |  配置参数          |
*                 ----------------------
*                 |下一节点物理地址(4) |
*                 ----------------------
*                 |下一节点更新标识(4) |
*                 ----------------------
*****************************************************************************/
STATIC HI_S32 TdeOsiSetNodeFinish(TDE_HANDLE s32Handle, TDE_HWNode_S* pHWNode,
                                  HI_U32 u32WorkBufNum, TDE_NODE_SUBM_TYPE_E enSubmType)
{
    HI_U32 u32Size;
    HI_VOID* pBuf = HI_NULL;
    TDE_NODE_BUF_S stSwNode = {0};
    HI_S32 s32Ret;

    /* AE5D03390:软件规避区域外clip bug */
    TdeOsiAdjClipPara(pHWNode);

    u32Size = TdeHalNodeGetNdSize(pHWNode);
    if (0 == u32Size)
    {
        TDE_TRACE(TDE_KERN_INFO, "error buffer size!\n");
    
        return HI_FAILURE;
    }

    pBuf = (HI_VOID *)TDE_MALLOC(u32Size + TDE_NODE_HEAD_BYTE + TDE_NODE_TAIL_BYTE);
    if (HI_NULL == pBuf)
    {
        TDE_TRACE(TDE_KERN_INFO, "malloc (%d) failed, wgetfreenum(%d)!\n", (u32Size + TDE_NODE_HEAD_BYTE + TDE_NODE_TAIL_BYTE), wgetfreenum());
        return HI_ERR_TDE_NO_MEM;
    }

    /*写入需要修改的寄存器值。下一节点的地址和更新标识，需要在下一节点提交时写入*/
    TdeHalNodeMakeNd((HI_CHAR *)pBuf + TDE_NODE_HEAD_BYTE, pHWNode);

#ifdef  TDE_DEBUG
    TdeOsiPrintNodeInfo(pHWNode);
#endif
    TDE_PROC_PRINT_ND_PARA(pHWNode);

    
    stSwNode.pBuf = pBuf;
    stSwNode.u32NodeSz = u32Size;
    stSwNode.u64Update = pHWNode->u64TDE_UPDATE;
    stSwNode.u32PhyAddr = wgetphy(pBuf) + TDE_NODE_HEAD_BYTE;
    //printk("[tde_osictl.c:%d]pBuf:%x\n", __LINE__, stSwNode.u32PhyAddr);
        
    if((s32Ret = TdeOsiListAddNode(s32Handle, &stSwNode, enSubmType, u32WorkBufNum)) < 0)
    {
        TDE_TRACE(TDE_KERN_INFO, "TdeOsiListAddNode fail!\n");
        TDE_FREE(pBuf);
        return s32Ret;
    }
    return HI_SUCCESS;
}

/****************************************************************************/
/*                             TDE osi ctl 接口实现                         */
/****************************************************************************/

/*****************************************************************************
* Function:      TdeOsiBeginJob
* Description:   获得TDE 任务句柄
* Input:         无
* Output:        无
* Return:        创建的任务句柄
* Others:        无
*****************************************************************************/
HI_S32 TdeOsiBeginJob(TDE_HANDLE *ps32Handle)
{
    if (NULL == ps32Handle)
    {
        TDE_TRACE(TDE_KERN_ERR, "Null ptr!\n");
        return HI_ERR_TDE_NULL_PTR;
    }

    return TdeOsiListBeginJob(ps32Handle);
}

/*****************************************************************************
* Function:      TdeOsiEndJob
* Description:   提交TDE任务
* Input:         s32Handle: 任务句柄
*                bBlock: 是否阻塞
*                u32TimeOut: 超时时间值(10ms为单位)
* Output:        无
* Return:        成功 / 失败
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiEndJob(TDE_HANDLE s32Handle, HI_BOOL bBlock, HI_U32 u32TimeOut,
                        HI_BOOL bSync, TDE_FUNC_CB pFuncComplCB, HI_VOID *pFuncPara)
{
    /* 强制写成异步提交，通知模式没有实际作用，任务必然时串行阻塞的 */
    return TdeOsiListSubmitJob(s32Handle, TDE_LIST_AQ, u32TimeOut, pFuncComplCB, pFuncPara, TDE_JOB_WAKE_NOTIFY);
}



/*****************************************************************************
* Function:      TdeOsiQuickFill
* Description:   快速将固定值填充到目标位图，填充值依赖于目标位图格式
* Input:         pstDst: 目标位图信息结构
*                u32FillData: 填充值
*                pFuncComplCB: 操作完成回调函数指针,为NULL表示不需要通知操作完成
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiQuickFill(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstDst, TDE2_RECT_S *pstDstRect,
                           HI_U32 u32FillData)
{
    TDE2_FILLCOLOR_S stFillColor;

    stFillColor.enColorFmt   = pstDst->enColorFmt;
    stFillColor.u32FillColor = u32FillData;

    return TdeOsi1SourceFill(s32Handle, pstDst, pstDstRect, &stFillColor, NULL);
}
/*
HI_S32 TdeOsiSetDeflickerLevel(TDE_DEFLICKER_LEVEL_E eDeflickerLevel)
{
    return TdeHalSetDeflicerLevel(eDeflickerLevel);
}
*/

HI_S32 TdeOsiSetAlphaThresholdValue(HI_U8 u8ThresholdValue)
{
    return TdeHalSetAlphaThreshold(u8ThresholdValue);
}


HI_S32 TdeOsiSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold)
{
    return TdeHalSetAlphaThresholdState(bEnAlphaThreshold);
}


/*****************************************************************************
* Function:      TdeOsiSingleSrc1Blit
* Description:   单源1的操作实现
* Input:         pstBackGround: 源1位图信息结构
*                pstBackGroundRect: 源1位图操作区域
*                pstDst: 目的位图信息结构
*                pstDstRect: 目的位图操作区域
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
#ifndef HIGO_CODE_CUT
STATIC HI_S32 TdeOsiSingleSrc1Blit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                                   TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect)
{
    TDE_HWNode_S stHWNode;
    TDE_DRV_SURFACE_S stSrcDrvSurface;
    TDE_DRV_SURFACE_S stDstDrvSurface;
    TDE_SCANDIRECTION_S stSrcScanInfo;
    TDE_SCANDIRECTION_S stDstScanInfo;

    /* 调用TdeHalNodeInitNd(&stHWNode)初始化节点 */
    TdeHalNodeInitNd(&stHWNode, HI_FALSE);

    /* 调用TdeHalNodeSetBaseOperate设置基本操作命令 */
    TdeHalNodeSetBaseOperate(&stHWNode, TDE_QUIKE_COPY, TDE_SRC1_BYPASS, 0);

    /* 获取扫描信息 */
    if (TdeOsiGetScanInfo(pstBackGround, pstBackGroundRect, pstDst, pstDstRect, HI_NULL,
                          &stSrcScanInfo,
                          &stDstScanInfo) < 0)
    {
        return HI_ERR_TDE_INVALID_PARA;
    }

    /* 转换源surface */
    TdeOsiConvertSurface(pstBackGround, pstBackGroundRect, &stSrcScanInfo, &stSrcDrvSurface, NULL);

    /* 设置背景信息 */
    TdeHalNodeSetSrc1(&stHWNode, &stSrcDrvSurface);

    TdeOsiSetExtAlpha(pstBackGround, HI_NULL, &stHWNode); /* AI7D02681 */

    /* 转换目标surface */
    TdeOsiConvertSurface(pstDst, pstDstRect, &stDstScanInfo, &stDstDrvSurface, NULL);

    /* 设置目标信息 */
    TdeHalNodeSetTgt(&stHWNode, &stDstDrvSurface, TDE2_OUTALPHA_FROM_NORM);

    /* 提交节点 */
    return TdeOsiSetNodeFinish(s32Handle, &stHWNode, 0, TDE_NODE_SUBM_ALONE);
}

#endif
/*****************************************************************************
* Function:      TdeOsiSingleSrc2Blit
* Description:   单源2的操作实现
* Input:         pstForeGround: 源2位图信息结构
*                pstForeGroundRect: 源2位图操作区域
*                pstDst: 目的位图信息结构
*                pstDstRect: 目的位图操作区域
*                pstOpt:配置参数
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/

STATIC HI_S32 TdeOsiSingleSrc2Blit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                                   TDE2_SURFACE_S* pstDst,
                                   TDE2_RECT_S  *pstDstRect,
                                   TDE2_OPT_S* pstOpt)
{
    TDE_HWNode_S stHWNode = {0};
    TDE_DRV_SURFACE_S stSrcDrvSurface;
    TDE_DRV_SURFACE_S stDstDrvSurface;
    TDE_SCANDIRECTION_S stSrcScanInfo;
    TDE_SCANDIRECTION_S stDstScanInfo;
    HI_U16 u16Code;
    TDE_DRV_CONV_MODE_CMD_S stConv;
    TDE2_RECT_S stFGOptArea;
    TDE2_RECT_S stDstOptArea;
    TDE_FILTER_OPT stFilterOpt = {0};

    if (NULL == pstOpt)
        return HI_ERR_TDE_NULL_PTR;
    
    if (TdeOsiCheckSingleSrc2Opt(pstForeGround->enColorFmt, pstDst->enColorFmt, pstOpt) < 0)
    {
        return HI_ERR_TDE_INVALID_PARA;
    }

    if(pstOpt->bResize)
    {
        if (TdeOsiCheckResizePara(pstForeGroundRect->u32Width, pstForeGroundRect->u32Height,
                                  pstDstRect->u32Width, pstDstRect->u32Height) < 0)
        {
            return HI_ERR_TDE_MINIFICATION;
        }
    }

    /* 调用TdeHalNodeInitNd(&stHWNode)初始化节点 */
    TdeHalNodeInitNd(&stHWNode, HI_FALSE);

    /* 设置clip信息，可能会调整surface大小 */
    if(TdeOsiSetClipPara(NULL, NULL, pstForeGround, pstForeGroundRect, pstDst,
                      pstDstRect, pstOpt, &stHWNode) < 0)
    {
        return HI_ERR_TDE_CLIP_AREA;
    }

    /* 获取扫描信息 */
    if (TdeOsiGetScanInfo(pstForeGround, pstForeGroundRect, pstDst, pstDstRect, pstOpt,
                          &stSrcScanInfo, &stDstScanInfo) < 0)
    {
        return HI_ERR_TDE_INVALID_PARA;
    }

    /* 转换源surface */
    TdeOsiConvertSurface(pstForeGround, pstForeGroundRect, &stSrcScanInfo, &stSrcDrvSurface, &stFGOptArea);

    /* 设置前景信息 */
    TdeHalNodeSetSrc2(&stHWNode, &stSrcDrvSurface);

    /* 转换目标surface */
    TdeOsiConvertSurface(pstDst, pstDstRect, &stDstScanInfo, &stDstDrvSurface, &stDstOptArea);

    /* 输出alpha来源检查 */
    TDE_CHECK_OUTALPHAFROM(pstOpt->enOutAlphaFrom);

    if(TDE2_OUTALPHA_FROM_BACKGROUND == pstOpt->enOutAlphaFrom)
    {
        TDE_TRACE(TDE_KERN_ERR, "enOutAlphaFrom error!\n");
        return HI_ERR_TDE_INVALID_PARA;
        
    }

    /* 设置目标信息 */
    TdeHalNodeSetTgt(&stHWNode, &stDstDrvSurface, pstOpt->enOutAlphaFrom);

    /* 调用TdeOsiSingleSrc2GetOptCode获取编码 */
    u16Code = TdeOsiSingleSrc2GetOptCode(pstForeGround->enColorFmt, pstDst->enColorFmt);

    TdeOsiGetConvbyCode(u16Code, &stConv);

    /* 调用TdeHalNodeSetColorConvert设置编码 */
    TdeHalNodeSetColorConvert(&stHWNode, &stConv);

    TdeOsiSetBaseOptParaForBlit(pstOpt, HI_NULL, pstForeGround,TDE_OPERATION_SINGLE_SRC2, &stHWNode);

    TdeOsiSetExtAlpha(HI_NULL, pstForeGround, &stHWNode); /* AI7D02681 */

    if ((pstOpt->bResize) || (pstOpt->enDeflickerMode != TDE2_DEFLICKER_MODE_NONE))
    {
        /* 调用分块处理 */        

        /* 设置扫描方向 */
        memcpy(&stFilterOpt.stSrcDire, &stSrcScanInfo, sizeof(TDE_SCANDIRECTION_S));
        memcpy(&stFilterOpt.stDstDire, &stDstScanInfo, sizeof(TDE_SCANDIRECTION_S));

        stFilterOpt.enFilterMode = g_enTdeFilterMode[pstOpt->enFilterMode];

        /* 调用缩放分块处理函数TdeOsiSetFilterNode */
        return TdeOsiSetFilterNode(s32Handle, &stHWNode, pstForeGround, pstDst,
                                   &stFGOptArea, &stDstOptArea, pstOpt->enDeflickerMode, &stFilterOpt);
    }
    else
    {
        /* 提交节点 */
        return TdeOsiSetNodeFinish(s32Handle, &stHWNode, 0, TDE_NODE_SUBM_ALONE);
    }
    return HI_SUCCESS;
}

/*****************************************************************************
* Function:      TdeOsiDoubleSrcBlit
* Description:   双源的操作实现
* Input:         pstBackGround: 源1位图信息结构
*                pstBackGroundRect: 源1位图操作区域
*                pstForeGround: 源2位图信息结构
*                pstForeGroundRect: 源2位图操作区域
*                pstDst: 目的位图信息结构
*                pstDstRect: 目的位图操作区域
*                pstOpt:配置参数
* Output:        无
* Return:        成功/失败
* Others:        AI7D02579 增加对YCbCr422的支持
*****************************************************************************/
STATIC HI_S32 TdeOsiDoubleSrcBlit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                                  TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                                  TDE2_SURFACE_S* pstDst,
                                  TDE2_RECT_S  *pstDstRect,
                                  TDE2_OPT_S* pstOpt)
{
    TDE_HWNode_S stHWNode = {0};
    TDE_DRV_SURFACE_S stSrcDrvSurface;
    TDE_DRV_SURFACE_S stDstDrvSurface;
    TDE_SCANDIRECTION_S stSrcScanInfo;
    TDE_SCANDIRECTION_S stDstScanInfo;
    HI_U16 u16Code;
    TDE2_RECT_S stBGOptArea;
    TDE2_RECT_S stFGOptArea;
    TDE2_RECT_S stDstOptArea;
    TDE_FILTER_OPT stFilterOpt = {0};
    TDE_DRV_CONV_MODE_CMD_S stConv = {0};

    if (TdeOsiCheckDoubleSrcOpt(pstBackGround->enColorFmt, pstForeGround->enColorFmt, pstDst->enColorFmt,
                                pstOpt) < 0)
    {
        return HI_ERR_TDE_INVALID_PARA;
    }
    
    if(pstOpt->bResize)
    {
        if (TdeOsiCheckResizePara(pstForeGroundRect->u32Width, pstForeGroundRect->u32Height,
                                  pstDstRect->u32Width, pstDstRect->u32Height) < 0)
        {
            return HI_ERR_TDE_MINIFICATION;
        }
    }
    
    /* 调用TdeHalNodeInitNd(&stHWNode)初始化节点 */
    TdeHalNodeInitNd(&stHWNode, HI_FALSE);

    /* 设置clip信息，可能会调整surface大小 */
    if(TdeOsiSetClipPara(pstBackGround, pstBackGroundRect, pstForeGround, pstForeGroundRect, pstDst,
                      pstDstRect, pstOpt, &stHWNode) < 0)
    {
        return HI_ERR_TDE_CLIP_AREA;
    }

    /* 获取扫描信息 */
    if (TdeOsiGetScanInfo(pstForeGround, pstForeGroundRect, pstDst, pstDstRect, pstOpt,
                          &stSrcScanInfo,
                          &stDstScanInfo) < 0)
    {
        return HI_ERR_TDE_INVALID_PARA;
    }

    /* 转换背景surface */
    TdeOsiConvertSurface(pstBackGround, pstBackGroundRect, &stSrcScanInfo, &stSrcDrvSurface, &stBGOptArea);

    /* 设置背景信息 */
    TdeHalNodeSetSrc1(&stHWNode, &stSrcDrvSurface);

    /* 转换前景surface */
    TdeOsiConvertSurface(pstForeGround, pstForeGroundRect, &stSrcScanInfo, &stSrcDrvSurface, &stFGOptArea);

    /* 设置前景信息 */
    TdeHalNodeSetSrc2(&stHWNode, &stSrcDrvSurface);

    /* 转换目标surface */
    TdeOsiConvertSurface(pstDst, pstDstRect, &stDstScanInfo, &stDstDrvSurface, &stDstOptArea);

    /* 输出alpha来源检查 */
    TDE_CHECK_OUTALPHAFROM(pstOpt->enOutAlphaFrom);

    /* 设置目标信息 */
    TdeHalNodeSetTgt(&stHWNode, &stDstDrvSurface, pstOpt->enOutAlphaFrom);

    /* 调用TdeOsiDoubleSrcGetOptCode获取编码 */
    u16Code = TdeOsiDoubleSrcGetOptCode(pstBackGround->enColorFmt, pstForeGround->enColorFmt,
                                        pstDst->enColorFmt);

    TdeOsiGetConvbyCode(u16Code, &stConv);

    /* 调用TdeHalNodeSetColorConvert设置编码 */
    TdeHalNodeSetColorConvert(&stHWNode, &stConv);

    TdeOsiSetBaseOptParaForBlit(pstOpt, pstBackGround, pstForeGround, TDE_OPERATION_DOUBLE_SRC, &stHWNode);

    TdeOsiSetExtAlpha(pstBackGround, pstForeGround, &stHWNode);
    
    //if ((pstOpt->bResize) || (pstOpt->bDeflicker))
    if ((pstOpt->bResize) || (TDE2_DEFLICKER_MODE_NONE != pstOpt->enDeflickerMode))
    {
        TDE_DOUBLESRC_ADJ_INFO_S stDSAdjInfo;
        stDSAdjInfo.bDoubleSource = HI_TRUE;
        stDSAdjInfo.s32DiffX = stBGOptArea.s32Xpos - stDstOptArea.s32Xpos;
        stDSAdjInfo.s32DiffY = stBGOptArea.s32Ypos - stDstOptArea.s32Ypos;

        /* 调用分块处理 */        

        /* 设置扫描方向 */
        memcpy(&stFilterOpt.stSrcDire, &stSrcScanInfo, sizeof(TDE_SCANDIRECTION_S));
        memcpy(&stFilterOpt.stDstDire, &stDstScanInfo, sizeof(TDE_SCANDIRECTION_S));

        /* 设置双原调整信息 */
        memcpy(&stFilterOpt.stDSAdjInfo, &stDSAdjInfo, sizeof(TDE_DOUBLESRC_ADJ_INFO_S));

        stFilterOpt.enFilterMode = g_enTdeFilterMode[pstOpt->enFilterMode];

        /* 需要判断是否为局部抗闪烁*/
        /* 调用缩放分块处理函数TdeOsiSetFilterNode */
        return TdeOsiSetFilterNode(s32Handle, &stHWNode, pstForeGround, pstDst,
                                   &stFGOptArea, &stDstOptArea, pstOpt->enDeflickerMode, &stFilterOpt);
    }
    else
    {
        /* 提交节点 */
        return TdeOsiSetNodeFinish(s32Handle, &stHWNode, 0, TDE_NODE_SUBM_ALONE);
    }
}

/*****************************************************************************
* Function:      TdeOsiYC422TmpOpt
* Description:   如果操作中有YCbCr422位图时,需要增加一个pass临时处理
* Input:         s32Handle: 任务句柄
*                pstForeGround: 前景位图信息结构
*                pstForeGroundRect: 前景位图操作区域结构
*                pstDst:  目标位图信息结构
*                pstDstRect: 目的位图操作区域结构
*                pstOpt:  运算参数设置结构
* Output:        无
* Return:        =0: 成功, <0:有错误
* Others:        AI7D02579 增加对YCbCr422的支持
*****************************************************************************/
STATIC HI_S32 TdeOsiYC422TmpOpt(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect,
                                TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pstOpt)
{
    TDE2_OPT_S stTmpOpt = {0};
    TDE2_SURFACE_S stTmpDst = {0};
    TDE2_RECT_S stTmpDstRect = {0};
    HI_S32 s32Ret = HI_FAILURE;
    HI_BOOL bDeflicker;

    /* 不能在滤波的同时作镜像 */
    if (((pstOpt->enDeflickerMode != TDE2_DEFLICKER_MODE_NONE)|| (pstOpt->bResize)) && (pstOpt->enMirror))
    {
        TDE_TRACE(TDE_KERN_ERR, "Could not support VF/FF/HF and Mirror\n!");
        return HI_ERR_TDE_UNSUPPORTED_OPERATION;
    }

    bDeflicker = (pstOpt->enDeflickerMode == TDE2_DEFLICKER_MODE_NONE)?HI_FALSE:HI_TRUE;
    /* 如果可以直接一个pass作完, 则直接返回 */
    if (0 == TdeOsiCheckYc422RPara(pstForeGround, pstForeGroundRect, pstDst, pstDstRect, 
                                   bDeflicker, pstOpt->bResize))
    {
        TDE_TRACE(TDE_KERN_DEBUG, "One Pass For Tmp Operation!\n");
        return 0;
    }
    TDE_TRACE(TDE_KERN_DEBUG, "Two Pass For Tmp Operation!\n");

    /* YCbCr422输入时,不支持输出格式为不足16bit/pix的格式 */
    if (TdeOsiGetbppByFmt(pstDst->enColorFmt) < 16)
    {
        TDE_TRACE(TDE_KERN_ERR, "Could not output the format For YCbCr422R!\n");
        return HI_ERR_TDE_UNSUPPORTED_OPERATION;
    }
    
    if (!pstOpt->bResize)
    {
        TDE_UNIFY_RECT(pstForeGroundRect, pstDstRect);
    }

    stTmpOpt.bResize = pstOpt->bResize;
    stTmpOpt.enDeflickerMode = pstOpt->enDeflickerMode;

    memcpy(&stTmpDst, pstDst, sizeof(TDE2_SURFACE_S));
    memcpy(&stTmpDstRect, pstDstRect, sizeof(TDE2_RECT_S));
    stTmpDst.enColorFmt = TDE2_COLOR_FMT_RGB565;
    stTmpDst.u32Stride = stTmpDst.u32Width * 2;

    TDE_TRACE(TDE_KERN_DEBUG, "tmp x:%d, y:%d, w:%d, h:%d\n", 
              stTmpDstRect.s32Xpos, stTmpDstRect.s32Ypos, stTmpDstRect.u32Width, stTmpDstRect.u32Height);

    if ((s32Ret = TdeOsiSingleSrc2Blit(s32Handle, pstForeGround, 
                  pstForeGroundRect, &stTmpDst, &stTmpDstRect, &stTmpOpt)) < 0)
    {
        return s32Ret;
    }

    memcpy(pstForeGround, &stTmpDst, sizeof(TDE2_SURFACE_S));
    memcpy(pstForeGroundRect, &stTmpDstRect, sizeof(TDE2_RECT_S));

    /* 所有的滤波操作都在pass1中完成, 后面的操作不做滤波 */
    pstOpt->enDeflickerMode = TDE2_DEFLICKER_MODE_NONE;
    pstOpt->bResize = HI_FALSE;

    return 0;
}

/*****************************************************************************
* Function:      TdeOsiBlit
* Description:   将pstBackGround与pstForeGround的位图进行运算将结果输出到pstDst中，运算设置在pstOpt
* Input:         enCmd: TDE运算指令种类
*                pstBackGround: 背景位图信息结构
*                pstForeGround: 前景位图信息结构
*                pstDst:  目标位图信息结构
*                pstOpt:  运算参数设置结构
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiBlit(TDE_HANDLE s32Handle, TDE2_SURFACE_S* pstBackGround, TDE2_RECT_S  *pstBackGroundRect,
                      TDE2_SURFACE_S* pstForeGround, TDE2_RECT_S  *pstForeGroundRect, TDE2_SURFACE_S* pstDst,
                      TDE2_RECT_S  *pstDstRect, TDE2_OPT_S* pstOpt)
{
    TDE_OPERATION_CATEGORY_E enOptCategory;
    HI_S32 s32Ret = 0;

    /* 调用TdeOsiGetOptCategory获取操作分类 */
    enOptCategory = TdeOsiGetOptCategory(pstBackGround, pstBackGroundRect, pstForeGround, pstForeGroundRect, pstDst,
                                         pstDstRect, pstOpt);

    switch (enOptCategory)
    {
#ifndef HIGO_CODE_CUT
    case TDE_OPERATION_SINGLE_SRC1:
    {
        if (NULL == pstBackGround)
        {
            return TdeOsiSingleSrc1Blit(s32Handle, pstForeGround, pstForeGroundRect,
                                        pstDst, pstDstRect);
        }
        else
        {
            return TdeOsiSingleSrc1Blit(s32Handle, pstBackGround, pstBackGroundRect,
                                        pstDst, pstDstRect);
        }
    }
    break;
  
    case TDE_OPERATION_SINGLE_SRC2:
    {
        if (NULL == pstBackGround)
        {
            if ((s32Ret = TdeOsiYC422TmpOpt(s32Handle, pstForeGround, pstForeGroundRect,
                                        pstDst, pstDstRect, pstOpt)) < 0)
            {
                return s32Ret;
            }

            if ((s32Ret = TdeOsiSingleSrc2Blit(s32Handle, pstForeGround, pstForeGroundRect,
                                        pstDst, pstDstRect, pstOpt)) < 0)
            {
                return s32Ret;
            }
        }
        else
        {
            if ((s32Ret = TdeOsiYC422TmpOpt(s32Handle, pstBackGround, pstBackGroundRect,
                                        pstDst, pstDstRect, pstOpt)) < 0 )
            {
                return s32Ret;
            }

            if ((s32Ret = TdeOsiSingleSrc2Blit(s32Handle, pstBackGround, pstBackGroundRect,
                                        pstDst, pstDstRect, pstOpt)) < 0 ) /*AI7D02940*/
            {
                return s32Ret;
            }
        }
    }
    break;
   #endif
    case TDE_OPERATION_DOUBLE_SRC:
    {
        if ((s32Ret = TdeOsiYC422TmpOpt(s32Handle, pstForeGround, pstForeGroundRect,
                                        pstDst, pstDstRect, pstOpt)) < 0)
        {
            return s32Ret;
        }
        
        if ((s32Ret = TdeOsiDoubleSrcBlit(s32Handle, pstBackGround, pstBackGroundRect, pstForeGround, pstForeGroundRect,
                                   pstDst, pstDstRect, pstOpt)) < 0)
        {
            return s32Ret;
        }
    }
    break;
    default:
        return HI_ERR_TDE_INVALID_PARA;
    }
    return HI_SUCCESS;
}


/*****************************************************************************
* Function:      TdeOsiMbBlit
* Description:   宏块处理接口
* Input:         s32Handle: 任务句柄
*                pstMB: 宏块位图信息结构
*                pstMbRect: 宏块位图操作区域
*                pstDst: 目的位图信息结构
*                pstDstRect:  目标位图操作区域
*                pstMbOpt:  运算参数设置结构
* Output:        无
* Return:        >0: 返回当前操作所属任务的id ; <0: 失败
* Others:        无
*****************************************************************************/
HI_S32     TdeOsiMbBlit(TDE_HANDLE s32Handle, TDE2_MB_S* pstMB, TDE2_RECT_S  *pstMbRect,
                        TDE2_SURFACE_S* pstDst, TDE2_RECT_S  *pstDstRect, TDE2_MBOPT_S* pstMbOpt)
{
    TDE_HWNode_S stHwNode = {0};

    if ((HI_NULL == pstMB) || (HI_NULL == pstMbRect) 
        || (HI_NULL == pstDst) || (HI_NULL == pstDstRect) || (HI_NULL == pstMbOpt))
    {
        TDE_TRACE(TDE_KERN_ERR, "Contains NULL ptr!\n");
        return HI_ERR_TDE_NULL_PTR;
    }

    if((pstDstRect->u32Height == pstMbRect->u32Height)
        &&(pstDstRect->u32Width == pstMbRect->u32Width))
    {
        pstMbOpt->enResize = TDE2_MBRESIZE_NONE;
    }

    if (TDE2_MBRESIZE_NONE == pstMbOpt->enResize)
    {
        TDE_UNIFY_RECT(pstMbRect, pstDstRect);
    }

    if (TdeOsiCheckResizePara(pstMbRect->u32Width, pstMbRect->u32Height,
                              pstDstRect->u32Width, pstDstRect->u32Height) < 0)
    {
        TDE_TRACE(TDE_KERN_INFO, "The Scale is too large!\n");
        return HI_ERR_TDE_MINIFICATION;
    }

    return TdeOsiSetMbPara(s32Handle, &stHwNode, pstMB, pstMbRect,
                           pstDst, pstDstRect, pstMbOpt);
}



#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

