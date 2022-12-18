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
/*                             TDE hal �ڲ��궨��                           */
/****************************************************************************/



/*����ṹ���Ա��ƫ��ֵ*/
#define TDE_OFFSET_OF(type, member) ((HI_U32) (&((type *)0)->member))

#ifdef TDE_VERSION_MPW
#define UPDATE_SIZE 32
#else
#define UPDATE_SIZE 64
#endif
/*�����жϵ�ǰ�����¶�Ӧ��Update����Ƿ�Ϊ1*/
#define TDE_MASK_UPDATE(member) (1 << ((TDE_OFFSET_OF(TDE_HWNode_S, member) >> 2) % (UPDATE_SIZE)))

/* �������õ����ø���update ��� */
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

/* ���ݵ�ǰ��Ա�͸��±�ǻ�ȡ�ڵ�Buffer�еĳ�Աָ��
   ����pRetΪ�ձ�ʾ��ǰBuffer��û����Ҫ��member */
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

/* ��д�Ĵ�����װ */
#define TDE_READ_REG(base, offset) \
    (*(volatile unsigned int   *)((unsigned int)(base) + (offset)))
    
#define TDE_WRITE_REG(base, offset, value) \
    (*(volatile unsigned int   *)((unsigned int)(base) + (offset)) = (value))

/* TDE�Ĵ�����ַ��Χ */
#define TDE_REG_SIZE 0x1000

#define TDE_PARA_TABLE_SIZE 32
#define TDE_PARA_TABLE_ORG_SIZE 40
#define TDE_PARA_TABLE_NUM  12

#define TDE_PARA_HTABLE_ORG_SIZE 33 * 4
#define TDE_PARA_HTABLE_SIZE 160 /* ���ø�Ӳ���Ĳ�������Ҫ16�ֽڶ���, ��˶�ʹ����160�ֽ� */
#define TDE_PARA_HTABLE_NUM  6

#define TDE_PARA_VTABLE_ORG_SIZE 40
#define TDE_PARA_VTABLE_SIZE TDE_PARA_TABLE_SIZE
#define TDE_PARA_VTABLE_NUM  TDE_PARA_TABLE_NUM

/* �㷨���ṩStep�ķ�Χ���� */
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
/* 8*32��ϵ����Χ */
#define TDE_RESIZE_8X32_AREA_0  4096     /*1.0*/
#define TDE_RESIZE_8X32_AREA_1  5936     /*0.69*/
#define TDE_RESIZE_8X32_AREA_2  8192     /*0.5*/
#define TDE_RESIZE_8X32_AREA_3  12412    /*0.33*/
#define TDE_RESIZE_8X32_AREA_4  204800   /*0.02*/

/* ColorKeyоƬ�����ģʽ */
#define TDE_COLORKEY_IGNORE     2
#define TDE_COLORKEY_AREA_OUT   1
#define TDE_COLORKEY_AREA_IN    0

/* Aq����ģʽ */
#define TDE_AQ_CTRL_COMP_LIST   0x0 /*��ɵ�ǰ����֮��������һ��ͬ������*/
#define TDE_AQ_CTRL_COMP_LINE   0x4 /*��ɵ�ǰ����ǰ�ڵ㵱ǰ�к�������һ��ͬ������*/

/* Sq����ģʽ*/
#define TDE_SQ_CTRL_COMP_LIST   0x0 /*��ɵ�ǰ����֮��������һ��ͬ������*/
#define TDE_SQ_CTRL_COMP_LINE   0x4 /*��ɵ�ǰ����ǰ�ڵ㵱ǰ�к�������һ��ͬ������*/

/* ��ǰ�й���ʱ�ı�� */
#define TDE_SUSP_LINE_INVAL (-1)
#define TDE_SUSP_LINE_READY (-2)

#define TDE_MAX_READ_STATUS_TIME 10

/****************************************************************************/
/*                             TDE hal �ڲ����Ͷ���                         */
/****************************************************************************/
/* Դλͼ����ģʽ */
typedef enum hiTDE_SRC_MODE_E
{
    TDE_SRC_MODE_DISA  = 0,
    TDE_SRC_MODE_BMP   = 1,
    TDE_SRC_MODE_PATTERN = 2,
    TDE_SRC_MODE_FILL  = 3,
    TDE_SRC_QUICK_COPY = 5,
    TDE_SRC_QUICK_FILL = 7    
}TDE_SRC_MODE_E;

/* Sq���ƼĴ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
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

/* Aq���ƼĴ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
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

/* ������ʽ�Ĵ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
typedef union hiTDE_INS_U
{
    struct
    {
        HI_U32 u32Src1Mod       :3;     /* Դ1����ģʽ */
        HI_U32 u32Src2Mod       :2;     /* Դ2����ģʽ */
        HI_U32 u32IcsConv       :1;     /* ������ɫ�ռ�ת��ʹ�� */
        HI_U32 u32Resize        :1;     /* 2D����ʹ�� */
        HI_U32 u32DfeEn         :1;     /* ����˸�˲���ʹ�� */
#ifdef TDE_VERSION_MPW
        HI_U32 u32Reserve1      :3;     /* ���� */
#else
	    HI_U32 u32Y1En		:1;		    /* Y1ͨ��ʹ��*/	
	    HI_U32 u32Y2En		:1;		    /* Y2ͨ��ʹ��*/
        HI_U32 u32Reserve1      :1;     /* ���� */
#endif
        HI_U32 u32Clut          :1;     /* CLUTʹ�� */
        HI_U32 u32ColorKey      :1;     /* Colorkeyʹ�� */
        HI_U32 u32IcscSel      :1;      /* ������ɫ�ռ�ת��ѡ��*/
        HI_U32 u32Clip          :1;     /* Clipʹ�� */
        HI_U32 u32MbMode        :3;     /* ��鴦��ģʽ */
        HI_U32 u32MbEn          :1;     /* ������ʹ�� */
        HI_U32 u32AqIrqMask     :4;     /* �첽�����ж����� */
        HI_U32 u32SqIrqMask     :5;     /* ͬ�������ж����� */
        HI_U32 u32OcsConv      :1;      /*�����ɫ�ռ�ת��ʹ��*/
        HI_U32 u32BlockFlag     :1;     /*�Ƿ�ֿ��־*/
        HI_U32 u32FirstBlockFlag    :1; /*��һ���ֿ��־*/
        HI_U32 u32LastBlockFlag     :1; /*���һ���ֿ��־*/
    }stBits;
    HI_U32 u32All;
}TDE_INS_U;

/* Դλͼ���ͼĴ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
typedef union hiTDE_SRC_TYPE_U
{
    struct
    {
        HI_U32 u32Pitch        :16;
        HI_U32 u32SrcColorFmt  :5;
        HI_U32 u32AlphaRange   :1;
#ifdef TDE_VERSION_MPW
        HI_U32 u32Reserve1     :2;  /* ���� */
#else
        HI_U32 u32ColorizeEnable:1; /* Colorizeʹ�ܣ�ֻ��Src2��Ч;Src1Ϊ����λ */
        HI_U32 u32Reserve1     :1;  /* ���� */
#endif
        HI_U32 u32HScanOrd     :1;
        HI_U32 u32VScanOrd     :1;
        HI_U32 u32Reserve2     :3;
        HI_U32 u32RgbExp       :1;
        HI_U32 u32Reserve3     :2;
    }stBits;
    HI_U32 u32All;
}TDE_SRC_TYPE_U;

/* λͼ��ʼλ�üĴ������ø�ʽ */
typedef union hiTDE_SUR_XY_U
{
    struct
    {
        HI_U32 u32X            :12; /* X������ */
        HI_U32 u32Reserve1     :4;  /* ���� */
        HI_U32 u32Y            :12; /* Y������ */
        HI_U32 u32Reserve2     :4;  /* ���� */
    }stBits;
    HI_U32 u32All;
}TDE_SUR_XY_U;

/* λͼ�ߴ�Ĵ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
typedef union hiTDE_SUR_SIZE_U
{
    struct
    {
        HI_U32 u32Width        :12;             /* ͼ���� */
        HI_U32 u32AlphaThresholdLow     :4;     /* alpha�о���ֵ��4λ,��Ŀ��size�Ĵ�������Ч;��Դ2size�Ĵ�����Ϊ����λ */
        HI_U32 u32Height       :12;             /* ͼ��߶� */
        HI_U32 u32AlphaThresholdHigh     :4;    /* alpha�о���ֵ��4λ,��Ŀ��size�Ĵ�������Ч;��Դ2size�Ĵ�����Ϊ����λ*/
    }stBits;
    HI_U32 u32All;
}TDE_SUR_SIZE_U;

/* Ŀ��λͼ���ͼĴ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
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

/* ��ɫ�ռ�ת���Ĵ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
typedef union hiTDE_COLOR_CONV_U
{
    struct
    {
        HI_U32 u32InColorImetry       :1;  /*����ɫ��ת����׼*/
        HI_U32 u32InRgb2Yc       :1;
        HI_U32 u32InColorSpace  :1;     /*����ɫ��ת��ʹ�õľ���*/
        HI_U32 u32InChromaFmt   :1;     /*����ɫ����ɫ��ʽ*/
        HI_U32 u32OutColorImetry    :1; /*���ɫ��ת����׼*/
        HI_U32 u32OutColorSpace     :1; /*���ɫ��ת��ʹ�õľ���*/
        HI_U32 u32OutChromaFmt      :1; /*���ɫ����ɫ��ʽ*/
        HI_U32 u32Reserve1       :2;
        HI_U32 u32ClutMod        :1;
        HI_U32 u32ClutReload     :1;
#ifdef TDE_VERSION_MPW
        HI_U32 u32Reserve2       :5;        /* ���� */
#else
        HI_U32 u32Reserve2       :1;        /* ���� */
        HI_U32 u32OcscReload	:1;	        /* ���CSC�Զ����������ʹ�� */
        HI_U32 u32OcscCustomEn	:1;	        /* �Զ������CSCʹ��*/
        HI_U32 u32IcscReload	:1;	        /* ����CSC�Զ����������ʹ�� */
        HI_U32 u32IcscCustomEn	:1;	        /* �Զ�������CSCʹ��*/
#endif
        HI_U32 u32Alpha0         :8;
        HI_U32 u32Alpha1         :8;
    }stBits;
    HI_U32 u32All;
}TDE_COLOR_CONV_U;

/* ���żĴ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
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
        HI_U32 u32DfeAlphaDisable   :1; /*alpha����˸��ʹ��*/
        HI_U32 u32Reserve6     :5;
    }stBits;
    HI_U32 u32All;
}TDE_2D_RSZ_U;

/* λͼ�ߴ�Ĵ������ø�ʽ,���庬��ο��Ĵ����ֲ� */
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
        HI_U32 u32BlendReverse      :1; /*����ǰ�󱳾�����ʹ��*/
    }stBits;
    HI_U32 u32All;
}TDE_ALU_U;

/* ARGB/AYUV����˳��Ĵ�����ʽ */
typedef union hiTDE_ARGB_ORDER_U
{
    struct
    {
        HI_U32 u32Src1ArgbOrder :   5;  /* Src1��ARGB����˳�� */
        HI_U32 u32Reserved1 :   3;      /* ���� */
        HI_U32 u32Src2ArgbOrder :   5;  /* Src2��ARGB����˳�� */
        HI_U32 u32Reserved2 :   3;      /* ���� */
        HI_U32 u32TarArgbOrder  :   5;  /* Ŀ���ARGB����˳�� */
        HI_U32 u32Reserved3 :   3;      /* ���� */
    }stBits;
    HI_U32 u32All;
}TDE_ARGB_ORDER_U;

/* Colorkey Mask�Ĵ��� */
typedef union hiTDE_COLORKEY_MASK_U
{
    struct
    {
        HI_U32 u32BlueMask  :   8;  /* ��ɫ����/clut/V������mask */
        HI_U32 u32GreenMask :   8;  /* ��ɫ����/U������mask */
        HI_U32 u32RedMask   :   8;  /* ��ɫ����/Y������mask */
        HI_U32 u32AlphaMask :   8;  /* Alpha������mask */
    }stBits;
    HI_U32 u32All;
}TDE_COLORKEY_MASK_U;

/* alpha blendģʽ�Ĵ��� */
typedef union hiTDE2_ALPHA_BLEND_U
{
    struct
    {
        HI_U32 u32Src1BlendMode :       4;      /* Src1�ĵ���ģʽ */
        HI_U32 u32Src1PremultiEn :      1;      /* Src1Ԥ������alphaʹ�� */
        HI_U32 u32Src1MultiGlobalEn :   1;      /* Src1Ԥ��ȫ��alphaʹ�� */
        HI_U32 u32Src1PixelAlphaEn    :   1;    /* Src1����alphaʹ�� */
        HI_U32 u32Src1GlobalAlphaEn   :   1;    /* Src1ȫ��alphaʹ�� */
        HI_U32 u32Src2BlendMode :       4;      /* Src2�ĵ���ģʽ */
        HI_U32 u32Src2PremultiEn :      1;      /* Src2Ԥ������alphaʹ�� */
        HI_U32 u32Src2MultiGlobalEn :   1;      /* Src2Ԥ��ȫ��alphaʹ�� */
        HI_U32 u32Src2PixelAlphaEn    :   1;    /* Src2����alphaʹ�� */
        HI_U32 u32Src2GlobalAlphaEn   :   1;    /* Src2ȫ��alphaʹ�� */
        HI_U32 u32AlphaRopEn    :   1;          /* Alpha����ʱAlphaʹ�� */
        HI_U32 u32Reserved  :   15;             /* ���� */
    }stBits;
    HI_U32 u32All;
}TDE_ALPHA_BLEND_U;

typedef union hiTDE_Y_PITCH
{
    struct
    {
        HI_U32 u32Pitch     :   16; /* �п�� */
        HI_U32 u32Reserved	:16;	/* ����*/
    }stBits;
    HI_U32 u32All;
}TDE_Y_PITCH_U;

/* �˲������б��� */
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

/* ÿ��Ӳ���ڵ���Ϣ����,����ά��Ӳ���ڵ� */
typedef struct hiTDE_BUF_NODE_S
{
    struct list_head stList;
    HI_U32 u32PhyAddr;              /*ָ��Ӳ��buffer�����ַ*/
    HI_U32* pu32VirAddr;            /*Ӳ��buffer��Ӧ�������ַ*/
    HI_S32 s32Handle;               /*��ǰ�ڵ�������job handle*/
    HI_VOID* pSwNode;               /*��ǰ�ڵ�ָ�������ڵ�ָ��*/
    HI_U32 u32WordSize;             /*��ǰ�ڵ������������С(��Ϊ��λ)*/
    HI_U32 u32CurUpdate;            /*��ǰ�ڵ���±��*/
    struct hiTDE_BUF_NODE_S* pstParentAddr;/*���̳�������Ϣ�ĸ��ڵ��ַ*/
}TDE_BUF_NODE_S;


/* TDE��������ʱ��״̬��Ϣ */
typedef struct hiTDE_SUSP_STAT_S
{
    HI_S32 s32AqSuspLine;       /*Aq����ʱִ�е�����,���Ϊ-1��ʾ��Ч*/
    TDE_BUF_NODE_S* pstSwBuf;
    HI_VOID *pSwNode;       /*ָ����������ڵ��ָ��*/
}TDE_SUSP_STAT_S;

/* ���ò������׵�ַ */
typedef struct hiTDE_PARA_TABLE_S
{
    HI_U32 u32HfCoefAddr;
    HI_U32 u32VfCoefAddr;
}TDE_PARA_TABLE_S;

/****************************************************************************/
/*                             TDE hal �ڲ���������                         */
/****************************************************************************/
/* ӳ���Ĵ�������ַ */
STATIC volatile HI_U32* s_pu32BaseVirAddr = HI_NULL;

/* Aq����ʱ��״̬��Ϣ */
STATIC TDE_SUSP_STAT_S s_stSuspStat = {0};

/* ���ò������׵�ַ */
STATIC TDE_PARA_TABLE_S s_stParaTable = {0};

#ifdef TDE_PROC_ENABLE
/* proc��ӡ��Ҫ��ȫ�ֱ��� */
extern HI_U32 g_u32TdeAqCurProcNum;
extern HI_U32 g_u32TdeSqCurProcNum;


#endif

/** ����˸���� Ĭ��Ϊ�Զ� */
STATIC TDE_DEFLICKER_LEVEL_E s_eDeflickerLevel = TDE_DEFLICKER_AUTO;

/*alpha�о�����*/
STATIC HI_BOOL s_bEnAlphaThreshold = HI_FALSE;

/*alpha�о���ֵ*/
STATIC HI_U8 s_u8AlphaThresholdValue = 0xff;
#define TDE_CSCTABLE_SIZE 7

STATIC HI_U32 s_u32Rgb2YuvCsc[TDE_CSCTABLE_SIZE] = 
    {0x0096004d, 0xffd5001d, 0x0080ffab, 0xff950080, 0x0000ffeb, 0x00000000, 0x02010000};
STATIC HI_U32 s_u32Yuv2RgbCsc[TDE_CSCTABLE_SIZE] = 
    {0x00000100, 0x01000167, 0xff49ffa8, 0x01c60100, 0x00000000, 0x06030000, 0x00000000};

STATIC HI_U32 s_u32Rgb2YuvCoefAddr = 0;
STATIC HI_U32 s_u32Yuv2RgbCoefAddr = 0;
/****************************************************************************/
/*                             TDE hal �ڲ���������                         */
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
/*                             TDE hal ctl �ӿ�ʵ��                         */
/****************************************************************************/
/*****************************************************************************
* Function:      TdeHalInit
* Description:   ��Ҫ����ӳ��TDE����ַ
* Input:         u32BaseAddr:�Ĵ�������ַ
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
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
    /*��ʼ��TDE�ڴ��*/
    if (HI_SUCCESS != wmeminit())
    {
        goto TDE_INIT_ERR;
    }

    /* ���ò������׵�ַ */
    if (HI_SUCCESS != TdeHalInitParaTable())
    {
        goto TDE_INIT_ERR;
    }

    /* �Ĵ���ӳ�� */
    s_pu32BaseVirAddr = (volatile HI_U32*)TDE_REG_MAP(u32BaseAddr, TDE_REG_SIZE);
    if(HI_NULL == s_pu32BaseVirAddr)
	{
        goto TDE_INIT_ERR;
	}

    TdeHalSetClock();

    /* �Ĵ�����λ */    
	TdeHalCtlReset();

    /* ��ʼ��SQ/AQ */
    TdeHalInitQueue(); 
    
    return HI_SUCCESS;

TDE_INIT_ERR:
    return HI_FAILURE;
}

/*****************************************************************************
* Function:      TdeHalOpen
* Description:   ��Ҫ���ڳ�ʼ������ļĴ���
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalOpen(HI_VOID)
{
    /* do sth ... */
    return HI_SUCCESS;
}

/*****************************************************************************
* Function:      TdeHalRelease
* Description:   ��Ҫ�����ͷ�ӳ���TDE����ַ
* Input:         ��
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
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


    
    /* ��ӳ�����ַ */
    TDE_REG_UNMAP(s_pu32BaseVirAddr);
    s_pu32BaseVirAddr = HI_NULL;

    /*TDE�ڴ��ȥ��ʼ��*/
    wmemterm();
    
    return;
}

/*****************************************************************************
* Function:      TdeHalCtlIsIdle
* Description:   ��ѯTDE�Ƿ���IDLE״̬
* Input:         ��
* Output:        ��
* Return:        True: Idle/False: Busy
* Others:        ��
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdle(HI_VOID)
{
    return (HI_BOOL)(!(TDE_READ_REG(s_pu32BaseVirAddr, TDE_STA) & 0x1));
}

/*****************************************************************************
* Function:      TdeHalCtlIsIdleSafely
* Description:   ѭ����β�ѯ, ȷ��TDE�Ƿ���IDLE״̬
* Input:         ��
* Output:        ��
* Return:        True: Idle/False: Busy
* Others:        ��
*****************************************************************************/
HI_BOOL TdeHalCtlIsIdleSafely(HI_VOID)
{
    HI_U32 i = 0;
    
    /* ������ȡ���Ӳ��״̬,ȷ��TDE��� */
    for (i = 0; i < TDE_MAX_READ_STATUS_TIME; i++)
    {
        /* ֻҪ��һ�η�IDLE, ����Ϊ�Ƿ�IDLE */
        if (!TdeHalCtlIsIdle())
        {
            return HI_FALSE;
        }
    }
    return HI_TRUE;
}

/*****************************************************************************
* Function:      TdeHalCtlIntMask
* Description:   ��ȡSq/Aq���ж�״̬
* Input:         enListType: ����Sq/Aq������
* Output:        ��
* Return:        Sq/Aq�ж�״̬
* Others:        ��
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
* Description:   ��λTDE HAL����״̬,�����������
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalResetStatus(HI_VOID)
{
    s_stSuspStat.s32AqSuspLine = TDE_SUSP_LINE_INVAL;
    s_stSuspStat.pSwNode = HI_NULL;
    return;
}

/*****************************************************************************
* Function:      TdeHalCtlReset
* Description:   ��λ�����ж�״̬
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalCtlReset(HI_VOID)
{
    /* ��λ */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_RST, 0xffffffff);

    /* ���ж�״̬ */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_INT, 0x800f001f);
}

/*****************************************************************************
* Function:      TdeHalCtlIntClear
* Description:   ����Ӧ���ж�״̬
* Input:         enListType: ����Sq/Aq������
*                u32Stats: ����Ӧ���ж�״̬
* Output:        ��
* Return:        ��
* Others:        ��
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

/*�ж�TDE�Ĺ���������ͬ�������첽*/
HI_BOOL TdeHalIsSqWork()
{
    return (HI_BOOL)((TDE_READ_REG(s_pu32BaseVirAddr, TDE_STA) & 0x4) >> 2);
}

/****************************************************************************/
/*                             TDE hal node �ӿ�ʵ��                        */
/****************************************************************************/
/*****************************************************************************
* Function:      TdeHalNodeInitNd
* Description:   ��ʼ����������һ��TDE�����ڵ�����Ľṹ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeInitNd(TDE_HWNode_S* pHWNode, HI_BOOL bChild)
{
    TDE_INS_U unIns;

    TDE_ASSERT(HI_NULL != pHWNode);

    /* ������ӽڵ�, ����Ҫ���ڵ��������Ϣ,ֻ��Update��� */
    if (bChild)
    {
        TDE_2D_RSZ_U unRsz;
	    HI_BOOL bClipOut = pHWNode->u32TDE_CLIP_START >> 31;
	  
        unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
        unRsz.stBits.u32VfCoefReload = 0;/* ������ӽڵ�����Ҫ���²����� */
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
    else /* ����������Ϣ��� */
    {
        memset(pHWNode, 0, sizeof(TDE_HWNode_S));
    }
    
    /* ������������ж�,ͬ������ɸ����ж�, �رսڵ�����ж� */
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32SqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    unIns.stBits.u32AqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    pHWNode->u32TDE_INS = unIns.u32All;
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
}

/* AE5D03390:������������clip bug */

HI_VOID TdeHalNodeInitChildNd(TDE_HWNode_S* pHWNode, HI_U32 u32TDE_CLIP_START, HI_U32 u32TDE_CLIP_STOP)
{
#ifndef HIGO_CODE_CUT
    TDE_INS_U unIns;
	TDE_2D_RSZ_U unRsz;
	HI_BOOL bClipOut = pHWNode->u32TDE_CLIP_START >> 31;

    TDE_ASSERT(HI_NULL != pHWNode);

    /* ������ӽڵ�, ����Ҫ���ڵ��������Ϣ,ֻ��Update��� */

	unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
	unRsz.stBits.u32VfCoefReload = 0;/* ������ӽڵ�����Ҫ���²����� */
	unRsz.stBits.u32HfCoefReload = 0;
	pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
	pHWNode->u64TDE_UPDATE = 0;
	TDE_SET_UPDATE(u32TDE_2D_RSZ, pHWNode->u64TDE_UPDATE);

	if(bClipOut)
	{
	    pHWNode->u32TDE_INS = pHWNode->u32TDE_INS | 0x4000; /* ����clip ����*/
	    pHWNode->u32TDE_CLIP_START = u32TDE_CLIP_START;
	    pHWNode->u32TDE_CLIP_STOP = u32TDE_CLIP_STOP;
	    TDE_SET_UPDATE(u32TDE_CLIP_START, pHWNode->u64TDE_UPDATE);
	    TDE_SET_UPDATE(u32TDE_CLIP_STOP, pHWNode->u64TDE_UPDATE);
	}
    
    /* ������������ж�,ͬ������ɸ����ж�, �رսڵ�����ж� */
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32SqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    unIns.stBits.u32AqIrqMask = TDE_SQ_MASK_DISABLE_ALL;
    pHWNode->u32TDE_INS = unIns.u32All;
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    #endif
}

/*****************************************************************************
* Function:      TdeHalNodeGetNdSize
* Description:   ��ȡ��ǰ���������µĽڵ�������ٸ���(4�ֽ�)
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
* Output:        ��
* Return:        ���������ֽ���
* Others:        ��
*****************************************************************************/
HI_U32 TdeHalNodeGetNdSize(TDE_HWNode_S* pHWNode)
{
    HI_S32 u32Size = 0;
    HI_U32 i = 0;

    TDE_ASSERT(HI_NULL != pHWNode);

    /* ͳ��u32TDE_UPDATE�е���Ч����,���㵱ǰ�����������С */
    for (i = 0; i < sizeof(TDE_HWNode_S)/4 - 2; i++)
    {
        if ( 1 == ((pHWNode->u64TDE_UPDATE >> i) & 1) )
        {
            u32Size++;
        }
    }
    return (u32Size << 0x2);/* ����Word�����ֽ��� */
}

/*****************************************************************************
* Function:      TdeHalNodeMakeNd
* Description:   �ɵ�ǰ���������µĽڵ�pHWNode,�����ɿ���ֱ�����õĽڵ㵽pBuf��
* Input:         pBuf: �����ڵ�󻺴�ڵ��buffer
*                pHWNode: ������ڻ���Ľڵ�ṹָ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalNodeMakeNd(HI_VOID* pBuf, TDE_HWNode_S* pHWNode)
{
    HI_U32 *pNodeBuf = (HI_U32*)pBuf;
    HI_U32 *pu32Node = (HI_U32*)pHWNode;
    HI_U32 i = 0;
    
    TDE_ASSERT(HI_NULL != pBuf);
    TDE_ASSERT(HI_NULL != pHWNode);

    /* ��pHWNode�е���Ч���ݸ��Ƶ�����ڵ��buffer�� */
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
* Description:   ����TDE����
* Input:         enListType: ��������
*                u32NodePhyAddr: �����׽ڵ��ַ
*                u32Update:�����׽ڵ���±�ʶ
*                bAqUseBuff: �Ƿ�ʹ����ʱbuffer
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_S32 TdeHalNodeExecute(TDE_LIST_TYPE_E enListType, HI_U32 u32NodePhyAddr, HI_U64 u64Update, HI_BOOL bAqUseBuff)
{
    TDE_AQ_CTRL_U unAqCtrl;
#ifndef HIGO_CODE_CUT      
    TDE_SQ_CTRL_U unSqCtrl;
#endif    
    if (enListType == TDE_LIST_AQ)
    {
        /*TDE����*/
        if(TdeHalCtlIsIdle())
        {
            /*д���׽ڵ��ַ*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_NADDR, u32NodePhyAddr);

            /*д���׽ڵ���±�ʶ*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_UPDATE, (HI_U32)(u64Update & 0xffffffff));
#if defined (TDE_VERSION_PILOT) || defined (TDE_VERSION_FPGA)
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_UPDATE2, (HI_U32)((u64Update >> 32) & 0xffffffff));
#endif

            unAqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_AQ_CTRL);

            /*����Ҫʹ����ʱbuffer,����ģʽΪ��ǰ�ڵ���ɴ�ϣ�����Ϊ��ǰ�ڵ�
               ��ǰ����ɴ��*/
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
            
            /* ����Aq*/
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
        /*TDE���л��첽�����ڹ����������ύͬ������*/
        if(TdeHalCtlIsIdle() || ((TDE_READ_REG(s_pu32BaseVirAddr, TDE_STA) & 0x4) >> 2))
        {
            /*д���׽ڵ��ַ*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_NADDR, u32NodePhyAddr);

            /*д���׽ڵ���±�ʶ*/
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_UPDATE, (HI_U32)(u64Update & 0xffffffff));
            
#if defined (TDE_VERSION_PILOT) || defined (TDE_VERSION_FPGA)
            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_UPDATE2, (HI_U32)((u64Update >> 32) & 0xffffffff));
#endif
            /*ʹ��ͬ������*/
            unSqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL);

            unSqCtrl.stBits.u32SqEn = 0x1;
            unSqCtrl.stBits.u32SqUpdateFlag = 0x1;

            TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL, unSqCtrl.u32All);

            /* ����Sq*/
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
* Description:   ����Դ1λͼ��Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvSurface: �������õ�λͼ��Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetSrc1(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface)
{
    TDE_SRC_TYPE_U unSrcType;
    TDE_SUR_XY_U unXy;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvSurface);

    /*����Դλͼ������Ϣ*/
    unSrcType.u32All = pHWNode->u32TDE_S1_TYPE;
    unSrcType.stBits.u32Pitch = (HI_U32)pDrvSurface->u32Pitch;
    unSrcType.stBits.u32SrcColorFmt = (HI_U32)pDrvSurface->enColorFmt;
    unSrcType.stBits.u32AlphaRange = (HI_U32)pDrvSurface->bAlphaMax255;
    unSrcType.stBits.u32HScanOrd = (HI_U32)pDrvSurface->enHScan;
    unSrcType.stBits.u32VScanOrd = (HI_U32)pDrvSurface->enVScan;
    unSrcType.stBits.u32RgbExp = 0; /*һֱʹ�õ�λ���Ϊ0,��λʹ�õ�λ����չ��ʽ*/

    unXy.u32All = pHWNode->u32TDE_S1_XY;
    unXy.stBits.u32X = pDrvSurface->u32Xpos;
    unXy.stBits.u32Y = pDrvSurface->u32Ypos;

    /*Դ1λͼ���������Targetλͼһ��,��˲�����Դ1�Ĵ�С*/

    /*���û���ڵ�*/
    pHWNode->u32TDE_S1_ADDR = pDrvSurface->u32PhyAddr;
    pHWNode->u32TDE_S1_TYPE = unSrcType.u32All;
    pHWNode->u32TDE_S1_XY = unXy.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_S1_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S1_TYPE, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S1_XY, pHWNode->u64TDE_UPDATE);
    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetSrc2
* Description:   ����Դ2λͼ��Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvSurface: �������õ�λͼ��Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
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
        /*CNcomment:���û�δ�����Զ���ϵ����ICSC����ʹ��,
        ��ǿ��ʹ��TDE������ϵ��(TDEĬ��ϵ����������)*/
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
* Description:   ���ú���ʽԴλͼ������Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvMbY: �������õ�����λͼ��Ϣ
*                enMbOpt: ���ģʽѡ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetSrcMbY(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvMbY, TDE_DRV_MB_OPT_MODE_E enMbOpt)
{
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvMbY);

    if (TDE_MB_RASTER_OPT == enMbOpt)
    {
        /* ����Ǻ�����դ��ϲ���ģʽ,������Ϣֱ�����õ�Src2�� */
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
        /*��Ϊ��������ʱ,��Ҫ����Դ2�Ĵ�С,��Ϊλͼ��С��Ϣ*/
        unSurSize.stBits.u32Width = (HI_U32)pDrvMbY->u32Width;
        unSurSize.stBits.u32Height = (HI_U32)pDrvMbY->u32Height;
        pHWNode->u32TDE_S2_SIZE = unSurSize.u32All;
        TDE_SET_UPDATE(u32TDE_S2_SIZE, pHWNode->u64TDE_UPDATE);
    }

    return;
}

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
* Description:   ����Ŀ��λͼ��Ϣ
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pDrvSurface: �������õ�λͼ��Ϣ
*                enAlphaFrom: alpha from
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetTgt(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, TDE_DRV_OUTALPHA_FROM_E enAlphaFrom)
{
    TDE_TAR_TYPE_U unTarType;
    TDE_SUR_SIZE_U unSurSize;
    TDE_SUR_XY_U unXy;
    
    TDE_ASSERT(HI_NULL != pHWNode);

    /*����Դλͼ������Ϣ*/
    unTarType.u32All = pHWNode->u32TDE_TAR_TYPE;
    unTarType.stBits.u32Pitch = (HI_U32)pDrvSurface->u32Pitch;
    unTarType.stBits.u32TarColorFmt = (HI_U32)pDrvSurface->enColorFmt;
    unTarType.stBits.u32AlphaRange = (HI_U32)pDrvSurface->bAlphaMax255;
    unTarType.stBits.u32HScanOrd = (HI_U32)pDrvSurface->enHScan;
    unTarType.stBits.u32VScanOrd = (HI_U32)pDrvSurface->enVScan;
    unTarType.stBits.u32AlphaFrom = (HI_U32)enAlphaFrom;
    unTarType.stBits.u32RgbRound = 0; /*һֱʹ��ʹ����������Ľ�λ��ʽ*/

    /*����λͼ��С��Ϣ*/
    unSurSize.u32All = pHWNode->u32TDE_TS_SIZE;
    unSurSize.stBits.u32Width = (HI_U32)pDrvSurface->u32Width;
    unSurSize.stBits.u32Height = (HI_U32)pDrvSurface->u32Height;

    /*����alpha�о���ֵ */
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


    /*���û���ڵ�*/
    pHWNode->u32TDE_TAR_ADDR = pDrvSurface->u32PhyAddr;
    pHWNode->u32TDE_TAR_TYPE = unTarType.u32All;
    pHWNode->u32TDE_TAR_XY = unXy.u32All;
    pHWNode->u32TDE_TS_SIZE = unSurSize.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_TAR_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_TAR_TYPE, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_TAR_XY, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_TS_SIZE, pHWNode->u64TDE_UPDATE);
    
    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetBaseOperate
* Description:   ���û�����������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                enMode: ��������ģʽ
*                enAlu: ALUģʽ
*                pstColorFill: �����������ģʽ����������,���ȡ��ֵ
* Output:        ��
* Return:        ��
* Others:        ��
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
    case TDE_QUIKE_FILL:/*�������*/
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
    case TDE_QUIKE_COPY:/*���ٿ���*/
        {
            unAluMode.stBits.u32AluMod = TDE_SRC1_BYPASS;
            unIns.stBits.u32Src1Mod = TDE_SRC_QUICK_COPY;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_DISA;
        }
        break;
    case TDE_NORM_FILL_1OPT:/*��ͨ��Դ���*/
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
    case TDE_NORM_BLIT_1OPT:/*��ͨ��Դ��������*/
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
    
    case TDE_NORM_FILL_2OPT:/*��ɫ��λͼ�����������*/
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
    case TDE_NORM_BLIT_2OPT:/*��ͨ˫Դ�������� */
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
    case TDE_MB_2OPT:/*���ϲ�����*/
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
    case TDE_MB_C_OPT:/*���ɫ���ϲ�������*/
        {
            unIns.stBits.u32Src1Mod = TDE_SRC_MODE_DISA;
            unIns.stBits.u32Src2Mod = TDE_SRC_MODE_BMP;
            unIns.stBits.u32MbEn = 1;
            unAluMode.stBits.u32AluMod = TDE_SRC2_BYPASS;
        }
        break;
    case TDE_MB_Y_OPT:/*�����������*/
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

    /*���û���ڵ�*/
    pHWNode->u32TDE_ALU = unAluMode.u32All;
    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetGlobalAlpha
* Description:   ����Alpha��ϲ���
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                u8Alpha: Alpha�������ֵ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/

HI_VOID TdeHalNodeSetGlobalAlpha(TDE_HWNode_S* pHWNode, HI_U8 u8Alpha)
{
#ifndef HIGO_CODE_CUT
    TDE_ALU_U unAluMode;

    TDE_ASSERT(HI_NULL != pHWNode);

    TDE_ALPHA_ADJUST(u8Alpha);
    
    /*���û���ڵ�*/
    unAluMode.u32All = pHWNode->u32TDE_ALU;
    unAluMode.stBits.u32GlobalAlpha = u8Alpha;
    pHWNode->u32TDE_ALU = unAluMode.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);

    return;
    #endif
}

#if 1
/*****************************************************************************
* Function:      TdeHalNodeSetExpAlpha
* Description:   ����RGB5551��Alpha��չʱ,��չΪalpha0, alpha1������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                u8Alpha0: Alpha0����ֵ
*                u8Alpha1: Alpha1����ֵ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetExpAlpha(TDE_HWNode_S* pHWNode, TDE_DRV_SRC_E enSrc, HI_U8 u8Alpha0, HI_U8 u8Alpha1)
{
    TDE_COLOR_CONV_U unConv;
    
    TDE_ASSERT(HI_NULL != pHWNode);

    TDE_ALPHA_ADJUST(u8Alpha0);
    TDE_ALPHA_ADJUST(u8Alpha1);
    
    /*����alpha0, alpha1*/
    unConv.u32All = pHWNode->u32TDE_COLOR_CONV;
    unConv.stBits.u32Alpha0 = u8Alpha0;
    unConv.stBits.u32Alpha1 = u8Alpha1;
    pHWNode->u32TDE_COLOR_CONV = unConv.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);

    if(TDE_DRV_SRC_S1 & enSrc)
    {
        pHWNode->u32TDE_S1_TYPE |= 0x20000000;
        
        /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
        TDE_SET_UPDATE(u32TDE_S1_TYPE, pHWNode->u64TDE_UPDATE);
    }

    if(TDE_DRV_SRC_S2 & enSrc)
    {
        pHWNode->u32TDE_S2_TYPE |= 0x20000000;
        
        /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
        TDE_SET_UPDATE(u32TDE_S2_TYPE, pHWNode->u64TDE_UPDATE);
    }

    return;
}

/*****************************************************************************
* Function:      TdeHalNodeSetAlphaBorder
* Description:   �����Ƿ�ʹ��Alplha�߽紦��
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                bEnable: �Ƿ�ʹ��Alplha�߽�
* Output:        ��
* Return:        ��
* Others:        ��
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
* Description:   ����ROP�������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                enRopCode: ROP������
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/

HI_VOID TdeHalNodeSetRop(TDE_HWNode_S* pHWNode, TDE2_ROP_CODE_E enRgbRop, TDE2_ROP_CODE_E enAlphaRop)
{
#ifndef HIGO_CODE_CUT
    TDE_ALU_U unAluMode;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    /*���û���ڵ�*/
    unAluMode.u32All = pHWNode->u32TDE_ALU;
    unAluMode.stBits.u32RgbRopMod = (HI_U32)enRgbRop;
    unAluMode.stBits.u32AlphaRopMod = (HI_U32)enAlphaRop;
    pHWNode->u32TDE_ALU = unAluMode.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);
    #endif
}

/*****************************************************************************
* Function:      TdeHalNodeSetColorExp
* Description:   ������ɫ��չ����ɫУ������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pClutCmd: Clut�����������
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/

HI_VOID TdeHalNodeSetClutOpt(TDE_HWNode_S* pHWNode, TDE_DRV_CLUT_CMD_S* pClutCmd, HI_BOOL bReload)
{
#ifndef HIGO_CODE_CUT
    TDE_INS_U unIns;
    TDE_COLOR_CONV_U unConv;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pClutCmd);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32Clut = 1; /*ʹ��Clut����*/

    unConv.u32All = pHWNode->u32TDE_COLOR_CONV;
    unConv.stBits.u32ClutMod = (HI_U32)pClutCmd->enClutMode;
    unConv.stBits.u32ClutReload = (HI_U32)bReload; /* reload clut ���Ĵ��� */

    /*���û���ڵ�*/
    pHWNode->u32TDE_CLUT_ADDR = (HI_U32)pClutCmd->pu8PhyClutAddr;
    pHWNode->u32TDE_INS = unIns.u32All;
    pHWNode->u32TDE_COLOR_CONV = unConv.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_CLUT_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);
    #endif
}

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
#ifndef HIGO_CODE_CUT
HI_VOID TdeHalNodeSetColorKey(TDE_HWNode_S* pHWNode, TDE_COLORFMT_CATEGORY_E enFmtCat, 
                              TDE_DRV_COLORKEY_CMD_S* pColorKey)
{
    TDE_INS_U unIns;
    TDE_ALU_U unAluMode;

    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pColorKey);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32ColorKey = 1; /*ʹ��Color Key����*/
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
    else if (TDE_COLORFMT_CATEGORY_CLUT == enFmtCat)/*CLUT��ʽֻ������*/
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
    else if (TDE_COLORFMT_CATEGORY_YCbCr == enFmtCat)/*YCbCr��ʽ*/
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
    
    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_ALU, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_CK_MIN, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_CK_MAX, pHWNode->u64TDE_UPDATE);
    return;
}
#endif
/*****************************************************************************
* Function:      TdeHalNodeSetClipping
* Description:   ���þ��βü���������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pClip: �ü����η�Χ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/

HI_VOID TdeHalNodeSetClipping(TDE_HWNode_S* pHWNode, TDE_DRV_CLIP_CMD_S* pClip)
{
#ifndef HIGO_CODE_CUT
    TDE_INS_U unIns;
    TDE_SUR_SIZE_U unClipPos;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pClip);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32Clip = 1; /*����clip����*/

    if(pClip->bInsideClip)
    {
        unClipPos.u32All = 0;
    }
    else
    {
        /* ������clipָʾ */
        unClipPos.u32All = 0x80000000; 
    }
    unClipPos.stBits.u32Width = pClip->u16ClipStartX;
    unClipPos.stBits.u32Height = pClip->u16ClipStartY;
    pHWNode->u32TDE_CLIP_START = unClipPos.u32All;

    unClipPos.u32All = 0; /* ���¸�λ,׼����һ���� AI7D02798 */
    unClipPos.stBits.u32Width = pClip->u16ClipEndX;
    unClipPos.stBits.u32Height = pClip->u16ClipEndY;
    pHWNode->u32TDE_CLIP_STOP = unClipPos.u32All;

    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_CLIP_START, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_CLIP_STOP, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
    #endif
}

/*****************************************************************************
* Function:      TdeHalNodeSetFlicker
* Description:   ���ÿ���˸�˲��������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pFlicker: ����˸ϵ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetFlicker(TDE_HWNode_S* pHWNode, TDE_DRV_FLICKER_CMD_S* pFlicker)
{
    TDE_INS_U unIns;
    TDE_2D_RSZ_U unRsz;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pFlicker);
    
    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32DfeEn = 1; /*ʹ�ܿ���˸*/
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

    /*���û���ڵ�*/
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
    
    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
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
* Description:   ���������˲��������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pResize: ����ϵ��
* Output:        ��
* Return:        ��
* Others:        ��
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
    //unIns.stBits.u32Resize = 0x1; /*ʹ������*/
    
    unRsz.u32All = pHWNode->u32TDE_2D_RSZ;
    unRsz.stBits.u32HfMod = pResize->enFilterH;
    unRsz.stBits.u32VfMod = pResize->enFilterV;

    /* ��ֱ�˲� */
    if (TDE_DRV_FILTER_NONE != pResize->enFilterV)
    {
        unRsz.stBits.u32VfRingEn = pResize->bVfRing; /*ʹ����ֵ�˲�*/
        unRsz.stBits.u32VfCoefReload = 0x1; /*���봹ֱ����*/
        /* ���ݲ������ô�ֱ���Ų������׵�ַ */
        pHWNode->u32TDE_VF_COEF_ADDR = s_stParaTable.u32VfCoefAddr
                      + TdeHalGetResizeParaVTable(pResize->u32StepV) * TDE_PARA_VTABLE_SIZE;
        TDE_SET_UPDATE(u32TDE_VF_COEF_ADDR, pHWNode->u64TDE_UPDATE);

        if (TDE_NODE_SUBM_PARENT == enNodeType)
        {
        /* ���ô�ֱƫ�� */
        u32Sign = pResize->u32OffsetY >> 31; /*��ȡ����*/
        pHWNode->u32TDE_RSZ_Y_OFST = (u32Sign << 16) | (pResize->u32OffsetY & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_Y_OFST, pHWNode->u64TDE_UPDATE);
        unIns.stBits.u32Resize = 0x1; /*ʹ������*/
        }
    }
    /* ˮƽ�˲� */
    if (TDE_DRV_FILTER_NONE != pResize->enFilterH)
    {
        unRsz.stBits.u32HfRingEn = pResize->bHfRing;/*ʹ����ֵ�˲�*/
        unRsz.stBits.u32HfCoefReload = 0x1;/*����ˮƽ����*/
        /* ���ݲ������ô�ֱ���Ų������׵�ַ */
        pHWNode->u32TDE_HF_COEF_ADDR = s_stParaTable.u32HfCoefAddr
                    + TdeHalGetResizeParaHTable(pResize->u32StepH) * TDE_PARA_HTABLE_SIZE;
        TDE_SET_UPDATE(u32TDE_HF_COEF_ADDR, pHWNode->u64TDE_UPDATE);

        if (TDE_NODE_SUBM_PARENT == enNodeType)
        {
        /* ����ˮƽƫ�� */
        u32Sign = pResize->u32OffsetX >> 31; /*��ȡ����*/
        pHWNode->u32TDE_RSZ_X_OFST = (u32Sign << 16) | (pResize->u32OffsetX & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_X_OFST, pHWNode->u64TDE_UPDATE);
        unIns.stBits.u32Resize = 0x1; /*ʹ������*/
        }
    }

    unRsz.stBits.u32CoefSym = pResize->bCoefSym;/*�Գ��˲�ϵ��*/
    pHWNode->u32TDE_2D_RSZ = unRsz.u32All;
    if (TDE_NODE_SUBM_PARENT == enNodeType)
    {
        pHWNode->u32TDE_INS = unIns.u32All;

        unTarType.u32All = pHWNode->u32TDE_TAR_TYPE;
        unTarType.stBits.u32DfeFirstlineOutEn = pResize->bFirstLineOut;
        unTarType.stBits.u32DfeLastlineOutEn = pResize->bLastLineOut;
        pHWNode->u32TDE_TAR_TYPE = unTarType.u32All;

        /* �����˲����� */
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
* Description:   ������ɫ�ռ�ת���������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pConv: ��ɫ�ռ�ת������
* Output:        ��
* Return:        ��
* Others:        ��
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

    /*���û���ڵ�*/
    pHWNode->u32TDE_COLOR_CONV = unConv.u32All;
    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_COLOR_CONV, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);
    return;
}

/*****************************************************************************
* Function:      TdeHalNodeAddChild
* Description:   ���˲�����ʱ����ӽڵ�
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pChildInfo: ����ӽڵ��������Ϣ
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeAddChild(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo)
{
    TDE_SUR_XY_U unXy;
    TDE_INS_U unIns;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pChildInfo);

    /* ����Update��Ϣ���üĴ���:
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
        
        /* ����ˮƽƫ�� */
        u32Sign = pChildInfo->u32HOfst >> 31; /*��ȡ����*/
        pHWNode->u32TDE_RSZ_X_OFST = (u32Sign << 16) | (pChildInfo->u32HOfst & 0xffff);
        TDE_SET_UPDATE(u32TDE_RSZ_X_OFST, pHWNode->u64TDE_UPDATE);

        /* ���ô�ֱƫ�� */
        u32Sign = pChildInfo->u32VOfst >> 31; /*��ȡ����*/
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
    /* ����������Ϣ */
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
* Description:   ���ú�鴦���������
* Input:         pHWNode: ������ڻ���Ľڵ�ṹָ��
*                pMbCmd: ��鴦�����
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
HI_VOID TdeHalNodeSetMbMode(TDE_HWNode_S* pHWNode, TDE_DRV_MB_CMD_S* pMbCmd)
{
    TDE_INS_U unIns;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pMbCmd);

    unIns.u32All = pHWNode->u32TDE_INS;
    unIns.stBits.u32MbMode = (HI_U32)pMbCmd->enMbMode;
    pHWNode->u32TDE_INS = unIns.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_INS, pHWNode->u64TDE_UPDATE);

    return;
}



/****************************************************************************/
/*                             TDE hal �ڲ�����ʵ��                         */
/****************************************************************************/
/*****************************************************************************
* Function:      TdeHalInitParaTable
* Description:   ��ʼ�����ò�����
* Input:         ��
* Output:        ��
* Return:        �ɹ�/ʧ��
* Others:        ��
*****************************************************************************/
STATIC HI_S32 TdeHalInitParaTable(HI_VOID)
{
    #include "tde_filterPara.h"
    #define OrgHfCoef Tde8x32Coef /* H2 / HD TDEˮƽ����ʹ�ø���ϵ���� */
    HI_U32 i = 0;
    HI_U32 j = 0;
    TDE_FILTER_PARA_U unPara;
    HI_U32 *pHfCoef = HI_NULL;
    HI_U32 *pVfCoef = HI_NULL;
    HI_U32 *pRgb2YuvCsc = HI_NULL;
    HI_U32 *pYuv2RgbCsc = HI_NULL;
    
    /* �㷨�ṩ�Ĳ����б� */
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
    /* �����㷨���ṩ�Ľṹ���������� */
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
* Description:   ����Դ2λͼ������Ϣ
* Input:         pHWNode: Ӳ������ڵ�ָ��
*                pDrvSurface: λͼ��Ϣ
*                bS2Size: �Ƿ�����Դ2�ߴ�
* Output:        ��
* Return:        ����ִ�е�ǰ�ڵ�������ַ
* Others:        ��
*****************************************************************************/
STATIC HI_VOID TdeHalNodeSetSrc2Base(TDE_HWNode_S* pHWNode, TDE_DRV_SURFACE_S* pDrvSurface, HI_BOOL bS2Size)
{
    TDE_SRC_TYPE_U unSrcType;
    TDE_SUR_XY_U unXy;
    
    TDE_ASSERT(HI_NULL != pHWNode);
    TDE_ASSERT(HI_NULL != pDrvSurface);

    /*����Դλͼ������Ϣ*/
    unSrcType.u32All = 0;
    unSrcType.stBits.u32Pitch = pDrvSurface->u32Pitch;
    unSrcType.stBits.u32SrcColorFmt = (HI_U32)pDrvSurface->enColorFmt;
    unSrcType.stBits.u32AlphaRange = (HI_U32)pDrvSurface->bAlphaMax255;
    unSrcType.stBits.u32HScanOrd = (HI_U32)pDrvSurface->enHScan;
    unSrcType.stBits.u32VScanOrd = (HI_U32)pDrvSurface->enVScan;
    unSrcType.stBits.u32RgbExp = 0; /*һֱʹ�õ�λ���Ϊ0,��λʹ�õ�λ����չ��ʽ*/

    unXy.u32All = pHWNode->u32TDE_S2_XY;
    unXy.stBits.u32X = pDrvSurface->u32Xpos;
    unXy.stBits.u32Y = pDrvSurface->u32Ypos;

    /*���û���ڵ�*/
    pHWNode->u32TDE_S2_ADDR = pDrvSurface->u32PhyAddr;
    pHWNode->u32TDE_S2_TYPE = unSrcType.u32All;
    pHWNode->u32TDE_S2_XY = unXy.u32All;

    /*HWNode.TDE_UPDATE�����������Ӧλ��1*/
    TDE_SET_UPDATE(u32TDE_S2_ADDR, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S2_TYPE, pHWNode->u64TDE_UPDATE);
    TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);
    
    if (bS2Size)
    {
        TDE_SUR_SIZE_U unSurSize;
        unSurSize.u32All = 0;
        /*����λͼ��С��Ϣ*/
        unSurSize.stBits.u32Width = (HI_U32)pDrvSurface->u32Width;
        unSurSize.stBits.u32Height = (HI_U32)pDrvSurface->u32Height;
        pHWNode->u32TDE_S2_SIZE = unSurSize.u32All;
        TDE_SET_UPDATE(u32TDE_S2_SIZE, pHWNode->u64TDE_UPDATE);
    }

    return;
}

/*****************************************************************************
* Function:      TdeHalGetbppByFmt
* Description:   ������������ɫ��ʽ�õ�Bpp
* Input:         enFmt: ��ɫ��ʽ
* Output:        ����λ��
* Return:        -1:�����ʽ
* Others:        ��
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
* Description:   ���ݲ����ҵ��������
* Input:         u32Step: ���벽��
* Output:        ��
* Return:        ����Ҫ������ű������ַ����
* Others:        ��
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
* Description:   ���ݲ����ҵ���ֱ���Ų����������
* Input:         u32Step: ���봹ֱ���Ų���
* Output:        ��
* Return:        ����Ҫ������ű������ַ����
* Others:        ��
*****************************************************************************/
STATIC  HI_U32 TdeHalGetResizeParaVTable(HI_U32 u32Step)
{
    HI_U32 u32Index;

    /* ���ݲ����ҵ�������� */
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
* Description:   pHWNode:   Ӳ���ڵ���Ϣ
*                pChildInfo: �ӽڵ���Ϣ
* Input:         ��
* Output:        ��
* Return:        ��
* Others:        ��
*****************************************************************************/
STATIC  HI_VOID TdeHalSetXyByAdjInfo(TDE_HWNode_S* pHWNode, TDE_CHILD_INFO* pChildInfo)
{
    TDE_SUR_XY_U unXy;
    
    switch (pChildInfo->stAdjInfo.enScaleMode)
    {
    case TDE_CHILD_SCALE_NORM:
    case TDE_CHILD_SCALE_MBC:
        {
            /* ֱ�Ӱ���S2�ֿ� */
            unXy.u32All = pHWNode->u32TDE_S2_XY;
            unXy.stBits.u32X = pChildInfo->u32Xi;
            unXy.stBits.u32Y = pChildInfo->u32Yi;
            pHWNode->u32TDE_S2_XY = unXy.u32All;
            TDE_SET_UPDATE(u32TDE_S2_XY, pHWNode->u64TDE_UPDATE);
            break;
        }
    case TDE_CHILD_SCALE_MBY:
        {
            /* ֱ�Ӱ���S1�ֿ� */
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
            /* ��������S1�ֿ�, ����ɫ��S2��ʼλ�� */
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
            /* ��������S1�ֿ�, ����ɫ��S2��ʼλ�� */
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
            /* ����ɫ��S2�ֿ�, ��������S1��ʼλ�� */
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

    /* ��Aq/Sq�����׵�ַ�Ĵ���д0 */
    TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_AQ_NADDR, 0);
   // TDE_WRITE_REG(s_pu32BaseVirAddr, TDE_SQ_NADDR, 0);

    unAqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_AQ_CTRL);
   // unSqCtrl.u32All = TDE_READ_REG(s_pu32BaseVirAddr, TDE_SQ_CTRL);
    
    /* ʹ��Aq/Sq���� */
    unAqCtrl.stBits.u32AqEn = 1;
#if 0
    unSqCtrl.stBits.u32SqEn = 0;    /* Ӳ����ʱ����*/

    /* ����SQ�Ĵ���������ͬ��ģʽ */
    unSqCtrl.stBits.u32TrigMode = 0;
    unSqCtrl.stBits.u32TrigCond = 0;

    /* ����Sq/Aq����ģʽ */
    unSqCtrl.stBits.u32SqOperMode = TDE_SQ_CTRL_COMP_LIST; /*Sq��ɺ�������һ����*/
#endif    
    unAqCtrl.stBits.u32AqOperMode = TDE_AQ_CTRL_COMP_LINE; /* ����� */

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

