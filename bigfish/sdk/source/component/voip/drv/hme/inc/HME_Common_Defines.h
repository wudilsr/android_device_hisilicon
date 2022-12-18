
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


#define HME_VERSTR_MINLEN               128           /*the minimum length of version string*/ /*CNcomment:版本查询字符串最小长度*/

/* BEGIN: Modified by wangjuan, 2011/2/9   PN:WJ_CODE_Resample*/
#define HME_MAX_CHANNEL_COUNT           16            /*maximum support channel count definition*/ /*CNcomment:最大支持通道数定义*/
#define HME_MAX_CONF_COUNT              16            /*maximum conference count*/ /*CNcomment:最大的会场个数*/
/* END:   Modified by wangjuan, 2011/2/9 */

/*audio device volume adjust range*/ /*CNcomment:音频设备音量调整范围*/
#define HME_AUDEV_VOLUME_MAX            65535         /*maximum value of device operation*/ /*CNcomment:设备操作的最大值*/
#define HME_ENGINE_VOLUME_MAX           100           /*API interface operation range*/ /*CNcomment:API接口的操作范围*/

/* BEGIN: Added by czg, 2010/11/5   PN:czg_st_1104_02*/
#define MAX_IP_ADDR_LEN  16
/* END:   Added by czg, 2010/11/5 */

/*returned value section definition according to component*/ /*CNcomment:返回值按组件分段定义*/

#define HME_ERR_BASE                     0x0000

#define HME_ERR_API                     (HME_ERR_BASE)                /*extern API layer*/ /*CNcomment:对外API层*/
#define HME_ERR_TOPLEVEL                (HME_ERR_BASE + 0x1000)       /*business realization layer*/ /*CNcomment:业务实现层*/
#define HME_AUDIO                       (HME_ERR_BASE + 0x2000)       /*audio process module*/ /*CNcomment:音频处理模块（包括音频设备和本地音频处理）*/
#define HME_CONFER                      (HME_ERR_BASE + 0x3000)       /*conference module*/ /*CNcomment:会议模块*/
#define HME_STREAM                      (HME_ERR_BASE + 0x4000)       /*stream module*/ /*CNcomment:流模块*/
#define HME_NET                         (HME_ERR_BASE + 0x5000)       /*net process*/ /*CNcomment:网络处理*/
#define HME_CODEC_MGR                   (HME_ERR_BASE + 0x6000)       /*error code base address of codec management module*/ /*CNcomment:CODEC管理模块的错误码基址*/
#define HME_DTMF                        (HME_ERR_BASE + 0x7000)       /*dtmf module*/ /*CNcomment:dtmf模块*/
#define HME_OS_ERR_BASE                 (HME_ERR_BASE + 0xf000)       /*system function error*/ /*CNcomment:系统函数出错，打印日志时如果要加上错误码*/

#define HME_SSM                         (HME_ERR_BASE + 0x7000)       /*SSM*/


/*define return value*/ /*CNcomment:HME VE API 返回值枚举定义，需定义到对外头文件*/
typedef enum _HME_ERRNO_ENUM
{
    HME_ERR_FAILURE                     = -1,
    HME_ERR_OK                          = 0,
    HME_ERR_ERROR                       = 1
} HME_LIB_RESULT;

/*define error number*/ /*CNcomment:相关错误码定义*/
#define HME_ERR_UNKNOWN                     (HME_ERR_API + 1)  /*unknow error*/ /*CNcomment:未知错误*/
#define HME_ERR_INVALPARAM                  (HME_ERR_API + 2)  /*invalid parameter*/ /*CNcomment:无效的参数*/
#define HME_ERR_INVALCHANNELID              (HME_ERR_API + 3)  /*invalid channel ID*/ /*CNcomment:无效通道号*/
#define HME_ERR_INVALNETPORT                (HME_ERR_API + 4)  /*invalid IP or port*/ /*CNcomment:无效IP地址或端口号*/
#define HME_ERR_UNINITIALIZE                (HME_ERR_API + 5)  /*not initialize libarary*/ /*CNcomment:库没有初时化*/
#define HME_ERR_NOT_IMPLEMENTED             (HME_ERR_API + 6)  /*contion not meet*/ /*CNcomment:先决条件不满足*/
#define HME_ERR_NOT_SUPPORT_BY_VERSION      (HME_ERR_API + 7)  /*not support temporarily*/ /*CNcomment:功能暂不支持*/
#define HME_ERR_LOG_INIT                    (HME_ERR_API + 8)  /*log error*/ /*CNcomment:日志启动出错*/
#define HME_ERR_STARTUP_FAIL                (HME_ERR_API + 9)  /*start up fail*/
#define HME_ERR_DELETE_FAIL                 (HME_ERR_API + 10) /*del up fail*/

/* BEGIN: Added by czg, 2010/10/8 */
#define HME_AGC_DISABLE  0      /*AGC disable*/ /*CNcomment:功能关闭*/
#define HME_AGC_ENABLE   1      /*AGC enable*/ /*CNcomment:功能开启*/
#define HME_EC_DISABLE   0      /*EC disable*/ /*CNcomment:功能关闭*/
#define HME_EC_ENABLE    1      /*EC enable*/ /*CNcomment:功能开启*/
#define HME_ANR_DISABLE  0      /*ANR disable*/ /*CNcomment:功能关闭*/
#define HME_ANR_ENABLE   1      /*ANR enable*/ /*CNcomment:功能开启*/
/* END:   Added by czg, 2010/10/8 */

#define HME_CODECNAME_MAX_LEN 30

#if 0
/*soft gain*/ /*CNcomment:软增益定标值*/
#define HME_SOFT_GAIN_BASE_VALUE     10
#else
#define HME_SOFT_GAIN_BASE_VALUE     0
#endif

/*define samplerate, unit by HZ*/ /*CNcomment:采样率定义,单位HZ*/
#define HME_SAMPLERATE_8000              8000
#define HME_SAMPLERATE_11025             11025
#define HME_SAMPLERATE_16000             16000
#define HME_SAMPLERATE_22050             22050
#define HME_SAMPLERATE_24000             24000
#define HME_SAMPLERATE_32000             32000
#define HME_SAMPLERATE_44100             44100
#define HME_SAMPLERATE_48000             48000

/*define precision of samplerate*/ /*CNcomment:采样精度定义*/
#define HME_16B_PER_SAMPLE               16
#define HME_8B_PER_SAMPLE                8

/*the duration of PCM, unit by ms*/ /*CNcomment:PCM时长,单位ms(只定义基本处理长度和最大长度)*/
#define HME_PCMLEN_10MS                  10
#define HME_PCMLEN_20MS                  20
#define HME_PCMLEN_30MS                  30
/* BEGIN: Added by czg, 2010/9/28 */
#define HME_PCMLEN_40MS                  40
#define HME_PCMLEN_50MS                  50
#define HME_PCMLEN_60MS                  60
/* END:   Added by czg, 2010/9/28 */
#define HME_PCMLEN_MAX_240MS             240

/*common length of frame, that is the length of PCM data, unit by byte*/ /*CNcomment:常用帧长，即每帧PCM数据长度,单位字节,(采样率*时长*精度/8bit)*/
#define HME_DATALEN_8K16BMAX             3840                        /*8K, 16bit, one frame size is 240ms in packet*/ /*CNcomment:8K、16位采样，打包时长为240ms时每帧字节数*/
#define HME_DATALEN_8K16BOF10MS          160                         /*8K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:8K、16位采样，打包时长为10ms时每帧字节数*/
#define HME_DATALEN_8K16BOF5MS           80                          /*8K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:8K、16位采样，打包时长为10ms时每帧字节数*/
#define HME_DATALEN_8K8BOF10MS           80                          /*8K, 8bit, one frame size is 10ms in packet*/ /*CNcomment:8K、8位采样，打包时长为10ms时每帧字节数*/

#define HME_DATALEN_16K16BMAX            7680                        /*16K, 16bit, one frame size is 240ms in packet*/ /*CNcomment:16K、16位采样，打包时长为240ms时每帧字节数*/
#define HME_DATALEN_16K16BOF10MS         320                         /*16K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:16K、16位采样，打包时长为10ms时每帧字节数*/
#define HME_DATALEN_16K16BOF5MS          160                         /*16K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:16K、16位采样，打包时长为10ms时每帧字节数*/
#define HME_DATALEN_16K8BOF10MS          160                         /*16K, 8bit, one frame size is 10ms in packet*/ /*CNcomment:16K、8位采样，打包时长为10ms时每帧字节数*/

#define HME_DATALEN_48K16BOF10MS         960                         /*48K, 16bit, one frame size is 10ms in packet*/ /*CNcomment:48K、16位采样，打包时长为10ms时每帧字节数*/
#define HME_MAX_BYTE_PER_FRAME           HME_DATALEN_8K16BOF10MS

/*common length of frame, that is the length of PCM data, unit by PcmSamples*/ /*CNcomment:常用帧长，即每帧PCM数据长度,单位样点数,(采样率*时长*精度)*/
#define HME_PCMLEN_8K16BMAX              (HME_DATALEN_8K16BMAX/2)    /*8K, 16bit, the PcmSamples of one frame in packet which is 240ms*/ /*CNcomment:8K、16位采样，打包时长为240ms时每帧样点数*/
#define HME_PCMLEN_8K16BOF10MS           (HME_DATALEN_8K16BOF10MS/2) /*8K, 16bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:8K、16位采样，打包时长为10ms时每帧样点数*/
#define HME_PCMLEN_8K16BOF1MS             8                          /*8K, 16bit, the PcmSamples of one frame in packet which is 1ms*/ /*CNcomment:8K、16位采样，打包时长为1ms时每帧样点数*/
#define HME_PCMLEN_8K8BOF10MS            (HME_DATALEN_8K8BOF10MS/2)  /*8K, 8bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:8K、8位采样，打包时长为10ms时每帧样点数*/

#define HME_PCMLEN_16K16BMAX              (HME_DATALEN_16K16BMAX/2)    /*16K, 16bit, the PcmSamples of one frame in packet which is 240ms*/ /*CNcomment:16K、16位采样，打包时长为240ms时每帧样点数*/
#define HME_PCMLEN_16K16BOF10MS           (HME_DATALEN_16K16BOF10MS/2) /*16K, 16bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:16K、16位采样，打包时长为10ms时每帧样点数*/
#define HME_PCMLEN_16K16BOF1MS             16                          /*16K, 16bit, the PcmSamples of one frame in packet which is 1ms*/ /*CNcomment:16K、16位采样，打包时长为1ms时每帧样点数*/
#define HME_PCMLEN_16K8BOF10MS            (HME_DATALEN_16K8BOF10MS/2)  /*16K, 8bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:16K、8位采样，打包时长为10ms时每帧样点数*/


#define HME_PCMLEN_48K16BOF10MS          (HME_DATALEN_48K16BOF10MS/2)  /*48K, 16bit, the PcmSamples of one frame in packet which is 10ms*/ /*CNcomment:48K、16位采样，打包时长为10ms时每帧样点数*/

/* BEGIN: Added by wangjuan, 2010/9/27   PN:A9_CODE*/
#define HME_MAX_PCM_DATA_LEN             HME_PCMLEN_48K16BOF10MS       /*the length of the biggest PCM buf*/ /*CNcomment:最大的PCM buf的长度*/  
#define HME_MAX_DATA_LEN                 HME_DATALEN_48K16BOF10MS
/* END:   Added by wangjuan, 2010/9/27 */

/* BEGIN: Added by czg, 2010/10/11   PN:A9_Code*/
#define HME_NULL_BYTE   0xFF
#define HME_NULL_WORD   0xFFFF
#define HME_NULL_LWORD  0xFFFFFFFF
/* END:   Added by czg, 2010/10/11 */

#define HME_PACKET_DATA_MAX_LEN 2000       /*the largest length of packet*/ /*CNcomment:数据包最大长度*/
#define SDES_ITEM_LENGTH 256               /*the length of SDES*/ /*CNcomment:SDES项的长度*/
#define HME_MAX_APP_DATA_SIZE 1000         /*the largest length of APP-packet*/ /*CNcomment:APP包最大数据长度*/
#define HME_MAX_APP_SUB_TYPE  31           /*the largest value of the sub-APP*/ /*CNcomment:APP子类型的最大值*/
/* BEGIN: Modified by wangjuan, 2011/1/22   PN:WJ_CODE_Resample*/
#define MAX_AUDIO_DEV_COUNT 16             /*the largest number of Audio device*/ /*CNcomment:最大的音频设备数*/
/* END:   Modified by wangjuan, 2011/1/22 */

/* BEGIN: Added by zhangcheng, 2011/2/26   PN:msg trace set*/
#define  HME_MAX_USER_MSG_TRACE_PATH   64  /*the largest length of message trace path in User space*/ /*CNcomment:用户态消息跟踪路径最大长度*/
/* END:   Added by zhangcheng, 2011/2/26 */


/* BEGIN: Added by czg, 2010/10/11 */

/* BEGIN: Modified by wangjuan, 2011/1/22   PN:WJ_CODE_Resample*/
/*the type of coder and decoder*/ /*CNcomment:编解码类型定义*/
typedef enum 
{
    CODER_DECODER_G711A  = 0,   /*G.711A*/
    CODER_DECODER_G711MU = 1,   /*G.711Mu*/
    CODER_DECODER_G722 = 2,     /*G.722*/
    CODER_DECODER_BUTT          /*invalid*/
}CODER_DECODER;
/* END:   Modified by wangjuan, 2011/1/22 */


/* END:   Added by czg, 2010/10/11 */

/*the relationship of time and bitpersample*/ /*CNcomment:时长与字节数转换公式定义*/
#define TIME2LEN(rate, time, bitpersample) ((rate/1000)*time*(bitpersample/8))
#define LEN2TIME(len, rate, bitpersample)  (len/((rate/1000)*(bitpersample/8)))

/*describe PCM data*/ /*CNcomment:PCM数据描述*/
typedef struct _HME_PCM_STRU
{
   int8     *pszBuffer;             /*the address of PCM data bufffer*/ /*CNcomment:PCM数据缓存地址*/
   int32    iBytes;                 /*the length of PCM data, unit by byte*/ /*CNcomment:PCM数据长度，字节为单位*/
   int32    iFrequency;             /*samplerate, unit by HZ*/ /*CNcomment:采样率HZ为单位*/
   int32    iBitPerSample;          /*the precision of persample*/ /*CNcomment:每个样点的精度*/
   int32    iChannels;              /*PCM channel*/ /*CNcomment:通道数*/
   uint32    uiCurTimeStamp;        /*the PTS of frame packet*/ /*CNcomment:此数据包的时间戳*/
}HME_PCM_STRU;

typedef struct _AUDIO_DEV_FRAME_INFO_S
{
    void     *pdata;                /*the address of PCM data bufffer*/ /*CNcomment:PCM数据缓存地址*/
    int32     iDataLen;             /*the length of PCM data, unit by byte*/ /*CNcomment:PCM数据长度，字节为单位*/
    int32     iSampleRate;          /*samplerate, unit by HZ*/ /*CNcomment:采样率HZ为单位*/
    int32     iBitPerSample;        /*the precision of persample*/ /*CNcomment:每个样点的精度*/
    int32     iChannels;            /*PCM channel, 1:mono 2:stereo*/ /*CNcomment:声道，1：单声道 2：立体声。后续考虑支持立体声处理*/
    int32     iTimeStamp;       	/*the time stamp, unit by ms*/ /*CNcomment:下行通道：RTP的时间戳转换为毫秒单位即可，上行通道：AI采集会把时间戳带上来*/

}AUDIO_DEV_FRAME_INFO_S;



/* BEGIN: Added by wangjuan, 2010/11/24   PN:interface change*/
/*the system parameter of Audio device*/ /*CNcomment:音频设备系统参数*/
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
/*the event type of conference model*/ /*CNcomment:会议模块事件类型枚举值*/
enum ENUM_CONF_EVENT_TYPE
{
    E_CHN_LOCAL_PLAY_END = 0,   /*the event of play end in local channel*/ /*CNcomment:通道本端播放结束事件*/
    E_CHN_REMOTE_PLAY_END,      /*the event of play end in remote channel*/ /*CNcomment:通道远端播放结束事件*/    
    E_CONF_EVENT_BUTT           /*invalid*/ /*CNcomment:无效类型*/
};

/*the event type of dtmf model*/ /*CNcomment:dtmf模块事件类型枚举值*/
enum ENUM_DTMF_EVENT_TYPE
{
    E_CHN_UP_DTMF = 0,    /*receive event int channel up*/ /*CNcomment:通道上行收号事件*/
    E_CHN_DOWN_DTMF,      /*receive event int channel down*/ /*CNcomment:通道下行收号事件*/    
    E_DTMF_EVENT_BUTT,    /*invalid*/ /*CNcomment:无效类型*/
};

/*the parameter of conf model using when report event*/ /*CNcomment:事件上报时conf模块需要上报的结构体参数*/
typedef struct CONF_PLAY_END_EVENT_STRU
{
    uint16 usChnId;         /*channel ID*/ /*CNcomment:通道ID*/
    uint16 usConfId;        /*conference ID, reserved*/ /*CNcomment:会议ID，目前保留*/
    int32 iEventType;       /*event type*/ /*CNcomment:事件类型, enum ENUM_CONF_EVENT_TYPE*/
    uint32 iEventValue;     /*event value, reserved*/ /*CNcomment:事件值，目前保留*/
}CONF_PLAY_END_EVENT_S;

/*the parameter of conf model using when report event*/ /*CNcomment:事件上报时conf模块需要上报的结构体参数*/
typedef struct DTMF_EVENT_STRU
{
    uint16 usChnId;         /*channel ID*/ /*CNcomment:通道ID*/
    uint16 usConfId;        /*conference ID, reserved*/ /*CNcomment:会议ID，目前保留*/
    int32 iEventType;       /*event type*/ /*CNcomment:事件类型, enum ENUM_CONF_EVENT_TYPE*/
    uint32 iEventValue;     /*event value*/ /*CNcomment:事件值*/
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
