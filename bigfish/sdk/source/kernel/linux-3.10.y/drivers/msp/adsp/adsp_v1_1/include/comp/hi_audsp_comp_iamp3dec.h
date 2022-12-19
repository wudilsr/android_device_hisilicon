
/*********************************************************************

Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
**********************************************************************
File Name     :	pcmdec.h
Version	      :	Initial	Draft
Author	      :	Hisilicon multimedia software group
Created	      :	2007/7/23
Last Modified :
Description   :	API header file for the codec of PCM
Function List :
History	      :
* Version     Date	   Author     DefectNum	      Description
           2008/10/11   y00106256      NULL       Create this file.
*********************************************************************/
#ifndef __AUDSP_COMP_PCMDEC_H__
#define __AUDSP_COMP_PCMDEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif     /* __cpluscplus */
#endif  /* __cpluscplus */

#include "hi_type.h"

/****************************************************************************
                            DATA TYPE INFORMATION
****************************************************************************/
typedef struct
{
    /* output */
    HI_U32 u32StreamSampleRate;
    HI_U32 u32StreamChannels;
    HI_U32 u32StreamBitRate;

    HI_U32 u32PcmSampleRate;
    HI_U32 u32LbrSampleRate;
    HI_U32 u32HbrSampleRate;

    HI_U32 u32PcmChannels;
    HI_U32 u32LbrChannels;/* 2 */
    HI_U32 u32HbrChannels;/* 2(DDP) or 8 */

    HI_U32 u32PcmBitDepth;/* 16 or 24 */
    HI_U32 u32LbrBitDepth;/* 16 */
    HI_U32 u32HbrBitDepth;/* 16 */

    HI_U32 u32PcmBytesPerFrame;
    HI_U32 u32LbrBytesPerFrame;
    HI_U32 u32HbrBytesPerFrame;

    HI_BOOL bAckEosFlag;
    HI_BOOL bInterlace;

    HI_U32 u32CurnPtsReadPos; /* for PTS */

    HI_S32 s32ChannelMode;
} MP3_FRMAE_BUF_S;


#ifdef __cplusplus
#if __cplusplus
}
#endif     /* __cpluscplus */
#endif  /* __cpluscplus */

#endif  /* __AUDSP_COMP_PCMDEC_H__ */

