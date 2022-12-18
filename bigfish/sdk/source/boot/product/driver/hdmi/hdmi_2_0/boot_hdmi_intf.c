#include "hi_drv_hdmi.h"
#include "hi_unf_hdmi.h"
#include "hi_drv_disp.h"
#include "drv_hdmi_common.h"
#include "boot_hdmi_intf.h"

#define CHECK_POINTER(p) \
do{                      \
    if(HI_NULL == p){\
        HDMI_ERR("Error In %s,Line %d\n",__FUNCTION__,__LINE__);       \
        return HI_FAILURE;\
    } \
}while(0) 


static HDMI_DEVICE_S s_stHdmiDev[HDMI_DEVICE_ID_BUTT];

static HDMI_VIDEO_TIMING_E DispFmt2HdmiTiming(HI_U32 u32DispFmt)
{
    HDMI_VIDEO_TIMING_E VideoTimingMode;
    switch (u32DispFmt)
    {
        case HI_DRV_DISP_FMT_1080P_60:
        case HI_DRV_DISP_FMT_1080P_59_94:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_60000;
            break;
        case HI_DRV_DISP_FMT_1080P_50:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_50000;
            break;
        case HI_DRV_DISP_FMT_1080P_30:
        case HI_DRV_DISP_FMT_1080P_29_97:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_30000;
            break;
        case HI_DRV_DISP_FMT_1080P_25:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_25000;
            break;
        case HI_DRV_DISP_FMT_1080P_24:
        case HI_DRV_DISP_FMT_1080P_23_976:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080P_24000;
            break;
        case HI_DRV_DISP_FMT_1080i_60:
        case HI_DRV_DISP_FMT_1080i_59_94:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080I_60000;
            break;
        case HI_DRV_DISP_FMT_1080i_50:
            VideoTimingMode = HDMI_VIDEO_TIMING_1920X1080I_50000;
            break;
        case HI_DRV_DISP_FMT_720P_60:
        case HI_DRV_DISP_FMT_720P_59_94:
            VideoTimingMode = HDMI_VIDEO_TIMING_1280X720P_60000;
            break;
        case HI_DRV_DISP_FMT_720P_50:
            VideoTimingMode = HDMI_VIDEO_TIMING_1280X720P_50000;
            break;
        case HI_DRV_DISP_FMT_576P_50:
            VideoTimingMode = HDMI_VIDEO_TIMING_720X576P_50000;
            break;
        case HI_DRV_DISP_FMT_480P_60:
            VideoTimingMode = HDMI_VIDEO_TIMING_720X480P_60000;
            break;
        case HI_DRV_DISP_FMT_3840X2160_24:
        case HI_DRV_DISP_FMT_3840X2160_23_976:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_24000;
            break;            
        case HI_DRV_DISP_FMT_3840X2160_25:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_25000;
            break;  
        case HI_DRV_DISP_FMT_3840X2160_30:
        case HI_DRV_DISP_FMT_3840X2160_29_97:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_30000;
            break;  
        case HI_DRV_DISP_FMT_4096X2160_24:    
            VideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_24000;
            break;
        case HI_DRV_DISP_FMT_4096X2160_25:    
            VideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_25000;
            break;
        case HI_DRV_DISP_FMT_4096X2160_30:    
            VideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_30000;
            break;
        case HI_DRV_DISP_FMT_3840X2160_50:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_50000;
            break;  
        case HI_DRV_DISP_FMT_3840X2160_60:
            VideoTimingMode = HDMI_VIDEO_TIMING_3840X2160P_60000;
            break; 
        case HI_DRV_DISP_FMT_4096X2160_50:    
            VideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_50000;
            break;
        case HI_DRV_DISP_FMT_4096X2160_60:    
            VideoTimingMode = HDMI_VIDEO_TIMING_4096X2160P_60000;
            break;
        case HI_DRV_DISP_FMT_1440x576i_50:
        case HI_DRV_DISP_FMT_PAL:
        case HI_DRV_DISP_FMT_PAL_B:
        case HI_DRV_DISP_FMT_PAL_B1:
        case HI_DRV_DISP_FMT_PAL_D:
        case HI_DRV_DISP_FMT_PAL_D1:
        case HI_DRV_DISP_FMT_PAL_G:
        case HI_DRV_DISP_FMT_PAL_H:
        case HI_DRV_DISP_FMT_PAL_K:
        case HI_DRV_DISP_FMT_PAL_I:
        case HI_DRV_DISP_FMT_PAL_M:
        case HI_DRV_DISP_FMT_PAL_N:
        case HI_DRV_DISP_FMT_PAL_Nc:
        case HI_DRV_DISP_FMT_PAL_60:

        case HI_DRV_DISP_FMT_SECAM_SIN:
        case HI_DRV_DISP_FMT_SECAM_COS:
        case HI_DRV_DISP_FMT_SECAM_L:
        case HI_DRV_DISP_FMT_SECAM_B:
        case HI_DRV_DISP_FMT_SECAM_G:
        case HI_DRV_DISP_FMT_SECAM_D:
        case HI_DRV_DISP_FMT_SECAM_K:
        case HI_DRV_DISP_FMT_SECAM_H:
            VideoTimingMode = HDMI_VIDEO_TIMING_720X576I_50000;
            break;
        case HI_DRV_DISP_FMT_1440x480i_60:
        case HI_DRV_DISP_FMT_NTSC:
        case HI_DRV_DISP_FMT_NTSC_J:
        case HI_DRV_DISP_FMT_NTSC_443:
            VideoTimingMode = HDMI_VIDEO_TIMING_720X480I_60000;
            break;
        case HI_DRV_DISP_FMT_861D_640X480_60:
            VideoTimingMode = HDMI_VIDEO_TIMING_640X480P_60000;
            break;
        default:
            HDMI_INFO("Not CEA video timing:%d\n", u32DispFmt);
            // 4k2k && vesa
            VideoTimingMode = HDMI_VIDEO_TIMING_UNKNOWN;
            break;
    }

    return VideoTimingMode;
}

static HI_VOID HdmiVOAttrInit(HDMI_VO_ATTR_S *pstVideoAttr)
{
    //pstVideoAttr->enVideoTiming = DispFmt2HdmiTiming(u32DispFmt);

    if (pstVideoAttr->enVideoTiming > HDMI_VIDEO_TIMING_720X576P_50000)
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_709;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_16_9;
        pstVideoAttr->enHvSyncPol     = HDMI_HV_SYNC_POL_HPVP;
    }
    else
    {
        pstVideoAttr->enColorimetry   = HDMI_COLORIMETRY__ITU_601;
        pstVideoAttr->enPictureAspect = HDMI_PICTURE_ASPECT_4_3;
        pstVideoAttr->enHvSyncPol     = HDMI_HV_SYNC_POL_HNVN;
    }

    pstVideoAttr->u32PixelRepeat = 1;
    if (pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_720X480I_60000 ||
        pstVideoAttr->enVideoTiming == HDMI_VIDEO_TIMING_720X576I_50000)
    {
        pstVideoAttr->u32PixelRepeat = 2;
    }

    if (pstVideoAttr->enVideoTiming <= HDMI_VIDEO_TIMING_640X480P_60000)
    {
        pstVideoAttr->enRGBQuantization = HDMI_QUANTIZATION_RANGE_FULL;
    }
    else
    {
        pstVideoAttr->enYCCQuantization = HDMI_YCC_QUANTIZATION_RANGE_LIMITED;
    }
    
    if (pstVideoAttr->enVideoTiming != HDMI_VIDEO_TIMING_UNKNOWN &&
        pstVideoAttr->enVideoTiming != HDMI_VIDEO_TIMING_640X480P_60000)
    {
        pstVideoAttr->enInColorSpace = HDMI_COLORSPACE_YCbCr444;
    }
    else
    {
        pstVideoAttr->enInColorSpace = HDMI_COLORSPACE_RGB;
    }
    
    pstVideoAttr->enStereoMode    = HDMI_3D_BUTT;
    pstVideoAttr->enInBitDepth    = HDMI_VIDEO_BITDEPTH_10;
    pstVideoAttr->enActiveAspect  = HDMI_ACTIVE_ASPECT_PICTURE;
}


static HI_VOID DispFmt2VOAttr(HI_U32 u32DispFmt, HDMI_VO_ATTR_S *pstVideoAttr)
{
    pstVideoAttr->enVideoTiming = DispFmt2HdmiTiming(u32DispFmt);
    HdmiVOAttrInit(pstVideoAttr);
}

static HI_S32 HdmiDeviceInit(HDMI_DEVICE_S * pstHdmiDev)
{
    HDMI_AO_ATTR_S*          pstAudioAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;
    HDMI_APP_ATTR_S*         pstAppAttr;
    CHECK_POINTER(pstHdmiDev);
    
    pstAudioAttr = &pstHdmiDev->stAttr.stAOAttr;
    pstVideoAttr = &pstHdmiDev->stAttr.stVOAttr;
    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;

    pstAppAttr->bEnableHdmi = HI_TRUE;
    pstHdmiDev->enTmdsMode  = HDMI_TMDS_MODE_HDMI_1_4;
    
    /* video attribute init*/
    pstVideoAttr->enVideoTiming = HDMI_VIDEO_TIMING_1280X720P_50000;
    HdmiVOAttrInit(pstVideoAttr);

    /* audio attribute init*/
    pstAudioAttr->enSoundIntf   = HDMI_AUDIO_INTERFACE__I2S;
    pstAudioAttr->enSampleFs    = HDMI_SAMPLE_RATE_48K;
    pstAudioAttr->enSampleDepth = HDMI_AUDIO_BIT_DEPTH_16;
    pstAudioAttr->enChanels     = HDMI_AUDIO_FORMAT_2CH;
    
    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_Open(HDMI_DEVICE_S* pstHdmiDev)
{
    HI_S32 s32Ret = HI_FAILURE;
    CHECK_POINTER(pstHdmiDev);

    /* open hdmi hal module*/
    s32Ret = HAL_HDMI_Open(HI_NULL, &pstHdmiDev->pstHdmiHal);
    if (s32Ret != HI_SUCCESS)
    {
        HDMI_ERR("HAL_HDMI_Open fail\n");
        return HI_FAILURE;    
    }
    
    HdmiDeviceInit(pstHdmiDev);
    pstHdmiDev->pstHdmiHal->stHalCtx.hHdmiDev = pstHdmiDev;
    pstHdmiDev->pstHdmiHal->stHalCtx.u32HdmiID = pstHdmiDev->u32HdmiDevId;
    
    pstHdmiDev->pstHdmiHal->HAL_HDMI_HardwareInit(pstHdmiDev->pstHdmiHal);
    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_AVMuteSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bAvMute)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_AvMuteSet(pstHdmiDev->pstHdmiHal, bAvMute);
    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_Start(HDMI_DEVICE_S* pstHdmiDev)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
   
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyPowerEnableSet(pstHdmiDev->pstHdmiHal, HI_TRUE);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_TmdsModeSet(pstHdmiDev->pstHdmiHal, pstHdmiDev->enTmdsMode);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyOutputEnableSet(pstHdmiDev->pstHdmiHal, HI_TRUE);
    DRV_HDMI_AVMuteSet(pstHdmiDev, HI_FALSE);

    return HI_SUCCESS;
}


HI_S32 DRV_HDMI_Stop(HDMI_DEVICE_S* pstHdmiDev)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    DRV_HDMI_AVMuteSet(pstHdmiDev, HI_TRUE);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyOutputEnableSet(pstHdmiDev->pstHdmiHal, HI_FALSE);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyPowerEnableSet(pstHdmiDev->pstHdmiHal, HI_FALSE);
    return HI_SUCCESS;
}

HI_S32 DRV_HDMI_Close(HDMI_DEVICE_S* pstHdmiDev)
{
    CHECK_POINTER(pstHdmiDev);
 
    DRV_HDMI_Stop(pstHdmiDev);
    HAL_HDMI_Close(pstHdmiDev->pstHdmiHal);
    return HI_SUCCESS;   
}



#if 0
static HI_S32 CheckAudioAttr(HDMI_AO_ATTR_S *pstAOAttr)
{
    if (HDMI_AUDIO_INTERFACE__I2S != pstAOAttr->enSoundIntf
       && HDMI_AUDIO_INTERFACE__SPDIF != pstAOAttr->enSoundIntf
       && HDMI_AUDIO_INTERFACE__HBRA != pstAOAttr->enSoundIntf)
    {
        HDMI_COM_ERR("The Audio interface(%d) is invalid\n",pstAOAttr->enSoundIntf);
        return HI_FAILURE;
    }

    if (pstAOAttr->enChanels < HDMI_AUDIO_FORMAT_2CH || pstAOAttr->enChanels > HDMI_AUDIO_FORMAT_8CH)
    {
        HDMI_COM_ERR("The Audio chanel number(%d) is invalid\n",pstAOAttr->enChanels);
        return HI_FAILURE;
    }
    
    switch (pstAOAttr->enSampleFs)
    {
        case HDMI_SAMPLE_RATE_32K:
        case HDMI_SAMPLE_RATE_44K:
        case HDMI_SAMPLE_RATE_48K:
        case HDMI_SAMPLE_RATE_88K:
        case HDMI_SAMPLE_RATE_96K:
        case HDMI_SAMPLE_RATE_176K:
        case HDMI_SAMPLE_RATE_192K:
        case HDMI_SAMPLE_RATE_768K:
            break;
        default:
            HDMI_COM_ERR("The input Audio Frequency(%d) is invalid\n",pstAOAttr->enSampleFs);
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 HdmiAudioPathSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr)
{
    HDMI_AUDIO_CONFIG_S      stAudioCfg;
    
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAOAttr);   
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    
    stAudioCfg.bDownSample   = pstAOAttr->bDownSample;
    stAudioCfg.enLayout      = pstAOAttr->enChanels;
    stAudioCfg.enSampleDepth = pstAOAttr->enSampleDepth;
    stAudioCfg.enSampleFs    = pstAOAttr->enSampleFs;
    stAudioCfg.enSoundIntf   = pstAOAttr->enSoundIntf;
    pstHdmiDev->pstHdmiHal->HAL_HDMI_AudioPathSet(pstHdmiDev->pstHdmiHal, &stAudioCfg);

    return HI_SUCCESS;
    
}



HI_S32 DRV_HDMI_AOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr)
{
    HDMI_AO_ATTR_S*          pstAudioAttr;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAOAttr);
  
    if (HI_SUCCESS != CheckAudioAttr(pstAOAttr))
    {
        HDMI_COM_ERR("HDMI_CheckAudioAttr fail\n");
        return HI_FAILURE;
    }

    pstAudioAttr = &pstHdmiDev->stAttr.stAOAttr;
#if 0    
    if (!memcmp(pstAOAttr, pstAudioAttr, sizeof(HDMI_AO_ATTR_S)))
    {
        HDMI_COM_INFO("The Audio Attr is not change\n");
        return HI_SUCCESS;    
    }
#endif
    HdmiAudioPathSet(pstHdmiDev, pstAOAttr);
    memcpy(pstAudioAttr, pstAOAttr, sizeof(HDMI_AO_ATTR_S));

    HDMI_AudioInfoFrameSet(&pstHdmiDev->stInfoFrame);

    return HI_SUCCESS;
}

#endif


static HI_S32 CheckVideoAttr(HDMI_VO_ATTR_S* pstVOAttr)
{
    CHECK_POINTER(pstVOAttr);
    
    if (pstVOAttr->enVideoTiming >= HDMI_VIDEO_TIMING_BUTT ||
        pstVOAttr->enVideoTiming < 0)
    {
        HDMI_ERR("Hdmi video timing(%d) is wrong\n", pstVOAttr->enVideoTiming);
        return HI_FAILURE;
    }

    
    if (pstVOAttr->enHvSyncPol > HDMI_HV_SYNC_POL_HNVN ||
        pstVOAttr->enHvSyncPol < 0)
    {
        HDMI_ERR("Hdmi video HvSyncPol(%d) is wrong\n", pstVOAttr->enHvSyncPol);
        return HI_FAILURE;
    }

    if (pstVOAttr->enInColorSpace >= HDMI_COLORSPACE_BUTT ||
        pstVOAttr->enInColorSpace < 0)
    {
        HDMI_ERR("Hdmi video InColorSpace(%d) is wrong\n", pstVOAttr->enInColorSpace);
        return HI_FAILURE;
    }

    if (pstVOAttr->enColorimetry <= HDMI_COLORIMETRY__NONE ||
        pstVOAttr->enColorimetry > HDMI_COLORIMETRY__EXTENDED)
    {
        HDMI_ERR("Hdmi video Colorimetry(%d) is wrong\n", pstVOAttr->enColorimetry);
        return HI_FAILURE;
    }

    if (pstVOAttr->enRGBQuantization < HDMI_QUANTIZATION_RANGE_DEFAULT ||
        pstVOAttr->enRGBQuantization > HDMI_QUANTIZATION_RANGE_FULL)
    {
        HDMI_ERR("Hdmi video RGBQuantization(%d) is wrong\n", pstVOAttr->enRGBQuantization);
        return HI_FAILURE;
    }

    if (pstVOAttr->enPictureAspect < HDMI_PICTURE_ASPECT_4_3 ||
        pstVOAttr->enPictureAspect > HDMI_PICTURE_ASPECT_16_9)
    {
        HDMI_ERR("Hdmi video PictureAspect(%d) is wrong\n", pstVOAttr->enPictureAspect);
        return HI_FAILURE;
    }

    if (pstVOAttr->enInBitDepth < HDMI_VIDEO_BITDEPTH_8 ||
        pstVOAttr->enInBitDepth > HDMI_VIDEO_BITDEPTH_12)
    {
        HDMI_ERR("Hdmi video InBitDepth(%d) is wrong\n", pstVOAttr->enInBitDepth);
        return HI_FAILURE;
    }
        
    return HI_SUCCESS;
}


static HI_S32 HdmiVideoPathSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr)
{
    HDMI_VIDEO_CONFIG_S stVideoCfg = {0};
    HDMI_APP_ATTR_S*    pstAppAttr;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstVOAttr);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    
    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;
    
    stVideoCfg.u32PixelClk     = pstVOAttr->u32ClkFs;
    stVideoCfg.enInBitDepth    = pstVOAttr->enInBitDepth;
    stVideoCfg.enHvSyncPol     = pstVOAttr->enHvSyncPol;
    stVideoCfg.enQuantization  = pstVOAttr->enRGBQuantization;
    stVideoCfg.enInColorSpace  = pstVOAttr->enInColorSpace;
    stVideoCfg.enDeepColor     = pstAppAttr->enDeepColorMode;
    stVideoCfg.enOutColorSpace = pstAppAttr->bYUV420Enable ? HDMI_COLORSPACE_YCbCr420 : pstAppAttr->enOutColorSpace;
    stVideoCfg.enOutColorSpace = pstAppAttr->bEnableHdmi ? stVideoCfg.enOutColorSpace : HDMI_COLORSPACE_RGB;

    switch (pstVOAttr->enColorimetry)
    {
        case HDMI_COLORIMETRY__ITU_601:
            stVideoCfg.enConvStd = HDMI_CONV_STD_BT_601;
            break;
        case HDMI_COLORIMETRY__ITU_709:
            stVideoCfg.enConvStd = HDMI_CONV_STD_BT_709;
            break;              
        case HDMI_COLORIMETRY__EXTENDED:
            if (pstVOAttr->enExtendedColorimetry == HDMI_EXTENDED_COLORIMETRY_2020_non_const_luminous)
                stVideoCfg.enConvStd = HDMI_CONV_STD_BT_2020_non_const_luminous;
            else if (pstVOAttr->enExtendedColorimetry == HDMI_EXTENDED_COLORIMETRY_2020_const_luminous)
                stVideoCfg.enConvStd = HDMI_CONV_STD_BT_2020_const_luminous;
            break;   
        default:
            break;      
    }
    /* Video will mute and unmute in this function call*/
    pstHdmiDev->pstHdmiHal->HAL_HDMI_VideoPathSet(pstHdmiDev->pstHdmiHal, &stVideoCfg);
    return HI_SUCCESS;
}

#if 0 
static HI_S32 HdmiAudioPathSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_AO_ATTR_S *pstAOAttr)
{
    HDMI_AUDIO_CONFIG_S      stAudioCfg;
    
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAOAttr);   
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    
    stAudioCfg.bDownSample   = pstAOAttr->bDownSample;
    stAudioCfg.enLayout      = pstAOAttr->enChanels;
    stAudioCfg.enSampleDepth = pstAOAttr->enSampleDepth;
    stAudioCfg.enSampleFs    = pstAOAttr->enSampleFs;
    stAudioCfg.enSoundIntf   = pstAOAttr->enSoundIntf;
    pstHdmiDev->pstHdmiHal->HAL_HDMI_AudioPathSet(pstHdmiDev->pstHdmiHal, &stAudioCfg);

    return HI_SUCCESS;
    
}

HI_S32 DRV_HDMI_VOAttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_VO_ATTR_S* pstVOAttr)
{
    HDMI_AO_ATTR_S*          pstAudioAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;
    HDMI_APP_ATTR_S*         pstAppAttr;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstVOAttr);
    
    if (HI_SUCCESS != CheckVideoAttr(pstVOAttr))
    {
        HDMI_COM_ERR("HDMI_CheckVideoAttr fail\n");
        return HI_FAILURE;
    }
    
    pstAudioAttr = &pstHdmiDev->stAttr.stAOAttr;
    pstVideoAttr = &pstHdmiDev->stAttr.stVOAttr;
    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;
    
    memcpy(pstVideoAttr, pstVOAttr, sizeof(HDMI_VO_ATTR_S));  
    
    if (pstAppAttr->bEnableHdmi && pstVideoAttr->enVideoTiming >= HDMI_VIDEO_TIMING_3840X2160P_50000)
    {
        if (pstAppAttr->enOutColorSpace != HDMI_COLORSPACE_YCbCr420)
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_2_0;
        }
        else
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_1_4;
        }
    }   
     
    HdmiVideoPathSet(pstHdmiDev, pstVOAttr);
    DRV_HDMI_AVIInfoFrameSet(&pstHdmiDev->stInfoFrame);
#if 0
    HdmiAudioPathSet(pstHdmiDev, pstAudioAttr);
    HDMI_AudioInfoFrameSet(&pstHdmiDev->stInfoFrame);
#endif 
    DRV_HDMI_VendorInfoFrameSet(&pstHdmiDev->stInfoFrame);
   
    //DRV_HDMI_Start(pstHdmiDev);
    return HI_SUCCESS;
}
#endif

HI_S32 DRV_HDMI_AttrGet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr)
{
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAttr);
    
    memcpy(pstAttr, &pstHdmiDev->stAttr, sizeof(HDMI_ATTR_S));
    return HI_SUCCESS;
}

#ifdef HDMI_SCDC_SUPPORT
static HI_S32 HdmiScrambleEnableSet(HDMI_DEVICE_S* pstHdmiDev, HI_BOOL bEnable)
{
    HDMI_SCDC_CONFIG_S       stScdcConfig;
    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstHdmiDev->pstHdmiHal);
    
    memset(&stScdcConfig, 0, sizeof(HDMI_SCDC_CONFIG_S));
    stScdcConfig.bScdcEnable             = bEnable;
    stScdcConfig.bScdcPresent            = HI_TRUE;
    stScdcConfig.bRRCapable              = HI_FALSE;
    stScdcConfig.bLTE340McscScramble     = HI_FALSE;
    
    if (bEnable)
    {
        stScdcConfig.u32MaxTmdsCharacterRate = 600 * 1000000;
        pstHdmiDev->pstHdmiHal->HAL_HDMI_PhyOutputEnableSet(pstHdmiDev->pstHdmiHal, HI_FALSE);
    }
    else
    {
        stScdcConfig.u32MaxTmdsCharacterRate = 300 * 1000000;
    }
    
    HDMI_INFO("ScdcEnable:%d\n",stScdcConfig.bScdcEnable); 
    HDMI_INFO("Scdc Config:ScdcPresent(%d),RRCapable(%d),LTE340McscScramble(%d),MaxTmdsCharacterRate(%d)\n",stScdcConfig.bScdcPresent,stScdcConfig.bRRCapable,stScdcConfig.bLTE340McscScramble,stScdcConfig.u32MaxTmdsCharacterRate);
    pstHdmiDev->pstHdmiHal->HAL_HDMI_ScdcConfig(pstHdmiDev->pstHdmiHal, &stScdcConfig);
    
    return HI_SUCCESS;
}
#endif
static HI_S32 HdmiModeSchedule(HDMI_DEVICE_S* pstHdmiDev)
{

    HDMI_TX_CAPABILITY_E     enTxCapability;
    HDMI_APP_ATTR_S*         pstAppAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;

    pstAppAttr   = &pstHdmiDev->stAttr.stAppAttr;
    pstVideoAttr = &pstHdmiDev->stAttr.stVOAttr;

    pstHdmiDev->pstHdmiHal->HAL_HDMI_TxCapabilityGet(pstHdmiDev->pstHdmiHal, &enTxCapability); 

    /* When video format is 4K50,60 or 4K30,25,24 deepclolor, switch to HDMI2.0*/
    if (pstVideoAttr->enVideoTiming >= HDMI_VIDEO_TIMING_3840X2160P_50000)
    {
    #if 0  
        if ((enTxCapability & HDMI_TX_SUPPORT_HDMI2_0) && 
            pstAppAttr->bEnableHdmi == HI_TRUE &&
            pstAppAttr->enOutColorSpace != HDMI_COLORSPACE_YCbCr420)
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_2_0;
        }
        else if (pstAppAttr->bEnableHdmi != HI_TRUE)
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_DVI;
            pstAppAttr->enOutColorSpace = HDMI_COLORSPACE_RGB;
        }
        else 
        {
            HDMI_ERR("source does not support HDMI2.0\n");
            return HI_FAILURE;
        }
    #else
        HDMI_INFO("Enable YUV420\n");
        pstHdmiDev->enTmdsMode      = HDMI_TMDS_MODE_HDMI_1_4;  
        pstAppAttr->bYUV420Enable = HI_TRUE;//In boot, when fmt is 4KP60, set outcolorspace YUV420 default   
    #endif
    } 
    else
    {
        if (pstAppAttr->bEnableHdmi == HI_TRUE)
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_HDMI_1_4;  
        }
        else
        {
            pstHdmiDev->enTmdsMode = HDMI_TMDS_MODE_DVI;
            pstAppAttr->enOutColorSpace = HDMI_COLORSPACE_RGB;
        }
    }

   
#ifdef HDMI_SCDC_SUPPORT    
    if (pstHdmiDev->enTmdsMode == HDMI_TMDS_MODE_HDMI_2_0)
    {
        HdmiScrambleEnableSet(pstHdmiDev, HI_TRUE);
    }
    else
    {
        HdmiScrambleEnableSet(pstHdmiDev, HI_FALSE);
    }
#endif  

    pstHdmiDev->pstHdmiHal->HAL_HDMI_TmdsModeSet(pstHdmiDev->pstHdmiHal, pstHdmiDev->enTmdsMode);
    HDMI_INFO("Tmds mode switch to %d\n",pstHdmiDev->enTmdsMode,pstAppAttr->enOutColorSpace);

    return HI_SUCCESS;
}


HI_S32 DRV_HDMI_AttrSet(HDMI_DEVICE_S* pstHdmiDev, HDMI_ATTR_S *pstAttr)
{
    //HDMI_AO_ATTR_S*          pstAudioAttr;
    HDMI_VO_ATTR_S*          pstVideoAttr;
    //HDMI_APP_ATTR_S*         pstAppAttr;

    CHECK_POINTER(pstHdmiDev);
    CHECK_POINTER(pstAttr);

    //pstAudioAttr = &pstAttr->stAOAttr;
    pstVideoAttr = &pstAttr->stVOAttr;
    //pstAppAttr   = &pstAttr->stAppAttr;
    CheckVideoAttr(pstVideoAttr);
    memcpy(&pstHdmiDev->stAttr, pstAttr, sizeof(HDMI_ATTR_S)); 
    
    HdmiModeSchedule(pstHdmiDev);
    
    HdmiVideoPathSet(pstHdmiDev, &pstHdmiDev->stAttr.stVOAttr);
    DRV_HDMI_AVIInfoFrameSend(&pstHdmiDev->stInfoFrame, HI_TRUE);
#if 0
    HdmiAudioPathSet(pstHdmiDev, pstAudioAttr);
    DRV_HDMI_AudioInfoFrameSet(&pstHdmiDev->stInfoFrame);
#endif
    DRV_HDMI_VendorInfoFrameSend(&pstHdmiDev->stInfoFrame, HI_TRUE);

    return HI_SUCCESS;
}
#if 0
static HI_S32 Disp2HdmiVoAttr(HDMI_VO_ATTR_S *pstDestAttr, HDMI_VIDEO_ATTR_S *pstSrcAttr)
{
    if (pstSrcAttr == HI_NULL || pstDestAttr == HI_NULL)
    {
        return HI_FAILURE;
    }

    pstDestAttr->enColorimetry   = pstSrcAttr->enColorimetry;
    if (pstSrcAttr->enColorimetry > HDMI_COLORIMETRY_EXTENDED)
    {
        pstDestAttr->enColorimetry = HDMI_COLORIMETRY__EXTENDED;
        pstDestAttr->enExtendedColorimetry = pstSrcAttr->enColorimetry - HDMI_COLORIMETRY_EXTENDED - 1;
    }
    pstDestAttr->enPictureAspect   = pstSrcAttr->enPictureAspect;
    pstDestAttr->enActiveAspect    = pstSrcAttr->enActiveAspect;    
    pstDestAttr->enHvSyncPol       = pstSrcAttr->enHvSyncPol;
    pstDestAttr->enInBitDepth      = pstSrcAttr->enInBitDepth;
    pstDestAttr->enInColorSpace    = pstSrcAttr->enInColorSpace;
    pstDestAttr->enPictureScaling  = pstSrcAttr->enPictureScaling;
    pstDestAttr->enRGBQuantization = pstSrcAttr->enRGBQuantization;
    pstDestAttr->enYCCQuantization = pstSrcAttr->enYCCQuantization;
    pstDestAttr->enStereoMode      = pstSrcAttr->enStereoMode;
    pstDestAttr->enVideoTiming     = DispFmt2HdmiTiming(pstSrcAttr->enVideoFmt);
    pstDestAttr->u32ClkFs          = pstSrcAttr->u32ClkFs;
    pstDestAttr->u32PixelRepeat    = pstSrcAttr->u32PixelRepeat;

    return HI_SUCCESS;
}
#endif
HI_S32 HI_DRV_HDMI_Init(HI_VOID)
{
   return HI_SUCCESS;
}

HI_S32 HI_DRV_HDMI_Open(HI_UNF_HDMI_ID_E enHdmiID)
{
    memset(&s_stHdmiDev[enHdmiID], 0, sizeof(HDMI_DEVICE_S));
    s_stHdmiDev[enHdmiID].u32HdmiDevId = enHdmiID;
    return DRV_HDMI_Open(&s_stHdmiDev[enHdmiID]);
}
#if 0
HI_S32 HI_DRV_HDMI_SetFormat(HI_UNF_HDMI_ID_E enHdmiID, HDMI_VIDEO_ATTR_S *pstVideoAttr)
{
    HDMI_VO_ATTR_S  stVOAttr;
    //DispFmt2VOAttr(u32DispFmt, &stVOAttr);
    Disp2HdmiVoAttr(&stVOAttr, pstVideoAttr);
    return DRV_HDMI_VOAttrSet(&s_stHdmiDev[enHdmiID], &stVOAttr);
}
#endif
HI_S32 HI_DRV_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmiID, HI_DRV_HDMI_ATTR_S *pstAttr)
{
    HDMI_ATTR_S stAttr;
    memset(&stAttr, 0, sizeof(HDMI_ATTR_S));
    DRV_HDMI_AttrGet(&s_stHdmiDev[enHdmiID], &stAttr);
    DispFmt2VOAttr(pstAttr->u32DispFmt, &stAttr.stVOAttr);
    stAttr.stAppAttr.bEnableHdmi     = pstAttr->bEnableHdmi;
    //stAttr.stAppAttr.bEnableAudio    = pstAttr->bEnableAudio;
    //stAttr.stAppAttr.bEnableVideo    = pstAttr->bEnableVideo;
    stAttr.stAppAttr.enOutColorSpace = pstAttr->enVidOutMode;
    stAttr.stVOAttr.enInColorSpace   = pstAttr->enVidInMode;
    stAttr.stVOAttr.u32ClkFs         = pstAttr->u32ClkFs;
    return DRV_HDMI_AttrSet(&s_stHdmiDev[enHdmiID], &stAttr);
}
#if 0
HI_S32 HI_DRV_HDMI_GetAttr(HI_UNF_HDMI_ID_E enHdmiID, HDMI_ATTR_S *pstAttr)
{
    return DRV_HDMI_AttrGet(&s_stHdmiDev[enHdmiID], pstAttr);
}
#endif
HI_S32 HI_DRV_HDMI_Start(HI_UNF_HDMI_ID_E enHdmiID)
{
    return DRV_HDMI_Start(&s_stHdmiDev[enHdmiID]);
}

HI_S32 HI_DRV_HDMI_Close(HI_UNF_HDMI_ID_E enHdmiID)
{
    return DRV_HDMI_Close(&s_stHdmiDev[enHdmiID]);
}

HI_S32 HI_DRV_HDMI_DeInit(HI_VOID)
{
   return HI_SUCCESS;
}

HI_S32 HI_UNF_HDMI_Init(void)
{
    return HI_DRV_HDMI_Init();
}

HI_S32 HI_UNF_HDMI_DeInit(void)
{
    return HI_DRV_HDMI_DeInit();
}


HI_S32 HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_E enHdmi)
{
    return HI_DRV_HDMI_Open(enHdmi);
}
#if 0
HI_S32 HI_UNF_HDMI_SetFormat(HI_UNF_HDMI_ID_E enHdmi, HI_U32 u32DispFmt)
{
    return HI_DRV_HDMI_SetFormat(enHdmi, u32DispFmt);
}
#endif
HI_S32 HI_UNF_HDMI_SetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr)
{
    return HI_DRV_HDMI_SetAttr(enHdmi, (HI_DRV_HDMI_ATTR_S*)pstAttr);
}
#if 0
HI_S32 HI_UNF_HDMI_GetAttr(HI_UNF_HDMI_ID_E enHdmi, HI_UNF_HDMI_ATTR_S *pstAttr)
{
    return HI_DRV_HDMI_GetAttr(enHdmi, pstAttr);
}
#endif
HI_S32 HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_E enHdmi)
{
    return HI_DRV_HDMI_Start(enHdmi);
}


HI_S32 HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_E enHdmi)
{
    return HI_DRV_HDMI_Close(enHdmi);
}




