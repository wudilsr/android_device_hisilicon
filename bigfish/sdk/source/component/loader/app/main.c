/*******************************************************************************
 *             Copyright 2013 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: main.c
 * Description:
 *       HiLoader entry definition here.
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 ******************************************************************************/
#include "upgrd_common.h"
#include "upgrd_osd.h"
#include "hi_loader_info.h"
#include "hi_unf_frontend.h"
#include "loaderdb_info.h"
#include "upgrd_config.h"
#include "hi_adp_boardcfg.h"
#include "protocol.h"
#include "burn.h"
#include "download_usb.h"

#ifdef HI_LOADER_BOOTLOADER
#include <common.h>
#include <command.h>
#endif

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif

#define MAX_UPGRADE_MEMORY (2 * 1024 * 1024)

static LOADERCALLBACKSET_S g_stCallback;
static HI_U32 g_u32DownloadProgress = 0;
static HI_U32 g_u32BurnDataProgress = 0;
static UPGRD_LOADER_INFO_S g_stLoaderInfo;
static LOADER_VERSION_INFO_S g_stUpgradeVer;

static HI_BOOL g_bFirstBurn = HI_TRUE;

#ifdef HI_LOADER_BOOTLOADER
HI_BOOL g_bHiproUpgrdFlg = HI_FALSE;
#endif

/*display upgrade result, type: 1-info, others-warning*/
static HI_S32 ShowResultInfo(HI_U32 type, LOADER_Content_E enContent)
{
    NOTIFY_INFO_S astInfo[3];

    astInfo[0].s32StartX = 120;
    astInfo[0].s32StartY = 90;
    if (1 == type)
    {
        HI_OSAL_Snprintf(astInfo[0].acInfo, sizeof(astInfo[0].acInfo), "%s", LoaderOSDGetText(LOADER_CONTENT_INFO));
    }
    else
    {
        HI_OSAL_Snprintf(astInfo[0].acInfo, sizeof(astInfo[0].acInfo), "%s", LoaderOSDGetText(LOADER_CONTENT_WARNING));
    }

    astInfo[1].s32StartX = 80;
    astInfo[1].s32StartY = 130;
    HI_OSAL_Snprintf(astInfo[1].acInfo, sizeof(astInfo[1].acInfo), "%s", LoaderOSDGetText(enContent));

    astInfo[2].s32StartX = 80;
    astInfo[2].s32StartY = 160;
    HI_OSAL_Snprintf(astInfo[2].acInfo, sizeof(astInfo[2].acInfo), "%s", LoaderOSDGetText(LOADER_CONTENT_REBOOT));

    return LOADER_NotifyInfo(HI_NULL, 3, astInfo);
}

static HI_S32 ShowFactoryResetInfo(LOADER_Content_E enContent)
{
    NOTIFY_INFO_S astInfo[2];

    astInfo[0].s32StartX = 120;
    astInfo[0].s32StartY = 90;

    HI_OSAL_Snprintf(astInfo[0].acInfo, sizeof(astInfo[0].acInfo), "%s", LoaderOSDGetText(LOADER_CONTENT_INFO));

	astInfo[1].s32StartX = 80;
    astInfo[1].s32StartY = 130;
    HI_OSAL_Snprintf(astInfo[1].acInfo, sizeof(astInfo[1].acInfo), "%s", LoaderOSDGetText(enContent));

    return LOADER_NotifyInfo(HI_NULL, 2, astInfo);
}

static HI_S32 BurnData(LOADER_DATA_S * pstData, HI_U32 u32Number)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (g_bFirstBurn)
    {
        g_bFirstBurn = HI_FALSE;

        LOADER_KEYLED_DisplayString("burn");

        g_stLoaderInfo.stLoaderPrivate.bTagDestroy = HI_TRUE;
        g_stLoaderInfo.stTagPara.bTagNeedUpgrd = HI_TRUE;
        s32Ret = Upgrd_WriteLoaderDBInfo(&g_stLoaderInfo);
    }

    s32Ret = LOADER_BURN_WriteData(pstData, u32Number);

    return s32Ret;
}

static HI_S32 ClearUpgradeParam(HI_VOID)
{
    g_stLoaderInfo.stLoaderParam.eUpdateType     = HI_LOADER_TYPE_BUTT;
    g_stLoaderInfo.stLoaderPrivate.u32FailedCnt  = 0;
    g_stLoaderInfo.stLoaderPrivate.bTagDestroy   = HI_FALSE;
    g_stLoaderInfo.stTagPara.bTagNeedUpgrd       = HI_FALSE;
    g_stLoaderInfo.stTagPara.bTagManuForceUpgrd = HI_FALSE;

    memset(&(g_stLoaderInfo.stLoaderParam.stPara.stUSBParam), 0, sizeof(g_stLoaderInfo.stLoaderParam.stPara.stUSBParam));

    if (HI_SUCCESS != Upgrd_WriteLoaderDBInfo(&g_stLoaderInfo))
    {
        HI_ERR_LOADER("failed to update loaderdb.\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}


static HI_S32 DisplayProgress(OSD_EVENT_TYPE_E enType, HI_U32 u32CurSize, HI_U32 u32TotalSize)
{
    HI_U32 u32Progress = 0;

    if (u32TotalSize == 0)
        return HI_FAILURE;

    u32Progress = u32CurSize / (u32TotalSize / 100);

    switch (enType)
    {
    case OSD_EVENT_TYPE_DOWNLOAD:
    {
        if (g_u32DownloadProgress != u32Progress)
        {
            g_u32DownloadProgress = u32Progress;

            Drv_ShowDoubleGuage(g_u32DownloadProgress, g_u32BurnDataProgress);
        }

        break;
    }

    case OSD_EVENT_TYPE_BURN:
    {
        if (g_u32BurnDataProgress != u32Progress)
        {
            g_u32BurnDataProgress = u32Progress;

            Drv_ShowDoubleGuage(g_u32DownloadProgress, g_u32BurnDataProgress);
        }

        break;
    }

    default:
        break;
    }

    return HI_SUCCESS;
}

static HI_VOID ShowLoaderInfo(HI_VOID)
{
    HI_INFO_LOADER("HiLOADER start , build at %s , %s \n", __TIME__, __DATE__ );
    HI_INFO_LOADER("Support features:\n");
#if defined(HI_LOADER_PROTOCOL_HISI_OTA)
    HI_INFO_LOADER("HISI_OTA\n");
#endif

#if defined(HI_LOADER_PROTOCOL_SSU_OTA)
    HI_INFO_LOADER("SSU_OTA\n");
#endif

#if defined(HI_LOADER_MODE_USB)
    HI_INFO_LOADER("USB\n");
#endif

#if defined(HI_LOADER_MODE_IP)
    HI_INFO_LOADER("IP\n");
#endif

#if defined(HI_LOADER_MODE_FS)
    HI_INFO_LOADER("FS\n");
#endif
}

static HI_VOID ShowUpgrdParam(UPGRD_LOADER_INFO_S *ptrParam)
{
    if(!ptrParam)
    {
        HI_FATAL_LOADER("invalid input parameter\n");
        return;
    }

    HI_DBG_LOADER("*************** loaderdb info *******************\n");

    if (ptrParam->stTagPara.bTagManuForceUpgrd)
        HI_DBG_LOADER("manual_force_upgrd                     : %d\n", ptrParam->stTagPara.bTagManuForceUpgrd);
    else
        HI_DBG_LOADER("upgrd_type(0:OTA,1:IP,2:USB,3:FS,4:FACTORY_RESET,5:INVALID) : %d\n", ptrParam->stLoaderParam.eUpdateType);

    HI_DBG_LOADER("destroy_tag                            : %d\n", ptrParam->stLoaderPrivate.bTagDestroy);
    HI_DBG_LOADER("fail_cnt                               : %d\n", ptrParam->stLoaderPrivate.u32FailedCnt);
    HI_DBG_LOADER("new_software_version                   : 0x%x\n", ptrParam->stLoaderParam.u32CurSoftware);

    HI_DBG_LOADER("******************* end *****************************\n");
}


static HI_S32 LOADER_InitEnv(HI_VOID)
{
    HI_S32 s32Ret;

#ifdef HI_LOADER_APPLOADER
    HI_CHAR * env;

    /* init common modules */
    s32Ret = HI_SYS_Init();
    if (HI_SUCCESS != s32Ret)
        goto out;

    /* register loader module */
    s32Ret = HI_MODULE_Register(HI_ID_LOADER, "HI_LOADER");
    if (HI_SUCCESS != s32Ret)
        goto out;

    /* change log level */
    env = getenv("loglevel");
    if (env)
    {
        HI_U32 value = atoi(env);
        if (value < HI_LOG_LEVEL_BUTT)
            s32Ret = HI_SYS_SetLogLevel(HI_ID_LOADER, (HI_LOG_LEVEL_E)value);
    }
    else
    {
        s32Ret = HI_SYS_SetLogLevel(HI_ID_LOADER, HI_LOG_LEVEL_INFO);
    }
#endif

    /* show loader basic info */
    ShowLoaderInfo();

    s32Ret = LOADER_KEYLED_Init();
    if (HI_SUCCESS != s32Ret)
        goto out;

    s32Ret = LOADER_OSD_Init();
    if (HI_SUCCESS != s32Ret)
        goto out;

    LOADER_KEYLED_DisplayString("LoAd");

out:
    return s32Ret;
}

static HI_LOADER_TYPE_E LOADER_ProbeUpgrdType(HI_VOID )
{
    HI_S32 s32Ret;
    HI_LOADER_TYPE_E enUpgrdType = HI_LOADER_TYPE_BUTT;

    /* Get upgrade parameter from loaderdb */
    s32Ret = Upgrd_ReadLoaderDBInfo(&g_stLoaderInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("Failed to read loaderdb Info.\n");
        return HI_LOADER_TYPE_BUTT;
    }

    ShowUpgrdParam(&g_stLoaderInfo);

    if (HI_TRUE == g_stLoaderInfo.stLoaderPrivate.bTagDestroy)
    {
        return g_stLoaderInfo.stLoaderParam.eUpdateType;
    }

    s32Ret = LOADER_CheckUpgradeTypePolicy(&g_stLoaderInfo, &enUpgrdType);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("invalid upgrade type(%d).\n", enUpgrdType);
        return HI_LOADER_TYPE_BUTT;
    }

    return enUpgrdType;

}

/*
 * check whether stb met upgrade condition .
 * for normal ugprade need check sbtinfo and software version.
 * but for manual force ugprade only check stbinfo.
 */
static HI_S32 LOADER_VerifyStbVersion(HI_LOADER_TYPE_E enUpgrdType)
{
    HI_S32 s32Ret;

    /* get upgrade stream version info */
    s32Ret = LOADER_PROTOCOL_GetVersionInfo(&g_stUpgradeVer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("get upgrade stream version info failed!\n");
        goto out;
    }

    s32Ret = LOADER_CheckVersionMatch(&g_stLoaderInfo, &g_stUpgradeVer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("can't upgrade stb with the upgrade stream for version dismatch.\n");
        goto out;
    }

out:
    return s32Ret;
}

static HI_S32 LOADER_UpdateStbVersion(HI_VOID)
{
    return LOADER_UpdateVersionInfo(&g_stLoaderInfo, &g_stUpgradeVer);
}

static HI_S32 LOADER_RecvBurnUpgrdData(HI_VOID)
{
    HI_S32 s32Ret;
    HI_U32 u32PartitionNum;
    LOADER_PARTITION_INFO_S astPartitionInfo[MAX_UPGRADE_IMAGE_NUM];

    s32Ret = LOADER_PROTOCOL_GetPartitionInfo(astPartitionInfo, MAX_UPGRADE_IMAGE_NUM, &u32PartitionNum);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("Get partition info failed!\n");
        goto out;
    }

    s32Ret = LOADER_BURN_Init(astPartitionInfo, u32PartitionNum, g_stCallback.pfnOSDCallback);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("Burn Init failed!\n");
        goto out;
    }

    s32Ret = LOADER_PROTOCOL_Process(MAX_UPGRADE_MEMORY);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("Process failed!\n" );
        goto out;
    }

out:
    LOADER_BURN_DeInit();
    return s32Ret;
}

#define SHOW_UPGRADE_INFO_HELPER() do {\
    switch (enUpgrdType) \
    {\
    case HI_LOADER_TYPE_OTA: \
        HI_DBG_LOADER(">> start OTA ugprade procedure...\n"); \
        break;\
    case HI_LOADER_TYPE_IP: \
        HI_DBG_LOADER(">> start IP ugprade procedure...\n"); \
        break;\
    case HI_LOADER_TYPE_USB: \
        HI_DBG_LOADER(">> start USB ugprade procedure...\n"); \
        break;\
    case HI_LOADER_TYPE_FS: \
        HI_DBG_LOADER(">> start FS ugprade procedure...\n"); \
        break;\
    default:\
        HI_DBG_LOADER("invalid upgrade type.\n");\
    }\
}while(0)

static HI_S32 LOADER_DoUpgrdProcedure(HI_LOADER_TYPE_E enUpgrdType)
{
    HI_S32 s32Ret;

    if (enUpgrdType >= HI_LOADER_TYPE_BUTT)
    {
        HI_ERR_LOADER("invalid upgrade type(%d).\n", enUpgrdType);
        return HI_FAILURE;
    }

    SHOW_UPGRADE_INFO_HELPER();

    /* init osd display */
    Drv_CreatGuageWin();
    Drv_UpdateIndictorText(LOADER_CONTENT_UPGRADING);
    Drv_ShowDoubleGuage(0, 0);

    s32Ret = LOADER_PROTOCOL_Init(enUpgrdType, (HI_VOID *)&(g_stLoaderInfo.stLoaderParam));
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("protocol init failed!\n");
        goto out;
    }

    g_stCallback.pfnDataCallback = BurnData;
    g_stCallback.pfnOSDCallback = DisplayProgress;
    s32Ret = LOADER_PROTOCOL_RegisterCallback(&g_stCallback);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("Register callback failed!\n");
        goto out;
    }

    /* check whether upgrade stream can be upgraded  */
    s32Ret = LOADER_VerifyStbVersion(enUpgrdType);
    if (HI_SUCCESS != s32Ret)
        goto out;

    /* receive upgrade data and burn into storage device */
    s32Ret = LOADER_RecvBurnUpgrdData();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("receive and burn data failed.\n");
        goto out;
    }

    /* update stb version info */
    s32Ret = LOADER_UpdateStbVersion();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("update stb version info failed.\n");
        goto out;
    }

out:
    LOADER_PROTOCOL_DeInit();
    Drv_DestroyGuageWin();

    return s32Ret;

}

HI_VOID LOADER_ShowUpgradeResult(HI_S32 s32Ret)
{
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_LOADER("HiLOADER upgrade failed.\n");

        switch (s32Ret)
        {
        case HI_UPGRD_ERR_SIGNAL_LOSE:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_SIG_EXPT);
            LOADER_KEYLED_DisplayString("E01");
            break;
        }

        case HI_UPGRD_CRC_ERROR:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_CRC);
            LOADER_KEYLED_DisplayString("E03");
            break;
        }

        case HI_UPGRD_USB_FILE_ERROR:
        {
            ShowResultInfo(2, LOADER_CONTENT_NOT_FIND_USB_FILE);
            LOADER_KEYLED_DisplayString("E04");
            break;
        }

        case HI_UPGRD_UPGRDPRO_WRFLASH:
        {
            LOADER_KEYLED_DisplayString("E05");
            break;
        }

        case HI_UPGRD_DMX_TIMEOUT:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_DOWNLOAD_TIMEOUT);
            LOADER_KEYLED_DisplayString("E06");
            break;
        }

        case HI_UPGRD_OUI_NOT_MATCH:
        {
            ShowResultInfo(2, LOADER_CONTENT_NOT_FIND_USB_FILE);
            LOADER_KEYLED_DisplayString("E07");
            break;
        }

        case HI_UPGRD_HARDWARE_NOT_MATCH:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_HARD_VER);
            LOADER_KEYLED_DisplayString("E08");
            break;
        }

        case HI_UPGRD_SOFTWARE_NOT_MATCH:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_SOFT_VER);
            LOADER_KEYLED_DisplayString("E09");
            break;
        }

        case HI_UPGRD_SN_NOT_MATCH:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_SN_DISMATCH);
            LOADER_KEYLED_DisplayString("E10");
            break;
        }

        case HI_UPGRD_DATA_ERROR:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_DATA);
            LOADER_KEYLED_DisplayString("E11");
            break;
        }

        case HI_UPGRD_CONNECT_FAIL:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_NO_RESP);
            LOADER_KEYLED_DisplayString("E12");
            break;
        }

        case HI_UPGRD_IP_FILE_ERROR:
        {
            ShowResultInfo(2, LOADER_CONTENT_IP_NOT_FIND_FILE);
            LOADER_KEYLED_DisplayString("E13");
            break;
        }

        case HI_UPGRD_NETWORK_ERROR:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_NET_EXPT);
            LOADER_KEYLED_DisplayString("E14");
            break;
        }

        case HI_UPGRD_SET_IP_ERROR:
        {
            ShowResultInfo(2, LOADER_CONTENT_SET_IP_ERR);
            LOADER_KEYLED_DisplayString("E15");
            break;
        }

        case HI_UPGRD_IP_TIMEOUT:
        {
            ShowResultInfo(2, LOADER_CONTENT_FAIL_NET_TIMEOUT);
            LOADER_KEYLED_DisplayString("E16");
            break;
        }

		case HI_UPGRD_FACTORY_RESET_FAIL:
        {
            ShowResultInfo(2, LOADER_CONTENT_FACTORY_RESET_FAILED);
            LOADER_KEYLED_DisplayString("E17");
            break;
        }

        default:
            ShowResultInfo(2, LOADER_CONTENT_FAIL_DOWNLOAD);
            LOADER_KEYLED_DisplayString("E02");
            break;
        }
    }
    else
    {
        HI_INFO_LOADER("HiLOADER upgrade success finished.\n");

        ShowResultInfo(1, LOADER_CONTENT_PT_SUCC);
        LOADER_KEYLED_DisplayString("Succ");
    }

    /* keep OSD display upgrade result 3 seconds */
    LOADER_Delayms(3000);
}

static HI_VOID LOADER_FactoryReset()
{
	LOADER_PARTITION_INDEX_S	stLoaderParIndex;
	HI_S8 acCommand[128] = {0};
	pid_t child_pid;

	memset(&stLoaderParIndex, 0x0, sizeof(stLoaderParIndex));
	if (HI_SUCCESS != Loader_GetFlashParIndex(CACHE, &stLoaderParIndex))
	{
		HI_ERR_LOADER("can't find %s partition!\n", CACHE);
		LOADER_ShowUpgradeResult(HI_UPGRD_FACTORY_RESET_FAIL);
		return;
	}
	if (HI_FLASH_TYPE_EMMC_0 == stLoaderParIndex.u32FlashType)
	{
		HI_OSAL_Snprintf(acCommand, sizeof(acCommand), "mkfs.ext4 /dev/mmcblk0p%d -F", stLoaderParIndex.u32FlashIndex+1);
	}
	child_pid = system(acCommand);
	if (!(-1!=child_pid && WIFEXITED(child_pid) && 0 == WEXITSTATUS(child_pid)))
	{
		HI_ERR_LOADER("format %s partition error!\n", CACHE);
		LOADER_ShowUpgradeResult(HI_UPGRD_FACTORY_RESET_FAIL);
		return;
	}

	memset(&stLoaderParIndex, 0x0, sizeof(stLoaderParIndex));
	if (HI_SUCCESS != Loader_GetFlashParIndex(USERDATA, &stLoaderParIndex))
	{
		HI_ERR_LOADER("can't find %s partition!\n", USERDATA);
		LOADER_ShowUpgradeResult(HI_UPGRD_FACTORY_RESET_FAIL);
		return;
	}
	if (HI_FLASH_TYPE_EMMC_0 == stLoaderParIndex.u32FlashType)
	{
		HI_OSAL_Snprintf(acCommand, sizeof(acCommand), "mkfs.ext4 /dev/mmcblk0p%d -F", stLoaderParIndex.u32FlashIndex+1);
	}

	child_pid = system(acCommand);
	if (!(-1!=child_pid && WIFEXITED(child_pid) && 0 == WEXITSTATUS(child_pid)))
	{
		HI_ERR_LOADER("format %s partition error!\n", USERDATA);
		LOADER_ShowUpgradeResult(HI_UPGRD_FACTORY_RESET_FAIL);
		return;
	}
	(HI_VOID)ShowFactoryResetInfo(LOADER_CONTENT_FACTORY_RESET_SUCC);
}


/* general upgrade entry */
#ifdef HI_LOADER_APPLOADER
int main(HI_VOID)
#else
HI_S32 LOADER_App(HI_VOID)
#endif
{
    HI_S32 s32Ret;
    HI_LOADER_TYPE_E enUpgrdType = HI_LOADER_TYPE_BUTT;

    s32Ret = LOADER_InitEnv();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("init loader runtime env failed.\n");
        goto out;
    }

    enUpgrdType = LOADER_ProbeUpgrdType();
    if (enUpgrdType >= HI_LOADER_TYPE_BUTT)
    {
        s32Ret = HI_FAILURE;
        goto out;
    }

	if (enUpgrdType == HI_LOADER_TPYE_FACT_RESET)
	{
		(HI_VOID)ShowFactoryResetInfo(LOADER_CONTENT_FACTORY_RESET_GOINGON);
		LOADER_FactoryReset();
		ClearUpgradeParam();
		goto out;
	}

    s32Ret = LOADER_DoUpgrdProcedure(enUpgrdType);
    if (HI_SUCCESS == s32Ret)
        ClearUpgradeParam();

    /* show upgrade final result */
    LOADER_ShowUpgradeResult(s32Ret);

out:

    LOADER_UpgrdeDone(s32Ret, enUpgrdType);

    return s32Ret;
}

/*
 * entry for factory batch USB upgrade scense
 * without check upgrade tag and version info.
 */
#ifdef HI_LOADER_BOOTLOADER

static HI_S32 DisplayUsbUpgrdProgress(OSD_EVENT_TYPE_E enType, HI_U32 u32CurSize, HI_U32 u32TotalSize)
{
    HI_U32 u32Progress = 0;

    if (u32TotalSize == 0)
        return HI_FAILURE;

    switch (enType)
    {
    case OSD_EVENT_TYPE_DOWNLOAD:
        u32Progress = u32CurSize / (u32TotalSize / 100);
        HI_INFO_LOADER("%d%%\n", u32Progress);
        break;

    case OSD_EVENT_TYPE_BURN:
    {
        /* this printf keep heartbeat between hipro */
        HI_INFO_LOADER("writing...\n");

        break;
    }

    default:
        break;
    }

    return HI_SUCCESS;
}

HI_S32 LOADER_USB_Mandatory_Upgrd(HI_VOID)
{
    HI_S32 s32Ret;
    HI_LOADER_TYPE_E enUpgrdType = HI_LOADER_TYPE_USB;

    g_bHiproUpgrdFlg = HI_TRUE;

    ShowLoaderInfo();

    s32Ret = LOADER_PROTOCOL_Init(enUpgrdType, (HI_VOID *)NULL);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("protocol init failed!\n");
        goto err0;
    }

    g_stCallback.pfnDataCallback = LOADER_BURN_WriteData;
    g_stCallback.pfnOSDCallback = DisplayUsbUpgrdProgress;
    s32Ret = LOADER_PROTOCOL_RegisterCallback(&g_stCallback);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("Register callback failed!\n");
        goto err1;
    }

    /* get upgrade stream info */
    s32Ret = LOADER_PROTOCOL_GetVersionInfo(&g_stUpgradeVer);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("get upgrade stream version info failed!\n");
        goto err1;
    }

    /* receive upgrade data and burn into storage device */
    s32Ret = LOADER_RecvBurnUpgrdData();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("receive and burn data failed.\n");
    }

    HI_INFO_LOADER("HiLOADER upgrade success finished.\n");

err1:
    LOADER_PROTOCOL_DeInit();
err0:
    LOADER_UpgrdeDone(s32Ret, enUpgrdType);
    g_bHiproUpgrdFlg = HI_FALSE;
    return s32Ret;
}

int do_usbburn(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
    return LOADER_USB_Mandatory_Upgrd();
}

U_BOOT_CMD(
    usbburn,    3,  1,  do_usbburn,
    "burn file from USB device\n",
    "burn file from USB device\n"
);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
