/**
\file
\brief 图层适配模块
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author a
\date 2010-1-4
*/

#ifndef __ADP_LAYER_H__
#define __ADP_LAYER_H__

/* add include here */

#include "higo_surface.h"
#include "higo_gdev.h"


#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/
/** 图层最多个数, 此数据是可以改变的*/
//#ifndef HIGO_CODE_CUT
#define HIGO_LAYER_MAXCOUNT 6
//#else
//#define HIGO_LAYER_MAXCOUNT 4
//#endif
/** 图层能力集结构 */
typedef struct _HIGO_LAYER_CAP_S
{
    HI_U8       u8FmtCount;       /**< 支持的像素格式的个数 */
    HIGO_PF_E*  enPixelFmt;       /**< 图层支持的像素格式 */
    HI_BOOL     bPremultiply;     /**< 支持预乘格式 */
    HI_BOOL     bNonPremultiply;  /**< 支持非预乘格式 */
    HI_S32            MaxWidth;     
    HI_S32            MaxHeight;
    HI_S32            MinWidth;     
    HI_S32            MinHeight;
    HI_S32            MaxDisplayWidth;     
    HI_S32            MaxDisplayHeight;
    HI_BOOL           bVoScale;
} HIGO_LAYER_CAP_S;

struct fb_bitfield {
	HI_U32 offset;			/* beginning of bitfield	*/
	HI_U32 length;			/* length of bitfield		*/
	HI_U32 msb_right;		/* != 0 : Most significant bit is */ 
					/* right */ 
};

/** 位域信息结构 */
typedef struct _HIGO_BITFIELD_S
{
    struct fb_bitfield red;   /**< 红色位域信息 */
    struct fb_bitfield green; /**< 绿色位域信息 */
    struct fb_bitfield blue;  /**< 蓝色位域信息 */
    struct fb_bitfield transp;/**< 透明色位域信息 */
} HIGO_BITFIELD_S;


#ifndef HIGO_CODE_CUT
extern const HIGO_BITFIELD_S s_BitField[9] ;
#endif
HI_VOID ADP_Layer_ConvertFieldInfo(HIGO_PF_E enType, HIGO_BITFIELD_S *pstFieldInfo);
HI_S32 HIGO_ADP_InitDisplay(HI_VOID);
HI_VOID HIGO_ADP_CapabilityInquire(HI_U32 LayerID,  HIGO_LAYER_CAP_S** pstruCap);
HI_S32 HIGO_ADP_GetDefaultParam(HI_U32  LayerID, HIGO_LAYER_INFO_S *pLayerInfo);



/*************************** Structure Definition ****************************/

struct _HIGO_LAYER_ADP_S
{
    HI_S32  (*InitDisplay)(HI_VOID);/**< 系统初始化 */
    HI_VOID (*DeinitDisplay)(HI_VOID);/**< 系统去初始化*/
    HI_S32  (*GetDefautParam)(HI_U32 LayerID, HIGO_LAYER_INFO_S *pLayerInfo);
    HI_S32  (*CreateLayer)(HI_U32  LayerID,  HIGO_LAYER_INFO_S *pLayerInfo);/**< 创建图层*/
    HI_VOID  (*DestroyLayer)(HI_U32 LayerID);/**< 销毁图层 */

	HI_S32  (*SetLayerSurface)(HI_U32 LayerID, const HIGO_SURFACE_S *pSurface, HI_RECT *pRect);  /**刷新图层CANVAS BUFFER*/
	HI_S32  (*GetCanvasSurface)(HI_U32 LayerID, const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE *pSurface); /**获取图层CANVAS BUFFER*/
  //HI_S32  (*SetLayerZorder)(HI_U32 LayerID, HIGO_LAYER_ZORDER_E enZFlag);/**< 设置图层Z序*/
  //HI_S32  (*GetLayerZorder)(HI_U32 LayerID, HI_U32* u32ZFlag);
    HI_S32  (*ShowLayer)(HI_U32 LayerID, HI_BOOL bVisbile);/**< 显示图层*/
//    HI_S32  (*GetLayerShowState)(HI_U32 LayerID, HI_BOOL *pbVisbile);/**< 显示图层*/ 
    HI_S32  (*SetLayerAlpha)(HI_U32 LayerID, const HIGO_LAYER_ALPHA_S *pAlphaInfo); /**< 设置ALPHA函数 */
   // HI_S32  (*SetLayerColorKey)(HI_U32 LayerID, HI_BOOL bEnable, HI_U32 Key);/**< 设置COLORKEY */
    HI_S32  (*GetLayerAlpha)(HI_U32 LayerID, HIGO_LAYER_ALPHA_S *pAlphaInfo); /**< 获取ALPHA函数 */
#ifndef HIGO_CODE_CUT
    HI_S32  (*SetLayerColorKey)(HI_U32 LayerID, HI_BOOL bEnable, HI_U32 Key);/**< 设置COLORKEY */
    HI_S32  (*GetLayerColorKey)(HI_U32 LayerID,HI_BOOL *pbEnable, HI_U32 *pKey);/**< 设置COLORKEY */
   // HI_S32  (*GetPalette)(HI_U32 LayerID, HI_PALETTE pPalette);/**< 设置调色板 */
    HI_S32  (*SetPos)( HI_U32 LayerID, HI_U32 u32XStart, HI_U32 u32YStart);   /**< 修改图层在屏幕上的显示位置 */
    HI_S32  (*GetPos)(HI_U32 LayerID, HI_U32* pXStart, HI_U32* pYStart);   /**< 获取图层在屏幕上的显示位置 */
	HI_S32  (*SetScreenSize)(HI_U32 LayerID, HI_U32 u32Width, HI_U32 u32Height);       /**< 获取屏幕的高宽 */
	HI_S32  (*GetScreenSize)(HI_U32 LayerID, HI_U32 *pWidth, HI_U32 *pHeight);       /**< 获取屏幕的高宽 */	
	HI_S32  (*SetDisplaySize)(HI_U32 LayerID, HI_U32 u32Width, HI_U32 u32Height);       /**< 设置中间显示buffer的高宽 */
	HI_S32  (*GetDisplaySize)(HI_U32 LayerID, HI_U32 *pWidth, HI_U32 *pHeight);       /**< 获取中间显示buffer的高宽 */	

    HI_S32  (*RefreshLayer)(HI_U32 LayerID, const HI_RECT *pRect);    
    HI_VOID (*CapabilityInquire)(HI_U32 LayerID,  HIGO_LAYER_CAP_S** pstruCap);
    HI_U32  LayerCount;
#endif    
};


typedef struct _HIGO_LAYER_ADP_S HIGO_LAYER_ADP_S;

/******************************* API declaration *****************************/

HI_S32 HIGO_ADP_CreateVideoDevice(HIGO_LAYER_ADP_S *thiz);

#ifdef __cplusplus
}
#endif
#endif /* __ADP_LAYER_H__ */

