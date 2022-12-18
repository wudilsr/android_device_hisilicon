/******************************************************************************

  Copyright (C), 2001-2011, HiSilicon Technologies Co., Ltd.

 ******************************************************************************
  File Name    : hi_unf_disp.h
  Version       : Initial draft
  Author        : HiSilicon multimedia software group
  Created Date: 2009-12-17
  Description   :
  Change History:
  Date        : 2009-12-17
  Author      : Wan Li (employee ID: 58735)
  Description: This file is created.

*******************************************************************************/

#ifndef __HI_UNF_COMMON_H__
#define __HI_UNF_COMMON_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_common.h"
#include "hi_audio_codec.h"

/*************************** Structure Definition ****************************/
/** \addtogroup     Common for the media domain */
/** @{ */  /** <!--[Common for the media domain] */

/**Defines the stream buffer.*/
/**CNcomment: ������������ṹ�� */
typedef struct hiUNF_STREAM_BUF_S
{
    HI_U8   *pu8Data;        /**<Data pointer*/ /**<CNcomment: ����ָ�� */
    HI_U32  u32Size;         /**<Data size*/ /**<CNcomment: ���ݳ��� */
} HI_UNF_STREAM_BUF_S;

/**Defines the structure of the ES buffer.*/
/**CNcomment: ����ES��������ṹ�� */
typedef struct hiUNF_ES_BUF_S
{
    HI_U8 * pu8Buf;    /**<User-state virtual address of the buffer*/ /**<CNcomment: buffer���û�̬���ַ*/
    HI_U32 u32BufLen;  /**<Buffer length*/ /**<CNcomment: buffer�ĳ���*/
    HI_U32 u32PtsMs;   /**<Presentation time stamp (PTS) value corresponding to the start of the stream. The invalid value is 0xFFFFFFFF.*/
                       /**<CNcomment: ������ʼ����Ӧ��PTSֵ����ЧΪ0xffffffff*/
}HI_UNF_ES_BUF_S;

/**Defines the enum of the audio sample rate.*/
/**CNcomment: ������Ƶ������ö��*/
typedef enum hiUNF_SAMPLE_RATE_E
{
    HI_UNF_SAMPLE_RATE_UNKNOWN=0,       /**<Unknown*/ /**<CNcomment: δ֪����Ƶ�� */
    HI_UNF_SAMPLE_RATE_8K    = 8000,    /**<8 kHz sampling rate*/ /**<CNcomment: 8K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_11K   = 11025,   /**<11.025 kHz sampling rate*/ /**<CNcomment: 11.025K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_12K   = 12000,   /**<12 kHz sampling rate*/ /**<CNcomment: 12K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_16K   = 16000,   /**<16 kHz sampling rate*/ /**<CNcomment: 16K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_22K   = 22050,   /**<22.050 kHz sampling rate*/ /**<CNcomment: 22.050K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_24K   = 24000,   /**<24 kHz sampling rate*/ /**<CNcomment: 24K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_32K   = 32000,   /**<32 kHz sampling rate*/ /**<CNcomment: 32K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_44K   = 44100,   /**<44.1 kHz sampling rate*/ /**<CNcomment: 44.1K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_48K   = 48000,   /**<48 kHz sampling rate*/ /**<CNcomment: 48K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_88K   = 88200,   /**<88.2 kHz sampling rate*/ /**<CNcomment: 88.2K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_96K   = 96000,   /**<96 kHz sampling rate*/ /**<CNcomment: 96K����Ƶ�� */
	HI_UNF_SAMPLE_RATE_176K	 = 176400,	/**<176 kHz sampling rate*/ /**<CNcomment: 176K����Ƶ�� */
    HI_UNF_SAMPLE_RATE_192K  = 192000,  /**<192 kHz sampling rate*/ /**<CNcomment: 192K����Ƶ�� */

    HI_UNF_SAMPLE_RATE_BUTT
}HI_UNF_SAMPLE_RATE_E;

/**Defines the bit depth during audio sampling.*/
/**CNcomment: ������Ƶ����λ��ö��*/
typedef enum hiUNF_BIT_DEPTH_E
{
    HI_UNF_BIT_DEPTH_UNKNOWN =0,/**<Unknown*/ /**<CNcomment: δ֪����λ��  */
    HI_UNF_BIT_DEPTH_8  = 8,    /**< 8-bit depth*/ /**<CNcomment: 8λ����λ��  */
    HI_UNF_BIT_DEPTH_16 = 16,   /**<16-bit depth*/ /**<CNcomment: 16λ����λ�� */
    HI_UNF_BIT_DEPTH_18 = 18,   /**<18-bit depth*/ /**<CNcomment: 18λ����λ�� */
    HI_UNF_BIT_DEPTH_20 = 20,   /**<20-bit depth*/ /**<CNcomment: 20λ����λ�� */
    HI_UNF_BIT_DEPTH_24 = 24,   /**<24-bit depth*/ /**<CNcomment: 24λ����λ�� */
    HI_UNF_BIT_DEPTH_32 = 32,   /**<32-bit depth*/ /**<CNcomment: 32λ����λ�� */

    HI_UNF_BIT_DEPTH_BUTT
}HI_UNF_BIT_DEPTH_E;

/**Defines the mode of audio channels.*/
/**CNcomment: ������Ƶ����ģʽö��*/
typedef enum hiUNF_TRACK_MODE_E
{
    HI_UNF_TRACK_MODE_STEREO = 0,          /**<Stereo*/ /**<CNcomment: ������*/
    HI_UNF_TRACK_MODE_DOUBLE_MONO,         /**<Data is output after being mixed in the audio-left channel and audio-right channel.*/ /**<CNcomment: ����������Ϻ����*/
    HI_UNF_TRACK_MODE_DOUBLE_LEFT,         /**<The audio-left channel and audio-right channel output the data of the audio-left channel.*/ /**<CNcomment: ���������������������*/
    HI_UNF_TRACK_MODE_DOUBLE_RIGHT,        /**<The audio-left channel and audio-right channel output the data of the audio-right channel.*/ /**<CNcomment: ���������������������*/
    HI_UNF_TRACK_MODE_EXCHANGE,            /**<Data is output after being exchanged in the audio-left channel and audio-right channel.*/ /**<CNcomment: �����������ݽ������ */
    HI_UNF_TRACK_MODE_ONLY_RIGHT,          /**<Only the data in the audio-right channel is output.*/ /**<CNcomment: ֻ�������������*/
    HI_UNF_TRACK_MODE_ONLY_LEFT,           /**<Only the data in the audio-left channel is output.*/ /**<CNcomment: ֻ�������������*/
    HI_UNF_TRACK_MODE_MUTED,               /**<Mute*/ /**<CNcomment: ����*/

    HI_UNF_TRACK_MODE_BUTT
} HI_UNF_TRACK_MODE_E;

/**Defines the audio stream format.*/
/**CNcomment: ������Ƶ������ʽö��*/
typedef enum hiUNF_ADEC_STREAM_FMT_E
{
    HI_UNF_ADEC_STRAM_FMT_NONE = 0,     /**<Normal mode.*/ /**<CNcomment: ����ģʽ*/
    HI_UNF_ADEC_STRAM_FMT_PACKET,       /**<Packet mode. In this mode, the decoder can decode the next packet only after processing an entire packet. A packet must correspond to a valid PTS to ensure packet integrity.*/
                                        /**<CNcomment: packet ģʽ�� ��������������һ������packet ����, ���ܽ�����һ��packet
                                            ���롣Ϊ��֤packet �����ԣ�һ��packet �����Ӧһ���Ϸ�PTS */

    HI_UNF_ADEC_STRAM_FMT_BUTT
}UNF_ADEC_STREAM_FMT_E;

/**Defines the attributes of the audio decoder.*/
/**CNcomment: ������Ƶ���������Խṹ*/
typedef struct hiUNF_ACODEC_ATTR_S{
    HI_U32        enType;                    /**<Audio decoder type*/ /**<CNcomment: ��Ƶ��������*/
    HI_HADECODE_OPENPARAM_S stDecodeParam;   /**<Audio decoder parameter*/ /**<CNcomment: ��Ƶ�������*/
	UNF_ADEC_STREAM_FMT_E enFmt;             /**<Audio stream format parameter*/ /**<CNcomment: ��Ƶ������ʽ����*/

}HI_UNF_ACODEC_ATTR_S;

/**Defines the attributes of audio encoder.*/
/**CNcomment: ������Ƶ���������Խṹ*/
typedef struct hiUNF_AENC_ATTR_S
{
    HI_U32         enAencType;              /**<Audio encoder type*/ /**<CNcomment: ��Ƶ��������*/
    HI_HAENCODE_OPENPARAM_S   sOpenParam;   /**<Audio encoder parameter*/ /**<CNcomment: ��Ƶ�������*/
}HI_UNF_AENC_ATTR_S;

/**Defines the information about audio streams.*/
/**CNcomment: ������Ƶ������Ϣ�ṹ*/
typedef struct hiUNF_ACODEC_STREAMINFO_S
{
    HI_U32   enACodecType;                 /**<Audio encoding type*/ /**<CNcomment: ��Ƶ��������*/
    HI_U32               enSampleRate;     /**<Audio sampling rate*/ /**<CNcomment: ��Ƶ������*/
    HI_UNF_BIT_DEPTH_E   enBitDepth;       /**<Bit depth during audio sampling*/ /**<CNcomment: ��Ƶ����λ��*/
}HI_UNF_ACODEC_STREAMINFO_S;

/**Defines the information about audio frames.*/
/**CNcomment: ������Ƶ֡��Ϣ�ṹ*/
typedef struct hiUNF_AO_FRAMEINFO_S
{
    /** s32BitPerSample: (PCM) Data depth, and format of storing the output data
          If the data depth is 16 bits, 16-bit word memory is used.
          If the data depth is greater than 16 bits, 32-bit word memory is used, and data is stored as left-aligned data. That is, the valid data is at upper bits.
     */
    /**CNcomment: s32BitPerSample: (PCM) ����λ������. �����Ÿ�ʽ
          ����16bit:   ռ��16bit word�ڴ�
          ����16bit:   ռ��32bit word�ڴ�, ��������뷽ʽ���(��Ч�����ڸ�λ)
     */
    HI_S32  s32BitPerSample;       /**<Data depth*/ /**<CNcomment: ����λ��*/
    HI_BOOL bInterleaved;          /**<Whether the data is interleaved*/ /**<CNcomment: �����Ƿ�֯*/
    HI_U32  u32SampleRate;         /**<Sampling rate*/ /**<CNcomment: ������*/
    HI_U32  u32Channels;           /**<Number of channels*/ /**<CNcomment: ͨ������*/
    HI_U32  u32PtsMs;              /**<Presentation time stamp (PTS)*/ /**<CNcomment: ʱ���*/
    HI_S32 *ps32PcmBuffer;         /**<Pointer to the buffer for storing the pulse code modulation (PCM) data*/ /**<CNcomment: PCM���ݻ���ָ��*/
    HI_S32 *ps32BitsBuffer;        /**<Pointer to the buffer for storing the stream data*/ /**<CNcomment: �������ݻ���ָ��*/
    HI_U32  u32PcmSamplesPerFrame; /**<Number of sampling points of the PCM data*/ /**<CNcomment: PCM���ݲ���������*/
    HI_U32  u32BitsBytesPerFrame;  /**<IEC61937 data size*/ /**<CNcomment: IEC61937���ݳ���*/
    HI_U32  u32FrameIndex;         /**<Frame ID*/ /**<CNcomment: ֡��� */
} HI_UNF_AO_FRAMEINFO_S;

/**Defines the video norm.*/
/**CNcomment: ������Ƶ��ʽö��*/
typedef enum hiUNF_ENC_FMT_E
{
    HI_UNF_ENC_FMT_1080P_60 = 0,     /**<1080p 60 Hz*/
    HI_UNF_ENC_FMT_1080P_50,         /**<1080p 50 Hz*/
    HI_UNF_ENC_FMT_1080P_30,         /**<1080p 30 Hz*/
    HI_UNF_ENC_FMT_1080P_25,         /**<1080p 25 Hz*/
    HI_UNF_ENC_FMT_1080P_24,         /**<1080p 24 Hz*/

    HI_UNF_ENC_FMT_1080i_60,         /**<1080i 60 Hz*/
    HI_UNF_ENC_FMT_1080i_50,         /**<1080i 60 Hz*/

    HI_UNF_ENC_FMT_720P_60,          /**<720p 60 Hz*/
    HI_UNF_ENC_FMT_720P_50,          /**<720p 50 Hz */

    HI_UNF_ENC_FMT_576P_50,          /**<576p 50 Hz*/
    HI_UNF_ENC_FMT_480P_60,          /**<480p 60 Hz*/

    HI_UNF_ENC_FMT_PAL,              /* B D G H I PAL */
    HI_UNF_ENC_FMT_PAL_N,            /* (N)PAL        */
    HI_UNF_ENC_FMT_PAL_Nc,           /* (Nc)PAL       */

    HI_UNF_ENC_FMT_NTSC,             /* (M)NTSC       */
    HI_UNF_ENC_FMT_NTSC_J,           /* NTSC-J        */
    HI_UNF_ENC_FMT_NTSC_PAL_M,       /* (M)PAL        */

    HI_UNF_ENC_FMT_SECAM_SIN,        /**< SECAM_SIN*/
    HI_UNF_ENC_FMT_SECAM_COS,        /**< SECAM_COS*/

    HI_UNF_ENC_FMT_861D_640X480_60,
    HI_UNF_ENC_FMT_VESA_800X600_60,
    HI_UNF_ENC_FMT_VESA_1024X768_60,
    HI_UNF_ENC_FMT_VESA_1280X720_60,
    HI_UNF_ENC_FMT_VESA_1280X800_60,
    HI_UNF_ENC_FMT_VESA_1280X1024_60,
    HI_UNF_ENC_FMT_VESA_1360X768_60,         /**<Rowe*/
    HI_UNF_ENC_FMT_VESA_1366X768_60,
    HI_UNF_ENC_FMT_VESA_1400X1050_60,        /**<Rowe*/
    HI_UNF_ENC_FMT_VESA_1440X900_60,
    HI_UNF_ENC_FMT_VESA_1440X900_60_RB,
    HI_UNF_ENC_FMT_VESA_1600X900_60_RB,
    HI_UNF_ENC_FMT_VESA_1600X1200_60,
    HI_UNF_ENC_FMT_VESA_1680X1050_60,       /**<Rowe*/
    HI_UNF_ENC_FMT_VESA_1920X1080_60,
    HI_UNF_ENC_FMT_VESA_1920X1200_60,
    HI_UNF_ENC_FMT_VESA_2048X1152_60,
    HI_UNF_ENC_FMT_VESA_CUSTOMER_DEFINE,

    HI_UNF_ENC_FMT_BUTT
}HI_UNF_ENC_FMT_E;

/**Defines the aspect ratio.*/
/**CNcomment: �����߱�ö��*/
typedef enum hiUNF_ASPECT_RATIO_E
{
    HI_UNF_ASPECT_RATIO_UNKNOWN,  /**<Unknown*/ /**<CNcomment: δ֪��߱�*/
    HI_UNF_ASPECT_RATIO_4TO3,     /**<4:3*/ /**<CNcomment: 4��3*/
    HI_UNF_ASPECT_RATIO_16TO9,    /**<16:9*/ /**<CNcomment: 16��9*/
    HI_UNF_ASPECT_RATIO_SQUARE,   /**<Square*/ /**<CNcomment: ������*/
    HI_UNF_ASPECT_RATIO_14TO9,    /**<14:9*/ /**<CNcomment: 14��9*/
    HI_UNF_ASPECT_RATIO_221TO1,   /**<221:100*/ /**<CNcomment: 221��100*/
    HI_UNF_ASPECT_RATIO_ZOME,     /**<Unsupported default, display as rate of width and height of data source*/ /**<CNcomment: Ĭ�ϲ�֧�֣���������Դ��߱���ʾ*/
    HI_UNF_ASPECT_RATIO_FULL,     /**<Unsupported default, display as full screen*/ /**<CNcomment: Ĭ�ϲ�֧�֣�ȫ����ʾ*/
    HI_UNF_ASPECT_RATIO_235TO1,   /**<235:100*/ /**<CNcomment: 235��100*/
    HI_UNF_ASPECT_RATIO_BUTT
}HI_UNF_ASPECT_RATIO_E;

/**Defines the mode of converting the aspect ratio.*/
/**CNcomment: �����߱�ת����ʽö��*/
typedef enum hiUNF_ASPECT_CVRS_E
{
    HI_UNF_ASPECT_CVRS_IGNORE = 0x0,   /**<Ignore*/ /**<CNcomment: ����*/
    HI_UNF_ASPECT_CVRS_LETTERBOX,      /**<Add black borders*/ /**<CNcomment: �Ӻڱ�*/
    HI_UNF_ASPECT_CVRS_PANANDSCAN,     /**<Clip the picture*/ /**<CNcomment: �ü�*/
    HI_UNF_ASPECT_CVRS_COMBINED,       /**<Add black borders and clip the picture*/ /**<CNcomment: �ӺڱߺͲü����*/
    HI_UNF_ASPECT_CVRS_BUTT
} HI_UNF_ASPECT_CVRS_E;

/**Defines the mode of the video decoder.*/
/**CNcomment: ������Ƶ������ģʽö��*/
typedef enum hiUNF_VCODEC_MODE_E
{
    HI_UNF_VCODEC_MODE_NORMAL = 0,   /**<Decode all frames.*/ /**<CNcomment: ������֡*/
    HI_UNF_VCODEC_MODE_IP,           /**<Decode only I frames and P frames.*/ /**<CNcomment: ֻ��IP֡*/
    HI_UNF_VCODEC_MODE_I,            /**<Decode only I frames.*/ /**<CNcomment: ֻ��I֡*/
    HI_UNF_VCODEC_MODE_DROP_INVALID_B,  /**<Decode all frames except the first B frame sequence behind I frames */ /**<CNcomment: ������֡�����˽�����I֡�����B֡*/
    HI_UNF_VCODEC_MODE_BUTT
}HI_UNF_VCODEC_MODE_E;

/**Defines special control operation of decoder*/
/**CNcomment: ���������������������ѡ�� */
typedef enum hiHI_UNF_VCODEC_CTRL_OPTION_E
{
    HI_UNF_VCODEC_CTRL_OPTION_SIMPLE_DPB = 0x1,

} HI_UNF_VCODEC_CTRL_OPTION_E;

/**Defines the decoding capability (resolution) of the decoder.*/
/**CNcomment: �����������������(�ֱ���) */
typedef enum hiUNF_VCODEC_CAP_LEVEL_E
{
    HI_UNF_VCODEC_CAP_LEVEL_NULL = 0, /**<Do not decode.*/ /**<CNcomment: ����Ҫ���� */
    HI_UNF_VCODEC_CAP_LEVEL_QCIF = 0, /**<The resolution of the picture to be decoded is less than or equal to 176x144.*/ /**<CNcomment: �����ͼ���С������176*144 */
    HI_UNF_VCODEC_CAP_LEVEL_CIF,      /**<The resolution of the picture to be decoded less than or equal to 352x288.*/ /**<CNcomment: �����ͼ���С������352*288 */
    HI_UNF_VCODEC_CAP_LEVEL_D1,       /**<The resolution of the picture to be decoded less than or equal to 720x576.*/ /**<CNcomment: �����ͼ���С������720*576 */
    HI_UNF_VCODEC_CAP_LEVEL_720P,     /**<The resolution of the picture to be decoded is less than or equal to 1280x720.*/ /**<CNcomment: �����ͼ���С������1280*720 */
    HI_UNF_VCODEC_CAP_LEVEL_FULLHD,   /**<The resolution of the picture to be decoded is less than or equal to 1920x1080.*/ /**<CNcomment: �����ͼ���С������1920*1080 */
    HI_UNF_VCODEC_CAP_LEVEL_BUTT
} HI_UNF_VCODEC_CAP_LEVEL_E;

/**Defines the stream type supported by the decoder.*/
/**CNcomment: ���������֧�ֵ��������� */
typedef enum hiUNF_VCODEC_TYPE_E
{
    HI_UNF_VCODEC_TYPE_MPEG2,  /**<MPEG2*/
    HI_UNF_VCODEC_TYPE_MPEG4,  /**<MPEG4 DIVX4 DIVX5*/
    HI_UNF_VCODEC_TYPE_AVS,    /**<AVS*/
    HI_UNF_VCODEC_TYPE_H263,   /**<H263*/
    HI_UNF_VCODEC_TYPE_H264,   /**<H264*/
    HI_UNF_VCODEC_TYPE_REAL8,  /**<REAL*/
    HI_UNF_VCODEC_TYPE_REAL9,  /**<REAL*/
    HI_UNF_VCODEC_TYPE_VC1,    /**<VC-1*/
    HI_UNF_VCODEC_TYPE_VP6,    /**<VP6*/
    HI_UNF_VCODEC_TYPE_VP6F,   /**<VP6F*/
    HI_UNF_VCODEC_TYPE_VP6A,   /**<VP6A*/
    HI_UNF_VCODEC_TYPE_MJPEG,  /**<MJPEG*/
    HI_UNF_VCODEC_TYPE_SORENSON, /**<SORENSON SPARK*/
    HI_UNF_VCODEC_TYPE_DIVX3,  /**<DIVX3, not supported*/
    HI_UNF_VCODEC_TYPE_RAW,    /**RAW*/
    HI_UNF_VCODEC_TYPE_JPEG,  /**JPEG��added for VENC*/
    HI_UNF_VCODEC_TYPE_VP8,    /**<VP8*/

    HI_UNF_VCODEC_TYPE_BUTT
}HI_UNF_VCODEC_TYPE_E;

typedef struct hiUNF_VCODEC_VC1_ATTR_S
{
	HI_BOOL  bAdvancedProfile;   /**<Whether the profile is an advanced profile*/ /**<CNcomment: �Ƿ�Advanced Profile*/
	HI_U32   u32CodecVersion;    /**<Version number*/ /**<CNcomment: �汾��*/
}HI_UNF_VCODEC_VC1_ATTR_S;

typedef struct hiUNF_VCODEC_VP6_ATTR_S
{
	HI_BOOL  bReversed;    /**<To reverse a picture, set this parameter to 1. In this cases, set it to 0.*/ /**<CNcomment: ͼ����Ҫ��תʱ��1��������0*/
}HI_UNF_VCODEC_VP6_ATTR_S;

typedef union hiUNF_VCODEC_EXTATTR_U
{
	HI_UNF_VCODEC_VC1_ATTR_S stVC1Attr;
	HI_UNF_VCODEC_VP6_ATTR_S stVP6Attr;
}HI_UNF_VCODEC_EXTATTR_U;

typedef struct hiUNF_VCODEC_COMPRESS_ATTR_S
{
    HI_S32          s32VcmpEn;           /*reserved*/
    HI_S32          s32WatermarkFlag;    /**<Watermark Flag, 1 means enable, others means disable*/ /**<CNcomment: ѹ��ˮӡʹ��, 1: ʹ��, others: ��ʹ��*/
    HI_S32          s32WMStartLine;      /**<Watermark Start Line*/ /**<CNcomment: ˮӡ��ʼ�к�*/
    HI_S32          s32WMEndLine;        /**<Watermark End Line*/ /**<CNcomment: ˮӡ��ֹ�к�*/
}HI_UNF_VCODEC_COMPRESS_ATTR_S;

/**Defines the attributes of a video decoder.*/
/**CNcomment: ������Ƶ���������Խṹ*/
typedef struct hiUNF_VCODEC_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E        enType;          /**<Video encoding type*/ /**<CNcomment: ��Ƶ��������*/
	HI_UNF_VCODEC_EXTATTR_U     unExtAttr;       /**<Extra attributes related to the video encoding type*/ /**<CNcomment: ��Ƶ����������صĶ�������*/
    HI_UNF_VCODEC_MODE_E  	    enMode;          /**<Mode of a video decoder*/ /**<CNcomment: ��Ƶ������ģʽģʽ*/
    HI_UNF_VCODEC_COMPRESS_ATTR_S stCompressAttr;  /**<compress attribute of video decoder*//**<��Ƶ������ѹ������*/
    HI_U32                	    u32ErrCover;     /**<Error concealment threshold of the output frames of a video decoder. The value 0 indicates that no frames are output if an error occurs; the value 100 indicates that all frames are output no matter whether errors occur.*/
                                                 /**<CNcomment: ��Ƶ�����������֡�����������ޣ�0:���ִ��󼴲������100:���ܴ������ȫ�����*/
    HI_U32                	    u32Priority;     /**<Priority of a video decoder. The value range is [1, HI_UNF_VCODEC_MAX_PRIORITY]. The value 0 is a reserved value. If you set the value to 0, no error message is displayed, but the value 1 is used automatically. The smaller the value, the lower the priority.*/
                                                 /**<CNcomment: ��Ƶ���������ȼ�, ȡֵ��Χ: ���ڵ���1��С�ڵ���HI_UNF_VCODEC_MAX_PRIORITY, 0�Ǳ���ֵ������Ϊ0���ᱨ�����ǻ��Զ�ȡֵΪ1,��ֵԽС���ȼ�Խ�� */
    HI_BOOL                     bOrderOutput;    /**<Whether the videos are output by the decoding sequence. You are advised to set this parameter to HI_TRUE in VP mode, and HI_FALSE in other modes.*/
                                                 /**<CNcomment: �Ƿ񰴽����������VPģʽ���Ƽ�����ΪHI_TRUE, һ��ģʽ������ΪHI_FALSE */
    HI_S32                      s32CtrlOptions;  /**<The value is HI_UNF_VCODEC_CTRL_OPTION_E, or the 'or' value of several enum type*/
                                                 /**<CNcomment: ȡֵΪHI_UNF_VCODEC_CTRL_OPTION_E�����߼���ö�ٵ�'��'  */
}HI_UNF_VCODEC_ATTR_S;

/**Defines the advanced attributes of a video decoder.*/
/**CNcomment: ������Ƶ��������ǿ���Խṹ*/
typedef struct hiUNF_VCODEC_ADV_ATTR_S
{
    HI_UNF_VCODEC_TYPE_E  enType;           /**<Video encoding type*/ /**<CNcomment: ��Ƶ��������*/
    HI_UNF_VCODEC_MODE_E  enMode;           /**<Mode of a video decoder*/ /**<CNcomment: ��Ƶ������ģʽģʽ*/
    HI_U32                u32ErrCover;      /**<Error concealment threshold of the output frames of a video decoder. The value 0 indicates that no frames are output if an error occurs; the value 100 indicates that all frames are output no matter whether errors occur.*/
                                            /**<CNcomment: ��Ƶ�����������֡�����������ޣ�0:���ִ��󼴲������100:���ܴ������ȫ�����*/
    HI_U32                u32Priority;      /**<Priority of a video decoder. The value range is [1, HI_UNF_VCODEC_MAX_PRIORITY]. The value 0 is a reserved value. If you set the value to 0, no error message is displayed, but the value 1 is used automatically. The smaller the value, the lower the priority.*/
                                            /**<CNcomment: ��Ƶ���������ȼ�, ȡֵ��Χ: ���ڵ���1��С�ڵ���HI_UNF_VCODEC_MAX_PRIORITY, 0�Ǳ���ֵ������Ϊ0���ᱨ�����ǻ��Զ�ȡֵΪ1,��ֵԽС���ȼ�Խ�� */
    HI_BOOL               bOrderOutput;     /**<Whether the videos are output by the displaying sequence. You are advised to set this parameter to HI_TRUE in VP mode, and HI_FALSE in other modes.*/
                                            /**<CNcomment: �Ƿ񰴽����������VPģʽ���Ƽ�����ΪHI_TRUE, һ��ģʽ������ΪHI_FALSE */
    HI_S32                s32CtrlOptions;   /**<The value is HI_UNF_VCODEC_CTRL_OPTION_E, or the 'or' value of several enum type*/
                                            /**<CNcomment: ȡֵΪHI_UNF_VCODEC_CTRL_OPTION_E�����߼���ö�ٵ�'��'  */
}HI_UNF_VCODEC_ADV_ATTR_S;

/**Defines the sub stream protocol.*/
/**CNcomment: ����������Э���֧ö��*/
typedef enum hiUNF_VIDEO_SUB_STANDARD_E
{
    HI_UNF_VIDEO_SUB_STANDARD_UNKNOWN,       /**<Unknown*/ /**<CNcomment: δ֪Э���֧*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG2_MPEG1,   /**<The MPEG2 protocol family is compatible with MPEG1.*/ /**<CNcomment: MPEG2Э������Լ���MPEG1 */
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_SHV,     /**<The MPEG4 protocol family is compatible with SHV.*/ /**<CNcomment: MPEG4Э������Լ���SHV*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_XVID,    /**<The MPEG4 protocol family includes the sub protocol XVID.*/ /**<CNcomment: MPEG4Э�����XVID��֧*/
    HI_UNF_VIDEO_SUB_STANDARD_MPEG4_DIVX,    /**<The MPEG4 protocol family includes the sub protocol DIVX.*/ /**<CNcomment: MPEG4Э�����DIVX��֧*/

    HI_UNF_VIDEO_SUB_STANDARD_BUTT
}HI_UNF_VIDEO_SUB_STANDARD_E;

/**Defines the video sampling type.*/
/**CNcomment: ������Ƶ��������ö��*/
typedef enum hiUNF_VIDEO_SAMPLE_TYPE_E
{
    HI_UNF_VIDEO_SAMPLE_TYPE_UNKNOWN,                  /**<Unknown*/ /**<CNcomment: δ֪������ʽ*/
    HI_UNF_VIDEO_SAMPLE_TYPE_PROGRESSIVE,              /**<Progressive*/ /**<CNcomment: ������ʽΪ����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INTERLACE,                /**<Interlaced*/ /**<CNcomment: ������ʽΪ����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INFERED_PROGRESSIVE,      /**<Inferred progressive*/ /**<CNcomment: ������ʽΪ�Ʋ�����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_INFERED_INTERLACE,        /**<Inferred interlaced*/ /**<CNcomment: ������ʽΪ�Ʋ����*/

    HI_UNF_VIDEO_SAMPLE_TYPE_BUTT
}HI_UNF_VIDEO_SAMPLE_TYPE_E;

/**Defines the frame rate of the video stream.*/
/**CNcomment: ������Ƶ����֡�ʽṹ*/
typedef struct hiUNF_VCODEC_FRMRATE_S
{
    HI_U32 u32fpsInteger;     /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ���������, fps */
    HI_U32 u32fpsDecimal;     /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*/
                              /**<CNcomment: ������֡�ʵ�С�����֣�����3λ��, fps */
}HI_UNF_VCODEC_FRMRATE_S;

/**Defines the information about video streams.*/
/**CNcomment: ������Ƶ������Ϣ�ṹ*/
typedef struct hiUNF_VCODEC_STREAMINFO_S
{
    HI_UNF_VCODEC_TYPE_E        enVCodecType;   /**<Stream type*/ /**<CNcomment: �������� */
    HI_UNF_VIDEO_SUB_STANDARD_E enSubStandard;  /**<Sub stream protocol*/ /**<CNcomment: ������Э���֧ */
    HI_U32                      u32SubVersion;  /**<Version of the sub stream protocol*/ /**<CNcomment: ������Э��汾�� */
    HI_U32                      u32Profile;     /**<Stream profile*/ /**<CNcomment: ������profile */
    HI_U32                      u32Level;       /**<Stream level*/ /**<CNcomment: ������level */
    HI_UNF_ENC_FMT_E            enDisplayNorm;  /**<Display norm (PAL or NTSC)*/ /**<CNcomment: ��ʾ��׼(P/N) */
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;   /**<Sampling type (progressive or interlaced)*/ /**<CNcomment: ������ʽ(����/����) */
    HI_UNF_ASPECT_RATIO_E       enAspectRatio;  /**<Output aspect ratio*/ /**<CNcomment: �����߱� */

    HI_U32 u32bps;            /**<Bit rate, in kbit/s*/ /**<CNcomment: ����������, Kbps */
    HI_U32 u32fpsInteger;     /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ���������, fps */
    HI_U32 u32fpsDecimal;     /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ�С�����֣�����3λ��, fps */
    HI_U32 u32Width;          /**<Width of the decoded picture*/ /**<CNcomment: ����ͼ��� */
    HI_U32 u32Height;         /**<Height of the decoded picture*/ /**<CNcomment: ����ͼ��� */
    HI_U32 u32DisplayWidth;   /**<Width of the displayed picture*/ /**<CNcomment: ��ʾͼ��� */
    HI_U32 u32DisplayHeight;  /**<Height of the displayed picture*/ /**<CNcomment: ��ʾͼ��� */
    HI_U32 u32DisplayCenterX; /**<Horizontal coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/
                              /**<CNcomment: ��ʾͼ�����ĺ����꣬��ԭʼͼ������Ͻ�Ϊ����ԭ�� */
    HI_U32 u32DisplayCenterY; /**<Vertical coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/
                              /**<CNcomment: ��ʾͼ�����������꣬��ԭʼͼ������Ͻ�Ϊ����ԭ�� */
}HI_UNF_VCODEC_STREAMINFO_S;

/**Defines the information about the video sequence.*/
/**CNcomment: ������Ƶ����������Ϣ�ṹ*/
typedef struct hiUNF_VIDEO_SEQUENCE_INFO_S
{
    HI_U32                      u32Height;          /**<Picture height in the video sequence*/ /**<CNcomment: ��Ƶ������ͼ��ĸ߶�*/
    HI_U32                      u32Width;           /**<Picture width in the video sequence*/ /**<CNcomment: ��Ƶ������ͼ��Ŀ��*/
    HI_UNF_ASPECT_RATIO_E       enAspect;           /**<Picture aspect ratio in the video sequence*/ /**<CNcomment: ��Ƶ������ͼ��Ŀ�߱�*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;       /**<Video sampling type*/ /**<CNcomment: ��Ƶ��������*/
    HI_U32                      u32FrameRate;       /**<Frame rate for playing videos*/ /**<CNcomment: ��Ƶ����֡��*/
    HI_U32                      u32BitRate;         /**<Bit rate for playing videos*/ /**<CNcomment: ��Ƶ���ŵı�����*/
    HI_UNF_VCODEC_TYPE_E        entype;             /**<Video decoding type, including MPEG2, MPEG4, and H.264*/ /**<CNcomment: ��Ƶ�������ͣ�����MPEG2��MPEG4��H.264����*/
    HI_BOOL                     bIsLowDelay;        /**<Low delay*/ /**<CNcomment: �Ƿ���ӳ�*/
    HI_U32                      u32VBVBufferSize;   /**<Buffer size*/ /**<CNcomment: ��������С*/
    HI_U32                      u32StreamID;        /**<Video stream ID*/ /**<CNcomment: ��Ƶ����ID*/
    HI_U32                      u32Profile;         /**<Video decoding profile*/ /**<CNcomment: ��Ƶ�����profile*/
    HI_U32                      u32Level;           /**<Video decoding level*/ /**<CNcomment: ��Ƶ�����level*/
    HI_UNF_ENC_FMT_E            enVideoFormat;      /**<Video format. This format is valid only when VIDEO_MPEGSTANDARD_E is VIDeo_MPEG_STANDARD_ISO_IEC_13818.*/
                                                    /**<CNcomment: ��Ƶ��ʽ��ֻ��VIDEO_MPEGSTANDARD_EΪVIDeo_MPEG_STANDARD_ISO_IEC_13818���ø�ʽ����Ч*/

    /* Valid only if VIDEO_MPEGSTANDARD_E is VIDeo_MPEG_STANDARD_ISO_IEC_13818 */
    HI_U32                      u32FrameRateExtensionN;    /**<Integral part of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ��������֣���λΪfps*/
    HI_U32                      u32FrameRateExtensionD;    /**<Fractional part (calculated to three decimal places) of the frame rate (in frame/s)*/ /**<CNcomment: ������֡�ʵ�С�����֣�����3bit������λΪfps*/
}HI_UNF_VIDEO_SEQUENCE_INFO_S;

/**Defines the profile of video broadcasting.*/
/**CNcomment: ������Ƶ�㲥��profileö��*/
typedef enum hiUNF_VIDEO_BROADCAST_PROFILE_E
{
    HI_UNF_VIDEO_BROADCAST_DVB,        /**<Digital video broadcasting (DVB)*/ /**<CNcomment: ������Ƶ�㲥DVB*/
    HI_UNF_VIDEO_BROADCAST_DIRECTV,    /**<American live broadcast operator DirecTV*/ /**<CNcomment: ����ֱ����Ӫ��DirecTV*/
    HI_UNF_VIDEO_BROADCAST_ATSC,       /**<Advanced Television Systems Committee (ATSC)*/ /**<CNcomment: �Ƚ�������ʽίԱ��ATSC��Advanced Television Systems Committee��*/
    HI_UNF_VIDEO_BROADCAST_DVD,        /**<Digital video disc (DVD)*/ /**<CNcomment: ������Ƶ����*/
    HI_UNF_VIDEO_BROADCAST_ARIB,       /**<Association of Radio Industries and Businesses (ARIB)*/ /**<CNcomment: ���ߵ繤ҵ����ҵЭ����*/
    HI_UNF_VIDEO_BROADCAST_BUTT
}HI_UNF_VIDEO_BROADCAST_PROFILE_E;

/**Defines the position of the user data in the video information.*/
/**CNcomment: ������Ƶ��Ϣ���û����ݵ�λ��ö��*/
typedef enum hiUNF_VIDEO_USER_DATA_POSITION_E
{
    HI_UNF_VIDEO_USER_DATA_POSITION_UNKNOWN,       /**<Unknown*/ /**<CNcomment: δ֪λ��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_SEQ,     /**<The data is parsed from sequences under the MPEG2 protocol.*/ /**<CNcomment: MPEG2Э���£��������н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_GOP,     /**<The data is parsed from the group of pictures (GOP) under the MPEG2 protocol.*/ /**<CNcomment: MPEG2Э���£���GOP��Group Of Pictures���н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG2_FRAME,   /**<The data is parsed from picture frames under the MPEG2 protocol.*/ /**<CNcomment: MPEG2Э���£���ͼ��֡�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VSOS,    /**<The data is parsed from the sequences of visible objects under the MPEG4 protocol.*/ /**<CNcomment: MPEG4Э���£��ӿ��Ӷ��������н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VSO,     /**<The data is parsed from visible objects under the MPEG4 protocol.*/ /**<CNcomment: MPEG4Э���£��ӿ��Ӷ����н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_VOL,     /**<The data is parsed from the video object layer under the MPEG4 protocol.*/ /**<CNcomment: MPEG4Э���£�����Ƶ������н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_MPEG4_GOP,     /**<The data is parsed from the GOP under the MPEG4 protocol.*/ /**<CNcomment: MPEG4Э���£���GOP�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_H264_REG,      /**<The data is parsed from the user_data_regestered_itu_t_t35() syntax under the H.264 protocol.*/ /**<CNcomment: ��H.264Э���user_data_regestered_itu_t_t35()�﷨�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_H264_UNREG,    /**<The data is parsed from the user_data_unregestered() syntax under the H.264 protocol.*/ /**<CNcomment: ��H.264Э���user_data_unregestered()�﷨�н��*/
    HI_UNF_VIDEO_USER_DATA_POSITION_BUTT
}HI_UNF_VIDEO_USER_DATA_POSITION_E;

/**Defines the structure of the user data in the video information.*/
/**CNcomment: ������Ƶ��Ϣ�е��û����ݽṹ*/
typedef struct hiUNF_VIDEO_USERDATA_S
{
    HI_UNF_VIDEO_BROADCAST_PROFILE_E   enBroadcastProfile;   /**<Broadcasting profile of the user data*/ /**<CNcomment: �û����ݵĹ㲥profile*/
    HI_UNF_VIDEO_USER_DATA_POSITION_E  enPositionInStream;   /**<Position of the user data in video streams*/ /**<CNcomment: �û���������Ƶ���е�λ��*/
    HI_U32                             u32Pts;               /**<PTS corresponding to the user data*/ /**<CNcomment: �û����ݶ�Ӧ��ʱ���*/
    HI_U32                             u32SeqCnt;            /**<Sequence ID of the user data*/ /**<CNcomment: �û����ݵ�ǰһ������*/
    HI_U32                             u32SeqFrameCnt;       /**<Frame number of the user data*/ /**<CNcomment: �û����ݵ�ǰһ֡��*/
    HI_U8                              *pu8Buffer;           /**<Initial address of the user data memory, output parameter*/ /**<CNcomment: �û������ڴ����ĳ�ʼ��ַ,�������*/
    HI_U32                             u32Length;            /**<User data size (a multiple of 1 byte)*/ /**<CNcomment: �û����ݵĴ�С����1byteΪ��λ*/
    HI_BOOL                            bBufferOverflow;      /**<Indicate that whether the user data size exceeds the maximum size defined by MAX_USER_DATA_LEN.*/ /**<CNcomment: ��־�û����ݵĳ����Ƿ񳬹���MAX_USER_DATA_LEN��������ֵ*/
}HI_UNF_VIDEO_USERDATA_S;

/**Defines the parameters of format changing */
/**CNcomment: ������ʽ�л�ʱ����ز���*/
typedef struct hiUNF_NORMCHANGE_PARAM_S
{
    HI_UNF_ENC_FMT_E            enNewFormat;			/**<New format*/ /**<CNcomment: �µ���ʽ*/
    HI_U32                      u32ImageWidth;			/**<Width of image*/ /**<CNcomment: ͼ����*/
    HI_U32                      u32ImageHeight;			/**<Height of image*/ /**<CNcomment: ͼ��߶�*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;			/**<Sampling type*//**<CNcomment:��������*/
    HI_U32                      u32FrameRate;			/**<Frame rate*//**<CNcomment:֡��*/
}HI_UNF_NORMCHANGE_PARAM_S;

/**Defines the video format.*/
/**CNcomment: ������Ƶ��ʽö��*/
typedef enum hiUNF_VIDEO_FORMAT_E
{
    HI_UNF_FORMAT_YUV_SEMIPLANAR_422 = 0X10,       /**<The YUV spatial sampling format is 4:2:2.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:2*/
    HI_UNF_FORMAT_YUV_SEMIPLANAR_420 = 0X11,       /**<The YUV spatial sampling format is 4:2:0.*/ /**<CNcomment: YUV�ռ������ʽΪ4:2:0*/
    HI_UNF_FORMAT_YUV_PACKAGE_UYVY,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is UYVY.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪUYVY*/
    HI_UNF_FORMAT_YUV_PACKAGE_YUYV,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YUYV.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪYUYV*/
    HI_UNF_FORMAT_YUV_PACKAGE_YVYU,                /**<The YUV spatial sampling format is package, and the pixel arrangement sequence in the memory is YVYU.*/ /**<CNcomment: YUV�ռ������ʽΪpackage,�ڴ�����ΪYVYU*/
    HI_UNF_FORMAT_YUV_BUTT
}HI_UNF_VIDEO_FORMAT_E;

/**Defines the type of the video frame.*/
/**CNcomment: ������Ƶ֡������ö��*/
typedef enum hiUNF_VIDEO_FRAME_TYPE_E
{
    HI_UNF_FRAME_TYPE_UNKNOWN,   /**<Unknown*/ /**<CNcomment: δ֪��֡����*/
    HI_UNF_FRAME_TYPE_I,         /**<I frame*/ /**<CNcomment: I֡*/
    HI_UNF_FRAME_TYPE_P,         /**<P frame*/ /**<CNcomment: P֡*/
    HI_UNF_FRAME_TYPE_B,         /**<B frame*/ /**<CNcomment: B֡*/
    HI_UNF_FRAME_TYPE_BUTT
}HI_UNF_VIDEO_FRAME_TYPE_E;

/**Defines the video frame/field mode.*/
/**CNcomment: ������Ƶ֡��ģʽö��*/
typedef enum hiUNF_VIDEO_FIELD_MODE_E
{
    HI_UNF_VIDEO_FIELD_ALL,        /**<Frame mode*/ /**<CNcomment: ֡ģʽ*/
    HI_UNF_VIDEO_FIELD_TOP,        /**<Top field mode*/ /**<CNcomment: ����ģʽ*/
    HI_UNF_VIDEO_FIELD_BOTTOM,     /**<Bottom field mode*/ /**<CNcomment: �׳�ģʽ*/
    HI_UNF_VIDEO_FIELD_BUTT
}HI_UNF_VIDEO_FIELD_MODE_E;

/**Defines the playing time of videos.*/
/**CNcomment: ������Ƶ����ʱ��ṹ*/
typedef struct hiUNF_VIDEO_TIMECODE_S
{
    HI_U8   u8Hours;         /**<Hour*/ /**<CNcomment: ʱ*/
    HI_U8   u8Minutes;       /**<Minute*/ /**<CNcomment: ��*/
    HI_U8   u8Seconds;       /**<Second*/ /**<CNcomment: ��*/
    HI_U8   u8Frames;        /**<Number of played frames*/ /**<CNcomment: ����֡��*/
    HI_BOOL bInterpolated;   /**<Whether time is interpolated.*/ /**<CNcomment: �Ƿ񾭹���ֵ*/
}HI_UNF_VIDEO_TIMECODE_S;

/**Defines memory alloc mode for captured picture.*/
/**CNcomment: ���岶��ͼ���ڴ�����ʽ*/
typedef enum hiUNF_CAPTURE_ALLOC_TYPE_E
{
    HI_UNF_CAPTURE_NO_ALLOC,	    /**<no alloc*/ /* *<CNcomment: ��������ڴ�*/
    HI_UNF_CAPTURE_USER_ALLOC,	    /**<user alloc*/ /**<CNcomment: �û�����*/
    HI_UNF_CAPTURE_DRIVER_ALLOC,	/**<driver alloc*/ /**<CNcomment: ��������*/
}HI_UNF_CAPTURE_ALLOC_TYPE_E;

typedef struct hiUNF_CAPTURE_MEM_MODE_S
{
    HI_U32			    u32StartPhyAddr;	    /**<start phy addr*/ /* *<CNcomment: ��ʼ�����ַ*/
    HI_U32			    u32StartUserAddr;       /*<start user addr*/ /*  *<CNcomment: ��ʼ�û���ַ*/
    HI_U32			    u32DataLen;		    /*<len of databuf*/ /*  *<CNcomment: ����������*/
    HI_UNF_CAPTURE_ALLOC_TYPE_E	    enAllocMemType;	    /*<type*/ /*  *<CNcomment: ����*/
}HI_UNF_CAPTURE_MEM_MODE_S;

/**Defines the information about the captured picture.*/
/**CNcomment: ���岶��ͼ����Ϣ�ṹ*/
typedef struct hiUNF_CAPTURE_PICTURE_S
{
    HI_U32                u32TopYStartAddr;      /**<Address of the memory for storing top field Y of the captured picture*/ /**<CNcomment: ��Ų���ͼ��Ķ���Y�ڴ��ַ */
    HI_U32                u32TopCStartAddr;      /**<Address of the memory for storing top field C of the captured picture*/ /**<CNcomment: ��Ų���ͼ��Ķ���C�ڴ��ַ */
    HI_U32                u32BottomYStartAddr;   /**<Address of the memory for storing bottom field Y of the captured picture*/ /**<CNcomment: ��Ų���ͼ��ĵ׳�Y�ڴ��ַ */
    HI_U32                u32BottomCStartAddr;   /**<Address of the memory for storing bottom field C of the captured picture*/ /**<CNcomment: ��Ų���ͼ��ĵ׳�C�ڴ��ַ */
    HI_U32                u32Width;              /**<Width of the captured picture*/ /**<CNcomment: ����ͼ��Ŀ�� */
    HI_U32                u32Height;             /**<Height of the captured picture*/ /**<CNcomment: ����ͼ��ĸ߶� */
    HI_U32                u32Stride;             /**<Stride of the captured picture*/ /**<CNcomment: ����ͼ����о� */
    HI_UNF_VIDEO_FORMAT_E    enVideoFormat;      /**<Color format of the snapshot*/ /**<CNcomment: ���������ɫ��ʽ */
    HI_UNF_VIDEO_FIELD_MODE_E enFieldMode;       /**<Frame/field mode of the captured picture*/ /**<CNcomment: ����ͼ���֡����Ϣ */
    HI_UNF_VIDEO_SAMPLE_TYPE_E  enSampleType;    /**<Progressive/interlaced mode of the captured picture*/ /**<CNcomment: ����ͼ����������Ϣ */
    HI_U32                u32CompressFlag;
    HI_S32                s32CompFrameHeight;
    HI_S32                s32CompFrameWidth;
    HI_UNF_CAPTURE_MEM_MODE_S   stOutAllocMode;
} HI_UNF_CAPTURE_PICTURE_S;

/**Defines the field source of video frames.*/
/**CNcomment: ������Ƶ֡�г���Դö�� */
typedef enum hiUNF_VIDEO_FRAME_COMBINE_E
{
    HI_UNF_VIDEO_FRAME_COMBINE_T0B0,     /**<Both fields are originated from the previous frame.*/ /**<CNcomment: ������������һ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_T0B1,     /**<The top field is originated from the previous frame, and the bottom field is originated from the current frame.*/ /**<CNcomment: ����������һ֡���׳����Ե�ǰ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_T1B0,     /**<The top field is originated from the current frame, and the bottom field is originated from the previous frame.*/ /**<CNcomment: �������Ե�ǰ֡���׳�������һ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_T1B1,     /**<Both fields are originated from the current frame.*/ /**<CNcomment: ���������Ե�ǰ֡*/
    HI_UNF_VIDEO_FRAME_COMBINE_BUTT

}HI_UNF_VIDEO_FRAME_COMBINE_E;

/**Defines 3D frame packing type*/
typedef enum hiUNF_VIDEO_FRAME_PACKING_TYPE_E
{
    HI_UNF_FRAME_PACKING_TYPE_NONE,            /* normal frame, not a 3D frame */
    HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE,   /* side by side */
    HI_UNF_FRAME_PACKING_TYPE_TOP_BOTTOM,     /* top bottom */
    HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED,  /* time interlaced: one frame for left eye, the next frame for right eye */
    HI_UNF_FRAME_PACKING_TYPE_BUTT
}HI_UNF_VIDEO_FRAME_PACKING_TYPE_E;

/** max user data num of each frame*/
#define MAX_USER_DATA_NUM       4
/** max user data length*/
#define MAX_USER_DATA_LEN       256UL

/**Defines the information about video frames.*/
/**CNcomment: ������Ƶ֡��Ϣ�ṹ*/
typedef struct hiUNF_VO_FRAMEINFO_S
{
    HI_UNF_VIDEO_SEQUENCE_INFO_S        stSeqInfo;                /**<Video sequence. When the sequence ID is changed, the information in the data type is valid for the current frame only.*/ /**<CNcomment: ��Ƶ������Ϣ�������кŸı�ʱֻ�Ե�ǰ֡��Ч*/
    HI_U32                              u32FrameIndex;            /**<Frame index ID of a video sequence*/ /**<CNcomment: ��Ƶ�����е�֡������*/
    HI_UNF_VIDEO_FORMAT_E               enVideoFormat;            /**<Video format*/ /**<CNcomment: ��Ƶ��ʽ*/
    HI_UNF_ENC_FMT_E                    enDisplayNorm;            /**<Display norm*/ /**<CNcomment: ���ű�׼*/
    HI_UNF_VIDEO_FRAME_TYPE_E           enFrameType;              /**<Frame type*/ /**<CNcomment: ֡����*/
    HI_UNF_VIDEO_SAMPLE_TYPE_E          enSampleType;             /**<Sampling type*/ /**<CNcomment: ��������*/
    HI_UNF_VIDEO_FIELD_MODE_E           enFieldMode;              /**<Frame or field encoding mode*/ /**<CNcomment: ֡�򳡱���ģʽ*/
    HI_BOOL                             bTopFieldFirst;           /**<Top field first flag*/ /**<CNcomment: �������ȱ�־*/
    HI_UNF_ASPECT_RATIO_E               enAspectRatio;            /**<Picture aspect ratio*/ /**<CNcomment: ͼ���߱�*/
    HI_UNF_VIDEO_FRAME_COMBINE_E        enVideoCombine;           /**<Source of the fields in video frames*/ /**<CNcomment: ��Ƶ֡�г���Դ*/
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E   enFramePackingType;       /**<3D frame packing type*/

    HI_U32                              u32Width;                 /**<Width of the source picture*/ /**<CNcomment: ԭʼͼ���*/
    HI_U32                              u32Height;                /**<Height of the source picture*/ /**<CNcomment: ԭʼͼ���*/
    HI_U32                              u32DisplayWidth;          /**<Width of the displayed picture*/ /**<CNcomment: ��ʾͼ���*/
    HI_U32                              u32DisplayHeight;         /**<Height of the displayed picture*/ /**<CNcomment: ��ʾͼ���*/
    HI_U32                              u32DisplayCenterX;        /**<Horizontal coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: ��ʾ����x���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    HI_U32                              u32DisplayCenterY;        /**<Vertical coordinate of the center of the displayed picture (the upper left point of the source picture serves as the coordinate origin)*/ /**<CNcomment: ��ʾ����y���꣬ԭʼͼ�����Ͻ�Ϊ����ԭ��*/
    HI_U32                              u32ErrorLevel;            /**<Error percentage of a decoded picture, ranging from 0% to 100%*/ /**<CNcomment: һ������ͼ���еĴ��������ȡֵΪ0��100*/
    HI_U32                              u32SeqCnt;                /**<Video sequence ID. The ID of the first frame is numbered 0, and the subsequent ID is increased by 1. When the maximum value is reached, the ID starts from 0 again.*/ /**<CNcomment: ��Ƶ���кţ���0��ʼ������һ֡ͼ����1�������ﵽ���ֵ���0���¼���*/
    HI_U32                              u32SeqFrameCnt;           /**<Picture ID in a video sequence. The ID of the first frame in each sequence is numbered 0*/ /**<CNcomment: ��Ƶ�����е�ͼ���ţ�ÿ�������е�һ֡���Ϊ0*/
    HI_U32                              u32SrcPts;                /**<Original PTS of a video frame*/ /**<CNcomment: ��Ƶ֡��ԭʼʱ���*/
    HI_U32                              u32Pts;                   /**<PTS of a video frame*/ /**<CNcomment: ��Ƶ֡��ʱ���*/
    HI_UNF_VIDEO_TIMECODE_S             stTimeCode;               /**<Playing time of a video frame*/ /**<CNcomment: һ����Ƶ֡�Ĳ���ʱ��ֵ*/

    HI_U32                              u32YAddr;                 /**<Address of the Y component in the current frame*/ /**<CNcomment: ��ǰ֡Y�������ݵĵ�ַ*/
    HI_U32                              u32CAddr;                 /**<Address of the C component in the current frame*/ /**<CNcomment: ��ǰ֡C�������ݵĵ�ַ*/

    HI_U32                              u32LstYAddr;              /**<Address of the Y component in the previous frame*/ /**<CNcomment: ��һ֡Y�������ݵĵ�ַ*/
    HI_U32                              u32LstYCddr;              /**<Address of the C component in the previous frame*/ /**<CNcomment: ��һ֡C�������ݵĵ�ַ*/

    HI_U32                              u32YStride;               /**<Stride of the Y component*/ /**<CNcomment: Y�������ݵĿ��*/
    HI_U32                              u32CStride;               /**<Stride of the C component*/ /**<CNcomment: C�������ݵĿ��*/
    HI_U32                              u32Repeat;                /**<Times of playing a video frame*/ /**<CNcomment: ��Ƶ֡���Ŵ���.*/
    HI_U32                              u32MgcNum;                /**<Magic number of a video frame*/ /**<CNcomment: ��Ƶ֡ħ����*/

    HI_U32                           u32VdecInfo[8];           /* 0~4: VDEC_OPTMALG_INFO_S,  5~6: Y/C kernel-vir addr, 7: reserved */
    HI_U32                           u32CompressFlag;
    HI_S32                           s32CompFrameHeight;
    HI_S32                           s32CompFrameWidth;
}HI_UNF_VO_FRAMEINFO_S;

#pragma pack(4)
/**Change flag bits of the network parameter structures*/
/**CNcomment: ��������ṹ�����־λ */
typedef struct
{
   HI_U32   bit1IPAddr:1;	/**<Change flag of the IP address. It indicates that u32IpLen and u8IpAddr[16] change.*/ /**<CNcomment: ip������, u32IpLen��u8IpAddr[16]�и���*/
   HI_U32   bit1IPPort:1;	/**<Change flag of the IP port. It indicates that u16Ipport changes.*/ /**<CNcomment: ip port������, u16Ipport�и���*/
   HI_U32   bit1IPTos:1;	/**<Change flag of the IP service type. It indicates that u32IPTos and u32Mask change.*/ /**<CNcomment: IP�������ͱ�����,u32IPTos��u32Mask�и���*/
   HI_U32   bit1Vlan:1;		/**<VLAN change flag, reserved. It indicates that u32VlanEn, u32VlanPri, u32VlanPid, and u32Mask change.*/ /**<CNcomment: Vlan������,u32VlanEn,u32VlanPri,u32VlanPid��u32Mask�и��ģ�����*/
   HI_U32   bit1Protocol:1;	/**<Change flag of the protocol type, reserved. Only IPv4 is supported currently.*/ /**<CNcomment: Э�����ͱ����ǣ�Ŀǰֻ֧��IPV4,����*/
   HI_U32   bit25Resv:27;
}HI_UNF_NET_CHANGE_S;

/**Configuration of the network parameter structure*/
/**CNcomment: ������������ṹ */
typedef struct
{
    HI_U32 					  u32IpLen;          /**<Length of the source IP address. The IP address can be 4 bytes (IPv4) or 16 bytes (IPv6). Other values are invalid.*/ /**<CNcomment: source ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
    HI_U8 					  u8IpAddr[16];      /**<Source IP address. The IP address can be 4 bytes (IPv4) or 16 bytes (IPv6), but is not a string. For a 4-byte IP address, 192.168.1.1 for example, each segment occupies one byte.*/ /**<CNcomment: source ip��ַ��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ�������192.168.1.1Ϊ����4�ֽ�����Ϊ192,168,1,1*/
    HI_U16 					  u16Ipport;    	 /**<Source RTP port number. The RTP port number must be an even number, and the corresponding RTCP port number is the RTP port number plus 1.*/ /**<CNcomment: source RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1*/
    HI_U16 					  u16Reserve;    	 /**<Reserved*/ /**<CNcomment: �����ֶ�*/
    HI_U32 					  u32Protocol;       /**<Protocol type, reserved. The value 0x0800 indicates IPv4, and the value 0x86dd indicates IPv6. Only IPv4 is supported currently.*/ /**<CNcomment: Э������,0x0800--IPV4, 0x86dd--IPV6��Ŀǰֻ֧��IPV4������*/
	HI_U32					  u32PayLoadValue;   /**<Payload type*/ /**<CNcomment: �������� */
	HI_UNF_NET_CHANGE_S       stNetChange;       /**<Change flag of network parameters*/ /**<CNcomment: ������������־λ  */

}HI_UNF_VP_NET_PARA_S;
#pragma pack()
/** @} */  /** <!-- ==== Structure Definition End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_UNF_VID_ H*/
