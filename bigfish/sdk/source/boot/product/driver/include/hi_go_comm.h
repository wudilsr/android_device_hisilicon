/**
 \file
 \brief Describes the header file that contains the common contents of the HiGo.CNcomment:HiGo��������ͷ�ļ�
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version 1.0
 \author s37678
 \date 2008-5-16
 */

#ifndef __HI_GO_COMM_H__
#define __HI_GO_COMM_H__

/* add include here */
#include "hi_type.h"
#include "hi_go_errno.h"

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/
/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_3_3_2 */
/** @{ */  /**<!��[Common contents of the HiGo]*//**CNcomment: <!-- ��HiGo�������ݡ� */

/**Maximum number of colors in the palette*//**CNcomment: ��ɫ�������ɫ�� */
#define MAX_PALETTE_COLOR_SIZE 256

/**Color value*//**CNcomment: ��ɫֵ */
typedef HI_U32 HI_COLOR;

/**Palette*//**CNcomment: ��ɫ�� */
typedef HI_COLOR HI_PALETTE[MAX_PALETTE_COLOR_SIZE];

typedef enum 
{
    HIGO_IMGTYPE_JPEG = 0, /**<.jpeg picture*//**CNcomment:< JPEG��ʽͼƬ*/
    HIGO_IMGTYPE_GIF,      /**<.gif picture*//**CNcomment:< GIF��ʽͼƬ*/
    HIGO_IMGTYPE_BMP,       /**<.bmp picture*//**CNcomment:< BMP��ʽͼƬ */
    HIGO_IMGTYPE_PNG,      /**<.png picture*//**CNcomment:< PNG��ʽͼƬ */
    HIGO_IMGTPYE_BUTT
} HIGO_IMGTYPE_E;


/**Rectangle*//**CNcomment: ���� */
typedef struct
{
    HI_S32 x, y;

    HI_S32 w, h;
} HI_RECT;

/**Region*//**CNcomment: ���� */
typedef struct
{
    HI_S32 l;
    HI_S32 t;
    HI_S32 r;
    HI_S32 b;
} HI_REGION;


#define HIGO_INVALID_HANDLE 0x0

/**Stream position*//**CNcomment: ��ʽλ��*/


/** @} */  /*! <!-- Structure Definition end */

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/
/** \addtogroup      H_1_3_3_2 */
/** @{ */  /** <!��[Common contents of the HiGo]*//**CNcomment: <!-- ��HiGo�������ݡ� */


/** 
\brief Initializes the HiGo.CNcomment:HiGo��ʼ��
\attention \n
Before using the HiGo, you must call this application programming interface (API) to initialize the HiGo. The HiGo 
includes the graphic device (Gdev) module, decoder, Winc module, bit block transfer (Bliter) module, and surface 
module.
CNcomment:ʹ��HiGo���ܱ����ȵ��øýӿڣ����HiGo�ĳ�ʼ������Ҫ����gdev, decoder, winc, blit, surfaceģ��
\param N/A.CNcomment:��

\retval ::HI_SUCCESS
\retval ::HI_FAILURE
\retval ::HIGO_ERR_DEPEND_TDE
\retval ::HIGO_ERR_INITFAILED

\see \n
::HI_GO_Deinit
*/
HI_S32	HI_GO_Init(HI_VOID);

/**
\brief Deinitializes the HiGo.CNcomment: HiGoȥ��ʼ��
\attention \n
If the HiGo is not used, you need to call this API to release resources.CNcomment: ����ʹ��HiGo����ʱ��Ҫ���øýӿڣ��ͷ���Դ
\param N/A.CNcomment: ��

\retval ::HI_SUCCESS
\retval ::HIGO_ERR_NOTINIT
\retval ::HIGO_ERR_DEINITFAILED

\see \n
::HI_GO_Init
*/
HI_S32	HI_GO_Deinit(HI_VOID);


#ifdef __cplusplus
}
#endif
#endif /* __HI_GO_COMM_H__ */
