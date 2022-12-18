/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_error_mpi.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2008/04/24
  Description   : error code of MPI
  History       :
  1.Date        : 2008/04/24
    Author      : q46153
    Modification: Created file

******************************************************************************/
/** 
\file
\brief Describes the information about common error codes. CNcomment: 提供公共错误码的相关信息
*/
/* add include here */
#ifndef __HI_UNF_MPI_ERRORCODE_H__
#define __HI_UNF_MPI_ERRORCODE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* End of #ifdef __cplusplus */

/***************************** Macro Definition ******************************/
/** \addtogroup      H_3_1 */
/** @{ */  /** <!-- 【Error codes related to media processing CNcomment: 媒体处理错误码】 */

#define HI_ERR_DISP_DEV_NOT_EXIST           (HI_S32)(0x80100001)
#define HI_ERR_DISP_NOT_DEV_FILE            (HI_S32)(0x80100002)
#define HI_ERR_DISP_DEV_OPEN_ERR            (HI_S32)(0x80100003)
#define HI_ERR_DISP_DEV_CLOSE_ERR           (HI_S32)(0x80100004)
#define HI_ERR_DISP_NULL_PTR                (HI_S32)(0x80100005)
#define HI_ERR_DISP_NO_INIT                 (HI_S32)(0x80100006)
#define HI_ERR_DISP_INVALID_PARA            (HI_S32)(0x80100007)
#define HI_ERR_DISP_CREATE_ERR              (HI_S32)(0x80100008)
#define HI_ERR_DISP_DESTROY_ERR             (HI_S32)(0x80100009)
#define HI_ERR_DISP_NOT_EXIST               (HI_S32)(0x8010000A)
#define HI_ERR_DISP_INVALID_OPT             (HI_S32)(0x8010000B)
#define HI_ERR_DISP_NOT_SUPPORT_FMT         (HI_S32)(0x8010000C)

#define HI_ERR_DISP_NOT_OPEN                (HI_S32)(0x8010000D)
#define HI_ERR_DISP_SRC_UNAVAILABLE         (HI_S32)(0x8010000E)
#define HI_ERR_DISP_NOT_SUPPORT             (HI_S32)(0x8010000F)
#define HI_ERR_DISP_UNKNOWN                 (HI_S32)(0x801000FF)
#define HI_ERR_DISP_TIMEOUT                 (HI_S32)(0x801000F1)
#define HI_ERR_DISP_MALLOC_MAP_ERR          (HI_S32)(0x801000F2)

#define HI_ERR_VO_DEV_NOT_EXIST             (HI_S32)(0x80110001)
#define HI_ERR_VO_NOT_DEV_FILE              (HI_S32)(0x80110002)
#define HI_ERR_VO_DEV_OPEN_ERR              (HI_S32)(0x80110003)
#define HI_ERR_VO_DEV_CLOSE_ERR             (HI_S32)(0x80110004)
#define HI_ERR_VO_NULL_PTR                  (HI_S32)(0x80110005)
#define HI_ERR_VO_NO_INIT                   (HI_S32)(0x80110006)
#define HI_ERR_VO_INVALID_PARA              (HI_S32)(0x80110007)
#define HI_ERR_VO_CREATE_ERR                (HI_S32)(0x80110008)
#define HI_ERR_VO_DESTROY_ERR               (HI_S32)(0x80110009)
#define HI_ERR_VO_NOT_EXIST                 (HI_S32)(0x80110010)
#define HI_ERR_VO_INVALID_OPT               (HI_S32)(0x80110030)
#define HI_ERR_VO_WIN_NOT_EXIST             (HI_S32)(0x80110040)
#define HI_ERR_VO_WIN_NOT_ENABLE            (HI_S32)(0x80110041)
#define HI_ERR_VO_WIN_UNSUPPORT           (HI_S32)(0x80110042)
#define HI_ERR_VO_TIMEOUT                   (HI_S32)(0x80110043)
#define HI_ERR_VO_OPERATION_DENIED          (HI_S32)(0x80110044)
#define HI_ERR_VO_SLAVE_WIN_LOST            (HI_S32)(0x80110045)
#define HI_ERR_VO_FRAME_INFO_ERROR          (HI_S32)(0x80110046)
#define HI_ERR_VO_FRAME_RELEASE_FAILED      (HI_S32)(0x80110047)
#define HI_ERR_VO_NO_FRAME_TO_RELEASE       (HI_S32)(0x80110048)
#define HI_ERR_VO_ADD_PROC_ERR              (HI_S32)(0x80110049)
#define HI_ERR_VO_MALLOC_FAILED             (HI_S32)(0x80110050)
#define HI_ERR_VO_DEPEND_DEVICE_NOT_READY   (HI_S32)(0x80110051)
#define HI_ERR_VO_BUFQUE_FULL               (HI_S32)(0x80110052)
#define HI_ERR_VO_BUFQUE_EMPTY               (HI_S32)(0x80110053)








#define HI_ERR_VDEC_NOT_OPEN                (HI_S32)(0x80120001)
#define HI_ERR_VDEC_INVALID_PARA            (HI_S32)(0x80120002)
#define HI_ERR_VDEC_NULL_PTR                (HI_S32)(0x80120003)
#define HI_ERR_VDEC_NOT_SUPPORT             (HI_S32)(0x80120004)
#define HI_ERR_VDEC_TIMEOUT                 (HI_S32)(0x80120005)
#define HI_ERR_VDEC_MALLOC_FAILED           (HI_S32)(0x80120044)
#define HI_ERR_VDEC_CREATECH_FAILED         (HI_S32)(0x80120047)
#define HI_ERR_VDEC_DESTROYCH_FAILED        (HI_S32)(0x80120048)
#define HI_ERR_VDEC_INVALID_CHANID          (HI_S32)(0x80120049)
#define HI_ERR_VDEC_RESETCH_FAILED          (HI_S32)(0x80120050)
#define HI_ERR_VDEC_SETATTR_FAILED          (HI_S32)(0x80120051)
#define HI_ERR_VDEC_GETATTR_FAILED          (HI_S32)(0x80120052)
#define HI_ERR_VDEC_SENDSTREAM_FAILED       (HI_S32)(0x80120053)
#define HI_ERR_VDEC_RECEIVE_FAILED          (HI_S32)(0x80120054)
#define HI_ERR_VDEC_DISCARD_PRIDATA         (HI_S32)(0x80120055)
#define HI_ERR_VDEC_RELEASEFRAME_FAILED     (HI_S32)(0x80120056)
#define HI_ERR_VDEC_RELEASEPRI_FAILED       (HI_S32)(0x80120057)
#define HI_ERR_VDEC_NOT_INIT                (HI_S32)(0x80120059)
#define HI_ERR_VDEC_USERCOPY_ERR            (HI_S32)(0x8012005A)
#define HI_ERR_VDEC_LIST_EMPTY              (HI_S32)(0x8012005B)
#define HI_ERR_VDEC_INVALID_STATE           (HI_S32)(0x8012005C)
#define HI_ERR_VDEC_NOT_ENABLE              (HI_S32)(0x80120060)
#define HI_ERR_VDEC_BUFFER_NOT_ATTACH       (HI_S32)(0x80120061)
#define HI_ERR_VDEC_BUFFER_REQUIRE_INVALID  (HI_S32)(0x80120062)
#define HI_ERR_VDEC_BUFFER_ATTACHED         (HI_S32)(0x80120063)
#define HI_ERR_VDEC_BUFFER_FULL             (HI_S32)(0x80120064)

#define HI_ERR_SND_NOT_INIT                 (HI_S32)(0x80130001)
#define HI_ERR_SND_INVALID_PARA             (HI_S32)(0x80130002)
#define HI_ERR_SND_NULL_PTR                 (HI_S32)(0x80130003)
#define HI_ERR_SND_INVALID_ID               (HI_S32)(0x80130004)
#define HI_ERR_SND_USED                     (HI_S32)(0x80130005)
#define HI_ERR_SND_NOTSUPPORT               (HI_S32)(0x80130006)
#define HI_ERR_SND_USERCOPY_ERR             (HI_S32)(0x80130007)
#define HI_ERR_HIAO_DEV_NOT_OPEN            (HI_S32)(0x80130041)
#define HI_ERR_HIAO_CREATE_FAIL             (HI_S32)(0x80130042)
#define HI_ERR_HIAO_NULL_PTR                (HI_S32)(0x80130043)
#define HI_ERR_HIAO_INVALID_PARA            (HI_S32)(0x80130044)
#define HI_ERR_HIAO_OUT_BUF_FULL            (HI_S32)(0x80130046)
#define HI_ERR_HIAO_INVALID_OUTFRAME        (HI_S32)(0x80130047)
#define HI_ERR_HIAO_DATASIZE_EXCEED         (HI_S32)(0x80130048)
#define HI_ERR_HIAO_INVALID_INFRAME         (HI_S32)(0x80130049)
#define HI_ERR_HIAO_INBUF_EMPTY             (HI_S32)(0x8013004a)
#define HI_ERR_HIAO_INVALID_PORT            (HI_S32)(0x8013004c)
#define HI_ERR_HIAO_SENDMUTE                (HI_S32)(0x8013004d)

#define HI_ERR_ADEC_DEV_NOT_OPEN            (HI_S32)(0x80140001)
#define HI_ERR_ADEC_INVALID_PARA            (HI_S32)(0x80140002)
#define HI_ERR_ADEC_NULL_PTR                (HI_S32)(0x80140003)
#define HI_ERR_ADEC_IN_BUF_FULL             (HI_S32)(0x80140004)
#define HI_ERR_ADEC_OUT_BUF_EMPTY           (HI_S32)(0x80140005)
#define HI_ERR_ADEC_OUT_VOLUME              (HI_S32)(0x80140006)
#define HI_ERR_ADEC_IN_PTSBUF_FULL          (HI_S32)(0x80140007)

#define HI_ERR_DMX_NOT_INIT                 (HI_S32)(0x80150001)
#define HI_ERR_DMX_INVALID_PARA             (HI_S32)(0x80150002)
#define HI_ERR_DMX_NULL_PTR                 (HI_S32)(0x80150003)
#define HI_ERR_DMX_NOT_SUPPORT              (HI_S32)(0x80150004)
#define HI_ERR_DMX_TIMEOUT                  (HI_S32)(0x80150005)
#define HI_ERR_DMX_ALLOC_MEM_FAILED         (HI_S32)(0x80150006)
#define HI_ERR_DMX_BUSY                     (HI_S32)(0x80150007)
#define HI_ERR_DMX_NOATTACH_PORT            (HI_S32)(0x80150008)
#define HI_ERR_DMX_ATTACHED_PORT            (HI_S32)(0x80150009)
#define HI_ERR_DMX_RECREAT_TSBUFFER         (HI_S32)(0x8015000a)
#define HI_ERR_DMX_UNMATCH_CHAN             (HI_S32)(0x8015000b)
#define HI_ERR_DMX_NOFREE_CHAN              (HI_S32)(0x8015000c)
#define HI_ERR_DMX_OPENING_CHAN             (HI_S32)(0x8015000d)
#define HI_ERR_DMX_NOT_OPEN_CHAN            (HI_S32)(0x8015000e)
#define HI_ERR_DMX_ATTACHED_FILTER          (HI_S32)(0x8015000f)
#define HI_ERR_DMX_NOATTACH_FILTER          (HI_S32)(0x80150010)
#define HI_ERR_DMX_UNMATCH_FILTER           (HI_S32)(0x80150011)
#define HI_ERR_DMX_NOFREE_FILTER            (HI_S32)(0x80150012)
#define HI_ERR_DMX_NOATTACH_KEY             (HI_S32)(0x80150013)
#define HI_ERR_DMX_UNMATCH_KEY              (HI_S32)(0x80150014)
#define HI_ERR_DMX_NOFREE_KEY               (HI_S32)(0x80150015)
#define HI_ERR_DMX_ATTACHED_KEY             (HI_S32)(0x80150016)
#define HI_ERR_DMX_NOAVAILABLE_BUF          (HI_S32)(0x80150017)
#define HI_ERR_DMX_NOAVAILABLE_DATA         (HI_S32)(0x80150018)
#define HI_ERR_DMX_REACQUIRE_BUF            (HI_S32)(0x80150019)

#define HI_ERR_VI_NO_INIT                   (HI_S32)(0x801A0001)
#define HI_ERR_VI_INVALID_PARA              (HI_S32)(0x801A0002)
#define HI_ERR_VI_NULL_PTR                  (HI_S32)(0x801A0003)
#define HI_ERR_VI_INVALID_CHNID             (HI_S32)(0x801A0004)
#define HI_ERR_VI_DEV_OPENED                (HI_S32)(0x801A0005)
#define HI_ERR_VI_DEV_NOT_EXIST             (HI_S32)(0x801A0006)
#define HI_ERR_VI_NOT_DEV_FILE              (HI_S32)(0x801A0007)
#define HI_ERR_VI_NO_CHN_LEFT               (HI_S32)(0x801A0008)
#define HI_ERR_VI_BUSY                      (HI_S32)(0x801A0009)
#define HI_ERR_VI_CHN_NOT_EXIST             (HI_S32)(0x801A000A)
#define HI_ERR_VI_CHN_INVALID_OPT           (HI_S32)(0x801A000B)
#define HI_ERR_VI_CHN_INVALID_STAT          (HI_S32)(0x801A000C)
#define HI_ERR_VI_CHN_INIT_BUF_ERR          (HI_S32)(0x801A000D)
#define HI_ERR_VI_BUF_EMPTY                 (HI_S32)(0x801A000E)
#define HI_ERR_VI_BUF_FULL                  (HI_S32)(0x801A000F)
#define HI_ERR_VI_NOT_SUPPORT               (HI_S32)(0x801A0010)

#define HI_ERR_AENC_DEV_NOT_OPEN            (HI_S32)(0x801C0001)
#define HI_ERR_AENC_INVALID_PARA            (HI_S32)(0x801C0002)
#define HI_ERR_AENC_NULL_PTR                (HI_S32)(0x801C0003)
#define HI_ERR_AENC_OUT_BUF_FULL            (HI_S32)(0x801C0006)
#define HI_ERR_AENC_INVALID_OUTFRAME        (HI_S32)(0x801C0007)
#define HI_ERR_AENC_DATASIZE_EXCEED         (HI_S32)(0x801C0008)
#define HI_ERR_AENC_CREATECH_FAIL           (HI_S32)(0x801C0009)
#define HI_ERR_AENC_IN_BUF_FULL             (HI_S32)(0x801C000a)
#define HI_ERR_AENC_CH_NOT_OPEN             (HI_S32)(0x801C000b)
#define HI_ERR_AENC_OUT_BUF_EMPTY           (HI_S32)(0x801C000c)
#define HI_ERR_AENC_OUT_BUF_BAD             (HI_S32)(0x801C000d)
#define HI_ERR_AENC_IN_BUF_UNEMPTY          (HI_S32)(0x801C000e)
#define HI_ERR_AENC_CH_NOT_SUPPORT          (HI_S32)(0x801C000f)


#define HI_ERR_VENC_NO_INIT                 (HI_S32)(0x801D0001)
#define HI_ERR_VENC_INVALID_PARA            (HI_S32)(0x801D0002)
#define HI_ERR_VENC_NULL_PTR                (HI_S32)(0x801D0003)
#define HI_ERR_VENC_INVALID_CHNID           (HI_S32)(0x801D0004)
#define HI_ERR_VENC_DEV_OPENED              (HI_S32)(0x801D0005)
#define HI_ERR_VENC_DEV_NOT_EXIST           (HI_S32)(0x801D0006)
#define HI_ERR_VENC_NOT_DEV_FILE            (HI_S32)(0x801D0007)
#define HI_ERR_VENC_CREATE_ERR              (HI_S32)(0x801D0008)
#define HI_ERR_VENC_DESTROY_ERR             (HI_S32)(0x801D0009)
#define HI_ERR_VENC_CHN_NOT_EXIST           (HI_S32)(0x801D000A)
#define HI_ERR_VENC_CHN_INVALID_STAT        (HI_S32)(0x801D000B)
#define HI_ERR_VENC_CHN_NO_ATTACH           (HI_S32)(0x801D000C)
#define HI_ERR_VENC_BUF_EMPTY               (HI_S32)(0x801D000D)
#define HI_ERR_VENC_CHN_RELEASE_ERR         (HI_S32)(0x801D000E)
#define HI_ERR_VENC_NOT_SUPPORT             (HI_S32)(0x801D000F)

#define HI_ERR_SIO_AI_INVALID_DEVID         (HI_S32)(0x801E0001)
#define HI_ERR_SIO_AI_INVALID_CHNID         (HI_S32)(0x801E0002)
#define HI_ERR_SIO_AI_ILLEGAL_PARAM         (HI_S32)(0x801E0003)
#define HI_ERR_SIO_AI_NULL_PTR              (HI_S32)(0x801E0004)
#define HI_ERR_SIO_AI_NOT_CONFIG            (HI_S32)(0x801E0005)
#define HI_ERR_SIO_AI_NOT_SURPPORT          (HI_S32)(0x801E0006)
#define HI_ERR_SIO_AI_NOT_PERM              (HI_S32)(0x801E0007)
#define HI_ERR_SIO_AI_NOT_ENABLED           (HI_S32)(0x801E0008)
#define HI_ERR_SIO_AI_NOMEM                 (HI_S32)(0x801E0009)
#define HI_ERR_SIO_AI_NOBUF                 (HI_S32)(0x801E000A)
#define HI_ERR_SIO_AI_BUF_EMPTY             (HI_S32)(0x801E000B)
#define HI_ERR_SIO_AI_BUF_FULL              (HI_S32)(0x801E000C)
#define HI_ERR_SIO_AI_SYS_NOTREADY          (HI_S32)(0x801E000D)
#define HI_ERR_SIO_AI_BUSY                  (HI_S32)(0x801E000E)

#define HI_ERR_SIO_AO_INVALID_DEVID         (HI_S32)(0x801F0001)
#define HI_ERR_SIO_AO_INVALID_CHNID         (HI_S32)(0x801F0002)
#define HI_ERR_SIO_AO_ILLEGAL_PARAM         (HI_S32)(0x801F0003)
#define HI_ERR_SIO_AO_NULL_PTR              (HI_S32)(0x801F0004)
#define HI_ERR_SIO_AO_NOT_CONFIG            (HI_S32)(0x801F0005)
#define HI_ERR_SIO_AO_NOT_SURPPORT          (HI_S32)(0x801F0006)
#define HI_ERR_SIO_AO_NOT_PERM              (HI_S32)(0x801F0007)
#define HI_ERR_SIO_AO_NOT_ENABLED           (HI_S32)(0x801F0008)
#define HI_ERR_SIO_AO_NOMEM                 (HI_S32)(0x801F0009)
#define HI_ERR_SIO_AO_NOBUF                 (HI_S32)(0x801F000A)
#define HI_ERR_SIO_AO_BUF_EMPTY             (HI_S32)(0x801F000B)
#define HI_ERR_SIO_AO_BUF_FULL              (HI_S32)(0x801F000C)
#define HI_ERR_SIO_AO_SYS_NOTREADY          (HI_S32)(0x801F000D)
#define HI_ERR_SIO_AO_BUSY                  (HI_S32)(0x801F000E)

#define HI_ERR_HDMI_NOT_INIT                (HI_S32)(0x80210001)
#define HI_ERR_HDMI_INVALID_PARA            (HI_S32)(0x80210002)
#define HI_ERR_HDMI_NUL_PTR                 (HI_S32)(0x80210003)
#define HI_ERR_HDMI_DEV_NOT_OPEN            (HI_S32)(0x80210004)
#define HI_ERR_HDMI_DEV_NOT_CONNECT         (HI_S32)(0x80210005)
#define HI_ERR_HDMI_READ_SINK_FAILED        (HI_S32)(0x80210006)
#define HI_ERR_HDMI_INIT_ALREADY            (HI_S32)(0x80210007)
#define HI_ERR_HDMI_CALLBACK_ALREADY        (HI_S32)(0x80210008)
#define HI_ERR_HDMI_INVALID_CALLBACK        (HI_S32)(0x80210009)
#define HI_ERR_HDMI_FEATURE_NO_USPPORT      (HI_S32)(0x8021000a)
#define HI_ERR_HDMI_BUS_BUSY                (HI_S32)(0x8021000b)

#define HI_ERR_PVR_NOT_INIT                 (HI_S32)(0x80300001)
#define HI_ERR_PVR_INVALID_PARA             (HI_S32)(0x80300002)
#define HI_ERR_PVR_NUL_PTR                  (HI_S32)(0x80300003)
#define HI_ERR_PVR_CHN_NOT_INIT             (HI_S32)(0x80300004)
#define HI_ERR_PVR_INVALID_CHNID            (HI_S32)(0x80300005)
#define HI_ERR_PVR_NO_CHN_LEFT              (HI_S32)(0x80300006)
#define HI_ERR_PVR_ALREADY                  (HI_S32)(0x80300007)
#define HI_ERR_PVR_BUSY                     (HI_S32)(0x80300008)
#define HI_ERR_PVR_NO_MEM                   (HI_S32)(0x80300009)
#define HI_ERR_PVR_NOT_SUPPORT              (HI_S32)(0x8030000A)
#define HI_ERR_PVR_RETRY                    (HI_S32)(0x8030000B)
#define HI_ERR_PVR_FILE_EXIST               (HI_S32)(0x80300011)
#define HI_ERR_PVR_FILE_NOT_EXIST           (HI_S32)(0x80300012)
#define HI_ERR_PVR_FILE_CANT_OPEN           (HI_S32)(0x80300013)
#define HI_ERR_PVR_FILE_CANT_CLOSE          (HI_S32)(0x80300014)
#define HI_ERR_PVR_FILE_CANT_SEEK           (HI_S32)(0x80300015)
#define HI_ERR_PVR_FILE_CANT_WRITE          (HI_S32)(0x80300016)
#define HI_ERR_PVR_FILE_CANT_READ           (HI_S32)(0x80300017)
#define HI_ERR_PVR_FILE_INVALID_FNAME       (HI_S32)(0x80300018)
#define HI_ERR_PVR_FILE_TILL_START          (HI_S32)(0x80300019)
#define HI_ERR_PVR_FILE_TILL_END            (HI_S32)(0x8030001A)
#define HI_ERR_PVR_FILE_DISC_FULL           (HI_S32)(0x8030001B)
#define HI_ERR_PVR_REC_INVALID_STATE        (HI_S32)(0x80300021)
#define HI_ERR_PVR_REC_INVALID_DMXID        (HI_S32)(0x80300022)
#define HI_ERR_PVR_REC_INVALID_FSIZE        (HI_S32)(0x80300023)
#define HI_ERR_PVR_REC_INVALID_UDSIZE       (HI_S32)(0x80300024)
#define HI_ERR_PVR_PLAY_INVALID_STATE       (HI_S32)(0x80300031)
#define HI_ERR_PVR_PLAY_INVALID_DMXID       (HI_S32)(0x80300032)
#define HI_ERR_PVR_INDEX_CANT_MKIDX         (HI_S32)(0x80300041)
#define HI_ERR_PVR_INDEX_FORMAT_ERR         (HI_S32)(0x80300042)
#define HI_ERR_PVR_INDEX_DATA_ERR           (HI_S32)(0x80300043)
#define HI_ERR_PVR_INTF_EVENT_INVAL         (HI_S32)(0x80300051)
#define HI_ERR_PVR_INTF_EVENT_NOREG         (HI_S32)(0x80300052)

#define HI_ERR_AVPLAY_DEV_NOT_EXIST         (HI_S32)(0x80310001)
#define HI_ERR_AVPLAY_NOT_DEV_FILE          (HI_S32)(0x80310002)
#define HI_ERR_AVPLAY_DEV_OPEN_ERR          (HI_S32)(0x80310003)
#define HI_ERR_AVPLAY_DEV_CLOSE_ERR         (HI_S32)(0x80310004)
#define HI_ERR_AVPLAY_NULL_PTR              (HI_S32)(0x80310005)
#define HI_ERR_AVPLAY_DEV_NO_INIT           (HI_S32)(0x80310006)
#define HI_ERR_AVPLAY_INVALID_PARA          (HI_S32)(0x80310007)
#define HI_ERR_AVPLAY_CREATE_ERR            (HI_S32)(0x80310008)
#define HI_ERR_AVPLAY_DESTROY_ERR           (HI_S32)(0x80310009)
#define HI_ERR_AVPLAY_INVALID_OPT           (HI_S32)(0x8031000A)
#define HI_ERR_AVPLAY_NOT_SUPPORT           (HI_S32)(0x8031000B)

#define HI_ERR_SYNC_DEV_NOT_EXIST           (HI_S32)(0x80320001)
#define HI_ERR_SYNC_NOT_DEV_FILE            (HI_S32)(0x80320002)
#define HI_ERR_SYNC_DEV_OPEN_ERR            (HI_S32)(0x80320003)
#define HI_ERR_SYNC_DEV_CLOSE_ERR           (HI_S32)(0x80320004)
#define HI_ERR_SYNC_NULL_PTR                (HI_S32)(0x80320005)
#define HI_ERR_SYNC_DEV_NO_INIT             (HI_S32)(0x80320006)
#define HI_ERR_SYNC_INVALID_PARA            (HI_S32)(0x80320007)
#define HI_ERR_SYNC_CREATE_ERR              (HI_S32)(0x80320008)
#define HI_ERR_SYNC_DESTROY_ERR             (HI_S32)(0x80320009)
#define HI_ERR_SYNC_INVALID_OPT             (HI_S32)(0x8032000A)

#define HI_ERR_MCE_PTR_NULL       			(HI_S32)(0x80330001)
#define HI_ERR_MCE_PARAM_INVALID  			(HI_S32)(0x80330002)
#define HI_ERR_MCE_OPEN_ALREADY   			(HI_S32)(0x80330003)
#define HI_ERR_MCE_MEM_ALLC       			(HI_S32)(0x80330004)
#define HI_ERR_MCE_MTD_OPEN       			(HI_S32)(0x80330005)
#define HI_ERR_MCE_MTD_CLOSE      			(HI_S32)(0x80330006)
#define HI_ERR_MCE_MTD_READ       			(HI_S32)(0x80330007)
#define HI_ERR_MCE_MTD_WRITE      			(HI_S32)(0x80330008)
#define HI_ERR_MCE_MTD_NOFIND     			(HI_S32)(0x80330009)
#define HI_ERR_MCE_MTD_INFO       			(HI_S32)(0x80330010)
#define HI_ERR_MCE_BASE_INFO      			(HI_S32)(0x80330011)
#define HI_ERR_MCE_LOGO_INFO      			(HI_S32)(0x80330012)
#define HI_ERR_MCE_PLAY_INFO      			(HI_S32)(0x80330013)

#define HI_ERR_VP_PTR_NULL       			(HI_S32)(0x80340001)
#define HI_ERR_VP_NOT_INIT       			(HI_S32)(0x80340002)
#define HI_ERR_VP_DEV_NOT_EXIST             (HI_S32)(0x80340003)
#define HI_ERR_VP_NOT_DEV_FILE              (HI_S32)(0x80340004)
#define HI_ERR_VP_DEV_OPEN_ERR              (HI_S32)(0x80340005)
#define HI_ERR_VP_INVALID_PARA              (HI_S32)(0x80340006)
#define HI_ERR_VP_NOT_SUPPORT				(HI_S32)(0x80340007)
#define HI_ERR_VP_INVALID_HANDLE			(HI_S32)(0x80340008)
#define HI_ERR_VP_HANDLE_NOTEXIST			(HI_S32)(0x80340009)
#define HI_ERR_VP_NOT_READY 			    (HI_S32)(0x8034000a)
#define HI_ERR_VP_ILLEGAL_STATE				(HI_S32)(0x8034000b)

#define HI_ERR_IR_OPEN_ERR                          (HI_S32)(0x80410001)
#define HI_ERR_IR_CLOSE_ERR                         (HI_S32)(0x80410002)
#define HI_ERR_IR_NOT_INIT                          (HI_S32)(0x80410003)
#define HI_ERR_IR_INVALID_PARA                      (HI_S32)(0x80410004)
#define HI_ERR_IR_NULL_PTR                          (HI_S32)(0x80410005)
#define HI_ERR_IR_READ_FAILED                       (HI_S32)(0x80410006)
#define HI_ERR_IR_IOCTL_FAILED                      (HI_S32)(0x80410007)
#define HI_ERR_IR_UNSUPPORT                         (HI_S32)(0x80410008)

#define HI_ERR_RTC_NOT_INIT                         (HI_S32)(0x80420001)
#define HI_ERR_RTC_REPEAT_INIT                      (HI_S32)(0x80420002)
#define HI_ERR_RTC_INVALID_POINT                    (HI_S32)(0x80420003)
#define HI_ERR_RTC_INVALID_PARA                     (HI_S32)(0x80420004)
#define HI_ERR_RTC_FAILED_INIT                      (HI_S32)(0x80420005)
#define HI_ERR_RTC_FAILED_SETTIME                   (HI_S32)(0x80420006)
#define HI_ERR_RTC_FAILED_GETTIME                   (HI_S32)(0x80420007)
#define HI_ERR_RTC_FAILED_ALARMENABLE               (HI_S32)(0x80420008)
#define HI_ERR_RTC_FAILED_ALARMDISABLE              (HI_S32)(0x80420009)
#define HI_ERR_RTC_FAILED_SETALARM                  (HI_S32)(0x8042000A)
#define HI_ERR_RTC_FAILED_GETALARM                  (HI_S32)(0x8042000B)

#define HI_ERR_WDG_NOT_INIT                         (HI_S32)(0x80430001)
#define HI_ERR_WDG_REPEAT_INIT                      (HI_S32)(0x80430002)
#define HI_ERR_WDG_INVALID_POINT                    (HI_S32)(0x80430003)
#define HI_ERR_WDG_INVALID_PARA                     (HI_S32)(0x80430004)
#define HI_ERR_WDG_FAILED_INIT                      (HI_S32)(0x80430005)
#define HI_ERR_WDG_FAILED_SETTIMEOUT                (HI_S32)(0x80430006)
#define HI_ERR_WDG_FAILED_ENABLE                    (HI_S32)(0x80430007)
#define HI_ERR_WDG_FAILED_DISABLE                   (HI_S32)(0x80430008)
#define HI_ERR_WDG_FAILED_CLEARWDG                  (HI_S32)(0x80430009)
#define HI_ERR_WDG_FAILED_RESET                     (HI_S32)(0x8043000A)
#define HI_ERR_WDG_FAILED_RESMODE                   (HI_S32)(0x8043000B)
#define HI_ERR_WDG_NOT_SUPPORT                      (HI_S32)(0x8043000C)
#define HI_ERR_WDG_FAILED_GETTIMEOUT                (HI_S32)(0x8043000D)

#define HI_ERR_I2C_OPEN_ERR                         (HI_S32)(0x80440001)
#define HI_ERR_I2C_CLOSE_ERR                        (HI_S32)(0x80440002)
#define HI_ERR_I2C_NOT_INIT                         (HI_S32)(0x80440003)
#define HI_ERR_I2C_INVALID_PARA                     (HI_S32)(0x80440004)
#define HI_ERR_I2C_NULL_PTR                         (HI_S32)(0x80440005)
#define HI_ERR_I2C_COPY_DATA_ERR                    (HI_S32)(0x80440006)
#define HI_ERR_I2C_MALLOC_ERR                       (HI_S32)(0x80440007)
#define HI_ERR_I2C_WRITE_TIMEOUT                    (HI_S32)(0x80440008)
#define HI_ERR_I2C_READ_TIMEOUT                     (HI_S32)(0x80440009)

#define HI_ERR_SCI_OPEN_ERR                         (HI_S32)(0x80450001)
#define HI_ERR_SCI_CLOSE_ERR                        (HI_S32)(0x80450002)
#define HI_ERR_SCI_NOT_INIT                         (HI_S32)(0x80450003)
#define HI_ERR_SCI_INVALID_PARA                     (HI_S32)(0x80450004)
#define HI_ERR_SCI_NULL_PTR                         (HI_S32)(0x80450005)
#define HI_ERR_SCI_INVALID_OPT                      (HI_S32)(0x80450006)
#define HI_ERR_SCI_SEND_ERR                         (HI_S32)(0x80450007)
#define HI_ERR_SCI_RECEIVE_ERR                      (HI_S32)(0x80450008)
#define HI_ERR_SCI_NO_ATR                           (HI_S32)(0x80450009)
#define HI_ERR_SCI_PPS_PTYPE_ERR                    (HI_S32)(0x8045000A)
#define HI_ERR_SCI_PPS_FACTOR_ERR                   (HI_S32)(0x8045000B)
#define HI_ERR_SCI_PPS_NOTSUPPORT_ERR               (HI_S32)(0x8045000C)


#define HI_ERR_ETH_NOT_INIT                         (HI_S32)(0x80460001)
#define HI_ERR_ETH_REPEAT_INIT                      (HI_S32)(0x80460002)
#define HI_ERR_ETH_INVALID_POINT                    (HI_S32)(0x80460003)
#define HI_ERR_ETH_INVALID_PARA                     (HI_S32)(0x80460004)
#define HI_ERR_ETH_FAILED_INIT                      (HI_S32)(0x80460005)

#define HI_ERR_GPIO_OPEN_ERR                        (HI_S32)(0x80470001)
#define HI_ERR_GPIO_CLOSE_ERR                       (HI_S32)(0x80470002)
#define HI_ERR_GPIO_NOT_INIT                        (HI_S32)(0x80470003)
#define HI_ERR_GPIO_INVALID_PARA                    (HI_S32)(0x80470004)
#define HI_ERR_GPIO_NULL_PTR                        (HI_S32)(0x80470005)
#define HI_ERR_GPIO_INVALID_OPT                     (HI_S32)(0x80470006)
#define HI_ERR_GPIO_FAILED_SETINT                   (HI_S32)(0x80470007)
#define HI_ERR_GPIO_FAILED_SETENABLE                (HI_S32)(0x80470008)
#define HI_ERR_GPIO_FAILED_GETINT                   (HI_S32)(0x80470009)
#define HI_ERR_GPIO_GETINT_TIMEOUT                  (HI_S32)(0x8047000A)
#define HI_ERR_GPIO_INTTYPE_NOT_SUPPORT             (HI_S32)(0x8047000B)
#define HI_ERR_GPIO_NOT_SUPPORT                     (HI_S32)(0x8047000C)
#define HI_ERR_GPIO_FAILED_SETOUTPUTTYPE            (HI_S32)(0x8047000D)
#define HI_ERR_GPIO_FAILED_GETOUTPUTTYPE            (HI_S32)(0x8047000E)

#define HI_ERR_DMAC_NOT_INIT                        (HI_S32)(0x80480001)
#define HI_ERR_DMAC_REPEAT_INIT                     (HI_S32)(0x80480002)
#define HI_ERR_DMAC_INVALID_POINT                   (HI_S32)(0x80480003)
#define HI_ERR_DMAC_INVALID_PARA                    (HI_S32)(0x80480004)
#define HI_ERR_DMAC_FAILED_INIT                     (HI_S32)(0x80480005)
#define HI_ERR_DMAC_FAILED_GETCHANNEL               (HI_S32)(0x80480006)
#define HI_ERR_DMAC_FAILED_MEMTRANS                 (HI_S32)(0x80480007)
#define HI_ERR_DMAC_FAILED_PERTRANS                 (HI_S32)(0x80480008)
#define HI_ERR_DMAC_FAILED_GETSTAT                  (HI_S32)(0x80480009)
#define HI_ERR_DMAC_FAILED_LISTRESET                (HI_S32)(0x8048000A)
#define HI_ERR_DMAC_FAILED_ADDLIST                  (HI_S32)(0x8048000B)
#define HI_ERR_DMAC_FAILED_LISTTRANS                (HI_S32)(0x8048000C)

#define  HI_ERR_PMOC_NOT_INIT                       (HI_S32)(0x80490001)
#define  HI_ERR_PMOC_REPEAT_INIT                    (HI_S32)(0x80490002)
#define  HI_ERR_PMOC_INVALID_POINT                  (HI_S32)(0x80490003)
#define  HI_ERR_PMOC_INVALID_PARA                   (HI_S32)(0x80490004)
#define  HI_ERR_PMOC_FAILED_INIT                    (HI_S32)(0x80490005)
#define  HI_ERR_PMOC_FAILED_MODE                    (HI_S32)(0x80490006)
#define  HI_ERR_PMOC_FAILED_READMODE                (HI_S32)(0x80490007)
#define  HI_ERR_PMOC_FAILED_IRPOWERVAL              (HI_S32)(0x80490008)
#define  HI_ERR_PMOC_FAILED_KEYLEDPOWERVAL          (HI_S32)(0x80490009)
#define  HI_ERR_PMOC_INVALID_MODE                   (HI_S32)(0x8049000A)
#define  HI_ERR_PMOC_FAILED_STANDBY                 (HI_S32)(0x8049000B)
#define  HI_ERR_PMOC_FAILED_SETDEV                  (HI_S32)(0x8049000C)

#define HI_ERR_TUNER_NOT_INIT                       (HI_S32)(0x804A0001)
#define HI_ERR_TUNER_NOT_OPEN                       (HI_S32)(0x804A0002)
#define HI_ERR_TUNER_INVALID_POINT                  (HI_S32)(0x804A0003)
#define HI_ERR_TUNER_INVALID_PARA                   (HI_S32)(0x804A0004)
#define HI_ERR_TUNER_FAILED_INIT                    (HI_S32)(0x804A0005)
#define HI_ERR_TUNER_FAILED_CONNECT                 (HI_S32)(0x804A0006)
#define HI_ERR_TUNER_FAILED_GETSTATUS               (HI_S32)(0x804A0007)
#define HI_ERR_TUNER_FAILED_GETSIGNALSTRENGTH       (HI_S32)(0x804A0008)
#define HI_ERR_TUNER_FAILED_GETBER                  (HI_S32)(0x804A0009)
#define HI_ERR_TUNER_FAILED_GETSNR                  (HI_S32)(0x804A000A)
#define HI_ERR_TUNER_FAILED_SETTSTYPE               (HI_S32)(0x804A000B)
#define HI_ERR_TUNER_FAILED_SELECTTUNER             (HI_S32)(0x804A000C)
#define HI_ERR_TUNER_FAILED_SELECTI2CCHANNEL        (HI_S32)(0x804A000D)
#define HI_ERR_TUNER_FAILED_LOWCONS                 (HI_S32)(0x804A000E)
#define HI_ERR_TUNER_FAILED_NORMALMODE              (HI_S32)(0x804A000F)
#define HI_ERR_TUNER_FAILED_REGRW                   (HI_S32)(0x804A0010)
#define HI_ERR_TUNER_FAILED_SETTUNER                (HI_S32)(0x804A0011)
#define HI_ERR_TUNER_NOT_CONNECT                    (HI_S32)(0x804A0012)
#define HI_ERR_TUNER_INVALID_PORT                   (HI_S32)(0x804A0013)
#define HI_ERR_TUNER_FAILED_SETQAMINSIDE            (HI_S32)(0x804A0014)
#define HI_ERR_TUNER_FAILED_SELECTSYMBOLRATE        (HI_S32)(0x804A0015)
#define HI_ERR_TUNER_FAILED_GETSIGNALQUALITY        (HI_S32)(0x804A0016)
#define HI_ERR_TUNER_FAILED_GETSIGNALINFO           (HI_S32)(0x804A0017)
#define HI_ERR_TUNER_FAILED_BLINDSCAN               (HI_S32)(0x804A0018)
#define HI_ERR_TUNER_FAILED_LNBCTRL                 (HI_S32)(0x804A0019)
#define HI_ERR_TUNER_FAILED_SWITCH                  (HI_S32)(0x804A001A)
#define HI_ERR_TUNER_FAILED_DISEQC                  (HI_S32)(0x804A001B)
#define HI_ERR_TUNER_FAILED_STANDBY                 (HI_S32)(0x804A001C)
#define HI_ERR_TUNER_FAILED_WAKEUP                  (HI_S32)(0x804A001D)
#define HI_ERR_TUNER_FAILED_DISABLE                 (HI_S32)(0x804A001E)
#define HI_ERR_TUNER_FAILED_ENABLE                  (HI_S32)(0x804A001F)
#define HI_ERR_TUNER_FAILED_SETPLPID                (HI_S32)(0x804A0020)
#define HI_ERR_TUNER_FAILED_GETPLPNUM               (HI_S32)(0x804A0021)
#define HI_ERR_TUNER_FAILED_GETPLPTYPE              (HI_S32)(0x804A0022)
#define HI_ERR_TUNER_FAILED_SETTSOUT                (HI_S32)(0x804A0023)

#define HI_ERR_KEYLED_NOT_INIT                      (HI_S32)(0x804B0001)
#define HI_ERR_KEYLED_INVALID_PARA                  (HI_S32)(0x804B0002)
#define HI_ERR_KEYLED_NULL_PTR                      (HI_S32)(0x804B0003)
#define HI_ERR_KEYLED_NO_NEW_KEY                    (HI_S32)(0x804B0004)
#define HI_ERR_KEYLED_TIMEOUT                       (HI_S32)(0x804B0005)
#define HI_ERR_KEYLED_FAILED_SETMODE                (HI_S32)(0x804B0006)
#define HI_ERR_KEYLED_FAILED_DISPLAY                (HI_S32)(0x804B0007)


#define HI_ERR_E2PROM_OPEN_ERR                      (HI_S32)(0x804C0001)
#define HI_ERR_E2PROM_CLOSE_ERR                     (HI_S32)(0x804C0002)
#define HI_ERR_E2PROM_NOT_INIT                      (HI_S32)(0x804C0003)
#define HI_ERR_E2PROM_INVALID_PARA                  (HI_S32)(0x804C0004)
#define HI_ERR_E2PROM_NULL_PTR                      (HI_S32)(0x804C0005)
#define HI_ERR_E2PROM_COPY_DATA_ERR                 (HI_S32)(0x804C0006)
#define HI_ERR_E2PROM_MALLOC_ERR                    (HI_S32)(0x804C0007)


#define  HI_ERR_CIPHER_NOT_INIT                     (HI_S32)(0x804D0001)
#define  HI_ERR_CIPHER_INVALID_HANDLE               (HI_S32)(0x804D0002)
#define  HI_ERR_CIPHER_INVALID_POINT                (HI_S32)(0x804D0003)
#define  HI_ERR_CIPHER_INVALID_PARA                 (HI_S32)(0x804D0004)
#define  HI_ERR_CIPHER_FAILED_INIT                  (HI_S32)(0x804D0005)
#define  HI_ERR_CIPHER_FAILED_GETHANDLE             (HI_S32)(0x804D0006)
#define  HI_ERR_CIPHER_FAILED_RELEASEHANDLE         (HI_S32)(0x804D0007)
#define  HI_ERR_CIPHER_FAILED_CONFIGAES             (HI_S32)(0x804D0008)
#define  HI_ERR_CIPHER_FAILED_CONFIGDES             (HI_S32)(0x804D0009)
#define  HI_ERR_CIPHER_FAILED_ENCRYPT               (HI_S32)(0x804D000A)
#define  HI_ERR_CIPHER_FAILED_DECRYPT               (HI_S32)(0x804D000B)
#define  HI_ERR_CIPHER_BUSY                         (HI_S32)(0x804D000C)


#define  HI_ERR_CA_OPEN_ERR                         (HI_S32)(0x804E0001)
#define  HI_ERR_CA_CLOSE_ERR                        (HI_S32)(0x804E0002)
#define  HI_ERR_CA_NOT_INIT                         (HI_S32)(0x804E0003)
#define  HI_ERR_CA_COPY_DATA_ERR                    (HI_S32)(0x804E0004)
#define  HI_ERR_CA_INVALID_PARA                     (HI_S32)(0x804E0005)
#define  HI_ERR_CA_WAIT_TIMEOUT                     (HI_S32)(0x804E0006)
#define  HI_ERR_CA_CW_DECRYPT                       (HI_S32)(0x804E0007)
#define  HI_ERR_CA_R2R_DECRYPT                      (HI_S32)(0x804E0008)
#define  HI_ERR_CA_R2R_ENCRYPT                      (HI_S32)(0x804E0009)
#define  HI_ERR_CA_SETPARAM_AGAIN	                (HI_S32)(0x804E000A)
#define  HI_ERR_CA_DBG_INERR 		                (HI_S32)(0x804E000B)
#define  HI_ERR_CA_NOT_CONFIG                       (HI_S32)(0x804E000C)
#define  HI_ERR_CA_LPK_DECRYPT                      (HI_S32)(0x804E000D)
#define  HI_ERR_CA_NOT_SUPPORT                      (HI_S32)(0x804E000E)
#define  HI_ERR_CA_SWPK_ENCRYPT                     (HI_S32)(0x804E000F)

#define  HI_ERR_C51_COPY_DATA_ERR                   (HI_S32)(0x804F0001)
#define  HI_ERR_C51_INVALID_PARAM                   (HI_S32)(0x804F0002)

#define  HI_ERR_CI_NOT_INIT                         (HI_S32)(0x80500001)
#define  HI_ERR_CI_OPEN_ERR                         (HI_S32)(0x80500002)
#define  HI_ERR_CI_CLOSE_ERR                        (HI_S32)(0x80500003)
#define  HI_ERR_CI_INVALID_PARA                     (HI_S32)(0x80500004)
#define  HI_ERR_CI_NO_MEMORY                        (HI_S32)(0x80500005)
#define  HI_ERR_CI_TIMEOUT                          (HI_S32)(0x80500006)
#define  HI_ERR_CI_REG_READ_ERR                     (HI_S32)(0x80500007)
#define  HI_ERR_CI_REG_WRITE_ERR                    (HI_S32)(0x80500008)
#define  HI_ERR_CI_IO_READ_ERR                      (HI_S32)(0x80500009)
#define  HI_ERR_CI_IO_WRITE_ERR                     (HI_S32)(0x8050000A)
#define  HI_ERR_CI_ATTR_READ_ERR                    (HI_S32)(0x8050000B)
#define  HI_ERR_CI_ATTR_WRITE_ERR                   (HI_S32)(0x8050000C)
#define  HI_ERR_CI_CANNOT_POWEROFF                  (HI_S32)(0x8050000D)
#define  HI_ERR_CI_PCCD_DEVICE_BUSY                 (HI_S32)(0x8050000E)
#define  HI_ERR_CI_PCCD_CIS_READ                    (HI_S32)(0x8050000F)
#define  HI_ERR_CI_UNSUPPORT                        (HI_S32)(0x80500010)
#define  HI_ERR_CI_UNKONWN                          (HI_S32)(0x80500011)

#define HI_ERR_PDM_DEV_NOT_EXIST                    (HI_S32)(0x80520001)
#define HI_ERR_PDM_NOT_DEVICE                       (HI_S32)(0x80520002)
#define HI_ERR_PDM_DEV_OPEN_ERR                     (HI_S32)(0x80520003)
#define HI_ERR_PDM_DEV_NOT_INIT                     (HI_S32)(0x80520004)
#define HI_ERR_PDM_PTR_NULL                         (HI_S32)(0x80520005)
#define HI_ERR_PDM_PARAM_INVALID                    (HI_S32)(0x80520006)
#define HI_ERR_PDM_GET_MTDINFO_ERR                  (HI_S32)(0x80520007)
#define HI_ERR_PDM_MTD_OPEN                         (HI_S32)(0x80520008)
#define HI_ERR_PDM_MTD_CLOSE                        (HI_S32)(0x80520009)
#define HI_ERR_PDM_MTD_READ                         (HI_S32)(0x80520010)
#define HI_ERR_PDM_MTD_WRITE                        (HI_S32)(0x80520011)
#define HI_ERR_PDM_MTD_GETINFO                      (HI_S32)(0x80520012)
#define HI_ERR_PDM_MTD_ERASE                        (HI_S32)(0x80520013)
#define HI_ERR_PDM_MEM_ALLC                         (HI_S32)(0x80520014)
#define HI_ERR_PDM_INVALID_OPT                      (HI_S32)(0x80520015)
#define HI_ERR_PDM_GET_DEVINFO_ERR                  (HI_S32)(0x80510016)

/** @} */  /*! <!-- Macro Definition end */



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __HI_UNF_MPI_ERRORCODE_H__ */

