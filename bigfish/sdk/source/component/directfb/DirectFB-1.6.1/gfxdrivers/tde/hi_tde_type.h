/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
 File Name     : tde_type.h
Version       : Initial Draft
Author        : w54130
Created       : 2007/5/21
Last Modified :
Description   : TDE public type
Function List :
History       :
1.Date        : 2007/5/21
Author      : w54130
Modification: Created file

 ******************************************************************************/
#ifndef __TDE_TYPE_H__
#define __TDE_TYPE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_tde_errcode.h"

/****************************************************************************/
/*                             TDE2 types define                             */
/****************************************************************************/
/** TDE������� */
typedef HI_S32 TDE_HANDLE;

/** TDE�жϻص����� */
typedef HI_VOID (* TDE_FUNC_CB) (HI_VOID *pParaml, HI_VOID *pParamr);

typedef HI_VOID (* TDE_TRIG_SEL)(HI_U32);

/** RGB��Packet YUV ��ɫ��ʽ */
typedef enum hiTDE2_COLOR_FMT_E
{
    TDE2_COLOR_FMT_RGB444 = 0,          /**< RGB444��ʽ, Redռ4bits Greenռ4bits, Blueռ4bits,�����ʽ�������� */
    TDE2_COLOR_FMT_BGR444,              /**< BGR444��ʽ */    
    TDE2_COLOR_FMT_RGB555,              /**< RGB555��ʽ */
    TDE2_COLOR_FMT_BGR555,              /**< BGR555��ʽ */
    TDE2_COLOR_FMT_RGB565,              /**< RGB565��ʽ */
    TDE2_COLOR_FMT_BGR565,              /**< BGR565��ʽ */
    TDE2_COLOR_FMT_RGB888,              /**< RGB888��ʽ */
    TDE2_COLOR_FMT_BGR888,              /**< BGR888��ʽ */
    TDE2_COLOR_FMT_ARGB4444,            /**< ARGB4444��ʽ */
    TDE2_COLOR_FMT_ABGR4444,            /**< ABGR4444��ʽ */
    TDE2_COLOR_FMT_RGBA4444,            /**< RGBA4444��ʽ */
    TDE2_COLOR_FMT_BGRA4444,            /**< BGRA4444��ʽ */
    TDE2_COLOR_FMT_ARGB1555,            /**< ARGB1555��ʽ */
    TDE2_COLOR_FMT_ABGR1555,            /**< ABGR1555��ʽ */
    TDE2_COLOR_FMT_RGBA1555,            /**< RGBA1555��ʽ */
    TDE2_COLOR_FMT_BGRA1555,            /**< BGRA1555��ʽ */
    TDE2_COLOR_FMT_ARGB8565,            /**< ARGB8565��ʽ */
    TDE2_COLOR_FMT_ABGR8565,            /**< ABGR8565��ʽ */
    TDE2_COLOR_FMT_RGBA8565,            /**< RGBA8565��ʽ */
    TDE2_COLOR_FMT_BGRA8565,            /**< BGRA8565��ʽ */
    TDE2_COLOR_FMT_ARGB8888,            /**< ARGB8888��ʽ */
    TDE2_COLOR_FMT_ABGR8888,            /**< ABGR8888��ʽ */
    TDE2_COLOR_FMT_RGBA8888,            /**< RGBA8888��ʽ */
    TDE2_COLOR_FMT_BGRA8888,            /**< BGRA8888��ʽ */
    TDE2_COLOR_FMT_CLUT1,               /**<��Alpha����,��ɫ��1bit��ʽ,ÿ������1��bit��ʾ */
    TDE2_COLOR_FMT_CLUT2,               /**<��Alpha����,��ɫ��2bit��ʽ,ÿ������2��bit��ʾ */
    TDE2_COLOR_FMT_CLUT4,               /**<��Alpha����,��ɫ��4bit��ʽ,ÿ������4��bit��ʾ */
    TDE2_COLOR_FMT_CLUT8,               /**<��Alpha����,��ɫ��8bit��ʽ,ÿ������8��bit��ʾ */
    TDE2_COLOR_FMT_ACLUT44,             /**<��Alpha����,��ɫ��1bit��ʽ,ÿ������1��bit��ʾ */
    TDE2_COLOR_FMT_ACLUT88,             /**<��Alpha����,��ɫ��1bit��ʽ,ÿ������1��bit��ʾ */
    TDE2_COLOR_FMT_A1,                  /**<alpha��ʽ��ÿ������1bit */
    TDE2_COLOR_FMT_A8,                  /**<alpha��ʽ��ÿ������8bit */
    TDE2_COLOR_FMT_YCbCr888,            /**<YUV packet��ʽ����alpha����*/
    TDE2_COLOR_FMT_AYCbCr8888,          /**<YUV packet��ʽ����alpha����*/
    TDE2_COLOR_FMT_YCbCr422,            /**<YUV packet422��ʽ */
    TDE2_COLOR_FMT_byte,                /**<���������ݿ���copy*/
    TDE2_COLOR_FMT_halfword,            /**<���������ݿ���copy*/
    TDE2_COLOR_FMT_JPG_YCbCr400MBP,     /**<Semi-planar YUV400��ʽ ,��Ӧ��JPG����*/
    TDE2_COLOR_FMT_JPG_YCbCr422MBHP,    /**<Semi-planar YUV422��ʽ,ˮƽ�����������Ӧ��JPG���� */
    TDE2_COLOR_FMT_JPG_YCbCr422MBVP,    /**<Semi-planar YUV422��ʽ,��ֱ�����������Ӧ��JPG���� */
    TDE2_COLOR_FMT_MP1_YCbCr420MBP,     /**<Semi-planar YUV420��ʽ */
    TDE2_COLOR_FMT_MP2_YCbCr420MBP,     /**<Semi-planar YUV420��ʽ */
    TDE2_COLOR_FMT_MP2_YCbCr420MBI,     /**<Semi-planar YUV400��ʽ */
    TDE2_COLOR_FMT_JPG_YCbCr420MBP,     /**<Semi-planar YUV400��ʽ,����Ӧ��JPG */
    TDE2_COLOR_FMT_JPG_YCbCr444MBP,     /**<Semi-planar YUV444��ʽ */
    TDE2_COLOR_FMT_BUTT                 /**< ö��������*/
} TDE2_COLOR_FMT_E;

/** Semi-planar YUV ��ʽ���� */
typedef enum hiTDE2_MB_COLORFMT_E
{
    TDE2_MB_COLOR_FMT_JPG_YCbCr400MBP = 0,/**<Semi-planar YUV400��ʽ ,��Ӧ��JPG����*/
    TDE2_MB_COLOR_FMT_JPG_YCbCr422MBHP,   /**<Semi-planar YUV422��ʽ,ˮƽ�����������Ӧ��JPG���� */
    TDE2_MB_COLOR_FMT_JPG_YCbCr422MBVP,   /**<Semi-planar YUV422��ʽ,��ֱ�����������Ӧ��JPG���� */
    TDE2_MB_COLOR_FMT_MP1_YCbCr420MBP,    /**<Semi-planar YUV420��ʽ */
    TDE2_MB_COLOR_FMT_MP2_YCbCr420MBP,    /**<Semi-planar YUV420��ʽ */
    TDE2_MB_COLOR_FMT_MP2_YCbCr420MBI,    /**<Semi-planar YUV400��ʽ */
    TDE2_MB_COLOR_FMT_JPG_YCbCr420MBP,    /**<Semi-planar YUV400��ʽ,����Ӧ��JPG */
    TDE2_MB_COLOR_FMT_JPG_YCbCr444MBP,    /**<Semi-planar YUV444��ʽ,����Ӧ��JPG */
    TDE2_MB_COLOR_FMT_BUTT
} TDE2_MB_COLOR_FMT_E;

/** �û����õ�λͼ��Ϣ�ṹ */
typedef struct hiTDE2_SURFACE_S
{
    HI_U32 u32PhyAddr;              /**< λͼ�׵�ַ��Y������ַ */

    TDE2_COLOR_FMT_E enColorFmt;    /**< ��ɫ��ʽ */

    HI_U32 u32Height;               /**< λͼ�߶� */

    HI_U32 u32Width;                /**< λͼ��� */

    HI_U32 u32Stride;               /**< λͼ��Ȼ�Y������� */
    HI_U8* pu8ClutPhyAddr;          /**< Clut���ַ,������ɫ��չ����ɫУ��*/

    HI_BOOL bYCbCrClut;             /**< Clut���Ƿ�λ��YCbCr�ռ� */

    HI_BOOL bAlphaMax255;           /**< λͼalpha���ֵΪ255����128 */

    HI_BOOL bAlphaExt1555;          /**< �Ƿ�ʹ��1555��Alpha��չ */
    HI_U8 u8Alpha0;                 /**< Alpha0��Alpha1ֵ������ARGB1555��ʽ */
    HI_U8 u8Alpha1;                 /**< Alpha0��Alpha1ֵ������ARGB1555��ʽ */
    HI_U32 u32CbCrPhyAddr;          /**< CbCr������ַ,pilot */        
    HI_U32 u32CbCrStride;           /**< CbCr�������,pilot */
} TDE2_SURFACE_S;

/** Semi-planar YUV��ʽ���ݶ��� */
typedef struct hiTDE2_MB_S
{
    TDE2_MB_COLOR_FMT_E enMbFmt;        /**< YUV��ʽ */
    HI_U32              u32YPhyAddr;    /**< Y���������ַ */
    HI_U32              u32YWidth;      /**< Y������� */
    HI_U32              u32YHeight;     /**< Y�����߶� */
    HI_U32              u32YStride;     /**< Y������ȣ�ÿ���ֽ��� */
    HI_U32              u32CbCrPhyAddr; /**< UV������� */
    HI_U32              u32CbCrStride;  /**< UV�������,ÿ���ֽ��� */
} TDE2_MB_S;

/** TDE���ζ���*/
typedef struct hiTDE2_RECT_S
{
    HI_S32 s32Xpos;     /**< x���� */
    HI_S32 s32Ypos;     /**< y���� */
    HI_U32 u32Width;    /**< ��� */
    HI_U32 u32Height;   /**< �߶� */
} TDE2_RECT_S;

/** �߼����㷽ʽ */
typedef enum hiTDE2_ALUCMD_E
{
    TDE2_ALUCMD_NONE = 0x0,         /**< ������alpha��rop���� */    
    TDE2_ALUCMD_BLEND = 0x1,        /**< Alpha���*/
    TDE2_ALUCMD_ROP = 0x2,          /**< ����rop���� */
    TDE2_ALUCMD_COLORIZE = 0x4,     /**< ����Colorize���� */
    TDE2_ALUCMD_BUTT = 0x8          /**< ö�ٽ��� */
} TDE2_ALUCMD_E;

/** ROP�����붨�� */
typedef enum hiTDE2_ROP_CODE_E
{
    TDE2_ROP_BLACK = 0,     /**<Blackness*/
    TDE2_ROP_NOTMERGEPEN,   /**<~(S2 | S1)*/
    TDE2_ROP_MASKNOTPEN,    /**<~S2&S1*/
    TDE2_ROP_NOTCOPYPEN,    /**< ~S2*/
    TDE2_ROP_MASKPENNOT,    /**< S2&~S1 */
    TDE2_ROP_NOT,           /**< ~S1 */
    TDE2_ROP_XORPEN,        /**< S2^S1 */
    TDE2_ROP_NOTMASKPEN,    /**< ~(S2 & S1) */
    TDE2_ROP_MASKPEN,       /**< S2&S1 */
    TDE2_ROP_NOTXORPEN,     /**< ~(S2^S1) */
    TDE2_ROP_NOP,           /**< S1 */
    TDE2_ROP_MERGENOTPEN,   /**< ~S2|S1 */
    TDE2_ROP_COPYPEN,       /**< S2 */
    TDE2_ROP_MERGEPENNOT,   /**< S2|~S1 */
    TDE2_ROP_MERGEPEN,      /**< S2|S1 */
    TDE2_ROP_WHITE,         /**< Whiteness */
    TDE2_ROP_BUTT
} TDE2_ROP_CODE_E;

/** blit������ */
typedef enum hiTDE2_MIRROR_E
{
    TDE2_MIRROR_NONE = 0,       /**< �����о��� */
    TDE2_MIRROR_HORIZONTAL,     /**< ˮƽ���� */
    TDE2_MIRROR_VERTICAL,       /**< ��ֱ���� */
    TDE2_MIRROR_BOTH,           /**< ��ֱ��ˮƽ���� */
    TDE2_MIRROR_BUTT
} TDE2_MIRROR_E;

/**Clip��������*/
typedef enum hiTDE2_CLIPMODE_E
{
    TDE2_CLIPMODE_NONE = 0, /**< ��clip���� */
    TDE2_CLIPMODE_INSIDE,   /**<  ���о��η�Χ�ڵ��������,�����ӵ�*/
    TDE2_CLIPMODE_OUTSIDE,  /**< ���о��η�Χ�����������������ӵ�*/
    TDE2_CLIPMODE_BUTT
} TDE2_CLIPMODE_E;

/**����ʽ��������*/
typedef enum hiTDE2_MBRESIZE_E
{
    TDE2_MBRESIZE_NONE = 0,         /**< �������� */
    TDE2_MBRESIZE_QUALITY_LOW,      /**< ���������� */
    TDE2_MBRESIZE_QUALITY_MIDDLE,   /**< ���������� */
    TDE2_MBRESIZE_QUALITY_HIGH,     /**< ���������� */
    TDE2_MBRESIZE_BUTT
} TDE2_MBRESIZE_E;

/** ���ɫ���� */
typedef struct hiTDE2_FILLCOLOR_S
{
    TDE2_COLOR_FMT_E enColorFmt;    /**< TDE���ظ�ʽ */
    HI_U32           u32FillColor;  /**< �����ɫ���������ظ�ʽ����ͬ */
} TDE2_FILLCOLOR_S;

/** colorkeyѡ������ */
typedef enum hiTDE2_COLORKEY_MODE_E
{
    TDE2_COLORKEY_MODE_NONE = 0,     /**< ����color key */
    TDE2_COLORKEY_MODE_FOREGROUND,   /**< ��ǰ��λͼ����color key��˵��:������ɫ��չ����CLUTǰ��color key��������ɫУ��:��CLUT����color key */
    TDE2_COLORKEY_MODE_BACKGROUND,   /**< �Ա���λͼ����color key*/
    TDE2_COLORKEY_MODE_BUTT
} TDE2_COLORKEY_MODE_E;

/** colorkey��Χ���� */
typedef struct hiTDE2_COLORKEY_COMP_S
{
    HI_U8 u8CompMin;           /**< ������Сֵ*/
    HI_U8 u8CompMax;           /**< �������ֵ*/
    HI_U8 bCompOut;            /**< �����ؼ�ɫ�ڷ�Χ��/��Χ��*/
    HI_U8 bCompIgnore;         /**< �����Ƿ����*/
    HI_U8 u8CompMask;          /**< ��������*/
    HI_U8 u8Reserved;
    HI_U8 u8Reserved1;
    HI_U8 u8Reserved2;
} TDE2_COLORKEY_COMP_S;

/** colorkeyֵ���� */
typedef union hiTDE2_COLORKEY_U
{
    struct
    {
        TDE2_COLORKEY_COMP_S stAlpha;   /**< alpha ������Ϣ */
        TDE2_COLORKEY_COMP_S stRed;     /**< ��ɫ������Ϣ */
        TDE2_COLORKEY_COMP_S stGreen;   /**< ��ɫ������Ϣ */
        TDE2_COLORKEY_COMP_S stBlue;    /**< ��ɫ������Ϣ */
    } struCkARGB;
    struct
    {
        TDE2_COLORKEY_COMP_S stAlpha;   /**< alpha ������Ϣ */
        TDE2_COLORKEY_COMP_S stY;       /**< Y������Ϣ */
        TDE2_COLORKEY_COMP_S stCb;      /**< Cb������Ϣ */
        TDE2_COLORKEY_COMP_S stCr;      /**< Cr������Ϣ */
    } struCkYCbCr;
    struct
    {
        TDE2_COLORKEY_COMP_S stAlpha;   /**< alpha ������Ϣ */
        TDE2_COLORKEY_COMP_S stClut;    /**< ��ɫ�������Ϣ */
    } struCkClut;
} TDE2_COLORKEY_U;

/** ���alpha���� */
typedef enum hiTDE2_OUTALPHA_FROM_E
{
    TDE2_OUTALPHA_FROM_NORM = 0,    /**< ��Դ��alpha blending�Ľ�����߿���˸�Ľ�� */
    TDE2_OUTALPHA_FROM_BACKGROUND,  /**< ��Դ�ڱ���λͼ */
    TDE2_OUTALPHA_FROM_FOREGROUND,  /**< ��Դ��ǰ��λͼ */
    TDE2_OUTALPHA_FROM_GLOBALALPHA, /**< ��Դ��ȫ��alpha */
    TDE2_OUTALPHA_FROM_BUTT
} TDE2_OUTALPHA_FROM_E;

/** �����˲����� */
typedef enum hiTDE2_FILTER_MODE_E
{
    TDE2_FILTER_MODE_COLOR = 0, /**< ����ɫ�����˲� */
    TDE2_FILTER_MODE_ALPHA,     /**< ��alphaͨ���˲� */
    TDE2_FILTER_MODE_BOTH,      /**< ����ɫ��alphaͨ��ͬʱ�˲� */
    TDE2_FILTER_MODE_BUTT
} TDE2_FILTER_MODE_E;

/**������˸����ͨ������ */
typedef enum hiTDE2_DEFLICKER_MODE_E
{
    TDE2_DEFLICKER_MODE_NONE = 0,   /**< �������� */
    TDE2_DEFLICKER_MODE_RGB,        /**< RGB�������� */
    TDE2_DEFLICKER_MODE_BOTH,       /**< alpha�������� */
    TDE2_DEFLICKER_MODE_BUTT
}TDE2_DEFLICKER_MODE_E;

/* blend mode */
typedef enum hiTDE2_BLEND_MODE_E
{
    TDE2_BLEND_ZERO = 0x0,
    TDE2_BLEND_ONE,
    TDE2_BLEND_SRC2COLOR,
    TDE2_BLEND_INVSRC2COLOR,
    TDE2_BLEND_SRC2ALPHA,
    TDE2_BLEND_INVSRC2ALPHA,
    TDE2_BLEND_SRC1COLOR,
    TDE2_BLEND_INVSRC1COLOR,
    TDE2_BLEND_SRC1ALPHA,
    TDE2_BLEND_INVSRC1ALPHA,
    TDE2_BLEND_SRC2ALPHASAT,
    TDE2_BLEND_BUTT
}TDE2_BLEND_MODE_E;

/** alpha�������,����ѡ���Լ����ò�����Ҳ����ѡ��Porter/Duff�е�һ�� */
/* pixel = (source * fs + destination * fd),
   sa = source alpha,
   da = destination alpha */
typedef enum hiTDE2_BLENDCMD_E
{
    TDE2_BLENDCMD_NONE = 0x0,     /**< fs: sa      fd: 1.0-sa */
    TDE2_BLENDCMD_CLEAR,    /**< fs: 0.0     fd: 0.0 */
    TDE2_BLENDCMD_SRC,      /**< fs: 1.0     fd: 0.0 */
    TDE2_BLENDCMD_SRCOVER,  /**< fs: 1.0     fd: 1.0-sa */
    TDE2_BLENDCMD_DSTOVER,  /**< fs: 1.0-da  fd: 1.0 */
    TDE2_BLENDCMD_SRCIN,    /**< fs: da      fd: 0.0 */
    TDE2_BLENDCMD_DSTIN,    /**< fs: 0.0     fd: sa */
    TDE2_BLENDCMD_SRCOUT,   /**< fs: 1.0-da  fd: 0.0 */
    TDE2_BLENDCMD_DSTOUT,   /**< fs: 0.0     fd: 1.0-sa */
    TDE2_BLENDCMD_SRCATOP,  /**< fs: da      fd: 1.0-sa */
    TDE2_BLENDCMD_DSTATOP,  /**< fs: 1.0-da  fd: sa */
    TDE2_BLENDCMD_ADD,      /**< fs: 1.0     fd: 1.0 */
    TDE2_BLENDCMD_XOR,      /**< fs: 1.0-da  fd: 1.0-sa */
    TDE2_BLENDCMD_DST,      /**< fs: 0.0     fd: 1.0 */
    TDE2_BLENDCMD_CONFIG,   /**< �û��Լ����ò���*/
    TDE2_BLENDCMD_BUTT
}TDE2_BLENDCMD_E;
/* alpha��ϲ���ѡ�� */
typedef struct hiTDE2_BLEND_OPT_S
{
    HI_BOOL  bGlobalAlphaEnable;        /**< �Ƿ�ʹ��ȫ��alpha */
    HI_BOOL  bPixelAlphaEnable;         /**< �Ƿ�ʹ������alpha */
    HI_BOOL bSrc1AlphaPremulti;         /**< �Ƿ�ʹ��Src1 alphaԤ�� */
    HI_BOOL bSrc2AlphaPremulti;         /**< �Ƿ�ʹ��Src2 alphaԤ�� */
    TDE2_BLENDCMD_E eBlendCmd;          /**< alpha�������*/    
    TDE2_BLEND_MODE_E eSrc1BlendMode;   /**< Src1 blendģʽѡ��,��eBlendCmd = TDE2_BLENDCMD_CONFIGʱ��Ч */
    TDE2_BLEND_MODE_E eSrc2BlendMode;   /**< Src2 blendģʽѡ��,��eBlendCmd = TDE2_BLENDCMD_CONFIGʱ��Ч */
}TDE2_BLEND_OPT_S;

/* CSC����ѡ��*/
typedef struct hiTDE2_CSC_OPT_S
{
    HI_BOOL bICSCUserEnable;		/** �û��Զ���ICSC����ʹ��*/
    HI_BOOL bICSCParamReload;	/** ���¼����û��Զ���ICSC����ʹ��*/
    HI_BOOL bOCSCUserEnable;		/** �û��Զ���OCSC����ʹ��*/
    HI_BOOL bOCSCParamReload;	/** ���¼����û��Զ���OCSC����ʹ��*/
    HI_U32 u32ICSCParamAddr;		/** ICSC������ַ��Ҫ��128bit����*/
    HI_U32 u32OCSCParamAddr;	/** OCSC������ַ��Ҫ��128bit����*/
}TDE2_CSC_OPT_S;

/** blit����ѡ��� */
typedef struct hiTDE2_OPT_S
{
    TDE2_ALUCMD_E enAluCmd;                 /**<�߼���������*/

    TDE2_ROP_CODE_E enRopCode_Color;        /**<��ɫ�ռ�ROP����*/

    TDE2_ROP_CODE_E enRopCode_Alpha;        /**<Alpha��ROP����*/

    TDE2_COLORKEY_MODE_E enColorKeyMode;    /**<color key��ʽ*/

    TDE2_COLORKEY_U unColorKeyValue;        /**<color key����ֵ*/

    TDE2_CLIPMODE_E enClipMode;             /**<��������clip������������clip*/

    TDE2_RECT_S stClipRect;                 /**<clip������*/

    TDE2_DEFLICKER_MODE_E enDeflickerMode;  /**<����˸ģʽ*/

    HI_BOOL bResize;                        /**<�Ƿ�����*/

    TDE2_FILTER_MODE_E enFilterMode;        /**< ����ʱʹ�õ��˲�ģʽ */

    TDE2_MIRROR_E enMirror;                 /**<��������*/

    HI_BOOL bClutReload;                    /**<�Ƿ����¼���Clut��*/

    HI_U8   u8GlobalAlpha;                  /**<ȫ��Alphaֵ*/

    TDE2_OUTALPHA_FROM_E enOutAlphaFrom;    /**<���alpha��Դ*/
    
    HI_U32 u32Colorize;                     /**< Colorizeֵ */

    TDE2_BLEND_OPT_S stBlendOpt;

    TDE2_CSC_OPT_S stCscOpt;	
} TDE2_OPT_S;


/** ������ѡ��� */
typedef struct hiTDE2_MBOPT_S
{
    TDE2_CLIPMODE_E enClipMode;     /**< Clipģʽѡ��*/

    TDE2_RECT_S stClipRect;         /**< clip������*/

    HI_BOOL bDeflicker;             /**< �Ƿ���˸*/

    TDE2_MBRESIZE_E enResize;       /**< ������Ϣ*/

    HI_BOOL bSetOutAlpha;           /**< ���������Alpha,��Ĭ��������Alphaֵ*/
    
    HI_U8   u8OutAlpha;             /**< �μ������ȫ��alpha */
} TDE2_MBOPT_S;

/** ģʽ��������Ϣ���� */
typedef struct hiTDE2_PATTERN_FILL_OPT_S
{
    TDE2_ALUCMD_E enAluCmd;                 /**< �߼���������*/

    TDE2_ROP_CODE_E enRopCode_Color;        /**< ��ɫ�ռ�ROP����*/

    TDE2_ROP_CODE_E enRopCode_Alpha;        /**< alpha��ROP����*/

    TDE2_COLORKEY_MODE_E enColorKeyMode;    /**< color key��ʽ*/

    TDE2_COLORKEY_U unColorKeyValue;        /**< color keyֵ*/

    TDE2_CLIPMODE_E enClipMode;             /**< clipģʽ*/

    TDE2_RECT_S stClipRect;                 /**< clip����*/

    HI_BOOL bClutReload;                    /**< �Ƿ�����clut��*/

    HI_U8 u8GlobalAlpha;                    /**< ȫ��alpha*/

    TDE2_OUTALPHA_FROM_E enOutAlphaFrom;    /**< ���alpha��Դ*/

    HI_U32 u32Colorize;                     /* Colorizeֵ*/

    TDE2_BLEND_OPT_S stBlendOpt;            /* Blend����ѡ�� */

    TDE2_CSC_OPT_S stCscOpt;		/* Csc����ѡ��*/
    
}TDE2_PATTERN_FILL_OPT_S;

/** ��ת������ */
typedef enum hiTDE_ROTATE_ANGLE_E
{
    TDE_ROTATE_CLOCKWISE_90 = 0,    /**<  ˳ʱ����ת90�� */
    TDE_ROTATE_CLOCKWISE_180,       /**<  ˳ʱ����ת180�� */
    TDE_ROTATE_CLOCKWISE_270,       /**<  ˳ʱ����ת270�� */
    TDE_ROTATE_BUTT
} TDE_ROTATE_ANGLE_E;


/** ����˸������ */
typedef enum hiTDE_DEFLICKER_LEVEL_E
{
    TDE_DEFLICKER_AUTO = 0, /**< *<����Ӧ����TDEѡ����˸ϵ��*/
    TDE_DEFLICKER_LOW,      /**< *�ͼ�����˸*/
    TDE_DEFLICKER_MIDDLE,   /**< *�м�����˸*/
    TDE_DEFLICKER_HIGH,     /**< *�߼�����˸*/
    TDE_DEFLICKER_BUTT
}TDE_DEFLICKER_LEVEL_E;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __TDE_TYPE_H__ */


