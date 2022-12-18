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
 * \brief Describes the information about the audio codec. CNcomment:提供AUDIO_CODEC的相关信息
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
/** CNcomment:HA format 定义 */
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
/**CNcomment:定义HA codec 最大音频通道 */
#define HA_AUDIO_MAXCHANNELS 8

/************************************ Struct *************************************/

/**Define the error codes of an HA codec.*/
/**CNcomment:定义HA codec 错误码 */
typedef enum hiHA_ERRORTYPE_E
{
    HA_ErrorNone = 0,

    HA_ErrorInsufficientResources = (HI_S32) 0x80001000,/**<The device fails to be created due to insufficient resources.*/ /**<CNcomment:资源不够，创建设备失败 */

    HA_ErrorInvalidParameter = (HI_S32) 0x80001001, /**<The input parameter is invalid.*/ /**<CNcomment:输入参数非法 */

    HA_ErrorStreamCorrupt = (HI_S32) 0x80001002, /**<The decoding fails due to incorrect input streams.*/ /**<CNcomment:输入码流错误，解码失败 */

    HA_ErrorNotEnoughData = (HI_S32) 0x80001003,/**<The decoding ends due to insufficient streams.*/ /**<CNcomment:输入码流不够，退出解码 */

    HA_ErrorDecodeMode = (HI_S32) 0x80001004,/**<The decoding mode is not supported.*/ /**<CNcomment:解码模式不支持 */

	HA_ErrorNotSupportCodec = (HI_S32) 0x80001005,/**<The codec is not supported.*/

    HA_ErrorMax = 0x9FFFFFFF
} HI_HA_ERRORTYPE_E;

/**
 *Definition of the distribution mode of the channels of an HA codec. CNcomment:定义HA codec 声道分布模式
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
 *Definition of the decoding mode of an HA decoder. CNcomment:定义HA 解码器解码模式
 *
 */
typedef enum hiHA_DECODEMODE_E
{
    HD_DEC_MODE_RAWPCM = 0,        /**<PCM decoding mode*/ /**<CNcomment:PCM 解码模式 */
    HD_DEC_MODE_THRU,              /**<SPIDF61937 passthrough decoding mode only, such as AC3/DTS */ /**<CNcomment:透传解码模式 */
    HD_DEC_MODE_SIMUL,             /**<PCM and passthrough decoding mode*/ /**<CNcomment:PCM + 透传解码模式 */
    HD_DEC_MODE_BUTT = 0x7FFFFFFF
} HI_HA_DECODEMODE_E;

/**
 * Definition of the HA codec version. CNcomment:HA codec 版本定义
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
 * Definition of the data types of the PCM module in an HA codec HA codec. CNcomment:pcm 数据类型结构体定义
 *
 */
typedef struct hiHA_PCMMODETYPE_S
{
    HI_U32              u32DesiredOutChannels;/**<Input, number of expected output channels. If the number of original channels is not equal to the number of
                                              expected output channels, the decoded automatically performs down-mixing or up-mixing. In this way, the number of output channels is equal to
                                              the value of u32DesiredOutChannels. 1: mono; 2 stereo*/
                                              /**<CNcomment:IN. 期望输出声道数目. 如果码流原始声道不等于
                                              期望输出声道，解码器自动进行down-mix 或up-mix 处理，使得输出
                                              声道等于u32DesiredOutChannels.  1: mono, 2 for stereo */
    HI_BOOL             bInterleaved;/**<Whether the PCM data is interleaved.
                                     HI_TRUE: interleaved mode (L/R/L/R.. .L/R/L/R)
                                     HI_FALSE: non-interleaved mode (L/L/L.../R/R/R...)*/
                                     /**<CNcomment:IN. PCM 数据是否交织模式
                                     HI_TRUE:  交织模式: L/R/L/R...L/R/L/R
                                     HI_FALSE: 非交织模式: L/L/L......../R/R/R...... */
    HI_U32              u32BitPerSample;/**<Input. Bit width of the PCM data. Only 16-bit or 24-bit width is supported. For the data of 16-bit width, 16-bit memory is used.
                                        For the data of 24-bit width, 32-bit memory is used. The active bits of the 24-bit PCM data are upper bits, and the lower eight bits are padded with 0s.*/
                                        /**<CNcomment:IN. PCM 数据位宽,仅支持16 或24 数据位宽 16bit 位宽占用16bit 内存,
                                        24bit 位宽占用32比特内存.24bit PCM数据有效为在高位，低8 位补0 */
    HI_U32              u32DesiredSampleRate; /**<Input, expected output sampling rate*/ /**<CNcomment:IN. 期望输出采样频率 */
    HI_HA_CHANNELTYPE_E enChannelMapping[HA_AUDIO_MAXCHANNELS]; /**<Input, distribution mode of output channels*/ /**<CNcomment:IN. 输出声道分布模式 */
} HI_HA_PCMMODETYPE_S;

/**
 *Configuration parameters required by an HA codec for creating devices. CNcomment:HA 解码器创建设备的配置参数
 *
 */
typedef struct hiHADECODE_OPENPARAM_S
{
    HI_HA_DECODEMODE_E  enDecMode;  /**<IN.  */
    HI_HA_PCMMODETYPE_S sPcmformat; /**<IN.  */
    HI_VOID *           pCodecPrivateData;/**<Input, pointer to private data. If the decoder does not contain private data, this parameter is set to 0.*/
                                          /**<CNcomment:IN. 指向私有配置结构体的指针，如果解码器没有私有配置，设置为0 */
    HI_U32              u32CodecPrivateDataSize;/**<Input, size of the private data. If the decoder does not contain private data, this parameter is set to 0.*/
                                                /**<CNcomment:IN. 私有结构体大小, 如果解码器没有私有配置，设置为0 */
} HI_HADECODE_OPENPARAM_S;

typedef struct
{
    HI_U32  enCmd;              /* HA_CODEC_GET_DECOPENPARAM_CMD */
    HI_HADECODE_OPENPARAM_S *pstDecodeParams;
} HA_CODEC_GET_DECOPENPARAM_PARAM_S;

/**
 * Input streams of an HA decoder. CNcomment:HA 解码器输入码流结构体
 *
 */
typedef struct hiHADECODE_INPACKET_S
{
    HI_U32  u32PtsMs;  /**<Input, presentation time stamp (PTS) (in ms). Note: The HA decoder must discard this information.*/
    HI_U8  *pu8Data;   /**<Input/output, pointer to input streams. The decoder update this pointer after decoding.*/ /**<CNcomment:IN/OUT. 输入码流指针，解码完成后解码器更新该指针 */
    HI_S32  s32Size;   /**<Input, size (in byte) of input streams*/ /**<CNcomment:IN. 输入码流大小. unit: Byte */
} HI_HADECODE_INPACKET_S;

/**
 *  Output structure of the HA decoder. CNcomment:HA 解码器输出结构体
 *
 */
typedef struct hiHI_HADECODE_OUTPUT_S
{
    HI_S32 *ps32PcmOutBuf;       /**<Input, pointer to the decoded PCM data.
                                  Note: 1) ps32PcmOutBuf must be 32-word aligned.
                                        2) ps32PcmOutBuf is NULL when the decoder is working in HD_DEC_MODE_THRU mode.*/
                                 /**<CNcomment:IN. 指向PCM 解码输出的指针. */

    HI_U32  u32PcmOutBufSize;    /**<Input, size (in byte) of the buffer for storing the decoded PCM data
                                  Note: u32PcmOutBufSize is 0 when the decoder is working in HD_DEC_MODE_THRU mode.*/
                                 /**<CNcomment:IN. PCM 解码输出缓冲区大小. unit:Byte */

    HI_S32 *ps32BitsOutBuf;      /**<Input, pointer to the decoded passthrough data.
                                  Note: 1) ps32BitsOutBuf must be 32-word aligned.
                                        2) ps32BitsOutBuf is NULL when the decoder is working in HD_DEC_MODE_RAWPCM mode.*/
                                 /**<CNcomment:IN. 指向透传解码输出的指针. */

    HI_U32  u32BitsOutBufSize;   /**<Input, size (in byte) of the buffer for storing the decoded passthrough data (IEC61937)
                                  Note: u32BitsOutBufSize is 0 when the decoder is working in HD_DEC_MODE_RAWPCM mode.*/
                                 /**<CNcomment:IN. 透传(IEC61937) 解码输出缓冲区大小. unit:Byte */

    HI_U32  u32PcmOutSamplesPerFrame; /**<Output, number of output sampling points after the PCM data is decoded*/ /**<CNcomment:OUT. 解码Pcm 输出样点数 */
    HI_BOOL bInterleaved;             /**<Output, interleaved mode for PCM decoding*/ /**<CNcomment:OUT. PCM  解码交织模式   */
    HI_U32  u32BitPerSample;          /**<Output, bit per sampling*/ /**<CNcomment:OUT. Bit per sample */
    HI_U32  u32BitsOutBytesPerFrame;  /**<Output, size (in byte) of the passthrough frame*/ /**<CNcomment:OUT. 透传输出帧大小. unit: Byte */
    HI_U32  u32OutChannels;           /**<Output, number of output channels*/ /**<CNcomment:OUT. 输出声道数  */
    HI_U32  u32OutSampleRate;         /**<Output, output sampling rate*/ /**<CNcomment:OUT. 输出采样频率 */
    HI_U32  u32OrgChannels;           /**<Output, number of original channels*/ /**<CNcomment:OUT. 码流原始声道数*/
    HI_U32  u32OrgSampleRate;         /**<Output, original sampling rate*/ /**<CNcomment:OUT. 码流原始采样频率 */
    HI_U32  u32BitRate;               /**<Output, bit rate (in bit/s) of the compressed streams*/ /**<CNcomment:OUT. 码流压缩率unit: bit/S */
} HI_HADECODE_OUTPUT_S;

/**
 *Definition of the HA decoder. CNcomment:HA 解码器设备定义
 *
 */
typedef struct hiHA_DECODE_S
{
    /**<Input, description information about a decoder, such as MP3 or AAC. */
    /**<CNcomment:IN. 解码器描述名字，如MP3,AAC */
    const HI_PCHAR szName;

    /**<Input, decoder ID. Note: This ID is the identifier of a decoder, and must be unique. */
    /**<CNcomment:IN. 解码器标识，注意: 此标识作为解码器唯一身份标识，必须唯一而不能有重复 */
    const HI_U32 enCodecID;

    /**<Input, decoder version. */
    /**<CNcomment:IN. 解码器版本描述 */
    const HI_HAAUDIO_VERSIONTYPE_U uVersion;

    /**<Input, detailed information about a decoder. */
    /**<CNcomment:IN. 解码器详细描述信息 */
    const HI_PCHAR pszDescription;

    /**<Output, pointer to the next decoder. This member variable is maintained by the client that calls the HA codec. Therefore, the developers of the HA decoder
        can ignore this member variable. */
    /**<CNcomment:OUT. 指向下个解码器设备的指针.  该成员变量由调用HA Codec 的客户端维护, HA 解码器开发者可以忽略该成员 */
    struct hiHA_DECODE_S *pstNext;

    /**<Output, pointer to the dll symbol of an HA decoder. This member variable is maintained by the client that calls the HA codec. Therefore, the developers of the HA decoder
        can ignore this member variable. */
    /**<CNcomment:OUT. Pointer to dll symbol of the HA deocder.   该成员变量由调用HA Codec 的客户端维护, HA 解码器开发者可以忽略该成员 */
    HI_VOID  * pDllModule;

    /**<Initializes a decoder.
        @param [out] phDecoder
            pointer of the decoder handle
        @param [in] pstOpenParam
            pointer of the open params
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:解码器初始化 */
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
    /**<CNcomment:解码器去初始化 */
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
    /**<CNcomment:解码器动态配置方法。用户可以在解码器运行时调用该接口 */
    HI_HA_ERRORTYPE_E (*DecSetConfig)(HI_VOID * hDecoder, HI_VOID * pstConfigStructure);

    /**<Maximum size of the buffer required for storing the PCM data decoded by the decoder. The memory needs to be allocated based on the size on the client.
        @param [in] hDecoder
            the decoder handle
        @param [in/out] pu32OutSizes
            pointer to the max size of the pcm audio frame. unit:Byte
        @return HA_ErrorNone
            If the command successfully executes, the return code will be
            HA_ErrorNone.  Otherwise the appropriate HI_HA_ERRORTYPE_E Error will be returned. */
    /**<CNcomment:解码器PCM  输出所需最大缓冲区size. 客户端需要根据该方法分配内存 */
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
    /**<CNcomment:解码器透传 输出所需最大缓冲区size. 客户端需要根据该方法分配内存 */
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
    /**<CNcomment:解码器解码一帧方法*/
    HI_HA_ERRORTYPE_E (*DecDecodeFrame)(HI_VOID * hDecoder,
                                        HI_HADECODE_INPACKET_S * pstApkt,
                                        HI_HADECODE_OUTPUT_S * pstAOut);
} HI_HA_DECODE_S;

/**
 *Parameters for creating an HA encoder. CNcomment:HA 编码器创建配置参数
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
