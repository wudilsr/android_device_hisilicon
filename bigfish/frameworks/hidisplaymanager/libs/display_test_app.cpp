#include <stdio.h>
#include <stdlib.h>
#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include <utils/threads.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include <binder/IBinder.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <utils/threads.h>
#include <sys/types.h>
#include "stdlib.h"
#include "DisplayClient.h"
#include "displaydef.h"

#define CAP_CHAR_SIZE (DISP_ENC_FMT_BUTT+1)

using namespace android;

const char *FmtCharTable[CAP_CHAR_SIZE] = {
    "Is support 3d                      ",
    "HI_UNF_ENC_FMT_1080P_60            ",
    "HI_UNF_ENC_FMT_1080P_50            ",
    "HI_UNF_ENC_FMT_1080P_30            ",
    "HI_UNF_ENC_FMT_1080P_25            ",
    "HI_UNF_ENC_FMT_1080P_24            ",
    "HI_UNF_ENC_FMT_1080i_60            ",
    "HI_UNF_ENC_FMT_1080i_50            ",
    "HI_UNF_ENC_FMT_720P_60             ",
    "HI_UNF_ENC_FMT_720P_50             ",
    "HI_UNF_ENC_FMT_576P_50             ",
    "HI_UNF_ENC_FMT_480P_60             ",
    "HI_UNF_ENC_FMT_PAL                 ",
    "HI_UNF_ENC_FMT_PAL_N               ",
    "HI_UNF_ENC_FMT_PAL_Nc              ",
    "HI_UNF_ENC_FMT_NTSC                ",
    "HI_UNF_ENC_FMT_NTSC_J              ",
    "HI_UNF_ENC_FMT_NTSC_PAL_M          ",
    "HI_UNF_ENC_FMT_SECAM_SIN           ",
    "HI_UNF_ENC_FMT_SECAM_COS           ",
    "HI_UNF_ENC_FMT_1080P_24_FRAME_PACKING",
    "HI_UNF_ENC_FMT_720P_60_FRAME_PACKING",
    "HI_UNF_ENC_FMT_720P_50_FRAME_PACKING",
    "HI_UNF_ENC_FMT_861D_640X480_60     ",
    "HI_UNF_ENC_FMT_VESA_800X600_60     ",
    "HI_UNF_ENC_FMT_VESA_1024X768_60    ",
    "HI_UNF_ENC_FMT_VESA_1280X720_60    ",
    "HI_UNF_ENC_FMT_VESA_1280X800_60    ",
    "HI_UNF_ENC_FMT_VESA_1280X1024_60   ",
    "HI_UNF_ENC_FMT_VESA_1360X768_60    ",
    "HI_UNF_ENC_FMT_VESA_1366X768_60    ",
    "HI_UNF_ENC_FMT_VESA_1400X1050_60   ",
    "HI_UNF_ENC_FMT_VESA_1440X900_60    ",
    "HI_UNF_ENC_FMT_VESA_1440X900_60_RB ",
    "HI_UNF_ENC_FMT_VESA_1600X900_60_RB ",
    "HI_UNF_ENC_FMT_VESA_1600X1200_60   ",
    "HI_UNF_ENC_FMT_VESA_1680X1050_60   ",
    "HI_UNF_ENC_FMT_VESA_1680X1050_60_RB ",
    "HI_UNF_ENC_FMT_VESA_1920X1080_60   ",
    "HI_UNF_ENC_FMT_VESA_1920X1200_60   ",
    "HI_UNF_ENC_FMT_VESA_1920X1440_60   ",
    "HI_UNF_ENC_FMT_VESA_2048X1152_60   ",
    "HI_UNF_ENC_FMT_VESA_2560X1440_60_RB ",
    "HI_UNF_ENC_FMT_VESA_2560X1600_60_RB ",
    "HI_UNF_ENC_FMT_3840X2160_24      ",
    "HI_UNF_ENC_FMT_3840X2160_25      ",
    "HI_UNF_ENC_FMT_3840X2160_30      ",
    "HI_UNF_ENC_FMT_3840X2160_50      ",
    "HI_UNF_ENC_FMT_3840X2160_60      ",
    "HI_UNF_ENC_FMT_4096X2160_24      ",
    "HI_UNF_ENC_FMT_4096X2160_25      ",
    "HI_UNF_ENC_FMT_4096X2160_30      ",
    "HI_UNF_ENC_FMT_4096X2160_50      ",
    "HI_UNF_ENC_FMT_4096X2160_60      ",
    "HI_UNF_ENC_FMT_3840X2160_23_976   ",
    "HI_UNF_ENC_FMT_3840X2160_29_97     ",
    "HI_UNF_ENC_FMT_720P_59_94          ",
    "HI_UNF_ENC_FMT_1080P_59_94        ",
    "HI_UNF_ENC_FMT_1080P_29_97        ",
    "HI_UNF_ENC_FMT_1080P_23_976      ",
    "HI_UNF_ENC_FMT_1080i_59_94         ",
};


int main(int argc, char *argv[])
{
    DisplayClient disp;

    int ret = -1;

    if(argc <= 2)
    {
        if(argc == 1)
        {
            printf("disptest --help\n");
        }
        else
        {
            if(0==strncmp("--help",argv[1],sizeof("--help")))
            {

                printf("Example:\tdisptest setbright value  (0 <= value <= 100)\n");
                printf("\t\tdisptest setcontrast value      (0 <= value <= 100)\n");
                printf("\t\tdisptest sethue value           (0 <= value <= 100)\n");
                printf("\t\tdisptest setsaturation value    (0 <= value <= 100)\n");

                printf("\t\tdisptest setfmt mode\n");
                printf("\t\tmode ---------------------- value\n");
                printf("\t\tFMT_1080P_60 -------------- 0\n");
                printf("\t\tFMT_1080P_50 -------------- 1\n");
                printf("\t\tFMT_1080P_30 -------------- 2\n");
                printf("\t\tFMT_1080P_25 -------------- 3\n");
                printf("\t\tFMT_1080P_24 -------------- 4\n");
                printf("\t\tFMT_1080i_60 -------------- 5\n");
                printf("\t\tFMT_1080i_50 -------------- 6\n");
                printf("\t\tFMT_720P_60 --------------- 7\n");
                printf("\t\tFMT_720P_50 --------------- 8\n");
                printf("\t\tFMT_576P_50 --------------- 9\n");
                printf("\t\tFMT_480P_60 --------------- 10\n");
                printf("\t\tFMT_PAL ------------------- 11\n");
                printf("\t\tFMT_PAL_N ----------------- 12\n");
                printf("\t\tFMT_PAL_Nc ---------------- 13\n");
                printf("\t\tFMT_NTSC ------------------ 14\n");
                printf("\t\tFMT_NTSC_J ---------------- 15\n");
                printf("\t\tFMT_NTSC_PAL_M ------------ 16\n");
                printf("\t\tFMT_SECAM_SIN ------------- 17\n");
                printf("\t\tFMT_SECAM_COS ------------- 18\n");

                printf("\t\tFMT_1080P_24_FRAME_PACKING- 19\n");
                printf("\t\tFMT_720P_60_FRAME_PACKING - 20\n");
                printf("\t\tFMT_720P_50_FRAME_PACKING - 21\n");

                printf("\t\tFMT_861D_640X480_60 ------- 22\n");
                printf("\t\tFMT_VESA_800X600_60 ------- 23\n");
                printf("\t\tFMT_VESA_1024X768_60 ------ 24\n");
                printf("\t\tFMT_VESA_1280X720_60 ------ 25\n");
                printf("\t\tFMT_VESA_1280X800_60 ------ 26\n");
                printf("\t\tFMT_VESA_1280X1024_60 ----- 27\n");
                printf("\t\tFMT_VESA_1360X768_60 ------ 28\n");
                printf("\t\tFMT_VESA_1366X768_60 ------ 29\n");
                printf("\t\tFMT_VESA_1400X1050_60 ----- 30\n");
                printf("\t\tFMT_VESA_1400X1050_60 ------ 31\n");
                printf("\t\tFMT_VESA_1440X900_60_RB --- 32\n");
                printf("\t\tFMT_VESA_1600X900_60_RB --- 33\n");
                printf("\t\tFMT_VESA_1600X1200_60 --- 34\n");
                printf("\t\tFMT_VESA_1680X1050_60 ----- 35\n");
                printf("\t\tFMT_VESA_1680X1050_60_RB ----- 36\n");
                printf("\t\tFMT_VESA_1920X1080_60 ----- 37\n");
                printf("\t\tFMT_VESA_1920X1200_60 ----- 38\n");
                printf("\t\tFMT_VESA_1920X1440_60 ----- 39\n");
                printf("\t\tFMT_VESA_2048X1152_60 ----- 40\n");
                printf("\t\tFMT_VESA_2560X1440_60_RB ----- 41\n");
                printf("\t\tFMT_VESA_2560X1600_60_RB ----- 42\n");

                printf("\t\tFMT_3840X2160_24  ----- 256\n");
                printf("\t\tFMT_3840X2160_25 ----- 257\n");
                printf("\t\tFMT_3840X2160_30 ----- 258\n");
                printf("\t\tFMT_3840X2160_50 ----- 259\n");
                printf("\t\tFMT_3840X2160_60 ----- 260\n");

                printf("\t\tFMT_4096X2160_24 ----- 261\n");
                printf("\t\tFMT_4096X2160_25 ----- 262\n");
                printf("\t\tFMT_4096X2160_30 ----- 263\n");
                printf("\t\tFMT_4096X2160_50 ----- 264\n");
                printf("\t\tFMT_4096X2160_60 ----- 265\n");

                printf("\t\tFMT_3840X2160_23_976  ---266\n");
                printf("\t\tFMT_3840X2160_29_97 ---- 267\n");
                printf("\t\tFMT_720P_59_94 --------- 268\n");
                printf("\t\tFMT_1080P_59_94 -------- 269\n");
                printf("\t\tFMT_1080P_29_97  -------- 270\n");
                printf("\t\tFMT_1080P_23_976 ------- 271\n");
                printf("\t\tFMT_1080i_59_94 --------- 272\n");

                printf("\t\tdisptest setrange left top width height\n");
                printf("\t\t0<= left <= FMT_MAX_WIDTH\n");
                printf("\t\t0<= top <= FMT_MAX_HEIGHT\n");
                printf("\t\t32 <= width <= FMT_MAX_WIDTH\n");
                printf("\t\t32 <= height <= FMT_MAX_HEIGHT\n");
                printf("\t\tleft + width <= FMT_MAX_WIDTH\n");
                printf("\t\ttop + height <= FMT_MAX_HEIGHT\n");
                printf("\t\tFMT_MAX_WIDTH and FMT_MAX_HEIGHT distinguish acorrding to Format\n");

                printf("\t\tdisptest gethdmicap\n");
                printf("\t\t--check which capabilities that hdmi support\n");

                printf("\t\tdisptest sethdcp value\n");
                printf("\t\t--enable HDCP or not\n");

                printf("\t\tdisptest gethdcp value\n");
                printf("\t\t--get hdcp\n");

                printf("\t\tdisptest gethdmicap\n");
                printf("\t\t--get hdmi cap\n");

                printf("\t\tdisptest setmacrovision value\n");
                printf("\t\t--set MacroVision mode\n");

                printf("\t\tdisptest getmacrovision\n");
                printf("\t\t--get MacroVision mode\n");

                printf("\t\tdisptest setstereooutmode value videofps\n");
                printf("\t\t--set Stereo Out Mode\n");

                printf("\t\tdisptest getstereooutmode\n");
                printf("\t\t--get Stereo Out Mode\n");

                printf("\t\tdisptest setstereopriority value\n");
                printf("\t\t--set Stereo Priority mode\n");

                printf("\t\tdisptest getstereopriority\n");
                printf("\t\t--get stereo priority mode\n");

                printf("\t\tdisptest setaspectratio value\n");
                printf("\t\t--set aspectratio mode\n");

                printf("\t\tdisptest getaspectratio\n");
                printf("\t\t--get aspectratio mode\n");

                printf("\t\tdisptest setaspectcvrs value\n");
                printf("\t\t--set aspectcvrs mode\n");

                printf("\t\tdisptest getaspectcvrs\n");
                printf("\t\t--get aspectcvrs mode\n");

                printf("\t\tdisptest setsaveparam\n");
                printf("\t\t--set saveparam\n");

                printf("\t\tdisptest setoutputenable port enable\n");
                printf("\t\t--enable output port or not\n");
                printf("\t\t--port: 0->HDMI, 1->CVBS\n");
                printf("\t\t--enable: 0->disabled (close this port), 1->enabled (open this port)\n");

                printf("\t\tdisptest getoutputenable port\n");
                printf("\t\t--get output port enable status\n");
                printf("\t\t--port: 0->HDMI, 1->CVBS\n");
            }
            else if(0==strncmp("gethdmicap",argv[1],sizeof("gethdmicap")))
            {
                Parcel pl;
                ret = disp.GetDisplayCapability(&pl);
                if(ret != -1)
                {
                    printf("=========get hdmi cap ========\n");
                    int butt = DISP_ENC_FMT_BUTT > CAP_CHAR_SIZE? DISP_ENC_FMT_BUTT:CAP_CHAR_SIZE;
                    int cnt = (DISP_ENC_FMT_4096X2160_60 - DISP_ENC_FMT_3840X2160_24 + 1)
                            + (DISP_ENC_FMT_1080i_59_94 - DISP_ENC_FMT_3840X2160_23_976 + 1);
                    for(int i =0;i< CAP_CHAR_SIZE;i++)
                    {
                        if (i > DISP_ENC_FMT_VESA_2560X1600_60_RB + 1 + cnt)
                        {
                            break;
                        }
                        printf("\t\t%s\t=%d\n",FmtCharTable[i], pl.readInt32());
                    }
                }
                else
                {
                    printf("=========get hdmi cap failed !========\n");
                }
            }
            else if(0==strncmp("getmacrovision",argv[1],sizeof("getmacrovision")))
            {
                ret = disp.GetMacroVision();
                printf("=========get macrovision = %d========\n",ret);
            }
            else if(0==strncmp("gethdcp",argv[1],sizeof("gethdcp")))
            {
                ret = disp.GetHdcp();
                printf("=========get hdcp = %d========\n",ret);
            }
            else if(0==strncmp("getfmt",argv[1],sizeof("getfmt")))
            {
                ret = disp.GetEncFmt();
                printf("=========get fmt = %d========\n",ret);
            }
            else if(0==strncmp("getbright",argv[1],sizeof("getbright")))
            {
                ret = disp.GetBrightness();
                printf("=========get brightness = %d========\n",ret);
            }
            else if(0==strncmp("getcontrast",argv[1],sizeof("getcontrast")))
            {
                ret = disp.GetContrast();
                printf("=========get contrast = %d========\n",ret);
            }
            else if(0==strncmp("getsaturation",argv[1],sizeof("getsaturation")))
            {
                ret = disp.GetSaturation();
                printf("=========get saturation = %d========\n",ret);
            }
            else if(0==strncmp("gethue",argv[1],sizeof("gethue")))
            {
                ret = disp.GetHuePlus();
                printf("=========get hue= %d========\n",ret);
            }
            else if(0==strncmp("getrange",argv[1],sizeof("getrange")))
            {
                Rect rect;
                disp.GetOutRange(&(rect.left),&(rect.top),&(rect.right),&(rect.bottom));
                printf("=========get range left = %d top = %d width = %d height = %d========\n",
                        rect.left,rect.top,rect.right,rect.bottom);
            }
            else if(0==strncmp("getstereooutmode",argv[1],sizeof("getstereooutmode")))
            {
                ret = disp.GetStereoOutMode();
                printf("=========get stereo out mode = %d========\n",ret);
            }
            else if(0==strncmp("getstereopriority",argv[1],sizeof("getstereopriority")))
            {
                ret = disp.GetRightEyeFirst();
                printf("=========get stereo priority = %d========\n",ret);
            }
            else if(0==strncmp("getaspectratio",argv[1],sizeof("getaspectratio")))
            {
                ret = disp.GetAspectRatio();
                printf("=========get aspectratio = %d========\n",ret);
            }
            else if(0==strncmp("getaspectcvrs",argv[1],sizeof("getaspectcvrs")))
            {
                ret = disp.GetAspectCvrs();
                printf("=========get aspectcvrs = %d========\n",ret);
            }
            else if(0 == strncmp("setsaveparam",argv[1],sizeof("setsaveparam")))
            {
                ret = disp.SaveParam();
                if(ret != 0)
                {
                    printf("=========save baseparam failed !========\n");
                }
            }
            else
            {
                printf("disptest --help\n");
            }
        }
    }
    else
    {
        if(0==strncmp("setrange",argv[1],sizeof("setrange")))
        {
            if(argc >= 6)
            {
                ret = disp.SetOutRange(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
                if(ret != 0)
                {
                    printf("=========set outrange failed !========\n");
                }
            }
        }
        else if(0==strncmp("setfmt",argv[1],sizeof("setfmt")))
        {
            ret = disp.SetEncFmt(atoi(argv[2]));
            if(ret != 0)
            {
                printf("=========set fmt failed !========\n");
            }
        }
        else if(0==strncmp("setbright",argv[1],sizeof("setbright")))
        {
            ret = disp.SetBrightness(atoi(argv[2]));
            if(ret != 0)
            {
                printf("=========set brightness failed !========\n");
            }
        }
        else if(0==strncmp("setmacrovision",argv[1],sizeof("setmacrovision")))
        {
            ret = disp.SetMacroVision(atoi(argv[2]));
            if(ret != 0)
            {
                printf("=========set macrovision failed !========\n");
            }
        }

        else if(0==strncmp("setcontrast",argv[1],sizeof("setcontrast")))
        {
            ret = disp.SetContrast(atoi(argv[2]));
            if(ret != 0)
            {
                printf("=========set contrast failed !========\n");
            }
        }
        else if(0==strncmp("setsaturation",argv[1],sizeof("setsaturation")))
        {
            ret = disp.SetSaturation(atoi(argv[2]));
            if(ret != 0)
            {
                printf("=========set saturation failed !========\n");
            }
        }
        else if(0==strncmp("sethue",argv[1],sizeof("sethue")))
        {
            ret = disp.SetHuePlus(atoi(argv[2]));
            if(ret != 0)
            {
                printf("=========set hue failed !========\n");
            }
        }
        else if(0 == strncmp("sethdcp",argv[1],sizeof("sethdcp")))
        {
            ret = disp.SetHdcp((bool)atoi(argv[2]));

            if(ret != 0)
            {
                printf("=========set Hdcp failed !========\n");
            }
        }
        else if(0 == strncmp("setstereooutmode",argv[1],sizeof("setstereooutmode")))
        {
            if(argc >= 3)
            {
                ret = disp.SetStereoOutMode(atoi(argv[2]), atoi(argv[3]));
                if(ret != 0) printf("=========set Stereo Out Mode failed !========\n");
            }
        }
        else if(0 == strncmp("setstereopriority",argv[1],sizeof("setstereopriority")))
        {
            ret = disp.SetRightEyeFirst(atoi(argv[2]));

            if(ret != 0)
            {
                printf("=========set Stereo Priority failed !========\n");
            }
        }
        else if(0==strncmp("setaspectratio",argv[1],sizeof("setaspectratio")))
        {
            ret = disp.SetAspectRatio(atoi(argv[2]));
            printf("=========set aspectratio = %d========\n",ret);
        }
        else if(0==strncmp("setaspectcvrs",argv[1],sizeof("setaspectcvrs")))
        {
            ret = disp.SetAspectCvrs(atoi(argv[2]));
            printf("=========set aspectcvrs = %d========\n",ret);
        }
        else if(0 == strncmp("setoutputenable",argv[1],sizeof("setoutputenable")))
        {
            if(argc >= 3)
            {
                ret = disp.SetOutputEnable(atoi(argv[2]), atoi(argv[3]));
                if(ret != 0) printf("=========enable output port or not failed !========\n");
            }
        }
        else if(0==strncmp("getoutputenable",argv[1],sizeof("getoutputenable")))
        {
            ret = disp.GetOutputEnable(atoi(argv[2]));
            printf("=========get output port enable status = %d========\n",ret);
        }
        else
        {
            printf("no such cmd !\n");
        }
    }
    return 0;
}
