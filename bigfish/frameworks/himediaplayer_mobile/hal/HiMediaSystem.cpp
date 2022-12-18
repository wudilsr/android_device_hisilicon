#define LOG_NDEBUG 0
#define LOG_TAG "HiMediaSystem"
#include <utils/Log.h>
#include "HiMediaSystem.h"
#include "hi_audio_codec.h"
#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_demux.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_svr_player.h"
#include "hi_svr_format.h"
#include "hi_unf_so.h"
#include "hi_svr_assa.h"
#include "hi_svr_charset.h"
#include "hi_svr_charset_norm.h"
#include "hi_unf_subt.h"
#include "HiMediaDefine.h"
#include <cutils/properties.h>


static int HiMediaSystem_VO_Init(HI_UNF_VO_DEV_MODE_E enDevMode)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = HI_UNF_VO_Init(enDevMode);
    if (s32Ret != HI_SUCCESS)
    {
        LOGE("call HI_UNF_VO_Init failed.");
        return s32Ret;
    }
    return HI_SUCCESS;
}

static int HiMediaSystem_Snd_Init(HI_VOID)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_SND_ATTR_S stAttr;

    Ret = HI_UNF_SND_Init();
    if (Ret != HI_SUCCESS)
    {
        LOGE("call HI_UNF_SND_Init failed.\n");
        return Ret;
    }
    Ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        LOGE("call HI_UNF_SND_GetDefaultOpenAttr failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_Open(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        LOGE("call HI_UNF_SND_Open failed.\n");
        return Ret;
    }
    return HI_SUCCESS;
}

static int HiMediaSystem_Snd_DeInit(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (s32Ret != HI_SUCCESS)
    {
        LOGE("call HI_UNF_SND_Close failed.");
        return s32Ret;
    }

    s32Ret = HI_UNF_SND_DeInit();
    if (s32Ret != HI_SUCCESS)
    {
        LOGE("call HI_UNF_SND_DeInit failed.");
        return s32Ret;
    }

    return HI_SUCCESS;
}

static int HiMediaSystem_VO_DeInit(HI_VOID)
{
    HI_S32 Ret = HI_FAILURE;

    Ret = HI_UNF_VO_DeInit();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_VO_DeInit failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

static int HiMediaSystem_AVPlay_RegADecLib(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;

    s32Ret  = HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.MP3.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DOLBYPLUS.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTSHD.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTSM6.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.MP2.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AAC.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DRA.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DOLBYTRUEHD.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.TRUEHDPASSTHROUGH.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AMRNB.codec.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AMRWB.codec.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.WMA.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.COOK.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.BLURAYLPCM.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.FFMPEG_ADEC.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.PCM.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.AC3PASSTHROUGH.decode.so");
    s32Ret |= HI_UNF_AVPLAY_RegisterAcodecLib("libHA.AUDIO.DTSPASSTHROUGH.decode.so");

    if (s32Ret != HI_SUCCESS)
    {
        LOGE("!!! some audio codec NOT found. you may NOT able to decode some audio type.");
    }

    return HI_SUCCESS;
}

static int HiMediaSystem_AVPlay_RegVDecLib(HI_VOID)
{
    HI_S32 s32Ret = HI_SUCCESS;
    s32Ret = HI_UNF_AVPLAY_RegisterVcodecLib("libHV.VIDEO.FFMPEG_VDEC.decode.so");
    if (s32Ret != HI_SUCCESS)
    {
        LOGE("libHV.VIDEO.FFMPEG_VDEC.decode.so reg fail");
    }
    return HI_SUCCESS;
}

namespace android
{
    HI_S32 HiMediaSystem::mPlayerInstCount  = 0;
    HI_S32 HiMediaSystem::mCharsetInstCount = 0;
    HI_S32 HiMediaSystem::mDeviceInstCount = 0;
    Mutex HiMediaSystem::mInstMutex;
    Mutex HiMediaSystem::mPlayerInstMutex;
    Mutex HiMediaSystem::mCharsetInstMutex;
    Mutex HiMediaSystem::mDeviceInstMutex;

    //recored all install's fq size
    static const HI_S32 max_aud_num = 16;
    static const HI_S32 fq_deault_size = 1280;
    static struct
    {
        HI_S32 handle;
        HI_S32 size;
    } s_fq_size[max_aud_num] = {0};

    /* static */
    int HiMediaSystem::initMediaDevice()
    {
        LOGV("%s IN", __FUNCTION__);

        HI_S32 s32Ret;
        HI_SYS_VERSION_S attr;

        s32Ret = HI_SYS_Init();
        if (HI_SUCCESS != s32Ret)
        {
            LOGE("ERR: HI_SYS_Init fail! ");
            return s32Ret;
        }

        s32Ret = HI_UNF_SO_Init();
        if (HI_SUCCESS != s32Ret)
        {
            LOGE("ERR: HI_UNF_SO_Init fail! ");
            return s32Ret;
        }

        s32Ret = HI_UNF_SUBT_Init();
        if (HI_SUCCESS != s32Ret)
        {
            LOGE("ERR: HI_UNF_SUBT_Init() fail! ");
            return s32Ret;
        }

        /* Set VO to Normal, fix bugs of [h263aac.3g2] vfmw release buffer failed after VO release 3 times */
        s32Ret = HiMediaSystem_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);

        if (s32Ret != HI_SUCCESS)
        {
            LOGE("ERR: HiMediaSystem_VO_Init failed.");
            return s32Ret;
        }

        s32Ret = HiMediaSystem_Snd_Init();
        if (s32Ret != HI_SUCCESS)
        {
            LOGE("ERR: HiMediaSystem_Snd_Init failed.");
            return s32Ret;
        }

        s32Ret = HiMediaSystem_AVPlay_RegADecLib();
        if (s32Ret != HI_SUCCESS)
        {
            LOGE("ERR: HiMediaSystem_AVPlay_RegADecLib failed.");
            return s32Ret;
        }

        s32Ret = HiMediaSystem_AVPlay_RegVDecLib();
        if (s32Ret != HI_SUCCESS)
        {
            LOGE("ERR: HiMediaSystem_AVPlay_RegVDecLib failed.");
            return s32Ret;
        }

        s32Ret = HI_UNF_AVPLAY_Init();
        if (s32Ret != HI_SUCCESS)
        {
            LOGE("ERR: HI_UNF_AVPLAY_Init failed.");
            return s32Ret;
        }

        return s32Ret;
    }

    /* static */
    int HiMediaSystem::destroyMediaDevice()
    {
        LOGV("HiMediaSystem::destroyMediaDevice()");
        HI_S32 s32Ret = HI_SUCCESS;
        if (HI_SUCCESS != HI_UNF_AVPLAY_DeInit())
        {
            LOGE("ERR: HI_UNF_AVPLAY_DeInit fail, return UNKNOWN_ERROR!");
            return UNKNOWN_ERROR;
        }

        if (HI_SUCCESS != HI_UNF_SUBT_DeInit())
        {
            LOGE("ERR: HI_UNF_SUBT_DeInit fail!");
        }

        if (HI_SUCCESS != HI_UNF_SO_DeInit())
        {
            LOGE("ERR: HI_UNF_SO_DeInit fail!");
        }

        if (HI_SUCCESS != HiMediaSystem_Snd_DeInit())
        {
            LOGE("ERR: HiMediaSystem_Snd_DeInit fail!");
        }

        if (HI_SUCCESS != HiMediaSystem_VO_DeInit())
        {
            LOGE("ERR: HiMediaSystem_VO_DeInit fail!");
        }

        if (HI_SUCCESS != HI_SYS_DeInit())
        {
            LOGE("ERR: HI_SYS_DeInit fail!");
        }

        return 0;
    }

    int HiMediaSystem::initDevice()
    {
        HI_S32 s32Ret = NO_ERROR;

        LOGE("%s IN, HiMediaSystem::mDeviceInstCount = %d", __FUNCTION__, HiMediaSystem::mDeviceInstCount);

        Mutex::Autolock mLock(&HiMediaSystem::mDeviceInstMutex);
        if (0 == HiMediaSystem::mDeviceInstCount)
        {
            s32Ret = initMediaDevice();
        }

        HiMediaSystem::mDeviceInstCount++;

        return s32Ret;
    }

    int HiMediaSystem::deInitDevice()
    {
        HI_S32 s32Ret = NO_ERROR;

        LOGE("%s IN, HiMediaSystem::mDeviceInstCount = %d", __FUNCTION__, HiMediaSystem::mDeviceInstCount);

        Mutex::Autolock mLock(&HiMediaSystem::mDeviceInstMutex);

        if (HiMediaSystem::mDeviceInstCount > 0)
            HiMediaSystem::mDeviceInstCount--;

        if (0 == HiMediaSystem::mDeviceInstCount)
        {
            s32Ret = destroyMediaDevice();
        }

        return s32Ret;
    }

    int HiMediaSystem::initPlayer()
    {
        HI_S32 s32Ret = NO_ERROR;

        LOGV("HiMediaSystem::initPlayer()");
        Mutex::Autolock mLock(&HiMediaSystem::mPlayerInstMutex);
        if (HiMediaSystem::mPlayerInstCount >= MAX_INSTANCE_NUM)
        {
            LOGV("WAR: HiMediaSystem::mInstPlayerCount >= MAX_INSTANCE_NUM");
            //return UNKNOWN_ERROR;
        }

        if (0 == HiMediaSystem::mPlayerInstCount)
        {
            s32Ret = HI_SVR_PLAYER_Init();
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_Init failed");
                return s32Ret;
            }

            HI_SVR_PLAYER_EnableDbg(HI_TRUE);

            HI_FORMAT_LIB_VERSION_S stVersion;
            HI_SVR_PLAYER_GetVersion(&stVersion);
            LOGV("current HiMediaSystem lib version is %d.%d.%d.%d",
                 stVersion.u8VersionMajor,
                 stVersion.u8VersionMinor,
                 stVersion.u8Revision,
                 stVersion.u8Step);

            s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libffmpeg_plugin.so");
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_RegisterDynamic libffmpeg_plugin.so");
            }

            s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libformat.so");
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_RegisterDynamic libformat.so fail");
            }

            s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libdvdprotocol.so");
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_RegisterDynamic libdvdprotocol.so fail");
            }

            s32Ret = HI_SVR_PLAYER_RegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, "libffmpegformat.so");
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_RegisterDynamic libffmpegformat.so fail");
            }
        }

        HiMediaSystem::mPlayerInstCount++;
        LOGV("HiMediaSystem::initPlayer() OK inst num [%d]", HiMediaSystem::mPlayerInstCount);
        return s32Ret;
    }

    int HiMediaSystem::deInitPlayer()
    {
        HI_S32 s32Ret = NO_ERROR;

        LOGV("HiMediaSystem::deInitPlayer()");
        Mutex::Autolock mLock(&HiMediaSystem::mPlayerInstMutex);
        HiMediaSystem::mPlayerInstCount--;
        LOGV("HiMediaSystem::deInitPlayer() inst num [%d]", HiMediaSystem::mPlayerInstCount);
        if (0 == HiMediaSystem::mPlayerInstCount)
        {
            s32Ret = HI_SVR_PLAYER_UnRegisterDynamic(HI_SVR_PLAYER_DLL_PARSER, NULL);
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_UnRegisterDynamic fail!");
            }

            s32Ret = HI_SVR_PLAYER_Deinit();
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: HI_SVR_PLAYER_Deinit fail!");
            }
            else
            {
                LOGV("HI_SVR_PLAYER_Deinit success!");
            }
        }

        return s32Ret;
    }

    int HiMediaSystem::initCharset()
    {
        Mutex::Autolock mLock(&HiMediaSystem::mCharsetInstMutex);

        LOGV("HiMediaSystem::initCharset mCharsetInstCount is [%d]", HiMediaSystem::mCharsetInstCount);
        if (0 == HiMediaSystem::mCharsetInstCount++)
        {
            int s32Ret = HI_CHARSET_Init();
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: charset init failed\n");
                return s32Ret;
            }

            s32Ret = HI_CHARSET_RegisterDynamic("libcharset.so");
            if (HI_SUCCESS != s32Ret)
            {
                LOGE("ERR: register charset libcharset.so fail, ret = 0x%x \n", s32Ret);
                return s32Ret;
            }
        }

        return NO_ERROR;
    }

    int HiMediaSystem::deInitCharset()
    {
        Mutex::Autolock mLock(&HiMediaSystem::mCharsetInstMutex);

        HiMediaSystem::mCharsetInstCount--;
        LOGV("HiMediaSystem::deInitCharset mCharsetInstCount is [%d]", HiMediaSystem::mCharsetInstCount);
        if (0 == HiMediaSystem::mCharsetInstCount)
        {
            return HI_CHARSET_Deinit();
        }

        return NO_ERROR;
    }
};
