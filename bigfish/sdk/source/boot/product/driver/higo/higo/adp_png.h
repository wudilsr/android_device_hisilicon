/**
\file
\brief png adaptive layer
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author memmng
\date 2010-2-1
*/

#ifndef __ADP_PNG_H__
#define __ADP_PNG_H__

/* add include here */

#include "hi_go_config.h"

#ifdef HIGO_PNG_SUPPORT
#include "higo_common.h"
#include "higo_io.h"
#include "higo_surface.h"
#include "hi_go_decoder.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif
#ifdef HIGO_PNG_SUPPORT
/***************************** Macro Definition ******************************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/
HI_S32 HIGO_ADP_PngCreateDecoder(DEC_HANDLE *pPngDec, const  HIGO_DEC_ATTR_S *pSrcDesc);

HI_S32 HIGO_ADP_PngDestroyDecoder(DEC_HANDLE PngDec);

HI_S32 HIGO_ADP_PngResetDecoder(DEC_HANDLE PngDec);

HI_S32 HIGO_ADP_PngDecCommInfo(DEC_HANDLE PngDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);

HI_S32 HIGO_ADP_PngDecImgInfo(DEC_HANDLE PngDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);

HI_S32 HIGO_ADP_PngDecImgData(DEC_HANDLE PngDec, HI_U32 Index, HIGO_SURFACE_S *pSurface);
#if 0
HI_S32 HIGO_ADP_PngDecExtendData(DEC_HANDLE PngDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID **pData,
                                 HI_U32 *pLength);

HI_S32 HIGO_ADP_PngReleaseDecExtendData(DEC_HANDLE PngDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID *pData);
#endif
HI_S32 HIGO_ADP_PngGetActualSize(DEC_HANDLE PngDec, HI_S32 Index, const HI_RECT *pSrcRect, HIGO_SURINFO_S *pSurInfo);

#endif
#ifdef __cplusplus
}
#endif
#endif /* __ADP_PNG_H__ */
