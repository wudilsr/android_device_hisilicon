/**
\file
\brief GDEV模块间操作函数
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author w66592
\date 2010-2-1
*/

#ifndef __HIGO_GDEV_H__
#define __HIGO_GDEV_H__

/* add include here */
#include "higo_common.h"
#include "hi_go_surface.h"
#include "hi_go_gdev.h"

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/



#define HIGO_SD_MAXWIDTH  720
#define HIGO_SD_MAXHEIGHT 576
#define HIGO_SD_MINWIDTH  8
#define HIGO_SD_MINHEIGHT 8

#define HIGO_HD_MAXWIDTH  3840
#define HIGO_HD_MAXHEIGHT 2160
#define HIGO_HD_MINWIDTH  8
#define HIGO_HD_MINHEIGHT 8
#define HIGO_MAX_FLIPBUF_NUM 2

/*************************** Structure Definition ****************************/

typedef struct _HIGO_LAYER_REC_S
{
    HI_U32                 LayerID;       /**< 硬件图层ID */
    HI_HANDLE              hLayer;        /**< 图层句柄 */
    HI_BOOL                bCreated;      /**< 图层是否已经被创建 */
    HIGO_LAYER_INFO_S      LayerInfo;     /**< 图层信息*/
    HI_HANDLE              hLayerSurface;  /**< 图层surface句柄*/
} HIGO_LAYER_REC_S;

typedef struct
{
    HI_S32 s32XPos;         /**<  horizontal position *//**<CNcommnet:水平位置 */
    HI_S32 s32YPos;         /**<  vertical position *//**<CNcomment:垂直位置 */
}HIGO_POINT_S;

typedef struct
{
    HI_BOOL bKeyEnable;      /*colorkey enable flag*//*CNcomment:colorkey 是否使能*/
    HI_BOOL bMaskEnable;    /*key mask enable flag*//*CNcomment:key mask 是否使能*/
    HI_U32 u32Key;              /*key value*/
    HI_U8 u8RedMask;          /*red mask*/
    HI_U8 u8GreenMask;       /*green mask*/
    HI_U8 u8BlueMask;          /*blue mask*/
    HI_U8 u8Reserved;           
    HI_U32 u32KeyMode;	 /*0:In region; 1:Out region*/

    /*Max colorkey value of red component*/
    /*CNcomment:colorkey红色分量最大值*/
    HI_U8 u8RedMax;

    /*Max colorkey value of Green component*/
    /*CNcomment:colorkey绿色分量最大值*/
    HI_U8 u8GreenMax; 

    /*Max colorkey value of blue component*/
    /*CNcomment:colorkey蓝色分量最大值*/
    HI_U8 u8BlueMax;           
    HI_U8 u8Reserved1;

    /*Min colorkey value of red component*/
    /*CNcomment:colorkey红色分量最小值*/
    HI_U8 u8RedMin;            

    /*Min colorkey value of Green component*/
    /*CNcomment:colorkey绿色分量最小值*/
    HI_U8 u8GreenMin;         

    /*Min colorkey value of blue component*/
    /*CNcomment:colorkey蓝色分量最小值*/
    HI_U8 u8BlueMin;            
    HI_U8 u8Reserved2;
}HIGO_COLORKEYEX_S;

/********************** Global Variable declaration **************************/

HI_S32 HIGO_InitDisplay(HI_VOID);
HI_S32 HIGO_DinitDisplay(HI_VOID);

#ifdef __cplusplus
}
#endif
#endif /* __HIGO_GDEV_H__ */
