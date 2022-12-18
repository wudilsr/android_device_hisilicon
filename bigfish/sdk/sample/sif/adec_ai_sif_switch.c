/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : cast.c
  Version       : Initial Draft
  Author        : Hisilicon audio 
  Created       : 2010/01/26
  Description   :
  History       :
  1.Date        : 2013/06/1
    Author      : audio
    Modification: Created file

******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/fb.h>
#include <assert.h>
#include <pthread.h>
#include <sys/wait.h>

#include "hi_unf_common.h"
#include "hi_unf_ai.h"
#include "hi_unf_sound.h"
#include "hi_adp_mpi.h"

#include "hi_unf_sif.h"
#include "hi_unf_frontend.h"
#include "hi_unf_hdmirx.h"

#ifdef CONFIG_SUPPORT_CA_RELEASE
#define sample_printf
#else
#define sample_printf printf
#endif

#define ATV_RF_TUNER_ADDR       0xc0
#define ATV_RF_TUNER_RESET_GPIO 0
#define ATV_RF_TUNER_TYPE       HI_UNF_TUNER_DEV_TYPE_TDA18273
#define ATV_RF_DEMOD_TYPE       HI_UNF_DEMOD_DEV_TYPE_TDA8296I
#define ATV_RF_DEMOD_ADDR       0
#define ATV_RF_TUNER_FREQ       107250  /* Khz */
#define ATV_RF_SYSTEM           HI_UNF_ATV_SYSTEM_PAL_BG

#define ATV_RF_GPIO_I2C_SCL_GROUP   3
#define ATV_RF_GPIO_I2C_SCL_BIT     3
#define ATV_RF_GPIO_I2C_SDA_GROUP   3
#define ATV_RF_GPIO_I2C_SDA_BIT     2
#define ATV_RF_GPIO_I2C_SCL_NUM     (ATV_RF_GPIO_I2C_SCL_GROUP*8 + ATV_RF_GPIO_I2C_SCL_BIT)
#define ATV_RF_GPIO_I2C_SDA_NUM     (ATV_RF_GPIO_I2C_SDA_GROUP*8 + ATV_RF_GPIO_I2C_SDA_BIT)

typedef struct hiSAMPLE_ATV_RF_SCAN_S
{
    HI_BOOL             bScaned;
    HI_U32              u32TotalNum;
    HI_U32              u32CurNum;
    HI_UNF_ATV_SYSTEM_E enAtvSystem[100];
    HI_U32              u32Freq[100];
} SAMPLE_ATV_RF_SCAN_S;

static volatile HI_BOOL s_bAtvRfMonitorEn;
HI_HANDLE               s_hAtvRfWindow;
HI_HANDLE               s_hAtvRfVi;
static HI_U32 s_u32AtvRfI2cNum  = 0;
static HI_U32 s_u32AtvRfTunerId = 0;
static HI_UNF_TUNER_ATTR_S s_stTunerAttr;
static HI_UNF_TUNER_CONNECT_PARA_S s_stTunerConnect;
static HI_BOOL s_bFeInited = HI_FALSE;
static HI_BOOL s_bSifInited= HI_FALSE;
static SAMPLE_ATV_RF_SCAN_S s_stSampleAtvRfScan = {HI_FALSE};

#define SAMPLE_PRINT_FUNC(str)\
do{\
    printf("test case <%s> %s\n",__FUNCTION__, str);\
}while(0)

#define SAMPLE_RF_CHECK_FUNC(s32Ret, pfn)   \
do {\
    s32Ret = pfn;\
    if (HI_SUCCESS != s32Ret)\
    {\
        printf("\033[0;32m");\
        printf(#pfn" Run Failure!\n");\
        printf("\033[0;39m");\
    }\
} while(0)

HI_S32 SampleAtvRfFeInit(HI_VOID)
{
    HI_S32 s32Ret;

    if (HI_TRUE == s_bFeInited)
    {
        return HI_SUCCESS;
    }
    
    s32Ret = HI_UNF_I2C_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_I2C_Init Failed \n");
        return HI_FAILURE;
    }
    
    s32Ret = HI_UNF_I2C_CreateGpioI2c(&s_u32AtvRfI2cNum, ATV_RF_GPIO_I2C_SCL_NUM,
        ATV_RF_GPIO_I2C_SDA_NUM);

    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_I2C_CreateGpioI2c Failed \n");
        return HI_FAILURE;
    }

    /* FrontEnd Init and Setting */
    s32Ret = HI_UNF_TUNER_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_TUNER_Init Failed \n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_TUNER_Open(s_u32AtvRfTunerId);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_TUNER_Open Failed \n");
        return HI_FAILURE;
    }
    
    s_stTunerAttr.enSigType = HI_UNF_TUNER_SIG_TYPE_ATV;
    s_stTunerAttr.enTunerDevType = ATV_RF_TUNER_TYPE;
    s_stTunerAttr.u32TunerAddr = ATV_RF_TUNER_ADDR;
    s_stTunerAttr.enDemodDevType = ATV_RF_DEMOD_TYPE;
    s_stTunerAttr.u32DemodAddr = ATV_RF_DEMOD_ADDR;
    s_stTunerAttr.enOutputMode = HI_UNF_TUNER_OUTPUT_MODE_DEFAULT;
    s_stTunerAttr.enI2cChannel = s_u32AtvRfI2cNum;
    s_stTunerAttr.u32ResetGpioNo = ATV_RF_TUNER_RESET_GPIO;    
    s32Ret = HI_UNF_TUNER_SetAttr(s_u32AtvRfTunerId, &s_stTunerAttr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_TUNER_SetAttr Failed \n");
        return HI_FAILURE;
    }

    s_stTunerConnect.enSigType = HI_UNF_TUNER_SIG_TYPE_ATV;
    s_stTunerConnect.unConnectPara.stAtv.u32Freq = ATV_RF_TUNER_FREQ;
    s_stTunerConnect.unConnectPara.stAtv.enSystem = ATV_RF_SYSTEM;
    s_stTunerConnect.unConnectPara.stAtv.enSifBw = HI_UNF_ATV_SIF_BW_NORMAL;
    s32Ret = HI_UNF_TUNER_Connect(s_u32AtvRfTunerId, &s_stTunerConnect, 0);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_TUNER_Connect Failed \n");
        return HI_FAILURE;
    }
    
    s_bFeInited = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 SampleAtvFeDeInit(HI_VOID)
{
    HI_S32 s32Ret;

    if (HI_TRUE != s_bFeInited)
    {
        return HI_SUCCESS;
    }
    

    s32Ret = HI_UNF_TUNER_Close(s_u32AtvRfTunerId);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_TUNER_Close Failed \n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_TUNER_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_TUNER_DeInit Failed \n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_I2C_DestroyGpioI2c(s_u32AtvRfI2cNum);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_I2C_DestroyGpioI2c Failed \n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_I2C_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("call HI_UNF_I2C_DeInit Failed \n");
        return HI_FAILURE;
    }

    s_bFeInited = HI_FALSE;
    
    return HI_SUCCESS;
}

HI_S32 SampleAtvRfSifInit(HI_VOID)
{
    HI_S32 s32Ret;
    HI_UNF_SIF_OPENPARMS_S stOpenPara;
    HI_UNF_SIF_ATTR_S stAttr;
    
    if (HI_TRUE == s_bSifInited)
    {
        return HI_SUCCESS;
    }

    s32Ret = HI_UNF_SIF_Init();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_Init Failure!\n");
        return HI_FAILURE;
    }

    stOpenPara.enAIFMode = HI_UNF_SIF_AIF_MODE_INTERNEL;
    s32Ret = HI_UNF_SIF_Open(HI_UNF_SIF_ID_0, &stOpenPara);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_Open Failure!\n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_SIF_GetDefaultAttr(HI_UNF_SIF_ID_0, &stAttr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_GetDefaultAttr Failure!\n");
        return HI_FAILURE;
    }
    
    s32Ret = HI_UNF_SIF_SetAttr(HI_UNF_SIF_ID_0, &stAttr);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_SetAttr Failure!\n");
        return HI_FAILURE;
    }

    s32Ret = HI_UNF_SIF_Start(HI_UNF_SIF_ID_0);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_Start Failure!\n");
        return HI_FAILURE;
    }

    s_bSifInited = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 SampleAtvRfSifDeInit(HI_VOID)
{
    HI_S32 s32Ret;
    
    if (HI_TRUE != s_bSifInited)
    {
        return HI_SUCCESS;
    }

    s32Ret = HI_UNF_SIF_Stop(HI_UNF_SIF_ID_0);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_Stop Failure!\n");
        return HI_FAILURE;
    }
    
    s32Ret = HI_UNF_SIF_Close(HI_UNF_SIF_ID_0);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_Close Failure!\n");
        return HI_FAILURE;
    }
    
    s32Ret = HI_UNF_SIF_DeInit();
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("HI_UNF_SIF_DeInit Failure!\n");
        return HI_FAILURE;
    }
    
    s_bSifInited = HI_FALSE;

    return HI_SUCCESS;
}

HI_UNF_ATV_SYSTEM_E SampleRfGetAtvSystem(HI_UNF_COLOR_SYS_E enColorSys,
    HI_UNF_SIF_STANDARD_TYPE_E enAudioSystem)
{
    HI_UNF_ATV_SYSTEM_E enAtvSystem = HI_UNF_ATV_SYSTEM_PAL_BG;
    
    switch (enColorSys)
    {
        case HI_UNF_COLOR_SYS_PAL:
        {
            if (HI_UNF_SIF_STANDARD_BG == enAudioSystem ||
                HI_UNF_SIF_STANDARD_BG_A2== enAudioSystem ||
                HI_UNF_SIF_STANDARD_BG_NICAM== enAudioSystem)
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_PAL_BG;
            }
            else if (HI_UNF_SIF_STANDARD_DK == enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK1_A2 == enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK2_A2 == enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK3_A2== enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK_NICAM == enAudioSystem)
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_PAL_DK;
            }
            else if (HI_UNF_SIF_STANDARD_I == enAudioSystem)
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_PAL_I;
            }
            break;
        }
        case HI_UNF_COLOR_SYS_NTSC:
        {
            enAtvSystem = HI_UNF_ATV_SYSTEM_NTSC_M;
            break;
        }
        case HI_UNF_COLOR_SYS_SECAM:
        {
            if (HI_UNF_SIF_STANDARD_BG == enAudioSystem ||
                HI_UNF_SIF_STANDARD_BG_A2== enAudioSystem ||
                HI_UNF_SIF_STANDARD_BG_NICAM== enAudioSystem)
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_SECAM_BG;
            }
            else if (HI_UNF_SIF_STANDARD_DK == enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK1_A2 == enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK2_A2 == enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK3_A2== enAudioSystem ||
                HI_UNF_SIF_STANDARD_DK_NICAM == enAudioSystem)
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_SECAM_DK;
            }
            else if (HI_UNF_SIF_STANDARD_L == enAudioSystem)
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_SECAM_L_PRIME;
            }
            else
            {
                enAtvSystem = HI_UNF_ATV_SYSTEM_SECAM_LL;
            }
            
            break;
        }
        case HI_UNF_COLOR_SYS_PAL_M:
        {
            enAtvSystem = HI_UNF_ATV_SYSTEM_PAL_M;
            break;
        }
        case HI_UNF_COLOR_SYS_PAL_N:
        {
            enAtvSystem = HI_UNF_ATV_SYSTEM_PAL_N;
            break;
        }
        default:
            break;
    }

    return enAtvSystem;
}

HI_UNF_SIF_STANDARD_TYPE_E SampleAtvRfGetAudioSystem(HI_UNF_COLOR_SYS_E enColorSys)
{
    HI_S32 s32Ret;
    HI_UNF_SIF_SYSCTL_E enSysCtl = HI_UNF_SIF_SYSCTL_PAL_SUM;
    HI_UNF_SIF_STANDARD_TYPE_E enAudioSystem = HI_UNF_SIF_STANDARD_BG;
    HI_BOOL bComplete =  HI_FALSE;

    switch (enColorSys)
    {
        case HI_UNF_COLOR_SYS_PAL:
        case HI_UNF_COLOR_SYS_SECAM:
        {
            enSysCtl = HI_UNF_SIF_SYSCTL_PAL_SUM;
            enAudioSystem = HI_UNF_SIF_STANDARD_BG;
            break;
        }
        case HI_UNF_COLOR_SYS_NTSC:
        case HI_UNF_COLOR_SYS_PAL_M:
        case HI_UNF_COLOR_SYS_PAL_N:
        {
            enSysCtl = HI_UNF_SIF_SYSCTL_BTSC;
            enAudioSystem = HI_UNF_SIF_STANDARD_M;
            break;
        }
        default:
            break;
    }

    s32Ret = HI_UNF_SIF_StartAutoStandardDetection(HI_UNF_SIF_ID_0, enSysCtl);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("Call HI_UNF_SIF_StartAutoStandardDetection Fialure!\n");
    }

    usleep(200 * 1000);

    s32Ret = HI_UNF_SIF_GetDetectComplete(HI_UNF_SIF_ID_0, &bComplete);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("Call HI_UNF_SIF_GetDetectComplete Fialure!\n");
        return enAudioSystem;
    }
    if (HI_TRUE != bComplete)
    {
        sample_printf("Audio demod check system failure, use default parm!\n");
    }

    s32Ret = HI_UNF_SIF_GetAutoDetectStandard(HI_UNF_SIF_ID_0, &enAudioSystem);
    if (HI_SUCCESS != s32Ret)
    {
        sample_printf("Call HI_UNF_SIF_GetAutoDetectStandard Fialure!\n");
    }
    
    return enAudioSystem;
}

HI_VOID SampleRfPlayScan(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 u32StartFreq = 0;
    HI_U32 u32EndFreq = 0;
    HI_U32 u32Freq = 0;
    HI_UNF_TUNER_STATUS_S stTunerStatus;
    HI_UNF_TUNER_SIGNALINFO_S stSignalInfo;

    HI_UNF_COLOR_SYS_E enColorSys;
    HI_UNF_ATV_SYSTEM_E enAtvSystem;
    HI_UNF_SIF_STANDARD_TYPE_E enAudioSystem;
    int u32ASDCtl;

    stSignalInfo.enSigType = HI_UNF_TUNER_SIG_TYPE_ATV;
    
    printf("Start Scan RF Program...\n");
    printf("Please Input Start RF Freq(Khz) and End RF Freq(Khz):\n");
    scanf("%d%d", &u32StartFreq, &u32EndFreq);
    if (u32EndFreq <= u32StartFreq)
    {
        printf("Invalid Input!\n");
        return;
    }
    printf("Start Freq is %dKhz\n", u32StartFreq);
    printf("End   Freq is %dKhz\n", u32EndFreq);

    s_stSampleAtvRfScan.u32TotalNum = 0;
    s_stSampleAtvRfScan.bScaned = HI_FALSE;
    
    for (u32Freq = u32StartFreq; u32Freq <= u32EndFreq; )
    {
        printf("RF Freq is %dKhz\n", u32Freq);
        
        /* 1. 默认使用NTSC-M制式搜索 */
        s_stTunerConnect.unConnectPara.stAtv.u32Freq = u32Freq;
        s_stTunerConnect.unConnectPara.stAtv.enSystem = HI_UNF_ATV_SYSTEM_NTSC_M;
        s_stTunerConnect.unConnectPara.stAtv.enSifBw = HI_UNF_ATV_SIF_BW_NORMAL;
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_Connect(s_u32AtvRfTunerId, &s_stTunerConnect, 0));

        /* 2. 判断AIF是否Lock住 */
        usleep(30 * 1000);
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_GetStatus(s_u32AtvRfTunerId, &stTunerStatus));
        if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerStatus.enLockStatus)
        {
            u32Freq += 1000;
            continue;
        }
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_GetSignalInfo(s_u32AtvRfTunerId, &stSignalInfo));
        printf("### AIF Locked! ###\n");

        /* 3. 根据AFC跳到更准确的频点 */
        u32Freq += stSignalInfo.unSignalInfo.stAtv.s32AfcFreq;
        s_stTunerConnect.unConnectPara.stAtv.u32Freq = u32Freq;
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_Connect(s_u32AtvRfTunerId, &s_stTunerConnect, 0));
        usleep(30 * 1000);
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_GetStatus(s_u32AtvRfTunerId, &stTunerStatus));
        if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerStatus.enLockStatus)
        {
            u32Freq += 1000;
            continue;
        }
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_GetSignalInfo(s_u32AtvRfTunerId, &stSignalInfo));

        usleep(200 * 1000);

        printf("Please Select The Color system to Decoder!\n");
        printf("1: PAL and Secam\n");
        printf("2: M or N\n");        
        scanf("%d", &u32ASDCtl);

        if (u32ASDCtl == 2)
        {
            enColorSys = HI_UNF_COLOR_SYS_NTSC;
        }
        else
        {
            enColorSys = HI_UNF_COLOR_SYS_PAL;
        }

        /* 8. 获取音频制式 */        
        s_stTunerConnect.unConnectPara.stAtv.u32Freq = u32Freq;
        s_stTunerConnect.unConnectPara.stAtv.enSystem = HI_UNF_ATV_SYSTEM_PAL_DK;
        s_stTunerConnect.unConnectPara.stAtv.enSifBw  = HI_UNF_ATV_SIF_BW_WIDE;
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_Connect(s_u32AtvRfTunerId, &s_stTunerConnect, 0));
        enAudioSystem = SampleAtvRfGetAudioSystem(enColorSys);
        
        enAtvSystem = SampleRfGetAtvSystem(enColorSys, enAudioSystem);
        s_stSampleAtvRfScan.u32Freq[s_stSampleAtvRfScan.u32TotalNum] = u32Freq;
        s_stSampleAtvRfScan.enAtvSystem[s_stSampleAtvRfScan.u32TotalNum] = enAtvSystem;
        s_stSampleAtvRfScan.u32TotalNum++;
        printf("RF Freq[%d]Khz has signal!\n", u32Freq);
        
        u32Freq += 3000;
    }

    s_stSampleAtvRfScan.bScaned = HI_TRUE;
    s_stSampleAtvRfScan.u32CurNum = 0;
    sample_printf("Total Program Num is %d!\n", s_stSampleAtvRfScan.u32TotalNum);

    if (s_stSampleAtvRfScan.u32TotalNum > 0)
    {
        u32Freq = s_stSampleAtvRfScan.u32Freq[s_stSampleAtvRfScan.u32CurNum];
        enAtvSystem = s_stSampleAtvRfScan.enAtvSystem[s_stSampleAtvRfScan.u32CurNum];
        
        s_stTunerConnect.unConnectPara.stAtv.u32Freq = u32Freq;
        s_stTunerConnect.unConnectPara.stAtv.enSystem = enAtvSystem;
        s_stTunerConnect.unConnectPara.stAtv.enSifBw = HI_UNF_ATV_SIF_BW_NORMAL;
        SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_Connect(s_u32AtvRfTunerId, &s_stTunerConnect, 0));
    }
}

HI_VOID SampleRfPlayManualSet(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 u32Freq;
    HI_UNF_ATV_SYSTEM_E enAtvSystem;
    HI_UNF_SIF_STANDARD_TYPE_E enAtvAudioSys;
    
    printf("Input RF Freq:\n");
    scanf("%d", &u32Freq);

    printf("Select System:\n");
    printf("0-PAL_BG\n");
    printf("1-PAL_DK\n");
    printf("2-PAL_I\n");
    printf("3-PAL_M\n");
    printf("4-PAL_N\n");
    printf("5-SECAM_BG\n");
    printf("6-SECAM_DK\n");
    printf("7-SECAM_L_PRIME\n");
    printf("8-SECAM_LL\n");
    printf("9-NTSC_M\n");
    scanf("%d", (HI_U32 *)(&enAtvSystem));
    
    s_stTunerConnect.unConnectPara.stAtv.u32Freq  = u32Freq;
    s_stTunerConnect.unConnectPara.stAtv.enSystem = enAtvSystem;
    s_stTunerConnect.unConnectPara.stAtv.enSifBw  = HI_UNF_ATV_SIF_BW_NORMAL;
    SAMPLE_RF_CHECK_FUNC(s32Ret, HI_UNF_TUNER_Connect(s_u32AtvRfTunerId, &s_stTunerConnect, 0));

    printf("Select Audio System:\n");
    printf("0-HI_UNF_SIF_STANDARD_BG\n");
    printf("1-HI_UNF_SIF_STANDARD_BG_A2\n");
    printf("2-HI_UNF_SIF_STANDARD_BG_NICAM\n");
    printf("3-HI_UNF_SIF_STANDARD_I\n");
    printf("4-HI_UNF_SIF_STANDARD_DK\n");
    printf("5-HI_UNF_SIF_STANDARD_DK1_A2\n");
    printf("6-HI_UNF_SIF_STANDARD_DK2_A2\n");
    printf("7-HI_UNF_SIF_STANDARD_DK3_A2\n");
    printf("8-HI_UNF_SIF_STANDARD_DK_NICAM\n");
    printf("9-HI_UNF_SIF_STANDARD_L\n");
    printf("10-HI_UNF_SIF_STANDARD_M\n");
    printf("11-HI_UNF_SIF_STANDARD_M_BTSC\n");
    printf("12-HI_UNF_SIF_STANDARD_M_A2\n");
    printf("13-HI_UNF_SIF_STANDARD_M_EIA_J\n");
    scanf("%d", (HI_U32 *)(&enAtvAudioSys));
    
    HI_UNF_SIF_SetStandard(HI_UNF_SIF_ID_0, enAtvAudioSys);

    
}


#define CAST_FILE_SAVE_MAX_SIZE  500*1024*1024     //MB

HI_U32 g_u32FileSaveLimitSize;
FILE *g_pAIFile = HI_NULL;
static HI_BOOL g_StopThread = HI_FALSE;

typedef enum hi_DEMOD_SYSTEM_SELECT
{
    DEMOD_SYSTEM_SELECT_A2_DK1   ,  
    DEMOD_SYSTEM_SELECT_NICAM_DK ,
    DEMOD_SYSTEM_SELECT_A2_BG    , 
    DEMOD_SYSTEM_SELECT_NICAM_BG ,
    DEMOD_SYSTEM_SELECT_NICAM_I  , 
    DEMOD_SYSTEM_SELECT_BTSC     ,
    DEMOD_SYSTEM_SELECT_BTSC_Sap ,
    DEMOD_SYSTEM_SELECT_NICAM_L  , 
    DEMOD_SYSTEM_SELECT_AM_L     ,
    DEMOD_SYSTEM_SELECT_FM_Korea ,
    DEMOD_SYSTEM_SELECT_EIAJ     , 
    DEMOD_SYSTEM_SELECT_BUTT     , 
}DEMOD_SYSTEM_SELECT;

typedef struct hiATV_RF_S
{
    HI_U32              u32AtvFreq_KHz;
    HI_UNF_ATV_SYSTEM_E enATVSysSel;
} ATV_RF_S;

HI_VOID VirTthread(HI_VOID *args)
{
    HI_S32 Ret;
    HI_UNF_AO_FRAMEINFO_S  stAiFrame;
    HI_UNF_AO_FRAMEINFO_S *pstAiFrame = &stAiFrame;
    HI_U32 FrameSize = 0;
    HI_U32 u32TotalCounter=0;
    HI_HANDLE hVirTra = *(HI_HANDLE *)args; 
#if 0
    pstAiFrame->ps32PcmBuffer = malloc(4000);
 
    if(NULL == pstAiFrame->ps32PcmBuffer)
    {
        printf("malloc PcmBuffer error\n");
        return;
    }
#endif   
    while (!g_StopThread)
    {
        Ret = HI_UNF_SND_AcquireTrackFrame(hVirTra, pstAiFrame, 0);
        if(HI_SUCCESS != Ret)
        {
            usleep(5*1000);
            continue;
        }
        FrameSize = pstAiFrame->u32PcmSamplesPerFrame*pstAiFrame->u32Channels*pstAiFrame->s32BitPerSample /8;
        u32TotalCounter += FrameSize;
        if(u32TotalCounter <= g_u32FileSaveLimitSize*1024*1024)
        {
            //fwrite(pstAiFrame->ps32PcmBuffer, 1, FrameSize, g_pAIFile);
        }

        HI_UNF_SND_ReleaseTrackFrame(hVirTra, pstAiFrame);
    }
    
    if(g_pAIFile)
    {
        fclose(g_pAIFile);  
        g_pAIFile = HI_NULL;
    }

    return;
}


HI_VOID InitSourceAI(HI_HANDLE hTrack,HI_HANDLE *pHandleAI)
{
    HI_UNF_AI_ATTR_S stAitAttr;
    HI_UNF_AI_Init();
    HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_I2S0,&stAitAttr);
    HI_UNF_AI_Create(HI_UNF_AI_I2S0, &stAitAttr, pHandleAI);
    HI_UNF_SND_Attach(hTrack, *pHandleAI);
    HI_UNF_AI_SetEnable(*pHandleAI, HI_TRUE);
}

HI_VOID DeInitSourceAI(HI_HANDLE hTrack,HI_HANDLE *pHandleAI)
{
    HI_UNF_AI_SetEnable(*pHandleAI, HI_FALSE);
    HI_UNF_SND_Detach(hTrack, *pHandleAI);
    HI_UNF_AI_Destroy(*pHandleAI);
    HI_UNF_AI_DeInit();   
}

HI_VOID InitSourceHDMI(HI_HANDLE hTrack,HI_HANDLE *pHandleAI,HI_U32 srcHdmi)
{
    HI_UNF_AI_ATTR_S stAitAttr;
	HI_UNF_SIG_STATUS_E enStatus;
	HI_UNF_HDMIRX_TIMING_INFO_S stTimingInfo;
	HI_UNF_AI_HDMI_ATTR_S stAudioInfo;

    HI_UNF_HDMIRX_Connect(srcHdmi);
	while (1)
	{
   		enStatus = HI_UNF_HDMIRX_GetSignalStatus(&enStatus);
		if(enStatus == HI_UNF_SIG_SUPPORT)
		{
			break;
		}
		sleep(1);
		printf(".");
	}
   
   enStatus = HI_UNF_HDMIRX_GetTimingInfo(&stTimingInfo);
   if (HI_FAILURE != enStatus)
   {
	   printf("u32Width;		%d\n", stTimingInfo.u32Width		);
	   printf("u32Height;		%d\n", stTimingInfo.u32Height		);
	   printf("u32FrameRate;	%d\n", stTimingInfo.u32FrameRate	);
	   printf("enColorSpace;0:601,1:709,2:RGB	  %d\n", stTimingInfo.enColorSpace	  );
	   printf("enPixelFmt;0:RGB,1:420,2:422, 3:444		%d\n", stTimingInfo.enPixelFmt		);
	   printf("enBitWidth;0:8bit,1:10bit,2:12bit	  %d\n", stTimingInfo.enBitWidth	  );
	   printf("bInterlace;0:Procc;1:Inter	   %d\n", stTimingInfo.bInterlace	   );
	   printf("enOverSampleMode;0:1X;1:2X,2:4X	%d\n", stTimingInfo.enOversample);
	   printf("en3dFmt; 0:2D		%d\n", stTimingInfo.en3dFmt);
	   printf("bDviMode;		%d\n", stTimingInfo.bHdmiMode		 );
	   printf("u32Vblank;		%d\n", stTimingInfo.u32Vblank		);
	   printf("bPcMode; 	  %d\n", stTimingInfo.bPcMode		);
	   printf("u32TimingIndex;		 %d\n", stTimingInfo.u32TimingIdx);
	   //break;
   }
   else
   	{
   		printf("HI_UNF_HDMIRX_GetTimingInfo error\n");
   	}
   sleep(1);
   enStatus = HI_UNF_HDMIRX_GetAudioInfo(&stAudioInfo);
   if (HI_FAILURE != enStatus)
   {
	   printf("enChannel:%d\n", stAudioInfo.enChannel);
	   printf("enBitDepth:%d\n", stAudioInfo.enBitDepth);
	   printf("enSampleRate:%d\n", stAudioInfo.enSampleRate);
	   printf("enHdmiAudioDataFormat:%d\n", stAudioInfo.enHdmiAudioDataFormat);
	   sleep(1);
   	}
	
    HI_UNF_AI_Init();
    HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_HDMI0,&stAitAttr);
    HI_UNF_AI_Create(HI_UNF_AI_HDMI0, &stAitAttr, pHandleAI);
    HI_UNF_SND_Attach(hTrack, *pHandleAI);
    HI_UNF_AI_SetEnable(*pHandleAI, HI_TRUE);
}

HI_VOID DeInitSourceHDMI(HI_HANDLE hTrack,HI_HANDLE *pHandleAI)
{
    HI_UNF_AI_SetEnable(*pHandleAI, HI_FALSE);
    HI_UNF_SND_Detach(hTrack, *pHandleAI);
    HI_UNF_AI_Destroy(*pHandleAI);
    HI_UNF_AI_DeInit();   
	
	HI_UNF_HDMIRX_DisConnect();
//	HI_UNF_HDMIRX_DeInit();
}


/************************
  HI_UNF_AI_ADC0 :MIC_In
  HI_UNF_AI_ADC1:VGA_In
  HI_UNF_AI_ADC2:AV0
  HI_UNF_AI_ADC3:YPbPr
  HI_UNF_AI_ADC4:AV1
*************************/  
typedef enum 
{
    HI_UNF_AI_SAMPLE_VGA,
    HI_UNF_AI_SAMPLE_AV0,
    HI_UNF_AI_SAMPLE_AV1,
    HI_UNF_AI_SAMPLE_YPbPr,
    HI_UNF_AI_SAMPLE_MIC,
    HI_UNF_AI_SAMPLE_BUTT,
} HI_UNF_AI_SAMPLE_SRC_E;

HI_VOID InitSourceCvbs(HI_HANDLE hTrack,HI_HANDLE *pHandleAI, HI_UNF_AI_SAMPLE_SRC_E enSource)
{
    HI_UNF_AI_ATTR_S stAitAttr;
    HI_UNF_AI_Init();

    switch (enSource)
    {
        case HI_UNF_AI_SAMPLE_VGA:
            HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC1,&stAitAttr);
            HI_UNF_AI_Create(HI_UNF_AI_ADC1, &stAitAttr, pHandleAI);
            break;
        case HI_UNF_AI_SAMPLE_AV0:
            HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC2,&stAitAttr);
            HI_UNF_AI_Create(HI_UNF_AI_ADC2, &stAitAttr, pHandleAI);
            break;                   
        case HI_UNF_AI_SAMPLE_AV1:
            HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC4,&stAitAttr);
            HI_UNF_AI_Create(HI_UNF_AI_ADC4, &stAitAttr, pHandleAI);
            break;
        case HI_UNF_AI_SAMPLE_YPbPr:
            HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC3,&stAitAttr);
            HI_UNF_AI_Create(HI_UNF_AI_ADC3, &stAitAttr, pHandleAI);
            break;      
        case HI_UNF_AI_SAMPLE_MIC:
            HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_ADC0,&stAitAttr);
            HI_UNF_AI_Create(HI_UNF_AI_ADC0, &stAitAttr, pHandleAI);
            break;    
        default:
            break;
    }

    HI_UNF_SND_Attach(hTrack, *pHandleAI);
    HI_UNF_AI_SetEnable(*pHandleAI, HI_TRUE);
}

HI_VOID DeInitSourceCvbs(HI_HANDLE hTrack,HI_HANDLE *pHandleAI)
{
    HI_UNF_AI_SetEnable(*pHandleAI, HI_FALSE);
    HI_UNF_SND_Detach(hTrack, *pHandleAI);
    HI_UNF_AI_Destroy(*pHandleAI);
    HI_UNF_AI_DeInit();   
}

HI_VOID InitSourceSIF(HI_HANDLE hTrack,HI_HANDLE *pHandleAI)
{
    HI_UNF_AI_ATTR_S stAitAttr;
    int              u32FrontEnd;

    SampleAtvRfFeInit();
    SampleAtvRfSifInit();

    printf("Please Select The way to setting FrontEnd!\n");
    printf("1: MANNUAM\n");
    printf("2: Auto Scan\n");        
    scanf("%d", &u32FrontEnd);

    if (u32FrontEnd == 1)
    {
        SampleRfPlayManualSet();
    }
    else
    {        
        SampleRfPlayScan();
    }

    HI_UNF_AI_Init();
    HI_UNF_AI_GetDefaultAttr(HI_UNF_AI_SIF0,&stAitAttr);
    HI_UNF_AI_Create(HI_UNF_AI_SIF0, &stAitAttr, pHandleAI);
    HI_UNF_SND_Attach(hTrack, *pHandleAI);
    HI_UNF_AI_SetEnable(*pHandleAI, HI_TRUE);
   
}

HI_VOID DeInitSourceSIF(HI_HANDLE hTrack,HI_HANDLE *pHandleAI)
{
    HI_UNF_AI_SetEnable(*pHandleAI, HI_FALSE);
    HI_UNF_SND_Detach(hTrack, *pHandleAI);
    HI_UNF_AI_Destroy(*pHandleAI);
    HI_UNF_AI_DeInit();    

    SampleAtvFeDeInit();
    SampleAtvRfSifDeInit();
}


FILE             *g_pAudEsFile = HI_NULL;
static pthread_t g_EsThd;

HI_S32 g_AudEsFileOffest;

HI_VOID EsTthread(HI_VOID *args)
{
    HI_HANDLE hAvplay;
    HI_UNF_STREAM_BUF_S StreamBuf;
    HI_U32 Readlen;
    HI_S32 Ret;
    HI_BOOL bVidBufAvail = HI_TRUE, bAudBufAvail = HI_TRUE;

    hAvplay = (HI_HANDLE)args;
    bVidBufAvail = HI_FALSE;
    bAudBufAvail = HI_FALSE;
    static int counter=0;

    while (!g_StopThread)
    {
            Ret = HI_UNF_AVPLAY_GetBuf(hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, 0x1000, &StreamBuf, 0);
            if (HI_SUCCESS == Ret)
            {
                bAudBufAvail = HI_TRUE;
                Readlen = fread(StreamBuf.pu8Data, sizeof(HI_S8), 0x1000, g_pAudEsFile);
               
                if (Readlen > 0)
                {
                    counter++;
                    Ret = HI_UNF_AVPLAY_PutBuf(hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_AUD, Readlen, 0);
                    if (Ret != HI_SUCCESS)
                    {
                        sample_printf("call HI_UNF_AVPLAY_PutBuf failed.\n");
                    }
                }
                else if (Readlen == 0)
                {
                    sample_printf("read aud file end and rewind!\n");
                    rewind(g_pAudEsFile);
                    if (g_AudEsFileOffest)
                    {
                        fseek(g_pAudEsFile, g_AudEsFileOffest, SEEK_SET);
                    }
                }
                else
                {
                    perror("read aud file error\n");
                }
            }
            else if (Ret != HI_SUCCESS)
            {
                bAudBufAvail = HI_FALSE;
            }

            usleep(1000 * 10);
    }

    return;
}

HI_VOID InitSourceAVPLAY(HI_HANDLE hTrack,HI_HANDLE *pHandleAV)
{
    HI_S32 Ret; 
    HI_UNF_AVPLAY_ATTR_S stAvAttr;

    Ret = HI_UNF_AVPLAY_Init();
    Ret |= HI_UNF_AVPLAY_GetDefaultConfig(&stAvAttr, HI_UNF_AVPLAY_STREAM_TYPE_ES);
    Ret |= HI_UNF_AVPLAY_Create(&stAvAttr, pHandleAV);
    Ret |= HI_UNF_AVPLAY_ChnOpen(*pHandleAV, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    Ret |= HIADP_AVPlay_SetAdecAttr(*pHandleAV, HA_AUDIO_ID_MP3, HD_DEC_MODE_RAWPCM, 0);    
    Ret |= HI_UNF_SND_Attach(hTrack, *pHandleAV);

    g_StopThread = HI_FALSE;
    g_pAudEsFile = fopen("./father.mp3", "rb");
    if (!g_pAudEsFile) sample_printf("open file %s error!\n", "./father.mp3");

    pthread_create(&g_EsThd, HI_NULL, (HI_VOID *)EsTthread, (HI_VOID *)(*pHandleAV));
    
    Ret |= HI_UNF_AVPLAY_Start(*pHandleAV, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    sample_printf("Init AVplay 0x%x\n", Ret);
   
}

HI_VOID DeInitSourceAVPLAY(HI_HANDLE hTrack,HI_HANDLE *pHandleAV)
{
    
    HI_S32 Ret; 
    Ret = HI_UNF_AVPLAY_Stop(*pHandleAV, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);    
    
    g_StopThread = HI_TRUE;
    pthread_join(g_EsThd, HI_NULL);

    fclose(g_pAudEsFile);
    
    Ret |= HI_UNF_SND_Detach(hTrack, *pHandleAV);       
    Ret |= HI_UNF_AVPLAY_ChnClose(*pHandleAV, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    Ret |= HI_UNF_AVPLAY_Destroy(*pHandleAV);
    Ret |= HI_UNF_AVPLAY_DeInit();    
}

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 Ret;    
    HI_HANDLE HandleAI,HandleSIF, HandleAVPLAY, HandleVGA, HandleAV0, HandleAV1, HandleYPbPr, HandleMIC, HandleHDMI;
    HI_HANDLE hTrackSlave;
    HI_UNF_AUDIOTRACK_ATTR_S  stTrackAttr;        
    
    HI_CHAR InputCmd[32];

    if (argc > 2)
    {
#if 1
        printf(" usage: sample_audio_switch \n");
        printf(" examples: \n");
        printf(" sample_audio_switch\n");        
#endif
        return 0;
    }

    HI_SYS_Init();
	
    HI_UNF_HDMIRX_Init();
//	HI_AMP_Init();
//	HI_AMP_SetMute(HI_FALSE);


    Ret = HIADP_Snd_Init();
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call SndInit failed.\n");
        goto SYS_DEINIT;
    }

    Ret = HI_UNF_SND_GetDefaultTrackAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_GetDefaultTrackAttr failed.\n");
        goto SND_DEINIT;
    }
    Ret = HI_UNF_SND_CreateTrack(HI_UNF_SND_0, &stTrackAttr, &hTrackSlave);
    if (Ret != HI_SUCCESS)
    {
        sample_printf("call HI_UNF_SND_CreateTrack failed.\n");
        goto SND_DEINIT;
    }

    HIADP_AVPlay_RegADecLib();
#if 1
	while(1)
	{
	#if 1
		sample_printf("AVPlay\n");
        InitSourceAVPLAY(hTrackSlave,&HandleAVPLAY);
		sleep(10);
        DeInitSourceAVPLAY(hTrackSlave,&HandleAVPLAY);

		sample_printf("VGA\n");		
        InitSourceCvbs(hTrackSlave,&HandleVGA, HI_UNF_AI_SAMPLE_VGA);
		sleep(10);
        DeInitSourceCvbs(hTrackSlave,&HandleVGA);

		sample_printf("HDMI1\n");	
		InitSourceHDMI(hTrackSlave,&HandleHDMI,1);
		sleep(10);
		DeInitSourceHDMI(hTrackSlave,&HandleHDMI);

		sample_printf("AV0\n");	
        InitSourceCvbs(hTrackSlave, &HandleAV0, HI_UNF_AI_SAMPLE_AV0);
		sleep(10);
        DeInitSourceCvbs(hTrackSlave, &HandleAV0);

		sample_printf("HDMI0\n");	
		InitSourceHDMI(hTrackSlave,&HandleHDMI,0);
		sleep(10);
		DeInitSourceHDMI(hTrackSlave,&HandleHDMI);

		sample_printf("MIC\n");	
        InitSourceCvbs(hTrackSlave, &HandleAV0, HI_UNF_AI_SAMPLE_MIC);
		sleep(10);
        DeInitSourceCvbs(hTrackSlave, &HandleAV0);

		sample_printf("HDMI1\n");	
		InitSourceHDMI(hTrackSlave,&HandleHDMI,1);
		sleep(10);
		DeInitSourceHDMI(hTrackSlave,&HandleHDMI);
	#else		
		sample_printf("MIC\n"); 
		InitSourceCvbs(hTrackSlave, &HandleAV0, HI_UNF_AI_SAMPLE_MIC);
		sleep(10);
		DeInitSourceCvbs(hTrackSlave, &HandleAV0);
	#endif
		
	}
#else
    InitSourceCvbs(hTrackSlave,&HandleVGA, HI_UNF_AI_SAMPLE_VGA);
    
    printf("please input the q to quit!Now is VGA\n");

    while (1)
    { 
        printf("input source/exit source\n");
        printf("       SIF   (s/6)\n");
        printf("       TLV   (t/7)\n");
        printf("       AVPLAY(a/8)\n");
        printf("       VGA   (v/1)\n");
        printf("       AV0   (k/2)\n");
        printf("       AV1   (j/3)\n");
        printf("       YPbPr (y/5)\n");
        printf("       MIC   (m/4)\n");
        printf("       HDMI  (h/9)\n");
        
        SAMPLE_GET_INPUTCMD(InputCmd);

        if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        } 

        if ('s' == InputCmd[0])
        {
            InitSourceSIF(hTrackSlave, &HandleSIF);
        }
        if ('6' == InputCmd[0])
        {
            DeInitSourceSIF(hTrackSlave, &HandleSIF);
        }        

        if ('t' == InputCmd[0])
        {
            InitSourceAI(hTrackSlave, &HandleAI);
        }
        if ('7' == InputCmd[0])
        {
            DeInitSourceAI(hTrackSlave, &HandleAI);
        }
            
        if ('a' == InputCmd[0])
        {
            InitSourceAVPLAY(hTrackSlave,&HandleAVPLAY);
        }
        if ('8' == InputCmd[0])     
        {
            DeInitSourceAVPLAY(hTrackSlave,&HandleAVPLAY);
        }
        if ('v' == InputCmd[0])     
        {
            InitSourceCvbs(hTrackSlave,&HandleVGA, HI_UNF_AI_SAMPLE_VGA);
        }
        if ('1' == InputCmd[0])     
        {
            DeInitSourceCvbs(hTrackSlave,&HandleVGA);
        }

        if ('k' == InputCmd[0])     
        {
            InitSourceCvbs(hTrackSlave, &HandleAV0, HI_UNF_AI_SAMPLE_AV0);
        }
        if ('2' == InputCmd[0])     
        {
            DeInitSourceCvbs(hTrackSlave, &HandleAV0);
        }

        if ('j' == InputCmd[0])     
        {
            InitSourceCvbs(hTrackSlave,&HandleAV1, HI_UNF_AI_SAMPLE_AV1);
        }
        if ('3' == InputCmd[0])     
        {
            DeInitSourceCvbs(hTrackSlave,&HandleAV1);
        }

        if ('y' == InputCmd[0])     
        {
            InitSourceCvbs(hTrackSlave,&HandleYPbPr, HI_UNF_AI_SAMPLE_YPbPr);
        }
        if ('5' == InputCmd[0])     
        {
            DeInitSourceCvbs(hTrackSlave,&HandleYPbPr);
        }

        if ('m' == InputCmd[0])
        {
            InitSourceCvbs(hTrackSlave,&HandleMIC, HI_UNF_AI_SAMPLE_MIC);
        }
        if ('4' == InputCmd[0])     
        {
            DeInitSourceCvbs(hTrackSlave,&HandleMIC);
        }

        if ('h' == InputCmd[0])
        {
            InitSourceHDMI(hTrackSlave,&HandleHDMI);
        }
        if ('9' == InputCmd[0])     
        {
            DeInitSourceHDMI(hTrackSlave,&HandleHDMI);
        }
        
    }
#endif        
    HI_UNF_SND_DestroyTrack(hTrackSlave);
SND_DEINIT:
    HIADP_Snd_DeInit();
SYS_DEINIT:
    HI_SYS_DeInit();

    return 0;
}

