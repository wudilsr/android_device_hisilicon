#include <linux/kernel.h>
#include <mach/hardware.h>
#include <asm/io.h>

#include "hi_module.h"
#include "hi_drv_module.h"
#include "hi_drv_dev.h"
#include "hi_drv_proc.h"
#include "hi_kernel_adapt.h"

#include "hi_drv_pdm.h"
#include "drv_pdm_ext.h"
#include "drv_pdm.h"
#include "hi_osal.h"

#define PDM_NAME "HI_PDM"

DECLARE_MUTEX(g_PdmMutex);

#define DRV_PDM_Lock() \
    do {         \
        if (down_interruptible(&g_PdmMutex))   \
        {       \
            HI_ERR_PDM("ERR: PDM intf lock error!\n");  \
        }       \
    } while (0)

#define DRV_PDM_UnLock() \
    do {         \
        up(&g_PdmMutex);    \
    } while (0)

typedef struct tagPDM_REGISTER_PARAM_S
{
    DRV_PROC_READ_FN  rdproc;
    DRV_PROC_WRITE_FN wtproc;
} PDM_REGISTER_PARAM_S;

PDM_EXPORT_FUNC_S g_PdmExportFuncs =
{
    .pfnPDM_GetDispParam      = DRV_PDM_GetDispParam,
    .pfnPDM_GetMceParam       = DRV_PDM_GetMceParam,
    .pfnPDM_GetMceData        = DRV_PDM_GetMceData,
    .pfnPDM_ReleaseReserveMem = DRV_PDM_ReleaseReserveMem,
    .pfnPDM_GetData           = DRV_PDM_GetData,
    .pfnGetSoundParam         = DRV_PDM_GetSoundParam
};

PDM_GLOBAL_S g_PdmGlobal;

/*the function to get pdm tag data*/
extern int get_param_data(const char *name, char *buf, unsigned int buflen);

static HI_VOID PDM_ProcDispTiming(struct seq_file *p, HI_UNF_DISP_TIMING_S *pstTiming)
{
    HI_CHAR *DataWith[] =
    {
        "WIDTH8",
        "WIDTH16",
        "WIDTH24"
    };

    PROC_PRINT(p, " ############ Custom Timing begin ##############\n");
    PROC_PRINT(p, "VFB:      		%d   \n",pstTiming->VFB);
    PROC_PRINT(p, "VBB:      		%d   \n",pstTiming->VBB);
    PROC_PRINT(p, "VACT:      		%d   \n",pstTiming->VACT);
    PROC_PRINT(p, "HFB:      		%d   \n",pstTiming->HFB);
    PROC_PRINT(p, "HBB:      		%d   \n",pstTiming->HBB);
    PROC_PRINT(p, "HACT:      		%d   \n",pstTiming->HACT);
    PROC_PRINT(p, "VPW:      		%d   \n",pstTiming->VPW);
    PROC_PRINT(p, "HPW:      		%d   \n",pstTiming->HPW);

    if (pstTiming->IDV)
    {
        PROC_PRINT(p, "IDV:      		%s   \n","true");
    }
    else
    {
        PROC_PRINT(p, "IDV:      		%s   \n","false");
    }

    if (pstTiming->IHS)
    {
        PROC_PRINT(p, "IHS:      		%s   \n","true");
    }
    else
    {
        PROC_PRINT(p, "IHS:      		%s   \n","false");
    }

    if (pstTiming->IVS)
    {
        PROC_PRINT(p, "IVS:      		%s   \n","true");
    }
    else
    {
        PROC_PRINT(p, "IVS:      		%s   \n","false");
    }

    if (pstTiming->ClockReversal)
    {
        PROC_PRINT(p, "ClockReversal:      	%s   \n", "true");
    }
    else
    {
        PROC_PRINT(p, "ClockReversal:      	%s   \n", "false");
    }

    if (pstTiming->DataWidth < HI_UNF_DISP_INTF_DATA_WIDTH_BUTT)
    {
        PROC_PRINT(p, "DataWidth:      	%s   \n", DataWith[pstTiming->DataWidth]);
    }
    else
    {
        PROC_PRINT(p, "DataWidth:      	%d   \n", pstTiming->DataWidth);
    }

    PROC_PRINT(p, "ItfFormat:      	%d   \n", pstTiming->ItfFormat);

    if (pstTiming->DitherEnable)
    {
        PROC_PRINT(p, "DitherEnable:      	%s   \n","true");
    }
    else
    {
        PROC_PRINT(p, "DitherEnable:      	%s   \n","false");
    }

    PROC_PRINT(p, "ClkPara0:      		0x%x   \n",pstTiming->ClkPara0);
    PROC_PRINT(p, "ClkPara1:      		0x%x   \n",pstTiming->ClkPara1);

    if (pstTiming->bInterlace)
    {
        PROC_PRINT(p, "bInterlace:      	%s   \n","true");
    }
    else
    {
        PROC_PRINT(p, "bInterlace:      	%s   \n","false");
    }

    PROC_PRINT(p, "PixFreq:      		%d   \n",pstTiming->PixFreq);
    PROC_PRINT(p, "VertFreq:      		%d   \n",pstTiming->VertFreq);
    PROC_PRINT(p, "AspectRatioW:      	%d   \n",pstTiming->AspectRatioW);
    PROC_PRINT(p, "AspectRatioH:      	%d   \n",pstTiming->AspectRatioH);

    if (pstTiming->bUseGamma)
    {
        PROC_PRINT(p, "UseGamma:      		%s   \n","true");
    }
    else
    {
        PROC_PRINT(p, "UseGamma:      		%s   \n","false");
    }

    PROC_PRINT(p, "Reserve0:      		%d   \n",pstTiming->Reserve0);
    PROC_PRINT(p, "Reserve1:      		%d   \n",pstTiming->Reserve1);
    PROC_PRINT(p, " ############ Custom Timing end ##############\n");
}

static HI_S32 PDM_ProcRead(struct seq_file *p, HI_VOID *v)
{
    HI_DISP_PARAM_S stDispParam;
    HI_UNF_PDM_SOUND_PARAM_S stSoundParam;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 ii = 0, jj = 0;
    HI_CHAR *Aspect[HI_UNF_DISP_ASPECT_RATIO_BUTT] =
    {
        "auto",
        "4to3",
        "16to9",
        "221to1",
        "user"
    };

    HI_CHAR *MClk[] =
    {
        "128*fs",
        "256*fs",
        "384*fs",
        "512*fs",
        "768*fs",
        "1024*fs"
    };

    for (ii = HI_UNF_DISPLAY0; ii < HI_UNF_DISPLAY2; ii++)
    {
        memset(&stDispParam, 0, sizeof(stDispParam));
        s32Ret = DRV_PDM_GetDispParam(HI_UNF_DISPLAY0 + ii, &stDispParam);
        if (HI_SUCCESS == s32Ret)
        {
            PROC_PRINT(p, "---------------------------Dispaly%d------------------------------\n", ii);

            if (stDispParam.enFormat == HI_UNF_ENC_FMT_BUTT)
            {
                PROC_PRINT(p, "format:      		%s   \n","Custom timing");
                PDM_ProcDispTiming(p, &(stDispParam.stDispTiming));
            }
            else
            {
                PROC_PRINT(p, "format:      		%d   \n",stDispParam.enFormat);
            }

            PROC_PRINT(p, "source display:        	%d\n",stDispParam.enSrcDisp);
            PROC_PRINT(p, "background color:      	0x%02x%02x%02x\n",
                       stDispParam.stBgColor.u8Red, stDispParam.stBgColor.u8Green, stDispParam.stBgColor.u8Blue);
            PROC_PRINT(p, "HuePlus/Brightness/Contrast/Saturation: %d/%d/%d/%d\n",
                       stDispParam.u32HuePlus, stDispParam.u32Brightness,
                       stDispParam.u32Contrast, stDispParam.u32Saturation);
            PROC_PRINT(p, "virtual screen(Width/Height):      	%d/%d\n",
                       stDispParam.u32VirtScreenWidth, stDispParam.u32VirtScreenHeight);
            PROC_PRINT(p, "offset(Left/Top/Right/Bottom):      	%d/%d/%d/%d\n",
                       stDispParam.stOffsetInfo.u32Left, stDispParam.stOffsetInfo.u32Top,
                       stDispParam.stOffsetInfo.u32Right, stDispParam.stOffsetInfo.u32Bottom);
            PROC_PRINT(p, "bGammaEnable:      	%d\n",stDispParam.bGammaEnable);
            PROC_PRINT(p, "pixelformat:      	%d\n",stDispParam.enPixelFormat);
            if ((stDispParam.stAspectRatio.enDispAspectRatio != HI_UNF_DISP_ASPECT_RATIO_USER)
                && (stDispParam.stAspectRatio.enDispAspectRatio != HI_UNF_DISP_ASPECT_RATIO_BUTT))
            {
                PROC_PRINT(p, "aspectRatio:      	%s\n",Aspect[stDispParam.stAspectRatio.enDispAspectRatio]);
            }
            else if (stDispParam.stAspectRatio.enDispAspectRatio == HI_UNF_DISP_ASPECT_RATIO_USER)
            {
                PROC_PRINT(p, "aspectRatio:      	%s(%dto%d)\n",Aspect[stDispParam.stAspectRatio.enDispAspectRatio],
                           stDispParam.stAspectRatio.u32UserAspectWidth, stDispParam.stAspectRatio.u32UserAspectHeight);
            }

            for (jj = HI_UNF_DISP_INTF_TYPE_HDMI; jj < HI_UNF_DISP_INTF_TYPE_BUTT; jj++)
            {
                if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI)
                {
                    PROC_PRINT(p, "HDMI:      		HDMI_%d\n",stDispParam.stIntf[jj].unIntf.enHdmi);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_LCD)
                {
                    PROC_PRINT(p, "LCD:      		LCD_%d\n",stDispParam.stIntf[jj].unIntf.enLcd);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_BT1120)
                {
                    PROC_PRINT(p, "BT1120:      		BT1120_%d\n",stDispParam.stIntf[jj].unIntf.enHdmi);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_BT656)
                {
                    PROC_PRINT(p, "BT656:      		BT656_%d\n",stDispParam.stIntf[jj].unIntf.enHdmi);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_YPBPR)
                {
                    PROC_PRINT(p, "YPbPr(Y/Pb/Pr):      	%d/%d/%d\n",stDispParam.stIntf[jj].unIntf.stYPbPr.u8DacY,
									stDispParam.stIntf[jj].unIntf.stYPbPr.u8DacPb, stDispParam.stIntf[jj].unIntf.stYPbPr.u8DacPr);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_RGB)
                {
                    PROC_PRINT(p, "RGB(R/G/B):      	%d/%d/%d\n",stDispParam.stIntf[jj].unIntf.stRGB.u8DacR,
                               stDispParam.stIntf[jj].unIntf.stRGB.u8DacG, stDispParam.stIntf[jj].unIntf.stRGB.u8DacB);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_CVBS)
                {
                    PROC_PRINT(p, "CVBS:      		%d\n",stDispParam.stIntf[jj].unIntf.stCVBS.u8Dac);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_SVIDEO)
                {
                    PROC_PRINT(p, "SVIDEO(Y/C):      	%d/%d\n",stDispParam.stIntf[jj].unIntf.stSVideo.u8DacY,
                               stDispParam.stIntf[jj].unIntf.stSVideo.u8DacC);
                }
                else if (stDispParam.stIntf[jj].enIntfType == HI_UNF_DISP_INTF_TYPE_VGA)
                {
                    PROC_PRINT(p, "VGA(R/G/B):      	%d/%d/%d\n",stDispParam.stIntf[jj].unIntf.stVGA.u8DacR,
                               stDispParam.stIntf[jj].unIntf.stVGA.u8DacG, stDispParam.stIntf[jj].unIntf.stVGA.u8DacB);
                }
            }
        }
    }

    for (ii = HI_UNF_SND_0; ii < HI_UNF_SND_BUTT; ii++)
    {
        HI_BOOL bVolumeExistInBase = HI_FALSE;
        
        memset(&stSoundParam, 0, sizeof(stSoundParam));
        s32Ret = HI_DRV_PDM_GetSoundParamEx(HI_UNF_SND_0 + ii, &stSoundParam, &bVolumeExistInBase);
        if (
            (HI_SUCCESS == s32Ret)
            && (stSoundParam.u32PortNum <= sizeof(stSoundParam.stOutport) / sizeof(stSoundParam.stOutport[0]))
        )
        {
            PROC_PRINT(p, "---------------------------Sound%d------------------------------\n", ii);
            for (jj = 0; jj < stSoundParam.u32PortNum; jj++)
            {
                if (stSoundParam.stOutport[jj].enOutPort == HI_UNF_SND_OUTPUTPORT_DAC0)
                {
                    if (bVolumeExistInBase)
                    {
                        PROC_PRINT(p, "DAC:      			%s       VOL:%3d\n", "DAC0", stSoundParam.au32Volume[jj]);
                    }
                    else
                    {
                        PROC_PRINT(p, "DAC:      			%s\n", "DAC0");
                    }
                }

                if (stSoundParam.stOutport[jj].enOutPort == HI_UNF_SND_OUTPUTPORT_SPDIF0)
                {
                    if (bVolumeExistInBase)
                    {
                        PROC_PRINT(p, "SPDIF:      			%s     VOL:%3d\n", "SPDIF0", stSoundParam.au32Volume[jj]);
                    }
                    else
                    {
                        PROC_PRINT(p, "SPDIF:      			%s\n", "SPDIF0");
                    }
                    
                }

                if (stSoundParam.stOutport[jj].enOutPort == HI_UNF_SND_OUTPUTPORT_HDMI0)
                {
                    if (bVolumeExistInBase)
                    {
                        PROC_PRINT(p, "HDMI:      			%s      VOL:%3d\n", "HDMI0", stSoundParam.au32Volume[jj]);
                    }
                    else
                    {
                        PROC_PRINT(p, "HDMI:      			%s\n", "HDMI0");
                    }
                    
                }

                if (stSoundParam.stOutport[jj].enOutPort == HI_UNF_SND_OUTPUTPORT_ARC0)
                {
                    if (bVolumeExistInBase)
                    {
                        PROC_PRINT(p, "ARC:      			%s       VOL:%3d\n", "ARC0", stSoundParam.au32Volume[jj]);
                    }
                    else
                    {
                        PROC_PRINT(p, "ARC:      			%s\n", "ARC0");
                    }
                    
                }

                if (
                    (stSoundParam.stOutport[jj].enOutPort == HI_UNF_SND_OUTPUTPORT_I2S0)
                    || (stSoundParam.stOutport[jj].enOutPort == HI_UNF_SND_OUTPUTPORT_I2S1)
                )
                {
                    PROC_PRINT(p, "I2S%d attr:      		\n",
                               stSoundParam.stOutport[jj].enOutPort - HI_UNF_SND_OUTPUTPORT_I2S0);

                    if (bVolumeExistInBase)
                    {
                        PROC_PRINT(p, "	VOL :                   %3d\n", stSoundParam.au32Volume[jj]);
                    }
                    
                    if (stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.bMaster)
                    {
                        PROC_PRINT(p, "	Master:      		TRUE\n");
                    }
                    else
                    {
                        PROC_PRINT(p, "	Master:      		FALSE\n");
                    }

                    if (stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.bPcmSampleRiseEdge)
                    {
                        PROC_PRINT(p, "	PcmSampleRiseEdge:      TRUE\n");
                    }
                    else
                    {
                        PROC_PRINT(p, "	PcmSampleRiseEdge:      FALSE\n");
                    }

                    PROC_PRINT(p, "	Master colock:      	%s\n",
                               MClk[stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.enMclkSel]);

                    PROC_PRINT(p, "	Bit colock:      	%d DIV\n",
                               stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.enBclkSel);

                    PROC_PRINT(p, "	Channel:      		%d\n",
                               stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.enChannel);

                    if (stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.enI2sMode == HI_UNF_I2S_STD_MODE)
                    {
                        PROC_PRINT(p, "	Mode:      		standard\n");
                    }
                    else
                    {
                        PROC_PRINT(p, "	Mode:      		pcm\n");
                    }

                    PROC_PRINT(p, "	Bit Depth:      	%d\n",
                               stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.enBitDepth);

                    PROC_PRINT(p, "	PCM Delay Cycle:      	%d\n",
                               stSoundParam.stOutport[jj].unAttr.stI2sAttr.stAttr.enPcmDelayCycle);
                }
            }
        }
    }

    return HI_SUCCESS;
}

static HI_S32 PDM_ProcWrite(struct file * file,
                            const char __user * buf, size_t count, loff_t *ppos)
{
    return count;
}

HI_S32 PDM_DRV_Open(struct inode *finode, struct file  *ffile)
{
    return HI_SUCCESS;
}

HI_S32 PDM_DRV_Close(struct inode *finode, struct file  *ffile)
{
    return HI_SUCCESS;
}

HI_S32 PDM_Ioctl(struct inode *inode, struct file *file, unsigned int cmd, HI_VOID *arg)
{
    HI_S32 Ret = HI_SUCCESS;

    DRV_PDM_Lock();

    DRV_PDM_UnLock();

    return Ret;
}

static long PDM_DRV_Ioctl(struct file *ffile, unsigned int cmd, unsigned long arg)
{
    HI_S32 Ret;

    Ret = HI_DRV_UserCopy(ffile->f_dentry->d_inode, ffile, cmd, arg, PDM_Ioctl);

    return Ret;
}

HI_S32 PDM_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    return HI_SUCCESS;
}

HI_S32 PDM_Resume(PM_BASEDEV_S *pdev)
{
    return HI_SUCCESS;
}

static PDM_REGISTER_PARAM_S g_PdmProcPara = {
    .rdproc = PDM_ProcRead,
    .wtproc = PDM_ProcWrite,
};

static UMAP_DEVICE_S g_PdmRegisterData;

static struct file_operations g_PdmFops =
{
    .owner			= THIS_MODULE,
    .open			= PDM_DRV_Open,
    .unlocked_ioctl = PDM_DRV_Ioctl,
    .release		= PDM_DRV_Close,
};

static PM_BASEOPS_S g_PdmDrvOps = {
    .probe        = NULL,
    .remove       = NULL,
    .shutdown     = NULL,
    .prepare      = NULL,
    .complete     = NULL,
    .suspend      = PDM_Suspend,
    .suspend_late = NULL,
    .resume_early = NULL,
    .resume       = PDM_Resume,
};

/*******************************************
tag format is version=1.0.0.0  fb=0x85000000,0x10000  baseparam=0x86000000,0x2000 ����
*******************************************/
HI_S32 PDM_GetTagBuf(HI_VOID)
{
    HI_CHAR PdmTag[512];
    HI_U32 PdmLen;
    HI_CHAR TmpBuf[32];
    HI_CHAR                 *p, *q;

    memset(PdmTag, 0x0, 512);

    PdmLen = get_param_data("pdm_tag", PdmTag, 512);
    if (PdmLen >= 512)
    {
        return HI_FAILURE;
    }

    PdmTag[511] = '\0';

    p = PdmTag;

    g_PdmGlobal.u32BufNum = 0;

    while (*p != '\0')
    {
        p = strstr(p, " ");
        if (0 == p)
        {
            return HI_SUCCESS;
        }

        q = strstr(p, "=");
        if (0 == q)
        {
            return HI_SUCCESS;
        }

        p++;

        memcpy(g_PdmGlobal.stBufInfo[g_PdmGlobal.u32BufNum].as8BufName, p, q - p);

        p = q + 1;
        q = strstr(p, ",");
        if (0 == q)
        {
            return HI_FAILURE;
        }

        memset(TmpBuf, 0x0, sizeof(TmpBuf));
        memcpy(TmpBuf, p, q - p);

        g_PdmGlobal.stBufInfo[g_PdmGlobal.u32BufNum].u32PhyAddr = simple_strtoul(TmpBuf, NULL, 16);

        p = q + 1;
        q = strstr(p, " ");
        if (0 == q)
        {
            q = PdmTag + PdmLen;
        }

        memset(TmpBuf, 0x0, sizeof(TmpBuf));
        memcpy(TmpBuf, p, q - p);

        g_PdmGlobal.stBufInfo[g_PdmGlobal.u32BufNum].u32Lenth = simple_strtoul(TmpBuf, NULL, 16);

        g_PdmGlobal.u32BufNum++;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_PDM_Init(HI_VOID)
{
    HI_S32 ret;

    ret = HI_DRV_MODULE_Register(HI_ID_PDM, PDM_NAME, (HI_VOID*)&g_PdmExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_PDM("ERR: HI_DRV_MODULE_Register!\n");
        return ret;
    }

    memset(&g_PdmGlobal, 0x0, sizeof(PDM_GLOBAL_S));

    HI_INIT_MUTEX(&g_PdmGlobal.PdmMutex);

    ret = PDM_GetTagBuf();
    if (HI_SUCCESS != ret)
    {
        memset(g_PdmGlobal.stBufInfo, 0x0, sizeof(PDM_BUF_INFO_S) * PDM_MAX_BUF_NUM);
    }

    return ret;
}

HI_S32 HI_DRV_PDM_DeInit(HI_VOID)
{
    HI_DRV_MODULE_UnRegister(HI_ID_PDM);

    return HI_SUCCESS;
}

HI_S32 PDM_DRV_ModInit(HI_VOID)
{
    HI_CHAR ProcName[16];
    DRV_PROC_ITEM_S     *pProcItem = HI_NULL;

#ifndef HI_MCE_SUPPORT
    HI_DRV_PDM_Init();
#endif

    HI_OSAL_Snprintf(ProcName, sizeof(ProcName), "%s", HI_MOD_PDM);

    pProcItem = HI_DRV_PROC_AddModule(ProcName, HI_NULL, HI_NULL);
    if (HI_NULL != pProcItem)
    {
        pProcItem->read  = g_PdmProcPara.rdproc;
        pProcItem->write = g_PdmProcPara.wtproc;
    }

    HI_OSAL_Snprintf(g_PdmRegisterData.devfs_name, sizeof(g_PdmRegisterData.devfs_name), UMAP_DEVNAME_PDM);
    g_PdmRegisterData.fops   = &g_PdmFops;
    g_PdmRegisterData.minor  = UMAP_MIN_MINOR_PDM;
    g_PdmRegisterData.owner  = THIS_MODULE;
    g_PdmRegisterData.drvops = &g_PdmDrvOps;
    if (HI_DRV_DEV_Register(&g_PdmRegisterData) < 0)
    {
        HI_FATAL_PDM("register PDM failed.\n");
        return HI_FAILURE;
    }

    return 0;
}

HI_VOID PDM_DRV_ModExit(HI_VOID)
{
    HI_CHAR ProcName[16];

    HI_DRV_DEV_UnRegister(&g_PdmRegisterData);

    HI_OSAL_Snprintf(ProcName, sizeof(ProcName), "%s", HI_MOD_PDM);
    HI_DRV_PROC_RemoveModule(ProcName);

#ifndef HI_MCE_SUPPORT
    HI_DRV_PDM_DeInit();
#endif

    return;
}

#ifdef MODULE
module_init(PDM_DRV_ModInit);
module_exit(PDM_DRV_ModExit);
#endif

MODULE_AUTHOR("HISILICON");
MODULE_LICENSE("GPL");
