/******************************************************************************

  Copyright (C), 2001-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_unf_voip.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/11/16
  Description   :
  History       :
  1.Date        : 2010/11/16
    Author      :
    Modification: Created file

 *******************************************************************************/

/**
 * \file
 * \brief Describes the information about the voice over Internet Protocol (VoIP) engine.CNcomment:提供VOIP语音引擎的相关信息CNend
 */
#ifndef __HI_UNF_VOIP_H__
#define __HI_UNF_VOIP_H__

#include "hi_common.h"
#include "hi_error_voip.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*************************** Structure Definition ****************************/
/** \addtogroup      VOIP */
/** @{ */  /**<!—[VOIP] */


/**Defines the working mode of the VoIP channel.*/
/**CNcomment:定义VOIP 通道工作模式类型 */
typedef enum hiUNF_VOIP_WORKMODE_E
{
    HI_UNF_VOIP_MODE_DTMF  = 0x00,  /**<dual-tone multi-frequency (DTMF) mode of receiving numbers, reserved*/ /**<CNcomment:DTMF收号模式，保留 */
    HI_UNF_VOIP_MODE_VOIVE = 0x01,  /**<Voice mode*/ /**<CNcomment:语音模式 */
    HI_UNF_VOIP_MODE_FAX   = 0x02,  /**<Fax mode, reserved*/ /**<CNcomment:传真模式 ，保留*/
    HI_UNF_VOIP_MODE_MODEM = 0x03,  /**<Modem mode, reserved*/ /**<CNcomment:Modem 模式，保留*/
    HI_UNF_VOIP_MODE_BUTT = 0x4
} HI_UNF_VOIP_WORKMODE_E;

/**Defines the type of the reported event related to the VoIP channel.*/
/**CNcomment:定义VOIP 通道事件上报类型 */
typedef enum hiUNF_VOIP_EVENT_E
{
    HI_UNF_VOIP_CH_EVENT_FAULT,              /**<The channel is faulty.*/ /**<CNcomment:通道故障*/
    HI_UNF_VOIP_CH_EVENT_NORMAL,             /**<The channel is restored to the normal status. This event is not supported.*/ /**<CNcomment:通道恢复正常，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_OPEN_FAILED,        /**<The channel fails to be enabled. This event is not supported.*/ /**<CNcomment:打开通道失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_CLOSE_FAILED,       /**<The channel fails to be disabled. This event is not supported.*/ /**<CNcomment:关闭通道失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_LOCAL_PLAY_END,     /**<Local playing ends.*/ /**<CNcomment:LOCAL PLAY结束*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_PLAY_END,    /**<Remote playing ends.*/  /**<CNcomment:REMOTE PLAY结束*/
    HI_UNF_VOIP_CH_EVENT_FAX_START,          /**<The fax starts. This event is not supported.*/ /**<CNcomment:传真开始，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_FAX_END,            /**<The fax ends. This event is not supported.*/ /**<CNcomment:传真结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_MODEM_START,        /**<The modem starts. This event is not supported.*/ /**<CNcomment:MODEM开始，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_MODEM_END,          /**<The modem ends. This event is not supported.*/ /**<CNcomment:MODEM结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DETECT_DTMF,        /**<DTMF detection.*/ /**<CNcomment:DTMF检测*/
    HI_UNF_VOIP_CH_EVENT_DETECT_FSK,         /**<Frequency shift keying (FSK) detection. This event is not supported.*/ /**<CNcomment:FSK检测，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DETECT_BUSY_TONE,   /**<Busy tone detection. This event is not supported.*/ /**<CNcomment:忙音检测，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM,         /**<Real-time Transport Control Protocol (RTCP) alarm. This event is not supported.*/ /**<CNcomment:RTCP告警，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_GENCALLID_FAILED,   /**<The caller number fails to be displayed. This event is not supported.*/ /**<CNcomment:主叫显示失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_STOPCALLID_FAILED,  /**<The displaying of the caller number fails to be disabled. The event is not supported.*/ /**<CNcomment:停主叫显示失败，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DATA_TONE,          /**<Signal tone related to comfort noise generator (CNG), V8, and V25. This event is not supported.*/ /**<CNcomment:CNG, V8, V25相关信号音，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_FAX_START,   /**<The chip detects that the peer end starts to transmits T38 packet.*/ /**<CNcomment:检测到远端开始发送传真(T38) 报文，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_FSK_END,            /**<The FSK detection ends. This event is not supported.*/ /**<CNcomment:FSK结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_DTMF_END,           /**<The DTMF detection ends. This event is not supported.*/ /**<CNcomment:DTMF结束，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_RTP_STATISTIC,      /**<Real-time Transport Protocol (RTP) statistics. This event is not supported.*/ /**<CNcomment:RTP统计，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM_RESTORE, /**<The quality of service (QoS) alarm is restored. This event is not supported.*/ /**<CNcomment:QOS告警恢复，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_VQM_STATISTIC,      /**<Voice quality monitor (VQM) statistics. This event is not supported.*/ /**<CNcomment:VQM统计，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_PT_CHANGE,          /**<The packet type (PT) changes. This event is not supported.*/ /**<CNcomment:PT change，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_CHIP_FAULT,         /**<The chip is faulty. This event is not supported.*/ /**<CNcomment:DSP Fault，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_CLEAR_RTP,          /**<The RTCP statistics are cleared. This event is not supported.*/ /**<CNcomment:用于上报RTCP统计清零前的统计值，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_ANI_START,          /**<Automatic number identification (ANI) signal detection starts. This event is not supported.*/ /**<CNcomment:ANI信号检测，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_ANI_END,            /**<ANI signal detection ends. This event is not supported.*/ /**<CNcomment:ANI结束事件，暂不支持*/
    HI_UNF_VOIP_CH_EVENT_BUTT
} HI_UNF_VOIP_EVENT_E;


/**
Defines the enumeration type of the attribute ID of the VoIP channel. CNcomment:定义VOIP 通道属性ID枚举类型  CNend
Note: The enumeration type must be consistent with OPEN_CHN_PARA_ENUM in HME_Api.h. CNcomment:注意 : 该枚举类型必须与HME_Api.h中的OPEN_CHN_PARA_ENUM 定义一致。CNend
*/
typedef enum hiUNF_VOIP_ATTR_ID_E
{
    HI_UNF_VOIP_ATTR_ID_MAC = 1,        /**<Configuration parameter of the media access control (MAC) layer. This parameter is not supported.*/ /**<CNcomment:Mac层配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_IPUDP = 2,      /**<Parameter of the IP User Datagram Protocol (UDP) layer. This parameter is not supported.*/ /**<CNcomment:IP UDP层配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_DSP = 3,        /**<common DSP configuration parameter*/ /**<CNcomment:dsp common配置参数 */
    HI_UNF_VOIP_ATTR_ID_EC = 4,         /**<Echo cancellation (EC) configuration parameter*/ /**<CNcomment:ec配置参数 */
    HI_UNF_VOIP_ATTR_ID_JB = 5,         /**<Jitter buffer (JB) configuration parameter*/ /**<CNcomment:jb配置参数 */
    HI_UNF_VOIP_ATTR_ID_VQE = 6,        /**<Voice quality enhancement (VQE) configuration parameter*/ /**<CNcomment:VQE配置参数 */
    HI_UNF_VOIP_ATTR_ID_T38 = 7,        /**<T38 configuration parameter. This parameter is not supported.*/ /**<CNcomment:T38配置参数,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_DTMFINRTP = 8,  /**<DTMF in RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:Dtmf in rtp配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_2198REDRTP = 9, /**< 2198Red RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:2198Red rtp配置参数,暂不支持 */
    HI_UNF_VOIP_ATTR_ID_RTCP = 10,      /**< 2198Red RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:2198Red rtp配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_R2 = 11,        /**< 2198Red RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:2198Red rtp配置参数 ,暂不支持*/
    HI_UNF_VOIP_ATTR_ID_NET = 13,       /**<Network configuration parameter*/ /**<CNcomment:网络配置参数 */
    HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV = 14,  /**<Audio device configuration parameter*/ /**<CNcomment:配置音频设备参数 */
    HI_UNF_VOIP_ATTR_ID_CFG_LOCAL_RECV_DIGITAL = 15,/**<Conifg DTMF receiving sign parameter*/ /**<CNcomment:配置DTMF收号参数 */

    HI_UNF_VOIP_ATTR_ID_BUTT
}HI_UNF_VOIP_ATTR_ID_E;

/**Define voip audio device type. */
/**CNcomment:定义VOIP音频设备枚举类型*/
typedef enum hiUNF_VOIP_AUDIO_DEVICE_E
{
    HI_UNF_VOIP_AUD_DEV_SIO = 0,     /**< SIO */
    HI_UNF_VOIP_AUD_DEV_BLUETOOTH,   /**<Bluetooth*/ /**<CNcomment:蓝牙 */
    HI_UNF_VOIP_AUD_DEV_ALSA,        /**<Audio Device*/ /**<CNcomment:ALSA 音频设备 */
    HI_UNF_VOIP_AUD_DEV_BUTT
}HI_UNF_VOIP_AUDIO_DEVICE_E;

/**Define voip audio device input and output type. */
/**CNcomment:定义VOIP音频设备输入输出类型*/
typedef enum hiUNF_VOIP_AUDIO_DEVICE_TYPE_E
{
    HI_UNF_VOIP_AUD_OUT_DEV = 0,     /**<Audio output device*/ /**<CNcomment:音频输出设备 */
    HI_UNF_VOIP_AUD_IN_DEV,          /**<Audio input device*/ /**<CNcomment:音频输入设备 */
    HI_UNF_VOIP_AUD_DEV_TYPE_BUTT
}HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E;


/**Defines the type-length-value (TLV) head.*/
/**CNcomment:定义TLV头*/
typedef struct hiUNF_VOIP_TLV_HEAD_S
{
    HI_U16  u16BlockType;    /**<Block type. It corresponds to HI_UNF_VOIP_ATTR_ID_E in the data structure of the attribute of the VoIP channel.*/
                             /**<CNcomment:块类型 , VOIP通道属性结构体中，对应枚举类型HI_UNF_VOIP_ATTR_ID_E */
    HI_U16  u16BlockLen;     /**<Block length*/ /**<CNcomment:块长度 , 参数长度*/
}HI_UNF_VOIP_TLV_HEAD_S;

/**Defines the length of the TLV head.*/
/**CNcomment:定义TLV头长度*/
#define HI_NUF_TVL_HEAD_LEN    ((HI_S32)sizeof(HI_UNF_VOIP_TLV_HEAD_S))

/**Flags indicating the change of the structure of the common DSP parameters*/
/**CNcomment:Dsp Common参数结构变更标志位 */
typedef struct hiUNF_DSP_CHANGE_FLAG_S
{
    HI_U32   bit1WorkMode:1;           /**<Reserved, change of the working mode*/ /**<CNcomment:保留, 工作模式变更 */
    HI_U32   bit1ConnectMode:1;        /**<Change of the connection mode*/ /**<CNcomment:连接模式变更 */
    HI_U32   bit1Codec:1;              /**<Encoding change of the local end*/ /**<CNcomment:本端编码变更 */
    HI_U32   bit1RtpPt:1;              /**<Change of the payload type of RTP*/ /**<CNcomment:RTP的Payload type变更 */
    HI_U32   bit1PacketPeriod:1;       /**<Change of the packaging duration of the local end*/ /**<CNcomment:本端打包时长变更 */
    HI_U32   bit1DtmfTransMode:1;      /**<Reserved, change of the DTMF transfer mode*/ /**<CNcomment:保留，DTMF传输模式变更 */
    HI_U32   bit1V34Control:1;         /**<Reserved, change of V34 speed reduction*/ /**<CNcomment:保留，V34降速变更标志 */
    HI_U32   bit25Resv:25;
}HI_UNF_DSP_CHANGE_FLAG_S;

/**Configuration of common DSP parameters*/
/**CNcomment:Dsp Common参数配置 */
typedef struct hiUNF_DSP_CONFIG_BODY_S
{
    HI_U8   u8WorkMode;      /**<Reserved. Working mode of the channel, corresponding to the change flag bit1WorkMode.*/
                             /**<CNcomment:保留, 通道工作模式 对应变更标志 bit1WorkMode */
    HI_U8   u8ConnectMode;   /**<Connection mode, for controlling whether to transmit and receive RTP packets. It corresponds to the change flag bit1ConnectMode.\n
                                 The enumeration type enum TERMINAL_MODE is as follows: 0--Transmit data only; 1--Receive data only; 2--Transmit and receive data; 3--Do not transmit and receive data.*/
                             /**<CNcomment:连接模式, 控制是否发送和接收RTP包, 对应变更标志 bit1ConnectMode,\n
                                 对应枚举类型enum TERMINAL_MODE :0--只发送数据,1--只接收数据,2--同时发送和接收,3--不发送和不接收数据*/
    HI_U16  u16Codec;        /**<Codec type of a VoIP channel, corresponding to the change flag bit1Codec.\n
                                 The enumeration type enum CODER_DECODER is as follows:0--G.711A, 1--G.711Mu, 2--G.722.*/
                             /**<CNcomment:VOIP通道的编解码类型,  对应变更标志 bit1Codec,\n
                                 对应枚举类型enum CODER_DECODER:0--G.711A,1--G.711Mu,2--G.722.*/
    HI_U8   u8RtpPT;         /**<RTP payload type of the transmitted RTP packet head, corresponding to the change flag bit1RtpPt.\n
                                 The enumeration type enum EN_VOIP_MEDIA_PROTOCOL_TYPE is as follows: 0--G.711Mu, 8--G.711A, 9--G.722.\n
                                 Note that the type must be the same as u16Codec.*/
                             /**<CNcomment:发送的RTP报文头中的RTP净荷类型, 对应变更标志 bit1RtpPt ,\n
                                 对应枚举类型enum EN_VOIP_MEDIA_PROTOCOL_TYPE:0 --  G.711Mu, 8--G.711A, 9--G.722 \n
                                 注意必须与u16Codec类型保持一致。*/
    HI_U8   u8PacketPeriod;     /**<Duration for packaging an RTP packet, corresponding to the change bit bit1PacketPeriod. The valid value is 10 ms, 20 ms, 30 ms, 40 ms, 50 ms, or 60 ms.*/
                                /**<CNcomment:RTP打包解包时长，有效值[10,20,30,40,50,60]ms,  对应变更标志 bit1PacketPeriod */
    HI_U8   u8DtmfTransMode;    /**<Reserved. DTMF transfer mode, corresponding to the change flag bit1DtmfTransMode .*/
                                /**<CNcomment:保留，DTMF传输模式 对应变更标志 bit1DtmfTransMode */
    HI_U8   u8V34Control;       /**<Reserved. Whether to support V34 speed reduction, corresponding to bit1V34Control*/
                                /**<CNcomment:保留，是否支持V34降速配置 对应变更标志 bit1V34Control */
}HI_UNF_DSP_CONFIG_BODY_S;


/**Structure of common DSP parameters*/
/**CNcomment:配置Dsp Common参数结构 */
typedef struct hiUNF_VOIP_DSP_CONFIG_PARA_S
{
    HI_UNF_DSP_CHANGE_FLAG_S stChange; /**<Change flag. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                       /**<CNcomment:变更标志位 , 修改通道属性时有效，创建通道时无效*/
    HI_UNF_DSP_CONFIG_BODY_S stBody;   /**<DSP common configuration parameter*/
                                       /**<CNcomment:Dsp Common配置参数 */
}HI_UNF_VOIP_DSP_CONFIG_PARA_S;


/**Flags indicating the change of the structure of the DSP voice parameters*/
/**CNcomment:DSP语音相关参数结构变更标志位 */
typedef struct hiUNF_VOICE_CHANGE_FLAG_S
{
    HI_U32   bit1EcEnable:1;          /**<EC change flag*/ /**<CNcomment:EC变更标志 */
    HI_U32   bit1NlpEnable:1;         /**<Reserved, non-linear Processor (NLP) enable change flag.*/ /**<CNcomment:保留，NLP使能变更标志*/
    HI_U32   bit1NlpMode:1;           /**<Reserved, NLP mode change flag. It cannot be configured.*/ /**<CNcomment:保留，NLP模式变更标志, 不支持配置*/
    HI_U32   bit1VadEnable:1;         /**<Voice activity detector (VAD) parameter change flag*/ /**<CNcomment:Vad参数变更 */
    HI_U32   bit1VadMode:1;           /**<Reserved, VAD mode change mode. It is not supported.*/ /**<CNcomment:保留，Vad模式变更标志, 目前不支持*/
    HI_U32   bit1CngEnable:1;         /**<Reserved, CNG enable change flag.*/ /**<CNcomment:保留，Cng使能变更标志*/
    HI_U32   bit1CngLevel:1;          /**<Reserved, CNG energy change flag.*/ /**<CNcomment:保留，Cng模式变更标志*/
    HI_U32   bit1PlcMode:1;           /**<Reserved, packet loss compensation (PLC) mode change mode. Only one mode is supported.*/ /**<CNcomment:保留，PLC模式变更标志 */
    HI_U32   bit1InputVolume:1;       /**<Input gain change flag*/ /**<CNcomment:输入音量变更 */
    HI_U32   bit1OutputVolume:1;      /**<Output gain change flag*/ /**<CNcomment:输出音量变更 */
    HI_U32   bit1InputMute:1;         /**<Input mute change flag*/ /**<CNcomment:输入静音变更 */
    HI_U32   bit1OutputMute:1;        /**<Output mute change flag*/ /**<CNcomment:输出静音变更 */
    HI_U32   bit1InputGain:1;         /**<Input gain change flag*/ /**<CNcomment:输入增益变更 */
    HI_U32   bit1OutputGain:1;        /**<Output gain change flag*/ /**<CNcomment:输出增益变更 */
    HI_U32   bit18Resv:18;
}HI_UNF_VOICE_CHANGE_FLAG_S;

/**Configuration of DSP voice parameters*/
/**CNcomment:DSP语音相关参数配置 */
typedef struct hiUNF_VOICE_CONFIG_BODY_S
{
    HI_U8   u8EcEnableFlag;     /**<EC enable flag: 0 - EC off; 1 - EC on. It corresponds to the change flag bit1EcEnable.*/
                                /**<CNcomment:回声抑制使能标志: 0 -- EC Off , 1 -- EC On ,  对应变更标志 bit1EcEnable */
    HI_U8   u8NlpEnableFlag;    /**<Reserved, NLP enable flag. It corresponds to the change flag bit1NlpEnable.*/
                                /**<CNcomment:保留， NLP使能标志,  对应变更标志 bit1NlpEnable */
    HI_U8   u8NlpMode;          /**<Reserved, NLP mode. It corresponds to the change bit bit1NlpMode.*/
                                /**<CNcomment:保留，NLP模式,    对应变更标志 bit1NlpMode */
    HI_U8   u8VadEnableFlag;    /**<VAD enable flag: 0 - VAD off; 1 - VAD on. It corresponds to the change flag bit1VadEnable.*/
                                /**<CNcomment:VAD使能标志: 0 -- VAD Off , 1 -- VAD On , 对应变更标志 bit1VadEnable */
    HI_U8   u8VadMode;          /**<Reserved, VAD mode. It corresponds to the change flag bit1VadMode.*/
                                /**<CNcomment:保留，VAD模式,     对应变更标志 bit1VadMode */
    HI_U8   u8CngEnableFlag;    /**<Reserved, CNG enable flag. It corresponds to the change flag bit1CngEnable.*/
                                /**<CNcomment:保留，Cng使能标志,  对应变更标志 bit1CngEnable */
    HI_U8   u8CngLevel;         /**<Reserved, CNG energy. It corresponds to the change bit bit1CngLevel.*/
                                /**<CNcomment:保留，CNG能量,    对应变更标志 bit1CngLevel */
    HI_U8   u8PlcMode;          /**<Reserved, PLC mode. It corresponds to the change bit bit1PlcMode.*/
                                /**<CNcomment:保留，PLC模式,     对应变更标志 bit1PlcMode */
    HI_U8   u8InputVolume;      /**<Input volume. Its value range is [0, 100]. The default value is 100. This parameter corresponds to the change bit bit1InputVolume.*/
                                /**<CNcomment:输入音量 [0 ~ 100] , 缺省值为100 ,  对应变更标志 bit1InputVolume */
    HI_U8   u8OutputVolume;     /**<Output volume. Its value range is [0, 100]. The default value is 100. This parameter corresponds to the change bit bit1OutputVolume.
                                    The sametime to set Volume & Gain, the priority of u8OutputVolume is less than s8OutputGain;
                                    To set Volume & Gain respectively, the last take effect*/
                                /**<CNcomment:输出音量 [0 ~ 100] , 缺省值为100 , 对应变更标志 bit1OutputVolume.
                                    同时设置音量和增益，音量的优先级小于增益; 分别设置音量和增益，后设置的生效 */
    HI_U8   u8InputMute;        /**<Input mute: Input Mute flag. This parameter corresponds to the change bit bit1InputMute.*/
                                /**<CNcomment:输入静音标志 : 0 -- UnMute , 1 -- Mute , 对应变更标志 bit1InputMute */
    HI_U8   u8OutputMute;       /**<Output mute. Input Mute flag. This parameter corresponds to the change bit  bit1OutputMute.*/
                                /**<CNcomment:输出静音标志 : 0 -- UnMute , 1 -- Mute , 对应变更标志 bit1OutputMute */
    HI_S8   s8InputGain;        /**<Input gain. Its gain range is [-70 ~ 0]. The default value is 0. This parameter corresponds to the change bit bit1InputGain.*/
                                /**<CNcomment:输入增益 [-70, 0] , 缺省值为0 ,  对应变更标志 bit1InputGain */
    HI_S8   s8OutputGain;       /**<Output gain. Its value range is [-70 ~ 0]. The default value is 0. This parameter corresponds to the change bit bit1OutputGain.
                                    The sametime to set Volume & Gain, the priority of s8OutputGain is greater than u8OutputVolume;
                                    To set Volume & Gain respectively, the last take effect*/
                                /**<CNcomment:输出增益 [-70, 0] , 缺省值为0 , 对应变更标志 bit1OutputGain.
                                    同时设置音量和增益，增益的优先级大于音量; 分别设置音量和增益，后设置的生效 */
    HI_U16  u16Rsev;
}HI_UNF_VOICE_CONFIG_BODY_S;

/**Structure of DSP voice parameters*/
/**CNcomment:配置dsp语音参数结构 */
typedef struct hiUNF_VOICE_CONFIG_PARA_S
{
    HI_UNF_VOICE_CHANGE_FLAG_S stChange;  /**<Change flag. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                          /**<CNcomment:变更标志位 , 修改通道属性时有效，创建通道时无效*/
    HI_UNF_VOICE_CONFIG_BODY_S stBody;    /**<DSP voice configuration parameter*/ /**<CNcomment:语音配置参数 */
}HI_UNF_VOICE_CONFIG_PARA_S;

/**Flags indicating the change of the structure of JB parameters*/
/**CNcomment:JB参数结构变更标志位 */
typedef struct hiUNF_JB_CHANGE_FLAG_S
{
    HI_U32   bit1JbMode:1;      /**<Change flag of the JB mode*/ /**<CNcomment:JB 模式   变更标志 */
    HI_U32   bit1JbInit:1;      /**<Change flag of the JB initial value*/ /**<CNcomment:JB 初始值 变更标志 */
    HI_U32   bit1JbMax:1;       /**<Change flag of the JB maximum value*/ /**<CNcomment:JB 最大值 变更标志 */
    HI_U32   bit1JbMin:1;       /**<Reserved, change flag of the JB minimum value*/ /**<CNcomment:保留，JB 最小值 变更标志 */
    HI_U32   bit28Resv:28;
}HI_UNF_JB_CHANGE_FLAG_S;

/**JB parameter configuration*/
/**CNcomment:JB参数配置 */
typedef struct hiUNF_JB_CONFIG_BODY_S
{
    HI_U8  u8JbMode;           /**<JB mode: 0 - dynamic JB; 1 - static JB. It corresponds to the change flag bit1JbMode.*/
                               /**<CNcomment:JitterBuffer模式: 0--动态JB , 1--静态JB,  对应变更标志 bit1JbMode */
    HI_U8  u8JbInit;           /**<JB initial value. It ranges from 0 ms to 150 ms and corresponds to the change flag bit1JbInit.*/
                               /**<CNcomment:JitterBuffer的初始值 [0 ~ 150]ms  ,对应变更标志 bit1JbInit */
    HI_U8  u8JbMax;            /**<JB maximum value. It ranges from 0 ms to 150 ms and corresponds to the change flag bit1JbMax.*/
                               /**<CNcomment:JitterBuffer的最大值 [0 ~ 150]ms , 对应变更标志 bit1JbMax */
    HI_U8  u8JbMin;            /**<JB minimum value. It ranges from 0 ms to 150 ms and corresponds to the change flag bit1JbMin.*/
                               /**<CNcomment:保留，JitterBuffer的最小值  [0 ~ 150]ms  ,对应变更标志 bit1JbMin */
}HI_UNF_JB_CONFIG_BODY_S;

/**Structure of JB parameters*/
/**CNcomment:配置JB参数结构 */
typedef struct hiUNF_JB_CONFIG_PARA_S
{
    HI_UNF_JB_CHANGE_FLAG_S stChange;  /**<Change flag. It is invalid when a channel is created and the JB parameters are not processed when channel attributes are modified.*/
                                       /**<CNcomment:变更标志位 ,  创建通道时无效，修改通道属性时不处理JB参数*/
    HI_UNF_JB_CONFIG_BODY_S stBody;    /**<JB configuration parameter*/ /**<CNcomment:JB配置参数 */
}HI_UNF_JB_CONFIG_PARA_S;


/**Flags indicating the change of the structure of VQE parameters*/
/**CNcomment:VQE参数结构变更标志位 */
/**The local end indicates MIC input, and the remote end indicates network input.*/
/**CNcomment:这里的本端是指mic输入,远端是指网络输入*/
typedef struct hiUNF_VQE_CHANGE_FLAG_S
{
    HI_U32   bit1LocalAgcFlag:1;   /**<Change flag of the automatic gain control (AGC) enable flag parameter of the local end*/ /**<CNcomment:本端AGC 使能标志参数 变更标志 */
    HI_U32   bit1LocalAgcValue:1;  /**<Reserved, change flag of the target AGC value of the local end*/ /**<CNcomment:保留，本端AGC 目标值 变更标志 */

    HI_U32   bit1RemoteAgcFlag:1;  /**<Change flag of the AGC enable flag parameter of the remote end*/ /**<CNcomment:远端AGC 使能标志参数 变更标志 */
    HI_U32   bit1RemoteAgcValue:1; /**<Reserved, change flag of the target AGC value of the remote end*/ /**<CNcomment:保留，远端AGC 目标值 变更标志 */

    HI_U32   bit1LocalAnrFlag:1;   /**<Change flag of the automatic noise reduction (ANR) enable flag parameter of the local end*/ /**<CNcomment:本端ANR 使能标志参数 变更标志*/
    HI_U32   bit1LocalAnrValue:1;  /**<Reserved, change flag of the target ANR value of the local end*/ /**<CNcomment:保留，ANR 目标值 变更标志 */

    HI_U32   bit1RemoteAnrFlag:1;  /**<Change flag of the ANR enable flag parameter of the remote end*/ /**<CNcomment:远端ANR 使能标志参数 变更标志*/
    HI_U32   bit1RemoteAnrValue:1; /**<Reserved, change flag of the target ANR value of the remote end*/ /**<CNcomment:保留，ANR 目标值 变更标志 */

    HI_U32   bit24Resv:24;
}HI_UNF_VQE_CHANGE_FLAG_S;

/**VQE parameter configuration*/
/**CNcomment:VQE参数配置 */
typedef struct hiUNF_VQE_CONFIG_BODY_S
{
    HI_U8   u8LocalAgcFlag;         /**<AGC enable flag of the local end: 0 - AGC off; 1 - AGC on. It corresponds to the change flag bit1LocalAgcFlag.*/
                                    /**<CNcomment:本端AGC 使能标志: 0 -- Agc Off , 1 -- Agc On , 对应变更标志 bit1LocalAgcFlag */
    HI_U8   u8LocalAgcValue;        /**<Reserved, automatic gain adjustment parameter of the local end.
                                                            Its value ranges from 0 to 15. The value 0 indicates -24 dB, and the value 15 indicates -9 dB. The default value is 13.
                                                            This parameter corresponds to the change flag bit1LocalAgcValue.*/
                                    /**<CNcomment:保留，本端自动增益调整参数,
                                                            [0 ~ 15] 对应 实际性能参数的-9dBm0 ~ -24dBm0, 缺省值13 ,
                                                            对应变更标志 bit1LocalAgcValue */
    HI_U8   u8RemoteAgcFlag;        /**<AGC enable flag of the remote end: 0 - AGC off; 1 - AGC on. It corresponds to the change flag bit1RemoteAgcFlag.*/
                                    /**<CNcomment:远端AGC 使能标志: 0 -- Agc Off , 1 -- Agc On ,  对应变更标志 bit1RemoteAgcFlag */
    HI_U8   u8RemoteAgcValue;       /**<Reserved, automatic gain adjustment parameter of the remote end.
                                                            Its value ranges from 0 to 15. The value 0 indicates -24 dB, and the value 15 indicates -9 dB. The default value is 13.
                                                            This parameter corresponds to the change flag bit1RemoteAgcValue.*/
                                    /**<CNcomment:保留，远端自动增益调整参数,
                                                            [0 ~ 15]对应实际性能参数的-9dBm0 ~ -24dBm0, 缺省值13 ,
                                                            对应变更标志 bit1RemoteAgcValue */
    HI_U8   u8LocalAnrFlag;         /**<ANR enable flag of the local end: 0 - ANR off; 1 - ANR on. It corresponds to the change flag bit1LocalAnrFlag.*/
                                    /**<CNcomment:本端ANR 使能标志: 0 -- Anr Off , 1 -- Anr On ,  对应变更标志 bit1LocalAnrFlag */
    HI_U8   u8LocalAnrValue;        /**<Reserved, target ANR value of the local end (background noise reduction parameter). It corresponds to the change flag bit1LocalAnrValue.*/
                                    /**<CNcomment:保留，本端ANR 目标值(背景噪声抑制调整参数) ,  对应变更标志 bit1LocalAnrValue */

    HI_U8   u8RemoteAnrFlag;        /**<ANR enable flag of the remote end: 0 - ANR off; 1 - ANR on. It corresponds to the change flag bit1RemoteAnrFlag.*/
                                    /**<CNcomment:远端ANR 使能标志: 0 -- Anr Off, 1 -- Anr On   , 对应变更标志 bit1RemoteAnrFlag */
    HI_U8   u8RemoteAnrValue;       /**<Reserved, target ANR value of the remote end (background noise reduction parameter). It corresponds to the change flag bit1RemoteAnrValue.*/
                                    /**<CNcomment:保留，远端ANR 目标值(背景噪声抑制调整参数)  ,   对应变更标志 bit1RemoteAnrValue */
}HI_UNF_VQE_CONFIG_BODY_S;


/**Structure of VQE parameters*/
/**CNcomment: 配置VQE参数结构 */
typedef struct hiUNF_VQE_CONFIG_PARA_S
{
    HI_UNF_VQE_CHANGE_FLAG_S stChange;  /**<Change flag. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                        /**<CNcomment:变更标志位 , 修改通道属性时有效，创建通道时无效*/
    HI_UNF_VQE_CONFIG_BODY_S stBody;    /**<VQE configuration parameter*/ /**<CNcomment:VQE配置参数 */
}HI_UNF_VQE_CONFIG_PARA_S;


/**Flags indicating the change of the structure of network parameters*/
/**CNcomment:网络参数结构变更标志位 */
typedef struct hiUNF_NET_CHANGE_FLAG_S
{
   HI_U32   bit1SrcIP:1;     /**<Change flag of the source IP address. It indicates that 32SrcIPLen and u8SrcIP[16] change.*/
                             /**<CNcomment:source ip变更标记, 32SrcIPLen和u8SrcIP[16]有更改*/
   HI_U32   bit1DstIP:1;     /**<Change flag of the destination IP address. It indicates that u32DstIPLen and u8DstIP[16] change.*/
                             /**<CNcomment:dest ip变更标记, u32DstIPLen和u8DstIP[16]有更改*/
   HI_U32   bit1SrcPort:1;   /**<Change flag of the source port. It indicates that u16SrcPort changes.*/
                             /**<CNcomment:source port 变更标记,u16SrcPort有更改*/
   HI_U32   bit1DstPort:1;   /**<Change flag of the destination port. It indicates that u16DstPort changes.*/
                             /**<CNcomment:dest port变更标记,u16DstPort有更改*/
   HI_U32   bit1IPTos:1;     /**<Change flag of the IP service type. It indicates that u32IPTos and u32Mask change.*/
                             /**<CNcomment:IP服务类型变更标记,u32IPTos和u32Mask有更改*/
   HI_U32   bit1Vlan:1;      /**<Virtual local area network (VLAN) change flag, reserved. It indicates that u32VlanEn, u32VlanPri, and u32VlanPid change.*/
                             /**<CNcomment:Vlan变更标记,u32VlanEn,u32VlanPri,u32VlanPid有更改，保留*/
   HI_U32   bit1Protocol:1;  /**<Change flag of the protocol type, reserved. Only Internet Protocol version 4 (IPv4) is supported currently.*/
                             /**<CNcomment:协议类型变更标记，目前只支持IPV4,保留*/
   HI_U32   bit25Resv:25;
}HI_UNF_NET_CHANGE_FLAG_S;

/**Network parameter configuration*/
/**CNcomment:网络参数配置 */
typedef struct hiUNF_NET_CONFIG_BODY_S
{
   HI_U32   u32SrcIPLen;       /**<Length of the source IP address. The IP address is 4 bytes (IPv4) or 16 bytes (IPv6). Other values are invalid.*/
                               /**<CNcomment:source ip地址长度，4(IPV4)或16(IPV6)，其它值无效*/
   HI_U8    u8SrcIP[16];       /**<Source IP address. The IP address is 4 bytes (IPv4) or 16 bytes (IPv6), but is not a string. For a 4-byte IP address, 192.168.1.1 for example, each segment occupies one byte.*/
                               /**<CNcomment:source ip地址，4字节(IPV4)或16字节(IPV6)，不是字符串，以192.168.1.1为例，4字节依次为192,168,1,1 */
   HI_U32   u32DstIPLen;       /**<Length of the destination IP address. The IP address is 4 bytes (IPv4) or 16 bytes (IPv6). Other values are invalid.*/
                               /**<CNcomment:dest ip地址长度，4(IPV4)或16(IPV6)，其它值无效*/
   HI_U8    u8DstIP[16];       /**<Destination IP address. The address is 4 bytes (IPv4) or 16 bytes (IPv6), but is not a string.*/
                               /**<CNcomment:dest ip地址，4字节(IPV4)或16字节(IPV6)，不是字符串*/

   HI_U16   u16SrcPort;        /**<Source RTP port number. The RTP port number must be an even number, and the corresponding RTCP port number is the RTP port number plus 1.*/
                               /**<CNcomment:source RTP 端口号，应为偶数；对应RTCP端口号为该数值+1 */
   HI_U16   u16DstPort;        /**<Destination RTP port number. The RTP port number must be an even number, and the corresponding RTCP port number is the RTP port number plus 1.*/
                               /**<CNcomment:dest RTP 端口号，应为偶数；对应RTCP端口号为该数值+1 */

   HI_U32   u32Mask;        /**<bit0: u32IPTos valid*/
   HI_U32   u32IPTos;       /**<IP service type, 8 bits*/ /**<CNcomment:IP服务类型,8bit*/
   HI_U32   u32VlanEn;      /**<VLAN enable, reserved. 0 - VLAN invalid; 1 - VLAN valid*/ /**<CNcomment:vlan使能: 0--vlan 无效,1--vlan 有效, 保留*/
   HI_U32   u32VlanPri;     /**<VLAN priority, 3 bits, reserved. It is valid when u32VlanEn is set to 1.*/ /**<CNcomment:vlan优先级,3bit, vlan为1时有效, 保留*/
   HI_U32   u32VlanPid;     /**<VLAN PID, 12 bits, reserved. It is valid when u32VlanEn is 1.*/ /**<CNcomment:vlan pid, 12bit, vlan为1时有效, 保留*/
   HI_U32   u32Protocol;    /**<Protocol type, reserved. 0x0800 - IPv4; 0x86dd - IPv6*/ /**<CNcomment:协议类型,0x0800--IPV4, 0x86dd--IPV6, 保留*/
}HI_UNF_NET_CONFIG_BODY_S;

/**Configuration of the network parameter structure*/
/**CNcomment:配置网络参数结构 */
typedef struct hiUNF_NET_CONFIG_PARA_S
{
    HI_UNF_NET_CHANGE_FLAG_S stChange;  /**<Flag indicating the change of network parameters. This flag must be set when you create or change a channel.*/
                                        /**<CNcomment:网络参数变更标志位 ,创建或修改通道时对应位必须设置*/

    HI_UNF_NET_CONFIG_BODY_S stBody;    /**<Network configuration parameter*/ /**<CNcomment:网络配置参数 */
}HI_UNF_NET_CONFIG_PARA_S;

/**Flags indicating the change of audio device parameters*/
/**CNcomment:音频设备参数变更标志*/
typedef struct hiUNF_AUDDEV_FLAG_S
{
    HI_U32   bit1AudioDevId:1;        /**<Change flag of ID of the audio device*/ /**<CNcomment:AudioDevId 变更标志 */
    HI_U32   bit1AiAttrChange:1;      /**<Change flag of audio input (AI) SampleRate/BitPerSample/Channels*/ /**<CNcomment:AI SampleRate/BitPerSample/Channels变更标志 */
    HI_U32   bit1AoAttrChange:1;      /**<Change flag of audio output (AO) SampleRate/BitPerSample/Channels*/ /**<CNcomment:AO SampleRate/BitPerSample/Channels变更标志 */
    HI_U32   bit29Resv:29;
}HI_UNF_AUDDEV_FLAG_S;

/**Audio device system parameters*/
/**CNcomment:音频设备系统参数 */
typedef struct hiUNF_AUDDEV_BODY_S
{
    HI_S32 s32AudioDevId;           /**<Audio device ID, [0]*/ /**<CNcomment:音频设备ID , 请参考HI_UNF_VOIP_AUDIO_DEVICE_E定义*/

    /**AI parameters*/ /**CNcomment:音频输入参数 */
    HI_S32 s32AiSampleRate;         /**<Sampling rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:采样率, [8000], [16000], [32000], [48000]*/
    HI_S32 s32AiBitPerSample;       /**<Bit depth, [16]*/ /**<CNcomment:采样精度, [16]*/
    HI_S32 s32AiChannels;           /**<Number of AI channels, [1]*/ /**<CNcomment:通道数, [1]*/

    /**AO parameters*/ /**CNcomment:音频输出参数*/
    HI_S32 s32AoSampleRate;         /**<Sampling rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:采样率, [8000], [16000], [32000], [48000]*/
    HI_S32 s32AoBitPerSample;       /**<Bit depth, [16]*/ /**<CNcomment:采样精度, [16]*/
    HI_S32 s32AoChannels;           /**<Number of AO channels, [1]*/ /**<CNcomment:通道数, [1]*/

}HI_UNF_AUDDEV_BODY_S;

typedef struct hiUNF_DIGIT_CHANGE_FLAG_S
{
    HI_U32   bit1DigitEnable:1;      /**Digit enable*/ /**CNcomment:收号使能   变更标志 */
    HI_U32   bit28Resv:31;
}HI_UNF_DIGIT_CHANGE_FLAG_S;

/**Configuration of Digit parameter*/
/**CNcomment:收号参数配置 */
typedef struct hiUNF_DIGIT_CONFIG_BODY_S
{
    HI_U32  u32DigitEnableFlag;     /**Digit enable flag, 0:enable, 1:disable*/ /**CNcomment:收号使能标志，0表示不使能，1表示使能*/
}HI_UNF_DIGIT_CONFIG_BODY_S;

typedef struct hiUNF_DIGIT_CONFIG_PARA_S
{
    HI_UNF_DIGIT_CHANGE_FLAG_S stChange;  /**<change flag of DTMF digit parameter*/ /**<CNcomment:DTMF收号参数变更标记 */
    HI_UNF_DIGIT_CONFIG_BODY_S stBody;    /**<configuration parameter of DTMF digit*/ /**<CNcomment:DTMF收号配置参数 */
}HI_UNF_DIGIT_CONFIG_PARA_S;

/**Audio device parameters*/
/**CNcomment:音频设备参数*/
typedef struct hiUNF_AUDDEV_PARA_S
{
    HI_UNF_AUDDEV_FLAG_S    stChang;        /**<Change flag of audio device parameters. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                            /**<CNcomment:音频设备参数变更标记， 修改通道属性时有效，创建通道时无效*/
    HI_UNF_AUDDEV_BODY_S    stBody;         /**<Audio device configuration parameter*/ /**<CNcomment:音频设备配置参数*/
}HI_UNF_AUDDEV_PARA_S;


/**Defines the attributes of a VoIP channel.*/
/**CNcomment:定义VOIP 通道属性 */
typedef struct hiUNF_VOIP_CHN_ATTR_S
{
    HI_UNF_VOIP_TLV_HEAD_S stTlvHead;         /**<u16BlockType is invalid. u16BlockLen indicates the length of the entire HI_UNF_VOIP_CHN_ATTR_S.*/
                                              /**<CNcomment:其中，u16BlockType无效，这里u16BlockLen表示整个HI_UNF_VOIP_CHN_ATTR_S 结构体长度*/

    HI_UNF_VOIP_TLV_HEAD_S stDspHead;         /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_DSP, and u16BlockLen is the length of HI_UNF_VOIP_DSP_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_DSP, u16BlockLen为HI_UNF_VOIP_DSP_CONFIG_PARA_S结构体长度*/
    HI_UNF_VOIP_DSP_CONFIG_PARA_S stDspPara;  /**<Common DSP configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:dsp common配置参数，打开通道时是必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stEcHead;          /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_EC, and u16BlockLen is the length of HI_UNF_VOICE_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_EC, u16BlockLen为HI_UNF_VOICE_CONFIG_PARA_S结构体长度*/
    HI_UNF_VOICE_CONFIG_PARA_S stEcPara;      /**<EC configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:Ec配置参数, 打开通道时是必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stJBHead;          /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_JB, and u16BlockLen is the length of HI_UNF_JB_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_JB, u16BlockLen为HI_UNF_JB_CONFIG_PARA_S结构体长度*/
    HI_UNF_JB_CONFIG_PARA_S stJBPara;         /**<JB configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:JB配置参数, 打开通道时是必填项，修改通道时无效*/

    HI_UNF_VOIP_TLV_HEAD_S stVQEHead;         /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_VQE, and u16BlockLen is the length of HI_UNF_VQE_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_VQE, u16BlockLen为HI_UNF_VQE_CONFIG_PARA_S结构体长度*/
    HI_UNF_VQE_CONFIG_PARA_S stVQEPara;       /**<VQE configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:VQE配置参数，打开通道时是必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stNetHead;         /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_NET, and u16BlockLen is the length of HI_UNF_NET_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_NET, u16BlockLen为HI_UNF_NET_CONFIG_PARA_S结构体长度*/
    HI_UNF_NET_CONFIG_PARA_S stNetPara;       /**<Network configuration parameter, optional*/
                                              /**<CNcomment:NET配置参数，可选项*/

    HI_UNF_VOIP_TLV_HEAD_S stAudevHead;       /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV, and u16BlockLen is the length of HI_UNF_AUDDEV_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV, u16BlockLen为HI_UNF_AUDDEV_PARA_S结构体长度*/
    HI_UNF_AUDDEV_PARA_S   stAudevPara;       /**<Audio device configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:音频设备配置参数，打开通道为必填项，修改通道时可选*/

    HI_UNF_VOIP_TLV_HEAD_S stDigitHead;       /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_CFG_DIGITAL, and u16BlockLen is the length of HI_UNF_DIGIT_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  为HI_UNF_VOIP_ATTR_ID_CFG_DIGITAL, u16BlockLen为HI_UNF_DIGIT_CONFIG_PARA_S结构体长度*/
    HI_UNF_DIGIT_CONFIG_PARA_S stDigitPara;   /**<DTMF digit configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:DTMF收号配置参数，打开通道为必选项，修改通道为可选项*/
}HI_UNF_VOIP_CHN_ATTR_S;

/**Description of the basic frequency, reserved*/
/**CNcomment:基本频率描述，保留*/
typedef struct hiUNF_VOIP_BASE_FREQ_INFO_S
{
    HI_U16  u16Frequence;        /**<Fundamental frequency*/ /**<CNcomment:基波频率*/
    HI_U16  u16Amplitude;        /**<Fundamental amplitude*/ /**<CNcomment:基波幅度*/
}HI_UNF_VOIP_BASE_FREQ_INFO_S;

/**Description of the basic cadence, reserved*/
/**CNcomment:基本节拍描述，保留*/
typedef struct hiUNF_VOIP_CADENCE_INFO_S
{
    HI_U16  u16FreqFlag;        /**<Fundamental frequency flag*/ /**<CNcomment:使用的基波标志*/
    HI_U16  u16Reserved;        /**<Reserved*/ /**<CNcomment:保留域*/
    HI_U16  u16OnTime;          /**<Valid time*/ /**<CNcomment:有效时间*/
    HI_U16  u16OffTime;         /**<Mute time*/ /**<CNcomment:静音时间*/
}HI_UNF_VOIP_CADENCE_INFO_S;

/**Description of ringback tone parameters, reserved*/
/**CNcomment:回铃音参数描述，保留*/
typedef struct hiUNF_VOIP_TONE_ATTR_S
{
    HI_UNF_VOIP_BASE_FREQ_INFO_S   stBaseFreqInfo[4]; /**<Description of the fundamental frequency*/ /**<CNcomment:基本频率描述*/
    HI_U32                u32CadenceCount;            /**<Number of cadences*/ /**<CNcomment:节拍的数量*/
    HI_U32                u32Resve;
    HI_UNF_VOIP_CADENCE_INFO_S     stCadenceInfo[8];  /**<Cadence description*/ /**<CNcomment:节拍描述*/
}HI_UNF_VOIP_TONE_ATTR_S;

/**Descriptor of the playing attributes of the ringback tone, reserved*/
/**CNcomment:回铃音播放属性描述符，保留*/
typedef struct hiUNF_VOIP_PLAY_TONE_ATTR_S
{
    HI_UNF_VOIP_TONE_ATTR_S stToneParam;    /**<Ringback tone parameter, reserved*/ /**<CNcomment:回铃音参数，保留*/
    HI_U32 u32MixFlag;                      /**<Mixing flag: 0 - not mixed; 1-mixed*/ /**<CNcomment:混音标志: 0--不混音, 1--混音*/
    HI_U32 u32LoopTime;                     /**<Number of loop times: 0-not looped; 1-254: number of loop times; 255  -  keep playing*/
                                            /**<CNcomment:重复次数: 0--不重复, 1~254 -- 重复次数, 255 -- 一直播放*/
}HI_UNF_VOIP_PLAY_TONE_ATTR_S;

/**Descriptor of the playing attributes of the audio file*/
/**CNcomment:音频文件播放属性描述符*/
typedef struct hiUNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S
{
    HI_U32 u32DataAddr;         /**<Audio file address*/ /**<CNcomment:音频文件地址*/
    HI_U32 u32DataLen;          /**<Audio file length*/ /**<CNcomment:音频文件长度*/
    HI_U16 u16SourceFormat;     /**<Audio file encoding type: 0 - G.711A; 1 - G.711Mu. Note: Only the standard WAV file of the 711 payload type is supported.*/
                                /**<CNcomment:音频文件编码类型: 0 -- G.711A, 1 -- G.711Mu. 注: 目前只支持播放711类型的标准wav文件，且文件为纯净荷。*/
    HI_U16 u16Resv;
    HI_U32 u32MixFlag;          /**<Mixing flag: 0 - not mixed; 1 - mixed*/ /**<CNcomment:混音标志: 0--不混音, 1--混音*/
    HI_U32 u32Direction;        /**<Playing direction: 0 - play to the local end; 1 - play to the remote end (reserved)*/
                                /**<CNcomment:播放方向: 0--播放到本端, 1-- 播放到远端*/
    HI_U32 u32LoopTime;         /**<Number of loop times: 0 - not looped; 1-254: number of loop times; 255  -  keep playing*/
                                /**<CNcomment:重复次数: 0--不重复, 1~254 -- 重复次数, 255 -- 一直播放*/
}HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S;


/**Descriptor of the network quality*/
/**CNcomment:网络质量信息描述符*/
typedef struct hiUNF_VOIP_NET_QUALITY_STATIC_INFO_S
{
    HI_U32 u32TotalLostPacket;              /**<Number of lost packets*/ /**<CNcomment:数据丢包统计*/
    HI_U32 u32LossFraction;                 /**<Packet loss rate (%)*/ /**<CNcomment:丢包率(%) */
    HI_U32 u32Jitter;                       /**<Average jitter (ms)*/ /**<CNcomment:平均抖动(ms) */
    HI_U32 u32Delay;                        /**<Average delay (ms)*/ /**<CNcomment:平均时延(ms) */
}HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S;

/**Descriptor of the RTCP statistics*/
/**CNcomment:RTCP统计信息描述符 */
typedef struct hiUNF_VOIP_RTCP_STATIC_INFO_S
{
    HI_U32 u32SendPacketNum;               /**<Number of transmitted packets*/ /**<CNcomment:发送包总数*/
    HI_U32 u32SendBytes;                   /**<Number of transmitted bytes*/ /**<CNcomment:发送字节数*/
    HI_U32 u32RecPacketNum;
    HI_U32 u32RecBytes;
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stSendInfo;          /**<Transmission statistics*/ /**<CNcomment:发送统计*/
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stRecvInfo;          /**<Reception statistics*/ /**<CNcomment:接收统计*/
}HI_UNF_VOIP_RTCP_STATIC_INFO_S;

/**Descriptor of the RTCP configuration*/
/**CNcomment:RTCP配置描述符*/
typedef struct hiUNF_VOIP_CFG_RTCP_ATTR_S
{
    HI_U32 u32EnableFlag;               /**<RTCP statistics enable: 0 - disabled; 1 - enabled*/ /**<CNcomment:RTCP统计使能: 0--不使能, 1--使能*/
    HI_U32 u32SendInterval;             /**<Interval of transmitting the RTCP report. Its value range is [500, 65535] and is in the unit of ms. The value must be an integral multiple of 500.*/
                                        /**<CNcomment:RTCP报告发送间隔, [500 ~ 65535] ms , 必须为500ms的整数倍*/
}HI_UNF_VOIP_CFG_RTCP_ATTR_S;


/*******************************Audio adapter module*********************************/
/*******************************CNcomment:音频适配模块CNend ******************************/
#define HI_ALSA_AUD_DEV_NAME_LEN 32        /**<the length of ALSA audio device name*/ /**<CNcomment:ALSA 音频设备名长度*/

/**Define Alsa soundcard information*/
/**CNcomment:定义ALSA声卡信息 */
typedef struct hi_ALSA_CARD_INFO_S
{
    HI_S32 s32CardNo;           /**<ALSA soundcard number*/ /**<CNcomment:ALSA声卡号 */
    HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enType;       /**<Input and output type of audio device*/ /**<CNcomment:音频设备输入输出类型*/
    HI_CHAR szName[HI_ALSA_AUD_DEV_NAME_LEN];     /**<ALSA soundcard name*/ /**<CNcomment:ALSA声卡名*/
}HI_ALSA_CARD_INFO_S;


/**Attribute struct of audio device in audio adapter module*/
/**CNcomment:音频适配模块音频设备属性结构体 */
typedef struct hiUNF_AUDADP_AUDDEV_PARA_S
{
    HI_S32 s32AudioDevId;      /**<ID of audio device*/ /**<CNcomment:音频设备ID，请参考 HI_UNF_VOIP_AUDIO_DEVICE_E 定义*/

    /**Parameter of audio input device*/ /**CNcomment:音频输入设备参数 */
    HI_S32 s32AiCardNo;        /**<ALSA soundcard number*/ /**<CNcomment:ALSA声卡号 */
    HI_S32 s32AiSampleRate;    /**<sample rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:采样率, 有效值为 8000, 16000, 32000, 48000*/
    HI_S32 s32AiBitPerSample;  /**<bit depth, [16]*/ /**<CNcomment:采样精度，有效值为16*/
    HI_S32 s32AiChannels;      /**<channels,[1]*/ /**<CNcomment:通道数，有效值为1*/

    /**Parameter of audio output device*/ /**CNcomment:音频输出设备参数 */
    HI_S32 s32AoCardNo;        /**<ALSA soundcard number*/ /**<CNcomment:ALSA声卡号*/
    HI_S32 s32AoSampleRate;    /**<sample rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:采样率, 有效值为 8000, 16000, 32000, 48000*/
    HI_S32 s32AoBitPerSample;  /**<bit depth, [16]*/ /**<CNcomment:采样精度，有效值为16*/
    HI_S32 s32AoChannels;      /**<channels,[1]*/ /**<CNcomment:通道数，有效值为1*/

}HI_UNF_AUDADP_AUDDEV_PARA_S;

/**Defines the type of the event transmitted by the VoIP audio adapter module.*/
/**CNcomment:定义音频适配模块事件类型*/
typedef enum hiUNF_AUDADP_EVENT_E
{
    HI_UNF_AUDADP_EVENT_OPEN_SUCCESS,              /**<The audio device is started successfully.*/ /**<CNcomment:打开音频设备成功*/
    HI_UNF_AUDADP_EVENT_OPEN_FAILURE,              /**<The audio device fails to be started.*/ /**<CNcomment:打开音频设备失败*/
    HI_UNF_AUDADP_EVENT_CLOSED,                    /**<The started audio device is stopped.*/ /**<CNcomment:音频设备关闭*/
    HI_UNF_AUDADP_EVENT_STREAM_ERROR,              /**<An audio stream error occurs when the audio device is started.*/ /**<CNcomment:音频数据流错误*/
    HI_UNF_AUDADP_EVENT_BLUETOOTH_NOT_CONNECTED,   /**<The Bluetooth device is not connected.*/ /**<CNcomment:蓝牙耳机未连接*/
    HI_UNF_AUDADP_EVENT_BUTT
} HI_UNF_AUDADP_EVENT_E;

/**Defines the status type of the audio device.*/
/**CNcomment:定义音频设备状态*/
typedef enum hiUNF_AUDADP_STATUS_E
{
    HI_UNF_AUDADP_STATUS_CLOSED  = 0x00, /**<The audio device is stopped.*/ /**<CNcomment:音频设备关闭 */
    HI_UNF_AUDADP_STATUS_OPENING,        /**<The audio device is being started.*/ /**<CNcomment:音频设备正在打开 */
    HI_UNF_AUDADP_STATUS_OPENED,         /**<The audio device is started.*/ /**<CNcomment:音频设备已打开*/
    HI_UNF_AUDADP_STATUS_RUNNING,        /**<The audio data is being transmitted.*/ /**<CNcomment:音频设备正在运行，正常传输音频数据*/
    HI_UNF_AUDADP_STATUS_ERROR,          /**<The audio device fails to be started or the audio data fails to be transmitted.*/ /**<CNcomment:打开音频设备或传输音频数据失败*/
    HI_UNF_AUDADP_STATUS_BLUETOOTH_NOT_CONNECTED,   /**<The Bluetooth device is not connected.*/ /**<CNcomment:蓝牙耳机未连接*/
    HI_UNF_AUDADP_STATUS_BUTT
} HI_UNF_AUDADP_STATUS_E;

/**Defines data structure of the event transmitted by the VoIP audio adapter module.*/
/**CNcomment:定义音频适配模块事件结构体*/
typedef struct hiUNF_AUDADP_EVENT_S
{
    HI_S32 s32AudioDevId;              /**<Aaudio device index*/ /**<CNcomment:音频设备ID，请参考 HI_UNF_VOIP_AUDIO_DEVICE_E 定义*/
    HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType;   /**<HI_TRUE: AI device; HI_FALSE: AO device*/ /**<CNcomment:音频设备输入输出类型*/
    HI_UNF_AUDADP_EVENT_E enEvent;     /**<Event type*/ /**<CNcomment:事件类型*/
    HI_UNF_AUDADP_STATUS_E enStatus;   /**<Audio device status*/ /**<CNcomment:音频设备状态*/
    HI_U32 u32Args;                    /**<Private arguments transmitted by users when the event callback function is registered*/ /**<CNcomment:用户私有数据*/
}HI_UNF_AUDADP_EVENT_S;

/**Operating flag of audio device*/
/**CNcomment:音频设备操作标志*/
typedef struct hiUNF_AUDDEV_OPT_FLAG_S
{
    HI_U32   bit1AudInDev:1;       /**<AI device*/ /**<CNcomment: 输入设备操作标志 */
    HI_U32   bit1AudOutDev:1;      /**<AO device*/ /**<CNcomment:输出设备操作标志 */
    HI_U32   bit30Resv:30;
}HI_UNF_AUDDEV_OPT_FLAG_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup     VOIP */
/** @{ */  /** <!--  [VOIP] */

/**
 \brief Initializes the VoIP module. CNcomment: 初始化VOIP模块CNend
 \attention \n
 \param N/A
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR  The device fails to be started. CNcomment:设备打开错误CNend
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST  The device does not exist. CNcomment:设备不存在CNend
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE  The file is not a device file. CNcomment:不是设备文件CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT    The thread for processing VoIP events fails to be initialized. CNcomment:EVENT初始化失败CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_Init(HI_VOID);

/**
 \brief Deinitializes the VoIP module. CNcomment:去初始化VOIP模块CNend
 \attention \n
 \param N/A
 \retval ::0 Success CNcomment:成功CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_DeInit(HI_VOID);

/**
 \brief Obtains the default configuration of an VoIP channel. CNcomment:获取缺省的VOIP 通道配置CNend
 \attention \n
        Ensure that the working mode of the VoIP channel to be created is correct. Only the voice mode HI_UNF_VOIP_MODE_VOIVE is supported.
        You are advised to obtain default attributes by calling this API before creating a VoIP channel. This avoids failure in creating a VoIP channel due to incomplete or incorrect parameters.
        CNcomment:请正确输入想要创建VOIP 通道工作模式，目前只支持语音模式HI_UNF_VOIP_MODE_VOIVE
        创建VOIP 通道前建议调用本接口，获取到默认属性，避免创建VOIP 通道时由于参数不全或参数错误导致创建不成功现象CNend
 \param[in] enWorkMode       Working mode of a VoIP channel. For details, see ::HI_UNF_VOIP_WORKMODE_E. CNcomment:VOIP 通道工作模式，请参见::HI_UNF_VOIP_WORKMODE_E
 \param[out] pstDefChAttr  Pointer to the default VoIP channel attributes. For details, see :HI_UNF_VOIP_CHN_ATTR_S. CNcomment:指针类型，VOIP 通道默认属性，参见:HI_UNF_VOIP_CHN_ATTR_S  CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr);

/**
 \brief Creates a VoIP channel. CNcomment:创建VOIP 通道CNend
 \attention \n
 Before creating a VoIP channel, you are advised to obtain default channel attributes by calling HI_UNF_VOIP_GetChDefaultAttr() and modify parameter values as required.
 CNcomment:创建通道前，建议先调用HI_UNF_VOIP_GetChDefaultAttr()获取默认通道属性，再对参数做必要修改。CNend
 \param[in] enWorkMode       Working mode of a VoIP channel. For details, see ::HI_UNF_VOIP_WORKMODE_E. CNcomment:VOIP 通道工作模式，请参见::HI_UNF_VOIP_WORKMODE_E  CNend
 \param[in]  pstChAttr  Pointer to VoIP channel attributes. For details, see ::HI_UNF_VOIP_CHN_ATTR_S. CNcomment:指针类型，VOIP 通道属性，请参见::HI_UNF_VOIP_CHN_ATTR_S  CNend
 \param[out] phVoip   Pointer to the handle of a created VoIP channel CNcomment:指针类型，创建的VOIP 通道句柄CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::HI_ERR_VOIP_HME_CREATE_ERR   A channel fails to be created. CNcomment:创建通道失败CNend
 \retval ::Other values  A channel fails to be created. CNcomment:其它  创建通道失败CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoip);

/**
 \brief Destroys a VoIP channel. CNcomment:销毁VOIP 通道CNend
 \attention \n
N/A
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  The parameter is invalid. CNcomment:无效参数CNend
 \retval ::HI_ERR_VOIP_HME_DESTROY_ERR   A channel fails to be destroyed. CNcomment:销毁通道失败CNend
 \retval ::Other values  A channel fails to be destroyed. CNcomment:其它  销毁通道失败CNend
 \see \n
N/A
 */
 HI_S32 HI_UNF_VOIP_DestroyChannel(HI_HANDLE hVoip);

/**
 \brief Obtains the configuration of a VoIP channel. CNcomment:获取VOIP 通道配置CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[out] pstChAttr  Pointer to VoIP channel attributes. For details, see :HI_UNF_VOIP_CHN_ATTR_S. CNcomment:指针类型，VOIP 通道属性，参见:HI_UNF_VOIP_CHN_ATTR_S  CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  Channel attributes fail to be obtained. CNcomment:其它  获取通道属性失败CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_GetChAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

/**
 \brief Modifies the configuration of a VoIP channel. CNcomment:修改VOIP 通道配置CNend
 \attention \n
        You are advised to obtain the current channel configuration by calling HI_UNF_VOIP_GetChAttr(), and modify parameter values as required. Set the corresponding change flags to 1, and set irrelevant change flags to 0.
        CNcomment:建议先调用HI_UNF_VOIP_GetChAttr()获取当前通道配置，再对参数做必要修改，对应的更改标记置1，无关更改标志置0。CNend
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP通道句柄CNend
 \param[in] pstChAttr  Pointer to VoIP channel attributes. For details, see :HI_UNF_VOIP_CHN_ATTR_S. CNcomment:指针类型，VOIP 通道属性，参见:HI_UNF_VOIP_CHN_ATTR_S  CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  Channel attributes fail to be modified. CNcomment:其它  修改通道属性失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_ModifyChnAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

#if 0
/**
 \brief Obtains the sub attributes of a VoIP channel. CNcomment:获取VOIP 通道子属性CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] enAttrID  ID of the VoIP channel configuration parameter. For details, see :HI_UNF_VOIP_ATTR_ID_E. CNcomment:VOIP 通道配置参数ID，参见: HI_UNF_VOIP_ATTR_ID_E  CNend
 \param[out] pChSubAttr  Pointer to the sub attributes of a VoIP channel. The data structure corresponds to enAttrID. CNcomment:指针类型，VOIP 通道子属性，结构体与enAttrID 对应。CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  Channel attributes fail to be obtained. CNcomment:其它  获取通道属性失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_GetChSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief Modifies the sub attributes of a VoIP channel. CNcomment:修改VOIP 通道子属性CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] enAttrID  ID of the VoIP channel configuration parameter. For details, see :HI_UNF_VOIP_ATTR_ID_E. CNcomment:VOIP 通道配置参数ID，参见: HI_UNF_VOIP_ATTR_ID_E  CNend
 \param[out] pChSubAttr  Pointer to the sub attributes of a VoIP channel. The data structure corresponds to enAttrID. CNcomment:指针类型，VOIP 通道子属性，结构体与enAttrID 对应。CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  Channel attributes fail to be modified. CNcomment:其它  修改通道属性失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_ModifyChnSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief Plays the ringback tone. CNcomment:播放回铃音CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] pstToneAttr  Pointer to the ringback tone playing parameter. For details, see :HI_UNF_VOIP_PLAY_TONE_ATTR_S. CNcomment:指针类型，回铃音播放参数，参见: HI_UNF_VOIP_PLAY_TONE_ATTR_S  CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  The ringback tone fails to be played. CNcomment:其它  播放回铃音失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_PlayTone(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr);

/**
 \brief Stops playing the ringback tone. CNcomment:停止播放回铃音CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::Other values  The ringback tone fails to be stopped. CNcomment:其它  停止播放回铃音失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_StopTone(HI_HANDLE hVoip);
#endif

/**
 \brief Plays an audio file. CNcomment:播放音频文件CNend
 \attention \n
        Only the standard WAV file of the 711 payload type is supported. CNcomment:目前只支持播放711类型的标准wav文件，且文件为纯净荷。CNend
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] pstAnnAttr  Pointer to the audio file playing parameter. For details, see :HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S.
                        CNcomment:指针类型，音频文件播放参数，参见: HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S  CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  The audio file fails to be played. CNcomment:其它  播放音频文件失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_PlayAnnouncement(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr);

/**
 \brief Stops playing an audio file. CNcomment:停止播放音频文件CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] u32Direction  Playing direction. It must be the same as the value of u32Direction (audio file playing attribute).
            CNcomment:播放方向，必须与音频文件播放属性中的u32Direction 保持一致。CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::Other values  The audio file fails to be stopped. CNcomment:其它  停止 播放音频文件失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_StopAnnouncement(HI_HANDLE hVoip, HI_U32 u32Direction);

/**
 \brief  Defines the type of the event callback function. CNcomment:定义事件回调函数类型CNend
 \attention \n
N/A
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] enEvent     Event type enumeration. For details, see the definition of :HI_UNF_VOIP_EVENT_E . CNcomment:枚举类型，表示事件类型，参见: HI_UNF_VOIP_EVENT_E 定义CNend
 \param[in] s32EventValue  Event type parameter. It can be used to add output parameters to events, for example, adding the error codes to error events.
                           CNcomment:事件类型参数，用于为event附带一些输出参数， 比如错误事件的错误码CNend
 \param[in] u32Args        Transferred args parameter during registration CNcomment:注册时传入的args参数。CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::Other values   Failure CNcomment:其它  失败CNend
 \see \n
N/A
 */
typedef HI_S32 (*HI_UNF_VOIP_EVENT_CB_FN)(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args);


/**
 \brief Registers an event. CNcomment:注册事件CNend
 \attention \n
N/A
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] pfnEventCB  Pointer to the callback function corresponding to the registered event. The null pointer indicates unregistration.
                        CNcomment:回调函数指针，指向与注册事件对应的回调函数。指针为NULL表示UnRegister  CNend
 \param[in] u32Args     Private parameter of a callback function. This parameter is transferred to the callback function when the callback function is called.
                        CNcomment:回调函数私有参数，此参数在回调函数被调用的时候会传递给回调函数。CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NOT_EXIST   The channel does not exist. CNcomment:通道不存在CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_RegisterEvent(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);


/**
 \brief Obtains the RTCP statistics. CNcomment:获取RTCP统计信息CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[out] pstRtcpInfo  Pointer to RTCP statistics. For details, see :HI_UNF_VOIP_RTCP_STATIC_INFO_S. CNcomment:指针类型，RTCP统计信息，参见: HI_UNF_VOIP_RTCP_STATIC_INFO_S  CNend
 \retval ::0 Success CNcomment:
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values  The RTCP statistics fail to be obtained. CNcomment:其它  获取RTCP统计信息失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_GetRtcpStaticInfo(HI_HANDLE hVoip, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo);

/**
 \brief  Performs the RTCP configuration. CNcomment:RTCP配置CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP 通道句柄CNend
 \param[in] pstRtcpAttr  Pointer to RTCP configuration. For details, see :HI_UNF_VOIP_CFG_RTCP_ATTR_S. CNcomment:指针类型，RTCP配置，参见: HI_UNF_VOIP_CFG_RTCP_ATTR_S  CNend
 \retval ::0 Success CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:无效的输入参数CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:空指针CNend
 \retval ::Other values   RTCP configuration fails to be performed. CNcomment:其它  RTCP配置失败CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_CfgRtcp(HI_HANDLE hVoip, HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr);


/*******************************Voip Audio Adapter***********************************/
/*******************************CNcomment:音频适配模块CNend ******************************/

/**
 \brief Initializes the VoIP audio adapter module. CNcomment:初始化音频适配模块CNend
 \attention \n
You must initialize the VoIP module before initializing the audio adapter module. CNcomment:必须先初始化VOIP模块再初始化音频适配模块CNend
 \param N/A
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR Failed to open the device. CNcomment:打开设备节点失败CNend
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST The device do not exist. CNcomment:设备不存在CNend
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE It is not device file. CNcomment:不是设备文件CNend
 \retval ::Other values    Failure CNcomment:其它  失败CNend
 \see \n
None
 */

HI_S32 HI_UNF_AUDADP_Init(HI_VOID);

/**
 \brief Deinitializes the VoIP audio adapter module. CNcomment:音频适配模块去初始化CNend
 \attention \n
You are advised to deinitialize the audio adapter module after deinitializing the VoIP module. CNcomment:去初始化音频适配模块之前需去初始化VOIP模块。CNend
 \param N/A
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \see \n
None
 */

HI_S32 HI_UNF_AUDADP_DeInit(HI_VOID);

/**
 \brief Starts the audio device. CNcomment:打开音频设备CNend
 \attention \n
You are advised to start the audio device immediately after initializing the audio adapter module. CNcomment:打开音频设备之前需初始化音频适配模块。CNend
 \param[in] pstAudDev   Parameters of the started audio device CNcomment:音频设备参数CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:音频设备操作标志CNend
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT  No Deinitialization CNcomment:未初始化CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The point is null. CNcomment:空指针CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA The parameter is invalid. CNcomment:无效参数CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Open(HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudDev, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Stops the audio device. CNcomment:关闭音频设备CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:音频设备ID, 请参考 HI_UNF_VOIP_AUDIO_DEVICE_E 定义CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:音频设备操作标志CNend
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT  No Deinitialization CNcomment:未初始化CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  The parameter is invalid. CNcomment:无效参数CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Close(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Starts to transmit audio data. CNcomment:开始音频数据传输CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:音频设备ID, 请参考 HI_UNF_VOIP_AUDIO_DEVICE_E 定义CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:音频设备操作标志CNend
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT   No Deinitialization CNcomment:未初始化CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The parameter is invalid. CNcomment:无效参数CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Start(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Stops transmitting audio data. CNcomment:停止音频数据传输CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:音频设备ID, 请参考 HI_UNF_VOIP_AUDIO_DEVICE_E 定义CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:音频设备操作标志CNend
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT    No Deinitialization CNcomment:未初始化  CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The parameter is invalid. CNcomment:无效参数CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Stop(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Obtains the audio device status. CNcomment:获取音频设备状态CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:音频设备ID, 请参考 HI_UNF_VOIP_AUDIO_DEVICE_E 定义CNend
 \param[in] bAudioInDev  HI_TRUE for AI device, HI_FALSE for AO device CNcomment:音频设备输入输出类型CNend
 \param[out] ps32Status  Returned audio device status CNcomment:音频设备状态CNend
 \retval ::0  HI_SUCCESS CNcomment:成功 CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT  No Deinitialization CNcomment:未初始化CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The point is null. CNcomment:空指针CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  The parameter is invalid. CNcomment:无效参数CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevId, HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_UNF_AUDADP_STATUS_E *ps32Status);

/**
 \brief Defines the event callback function of the audio adapter. CNcomment:定义音频适配事件回调函数CNend
 \attention \n
 N/A
 \param[in] pstAudadpEvent   Event structure CNcomment:音频适配事件属性结构体CNend
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::others FAILURE CNcomment:其它 失败CNend
 \see \n
N/A
 */

typedef HI_S32 (*HI_UNF_AUDADP_EVENT_CB_FN)(HI_UNF_AUDADP_EVENT_S *pstAudadpEvent);

/**
 \brief Registers the callback function for audio adapter events. CNcomment:注册音频适配模块事件回调函数 CNend
 \attention \n
 N/A
 \param[in] pfnEventCB   Pointer of the callback function. Null pointer indicates unregisteration. CNcomment:事件回调函数指针 , NULL 用于注销事件回调函数.CNend
 \param[in] u32Args  Private parameter from user application. CNcomment:用户私有数据.CNend
 \retval ::0  HI_SUCCESS CNcomment:成功CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT   No Deinitialization CNcomment:未初始化CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);

/**
 \brief Obtain ALSA audio device list. CNcomment:获取ALSA音频设备列表 CNend
 \attention \n
 \param[in] enAudioDevType  The input and output type of audio device. CNcomment:音频设备输入输出类型CNend
 \param[in] pstCardList   The point of ALSA audio device list. CNcomment:ALSA音频设备列表指针CNend
 \param[in] u32Max        The maximum device number of ALSA audio device list. CNcomment:ALSA音频设备列表最大设备数目CNend
 \param[out] pu32Count    Obtained number of audio device CNcomment:获取到的音频设备数目CNend
 \retval ::HI_SUCCESS  Success CNcomment:成功CNend
 \retval ::Other Failure CNcomment:其它 失败CNend
 \see \n
N/A
 */

HI_S32 HI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardList,HI_U32 u32Max,HI_U32 *pu32Count);

/**
 \brief Obtain sample rate range of audio device. CNcomment:获取音频设备采样率范围CNend
 \attention \n
 Audio device must be in closed status. CNcomment:音频设备必须处于关闭状态.CNend
 \param[in] pstCardInfo  The information of ALSA audio device CNcomment:ALSA音频设备信息CNend
 \param[out] pu32Min     The minimum sample rate of audio device CNcomment:音频设备最小采样率CNend
 \param[out] pu32Max     The maximum sample rate of audio device CNcomment:音频设备最大采样率CNend
 \retval ::HI_SUCCESS  Success CNcomment:成功CNend
 \retval ::Other Failure CNcomment:其它 失败CNend
 \see \n
N/A
 */

HI_S32 HI_ALSA_GetAudioDevRateRange(HI_ALSA_CARD_INFO_S * pstCardInfo, HI_U32 *pu32Min, HI_U32 *pu32Max);

/** @} */  /** <!-- ==== API Declaration End ==== */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
