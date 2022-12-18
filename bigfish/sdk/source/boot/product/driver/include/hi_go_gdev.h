/**
 \file
 \brief Describes the header file of the graphic device (Gdev) module. CNcomment:Gdevģ��ͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author w66592
 \date 2008-5-16
 */

#ifndef __HI_GO_GDEV_H__
#define __HI_GO_GDEV_H__

#include "hi_go_comm.h"
#include "hi_go_surface.h"
#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_6 */
/** @{ */  /** <!-- [Gdev module] */

/*Definition of the graphics layer ID*/
/*CNcomment:ͼ��ID����*/
typedef enum
{
    HIGO_LAYER_HD_0 = 0x0,
    HIGO_LAYER_HD_1,
    HIGO_LAYER_HD_2,
    HIGO_LAYER_HD_3,
    HIGO_LAYER_SD_0,    
    HIGO_LAYER_SD_1,    
    HIGO_LAYER_SD_2,     
    HIGO_LAYER_SD_3, 
    HIGO_LAYER_AD_0,  
    HIGO_LAYER_AD_1,
    HIGO_LAYER_AD_2,
    HIGO_LAYER_AD_3,
    HIGO_LAYER_CURSOR,
    HIGO_LAYER_ID_BUTT
}HIGO_LAYER_E;

/**Standard-definition (SD) graphics layer 0*/
/**CNcomment:����ͼ�ε��Ӳ�0 */
//#define HIGO_LAYER_RGB0 HIGO_LAYER_SD_0

/**SD graphics layer 1*/
/**CNcomment:����ͼ�ε��Ӳ�1 */
//#define HIGO_LAYER_RGB1 HIGO_LAYER_SD_1

/** The following macro defines the buffer mode of each graphics layer of the HiGo. The canvas buffer is used for drawing,
and the display buffer is used for display output.*/
/** CNcomment:����궨����higo��ÿ��ͼ���bufferģʽ������canvas buffer�ǹ��û����Ƶ�buffer, display buffer��������ʾ�����buffer.*/
#define HIGO_LAYER_BUFFER_SINGLE      0x02 /**<One canvas buffer, and no display buffer*//**<CNcomment:1��canvas buffer, ��display buffer */    
#define HIGO_LAYER_BUFFER_DOUBLE      0x04 /**<One canvas buffer, and one display buffer. Dual buffers are supported.*//**<CNcomment:1��canvas buffer, 1��display buffer ֧��˫���� */ 
#define HIGO_LAYER_BUFFER_TRIPLE      0x08 /**<One canvas buffer, and two display buffers. The flip function is supported.*//**<CNcomment:1��canvas buffer, 2��display buffer ֧��flip,ˢ�µ�ʱ��ȴ�������� */
#define HIGO_LAYER_BUFFER_OVER        0x10 /**<One canvas buffer, and two display buffers. The flip function is supported. If tasks are being performed during refresh, the current frame is discarded.*//**<CNcomment:1��canvas buffer, 2��display buffer ֧��flip,���ˢ�µ�ʱ���������æ��������ǰ֡ */

/**Refresh mode of graphics layers for complying with old definitions. The mode is not recommended.*/
/** CNcomment:Ϊ�����϶��壬ͼ���ˢ�·�ʽ��������ʹ��*/
typedef enum 
{
   // HIGO_LAYER_FLUSH_FLIP        = HIGO_LAYER_BUFFER_TRIPLE, 
    HIGO_LAYER_FLUSH_DOUBBUFER   = HIGO_LAYER_BUFFER_DOUBLE, 
   // HIGO_LAYER_FLUSH_NORMAL      = HIGO_LAYER_BUFFER_SINGLE, 
   // HIGO_LAYER_FLUSH_OVER        = HIGO_LAYER_BUFFER_OVER,
    HIGO_LAYER_FLUSH_BUTT
} HIGO_LAYER_FLUSHTYPE_E;

/*Anti-flicker level, ranging from low to high. The higher the level, the better the anti-flicker effect, but the more blurred the picture.*/
/*CNcomment:����˸����ֵΪLOW~HIGH,ֵԽ����˸Ч��Խ�ã���Խģ��*/
typedef enum
{
    HIGO_LAYER_DEFLICKER_NONE = 0, 
    HIGO_LAYER_DEFLICKER_LOW,
    HIGO_LAYER_DEFLICKER_MIDDLE,
    HIGO_LAYER_DEFLICKER_HIGH,
    HIGO_LAYER_DEFLICKER_AUTO,    
    HIGO_LAYER_DEFLICKER_BUTT
}HIGO_LAYER_DEFLICKER_E;

/**Layer attribute parameters*/
/**CNcomment:ͼ�����Բ���*/
typedef struct 
{
    HI_S32                 ScreenWidth;    /**<Height of a graphics layer on the screen. The value must be greater than 0.*//**<CNcomment:ͼ������Ļ����ʾ��ȣ��������0 */
    HI_S32                 ScreenHeight;   /**<Width of a graphics layer on the screen. The value must be greater than 0.*//**<CNcomment:ͼ������Ļ����ʾ�߶ȣ��������0 */
    HI_S32                 CanvasWidth;    /**<Width of the canvas buffer of a graphics layer. If the value is 0, no canvas buffer is created.*//**<CNcomment:ͼ��Ļ���buffer��ȣ�Ϊ0ʱ������������buffer */
    HI_S32                 CanvasHeight;   /**<Height of the canvas buffer of a graphics layer. If the value is 0, no canvas buffer is created.*//**<CNcomment:ͼ��Ļ���buffer�߶ȣ�Ϊ0ʱ������������buffer */
    HI_S32                 DisplayWidth;   /**<Width of the display buffer of a graphics layer. If the value is 0, the value of ScreenWidth is used.*//**<CNcomment:ͼ�����ʾbuffer��ȣ�Ϊ0ʱ����ScreenWidth��ͬ*/
    HI_S32                 DisplayHeight;  /**<Height of the display buffer of a graphics layer. If the value is 0, the value of ScreenHeight is used.*//**<CNcomment:ͼ�����ʾbuffer�߶ȣ�Ϊ0ʱ����ScreenHeight��ͬ*/
    HIGO_LAYER_FLUSHTYPE_E LayerFlushType; /**< Refresh mode of the layer. You can choose the refresh mode based on the actual scenario to improve the refresh efficiency. If the value is 0, the dual-buffer+flip refresh mode is used by default. *//**<CNcomment:ͼ���ˢ�·�ʽ���û��ɸ���ʹ�ó���ѡ��ͬ��ˢ��ģʽ�����ˢ��Ч��,����0ʱĬ��ʹ��˫����+Flipˢ��ģʽ */
    HIGO_LAYER_DEFLICKER_E AntiLevel;      /**<Anti-flicker level of a graphics layer*//**<CNcomment:ͼ�㿹��˸���� */
    HIGO_PF_E              PixelFormat;    /**<Pixel format of a graphics layer. The format must be supported by the hardware layer. You need to choose the pixel format parameters of the layer based on hardware devices.*//**<CNcomment:ͼ������ظ�ʽ���˸�ʽ����ΪӲ��ͼ����֧�ֵĸ�ʽ������ݲ�ͬӲ���豸��ѡ��ͼ������ظ�ʽ���� */
    HIGO_LAYER_E           LayerID;        /**<Hardware ID of a graphics layer. The supported graphics layer depends on the chip platform. For example, the Hi3720 supports an HD graphics layer and an SD graphics layer.*//**<CNcomment:ͼ��Ӳ��ID����֧��ͼ��ȡ����оƬƽ̨��hi3720����֧��һ�������һ������ */
} HIGO_LAYER_INFO_S;

/**Status of a graphics layer*/
/**CNcomment:ͼ��״̬�ṹ */
typedef struct 
{
    HI_BOOL bShow;             /**<Whether to display a graphics layer.*//**<CNcomment:ͼ���Ƿ���ʾ */
} HIGO_LAYER_STATUS_S;

typedef struct
{
    HI_COLOR ColorKey;         /**<Transparency of a graphics layer*//**<CNcomment:ͼ���͸��ɫ*/
    HI_BOOL bEnableCK;         /**<Whether the colorkey of a graphics layer is enabled.*//**<CNcomment:ͼ���Ƿ�ʹ��colorkey */
}HIGO_LAYER_KEY_S;

typedef struct
{
    HI_BOOL bAlphaEnable;   /**<Alpha pixel enable flag*//**<CNcomment:alpha����ʹ�ܱ�־ */
    HI_BOOL bAlphaChannel;  /**<Alpha channel enable flag*//**<CNcomment:alphaͨ��ʹ�ܱ�־  */
    HI_U8   Alpha0;         /**<Alpha0 value. It is valid in ARGB1555 format.*//**<CNcomment:alpha0ֵ,��ARGB1555��ʽ����Ч */
    HI_U8   Alpha1;         /**<Alpha1 value. It is valid in ARGB1555 format.*//**<CNcomment:alpha1ֵ,��ARGB1555��ʽ����Ч */
    HI_U8   GlobalAlpha;    /**<Global alpha. This value is valid only when the alpha channel is valid.*//**<CNcomment:ȫ��alpha����ֵֻ����alphaͨ����Ч��ʱ��������� */
}HIGO_LAYER_ALPHA_S;


/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_6 */
/** @{ */  /** <!--[Gdev module] */


/**
\brief Obtains the default parameters of an SD or HD graphics layer based on its ID.
If you do not want to use default values, you can set the members of pLayerInfo.
CNcomment:����ͼ��ID��ȡ��Ӧͼ��(SD,HD)����ʱ��Ĭ�ϲ�����
�����Ҫʹ�÷�Ĭ��ֵ������ֱ������pLayerInfo������Ա
\attention \n

\param[in] LayerID Layer ID. CNcomment:ͼ��ID
\param[in]  pLayerInfo Obtained parameters of a graphics layer when it is created. CNcomment:��ȡ���Ĵ�������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERID
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVPARAM
\see \n
N/A. CNcomment:��
*/
HI_S32 HI_GO_GetLayerDefaultParam (HIGO_LAYER_E LayerID, HIGO_LAYER_INFO_S *pLayerInfo);


/** 
\brief Creates a graphics layer. CNcomment:����ͼ��
\attention \n
The platform determines whether VO hardware scaling is supported.
If VO hardware scaling is supported, the display size is scaled to fit the screen when the display size is inconsistent with the screen size.
If VO hardware scaling is not supported, the display size and screen size must be the same.
CNcomment:�Ƿ�֧��VOӲ������ȡ����ƽ̨��
���ƽ̨֧��VO Ӳ�����ţ���������displaysize��screensize��һ�µ�����£����ջ����ŵ�screensize�Ĵ�С��
���ƽ̨��֧��VO Ӳ�����ţ���ʹdisplaysize��screensize��һ�£�Ҳ��ǿ��Ҫ��displaysize��screensizeһ��

\param[in]  pLayerInfo Basic attributes of a graphics layer. The value cannot be empty. CNcomment:ͼ��������ԣ�����Ϊ��
\param[out] pLayer Pointer to the handle of a graphics layer. The value cannot be empty. CNcomment:ͼ��ľ��ָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT 
\retval ::HIGO_ERR_NULLPTR 
\retval ::HIGO_ERR_INVSIZE 
\retval ::HIGO_ERR_INVLAYERID 
\retval ::HIGO_ERR_INVPIXELFMT 
\retval ::HIGO_ERR_INVFLUSHTYPE
\retval ::HIGO_ERR_INVANILEVEL
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_NOMEM
\retval ::HIGO_ERR_INTERNAL
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_ALREADYBIND
\retval ::HIGO_ERR_INVLAYERSURFACE

\see \n
::HI_GO_DestroyLayer
*/
HI_S32 HI_GO_CreateLayer (const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE* pLayer);

/** 
\brief Destroys a graphics layer. CNcomment:����ͼ��
\attention \n
If a graphics layer is in use (for example, the desktop based on the layer is not destroyed), the layer cannot be destroyed.
CNcomment:��ͼ�����ڱ�ʹ��ʱ��������ڴ�ͼ�������δ���٣�����ͼ���޷�������
\param[in] Layer Layer handle. CNcomment:ͼ����

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE


\see \n
::HI_GO_CreateLayer
*/
HI_S32 HI_GO_DestroyLayer(HI_HANDLE Layer);


/** 
\brief Sets the position of a graphics layer on the screen. CNcomment:����ͼ������Ļ�е�λ��
\attention \n
The value takes effect at once and you do not need to refresh it. If the start position of a layer exceeds the screen, it is automatically adjusted to the boundary of the screen.
CNcomment:������Ч������ˢ�¡������õ�ͼ�����ʼλ�ó�����Ļ��Χʱ���Զ���������Ļ�ı߽�ֵ
\param[in] Layer  Layer handle. CNcomment:ͼ����
\param[in] u32StartX Horizontal coordinate of the position where a layer appears on the screen. CNcomment:ͼ������Ļ�ϵ���ʾλ��X����
\param[in] u32StartY Vertical coordinate of the position where a layer appears on the screen. CNcomment:ͼ������Ļ�ϵ���ʾλ��Y����

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERPOS

\see \n
::HI_GO_GetLayerPos
*/
HI_S32 HI_GO_SetLayerPos(HI_HANDLE Layer, HI_U32 u32StartX, HI_U32 u32StartY);

/** 
\brief Obtains the position where a layer appears on the screen. CNcomment:��ȡͼ������Ļ�ϵ�λ��
\attention \n
��
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[out] pStartX Pointer of the horizontal coordinate of the position where a layer appears on the screen. The value cannot be empty. CNcomment:ͼ������Ļ�ϵ���ʾλ��X����ָ�룬����Ϊ��
\param[out] pStartY Pointer of the vertical coordinate of the position where a layer appears on the screen. The value cannot be empty. CNcomment:ͼ������Ļ�ϵ���ʾλ��Y����ָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE


\see \n
::HI_GO_SetLayerPos
*/
HI_S32 HI_GO_GetLayerPos(HI_HANDLE Layer, HI_U32 *pStartX, HI_U32 *pStartY);


/** 
\brief Sets the output height and width of a graphics layer on the display device. CNcomment:�����������ʾ�豸�ϵ�����ĸ߶ȺͿ��
\attention \n
This API supports zoom in operations. The maximum range is specified when a graphics layer is created.\n
CNcomment:���ڴ�֧�ֵ�ǰ���£��ýӿڿ���֧������\n

\param[in]  Layer Layer handle. CNcomment:ͼ����
\param[in] u32SWidth  Actual output width. CNcomment:ʵ��������
\param[in] u32SHeight Actual output height. CNcomment:ʵ������߶�
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVSIZE
\retval ::HIGO_ERR_INVHANDLE


\see \n
::HI_GO_GetScreenSize
*/
HI_S32 HI_GO_SetScreenSize(HI_HANDLE Layer, HI_U32 u32SWidth, HI_U32 u32SHeight);


/** 
\brief Obtains the output height and width of a graphics layer on the display device. CNcomment:��ȡ�������ʾ�豸�ϵ�����ĸ߶ȺͿ�ȡ�
\attention \n
\param[in]  Layer Layer handle. CNcomment:ͼ����
\param[out] pSWidth  Pointer to the actual output width. CNcomment:ʵ��������ָ��
\param[out] pSHeight Pointer to the actual output height. CNcomment:ʵ������߶�ָ��
\retval none
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_SetScreenSize
*/
HI_S32 HI_GO_GetScreenSize(HI_HANDLE Layer, HI_U32 *pSWidth, HI_U32 *pSHeight);

/** 
\brief Sets the global alpha value of a layer surface. CNcomment:����ͼ��surface��ȫ��alphaֵ
\attention \n
The value takes effect at once, and you do not need to refresh it.
CNcomment:������Ч������ˢ��
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[in] Alpha Global alpha value. The value cannot be empty and ranges from 0 to 255. CNcomment:Alpha ȫ��alphaֵ������Ϊ�գ���Χ0-255

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_SETALPHAFAILED

\see \n
::HI_GO_GetLayerAlpha
*/

HI_S32 HI_GO_SetLayerAlpha(HI_HANDLE Layer, HI_U8 Alpha);

/** 
\brief Obtains the global alpha value of a layer surface. CNcomment:��ȡͼ��surface��ȫ��alphaֵ
\attention \n
��
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[out] pAlpha Pointer to the global alpha value. CNcomment:ȫ��alphaָ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_SetLayerAlpha
*/
HI_S32 HI_GO_GetLayerAlpha(HI_HANDLE Layer, HI_U8* pAlpha);


/** 
\brief Obtains the surface of a graphics layer. CNcomment:��ȡͼ���surface
\attention \n
Surface of a graphics layer. It cannot be released by calling HI_GO_FreeSurface. The surface can be released only when the corresponding layer is destroyed.
After a process is switched, you must obtain the layer surface again by calling HI_S32 HI_GO_GetLayerSurface.
CNcomment:ͼ��surface������ʹ��HI_GO_FreeSurface���ͷš�ֻ��������ͼ���ʱ��Żᱻ�ͷ�
�����л�֮�������øýӿ������»�ȡͼ��surface;
\param[in] Layer handle. CNcomment:Layer ͼ����
\param[out] pSurface Pointer to the surface handle. The value cannot be empty. CNcomment:surface���ָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_NOMEM

\see \n
N/A. CNcomment:��
*/
HI_S32 HI_GO_GetLayerSurface(HI_HANDLE Layer, HI_HANDLE *pSurface);

/** 
\brief Shows or hides a graphics layer. CNcomment:��ʾ������ͼ��
\attention \n
The value takes effect at once, and you do not need to refresh it.
CNcomment:������Ч������ˢ��
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[in] bVisbile Show/hide flag. HI_TRUE: show; HI_FALSE: hide. CNcomment:��ʾ���ر�־��HI_TRUE����ʾ��HI_FALSE������

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_GetLayerStatus
*/
HI_S32 HI_GO_ShowLayer(HI_HANDLE Layer, HI_BOOL bVisbile);
#if 0
/** 
\brief Obtains the current status of a graphics layer. CNcomment:��ȡͼ�㵱ǰ״̬
\attention \n
��
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[out] pLayerStatus Pointer to the current status of a graphics layer. The value cannot be empty. CNcomment:ͼ�㵱ǰ״̬�ṹָ�룬����Ϊ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
::HI_GO_ShowLayer
*/
HI_S32 HI_GO_GetLayerStatus(HI_HANDLE Layer, HIGO_LAYER_STATUS_S* pLayerStatus);
#endif
/** 
\brief Refreshes a graphics layer. CNcomment:ˢ��ͼ��
\attention \n
1. After drawing, you need to refresh the layer to display the drawing result.
2. There are two display modes after a graphics layer is refreshed. If there is no window, the contents of the layer surface are displayed; if there is a window, its contents are displayed.
CNcomment:1.������ɺ���ˢ��ͼ�������ʾ���ƺ���
2.ˢ��������ģʽ��һ����û���κδ��ڵ�ʱ�����ʾlayersurface�����ݣ�������ʾ�����е����ݡ�
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[in]  pRect Rectangle to be refreshed. If the value is NULL, the entire screen is refreshed. CNcomment:ˢ�µľ������������NULL, ��ˢ������ȫ��
\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE
\retval ::HIGO_ERR_INVLAYERSURFACE
\retval ::HIGO_ERR_OUTOFBOUNDS
\retval ::HIGO_ERR_EMPTYRECT

\see \n
N/A. CNcomment:��
*/
HI_S32 HI_GO_RefreshLayer(HI_HANDLE Layer, const HI_RECT* pRect);


#if 0
/**
\brief Sets the background color of a graphics layer. CNcomment:����ͼ��ı�����ɫ
\attention \n
The background color of a graphics layer takes effect only when widows are overlaid with each other.
CNcomment:ͼ�㱳��ɫ��ֻ���ڵ��Ӵ��ڲ���Ч
\param[in] Layer Layer handle. CNcomment:ͼ����
\param[in] Color Background color of a graphics layer. CNcomment:ͼ�㱳����ɫ

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE

\see \n
N/A. CNcomment:��
*/
HI_S32 HI_GO_SetLayerBGColor(HI_HANDLE Layer, HI_COLOR Color);

/**
\brief Sets the transparency of a graphics layer. CNcomment:����ͼ���͸��ɫ
\attention \n
��

\param[in] Layer       Layer handle. CNcomment:ͼ����              
\param[in] pKey        Pointer to the transparency information. The value cannot be empty. CNcomment:͸��ɫ��Ϣָ�룬����Ϊ��
\param[out] �� 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE

\see \n
    ::HI_GO_GetLayerColorkey
*/
HI_S32 HI_GO_SetLayerColorkey(HI_HANDLE Layer, const HIGO_LAYER_KEY_S *pKey);

/**
\brief Obtains the transparency information about a graphics layer. CNcomment:��ȡ͸��ɫ��Ϣ
\attention \n
��

\param[in] Layer       Layer handle. CNcomment:ͼ����              
\param[in] pKey        Pointer to the transparency information. CNcomment:͸��ɫ��Ϣָ��
\param[out] N/A. CNcomment:�� 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_NULLPTR
\retval ::HIGO_ERR_INVHANDLE 

\see \n
    ::HI_GO_SetLayerColorkey
*/
HI_S32 HI_GO_GetLayerColorkey(HI_HANDLE Layer, HIGO_LAYER_KEY_S *pKey);

/**
\brief Configures the alpha information about a graphics layer. This API is an extended API. CNcomment:����ͼ��alpha��Ϣ����չ�ӿ�
\attention \n
The alpha0 and alpha1 of the data structure HIGO_LAYER_ALPHA_S are valid only in ARGB1555 format.
This API is used to implement the translucent effect in ARGB1555 format.
CNcomment:�ýӿ�HIGO_LAYER_ALPHA_S�ṹ���alpha0,alpha1ֻ��ARGB1555��ʽ�²���Ч��
������ARGB1555��ʽ��ʵ�ְ�͸��Ч��

\param[in] Layer       Layer handle. CNcomment:ͼ����              
\param[in] pAlphaInfo   Alpha information about a graphics layer. The value cannot be empty. CNcomment:ͼ��alpha��Ϣ������Ϊ��   
\param[out] N/A. 

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_NULLPTR

\see \n
::HI_GO_GetLayerAlphaEx
*/
HI_S32 HI_GO_SetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo);


/**
\brief Obtains the alpha information about a graphics layer. This API is an extended API. CNcomment:��ȡͼ��alpha��Ϣ����չ�ӿ�
\attention \n
N/A

\param[in] Layer       Layer handle. CNcomment:ͼ����              
\param[out] pAlphaInfo  Alpha information about a graphics layer. The value cannot be empty. CNcomment:ͼ��alpha��Ϣ������Ϊ��   

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_INVHANDLE 
\retval ::HIGO_ERR_DEPEND_FB

\see \n
    ::HI_GO_SetLayerAlphaEx
*/
HI_S32 HI_GO_GetLayerAlphaEx(HI_HANDLE Layer,  HIGO_LAYER_ALPHA_S *pAlphaInfo);
#endif


/** @} */  /*! <!-- API declaration end */


#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_GDEV_H__ */
