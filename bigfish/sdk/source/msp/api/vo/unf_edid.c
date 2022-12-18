/******************************************************************************

   Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.

******************************************************************************
	File Name     : hi_unf_edid.c
	Version       : Initial Draft
	Author        : Hisilicon TC group
	Created       : 2013/10/08
	Description   :
	History       :
	1.Date        : 2013/10/08
	Author	      : w00217574
	Modification  : Created file

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "hi_mpi_edid.h"
typedef struct tagEDID_VIDEO_FORMAT_S
{
    HI_BOOL                      bProgressive;
    HI_U16                      u32Hact;
    HI_U16                      u32Vact;
    HI_U16                      u32VerFreq;
    HI_UNF_ENC_FMT_E enFormat;
} EDID_VIDEO_FORMAT_S;

EDID_VIDEO_FORMAT_S g_EDIDVideoFmt[] = 
{
    {HI_TRUE ,1920,1080,60,HI_UNF_ENC_FMT_1080P_60},
    {HI_TRUE ,1920,1080,50,HI_UNF_ENC_FMT_1080P_50},
    {HI_TRUE ,1920,1080,30,HI_UNF_ENC_FMT_1080P_30},
    {HI_TRUE ,1920,1080,25,HI_UNF_ENC_FMT_1080P_25},
    {HI_TRUE ,1920,1080,24,HI_UNF_ENC_FMT_1080P_24},
        
    {HI_FALSE ,1920,1080,60,HI_UNF_ENC_FMT_1080i_60},
    {HI_FALSE ,1920,1080,50,HI_UNF_ENC_FMT_1080i_50},

    {HI_TRUE ,1280,720,60,HI_UNF_ENC_FMT_720P_60},
    {HI_TRUE ,1280,720,50,HI_UNF_ENC_FMT_720P_50},

    {HI_TRUE ,720,576,60,HI_UNF_ENC_FMT_576P_50},
    {HI_TRUE ,720,480,50,HI_UNF_ENC_FMT_480P_60},
        
    {HI_FALSE,720,576,50,HI_UNF_ENC_FMT_PAL},
    {HI_FALSE ,720,480,60,HI_UNF_ENC_FMT_NTSC},
};

HI_UNF_ENC_FMT_E EDID_GetVideoFormat(EDID_VIDEO_TIMING_S *pstVideoTiming,HI_BOOL *pbNativeFormat)
{
    HI_U32 i;
    if (!pstVideoTiming)
        return HI_UNF_ENC_FMT_BUTT;

    *pbNativeFormat = HI_FALSE;
    for ( i = 0; i < sizeof(g_EDIDVideoFmt)/sizeof(EDID_VIDEO_FORMAT_S); i++ )
    {
        if ((pstVideoTiming->bProgressive == g_EDIDVideoFmt[i].bProgressive)
            &&(pstVideoTiming->u32Hact == g_EDIDVideoFmt[i].u32Hact)
            &&(pstVideoTiming->u32Vact == g_EDIDVideoFmt[i].u32Vact)
            &&(pstVideoTiming->u32VerFreq == g_EDIDVideoFmt[i].u32VerFreq)
            )
        {
          
            if (HI_UNF_EDID_TIMING_ATTR_PREFERRED_TIMING == pstVideoTiming->enTimingAttr)
                *pbNativeFormat = HI_TRUE;
            else
                *pbNativeFormat = HI_FALSE;
            
            return g_EDIDVideoFmt[i].enFormat;
        }
    }
     return HI_UNF_ENC_FMT_BUTT;
}

HI_S32 HI_UNF_EDID_EdidParse(HI_U8 *pu8Edid, HI_U32 u32EdidLength,HI_UNF_EDID_INFO_S *pstEdidInfo)
{
    HI_U32 i;
    HI_S32 s32Ret;
    
    struct list_head* pos = HI_NULL;
    EDID_INFO_S  stEdidMpiInfo;
    EDID_SIMPLE_TIMING_S *pstSimpleTimingList;
    EDID_DETAIL_TIMING_S *pstDetailTimingList;
    EDID_VIDEO_TIMING_S *pstVideTimingList;
    HI_UNF_EDID_SIMPLE_TIMING_S   *pstSimpleTiming = HI_NULL ;	/* Est. stTimings and mfg rsvd stTimings*/
    HI_UNF_EDID_DETAIL_TIMING_S   *pstDetailTiming = HI_NULL;	    /* Detailing stTimings  */
    
    memset(&stEdidMpiInfo,0x0,sizeof(EDID_INFO_S));
    memset(pstEdidInfo,0x0,sizeof(HI_UNF_EDID_INFO_S));
    
    s32Ret = HI_MPI_EDID_EdidParse(pu8Edid, u32EdidLength,&stEdidMpiInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_EDID("EDID parse err \n");
        return HI_FAILURE;
    }
    
    /*add Simple Timing*/
    pstEdidInfo->u32SimpleTimingNum = stEdidMpiInfo.u32SimpleTimingNum;
    if (HI_NULL != stEdidMpiInfo.pstSimpleTimingList)
     {
        pstSimpleTiming = malloc(sizeof(HI_UNF_EDID_SIMPLE_TIMING_S)*stEdidMpiInfo.u32SimpleTimingNum);
        if (NULL == pstSimpleTiming)
        {
            HI_ERR_EDID("maloc err \n");
            s32Ret = HI_FAILURE;
            goto ERR_EXIT1;
        }
     
        pos = &stEdidMpiInfo.pstSimpleTimingList->head;
        i =0;
        do
        {
            pstSimpleTimingList = list_entry(pos, EDID_SIMPLE_TIMING_S, head);
            pstSimpleTiming[i] = pstSimpleTimingList->stSimpleTiming;
            
            pos = pos->next;
            i++;
            
            if(i >= stEdidMpiInfo.u32SimpleTimingNum )
                break;
        }
        while (pos != &(stEdidMpiInfo.pstSimpleTimingList->head));
   }
/*add Detail Timing*/
    pstEdidInfo->u32DetailTimingNum = stEdidMpiInfo.u32DetailTimingNum;

    if (HI_NULL != stEdidMpiInfo.pstDetailTimingList)
    {
        pstDetailTiming = malloc(sizeof(HI_UNF_EDID_DETAIL_TIMING_S)*stEdidMpiInfo.u32DetailTimingNum);
        if (NULL == pstDetailTiming)
        {

            HI_ERR_EDID("maloc err \n");
            s32Ret = HI_FAILURE;
            goto ERR_EXIT1;
        }
        pos = &stEdidMpiInfo.pstDetailTimingList->head;
         i =0;
        do
        {
            pstDetailTimingList = list_entry(pos, EDID_DETAIL_TIMING_S, head);
            pstDetailTiming[i] = pstDetailTimingList->stDetailTiming;
            
            if (HI_UNF_EDID_TIMING_ATTR_PREFERRED_TIMING == pstDetailTiming->enTimingAttr)
                pstEdidInfo->stEDIDBaseInfo.stPerferTiming  = pstDetailTiming[i].stTiming ;
            
            pos = pos->next;
            i++;
            
            if(i >= stEdidMpiInfo.u32DetailTimingNum )
                break;
        }
        while (pos != &(stEdidMpiInfo.pstDetailTimingList->head));
   }
    /*add base info*/
    pstEdidInfo->enVideoPort = stEdidMpiInfo.enVideoPort;
    pstEdidInfo->stEDIDBaseInfo.u8Version = stEdidMpiInfo.stVersion.u8Version;
    pstEdidInfo->stEDIDBaseInfo.u8Revision = stEdidMpiInfo.stVersion.u8Revision;
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u32ProductCode = stEdidMpiInfo.stVendor.u16ProductCode;
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u32SerialNumber = stEdidMpiInfo.stVendor.u32SerialNum;
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u32Week = stEdidMpiInfo.stVendor.u32MfWeek;
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u32Year = stEdidMpiInfo.stVendor.u32MfYear;
    
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u8MfrsName[0] = (HI_U8) stEdidMpiInfo.stVendor.cMfName[0];
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u8MfrsName[1] = (HI_U8) stEdidMpiInfo.stVendor.cMfName[1];
    pstEdidInfo->stEDIDBaseInfo.stMfrsInfo.u8MfrsName[2] = (HI_U8) stEdidMpiInfo.stVendor.cMfName[2];
    

    if (stEdidMpiInfo.pstExitenInfo)
    {
        if ( stEdidMpiInfo.pstExitenInfo->pstVideoFormat )
        {
            pstEdidInfo->stEDIDBaseInfo.bSupportHdmi = HI_TRUE;
            pstEdidInfo->stEDIDBaseInfo.bSupportDVIDual = stEdidMpiInfo.pstExitenInfo->pstVideoFormat->bDVI_Dual;
            pstEdidInfo->stEDIDBaseInfo.bSupportsAI = stEdidMpiInfo.pstExitenInfo->pstVideoFormat->bSupportsAI;

            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColorY444= stEdidMpiInfo.pstExitenInfo->pstVideoFormat->bDC_Y444;
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColor30Bit = stEdidMpiInfo.pstExitenInfo->pstVideoFormat->bDC_30bit;
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColor36Bit= stEdidMpiInfo.pstExitenInfo->pstVideoFormat->bDC_36bit;
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColor48Bit= stEdidMpiInfo.pstExitenInfo->pstVideoFormat->bDC_48bit;
        }
        else
        {
            pstEdidInfo->stEDIDBaseInfo.bSupportHdmi = HI_FALSE;
            pstEdidInfo->stEDIDBaseInfo.bSupportDVIDual = HI_FALSE;
            pstEdidInfo->stEDIDBaseInfo.bSupportsAI = HI_FALSE;
            
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColorY444 = HI_FALSE;
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColor30Bit = HI_FALSE;
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColor36Bit = HI_FALSE;
            pstEdidInfo->stEDIDBaseInfo.stDeepColor.bDeepColor48Bit = HI_FALSE;
        }

        HI_UNF_ENC_FMT_E enFormat = HI_UNF_ENC_FMT_BUTT;
        HI_BOOL bNativeFormat = HI_FALSE;

        if (stEdidMpiInfo.pstExitenInfo->pstVideoTiming)
        {
            pos = &stEdidMpiInfo.pstExitenInfo->pstVideoTiming->head;
            do
            {
                pstVideTimingList = list_entry(pos, EDID_VIDEO_TIMING_S, head);
                enFormat = EDID_GetVideoFormat(pstVideTimingList,&bNativeFormat);
                if (HI_UNF_ENC_FMT_BUTT != enFormat)
                {
                    pstEdidInfo->stEDIDBaseInfo.bSupportFormat[enFormat] = HI_TRUE;
                    
                    if (HI_TRUE == bNativeFormat)
                        pstEdidInfo->stEDIDBaseInfo.enNativeFormat = enFormat;
                }   
                    pos = pos->next;
            }
            while (pos != &(stEdidMpiInfo.pstExitenInfo->pstVideoTiming->head));
        }
    }

    pstEdidInfo->pstSimpleTiming = pstSimpleTiming ;
    pstEdidInfo->pstDetailTiming = pstDetailTiming ;
    
    HI_MPI_EDID_EdidRelease(&stEdidMpiInfo);
    return s32Ret;
    
ERR_EXIT1:   
    if (pstSimpleTiming)
        free(pstSimpleTiming);
    HI_MPI_EDID_EdidRelease(&stEdidMpiInfo);
    return s32Ret;
}

HI_VOID HI_UNF_EDID_EdidRelease(HI_UNF_EDID_INFO_S *pEdidInfo)
{
    if ( !pEdidInfo )
        return;
    
    if ( pEdidInfo->pstSimpleTiming )
        free(pEdidInfo->pstSimpleTiming);
    
    if (pEdidInfo->pstDetailTiming)
        free(pEdidInfo->pstDetailTiming);    
}

