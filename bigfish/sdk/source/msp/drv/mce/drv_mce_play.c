#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/stddef.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/relay.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/cpu.h>
#include <linux/splice.h>
#include <asm/io.h>
#include <mach/platform.h>
#include <mach/hardware.h>
#include <asm/memory.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/fs.h>
#include <linux/time.h>
#include <linux/sched.h>

#include "hi_kernel_adapt.h"

#include "drv_mce_avplay.h"
#include "drv_base_ext_k.h"
#include "hi_drv_mmz.h"
#include "drv_i2c_ext.h"
#include "drv_gpio_ext.h"
#include "drv_gpioi2c_ext.h"
#include "drv_tuner_ext.h"
#include "hi_drv_tuner.h"
#include "drv_demux_ext.h"
#include "drv_base_ext_k.h"
#include "drv_vdec_ext.h"
#include "drv_win_ext.h"
#include "drv_disp_ext.h"
#include "drv_sync_ext.h"
#include "drv_vfmw_ext.h"
#include "drv_tde_ext.h"
#include "hi_drv_file.h"
#include "drv_adec_ext.h"
#include "drv_adsp_ext.h"
#include "drv_ao_ext.h"
#include "drv_hdmi_ext.h"
#include "drv_hifb_ext.h"
#include "hi_drv_mce.h"
#include "drv_media_mem.h"
#include "drv_mce_boardcfg.h"
#include "drv_vpss_ext.h"
#include "hi_drv_pdm.h"
#include "hi_drv_gpioi2c.h"
#include "drv_pq_ext.h"



#define MCE_DMX_ID              0
#define MCE_DMX_TS_PORT         0
#define MCE_DMX_DVB_PORT        0
#define MCE_GET_TS_LEN          (188*50)
#define MCE_GET_ES_LEN          (16*1024)

#define MCE_LOCK(pMutex)    \
    do{ \
        if(down_interruptible(pMutex))  \
        {       \
            HI_ERR_MCE("ERR: mce lock err!\n"); \
        }       \
    }while(0)

#define MCE_UNLOCK(pMutex)    \
    do{ \
        up(pMutex); \
    }while(0)

extern MCE_S   g_Mce;

HI_S32 MCE_Init(HI_VOID);
HI_S32 MCE_DeInit(HI_VOID);

HI_U32 MCE_GetCurTime(HI_VOID)
{
    HI_U64   SysTime;

    SysTime = sched_clock();

    do_div(SysTime, 1000000);

    return (HI_U32)SysTime;
}

HI_VOID MCE_TransFomat(HI_UNF_ENC_FMT_E enSrcFmt, HI_UNF_ENC_FMT_E *penHdFmt, HI_UNF_ENC_FMT_E *penSdFmt)
{
    switch(enSrcFmt)
    {
        /* bellow are tv display formats */
        case HI_UNF_ENC_FMT_1080P_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_1080P_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_1080P_50:
        {
            *penHdFmt = HI_UNF_ENC_FMT_1080P_50;
            *penSdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }
        case HI_UNF_ENC_FMT_1080i_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_1080i_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_1080i_50:
        {
            *penHdFmt = HI_UNF_ENC_FMT_1080i_50;
            *penSdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }
        case HI_UNF_ENC_FMT_720P_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_720P_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_720P_50:
        {
            *penHdFmt = HI_UNF_ENC_FMT_720P_50;
            *penSdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }
        case HI_UNF_ENC_FMT_576P_50:
        {
            *penHdFmt = HI_UNF_ENC_FMT_576P_50;
            *penSdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }
        case HI_UNF_ENC_FMT_480P_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_480P_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_PAL:
        {
            *penHdFmt = HI_UNF_ENC_FMT_PAL;
            *penSdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }
        case HI_UNF_ENC_FMT_NTSC:
        {
            *penHdFmt = HI_UNF_ENC_FMT_NTSC;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }

        /* bellow are vga display formats */
        case HI_UNF_ENC_FMT_861D_640X480_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_861D_640X480_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_800X600_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_800X600_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1024X768_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1024X768_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1280X720_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1280X720_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1280X800_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1280X800_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1280X1024_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1280X1024_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1360X768_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1360X768_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1366X768_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1366X768_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1400X1050_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1400X1050_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1440X900_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1440X900_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1440X900_60_RB:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1440X900_60_RB;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1600X900_60_RB:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1600X900_60_RB;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1600X1200_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1600X1200_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1680X1050_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1680X1050_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }

        case HI_UNF_ENC_FMT_VESA_1920X1080_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1920X1080_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_1920X1200_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_1920X1200_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        case HI_UNF_ENC_FMT_VESA_2048X1152_60:
        {
            *penHdFmt = HI_UNF_ENC_FMT_VESA_2048X1152_60;
            *penSdFmt = HI_UNF_ENC_FMT_NTSC;
            break;
        }
        default:
        {
            *penHdFmt = HI_UNF_ENC_FMT_1080i_50;
            *penSdFmt = HI_UNF_ENC_FMT_PAL;
            break;
        }
    }

    return;
}

HI_S32 MCE_TransToNewWin(HI_HANDLE hOldWin, HI_HANDLE hNewWin)
{
    HI_S32                          Ret = HI_SUCCESS;
    HI_DRV_WIN_INFO_S          stOldWinInfo;
    HI_DRV_WIN_INFO_S          stNewWinInfo;
    HI_DRV_VIDEO_FRAME_S       stCapPic;

    Ret = HI_DRV_WIN_GetInfo(hOldWin, &stOldWinInfo);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_GetInfo \n");
        return Ret;
    }

    Ret = HI_DRV_WIN_GetInfo(hNewWin, &stNewWinInfo);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_GetInfo \n");
        return Ret;
    }

    if ((HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE == stOldWinInfo.eType)
        && (HI_DRV_WIN_ACTIVE_MAIN_AND_SLAVE == stNewWinInfo.eType))
    {
        memset(&stCapPic, 0, sizeof(stCapPic));

        Ret = HI_DRV_WIN_CapturePicture(stOldWinInfo.hPrim, &stCapPic);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_CapturePicture \n");
            return Ret;
        }

        Ret = HI_DRV_WIN_SendFrame(stNewWinInfo.hPrim, &stCapPic);
        (HI_VOID)HI_DRV_WIN_CapturePictureRelease(stOldWinInfo.hPrim, &stCapPic);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_SendFrame \n");
            return Ret;
        }

        memset(&stCapPic, 0, sizeof(stCapPic));

        Ret = HI_DRV_WIN_CapturePicture(stOldWinInfo.hSec, &stCapPic);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_CapturePicture \n");
            return Ret;
        }

        Ret = HI_DRV_WIN_SendFrame(stNewWinInfo.hSec, &stCapPic);
        (HI_VOID)HI_DRV_WIN_CapturePictureRelease(stOldWinInfo.hSec, &stCapPic);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_SendFrame \n");
            return Ret;
        }

        #if 0
        Ret = HI_DRV_WIN_SetZorder(stNewWinInfo.hPrim, HI_DRV_DISP_ZORDER_MOVETOP);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_SetZorder \n");
            return Ret;
        }

        Ret = HI_DRV_WIN_SetZorder(stNewWinInfo.hSec, HI_DRV_DISP_ZORDER_MOVETOP);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_SetZorder \n");
            return Ret;
        }
        #endif
    }
    else if((HI_DRV_WIN_ACTIVE_SINGLE == stOldWinInfo.eType)
        && (HI_DRV_WIN_ACTIVE_SINGLE == stNewWinInfo.eType))
    {
        memset(&stCapPic, 0, sizeof(stCapPic));

        Ret = HI_DRV_WIN_CapturePicture(stOldWinInfo.hPrim, &stCapPic);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_CapturePicture \n");
            return Ret;
        }

        Ret = HI_DRV_WIN_SendFrame(stNewWinInfo.hPrim, &stCapPic);
        (HI_VOID)HI_DRV_WIN_CapturePictureRelease(stOldWinInfo.hPrim, &stCapPic);
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_WIN_SendFrame \n");
            return Ret;
        }
    }
    else
    {
        HI_ERR_MCE("ERR: MCE and New APP is not the same homologous mode! \n");
    }

    return Ret;
}

HI_S32 MCE_ADP_DispOpen(HI_DISP_PARAM_S stDispParam)
{
    HI_S32    Ret = HI_SUCCESS;
    HI_U32    i = 0;

    Ret = HI_DRV_DISP_Open(HI_UNF_DISPLAY1);
    Ret |= HI_DRV_DISP_Open(HI_UNF_DISPLAY0);

    /*open hdmi according to base param*/
    for (i = 0; i < HI_UNF_DISP_INTF_TYPE_BUTT; i++)
    {
        if ((g_Mce.stDispParam.stIntf[i].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI)
            && (g_Mce.stDispParam.stIntf[i].unIntf.enHdmi != HI_UNF_HDMI_ID_BUTT))
        {
                Ret |= HI_DRV_HDMI_Open(g_Mce.stDispParam.stIntf[i].unIntf.enHdmi);
        }
    }

    return Ret;
}

HI_S32 MCE_ADP_DispClose(HI_VOID)
{
    HI_S32        Ret = HI_SUCCESS;
    HI_U32        i = 0;

    /*close hdmi according to base param*/
    for (i = 0; i < HI_UNF_DISP_INTF_TYPE_BUTT; i++)
    {
        if ((g_Mce.stDispParam.stIntf[i].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI)
            && (g_Mce.stDispParam.stIntf[i].unIntf.enHdmi != HI_UNF_HDMI_ID_BUTT))
        {
                Ret |= HI_DRV_HDMI_Close(g_Mce.stDispParam.stIntf[i].unIntf.enHdmi);
        }
    }

    Ret |= HI_DRV_DISP_Close(HI_UNF_DISPLAY0);

    Ret |= HI_DRV_DISP_Close(HI_UNF_DISPLAY1);

    return Ret;
}

HI_S32 MCE_ADP_VoOpen(HI_VOID)
{
    HI_S32      Ret = HI_SUCCESS;

    //Ret = HI_DRV_VO_SetDevMode(HI_UNF_VO_DEV_MODE_NORMAL);

    return Ret;
}

HI_S32 MCE_ADP_VoClose(HI_VOID)
{
    //HI_S32      Ret;

    //Ret = HI_DRV_VO_Close(HI_UNF_DISPLAY1);

    return HI_SUCCESS;
}

HI_S32 MCE_ADP_VoCreateWin(HI_HANDLE *phWin)
{
    HI_S32                  Ret;
    HI_DRV_WIN_ATTR_S    WinAttr;

    memset(&WinAttr, 0x0, sizeof(HI_DRV_WIN_ATTR_S));
    WinAttr.enDisp = HI_UNF_DISPLAY1;
    WinAttr.bVirtual = HI_FALSE;
    WinAttr.stCustmAR.u32ARh = 0;
    WinAttr.stCustmAR.u32ARw = 0;
    WinAttr.enARCvrs = HI_DRV_ASP_RAT_MODE_FULL;
    WinAttr.stInRect.s32X = 0;
    WinAttr.stInRect.s32Y = 0;
    WinAttr.stInRect.s32Width = 1920;
    WinAttr.stInRect.s32Height = 1080;

    Ret = HI_DRV_WIN_Create(&WinAttr, phWin);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_Create\n");
    }

    return Ret;
}

#ifdef HI_FRONTEND_SUPPORT
HI_S32 MCE_ADP_DmxAttachTunerPort(HI_U32 DmxId, HI_U32 PortId)
{
    HI_S32                      Ret;
    HI_U32                      DrvDmxAttachPort;
    HI_UNF_DMX_PORT_E           UnfDmxAttachPort;
    HI_UNF_TUNER_ATTR_S         TunerAttr;
    HI_UNF_DMX_PORT_ATTR_S      DmxAttachPortAttr;
    
    GET_TUNER_CONFIG(TunerAttr);

    if(HI_UNF_TUNER_SIG_TYPE_SAT == TunerAttr.enSigType)
    {
        UnfDmxAttachPort = HI_DEMUX_PORT;
        DrvDmxAttachPort = UnfDmxAttachPort - HI_UNF_DMX_PORT_TSI_0;
        
        HI_DRV_DMX_TunerPortGetAttr(DrvDmxAttachPort, &DmxAttachPortAttr);

        switch (UnfDmxAttachPort)
        {
        case HI_UNF_DMX_PORT_TSI_0:
        default:
            DmxAttachPortAttr.enPortType = HI_TSI0_TYPE;
            DmxAttachPortAttr.u32SerialBitSelector = HI_TSI0_BIT_SELECTOR;
            DmxAttachPortAttr.u32TunerInClk = HI_TSI0_CLK_PHASE_REVERSE;
            break;
        case HI_UNF_DMX_PORT_TSI_1:
            DmxAttachPortAttr.enPortType = HI_TSI1_TYPE;
            DmxAttachPortAttr.u32SerialBitSelector = HI_TSI1_BIT_SELECTOR;
            DmxAttachPortAttr.u32TunerInClk = HI_TSI1_CLK_PHASE_REVERSE;
            break;
        case HI_UNF_DMX_PORT_TSI_2:
            DmxAttachPortAttr.enPortType = HI_TSI2_TYPE;
            DmxAttachPortAttr.u32SerialBitSelector = HI_TSI2_BIT_SELECTOR;
            DmxAttachPortAttr.u32TunerInClk = HI_TSI2_CLK_PHASE_REVERSE;
            break;
        case HI_UNF_DMX_PORT_TSI_3:
            DmxAttachPortAttr.enPortType = HI_TSI3_TYPE;
            DmxAttachPortAttr.u32SerialBitSelector = HI_TSI3_BIT_SELECTOR;
            DmxAttachPortAttr.u32TunerInClk = HI_TSI3_CLK_PHASE_REVERSE;
            break;
        case HI_UNF_DMX_PORT_TSI_4:
            DmxAttachPortAttr.enPortType = HI_TSI4_TYPE;
            DmxAttachPortAttr.u32SerialBitSelector = HI_TSI4_BIT_SELECTOR;
            DmxAttachPortAttr.u32TunerInClk = HI_TSI4_CLK_PHASE_REVERSE;
            break;
        case HI_UNF_DMX_PORT_TSI_5:
            DmxAttachPortAttr.enPortType = HI_TSI5_TYPE;
            DmxAttachPortAttr.u32SerialBitSelector = HI_TSI5_BIT_SELECTOR;
            DmxAttachPortAttr.u32TunerInClk = HI_TSI5_CLK_PHASE_REVERSE;
            break;
        }
        
        HI_DRV_DMX_TunerPortSetAttr(DrvDmxAttachPort, &DmxAttachPortAttr);

        Ret = HI_DRV_DMX_AttachTunerPort(MCE_DMX_ID, DrvDmxAttachPort);
        if(HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_DMX_AttachTunerPort!\n");
            return HI_FAILURE;
        }    
    }
    else
    {
        Ret = HI_DRV_DMX_AttachTunerPort(MCE_DMX_ID, MCE_DMX_DVB_PORT);
        if(HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_DMX_AttachTunerPort!\n");
            return HI_FAILURE;
        }        
    }

    return HI_SUCCESS;   
}
#endif

#ifdef HI_FRONTEND_SUPPORT
HI_S32 MCE_ADP_TunerConnect(HI_UNF_MCE_DVB_PARAM_S stParam)
{
    HI_S32                              Ret;
    HI_UNF_TUNER_ATTR_S                 stAttr;
    HI_UNF_TUNER_SAT_ATTR_S             stSatTunerAttr;
    HI_UNF_TUNER_TSOUT_SET_S            stTsOut;

    Ret = HI_DRV_TUNER_GetDeftAttr(TUNER_USE, &stAttr);
    GET_TUNER_CONFIG(stAttr);
    Ret |= HI_DRV_TUNER_SetAttr(TUNER_USE, &stAttr);

    if (HI_UNF_TUNER_SIG_TYPE_SAT == stAttr.enSigType)
    {
    #if (HI_TUNER_SIGNAL_TYPE == 2)
        GET_SAT_TUNER_CONFIG(stSatTunerAttr);
    #endif
        Ret |= HI_DRV_TUNER_SetSatAttr(TUNER_USE, &stSatTunerAttr);

        Ret |= HI_DRV_TUNER_SetLNBConfig(TUNER_USE, &stParam.stLnbCfg);

        Ret |= HI_DRV_TUNER_SetLNBPower(TUNER_USE, stParam.enLNBPower);

        Ret |= HI_DRV_TUNER_DISEQC_Switch16Port(TUNER_USE, &stParam.st16Port);

        Ret |= HI_DRV_TUNER_DISEQC_Switch4Port(TUNER_USE, &stParam.st4Port);

        Ret |= HI_DRV_TUNER_Switch22K(TUNER_USE, stParam.enSwitch22K);

     #ifdef HI_TUNER_OUTPUT_PIN0
        GET_TUNER_TSOUT_CONFIG(stTsOut);
    
        Ret |= HI_DRV_TUNER_SetTsOut(TUNER_USE, &stTsOut);
	 #endif
    }

    Ret |= HI_DRV_TUNER_Connect(TUNER_USE, &stParam.stConnectPara, 0);

    return Ret;
}
#endif

HI_S32 MCE_TsThread(HI_VOID *args)
{
    HI_S32                          Ret;
    DMX_DATA_BUF_S                  StreamBuf;
    HI_U32                          TotalLen = 0;
    HI_U32                          ReadLen = 0;
    HI_U32                          CycleCount = 0;
    HI_BOOL                         bSendEnd = HI_FALSE;
    HI_BOOL                         bIsEmpty = HI_FALSE;
    MCE_S                           *pMce;

    pMce = (MCE_S *)args;

    while(!pMce->bTsThreadStop)
    {    
        if (bSendEnd)
        {            
            Ret = HI_DRV_AVPLAY_IsBufEmpty(pMce->hAvplay, &bIsEmpty);
            if (HI_SUCCESS == Ret)
            {
                if (HI_TRUE == bIsEmpty)
                {
                    pMce->playEnd = HI_TRUE;   
                }
            }

            msleep(50);
            continue;
        }

        Ret = HI_DRV_DMX_GetTSBuffer(MCE_DMX_TS_PORT, MCE_GET_TS_LEN, &StreamBuf, 1000);
        if(HI_SUCCESS != Ret)
        {
            msleep(10);
            continue;
        }

        if(TotalLen + MCE_GET_TS_LEN < pMce->stMceParam.u32PlayDataLen)
        {
            ReadLen = MCE_GET_TS_LEN;
            memcpy((HI_U8 *)StreamBuf.BufKerAddr, (HI_U8 *)(pMce->u32PlayDataAddr + TotalLen), ReadLen);
            TotalLen += ReadLen;
        }
        else
        {
            ReadLen = pMce->stMceParam.u32PlayDataLen - TotalLen;
            memcpy((HI_U8 *)StreamBuf.BufKerAddr, (HI_U8 *)(pMce->u32PlayDataAddr + TotalLen), ReadLen);
            TotalLen = 0;
            CycleCount++;
        }

        Ret = HI_DRV_DMX_PutTSBuffer(MCE_DMX_TS_PORT, ReadLen, 0);
        if(HI_SUCCESS != Ret)
        {
            HI_ERR_MCE("ERR: HI_DRV_DMX_PutTSBuffer\n");
        }

        if (HI_UNF_MCE_PLAYCTRL_BY_COUNT == pMce->stStopParam.enCtrlMode)
        {
            if (CycleCount >= pMce->stStopParam.u32PlayCount)
            {
            	HI_DRV_AVPLAY_FlushStream(pMce->hAvplay);
                bSendEnd = HI_TRUE;
            }
        }
    }

    Ret = HI_DRV_DMX_ResetTSBuffer(MCE_DMX_TS_PORT);

    return Ret;
}

HI_UNF_VCODEC_TYPE_E MCE_VedioTypeConvert(HI_UNF_MCE_VDEC_TYPE_E enMceType)
{
    HI_UNF_VCODEC_TYPE_E enVdecType;

    switch (enMceType)
    {
        case HI_UNF_MCE_VDEC_TYPE_MPEG2:
            enVdecType = HI_UNF_VCODEC_TYPE_MPEG2;
            break;

        case HI_UNF_MCE_VDEC_TYPE_MPEG4:
            enVdecType = HI_UNF_VCODEC_TYPE_MPEG4;
            break;

        case HI_UNF_MCE_VDEC_TYPE_H264:
            enVdecType = HI_UNF_VCODEC_TYPE_H264;
            break;

        case HI_UNF_MCE_VDEC_TYPE_AVS:
            enVdecType = HI_UNF_VCODEC_TYPE_AVS;
            break;

        default:
            enVdecType = HI_UNF_VCODEC_TYPE_MPEG2;
            break;
    }

    return enVdecType;
}

static HI_S32 MCE_SetVolume(HI_UNF_SND_E enSound, HI_UNF_SND_ATTR_S *pstAttr, HI_U32 u32Volume)
{
    HI_U8 ii = 0;
    HI_U8 jj = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_UNF_SND_GAIN_ATTR_S stGainAttr;
    HI_UNF_PDM_SOUND_PARAM_S stSoundParam;
    HI_BOOL bVolumeExistInBase = HI_FALSE;

    memset(&stSoundParam, 0, sizeof(stSoundParam));
    s32Ret = HI_DRV_PDM_GetSoundParamEx(enSound, &stSoundParam, &bVolumeExistInBase);
    if ((HI_SUCCESS == s32Ret) && (bVolumeExistInBase))
    {
        for (ii = 0; ii < pstAttr->u32PortNum && ii < HI_UNF_SND_OUTPUTPORT_MAX; ii++)
        {
            for (jj = 0; jj < stSoundParam.u32PortNum; jj++)
            {
                if (pstAttr->stOutport[ii].enOutPort == stSoundParam.stOutport[jj].enOutPort)
                {
                    break;
                }
            }

            if (jj < stSoundParam.u32PortNum)
            {
                stGainAttr.bLinearMode = HI_TRUE;
                stGainAttr.s32Gain = (HI_S32)stSoundParam.au32Volume[jj];
            }
            else
            {
                stGainAttr.bLinearMode = HI_TRUE;
                stGainAttr.s32Gain = (HI_S32)u32Volume;
            }

            HI_DRV_AO_SND_SetVolume(enSound, pstAttr->stOutport[ii].enOutPort, stGainAttr);
        }
    }
    else
    {
        stGainAttr.bLinearMode = HI_TRUE;
        stGainAttr.s32Gain = (HI_S32)u32Volume;

        for (ii = 0; ii < pstAttr->u32PortNum && ii < HI_UNF_SND_OUTPUTPORT_MAX; ii++)
        {
            HI_DRV_AO_SND_SetVolume(enSound, pstAttr->stOutport[ii].enOutPort, stGainAttr);
        }
    }

    return HI_SUCCESS;
}

HI_S32 MCE_TsPlayStart(MCE_S *pMce)
{
    HI_S32                          Ret;
    HI_UNF_AVPLAY_ATTR_S            AvplayAttr;
    HI_UNF_VCODEC_ATTR_S            VdecAttr;
    HI_UNF_AVPLAY_OPEN_OPT_S        OpenOpt;
    HI_UNF_SYNC_ATTR_S              SyncAttr;
    HI_UNF_MCE_TSFILE_PARAM_S       stParam;
    HI_UNF_SND_ATTR_S               stAttr;
    HI_UNF_AUDIOTRACK_ATTR_S        stTrackAttr;

    stParam = pMce->stMceParam.stPlayParam.unParam.stTsParam;

    Ret = HI_DRV_AO_SND_Init(HI_NULL);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_Init!\n");
        goto ERR0;
    }

    Ret = HI_DRV_AO_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_GetDefaultOpenAttr!\n");
        goto ERR00;
    }

    Ret = HI_DRV_AO_SND_Open(HI_UNF_SND_0, &stAttr, HI_NULL);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_Open!\n");
        goto ERR00;
    }

    if (pMce->stMceParam.stPlayParam.unParam.stTsParam.u32Volume > 100)
    {
        pMce->stMceParam.stPlayParam.unParam.stTsParam.u32Volume = 50;
    }

    Ret = MCE_SetVolume(HI_UNF_SND_0, &stAttr, pMce->stMceParam.stPlayParam.unParam.stTsParam.u32Volume);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_SetVolume!\n");
        goto ERR00;
    }

    Ret = MCE_ADP_DispOpen(pMce->stDispParam);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_DispOpen!\n");
        goto ERR1;
    }

    Ret = MCE_ADP_VoOpen();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_VoOpen!\n");
        goto ERR2;
    }

    Ret = MCE_ADP_VoCreateWin(&pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_VoCreateWin!\n");
        goto ERR3;
    }

    Ret = HI_DRV_DMX_AttachRamPort(MCE_DMX_ID, MCE_DMX_TS_PORT);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_DMX_AttachRamPort!\n");
        goto ERR4;
    }

    Ret = HI_DRV_DMX_CreateTSBuffer(MCE_DMX_TS_PORT, 0x200000, &pMce->TsBuf, HI_NULL);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_DMX_CreateTSBuffer!\n");
        goto ERR5;
    }

    Ret = HI_DRV_DMX_ResetTSBuffer(MCE_DMX_TS_PORT);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_DMX_ResetTSBuffer!\n");
        goto ERR6;
    }

    Ret = HI_DRV_AVPLAY_Init();
    AvplayAttr.u32DemuxId = MCE_DMX_ID;
    AvplayAttr.stStreamAttr.enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_TS;
    AvplayAttr.stStreamAttr.u32VidBufSize = (5*1024*1024);
    AvplayAttr.stStreamAttr.u32AudBufSize = (384*1024);
    Ret |= HI_DRV_AVPLAY_Create(&AvplayAttr, &pMce->hAvplay);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Create!\n");
        goto ERR6;
    }

    Ret = HI_DRV_AVPLAY_ChnOpen(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);

    OpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    OpenOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    OpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;
    Ret |= HI_DRV_AVPLAY_ChnOpen(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &OpenOpt);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_ChnOpen!\n");
        goto ERR7;
    }

    Ret = HI_DRV_AO_Track_GetDefaultOpenAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    Ret |= HI_DRV_AO_Track_Create(HI_UNF_SND_0, &stTrackAttr, HI_FALSE, HI_NULL, &pMce->hSnd);
    Ret |= HI_DRV_AVPLAY_AttachSnd(pMce->hAvplay, pMce->hSnd);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_MPI_AVPLAY_AttachSnd!\n");
        goto ERR8;
    }

    Ret = HI_DRV_AVPLAY_AttachWindow(pMce->hAvplay, pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_AttachWindow!\n");
        goto ERR9;
    }

    Ret = HI_DRV_WIN_SetEnable(pMce->hWindow, HI_TRUE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_SetEnable!\n");
        goto ERR10;
    }


    Ret = HI_DRV_AVPLAY_SetAttr(pMce->hAvplay,HI_UNF_AVPLAY_ATTR_ID_VID_PID, &stParam.u32VideoPid);
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay,HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &stParam.u32AudioPid);

    Ret |= HI_DRV_AVPLAY_GetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);

    Ret |= HI_DRV_AVPLAY_GetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    VdecAttr.enType = MCE_VedioTypeConvert(stParam.enVideoType);
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_SetAttr!\n");
        goto ERR11;
    }

    Ret = HI_DRV_AVPLAY_Start(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Start!\n");
        goto ERR11;
    }

    pMce->BeginTime = MCE_GetCurTime();
    
    pMce->bTsThreadStop = HI_FALSE;
    pMce->pPlayTask = kthread_create(MCE_TsThread, pMce, "HI_MCE_TsPlay");
    if(IS_ERR(pMce->pPlayTask))
    {
        HI_ERR_MCE("ERR: crate thread err!\n");
        goto ERR12;
    }

    wake_up_process(pMce->pPlayTask);

    return Ret;

ERR12:
    HI_DRV_AVPLAY_Stop(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
ERR11:
    HI_DRV_WIN_SetEnable(pMce->hWindow, HI_FALSE);
ERR10:
    HI_DRV_AVPLAY_DetachWindow(pMce->hAvplay, pMce->hWindow);
ERR9:
    HI_DRV_AVPLAY_DetachSnd(pMce->hAvplay, pMce->hSnd);
    HI_DRV_AO_Track_Destroy(pMce->hSnd);
ERR8:
    HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
ERR7:
    HI_DRV_AVPLAY_Destroy(pMce->hAvplay);
    HI_DRV_AVPLAY_DeInit();
ERR6:
    (HI_VOID)HI_DRV_DMX_DestroyTSBuffer(MCE_DMX_TS_PORT);
ERR5:
    (HI_VOID)HI_DRV_DMX_DetachPort(MCE_DMX_ID);
ERR4:
    HI_DRV_WIN_Destroy(pMce->hWindow);
ERR3:
    MCE_ADP_VoClose();
ERR2:
    MCE_ADP_DispClose();
ERR1:
    HI_DRV_AO_SND_Close(HI_UNF_SND_0, HI_NULL);
ERR00:
    HI_DRV_AO_SND_DeInit(HI_NULL);
ERR0:
    return Ret;
}

HI_S32 MCE_AniThread(HI_VOID *args)
{
    HI_S32                          Ret;
    HI_UNF_STREAM_BUF_S             StreamBuf;
    HI_U32                          TotalLen = 0;
    HI_U32                          ReadLen = 0;
    HI_U32                          CycleCount = 0;
    MCE_S                           *pMce;
    HI_UNF_AVPLAY_PUTBUFEX_OPT_S    stExOpt;
    HI_BOOL bStatus;
    HI_U32 u32PicIndex = 0;

    pMce = (MCE_S *)args;
	HI_DRV_AVPLAY_Step(pMce->hAvplay, HI_NULL);
	
    while(!pMce->bAniThreadStop)
    {   
		Ret = HI_DRV_AVPLAY_ProcStatus(pMce->hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, &bStatus);
		if ((HI_SUCCESS == Ret) && (HI_TRUE == bStatus))
		{
			msleep(pMce->stMceParam.stPlayParam.unParam.stAniParam.au32PicTime[u32PicIndex]);
            /* 1.Mce stop/exit operation will occur during the sleep*/
            /* 2.A system crash will occur when the release of resources continue to have access*/
            /* 3.Re-determination condition after wake up.*/
            if (HI_TRUE == pMce->bAniThreadStop)
            {
                break;
            }

			++u32PicIndex;
            if ((u32PicIndex >= pMce->stMceParam.stPlayParam.unParam.stAniParam.u32PicCount)
                || (u32PicIndex >= ANI_MAX_PIC_SUPPORT))
            {
                u32PicIndex = 0;
                CycleCount++;

				if (HI_UNF_MCE_PLAYCTRL_BY_COUNT == pMce->stStopParam.enCtrlMode)
		        {
		            if (CycleCount >= pMce->stStopParam.u32PlayCount)
		            {
		                HI_DRV_AVPLAY_FlushStream(pMce->hAvplay);
		                pMce->playEnd = HI_TRUE;
						continue;
		            }
		        }
            }

			HI_DRV_AVPLAY_Step(pMce->hAvplay, HI_NULL);
        }
        else
        {
            StreamBuf.u32Size = MCE_GET_ES_LEN;
            Ret = HI_DRV_AVPLAY_GetBuf(pMce->hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, MCE_GET_ES_LEN, &StreamBuf, 0);
            if(HI_SUCCESS != Ret)
            {
                msleep(10);
                continue;
            }

            if(TotalLen + MCE_GET_ES_LEN < pMce->stMceParam.u32PlayDataLen)
            {
                ReadLen = MCE_GET_ES_LEN;
                memcpy((HI_U8 *)StreamBuf.pu8Data, (HI_U8 *)(pMce->u32PlayDataAddr + TotalLen), ReadLen);
                TotalLen += ReadLen;
            }
            else
            {
                ReadLen = pMce->stMceParam.u32PlayDataLen - TotalLen;
                memcpy((HI_U8 *)StreamBuf.pu8Data, (HI_U8 *)(pMce->u32PlayDataAddr + TotalLen), ReadLen);
                TotalLen = 0;
            }

            stExOpt.bContinue = HI_TRUE;
            stExOpt.bEndOfFrm = HI_TRUE;

            Ret = HI_DRV_AVPLAY_PutBuf(pMce->hAvplay, HI_UNF_AVPLAY_BUF_ID_ES_VID, ReadLen, 0, &stExOpt);
            if(HI_SUCCESS != Ret)
            {
                HI_ERR_MCE("ERR: HI_DRV_AVPLAY_PutBuf\n");
            }
        }

        if (HI_UNF_MCE_PLAYCTRL_BY_COUNT == pMce->stStopParam.enCtrlMode)
        {
            if (CycleCount >= pMce->stStopParam.u32PlayCount)
            {
                HI_DRV_AVPLAY_FlushStream(pMce->hAvplay);
                pMce->playEnd = HI_TRUE;
            }
        }

    }

    return HI_SUCCESS;
}

HI_S32 MCE_AniPlayStart(MCE_S *pMce)
{
    HI_S32                          Ret;
    HI_UNF_AVPLAY_ATTR_S            AvplayAttr;
    HI_UNF_VCODEC_ATTR_S            VdecAttr;
    HI_UNF_AVPLAY_OPEN_OPT_S        OpenOpt;
    HI_UNF_MCE_ANI_PARAM_S       stParam;

    stParam = pMce->stMceParam.stPlayParam.unParam.stAniParam;

    Ret = MCE_ADP_DispOpen(pMce->stDispParam);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_DispOpen!\n");
        goto ERR1;
    }

    Ret = MCE_ADP_VoOpen();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_VoOpen!\n");
        goto ERR2;
    }

    Ret = MCE_ADP_VoCreateWin(&pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_VoCreateWin!\n");
        goto ERR3;
    }

    Ret = HI_DRV_AVPLAY_Init();
    AvplayAttr.u32DemuxId = MCE_DMX_ID;
    AvplayAttr.stStreamAttr.enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_ES;
    AvplayAttr.stStreamAttr.u32VidBufSize = (5*1024*1024);
    AvplayAttr.stStreamAttr.u32AudBufSize = (384*1024);
    Ret |= HI_DRV_AVPLAY_Create(&AvplayAttr, &pMce->hAvplay);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Create!\n");
        goto ERR4;
    }

    OpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    OpenOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    OpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;
    Ret |= HI_DRV_AVPLAY_ChnOpen(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &OpenOpt);
    Ret |= HI_DRV_AVPLAY_SetProgressive(pMce->hAvplay, HI_TRUE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_ChnOpen!\n");
        goto ERR5;
    }

    Ret = HI_DRV_AVPLAY_AttachWindow(pMce->hAvplay, pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_AttachWindow!\n");
        goto ERR6;
    }

    Ret = HI_DRV_WIN_SetEnable(pMce->hWindow, HI_TRUE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_SetEnable!\n");
        goto ERR7;
    }

    Ret |= HI_DRV_AVPLAY_GetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    VdecAttr.enType = MCE_VedioTypeConvert(HI_UNF_MCE_VDEC_TYPE_H264);
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_SetAttr!\n");
        goto ERR8;
    }

    Ret = HI_DRV_AVPLAY_Start(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Start!\n");
        goto ERR8;
    }

    pMce->BeginTime = MCE_GetCurTime();

    pMce->bAniThreadStop = HI_FALSE;
    pMce->pPlayTask = kthread_create(MCE_AniThread, pMce, "HI_MCE_AniPlay");
    if(IS_ERR(pMce->pPlayTask))
    {
        HI_ERR_MCE("ERR: crate thread err!\n");
        goto ERR9;
    }

    wake_up_process(pMce->pPlayTask);

    return Ret;

ERR9:
    HI_DRV_AVPLAY_Stop(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, HI_NULL);
ERR8:
    HI_DRV_WIN_SetEnable(pMce->hWindow, HI_FALSE);
ERR7:
    HI_DRV_AVPLAY_DetachWindow(pMce->hAvplay, pMce->hWindow);
ERR6:
    HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
ERR5:
    HI_DRV_AVPLAY_Destroy(pMce->hAvplay);
    HI_DRV_AVPLAY_DeInit();
ERR4:
    HI_DRV_WIN_Destroy(pMce->hWindow);
ERR3:
    MCE_ADP_VoClose();
ERR2:
    MCE_ADP_DispClose();
ERR1:
    return Ret;
}

HI_S32 MCE_AniPlayStop(MCE_S *pMce)
{
    HI_UNF_AVPLAY_STOP_OPT_S    stStop;

    if(HI_NULL != pMce->pPlayTask)
    {
        pMce->bAniThreadStop = HI_TRUE;
        kthread_stop(pMce->pPlayTask);
        pMce->pPlayTask = HI_NULL;
    }

    stStop.enMode = pMce->stStopParam.enStopMode;
    stStop.u32TimeoutMs = 0;
    (HI_VOID)HI_DRV_AVPLAY_Stop(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStop);

    return HI_SUCCESS;
}

/*release tsplay resource*/
HI_S32  MCE_AniPlayExit(MCE_S *pMce, HI_UNF_MCE_EXITPARAM_S *pstExitParam)
{
    if (HI_INVALID_HANDLE != pstExitParam->hNewWin)
    {
        (HI_VOID)MCE_TransToNewWin(pMce->hWindow, pstExitParam->hNewWin);
    }

    (HI_VOID)HI_DRV_WIN_SetEnable(pMce->hWindow, HI_FALSE);

    (HI_VOID)HI_DRV_AVPLAY_DetachWindow(pMce->hAvplay, pMce->hWindow);

    (HI_VOID)HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

    (HI_VOID)HI_DRV_AVPLAY_Destroy(pMce->hAvplay);

    (HI_VOID)HI_DRV_AVPLAY_DeInit();

    (HI_VOID)HI_DRV_WIN_Destroy(pMce->hWindow);

    /*still mode, the following resource need not to be released*/
    if (HI_INVALID_HANDLE != pstExitParam->hNewWin)
    {
        return HI_SUCCESS;
    }

    (HI_VOID)MCE_ADP_VoClose();

    return HI_SUCCESS;
}

HI_S32 MCE_TsPlayStop(MCE_S *pMce)
{
    HI_UNF_AVPLAY_STOP_OPT_S    stStop;

    if(HI_NULL != pMce->pPlayTask)
    {
        pMce->bTsThreadStop = HI_TRUE;
        kthread_stop(pMce->pPlayTask);
        pMce->pPlayTask = HI_NULL;
    }

    stStop.enMode = pMce->stStopParam.enStopMode;
    stStop.u32TimeoutMs = 0;
    (HI_VOID)HI_DRV_AVPLAY_Stop(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStop);

    return HI_SUCCESS;
}

/*release tsplay resource*/
HI_S32  MCE_TsPlayExit(MCE_S *pMce, HI_UNF_MCE_EXITPARAM_S *pstExitParam)
{
    if (HI_INVALID_HANDLE != pstExitParam->hNewWin)
    {
        (HI_VOID)MCE_TransToNewWin(pMce->hWindow, pstExitParam->hNewWin);
    }

    (HI_VOID)HI_DRV_WIN_SetEnable(pMce->hWindow, HI_FALSE);

    (HI_VOID)HI_DRV_AVPLAY_DetachWindow(pMce->hAvplay, pMce->hWindow);

    (HI_VOID)HI_DRV_AVPLAY_DetachSnd(pMce->hAvplay, pMce->hSnd);

    (HI_VOID)HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);

    (HI_VOID)HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);

    (HI_VOID)HI_DRV_AVPLAY_Destroy(pMce->hAvplay);

    (HI_VOID)HI_DRV_AVPLAY_DeInit();

    (HI_VOID)HI_DRV_WIN_Destroy(pMce->hWindow);

    (HI_VOID)HI_DRV_DMX_DestroyTSBuffer(MCE_DMX_TS_PORT);

    /*still mode, the following resource need not to be released*/
    if (HI_INVALID_HANDLE != pstExitParam->hNewWin)
    {
        return HI_SUCCESS;
    }

    (HI_VOID)HI_DRV_DMX_DetachPort(MCE_DMX_ID);

    (HI_VOID)MCE_ADP_VoClose();

    /*we can not close display here for smooth trans*/
#if 0
    (HI_VOID)MCE_ADP_DispClose();
#endif

    (HI_VOID)HI_DRV_AO_Track_Destroy(pMce->hSnd);

    HI_DRV_AO_SND_Close(HI_UNF_SND_0, HI_NULL);

    HI_DRV_AO_SND_DeInit(HI_NULL);

    return HI_SUCCESS;
}

#ifdef HI_FRONTEND_SUPPORT
HI_S32 MCE_DvbPlayStart(MCE_S *pMce)
{
    HI_S32                          Ret;
    HI_UNF_AVPLAY_ATTR_S            AvplayAttr;
    HI_UNF_VCODEC_ATTR_S            VdecAttr;
    HI_UNF_AVPLAY_OPEN_OPT_S        OpenOpt;
    HI_UNF_SYNC_ATTR_S              SyncAttr;
    HI_UNF_MCE_DVB_PARAM_S          stParam;
    HI_UNF_SND_ATTR_S               stAttr;
    HI_UNF_AUDIOTRACK_ATTR_S        stTrackAttr;

    stParam = pMce->stMceParam.stPlayParam.unParam.stDvbParam;

    Ret = HI_DRV_TUNER_Open(TUNER_USE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_TUNER_Open!\n");
        goto ERR;
    }

    Ret = MCE_ADP_TunerConnect(stParam);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_TunerConnect!\n");
        goto ERR0;
    }

    Ret = HI_DRV_AO_SND_Init(HI_NULL);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_Init!\n");
        goto ERR0;
    }

    Ret = HI_DRV_AO_SND_GetDefaultOpenAttr(HI_UNF_SND_0,&stAttr);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_GetDefaultOpenAttr!\n");
        goto ERR00;
    }

    Ret = HI_DRV_AO_SND_Open(HI_UNF_SND_0, &stAttr, HI_NULL);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_Open!\n");
        goto ERR00;
    }

    if (pMce->stMceParam.stPlayParam.unParam.stDvbParam.u32Volume > 100)
    {
        pMce->stMceParam.stPlayParam.unParam.stDvbParam.u32Volume = 50;
    }

    Ret = MCE_SetVolume(HI_UNF_SND_0, &stAttr, pMce->stMceParam.stPlayParam.unParam.stDvbParam.u32Volume);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_SetVolume!\n");
        goto ERR00;
    }

    Ret = MCE_ADP_DispOpen(pMce->stDispParam);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_DispOpen!\n");
        goto ERR1;
    }

    Ret = MCE_ADP_VoOpen();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_VO_Open!\n");
        goto ERR2;
    }

    Ret = MCE_ADP_VoCreateWin(&pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_VoCreateWin!\n");
        goto ERR3;
    }

    Ret = MCE_ADP_DmxAttachTunerPort(MCE_DMX_ID, MCE_DMX_DVB_PORT);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_DmxAttachTunerPort!\n");
        goto ERR4;
    }

    Ret = HI_DRV_AVPLAY_Init();
    AvplayAttr.u32DemuxId = MCE_DMX_ID;
    AvplayAttr.stStreamAttr.enStreamType = HI_UNF_AVPLAY_STREAM_TYPE_TS;
    AvplayAttr.stStreamAttr.u32VidBufSize = (5*1024*1024);
    AvplayAttr.stStreamAttr.u32AudBufSize = (384*1024);
    Ret |= HI_DRV_AVPLAY_Create(&AvplayAttr, &pMce->hAvplay);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Create!\n");
        goto ERR5;
    }

    Ret = HI_DRV_AVPLAY_ChnOpen(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD, HI_NULL);
    OpenOpt.enCapLevel = HI_UNF_VCODEC_CAP_LEVEL_FULLHD;
    OpenOpt.enDecType = HI_UNF_VCODEC_DEC_TYPE_NORMAL;
    OpenOpt.enProtocolLevel = HI_UNF_VCODEC_PRTCL_LEVEL_H264;
    Ret |= HI_DRV_AVPLAY_ChnOpen(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID, &OpenOpt);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_ChnOpen!\n");
        goto ERR6;
    }

    Ret = HI_DRV_AO_Track_GetDefaultOpenAttr(HI_UNF_SND_TRACK_TYPE_SLAVE, &stTrackAttr);
    Ret |= HI_DRV_AO_Track_Create(HI_UNF_SND_0, &stTrackAttr, HI_FALSE, HI_NULL, &pMce->hSnd);
    Ret |= HI_DRV_AVPLAY_AttachSnd(pMce->hAvplay, pMce->hSnd);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_MPI_AVPLAY_AttachSnd!\n");
        goto ERR7;
    }

    Ret = HI_DRV_AVPLAY_AttachWindow(pMce->hAvplay, pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_AttachWindow!\n");
        goto ERR8;
    }

    Ret = HI_DRV_WIN_SetEnable(pMce->hWindow, HI_TRUE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_SetEnable!\n");
        goto ERR9;
    }

    Ret = HI_DRV_AVPLAY_SetAttr(pMce->hAvplay,HI_UNF_AVPLAY_ATTR_ID_VID_PID, &stParam.u32VideoPid);
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay,HI_UNF_AVPLAY_ATTR_ID_AUD_PID, &stParam.u32AudioPid);

    Ret |= HI_DRV_AVPLAY_GetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);
    SyncAttr.enSyncRef = HI_UNF_SYNC_REF_AUDIO;
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_SYNC, &SyncAttr);

    Ret |= HI_DRV_AVPLAY_GetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    VdecAttr.enType = MCE_VedioTypeConvert(stParam.enVideoType);
    Ret |= HI_DRV_AVPLAY_SetAttr(pMce->hAvplay, HI_UNF_AVPLAY_ATTR_ID_VDEC, &VdecAttr);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_SetAttr!\n");
        goto ERR10;
    }

    Ret = HI_DRV_AVPLAY_Start(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Start!\n");
        goto ERR10;
    }

    pMce->BeginTime = MCE_GetCurTime();

    return Ret;

ERR10:
    HI_DRV_WIN_SetEnable(pMce->hWindow, HI_FALSE);
ERR9:
    HI_DRV_AVPLAY_DetachWindow(pMce->hAvplay, pMce->hWindow);
ERR8:
    HI_DRV_AVPLAY_DetachSnd(pMce->hAvplay, pMce->hSnd);
    HI_DRV_AO_Track_Destroy(pMce->hSnd);
ERR7:
    HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
ERR6:
    HI_DRV_AVPLAY_Destroy(pMce->hAvplay);
    (HI_VOID)HI_DRV_AVPLAY_DeInit();
ERR5:
    HI_DRV_DMX_DetachPort(MCE_DMX_ID);
ERR4:
    HI_DRV_WIN_Destroy(pMce->hWindow);
ERR3:
    MCE_ADP_VoClose();
ERR2:
    MCE_ADP_DispClose();
ERR1:
    HI_DRV_AO_SND_Close(HI_UNF_SND_0, HI_NULL);
ERR00:
    HI_DRV_AO_SND_DeInit(HI_NULL);
ERR0:
    HI_DRV_TUNER_Close(TUNER_USE);
ERR:
    return Ret;
}

HI_S32 MCE_DvbPlayStop(MCE_S *pMce)
{
    HI_S32                      Ret;
    HI_UNF_AVPLAY_STOP_OPT_S    stStop;

    stStop.enMode = pMce->stStopParam.enStopMode;
    stStop.u32TimeoutMs = 0;
    Ret = HI_DRV_AVPLAY_Stop(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD | HI_UNF_AVPLAY_MEDIA_CHAN_VID, &stStop);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Stop!\n");
        return Ret;
    }

    return HI_SUCCESS;
}

/*release dvbplay resource*/
HI_S32  MCE_DvbPlayExit(MCE_S *pMce, HI_UNF_MCE_EXITPARAM_S *pstExitParam)
{
    HI_S32                      Ret;

//    (HI_VOID)HI_DRV_AVPLAY_GetSyncVdecHandle( pMce->hAvplay, &hVdec, &hSync);

    if (HI_INVALID_HANDLE != pstExitParam->hNewWin)
    {
        (HI_VOID)MCE_TransToNewWin(pMce->hWindow, pstExitParam->hNewWin);
    }

    Ret = HI_DRV_WIN_SetEnable(pMce->hWindow, HI_FALSE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_SetEnable!\n");
        return Ret;
    }

    Ret = HI_DRV_AVPLAY_DetachWindow(pMce->hAvplay, pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_DetachWindow!\n");
        return Ret;
    }

    Ret |= HI_DRV_AVPLAY_DetachSnd(pMce->hAvplay, pMce->hSnd);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_DetachSnd!\n");
        return Ret;
    }

    Ret = HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_AUD);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_ChnClose!\n");
        return Ret;
    }

    Ret = HI_DRV_AVPLAY_ChnClose(pMce->hAvplay, HI_UNF_AVPLAY_MEDIA_CHAN_VID);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_ChnClose!\n");
        return Ret;
    }

    Ret = HI_DRV_AVPLAY_Destroy(pMce->hAvplay);
    Ret|= HI_DRV_AVPLAY_DeInit();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AVPLAY_Destroy!\n");
        return Ret;
    }

    Ret = HI_DRV_WIN_Destroy(pMce->hWindow);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_Destroy!\n");
        return Ret;
    }

    /*still mode, the following resource need not to be released*/
    if (HI_INVALID_HANDLE != pstExitParam->hNewWin)
    {
        return HI_SUCCESS;
    }

    Ret = HI_DRV_TUNER_Close(TUNER_USE);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_TUNER_Close!\n");
        return Ret;
    }

    Ret = HI_DRV_DMX_DetachPort(MCE_DMX_ID);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_DMX_DetachPort!\n");
        return Ret;
    }
    /**/
    Ret = MCE_ADP_VoClose();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_VoClose!\n");
        return Ret;
    }

    /*we can not close display here for smooth trans*/
#if 0
    Ret = MCE_ADP_DispClose();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ADP_DispClose!\n");
        return Ret;
    }
#endif
    Ret = HI_DRV_AO_Track_Destroy(pMce->hSnd);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_Track_Destroy!\n");
        return Ret;
    }

    HI_DRV_AO_SND_Close(HI_UNF_SND_0, HI_NULL);

    HI_DRV_AO_SND_DeInit(HI_NULL);

    return HI_SUCCESS;
}
#endif

HI_BOOL g_bRecvVideoFrame = HI_FALSE;

extern HI_VOID HifbSetLogoLayerEnable(HI_BOOL bEnable);

HI_S32 MCE_StopLogo(HI_VOID *args)
{
    HI_U32      u32Count = 0;

    while (1)
    {
        if (g_bRecvVideoFrame)
        {
            msleep(10);

            break;
        }
        else if (u32Count >= 100)
        {
            break;
        }
        else
        {
            msleep(10);
            u32Count++;
        }
    }

    /* disable logo after vid play start */
    HifbSetLogoLayerEnable(HI_FALSE);

    return HI_SUCCESS;
}

HI_S32 MCE_PlayStart(MCE_S *pMce)
{
    struct task_struct *pStopLogoThread = HI_NULL;
    HI_S32      Ret = HI_SUCCESS;
//  HI_BOOL     bReceivedFirstVidFrm = HI_FALSE;
//  HI_U32      u32WaitStart = 0;

    if(HI_UNF_MCE_TYPE_PLAY_DVB == pMce->stMceParam.stPlayParam.enPlayType)
    {
    #ifdef HI_FRONTEND_SUPPORT
        Ret = MCE_DvbPlayStart(pMce);
    #endif
    }
    else if(HI_UNF_MCE_TYPE_PLAY_TSFILE == pMce->stMceParam.stPlayParam.enPlayType)
    {
        Ret = MCE_TsPlayStart(pMce);
    }
    else if (HI_UNF_MCE_TYPE_PLAY_ANI == pMce->stMceParam.stPlayParam.enPlayType)
    {
        Ret = MCE_AniPlayStart(pMce);
    }

    pStopLogoThread = kthread_create(MCE_StopLogo, HI_NULL, "HI_LOGO_STOP");
    if (!IS_ERR(pStopLogoThread))
    {
        wake_up_process(pStopLogoThread);
    }
    else
    {
        /* disable logo after vid play start */
        HifbSetLogoLayerEnable(HI_FALSE);
    }

    return Ret;
}

HI_S32 MCE_PlayStop(MCE_S *pMce)
{
    HI_S32      Ret;

    if(HI_UNF_MCE_TYPE_PLAY_DVB ==  pMce->stMceParam.stPlayParam.enPlayType)
    {
    #ifdef HI_FRONTEND_SUPPORT
        Ret = MCE_DvbPlayStop(pMce);
    #endif
    }
    else if(HI_UNF_MCE_TYPE_PLAY_TSFILE == pMce->stMceParam.stPlayParam.enPlayType)
    {
        Ret = MCE_TsPlayStop(pMce);

        /*release reserve mem for ts data*/
        HI_DRV_PDM_ReleaseReserveMem("playdata");
    }
    else if (HI_UNF_MCE_TYPE_PLAY_ANI == pMce->stMceParam.stPlayParam.enPlayType)
    {
        Ret = MCE_AniPlayStop(pMce);

        /*release reserve mem for ts data*/
        HI_DRV_PDM_ReleaseReserveMem("playdata");
    }

    return HI_SUCCESS;
}

extern HI_S32 VFMW_DRV_Init(HI_VOID);
extern HI_S32 HI_DRV_PQ_Init(HI_CHAR* pszPath);

HI_S32 MCE_ModuleInit(HI_VOID)
{
#if 1
    HI_S32      Ret;

    Ret = HI_DRV_CommonInit();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_CommonInit!\n");
        return Ret;
    }

    Ret = HI_DRV_I2C_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_I2C_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_GPIO_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_GPIO_Init!\n");
        return Ret;
    }

#ifdef HI_GPIOI2C_SUPPORT
    Ret = HI_DRV_GPIOI2C_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_GPIOI2C_Init!\n");
        return Ret;
    }
#endif

#ifdef HI_FRONTEND_SUPPORT
    Ret = HI_DRV_TUNER_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_TUNER_Init!\n");
        return Ret;
    }
#endif

    Ret = HI_DRV_DMX_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_DMX_Init!\n");
        return Ret;
    }

    Ret = VFMW_DRV_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: VFMW_DRV_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_PDM_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_PDM_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_PQ_Init(HI_NULL);
    if(HI_SUCCESS != Ret)
    {
        HI_WARN_MCE("ERR: HI_DRV_PQ_Init!\n");
    }

    Ret = HI_DRV_VPSS_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_VPSS_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_VDEC_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_VDEC_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_SYNC_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_SYNC_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_HDMI_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_HDMI_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_DISP_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_DISP_Init!\n");
        return Ret;
    }

    Ret = tde_init_module_k();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_TDE_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_WIN_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_WIN_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_ADEC_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_ADEC_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_AO_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_AO_SND_Init!\n");
        return Ret;
    }

    Ret = HI_DRV_ADSP_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: HI_DRV_ADSP_Init!\n");
        return Ret;
    }

    Ret = hifb_init_module_k();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: hifb_init_module_k!\n");
        return Ret;
    }

    return Ret;
#endif
    return HI_SUCCESS;
}

HI_S32 HI_DRV_MCE_Exit(HI_UNF_MCE_EXITPARAM_S *pstExitParam)
{
    HI_S32              Ret = HI_SUCCESS;
    MCE_S               *pMce = &g_Mce;

    if (pMce->bMceExit)
    {
        return HI_SUCCESS;
    }

    if(HI_UNF_MCE_TYPE_PLAY_DVB == pMce->stMceParam.stPlayParam.enPlayType)
    {
    #ifdef HI_FRONTEND_SUPPORT
        Ret = MCE_DvbPlayExit(pMce, pstExitParam);
    #endif
    }
    else if(HI_UNF_MCE_TYPE_PLAY_TSFILE == pMce->stMceParam.stPlayParam.enPlayType)
    {
        Ret = MCE_TsPlayExit(pMce, pstExitParam);
    }
    else if(HI_UNF_MCE_TYPE_PLAY_ANI == pMce->stMceParam.stPlayParam.enPlayType)
    {
        MCE_AniPlayExit(pMce, pstExitParam);
    }

    pMce->bMceExit = HI_TRUE;

    return Ret;
}

HI_S32 HI_DRV_MCE_Stop(HI_UNF_MCE_STOPPARM_S *pstStopParam)
{
    HI_S32              Ret;
    HI_U32              CurTime;
    MCE_S               *pMce = &g_Mce;

    if ((HI_UNF_MCE_TYPE_PLAY_DVB == pMce->stMceParam.stPlayParam.enPlayType)
       && (HI_UNF_MCE_PLAYCTRL_BY_COUNT == pstStopParam->enCtrlMode))
    {
        HI_ERR_MCE("ERR: DVB play type does not support count control mode\n");
        return HI_FAILURE;
    }

    if (pMce->bPlayStop)
    {
        return HI_SUCCESS;
    }

    memcpy(&pMce->stStopParam, pstStopParam, sizeof(HI_UNF_MCE_STOPPARM_S));

    while(1)
    {
        CurTime = MCE_GetCurTime();

        if (HI_UNF_MCE_PLAYCTRL_BY_TIME == pstStopParam->enCtrlMode)
        {
            if (CurTime - pMce->BeginTime > pstStopParam->u32PlayTimeMs)
            {
                break;
            }
        }
        else if (HI_UNF_MCE_PLAYCTRL_BY_COUNT == pstStopParam->enCtrlMode)
        {
            if (pMce->playEnd)
            {
                break;
            }
        }
        else
        {
            break;
        }

        msleep(100);
    }

    pMce->EndTime = MCE_GetCurTime();

    Ret = MCE_PlayStop(pMce);

    pMce->bPlayStop = HI_TRUE;

    return Ret;
}


HI_S32 MCE_Init(HI_VOID)
{
    HI_S32              Ret;
    MCE_S               *pMce = &g_Mce;

    Ret = MCE_ModuleInit();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_ModuleInit\n");
        Ret = HI_FAILURE;
        goto ERR0;
    }

    Ret = HI_DRV_PDM_GetDispParam(HI_UNF_DISPLAY1, &pMce->stDispParam);
    Ret |= HI_DRV_PDM_GetMceParam(&pMce->stMceParam);
    if (0 != pMce->stMceParam.u32PlayDataLen)
    {
        Ret |= HI_DRV_PDM_GetMceData(pMce->stMceParam.u32PlayDataLen, &pMce->u32PlayDataAddr);
    }

    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: get PDM Param\n");
        Ret = HI_FAILURE;
        goto ERR0;
    }

    if ((1 != pMce->stMceParam.u32CheckFlag) || (HI_TRUE != pMce->stMceParam.stPlayParam.bPlayEnable))
    {
        HI_ERR_MCE("mce checkflag is not open\n");
        Ret = HI_FAILURE;
        goto ERR0;
    }

    pMce->bPlayStop = HI_FALSE;
    pMce->bMceExit = HI_FALSE;

    Ret = MCE_PlayStart(pMce);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("ERR: MCE_PlayStart\n");
        Ret = HI_FAILURE;
        goto ERR0;
    }

    return Ret;

ERR0:
    pMce->bMceExit = HI_TRUE;
    return Ret;
}

HI_S32 MCE_DeInit(HI_VOID)
{
    return HI_SUCCESS;
}

#ifndef MODULE
core_initcall(MCE_Init);
//early_initcall(MCE_Init);
#else
#endif

