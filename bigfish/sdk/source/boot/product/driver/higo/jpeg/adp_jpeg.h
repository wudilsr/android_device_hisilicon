/**
\file
\brief jpeg adaptive layer
\copyright Shenzhen Hisilicon Co., Ltd.
\date 2008-2018
\version draft
\author memmng
\date 2010-2-1
*/

#ifndef __ADP_JPEG_H__
#define __ADP_JPEG_H__

/* add include here */
#include "hi_go_config.h"

#ifdef HIGO_JPEG_SUPPORT
#include "higo_io.h"
#include "higo_common.h"
#include "higo_surface.h"
#include "hi_go_decoder.h"
#include "hi_go_config.h"

#ifdef __cplusplus
extern "C" {
#endif
/***************************** Macro Definition ******************************/



/*************************** Structure Definition ****************************/



/********************** Global Variable declaration **************************/



/******************************* API declaration *****************************/
/**
 \brief jpeg initial
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JpegInit(HI_VOID);

/**
 \brief jpeg de initial
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JpegDeInit(HI_VOID);

/**
 \brief create decode instance
 \param[in] DEC_HANDLE *pJpegDec  decode instance handle
 \param[in] const HIGO_DEC_ATTR_S *pSrcDesc decoder parameter
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGCreateDecoder(DEC_HANDLE *pJpegDec, const HIGO_DEC_ATTR_S *pSrcDesc);

/**
 \brief destroy decoder
 \param[in] DEC_HANDLE JpegDec decode instance handle
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGDestroyDecoder(DEC_HANDLE JpegDec);
#ifdef TEST_IN_ROOTBOX
/**
 \brief send bitstream to decoder
 \param[in] DEC_HANDLE JpegDec  decode instance handle
 \param[in] HIGO_DEC_WRITESTREAM_S *pWriteStream
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGWriteStream(DEC_HANDLE JpegDec, HIGO_DEC_WRITESTREAM_S *pWriteStream);
#endif

/**
 \brief restart decode 
 \param[in] DEC_HANDLE JpegDec decode instance handle
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGResetDecoder(DEC_HANDLE JpegDec);

/**
 \brief deocode picuture common info
 \param[in] DEC_HANDLE JpegDec decode instance handle
 \param[in] HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo common info pointer
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGDecCommInfo(DEC_HANDLE JpegDec, HIGO_DEC_PRIMARYINFO_S *pPrimaryInfo);

/**
 \brief decode picture index info
 \param[in] DEC_HANDLE JpegDec decode instance handle
 \param[in] HI_U32  Index index number
 \param[in] HIGO_DEC_IMGINFO_S *pImgInfo pointer of picture infor
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGDecImgInfo(DEC_HANDLE JpegDec, HI_U32 Index, HIGO_DEC_IMGINFO_S *pImgInfo);

/**
 \brief get picture data, and decode can do scaling in frequency domain
 \param[in] DEC_HANDLE JpegDec  decode instance handle
 \param[in] HI_U32 Index index number
 \param[in/out] HIGO_DEC_IMGDATA_S *pImgInfo picture info ,for input and output 
               input: decode output format, height, witdh , pixel format  which user needed 
               output: format decode output
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGDecImgData(DEC_HANDLE JpegDec, HI_U32 Index, HIGO_SURFACE_S * pSurface);

/**
 \brief release decode data after finish decoding 
 \param[in] DEC_HANDLE Decoder decode instance handle
 \param[in] HIGO_DEC_IMGDATA_S *pImgInfo data pointer
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGReleaseDecImgData(DEC_HANDLE Decoder, HIGO_DEC_IMGDATA_S *pImgData);
#if 0

/**
 \brief decode extend data
 \param[in] DEC_HANDLE JpegDec decode instance handle
 \param[in] HIGO_DEC_EXTENDTYPE_E DecExtendType 
 \param[in] HI_VOID **pData 
 \param[in] HI_U32 *pLength 
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGDecExtendData(DEC_HANDLE JpegDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID **pData,
                                   HI_U32 *pLength);

/**
 \brief 
 \param[in] DEC_HANDLE JpegDec
 \param[in] HIGO_DEC_EXTENDTYPE_E DecExtendType
 \param[in] HI_VOID *pData
 \param[out] none
 \retval none
 \return none
 */
HI_S32   HIGO_ADP_JPGReleaseDecExtendData(DEC_HANDLE JpegDec, HIGO_DEC_EXTENDTYPE_E DecExtendType, HI_VOID *pData);

#endif
HI_S32 HIGO_ADP_JPGGetActualSize(DEC_HANDLE JpegDec, HI_S32 Index, const HI_RECT *pSrcRect, HIGO_SURINFO_S *pSurInfo);

#ifdef __cplusplus
}
#endif
#endif
#endif /* __ADP_JPEG_H__ */
