
/**************************************************************************************************
Copyright (C), 1988-2010, Huawei Tech. Co., Ltd.
 
File name       : HME_commondefine.h
Author: [SuiShankun 00133284]      Version: 1.00       Date:[2010-3-17 15:01:44]
Description     : Define common data in HME system and system config
Others          : 
Function List   : 
        1: ...
History         : 
        Date                 Author                  ver         Modification
        
**************************************************************************************************/


#ifndef _HME_COMMON_DEFINE_H_
#define _HME_COMMON_DEFINE_H_

#include "HME_commontype.h"


#define HME_VERSTR_MINLEN               128           /*the minimum length of version string*/ /*CNcomment:�汾��ѯ�ַ�����С����*/

/* BEGIN: Modified by wangjuan, 2011/2/9   PN:WJ_CODE_Resample*/
#define HME_MAX_CHANNEL_COUNT           16            /*maximum support channel count definition*/ /*CNcomment:���֧��ͨ��������*/
#define HME_MAX_CONF_COUNT              16            /*maximum conference count*/ /*CNcomment:���Ļ᳡����*/
/* END:   Modified by wangjuan, 2011/2/9 */

/*audio device volume adjust range*/ /*CNcomment:��Ƶ�豸����������Χ*/
#define HME_AUDEV_VOLUME_MAX            65535         /*maximum value of device operation*/ /*CNcomment:�豸���������ֵ*/
#define HME_ENGINE_VOLUME_MAX           100           /*API interface operation range*/ /*CNcomment:API�ӿڵĲ�����Χ*/

/* BEGIN: Added by czg, 2010/11/5   PN:czg_st_1104_02*/
#define MAX_IP_ADDR_LEN  16
/* END:   Added by czg, 2010/11/5 */

/*returned value section definition according to component*/ /*CNcomment:����ֵ������ֶζ���*/

#define HME_ERR_BASE                     0x0000

#define HME_ERR_API                     (HME_ERR_BASE)                /*extern API layer*/ /*CNcomment:����API��*/
#define HME_ERR_TOPLEVEL                (HME_ERR_BASE + 0x1000)       /*business realization layer*/ /*CNcomment:ҵ��ʵ�ֲ�*/
#define HME_AUDIO                       (HME_ERR_BASE + 0x2000)       /*audio process module*/ /*CNcomment:��Ƶ����ģ�飨������Ƶ�豸�ͱ�����Ƶ����*/
#define HME_CONFER                      (HME_ERR_BASE + 0x3000)       /*conference module*/ /*CNcomment:����ģ��*/
#define HME_STREAM                      (HME_ERR_BASE + 0x4000)       /*stream module*/ /*CNcomment:��ģ��*/
#define HME_NET                         (HME_ERR_BASE + 0x5000)       /*net process*/ /*CNcomment:���紦��*/
#define HME_CODEC_MGR                   (HME_ERR_BASE + 0x6000)       /*error code base address of codec management module*/ /*CNcomment:CODEC����ģ��Ĵ������ַ*/
#define HME_DTMF                        (HME_ERR_BASE + 0x7000)       /*dtmf module*/ /*CNcomment:dtmfģ��*/
#define HME_OS_ERR_BASE                 (HME_ERR_BASE + 0xf000)       /*system function error*/ /*CNcomment:ϵͳ����������ӡ��־ʱ���Ҫ���ϴ�����*/

#define HME_SSM                         (HME_ERR_BASE + 0x7000)       /*SSM*/


/*define return value*/ /*CNcomment:HME VE API ����ֵö�ٶ��壬�趨�嵽����ͷ�ļ�*/
typedef enum _HME_ERRNO_ENUM
{
    HME_ERR_FAILURE                     = -1,
    HME_ERR_OK                          = 0,
    HME_ERR_ERROR                       = 1
} HME_LIB_RESULT;

/*define error number*/ /*CNcomment:��ش����붨��*/
#define HME_ERR_UNKNOWN                     (HME_ERR_API + 1)  /*unknow error*/ /*CNcomment:δ֪����*/
#define HME_ERR_INVALPARAM                  (HME_ERR_API + 2)  /*invalid parameter*/ /*CNcomment:��Ч�Ĳ���*/
#define HME_ERR_INVALCHANNELID              (HME_ERR_API + 3)  /*invalid channel ID*/ /*CNcomment:��Чͨ����*/
#define HME_ERR_INVALNETPORT                (HME_ERR_API + 4)  /*invalid IP or port*/ /*CNcomment:��ЧIP��ַ��˿ں�*/
#define HME_ERR_UNINITIALIZE                (HME_ERR_API + 5)  /*not initialize libarary*/ /*CNcomment:��û�г�ʱ��*/
#define HME_ERR_NOT_IMPLEMENTED             (HME_ERR_API + 6)  /*contion not meet*/ /*CNcomment:�Ⱦ�����������*/
#define HME_ERR_NOT_SUPPORT_BY_VERSION      (HME_ERR_API + 7)  /*not support temporarily*/ /*CNcomment:�����ݲ�֧��*/
#define HME_ERR_LOG_INIT                    (HME_ERR_API + 8)  /*log error*/ /*CNcomment:��־��������*/
#define HME_ERR_STARTUP_FAIL                (HME_ERR_API + 9)  /*start up fail*/
#define HME_ERR_DELETE_FAIL                 (HME_ERR_API + 10) /*del up fail*/

/* BEGIN: Added by czg, 2010/10/8 */
#define HME_AGC_DISABLE  0      /*AGC disable*/ /*CNcomment:���ܹر�*/
#define HME_AGC_ENABLE   1      /*AGC enable*/ /*CNcomment:���ܿ���*/
#define HME_EC_DISABLE   0      /*EC disable*/ /*CNcomment:���ܹر�*/
#define HME_EC_ENABLE    1      /*EC enable*/ /*CNcomment:���ܿ���*/
#define HME_ANR_DISABLE  0      /*ANR disable*/ /*CNcomment:���ܹر�*/
#define HME_ANR_ENABLE   1      /*ANR enable*/ /*CNcomment:���ܿ���*/
/* END:   Added by czg, 2010/10/8 */

#define HME_CODECNAME_MAX_LEN 30

#if 0
/*soft gain*/ /*CNcomment:�����涨��ֵ*/
#define HME_SOFT_GAIN_BASE_VALUE     10
#else
#define HME_SOFT_GAIN_BASE_VALUE     0
#endif

/*define samplerate, unit by HZ*/ /*CNcomment:�����ʶ���,��λHZ*/
#define HME_SAMPLERATE_8000              8000
#define HME_SAMPLERATE_11025             11025
#define HME_SAMPLERATE_16000             16000
#define HME_SAMPLERATE_22050             22050
#define HME_SAMPLERATE_24000             24000
#define HME_SAMPLERATE_32000             32000
#define HME_SAMPLERATE_44100             44100
#define HME_SAMPLERATE_48000             48000

/*define precision of samplerate*/ /*CNcomment:�������ȶ���*/
#define HME_16B_PER_SAMPLE               16
#define HME_8B_PER_SAMPLE                8

/*the duration of PCM, unit by ms*/ /*CNcomment:PCMʱ��,��λms(ֻ������������Ⱥ���󳤶�)*/
#define HME_PCMLEN_10MS                  10
#define HME_PCMLEN_20MS                  20
#define HME_PCMLEN_30MS                  30
/* BEGIN: Added by czg, 2010/9/28 */
#define HME_PCMLEN_40MS                  40
#define HME_PCMLEN_50MS                  50
#define HME_PCMLEN_60MS                  60
/* END:   Added by czg, 2010/9/28 */
#define HME_PCMLEN_MAX_240MS             240

/*common length of frame, that is the length of PCM data, unit by byte*/ /*CNcomment:����֡������ÿ֡PCM���ݳ���,��λ�ֽ�,(������*ʱ��*����/8bit)*/
#define HME_DATALEN_8K16BMAX             3840                        /*8K, 16bit, one frame size is 240ms in packet*/ /*CNcomment:8K��16λ���������ʱ��Ϊ240msʱÿ֡�ֽ���*/
#define HME_DATALEN_8K16BOF10MS          160                         /*8K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:8K��16λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/
#define HME_DATALEN_8K16BOF5MS           80                          /*8K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:8K��16λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/
#define HME_DATALEN_8K8BOF10MS           80                          /*8K, 8bit, one frame size is 10ms in packet*/ /*CNcomment:8K��8λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/

#define HME_DATALEN_16K16BMAX            7680                        /*16K, 16bit, one frame size is 240ms in packet*/ /*CNcomment:16K��16λ���������ʱ��Ϊ240msʱÿ֡�ֽ���*/
#define HME_DATALEN_16K16BOF10MS         320                         /*16K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:16K��16λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/
#define HME_DATALEN_16K16BOF5MS          160                         /*16K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:16K��16λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/
#define HME_DATALEN_16K8BOF10MS          160                         /*16K, 8bit, one frame size is 10ms in packet*/ /*CNcomment:16K��8λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/

#define HME_DATALEN_48K16BOF10MS         960                         /*48K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:48K��16λ���������ʱ��Ϊ10msʱÿ֡�ֽ���*/
#define HME_MAX_BYTE_PER_FRAME           HME_DATALEN_8K16BOF10MS

/*common length of frame, that is the length of PCM data, unit by PcmSamples*/ /*CNcomment:����֡������ÿ֡PCM���ݳ���,��λ������,(������*ʱ��*����)*/
#define HME_PCMLEN_8K16BMAX              (HME_DATALEN_8K16BMAX/2)    /*8K, 16bit, the PcmSamples of one frame in packet which is 240ms*/ /*CNcomment:8K��16λ���������ʱ��Ϊ240msʱÿ֡������*/
#define HME_PCMLEN_8K16BOF10MS           (HME_DATALEN_8K16BOF10MS/2) /*8K, 16bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:8K��16λ���������ʱ��Ϊ10msʱÿ֡������*/
#define HME_PCMLEN_8K16BOF1MS             8                          /*8K, 16bit, the PcmSamples of one frame in packet which is 1ms*/ /*CNcomment:8K��16λ���������ʱ��Ϊ1msʱÿ֡������*/
#define HME_PCMLEN_8K8BOF10MS            (HME_DATALEN_8K8BOF10MS/2)  /*8K, 8bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:8K��8λ���������ʱ��Ϊ10msʱÿ֡������*/

#define HME_PCMLEN_16K16BMAX              (HME_DATALEN_16K16BMAX/2)    /*16K, 16bit, the PcmSamples of one frame in packet which is 240ms*/ /*CNcomment:16K��16λ���������ʱ��Ϊ240msʱÿ֡������*/
#define HME_PCMLEN_16K16BOF10MS           (HME_DATALEN_16K16BOF10MS/2) /*16K, 16bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:16K��16λ���������ʱ��Ϊ10msʱÿ֡������*/
#define HME_PCMLEN_16K16BOF1MS             16                          /*16K, 16bit, the PcmSamples of one frame in packet which is 1ms*/ /*CNcomment:16K��16λ���������ʱ��Ϊ1msʱÿ֡������*/
#define HME_PCMLEN_16K8BOF10MS            (HME_DATALEN_16K8BOF10MS/2)  /*16K, 8bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:16K��8λ���������ʱ��Ϊ10msʱÿ֡������*/


#define HME_PCMLEN_48K16BOF10MS          (HME_DATALEN_48K16BOF10MS/2)  /*48K, 16bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:48K��16λ���������ʱ��Ϊ10msʱÿ֡������*/

/* BEGIN: Added by wangjuan, 2010/9/27   PN:A9_CODE*/
#define HME_MAX_PCM_DATA_LEN             HME_PCMLEN_48K16BOF10MS       /*the length of the biggest PCM buf*/ /*CNcomment:����PCM buf�ĳ���*/  
#define HME_MAX_DATA_LEN                 HME_DATALEN_48K16BOF10MS
/* END:   Added by wangjuan, 2010/9/27 */

/* BEGIN: Added by czg, 2010/10/11   PN:A9_Code*/
#define HME_NULL_BYTE   0xFF
#define HME_NULL_WORD   0xFFFF
#define HME_NULL_LWORD  0xFFFFFFFF
/* END:   Added by czg, 2010/10/11 */

#define HME_PACKET_DATA_MAX_LEN 2000       /*the largest length of packet*/ /*CNcomment:���ݰ���󳤶�*/
#define SDES_ITEM_LENGTH 256               /*the length of SDES*/ /*CNcomment:SDES��ĳ���*/
#define HME_MAX_APP_DATA_SIZE 1000         /*the largest length of APP-packet*/ /*CNcomment:APP��������ݳ���*/
#define HME_MAX_APP_SUB_TYPE  31           /*the largest value of the sub-APP*/ /*CNcomment:APP�����͵����ֵ*/
/* BEGIN: Modified by wangjuan, 2011/1/22   PN:WJ_CODE_Resample*/
#define MAX_AUDIO_DEV_COUNT 16             /*the largest number of Audio device*/ /*CNcomment:������Ƶ�豸��*/
/* END:   Modified by wangjuan, 2011/1/22 */

/* BEGIN: Added by zhangcheng, 2011/2/26   PN:msg trace set*/
#define  HME_MAX_USER_MSG_TRACE_PATH   64  /*the largest length of message trace path in User space*/ /*CNcomment:�û�̬��Ϣ����·����󳤶�*/
/* END:   Added by zhangcheng, 2011/2/26 */


/* BEGIN: Added by czg, 2010/10/11 */

/* BEGIN: Modified by wangjuan, 2011/1/22   PN:WJ_CODE_Resample*/
/*the type of coder and decoder*/ /*CNcomment:��������Ͷ���*/
typedef enum 
{
    CODER_DECODER_G711A  = 0,   /*G.711A*/
    CODER_DECODER_G711MU = 1,   /*G.711Mu*/
    CODER_DECODER_G722 = 2,     /*G.722*/
    CODER_DECODER_BUTT          /*invalid*/
}CODER_DECODER;
/* END:   Modified by wangjuan, 2011/1/22 */


/* END:   Added by czg, 2010/10/11 */

/*the relationship of time and bitpersample*/ /*CNcomment:ʱ�����ֽ���ת����ʽ����*/
#define TIME2LEN(rate, time, bitpersample) ((rate/1000)*time*(bitpersample/8))
#define LEN2TIME(len, rate, bitpersample)  (len/((rate/1000)*(bitpersample/8)))

/*describe PCM data*/ /*CNcomment:PCM��������*/
typedef struct _HME_PCM_STRU
{
   int8     *pszBuffer;             /*the address of PCM data bufffer*/ /*CNcomment:PCM���ݻ����ַ*/
   int32    iBytes;                 /*the length of PCM data, unit by byte*/ /*CNcomment:PCM���ݳ��ȣ��ֽ�Ϊ��λ*/
   int32    iFrequency;             /*samplerate, unit by HZ*/ /*CNcomment:������HZΪ��λ*/
   int32    iBitPerSample;          /*the precision of persample*/ /*CNcomment:ÿ������ľ���*/
   int32    iChannels;              /*PCM channel*/ /*CNcomment:ͨ����*/
   uint32    uiCurTimeStamp;        /*the PTS of frame packet*/ /*CNcomment:�����ݰ���ʱ���*/
}HME_PCM_STRU;

typedef struct _AUDIO_DEV_FRAME_INFO_S
{
    void     *pdata;                /*the address of PCM data bufffer*/ /*CNcomment:PCM���ݻ����ַ*/
    int32     iDataLen;             /*the length of PCM data, unit by byte*/ /*CNcomment:PCM���ݳ��ȣ��ֽ�Ϊ��λ*/
    int32     iSampleRate;          /*samplerate, unit by HZ*/ /*CNcomment:������HZΪ��λ*/
    int32     iBitPerSample;        /*the precision of persample*/ /*CNcomment:ÿ������ľ���*/
    int32     iChannels;            /*PCM channel, 1:mono 2:stereo*/ /*CNcomment:������1�������� 2������������������֧������������*/
    int32     iTimeStamp;       	/*the time stamp, unit by ms*/ /*CNcomment:����ͨ����RTP��ʱ���ת��Ϊ���뵥λ���ɣ�����ͨ����AI�ɼ����ʱ���������*/

}AUDIO_DEV_FRAME_INFO_S;



/* BEGIN: Added by wangjuan, 2010/11/24   PN:interface change*/
/*the system parameter of Audio device*/ /*CNcomment:��Ƶ�豸ϵͳ����*/
typedef struct _HME_AUDDEV_FUN_STRU
{   
    /* audio dev ai */    
    void*  AiDev;                   
    /* dev handle */    
    int32 (*Ai_SetDevAttr)(void*  AiDev,  int32 iSampleRate,int32 iBitPerSample,int32 iChannels);    
    int32 (*Ai_GetFrameProc)(void*  AiDev, AUDIO_DEV_FRAME_INFO_S * pstAiFrame);   
    /* audio dev ao */    
    void*  AoDev;                  
    /* dev handle */    
    int32 (*Ao_SetDevAttr)(void*  AoDev,  int32 iSampleRate,int32 iBitPerSample,int32 iChannels);  
    int32 (*Ao_PutFrameProc)(void*  AoDev, const AUDIO_DEV_FRAME_INFO_S * pstAoFrame);
} HME_AUDDEV_FUN_S;
/* END:   Added by wangjuan, 2010/11/24 */

/* BEGIN: Added by czg, 2010/10/18   PN:A9_CODE*/
/*the event type of conference model*/ /*CNcomment:����ģ���¼�����ö��ֵ*/
enum ENUM_CONF_EVENT_TYPE
{
    E_CHN_LOCAL_PLAY_END = 0,   /*the event of play end in local channel*/ /*CNcomment:ͨ�����˲��Ž����¼�*/
    E_CHN_REMOTE_PLAY_END,      /*the event of play end in remote channel*/ /*CNcomment:ͨ��Զ�˲��Ž����¼�*/    
    E_CONF_EVENT_BUTT           /*invalid*/ /*CNcomment:��Ч����*/
};

/*the event type of dtmf model*/ /*CNcomment:dtmfģ���¼�����ö��ֵ*/
enum ENUM_DTMF_EVENT_TYPE
{
    E_CHN_UP_DTMF = 0,    /*receive event int channel up*/ /*CNcomment:ͨ�������պ��¼�*/
    E_CHN_DOWN_DTMF,      /*receive event int channel down*/ /*CNcomment:ͨ�������պ��¼�*/    
    E_DTMF_EVENT_BUTT,    /*invalid*/ /*CNcomment:��Ч����*/
};

/*the parameter of conf model using when report event*/ /*CNcomment:�¼��ϱ�ʱconfģ����Ҫ�ϱ��Ľṹ�����*/
typedef struct CONF_PLAY_END_EVENT_STRU
{
    uint16 usChnId;         /*channel ID*/ /*CNcomment:ͨ��ID*/
    uint16 usConfId;        /*conference ID, reserved*/ /*CNcomment:����ID��Ŀǰ����*/
    int32 iEventType;       /*event type*/ /*CNcomment:�¼�����, enum ENUM_CONF_EVENT_TYPE*/
    uint32 iEventValue;     /*event value, reserved*/ /*CNcomment:�¼�ֵ��Ŀǰ����*/
}CONF_PLAY_END_EVENT_S;

/*the parameter of conf model using when report event*/ /*CNcomment:�¼��ϱ�ʱconfģ����Ҫ�ϱ��Ľṹ�����*/
typedef struct DTMF_EVENT_STRU
{
    uint16 usChnId;         /*channel ID*/ /*CNcomment:ͨ��ID*/
    uint16 usConfId;        /*conference ID, reserved*/ /*CNcomment:����ID��Ŀǰ����*/
    int32 iEventType;       /*event type*/ /*CNcomment:�¼�����, enum ENUM_CONF_EVENT_TYPE*/
    uint32 iEventValue;     /*event value*/ /*CNcomment:�¼�ֵ*/
}DTMF_EVENT_S;

// net statistics*/
typedef struct _HME_RTCP_STAT_STRU
{
    uint32 uiTotalLostPacket;               /*data loss packet statistics*/
    uint32 uiLossFraction;                  /*loss packet Fraction(%)*/
    uint32 uiJitter;                        /*average jitter(%)*/
    uint32 uiDelay;                         /*average delay(%)*/
} HME_RTCP_STAT_STRU; 

/* RTCP statistics */
typedef struct _HME_RTCP_STATINFOR_STRU
{
    uint32 uiSendPacketNum;                 /*send packet total number*/
    uint32 uiSendBytes;                     /*send btye number*/
    uint32 uiRecPacketNum;
    uint32 uiRecBytes;
    HME_RTCP_STAT_STRU stSendInfo;          /*send statistics*/
    HME_RTCP_STAT_STRU stRecvInfo;          /*receive statistics*/
} HME_RTCP_STATINFOR_STRU;

typedef void (*HME_LOCAL_EventProc)(void *pEventInfo);
/* END:   Added by czg, 2010/10/18 */

/* BEGIN: Added by czg, 2010/10/13   PN:A9_Code*/
typedef void (*HME_pDataCapProc)(uint8 *pcDataBuf, uint16 usDataLen, void *pDataCapParas);
/* END:   Added by czg, 2010/10/13 */

/* BEGIN: Added by zhangcheng, 2011/2/26   PN:msg trace set*/
typedef int32 (*USER_MSG_EVT_DEEL_FUN)(uint32 uiChnId, uint32 uiFlag, uint8  *aucUsersPath);
/* END:   Added by zhangcheng, 2011/2/26 */
/* BEGIN: Added by zhangcheng, 2011/2/26   PN:chn loop code*/
typedef int32 (*SET_CHN_LOOP_DEEL_FUN)(uint32 uiChnId, uint32 uiFlag);
/* END:   Added by zhangcheng, 2011/2/26 */


#endif
        
/**************************************************************************************************
            End of File  
**************************************************************************************************/
