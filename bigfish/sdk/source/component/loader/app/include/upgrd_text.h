/******************************************************************************
                              Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : test_loader.h
Version       : Initial Draft
Author        : Hisilicon multimedia Hardware group l50549
Created       : 2007/08/20
Last Modified :
Description   :
Function List :
History       :
******************************************************************************/
#ifndef __UPDATE_TEXT_H__
#define __UPDATE_TEXT_H__

#include "hi_type.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_4 */
/** @{ */  /** <!-- [UI display data structure] */

HI_S32 HI_GO_CreateText(const HI_CHAR* pSbFontFile, const HI_CHAR* pMbFontFile, HI_HANDLE* pTextOut);

HI_S32 HI_GO_GetTextExtent(HI_HANDLE TextOut, const HI_CHAR *pText, HI_S32 *pWidth, HI_S32 *pHeight);

HI_S32 HI_GO_SetTextBGColor(HI_HANDLE TextOut, HI_COLOR Color);

HI_S32 HI_GO_SetTextColor(HI_HANDLE TextOut, HI_COLOR Color);

HI_S32 HI_GO_TextOut(HI_HANDLE TextOut, HI_HANDLE Surface, const HI_CHAR *pText,
                     const HI_RECT *pRect);

/** @} */  /** <!-- ==== API declaration end ==== */
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*__UPDATE_OSD_H__*/
