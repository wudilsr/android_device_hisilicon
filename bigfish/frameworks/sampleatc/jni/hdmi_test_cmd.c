/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hmdi_test_cmd.c
  Version       : 0.0.1
  Author        : Hisilicon multimedia software group
  Created       : 2010/07/08
  Description   :
  History       :
  1.Date        : 2010/07/08
    Author      : l00168554
    Modification: Created file

******************************************************************************/
#include "stdlib.h"
#include <sys/time.h>
#include "hi_adp.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_disp.h"
#include "hdmi_test_cmd.h"
#include "hi_unf_vo.h"
#include "hi_adp_hdmi.h"
#include "hi_unf_ecs.h"
#include "string.h"
//#include "hi_struct.h"
//#include "hi_go.h"
//#include "hi_go_comm.h"

 #include "HA.AUDIO.DOLBYPLUS.decode.h"

/* Macro */
// cec max parm > 15
#define HDMI_MAX_ARGC       20
#define HDMI_MAX_PAMRM_SIZE 30

/* Variable */
static HI_U8 args[HDMI_MAX_ARGC][HDMI_MAX_PAMRM_SIZE];
static HDMI_INPUT_PARAM_S Hdmi_V_Timing[] =
{
    {HI_UNF_ENC_FMT_1080P_60,   "1080P_60",},      /**<1080p60 HZ*/
    {HI_UNF_ENC_FMT_1080P_50,   "1080P_50",},      /**<1080p50 HZ*/
    {HI_UNF_ENC_FMT_1080P_30,   "1080P_30",},      /**<1080p30 HZ*/
    {HI_UNF_ENC_FMT_1080P_25,   "1080P_25",},      /**<1080p25 HZ*/
    {HI_UNF_ENC_FMT_1080P_24,   "1080P_24",},      /**<1080p24 HZ*/

    {HI_UNF_ENC_FMT_1080i_60,   "1080i_60",},      /**<1080i60 HZ */
    {HI_UNF_ENC_FMT_1080i_50,   "1080i_50",},      /**<1080i60 HZ */

    {HI_UNF_ENC_FMT_720P_60,    "720P_60",},       /**<720p60 HZ */
    {HI_UNF_ENC_FMT_720P_50,     "720P_50",},      /**<720p50 HZ */

    {HI_UNF_ENC_FMT_576P_50,    "576P_50",},       /**<576p50 HZ */
    {HI_UNF_ENC_FMT_480P_60,    "480P_60",},       /**<480p60 HZ */

    {HI_UNF_ENC_FMT_PAL,        "576i_50 PAL",},   /* B D G H I PAL */
    {HI_UNF_ENC_FMT_NTSC,       "480i_60 NTSC",},  /* (M)NTSC       */

    {HI_UNF_ENC_FMT_861D_640X480_60, "640x480p_60",},  /* 640x480        */

    {HI_UNF_ENC_FMT_VESA_800X600_60, "800x600",},        /* 800x600       */
    {HI_UNF_ENC_FMT_VESA_1024X768_60, "1024X768",},      /* 1024X768       */
    {HI_UNF_ENC_FMT_VESA_1280X1024_60, "1280X1024",},    /* 1280X1024      */
    {HI_UNF_ENC_FMT_VESA_1366X768_60, "1366X768",},      /* 1366X768       */
    {HI_UNF_ENC_FMT_VESA_1440X900_60, "1440X900",},      /* 1440X900       */
    {HI_UNF_ENC_FMT_VESA_1440X900_60_RB, "1440X900_RB",},/* 1440X900_RB    */
    {HI_UNF_ENC_FMT_VESA_1600X1200_60, "1600X1200",},    /* 1600X1200      */
    {HI_UNF_ENC_FMT_VESA_1920X1200_60, "1920X1200",},    /* 1920X1200      */
    {HI_UNF_ENC_FMT_VESA_2048X1152_60, "2048X1152",},    /* 2048X1152      */
    {HI_UNF_ENC_FMT_VESA_2560X1440_60_RB, "2560X1440_RB",},    /* 2560X1440      */
    {HI_UNF_ENC_FMT_VESA_2560X1600_60_RB, "2560X1600_RB",},    /* 2560X1600      */

    {HI_UNF_ENC_FMT_3840X2160_24, "3840X2160_24",},    /* 4Kx2K_24      */
    {HI_UNF_ENC_FMT_3840X2160_25, "3840X2160_25",},    /* 4Kx2K_25      */
    {HI_UNF_ENC_FMT_3840X2160_30, "3840X2160_30",},    /* 4Kx2K_30      */
    {HI_UNF_ENC_FMT_4096X2160_24, "4096X2160_24",},    /* 4Kx2K_30      */

    {HI_UNF_ENC_FMT_3840X2160_23_976, "3840X2160_23_976",},    /* 4Kx2K_23.976      */
    {HI_UNF_ENC_FMT_3840X2160_29_97, "3840*2160_29_97",},      /* 4Kx2K_29.97      */
    {HI_UNF_ENC_FMT_720P_59_94, "1280*720_59_94",},            /* 720p_59.94      */
    {HI_UNF_ENC_FMT_1080P_59_94, "1920*1080_59_94",},          /* 1080p_59.94      */
    {HI_UNF_ENC_FMT_1080P_29_97, "1920*1080_29_97",},          /* 1080p_29.97      */
    {HI_UNF_ENC_FMT_1080P_23_976, "1920*1080_23_976",},        /* 1080p_23.976      */
    {HI_UNF_ENC_FMT_1080i_59_94, "1920*1080i_59_94",},         /* 1080i_59.94      */
#if 0
    {HI_UNF_ENC_FMT_PAL,        "PAL",},           /* B D G H I PAL */
    {HI_UNF_ENC_FMT_PAL_N,      "PAL_N",},         /* (N)PAL        */
    {HI_UNF_ENC_FMT_PAL_Nc,     "PAL_Nc",},        /* (Nc)PAL       */

    {HI_UNF_ENC_FMT_NTSC,       "NTSC",},          /* (M)NTSC       */
    {HI_UNF_ENC_FMT_NTSC_J,     "NTSC_J",},        /* NTSC-J        */
    {HI_UNF_ENC_FMT_NTSC_PAL_M, "NTSC_M",},        /* (M)PAL        */

    {HI_UNF_ENC_FMT_SECAM_SIN,  "SECAM_SIN",},     /**< SECAM_SIN*/
    {HI_UNF_ENC_FMT_SECAM_COS,  "SECAM_COS",},     /**< SECAM_COS*/
#endif
    {HI_UNF_ENC_FMT_BUTT,       "BUTT",},          /* MAX */
};

#define HDMI_MAX_COLOR_MODE  3
static HDMI_INPUT_PARAM_S Hdmi_V_ColorMode[HDMI_MAX_COLOR_MODE] =
{
    {0,   "RGB444",},        /* RGB444 Mode */
    {1,   "YCbCr422",},      /* YCbCr422 Mode */
    {2,   "YCbCr444",},      /* YCbCr444 Mode */
};

#define HDMI_MAX_ASPECTRATE  2
static HDMI_INPUT_PARAM_S Hdmi_V_AspectRate[2] =
{
    {0,   "4:3",},        /* RGB444 Mode */
    {1,   "16:9",},      /* YCbCr422 Mode */
};

#define HDMI_MAX_AUDIO_FREQNCE  7
static HDMI_INPUT_PARAM_S Hdmi_A_Frequent[HDMI_MAX_AUDIO_FREQNCE] =
{
    {0,   "32000",},        /* 32K */
    {1,   "44100",},        /* 44.1K */
    {2,   "48000",},        /* 48K */
    {3,   "88200",},        /* 88.2K */
    {4,   "96000",},        /* 96K */
    {5,   "176400",},       /* 176.4K */
    {6,   "192000",},       /* 192K */
};

HDMI_SAMPLE_CONTEXT_S g_stHDMI_Sample_Context;

static HI_UNF_HDMI_ID_E enTest_Hdmi_ID = HI_UNF_HDMI_ID_0;

extern HI_U32 g_HDCPFlag;
//extern HI_U32 g_Audiotype;
HI_HANDLE g_hWin;
/* ---------------Local Function-------------------------- */
static HI_U8  Hdmi_AdjustString(HI_CHAR *ptr);
static HI_U32 Hdmi_ParseArg(HI_U32 argc);
static HI_U32 hdmi_hdmi_force(void);
static HI_U32 hdmi_dvi_force(void);
static HI_U32 hdmi_display_edid(void);
static HI_U32 hdmi_out_enable(void);
static HI_U32 hdmi_out_disable(void);
HI_U32 hdmi_video_timing(HI_U32 u32TimingIndex);
static HI_U32 hdmi_color_mode(HI_U32 u32ColorIndex);
static HI_U32 hdmi_apectrate(HI_U32 u32apectrateIndex);
static HI_U32 hdmi_reversecolor(HI_U32 u32reversecolorIndex);
static HI_U32 hdmi_rgbfullrange(HI_U32 u32fullrangeIndex);
static HI_U32 hdmi_ycbcrfullrange(HI_U32 u32fullrangeIndex);
static HI_U32 hdmi_attachIntf(HI_U32 u32dispChnIndex);
static HI_U32 hdmi_detachIntf(HI_U32 u32dispChnIndex);
static HI_U32 hdmi_v_mute(HI_BOOL bMuteVideo);
static HI_U32 hdmi_a_freq(HI_U32 u32AFreqIndex);
//static HI_U32 hdmi_a_inputmode(HI_U32 inputmode);
static HI_U32 hdmi_a_mute(HI_BOOL bMuteAudio);
static HI_U32 hdmi_a_downsample(HI_U32 factor, HI_U32 AOfreq);
static HI_U32 hdmi_av_mute(HI_U32 u32MuteFlag);
HI_U32 hdmi_deepcolor(HI_U32 u32DeepColorFlag);
static HI_U32 hdmi_xvycc(HI_U32 xvYCCFlag);
static HI_U32 hdmi_a_channel8(HI_U32 channel8flag);
static HI_U32 hdmi_a_passtru(HI_U32 passTruFlag);
HI_U32 hdmi_a_compress(HI_U32 compressFlag);
static HI_U32 hdmi_cec_autoping(void);
static HI_U32 hdmi_cec_setcmd(HI_U8 destAddr, HI_U8 u8Opcode, HI_U8 *data, HI_U8 Datalength);
static HI_U32 hdmi_ResetTest(HI_U32 loop);
static HI_U32 hdmi_ReOpenTest(HI_U32 loop);
static HI_U32 hdmi_ReStartTest(HI_U32 loop);
static HI_U32 hdmi_EDIDTest(HI_U32 loop);
static HI_U32 hdmi_RegDebug(HI_U32 Debugflag);
static HI_U32 hdmi_RandomSwitch(HI_U8 EnableFlag);

static HI_U32 hdmi_set_disp_3d(HI_UNF_DISP_3D_E en3D);

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
static HI_U32 hdmi_picture_display(void);
static HI_U32 hdmi_picture_clear(void);
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

static HI_U32 Hdmi_String_to_Integer(HI_U8 *ptr)
{
    HI_U32 index, stringLen = 0;

    if (NULL == ptr)
    {
        return 0xFFFFFFFF;
    }
    stringLen = strlen((char *)ptr);

    if(stringLen > 16)
    {
        return 0xFFFFFFFF;
    }

    for (index = 0; index < stringLen; index ++)
    {
        if ( (ptr[index] >= '0') && (ptr[index] <= '9') )
        {
            continue;
        }
        return 0xFFFFFFFF;
    }

    return (atoi((char *)ptr));
}

static HI_U32 Hdmi_String_to_Hexadecimal(HI_U8 *ptr)
{
    HI_U32 result;

    if (NULL == ptr)
    {
        return 0xFFFFFFFF;
    }

    result = strtol((const char *)ptr, NULL, 16);

    return (result);
}

/*adjust input parameter*/
static HI_U8 Hdmi_AdjustString(HI_CHAR *ptr)
{
    HI_U32 i;

    /* Search the first charater char */
    while(*ptr==' ' && *ptr++ != '\0')
    {
        ;
    }

    /* change to little case charater */
    for(i=strlen((char *)ptr); i>0; i--)
    {
        if ((*(ptr+i-1) >= 'A') && (*(ptr+i-1) <= 'Z'))
        {
            *(ptr+i-1) = (*(ptr+i-1) - 'A') + 'a';
        }
    }

    for(i=strlen((char *)ptr);i>0;i--)
    {
        if (*(ptr+i-1) == 0x0a || *(ptr+i-1) == ' ')
        {
            *(ptr+i-1) = '\0';
        }
        else
        {
            break;
        }
    }

    for(i=0; i<HDMI_MAX_ARGC; i++)
    {
        memset(args[i], 0, HDMI_MAX_PAMRM_SIZE);
    }
    /* fill args[][] with input string */
    for(i=0; i<HDMI_MAX_ARGC; i++)
    {
        HI_U8 j = 0;
        while(*ptr==' ' && *ptr++ != '\0')
            ;

        while((*ptr !=' ') && (*ptr!='\0'))
        {
            args[i][j++] = *ptr++;
        }

        args[i][j] = '\0';
        if ('\0' == *ptr)
        {
            i++;
            break;
        }
        args[i][j] = '\0';
    }

    return i;
}

static HI_U32 Hdmi_ParseArg(HI_U32 argc)
{
    HI_U32 i, index;
    HI_U32 RetError = HI_SUCCESS;

    printf("input parameter Num:%d ", argc);
    for (i = 0 ; i < argc; i++)
    {
        printf("argv[%d]:%s, ", i, args[i]);
    }
    printf("\n");

    /* Parse HDMI input command */
    if ( (0 == strcmp("help", (char *)args[0])) || (0 == strcmp("h", (char *)args[0])) )
    {
        printf("List all testtool command\n");
        printf("help          list all command we provide\n");
        printf("q             quit sample test\n");
//      printf("hdmi_debug    Display all relative status\n");
//        printf("play_stop     force to stop  A/V decoder\n");
//        printf("play_start    force to start A/V decoder\n");
        printf("hdmi_hdmi_force   force to hdmi output\n");
        printf("hdmi_dvi_force    force to enter dvi output mode\n");
        printf("hdmi_display_edid display current sink EDID message\n");
//        printf("hdmi_out_enable   enable hdmi/dvi output\n");
//        printf("hdmi_out_disable  disable hdmi/dvi output\n");
        printf("hdmi_deepcolor    set video deepcolor mode\n");
        printf("hdmi_xvycc        set video xvYCC output\n");
        printf("hdmi_video_timing set video output timing format\n");
        printf("hdmi_color_mode   set video color output(RGB/YCbCr)\n");
        printf("hdmi_apectrate    set video apectrate only to 576P/I, 480P/I\n");
        printf("hdmi_reversecolor set video color space 601<-->709\n");
        printf("hdmi_rgbfullrange    set video color RGB fullrange\n");
        printf("hdmi_ycbcrfullrange  set video color YCbCr fullrange\n");
        printf("hdmi_attach_intf  attach hdmi to disp \n");
        printf("hdmi_detach_intf  detach hdmi from disp \n");


#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        printf("hdmi_v_mute       set video output mute/unmute\n");
        printf("hdmi_a_freq       set audio output frequence\n");

        printf("hdmi_a_mute       set audio output mute/unmute\n");
        printf("hdmi_a_downsample set audio output downsample\n");
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        printf("hdmi_av_mute      set video&audio mute/unmute\n");
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        printf("hdmi_a_channel8  set audio multi channel(8) output\n");
        printf("hdmi_a_passtru       set audio passThrough / No passThrough\n");
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        printf("hdmi_hdcp         set HDCP, to be define\n");
        printf("hdmi_cecautoping  set CEC command, Autoping\n");
        printf("cec_setcm         set CEC command\n");
        printf("cec_getcm         get CEC command\n");
        printf("cec_enable        enable cec.\n");
        printf("cec_disable        enable cec.\n");
        printf("hdmi_reset        set hdmi reset command\n");
        printf("hdmi_reopen       set hdmi reopen command\n");
        printf("hdmi_restart      set hdmi restart command\n");
        printf("hdmi_edid_test    set hdmi edid test command\n");
        printf("hdmi_reg          debug hdmi register command\n");
        printf("hdmi_randomswitch set hdmi random switch\n");
        printf("hdmi_set_disp_3d  Set disp 3d mode\n");
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        printf("hdmi_picture_display display a picture\n");
        printf("hdmi_picture_clear   clear a picure\n");
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
    }
    else if (0 == strcmp("play_stop", (char *)args[0]))
    {
        /* force to stop A/V decoder */
        printf("do not need to support \n");
        return RetError;
    }
    else if (0 == strcmp("play_start", (char *)args[0]))
    {
        /* force to start A/V decoder */
        printf("do not need to support \n");
        return RetError;
    }
    else if (0 == strcmp("hdmi_hdmi_force", (char *)args[0]))
    {
        /* force to Output hdmi signal */
        RetError = hdmi_hdmi_force();
    }
    else if (0 == strcmp("hdmi_dvi_force", (char *)args[0]))
    {
        /* force to Output dvi signal */
        RetError = hdmi_dvi_force();
    }
#if 1
    else if (0 == strcmp("hdmi_display_edid", (char *)args[0]))
    {
        /* display EDID from memory */
        RetError = hdmi_display_edid();
    }
#endif
    else if (0 == strcmp("hdmi_out_enable", (char *)args[0]))
    {
        /* enable hdmi output */
        RetError = hdmi_out_enable();
    }
    else if (0 == strcmp("hdmi_out_disable", (char *)args[0]))
    {
        /* disable hdmi output */
        RetError = hdmi_out_disable();
    }
    else if (0 == strcmp("hdmi_deepcolor", (char *)args[0]))
    {
        HI_U8 u8DeepColorIndex;
        /* set video Deep color */
        if (1 >= argc)
        {
            printf("Usage:hdmi_deepcolor DeepColorflag\n");
            printf("DeepColorflag: 0:Deep Color 24bit\n");
            printf("DeepColorflag: 1:Deep Color 30bit\n");
            printf("DeepColorflag: 2:Deep Color 36bit\n");
            printf("DeepColorflag: >=3:Deep Color Off\n");
            return RetError;
        }
        u8DeepColorIndex = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (u8DeepColorIndex > HI_UNF_HDMI_DEEP_COLOR_36BIT )
        {
            printf("input deep color mode is larget than Max index:%d\n", HI_UNF_HDMI_DEEP_COLOR_BUTT);
            return HI_FAILURE;
        }
        RetError = hdmi_deepcolor(u8DeepColorIndex);
    }
    else if (0 == strcmp("hdmi_xvycc", (char *)args[0]))
    {
        /* set video xvYCC */
        if (1 >= argc)
        {
            printf("Usage:hdmi_xvycc xvYCCflag\n");
            printf("xvYCCflag: 0:disable, >=1:enable\n");
            return RetError;
        }
        RetError = hdmi_xvycc(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_video_timing", (char *)args[0]))
    {
        HI_U32 timing_index;
        //minus 1 butt fmt
        HI_U32 u32Len = (sizeof(Hdmi_V_Timing) / sizeof(HDMI_INPUT_PARAM_S))-1;
        /* change video timing format: 720p@60, 1080i@50, ... */
        if (2 > argc)
        {
            printf("Usage:hdmi_video_timing timeingmode\n");
            for(index = 0; index < u32Len; index ++)
            {
                printf("timemode:%02d   %s\n", index, Hdmi_V_Timing[index].Index_String);
            }

            return RetError;
        }
        timing_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (timing_index > (u32Len - 1))
        {
            printf("input timing mode is larget than Max index:%d\n", (u32Len - 1));
            return HI_FAILURE;
        }

        if(timing_index <= 10)
        {
            timing_index = timing_index;
        }
        else if(timing_index == 11)
        {
            printf("PAL\n");
            timing_index = HI_UNF_ENC_FMT_PAL;
        }
        else if(timing_index == 12)
        {
            printf("NTSC\n");
            timing_index = HI_UNF_ENC_FMT_NTSC;
        }
        else if(timing_index == 13)
        {
            printf("640*480\n");
            timing_index = HI_UNF_ENC_FMT_861D_640X480_60;
        }
        else if(timing_index == 14)
        {
            printf("800X600\n");
            timing_index = HI_UNF_ENC_FMT_VESA_800X600_60;
        }
        else if(timing_index == 15)
        {
            printf("1024X768\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1024X768_60;
        }
        else if(timing_index == 16)
        {
            printf("1280X1024\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1280X1024_60;
        }
        else if(timing_index == 17)
        {
            printf("1366X768\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1366X768_60;
        }
        else if(timing_index == 18)
        {
            printf("1440X900\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1440X900_60;
        }
        else if(timing_index == 19)
        {
            printf("1440X900\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1440X900_60_RB;
        }
        else if(timing_index == 20)
        {
            printf("1600X1200\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1600X1200_60;
        }
        else if(timing_index == 21)
        {
            printf("1920X1200\n");
            timing_index = HI_UNF_ENC_FMT_VESA_1920X1200_60;
        }
        else if(timing_index == 22)
        {
            printf("2048X1152\n");
            timing_index = HI_UNF_ENC_FMT_VESA_2048X1152_60;
        }
        else if(timing_index == 23)
        {
            printf("2560X1440\n");
            timing_index = HI_UNF_ENC_FMT_VESA_2560X1440_60_RB;
        }
        else if(timing_index == 24)
        {
            printf("2560X1600\n");
            timing_index = HI_UNF_ENC_FMT_VESA_2560X1600_60_RB;
        }
        else if(timing_index == 25)
        {
            printf("3840X2160_24\n");
            timing_index = HI_UNF_ENC_FMT_3840X2160_24;
        }
        else if(timing_index == 26)
        {
            printf("3840X2160_25\n");
            timing_index = HI_UNF_ENC_FMT_3840X2160_25;
        }
        else if(timing_index == 27)
        {
            printf("3840X2160_30\n");
            timing_index = HI_UNF_ENC_FMT_3840X2160_30;
        }
        else if(timing_index == 28)
        {
            printf("4096X2160_24\n");
            timing_index = HI_UNF_ENC_FMT_4096X2160_24;
        }
        else if(timing_index == 29)
        {
            printf("3840X2160_23.976\n");
            timing_index = HI_UNF_ENC_FMT_3840X2160_23_976;
        }
        else if(timing_index == 30)
        {
            printf("3840X2160_29.97\n");
            timing_index =HI_UNF_ENC_FMT_3840X2160_29_97;
        }
        else if(timing_index == 31)
        {
            printf("720p_59.94\n");
            timing_index = HI_UNF_ENC_FMT_720P_59_94;
        }
        else if(timing_index == 32)
        {
            printf("1080p_59.94\n");
            timing_index = HI_UNF_ENC_FMT_1080P_59_94;
        }
        else if(timing_index == 33)
        {
            printf("1080p_29.97\n");
            timing_index = HI_UNF_ENC_FMT_1080P_29_97;
        }
        else if(timing_index == 34)
        {
            printf("1080p_23.976\n");
            timing_index = HI_UNF_ENC_FMT_1080P_23_976;
        }
        else if(timing_index == 35)
        {
            printf("1080i_59.94 \n");
            timing_index = HI_UNF_ENC_FMT_1080i_59_94;
        }
        RetError = hdmi_video_timing(timing_index);
    }
    else if (0 == strcmp("hdmi_color_mode", (char *)args[0]))
    {
        HI_U8 color_index;
        /* change video color mode: RGB444, YCbCr422, YCbCr444, ... */
        if (1 >= argc)
        {
            printf("Usage:hdmi_color_mode colormode\n");
            for(index = 0; index < HDMI_MAX_COLOR_MODE; index ++)
            {
                printf("colormode:%02d   %s\n", index, Hdmi_V_ColorMode[index].Index_String);
            }
            return RetError;
        }
        color_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (color_index >= HDMI_MAX_COLOR_MODE)
        {
            printf("input color mode is larget than Max index:%d\n", HDMI_MAX_COLOR_MODE);
            return HI_FAILURE;
        }
        RetError = hdmi_color_mode(color_index);
    }
    else if (0 == strcmp("hdmi_apectrate", (char *)args[0]))
    {
        HI_U8 apectrate_index;
        /* change video aspect rate: 4:3/16:9 */
        if (1 >= argc)
        {
            printf("Usage:hdmi_apectrate apectrate\n");
            for(index = 0; index < HDMI_MAX_ASPECTRATE; index ++)
            {
                printf("apectrate_index:%02d   %s\n", index, Hdmi_V_AspectRate[index].Index_String);
            }
            return RetError;
        }
        apectrate_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (apectrate_index >= HDMI_MAX_ASPECTRATE)
        {
            printf("input apectrate mode is larget than Max index:%d\n", HDMI_MAX_ASPECTRATE);
            return HI_FAILURE;
        }
        RetError = hdmi_apectrate(apectrate_index);
    }
    else if (0 == strcmp("hdmi_reversecolor", (char *)args[0]))
    {
        HI_U8 reversecolor_index;
        /* change video reverse color space: normal/reserve */
        if (1 >= argc)
        {
            printf("Usage:hdmi_reversecolor reversecolor\n");
            printf("reversecolor_index:0   normal range\n");
            printf("reversecolor_index:1   reverse range\n");
            return RetError;
        }
        reversecolor_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (reversecolor_index >= 2)
        {
            printf("input apectrate mode is larget than Max index:%d\n", 2);
            return HI_FAILURE;
        }
        RetError = hdmi_reversecolor(reversecolor_index);
    }
    else if (0 == strcmp("hdmi_rgbfullrange", (char *)args[0]))
    {
        HI_U8 fullrange_index;
        /* change video color space: normal/limit/full */
        if (1 >= argc)
        {
            printf("Usage:hdmi_rgbfullrange fullrange_index\n");
            printf("reversecolor_index:0   normal range\n");
            printf("reversecolor_index:1   limitation range\n");
            printf("reversecolor_index:2   full range\n");
            return RetError;
        }
        fullrange_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (fullrange_index >= 3)
        {
            printf("input apectrate mode is larget than Max index:%d\n", 3);
            return HI_FAILURE;
        }
        RetError = hdmi_rgbfullrange(fullrange_index);
    }
    else if (0 == strcmp("hdmi_ycbcrfullrange", (char *)args[0]))
    {
        HI_U8 fullrange_index;
        /* change video color space: normal/limit/full */
        if (1 >= argc)
        {
            printf("Usage:hdmi_ycbcrfullrange fullrange_index\n");
            printf("reversecolor_index:0   normal range\n");
            printf("reversecolor_index:1   limitation range\n");
            printf("reversecolor_index:2   full range\n");
            return RetError;
        }
        fullrange_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (fullrange_index >= 3)
        {
            printf("input apectrate mode is larget than Max index:%d\n", 3);
            return HI_FAILURE;
        }
        RetError = hdmi_ycbcrfullrange(fullrange_index);
    }
    else if (0 == strcmp("hdmi_attach_intf", (char *)args[0]))
    {
        HI_U8 dispchannel;
        /* change video color space: normal/limit/full */
        if (1 >= argc)
        {
            printf("Usage:hdmi_attach_intf dispchannel\n");
            printf("dispchannel_index:0   disp0 \n");
            printf("dispchannel_index:1   disp1 \n");
            return RetError;
        }

        dispchannel = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (dispchannel >= 2)
        {
            printf("input disp channel index is larget than Max index:%d\n", 2);
            return HI_FAILURE;
        }
        RetError = hdmi_attachIntf(dispchannel);
    }
    else if (0 == strcmp("hdmi_detach_intf", (char *)args[0]))
    {
        HI_U8 dispchannel;
        /* change video color space: normal/limit/full */
        if (1 >= argc)
        {
            printf("Usage:hdmi_detach_intf dispchannel\n");
            printf("dispchannel_index:0   disp0 \n");
            printf("dispchannel_index:1   disp1 \n");
            return RetError;
        }

        dispchannel = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (dispchannel >= 2)
        {
            printf("input disp channel index is larget than Max index:%d\n", 2);
            return HI_FAILURE;
        }
        RetError = hdmi_detachIntf(dispchannel);
    }
    else if (0 == strcmp("hdmi_v_mute", (char *)args[0]))
    {
        /* Mute/Unmute video */
        if (1 >= argc)
        {
            printf("Usage:hdmi_v_mute muteflag\n");
            printf("muteflag: 0:UnMute, >=1:mute\n");
            return RetError;
        }
        RetError = hdmi_v_mute(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_a_freq", (char *)args[0]))
    {
        HI_U8 AFreq_index;
        /* change audio frequency: 32kHz,44.1kHz,48kHz,88.2kHz,96kHz,176.4kHz or 192kHz ... */
        if (1 >= argc)
        {
            printf("Usage:hdmi_a_freq frequncy\n");
            printf("frequncy: 32000,44100,48000,88200,96000,176400,192000\n");
            for(index = 0; index < HDMI_MAX_AUDIO_FREQNCE; index ++)
            {
                printf("Audio Freq:%02d   %s\n", index, Hdmi_A_Frequent[index].Index_String);
            }
            return RetError;
        }
        AFreq_index = (HI_U8)Hdmi_String_to_Integer(args[1]);
        if (AFreq_index >= HDMI_MAX_AUDIO_FREQNCE)
        {
            printf("input Audio freq index is larget than Max index:%d\n", HDMI_MAX_AUDIO_FREQNCE);
            return RetError;
        }
        RetError = hdmi_a_freq(AFreq_index);
    }
    #if 0
    else if (0 == strcmp("hdmi_a_inputmode", (char *)args[0]))
    {
        if (1 >= argc)
        {
            printf("Usage:hdmi_a_inputmode flag\n");
            printf("muteflag: 0:SPDIF, >=1:I2S\n");
            return RetError;
        }
        RetError = hdmi_a_inputmode(Hdmi_String_to_Integer(args[1]));
    }
    #endif
    else if (0 == strcmp("hdmi_a_mute", (char *)args[0]))
    {
        /* Mute/Unmute audio */
        if (1 >= argc)
        {
            printf("Usage:hdmi_a_mute muteflag\n");
            printf("muteflag: 0:UnMute, >=1:mute\n");
            return RetError;
        }
        RetError = hdmi_a_mute(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_a_downsample", (char *)args[0]))
    {
        /* downsample audio */
        if (2 >= argc)
        {
            printf("Usage:hdmi_a_downsample downfactor AOfreq\n");
            printf("downfactor: 0:no downsample, 1:downsample by 2, 2:downsample by 4\n");
            printf("AOfreq: 96000, 192000, default is 192000\n");
            return RetError;
        }
        RetError = hdmi_a_downsample(Hdmi_String_to_Integer(args[1]), Hdmi_String_to_Integer(args[2]));
    }
    else if (0 == strcmp("hdmi_av_mute", (char *)args[0]))
    {
        /* Mute/Unmute audio */
        if (1 >= argc)
        {
            printf("Usage:hdmi_av_mute muteflag\n");
            printf("muteflag: 0:UnMute, >=1:mute\n");
            return RetError;
        }
        RetError = hdmi_av_mute(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_a_channel8", (char *)args[0]))
    {
        /* change hdmi output channel: 0:2 channel, >=1:8chnanel */
        if (1 >= argc)
        {
            printf("Usage:hdmi_a_channel8 channel8flag\n");
            printf("channel8flag: 0:2 channel, >=1:8 channel\n");
            return RetError;
        }
        RetError = hdmi_a_channel8(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_a_passtru", (char *)args[0]))
    {
        /* change hdmi output channel: 0:2 channel, >=1:8chnanel */
        if (1 >= argc)
        {
            printf("Usage:hdmi_a_passtru PassThroughflag \n");
            printf("channel8flag: 0:No passThrough, >=1: passThrough\n");
            return RetError;
        }
        RetError = hdmi_a_passtru(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_hdcp", (char *)args[0]))
    {
        /* hdcp setting, to be define */
        if (1 >= argc)
        {
            printf("Usage:hdmi_hdcp hdcpflag\n");
            printf("hdcpflag: 0:disable, 1:enable\n");
            return RetError;
        }
        RetError = hdmi_hdcp(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_cecautoping", (char *)args[0]))
    {
        /* CEC command, to be define */
        RetError = hdmi_cec_autoping();
    }
    else if (0 == strcmp("cec_enable", (char *)args[0]))
    {
        HI_UNF_HDMI_CEC_Enable(enTest_Hdmi_ID);
    }
    else if (0 == strcmp("cec_disable", (char *)args[0]))
    {
        HI_UNF_HDMI_CEC_Disable(enTest_Hdmi_ID);
    }
    else if (0 == strcmp("cec_setcm", (char *)args[0]))
    {
        HI_U8 destAddr, u8Opcode, index;
        HI_U8 cmd[15], cmdlength;

        if (argc < 4)
        {
            printf("Usage:cec_setcm destAdd Opcode OperandLength Operandx ...\n");
            printf("At present, we support:\n");
            //Standby
            printf("cec_setcm 0  0x36 0          //<Standy> standy :ok\n");
            //One Torch Play
            printf("cec_setcm 0  0X04 0          //<Image View On> invoke TV out of standy :ok\n");
            printf("cec_setcm 0  0X0d 0          //<Text View On> invoke TV out of standy :ok\n");
            printf("cec_setcm 15 0X82 3 1 0      //<Active Source> brocast message with Physical Address :ok\n");
            //System Information
            printf("cec_setcm 0 0x9f 0           //Get CEC Version  :ok");
            printf("cec_setcm 0 0x91 0           //Get Menu Language :ok\n");
            printf("cec_setcm 0 0x83 0           //Give Physical Address :ok\n");
            //printf("cec_setcm 15 0x84 3 1 0 3    //<Report Physical Address> PhyAdd & LogicalAdd brocast message\n");
            //Vendor Specific Command
            printf("cec_setcm 0 0X8C 0           //<Give Device Vendor ID> :ok\n");
            //Device OSD Name Transfer/OSD Display
            printf("cec_setcm 0 0X46 0           //< <Give OSD Name> :ok\n");
            printf("cec_setcm 0 0X64 3 65 66 67  //<Set OSD String>:Maybe no suppor\n");
            //Give Device Power Status
            printf("cec_setcm 0 0X8F 0           //<Give Device Power Status> :ok\n");
            //Set OSD NAME
            return RetError;
        }

        /*
        cec_setcm 0 0X8D 1 0      <Menu Request>
        cec_setcm 0 0X8e 1 0      <Menu Status>
        cec_setcm 0 0X44 1 0x43 <User Control Pressed>
        cec_setcm 0 0X45 1 0x43 <User Control Release>

        cec_setcm 0 0X44 1 0x01 <User Control Pressed>:Up
        cec_setcm 0 0X45 1 0x01 <User Control Release>:Up

        cec_setcm 0 0X44 1 0x02 <User Control Pressed>:Down
        cec_setcm 0 0X45 1 0x02 <User Control Release>:Down
        */

        /* CEC command */
        destAddr = Hdmi_String_to_Hexadecimal(args[1]);

        /* CEC command */
        u8Opcode = Hdmi_String_to_Hexadecimal(args[2]);

        cmdlength = Hdmi_String_to_Hexadecimal(args[3]);

        if(argc < (cmdlength + 4))
        {
            printf("Input argc:%d too little\n", argc);
            return 0;
        }

        /* CEC command */
        for(index = 0; index < cmdlength; index ++)
        {
            cmd[index] = Hdmi_String_to_Hexadecimal(args[4+index]);
        }

        RetError = hdmi_cec_setcmd(destAddr, u8Opcode, cmd, cmdlength);
    }
    else if (0 == strcmp("cec_getcm", (char *)args[0])){
        HI_UNF_HDMI_CEC_CMD_S  pCECCmd;

        if(HI_UNF_HDMI_GetCECCommand(enTest_Hdmi_ID, &pCECCmd, 200) == 0){
            int i = 0;
            printf("get cmd enSrcAdd:0x%02x\n",pCECCmd.enSrcAdd);
            printf("get cmd enDstAdd:0x%02x\n",pCECCmd.enDstAdd);
            printf("get cmd u8Opcode:0x%02x\n",pCECCmd.u8Opcode);
            printf("get cmd Operand Len:0x%02x\n",pCECCmd.unOperand.stRawData.u8Length);
            for(;i<pCECCmd.unOperand.stRawData.u8Length;i++)
            {
                printf("Opcode %d:0x%02x\n",i,pCECCmd.unOperand.stRawData.u8Data[i]);
            }
            printf("\n");
        }
    }
    else if (0 == strcmp("hdmi_reset", (char *)args[0]))
    {
        /* HDMI Reset test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_reset times\n");
            printf("times: >1: reset times\n");
            return RetError;
        }
        RetError = hdmi_ResetTest(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_reopen", (char *)args[0]))
    {
        /* HDMI Reset test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_reopen times\n");
            printf("times: >1: reopen times\n");
            return RetError;
        }
        RetError = hdmi_ReOpenTest(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_restart", (char *)args[0]))
    {
        /* HDMI Reset test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_restart times\n");
            printf("times: >1: restart times\n");
            return RetError;
        }
        RetError = hdmi_ReStartTest(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_edid_test", (char *)args[0]))
    {
        /* HDMI edid test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_edid_test times\n");
            printf("times: >1: test times\n");
            return RetError;
        }
        RetError = hdmi_EDIDTest(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_reg", (char *)args[0]))
    {
        /* HDMI ddc test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_reg option\n");
            printf("option: 0: ddc, 1:Audio, 2:dump all\n");
            return RetError;
        }
        hdmi_RegDebug(Hdmi_String_to_Integer(args[1]));
    }
    else if (0 == strcmp("hdmi_randomswitch", (char *)args[0]))
    {
        /* HDMI Reset test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_RandomSwitch times\n");
            printf("hdcpflag: 0:disable, 1:enable\n");
            return RetError;
        }
        RetError = hdmi_RandomSwitch(Hdmi_String_to_Integer(args[1]));
    }

    else if (0 == strcmp("hdmi_set_disp_3d", (char *)args[0]))
    {
        /* HDMI Reset test */
        if (1 >= argc)
        {
            printf("Usage:hdmi_set_disp_3d format\n");
            printf("0: 3D disable\n");
            printf("1: 3D Frame Packing\n");
            printf("2: Side by side half\n");
            printf("3: Top and Bottom \n");
            return RetError;
        }
        RetError = hdmi_set_disp_3d(Hdmi_String_to_Integer(args[1]));
    }
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
    else if (0 == strcmp("hdmi_picture_display", (char *)args[0]))
    {
        RetError = hdmi_picture_display();
    }
    else if (0 == strcmp("hdmi_picture_clear", (char *)args[0]))
    {
        RetError = hdmi_picture_clear();
    }
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

    return RetError;
}


static HI_U32 hdmi_hdmi_force(void)
{
    HI_U32              RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S  attr;
//  HI_UNF_HDMI_INFOFRAME_S           stInfoFrame;
//  HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;

    printf("hdmi_hdmi_force  with HI_UNF_HDMI_SetAttr\n");
    HI_UNF_HDMI_Stop(enTest_Hdmi_ID);


    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    attr.bEnableHdmi = HI_TRUE;
    attr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
    attr.bEnableAudio = HI_TRUE;
    attr.bEnableAviInfoFrame = HI_TRUE;
    attr.bEnableAudInfoFrame = HI_TRUE;
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);

    HI_UNF_HDMI_Start(enTest_Hdmi_ID);




    return RetError;
}

static HI_U32 hdmi_dvi_force(void)
{
    HI_U32              RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S  attr;

    printf("hdmi_dvi_force with HI_UNF_HDMI_SetAttr\n");
    HI_UNF_HDMI_Stop(enTest_Hdmi_ID);
    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    attr.bEnableHdmi = HI_FALSE;
    attr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
    attr.bEnableAudio = HI_FALSE;
    attr.bEnableAviInfoFrame = HI_FALSE;
    attr.bEnableAudInfoFrame = HI_FALSE;
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_Start(enTest_Hdmi_ID);

    return RetError;
}

static HI_U32 hdmi_display_edid(void)
{
    HI_U32     u32Len = 0;
    HI_U32     RetError = HI_SUCCESS;
    HI_U32     index;
    HI_U8      u8Edid[512] = {0};

    printf("hdmi_display_edid enter with HI_UNF_HDMI_Force_GetEDID \n");
    RetError = HI_UNF_HDMI_Force_GetEDID(enTest_Hdmi_ID,u8Edid,&u32Len);

    if (RetError != HI_SUCCESS)
    {
        printf("can not get sink Attribute\n");
    }

    if(u32Len > 512)
    {
        printf("Edid Len %d is biger than 512! \n",u32Len);
        u32Len = 512;
    }

    for (index = 0; index < u32Len; index ++)
    {
        printf("%02x ", u8Edid[index]);
        if (0 == ((index + 1) % 16))
        {
            printf("\n");
        }
    }
    printf("hdmi_display_edid end\n");

    return RetError;
}

static HI_U32 hdmi_out_enable(void)
{
    HI_U32 Ret;
    HI_U32 RetError = HI_SUCCESS;

    printf("hdmi_out_enable with HI_UNF_HDMI_Start\n");
    Ret = HI_UNF_HDMI_Start(enTest_Hdmi_ID);
    return RetError;
}

static HI_U32 hdmi_out_disable(void)
{
    HI_U32 Ret;
    HI_U32 RetError = HI_SUCCESS;

    printf("hdmi_out_disable with HI_UNF_HDMI_Stop\n");
    Ret = HI_UNF_HDMI_Stop(enTest_Hdmi_ID);

    return RetError;
}

HI_UNF_ENC_FMT_E Last2DFmt = HI_UNF_ENC_FMT_BUTT;

HI_U32 hdmi_video_timing(HI_U32 u32TimingIndex)
{
    HI_U32                            RetError = HI_SUCCESS;
    //HI_UNF_HDMI_COLORSPACE_E          enColorimetry;
    //HI_UNF_HDMI_ASPECT_RATIO_E             enAspectRate;
    //HI_U32                            u32PixelRepetition;
    //HI_U32                            enRGBQuantization;
    HI_UNF_HDMI_ATTR_S                attr;
    //HI_UNF_HDMI_INFOFRAME_S           stInfoFrame;
    //HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;
    //HI_UNF_HDMI_SINK_CAPABILITY_S     sinkCap;
    //HI_UNF_HDMI_VIDEO_MODE_E          enVidOutMode;

    printf("hdmi_video_timing u32TimingIndex:%d\n", u32TimingIndex);

    /* Output all debug message */
    //HI_UNF_HDMI_GetSinkCapability(enTest_Hdmi_ID, &sinkCap);
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
    if (HI_TRUE == sinkCap.bVideoFmtSupported[u32TimingIndex])
    {
        printf("From EDID, sink can receive this format!!!\n");
    }
    else
    {
        printf("From EDID, Sink CAN NOT receive this format*******\n");
        //return HI_FAILURE;
    }
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

    printf("change DISP Timing to u32TimingIndex:%d\n", u32TimingIndex);
    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
    RetError = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);

    //HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);

    enColorimetry      = HDMI_COLORIMETRY_ITU709;
    enAspectRate       = HI_UNF_HDMI_ASPECT_RATIO_16TO9;
    u32PixelRepetition = HI_FALSE;
    enRGBQuantization  = HDMI_RGB_QUANTIZATION_DEFAULT_RANGE;

    //enVidOutMode = attr.enVidOutMode;
    if (HI_TRUE == sinkCap.bSupportYCbCr)
    {
        enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;
    }
    else
    {
        enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
    }

    /* New function to set AVI Infoframe */
    memset(&stInfoFrame, 0, sizeof(HI_UNF_HDMI_INFOFRAME_S));
    HI_UNF_HDMI_GetInfoFrame(enTest_Hdmi_ID, HI_INFOFRAME_TYPE_AVI, &stInfoFrame);

    pstVIDInfoframe = (HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *)&(stInfoFrame.unInforUnit.stAVIInfoFrame);
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

    if(HI_UNF_ENC_FMT_1080P_60 == u32TimingIndex)
    {
        printf("Set 1920X1080P_60000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_1080P_50 == u32TimingIndex)
    {
        printf("Set 1920X1080P_50000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_1080P_30 == u32TimingIndex)
    {
        printf("Set 1920X1080P_30000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_1080P_25 == u32TimingIndex)
    {
        printf("Set 1920X1080P_25000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_1080P_24 == u32TimingIndex)
    {
        printf("Set 1920X1080P_24000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_1080i_60 == u32TimingIndex)
    {
        printf("Set 1920X1080i_60000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_1080i_50 == u32TimingIndex)
    {
        printf("Set 1920X1080i_50000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_720P_60 == u32TimingIndex)
    {
        printf("Set 1280X720P_60000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_720P_50 == u32TimingIndex)
    {
        printf("Set 1280X720P_50000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_576P_50 == u32TimingIndex)
    {
        printf("Set 720X576P_50000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
        //enColorimetry = HDMI_COLORIMETRY_ITU601;
        //enAspectRate  = HI_UNF_HDMI_ASPECT_RATIO_4TO3;
    }
    else if(HI_UNF_ENC_FMT_480P_60 == u32TimingIndex)
    {
        printf("Set 720X480P_60000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
        //enColorimetry = HDMI_COLORIMETRY_ITU601;
        //enAspectRate  = HI_UNF_HDMI_ASPECT_RATIO_4TO3;
    }
    else if(HI_UNF_ENC_FMT_PAL == u32TimingIndex)
    {
        printf("Set PAL 576I_50000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
        //enColorimetry = HDMI_COLORIMETRY_ITU601;
        //enAspectRate  = HI_UNF_HDMI_ASPECT_RATIO_4TO3;
        //u32PixelRepetition = HI_TRUE;
    }
    else if(HI_UNF_ENC_FMT_NTSC == u32TimingIndex)
    {
        printf("Set NTS 480I_60000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
    }
    else if(HI_UNF_ENC_FMT_861D_640X480_60 == u32TimingIndex)
    {
        printf("Set 640X480P_60000 u32TimingIndex:0x%x\n", u32TimingIndex);
        //for VGA output!!!
        printf("change to LCD\n");
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_LCD);
        printf("change to fomat\n");
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, HI_UNF_ENC_FMT_861D_640X480_60);//driver change to HI_UNF_DISP_SetIntfType() DISP_SetLcdDefaultPara().
        printf("change to fomat\n");
        //HI_UNF_DISP_SetDacMode();
    }
    else if ((HI_UNF_ENC_FMT_VESA_800X600_60 <= u32TimingIndex) && (HI_UNF_ENC_FMT_VESA_2560X1600_60_RB >= u32TimingIndex))
    {
        printf("DVI timing mode u32TimingIndex:0x%x\n", u32TimingIndex);
        if (attr.bEnableHdmi != HI_FALSE)
        {
            printf("HDMI Ouptut, need DVI output, we do not support this format in HDMI Mode\n");
            //return HI_FAILURE;
        }
        //for VGA output!!!
        printf("change to LCD\n");
        //HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_LCD);
        //HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);//driver change to HI_UNF_DISP_SetIntfType() DISP_SetLcdDefaultPara().
        //HI_UNF_DISP_SetDacMode();
    }
    else if (HI_UNF_ENC_FMT_3840X2160_24 == u32TimingIndex)
    {
        printf("Set 3840X2160_24 u32TimingIndex:0x%x\n", u32TimingIndex);
    }
    else if (HI_UNF_ENC_FMT_3840X2160_25 == u32TimingIndex)
    {
        printf("Set 3840X2160_25 u32TimingIndex:0x%x\n", u32TimingIndex);
    }
    else if (HI_UNF_ENC_FMT_3840X2160_30 == u32TimingIndex)
    {
        printf("Set 3840X2160_30 u32TimingIndex:0x%x\n", u32TimingIndex);
    }
    else if (HI_UNF_ENC_FMT_4096X2160_24 == u32TimingIndex)
    {
        printf("Set 4096X2160_24 u32TimingIndex:0x%x\n", u32TimingIndex);
    }
    //attr.enVideoFmt = u32TimingIndex;
    //if(u32TimingIndex == 99)
    //{
        //RetError = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING);
    //}
    //else
        //{

    Last2DFmt = u32TimingIndex;
    RetError = HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, u32TimingIndex);
        //}
    //HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    return RetError;
}

static HI_U32 hdmi_color_mode(HI_U32 u32ColorIndex)
{
    HI_U32                            RetError = HI_SUCCESS;
    HI_UNF_HDMI_VIDEO_MODE_E          enVidOutMode;
    HI_UNF_HDMI_ATTR_S                attr;
    HI_UNF_EDID_BASE_INFO_S           sinkCap;
    HI_UNF_HDMI_VIDEO_MODE_E          enOldVidOutMode;

    printf("hdmi_color_mode u32ColorIndex:%d\n", u32ColorIndex);

    switch(u32ColorIndex)
    {
    case 1:
        enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR422;
        break;
    case 2:
        enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;
        break;
    case 0:
    default:
        enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
        break;
    }

    RetError = HI_UNF_HDMI_GetSinkCapability(enTest_Hdmi_ID, &sinkCap);

    if(RetError == HI_SUCCESS)
    {
        if( (enVidOutMode == HI_UNF_HDMI_VIDEO_MODE_YCBCR444)
            && (HI_TRUE != sinkCap.stColorSpace.bYCbCr444)  )
        {
            printf("sink device do not support YCbCr444 \n");
            return HI_FAILURE;
        }

        if( (enVidOutMode == HI_UNF_HDMI_VIDEO_MODE_YCBCR422)
            && (HI_TRUE != sinkCap.stColorSpace.bYCbCr422)  )
        {
            printf("sink device do not support YCbCr422 \n");
            return HI_FAILURE;
        }
    }
    else
    {
        printf("can't get capability, force set Attr \n");
    }

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);

    printf("hdmi_color_mode enVidOutMode:%d with HI_UNF_HDMI_SetAttr\n", enVidOutMode);
    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);

    enOldVidOutMode = attr.enVidOutMode;
    attr.enVidOutMode = enVidOutMode;
    RetError = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    if(RetError != HI_SUCCESS)
    {
        printf("HI_UNF_HDMI_SetAttr Err! \n");
    }

    sleep(1);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);

    return RetError;
}
static HI_U32 hdmi_apectrate(HI_U32 u32apectrateIndex)
{
    HI_U32                            RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S                attr;
    HI_UNF_HDMI_INFOFRAME_S           stInfoFrame;
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;
    HI_UNF_WINDOW_ATTR_S              winattr;

    printf("hdmi_apectrate u32apectrateIndex:%d\n", u32apectrateIndex);

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);

    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    /* We now need to remake AVI Inforframe to indicate colorimetry mode */
    HI_UNF_HDMI_GetInfoFrame(enTest_Hdmi_ID, HI_INFOFRAME_TYPE_AVI, &stInfoFrame);
    pstVIDInfoframe = &(stInfoFrame.unInforUnit.stAVIInfoFrame);

    switch(u32apectrateIndex)
    {
    case 0:
        printf("4:3\n");
        HI_UNF_VO_GetWindowAttr(g_hWin, &winattr);
        //winattr.enAspectRatio = HI_UNF_HDMI_ASPECT_RATIO_4TO3;
        winattr.stWinAspectAttr.enAspectCvrs  = HI_UNF_VO_ASPECT_CVRS_IGNORE;
        HI_UNF_VO_SetWindowAttr(g_hWin, &winattr);
        pstVIDInfoframe->enAspectRatio       = HI_UNF_HDMI_ASPECT_RATIO_4TO3;
        pstVIDInfoframe->enActiveAspectRatio = HI_UNF_HDMI_ASPECT_RATIO_4TO3;
        break;
    default:
        printf("16:9\n");
        HI_UNF_VO_GetWindowAttr(g_hWin, &winattr);
     //   winattr.enAspectRatio = HI_UNF_HDMI_ASPECT_RATIO_16TO9;
        winattr.stWinAspectAttr.enAspectCvrs  = HI_UNF_VO_ASPECT_CVRS_IGNORE;
        HI_UNF_VO_SetWindowAttr(g_hWin, &winattr);
        pstVIDInfoframe->enAspectRatio       = HI_UNF_HDMI_ASPECT_RATIO_16TO9;
        pstVIDInfoframe->enActiveAspectRatio = HI_UNF_HDMI_ASPECT_RATIO_16TO9;
        break;
    }

    printf("remake AVI inforframe\n");
    HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &stInfoFrame);
    //HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);

    return RetError;
}
static HI_U32 hdmi_rgbfullrange(HI_U32 u32fullrangeIndex)
{
    HI_U32                            RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S                attr;
    HI_UNF_HDMI_INFOFRAME_S           stInfoFrame;
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;
    HI_UNF_ENC_FMT_E                  curDispFormat;

    printf("hdmi_rgbfullrange u32fullrangeIndex:%d\n", u32fullrangeIndex);

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);

    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    /* We now need to remake AVI Inforframe to indicate colorimetry mode */
    HI_UNF_HDMI_GetInfoFrame(enTest_Hdmi_ID, HI_INFOFRAME_TYPE_AVI, &stInfoFrame);
    pstVIDInfoframe = &(stInfoFrame.unInforUnit.stAVIInfoFrame);

    HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1,&curDispFormat);


        switch(u32fullrangeIndex)
        {
        case 0:
            printf("RGB default color range\n");
            pstVIDInfoframe->enRGBQuantization  = HDMI_RGB_QUANTIZATION_FULL_RANGE;
            pstVIDInfoframe->enYCCQuantization = HDMI_YCC_QUANTIZATION_LIMITED_RANGE;
            break;
        case 1:
            printf("RGB Limitation color range\n");
            pstVIDInfoframe->enRGBQuantization  = HDMI_RGB_QUANTIZATION_LIMITED_RANGE;
            pstVIDInfoframe->enYCCQuantization = HDMI_YCC_QUANTIZATION_LIMITED_RANGE;
            break;
        default:
            printf("RGB Full color range\n");
            pstVIDInfoframe->enRGBQuantization  = HDMI_RGB_QUANTIZATION_FULL_RANGE;
            pstVIDInfoframe->enYCCQuantization = HDMI_YCC_QUANTIZATION_LIMITED_RANGE;
            break;
        }


    printf("remake AVI inforframe\n");
    HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &stInfoFrame);
    //HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);

    return RetError;
}

static HI_U32 hdmi_ycbcrfullrange(HI_U32 u32fullrangeIndex)
{
    HI_U32                            RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S                attr;
    HI_UNF_HDMI_INFOFRAME_S           stInfoFrame;
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;
    HI_UNF_ENC_FMT_E                  curDispFormat;

    printf("hdmi_rgbfullrange u32fullrangeIndex:%d\n", u32fullrangeIndex);

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);

    //HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    /* We now need to remake AVI Inforframe to indicate colorimetry mode */
    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);

    HI_UNF_HDMI_GetInfoFrame(enTest_Hdmi_ID, HI_INFOFRAME_TYPE_AVI, &stInfoFrame);
    pstVIDInfoframe = &(stInfoFrame.unInforUnit.stAVIInfoFrame);

    HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1,&curDispFormat);


        switch(u32fullrangeIndex)
        {
        case 0:
            printf("YCC default color range\n");
            pstVIDInfoframe->enRGBQuantization  = HDMI_RGB_QUANTIZATION_DEFAULT_RANGE;
            pstVIDInfoframe->enYCCQuantization = HDMI_YCC_QUANTIZATION_LIMITED_RANGE;
            break;
        case 1:
            printf("YCC Limitation color range\n");
            pstVIDInfoframe->enRGBQuantization  = HDMI_RGB_QUANTIZATION_DEFAULT_RANGE;
            pstVIDInfoframe->enYCCQuantization = HDMI_YCC_QUANTIZATION_LIMITED_RANGE;
            break;
        default:
            printf("YCC Full color range\n");
            pstVIDInfoframe->enRGBQuantization  = HDMI_RGB_QUANTIZATION_DEFAULT_RANGE;
            pstVIDInfoframe->enYCCQuantization = HDMI_YCC_QUANTIZATION_FULL_RANGE;
            break;
    }

    printf("remake AVI inforframe\n");
    HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &stInfoFrame);
    //HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);

    return RetError;
}

static HI_U32 hdmi_attachIntf(HI_U32 u32dispChnIndex)
{
    HI_UNF_DISP_INTF_S stHdmiIntf;
    HI_UNF_DISP_E enDisp;
    HI_U32  RetError;
    printf("attach hdmi to disp%d!\n",u32dispChnIndex);

    switch(u32dispChnIndex)
    {
        case 0:
            enDisp = HI_UNF_DISPLAY0;
            break;
        case 1:
            enDisp = HI_UNF_DISPLAY1;
            break;
        default:
            enDisp = HI_UNF_DISPLAY_BUTT;
            break;
    }

    stHdmiIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
    stHdmiIntf.unIntf.enHdmi = HI_UNF_HDMI_ID_0;
    RetError = HI_UNF_DISP_AttachIntf(enDisp,&stHdmiIntf,1);

    return RetError;
}

static HI_U32 hdmi_detachIntf(HI_U32 u32dispChnIndex)
{
    HI_UNF_DISP_INTF_S stHdmiIntf;
    HI_UNF_DISP_E enDisp;
    HI_U32  RetError;
    printf("Detach hdmi from disp%d!\n",u32dispChnIndex);

    switch(u32dispChnIndex)
    {
        case 0:
            enDisp = HI_UNF_DISPLAY0;
            break;
        case 1:
            enDisp = HI_UNF_DISPLAY1;
            break;
        default:
            enDisp = HI_UNF_DISPLAY_BUTT;
            break;
    }

    printf("Detach enDisp %d \n",enDisp);

    stHdmiIntf.enIntfType = HI_UNF_DISP_INTF_TYPE_HDMI;
    stHdmiIntf.unIntf.enHdmi = HI_UNF_HDMI_ID_0;
    RetError = HI_UNF_DISP_DetachIntf(enDisp,&stHdmiIntf,1);

    return RetError;
}

static HI_U32 hdmi_reversecolor(HI_U32 u32reversecolorIndex)
{
    HI_U32                            RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S                attr;
    HI_UNF_HDMI_INFOFRAME_S           stInfoFrame;
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;
    HI_UNF_ENC_FMT_E                  curDispFormat;

    printf("hdmi_reversecolor u32reversecolorIndex:%d\n", u32reversecolorIndex);

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);

    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    /* We now need to remake AVI Inforframe to indicate colorimetry mode */
    HI_UNF_HDMI_GetInfoFrame(enTest_Hdmi_ID, HI_INFOFRAME_TYPE_AVI, &stInfoFrame);
    pstVIDInfoframe = &(stInfoFrame.unInforUnit.stAVIInfoFrame);

    HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1,&curDispFormat);
    if (curDispFormat <= HI_UNF_ENC_FMT_720P_50)
    {
        //HD
        switch(u32reversecolorIndex)
        {
        case 1:
            printf("HD reverse color space 601\n");
            pstVIDInfoframe->enColorimetry = HDMI_COLORIMETRY_ITU601;
            break;
        default:
            printf("HD normal color space 709\n");
            pstVIDInfoframe->enColorimetry = HDMI_COLORIMETRY_ITU709;
            break;
        }
    }
    else
    {
        //SD
        switch(u32reversecolorIndex)
        {
        case 1:
            printf("SD reverse color space 709\n");
            pstVIDInfoframe->enColorimetry = HDMI_COLORIMETRY_ITU709;
            break;
        default:
            printf("SD normal color space 601\n");
            pstVIDInfoframe->enColorimetry = HDMI_COLORIMETRY_ITU601;
            break;
        }
    }

    printf("remake AVI inforframe\n");
    HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &stInfoFrame);
    //HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);

    return RetError;
}

HI_U32 hdmi_deepcolor(HI_U32 u32DeepColorFlag)
{
    HI_U32 RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S            attr;
    HI_UNF_EDID_BASE_INFO_S       sinkCap;

    RetError = HI_UNF_HDMI_GetSinkCapability(enTest_Hdmi_ID, &sinkCap);

    if(RetError == HI_SUCCESS)
    {
        if (u32DeepColorFlag == HI_UNF_HDMI_DEEP_COLOR_24BIT)
        {
            //OK
        }
        else if (u32DeepColorFlag == HI_UNF_HDMI_DEEP_COLOR_30BIT)
        {
            if (HI_TRUE != sinkCap.stDeepColor.bDeepColor30Bit)
            {
                printf("HI_UNF_HDMI_DEEP_COLOR_30BIT do not support in Sink Device\n");
            }
        }
        else if (u32DeepColorFlag == HI_UNF_HDMI_DEEP_COLOR_36BIT)
        {
            if (HI_TRUE != sinkCap.stDeepColor.bDeepColor36Bit)
            {
                printf("HI_UNF_HDMI_DEEP_COLOR_36BIT do not support in Sink Device\n");
            }
        }
        else
        {
            printf("DeepColor:0x%x do not support in current environment\n", u32DeepColorFlag);
        }
    }
    else
    {
        printf("can't get capability, force set Attr \n");
    }

    printf("hdmi_deepcolor u32DeepColorFlag:%d\n", u32DeepColorFlag);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);
    HI_UNF_HDMI_SetDeepColor(enTest_Hdmi_ID, u32DeepColorFlag);

    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    attr.enDeepColorMode = u32DeepColorFlag;
    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);

    /* We should fill General Control packet, hdmi chip do it in driver level */
    return RetError;
}
static HI_U32 hdmi_xvycc(HI_U32 xvYCCFlag)
{
    HI_U32 RetError = HI_SUCCESS;
//    HI_UNF_DISP_HDMI_SETTING_S  stHdmiIntf;
    HI_UNF_HDMI_ATTR_S            attr;
    HI_UNF_EDID_BASE_INFO_S       sinkCap;
    HI_UNF_HDMI_INFOFRAME_S       stInfoFrame;
    HI_UNF_HDMI_AVI_INFOFRAME_VER2_S *pstVIDInfoframe;

    /*
    The Sink indicates support for specific transmission profiles by setting one
    or more of the MD0, MD1, etc. bits in the Colorimetry Data Block.
    (Externd Tag Code in EDID Block 1)
    If the attached Sink's EDID does not include a Colorimetry Data Block
    then the Source shall not transmit Gamut Metadata Packets.
    Note that xvYCC colorimetry requires transmission of the gamut metadata.

    Gamut Boundary Description (GBD)
    The lowest speed transmission profile is P0,
    transmitting at a rate of one Gamut Metadata Packet per video field.
    P0 metadata fits completely within that one packet.

    requirement:
    1). flag in EDID Colormimetry Data Block
    2). input HDMI is YCbCr444
    3). enable XVYCC (0x72    0x50, 0x72    0x68)
    4). Output mode set to YCbCr444
    5). set AVI inforfraem to xvYCC.
    6). send out Gamut Metadata packets.
    */
    printf("hdmi_xvycc xvYCCFlag:%d\n", xvYCCFlag);

     RetError = HI_UNF_HDMI_GetSinkCapability(enTest_Hdmi_ID, &sinkCap);

    if(RetError == HI_SUCCESS)
    {
        if (HI_TRUE == xvYCCFlag)
        {
            if ((HI_TRUE != sinkCap.stColorMetry.bxvYCC601) && (HI_TRUE != sinkCap.stColorMetry.bxvYCC709) )
            {
                printf("$$$sink device do not support xvYCC Colorimetry$$$$$$$\n");
                //return HI_FAILURE;
            }
        }
    }
    else
    {
        printf("can't get capability, force set Attr \n");
    }

    HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);

    if (attr.enDeepColorMode != HI_UNF_HDMI_DEEP_COLOR_36BIT)
    {
        printf("please first set Deepcolor 36bit. Return!!!\n");
        return HI_FAILURE;
    }

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);
    HI_UNF_HDMI_SetDeepColor(enTest_Hdmi_ID, attr.enDeepColorMode);
    /* Set HDMI xvYCC Mode register */
    HI_UNF_HDMI_SetxvYCCMode(enTest_Hdmi_ID, xvYCCFlag);

    attr.bxvYCCMode   = xvYCCFlag;
    attr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;

    HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);


    /* refill AVI Inforframe */
    HI_UNF_HDMI_GetInfoFrame(enTest_Hdmi_ID, HI_INFOFRAME_TYPE_AVI, &stInfoFrame);
    pstVIDInfoframe = &(stInfoFrame.unInforUnit.stAVIInfoFrame);
    switch (pstVIDInfoframe->enTimingMode)
    {
    case HI_UNF_ENC_FMT_1080P_60:
    case HI_UNF_ENC_FMT_1080P_50:
    case HI_UNF_ENC_FMT_1080P_30:
    case HI_UNF_ENC_FMT_1080P_25:
    case HI_UNF_ENC_FMT_1080P_24:
    case HI_UNF_ENC_FMT_1080i_60:
    case HI_UNF_ENC_FMT_1080i_50:
    case HI_UNF_ENC_FMT_720P_60:
    case HI_UNF_ENC_FMT_720P_50:
        pstVIDInfoframe->enColorimetry = HDMI_COLORIMETRY_XVYCC_709;
        break;
    default:
        pstVIDInfoframe->enColorimetry = HDMI_COLORIMETRY_XVYCC_601;
    }
    pstVIDInfoframe->enOutputType = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;
    printf("remake AVI inforframe with xvYCC color mode\n");
    HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &stInfoFrame);
    return RetError;
}
static HI_U32 hdmi_a_freq(HI_U32 u32AFreq)
{
#ifndef ATC_AUDIO
    HI_U32 Ret = HI_SUCCESS;
    printf("HDMI audio sample rate is setting by aiao now\n");
    Ret = HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, u32AFreq);
    printf("set Sound samplerate Audio_Freq:%d, Ret:0x%x\n", u32AFreq, Ret);
#else
    HI_U32 Ret = HI_SUCCESS;
    HI_U32 Audio_Freq;
    HI_UNF_HDMI_AUDIO_ATTR_S          attr;

    printf("hdmi_a_freq u32AFreqIndex:%d with HI_UNF_SND_SetSampleRate\n", u32AFreq);
    switch (u32AFreq)
    {
    case 0:
        Audio_Freq = HI_UNF_SAMPLE_RATE_32K;
        break;
    case 1:
        Audio_Freq = HI_UNF_SAMPLE_RATE_44K;
        break;
    case 2:
        Audio_Freq = HI_UNF_SAMPLE_RATE_48K;
        break;
    case 3:
        Audio_Freq = HI_UNF_SAMPLE_RATE_88K;//Audio driver do not support
        break;
    case 4:
        Audio_Freq = HI_UNF_SAMPLE_RATE_96K;
        break;
    case 5:
        Audio_Freq = 176400;//Audio driver do not support
        break;
    case 6:
        Audio_Freq = HI_UNF_SAMPLE_RATE_192K;
        break;
    case 7:
    default:
        printf("Error input Audio Frequency\n");
        return HI_FAILURE;
    }

    if  (! ((HI_UNF_SAMPLE_RATE_32K == Audio_Freq)
         || (HI_UNF_SAMPLE_RATE_44K == Audio_Freq)
         || (HI_UNF_SAMPLE_RATE_48K == Audio_Freq)
         || (HI_UNF_SAMPLE_RATE_96K == Audio_Freq)
         || (HI_UNF_SAMPLE_RATE_192K == Audio_Freq)
        ))
    {
        printf("Error:Hisi Chip do not support this freq:%d now!!\n", Audio_Freq);
        return 0;
    }
    Ret |= HI_UNF_HDMI_GetAudioAttr(enTest_Hdmi_ID, &attr);
    printf("set Sound samplerate Audio_Freq:%d, Ret:0x%x\n", Audio_Freq, Ret);

    attr.enSampleRate       = Audio_Freq;
    printf("set HDMI Attribute\n");
    Ret = HI_UNF_HDMI_SetAudioAttr(enTest_Hdmi_ID, &attr);
#endif

    return Ret;
}

#if 0
static HI_U32 hdmi_a_inputmode(HI_U32 inputmode)
{
    HI_U32                 Ret = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S     attr;

    Ret = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    if (0 == inputmode)
    {
        attr.enSoundIntf = HI_UNF_SND_INTERFACE_SPDIF;
    }
    else
    {
        attr.enSoundIntf = HI_UNF_SND_INTERFACE_I2S;
    }

#if 0
    Ret = hdmi_a_mute(HI_TRUE);
    printf("set HDMI Audio input mode:%d\n", attr.enSoundIntf);
    Ret = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    Ret = hdmi_a_mute(HI_FALSE);
#else
    printf("set HDMI Audio input mode:%d\n", attr.enSoundIntf);
    Ret = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
#endif
    return Ret;
}
#endif

static HI_U32 hdmi_v_mute(HI_BOOL bMuteAudio)
{
    HI_U32 Ret = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S          attr;

    Ret = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    if (HI_FALSE == bMuteAudio)
    {
        attr.bEnableVideo     = HI_TRUE;
    }
    else
    {
        attr.bEnableVideo     = HI_FALSE;
    }
    Ret = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);

    return Ret;
}
static HI_U32 hdmi_a_mute(HI_BOOL bMuteAudio)
{
    HI_U32 Ret = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S          attr;

    Ret = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    if (HI_FALSE == bMuteAudio)
    {
        attr.bEnableAudio     = HI_TRUE;
    }
    else
    {
        attr.bEnableAudio     = HI_FALSE;
    }
    Ret = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);

    return Ret;
}
static HI_U32 hdmi_a_downsample(HI_U32 factor, HI_U32 AOfreq)
{
    printf("HDMI audio downsample is setting by aiao now! return  /n");
#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
    HI_U32 Ret = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S          attr;
    HI_UNF_HDMI_INFOFRAME_S     InfoFrame;
    HI_UNF_HDMI_AUD_INFOFRAME_VER1_S *pstAUDInfoframe;

    if (1 == factor)
    {
        /* downsample by 2 */
    }
    else if (2 == factor)
    {
        /* downsample by 4 */
    }
    else
    {
        printf("no downsample\n");
        return HI_SUCCESS;
    }

    if ((96000 != AOfreq) && (192000 != AOfreq))
    {
        AOfreq = 192000;
    }

    if ((96000 == AOfreq) && (1 != factor) )
    {
        printf("AOFreq:%d can not downsample facotr:%d\n", AOfreq, factor);
    }
    Ret = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    //attr.enSampleRate = AOfreq;

    Ret |= HI_UNF_SND_SetSampleRate(HI_UNF_SND_0, AOfreq);
    printf("set Sound samplerate Audio_Freq:%d, Ret:0x%x\n", AOfreq, Ret);

    attr.u8DownSampleParm = factor;

    /* Set Audio infoframe */
    /* New function to set Audio Infoframe */
    /* HDMI requires the CT, SS and SF fields to be set to 0 ("Refer to Stream Header")
       as these items are carried in the audio stream.*/
    memset(&InfoFrame, 0, sizeof(InfoFrame));
    InfoFrame.enInfoFrameType = HI_INFOFRAME_TYPE_AUDIO;
    pstAUDInfoframe = (HI_UNF_HDMI_AUD_INFOFRAME_VER1_S *)&(InfoFrame.unInforUnit.stAUDInfoFrame);
    pstAUDInfoframe->u32ChannelCount      = 2; //maybe 2 or 8;
    pstAUDInfoframe->enCodingType         = HDMI_AUDIO_CODING_REFER_STREAM_HEAD;
    pstAUDInfoframe->u32SampleSize        = HI_UNF_HDMI_DEFAULT_SETTING;
    pstAUDInfoframe->u32SamplingFrequency = HI_UNF_HDMI_DEFAULT_SETTING;
    pstAUDInfoframe->u32ChannelAlloc      = 0;
    pstAUDInfoframe->u32LevelShift        = 0;
    pstAUDInfoframe->u32DownmixInhibit    = HI_FALSE;
    printf("***HI_UNF_HDMI_SetInfoFrame for AUDIO Infoframe\n");
    Ret = HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &InfoFrame);
    Ret = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

    return HI_SUCCESS;
}
static HI_U32 hdmi_av_mute(HI_U32 u32MuteFlag)
{
    HI_U32 RetError = HI_SUCCESS;

    HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, u32MuteFlag );

    return RetError;
}

static HI_U32 hdmi_a_channel8(HI_U32 channel8flag)
{
#ifndef ATC_AUDIO
    printf("HDMI multy channel is setting by aiao now! return /n");
    return HI_SUCCESS;
#else
    HI_U32 RetError = HI_SUCCESS;
    HI_U32 u32ChannelCount = 2;
    HI_UNF_HDMI_AUDIO_ATTR_S attr;
    //must be PCM Audio output!!!
    printf("hdmi_a_channel8 channel8flag:%d\n", channel8flag);

    if(channel8flag >= 1)
        u32ChannelCount = 8;

    RetError |= HI_UNF_HDMI_GetAudioAttr(enTest_Hdmi_ID, &attr);
    attr.u32Channels = u32ChannelCount;

    RetError |= HI_UNF_HDMI_SetAudioAttr(enTest_Hdmi_ID, &attr);

    return RetError;
#endif
}
//extern HI_VOID HDMI_SetAudioCompress(HI_U32 CompressFlag);

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
HI_U32 hdmi_a_compress(HI_U32 compressFlag)
{
    HI_U32 RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S          attr;
    HI_UNF_HDMI_INFOFRAME_S     InfoFrame;
    HI_UNF_HDMI_AUD_INFOFRAME_VER1_S *pstAUDInfoframe;

    printf("hdmi_a_compress compressFlag:%d\n", compressFlag);

    if(g_Audiotype != HA_AUDIO_ID_DOLBY_PLUS)
    {
        printf("Audio type is not AC3, can not open Compress mode\n");
        return 0;
    }

    RetError = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
#if 0
    if (compressFlag >= 1)
    {
        HDMI_SetAudioCompress(HI_TRUE);
    }
    else
    {
        HDMI_SetAudioCompress(HI_FALSE);
    }
 #endif
    /* Set Audio infoframe */
    /* New function to set Audio Infoframe */
    /* HDMI requires the CT, SS and SF fields to be set to 0 ("Refer to Stream Header")
       as these items are carried in the audio stream.*/
    memset(&InfoFrame, 0, sizeof(InfoFrame));
    InfoFrame.enInfoFrameType = HI_INFOFRAME_TYPE_AUDIO;
    pstAUDInfoframe = (HI_UNF_HDMI_AUD_INFOFRAME_VER1_S *)&(InfoFrame.unInforUnit.stAUDInfoFrame);
    pstAUDInfoframe->u32ChannelCount      = 2; //maybe 2 or 8;
    pstAUDInfoframe->enCodingType         = HDMI_AUDIO_CODING_REFER_STREAM_HEAD;
    pstAUDInfoframe->u32SampleSize        = HI_UNF_HDMI_DEFAULT_SETTING;
    pstAUDInfoframe->u32SamplingFrequency = HI_UNF_HDMI_DEFAULT_SETTING;
    pstAUDInfoframe->u32ChannelAlloc      = 0;
    pstAUDInfoframe->u32LevelShift        = 0;
    pstAUDInfoframe->u32DownmixInhibit    = HI_FALSE;
#ifdef __HDMI_SIMPLY_HD_TEST__
    if (compressFlag >= 1)
    {
        //Only for HDMI SimplyHD specific Test
        printf("compress:special compress test\n");
        pstAUDInfoframe->u32SamplingFrequency = HI_UNF_HDMI_DEFAULT_SETTING;
        pstAUDInfoframe->u32ChannelCount      = 6;
        pstAUDInfoframe->u32ChannelAlloc      = 0x0b;
    }
#endif
    printf("***HI_UNF_HDMI_SetInfoFrame for AUDIO Infoframe\n");
    RetError = HI_UNF_HDMI_SetInfoFrame(enTest_Hdmi_ID, &InfoFrame);

    RetError = hdmi_a_mute(HI_TRUE);

    RetError = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    RetError = hdmi_a_mute(HI_FALSE);

    return RetError;
}
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

HI_U32 hdmi_a_passtru(HI_U32 passTruFlag)
{
    HI_U32              Ret = HI_SUCCESS;

    if(passTruFlag == 0)
    {
        Ret = HI_UNF_SND_SetHdmiMode(0,HI_UNF_SND_OUTPUTPORT_HDMI0,HI_UNF_SND_HDMI_MODE_LPCM);
        printf("hdmi passthru off 0x%x \n",Ret);
    }
    else
    {
        Ret = HI_UNF_SND_SetHdmiMode(0,HI_UNF_SND_OUTPUTPORT_HDMI0,HI_UNF_SND_HDMI_MODE_RAW);
        printf("hdmi passthru on 0x%x \n",Ret);
    }
    return Ret;
}

HI_U32 hdmi_hdcp(HI_U32 hdcpflag)
{
    HI_U32              RetError = HI_SUCCESS;
    HI_UNF_HDMI_ATTR_S  attr;

    printf("hdmi_hdcp hdcpflag:%d with HI_UNF_HDMI_SetAttr\n", hdcpflag);
    printf("\n*******Warnning:HDCP Can Only be Enable/Disable at the beginnig!!!!!*******\n");
    printf("This is just for test, Appication should not change HDCP Flag during running\n");

    RetError = HI_UNF_HDMI_GetAttr(enTest_Hdmi_ID, &attr);
    if (hdcpflag)
    {
        attr.bHDCPEnable = HI_TRUE;//Enable HDCP
    }
    else
    {
        attr.bHDCPEnable= HI_FALSE;
    }

    //HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_TRUE);
    RetError = HI_UNF_HDMI_SetAttr(enTest_Hdmi_ID, &attr);
    //HI_UNF_HDMI_SetAVMute(enTest_Hdmi_ID, HI_FALSE);


    return RetError;
}

static HI_U32 hdmi_cec_autoping(void)
{
    HI_U32                 RetError = HI_SUCCESS;
    HI_UNF_HDMI_CEC_CMD_S  CECCmd;

    printf("CEC Auto Ping\n");
    memset(&CECCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));
    CECCmd.enSrcAdd = HI_UNF_CEC_LOGICALADD_TUNER_1;
    CECCmd.enDstAdd = HI_UNF_CEC_LOGICALADD_TV;
    CECCmd.u8Opcode = CEC_OPCODE_POLLING_MESSAGE;

    HI_UNF_HDMI_SetCECCommand(enTest_Hdmi_ID, &CECCmd);

    return RetError;
}

static HI_U32 hdmi_cec_setcmd(HI_U8 destAddr, HI_U8 u8Opcode, HI_U8 *data, HI_U8 Datalength)
{
    HI_U32                 RetError = HI_SUCCESS;
    HI_UNF_HDMI_CEC_CMD_S  CECCmd;

    printf("CEC hdmi_cec_cmd, destAddr:0x%x, u8Opcode:0x%x, Datalength:0x%x\n", destAddr, u8Opcode, Datalength);
    usleep(300*1000);
    memset(&CECCmd, 0, sizeof(HI_UNF_HDMI_CEC_CMD_S));
    CECCmd.enSrcAdd = HI_UNF_CEC_LOGICALADD_TUNER_1;
    CECCmd.enDstAdd = destAddr;//HI_UNF_CEC_LOGICALADD_TV;
    CECCmd.u8Opcode = u8Opcode;
    CECCmd.unOperand.stRawData.u8Length = Datalength;
    memcpy(&(CECCmd.unOperand.stRawData.u8Data), data, Datalength);

    HI_UNF_HDMI_SetCECCommand(enTest_Hdmi_ID, &CECCmd);

    return RetError;
}


static HI_U32 hdmi_ResetTest(HI_U32 loop)
{
    HI_S32 ret  = 0;

    if (loop <= 0)
    {
        loop = 10;
    }
    printf("Begin to do reset test\n");
#if 1
{
  //  HI_UNF_HDMI_INIT_PARA_S pstHdmiPara;

    HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);

    while((loop --) >= 1)
    {
        sleep(1);
        printf("www continue to loop:%d\n", loop);
        //memset(&pstHdmiPara, 0, sizeof(HI_UNF_HDMI_INIT_PARA_S));
        ret = HI_UNF_HDMI_Init();
        sleep(3);
        ret = HI_UNF_HDMI_DeInit();
        printf("reset finish\n");
    }
    HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, HI_UNF_ENC_FMT_720P_50);
}
#else
    while((loop --) >= 1)
    {
        sleep(10);
        printf("continue to loop:%d\n", loop);
        HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);
        sleep(1);
        HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, HI_UNF_ENC_FMT_720P_50);
        printf("reset finish\n");
    }
#endif
    return 0;
}

static HI_U32 hdmi_ReOpenTest(HI_U32 loop)
{
    if (loop <= 0)
    {
        loop = 10;
    }
    printf("Begin to do reset test\n");
    HI_UNF_HDMI_OPEN_PARA_S stOpenParam;
    memset(&stOpenParam, 0, sizeof(HI_UNF_HDMI_OPEN_PARA_S));
    stOpenParam.enDefaultMode = HI_UNF_HDMI_DEFAULT_ACTION_NULL;
    while((loop --) >= 1)
    {
        sleep(5);
        printf("continue to loop:%d\n", loop);
        HI_UNF_HDMI_Close(HI_UNF_HDMI_ID_0);
        sleep(2);
        printf("reopen\n");
        HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0,&stOpenParam);

        printf("reopen finish\n");
    }

    return 0;
}

static HI_U32 hdmi_ReStartTest(HI_U32 loop)
{
    if (loop <= 0)
    {
        loop = 10;
    }
    printf("Begin to do reset test\n");

    while((loop --) >= 1)
    {
        sleep(5);
        printf("continue to loop:%d\n", loop);
        HI_UNF_HDMI_Stop(HI_UNF_HDMI_ID_0);
        sleep(2);
        printf("stop\n");
        HI_UNF_HDMI_Start(HI_UNF_HDMI_ID_0);
        printf("restart finish\n");
    }

    return 0;
}

static HI_U32 hdmi_RegDebug(HI_U32 Debugflag)
{
    HI_U32 index;
    HI_U32 hdmiregister = 0;

    if (Debugflag == 0)
    {
        printf("Debug hdmi DDC register:\n");
        for (index=0xEC; index<=0xF5; index++)
        {
            HI_SYS_ReadRegister((HDMI_BASE_REG_ADDR + index * 4), &hdmiregister);
            printf("0x%02x(0x72, 0x%02x):0x%02x\n", (HDMI_BASE_REG_ADDR + index * 4), index, hdmiregister);
        }
        printf("\nFinish\n");
    }

    else if (Debugflag == 1)
    {
        {
            HI_U8 index;
            HI_U32 hdmiregister = 0;
            printf("Debug hdmi audio register:\n");
            for (index=0; index<=0x30; index++)
            {
                HI_SYS_ReadRegister((HDMI_BASE_REG_ADDR + (0x100 + index) * 4), &hdmiregister);
                printf("0x%02x(0x7a, 0x%02x):0x%02x\n", (HDMI_BASE_REG_ADDR + (0x100 + index) * 4), index, hdmiregister);
            }
            printf("\n");
        }
        {
            HI_U8 index;
            HI_U32 hdmiregister = 0;
            printf("Debug hdmi audio infoframe:\n");
            for (index=0x80; index<=0x8D; index++)
            {
                HI_SYS_ReadRegister((HDMI_BASE_REG_ADDR + (0x100 + index) * 4), &hdmiregister);
                printf("0x%02x(0x7a, 0x%02x):0x%02x\n", (HDMI_BASE_REG_ADDR + (0x100 + index) * 4), index, hdmiregister);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Debug hdmi All 0x72 register:\n");
        for (index=0x00; index<=0xFF; index++)
        {
            HI_SYS_ReadRegister((HDMI_BASE_REG_ADDR + index * 4), &hdmiregister);
            printf("0x%02x(0x72, 0x%02x):0x%02x\n", (HDMI_BASE_REG_ADDR + index * 4), index, hdmiregister);
            usleep(1000 * 10);
        }
        usleep(1000* 100);
        printf("Debug hdmi All 0x7a register:\n");
        for (index=0x00; index<=0xFF; index++)
        {
            HI_SYS_ReadRegister((HDMI_BASE_REG_ADDR +(0x100 + index) * 4), &hdmiregister);
            printf("0x%02x(0x7a, 0x%02x):0x%02x\n", (HDMI_BASE_REG_ADDR +(0x100 + index) * 4), index, hdmiregister);
            usleep(1000 * 10);
        }
        usleep(1000* 100);
        printf("Debug hdmi All 0xCC register:\n");
        for (index=0x80; index<=0xF2; index++)
        {
            HI_SYS_ReadRegister((HDMI_BASE_REG_ADDR +(0x200 + index) * 4), &hdmiregister);
            printf("0x%02x(0xCC, 0x%02x):0x%02x\n", (HDMI_BASE_REG_ADDR +(0x200 + index) * 4), index, hdmiregister);
            usleep(1000 * 10);
        }
        printf("\nFinish\n");
    }
    return 0;
}

static HI_U32 SI_DDC_Adjust(void)
{
    HI_U32 Ret;
    HI_U32 value;
    HI_S32 count = 0;

    HI_U32    u32BaseAddr = 0xf8a21000;

    //DDC_DELAY_CNT  osc=50Mhz  dscl = 50Mhz / (DDC_DELAY_CNT * 8) = 62500 hz
    // dscl should in range 48Khz ~ 72Khz
    HI_SYS_WriteRegister(0xf8ce03d8, 0x1a); //DDC_DELAY_CNT

    //bit 6  bus_low
    HI_SYS_ReadRegister(0xf8ce03c8, &value);
    printf("DDC Status(0x72:0xf2):0x%x\n", value);

    HI_SYS_ReadRegister(u32BaseAddr + 0x04, &value);
    printf("HDMI PINSHARE Tx_SDA:0x%x is:0x%x\n", u32BaseAddr + 0x04, value);

    HI_SYS_ReadRegister(u32BaseAddr + 0x00, &value);
    printf("HDMI PINSHARE Tx_SCL:0x%x is:0x%x\n", u32BaseAddr + 0x00, value);


    //gpio
    if(value == 0x01)
    {
        //PIO Mode
        //himm 0xF8A21000 0x00 GPIO0_0 // HDMI_TX_SCL
        //himm 0xF8A21004 0x00 GPIO0_1 // HDMI_TX_SDA
        HI_SYS_WriteRegister(u32BaseAddr + 0x00,(HI_U32)0x00);
        HI_SYS_WriteRegister(u32BaseAddr + 0x04,(HI_U32)0x00);


        //if SDA is low, need to create clock in SCL
        //SDA is high

        HI_UNF_GPIO_Init();
        //Set GPIO0_1:HDMI_SDA input
        //  u32GpioNo = 组号*8 + 在组里的编号
        Ret = HI_UNF_GPIO_SetDirBit(0*8 + 1, HI_TRUE);//GPIO0_1:HDMI_SDA

        Ret = HI_UNF_GPIO_SetDirBit(0, HI_FALSE);//GPIO0_0:HDMI_SCL

        Ret = HI_UNF_GPIO_ReadBit(1, &value);//GPIO0_1:HDMI_SDA

        printf("Current Value:%d\n", value);
        //in order to pull up HDMI_SDA,try to set HDMI_SCL repeat
        while ((value == 0) && ((count ++) < 20))
        {
            printf("***Pull up SCL Voltage for DDC, count:%d\n", count);

            Ret = HI_UNF_GPIO_WriteBit(0, HI_TRUE);//GPIO0_0:HDMI_SCL
            usleep(1000);//msleep(1);

            Ret = HI_UNF_GPIO_WriteBit(0, HI_FALSE);//GPIO0_0:HDMI_SCL
            usleep(1000);//msleep(1);

            Ret = HI_UNF_GPIO_ReadBit(1, &value);//GPIO0_1:HDMI_SDA
        }

        if (value == 0)
        {
            printf("Can not pull up SCL Voltage\n");
        }

        //SDA/SCL Mode
        //himm 0xF8A21000 0x01 HDMI_TX_SCL
        //himm 0xF8A21004 0x01 HDMI_TX_SDA  //DDC
        Ret = HI_SYS_WriteRegister(u32BaseAddr + 0x00,(HI_U32)0x01);
        HI_SYS_WriteRegister(u32BaseAddr + 0x04,(HI_U32)0x01);
    }

    return HI_SUCCESS;
}

static HI_U32 hdmi_EDIDTest(HI_U32 loop)
{
    HI_U32 u32BaseAddr, value;
    HI_U32 Timeout, index;

    if (loop <= 0)
    {
        loop = 10;
    }
    else if(loop >= 1000)
    {
        loop = 1000;
    }

    u32BaseAddr = 0xf8ce03c8; //0x7a:0xf2:DDC I2C Target Slave Address Register
    HI_SYS_ReadRegister(u32BaseAddr, &value);
    printf("DDC Status(0x7a:0xf2):0x%x\n", value);

    printf("Begin to do EDID test\n");
    SI_DDC_Adjust();

    while(loop --)
    {
        usleep(200*1000);
        printf("continue to loop:%d\n", loop);

        /*the addr of edid is 0xa0*/
        u32BaseAddr = 0xf8ce03b4; //0x7a:0xed:DDC I2C Target Slave Address Register
        HI_SYS_WriteRegister(0xf8ce03b4, 0xa0);
        /* get the data of seg 0(256)*/
        //Set DDC Segment Address:0
        u32BaseAddr = 0xf8ce03b8; //0x7a:0xee:DDC I2C Target Slave Address Register
        HI_SYS_WriteRegister(u32BaseAddr, 0x0);
        //Set DDC offset, try to Read EDID version, offset 0x12, 0x13.
        u32BaseAddr = 0xf8ce03bc; //0x7a:0xef:DDC I2C Target Slave Address Register
        HI_SYS_WriteRegister(u32BaseAddr, 0x12);

        //The total number of bytes to be read from the slave.
        u32BaseAddr = 0xf8ce03c0; //0x7a:0xf0:DDC I2C Target Slave Address Register
        HI_SYS_WriteRegister(u32BaseAddr, 0x08);
        //HI_SYS_WriteRegister(u32BaseAddr, 0x01);
        //clear DDC fifo, 0x09:0b1001 = Clear FIFO
        u32BaseAddr = 0xf8ce03cc; //0x7a:0xf3:DDC I2C Command Register
        HI_SYS_WriteRegister(u32BaseAddr, 0x09);
        /*begin the read operation of ddc*/
        //start read edid, 0x02:0b0010 = Sequential Read with no ACK on last byte
        u32BaseAddr = 0xf8ce03cc; //0x7a:0xf3:DDC I2C Command Register
        HI_SYS_WriteRegister(u32BaseAddr, 0x02);

        usleep(10*1000);

        Timeout = 100;
        while((Timeout) ++ < 10)
        {
            //read DDC status!
            u32BaseAddr = 0xf8ce03c8; //0x7a:0xf2:DDC I2C Target Slave Address Register

            HI_SYS_ReadRegister(u32BaseAddr, &value);
            if((value & 0x10) == 0)
            {
                break;
            }
            usleep(10*1000);
        }
        if(Timeout == 0)
        {
            printf("*****DDC status:0x%x busy!!!", value);
            return 0;
        }

        u32BaseAddr = 0xf8ce03d4; //0x7a:0xf2:DDC I2C Target Slave Address Register
        HI_SYS_ReadRegister(u32BaseAddr, &value);
        printf("we will read %d bytes\n", value);
        for(index = 0; index < value; index ++)
        {
            HI_U32 data;
            u32BaseAddr = 0xf8ce03d0; //0x7a:0xf2:DDC I2C Target Slave Address Register
            HI_SYS_ReadRegister(u32BaseAddr, &data);
            printf("%02d:0x%x\n", index, data);
        }
        printf("Read Succeeed!!!!");
        printf("\n\n");
    }

    return 0;
}

/***********************************************************************
Function   :
Description:
Input      :
Output     :
Return     :
***********************************************************************/
HI_U32 HDMI_Test_CMD(HI_CHAR * u8String)
{
    HI_U8 argc = 0;

    if (NULL == u8String)
    {
        return HI_FAILURE;
    }
    memset(args, 0, sizeof(args));
    argc = Hdmi_AdjustString(u8String);

    if ( (0 == strcmp("q", (char *)args[0])) || (0 == strcmp("Q", (char *)args[0]))
      || (0 == strcmp("quit", (char *)args[0])) || (0 == strcmp("QUIT", (char *)args[0])) )
    {
        printf("quit the program, use extran interface to quit\n");
        return HI_FAILURE;
    }

    return Hdmi_ParseArg(argc);
}

static HI_U32 hdmi_RandomSwitch(HI_U8 EnableFlag)
{
    HI_U32 RetError = HI_SUCCESS;
    HI_U32 CurrentIndex;
    struct timeval Time0;
    HI_U32 index = 1;

    gettimeofday(&Time0, NULL);
    srand(Time0.tv_usec);
#if 1
    //while(index)// ++  < 10)
    while(index ++  < 10)
    {
        CurrentIndex = rand();
        CurrentIndex %= (HI_UNF_ENC_FMT_NTSC + 1);
        //CurrentIndex %= HI_UNF_ENC_FMT_VESA_2048X1152_60;

        hdmi_video_timing(CurrentIndex);
        sleep(5);
    }
#else
    HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);

    while(index)// ++  < 10)
    {
        CurrentIndex = rand();
        //CurrentIndex %= (HI_UNF_ENC_FMT_NTSC + 1);
        CurrentIndex %= HI_UNF_ENC_FMT_VESA_2048X1152_60;

        if(CurrentIndex <= 10)
        {
            CurrentIndex = CurrentIndex;
        }
        else if(CurrentIndex == 11)
        {
            printf("PAL\n");
            CurrentIndex = HI_UNF_ENC_FMT_PAL;
        }
        else if(CurrentIndex == 12)
        {
            printf("NTSC\n");
            CurrentIndex = HI_UNF_ENC_FMT_NTSC;
        }
        else if((CurrentIndex >= 13) && (CurrentIndex < 22))
        {
            printf("640*480\n");
            CurrentIndex = (CurrentIndex - 13) + HI_UNF_ENC_FMT_861D_640X480_60;
        }

        if(CurrentIndex <= HI_UNF_ENC_FMT_NTSC)
        {
            printf("change to DTV\n");
            CurrentIndex = CurrentIndex;
            HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_TV);
            HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, CurrentIndex);
        }
        else
        {
            printf("change to LCD\n");
            HI_UNF_DISP_SetIntfType(HI_UNF_DISPLAY1, DISP_INTF_TYPE_LCD);
            HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, CurrentIndex);
        }
        sleep(2);
    }

    HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, HI_UNF_ENC_FMT_1080i_50);
#endif

    return RetError;
}



static HI_U32 hdmi_set_disp_3d(HI_UNF_DISP_3D_E en3D)
{
    HI_U32                 Ret = HI_SUCCESS;
    HI_UNF_ENC_FMT_E enEncFormat;
    HI_UNF_DISP_GetFormat(HI_UNF_DISPLAY1,&enEncFormat);
    printf("\n disp Fmt: %d \n",enEncFormat);

    if(en3D == 0x01)
    {
        if( enEncFormat == HI_UNF_ENC_FMT_1080P_60 ||
            enEncFormat == HI_UNF_ENC_FMT_1080P_50 ||
            enEncFormat == HI_UNF_ENC_FMT_1080P_30 ||
            enEncFormat == HI_UNF_ENC_FMT_1080P_25 ||
            enEncFormat == HI_UNF_ENC_FMT_1080P_24 ||
            enEncFormat == HI_UNF_ENC_FMT_1080i_60 ||
            enEncFormat == HI_UNF_ENC_FMT_1080i_50)
        {
            Last2DFmt = enEncFormat;
            enEncFormat = HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING;
        }
        else if(enEncFormat == HI_UNF_ENC_FMT_720P_60)
        {
            Last2DFmt = enEncFormat;
            enEncFormat = HI_UNF_ENC_FMT_720P_60_FRAME_PACKING;
        }
        else if(enEncFormat == HI_UNF_ENC_FMT_720P_50)
        {
            Last2DFmt = enEncFormat;
            enEncFormat = HI_UNF_ENC_FMT_720P_50_FRAME_PACKING;
        }

        Ret = HI_UNF_DISP_Set3DMode(HI_UNF_DISPLAY1,en3D,enEncFormat);
    }
    else
    {
        if(Last2DFmt == HI_UNF_ENC_FMT_BUTT)
        {
            Last2DFmt = enEncFormat;
        }

        Ret = HI_UNF_DISP_Set3DMode(HI_UNF_DISPLAY1,en3D,Last2DFmt);
    }
    return Ret;
}

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
static HI_HANDLE hLayer, hImageSurface;
static HI_S32 Test_DecFile(const HI_CHAR *pszFileName, HI_HANDLE *pSurface)
{
    HI_S32 ret;
    HI_HANDLE hDecoder;
    HIGO_DEC_ATTR_S stSrcDesc;

    /** Create Higo Deocoder */
    stSrcDesc.SrcType = HIGO_DEC_SRCTYPE_FILE;
    stSrcDesc.SrcInfo.pFileName = pszFileName;
    ret = HI_GO_CreateDecoder(&stSrcDesc, &hDecoder);
    if (HI_SUCCESS != ret)
    {
        return ret;
    }

    ret  = HI_GO_DecImgData(hDecoder, 0, NULL, pSurface);
    ret |= HI_GO_DestroyDecoder(hDecoder);

    return ret;
}

static HI_S32 Test_DoDecImageTime(const HI_CHAR* pFile, HI_S32 *pTimeCosted)
{
    HI_S32 ret;
    HIGO_LAYER_INFO_S stLayerInfo;
    HI_S32 i;
    struct timeval t1, t2;
    HI_S32 t;
    HIGO_BLTOPT_S opt = {0};
    HI_HANDLE hDstSurface;

    HI_RECT_S SRect, Rect;

    ret = HI_GO_GetLayerDefaultParam(HIGO_LAYER_HD_0, &stLayerInfo);
    if (HI_SUCCESS != ret)
    {
        return HI_FAILURE;
    }

    stLayerInfo.CanvasWidth = 1920;
    stLayerInfo.CanvasHeight = 1080;
    //stLayerInfo.DisplayWidth = 1920;
    //  stLayerInfo.DisplayHeight = 1080;
    stLayerInfo.ScreenWidth = 1920;
    stLayerInfo.ScreenHeight = 1080;
    stLayerInfo.PixelFormat = HIGO_PF_8888;
    ret = HI_GO_CreateLayer(&stLayerInfo,&hLayer);
    if (HI_SUCCESS != ret)
    {
        printf("failed to create the layer!\n");
        return HI_FAILURE;
    }

    ret = HI_GO_GetLayerSurface (hLayer,&hDstSurface);
    if (HI_SUCCESS != ret)
    {
        printf("failed to get the layer surface!\n");
        goto RET;
    }

    ret = HI_GO_FillRect(hDstSurface, NULL, 0x00000000, HIGO_COMPOPT_NONE);
    if (HI_SUCCESS != ret)
    {
       printf("failed to fill the layer surface!\n");
       goto RET;
    }

    HI_GO_SyncSurface(hDstSurface, HIGO_SYNC_MODE_CPU);

    gettimeofday(&t1, NULL);
    /** Output text */
    for (i=0; i<5; i++)
    {
        if (hImageSurface != HIGO_INVALID_HANDLE)
        {
            HI_GO_FreeSurface(hImageSurface);
        }

        ret = Test_DecFile(pFile, &hImageSurface);
        if (HI_SUCCESS != ret)
        {
            printf("failed to dec file:%s !\n", pFile);
            goto RET;
        }
    }

    gettimeofday(&t2, NULL);
    t = ((t2.tv_sec*1000000 + t2.tv_usec) - (t1.tv_sec*1000000 + t1.tv_usec))/1000;
    *pTimeCosted = t/5;
#if 1
    SRect.s32X = 0;
    SRect.s32Y = 0;
    SRect.s32Width = 1920;
    SRect.s32Height = 1080;

    Rect.s32X = 0;
    Rect.s32Y = 0;
    Rect.s32Width = 1920/2;
    Rect.s32Height = 1080;
    printf("1:Rect.s32X:%d\n", Rect.s32X);
    memset(&opt, 0, sizeof(HIGO_BLTOPT_S));
    opt.EnableScale = HI_TRUE;
    ret = HI_GO_Blit(hImageSurface, NULL, hDstSurface, (const HI_RECT* )&Rect, &opt);

    Rect.s32X = 1920 / 2;
    printf("2:Rect.s32X:%d\n", Rect.s32X);
    ret = HI_GO_Blit(hImageSurface, NULL, hDstSurface, (const HI_RECT *)&Rect, &opt);
#else
    Rect.s32X = 300;
    Rect.s32Y = 500;
    Rect.s32Width = 400;
    Rect.s32Height = 300;
    printf("1:Rect.s32X:%d\n", Rect.s32X);
    ret = HI_GO_Blit(hImageSurface, NULL, hDstSurface, (const HI_RECT* )&Rect, &opt);

    Rect.s32X = 1920 / 2 + Rect.s32X;//1500;
    Rect.s32Y = 500;
    Rect.s32Width = 400;
    Rect.s32Height = 300;
    printf("2:Rect.s32X:%d\n", Rect.s32X);
    ret = HI_GO_Blit(hImageSurface, NULL, hDstSurface, (const HI_RECT *)&Rect, &opt);
#endif
    HI_GO_SyncSurface(hDstSurface, HIGO_SYNC_MODE_CPU);

    /**  Flash Display Content  */
    ret = HI_GO_RefreshLayer(hLayer, NULL);
    return 0;

RET:
    HI_GO_FreeSurface(hImageSurface);
    ret = HI_GO_DestroyLayer(hLayer);
    return HI_SUCCESS;
}
static HI_U32 HigoBegin = HI_FALSE;
static HI_S32 Test_DecImageTime_JPG(void)
{
    HI_S32 ret = HI_SUCCESS;
    HI_S32 TimeCosted;

    if (HigoBegin == HI_FALSE)
    {
        ret |= HI_GO_Init();
        if (HI_SUCCESS != ret)
        {
            printf("Init Hi_Go Error\n");
            return HI_FAILURE;
        }
        HigoBegin = HI_TRUE;
    }

    Test_DoDecImageTime("./sample.jpg", &TimeCosted);
#if 0
    HigoBegin = HI_FALSE;

    ret |= HI_GO_Deinit();
    if (HI_SUCCESS != ret)
    {
        printf("DeInit Hi_Go Error\n");
        return HI_FAILURE;
    }
#endif
    return 0;
}

static HI_U32 hdmi_picture_display(void)
{
    Test_DecImageTime_JPG();
    return 0;
}
static HI_U32 hdmi_picture_clear(void)
{
    HI_S32 ret;

    HigoBegin = HI_FALSE;

    HI_GO_FreeSurface(hImageSurface);
    ret = HI_GO_DestroyLayer(hLayer);

    ret |= HI_GO_Deinit();
    if (HI_SUCCESS != ret)
    {
        printf("DeInit Hi_Go Error\n");
        return HI_FAILURE;
    }
    return 0;
}
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

/*-----------------------------------END--------------------------------*/
