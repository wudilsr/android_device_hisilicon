/*****************************************************************************
*             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: tde_hal.c
* Description:TDE hal interface define
*
* History:
* Version   Date          Author        DefectNum       Description
*
*****************************************************************************/
#include "tde_hal.h"
#include "tde_define.h"
#include "wmalloc.h"
#include "list.h"

#include "hi_reg_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif  /* __cplusplus */
#endif  /* __cplusplus */


/****************************************************************************/
/*                             TDE hal 内部宏定义                           */
/****************************************************************************/



/*计算结构体成员的偏移值*/
#define TDE_OFFSET_OF(type, member) ((HI_U32) (&((type *)0)->member))

#ifdef TDE_VERSION_MPW
#define UPDATE_SIZE 32
#else
#define UPDATE_SIZE 64
#endif
/*用于判断当前设置下对应的Update标记是否为1*/
#define TDE_MASK_UPDATE(member) (1 << ((TDE_OFFSET_OF(TDE_HWNode_S, member) >> 2) % (UPDATE_SIZE)))

/* 根据设置的配置更新update 标记 */
#define TDE_SET_UPDATE(member, updateflg) \
do{\
    updateflg |= ((HI_U64)1 << ((TDE_OFFSET_OF(TDE_HWNode_S, member))/4 % (UPDATE_SIZE)));\
}while(0)

#define TDE_FILL_DATA_BY_FMT(fill, data, fmt)\
do{\
    HI_U32 u32Bpp;\
    u32Bpp = TdeHalGetbppByFmt(fmt);\
    if (0xffffffff != u32Bpp)\
    {\
        HI_U32 i;\
        HI_U32 u32Cell;\
        u32Cell = data & (0xffffffff >> (32 - u32Bpp));\
        for (i = 0; i < (32 / u32Bpp); i++)\
        {\
            fill |= (u32Cell << (i * u32Bpp));\
        }\
    }\
    else\
    {\
        fill = data;\
    }\
}while(0)

/* 根据当前成员和更新标记获取节点Buffer中的成员指针
   返回pRet为空表示当前Buffer中没有需要的member */
#define TDE_GET_MEMBER_IN_BUFF(pRet, member, pstVirBuf, update)\
do{\
    HI_S32 s32Offset;\
    \
    s32Offset = TdeHalGetOffsetInNode(TDE_MASK_UPDATE(member), update);\
    if (-1 != s32Offset )\
    {\
        pRet = pstVirBuf + s32Offset;\
    }\
    else\
    {\
        pRet = HI_NULL;\
    }\
}while(0)

#ifdef TDE_VERSION_MPW
#define TDE_ALPHA_ADJUST(u8Alpha)\
do{\
    if(255 == u8Alpha)\
    {\
        u8Alpha = 0x80;\
    }\
    else\
    {\
        u8Alpha = ((u8Alpha + 1)>>1); /*AI7D02798*/ \
    }\
}while(0)
#else
#define TDE_ALPHA_ADJUST(u8Alpha)
#endif


#define TDE_GET_MEMBER_IN_BUFNODE(pRet, member, pstNdBuf) \
    TDE_GET_MEMBER_IN_BUFF(pRet, member, (pstNdBuf)->pu32VirAddr, (pstNdBuf)->u32CurUpdate)

/* 读写寄存器封装 */
#define TDE_READ_REG(base, offset) \
    (*(volatile unsigned int   *)((unsigned int)(base) + (offset)))
    
#define TDE_WRITE_REG(base, offset, value) \
    (*(volatile unsigned int   *)((unsigned int)(base) + (offset)) = (value))

/* TDE寄存器地址范围 */
#define TDE_REG_SIZE 0x1000

#define TDE_PARA_TABLE_SIZE 32
#define TDE_PARA_TABLE_ORG_SIZE 40
#define TDE_PARA_TABLE_NUM  12

#define TDE_PARA_HTABLE_ORG_SIZE 33 * 4
#define TDE_PARA_HTABLE_SIZE 160 /* 配置给硬件的参数表需要16字节对齐, 因此多使用了160字节 */
#define TDE_PARA_HTABLE_NUM  6

#define TDE_PARA_VTABLE_ORG_SIZE 40
#define TDE_PARA_VTABLE_SIZE TDE_PARA_TABLE_SIZE
#define TDE_PARA_VTABLE_NUM  TDE_PARA_TABLE_NUM

/* 算法组提供Step的范围类型 */
#define TDE_RESIZE_PARA_AREA_0  3724     /*1.1*/
#define TDE_RESIZE_PARA_AREA_1  4096     /*1.0*/
#define TDE_RESIZE_PARA_AREA_2  4501     /*0.91*/
#define TDE_RESIZE_PARA_AREA_3  4935     /*0.83*/
#define TDE_RESIZE_PARA_AREA_4  5326     /*0.769*/
#define TDE_RESIZE_PARA_AREA_5  5729     /*0.715*/
#define TDE_RESIZE_PARA_AREA_6  6141     /*0.667*/
#define TDE_RESIZE_PARA_AREA_7  8192     /*0.5*/
#define TDE_RESIZE_PARA_AREA_8  12300    /*0.333*/
#define TDE_RESIZE_PARA_AREA_9  16384    /*0.25*/
#define TDE_RESIZE_PARA_AREA_10 20480    /*0.2*/
/* 8*32相系数表范围 */
#define TDE_RESIZE_8X32_AREA_0  4096     /*1.0*/
#define TDE_RESIZE_8X32_AREA_1  5936     /*0.69*/
#define TDE_RESIZE_8X32_AREA_2  8192     /*0.5*/
#define TDE_RESIZE_8X32_AREA_3  12412    /*0.33*/
#define TDE_RESIZE_8X32_AREA_4  204800   /*0.02*/

/* ColorKey芯片所需的模式 */
#define TDE_COLORKEY_IGNORE     2
#define TDE_COLORKEY_AREA_OUT   1
#define TDE_COLORKEY_AREA_IN    0

/* Aq控制模式 */
#define TDE_AQ_CTRL_COMP_LIST   0x0 /*完成当前链表之后，启动下一个同步链表*/
#define TDE_AQ_CTRL_COMP_LINE   0x4 /*完成当前链表当前节点当前行后，启动下一个同步链表*/

/* Sq控制模式*/
#define TDE_SQ_CTRL_COMP_LIST   0x0 /*完成当前链表之后，启动下一个同步链表*/
#define TDE_SQ_CTRL_COMP_LINE   0x4 /*完成当前链表当前节点当前行后，启动下一个同步链表*/

/* 当前行挂起时的标记 */
#define TDE_SUSP_LINE_INVAL (-1)
#define TDE_SUSP_LINE_READY (-2)

#define TDE_MAX_READ_STATUS_TIME 10

/****************************************************************************/
/*                             TDE hal 内部类型定义                         */
/****************************************************************************/
/* 源位图运行模式 */
typedef enum hiTDE_SRC_MODE_E
{
    TDE_SRC_MODE_DISA  = 0,
    TDE_SRC_MODE_BMP   = 1,
    TDE_SRC_MODE_PATTERN = 2,
    TDE_SRC_MODE_FILL  = 3,
    TDE_SRC_QUICK_COPY = 5,
    TDE_SRC_QUICK_FILL = 7    
}TDE_SRC_MODE_E;

/* Sq控制寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_SQ_CTRL_U
{
    struct
    {
        HI_U32 u32TrigMode     :1;
        HI_U32 u32TrigCond     :1;
        HI_U32 u32Reserve1     :19;
        HI_U32 u32SqOperMode   :4;
        HI_U32 u32SqEn         :1;
        HI_U32 u32Reserve2     :5;
        HI_U32 u32SqUpdateFlag :1;
    }stBits;
    HI_U32 u32All;
}TDE_SQ_CTRL_U;

/* Aq控制寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_AQ_CTRL_U
{
    struct
    {
        HI_U32 u32Reserve1     :20;
        HI_U32 u32AqOperMode   :4;
        HI_U32 u32AqEn         :1;
        HI_U32 u32Reserve2     :7;
    }stBits;
    HI_U32 u32All;
}TDE_AQ_CTRL_U;

/* 操作方式寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_INS_U
{
    struct
    {
        HI_U32 u32Src1Mod       :3;     /* 源1运行模式 */
        HI_U32 u32Src2Mod       :2;     /* 源2运行模式 */
        HI_U32 u32IcsConv       :1;     /* 输入颜色空间转换使能 */
        HI_U32 u32Resize        :1;     /* 2D缩放使能 */
        HI_U32 u32DfeEn         :1;     /* 抗闪烁滤波器使能 */
#ifdef TDE_VERSION_MPW
        HI_U32 u32Reserve1      :3;     /* 保留 */
#else
	    HI_U32 u32Y1En		:1;		    /* Y1通道使能*/	
	    HI_U32 u32Y2En		:1;		    /* Y2通道使能*/
        HI_U32 u32Reserve1      :1;     /* 保留 */
#endif
        HI_U32 u32Clut          :1;     /* CLUT使能 */
        HI_U32 u32ColorKey      :1;     /* Colorkey使能 */
        HI_U32 u32IcscSel      :1;      /* 输入颜色空间转换选择*/
        HI_U32 u32Clip          :1;     /* Clip使能 */
        HI_U32 u32MbMode        :3;     /* 宏块处理模式 */
        HI_U32 u32MbEn          :1;     /* 宏块操作使能 */
        HI_U32 u32AqIrqMask     :4;     /* 异步链表中断掩码 */
        HI_U32 u32SqIrqMask     :5;     /* 同步链表中断掩码 */
        HI_U32 u32OcsConv      :1;      /*输出颜色空间转换使能*/
        HI_U32 u32BlockFlag     :1;     /*是否分块标志*/
        HI_U32 u32FirstBlockFlag    :1; /*第一个分块标志*/
        HI_U32 u32LastBlockFlag     :1; /*最后一个分块标志*/
    }stBits;
    HI_U32 u32All;
}TDE_INS_U;

/* 源位图类型寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_SRC_TYPE_U
{
    struct
    {
        HI_U32 u32Pitch        :16;
        HI_U32 u32SrcColorFmt  :5;
        HI_U32 u32AlphaRange   :1;
#ifdef TDE_VERSION_MPW
        HI_U32 u32Reserve1     :2;  /* 保留 */
#else
        HI_U32 u32ColorizeEnable:1; /* Colorize使能，只对Src2有效;Src1为保留位 */
        HI_U32 u32Reserve1     :1;  /* 保留 */
#endif
        HI_U32 u32HScanOrd     :1;
        HI_U32 u32VScanOrd     :1;
        HI_U32 u32Reserve2     :3;
        HI_U32 u32RgbExp       :1;
        HI_U32 u32Reserve3     :2;
    }stBits;
    HI_U32 u32All;
}TDE_SRC_TYPE_U;

/* 位图起始位置寄存器配置格式 */
typedef union hiTDE_SUR_XY_U
{
    struct
    {
        HI_U32 u32X            :12; /* X首坐标 */
        HI_U32 u32Reserve1     :4;  /* 保留 */
        HI_U32 u32Y            :12; /* Y首坐标 */
        HI_U32 u32Reserve2     :4;  /* 保留 */
    }stBits;
    HI_U32 u32All;
}TDE_SUR_XY_U;

/* 位图尺寸寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_SUR_SIZE_U
{
    struct
    {
        HI_U32 u32Width        :12;             /* 图象宽度 */
        HI_U32 u32AlphaThresholdLow     :4;     /* alpha判决阈值低4位,在目标size寄存器中有效;在源2size寄存器中为保留位 */
        HI_U32 u32Height       :12;             /* 图象高度 */
        HI_U32 u32AlphaThresholdHigh     :4;    /* alpha判决阈值高4位,在目标size寄存器中有效;在源2size寄存器中为保留位*/
    }stBits;
    HI_U32 u32All;
}TDE_SUR_SIZE_U;

/* 目的位图类型寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_TAR_TYPE_U
{
    struct
    {
        HI_U32 u32Pitch        :16;
        HI_U32 u32TarColorFmt  :5;
        HI_U32 u32AlphaRange   :1;
        HI_U32 u32AlphaFrom    :2;
        HI_U32 u32HScanOrd     :1;
        HI_U32 u32VScanOrd     :1;
        HI_U32 u32RgbRound     :1;
        HI_U32 u32DfeLastlineOutEn  :1;
        HI_U32 u32DfeFirstlineOutEn :1;
        HI_U32 u32Reserve2     :3;
    }stBits;
    HI_U32 u32All;
}TDE_TAR_TYPE_U;

/* 颜色空间转换寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_COLOR_CONV_U
{
    struct
    {
        HI_U32 u32InColorImetry       :1;  /*输入色彩转换标准*/
        HI_U32 u32InRgb2Yc       :1;
        HI_U32 u32InColorSpace  :1;     /*输入色彩转换使用的矩阵*/
        HI_U32 u32InChromaFmt   :1;     /*输入色彩颜色格式*/
        HI_U32 u32OutColorImetry    :1; /*输出色彩转换标准*/
        HI_U32 u32OutColorSpace     :1; /*输出色彩转换使用的矩阵*/
        HI_U32 u32OutChromaFmt      :1; /*输出色彩颜色格式*/
        HI_U32 u32Reserve1       :2;
        HI_U32 u32ClutMod        :1;
        HI_U32 u32ClutReload     :1;
#ifdef TDE_VERSION_MPW
        HI_U32 u32Reserve2       :5;        /* 保留 */
#else
        HI_U32 u32Reserve2       :1;        /* 保留 */
        HI_U32 u32OcscReload	:1;	        /* 输出CSC自定义参数更新使能 */
        HI_U32 u32OcscCustomEn	:1;	        /* 自定义输出CSC使能*/
        HI_U32 u32IcscReload	:1;	        /* 输入CSC自定义参数更新使能 */
        HI_U32 u32IcscCustomEn	:1;	        /* 自定义输入CSC使能*/
#endif
        HI_U32 u32Alpha0         :8;
        HI_U32 u32Alpha1         :8;
    }stBits;
    HI_U32 u32All;
}TDE_COLOR_CONV_U;

/* 缩放寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_2D_RSZ_U
{
    struct
    {
        HI_U32 u32HfMod        :2;
        HI_U32 u32Reserve1     :2;
        HI_U32 u32VfMod        :2;
        HI_U32 u32Reserve2     :2;
        HI_U32 u32DfeMod       :2;
        HI_U32 u32Reserve3     :2;
        HI_U32 u32AlpBorder    :2;
        HI_U32 u32Reserve4     :2;
        HI_U32 u32VfRingEn     :1;
        HI_U32 u32HfRingEn     :1;
        HI_U32 u32CoefSym      :1;
        HI_U32 u32Reserve5     :5;
        HI_U32 u32VfCoefReload :1;
        HI_U32 u32HfCoefReload :1;
        HI_U32 u32DfeAlphaDisable   :1; /*alpha抗闪烁不使能*/
        HI_U32 u32Reserve6     :5;
    }stBits;
    HI_U32 u32All;
}TDE_2D_RSZ_U;

/* 位图尺寸寄存器配置格式,具体含义参考寄存器手册 */
typedef union hiTDE_ALU_U
{
    struct
    {
        HI_U32 u32AluMod        :4;
        HI_U32 u32AlphaThreshodEn      :1;
        HI_U32 u32AlphaRopMod   :4;
        HI_U32 u32RgbRopMod     :4;
        HI_U32 u32GlobalAlpha   :8;
        HI_U32 u32CkBMod        :2;
        HI_U32 u32CkGMod        :2;
        HI_U32 u32CkRMod        :2;
        HI_U32 u32CkAMod        :2;
        HI_U32 u32CkSel         :2;
        HI_U32 u32BlendReverse      :1; /*叠加前后背景反向使能*/
    }stBits;
    HI_U32 u32All;
}TDE_ALU_U;

/* ARGB/AYUV分量顺序寄存器格式 */
typedef union hiTDE_ARGB_ORDER_U
{
    struct
    {
        HI_U32 u32Src1ArgbOrder :   5;  /* Src1的ARGB排列顺序 */
        HI_U32 u32Reserved1 :   3;      /* 保留 */
        HI_U32 u32Src2ArgbOrder :   5;  /* Src2的ARGB排列顺序 */
        HI_U32 u32Reserved2 :   3;      /* 保留 */
        HI_U32 u32TarArgbOrder  :   5;  /* 目标的ARGB排列顺序 */
        HI_U32 u32Reserved3 :   3;      /* 保留 */
    }stBits;
    HI_U32 u32All;
}TDE_ARGB_ORDER_U;

/* Colorkey Mask寄存器 */
typedef union hiTDE_COLORKEY_MASK_U
{
    struct
    {
        HI_U32 u32BlueMask  :   8;  /* 蓝色分量/clut/V分量的mask */
        HI_U32 u32GreenMask :   8;  /* 绿色分量/U分量的mask */
        HI_U32 u32RedMask   :   8;  /* 红色分量/Y分量的mask */
        HI_U32 u32AlphaMask :   8;  /* Alpha分量的mask */
    }stBits;
    HI_U32 u32All;
}TDE_COLORKEY_MASK_U;

/* alpha blend模式寄存器 */
typedef union hiTDE2_ALPHA_BLEND_U
{
    struct
    {
        HI_U32 u32Src1BlendMode :       4;      /* Src1的叠加模式 */
        HI_U32 u32Src1PremultiEn :      1;      /* Src1预乘象素alpha使能 */
        HI_U32 u32Src1MultiGlobalEn :   1;      /* Src1预乘全局alpha使能 */
        HI_U32 u32Src1PixelAlphaEn    :   1;    /* Src1象素alpha使能 */
        HI_U32 u32Src1GlobalAlphaEn   :   1;    /* Src1全局alpha使能 */
        HI_U32 u32Src2BlendMode :       4;      /* Src2的叠加模式 */
        HI_U32 u32Src2PremultiEn :      1;      /* Src2预乘象素alpha使能 */
        HI_U32 u32Src2MultiGlobalEn :   1;      /* Src2预乘全局alpha使能 */
        HI_U32 u32Src2PixelAlphaEn    :   1;    /* Src2象素alpha使能 */
        HI_U32 u32Src2GlobalAlphaEn   :   1;    /* Src2全局alpha使能 */
        HI_U32 u32AlphaRopEn    :   1;          /* Alpha叠加时Alpha使能 */
        HI_U32 u32Reserved  :   15;             /* 保留 */
    }stBits;
    HI_U32 u32All;
}TDE_ALPHA_BLEND_U;

typedef union hiTDE_Y_PITCH
{
    struct
    {
        HI_U32 u32Pitch     :   16; /* 行跨度 */
        HI_U32 u32Reserved	:16;	/* 保留*/
    }stBits;
    HI_U32 u32All;
}TDE_Y_PITCH_U;

/* 滤波参数列表项 */
typedef union hiTDE_FILTER_PARA_U
{
    struct
    {
        HI_U32 u32Para0        :5;
        HI_U32 u32Para1        :6;
        HI_U32 u32Para2        :8;
        HI_U32 u32Para3        :7;
        HI_U32 u32Para4        :6;
    }stBits;
    HI_U32 u32All;
}TDE_FILTER_PARA_U;

/* 每个硬件节点信息链表,用于维护硬件节点 */
typedef struct hiTDE_BUF_NODE_S
{
    struct list_head stList;
    HI_U32 u32PhyAddr;              /*指向硬件buffer物理地址*/
    HI_U32* pu32VirAddr;            /*硬件buffer对应的虚拟地址*/
    HI_S32 s32Handle;               /*当前节点所属的job handle*/
    HI_VOID* pSwNode;               /*当前节点指向的软件节点指针*/
    HI_U32 u32WordSize;             /*当前节点配置项所需大小(字为单位)*/
    HI_U32 u32CurUpdate;            /*当前节点更新标记*/
    struct hiTDE_BUF_NODE_S* pstParentAddr;/*被继承配置信息的父节点地址*/
}TDE_BUF_NODE_S;


/* TDE操作挂起时的状态信息 */
typedef struct hiTDE_SUSP_STAT_S
{
    HI_S32 s32AqSuspLine;       /*Aq挂起时执行到的行,如果为-1表示无效*/
    TDE_BUF_NODE_S* pstSwBuf;
    HI_VOID *pSwNode;       /*指向挂起的软件节点的指针*/
}TDE_SUSP_STAT_S;

/* 配置参数表首地址 */
typedef struct hiTDE_PARA_TABLE_S
{
    HI_U32 u32HfCoefAddr;
    HI_U32 u32VfCoefAddr;
}TDE_PARA_TABLE_S;

/****************************************************************************/
/*                             TDE hal 内部变量定义                         */
/****************************************************************************/
/* 映射后寄存器基地址 */
STATIC volatile HI_U32* s_pu32BaseVirAddr = HI_NULL;

/* Aq挂起时的状态信息 */
STATIC TDE_SUSP_STAT_S s_stSuspStat = {0};

/* 配置参数表首地址 */
STATIC TDE_PARA_TABLE_S s_stParaTable = {0};

#ifdef TDE_PROC_ENABLE
/* proc打印需要的全局变量 */
extern HI_U32 g_u32TdeAqCurProcNum;
extern HI_U32 g_u32TdeSqCurProcNum;


#endif

/** 抗闪烁级别 默认为自动 */
STATIC TDE_DEFLICKER_LEVEL_E s_eDeflickerLevel = TDE_DEFLICKER_AUTO;

/*alpha判决开关*/
STATIC HI_BOOL s_bEnAlphaThreshold = HI_FALSE;

/*alpha判决阈值*/
STATIC HI_U8 s_u8AlphaThresholdValue = 0xff;
#define TDE_CSCTABLE_SIZE 7

STATIC HI_U32 s_u32Rgb2YuvCsc[TDE_CSCTABLE_SIZE] = 
    {0x0096004d, 0xffd5001d, 0x0080ffab, 0xff950080, 0x0000ffeb, 0x00000000, 0x02010000};
STATIC HI_U32 s_u32Yuv2RgbCsc[TDE_CSCTABLE_SIZE] = 
    {0x00000100, 0x01000167, 0xff49ffa8, 0x01c60100, 0x00000000, 0x06030000, 0x00000000};

STATIC HI_U32 s_u32Rgb2YuvCoefAddr = 0;
STATIC HI_U32 s_u32Yuv2RgbCoefAddr = 0;
/****************************************************************************/
/*                             TDE hal 内部函数定义                         */
/****************************************************************************/
STATIC HI_S32 TdeHalInitParaTable(HI_VOID);
STATIC HI_VOID TdeHalNodeSetSrc2Base(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, HI_BOOL bS2Size);
STATIC HI_S32  TdeHalGetbppByFmt(TDE_DRV_COLOR_FMT_E enFmt);
STATIC  HI_U32 TdeHalGetResizeParaHTable(HI_U32 u32Step);
STATIC  HI_U32 TdeHalGetResizeParaVTable(HI_U32 u32Step);
//STATIC  TDE_NODE_BUF_S* TdeHalUpdateChildBuf(TDE_NODE_BUF_S* pNodeBuf);
STATIC  HI_VOID TdeHalSetXyByAdjInfo(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo);
STATIC  HI_VOID TdeHalInitQueue(HI_VOID);

/****************************************************************************/
/*                             TDE hal ctl 接口实现                         */
/****************************************************************************/
/*****************************************************************************
* Function:      TdeHalInit
* Description:   主要用于映射TDE基地址
* Input:         u32BaseAddr:寄存器基地址
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_VOID TdeHalSetClock(HI_VOID)
{
    U_PERI_CRG37 unTempValue;

    unTempValue.u32 = g_pstRegCrg->PERI_CRG37.u32;
    
    /*cancel reset*/
    unTempValue.bits.tde_srst_req = 0x0;

    /*enable clock*/
    unTempValue.bits.tde_cken = 0x1;

    g_pstRegCrg->PERI_CRG37.u32 = unTempValue.u32;
    
    return;
}

HI_S32 TdeHalInit(HI_U32 u32BaseAddr)
{
    /*初始化TDE内存池*/
    if (HI_SUCCESS != wmeminit())
    {
        goto TDE_INIT_ERR;
    }

    /* 配置参数表首地址 */
    if (HI_SUCCESS != TdeHalInitParaTable())
    {
        goto TDE_INIT_ERR;
    }

    /* 寄存器映射 */
    s_pu32BaseVirAddr = (volatile HI_U32*)TDE_REG_MAP(u32BaseAddr, TDE_REG_SIZE);
    if(HI_NULL == s_pu32BaseVirAddr)
	{
        goto TDE_INIT_ERR;
	}

    TdeHalSetClock();

    /* 寄存器复位 */    
	TdeHalCtlReset();

    /* 初始化SQ/AQ */
    TdeHalInitQueue(); 
    
    return HI_SUCCESS;

TDE_INIT_ERR:
    return HI_FAILURE;
}

/*****************************************************************************
* Function:      TdeHalOpen
* Description:   主要用于初始化必须的寄存器
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32 TdeHalOpen(HI_VOID)
{
    /* do sth ... */
    return HI_SUCCESS;
}

/*****************************************************************************
* Function:      TdeHalRelease
* Description:   主要用于释放映射的TDE基地址
* Input:         无
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
HI_VOID TdeHalRelease(HI_VOID)
{
    HI_VOID *pBuf;
    if(0 != s_stParaTable.u32HfCoefAddr)
    {
        HI_VOID *pHfCoef = (HI_VOID *)wgetvrt(s_stParaTable.u32HfCoefAddr);
        if (pHfCoef != NULL)
            TDE_FREE(pHfCoef);
    }
    if (0 != s_stParaTable.u32VfCoefAddr)
    {
        HI_VOID *pVfCoef = (HI_VOID *)wgetvrt(s_stParaTable.u32VfCoefAddr);
        if (pVfCoef != NULL)
            TDE_FREE(pVfCoef);
    }
    #ifdef TDE_CSC_ENABLE
    if (0 != s_u32Rgb2YuvCoefAddr)
    {
        pBuf = (HI_VOID *)wgetvrt(s_u32Rgb2YuvCoefAddr);
        if (HI_NULL != pBuf)
        {
            TDE_FREE(pBuf);
            s_u32Rgb2YuvCoefAddr = 0;
        }
    }

    if (0 != s_u32Yuv2RgbCoefAddr)
    {
        pBuf = (HI_VOID *)wgetvrt(s_u32Yuv2RgbCoefAddr);
        if (HI_NULL != pBuf)
        {
            TDE_FREE(pBuf);
            s_u32Yuv2RgbCoefAddr = 0;
        }
    }
#endif


    
    /* 反映射基地址 */
    TDE_REG_UNMAP(s_pu32BaseVirAddr);
    s_pu32BaseVirAddr = HI_NULL;

    /*TDE内存池去初始化*/
    wmemterm();
    
    return;
}

/*****************************************************************************
* Function:      TdeHalCtlIsIdle
* Description:   查询TDE是否处于IDLE状态
* Input:         无
* Output:        无
* Return:        True: Idle/False: Busy
* Others:        无
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdle(HI_VOID)
{
    return (HI_BOOL)(!(TDE_READ_REG(s_pu32BaseVirAddr, TDE_STA) & 0x1));
}

/*****************************************************************************
* Function:      TdeHalCtlIsIdleSafely
* Description:   循环多次查询, 确保TDE是否处于IDLE状态
* Input:         无
* Output:        无
* Return:        True: Idle/False: Busy
* Others:        无
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdleSafely(HI_VOID)
{
    HI_U32 i = 0;
    
    /* 连续读取多次硬件状态,确保TDE完成 */
    for (i = 0; i < TDE_MAX_READ_STATUS_TIME; i++)
    {
        /* 只要有一次非IDLE, 就认为是非IDLE */
        if (!TdeHalCtlIsIdle())
        {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

/*****************************************************************************
* Function:      TdeHalCtlIntMask
* Description:   获取Sq/Aq的中断状态
* Input:         enListType: 设置Sq/Aq的类型
* Output:        无
* Return:        Sq/Aq中断状态
* Others:        无
*****************************************************************************/
HI_U32 TdeHalCtlIntStats(HI_VOID)
{
    HI_U32 Value;

    Value = TDE_READ_REG(s_pu32BaseVirAddr, TDE_INT);
    /* clear all status */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_INT, (Value)/*0x800f001f*/);

    return Value;
}

/*****************************************************************************
* Function:      TdeHalResetStatus
* Description:   复位TDE HAL所有状态,清除所有链表
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalResetStatus(HI_VOID)
{
    s_stSuspStat.s32AqSuspLine = TDE_SUSP_LINE_INVAL;
    s_stSuspStat.pSwNode = HI_NULL;
    return;
}

/*****************************************************************************
* Function:      TdeHalCtlReset
* Description:   软复位，请中断状态
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalCtlReset(HI_VOID)
{
    /* 复位 */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_RST, 0xffffffff);

    /* 请中断状态 */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_INT, 0x800f001f);
}

/*****************************************************************************
* Function:      TdeHalCtlIntClear
* Description:   清相应的中断状态
* Input:         enListType: 设置Sq/Aq的类型
*                u32Stats: 清相应的中断状态
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalCtlIntClear(TDE_LIST_TYPE_E enListType, HI_U32 u32Stats)
{
    HI_U32 u32ReadStats = 0;

    u32ReadStats = TDE_READ_REG(s_pu32BaseVirAddr, TDE_INT);
    if (TDE_LIST_AQ == enListType)
    {
        u32ReadStats = (u32ReadStats & 0x0000ffff) | ((u32Stats << 16) & 0xffff0000);
    }
    else
    {
        u32ReadStats = (u32ReadStats & 0xffff0000) | (u32Stats & 0x0000ffff);
    }
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_INT, u32ReadStats);
}

/*判断TDE的工作队列是同步还是异步*/
HI_BOOL TdeHalIsSqWork()
{
    return (HI_BOOL)((TDE_READ_REG(s_pu32BaseVirAddr, TDE_STA) & 0x4) >> 2);
}

/****************************************************************************/
/*                             TDE hal node 接口实现                        */
/****************************************************************************/
/*****************************************************************************
* Function:      TdeHalNodeInitNd
* Description:   初始化软件缓存的一个TDE操作节点所需的结构
* Input:         pHWNode: 软件用于缓存的节点结构指针
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeInitNd(TDE_HWNode_S* pHWNode, HI_BOOL bChild)
{
    TDE_INS_U unIns;

    TDE_ASSERT(HI_NULL != pHWNode);

    /* 如果是子节点, 还需要父节点的设置信息,只把Update清空 */
    if (bChild)
    {
        TDE_2D_RSZ_U unRsz;
	    HI_BOOL bClipOut = pHWNode->u32TDE_CLIP_START >> 31;
	  
        unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
        unRsz.stBits.u32VfCoefReload = 0;/* 如果是子节点则不需要更新参数表 */
        unRsz.stBits.u32HfCoefReload = 0;
        pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
        pHWNode->u64TDE_UPDATE = 0;
        TDE_SET_UPDATE(u32TDE_2D_RSZ, pHWNode->u64TDE_UPDATE);

	 if(bClipOut)
	 {
        TDE_SET_UPDATE(u32TDE_CLIP_START, pHWNode->u64TDE_UPDATE);
        TDE_SET_UPDATE(u32TDE_CLIP_STOP, pHWNode->u64TDE_UPDATE);
	 }
    }
    else /* 否则所有信息清空 */
    {
        memset(pHWNode, 0, sizeof(TDE_HWNode_S));
    }
    
    /* 开启链表完成中断,同步链表可更新中断, 关闭节点完成中断 */
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32SqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    unIns.stBits.u32AqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    pHWNode->u32TDE_INS = unIns.u32All;
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
}

/* AE5D03390:软件规避区域外clip bug */

HI_VOID TdeHalNodeInitChildNd(TDE_HWNode_S* pHWNode, HI_U32 u32TDE_CLIP_START, HI_U32 u32TDE_CLIP_STOP)
{
#ifndef HIGO_CODE_CUT
    TDE_INS_U unIns;
	TDE_2D_RSZ_U unRsz;
	HI_BOOL bClipOut = pHWNode->u32TDE_CLIP_START >> 31;

    TDE_ASSERT(HI_NULL != pHWNode);

    /* 如果是子节点, 还需要父节点的设置信息,只把Update清空 */

	unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
	unRsz.stBits.u32VfCoefReload = 0;/* 如果是子节点则不需要更新参数表 */
	unRsz.stBits.u32HfCoefReload = 0;
	pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
	pHWNode->u64TDE_UPDATE = 0;
	TDE_SET_UPDATE(u32TDE_2D_RSZ, pHWNode->u64TDE_UPDATE);

	if(bClipOut)
	{
	    pHWNode->u32TDE_INS = pHWNode->u32TDE_INS | 0x4000; /* 开启clip 功能*/
	    pHWNode->u32TDE_CLIP_START = u32TDE_CLIP_START;
	    pHWNode->u32TDE_CLIP_STOP = u32TDE_CLIP_STOP;
	    TDE_SET_UPDATE(u32TDE_CLIP_START, pHWNode->u64TDE_UPDATE);
	    TDE_SET_UPDATE(u32TDE_CLIP_STOP, pHWNode->u64TDE_UPDATE);
	}
    
    /* 开启链表完成中断,同步链表可更新中断, 关闭节点完成中断 */
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32SqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    unIns.stBits.u32AqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    pHWNode->u32TDE_INS = unIns.u32All;
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    #endif
}

/*****************************************************************************
* Function:      TdeHalNodeGetNdSize
* Description:   获取当前功能配置下的节点所需多少个字(4字节)
* Input:         pHWNode: 软件用于缓存的节点结构指针
* Output:        无
* Return:        返回所需字节数
* Others:        无
*****************************************************************************/
HI_U32 TdeHalNodeGetNdSize(TDE_HWNode_S* pHWNode)
{
    HI_S32 u32Size = 0;
    HI_U32 i = 0;

    TDE_ASSERT(HI_NULL != pHWNode);

    /* 统计u32TDE_UPDATE中的有效设置,计算当前配置下所需大小 */
    for (i = 0; i < sizeof(TDE_HWNode_S)/4 - 2; i++)
    {
        if ( 1 == ((pHWNode->u64TDE_UPDATE >> i) & 1) )
        {
            u32Size++;
        }
    }
    return (u32Size << 0x2);/* 根据Word返回字节数 */
}

/*****************************************************************************
* Function:      TdeHalNodeMakeNd
* Description:   由当前功能配置下的节点pHWNode,制作成可以直接配置的节点到pBuf中
* Input:         pBuf: 制作节点后缓存节点的buffer
*                pHWNode: 软件用于缓存的节点结构指针
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32 TdeHalNodeMakeNd(HI_VOID* pBuf, TDE_HWNode_S* pHWNode)
{
    HI_U32 *pNodeBuf = (HI_U32*)pBuf;
    HI_U32 *pu32Node = (HI_U32*)pHWNode;
    HI_U32 i = 0;
    
    TDE_ASSERT(HI_NULL != pBuf);
    TDE_ASSERT(HI_NULL != pHWNode);

    /* 将pHWNode中的有效数据复制到保存节点的buffer中 */
    for (i = 0; i < (sizeof(TDE_HWNode_S) - sizeof(pHWNode->u64TDE_UPDATE))/4; i++)
    {
        if ( 1 == ((pHWNode->u64TDE_UPDATE >> i) & 1) )
        {
            *(pNodeBuf++) = *(pu32Node + i);
        }
    }

    return HI_SUCCESS;
}

/*****************************************************************************
* Function:      TdeHalNodeExecute
* Description:   启动TDE链表
* Input:         enListType: 链表类型
*                u32NodePhyAddr: 链表首节点地址
*                u32Update:链表首节点更新标识
*                bAqUseBuff: 是否使用临时buffer
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_S32 TdeHalNodeExecute(TDE_LIST_TYPE_E enListType, HI_U32 u32NodePhyAddr, HI_U64 u64Update, HI_BOOL bAqUseBuff)
{
    TDE_AQ_CTRL_U unAqCtrl;
#ifndef HIGO_CODE_CUT      
    TDE_SQ_CTRL_U unSqCtrl;
#endif    
    if (enListType == TDE_LIST_AQ)
    {
        /*TDE空闲*/
        if(TdeHalCtlIsIdle())
        {
            /*写入首节点地址*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_NADDR, u32NodePhyAddr);

            /*写入首节点更新标识*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_UPDATE, (HI_U32)(u64Update & 0xffffffff));
#if defined (TDE_VERSION_PILOT) || defined (TDE_VERSION_FPGA)
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_UPDATE2, (HI_U32)((u64Update >> 32) & 0xffffffff));
#endif

            unAqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_AQ_CTRL);

            /*若需要使用临时buffer,则打断模式为当前节点完成打断；否则为当前节点
               当前行完成打断*/
            if (HI_TRUE ==  bAqUseBuff)
            {
                unAqCtrl.stBits.u32AqOperMode = TDE_AQ_CTRL_COMP_LIST;
                TDE_TRACE(TDE_KERN_INFO,"Aq Ctrl use comp list mode\n");
            }
            else
            {
                unAqCtrl.stBits.u32AqOperMode = TDE_AQ_CTRL_COMP_LINE;
                TDE_TRACE(TDE_KERN_INFO,"Aq Ctrl use comp node line mode\n");
            }

            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_CTRL, unAqCtrl.u32All);

            //cleanDcache();
            
            /* 启动Aq*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_CTRL, 0x1);   
        }
        else
        {
            return HI_FAILURE;
        }
    }
#ifndef HIGO_CODE_CUT  
    else
    {
        /*TDE空闲或异步链表在工作，都可提交同步链表*/
        if(TdeHalCtlIsIdle() || ((TDE_READ_REG(s_pu32BaseVirAddr, TDE_STA) & 0x4) >> 2))
        {
            /*写入首节点地址*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_NADDR, u32NodePhyAddr);

            /*写入首节点更新标识*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_UPDATE, (HI_U32)(u64Update & 0xffffffff));
            
#if defined (TDE_VERSION_PILOT) || defined (TDE_VERSION_FPGA)
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_UPDATE2, (HI_U32)((u64Update >> 32) & 0xffffffff));
#endif
            /*使能同步链表*/
            unSqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL);

            unSqCtrl.stBits.u32SqEn = 0x1;
            unSqCtrl.stBits.u32SqUpdateFlag = 0x1;

            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL, unSqCtrl.u32All);

            /* 启动Sq*/
            //TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_CTRL, 0x101);
        }
        else
        {
            return HI_FAILURE;
        }
    }
 #endif   
    return HI_SUCCESS;
}



/*****************************************************************************
* Function:      TdeHalNodeSetSrc1
* Description:   设置源1位图信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvSurface: 用于设置的位图信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc1(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface)
{
    TDE_SRC_TYPE_U unSrcType;
    TDE_SUR_XY_U unXy;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvSurface);

    /*配置源位图属性信息*/
    unSrcType.u32All = pHWNode->u32TDE_S1_TYPE;
    unSrcType.stBits.u32Pitch = (HI_U32)pDrvSurface->u32Pitch;
    unSrcType.stBits.u32SrcColorFmt = (HI_U32)pDrvSurface->enColorFmt;
    unSrcType.stBits.u32AlphaRange = (HI_U32)pDrvSurface->bAlphaMax255;
    unSrcType.stBits.u32HScanOrd = (HI_U32)pDrvSurface->enHScan;
    unSrcType.stBits.u32VScanOrd = (HI_U32)pDrvSurface->enVScan;
    unSrcType.stBits.u32RgbExp = 0; /*一直使用低位填充为0,高位使用低位的扩展方式*/

    unXy.u32All = pHWNode->u32TDE_S1_XY;
    unXy.stBits.u32X = pDrvSurface->u32Xpos;
    unXy.stBits.u32Y = pDrvSurface->u32Ypos;

    /*源1位图宽高总是与Target位图一致,因此不设置源1的大小*/

    /*配置缓存节点*/
    pHWNode->u32TDE_S1_ADDR = pDrvSurface->u32PhyAddr;
    pHWNode->u32TDE_S1_TYPE = unSrcType.u32All;
    pHWNode->u32TDE_S1_XY = unXy.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_S1_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S1_TYPE, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);
    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetSrc2
* Description:   设置源2位图信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvSurface: 用于设置的位图信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc2(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface)
{
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvSurface);

    TdeHalNodeSetSrc2Base(pHWNode, pDrvSurface, HI_TRUE);
    return;
}

HI_VOID TdeHalNodeSetCsc(TDE_HWNode_S* pHWNode, TDE2_CSC_OPT_S *pstCscOpt)
{
    #ifdef TDE_CSC_ENABLE
    TDE_COLOR_CONV_U unColorConv;
    TDE_INS_U unIns;

    TDE_ASSERT(HI_NULL != pHWNode);

    unColorConv.u32All = pHWNode->u32TDE_COLOR_CONV;
        unIns.u32All = pHWNode->u32TDE_INS;

    unColorConv.stBits.u32IcscCustomEn = pstCscOpt->bICSCUserEnable;
    unColorConv.stBits.u32IcscReload = pstCscOpt->bICSCParamReload;
    unColorConv.stBits.u32OcscCustomEn = pstCscOpt->bOCSCUserEnable;
    unColorConv.stBits.u32OcscReload = pstCscOpt->bOCSCParamReload;

    pHWNode->u32TDE_ICSC_ADDR = pstCscOpt->u32ICSCParamAddr;
    pHWNode->u32TDE_OCSC_ADDR = pstCscOpt->u32OCSCParamAddr;

    	/*use correct parameter when user not use user parameter and enable ICSC function*/
        /*CNcomment:若用户未开启自定义系数且ICSC功能使能,
        则强制使用TDE的修正系数(TDE默认系数存在问题)*/
        if (!pstCscOpt->bICSCUserEnable && unIns.stBits.u32IcsConv)
        {
            unColorConv.stBits.u32IcscCustomEn = 1;
        unColorConv.stBits.u32IcscReload = 1;
        if (unColorConv.stBits.u32InRgb2Yc)
            {
                pHWNode->u32TDE_ICSC_ADDR = s_u32Rgb2YuvCoefAddr;
            }
        else
            {
                pHWNode->u32TDE_ICSC_ADDR = s_u32Yuv2RgbCoefAddr;
            }
        }

        if (!pstCscOpt->bOCSCUserEnable && unIns.stBits.u32OcsConv)
        {
            unColorConv.stBits.u32OcscCustomEn = 1;
        unColorConv.stBits.u32OcscReload = 1;
        if (unColorConv.stBits.u32InRgb2Yc)
            {
                pHWNode->u32TDE_OCSC_ADDR = s_u32Yuv2RgbCoefAddr;
            }
        else
            {
                pHWNode->u32TDE_OCSC_ADDR = s_u32Rgb2YuvCoefAddr;
            }
        }

        pHWNode->u32TDE_COLOR_CONV = unColorConv.u32All;

    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_ICSC_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_OCSC_ADDR, pHWNode->u64TDE_UPDATE);
#endif

	return;
}

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
HI_VOID TdeHalNodeSetSrcMbY(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbY, TDE_DRV_MB_OPT_MODE_E enMbOpt)
{
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvMbY);

    if (TDE_MB_RASTER_OPT == enMbOpt)
    {
        /* 如果是宏块与光栅混合操作模式,亮度信息直接设置到Src2中 */
        TdeHalNodeSetSrc2(pHWNode, pDrvMbY);

        return;
    }
    else
    {
        TdeHalNodeSetSrc1(pHWNode, pDrvMbY);
    }

    if (TDE_MB_Y_FILTER == enMbOpt || TDE_MB_CONCA_FILTER == enMbOpt)
    {
        TDE_SUR_SIZE_U unSurSize;
        unSurSize.u32All = pHWNode->u32TDE_S2_SIZE;
        /*当为如上类型时,需要配置源2的大小,作为位图大小信息*/
        unSurSize.stBits.u32Width = (HI_U32)pDrvMbY->u32Width;
        unSurSize.stBits.u32Height = (HI_U32)pDrvMbY->u32Height;
        pHWNode->u32TDE_S2_SIZE = unSurSize.u32All;
        TDE_SET_UPDATE(u32TDE_S2_SIZE, pHWNode->u64TDE_UPDATE);
    }

    return;
}

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
HI_VOID TdeHalNodeSetSrcMbCbCr(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbCbCr, TDE_DRV_MB_OPT_MODE_E enMbOpt)
{
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvMbCbCr);
    
    if (TDE_MB_Y_FILTER == enMbOpt || TDE_MB_CONCA_FILTER == enMbOpt)
    {
        TdeHalNodeSetSrc2Base(pHWNode, pDrvMbCbCr, HI_FALSE);
    }
    else
    {
        TdeHalNodeSetSrc2Base(pHWNode, pDrvMbCbCr, HI_TRUE);
    }

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetTgt
* Description:   设置目的位图信息
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pDrvSurface: 用于设置的位图信息
*                enAlphaFrom: alpha from
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetTgt(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, TDE_DRV_OUTALPHA_FROM_E enAlphaFrom)
{
    TDE_TAR_TYPE_U unTarType;
    TDE_SUR_SIZE_U unSurSize;
    TDE_SUR_XY_U unXy;
    
    TDE_ASSERT(HI_NULL != pHWNode);

    /*配置源位图属性信息*/
    unTarType.u32All = pHWNode->u32TDE_TAR_TYPE;
    unTarType.stBits.u32Pitch = (HI_U32)pDrvSurface->u32Pitch;
    unTarType.stBits.u32TarColorFmt = (HI_U32)pDrvSurface->enColorFmt;
    unTarType.stBits.u32AlphaRange = (HI_U32)pDrvSurface->bAlphaMax255;
    unTarType.stBits.u32HScanOrd = (HI_U32)pDrvSurface->enHScan;
    unTarType.stBits.u32VScanOrd = (HI_U32)pDrvSurface->enVScan;
    unTarType.stBits.u32AlphaFrom = (HI_U32)enAlphaFrom;
    unTarType.stBits.u32RgbRound = 0; /*一直使用使用四舍无入的截位方式*/

    /*配置位图大小信息*/
    unSurSize.u32All = pHWNode->u32TDE_TS_SIZE;
    unSurSize.stBits.u32Width = (HI_U32)pDrvSurface->u32Width;
    unSurSize.stBits.u32Height = (HI_U32)pDrvSurface->u32Height;

    /*设置alpha判决阈值 */
#ifdef TDE_VERSION_MPW
    unSurSize.stBits.u32AlphaThresholdHigh = ((s_u8AlphaThresholdValue >>1) >> 4); //change the range 0-128
    unSurSize.stBits.u32AlphaThresholdLow = ((s_u8AlphaThresholdValue >>1) & 0x0f);
#else
    unSurSize.stBits.u32AlphaThresholdHigh = (s_u8AlphaThresholdValue >> 4); //change the range 0-255
    unSurSize.stBits.u32AlphaThresholdLow = (s_u8AlphaThresholdValue & 0x0f);
#endif
    unXy.u32All = pHWNode->u32TDE_TAR_XY;
    unXy.stBits.u32X = pDrvSurface->u32Xpos;
    unXy.stBits.u32Y = pDrvSurface->u32Ypos;


    /*配置缓存节点*/
    pHWNode->u32TDE_TAR_ADDR = pDrvSurface->u32PhyAddr;
    pHWNode->u32TDE_TAR_TYPE = unTarType.u32All;
    pHWNode->u32TDE_TAR_XY = unXy.u32All;
    pHWNode->u32TDE_TS_SIZE = unSurSize.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_TAR_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_TAR_TYPE, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_TAR_XY, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_TS_SIZE, pHWNode->u64TDE_UPDATE);
    
    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetBaseOperate
* Description:   设置基本操作类型
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                enMode: 基本操作模式
*                enAlu: ALU模式
*                pstColorFill: 如果基本操作模式中有填充操作,则读取此值
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetBaseOperate(TDE_HWNode_S* pHWNode, TDE_DRV_BASEOPT_MODE_E enMode,
                                 TDE_DRV_ALU_MODE_E enAlu, TDE_DRV_COLORFILL_S *pstColorFill)
{
    TDE_ALU_U unAluMode;
    TDE_INS_U unIns;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    
    unAluMode.u32All = pHWNode->u32TDE_ALU;
    unIns.u32All = pHWNode->u32TDE_INS;
    unAluMode.stBits.u32AlphaThreshodEn = (s_bEnAlphaThreshold)?1:0;

    switch (enMode)
    {
    case TDE_QUIKE_FILL:/*快速填充*/
        {
            TDE_ASSERT(HI_NULL != pstColorFill);
            if (HI_NULL == pstColorFill)
            {
                return;
            }
            TDE_FILL_DATA_BY_FMT(pHWNode->u32TDE_S1_FILL, 
                pstColorFill->u32FillData, pstColorFill->enDrvColorFmt);
            TDE_SET_UPDATE(u32TDE_S1_FILL, pHWNode->u64TDE_UPDATE);
            
            unAluMode.stBits.u32AluMod = TDE_SRC1_BYPASS;
            unIns.stBits.u32Src1Mod = TDE_SRC_QUICK_FILL;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_DISA;
        }
        break;
#ifndef HIGO_CODE_CUT  
    case TDE_QUIKE_COPY:/*快速拷贝*/
        {
            unAluMode.stBits.u32AluMod = TDE_SRC1_BYPASS;
            unIns.stBits.u32Src1Mod = TDE_SRC_QUICK_COPY;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_DISA;
        }
        break;
    case TDE_NORM_FILL_1OPT:/*普通单源填充*/
        {
            TDE_ASSERT(HI_NULL != pstColorFill);
            if (HI_NULL == pstColorFill)
            {
                return;
            }
            TDE_FILL_DATA_BY_FMT(pHWNode->u32TDE_S2_FILL, 
                pstColorFill->u32FillData, pstColorFill->enDrvColorFmt);
            
            TDE_SET_UPDATE(u32TDE_S2_FILL, pHWNode->u64TDE_UPDATE);
            
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_DISA;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_FILL;
            if (TDE_ALU_NONE == enAlu)
            {
                unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
            }
            else
            {
                unAluMode.stBits.u32AluMod = (HI_U32)enAlu;
            }
        }
        break;
    case TDE_NORM_BLIT_1OPT:/*普通单源操作搬移*/
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_DISA;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_BMP;
            if (TDE_ALU_NONE == enAlu)
            {
                unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
            }
            else
            {
                unAluMode.stBits.u32AluMod = (HI_U32)enAlu;
            }
        }
        break;
    
    case TDE_NORM_FILL_2OPT:/*单色和位图运算操作搬移*/
        {
            TDE_ASSERT(HI_NULL != pstColorFill);
            if (HI_NULL == pstColorFill)
            {
                return;
            }
            TDE_FILL_DATA_BY_FMT(pHWNode->u32TDE_S2_FILL, 
                pstColorFill->u32FillData, pstColorFill->enDrvColorFmt);
            TDE_SET_UPDATE(u32TDE_S2_FILL, pHWNode->u64TDE_UPDATE);
            
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_FILL;
            if (TDE_ALU_NONE == enAlu)
            {
                unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
            }
            else
            {
                unAluMode.stBits.u32AluMod = (HI_U32)enAlu;
            }
        }
        break;
#endif            
    case TDE_NORM_BLIT_2OPT:/*普通双源操作搬移 */
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_BMP;
            if(TDE_ALU_NONE == enAlu)
            {
                unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
            }
            else
            {
                unAluMode.stBits.u32AluMod = (HI_U32)enAlu;
            }
        }
        break;
    case TDE_MB_2OPT:/*宏块合并操作*/
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32MbEn = 1;
            if (TDE_ALU_CONCA == enAlu)
            {
                unAluMode.stBits.u32AluMod = TDE_ALU_CONCA;
            }
            else if (TDE_ALU_NONE == enAlu)
            {
                unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;

            }
            else
            {
                unAluMode.stBits.u32AluMod = enAlu;
            }
        }
        break;
    case TDE_MB_C_OPT:/*宏块色度上采样操作*/
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_DISA;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32MbEn = 1;
            unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
        }
        break;
    case TDE_MB_Y_OPT:/*宏块亮度缩放*/
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_DISA;
            unIns.stBits.u32MbEn = 1;
            unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
        }
        break;
#ifndef HIGO_CODE_CUT     
    case TDE_SINGLE_SRC_PATTERN_FILL_OPT:
    {
        unIns.stBits.u32Src1Mod = TDE_SRC_MODE_DISA;
        unIns.stBits.u32Src2Mod = TDE_SRC_MODE_PATTERN;
        if (TDE_ALU_NONE != enAlu)
        {
            unAluMode.stBits.u32AluMod = enAlu;
        }
        else
        {
            unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
        }
        break;
    }
    case TDE_DOUBLE_SRC_PATTERN_FILL_OPT:
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_PATTERN;
            if (TDE_ALU_NONE != enAlu)
            {
                unAluMode.stBits.u32AluMod = enAlu;
            }
            else
            {
                unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
            }
            break;
        }
   #endif 
    default:
        break;
    }

    /*配置缓存节点*/
    pHWNode->u32TDE_ALU = unAluMode.u32All;
    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetGlobalAlpha
* Description:   设置Alpha混合参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                u8Alpha: Alpha混合设置值
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

HI_VOID TdeHalNodeSetGlobalAlpha(TDE_HWNode_S* pHWNode, HI_U8 u8Alpha)
{
#ifndef HIGO_CODE_CUT
    TDE_ALU_U unAluMode;

    TDE_ASSERT(HI_NULL != pHWNode);

    TDE_ALPHA_ADJUST(u8Alpha);
    
    /*配置缓存节点*/
    unAluMode.u32All = pHWNode->u32TDE_ALU;
    unAluMode.stBits.u32GlobalAlpha = u8Alpha;
    pHWNode->u32TDE_ALU = unAluMode.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);

    return;
    #endif
}

#if 1
/*****************************************************************************
* Function:      TdeHalNodeSetExpAlpha
* Description:   当对RGB5551作Alpha扩展时,扩展为alpha0, alpha1的设置
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                u8Alpha0: Alpha0设置值
*                u8Alpha1: Alpha1设置值
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetExpAlpha(TDE_HWNode_S* pHWNode, TDE_DRV_SRC_E enSrc, HI_U8 u8Alpha0, HI_U8 u8Alpha1)
{
    TDE_COLOR_CONV_U unConv;
    
    TDE_ASSERT(HI_NULL != pHWNode);

    TDE_ALPHA_ADJUST(u8Alpha0);
    TDE_ALPHA_ADJUST(u8Alpha1);
    
    /*配置alpha0, alpha1*/
    unConv.u32All = pHWNode->u32TDE_COLOR_CONV;
    unConv.stBits.u32Alpha0 = u8Alpha0;
    unConv.stBits.u32Alpha1 = u8Alpha1;
    pHWNode->u32TDE_COLOR_CONV = unConv.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);

    if(TDE_DRV_SRC_S1 & enSrc)
    {
        pHWNode->u32TDE_S1_TYPE |= 0x20000000;
        
        /*HWNode.TDE_UPDATE中有配置项对应位设1*/
        TDE_SET_UPDATE(u32TDE_S1_TYPE, pHWNode->u64TDE_UPDATE);
    }

    if(TDE_DRV_SRC_S2 & enSrc)
    {
        pHWNode->u32TDE_S2_TYPE |= 0x20000000;
        
        /*HWNode.TDE_UPDATE中有配置项对应位设1*/
        TDE_SET_UPDATE(u32TDE_S2_TYPE, pHWNode->u64TDE_UPDATE);
    }

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetAlphaBorder
* Description:   设置是否使能Alplha边界处理
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                bEnable: 是否使能Alplha边界
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
#ifndef HIGO_CODE_CUT
HI_VOID TdeHalNodeSetAlphaBorder(TDE_HWNode_S* pHWNode, HI_BOOL bVEnable, HI_BOOL bHEnable)
{
    TDE_2D_RSZ_U unRsz;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
    unRsz.stBits.u32AlpBorder = (((HI_U32)bVEnable << 1) | (HI_U32)bHEnable);
    pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
    
    TDE_SET_UPDATE(u32TDE_2D_RSZ, pHWNode->u64TDE_UPDATE);
    return;
}
#endif
#endif

/*****************************************************************************
* Function:      TdeHalNodeSetRop
* Description:   设置ROP运算参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                enRopCode: ROP运算码
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

HI_VOID TdeHalNodeSetRop(TDE_HWNode_S* pHWNode, TDE2_ROP_CODE_E enRgbRop, TDE2_ROP_CODE_E enAlphaRop)
{
#ifndef HIGO_CODE_CUT
    TDE_ALU_U unAluMode;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    /*配置缓存节点*/
    unAluMode.u32All = pHWNode->u32TDE_ALU;
    unAluMode.stBits.u32RgbRopMod = (HI_U32)enRgbRop;
    unAluMode.stBits.u32AlphaRopMod = (HI_U32)enAlphaRop;
    pHWNode->u32TDE_ALU = unAluMode.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);
    #endif
}

/*****************************************************************************
* Function:      TdeHalNodeSetColorExp
* Description:   设置颜色扩展或颜色校正参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pClutCmd: Clut操作所需参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

HI_VOID TdeHalNodeSetClutOpt(TDE_HWNode_S* pHWNode, TDE_DRV_CLUT_CMD_S* pClutCmd, HI_BOOL bReload)
{
#ifndef HIGO_CODE_CUT
    TDE_INS_U unIns;
    TDE_COLOR_CONV_U unConv;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pClutCmd);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32Clut = 1; /*使能Clut操作*/

    unConv.u32All = pHWNode->u32TDE_COLOR_CONV;
    unConv.stBits.u32ClutMod = (HI_U32)pClutCmd->enClutMode;
    unConv.stBits.u32ClutReload = (HI_U32)bReload; /* reload clut 到寄存器 */

    /*配置缓存节点*/
    pHWNode->u32TDE_CLUT_ADDR = (HI_U32)pClutCmd->pu8PhyClutAddr;
    pHWNode->u32TDE_INS = unIns.u32All;
    pHWNode->u32TDE_COLOR_CONV = unConv.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_CLUT_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);
    #endif
}

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
#ifndef HIGO_CODE_CUT
HI_VOID TdeHalNodeSetColorKey(TDE_HWNode_S* pHWNode, TDE_COLORFMT_CATEGORY_E enFmtCat, 
                              TDE_DRV_COLORKEY_CMD_S* pColorKey)
{
    TDE_INS_U unIns;
    TDE_ALU_U unAluMode;

    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pColorKey);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32ColorKey = 1; /*使能Color Key操作*/
    unAluMode.u32All = pHWNode->u32TDE_ALU;
    unAluMode.stBits.u32CkSel = (HI_U32)pColorKey->enColorKeyMode;

    if (TDE_COLORFMT_CATEGORY_ARGB == enFmtCat)
    {
        TDE_ALPHA_ADJUST(pColorKey->unColorKeyValue.struCkARGB.stAlpha.u8CompMin);
        TDE_ALPHA_ADJUST(pColorKey->unColorKeyValue.struCkARGB.stAlpha.u8CompMax);
        
        pHWNode->u32TDE_CK_MIN = pColorKey->unColorKeyValue.struCkARGB.stBlue.u8CompMin
            | (pColorKey->unColorKeyValue.struCkARGB.stGreen.u8CompMin << 8)
            | (pColorKey->unColorKeyValue.struCkARGB.stRed.u8CompMin << 16)
            | (pColorKey->unColorKeyValue.struCkARGB.stAlpha.u8CompMin << 24);
        pHWNode->u32TDE_CK_MAX = pColorKey->unColorKeyValue.struCkARGB.stBlue.u8CompMax
            | (pColorKey->unColorKeyValue.struCkARGB.stGreen.u8CompMax << 8)
            | (pColorKey->unColorKeyValue.struCkARGB.stRed.u8CompMax << 16)
            | (pColorKey->unColorKeyValue.struCkARGB.stAlpha.u8CompMax << 24);

        if (pColorKey->unColorKeyValue.struCkARGB.stBlue.bCompIgnore)
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkARGB.stBlue.bCompOut)
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkARGB.stGreen.bCompIgnore)
        {
            unAluMode.stBits.u32CkGMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkARGB.stGreen.bCompOut)
        {
            unAluMode.stBits.u32CkGMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkGMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkARGB.stRed.bCompIgnore)
        {
            unAluMode.stBits.u32CkRMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkARGB.stRed.bCompOut)
        {
            unAluMode.stBits.u32CkRMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkRMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkARGB.stAlpha.bCompIgnore)
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkARGB.stAlpha.bCompOut)
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_AREA_IN;
        }
    }
    else if (TDE_COLORFMT_CATEGORY_CLUT == enFmtCat)/*CLUT格式只用索引*/
    {
        TDE_ALPHA_ADJUST(pColorKey->unColorKeyValue.struCkClut.stAlpha.u8CompMin);
        TDE_ALPHA_ADJUST(pColorKey->unColorKeyValue.struCkClut.stAlpha.u8CompMax);

        pHWNode->u32TDE_CK_MIN = pColorKey->unColorKeyValue.struCkClut.stClut.u8CompMin
            | (pColorKey->unColorKeyValue.struCkClut.stAlpha.u8CompMin << 24);
        pHWNode->u32TDE_CK_MAX = pColorKey->unColorKeyValue.struCkClut.stClut.u8CompMax
            | (pColorKey->unColorKeyValue.struCkClut.stAlpha.u8CompMax << 24);
        
        if (pColorKey->unColorKeyValue.struCkClut.stClut.bCompIgnore)
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkClut.stClut.bCompOut)
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkClut.stAlpha.bCompIgnore)
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkClut.stAlpha.bCompOut)
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_AREA_IN;
        }
    }
    else if (TDE_COLORFMT_CATEGORY_YCbCr == enFmtCat)/*YCbCr格式*/
    {
        TDE_ALPHA_ADJUST(pColorKey->unColorKeyValue.struCkYCbCr.stAlpha.u8CompMin);
        TDE_ALPHA_ADJUST(pColorKey->unColorKeyValue.struCkYCbCr.stAlpha.u8CompMax);
        
        pHWNode->u32TDE_CK_MIN = pColorKey->unColorKeyValue.struCkYCbCr.stCr.u8CompMin
            | (pColorKey->unColorKeyValue.struCkYCbCr.stCb.u8CompMin << 8)
            | (pColorKey->unColorKeyValue.struCkYCbCr.stY.u8CompMin << 16)
            | (pColorKey->unColorKeyValue.struCkYCbCr.stAlpha.u8CompMin << 24);
        pHWNode->u32TDE_CK_MAX = pColorKey->unColorKeyValue.struCkYCbCr.stCr.u8CompMax
            | (pColorKey->unColorKeyValue.struCkYCbCr.stCb.u8CompMax << 8)
            | (pColorKey->unColorKeyValue.struCkYCbCr.stY.u8CompMax << 16)
            | (pColorKey->unColorKeyValue.struCkYCbCr.stAlpha.u8CompMax << 24);

        if (pColorKey->unColorKeyValue.struCkYCbCr.stCr.bCompIgnore)
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkYCbCr.stCr.bCompOut)
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkBMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkYCbCr.stCb.bCompIgnore)
        {
            unAluMode.stBits.u32CkGMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkYCbCr.stCb.bCompOut)
        {
            unAluMode.stBits.u32CkGMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkGMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkYCbCr.stY.bCompIgnore)
        {
            unAluMode.stBits.u32CkRMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkYCbCr.stY.bCompOut)
        {
            unAluMode.stBits.u32CkRMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkRMod = TDE_COLORKEY_AREA_IN;
        }

        if (pColorKey->unColorKeyValue.struCkYCbCr.stAlpha.bCompIgnore)
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_IGNORE;
        }
        else if (pColorKey->unColorKeyValue.struCkYCbCr.stAlpha.bCompOut)
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_AREA_OUT;
        }
        else
        {
            unAluMode.stBits.u32CkAMod = TDE_COLORKEY_AREA_IN;
        }
    }
    else
    {
        return;
    }
    pHWNode->u32TDE_ALU = unAluMode.u32All;
    pHWNode->u32TDE_INS = unIns.u32All;
    
    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_CK_MIN, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_CK_MAX, pHWNode->u64TDE_UPDATE);
    return;
}
#endif
/*****************************************************************************
* Function:      TdeHalNodeSetClipping
* Description:   设置矩形裁减操作参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pClip: 裁减矩形范围
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/

HI_VOID TdeHalNodeSetClipping(TDE_HWNode_S* pHWNode, TDE_DRV_CLIP_CMD_S* pClip)
{
#ifndef HIGO_CODE_CUT
    TDE_INS_U unIns;
    TDE_SUR_SIZE_U unClipPos;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pClip);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32Clip = 1; /*启用clip操作*/

    if(pClip->bInsideClip)
    {
        unClipPos.u32All = 0;
    }
    else
    {
        /* 区域外clip指示 */
        unClipPos.u32All = 0x80000000; 
    }
    unClipPos.stBits.u32Width = pClip->u16ClipStartX;
    unClipPos.stBits.u32Height = pClip->u16ClipStartY;
    pHWNode->u32TDE_CLIP_START = unClipPos.u32All;

    unClipPos.u32All = 0; /* 重新复位,准备下一设置 AI7D02798 */
    unClipPos.stBits.u32Width = pClip->u16ClipEndX;
    unClipPos.stBits.u32Height = pClip->u16ClipEndY;
    pHWNode->u32TDE_CLIP_STOP = unClipPos.u32All;

    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_CLIP_START, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_CLIP_STOP, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
    #endif
}

/*****************************************************************************
* Function:      TdeHalNodeSetFlicker
* Description:   设置抗闪烁滤波运算参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pFlicker: 抗闪烁系数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetFlicker(TDE_HWNode_S* pHWNode, TDE_DRV_FLICKER_CMD_S* pFlicker)
{
    TDE_INS_U unIns;
    TDE_2D_RSZ_U unRsz;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pFlicker);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32DfeEn = 1; /*使能抗闪烁*/
    unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
    if (pFlicker->enDeflickerMode == TDE2_DEFLICKER_MODE_RGB)
    {
        unRsz.stBits.u32DfeAlphaDisable = 1;
    }
    else
    {
        unRsz.stBits.u32DfeAlphaDisable = 0;
    }
    unRsz.stBits.u32DfeMod = (HI_U32)pFlicker->enDfeMode;

    /*配置缓存节点*/
    switch(s_eDeflickerLevel)
    {
        case TDE_DEFLICKER_LOW:
        {
            unRsz.stBits.u32DfeMod = 0;
            pHWNode->u32TDE_DFE_COEF0 = 0x0f003307;
            break;
        }
        case TDE_DEFLICKER_MIDDLE:
        {
            unRsz.stBits.u32DfeMod = 0;
            pHWNode->u32TDE_DFE_COEF0 = 0x0f002010;
            break;
        }
        case TDE_DEFLICKER_HIGH:
        {
            unRsz.stBits.u32DfeMod = 0;
            pHWNode->u32TDE_DFE_COEF0 = 0x0f001a13;
            break;
        }
        default:   
        {
            pHWNode->u32TDE_DFE_COEF0 = (HI_U32)pFlicker->u8Coef0NextLine 
                | ((HI_U32)pFlicker->u8Coef0CurLine << 8)
                | ((HI_U32)pFlicker->u8Coef0LastLine << 16)
                | ((HI_U32)pFlicker->u8Threshold0 << 24);
            pHWNode->u32TDE_DFE_COEF1 = (HI_U32)pFlicker->u8Coef1NextLine 
                | ((HI_U32)pFlicker->u8Coef1CurLine << 8)
                | ((HI_U32)pFlicker->u8Coef1LastLine << 16)
                | ((HI_U32)pFlicker->u8Threshold1 << 24);
            pHWNode->u32TDE_DFE_COEF2 = (HI_U32)pFlicker->u8Coef2NextLine 
                | ((HI_U32)pFlicker->u8Coef2CurLine << 8)
                | ((HI_U32)pFlicker->u8Coef2LastLine << 16)
                | ((HI_U32)pFlicker->u8Threshold2 << 24);
            pHWNode->u32TDE_DFE_COEF3 = (HI_U32)pFlicker->u8Coef3NextLine 
                | ((HI_U32)pFlicker->u8Coef3CurLine << 8)
                | ((HI_U32)pFlicker->u8Coef3LastLine << 16);
                    break;
        }
    }

    pHWNode->u32TDE_INS = unIns.u32All;
    pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
    
    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_2D_RSZ, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_DFE_COEF0, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_DFE_COEF1, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_DFE_COEF2, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_DFE_COEF3, pHWNode->u64TDE_UPDATE);

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetResize
* Description:   设置缩放滤波运算参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pResize: 缩放系数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetResize(TDE_HWNode_S* pHWNode, TDE_DRV_RESIZE_CMD_S* pResize, 
TDE_NODE_SUBM_TYPE_E enNodeType)
{
    TDE_INS_U unIns;
    TDE_2D_RSZ_U unRsz;
    HI_U32 u32Sign = 0;

    TDE_TAR_TYPE_U unTarType;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pResize);

    unIns.u32All = pHWNode->u32TDE_INS;
    //unIns.stBits.u32Resize = 0x1; /*使能缩放*/
    
    unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
    unRsz.stBits.u32HfMod = pResize->enFilterH;
    unRsz.stBits.u32VfMod = pResize->enFilterV;

    /* 垂直滤波 */
    if (TDE_DRV_FILTER_NONE != pResize->enFilterV)
    {
        unRsz.stBits.u32VfRingEn = pResize->bVfRing; /*使能中值滤波*/
        unRsz.stBits.u32VfCoefReload = 0x1; /*载入垂直参数*/
        /* 根据步长配置垂直缩放参数表首地址 */
        pHWNode->u32TDE_VF_COEF_ADDR = s_stParaTable.u32VfCoefAddr
                      + TdeHalGetResizeParaVTable(pResize->u32StepV) * TDE_PARA_VTABLE_SIZE;
        TDE_SET_UPDATE(u32TDE_VF_COEF_ADDR, pHWNode->u64TDE_UPDATE);

        if (TDE_NODE_SUBM_PARENT == enNodeType)
        {
        /* 设置垂直偏移 */
        u32Sign = pResize->u32OffsetY >> 31; /*提取符号*/
        pHWNode->u32TDE_RSZ_Y_OFST = (u32Sign << 16) | (pResize->u32OffsetY & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_Y_OFST, pHWNode->u64TDE_UPDATE);
        unIns.stBits.u32Resize = 0x1; /*使能缩放*/
        }
    }
    /* 水平滤波 */
    if (TDE_DRV_FILTER_NONE != pResize->enFilterH)
    {
        unRsz.stBits.u32HfRingEn = pResize->bHfRing;/*使能中值滤波*/
        unRsz.stBits.u32HfCoefReload = 0x1;/*载入水平参数*/
        /* 根据步长配置垂直缩放参数表首地址 */
        pHWNode->u32TDE_HF_COEF_ADDR = s_stParaTable.u32HfCoefAddr
                    + TdeHalGetResizeParaHTable(pResize->u32StepH) * TDE_PARA_HTABLE_SIZE;
        TDE_SET_UPDATE(u32TDE_HF_COEF_ADDR, pHWNode->u64TDE_UPDATE);

        if (TDE_NODE_SUBM_PARENT == enNodeType)
        {
        /* 设置水平偏移 */
        u32Sign = pResize->u32OffsetX >> 31; /*提取符号*/
        pHWNode->u32TDE_RSZ_X_OFST = (u32Sign << 16) | (pResize->u32OffsetX & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_X_OFST, pHWNode->u64TDE_UPDATE);
        unIns.stBits.u32Resize = 0x1; /*使能缩放*/
        }
    }

    unRsz.stBits.u32CoefSym = pResize->bCoefSym;/*对称滤波系数*/
    pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
    if (TDE_NODE_SUBM_PARENT == enNodeType)
    {
        pHWNode->u32TDE_INS = unIns.u32All;

        unTarType.u32All = pHWNode->u32TDE_TAR_TYPE;
        unTarType.stBits.u32DfeFirstlineOutEn = pResize->bFirstLineOut;
        unTarType.stBits.u32DfeLastlineOutEn = pResize->bLastLineOut;
        pHWNode->u32TDE_TAR_TYPE = unTarType.u32All;

        /* 设置滤波步长 */
#ifdef TDE_VERSION_MPW   
        HI_U16 u16VStep;
        HI_U16 u16HStep;
        u16HStep = pResize->u32StepH & 0xffff;
        u16VStep = pResize->u32StepV & 0xffff;
        pHWNode->u32TDE_RSZ_STEP = (HI_U32)u16HStep | ((HI_U32)u16VStep << 16);
        TDE_SET_UPDATE(u32TDE_RSZ_STEP, pHWNode->u64TDE_UPDATE);
#else
    pHWNode->u32TDE_RSZ_HSTEP = pResize->u32StepH;
    pHWNode->u32TDE_RSZ_VSTEP = pResize->u32StepV;
    TDE_SET_UPDATE(u32TDE_RSZ_HSTEP, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_RSZ_VSTEP, pHWNode->u64TDE_UPDATE);
#endif
    
        TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
        TDE_SET_UPDATE(u32TDE_TAR_TYPE , pHWNode->u64TDE_UPDATE);
    }

    TDE_SET_UPDATE(u32TDE_2D_RSZ, pHWNode->u64TDE_UPDATE);

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetColorConvert
* Description:   设置颜色空间转换所需参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pConv: 颜色空间转换参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetColorConvert(TDE_HWNode_S* pHWNode, TDE_DRV_CONV_MODE_CMD_S* pConv)
{
    TDE_INS_U unIns;
    TDE_COLOR_CONV_U unConv;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pConv);

    unIns.u32All = pHWNode->u32TDE_INS;
    unConv.u32All = pHWNode->u32TDE_COLOR_CONV;

    unIns.stBits.u32IcsConv = (HI_U32)pConv->bInConv;
    unIns.stBits.u32OcsConv = (HI_U32)pConv->bOutConv;
    
    unConv.stBits.u32InRgb2Yc = (HI_U32)pConv->bInRGB2YC;
    //unConv.stBits.u32InColorSpace = (HI_U32)pConv->bInMetrixVid;
    //unConv.stBits.u32InColorimetry = (HI_U32)pConv->bInMetrix709;
    //unConv.stBits.u32OutColorSpace = (HI_U32)pConv->bOutMetrixVid;
    //unConv.stBits.u32OutColorimetry = (HI_U32)pConv->bOutMetrix709;

    /*配置缓存节点*/
    pHWNode->u32TDE_COLOR_CONV = unConv.u32All;
    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    return;
}

/*****************************************************************************
* Function:      TdeHalNodeAddChild
* Description:   在滤波操作时添加子节点
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pChildInfo: 添加子节点的配置信息
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeAddChild(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo)
{
    TDE_SUR_XY_U unXy;
    TDE_INS_U unIns;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pChildInfo);

    /* 根据Update信息配置寄存器:
       u32TDE_RSZ_OFST
       u32TDE_2D_RSZ
       TDE_S2_XY
       TDE_TAR_XY
       TDE_S2_SIZE
       TDE_TS_SIZE
       */
    if (pChildInfo->u64Update & 0x1)
    {
        TdeHalSetXyByAdjInfo(pHWNode, pChildInfo);
    }
    if (pChildInfo->u64Update & 0x2)
    {
        TDE_SUR_SIZE_U unSz;
        unSz.u32All = pHWNode->u32TDE_S2_SIZE;
        unSz.stBits.u32Width = pChildInfo->u32Wi;
        unSz.stBits.u32Height = pChildInfo->u32Hi;
        pHWNode->u32TDE_S2_SIZE = unSz.u32All;
        TDE_SET_UPDATE(u32TDE_S2_SIZE, pHWNode->u64TDE_UPDATE);
    }
    if (pChildInfo->u64Update & 0x4)
    {
        HI_U32 u32Sign;
        
        /* 设置水平偏移 */
        u32Sign = pChildInfo->u32HOfst >> 31; /*提取符号*/
        pHWNode->u32TDE_RSZ_X_OFST = (u32Sign << 16) | (pChildInfo->u32HOfst & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_X_OFST, pHWNode->u64TDE_UPDATE);

        /* 设置垂直偏移 */
        u32Sign = pChildInfo->u32VOfst >> 31; /*提取符号*/
        pHWNode->u32TDE_RSZ_Y_OFST = (u32Sign << 16) | (pChildInfo->u32VOfst & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_Y_OFST, pHWNode->u64TDE_UPDATE);
    }
    if (pChildInfo->u64Update & 0x8)
    {
        unXy.u32All = pHWNode->u32TDE_TAR_XY;
        unXy.stBits.u32X = pChildInfo->u32Xo;
        unXy.stBits.u32Y = pChildInfo->u32Yo;
        pHWNode->u32TDE_TAR_XY = unXy.u32All;
        TDE_SET_UPDATE(u32TDE_TAR_XY, pHWNode->u64TDE_UPDATE);
        if(pChildInfo->stDSAdjInfo.bDoubleSource)
        {
            unXy.u32All = pHWNode->u32TDE_S1_XY;
            unXy.stBits.u32X = (HI_U32)(pChildInfo->u32Xo + pChildInfo->stDSAdjInfo.s32DiffX);
            unXy.stBits.u32Y = (HI_U32)(pChildInfo->u32Yo + pChildInfo->stDSAdjInfo.s32DiffY);
            pHWNode->u32TDE_S1_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);
        }
    }
    if (pChildInfo->u64Update & 0x10)
    {
        TDE_SUR_SIZE_U unSz;
        unSz.u32All = pHWNode->u32TDE_TS_SIZE;
        unSz.stBits.u32Width = pChildInfo->u32Wo;
        unSz.stBits.u32Height = pChildInfo->u32Ho;
        pHWNode->u32TDE_TS_SIZE = unSz.u32All;
        TDE_SET_UPDATE(u32TDE_TS_SIZE, pHWNode->u64TDE_UPDATE);
    }
    /* 填充块类型信息 */
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32BlockFlag = (HI_U32)pChildInfo->enSliceType;
    if (pChildInfo->enSliceType == TDE_FIRST_BLOCK_SLICE_TYPE)
    {
        unIns.stBits.u32FirstBlockFlag = 1;
        unIns.stBits.u32LastBlockFlag = 0;
    }
    else if (pChildInfo->enSliceType == TDE_LAST_BLOCK_SLICE_TYPE)
    {
        unIns.stBits.u32FirstBlockFlag = 0;
        unIns.stBits.u32LastBlockFlag = 1;
    }
    else
    {
        unIns.stBits.u32FirstBlockFlag = 0;
        unIns.stBits.u32LastBlockFlag = 0;
    }
    pHWNode->u32TDE_INS = unIns.u32All;

    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetMbMode
* Description:   设置宏块处理所需参数
* Input:         pHWNode: 软件用于缓存的节点结构指针
*                pMbCmd: 宏块处理参数
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
HI_VOID TdeHalNodeSetMbMode(TDE_HWNode_S* pHWNode, TDE_DRV_MB_CMD_S* pMbCmd)
{
    TDE_INS_U unIns;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pMbCmd);

    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32MbMode = (HI_U32)pMbCmd->enMbMode;
    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
}



/****************************************************************************/
/*                             TDE hal 内部函数实现                         */
/****************************************************************************/
/*****************************************************************************
* Function:      TdeHalInitParaTable
* Description:   初始化配置参数表
* Input:         无
* Output:        无
* Return:        成功/失败
* Others:        无
*****************************************************************************/
STATIC HI_S32 TdeHalInitParaTable(HI_VOID)
{
    #include "tde_filterPara.h"
    #define OrgHfCoef Tde8x32Coef /* H2 / HD TDE水平单独使用各自系数表 */
    HI_U32 i = 0;
    HI_U32 j = 0;
    TDE_FILTER_PARA_U unPara;
    HI_U32 *pHfCoef = HI_NULL;
    HI_U32 *pVfCoef = HI_NULL;
    HI_U32 *pRgb2YuvCsc = HI_NULL;
    HI_U32 *pYuv2RgbCsc = HI_NULL;
    
    /* 算法提供的参数列表 */
    pHfCoef = (HI_U32 *)TDE_MALLOC(TDE_PARA_HTABLE_SIZE * TDE_PARA_HTABLE_NUM);
    if (HI_NULL == pHfCoef)
    {
        TDE_TRACE(TDE_KERN_ERR,"Alloc horizontal coef failed!\n");
        return HI_FAILURE;
    }
    
    pVfCoef = (HI_U32 *)TDE_MALLOC(TDE_PARA_VTABLE_SIZE * TDE_PARA_VTABLE_NUM);
    if (HI_NULL == pVfCoef)
    {
        TDE_TRACE(TDE_KERN_ERR,"Alloc vertical coef failed\n");
        TDE_FREE(pHfCoef);
        return HI_FAILURE;
    }

    memset(pHfCoef, 0, (TDE_PARA_HTABLE_SIZE * TDE_PARA_HTABLE_NUM));
    memset(pVfCoef, 0, (TDE_PARA_VTABLE_SIZE * TDE_PARA_VTABLE_NUM));
    /* 按照算法组提供的结构拷贝参数表 */
    for (i = 0; i < TDE_PARA_HTABLE_NUM; i++)
    {
        memcpy(pHfCoef + i*(TDE_PARA_HTABLE_SIZE/4), OrgHfCoef + i*(TDE_PARA_HTABLE_ORG_SIZE/4), (TDE_PARA_HTABLE_ORG_SIZE));
    }
    for (i = 0, j = 0; i < TDE_PARA_VTABLE_ORG_SIZE * TDE_PARA_VTABLE_NUM - 4; j++)
    {
        unPara.stBits.u32Para0 = OrgVfCoef[i++];
        unPara.stBits.u32Para1 = OrgVfCoef[i++];
        unPara.stBits.u32Para2 = OrgVfCoef[i++];
        unPara.stBits.u32Para3 = OrgVfCoef[i++];
        unPara.stBits.u32Para4 = OrgVfCoef[i++];
        *(pVfCoef + j) = unPara.u32All;
    }

    memset(&s_stParaTable, 0, sizeof(s_stParaTable));

    s_stParaTable.u32HfCoefAddr = wgetphy((HI_VOID *)pHfCoef);
    s_stParaTable.u32VfCoefAddr = wgetphy((HI_VOID *)pVfCoef);

    #ifdef TDE_CSC_ENABLE
    pRgb2YuvCsc = (HI_U32 *)TDE_MALLOC(TDE_CSCTABLE_SIZE * sizeof(HI_U32));
    if (HI_NULL == pRgb2YuvCsc)
    {
        TDE_FREE(pHfCoef);
        TDE_FREE(pVfCoef);
        TDE_TRACE(TDE_KERN_INFO, "Alloc csc coef failed!\n");
        return HI_FAILURE;
    }
    
    pYuv2RgbCsc = (HI_U32 *)TDE_MALLOC(TDE_CSCTABLE_SIZE * sizeof(HI_U32));
    if (HI_NULL == pYuv2RgbCsc)
    {
        TDE_TRACE(TDE_KERN_INFO, "Alloc csc coef failed\n");
        TDE_FREE(pHfCoef);
        TDE_FREE(pVfCoef);
        TDE_FREE(pRgb2YuvCsc);
        return HI_FAILURE;
    }

    memcpy(pRgb2YuvCsc, s_u32Rgb2YuvCsc, TDE_CSCTABLE_SIZE * sizeof(HI_U32));
    memcpy(pYuv2RgbCsc, s_u32Yuv2RgbCsc, TDE_CSCTABLE_SIZE * sizeof(HI_U32));

    s_u32Rgb2YuvCoefAddr = wgetphy((HI_VOID *)pRgb2YuvCsc);
    s_u32Yuv2RgbCoefAddr = wgetphy((HI_VOID *)pYuv2RgbCsc);
    #endif

    
    return HI_SUCCESS;
}



/*****************************************************************************
* Function:      TdeHalNodeSetSrc2Base
* Description:   设置源2位图基本信息
* Input:         pHWNode: 硬件链表节点指针
*                pDrvSurface: 位图信息
*                bS2Size: 是否设置源2尺寸
* Output:        无
* Return:        链表执行当前节点的物理地址
* Others:        无
*****************************************************************************/
STATIC HI_VOID TdeHalNodeSetSrc2Base(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, HI_BOOL bS2Size)
{
    TDE_SRC_TYPE_U unSrcType;
    TDE_SUR_XY_U unXy;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvSurface);

    /*配置源位图属性信息*/
    unSrcType.u32All = 0;
    unSrcType.stBits.u32Pitch = pDrvSurface->u32Pitch;
    unSrcType.stBits.u32SrcColorFmt = (HI_U32)pDrvSurface->enColorFmt;
    unSrcType.stBits.u32AlphaRange = (HI_U32)pDrvSurface->bAlphaMax255;
    unSrcType.stBits.u32HScanOrd = (HI_U32)pDrvSurface->enHScan;
    unSrcType.stBits.u32VScanOrd = (HI_U32)pDrvSurface->enVScan;
    unSrcType.stBits.u32RgbExp = 0; /*一直使用低位填充为0,高位使用低位的扩展方式*/

    unXy.u32All = pHWNode->u32TDE_S2_XY;
    unXy.stBits.u32X = pDrvSurface->u32Xpos;
    unXy.stBits.u32Y = pDrvSurface->u32Ypos;

    /*配置缓存节点*/
    pHWNode->u32TDE_S2_ADDR = pDrvSurface->u32PhyAddr;
    pHWNode->u32TDE_S2_TYPE = unSrcType.u32All;
    pHWNode->u32TDE_S2_XY = unXy.u32All;

    /*HWNode.TDE_UPDATE中有配置项对应位设1*/
    TDE_SET_UPDATE(u32TDE_S2_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S2_TYPE, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);
    
    if (bS2Size)
    {
        TDE_SUR_SIZE_U unSurSize;
        unSurSize.u32All = 0;
        /*配置位图大小信息*/
        unSurSize.stBits.u32Width = (HI_U32)pDrvSurface->u32Width;
        unSurSize.stBits.u32Height = (HI_U32)pDrvSurface->u32Height;
        pHWNode->u32TDE_S2_SIZE = unSurSize.u32All;
        TDE_SET_UPDATE(u32TDE_S2_SIZE, pHWNode->u64TDE_UPDATE);
    }

    return;
}

/*****************************************************************************
* Function:      TdeHalGetbppByFmt
* Description:   根据驱动层颜色格式得到Bpp
* Input:         enFmt: 颜色格式
* Output:        像素位宽
* Return:        -1:错误格式
* Others:        无
*****************************************************************************/
STATIC HI_S32  TdeHalGetbppByFmt(TDE_DRV_COLOR_FMT_E enFmt)
{
    switch (enFmt)
    {
#ifndef HIGO_CODE_CUT  
    case TDE_DRV_COLOR_FMT_RGB444:
    case TDE_DRV_COLOR_FMT_RGB555:
    case TDE_DRV_COLOR_FMT_RGB565:
    case TDE_DRV_COLOR_FMT_ARGB4444:
    case TDE_DRV_COLOR_FMT_ARGB1555:
    case TDE_DRV_COLOR_FMT_ACLUT88:
    case TDE_DRV_COLOR_FMT_YCbCr422:
    case TDE_DRV_COLOR_FMT_halfword:
#else      
    case TDE_DRV_COLOR_FMT_RGB565:
    case TDE_DRV_COLOR_FMT_ARGB1555:    
#endif
        return 16;
        
    //case TDE_DRV_COLOR_FMT_RGB888:
    //case TDE_DRV_COLOR_FMT_ARGB8565:
    case TDE_DRV_COLOR_FMT_YCbCr888:    
        return 24;    
    case TDE_DRV_COLOR_FMT_ARGB8888:
    case TDE_DRV_COLOR_FMT_AYCbCr8888:
        return 32;
#ifndef HIGO_CODE_CUT
    case TDE_DRV_COLOR_FMT_CLUT1:
    case TDE_DRV_COLOR_FMT_A1:
        return 1;

    case TDE_DRV_COLOR_FMT_CLUT2:
        return 2;

    case TDE_DRV_COLOR_FMT_CLUT4:
        return 4;

    case TDE_DRV_COLOR_FMT_CLUT8:
    case TDE_DRV_COLOR_FMT_ACLUT44:
    case TDE_DRV_COLOR_FMT_A8:
    case TDE_DRV_COLOR_FMT_byte:
        return 8;
#endif
    case TDE_DRV_COLOR_FMT_YCbCr400MBP:
    case TDE_DRV_COLOR_FMT_YCbCr422MBH:
    case TDE_DRV_COLOR_FMT_YCbCr422MBV:
    case TDE_DRV_COLOR_FMT_YCbCr420MB:
    case TDE_DRV_COLOR_FMT_YCbCr444MB:
    case TDE_DRV_COLOR_FMT_BUTT:
    default:
        return -1;
    }
}

/*****************************************************************************
* Function:      TdeHalGetResizeParaTable
* Description:   根据步长找到表的索引
* Input:         u32Step: 输入步长
* Output:        无
* Return:        符合要求的缩放表物理地址索引
* Others:        无
*****************************************************************************/
STATIC HI_U32 TdeHalGetResizeParaHTable(HI_U32 u32Step)
{
    HI_U32 u32Index;

    if (TDE_RESIZE_8X32_AREA_0 > u32Step)
    {
        u32Index = 0;
    }
    else if (TDE_RESIZE_8X32_AREA_0 <= u32Step && TDE_RESIZE_8X32_AREA_1 > u32Step)
    {
        u32Index = 1;
    }
    else if (TDE_RESIZE_8X32_AREA_1 <= u32Step && TDE_RESIZE_8X32_AREA_2 > u32Step)
    {
        u32Index = 2;
    }
    else if (TDE_RESIZE_8X32_AREA_2 <= u32Step && TDE_RESIZE_8X32_AREA_3 > u32Step)
    {
        u32Index = 3;
    }
    else if (TDE_RESIZE_8X32_AREA_3 <= u32Step && TDE_RESIZE_8X32_AREA_4 > u32Step)
    {
        u32Index = 4;
    }
    else /* TDE_RESIZE_8X32_AREA_4 <= u32Step */
    {
        u32Index = 5;
    }

    return u32Index;
}
/*****************************************************************************
* Function:      TdeHalGetResizeParaVTable
* Description:   根据步长找到垂直缩放参数表的索引
* Input:         u32Step: 输入垂直缩放步长
* Output:        无
* Return:        符合要求的缩放表物理地址索引
* Others:        无
*****************************************************************************/
STATIC  HI_U32 TdeHalGetResizeParaVTable(HI_U32 u32Step)
{
    HI_U32 u32Index;

    /* 根据步长找到表的索引 */
    if (u32Step < TDE_RESIZE_PARA_AREA_0)
    {
        u32Index = 0;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_0 && u32Step < TDE_RESIZE_PARA_AREA_1)
    {
        u32Index = 1;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_1 && u32Step < TDE_RESIZE_PARA_AREA_2)
    {
        u32Index = 2;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_2 && u32Step < TDE_RESIZE_PARA_AREA_3)
    {
        u32Index = 3;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_3 && u32Step < TDE_RESIZE_PARA_AREA_4)
    {
        u32Index = 4;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_4 && u32Step < TDE_RESIZE_PARA_AREA_5)
    {
        u32Index = 5;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_5 && u32Step < TDE_RESIZE_PARA_AREA_6)
    {
        u32Index = 6;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_6 && u32Step < TDE_RESIZE_PARA_AREA_7)
    {
        u32Index = 7;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_7 && u32Step < TDE_RESIZE_PARA_AREA_8)
    {
        u32Index = 8;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_8 && u32Step < TDE_RESIZE_PARA_AREA_9)
    {
        u32Index = 9;
    }
    else if (u32Step >= TDE_RESIZE_PARA_AREA_9 && u32Step < TDE_RESIZE_PARA_AREA_10)
    {
        u32Index = 10;
    }
    else /* u32Step >= TDE_RESIZE_PARA_AREA_10 */
    {
        u32Index = 11;
    }

    return u32Index;
}


/*****************************************************************************
* Function:      TdeHalSetXyByAdjInfo
* Description:   pHWNode:   硬件节点信息
*                pChildInfo: 子节点信息
* Input:         无
* Output:        无
* Return:        无
* Others:        无
*****************************************************************************/
STATIC  HI_VOID TdeHalSetXyByAdjInfo(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo)
{
    TDE_SUR_XY_U unXy;
    
    switch (pChildInfo->stAdjInfo.enScaleMode)
    {
    case TDE_CHILD_SCALE_NORM:
    case TDE_CHILD_SCALE_MBC:
        {
            /* 直接按照S2分块 */
            unXy.u32All = pHWNode->u32TDE_S2_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
            pHWNode->u32TDE_S2_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);
            break;
        }
    case TDE_CHILD_SCALE_MBY:
        {
            /* 直接按照S1分块 */
            unXy.u32All = pHWNode->u32TDE_S1_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
            pHWNode->u32TDE_S1_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);
            break;
        }
    case TDE_CHILD_SCALE_MB_CONCA_H:
    case TDE_CHILD_SCALE_MB_CONCA_M:
        {
            /* 按照亮度S1分块, 调整色度S2起始位置 */
            unXy.u32All = pHWNode->u32TDE_S1_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
            pHWNode->u32TDE_S1_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);

            unXy.u32All = pHWNode->u32TDE_S2_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi - pChildInfo->stAdjInfo.u32StartInX;
            unXy.stBits.u32Y = 0;
            pHWNode->u32TDE_S2_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);
            break;
        }
    case TDE_CHILD_SCALE_MB_CONCA_L:
        {
            /* 按照亮度S1分块, 调整色度S2起始位置 */
            unXy.u32All = pHWNode->u32TDE_S1_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
            pHWNode->u32TDE_S1_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);

            unXy.u32All = pHWNode->u32TDE_S2_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
			
            if (TDE_DRV_COLOR_FMT_YCbCr420MB == pChildInfo->stAdjInfo.enFmt
                || TDE_DRV_COLOR_FMT_YCbCr422MBH == pChildInfo->stAdjInfo.enFmt)
            {
                unXy.stBits.u32X = (pChildInfo->u32Xi >> 1);
            }
            if (TDE_DRV_COLOR_FMT_YCbCr420MB == pChildInfo->stAdjInfo.enFmt
                || TDE_DRV_COLOR_FMT_YCbCr422MBV == pChildInfo->stAdjInfo.enFmt)
            {
                unXy.stBits.u32Y = (pChildInfo->u32Yi >> 1);
            }
            pHWNode->u32TDE_S2_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);
            break;
        }
    case TDE_CHILD_SCALE_MB_CONCA_CUS:
        {
            /* 按照色度S2分块, 调整亮度S1起始位置 */
            unXy.u32All = pHWNode->u32TDE_S2_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
            pHWNode->u32TDE_S2_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);

            unXy.u32All = pHWNode->u32TDE_S1_XY;
            unXy.stBits.u32X = pChildInfo->u32Xo - pChildInfo->stAdjInfo.u32StartOutX 
                               + pChildInfo->stAdjInfo.u32StartInX;
            unXy.stBits.u32Y = pChildInfo->stAdjInfo.u32StartInY;
            pHWNode->u32TDE_S1_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);
			break;
	 }
    default:
        break;
    }
}

STATIC  HI_VOID TdeHalInitQueue(HI_VOID)
{
    TDE_AQ_CTRL_U unAqCtrl;
    //TDE_SQ_CTRL_U unSqCtrl;

    /* 将Aq/Sq链表首地址寄存器写0 */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_NADDR, 0);
   // TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_NADDR, 0);

    unAqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_AQ_CTRL);
   // unSqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL);
    
    /* 使能Aq/Sq链表 */
    unAqCtrl.stBits.u32AqEn = 1;
#if 0
    unSqCtrl.stBits.u32SqEn = 0;    /* 硬件暂时屏蔽*/

    /* 设置SQ的触发条件和同步模式 */
    unSqCtrl.stBits.u32TrigMode = 0;
    unSqCtrl.stBits.u32TrigCond = 0;

    /* 配置Sq/Aq操作模式 */
    unSqCtrl.stBits.u32SqOperMode = TDE_SQ_CTRL_COMP_LIST; /*Sq完成后启动下一链表*/
#endif    
    unAqCtrl.stBits.u32AqOperMode = TDE_AQ_CTRL_COMP_LINE; /* 不打断 */

    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_CTRL, unAqCtrl.u32All);

    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AXI_ID, 0x1010);
    //TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL, unSqCtrl.u32All);
}
HI_S32 TdeHalSetAlphaThreshold(HI_U8 u8ThresholdValue)
{
    s_u8AlphaThresholdValue = u8ThresholdValue;
    
    return HI_SUCCESS;
    
}
HI_S32 TdeHalSetAlphaThresholdState(HI_BOOL bEnAlphaThreshold)
{
    s_bEnAlphaThreshold = bEnAlphaThreshold;

    return HI_SUCCESS;
}
#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

