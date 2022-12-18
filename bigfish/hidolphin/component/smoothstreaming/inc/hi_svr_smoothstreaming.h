/**
 \file
 \brief Server smoothstreaming module. CNcomment:HiSmoothStreaming模块
 \author HiSilicon Technologies Co., Ltd.
 \date 2008-2018
 \version 1.0.0.1
 \author
 \date 2013-02-19
 */

#ifndef _HI_SVR_SMOOTHSTREAMING_H
#define _HI_SVR_SMOOTHSTREAMING_H

#include "hi_type.h"

/*************************** Structure Definition ****************************/
/** @{ */  /** <!-- [HiSmoothStreaming data structure] CNcomment:【HiSmoothStreaming数据结构】 */

/** smoothstreaming url max length*/
/** CNcomment:url最大长度 */
#define HI_SVR_SMOOTHSTREAMING_FORMAT_MAX_URL_LEN 1024

/** Invalid handle */
/** CNcomment:非法句柄 */
#define HI_SVR_SMOOTHSTREAMING_INVALID_HDL (0)

/** smoothstreaming language max length */
/** CNcomment:语言的最大长度*/
#define HI_SVR_SMOOTHSTREAMING_LANG_LEN    (4)


/** playing speed flag*/
/** CNcomment:播放速度标志 */
typedef enum hiSVR_SMOOTHSTREAMING_SPEED_E
{
    HI_SMOOTHSTREAMING_SPEED_NORMAL =              1024,
    HI_SMOOTHSTREAMING_SPEED_2X_FAST_FORWARD   =   2 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_4X_FAST_FORWARD   =   4 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_8X_FAST_FORWARD   =   8 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_16X_FAST_FORWARD  =   16 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_32X_FAST_FORWARD  =   32 * HI_SMOOTHSTREAMING_SPEED_NORMAL,

    HI_SMOOTHSTREAMING_SPEED_2X_FAST_BACKWARD  =   -2 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_4X_FAST_BACKWARD  =   -4 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_8X_FAST_BACKWARD  =   -8 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_16X_FAST_BACKWARD =   -16 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_32X_FAST_BACKWARD =   -32 * HI_SMOOTHSTREAMING_SPEED_NORMAL,
    HI_SMOOTHSTREAMING_SPEED_BUTT
} HI_SVR_SMOOTHSTREAMING_SPEED_E;

/** smoothstream attribute setting flag*/
/** CNcomment:播放器属性 */
typedef enum hiSVR_SMOOTHSTREAMING_ATTR_E
{
    HI_SVR_SMOOTHSTREAMING_ATTR_AVPLAYER_HDL = 0,       /**< obtain the avplayer handle, The parameter is the HI_HANDLE variable. */
                                                        /**< CNcomment:获取当前的AVPlay句柄，参数为HI_HANDLE变量 */
    HI_SVR_SMOOTHSTREAMING_ATTR_WINDOW_HDL,             /**< obtain the Window handle, The parameter is the HI_HANDLE variable. */
                                                        /**< CNcomment:获取当前的Window句柄，参数为HI_HANDLE变量 */
    HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING,           /**< Set or obtain the cache timing. The parameter is ::HI_SVR_SMOOTHSTREAMING_CACHE_TIMING_S. */
                                                        /**< CNcomment:设置媒体数据的缓冲时序，参数类型是:HI_SVR_SMOOTHSTREAMING_CACHE_TIMING_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING,           /**< Set or obtain the http attribute. The parameter is ::HI_SVR_SMOOTHSTREAMING_HTTP_ATTR_S. */
                                                        /**< CNcomment:设置http的属性，参数类型是:HI_SVR_SMOOTHSTREAMING_HTTP_ATTR_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_STREAM_ID,              /**< Set or obtain the stream ID. This attribute is applicable to multi-audio multi-video streams. The parameter is ::HI_SVR_PLAYER_STREAMID_S. */
                                                        /**< CNcomment:设置/获取流编号，该属性针对多音频、多视频流的情况，参数为::HI_SVR_PLAYER_STREAMID_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_PATH,               /**< Set the DRM path. The parameter is ::HI_SVR_SMOOTHSTREAMING_DRM_PATH_S. */
                                                        /**< CNcomment:设置DRM设备证书路径及许可证的本地保存路径，参数类型是:HI_SVR_SMOOTHSTREAMING_DRM_PATH_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_DOMAIN,             /**< reserved, currently no use*/
                                                        /**< CNcomment:扩展接口，获取DRM header的内容信息*/
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_CERTBUFF,           /**< reserved, currently no use.*/
                                                        /**< CNcomment:扩展接口，暂时未实现，预留用于从外部透传buffer形式的playready证书*/
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_INITIATOR,          /**< reserved, currently no use.*/
                                                        /**< CNcomment:扩展接口，暂时未实现，预留用于从外部透传DRM的初始化信息*/
    HI_SVR_SMOOTHSTREAMING_ATTR_USERDATA,               /**< reserved, currently no use.*/
                                                        /**< CNcomment:扩展接口，暂时未实现，预留用于从外部透传用户定义的信息，如媒体数据单独的URL等*/
    HI_SVR_SMOOTHSTREAMING_ATTR_BUTT
} HI_SVR_SMOOTHSTREAMING_ATTR_E;

/** media data cache timing*/
/** CNcomment:播放器属性 */
typedef struct hiSVR_SMOOTHSTREAMING_CACHE_TIMING_S
{
    HI_U32 u32DefBufferDelayMs;     /**< Default value(in ms) for the "BufferDelay" in the SSPK, which is used to judge if there is enough buffered media data to start playing. */
                                    /**< CNcomment: BufferDelay的默认值，BufferDelay用于控制媒体数据的缓冲，一旦已经缓冲的媒体数据的PTS超过最近播放的媒体数据的PTS+BufferDelay，则启动播放*/
    HI_U32 u32StepBufferDelayMs;    /**< step value for the "BufferDelay"*/
                                    /**< CNcomment: BufferDelay的步进值.如果播放的过程中出现缓冲数据不足，欠载的情况，播放器会自动以此步长增加BufferDelay，以加大缓冲门限，减少欠载的可能*/
    HI_U32 u32MaxBufferDelayMs;     /**< max value for the "BufferDelay"*/
                                    /**< CNcomment: BufferDelay的最大值，BufferDelay步进增加，但不能超过此最大值*/
    HI_U32 u32RebufferThresholdMs;  /**< Time value(in ms) for buffer underrun check*/
                                    /**< CNcomment: 用于判断欠载的门限值，如果已缓冲的媒体数据长度小于此门限值，则暂停播放，等待缓冲*/
} HI_SVR_SMOOTHSTREAMING_CACHE_TIMING_S;

/** http attribute settings*/
/** CNcomment:http相关属性 */
typedef struct hiSVR_SMOOTHSTREAMING_HTTP_ATTR_S
{
    HI_S32 s32HttpMaxRedirectCt;                /**< max count for http redirection, the default value is 10*/
    HI_S32 s32HttpResponseTimeout;              /**< timeout for http response, the default value is 20, in seconds*/
    HI_S32 s32HttpInitialReceiveTimeout;        /**< timeout for the first http receive, the default value is 30, in seconds*/
    HI_S32 s32HttpSubsequentReceiveTimeout;     /**< timeout for the subsequent(not the first one) http receive, the default is 6, in seconds*/
    HI_S32 s32HttpMaxReconnectAttemptCt;        /**< max count for http reconnect, the default is 1*/
} HI_SVR_SMOOTHSTREAMING_HTTP_ATTR_S;

/** DRM path for device certificate and license storage*/
/** CNcomment:DRM 设备证书路径，及本地许可证保存路径 */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_PATH_S
{
    HI_U8* pDrmCertPath;            /**< DRM certificate path*/
                                    /**< CNcomment:DRM设备证书的保存目录，只需目录名，不用指定文件名,应用必须保证传入的目录具有可读可写权限 */
    HI_U8* pDrmLicenseStoreFile;    /**< DRM license storage path*/
                                    /**< CNcomment:DRM媒体许可证的本地保存目录，需要包含文件名在内的完整路径，应用必须保证传入的路径具有可读可写权限*/
} HI_SVR_SMOOTHSTREAMING_DRM_PATH_S;

/** DRM string */
/** CNcomment:DRM接口专用的string数据结构 */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_STRING_S
{
    HI_U8  *pszString;      /**< name*/
    HI_U32  u32Length;      /**< data length*/
    HI_U8  *pu8Addr;        /**< data*/
} HI_SVR_SMOOTHSTREAMING_DRM_STRING_S;

/** DRM header */
/** CNcomment:DRM header接口专用的数据结构 */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_HEADER_S
{
    HI_U32  u32Length;      /**< data length*/
    HI_U8  *pu8Addr;        /**< data*/
} HI_SVR_SMOOTHSTREAMING_DRM_HEADER_S;

/** DRM certificate buffer*/
/** CNcomment:buffer形式的playready证书数据结构 */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_CERTBUFF_S
{
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stPriv;                /**< content of playready certificate file "priv.dat"*/
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stZgpriv;              /**< content of playready certificate file "zgpriv.dat"*/
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stBgroupcert;          /**< content of playready certificate file "bgroupcert.dat"*/
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stDevcerttemplate;     /**< content of playready certificate file "devcerttemplate.dat"*/
    HI_U8 *pszKeyfilePath;                                     /**< keyfile path*/
} HI_SVR_SMOOTHSTREAMING_DRM_CERTBUFF_S;

/** player initialation parameter*/
/** CNcomment:播放器初始化参数*/
typedef struct hiSVR_SMOOTHSTREAMING_PARAM_S
{
    HI_HANDLE hAVPlayer;            /**< AVPlay created externally. A window device and a sound device are bound to the AVPlay and the window size and the sound volume are set.
                                        The AVPlay handle can be transferred to the HiPlayer, which will use the AVPlay for playing.  */
                                    /**< CNcomment:外部已经创建了avplay并绑定了window,sound，并设置好window的大小位置，sound的音量，
                                        可以将avplay句柄传给HiPlayer，HiPlayer继续使用该avplay播放。 */
    HI_U32  x, y, w, h;             /**< Reserved attributes,not in use currently.Coordinate, width, and height of the video output window. This parameter is invalid in the case of hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL. *//**< CNcomment:保留属性，目前未使用。视频输出窗口坐标及宽高，hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL，该参数无效 */
    HI_U32  u32MixHeight;           /**< Reserved attribute,not in use currently.Audio output mix weight. The value ranges from 0 to 100. This parameter is invalid in the case of hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL. *//**< CNcomment:保留属性，目前未使用。音频输出混音权重0-100，hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL，该参数无效 */
    HI_U32   u32SndPort;            /**< Reserved attribute,not in use currently.Specified audio port number, 0: master audio, 1: slave audio  *//**< CNcomment:保留属性，目前未使用。指定音频端口号，0代表主音，1代表辅音*/
    HI_U32   u32Display;            /**< Reserved attribute,not in use currently.Display mode*//**< CNcomment:保留属性，目前未使用。视频显示模式，HD, SD*/
    HI_U32   u32VideoCacheSize;     /**< Reserved attribute,not in use currently.video data cache size, in byte, max value 32*1024*1024, minvalue 512*1024.*//**< CNcomment:保留属性，目前未使用。视频缓冲区大小，最新512*1024，最大32*1024*1024，单位字节。*/
    HI_U32   u32AudioCacheSize;     /**< Reserved attribute,not in use currently.audio data cache size, in byte, max value 4*1024*1024, minvalue 192*1024 *//**< CNcomment:保留属性，目前未使用。音频缓冲区大小，最新192*1024，最大4*1024*1024，单位字节。*/
} HI_SVR_SMOOTHSTREAMING_PARAM_S;

/** player mode*/
/** CNcomment:播放器播放模式*/
typedef enum hiSVR_SMOOTHSTREAMING_PLAYMODE_E
{
    HI_SVR_SMOOTHSTREAMING_PLAYMODE_NORMAL = 0,
    HI_SVR_SMOOTHSTREAMING_PLAYMODE_BUTT,
} HI_SVR_SMOOTHSTREAMING_PLAYMODE_E;

/** input media*/
/** CNcomment:输入的媒体*/
typedef struct hiSVR_SMOOTHSTREAMING_MEDIA_S
{
    HI_SVR_SMOOTHSTREAMING_PLAYMODE_E   ePlayMode;                 /**< player mode*/
    HI_CHAR  aszUrl[HI_SVR_SMOOTHSTREAMING_FORMAT_MAX_URL_LEN];    /**< input media url*/
} HI_SVR_SMOOTHSTREAMING_MEDIA_S;

/** player state*/
/** CNcomment:播放器状态*/
typedef enum hiSVR_SMOOTHSTREAMING_STATE_E
{
    HI_SVR_SMOOTHSTREAMING_STATE_INITIAL = 0,       /**< Initial state*/
                                                    /**< CNcomment:初始状态，在第一次成功调用HI_SMOOTHSTREAMING_Open之前播放器处于这个状态*/
    HI_SVR_SMOOTHSTREAMING_STATE_STOPPED,           /**< stopped state*/
                                                    /**< CNcomment:已成功打开一个媒体, 但已停止播放*/
    HI_SVR_SMOOTHSTREAMING_STATE_PLAYING,           /**< playing state*/
                                                    /**< CNcomment:正常播放状态，正在以正常速度播放媒体*/
    HI_SVR_SMOOTHSTREAMING_STATE_PAUSED,            /**< paused state*/
    HI_SVR_SMOOTHSTREAMING_STATE_FAST_FORWARD,      /**< fast forwrd state*/
                                                    /**< CNcomment:快进状态*/
    HI_SVR_SMOOTHSTREAMING_STATE_FAST_BACKWARD,     /**< fast backward state*/
                                                    /**< CNcomment:快退状态*/
    HI_SVR_SMOOTHSTREAMING_STATE_BUT
} HI_SVR_SMOOTHSTREAMING_STATE_E;

/** player running state*/
/** CNcomment:播放器运行信息*/
typedef struct hiSVR_SMOOTHSTREAMING_RUNNING_INFO_S
{
    HI_SVR_SMOOTHSTREAMING_STATE_E eStatus;     /**< player state*/
    HI_U64  u64CurTimeMs;                     /**< current playback time, in seconds*/
    HI_S32  s32Speed;                           /**< play speed*/
    HI_S32  s32CurBitrate;                      /**< current media bitrate*/
    HI_S32  s32CurVidStreamIdx;                 /**< current selected stream index*/
    HI_S32  s32CurAudStreamIdx;                 /**< current selected stream index*/
    HI_S32  s32CurSubStreamIdx;                 /**< current selected subtitle stream index*/
} HI_SVR_SMOOTHSTREAMING_RUNNING_INFO_S;

/** video track information*/
/** CNcomment:媒体的视频track信息，一般来说一个smooth streaming媒体只有一个视频流stream,
而视频流又可以包括多个内容相同，但码率不同的视频码流，一个这样的码流就是一个track*/
typedef struct hiSVR_SMOOTHSTREAMING_VID_TRACK_INFO_S
{
    HI_S32 s32StreamIdx;        /**< index for the stream which this video track belongs to*/
                                /**< CNcomment:此track从属于的stream的索引号，*/
    HI_S32 s32TrackIdx;         /**< the index of this video track*/
    HI_U32 u32Format;           /**< the encoding format of this track, For details about the value definition, see ::HI_UNF_VCODEC_TYPE_E.*/
                                /**< CNcomment:此视频track的编码格式，其取值见::HI_UNF_VCODEC_TYPE_E*/
    HI_S32 s32Bitrate;          /**< the bitrate of this video track*/
    HI_S32 s32Width;            /**< the width in pixels of this video track*/
    HI_S32 s32Height;           /**< the heigth in pixels of this video track*/
} HI_SVR_SMOOTHSTREAMING_VID_TRACK_INFO_S;

/** audio track information*/
/** CNcomment:媒体的音频track信息，一般来说一个smooth streaming媒体可以有多个音频流stream(多语言),
而一个音频流一般只包括一个音频track*/
typedef struct hiSVR_SMOOTHSTREAMING_AUD_TRACK_INFO_S
{
    HI_S32 s32StreamIdx;        /**< the stream index which this track belongs to*/
                                /**< CNcomment:此track从属于的stream的索引号，*/
    HI_S32 s32TrackIdx;         /**< the index of this track*/
    HI_U32 u32Format;           /**< the encoding format of this track, For details about the value definition, see ::HA_FORMAT_E.*/
                                /**< CNcomment:此音频track的编码格式，其取值见::HA_FORMAT_E*/
    HI_S32 s32Bitrate;          /**< the bitrate of this audio track*/
    HI_U32 u32SampleRate;       /**< the samplerate of this audio track*/
    HI_U32 u32BlockAlign;       /**< Number of bytes contained in a packet of this audio track*/
                                /**< CNcomment:packet所包含的字节数*/
    HI_U16 u16Channels;         /**< num of channels*/
    HI_U16 u16BitsPerSample;    /**< Number of bits occupied by each audio sampling point such as 8 bits or 16 bits.*/
    HI_CHAR aszLanguage[HI_SVR_SMOOTHSTREAMING_LANG_LEN];  /**< Audio stream language *//**< CNcomment:音频流语言 */
} HI_SVR_SMOOTHSTREAMING_AUD_TRACK_INFO_S;


/** Subtitle information */
/** CNcomment:字幕信息 */
typedef struct hiSVR_SMOOTHSTREAMING_SUB_INFO_S
{
    HI_S32  s32StreamIdx;                    /**< Stream index. *//**< CNcomment:流索引 */
    HI_S32  s32TrackIdx;                     /**< the index of this track*/
    HI_S32  s32Bitrate;                      /**< the bitrate of this subtitle track*/
    HI_U32  u32Format;                       /**< Subtitle format, For details about the value definition, see::HI_FORMAT_SUBTITLE_TYPE_E *//**< CNcomment:字幕格式，取值::HI_FORMAT_SUBTITLE_TYPE_E */
    HI_U32  u32CharSet;                      /**< Encoding type of the subtitle, the value range is as follows, default is 0.*/
    HI_CHAR aszLanguage[HI_SVR_SMOOTHSTREAMING_LANG_LEN]; /**< Subtitle language *//**< CNcomment:字幕语言 */
} HI_SVR_SMOOTHSTREAMING_SUB_TRACK_INFO_S;


/** media information*/
/** CNcomment:smooth streaming媒体信息*/
typedef struct hiSVR_SMOOTHSTREAMING_MEDIA_INFO_S
{
    HI_BOOL bIsLive;                /**< The flag represent if this media presentation is live.1 for live, 0 for none live*/
                                    /**< CNcomment:标志位，用于表示当前媒体是直播还是点播.1, 直播，0，点播*/
    HI_S64 s64Duration;             /**< duration of this media presentation, in ms*//**< CNcomment:文件播放的时间长度，单位ms*/
    HI_S64 s64StartTime;            /**< start time of this media presentation, in ms*//**< CNcomment:文件播放的开始时间，单位ms*/
    HI_U32 u32NumVidTracks;         /**< number of video tracks*/
    HI_U32 u32NumAudTracks;         /**< number of audio tracks*/
    HI_U32 u32NumSubTracks;         /**< number of subtitle tracks*/
    HI_U32 u32NumVidStreams;        /**< number of video streams*/
    HI_U32 u32NumAudStreams;        /**< number of audio streams*/
    HI_U32 u32NumSubStreams;        /**< number of subtitle streams*/
    HI_SVR_SMOOTHSTREAMING_VID_TRACK_INFO_S  * pastruVidTracks;     /**< information of video tracks*/
    HI_SVR_SMOOTHSTREAMING_AUD_TRACK_INFO_S  * pastruAudTracks;     /**< information of audio tracks*/
    HI_SVR_SMOOTHSTREAMING_SUB_TRACK_INFO_S  * pastruSubTracks;     /**< information of subtitle tracks*/
} HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S;

/** IDs of the AV and subtitle streams to be switched. */
/** CNcomment:要切换到的音视频、字幕流ID  */
typedef struct hiSVR_SMOOTHSTREAMING_STREAMID_S
{
    HI_U16 u16VidStreamId;   /**< Video stream ID. The value is  ranges from 0 to (u32NumVidStreams - 1), which u32NumVidStreams is defined in structure HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S. */
                           /**< CNcomment:视频流id，取值范围0-(u32NumVidStreams - 1)，u32NumVidStreams由HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S结构中定义*/
    HI_U16 u16AudStreamId;   /**< Audio stream ID. The value is  ranges from 0 to (u32NumAudStreams - 1), which u32NumAudStreams is defined in structure HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S. */
                           /**< CNcomment:音频流id，取值范围0-(u32NumAudStreams - 1)，u32NumAudStreams由HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S结构中定义*/
    HI_U16 u16SubStreamId;  /**< Subtitle ID.  The value is  ranges from 0 to (u32NumSubStreams - 1), which u32NumSubStreams is defined in structure HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S.*/
                           /**< CNcomment:字幕id，取值范围0-(u32NumSubStreams - 1)，u32NumSubStreams由HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S结构中定义*/
} HI_SVR_SMOOTHSTREAMING_STREAMID_S;


/** smooth streaming error type*/
/** CNcomment:smooth streaming错误类型*/
typedef enum hiSVR_SMOOTHSTREAMING_ERROR_TYPE_E
{
    HI_SVR_SMOOTHSTREAMING_ERROR_NOERROR = 0,       /**< no error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_UNKNOWN,           /**< unknown error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_NOMEM,             /**< not enough memory*/
    HI_SVR_SMOOTHSTREAMING_ERROR_MANIFEST,          /**< manifest error*/
                                                    /**< CNcomment:smooth steaming manifest解析失败*/
    HI_SVR_SMOOTHSTREAMING_ERROR_SOCKET,            /**< socket error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_HTTP,              /**< http error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_DATA,              /**< chunk data error*/
                                                    /**< CNcomment:此错误码表明媒体的分片数据有错*/
    HI_SVR_SMOOTHSTREAMING_ERROR_DRMINIT,           /**< drm playready initial error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_BUTT
} HI_SVR_SMOOTHSTREAMING_ERROR_TYPE_E;

/** smooth streaming error information*/
/** CNcomment:smooth streaming出错信息*/
typedef struct hiSVR_SMOOTHSTREAMING_ERROR_S
{
    HI_SVR_SMOOTHSTREAMING_ERROR_TYPE_E eErrorType;         /**< error type*/
    HI_S32 s32HttpErr;                                      /**< http error code*/
                                                            /**< CNcomment:http错误码*/
} HI_SVR_SMOOTHSTREAMING_ERROR_S;

/** event information*/
/** CNcomment:smooth streaming状态更新事件产生的原因*/
typedef enum hiSVR_SMOOTHSTREAMING_UPDATE_E
{
    HI_SVR_SMOOTHSTREAMING_UPDATE_UNKNOWN = 0,
    HI_SVR_SMOOTHSTREAMING_UPDATE_STATE_CHANGE,
    HI_SVR_SMOOTHSTREAMING_UPDATE_BUFFERREADY,              /**< This event means we already got enough cached media data, start to play*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_BUFFERLOW,                /**< There is an underrun event*/
                                                            /**< CNcomment:欠载事件*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_BITRATECHANGE,            /**< Bit rate changed*/
                                                            /**< CNcomment:媒体的比特率变化事件*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_EOF,                      /**< end of file event*/
                                                            /**< CNcomment:表示当前媒体已播放完毕*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_SOF,                      /**< start of file event*/
                                                            /**< CNcomment:表示当前媒体已快进到开头*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_BUTT
} HI_SVR_SMOOTHSTREAMING_UPDATE_E;

typedef struct hiSVR_SMOOTHSTREAMING_STATE_INFO_S
{
    HI_SVR_SMOOTHSTREAMING_UPDATE_E eEventType;
    HI_SVR_SMOOTHSTREAMING_STATE_E eState;
    HI_S32  s32Speed;                           /**< play speed*/
    HI_S32  s32CurBitrate;                      /**< current media bitrate*/
} HI_SVR_SMOOTHSTREAMING_STATE_INFO_S;

typedef enum hiSVR_SMOOTHSTREAMING_CMD_INFO_E
{
    HI_SVR_SMOOTHSTREAMING_CMD_PLAY = 0,
    HI_SVR_SMOOTHSTREAMING_CMD_FAST_FORWARD,
    HI_SVR_SMOOTHSTREAMING_CMD_FAST_BACKWARD,
    HI_SVR_SMOOTHSTREAMING_CMD_PAUSE,
    HI_SVR_SMOOTHSTREAMING_CMD_RESUME,
    HI_SVR_SMOOTHSTREAMING_CMD_SEEK,
    HI_SVR_SMOOTHSTREAMING_CMD_STOP,
    HI_SVR_SMOOTHSTREAMING_CMD_BUTT,
} HI_SVR_SMOOTHSTREAMING_CMD_INFO_E;

typedef struct hiSVR_SMOOTHSTREAMING_CMD_INFO_S
{
    HI_SVR_SMOOTHSTREAMING_CMD_INFO_E eCommand;
    HI_BOOL bFailed;
} HI_SVR_SMOOTHSTREAMING_CMD_INFO_S;

/** Version number definition */
/** CNcomment:版本号定义 */
typedef struct hiSVR_SMOOTHSTREAMING_VERSION_S
{
    HI_U8 u8VersionMajor;    /**< Major version accessor element */
    HI_U8 u8VersionMinor;    /**< Minor version accessor element */
    HI_U8 u8Revision;        /**< Revision version accessor element */
    HI_U8 u8Step;            /**< Step version accessor element */
} HI_SVR_SMOOTHSTREAMING_VERSION_S;

/** Command of the invoking */
/** CNcomment:invoke操作命令 */
typedef enum hiSVR_SMOOTHSTREAMING_INVOKE_ID_E
{
    HI_SVR_SMOOTHSTREAMING_INVOKE_PRE_CLOSE_FILE = 0x0, /**< the command of the file to be closed, no parameter*//**< CNcomment:预关闭文件，无参数 */
    HI_SVR_SMOOTHSTREAMING_INVOKE_BUTT
} hiSVR_SMOOTHSTREAMING_INVOKE_ID_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** @{ */  /** <!-- [HiSmoothStreaming] CNcomment:【HiSmoothStreaming API 函数】 */

/**
\brief error event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistErrCb interface can be called to register the callback function. CNcomment:出错事件回调函数，调用::HI_SVR_SMOOTHSTREAMING_RegistErrCb接口注册该回调函数
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pstruErr error event parameter. CNcomment: 出错事件参数

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_ERROR_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ERROR_S *pstruErr);


/**
\brief mediaready event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistMediaReadyCb interface can be called to register the callback function. CNcomment:媒体准备好事件回调函数，调用::HI_SVR_SMOOTHSTREAMING_RegistMediaReadyCb接口注册该回调函数
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pstruMediaInfo error event parameter. CNcomment: 媒体准备好事件参数

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S *pstruMediaInfo);

/**
\brief state update event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistStateEventCb interface can be called to register the callback function. CNcomment:播放器状态更新事件回调函数，调用::HI_SVR_SMOOTHSTREAMING_RegistStateEventCb接口注册该回调函数
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pStruEvent error event parameter. CNcomment: 播放器状态更新事件参数

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_STATE_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_STATE_INFO_S* pStruEvent);

/**
\brief command done event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistCmdCb interface can be called to register the callback function. CNcomment:播放命令执行完事件回调函数，调用::HI_SVR_SMOOTHSTREAMING_RegistCmdCb接口注册该回调函数
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pStruEvent error event parameter. CNcomment: 播放命令执行完事件参数

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_CMD_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_CMD_INFO_S* pStruEvent);

/**
\brief subtitle text data call back function. CNcomment:字幕数据回调函数:HI_SVR_SMOOTHSTREAMING_RegistSubCb接口注册该回调函数
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pData subtitle data. CNcomment: 字幕数据
\param[in] u32DataLen subtitle data len. CNcomment: 字幕数据长度
\param[in] isFinal is it the end of subtitle file. CNcomment: 字幕文件是否结束标志
\param[in] s64PtsAjustTimeMs pts adjust value. CNcomment: pts调整值
\param[in] u32UserData user data. CNcomment: 客户数据

\retval ::HI_SUCCESS CNcomment:处理成功
\retval ::HI_FAILURE CNcomment:字幕数据处理失败

\see \n
None.
*/

typedef HI_S32 (*HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN)(HI_HANDLE hPlayer, HI_U8* pData, HI_U32 u32DataLen, HI_BOOL isFinal,HI_S64 s64PtsAjustTimeMs,HI_U32 u32UserData);


#ifdef __cplusplus
extern "C" {
#endif

/**
\brief Get version of HiSmoothStream Player. CNcomment:取得组件版本号
\attention \n
\param[out] pstruVersion version of HiSmoothStreaming lib. CNcomment:取得的组件版本号

\retval ::HI_SUCCESS CNcomment:取得版本成功
\retval ::HI_FAILURE CNcomment:操作非法

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetVersion(HI_SVR_SMOOTHSTREAMING_VERSION_S* pstruVersion);

/**
\brief Initialize the player. CNcomment:初始化Player
\attention \n
The HI_S32 HI_SMOOTHSTREAMING_Init interface can be called to return a success message after the initialization is successful. Multiple processes are not supported
. This interface must be called prior to other interfaces.
CNcomment:初始化成功后再调用该接口返回成功，不支持多进程，调用其它接口前必须先调用该接口
\param None. CNcomment:无

\retval ::HI_SUCCESS The initialization is successful. CNcomment:初始化成功
\retval ::HI_FAILURE The initialization fails. CNcomment:初始化失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Init(HI_VOID);

/**
\brief Deinitialize the player module by calling the HI_S32 HI_SMOOTHSTREAMING_Deinit interface. The player module is not used any more. CNcomment:去初始化player模块，不再使用player模块，调用该接口去初始化player模块
\attention \n
The ::HI_SMOOTHSTREAMING_Destroy interface must be called to release the created player first. Otherwise, a failure is returned. The Deinit interface does not release the player resource. \n
This interface can be called to return a success message after the deinitialization is successful.
CNcomment:必须先调用::HI_SMOOTHSTREAMING_Destroy接口释放掉创建的播放器，再调用该接口，否则会返回失败，Deinit不负责释放\n
播放器资源。去初始化成功后再调用该接口返回成功
\param None. CNcomment:无

\retval ::HI_SUCCESS The deinitialization is successful. CNcomment:去初始化成功
\retval ::HI_FAILURE The deinitialization fails and the created player is not released. CNcomment:去初始化失败，没有释放掉创建的播放器

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Deinit(HI_VOID);

/**
\brief Create a player. CNcomment:创建一个播放器
\attention \n
This interface must be called after initialization. \n
CNcomment:该接口必须在初始化后调用.\n
\param[in] pstruParam player initialization attribute. CNcomment:播放器初始化属性,类型HI_SVR_SMOOTHSTREAMING_PARAM_S
\param[out] phPlayer handle of the created player. CNcomment:创建的播放器句柄

\retval ::HI_SUCCESS A player is created successfully and the player handle is valid. CNcomment:创建成功，播放器句柄有效
\retval ::HI_FAILURE A player fails to be created. The parameters are invalid or resources are insufficient. CNcomment:创建失败，参数非法或资源不够

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Create(HI_SVR_SMOOTHSTREAMING_PARAM_S *pstruParam, HI_HANDLE *phPlayer);

/**
\brief Destroy a player instance. CNcomment:销毁一个播放器实例
\attention \n
The HI_S32 HI_SMOOTHSTREAMING_Destroy interface is called to destroy the player resource after the ::HI_SMOOTHSTREAMING_Create interface is called to create a player.
CNcomment:调用::HI_SMOOTHSTREAMING_Create创建播放器后，调用该接口销毁播放器资源
\param[in] hPlayer player handle. CNcomment:播放器句柄

\retval ::HI_SUCCESS The player is released successfully. CNcomment:播放器释放成功
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Destroy(HI_HANDLE hPlayer);

/**
\brief Open a smooth streaming media presentation. CNcomment:打开一个smooth streaming媒体
\attention \n
The HI_S32 HI_SMOOTHSTREAMING_Open interface is called to open one smooth streaming presentation, must be called after the ::HI_SMOOTHSTREAMING_Create.
CNcomment:要调用HI_SMOOTHSTREAMING_Open接口，必须先调用HI_SMOOTHSTREAMING_Create创建播放器实例
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pstruMedia:要打开的媒体的URL及播放模式,目前播放模式只支持正常播放模式，后续会增加其他模式

\retval ::HI_SUCCESS The media is opened successfully.
\retval ::HI_FAILURE The media open failed.
CNcomment:同步接口，返回值HI_SUCCESS表示open成功, HI_FAILURE表示失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Open(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIA_S* pstruMedia);

/**
\brief Start playing. CNcomment:开始播放
\attention \n
This interface is an asynchronous interface. It must be called after the ::HI_SMOOTHSTREAMING_Open interface is called. \n
Values returned by this interface cannot be used to check whether the playing is successful. The player notifies the APP of playing success using  \n
CNcomment:异步接口，该接口必须在调用::HI_SMOOTHSTREAMING_Open接口后调用，播放成功后再调用该接口返回HI_FAILURE，\n
不能通过该接口返回值来判断播放器是否播放成功，需要通过查询播放器状态确认，如果当前播放器状态是HI_SVR_SMOOTHSTREAMING_STATE_PLAYING，则play成功\n
而失败将通过由接口HI_SMOOTHSTREAMING_RegistErrCb注册的回调函数通知。
停止播放后，可以调用该接口重新播放

\param[in] hPlayer player handle. CNcomment:播放器句柄

\retval ::HI_SUCCESS The operation is valid. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Play(HI_HANDLE hPlayer);

/**
\brief Stop playing. CNcomment:停止播放
\attention \n
This interface is an asynchronous interface. It can be called to stop playing during playing, fast forward, rewind, and pause. Values returned by this interface cannot be used to check whether playing is stopped successfully. \n
The ::HI_SMOOTHSTREAMING_Play interface can be called to restart playing after playing is stopped.

CNcomment:异步接口，播放、快进、快退、暂停过程中都可以调用该接口停止播放，不能通过该接口返回值来判断播放器\n
是否停止成功，需要通过查询播放器状态确认，如果当前播放器状态是HI_SMOOTHSTREAMING_STATE_TUNING，则stop成功\n
停止播放后，可以调用::HI_SMOOTHSTREAMING_Play接口重新播放

\param[in] hPlayer player handle. CNcomment:播放器句柄

\retval ::HI_SUCCESS The operation is valid. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Stop(HI_HANDLE hPlayer);

/**
\brief Pause playing. CNcomment:暂停播放
\attention \n
This interface is an asynchronous interface. It can be called to pause playing during playing, fast forward, rewind, and pause.
But during trick mode play(fast forward, rewind), pause will cancel trick play, set player back to normal playing and adjust speed to normal speed.
Values returned by this interface cannot be used to check whether playing is paused successfully. \n
The ::HI_SMOOTHSTREAMING_Play interface can be called to restart playing after playing is stopped.

CNcomment:异步接口，播放、快进、快退、暂停过程中都可以调用该接口停止播放，但在快进快退的过程中暂停会取消快进快退,\n
调用HI_SMOOTHSTREAMING_Resume后会回到正常播放模式不能继续快进快退播放。不能通过该接口返回值来判断播放器\n
是否暂停成功，需要通过查询播放器状态确认，如果当前播放器状态是HI_SVR_SMOOTHSTREAMING_STATE_PAUSED，则pause成功\n
暂停播放后，可以调用::HI_SMOOTHSTREAMING_Resume接口恢复播放

\param[in] hPlayer player handle. CNcomment:播放器句柄

\retval ::HI_SUCCESS The operation is valid. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Pause(HI_HANDLE hPlayer);

/**
\brief Resume playing. CNcomment:恢复正常播放
\attention \n
This interface is an asynchronous interface. It can be called to resume playing after calling HI_SMOOTHSTREAM_Pause or HI_SMOOTHSTREAMING_TPlay, \n
Values returned by this interface cannot be used to check whether playing is resumed successfully.

CNcomment:异步接口，调用HI_SMOOTHSTREAMING_Pause暂停播放或者调用HI_SMOOTHSTREAMING_TPlay进行快进快退播放操作后，可以调用此接口恢复正常播放，\n
不能通过该接口返回值来判断播放器是否恢复成功，需要通过查询播放器状态确认，如果当前播放器状态是HI_SVR_SMOOTHSTREAMING_STATE_PLAYING，则resume成功\n

\param[in] hPlayer player handle. CNcomment:播放器句柄

\retval ::HI_SUCCESS The operation is valid. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Resume(HI_HANDLE hPlayer);

/**
\brief Fast forward and rewind. CNcomment:快进、快退
\attention \n
This interface is an asynchronous interface. It must be called after the ::HI_SMOOTHSTREAMING_Play interface is called.\n
The ::HI_SMOOTHSTREAMING_Resume interface can be called to \n
resume normal playing after fast forward or rewind.
CNcomment:异步接口，该函数必须调用::HI_SMOOTHSTREAMING_Play后调用，不能通过该接口\n
返回值来判断是否快进或快退成功,快进、快退后通过调用::HI_SMOOTHSTREAMING_Resume\n
接口恢复正常播放。

\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] eSpeed playing speed. The value is HI_SVR_SMOOTHSTREAMING_SPEED_E. CNcomment:播放倍数,值为HI_SVR_SMOOTHSTREAMING_SPEED_E

\retval ::HI_SUCCESS The operation is valid. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_TPlay(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_SPEED_E eSpeed);

/**
\brief Seek to a specified location for playing. CNcomment:跳到指定位置播放
\attention \n
This interface is an asynchronous interface. It must be called after the ::HI_SMOOTHSTREAMING_Open interface is called. It can be called to jump to a specified time point for playing.
CNcomment:异步接口，该接口必须在调用::HI_SMOOTHSTREAMING_Open接口后调用，调用该接口跳到指定时间点播放

\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] s64Sec seeking time. The unit is seconds. CNcomment:seek时间，单位秒

\retval ::HI_SUCCESS The operation is successful. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Seek(HI_HANDLE hPlayer, HI_S64 s64Sec);

/**
\brief Extended Interface.
\attention \n
无
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] u32InvokeId  command of the operation, value is ::hiSVR_SMOOTHSTREAMING_INVOKE_ID_E.
\param [in] pArg parameter of the command

\retval ::HI_SUCCESS The operation is successful. CNcomment:合法操作
\retval ::HI_FAILURE The operation is invalid. CNcomment:非法操作

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Invoke(HI_HANDLE hPlayer, HI_U32 u32InvokeId, HI_VOID *pArg);

/**
\brief Obtain information about the current player running information,
CNcomment:获取当前播放器状态信息
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Open interface is called.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Open接口后调用

\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[out] pstruInfo obtained file information. CNcomment:获取的播放器状态信息

\retval ::HI_SUCCESS The file information is obtained successfully. CNcomment:获取到播放器状态信息
\retval ::HI_FAILURE The file information fails to be obtained. CNcomment:获取播放器状态信息失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetPlayerInfo(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_RUNNING_INFO_S* pstruRunningInfo);

/**
\brief Obtain information about the current open file, such as the file size, playing duration, file bit rate, video width, video height, coding format, frame rate, video bit rate, audio encoding, and audio bit rate.
CNcomment:获取当前打开文件信息，如是否为直播、播放时长、开始播放时间、音轨信息等CNend
\attention \n
This interface must be called after the ::HI_SVR_SMOOTHSTREAMING_Open interface is called.
CNcomment:该函数必须在调用::HI_SVR_SMOOTHSTREAMING_Open接口后调用CNend

\param[in] hPlayer player handle. CNcomment:播放器句柄CNend
\param[out] pMediaInfo obtained file information. CNcomment:获取的文件信息CNend

\retval ::HI_SUCCESS The file information is obtained successfully. CNcomment:获取到文件信息CNend
\retval ::HI_FAILURE The file information fails to be obtained. CNcomment:获取文件信息失败CNend

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetMediaInfo(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S *pMediaInfo);


/**
\brief Register a player error callback function. CNcomment:注册播放器出错事件回调函数
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Create接口后调用，该函数不能在player任何回调事件中调用
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pfnErrCb player error callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_ERROR_FN. CNcomment:播放器出错事件回调函数，回调函数定义::HI_SMOOTHSTREAM_ERROR_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:注册成功
\retval ::HI_FAILURE The registration fails. CNcomment:设置失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistErrCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ERROR_FN pfnErrCb);

/**
\brief Register a player error callback function. CNcomment:注册播放器媒体准备好回调函数, mediaready指已经获取到媒体描述文件并正确解析，已获取到媒体相关信息
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Create接口后调用，该函数不能在player任何回调事件中调用
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pfnMediaReadyCb player error callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN.
CNcomment:播放器mediaready回调函数，回调函数定义::HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:注册成功
\retval ::HI_FAILURE The registration fails. CNcomment:设置失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistMediaReadyCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN pfnMediaReadyCb);

/**
\brief Register a player event callback function. CNcomment:注册播放器状态更新事件的回调函数\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Create接口后调用，该函数不能在player任何回调事件中调用
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pfnEventCb player error callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_STATE_FN.
CNcomment:播放器状态更新事件回调函数，回调函数定义::HI_SVR_SMOOTHSTREAMING_STATE_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:注册成功
\retval ::HI_FAILURE The registration fails. CNcomment:设置失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistStateEventCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_STATE_FN pfnStateCb);

/**
\brief Register a player event callback function. CNcomment:注册播放命令执行完事件的回调函数\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Create接口后调用，该函数不能在player任何回调事件中调用
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pfnCommandCb player command done callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_CMD_FN.
CNcomment:播放器播放命令执行完回调函数，回调函数定义::HI_SVR_SMOOTHSTREAMING_CMD_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:注册成功
\retval ::HI_FAILURE The registration fails. CNcomment:设置失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistCmdCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_CMD_FN pfnCommandCb);

/**
\brief Register subtitle data callback function. CNcomment:注册播放数据回调函数\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Create接口后调用。
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] pfnSubCb subtitle data callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN.
CNcomment:pfnSubCb为字幕数据回调函数，回调函数定义::HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:注册成功
\retval ::HI_FAILURE The registration fails. CNcomment:设置失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistSubCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN pfnSubCb);

/**
\brief force a quality level(biterate level). CNcomment:停止smooth streaming根据网络带宽自动选择不同码率的功能，强制选择一个码率播放\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called.
CNcomment:该函数必须在调用::HI_SMOOTHSTREAMING_Create接口后调用
\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] s32TrackIdx，强行指定的track索引，此索引对应HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S::HI_SVR_SMOOTHSTREAMING_VID_TRACK_INFO_S::s32TrackIdx
CNcomment:用户可以根据由注册的HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN传回的HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S中的媒体信息,\n
得到每个track对应的bitrate及相应的s32TrackIdx, 然后根据网络情况进行选择.

\retval ::HI_SUCCESS The operation is successful. CNcomment:设置成功
\retval ::HI_FAILURE The operation fails. CNcomment:设置失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_ForceQualityLevel(HI_HANDLE hPlayer, HI_S32 s32TrackIdx);

/**
\brief obtain player parameters. CNcomment:获取播放器参数
\attention \n
CNcomment:The following operations are supported:
HI_SVR_SMOOTHSTREAMING_ATTR_AVPLAYER_HDL:used to abtain current avplayer handle.
HI_SVR_SMOOTHSTREAMING_ATTR_WINDOW_HDL:used to abtain current window handle.
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING: used to abtain cache timing setting.
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING: used to abtain http setting.

CNcomment:支持的操作如下
HI_SVR_SMOOTHSTREAMING_ATTR_AVPLAYER_HDL:用于获取avplayer的句柄.
HI_SVR_SMOOTHSTREAMING_ATTR_WINDOW_HDL:用于获取播放窗体window的句柄.
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING: 用于获取缓冲时序的参数.
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING: 用于获取http相关设置的参数.

\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] eAttrId ID of the player parameter to be set. CNcomment:要获取的播放器参数ID
\param[out] pArg player parameter to be set. CNcomment:获取到的播放器参数

\retval ::HI_SUCCESS Parameters are set successfully. CNcomment:参数获取成功
\retval ::HI_FAILURE The operation fails. CNcomment:操作失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetParam(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ATTR_E eAttrId, HI_VOID* pArg);

/**
\brief Set player parameters. CNcomment:设置播放器参数
\attention \n
CNcomment:The following operations are supported:
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING, used to set media data cache timing.
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING, used to set http param.
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_PATH, used to specify DRM certificate path and license store path
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_DOMAIN, used to set DRM domain information

CNcomment:支持的操作如下
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING, 用于设置媒体数据缓冲的时序
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING, 用于设置http相关参数，比如超时时长，连接失败重连次数等
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_PATH, 用于设置DRM证书及许可证保存的路径
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_DOMAIN, 用于设置DRM域信息

\param[in] hPlayer player handle. CNcomment:播放器句柄
\param[in] eAttrId ID of the player parameter to be set. CNcomment:要设置的播放器参数ID
\param[in] pArg player parameter to be set. CNcomment:要设置的播放器参数

\retval ::HI_SUCCESS Parameters are set successfully. CNcomment:参数设置成功
\retval ::HI_FAILURE The operation fails. CNcomment:操作失败

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_SetParam(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ATTR_E eAttrId, HI_VOID* pArg);

#ifdef __cplusplus
}
#endif
#endif
