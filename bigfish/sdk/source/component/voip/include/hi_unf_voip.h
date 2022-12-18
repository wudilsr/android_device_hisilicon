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
 * \brief Describes the information about the voice over Internet Protocol (VoIP) engine.CNcomment:�ṩVOIP��������������ϢCNend
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
/** @{ */  /**<!��[VOIP] */


/**Defines the working mode of the VoIP channel.*/
/**CNcomment:����VOIP ͨ������ģʽ���� */
typedef enum hiUNF_VOIP_WORKMODE_E
{
    HI_UNF_VOIP_MODE_DTMF  = 0x00,  /**<dual-tone multi-frequency (DTMF) mode of receiving numbers, reserved*/ /**<CNcomment:DTMF�պ�ģʽ������ */
    HI_UNF_VOIP_MODE_VOIVE = 0x01,  /**<Voice mode*/ /**<CNcomment:����ģʽ */
    HI_UNF_VOIP_MODE_FAX   = 0x02,  /**<Fax mode, reserved*/ /**<CNcomment:����ģʽ ������*/
    HI_UNF_VOIP_MODE_MODEM = 0x03,  /**<Modem mode, reserved*/ /**<CNcomment:Modem ģʽ������*/
    HI_UNF_VOIP_MODE_BUTT = 0x4
} HI_UNF_VOIP_WORKMODE_E;

/**Defines the type of the reported event related to the VoIP channel.*/
/**CNcomment:����VOIP ͨ���¼��ϱ����� */
typedef enum hiUNF_VOIP_EVENT_E
{
    HI_UNF_VOIP_CH_EVENT_FAULT,              /**<The channel is faulty.*/ /**<CNcomment:ͨ������*/
    HI_UNF_VOIP_CH_EVENT_NORMAL,             /**<The channel is restored to the normal status. This event is not supported.*/ /**<CNcomment:ͨ���ָ��������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_OPEN_FAILED,        /**<The channel fails to be enabled. This event is not supported.*/ /**<CNcomment:��ͨ��ʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_CLOSE_FAILED,       /**<The channel fails to be disabled. This event is not supported.*/ /**<CNcomment:�ر�ͨ��ʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_LOCAL_PLAY_END,     /**<Local playing ends.*/ /**<CNcomment:LOCAL PLAY����*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_PLAY_END,    /**<Remote playing ends.*/  /**<CNcomment:REMOTE PLAY����*/
    HI_UNF_VOIP_CH_EVENT_FAX_START,          /**<The fax starts. This event is not supported.*/ /**<CNcomment:���濪ʼ���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_FAX_END,            /**<The fax ends. This event is not supported.*/ /**<CNcomment:����������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_MODEM_START,        /**<The modem starts. This event is not supported.*/ /**<CNcomment:MODEM��ʼ���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_MODEM_END,          /**<The modem ends. This event is not supported.*/ /**<CNcomment:MODEM�������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DETECT_DTMF,        /**<DTMF detection.*/ /**<CNcomment:DTMF���*/
    HI_UNF_VOIP_CH_EVENT_DETECT_FSK,         /**<Frequency shift keying (FSK) detection. This event is not supported.*/ /**<CNcomment:FSK��⣬�ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DETECT_BUSY_TONE,   /**<Busy tone detection. This event is not supported.*/ /**<CNcomment:æ����⣬�ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM,         /**<Real-time Transport Control Protocol (RTCP) alarm. This event is not supported.*/ /**<CNcomment:RTCP�澯���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_GENCALLID_FAILED,   /**<The caller number fails to be displayed. This event is not supported.*/ /**<CNcomment:������ʾʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_STOPCALLID_FAILED,  /**<The displaying of the caller number fails to be disabled. The event is not supported.*/ /**<CNcomment:ͣ������ʾʧ�ܣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DATA_TONE,          /**<Signal tone related to comfort noise generator (CNG), V8, and V25. This event is not supported.*/ /**<CNcomment:CNG, V8, V25����ź������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_REMOTE_FAX_START,   /**<The chip detects that the peer end starts to transmits T38 packet.*/ /**<CNcomment:��⵽Զ�˿�ʼ���ʹ���(T38) ���ģ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_FSK_END,            /**<The FSK detection ends. This event is not supported.*/ /**<CNcomment:FSK�������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_DTMF_END,           /**<The DTMF detection ends. This event is not supported.*/ /**<CNcomment:DTMF�������ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_RTP_STATISTIC,      /**<Real-time Transport Protocol (RTP) statistics. This event is not supported.*/ /**<CNcomment:RTPͳ�ƣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_RTCP_ALARM_RESTORE, /**<The quality of service (QoS) alarm is restored. This event is not supported.*/ /**<CNcomment:QOS�澯�ָ����ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_VQM_STATISTIC,      /**<Voice quality monitor (VQM) statistics. This event is not supported.*/ /**<CNcomment:VQMͳ�ƣ��ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_PT_CHANGE,          /**<The packet type (PT) changes. This event is not supported.*/ /**<CNcomment:PT change���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_CHIP_FAULT,         /**<The chip is faulty. This event is not supported.*/ /**<CNcomment:DSP Fault���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_CLEAR_RTP,          /**<The RTCP statistics are cleared. This event is not supported.*/ /**<CNcomment:�����ϱ�RTCPͳ������ǰ��ͳ��ֵ���ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_ANI_START,          /**<Automatic number identification (ANI) signal detection starts. This event is not supported.*/ /**<CNcomment:ANI�źż�⣬�ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_ANI_END,            /**<ANI signal detection ends. This event is not supported.*/ /**<CNcomment:ANI�����¼����ݲ�֧��*/
    HI_UNF_VOIP_CH_EVENT_BUTT
} HI_UNF_VOIP_EVENT_E;


/**
Defines the enumeration type of the attribute ID of the VoIP channel. CNcomment:����VOIP ͨ������IDö������  CNend
Note: The enumeration type must be consistent with OPEN_CHN_PARA_ENUM in HME_Api.h. CNcomment:ע�� : ��ö�����ͱ�����HME_Api.h�е�OPEN_CHN_PARA_ENUM ����һ�¡�CNend
*/
typedef enum hiUNF_VOIP_ATTR_ID_E
{
    HI_UNF_VOIP_ATTR_ID_MAC = 1,        /**<Configuration parameter of the media access control (MAC) layer. This parameter is not supported.*/ /**<CNcomment:Mac�����ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_IPUDP = 2,      /**<Parameter of the IP User Datagram Protocol (UDP) layer. This parameter is not supported.*/ /**<CNcomment:IP UDP�����ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_DSP = 3,        /**<common DSP configuration parameter*/ /**<CNcomment:dsp common���ò��� */
    HI_UNF_VOIP_ATTR_ID_EC = 4,         /**<Echo cancellation (EC) configuration parameter*/ /**<CNcomment:ec���ò��� */
    HI_UNF_VOIP_ATTR_ID_JB = 5,         /**<Jitter buffer (JB) configuration parameter*/ /**<CNcomment:jb���ò��� */
    HI_UNF_VOIP_ATTR_ID_VQE = 6,        /**<Voice quality enhancement (VQE) configuration parameter*/ /**<CNcomment:VQE���ò��� */
    HI_UNF_VOIP_ATTR_ID_T38 = 7,        /**<T38 configuration parameter. This parameter is not supported.*/ /**<CNcomment:T38���ò���,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_DTMFINRTP = 8,  /**<DTMF in RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:Dtmf in rtp���ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_2198REDRTP = 9, /**< 2198Red RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:2198Red rtp���ò���,�ݲ�֧�� */
    HI_UNF_VOIP_ATTR_ID_RTCP = 10,      /**< 2198Red RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:2198Red rtp���ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_R2 = 11,        /**< 2198Red RTP configuration parameter. This parameter is not supported.*/ /**<CNcomment:2198Red rtp���ò��� ,�ݲ�֧��*/
    HI_UNF_VOIP_ATTR_ID_NET = 13,       /**<Network configuration parameter*/ /**<CNcomment:�������ò��� */
    HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV = 14,  /**<Audio device configuration parameter*/ /**<CNcomment:������Ƶ�豸���� */
    HI_UNF_VOIP_ATTR_ID_CFG_LOCAL_RECV_DIGITAL = 15,/**<Conifg DTMF receiving sign parameter*/ /**<CNcomment:����DTMF�պŲ��� */

    HI_UNF_VOIP_ATTR_ID_BUTT
}HI_UNF_VOIP_ATTR_ID_E;

/**Define voip audio device type. */
/**CNcomment:����VOIP��Ƶ�豸ö������*/
typedef enum hiUNF_VOIP_AUDIO_DEVICE_E
{
    HI_UNF_VOIP_AUD_DEV_SIO = 0,     /**< SIO */
    HI_UNF_VOIP_AUD_DEV_BLUETOOTH,   /**<Bluetooth*/ /**<CNcomment:���� */
    HI_UNF_VOIP_AUD_DEV_ALSA,        /**<Audio Device*/ /**<CNcomment:ALSA ��Ƶ�豸 */
    HI_UNF_VOIP_AUD_DEV_BUTT
}HI_UNF_VOIP_AUDIO_DEVICE_E;

/**Define voip audio device input and output type. */
/**CNcomment:����VOIP��Ƶ�豸�����������*/
typedef enum hiUNF_VOIP_AUDIO_DEVICE_TYPE_E
{
    HI_UNF_VOIP_AUD_OUT_DEV = 0,     /**<Audio output device*/ /**<CNcomment:��Ƶ����豸 */
    HI_UNF_VOIP_AUD_IN_DEV,          /**<Audio input device*/ /**<CNcomment:��Ƶ�����豸 */
    HI_UNF_VOIP_AUD_DEV_TYPE_BUTT
}HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E;


/**Defines the type-length-value (TLV) head.*/
/**CNcomment:����TLVͷ*/
typedef struct hiUNF_VOIP_TLV_HEAD_S
{
    HI_U16  u16BlockType;    /**<Block type. It corresponds to HI_UNF_VOIP_ATTR_ID_E in the data structure of the attribute of the VoIP channel.*/
                             /**<CNcomment:������ , VOIPͨ�����Խṹ���У���Ӧö������HI_UNF_VOIP_ATTR_ID_E */
    HI_U16  u16BlockLen;     /**<Block length*/ /**<CNcomment:�鳤�� , ��������*/
}HI_UNF_VOIP_TLV_HEAD_S;

/**Defines the length of the TLV head.*/
/**CNcomment:����TLVͷ����*/
#define HI_NUF_TVL_HEAD_LEN    ((HI_S32)sizeof(HI_UNF_VOIP_TLV_HEAD_S))

/**Flags indicating the change of the structure of the common DSP parameters*/
/**CNcomment:Dsp Common�����ṹ�����־λ */
typedef struct hiUNF_DSP_CHANGE_FLAG_S
{
    HI_U32   bit1WorkMode:1;           /**<Reserved, change of the working mode*/ /**<CNcomment:����, ����ģʽ��� */
    HI_U32   bit1ConnectMode:1;        /**<Change of the connection mode*/ /**<CNcomment:����ģʽ��� */
    HI_U32   bit1Codec:1;              /**<Encoding change of the local end*/ /**<CNcomment:���˱����� */
    HI_U32   bit1RtpPt:1;              /**<Change of the payload type of RTP*/ /**<CNcomment:RTP��Payload type��� */
    HI_U32   bit1PacketPeriod:1;       /**<Change of the packaging duration of the local end*/ /**<CNcomment:���˴��ʱ����� */
    HI_U32   bit1DtmfTransMode:1;      /**<Reserved, change of the DTMF transfer mode*/ /**<CNcomment:������DTMF����ģʽ��� */
    HI_U32   bit1V34Control:1;         /**<Reserved, change of V34 speed reduction*/ /**<CNcomment:������V34���ٱ����־ */
    HI_U32   bit25Resv:25;
}HI_UNF_DSP_CHANGE_FLAG_S;

/**Configuration of common DSP parameters*/
/**CNcomment:Dsp Common�������� */
typedef struct hiUNF_DSP_CONFIG_BODY_S
{
    HI_U8   u8WorkMode;      /**<Reserved. Working mode of the channel, corresponding to the change flag bit1WorkMode.*/
                             /**<CNcomment:����, ͨ������ģʽ ��Ӧ�����־ bit1WorkMode */
    HI_U8   u8ConnectMode;   /**<Connection mode, for controlling whether to transmit and receive RTP packets. It corresponds to the change flag bit1ConnectMode.\n
                                 The enumeration type enum TERMINAL_MODE is as follows: 0--Transmit data only; 1--Receive data only; 2--Transmit and receive data; 3--Do not transmit and receive data.*/
                             /**<CNcomment:����ģʽ, �����Ƿ��ͺͽ���RTP��, ��Ӧ�����־ bit1ConnectMode,\n
                                 ��Ӧö������enum TERMINAL_MODE :0--ֻ��������,1--ֻ��������,2--ͬʱ���ͺͽ���,3--�����ͺͲ���������*/
    HI_U16  u16Codec;        /**<Codec type of a VoIP channel, corresponding to the change flag bit1Codec.\n
                                 The enumeration type enum CODER_DECODER is as follows:0--G.711A, 1--G.711Mu, 2--G.722.*/
                             /**<CNcomment:VOIPͨ���ı��������,  ��Ӧ�����־ bit1Codec,\n
                                 ��Ӧö������enum CODER_DECODER:0--G.711A,1--G.711Mu,2--G.722.*/
    HI_U8   u8RtpPT;         /**<RTP payload type of the transmitted RTP packet head, corresponding to the change flag bit1RtpPt.\n
                                 The enumeration type enum EN_VOIP_MEDIA_PROTOCOL_TYPE is as follows: 0--G.711Mu, 8--G.711A, 9--G.722.\n
                                 Note that the type must be the same as u16Codec.*/
                             /**<CNcomment:���͵�RTP����ͷ�е�RTP��������, ��Ӧ�����־ bit1RtpPt ,\n
                                 ��Ӧö������enum EN_VOIP_MEDIA_PROTOCOL_TYPE:0 --  G.711Mu, 8--G.711A, 9--G.722 \n
                                 ע�������u16Codec���ͱ���һ�¡�*/
    HI_U8   u8PacketPeriod;     /**<Duration for packaging an RTP packet, corresponding to the change bit bit1PacketPeriod. The valid value is 10 ms, 20 ms, 30 ms, 40 ms, 50 ms, or 60 ms.*/
                                /**<CNcomment:RTP������ʱ������Чֵ[10,20,30,40,50,60]ms,  ��Ӧ�����־ bit1PacketPeriod */
    HI_U8   u8DtmfTransMode;    /**<Reserved. DTMF transfer mode, corresponding to the change flag bit1DtmfTransMode .*/
                                /**<CNcomment:������DTMF����ģʽ ��Ӧ�����־ bit1DtmfTransMode */
    HI_U8   u8V34Control;       /**<Reserved. Whether to support V34 speed reduction, corresponding to bit1V34Control*/
                                /**<CNcomment:�������Ƿ�֧��V34�������� ��Ӧ�����־ bit1V34Control */
}HI_UNF_DSP_CONFIG_BODY_S;


/**Structure of common DSP parameters*/
/**CNcomment:����Dsp Common�����ṹ */
typedef struct hiUNF_VOIP_DSP_CONFIG_PARA_S
{
    HI_UNF_DSP_CHANGE_FLAG_S stChange; /**<Change flag. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                       /**<CNcomment:�����־λ , �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_DSP_CONFIG_BODY_S stBody;   /**<DSP common configuration parameter*/
                                       /**<CNcomment:Dsp Common���ò��� */
}HI_UNF_VOIP_DSP_CONFIG_PARA_S;


/**Flags indicating the change of the structure of the DSP voice parameters*/
/**CNcomment:DSP������ز����ṹ�����־λ */
typedef struct hiUNF_VOICE_CHANGE_FLAG_S
{
    HI_U32   bit1EcEnable:1;          /**<EC change flag*/ /**<CNcomment:EC�����־ */
    HI_U32   bit1NlpEnable:1;         /**<Reserved, non-linear Processor (NLP) enable change flag.*/ /**<CNcomment:������NLPʹ�ܱ����־*/
    HI_U32   bit1NlpMode:1;           /**<Reserved, NLP mode change flag. It cannot be configured.*/ /**<CNcomment:������NLPģʽ�����־, ��֧������*/
    HI_U32   bit1VadEnable:1;         /**<Voice activity detector (VAD) parameter change flag*/ /**<CNcomment:Vad������� */
    HI_U32   bit1VadMode:1;           /**<Reserved, VAD mode change mode. It is not supported.*/ /**<CNcomment:������Vadģʽ�����־, Ŀǰ��֧��*/
    HI_U32   bit1CngEnable:1;         /**<Reserved, CNG enable change flag.*/ /**<CNcomment:������Cngʹ�ܱ����־*/
    HI_U32   bit1CngLevel:1;          /**<Reserved, CNG energy change flag.*/ /**<CNcomment:������Cngģʽ�����־*/
    HI_U32   bit1PlcMode:1;           /**<Reserved, packet loss compensation (PLC) mode change mode. Only one mode is supported.*/ /**<CNcomment:������PLCģʽ�����־ */
    HI_U32   bit1InputVolume:1;       /**<Input gain change flag*/ /**<CNcomment:����������� */
    HI_U32   bit1OutputVolume:1;      /**<Output gain change flag*/ /**<CNcomment:���������� */
    HI_U32   bit1InputMute:1;         /**<Input mute change flag*/ /**<CNcomment:���뾲����� */
    HI_U32   bit1OutputMute:1;        /**<Output mute change flag*/ /**<CNcomment:���������� */
    HI_U32   bit1InputGain:1;         /**<Input gain change flag*/ /**<CNcomment:���������� */
    HI_U32   bit1OutputGain:1;        /**<Output gain change flag*/ /**<CNcomment:��������� */
    HI_U32   bit18Resv:18;
}HI_UNF_VOICE_CHANGE_FLAG_S;

/**Configuration of DSP voice parameters*/
/**CNcomment:DSP������ز������� */
typedef struct hiUNF_VOICE_CONFIG_BODY_S
{
    HI_U8   u8EcEnableFlag;     /**<EC enable flag: 0 - EC off; 1 - EC on. It corresponds to the change flag bit1EcEnable.*/
                                /**<CNcomment:��������ʹ�ܱ�־: 0 -- EC Off , 1 -- EC On ,  ��Ӧ�����־ bit1EcEnable */
    HI_U8   u8NlpEnableFlag;    /**<Reserved, NLP enable flag. It corresponds to the change flag bit1NlpEnable.*/
                                /**<CNcomment:������ NLPʹ�ܱ�־,  ��Ӧ�����־ bit1NlpEnable */
    HI_U8   u8NlpMode;          /**<Reserved, NLP mode. It corresponds to the change bit bit1NlpMode.*/
                                /**<CNcomment:������NLPģʽ,    ��Ӧ�����־ bit1NlpMode */
    HI_U8   u8VadEnableFlag;    /**<VAD enable flag: 0 - VAD off; 1 - VAD on. It corresponds to the change flag bit1VadEnable.*/
                                /**<CNcomment:VADʹ�ܱ�־: 0 -- VAD Off , 1 -- VAD On , ��Ӧ�����־ bit1VadEnable */
    HI_U8   u8VadMode;          /**<Reserved, VAD mode. It corresponds to the change flag bit1VadMode.*/
                                /**<CNcomment:������VADģʽ,     ��Ӧ�����־ bit1VadMode */
    HI_U8   u8CngEnableFlag;    /**<Reserved, CNG enable flag. It corresponds to the change flag bit1CngEnable.*/
                                /**<CNcomment:������Cngʹ�ܱ�־,  ��Ӧ�����־ bit1CngEnable */
    HI_U8   u8CngLevel;         /**<Reserved, CNG energy. It corresponds to the change bit bit1CngLevel.*/
                                /**<CNcomment:������CNG����,    ��Ӧ�����־ bit1CngLevel */
    HI_U8   u8PlcMode;          /**<Reserved, PLC mode. It corresponds to the change bit bit1PlcMode.*/
                                /**<CNcomment:������PLCģʽ,     ��Ӧ�����־ bit1PlcMode */
    HI_U8   u8InputVolume;      /**<Input volume. Its value range is [0, 100]. The default value is 100. This parameter corresponds to the change bit bit1InputVolume.*/
                                /**<CNcomment:�������� [0 ~ 100] , ȱʡֵΪ100 ,  ��Ӧ�����־ bit1InputVolume */
    HI_U8   u8OutputVolume;     /**<Output volume. Its value range is [0, 100]. The default value is 100. This parameter corresponds to the change bit bit1OutputVolume.
                                    The sametime to set Volume & Gain, the priority of u8OutputVolume is less than s8OutputGain;
                                    To set Volume & Gain respectively, the last take effect*/
                                /**<CNcomment:������� [0 ~ 100] , ȱʡֵΪ100 , ��Ӧ�����־ bit1OutputVolume.
                                    ͬʱ�������������棬���������ȼ�С������; �ֱ��������������棬�����õ���Ч */
    HI_U8   u8InputMute;        /**<Input mute: Input Mute flag. This parameter corresponds to the change bit bit1InputMute.*/
                                /**<CNcomment:���뾲����־ : 0 -- UnMute , 1 -- Mute , ��Ӧ�����־ bit1InputMute */
    HI_U8   u8OutputMute;       /**<Output mute. Input Mute flag. This parameter corresponds to the change bit  bit1OutputMute.*/
                                /**<CNcomment:���������־ : 0 -- UnMute , 1 -- Mute , ��Ӧ�����־ bit1OutputMute */
    HI_S8   s8InputGain;        /**<Input gain. Its gain range is [-70 ~ 0]. The default value is 0. This parameter corresponds to the change bit bit1InputGain.*/
                                /**<CNcomment:�������� [-70, 0] , ȱʡֵΪ0 ,  ��Ӧ�����־ bit1InputGain */
    HI_S8   s8OutputGain;       /**<Output gain. Its value range is [-70 ~ 0]. The default value is 0. This parameter corresponds to the change bit bit1OutputGain.
                                    The sametime to set Volume & Gain, the priority of s8OutputGain is greater than u8OutputVolume;
                                    To set Volume & Gain respectively, the last take effect*/
                                /**<CNcomment:������� [-70, 0] , ȱʡֵΪ0 , ��Ӧ�����־ bit1OutputGain.
                                    ͬʱ�������������棬��������ȼ���������; �ֱ��������������棬�����õ���Ч */
    HI_U16  u16Rsev;
}HI_UNF_VOICE_CONFIG_BODY_S;

/**Structure of DSP voice parameters*/
/**CNcomment:����dsp���������ṹ */
typedef struct hiUNF_VOICE_CONFIG_PARA_S
{
    HI_UNF_VOICE_CHANGE_FLAG_S stChange;  /**<Change flag. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                          /**<CNcomment:�����־λ , �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_VOICE_CONFIG_BODY_S stBody;    /**<DSP voice configuration parameter*/ /**<CNcomment:�������ò��� */
}HI_UNF_VOICE_CONFIG_PARA_S;

/**Flags indicating the change of the structure of JB parameters*/
/**CNcomment:JB�����ṹ�����־λ */
typedef struct hiUNF_JB_CHANGE_FLAG_S
{
    HI_U32   bit1JbMode:1;      /**<Change flag of the JB mode*/ /**<CNcomment:JB ģʽ   �����־ */
    HI_U32   bit1JbInit:1;      /**<Change flag of the JB initial value*/ /**<CNcomment:JB ��ʼֵ �����־ */
    HI_U32   bit1JbMax:1;       /**<Change flag of the JB maximum value*/ /**<CNcomment:JB ���ֵ �����־ */
    HI_U32   bit1JbMin:1;       /**<Reserved, change flag of the JB minimum value*/ /**<CNcomment:������JB ��Сֵ �����־ */
    HI_U32   bit28Resv:28;
}HI_UNF_JB_CHANGE_FLAG_S;

/**JB parameter configuration*/
/**CNcomment:JB�������� */
typedef struct hiUNF_JB_CONFIG_BODY_S
{
    HI_U8  u8JbMode;           /**<JB mode: 0 - dynamic JB; 1 - static JB. It corresponds to the change flag bit1JbMode.*/
                               /**<CNcomment:JitterBufferģʽ: 0--��̬JB , 1--��̬JB,  ��Ӧ�����־ bit1JbMode */
    HI_U8  u8JbInit;           /**<JB initial value. It ranges from 0 ms to 150 ms and corresponds to the change flag bit1JbInit.*/
                               /**<CNcomment:JitterBuffer�ĳ�ʼֵ [0 ~ 150]ms  ,��Ӧ�����־ bit1JbInit */
    HI_U8  u8JbMax;            /**<JB maximum value. It ranges from 0 ms to 150 ms and corresponds to the change flag bit1JbMax.*/
                               /**<CNcomment:JitterBuffer�����ֵ [0 ~ 150]ms , ��Ӧ�����־ bit1JbMax */
    HI_U8  u8JbMin;            /**<JB minimum value. It ranges from 0 ms to 150 ms and corresponds to the change flag bit1JbMin.*/
                               /**<CNcomment:������JitterBuffer����Сֵ  [0 ~ 150]ms  ,��Ӧ�����־ bit1JbMin */
}HI_UNF_JB_CONFIG_BODY_S;

/**Structure of JB parameters*/
/**CNcomment:����JB�����ṹ */
typedef struct hiUNF_JB_CONFIG_PARA_S
{
    HI_UNF_JB_CHANGE_FLAG_S stChange;  /**<Change flag. It is invalid when a channel is created and the JB parameters are not processed when channel attributes are modified.*/
                                       /**<CNcomment:�����־λ ,  ����ͨ��ʱ��Ч���޸�ͨ������ʱ������JB����*/
    HI_UNF_JB_CONFIG_BODY_S stBody;    /**<JB configuration parameter*/ /**<CNcomment:JB���ò��� */
}HI_UNF_JB_CONFIG_PARA_S;


/**Flags indicating the change of the structure of VQE parameters*/
/**CNcomment:VQE�����ṹ�����־λ */
/**The local end indicates MIC input, and the remote end indicates network input.*/
/**CNcomment:����ı�����ָmic����,Զ����ָ��������*/
typedef struct hiUNF_VQE_CHANGE_FLAG_S
{
    HI_U32   bit1LocalAgcFlag:1;   /**<Change flag of the automatic gain control (AGC) enable flag parameter of the local end*/ /**<CNcomment:����AGC ʹ�ܱ�־���� �����־ */
    HI_U32   bit1LocalAgcValue:1;  /**<Reserved, change flag of the target AGC value of the local end*/ /**<CNcomment:����������AGC Ŀ��ֵ �����־ */

    HI_U32   bit1RemoteAgcFlag:1;  /**<Change flag of the AGC enable flag parameter of the remote end*/ /**<CNcomment:Զ��AGC ʹ�ܱ�־���� �����־ */
    HI_U32   bit1RemoteAgcValue:1; /**<Reserved, change flag of the target AGC value of the remote end*/ /**<CNcomment:������Զ��AGC Ŀ��ֵ �����־ */

    HI_U32   bit1LocalAnrFlag:1;   /**<Change flag of the automatic noise reduction (ANR) enable flag parameter of the local end*/ /**<CNcomment:����ANR ʹ�ܱ�־���� �����־*/
    HI_U32   bit1LocalAnrValue:1;  /**<Reserved, change flag of the target ANR value of the local end*/ /**<CNcomment:������ANR Ŀ��ֵ �����־ */

    HI_U32   bit1RemoteAnrFlag:1;  /**<Change flag of the ANR enable flag parameter of the remote end*/ /**<CNcomment:Զ��ANR ʹ�ܱ�־���� �����־*/
    HI_U32   bit1RemoteAnrValue:1; /**<Reserved, change flag of the target ANR value of the remote end*/ /**<CNcomment:������ANR Ŀ��ֵ �����־ */

    HI_U32   bit24Resv:24;
}HI_UNF_VQE_CHANGE_FLAG_S;

/**VQE parameter configuration*/
/**CNcomment:VQE�������� */
typedef struct hiUNF_VQE_CONFIG_BODY_S
{
    HI_U8   u8LocalAgcFlag;         /**<AGC enable flag of the local end: 0 - AGC off; 1 - AGC on. It corresponds to the change flag bit1LocalAgcFlag.*/
                                    /**<CNcomment:����AGC ʹ�ܱ�־: 0 -- Agc Off , 1 -- Agc On , ��Ӧ�����־ bit1LocalAgcFlag */
    HI_U8   u8LocalAgcValue;        /**<Reserved, automatic gain adjustment parameter of the local end.
                                                            Its value ranges from 0 to 15. The value 0 indicates -24 dB, and the value 15 indicates -9 dB. The default value is 13.
                                                            This parameter corresponds to the change flag bit1LocalAgcValue.*/
                                    /**<CNcomment:�����������Զ������������,
                                                            [0 ~ 15] ��Ӧ ʵ�����ܲ�����-9dBm0 ~ -24dBm0, ȱʡֵ13 ,
                                                            ��Ӧ�����־ bit1LocalAgcValue */
    HI_U8   u8RemoteAgcFlag;        /**<AGC enable flag of the remote end: 0 - AGC off; 1 - AGC on. It corresponds to the change flag bit1RemoteAgcFlag.*/
                                    /**<CNcomment:Զ��AGC ʹ�ܱ�־: 0 -- Agc Off , 1 -- Agc On ,  ��Ӧ�����־ bit1RemoteAgcFlag */
    HI_U8   u8RemoteAgcValue;       /**<Reserved, automatic gain adjustment parameter of the remote end.
                                                            Its value ranges from 0 to 15. The value 0 indicates -24 dB, and the value 15 indicates -9 dB. The default value is 13.
                                                            This parameter corresponds to the change flag bit1RemoteAgcValue.*/
                                    /**<CNcomment:������Զ���Զ������������,
                                                            [0 ~ 15]��Ӧʵ�����ܲ�����-9dBm0 ~ -24dBm0, ȱʡֵ13 ,
                                                            ��Ӧ�����־ bit1RemoteAgcValue */
    HI_U8   u8LocalAnrFlag;         /**<ANR enable flag of the local end: 0 - ANR off; 1 - ANR on. It corresponds to the change flag bit1LocalAnrFlag.*/
                                    /**<CNcomment:����ANR ʹ�ܱ�־: 0 -- Anr Off , 1 -- Anr On ,  ��Ӧ�����־ bit1LocalAnrFlag */
    HI_U8   u8LocalAnrValue;        /**<Reserved, target ANR value of the local end (background noise reduction parameter). It corresponds to the change flag bit1LocalAnrValue.*/
                                    /**<CNcomment:����������ANR Ŀ��ֵ(�����������Ƶ�������) ,  ��Ӧ�����־ bit1LocalAnrValue */

    HI_U8   u8RemoteAnrFlag;        /**<ANR enable flag of the remote end: 0 - ANR off; 1 - ANR on. It corresponds to the change flag bit1RemoteAnrFlag.*/
                                    /**<CNcomment:Զ��ANR ʹ�ܱ�־: 0 -- Anr Off, 1 -- Anr On   , ��Ӧ�����־ bit1RemoteAnrFlag */
    HI_U8   u8RemoteAnrValue;       /**<Reserved, target ANR value of the remote end (background noise reduction parameter). It corresponds to the change flag bit1RemoteAnrValue.*/
                                    /**<CNcomment:������Զ��ANR Ŀ��ֵ(�����������Ƶ�������)  ,   ��Ӧ�����־ bit1RemoteAnrValue */
}HI_UNF_VQE_CONFIG_BODY_S;


/**Structure of VQE parameters*/
/**CNcomment: ����VQE�����ṹ */
typedef struct hiUNF_VQE_CONFIG_PARA_S
{
    HI_UNF_VQE_CHANGE_FLAG_S stChange;  /**<Change flag. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                        /**<CNcomment:�����־λ , �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_VQE_CONFIG_BODY_S stBody;    /**<VQE configuration parameter*/ /**<CNcomment:VQE���ò��� */
}HI_UNF_VQE_CONFIG_PARA_S;


/**Flags indicating the change of the structure of network parameters*/
/**CNcomment:��������ṹ�����־λ */
typedef struct hiUNF_NET_CHANGE_FLAG_S
{
   HI_U32   bit1SrcIP:1;     /**<Change flag of the source IP address. It indicates that 32SrcIPLen and u8SrcIP[16] change.*/
                             /**<CNcomment:source ip������, 32SrcIPLen��u8SrcIP[16]�и���*/
   HI_U32   bit1DstIP:1;     /**<Change flag of the destination IP address. It indicates that u32DstIPLen and u8DstIP[16] change.*/
                             /**<CNcomment:dest ip������, u32DstIPLen��u8DstIP[16]�и���*/
   HI_U32   bit1SrcPort:1;   /**<Change flag of the source port. It indicates that u16SrcPort changes.*/
                             /**<CNcomment:source port ������,u16SrcPort�и���*/
   HI_U32   bit1DstPort:1;   /**<Change flag of the destination port. It indicates that u16DstPort changes.*/
                             /**<CNcomment:dest port������,u16DstPort�и���*/
   HI_U32   bit1IPTos:1;     /**<Change flag of the IP service type. It indicates that u32IPTos and u32Mask change.*/
                             /**<CNcomment:IP�������ͱ�����,u32IPTos��u32Mask�и���*/
   HI_U32   bit1Vlan:1;      /**<Virtual local area network (VLAN) change flag, reserved. It indicates that u32VlanEn, u32VlanPri, and u32VlanPid change.*/
                             /**<CNcomment:Vlan������,u32VlanEn,u32VlanPri,u32VlanPid�и��ģ�����*/
   HI_U32   bit1Protocol:1;  /**<Change flag of the protocol type, reserved. Only Internet Protocol version 4 (IPv4) is supported currently.*/
                             /**<CNcomment:Э�����ͱ����ǣ�Ŀǰֻ֧��IPV4,����*/
   HI_U32   bit25Resv:25;
}HI_UNF_NET_CHANGE_FLAG_S;

/**Network parameter configuration*/
/**CNcomment:����������� */
typedef struct hiUNF_NET_CONFIG_BODY_S
{
   HI_U32   u32SrcIPLen;       /**<Length of the source IP address. The IP address is 4 bytes (IPv4) or 16 bytes (IPv6). Other values are invalid.*/
                               /**<CNcomment:source ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
   HI_U8    u8SrcIP[16];       /**<Source IP address. The IP address is 4 bytes (IPv4) or 16 bytes (IPv6), but is not a string. For a 4-byte IP address, 192.168.1.1 for example, each segment occupies one byte.*/
                               /**<CNcomment:source ip��ַ��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ�������192.168.1.1Ϊ����4�ֽ�����Ϊ192,168,1,1 */
   HI_U32   u32DstIPLen;       /**<Length of the destination IP address. The IP address is 4 bytes (IPv4) or 16 bytes (IPv6). Other values are invalid.*/
                               /**<CNcomment:dest ip��ַ���ȣ�4(IPV4)��16(IPV6)������ֵ��Ч*/
   HI_U8    u8DstIP[16];       /**<Destination IP address. The address is 4 bytes (IPv4) or 16 bytes (IPv6), but is not a string.*/
                               /**<CNcomment:dest ip��ַ��4�ֽ�(IPV4)��16�ֽ�(IPV6)�������ַ���*/

   HI_U16   u16SrcPort;        /**<Source RTP port number. The RTP port number must be an even number, and the corresponding RTCP port number is the RTP port number plus 1.*/
                               /**<CNcomment:source RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1 */
   HI_U16   u16DstPort;        /**<Destination RTP port number. The RTP port number must be an even number, and the corresponding RTCP port number is the RTP port number plus 1.*/
                               /**<CNcomment:dest RTP �˿ںţ�ӦΪż������ӦRTCP�˿ں�Ϊ����ֵ+1 */

   HI_U32   u32Mask;        /**<bit0: u32IPTos valid*/
   HI_U32   u32IPTos;       /**<IP service type, 8 bits*/ /**<CNcomment:IP��������,8bit*/
   HI_U32   u32VlanEn;      /**<VLAN enable, reserved. 0 - VLAN invalid; 1 - VLAN valid*/ /**<CNcomment:vlanʹ��: 0--vlan ��Ч,1--vlan ��Ч, ����*/
   HI_U32   u32VlanPri;     /**<VLAN priority, 3 bits, reserved. It is valid when u32VlanEn is set to 1.*/ /**<CNcomment:vlan���ȼ�,3bit, vlanΪ1ʱ��Ч, ����*/
   HI_U32   u32VlanPid;     /**<VLAN PID, 12 bits, reserved. It is valid when u32VlanEn is 1.*/ /**<CNcomment:vlan pid, 12bit, vlanΪ1ʱ��Ч, ����*/
   HI_U32   u32Protocol;    /**<Protocol type, reserved. 0x0800 - IPv4; 0x86dd - IPv6*/ /**<CNcomment:Э������,0x0800--IPV4, 0x86dd--IPV6, ����*/
}HI_UNF_NET_CONFIG_BODY_S;

/**Configuration of the network parameter structure*/
/**CNcomment:������������ṹ */
typedef struct hiUNF_NET_CONFIG_PARA_S
{
    HI_UNF_NET_CHANGE_FLAG_S stChange;  /**<Flag indicating the change of network parameters. This flag must be set when you create or change a channel.*/
                                        /**<CNcomment:������������־λ ,�������޸�ͨ��ʱ��Ӧλ��������*/

    HI_UNF_NET_CONFIG_BODY_S stBody;    /**<Network configuration parameter*/ /**<CNcomment:�������ò��� */
}HI_UNF_NET_CONFIG_PARA_S;

/**Flags indicating the change of audio device parameters*/
/**CNcomment:��Ƶ�豸���������־*/
typedef struct hiUNF_AUDDEV_FLAG_S
{
    HI_U32   bit1AudioDevId:1;        /**<Change flag of ID of the audio device*/ /**<CNcomment:AudioDevId �����־ */
    HI_U32   bit1AiAttrChange:1;      /**<Change flag of audio input (AI) SampleRate/BitPerSample/Channels*/ /**<CNcomment:AI SampleRate/BitPerSample/Channels�����־ */
    HI_U32   bit1AoAttrChange:1;      /**<Change flag of audio output (AO) SampleRate/BitPerSample/Channels*/ /**<CNcomment:AO SampleRate/BitPerSample/Channels�����־ */
    HI_U32   bit29Resv:29;
}HI_UNF_AUDDEV_FLAG_S;

/**Audio device system parameters*/
/**CNcomment:��Ƶ�豸ϵͳ���� */
typedef struct hiUNF_AUDDEV_BODY_S
{
    HI_S32 s32AudioDevId;           /**<Audio device ID, [0]*/ /**<CNcomment:��Ƶ�豸ID , ��ο�HI_UNF_VOIP_AUDIO_DEVICE_E����*/

    /**AI parameters*/ /**CNcomment:��Ƶ������� */
    HI_S32 s32AiSampleRate;         /**<Sampling rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:������, [8000], [16000], [32000], [48000]*/
    HI_S32 s32AiBitPerSample;       /**<Bit depth, [16]*/ /**<CNcomment:��������, [16]*/
    HI_S32 s32AiChannels;           /**<Number of AI channels, [1]*/ /**<CNcomment:ͨ����, [1]*/

    /**AO parameters*/ /**CNcomment:��Ƶ�������*/
    HI_S32 s32AoSampleRate;         /**<Sampling rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:������, [8000], [16000], [32000], [48000]*/
    HI_S32 s32AoBitPerSample;       /**<Bit depth, [16]*/ /**<CNcomment:��������, [16]*/
    HI_S32 s32AoChannels;           /**<Number of AO channels, [1]*/ /**<CNcomment:ͨ����, [1]*/

}HI_UNF_AUDDEV_BODY_S;

typedef struct hiUNF_DIGIT_CHANGE_FLAG_S
{
    HI_U32   bit1DigitEnable:1;      /**Digit enable*/ /**CNcomment:�պ�ʹ��   �����־ */
    HI_U32   bit28Resv:31;
}HI_UNF_DIGIT_CHANGE_FLAG_S;

/**Configuration of Digit parameter*/
/**CNcomment:�պŲ������� */
typedef struct hiUNF_DIGIT_CONFIG_BODY_S
{
    HI_U32  u32DigitEnableFlag;     /**Digit enable flag, 0:enable, 1:disable*/ /**CNcomment:�պ�ʹ�ܱ�־��0��ʾ��ʹ�ܣ�1��ʾʹ��*/
}HI_UNF_DIGIT_CONFIG_BODY_S;

typedef struct hiUNF_DIGIT_CONFIG_PARA_S
{
    HI_UNF_DIGIT_CHANGE_FLAG_S stChange;  /**<change flag of DTMF digit parameter*/ /**<CNcomment:DTMF�պŲ��������� */
    HI_UNF_DIGIT_CONFIG_BODY_S stBody;    /**<configuration parameter of DTMF digit*/ /**<CNcomment:DTMF�պ����ò��� */
}HI_UNF_DIGIT_CONFIG_PARA_S;

/**Audio device parameters*/
/**CNcomment:��Ƶ�豸����*/
typedef struct hiUNF_AUDDEV_PARA_S
{
    HI_UNF_AUDDEV_FLAG_S    stChang;        /**<Change flag of audio device parameters. It is valid when the attributes of a channel are modified and is invalid when a channel is created.*/
                                            /**<CNcomment:��Ƶ�豸���������ǣ� �޸�ͨ������ʱ��Ч������ͨ��ʱ��Ч*/
    HI_UNF_AUDDEV_BODY_S    stBody;         /**<Audio device configuration parameter*/ /**<CNcomment:��Ƶ�豸���ò���*/
}HI_UNF_AUDDEV_PARA_S;


/**Defines the attributes of a VoIP channel.*/
/**CNcomment:����VOIP ͨ������ */
typedef struct hiUNF_VOIP_CHN_ATTR_S
{
    HI_UNF_VOIP_TLV_HEAD_S stTlvHead;         /**<u16BlockType is invalid. u16BlockLen indicates the length of the entire HI_UNF_VOIP_CHN_ATTR_S.*/
                                              /**<CNcomment:���У�u16BlockType��Ч������u16BlockLen��ʾ����HI_UNF_VOIP_CHN_ATTR_S �ṹ�峤��*/

    HI_UNF_VOIP_TLV_HEAD_S stDspHead;         /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_DSP, and u16BlockLen is the length of HI_UNF_VOIP_DSP_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_DSP, u16BlockLenΪHI_UNF_VOIP_DSP_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_VOIP_DSP_CONFIG_PARA_S stDspPara;  /**<Common DSP configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:dsp common���ò�������ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stEcHead;          /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_EC, and u16BlockLen is the length of HI_UNF_VOICE_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_EC, u16BlockLenΪHI_UNF_VOICE_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_VOICE_CONFIG_PARA_S stEcPara;      /**<EC configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:Ec���ò���, ��ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stJBHead;          /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_JB, and u16BlockLen is the length of HI_UNF_JB_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_JB, u16BlockLenΪHI_UNF_JB_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_JB_CONFIG_PARA_S stJBPara;         /**<JB configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:JB���ò���, ��ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��Ч*/

    HI_UNF_VOIP_TLV_HEAD_S stVQEHead;         /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_VQE, and u16BlockLen is the length of HI_UNF_VQE_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_VQE, u16BlockLenΪHI_UNF_VQE_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_VQE_CONFIG_PARA_S stVQEPara;       /**<VQE configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:VQE���ò�������ͨ��ʱ�Ǳ�����޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stNetHead;         /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_NET, and u16BlockLen is the length of HI_UNF_NET_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_NET, u16BlockLenΪHI_UNF_NET_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_NET_CONFIG_PARA_S stNetPara;       /**<Network configuration parameter, optional*/
                                              /**<CNcomment:NET���ò�������ѡ��*/

    HI_UNF_VOIP_TLV_HEAD_S stAudevHead;       /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV, and u16BlockLen is the length of HI_UNF_AUDDEV_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_CFG_SYS_AUDEV, u16BlockLenΪHI_UNF_AUDDEV_PARA_S�ṹ�峤��*/
    HI_UNF_AUDDEV_PARA_S   stAudevPara;       /**<Audio device configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:��Ƶ�豸���ò�������ͨ��Ϊ������޸�ͨ��ʱ��ѡ*/

    HI_UNF_VOIP_TLV_HEAD_S stDigitHead;       /**<u16BlockType is HI_UNF_VOIP_ATTR_ID_CFG_DIGITAL, and u16BlockLen is the length of HI_UNF_DIGIT_CONFIG_PARA_S.*/
                                              /**<CNcomment:u16BlockType  ΪHI_UNF_VOIP_ATTR_ID_CFG_DIGITAL, u16BlockLenΪHI_UNF_DIGIT_CONFIG_PARA_S�ṹ�峤��*/
    HI_UNF_DIGIT_CONFIG_PARA_S stDigitPara;   /**<DTMF digit configuration parameter. This parameter is mandatory when you enable a channel and is optional when you modify a channel.*/
                                              /**<CNcomment:DTMF�պ����ò�������ͨ��Ϊ��ѡ��޸�ͨ��Ϊ��ѡ��*/
}HI_UNF_VOIP_CHN_ATTR_S;

/**Description of the basic frequency, reserved*/
/**CNcomment:����Ƶ������������*/
typedef struct hiUNF_VOIP_BASE_FREQ_INFO_S
{
    HI_U16  u16Frequence;        /**<Fundamental frequency*/ /**<CNcomment:����Ƶ��*/
    HI_U16  u16Amplitude;        /**<Fundamental amplitude*/ /**<CNcomment:��������*/
}HI_UNF_VOIP_BASE_FREQ_INFO_S;

/**Description of the basic cadence, reserved*/
/**CNcomment:������������������*/
typedef struct hiUNF_VOIP_CADENCE_INFO_S
{
    HI_U16  u16FreqFlag;        /**<Fundamental frequency flag*/ /**<CNcomment:ʹ�õĻ�����־*/
    HI_U16  u16Reserved;        /**<Reserved*/ /**<CNcomment:������*/
    HI_U16  u16OnTime;          /**<Valid time*/ /**<CNcomment:��Чʱ��*/
    HI_U16  u16OffTime;         /**<Mute time*/ /**<CNcomment:����ʱ��*/
}HI_UNF_VOIP_CADENCE_INFO_S;

/**Description of ringback tone parameters, reserved*/
/**CNcomment:��������������������*/
typedef struct hiUNF_VOIP_TONE_ATTR_S
{
    HI_UNF_VOIP_BASE_FREQ_INFO_S   stBaseFreqInfo[4]; /**<Description of the fundamental frequency*/ /**<CNcomment:����Ƶ������*/
    HI_U32                u32CadenceCount;            /**<Number of cadences*/ /**<CNcomment:���ĵ�����*/
    HI_U32                u32Resve;
    HI_UNF_VOIP_CADENCE_INFO_S     stCadenceInfo[8];  /**<Cadence description*/ /**<CNcomment:��������*/
}HI_UNF_VOIP_TONE_ATTR_S;

/**Descriptor of the playing attributes of the ringback tone, reserved*/
/**CNcomment:��������������������������*/
typedef struct hiUNF_VOIP_PLAY_TONE_ATTR_S
{
    HI_UNF_VOIP_TONE_ATTR_S stToneParam;    /**<Ringback tone parameter, reserved*/ /**<CNcomment:����������������*/
    HI_U32 u32MixFlag;                      /**<Mixing flag: 0 - not mixed; 1-mixed*/ /**<CNcomment:������־: 0--������, 1--����*/
    HI_U32 u32LoopTime;                     /**<Number of loop times: 0-not looped; 1-254: number of loop times; 255  -  keep playing*/
                                            /**<CNcomment:�ظ�����: 0--���ظ�, 1~254 -- �ظ�����, 255 -- һֱ����*/
}HI_UNF_VOIP_PLAY_TONE_ATTR_S;

/**Descriptor of the playing attributes of the audio file*/
/**CNcomment:��Ƶ�ļ���������������*/
typedef struct hiUNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S
{
    HI_U32 u32DataAddr;         /**<Audio file address*/ /**<CNcomment:��Ƶ�ļ���ַ*/
    HI_U32 u32DataLen;          /**<Audio file length*/ /**<CNcomment:��Ƶ�ļ�����*/
    HI_U16 u16SourceFormat;     /**<Audio file encoding type: 0 - G.711A; 1 - G.711Mu. Note: Only the standard WAV file of the 711 payload type is supported.*/
                                /**<CNcomment:��Ƶ�ļ���������: 0 -- G.711A, 1 -- G.711Mu. ע: Ŀǰֻ֧�ֲ���711���͵ı�׼wav�ļ������ļ�Ϊ�����ɡ�*/
    HI_U16 u16Resv;
    HI_U32 u32MixFlag;          /**<Mixing flag: 0 - not mixed; 1 - mixed*/ /**<CNcomment:������־: 0--������, 1--����*/
    HI_U32 u32Direction;        /**<Playing direction: 0 - play to the local end; 1 - play to the remote end (reserved)*/
                                /**<CNcomment:���ŷ���: 0--���ŵ�����, 1-- ���ŵ�Զ��*/
    HI_U32 u32LoopTime;         /**<Number of loop times: 0 - not looped; 1-254: number of loop times; 255  -  keep playing*/
                                /**<CNcomment:�ظ�����: 0--���ظ�, 1~254 -- �ظ�����, 255 -- һֱ����*/
}HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S;


/**Descriptor of the network quality*/
/**CNcomment:����������Ϣ������*/
typedef struct hiUNF_VOIP_NET_QUALITY_STATIC_INFO_S
{
    HI_U32 u32TotalLostPacket;              /**<Number of lost packets*/ /**<CNcomment:���ݶ���ͳ��*/
    HI_U32 u32LossFraction;                 /**<Packet loss rate (%)*/ /**<CNcomment:������(%) */
    HI_U32 u32Jitter;                       /**<Average jitter (ms)*/ /**<CNcomment:ƽ������(ms) */
    HI_U32 u32Delay;                        /**<Average delay (ms)*/ /**<CNcomment:ƽ��ʱ��(ms) */
}HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S;

/**Descriptor of the RTCP statistics*/
/**CNcomment:RTCPͳ����Ϣ������ */
typedef struct hiUNF_VOIP_RTCP_STATIC_INFO_S
{
    HI_U32 u32SendPacketNum;               /**<Number of transmitted packets*/ /**<CNcomment:���Ͱ�����*/
    HI_U32 u32SendBytes;                   /**<Number of transmitted bytes*/ /**<CNcomment:�����ֽ���*/
    HI_U32 u32RecPacketNum;
    HI_U32 u32RecBytes;
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stSendInfo;          /**<Transmission statistics*/ /**<CNcomment:����ͳ��*/
    HI_UNF_VOIP_NET_QUALITY_STATIC_INFO_S stRecvInfo;          /**<Reception statistics*/ /**<CNcomment:����ͳ��*/
}HI_UNF_VOIP_RTCP_STATIC_INFO_S;

/**Descriptor of the RTCP configuration*/
/**CNcomment:RTCP����������*/
typedef struct hiUNF_VOIP_CFG_RTCP_ATTR_S
{
    HI_U32 u32EnableFlag;               /**<RTCP statistics enable: 0 - disabled; 1 - enabled*/ /**<CNcomment:RTCPͳ��ʹ��: 0--��ʹ��, 1--ʹ��*/
    HI_U32 u32SendInterval;             /**<Interval of transmitting the RTCP report. Its value range is [500, 65535] and is in the unit of ms. The value must be an integral multiple of 500.*/
                                        /**<CNcomment:RTCP���淢�ͼ��, [500 ~ 65535] ms , ����Ϊ500ms��������*/
}HI_UNF_VOIP_CFG_RTCP_ATTR_S;


/*******************************Audio adapter module*********************************/
/*******************************CNcomment:��Ƶ����ģ��CNend ******************************/
#define HI_ALSA_AUD_DEV_NAME_LEN 32        /**<the length of ALSA audio device name*/ /**<CNcomment:ALSA ��Ƶ�豸������*/

/**Define Alsa soundcard information*/
/**CNcomment:����ALSA������Ϣ */
typedef struct hi_ALSA_CARD_INFO_S
{
    HI_S32 s32CardNo;           /**<ALSA soundcard number*/ /**<CNcomment:ALSA������ */
    HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enType;       /**<Input and output type of audio device*/ /**<CNcomment:��Ƶ�豸�����������*/
    HI_CHAR szName[HI_ALSA_AUD_DEV_NAME_LEN];     /**<ALSA soundcard name*/ /**<CNcomment:ALSA������*/
}HI_ALSA_CARD_INFO_S;


/**Attribute struct of audio device in audio adapter module*/
/**CNcomment:��Ƶ����ģ����Ƶ�豸���Խṹ�� */
typedef struct hiUNF_AUDADP_AUDDEV_PARA_S
{
    HI_S32 s32AudioDevId;      /**<ID of audio device*/ /**<CNcomment:��Ƶ�豸ID����ο� HI_UNF_VOIP_AUDIO_DEVICE_E ����*/

    /**Parameter of audio input device*/ /**CNcomment:��Ƶ�����豸���� */
    HI_S32 s32AiCardNo;        /**<ALSA soundcard number*/ /**<CNcomment:ALSA������ */
    HI_S32 s32AiSampleRate;    /**<sample rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:������, ��ЧֵΪ 8000, 16000, 32000, 48000*/
    HI_S32 s32AiBitPerSample;  /**<bit depth, [16]*/ /**<CNcomment:�������ȣ���ЧֵΪ16*/
    HI_S32 s32AiChannels;      /**<channels,[1]*/ /**<CNcomment:ͨ��������ЧֵΪ1*/

    /**Parameter of audio output device*/ /**CNcomment:��Ƶ����豸���� */
    HI_S32 s32AoCardNo;        /**<ALSA soundcard number*/ /**<CNcomment:ALSA������*/
    HI_S32 s32AoSampleRate;    /**<sample rate, [8000], [16000], [32000], [48000]*/ /**<CNcomment:������, ��ЧֵΪ 8000, 16000, 32000, 48000*/
    HI_S32 s32AoBitPerSample;  /**<bit depth, [16]*/ /**<CNcomment:�������ȣ���ЧֵΪ16*/
    HI_S32 s32AoChannels;      /**<channels,[1]*/ /**<CNcomment:ͨ��������ЧֵΪ1*/

}HI_UNF_AUDADP_AUDDEV_PARA_S;

/**Defines the type of the event transmitted by the VoIP audio adapter module.*/
/**CNcomment:������Ƶ����ģ���¼�����*/
typedef enum hiUNF_AUDADP_EVENT_E
{
    HI_UNF_AUDADP_EVENT_OPEN_SUCCESS,              /**<The audio device is started successfully.*/ /**<CNcomment:����Ƶ�豸�ɹ�*/
    HI_UNF_AUDADP_EVENT_OPEN_FAILURE,              /**<The audio device fails to be started.*/ /**<CNcomment:����Ƶ�豸ʧ��*/
    HI_UNF_AUDADP_EVENT_CLOSED,                    /**<The started audio device is stopped.*/ /**<CNcomment:��Ƶ�豸�ر�*/
    HI_UNF_AUDADP_EVENT_STREAM_ERROR,              /**<An audio stream error occurs when the audio device is started.*/ /**<CNcomment:��Ƶ����������*/
    HI_UNF_AUDADP_EVENT_BLUETOOTH_NOT_CONNECTED,   /**<The Bluetooth device is not connected.*/ /**<CNcomment:��������δ����*/
    HI_UNF_AUDADP_EVENT_BUTT
} HI_UNF_AUDADP_EVENT_E;

/**Defines the status type of the audio device.*/
/**CNcomment:������Ƶ�豸״̬*/
typedef enum hiUNF_AUDADP_STATUS_E
{
    HI_UNF_AUDADP_STATUS_CLOSED  = 0x00, /**<The audio device is stopped.*/ /**<CNcomment:��Ƶ�豸�ر� */
    HI_UNF_AUDADP_STATUS_OPENING,        /**<The audio device is being started.*/ /**<CNcomment:��Ƶ�豸���ڴ� */
    HI_UNF_AUDADP_STATUS_OPENED,         /**<The audio device is started.*/ /**<CNcomment:��Ƶ�豸�Ѵ�*/
    HI_UNF_AUDADP_STATUS_RUNNING,        /**<The audio data is being transmitted.*/ /**<CNcomment:��Ƶ�豸�������У�����������Ƶ����*/
    HI_UNF_AUDADP_STATUS_ERROR,          /**<The audio device fails to be started or the audio data fails to be transmitted.*/ /**<CNcomment:����Ƶ�豸������Ƶ����ʧ��*/
    HI_UNF_AUDADP_STATUS_BLUETOOTH_NOT_CONNECTED,   /**<The Bluetooth device is not connected.*/ /**<CNcomment:��������δ����*/
    HI_UNF_AUDADP_STATUS_BUTT
} HI_UNF_AUDADP_STATUS_E;

/**Defines data structure of the event transmitted by the VoIP audio adapter module.*/
/**CNcomment:������Ƶ����ģ���¼��ṹ��*/
typedef struct hiUNF_AUDADP_EVENT_S
{
    HI_S32 s32AudioDevId;              /**<Aaudio device index*/ /**<CNcomment:��Ƶ�豸ID����ο� HI_UNF_VOIP_AUDIO_DEVICE_E ����*/
    HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType;   /**<HI_TRUE: AI device; HI_FALSE: AO device*/ /**<CNcomment:��Ƶ�豸�����������*/
    HI_UNF_AUDADP_EVENT_E enEvent;     /**<Event type*/ /**<CNcomment:�¼�����*/
    HI_UNF_AUDADP_STATUS_E enStatus;   /**<Audio device status*/ /**<CNcomment:��Ƶ�豸״̬*/
    HI_U32 u32Args;                    /**<Private arguments transmitted by users when the event callback function is registered*/ /**<CNcomment:�û�˽������*/
}HI_UNF_AUDADP_EVENT_S;

/**Operating flag of audio device*/
/**CNcomment:��Ƶ�豸������־*/
typedef struct hiUNF_AUDDEV_OPT_FLAG_S
{
    HI_U32   bit1AudInDev:1;       /**<AI device*/ /**<CNcomment: �����豸������־ */
    HI_U32   bit1AudOutDev:1;      /**<AO device*/ /**<CNcomment:����豸������־ */
    HI_U32   bit30Resv:30;
}HI_UNF_AUDDEV_OPT_FLAG_S;


/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** \addtogroup     VOIP */
/** @{ */  /** <!--  [VOIP] */

/**
 \brief Initializes the VoIP module. CNcomment: ��ʼ��VOIPģ��CNend
 \attention \n
 \param N/A
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR  The device fails to be started. CNcomment:�豸�򿪴���CNend
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST  The device does not exist. CNcomment:�豸������CNend
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE  The file is not a device file. CNcomment:�����豸�ļ�CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT    The thread for processing VoIP events fails to be initialized. CNcomment:EVENT��ʼ��ʧ��CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_Init(HI_VOID);

/**
 \brief Deinitializes the VoIP module. CNcomment:ȥ��ʼ��VOIPģ��CNend
 \attention \n
 \param N/A
 \retval ::0 Success CNcomment:�ɹ�CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_DeInit(HI_VOID);

/**
 \brief Obtains the default configuration of an VoIP channel. CNcomment:��ȡȱʡ��VOIP ͨ������CNend
 \attention \n
        Ensure that the working mode of the VoIP channel to be created is correct. Only the voice mode HI_UNF_VOIP_MODE_VOIVE is supported.
        You are advised to obtain default attributes by calling this API before creating a VoIP channel. This avoids failure in creating a VoIP channel due to incomplete or incorrect parameters.
        CNcomment:����ȷ������Ҫ����VOIP ͨ������ģʽ��Ŀǰֻ֧������ģʽHI_UNF_VOIP_MODE_VOIVE
        ����VOIP ͨ��ǰ������ñ��ӿڣ���ȡ��Ĭ�����ԣ����ⴴ��VOIP ͨ��ʱ���ڲ�����ȫ����������´������ɹ�����CNend
 \param[in] enWorkMode       Working mode of a VoIP channel. For details, see ::HI_UNF_VOIP_WORKMODE_E. CNcomment:VOIP ͨ������ģʽ����μ�::HI_UNF_VOIP_WORKMODE_E
 \param[out] pstDefChAttr  Pointer to the default VoIP channel attributes. For details, see :HI_UNF_VOIP_CHN_ATTR_S. CNcomment:ָ�����ͣ�VOIP ͨ��Ĭ�����ԣ��μ�:HI_UNF_VOIP_CHN_ATTR_S  CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstDefChAttr);

/**
 \brief Creates a VoIP channel. CNcomment:����VOIP ͨ��CNend
 \attention \n
 Before creating a VoIP channel, you are advised to obtain default channel attributes by calling HI_UNF_VOIP_GetChDefaultAttr() and modify parameter values as required.
 CNcomment:����ͨ��ǰ�������ȵ���HI_UNF_VOIP_GetChDefaultAttr()��ȡĬ��ͨ�����ԣ��ٶԲ�������Ҫ�޸ġ�CNend
 \param[in] enWorkMode       Working mode of a VoIP channel. For details, see ::HI_UNF_VOIP_WORKMODE_E. CNcomment:VOIP ͨ������ģʽ����μ�::HI_UNF_VOIP_WORKMODE_E  CNend
 \param[in]  pstChAttr  Pointer to VoIP channel attributes. For details, see ::HI_UNF_VOIP_CHN_ATTR_S. CNcomment:ָ�����ͣ�VOIP ͨ�����ԣ���μ�::HI_UNF_VOIP_CHN_ATTR_S  CNend
 \param[out] phVoip   Pointer to the handle of a created VoIP channel CNcomment:ָ�����ͣ�������VOIP ͨ�����CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::HI_ERR_VOIP_HME_CREATE_ERR   A channel fails to be created. CNcomment:����ͨ��ʧ��CNend
 \retval ::Other values  A channel fails to be created. CNcomment:����  ����ͨ��ʧ��CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_WORKMODE_E enWorkMode, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr, HI_HANDLE *phVoip);

/**
 \brief Destroys a VoIP channel. CNcomment:����VOIP ͨ��CNend
 \attention \n
N/A
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  The parameter is invalid. CNcomment:��Ч����CNend
 \retval ::HI_ERR_VOIP_HME_DESTROY_ERR   A channel fails to be destroyed. CNcomment:����ͨ��ʧ��CNend
 \retval ::Other values  A channel fails to be destroyed. CNcomment:����  ����ͨ��ʧ��CNend
 \see \n
N/A
 */
 HI_S32 HI_UNF_VOIP_DestroyChannel(HI_HANDLE hVoip);

/**
 \brief Obtains the configuration of a VoIP channel. CNcomment:��ȡVOIP ͨ������CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[out] pstChAttr  Pointer to VoIP channel attributes. For details, see :HI_UNF_VOIP_CHN_ATTR_S. CNcomment:ָ�����ͣ�VOIP ͨ�����ԣ��μ�:HI_UNF_VOIP_CHN_ATTR_S  CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  Channel attributes fail to be obtained. CNcomment:����  ��ȡͨ������ʧ��CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_GetChAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

/**
 \brief Modifies the configuration of a VoIP channel. CNcomment:�޸�VOIP ͨ������CNend
 \attention \n
        You are advised to obtain the current channel configuration by calling HI_UNF_VOIP_GetChAttr(), and modify parameter values as required. Set the corresponding change flags to 1, and set irrelevant change flags to 0.
        CNcomment:�����ȵ���HI_UNF_VOIP_GetChAttr()��ȡ��ǰͨ�����ã��ٶԲ�������Ҫ�޸ģ���Ӧ�ĸ��ı����1���޹ظ��ı�־��0��CNend
 \param[in] hVoip  VoIP channel handle CNcomment:VOIPͨ�����CNend
 \param[in] pstChAttr  Pointer to VoIP channel attributes. For details, see :HI_UNF_VOIP_CHN_ATTR_S. CNcomment:ָ�����ͣ�VOIP ͨ�����ԣ��μ�:HI_UNF_VOIP_CHN_ATTR_S  CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  Channel attributes fail to be modified. CNcomment:����  �޸�ͨ������ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_ModifyChnAttr(HI_HANDLE hVoip, HI_UNF_VOIP_CHN_ATTR_S *pstChAttr);

#if 0
/**
 \brief Obtains the sub attributes of a VoIP channel. CNcomment:��ȡVOIP ͨ��������CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] enAttrID  ID of the VoIP channel configuration parameter. For details, see :HI_UNF_VOIP_ATTR_ID_E. CNcomment:VOIP ͨ�����ò���ID���μ�: HI_UNF_VOIP_ATTR_ID_E  CNend
 \param[out] pChSubAttr  Pointer to the sub attributes of a VoIP channel. The data structure corresponds to enAttrID. CNcomment:ָ�����ͣ�VOIP ͨ�������ԣ��ṹ����enAttrID ��Ӧ��CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  Channel attributes fail to be obtained. CNcomment:����  ��ȡͨ������ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_GetChSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief Modifies the sub attributes of a VoIP channel. CNcomment:�޸�VOIP ͨ��������CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] enAttrID  ID of the VoIP channel configuration parameter. For details, see :HI_UNF_VOIP_ATTR_ID_E. CNcomment:VOIP ͨ�����ò���ID���μ�: HI_UNF_VOIP_ATTR_ID_E  CNend
 \param[out] pChSubAttr  Pointer to the sub attributes of a VoIP channel. The data structure corresponds to enAttrID. CNcomment:ָ�����ͣ�VOIP ͨ�������ԣ��ṹ����enAttrID ��Ӧ��CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  Channel attributes fail to be modified. CNcomment:����  �޸�ͨ������ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_ModifyChnSubAttr(HI_HANDLE hVoip, HI_UNF_VOIP_ATTR_ID_E enAttrID, HI_VOID *pChSubAttr);

/**
 \brief Plays the ringback tone. CNcomment:���Ż�����CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] pstToneAttr  Pointer to the ringback tone playing parameter. For details, see :HI_UNF_VOIP_PLAY_TONE_ATTR_S. CNcomment:ָ�����ͣ����������Ų������μ�: HI_UNF_VOIP_PLAY_TONE_ATTR_S  CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  The ringback tone fails to be played. CNcomment:����  ���Ż�����ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_PlayTone(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_TONE_ATTR_S *pstToneAttr);

/**
 \brief Stops playing the ringback tone. CNcomment:ֹͣ���Ż�����CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::Other values  The ringback tone fails to be stopped. CNcomment:����  ֹͣ���Ż�����ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_StopTone(HI_HANDLE hVoip);
#endif

/**
 \brief Plays an audio file. CNcomment:������Ƶ�ļ�CNend
 \attention \n
        Only the standard WAV file of the 711 payload type is supported. CNcomment:Ŀǰֻ֧�ֲ���711���͵ı�׼wav�ļ������ļ�Ϊ�����ɡ�CNend
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] pstAnnAttr  Pointer to the audio file playing parameter. For details, see :HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S.
                        CNcomment:ָ�����ͣ���Ƶ�ļ����Ų������μ�: HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S  CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  The audio file fails to be played. CNcomment:����  ������Ƶ�ļ�ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_PlayAnnouncement(HI_HANDLE hVoip, HI_UNF_VOIP_PLAY_ANNOUNCEMENT_ATTR_S *pstAnnAttr);

/**
 \brief Stops playing an audio file. CNcomment:ֹͣ������Ƶ�ļ�CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] u32Direction  Playing direction. It must be the same as the value of u32Direction (audio file playing attribute).
            CNcomment:���ŷ��򣬱�������Ƶ�ļ����������е�u32Direction ����һ�¡�CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::Other values  The audio file fails to be stopped. CNcomment:����  ֹͣ ������Ƶ�ļ�ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_StopAnnouncement(HI_HANDLE hVoip, HI_U32 u32Direction);

/**
 \brief  Defines the type of the event callback function. CNcomment:�����¼��ص���������CNend
 \attention \n
N/A
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] enEvent     Event type enumeration. For details, see the definition of :HI_UNF_VOIP_EVENT_E . CNcomment:ö�����ͣ���ʾ�¼����ͣ��μ�: HI_UNF_VOIP_EVENT_E ����CNend
 \param[in] s32EventValue  Event type parameter. It can be used to add output parameters to events, for example, adding the error codes to error events.
                           CNcomment:�¼����Ͳ���������Ϊevent����һЩ��������� ��������¼��Ĵ�����CNend
 \param[in] u32Args        Transferred args parameter during registration CNcomment:ע��ʱ�����args������CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::Other values   Failure CNcomment:����  ʧ��CNend
 \see \n
N/A
 */
typedef HI_S32 (*HI_UNF_VOIP_EVENT_CB_FN)(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args);


/**
 \brief Registers an event. CNcomment:ע���¼�CNend
 \attention \n
N/A
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] pfnEventCB  Pointer to the callback function corresponding to the registered event. The null pointer indicates unregistration.
                        CNcomment:�ص�����ָ�룬ָ����ע���¼���Ӧ�Ļص�������ָ��ΪNULL��ʾUnRegister  CNend
 \param[in] u32Args     Private parameter of a callback function. This parameter is transferred to the callback function when the callback function is called.
                        CNcomment:�ص�����˽�в������˲����ڻص����������õ�ʱ��ᴫ�ݸ��ص�������CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NOT_EXIST   The channel does not exist. CNcomment:ͨ��������CNend
 \see \n
N/A
 */
HI_S32 HI_UNF_VOIP_RegisterEvent(HI_HANDLE hVoip, HI_UNF_VOIP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);


/**
 \brief Obtains the RTCP statistics. CNcomment:��ȡRTCPͳ����ϢCNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[out] pstRtcpInfo  Pointer to RTCP statistics. For details, see :HI_UNF_VOIP_RTCP_STATIC_INFO_S. CNcomment:ָ�����ͣ�RTCPͳ����Ϣ���μ�: HI_UNF_VOIP_RTCP_STATIC_INFO_S  CNend
 \retval ::0 Success CNcomment:
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values  The RTCP statistics fail to be obtained. CNcomment:����  ��ȡRTCPͳ����Ϣʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_GetRtcpStaticInfo(HI_HANDLE hVoip, HI_UNF_VOIP_RTCP_STATIC_INFO_S * pstRtcpInfo);

/**
 \brief  Performs the RTCP configuration. CNcomment:RTCP����CNend
 \attention \n
 \param[in] hVoip  VoIP channel handle CNcomment:VOIP ͨ�����CNend
 \param[in] pstRtcpAttr  Pointer to RTCP configuration. For details, see :HI_UNF_VOIP_CFG_RTCP_ATTR_S. CNcomment:ָ�����ͣ�RTCP���ã��μ�: HI_UNF_VOIP_CFG_RTCP_ATTR_S  CNend
 \retval ::0 Success CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The input parameter is invalid. CNcomment:��Ч���������CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The pointer is null. CNcomment:��ָ��CNend
 \retval ::Other values   RTCP configuration fails to be performed. CNcomment:����  RTCP����ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_VOIP_CfgRtcp(HI_HANDLE hVoip, HI_UNF_VOIP_CFG_RTCP_ATTR_S * pstRtcpAttr);


/*******************************Voip Audio Adapter***********************************/
/*******************************CNcomment:��Ƶ����ģ��CNend ******************************/

/**
 \brief Initializes the VoIP audio adapter module. CNcomment:��ʼ����Ƶ����ģ��CNend
 \attention \n
You must initialize the VoIP module before initializing the audio adapter module. CNcomment:�����ȳ�ʼ��VOIPģ���ٳ�ʼ����Ƶ����ģ��CNend
 \param N/A
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_DEV_OPEN_ERR Failed to open the device. CNcomment:���豸�ڵ�ʧ��CNend
 \retval ::HI_ERR_VOIP_HME_DEV_NOT_EXIST The device do not exist. CNcomment:�豸������CNend
 \retval ::HI_ERR_VOIP_HME_NOT_DEV_FILE It is not device file. CNcomment:�����豸�ļ�CNend
 \retval ::Other values    Failure CNcomment:����  ʧ��CNend
 \see \n
None
 */

HI_S32 HI_UNF_AUDADP_Init(HI_VOID);

/**
 \brief Deinitializes the VoIP audio adapter module. CNcomment:��Ƶ����ģ��ȥ��ʼ��CNend
 \attention \n
You are advised to deinitialize the audio adapter module after deinitializing the VoIP module. CNcomment:ȥ��ʼ����Ƶ����ģ��֮ǰ��ȥ��ʼ��VOIPģ�顣CNend
 \param N/A
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \see \n
None
 */

HI_S32 HI_UNF_AUDADP_DeInit(HI_VOID);

/**
 \brief Starts the audio device. CNcomment:����Ƶ�豸CNend
 \attention \n
You are advised to start the audio device immediately after initializing the audio adapter module. CNcomment:����Ƶ�豸֮ǰ���ʼ����Ƶ����ģ�顣CNend
 \param[in] pstAudDev   Parameters of the started audio device CNcomment:��Ƶ�豸����CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:��Ƶ�豸������־CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT  No Deinitialization CNcomment:δ��ʼ��CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The point is null. CNcomment:��ָ��CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA The parameter is invalid. CNcomment:��Ч����CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Open(HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudDev, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Stops the audio device. CNcomment:�ر���Ƶ�豸CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:��Ƶ�豸ID, ��ο� HI_UNF_VOIP_AUDIO_DEVICE_E ����CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:��Ƶ�豸������־CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT  No Deinitialization CNcomment:δ��ʼ��CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  The parameter is invalid. CNcomment:��Ч����CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Close(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Starts to transmit audio data. CNcomment:��ʼ��Ƶ���ݴ���CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:��Ƶ�豸ID, ��ο� HI_UNF_VOIP_AUDIO_DEVICE_E ����CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:��Ƶ�豸������־CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT   No Deinitialization CNcomment:δ��ʼ��CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The parameter is invalid. CNcomment:��Ч����CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Start(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Stops transmitting audio data. CNcomment:ֹͣ��Ƶ���ݴ���CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:��Ƶ�豸ID, ��ο� HI_UNF_VOIP_AUDIO_DEVICE_E ����CNend
 \param[in] stAudDevOptFlag  Operated object flag CNcomment:��Ƶ�豸������־CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT    No Deinitialization CNcomment:δ��ʼ��  CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA   The parameter is invalid. CNcomment:��Ч����CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_Stop(HI_S32 s32AudioDevId, HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag);

/**
 \brief Obtains the audio device status. CNcomment:��ȡ��Ƶ�豸״̬CNend
 \attention \n
 N/A
 \param[in] s32AudioDevIndex   ID of the aduio device CNcomment:��Ƶ�豸ID, ��ο� HI_UNF_VOIP_AUDIO_DEVICE_E ����CNend
 \param[in] bAudioInDev  HI_TRUE for AI device, HI_FALSE for AO device CNcomment:��Ƶ�豸�����������CNend
 \param[out] ps32Status  Returned audio device status CNcomment:��Ƶ�豸״̬CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ� CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT  No Deinitialization CNcomment:δ��ʼ��CNend
 \retval ::HI_ERR_VOIP_HME_NULL_PTR  The point is null. CNcomment:��ָ��CNend
 \retval ::HI_ERR_VOIP_HME_INVALID_PARA  The parameter is invalid. CNcomment:��Ч����CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_AudDev_GetStatus(HI_S32 s32AudioDevId, HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType, HI_UNF_AUDADP_STATUS_E *ps32Status);

/**
 \brief Defines the event callback function of the audio adapter. CNcomment:������Ƶ�����¼��ص�����CNend
 \attention \n
 N/A
 \param[in] pstAudadpEvent   Event structure CNcomment:��Ƶ�����¼����Խṹ��CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::others FAILURE CNcomment:���� ʧ��CNend
 \see \n
N/A
 */

typedef HI_S32 (*HI_UNF_AUDADP_EVENT_CB_FN)(HI_UNF_AUDADP_EVENT_S *pstAudadpEvent);

/**
 \brief Registers the callback function for audio adapter events. CNcomment:ע����Ƶ����ģ���¼��ص����� CNend
 \attention \n
 N/A
 \param[in] pfnEventCB   Pointer of the callback function. Null pointer indicates unregisteration. CNcomment:�¼��ص�����ָ�� , NULL ����ע���¼��ص�����.CNend
 \param[in] u32Args  Private parameter from user application. CNcomment:�û�˽������.CNend
 \retval ::0  HI_SUCCESS CNcomment:�ɹ�CNend
 \retval ::HI_ERR_VOIP_HME_NO_INIT   No Deinitialization CNcomment:δ��ʼ��CNend
 \see \n
N/A
 */

HI_S32 HI_UNF_AUDADP_RegisterEvent(HI_UNF_AUDADP_EVENT_CB_FN pfnEventCB, HI_U32 u32Args);

/**
 \brief Obtain ALSA audio device list. CNcomment:��ȡALSA��Ƶ�豸�б� CNend
 \attention \n
 \param[in] enAudioDevType  The input and output type of audio device. CNcomment:��Ƶ�豸�����������CNend
 \param[in] pstCardList   The point of ALSA audio device list. CNcomment:ALSA��Ƶ�豸�б�ָ��CNend
 \param[in] u32Max        The maximum device number of ALSA audio device list. CNcomment:ALSA��Ƶ�豸�б�����豸��ĿCNend
 \param[out] pu32Count    Obtained number of audio device CNcomment:��ȡ������Ƶ�豸��ĿCNend
 \retval ::HI_SUCCESS  Success CNcomment:�ɹ�CNend
 \retval ::Other Failure CNcomment:���� ʧ��CNend
 \see \n
N/A
 */

HI_S32 HI_ALSA_GetAudioDevList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudioDevType,HI_ALSA_CARD_INFO_S * pstCardList,HI_U32 u32Max,HI_U32 *pu32Count);

/**
 \brief Obtain sample rate range of audio device. CNcomment:��ȡ��Ƶ�豸�����ʷ�ΧCNend
 \attention \n
 Audio device must be in closed status. CNcomment:��Ƶ�豸���봦�ڹر�״̬.CNend
 \param[in] pstCardInfo  The information of ALSA audio device CNcomment:ALSA��Ƶ�豸��ϢCNend
 \param[out] pu32Min     The minimum sample rate of audio device CNcomment:��Ƶ�豸��С������CNend
 \param[out] pu32Max     The maximum sample rate of audio device CNcomment:��Ƶ�豸��������CNend
 \retval ::HI_SUCCESS  Success CNcomment:�ɹ�CNend
 \retval ::Other Failure CNcomment:���� ʧ��CNend
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
