/******************************************************************************

 Copyright (C), 2001-2051, Hisilicon Tech. Co., Ltd.

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <linux/videodev.h>
#include <fcntl.h>
#include <string.h>
#include <net/if.h>

#include "utils/Log.h"
#include "vp_adpt.h"
#include "hi_unf_common.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_vi.h"
#include "hi_unf_venc.h"
#include "hi_unf_vp.h"
#include "hi_unf_avplay.h"
#include "hi_unf_voip.h"
#include "hi_unf_sound.h"
#include "hi_go_surface.h"
#include "hi_unf_mce.h"

//#include "hi_adp_mpi.h"

/*******************************Net Related  *****************************/

#define DFLT_SCOPE_ID "eth0"  /* Default scope identifier.  */
#define DFLT_RTP_PORT 16384  /* Default RTP port.  */

/*******************************  USB cam Related*****************************/
static HI_U32 g_SetUsbCamFps    = 30;
static HI_U32 g_SetUsbCamWidth  = 640;
static HI_U32 g_SetUsbCamHeight = 480;
static char *g_UsbCamDev  = "/dev/video0";
static HI_U32 g_u32BufCnt = 4;

static HI_S32 g_VideoOption[HI_OPTIONAL_CONFIG_BUTT] = 
{
	HI_UNF_H264_PROFILE_HIGH, 	//HI_OPTIONAL_CONFIG_VENC_PROFILE, 
	1450,						//HI_OPTIONAL_CONFIG_RTP_SPLIT_SIZE, 
	1500,						//HI_OPTIONAL_CONFIG_RTP_RECVBUF_SIZE,
	150,						//HI_OPTIONAL_CONFIG_RTP_RECVBUF_NUM, 
	5, 							// HI_OPTIONAL_CONFIG_RTP_SORT_DEPTH,
	1							//HI_OPTIONAL_CONFIG_NET_IP_TYPE
};

typedef struct hiUSB_CAM_THREAD_ARG_S
{
    HI_HANDLE hVP;
    HI_U32    u32USBCamFmt;
    int       UsbCamFd;
} USB_CAM_THREAD_ARG_S;

static HI_U32 g_u32CamFormat = 1; /*1 - YUV,  0 -MJPEG*/

static pthread_t g_threadUSBCam;
static USB_CAM_THREAD_ARG_S g_stUSBCamArgs;
static HI_BOOL g_bUSBCamStop = HI_FALSE;
static HI_BOOL g_UsbPlugFlag = HI_FALSE;

/*******************************  Video Related *****************************/
/* DAC */
#define DAC_CVBS HI_DAC_CVBS
#define DAC_YPBPR_Y HI_DAC_YPBPR_Y
#define DAC_YPBPR_PB HI_DAC_YPBPR_PB
#define DAC_YPBPR_PR HI_DAC_YPBPR_PR

static HI_HANDLE hRemoteWin = HI_INVALID_HANDLE;
static HI_HANDLE hLocalWin = HI_INVALID_HANDLE;
static HI_HANDLE hVP = HI_INVALID_HANDLE;

static HI_U32 g_u32Span = 5000;
static HI_U32 g_stopGet = 0;
static pthread_t g_threadStatics;

static HI_DOUBLE g_u32InRate  = 0;
static HI_DOUBLE g_u32OutRate = 0;
static HI_BOOL bHasVideoData = HI_FALSE;

#define SYS_MAX_VALUE 0xFFFFFFFFU

static HI_U32 g_PhonePlayer_VideoState = 0;

/*******************************  Audio Related *****************************/
#define HI_AUD_DEV_LIST_MAX 10
#define HI_VOIP_DEF_NET_PORT 8100
#define AUD_MAX_GAIN 0
#define AUD_MIN_GAIN -70
#define HI_AUD_DEV_LOCK()
#define HI_AUD_DEV_UNLOCK()

typedef enum
{
    HI_VOIP_AUD_DEV_TYPE_SLIC = 0,
    HI_VOIP_AUD_DEV_TYPE_BLUETOOTH,
    HI_VOIP_AUD_DEV_TYPE_SNDCARD,
    HI_VOIP_AUD_DEV_TYPE_BUTT
} HI_VOIP_AUDIO_DEVICE_TYPE_E;

typedef struct
{
    HI_U32  u32AudDevId;                        /* HI_UNF_VOIP_AUDIO_DEVICE_E */
    HI_U32  u32AudDevTpye;                      /* HI_VOIP_AUDIO_DEVICE_TYPE_E */
    HI_S32  s32InSndCardNo;                       /* ALSA sound card number */
    HI_S32  s32InFlag;                            /*0--invalid 1--valid*/
    HI_CHAR szInName[HI_ALSA_AUD_DEV_NAME_LEN];   /*card name*/
    HI_S32  s32OutSndCardNo;                       /* ALSA sound card number */
    HI_S32  s32OutFlag;                            /*0--invalid 1--valid*/
    HI_CHAR szOutName[HI_ALSA_AUD_DEV_NAME_LEN];   /*card name*/
} HI_AUD_DEV_SELECT_PAIR_S;

typedef struct
{
    HI_U32                   u32AudInDevNum;
    HI_U32                   u32AudOutDevNum;
    HI_AUD_DEV_SELECT_PAIR_S stAudDevSel;
    HI_AUD_DEV_INFO_S        stAudevInList[HI_AUD_DEV_LIST_MAX];
    HI_AUD_DEV_INFO_S        stAudevOutList[HI_AUD_DEV_LIST_MAX];
} HI_AUD_DEV_GLOBAL_INFO_S;

static HI_AUD_DEV_GLOBAL_INFO_S g_stAudDevInfo;
static HI_HANDLE hVoipHandle = HI_NULL;
static pthread_t g_threadAudStatics;

static HI_U32 g_stopAudGet = 0;
static HI_U32 g_u32AudSpan = 5000;
static HI_DOUBLE g_u32AudInRate  = 0;
static HI_DOUBLE g_u32AudOutRate = 0;
static HI_BOOL bHasAudioData = HI_FALSE;

static HI_U32 g_PhonePlayer_AudioState = HI_ENGINE_BUTT;

/*********************************************************************
 *******************************  USB cam *****************************
 **********************************************************************/
static HI_U32 UsbCamInit(USB_CAM_THREAD_ARG_S *pArgs)
{
    HI_S32 s32Ret   = HI_FAILURE;
    HI_U32 fdUsbCam = 0;
    struct v4l2_streamparm *setfps;
    struct v4l2_capability stUsbCap;
    struct v4l2_format stUsbFmt;
    HI_S32 fps = g_SetUsbCamFps;
    char   *TmpCamDev = "/dev/video1";

    /* open usb camera with non-block mode */
    fdUsbCam = open(g_UsbCamDev, O_RDWR | O_NONBLOCK, 0);
    if (HI_FAILURE == fdUsbCam)
    {
        fdUsbCam = open(TmpCamDev, O_RDWR | O_NONBLOCK, 0);
        if (HI_FAILURE == fdUsbCam)
        {
            ALOGE("open %s failed\r\n", TmpCamDev);
            return HI_FAILURE;
        }
    }
    else
    {
        ALOGE("open %s Ok\r\n", g_UsbCamDev);
    }

    s32Ret = ioctl(fdUsbCam, VIDIOC_QUERYCAP, &stUsbCap);
    ALOGE("usb cam cap:0x%x.\n", stUsbCap.capabilities);
    if (s32Ret < 0)
    {
        ALOGE("Error opening device %s: unable to query device.\n", g_UsbCamDev);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    if ((stUsbCap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == 0)
    {
        ALOGE("Error opening device %s: video capture not supported.\n", g_UsbCamDev);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    if (!(stUsbCap.capabilities & V4L2_CAP_STREAMING))
    {
        ALOGE("%s Not support streaming i/o\n", g_UsbCamDev);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    /* test format if it supports */
    memset(&stUsbFmt, 0, sizeof(struct v4l2_format));
    stUsbFmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (ioctl(fdUsbCam, VIDIOC_G_FMT, &stUsbFmt) < 0)
    {
        ALOGE("get format failed\n");
        close(fdUsbCam);
        return HI_FAILURE;
    }
    else
    {
        ALOGE("USB CAM's orignal FMT:\n");
        ALOGE("Width = %d\n", stUsbFmt.fmt.pix.width);
        ALOGE("Height = %d\n", stUsbFmt.fmt.pix.height);
        ALOGE("Image size = %d\n", stUsbFmt.fmt.pix.sizeimage);
        ALOGE("pixelformat = %d\n", stUsbFmt.fmt.pix.pixelformat);
        ALOGE("field = %d\n", stUsbFmt.fmt.pix.field);
        if (V4L2_PIX_FMT_MJPEG == stUsbFmt.fmt.pix.pixelformat)
        {
            ALOGE("V4L2_PIX_FMT_MJPEG\r\n");
        }
        else if (V4L2_PIX_FMT_YUYV == stUsbFmt.fmt.pix.pixelformat)
        {
            ALOGE("V4L2_PIX_FMT_YUYV\r\n");
        }
        else
        {
            ALOGE("fmt unknown\r\n");
        }

        ALOGE("\n");
    }

    /* set format */
    stUsbFmt.fmt.pix.width  = g_SetUsbCamWidth;
    stUsbFmt.fmt.pix.height = g_SetUsbCamHeight;
    stUsbFmt.fmt.pix.pixelformat = pArgs->u32USBCamFmt;
    s32Ret = ioctl(fdUsbCam, VIDIOC_S_FMT, &stUsbFmt);
    if (s32Ret < 0)
    {
        ALOGE("Unable to set format: %d, err:%d.\n", stUsbFmt.fmt.pix.pixelformat, errno);
        close(fdUsbCam);
        return s32Ret;
    }

    if (ioctl(fdUsbCam, VIDIOC_G_FMT, &stUsbFmt) < 0)
    {
        ALOGE("get format failed\n");
        close(fdUsbCam);
        return HI_FAILURE;
    }
    else
    {
        ALOGE("After set attr:\r\nWidth = %d\n", stUsbFmt.fmt.pix.width);
        ALOGE("Height = %d\n", stUsbFmt.fmt.pix.height);
        ALOGE("Image size = %d\n", stUsbFmt.fmt.pix.sizeimage);
        ALOGE("pixelformat = %d\n", stUsbFmt.fmt.pix.pixelformat);
        if (V4L2_PIX_FMT_MJPEG == stUsbFmt.fmt.pix.pixelformat)
        {
            ALOGE("V4L2_PIX_FMT_MJPEG\r\n");
        }
        else if (V4L2_PIX_FMT_YUYV == stUsbFmt.fmt.pix.pixelformat)
        {
            ALOGE("V4L2_PIX_FMT_YUYV\r\n");
        }
        else
        {
            ALOGE("fmt unknown\r\n");
        }

        ALOGE("\n");
    }

    setfps = (struct v4l2_streamparm *)calloc(1, sizeof(struct v4l2_streamparm));
    if (HI_NULL == setfps)
    {
        ALOGE("calloc memory failed, %d, %s\n", __LINE__, __FUNCTION__);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    memset(setfps, 0, sizeof(struct v4l2_streamparm));
    setfps->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    s32Ret = ioctl(fdUsbCam, VIDIOC_G_PARM, setfps);
    if (s32Ret == 0)
    {
        ALOGE("\n  Frame rate:   %u/%u\n",
              setfps->parm.capture.timeperframe.denominator,
              setfps->parm.capture.timeperframe.numerator
        );
    }
    else
    {
        perror("Unable to read out current frame rate");
        free(setfps);
        close(fdUsbCam);
        return HI_FAILURE;
    }

    if ((setfps->parm.capture.timeperframe.numerator == 1)
        && (setfps->parm.capture.timeperframe.denominator == fps))
    {
        ; /* OK, fps is aready the value we want */
    }
    else
    {
        /* set frame rate */
        setfps->parm.capture.timeperframe.numerator   = 1;
        setfps->parm.capture.timeperframe.denominator = fps;
        s32Ret = ioctl(fdUsbCam, VIDIOC_S_PARM, setfps);
        if (HI_FAILURE == s32Ret)
        {
            perror("Unable to set frame rate");
            free(setfps);
            close(fdUsbCam);
            return HI_FAILURE;
        }

        s32Ret = ioctl(fdUsbCam, VIDIOC_G_PARM, setfps);
        if (s32Ret == 0)
        {
            if ((setfps->parm.capture.timeperframe.numerator != 1)
                || (setfps->parm.capture.timeperframe.denominator != fps))
            {
                ALOGE("\n  Frame rate:   %u/%u fps (requested frame rate %u fps is "
                      "not supported by device)\n",
                      setfps->parm.capture.timeperframe.denominator,
                      setfps->parm.capture.timeperframe.numerator,
                      fps);
            }
            else
            {
                ALOGE("\n  Frame rate:   %d fps\n", fps);
            }
        }
        else
        {
            perror("Unable to read out current frame rate");
            free(setfps);
            close(fdUsbCam);
            return HI_FAILURE;
        }
    }

    ALOGE("\nUSB CAM's output mode: %d \n", setfps->parm.output.outputmode);

    pArgs->UsbCamFd = fdUsbCam;

    return HI_SUCCESS;
}

static HI_U32 UsbCamDeinit(USB_CAM_THREAD_ARG_S *pArgs)
{
    close(pArgs->UsbCamFd);

    ALOGE(" Deinit V4L2 \n");

    return HI_SUCCESS;
}

void* USB_ScheduleCheckPlug(void* args)
{
    HI_S32 s32Ret;
    struct v4l2_format stUsbFmt;
    HI_U32 fail_cnt = 0;
    HI_UNF_VP_SOURCE_ATTR_S stSrcAttr;

    memset(&stSrcAttr, 0, sizeof(HI_UNF_VP_SOURCE_ATTR_S));
    USB_CAM_THREAD_ARG_S *pArgs = (USB_CAM_THREAD_ARG_S*)args;
    HI_HANDLE hVP = pArgs->hVP;

    while (!g_bUSBCamStop)
    {
        /*check usb*/
        memset(&stUsbFmt, 0, sizeof(struct v4l2_format));
        stUsbFmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        s32Ret = ioctl(pArgs->UsbCamFd, VIDIOC_G_FMT, &stUsbFmt);
        if (s32Ret < 0)
        {
            usleep(10 * 1000);
            fail_cnt++;
            if (fail_cnt >= 300)
            {
                if (g_UsbPlugFlag)
                {
                    HI_UNF_VP_StopRemote(hVP, HI_UNF_VP_RMT_MODE_SEND);
                    HI_UNF_VP_StopPreView(hVP);
                    HI_UNF_VP_DetachSource(hVP);
                    g_UsbPlugFlag = HI_FALSE;
                }

                UsbCamDeinit(pArgs);

                if (HI_SUCCESS == UsbCamInit(pArgs))
                {
                    stSrcAttr.enSrcMode = HI_UNF_VP_SRC_MODE_USBCAM;
                    stSrcAttr.hSrc = pArgs->UsbCamFd;
                    stSrcAttr.u32VIBufNum = g_u32BufCnt;
                    HI_UNF_VP_AttachSource(hVP, &stSrcAttr);
                    HI_UNF_VP_StartPreView(hVP);
                    HI_UNF_VP_StartRemote(hVP, HI_UNF_VP_RMT_MODE_SEND);
                    g_UsbPlugFlag = HI_TRUE;
                }

                fail_cnt = 0;
            }

            continue;
        }
        else
        {
            usleep(10 * 1000);
            fail_cnt = 0;
        }
    }

    return NULL;
}

static HI_S32 Checkipaddr(HI_BOOL bIpv4, const HI_CHAR *ipaddr)
{
    struct sockaddr_in stIpv4Attr;
    struct sockaddr_in6 stIpv6Attr;

    if (bIpv4)
    {
        return inet_pton(AF_INET, ipaddr, (void *)&stIpv4Attr.sin_addr);
    }
    else
    {
        return inet_pton(AF_INET6, ipaddr, (void *)&stIpv6Attr.sin6_addr);
    }
}

static HI_S32 IpaddrCharToU8(const HI_CHAR *ipaddr, HI_U8 *getaddr)
{
    char cinput[20];
    char *input;
    int len;
    HI_U32 getU32, totalpoint = 0;

    if (HI_NULL == ipaddr)
    {
        return -1;
    }

    len = strlen(ipaddr);
    memcpy(cinput, ipaddr, len);
    cinput[len] = '\0';
    input  = cinput;
    getU32 = 0;
    if ('\n' == *input)
    {
        return -1;
    }

    while ('\n' != *input)
    {
        if (('0' <= *input) && ('9' >= *input))
        {
            getU32 = (getU32 * 10) + (*input++ - 0x30);
            if (getU32 > 255)
            {
                return -1;
            }
        }
        else if ('.' == *input)
        {
            if ((totalpoint > 3) || !getU32)
            {
                return -1;
            }

            getaddr[totalpoint++] = (HI_U8)getU32;
            getU32 = 0;
            input++;
        }
        else
        {
            break;
        }
    }

    if ((totalpoint != 3) || !getU32)
    {
        return -1;
    }

    getaddr[totalpoint] = (HI_U8)getU32;
    ALOGE("get int %d, store getaddr %d", getU32, getaddr[totalpoint]);
    return 0;
}

#if 1

/****************************MCE Common Interface********************************************/
HI_S32 HIADP_MCE_Exit(HI_VOID)
{
    HI_S32 Ret;
    HI_UNF_MCE_STOPPARM_S stStop;

    Ret = HI_UNF_MCE_Init(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        ALOGE("call HI_UNF_MCE_Init failed, Ret=%#x!\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_MCE_ClearLogo();
    if (HI_SUCCESS != Ret)
    {
        ALOGE("call HI_UNF_MCE_ClearLogo failed, Ret=%#x!\n", Ret);
        return Ret;
    }

    stStop.enStopMode = HI_UNF_AVPLAY_STOP_MODE_STILL;
    stStop.enCtrlMode = HI_UNF_MCE_PLAYCTRL_BY_TIME;
    stStop.u32PlayTimeMs = 0;
    Ret = HI_UNF_MCE_Stop(&stStop);
    if (HI_SUCCESS != Ret)
    {
        ALOGE("call HI_UNF_MCE_Stop failed, Ret=%#x!\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_MCE_Exit(HI_NULL);
    if (HI_SUCCESS != Ret)
    {
        ALOGE("call HI_UNF_MCE_Exit failed, Ret=%#x!\n", Ret);
        return Ret;
    }

    HI_UNF_MCE_DeInit();

    return HI_SUCCESS;
}

/****************************VO Common Interface********************************************/
static HI_S32 HIADP_VO_Init(HI_UNF_VO_DEV_MODE_E enDevMode)
{
    HI_S32 Ret;

    Ret = HI_UNF_VO_Init(enDevMode);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_VO_Init failed.\n");
        return Ret;
    }

 #if 0
    Ret = HI_UNF_VO_Open(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_VO_Open failed.\n");
        HI_UNF_VO_DeInit();
        return Ret;
    }
 #endif

    return HI_SUCCESS;
}

static HI_S32 HIADP_VO_DeInit()
{
    HI_S32 Ret;

 #if 0
    Ret = HI_UNF_VO_Close(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_VO_Close failed.\n");
        return Ret;
    }
 #endif

    Ret = HI_UNF_VO_DeInit();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_VO_DeInit failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 HIADP_VO_CreatWin(HI_RECT_S *pstWinRect, HI_HANDLE *phWin)
{
    HI_S32 Ret;
    HI_UNF_WINDOW_ATTR_S WinAttr;

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    WinAttr.enDisp   = HI_UNF_DISPLAY1;
    WinAttr.bVirtual = HI_FALSE;
    WinAttr.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    WinAttr.stWinAspectAttr.u32UserAspectWidth  = 0;
    WinAttr.stWinAspectAttr.u32UserAspectHeight = 0;
    WinAttr.bUseCropRect = HI_FALSE;
    WinAttr.stInputRect.s32X = 0;
    WinAttr.stInputRect.s32Y = 0;
    WinAttr.stInputRect.s32Width  = 0;
    WinAttr.stInputRect.s32Height = 0;

    if (HI_NULL == pstWinRect)
    {
        memset(&WinAttr.stOutputRect, 0x0, sizeof(HI_RECT_S));
    }
    else
    {
        memcpy(&WinAttr.stOutputRect, pstWinRect, sizeof(HI_RECT_S));
    }

    Ret = HI_UNF_VO_CreateWindow(&WinAttr, phWin);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_VO_CreateWindow failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 HIADP_VO_CreatWinExt(HI_RECT_S *pstWinRect, HI_HANDLE *phWin, HI_BOOL bVirtScreen)
{
    HI_S32 Ret;
    HI_UNF_WINDOW_ATTR_S WinAttr;

    memset(&WinAttr, 0, sizeof(HI_UNF_WINDOW_ATTR_S));
    WinAttr.enDisp   = HI_UNF_DISPLAY1;
    WinAttr.bVirtual = HI_FALSE;
    WinAttr.stWinAspectAttr.enAspectCvrs = HI_UNF_VO_ASPECT_CVRS_IGNORE;
    WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    WinAttr.stWinAspectAttr.u32UserAspectWidth  = 0;
    WinAttr.stWinAspectAttr.u32UserAspectHeight = 0;
    WinAttr.bUseCropRect = HI_FALSE;
    WinAttr.stInputRect.s32X = 0;
    WinAttr.stInputRect.s32Y = 0;
    WinAttr.stInputRect.s32Width  = 0;
    WinAttr.stInputRect.s32Height = 0;

    if (HI_NULL == pstWinRect)
    {
        memset(&WinAttr.stOutputRect, 0x0, sizeof(HI_RECT_S));
    }
    else
    {
        memcpy(&WinAttr.stOutputRect, pstWinRect, sizeof(HI_RECT_S));
    }

    Ret = HI_UNF_VO_CreateWindowExt(&WinAttr, phWin, bVirtScreen);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_VO_CreateWindowExt failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

/****************************DISP Common Interface********************************************/
static HI_S32 HIADP_Disp_Init(HI_UNF_ENC_FMT_E enFormat)
{
    HI_S32 Ret;
    HI_UNF_DISP_BG_COLOR_S BgColor;
    HI_UNF_DISP_INTF_S stIntf[2];
    HI_UNF_DISP_OFFSET_S offset;

    Ret = HI_UNF_DISP_Init();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Init failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    /* set display1 interface */
    stIntf[0].enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
    stIntf[0].unIntf.stYPbPr.u8DacY  = DAC_YPBPR_Y;
    stIntf[0].unIntf.stYPbPr.u8DacPb = DAC_YPBPR_PB;
    stIntf[0].unIntf.stYPbPr.u8DacPr = DAC_YPBPR_PR;
    stIntf[1].enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
    stIntf[1].unIntf.enHdmi = HI_UNF_HDMI_ID_0;
    Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &stIntf[0], 2);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_AttachIntf failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    /* set display0 interface */
    stIntf[0].enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
    stIntf[0].unIntf.stCVBS.u8Dac = DAC_CVBS;
    Ret = HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY0, &stIntf[0], 1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_AttachIntf failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    Ret = HI_UNF_DISP_Attach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Attach failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    /* set display1 format*/
    Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, enFormat);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_SetFormat failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    /* set display0 format*/
    if ((HI_UNF_ENC_FMT_1080P_60 == enFormat)
        || (HI_UNF_ENC_FMT_1080i_60 == enFormat)
        || (HI_UNF_ENC_FMT_720P_60 == enFormat)
        || (HI_UNF_ENC_FMT_480P_60 == enFormat)
        || (HI_UNF_ENC_FMT_NTSC == enFormat))
    {
        Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, HI_UNF_ENC_FMT_NTSC);
        if (HI_SUCCESS != Ret)
        {
            ALOGE("call HI_UNF_DISP_SetFormat failed, Ret=%#x.\n", Ret);
            HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
            HI_UNF_DISP_DeInit();
            return Ret;
        }
    }

    if ((HI_UNF_ENC_FMT_1080P_50 == enFormat)
        || (HI_UNF_ENC_FMT_1080i_50 == enFormat)
        || (HI_UNF_ENC_FMT_720P_50 == enFormat)
        || (HI_UNF_ENC_FMT_576P_50 == enFormat)
        || (HI_UNF_ENC_FMT_PAL == enFormat))
    {
        Ret = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, HI_UNF_ENC_FMT_PAL);
        if (HI_SUCCESS != Ret)
        {
            ALOGE("call HI_UNF_DISP_SetFormat failed, Ret=%#x.\n", Ret);
            HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
            HI_UNF_DISP_DeInit();
            return Ret;
        }
    }
#if 0
    Ret = HI_UNF_DISP_SetVirtualScreen(HI_UNF_DISPLAY1, 1280, 720);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_SetVirtualScreen failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }
#endif
    offset.u32Left = 0;
    offset.u32Top    = 0;
    offset.u32Right  = 0;
    offset.u32Bottom = 0;

    /*set display1 screen offset*/
    Ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY1, &offset);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_SetBgColor failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    /*set display0 screen offset*/
    Ret = HI_UNF_DISP_SetScreenOffset(HI_UNF_DISPLAY0, &offset);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_SetBgColor failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    BgColor.u8Red   = 0;
    BgColor.u8Green = 0;
    BgColor.u8Blue  = 0;
    Ret = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &BgColor);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_SetBgColor failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Open DISPLAY1 failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

    Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Open DISPLAY0 failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }

 #if 0
    Ret = HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, enFormat);
    if (HI_SUCCESS != Ret)
    {
        ALOGE("call HIADP_HDMI_Init failed, Ret=%#x.\n", Ret);
        HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
        HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
        HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
        HI_UNF_DISP_DeInit();
        return Ret;
    }
 #endif

    return HI_SUCCESS;
}

static HI_S32 HIADP_Disp_DeInit(HI_VOID)
{
    HI_S32 Ret;

    Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Close failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_DISP_Close(HI_UNF_DISPLAY0);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Close failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Detach failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    Ret = HI_UNF_DISP_DeInit();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_DeInit failed, Ret=%#x.\n", Ret);
        return Ret;
    }

    //HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);

    return HI_SUCCESS;
}

/*****************************************SOUND Common Interface************************************/
static HI_S32 HIADP_Snd_Init(HI_VOID)
{
    HI_S32 Ret;
    HI_UNF_SND_ATTR_S stAttr;

    Ret = HI_UNF_SND_Init();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_SND_Init failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_SND_GetDefaultOpenAttr failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_Open(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_SND_Open failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

static HI_S32 HIADP_Snd_DeInit(HI_VOID)
{
    HI_S32 Ret;

    Ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_SND_Close failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_DeInit();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_SND_DeInit failed.\n");
        return Ret;
    }

    return HI_SUCCESS;
}

#endif
static HI_S32 HIADP_GetWinHandle(HI_S32 lrwindow)
{
    HI_HANDLE hWin;

    if (1 == lrwindow)
    {
        hWin = hLocalWin;
    }
    else if (2 == lrwindow)
    {
        hWin = hRemoteWin;
    }
    else
    {
        hWin = HI_INVALID_HANDLE;
    }

    return hWin;
}

static HI_DOUBLE HIADP_GetPacketRate(HI_ADP_STATICS_E enVideoStatic)
{
    HI_DOUBLE dValue = -1;

    switch (enVideoStatic)
    {
    case PACKET_INRATE:
        dValue = g_u32InRate;
        break;
    case PACKET_OUTRATE:
        dValue = g_u32OutRate;
        break;
    default:
        break;
    }

    return dValue;
}

void* HIADP_VpSchedule_NetStatics(void* args)
{
    HI_S32 s32Ret;
    HI_UNF_VP_NET_STA_S stNetStatics;
    HI_HANDLE *hVP = (HI_HANDLE *)args;
    HI_U32 u32LstSysTime;
    HI_U32 u32CurSysTime;
    HI_U32 u32SysTimeDelta = 0;
    HI_U32 u32LstRecvPacketNum = 0;
    HI_U32 u32LstRecvBytes = 0;
    HI_U32 u32LstSendBytes = 0;
    HI_U32 u32DataDelta = 0;

    bHasVideoData = HI_FALSE;
    g_u32InRate  = 0;
    g_u32OutRate = 0;

    HI_SYS_GetTimeStampMs(&u32LstSysTime);

    while (!g_stopGet)
    {
        usleep(g_u32Span * 1000);
        if (g_stopGet)
        {
            break;
        }

        s32Ret = HI_UNF_VP_GetNetStatics(*hVP, &stNetStatics);
        if (HI_SUCCESS == s32Ret)
        {
            HI_SYS_GetTimeStampMs(&u32CurSysTime);
            if (u32CurSysTime > u32LstSysTime)
            {
                u32SysTimeDelta = u32CurSysTime - u32LstSysTime;
            }
            else
            {
                u32SysTimeDelta = SYS_MAX_VALUE - u32LstSysTime + u32CurSysTime;
            }

            if (u32SysTimeDelta < 1000)
            {
                u32SysTimeDelta = 1000;
            }

            u32LstSysTime = u32CurSysTime;

            /* calute inrate(bps)*/
            if (stNetStatics.u32RecvBytes > u32LstRecvBytes)
            {
                u32DataDelta = stNetStatics.u32RecvBytes - u32LstRecvBytes;
            }
            else
            {
                u32DataDelta = SYS_MAX_VALUE - u32LstRecvBytes + stNetStatics.u32RecvBytes;
            }

            u32LstRecvBytes = stNetStatics.u32RecvBytes;
            g_u32InRate = u32DataDelta / (u32SysTimeDelta / 1000) * 8;

            /* calute outrate(bps)*/
            if (stNetStatics.u32SendBytes > u32LstSendBytes)
            {
                u32DataDelta = stNetStatics.u32SendBytes - u32LstSendBytes;
            }
            else
            {
                u32DataDelta = SYS_MAX_VALUE - u32LstSendBytes + stNetStatics.u32SendBytes;
            }

            u32LstSendBytes = stNetStatics.u32SendBytes;
            g_u32OutRate = u32DataDelta / (u32SysTimeDelta / 1000) * 8;

            /* Check whether has video packet */
            if (stNetStatics.u32RecvPacketNum > u32LstRecvPacketNum)
            {
                u32DataDelta = stNetStatics.u32RecvPacketNum - u32LstRecvPacketNum;
            }
            else
            {
                u32DataDelta = SYS_MAX_VALUE - u32LstRecvPacketNum + stNetStatics.u32RecvPacketNum;
            }

            u32LstRecvPacketNum = stNetStatics.u32RecvPacketNum;
            if ((u32DataDelta > 0) && (SYS_MAX_VALUE != u32DataDelta))
            {
                bHasVideoData = HI_TRUE;
            }
            else
            {
                bHasVideoData = HI_FALSE;
            }
        }
    }

    return NULL;
}

void* HIADP_VoipSchedule_NetStatics(void* args)
{
    HI_S32 ret;
    HI_HANDLE hVoipHandle;
    HI_U32 u32LstSysTime;
    HI_U32 u32CurSysTime;
    HI_U32 u32SysTimeDelta = 0;
    HI_U32 u32LstRecvPacketNum = 0;
    HI_U32 u32LstRecvBytes = 0;
    HI_U32 u32LstSendBytes = 0;
    HI_U32 u32DataDelta = 0;
    HI_UNF_VOIP_RTCP_STATIC_INFO_S stRtcpInfo;

    bHasAudioData   = HI_FALSE;
    g_u32AudInRate  = 0;
    g_u32AudOutRate = 0;
    hVoipHandle = *((HI_HANDLE *)args);

    while (!g_stopAudGet)
    {
        usleep(g_u32AudSpan * 1000);
        if (g_stopAudGet)
        {
            break;
        }

        memset(&stRtcpInfo, 0, sizeof(HI_UNF_VOIP_RTCP_STATIC_INFO_S));
        ret = HI_UNF_VOIP_GetRtcpStaticInfo(hVoipHandle, &stRtcpInfo);

        if (ret == HI_SUCCESS)
        {
            HI_SYS_GetTimeStampMs(&u32CurSysTime);
            if (u32CurSysTime > u32LstSysTime)
            {
                u32SysTimeDelta = u32CurSysTime - u32LstSysTime;
            }
            else
            {
                u32SysTimeDelta = SYS_MAX_VALUE - u32LstSysTime + u32CurSysTime;
            }

            if (u32SysTimeDelta < 1000)
            {
                u32SysTimeDelta = 1000;
            }

            u32LstSysTime = u32CurSysTime;

            /* calute inrate(bps)*/
            if (stRtcpInfo.u32RecBytes > u32LstRecvBytes)
            {
                u32DataDelta = stRtcpInfo.u32RecBytes - u32LstRecvBytes;
            }
            else
            {
                u32DataDelta = SYS_MAX_VALUE - u32LstRecvBytes + stRtcpInfo.u32RecBytes;
            }

            u32LstRecvBytes = stRtcpInfo.u32RecBytes;
            g_u32AudInRate = u32DataDelta / (u32SysTimeDelta / 1000) * 8;

            /* calute outrate(bps)*/
            if (stRtcpInfo.u32SendBytes > u32LstSendBytes)
            {
                u32DataDelta = stRtcpInfo.u32SendBytes - u32LstSendBytes;
            }
            else
            {
                u32DataDelta = SYS_MAX_VALUE - u32LstSendBytes + stRtcpInfo.u32SendBytes;
            }

            u32LstSendBytes = stRtcpInfo.u32SendBytes;
            g_u32AudOutRate = u32DataDelta / (u32SysTimeDelta / 1000) * 8;

            /* Check whether has video packet */
            if (stRtcpInfo.u32RecPacketNum > u32LstRecvPacketNum)
            {
                u32DataDelta = stRtcpInfo.u32RecPacketNum - u32LstRecvPacketNum;
            }
            else
            {
                u32DataDelta = SYS_MAX_VALUE - u32LstRecvPacketNum + stRtcpInfo.u32RecPacketNum;
            }

            u32LstRecvPacketNum = stRtcpInfo.u32RecPacketNum;
            if ((u32DataDelta > 0) && (SYS_MAX_VALUE != u32DataDelta))
            {
                bHasAudioData = HI_TRUE;
            }
            else
            {
                bHasAudioData = HI_FALSE;
            }
        }
    }

    return NULL;
}

HI_S32 Hi_Adp_Video_Init(HI_VOID)
{
    HI_S32 ret = 0;

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_INITED))
    {
        ret  = HI_SYS_Init();
        ret |= HIADP_MCE_Exit();
        ret |= HI_UNF_AVPLAY_Init();
        ret |= HI_UNF_VI_Init();
        ret |= HI_UNF_VENC_Init();
        ret |= HI_UNF_VP_Init();
        if (HI_SUCCESS != ret)
        {
            ALOGE("Hi_Adp_Av_Init failed\n");
            return ret;
        }

        g_PhonePlayer_VideoState |= HI_ENGINE_INITED;
    }

    ALOGE("Hi_Adp_Av_Init OK\n");

    return ret;
}

HI_S32 Hi_Adp_Video_Deinit(HI_VOID)
{
    HI_S32 ret = 0;

    if (g_PhonePlayer_VideoState & HI_ENGINE_STARTED)
    {
        ALOGE("Illegal state, Video should be stopped firstly\n");
        return HI_FAILURE;
    }

    if (g_PhonePlayer_VideoState & HI_ENGINE_INITED)
    {
        ret  = HI_UNF_VP_DeInit();
        ret |= HI_UNF_AVPLAY_DeInit();
        ret |= HI_UNF_VI_DeInit();
        ret |= HI_UNF_VENC_DeInit();
        ret |= HI_SYS_DeInit();
        if (HI_SUCCESS != ret)
        {
            ALOGE("Hi_Adp_Video_Deinit failed\n");
            return ret;
        }

        g_PhonePlayer_VideoState &= ~HI_ENGINE_INITED;
    }

    ALOGE("Hi_Adp_Video_Deinit OK\n");

    return ret;
}

HI_S32 Hi_Adp_Video_Open(HI_RECT_S stLocalWinRect, HI_RECT_S stRemotewinRect, HI_ADP_RESOLUTION_E eSetRes,
                         HI_S32 s32VoFormat,
                         HI_U32 u32CapFmRate)
{
    HI_S32 ret = 0;
    HI_UNF_ENC_FMT_E eSetFormat;

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_OPENED))
    {
        if ((s32VoFormat < 0) || (s32VoFormat > 3))
        {
            ALOGE("input wrong disp format %d\n", s32VoFormat);
            return -1;
        }

        switch (s32VoFormat)
        {
        case 0:
            eSetFormat = HI_UNF_ENC_FMT_720P_60;
            break;
        case 1:
            eSetFormat = HI_UNF_ENC_FMT_1080P_60;
            break;
        case 2:
            eSetFormat = HI_UNF_ENC_FMT_NTSC;
            break;
        case 3:
            eSetFormat = HI_UNF_ENC_FMT_VESA_1280X720_60;
            break;                                                         //TODO: need to confirm which type, HI_UNF_DISP_SetCustomTiming  by y00190777
        default:
            eSetFormat = HI_UNF_ENC_FMT_PAL;
            break;
        }
#if 0
        ret = HIADP_Disp_Init(eSetFormat);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HIADP_Disp_Init failed.\n");
            return ret;
        }
#endif
        ret  = HIADP_VO_Init(HI_UNF_VO_DEV_MODE_NORMAL);
        ret |= HIADP_VO_CreatWinExt(&stRemotewinRect, &hRemoteWin, HI_TRUE);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HIADP_VO_CreatWinExt failed.\n");
            HIADP_VO_DeInit();
           // HIADP_Disp_DeInit();
            return ret;
        }

        ret = HIADP_VO_CreatWinExt(&stLocalWinRect, &hLocalWin, HI_TRUE);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HIADP_VO_CreatWinExt failed.\n");
            HI_UNF_VO_DestroyWindow(hRemoteWin);
            hRemoteWin = HI_INVALID_HANDLE;
            HIADP_VO_DeInit();
           // HIADP_Disp_DeInit();
            return ret;
        }

        ret = HI_UNF_VO_SetWindowZorder(hLocalWin, HI_LAYER_ZORDER_MOVETOP);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VO_SetWindowZorder failed.ret = 0x%x", ret);
        }

        switch (eSetRes)
        {
        case HI_RESOLUTION_176_144:
            g_SetUsbCamWidth  = 176;
            g_SetUsbCamHeight = 144;
            g_u32CamFormat = 1;
            break;
        case HI_RESOLUTION_320_240:
            g_SetUsbCamWidth  = 320;
            g_SetUsbCamHeight = 240;
            g_u32CamFormat = 1;
            break;
        case HI_RESOLUTION_352_288:
            g_SetUsbCamWidth  = 352;
            g_SetUsbCamHeight = 288;
            g_u32CamFormat = 1;
            break;
        case HI_RESOLUTION_640_480:
            g_SetUsbCamWidth  = 640;
            g_SetUsbCamHeight = 480;
            g_u32CamFormat = 1;
            break;

            //case HI_RESOLUTION_720_576: g_SetUsbCamWidth = 720;g_SetUsbCamHeight = 576;g_u32CamFormat = 1;break;
        case HI_RESOLUTION_1280_720:
            g_SetUsbCamWidth  = 1280;
            g_SetUsbCamHeight = 720;
            g_u32CamFormat = 0;
            break;
        case HI_RESOLUTION_1920_1080:
            g_SetUsbCamWidth  = 1920;
            g_SetUsbCamHeight = 1080;
            g_u32CamFormat = 0;
            break;
        default:
            ALOGE("Wrong input resolution %d\n", eSetRes);
            break;
        }

        if ((u32CapFmRate > 30) || (u32CapFmRate < 5))
        {
            g_SetUsbCamFps = 30;
        }
        else
        {
            g_SetUsbCamFps = u32CapFmRate;
        }

        g_PhonePlayer_VideoState |= HI_ENGINE_OPENED;
    }

    ALOGE("Hi_Adp_Video_Open OK\n");

    return ret;
}

HI_S32 Hi_Adp_Video_Close()
{
    HI_S32 ret = 0;

    if (g_PhonePlayer_VideoState & HI_ENGINE_STARTED)
    {
        ALOGE("Illegal state, Video should be stopped firstly\n");
        return HI_FAILURE;
    }

    if (g_PhonePlayer_VideoState & HI_ENGINE_OPENED)
    {
        HI_UNF_VO_DestroyWindow(hLocalWin);
        hLocalWin = HI_INVALID_HANDLE;
        HI_UNF_VO_DestroyWindow(hRemoteWin);
        hRemoteWin = HI_INVALID_HANDLE;
        HIADP_VO_DeInit();
#if 0
        HIADP_Disp_DeInit();
#endif
        g_PhonePlayer_VideoState &= ~HI_ENGINE_OPENED;
    }

    ALOGE("Hi_Adp_Video_Close OK\n");

    return ret;
}

HI_S32 Hi_Adp_Video_Start(const HI_CHAR *pLoacalIp, HI_S32 s32LoalPort, const HI_CHAR *pRemoteIp, HI_S32 s32RemotePort,
                          HI_S32 s32EncFR, HI_S32 s32Payload, HI_S32 s32TargetBR, HI_S32 s32Gop)
{
    HI_S32 ret = 0;
    HI_UNF_VP_ATTR_S stDefAttr;
    HI_UNF_VP_SOURCE_ATTR_S stSrcAttr;
    HI_UNF_VP_RTCP_CFG_S stRtcpCfg;
    HI_BOOL bAf_inet; // 1-ipv4, 0-ipv6

    if (!((g_PhonePlayer_VideoState & HI_ENGINE_INITED) || (g_PhonePlayer_VideoState & HI_ENGINE_OPENED)))
    {
        ALOGE("Illegal state, check whether Video has been inited\n");
        return HI_FAILURE;
    }

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_STARTED))
    {
		ALOGE("Payload %d, VENC_PROFILE %d, SPLIT_SIZE %d, RECVBUF_SIZE %d, RECVBUF_NUM %d, SORT_DEPTH %d, IsIPv4 %d.\n", 
			s32Payload, g_VideoOption[HI_OPTIONAL_CONFIG_VENC_PROFILE], g_VideoOption[HI_OPTIONAL_CONFIG_RTP_SPLIT_SIZE], 
			g_VideoOption[HI_OPTIONAL_CONFIG_RTP_RECVBUF_SIZE],g_VideoOption[HI_OPTIONAL_CONFIG_RTP_RECVBUF_NUM],
			g_VideoOption[HI_OPTIONAL_CONFIG_RTP_SORT_DEPTH],g_VideoOption[HI_OPTIONAL_CONFIG_NET_IP_TYPE]);

		memset(&stSrcAttr, 0, sizeof(HI_UNF_VP_SOURCE_ATTR_S));

		bAf_inet = (HI_BOOL)g_VideoOption[HI_OPTIONAL_CONFIG_NET_IP_TYPE];  // 1-ipv4, 0-ipv6

		if ((1 != Checkipaddr(bAf_inet, pLoacalIp))
            || (1 != Checkipaddr(bAf_inet, pRemoteIp))
        )

        {
            ALOGE("wrong ip format localip %s remoteip %s\n", pLoacalIp, pRemoteIp);
            return HI_FAILURE;
        }

        switch (g_u32CamFormat)
        {
        case 0:
            g_stUSBCamArgs.u32USBCamFmt = V4L2_PIX_FMT_MJPEG;
            break;

        case 1:
            g_stUSBCamArgs.u32USBCamFmt = V4L2_PIX_FMT_YUYV;
            break;
        default:
            g_stUSBCamArgs.u32USBCamFmt = V4L2_PIX_FMT_YUYV;
            break;
        }

        ret = UsbCamInit(&g_stUSBCamArgs);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call UsbCamInit failed.\n");
            return ret;
        }

        memset(&stDefAttr, 0, sizeof(HI_UNF_VP_ATTR_S));
        ret = HI_UNF_VP_GetDefaultAttr(&stDefAttr);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_GetDefaultAttr failed.\n");
            goto ERR0;
        }

        stDefAttr.stRtpAttr.u32PayLoadType = s32Payload;
		stDefAttr.stRtpAttr.u32SplitSize = g_VideoOption[HI_OPTIONAL_CONFIG_RTP_SPLIT_SIZE];
		stDefAttr.stRtpAttr.u32RecvBufSize = g_VideoOption[HI_OPTIONAL_CONFIG_RTP_RECVBUF_SIZE];
		stDefAttr.stRtpAttr.u32RecvBufNum = g_VideoOption[HI_OPTIONAL_CONFIG_RTP_RECVBUF_NUM];
		stDefAttr.stRtpAttr.u32SortDepth = g_VideoOption[HI_OPTIONAL_CONFIG_RTP_SORT_DEPTH];

		stDefAttr.stVencAttr.enVencProfile = (HI_UNF_H264_PROFILE_E)g_VideoOption[HI_OPTIONAL_CONFIG_VENC_PROFILE];
        stDefAttr.stVencAttr.enVencType = HI_UNF_VCODEC_TYPE_H264;
        stDefAttr.stVencAttr.u32Width  = g_SetUsbCamWidth / 4 * 4;
        stDefAttr.stVencAttr.u32Height = g_SetUsbCamHeight / 4 * 4;
        stDefAttr.stVencAttr.u32InputFrmRate  = g_SetUsbCamFps;
        stDefAttr.stVencAttr.u32TargetFrmRate = s32EncFR;
        stDefAttr.stVencAttr.u32TargetBitRate = s32TargetBR;
        stDefAttr.stVencAttr.u32Gop = s32Gop;

        if (stDefAttr.stVencAttr.u32Width > 1280)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
            stDefAttr.stVencAttr.u32StrmBufSize = 1920 * 1080 * 2;
        }
        else if (stDefAttr.stVencAttr.u32Width > 720)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_720P;
            stDefAttr.stVencAttr.u32StrmBufSize = 1280 * 720 * 2;
        }
        else if (stDefAttr.stVencAttr.u32Width > 352)
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_D1;
            stDefAttr.stVencAttr.u32StrmBufSize = 720 * 576 * 2;
        }
        else
        {
            stDefAttr.stVencAttr.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_CIF;
            stDefAttr.stVencAttr.u32StrmBufSize = 352 * 288 * 2;
        }

        stDefAttr.enDecType = HI_UNF_VCODEC_TYPE_H264;
        stDefAttr.bIsIpv4 = bAf_inet;
        if (stDefAttr.bIsIpv4)
        {
            stDefAttr.stLocalNetAttr.stIpv4Attr.sin_family = AF_INET;
            inet_pton(AF_INET, pLoacalIp, (void *)&stDefAttr.stLocalNetAttr.stIpv4Attr.sin_addr);
            stDefAttr.stLocalNetAttr.stIpv4Attr.sin_port = htons(s32LoalPort);
            stDefAttr.stRemoteNetAttr.stIpv4Attr.sin_family = AF_INET;
            inet_pton(AF_INET, pRemoteIp, (void *)&stDefAttr.stRemoteNetAttr.stIpv4Attr.sin_addr);
            stDefAttr.stRemoteNetAttr.stIpv4Attr.sin_port = htons(s32RemotePort);
        }
        else
        {
            stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_family = AF_INET6;
            inet_pton(AF_INET6, pLoacalIp, (void *)&stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_addr);
            stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_scope_id = if_nametoindex(DFLT_SCOPE_ID);
            stDefAttr.stLocalNetAttr.stIpv6Attr.sin6_port = htons(s32LoalPort);
            stDefAttr.stRemoteNetAttr.stIpv6Attr.sin6_family = AF_INET6;
            inet_pton(AF_INET6, pRemoteIp, (void *)&stDefAttr.stRemoteNetAttr.stIpv6Attr.sin6_addr);
            stDefAttr.stRemoteNetAttr.stIpv6Attr.sin6_port = htons(s32RemotePort);
        }

        ret = HI_UNF_VP_Create(&stDefAttr, &hVP);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_Create failed.\n");
            goto ERR0;
        }

        stRtcpCfg.u32EnableFlag   = 1;
        stRtcpCfg.u32SendInterval = g_u32Span;
        ret = HI_UNF_VP_ConfigRtcp(hVP, &stRtcpCfg);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_ConfigRtcp failed.\n");
            goto ERR1;
        }

        stSrcAttr.enSrcMode = HI_UNF_VP_SRC_MODE_USBCAM;
        stSrcAttr.hSrc = g_stUSBCamArgs.UsbCamFd;
        stSrcAttr.u32VIBufNum = g_u32BufCnt;
        ret = HI_UNF_VP_AttachSource(hVP, &stSrcAttr);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_AttachSource failed.\n");
            goto ERR1;
        }

        g_UsbPlugFlag = HI_TRUE;

        ret = HI_UNF_VP_AttachLocalWin(hVP, hLocalWin);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_AttachLocalWin failed.\n");
            goto ERR2;
        }

        ret |= HI_UNF_VP_AttachRemoteWin(hVP, hRemoteWin);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_AttachRemoteWin failed.\n");
            goto ERR3;
        }

        ret = HI_UNF_VP_Start(hVP);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call HI_UNF_VP_Start failed.\n");
            goto ERR4;
        }

        g_stUSBCamArgs.hVP = hVP;
        g_bUSBCamStop = HI_FALSE;
        pthread_create(&g_threadUSBCam, HI_NULL, USB_ScheduleCheckPlug, (void*)(&g_stUSBCamArgs));

        g_stopGet = 0;
        pthread_create(&g_threadStatics, HI_NULL, HIADP_VpSchedule_NetStatics, (void*)(&hVP));

        g_PhonePlayer_VideoState |= HI_ENGINE_STARTED;
    }

    ALOGE("Hi_Adp_Video_Start OK.\n");

    return ret;

ERR4:
    HI_UNF_VP_Stop(hVP);
    HI_UNF_VP_DetachRemoteWin(hVP);

ERR3:
    HI_UNF_VP_DetachLocalWin(hVP);

ERR2:
    if (g_UsbPlugFlag)
    {
        HI_UNF_VP_DetachSource(hVP);
        g_UsbPlugFlag = HI_FALSE;
    }

ERR1:
    HI_UNF_VP_Destroy(hVP);

ERR0:
    UsbCamDeinit(&g_stUSBCamArgs);

    ALOGE("Hi_Adp_Video_Start failed.\n");
    return ret;
}

HI_S32 Hi_Adp_Video_Stop(HI_VOID)
{
    HI_S32 ret = 0;

    if (g_PhonePlayer_VideoState & HI_ENGINE_STARTED)
    {
        g_stopGet = 1;
        pthread_join(g_threadStatics, NULL);
        bHasVideoData = HI_FALSE;
        g_u32InRate  = 0;
        g_u32OutRate = 0;

        g_bUSBCamStop = HI_TRUE;
        pthread_join(g_threadUSBCam, NULL);

        HI_UNF_VP_Stop(hVP);

        HI_UNF_VP_DetachRemoteWin(hVP);

        HI_UNF_VP_DetachLocalWin(hVP);

        if (g_UsbPlugFlag)
        {
            HI_UNF_VP_DetachSource(hVP);
            g_UsbPlugFlag = HI_FALSE;
        }

        HI_UNF_VP_Destroy(hVP);
        hVP = HI_INVALID_HANDLE;
        UsbCamDeinit(&g_stUSBCamArgs);

        g_PhonePlayer_VideoState &= ~HI_ENGINE_STARTED;
    }

    ALOGE("Hi_Adp_Video_Stop OK.\n");

    return ret;
}

HI_S32 Hi_Adp_Video_SetCheckSpan(HI_S32 s32Span)
{
    HI_S32 ret;
    HI_UNF_VP_RTCP_CFG_S stRtcpCfg;

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_STARTED))
    {
        ALOGE("Illegal state, check whether Video has been started\n");
        return HI_FAILURE;
    }

    stRtcpCfg.u32EnableFlag   = 1;
    stRtcpCfg.u32SendInterval = s32Span;
    ret = HI_UNF_VP_ConfigRtcp(hVP, &stRtcpCfg);
    if (HI_SUCCESS != ret)
    {
        ALOGE("HI_UNF_VP_ConfigRtcp failed.\n");
        return ret;
    }

    g_u32Span = s32Span;

    ALOGE("Hi_Adp_Video_SetCheckSpan OK.\n");
    return ret;
}

HI_S32 Hi_Adp_Video_CheckPacket()
{
    return bHasVideoData;
}

HI_DOUBLE Hi_Adp_Video_GetVideoStatics(HI_ADP_STATICS_E enVideoStatic)
{
    HI_S32 ret;
    HI_DOUBLE dValue = -1;
    HI_UNF_VP_NET_STA_S stVideoSta;
    HI_HANDLE hAvplay = HI_INVALID_HANDLE;
    HI_UNF_AVPLAY_STREAM_INFO_S stStreamInfo;

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_STARTED))
    {
        ALOGE("Illegal state, check whether Video has been started\n");
        return HI_FAILURE;
    }

    switch (enVideoStatic)
    {
    case PACKET_INRATE:
    case PACKET_OUTRATE:
        dValue = HIADP_GetPacketRate(enVideoStatic);
        break;
    case PACKET_INLOSTRATE:
        ret = HI_UNF_VP_GetNetStatics(hVP, &stVideoSta);
        if (HI_SUCCESS == ret)
        {
            dValue = (HI_DOUBLE)stVideoSta.stRecvInfo.u32LossFraction;
        }

        break;
    case PACKET_INDELAYTIME:
        ret = HI_UNF_VP_GetNetStatics(hVP, &stVideoSta);
        if (HI_SUCCESS == ret)
        {
            dValue = (HI_DOUBLE)stVideoSta.stRecvInfo.u32Delay;
        }

        break;
    case VIDEO_WIDTH:
        ret  = HI_UNF_VP_GetAvplayHandle(hVP, &hAvplay);
        ret |= HI_UNF_AVPLAY_GetStreamInfo(hAvplay, &stStreamInfo);
        if (HI_SUCCESS == ret)
        {
            dValue = (HI_DOUBLE)stStreamInfo.stVidStreamInfo.u32Width;
        }

        break;
    case VIDEO_HEIGHT:
        ret  = HI_UNF_VP_GetAvplayHandle(hVP, &hAvplay);
        ret |= HI_UNF_AVPLAY_GetStreamInfo(hAvplay, &stStreamInfo);
        if (HI_SUCCESS == ret)
        {
            dValue = (HI_DOUBLE)stStreamInfo.stVidStreamInfo.u32Height;
        }

        break;
    default:
        dValue = -1;
        break;
    }

    return dValue;
}

HI_S32 Hi_Adp_Video_EnableLocal(HI_BOOL bEnable)
{
    HI_S32 ret;

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_STARTED))
    {
        ALOGE("Illegal state, check whether Video has been started\n");
        return HI_FAILURE;
    }

    if (bEnable)
    {
        ret  = HI_UNF_VP_StartPreView(hVP);
        ret |= HI_UNF_VP_StartRemote(hVP, HI_UNF_VP_RMT_MODE_SEND);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call Hi_Adp_Video_EnableLocal failed.\n");
        }
    }
    else
    {
        ret  = HI_UNF_VP_StopRemote(hVP, HI_UNF_VP_RMT_MODE_SEND);
        ret |= HI_UNF_VP_StopPreView(hVP);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call Hi_Adp_Video_EnableLocal failed.\n");
        }
    }

    ALOGE("Hi_Adp_Video_EnableLocal OK.\n");

    return ret;
}

HI_S32 Hi_Adp_Video_EnableRemote(HI_BOOL bEnable)
{
    HI_S32 ret;

    if (!(g_PhonePlayer_VideoState & HI_ENGINE_STARTED))
    {
        ALOGE("Illegal state, check whether Video has been started\n");
        return HI_FAILURE;
    }

    if (bEnable)
    {
        ret = HI_UNF_VP_StartRemote(hVP, HI_UNF_VP_RMT_MODE_RECV);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call Hi_Adp_Video_EnableRemote failed.\n");
        }
    }
    else
    {
        ret = HI_UNF_VP_StopRemote(hVP, HI_UNF_VP_RMT_MODE_RECV);
        if (HI_SUCCESS != ret)
        {
            ALOGE("call Hi_Adp_Video_EnableRemote failed.\n");
        }
    }

    ALOGE("call Hi_Adp_Video_EnableRemote OK.\n");

    return ret;
}

HI_S32 Hi_Adp_Video_SetWindowShow(HI_S32 lrwindow, HI_S32 showorhide)
{
    HI_S32 ret = -1;
    HI_HANDLE hWIN;
    HI_UNF_WINDOW_ATTR_S stWinAttr;

    ALOGE("SetWindowShow 0 hide 1 show  2 full , the value %d\n", showorhide);

    if ((showorhide < 0) || (showorhide > 2))
    {
        ALOGE("input wrong para %d\n", showorhide);
        return ret;
    }

    hWIN = HIADP_GetWinHandle(lrwindow);
    if (HI_INVALID_HANDLE == hWIN)
    {
        ALOGE("input wrong window %d\n", lrwindow);
        return ret;
    }

    switch (showorhide)
    {
    case 0:
        ret = HI_UNF_VO_FreezeWindow(hWIN, HI_TRUE, HI_UNF_WINDOW_FREEZE_MODE_BLACK);
        break;
    case 1:
        ret = HI_UNF_VO_FreezeWindow(hWIN, HI_FALSE, HI_UNF_WINDOW_FREEZE_MODE_BLACK);
        break;
    case 2:
        ret = HI_UNF_VO_GetWindowAttr(hWIN, &stWinAttr);
        stWinAttr.stOutputRect.s32X = 0;
        stWinAttr.stOutputRect.s32Y = 0;
        stWinAttr.stOutputRect.s32Width  = 0;
        stWinAttr.stOutputRect.s32Height = 0;
        ret |= HI_UNF_VO_SetWindowAttr(hWIN, &stWinAttr);
        break;
    default:
        break;
    }

    if (HI_SUCCESS != ret)
    {
        ALOGE("call SetWindowShow failed.\n");
        return ret;
    }

    ALOGE("SetWindowShow OK.\n");
    return ret;
}

HI_S32 Hi_Adp_Video_SetWindowZorder(HI_S32 lrwindow, HI_S32 zorder)
{
    HI_S32 ret = -1;
    HI_HANDLE hWIN;
    HI_UNF_WINDOW_ATTR_S stWinAttr;
    HI_LAYER_ZORDER_E enZFlag;

    ALOGE("SetWindowZorder the value %d.\n", zorder);

    hWIN = HIADP_GetWinHandle(lrwindow);
    if (HI_INVALID_HANDLE == hWIN)
    {
        ALOGE("input wrong window %d\n", lrwindow);
        return ret;
    }

    if ((zorder < 0) || (zorder > 3))
    {
        ALOGE("input wrong zorder para %d\n", zorder);
        return ret;
    }

    switch (zorder)
    {
    case 0:
        enZFlag = HI_LAYER_ZORDER_MOVETOP;
        break;
    case 1:
        enZFlag = HI_LAYER_ZORDER_MOVEUP;
        break;
    case 2:
        enZFlag = HI_LAYER_ZORDER_MOVEBOTTOM;
        break;
    case 3:
        enZFlag = HI_LAYER_ZORDER_MOVEDOWN;
        break;
    default:
        enZFlag = HI_LAYER_ZORDER_BUTT;
        break;
    }

    ret = HI_UNF_VO_SetWindowZorder(hWIN, enZFlag);
    if (HI_SUCCESS != ret)
    {
        ALOGE("call HI_UNF_VO_SetWindowZorder failed.\n");
        return ret;
    }

    ALOGE("call HI_UNF_VO_SetWindowZorder OK.\n");
    return ret;
}

HI_S32 Hi_Adp_Video_SetWindowPos(HI_S32 lrwindow, HI_S32 X, HI_S32 Y, HI_S32 W, HI_S32 H )
{
    HI_S32 ret = -1;
    HI_HANDLE hWIN;
    HI_UNF_WINDOW_ATTR_S stWinAttr;

    ALOGE("SetWindowPos x %d, y %d, w %d, h %d.\n", X, Y, W, H);

    hWIN = HIADP_GetWinHandle(lrwindow);
    if (HI_INVALID_HANDLE == hWIN)
    {
        ALOGE("input wrong window %d\n", lrwindow);
        return ret;
    }

    ret = HI_UNF_VO_GetWindowAttr(hWIN, &stWinAttr);
    stWinAttr.stOutputRect.s32X = X;
    stWinAttr.stOutputRect.s32Y = Y;
    stWinAttr.stOutputRect.s32Width  = W;
    stWinAttr.stOutputRect.s32Height = H;
    ret |= HI_UNF_VO_SetWindowAttr(hWIN, &stWinAttr);
    if (HI_SUCCESS != ret)
    {
        ALOGE("call HI_UNF_VO_SetWindowAttr failed.\n");
        return ret;
    }

    ALOGE("call HI_UNF_VO_SetWindowAttr OK.\n");
    return ret;
}

HI_S32 Hi_Adp_Video_GetOptionalConfig(HI_S32 OptionType)
{
    HI_S32 ret = -1;
	HI_S32 Value;

    ALOGE("enter Hi_Adp_Video_GetOptionalConfig.\n");

	if ((OptionType < HI_OPTIONAL_CONFIG_VENC_PROFILE) || (OptionType >= HI_OPTIONAL_CONFIG_BUTT))
	{
		ALOGE("invalid optional config %d, see HI_ADP_OPTIONAL_CONFIG_E\n", OptionType);
		return ret;
	}

	Value = g_VideoOption[OptionType];

    ALOGE("call Hi_Adp_Video_GetOptionalConfig OK.\n");
    return Value;
}

/**************************
HI_OPTIONAL_CONFIG_VENC_PROFILE
the value  see HI_UNF_H264_PROFILE_E

HI_OPTIONAL_CONFIG_RTP_SPLIT_SIZE,
HI_OPTIONAL_CONFIG_RTP_RECVBUF_SIZE,
HI_OPTIONAL_CONFIG_RTP_RECVBUF_NUM,
HI_OPTIONAL_CONFIG_RTP_SORT_DEPTH,
the value check see the function RTP_CheckUserConfig in rtp.c file.

HI_OPTIONAL_CONFIG_NET_IP_TYPE,
the value 0 means ipv6,1 means ipv4.
*****************************/
HI_S32 Hi_Adp_Video_SetOptionalConfig(HI_S32 OptionType, HI_S32 Value)
{
    HI_S32 ret = -1;

    ALOGE("enter Hi_Adp_Video_SetOptionalConfig OptionType %d , Value %d.\n", OptionType, Value);

    if (g_PhonePlayer_VideoState & HI_ENGINE_STARTED)
    {
        ALOGE("Illegal state, Video should be stopped firstly\n");
        return ret;
    }

	if (Value < 0)
	{
		ALOGE("invalid Value %d\n", Value);
		return ret;
	}

	if ((OptionType < HI_OPTIONAL_CONFIG_VENC_PROFILE) || (OptionType >= HI_OPTIONAL_CONFIG_BUTT))
	{
		ALOGE("invalid video optional config %d, see HI_ADP_OPTIONAL_CONFIG_E\n", OptionType);
		return ret;
	}

	g_VideoOption[OptionType] = Value;

    ALOGE("call Hi_Adp_Video_SetOptionalConfig OK.\n");
    return 0;
}

HI_S32 Adp_Voip_GetValidRateMax(HI_U32 u32RateMin, HI_U32 u32RateMax, HI_U32 *pu32Rate)
{
    HI_U32 i;
    HI_U32 u32SampleRateList[4] = {48000, 32000, 16000, 8000};

    if (u32RateMin > u32RateMax)
    {
        return HI_FAILURE;
    }

    for (i = 0; i < 4; i++)
    {
        if ((u32SampleRateList[i] >= u32RateMin) && (u32SampleRateList[i] <= u32RateMax))
        {
            *pu32Rate = u32SampleRateList[i];
            return HI_SUCCESS;
        }
    }

    return HI_FAILURE;
}

static HI_S32   Adp_Voip_SetDefNetPara(HI_UNF_NET_CONFIG_PARA_S *pstNetCfg)
{
    HI_U8 u8VoipLoopIP[4] = {127, 0, 0, 1};
    HI_UNF_NET_CONFIG_BODY_S    *pstNetPara = NULL;
    HI_UNF_NET_CHANGE_FLAG_S    *pstNetFlag = NULL;

    if (pstNetCfg == NULL)
    {
        ALOGE("null pointer pstNetCfg\n");
        return HI_FAILURE;
    }

    pstNetPara = &pstNetCfg->stBody;
    pstNetFlag = &pstNetCfg->stChange;

    pstNetFlag->bit1SrcIP   = 1;
    pstNetPara->u32SrcIPLen = sizeof(u8VoipLoopIP);
    memcpy(pstNetPara->u8SrcIP, u8VoipLoopIP, sizeof(u8VoipLoopIP));
    pstNetFlag->bit1DstIP   = 1;
    pstNetPara->u32DstIPLen = sizeof(u8VoipLoopIP);
    memcpy(pstNetPara->u8DstIP, u8VoipLoopIP, sizeof(u8VoipLoopIP));
    pstNetFlag->bit1SrcPort = 1;
    pstNetPara->u16SrcPort  = HI_VOIP_DEF_NET_PORT;
    pstNetFlag->bit1DstPort = 1;
    pstNetPara->u16DstPort = HI_VOIP_DEF_NET_PORT;

    return HI_SUCCESS;
}

static HI_S32 Adp_Voip_SetAudDevPara(HI_AUD_DEV_SELECT_PAIR_S *   pstAudDev,
                                     HI_U32                       u32AudInRate,
                                     HI_U32                       u32AudOutRate,
                                     HI_UNF_AUDDEV_BODY_S *       pstVoipAudDevPara,
                                     HI_UNF_AUDADP_AUDDEV_PARA_S *pstAudAdpDevPara)
{
    if ((NULL == pstAudDev) || (NULL == pstVoipAudDevPara) || (NULL == pstAudAdpDevPara))
    {
        ALOGE("Invalide param!\n");
        return HI_FAILURE;
    }

    pstVoipAudDevPara->s32AudioDevId     = pstAudDev->u32AudDevId;
    pstVoipAudDevPara->s32AiSampleRate   = u32AudInRate;
    pstVoipAudDevPara->s32AiBitPerSample = 16;
    pstVoipAudDevPara->s32AiChannels = 1;

    pstVoipAudDevPara->s32AoSampleRate   = u32AudOutRate;
    pstVoipAudDevPara->s32AoBitPerSample = 16;
    pstVoipAudDevPara->s32AoChannels = 1;

    pstAudAdpDevPara->s32AudioDevId     = pstAudDev->u32AudDevId;
    pstAudAdpDevPara->s32AiSampleRate   = u32AudInRate;
    pstAudAdpDevPara->s32AiBitPerSample = 16;
    pstAudAdpDevPara->s32AiChannels = 1;
    pstAudAdpDevPara->s32AiCardNo = pstAudDev->s32InSndCardNo;

    pstAudAdpDevPara->s32AoSampleRate   = u32AudOutRate;
    pstAudAdpDevPara->s32AoBitPerSample = 16;
    pstAudAdpDevPara->s32AoChannels = 1;
    pstAudAdpDevPara->s32AoCardNo = pstAudDev->s32OutSndCardNo;

    return HI_SUCCESS;
}

static HI_S32 Adp_Voip_GetAudioList(HI_UNF_VOIP_AUDIO_DEVICE_TYPE_E enAudDevType,
                                    HI_AUD_DEV_INFO_S *             pstAudDevList,
                                    HI_U32                          u32ListMax,
                                    HI_U32 *                        pu32DevNum)
{
    HI_U32 i, u32Count = 0;
    HI_S32 s32Ret;
    HI_ALSA_CARD_INFO_S stAlsaDevList[HI_AUD_DEV_LIST_MAX];
    HI_AUD_DEV_INFO_S *pstAudDev = NULL;

    if ((NULL == pstAudDevList) || (NULL == pu32DevNum))
    {
        ALOGE("Invalide param!\n");
        return HI_FAILURE;
    }

    if (u32ListMax == 0)
    {
        ALOGE("Invalid para, u32ListMax is %d!\n", u32ListMax);
        return HI_FAILURE;
    }

    memset(pstAudDevList, 0, sizeof(HI_AUD_DEV_INFO_S) * u32ListMax);
    pstAudDev   = &pstAudDevList[0];
    *pu32DevNum = 0;

    /* ALSA device */
    memset(stAlsaDevList, 0, sizeof(HI_ALSA_CARD_INFO_S) * HI_AUD_DEV_LIST_MAX);
    s32Ret = HI_ALSA_GetAudioDevList(enAudDevType, stAlsaDevList,
                                     HI_AUD_DEV_LIST_MAX - (*pu32DevNum), &u32Count);
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("Get audio in device list failure, ErrCode is %x!\n", s32Ret);
        return HI_SUCCESS;
    }

    if (u32Count <= 0)
    {
        ALOGI("No alsa audio device found!\n");
        return HI_SUCCESS;
    }

    for (i = 0; i < u32Count; i++)
    {
        pstAudDev->u32AudDevId  = HI_UNF_VOIP_AUD_DEV_ALSA;
        pstAudDev->s32SndCardNo = stAlsaDevList[i].s32CardNo;
        strcpy(pstAudDev->szName, stAlsaDevList[i].szName);
        if (0 == strcmp(pstAudDev->szName, "HISI-AIAO"))
        {
            pstAudDev->s32SndCardNo = -1;   //for voip sdk code being not modified
        }

        pstAudDev->u32AudDevTpye = HI_VOIP_AUD_DEV_TYPE_SNDCARD;
        pstAudDev++;
        (*pu32DevNum)++;
    }

    usleep(200 * 1000);

    return HI_SUCCESS;
}

//static HI_S32 Adp_Voip_SelectAudDev(HI_AUD_DEV_INFO_S * pstAudInDevList, HI_U32 u32AudInDevNum,
//                                        HI_AUD_DEV_INFO_S * pstAudOutDevList, HI_U32 u32AudOutDevNum, HI_AUD_DEV_SELECT_PAIR_S *pstAudDevSel)
static HI_S32 Adp_Voip_SelectAudDev(HI_U32 u32AudSelectInDevNum,
                                    HI_U32 u32AudSelectOutDevNum)
{
    HI_AUD_DEV_SELECT_PAIR_S stAudDevSel;

    memset(&stAudDevSel, 0, sizeof(HI_AUD_DEV_SELECT_PAIR_S));

    stAudDevSel.u32AudDevId    = HI_UNF_VOIP_AUD_DEV_BUTT;
    stAudDevSel.u32AudDevTpye  = HI_VOIP_AUD_DEV_TYPE_BUTT;
    stAudDevSel.s32InSndCardNo = -1;
    stAudDevSel.s32InFlag = 0;
    stAudDevSel.s32OutSndCardNo = -1;
    stAudDevSel.s32OutFlag = 0;

    if (g_stAudDevInfo.u32AudInDevNum == 0)
    {
        ALOGE("Invalid para, u32AudInDevNum is 0!\n");
        return HI_FAILURE;
    }

    if (g_stAudDevInfo.u32AudOutDevNum == 0)
    {
        ALOGE("Invalid para, u32AudOutDevNum is 0!\n");
        return HI_FAILURE;
    }

    if ((u32AudSelectInDevNum >= g_stAudDevInfo.u32AudInDevNum)
        || (u32AudSelectOutDevNum >= g_stAudDevInfo.u32AudOutDevNum))
    {
        ALOGE("Select input or output device num is beyond the scope of exits devices!\n");
        return HI_FAILURE;
    }

    if (g_stAudDevInfo.stAudevInList[u32AudSelectInDevNum].u32AudDevId
        != g_stAudDevInfo.stAudevOutList[u32AudSelectOutDevNum].u32AudDevId)
    {
        ALOGE("Don't Support the combination of the diffirent DevIDs !\n");
        return HI_FAILURE;
    }

    if (g_stAudDevInfo.stAudevInList[u32AudSelectInDevNum].u32AudDevTpye
        != g_stAudDevInfo.stAudevOutList[u32AudSelectOutDevNum].u32AudDevTpye)
    {
        ALOGE("Don't Support the combination of the diffirent DevTypes !\n");
        return HI_FAILURE;
    }

    stAudDevSel.s32InSndCardNo = g_stAudDevInfo.stAudevInList[u32AudSelectInDevNum].s32SndCardNo;
    strcpy(stAudDevSel.szInName, g_stAudDevInfo.stAudevInList[u32AudSelectInDevNum].szName);
    stAudDevSel.s32InFlag = 1;

    stAudDevSel.u32AudDevId     = g_stAudDevInfo.stAudevOutList[u32AudSelectInDevNum].u32AudDevId;
    stAudDevSel.u32AudDevTpye   = g_stAudDevInfo.stAudevOutList[u32AudSelectInDevNum].u32AudDevTpye;
    stAudDevSel.s32OutSndCardNo = g_stAudDevInfo.stAudevOutList[u32AudSelectInDevNum].s32SndCardNo;
    strcpy(stAudDevSel.szOutName, g_stAudDevInfo.stAudevOutList[u32AudSelectInDevNum].szName);
    stAudDevSel.s32OutFlag = 1;

    g_stAudDevInfo.stAudDevSel = stAudDevSel;

    return HI_SUCCESS;
}

/*Should call when ALSA device be closed*/
static HI_S32 Adp_Voip_GetAudDevSampleRate(HI_AUD_DEV_SELECT_PAIR_S * pstAudDev,
                                           HI_U32 *                   pu32AudInRate,
                                           HI_U32 *                   pu32AudOutRate)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32RateMin, u32RateMax;
    HI_ALSA_CARD_INFO_S stAlsaCardInfo;

    if ((NULL == pstAudDev) || (NULL == pu32AudInRate) || (NULL == pu32AudOutRate))
    {
        ALOGE("Invalide param!\n");
        return HI_FAILURE;
    }

    if ((HI_VOIP_AUD_DEV_TYPE_SLIC == pstAudDev->u32AudDevTpye)
        || (HI_VOIP_AUD_DEV_TYPE_BLUETOOTH == pstAudDev->u32AudDevTpye))
    {
        *pu32AudInRate  = HI_UNF_SAMPLE_RATE_8K;
        *pu32AudOutRate = HI_UNF_SAMPLE_RATE_8K;
    }
    else if (HI_VOIP_AUD_DEV_TYPE_SNDCARD == pstAudDev->u32AudDevTpye)
    {
        /*input device*/
        stAlsaCardInfo.s32CardNo = pstAudDev->s32InSndCardNo;
        stAlsaCardInfo.enType = HI_UNF_VOIP_AUD_IN_DEV;
        strcpy(stAlsaCardInfo.szName, pstAudDev->szInName);

        s32Ret = HI_ALSA_GetAudioDevRateRange(&stAlsaCardInfo, &u32RateMin, &u32RateMax);
        if (HI_SUCCESS != s32Ret)
        {
            ALOGE("Get audio IN device [%d : %s] sample rate range failure, ErrCode is %x!\n",
                  stAlsaCardInfo.s32CardNo,
                  stAlsaCardInfo.szName,
                  s32Ret);
        }
        else
        {
            ALOGI("Audio IN device [%d], name [%s], rate_min [%d], rate_max[%d]\n",
                  stAlsaCardInfo.s32CardNo,
                  stAlsaCardInfo.szName,
                  u32RateMin,
                  u32RateMax);

            s32Ret = Adp_Voip_GetValidRateMax(u32RateMin, u32RateMax, pu32AudInRate);
        }

        /*output device*/
        if (0 > pstAudDev->s32OutSndCardNo)      //HI-AIAO
        {
            *pu32AudOutRate = HI_UNF_SAMPLE_RATE_48K;
        }
        else            //ASLA SOUND CARD
        {
            stAlsaCardInfo.s32CardNo = pstAudDev->s32OutSndCardNo;
            stAlsaCardInfo.enType = HI_UNF_VOIP_AUD_OUT_DEV;
            strcpy(stAlsaCardInfo.szName, pstAudDev->szOutName);

            s32Ret = HI_ALSA_GetAudioDevRateRange(&stAlsaCardInfo, &u32RateMin, &u32RateMax);
            if (HI_SUCCESS != s32Ret)
            {
                ALOGE("Get audio OUT device [%d : %s] sample rate range failure, ErrCode is %x!\n",
                      stAlsaCardInfo.s32CardNo,
                      stAlsaCardInfo.szName,
                      s32Ret);
            }
            else
            {
                ALOGI("Audio OUT device [%d], name [%s], rate_min [%d], rate_max[%d]\n",
                      stAlsaCardInfo.s32CardNo,
                      stAlsaCardInfo.szName,
                      u32RateMin,
                      u32RateMax);

                s32Ret = Adp_Voip_GetValidRateMax(u32RateMin, u32RateMax, pu32AudOutRate);
            }
        }
    }

#if 0
    if (HI_UNF_VOIP_AUD_DEV_ALSA == pstAudDev->u32AudDevId)
    {
        usleep(100 * 1000);
    }
#endif


    return HI_SUCCESS;
}

HI_S32 Hi_Adp_Audio_GetAudDevList(HI_AUD_DEV_INFO_S *pstAudInDevList,
                                  HI_AUD_DEV_INFO_S *pstAudOutDevList)
{
    HI_S32 s32Ret;

    if ((pstAudInDevList == NULL) || (pstAudOutDevList == NULL))
    {
        ALOGE("Invalide Param\n");
        return HI_FAILURE;
    }

    s32Ret = Adp_Voip_GetAudioList(HI_UNF_VOIP_AUD_IN_DEV, g_stAudDevInfo.stAudevInList,
                                   HI_AUD_DEV_LIST_MAX, &g_stAudDevInfo.u32AudInDevNum);
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("Get audio in list failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    if (g_stAudDevInfo.u32AudInDevNum == 0)
    {
        ALOGE("There are no input devices\n");
        return HI_FAILURE;
    }

    s32Ret = Adp_Voip_GetAudioList(HI_UNF_VOIP_AUD_OUT_DEV, g_stAudDevInfo.stAudevOutList,
                                   HI_AUD_DEV_LIST_MAX, &g_stAudDevInfo.u32AudOutDevNum);
    if (HI_SUCCESS != s32Ret)
    {
        memset(g_stAudDevInfo.stAudevInList, 0,
               sizeof(HI_AUD_DEV_INFO_S) * g_stAudDevInfo.u32AudInDevNum);
        ALOGE("Get audio in list failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    if (g_stAudDevInfo.u32AudOutDevNum == 0)
    {
        ALOGE("Invalid para, u32AudOutDevNum is 0!\n");
        memset(g_stAudDevInfo.stAudevInList, 0,
               sizeof(HI_AUD_DEV_INFO_S) * g_stAudDevInfo.u32AudInDevNum);
        return HI_FAILURE;
    }

    memcpy(pstAudInDevList, &g_stAudDevInfo.stAudevInList,
           sizeof(HI_AUD_DEV_INFO_S) * g_stAudDevInfo.u32AudInDevNum);
    memcpy(pstAudOutDevList, &g_stAudDevInfo.stAudevOutList,
           sizeof(HI_AUD_DEV_INFO_S) * g_stAudDevInfo.u32AudOutDevNum);

    return HI_SUCCESS;
}

HI_S32 Hi_Adp_Audio_Init(HI_VOID)
{
    HI_S32 s32Ret;

    if ((g_PhonePlayer_AudioState == HI_ENGINE_OPENED)
       || (g_PhonePlayer_AudioState == HI_ENGINE_STARTED))
    {
        ALOGE("Voip hasn't init yet, current state is %d\n", g_PhonePlayer_AudioState);
        return HI_FAILURE;
    }

    if (g_PhonePlayer_AudioState == HI_ENGINE_INITED)
    {
        ALOGI("Voip has started yet\n");
        return HI_SUCCESS;
    }

    memset(&g_stAudDevInfo, 0, sizeof(HI_AUD_DEV_GLOBAL_INFO_S));
    s32Ret  = HIADP_Snd_Init();
    s32Ret |= HI_UNF_VOIP_Init();
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("Voip initial failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    s32Ret |= HI_UNF_AUDADP_Init();
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("AudAdp initial failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    g_PhonePlayer_AudioState = HI_ENGINE_INITED;

    return 0;
}

HI_S32 Hi_Adp_Audio_Deinit(HI_VOID)
{
    if ((g_PhonePlayer_AudioState == HI_ENGINE_OPENED)
       || (g_PhonePlayer_AudioState == HI_ENGINE_STARTED))
    {
        ALOGE("Voip hasn't init yet, current state is %d\n", g_PhonePlayer_AudioState);
        return HI_FAILURE;
    }

    if (g_PhonePlayer_AudioState == HI_ENGINE_BUTT)
    {
        ALOGI("Voip has started yet\n");
        return HI_SUCCESS;
    }

    (HI_VOID)HI_UNF_VOIP_DeInit();
    (HI_VOID)HI_UNF_AUDADP_DeInit();
    (HI_VOID)HIADP_Snd_DeInit();

    g_PhonePlayer_AudioState = HI_ENGINE_BUTT;
    return HI_SUCCESS;
}

HI_S32 Hi_Adp_Audio_Open(HI_U32 u32AudSelectInDevNum, HI_U32 u32AudSelectOutDevNum)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stChAttr;
    HI_UNF_AUDADP_AUDDEV_PARA_S stAudAdpDevPara;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;
    HI_U32 u32AiSampleRate = HI_UNF_SAMPLE_RATE_8K;
    HI_U32 u32AoSampleRate = HI_UNF_SAMPLE_RATE_48K;

    if ((g_PhonePlayer_AudioState == HI_ENGINE_STARTED)
       || (g_PhonePlayer_AudioState == HI_ENGINE_BUTT))
    {
        ALOGE("Voip hasn't inited or has started yet, current state is %d\n", g_PhonePlayer_AudioState);
        return HI_FAILURE;
    }

    if (g_PhonePlayer_AudioState == HI_ENGINE_OPENED)
    {
        ALOGI("Voip has open yet\n");
        return HI_SUCCESS;
    }

    hVoipHandle = 0;
    memset(&stChAttr, 0, sizeof(HI_UNF_VOIP_CHN_ATTR_S));
    memset(&stAudAdpDevPara, 0, sizeof(HI_UNF_AUDADP_AUDDEV_PARA_S));

    s32Ret = Adp_Voip_SelectAudDev(u32AudSelectInDevNum, u32AudSelectOutDevNum);
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("Select audio device failure!\n");
        return s32Ret;
    }

    s32Ret = Adp_Voip_GetAudDevSampleRate(&g_stAudDevInfo.stAudDevSel, &u32AiSampleRate, &u32AoSampleRate);
    if (HI_SUCCESS != s32Ret)
    {
        ALOGE("Get audio device sample rate failure!\n");
        return s32Ret;
    }

    s32Ret = HI_UNF_VOIP_GetChDefaultAttr(HI_UNF_VOIP_MODE_VOIVE, &stChAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Voip get default attribute failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Adp_Voip_SetAudDevPara(&g_stAudDevInfo.stAudDevSel, u32AiSampleRate,
                                    u32AoSampleRate, &stChAttr.stAudevPara.stBody, &stAudAdpDevPara);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Set audio device para failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Adp_Voip_SetDefNetPara(&stChAttr.stNetPara);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Set voip net para failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    s32Ret = HI_UNF_VOIP_CreateChannel(HI_UNF_VOIP_MODE_VOIVE, &stChAttr, &hVoipHandle);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Voip create channel failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    stAudDevOptFlag.bit1AudInDev  = g_stAudDevInfo.stAudDevSel.s32InFlag;
    stAudDevOptFlag.bit1AudOutDev = g_stAudDevInfo.stAudDevSel.s32OutFlag;
    s32Ret = HI_UNF_AUDADP_AudDev_Open(&stAudAdpDevPara, stAudDevOptFlag);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Audio adapter open failure! ErrCode=%x\n", s32Ret);
        (HI_VOID)HI_UNF_VOIP_DestroyChannel(hVoipHandle);
        return s32Ret;
    }

    g_PhonePlayer_AudioState = HI_ENGINE_OPENED;

    return HI_SUCCESS;
}

HI_S32 Hi_Adp_Audio_Start(const HI_CHAR *pLoacalIp,
                          HI_U32         uLocalPort,
                          const HI_CHAR *pRemoteIp,
                          HI_U32         uRemotePort)
{
    HI_U8 u8VoipSrcIP[4], u8VoipDstIP[4];
    HI_U32 u32AudDevId;
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stChAttr;
    HI_UNF_VOIP_CFG_RTCP_ATTR_S stRtcpAttr;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;

    if ((g_PhonePlayer_AudioState == HI_ENGINE_BUTT)
       || (g_PhonePlayer_AudioState == HI_ENGINE_INITED))
    {
        ALOGE("Voip hasn't open yet, current state is %d\n", g_PhonePlayer_AudioState);
        return HI_FAILURE;
    }

    if (g_PhonePlayer_AudioState == HI_ENGINE_STARTED)
    {
        ALOGI("Voip has started yet\n");
        return HI_SUCCESS;
    }

    if ((pLoacalIp == NULL) || (pRemoteIp == NULL))
    {
        ALOGE("%s %s ,Invalide param\n", pLoacalIp, pRemoteIp);
        return HI_FAILURE;
    }

    IpaddrCharToU8(pLoacalIp, u8VoipSrcIP);
    IpaddrCharToU8(pRemoteIp, u8VoipDstIP);

    memset(&stChAttr, 0, sizeof(HI_UNF_VOIP_CHN_ATTR_S));
    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stChAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get chn attr failed! ErrCode %x\n", s32Ret);
        return s32Ret;
    }

    stChAttr.stNetPara.stChange.bit1SrcIP   = 1;
    stChAttr.stNetPara.stChange.bit1SrcPort = 1;
    memcpy(stChAttr.stNetPara.stBody.u8SrcIP, u8VoipSrcIP, sizeof(u8VoipSrcIP));
    stChAttr.stNetPara.stBody.u16SrcPort  = uLocalPort;
    stChAttr.stNetPara.stBody.u32SrcIPLen = sizeof(u8VoipSrcIP);

    stChAttr.stNetPara.stChange.bit1DstIP   = 1;
    stChAttr.stNetPara.stChange.bit1DstPort = 1;
    memcpy(stChAttr.stNetPara.stBody.u8DstIP, u8VoipDstIP, sizeof(u8VoipDstIP));
    stChAttr.stNetPara.stBody.u16DstPort  = uRemotePort;
    stChAttr.stNetPara.stBody.u32DstIPLen = sizeof(u8VoipDstIP);

    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stChAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Modify chn attr failed! ErrCode %x\n", s32Ret);
        return s32Ret;
    }

    stRtcpAttr.u32EnableFlag   = 1;
    stRtcpAttr.u32SendInterval = g_u32AudSpan;
    s32Ret = HI_UNF_VOIP_CfgRtcp(hVoipHandle, &stRtcpAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Voip cfg rtcp failed! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

    u32AudDevId = g_stAudDevInfo.stAudDevSel.u32AudDevId;
    stAudDevOptFlag.bit1AudInDev  = g_stAudDevInfo.stAudDevSel.s32InFlag;
    stAudDevOptFlag.bit1AudOutDev = g_stAudDevInfo.stAudDevSel.s32OutFlag;
    s32Ret = HI_UNF_AUDADP_AudDev_Start(u32AudDevId, stAudDevOptFlag);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Audio adapter start failure! ErrCode=%x\n", s32Ret);
        return s32Ret;
    }

#if 0
    if (pfnEventCB)
    {
        s32Ret = HI_UNF_VOIP_RegisterEvent(hVoipHandle, pfnEventCB, hVoipHandle);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Voip register event cb function failure! ErrCode=%x\n", s32Ret);
        }
    }
#endif


    g_stopAudGet = 0;
    pthread_create(&g_threadAudStatics, HI_NULL, HIADP_VoipSchedule_NetStatics, (void*)(&hVoipHandle));

    g_PhonePlayer_AudioState = HI_ENGINE_STARTED;

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_Stop(HI_VOID)
{
    HI_S32 s32Ret, u32AudDevId;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;

    if ((g_PhonePlayer_AudioState == HI_ENGINE_INITED)
       || (g_PhonePlayer_AudioState == HI_ENGINE_BUTT))
    {
        ALOGE("Voip hasn't started yet, current state is %d\n", g_PhonePlayer_AudioState);
        return HI_FAILURE;
    }

    if (g_PhonePlayer_AudioState == HI_ENGINE_OPENED)
    {
        ALOGI("Voip has stopped yet\n");
        return HI_SUCCESS;
    }

    g_stopAudGet = 1;
    pthread_join(g_threadAudStatics, NULL);

    u32AudDevId = g_stAudDevInfo.stAudDevSel.u32AudDevId;
    stAudDevOptFlag.bit1AudInDev  = g_stAudDevInfo.stAudDevSel.s32InFlag;
    stAudDevOptFlag.bit1AudOutDev = g_stAudDevInfo.stAudDevSel.s32OutFlag;
    s32Ret = HI_UNF_AUDADP_AudDev_Stop(u32AudDevId, stAudDevOptFlag);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Audio adapter stop failure! ErrCode=%x\n", s32Ret);
    }

    g_PhonePlayer_AudioState = HI_ENGINE_OPENED;

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_Close(HI_VOID)
{
    HI_U32 u32AudDevId;
    HI_UNF_AUDDEV_OPT_FLAG_S stAudDevOptFlag;

    if ((g_PhonePlayer_AudioState == HI_ENGINE_BUTT)
       || (g_PhonePlayer_AudioState == HI_ENGINE_STARTED))
    {
        ALOGE("Voip hasn't inited yet, current state is %d\n", g_PhonePlayer_AudioState);
        return HI_FAILURE;
    }

    if (g_PhonePlayer_AudioState == HI_ENGINE_INITED)
    {
        ALOGI("Voip has closed yet\n");
        return HI_SUCCESS;
    }

    u32AudDevId = g_stAudDevInfo.stAudDevSel.u32AudDevId;
    stAudDevOptFlag.bit1AudInDev  = g_stAudDevInfo.stAudDevSel.s32InFlag;
    stAudDevOptFlag.bit1AudOutDev = g_stAudDevInfo.stAudDevSel.s32OutFlag;
    (HI_VOID)HI_UNF_VOIP_DestroyChannel(hVoipHandle);
    (HI_VOID)HI_UNF_AUDADP_AudDev_Close(u32AudDevId, stAudDevOptFlag);

    g_PhonePlayer_AudioState = HI_ENGINE_INITED;

    return HI_SUCCESS;
}

HI_S32 Hi_Adp_Audio_SetMute(HI_S32 sDevice)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((sDevice < AUD_DEV_PLAYBACK_DIRECTION)
       || (sDevice > AUD_DEV_CAPTURE_DIRECTION))
    {
        ALOGE("Invalide direction %d\n", sDevice);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    if (sDevice == AUD_DEV_PLAYBACK_DIRECTION)      //Playback
    {
        stVoipChnAttr.stEcPara.stChange.bit1OutputMute = 1;
        stVoipChnAttr.stEcPara.stBody.u8OutputMute = 1;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed. ret 0x%x\n", s32Ret);
        }
    }
    else
    {
        stVoipChnAttr.stEcPara.stChange.bit1InputMute = 1;
        stVoipChnAttr.stEcPara.stBody.u8InputMute = 1;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed. ret 0x%x\n", s32Ret);
        }
    }

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_SetUnMute(HI_S32 sDevice)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((sDevice < AUD_DEV_PLAYBACK_DIRECTION)
       || (sDevice > AUD_DEV_CAPTURE_DIRECTION))
    {
        ALOGE("Invalide direction %d\n", sDevice);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return HI_FAILURE;
    }

    if (sDevice == AUD_DEV_PLAYBACK_DIRECTION)      //Playback
    {
        stVoipChnAttr.stEcPara.stChange.bit1OutputMute = 1;
        stVoipChnAttr.stEcPara.stBody.u8OutputMute = 0;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed. ret 0x%x\n", s32Ret);
        }
    }
    else
    {
        stVoipChnAttr.stEcPara.stChange.bit1InputMute = 1;
        stVoipChnAttr.stEcPara.stBody.u8InputMute = 0;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed. ret 0x%x\n", s32Ret);
        }
    }

    return s32Ret;
}

HI_S32  Hi_Adp_Audio_SetVolume(HI_S32 sDevice, HI_S32 s32Volume)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((sDevice < AUD_DEV_PLAYBACK_DIRECTION)
       || (sDevice > AUD_DEV_CAPTURE_DIRECTION))
    {
        ALOGE("Invalide direction %d\n", sDevice);
        return HI_FAILURE;
    }

    if ((s32Volume < 0) || (s32Volume > 100))
    {
        ALOGE("Invalide volume %d\n", s32Volume);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    if (sDevice == AUD_DEV_PLAYBACK_DIRECTION)      //Playback
    {
        stVoipChnAttr.stEcPara.stChange.bit1OutputVolume = 1;
        stVoipChnAttr.stEcPara.stBody.u8OutputVolume = (HI_U8)s32Volume;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed. ret 0x%x\n", s32Ret);
        }
    }
    else
    {
        stVoipChnAttr.stEcPara.stChange.bit1InputVolume = 1;
        stVoipChnAttr.stEcPara.stBody.u8InputVolume = (HI_U8)s32Volume;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed . ret 0x%x\n", s32Ret);
        }
    }

    return s32Ret;
}

HI_S32  Hi_Adp_Audio_SetGain(HI_S32 sDevice, HI_S32 s32Gain)
{
    HI_S32 s32Ret = HI_FAILURE;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((sDevice < AUD_DEV_PLAYBACK_DIRECTION)
       || (sDevice > AUD_DEV_CAPTURE_DIRECTION))
    {
        ALOGE("Invalide direction %d\n", sDevice);
        return HI_FAILURE;
    }

    if ((s32Gain > AUD_MAX_GAIN) || (s32Gain < AUD_MIN_GAIN))
    {
        ALOGE("Invalide gain %d\n", s32Gain);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    if (sDevice == AUD_DEV_PLAYBACK_DIRECTION)      //Playback
    {
        stVoipChnAttr.stEcPara.stChange.bit1OutputGain = 1;
        stVoipChnAttr.stEcPara.stBody.s8OutputGain = s32Gain;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed. ret 0x%x\n", s32Ret);
        }
    }
    else
    {
        stVoipChnAttr.stEcPara.stChange.bit1InputGain = 1;
        stVoipChnAttr.stEcPara.stBody.s8InputGain = s32Gain;
        s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
        if (s32Ret != HI_SUCCESS)
        {
            ALOGE("Modify Voip chn attr failed . ret 0x%x\n", s32Ret);
        }
    }

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_SetCheckSpan(HI_S32 s32Span)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CFG_RTCP_ATTR_S stRtcpAttr;

    g_u32AudSpan = s32Span;
    memset(&stRtcpAttr, 0, sizeof(HI_UNF_VOIP_CFG_RTCP_ATTR_S));
    stRtcpAttr.u32EnableFlag   = 1;
    stRtcpAttr.u32SendInterval = (HI_U32)s32Span;
    s32Ret = HI_UNF_VOIP_CfgRtcp(hVoipHandle, &stRtcpAttr);

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_CheckPacket()
{
    return bHasAudioData;
}

HI_S32 Hi_Adp_Audio_EnableAEC(HI_S32 s32Enable)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((s32Enable != HI_FALSE) && (s32Enable != HI_TRUE))
    {
        ALOGE("Invalide param %d\n", s32Enable);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    stVoipChnAttr.stEcPara.stChange.bit1EcEnable = 1;
    stVoipChnAttr.stEcPara.stBody.u8EcEnableFlag = s32Enable;
    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Modify Voip chn attr failed . ret 0x%x\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_EnableANS(HI_S32 s32Enable)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((s32Enable != HI_FALSE) && (s32Enable != HI_TRUE))
    {
        ALOGE("Invalide param %d\n", s32Enable);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    stVoipChnAttr.stVQEPara.stChange.bit1LocalAnrFlag = 1;
    stVoipChnAttr.stVQEPara.stBody.u8LocalAnrFlag = s32Enable;
    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Modify Voip chn attr failed . ret 0x%x\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_EnableAGC(HI_S32 s32Enable)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((s32Enable != HI_FALSE) && (s32Enable != HI_TRUE))
    {
        ALOGE("Invalide param %d\n", s32Enable);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    stVoipChnAttr.stVQEPara.stChange.bit1LocalAgcFlag = 1;
    stVoipChnAttr.stVQEPara.stBody.u8LocalAgcFlag = s32Enable;
    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Modify Voip chn attr failed . ret 0x%x\n", s32Ret);
    }

    return s32Ret;
}

HI_S32 Hi_Adp_Audio_EnableVAD(HI_S32 s32Enable)
{
    HI_S32 s32Ret;
    HI_UNF_VOIP_CHN_ATTR_S stVoipChnAttr;

    if ((s32Enable != HI_FALSE) && (s32Enable != HI_TRUE))
    {
        ALOGE("Invalide param %d\n", s32Enable);
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_VOIP_GetChAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Get Voip chn attr failed. ret 0x%x\n", s32Ret);
        return s32Ret;
    }

    stVoipChnAttr.stEcPara.stChange.bit1VadEnable = 1;
    stVoipChnAttr.stEcPara.stBody.u8VadEnableFlag = s32Enable;
    s32Ret = HI_UNF_VOIP_ModifyChnAttr(hVoipHandle, &stVoipChnAttr);
    if (s32Ret != HI_SUCCESS)
    {
        ALOGE("Modify Voip chn attr failed . ret 0x%x\n", s32Ret);
    }

    return s32Ret;
}
