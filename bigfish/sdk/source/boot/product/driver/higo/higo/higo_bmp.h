/**
 \file
 \brief BMP decode
 \copyright Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author Xuejiangcheng x57522
 \date 2008-8-20
 */

#ifndef __HIGO_BMP_H__
#define __HIGO_BMP_H__
#include "hi_type.h"
#include "higo_common.h"
#include "higo_surface.h"
#include "higo_io.h"
#include "hi_go_config.h"

/* add include here */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef HIGO_BMP_SUPPORT

/***************************** Macro Definition ******************************/

/*************************** Structure Definition ****************************/

/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

HI_S32 BMP_CreateDecoder(DEC_HANDLE *pBmpDec, const HIGO_DEC_ATTR_S *pSrcDesc);

HI_S32 BMP_DestroyDecoder(DEC_HANDLE BmpDec);

HI_S32 BMP_ResetDecoder(DEC_HANDLE BmpDec);

HI_S32 BMP_DecCommInfo(DEC_HANDLE BmpDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);

HI_S32 BMP_DecImgInfo(DEC_HANDLE BmpDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);

HI_S32 BMP_DecImgData(DEC_HANDLE BmpDec, HI_U32 Index, HIGO_SURFACE_S *pSurface);

HI_S32 BMP_ReleaseDecImgData(DEC_HANDLE BmpDec, HIGO_DEC_IMGDATA_S *pImgData);

#ifdef TEST_IN_ROOTBOX
HI_S32 BMP_DecExtendData(DEC_HANDLE BmpDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID **pData, HI_U32 *pLength);

HI_S32 BMP_ReleaseDecExtendData(DEC_HANDLE BmpDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID *pData);
#endif
HI_S32 BMP_GetActualSize(DEC_HANDLE BmpDec, HI_S32 Index, const HI_RECT *pSrcRect, HIGO_SURINFO_S *pSurInfo);

#endif

#ifdef __cplusplus
}
#endif
#endif /* __HIGO_BMP_H__ */
