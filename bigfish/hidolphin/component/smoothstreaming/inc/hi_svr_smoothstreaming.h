/**
 \file
 \brief Server smoothstreaming module. CNcomment:HiSmoothStreamingģ��
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
/** @{ */  /** <!-- [HiSmoothStreaming data structure] CNcomment:��HiSmoothStreaming���ݽṹ�� */

/** smoothstreaming url max length*/
/** CNcomment:url��󳤶� */
#define HI_SVR_SMOOTHSTREAMING_FORMAT_MAX_URL_LEN 1024

/** Invalid handle */
/** CNcomment:�Ƿ���� */
#define HI_SVR_SMOOTHSTREAMING_INVALID_HDL (0)

/** smoothstreaming language max length */
/** CNcomment:���Ե���󳤶�*/
#define HI_SVR_SMOOTHSTREAMING_LANG_LEN    (4)


/** playing speed flag*/
/** CNcomment:�����ٶȱ�־ */
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
/** CNcomment:���������� */
typedef enum hiSVR_SMOOTHSTREAMING_ATTR_E
{
    HI_SVR_SMOOTHSTREAMING_ATTR_AVPLAYER_HDL = 0,       /**< obtain the avplayer handle, The parameter is the HI_HANDLE variable. */
                                                        /**< CNcomment:��ȡ��ǰ��AVPlay���������ΪHI_HANDLE���� */
    HI_SVR_SMOOTHSTREAMING_ATTR_WINDOW_HDL,             /**< obtain the Window handle, The parameter is the HI_HANDLE variable. */
                                                        /**< CNcomment:��ȡ��ǰ��Window���������ΪHI_HANDLE���� */
    HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING,           /**< Set or obtain the cache timing. The parameter is ::HI_SVR_SMOOTHSTREAMING_CACHE_TIMING_S. */
                                                        /**< CNcomment:����ý�����ݵĻ���ʱ�򣬲���������:HI_SVR_SMOOTHSTREAMING_CACHE_TIMING_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING,           /**< Set or obtain the http attribute. The parameter is ::HI_SVR_SMOOTHSTREAMING_HTTP_ATTR_S. */
                                                        /**< CNcomment:����http�����ԣ�����������:HI_SVR_SMOOTHSTREAMING_HTTP_ATTR_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_STREAM_ID,              /**< Set or obtain the stream ID. This attribute is applicable to multi-audio multi-video streams. The parameter is ::HI_SVR_PLAYER_STREAMID_S. */
                                                        /**< CNcomment:����/��ȡ����ţ���������Զ���Ƶ������Ƶ�������������Ϊ::HI_SVR_PLAYER_STREAMID_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_PATH,               /**< Set the DRM path. The parameter is ::HI_SVR_SMOOTHSTREAMING_DRM_PATH_S. */
                                                        /**< CNcomment:����DRM�豸֤��·�������֤�ı��ر���·��������������:HI_SVR_SMOOTHSTREAMING_DRM_PATH_S */
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_DOMAIN,             /**< reserved, currently no use*/
                                                        /**< CNcomment:��չ�ӿڣ���ȡDRM header��������Ϣ*/
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_CERTBUFF,           /**< reserved, currently no use.*/
                                                        /**< CNcomment:��չ�ӿڣ���ʱδʵ�֣�Ԥ�����ڴ��ⲿ͸��buffer��ʽ��playready֤��*/
    HI_SVR_SMOOTHSTREAMING_ATTR_DRM_INITIATOR,          /**< reserved, currently no use.*/
                                                        /**< CNcomment:��չ�ӿڣ���ʱδʵ�֣�Ԥ�����ڴ��ⲿ͸��DRM�ĳ�ʼ����Ϣ*/
    HI_SVR_SMOOTHSTREAMING_ATTR_USERDATA,               /**< reserved, currently no use.*/
                                                        /**< CNcomment:��չ�ӿڣ���ʱδʵ�֣�Ԥ�����ڴ��ⲿ͸���û��������Ϣ����ý�����ݵ�����URL��*/
    HI_SVR_SMOOTHSTREAMING_ATTR_BUTT
} HI_SVR_SMOOTHSTREAMING_ATTR_E;

/** media data cache timing*/
/** CNcomment:���������� */
typedef struct hiSVR_SMOOTHSTREAMING_CACHE_TIMING_S
{
    HI_U32 u32DefBufferDelayMs;     /**< Default value(in ms) for the "BufferDelay" in the SSPK, which is used to judge if there is enough buffered media data to start playing. */
                                    /**< CNcomment: BufferDelay��Ĭ��ֵ��BufferDelay���ڿ���ý�����ݵĻ��壬һ���Ѿ������ý�����ݵ�PTS����������ŵ�ý�����ݵ�PTS+BufferDelay������������*/
    HI_U32 u32StepBufferDelayMs;    /**< step value for the "BufferDelay"*/
                                    /**< CNcomment: BufferDelay�Ĳ���ֵ.������ŵĹ����г��ֻ������ݲ��㣬Ƿ�ص���������������Զ��Դ˲�������BufferDelay���ԼӴ󻺳����ޣ�����Ƿ�صĿ���*/
    HI_U32 u32MaxBufferDelayMs;     /**< max value for the "BufferDelay"*/
                                    /**< CNcomment: BufferDelay�����ֵ��BufferDelay�������ӣ������ܳ��������ֵ*/
    HI_U32 u32RebufferThresholdMs;  /**< Time value(in ms) for buffer underrun check*/
                                    /**< CNcomment: �����ж�Ƿ�ص�����ֵ������ѻ����ý�����ݳ���С�ڴ�����ֵ������ͣ���ţ��ȴ�����*/
} HI_SVR_SMOOTHSTREAMING_CACHE_TIMING_S;

/** http attribute settings*/
/** CNcomment:http������� */
typedef struct hiSVR_SMOOTHSTREAMING_HTTP_ATTR_S
{
    HI_S32 s32HttpMaxRedirectCt;                /**< max count for http redirection, the default value is 10*/
    HI_S32 s32HttpResponseTimeout;              /**< timeout for http response, the default value is 20, in seconds*/
    HI_S32 s32HttpInitialReceiveTimeout;        /**< timeout for the first http receive, the default value is 30, in seconds*/
    HI_S32 s32HttpSubsequentReceiveTimeout;     /**< timeout for the subsequent(not the first one) http receive, the default is 6, in seconds*/
    HI_S32 s32HttpMaxReconnectAttemptCt;        /**< max count for http reconnect, the default is 1*/
} HI_SVR_SMOOTHSTREAMING_HTTP_ATTR_S;

/** DRM path for device certificate and license storage*/
/** CNcomment:DRM �豸֤��·�������������֤����·�� */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_PATH_S
{
    HI_U8* pDrmCertPath;            /**< DRM certificate path*/
                                    /**< CNcomment:DRM�豸֤��ı���Ŀ¼��ֻ��Ŀ¼��������ָ���ļ���,Ӧ�ñ��뱣֤�����Ŀ¼���пɶ���дȨ�� */
    HI_U8* pDrmLicenseStoreFile;    /**< DRM license storage path*/
                                    /**< CNcomment:DRMý�����֤�ı��ر���Ŀ¼����Ҫ�����ļ������ڵ�����·����Ӧ�ñ��뱣֤�����·�����пɶ���дȨ��*/
} HI_SVR_SMOOTHSTREAMING_DRM_PATH_S;

/** DRM string */
/** CNcomment:DRM�ӿ�ר�õ�string���ݽṹ */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_STRING_S
{
    HI_U8  *pszString;      /**< name*/
    HI_U32  u32Length;      /**< data length*/
    HI_U8  *pu8Addr;        /**< data*/
} HI_SVR_SMOOTHSTREAMING_DRM_STRING_S;

/** DRM header */
/** CNcomment:DRM header�ӿ�ר�õ����ݽṹ */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_HEADER_S
{
    HI_U32  u32Length;      /**< data length*/
    HI_U8  *pu8Addr;        /**< data*/
} HI_SVR_SMOOTHSTREAMING_DRM_HEADER_S;

/** DRM certificate buffer*/
/** CNcomment:buffer��ʽ��playready֤�����ݽṹ */
typedef struct hiSVR_SMOOTHSTREAMING_DRM_CERTBUFF_S
{
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stPriv;                /**< content of playready certificate file "priv.dat"*/
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stZgpriv;              /**< content of playready certificate file "zgpriv.dat"*/
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stBgroupcert;          /**< content of playready certificate file "bgroupcert.dat"*/
    HI_SVR_SMOOTHSTREAMING_DRM_STRING_S stDevcerttemplate;     /**< content of playready certificate file "devcerttemplate.dat"*/
    HI_U8 *pszKeyfilePath;                                     /**< keyfile path*/
} HI_SVR_SMOOTHSTREAMING_DRM_CERTBUFF_S;

/** player initialation parameter*/
/** CNcomment:��������ʼ������*/
typedef struct hiSVR_SMOOTHSTREAMING_PARAM_S
{
    HI_HANDLE hAVPlayer;            /**< AVPlay created externally. A window device and a sound device are bound to the AVPlay and the window size and the sound volume are set.
                                        The AVPlay handle can be transferred to the HiPlayer, which will use the AVPlay for playing.  */
                                    /**< CNcomment:�ⲿ�Ѿ�������avplay������window,sound�������ú�window�Ĵ�Сλ�ã�sound��������
                                        ���Խ�avplay�������HiPlayer��HiPlayer����ʹ�ø�avplay���š� */
    HI_U32  x, y, w, h;             /**< Reserved attributes,not in use currently.Coordinate, width, and height of the video output window. This parameter is invalid in the case of hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL. *//**< CNcomment:�������ԣ�Ŀǰδʹ�á���Ƶ����������꼰��ߣ�hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL���ò�����Ч */
    HI_U32  u32MixHeight;           /**< Reserved attribute,not in use currently.Audio output mix weight. The value ranges from 0 to 100. This parameter is invalid in the case of hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL. *//**< CNcomment:�������ԣ�Ŀǰδʹ�á���Ƶ�������Ȩ��0-100��hAVPlayer!=HI_SVR_PLAYER_INVALID_HDL���ò�����Ч */
    HI_U32   u32SndPort;            /**< Reserved attribute,not in use currently.Specified audio port number, 0: master audio, 1: slave audio  *//**< CNcomment:�������ԣ�Ŀǰδʹ�á�ָ����Ƶ�˿ںţ�0����������1������*/
    HI_U32   u32Display;            /**< Reserved attribute,not in use currently.Display mode*//**< CNcomment:�������ԣ�Ŀǰδʹ�á���Ƶ��ʾģʽ��HD, SD*/
    HI_U32   u32VideoCacheSize;     /**< Reserved attribute,not in use currently.video data cache size, in byte, max value 32*1024*1024, minvalue 512*1024.*//**< CNcomment:�������ԣ�Ŀǰδʹ�á���Ƶ��������С������512*1024�����32*1024*1024����λ�ֽڡ�*/
    HI_U32   u32AudioCacheSize;     /**< Reserved attribute,not in use currently.audio data cache size, in byte, max value 4*1024*1024, minvalue 192*1024 *//**< CNcomment:�������ԣ�Ŀǰδʹ�á���Ƶ��������С������192*1024�����4*1024*1024����λ�ֽڡ�*/
} HI_SVR_SMOOTHSTREAMING_PARAM_S;

/** player mode*/
/** CNcomment:����������ģʽ*/
typedef enum hiSVR_SMOOTHSTREAMING_PLAYMODE_E
{
    HI_SVR_SMOOTHSTREAMING_PLAYMODE_NORMAL = 0,
    HI_SVR_SMOOTHSTREAMING_PLAYMODE_BUTT,
} HI_SVR_SMOOTHSTREAMING_PLAYMODE_E;

/** input media*/
/** CNcomment:�����ý��*/
typedef struct hiSVR_SMOOTHSTREAMING_MEDIA_S
{
    HI_SVR_SMOOTHSTREAMING_PLAYMODE_E   ePlayMode;                 /**< player mode*/
    HI_CHAR  aszUrl[HI_SVR_SMOOTHSTREAMING_FORMAT_MAX_URL_LEN];    /**< input media url*/
} HI_SVR_SMOOTHSTREAMING_MEDIA_S;

/** player state*/
/** CNcomment:������״̬*/
typedef enum hiSVR_SMOOTHSTREAMING_STATE_E
{
    HI_SVR_SMOOTHSTREAMING_STATE_INITIAL = 0,       /**< Initial state*/
                                                    /**< CNcomment:��ʼ״̬���ڵ�һ�γɹ�����HI_SMOOTHSTREAMING_Open֮ǰ�������������״̬*/
    HI_SVR_SMOOTHSTREAMING_STATE_STOPPED,           /**< stopped state*/
                                                    /**< CNcomment:�ѳɹ���һ��ý��, ����ֹͣ����*/
    HI_SVR_SMOOTHSTREAMING_STATE_PLAYING,           /**< playing state*/
                                                    /**< CNcomment:��������״̬�������������ٶȲ���ý��*/
    HI_SVR_SMOOTHSTREAMING_STATE_PAUSED,            /**< paused state*/
    HI_SVR_SMOOTHSTREAMING_STATE_FAST_FORWARD,      /**< fast forwrd state*/
                                                    /**< CNcomment:���״̬*/
    HI_SVR_SMOOTHSTREAMING_STATE_FAST_BACKWARD,     /**< fast backward state*/
                                                    /**< CNcomment:����״̬*/
    HI_SVR_SMOOTHSTREAMING_STATE_BUT
} HI_SVR_SMOOTHSTREAMING_STATE_E;

/** player running state*/
/** CNcomment:������������Ϣ*/
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
/** CNcomment:ý�����Ƶtrack��Ϣ��һ����˵һ��smooth streamingý��ֻ��һ����Ƶ��stream,
����Ƶ���ֿ��԰������������ͬ�������ʲ�ͬ����Ƶ������һ����������������һ��track*/
typedef struct hiSVR_SMOOTHSTREAMING_VID_TRACK_INFO_S
{
    HI_S32 s32StreamIdx;        /**< index for the stream which this video track belongs to*/
                                /**< CNcomment:��track�����ڵ�stream�������ţ�*/
    HI_S32 s32TrackIdx;         /**< the index of this video track*/
    HI_U32 u32Format;           /**< the encoding format of this track, For details about the value definition, see ::HI_UNF_VCODEC_TYPE_E.*/
                                /**< CNcomment:����Ƶtrack�ı����ʽ����ȡֵ��::HI_UNF_VCODEC_TYPE_E*/
    HI_S32 s32Bitrate;          /**< the bitrate of this video track*/
    HI_S32 s32Width;            /**< the width in pixels of this video track*/
    HI_S32 s32Height;           /**< the heigth in pixels of this video track*/
} HI_SVR_SMOOTHSTREAMING_VID_TRACK_INFO_S;

/** audio track information*/
/** CNcomment:ý�����Ƶtrack��Ϣ��һ����˵һ��smooth streamingý������ж����Ƶ��stream(������),
��һ����Ƶ��һ��ֻ����һ����Ƶtrack*/
typedef struct hiSVR_SMOOTHSTREAMING_AUD_TRACK_INFO_S
{
    HI_S32 s32StreamIdx;        /**< the stream index which this track belongs to*/
                                /**< CNcomment:��track�����ڵ�stream�������ţ�*/
    HI_S32 s32TrackIdx;         /**< the index of this track*/
    HI_U32 u32Format;           /**< the encoding format of this track, For details about the value definition, see ::HA_FORMAT_E.*/
                                /**< CNcomment:����Ƶtrack�ı����ʽ����ȡֵ��::HA_FORMAT_E*/
    HI_S32 s32Bitrate;          /**< the bitrate of this audio track*/
    HI_U32 u32SampleRate;       /**< the samplerate of this audio track*/
    HI_U32 u32BlockAlign;       /**< Number of bytes contained in a packet of this audio track*/
                                /**< CNcomment:packet���������ֽ���*/
    HI_U16 u16Channels;         /**< num of channels*/
    HI_U16 u16BitsPerSample;    /**< Number of bits occupied by each audio sampling point such as 8 bits or 16 bits.*/
    HI_CHAR aszLanguage[HI_SVR_SMOOTHSTREAMING_LANG_LEN];  /**< Audio stream language *//**< CNcomment:��Ƶ������ */
} HI_SVR_SMOOTHSTREAMING_AUD_TRACK_INFO_S;


/** Subtitle information */
/** CNcomment:��Ļ��Ϣ */
typedef struct hiSVR_SMOOTHSTREAMING_SUB_INFO_S
{
    HI_S32  s32StreamIdx;                    /**< Stream index. *//**< CNcomment:������ */
    HI_S32  s32TrackIdx;                     /**< the index of this track*/
    HI_S32  s32Bitrate;                      /**< the bitrate of this subtitle track*/
    HI_U32  u32Format;                       /**< Subtitle format, For details about the value definition, see::HI_FORMAT_SUBTITLE_TYPE_E *//**< CNcomment:��Ļ��ʽ��ȡֵ::HI_FORMAT_SUBTITLE_TYPE_E */
    HI_U32  u32CharSet;                      /**< Encoding type of the subtitle, the value range is as follows, default is 0.*/
    HI_CHAR aszLanguage[HI_SVR_SMOOTHSTREAMING_LANG_LEN]; /**< Subtitle language *//**< CNcomment:��Ļ���� */
} HI_SVR_SMOOTHSTREAMING_SUB_TRACK_INFO_S;


/** media information*/
/** CNcomment:smooth streamingý����Ϣ*/
typedef struct hiSVR_SMOOTHSTREAMING_MEDIA_INFO_S
{
    HI_BOOL bIsLive;                /**< The flag represent if this media presentation is live.1 for live, 0 for none live*/
                                    /**< CNcomment:��־λ�����ڱ�ʾ��ǰý����ֱ�����ǵ㲥.1, ֱ����0���㲥*/
    HI_S64 s64Duration;             /**< duration of this media presentation, in ms*//**< CNcomment:�ļ����ŵ�ʱ�䳤�ȣ���λms*/
    HI_S64 s64StartTime;            /**< start time of this media presentation, in ms*//**< CNcomment:�ļ����ŵĿ�ʼʱ�䣬��λms*/
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
/** CNcomment:Ҫ�л���������Ƶ����Ļ��ID  */
typedef struct hiSVR_SMOOTHSTREAMING_STREAMID_S
{
    HI_U16 u16VidStreamId;   /**< Video stream ID. The value is  ranges from 0 to (u32NumVidStreams - 1), which u32NumVidStreams is defined in structure HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S. */
                           /**< CNcomment:��Ƶ��id��ȡֵ��Χ0-(u32NumVidStreams - 1)��u32NumVidStreams��HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S�ṹ�ж���*/
    HI_U16 u16AudStreamId;   /**< Audio stream ID. The value is  ranges from 0 to (u32NumAudStreams - 1), which u32NumAudStreams is defined in structure HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S. */
                           /**< CNcomment:��Ƶ��id��ȡֵ��Χ0-(u32NumAudStreams - 1)��u32NumAudStreams��HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S�ṹ�ж���*/
    HI_U16 u16SubStreamId;  /**< Subtitle ID.  The value is  ranges from 0 to (u32NumSubStreams - 1), which u32NumSubStreams is defined in structure HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S.*/
                           /**< CNcomment:��Ļid��ȡֵ��Χ0-(u32NumSubStreams - 1)��u32NumSubStreams��HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S�ṹ�ж���*/
} HI_SVR_SMOOTHSTREAMING_STREAMID_S;


/** smooth streaming error type*/
/** CNcomment:smooth streaming��������*/
typedef enum hiSVR_SMOOTHSTREAMING_ERROR_TYPE_E
{
    HI_SVR_SMOOTHSTREAMING_ERROR_NOERROR = 0,       /**< no error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_UNKNOWN,           /**< unknown error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_NOMEM,             /**< not enough memory*/
    HI_SVR_SMOOTHSTREAMING_ERROR_MANIFEST,          /**< manifest error*/
                                                    /**< CNcomment:smooth steaming manifest����ʧ��*/
    HI_SVR_SMOOTHSTREAMING_ERROR_SOCKET,            /**< socket error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_HTTP,              /**< http error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_DATA,              /**< chunk data error*/
                                                    /**< CNcomment:�˴��������ý��ķ�Ƭ�����д�*/
    HI_SVR_SMOOTHSTREAMING_ERROR_DRMINIT,           /**< drm playready initial error*/
    HI_SVR_SMOOTHSTREAMING_ERROR_BUTT
} HI_SVR_SMOOTHSTREAMING_ERROR_TYPE_E;

/** smooth streaming error information*/
/** CNcomment:smooth streaming������Ϣ*/
typedef struct hiSVR_SMOOTHSTREAMING_ERROR_S
{
    HI_SVR_SMOOTHSTREAMING_ERROR_TYPE_E eErrorType;         /**< error type*/
    HI_S32 s32HttpErr;                                      /**< http error code*/
                                                            /**< CNcomment:http������*/
} HI_SVR_SMOOTHSTREAMING_ERROR_S;

/** event information*/
/** CNcomment:smooth streaming״̬�����¼�������ԭ��*/
typedef enum hiSVR_SMOOTHSTREAMING_UPDATE_E
{
    HI_SVR_SMOOTHSTREAMING_UPDATE_UNKNOWN = 0,
    HI_SVR_SMOOTHSTREAMING_UPDATE_STATE_CHANGE,
    HI_SVR_SMOOTHSTREAMING_UPDATE_BUFFERREADY,              /**< This event means we already got enough cached media data, start to play*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_BUFFERLOW,                /**< There is an underrun event*/
                                                            /**< CNcomment:Ƿ���¼�*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_BITRATECHANGE,            /**< Bit rate changed*/
                                                            /**< CNcomment:ý��ı����ʱ仯�¼�*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_EOF,                      /**< end of file event*/
                                                            /**< CNcomment:��ʾ��ǰý���Ѳ������*/
    HI_SVR_SMOOTHSTREAMING_UPDATE_SOF,                      /**< start of file event*/
                                                            /**< CNcomment:��ʾ��ǰý���ѿ������ͷ*/
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
/** CNcomment:�汾�Ŷ��� */
typedef struct hiSVR_SMOOTHSTREAMING_VERSION_S
{
    HI_U8 u8VersionMajor;    /**< Major version accessor element */
    HI_U8 u8VersionMinor;    /**< Minor version accessor element */
    HI_U8 u8Revision;        /**< Revision version accessor element */
    HI_U8 u8Step;            /**< Step version accessor element */
} HI_SVR_SMOOTHSTREAMING_VERSION_S;

/** Command of the invoking */
/** CNcomment:invoke�������� */
typedef enum hiSVR_SMOOTHSTREAMING_INVOKE_ID_E
{
    HI_SVR_SMOOTHSTREAMING_INVOKE_PRE_CLOSE_FILE = 0x0, /**< the command of the file to be closed, no parameter*//**< CNcomment:Ԥ�ر��ļ����޲��� */
    HI_SVR_SMOOTHSTREAMING_INVOKE_BUTT
} hiSVR_SMOOTHSTREAMING_INVOKE_ID_E;

/** @} */  /** <!-- ==== Structure Definition end ==== */

/******************************* API declaration *****************************/
/** @{ */  /** <!-- [HiSmoothStreaming] CNcomment:��HiSmoothStreaming API ������ */

/**
\brief error event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistErrCb interface can be called to register the callback function. CNcomment:�����¼��ص�����������::HI_SVR_SMOOTHSTREAMING_RegistErrCb�ӿ�ע��ûص�����
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pstruErr error event parameter. CNcomment: �����¼�����

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_ERROR_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ERROR_S *pstruErr);


/**
\brief mediaready event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistMediaReadyCb interface can be called to register the callback function. CNcomment:ý��׼�����¼��ص�����������::HI_SVR_SMOOTHSTREAMING_RegistMediaReadyCb�ӿ�ע��ûص�����
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pstruMediaInfo error event parameter. CNcomment: ý��׼�����¼�����

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S *pstruMediaInfo);

/**
\brief state update event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistStateEventCb interface can be called to register the callback function. CNcomment:������״̬�����¼��ص�����������::HI_SVR_SMOOTHSTREAMING_RegistStateEventCb�ӿ�ע��ûص�����
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pStruEvent error event parameter. CNcomment: ������״̬�����¼�����

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_STATE_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_STATE_INFO_S* pStruEvent);

/**
\brief command done event callback function. The ::HI_SVR_SMOOTHSTREAMING_RegistCmdCb interface can be called to register the callback function. CNcomment:��������ִ�����¼��ص�����������::HI_SVR_SMOOTHSTREAMING_RegistCmdCb�ӿ�ע��ûص�����
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pStruEvent error event parameter. CNcomment: ��������ִ�����¼�����

\retval ::None

\see \n
None.
*/
typedef HI_VOID (*HI_SVR_SMOOTHSTREAMING_CMD_FN)(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_CMD_INFO_S* pStruEvent);

/**
\brief subtitle text data call back function. CNcomment:��Ļ���ݻص�����:HI_SVR_SMOOTHSTREAMING_RegistSubCb�ӿ�ע��ûص�����
\attention \n
None.
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pData subtitle data. CNcomment: ��Ļ����
\param[in] u32DataLen subtitle data len. CNcomment: ��Ļ���ݳ���
\param[in] isFinal is it the end of subtitle file. CNcomment: ��Ļ�ļ��Ƿ������־
\param[in] s64PtsAjustTimeMs pts adjust value. CNcomment: pts����ֵ
\param[in] u32UserData user data. CNcomment: �ͻ�����

\retval ::HI_SUCCESS CNcomment:����ɹ�
\retval ::HI_FAILURE CNcomment:��Ļ���ݴ���ʧ��

\see \n
None.
*/

typedef HI_S32 (*HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN)(HI_HANDLE hPlayer, HI_U8* pData, HI_U32 u32DataLen, HI_BOOL isFinal,HI_S64 s64PtsAjustTimeMs,HI_U32 u32UserData);


#ifdef __cplusplus
extern "C" {
#endif

/**
\brief Get version of HiSmoothStream Player. CNcomment:ȡ������汾��
\attention \n
\param[out] pstruVersion version of HiSmoothStreaming lib. CNcomment:ȡ�õ�����汾��

\retval ::HI_SUCCESS CNcomment:ȡ�ð汾�ɹ�
\retval ::HI_FAILURE CNcomment:�����Ƿ�

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetVersion(HI_SVR_SMOOTHSTREAMING_VERSION_S* pstruVersion);

/**
\brief Initialize the player. CNcomment:��ʼ��Player
\attention \n
The HI_S32 HI_SMOOTHSTREAMING_Init interface can be called to return a success message after the initialization is successful. Multiple processes are not supported
. This interface must be called prior to other interfaces.
CNcomment:��ʼ���ɹ����ٵ��øýӿڷ��سɹ�����֧�ֶ���̣����������ӿ�ǰ�����ȵ��øýӿ�
\param None. CNcomment:��

\retval ::HI_SUCCESS The initialization is successful. CNcomment:��ʼ���ɹ�
\retval ::HI_FAILURE The initialization fails. CNcomment:��ʼ��ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Init(HI_VOID);

/**
\brief Deinitialize the player module by calling the HI_S32 HI_SMOOTHSTREAMING_Deinit interface. The player module is not used any more. CNcomment:ȥ��ʼ��playerģ�飬����ʹ��playerģ�飬���øýӿ�ȥ��ʼ��playerģ��
\attention \n
The ::HI_SMOOTHSTREAMING_Destroy interface must be called to release the created player first. Otherwise, a failure is returned. The Deinit interface does not release the player resource. \n
This interface can be called to return a success message after the deinitialization is successful.
CNcomment:�����ȵ���::HI_SMOOTHSTREAMING_Destroy�ӿ��ͷŵ������Ĳ��������ٵ��øýӿڣ�����᷵��ʧ�ܣ�Deinit�������ͷ�\n
��������Դ��ȥ��ʼ���ɹ����ٵ��øýӿڷ��سɹ�
\param None. CNcomment:��

\retval ::HI_SUCCESS The deinitialization is successful. CNcomment:ȥ��ʼ���ɹ�
\retval ::HI_FAILURE The deinitialization fails and the created player is not released. CNcomment:ȥ��ʼ��ʧ�ܣ�û���ͷŵ������Ĳ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Deinit(HI_VOID);

/**
\brief Create a player. CNcomment:����һ��������
\attention \n
This interface must be called after initialization. \n
CNcomment:�ýӿڱ����ڳ�ʼ�������.\n
\param[in] pstruParam player initialization attribute. CNcomment:��������ʼ������,����HI_SVR_SMOOTHSTREAMING_PARAM_S
\param[out] phPlayer handle of the created player. CNcomment:�����Ĳ��������

\retval ::HI_SUCCESS A player is created successfully and the player handle is valid. CNcomment:�����ɹ��������������Ч
\retval ::HI_FAILURE A player fails to be created. The parameters are invalid or resources are insufficient. CNcomment:����ʧ�ܣ������Ƿ�����Դ����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Create(HI_SVR_SMOOTHSTREAMING_PARAM_S *pstruParam, HI_HANDLE *phPlayer);

/**
\brief Destroy a player instance. CNcomment:����һ��������ʵ��
\attention \n
The HI_S32 HI_SMOOTHSTREAMING_Destroy interface is called to destroy the player resource after the ::HI_SMOOTHSTREAMING_Create interface is called to create a player.
CNcomment:����::HI_SMOOTHSTREAMING_Create�����������󣬵��øýӿ����ٲ�������Դ
\param[in] hPlayer player handle. CNcomment:���������

\retval ::HI_SUCCESS The player is released successfully. CNcomment:�������ͷųɹ�
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Destroy(HI_HANDLE hPlayer);

/**
\brief Open a smooth streaming media presentation. CNcomment:��һ��smooth streamingý��
\attention \n
The HI_S32 HI_SMOOTHSTREAMING_Open interface is called to open one smooth streaming presentation, must be called after the ::HI_SMOOTHSTREAMING_Create.
CNcomment:Ҫ����HI_SMOOTHSTREAMING_Open�ӿڣ������ȵ���HI_SMOOTHSTREAMING_Create����������ʵ��
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pstruMedia:Ҫ�򿪵�ý���URL������ģʽ,Ŀǰ����ģʽֻ֧����������ģʽ����������������ģʽ

\retval ::HI_SUCCESS The media is opened successfully.
\retval ::HI_FAILURE The media open failed.
CNcomment:ͬ���ӿڣ�����ֵHI_SUCCESS��ʾopen�ɹ�, HI_FAILURE��ʾʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Open(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIA_S* pstruMedia);

/**
\brief Start playing. CNcomment:��ʼ����
\attention \n
This interface is an asynchronous interface. It must be called after the ::HI_SMOOTHSTREAMING_Open interface is called. \n
Values returned by this interface cannot be used to check whether the playing is successful. The player notifies the APP of playing success using  \n
CNcomment:�첽�ӿڣ��ýӿڱ����ڵ���::HI_SMOOTHSTREAMING_Open�ӿں���ã����ųɹ����ٵ��øýӿڷ���HI_FAILURE��\n
����ͨ���ýӿڷ���ֵ���жϲ������Ƿ񲥷ųɹ�����Ҫͨ����ѯ������״̬ȷ�ϣ������ǰ������״̬��HI_SVR_SMOOTHSTREAMING_STATE_PLAYING����play�ɹ�\n
��ʧ�ܽ�ͨ���ɽӿ�HI_SMOOTHSTREAMING_RegistErrCbע��Ļص�����֪ͨ��
ֹͣ���ź󣬿��Ե��øýӿ����²���

\param[in] hPlayer player handle. CNcomment:���������

\retval ::HI_SUCCESS The operation is valid. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Play(HI_HANDLE hPlayer);

/**
\brief Stop playing. CNcomment:ֹͣ����
\attention \n
This interface is an asynchronous interface. It can be called to stop playing during playing, fast forward, rewind, and pause. Values returned by this interface cannot be used to check whether playing is stopped successfully. \n
The ::HI_SMOOTHSTREAMING_Play interface can be called to restart playing after playing is stopped.

CNcomment:�첽�ӿڣ����š���������ˡ���ͣ�����ж����Ե��øýӿ�ֹͣ���ţ�����ͨ���ýӿڷ���ֵ���жϲ�����\n
�Ƿ�ֹͣ�ɹ�����Ҫͨ����ѯ������״̬ȷ�ϣ������ǰ������״̬��HI_SMOOTHSTREAMING_STATE_TUNING����stop�ɹ�\n
ֹͣ���ź󣬿��Ե���::HI_SMOOTHSTREAMING_Play�ӿ����²���

\param[in] hPlayer player handle. CNcomment:���������

\retval ::HI_SUCCESS The operation is valid. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Stop(HI_HANDLE hPlayer);

/**
\brief Pause playing. CNcomment:��ͣ����
\attention \n
This interface is an asynchronous interface. It can be called to pause playing during playing, fast forward, rewind, and pause.
But during trick mode play(fast forward, rewind), pause will cancel trick play, set player back to normal playing and adjust speed to normal speed.
Values returned by this interface cannot be used to check whether playing is paused successfully. \n
The ::HI_SMOOTHSTREAMING_Play interface can be called to restart playing after playing is stopped.

CNcomment:�첽�ӿڣ����š���������ˡ���ͣ�����ж����Ե��øýӿ�ֹͣ���ţ����ڿ�����˵Ĺ�������ͣ��ȡ���������,\n
����HI_SMOOTHSTREAMING_Resume���ص���������ģʽ���ܼ���������˲��š�����ͨ���ýӿڷ���ֵ���жϲ�����\n
�Ƿ���ͣ�ɹ�����Ҫͨ����ѯ������״̬ȷ�ϣ������ǰ������״̬��HI_SVR_SMOOTHSTREAMING_STATE_PAUSED����pause�ɹ�\n
��ͣ���ź󣬿��Ե���::HI_SMOOTHSTREAMING_Resume�ӿڻָ�����

\param[in] hPlayer player handle. CNcomment:���������

\retval ::HI_SUCCESS The operation is valid. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Pause(HI_HANDLE hPlayer);

/**
\brief Resume playing. CNcomment:�ָ���������
\attention \n
This interface is an asynchronous interface. It can be called to resume playing after calling HI_SMOOTHSTREAM_Pause or HI_SMOOTHSTREAMING_TPlay, \n
Values returned by this interface cannot be used to check whether playing is resumed successfully.

CNcomment:�첽�ӿڣ�����HI_SMOOTHSTREAMING_Pause��ͣ���Ż��ߵ���HI_SMOOTHSTREAMING_TPlay���п�����˲��Ų����󣬿��Ե��ô˽ӿڻָ��������ţ�\n
����ͨ���ýӿڷ���ֵ���жϲ������Ƿ�ָ��ɹ�����Ҫͨ����ѯ������״̬ȷ�ϣ������ǰ������״̬��HI_SVR_SMOOTHSTREAMING_STATE_PLAYING����resume�ɹ�\n

\param[in] hPlayer player handle. CNcomment:���������

\retval ::HI_SUCCESS The operation is valid. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Resume(HI_HANDLE hPlayer);

/**
\brief Fast forward and rewind. CNcomment:���������
\attention \n
This interface is an asynchronous interface. It must be called after the ::HI_SMOOTHSTREAMING_Play interface is called.\n
The ::HI_SMOOTHSTREAMING_Resume interface can be called to \n
resume normal playing after fast forward or rewind.
CNcomment:�첽�ӿڣ��ú����������::HI_SMOOTHSTREAMING_Play����ã�����ͨ���ýӿ�\n
����ֵ���ж��Ƿ�������˳ɹ�,��������˺�ͨ������::HI_SMOOTHSTREAMING_Resume\n
�ӿڻָ��������š�

\param[in] hPlayer player handle. CNcomment:���������
\param[in] eSpeed playing speed. The value is HI_SVR_SMOOTHSTREAMING_SPEED_E. CNcomment:���ű���,ֵΪHI_SVR_SMOOTHSTREAMING_SPEED_E

\retval ::HI_SUCCESS The operation is valid. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_TPlay(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_SPEED_E eSpeed);

/**
\brief Seek to a specified location for playing. CNcomment:����ָ��λ�ò���
\attention \n
This interface is an asynchronous interface. It must be called after the ::HI_SMOOTHSTREAMING_Open interface is called. It can be called to jump to a specified time point for playing.
CNcomment:�첽�ӿڣ��ýӿڱ����ڵ���::HI_SMOOTHSTREAMING_Open�ӿں���ã����øýӿ�����ָ��ʱ��㲥��

\param[in] hPlayer player handle. CNcomment:���������
\param[in] s64Sec seeking time. The unit is seconds. CNcomment:seekʱ�䣬��λ��

\retval ::HI_SUCCESS The operation is successful. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Seek(HI_HANDLE hPlayer, HI_S64 s64Sec);

/**
\brief Extended Interface.
\attention \n
��
\param[in] hPlayer player handle. CNcomment:���������
\param[in] u32InvokeId  command of the operation, value is ::hiSVR_SMOOTHSTREAMING_INVOKE_ID_E.
\param [in] pArg parameter of the command

\retval ::HI_SUCCESS The operation is successful. CNcomment:�Ϸ�����
\retval ::HI_FAILURE The operation is invalid. CNcomment:�Ƿ�����

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_Invoke(HI_HANDLE hPlayer, HI_U32 u32InvokeId, HI_VOID *pArg);

/**
\brief Obtain information about the current player running information,
CNcomment:��ȡ��ǰ������״̬��Ϣ
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Open interface is called.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Open�ӿں����

\param[in] hPlayer player handle. CNcomment:���������
\param[out] pstruInfo obtained file information. CNcomment:��ȡ�Ĳ�����״̬��Ϣ

\retval ::HI_SUCCESS The file information is obtained successfully. CNcomment:��ȡ��������״̬��Ϣ
\retval ::HI_FAILURE The file information fails to be obtained. CNcomment:��ȡ������״̬��Ϣʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetPlayerInfo(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_RUNNING_INFO_S* pstruRunningInfo);

/**
\brief Obtain information about the current open file, such as the file size, playing duration, file bit rate, video width, video height, coding format, frame rate, video bit rate, audio encoding, and audio bit rate.
CNcomment:��ȡ��ǰ���ļ���Ϣ�����Ƿ�Ϊֱ��������ʱ������ʼ����ʱ�䡢������Ϣ��CNend
\attention \n
This interface must be called after the ::HI_SVR_SMOOTHSTREAMING_Open interface is called.
CNcomment:�ú��������ڵ���::HI_SVR_SMOOTHSTREAMING_Open�ӿں����CNend

\param[in] hPlayer player handle. CNcomment:���������CNend
\param[out] pMediaInfo obtained file information. CNcomment:��ȡ���ļ���ϢCNend

\retval ::HI_SUCCESS The file information is obtained successfully. CNcomment:��ȡ���ļ���ϢCNend
\retval ::HI_FAILURE The file information fails to be obtained. CNcomment:��ȡ�ļ���Ϣʧ��CNend

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetMediaInfo(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S *pMediaInfo);


/**
\brief Register a player error callback function. CNcomment:ע�Ქ���������¼��ص�����
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Create�ӿں���ã��ú���������player�κλص��¼��е���
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pfnErrCb player error callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_ERROR_FN. CNcomment:�����������¼��ص��������ص���������::HI_SMOOTHSTREAM_ERROR_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:ע��ɹ�
\retval ::HI_FAILURE The registration fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistErrCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ERROR_FN pfnErrCb);

/**
\brief Register a player error callback function. CNcomment:ע�Ქ����ý��׼���ûص�����, mediareadyָ�Ѿ���ȡ��ý�������ļ�����ȷ�������ѻ�ȡ��ý�������Ϣ
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Create�ӿں���ã��ú���������player�κλص��¼��е���
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pfnMediaReadyCb player error callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN.
CNcomment:������mediaready�ص��������ص���������::HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:ע��ɹ�
\retval ::HI_FAILURE The registration fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistMediaReadyCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN pfnMediaReadyCb);

/**
\brief Register a player event callback function. CNcomment:ע�Ქ����״̬�����¼��Ļص�����\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Create�ӿں���ã��ú���������player�κλص��¼��е���
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pfnEventCb player error callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_STATE_FN.
CNcomment:������״̬�����¼��ص��������ص���������::HI_SVR_SMOOTHSTREAMING_STATE_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:ע��ɹ�
\retval ::HI_FAILURE The registration fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistStateEventCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_STATE_FN pfnStateCb);

/**
\brief Register a player event callback function. CNcomment:ע�Ქ������ִ�����¼��Ļص�����\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called. This function cannot be called in any player callback event.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Create�ӿں���ã��ú���������player�κλص��¼��е���
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pfnCommandCb player command done callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_CMD_FN.
CNcomment:��������������ִ����ص��������ص���������::HI_SVR_SMOOTHSTREAMING_CMD_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:ע��ɹ�
\retval ::HI_FAILURE The registration fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistCmdCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_CMD_FN pfnCommandCb);

/**
\brief Register subtitle data callback function. CNcomment:ע�Ქ�����ݻص�����\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Create�ӿں���á�
\param[in] hPlayer player handle. CNcomment:���������
\param[in] pfnSubCb subtitle data callback function. The callback function definition is ::HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN.
CNcomment:pfnSubCbΪ��Ļ���ݻص��������ص���������::HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN

\retval ::HI_SUCCESS The registration is successful. CNcomment:ע��ɹ�
\retval ::HI_FAILURE The registration fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_RegistSubCb(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_SUB_DATA_FN pfnSubCb);

/**
\brief force a quality level(biterate level). CNcomment:ֹͣsmooth streaming������������Զ�ѡ��ͬ���ʵĹ��ܣ�ǿ��ѡ��һ�����ʲ���\n
\attention \n
This interface must be called after the ::HI_SMOOTHSTREAMING_Create interface is called.
CNcomment:�ú��������ڵ���::HI_SMOOTHSTREAMING_Create�ӿں����
\param[in] hPlayer player handle. CNcomment:���������
\param[in] s32TrackIdx��ǿ��ָ����track��������������ӦHI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S::HI_SVR_SMOOTHSTREAMING_VID_TRACK_INFO_S::s32TrackIdx
CNcomment:�û����Ը�����ע���HI_SVR_SMOOTHSTREAMING_MEDIAREADY_FN���ص�HI_SVR_SMOOTHSTREAMING_MEDIA_INFO_S�е�ý����Ϣ,\n
�õ�ÿ��track��Ӧ��bitrate����Ӧ��s32TrackIdx, Ȼ����������������ѡ��.

\retval ::HI_SUCCESS The operation is successful. CNcomment:���óɹ�
\retval ::HI_FAILURE The operation fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_ForceQualityLevel(HI_HANDLE hPlayer, HI_S32 s32TrackIdx);

/**
\brief obtain player parameters. CNcomment:��ȡ����������
\attention \n
CNcomment:The following operations are supported:
HI_SVR_SMOOTHSTREAMING_ATTR_AVPLAYER_HDL:used to abtain current avplayer handle.
HI_SVR_SMOOTHSTREAMING_ATTR_WINDOW_HDL:used to abtain current window handle.
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING: used to abtain cache timing setting.
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING: used to abtain http setting.

CNcomment:֧�ֵĲ�������
HI_SVR_SMOOTHSTREAMING_ATTR_AVPLAYER_HDL:���ڻ�ȡavplayer�ľ��.
HI_SVR_SMOOTHSTREAMING_ATTR_WINDOW_HDL:���ڻ�ȡ���Ŵ���window�ľ��.
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING: ���ڻ�ȡ����ʱ��Ĳ���.
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING: ���ڻ�ȡhttp������õĲ���.

\param[in] hPlayer player handle. CNcomment:���������
\param[in] eAttrId ID of the player parameter to be set. CNcomment:Ҫ��ȡ�Ĳ���������ID
\param[out] pArg player parameter to be set. CNcomment:��ȡ���Ĳ���������

\retval ::HI_SUCCESS Parameters are set successfully. CNcomment:������ȡ�ɹ�
\retval ::HI_FAILURE The operation fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_GetParam(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ATTR_E eAttrId, HI_VOID* pArg);

/**
\brief Set player parameters. CNcomment:���ò���������
\attention \n
CNcomment:The following operations are supported:
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING, used to set media data cache timing.
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING, used to set http param.
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_PATH, used to specify DRM certificate path and license store path
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_DOMAIN, used to set DRM domain information

CNcomment:֧�ֵĲ�������
HI_SVR_SMOOTHSTREAMING_ATTR_CACHE_TIMING, ��������ý�����ݻ����ʱ��
HI_SVR_SMOOTHSTREAMING_ATTR_HTTP_SETTING, ��������http��ز��������糬ʱʱ��������ʧ������������
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_PATH, ��������DRM֤�鼰���֤�����·��
HI_SVR_SMOOTHSTREAMING_ATTR_DRM_DOMAIN, ��������DRM����Ϣ

\param[in] hPlayer player handle. CNcomment:���������
\param[in] eAttrId ID of the player parameter to be set. CNcomment:Ҫ���õĲ���������ID
\param[in] pArg player parameter to be set. CNcomment:Ҫ���õĲ���������

\retval ::HI_SUCCESS Parameters are set successfully. CNcomment:�������óɹ�
\retval ::HI_FAILURE The operation fails. CNcomment:����ʧ��

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_SetParam(HI_HANDLE hPlayer, HI_SVR_SMOOTHSTREAMING_ATTR_E eAttrId, HI_VOID* pArg);

#ifdef __cplusplus
}
#endif
#endif
