#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/times.h>

#include "hi_audio_codec.h"
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_demux.h"
#include "hi_unf_so.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_go.h"
#include "hi_adp_audio.h"
#include "hi_adp_mpi.h"
#include "hi_adp_hdmi.h"
#include "hi_svr_player.h"
#include "hi_svr_format.h"
#include "hi_svr_metadata.h"
#include "hi_svr_assa.h"
#include "hi_unf_subt.h"
#include "hi_unf_edid.h"
#if defined (DRM_SUPPORT)
#include "localplay_drm.h"
#endif

#if defined (CHARSET_SUPPORT)
#include "hi_svr_charset.h"
#include "hi_svr_charset_norm.h"
#endif

#include "test_protocol_args.h"
//Gaplessplay include
#include "play_m3u9.h"

#define SLEEP_TIME         (10 * 1000)
#define CMD_LEN            (1024)
#define PRINTF printf

//#define sscanf(cmd, fmt, ...)  -1
#define USE_EXTERNAL_AVPLAY   1

#define HELP_INFO  \
" ------------- help info ----------------------------------  \n\n " \
"    h     : help info                                          \n " \
"    play  : play                                               \n " \
"    pause : pause                                              \n " \
"    seek  : seek ms, example: seek 90000                       \n " \
"    metadata : print metadata, example: metadata               \n " \
"    posseek  : seek bytes, example: posseek 90000              \n " \
"    stop  : stop                                               \n " \
"    resume: resume                                             \n " \
"    bw    : backward 2/4/8/16/32/64, example: bw 2             \n " \
"    ff    : forward 2/4/8/16/32/64, example: ff 4              \n " \
"    info  : info of player                                     \n " \
"    set   : example:                                           \n " \
"            set mute 1/0                                       \n " \
"            set vmode 0/1/2/3...                               \n " \
"            set sync v_pts_offset a_pts_offset s_pts_offset    \n " \
"            set vol 50                                         \n " \
"            set track 0/1/2/...                                \n " \
"            set pos 20 20 300 300                              \n " \
"            set id prgid vid aid sid, example set id 0 0 1 0   \n " \
"            set hdmi                                           \n " \
"            set spdif                                          \n " \
"    get   : get bandwidth                                      \n " \
"            get bufferconfig size/time                         \n " \
"            get bufferstatus                                   \n " \
"            ......                                             \n " \
"    open  : open new file, example: open /mnt/1.avi            \n " \
"    dbg   : enable dgb, example: dgb 1/0                       \n " \
"    q     : quite                                              \n " \
"    sethls: sethls track 0/1/2...                              \n " \
" ----------------------------------------------------------- \n\n " \

static HI_HANDLE s_hLayer = HIGO_INVALID_HANDLE;
static HI_HANDLE s_hLayerSurface = HIGO_INVALID_HANDLE;
static HI_HANDLE s_hFont  = HIGO_INVALID_HANDLE;
static HI_SO_SUBTITLE_ASS_PARSE_S *s_pstParseHand = NULL;

static HI_S32 s_s32ThreadExit = HI_FAILURE;
static HI_S32 s_s32ThreadEnd = HI_SUCCESS;
static HI_CHAR  s_aszUrl[HI_FORMAT_MAX_URL_LEN];
static pthread_t s_hThread = {0};
static HI_S64 s_s64CurPgsClearTime = -1;
static HI_BOOL s_bPgs = HI_FALSE;
static HI_SVR_PLAYER_STREAMID_S s_stStreamID = {
    0,
    0,
    0,
    0
};

static HI_SVR_PLAYER_PARAM_S s_stParam = {
        0,
        3,
        0,
        0,
        0,
        0,
        100,
        0,
        0,
        HI_UNF_DISPLAY1,
        100,
        0
};

static HI_BOOL s_noPrintInHdmiATC = HI_FALSE;

#if (USE_EXTERNAL_AVPLAY == 1)
#define INVALID_TRACK_HDL     (0xffffffff)

static HI_HANDLE s_hAudioTrack = (HI_HANDLE)INVALID_TRACK_HDL;
static HI_HANDLE s_hWindow     = (HI_HANDLE)HI_SVR_PLAYER_INVALID_HDL;
#endif

static HI_S32 clearSubtitle();
static HI_S32 subOndraw(HI_U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, HI_VOID *pArg);
static HI_S32 subOnclear(HI_U32 u32UserData, HI_VOID *pArg);
static HI_S32 outFileInfo(HI_FORMAT_FILE_INFO_S *pstFileInfo);
static HI_S32 CheckPlayerStatus(HI_HANDLE hPlayer, HI_U32 u32Status, HI_U32 u32TimeOutMs);

static HI_CHAR *getVidFormatStr(HI_U32 u32Format)
{
    switch (u32Format)
    {
    case HI_FORMAT_VIDEO_MPEG2:
        return "MPEG2";

    case HI_FORMAT_VIDEO_MPEG4:
        return "MPEG4";

    case HI_FORMAT_VIDEO_AVS:
        return "AVS";

    case HI_FORMAT_VIDEO_H263:
        return "H263";

    case HI_FORMAT_VIDEO_H264:
        return "H264";

    case HI_FORMAT_VIDEO_REAL8:
        return "REAL8";

    case HI_FORMAT_VIDEO_REAL9:
        return "REAL9";

    case HI_FORMAT_VIDEO_VC1:
        return "VC1";

    case HI_FORMAT_VIDEO_VP6:
        return "VP6";

    case HI_FORMAT_VIDEO_DIVX3:
        return "DIVX3";

    case HI_FORMAT_VIDEO_RAW:
        return "RAW";

    case HI_FORMAT_VIDEO_JPEG:
        return "JPEG";

    case HI_FORMAT_VIDEO_MJPEG:
        return "MJPEG";

    case HI_FORMAT_VIDEO_MJPEGB:
        return "MJPEGB";

    case HI_FORMAT_VIDEO_SORENSON:
        return "SORENSON";

    case HI_FORMAT_VIDEO_VP6F:
        return "VP6F";

    case HI_FORMAT_VIDEO_VP6A:
        return "VP6A";

    case HI_FORMAT_VIDEO_VP8:
        return "VP8";

    case HI_FORMAT_VIDEO_MVC:
        return "MVC";

    case HI_FORMAT_VIDEO_SVQ1:
        return "SORENSON1";

    case HI_FORMAT_VIDEO_SVQ3:
        return "SORENSON3";

    case HI_FORMAT_VIDEO_DV:
        return "DV";

    case HI_FORMAT_VIDEO_WMV1:
        return "WMV1";

    case HI_FORMAT_VIDEO_WMV2:
        return "WMV2";

    case HI_FORMAT_VIDEO_MSMPEG4V1:
        return "MICROSOFT MPEG4V1";

    case HI_FORMAT_VIDEO_MSMPEG4V2:
        return "MICROSOFT MPEG4V2";

    case HI_FORMAT_VIDEO_CINEPAK:
        return "CINEPACK";

    case HI_FORMAT_VIDEO_RV10:
        return "RV10";

    case HI_FORMAT_VIDEO_RV20:
        return "RV20";

    case HI_FORMAT_VIDEO_INDEO4:
        return "INDEO4";

    case HI_FORMAT_VIDEO_INDEO5:
        return "INDEO5";

    default:
        return "UN-KNOWN";

    }
}

static HI_CHAR *getAudFormatStr(HI_U32 u32Format)
{
    switch (u32Format)
    {
    case HI_FORMAT_AUDIO_MP2:
        return "MPEG2";

    case HI_FORMAT_AUDIO_MP3:
        return "MPEG3";

    case HI_FORMAT_AUDIO_AAC:
        return "AAC";

    case HI_FORMAT_AUDIO_AC3:
        return "AC3";

    case HI_FORMAT_AUDIO_DTS:
        return "DTS";

    case HI_FORMAT_AUDIO_VORBIS:
        return "VORBIS";

    case HI_FORMAT_AUDIO_DVAUDIO:
        return "DVAUDIO";

    case HI_FORMAT_AUDIO_WMAV1:
        return "WMAV1";

    case HI_FORMAT_AUDIO_WMAV2:
        return "WMAV2";

    case HI_FORMAT_AUDIO_MACE3:
        return "MACE3";

    case HI_FORMAT_AUDIO_MACE6:
        return "MACE6";

    case HI_FORMAT_AUDIO_VMDAUDIO:
        return "VMDAUDIO";

    case HI_FORMAT_AUDIO_SONIC:
        return "SONIC";

    case HI_FORMAT_AUDIO_SONIC_LS:
        return "SONIC_LS";

    case HI_FORMAT_AUDIO_FLAC:
        return "FLAC";

    case HI_FORMAT_AUDIO_MP3ADU:
        return "MP3ADU";

    case HI_FORMAT_AUDIO_MP3ON4:
        return "MP3ON4";

    case HI_FORMAT_AUDIO_SHORTEN:
        return "SHORTEN";

    case HI_FORMAT_AUDIO_ALAC:
        return "ALAC";

    case HI_FORMAT_AUDIO_WESTWOOD_SND1:
        return "WESTWOOD_SND1";

    case HI_FORMAT_AUDIO_GSM:
        return "GSM";

    case HI_FORMAT_AUDIO_QDM2:
        return "QDM2";

    case HI_FORMAT_AUDIO_COOK:
        return "COOK";

    case HI_FORMAT_AUDIO_TRUESPEECH:
        return "TRUESPEECH";

    case HI_FORMAT_AUDIO_TTA:
        return "TTA";

    case HI_FORMAT_AUDIO_SMACKAUDIO:
        return "SMACKAUDIO";

    case HI_FORMAT_AUDIO_QCELP:
        return "QCELP";

    case HI_FORMAT_AUDIO_WAVPACK:
        return "WAVPACK";

    case HI_FORMAT_AUDIO_DSICINAUDIO:
        return "DSICINAUDIO";

    case HI_FORMAT_AUDIO_IMC:
        return "IMC";

    case HI_FORMAT_AUDIO_MUSEPACK7:
        return "MUSEPACK7";

    case HI_FORMAT_AUDIO_MLP:
        return "MLP";

    case HI_FORMAT_AUDIO_GSM_MS:
        return "GSM_MS";

    case HI_FORMAT_AUDIO_ATRAC3:
        return "ATRAC3";

    case HI_FORMAT_AUDIO_VOXWARE:
        return "VOXWARE";

    case HI_FORMAT_AUDIO_APE:
        return "APE";

    case HI_FORMAT_AUDIO_NELLYMOSER:
        return "NELLYMOSER";

    case HI_FORMAT_AUDIO_MUSEPACK8:
        return "MUSEPACK8";

    case HI_FORMAT_AUDIO_SPEEX:
        return "SPEEX";

    case HI_FORMAT_AUDIO_WMAVOICE:
        return "WMAVOICE";

    case HI_FORMAT_AUDIO_WMAPRO:
        return "WMAPRO";

    case HI_FORMAT_AUDIO_WMALOSSLESS:
        return "WMALOSSLESS";

    case HI_FORMAT_AUDIO_ATRAC3P:
        return "ATRAC3P";

    case HI_FORMAT_AUDIO_EAC3:
        return "EAC3";

    case HI_FORMAT_AUDIO_SIPR:
        return "SIPR";

    case HI_FORMAT_AUDIO_MP1:
        return "MP1";

    case HI_FORMAT_AUDIO_TWINVQ:
        return "TWINVQ";

    case HI_FORMAT_AUDIO_TRUEHD:
        return "TRUEHD";

    case HI_FORMAT_AUDIO_MP4ALS:
        return "MP4ALS";

    case HI_FORMAT_AUDIO_ATRAC1:
        return "ATRAC1";

    case HI_FORMAT_AUDIO_BINKAUDIO_RDFT:
        return "BINKAUDIO_RDFT";

    case HI_FORMAT_AUDIO_BINKAUDIO_DCT:
        return "BINKAUDIO_DCT";

    case HI_FORMAT_AUDIO_DRA:
        return "DRA";

    case HI_FORMAT_AUDIO_PCM: /* various PCM "codecs" */
        return "PCM";

    case HI_FORMAT_AUDIO_ADPCM: /* various ADPCM codecs */
        return "ADPCM";

    case HI_FORMAT_AUDIO_AMR_NB: /* AMR */
        return "AMR_NB";

    case HI_FORMAT_AUDIO_AMR_WB:
        return "AMR_WB";

    case HI_FORMAT_AUDIO_AMR_AWB:
        return "AMR_AWB";

    case HI_FORMAT_AUDIO_RA_144: /* RealAudio codecs*/
        return "RA_144";

    case HI_FORMAT_AUDIO_RA_288:
        return "RA_288";

    case HI_FORMAT_AUDIO_DPCM: /* various DPCM codecs */
        return "DPCM";

    case HI_FORMAT_AUDIO_G711:  /* various G.7xx codecs */
        return "G711";

    case HI_FORMAT_AUDIO_G722:
        return "G722";

    case HI_FORMAT_AUDIO_G7231:
        return "G7231";

    case HI_FORMAT_AUDIO_G726:
        return "G726";

    case HI_FORMAT_AUDIO_G728:
        return "G728";

    case HI_FORMAT_AUDIO_G729AB:
        return "G729AB";

    case HI_FORMAT_AUDIO_PCM_BLURAY:
        return "PCM_BLURAY";

    default:
        break;
    }

    return "UN-KNOWN";
}

static HI_CHAR *getSubFormatStr(HI_U32 u32Format)
{
    switch (u32Format)
    {
    case HI_FORMAT_SUBTITLE_ASS:
        return "ASS";

    case HI_FORMAT_SUBTITLE_LRC:
        return "LRC";

    case HI_FORMAT_SUBTITLE_SRT:
        return "SRT";

    case HI_FORMAT_SUBTITLE_SMI:
        return "SMI";

     case HI_FORMAT_SUBTITLE_SUB:
        return "SUB";

    case HI_FORMAT_SUBTITLE_TXT:
        return "TEXT";

    case HI_FORMAT_SUBTITLE_HDMV_PGS:
        return "HDMV_PGS";

    case HI_FORMAT_SUBTITLE_DVB_SUB:
        return "DVB_SUB_BMP";

    case HI_FORMAT_SUBTITLE_DVD_SUB:
        return "DVD_SUB_BMP";

    default:
        return "UN-KNOWN";

    }
}


static HI_S32 deviceInit(HI_UNF_ENC_FMT_E fmt)
{
    HI_S32 s32Ret = 0;

    HI_SYS_Init();

    HIADP_MCE_Exit();

    s32Ret = HIADP_Disp_Init(fmt);

    if (s32Ret != HI_SUCCESS)
    {
        PRINTF("call DispInit failed.\n");
        return HI_FAILURE;
    }

    s32Ret = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);

    if (s32Ret != HI_SUCCESS)
    {
        PRINTF("call VoInit failed.\n");
        return HI_FAILURE;
    }

    s32Ret = HIADP_Snd_Init();

    if (s32Ret != HI_SUCCESS)
    {
        PRINTF("call SndInit failed.\n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.BLURAYLPCM.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.FFMPEG_ADEC.decode.so");
    s32Ret |= HIADP_AVPlay_RegADecLib();

    if (s32Ret != HI_SUCCESS)
    {
        PRINTF("call HI_UNF_AVPLAY_RegisterAcodecLib failed.\n");
    }

    s32Ret = HI_UNF_AVPLAY_RegisterVcodecLib("libHV.VIDEO.FFMPEG_VDEC.decode.so");
    if (s32Ret != HI_SUCCESS)
    {
        PRINTF("call HI_UNF_AVPLAY_RegisterVcodecLib return 0x%x.\n", s32Ret);
    }

    s32Ret = HI_UNF_DMX_Init();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("### HI_UNF_DMX_Init init fail.\n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_AVPLAY_Init();

    if (s32Ret != HI_SUCCESS)
    {
        PRINTF("call HI_UNF_AVPLAY_Init failed.\n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_SO_Init();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("### HI_UNF_SO_Init init fail.\n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_SUBT_Init();
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("### HI_UNF_SUBT_Init init fail.\n");
        return HI_FAILURE;
    }

    usleep(3000 * 1000);

    return HI_SUCCESS;
}

static HI_VOID deviceDeinit(HI_VOID)
{
    (HI_VOID)HI_UNF_AVPLAY_DeInit();
    (HI_VOID)HI_UNF_DMX_DeInit();
    (HI_VOID)HI_UNF_SO_DeInit();

    (HI_VOID)HIADP_Snd_DeInit();
    (HI_VOID)HIADP_VO_DeInit();
    (HI_VOID)HIADP_Disp_DeInit();
    (HI_VOID)HI_SYS_DeInit();
    (HI_VOID)HI_UNF_SUBT_DeInit();
    return;
}

static HI_S32 TestCallBack(TEST_EVENT_S *pstEvent)
{
    if (NULL == pstEvent)
    {
        PRINTF("TestCallBack args is null\n");
        return HI_FAILURE;
    }
    switch (pstEvent->type)
    {
    case 1:
        PRINTF("TestCallBack read bytes is: %d\n", *((HI_S32*)pstEvent->Args));
        break;
    default:
        PRINTF("unknow event TestCallBack \n");
        break;
    }
    return HI_SUCCESS;
}

static HI_S32 setMedia(HI_HANDLE hPlayer, const HI_CHAR * pszUrl)
{
    HI_S32 s32Ret;
    HI_SVR_PLAYER_MEDIA_S stMedia;
    HI_HANDLE hSo = (HI_HANDLE)NULL;
    HI_HANDLE hAVPlay = HI_SVR_PLAYER_INVALID_HDL;

    memset(&stMedia, 0, sizeof(HI_SVR_PLAYER_MEDIA_S));
    sprintf(stMedia.aszUrl, "%s", pszUrl);
    stMedia.u32ExtSubNum = 0;

    PRINTF("### open media file is %s \n", stMedia.aszUrl);
    s32Ret = HI_SVR_PLAYER_SetMedia(hPlayer, HI_SVR_PLAYER_MEDIA_STREAMFILE, &stMedia);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: HI_SVR_PLAYER_SetMedia err, ret = 0x%x!\n", s32Ret);
        return s32Ret;
    }
    else
    {
        PRINTF("ERR: HI_SVR_PLAYER_SetMedia su, ret = 0x%x!\n", s32Ret);
    }

    s32Ret |= HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_SO_HDL, &hSo);
    s32Ret |= HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAVPlay);
    s32Ret |= HI_UNF_SO_RegOnDrawCb(hSo, subOndraw, subOnclear, hAVPlay);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: set subtitle draw function fail!\n");
    }

    return s32Ret;
}

static HI_VOID* reconnect(HI_VOID *pArg)
{
    HI_S32  s32Ret = HI_FAILURE;
    HI_S64 s64LastPts = HI_FORMAT_NO_PTS;
    HI_HANDLE hPlayer = (HI_HANDLE)pArg;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_SVR_PLAYER_MEDIA_S stMedia;
    HI_SVR_PLAYER_INFO_S stPlayerInfo;

    memset(&stMedia, 0, sizeof(HI_SVR_PLAYER_MEDIA_S));
    memset(&stPlayerInfo, 0, sizeof(HI_SVR_PLAYER_INFO_S));

    s_s32ThreadEnd = HI_FAILURE;
    sprintf(stMedia.aszUrl, "%s", s_aszUrl);
    stMedia.u32ExtSubNum = 0;
    PRINTF("### open media file is %s \n", stMedia.aszUrl);

    (HI_VOID)HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);
    (HI_VOID)HI_GO_RefreshLayer(s_hLayer, NULL);

    clearSubtitle();
    s32Ret = HI_SVR_PLAYER_GetPlayerInfo(hPlayer, &stPlayerInfo);
    if (HI_SUCCESS == s32Ret)
    {
        s64LastPts = stPlayerInfo.u64TimePlayed;
        s32Ret = HI_FAILURE;
    }

    (HI_VOID)HI_SVR_PLAYER_Stop(hPlayer);
    CheckPlayerStatus(hPlayer, HI_SVR_PLAYER_STATE_STOP, 100);

    while (s32Ret == HI_FAILURE && (s_s32ThreadExit == HI_FAILURE))
    {
        s32Ret = setMedia(hPlayer, s_aszUrl);
        if (HI_SUCCESS != s32Ret)
        {
            continue;
        }
    }

    s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

    if (HI_SUCCESS == s32Ret && NULL != pstFileInfo)
    {
        outFileInfo(pstFileInfo);
    }
    else
    {
        PRINTF("ERR: get file info fail!\n");
    }

    (HI_VOID)HI_SVR_PLAYER_Seek(hPlayer, s64LastPts);
    (HI_VOID)HI_SVR_PLAYER_Play(hPlayer);

    s_s32ThreadEnd = HI_SUCCESS;
    return NULL;
}

static HI_S32 eventCallBack(HI_HANDLE hPlayer, HI_SVR_PLAYER_EVENT_S *pstruEvent)
{
    HI_SVR_PLAYER_STATE_E eEventBk = HI_SVR_PLAYER_STATE_BUTT;
    HI_SVR_PLAYER_STREAMID_S *pstSreamId = NULL;
    HI_HANDLE hWindow = (HI_HANDLE)NULL;
    HI_FORMAT_FILE_INFO_S *pstFileInfo;
    HI_S32 s32Ret = HI_FAILURE;
    static HI_SVR_PLAYER_STATE_E ePlayerState = HI_SVR_PLAYER_STATE_BUTT;
    static HI_S32 s32PausedCtrl = 0;

    if (0 == hPlayer || NULL == pstruEvent)
    {
        return HI_SUCCESS;
    }

    if (HI_SVR_PLAYER_EVENT_STATE_CHANGED == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        eEventBk = (HI_SVR_PLAYER_STATE_E)*pstruEvent->pu8Data;
        PRINTF("Status change to %d \n", eEventBk);
        ePlayerState = eEventBk;

        if (eEventBk == HI_SVR_PLAYER_STATE_STOP)
        {
            HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hWindow);
            HI_UNF_VO_ResetWindow(hWindow, HI_UNF_WINDOW_FREEZE_MODE_BLACK);
        }

        if (eEventBk == HI_SVR_PLAYER_STATE_PAUSE && s32PausedCtrl == 1)
        {
            s32PausedCtrl = 2;
        }
        else
        {
            s32PausedCtrl = 0;
        }
    }
    else if (HI_SVR_PLAYER_EVENT_SOF == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        PRINTF("File position is start of file! \n");
        /* ���˵�ͷ������������ */
        eEventBk = (HI_SVR_PLAYER_STATE_E)*pstruEvent->pu8Data;

        if (HI_SVR_PLAYER_STATE_BACKWARD == eEventBk)
        {
            PRINTF("backward to start of file, start play! \n");
            HI_SVR_PLAYER_Play(hPlayer);
        }
    }
    else if (HI_SVR_PLAYER_EVENT_EOF == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        PRINTF("File postion is end of file, clear last frame and replay! \n");
        HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hWindow);
        HI_UNF_VO_ResetWindow(hWindow, HI_UNF_WINDOW_FREEZE_MODE_BLACK);
        clearSubtitle();
        /*rtsp/mms/rtmp need to redo setting media when stop->play/replay*/
        if (strstr(s_aszUrl, "rtsp") ||
            strstr(s_aszUrl, "mms")  ||
            strstr(s_aszUrl, "rtmp"))
        {
            s32Ret = setMedia(hPlayer, s_aszUrl);
            if (HI_SUCCESS != s32Ret)
            {
                return HI_FAILURE;
            }
        }

        HI_SVR_PLAYER_Play(hPlayer);
    }
    else if (HI_SVR_PLAYER_EVENT_STREAMID_CHANGED == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        pstSreamId = (HI_SVR_PLAYER_STREAMID_S*)pstruEvent->pu8Data;

        if (NULL != pstSreamId)
        {
            if (s_stStreamID.u16SubStreamId != pstSreamId->u16SubStreamId ||
                s_stStreamID.u16ProgramId != pstSreamId->u16ProgramId)
            {
                clearSubtitle();
                s_stStreamID = *pstSreamId;
            }

            PRINTF("Stream id change to: ProgramId %d, vid %d, aid %d, sid %d \n",
                pstSreamId->u16ProgramId,
                pstSreamId->u16VidStreamId,
                pstSreamId->u16AudStreamId,
                pstSreamId->u16SubStreamId);
        }
    }
    else if (HI_SVR_PLAYER_EVENT_PROGRESS == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        HI_SVR_PLAYER_PROGRESS_S stProgress;
        memcpy(&stProgress, pstruEvent->pu8Data, pstruEvent->u32Len);
        if(s_noPrintInHdmiATC == HI_FALSE)
        {
            PRINTF("Current progress is %d, Duration:%lld ms,Buffer size:%lld bytes\n",
                stProgress.u32Progress, stProgress.s64Duration,stProgress.s64BufferSize);
        }
    }
    else if (HI_SVR_PLAYER_EVENT_ERROR == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        HI_S32 s32SysError = (HI_S32)*pstruEvent->pu8Data;

        if (HI_SVR_PLAYER_ERROR_VID_PLAY_FAIL == s32SysError)
        {
            PRINTF("ERR: Vid start fail!\n");
        }
        else if (HI_SVR_PLAYER_ERROR_AUD_PLAY_FAIL == s32SysError)
        {
            PRINTF("ERR: Aud start fail!\n");
        }
        else if (HI_SVR_PLAYER_ERROR_PLAY_FAIL == s32SysError)
        {
            PRINTF("ERR: Play fail!\n");
        }
        else if (HI_SVR_PLAYER_ERROR_NOT_SUPPORT == s32SysError)
        {
            PRINTF("ERR: Not support!\n");
        }
        else if (HI_SVR_PLAYER_ERROR_TIMEOUT == s32SysError)
        {
            PRINTF("ERR: Time Out!\n");
        }
        else
        {
            PRINTF("unknow Error = 0x%x \n", s32SysError);
        }
    }
    else if (HI_SVR_PLAYER_EVENT_NETWORK_INFO == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        HI_FORMAT_NET_STATUS_S *pstNetStat = (HI_FORMAT_NET_STATUS_S*)pstruEvent->pu8Data;
        PRINTF("HI_SVR_PLAYER_EVNET_NETWORK_INFO: type:%d, code:%d, str:%s\n",
            pstNetStat->eType, pstNetStat->s32ErrorCode, pstNetStat->szProtocals);
        if (pstNetStat->eType == HI_FORMAT_MSG_NETWORK_ERROR_DISCONNECT)
        {
            s32Ret = pthread_create(&s_hThread, HI_NULL, reconnect, (HI_VOID*)hPlayer);
            if (s32Ret == HI_SUCCESS)
            {
                PRINTF("create thread:reconnect successfully\n");
            }
            else
            {
                PRINTF("ERR:failed to create thread:reconnect\n");
            }
        }
    }
    else if (HI_SVR_PLAYER_EVENT_FIRST_FRAME_TIME == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        HI_U32 u32Time = *((HI_U32*)pstruEvent->pu8Data);
        PRINTF("the first frame time is %d ms\n",u32Time);
    }
    else if (HI_SVR_PLAYER_EVENT_DOWNLOAD_PROGRESS == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        HI_SVR_PLAYER_PROGRESS_S stDown;
        HI_S64 s64BandWidth = 0;

        HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_BANDWIDTH, &s64BandWidth);

        memcpy(&stDown, pstruEvent->pu8Data, pstruEvent->u32Len);
        PRINTF("download progress:%d, duration:%lld ms, buffer size:%lld bytes, bandwidth = %lld\n",
            stDown.u32Progress, stDown.s64Duration, stDown.s64BufferSize, s64BandWidth);
        if (stDown.u32Progress >= 100 && s32PausedCtrl == 2){
            HI_SVR_PLAYER_Resume(hPlayer);
        }
    }
    else if (HI_SVR_PLAYER_EVENT_BUFFER_STATE == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        HI_SVR_PLAYER_BUFFER_S *pstBufStat = (HI_SVR_PLAYER_BUFFER_S*)pstruEvent->pu8Data;
        PRINTF("HI_SVR_PLAYER_EVENT_BUFFER_STATE type:%d, duration:%lld ms, size:%lld bytes\n",pstBufStat->eType,
            pstBufStat->stBufStat.s64Duration,
            pstBufStat->stBufStat.s64BufferSize);

        HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

        if (pstBufStat->eType == HI_SVR_PLAYER_BUFFER_EMPTY)
        {
            PRINTF("### HI_SVR_PLAYER_EVENT_BUFFER_STATE type:HI_SVR_PLAYER_BUFFER_EMPTY, duration:%lld ms, size:%lld bytes\n",
                pstBufStat->stBufStat.s64Duration,
                pstBufStat->stBufStat.s64BufferSize);
            if ((HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType ||
                HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType ) &&
                HI_SVR_PLAYER_STATE_PLAY == ePlayerState)
            {
                s32PausedCtrl = 1;
                HI_SVR_PLAYER_Pause(hPlayer);
            }
        }
        else if (pstBufStat->eType == HI_SVR_PLAYER_BUFFER_START)
        {
            PRINTF("### HI_SVR_PLAYER_EVENT_BUFFER_STATE type:HI_SVR_PLAYER_BUFFER_START, duration:%lld ms, size:%lld bytes\n",
                pstBufStat->stBufStat.s64Duration,
                pstBufStat->stBufStat.s64BufferSize);
            if ((HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType ||
                HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType ) &&
                HI_SVR_PLAYER_STATE_PLAY == ePlayerState)
            {
                s32PausedCtrl = 1;
                HI_SVR_PLAYER_Pause(hPlayer);
            }
        }
        else if (pstBufStat->eType == HI_SVR_PLAYER_BUFFER_ENOUGH)
        {
            PRINTF("### HI_SVR_PLAYER_EVENT_BUFFER_STATE type:HI_SVR_PLAYER_BUFFER_ENOUGH, duration:%lld ms, size:%lld bytes\n",
                pstBufStat->stBufStat.s64Duration,
                pstBufStat->stBufStat.s64BufferSize);
            if ((HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType ||
                HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType ) &&
                2 == s32PausedCtrl)
            {
                HI_SVR_PLAYER_Resume(hPlayer);
            }
        }
        else if (pstBufStat->eType == HI_SVR_PLAYER_BUFFER_FULL)
        {
            PRINTF("### HI_SVR_PLAYER_EVENT_BUFFER_STATE type:HI_SVR_PLAYER_BUFFER_FULL, duration:%lld ms, size:%lld bytes\n",
                pstBufStat->stBufStat.s64Duration,
                pstBufStat->stBufStat.s64BufferSize);
            if ((HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType ||
                HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType ) &&
                2 == s32PausedCtrl)
            {
                HI_SVR_PLAYER_Resume(hPlayer);
            }
        }
    }
    else if (HI_SVR_PLAYER_EVENT_SEEK_FINISHED == (HI_SVR_PLAYER_EVENT_E)pstruEvent->eEvent)
    {
        PRINTF("seek finish! \n");
    }
    else
    {
        PRINTF("unknow event type is %d\n",pstruEvent->eEvent);
    }

    return HI_SUCCESS;
}

static HI_S32 outputText(const HI_CHAR* pszText, HI_RECT *pstRect)
{
    if (HIGO_INVALID_HANDLE != s_hFont && HIGO_INVALID_HANDLE != s_hLayer)
    {
        (HI_VOID)HI_GO_TextOutEx(s_hFont, s_hLayerSurface, pszText, pstRect,
            HIGO_LAYOUT_WRAP | HIGO_LAYOUT_HCENTER | HIGO_LAYOUT_BOTTOM); /*lint !e655*/
        (HI_VOID)HI_GO_RefreshLayer(s_hLayer, NULL);
    }
    else
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 subOndraw(HI_U32 u32UserData, const HI_UNF_SO_SUBTITLE_INFO_S *pstInfo, HI_VOID *pArg)
{
    HI_RECT rc = {260, 450, 760, 200};//{260, 550, 760, 100};
    HI_S32 s32Ret = HI_FAILURE;
    HI_CHAR *pszOutHand = NULL;
    HI_SO_SUBTITLE_ASS_DIALOG_S *pstDialog = NULL;
    HI_PIXELDATA pData;
    HI_S32 s32AssLen = 0;
    HI_U32 u32DisplayWidth = 0, u32DisplayHeight = 0;

    if (HI_UNF_SUBTITLE_ASS != pstInfo->eType)
    {
        if (NULL != s_pstParseHand)
        {
            HI_SO_SUBTITLE_ASS_DeinitParseHand(s_pstParseHand);
            s_pstParseHand = NULL;
        }
    }

    switch (pstInfo->eType)
    {
    case HI_UNF_SUBTITLE_BITMAP:
        clearSubtitle();
        PRINTF("sub title bitmap! \n");
        {
            HI_U32 i = 0, j = 0;
            HI_U32 u32PaletteIdx = 0;
            HI_U8 *pu8Surface = NULL;
            HI_S32 x = 100 ,y= 100;
            HI_S32 s32GfxX, s32GfxY;
            HI_S32 s32SurfaceW = 0, s32SurfaceH = 0;
            HI_S32 s32SurfaceX, s32SurfaceY, s32SurfaceYOff = 0;
            HI_S32 s32DrawH, s32DrawW;
            HI_BOOL bScale = HI_FALSE;

            HI_GO_LockSurface(s_hLayerSurface, pData, HI_TRUE);
            HI_GO_GetSurfaceSize(s_hLayerSurface, &s32SurfaceW, &s32SurfaceH);

            pu8Surface = (HI_U8*)pData[0].pData;

            if (NULL == pu8Surface)
            {
                HI_GO_UnlockSurface(s_hLayerSurface);
                return HI_SUCCESS;
            }

            if (s32SurfaceW * s32SurfaceH * pData[0].Bpp < pstInfo->unSubtitleParam.stGfx.h * pstInfo->unSubtitleParam.stGfx.w * 4)
            {
                HI_GO_UnlockSurface(s_hLayerSurface);
                return HI_SUCCESS;
            }

            /*l00192899,if the len==0, should not get u32PaletteIdx from pu8PixData, it will make a segment fault*/
            if( (pstInfo->unSubtitleParam.stGfx.w <=0) || (pstInfo->unSubtitleParam.stGfx.h <=0) || (pstInfo->unSubtitleParam.stGfx.pu8PixData ==NULL) || (pstInfo->unSubtitleParam.stGfx.u32Len <=0))
            {
                break;
            }

            if (HI_SUCCESS == HI_UNF_DISP_GetVirtualScreen(HI_UNF_DISPLAY1, &u32DisplayWidth, &u32DisplayHeight))
            {
                if (pstInfo->unSubtitleParam.stGfx.w <= u32DisplayWidth && pstInfo->unSubtitleParam.stGfx.h <= u32DisplayHeight)
                {
                    x = (u32DisplayWidth - pstInfo->unSubtitleParam.stGfx.w)/2;
                    y = u32DisplayHeight - pstInfo->unSubtitleParam.stGfx.h - 100;
                }
                else
                {
                    /*scale it*/
                    bScale = HI_TRUE;
                    x = 0;
                    y = 0;
                }
            }

            s32SurfaceX = x;
            s32SurfaceY = y;
            if (bScale)
            {
                s32DrawW = s32SurfaceW;
                s32DrawH = pstInfo->unSubtitleParam.stGfx.h * s32SurfaceW/pstInfo->unSubtitleParam.stGfx.w;
                s32SurfaceY = s32SurfaceH - s32DrawH - 50;
                if (s32SurfaceY <= 0)
                {
                    s32SurfaceY = 20;
                }
                s32SurfaceYOff  = 0;
                for (i = 0; i < (HI_U32)s32DrawH; i++)
                {
                    s32GfxY = s32SurfaceYOff * (HI_S32)pstInfo->unSubtitleParam.stGfx.w/s32SurfaceW;
                    for (j = 0; j < (HI_U32)s32DrawW; j++)
                    {
                        s32GfxX = s32SurfaceX * (HI_S32)pstInfo->unSubtitleParam.stGfx.w/s32SurfaceW;
                        if (s32GfxY * pstInfo->unSubtitleParam.stGfx.w + s32GfxX >= pstInfo->unSubtitleParam.stGfx.u32Len)
                        {
                            PRINTF("error\n");
                            break;
                        }
                        u32PaletteIdx = pstInfo->unSubtitleParam.stGfx.pu8PixData[s32GfxY * pstInfo->unSubtitleParam.stGfx.w + s32GfxX];

                        if (u32PaletteIdx >= HI_UNF_SO_PALETTE_ENTRY)
                        {
                            break;
                        }


                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 2]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Red;
                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 1]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Green;
                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 0]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Blue;
                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 3]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Alpha;
                        s32SurfaceX++;
                    }
                    s32SurfaceX = x;
                    s32SurfaceY ++;
                    s32SurfaceYOff ++;
                }
            }
            else
            {
                for (i = 0; i < pstInfo->unSubtitleParam.stGfx.h; i++)
                {
                    for (j = 0; j < pstInfo->unSubtitleParam.stGfx.w; j++)
                    {
                        u32PaletteIdx = pstInfo->unSubtitleParam.stGfx.pu8PixData[i * pstInfo->unSubtitleParam.stGfx.w + j];

                        if (u32PaletteIdx >= HI_UNF_SO_PALETTE_ENTRY)
                        {
                            break;
                        }

                        if (i * pstInfo->unSubtitleParam.stGfx.w + j > pstInfo->unSubtitleParam.stGfx.u32Len)
                        {
                            break;
                        }

                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 2]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Red;
                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 1]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Green;
                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 0]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Blue;
                        pu8Surface[s32SurfaceY * pData[0].Pitch + 4 * s32SurfaceX + 3]
                            = pstInfo->unSubtitleParam.stGfx.stPalette[u32PaletteIdx].u8Alpha;
                        s32SurfaceX++;
                    }
                    s32SurfaceX = x;
                    s32SurfaceY++;
                }
            }

            HI_GO_UnlockSurface(s_hLayerSurface);
            // HI_GO_SetLayerPos(s_hLayer, x, y);
            HI_GO_SetLayerPos(s_hLayer, 0,0);
            (HI_VOID)HI_GO_RefreshLayer(s_hLayer, NULL);
            // update the current pgs clear time
            if (s_bPgs)
            {
                s_s64CurPgsClearTime = pstInfo->unSubtitleParam.stGfx.s64Pts + pstInfo->unSubtitleParam.stGfx.u32Duration;
            }
        }
        break;

    case HI_UNF_SUBTITLE_TEXT:
        clearSubtitle();
        HI_GO_SetLayerPos(s_hLayer, 0, 0);
        if (NULL == pstInfo->unSubtitleParam.stText.pu8Data)
        {
            return HI_FAILURE;
        }

        PRINTF("OUTPUT: %s ", pstInfo->unSubtitleParam.stText.pu8Data);
        (HI_VOID)outputText((const HI_CHAR*)pstInfo->unSubtitleParam.stText.pu8Data, &rc);

        break;

    case HI_UNF_SUBTITLE_ASS:
        clearSubtitle();
        HI_GO_SetLayerPos(s_hLayer, 0, 0);
        if ( NULL == s_pstParseHand )
        {
            s32Ret = HI_SO_SUBTITLE_ASS_InitParseHand(&s_pstParseHand);

            if ( s32Ret != HI_SUCCESS )
            {
                return HI_FAILURE;
            }
        }

        s32Ret = HI_SO_SUBTITLE_ASS_StartParse(pstInfo, &pstDialog, s_pstParseHand);

        if (s32Ret == HI_SUCCESS)
        {
            s32Ret = HI_SO_SUBTITLE_ASS_GetDialogText(pstDialog, &pszOutHand, &s32AssLen);

            if ( s32Ret != HI_SUCCESS || NULL == pszOutHand )
            {
                PRINTF("##########can't parse this Dialog!#########\n");
            }
            else
            {
                (HI_VOID)outputText(pszOutHand, &rc);
                PRINTF("OUTPUT: %s \n", pszOutHand);
            }
        }
        else
        {
            PRINTF("##########can't parse this ass file!#########\n");
        }

        free(pszOutHand);
        pszOutHand = NULL;
        HI_SO_SUBTITLE_ASS_FreeDialog(&pstDialog);
        break;

    default:
        break;
    }

    return HI_SUCCESS;
}

static HI_S32 clearSubtitle()
{
    HI_RECT rc = {160, 550, 760, 100};
    HI_CHAR TextClear[] = "";

    PRINTF("CLEAR Subtitle! \n");
    (HI_VOID)HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);

    if (HIGO_INVALID_HANDLE != s_hFont && HIGO_INVALID_HANDLE != s_hLayer)
    {
        (HI_VOID)HI_GO_TextOutEx(s_hFont, s_hLayerSurface, TextClear, &rc,
            HIGO_LAYOUT_WRAP | HIGO_LAYOUT_HCENTER | HIGO_LAYOUT_BOTTOM); /*lint !e655*/
    }

    if (HIGO_INVALID_HANDLE != s_hLayer)
        (HI_VOID)HI_GO_RefreshLayer(s_hLayer, NULL);

    return HI_SUCCESS;
}

static HI_S32 subOnclear(HI_U32 u32UserData, HI_VOID *pArg)
{
    HI_RECT rc = {160, 550, 760, 100};
    HI_CHAR TextClear[] = "";

#if 1
    HI_UNF_SO_CLEAR_PARAM_S *pstClearParam = NULL;
    if(pArg)
    {
        pstClearParam = (HI_UNF_SO_CLEAR_PARAM_S *)pArg;
    }

    // l00192899 if clear operation time is earlier than s_s64CurPgsClearTime,current clear operation is out of date */
    // the clear operation must come from previous pgs subtitle.
    if(-1 != s_s64CurPgsClearTime && pstClearParam)
    {
        if (pstClearParam->s64ClearTime < s_s64CurPgsClearTime)
        {
            PRINTF("s64Cleartime=%lld s_s64CurPgsClearTime=%lld is not time!\n", pstClearParam->s64ClearTime,s_s64CurPgsClearTime);
            return HI_SUCCESS;
        }
    }
#endif

    PRINTF("CLEAR Subtitle! \n");
    (HI_VOID)HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);

    if (HIGO_INVALID_HANDLE != s_hFont && HIGO_INVALID_HANDLE != s_hLayer)
    {
        (HI_VOID)HI_GO_TextOutEx(s_hFont, s_hLayerSurface, TextClear, &rc,
            HIGO_LAYOUT_WRAP | HIGO_LAYOUT_HCENTER | HIGO_LAYOUT_BOTTOM); /*lint !e655*/
    }

    if (HIGO_INVALID_HANDLE != s_hLayer)
        (HI_VOID)HI_GO_RefreshLayer(s_hLayer, NULL);

    return HI_SUCCESS;
}

static HI_S32 outFileInfo(HI_FORMAT_FILE_INFO_S *pstFileInfo)
{
    HI_U32 i = 0, j = 0;

    PRINTF("\n\n*************************************************\n");

    if (HI_FORMAT_STREAM_TS == pstFileInfo->eStreamType)
        PRINTF("Stream type: %s \n", "TS");
    else
        PRINTF("Stream type: %s \n", "ES");

    if (HI_FORMAT_SOURCE_NET_VOD == pstFileInfo->eSourceType)
        PRINTF("Source type: %s \n", "NETWORK VOD");
    else if (HI_FORMAT_SOURCE_NET_LIVE == pstFileInfo->eSourceType)
        PRINTF("Source type: %s \n", "NETWORK LIVE");
    else if (HI_FORMAT_SOURCE_LOCAL == pstFileInfo->eSourceType)
        PRINTF("Source type: %s \n", "LOCAL");
    else
        PRINTF("Source type: %s \n", "UNKNOWN");

    PRINTF("File size:   %lld bytes \n", pstFileInfo->s64FileSize);
    PRINTF("Start time:  %lld:%lld:%lld \n",
        pstFileInfo->s64StartTime / (1000 * 3600),
        (pstFileInfo->s64StartTime % (1000 * 3600)) / (1000 * 60),
        ((pstFileInfo->s64StartTime % (1000 * 3600)) % (1000 * 60)) / 1000);
    PRINTF("Duration:    %lld:%lld:%lld \n",
        pstFileInfo->s64Duration / (1000 * 3600),
        (pstFileInfo->s64Duration % (1000 * 3600)) / (1000 * 60),
        ((pstFileInfo->s64Duration % (1000 * 3600)) % (1000 * 60)) / 1000);
    PRINTF("bps:         %d bits/s \n", pstFileInfo->u32Bitrate);

    for (i = 0; i < pstFileInfo->u32ProgramNum; i++)
    {
        PRINTF("\nProgram %d: \n", i);
        PRINTF("   video info: \n");

        for (j = 0; j < pstFileInfo->pastProgramInfo[i].u32VidStreamNum; j++)
        {
            if (HI_FORMAT_INVALID_STREAM_ID != pstFileInfo->pastProgramInfo[i].pastVidStream[j].s32StreamIndex)
            {
                PRINTF("     stream idx:   %d \n", pstFileInfo->pastProgramInfo[i].pastVidStream[j].s32StreamIndex);
                PRINTF("     format:       %s \n", getVidFormatStr(pstFileInfo->pastProgramInfo[i].pastVidStream[j].u32Format));
                PRINTF("     w * h:        %d * %d \n",
                    pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16Width,
                    pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16Height);
                PRINTF("     fps:          %d.%d \n",
                    pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16FpsInteger,
                    pstFileInfo->pastProgramInfo[i].pastVidStream[j].u16FpsDecimal);
                PRINTF("     bps:          %d bits/s \n", pstFileInfo->pastProgramInfo[i].pastVidStream[j].u32Bitrate);
            }
        }

        if (pstFileInfo->pastProgramInfo[i].u32VidStreamNum <= 0)
        {
            PRINTF("     video stream is null. \n");
        }

        for (j = 0; j < pstFileInfo->pastProgramInfo[i].u32AudStreamNum; j++)
        {
            PRINTF("   audio %d info: \n", j);
            PRINTF("     stream idx:   %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].s32StreamIndex);
            PRINTF("     format:       %s \n", getAudFormatStr(pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32Format));
            PRINTF("     profile:      0x%x \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32Profile);
            PRINTF("     samplerate:   %d Hz \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32SampleRate);
            PRINTF("     bitpersample: %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16BitPerSample);
            PRINTF("     channels:     %d \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u16Channels);
            PRINTF("     bps:          %d bits/s \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].u32Bitrate);
            PRINTF("     lang:         %s \n", pstFileInfo->pastProgramInfo[i].pastAudStream[j].aszLanguage);
        }

        for (j = 0; j < pstFileInfo->pastProgramInfo[i].u32SubStreamNum; j++)
        {
            PRINTF("   subtitle %d info: \n", j);
            PRINTF("     stream idx:     %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].s32StreamIndex);
            PRINTF("     sub type:       %s \n", getSubFormatStr(pstFileInfo->pastProgramInfo[i].pastSubStream[j].u32Format));
            PRINTF("     be ext sub:     %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].bExtSub);
            PRINTF("     original width: %d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u16OriginalFrameWidth);
            PRINTF("     original height:%d \n", pstFileInfo->pastProgramInfo[i].pastSubStream[j].u16OriginalFrameHeight);
        }
    }

    PRINTF("\n*************************************************\n\n");

    return HI_SUCCESS;
}

static HI_S32 parserSubFile(HI_CHAR *pargv, HI_SVR_PLAYER_MEDIA_S *pstMedia)
{
    HI_CHAR *p = NULL, *q = NULL;

    /* ���������Ļ */
    p = pargv;

    while (NULL != p)
    {
        q = strchr(p, ',');

        if (NULL == q)
        {
            sprintf(pstMedia->aszExtSubUrl[pstMedia->u32ExtSubNum], "%s", p);
            pstMedia->u32ExtSubNum++;
            break;
        }
        else
        {
            memcpy(pstMedia->aszExtSubUrl[pstMedia->u32ExtSubNum], p, q - p);
            pstMedia->u32ExtSubNum++;
        }

        if (HI_FORMAT_MAX_LANG_NUM <= pstMedia->u32ExtSubNum)
        {
            break;
        }

        p = q + 1;
    }

    return HI_SUCCESS;
}

static HI_S32 getClosely3DDisplayFormat(
        HI_HANDLE hPlayer,
        HI_UNF_DISP_3D_E en3D,
        HI_UNF_ENC_FMT_E *pen3DEncodingFormat,
        HI_UNF_VIDEO_FRAME_PACKING_TYPE_E  *penFrameType
        )
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;
    HI_FORMAT_VID_INFO_S *pstVidStream = NULL;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_U16 u16Fps;

    if (pen3DEncodingFormat == NULL ||
        penFrameType == NULL ||
        HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId) != HI_SUCCESS ||
        HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo) != HI_SUCCESS ||
        pstFileInfo->u32ProgramNum <= 0 ||
        pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32VidStreamNum <= 0)
    {
        return HI_FAILURE;
    }

    pstVidStream = &pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastVidStream[stStreamId.u16VidStreamId];
    u16Fps = pstVidStream->u16FpsInteger;

    switch(en3D)
    {
        case HI_UNF_DISP_3D_FRAME_PACKING:
            if (u16Fps <= 50)
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING;
            }
            else if (u16Fps <= 60)
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_720P_50_FRAME_PACKING;
            }
            else
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_720P_60_FRAME_PACKING;
            }
            *penFrameType = HI_UNF_FRAME_PACKING_TYPE_TIME_INTERLACED;
            break;
        case HI_UNF_DISP_3D_SIDE_BY_SIDE_HALF:
            if (u16Fps <= 60)
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_1080i_50;
            }
            else
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_1080i_60;
            }
            *penFrameType = HI_UNF_FRAME_PACKING_TYPE_SIDE_BY_SIDE;
            break;
        case HI_UNF_DISP_3D_TOP_AND_BOTTOM:
            if (u16Fps <= 50)
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_1080P_24;
            }
            else if (u16Fps <= 60)
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_720P_50;
            }
            else
            {
                *pen3DEncodingFormat = HI_UNF_ENC_FMT_720P_60;
            }
            *penFrameType = HI_UNF_FRAME_PACKING_TYPE_TOP_AND_BOTTOM;
            break;
        case HI_UNF_DISP_3D_SIDE_BY_SIDE_FULL:
        default:
            *pen3DEncodingFormat = HI_UNF_ENC_FMT_BUTT;
            *penFrameType = HI_UNF_FRAME_PACKING_TYPE_BUTT;
            s32Ret = HI_FAILURE;
            PRINTF("3D Mode %d not supported now\n", en3D);
    }

    return s32Ret;
}

static HI_S32 setVideoMode(HI_HANDLE hPlayer, HI_UNF_DISP_3D_E en3D)
{
    HI_S32 s32Ret, s32Ret1;
    HI_UNF_DISP_3D_E enCur3D;
    HI_UNF_ENC_FMT_E enCurEncFormat, enEncFormat = HI_UNF_ENC_FMT_720P_50;
    HI_UNF_VIDEO_FRAME_PACKING_TYPE_E enFrameType = HI_UNF_FRAME_PACKING_TYPE_NONE;
    HI_UNF_EDID_BASE_INFO_S stSinkAttr;
    HI_BOOL bSetMode = HI_FALSE;
    HI_HANDLE hAVPlay = (HI_HANDLE)NULL;

    s32Ret = HI_UNF_DISP_Get3DMode((HI_UNF_DISP_E)s_stParam.u32Display, &enCur3D, &enCurEncFormat);
    if (s32Ret == HI_SUCCESS &&
        enCur3D == en3D)
    {
        PRINTF("Already in Mode:%d!\n", en3D);
        return HI_SUCCESS;
    }

    /*switch to 2D Mode*/
    if (en3D == HI_UNF_DISP_3D_NONE)
    {
        enEncFormat = HI_UNF_ENC_FMT_720P_50;
        bSetMode = HI_TRUE;
        enFrameType = HI_UNF_FRAME_PACKING_TYPE_NONE;
    }
    /*switch to 3D Mode*/
    else
    {
        s32Ret = HI_UNF_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_0, &stSinkAttr);
        if (s32Ret == HI_SUCCESS &&
            stSinkAttr.st3DInfo.bSupport3D == HI_TRUE)
        {
            if (getClosely3DDisplayFormat(hPlayer, en3D, &enEncFormat, &enFrameType) == HI_SUCCESS)
            {
                bSetMode = HI_TRUE;
            }
        }
        else if (s32Ret != HI_SUCCESS)
        {
            PRINTF("Get HDMI sink capability ret error:%#x\n", s32Ret);
        }
        else
        {
            PRINTF("HDMI Sink video mode not supported.\n");
        }
    }

    if (bSetMode == HI_TRUE)
    {
        s32Ret1 = HI_UNF_HDMI_SetAVMute(HI_UNF_HDMI_ID_0, HI_TRUE);
        if (s32Ret1 != HI_SUCCESS)
        {
            PRINTF("Set Hdmi av mute ret error,%#x \n", s32Ret1);
        }

        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAVPlay);
        if (s32Ret == HI_SUCCESS)
        {
            /*mvc don't need to set framepack type*/
            s32Ret = HI_UNF_AVPLAY_SetAttr(hAVPlay, HI_UNF_AVPLAY_ATTR_ID_FRMPACK_TYPE, (HI_VOID*)&enFrameType);
            s32Ret |= HI_UNF_DISP_Set3DMode((HI_UNF_DISP_E)s_stParam.u32Display, en3D, enEncFormat);
        }

        s32Ret1 = HI_UNF_HDMI_SetAVMute(HI_UNF_HDMI_ID_0, HI_FALSE);
        if (s32Ret1 != HI_SUCCESS)
        {
            PRINTF("Set Hdmi av unmute ret error,%#x \n", s32Ret1);
        }
    }
    else
    {
        s32Ret = HI_FAILURE;
    }

    PRINTF("set videomode from(mode:%d,fmt:%d) to (mode:%d,format:%d) ret %#x\n",
            enCur3D, enCurEncFormat, en3D, enEncFormat, s32Ret);

    return s32Ret;
}

HI_S32 setAttr(HI_HANDLE hPlayer, HI_CHAR *pszCmd)
{
    HI_S32 s32Ret = 0;
    HI_HANDLE hdl = 0;
    HI_U32 u32Tmp = 0;
    HI_SVR_PLAYER_SYNC_ATTR_S stSyncAttr;
    HI_UNF_WINDOW_ATTR_S stWinAttr;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_UNF_DISP_ASPECT_RATIO_S stAspectRatio;
    HI_UNF_SND_GAIN_ATTR_S stGain;

    if (NULL == pszCmd)
        return HI_FAILURE;

    if (0 == strncmp("sync", pszCmd, 4))
    {
        if (3 != sscanf(pszCmd, "sync %d %d %d",
            &stSyncAttr.s32VidFrameOffset, &stSyncAttr.s32AudFrameOffset, &stSyncAttr.s32SubTitleOffset))
        {
            PRINTF("ERR: input err, example: set sync vidptsadjust audptsadjust, subptsadjust! \n");
            return HI_FAILURE;
        }

        s32Ret = HI_SVR_PLAYER_SetParam(hPlayer, HI_SVR_PLAYER_ATTR_SYNC, (HI_VOID*)&stSyncAttr);
    }
    else if (0 == strncmp("vol", pszCmd, 3))
    {
#if (USE_EXTERNAL_AVPLAY == 1)
        if ((HI_HANDLE)INVALID_TRACK_HDL == s_hAudioTrack)
        {
            PRINTF("ERR: audio track handle is invalid! \n");
            return HI_FAILURE;
        }
        hdl = s_hAudioTrack;
#else
        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_AUDTRACK_HDL, &hdl);
        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: get audio track hdl fail! \n");
            return HI_FAILURE;
        }
#endif

        if (1 != sscanf(pszCmd, "vol %d", &u32Tmp))
        {
            PRINTF("ERR: not input volume! \n");
            return HI_FAILURE;
        }
        stGain.bLinearMode = HI_TRUE;
        stGain.s32Gain = u32Tmp;

        s32Ret = HI_UNF_SND_SetTrackWeight(hdl, &stGain);
        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: set volume failed! \n");
            return HI_FAILURE;
        }
    }
    else if (0 == strncmp("track", pszCmd, 5))
    {
        if (1 != sscanf(pszCmd, "track %d", &u32Tmp))
        {
            PRINTF("ERR: not input track mode! \n");
            return HI_FAILURE;
        }

        s32Ret = HI_UNF_SND_SetTrackMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL,(HI_UNF_TRACK_MODE_E)u32Tmp);
    }
    else if (0 == strncmp("mute", pszCmd, 4))
    {
        if (1 != sscanf(pszCmd, "mute %d", &u32Tmp))
        {
            PRINTF("ERR: not input mute val! \n");
            return HI_FAILURE;
        }

        s32Ret = HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL,(HI_BOOL)u32Tmp);
    }
    else if (0 == strncmp("pos", pszCmd, 3))
    {
        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hdl);
        s32Ret |= HI_UNF_VO_GetWindowAttr(hdl, &stWinAttr);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: get win attr fail! \n");
            return HI_FAILURE;
        }

        if (4 != sscanf(pszCmd, "pos %d %d %d %d",
            &stWinAttr.stOutputRect.s32X,
            &stWinAttr.stOutputRect.s32Y,
            &stWinAttr.stOutputRect.s32Width,
            &stWinAttr.stOutputRect.s32Height))
        {
            PRINTF("ERR: input err, example: set pos x y width height! \n");
            return HI_FAILURE;
        }

        s32Ret = HI_UNF_VO_SetWindowAttr(hdl, &stWinAttr);
    }
    else if (0 == strncmp("aspect", pszCmd, 6))
    {
        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hdl);
        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: get win attr fail! \n");
            return HI_FAILURE;
        }

        if (1 != sscanf(pszCmd, "aspect %d", &u32Tmp))
        {
            PRINTF("ERR: not input aspectration val! \n");
            return HI_FAILURE;
        }
        stAspectRatio.enDispAspectRatio = (HI_UNF_DISP_ASPECT_RATIO_E)u32Tmp;
        if (stAspectRatio.enDispAspectRatio== HI_UNF_DISP_ASPECT_RATIO_USER)
        {
            PRINTF("ERR: set aspect ratio fail, use user-aspect instead.\n");
            return HI_FAILURE;
        }
        s32Ret = HI_UNF_DISP_SetAspectRatio((HI_UNF_DISP_E)hdl, &stAspectRatio);
        if (s32Ret != HI_SUCCESS)
        {
            PRINTF("ERR: set aspect ratio fail.\n");
            return HI_FAILURE;
        }
    }
    else if (0 == strncmp("user-aspect", pszCmd, 11))
    {
        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hdl);
        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: get win attr fail! \n");
            return HI_FAILURE;
        }

        if (3 != sscanf(pszCmd, "user-aspect %u %u %u", &u32Tmp,
            &stAspectRatio.u32UserAspectWidth, &stAspectRatio.u32UserAspectHeight))
        {
            PRINTF("ERR: not input user-aspectration vals! \n");
            return HI_FAILURE;
        }
        stAspectRatio.enDispAspectRatio = (HI_UNF_DISP_ASPECT_RATIO_E)u32Tmp;
        if (stAspectRatio.enDispAspectRatio != HI_UNF_DISP_ASPECT_RATIO_USER)
        {
            PRINTF("ERR: set user-aspect ratio fail, use aspect instead.\n");
            return HI_FAILURE;
        }
        s32Ret = HI_UNF_DISP_SetAspectRatio((HI_UNF_DISP_E)hdl, &stAspectRatio);
        if (s32Ret != HI_SUCCESS)
        {
            PRINTF("ERR: set user-aspect ratio fail.\n");
            return HI_FAILURE;
        }
    }
    else if (0 == strncmp("zorder", pszCmd, 6))
    {
        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_WINDOW_HDL, &hdl);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: get win hdl fail! \n");
            return HI_FAILURE;
        }

        if (1 != sscanf(pszCmd, "zorder %d", &u32Tmp))
        {
            PRINTF("ERR: not input zorder val! \n");
            return HI_FAILURE;
        }

        s32Ret = HI_UNF_VO_SetWindowZorder(hdl, (HI_LAYER_ZORDER_E)u32Tmp);
    }
    else if (0 == strncmp("id", pszCmd, 2))
    {
        HI_FORMAT_FILE_INFO_S *pstFileInfo = NULL;

        s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);
        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("ERR: get file info fail! \n");
            return HI_FAILURE;
        }

        if (4 != sscanf(pszCmd, "id %hu %hu %hu %hu",
            &stStreamId.u16ProgramId,
            &stStreamId.u16VidStreamId,
            &stStreamId.u16AudStreamId,
            &stStreamId.u16SubStreamId))
        {
            PRINTF("ERR: input err, example: set id 0 0 1 0, set id prgid videoid audioid subtitleid! \n");
            return HI_FAILURE;
        }

        if (stStreamId.u16ProgramId >= pstFileInfo->u32ProgramNum ||
            (stStreamId.u16VidStreamId != 0 &&
             stStreamId.u16VidStreamId >= pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32VidStreamNum) ||
            (stStreamId.u16AudStreamId != 0 &&
             stStreamId.u16AudStreamId >= pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32AudStreamNum) ||
            (stStreamId.u16SubStreamId != 0 &&
             stStreamId.u16SubStreamId >= pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum))
        {
            PRINTF("invalid stream id\n");
            return HI_FAILURE;
        }

        s32Ret = HI_SVR_PLAYER_SetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId);

        if (HI_SUCCESS == s32Ret &&
            pstFileInfo->u32ProgramNum > 0 &&
            pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].u32SubStreamNum > 0)
        {
            if (pstFileInfo->pastProgramInfo[stStreamId.u16ProgramId].pastSubStream[stStreamId.u16SubStreamId].u32Format ==
                HI_FORMAT_SUBTITLE_HDMV_PGS)
            {
                s_bPgs = HI_TRUE;
            }
            else
            {
                s_s64CurPgsClearTime = -1;
                s_bPgs = HI_FALSE;
            }
        }
    }
    else if (0 == strncmp("vmode", pszCmd, 5))
    {
        if (1 != sscanf(pszCmd, "vmode %u", &u32Tmp))
        {
            PRINTF("no input val for set video mode!(%d-2d,%d-framepacking,%d-sbs,%d-tab...) \n",
                    HI_UNF_DISP_3D_NONE, HI_UNF_DISP_3D_FRAME_PACKING, HI_UNF_DISP_3D_SIDE_BY_SIDE_HALF,
                    HI_UNF_DISP_3D_TOP_AND_BOTTOM);
            PRINTF("for example:set vmode 1\n");
            return HI_FAILURE;
        }
        else if (u32Tmp >= HI_UNF_DISP_3D_BUTT)
        {
            PRINTF("invalid video mode (%u),should < %d\n", u32Tmp,  HI_UNF_DISP_3D_BUTT);
        }

        setVideoMode(hPlayer, (HI_UNF_DISP_3D_E)u32Tmp);
    }
    else if (0 == strncmp("hdmi", pszCmd, 4))
    {

        static int hdmi_toggle =0;
        hdmi_toggle++;
        if(hdmi_toggle&1)
        {
            HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
            printf("hmdi pass-through on!\n");
        }
        else
        {
            HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_LPCM);
            printf("hmdi pass-through off!\n");
        }

    }
    else if (0 == strncmp("spdif", pszCmd, 5))
    {
        static int spdif_toggle = 0;
        spdif_toggle++;
        if (spdif_toggle & 1)
        {
            HI_UNF_SND_SetSpdifMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_UNF_SND_SPDIF_MODE_RAW);
            printf("spdif pass-through on!\n");
        }
        else
        {
            HI_UNF_SND_SetSpdifMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_UNF_SND_SPDIF_MODE_LPCM);
            printf("spdif pass-through off!\n");
        }
    }
    else
    {
        PRINTF("ERR: not support commond! \n");
    }

    return HI_SUCCESS;
}

HI_S32 getAttr(HI_HANDLE hPlayer, HI_CHAR *pszCmd)
{
    HI_S32 s32Ret = 0;
    HI_S64 s64Tmp = 0;
    HI_CHAR cTmp[512];
    HI_FORMAT_BUFFER_CONFIG_S stBufConfig;
    HI_FORMAT_BUFFER_STATUS_S stBufStatus;

    if (NULL == pszCmd)
        return HI_FAILURE;

    if (0 == strncmp("bandwidth", pszCmd, 9))
    {
        s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_BANDWIDTH, (HI_VOID*)&s64Tmp);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("get bandwidth fail! \n");
            return HI_FAILURE;
        }

        PRINTF("get bandwidth is %lld bps\n", s64Tmp);
        PRINTF("get bandwidth is %lld K bps\n", s64Tmp/1024);
        PRINTF("get bandwidth is %lld KBps\n", s64Tmp/8192);
    }
    else if (0 == strncmp("bufferconfig", pszCmd, 12))
    {
        memset(&stBufConfig, 0, sizeof(HI_FORMAT_BUFFER_CONFIG_S));

        if (1 != sscanf(pszCmd, "bufferconfig %s", cTmp))
        {
            PRINTF("ERR: not input bufferconfig type! \n");
            return HI_FAILURE;
        }

        if (0 == strcmp(cTmp,"size"))
        {
            stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_SIZE;
        }
        else if (0 == strcmp(cTmp, "time"))
        {
            stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_TIME;
        }
        else
        {
            PRINTF("ERR: do not know bufferconfig type(%s)! \n",cTmp);
            return HI_FAILURE;
        }

        s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, (HI_VOID*)&stBufConfig);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("get bufferconfig fail! \n");
            return HI_FAILURE;
        }
        PRINTF("BufferConfig:type(%d):%s\n",stBufConfig.eType, cTmp);
        PRINTF("s64EventStart:%lld\n", stBufConfig.s64EventStart);
        PRINTF("s64EventEnough:%lld\n", stBufConfig.s64EventEnough);
        PRINTF("s64Total:%lld\n", stBufConfig.s64Total);
        PRINTF("s64TimeOut:%lld\n", stBufConfig.s64TimeOut);
    }
    else if (0 == strncmp("bufferstatus", pszCmd, 12))
    {
        s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_BUFFER_STATUS, (HI_VOID*)&stBufStatus);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("get Buffer status fail! \n");
            return HI_FAILURE;
        }
        PRINTF("BufferStatus:\n");
        PRINTF("s64Duration:%lld ms\n", stBufStatus.s64Duration);
        PRINTF("s64BufferSize:%lld bytes\n", stBufStatus.s64BufferSize);
    }
    else if (0 == strncmp("hlsinfo", pszCmd, 7))
    {
        HI_FORMAT_HLS_STREAM_INFO_S stHlsInfo;

        if (1 != sscanf(pszCmd, "hlsinfo %d", &stHlsInfo.stream_nb) ||
                stHlsInfo.stream_nb < 0)
        {
            PRINTF("ERR: input err, example: get hlsinfo 0\n");
            return HI_FAILURE;
        }

        s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_HLS_STREAM_INFO, (HI_VOID*)&stHlsInfo);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("get HLS streaminfo fail! \n");
            return HI_FAILURE;
        }

        PRINTF("hls streamindex:%d\n", stHlsInfo.stream_nb);
        PRINTF("hls segments number in current stream:%d\n", stHlsInfo.hls_segment_nb);
        PRINTF("hls stream url:%s\n", stHlsInfo.url);
    }
    else if (0 == strncmp("hlsseg", pszCmd, 6))
    {
        HI_FORMAT_HLS_SEGMENT_INFO_S stHlsSegInfo;

        s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_HLS_SEGMENT_INFO, (HI_VOID*)&stHlsSegInfo);

        if (HI_SUCCESS != s32Ret)
        {
            PRINTF("get HLS segment info fail! \n");
            return HI_FAILURE;
        }

        PRINTF("hls stream of current segment:%d\n", stHlsSegInfo.stream_num);
        PRINTF("hls current segment duration :%d\n", stHlsSegInfo.total_time);
        PRINTF("hls index of current segment :%d\n", stHlsSegInfo.seq_num);
        PRINTF("hls bandwidth required       :%lld\n", stHlsSegInfo.bandwidth);
        PRINTF("hls current segment url      :%s\n", stHlsSegInfo.url);

    }
    else
    {
        PRINTF("ERR: not support command! \n");
    }

    return HI_SUCCESS;
}

HI_S32 higoInit()
{
    HI_S32 s32Ret = 0;

    HIGO_LAYER_INFO_S stLayerInfo = {0};

    s32Ret = HI_GO_Init();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: failed to init higo! ret = 0x%x !\n", s32Ret);
        return HI_FAILURE;
    }

    (HI_VOID)HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo);

    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_DOUBBUFER;
    stLayerInfo.PixelFormat = HIGO_PF_8888;
    s32Ret = HI_GO_CreateLayer(&stLayerInfo, &s_hLayer);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: failed to create the layer sd 0, ret = 0x%x !\n", s32Ret);
        goto RET;
    }

    s32Ret =  HI_GO_GetLayerSurface(s_hLayer, &s_hLayerSurface);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: failed to get layer surface! s32Ret = 0x%x \n", s32Ret);
        goto RET;
    }

    (HI_VOID)HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);
    s32Ret = HI_GO_CreateText("./higo_gb2312.ubf", NULL,  &s_hFont);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: failed to create the font:higo_gb2312.ubf !\n");
        goto RET;
    }

    (HI_VOID)HI_GO_SetTextColor(s_hFont, 0xffffffff);

    return HI_SUCCESS;

RET:
    return HI_FAILURE;
}

static HI_S32 CheckPlayerStatus(HI_HANDLE hPlayer, HI_U32 u32Status, HI_U32 u32TimeOutMs)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32Time = (HI_U32)times(NULL) * 10;
    HI_SVR_PLAYER_INFO_S stPlayerInfo;

    if (HI_SVR_PLAYER_STATE_BUTT <= u32Status)
    {
        return HI_FAILURE;
    }

    while (1)
    {
        s32Ret = HI_SVR_PLAYER_GetPlayerInfo(hPlayer, &stPlayerInfo);

        if (HI_SUCCESS == s32Ret && (HI_U32)stPlayerInfo.eStatus == u32Status)
        {
            return HI_SUCCESS;
        }

        if ((((HI_U32)times(NULL) * 10) - u32Time) >= u32TimeOutMs)
        {
            break;
        }

        usleep(SLEEP_TIME);
    }

    return HI_FAILURE;
}

static HI_S32 isSystemSuccessful(pid_t status)
{
    if (-1 == status)
    {
        PRINTF("\n---system error!!---");
        return -1;
    }
    else
    {
        PRINTF("\n---exit status value = [0x%x]---",status);
        if (WIFEXITED(status)) /*lint !e160*/
        {
            if (0 == WEXITSTATUS(status)) /*lint !e160*/
            {
                PRINTF("\n---run shell script successfully!!---");
                return 0;

            }
            else
            {
                PRINTF("\n---run shell script fail, script exit code: %d---",WEXITSTATUS(status)); /*lint !e160*/
                return -1;
            }
        }
        else
        {
            PRINTF("\n---exit status = [%d]---",WEXITSTATUS(status)); /*lint !e160*/
            return -1;
        }
    }
}

static HI_S32 do_mountiso(char *arg)
{
    pid_t status;
    static HI_U32 loopNum = 0;

    const HI_CHAR * path = arg;
//  const HI_CHAR * fuser = "fuser -km /mnt/iso/";
    const HI_CHAR * umount = "umount -f /mnt/iso/";
    const HI_CHAR * mount = "mount -o loop";

    HI_CHAR buff[512] = {0};

    if (loopNum < 64)
    {
        HI_CHAR mknod[512]={0};

        sprintf(mknod, "mknod /dev/loop%d b 7 %d",loopNum,loopNum);
        loopNum++;
        status = system(mknod);

        if (1 == loopNum)
        {
            sprintf(mknod, "mknod /dev/loop%d b 7 %d",loopNum,loopNum);
            loopNum++;
            status = system(mknod);
        }

        if (isSystemSuccessful(status) != 0)
        {
            PRINTF("\n----mknod error! -----");
        }
    }

    /*
    status = system(fuser);
    if (isSystemSuccessful(status) != 0)
    {
        PRINTF("----fuser /mnt/iso error! -----");
    }
    sleep(1);
    */

    status = system(umount);
    if (isSystemSuccessful(status) != 0)
    {
        PRINTF("----umount iso error! -----");
    }

    memset(buff,0,sizeof(buff));
    sprintf(buff, "%s %s %s", mount, path, "/mnt/iso");
    PRINTF("\n----mountiso buf -----=%s ",buff);
    status = system(buff);

    if (isSystemSuccessful(status) != 0)
    {
        PRINTF("\n----mount iso error! -----");
        return -errno;
    }

    return 0;
}

HI_S32 getfiledir(HI_CHAR *dirName,HI_CHAR *mediaUrl)
{
    DIR *dir = NULL;
    struct dirent *dir_env = NULL;
    //  struct stat stat_file;

    HI_CHAR dir_temp[1024] = {0};
    HI_CHAR vid_name[1024];

    FILE *m3u8 = fopen(mediaUrl,"w+");

    fwrite("#EXTM3U\n",8,1, m3u8);
    fwrite("#EXT-X-TARGETDURATION:\n",23,1, m3u8);
    fwrite("#EXT-X-MEDIA-SEQUENCE:\n",23,1, m3u8);
    fflush(m3u8);

    if ((dir = opendir(dirName)) == NULL)
    {
        return HI_FAILURE;
    }

    while ((dir_env = readdir(dir)) != NULL)
    {
        if (!strcasecmp(dir_env->d_name,"bdmv"))
        {
            strcpy(dir_temp,dirName);
            strcat(dir_temp,"bdmv/stream/");
            break;
        }
        else if (!strcasecmp(dir_env->d_name,"video_ts"))
        {
            strcpy(dir_temp,dirName);
            strcat(dir_temp,"video_ts/");
            break;
        }
    }

    closedir(dir);

    if ((dir = opendir(dir_temp)) == NULL)
    {
        return HI_FAILURE;
    }

    if (strstr(dir_temp,"bdmv/stream/"))  /*for bule ray*/
    {
        while ((dir_env = readdir(dir)) != NULL)
        {
            strcpy(vid_name,dir_temp);
            strcat(vid_name,dir_env->d_name);
            fwrite("#EXTINF:\n",9,1, m3u8);
            fwrite(vid_name,strlen(vid_name),1, m3u8);
            fwrite("\n",1,1, m3u8);
            fflush(m3u8);
        }
    }
    else if (strstr(dir_temp,"video_ts/"))  /*for DVD*/
    {
        while ((dir_env = readdir(dir)) != NULL)
        {
            if (strstr(dir_env->d_name,".vob"))
            {
                if (!strcasecmp(dir_env->d_name,"VIDEO_TS.VOB"))
                {
                    continue;
                }
                else
                {
                    strcpy(vid_name,dir_temp);
                    strcat(vid_name,dir_env->d_name);
                    fwrite("#EXTINF:\n",9,1, m3u8);
                    fwrite(vid_name,strlen(vid_name),1, m3u8);
                    fwrite("\n",1,1, m3u8);
                    fflush(m3u8);
                }
            }
        }
    }

    fwrite("#EXT-X-ENDLIST\n",15,1, m3u8);
    fflush(m3u8);
    fclose(m3u8);
    closedir(dir);

    return HI_SUCCESS;
}

HI_VOID SetHlsInfo(HI_HANDLE hPlayer, HI_CHAR *pszCmd)
{
    if (NULL == pszCmd)
        return;
    if (0 == strncmp("track", pszCmd, 5))
    {
        HI_S32 s32HlsStreamNum = 0;
        (HI_VOID)HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_HLS_STREAM_NUM, &s32HlsStreamNum);

        HI_S32 s32Track = -1;
        if (1 != sscanf(pszCmd, "track %d", &s32Track))
        {
            PRINTF("ERR: input err, example: sethls track 0 \n");
            return;
        }
        if (s32Track >= s32HlsStreamNum || s32Track < -1)
        {
            PRINTF("ERR: track id must from -1 and to streamnum %d !\n", s32HlsStreamNum);
            return;
        }
        HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_SET_HLS_STREAM, (HI_VOID*)s32Track);
    }
    else
    {
        PRINTF("ERR: not support commond1! \n");
    }
}
#if (USE_EXTERNAL_AVPLAY == 1)
HI_S32 openVidChannel(HI_HANDLE hAVPlay)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_WINDOW_ATTR_S stWinAttr;
    HI_HANDLE hWindow = HI_SVR_PLAYER_INVALID_HDL;
    HI_UNF_AVPLAY_OPEN_OPT_S stOpenOpt;

    memset(&stWinAttr, 1, sizeof(stWinAttr));
    stWinAttr.enDisp   = (HI_UNF_DISP_E)s_stParam.u32Display;
    stWinAttr.bVirtual = HI_FALSE;
    stWinAttr.stWinAspectAttr.enAspectCvrs        = HI_UNF_VO_ASPECT_CVRS_LETTERBOX;//HI_UNF_VO_ASPECT_CVRS_IGNORE;//HI_UNF_VO_ASPECT_CVRS_LETTERBOX
    stWinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    stWinAttr.bUseCropRect      = HI_FALSE;
    stWinAttr.stInputRect.s32X  = 0;
    stWinAttr.stInputRect.s32Y  = 0;
    stWinAttr.stInputRect.s32Width  = 0;
    stWinAttr.stInputRect.s32Height = 0;
    stWinAttr.stOutputRect.s32X = s_stParam.x;
    stWinAttr.stOutputRect.s32Y = s_stParam.y;
    stWinAttr.stOutputRect.s32Width  = s_stParam.w;
    stWinAttr.stOutputRect.s32Height = s_stParam.h;
    s32Ret = HI_UNF_VO_CreateWindow(&stWinAttr, &hWindow);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("create window fail, return %#x\n", s32Ret);
        return s32Ret;
    }

    stOpenOpt.enDecType  = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    stOpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    stOpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;
    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stOpenOpt);
    if (HI_SUCCESS != s32Ret)
    {
        HI_UNF_VO_DestroyWindow(hWindow);
        PRINTF("open vid channel failed, return %#x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_AttachWindow(hWindow, hAVPlay);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("attach window failed, return %#x\n", s32Ret);
        HI_UNF_AVPLAY_ChnClose(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_VO_DestroyWindow(hWindow);
        return s32Ret;
    }

    s32Ret = HI_UNF_VO_SetWindowEnable(hWindow, HI_TRUE);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("enable window failed, return %#x\n", s32Ret);
        HI_UNF_VO_DetachWindow(hWindow, hAVPlay);
        HI_UNF_AVPLAY_ChnClose(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
        HI_UNF_VO_DestroyWindow(hWindow);
        return s32Ret;
    }
    s_hWindow = hWindow;
    printf("open video channel success!\n");

    return HI_SUCCESS;
}

HI_S32 closeVidChannel(HI_HANDLE hAVPlay)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32RetTmp = HI_SUCCESS;

    if (s_hWindow != (HI_HANDLE)HI_SVR_PLAYER_INVALID_HDL)
    {
            s32RetTmp = HI_UNF_VO_SetWindowEnable(s_hWindow, HI_FALSE);
            if (HI_SUCCESS !=  s32RetTmp)
            {
                PRINTF("disable window failed, return %#x\n", s32RetTmp);
                s32Ret = s32RetTmp;
            }
            s32RetTmp = HI_UNF_VO_DetachWindow(s_hWindow, hAVPlay);
            if (HI_SUCCESS !=  s32RetTmp)
            {
                PRINTF("detach window failed, return %#x\n", s32RetTmp);
                s32Ret = s32RetTmp;
            }
            s32RetTmp = HI_UNF_VO_DestroyWindow(s_hWindow);
            if (HI_SUCCESS !=  s32RetTmp)
            {
                PRINTF("destroy window fail, return %#x\n", s32RetTmp);
                s32Ret = s32RetTmp;
            }
            s_hWindow = (HI_HANDLE)HI_SVR_PLAYER_INVALID_HDL;
    }

    s32RetTmp = HI_UNF_AVPLAY_ChnClose(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if (HI_SUCCESS !=  s32RetTmp)
    {
        PRINTF("close video channel failed, return %#x\n", s32RetTmp);
        s32Ret = s32RetTmp;
    }

    return s32Ret;
}

HI_S32 openAudChannel(HI_HANDLE hAVPlay)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_AUDIOTRACK_ATTR_S stTrackAttr;
    HI_UNF_SND_GAIN_ATTR_S stGain;
    HI_HANDLE hTrack = (HI_HANDLE)INVALID_TRACK_HDL;

    memset(&stTrackAttr, 0, sizeof(stTrackAttr));
    stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_MASTER;
    s32Ret = HI_UNF_SND_GetDefaultTrackAttr(stTrackAttr.enTrackType, &stTrackAttr);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("get default track attr fail ,return 0x%x\n", s32Ret);
        return s32Ret;
    }

    /*Warning:There must be only one master track on a sound device.*/
    stTrackAttr.enTrackType = HI_UNF_SND_TRACK_TYPE_MASTER;
    s32Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrack);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("create track fail ,return 0x%x\n", s32Ret);
        return s32Ret;
    }

    stGain.bLinearMode = HI_TRUE;
    stGain.s32Gain = s_stParam.u32MixHeight;
    s32Ret = HI_UNF_SND_SetTrackWeight(hTrack, &stGain);
    if (HI_SUCCESS == s32Ret)
    {
        PRINTF("set sound track mixer weight failed, return 0x%x\n", s32Ret);
    }

    s32Ret = HI_UNF_AVPLAY_ChnOpen(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("open audio channel fail, return %#x \n", s32Ret);
        HI_UNF_SND_DestroyTrack(hTrack);
        return s32Ret;
    }
    s32Ret = HI_UNF_SND_Attach(hTrack, hAVPlay);
    if (HI_SUCCESS != s32Ret)
    {
        HI_UNF_SND_DestroyTrack(hTrack);
        HI_UNF_AVPLAY_ChnClose(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
        PRINTF("attach audio track fail, return %#x \n", s32Ret);
        return s32Ret;
    }
    s_hAudioTrack = hTrack;
    printf("open audio channel success!\n");

    return HI_SUCCESS;
}

HI_S32 closeAudChannel(HI_HANDLE hAVPlay)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32 s32RetTmp = HI_SUCCESS;

    if (s_hAudioTrack != (HI_HANDLE)INVALID_TRACK_HDL)
    {
        s32RetTmp = HI_UNF_SND_Detach(s_hAudioTrack, hAVPlay);
        if (HI_SUCCESS != s32RetTmp)
        {
            s32Ret = s32RetTmp;
            PRINTF("detach audio track fail, return %#x \n", s32RetTmp);
        }
        s32RetTmp = HI_UNF_SND_DestroyTrack(s_hAudioTrack);
        if (HI_SUCCESS != s32RetTmp)
        {
            s32Ret = s32RetTmp;
            PRINTF("destroy audio track fail, return %#x \n", s32RetTmp);
        }

        s_hAudioTrack = (HI_HANDLE)INVALID_TRACK_HDL;
    }
    s32RetTmp = HI_UNF_AVPLAY_ChnClose(hAVPlay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    if (HI_SUCCESS != s32RetTmp)
    {
        s32Ret = s32RetTmp;
        PRINTF("close audio channel fail, return %#x \n", s32RetTmp);
    }

    return s32Ret;
}
#endif

HI_S32 main(HI_S32 argc, HI_CHAR **argv)
{
    HI_S32 s32Ret = 0;
    HI_HANDLE hPlayer = (HI_HANDLE)NULL, hSo = (HI_HANDLE)NULL, hAVPlay = HI_SVR_PLAYER_INVALID_HDL;
    HI_FORMAT_FILE_INFO_S *pstFileInfo;
    HI_SVR_PLAYER_INFO_S stPlayerInfo;
    HI_SVR_PLAYER_STREAMID_S stStreamId;
    HI_SVR_PLAYER_MEDIA_S stMedia;
    HI_CHAR aszInputCmd[CMD_LEN];
    HI_FORMAT_BUFFER_CONFIG_S stBufConfig;
    HI_UNF_ENC_FMT_E            enFormat = HI_UNF_ENC_FMT_720P_50;
 #if (USE_EXTERNAL_AVPLAY == 1)
    HI_UNF_AVPLAY_ATTR_S stAVPlayAttr;
#endif

    HI_S32 k = 0;

    if (argc < 2)
    {
        PRINTF("Usage: sample_localplay file                               \n"
               "                                                           \n"
               "          ------- select operation -------                 \n"
               "                                                           \n"
               "  -s subtitlefile1,subtitlefile2,... : input subtitle file \n"
               "  --drm trans=1 mimetype=xx DrmPath=./pdrd,LocalStore=data.localstore\n"
               "  --drm InstallDrmEngine file.so \n"
               "  -f videoFormat \n"
               "  --hls_fast_start"
               "\n");
        return HI_FAILURE;
    }

    memset(&stMedia, 0, sizeof(stMedia));

    sprintf(stMedia.aszUrl, "%s", argv[1]);
    HI_U32 uHlsStartMode = 0;
    for (k = 2; k < argc; k++)
    {
        if (!strcasecmp(argv[k], "-s"))
        {
            /* Specify the external subtitle */
            parserSubFile(argv[k + 1], &stMedia);
            k += 1;
        }
        else if (!strcasecmp(argv[k], "-f"))
        {
            /* video fmt */
            s_noPrintInHdmiATC = HI_TRUE;
            enFormat = stringToUnfFmt(argv[k + 1]);
            k += 1;
        }
#ifdef DRM_SUPPORT
        else if (!strcasecmp(argv[k], "--drm"))
        {
            /*Perform DRM operation before play*/
            drm_get_handle();//initialize drm handle
            int j = k + 1;
            char buf[2048] = "";
            for (; j < argc && j < k + 5; j++)
            {
                strcat(buf, argv[j]);
                strcat(buf, " ");
            }
            drm_cmd(buf);
            k += 1;
        }
#endif
        else if (!strcasecmp(argv[k], "--hls_fast_start"))
        {
            uHlsStartMode = 1;
            PRINTF("hls start mode is %d", uHlsStartMode);
        }
    }

    /* Gaplessplay function add code */
    HI_S32 ifsuccess = 0;
    s32Ret = playM3U9Main(argv[1]);

    if (HI_SUCCESS == s32Ret)
    {
        memset(stMedia.aszUrl, 0, sizeof(stMedia.aszUrl));
        sprintf(stMedia.aszUrl, "%s", "/data/01.m3u9");
        ifsuccess++;
    }
    else
    {
        memset(stMedia.aszUrl, 0, sizeof(stMedia.aszUrl));
        sprintf(stMedia.aszUrl, "%s", argv[1]);
    }
    sprintf(s_aszUrl, "%s", argv[1]);

    if (!ifsuccess)
    {
        HI_CHAR *p = strrchr(stMedia.aszUrl,'.');

        if (NULL != p && !strcasecmp(strrchr(stMedia.aszUrl,'.'),".ISO"))
        {
            s32Ret = do_mountiso(stMedia.aszUrl);

            if (HI_SUCCESS != s32Ret)
            {
                return HI_FAILURE;
            }

            HI_CHAR *dir = "/mnt/iso/";
            s32Ret = playM3U9Main(dir);

            if (HI_SUCCESS == s32Ret)
            {
                memset(stMedia.aszUrl, 0, sizeof(stMedia.aszUrl));
                sprintf(stMedia.aszUrl, "%s", "/data/01.m3u9");
                ifsuccess++;
            }

            if (HI_SUCCESS != s32Ret)    /*if get file dir doesn't success,change back to origin URL*/
            {
                memset(stMedia.aszUrl, 0, sizeof(stMedia.aszUrl));
                sprintf(stMedia.aszUrl, "%s", argv[1]);
            }
        }
    }

    ifsuccess = 0;

    s32Ret = deviceInit(enFormat);
    higoInit();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: local file play, device init fail! \n");
        goto LEAVE;
    }

#if defined (CHARSET_SUPPORT)
    s32Ret = HI_CHARSET_Init();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("\e[31m ERR: charset init failed \e[0m \n");
    }

    s32Ret = HI_CHARSET_RegisterDynamic("libhi_charset.so");

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("\e[31m ERR: register charset libcharset.so fail, ret = 0x%x \e[0m \n", s32Ret);
    }
#endif

    /**<This piece of code is used to simulate switching from dvb ts playing to hiplayer playing.
      when creating hiplayer with the avplay handle which was created out of hiplayer, hiplayer will not created
      avplay by itself anymore.Setting the marco to 0 and s_stParam.hAVPlayer to HI_SVR_PLAYER_INVALID_HDL,
      hiplayer will created avplay internal by itself.
    */
    /* CNcomment:�öδ�������ģ���dvb ts����ģʽ�л���HiPlayer���ţ����ⲿ������avplay������ݸ�
       HiPlayer��HiPlayer�ڲ����ٴ����µ�avplay������رոöδ��룬s_stParam.hAVPlayer
       ����ֵ����ΪHI_SVR_PLAYER_INVALID_HDL��HiPlayer�ڲ��Լ�����avplay */

#if (USE_EXTERNAL_AVPLAY == 1)
    /**<Use external created avplay handle to create hiplayer.You must do below things all by yourself.
      1-create the avplay;
      2-create the track and adjust the volume;
      3-create the window and adjust it's size and position.
      4-open the video channel and audio channel;
      5-attach the track/window to avplay,enable the window;
      6-create hiplayer with the avplay handle created in step 1.
      when switching with dvb play:
      dvb->hiplayer: stop avplay, set s_stParam.hAVPlayer's value with the avplay handle,and then creat hiplayer
          with HI_SVR_PLAYER_Create.
      hiplayer->dvb:destroy hiplayer with HI_SVR_PLAYER_Destroy,hiplay may close the av channel, then dvb need to
          reopen it.
    */
    /* CNcomment:ʹ���ⲿ������avplay�������avplay�����Ѿ��󶨺�window, sound�豸�����轫windowλ�á���С���úã�
       sound������С���úã�HiPlayer�ڲ���window,sound�����κβ�����
       a��dvb -> HiPlayer: ֹͣavplay����avplay�������s_stParam.hAVPlayer������HI_SVR_PLAYER_Create����HiPlayer��
          HiPlayer�Ὣavplayģʽ�л�����Ҫ��ģʽ�����һ����¿�������Ƶͨ����

       b��HiPlayer -> dvb: ����HI_SVR_PLAYER_Destroy�ӿ�����HiPlayer��HiPlayer��رյ�����Ƶͨ����dvb�����µ���
          HI_UNF_AVPLAY_ChnOpen�ӿڿ�������Ƶͨ����
    */

    s32Ret = HI_UNF_AVPLAY_GetDefaultConfig(&stAVPlayAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    stAVPlayAttr.stStreamAttr.u32VidBufSize = (20 * 1024 * 1024);
    stAVPlayAttr.stStreamAttr.u32AudBufSize = (4 *1024 * 1024);
    s32Ret |= HI_UNF_AVPLAY_Create(&stAVPlayAttr, &hAVPlay);
    if (HI_SUCCESS == s32Ret)
    {
        s32Ret = openVidChannel(hAVPlay);
        if (HI_SUCCESS != openAudChannel(hAVPlay) &&
            HI_SUCCESS != s32Ret)
        {
            PRINTF("open video channel and audio channel failed, use internal avplay!\n");
            HI_UNF_AVPLAY_Destroy(hAVPlay);
            hAVPlay = HI_SVR_PLAYER_INVALID_HDL;
        }
    }
    else
    {
        PRINTF("create avplay fail! \n");
        hAVPlay = HI_SVR_PLAYER_INVALID_HDL;
    }
#else
    hAVPlay = HI_SVR_PLAYER_INVALID_HDL;
#endif

    if ((HI_HANDLE)HI_SVR_PLAYER_INVALID_HDL != hAVPlay)
    {
        PRINTF("use external avplay!\n");
    }

    s32Ret = HI_SVR_PLAYER_Init();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: player init fail, ret = 0x%x\n", s32Ret);
        goto LEAVE;
    }
    HI_FORMAT_LIB_VERSION_S stPlayerVersion;

    memset(&stPlayerVersion, 0, sizeof(stPlayerVersion));
    HI_SVR_PLAYER_GetVersion(&stPlayerVersion);
    printf("HiPlayer V%u.%u.%u.%u\n",
            stPlayerVersion.u8VersionMajor,
            stPlayerVersion.u8VersionMinor,
            stPlayerVersion.u8Revision,
            stPlayerVersion.u8Step);

    /* Regist private protocol library  */
    s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libprivateprotocol.so");

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: register file parser libprivateprotocol.so fail, ret = 0x%x\n", s32Ret);
    }

    /* Regist file demuxers */
    s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libformat.so");
    (HI_VOID)HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libffmpegformat.so");

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: register file parser libformat.so fail, ret = 0x%x\n", s32Ret);
    }

    s_stParam.hAVPlayer = hAVPlay;
    s_stParam.hDRMClient = (HI_HANDLE)NULL;
#ifdef DRM_SUPPORT
    s_stParam.hDRMClient = (HI_HANDLE)drm_get_handle();
    PRINTF("drm handle created:%#x\n", s_stParam.hDRMClient);
#endif
    s32Ret = HI_SVR_PLAYER_Create(&s_stParam, &hPlayer);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: player open fail, ret = 0x%x\n", s32Ret);
        goto LEAVE;
    }

#if defined (CHARSET_SUPPORT)
    HI_S32 s32CodeType = HI_CHARSET_CODETYPE_UTF8;
    extern HI_CHARSET_FUN_S g_stCharsetMgr_s;

    s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_SET_CHARSETMGR_FUNC, &g_stCharsetMgr_s);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: HI_SVR_PLAYER_Invoke set charsetMgr failed\n");
    }

    /* Convert subtitle encoding to the utf8 encoding, subOndraw output must use utf8 character set. */
    s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_SET_DEST_CODETYPE, &s32CodeType);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: HI_SVR_PLAYER_Invoke Send Dest CodeType failed\n");
    }
#endif

    s32Ret = HI_SVR_PLAYER_RegCallback(hPlayer, eventCallBack);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: register event callback function fail, ret = 0x%x\n", s32Ret);
    }

    /* Fast start hls */
    if (1 == uHlsStartMode)
        HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_SET_HLS_START_MODE, (HI_VOID*)HI_FORMAT_HLS_MODE_FAST);

    stMedia.u32UserData = 0;

    HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_SET_LOG_LEVEL, (HI_VOID *)HI_FORMAT_LOG_QUITE);
    HI_SVR_PLAYER_EnableDbg(HI_FALSE);

    s32Ret = HI_SVR_PLAYER_SetMedia(hPlayer, HI_SVR_PLAYER_MEDIA_STREAMFILE, &stMedia);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: open file fail, ret = %d!\n", s32Ret);
        goto LEAVE;
    }

    HI_S32 s32HlsStreamNum = 0;
    HI_FORMAT_HLS_STREAM_INFO_S stStreamInfo;
    s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_HLS_STREAM_NUM, &s32HlsStreamNum);

    if (HI_SUCCESS != s32Ret)
        PRINTF("ERR: get hls stream num fail, ret = 0x%x!\n", s32Ret);
    else
        PRINTF("get hls stream num = %d\n", s32HlsStreamNum);

    /* Display the hls bandwidth stream info */
    for (k = 0; k < s32HlsStreamNum; k++)
    {
        stStreamInfo.stream_nb = k;
        s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_HLS_STREAM_INFO, &stStreamInfo);

        if (HI_SUCCESS != s32Ret)
            PRINTF("ERR: get %d hls stream info fail, ret = 0x%x!\n", k, s32Ret);
        PRINTF("\nHls stream number is: %d \n", stStreamInfo.stream_nb);
        PRINTF("URL: %s \n", stStreamInfo.url);
        PRINTF("BandWidth: %lld \n", stStreamInfo.bandwidth);
        PRINTF("SegMentNum: %d \n", stStreamInfo.hls_segment_nb);
    }
    HI_SVR_PLAYER_METADATA_S stMetaData;

    memset(&stMetaData, 0, sizeof(HI_SVR_PLAYER_METADATA_S));

    s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_METADATA, &stMetaData);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: get metadata fail!\n");
    }
    else
    {
        PRINTF("get metadata success!\n");
        HI_SVR_META_PRINT(&stMetaData);
    }

    /*Check drm status*/
#ifdef DRM_SUPPORT
    HI_CHAR* pszDrmMimeType = NULL;
    for (k = 0; k < stMetaData.u32KvpUsedNum; k++)
    {
        if (!strcasecmp(stMetaData.pstKvp[k].pszKey, "DRM_MIME_TYPE"))
        {
            pszDrmMimeType = (HI_CHAR*)stMetaData.pstKvp[k].unValue.pszValue;
            break;
        }
    }
    if (pszDrmMimeType)
    {
        /*DRM opened, check DRM right status*/
        s32Ret = drm_check_right_status(stMedia.aszUrl, pszDrmMimeType);
        while (s32Ret > 0)
        {
            s32Ret = drm_acquire_right_progress(pszDrmMimeType);
            if (s32Ret == 100)
            {
                PRINTF("acquiring right done\n");
                break;
            }
            PRINTF("acquiring right progress:%d%%\n", s32Ret);
            sleep(1);
        }
        if (s32Ret < 0)
        {
            PRINTF("DRM right invalid, can't play this file, exit now!\n");
            exit(0);
        }
    }
#endif

    /* Set buffer config */
    memset(&stBufConfig, 0, sizeof(HI_FORMAT_BUFFER_CONFIG_S));
    stBufConfig.eType = HI_FORMAT_BUFFER_CONFIG_SIZE;
    s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_BUFFER_CONFIG, &stBufConfig);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: HI_SVR_PLAYER_Invoke function fail, ret = 0x%x\n", s32Ret);
    }

    PRINTF("BufferConfig:type(%d)\n",stBufConfig.eType);
    PRINTF("s64EventStart:%lld\n", stBufConfig.s64EventStart);
    PRINTF("s64EventEnough:%lld\n", stBufConfig.s64EventEnough);
    PRINTF("s64Total:%lld\n", stBufConfig.s64Total);
    PRINTF("s64TimeOut:%lld\n", stBufConfig.s64TimeOut);

    s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

    if (HI_SUCCESS == s32Ret)
    {
        HI_SVR_PLAYER_STREAMID_S stStreamId1 = {0};

        outFileInfo(pstFileInfo);

        s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId1);

        if (HI_SUCCESS == s32Ret &&
            pstFileInfo->u32ProgramNum > 0)
        {
            if (pstFileInfo->pastProgramInfo[stStreamId1.u16ProgramId].u32VidStreamNum > 0 &&
                pstFileInfo->pastProgramInfo[stStreamId1.u16ProgramId].pastVidStream[stStreamId1.u16VidStreamId].u32Format
                == HI_FORMAT_VIDEO_MVC)
            {
                setVideoMode(hPlayer, HI_UNF_DISP_3D_FRAME_PACKING);
            }

            if (pstFileInfo->pastProgramInfo[stStreamId1.u16ProgramId].u32SubStreamNum > 0)
            {
                if (pstFileInfo->pastProgramInfo[stStreamId1.u16ProgramId].pastSubStream[stStreamId1.u16SubStreamId].u32Format ==
                        HI_FORMAT_SUBTITLE_HDMV_PGS)
                {
                    s_bPgs = HI_TRUE;
                }
                else
                {
                    s_s64CurPgsClearTime = -1;
                    s_bPgs = HI_FALSE;
                }
            }
        }
    }
    else
    {
        PRINTF("ERR: get file info fail!\n");
    }

    /* Test invoke */
    TEST_PROTOCOL_ARGS stArgs;
    stArgs.s32Cmd = TEST_CMD_TYPE_CALLBACK;
    stArgs.args = 0;
    stArgs.pfnCallback = TestCallBack;

    s32Ret |= HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_PROTOCOL_USER, &stArgs);

    /* Regist ondraw and onclear function after reopen file */
    s32Ret |= HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_SO_HDL, &hSo);
    s32Ret |= HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_AVPLAYER_HDL, &hAVPlay);
    s32Ret |= HI_UNF_SO_RegOnDrawCb(hSo, subOndraw, subOnclear, hAVPlay);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("ERR: set subtitle draw function fail!\n");
    }

    //PRINTF(HELP_INFO);

    s32Ret = HI_SVR_PLAYER_Play(hPlayer);

    if (HI_SUCCESS != s32Ret)
        PRINTF("ERR: play fail, ret = 0x%x\n", s32Ret);

    while (1)
    {
        SAMPLE_GET_INPUTCMD(aszInputCmd);

        PRINTF(">>> [input cmd] %s \n", aszInputCmd);

        if ('h' == aszInputCmd[0])
        {
            PRINTF(HELP_INFO);
        }
        else if (0 == strncmp("play", aszInputCmd, 4))
        {
            /*rtsp/mms/rtmp need to redo setting media when stop->play/replay*/
            if (strstr(s_aszUrl, "rtsp") ||
                strstr(s_aszUrl, "mms")  ||
                strstr(s_aszUrl, "rtmp"))
            {
                s32Ret = setMedia(hPlayer, s_aszUrl);
                if (HI_SUCCESS != s32Ret)
                {
                    continue;
                }
            }

            s32Ret = HI_SVR_PLAYER_Play(hPlayer);

            if (HI_SUCCESS != s32Ret)
                PRINTF("ERR: play fail, ret = 0x%x\n", s32Ret);
        }
        else if (0 == strncmp("pause", aszInputCmd, 5))
        {
            s32Ret = HI_SVR_PLAYER_Pause(hPlayer);

            if (HI_SUCCESS != s32Ret)
                PRINTF("ERR: pause fail, ret = 0x%x\n", s32Ret);
        }
        else if (0 == strncmp("seek", aszInputCmd, 4))
        {
            HI_S64 s64SeekTime = 0;

            if (1 != sscanf(aszInputCmd, "seek %lld", &s64SeekTime))
            {
                PRINTF("ERR: not input seek time, example: seek 8000!\n");
                continue;
            }

            s32Ret = HI_SVR_PLAYER_Seek(hPlayer, s64SeekTime);

            if (HI_SUCCESS != s32Ret)
                PRINTF("ERR: seek fail, ret = 0x%x\n", s32Ret);
            else
                clearSubtitle();
        }
        else if(0 == strncmp("posseek",aszInputCmd,7))
        {
            HI_S64 s64SeekPos = 0;
            if (1 != sscanf(aszInputCmd, "posseek %lld", &s64SeekPos))
            {
                PRINTF("ERR: not input seek position, example: pos 8000!\n");
                continue;
            }

            s32Ret = HI_SVR_PLAYER_SeekPos(hPlayer, s64SeekPos);

            if (HI_SUCCESS != s32Ret)
                PRINTF("ERR: seek pos fail, ret = 0x%x\n", s32Ret);
        }
        else if (0 == strncmp("metadata", aszInputCmd, 8))
        {
            HI_SVR_PLAYER_METADATA_S *pstMetadata = NULL;

            pstMetadata = HI_SVR_META_Create();
            s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_GET_METADATA, pstMetadata);

            if (HI_FAILURE == s32Ret)
            {
                PRINTF("Get Metadata fail!\n");
                continue;
            }

            HI_SVR_META_PRINT(pstMetadata);
            HI_SVR_META_Free(&pstMetadata);
        }
        else if (0 == strncmp("stop", aszInputCmd, 4))
        {
            s32Ret = HI_SVR_PLAYER_Stop(hPlayer);

            if (HI_SUCCESS != s32Ret)
                PRINTF("ERR: stop fail, ret = 0x%x\n", s32Ret);
            else
                clearSubtitle();
        }
        else if (0 == strncmp("resume", aszInputCmd, 6))
        {
            s32Ret = HI_SVR_PLAYER_Resume(hPlayer);

            if (HI_SUCCESS != s32Ret)
                PRINTF("ERR: resume fail, ret = 0x%x\n", s32Ret);
        }
        else if (0 == strncmp("bw", aszInputCmd, 2))
        {
            HI_S32 s32Speed = 0;

            if (1 != sscanf(aszInputCmd, "bw %d", &s32Speed))
            {
                PRINTF("ERR: not input tplay speed, example: bw 2!\n");
                continue;
            }

            s32Speed *= HI_SVR_PLAYER_PLAY_SPEED_NORMAL;

            if (s32Speed > HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_FORWARD)
            {
                PRINTF("ERR: not support tplay speed!\n");
                continue;
            }

            s32Speed = 0 - s32Speed;

            PRINTF("backward speed = %d \n", s32Speed);

            s32Ret = HI_SVR_PLAYER_TPlay(hPlayer, s32Speed);

            if (HI_SUCCESS == s32Ret)
                clearSubtitle();
            else
                PRINTF("ERR: tplay fail, ret = 0x%x\n", s32Ret);
        }
        else if (0 == strncmp("ff", aszInputCmd, 2))
        {
            HI_S32 s32Speed = 0;

            if (1 != sscanf(aszInputCmd, "ff %d", &s32Speed))
            {
                PRINTF("ERR: not input tplay speed, example: ff 4!\n");
                continue;
            }

            s32Speed *= HI_SVR_PLAYER_PLAY_SPEED_NORMAL;

            if (s32Speed > HI_SVR_PLAYER_PLAY_SPEED_32X_FAST_FORWARD)
            {
                PRINTF("ERR: not support tplay speed!\n");
                continue;
            }

            PRINTF("forward speed = %d \n", s32Speed);

            s32Ret = HI_SVR_PLAYER_TPlay(hPlayer, s32Speed);

            if (HI_SUCCESS == s32Ret)
                clearSubtitle();
            else
                PRINTF("ERR: tplay fail, ret = 0x%x\n", s32Ret);
        }
        else if (0 == strncmp("info", aszInputCmd, 4))
        {
            /* Output player information */

            s32Ret = HI_SVR_PLAYER_GetPlayerInfo(hPlayer, &stPlayerInfo);

            if (HI_SUCCESS != s32Ret)
            {
                PRINTF("ERR: HI_SVR_PLAYER_GetPlayerInfo fail!\n");
                continue;
            }

            PRINTF("PLAYER INFO: \n");
            PRINTF("  Cur progress:   %d \n", stPlayerInfo.u32Progress);
            PRINTF("  Time played:  %lld:%lld:%lld, Total time: %lld:%lld:%lld \n",
                stPlayerInfo.u64TimePlayed / (1000 * 3600),
                (stPlayerInfo.u64TimePlayed % (1000 * 3600)) / (1000 * 60),
                ((stPlayerInfo.u64TimePlayed % (1000 * 3600)) % (1000 * 60)) / 1000,
                pstFileInfo->s64Duration / (1000 * 3600),
                (pstFileInfo->s64Duration % (1000 * 3600)) / (1000 * 60),
                ((pstFileInfo->s64Duration % (1000 * 3600)) % (1000 * 60)) / 1000);
            PRINTF("  Speed:          %d \n", stPlayerInfo.s32Speed);
            PRINTF("  Status:         %d \n", stPlayerInfo.eStatus);

            s32Ret = HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamId);
            PRINTF("  StreamId: program id(%d), video id(%d), audio id(%d), subtitle id(%d) \n",
                stStreamId.u16ProgramId, stStreamId.u16VidStreamId, stStreamId.u16AudStreamId, stStreamId.u16SubStreamId);
        }
        else if (0 == strncmp("set ", aszInputCmd, 4))
        {
            setAttr(hPlayer, aszInputCmd + 4);
        }
        else if (0 == strncmp("get ", aszInputCmd, 4))
        {
            getAttr(hPlayer, aszInputCmd + 4);
        }
        else if (0 == strncmp("dbg", aszInputCmd, 3))
        {
            HI_S32 s32Dbg = 0;

            if (1 != sscanf(aszInputCmd, "dbg %d", &s32Dbg))
            {
                PRINTF("ERR: not dbg enable balue, example: dbg 1!\n");
                continue;
            }

            HI_SVR_PLAYER_EnableDbg((HI_BOOL)s32Dbg);
        }
        else if (0 == strncmp("open", aszInputCmd, 4))
        {
            HI_S32 s32Len;
            HI_CHAR aszUrl[HI_FORMAT_MAX_URL_LEN];
            HI_SVR_PLAYER_STREAMID_S stStreamIdx;
            /* Reopen a file */
            s32Ret = HI_SUCCESS;
            (HI_VOID)HI_GO_FillRect(s_hLayerSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);
            (HI_VOID)HI_GO_RefreshLayer(s_hLayer, NULL);

            s32Len = strlen(aszInputCmd + 5);
            if (s32Len >= (HI_S32)sizeof(aszUrl))
            {
                continue;
            }

            memcpy(aszUrl, aszInputCmd + 5, s32Len - 1);
            aszUrl[s32Len - 1] = 0;
            s32Ret = setMedia(hPlayer, aszUrl);

            if (HI_SUCCESS != s32Ret)
            {
                continue;
            }

            s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

            if (HI_SUCCESS == s32Ret)
            {
                outFileInfo(pstFileInfo);
                if (pstFileInfo->u32ProgramNum > 0 &&
                    HI_SVR_PLAYER_GetParam(hPlayer, HI_SVR_PLAYER_ATTR_STREAMID, (HI_VOID*)&stStreamIdx) == HI_SUCCESS &&
                    pstFileInfo->pastProgramInfo[stStreamIdx.u16ProgramId].u32VidStreamNum > 0 &&
                    pstFileInfo->pastProgramInfo[stStreamIdx.u16ProgramId].pastVidStream[stStreamIdx.u16VidStreamId].u32Format
                    == HI_FORMAT_VIDEO_MVC)
                {
                    setVideoMode(hPlayer, HI_UNF_DISP_3D_FRAME_PACKING);
                }
            }
            else
            {
                PRINTF("ERR: get file info fail!\n");
            }
        }
        else if (0 == strncmp("close", aszInputCmd, 4))
        {
            s32Ret = HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_PRE_CLOSE_FILE, NULL);
            if (HI_SUCCESS != s32Ret)
            {
                PRINTF("ERR: HI_FORMAT_INVOKE_PRE_CLOSE_FILE fail!\n");
            }
        }
        else if (0 == strncmp("sub", aszInputCmd, 3))
        {
            /* Set an external subtitle file in playing state */

            s32Ret = HI_SUCCESS;
            memset(&stMedia, 0, sizeof(stMedia));
            memcpy(stMedia.aszExtSubUrl[0], aszInputCmd + 4, strlen(aszInputCmd + 4) - 1);
            stMedia.u32ExtSubNum = 1;

            PRINTF("### open external sub file is %s \n", stMedia.aszExtSubUrl[0]);

            s32Ret = HI_SVR_PLAYER_SetMedia(hPlayer, HI_SVR_PLAYER_MEDIA_SUBTITLE, &stMedia);

            if (HI_SUCCESS != s32Ret)
            {
                PRINTF("ERR: HI_SVR_PLAYER_SetMedia err, ret = 0x%x!\n", s32Ret);
                continue;
            }

            s32Ret = HI_SVR_PLAYER_GetFileInfo(hPlayer, &pstFileInfo);

            if (HI_SUCCESS == s32Ret)
            {
                outFileInfo(pstFileInfo);
            }
            else
            {
                PRINTF("ERR: get file info fail!\n");
            }
        }
        else if (0 == strncmp("q", aszInputCmd, 1))
        {
            if (s_s32ThreadEnd == HI_FAILURE)
            {
                s_s32ThreadExit = HI_SUCCESS;
                HI_SVR_PLAYER_Invoke(hPlayer, HI_FORMAT_INVOKE_PRE_CLOSE_FILE, NULL);
                pthread_join(s_hThread, NULL);
            }
            break;
        }
        else if (0 == strncmp("sethls ", aszInputCmd, 7))
        {
            SetHlsInfo(hPlayer, aszInputCmd + 7);
        }
#ifdef DRM_SUPPORT
        else if (0 == strncmp("drm", aszInputCmd, 3))
        {
            drm_cmd(aszInputCmd + 4);
        }
#endif
        else
        {
            PRINTF("ERR: not support operation!\n");
        }
    }

LEAVE:
    s32Ret = HI_SVR_PLAYER_Destroy(hPlayer);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("### HI_SVR_PLAYER_Destroy err! \n");
    }

#if (USE_EXTERNAL_AVPLAY == 1)
    if (hAVPlay != HI_SVR_PLAYER_INVALID_HDL)
    {
        closeVidChannel(hAVPlay);
        closeAudChannel(hAVPlay);
        HI_UNF_AVPLAY_Destroy(hAVPlay);
        hAVPlay = HI_SVR_PLAYER_INVALID_HDL;
    }
#endif

    s32Ret = HI_SVR_PLAYER_UnRegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, NULL);

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("### HI_SVR_PLAYER_UnRegisterDynamic err! \n");
    }

    /* You must call HI_SVR_PLAYER_Destroy function to release the player resource before call the deinit function. */

    s32Ret = HI_SVR_PLAYER_Deinit();

    if (HI_SUCCESS != s32Ret)
    {
        PRINTF("### HI_SVR_PLAYER_Deinit err! \n");
    }

    if (NULL != s_pstParseHand)
    {
        HI_SO_SUBTITLE_ASS_DeinitParseHand(s_pstParseHand);
        s_pstParseHand = NULL;
    }

#if defined (CHARSET_SUPPORT)
    HI_CHARSET_Deinit();
#endif

    if (HIGO_INVALID_HANDLE != s_hLayer)
    {
        HI_GO_DestroyLayer(s_hLayer);
        s_hLayer = HIGO_INVALID_HANDLE;
    }

    if (HIGO_INVALID_HANDLE != s_hFont)
    {
        HI_GO_DestroyText(s_hFont);
        s_hFont = HIGO_INVALID_HANDLE;
    }

    s_hLayerSurface = HIGO_INVALID_HANDLE;

    (HI_VOID)HI_GO_Deinit();
    deviceDeinit();

#ifdef DRM_SUPPORT
    drm_clear_handle();
#endif

    return HI_SUCCESS;
}

