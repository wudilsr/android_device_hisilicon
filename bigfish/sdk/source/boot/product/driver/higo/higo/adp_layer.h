/**
\file
\brief ͼ������ģ��
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
/** ͼ��������, �������ǿ��Ըı��*/
//#ifndef HIGO_CODE_CUT
#define HIGO_LAYER_MAXCOUNT 6
//#else
//#define HIGO_LAYER_MAXCOUNT 4
//#endif
/** ͼ���������ṹ */
typedef struct _HIGO_LAYER_CAP_S
{
    HI_U8       u8FmtCount;       /**< ֧�ֵ����ظ�ʽ�ĸ��� */
    HIGO_PF_E*  enPixelFmt;       /**< ͼ��֧�ֵ����ظ�ʽ */
    HI_BOOL     bPremultiply;     /**< ֧��Ԥ�˸�ʽ */
    HI_BOOL     bNonPremultiply;  /**< ֧�ַ�Ԥ�˸�ʽ */
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

/** λ����Ϣ�ṹ */
typedef struct _HIGO_BITFIELD_S
{
    struct fb_bitfield red;   /**< ��ɫλ����Ϣ */
    struct fb_bitfield green; /**< ��ɫλ����Ϣ */
    struct fb_bitfield blue;  /**< ��ɫλ����Ϣ */
    struct fb_bitfield transp;/**< ͸��ɫλ����Ϣ */
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
    HI_S32  (*InitDisplay)(HI_VOID);/**< ϵͳ��ʼ�� */
    HI_VOID (*DeinitDisplay)(HI_VOID);/**< ϵͳȥ��ʼ��*/
    HI_S32  (*GetDefautParam)(HI_U32 LayerID, HIGO_LAYER_INFO_S *pLayerInfo);
    HI_S32  (*CreateLayer)(HI_U32  LayerID,  HIGO_LAYER_INFO_S *pLayerInfo);/**< ����ͼ��*/
    HI_VOID  (*DestroyLayer)(HI_U32 LayerID);/**< ����ͼ�� */

	HI_S32  (*SetLayerSurface)(HI_U32 LayerID, const HIGO_SURFACE_S *pSurface, HI_RECT *pRect);  /**ˢ��ͼ��CANVAS BUFFER*/
	HI_S32  (*GetCanvasSurface)(HI_U32 LayerID, const HIGO_LAYER_INFO_S *pLayerInfo, HI_HANDLE *pSurface); /**��ȡͼ��CANVAS BUFFER*/
  //HI_S32  (*SetLayerZorder)(HI_U32 LayerID, HIGO_LAYER_ZORDER_E enZFlag);/**< ����ͼ��Z��*/
  //HI_S32  (*GetLayerZorder)(HI_U32 LayerID, HI_U32* u32ZFlag);
    HI_S32  (*ShowLayer)(HI_U32 LayerID, HI_BOOL bVisbile);/**< ��ʾͼ��*/
//    HI_S32  (*GetLayerShowState)(HI_U32 LayerID, HI_BOOL *pbVisbile);/**< ��ʾͼ��*/ 
    HI_S32  (*SetLayerAlpha)(HI_U32 LayerID, const HIGO_LAYER_ALPHA_S *pAlphaInfo); /**< ����ALPHA���� */
   // HI_S32  (*SetLayerColorKey)(HI_U32 LayerID, HI_BOOL bEnable, HI_U32 Key);/**< ����COLORKEY */
    HI_S32  (*GetLayerAlpha)(HI_U32 LayerID, HIGO_LAYER_ALPHA_S *pAlphaInfo); /**< ��ȡALPHA���� */
#ifndef HIGO_CODE_CUT
    HI_S32  (*SetLayerColorKey)(HI_U32 LayerID, HI_BOOL bEnable, HI_U32 Key);/**< ����COLORKEY */
    HI_S32  (*GetLayerColorKey)(HI_U32 LayerID,HI_BOOL *pbEnable, HI_U32 *pKey);/**< ����COLORKEY */
   // HI_S32  (*GetPalette)(HI_U32 LayerID, HI_PALETTE pPalette);/**< ���õ�ɫ�� */
    HI_S32  (*SetPos)( HI_U32 LayerID, HI_U32 u32XStart, HI_U32 u32YStart);   /**< �޸�ͼ������Ļ�ϵ���ʾλ�� */
    HI_S32  (*GetPos)(HI_U32 LayerID, HI_U32* pXStart, HI_U32* pYStart);   /**< ��ȡͼ������Ļ�ϵ���ʾλ�� */
	HI_S32  (*SetScreenSize)(HI_U32 LayerID, HI_U32 u32Width, HI_U32 u32Height);       /**< ��ȡ��Ļ�ĸ߿� */
	HI_S32  (*GetScreenSize)(HI_U32 LayerID, HI_U32 *pWidth, HI_U32 *pHeight);       /**< ��ȡ��Ļ�ĸ߿� */	
	HI_S32  (*SetDisplaySize)(HI_U32 LayerID, HI_U32 u32Width, HI_U32 u32Height);       /**< �����м���ʾbuffer�ĸ߿� */
	HI_S32  (*GetDisplaySize)(HI_U32 LayerID, HI_U32 *pWidth, HI_U32 *pHeight);       /**< ��ȡ�м���ʾbuffer�ĸ߿� */	

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

