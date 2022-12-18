
/**
 \file
 \brief Describes the header file of the bit block transfer (Bliter) module.CNcomment:bliterͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-5-23
 */

#ifndef __HI_GO_BLITER_H__
#define __HI_GO_BLITER_H__

#include "hi_go_comm.h"
#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/


/****************************** Error Number ********************************/


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_1 */
/** @{ */  /** <!-- ��bliter�� */

/** Pixel-level alpha blending operation*/
/**CNcomment: ���ؼ�alpha��ϲ������� */
typedef enum
{
    HIGO_COMPOPT_NONE = 0, /**<Porter/Duff None-blending operation*//**CNcomment:< Porter/Duff None��ϲ��� */
    HIGO_COMPOPT_SRCOVER = 3 , /**<Porter/Duff Srcover blending operation*//**CNcomment:< Porter/Duff Srcover��ϲ��� */ 

    HIGO_COMPOPT_BUTT
} HIGO_COMPOPT_E;

/** Operation mode corresponding to colorkey*//**CNcomment: Colorkey��Ӧ�Ĳ�����ʽ */
typedef enum
{
    HIGO_CKEY_NONE = 0, /**<Do not use the colorkey.*//**CNcomment:< ��ʹ��colorkey */
    HIGO_CKEY_SRC,      /**<Use the source colorkey.*//**CNcomment:< ʹ��Դcolorkey */
    HIGO_CKEY_DST,     /**<Use the destination colorkey.*//**CNcomment:< ʹ��Ŀ��colorkey */

    HIGO_CKEY_BUTT
} HIGO_CKEY_E;

/** Two raster of operations (ROPs)*//**CNcomment: 2ԪROP���� */
typedef enum
{
    HIGO_ROP_BLACK = 0, /**< Blackness */
    HIGO_ROP_PSDon,     /**< ~(PS+D) */
    HIGO_ROP_PSDna,     /**< ~PS & D */
    HIGO_ROP_PSn,       /**< ~PS */
    HIGO_ROP_DPSna,     /**< PS & ~D */
    HIGO_ROP_Dn,        /**< ~D */
    HIGO_ROP_PSDx,      /**< PS^D */
    HIGO_ROP_PSDan,     /**< ~(PS&D) */
    HIGO_ROP_PSDa,      /**< PS & D */
    HIGO_ROP_PSDxn,     /**< ~(PS^D) */
    HIGO_ROP_D,         /**< D */
    HIGO_ROP_PSDno,     /**< ~PS + D */
    HIGO_ROP_PS,        /**< PS */
    HIGO_ROP_DPSno,     /**< PS + ~D */
    HIGO_ROP_PSDo,      /**< PS+D */
    HIGO_ROP_WHITE,     /**< Whiteness */

    HIGO_ROP_BUTT
} HIGO_ROP_E;

typedef enum
{
    HIGO_ROTATE_NONE = 0,
    HIGO_ROTATE_90,     /**<Rotate 90�� clockwise*//**CNcomment:< ˳ʱ����ת90�� */
    HIGO_ROTATE_180,    /**<Rotate 180�� clockwise*//**CNcomment:< ˳ʱ����ת180�� */
    HIGO_ROTATE_270,    /**<Rotate 270�� clockwise*//**CNcomment:< ˳ʱ����ת270�� */

    HIGO_ROTATE_BUTT
} HIGO_ROTATE_E;

typedef enum
{
    HIGO_MIRROR_NONE = 0,

    HIGO_MIRROR_LR,     /**<Mirror the left and the right*//**CNcomment:< ���Ҿ��� */
    HIGO_MIRROR_TB,     /**<Mirror the top and the bottom*//**CNcomment:< ���¾��� */

    HIGO_MIRROR_BUTT
} HIGO_MIRROR_E;

typedef struct 
{
    HI_BOOL EnableGlobalAlpha;      /**<Global alpha enable flag*//**CNcomment:< ȫ��alphaʹ�ܱ�־ */
    HI_BOOL EnablePixelAlpha;       /**<Pixel alpha enable flag*//**CNcomment:< ����alphaʹ�ܱ�־ */
    HIGO_COMPOPT_E PixelAlphaComp;  /**<Pixel alpha operation*//**CNcomment:< ����alpha���� */
    HIGO_CKEY_E    ColorKeyFrom;    /**<Colorkey operation*//**CNcomment:< ColorKey���� */
    HI_BOOL        EnableRop;       /**<Enable the ROP2 operation*//**CNcomment:< ����ROP2���� */
    HIGO_ROP_E     Rop;              /**<ROP2 operation type*//**CNcomment:< ROP2�������� */
    HIGO_ROP_E     RopAlpha;         /**<Type of the ROP alpha operation*//**CNcomment:< ROP alpha��������*/
 }HIGO_BLTOPT2_S;

/**CNcomment: blit�������� */
typedef struct
{
    HI_BOOL EnableGlobalAlpha;      /**<Global alpha enable flag. If this flag is enabled, the PixelAlphaComp blending mode must be specified.*//**CNcomment:< ȫ��alphaʹ�ܱ�־,�򿪴˿���֮�⻹����ָ��PixelAlphaComp�Ļ�Ϸ�ʽ*/
    HI_BOOL EnablePixelAlpha;       /**<Pixel alpha enable flag*//**CNcomment:< ����alphaʹ�ܱ�־ */
    HIGO_COMPOPT_E PixelAlphaComp;  /**<Pixel alpha operation*//**CNcomment:< ����alpha���� */
    HIGO_CKEY_E    ColorKeyFrom;    /**<colorkey operation*//**CNcomment:< ColorKey���� */
    HI_BOOL        EnableRop;       /**<Enable the ROP2 operation*//**CNcomment:< ����ROP2���� */
    HIGO_ROP_E     Rop;             /**<ROP2 operation type*//**CNcomment:< ROP2�������� */
    HIGO_ROP_E     RopAlpha;        /**<Type of the ROP alpha operation*/    /**CNcomment:< ROP alpha��������*/    
    HI_BOOL        EnableScale;      /**<Enable the scaling function*//**CNcomment:< �������� */
    HIGO_ROTATE_E  RotateType;      /**<Rotation type*//**CNcomment:< ��ת��ʽ */
    HIGO_MIRROR_E  MirrorType;      /**<Mirror type*//**CNcomment:< ����ʽ */
} HIGO_BLTOPT_S;

typedef struct
{
    HI_BOOL EnableGlobalAlpha;      /**<Global alpha enable flag*//**CNcomment:< ȫ��alphaʹ�ܱ�־ */

    HIGO_COMPOPT_E PixelAlphaComp;  /**<Pixel alpha operation*//**CNcomment:< ����alpha���� */
    HI_BOOL        EnableRop;       /**<Enable the ROP2 operation*//**CNcomment:< ����ROP2���� */
    HIGO_ROP_E     RopColor;        /**<ROP2 operation type*//**CNcomment:< ROP2�������� */
	HIGO_ROP_E     RopAlpha;
		
} HIGO_MASKOPT_S;

/**Anti-flicker level*//**CNcomment: ����˸���� */
typedef enum
{
    HIGO_DEFLICKER_AUTO = 0, /*Anti-flicker level, ranging from low to high. The higher the level, the better the anti-flicker effect, but the more blurred the picture.*//**CNcomment:����˸����ֵΪLOW~HIGH,ֵԽ����˸Ч��Խ�ã���Խģ��*/
    HIGO_DEFLICKER_LOW,
    HIGO_DEFLICKER_MIDDLE,
    HIGO_DEFLICKER_HIGH,
    HIGO_DEFLICKER_BUTT
}HIGO_DEFLICKEROPT_E;

/**Anti-flicker level*//**CNcomment: ����˸���� */
typedef struct
{
    HIGO_DEFLICKEROPT_E DefLevel;
}HIGO_DEFLICKEROPT_S;
/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_1 */
/** @{ */  /** <!-- ��bliter�� */

/** 
\brief Initializes the Bliter module.CNcomment: ��ʼ��Bliterģ��
\attention \n
When ::HI_GO_Init is called, this application programming interface (API) is also called.CNcomment: ::HI_GO_Init���Ѱ����˶Ըýӿڵĵ���
\param  N/A.CNcomment: ��

\retval ::HI_SUCCESS  
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE

\see \n
::HI_GO_Init \n
::HI_GO_DeinitBliter
*/
HI_S32 HI_GO_InitBliter(HI_VOID);

/**CNcomment:  
\brief Deinitializes the Bliter module.CNcomment:ȥ��ʼ��Bliterģ��
\attention \n
When ::HI_GO_Deinit is called, this API is also called.CNcomment:::HI_GO_Deinit���Ѱ����˶Ըýӿڵĵ���
\param N/A. CNcomment:��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT

\see \n
::HI_GO_Deinit \n
::HI_GO_InitBliter
*/

HI_S32 HI_GO_DeinitBliter(HI_VOID);

/**  
\brief Fills in a rectangle.CNcomment:�������
\attention \n
N/A.CNcomment:��
\param[in] Surface Surface handle.CNcomment:Surface���
\param[in] pRect Size of the rectangle to be filled in. If the parameter is not set, it indicates that the entire 
surface is filled in.CNcomment: �����δ�С��Ϊ�ձ�ʾ�������surface
\param[in] Color Color Fill color. For the RGB format, 32-bit color is filled in; for the palette, the color index (0-255) 
is filled in.CNcomment:�����ɫ,ע�������RGB��ʽ��ͳһ���32λɫ�������ɫ�壬��ֱ�������ɫ����(0 ~ 255)��
\param[in] CompositeOpt Blending mode.CNcomment:��Ϸ�ʽ

\retval ::HI_SUCCESS 
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_OUTOFPAL
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\see \n
N/A. CNcomment:��
*/
#ifndef ADVCA_TYPE_NAGRA
HI_S32 HI_GO_FillRect(HI_HANDLE Surface, const HI_RECT* pRect, HI_COLOR Color, HIGO_COMPOPT_E CompositeOpt);

/**  
\brief Transfers bit blocks. During the transfer, color space conversion (CSC), scaling, and rotation are supported.CNcomment:λ����ƣ��ڰ��ƹ����У�����ʵ��ɫ�ʿռ�ת�������š���ת����
\attention \n
Only the YUV-to-RGB CSC is supported. \n
The operations of colorkey, alpha, ROP, and colorkey+ROP are supported.\
Scaling, rotation, and mirror cannot be combined. \n
For scaling, rotation, and mirror, the source and destination pixel formats must be the same, but the format cannot 
be YUV or CLUT.\n
CNcomment:ɫ�ʿռ�ת����֧��YUV��RGBת�� \n
����֧�ֲ�������colorkey��alpha��ROP��colorkey+ROP\
���š���ת���񲻿����ʹ�� \n
���š���ת����Ҫ��Դ��Ŀ�����ظ�ʽ��ȫ��ͬ����������YUV��ʽ��CLUT��ʽ \n

\param[in] SrcSurface Source surface handle.CNcomment:Դsurface���
\param[in] pSrcRect Source region for transfer. If the parameter is not set, it indicates the entire source surface.CNcomment:���Ƶ�Դ����Ϊ�ձ�ʾ����Դsurface����
\param[in] DstSurface Destination surface handle.CNcomment:Ŀ��surface���
\param[in] pDstRect Destination region for transfer. If the parameter is not set, it indicates the entire destination 
surface.CNcomment:���Ƶ�Ŀ������Ϊ�ձ�ʾ����Ŀ��surface����
\param[in] pBlitOpt Blending mode.CNcomment:��Ϸ�ʽ

\retval ::HI_SUCCESS 
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVMIRRORTYPE
\retval ::HIGO_ERR_INVROTATETYPE
\retval ::HIGO_ERR_INVCKEYTYPE
\retval ::HIGO_ERR_INVROPTYPE
\retval ::HIGO_ERR_NOCOLORKEY
\retval ::HIGO_ERR_INVPIXELFMT
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVCOMPTYPE
\retval ::HIGO_ERR_UNSUPPORTED
\retval ::HIGO_ERR_LOCKED
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_EMPTYRECT
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_INTERNAL

\see \n
N/A. CNcomment:��
*/
HI_S32 HI_GO_Blit (HI_HANDLE SrcSurface, const HI_RECT* pSrcRect,
                   HI_HANDLE DstSurface, const HI_RECT* pDstRect,
                   const HIGO_BLTOPT_S* pBlitOpt);


/** @} */  /*! <!-- API declaration end */
#endif

#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_BLITER_H__ */
