/***********************************************************************************
*              Copyright 2006 - 2006, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_rtp.h
* Description: The RTP module.
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.1       2006-05-10   T41030     NULL         Create this file.
* 2.0       2006-05-08   W54723     NULL         Modify this file.
***********************************************************************************/

#ifndef __HI_RTP_H__
#define __HI_RTP_H__

#include "hi_type.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define HI_ERR_RTP_INVALID_PARA 1
#define HI_ERR_RTP_SOCKET       2
#define HI_ERR_RTP_SEND         3
#define HI_ERR_RTP_REACHMAX     4 /*已经达到能力限制*/
#define HI_ERR_RTP_NOT_ENOUGHMEM 5
#define HI_CHECK_TCPIP_PORT(port) ((port > 0 ) && (port < 35536))

#define VOD_MAX_CHN             4
#define H264_STARTCODE_LEN      4 /* 00 00 00 01 */

#define SET_BITFIELD(field, val, mask, shift) \
   do { \
     (field) &= ~(mask); \
     (field) |= (((val) << (shift)) & (mask)); \
   } while (0)


#define RTP_VERSION    2

/*RTP Payload type define*/
typedef enum hiRTP_PT_E
{
    RTP_PT_ULAW             = 0,        /* mu-law */
    RTP_PT_GSM              = 3,        /* GSM */
    RTP_PT_G723             = 4,        /* G.723 */
    RTP_PT_ALAW             = 8,        /* a-law */
    RTP_PT_G722             = 9,        /* G.722 */
    RTP_PT_S16BE_STEREO     = 10,       /* linear 16, 44.1khz, 2 channel */
    RTP_PT_S16BE_MONO       = 11,       /* linear 16, 44.1khz, 1 channel */
    RTP_PT_MPEGAUDIO        = 14,       /* mpeg audio */
    RTP_PT_JPEG             = 26,       /* jpeg */
    RTP_PT_H261             = 31,       /* h.261 */
    RTP_PT_MPEGVIDEO        = 32,       /* mpeg video */
    RTP_PT_MPEG2TS          = 33,       /* mpeg2 TS stream */
    RTP_PT_H263             = 34,       /* old H263 encapsulation */

    //RTP_PT_PRIVATE          = 96,
    RTP_PT_H264             = 96,       /* hisilicon define as h.264 */
    RTP_PT_G726             = 97,       /* hisilicon define as G.726 */
    RTP_PT_ADPCM            = 98,       /* hisilicon define as ADPCM */
    RTP_PT_DATA             = 100,      /* hisilicon define as md alarm data*/
    RTP_PT_ARM              = 101,      /* hisilicon define as AMR*/
    RTP_PT_MJPEG             = 102,       /* hisilicon define as MJPEG */
    RTP_PT_INVALID          = 127
}RTP_PT_E;



/* op-codes */
#define RTP_OP_PACKETFLAGS  1               /* opcode datalength = 1 */

#define RTP_OP_CODE_DATA_LENGTH     1

/* flags for opcode RTP_OP_PACKETFLAGS */
#define RTP_FLAG_LASTPACKET 0x00000001      /* last packet in stream */
#define RTP_FLAG_KEYFRAME   0x00000002      /* keyframe packet */

#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif

/* total 12Bytes */
typedef struct hiRTP_HDR_S
{

#if (BYTE_ORDER == LITTLE_ENDIAN)
    /* byte 0 */
    HI_U16 cc      :4;   /* CSRC count */
    HI_U16 x       :1;   /* header extension flag */
    HI_U16 p       :1;   /* padding flag */
    HI_U16 version :2;   /* protocol version */

    /* byte 1 */
    HI_U16 pt      :7;   /* payload type */
    HI_U16 marker  :1;   /* marker bit */
#elif (BYTE_ORDER == BIG_ENDIAN)
    /* byte 0 */
    HI_U16 version :2;   /* protocol version */
    HI_U16 p       :1;   /* padding flag */
    HI_U16 x       :1;   /* header extension flag */
    HI_U16 cc      :4;   /* CSRC count */
    /*byte 1*/
    HI_U16 marker  :1;   /* marker bit */
    HI_U16 pt      :7;   /* payload type */
#else
    #error YOU MUST DEFINE BYTE_ORDER == LITTLE_ENDIAN OR BIG_ENDIAN !
#endif


    /* bytes 2, 3 */
    HI_U16 seqno  :16;   /* sequence number */

    /* bytes 4-7 */
    HI_U32 ts;            /* timestamp in ms */

    /* bytes 8-11 */
    HI_U32 ssrc;          /* synchronization source */
} RTP_HDR_S;

typedef struct hiRTSP_ITLEAVED_HDR_S
{
    HI_U8  daollar;      /*8, $:dollar sign(24 decimal)*/
    HI_U8  channelid;    /*8, channel id*/
    HI_U16 resv;         /*16, reseved*/
    HI_U32 payloadLen;   /*16, payload length*/

    RTP_HDR_S rtpHead;   /*rtp head*/

}RTSP_ITLEAVED_HDR_S;

/*rtp field packet*/
#define RTP_HDR_SET_VERSION(pHDR, val)  ((pHDR)->version = val)
#define RTP_HDR_SET_P(pHDR, val)        ((pHDR)->p       = val)
#define RTP_HDR_SET_X(pHDR, val)        ((pHDR)->x       = val)
#define RTP_HDR_SET_CC(pHDR, val)       ((pHDR)->cc      = val)

#define RTP_HDR_SET_M(pHDR, val)        ((pHDR)->marker  = val)
#define RTP_HDR_SET_PT(pHDR, val)       ((pHDR)->pt      = val)

#define RTP_HDR_SET_SEQNO(pHDR, _sn)    ((pHDR)->seqno  = (_sn))
#define RTP_HDR_SET_TS(pHDR, _ts)       ((pHDR)->ts     = (_ts))

#define RTP_HDR_SET_SSRC(pHDR, _ssrc)    ((pHDR)->ssrc  = _ssrc)

#define RTP_HDR_LEN  sizeof(RTP_HDR_S)

/* Sender********************************************************** */

#define RTP_DEFAULT_SSRC 41030

HI_VOID HI_RTSP_ITLV_Packet(HI_U8 * pPackAddr, HI_U32 u32PackLen,
                           HI_U32 u32TimeStamp, HI_U32 marker,
                           RTP_PT_E enPayload,HI_U32 u32Ssrc, HI_U16 u16LastSn);
#if 0
/*send stream*/
HI_S32 HI_RTP_Send(HI_SOCKET s32WritSock,HI_U8* pu8Buff, HI_S32 s32DataLen,
                       struct sockaddr* pstruToAddr);


HI_S32 HI_RTP_AudioPTConvert(HI_U32 aenctype);

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
