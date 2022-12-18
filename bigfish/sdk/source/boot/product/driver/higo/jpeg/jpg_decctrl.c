/*******************************************************************************
 *              Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_decctrl.c
 * Description:
 *
 * History:
 * Version   Date             Author    DefectNum    Description
 * main\1    2008-04-09       z53517    HI_NULL      Create this file.
 ******************************************************************************/
#include "higo_adp_sys.h"
#include "jpg_common.h"
#include "jpg_decctrl.h"
#include "jpg_handle.h"
#include "jpg_buf.h"
#include "jpg_parse.h"

#include "jpg_hsdec.h"
#include "jpg_hdec.h"
#include "jpg_driver.h"
#include "exports.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

/****************************************************************************
*                       *
****************************************************************************/

typedef enum hiJPG_DECTYPE_E
{
    JPG_DECTYPE_HW = 0,
    JPG_DECTYPE_SW = 1,
    JPG_DECTYPE_BUTT
}JPG_DECTYPE_E;

/* AI7D02624 Modify*/
typedef struct hiJPG_DECCTX_S
{
    JPG_CYCLEBUF_S  ParseBuf;
    JPG_HANDLE       ParseHandle;
    JPG_HANDLE       HDecHandle;
    JPG_STATE_E     State;
    HI_S32          CurrIndex;
    HI_U32          ThumbCnt;
    HI_U32          ReqIndex;
    HI_BOOL         bParsedFF;
    HI_BOOL         bNeedSend;
    HI_BOOL         bNeedCopy;
    HI_U32          ThumbEcsLen;
    HI_BOOL         bReqExif;
    HI_VOID*        pExifAddr;

    JPG_DECODER_FUNC     struHwDec;
    JPG_DECODER_FUNC     struSwDec;
    JPG_DECODER_FUNC     *pstruCurrentDec;
    JPG_DECTYPE_E   DecType;
    HI_U32          FileLen;

    HI_BOOL        bHDecErr;
}JPG_DECCTX_S;

#define JPG_PARSEBUF_LEN                (32<<10)
#define JPG_STREAM_PART                 (32<<10)

#define JPGTAG_FF                              0xFF
#define JPGTAG_SOI                            0xD8
#define JPGTAG_EOI                            0xD9
#define JPG_PARSED_ALL                    0x0000001F

#define JPG_GETCURPICINFO(tHandle, tNeedIdx, tpNeedPicInfo)\
do{\
    JPG_PICPARSEINFO_S* tpList = NULL;\
    HI_U32 tIdx;\
    JPGPARSE_GetImgInfo((tHandle), &tpList); \
    if (tpList)\
    {\
        if(tNeedIdx > 0)\
        {\
            for(tIdx = 0; tIdx < tNeedIdx; tIdx++)\
            {\
                tpList = tpList->pNext;\
            }\
        } \
    }\
    tpNeedPicInfo = tpList;\
}while(0)

#ifndef X5_JPEG
#define JPG_GETHDSTATE( tHDecHandle, DecType, tState ) \
do{	\
	HI_VOID *pTmpBuf;	\
	HI_U32   Len;	\
	HI_U32   HdState;	\
	if(JPG_DECTYPE_HW == DecType)\
	{\
	    JPGHDEC_Status((tHDecHandle), &pTmpBuf, &Len, &HdState);  \
	}\
	else\
	{\
        JPGSDEC_Status((tHDecHandle), &pTmpBuf, &Len, &HdState);  \
    }\
	(tState) = HdState; \
}while(0)
#endif
#define JPGFILE_MAX              (8<<20)
#define JPGFILE_MIN               (8<<10)

#define JPGDEC_MEMSIZE            (48<<10)
#define JPGPARSE_MEMSIZE        (128<<10)
#define JPGHDEC_MEMSIZE          (1<<10)
#define JPGEXIF_MEMSIZE           (64<<10)

JPGDEC_CTRL_S s_DecCtrlMem = {{0},{0},{0},{0},{0},{0}};


/*****************************************************************************/
/*****************************************************************************/
static HI_VOID  JPG_InitMem(HI_U32 PhysAddr, HI_VOID* pVirtAddr)
{
    HI_U32  Total[6] = {   JPGDEC_MEMSIZE,
		                        JPGPARSE_MEMSIZE,
                                      JPGHDEC_MEMSIZE,
                                      JPGEXIF_MEMSIZE  };
    HI_U32 i;
    JPG_MEM_S*   pMem = &s_DecCtrlMem.s_DecMem;
    HI_U32           PhysAddrOffset = PhysAddr;
    HI_U8*           pVirtAddrOffset = pVirtAddr;

    for( i = 0; i < 6; i++ )
    {
        pMem->PhysAddr = PhysAddrOffset;
        pMem->pVirtAddr = pVirtAddrOffset;
        pMem->Total       = Total[i];
        pMem->Offset     = 0;

        PhysAddrOffset += pMem->Total;
        pVirtAddrOffset += pMem->Total;
        if( i < 5 )
        {
            pMem ++;
        }
    }
}

#if 1
STATIC_FUNC HI_S32 JPGCheckJpegEOI(HI_VOID* pBuf, HI_U32 Len, HI_BOOL bParsedFF, HI_S32* pOffset)
{
    HI_U8*   pu8Char;
    HI_U8*   pu8CharNxt;
    HI_U8*   ExtAddr;

    JPG_ASSERT_NULLPTR(pBuf);
    JPG_ASSERT_NULLPTR(pOffset);

    pu8Char      = (HI_U8*)pBuf;
    pu8CharNxt = (HI_U8*)pBuf + 1;
    ExtAddr       = (HI_U8*)pBuf + Len;

    if((HI_TRUE == bParsedFF) && (JPGTAG_EOI == *pu8Char))
    {
        *pOffset = -1;
        return HI_SUCCESS;
    }

    while(pu8CharNxt < ExtAddr)
    {
        if(JPGTAG_EOI == *pu8CharNxt)
        {
            if (JPGTAG_FF == *(pu8CharNxt - 1))
            {
                *pOffset = (pu8CharNxt - 1) - (HI_U8*)pBuf;
                //*pOffset += 2;
                return HI_SUCCESS;
            }
        }
        pu8CharNxt++;
    }

    *pOffset = (pu8CharNxt - 1) - (HI_U8*)pBuf;
    return HI_FAILURE;
}

STATIC_FUNC JPG_ENCFMT_E JPGGetFormat(const JPG_PICPARSEINFO_S* image)
{
    if(1 == image->ComponentInScan)
    {
        return JPGHAL_ENCFMT_400;
    }

    if(3 != image->ComponentInScan)
    {
        return JPGHAL_ENCFMT_BUTT;
    }

    if((image->ComponentInfo[1].HoriSampFactor != image->ComponentInfo[2].HoriSampFactor)
    || (image->ComponentInfo[1].VertSampFactor != image->ComponentInfo[2].VertSampFactor))
    {
        return JPGHAL_ENCFMT_BUTT;
    }

    if((image->ComponentInfo[0].HoriSampFactor >> 1) == image->ComponentInfo[1].HoriSampFactor)
    {
        if((image->ComponentInfo[0].VertSampFactor >> 1) == image->ComponentInfo[1].VertSampFactor)
        {
            return JPGHAL_ENCFMT_420;
        }
        else if(image->ComponentInfo[0].VertSampFactor  == image->ComponentInfo[1].VertSampFactor)
        {
            return JPGHAL_ENCFMT_422_21;
        }
    }
    else if((image->ComponentInfo[0].HoriSampFactor  == image->ComponentInfo[1].HoriSampFactor))
    {
        if((image->ComponentInfo[0].VertSampFactor >> 1) == image->ComponentInfo[1].VertSampFactor)
        {
            return JPGHAL_ENCFMT_422_12;
        }
        if(image->ComponentInfo[0].VertSampFactor  == image->ComponentInfo[1].VertSampFactor)
        {
            return JPGHAL_ENCFMT_444;
        }
    }

    return JPGHAL_ENCFMT_BUTT;
}

STATIC_FUNC HI_VOID JPGConvert2PicInfo(const JPG_PICPARSEINFO_S* pParseInfo, JPG_PICINFO_S *pPicInfo)
{
    pPicInfo->Profile = pParseInfo->Profile;
    pPicInfo->Width = pParseInfo->Width;
    pPicInfo->Height = pParseInfo->Height;
    pPicInfo->SamplePrecision = pParseInfo->Precise;
    pPicInfo->ComponentNum = pParseInfo->ComponentNum;
    pPicInfo->EncodeFormat = (JPG_SOURCEFMT_E)JPGGetFormat(pParseInfo);
#ifndef X5_JPEG
    if(pPicInfo->EncodeFormat == JPG_SOURCE_COLOR_FMT_YCBCR444)
		pPicInfo->EncodeFormat = JPG_SOURCE_COLOR_FMT_YCBCR422BHP;
    if(pPicInfo->EncodeFormat == JPG_SOURCE_COLOR_FMT_YCBCR422BVP)
		pPicInfo->EncodeFormat = JPG_SOURCE_COLOR_FMT_YCBCR420;

    if(pPicInfo->EncodeFormat == JPG_SOURCE_COLOR_FMT_YCBCR400)
		pPicInfo->EncodeFormat = JPG_SOURCE_COLOR_FMT_YCBCR420;
#endif

    return;
}


STATIC_FUNC HI_S32 JPGCheckPicAvail(JPG_STATE_E ParseState, HI_U32 CurIdx, HI_U32 ThumbCnt,
                                           HI_U32 ReqIndex)
{
    HI_S32 Ret = HI_FAILURE;

    assert((CurIdx + 1) != 0);

    if(ReqIndex > 0)
    {
        if(ThumbCnt >= ReqIndex)
        {
            Ret = HI_SUCCESS;
        }
        else if(JPG_STATE_THUMBPARSED == ParseState)
        {
            Ret = HI_ERR_JPG_THUMB_NOEXIST;
        }
        else
        {
            Ret = HI_FAILURE;
        }
    }
    else
    {
        Ret = ((0 == CurIdx) && ((ParseState == JPG_STATE_PARSED)||(ParseState >= JPG_STATE_DECODING))) ?
              HI_SUCCESS : HI_FAILURE;

    }

    return Ret;
}

STATIC_FUNC HI_S32 JPGConvert2DecInfo(const JPG_PICPARSEINFO_S* pParseInfo, const JPG_SURFACE_S* pSurface,
                                  JPGDEC_DECODEATTR_S* pDecodeAttr)
{
    HI_U32 i;

    pDecodeAttr->Height = pParseInfo->Height;
    pDecodeAttr->Width = pParseInfo->Width;
    pDecodeAttr->EncFmt = JPGGetFormat(pParseInfo);
    pDecodeAttr->pOutSurface = (JPG_SURFACE_S*)pSurface;

    for(i = 0; i < 4; i++)  /*pParseInfo->ComponentInScan*/
    {
        pDecodeAttr->pQuanTbl[i]   = pParseInfo->pQuantTbl[i];
        pDecodeAttr->pDcHuffTbl[i] = pParseInfo->pDcHuffTbl[i];
        pDecodeAttr->pAcHuffTbl[i] = pParseInfo->pAcHuffTbl[i];
    }

    return HI_SUCCESS;
}

STATIC_FUNC HI_S32 JPGCopyParseBuf2HDBuf(const JPG_CYCLEBUF_S* pParseBuf,
         JPG_HANDLE  HDecHandle,JPG_DECTYPE_E DecType ,HI_BOOL bEOI, HI_U32 EoiOffset)
{
    JPGBUF_DATA_S  stData;
    JPGDEC_WRITESTREAM_S stWriteStrm;
    HI_U8  EOIBuf[2] = {0xFF, 0xD9};
    HI_U8  SOIBuf[2] = {0xFF, 0xD8};

    JPGBUF_DATA_S  stDataTmp;
    HI_U32         CurOffset = EoiOffset;
    HI_U32         HeadLen;
    HI_VOID (*JPGDEC_SendStream)(JPG_HANDLE Handle,
                                 JPGDEC_WRITESTREAM_S* pStreamInfo);

    JPGDEC_SendStream = JPGHDEC_SendStream;
    (HI_VOID)JPGBUF_GetDataBtwWhRh(pParseBuf, &stData);

    if(JPG_DECTYPE_SW == DecType)
    {
        VCOS_memcpy(&stDataTmp, &stData, sizeof(JPGBUF_DATA_S));
        (HI_VOID)JPGBUF_GetDataBtwWhRt(pParseBuf, &stData);

        HeadLen = (stData.u32Len[0] + stData.u32Len[1])
                - (stDataTmp.u32Len[0] + stDataTmp.u32Len[1]);

        assert((HI_S32)HeadLen > 0);
        CurOffset += HeadLen;

        stWriteStrm.EndFlag = HI_FALSE;
        stWriteStrm.NeedCopyFlag = HI_TRUE;
        stWriteStrm.pStreamAddr   = SOIBuf;
        stWriteStrm.StreamLen = 2;
        //BM_TRACE("sendstream addr1 0x%x len 0x%x\n",stWriteStrm.pStreamAddr,stWriteStrm.StreamLen);
        JPGDEC_SendStream(HDecHandle, &stWriteStrm);
    }

    assert(stData.u32Len[0] + stData.u32Len[1] >= CurOffset);

    stWriteStrm.NeedCopyFlag = HI_TRUE;
    stWriteStrm.EndFlag = HI_FALSE;

    if(CurOffset <= stData.u32Len[0])
    {
        stWriteStrm.pStreamAddr  = stData.pAddr[0];
        stWriteStrm.StreamLen = CurOffset;
        JPGDEC_SendStream(HDecHandle, &stWriteStrm);
    }
    else
    {
        stWriteStrm.pStreamAddr  = stData.pAddr[0];
        stWriteStrm.StreamLen = stData.u32Len[0];
       // BM_TRACE("sendstream addr3 0x%x len 0x%x\n",stWriteStrm.pStreamAddr,stWriteStrm.StreamLen);
        JPGDEC_SendStream(HDecHandle, &stWriteStrm);

        stWriteStrm.pStreamAddr   = stData.pAddr[1];
        stWriteStrm.StreamLen = CurOffset - stData.u32Len[0];
        //BM_TRACE("sendstream addr4 0x%x len 0x%x\n",stWriteStrm.pStreamAddr,stWriteStrm.StreamLen);
        JPGDEC_SendStream(HDecHandle, &stWriteStrm);
    }

    if (HI_TRUE == bEOI)
    {
        stWriteStrm.EndFlag = HI_TRUE;
        stWriteStrm.pStreamAddr   = EOIBuf;
        stWriteStrm.StreamLen = 2;
        //BM_TRACE("sendstream addr5 0x%x len 0x%x\n",stWriteStrm.pStreamAddr,stWriteStrm.StreamLen);
        JPGDEC_SendStream(HDecHandle, &stWriteStrm);
    }

    return HI_SUCCESS;
}

STATIC_FUNC  HI_S32 JPGPreCheck(JPG_PICPARSEINFO_S*  pCurPicInfo, JPGDEC_CHECKINFO_S*  pCheckInfo)
{
    HI_U32 QuantTblNum  = 0;
    HI_U32 DcHuffTblNum = 0;
    HI_U32 AcHuffTblNum = 0;
    HI_U32 i;

    if ((NULL == pCurPicInfo) || (NULL == pCheckInfo))
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    for(i = 0; i < 4; i++)
    {
        if(NULL != pCurPicInfo->pQuantTbl[i])
        {
            QuantTblNum++;
        }
        if(NULL != pCurPicInfo->pDcHuffTbl[i])
        {
            DcHuffTblNum++;
        }
        if(NULL != pCurPicInfo->pAcHuffTbl[i])
        {
            AcHuffTblNum++;
        }
    }

    if((NULL == pCurPicInfo->pQuantTbl[0])
     ||(NULL == pCurPicInfo->pDcHuffTbl[0])
     ||((NULL == pCurPicInfo->pAcHuffTbl[0])
     && (JPG_PICTYPE_BASELINE == pCurPicInfo->Profile)))
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    for(i = 0; i < 4; i++)
    {
        if((pCurPicInfo->ComponentInfo[i].QuantTblNo >= QuantTblNum)
	 ||(pCurPicInfo->ComponentInfo[i].DcTblNo >= DcHuffTblNum))
        {
            return HI_ERR_JPG_DEC_FAIL;
        }
    }

    pCheckInfo->QuantTblNum  = QuantTblNum;
    pCheckInfo->DcHuffTblNum = DcHuffTblNum;
    pCheckInfo->AcHuffTblNum = AcHuffTblNum;

    pCheckInfo->Width        = pCurPicInfo->Width;
    pCheckInfo->Height       = pCurPicInfo->Height;
    pCheckInfo->Precise      = pCurPicInfo->Precise;
    pCheckInfo->Profile       = pCurPicInfo->Profile;

    pCheckInfo->EncFmt   = JPGGetFormat(pCurPicInfo);
    pCheckInfo->ComponentNum = pCurPicInfo->ComponentNum;

    return HI_SUCCESS;
}

#endif

/*****************************************************************************/
/*                          JPG FirmWare                           */
/*****************************************************************************/

/******************************************************************************
* Function:      JPG_CreateDecoder
* Description:
* Input:          ImgType
                        u32FileLen
* Output:        pHandle JPG
* Return:        HI_SUCCESS:
*                HI_ERR_JPG_DEC_BUSY:
*                HI_ERR_JPG_DEV_NOOPEN:
*                HI_ERR_JPG_NO_MEM:
*                HI_FAILURE:
* Others:
******************************************************************************/
HI_S32 JPG_CreateDecoder(JPG_HANDLE *pHandle, JPG_IMGTYPE_E ImgType, HI_U32 ImgLen)
{
    HI_S32          s32Ret;
    JPG_DECCTX_S*   pstCtx;
    JPG_HANDLE       JpgHandle;
//    HI_VOID*           pVirtAddr = HI_NULL;
    HI_U32               DecSize;
//    HI_U32                PhysAddr = 0;

    JPG_CHECK_NULLPTR(pHandle);
    JPG_CHECK_ENUM(ImgType, JPG_IMGTYPE_BUTT);


#if 1//ndef X5_JPEG

    s32Ret = JPGDRV_GetDevice();

    if(HI_SUCCESS != s32Ret)
    {
        s32Ret = (HI_ERR_JPG_DEC_BUSY == s32Ret) ? s32Ret : HI_FAILURE;
        return s32Ret;
    }
#endif

	//JPG_Handle_Clear();


#if 1
    DecSize = JPGDEC_MEMSIZE
		  + JPGPARSE_MEMSIZE
		  + JPGHDEC_MEMSIZE
		  + JPGEXIF_MEMSIZE ;
#endif

    pstCtx = JPGFMW_Alloc(&s_DecCtrlMem.s_DecMem, DecSize);
    if(NULL == pstCtx)
    {
        HIGO_ERROR(HI_ERR_JPG_NO_MEM);
        s32Ret = HI_ERR_JPG_NO_MEM;
        goto  LABEL0;
    }

    JPG_InitMem(s_DecCtrlMem.s_DecMem.PhysAddr, s_DecCtrlMem.s_DecMem.pVirtAddr);
#if 1
    pstCtx = (JPG_DECCTX_S*)JPGFMW_MemGet(&s_DecCtrlMem.s_DecMem,
		                               (sizeof(JPG_DECCTX_S) + JPG_PARSEBUF_LEN));
#endif
    if(NULL == pstCtx)
    {
        HIGO_ERROR(HI_ERR_JPG_NO_MEM);
        s32Ret = HI_ERR_JPG_NO_MEM;
        goto  LABEL0;
    }
    if(HI_SUCCESS != (s32Ret = JPG_Handle_Alloc(&JpgHandle, pstCtx)))
    {
        HIGO_ERROR(HI_ERR_JPG_NO_MEM);
        s32Ret = HI_ERR_JPG_NO_MEM;
        goto LABEL1;
    }

    s32Ret = JPGPARSE_CreateInstance(&pstCtx->ParseHandle, ImgType);
    if(HI_SUCCESS != s32Ret)
    {
        HIGO_ERROR(s32Ret);
        goto LABEL2;
    }


    (HI_VOID)JPGBUF_Init(&pstCtx->ParseBuf , pstCtx + 1, JPG_PARSEBUF_LEN, sizeof(HI_U8));

    pstCtx->State = JPG_STATE_STOP;
    pstCtx->CurrIndex = -1;
    pstCtx->ReqIndex = 0;
    pstCtx->ThumbCnt = 0;
    pstCtx->bParsedFF = HI_FALSE;
    pstCtx->bNeedSend = HI_TRUE;
    pstCtx->bNeedCopy = HI_FALSE;
    pstCtx->ThumbEcsLen = 0;

    /* AI7D02624 */
    pstCtx->bReqExif = HI_FALSE;
    pstCtx->pExifAddr = NULL;

    JPGDEC_InitHW(&pstCtx->struHwDec);

    pstCtx->pstruCurrentDec = &pstCtx->struHwDec;
    pstCtx->DecType = JPG_DECTYPE_HW;
    pstCtx->FileLen = ImgLen;
    pstCtx->bHDecErr = HI_FALSE;
    pstCtx->HDecHandle = 0;

    *pHandle = JpgHandle;

    return HI_SUCCESS;

    /*LABEL2:*/
    LABEL2:
        JPG_Handle_Free(JpgHandle);

    LABEL1:
        //VCOS_free(pstCtx);
        JPGFMW_Free(&s_DecCtrlMem.s_DecMem);
    /*LABEL0: */
     LABEL0:
#if  1//ndef X5_JPEG
        (HI_VOID)JPGDRV_ReleaseDevice();
#endif
        return s32Ret;
}

/******************************************************************************
* Function:      JPG_DestroyDecoder
* Description:
* Input:
* Output:         JPG
* Return:        HI_SUCCESS
* Others:
******************************************************************************/
HI_S32  JPG_DestroyDecoder(JPG_HANDLE Handle)
{
    JPG_DECCTX_S*  pstCtx;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    if(NULL == pstCtx)
    {
        /* AI7D02557 Modify */
        return HI_SUCCESS;
    }

    if(pstCtx->HDecHandle != 0)
    {
        pstCtx->pstruCurrentDec->JPGDEC_DestroyInstance(pstCtx->HDecHandle);
	 pstCtx->HDecHandle = 0;
    }

    JPGPARSE_DestroyInstance(pstCtx->ParseHandle);

    //VCOS_free(pstCtx);
    JPGFMW_Free(&s_DecCtrlMem.s_DecMem);

    JPG_Handle_Free(Handle);

	#if 1 //ndef X5_JPEG
    (HI_VOID)JPGDRV_ReleaseDevice();
	#endif

    return HI_SUCCESS;
}
#ifndef HIGO_CODE_CUT
/******************************************************************************
* Function:      JPG_Probe
* Description:
* Input:        Handle
*                  pBuf
*                  BufLen
* Output:
* Return:        HI_SUCCESS
*                    HI_ERR_JPG_WANT_STREAM
*                    HI_FAILURE
* Others:
******************************************************************************/
HI_S32  JPG_Probe(JPG_HANDLE Handle, HI_VOID* pBuf, HI_U32 BufLen)
{
    HI_U8* pu8Char;

    JPG_CHECK_NULLPTR(pBuf);
    pu8Char = (HI_U8*)pBuf;
    if( BufLen < 2 )
    {
        return HI_ERR_JPG_INVALID_PARA;
    }

    while((HI_U32)(pu8Char -  (HI_U8*)pBuf) < (BufLen - 1))
    {
        if((JPGTAG_FF == *pu8Char) && (JPGTAG_SOI == *(pu8Char + 1)))
        {
            return HI_SUCCESS;
        }
        pu8Char++;
    }

    return HI_FAILURE;
}
#endif
/******************************************************************************
* Function:      JPG_Decode
* Description:
* Input:         Handle
*                pSurface
*                Index
* Output:
* Return:        HI_SUCCESS
*                HI_ERR_JPG_INVALID_HANDLE
*                HI_ERR_JPG_WANT_STREAM
*                HI_ERR_JPG_DEC_FAIL
*                HI_FAILURE
* Others:
******************************************************************************/
HI_S32  JPG_Decode(JPG_HANDLE Handle, const JPG_SURFACE_S *pSurface, HI_U32 Index)
{
    JPG_DECCTX_S*   pstCtx;
    JPGDEC_DECODEATTR_S stDecAttr;
    JPG_PICPARSEINFO_S*  pCurPicInfo;

    JPGDEC_CHECKINFO_S  CheckInfo;
#if 0
    HI_U32 QuantTblNum  = 0;
    HI_U32 DcHuffTblNum = 0;
    HI_U32 AcHuffTblNum = 0;
    HI_U32 i;
#endif
    JPGBUF_DATA_S stData;
    HI_S32  s32Ret;
    HI_BOOL bEOI = HI_FALSE;
    HI_U32  Offset;
    HI_S32  Avail = HI_FAILURE;
    HI_U32  ImgLen;


    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);
    JPG_CHECK_NULLPTR(pSurface);

    assert((JPG_STATE_PARTPARSED <= pstCtx->State) &&
           (JPG_STATE_PARSED >= pstCtx->State));

    if(0 == Index)
    {
        assert(0 == pstCtx->CurrIndex);
    }

    if( pstCtx->CurrIndex == -1)
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    Avail = JPGCheckPicAvail(pstCtx->State, (HI_U32)pstCtx->CurrIndex,
                                 pstCtx->ThumbCnt, Index);
    if(Avail == HI_FAILURE)
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    pstCtx->ThumbEcsLen = 0;

    JPG_GETCURPICINFO(pstCtx->ParseHandle, Index, pCurPicInfo);

    s32Ret = JPGPreCheck(pCurPicInfo, &CheckInfo);
    if(HI_ERR_JPG_DEC_FAIL == s32Ret)
    {
       pstCtx->State = JPG_STATE_PARSEERR;
    	return HI_ERR_JPG_DEC_FAIL;
    }

#ifndef X5_JPEG
    if(HI_SUCCESS == JPGHDEC_Check(INVALID_HANDLE, &CheckInfo)
	&& ((pSurface->SurfaceInfo.MbSurface.YWidth  ==  pCurPicInfo->Width)
       &&(pSurface->SurfaceInfo.MbSurface.YHeight ==  pCurPicInfo->Height)))
#else
    if(HI_SUCCESS == JPGHDEC_Check(INVALID_HANDLE, &CheckInfo))
#endif
    {
        pstCtx->pstruCurrentDec = &pstCtx->struHwDec;
        pstCtx->DecType = JPG_DECTYPE_HW;
    }
    else
    {
        pstCtx->State = JPG_STATE_PARSEERR;
        //HI_TRACE(HI_LOG_LEVEL_WARNING, JPEG, "Decoder not supported!\n");
        return HI_ERR_JPG_NOSUPPORT_FMT;
    }

    if(pstCtx->bHDecErr == HI_TRUE)
    {
        pstCtx->DecType = JPG_DECTYPE_SW;
        pstCtx->pstruCurrentDec = &pstCtx->struSwDec;
    }

#if 1   /* for test */
    pstCtx->DecType = JPG_DECTYPE_HW;
    pstCtx->pstruCurrentDec = &pstCtx->struHwDec;

	if(pstCtx->DecType == JPG_DECTYPE_SW)
        BM_TRACE("Soft dec \n");
    else
        BM_TRACE("Hard dec \n");
#endif
    ImgLen =  pstCtx->FileLen;
    //BM_TRACE("@@@ file len = %d\n", ImgLen);
    if((JPG_DECTYPE_SW == pstCtx->DecType) && (0 == ImgLen))
    {
         JPG_ENCFMT_E  EncFmt;
	  const HI_U32  FactorTabx2[7] = {2, 0, 0, 3, 4, 4, 6};

	  EncFmt = JPGGetFormat(pCurPicInfo);
	  ImgLen = (pCurPicInfo->Width * pCurPicInfo->Height * FactorTabx2[EncFmt]) >> 1;
	  ImgLen >>= 2;

	  ImgLen = (ImgLen > JPGFILE_MAX) ?  JPGFILE_MAX :
	  	          ((ImgLen < JPGFILE_MIN) ? JPGFILE_MIN : ImgLen);
    }

    if(HI_SUCCESS != (s32Ret = pstCtx->pstruCurrentDec->JPGDEC_CreateInstance(&pstCtx->HDecHandle, ImgLen)))
    {
        return s32Ret;
    }

        pstCtx->pstruCurrentDec->JPGDEC_FlushBuf(pstCtx->HDecHandle);

        pstCtx->pstruCurrentDec->JPGDEC_Reset(pstCtx->HDecHandle);

     s32Ret = JPGConvert2DecInfo(pCurPicInfo, pSurface, &stDecAttr);

    (HI_VOID)JPGBUF_GetDataBtwWhRh(&pstCtx->ParseBuf, &stData);

    if(0 != stData.u32Len[0])
    {
        s32Ret = JPGPARSE_EndCheck(DEFAULT_HANDLE,  &pstCtx->ParseBuf,
                                   &Offset, &pstCtx->bParsedFF);
        if(HI_ERR_JPG_PARSE_FAIL == s32Ret)
        {
            /* AI7D02581 */
            pstCtx->State = JPG_STATE_DECODEERR;
            //HI_TRACE(HI_LOG_LEVEL_WARNING, JPEG, "Parse fail before Decoding!\n");
            return HI_ERR_JPG_DEC_FAIL;
        }

        bEOI = (HI_SUCCESS == s32Ret) ? HI_TRUE : HI_FALSE;

        if (HI_TRUE == bEOI)
        {
            pstCtx->bNeedSend = HI_FALSE;
        }


        (HI_VOID)JPGCopyParseBuf2HDBuf(&pstCtx->ParseBuf, pstCtx->HDecHandle, pstCtx->DecType,bEOI, Offset);
        JPGBUF_SetRdHead(&pstCtx->ParseBuf, Offset);

        if ((HI_TRUE == pstCtx->bParsedFF) && (HI_FALSE == pstCtx->bNeedCopy))
        {
            HI_U8 FFData = 0xFF;
            JPGDEC_WRITESTREAM_S stWriteStrm;
            stWriteStrm.pStreamAddr   = &FFData;
            stWriteStrm.StreamLen = 1;
            stWriteStrm.EndFlag = HI_FALSE;
            stWriteStrm.NeedCopyFlag = HI_TRUE;
            pstCtx->pstruCurrentDec->JPGDEC_SendStream(pstCtx->HDecHandle, &stWriteStrm);
            pstCtx->bParsedFF = (1 == stWriteStrm.CopyLen) ? HI_FALSE : pstCtx->bParsedFF;
        }
    }

    if ((0 == stData.u32Len[0]) || (HI_FALSE == bEOI))
    {
        pstCtx->bNeedSend = HI_TRUE;
    }

    JPGBUF_StepRdTail(&pstCtx->ParseBuf);
    pstCtx->pstruCurrentDec->JPGDEC_SetDecodeInfo(pstCtx->HDecHandle, &stDecAttr);

    pstCtx->pstruCurrentDec->JPGDEC_Start(pstCtx->HDecHandle);

#ifndef X5_JPEG
    JPG_GETHDSTATE( pstCtx->HDecHandle, pstCtx->DecType, pstCtx->State );
#else
    pstCtx->State = JPG_STATE_DECODING;
#endif
    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPG_GetPrimaryInfo
* Description:
* Input:         Handle
* Output:        pImageInfo
* Return:        HI_SUCCESS
*                HI_ERR_JPG_INVALID_HANDLE
*                HI_ERR_JPG_WANT_STREAM
*                HI_ERR_JPG_PARSE_FAIL
*                HI_FAILURE
* Others:
******************************************************************************/
HI_S32  JPG_GetPrimaryInfo(JPG_HANDLE Handle, JPG_PRIMARYINFO_S **pPrimaryInfo)
{
    JPG_PICINFO_S    stPicInfo;
    JPG_DECCTX_S*    pstCtx;
    HI_S32           s32Ret;

    JPG_PICPARSEINFO_S* pPicInfoHead = NULL;
    JPG_PICPARSEINFO_S* pList;
    JPG_PRIMARYINFO_S*  pstPrimInfo;
    JPG_PICINFO_S*          pPicInfoAddr;
    HI_U32                        i;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);

    JPG_CHECK_NULLPTR(pPrimaryInfo);

    s32Ret = JPG_GetPicInfo(Handle, &stPicInfo, 0);
    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    JPGPARSE_GetImgInfo(pstCtx->ParseHandle, &pPicInfoHead);

    pList = pPicInfoHead;
    for(i = 0; NULL != pList; i++)
    {
        pList = pList->pNext;
    }


    //pstPrimInfo = (JPG_PRIMARYINFO_S*)VCOS_malloc(sizeof(JPG_PRIMARYINFO_S)
    //                                            + i * sizeof(JPG_PICINFO_S));
    pstPrimInfo = (JPG_PRIMARYINFO_S*)JPGFMW_MemGet(&s_DecCtrlMem.s_DecMem, (sizeof(JPG_PRIMARYINFO_S)
                                                                                         + i * sizeof(JPG_PICINFO_S)));
    if(NULL == pstPrimInfo)
    {
        return HI_FAILURE;
    }

    pPicInfoAddr = (JPG_PICINFO_S*)((HI_U8*)pstPrimInfo + sizeof(JPG_PRIMARYINFO_S));
    pList = pPicInfoHead;

    pstPrimInfo->pPicInfo = pPicInfoAddr;
    for(i = 0; NULL != pList; i++)
    {
        JPGConvert2PicInfo(pList, pPicInfoAddr);
        pList = pList->pNext;
        if(NULL != pList)
        {
            pPicInfoAddr++;
        }
    }

    pstPrimInfo->Count = i;
    *pPrimaryInfo = pstPrimInfo;

    return HI_SUCCESS;

}

/******************************************************************************
* Function:      JPG_ReleasePrimaryInfo
* Description:
* Input:         Handle
* Output:        pImageInfo
* Return:        HI_SUCCESS
*                HI_ERR_JPG_INVALID_HANDLE
* Others:

******************************************************************************/
HI_S32  JPG_ReleasePrimaryInfo(JPG_HANDLE Handle, JPG_PRIMARYINFO_S *pImageInfo)
{
    JPG_CHECK_NULLPTR(pImageInfo);

    if((0 == pImageInfo->Count) || (NULL == pImageInfo->pPicInfo))
    {
        return HI_ERR_JPG_INVALID_PARA;
    }

    //VCOS_free(pImageInfo);
    JPGFMW_MemReset(&s_DecCtrlMem.s_DecMem, (sizeof(JPG_DECCTX_S) + JPG_PARSEBUF_LEN));
    #if 0
    if(s_DecCtrlMem.s_DecMem.Offset  + sizeof(JPG_PRIMARYINFO_S)
	>= s_DecCtrlMem.s_DecMem.Total)
    	{
           JPGFMW_MemReset(&s_DecCtrlMem.s_DecMem,
		   	s_DecCtrlMem.s_DecMem.Total - sizeof(JPG_PRIMARYINFO_S));
	}
    #endif

    return HI_SUCCESS;
}

static JPG_STATE_E JPG_TransformParseState(JPG_PARSESTATE_E enState)
{
    return (JPG_STATE_E)enState;
}

/******************************************************************************
* Function:      JPG_GetPicInfo
* Description:
* Input:         Handle
*                Index
* Output:        pPicInfo
* Return:        HI_SUCCESS
*                HI_ERR_JPG_INVALID_HANDLE
*                HI_ERR_JPG_WANT_STREAM
*                HI_ERR_JPG_PARSE_FAIL
*                HI_ERR_JPG_THUMB_NOEXIST
*                HI_FAILURE
* Others:

******************************************************************************/
HI_S32  JPG_GetPicInfo(JPG_HANDLE Handle, JPG_PICINFO_S *pPicInfo,
                             HI_U32 Index)
{
    JPG_DECCTX_S*   pstCtx;
    HI_S32          s32Ret;
    HI_S32          Avail = HI_FAILURE;

    JPG_PARSESTATE_S stParseState;
    JPG_PICPARSEINFO_S* pCurPicInfo;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);


   // BM_TRACE("5$$$$$$$$$$$JPG_GetPicInfo handle:%d pstCtx:0x%x ParseBuf:0x%x base:0x%x, len:0x%x\n", Handle, pstCtx, &pstCtx->ParseBuf, pstCtx->ParseBuf.pBase, pstCtx->ParseBuf.u32BufLen);

    JPG_CHECK_NULLPTR(pPicInfo);


    if(pstCtx->CurrIndex >= 0)
    {
        Avail = JPGCheckPicAvail(pstCtx->State, (HI_U32)pstCtx->CurrIndex,
                                 pstCtx->ThumbCnt, Index);
    }

    if(HI_SUCCESS == Avail)
    {
        JPG_GETCURPICINFO(pstCtx->ParseHandle, Index, pCurPicInfo);

        if (NULL == pCurPicInfo)
        {
            return HI_ERR_JPG_PARSE_FAIL;
        }

        /*AI7D02581*/
        if(JPG_PARSED_ALL  != (pCurPicInfo->SyntaxState & JPG_PARSED_ALL))
        {
            return HI_ERR_JPG_PARSE_FAIL;
        }

        JPGConvert2PicInfo(pCurPicInfo, pPicInfo);
        return HI_SUCCESS;
    }

    if(HI_ERR_JPG_THUMB_NOEXIST == Avail)
    {
        return HI_ERR_JPG_THUMB_NOEXIST;
    }

    pstCtx->ReqIndex = Index;
    stParseState.ThumbEcsLen = pstCtx->ThumbEcsLen;
    pstCtx->ThumbEcsLen = 0;
    pstCtx->State = JPG_STATE_PARSING;  // added
    s32Ret = JPGPARSE_Parse(pstCtx->ParseHandle, &pstCtx->ParseBuf,
                            Index, pstCtx->bReqExif, &stParseState);

    pstCtx->State = JPG_TransformParseState(stParseState.State);

    pstCtx->CurrIndex = stParseState.Index;
    pstCtx->ThumbCnt = stParseState.ThumbCnt;

    if(HI_SUCCESS == s32Ret)
    {
        Avail = JPGCheckPicAvail(pstCtx->State, (HI_U32)pstCtx->CurrIndex,
                                 pstCtx->ThumbCnt, Index);
        assert(HI_SUCCESS == Avail);
       JPG_GETCURPICINFO(pstCtx->ParseHandle, Index, pCurPicInfo);


       if((HI_NULL== pCurPicInfo) || (JPG_PARSED_ALL != (pCurPicInfo->SyntaxState & JPG_PARSED_ALL)))
        {
            return HI_ERR_JPG_PARSE_FAIL;
        }


       JPGConvert2PicInfo(pCurPicInfo, pPicInfo);
    }

    return s32Ret;
}

/******************************************************************************
* Function:      JPG_GetStatus
* Description:
* Input:         Handle
* Output:        pState
*                pIndex
* Return:        HI_SUCCESS
*                HI_ERR_JPG_PTR_NULL
*                HI_ERR_JPG_INVALID_HANDLE
* Others:         (GetStatus)
******************************************************************************/
HI_S32  JPG_GetStatus(JPG_HANDLE Handle, JPG_STATE_E *pState, HI_U32 *pIndex)
{
    JPG_DECCTX_S*     pstCtx;


    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);
    JPG_CHECK_NULLPTR(pState);
    JPG_CHECK_NULLPTR(pIndex);

    *pIndex = (pstCtx->CurrIndex >= 0) ? pstCtx->CurrIndex : 0;

    if((JPG_STATE_PARTPARSED == pstCtx->State) ||
       (JPG_STATE_THUMBPARSED == pstCtx->State))
    {
        *pIndex = pstCtx->ThumbCnt;
    }
    *pState = pstCtx->State;

     if( (pstCtx->State  >= JPG_STATE_DECODED) &&  (0 != pstCtx->HDecHandle))
    {
        pstCtx->pstruCurrentDec->JPGDEC_DestroyInstance(pstCtx->HDecHandle);
	    pstCtx->HDecHandle = 0;
    }

    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPG_SendStream
* Description:
* Input:         Handle
*                pWriteInfo
* Output:
* Return:        HI_SUCCESS
*                HI_ERR_JPG_PTR_NULL
*                HI_ERR_JPG_INVALID_PARA
*                HI_ERR_JPG_INVALID_HANDLE
* Others:
******************************************************************************/

HI_S32  JPG_SendStream(HI_U32 Handle, JPGDEC_WRITESTREAM_S *pWriteInfo)
{
    JPG_DECCTX_S*     pstCtx;
    HI_U32  FreeLen;
    HI_U32  MinLen;
    HI_S32 Offset;
    HI_S32 s32Ret;
    HI_BOOL bEOI;
    JPGDEC_WRITESTREAM_S HdStreamInfo;
    JPG_PARSESTATE_S  stParseState;
    HI_S32  Avail = HI_FAILURE;
    HI_U8   EOIBuf[2] = {0xFF, 0xD9};

    HI_VOID (*JPGDEC_SendStream)(JPG_HANDLE Handle,
                                 JPGDEC_WRITESTREAM_S* pStreamInfo);

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);
    JPG_CHECK_NULLPTR(pWriteInfo);

    JPGDEC_SendStream = pstCtx->pstruCurrentDec->JPGDEC_SendStream;
    if(((0 == pWriteInfo->StreamLen) && (HI_FALSE == pWriteInfo->EndFlag))
	 ||((HI_TRUE == pWriteInfo->NeedCopyFlag) && (NULL == pWriteInfo->pStreamAddr)))
    {
        HIGO_ERROR(HI_ERR_JPG_INVALID_PARA);
        return HI_ERR_JPG_INVALID_PARA;
    }
    pstCtx->bNeedCopy = pWriteInfo->NeedCopyFlag;


    switch(pstCtx->State)
    {
        case JPG_STATE_STOP:
        case JPG_STATE_PARSING:
        case JPG_STATE_PARTPARSED:
        case JPG_STATE_THUMBPARSED:
        case JPG_STATE_PARSED:
        case JPG_STATE_DECODED:
            if(pstCtx->CurrIndex >= 0)
            {
                Avail = JPGCheckPicAvail(pstCtx->State,    pstCtx->CurrIndex,
                                         pstCtx->ThumbCnt, pstCtx->ReqIndex);
            }
            if(HI_FAILURE != Avail)
            {
                pWriteInfo->CopyLen = 0;
                return HI_SUCCESS;
            }
            FreeLen = JPGBUF_GetFreeLen(&pstCtx->ParseBuf);
            MinLen = (FreeLen <= pWriteInfo->StreamLen) ? FreeLen : pWriteInfo->StreamLen;
            if(HI_TRUE == pWriteInfo->NeedCopyFlag)
            {

                (HI_VOID)JPGBUF_Write(&pstCtx->ParseBuf, pWriteInfo->pStreamAddr, MinLen);
                pWriteInfo->CopyLen = MinLen;
            }
            else
            {

                JPGBUF_SetWrHead(&pstCtx->ParseBuf, pWriteInfo->StreamLen);
                pWriteInfo->CopyLen = pWriteInfo->StreamLen;
            }

            if(pstCtx->CurrIndex >= 0)
            {
                stParseState.ThumbEcsLen = pstCtx->ThumbEcsLen;
                pstCtx->ThumbEcsLen = 0;
                if((JPG_STATE_PARSEERR == pstCtx->State) && (0 == pstCtx->ReqIndex))
                {
                    return HI_ERR_JPG_PARSE_FAIL;
                }

                pstCtx->State = JPG_STATE_PARSING;
                s32Ret = JPGPARSE_Parse(pstCtx->ParseHandle, &pstCtx->ParseBuf,
                                        pstCtx->ReqIndex, pstCtx->bReqExif, &stParseState);
                pstCtx->State = JPG_TransformParseState(stParseState.State);

                pstCtx->CurrIndex  = stParseState.Index;
                pstCtx->ThumbCnt  = stParseState.ThumbCnt;

                if ((stParseState.State <= JPGPARSE_STATE_PARTPARSED)
                     && (HI_TRUE == pWriteInfo->EndFlag)
                     && (pWriteInfo->StreamLen == pWriteInfo->CopyLen))
                {
                    //HI_TRACE(HI_LOG_LEVEL_WARNING, JPEG, "File end, parse err!\n");
                    pstCtx->State = JPGPARSE_STATE_PARSEERR;
                }
            }

            return HI_SUCCESS;

        case JPG_STATE_DECODING:
            #ifndef X5_JPEG
            JPG_GETHDSTATE( pstCtx->HDecHandle, pstCtx->DecType, pstCtx->State );
            #endif
            pWriteInfo->CopyLen = 0;

            if (HI_FALSE == pstCtx->bNeedSend)
            {
                return HI_SUCCESS;
            }

            if ((0 == pstCtx->CurrIndex) && (0 == pstCtx->ReqIndex))
            {

                bEOI = pWriteInfo->EndFlag;
                Offset = pWriteInfo->StreamLen;
            }
            else
            {

                s32Ret = JPGCheckJpegEOI(pWriteInfo->pStreamAddr,
                          pWriteInfo->StreamLen, pstCtx->bParsedFF, &Offset);



                bEOI = (HI_SUCCESS == s32Ret) ? HI_TRUE : HI_FALSE;
            }

            if(Offset > 0)
            {
                if ((HI_TRUE == pstCtx->bParsedFF) && (HI_FALSE != pstCtx->bNeedCopy))
                {

                    HdStreamInfo.pStreamAddr = (HI_VOID*)EOIBuf;
                    HdStreamInfo.StreamLen = 1;
                    HdStreamInfo.EndFlag = HI_FALSE;
                    HdStreamInfo.NeedCopyFlag = HI_TRUE;

                    JPGDEC_SendStream(pstCtx->HDecHandle, &HdStreamInfo);
                    pstCtx->bParsedFF = (1 == HdStreamInfo.CopyLen) ? HI_FALSE : pstCtx->bParsedFF;
                }

                HdStreamInfo.pStreamAddr = pWriteInfo->pStreamAddr;
                HdStreamInfo.StreamLen = (HI_U32)Offset;
                HdStreamInfo.EndFlag = bEOI;
                HdStreamInfo.NeedCopyFlag = pWriteInfo->NeedCopyFlag;
                JPGDEC_SendStream(pstCtx->HDecHandle, &HdStreamInfo);
                pWriteInfo->CopyLen = HdStreamInfo.CopyLen;
		  if(0 == HdStreamInfo.CopyLen)
		  {
			return HI_SUCCESS;
		  }
                if (0 != pstCtx->CurrIndex)
                {
                    pstCtx->ThumbEcsLen += HdStreamInfo.CopyLen;
                }
            }
            else
            {

                if (HI_TRUE == pWriteInfo->NeedCopyFlag)
                {
                    HdStreamInfo.pStreamAddr = EOIBuf;
                }
                else
                {
                    HdStreamInfo.pStreamAddr = HI_NULL;
                }

                HdStreamInfo.StreamLen = 2;
                HdStreamInfo.EndFlag = HI_TRUE;
                HdStreamInfo.NeedCopyFlag = pWriteInfo->NeedCopyFlag;
                JPGDEC_SendStream(pstCtx->HDecHandle, &HdStreamInfo);
                pstCtx->bParsedFF = (2 == HdStreamInfo.CopyLen) ? HI_FALSE : pstCtx->bParsedFF;
                pWriteInfo->CopyLen = 0;
            }

            if ((HI_TRUE == bEOI) && (HI_TRUE == pWriteInfo->EndFlag))
            {
                pstCtx->bNeedSend = HI_FALSE;
            }
	     #ifndef X5_JPEG
            JPG_GETHDSTATE( pstCtx->HDecHandle, pstCtx->DecType, pstCtx->State );
            #endif

            return HI_SUCCESS;

        case JPG_STATE_PARSEERR:
        case JPG_STATE_DECODEERR:
            pWriteInfo->CopyLen = 0;
            return HI_SUCCESS;

        default:
            assert(0);
            break;
    }

    /* ���� HI_SUCCESS */
    pWriteInfo->CopyLen = 0;
    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPG_ResetDecoder
* Description:
* Input:         Handle
* Output:
* Return:        HI_SUCCESS
*                HI_ERR_JPG_INVALID_HANDLE
* Others:
******************************************************************************/
HI_S32  JPG_ResetDecoder(JPG_HANDLE Handle)
{
    JPG_DECCTX_S* pstCtx;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);

    if(pstCtx->HDecHandle != 0)
    {
        pstCtx->pstruCurrentDec->JPGDEC_Reset(pstCtx->HDecHandle);
        pstCtx->pstruCurrentDec->JPGDEC_FlushBuf(pstCtx->HDecHandle);
    }

    JPGPARSE_Reset(pstCtx->ParseHandle);
    JPGBUF_Reset(&pstCtx->ParseBuf);

    //JPGFMW_MemReset(&s_DecCtrlMem.s_DecMem, (sizeof(JPG_DECCTX_S) + JPG_PARSEBUF_LEN));

    pstCtx->State = JPG_STATE_STOP;
    pstCtx->CurrIndex = -1;
    pstCtx->ReqIndex = 0;
    pstCtx->ThumbCnt = 0;
    pstCtx->bParsedFF = HI_FALSE;
    pstCtx->bNeedSend = HI_TRUE;
    pstCtx->ThumbEcsLen = 0;

    pstCtx->bReqExif = HI_FALSE;
    pstCtx->pExifAddr = NULL;

    return HI_SUCCESS;
}

static JPG_STATE_E JPG_TransformHDState(JPG_HDSTATE_E enState)
{
    return (JPG_STATE_E)enState;
}

/******************************************************************************
* Function:      JPG_IsNeedStream
* Description:   BUF
* Input:         Handle
* Output:        pSize
* Return:        HI_SUCCESS
*                    HI_FAILURE
* Others:
******************************************************************************/

HI_S32  JPG_IsNeedStream(JPG_HANDLE Handle, HI_VOID** pAddr, HI_U32 *pSize)
{
    JPG_DECCTX_S*     pstCtx;
    HI_S32 s32Ret;
    JPG_HDSTATE_E  HdState;
    HI_S32   Avail = HI_FAILURE;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);

    //BM_TRACE("+++++++++before Handle %d pstCtx->State %d pstCtx->ReqIndex %d pstCtx->CurrIndex  %d pstCtx->ParseBuf 0x%x base 0x%x\n",Handle,pstCtx->State,pstCtx->ReqIndex ,pstCtx->CurrIndex,&pstCtx->ParseBuf,pstCtx->ParseBuf.pBase);

    if(JPG_STATE_STOP == pstCtx->State)
    {
        (HI_VOID)JPGBUF_GetFreeInfo(&pstCtx->ParseBuf, pAddr, pSize);
        if(0 == *pSize)
        {
            return HI_FAILURE;
        }

        return HI_SUCCESS;
    }


    if (((JPG_STATE_PARSING <= pstCtx->State) && (JPG_STATE_PARSED > pstCtx->State))
        || ((0 == pstCtx->ReqIndex) && (pstCtx->CurrIndex != (HI_S32)pstCtx->ReqIndex))
        || ((0 != pstCtx->ReqIndex) && (pstCtx->CurrIndex < (HI_S32)pstCtx->ReqIndex)
             && (0 != pstCtx->CurrIndex)))
    {
        if(JPG_STATE_PARSING != pstCtx->State)
        {
            if(pstCtx->CurrIndex >= 0)
            {
                Avail = JPGCheckPicAvail(pstCtx->State, (HI_U32)pstCtx->CurrIndex,
                                         pstCtx->ThumbCnt, pstCtx->ReqIndex);
            }

            if((HI_SUCCESS == Avail) ||
               (HI_ERR_JPG_THUMB_NOEXIST == Avail))
            {
                *pSize = 0;
                return HI_FAILURE;
            }
        }

        (HI_VOID)JPGBUF_GetFreeInfo(&pstCtx->ParseBuf, pAddr, pSize);
        if(0 == *pSize)
        {
            pstCtx->State = JPG_STATE_PARSEERR;
            (HI_VOID)JPGBUF_Reset(&pstCtx->ParseBuf);

            return HI_FAILURE;
        }

        return HI_SUCCESS;
    }
    else if(JPG_STATE_DECODING == pstCtx->State)
    {
        s32Ret = pstCtx->pstruCurrentDec->JPGDEC_Status(pstCtx->HDecHandle, pAddr, pSize, &HdState);
        pstCtx->State = JPG_TransformHDState(HdState);

#ifdef X5_JPEG
    	if( (pstCtx->State  >= JPG_STATE_DECODED) &&  (0 != pstCtx->HDecHandle))
    	{
    		pstCtx->pstruCurrentDec->JPGDEC_DestroyInstance(pstCtx->HDecHandle);
    		pstCtx->HDecHandle = 0;
    	}

        if(JPG_HDSTATE_DECODEERR == HdState)
        {
		pstCtx->bHDecErr = HI_TRUE;
	 }

	 if((JPG_HDSTATE_DECODED == HdState) && (HI_TRUE == pstCtx->bHDecErr))
        {
		pstCtx->bHDecErr = HI_FALSE;
	 }
#endif
        if(HI_SUCCESS != s32Ret)
        {
            *pSize = 0;
            return HI_FAILURE;
        }

        if(*pSize >= JPG_STREAM_PART)
        {
            *pSize = JPG_STREAM_PART;
        }

        return HI_SUCCESS;
    }
    *pSize = 0;
    return HI_FAILURE;
}
#ifndef HIGO_CODE_CUT
/******************************************************************************
* Function:      JPG_GetExifData
* Description:   App1 Exif
* Input:         Handle
* Output:        pAddr
*                pSize
* Return:        HI_SUCCESS
*                HI_ERR_JPG_INVALID_HANDLE
*                HI_ERR_JPG_WANT_STREAM
*                HI_ERR_JPG_PARSE_FAIL
*                HI_ERR_JPG_NO_MEM:
* Others:
******************************************************************************/
HI_S32  JPG_GetExifData(JPG_HANDLE Handle, HI_VOID** pAddr, HI_U32 *pSize)
{
    /*AI7D02581*/
    JPG_DECCTX_S*   pstCtx;
    HI_S32          s32Ret;
    JPG_PARSESTATE_S stParseState;
    HI_U32 Index =  1;
    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);

    pstCtx->bReqExif = HI_TRUE;
    pstCtx->ReqIndex = Index;
    stParseState.ThumbEcsLen = pstCtx->ThumbEcsLen;
    pstCtx->ThumbEcsLen = 0;
    s32Ret = JPGPARSE_Parse(pstCtx->ParseHandle, &pstCtx->ParseBuf,
                            Index, pstCtx->bReqExif, &stParseState);

    if(HI_SUCCESS == s32Ret)
    {
        JPGPARSE_GetExifInfo(pstCtx->ParseHandle, pAddr, pSize);
	    pstCtx->pExifAddr = (*pAddr);
        pstCtx->bReqExif = HI_FALSE;
        return HI_SUCCESS;
    }
    else if(HI_ERR_JPG_WANT_STREAM == s32Ret)
    {
        return HI_ERR_JPG_WANT_STREAM;
    }
    else if(HI_ERR_JPG_NO_MEM == s32Ret)
    {
        return HI_ERR_JPG_NO_MEM;
    }

    pstCtx->bReqExif = HI_FALSE;
    return HI_ERR_JPG_PARSE_FAIL;
}

/******************************************************************************
* Function:      JPG_ReleaseExifData
* Description:
* Input:         Handle
*                pAddr
* Output:
* Return:        HI_SUCCESS
*                HI_FAILURE
* Others:
******************************************************************************/
HI_S32  JPG_ReleaseExifData(JPG_HANDLE Handle, HI_VOID* pAddr)
{
    JPG_DECCTX_S*   pstCtx;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);
    JPG_CHECK_NULLPTR(pAddr);

    if(pAddr != pstCtx->pExifAddr)
    {
        return HI_ERR_JPG_INVALID_PARA;
    }

    //VCOS_free(pAddr);
    JPGPARSE_ReleaseExif(pstCtx->ParseHandle, pAddr);

    pstCtx->pExifAddr = NULL;

    return HI_SUCCESS;
}

/******************************************************************************
* Function:      JPG_HdecCheck
* Description:
* Input:         Handle
*                pSurface
*                Index
* Output:
* Return:        HI_SUCCESS
*                HI_FAILURE
*                HI_ERR_JPG_INVALID_HANDLE
*                HI_ERR_JPG_DEC_FAIL
* Others:
******************************************************************************/
HI_S32 JPG_HdecCheck(JPG_HANDLE Handle, HI_U32 Index)
{
    JPG_DECCTX_S*   pstCtx;
    HI_S32          s32Ret;
    JPGDEC_CHECKINFO_S   CheckInfo;
    JPG_PICPARSEINFO_S*  pCurPicInfo;

    HI_U32  QuantTblNum  = 0;
    HI_U32  DcHuffTblNum = 0;
    HI_U32  AcHuffTblNum = 0;
    HI_S32  Avail = HI_FAILURE;
    HI_U32  i;

    HI_U32  SurfaceSize;

    pstCtx = (JPG_DECCTX_S*)JPG_Handle_GetInstance(Handle);
    JPG_CHECK_HANDLE(pstCtx);

    assert((JPG_STATE_PARTPARSED <= pstCtx->State) &&
           (JPG_STATE_PARSED >= pstCtx->State));

    if(0 == Index)
    {
        assert(0 == pstCtx->CurrIndex);
    }

    if( pstCtx->CurrIndex == -1)
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    Avail = JPGCheckPicAvail(pstCtx->State, (HI_U32)pstCtx->CurrIndex,
                                 pstCtx->ThumbCnt, Index);
    if(Avail == HI_FAILURE)
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    JPG_GETCURPICINFO(pstCtx->ParseHandle, Index, pCurPicInfo);
    if (NULL == pCurPicInfo)
    {
        return HI_ERR_JPG_DEC_FAIL;
    }

    for(i = 0; i < 4; i++)
    {
        if(NULL != pCurPicInfo->pQuantTbl[i])
        {
            QuantTblNum++;
        }
        if(NULL != pCurPicInfo->pDcHuffTbl[i])
        {
            DcHuffTblNum++;
        }
        if(NULL != pCurPicInfo->pAcHuffTbl[i])
        {
            AcHuffTblNum++;
        }
    }

    CheckInfo.QuantTblNum  = QuantTblNum;
    CheckInfo.DcHuffTblNum = DcHuffTblNum;
    CheckInfo.AcHuffTblNum = AcHuffTblNum;

    CheckInfo.Width        = pCurPicInfo->Width;
    CheckInfo.Height       = pCurPicInfo->Height;
    CheckInfo.Precise      = pCurPicInfo->Precise;
    CheckInfo.Profile      = pCurPicInfo->Profile;

    CheckInfo.EncFmt   = JPGGetFormat(pCurPicInfo);
    CheckInfo.ComponentNum = pCurPicInfo->ComponentNum;

    s32Ret = JPGHDEC_Check(INVALID_HANDLE, &CheckInfo);


   SurfaceSize = (pCurPicInfo->Width * pCurPicInfo->Height  * 2 ) ;

   if(SurfaceSize + pstCtx->FileLen > (30<<20))
   {
       return HI_FAILURE;
   }

    return s32Ret;
}
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */


