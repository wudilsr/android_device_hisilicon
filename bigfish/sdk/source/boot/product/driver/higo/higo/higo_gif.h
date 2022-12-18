/**
 \file
 \brief GIF½âÂë¹¦ÄÜ
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author wangxilin
 \date 2008-5-29
 */

#ifndef __HIGO_GIF_H__
#define __HIGO_GIF_H__

/* add include here */
#include "higo_common.h"
#include "hi_go_decoder.h"
#include "higo_io.h"
#include "hi_go_config.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef HIGO_GIF_SUPPORT

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

HI_S32 GIF_CreateDecoder(DEC_HANDLE *pGifDec, const HIGO_DEC_ATTR_S *pSrcDesc);

HI_S32 GIF_DestroyDecoder(DEC_HANDLE GifDec);

HI_S32 GIF_ResetDecoder(DEC_HANDLE GifDec);

HI_S32 GIF_DecCommInfo(DEC_HANDLE GifDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);

HI_S32 GIF_DecImgInfo(DEC_HANDLE GifDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);

HI_S32 GIF_SetDecImgAttr(DEC_HANDLE GifDec, HI_U32 Index, const HIGO_DEC_IMGATTR_S *pImgAttr);

HI_S32 GIF_DecImgData(DEC_HANDLE GifDec, HI_U32 Index, HIGO_SURFACE_S *pSurface);

#ifdef TEST_IN_ROOTBOX
HI_S32 GIF_DecExtendData(DEC_HANDLE GifDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID **pData, HI_U32 *pLength);

HI_S32 GIF_ReleaseDecExtendData(DEC_HANDLE GifDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID *pData);
#endif
HI_S32 GIF_GetActualSize(DEC_HANDLE GifDec, HI_S32 Index, const HI_RECT *pSrcRect, HIGO_SURINFO_S *pSurInfo);
#endif

#ifdef __cplusplus
}
#endif
#endif /* __HIGO_GIF_H__ */
