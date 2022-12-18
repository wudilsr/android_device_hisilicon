#define LOG_NDEBUG 0
#define LOG_TAG "HiMediaPlayer"

#include <cutils/properties.h>

#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_hdmi.h"
#include "hi_mpi_disp.h"
#include "hi_svr_player.h"
#include "hi_svr_metadata.h"
#include "hi_svr_charset.h"
#include "hi_svr_charset_norm.h"
#include "hi_audio_codec.h"

#include "HiMediaDefine.h"
#include "HiMetadata.h"
#include "HiMediaPlayerInvoke.h"
#include "HiMediaSystem.h"
#include "HiMediaLogger.h"
#include "HiMediaPlayer.h"

#include "DisplayClient.h"
#include "hidisplay.h"
#include "hi_unf_vo.h"

#define STR_SWITCH_PG  "SWITCH-PG "
#define HiKeyID3Pic "APIC"
#define NET_CACHE_UNDERRUN 1

namespace android {

static const status_t ERROR_NOT_OPEN = -1;
static const status_t ERROR_OPEN_FAILED = -2;
static const status_t ERROR_ALLOCATE_FAILED = -4;
static const status_t ERROR_NOT_SUPPORTED = -8;
static const status_t ERROR_NOT_READY = -16;
static const status_t ERROR_TIMEOUT = -32;
static const status_t STATE_ERROR_INITDEVICE = 0;
static const status_t STATE_ERROR_INITPLAYER = 1;
static const status_t STATE_ERROR = 2;
static const status_t STATE_INIT = 3;
static const status_t STATE_PREPARE = 4;
static const status_t STATE_PLAY = 5;
static const status_t STATE_STOPPING = 6;
static const status_t STATE_STOPPED = 7;

Mutex HiMediaPlayer::mInstMutex;
Mutex HiMediaPlayer::mCreateAvplayMutex;
AvPlayInstances HiMediaPlayer::mAVPlayInstances;
HI_S32 HiMediaPlayer::mSoundIdFlags = 0;
KeyedVector<HI_HANDLE, HiMediaPlayer*>  HiMediaPlayer::mInstances;
int HiMediaPlayer::mBuffering = BUFFERING_IDLE;

static status_t pushBlankBuffersToNativeWindow(const sp<ANativeWindow> &mNativeWindow);

#define AUDIO_BUFF_SIZE         (2 * 1024 * 1024)
#define VIDEO_BUFF_SIZE         (4 * 1024 * 1024)
#define WAITE_TIME              (50 * 1000) //50ms
#define WAITE_MAX_TIME          (3000) //3s
#define WAITE_COUNT             (30)
#define NORMAL_STR_LEN          (PROP_VALUE_MAX)
#define BENCH_MARK_TIME         1
#define DESTRUCT_RELEASE_WAIT   (200 * 1000)
// value define of output the substream of truehd
#define TRUEHD_AC3_SUB          0
#define SOUND_INVALID_PORTID    -1
#define SUB_DEFAULT_FRAME_PACK  (-1)
#define MAKE_ELEMENT(x)         { x, #x }

//100 ms,sub display accuracy which is android cts demanded
#define ANDROID_CTS_SUB_TOLERANCE 100
#define SUBTITLE_SYNC_TIMEOUT     1000
#define WASU_SEEK_MAX_DAYS        604800000 // 7days
#define IS_MMS_URL(member) \
    ( \
    NULL != member && \
    ( \
    NULL != strstr(member,"mms://") \
    || NULL != strstr(member,"mmst://") \
    || NULL != strstr(member,"mmsu://") \
    || NULL != strstr(member,"mmsh://") \
    ) \
    )

#define IS_RTMP_URL(member) \
    ( \
    NULL != member && \
    ( \
    NULL != strstr(member,"rtmp://") \
    || NULL != strstr(member,"rtmpe://") \
    || NULL != strstr(member,"rtmps://") \
    || NULL != strstr(member,"rtmpt://") \
    || NULL != strstr(member,"rtmpte://") \
    ) \
    )
#define SUB_GET_ITEM(func, fmt...) \
    do{ \
        int ret = func;  \
        if (HI_SUCCESS != ret)  \
        {  \
            LOGE("%s:%d call %s fail, ret is %d", __FUNCTION__, __LINE__, #func, ret); \
            if(NULL != reply ){   \
                reply->writeInt32(ret);  \
            }   \
            return HI_FAILURE;  \
         }   \
         if(NULL != reply ){   \
             reply->writeInt32(ret);   \
         }    \
    }while(0)

#define SUB_POST_BUFFER(func, fmt...) \
    do{ \
        if(NULL == mPlayer) { \
            if(NULL != reply ){   \
                reply->writeInt32(-1);   \
            }    \
            return s32Ret;  \
        } \
        if( mPlayer->getSubManager()->getInitialized() == false){ /*check is initial*/\
            if(NULL != reply ){   \
                reply->writeInt32(-1);   \
            }    \
            return s32Ret;  \
        }  \
        HI_S32 mIsDisableSubtitle; \
        mPlayer->getSubManager()->getDisableSubtitle(mIsDisableSubtitle); \
        if( mIsDisableSubtitle > 0 ){ /*check is initial*/\
            if(NULL != reply ){   \
                reply->writeInt32(-1);   \
            } \
            return s32Ret;  \
        } \
        HI_S32 ret = func; \
        /* mPlayer->getSubManager()->clearLastBuffer(); */ \
        ret |= mPlayer->getSubManager()->postBuffer(subManager::TYPE_DRAW); \
        if(  NULL != reply){  \
            reply->writeInt32( ret );   \
        }        \
    }while(0)

/* add for iptv */
typedef enum element_apk_type_e
{
    APP_TYPE_WASU = 0x0,
    APP_TYPE_BESTTV,
    APP_TYPE_ICNTV,
    APP_TYPE_BUTT
};
/* iptv end */

typedef struct element_array_t
{
    HI_U32                state;
    const HI_CHAR *       strings;
} element_array_t;

class HiMediaLooper : public Thread
{
    friend class LooperHandler;
public:
    HiMediaLooper() : mExitRequested(0) {
        mLooper = new Looper(true);
        run("HiMediaLooper", PRIORITY_BACKGROUND);

        LOGV("looper init done");
    }
    ~HiMediaLooper() {
        LOGV("looper deinit done");
    }

    status_t postMessage(const sp<MessageHandler>& handler,
            const Message& msg, nsecs_t relTime) {
        if (relTime > 0) {
            mLooper->sendMessageDelayed(relTime, handler, msg);
        } else {
            mLooper->sendMessage(handler, msg);
        }
        return OK;
    }
private:
    void waitMessage() {
        while (!mExitRequested) {
            int32_t ret = mLooper->pollOnce(-1);
            switch (ret) {
                case ALOOPER_POLL_WAKE:
                    LOGE("ALOOPER_POLL_WAKE");
                case ALOOPER_POLL_CALLBACK:
    //                LOGD("ALOOPER_POLL_CALLBACK");
                    continue;
                case ALOOPER_POLL_ERROR:
                    LOGE("ALOOPER_POLL_ERROR");
                    break;
                case ALOOPER_POLL_TIMEOUT:
                    LOGE("ALOOPER_POLL_TIMEOUT");
                    break;
                default:
                    LOGE("Looper::pollOnce() returned unknown status %d", ret);
                    break;
            }
        }
    }
    virtual bool threadLoop() {
        LOGV("thread loop enter");
        waitMessage();
        LOGV("thread loop leave");
        return OK;
    }

private:
    sp<Looper> mLooper;
    int mExitRequested;
};

class LooperHandler : public MessageHandler {
public:

    enum {
        MSG_SEND_BUFFERING_START = 0x1,
        MSG_SEND_BUFFERING_END,
        MSG_REMOVE_BUFFERING_START,
        MSG_EXIT,
    };

    LooperHandler(sp<HiMediaLooper>& looper, HiMediaPlayer* player) :
        mLooper(looper), mPlayer(player) { }
    virtual void handleMessage(const Message& message) {
        switch (message.what) {
        case MSG_SEND_BUFFERING_START:
            {
                mPlayer->mSendBufEventLock.lock();
                if (HiMediaPlayer::BUFFERING_NOT_ENOUGH != mPlayer->getBuffering())
                {
                    mPlayer->setBuffering(HiMediaPlayer::BUFFERING_NOT_ENOUGH);
                    mPlayer->bUnderrunOutside = true;
                    LOGV("handle send event 701");
                    mPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_START, 0);
                    mPlayer->writeLog(HiMediaPlayer::MEDIA_LOG_BUFFER_START, HiMediaPlayer::MEDIA_LOG_LEVEL_INFO, NULL);
                }
                mPlayer->mSendBufEventLock.unlock();
            }
            break;
        case MSG_SEND_BUFFERING_END:
            {
                mPlayer->mSendBufEventLock.lock();
                if (mPlayer->bUnderrunOutside == true && HiMediaPlayer::BUFFERING_ENOUGH != mPlayer->getBuffering())
                {
                    LOGV("handle send event 702");
                    mPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_END, 0);
                    mPlayer->setBuffering(HiMediaPlayer::BUFFERING_ENOUGH);
                    mPlayer->writeLog(HiMediaPlayer::MEDIA_LOG_BUFFER_END, HiMediaPlayer::MEDIA_LOG_LEVEL_INFO, NULL);
                }
                else
                {
                    LOGV("do not need send event 702");
                }
                mPlayer->bUnderrunOutside = false;
                mPlayer->mSendBufEventLock.unlock();
            }
            break;
        case MSG_REMOVE_BUFFERING_START:
            {
                ALOGD("handle remove event 701");
                mLooper->mLooper->removeMessages(this, MSG_SEND_BUFFERING_START);
            }
            break;
        case MSG_EXIT:
            ALOGD("handle send event MSG_EXIT");
            mLooper->mExitRequested = true;
            break;
        default:
            ALOGD("unsupport msg:%d", message.what);
            break;
        }
    }
private:
    sp<HiMediaLooper> mLooper;
    HiMediaPlayer* mPlayer;
};

static const element_array_t s_state_array[] =
{
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_INIT),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_DEINIT),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_PLAY),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_FORWARD),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_BACKWARD),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_PAUSE),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_STOP),
    MAKE_ELEMENT(HI_SVR_PLAYER_STATE_BUTT),
};

static HI_U32 getCurrentTime()
{
    struct timeval tv;

    if (0 == gettimeofday(&tv, NULL))
    {
        return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
    }

    return -1;
}

/* for command queue Async callback start */
static int prepareAsyncComplete(status_t status, void *cookie, bool cancelled)
{
    LOGV("[%s] Call %s IN", STR_SWITCH_PG, __FUNCTION__);

    if (true == ((HiMediaPlayer::CommandQueue*)cookie)->getPlayer()->mReset)
    {
        LOGV("Player is reseting, not send event ");
        return NO_ERROR;
    }

    if (status == NO_ERROR)
    {
        LOGV("HiMediaPlayer::prepareAsyncComplete, go to prepare_l");
        ((HiMediaPlayer::CommandQueue*)cookie)->getPlayer()->prepare_l(status, cancelled);
    }
    else
    {
        LOGV("HiMediaPlayer::prepareAsyncComplete, send Error");
        ((HiMediaPlayer::CommandQueue*)cookie)->getPlayer()->sendEvent(MEDIA_ERROR, MEDIA_ERROR_UNKNOWN, 0);
    }

    return NO_ERROR;
}

int   HiMediaPlayer::getDiagnose(void)
{
    LOGV("mDiagnose status = %d", mDiagnose);
    return mDiagnose;
}

static const HI_CHAR *PLAYER_GetAudFormatName(HI_U32 u32Format)
{
    switch (u32Format)
    {
    case HI_FORMAT_AUDIO_MP2:
        return "MP2";
        break;
    case HI_FORMAT_AUDIO_MP3:
        return "MP3";
        break;
    case HI_FORMAT_AUDIO_AAC:
        return "AAC";
        break;
    case HI_FORMAT_AUDIO_AC3:
        return "AC3";
        break;
    case HI_FORMAT_AUDIO_DTS:
        return "DTS";
        break;
    case HI_FORMAT_AUDIO_VORBIS:
        return "VORBIS";
        break;
    case HI_FORMAT_AUDIO_DVAUDIO:
        return "DVAUDIO";
        break;
    case HI_FORMAT_AUDIO_WMAV1:
        return "WMAV1";
        break;
    case HI_FORMAT_AUDIO_WMAV2:
        return "WMAV2";
        break;
    case HI_FORMAT_AUDIO_MACE3:
        return "MACE3";
        break;
    case HI_FORMAT_AUDIO_MACE6:
        return "MACE6";
        break;
    case HI_FORMAT_AUDIO_VMDAUDIO:
        return "VMDAUDIO";
        break;
    case HI_FORMAT_AUDIO_SONIC:
        return "SONIC";
        break;
    case HI_FORMAT_AUDIO_SONIC_LS:
        return "SONIC_LS";
        break;
    case HI_FORMAT_AUDIO_FLAC:
        return "FLAC";
        break;
    case HI_FORMAT_AUDIO_MP3ADU:
        return "MP3ADU";
        break;
    case HI_FORMAT_AUDIO_MP3ON4:
        return "MP3ON4";
        break;
    case HI_FORMAT_AUDIO_SHORTEN:
        return "SHORTEN";
        break;
    case HI_FORMAT_AUDIO_ALAC:
        return "ALAC";
        break;
    case HI_FORMAT_AUDIO_WESTWOOD_SND1:
        return "WESTWOOD_SND1";
        break;
    case HI_FORMAT_AUDIO_GSM:
        return "GSM";
        break;
    case HI_FORMAT_AUDIO_QDM2:
        return "QDM2";
        break;
    case HI_FORMAT_AUDIO_COOK:
        return "COOK";
        break;
    case HI_FORMAT_AUDIO_TRUESPEECH:
        return "TRUESPEECH";
        break;
    case HI_FORMAT_AUDIO_TTA:
        return "TTA";
        break;
    case HI_FORMAT_AUDIO_SMACKAUDIO:
        return "SMACKAUDIO";
        break;
    case HI_FORMAT_AUDIO_QCELP:
        return "QCELP";
        break;
    case HI_FORMAT_AUDIO_WAVPACK:
        return "WAVPACK";
        break;
    case HI_FORMAT_AUDIO_DSICINAUDIO:
        return "DSICINAUDIO";
        break;
    case HI_FORMAT_AUDIO_IMC:
        return "IMC";
        break;
    case HI_FORMAT_AUDIO_MUSEPACK7:
        return "MUSEPACK7";
        break;
    case HI_FORMAT_AUDIO_MLP:
        return "MLP";
        break;
    case HI_FORMAT_AUDIO_GSM_MS:
        return "GSM_MS";
        break;
    case HI_FORMAT_AUDIO_ATRAC3:
        return "ATRAC3";
        break;
    case HI_FORMAT_AUDIO_VOXWARE:
        return "VOXWARE";
        break;
    case HI_FORMAT_AUDIO_APE:
        return "APE";
        break;
    case HI_FORMAT_AUDIO_NELLYMOSER:
        return "NELLYMOSER";
        break;
    case HI_FORMAT_AUDIO_MUSEPACK8:
        return "MUSEPACK8";
        break;
    case HI_FORMAT_AUDIO_SPEEX:
        return "SPEEX";
        break;
    case HI_FORMAT_AUDIO_WMAVOICE:
        return "WMAVOICE";
        break;
    case HI_FORMAT_AUDIO_WMAPRO:
        return "WMAPRO";
        break;
    case HI_FORMAT_AUDIO_WMALOSSLESS:
        return "WMALOSSLESS";
        break;
    case HI_FORMAT_AUDIO_ATRAC3P:
        return "ATRAC3P";
        break;
    case HI_FORMAT_AUDIO_EAC3:
        return "EAC3";
        break;
    case HI_FORMAT_AUDIO_SIPR:
        return "SIPR";
        break;
    case HI_FORMAT_AUDIO_MP1:
        return "MP1";
        break;
    case HI_FORMAT_AUDIO_TWINVQ:
        return "TWINVQ";
        break;
    case HI_FORMAT_AUDIO_TRUEHD:
        return "TRUEHD";
        break;
    case HI_FORMAT_AUDIO_MP4ALS:
        return "MP4ALS";
        break;
    case HI_FORMAT_AUDIO_ATRAC1:
        return "ATRAC1";
        break;
    case HI_FORMAT_AUDIO_BINKAUDIO_RDFT:
        return "BINKAUDIO_RDFT";
        break;
    case HI_FORMAT_AUDIO_BINKAUDIO_DCT:
        return "BINKAUDIO_DCT";
        break;
    case HI_FORMAT_AUDIO_DRA:
        return "DRA";
        break;
    case HI_FORMAT_AUDIO_PCM:
        return "PCM";
        break;
    case HI_FORMAT_AUDIO_PCM_BLURAY:
        return "PCM_BLURAY";
        break;
    case HI_FORMAT_AUDIO_ADPCM:
        return "ADPCM";
        break;
    case HI_FORMAT_AUDIO_AMR_NB:
        return "AMR_NB";
        break;
    case HI_FORMAT_AUDIO_AMR_WB:
        return "AMR_WB";
        break;
    case HI_FORMAT_AUDIO_AMR_AWB:
        return "AMR_AWB";
        break;
    case HI_FORMAT_AUDIO_RA_144:
        return "RA_144";
        break;
    case HI_FORMAT_AUDIO_RA_288:
        return "RA_288";
        break;
    case HI_FORMAT_AUDIO_DPCM:
        return "DPCM";
        break;
    case HI_FORMAT_AUDIO_G711:
        return "G711";
        break;
    case HI_FORMAT_AUDIO_G722:
        return "G722";
        break;
    case HI_FORMAT_AUDIO_G7231:
        return "G7231";
        break;
    case HI_FORMAT_AUDIO_G726:
        return "G726";
        break;
    case HI_FORMAT_AUDIO_G728:
        return "G728";
        break;
    case HI_FORMAT_AUDIO_G729AB:
        return "G729AB";
        break;
    case HI_FORMAT_AUDIO_MULTI:
        return "MULTI";
        break;
    case HI_FORMAT_AUDIO_BUTT:
    default:
        return "UNKNOW";
        break;
    }

    return "UNKNOW";
}

static const HI_CHAR *PLAYER_GetVidFormatName(HI_U32 u32Format)
{
    switch (u32Format)
    {
    case HI_FORMAT_VIDEO_MPEG2:
        return "MPEG2";
        break;
    case HI_FORMAT_VIDEO_MPEG4:
        return "MPEG4";
        break;
    case HI_FORMAT_VIDEO_AVS:
        return "AVS";
        break;
    case HI_FORMAT_VIDEO_H263:
        return "H263";
        break;
    case HI_FORMAT_VIDEO_H264:
        return "H264";
        break;
    case HI_FORMAT_VIDEO_HEVC:
        return "HEVC";
        break;
    case HI_FORMAT_VIDEO_REAL8:
        return "REAL8";
        break;
    case HI_FORMAT_VIDEO_REAL9:
        return "REAL9";
        break;
    case HI_FORMAT_VIDEO_VC1:
        return "VC1";
        break;
    case HI_FORMAT_VIDEO_VP6:
        return "VP6";
        break;
    case HI_FORMAT_VIDEO_VP6F:
        return "VP6F";
        break;
    case HI_FORMAT_VIDEO_VP6A:
        return "VP6A";
        break;
    case HI_FORMAT_VIDEO_MJPEG:
        return "MJPEG";
        break;
    case HI_FORMAT_VIDEO_SORENSON:
        return "SORENSON";
        break;
    case HI_FORMAT_VIDEO_DIVX3:
        return "DIVX3";
        break;
    case HI_FORMAT_VIDEO_RAW:
        return "RAW";
        break;
    case HI_FORMAT_VIDEO_JPEG:
        return "JPEG";
        break;
    case HI_FORMAT_VIDEO_VP8:
        return "VP8";
        break;
    case HI_FORMAT_VIDEO_MSMPEG4V1:
        return "MSMPEG4V1";
        break;
    case HI_FORMAT_VIDEO_MSMPEG4V2:
        return "MSMPEG4V2";
        break;
    case HI_FORMAT_VIDEO_MSVIDEO1:
        return "MSVIDEO1";
        break;
    case HI_FORMAT_VIDEO_WMV1:
        return "WMV1";
        break;
    case HI_FORMAT_VIDEO_WMV2:
        return "WMV2";
        break;
    case HI_FORMAT_VIDEO_RV10:
        return "RV10";
        break;
    case HI_FORMAT_VIDEO_RV20:
        return "RV20";
        break;
    case HI_FORMAT_VIDEO_SVQ1:
        return "SVQ1";
        break;
    case HI_FORMAT_VIDEO_SVQ3:
        return "SVQ3";
        break;
    case HI_FORMAT_VIDEO_H261:
        return "H261";
        break;
    case HI_FORMAT_VIDEO_VP3:
        return "VP3";
        break;
    case HI_FORMAT_VIDEO_VP5:
        return "VP5";
        break;
    case HI_FORMAT_VIDEO_CINEPAK:
        return "CINEPAK";
        break;
    case HI_FORMAT_VIDEO_INDEO2:
        return "INDEO2";
        break;
    case HI_FORMAT_VIDEO_INDEO3:
        return "INDEO3";
        break;
    case HI_FORMAT_VIDEO_INDEO4:
        return "INDEO4";
        break;
    case HI_FORMAT_VIDEO_INDEO5:
        return "INDEO5";
        break;
    case HI_FORMAT_VIDEO_MJPEGB:
        return "MJPEGB";
        break;
    case HI_FORMAT_VIDEO_MVC:
        return "MVC";
        break;
    case HI_FORMAT_VIDEO_DV:
        return "DV";
        break;
    case HI_FORMAT_VIDEO_BUTT:
    default:
        return "UNKNOW";
        break;
    }

    return "UNKNOW";
}

status_t HiMediaPlayer::writeLog(MediaLogType log_type, MediaLogLevel log_level, HI_VOID * pArg)
{
    status_t ret;
    HI_S32 len = 0, size = 0;
    char description[8192];
    time_t secsSince1970;
    struct tm timeinfo = {0};
    HI_CHAR buffer [64] = {0};
    HI_S32 s32Ret = 0;

    if (!mDiagnose)
    {
        return NO_ERROR;
    }

    Mutex::Autolock l(mWriteLogLock);

    if (mLogger == NULL)
    {
        LOGE("Logger is not created yet");
        return UNKNOWN_ERROR;
    }

    if (!mDiagnose)
    {
        return NO_ERROR;
    }

    LOGV("start to write log, log_type:%d", log_type);

    /* [year-month-day hour:minute:second] */
    time(&secsSince1970);
    localtime_r(&secsSince1970, &timeinfo);
    strftime(buffer, sizeof(buffer), "%F %T", &timeinfo);
    size = sizeof(description);
    len += snprintf(description + len, size - len, "[%s]", buffer);
    if (len >= size)
        goto write_log;

    /* [log level] */
    switch(log_level)
    {
        case MEDIA_LOG_LEVEL_FATAL:
        {
            len += snprintf(description + len, size - len, "[fatal]");
            break;
        }
        case MEDIA_LOG_LEVEL_ERROR:
        {
            len += snprintf(description + len, size - len, "[error]");
            break;
        }
        case MEDIA_LOG_LEVEL_INFO:
        {
            len += snprintf(description + len, size - len, "[info]");
            break;
        }
        case MEDIA_LOG_LEVEL_DEBUG:
        default:
        {
            len += snprintf(description + len, size - len, "[debug]");
            break;
        }
    }
    if (len >= size)
        goto write_log;

    /* [module function line] */
    len += snprintf(description + len, size - len,"[HiMediaPlayer %s %d] ", __FUNCTION__, __LINE__);
    if (len >= size)
        goto write_log;

    /* details */
    switch(log_type)
    {
        case MEDIA_LOG_BUFFER_START:
        {
            HI_FORMAT_BUFFER_STATUS_S stBufStatus;
            HI_FORMAT_BUFFER_CONFIG_S stBufConfig;
            HI_S64 s64Size = 0, s64Duration = 0;

            s64BufferingSystemTime = getCurrentTime();

            len += snprintf(description + len, size - len, "buffering start, need buffer data");
            if (len >= size)
                goto write_log;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_STATUS, &stBufStatus);
            if (s32Ret == HI_SUCCESS)
            {
                stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_SIZE;
                s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, &stBufConfig);
                if (s32Ret == HI_SUCCESS)
                {
                    s64Size = stBufConfig.s64EventEnough > stBufStatus.s64BufferSize ? stBufConfig.s64EventEnough - stBufStatus.s64BufferSize : 0;
                    len += snprintf(description + len, size - len, " size: %lldB", s64Size);
                }

                stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_TIME;
                s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, &stBufConfig);
                if (s32Ret == HI_SUCCESS)
                {
                    s64Duration = stBufConfig.s64EventEnough > stBufStatus.s64Duration ? stBufConfig.s64EventEnough - stBufStatus.s64Duration : 0;
                    len += snprintf(description + len, size - len, " time: %lld ms", s64Duration);
                }
            }

            break;
        }
        case MEDIA_LOG_BUFFER_END:
        {
            len += snprintf(description + len, size - len, "buffering end, lasting time: %lldms", s64BufferingSystemTime != 0 ? getCurrentTime() - s64BufferingSystemTime : 0);
            s64BufferingSystemTime = 0;

            break;
        }
        case MEDIA_LOG_SEGMENT_DOWNLOAD_START:
        {
            HI_FORMAT_MSG_DATA_S *pstData = NULL;
            HI_FORMAT_MSG_TS_SEGMENT_START_S *pstSegInfo = NULL;
            HI_S32 *num = NULL;
            if (pArg != NULL)
            {
                pstData = (HI_FORMAT_MSG_DATA_S *)pArg;
                if (pstData->pData != NULL)
                {
                    pstSegInfo = (HI_FORMAT_MSG_TS_SEGMENT_START_S *)pstData->pData;
                }
            }

            if (NULL == pstSegInfo)
            {
                return NO_ERROR;
            }

            len += snprintf(description + len, size - len, "ts segment download is start, number: %d, filesize: %lldB, duration: %dms",
                    pstSegInfo->s32Sequence, pstSegInfo->s64Filesize, pstSegInfo->s32Duration);

            break;
        }
        case MEDIA_LOG_SEGMENT_DOWNLOAD_END:
        {
            HI_FORMAT_MSG_DATA_S *pstData = NULL;
            HI_FORMAT_MSG_TS_SEGMENT_END_S *pstSegInfo = NULL;
            HI_S64 s32Offset = 0;
            HI_U64 u64SpendTime = 0;
            HI_S32 s32BandWidth = 0;

            if (pArg != NULL)
            {
                pstData = (HI_FORMAT_MSG_DATA_S *)pArg;
                if (pstData->pData != NULL)
                {
                    pstSegInfo = (HI_FORMAT_MSG_TS_SEGMENT_END_S *)pstData->pData;
                }
            }

            if (NULL == pstSegInfo)
            {
                return NO_ERROR;
            }

            len += snprintf(description + len, size - len, "ts segment download is complete, recvsize:%lldB, spend time: %llums, rate: %dbps",
                    pstSegInfo->s64Offset, pstSegInfo->u64SpendTime, pstSegInfo->s32BandWidth);

            break;
        }
        case MEDIA_LOG_LIVE_MODE:
        {
            len += snprintf(description + len, size - len, "convert to live");

            break;
        }
        case MEDIA_LOG_IPTV_MODE:
        {
            len += snprintf(description + len, size - len, "convert to iptv");

            break;
        }
        case MEDIA_LOG_SET_DATA_SOURCE:
        {
            HI_CHAR *url = NULL;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            url = (HI_CHAR *)pArg;

            len += snprintf(description + len, size - len, "setDataSource, url:%s", url);

            break;
        }
        case MEDIA_LOG_CREATE_NEW_PLAYER:
        {
            HI_S32 *ps32Index = 0;

            if (MEDIA_LOG_LEVEL_FATAL == log_level)
            {
                len += snprintf(description + len, size - len, "create a new player fail");
            }
            else
            {
                if (NULL == pArg)
                {
                    return NO_ERROR;
                }

                ps32Index = (HI_S32 *)pArg;
                len += snprintf(description + len, size - len, "create a new player %d", *ps32Index);
            }
            break;
        }
        case MEDIA_LOG_SET_VIDEO_SURFACE_TEXTURE:
        {
            len += snprintf(description + len, size - len, "setVideoSurfaceTexture");

            break;
        }
        case MEDIA_LOG_PREPARE_ASYNC:
        {
            u32PrepareAsyncSystemTime = getCurrentTime();
            len += snprintf(description + len, size - len, "prepareAysnc start");

            break;
        }
        case MEDIA_LOG_PREPARED:
        {
            HI_U32 u32PreparedTime = 0;

            u32PreparedTime = getCurrentTime();

            if (MEDIA_LOG_LEVEL_ERROR == log_level)
            {
                len += snprintf(description + len, size - len, "prepareAsync fail");
            }
            else
            {
                len += snprintf(description + len, size - len, "prepareAsync is compeleted, spend time: %ums", u32PrepareAsyncSystemTime != 0 ? (u32PreparedTime - u32PrepareAsyncSystemTime) : 0);
            }

            break;
        }
        case MEDIA_LOG_STREAM_INFO:
        {
            HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            pstFileInfo = (HI_FORMAT_FILE_INFO_S *)pArg;
            if (HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType)
            {
                len += snprintf(description + len, size - len, "playmode:live, duration: %lldms", pstFileInfo->s64Duration);
            }
            else if (HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType)
            {
                len += snprintf(description + len, size - len, "playmode:vod, duration: %lldms", pstFileInfo->s64Duration);
            }
            else
            {
                len += snprintf(description + len, size - len, "playmode:local, duration: %lldms", pstFileInfo->s64Duration);
            }

            break;
        }
        case MEDIA_LOG_VIDEO_SIZE:
        {
            HI_UNF_NORMCHANGE_PARAM_S * pstParam = NULL;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            pstParam = (HI_UNF_NORMCHANGE_PARAM_S *)pArg;

            len += snprintf(description + len, size - len, "Video frame width: %u, height: %u", pstParam->u32ImageWidth, pstParam->u32ImageHeight);

            break;
        }
        case MEDIA_LOG_CONNECT_CODE:
        {
            HI_S32 s32HttpCode = 0;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            s32HttpCode = (HI_S32)pArg;

            len += snprintf(description + len, size - len, "http status code: %d", s32HttpCode);

            break;
        }
        case MEDIA_LOG_CONNECT_REDIRECT:
        {
            HI_CHAR *pStr = NULL;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            pStr = (HI_CHAR *)pArg;

            len += snprintf(description + len, size - len, "Redirect url: %s", pStr);

            break;
        }
        case MEDIA_LOG_CONNECTED:
        {
            HI_S32 s32SpendTime = 0;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            s32SpendTime = *(HI_S32 *)pArg;

            len += snprintf(description + len, size - len, "Connect server OK, spend time: %dms", s32SpendTime/1000);

            break;
        }
        case MEDIA_LOG_STREAM_CODEC:
        {
            HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
            const HI_CHAR *pVideoCodec = NULL;
            const HI_CHAR *pAudioCodec = NULL;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            pstFileInfo = (HI_FORMAT_FILE_INFO_S *)pArg;

            if (pstFileInfo->u32ProgramNum > 0)
            {
                if (pstFileInfo->pastProgramInfo[0].u32VidStreamNum > 0)
                {
                    pVideoCodec = PLAYER_GetVidFormatName(pstFileInfo->pastProgramInfo[0].pastVidStream[0].u32Format);
                }

                if (pstFileInfo->pastProgramInfo[0].u32AudStreamNum > 0)
                {
                    pAudioCodec = PLAYER_GetAudFormatName(pstFileInfo->pastProgramInfo[0].pastAudStream[0].u32Format);
                }
            }

            if (pVideoCodec)
            {
                len += snprintf(description + len, size - len, "Video codec: %s", pVideoCodec);
            }

            if (pAudioCodec)
            {
                if (pVideoCodec)
                {
                    len += snprintf(description + len, size - len, ", ");
                }

                len += snprintf(description + len, size - len, "Audio codec: %s", pAudioCodec);
            }

            break;
        }
        case MEDIA_LOG_START:
        {
            len += snprintf(description + len, size - len, "start");

            break;
        }
        case MEDIA_LOG_FIRST_FRAME:
        {
            HI_U32 u32Time = 0;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            u32Time = *(HI_U32 *)pArg;

            len += snprintf(description + len, size - len, "show the first video frame, spend time: %ums", u32Time);

            break;
        }
        case MEDIA_LOG_PAUSE:
        {
            len += snprintf(description + len, size - len, "pause");

            break;
        }
        case MEDIA_LOG_SEEK_TO:
        {
            HI_S32 s32Time = 0;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            s32Time = *(HI_S32 *)pArg;

            len += snprintf(description + len, size - len, "seekTo, totime:%dms", s32Time);

            break;
        }
        case MEDIA_LOG_SEEK_COMPLETE:
        {
            len += snprintf(description + len, size - len, "seek is compeleted");

            break;
        }
        case MEDIA_LOG_STOP:
        {
            len += snprintf(description + len, size - len, "stop");

            break;
        }
        case MEDIA_LOG_RESET:
        {
            len += snprintf(description + len, size - len, "reset");

            break;
        }
        case MEDIA_LOG_DESTROY:
        {
            HI_S32 s32Index = 0;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            s32Index = *(HI_S32 *)pArg;

            len += snprintf(description + len, size - len, "destroy this player, index %d", s32Index);

            break;
        }
        case MEDIA_LOG_CURRENT_PLAY_TIME:
        {
            HI_S32 s32Time = 0;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            s32Time = *(HI_S32 *)pArg;

            len += snprintf(description + len, size - len, "current playtime: %dms", s32Time);

            break;
        }
        case MEDIA_LOG_PLAY_COMPLETE:
        {
            len += snprintf(description + len, size - len, "stream is end");

            break;
        }
        case MEDIA_LOG_ERROR:
        {
            HI_CHAR *pEvent = NULL;

            if (NULL == pArg)
            {
                return NO_ERROR;
            }

            pEvent = (HI_CHAR *)pArg;

            len += snprintf(description + len, size - len, "Error happened, event: %s", pEvent);

            break;
        }
        default:
        {
            len += snprintf(description + len, size - len, "desc:sorry, no description of this error message");

            break;
        }
    }

    if (len >= size)
        goto write_log;

    len += snprintf(description + len, size - len, "\r\n");

write_log:

    ret = mLogger->writeLog(description);
    LOGV("finish to write log:");
    LOGV("%s", description);

    return ret;
}

static int do_nothing(status_t status, void *cookie, bool cancelled)
{
    return 0;
}
/* for command queue Async callback end */

/* static */
int HiMediaPlayer::hiPlayerEventCallback(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_S *pstruEvent)
{
    HiMediaPlayer* pHiPlayer = NULL;
    HI_SVR_PLAYER_STATE_E eEventBk = HI_SVR_PLAYER_STATE_BUTT;
    HI_SVR_PLAYER_STREAMID_S *pstSreamId = NULL;
    HI_HANDLE hWindow = (HI_HANDLE)NULL;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32Time = 0;
    HI_U32 *pu32Progress = NULL;

    if (NULL == hPlayer || NULL == pstruEvent)
    {
        return HI_SUCCESS;
    }

    {
        Mutex::Autolock mLock(&HiMediaPlayer::mInstMutex);
        const ssize_t i = HiMediaPlayer::mInstances.indexOfKey(hPlayer);

        if (i >= 0)
        {
            pHiPlayer = (HiMediaPlayer*)HiMediaPlayer::mInstances.valueAt(i);

            if (pHiPlayer == NULL || NULL == pHiPlayer->mCmdQueue.get())
            {
                LOGW("There is no HiMediaPlayer instance at index [%ld]", i);
                return HI_SUCCESS;
            }
        }
        else
        {
            LOGW("Can not find a valid HiMediaPlayer associate with handle[%d]", hPlayer);
            return HI_SUCCESS;
        }
    }

    switch(pstruEvent->eEvent)
    {
        case HI_SVR_PLAYER_EVENT_TS_SEGMENT_DOWNLOAD_START:
        {
            LOGV("HI_SVR_PLAYER_EVENT_TS_SEGMENT_DOWNLOAD_START\n");
            if (NULL == pstruEvent->pu8Data)
            {
                break;
            }

            HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;
            pHiPlayer->writeLog(MEDIA_LOG_SEGMENT_DOWNLOAD_START, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)pstData);

            break;
        }
        case HI_SVR_PLAYER_EVENT_TS_SEGMENT_DOWNLOAD_END:
        {
            LOGV("HI_SVR_PLAYER_EVENT_TS_SEGMENT_DOWNLOAD_END\n");
            if (NULL == pstruEvent->pu8Data)
            {
                break;
            }

            HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;
            pHiPlayer->writeLog(MEDIA_LOG_SEGMENT_DOWNLOAD_END, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)pstData);

            break;
        }
        case HI_SVR_PLAYER_EVENT_HTTP_REDIRECT:
        {
            LOGV("HI_SVR_PLAYER_EVENT_HTTP_REDIRECT\n");
            if (NULL == pstruEvent->pu8Data)
            {
                break;
            }

            HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;
            pHiPlayer->writeLog(MEDIA_LOG_CONNECT_REDIRECT, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)pstData->pData);

            break;
        }
        case HI_SVR_PLAYER_EVENT_HTTP_CONNECTED:
        {
            LOGV("HI_SVR_PLAYER_EVENT_HTTP_CONNECTED\n");

            if (NULL == pstruEvent->pu8Data)
            {
                break;
            }

            HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;
            pHiPlayer->writeLog(MEDIA_LOG_CONNECTED, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)&pstData->s32Param1);

            break;
        }
        case HI_SVR_PLAYER_EVENT_DOWNLOAD_START:
            {
                if (NULL == pstruEvent->pu8Data)
                {
                    LOGV("HI_SVR_PLAYER_EVENT_DOWNLOAD_START\n");
                    break;
                }

                HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;
                LOGV("Receive Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_START, param1(seg_index):%d", pstData->s32Param1);
                if (pHiPlayer->getDiagnose())
                {
                    LOGV("send Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_START, param1(seg_index):%d", pstData->s32Param1);
                    pHiPlayer->sendEvent(android::MEDIA_INFO, MEDIA_INFO_DOWNLOAD_START, pstData->s32Param1);
                }
            }
            break;
        case HI_SVR_PLAYER_EVENT_DOWNLOAD_END:
            {
                if (NULL == pstruEvent->pu8Data)
                {
                    LOGV("HI_SVR_PLAYER_EVENT_DOWNLOAD_END\n");
                    break;
                }

                HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;
                LOGV("Receive Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_END ,param1(consume_ms):%d", pstData->s32Param1);
                if (pHiPlayer->getDiagnose())
                {
                    LOGV("send Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_END ,param1(consume_ms):%d", pstData->s32Param1);
                    pHiPlayer->sendEvent(android::MEDIA_INFO, MEDIA_INFO_DOWNLOAD_END, pstData->s32Param1);
                }
            }
            break;
        case HI_SVR_PLAYER_EVENT_DOWNLOAD_ERROR:
            {
                if (NULL == pstruEvent->pu8Data)
                {
                    LOGV("HI_SVR_PLAYER_EVENT_DOWNLOAD_ERROR\n");
                    break;
                }

                HI_FORMAT_MSG_DATA_S *pstData = (HI_FORMAT_MSG_DATA_S*)pstruEvent->pu8Data;

                LOGV("Receive Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_ERROR ,param1(http_code):%d, seg_url:%s",
                        pstData->s32Param1, (char *)pstData->pData);
                if (pHiPlayer->getDiagnose())
                {
                    LOGV("send Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_ERROR ,param1(http_code):%d, seg_url:%s",
                            pstData->s32Param1, (char *)pstData->pData);
                    pHiPlayer->sendEvent(android::MEDIA_INFO, MEDIA_INFO_DOWNLOAD_ERROR, pstData->s32Param1);
                }
            }
            break;
        case HI_SVR_PLAYER_EVENT_STATE_CHANGED:
        {
            eEventBk = (HI_SVR_PLAYER_STATE_E)*pstruEvent->pu8Data;
            LOGV("[%s] Receive Event: HI_SVR_PLAYER_EVENT_STATE State [%s(%d)]",
                STR_SWITCH_PG, s_state_array[eEventBk].strings, eEventBk);

            switch (eEventBk)
            {
                case HI_SVR_PLAYER_STATE_INIT:
                    {
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_IDLE);
                    }
                    break;
                case HI_SVR_PLAYER_STATE_DEINIT:
                    {
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_DESTROY);
                    }
                    break;
                case HI_SVR_PLAYER_STATE_PLAY:
                    {
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_PLAY);
                        pHiPlayer->mCmdQueue->signal();
                    }
                    break;
                case HI_SVR_PLAYER_STATE_PAUSE:
                    {
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_PAUSE);
                        pHiPlayer->mCmdQueue->signal();
                    }
                    break;
                case HI_SVR_PLAYER_STATE_STOP:
                    {
                            /* add for iptv */
                            HI_CHAR value[1024] = {0};
                            memset(value, 0, 1024);
                            HI_S32 s32AppType = APP_TYPE_BUTT;

                            /* client.apk.name
                               1. wasu.app
                               2. besttv.app
                               3. icntv.app
                               set apk.name by using "setprop client.apk.name wasu.app" command.
                             */

                            if (property_get("client.apk.name", value, NULL) > 0)
                            {
                                LOGW("Stop callback, property_get value = %s \n", value);

                                if (!strncmp(value, "wasu.app", 8))
                                {
                                    s32AppType = APP_TYPE_WASU;
                                    LOGW("Stop callback, check application is wasu apk");
                                }
                            }
                            /* iptv end */

                        HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hWindow);
                        if (HI_UNF_WINDOW_FREEZE_MODE_BUTT != pHiPlayer->mWndFreezeMode && APP_TYPE_WASU != s32AppType)
                        {
                            if (HI_INVALID_HANDLE != hWindow)
                                HI_UNF_VO_ResetWindow(hWindow, pHiPlayer->mWndFreezeMode);
                        }
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_STOP);
                        pHiPlayer->mCmdQueue->signal();
                    }
                    break;
                case HI_SVR_PLAYER_STATE_FORWARD:
                    {
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_FWD);
                        pHiPlayer->mCmdQueue->signal();
                    }
                    break;
                case HI_SVR_PLAYER_STATE_BACKWARD:
                    {
                        pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_REW);
                        pHiPlayer->mCmdQueue->signal();
                    }
                    break;
                case HI_SVR_PLAYER_STATE_BUTT:
                    break;
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_SOF:
        {
            LOGV("Receive Event: HI_SVR_PLAYER_EVENT_SOF ");

            eEventBk = (HI_SVR_PLAYER_STATE_E)*pstruEvent->pu8Data;

            if (HI_SVR_PLAYER_STATE_BACKWARD == eEventBk)
            {
                HI_SVR_PLAYER_Play(hPlayer);
                LOGV("Send event MEDIA_FAST_BACKWORD_COMPLETE");
                pHiPlayer->sendEvent(android::MEDIA_FAST_BACKWORD_COMPLETE);
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_EOF:
        {
            LOGV("Receive Event: HI_SVR_PLAYER_EVENT_EOF ");

            pHiPlayer->writeLog(MEDIA_LOG_PLAY_COMPLETE, MEDIA_LOG_LEVEL_INFO, NULL);

            //because hiplayer will call stop func inter, when EOF
            pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_STOP);

            HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hWindow);

            if (HI_UNF_WINDOW_FREEZE_MODE_BUTT != pHiPlayer->mWndFreezeMode)
            {
                if (HI_INVALID_HANDLE != hWindow)
                    HI_UNF_VO_ResetWindow(hWindow, pHiPlayer->mWndFreezeMode);
            }

            if (pHiPlayer->mLoop)
            {
                LOGV("mLoop!=false,replay");
                pHiPlayer->mCmdQueue->enqueueCommand(new CommandStart(hPlayer, do_nothing));
            }
            else
            {
                LOGV("NOT LOOPING, send event MEDIA_PLAYBACK_COMPLETE");
                pHiPlayer->sendEvent(android::MEDIA_PLAYBACK_COMPLETE);
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_PROGRESS:
        {
            HI_SVR_PLAYER_PROGRESS_S *pstProgress = NULL;
            pstProgress = (HI_SVR_PLAYER_PROGRESS_S*)pstruEvent->pu8Data;

            if (NULL != pstProgress)
            {
                LOGV("Receive Event: Current play progress is %d ", pstProgress->u32Progress);
            }

            char soft_detector[PROPERTY_VALUE_MAX] = {0};
            if (property_get("persist.sys.softdetector.enable", soft_detector, "false") && strcmp("true", soft_detector)== 0)
            {
                HI_FORMAT_BUFFER_STATUS_S stStatus;
                HI_SVR_PLAYER_Invoke(pHiPlayer->mHandle, HI_FORMAT_INVOKE_GET_BUFFER_STATUS, (HI_VOID *)&stStatus);
                LOGV("Receive Event: Current play progress s64Duration = %d ", stStatus.s64Duration);
                pHiPlayer->sendEvent(android::MEDIA_INFO, MEDIA_INFO_EXTEND_BUFFER_LENGTH, stStatus.s64Duration);
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_STREAMID_CHANGED:
        {
            LOGV("Receive Event: HI_SVR_PLAYER_EVENT_STREAMID_CHANGED ");
            pHiPlayer->mCmdQueue->signal();
            pstSreamId = (HI_SVR_PLAYER_STREAMID_S*)pstruEvent->pu8Data;

            if (NULL != pstSreamId)
            {
                LOGV("Stream id change to: ProgramId %d, vid %d, aid %d, sid %d ",
                        pstSreamId->u16ProgramId,
                        pstSreamId->u16VidStreamId,
                        pstSreamId->u16AudStreamId,
                        pstSreamId->u16SubStreamId);
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_SEEK_FINISHED:
        {
            LOGV("NOT LOOPING, send event MEDIA_SEEK_COMPLETE");

            pHiPlayer->writeLog(MEDIA_LOG_SEEK_COMPLETE, MEDIA_LOG_LEVEL_INFO, NULL);

            HI_FORMAT_FILE_INFO_S *pstruInfo = NULL;
            HI_SVR_PLAYER_STREAMID_S stid;

            if (pHiPlayer->mLooper != NULL)
            {
                const Message msg_buffer_start((int)(LooperHandler::MSG_REMOVE_BUFFERING_START));
                LOGV("remove message 701 pHiPlayer:%p",pHiPlayer);
                pHiPlayer->mLooper->postMessage(pHiPlayer->mLooperHandle, msg_buffer_start, 0);

                const Message msg_buffer_end((int)(LooperHandler::MSG_SEND_BUFFERING_END));
                LOGV("post message 702 pHiPlayer:%p",pHiPlayer);
                pHiPlayer->mLooper->postMessage(pHiPlayer->mLooperHandle, msg_buffer_end, 0);
            }

            s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID *)&stid);
            if (HI_SUCCESS == s32Ret)
            {
                s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstruInfo);
                if (HI_SUCCESS == s32Ret && stid.u16ProgramId < pstruInfo->u32ProgramNum)
                {
                    if (0 < pstruInfo->pastProgramInfo[stid.u16ProgramId].u32SubStreamNum)
                    {
                        LOGV("clear sub buffer");
                        pHiPlayer->getSubManager()->postBuffer(subManager::TYPE_CLEAR);
                    }
                }
            }

            pHiPlayer->sendEvent(android::MEDIA_SEEK_COMPLETE);
        }
        break;
        case HI_SVR_PLAYER_EVENT_DOWNLOAD_PROGRESS:
        {
            HI_SVR_PLAYER_PROGRESS_S *pstProgress = NULL;

            if (NULL != pstruEvent->pu8Data)
            {
                pstProgress = (HI_SVR_PLAYER_PROGRESS_S *)pstruEvent->pu8Data;

                if (pstProgress->u32Progress <= 100)
                {
                    LOGV("Receive Event: HI_SVR_PLAYER_EVENT_DOWNLOAD_PROGRESS, download progress is %d ", pstProgress->u32Progress);
                    pHiPlayer->sendEvent(android::MEDIA_BUFFERING_UPDATE, pstProgress->u32Progress);
                }
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_FIRST_FRAME_TIME:
        {
            if (NULL == pstruEvent->pu8Data)
            {
                return HI_SUCCESS;
            }

            u32Time = *(HI_U32*)pstruEvent->pu8Data;

            LOGV("[%s] Send MEDIA_INFO_FIRST_FRAME_TIME event, time:%d ",
                STR_SWITCH_PG, u32Time);
            pHiPlayer->writeLog(MEDIA_LOG_FIRST_FRAME, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)(&u32Time));
            pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_FIRST_FRAME_TIME, u32Time);
            pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_RENDERING_START, u32Time);
            char soft_detector[PROPERTY_VALUE_MAX] = {0};
            if (property_get("persist.sys.softdetector.enable", soft_detector, "false") && strcmp("true", soft_detector)== 0)
            {
                HI_S64 streamNum = 0;
                HI_S64 bandwidth = 0;
                if (HI_SUCCESS ==  HI_SVR_PLAYER_Invoke(pHiPlayer->mHandle, HI_FORMAT_INVOKE_GET_HLS_STREAM_NUM, (HI_VOID *)&streamNum)){
                    if (1 == streamNum) {
                        s32Ret = HI_SVR_PLAYER_Invoke(pHiPlayer->mHandle, CMD_GET_HLS_BANDWIDTH, (HI_VOID *)&bandwidth);
                    } else {
                        bandwidth = -1;
                    }
                } else {
                    bandwidth = pHiPlayer->mpFileInfo->u32Bitrate;
                }
                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_EXTEND_FIRST_FRAME_TIME, bandwidth);
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_DOWNLOAD_FINISH:
        {
            LOGV("Send MEDIA_INFO_BUFFER_DOWNLOAD_FIN event, File download finish ");
            pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFER_DOWNLOAD_FIN, 0);
#if NET_CACHE_UNDERRUN
                if (pHiPlayer->getDiagnose())
                {
                    pHiPlayer->mSendBufEventLock.lock();
                    if (pHiPlayer->mBufEventControl == BUF_EVENT_SEND)
                    {
                        if (BUFFERING_NOT_ENOUGH == pHiPlayer->getBuffering())
                        {
                            LOGV("Download finish,send MEDIA_INFO_BUFFERING_END");
                            pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_END, 0);
                            pHiPlayer->setBuffering(BUFFERING_ENOUGH);
                            pHiPlayer->writeLog(MEDIA_LOG_BUFFER_END, MEDIA_LOG_LEVEL_INFO, NULL);
                        }
                    }
                    else
                        LOGV("Download finish,but current state do not allow send buffering end");
                    pHiPlayer->mSendBufEventLock.unlock();
                }
#endif
        }
        break;
        case HI_SVR_PLAYER_EVENT_BUFFER_STATE:
        {
            if (NULL == pstruEvent->pu8Data)
            {
                return HI_SUCCESS;
            }

            LOGV("Receive Event: HI_SVR_PLAYER_EVENT_BUFFER_STATE ");

            HI_SVR_PLAYER_BUFFER_S *pstBufStat = (HI_SVR_PLAYER_BUFFER_S *)pstruEvent->pu8Data;

            if (HI_SVR_PLAYER_BUFFER_EMPTY == pstBufStat->eType)
            {
                LOGV("Send MEDIA_INFO_BUFFER_EMPTY event ");
                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFER_EMPTY, 0);
#if NET_CACHE_UNDERRUN
                    if (pHiPlayer->getDiagnose())
                    {
                        LOGV("receive buffer empty,send MEDIA_INFO_BUFFERING_START");
                                    pHiPlayer->mSendBufEventLock.lock();
                        pHiPlayer->bUnderrunOutside = false;
                        if (pHiPlayer->mBufEventControl == BUF_EVENT_SEND)
                        {
                            if (BUFFERING_ENOUGH == pHiPlayer->getBuffering())
                            {
                                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_START, 0);
                                pHiPlayer->setBuffering(BUFFERING_NOT_ENOUGH);
                                pHiPlayer->writeLog(MEDIA_LOG_BUFFER_START, MEDIA_LOG_LEVEL_INFO, NULL);
                            }
                        }
                        else
                            LOGV("get empty buf event,but current state do not allow send buffering end");
                        pHiPlayer->mSendBufEventLock.unlock();
                    }
                #endif
            }
            else if (HI_SVR_PLAYER_BUFFER_START == pstBufStat->eType)
            {
                LOGV("Send MEDIA_INFO_BUFFER_START event ");
                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFER_START, 0);
#if NET_CACHE_UNDERRUN
                    if (pHiPlayer->getDiagnose())
                    {
                        pHiPlayer->mSendBufEventLock.lock();
                        pHiPlayer->bUnderrunOutside = false;
                        if (pHiPlayer->mBufEventControl == BUF_EVENT_SEND)
                        {
                            if (BUFFERING_ENOUGH == pHiPlayer->getBuffering())
                            {
                                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_START, 0);
                                pHiPlayer->setBuffering(BUFFERING_NOT_ENOUGH);
                                pHiPlayer->writeLog(MEDIA_LOG_BUFFER_START, MEDIA_LOG_LEVEL_INFO, NULL);
                            }
                        }
                        else
                            LOGV("get start buf event,but current state do not allow send buffering end");
                        pHiPlayer->mSendBufEventLock.unlock();
                    }
                #endif
            }
            else if (HI_SVR_PLAYER_BUFFER_ENOUGH == pstBufStat->eType)
            {
                LOGV("Send MEDIA_INFO_BUFFER_ENOUGH event ");
                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFER_ENOUGH, 0);
#if NET_CACHE_UNDERRUN
                    if (pHiPlayer->getDiagnose())
                    {
                        pHiPlayer->mSendBufEventLock.lock();
                        if (pHiPlayer->mBufEventControl == BUF_EVENT_SEND)
                        {
                            if (BUFFERING_NOT_ENOUGH == pHiPlayer->getBuffering())
                            {
                                LOGV("get buffer enough event,send MEDIA_INFO_BUFFERING_END");
                                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_END, 0);
                                pHiPlayer->setBuffering(BUFFERING_ENOUGH);
                                pHiPlayer->writeLog(MEDIA_LOG_BUFFER_END, MEDIA_LOG_LEVEL_INFO, NULL);
                            }
                        }
                        else
                            LOGV("get buffer enough event,but current state do not allow send buffering end");
                        pHiPlayer->mSendBufEventLock.unlock();
                    }
                #endif
            }
            else if (HI_SVR_PLAYER_BUFFER_FULL == pstBufStat->eType)
            {
                LOGV("Send MEDIA_INFO_BUFFER_FULL event ");
                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFER_FULL, 0);
                #if NET_CACHE_UNDERRUN
                    if (pHiPlayer->getDiagnose())
                    {
                        pHiPlayer->mSendBufEventLock.lock();
                        if (pHiPlayer->mBufEventControl == BUF_EVENT_SEND)
                        {
                            if (BUFFERING_NOT_ENOUGH == pHiPlayer->getBuffering())
                            {
                                LOGV("receive buffer full,send MEDIA_INFO_BUFFERING_END");
                                                            pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_END, 0);
                                pHiPlayer->setBuffering(BUFFERING_ENOUGH);
                                pHiPlayer->writeLog(MEDIA_LOG_BUFFER_END, MEDIA_LOG_LEVEL_INFO, NULL);
                            }
                        }
                        else
                            LOGV("get buffer full event,but current state do not allow send buffering end");
                        pHiPlayer->mSendBufEventLock.unlock();
                    }
                #endif
            }
            else
            {
                LOGV("HI_SVR_PLAYER_EVENT_BUFFER unknow bufferType:%d ", pstBufStat->eType);
            }
        }
        break;
        case HI_SVR_PLAYER_EVENT_NETWORK_INFO:
        {
            if (NULL == pstruEvent->pu8Data)
            {
                LOGV("HI_SVR_PLAYER_EVNET_NETWORK\n");
                break;
            }

            LOGV("Receive Event: HI_SVR_PLAYER_EVENT_NETWORK_INFO ");

            HI_FORMAT_NET_STATUS_S *pstNet = (HI_FORMAT_NET_STATUS_S*)pstruEvent->pu8Data;

            switch (pstNet->eType)
            {
            case HI_FORMAT_MSG_NETWORK_ERROR_UNKNOW:
                LOGV("Unknow network erro ");
                break;
            case HI_FORMAT_MSG_NETWORK_ERROR_CONNECT_FAILED:
                LOGV("Connect server fail ");
                break;
            case HI_FORMAT_MSG_NETWORK_ERROR_TIMEOUT:
                LOGV("Request timeout ");
                break;
            case HI_FORMAT_MSG_NETWORK_ERROR_DISCONNECT:
                LOGV("Server disconnect ");
                break;
            case HI_FORMAT_MSG_NETWORK_ERROR_NOT_FOUND:
                LOGV("Media stream not found ");
                break;
            case HI_FORMAT_MSG_NETWORK_NORMAL:
                LOGV("Network resume ");
                break;
            case HI_FORMAT_MSG_NETWORK_HTTP_CODE:
            {
                LOGV("Network httpcode :%d", pstNet->s32ErrorCode);

                pHiPlayer->writeLog(MEDIA_LOG_CONNECT_CODE, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)pstNet->s32ErrorCode);

                break;
            }
            default:
                break;
            }

            LOGV("Send MEDIA_INFO_NETWORK event ");
            pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_NETWORK, pstNet->eType);
        }
        break;
        case HI_SVR_PLAYER_EVENT_ERROR:
        {
            HI_S32 err = 0;

            if (NULL != pstruEvent->pu8Data)
            {
                err = *(pstruEvent->pu8Data);
            }

            LOGV("Receive Event: HI_SVR_PLAYER_EVENT_ERROR ");

            if (err == HI_SVR_PLAYER_ERROR_PLAY_FAIL)
            {
                LOGV("Media file play fail, send MEDIA_ERROR_UNKNOWN event ");

                pHiPlayer->writeLog(MEDIA_LOG_ERROR, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)"play fail");

                if (false==pHiPlayer->mCmdQueue->mIsIPTVTimeSeeking)
                {
                    pHiPlayer->sendEvent(android::MEDIA_ERROR, android::MEDIA_ERROR_UNKNOWN, 0);
                    pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_ERROR);
                }
                pHiPlayer->mCmdQueue->signal();
            }
            else if (err == HI_SVR_PLAYER_ERROR_NOT_SUPPORT)
            {
                LOGV("Media file play fail, send MEDIA_INFO_NOT_SUPPORT event ");

                pHiPlayer->writeLog(MEDIA_LOG_ERROR, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)"not support");

                if (false==pHiPlayer->mCmdQueue->mIsIPTVTimeSeeking)
                {
                    pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_NOT_SUPPORT, 0);
                    pHiPlayer->mCmdQueue->setState(HiMediaPlayer::CommandQueue::STATE_ERROR);
                }
                pHiPlayer->mCmdQueue->signal();
            }
            else if (err == HI_SVR_PLAYER_ERROR_TIMEOUT)
            {
                LOGV("Media file play fail, send MEDIA_INFO_TIMEOUT event ");

                pHiPlayer->writeLog(MEDIA_LOG_ERROR, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)"time out");

                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_TIMEOUT, 0);
            }
            else if (err == HI_SVR_PLAYER_ERROR_AUD_PLAY_FAIL)
            {
                LOGV("Audio stream play fail, send MEDIA_INFO_AUDIO_FAIL event ");

                pHiPlayer->writeLog(MEDIA_LOG_ERROR, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)"play audio fail");

                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_AUDIO_FAIL, 0);
            }
            else if (err == HI_SVR_PLAYER_ERROR_VID_PLAY_FAIL)
            {
                LOGV("Video stream play fail, send MEDIA_INFO_VIDEO_FAIL event ");

                pHiPlayer->writeLog(MEDIA_LOG_ERROR, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)"play video fail");

                pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_VIDEO_FAIL, 0);
            }
            else
            {
                LOGV("Unknow err, send MEDIA_INFO event ");

                pHiPlayer->writeLog(MEDIA_LOG_ERROR, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)"unknown error");

                pHiPlayer->sendEvent(android::MEDIA_INFO, err, 0);
            }
        }
        break;
        default:
        {
            LOGE("Receive Event: HI_SVR_PLAYER_EVENT_BUTT or UNKOWN EVENT[%d]", pstruEvent->eEvent);
        }
        break;
    }

    return HI_SUCCESS;
}

HiMediaPlayer* HiMediaPlayer::getHiMediaPlayerByAVPlayer(HI_HANDLE hAvPlayer)
{
    HiMediaPlayer* pHiPlayer = NULL;
    size_t i = 0;

    Mutex::Autolock mLock(&HiMediaPlayer::mInstMutex);

    for (i = 0; i < HiMediaPlayer::mInstances.size(); i++)
    {
        pHiPlayer = (HiMediaPlayer*)HiMediaPlayer::mInstances.valueAt(i);

        if (pHiPlayer == NULL)
        {
            continue;
        }

        if (hAvPlayer == pHiPlayer->mAVPlayer)
        {
            LOGV("getHiMediaPlayerByAVPlayer get index[%d]",i);
            return pHiPlayer;
        }
    }

    return NULL;
}

//add for I frame error detection, valid in OrderOutput mode as follows
HI_S32 HiMediaPlayer::streamIFrameErrorCB(HI_HANDLE hAvPlayer, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 u32Para)
{
    HiMediaPlayer* pHiPlayer = NULL;

    LOGV("HiMediaPlayer::streamIFrameErrorCB IN");

    if (HI_INVALID_HANDLE == hAvPlayer || HI_UNF_AVPLAY_EVENT_IFRAME_ERR != enEvent)
    {
        LOGV("[HiMediaPlayer-IFrame]: The event can't  be deal ");
        return HI_FAILURE;
    }

    pHiPlayer = getHiMediaPlayerByAVPlayer(hAvPlayer);

    if (pHiPlayer == NULL)
    {
        LOGW("There is no HiMediaPlayer instance");
        return HI_FAILURE;
    }

    LOGE("Send MEDIA_INFO_STREM_IFRAME_ERROR event ");

    pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_STREM_IFRAME_ERROR, 0);

    LOGV("HiMediaPlayer::streamIFrameErrorCB END");
    return HI_SUCCESS;
}

//Norm Switch
HI_S32 HiMediaPlayer::streamNormSwitchCB(HI_HANDLE hAvPlayer, HI_UNF_AVPLAY_EVENT_E enEvent, HI_U32 u32Para)
{
    HiMediaPlayer* pHiPlayer = NULL;

    LOGV("HiMediaPlayer::streamNormSwitchCB IN");

    if (HI_INVALID_HANDLE == hAvPlayer || HI_UNF_AVPLAY_EVENT_NORM_SWITCH != enEvent)
    {
        LOGV("[HiMediaPlayer-NormSwitch]: The event can't  be deal ");
        return HI_FAILURE;
    }

    pHiPlayer = getHiMediaPlayerByAVPlayer(hAvPlayer);

    if (pHiPlayer == NULL)
    {
        LOGW("There is no HiMediaPlayer instance");
        return HI_FAILURE;
    }

    HI_U32 enNewWidth = ((HI_UNF_NORMCHANGE_PARAM_S *)u32Para)->u32ImageWidth;

    LOGE("Send MEDIA_INFO_STREM_NORM_SWITCH event, streamNormSwitchCB NormSwitched to %d", enNewWidth);

    pHiPlayer->writeLog(MEDIA_LOG_VIDEO_SIZE, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)u32Para);

    pHiPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_STREM_NORM_SWITCH, enNewWidth);

    LOGV("HiMediaPlayer::streamNormSwitchCB END");
    return HI_SUCCESS;
}

HiMediaPlayer::HiMediaPlayer():
            mAVPlayer(HI_INVALID_HANDLE),
            mSoHandle(HI_INVALID_HANDLE),
            mReset(false),
            mState(STATE_ERROR),
            mLoop(false),
            mHandle(HI_SVR_PLAYER_INVALID_HDL),
            mWindow(HI_INVALID_HANDLE),
            mAudioTrack(HI_INVALID_HANDLE),
            mDuration(0),
            mPosition(0),
            mPrepareAsync(false),
            mUseStaticResource(false),
            mSndPortId(SOUND_INVALID_PORTID),
            mFirstPlay(true),
            mOrigAndroidPath(false),
            mIsTimedTextTrackEnable(false),
            mTotalTrackCount(0),
            mAudioTrackCount(0),
            mVideoTrackCount(0),
            mSubtitleTrackCount(0),
            mVolumeLock(0),
            mSubFramePackType(SUB_DEFAULT_FRAME_PACK),
            mIsNotSupportByteRange(0),
#if NET_CACHE_UNDERRUN
            mBufEventControl(BUF_EVENT_SEND),
#endif

            mVSink(0),
            mASink(0),
            mNdkMode(false),
            mNonVSink(false),
            mSetdatasourcePrepare(false),
            mHasPrepared(false),
            mPrepareResult(NO_ERROR),
            bUnderrunOutside(false),
            mLooper(NULL),
            mLooperHandle(NULL)
{
    LOGV("[%s] HiMediaPlayer construct", STR_SWITCH_PG);

    mUseExtAVPlay = true;
    mstrReferer = NULL;
    mstrUserAgent = NULL;
    mState = STATE_INIT;
    mDisplayStrategy = DP_STRATEGY_ADAPT_MASK;
    memset(&mMediaParam, 0, sizeof(mMediaParam));
    mpFileInfo = NULL;
    mWndFreezeMode = HI_UNF_WINDOW_FREEZE_MODE_BLACK;
    mSubTitleNativeWindow = NULL;
    mLogger = NULL;
    mDiagnose = 0;
    LOGE("construct finish");
    char value[PROPERTY_VALUE_MAX] = {0};
    if (property_get("service.media.hiplayer.graphic", value, NULL) && !strcasecmp("true", value))
    {
        mVSink = new HiVSink(0);
    }

}

HiMediaPlayer::HiMediaPlayer(void* userData):
            mAVPlayer(HI_INVALID_HANDLE),
            mSoHandle(HI_INVALID_HANDLE),
            mReset(false),
            mState(STATE_ERROR),
            mLoop(false),
            mHandle(HI_SVR_PLAYER_INVALID_HDL),
            mWindow(HI_INVALID_HANDLE),
            mAudioTrack(HI_INVALID_HANDLE),
            mDuration(0),
            mPosition(0),
            mPrepareAsync(false),
            mUseStaticResource(false),
            mSndPortId(SOUND_INVALID_PORTID),
            mFirstPlay(true),
            mOrigAndroidPath(false),
            mIsTimedTextTrackEnable(false),
            mTotalTrackCount(0),
            mAudioTrackCount(0),
            mVideoTrackCount(0),
            mSubtitleTrackCount(0),
            mVolumeLock(0),
            mSubFramePackType(SUB_DEFAULT_FRAME_PACK),
            mIsNotSupportByteRange(0),
            #if NET_CACHE_UNDERRUN
            mBufEventControl(BUF_EVENT_SEND),
            #endif
            mVSink(0),
            mASink(0),
            mNdkMode(true),
            mNonVSink(true),
            mSetdatasourcePrepare(false),
            mHasPrepared(false),
            mPrepareResult(NO_ERROR),
            bUnderrunOutside(false),
            mLooper(NULL),
            mLooperHandle(NULL)
{
    LOGV("[%s] HiMediaPlayer construct userData", STR_SWITCH_PG);

    mUseExtAVPlay = true;
    mstrReferer = NULL;
    mstrUserAgent = NULL;
    mState = STATE_INIT;
    mDisplayStrategy = DP_STRATEGY_ADAPT_MASK;
    memset(&mMediaParam, 0, sizeof(mMediaParam));
    mpFileInfo = NULL;
    mSubTitleNativeWindow = NULL;
    mWndFreezeMode = HI_UNF_WINDOW_FREEZE_MODE_BLACK;
    mLogger = NULL;
    mDiagnose = 0;
}

status_t HiMediaPlayer::initCheck()
{
    if (mState > STATE_ERROR)
    {
        return NO_ERROR;
    }

    LOGE("HiMediaPlayer::initCheck fail");
    return ERROR_NOT_READY;
}

int HiMediaPlayer::getTrueHDSetting()
{
    HI_CHAR value[PROP_VALUE_MAX];

    if (property_get("persist.sys.audio.truehd", value, "0") > 0)
    {
        // 1--use trueHD  0---use AC3
        mTureHD = atoi(value);
    }

    LOGV("HiMediaPlayer::getTrueHDSetting %d", mTureHD);

    return mTureHD;
}

int HiMediaPlayer::createAVPlay()
{
    LOGV("create avplay begin");
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_AVPLAY_ATTR_S stAVPlayAttr;
    HI_UNF_WINDOW_ATTR_S stWinAttr;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    HI_UNF_SND_GAIN_ATTR_S stGain;
    HI_UNF_AVPLAY_OPEN_OPT_S stOpenOpt;

    mSndPortId = findValidSndPortId();

    LOGV("HI_UNF_AVPLAY_GetDefaultConfig begin");
    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAVPlayAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    LOGV("HI_UNF_AVPLAY_GetDefaultConfig end");

    stAVPlayAttr.stStreamAttr.u32VidBufSize = VIDEO_BUFF_SIZE;
    stAVPlayAttr.stStreamAttr.u32AudBufSize = AUDIO_BUFF_SIZE;
    LOGV("HI_UNF_AVPLAY_Create begin");
    s32Ret |= HI_UNF_AVPLAY_Create(&stAVPlayAttr, &mAVPlayer);
    LOGV("HI_UNF_AVPLAY_Create end");

    if (HI_SUCCESS != s32Ret)
    {
        LOGV("Create avplay fail! ");
        mAVPlayer = HI_INVALID_HANDLE;

        return HI_FAILURE;
    }

    if (NULL == mASink.get())
    {
        LOGV("No Audiosink,create audio track");
        memset(&stTrackAttr, 0, sizeof(stTrackAttr));
        stTrackAttr.enTrackType = (0 == mSndPortId) ? HI_UNF_SND_TRACK_TYPE_MASTER : HI_UNF_SND_TRACK_TYPE_SLAVE;
        char value[PROPERTY_VALUE_MAX] = {0};

        s32Ret = HI_UNF_SND_GetDefaultTrackAttr(stTrackAttr.enTrackType, &stTrackAttr);
        LOGV("HI_UNF_SND_GetDefaultTrackAttr end");

        if (HI_SUCCESS != s32Ret)
        {
            LOGV("Get default trackattr(type:%d) fail ,return 0x%x ", stTrackAttr.enTrackType, s32Ret);
        }

        //stTrackAttr.enTrackType = (0 == mSndPortId) ? HI_UNF_SND_TRACK_TYPE_MASTER : HI_UNF_SND_TRACK_TYPE_SLAVE;
        LOGV("HI_UNF_SND_CreateTrack begin");
        s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &mAudioTrack);

        if (HI_SUCCESS != s32Ret && stTrackAttr.enTrackType == HI_UNF_SND_TRACK_TYPE_MASTER)
        {
            LOGV("Create master track fail, return 0x%x. Try create slave track ", s32Ret);

            stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_SLAVE;
            s32Ret = HI_UNF_SND_GetDefaultTrackAttr(stTrackAttr.enTrackType, &stTrackAttr);
            if (HI_SUCCESS != s32Ret)
            {
                LOGV("Get default trackattr(type:%d) fail ,return 0x%x ", stTrackAttr.enTrackType, s32Ret);
            }

            s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &mAudioTrack);
        }

        if (HI_SUCCESS == s32Ret && (HI_HANDLE)HI_INVALID_HANDLE != mAudioTrack)
        {
            stGain.bLinearMode = HI_TRUE;
            stGain.s32Gain = HIMEDIA_DEFAULT_MIXWEIGHT;
            LOGV("HI_UNF_SND_SetTrackWeight begin");
            s32Ret = HI_UNF_SND_SetTrackWeight(mAudioTrack, &stGain);
            LOGV("HI_UNF_SND_SetTrackWeight end");
            if (HI_SUCCESS == s32Ret)
            {
                LOGV("HI_UNF_AVPLAY_ChnOpen aud begin");
                s32Ret = HI_UNF_AVPLAY_ChnOpen(mAVPlayer, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
                s32Ret |= HI_UNF_SND_Attach(mAudioTrack, mAVPlayer);
                LOGV("HI_UNF_AVPLAY_ChnOpen aud end");
                if (HI_SUCCESS != s32Ret)
                {
                    LOGV("Attach sound device fail! ");
                }
            }
            else
            {
                LOGV("Set sound track mixer weight failed, return 0x%x", s32Ret);
            }
        }
        else
        {
            mAudioTrack = HI_INVALID_HANDLE;
            LOGV("Create audio track fail,return 0x%x", s32Ret);
        }
    }
    stWinAttr.enDisp = HI_UNF_DISPLAY1;
    stWinAttr.bVirtual     = HI_FALSE;
    stWinAttr.stWinAspectAttr.enAspectCvrs  = HI_UNF_VO_ASPECT_CVRS_LETTERBOX;
    stWinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    stWinAttr.bUseCropRect = HI_FALSE;
    stWinAttr.stInputRect.s32X  = 0;
    stWinAttr.stInputRect.s32Y  = 0;
    stWinAttr.stInputRect.s32Width   = 0;
    stWinAttr.stInputRect.s32Height  = 0;
    stWinAttr.stOutputRect.s32X = HIMEDIA_DEFAULT_OUTPUT_X;
    stWinAttr.stOutputRect.s32Y = HIMEDIA_DEFAULT_OUTPUT_Y;

    if (true == IsUseVsinkWindow())
    {
        LOGV("Create virtual window");
        stWinAttr.bVirtual     = HI_TRUE;
        stWinAttr.enVideoFormat      = HI_UNF_FORMAT_YUV_SEMIPLANAR_420;
    }

    int w = 0;
    int h = 0;
    DisplayClient DspClient;
    DspClient.GetVirtScreenSize(&w, &h);

    stWinAttr.stOutputRect.s32Width  = w;
    stWinAttr.stOutputRect.s32Height = h;

    LOGV("HI_UNF_VO_CreateWindow begin");
    s32Ret = HI_UNF_VO_CreateWindow(&stWinAttr, &mWindow);
    LOGV("HI_UNF_VO_CreateWindow end");

    LOGV("new mWindow handle = 0x%x", mWindow);

    if (HI_SUCCESS != s32Ret)
    {
        mWindow = HI_INVALID_HANDLE;
        LOGV("Create window fail! \n");
    }

#if 0
    stOpenOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    stOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;

    LOGV("HI_UNF_AVPLAY_ChnOpen vid begin");
    s32Ret = HI_UNF_AVPLAY_ChnOpen(mAVPlayer, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stOpenOpt);
    LOGV("HI_UNF_AVPLAY_ChnOpen vid end");
    if (HI_SUCCESS != s32Ret)
    {
        LOGV("Open vid channel failed.");
    }

    LOGV("HI_UNF_VO_AttachWindow begin");
    s32Ret = HI_UNF_VO_AttachWindow(mWindow, mAVPlayer);
    LOGV("HI_UNF_VO_AttachWindow end");
    if (HI_SUCCESS != s32Ret)
    {
        LOGV("Attach window failed.");
    }
#endif
    LOGV("create avplay end");
    return HI_SUCCESS;
}

int HiMediaPlayer::destroyAVPlay()
{
    HI_S32 s32Ret = HI_SUCCESS;
    LOGV("destroyAVPlay HI_UNF_SND_Detach HI_UNF_SND_DestroyTrack begin");
    /* sound deattach */
    if ((HI_HANDLE)HI_INVALID_HANDLE != mAudioTrack)
    {
        s32Ret |= HI_UNF_SND_Detach(mAudioTrack, mAVPlayer);
        s32Ret |= HI_UNF_SND_DestroyTrack(mAudioTrack);
        mAudioTrack = (HI_HANDLE)HI_INVALID_HANDLE;
        LOGV("Detach sound device, ret = 0x%x !", s32Ret);
    }
    LOGV("destroyAVPlay HI_UNF_SND_Detach HI_UNF_SND_DestroyTrack end");

    LOGV("destroyAVPlay HI_UNF_VO_SetWindowEnable HI_UNF_VO_DetachWindow begin");
    if (HI_INVALID_HANDLE != mWindow)
    {
        s32Ret = HI_UNF_VO_SetWindowEnable(mWindow, HI_FALSE);
        s32Ret |= HI_UNF_VO_DetachWindow(mWindow, mAVPlayer);
        LOGV("Detach window, ret = 0x%x !", s32Ret);
    }
    LOGV("destroyAVPlay HI_UNF_VO_SetWindowEnable HI_UNF_VO_DetachWindow end");

    LOGV("HI_UNF_AVPLAY_ChnClose VID begin");
    s32Ret = HI_UNF_AVPLAY_ChnClose(mAVPlayer, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    LOGV("HI_UNF_AVPLAY_ChnClose VID end");
    LOGV("Close vid channel, ret = 0x%x !", s32Ret);

    LOGV("HI_UNF_AVPLAY_ChnClose AUD begin");
    s32Ret = HI_UNF_AVPLAY_ChnClose(mAVPlayer, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    LOGV("HI_UNF_AVPLAY_ChnClose AUD end");
    LOGV("Close aud channel, ret = 0x%x !", s32Ret);

    LOGV("HI_UNF_AVPLAY_Destroy begin");
    s32Ret = HI_UNF_AVPLAY_Destroy(mAVPlayer);
    mAVPlayer = (HI_HANDLE)HI_INVALID_HANDLE;
    LOGV("HI_UNF_AVPLAY_Destroy end");

    LOGV("Destroy avplay handle, ret = 0x%x !", s32Ret);

    /* destroy window */
    LOGV("HI_UNF_VO_DestroyWindow begin");
    if (HI_INVALID_HANDLE != mWindow)
    {
        s32Ret = HI_UNF_VO_DestroyWindow(mWindow);
        mWindow = (HI_HANDLE)HI_INVALID_HANDLE;
        LOGV("Destroy window, ret = 0x%x !", s32Ret);
    }
    LOGV("HI_UNF_VO_DestroyWindow end");

    return HI_SUCCESS;
}

int HiMediaPlayer::createHiplayer()
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32LogLevel = HI_FORMAT_LOG_ERROR;
    HI_SVR_PLAYER_PARAM_S struParam;

    mCmdQueue = new CommandQueue(this);
    strncpy(mCmdQueue->mszOriHuaShuUrl, mMediaParam.aszUrl, (size_t)HI_FORMAT_MAX_URL_LEN - 1);

    if (NULL == mCmdQueue.get())
    {
        LOGE("Create player,create queue fail");
        return HI_FAILURE;
    }

    s32Ret= HI_SVR_PLAYER_Init();

    if (HI_SUCCESS != s32Ret)
    {
        LOGE("HiMediaPlayer::createHiplayer init hiplayer fail");
        return s32Ret;
    }

    memset(&struParam, 0, sizeof(struParam));
    struParam.u32DmxId     = HIMEDIA_DMX_ID;
    struParam.u32PortId    = HIMEDIA_DMX_PORTID; //what about port 0 for tunner dvb??
    struParam.u32MixHeight = HIMEDIA_DEFAULT_MIXWEIGHT;
    struParam.hAVPlayer    = HI_SVR_PLAYER_INVALID_HDL;
    struParam.u32SndPort   = HIMEDIA_DEFAULT_SNDPORT;
    struParam.u32Display   = HI_UNF_DISPLAY1;

    if(mNonVSink != true)
        struParam.hVSink   = reinterpret_cast<HI_HANDLE>(
            dynamic_cast<HI_SVR_VSINK_S*>(mVSink.get()));
    else
        struParam.hVSink   = NULL;
    struParam.hASink        = reinterpret_cast<HI_HANDLE>(
            dynamic_cast<HI_SVR_ASINK_S*>(mASink.get()));
    struParam.x            = HIMEDIA_DEFAULT_OUTPUT_X;
    struParam.y            = HIMEDIA_DEFAULT_OUTPUT_Y;

    int w = 0;
    int h = 0;
    DisplayClient DspClient;
    DspClient.GetVirtScreenSize(&w, &h);
    struParam.w  = w;
    struParam.h = h;

    char buffer[PROP_VALUE_MAX];
    memset(buffer, 0, PROP_VALUE_MAX);
    if (property_get("service.media.hiplayer.vdecerr", buffer, "0") && !strcasecmp("100", buffer))
    {
        struParam.u32VDecErrCover = 100;
    }
    else
    {
        struParam.u32VDecErrCover = 0;
    }

    mMediaParam.s32PlayMode = HI_SVR_PLAYER_PLAYMODE_NORMAL;
    surfaceSetting::getScreenResolution((int&)struParam.w, (int&)struParam.h);

    LOGV("Init screen resolution w[%d] h [%d]", struParam.w, struParam.h);

    if(!mUseExtAVPlay)
    {
        mSndPortId = findValidSndPortId();
    }

    if (mSndPortId == SOUND_INVALID_PORTID)
    {
        LOGE("ERR: Can not find a Valid Sound Port ID!");
        //mState = STATE_ERROR;
        //return HI_FAILURE;
    }
    else
    {
        struParam.u32SndPort = ((mSndPortId == 0) ? 0 : 1);
        LOGV("Current HiMediaPlayer instance use sound port id [%d]", mSndPortId);
    }

    if(mAVPlayer == HI_INVALID_HANDLE)
    {
        struParam.hAVPlayer = (HI_HANDLE)NULL;
    }
    else
    {
        struParam.hAVPlayer = mAVPlayer;

        if (HI_INVALID_HANDLE != mWindow)
        {
            struParam.hWindow = mWindow;
        }
    }

    if (HI_FAILURE == HI_SVR_PLAYER_Create(&struParam, &mHandle))
    {
        LOGE("HI_SVR_PLAYER_Create fail");
        mState = STATE_ERROR;
        return HI_FAILURE;
    }

    s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_CHARSETMGR_FUNC, &g_stCharsetMgr_s);

    if (HI_SUCCESS != s32Ret)
    {
        LOGV("ERR: HI_SVR_PLAYER_Invoke set charsetMgr failed\n");
    }

    HI_S32 s32CodeType = HI_CHARSET_CODETYPE_UTF8;

    s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_DEST_CODETYPE, &s32CodeType);

    if (HI_SUCCESS != s32Ret)
    {
        LOGV("ERR: HI_SVR_PLAYER_Invoke Send Dest CodeType failed\n");
    }

    s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_LOG_LEVEL, (HI_VOID*)s32LogLevel);

    if (HI_SUCCESS != s32Ret)
    {
        LOGV("ERR: HI_SVR_PLAYER_Invoke Set Log Level Fail\n");
    }

    if (HI_FAILURE == HI_SVR_PLAYER_RegCallback(mHandle, HiMediaPlayer::hiPlayerEventCallback))
    {
        LOGE("HI_SVR_PLAYER_RegCallback fail");
        HI_SVR_PLAYER_Destroy(mHandle);
        mHandle = HI_SVR_PLAYER_INVALID_HDL;
        mState = STATE_ERROR;
        return HI_FAILURE;
    }
    { //for autolock
        Mutex::Autolock mLock(&HiMediaPlayer::mInstMutex);
        mInstances.add(mHandle, this);
        mState = STATE_INIT;
    }
    getTrueHDSetting();
    return HI_SUCCESS;
}

void HiMediaPlayer::destroyHiPlayer()
{
    HI_S32 s32Index = 0;

    if (HI_SVR_PLAYER_INVALID_HDL != mHandle)
    {
        LOGV("HiMediaPlayer destroyHiPlayer Step 1, time is %u ", getCurrentTime());

        HI_U32 i = 0;

        while (i < WAITE_COUNT) //1.5s to protect pre_close set successfully
        {
            if (HI_SUCCESS != HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_PRE_CLOSE_FILE , NULL))
            {
                LOGW("WARN: ~HiMediaPlayer() PRE_CLOSE_FILE fail!");
                i++;
                usleep(WAITE_TIME);
                continue;
            }
            else
            {
                break;
            }
        }

        LOGV("HiMediaPlayer destroyHiPlayer after PRE_CLOSE, time is %u ", getCurrentTime());

        if (HI_INVALID_HANDLE != mAVPlayer)
        {
            if (HI_SUCCESS != HI_UNF_AVPLAY_UnRegisterEvent(mAVPlayer, HI_UNF_AVPLAY_EVENT_FRAMEPACKING_CHANGE))
            {
                LOGE("UNRegister HI_UNF_AVPLAY_EVENT_FRAMEPACKING_CHANGE fail ");
            }

            if (HI_SUCCESS != HI_UNF_AVPLAY_UnRegisterEvent(mAVPlayer, HI_UNF_AVPLAY_EVENT_IFRAME_ERR))
            {
                LOGE("UNRegister HI_UNF_AVPLAY_EVENT_IFRAME_ERR fail ");
            }

            if (HI_SUCCESS != HI_UNF_AVPLAY_UnRegisterEvent(mAVPlayer, HI_UNF_AVPLAY_EVENT_NORM_SWITCH))
            {
                LOGE("UNRegister HI_UNF_AVPLAY_EVENT_NORM_SWITCH fail ");
            }

            if (!mUseExtAVPlay)
                mAVPlayer = HI_INVALID_HANDLE;
        }

        if (HI_INVALID_HANDLE != mSoHandle)
        {
            if (HI_SUCCESS != HI_UNF_SO_RegOnDrawCb(mSoHandle, subManager::subOndraw, NULL, 0))
            {
                LOGE("HI_UNF_SO_RegOnDrawCb or HI_SVR_PLAYER_GetParam fail!");
            }

            mSoHandle = HI_INVALID_HANDLE;
        }

        LOGV("HiMediaPlayer call HI_SVR_PLAYER_Destroy before, time is %u ", getCurrentTime());
        {
            Mutex::Autolock Hiplayerlock(mCmdQueue->mLockHiplayer);
            mCmdQueue->enqueueCommand(new CommandDestroyPlayer(mHandle));
            LOGV("HiMediaPlayer call HI_SVR_PLAYER_Destroy after, time is %u ", getCurrentTime());

            mCmdQueue->mPlayerHandle = HI_SVR_PLAYER_INVALID_HDL;
        }

        // because wasu will not release surfaceview when switch to next program in live,
        // so if we do not push black frame,the last frame of last program will display.
        if (mNativeWindow.get() && mCmdQueue->mAppType == APP_TYPE_WASU)
            pushBlankBuffersToNativeWindow(mNativeWindow);

        LOGV("begin destroy mCmdQueue %u ", getCurrentTime());
        mCmdQueue.clear();
        LOGV("finish destroy mCmdQueue %u ", getCurrentTime());
        mCmdQueue = 0;
        mSurfaceSetting.clear();
        mSubManager.clear();

        s32Index = mInstances.indexOfKey(mHandle);
        writeLog(MEDIA_LOG_DESTROY, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)&s32Index);

        {
            LOGV("HiMediaPlayer destroyHiPlayer Step 2, time is %u ", getCurrentTime());
            Mutex::Autolock mLock(&HiMediaPlayer::mInstMutex);
            LOGV("HiMediaPlayer destroyHiPlayer Step 3, time is %u ", getCurrentTime());
            mInstances.removeItem(mHandle);
            LOGV("HiMediaPlayer destroyHiPlayer Step 4, time is %u ", getCurrentTime());
        }

        //clearValidSndPortId(mSndPortId);
        LOGV("HiMediaPlayer destroyHiPlayer Step 5");
        mHandle = HI_SVR_PLAYER_INVALID_HDL;
    }
}

HiMediaPlayer::~HiMediaPlayer()
{
    if (true == mUseStaticResource)
    {
        LOGV("HiMediaPlayer destructor Finish (do nothing)");
        return;
    }

#ifndef HIMEDIA_NOT_DEINIT_RESOURCE
    if (mState > STATE_ERROR_INITPLAYER)
    {
        HiMediaSystem::deInitPlayer();
    }
#endif

    LOGV("HiMediaPlayer destructor Step 1, deinitplayer finish");

    if(mUseExtAVPlay)
    {
        destroyAVPlay();
    }
    LOGV("HiMediaPlayer destructor Step 2, destroy avplay finish");

    clearValidSndPortId(mSndPortId);
    LOGV("HiMediaPlayer destructor Step 3, clear valid snd port id %d ", mSndPortId);
    mSndPortId = SOUND_INVALID_PORTID;

#ifndef HIMEDIA_NOT_DEINIT_RESOURCE
    if (mState > STATE_ERROR_INITDEVICE)
    {
        HiMediaSystem::deInitDevice();
    }

    LOGV("HiMediaPlayer destructor Step 4, deinit device finish");
    HiMediaSystem::deInitCharset();
#endif

    LOGV("[%s] HiMediaPlayer destructor Finish", STR_SWITCH_PG);
}

bool HiMediaPlayer::IsMustASyncPrepareUrl(char *uri)
{
    if(strstr(mMediaParam.aszUrl, "http://") || strstr(mMediaParam.aszUrl, "rtsp://")
        || strstr(mMediaParam.aszUrl, "rtp://") || IS_MMS_URL(mMediaParam.aszUrl)
        || IS_RTMP_URL(mMediaParam.aszUrl) || strstr(mMediaParam.aszUrl, "bluray:"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool HiMediaPlayer::IsUseVsinkWindow()
{
    char value[PROPERTY_VALUE_MAX] = {0};

    if (property_get("service.media.hiplayer.graphic", value, "false") && !strcasecmp("false", value)
        || true == mNonVSink)
    {
        ALOGD("do not use graphic output for hiplayer");
        return false;
    }

    if(strstr(mMediaParam.aszUrl, "http://") || strstr(mMediaParam.aszUrl, "rtsp://")
        || strstr(mMediaParam.aszUrl, "rtp://") || IS_MMS_URL(mMediaParam.aszUrl)
        || IS_RTMP_URL(mMediaParam.aszUrl) || strstr(mMediaParam.aszUrl, "udp://"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void HiMediaPlayer::SetDatasourcePrepare(char *uri)
{
    char value[PROPERTY_VALUE_MAX] = {0};
    if (property_get("ro.cts.enable", value, "false") && !strncasecmp("false", value, 5))
    {
        return;
    }

    if (false == IsMustASyncPrepareUrl(uri))
    {
        mSetdatasourcePrepare = true;
        LOGV("setdatasource prepare");
        prepare();
        mHasPrepared = true;
        mSetdatasourcePrepare = false;
    }
}

status_t HiMediaPlayer::setDataSource(const char *uri, const KeyedVector<String8, String8> *headers)
{
    LOGV("[%s] HiMediaPlayer::setDataSource uri[%s]", STR_SWITCH_PG, uri);

    String8 mHeaders = String8();
    String8 line;
    memset(&mMediaParam, 0, sizeof(mMediaParam));
    strncpy(mMediaParam.aszUrl, uri, (size_t)HI_FORMAT_MAX_URL_LEN - 1);
    /* replace character /r and /n to NULL in url*/
    char *pChar0D0A = mMediaParam.aszUrl;
    while(pChar0D0A && *pChar0D0A != '\0')
    {
        if(*pChar0D0A == 0x0D || *pChar0D0A == 0x0A)
        {
            *pChar0D0A = 0;
            LOGV("uri[%s] have char [0D0A], cut to [%s]",uri, mMediaParam.aszUrl);
            break;
        }
        pChar0D0A++;
    }

    mFirstPlay = true;

    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 10);
    char diagnoseDisable[PROPERTY_VALUE_MAX];
    diagnoseDisable[0] = 0;
    if (strstr(mMediaParam.aszUrl, "diagnose=deep") ||
        (property_get("diagnose.disable", diagnoseDisable, NULL) <= 0) ||
        (property_get("diagnose.disable", diagnoseDisable, NULL) > 0 && 0 == atoi(diagnoseDisable)))//(strstr(mMediaParam.aszUrl, "diagnose=deep"))
    {
        LOGV("open HLS Diagnose...");
        mDiagnose = 1;
        mLogger = new HiMediaLogger("/tmp/playInfoLog", 3600/*1h*/, 900/*15m*/);
       // mLogger = new HiMediaLogger("/tmp/playLog", 600/*1h*/, 120/*15m*/);
        if (mLogger == NULL)
        {
            LOGE("HiMediaPlayer::create HiMediaLogger fail");
        }
        else
        {
            LOGV("HiMediaPlayer::create HiMediaLogger OK");
        }
    }
    else
    {
        mDiagnose = 0;
        LOGV("close HLS Diagnose...");
    }
    LOGV("property diagnose.disable:%s", diagnoseDisable);

    writeLog(MEDIA_LOG_SET_DATA_SOURCE, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)uri);

    if (headers == NULL)
    {
        SetDatasourcePrepare(mMediaParam.aszUrl);
        return NO_ERROR;
    }

    for (size_t i = 0; i < headers->size(); ++i)
    {
        line.setTo("");
        line.append(headers->keyAt(i));
        line.append(": ");
        line.append(headers->valueAt(i));
        line.append("\r\n");
        mHeaders.append(line);
    }

    mMediaParam.u32UserData = (HI_U32)strdup(mHeaders.string());
    SetDatasourcePrepare(mMediaParam.aszUrl);
    return NO_ERROR;
}

status_t HiMediaPlayer::setDataSource(int fd, int64_t offset, int64_t length)
{
    LOGV("[%s] HiMediaPlayer::setDataSource fd[%d] offset[%lld] length[%lld]",
        STR_SWITCH_PG, fd, offset, length);

    HI_CHAR filePath[64];
    HI_CHAR dataSrcPath[HI_FORMAT_MAX_URL_LEN];
    char value[PROPERTY_VALUE_MAX] = {0};
    char diagnoseDisable[PROPERTY_VALUE_MAX];

    memset(filePath, 0, 64);
    memset(dataSrcPath, 0, HI_FORMAT_MAX_URL_LEN);

    sp<FdDelegate> fdDelegate = new FdDelegate(fd);
    mFdDelegates.push(fdDelegate);
    snprintf(filePath, 63, "/proc/%d/fd/%d", getpid(), fd);
    readlink(filePath, dataSrcPath, HI_FORMAT_MAX_URL_LEN);

    //set the file name and offset to stMedia
    memset(&mMediaParam, 0, sizeof(mMediaParam));
        snprintf(mMediaParam.aszUrl, HI_FORMAT_MAX_URL_LEN - 1,
            "%s%s%lld%s%lld%s%d",
        dataSrcPath, SEPARATE_SYMBOL_OFFSET, offset, SEPARATE_SYMBOL_LENGTH, length, SEPARATE_SYMBOL_FD,  fdDelegate->getFd());

    LOGV("mMediaParam.aszUrl is: %s", mMediaParam.aszUrl);
    diagnoseDisable[0] = 0;
    if (strstr(mMediaParam.aszUrl, "diagnose=deep") ||
        (property_get("diagnose.disable", diagnoseDisable, NULL) <= 0) ||
        (property_get("diagnose.disable", diagnoseDisable, NULL) > 0 && 0 == atoi(diagnoseDisable)))
    {
        LOGV("open HLS Diagnose...");
        mDiagnose = 1;
        mLogger = new HiMediaLogger("/tmp/playInfoLog", 3600/*1h*/, 900/*15m*/);
       // mLogger = new HiMediaLogger("/tmp/playLog", 600/*1h*/, 120/*15m*/);
        if (mLogger == NULL)
        {
            LOGE("HiMediaPlayer::create HiMediaLogger fail");
        }
        else
        {
            LOGV("HiMediaPlayer::create HiMediaLogger OK");
        }
    }
    else
    {
        mDiagnose = 0;
        LOGV("close HLS Diagnose...");
    }
    LOGV("property diagnose.disable:%s", diagnoseDisable);
    mFirstPlay = true;
    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 10);
    SetDatasourcePrepare(mMediaParam.aszUrl);
    return NO_ERROR;
}

int HiMediaPlayer::dumpFileInfo(HI_FORMAT_FILE_INFO_S *pstFileInfo)
{
    HI_U32 i = 0, j = 0;

    LOGV("*************************************************");
    if (HI_FORMAT_STREAM_TS == pstFileInfo->eStreamType)
        LOGV("Stream type: %s ", "TS");
    else
        LOGV("Stream type: %s ", "ES");

    if (HI_FORMAT_SOURCE_LOCAL == pstFileInfo->eSourceType)
        LOGV("Source type: %s ", "LOCAL");
    else if (HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType)
        LOGV("Source type: %s ", "VOD");
    else if (HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType)
        LOGV("Source type: %s ", "LIVE");

    LOGV("File size:   %lld bytes ", pstFileInfo->s64FileSize);
    LOGV("Start time:  %lld:%lld:%lld ",
        pstFileInfo->s64StartTime / (1000 * 3600),
        (pstFileInfo->s64StartTime % (1000 * 3600)) / (1000 * 60),
        ((pstFileInfo->s64StartTime % (1000 * 3600)) % (1000 * 60)) / 1000);
    LOGV("Duration:    %lld:%lld:%lld ",
        pstFileInfo->s64Duration / (1000 * 3600),
        (pstFileInfo->s64Duration % (1000 * 3600)) / (1000 * 60),
        (((pstFileInfo->s64Duration + 500) % (1000 * 3600)) % (1000 * 60)) / 1000);
    LOGV("bps:         %d bits/s ", pstFileInfo->u32Bitrate);

    for (i = 0; i < (int)pstFileInfo->u32ProgramNum; i++)
    {
        LOGV("Program %d: ", i);

        for (j = 0; j < pstFileInfo->pastProgramInfo[i].u32VidStreamNum; j++)
        {
            LOGV("   video %d info: ", j);
            LOGV("     stream idx:   %d ", pstFileInfo->pastProgramInfo[i].pastVidStream[j].s32StreamIndex);
            LOGV("     format:       %d ", pstFileInfo->pastProgramInfo[i].pastVidStream[j].u32Format);
            LOGV("     w * h:        %d * %d ",
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16Width,
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16Height);

            LOGV("     fps:          %d.%d ",
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16FpsInteger,
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16FpsDecimal);
            LOGV("     bps:          %d bits/s ", pstFileInfo->pastProgramInfo[i].pastVidStream[j].u32Bitrate);
            LOGV("     duration:     %lld:%lld:%lld ",
                pstFileInfo->pastProgramInfo[i].pastVidStream[j].s64Duration / (1000 * 3600),
                (pstFileInfo->pastProgramInfo[i].pastVidStream[j].s64Duration  % (1000 * 3600)) / (1000 * 60),
                (((pstFileInfo->pastProgramInfo[i].pastVidStream[j].s64Duration + 500)  % (1000 * 3600)) % (1000 * 60)) / 1000);
        }

        for (j = 0; j < (int)pstFileInfo->pastProgramInfo[i].u32AudStreamNum; j++)
        {
            LOGV("   audio %d info: ", j);
            LOGV("     stream idx:   %d ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].s32StreamIndex);
            LOGV("     format:       %d ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32Format);
            LOGV("     samplerate:   %d Hz ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32SampleRate);
            LOGV("     bitpersample: %d ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16BitPerSample);
            LOGV("     channels:     %d ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16Channels);
            LOGV("     bps:          %d bits/s ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16BitPerSample);
            LOGV("     lang:         %s ", pstFileInfo->pastProgramInfo[i].pastAudStream[j].aszLanguage);
            LOGV("     subID:        %d", pstFileInfo->pastProgramInfo[i].pastAudStream[j].s32SubStreamID);
            LOGV("     duration:     %lld:%lld:%lld ",
                pstFileInfo->pastProgramInfo[i].pastAudStream[j].s64Duration / (1000 * 3600),
                (pstFileInfo->pastProgramInfo[i].pastAudStream[j].s64Duration  % (1000 * 3600)) / (1000 * 60),
                (((pstFileInfo->pastProgramInfo[i].pastAudStream[j].s64Duration + 500) % (1000 * 3600)) % (1000 * 60)) / 1000);
        }

        for (j = 0; j < (int)pstFileInfo->pastProgramInfo[i].u32SubStreamNum; j++)
        {
            LOGV("   subtitle %d info: ", j);
            LOGV("     stream idx:   %d ", pstFileInfo->pastProgramInfo[i].pastSubStream[j].s32StreamIndex);
            LOGV("     format:       %d ", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u32Format);
            LOGV("     lang:         %s ", (char*)(pstFileInfo->pastProgramInfo[i].pastSubStream[j].paszLanguage));
            LOGV("     be ext sub:   %d ", pstFileInfo->pastProgramInfo[i].pastSubStream[j].bExtSub);
            LOGV("     sub u16OriginalFrameHeight: %d ", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u16OriginalFrameHeight);
            LOGV("     sub u16OriginalFrameWidth:  %d ", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u16OriginalFrameWidth);

        }
    }
    LOGV("*************************************************");

    return HI_SUCCESS;
}

status_t HiMediaPlayer::CreateAsinkAudioTrack()
{
    int s32Ret = HI_SUCCESS;
    int i = 0;
    // if set audio sink
    if (NULL != mASink.get() && NULL != mpFileInfo)
    {
        if ((HI_HANDLE)HI_INVALID_HANDLE != mAudioTrack)
        {
            LOGV("Set Asink,Destroy ori Audio Track %d", mAudioTrack);
            s32Ret |= HI_UNF_SND_Detach(mAudioTrack, mAVPlayer);
            s32Ret |= HI_UNF_SND_DestroyTrack(mAudioTrack);
            s32Ret |= HI_UNF_AVPLAY_ChnClose(mAVPlayer, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
            mAudioTrack = (HI_HANDLE)HI_INVALID_HANDLE;
            LOGV("Detach sound device, ret = 0x%x !", s32Ret);
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("Set ASink Destroy ori Audio Track Fail");
                return UNKNOWN_ERROR;
            }

            for (i = 0; i < mAVPlayInstances.AvPlayCount; i++)
            {
                if (mAVPlayer == mAVPlayInstances.mAVPlays[i]->mAVPlayer)
                {
                    LOGV("update avplay %d audio track", i);
                    mAVPlayInstances.mAVPlays[i]->mAudioTrack = HI_INVALID_HANDLE;
                    break;
                }
            }
        }

        HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
        memset(&stTrackAttr, 0, sizeof(stTrackAttr));
        if (0 == mpFileInfo->pastProgramInfo[0].u32VidStreamNum)
        {
            stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_VIRTUAL;
            s32Ret = HI_UNF_SND_GetDefaultTrackAttr(stTrackAttr.enTrackType, &stTrackAttr);
            s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &mAudioTrack);
        }
        else
        {
            memset(&stTrackAttr, 0, sizeof(stTrackAttr));
            //stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_MASTER;
            stTrackAttr.enTrackType = (0 == mSndPortId) ? HI_UNF_SND_TRACK_TYPE_MASTER : HI_UNF_SND_TRACK_TYPE_SLAVE;
            char value[PROPERTY_VALUE_MAX] = {0};

            s32Ret = HI_UNF_SND_GetDefaultTrackAttr(stTrackAttr.enTrackType, &stTrackAttr);
            LOGV("HI_UNF_SND_GetDefaultTrackAttr end");

            if (HI_SUCCESS != s32Ret)
            {
                LOGV("Get default trackattr(type:%d) fail ,return 0x%x ", stTrackAttr.enTrackType, s32Ret);
                return UNKNOWN_ERROR;
            }

            LOGV("HI_UNF_SND_CreateTrack begin");
            s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &mAudioTrack);

            if (HI_SUCCESS != s32Ret && stTrackAttr.enTrackType == HI_UNF_SND_TRACK_TYPE_MASTER)
            {
                LOGV("Create master track fail, return 0x%x. Try create slave track ", s32Ret);

                stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_SLAVE;
                s32Ret = HI_UNF_SND_GetDefaultTrackAttr(stTrackAttr.enTrackType, &stTrackAttr);
                if (HI_SUCCESS != s32Ret)
                {
                    LOGV("Get default trackattr(type:%d) fail ,return 0x%x ", stTrackAttr.enTrackType, s32Ret);
                    return UNKNOWN_ERROR;
                }

                s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &mAudioTrack);
            }
        }

        HI_UNF_SND_GAIN_ATTR_S stGain;
        if (HI_SUCCESS == s32Ret && (HI_HANDLE)HI_INVALID_HANDLE != mAudioTrack)
        {
            stGain.bLinearMode = HI_TRUE;
            stGain.s32Gain = HIMEDIA_DEFAULT_MIXWEIGHT;
            LOGV("HI_UNF_SND_SetTrackWeight begin");
            s32Ret = HI_UNF_SND_SetTrackWeight(mAudioTrack, &stGain);
            LOGV("HI_UNF_SND_SetTrackWeight end");
            if (HI_SUCCESS == s32Ret)
            {
                LOGV("HI_UNF_AVPLAY_ChnOpen aud begin");
                s32Ret = HI_UNF_AVPLAY_ChnOpen(mAVPlayer, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
                s32Ret |= HI_UNF_SND_Attach(mAudioTrack, mAVPlayer);
                LOGV("HI_UNF_AVPLAY_ChnOpen aud end");
                if (HI_SUCCESS != s32Ret)
                {
                    LOGV("Attach sound device fail! ");
                }
            }
            else
            {
                LOGV("Set sound track mixer weight failed, return 0x%x", s32Ret);
                return UNKNOWN_ERROR;
            }
        }
        else
        {
            LOGE("Set Audio sink,Create audio track fail 0x%x", s32Ret);
            return UNKNOWN_ERROR;
        }

        HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_EXTERNAL_AUDIOTRACK, (HI_VOID *)mAudioTrack);

        for (i = 0; i < mAVPlayInstances.AvPlayCount; i++)
        {
            if (mAVPlayer == mAVPlayInstances.mAVPlays[i]->mAVPlayer)
            {
                LOGV("update avplay %d audio track", i);
                mAVPlayInstances.mAVPlays[i]->mAudioTrack = mAudioTrack;
                break;
            }
        }
    }
    return NO_ERROR;
}

status_t HiMediaPlayer::prepare_l(status_t status, bool cancelled)
{
    HI_HANDLE hSo = HI_INVALID_HANDLE;
    HI_HANDLE hAvPlayer = HI_INVALID_HANDLE;
    bool bHaveVideo = false;
    bool bHaveSubtitle = false;
    HI_U32 i = 0;

    if (NULL == mCmdQueue.get())
    {
        LOGE("mCmdQueue is null,current operation do not execute");
        return NO_ERROR;
    }
    if (status == NO_ERROR)
    {
        LOGV("prepare_l go to get file info");

        if (HI_SUCCESS == HI_SVR_PLAYER_GetFileInfo(mHandle, &mpFileInfo))
        {
            if (NULL == mpFileInfo)
            {
                LOGE("HI_SVR_PLAYER_GetFileInfo fail!");
                return HI_FAILURE;
            }

            mCmdQueue->getFileInfoWrapper(mHandle);
            dumpFileInfo(mpFileInfo);

            if (NO_ERROR != CreateAsinkAudioTrack())
            {
                return UNKNOWN_ERROR;
            }

            for (i = 0; i < (int)mpFileInfo->u32ProgramNum; i++)
            {
                if (0 < mpFileInfo->pastProgramInfo[i].u32SubStreamNum)
                {
                    LOGV("have subtitle");
                    bHaveSubtitle = true;
                }

                /* if there have video, tell app the video's size */
                if (0 < mpFileInfo->pastProgramInfo[i].u32VidStreamNum)
                {
                    if (mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width <= 0)
                    {
                        mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width = HIMEDIA_VIRTUAL_SCREEN_W;
                    }

                    if (mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height <= 0)
                    {
                        mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height = HIMEDIA_VIRTUAL_SCREEN_H;
                    }

                    HI_S32 s32Width  = 0;
                    HI_S32 s32Height = 0;
                    bHaveVideo = true;

                    if (mpFileInfo->pastProgramInfo[i].u32SubStreamNum > 0)
                    {
                        s32Width = mpFileInfo->pastProgramInfo[i].pastSubStream[0].u16OriginalFrameWidth;
                        s32Height= mpFileInfo->pastProgramInfo[i].pastSubStream[0].u16OriginalFrameHeight;
                    }
                    else
                    {
                        s32Width = mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width;
                        s32Height= mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height;
                    }

                    sp<subManager> msm = getSubManager();

                    if (HI_SUCCESS != msm->setRawPicSize(s32Width, s32Height))
                    {
                        s32Width = mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width;
                        s32Height= mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height;
                        mSubManager->setRawPicSize(s32Width, s32Height);
                    }
                    if (false  == mSetdatasourcePrepare)
                    {
                         sendEvent(android::MEDIA_SET_VIDEO_SIZE,
                             mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width,
                             mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height);
                    }
                    break;
                }
            }

            writeLog(MEDIA_LOG_STREAM_INFO, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)mpFileInfo);
            writeLog(MEDIA_LOG_STREAM_CODEC, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)mpFileInfo);
        }
        else
        {
            LOGE("[SetDisplay] HI_SVR_PLAYER_GetFileInfo failed!");
        }

        LOGV("prepare_l get file info finish");

        //register subtitle output module draw/clear callback
        if (true == bHaveSubtitle)
        {
            HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_SO_HDL, &hSo);

            if (HI_INVALID_HANDLE != hSo)
            {
                mSoHandle = hSo;
                if (mOrigAndroidPath == true && NULL == mSubTitleNativeWindow.get() && IsUseVsinkWindow())
                {
                    for (i=0;i<mTimedTextStringArray.size();i++)
                    {
                        HiMediaPlayer::AddExtTimedTextStream(mTimedTextStringArray.getEntry(i));
                    }

                    for (i=0;i<mTimedTextStringArray.size();i++)
                    {
                        mTimedTextStringArray.erase(0);
                    }

                    LOGV("TIMEDTEXT in HiMediaPlayer::prepare_l, mOrigAndroidPath=true ready to hook SO,mHandle=%p",mHandle);
                    if (HI_SUCCESS != HI_UNF_SO_RegOnDrawCb(hSo, (HI_UNF_SO_ONDRAW_FN)this->TimedTextOndraw, \
                        (HI_UNF_SO_ONCLEAR_FN)this->TimedTextOnclear, (HI_U32)this))
                    {
                        LOGE("HI_UNF_SO_RegOnDrawCb or HI_SVR_PLAYER_GetParam fail!");
                    }
                }
                else
                {
                    LOGV("TIMEDTEXT in HiMediaPlayer::prepare_l, mOrigAndroidPath=FALSE, original SO path");
                    if (HI_SUCCESS != HI_UNF_SO_RegOnDrawCb(hSo, subManager::subOndraw, \
                        subManager::subOnclear, (HI_U32)getSubManager().get()))
                    {
                        LOGE("HI_UNF_SO_RegOnDrawCb or HI_SVR_PLAYER_GetParam fail!");
                    }
                }
            }
        }

        sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 80);
    }
    else
    {
        if (false  == mSetdatasourcePrepare)
        {
            sendEvent(android::MEDIA_ERROR, android::MEDIA_ERROR_UNKNOWN, android::MEDIA_ERROR_UNSUPPORTED);
        }
    }

    if (mPrepareAsync == true)
    {
        if (NO_ERROR == status)
        {
            if (HI_SUCCESS == HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAvPlayer))
            {
                if (HI_INVALID_HANDLE != hAvPlayer)
                {
                    if (HI_INVALID_HANDLE == mAVPlayer)
                        mAVPlayer = hAvPlayer;

                    //for IFrame error detection
                    LOGV("[HiMediaPlayer-IFrame]:  Register_streamIFrameErrorCB");

                    if (HI_SUCCESS != HI_UNF_AVPLAY_RegisterEvent(hAvPlayer, HI_UNF_AVPLAY_EVENT_IFRAME_ERR, HiMediaPlayer::streamIFrameErrorCB))
                    {
                        LOGE("[HiMediaPlayer-IFrame]:  Register_streamIFrameErrorCB fail ");
                    }

                    //add for Norm switch
                    LOGV("[HiMediaPlayer-NormSwitch]:  Register_streamNormSwitchCB");

                    if (HI_SUCCESS != HI_UNF_AVPLAY_RegisterEvent(hAvPlayer, HI_UNF_AVPLAY_EVENT_NORM_SWITCH, HiMediaPlayer::streamNormSwitchCB))
                    {
                        LOGE("[HiMediaPlayer-NormSwitch]:  Register_streamNormSwitchCB fail ");
                    }
                }
                else
                {
                    LOGV("Get avplay handle is invalid");
                }
            }
            //end

            LOGV("Send Event MEDIA_PREPARED");
            if (false  == mSetdatasourcePrepare)
            {
                LOGV("Send Event MEDIA_PREPARED in local play");
                sendEvent(MEDIA_PREPARED);
            }
        }
    }

    if (true == mUseExtAVPlay)
    {
        HI_S32 s32Ret;

        if (true == bHaveVideo)
        {
            s32Ret = HI_UNF_VO_SetWindowEnable(mWindow, HI_TRUE);
        }
        else
        {
            s32Ret = HI_UNF_VO_SetWindowEnable(mWindow, HI_FALSE);
        }

        if (HI_SUCCESS != s32Ret)
        {
            LOGV("Enable window failed.");
        }
    }

    return 0;
}

status_t HiMediaPlayer::SendPrepareMessage()
{
    if (NO_ERROR != mPrepareResult)
    {
        sendEvent(android::MEDIA_ERROR, android::MEDIA_ERROR_UNKNOWN, android::MEDIA_ERROR_UNSUPPORTED);
        LOGE("do not setdatasource preapre fail");
        return UNKNOWN_ERROR;
    }
    int i = 0;
    if (NULL != mpFileInfo)
    {
        for (i = 0; i < (int)mpFileInfo->u32ProgramNum; i++)
        {
            /* if there have video, tell app the video's size */
            if (0 < mpFileInfo->pastProgramInfo[i].u32VidStreamNum)
            {
                if (mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width <= 0)
                {
                    mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width = HIMEDIA_VIRTUAL_SCREEN_W;
                }

                if (mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height <= 0)
                {
                    mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height = HIMEDIA_VIRTUAL_SCREEN_H;
                }
                LOGV("setdatasource prepared,send video size");
                sendEvent(android::MEDIA_SET_VIDEO_SIZE,
                    mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Width,
                    mpFileInfo->pastProgramInfo[i].pastVidStream[0].u16Height);

                break;
            }
       }
    }
    mIsPrepared = true;
    sendEvent(MEDIA_PREPARED);
    return NO_ERROR;
}

status_t HiMediaPlayer::prepare()
{
    int i = 0;
    status_t ret;
    HI_S32 s32Index = 0;

    LOGV("[%s] Call HiMediaPlayer::prepare() IN", STR_SWITCH_PG);

    if (true == mHasPrepared)
    {
        return SendPrepareMessage();
    }

    //malloc avplay relation resource
    if (true == mUseExtAVPlay && HI_INVALID_HANDLE == mAVPlayer)
    {
        Mutex::Autolock lock(&HiMediaPlayer::mCreateAvplayMutex);
        if (HI_SUCCESS != mallocAvPlayResource())
        {
            LOGV("mallocAvPlayResource fail");
            return UNKNOWN_ERROR;
        }
    }

    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 20);

    if (HI_SVR_PLAYER_INVALID_HDL == mHandle)
    {
        if(HI_SUCCESS != createHiplayer())
        {
            LOGE("ERR: createHiplayer fail!");
            writeLog(MEDIA_LOG_CREATE_NEW_PLAYER, MEDIA_LOG_LEVEL_FATAL, (HI_VOID *)&s32Index);
            return UNKNOWN_ERROR;
        }

        s32Index = mInstances.indexOfKey(mHandle);
        writeLog(MEDIA_LOG_CREATE_NEW_PLAYER, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)&s32Index);
    }

    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 40);

    mPrepareAsync = false;

    // set Referer
    if (NULL != mstrReferer)
    {
        LOGV("set Refer invoke");
        if (HI_SUCCESS == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_REFERER, (HI_VOID *)mstrReferer))
        {
            LOGV("set Refer success,%s", mstrReferer);
        }
        else
        {
            LOGE("set Refer,call invoke methed fail");
        }

        delete[] mstrReferer;
        mstrReferer = NULL;
    }

    // set UA
    if (NULL != mstrUserAgent)
    {
        LOGV("set ua invoke");
        if (HI_SUCCESS == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_USERAGENT, (HI_VOID *)mstrUserAgent))
        {
            LOGV("set ua success,%s", mstrUserAgent);
        }
        else
        {
            LOGE("set ua,call invoke methed fail");
        }

        delete[] mstrUserAgent;
        mstrUserAgent = NULL;
    }

    if (mIsNotSupportByteRange)
    {
        if (HI_SUCCESS == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_NOT_SUPPORT_BYTERANGE, (HI_VOID *)mIsNotSupportByteRange))
        {
            LOGV("set not support byte range success,%d", mIsNotSupportByteRange);
        }
        else
        {
            LOGE("set not support byte range,call invoke methed fail");
        }
    }

    ret = mCmdQueue->enqueueCommand(new CommandPrepare(mHandle, mMediaParam));
    prepare_l(ret, false);

    LOGV("[%s] prepare sync finish", STR_SWITCH_PG);
    mIsPrepared = true;

    return ret;
}

int HiMediaPlayer::initResource()
{
    if (HiMediaSystem::initCharset() != NO_ERROR)
    {
        LOGE("ERR: charset init failed\n");
    }

    if (HiMediaSystem::initDevice() != NO_ERROR)
    {
        mState = STATE_ERROR_INITDEVICE;
        return HI_FAILURE;;
    }

    if (HiMediaSystem::initPlayer() != NO_ERROR)
    {
        mState = STATE_ERROR_INITPLAYER;
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static status_t pushBlankBuffersToNativeWindow(const sp<ANativeWindow> &mNativeWindow) {
    status_t err = NO_ERROR;
    ANativeWindowBuffer* anb = NULL;
    int numBufs = 0;
    int minUndequeuedBufs = 0;

    LOGV("push black buffer to surfaceflinger to flush last frame");
    // We need to reconnect to the ANativeWindow as a CPU client to ensure that
    // no frames get dropped by SurfaceFlinger assuming that these are video
    // frames.
    err = native_window_api_disconnect(mNativeWindow.get(),
            NATIVE_WINDOW_API_MEDIA);
    if (err != NO_ERROR)
    {
        LOGE("error pushing blank frames: api_disconnect failed: %s (%d)",
                strerror(-err), -err);
    }

    err = native_window_api_connect(mNativeWindow.get(),
            NATIVE_WINDOW_API_CPU);
    if (err != NO_ERROR)
    {
        LOGE("error pushing blank frames: api_connect failed: %s (%d)",
                strerror(-err), -err);
    }

    err = native_window_set_buffers_geometry(mNativeWindow.get(), 1, 1,
            HAL_PIXEL_FORMAT_RGBA_8888);
    if (err != NO_ERROR)
    {
        LOGE("error pushing blank frames: set_buffers_geometry failed: %s (%d)",
                strerror(-err), -err);
        goto error;
    }

    err = native_window_set_usage(mNativeWindow.get(),
            GRALLOC_USAGE_SW_WRITE_OFTEN);
    if (err != NO_ERROR)
    {
        LOGE("error pushing blank frames: set_usage failed: %s (%d)",
                strerror(-err), -err);
        goto error;
    }

    err = native_window_set_scaling_mode(mNativeWindow.get(),
            NATIVE_WINDOW_SCALING_MODE_SCALE_TO_WINDOW);
    if (err != OK)
    {
        LOGE("error pushing blank frames: set_scaling_mode failed: %s (%d)",
                strerror(-err), -err);
        goto error;
    }

    err = mNativeWindow->query(mNativeWindow.get(),
            NATIVE_WINDOW_MIN_UNDEQUEUED_BUFFERS, &minUndequeuedBufs);
    if (err != NO_ERROR)
    {
        LOGE("error pushing blank frames: MIN_UNDEQUEUED_BUFFERS query "
                "failed: %s (%d)", strerror(-err), -err);
        goto error;
    }

    numBufs = minUndequeuedBufs + 1;
    err = native_window_set_buffer_count(mNativeWindow.get(), numBufs);
    if (err != NO_ERROR)
    {
        ALOGE("error pushing blank frames: set_buffer_count failed: %s (%d)",
                strerror(-err), -err);
        goto error;
    }

    // We  push numBufs + 1 buffers to ensure that we've drawn into the same
    // buffer twice.  This should guarantee that the buffer has been displayed
    // on the screen and then been replaced, so an previous video frames are
    // guaranteed NOT to be currently displayed.
    for (int i = 0; i < numBufs + 1; i++)
    {
        int fenceFd = -1;
        err = native_window_dequeue_buffer_and_wait(mNativeWindow.get(), &anb);
        if (err != NO_ERROR)
        {
            LOGE("error pushing blank frames: dequeueBuffer failed: %s (%d)",
                    strerror(-err), -err);
            goto error;
        }

        sp<GraphicBuffer> buf(new GraphicBuffer(anb, false));

        // Fill the buffer with the a 1x1 checkerboard pattern
        uint32_t* img = NULL;
        err = buf->lock(GRALLOC_USAGE_SW_WRITE_OFTEN, (void**)(&img));
        if (err != NO_ERROR)
        {
            LOGE("error pushing blank frames: lock failed: %s (%d)",
                    strerror(-err), -err);
            goto error;
        }

        *img = 0;
        err = buf->unlock();
        if (err != NO_ERROR)
        {
            LOGE("error pushing blank frames: unlock failed: %s (%d)",
                    strerror(-err), -err);
            goto error;
        }

        err = mNativeWindow->queueBuffer(mNativeWindow.get(),
                buf->getNativeBuffer(), -1);
        if (err != NO_ERROR)
        {
            LOGE("error pushing blank frames: queueBuffer failed: %s (%d)",
                    strerror(-err), -err);
            goto error;
        }

        anb = NULL;
    }

error:

    if (err != NO_ERROR)
    {
        // Clean up after an error.
        if (anb != NULL)
        {
            mNativeWindow->cancelBuffer(mNativeWindow.get(), anb, -1);
        }

        native_window_api_disconnect(mNativeWindow.get(),
                NATIVE_WINDOW_API_CPU);
        native_window_api_connect(mNativeWindow.get(),
                NATIVE_WINDOW_API_MEDIA);

        return err;
    }
    else
    {
        // Clean up after success.
        err = native_window_api_disconnect(mNativeWindow.get(),
                NATIVE_WINDOW_API_CPU);
        if (err != NO_ERROR)
        {
            LOGE("error pushing blank frames: api_disconnect failed: %s (%d)",
                    strerror(-err), -err);
            return err;
        }

        err = native_window_api_connect(mNativeWindow.get(),
                NATIVE_WINDOW_API_MEDIA);
        if (err != NO_ERROR)
        {
            LOGE("error pushing blank frames: api_connect failed: %s (%d)",
                    strerror(-err), -err);
            return err;
        }

        return NO_ERROR;
    }
}


int HiMediaPlayer::reCreateAvplay()
{
    LOGV("Call HiMediaPlayer::reCreateAvplay() IN");
    destroyAVPlay();
    mWindow = HI_INVALID_HANDLE;
    mAVPlayer = HI_INVALID_HANDLE;
    mAudioTrack = HI_INVALID_HANDLE;
    createAVPlay();

    LOGV("Call HiMediaPlayer::reCreateAvplay() OUT");
    return HI_SUCCESS;
}


int HiMediaPlayer::mallocAvPlayResource()
{
    int i = 0;
    int ret = HI_SUCCESS;

    if (true == mNdkMode)
    {
        if (HI_INVALID_HANDLE == mAVPlayer)
        {
            LOGV("NDK mode, not use Static AvPlay Resource");

            ret = initResource();
            if (HI_SUCCESS != ret)
            {
                LOGE("initResource fail, ret:%d", ret);
            }

            ret = createAVPlay();
            if (HI_SUCCESS != ret)
            {
                LOGE("initResource fail, ret:%d", ret);
            }
        }

        mUseStaticResource = false;
        return ret;
    }

    LOGV("static avplay number is %d, max:%d", mAVPlayInstances.AvPlayCount, HIMEDIA_STATIC_AVPLAY_MAX_CNT);

    for (i = 0; i < mAVPlayInstances.AvPlayCount; i++)
    {
        if (false == mAVPlayInstances.mAVPlays[i]->mUse)
        {
            mAVPlayer = mAVPlayInstances.mAVPlays[i]->mAVPlayer;
            mWindow = mAVPlayInstances.mAVPlays[i]->mWindow;
            mAudioTrack = mAVPlayInstances.mAVPlays[i]->mAudioTrack;
            mAVPlayInstances.mAVPlays[i]->mUse = true;

            if (mAVPlayInstances.mAVPlays[i]->mUseVsinkWindow == IsUseVsinkWindow())
            {
                LOGV("find static avplay handle %x idx %d", mAVPlayer, i);
            }
            else
            {
                LOGV("find static avplay handle %x idx %d, but window is not match", mAVPlayer, i);
                reCreateAvplay();
                mAVPlayInstances.mAVPlays[i]->mAVPlayer = mAVPlayer;
                mAVPlayInstances.mAVPlays[i]->mWindow = mWindow;
                mAVPlayInstances.mAVPlays[i]->mAudioTrack = mAudioTrack;
                mAVPlayInstances.mAVPlays[i]->mUseVsinkWindow = IsUseVsinkWindow();
            }

            mUseStaticResource = true;
            break;
        }
    }

    if (i == mAVPlayInstances.AvPlayCount)
    {
        if (mAVPlayInstances.AvPlayCount < HIMEDIA_STATIC_AVPLAY_MAX_CNT)
        {
            ret = initResource();
            ret |= createAVPlay();

            if(HI_SUCCESS == ret)
            {
                AvPlayInfo *avplayInfo = new AvPlayInfo();
                avplayInfo->mAudioTrack = mAudioTrack;
                avplayInfo->mWindow = mWindow;
                avplayInfo->mAVPlayer = mAVPlayer;
                avplayInfo->mUse = true;
                avplayInfo->mUseVsinkWindow = IsUseVsinkWindow();
                mAVPlayInstances.AvPlayCount++;
                mAVPlayInstances.mAVPlays.add(avplayInfo);
                mUseStaticResource = true;
            }
        }
        else
        {
            LOGV("static avplay resource exceed max is %d, use self create resource", HIMEDIA_STATIC_AVPLAY_MAX_CNT);
            ret = initResource();
            ret |= createAVPlay();
            mUseStaticResource = false;
        }
    }

    return ret;
}

status_t HiMediaPlayer::prepareAsync()
{
    status_t ret = NO_ERROR;
    HI_S32 s32Index = 0;
    int i =0;
    LOGV("[%s] Call %s IN", STR_SWITCH_PG, __FUNCTION__);

    writeLog(MEDIA_LOG_PREPARE_ASYNC, MEDIA_LOG_LEVEL_INFO, NULL);

    if (mHasPrepared)
    {
        return SendPrepareMessage();
    }

    //malloc avplay relation resource
    if (true == mUseExtAVPlay && HI_INVALID_HANDLE == mAVPlayer)
    {
        Mutex::Autolock lock(&HiMediaPlayer::mCreateAvplayMutex);
        if (HI_SUCCESS != mallocAvPlayResource())
        {
            LOGV("mallocAvPlayResource fail");
            writeLog(MEDIA_LOG_CREATE_NEW_PLAYER, MEDIA_LOG_LEVEL_FATAL, (HI_VOID *)&s32Index);
            return UNKNOWN_ERROR;
        }

        s32Index = mInstances.indexOfKey(mHandle);
        writeLog(MEDIA_LOG_CREATE_NEW_PLAYER, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)&s32Index);
    }

    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 20);

    if (HI_SVR_PLAYER_INVALID_HDL == mHandle)
    {
        LOGV("prepareAsync CreatePlayer");

        if (HI_SUCCESS != createHiplayer())
        {
            LOGE("ERR: createHiplayer fail!");
            return UNKNOWN_ERROR;
        }
    }

    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 40);

    // set Referer
    if (NULL != mstrReferer)
    {
        LOGV("set Refer invoke");
        if (HI_SUCCESS == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_REFERER, (HI_VOID *)mstrReferer))
        {
            LOGV("set Refer success,%s", mstrReferer);
        }
        else
        {
            LOGE("set Refer,call invoke methed fail");
        }

        delete[] mstrReferer;
        mstrReferer = NULL;
    }

    // set UA
    if (NULL != mstrUserAgent)
    {
        LOGV("set ua invoke, addr = 0x%x ", mstrUserAgent);
        if (HI_SUCCESS == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_USERAGENT, (HI_VOID *)mstrUserAgent))
        {
            LOGV("set ua success,%s", mstrUserAgent);
        }
        else
        {
            LOGE("set ua,call invoke methed fail");
        }

        delete[] mstrUserAgent;
        mstrUserAgent = NULL;
    }

    if (mIsNotSupportByteRange)
    {
        if (HI_SUCCESS == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_NOT_SUPPORT_BYTERANGE, (HI_VOID *)mIsNotSupportByteRange))
        {
            LOGV("set not support byte range success,%d", mIsNotSupportByteRange);
        }
        else
        {
            LOGE("set not support byte range,call invoke methed fail");
        }
    }

    mPrepareAsync = true;
    mIsPrepared = true;

    LOGV("enqueue PrepareCommand");
    ret = mCmdQueue->enqueueCommand(new CommandPrepare(mHandle, mMediaParam, prepareAsyncComplete));
    if (NO_ERROR == ret)
    {
        writeLog(MEDIA_LOG_PREPARED, MEDIA_LOG_LEVEL_INFO, NULL);
    }
    else
    {
        writeLog(MEDIA_LOG_PREPARED, MEDIA_LOG_LEVEL_ERROR, NULL);
    }

    return ret;
}

status_t HiMediaPlayer::storeTimedTextData(const char * data, int size, int timeMs, Parcel * parcel)
{
    if (parcel != NULL && data != NULL)
    {
        parcel->writeInt32(KEY_LOCAL_SETTING);
        parcel->writeInt32(KEY_START_TIME);
        parcel->writeInt32(timeMs);

        parcel->writeInt32(KEY_STRUCT_TEXT);
        // write the size of the text sample
        parcel->writeInt32(size);
        // write the text sample as a byte array
        parcel->writeInt32(size);
        parcel->write(data, size);

        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

int HiMediaPlayer::TimedTextOndraw(int u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, void *pArg)
{

    HiMediaPlayer *pHiMediaPlayer = NULL;
    pHiMediaPlayer = (HiMediaPlayer *)u32UserData;
    Parcel tmpParcel;
    char _string[SUB_CHAR_MAX_LEN + 2] = "";
    int size = 0;
    int timeMs = 0, starttime = 0;
    int CurrentTime = 0;

    if (pHiMediaPlayer == NULL)
    {
        return HI_FAILURE;
    }

    //mIsTimedTextTrackEnable =false means the subtitle track is disable.
    if (pHiMediaPlayer != NULL)
    {
        if( pHiMediaPlayer->mIsTimedTextTrackEnable == false)
            return HI_SUCCESS;
    }

    timeMs = getCurrentTime();
    starttime = timeMs;
    pHiMediaPlayer->getCurrentPosition(&CurrentTime);
    LOGE("sub pts is %lld.current play progress is %d",pstInfo->unSubtitleParam.stText.s64Pts,CurrentTime);

    if (pstInfo->unSubtitleParam.stText.s64Pts > CurrentTime + ANDROID_CTS_SUB_TOLERANCE)
    {
        while(CurrentTime < pstInfo->unSubtitleParam.stText.s64Pts - ANDROID_CTS_SUB_TOLERANCE)
        {
            usleep(ANDROID_CTS_SUB_TOLERANCE * 1000);
            pHiMediaPlayer->getCurrentPosition(&CurrentTime);
            if (getCurrentTime() - starttime > SUBTITLE_SYNC_TIMEOUT)
            {
                LOGE("sync subtitle fail");
                break;
            }
        }
    }

    sp<subManager> msm = pHiMediaPlayer->getSubManager();
    msm->getSubData((HI_U32)msm.get(), pstInfo, pArg, _string, &size);
    // cts sub test,can not return 0 lenght string
    if (0 == strlen(_string))
    {
        return HI_SUCCESS;
    }

    pHiMediaPlayer->storeTimedTextData(_string, size, timeMs, &tmpParcel);
    pHiMediaPlayer->sendEvent(android::MEDIA_TIMED_TEXT, 0, 0, &tmpParcel);

    return HI_SUCCESS;
}

int HiMediaPlayer::TimedTextOnclear(int u32UserData, void *pArg)
{
    HiMediaPlayer *pHiMediaPlayer = NULL;
    pHiMediaPlayer = (HiMediaPlayer *)u32UserData;
    LOGV("TimedTextOnclear enter");

    if (pHiMediaPlayer != NULL)
    {
        pHiMediaPlayer->sendEvent(android::MEDIA_TIMED_TEXT);
        return HI_SUCCESS;
    }
    else
    {
        LOGE("ERROR!!!!!!! in TimedTextOnclear, pHiMediaPlayer=NULL!! ");
        return HI_FAILURE;
    }

}

status_t HiMediaPlayer::start()
{
    LOGV("[%s] Call HiMediaPlayer::start() IN", STR_SWITCH_PG);

    {
        Mutex::Autolock Hiplayerlock(mCmdQueue->mLockIPTVTimeSeek);
        if (mCmdQueue->mIsIPTVTimeSeeking)
        {
            LOGV("now iptv is seeking,can not start");
            return NO_ERROR;
        }

        if (mCmdQueue->mIPTVTimeSeekError)
        {
            LOGV("now iptv seek error,can not start");
            return NO_ERROR;
        }
    }
    status_t  ret = NO_ERROR;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_HANDLE hWin   = HI_SVR_PLAYER_INVALID_HDL;
    HI_S32 s32Width = 0, s32Height = 0;

    writeLog(MEDIA_LOG_START, MEDIA_LOG_LEVEL_INFO, NULL);

    if (mFirstPlay == true)
    {
        sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 90);
    }

    if (mIsPrepared == false)
    {
        ret = prepare();

        if (NO_ERROR != ret)
        {
            LOGE("Prepare fail");
            return UNKNOWN_ERROR;
        }
    }

    if (HI_SUCCESS == HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId)
        && mpFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum > 0)
    {
        s32Width = mpFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[stStreamId.u16SubStreamId].u16OriginalFrameWidth;
        s32Height= mpFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[stStreamId.u16SubStreamId].u16OriginalFrameHeight;

        if (HI_SUCCESS != mSubManager->setRawPicSize(s32Width, s32Height))
        {
            if (0 < mpFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32VidStreamNum)
            {
                s32Width = mpFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u16Width;
                s32Height= mpFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u16Height;
                mSubManager->setRawPicSize(s32Width, s32Height);
            }
        }
    }

    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }

    ret = mCmdQueue->enqueueCommand(new CommandStart(mHandle));

    if (NO_ERROR == ret)
    {
        if (mFirstPlay == true)
        {
            if (!strstr(mMediaParam.aszUrl, "diagnose=deep"))
            {
                if (BUFFERING_NOT_ENOUGH == getBuffering())
                {
                    LOGV("append one more MEDIA_INFO_BUFFERING_END log when user exit the playback.");
                    setBuffering(BUFFERING_ENOUGH);
                    sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_END, 0);
                    writeLog(MEDIA_LOG_BUFFER_END, MEDIA_LOG_LEVEL_INFO, NULL);
                }
            }

            sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_PREPARE_PROGRESS, 100);
            #if NET_CACHE_UNDERRUN
            if (HI_SUCCESS == HI_SVR_PLAYER_GetFileInfo(mHandle, &mpFileInfo)
                && (mpFileInfo->eSourceType == HI_FORMAT_SOURCE_NET_VOD
                    || mpFileInfo->eSourceType == HI_FORMAT_SOURCE_NET_LIVE))
            {
                setBuffering(BUFFERING_ENOUGH);
            }
            #endif
            mFirstPlay = false;
        }

        sp<surfaceSetting> mss = getSurfaceSetting();

        if (HI_SVR_PLAYER_INVALID_HDL == mss->getWindow())
        {
            HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hWin);
            mss->setWindow(hWin);
            mss->updateSurfacePosition();
        }
        LOGV("After updateSurfaceSetting");

        //if (mDiagnose)
        //{
        //    LOGV("set mBufEventControl to start");
        //    mSendBufEventLock.lock();
        //    mBufEventControl = BUF_EVENT_SEND;
        //    mSendBufEventLock.unlock();
        //}
    }

    return ret;
}

status_t HiMediaPlayer::stop()
{
    status_t ret = NO_ERROR;

    LOGV("[%s] Call HiMediaPlayer::stop IN ", STR_SWITCH_PG);
    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }

    ret = mCmdQueue->enqueueCommand(new CommandStop(mHandle, do_nothing));
    if (NO_ERROR == ret)
    {
        writeLog(MEDIA_LOG_STOP, MEDIA_LOG_LEVEL_INFO, NULL);
    }
    else
    {
        writeLog(MEDIA_LOG_STOP, MEDIA_LOG_LEVEL_ERROR, NULL);
    }

    return ret;
}

status_t HiMediaPlayer::seekTo(int position)
{
    status_t ret;
    LOGV("Call HiMediaPlayer::seekTo %d", position);
    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }

    if (mCmdQueue->mAppType == APP_TYPE_WASU)
    {
        mCmdQueue->mHuashuRequestSeekPoint = position;
        if (mCmdQueue->mIsIPTVTimeSeeking)
        {
            LOGV("now wasu is seeking");
            return NO_ERROR;
        }
    }

    #if NET_CACHE_UNDERRUN
    if (BUFFERING_IDLE == getBuffering()
        && HI_SUCCESS == HI_SVR_PLAYER_GetFileInfo(mHandle, &mpFileInfo)
        && (mpFileInfo->eSourceType == HI_FORMAT_SOURCE_NET_VOD || mpFileInfo->eSourceType == HI_FORMAT_SOURCE_NET_LIVE))
    {
        setBuffering(BUFFERING_ENOUGH);
    }
    #endif
    ret = mCmdQueue->enqueueCommand(new CommandSeek(mHandle, (position >= mPosition) ? position : -position));
    if (NO_ERROR == ret)
    {
        writeLog(MEDIA_LOG_SEEK_TO, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)(&position));
    }
    else
    {
        writeLog(MEDIA_LOG_SEEK_TO, MEDIA_LOG_LEVEL_ERROR, (HI_VOID *)(&position));
    }

    return ret;
}

status_t HiMediaPlayer::pause()
{
    status_t ret = NO_ERROR;

    LOGV("[%s] Call HiMediaPlayer::pause IN ", STR_SWITCH_PG);

    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    //if (mDiagnose)
    //{
    //    LOGV("set mBufEventControl to stop");
    //    mSendBufEventLock.lock();
    //    mBufEventControl = BUF_EVENT_NOT_SEND;
    //    mSendBufEventLock.unlock();
    //}

    ret = mCmdQueue->enqueueCommand(new CommandPause(mHandle));
    if (NO_ERROR == ret)
    {
        writeLog(MEDIA_LOG_PAUSE, MEDIA_LOG_LEVEL_INFO, NULL);
    }
    else
    {
        writeLog(MEDIA_LOG_PAUSE, MEDIA_LOG_LEVEL_ERROR, NULL);
    }

    return ret;
}

// Need Sync with other state changed operation
bool HiMediaPlayer::isPlaying()
{
    bool bIsPlaying = false;

    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    mCmdQueue->enqueueCommand(new CommandIsPlaying(mHandle, &bIsPlaying));

    return bIsPlaying;
}

status_t HiMediaPlayer::getCurrentPosition(int* position)
{
    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    status_t ret = mCmdQueue->enqueueCommand(new CommandGetPosition(mHandle, &mPosition));
    /* add for SHYD chinamobile weilaidianshi roll program */
    if (0 == mPosition)
    {
        mPosition = 1;
    }
    /* iptv end*/

    if (NULL != position)
        *position = mPosition;

    writeLog(MEDIA_LOG_CURRENT_PLAY_TIME, MEDIA_LOG_LEVEL_INFO, (HI_VOID *)(&mPosition));

    return ret;
}

status_t HiMediaPlayer::getDuration(int* duration)
{
    LOGV("HiMediaPlayer::getDuration()");
    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    status_t ret = NO_ERROR;

    if (mDuration > 0)
    {
        *duration = mDuration;
    }
    else
    {
        ret = mCmdQueue->enqueueCommand(new CommandGetDuration(mHandle, duration));
        mDuration = *duration;
    }

    return ret;
}

status_t HiMediaPlayer::reset()
{
    LOGV("[%s] Call HiMediaPlayer::reset() IN", STR_SWITCH_PG);
    int i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E eFormat = HI_UNF_FRAME_PACKING_TYPE_NONE;
    DisplayClient DspClient;

    writeLog(MEDIA_LOG_RESET, MEDIA_LOG_LEVEL_INFO, NULL);

    if (mstrReferer)
    {
        LOGV("delet referer setting");
        delete[] mstrReferer;
        mstrReferer = NULL;
    }

    if (mstrUserAgent)
    {
        LOGV("delet ua setting");
        delete[] mstrUserAgent;
        mstrUserAgent = NULL;
    }

    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    //quit huashu time seek thread
    mCmdQueue->mHuashuSeekQuit = true;

    if (mLooper != NULL)
    {
        const Message msg((int)LooperHandler::MSG_EXIT);
        LOGV("post message exit this:%p", this);
        mLooper->postMessage(mLooperHandle, msg, 0);
    }

    mReset = true;
    mCmdQueue->ReleaseFileInfoWrapper();
    destroyHiPlayer();

    if (mDiagnose)
    {
        LOGV("begin exit logger thread");
        if (mLogger != NULL)
        {
            mLogger->exit();
            mLogger = NULL;
        }

        LOGV("log exit has been called");
    }

    if (HI_UNF_WINDOW_FREEZE_MODE_BLACK == mWndFreezeMode
        && HI_INVALID_HANDLE != mWindow)
    {
        s32Ret = HI_UNF_VO_ResetWindow(mWindow, mWndFreezeMode);
        LOGV("Call HI_UNF_VO_ResetWindow ret = 0x%x ", s32Ret);
    }

    if (-1 != mPreOutputFormat)
    {
        LOGI("Reset to pre outputformat %d", mPreOutputFormat);
        DspClient.SetEncFmt(mPreOutputFormat);
    }

    LOGI("Reset to 2d");
    DspClient.SetStereoOutMode(OUTPUT_MODE_2D, 0);
    mDuration = 0;
    mPosition = 0;
    mPrepareAsync = false;
    mFirstPlay = true;
    mReset = false;
    mSubFramePackType = SUB_DEFAULT_FRAME_PACK;

    s32Ret = HI_UNF_AVPLAY_SetAttr(mAVPlayer, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, &eFormat);
    LOGV("Resume video frame pack type, ret = 0x%x ", s32Ret);

    // set static avplay resource no use
    {
        Mutex::Autolock lock(&HiMediaPlayer::mCreateAvplayMutex);
        for (i = 0; i < mAVPlayInstances.AvPlayCount; i++)
        {
            if (mAVPlayer == mAVPlayInstances.mAVPlays[i]->mAVPlayer)
            {
                mAVPlayInstances.mAVPlays[i]->setUse(false);
                mWindow = HI_INVALID_HANDLE;
                mAVPlayer = HI_INVALID_HANDLE;
                mAudioTrack = HI_INVALID_HANDLE;
                LOGV("set static avplay handle %x (idx %d) no use", mAVPlayInstances.mAVPlays[i]->mAVPlayer, i);
                break;
            }
        }

        LOGV("static avplay number is %d, max:%d", mAVPlayInstances.AvPlayCount, HIMEDIA_STATIC_AVPLAY_MAX_CNT);
    }

    return HI_SUCCESS;
}

inline status_t HiMediaPlayer::setLooping(int loop)
{
    LOGV("SetLooping loop[%d]", loop);
    mLoop = loop;
    return NO_ERROR;
}

// add volume adjust
 status_t HiMediaPlayer::setVolume(float leftVolume, float rightVolume)
{
    if (mVolumeLock == 1)
    {
        LOGV("SetVolume: No action due to mVolumeLock =%d", mVolumeLock);
        return NO_ERROR;
    }

    HI_HANDLE hdl = HI_SVR_PLAYER_INVALID_HDL;
    HI_UNF_SND_GAIN_ATTR_S stGain;
    HI_S32 s32Ret = HI_FAILURE;

    LOGV("SetVolume L-R [%4.2f  %4.2f]", leftVolume, rightVolume);

    HI_S32 left  = (HI_S32)(leftVolume*100);
    HI_S32 right = (HI_S32)(rightVolume*100);
    left     = (left  < 0  ) ? 0   : left;
    left     = (left  > 100) ? 100 : left;
    right    = (right < 0  ) ? 0   : right;
    right    = (right > 100) ? 100 : right;

    HI_S32 volume = (left+right) / 2;

    stGain.bLinearMode = HI_TRUE;
    stGain.s32Gain = volume;

    if (HI_INVALID_HANDLE == mAudioTrack)
    {
        s32Ret = HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hdl);
    }
    else
    {
        hdl = mAudioTrack;
        s32Ret = HI_SUCCESS;
    }

    if (HI_SUCCESS != s32Ret)
    {
        LOGE("ERR: get audio track hdl fail! \n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_SND_SetTrackWeight(hdl, &stGain);

    if (HI_SUCCESS != s32Ret)
    {
        LOGE("ERR: set volume failed! \n");
        return HI_FAILURE;
    }

    return NO_ERROR; //reserved, should return s32Ret in future
}

void HiMediaPlayer::setAudioSink(const sp<MediaPlayerBase::AudioSink> &audioSink)
{
    char value[PROPERTY_VALUE_MAX] = {0};

    LOGV("Call HiMediaPlayer::setAudioSink IN");

    if (property_get("ro.cts.enable", value, "false") && !strncasecmp("false", value, 5))
    {
        ALOGD("do not use audio sink output for hiplayer");
        return;
    }
    mASink = new HiASink(audioSink);
}

status_t HiMediaPlayer::suspend()
{
    LOGV("Call HiMediaPlayer::suspend() IN");
    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    return mCmdQueue->enqueueCommand(new CommandSuspend(mHandle));
}

status_t HiMediaPlayer::resume()
{
    LOGV("Call HiMediaPlayer::resume() IN");
    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    return mCmdQueue->enqueueCommand(new CommandResume(mHandle));
}

status_t HiMediaPlayer::SetStereoVideoFmt(int VideoFmt)
{
    LOGV("Call HiMediaPlayer::SetStereoVideoFmt IN");

    HI_S32 s32Ret = HI_SUCCESS;
    HI_HANDLE hAvPlayer = HI_INVALID_HANDLE;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E eFormat = HI_UNF_FRAME_PACKING_TYPE_NONE;
    HI_FORMAT_FILE_INFO_S *pstFileInfo  = NULL;
    HI_FORMAT_SUBTITLE_TYPE_E eSubType  = HI_FORMAT_SUBTITLE_BUTT;
    HI_FORMAT_PROGRAM_INFO_S *pstCurPrg = NULL;
    HI_SVR_PLAYER_STREAMID_S stStreamId;

    sp<subManager> msm = getSubManager();

    switch (VideoFmt)
    {
    case 0:
        eFormat = HI_UNF_FRAME_PACKING_TYPE_NONE;
        break;
    case 1:
        eFormat = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
        break;
    case 2:
        eFormat = HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM;
        break;
    default:
        eFormat = HI_UNF_FRAME_PACKING_TYPE_NONE;
        break;
    }

    HIMEDIA_DOFUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAvPlayer));

    if (HI_INVALID_HANDLE == hAvPlayer)
    {
        LOGV("Get AVPlay handle fail ");
        return UNKNOWN_ERROR;
    }

    LOGV("Set frame pack type is %d ", eFormat);

    s32Ret = HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId);
    s32Ret |= HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);

    if (HI_SUCCESS == s32Ret && NULL != pstFileInfo && stStreamId.u16ProgramId < pstFileInfo->u32ProgramNum)
    {
        pstCurPrg = &pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId];

        if (stStreamId.u16SubStreamId < pstCurPrg->u32SubStreamNum)
        {
            eSubType = (HI_FORMAT_SUBTITLE_TYPE_E)pstCurPrg->pastSubStream[stStreamId.u16SubStreamId].u32Format;
        }
    }

    LOGV("Current subtitle type is %d ", eSubType);

    if ((HI_FORMAT_SUBTITLE_HDMV_PGS == eSubType
        || HI_FORMAT_SUBTITLE_DVD_SUB == eSubType
        || HI_FORMAT_SUBTITLE_DVB_SUB == eSubType)
        && SUB_DEFAULT_FRAME_PACK == mSubFramePackType)
    {
        msm->clearLastBuffer();
        msm->setSubFramePackType(VideoFmt);
    }

    return HI_UNF_AVPLAY_SetAttr(hAvPlayer, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, &eFormat);
}

void HiMediaPlayer::SetStereoStrategy(int Strategy)
{
    LOGV("Call HiMediaPlayer::SetStereoStrategy IN, strategy is %d ", Strategy);

    mDisplayStrategy = Strategy;
}

int HiMediaPlayer::SetOrigAndroidPath(int flags)
{
    LOGV("TIMEDTEXT in HiMediaPlayer::SetOrigAndroidPath enter,set mOrigAndroidPath=%d",flags);
    switch (flags)
    {
        case 0:
            mOrigAndroidPath=false;
            break;
        case 1:
            mOrigAndroidPath=true;
            break;
    }

    return 0;
}

status_t  HiMediaPlayer::selectTrack(int trackIndex, bool select)
{
    bool bIsAudioTrack=false,bIsSubtitleTrack=false;
    int  nSubSelectidx = 0;
    if ( (trackIndex >= mTotalTrackCount) || (trackIndex <0) )
    {
        return BAD_INDEX;
    }

    LOGV("selectTrack, trackIndex=%d,mVideoTrackCount=%d,mAudioTrackCount=%d,mSubtitleTrackCount=%d,mTotalTrackCount=%d",trackIndex,mVideoTrackCount,mAudioTrackCount,mSubtitleTrackCount,mTotalTrackCount);


    if (trackIndex < mVideoTrackCount)
    {
        return INVALID_OPERATION;
    }
    else if (trackIndex < (mVideoTrackCount + mAudioTrackCount))
    {
        bIsAudioTrack = true;
        LOGV("set bIsAudioTrack=true");
    }
    else if (trackIndex < (mVideoTrackCount + mAudioTrackCount + mSubtitleTrackCount))
    {
        bIsSubtitleTrack =true;
        LOGV("set bIsSubtitleTrack =true");
    }
    else
    {
        return BAD_INDEX;
    }

    LOGV("HiMediaPlayer::selectTrack, trackIndex=%d,select=%d,bIsAudioTrack=%d,bIsSubtitleTrack=%d",
        trackIndex,select,bIsAudioTrack,bIsSubtitleTrack);

    if (bIsAudioTrack)
    {
        if (!select)
        {
            return INVALID_OPERATION;
        }
        else
        {
            return HiMediaPlayer::selectAudioTrack( (trackIndex -mVideoTrackCount));
        }
    }

    if (bIsSubtitleTrack)
    {
        if (!select)
        {
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            nSubSelectidx = trackIndex - mVideoTrackCount - mAudioTrackCount;
            if (HI_SUCCESS == HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId))
            {
                LOGV("current sub idx is %d. to unselect idx is %d",stStreamId.u16SubStreamId, nSubSelectidx);
                if (stStreamId.u16SubStreamId != nSubSelectidx)
                {
                    LOGE("current sub idx is not equal to unselect idx.");
                    return INVALID_OPERATION;
                }
            }
            else
            {
                LOGE("unselect sub,get playinfo fail");
                return INVALID_OPERATION;
            }
            mIsTimedTextTrackEnable = false;
        }
        else
        {
            mIsTimedTextTrackEnable = true;
            return HiMediaPlayer::selectSubtitleTrack((trackIndex-mVideoTrackCount-mAudioTrackCount));
        }
    }

    return NO_ERROR;
}

status_t HiMediaPlayer::selectAudioTrack(int AudIndex)
{
    LOGV("HiMediaPlayer::selectAudioTrack, audio track=%d,mAudioTrackCount=%d",AudIndex,mAudioTrackCount);

    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_SVR_PLAYER_STREAMID_S PlayerStreamID;

    if (mHandle !=NULL)
    {
        HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID);
        HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);
    }

    if (NULL == pstFileInfo)
    {
        LOGE("ERROR!!!!!!! HI_SVR_PLAYER_GetFileInfo error! ");
        return HI_FAILURE;
    }

    PlayerStreamID.u16AudStreamId = AudIndex;
    if (HI_SUCCESS != HI_SVR_PLAYER_SetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID))
    {
        LOGE("ERROR!!!!HI_SVR_PLAYER_SetParam fail");
        return HI_FAILURE;
    }

    LOGV("end of audio select track");

    return NO_ERROR;
}

status_t HiMediaPlayer::selectSubtitleTrack(int SubIndex)
{
    LOGV("HiMediaPlayer::selectSubtitleTrack, SubIndex=%d",SubIndex);

    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_U32 s32SubtitleNum;

    HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId);

    //current play track is the same with SubIndex
    if ( SubIndex == stStreamId.u16SubStreamId )
    {
        return NO_ERROR;
    }

    HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);
    if ( pstFileInfo == NULL )
    {
        LOGE("ERROR!!!!! HI_SVR_PLAYER_GetFileInfo pstFileInfo=NULL");
        return HI_FAILURE;
    }

    if (stStreamId.u16ProgramId < pstFileInfo->u32ProgramNum)
    {
        s32SubtitleNum = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum;
        if (SubIndex < s32SubtitleNum)//check the value is valid
        {
            stStreamId.u16SubStreamId = SubIndex;
            if(HI_SUCCESS != HI_SVR_PLAYER_SetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId))
            {
                LOGE("ERROR!!!!!!HI_SVR_PLAYER_SetParam error, switch subtitle fail");
                return HI_FAILURE;
            }
            else
            {
                mCmdQueue->wait();
                return NO_ERROR;
            }
        }
        else
        {
            LOGE("ERROR!!!!!! invalid sub idx, switch subtitle fail");
            return HI_FAILURE;
        }
    }
    else
    {
        LOGE("ERROR!!!!!! invalid program id, switch subtitle fail");
        return HI_FAILURE;
    }

    LOGV("selectSubtitleTrack done");
    return NO_ERROR;
}

status_t HiMediaPlayer::AddTimedTextSource(const Parcel& request)
{
    int fd = request.readFileDescriptor();
    off64_t offset = request.readInt64();
    off64_t length  = request.readInt64();
    String8 mimeType(request.readString16());

    char filename_proc[PATH_MAX] = {0};
    char filePath[PATH_MAX] = {0};
    char filename[PATH_MAX] = {0};
    char value[PROPERTY_VALUE_MAX] = {0};
    snprintf(filename_proc, PATH_MAX, "/proc/%ld/fd/%d", (long)getpid(), fd);
    if (readlink(filename_proc, filePath, PATH_MAX) < 0) {
        LOGE("TIMEDTEXT Get file name failed!");
    }

    memset(filename, 0, PATH_MAX);
    if (property_get("ro.cts.enable", value, "false") && !strncasecmp("false", value, 5))
    {
        snprintf(filename, HI_FORMAT_MAX_URL_LEN - 1,
            "%s%s%lld%s%lld",
            filePath, SEPARATE_SYMBOL_OFFSET, offset, SEPARATE_SYMBOL_LENGTH, length);
    }
    else
    {
        snprintf(filename, HI_FORMAT_MAX_URL_LEN - 1,
            "%s%s%lld%s%lld%s%d",
            filePath, SEPARATE_SYMBOL_OFFSET, offset, SEPARATE_SYMBOL_LENGTH, length, SEPARATE_SYMBOL_FD, fd);
    }

    LOGV("TIMEDTEXT in AddTimedTextSource,filepath=%s,mimeType=%s", filename,(const char *)mimeType);

    if (filePath != NULL)
    {
        if (mIsPrepared)
        {
            AddExtTimedTextStream(filename);
        }
        else
        {
            mTimedTextStringArray.push_back(filename);
        }
    }

    return NO_ERROR;
}

int HiMediaPlayer::AddExtTimedTextStream(const char *pTimedTextFilePath)
{
    if (pTimedTextFilePath != NULL)
    {
        LOGV("TIMEDTEXT in AddExtTimedTextStream,pTimedTextFilePath=%s",pTimedTextFilePath);

        HI_SVR_PLAYER_MEDIA_S stMedia;

        memset(&stMedia, 0, sizeof(stMedia));
        sprintf(stMedia.aszExtSubUrl[0], "%s", pTimedTextFilePath);
        stMedia.u32ExtSubNum = 1;

        if (mHandle != NULL)
        {
            HI_SVR_PLAYER_SetMedia(mHandle, HI_SVR_PLAYER_MEDIA_SUBTITLE, &stMedia);
            LOGV("TIMEDTEXT in HiMediaPlayer::AddExtTimedTextStream, HI_SVR_PLAYER_SetMedia done");
        }

        LOGV("[TIMEDTEXT AddExtTimedTextStream]subpath:%s,hPlayer : %x",stMedia.aszExtSubUrl[0], mHandle);
        return 0;
    }

    return 0;
}

status_t HiMediaPlayer::setSubFramePack(int type)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_HANDLE hAvPlayer = HI_INVALID_HANDLE;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E eFormat = HI_UNF_FRAME_PACKING_TYPE_NONE;
    HI_FORMAT_FILE_INFO_S *pstFileInfo  = NULL;
    HI_FORMAT_SUBTITLE_TYPE_E eSubType  = HI_FORMAT_SUBTITLE_BUTT;
    HI_FORMAT_PROGRAM_INFO_S *pstCurPrg = NULL;
    HI_SVR_PLAYER_STREAMID_S stStreamId;

    mSubFramePackType = type;

    s32Ret = HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId);
    s32Ret |= HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);

    if (HI_SUCCESS == s32Ret && NULL != pstFileInfo && stStreamId.u16ProgramId < pstFileInfo->u32ProgramNum)
    {
        pstCurPrg = &pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId];

        if (stStreamId.u16SubStreamId < pstCurPrg->u32SubStreamNum)
        {
            eSubType = (HI_FORMAT_SUBTITLE_TYPE_E)pstCurPrg->pastSubStream[stStreamId.u16SubStreamId].u32Format;
        }
    }

    LOGV("Current subtitle type is %d ", eSubType);

    if (!(HI_FORMAT_SUBTITLE_HDMV_PGS == eSubType
        || HI_FORMAT_SUBTITLE_DVD_SUB == eSubType
        || HI_FORMAT_SUBTITLE_DVB_SUB == eSubType))
    {
        LOGV("Current subtitle type is not graphic, not set submanager ");
        return NO_ERROR;
    }

    HIMEDIA_DOFUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAvPlayer));
    HIMEDIA_DOFUNC_RET(HI_UNF_AVPLAY_GetAttr(hAvPlayer, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, &eFormat));

    sp<subManager> msm = getSubManager();

    switch (mSubFramePackType)
    {
    case SUB_DEFAULT_FRAME_PACK:
        /* auto recognize, we set subtitle frame pack as video frame pack type */
        if (HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE == eFormat)
        {
            msm->clearLastBuffer();
            msm->setSubFramePackType(1);
        }
        else if (HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM == eFormat)
        {
            msm->clearLastBuffer();
            msm->setSubFramePackType(2);
        }
        else
        {
            msm->clearLastBuffer();
            msm->setSubFramePackType(0);
        }
        break;
    case 0:
    case 1:
    case 2:
    default:
        /* subtitle is normal 2d, sbs or tab subtitle */
        msm->clearLastBuffer();
        msm->setSubFramePackType(mSubFramePackType);
        break;
    }

    return NO_ERROR;
}

status_t HiMediaPlayer::getTrackInfo(Parcel* reply)
{
    int trackcount=0,i=0;
    mTotalTrackCount = 0;
    const char *lang;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_FORMAT_FILE_INFO_S *pstFileInfo  = NULL;
    HI_U32 s32SubtitleNum,s32VideoNum,s32AudioNum;

    // After on_prepared state, we could get mHandle.
    if (mHandle== NULL)
    {
        LOGE("mHandle == NULL, mplayer didnt prepare");
        return NO_ERROR;
    }

    CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

    if (HI_SUCCESS != HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo))
    {
        LOGE("HI_SVR_PLAYER_GetFileInfo fail");
        return NO_ERROR;
    }
    if (NULL == pstFileInfo)
    {
        LOGE("in HiMediaPlayer::getTrackInfo error, pstFileInfo == NULL");
        return NO_ERROR;
    }

    s32SubtitleNum = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum;
    s32VideoNum = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32VidStreamNum;
    s32AudioNum = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum;
    trackcount = s32SubtitleNum + s32VideoNum + s32AudioNum;
    mTotalTrackCount = trackcount;
    mSubtitleTrackCount = s32SubtitleNum;
    mVideoTrackCount = s32VideoNum;
    mAudioTrackCount = s32AudioNum;

    reply->writeInt32(trackcount);

    for(i=0;i<s32VideoNum;i++)
    {
        reply->writeInt32(2);  //means 2 element
        reply->writeInt32(MEDIA_TRACK_TYPE_VIDEO);
        lang = "und";
        reply->writeString16(String16(lang));
    }
    for(i=0;i<s32AudioNum;i++)
    {
        reply->writeInt32(2);
        reply->writeInt32(MEDIA_TRACK_TYPE_AUDIO);
        lang=pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[i].aszLanguage;
        reply->writeString16(String16(lang));
    }
    for(i=0;i<s32SubtitleNum;i++)
    {
        reply->writeInt32(2);
        reply->writeInt32(MEDIA_TRACK_TYPE_TIMEDTEXT);
        lang=(char*)(pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[i].paszLanguage);
        if (0 == strlen(lang))
        {
            lang = "und";
        }
        reply->writeString16(String16(lang));
    }
    return NO_ERROR;
}

status_t HiMediaPlayer::getAudioCodecFormat(HI_S32 s32AudioFormat, HI_CHAR * pszAudioCodec)
{
    switch(s32AudioFormat) //refer to MediaDef.cpp and hi_audio_code.h
    {
        case FORMAT_MP2:
        case FORMAT_MP3:
            sprintf(pszAudioCodec, "audio/mpeg");
            break;
        case FORMAT_AAC:
            sprintf(pszAudioCodec, "audio/mp4a-latm");
            break;
        case FORMAT_AMR_NB:
            sprintf(pszAudioCodec, "audio/3gpp");
            break;
        case FORMAT_AMR_WB:
        case FORMAT_AMR_AWB:
            sprintf(pszAudioCodec, "audio/amr-wb");
            break;
        case FORMAT_FLAC:
            sprintf(pszAudioCodec, "audio/flac");
            break;
        case FORMAT_WMAV1:
        case FORMAT_WMAV2:
            sprintf(pszAudioCodec, "audio/x-wav");
            break;
        case FORMAT_VORBIS:
            sprintf(pszAudioCodec, "audio/vorbis");
            break;
        case FORMAT_GSM_MS:
            sprintf(pszAudioCodec, "audio/gsm");
            break;
        case FORMAT_QCELP:
            sprintf(pszAudioCodec, "audio/qcelp");
            break;
        case FORMAT_AC3:
            sprintf(pszAudioCodec, "audio/ac3");
            break;
        default:
            sprintf(pszAudioCodec, "%d", s32AudioFormat);
            break;
    }
    return NO_ERROR;
}

status_t HiMediaPlayer::getVideoCodecFormat(HI_S32 s32VideoFormat, HI_CHAR * pszVideoCodec)
{
    switch(s32VideoFormat) //refer to MediaDef.cpp and hi_svr_codec.h
    {
        case HI_FORMAT_VIDEO_VP8:
            sprintf(pszVideoCodec, "video/x-vnd.on2.vp8");
            break;
        case HI_FORMAT_VIDEO_H264:
            sprintf(pszVideoCodec, "video/avc");
            break;
        case HI_FORMAT_VIDEO_MPEG4:
        case HI_FORMAT_VIDEO_MSMPEG4V1:
        case HI_FORMAT_VIDEO_MSMPEG4V2:
            sprintf(pszVideoCodec, "video/mp4");
            break;
        case HI_FORMAT_VIDEO_H263:
            sprintf(pszVideoCodec, "video/h263");
            break;
        case HI_FORMAT_VIDEO_MPEG2:
            sprintf(pszVideoCodec, "video/mpeg2");
            break;
        case HI_FORMAT_VIDEO_VC1:
            sprintf(pszVideoCodec, "video/x-ms-wm");
            break;
        case HI_FORMAT_VIDEO_REAL8:
        case HI_FORMAT_VIDEO_REAL9:
            sprintf(pszVideoCodec, "video/rn-realmedia");
            break;
        case HI_FORMAT_VIDEO_RAW:
            sprintf(pszVideoCodec, "video/raw");
            break;
        default:
            sprintf(pszVideoCodec, "%d", s32VideoFormat);
            break;
    }
    return NO_ERROR;
}

status_t HiMediaPlayer::transStringcode(HI_CHAR * ps8In, HI_S32 s32InLen, HI_CHAR * ps8Out, HI_S32 * ps32OutLen)
{
    HI_S32 s32Ret = NO_ERROR;
    HI_S32 s32CodeType = 0;//SVR_SUB_CODETYPE_UNKNOW;
    HI_CHARSET_FUN_S * pstCharsetMgr = &g_stCharsetMgr_s;
    HI_S32 usedlen = 0;

    if (ps8Out != NULL &&
       pstCharsetMgr != NULL &&
       pstCharsetMgr->Create != NULL &&
       pstCharsetMgr->Destroy != NULL)
    {
        HI_HANDLE _CharsetMgrHandler = (HI_HANDLE)NULL;

        s32Ret = pstCharsetMgr->Create(&_CharsetMgrHandler, 0);

        if (s32Ret == HI_SUCCESS)
        {
            s32Ret = pstCharsetMgr->IdentStream(_CharsetMgrHandler, (HI_U8 *)ps8In, s32InLen, 0, &s32CodeType);

            if (s32Ret == HI_SUCCESS)
            {
                s32Ret = pstCharsetMgr->ConvStream(_CharsetMgrHandler, (HI_U8 *)ps8Out, ps32OutLen,
                                         (HI_U8 *)ps8In, s32InLen, s32CodeType, 2, &usedlen);
                if (s32Ret == HI_SUCCESS)
                    LOGV("transStringcode, out: %s, codetype = %d\n", ps8Out, s32CodeType);
                else
                    LOGV("fail to convstream");
            }
            else
            {
                LOGV("fail to ident stream");
            }
        }
        else
        {
            LOGV("fail to create charset manager handler");
        }

        if (_CharsetMgrHandler)
        {
            pstCharsetMgr->Destroy(_CharsetMgrHandler);
            _CharsetMgrHandler = (HI_HANDLE)NULL;
        }
    }
    else
    {
        LOGV("transStringcode fail");
    }

    return s32Ret;
}

status_t HiMediaPlayer::getMetadata(const media::HiMetadata::Filter& ids, Parcel *records)
{
    using media::HiMetadata;
    HiMetadata metadata(records);

    const HI_CHAR *pszTmp  = "";
    const HI_CHAR *pszYear   = "";
    HI_S32 s32BitRate = 0;
    HI_S32 s32AudioSampleRate = 0;
    HI_S32 s32CdTrackNum = 0;
    HI_U32 i = 0;

    HI_SVR_PLAYER_METADATA_S pArg;// = {0};
    memset(&pArg, 0x00, sizeof(HI_SVR_PLAYER_METADATA_S));

    if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_METADATA, &pArg))
    {
        return HI_FAILURE;
    }

    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;

    if (HI_SUCCESS == HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo))
    {
        if (NULL == pstFileInfo)
        {
            LOGE("HI_SVR_PLAYER_GetFileInfo fail!");
        }
        else
        {
             HI_CHAR pszAudioCodec[HI_FORMAT_TITLE_MAX_LEN];
             HI_CHAR pszVideoCodec[HI_FORMAT_TITLE_MAX_LEN];
             HI_S32 s32AudioFormat = -1;
             HI_S32 s32VideoFormat = -1;
             HI_S64 s64Duration = 0;
             HI_S32 s32CdTrackMax = 0;
             HI_S32 s32CdTrackNum = 0;
             HI_S32 s32NumTracks = 0;

             //NumTracks, int
             s32NumTracks = pstFileInfo->pastProgramInfo[0].u32AudStreamNum +
                            pstFileInfo->pastProgramInfo[0].u32VidStreamNum +
                            pstFileInfo->pastProgramInfo[0].u32SubStreamNum;
             metadata.appendInt32(HiMetadata::kNumTracks, s32NumTracks);

             //BitRate, int
             metadata.appendInt32(HiMetadata::kBitRate, pstFileInfo->u32Bitrate);

             //audio codec
             if (pstFileInfo->pastProgramInfo[0].u32AudStreamNum > 0)
             {
                 s32AudioFormat = pstFileInfo->pastProgramInfo[0].pastAudStream[0].u32Format;

                 getAudioCodecFormat(s32AudioFormat, pszAudioCodec);

                 String16 *str16AudioCodec = new String16(pszAudioCodec, strlen(pszAudioCodec));
                 metadata.AppendStringMeta(HiMetadata::kAudioCodec, *str16AudioCodec);
             }
             LOGV("audio format = %d\n", s32AudioFormat);

             if (pstFileInfo->pastProgramInfo[0].u32VidStreamNum > 0)
             {
                 //video codec
                 s32VideoFormat = pstFileInfo->pastProgramInfo[0].pastVidStream[0].u32Format;
                 getVideoCodecFormat(s32VideoFormat, pszVideoCodec);
                 String16 *str16VideoCodec = new String16(pszVideoCodec, strlen(pszVideoCodec));
                 metadata.AppendStringMeta(HiMetadata::kVideoCodec, *str16VideoCodec);

                 if (NULL != str16VideoCodec)
                 {
                     delete(str16VideoCodec);
                     str16VideoCodec = NULL;
                 }

                 HI_U16 u16VideoHeight = 0;
                 HI_U16 u16VideoWidth = 0;
                 HI_U16 u16VideoFramerate1 = 0;
                 HI_U16 u16VideoFramerate2 = 0;
                 HI_U32 u32VideoBitrate = 0;

                 u16VideoHeight = pstFileInfo->pastProgramInfo[0].pastVidStream[0].u16Height;
                 u16VideoWidth = pstFileInfo->pastProgramInfo[0].pastVidStream[0].u16Width;
                 u16VideoFramerate1 = pstFileInfo->pastProgramInfo[0].pastVidStream[0].u16FpsInteger;
                 u16VideoFramerate2 = pstFileInfo->pastProgramInfo[0].pastVidStream[0].u16FpsDecimal;
                 u32VideoBitrate = pstFileInfo->pastProgramInfo[0].pastVidStream[0].u32Bitrate;

                 if(u16VideoHeight > 0)
                     metadata.appendInt32(HiMetadata::kVideoHeight, u16VideoHeight);
                 if(u16VideoWidth)
                     metadata.appendInt32(HiMetadata::kVideoWidth, u16VideoWidth);
                 if(u16VideoFramerate1 > 0)
                     metadata.appendInt32(HiMetadata::kVideoframeRate, u16VideoFramerate1);
                 if(u32VideoBitrate > 0)
                     metadata.appendInt32(HiMetadata::kVideoBitRate, u32VideoBitrate);

                 //LOGV("video format = %d\n", s32VideoFormat);
                 //LOGV("video height = %d\n", u16VideoHeight);
                 //LOGV("video width = %d\n", u16VideoWidth);
                 //LOGV("video framerate = %d.%d\n", u16VideoFramerate1, u16VideoFramerate2);
                 //LOGV("video bitrate = %d\n", u32VideoBitrate);
            }
             //duration
             s64Duration = pstFileInfo->s64Duration;
             if(s64Duration > 0)
                 metadata.appendInt32(HiMetadata::kDuration, (HI_S32)s64Duration);

             //LOGV("duration = %lld\n", s64Duration);

             //MimeType, string
             String16 *str16MimeType = new String16(pstFileInfo->aszFileFormat, strlen(pstFileInfo->aszFileFormat));
             metadata.AppendStringMeta(HiMetadata::kMimeType, *str16MimeType);
        }
    }

    HI_SVR_PLAYERKVP_S *pstKvp = pArg.pstKvp;
    HI_CHAR * ps8Out = NULL;
    HI_S32 s32OutLen = 0;
    HI_S32 s32Ret;

    for (i = 0; i < pArg.u32KvpUsedNum; i++)
    {

        //LOGV("key = %s\n", pstKvp[i].pszKey);
        if (!strcmp(pstKvp[i].pszKey, "album") ||
            !strcmp(pstKvp[i].pszKey, "title") ||
            !strcmp(pstKvp[i].pszKey, "artist") ||
            !strcmp(pstKvp[i].pszKey, "genre") ||
            !strcmp(pstKvp[i].pszKey, "composer") ||
            !strcmp(pstKvp[i].pszKey, "author") ||
            !strcmp(pstKvp[i].pszKey, "copyright") ||
            !strcmp(pstKvp[i].pszKey, "comment") ||
            !strcmp(pstKvp[i].pszKey, "rating") ||
            !strcmp(pstKvp[i].pszKey, "year") ||
            !strcmp(pstKvp[i].pszKey, "data")    )
        {
            s32OutLen = strlen(pstKvp[i].unValue.pszValue) * 4 + 2;
            ps8Out = new HI_CHAR[s32OutLen];

            s32Ret = transStringcode(pstKvp[i].unValue.pszValue, strlen(pstKvp[i].unValue.pszValue), ps8Out, &s32OutLen);
            if(s32Ret == NO_ERROR)
                pszTmp = ps8Out;
            else
                pszTmp = pstKvp[i].unValue.pszValue;

            String16 *str16Tmp = new String16(pszTmp, strlen(pszTmp));

            if (NULL == str16Tmp)
                break;

            if (!strcmp(pstKvp[i].pszKey, "album"))
                metadata.AppendStringMeta(HiMetadata::kAlbum, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "title"))
                metadata.AppendStringMeta(HiMetadata::kTitle, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "artist"))
                metadata.AppendStringMeta(HiMetadata::kArtist, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "genre"))
                metadata.AppendStringMeta(HiMetadata::kGenre, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "composer"))
                metadata.AppendStringMeta(HiMetadata::kComposer, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "author"))
                metadata.AppendStringMeta(HiMetadata::kAuthor, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "copyright"))
                metadata.AppendStringMeta(HiMetadata::kCopyright, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "comment"))
                metadata.AppendStringMeta(HiMetadata::kComment, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "rating"))
                metadata.AppendStringMeta(HiMetadata::kRating, *str16Tmp);
            else if(!strcmp(pstKvp[i].pszKey, "year") || !strcmp(pstKvp[i].pszKey, "data"))
                metadata.AppendStringMeta(HiMetadata::kDate, *str16Tmp);

            //LOGV("key : %s, value: %s\n", pstKvp[i].pszKey, pszTmp);

            if (NULL != str16Tmp)
            {
                delete(str16Tmp);
                str16Tmp = NULL;
            }

            if (ps8Out != NULL)
            {
                delete [] ps8Out;
                ps8Out = NULL;
            }
        }
        else if (!strcmp(pstKvp[i].pszKey, "track-info\/audio\/bit-rate") ||
                 !strcmp(pstKvp[i].pszKey, "codec-info\/audio\/sample-rate") ||
                 !strcmp(pstKvp[i].pszKey, "track"))
        {
            if (!strcmp(pstKvp[i].pszKey, "track-info\/audio\/bit-rate"))
            {
                metadata.appendInt32(HiMetadata::kAudioBitRate, pstKvp[i].unValue.s32Value);
            }
            else if (!strcmp(pstKvp[i].pszKey, "codec-info\/audio\/sample-rate"))
            {
                metadata.appendInt32(HiMetadata::kAudioSampleRate, pstKvp[i].unValue.s32Value);
            }
            else if (!strcmp(pstKvp[i].pszKey, "track"))
            {
                metadata.appendInt32(HiMetadata::kCdTrackNum, pstKvp[i].unValue.s32Value);
            }
            //LOGV(" %s: %d \n", pstKvp[i].pszKey, pstKvp[i].unValue.s32Value);
        }
        /* need to fix the path of parcel deliver
        else if(!strncmp("APIC", pstKvp[i].pszKey, strlen("APIC"))) //AlbumArt
        {
             HI_U32 u32Len = pstKvp[i].u32ValueNum;

             HI_CHAR * pu8Img = new HI_CHAR[u32Len];

             memcpy(pu8Img, pstKvp[i].unValue.pszValue, u32Len);

             metadata.AppendByteMeta(HiMetadata::kAlbumArt, pu8Img, u32Len);

             if(NULL != pu8Img)
            {
                 delete [] pu8Img;
                 pu8Img = NULL;
            }
             LOGV("key %s: len %d \n", pstKvp[i].pszKey, u32Len);
        }*/
    }

    return NO_ERROR;
}

status_t HiMediaPlayer::DealPreInvokeSetting(const Parcel& request, Parcel *reply, int& HasDeal)
{
    int utf8UASize = 0, utf8RefSize = 0;
    cmd_type_e cmd_type = (cmd_type_e)request.readInt32();

    if (CMD_SET_USER_AGENT == cmd_type)
    {
        HasDeal = 1;
        String16 strUA16 = request.readString16();
        if (NULL != strUA16.string() && 0 < strUA16.size())
        {
            utf8UASize = utf16_to_utf8_length(strUA16.string(), strUA16.size());
            LOGV("ua utf8size is %d",utf8UASize);

            if (mstrUserAgent)
            {
                delete[] mstrUserAgent;
                mstrUserAgent = NULL;
            }

            mstrUserAgent = new char[utf8UASize + 1];

            if (NULL != mstrUserAgent)
            {
                memset(mstrUserAgent, 0, utf8UASize + 1);
                utf16_to_utf8(strUA16.string(), strUA16.size(), mstrUserAgent);
                LOGV("ua is %s", mstrUserAgent);
                LOGV("ua len is %d", strlen(mstrUserAgent));
            }
            else
            {
                LOGE("alloc useragent mem fail");
                reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }
        }
        else
        {
            LOGE("ua info is invalid,maybe NULL or len is 0");
            reply->writeInt32(UNKNOWN_ERROR);
            return UNKNOWN_ERROR;
        }
        reply->writeInt32(NO_ERROR);
        return NO_ERROR;
    }
    else if (CMD_SET_REFERER == cmd_type)
    {
        HasDeal = 1;
        String16 strRef16 = request.readString16();
        if (NULL != strRef16.string() && 0 < strRef16.size())
        {
            utf8RefSize = utf16_to_utf8_length(strRef16.string(), strRef16.size());
            LOGV("Referer utf8RefSize is %d",utf8RefSize);

            if (mstrReferer)
            {
                delete[] mstrReferer;
                mstrReferer = NULL;
            }

            mstrReferer = new char[utf8RefSize + 1];

            if (NULL != mstrReferer)
            {
                memset(mstrReferer, 0, utf8RefSize + 1);
                utf16_to_utf8(strRef16.string(), strRef16.size(), mstrReferer);
                LOGV("Referer is %s", mstrReferer);
                LOGV("Referer len is %d", strlen(mstrReferer));
            }
            else
            {
                LOGE("alloc Referer mem fail");
                reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }
        }
        else
        {
            LOGE("Referer info is invalid,maybe NULL or len is 0");
            reply->writeInt32(UNKNOWN_ERROR);
            return UNKNOWN_ERROR;
        }
        reply->writeInt32(NO_ERROR);
        return NO_ERROR;
    }
    else if (CMD_SET_NOT_SUPPORT_BYTERANGE == cmd_type)
    {
        LOGE("not support byte range");
        HasDeal = 1;
        mIsNotSupportByteRange = request.readInt32();
        reply->writeInt32(NO_ERROR);
        return NO_ERROR;
    }
    else if(CMD_SET_VIDEO_SURFACE_OUTPUT == cmd_type)
    {
        HasDeal = 1;
        mNonVSink = true;

        if (NULL != reply)
        {
            reply->writeInt32(NO_ERROR);
        }
        return NO_ERROR;
    }
    else if (CMD_SET_3D_STRATEGY == cmd_type)
    {
        HasDeal = 1;
        int Strategy = request.readInt32();
        LOGV("[CMD_SET_3D_STRATEGY] Strategy = %d",Strategy);
        SetStereoStrategy(Strategy);
        reply->writeInt32(NO_ERROR);
    }
    else if (CMD_SET_SUB_SURFACE == cmd_type)
    {
        HasDeal = 1;
        if (NO_ERROR == setSubtitleNativeWindow(request))
        {
            reply->writeInt32(NO_ERROR);
        }
        else
        {
            reply->writeInt32(UNKNOWN_ERROR);
        }
    }

    char soft_detector[PROPERTY_VALUE_MAX] = {0};
    if (property_get("persist.sys.softdetector.enable", soft_detector, "false") && strcmp("true", soft_detector)== 0)
    {
        if (CMD_GET_MEDIA_URL == cmd_type)
        {
            if (NULL != reply)
            {
                reply->writeString16(String16(mMediaParam.aszUrl));
            }
        }
    }

    return NO_ERROR;
}

status_t HiMediaPlayer::invoke(const Parcel& request, Parcel *reply)
{
    int HasPreDeal = 0;
    int Ret = NO_ERROR;

    int CurrentPos = request.dataPosition();
    Ret = DealPreInvokeSetting(request, reply, HasPreDeal);
    request.setDataPosition(CurrentPos);

    if (HasPreDeal)
    {
        return Ret;
    }

    if(NULL == mCmdQueue.get())
    {
        LOGV("mCmdQueue is NULL,execute command return");
        return NO_ERROR;
    }
    return mCmdQueue->enqueueCommand(new CommandInvoke(mHandle, (Parcel*)&request, reply));
}

status_t HiMediaPlayer::setNativeWindow_l(const sp<ANativeWindow> &native) {

    HI_S32 ret;
    int FromSurfaceFlinger = 1;
    char value[PROPERTY_VALUE_MAX] = {0};
    /*if use video layer to display, push a blank buffer to clear last frame*/
    if (!IsUseVsinkWindow() && NULL != native.get())
    {
        native->query(native.get(),
            NATIVE_WINDOW_QUEUES_TO_WINDOW_COMPOSER, &FromSurfaceFlinger);
        LOGV("if FromSurfaceFlinger %d",FromSurfaceFlinger);

        if (1 == FromSurfaceFlinger)
        {
            pushBlankBuffersToNativeWindow(native);
            setSubSurface(native.get(), 0);
        }
    }

    if (property_get("service.media.hiplayer.graphic", value, "false") && !strcasecmp("false", value))
    {
        return OK;
    }

    ALOGD("already has a vsink, destroy and recreate vsink");
    sp<HiVSink> newVsink = new HiVSink(0);
    newVsink->setNativeWindow(native);

    /*reset vsink into player*/
    HI_SVR_VSINK_S* pstVSink = dynamic_cast<HI_SVR_VSINK_S*>(newVsink.get());
    ALOGD("Going to set VSINK:%p", pstVSink);

    if (mCmdQueue.get() == NULL)
    {
        ALOGD("command queue has not created, set vsink directly");
        mVSink = newVsink;
        mNativeWindow = native;
        return OK;
    }

    ret = mCmdQueue->enqueueCommand(new CommandSetVsink(mHandle, mVSink, newVsink, do_nothing));

    if (NO_ERROR == ret)
    {
        ALOGD("reset vsink done");
        mVSink = newVsink;
        mNativeWindow = native;
        return OK;
    }

    ALOGE("reset vsink failed");
    return UNKNOWN_ERROR;
}

status_t HiMediaPlayer::getParameter(int key, Parcel *reply)
{
    switch(key)
    {
        case KEY_PARAMETER_AUDIO_CHANNEL_COUNT:
        {
            Parcel Request, ReplyHimedia;
            int AudioCount = 0;
            Request.setDataPosition(0);
            Request.writeInt32(CMD_GET_AUDIO_INFO);
            Request.setDataPosition(0);
            HIMEDIA_NULL_VERIFY(mCmdQueue.get());
            HIMEDIA_NULL_VERIFY(mHandle);
            HIMEDIA_DOHIMEDIAFUNC_RET(mCmdQueue->enqueueCommand(new CommandInvoke(mHandle, (Parcel*)&Request, &ReplyHimedia)));
            ReplyHimedia.setDataPosition(0);
            HIMEDIA_DOHIMEDIAFUNC_RET(ReplyHimedia.readInt32());
            AudioCount = ReplyHimedia.readInt32();
            LOGV("AudioCount is %d",AudioCount);
            reply->writeInt32(AudioCount);
            break;
        }
        default:
        {
            LOGE("get param,do not support key %d", key);
            return UNKNOWN_ERROR;
        }
    }
    return NO_ERROR;
}

status_t HiMediaPlayer::setParameter(int key, const Parcel &request)
{
    switch(key)
    {
        case KEY_PARAMETER_PLAYBACK_RATE_PERMILLE:
        {
            const int BASE_SPEED = 1000;
            Parcel Request, ReplyHimedia;
            request.setDataPosition(0);
            int speed = request.readInt32();
            HIMEDIA_NULL_VERIFY(mCmdQueue.get());
            HIMEDIA_NULL_VERIFY(mHandle);

            if (0 != speed % BASE_SPEED)
            {
                LOGE("do not support the speed %d", speed);
                return UNKNOWN_ERROR;
            }

            if (speed == BASE_SPEED)
            {
                Request.writeInt32(CMD_SET_STOP_FASTPLAY);
                LOGV("resume play");
            }
            else if (speed > 0)
            {
                Request.writeInt32(CMD_SET_FORWORD);
                Request.writeInt32(speed / BASE_SPEED);
                LOGV("ff rate is %d", (speed / BASE_SPEED));
            }
            else if (speed <0)
            {
                speed = -speed;
                Request.writeInt32(CMD_SET_REWIND);
                Request.writeInt32(speed / BASE_SPEED);
                LOGV("rw rate is %d", (speed / BASE_SPEED));
            }

            Request.setDataPosition(0);
            HIMEDIA_DOHIMEDIAFUNC_RET(mCmdQueue->enqueueCommand(new CommandInvoke(mHandle, (Parcel*)&Request, &ReplyHimedia)));
            ReplyHimedia.setDataPosition(0);
            HIMEDIA_DOHIMEDIAFUNC_RET(ReplyHimedia.readInt32());
            break;
        }
        case KEY_PARAMETER_CACHE_STAT_COLLECT_FREQ_MS:
        {
            request.setDataPosition(0);
            int CollectFreq = request.readInt32();
            LOGV("collect freq is %d",CollectFreq);
            HIMEDIA_DOHIPLAYERFUNC_RET(HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BAND_COLLECT_FREQ_MS,
                (HI_VOID *)CollectFreq));
            break;
        }
        default:
        {
          LOGE("setparam,do not support the key %d", key);
          return UNKNOWN_ERROR;
        }
    }
    return NO_ERROR;
}

status_t HiMediaPlayer::setSurfaceTexture(const sp<IGraphicBufferProducer> &bufferProducer)
{
//    Mutex::Autolock autoLock(mLock);
    ALOGD("HiMediaPlayer::setSurfaceTexture");
    status_t err;

    if (bufferProducer != NULL) {
        err = setNativeWindow_l(new Surface(bufferProducer));
    } else {
        err = setNativeWindow_l(NULL);
    }

    if (NO_ERROR == err)
    {
        writeLog(MEDIA_LOG_SET_VIDEO_SURFACE_TEXTURE, MEDIA_LOG_LEVEL_INFO, NULL);
    }
    else
    {
        writeLog(MEDIA_LOG_SET_VIDEO_SURFACE_TEXTURE, MEDIA_LOG_LEVEL_ERROR, NULL);
    }

    return err;
}

status_t HiMediaPlayer::setSubSurface(const sp<Surface>& surface)
{
    HI_S32 s32Ret = HI_FAILURE;
    LOGV("Call setSubSurface (%4d)",__LINE__);

    mSurface = surface;
    sp<subManager> msm = getSubManager();

    if (NULL != msm.get())
        s32Ret = msm->setSubSurface(surface);
    else
        LOGE("[%s:%d], msm is null \n", __FILE__, __LINE__);

    return s32Ret;
}

status_t HiMediaPlayer::setSubSurface(ANativeWindow* pNativeWindow, bool isXBMC)
{
    HI_S32 s32Ret = HI_FAILURE;

    LOGV("Call setSubSurface (%4d)",__LINE__);

    sp<subManager> msm = getSubManager();
    s32Ret = msm->setSubSurface(pNativeWindow, isXBMC);
    return s32Ret;
}

status_t  HiMediaPlayer::getSubString(unsigned char* pSubString)
{
    LOGV("Call getSubString (%4d)",__LINE__);
    HI_S32 s32Ret = HI_FAILURE;
    sp<subManager> msm = getSubManager();
    s32Ret = msm->getSubString(pSubString);

    return s32Ret;
}

// Hisi External Video Window Attr
sp<surfaceSetting> HiMediaPlayer::getSurfaceSetting()
{
    if (mSurfaceSetting == NULL)
    {
        LOGV("Call HiMediaPlayer::getSurfaceSetting IN, mUseExtAVPlay = %d",mUseExtAVPlay);
        mSurfaceSetting = new surfaceSetting();
        //if(!mUseExtAVPlay) mSurfaceSetting->setVideoCvrs(HI_UNF_VO_ASPECT_CVRS_IGNORE); //mediaservice case
    }

    return mSurfaceSetting;
}

status_t HiMediaPlayer::updateVideoPosition(int x, int y, int w, int h)
{
    LOGV("Call HiMediaPlayer::updateSurfacePosition IN, x:y:w:h = %d:%d:%d:%d ", x, y, w, h);

    sp<surfaceSetting> mss = getSurfaceSetting();
    return mss->updateSurfacePosition(x, y, w, h);
}

status_t HiMediaPlayer::setOutRange(int left, int top, int width, int height)
{
    LOGV("Call HiMediaPlayer::setOutRange IN, left:top:width:height = %d:%d:%d:%d ", left, top, width, height);
    sp<surfaceSetting> mss = getSurfaceSetting();
    return mss->updateSurfacePosition(left, top, width, height);
}

status_t HiMediaPlayer::setVideoRatio(int width, int height)
{
    LOGV("Call HiMediaPlayer::setVideoRatio IN, width is %d height is %d", width, height);
    sp<surfaceSetting> mss = getSurfaceSetting();
    HI_ASPECT_RATIO_S AspectRatio;
    AspectRatio.width = width;
    AspectRatio.height = height;
    return mss->setVideoRatio(AspectRatio);
}

status_t HiMediaPlayer::setVideoScaling(int scalingmode)
{
    LOGV("Call HiMediaPlayer::setVideoCvrs IN, scalingmode is %d ",scalingmode);

    sp<surfaceSetting> mss = getSurfaceSetting();

    if (scalingmode == 1) //VIDEO_SCALING_MODE_SCALE_TO_FIT = 1;
        return mss->setVideoCvrs(HI_UNF_VO_ASPECT_CVRS_COMBINED);
    else if (scalingmode == 2) //VIDEO_SCALING_MODE_SCALE_TO_FIT_WITH_CROPPING = 2;
        return mss->setVideoCvrs(HI_UNF_VO_ASPECT_CVRS_LETTERBOX);
    else
        return 0;
}

status_t HiMediaPlayer::setVideoCvrs(int cvrs)
{
    LOGV("Call HiMediaPlayer::setVideoCvrs IN, cvrs is %d ", cvrs);

    sp<surfaceSetting> mss = getSurfaceSetting();
    return mss->setVideoCvrs(cvrs);
}

status_t  HiMediaPlayer::setVideoZOrder(int ZOrder)
{
    LOGV("Call HiMediaPlayer::setVideoZOrder IN, ZOrder is %d ", ZOrder);
    sp<surfaceSetting> mss = getSurfaceSetting();
    return mss->setVideoZOrder(ZOrder);
}

status_t  HiMediaPlayer::setWindowFreezeStatus(int flag)
{
    LOGV("Call HiMediaPlayer::setWindowFreezeStatus IN, flag is %d\n", flag);
    sp<surfaceSetting> mss = getSurfaceSetting();
    return mss->setWindowFreezeStatus(flag);
}

/* impl for sound poer index: support max 16 channel */
int HiMediaPlayer::findValidSndPortId()
{
    HI_U32 i = 0;

    Mutex::Autolock lock(mInstMutex);

    LOGV("HiMediaPlayer::findValidSndPortId mSoundIdFlags is [0x%08x]", mSoundIdFlags);

    if (mSoundIdFlags >= ((2<<MAX_INSTANCE_NUM) - 1))
    {
        return -1;
    }

    for (i = 0; i < MAX_INSTANCE_NUM; i++)
    {
        if (0 == (mSoundIdFlags & (1 << i)))
        {
            mSoundIdFlags |= (1<<i);
            return i;
        }
    }

    return -1;
}

int HiMediaPlayer::clearValidSndPortId(int index)
{
    if (index < 0 || index >= MAX_INSTANCE_NUM)
    {
        LOGE("ERR: HiMediaPlayer::clearValidSndPortId invalid index[%d]", index);
        return -1;
    }

    Mutex::Autolock lock(mInstMutex);
    mSoundIdFlags &= ~(1<<index);
    return 0;
}

/* Hisi External subtitle display*/
sp<subManager> HiMediaPlayer::getSubManager()
{
    //Mutex::Autolock lock(mLock);
    if (mSubManager == 0)
    {
        mSubManager = new subManager();
        if (mSurface.get())
        {
            mSubManager->setSubSurface(mSurface);
        }
    }

    return mSubManager;
}

/* Command Queue Impl */
HiMediaPlayer::CommandQueue::CommandQueue(HiMediaPlayer* player)
            :mCurCmd(NULL), mExcuting(true),
            mIsPlayerDestroyed(0), mCmdId(0), mPlayer(player), mState(STATE_IDLE),
            mCurSeekPoint(0),mHuashuRequestSeekPoint(0), mSyncStatus(NO_ERROR), mSuspendState(STATE_IDLE), mu32LastGetPositionTime(0),ms32LastPosition(0)
{
    LOGV("HiMediaPlayer::CommandQueue construct!");
    Mutex::Autolock l(mLock);
    mpWrapperFileInfo = NULL;

    /* add for iptv */
    mAppType = APP_TYPE_BUTT;
    mIsIPTVTimeSeeking = false;
    mIPTVTimeSeekError = false;
    ms64StartTime = HI_FORMAT_NO_PTS;
    /* iptv end */
    mIsHuashuIptvLiveMod = false;
    mbHuaShuLivePlaying = false;
    mHuashuSeekQuit = false;
    memset(mszOriHuaShuUrl ,0 ,HI_FORMAT_MAX_URL_LEN);
    createThreadEtc(HiMediaPlayer::CommandQueue::sched_thread, this,
                    "sched_thread", ANDROID_PRIORITY_DEFAULT, 0, NULL);
    mThreadCond.wait(mLock);
    LOGV("HiMediaPlayer::CommandQueue construct OUT!");
}

HiMediaPlayer::CommandQueue::~CommandQueue()
{
    Mutex::Autolock l(mLock);
    mExcuting = false;
    mThreadCond.signal();
    mThreadCond.wait(mLock);

    /* add for iptv */
    mAppType = APP_TYPE_BUTT;
    mIsHuashuIptvLiveMod = false;
    mbHuaShuLivePlaying = false;
    mIsIPTVTimeSeeking = false;
    mIPTVTimeSeekError = false;
    ms32LastPosition = 0;
    mu32LastGetPositionTime = 0;
    /* iptv end */

    LOGV("HiMediaPlayer::CommandQueue() deconstruct");
}

/* used to sync cmd complete callback */
int HiMediaPlayer::CommandQueue::syncComplete(status_t status, void *cookie, bool cancelled)
{
    CommandQueue *pQueue = (CommandQueue *)cookie;
    pQueue->mSyncStatus = status;
    Mutex::Autolock l(pQueue->mLock);
    pQueue->mSyncCond.signal();
    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::enqueueCommand(Command* cmd)
{
    if (NULL == cmd)
    {
        LOGE("Command is NULL");
        return UNKNOWN_ERROR;
    }

    bool sync = false;

    if(mState == STATE_IDLE) //special deal with cmd when Preparing!!!
    {
        switch(cmd->getType())
        {
        case Command::CMD_GETPOSITION:
            return doGetPosition(cmd);
        case Command::CMD_GETDURATION:
            return doGetDuration(cmd);
        case Command::CMD_ISPLAYING:
            return doIsPlaying(cmd);
        case Command::CMD_PREPARE:
            break;
        case Command::CMD_DESTROYPLAYER:
            break;
        case Command::CMD_SETVSINK:
            break;
        default:
            return NO_ERROR;
        }
    }

    cmd->setId(mCmdId++);
    /* set the default callback for sync cmd */
    if (NULL == cmd->getCb())
    {
        cmd->setCb(HiMediaPlayer::CommandQueue::syncComplete);
        sync = true;
    }

    {
        Mutex::Autolock l(mLock);
        // after destroy operation is in queue,do not deal any operation.maybe command is enqueued
        // from hiPlayerEventCallback thread
        if (mIsPlayerDestroyed)
        {
            LOGE("Player is destroyed,do not deal any operation,operation is type %d", cmd->getType());
            delete cmd;
            cmd = NULL;
            return NO_ERROR;
        }

        if (Command::CMD_DESTROYPLAYER == cmd->getType())
        {
            LOGE("enque destroy player cmd");
            mIsPlayerDestroyed = true;
        }

        mQueue.insertAt(cmd, 0);

        /*wake up sched_thread */
        if (mQueue.size() == 1)
        {
            mThreadCond.signal();
        }

        /* sync cmd, need wait */
        if (true == sync)
        {
            mSyncCond.wait(mLock);
            return mSyncStatus;
        }
    }

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::completeCommand(Command* cmd)
{
    LOGV("HiMediaPlayer::CommandQueue::completeCommand type [%d]", cmd->getType());
    complete_cb pCallback = 0;

    if (0 != (pCallback = cmd->getCb()))
    {
        pCallback(cmd->getRet(), this, 0);
    }

    return 0;
}

/* add for iptv */
int HiMediaPlayer::CommandQueue::iptv_thread(void* cookie)
{
    HiMediaPlayer::CommandQueue *pQueue = (HiMediaPlayer::CommandQueue *)cookie;
    return pQueue->iptv_seek();
}

int HiMediaPlayer::CommandQueue::iptv_seek()
{
    HI_CHAR aszNewPath[HI_FORMAT_MAX_URL_LEN]= {0};
    HI_CHAR startTime[NORMAL_STR_LEN]= {0};
    HI_CHAR liveMode[NORMAL_STR_LEN]= {0};
    HI_CHAR tailInfo[NORMAL_STR_LEN] = {0};
    HI_S32 s32Ret = HI_SUCCESS;
    HI_CHAR *p = NULL;
    HI_U32 start_time = 0;
    // live url info is "livemode=1",timeseeked url info is "livemode=2&starttime=20141116T205745.00Z"
    const int LiveUrlInfoLen = 10, TimeSeekedUrlInfoLen = 40;
    if (!mPlayer)
    {
        LOGV("IPTV seek player is null");
        Mutex::Autolock Hiplayerlock(mLockIPTVTimeSeek);
        mIsIPTVTimeSeeking = false;
        return 0;
    }
    Mutex::Autolock Hiplayerlock(mLockHiplayer);
    if (HI_SVR_PLAYER_INVALID_HDL == mPlayerHandle)
    {
        LOGV("IPTV seek hiplayer is null,must be released");
        Mutex::Autolock Hiplayerlock(mLockIPTVTimeSeek);
        mIsIPTVTimeSeeking = false;
        return 0;
    }
 iptv_seek:
    //calc starttime
    if (true == mHuashuSeekQuit)
    {
        Mutex::Autolock Hiplayerlock(mLockIPTVTimeSeek);
        mIsIPTVTimeSeeking = false;
        LOGV("quit huashu seek");
        return 0;
    }
    HI_CHAR szHlsSecondLevUrl[HI_FORMAT_MAX_URL_LEN] = {0};
    HI_SVR_PLAYER_Invoke(mPlayerHandle, HI_FORMAT_INVOKE_GET_HLS_SECOND_LEVEL_URL, (HI_VOID*)szHlsSecondLevUrl);
    LOGV("hls second url is %s", szHlsSecondLevUrl);
    time_t lt = time(0) - labs(mCurSeekPoint) / 1000 - 20;
    struct tm ptr = {0};
    localtime_r(&lt, &ptr);

    memset(startTime, 0, NORMAL_STR_LEN);
    strftime(startTime, 100, "%Y%m%dT%H%M%S.00Z", &ptr);

    LOGW("doSeek: new seekTime=%s", startTime);

    //set livemode=2
    memset(aszNewPath, 0, HI_FORMAT_MAX_URL_LEN);
    memset(tailInfo, 0, NORMAL_STR_LEN);
    p = strstr(szHlsSecondLevUrl, "livemode=1");

    if (NULL != p)
    {
        strncpy(tailInfo, p + LiveUrlInfoLen, NORMAL_STR_LEN);
        strncpy(aszNewPath, szHlsSecondLevUrl, p - szHlsSecondLevUrl);
        memset(liveMode, 0, NORMAL_STR_LEN);
        snprintf(liveMode, NORMAL_STR_LEN - 1, "livemode=2&starttime=%s", startTime);
        strncat(aszNewPath, liveMode, NORMAL_STR_LEN - 1);
        strncat(aszNewPath, tailInfo, NORMAL_STR_LEN - 1);
    }
    else
    {
        p = strstr(szHlsSecondLevUrl, "livemode=2&starttime=");
        if (NULL != p)
        {
            strncpy(tailInfo, p + TimeSeekedUrlInfoLen, NORMAL_STR_LEN);
            strncpy(aszNewPath, szHlsSecondLevUrl, p - szHlsSecondLevUrl);
            memset(liveMode, 0, NORMAL_STR_LEN);
            snprintf(liveMode, NORMAL_STR_LEN - 1, "livemode=2&starttime=%s", startTime);
            strncat(aszNewPath, liveMode, NORMAL_STR_LEN - 1);
            strncat(aszNewPath, tailInfo, NORMAL_STR_LEN - 1);
        }
    }

    if (0 != strlen(aszNewPath))
    {
        memset(mediaParam_t.aszUrl, 0, HI_FORMAT_MAX_URL_LEN);
        memcpy(mediaParam_t.aszUrl, aszNewPath, HI_FORMAT_MAX_URL_LEN);
    }

    HI_S32 s32HlsStartNumber = 1;
    const HI_S32 RETRY_TIMES = 2;
    HI_SVR_PLAYER_INFO_S struInfo;
    int RetryTimes = 0;
    while (RetryTimes < RETRY_TIMES)
    {
        if (true == mHuashuSeekQuit)
        {
            Mutex::Autolock Hiplayerlock(mLockIPTVTimeSeek);
            mIsIPTVTimeSeeking = false;
            LOGV("quit huashu seek");
            return 0;
        }
        if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mPlayerHandle,
            HI_FORMAT_INVOKE_SET_HEADERS, (void*)mediaParam_t.u32UserData))
        {
            LOGW("Warn: doSeek HI_FORMAT_INVOKE_SET_HEADERS fail!");
        }

        if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mPlayerHandle,
            HI_FORMAT_INVOKE_SET_HLS_LIVE_START_NUM, (void*)s32HlsStartNumber))
        {
            LOGW("Warn: doSeek HI_FORMAT_INVOKE_SET_HLS_LIVE_START_NUM fail!");
        }

        start_time = getCurrentTime();
        s32Ret = HI_SVR_PLAYER_SetMedia(mPlayerHandle,
            HI_SVR_PLAYER_MEDIA_STREAMFILE, &mediaParam_t);

        LOGW("Try Open file is %s \n", mediaParam_t.aszUrl);

        if (HI_SUCCESS != s32Ret)
        {
            LOGW("doSeek HI_SVR_PLAYER_SetMedia fail, redo it!");
            usleep(100 * WAITE_TIME);
            p = strstr(mediaParam_t.aszUrl, "livemode=");

            if (NULL != p && p < mediaParam_t.aszUrl + strlen(mediaParam_t.aszUrl))
            {

                memcpy(mediaParam_t.aszUrl, mszOriHuaShuUrl, HI_FORMAT_MAX_URL_LEN);
                LOGW("doSeek renew url = %s", mszOriHuaShuUrl);
                mHuashuRequestSeekPoint = 0;
                mCurSeekPoint = 0;
            }
            RetryTimes++;
            continue;
        }

        LOGE("doSeek HI_SVR_PLAYER_SetMedia use time = %d ", getCurrentTime() - start_time);

        s32Ret = HI_SVR_PLAYER_Play(mPlayerHandle);
        LOGW("doSeek resume play, s32Ret = %d ", s32Ret);

        if (HI_SUCCESS == s32Ret)
        {
            start_time = getCurrentTime();
            memset(&struInfo, 0, sizeof(struInfo));
            while (getCurrentTime() - start_time < WAITE_MAX_TIME)
            {
                s32Ret = HI_SVR_PLAYER_GetPlayerInfo(mPlayerHandle, &struInfo);
                if (HI_SUCCESS == s32Ret && HI_SVR_PLAYER_STATE_PLAY == struInfo.eStatus)
                {
                    break;
                }

                LOGW("doSeek mState(%d) is not STATE_PLAY sleep", mState);
                usleep(WAITE_TIME);
            }
        }
        break;
    }
    LOGV("live doSeek have played");

    // if has more seek oper
    LOGV("requst seek %d,curseek point %d", mHuashuRequestSeekPoint, mCurSeekPoint);
    if (mHuashuRequestSeekPoint != mCurSeekPoint)
    {
        mCurSeekPoint = mHuashuRequestSeekPoint;
        LOGV("has more seek oper,seek to %d goto seek again",  mCurSeekPoint);
        enqueueCommand(new CommandStop(mPlayerHandle));
        start_time = getCurrentTime();

        while (getCurrentTime() - start_time < WAITE_MAX_TIME)
        {
            if (mState == STATE_STOP || mState == STATE_DESTROY)
                break;
            usleep(WAITE_TIME);
        }

        LOGW("doSeek stop use time = %d \n", getCurrentTime() - start_time);
        goto iptv_seek;
    }

    if (HI_SUCCESS == s32Ret)
    {
        {
            Mutex::Autolock Hiplayerlock(mLockIPTVTimeSeek);
            mIsIPTVTimeSeeking = false;
            mIPTVTimeSeekError = false;
        }
        LOGV("doSeek send event MEDIA_SEEK_COMPLETE");

    }
    else
    {
        {
            Mutex::Autolock Hiplayerlock(mLockIPTVTimeSeek);
            mIsIPTVTimeSeeking = false;
            mIPTVTimeSeekError = true;
        }
        LOGE("iptv seek fail");
    }

    if (mPlayer->mLooper != NULL)
    {
        const Message msg_buffer_start((int)(LooperHandler::MSG_REMOVE_BUFFERING_START));
        LOGV("remove message 701 pHiPlayer:%p",mPlayer);
        mPlayer->mLooper->postMessage(mPlayer->mLooperHandle, msg_buffer_start, 0);

        const Message msg_buffer_end((int)(LooperHandler::MSG_SEND_BUFFERING_END));
        LOGV("post message 702 pHiPlayer:%p",mPlayer);
        mPlayer->mLooper->postMessage(mPlayer->mLooperHandle, msg_buffer_end, 0);
    }

    mPlayer->sendEvent(android::MEDIA_SEEK_COMPLETE);

    if (0 == mHuashuRequestSeekPoint)
    {
        mPlayer->writeLog(MEDIA_LOG_LIVE_MODE, MEDIA_LOG_LEVEL_INFO, NULL);
    }
    else
    {
        mPlayer->writeLog(MEDIA_LOG_IPTV_MODE, MEDIA_LOG_LEVEL_INFO, NULL);
    }

    LOGV("IPTV Seek Quit");
    return 0;
}
/* iptv end */

int HiMediaPlayer::CommandQueue::sched_thread(void* cookie)
{
    HiMediaPlayer::CommandQueue *pQueue = (HiMediaPlayer::CommandQueue *)cookie;
    return pQueue->run();
}

int HiMediaPlayer::CommandQueue::run()
{
    LOGV("HiMediaPlayer::CommandQueue::run()");
    //notify the construct, the thread is ok
    {
        Mutex::Autolock l(mLock);
        mThreadCond.signal();
    }
    while (mExcuting)
    {
        {
            //for autolock
            Mutex::Autolock l(mLock);
            if (mQueue.size() == 0)
            {
                //for the out case, but the no cmds in queue!
                if (false == mExcuting)
                {
                    LOGV("Command Queue sched thread go to exit!");
                    break;
                }

                mThreadCond.wait(mLock);
                continue;
            }
            mCurCmd = mQueue.top();
            mQueue.pop();
        }
        status_t ret = UNKNOWN_ERROR;
        HI_S32 CmdType = mCurCmd->getType();
        switch(CmdType)
        {
        case Command::CMD_PREPARE:          ret = doPrepare(mCurCmd);           break;
        case Command::CMD_START:            ret = doStart(mCurCmd);             break;
        case Command::CMD_STOP:             ret = doStop(mCurCmd);              break;
        case Command::CMD_PAUSE:            ret = doPause(mCurCmd);             break;
        case Command::CMD_RESUME:           ret = doResume(mCurCmd);            break;
        case Command::CMD_GETPOSITION:      ret = doGetPosition(mCurCmd);       break;
        case Command::CMD_GETDURATION:      ret = doGetDuration(mCurCmd);       break;
        case Command::CMD_SEEK:             ret = doSeek(mCurCmd);              break;
        case Command::CMD_ISPLAYING:        ret = doIsPlaying(mCurCmd);         break;
        case Command::CMD_INVOKE:           ret = doInvoke(mCurCmd);            break;
        case Command::CMD_DESTROYPLAYER:    ret = doDestroyPlayer(mCurCmd);     break;
        case Command::CMD_SETVSINK:         ret = doSetVsink(mCurCmd);          break;
        default:   LOGV("do nothing for default!");                             break;
        }
        mCurCmd->setRet(ret);
        completeCommand(mCurCmd);
        LOGV("Complete execute Cmd");
        /* notice: free the cmd there! */
        delete mCurCmd;
        mCurCmd= NULL;
    }
    LOGV("signal thread out");
    //notify the desctruct: the thread is out
    {
        Mutex::Autolock l(mLock);
        mThreadCond.signal();
    }
    LOGV("sched_thread out");

    return 0;
}

int HiMediaPlayer::CommandQueue::SetOutPutSettings()
{
    HI_S32 Re = OK;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    DisplayClient DspClient;
    Parcel DspCapability;
    HI_S32 IsTVSupport3D = 0;
    HI_S32 VideoCodecType = HI_FORMAT_VIDEO_BUTT;
    HI_S32 IsTVSupport_24FPS_1080P = 0;
    HI_S32 s32Width = 0, s32Height = 0;
    HI_FORMAT_VID_INFO_S *pstVidInfo;
    HI_BOOL bVideoFps24Hz = HI_FALSE;
    HI_S32 s32VideoFps = 0;
    HI_HANDLE  hAVPlayer = HI_SVR_PLAYER_INVALID_HDL;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E eFormat = HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED;

    mPlayer->mPreOutputFormat = -1;

    HIMEDIA_DOFUNC_RET(HI_SVR_PLAYER_GetFileInfo(mPlayer->mHandle, &pstFileInfo));
    HIMEDIA_NULL_VERIFY(pstFileInfo);

    HIMEDIA_DOFUNC_RET(HI_SVR_PLAYER_GetParam(mPlayer->mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &stStreamId));
    HIMEDIA_DOFUNC_RET(HI_SVR_PLAYER_GetParam(mPlayer->mHandle, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAVPlayer));

    DspClient.GetDisplayCapability(&DspCapability);
    DspCapability.setDataPosition(0);
    DspCapability.readInt32();
    DspCapability.readInt32();

    IsTVSupport3D = DspCapability.readInt32();

    LOGI("SetOutPutSettings Support 3D IS %d",IsTVSupport3D);
    LOGI("mDisplayStrategy Is %d",mPlayer->mDisplayStrategy);
    if (0 < pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32VidStreamNum)
    {
        VideoCodecType = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u32Format;
        s32Width  = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u16Width;
        s32Height = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u16Height;
        pstVidInfo = &pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId];
        s32VideoFps = pstVidInfo->u16FpsInteger;//pstVidInfo->u16FpsDecimal;

        if ((pstVidInfo->u16FpsInteger == 23 && pstVidInfo->u16FpsDecimal >= 900)
            || (pstVidInfo->u16FpsInteger == 24 && pstVidInfo->u16FpsDecimal <= 100))
        {
            bVideoFps24Hz = HI_TRUE;
        }
    }
    if (mPlayer->mDisplayStrategy & DP_STRATEGY_3D_MASK)
    {
        LOGI("OutPut 3D Mode");
        if (HI_FORMAT_VIDEO_MVC == VideoCodecType)
        {
            LOGI("Output Mode Is 3D");
            DspClient.SetStereoOutMode(OUTPUT_MODE_3D, s32VideoFps);
            Re = HI_UNF_AVPLAY_SetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, &eFormat);
            LOGV("Set video frame TIME_INTERLACED, ret = 0x%x ", Re);

        }
    }
    else if (mPlayer->mDisplayStrategy & DP_STRATEGY_ADAPT_MASK)
    {
        LOGI("OutPut Adapter Mode");
        // should set 3d output mode,if tv support 3d and file is mvc
        if (HI_FORMAT_VIDEO_MVC == VideoCodecType && IsTVSupport3D)
        {
            LOGI("Output Mode Is 3D");
            DspClient.SetStereoOutMode(OUTPUT_MODE_3D, s32VideoFps);
            Re = HI_UNF_AVPLAY_SetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, &eFormat);
            LOGV("Set video frame TIME_INTERLACED, ret = 0x%x ", Re);

        }
    }
    else if (mPlayer->mDisplayStrategy & DP_STRATEGY_2D_MASK)
    {
       DspClient.SetStereoOutMode(OUTPUT_MODE_2D, 0);
    }

    // if support 24fps-1080p
    DspCapability.readInt32();
    DspCapability.readInt32();
    DspCapability.readInt32();
    DspCapability.readInt32();

    IsTVSupport_24FPS_1080P = DspCapability.readInt32();

    LOGI("TV Support 1080P_24FPS Ability is %d",IsTVSupport_24FPS_1080P);

    if (IsTVSupport_24FPS_1080P && (mPlayer->mDisplayStrategy & DP_STRATEGY_24FPS_MASK)
        && (HI_TRUE == bVideoFps24Hz) && (mPlayer->mDisplayStrategy & DP_STRATEGY_2D_MASK))
    {
        LOGI("Set Mode 1080P_24FPS");
        mPlayer->mPreOutputFormat = DspClient.GetEncFmt();
        LOGI("mPreOutputFormat is %d", mPlayer->mPreOutputFormat);
        Re = DspClient.SetEncFmt(DISPLAY_FMT_1080P_24);
    }

    #if 0
    if (s32Width >= 3840 && s32Height >= 2160)
    {
        LOGI("==Set Mode 4k*2k 30fps==");
        mPlayer->mPreOutputFormat = DspClient.GetEncFmt();
        LOGI("mPreOutputFormat is %d", mPlayer->mPreOutputFormat);
        Re = DspClient.SetEncFmt(DISPLAY_FMT_4KX2K_30);
    }
    #endif

    return Re;
}
int HiMediaPlayer::CommandQueue::doPrepare(Command* cmd)
{
    LOGV("[%s] Call %s IN", STR_SWITCH_PG, __FUNCTION__);

    HI_HANDLE mHandle = cmd->getHandle();
    HI_SVR_PLAYER_MEDIA_S mediaParam = (static_cast<CommandPrepare*>(cmd))->getParam();
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 start_time = getCurrentTime();
    HI_S32 s32Underrun = 1;
    HI_S32 s32HlsStartNumber = 1;
    /* add for iptv */
    HI_CHAR value[1024] = {0};
    HI_FORMAT_BUFFER_CONFIG_S stBufConfig;
    HI_S64  s64BufMaxSize;

    memset(value, 0, 1024);

    /* client.apk.name
           1. wasu.app
           2. besttv.app
           3. icntv.app
           set apk.name by using "setprop client.apk.name wasu.app" command.
      */

    if (property_get("client.apk.name", value, NULL) > 0)
    {
        LOGW("doPrepare, property_get value = %s \n", value);

        if (!strncmp(value, "wasu.app", 8))
        {
            mAppType = APP_TYPE_WASU;
            LOGW("doPrepare, check application is wasu apk");
        }
    }
    /* iptv end */
    if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_HEADERS, (void*)mediaParam.u32UserData))
    {
        LOGW("Warn: doPrepare HI_FORMAT_INVOKE_SET_HEADERS fail!");
    }

    //china moblie request play the hls live stream from first segment.
    if (HI_FAILURE == HI_SVR_PLAYER_Invoke(mHandle,
        HI_FORMAT_INVOKE_SET_HLS_LIVE_START_NUM, (void*)s32HlsStartNumber))
    {
        LOGW("Warn: doPrepare HI_FORMAT_INVOKE_SET_HLS_LIVE_START_NUM fail!");
    }

    LOGV("set play the hls stream from first segment");

    /* Set buffer config */
    memset(&stBufConfig, 0, sizeof(HI_FORMAT_BUFFER_CONFIG_S));
    stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_SIZE;
    s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, &stBufConfig);

    stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_TIME;
    stBufConfig.s64EventStart  = 200;
    stBufConfig.s64EventEnough = 5000;
    stBufConfig.s64Total       = 20000;
    stBufConfig.s64TimeOut     = 2*60*1000;
    s64BufMaxSize = 40*1024*1024;

    s32Ret |= HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_CONFIG, &stBufConfig);
    s32Ret |= HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE, &s64BufMaxSize);
    s32Ret |= HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_UNDERRUN, &s32Underrun);
    if (HI_SUCCESS != s32Ret)
    {
        LOGV("ERR: HI_SVR_PLAYER_Invoke set buffer config fail, maybe is local file!");
    }

    LOGV("BufferConfig:type(%d)\n",stBufConfig.eType);
    LOGV("s64EventStart:%lld\n", stBufConfig.s64EventStart);
    LOGV("s64EventEnough:%lld\n", stBufConfig.s64EventEnough);
    LOGV("s64Total:%lld\n", stBufConfig.s64Total);
    LOGV("s64TimeOut:%lld\n", stBufConfig.s64TimeOut);

    s32Ret = HI_SVR_PLAYER_SetMedia(mHandle, HI_SVR_PLAYER_MEDIA_STREAMFILE, &mediaParam);

    memcpy(&mediaParam_t, &mediaParam, sizeof(mediaParam));
    LOGE("HI_SVR_PLAYER_SetMedia use time = %d ", getCurrentTime() - start_time);

    /* add for china mobile iptv */
    if (APP_TYPE_WASU == mAppType)
    {
        ms64StartTime = HI_FORMAT_NO_PTS;
        HI_CHAR *pStartTime = strstr(mediaParam.aszUrl, "&starttime=");

        if (NULL != pStartTime && pStartTime < mediaParam.aszUrl + strlen(mediaParam.aszUrl))
        {
            HI_CHAR *p = pStartTime + strlen("&starttime=");
            if (*p > '9' || *p < '0')
            {
                ms64StartTime = HI_FORMAT_NO_PTS;
            }
            else
            {
                ms64StartTime = atoi(pStartTime + strlen("&starttime="));
                LOGE("doPrepare: ms64StartTime = %lld ", ms64StartTime);
            }
        }

        HI_CHAR *pLiveModeString = NULL;
        pLiveModeString = strstr(mediaParam_t.aszUrl, "livemode=4");

        if (NULL == pLiveModeString)
        {
            pLiveModeString = strstr(mediaParam_t.aszUrl, "livemode=");
        }
        else
        {
            pLiveModeString = NULL;
            LOGW("doPrepare, livemode=4, use normal seek!");
        }

        if (NULL != pLiveModeString)
        {
            mIsHuashuIptvLiveMod= true;
            mbHuaShuLivePlaying = true;
            LOGV("is huashu live mode");
        }
    }
    /* end */

    SetOutPutSettings();

    if (s32Ret == HI_SUCCESS)
    {
        mState = STATE_INIT;
        setTrueHDSetting(mHandle);
        mPlayer->mPrepareResult = NO_ERROR;
    }
    else
    {
        LOGE("ERR: doPrepare fail!");
        mState = STATE_ERROR;
        mPlayer->mPrepareResult = UNKNOWN_ERROR;
        return UNKNOWN_ERROR;
    }

    /* We can set seek mode by setprop media.hisiplayer.seekmode *
     * setprop media.hisiplayer.seekmode pos --- means seek by pos *
     * setprop media.hisiplayer.seekmode pts --- means seek by pts */
    HI_CHAR seekmode[PROPERTY_VALUE_MAX] = {0};
    if (property_get("media.hisiplayer.seekmode", seekmode, "pos") > 0)
    {
        HI_FORMAT_SEEK_MODE_E eMode = HI_FORMAT_SEEK_MODE_BUTT;
        if (!strncasecmp(seekmode, "pts", 3))
        {
            /* Seek by pts. */
            eMode = HI_FORMAT_SEEK_MODE_PTS;
        }
        else
        {
            /* In this case, when we play network stream without index, it will seek by pos instead of pts. */
            eMode = HI_FORMAT_SEEK_MODE_POS;
        }

        LOGV("going to set seek mode to %s", seekmode);

        s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_SEEK_MODE, (HI_VOID*)eMode);
        if (HI_SUCCESS != s32Ret)
        {
            LOGE("ERR: HI_SVR_PLAYER_Invoke HI_FORMAT_INVOKE_SET_SEEK_MODE fail!");
        }
        else
        {
            LOGV("set seek mode success");
        }
    }

    mPlayer->mLooper = new HiMediaLooper();
    if (mPlayer->mLooper == NULL)
    {
        LOGE("create HiMediaLooper fail");
    }
    else
    {
        LOGV("create HiMediaLooper ok");
        mPlayer->mLooperHandle = new LooperHandler(mPlayer->mLooper, mPlayer);
        if (mPlayer->mLooperHandle == NULL)
        {
            LOGE("create LooperHandler fail");
        }
        else
        {
            LOGV("create LooperHandler ok");
        }
    }

    return NO_ERROR;
}

status_t HiMediaPlayer::CommandQueue::setTrueHDSetting(HI_HANDLE handle)
{
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_U32 i = 0;

    if (HI_SUCCESS != HI_SVR_PLAYER_GetParam(handle, HI_SVR_PLAYER_ATTR_STREAMID, &stStreamId))
    {
        return UNKNOWN_ERROR;
    }

    if (HI_SUCCESS != HI_SVR_PLAYER_GetFileInfo(handle, &pstFileInfo))
    {
        return UNKNOWN_ERROR;
    }

    if (NULL == pstFileInfo)
    {
        return UNKNOWN_ERROR;
    }

    if (pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum <= 0)
    {
        LOGE("stFileInfo.astProgramInfo[%d].u32AudStreamNum is %d",
            stStreamId.u16ProgramId,
            pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum);
        return NO_ERROR;
    }

    HI_U32 curAStreamId = stStreamId.u16AudStreamId;

    LOGV("curAStreamId is %d format %x subid is %d",
        curAStreamId,
        pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[curAStreamId].u32Format,
        pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[curAStreamId].s32SubStreamID);

    if ((FORMAT_TRUEHD !=
            pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[curAStreamId].u32Format)
        ||(HI_FORMAT_INVALID_STREAM_ID ==
            pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[curAStreamId].s32SubStreamID))
    {
        return NO_ERROR;
    }

    if (TRUEHD_AC3_SUB == mPlayer->getTrueHDSetting())//choose the AC3 as TrueHD to play
    {
        for (i = 0; i < pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum; i++)
        {
            if (pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[i].s32StreamIndex
                == pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[curAStreamId].s32SubStreamID)
            {
                break;
            }
        }

        if (i >= pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum)
        {
            return UNKNOWN_ERROR;
        }

        stStreamId.u16AudStreamId = i;

        if (HI_SUCCESS != HI_SVR_PLAYER_SetParam(handle, HI_SVR_PLAYER_ATTR_STREAMID, &stStreamId))
        {
            LOGE("setTrueHDSetting HI_SVR_PLAYER_SetParam fail stStreamId.u32AStreamId is %d!", stStreamId.u16AudStreamId);
        }
    }

    return NO_ERROR;
}

HI_U32 HiMediaPlayer::CommandQueue::getTrueHDBySubAc3(HI_HANDLE handle, HI_U32 id)
{
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_U32 i = 0;

    if (TRUEHD_AC3_SUB != mPlayer->getTrueHDSetting()
       || HI_SUCCESS != HI_SVR_PLAYER_GetParam(handle, HI_SVR_PLAYER_ATTR_STREAMID, &stStreamId)
       || HI_SUCCESS != HI_SVR_PLAYER_GetFileInfo(handle, &pstFileInfo)
       || NULL == pstFileInfo
       || stStreamId.u16ProgramId >= pstFileInfo->u32ProgramNum
       || pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum <= 0
       || FORMAT_AC3 != pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[id].u32Format)
    {
        return id;
    }

    for (i = 0; i < pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum; i++)
    {
        if ((FORMAT_TRUEHD == pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[i].u32Format)
           &&(HI_FORMAT_INVALID_STREAM_ID != pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[i].s32SubStreamID)
           &&(pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[i].s32SubStreamID
               == pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[id].s32StreamIndex))
        {
            return i;
        }
    }

    return id;
}

int HiMediaPlayer::CommandQueue::getFileInfoWrapper(HI_HANDLE hPlayer)
{
    HI_FORMAT_FILE_INFO_S* pstruInfo = NULL;
    HI_S32 ret = NO_ERROR;
    HI_U32 i = 0, j = 0;
    HI_U32 index = 0;

    HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstruInfo);

    if (NULL == mpWrapperFileInfo)
    {
        mpWrapperFileInfo = (HI_FORMAT_FILE_INFO_S*)HIMEDIA_MALLOCZ(sizeof(HI_FORMAT_FILE_INFO_S));
        HIMEDIA_NULL_VERIFY(mpWrapperFileInfo);

        memset(mpWrapperFileInfo, 0, sizeof(HI_FORMAT_FILE_INFO_S));
        AllocCopyFileInfo(mpWrapperFileInfo, pstruInfo);
    }

    pstruInfo = mpWrapperFileInfo;

    if (NULL == pstruInfo || pstruInfo->u32ProgramNum <= 0)
        return ret;

    for (index = 0; index < pstruInfo->u32ProgramNum; index++)
    {
        if (pstruInfo->pastProgramInfo[index].u32AudStreamNum <= 0)
        {
            continue;
        }

        //find the track, which has sub track info
        for (i = 0; i < pstruInfo->pastProgramInfo[index].u32AudStreamNum; i++)
        {
            if ((HI_FORMAT_AUDIO_TRUEHD == pstruInfo->pastProgramInfo[index].pastAudStream[i].u32Format)
                &&(HI_FORMAT_INVALID_STREAM_ID != pstruInfo->pastProgramInfo[index].pastAudStream[i].s32SubStreamID))
            {
                for (j = 0; j < pstruInfo->pastProgramInfo[index].u32AudStreamNum; j++)
                {
                    if (pstruInfo->pastProgramInfo[index].pastAudStream[j].s32StreamIndex
                        == pstruInfo->pastProgramInfo[index].pastAudStream[i].s32SubStreamID)
                    {
                        break;
                    }
                }

                if (j < pstruInfo->pastProgramInfo[index].u32AudStreamNum)
                {
                    //delete sub audio track info
                    for ( ; j < pstruInfo->pastProgramInfo[index].u32AudStreamNum - 1; j++)
                    {
                        pstruInfo->pastProgramInfo[index].pastAudStream[j] =
                                        pstruInfo->pastProgramInfo[index].pastAudStream[j + 1];
                    }

                    pstruInfo->pastProgramInfo[index].u32AudStreamNum--;
                }
            }
        }
    }

    return ret;
}

int HiMediaPlayer::CommandQueue::doStart(Command* cmd)
{
    LOGV("[%s] Call %s IN", STR_SWITCH_PG, __FUNCTION__);
    HI_HANDLE mHandle = cmd->getHandle();
    HI_SVR_PLAYER_INFO_S struInfo;

    if (STATE_ERROR == mState || STATE_IDLE == mState || STATE_PLAY == mState)
    {
        LOGW("doStart at wrong state %d", mState);
        return NO_ERROR;
    }

    if (STATE_PAUSE == mState || STATE_FWD == mState || STATE_REW == mState)
    {
        if (HI_FAILURE == HI_SVR_PLAYER_Resume(mHandle))
        {
            LOGE("ERR: HI_SVR_PLAYER_Resume fail");
            return ERROR_OPEN_FAILED;
        }
    }
    else
    {
        /* add for china mobile iptv */
        if (ms64StartTime != HI_FORMAT_NO_PTS)
        {
            LOGE("doStart HI_SVR_PLAYER_Seek = %lld ", ms64StartTime);
            HI_SVR_PLAYER_Seek(mHandle, ms64StartTime);
            ms64StartTime = HI_FORMAT_NO_PTS;
        }
        /* end */
        if (HI_FAILURE == HI_SVR_PLAYER_Play(mHandle))
        {
            LOGE("ERR: HI_SVR_PLAYER_Play fail");
            return ERROR_OPEN_FAILED;
        }
    }

    HI_S32 ret = wait();

    //add for start use time > 2s to success
    if (ret == ERROR_TIMEOUT && mState != STATE_ERROR)
    {
        LOGE("ERR: doStart TimeOut");
        ret = NO_ERROR;
        mState = STATE_PLAY;
    }

    if (mState == STATE_ERROR) //start asyn notify fail!
    {
        LOGE("ERR: doStart fail");
        ret = UNKNOWN_ERROR;
    }

   // mCurSeekPoint = 0;

    return ret;
}

int HiMediaPlayer::CommandQueue::doStop(Command* cmd)
{
    LOGV("[%s] Call %s IN", STR_SWITCH_PG, __FUNCTION__);
    HI_HANDLE mHandle = cmd->getHandle();

    if (STATE_IDLE == mState || STATE_STOP == mState)
    {
        LOGW("don't stop before STATE_INIT or STATE_STOP");
        return NO_ERROR;
    }

    if (STATE_INIT == mState) //beacuse hiplayer don't support stop after setMedia immediately
    {
        LOGW("stop at STATE_INIT");
        mState = STATE_STOP;
        return NO_ERROR;
    }

    if (HI_SUCCESS != HI_SVR_PLAYER_Stop((HI_HANDLE)mHandle))
    {
        LOGE("ERR: HI_SVR_PLAYER_Stop fail");
        return UNKNOWN_ERROR;
    }
   // HI_S32 ret = wait();

   // if (ret == ERROR_TIMEOUT) // add for stop use time > 2s to success
   // {
   //     ret= NO_ERROR;
   //     mState = STATE_STOP;
   // }

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doPause(Command* cmd)
{
    LOGV("[%s] Call %s IN", STR_SWITCH_PG, __FUNCTION__);
    HI_HANDLE mHandle = cmd->getHandle();

    if (STATE_INIT == mState || STATE_ERROR == mState
        || STATE_IDLE == mState || STATE_PAUSE == mState)
    {
        LOGW("doPause at wrong state %d", mState);
        return NO_ERROR;
    }

    if (STATE_FWD == mState || STATE_REW == mState)
    {
        if (HI_FAILURE == HI_SVR_PLAYER_Resume(mHandle))
        {
            LOGE("ERR: HI_SVR_PLAYER_Resume fail");
            return UNKNOWN_ERROR;
        }

        wait();
    }

    if (HI_FAILURE == HI_SVR_PLAYER_Pause(mHandle))
    {
        LOGE("ERR: HI_SVR_PLAYER_Pause fail");
        return UNKNOWN_ERROR;
    }

    // if wasu live playing,we must set to timeseek mode
    if (mbHuaShuLivePlaying == true && mIsHuashuIptvLiveMod == true && APP_TYPE_WASU == mAppType)
    {
        // make hls dmx fresh to timeseek url
        LOGV("begin fresh hls time seek url");
        if (HI_SUCCESS== HI_SVR_PLAYER_Invoke(mHandle,
            HI_FORMAT_INVOKE_SET_HLS_FRESH_URL, NULL))
        {
            mbHuaShuLivePlaying = false;
            LOGV("fresh hls time seek url ok");
        }
    }

    HI_S32 ret = wait();

    if (ret == ERROR_TIMEOUT)
    {
        ret= NO_ERROR;
        mState = STATE_PAUSE;
    }

    return ret;
}

int HiMediaPlayer::CommandQueue::doResume(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    HI_HANDLE mHandle = cmd->getHandle();
    HI_S32 s32Ret = HI_FAILURE;

    if (STATE_PAUSE == mSuspendState)
    {
        return NO_ERROR;
    }

    s32Ret = HI_SVR_PLAYER_Resume(mHandle);

    if (HI_SUCCESS != s32Ret)
    {
        LOGV("ERR: Resume fail, ret = 0x%x ", s32Ret);
        return UNKNOWN_ERROR;
    }

    return wait();
}

int HiMediaPlayer::CommandQueue::doGetPosition(Command* cmd)
{
    HI_HANDLE mHandle = cmd->getHandle();
    HI_SVR_PLAYER_INFO_S struInfo;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32TimePlayed = 0;

    HI_S32* position = (static_cast<CommandGetPosition*>(cmd))->getPosition();

    if (STATE_IDLE == mState)
    {
        *position = 0;
    }
    else
    {
        // if huashu app,and is seeking,we must return.or thread must be block by call
        // HI_SVR_PLAYER_GetPlayerInfo
        if (mAppType == APP_TYPE_WASU && mIsIPTVTimeSeeking)
        {
            LOGV("huashu is seeking,return");
            *position = mHuashuRequestSeekPoint;
            return NO_ERROR;
        }

        if (HI_SUCCESS == HI_SVR_PLAYER_GetPlayerInfo(mHandle, &struInfo))
        {
            s32TimePlayed = struInfo.u64TimePlayed;
            /* add for iptv */
            if (APP_TYPE_WASU == mAppType)
            {
                if (true == mIsHuashuIptvLiveMod)
                {
                    // if huashulive play,the position is latest time
                    if (0 == mCurSeekPoint)
                    {
                        if (STATE_PAUSE == mState && 0 != mu32LastGetPositionTime)
                        {
                            HI_U32 u32TimeGap = getCurrentTime() - mu32LastGetPositionTime;
                            LOGV("live pause state,gap time is %u", u32TimeGap);
                            mCurSeekPoint += u32TimeGap;
                            *position = mCurSeekPoint;
                        }
                        else
                        {
                            *position = 0;
                        }
                    }
                    else
                    {
                        LOGV("ms32LastPosition %d s32TimePlayed %d mu32LastGetPositionTime %d", ms32LastPosition, s32TimePlayed, mu32LastGetPositionTime);
                        if (ms32LastPosition == s32TimePlayed && 0 != ms32LastPosition && 0 != mu32LastGetPositionTime)
                        {
                            HI_U32 u32TimeGap = getCurrentTime() - mu32LastGetPositionTime;
                            LOGV("network error,gap time is %u", u32TimeGap);
                            mCurSeekPoint += u32TimeGap;
                            *position = mCurSeekPoint;
                            LOGV("network error,position is %u", mCurSeekPoint);
                        }
                        else
                        {
                            *position = labs(mCurSeekPoint);
                            LOGV("network normal,position is %u", mCurSeekPoint);
                        }

                    }
                    ms32LastPosition = s32TimePlayed;
                    mu32LastGetPositionTime = getCurrentTime();
                }
                else
                {
                    *position = struInfo.u64TimePlayed;
                }
            }
            else
            {
                *position = struInfo.u64TimePlayed;
            }
        }
        else
        {
            /* add for iptv */
            LOGE("ERR: doGetPosition fail!");
            if (APP_TYPE_WASU == mAppType)
                return NO_ERROR;
            else
                return UNKNOWN_ERROR;
        }
    }

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doGetDuration(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    HI_HANDLE mHandle = cmd->getHandle();
    HI_FORMAT_FILE_INFO_S *pstruInfo;
    HI_CHAR *p = NULL;

    HI_S32* duration = (static_cast<CommandGetDuration*>(cmd))->getDuration();

    if (STATE_IDLE == mState)
    {
        *duration = 0;
    }
    else if (HI_SUCCESS == HI_SVR_PLAYER_GetFileInfo(mHandle, &pstruInfo) && NULL != pstruInfo)
    {
        *duration = pstruInfo->s64Duration;

        /* add for iptv */
        p = strstr(mediaParam_t.aszUrl, "&livemode=");

        if (pstruInfo->eSourceType == HI_FORMAT_SOURCE_NET_LIVE)
        {
            if (NULL != p && APP_TYPE_WASU == mAppType)
            {
                /* only for iptv test */
                *duration = WASU_SEEK_MAX_DAYS;
            }
        }
        /* end */
    }
    else
    {
        LOGE("ERR: doGetDuration fail!");
        return UNKNOWN_ERROR;
    }

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doSeek(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    HI_HANDLE mHandle = cmd->getHandle();
    HI_S32 position = (static_cast<CommandSeek*>(cmd))->getPosition();
    HI_U32 start_time = getCurrentTime();
    HI_S32 s32Ret = HI_SUCCESS;
    HI_SVR_PLAYER_EVENT_S stPlayerEvent;

    /* only for test */
    //memset(mediaParam_t.aszUrl, 0, sizeof(mediaParam_t.aszUrl));
    //sprintf(mediaParam_t.aszUrl, "%s", "http://ips.itv.cmvideo.cn/140_0_3736680_0.m3u8?id=3736680&scId=&isChannel=true&time=300&serviceRegionIds=140&codec=ALL&quality=100&vSiteCode=&offset=0&livemode=1");

    /* add for iptv */

    HI_CHAR *p = NULL;
    p = strstr(mediaParam_t.aszUrl, "livemode=4");

    if (NULL == p)
    {
        p = strstr(mediaParam_t.aszUrl, "livemode=");
    }
    else
    {
        // livemode=4, is playback function, use normal seek
        p = NULL;
        LOGW("doSeek, livemode=4, use normal seek!");
    }

    if (NULL != p && APP_TYPE_WASU == mAppType)
    {
        mIsHuashuIptvLiveMod = true;
        mbHuaShuLivePlaying = false;
        mCurSeekPoint = labs(position) ;
        mPlayerHandle = mHandle;

        LOGW("doSeek: mIsIPTVTimeSeeking=%d", mIsIPTVTimeSeeking);

        s32Ret = HI_SVR_PLAYER_Invoke(mPlayerHandle, HI_FORMAT_INVOKE_PRE_CLOSE_FILE , NULL);
        if (HI_SUCCESS != s32Ret)
            LOGV("huashu doSeek HI_FORMAT_INVOKE_PRE_CLOSE_FILE fail!");

        s32Ret = HI_SVR_PLAYER_Stop(mPlayerHandle);
        if (HI_SUCCESS != s32Ret)
        {
            LOGW("doSeek HI_SVR_PLAYER_Stop fail!");
        }
        start_time = getCurrentTime();

        while (getCurrentTime() - start_time < WAITE_MAX_TIME)
        {
            if (mState == STATE_STOP || mState == STATE_DESTROY)
                break;
            usleep(WAITE_TIME);
        }

        LOGW("doSeek stop use time = %d \n", getCurrentTime() - start_time);

        #if NET_CACHE_UNDERRUN
        if (mPlayer->getDiagnose())
        {
            if (BUFFERING_NOT_ENOUGH == mPlayer->getBuffering())
            {
                LOGV("begin seek,clear 701 message");
                mPlayer->sendEvent(android::MEDIA_INFO, android::MEDIA_INFO_BUFFERING_END, 0);
                mPlayer->setBuffering(BUFFERING_ENOUGH);
            }
        }
        #endif

        if (false == mIsIPTVTimeSeeking)
        {
            LOGW("doSeek: call createThreadEtc");

            mIsIPTVTimeSeeking = true;
            createThreadEtc(HiMediaPlayer::CommandQueue::iptv_thread, this,
                            "iptv_seek_thread", ANDROID_PRIORITY_DEFAULT, 0, NULL);
        }
    }
    else
    {
        if (HI_FAILURE == HI_SVR_PLAYER_Seek(mHandle, position))
        {
            LOGE("doSeek fail");
            return UNKNOWN_ERROR;
        }
    }

    if (mPlayer->mLooper != NULL)
    {
        const Message msg((int)(LooperHandler::MSG_SEND_BUFFERING_START));
        LOGV("post message 701 pHiPlayer:%p",mPlayer);
        mPlayer->mLooper->postMessage(mPlayer->mLooperHandle, msg, 2*1000*1000*1000);
    }

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doIsPlaying(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    bool* bIsPlaying = (static_cast<CommandIsPlaying*>(cmd))->getPlaying();

    *bIsPlaying = (STATE_PLAY == mState || STATE_FWD == mState || STATE_REW == mState);

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doDestroyPlayer(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    HI_HANDLE Handle = cmd->getHandle();
    if (HI_SUCCESS != HI_SVR_PLAYER_Destroy(Handle))
    {
        LOGE("ERR: HI_SVR_PLAYER_Destroy fail!");
        return UNKNOWN_ERROR;
    }
    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doSetVsink(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    HI_HANDLE Handle = cmd->getHandle();
    CommandSetVsink* cmdSetVSink = static_cast<CommandSetVsink*>(cmd);
    HI_SVR_VSINK_S* pstVSink = dynamic_cast<HI_SVR_VSINK_S*>(cmdSetVSink->getVsink());

    if(mPlayer->mNonVSink != true)
    {
        if (HI_SUCCESS != HI_SVR_PLAYER_SetParam(Handle,
            HI_SVR_PLAYER_ATTR_VSINK_HDL, pstVSink))
        {
            LOGE("ERR: HI_SVR_PLAYER_SetParam(vsink) fail!");
            return UNKNOWN_ERROR;
        }
    }
    cmdSetVSink->clearVsink();
    return NO_ERROR;
}

int HiMediaPlayer::setSubtitleNativeWindow(const Parcel& subSurface)
{
    LOGV("HiMediaPlayer::invoke in CMD_SET_SUB_SURFACE");
    subSurface.setDataPosition(subSurface.dataPosition() + 4);
    sp<Surface> surface;
    sp<ANativeWindow> NativeWindow;
    sp<IBinder> binder(subSurface.readStrongBinder());
    sp<IGraphicBufferProducer> producer(interface_cast<IGraphicBufferProducer>(binder));

    if (producer != NULL)
    {
        mSubTitleNativeWindow = new Surface(producer);
        if (NULL == mSubTitleNativeWindow.get())
        {
            LOGE("setSubtitleNativeWindow SubTitleNativeWindow is null");
            return UNKNOWN_ERROR;
        }
    }
    else
    {
        LOGE("setSubtitleNativeWindow surface is null");
        return UNKNOWN_ERROR;
    }
    native_window_api_connect(mSubTitleNativeWindow.get(),
        NATIVE_WINDOW_API_CPU);
    native_window_set_scaling_mode(mSubTitleNativeWindow.get(),
        NATIVE_WINDOW_SCALING_MODE_SCALE_TO_WINDOW);
    setSubSurface(mSubTitleNativeWindow.get(), false);
    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::doInvoke(Command* cmd)
{
    LOGV("Call %s IN", __FUNCTION__);
    status_t   ret = OK;
    HI_S32     s32Ret = 0;
    HI_S32     arg = 0;

    HI_HANDLE mHandle = cmd->getHandle();
    Parcel* request = (static_cast<CommandInvoke*>(cmd))->getRequest();
    Parcel* reply   = (static_cast<CommandInvoke*>(cmd))->getReply();
    cmd_type_e cmd_type = (cmd_type_e)request->readInt32();

    HI_HANDLE  hAVPlayer = HI_SVR_PLAYER_INVALID_HDL, hWnd = HI_SVR_PLAYER_INVALID_HDL;
    HI_HANDLE hTrack = HI_SVR_PLAYER_INVALID_HDL;
    HI_UNF_VCODEC_ATTR_S VidAttr;
    HI_UNF_WINDOW_ATTR_S sWndAttr;
    HI_UNF_TRACK_MODE_E eTrackMode;
    HI_UNF_SYNC_ATTR_S stSyncAttr;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_U32 i = 0, j = 0;

    CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAVPlayer));

    LOGV("HiMediaPlayer::invoke cmd [%d]", cmd_type);
    switch(cmd_type)
    {
        case CMD_SET_VIDEO_FRAME_MODE:  // cmd request construct: cmdtype | frame_mode_e
        {
            arg = request->readInt32();

            CHECK_FUNC_RET(HI_UNF_AVPLAY_GetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VidAttr));

            VidAttr.enMode = (HI_UNF_VCODEC_MODE_E)arg;
            CHECK_FUNC_RET(HI_UNF_AVPLAY_SetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VidAttr));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_VIDEO_FRAME_MODE:
        {
            CHECK_FUNC_RET(HI_UNF_AVPLAY_GetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VidAttr));

            arg = (int)VidAttr.enMode;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
        }
        break;
        case CMD_SET_VIDEO_CVRS:      // cmd request construct: cmdtype | aspect_cvrs_mode_e
        {
            arg = request->readInt32();
            CHECK_FUNC_RET(mPlayer->setVideoCvrs(arg));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_VIDEO_CVRS:
        {
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hWnd));
            CHECK_FUNC_RET(HI_UNF_VO_GetWindowAttr(hWnd, &sWndAttr));

            arg = (int)sWndAttr.stWinAspectAttr.enAspectCvrs;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
        }
        break;
        case CMD_SET_AUDIO_MUTE_STATUS:      // cmd request construct: cmdtype | mute_status_e
        {
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hTrack));

            arg = request->readInt32();

            if (arg == 1)
            {
                CHECK_FUNC_RET(HI_UNF_SND_SetTrackMute(hTrack, HI_TRUE));
            }
            else
            {
                CHECK_FUNC_RET(HI_UNF_SND_SetTrackMute(hTrack, HI_FALSE));
            }

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_AUDIO_MUTE_STATUS:
        {
            HI_BOOL bMute = HI_FALSE;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hTrack));
            CHECK_FUNC_RET(HI_UNF_SND_GetTrackMute(hTrack, &bMute));

            arg = bMute;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
        }
        break;
        case CMD_SET_AUDIO_VOLUME:
        {
            HI_UNF_SND_GAIN_ATTR_S stGain;

            arg = request->readInt32();

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hTrack));

            memset(&stGain, 0, sizeof(stGain));
            stGain.bLinearMode = HI_TRUE;
            stGain.s32Gain = (HI_S32)arg;

            CHECK_FUNC_RET(HI_UNF_SND_SetTrackWeight(hTrack, &stGain));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_AUDIO_VOLUME:
        {
            HI_UNF_SND_GAIN_ATTR_S stGain;

            arg = request->readInt32();

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hTrack));

            memset(&stGain, 0, sizeof(stGain));
            stGain.bLinearMode = HI_TRUE;
            stGain.s32Gain = (HI_S32)arg;

            CHECK_FUNC_RET(HI_UNF_SND_GetTrackWeight(hTrack, &stGain));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(stGain.s32Gain);
            }
        }
        break;
        case CMD_SET_VIDEO_FPS:     // cmd request to set fps
        {
            HI_S32 arg2=0;
            arg = request->readInt32();
            arg2 = request->readInt32();
            HI_UNF_AVPLAY_FRMRATE_PARAM_S stFramerate;
            stFramerate.enFrmRateType = HI_UNF_AVPLAY_FRMRATE_TYPE_USER;
            stFramerate.stSetFrmRate.u32fpsInteger = (HI_U32)arg;
            stFramerate.stSetFrmRate.u32fpsDecimal = (HI_U32)arg2;
            CHECK_FUNC_RET(HI_UNF_AVPLAY_SetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_FRMRATE_PARAM, (HI_VOID*)&stFramerate));
            if(NULL !=reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_SET_VIDEO_Z_ORDER:
        {
            arg = request->readInt32();
            CHECK_FUNC_RET(mPlayer->setVideoZOrder(arg));
            if (NULL != reply)
            {
                reply->writeInt32(NO_ERROR);
            }
        }
        break;
        case CMD_SET_SURFACE_RATIO:       // cmd request construct: cmdtype | aspect_ratio_e
        {
            int width = request->readInt32();
            int height = request->readInt32();

            s32Ret = mPlayer->setVideoRatio(width, height);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }

            LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
            return s32Ret;
        }
        break;
        case CMD_GET_SURFACE_RATIO:
        {
            LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
            return BAD_TYPE;
        }
        break;
        case CMD_SET_AUDIO_CHANNEL_MODE:     // cmd request construct: cmdtype | audio_track_mode_e
        {
            arg = request->readInt32();

            LOGV("HI_UNF_SND_0 SET CHNEEL DBG LOG arg IS %d",arg);

            CHECK_FUNC_RET(HI_UNF_SND_SetTrackMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, (HI_UNF_TRACK_MODE_E)arg));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_AUDIO_CHANNEL_MODE:
        {
            CHECK_FUNC_RET(HI_UNF_SND_GetTrackMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, &eTrackMode));

            arg = eTrackMode;
            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
        }
        break;
        case CMD_SET_AV_SYNC_MODE:     // cmd request construct: cmdtype | av_sync_mode_e
        {
            CHECK_FUNC_RET(HI_UNF_AVPLAY_GetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_SYNC, (HI_VOID*)&stSyncAttr));

            arg = request->readInt32();
            stSyncAttr.enSyncRef = (HI_UNF_SYNC_REF_E)arg;

            CHECK_FUNC_RET(HI_UNF_AVPLAY_SetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_SYNC, (HI_VOID*)&stSyncAttr));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_AV_SYNC_MODE:
        {
            CHECK_FUNC_RET(HI_UNF_AVPLAY_GetAttr(hAVPlayer, HI_UNF_AVPLAY_ATTR_ID_SYNC, (HI_VOID*)&stSyncAttr));

            arg = (int)stSyncAttr.enSyncRef;
            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
        }
        break;
        case CMD_SET_VIDEO_FREEZE_MODE:     // cmd request construct: cmdtype | video_freeze_mode_e
        {
            arg = request->readInt32();
            mPlayer->mWndFreezeMode = (HI_UNF_WINDOW_FREEZE_MODE_E)arg;

            LOGV("set Freeze mode %d", mPlayer->mWndFreezeMode);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_VIDEO_FREEZE_MODE:
        {
            arg = (int)mPlayer->mWndFreezeMode;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
            LOGV("get Freeze mode %d", mPlayer->mWndFreezeMode);
        }
        break;
        case CMD_SET_AUDIO_TRACK_PID:     // cmd request construct: cmdtype | int(pid)
        {
            arg = request->readInt32();
            HI_SVR_PLAYER_STREAMID_S PlayerStreamID;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID));

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo));

            if (NULL == pstFileInfo)
                break;

            HI_FORMAT_AUD_INFO_S* pWappedAudStream =
                            mpWrapperFileInfo->pastProgramInfo[PlayerStreamID.u16ProgramId].pastAudStream;
            HI_U32 wrappedStreamNum =
                            mpWrapperFileInfo->pastProgramInfo[PlayerStreamID.u16ProgramId].u32AudStreamNum;

            if (wrappedStreamNum <= 0 || (unsigned int)arg >= wrappedStreamNum)
            {
                reply->writeInt32(HI_FAILURE);
                break;
            }

            HI_FORMAT_AUD_INFO_S* pAudStream =
                        pstFileInfo->pastProgramInfo[PlayerStreamID.u16ProgramId].pastAudStream;
            HI_U32 streamNum =
                        pstFileInfo->pastProgramInfo[PlayerStreamID.u16ProgramId].u32AudStreamNum;

            if (wrappedStreamNum == streamNum) //no trueHD+AC3
            {
                PlayerStreamID.u16AudStreamId = arg;
            }
            else
            {
                HI_S32 trueHdSetting = mPlayer->getTrueHDSetting();

                for (i = 0; i < streamNum; i++)
                {
                    if (pWappedAudStream[arg].s32StreamIndex == pAudStream[i].s32StreamIndex)
                    {
                        if (-1 == pAudStream[i].s32SubStreamID)   //don't have subStream, use it directly
                        {
                            PlayerStreamID.u16AudStreamId = i;
                        }
                        else if (1 == mPlayer->getTrueHDSetting()) //have subStream, but settting use TrueHD
                        {
                            PlayerStreamID.u16AudStreamId = i;
                        }
                        else                                //have subStream and setting use sub stream(AC3)
                        {
                            for (j = 0; j < streamNum; j++)
                            {
                                if (pAudStream[i].s32SubStreamID == pAudStream[j].s32StreamIndex)
                                {
                                    PlayerStreamID.u16AudStreamId = j;
                                    break;
                                }
                            }

                            if (j >= streamNum) // if  we can't find subStream, use master by the way
                            {
                                PlayerStreamID.u16AudStreamId = i;
                            }
                        }
                        break;
                    }
                }

                if (i >= streamNum )
                {
                    reply->writeInt32(HI_FAILURE);
                    break;
                }
            }

            CHECK_FUNC_RET(HI_SVR_PLAYER_SetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_AUDIO_TRACK_PID:
        {
            HI_SVR_PLAYER_STREAMID_S PlayerStreamID;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID));

            arg = getTrueHDBySubAc3(mHandle, PlayerStreamID.u16AudStreamId);
            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(arg);
            }
        }
        break;
        case CMD_SET_SEEK_POS:
        {
            //TODO: waili will add seek by position
            // the previous arg is the high 32 bits, and the arg2 is the low 32 bits.
            HI_S64 s64Offset = 0;

            HI_S32 arg = request->readInt32();
            HI_S32 arg2 = request->readInt32();

            s64Offset = arg;
            s64Offset <<= 32;
            s64Offset += arg2;

            CHECK_FUNC_RET(HI_SVR_PLAYER_SeekPos(mHandle, s64Offset));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_FILE_INFO:
        {
            //[28] get file info
            HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);

            if (NULL == pstFileInfo)
            {
                break;
            }

            HI_SVR_PLAYER_STREAMID_S PlayerStreamID;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID));

            HI_S32 AudioIndex = PlayerStreamID.u16AudStreamId;
            HI_S32 ProgramIndex = PlayerStreamID.u16ProgramId;
            HI_S32 VideoIndex = PlayerStreamID.u16VidStreamId;

            HI_U32 u32VideoFormat = -1;
            HI_U32 u32AudioFormat = -1;

            if (0 <= ProgramIndex && ProgramIndex < (HI_S32)(pstFileInfo->u32ProgramNum))
            {
                if (0 <= VideoIndex && VideoIndex < (HI_S32)(pstFileInfo->pastProgramInfo[ProgramIndex].u32VidStreamNum))
                    u32VideoFormat = pstFileInfo->pastProgramInfo[ProgramIndex].pastVidStream[VideoIndex].u32Format;
                if (0 <= AudioIndex && AudioIndex < (HI_S32)(pstFileInfo->pastProgramInfo[ProgramIndex].u32AudStreamNum))
                    u32AudioFormat = pstFileInfo->pastProgramInfo[ProgramIndex].pastAudStream[AudioIndex].u32Format;
            }

            s32Ret = HI_SUCCESS;
            LOGV("VideoFormat: %d",u32VideoFormat);
            LOGV("AudioFormat: %d",u32AudioFormat);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(u32VideoFormat);
                reply->writeInt32(u32AudioFormat);
                reply->writeInt64(pstFileInfo->s64FileSize);
                reply->writeInt32(pstFileInfo->eSourceType);

                const HI_CHAR *pszAlbum  = "";
                const HI_CHAR *pszTitle  = "";
                const HI_CHAR *pszArtist = "";
                const HI_CHAR *pszGenre  = "";
                const HI_CHAR *pszYear   = "";

                HI_SVR_PLAYER_METADATA_S pArg;// = {0}; // add init, IMG_0005.MOV crash
                memset(&pArg, 0x00, sizeof(HI_SVR_PLAYER_METADATA_S));

                HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_METADATA, &pArg);

                HI_SVR_PLAYERKVP_S *pstKvp = pArg.pstKvp;

                for (i = 0; i < pArg.u32KvpUsedNum; i++)
                {
                    if (!strcmp(pstKvp[i].pszKey, "album"))
                    {
                        pszAlbum = pstKvp[i].unValue.pszValue;
                        LOGV("album: %s\n", pszAlbum);
                    }
                    else if (!strcmp(pstKvp[i].pszKey, "title"))
                    {
                        pszTitle = pstKvp[i].unValue.pszValue;
                        LOGV("title: %s\n", pszTitle);
                    }
                    else if (!strcmp(pstKvp[i].pszKey, "artist"))
                    {
                        pszArtist = pstKvp[i].unValue.pszValue;
                        LOGV("artist: %s\n", pszArtist);
                    }
                    else if (!strcmp(pstKvp[i].pszKey, "genre"))
                    {
                        pszGenre = pstKvp[i].unValue.pszValue;
                        LOGV("genre: %s\n", pszGenre);
                    }
                    else if (!strcmp(pstKvp[i].pszKey, "year"))
                    {
                        pszYear = pstKvp[i].unValue.pszValue;
                        LOGV("year: %s\n", pszYear);
                    }
                    else if (!strcmp(pstKvp[i].pszKey, "date"))
                    {
                        //FIXME year of song is sometimes in meta 'data',sometimes in year
                        pszYear = pstKvp[i].unValue.pszValue;
                        LOGV("date: %s\n", pszYear);
                    }

                    LOGV("meta: %s\n", pstKvp[i].pszKey);
                }

                String16 *str16Album = new String16(pszAlbum, strlen(pszAlbum));
                reply->writeString16(*str16Album);
                String16 *str16Title = new String16(pszTitle, strlen(pszTitle));
                reply->writeString16(*str16Title);
                String16 *str16Artist = new String16(pszArtist, strlen(pszArtist));
                reply->writeString16(*str16Artist);
                String16 *str16Genre = new String16(pszGenre, strlen(pszGenre));
                reply->writeString16(*str16Genre);
                String16 *str16Year = new String16(pszYear, strlen(pszYear));
                reply->writeString16(*str16Year);

                delete(str16Album);
                delete(str16Title);
                delete(str16Artist);
                delete(str16Genre);
                delete(str16Year);
            }
        }
        break;

        case CMD_SET_OUTRANGE:
        {
            HI_S32 top = 0, left = 0, width = 0, height = 0;

            top    = request->readInt32();
            left   = request->readInt32();
            width  = request->readInt32();
            height = request->readInt32();

            if (width <0 || height <0)
            {
                s32Ret = -1;

                if( NULL != reply)
                {
                    reply->writeInt32( s32Ret);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return BAD_VALUE;
            }

            LOGV("Invoke setOutRange [%d %d %d %d]", top, left, width, height);

            mPlayer->setOutRange(top, left, width, height);

            if ( NULL != reply)
            {
                reply->writeInt32( s32Ret);
            }
        }
        break;
        case CMD_SET_SUB_ID:
        {
            /*reques Data Format: type(32)| subtitleId(32)  ;reply Data Format: ret(32)*/
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_U32 s32SubtitleNum, s32SubtitleId;
            HI_S32 s32Width = 0, s32Height = 0;

            s32SubtitleId = request->readInt32();
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            if ( s32SubtitleId == stStreamId.u16SubStreamId )
            {
                //check is current id is what we want, do nothing.
                if (NULL != reply)
                {
                    reply->writeInt32( s32Ret);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return s32Ret;
            }

            HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);

            if (NULL == pstFileInfo)
                break;

            s32SubtitleNum = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum;

            if ( s32SubtitleId < s32SubtitleNum)//check the value is ok
            {
                stStreamId.u16SubStreamId = s32SubtitleId;
                LOGV("[CMD_SET_SUB_CHANGE] dataTransact  set subtitle Id is :%d", stStreamId.u16SubStreamId);
                CHECK_FUNC_RET(HI_SVR_PLAYER_SetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));
            }
            else
            {
                s32Ret = HI_FAILURE;
            }

            s32Width = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[
                stStreamId.u16SubStreamId].u16OriginalFrameWidth;
            s32Height = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[
                stStreamId.u16SubStreamId].u16OriginalFrameHeight;

            LOGV("[CMD_SET_SUB_CHANGE] dataTransact  set subtitle");

            if (NULL != reply)
            {
                reply->writeInt32( s32Ret);
            }

            if ( mPlayer->getSubManager()->getInitialized() )
            {
                mPlayer->getSubManager()->clearLastBuffer();//added for clear lastSubtitle
                HI_S32 ret = mPlayer->getSubManager()->setRawPicSize(s32Width, s32Height);

                if (HI_SUCCESS != ret)
                {
                    s32Width = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u16Width;
                    s32Height= pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId].u16Height;
                    mPlayer->getSubManager()->setRawPicSize(s32Width, s32Height);
                }
            }
        }
        break;
        case CMD_GET_SUB_ID:
        {
            /*reques Data Format: type(32)| subtitleId(32) ; reply Data Format: ret(32)| SubID(32)*/
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            SUB_GET_ITEM(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            if (NULL != reply)
            {
                reply->writeInt32( stStreamId.u16SubStreamId);
            }
        }
        break;
        case CMD_GET_SUB_INFO:
        {
            /*request Data Format: type(32) ;reply Data format: ret(32)|subtitleNum(32)|SubId0(32)|isextra_sub0(32)|subName0(HI_FORMAT_SUB_TITLE_LEN)|IsGfxSub(32)|...*/
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_FORMAT_SUB_INFO_S *pstSubtitleInfo;
            HI_U32 s32SubtitleNum = 0;
            const HI_CHAR *pszLanguage  = "-";

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            s32Ret = HI_SUCCESS;

            if (NULL != reply)
            {
                reply->writeInt32( s32Ret );
            }

            HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);

            if (NULL == pstFileInfo)
                break;

            s32SubtitleNum = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum;

            if (NULL != reply)
            {
                reply->writeInt32( s32SubtitleNum );
            }

            LOGV(" [CMD_GET_SUB_INFO] subtitle Num:%d ", s32SubtitleNum);

            for (i=0; i < s32SubtitleNum; i++)
            {
                pstSubtitleInfo = &(pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[i]);

                if (NULL != reply)
                {
                    reply->writeInt32(i);
                    reply->writeInt32(pstSubtitleInfo->bExtSub);

                    if (0 == strlen(pstSubtitleInfo->paszLanguage[0]))
                    {
                        String16 pstr16(pszLanguage, strlen(pszLanguage));
                        reply->writeString16(pstr16);
                    }
                    else
                    {
                        String16 pstr16(pstSubtitleInfo->paszLanguage[0], strlen(pstSubtitleInfo->paszLanguage[0]));
                        reply->writeString16(pstr16);
                    }

                    reply->writeInt32(pstSubtitleInfo->u32Format);
                }
                LOGV(" [CMD_GET_SUB_INFO] subtitleInfo isExtraSub:%d, language is %s, len = %d",
                pstSubtitleInfo->bExtSub, pstSubtitleInfo->paszLanguage[0], strlen(pstSubtitleInfo->paszLanguage[0]));
            }
        }
        break;
        case CMD_GET_AUDIO_INFO:
        {
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_FORMAT_AUD_INFO_S *pstAudInfo;
            HI_S32 s32AudioTrackNum = 0;

            String16 *pstr16 = NULL;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            s32Ret = HI_SUCCESS;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }

            s32AudioTrackNum = mpWrapperFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum;

            if (NULL != reply)
            {
                reply->writeInt32(s32AudioTrackNum);
            }

            for (i = 0; i < (HI_U32)(s32AudioTrackNum); i++)
            {
                pstAudInfo = &(mpWrapperFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastAudStream[i]);

                if (NULL != reply)
                {
                    pstr16 = new String16(pstAudInfo->aszLanguage, strlen(pstAudInfo->aszLanguage));
                    reply->writeString16(*pstr16);
                    reply->writeInt32(pstAudInfo->u32Format);
                    reply->writeInt32(pstAudInfo->u32SampleRate);
                    reply->writeInt32(pstAudInfo->u16Channels);
                }
                LOGV("name:%s", pstAudInfo->aszLanguage);
                LOGV("audioFormat:%d", pstAudInfo->u32Format);
                LOGV("sampleRate:%d", pstAudInfo->u32SampleRate);
                LOGV("channel:%d", pstAudInfo->u16Channels);
            }
        }
        break;
        case CMD_GET_VIDEO_INFO:
        {
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_FORMAT_VID_INFO_S pstVidInfo;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            s32Ret = HI_SUCCESS;
            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }

            HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo);

            if (NULL == pstFileInfo)
                break;

            if (0 == pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32VidStreamNum
                || NULL == pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream)
            {
                LOGE("there is no video stream info");
                break;
            }

            pstVidInfo = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId];

            if (NULL != reply)
            {
                reply->writeInt32(pstVidInfo.u32Format);
                reply->writeInt32(pstVidInfo.u16FpsInteger);
                reply->writeInt32(pstVidInfo.u16FpsDecimal);
            }
        }
        break;
        case CMD_SET_3D_FORMAT:
        {
             int VideoFMT = request->readInt32();
             LOGV("[CMD_SET_3D_FORMAT] Video Format = %d",VideoFMT);
             s32Ret = mPlayer->SetStereoVideoFmt(VideoFMT);
             if( NULL != reply)
             {
                 reply->writeInt32(s32Ret);
             }
        }
        break;
        case CMD_SET_SUB_FONT_SIZE:
        {
            /*request Data Format: type(32) | size(32); reply Data Format: ret(32) */
            HI_S32 s32Size = 0;
            s32Size = request->readInt32();
            LOGV("[CMD_SET_SUB_FONT_SIZE] size:%d", s32Size);
            SUB_POST_BUFFER(mPlayer->getSubManager()->setFontSize( s32Size ));
        }
        break;
        case CMD_GET_SUB_FONT_SIZE:
        {
            /*request Data Format: type(32) ;reply Data Format: ret(32) | size(32)*/
            HI_S32 s32Size;
            SUB_GET_ITEM(mPlayer->getSubManager()->getFontSize(s32Size));

            if ( NULL != reply )
            {
                reply->writeInt32(s32Size);
            }
        }
        break;
        case CMD_SET_SUB_FONT_POSITION:
        {
            /*request Data Format: type(32) | H(32) |V(32) */
            HI_S32 s32X, s32Y;
            s32X = request->readInt32();
            s32Y = request->readInt32();
            LOGV("[CMD_SET_SUB_FONT_POSITION] s32X = %d,s32Y = %d",s32X,s32Y);
            SUB_POST_BUFFER(mPlayer->getSubManager()->setSubPlace(s32X, s32Y));
        }
        break;
        case CMD_GET_SUB_FONT_POSITION:
        {
            /*request Data Format: type(32) ; reply Data Format:ret(32)|H(32)|V(32) */
            HI_S32 s32X, s32Y;

            SUB_GET_ITEM(mPlayer->getSubManager()->getSubPlace(s32X, s32Y));

            if (NULL != reply)
            {
                reply->writeInt32(s32X);
                reply->writeInt32(s32Y);
            }
        }
        break;
        case CMD_SET_SUB_FONT_HORIZONTAL:
        {
            /*request Data Format: type(32)|H(32) ; reply Data Format:ret(32) */
            HI_S32 s32Horizontal = 0;
            s32Horizontal = request->readInt32();
            SUB_POST_BUFFER(mPlayer->getSubManager()->setHorizontal( s32Horizontal ));
        }
        break;
        case CMD_GET_SUB_FONT_HORIZONTAL:
        {
            /*request Data Format: type(32) ; reply Data Format:ret(32)|H(32) */
            HI_S32 s32Horizontal, s32Vertical;
            SUB_GET_ITEM(mPlayer->getSubManager()->getSubPlace(s32Horizontal, s32Vertical));
            if (NULL != reply)
            {
                reply->writeInt32( s32Horizontal);
            }
        }
        break;
        case CMD_SET_SUB_FONT_VERTICAL:
        {
            /*request Data Format: type(32)|V(32) ; reply Data Format:ret(32) */
            HI_S32 s32Vertical;
            s32Vertical = request->readInt32();
            SUB_POST_BUFFER(mPlayer->getSubManager()->setVertical( s32Vertical ));
        }
        break;
        case CMD_GET_SUB_FONT_VERTICAL:
        {
            /*request Data Format: type(32) ; reply Data Format:ret(32)|V(32) */
            HI_S32 s32Horizontal,s32Vertical;
            SUB_GET_ITEM(mPlayer->getSubManager()->getSubPlace(s32Horizontal, s32Vertical));
            if (NULL != reply)
            {
               reply->writeInt32( s32Vertical);
            }
        }
        break;
        case CMD_SET_SUB_FONT_ALIGNMENT:
        {
            /*request Data Format: type(32) | data(alignment)(0(Center),1(Left),2(Right)) */
            HI_S32 s32Align;
            s32Align = request->readInt32();
            SUB_POST_BUFFER(mPlayer->getSubManager()->setAlignment( s32Align ));
        }
        break;
        case CMD_GET_SUB_FONT_ALIGNMENT:
        {
            /*request Data Format: type(32);reply Data Format:ret(32) | data(alignment)(0(Center),1(Left),2(Right)) */
            HI_S32 s32Align;
            SUB_GET_ITEM(mPlayer->getSubManager()->getAlignment(s32Align));
            if (NULL != reply)
            {
                reply->writeInt32( s32Align);
            }
        }
        break;
        case CMD_SET_SUB_FONT_COLOR:
        {
            /*request Data Format: type(32) | color(32); reply Data Format: ret(32) */
            HI_U32 s32Color;
            s32Color = (HI_U32)request->readInt32();
            LOGV("[CMD_SET_SUB_FONT_COLOR] subcolors32Color = %d",s32Color);
            SUB_POST_BUFFER( mPlayer->getSubManager()->setSubColor( s32Color ));
        }
        break;
        case CMD_GET_SUB_FONT_COLOR:
        {
            /*request Data Format: type(32); reply Data Format: ret(32) | color(32) */
            HI_U32 u32Color;
            SUB_GET_ITEM(mPlayer->getSubManager()->getSubColor(u32Color));
            if (NULL != reply)
            {
                reply->writeInt32( u32Color);
            }
        }
        break;
        case CMD_SET_SUB_FONT_BACKCOLOR:
        {
            /*request Data Format: type(32) | color(32) ;reply Data Format: ret(32)*/
            HI_U64 u64Color;
            u64Color = (HI_U64)request->readInt32();
            SUB_POST_BUFFER(mPlayer->getSubManager()->setBkgroundcolor( u64Color ));
        }
        break;
        case CMD_GET_SUB_FONT_BACKCOLOR:
        {
            /*request Data Format: type(32) ;reply Data Format:ret(32) | color(32) */
            HI_U32 u32Color;
            SUB_GET_ITEM(mPlayer->getSubManager()->getBkgroundcolor(u32Color));
            if (NULL != reply)
            {
                reply->writeInt32( u32Color);
            }
        }
        break;
        case CMD_SET_SUB_FONT_SHADOW:
        {
            /*request Data Format: type(32) | IsDraw(32); reply Data Format: ret(32)*/
            HI_S32 s32DrawType = HI_FONT_DRAW_SHADOW;
            s32DrawType = request->readInt32();
            if (s32DrawType > 0)
                s32DrawType = HI_FONT_DRAW_SHADOW;
            else
                s32DrawType = HI_FONT_DRAW_NORMAL;
            SUB_POST_BUFFER(mPlayer->getSubManager()->setFontDrawType( s32DrawType));
        }
        break;
        case CMD_GET_SUB_FONT_SHADOW:
        {
            /*request Data Format: type(32) ; reply Data Format: ret(32)| IsDraw(32)*/
            HI_S32  s32Type;
            SUB_GET_ITEM(mPlayer->getSubManager()->getFontDrawType(s32Type));
            if (NULL != reply)
            {
                if (s32Type == HI_FONT_DRAW_SHADOW)
                    s32Type = 1;
                else
                    s32Type = 0;
                reply->writeInt32( s32Type);
            }
        }
        break;
        case CMD_SET_SUB_FONT_HOLLOW:
        {
            /*request Data Format: type(32) | IsDraw(32); reply Data Format: ret(32)*/
            HI_S32 s32DrawType = HI_FONT_DRAW_HOLLOW;
            s32DrawType = request->readInt32();

            if (s32DrawType > 0)
                s32DrawType = HI_FONT_DRAW_HOLLOW;
            else
                s32DrawType = HI_FONT_DRAW_NORMAL;
            SUB_POST_BUFFER(mPlayer->getSubManager()->setFontDrawType( s32DrawType));
        }
        break;
        case CMD_GET_SUB_FONT_HOLLOW:
        {
            /*request Data Format: type(32) ; reply Data Format: ret(32)| IsDraw(32)*/
            HI_S32 s32Type;
            SUB_GET_ITEM(mPlayer->getSubManager()->getFontDrawType(s32Type));
            if (NULL != reply)
            {
                if (s32Type == HI_FONT_DRAW_HOLLOW)
                    s32Type = 1;
                else
                    s32Type = 0;
                reply->writeInt32( s32Type);
            }
        }
        break;
        case CMD_SET_SUB_FONT_SPACE:
        {
            /*request Data Format: type(32) | Space(32) ;reply Data Format: ret(32)*/
            HI_S32 s32Space;
            s32Space = request->readInt32();
            SUB_POST_BUFFER( mPlayer->getSubManager()->setFontspace( s32Space ));
        }
        break;
        case CMD_GET_SUB_FONT_SPACE:
        {
            /*request Data Format: type(32) | Space(32); reply Data Format:ret(32)|Space(32) */
            HI_S32 s32Space;
            SUB_GET_ITEM(mPlayer->getSubManager()->getFontspace(s32Space));
            if(NULL != reply)
            {
                reply->writeInt32( s32Space);
            }
        }
        break;
        case CMD_SET_SUB_FONT_LINESPACE:
        {
            /*request Data Format: type(32) | Line(32); reply Data Format: ret(32) */
            HI_S32 s32Line;
            s32Line = request->readInt32();
            SUB_POST_BUFFER(mPlayer->getSubManager()->setLineSpacing( s32Line ));
        }
        break;
        case CMD_GET_SUB_FONT_LINESPACE:
        {
            /*request Data Format: type(32); reply Data Format: ret(32) | Line(32) */
            HI_S32 s32Line;
            SUB_GET_ITEM(mPlayer->getSubManager()->getLineSpace(s32Line));
            if (NULL != reply)
            {
                reply->writeInt32( s32Line);
            }
        }
        break;
        case CMD_SET_SUB_FONT_PATH:
        {
            /*request Data Format: type(32)|filename(String16); reply Data Format: ret(32)*/
            String16 sfontpath;
            HI_S32  hisize;
            HI_CHAR hichars[HI_FORMAT_MAX_URL_LEN];
            sfontpath = request->readString16();

            if ( sfontpath.size() == 0 )
            {
                LOGV("[CMD_SET_SUB_FONT_PATH] Can't set Subtitle file, Subtitle File is NULL!");
                s32Ret = HI_FAILURE;

                if (NULL != reply)
                {
                    reply->writeInt32( s32Ret);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return s32Ret;
            }
            utf16_to_utf8(sfontpath.string(), sfontpath.size(), hichars);
            LOGV("[CMD_SET_SUB_FONT_PATH] font path = %s",hichars);
            SUB_POST_BUFFER(mPlayer->getSubManager()->setFontPath(hichars));
        }
        break;
        case CMD_GET_SUB_FONT_PATH:
        {
            /*request Data Format:type(32) ; reply Data Format:ret(32) | filename(String16)*/
            String16 *sfontpath;
            HI_CHAR hichars[HI_FORMAT_MAX_URL_LEN];
            SUB_GET_ITEM(mPlayer->getSubManager()->getFontPath(hichars));

            if (NULL != reply)
            {
                sfontpath = new String16(hichars, strlen(hichars));
                reply->writeString16(*sfontpath);
            }
        }
        break;
        case CMD_SET_SUB_FONT_ENCODE:
        {
            HI_S32 s32CodeType;
            s32CodeType = request->readInt32();
            CHECK_FUNC_RET(HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_SOURCE_CODETYPE,
                &s32CodeType));/* set invoke for codetype */

            if (NULL != reply)
            {
                reply->writeInt32( HI_SUCCESS);
            }
        }
        break;
        case CMD_GET_SUB_FONT_ENCODE:
        {
            /*request Data Format:type(32); reply Data Format:ret(32) | encode(int)*/
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_U32 u32CodeType;
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo));

            u32CodeType = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[stStreamId.u16SubStreamId].u32CharSet;
            LOGV("[CMD_GET_SUB_FONT_ENCODE]codetype:%d", u32CodeType);
            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
                reply->writeInt32(u32CodeType);
            }
        }
        break;
        case CMD_SET_SUB_TIME_SYNC:
        {
            /*request Data Format: type(32)|VideoFrameOffset(32)ms|AudioFrameOffset(32)ms|SubOffset(32)ms */
            HI_SVR_PLAYER_SYNC_ATTR_S stSyncAttr;

            if (HI_SUCCESS != HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_SYNC, (HI_VOID*)&stSyncAttr))
            {
                LOGE("set sub time sync,get current avsync info fail");
                if (NULL != reply)
                    reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }

            stSyncAttr.s32VidFrameOffset = request->readInt32();
            stSyncAttr.s32AudFrameOffset = request->readInt32();
            stSyncAttr.s32SubTitleOffset = request->readInt32();
            LOGV("[CMD_SET_SUB_TIME_SYNC] sync %d %d %d",
                stSyncAttr.s32VidFrameOffset, stSyncAttr.s32AudFrameOffset, stSyncAttr.s32SubTitleOffset);
            CHECK_FUNC_RET(HI_SVR_PLAYER_SetParam(mHandle, HI_SVR_PLAYER_ATTR_SYNC, (HI_VOID*)&stSyncAttr));
            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
            }
        }
        break;
        case CMD_GET_SUB_TIME_SYNC:
        {
            /*request Data Format: type(32); reply Data Format:ret(32) |VideoFrameOffset(32)ms|AudioFrameOffset(32)ms|SubOffset(32)ms */
            HI_SVR_PLAYER_SYNC_ATTR_S stSyncAttr;
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_SYNC, (HI_VOID*)&stSyncAttr));

            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
                reply->writeInt32(stSyncAttr.s32VidFrameOffset);
                reply->writeInt32(stSyncAttr.s32AudFrameOffset);
                reply->writeInt32(stSyncAttr.s32SubTitleOffset);
            }
        }
        break;
        case CMD_SET_SUB_EXTRA_SUBNAME:
        {
            /*request Data Format:type(32)| fileNames(Strings)*/
            HI_SVR_PLAYER_MEDIA_S stMedia;
            HI_S32  hisize;
            String16 str16Ret;
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_CHAR hichars[HI_FORMAT_MAX_URL_LEN];
            HI_S32 s32Width, s32Height;

            memset(&stStreamId, 0, sizeof(stStreamId));
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));
            memset(&stMedia, 0, sizeof(stMedia));
            str16Ret = request->readString16();

            if ( str16Ret.size() == 0 )
            {
                LOGV("[CMD_SET_SUB_EXTRA_SUBNAME] Can't set Subtitle file, Subtitle File is NULL!");
                s32Ret = HI_FAILURE;

                if (NULL != reply)
                {
                    reply->writeInt32(s32Ret);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return s32Ret;
            }

            utf16_to_utf8(str16Ret.string(), str16Ret.size(), hichars);
            sprintf(stMedia.aszExtSubUrl[0], "%s", hichars);
            stMedia.u32ExtSubNum = 1;

            CHECK_FUNC_RET( HI_SVR_PLAYER_SetMedia(mHandle, HI_SVR_PLAYER_MEDIA_SUBTITLE, &stMedia));

            LOGV("[CMD_SET_SUB_EXTRA_SUBNAME] subname: %s %d hPlayer : %x",  stMedia.aszExtSubUrl[0], __LINE__, mHandle);
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo));

            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
            }

            HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId);

            s32Width = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[
                stStreamId.u16SubStreamId].u16OriginalFrameWidth;
            s32Height = pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[
                stStreamId.u16SubStreamId].u16OriginalFrameHeight;

            if ( mPlayer->getSubManager()->getInitialized() )
            {
                mPlayer->getSubManager()->setRawPicSize(s32Width, s32Height);
            }
        }
        break;
        case CMD_SET_SUB_FONT_STYLE:
        {
            /*request Data Format: type(32) | IsDraw(32); reply Data Format: ret(32)*/
            HI_S32 s32DrawType;
            s32DrawType = request->readInt32();
            SUB_POST_BUFFER(mPlayer->getSubManager()->setFontDrawType( s32DrawType));
        }
        break;
        case CMD_GET_SUB_FONT_STYLE:
        {
            /*request Data Format: type(32) ; reply Data Format: ret(32)| IsDraw(32)*/
            HI_S32  s32Type;
            SUB_GET_ITEM(mPlayer->getSubManager()->getFontDrawType(s32Type));
            if (NULL != reply)
            {
                reply->writeInt32( s32Type);
            }
        }
        break;
        case CMD_SET_SUB_DISABLE:
        {
            /*request Data Format: type(32) | IsDisable(32); reply Data Format: ret(32)*/
            HI_S32 s32Disable;
            s32Disable = request->readInt32();

            if (mPlayer->getSubManager()->getInitialized() == false)
            {
                /*check is initial*/
                if (NULL != reply )
                {
                    reply->writeInt32(-1);
                }
            }

            s32Ret = mPlayer->getSubManager()->setDisableSubtitle( s32Disable);

            if (s32Disable <= 0)
            {
                mPlayer->getSubManager()->postBuffer(subManager::TYPE_DRAW);
            }
            else
            {
                mPlayer->getSubManager()->postBuffer(subManager::TYPE_CLEAR);
            }

            if (NULL != reply)
            {
                reply->writeInt32( ret );
            }
        }
        break;
        case CMD_GET_SUB_DISABLE:
        {
            /*request Data Format: type(32) ; reply Data Format: ret(32)| IsDisable(32)*/
            HI_S32  s32Disable;
            SUB_GET_ITEM(mPlayer->getSubManager()->getDisableSubtitle(s32Disable));

            if (NULL != reply)
            {
                reply->writeInt32( s32Disable);
            }
        }
        break;
        case CMD_GET_SUB_ISBMP:
        {
            HI_SVR_PLAYER_STREAMID_S stStreamId;
            HI_FORMAT_SUBTITLE_TYPE_E eSubType;
            HI_S32 s32Data = 0;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId));

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo));
            eSubType =
                (HI_FORMAT_SUBTITLE_TYPE_E)pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[stStreamId.u16SubStreamId].u32Format;
            if (HI_FORMAT_SUBTITLE_HDMV_PGS == eSubType ||
                HI_FORMAT_SUBTITLE_DVB_SUB == eSubType ||
                HI_FORMAT_SUBTITLE_DVD_SUB == eSubType)
            {
                s32Data = 1;
            }
            else
            {
                s32Data = 0;
            }

            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
                reply->writeInt32(s32Data);
            }
        }
        break;
        case CMD_SET_SUB_CONFIG_PATH:
        {
            String16 sfontpath;
            HI_S32  hisize;
            HI_CHAR hichars[HI_FORMAT_MAX_URL_LEN];
            sfontpath = request->readString16();

            if ( sfontpath.size() == 0 )
            {
                LOGV("[CMD_SET_SUB_FONT_PATH] Can't set Subtitle file, Subtitle File is NULL!");
                s32Ret = HI_FAILURE;
                if (NULL != reply)
                {
                    reply->writeInt32( s32Ret);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return s32Ret;
            }

            utf16_to_utf8(sfontpath.string(), sfontpath.size(), hichars);
            LOGV("[CMD_SET_SUB_CONFIG_PATH] font config path = %s",hichars);
            SUB_GET_ITEM(mPlayer->mSubManager->setConfigPath(hichars));
        }
        break;
        case CMD_SET_VOLUME_LOCK:
        {
            //141 set VolumeLock
            HI_S32 s32VolumeLock = request->readInt32();

            LOGV("invoke: CMD_SET_VOLUME_ALWAYS_MUTE(%d -> %d)", mPlayer->mVolumeLock, s32VolumeLock);

            if ((s32VolumeLock==0)||(s32VolumeLock==1))
            {
                mPlayer->mVolumeLock = s32VolumeLock;
                if (NULL != reply)
                {
                    reply->writeInt32(HI_SUCCESS);
                }
            }
            else
            {
                LOGE("invoke: CMD_SET_VOLUME_ALWAYS_MUTE(%d -> %d) failed, Only 0 or 1 is available", mPlayer->mVolumeLock, s32VolumeLock);
                if (NULL != reply)
                {
                    reply->writeInt32(HI_FAILURE);
                }
            }
        }
        break;
        case CMD_GET_VOLUME_LOCK:
        {
            //142 get VolumeLock
            LOGV("invoke: CMD_GET_VOLUME_ALWAYS_MUTE(%d)", mPlayer->mVolumeLock);

            s32Ret = HI_SUCCESS;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(mPlayer->mVolumeLock);
            }
        }
        break;
        case CMD_GET_AVPLAY_HANDLE:
        {
            //143  get AVPlay handle
            LOGV("invoke(%d): CMD_GET_AVPLAY_HANDLE(%d)",CMD_GET_AVPLAY_HANDLE);

            s32Ret = HI_SUCCESS;
            HI_HANDLE hAVPlay_handle = HI_INVALID_HANDLE;
            s32Ret = HI_SVR_PLAYER_GetParam(mPlayer->mHandle, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAVPlay_handle);

            if (s32Ret !=HI_SUCCESS)
            {
                ALOGE("[%4d]@HiMediaPlayer.cpp Get AVPlay handle fail ", __LINE__);
            }

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(hAVPlay_handle);
            }
        }
        break;
        case CMD_SET_STOP_FASTPLAY:
        {
            CHECK_FUNC_RET(HI_SVR_PLAYER_Resume(mHandle));
            wait();
            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
            }
        }
        break;
        case CMD_SET_FORWORD:
        {
            arg = request->readInt32();
            arg *= HI_SVR_PLAYER_PLAY_SPEED_NORMAL ;
            CHECK_FUNC_RET(HI_SVR_PLAYER_TPlay(mHandle, arg));
            wait();

            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
            }
        }
        break;
        case CMD_SET_REWIND:
        {
            arg = request->readInt32();
            arg *= HI_SVR_PLAYER_PLAY_SPEED_NORMAL ;
            CHECK_FUNC_RET(HI_SVR_PLAYER_TPlay(mHandle, -arg));
            wait();

            if (NULL != reply)
            {
                reply->writeInt32(HI_SUCCESS);
            }
        }
        break;
        case CMD_GET_PID_NUMBER:
        {
            HI_SVR_PLAYER_STREAMID_S PlayerStreamID;
            HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_STREAMID, &PlayerStreamID);

            if (NULL != reply)
                reply->writeInt32(s32Ret);
            for (i = 0; i < mpWrapperFileInfo->u32ProgramNum; i++)
            {
                if (i == PlayerStreamID.u16ProgramId)
                {
                    if (NULL != reply)
                    {
                        reply->writeInt32(mpWrapperFileInfo->pastProgramInfo[i].u32AudStreamNum);
                    }
                }
            }
        }
        break;
        case CMD_GET_PROGRAM_NUMBER:
        {
            CHECK_FUNC_RET(HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo));
            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(pstFileInfo->u32ProgramNum);
            }
        }
        break;
        case CMD_GET_PROGRAM_STREAM_TYPE:
        {
            //request: type , reply: ret | stream type(int)

            s32Ret = 0;

            CHECK_FUNC_RET(HI_SVR_PLAYER_GetFileInfo(mHandle, &pstFileInfo));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(pstFileInfo->eSourceType);
            }
        }
        break;

        // For Http Live Streaming
        case CMD_GET_HLS_STREAM_NUM:
        {
            HI_S32 stream_num = -1;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_HLS_STREAM_NUM, (HI_VOID *)&stream_num);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(stream_num);
            }
        }
        break;
        case CMD_GET_HLS_BANDWIDTH:
        {
            HI_S64 bandwidth = 0;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BANDWIDTH, (HI_VOID *)&bandwidth);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt64(bandwidth);
            }
        }
        break;
        case CMD_GET_HLS_STREAM_INFO:
        {
            HI_FORMAT_HLS_STREAM_INFO_S stream_info;

            stream_info.stream_nb = request->readInt32();
            stream_info.bandwidth = 0;
            stream_info.hls_segment_nb = 0;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_HLS_STREAM_INFO, (HI_VOID *)&stream_info);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(stream_info.stream_nb);
                reply->writeInt32(stream_info.bandwidth);
                reply->writeInt32(stream_info.hls_segment_nb);
                String16 *temp_url = new String16(stream_info.url, strlen(stream_info.url));
                reply->writeString16(*temp_url);
            }
        }
        break;
        case CMD_GET_HLS_SEGMENT_INFO:
        {
            HI_FORMAT_HLS_SEGMENT_INFO_S segment_info;

            segment_info.stream_num = -1;
            segment_info.total_time = 0;
            segment_info.bandwidth  = 0;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_HLS_SEGMENT_INFO, (HI_VOID *)&segment_info);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(segment_info.stream_num);
                reply->writeInt32(segment_info.total_time);
                reply->writeInt32(segment_info.bandwidth);
                reply->writeInt32(segment_info.seq_num);
                String16 *temp_url = new String16(segment_info.url, strlen(segment_info.url));
                reply->writeString16(*temp_url);
            }
        }
        break;
        case CMD_SET_HLS_STREAM_ID:
        {
            HI_S32 stream_id = request->readInt32();

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_HLS_STREAM, (void *)stream_id);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_PLAYLIST_STREAM_DETAIL_INFO:
        {
            HI_S32 s32Ret = HI_FAILURE;
            HI_FORMAT_PLAYLIST_STREAM_DETAIL_S* PlaylistDetailInfo = NULL;
            HI_U32 i =0;
            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_PLAYLIST_STREAM_DETAIL_INFO,
                (void *)(&PlaylistDetailInfo));
            if (HI_FAILURE == s32Ret || NULL == PlaylistDetailInfo)
            {
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }

            reply->writeInt32(NO_ERROR);
            reply->writeInt32((int32_t)PlaylistDetailInfo->playlist_type);
            reply->writeInt32(PlaylistDetailInfo->bandwidth);
            String16 strUrl(PlaylistDetailInfo->url, strlen(PlaylistDetailInfo->url));
            reply->writeString16(strUrl);
            // segmentinfo
            reply->writeInt32(PlaylistDetailInfo->SEGMENT_LIST_S.index);
            reply->writeInt32(PlaylistDetailInfo->SEGMENT_LIST_S.finished);
            reply->writeInt32(PlaylistDetailInfo->SEGMENT_LIST_S.target_duration);
            reply->writeInt32(PlaylistDetailInfo->SEGMENT_LIST_S.segment_nb);
            // every segmentinfo
            if (NULL != PlaylistDetailInfo->SEGMENT_LIST_S.segments)
            {
                for (i = 0; i < (HI_U32)(PlaylistDetailInfo->SEGMENT_LIST_S.segment_nb); i++)
                {
                    HI_FORMAT_PLAYLIST_SEGMENT_DETAIL_INFO_S *TempSegInfo = PlaylistDetailInfo->SEGMENT_LIST_S.segments[i];
                    if (NULL == TempSegInfo)
                    {
                        LOGE("get playlist detail inifo error,seginfo idx %d is NULL", i);
                        reply->setDataPosition(0);
                        reply->writeInt32(UNKNOWN_ERROR);
                        LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                        return UNKNOWN_ERROR;
                    }
                    reply->writeInt32(TempSegInfo->start_time);
                    reply->writeInt32(TempSegInfo->total_time);
                    String16 strSegUrl(TempSegInfo->url, strlen(TempSegInfo->url));
                    reply->writeString16(strSegUrl);
                    String16 strKey(TempSegInfo->key, strlen(TempSegInfo->key));
                    reply->writeString16(strKey);
                    reply->writeInt32((HI_U32)TempSegInfo->key_type);
                    //reply->write(TempSegInfo->iv, AES_IV_LEN);
                }
            }
        }
        break;
        case CMD_SET_BUFFERSIZE_CONFIG:
        {
            /*request: type | buffer size(int) Kbytes | start size(Kbytes)
                        | enough size(Kbytes) | timeout(ms), reply:ret(int)*/
            HI_S32 s32KBytes = request->readInt32();
            HI_S32 s32Start  = request->readInt32();
            HI_S32 s32Enough = request->readInt32();
            HI_S32 s32TimeOut= request->readInt32();

            if (s32KBytes <= 0 || s32TimeOut <= 0
                || !(s32Start < s32Enough && s32Enough <= s32KBytes && s32Start >=0))
            {
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return HI_FAILURE;
            }

            HI_FORMAT_BUFFER_CONFIG_S stConfig;

            stConfig.eType          = HI_FORMAT_BUFFER_CONFIG_SIZE;
            stConfig.s64Total       = s32KBytes *1024;
            stConfig.s64EventEnough = s32Enough *1024;
            stConfig.s64EventStart  = s32Start  *1024;
            stConfig.s64TimeOut     = s32TimeOut; /*ms*/
            CHECK_FUNC_RET(HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_CONFIG, &stConfig));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_BUFFERSIZE_CONFIG:
        {
            /* request: type,reply:ret(int)|size(int) Kbytes |start size(Kbytes)| enough size(Kbytes)|timeout(ms) */
            HI_FORMAT_BUFFER_CONFIG_S stConfig;

            stConfig.eType = HI_FORMAT_BUFFER_CONFIG_SIZE;
            CHECK_FUNC_RET(HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, &stConfig));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(stConfig.s64Total/1024);
                reply->writeInt32(stConfig.s64EventStart/1024);
                reply->writeInt32(stConfig.s64EventEnough/1024);
                reply->writeInt32(stConfig.s64TimeOut);
            }
        }
        break;
        case CMD_SET_BUFFERTIME_CONFIG:
        {
            /* request: type(int)|time(int) ms |start time(ms)|enough time(ms) |timeout(ms), reply:ret(int) */
            HI_S32 s32Ms = request->readInt32();
            HI_S32 s32Start  = request->readInt32();
            HI_S32 s32Enough = request->readInt32();
            HI_S32 s32TimeOut= request->readInt32();

            if (s32Ms <= 0 || s32TimeOut <= 0
                || !(s32Start < s32Enough && s32Enough <= s32Ms && s32Start >=0))
            {
                if (NULL != reply)
                {
                    reply->writeInt32(HI_FAILURE);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return HI_FAILURE;
            }

            HI_FORMAT_BUFFER_CONFIG_S stConfig;

            stConfig.eType          = HI_FORMAT_BUFFER_CONFIG_TIME;
            stConfig.s64Total       = s32Ms;
            stConfig.s64EventEnough = s32Enough;
            stConfig.s64EventStart  = s32Start;
            stConfig.s64TimeOut     = s32TimeOut; /*ms*/

            CHECK_FUNC_RET(HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_CONFIG, &stConfig));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_BUFFERTIME_CONFIG:
        {
            /* request:type, reply:ret(int) |Total(int) ms |start(int) ms | enought(int)ms | timeout(int) ms */
            HI_FORMAT_BUFFER_CONFIG_S stConfig;
            stConfig.eType          = HI_FORMAT_BUFFER_CONFIG_TIME;
            CHECK_FUNC_RET(HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, &stConfig));

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(stConfig.s64Total);
                reply->writeInt32(stConfig.s64EventStart);
                reply->writeInt32(stConfig.s64EventEnough);
                reply->writeInt32(stConfig.s64TimeOut);
            }
        }
        break;
        case CMD_GET_BUFFER_STATUS:
        {
            /* request:Type, reply:ret(int) | size(int) Kbytes | time(int) ms */
            HI_FORMAT_BUFFER_STATUS_S stStatus;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_STATUS, (HI_VOID *)&stStatus);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(stStatus.s64BufferSize/1024);
                reply->writeInt32(stStatus.s64Duration);
            }
        }
        break;
        case CMD_GET_DOWNLOAD_SPEED:
        {
            /* request:Type, reply: ret(int) | speed(int) bps */
            HI_S32 bandwidth = 0;

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BANDWIDTH, (HI_VOID *)&bandwidth);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(bandwidth);
            }
        }
        break;
        case CMD_SET_BUFFER_MAX_SIZE:
        {
            /* request:Type| size(int) Kbytes, reply: ret(int)  */
            HI_S32 s32Size = request->readInt32();

            if (s32Size <= 0)
            {
                if (NULL != reply)
                {
                    reply->writeInt32(HI_FAILURE);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return HI_FAILURE;
            }

            s32Size *= 1024;
            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_MAX_SIZE, (HI_VOID *)&s32Size);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_GET_BUFFER_MAX_SIZE:
        {
            /* request:Type, reply: ret(int) | size(int) Kbytes */
            HI_S32 s32Size = 0;
            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_BUFFER_MAX_SIZE, (HI_VOID *)&s32Size);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
                reply->writeInt32(s32Size/1024);
            }
        }
        break;
        case CMD_SET_3D_SUBTITLE_CUT_METHOD:
        {
            arg = request->readInt32();
            int SubFramePackType = SUB_DEFAULT_FRAME_PACK;
            LOGV("set sub cut out method %d", arg);

            switch (arg)
            {
                case 0:
                    // when current mode is sbs/tab,we will cut out the subtitle in the middle
                    SubFramePackType = SUB_DEFAULT_FRAME_PACK;
                    break;
                case 1:
                    // will not cut out the subtitle in any mode
                    SubFramePackType = HI_UNF_FRAME_PACKING_TYPE_NONE;
                    break;
                default:
                    SubFramePackType = SUB_DEFAULT_FRAME_PACK;
                    break;
            }

            if (HI_SUCCESS == mPlayer->setSubFramePack(SubFramePackType))
            {
                reply->writeInt32(NO_ERROR);
                LOGV("set sub cut out method success");
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return NO_ERROR;
            }
            else
            {
                LOGE("set sub cut out method fail");
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }
        }
        break;
        case CMD_SET_BUFFER_UNDERRUN:
        {
            /* request:Type| size(int), reply: ret(int)  */
            HI_S32 s32Arg = request->readInt32();

            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_BUFFER_UNDERRUN, (HI_VOID *)&s32Arg);

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }
        }
        break;
        case CMD_SET_DOLBY_RANGEINFO:
        {
            int DolbyRangeInfo = request->readInt32();
            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_DOLBYRANGEINFO, (HI_VOID *)DolbyRangeInfo);

            if (HI_SUCCESS == s32Ret)
            {
                LOGV("DolbyRangeInfo set success %d", DolbyRangeInfo);
                if (NULL != reply)
                    reply->writeInt32(NO_ERROR);
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return NO_ERROR;
            }
            else
            {
                LOGE("DolbyRangeInfo set fail %d", DolbyRangeInfo);
                if (NULL != reply)
                    reply->writeInt32(UNKNOWN_ERROR);
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return UNKNOWN_ERROR;
            }

            LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
            return NO_ERROR;
        }
        break;
        case CMD_SET_DOLBY_DRCMODE:
        {
            int DolbyDrcMode = request->readInt32();
            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_SET_DOLBYDRCMODE, (HI_VOID *)DolbyDrcMode);

            if (HI_SUCCESS == s32Ret)
            {
                LOGV("DolbyDrcMode set success %d", DolbyDrcMode);
                if (NULL != reply)
                    reply->writeInt32(NO_ERROR);
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return NO_ERROR;
            }
            else
            {
                LOGE("DolbyDrcMode set fail %d", DolbyDrcMode);
                if (NULL != reply)
                    reply->writeInt32(UNKNOWN_ERROR);
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return UNKNOWN_ERROR;
            }

            LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
            return NO_ERROR;
        }
        break;
        case CMD_GET_DOLBYINFO:
        {
            HI_FORMAT_AUD_DOLBY_INFO_S DolbyInfo;
            s32Ret = HI_SVR_PLAYER_Invoke(mHandle, HI_FORMAT_INVOKE_GET_DOLBYINFO, (HI_VOID *)(&DolbyInfo));

            if (HI_SUCCESS == s32Ret)
            {
                LOGV("DolbyRangeInfo get success");
                if (NULL != reply)
                {
                    reply->writeInt32(NO_ERROR);
                    reply->writeInt32(DolbyInfo.s32ACMode);
                    reply->writeInt32(DolbyInfo.s32StreamType);
                    LOGE("DolbyInfo.u32DecoderType %u", DolbyInfo.u32DecoderType);
                    reply->writeInt64(DolbyInfo.u32DecoderType);
                }

                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                return NO_ERROR;
            }
            else
            {
                LOGE("DolbyRangeInfo set fail");
                LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
                if (NULL != reply)
                    reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }

            LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
            return NO_ERROR;
        }
        case CMD_SET_AVSYNC_START_REGION:
        {
            // get current setting
            HI_SVR_PLAYER_SYNC_ATTR_S stSyncAttr;
            if (HI_SUCCESS != HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_SYNC, (HI_VOID*)&stSyncAttr))
            {
                LOGE("set avsync start region fail,get current avsync info fail");
                if (NULL != reply)
                    reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }

            stSyncAttr.s32SyncVidPlusTime = request->readInt32();
            stSyncAttr.s32SyncVidNegativeTime = request->readInt32();
            LOGE("set avsync start region PlusTime %d NegativeTime %d",
                stSyncAttr.s32SyncVidPlusTime,stSyncAttr.s32SyncVidNegativeTime);

            if (HI_SUCCESS != HI_SVR_PLAYER_SetParam(mHandle, HI_SVR_PLAYER_ATTR_SYNC, (HI_VOID*)&stSyncAttr))
            {
                LOGE("set avsync start region fail,set avsync info fail");
                if (NULL != reply)
                    reply->writeInt32(UNKNOWN_ERROR);
                return UNKNOWN_ERROR;
            }

            if (NULL != reply)
                reply->writeInt32(NO_ERROR);

            LOGV("set avsync start region success");
            return NO_ERROR;
        }
        // End Http Live Streaming
        case CMD_SET_DAC_DECT_ENABLE:
        {
            int DolbyEnable = 1;
            DolbyEnable = request->readInt32();

            HI_MPI_DISP_Init();
            if(DolbyEnable == 0)
            {
                HI_MPI_DISP_SetDacOutputEnable(HI_FALSE);
                LOGV("Enable Dac force Output");
            }
            else
            {
                HI_MPI_DISP_SetDacOutputEnable(HI_TRUE);
                LOGV("Disable Dac force Output");
            }
            HI_MPI_DISP_DeInit();

            if (NULL != reply)
                reply->writeInt32(NO_ERROR);
            return NO_ERROR;
        }
        break;
        case CMD_SET_WIN_FREEZE_MODE:
        {
            arg = request->readInt32();
            CHECK_FUNC_RET(mPlayer->setWindowFreezeStatus(arg));
            if (NULL != reply)
            {
                reply->writeInt32(NO_ERROR);
            }
        }
        break;
        case CMD_SET_AUDIO_CHANNEL:
        {
            HI_UNF_TRACK_MODE_E eMode = HI_UNF_TRACK_MODE_BUTT;
            HI_S32 s32Ret = 0;
            HI_HANDLE hdl = HI_INVALID_HANDLE;
            HI_S32 s32Fixed = 0;
            arg = request->readInt32();
            LOGV("set audio channel arg:%d", arg);
            if (0 == arg)
            {
                eMode = HI_UNF_TRACK_MODE_DOUBLE_LEFT;
            }
            else if (1 == arg)
            {
                eMode = HI_UNF_TRACK_MODE_DOUBLE_RIGHT;
            }
            else if (2 == arg)
            {
                eMode = HI_UNF_TRACK_MODE_STEREO;
            }
            else
            {
                LOGE("unsupport channel:%d", arg);
                break;
            }
            s32Ret = HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hdl);
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("GET HI_SVR_PLAYER_ATTR_AUDTRACK_HDL failed.");
                break;
            }
            s32Ret = HI_UNF_SND_SetTrackChannelMode(hdl, eMode);
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("HI_UNF_SND_SetTrackChannelMode failed %x", s32Ret);
                break;
            }
            s32Ret = HI_UNF_SND_GetTrackChannelMode(hdl, &eMode);
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("HI_UNF_SND_GetTrackChannelMode failed %x", s32Ret);
                break;
            }
            if (HI_UNF_TRACK_MODE_DOUBLE_LEFT == eMode)
            {
                s32Fixed = 0;
            }
            else if (HI_UNF_TRACK_MODE_DOUBLE_RIGHT == eMode)
            {
                s32Fixed = 1;
            }
            else if (HI_UNF_TRACK_MODE_STEREO == eMode)
            {
                s32Fixed = 2;
            }
            else
            {
                LOGE("unknow mode:%d", eMode);
                break;
            }
            if (NULL != reply)
            {
                LOGV("Fixed audio channel :%d", s32Fixed);
                reply->writeInt32(s32Fixed);
            }
        }
        break;
        case CMD_SET_TRACK_VOLUME:
        {
            HI_UNF_SND_ABSGAIN_ATTR_S stAbsWeightGain;
            HI_S32 s32Ret = 0;
            HI_HANDLE hTrack = HI_INVALID_HANDLE;

            HI_S32 lVolume = request->readInt32();
            HI_S32 rVolume = request->readInt32();
            LOGV("set track volume:%d %d", lVolume, rVolume);

            s32Ret = HI_SVR_PLAYER_GetParam(mHandle, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hTrack);
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("GET HI_SVR_PLAYER_ATTR_AUDTRACK_HDL failed.");
                break;
            }

            memset(&stAbsWeightGain, 0, sizeof(stAbsWeightGain));
            stAbsWeightGain.bLinearMode = HI_TRUE;
            stAbsWeightGain.s32GainL = lVolume;
            stAbsWeightGain.s32GainR = rVolume;
            s32Ret = HI_UNF_SND_SetTrackAbsWeight(hTrack, &stAbsWeightGain);

            if (HI_SUCCESS != s32Ret)
            {
                LOGE("GET HI_SVR_PLAYER_ATTR_AUDTRACK_HDL failed.");
                break;
            }

            if (NULL != reply)
            {
                LOGV("fixed track Volume :%d", s32Ret);
                reply->writeInt32(s32Ret);
            }
        }
        break;
        default:
            LOGE("HiMediaPlayer::invoke fail: unkonw cmd type %d", (int)cmd);
            //if cmd is unknown, write HI_FAILURE to reply
            s32Ret = HI_FAILURE;

            if (NULL != reply)
            {
                reply->writeInt32(s32Ret);
            }

            LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);
            return BAD_TYPE;
    }

    LOGV("HiMediaPlayer::invoke leave, cmd [%d]", cmd_type);

    return ret;
}

/* the following 2 function used for sync with the HiMediaPlayer callback */
inline int HiMediaPlayer::CommandQueue::wait()
{
    Mutex::Autolock l(mCallbackLock);
    HI_S32 ret = 0;//set the init value.

    ret = mCallbackCond.waitRelative(mCallbackLock, 2000 * 1000 * 1000);

    if (ret != 0)
    {
        LOGW("WARN: HiMediaPlayer::CommandQueue::wait() out time for out ");
        return ERROR_TIMEOUT;
    }

    return NO_ERROR;
}

int HiMediaPlayer::CommandQueue::AllocCopyFileInfo(HI_FORMAT_FILE_INFO_S *pDstFileInfo, HI_FORMAT_FILE_INFO_S * pSrcFileInfo)
{
    HI_U32 i = 0;
    HI_S32 s32AllocSize = 0;

    if (pSrcFileInfo == NULL || pDstFileInfo == NULL || pDstFileInfo->pastProgramInfo != NULL)
    {
        return HI_FAILURE;
    }

    HIMEDIA_MEMCPY(pDstFileInfo, pSrcFileInfo, sizeof(HI_FORMAT_FILE_INFO_S));

    if (pSrcFileInfo->pastProgramInfo == NULL || pDstFileInfo->u32ProgramNum <= 0)
    {
        pDstFileInfo->u32ProgramNum = 0;
        return HI_SUCCESS;
    }

    s32AllocSize = pDstFileInfo->u32ProgramNum * sizeof(HI_FORMAT_PROGRAM_INFO_S);
    pDstFileInfo->pastProgramInfo = (HI_FORMAT_PROGRAM_INFO_S *)HIMEDIA_MALLOCZ(s32AllocSize);

    if (pDstFileInfo->pastProgramInfo == NULL)
    {
        pDstFileInfo->u32ProgramNum = 0;
        return HI_FAILURE;
    }

    for (i = 0; i< pSrcFileInfo->u32ProgramNum; i++)
    {
        if (pSrcFileInfo->pastProgramInfo[i].u32VidStreamNum > 0 &&
            pSrcFileInfo->pastProgramInfo[i].pastVidStream != NULL)
        {
            s32AllocSize = pSrcFileInfo->pastProgramInfo[i].u32VidStreamNum * sizeof(HI_FORMAT_VID_INFO_S);
            pDstFileInfo->pastProgramInfo[i].pastVidStream = (HI_FORMAT_VID_INFO_S *)HIMEDIA_MALLOCZ(s32AllocSize);
            if (pDstFileInfo->pastProgramInfo[i].pastVidStream == NULL)
            {
                goto errret;
            }

            HIMEDIA_MEMCPY(pDstFileInfo->pastProgramInfo[i].pastVidStream,
                pSrcFileInfo->pastProgramInfo[i].pastVidStream, s32AllocSize);
            pDstFileInfo->pastProgramInfo[i].u32VidStreamNum = pSrcFileInfo->pastProgramInfo[i].u32VidStreamNum;
        }

        if (pSrcFileInfo->pastProgramInfo[i].u32AudStreamNum > 0 &&
            pSrcFileInfo->pastProgramInfo[i].pastAudStream != NULL)
        {
            s32AllocSize = pSrcFileInfo->pastProgramInfo[i].u32AudStreamNum * sizeof(HI_FORMAT_AUD_INFO_S);
            pDstFileInfo->pastProgramInfo[i].pastAudStream = (HI_FORMAT_AUD_INFO_S *)HIMEDIA_MALLOCZ(s32AllocSize);
            if (pDstFileInfo->pastProgramInfo[i].pastAudStream == NULL)
            {
                goto errret;
            }

            HIMEDIA_MEMCPY(pDstFileInfo->pastProgramInfo[i].pastAudStream,
                pSrcFileInfo->pastProgramInfo[i].pastAudStream, s32AllocSize);
            pDstFileInfo->pastProgramInfo[i].u32AudStreamNum = pSrcFileInfo->pastProgramInfo[i].u32AudStreamNum;
        }

        if (pSrcFileInfo->pastProgramInfo[i].u32SubStreamNum > 0 &&
            pSrcFileInfo->pastProgramInfo[i].pastSubStream != NULL)
        {
            s32AllocSize = pSrcFileInfo->pastProgramInfo[i].u32SubStreamNum * sizeof(HI_FORMAT_SUB_INFO_S);
            pDstFileInfo->pastProgramInfo[i].pastSubStream = (HI_FORMAT_SUB_INFO_S *)HIMEDIA_MALLOCZ(s32AllocSize);
            if (pDstFileInfo->pastProgramInfo[i].pastSubStream == NULL)
            {
                goto errret;
            }

            HIMEDIA_MEMCPY(pDstFileInfo->pastProgramInfo[i].pastSubStream,
                pSrcFileInfo->pastProgramInfo[i].pastSubStream, s32AllocSize);
            pDstFileInfo->pastProgramInfo[i].u32SubStreamNum = pSrcFileInfo->pastProgramInfo[i].u32SubStreamNum;
        }
    }

    return HI_SUCCESS;
errret:
    HIMEDIA_FREE_ALL_PROGRAMS(pDstFileInfo);

    return HI_FAILURE;
}
inline int HiMediaPlayer::CommandQueue::signal()
{
    Mutex::Autolock l(mCallbackLock);
    mCallbackCond.signal();
    return NO_ERROR;
}
} // end namespace android
