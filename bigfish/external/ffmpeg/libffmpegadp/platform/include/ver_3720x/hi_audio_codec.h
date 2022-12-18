/******************************************************************************
Copyright (C), 2001-2021, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_audio_codec.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2009/11/01
Last Modified :
Description   : define audio common data structure
  History       :
  1.Date        : 2009/11/10
    Author      : zgjie
    Modification: Created file
******************************************************************************/

/**
 * \file
 * \brief Describes the information about the audio codec. CNcomment:�ṩAUDIO_CODEC�������Ϣ
 */

/* TODO:

 */

#ifndef __HISI_AUDIO_CODEC_H__
#define __HISI_AUDIO_CODEC_H__

#include "hi_type.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

#define VENDOR_HISI 0x400
#define VENDOR_NONE 0x100


/*
*                HA CODEC_ID defination
*   |      7bit                9bit                3bit                   13bit  |
*   |---vendor---|---format---|---reserved---|---id---|
*/
#define HA_VENDOR_OFFSETK  (32-7)
#define HA_VENDOR_MASK     (0x007fL << HA_VENDOR_OFFSETK)
#define HA_FORMAT_OFFSETK  (32-7-9)
#define HA_FORMAT_MASK     (0x01ffL << HA_FORMAT_OFFSETK)
#define HA_RESERVED_OFFSET (32-7-9-3)
#define HA_RESERVED_MASK   (0x007L << HA_RESERVED_OFFSET)
#define HA_ID_OFFSET       (32-7-9-3-13)
#define HA_ID_MASK         (0x1fffL<< HA_ID_OFFSET)

#define HA_BUILD_CODEC_ID(vendor, format, id) (((((HI_U32)vendor) << HA_VENDOR_OFFSETK) & HA_VENDOR_MASK) | ((((HI_U32)format) << HA_FORMAT_OFFSETK) & HA_FORMAT_MASK) | (((HI_U32)id) & HA_ID_MASK))
#define HA_GET_VENDOR(codec) ((HI_U32)(codec&HA_VENDOR_MASK)>>HA_VENDOR_OFFSETK)
#define HA_GET_FORMAT(codec) ((HI_U32)(codec&HA_FORMAT_MASK)>>HA_FORMAT_OFFSETK)
#define HA_GET_ID(codec)     ((HI_U32)(codec&HA_ID_MASK)>>HA_ID_OFFSET)

/** HA format definition*/
/** CNcomment:HA format ���� */
typedef enum hiHA_FORMAT_E
{
    /* audio format */
    FORMAT_MP2 = 0x000,  //MPEG audio layer 1, 2
    FORMAT_MP3, //MPEG audio layer 1, 2 or 3
    FORMAT_AAC,
    FORMAT_AC3,
    FORMAT_DTS,
    FORMAT_VORBIS,
    FORMAT_DVAUDIO,
    FORMAT_WMAV1,
    FORMAT_WMAV2,
    FORMAT_MACE3,
    FORMAT_MACE6,
    FORMAT_VMDAUDIO,
    FORMAT_SONIC,
    FORMAT_SONIC_LS,
    FORMAT_FLAC,
    FORMAT_MP3ADU,
    FORMAT_MP3ON4,
    FORMAT_SHORTEN,
    FORMAT_ALAC,
    FORMAT_WESTWOOD_SND1,
    FORMAT_GSM,
    FORMAT_QDM2,
    FORMAT_COOK,
    FORMAT_TRUESPEECH,
    FORMAT_TTA,
    FORMAT_SMACKAUDIO,
    FORMAT_QCELP,
    FORMAT_WAVPACK,
    FORMAT_DSICINAUDIO,
    FORMAT_IMC,
    FORMAT_MUSEPACK7,
    FORMAT_MLP,
    FORMAT_GSM_MS, /* as found in WAV */
    FORMAT_ATRAC3,
    FORMAT_VOXWARE,
    FORMAT_APE,
    FORMAT_NELLYMOSER,
    FORMAT_MUSEPACK8,
    FORMAT_SPEEX,
    FORMAT_WMAVOICE,
    FORMAT_WMAPRO,
    FORMAT_WMALOSSLESS,
    FORMAT_ATRAC3P,
    FORMAT_EAC3,
    FORMAT_SIPR,
    FORMAT_MP1,
    FORMAT_TWINVQ,
    FORMAT_TRUEHD,
    FORMAT_MP4ALS,
    FORMAT_ATRAC1,
    FORMAT_BINKAUDIO_RDFT,
    FORMAT_BINKAUDIO_DCT,
	FORMAT_DRA,

    /* various PCM "codecs" */
    FORMAT_PCM = 0x100,
	FORMAT_PCM_BLURAY = 0x121,

    /* various ADPCM codecs */
    FORMAT_ADPCM = 0x130,

    /* AMR */
    FORMAT_AMR_NB = 0x160,
    FORMAT_AMR_WB,
    FORMAT_AMR_AWB,

    /* RealAudio codecs*/
    FORMAT_RA_144 = 0x170,
    FORMAT_RA_288,

    /* various DPCM codecs */
    FORMAT_DPCM = 0x180,

    /* various G.7xx codecs */
    FORMAT_G711 = 0x190,
    FORMAT_G722,
    FORMAT_G7231,
    FORMAT_G726,
    FORMAT_G728,
    FORMAT_G729AB,


    /* support multi codecs */
    FORMAT_MULTI = 0x1f0,

    FORMAT_BUTT = 0x1ff,
} HA_FORMAT_E;

#define HA_CODEC_FORMAT_QUERY_CMD  0x1000
#define HA_CODEC_GET_DECOPENPARAM_CMD  0x1001
#define HA_CODEC_GET_ENCOPENPARAM_CMD  0x1002

/* struct for
   HI_HA_ERRORTYPE_E (*DecSetConfig)(NULL, HI_VOID *pstConfigStructure);
 */
typedef struct
{
    HI_U32  enCmd;              /* HA_CODEC_FORMAT_QUERY_CMD */

    HA_FORMAT_E enFormat;
} HA_CODEC_FORMAT_QUERY_PARAM_S;


/*************************** Structure Definition ****************************/
/** \addtogroup      H_2_2_5 */
/** @{ */  /** <!--  [AUDIO_CODEC] */

/**Define HA codec maximum audio channel*/
/**CNcomment:����HA codec �����Ƶͨ�� */
#define HA_AUDIO_MAXCHANNELS 8

/************************************ Struct *************************************/

/**Define the error codes of an HA codec.*/
/**CNcomment:����HA codec ������ */
typedef enum hiHA_ERRORTYPE_E
{
    HA_ErrorNone = 0,

    HA_ErrorInsufficientResources = (HI_S32) 0x80001000,/**<The device fails to be created due to insufficient resources.*/ /**<CNcomment:��Դ�����������豸ʧ�� */

    HA_ErrorInvalidParameter = (HI_S32) 0x80001001, /**<The input parameter is invalid.*/ /**<CNcomment:��������Ƿ� */

    HA_ErrorStreamCorrupt = (HI_S32) 0x80001002, /**<The decoding fails due to incorrect input streams.*/ /**<CNcomment:�����������󣬽���ʧ�� */

    HA_ErrorNotEnoughData = (HI_S32) 0x80001003,/**<The decoding ends due to insufficient streams.*/ /**<CNcomment:���������������˳����� */

    HA_ErrorDecodeMode = (HI_S32) 0x80001004,/**<The decoding mode is not supported.*/ /**<CNcomment:����ģʽ��֧�� */

	HA_ErrorNotSupportCodec = (HI_S32) 0x80001005,/**<The codec is not supported.*/

    HA_ErrorMax = 0x9FFFFFFF
} HI_HA_ERRORTYPE_E;

/**
 *Definition of the distribution mode of the channels of an HA codec. CNcomment:����HA codec �����ֲ�ģʽ
 *
 */
typedef enum hiHA_CHANNELTYPE_E
{
    HA_AUDIO_ChannelNone = 0x0,    /**< Unused or empty */
    HA_AUDIO_ChannelLF  = 0x1,     /**< Left front */
    HA_AUDIO_ChannelRF  = 0x2,     /**< Right front */
    HA_AUDIO_ChannelCF  = 0x3,     /**< Center front */
    HA_AUDIO_ChannelLS  = 0x4,     /**< Left surround */
    HA_AUDIO_ChannelRS  = 0x5,     /**< Right surround */
    HA_AUDIO_ChannelLFE = 0x6,     /**< Low frequency effects */
    HA_AUDIO_ChannelCS  = 0x7,     /**< Back surround */
    HA_AUDIO_ChannelLR  = 0x8,     /**< Left rear. */
    HA_AUDIO_ChannelRR  = 0x9,     /**< Right rear. */
    HA_AUDIO_ChannelMax = 0x7FFFFFFF
} HI_HA_CHANNELTYPE_E;

/**
 *Definition of the decoding mode of an HA decoder. CNcomment:����HA ����������ģʽ
 *
 */
typedef enum hiHA_DECODEMODE_E
{
    HD_DEC_MODE_RAWPCM = 0,        /**<PCM decoding mode*/ /**<CNcomment:PCM ����ģʽ */
    HD_DEC_MODE_THRU,              /**<SPIDF61937 passthrough decoding mode only, such as AC3/DTS */ /**<CNcomment:͸������ģʽ */
    HD_DEC_MODE_SIMUL,             /**<PCM and passthrough decoding mode*/ /**<CNcomment:PCM + ͸������ģʽ */
    HD_DEC_MODE_BUTT = 0x7FFFFFFF
} HI_HA_DECODEMODE_E;

/**
 * Definition of the HA codec version. CNcomment:HA codec �汾����
 *
 */
typedef union hiHI_HAAUDIO_VERSIONTYPE_U
{
    struct
    {
        HI_U8 u8VersionMajor;      /**< Major version */
        HI_U8 u8VersionMinor;      /**< Minor version */
        HI_U8 u8Revision;          /**< Revision version */
        HI_U8 u8Step;              /**< Step version */
    } s;
    HI_U32 u32Version;
} HI_HAAUDIO_VERSIONTYPE_U;

/**
 * Definition of the data types of the PCM module in an HA codec HA codec. CNcomment:pcm �������ͽṹ�嶨��
 *
 */
typedef struct hiHA_PCMMODETYPE_S
{
    HI_U32              u32DesiredOutChannels;/**<Input, number of expected output channels. If the number of original channels is not equal to the number of
                                              expected output channels, the decoded automatically performs down-mixing or up-mixing. In this way, the number of output channels is equal to
                                              the value of u32DesiredOutChannels. 1: mono; 2 stereo*/
                                              /**<CNcomment:IN. �������������Ŀ. �������ԭʼ����������
                                              ��������������������Զ�����down-mix ��up-mix ����ʹ�����
                                              ��������u32DesiredOutChannels.  1: mono, 2 for stereo */
    HI_BOOL             bInterleaved;/**<Whether the PCM data is interleaved.
                                     HI_TRUE: interleaved mode (L/R/L/R.. .L/R/L/R)
                                     HI_FALSE: non-interleaved mode (L/L/L.../R/R/R...)*/
                                     /**<CNcomment:IN. PCM �����Ƿ�֯ģʽ
                                     HI_TRUE:  ��֯ģʽ: L/R/L/R...L/R/L/R
                                     HI_FALSE: �ǽ�֯ģʽ: L/L/L......../R/R/R...... */
    HI_U32              u32BitPerSample;/**<Input. Bit width of the PCM data. Only 16-bit or 24-bit width is supported. For the data of 16-bit width, 16-bit memory is used.
                                        For the data of 24-bit width, 32-bit memory is used. The active bits of the 24-bit PCM data are upper bits, and the lower eight bits are padded with 0s.*/
                                        /**<CNcomment:IN. PCM ����λ��,��֧��16 ��24 ����λ�� 16bit λ��ռ��16bit �ڴ�,
                                        24bit λ��ռ��32�����ڴ�.24bit PCM������ЧΪ�ڸ�λ����8 λ��0 */
    HI_U32              u32DesiredSampleRate; /**<Input, expected output sampling rate*/ /**<CNcomment:IN. �����������Ƶ�� */
    HI_HA_CHANNELTYPE_E enChannelMapping[HA_AUDIO_MAXCHANNELS]; /**<Input, distribution mode of output channels*/ /**<CNcomment:IN. ��������ֲ�ģʽ */
} HI_HA_PCMMODETYPE_S;

/**
 *Configuration parameters required by an HA codec for creating devices. CNcomment:HA �����������豸�����ò���
 *
 */
typedef struct hiHADECODE_OPENPARAM_S
{
    HI_HA_DECODEMODE_E  enDecMode;  /**<IN.  */
    HI_HA_PCMMODETYPE_S sPcmformat; /**<IN.  */
    HI_VOID *           pCodecPrivateData;/**<Input, pointer to private data. If the decoder does not contain private data, this parameter is set to 0.*/
                                          /**<CNcomment:IN. ָ��˽�����ýṹ���ָ�룬���������û��˽�����ã�����Ϊ0 */
    HI_U32              u32CodecPrivateDataSize;/**<Input, size of the private data. If the decoder does not contain private data, this parameter is set to 0.*/
                                                /**<CNcomment:IN. ˽�нṹ���С, ���������û��˽�����ã�����Ϊ0 */
} HI_HADECODE_OPENPARAM_S;

typedef struct
{
    HI_U32  enCmd;              /* HA_CODEC_GET_DECOPENPARAM_CMD */
    HI_HADECODE_OPENPARAM_S *pstDecodeParams;
} HA_CODEC_GET_DECOPENPARAM_PARAM_S;

/**
 * Input streams of an HA decoder. CNcomment:HA ���������������ṹ��
 *
 */
typedef struct hiHADECODE_INPACKET_S
{
    HI_U32  u32PtsMs;  /**<Input, presentation time stamp (PTS) (in ms). Note: The HA decoder must discard this information.*/
    HI_U8  *pu8Data;   /**<Input/output, pointer to input streams. The decoder update this pointer after decoding.*/ /**<CNcomment:IN/OUT. ��������ָ�룬������ɺ���������¸�ָ�� */
    HI_S32  s32Size;   /**<Input, size (in byte) of input streams*/ /**<CNcomment:IN. ����������С. unit: Byte */
} HI_HADECODE_INPACKET_S;

/**
 *  Output structure of the HA decoder. CNcomment:HA ����������ṹ��
 *
 */
typedef struct hiHI_HADECODE_OUTPUT_S
{
    HI_S32 *ps32PcmOutBuf;       /**<Input, pointer to the decoded PCM data.
                                  Note: 1) ps32PcmOutBuf must be 32-word aligned.
                                        2) ps32PcmOutBuf is NULL when the decoder is working in HD_DEC_MODE_THRU mode.*/
                                 /**<CNcomment:IN. ָ��PCM ���������ָ��. */

    HI_U32  u32PcmOutBufSize;    /**<Input, size (in byte) of the buffer for storing the decoded PCM data
                                  Note: u32PcmOutBufSize is 0 when the decoder is working in HD_DEC_MODE_THRU mode.*/
                                 /**<CNcomment:IN. PCM ���������������С. unit:Byte */

    HI_S32 *ps32BitsOutBuf;      /**<Input, pointer to the decoded passthrough data.
                                  Note: 1) ps32BitsOutBuf must be 32-word aligned.
                                        2) ps32BitsOutBuf is NULL when the decoder is working in HD_DEC_MODE_RAWPCM mode.*/
                                 /**<CNcomment:IN. ָ��͸�����������ָ��. */

    HI_U32  u32BitsOutBufSize;   /**<Input, size (in byte) of the buffer for storing the decoded passthrough data (IEC61937)
                                  Note: u32BitsOutBufSize is 0 when the decoder is working in HD_DEC_MODE_RAWPCM mode.*/
                                 /**<CNcomment:IN. ͸��(IEC61937) ���������������С. unit:Byte */

    HI_U32  u32PcmOutSamplesPerFrame; /**<Output, number of output sampling points after the PCM data is decoded*/ /**<CNcomment:OUT. ����Pcm ��������� */
    HI_BOOL bInterleaved;             /**<Output, interleaved mode for PCM decoding*/ /**<CNcomment:OUT. PCM  ���뽻֯ģʽ   */
    HI_U32  u32BitPerSample;          /**<Output, bit per sampling*/ /**<CNcomment:OUT. Bit per sample */
    HI_U32  u32BitsOutBytesPerFrame;  /**<Output, size (in byte) of the passthrough frame*/ /**<CNcomment:OUT. ͸�����֡��С. unit: Byte */
    HI_U32  u32OutChannels;           /**<Output, number of output channels*/ /**<CNcomment:OUT. ���������  */
    HI_U32  u32OutSampleRate;         /**<Output, output sampling rate*/ /**<CNcomment:OUT. �������Ƶ�� */
    HI_U32  u32OrgChannels;           /**<Output, number of original channels*/ /**<CNcomment:OUT. ����ԭʼ������*/
    HI_U32  u32OrgSampleRate;         /**<Output, original sampling rate*/ /**<CNcomment:OUT. ����ԭʼ����Ƶ�� */
    HI_U32  u32BitRate;               /**<Output, bit rate (in bit/s) of the compressed streams*/ /**<CNcomment:OUT. ����ѹ����unit: bit/S */
} HI_HADECODE_OUTPUT_S;

/**
 *Definition of the HA decoder. CNcomment:HA �������豸����
 *
 */
typedef struct hiHA_DECODE_S
{
    /**<Input, description information about a decoder, such as MP3 or AAC. */
    /**<CNcomment:IN. �������������֣���MP3,AAC */
    const HI_PCHAR szName;

    /**<Input, decoder ID. Note: This ID is the identifier of a decoder, and must be unique. */
    /**<CNcomment:IN. ��������ʶ��ע��: �˱�ʶ��Ϊ������Ψһ��ݱ�ʶ������Ψһ���������ظ� */
    const HI_U32 enCodecID;

    /**<Input, decoder version. */
    /**<CNcomment:IN. �������汾���� */
    const HI_HAAUDIO_VERSIONTYPE_U uVersion;

    /**<Input, detailed information about a decoder. */
    /**<CNcomment:IN. ��������ϸ������Ϣ */
    const HI_PCHAR pszDescription;

    /**<Output, pointer to the next decoder. This member variable is maintained by the client that calls the HA codec. Therefore, the developers of the HA decoder
        can ignore this member variable. */
    /**<CNcomment:OUT. ָ���¸��������豸��ָ��.  �ó�Ա�����ɵ���HA Codec �Ŀͻ���ά��, HA �����������߿��Ժ��Ըó�Ա */
    struct hiHA_DECODE_S *pstNext;

    /**<Output, pointer to the dll symbol of an HA decoder. This member variable is maintained by the client that calls the HA codec. Therefore, the developers of the HA decoder
        can ignore this member variable. */
    /**<CNcomment:OUT. Pointer to dll symbol of the HA deocder.   �ó�Ա�����ɵ���HA Codec �Ŀͻ���ά��, HA �����������߿��Ժ��Ըó�Ա */
    HI_VOID  * pDllModule;

    /**<Initializes a decoder.
        @param [out] phDecoder
            pointer of the decoder handle
        @param [in] pstOpenParam
            pointer of the open params
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:��������ʼ�� */
    HI_HA_ERRORTYPE_E (*DecInit)(HI_VOID * *phDecoder,
                                 const HI_HADECODE_OPENPARAM_S * pstOpenParam);

    /**<Initializes a decoder.
        @param [in] hDecoder
          the decoder handle
        @param [in] pstOpenParam
          pointer of the open params
        @return HA_ErrorNone
          If the command successfully executes, the return code will be
          HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:������ȥ��ʼ�� */
    HI_HA_ERRORTYPE_E (*DecDeInit)(HI_VOID * hDecoder);

    /**<This method is used to configure a decoder dynamically. You can call this API when a decoder works.
        @param [in] hDecoder
            the decoder handle
        @param [in] pstConfigStructure
         pointer to application allocated structure to be used for
        initialization by the decoder.
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E will be returned. */
    /**<CNcomment:��������̬���÷������û������ڽ���������ʱ���øýӿ� */
    HI_HA_ERRORTYPE_E (*DecSetConfig)(HI_VOID * hDecoder, HI_VOID * pstConfigStructure);

    /**<Maximum size of the buffer required for storing the PCM data decoded by the decoder. The memory needs to be allocated based on the size on the client.
        @param [in] hDecoder
            the decoder handle
        @param [in/out] pu32OutSizes
            pointer to the max size of the pcm audio frame. unit:Byte
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:������PCM  ���������󻺳���size. �ͻ�����Ҫ���ݸ÷��������ڴ� */
    HI_HA_ERRORTYPE_E (*DecGetMaxPcmOutSize)(HI_VOID * hDecoder,
                                             HI_U32 * pu32OutSizes);

    /**<Maximum size of the buffer required for storing the passthrough data decoded by the decoder. The memory needs to be allocated based on the size on the client.
        @param [in] hDecoder
            the decoder handle
        @param [in/out] pu32OutSizes
            pointer to the max size of the iec61937 audio frame. unit:Byte
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:������͸�� ���������󻺳���size. �ͻ�����Ҫ���ݸ÷��������ڴ� */
    HI_HA_ERRORTYPE_E (*DecGetMaxBitsOutSize)(HI_VOID * hDecoder,
                                              HI_U32 * pu32OutSizes);

    /**<This method is used to decode a frame.
        @param [in] hDecoder
            the decoder handle
        @param [in/out] pstApkt
            pointer to audio stream packet
        @param [inout] pstAOut
            pointer to audio output
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:����������һ֡����*/
    HI_HA_ERRORTYPE_E (*DecDecodeFrame)(HI_VOID * hDecoder,
                                        HI_HADECODE_INPACKET_S * pstApkt,
                                        HI_HADECODE_OUTPUT_S * pstAOut);
} HI_HA_DECODE_S;

/**
 *Parameters for creating an HA encoder. CNcomment:HA �������������ò���
 *
 */
typedef struct hiHAENCODE_OPENPARAM_S
{
    HI_U32      u32DesiredOutChannels; /**<IN. Number of channels (e.g. 2 for stereo) */
    HI_BOOL     bInterleaved;       /**<IN */
    HI_S32      s32BitPerSample;    /**<IN */
    HI_U32      u32DesiredSampleRate; /**<IN */
    HI_U32      u32SamplePerFrame;  /**<IN. Pcm samples per frame for encoder */
    HI_VOID *   pCodecPrivateData;  /**<IN. Pointer of decoder private open parameters
                                     note: if there is none private parameters, pCodecPrivateData=0  */
    HI_U32      u32CodecPrivateDataSize;/**<IN. Size of decoder private open parameters
                                        note: if there is none private parameters, u32CodecPrivateDataSize=0 */
} HI_HAENCODE_OPENPARAM_S;

/**
 *  HA input pcm  packet struct
 *
 */
typedef struct hiHAENCODE_INPACKET_S
{
    HI_U32  u32PtsMs;      /**<IN  PTS (unit:MS)
                                       Note: HA encoder should discard this infomation */
    HI_U8  *pu8Data;       /**<IN/OUT.  pointer to input auduo pcm data .
                                      note: HA encoder would update pu8Data after encode */
    HI_U32  u32Size;       /**<IN/OUT. size of the input auduo data. unit: Byte */
} HI_HAENCODE_INPACKET_S;

/**
 *  HA encoder output struct
 *
 */
typedef struct hiHAENCODE_OUTPUT_S
{
    HI_S32 *ps32BitsOutBuf;         /**<IN. the pointer to encoded bitstream output buffer.
                                                note: ps32BitsOutBuf must  be word32-aligned */
    HI_U32  u32BitsOutBufSize;      /**<IN. the buffer size of bitstream output buffer. unit:Byte */
    HI_U32  u32BitsOutBytesPerFrame;/**<IN. size of the encoded audio data frame ,unit: Byte  */
    HI_U32  u32BitRate;             /**<IN. compress bit rate of the audio stream */
} HI_HAENCODE_OUTPUT_S;

/**
 *  HA encoder struct define
 *
 */
typedef struct hiHA_ENCODE_S
{
    /**< IN. Description name of audio encoder. */
    const HI_PCHAR szName;

    /**< IN. Codec ID */
    const HI_U32 enCodecID;

    /**< IN. Codec version */
    const HI_HAAUDIO_VERSIONTYPE_U uVersion;

    /**< IN. Description infomation of the audio encoder */
    const HI_PCHAR pszDescription;

    /**< OUT. pointer to next HA deocder.  manager by client. client:The layer of software that invokes the methods of the HA encoder. */
    struct hiHA_ENCODE_S *pstNext;

    /**< OUT. pointer to dll symbol of the HA deocder.  manager by client. */
    HI_VOID  * pDllModule;

    /**< EncodeInit  method will create an instance of andio encoder.
        @param [out] phEncoder
            pointer of the decoder handle
        @param [in] pstOpenParam
            pointer of the open params
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    HI_HA_ERRORTYPE_E (*EncodeInit)(HI_VOID * *phEncoder,
                                    const HI_HAENCODE_OPENPARAM_S * pstOpenParam);

    /**< DecDeInit  method is used to deinitialize the decode. It will free any resources  allocated at
      DecInit.
      @param [in] hEncoder
          the decoder handle
      @param [in] pstOpenParam
          pointer of the open params
      @return HA_ErrorNone
          If the command successfully executes, the return code will be
          HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    HI_HA_ERRORTYPE_E (*EncodeDeInit)(HI_VOID * hEncoder);

    /**< EncodeSetConfig method is used to send one of the configuration  structures to an  encoder.
        EncodeSetConfig can be invoked anytime after the Encoder has been loaded.
        @param [in] hEncoder
            the encoder handle
        @param [in] pstConfigStructure
         pointer to application allocated structure to be used for
        initialization by the encoder.
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E  Error will be returned. */
    HI_HA_ERRORTYPE_E (*EncodeSetConfig)(HI_VOID * hEncoder, HI_VOID * pstConfigStructure);

    /**< DecGetMaxBitsOutSize method is used to get the max output size of one iec61937 audio  frame
        @param [in] hEncoder
            the encoder handle
        @param [in/out] pu32OutSizes
            pointer to the max size of the iec61937 audio frame. unit:Byte
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    HI_HA_ERRORTYPE_E (*EncodeGetMaxBitsOutSize)(HI_VOID * hEncoder,
                                                 HI_U32 * pu32OutSizes);

    /**< EncodeFrame method is used to encode one audio frame
        @param [in] hEncoder
            the encoder handle
        @param [in/out] pstApkt
            pointer to audio stream packet
        @param [inout] pstAOut
            pointer to audio output
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    HI_HA_ERRORTYPE_E (*EncodeFrame)(HI_VOID * hEncoder,
                                     HI_HAENCODE_INPACKET_S * pstApkt,
                                     HI_HAENCODE_OUTPUT_S * pstAOut);
} HI_HA_ENCODE_S;

/** @} */  /** <!-- ==== Structure Definition end ==== */

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif /* #ifndef __HISI_AUDIO_CODEC_H__ */
