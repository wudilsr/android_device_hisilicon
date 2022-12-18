#include "hi_unf_disp.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_common.h"
#include "hi_unf_pdm.h"
#include "hi_go_gdev.h"
#include "hi_go_decoder.h"
#include "hi_go_bliter.h"

#include "upgrd_common.h"
#include "hi_adp_boardcfg.h"
#ifdef HI_HDCP_SUPPORT
#include "hi_flash.h"
#endif

#ifdef HI_ADVCA_FUNCTION_RELEASE
#include "ca_ssd.h"
#endif

#ifdef HI_LOADER_APPLOADER
typedef struct hiHDMI_ARGS_S
{
    HI_UNF_HDMI_ID_E  enHdmi;
}HDMI_ARGS_S;

static HDMI_ARGS_S g_stHdmiArgs;

#ifdef HI_HDCP_SUPPORT
HI_U32 g_HDCPFlag  = HI_TRUE;
#endif

//static HI_U32 g_ForceDVIFlag = HI_FALSE;
static HI_U32 g_HDMI_Bebug       = HI_FALSE;
static HI_U32 g_HDMIUserCallbackFlag = HI_FALSE;
static HI_UNF_HDMI_DEFAULT_ACTION_E g_enDefaultMode    = HI_UNF_HDMI_DEFAULT_ACTION_HDMI;//HI_UNF_HDMI_DEFAULT_ACTION_NULL;

static HI_UNF_HDMI_CALLBACK_FUNC_S g_stCallbackFunc;
typedef void (*User_HDMI_CallBack)(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData);

static User_HDMI_CallBack pfnHdmiUserCallback = NULL;

void HDMI_HotPlug_Proc(HI_VOID *pPrivateData)
{
    HI_S32          ret = HI_SUCCESS;
    HDMI_ARGS_S     *pArgs  = (HDMI_ARGS_S*)pPrivateData;
    HI_UNF_HDMI_ID_E       hHdmi   =  pArgs->enHdmi;
    HI_UNF_HDMI_ATTR_S             stHdmiAttr;
    //HI_UNF_HDMI_INFOFRAME_S        stInfoFrame;
    HI_UNF_EDID_BASE_INFO_S        stSinkCap;
    HI_UNF_HDMI_STATUS_S           stHdmiStatus;

#ifdef HI_HDCP_SUPPORT
        static HI_U8 u8FirstTimeSetting = HI_TRUE;
#endif

	HI_DBG_LOADER("\n --- Get HDMI event: HOTPLUG. --- \n");

    HI_UNF_HDMI_GetStatus(hHdmi,&stHdmiStatus);
    if (HI_FALSE == stHdmiStatus.bConnected)
    {
        HI_ERR_LOADER("No Connect\n");
        return;
    }

    
    HI_UNF_HDMI_GetAttr(hHdmi, &stHdmiAttr);
    ret = HI_UNF_HDMI_GetSinkCapability(hHdmi, &stSinkCap); 


    if(ret == HI_SUCCESS)
    {
        //stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_YCBCR444;
        if(HI_TRUE == stSinkCap.bSupportHdmi)
        {
            stHdmiAttr.bEnableHdmi = HI_TRUE;
            if(HI_TRUE != stSinkCap.stColorSpace.bYCbCr444)
            {
                stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
            }
        }
        else
        {
            stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
            //read real edid ok && sink not support hdmi,then we run in dvi mode
            stHdmiAttr.bEnableHdmi = HI_FALSE;
        }
    }
    else
    {
        //when get capability fail,use default mode 
        if(g_enDefaultMode == HI_UNF_HDMI_DEFAULT_ACTION_HDMI)
            stHdmiAttr.bEnableHdmi = HI_TRUE;
        else 
            stHdmiAttr.bEnableHdmi = HI_FALSE;
    }

	if(HI_TRUE == stHdmiAttr.bEnableHdmi)
	{
		stHdmiAttr.bEnableAudio = HI_FALSE;
		stHdmiAttr.bEnableVideo = HI_TRUE;
		stHdmiAttr.bEnableAudInfoFrame = HI_TRUE;
		stHdmiAttr.bEnableAviInfoFrame = HI_TRUE;
	}
	else
	{
		stHdmiAttr.bEnableAudio = HI_FALSE;
		stHdmiAttr.bEnableVideo = HI_TRUE;
		stHdmiAttr.bEnableAudInfoFrame = HI_FALSE;
		stHdmiAttr.bEnableAviInfoFrame = HI_FALSE;
        stHdmiAttr.enVidOutMode = HI_UNF_HDMI_VIDEO_MODE_RGB444;
	}

#ifdef HI_HDCP_SUPPORT
    if (u8FirstTimeSetting == HI_TRUE)
    {
        u8FirstTimeSetting = HI_FALSE;
        if (g_HDCPFlag == HI_TRUE)
        {
            stHdmiAttr.bHDCPEnable = HI_TRUE;//Enable HDCP
        }
        else
        {
            stHdmiAttr.bHDCPEnable= HI_FALSE;
        }
    }
    else
    {
        //HDCP Enable use default setting!!
    }
#endif
	
	HI_UNF_HDMI_SetAttr(hHdmi, &stHdmiAttr);

	/* HI_UNF_HDMI_SetAttr must before HI_UNF_HDMI_Start! */
	HI_UNF_HDMI_Start(hHdmi);

	return;
}

HI_VOID HDMI_UnPlug_Proc(HI_VOID *pPrivateData)
{
    HDMI_ARGS_S     *pArgs = (HDMI_ARGS_S*)pPrivateData;
    HI_UNF_HDMI_ID_E hHdmi = pArgs->enHdmi;

    HI_UNF_HDMI_Stop(hHdmi);

    return;
}

#ifdef HI_HDCP_SUPPORT
static HI_U32 HDCPFailCount = 0;
HI_VOID HDMI_HdcpFail_Proc(HI_VOID *pPrivateData)
{
    HI_UNF_HDMI_ATTR_S stHdmiAttr;
    HI_ERR_LOADER("\n --- Get HDMI event: HDCP_FAIL. --- \n");

    HDCPFailCount++;

    if (HDCPFailCount == 10)
    {
        HI_UNF_HDMI_GetAttr(0, &stHdmiAttr);
        stHdmiAttr.bEnableVideo  = HI_FALSE;
        stHdmiAttr.bEnableAudio = HI_FALSE;
        HI_UNF_HDMI_SetAttr(0, &stHdmiAttr);
    }

    return;
}

HI_VOID HDMI_HdcpSuccess_Proc(HI_VOID *pPrivateData)
{
    HI_INFO_LOADER("\n --- Get HDMI event: HDCP_SUCCESS. --- \n");
    return;
}
#endif

HI_VOID HDMI_Event_Proc(HI_UNF_HDMI_EVENT_TYPE_E event, HI_VOID *pPrivateData)
{
    switch (event)
    {
    case HI_UNF_HDMI_EVENT_HOTPLUG:
        HDMI_HotPlug_Proc(pPrivateData);
        break;
    case HI_UNF_HDMI_EVENT_NO_PLUG:
        HDMI_UnPlug_Proc(pPrivateData);
        break;
    case HI_UNF_HDMI_EVENT_EDID_FAIL:
        break;
#ifdef HI_HDCP_SUPPORT
    case HI_UNF_HDMI_EVENT_HDCP_FAIL:
        HDMI_HdcpFail_Proc(pPrivateData);
        break;
    case HI_UNF_HDMI_EVENT_HDCP_SUCCESS:
        HDMI_HdcpSuccess_Proc(pPrivateData);
        break;
#endif
    case HI_UNF_HDMI_EVENT_RSEN_CONNECT:
        break;
    case HI_UNF_HDMI_EVENT_RSEN_DISCONNECT:
        break;
    default:
        break;
    }

    /* Private Usage */
    if ((g_HDMIUserCallbackFlag == HI_TRUE) && (pfnHdmiUserCallback != NULL))
    {
        pfnHdmiUserCallback(event, NULL);
    }

    return;
}

#ifdef HI_HDCP_SUPPORT	
static HI_S32 HIADP_HDMI_SetHDCPKey(HI_UNF_HDMI_ID_E enHDMIId)
{
	HI_UNF_HDMI_LOAD_KEY_S stLoadKey;
	FILE *pBinFile;
	HI_U32 u32Len;
	HI_S32 s32Ret;
    HI_HANDLE hFlash = HI_INVALID_HANDLE;
    HI_Flash_InterInfo_S stFlashInfo;
    HI_U8 *pu8TmpBuf = NULL;

    hFlash = HI_Flash_OpenByName("privatedata");
    if(hFlash == HI_INVALID_HANDLE)
    {
        HI_ERR_LOADER("Open flash failed!\r\n");
        return HI_FAILURE;
    }
    
    s32Ret = HI_Flash_GetInfo(hFlash, &stFlashInfo);
    if(s32Ret != HI_SUCCESS)
    {
        HI_ERR_LOADER("Get flash info failed!\r\n");
        HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }

    pu8TmpBuf = (HI_U8*)malloc(stFlashInfo.PageSize);
    if(pu8TmpBuf == NULL)
    {
        HI_ERR_LOADER("Malloc memory failed!\r\n");
        HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }

    s32Ret = HI_Flash_Read(hFlash, 0, pu8TmpBuf, stFlashInfo.PageSize, HI_FLASH_RW_FLAG_RAW);
    if(s32Ret < 0)
    {
        HI_ERR_LOADER("Read flash failed!\r\n");
        HI_Flash_Close(hFlash);
        return HI_FAILURE;
    }

    memset(&stLoadKey, 0, sizeof(HI_UNF_HDMI_LOAD_KEY_S));
    stLoadKey.u32KeyLength = 332;

#ifdef HI_ADVCA_FUNCTION_RELEASE
	CA_SSD_DecryptImage(pu8TmpBuf, 336, HI_CA_KEY_GROUP_1);	
#else
	if(pu8TmpBuf[2] != 'H' || pu8TmpBuf[3] != 'I')
    {
		HI_INFO_LOADER("HDCP key invalided!\n");
    }
#endif
	stLoadKey.pu8InputEncryptedKey = pu8TmpBuf;

	s32Ret = HI_UNF_HDMI_LoadHDCPKey(enHDMIId,&stLoadKey);

	if(pu8TmpBuf != NULL)
	{
		free(pu8TmpBuf);
	}
	HI_Flash_Close(hFlash);
	return s32Ret;
}
#endif

HI_S32 HIADP_HDMI_Init(HI_UNF_HDMI_ID_E enHDMIId, HI_UNF_ENC_FMT_E enWantFmt)
{
    HI_S32 Ret = HI_FAILURE;
    HI_UNF_HDMI_OPEN_PARA_S stOpenParam;
    
    g_stHdmiArgs.enHdmi       = enHDMIId;

    Ret = HI_UNF_HDMI_Init();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_LOADER("HI_UNF_HDMI_Init failed:%#x\n", Ret);
        return HI_FAILURE;
    }

#ifdef HI_HDCP_SUPPORT
    Ret = HIADP_HDMI_SetHDCPKey(HI_UNF_HDMI_ID_0);
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_LOADER("Set hdcp erro:%#x\n",Ret);
    }
#endif

    g_stCallbackFunc.pfnHdmiEventCallback = HDMI_Event_Proc;
    g_stCallbackFunc.pPrivateData = &g_stHdmiArgs;

    Ret = HI_UNF_HDMI_RegCallbackFunc(enHDMIId, &g_stCallbackFunc);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_LOADER("hdmi reg failed:%#x\n", Ret);
        HI_UNF_HDMI_DeInit();
        return HI_FAILURE;
    }

    stOpenParam.enDefaultMode = g_enDefaultMode; //HI_UNF_HDMI_FORCE_NULL;
    Ret = HI_UNF_HDMI_Open(enHDMIId, &stOpenParam);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_LOADER("HI_UNF_HDMI_Open failed:%#x\n", Ret);
        HI_UNF_HDMI_DeInit();
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_E enHDMIId)
{
    HI_UNF_HDMI_Stop(enHDMIId);

    HI_UNF_HDMI_Close(enHDMIId);

    HI_UNF_HDMI_UnRegCallbackFunc(enHDMIId, &g_stCallbackFunc);

    HI_UNF_HDMI_DeInit();

    return HI_SUCCESS;
}
#endif

static HI_UNF_DISP_TIMING_S g_stDispTiming =
{
    .VFB           =                               27,
    .VBB           =                               23,
    .VACT          =                              768,
    .HFB           =                              210,
    .HBB           =                               46,
    .HACT          =                             1366,
    .VPW           =								4,
    .HPW           =                               24,
    .IDV           = HI_FALSE,
    .IHS           = HI_FALSE,
    .IVS           = HI_FALSE,
    .ClockReversal = HI_FALSE,
    .DataWidth     = HI_UNF_DISP_INTF_DATA_WIDTH24,
    .ItfFormat     = HI_UNF_DISP_INTF_DATA_FMT_RGB888,
    .DitherEnable  = HI_FALSE,
    .ClkPara0      =                       0x912ccccc,
    .ClkPara1      =                       0x006d8157,

    //.InRectWidth = 1366,
    //.InRectHeight = 768,
};

static HI_VOID GetDefDispParam(HI_UNF_PDM_DISP_PARAM_S *pstDispParam)
{
    HI_S32 i;

    pstDispParam->enFormat   = HI_UNF_ENC_FMT_720P_50;
    pstDispParam->u32HuePlus = 50;
    pstDispParam->u32Saturation = 50;
    pstDispParam->u32Contrast   = 50;
    pstDispParam->u32Brightness = 50;

    pstDispParam->stBgColor.u8Red   = 0x00;
    pstDispParam->stBgColor.u8Green = 0x00;
    pstDispParam->stBgColor.u8Blue  = 0xFF;

    pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_YPBPR].enIntfType = HI_UNF_DISP_INTF_TYPE_YPBPR;
    pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_YPBPR].unIntf.stYPbPr.u8DacY  = DAC_YPBPR_Y;
    pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_YPBPR].unIntf.stYPbPr.u8DacPb = DAC_YPBPR_PB;
    pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_YPBPR].unIntf.stYPbPr.u8DacPr = DAC_YPBPR_PR;

    pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_CVBS].enIntfType = HI_UNF_DISP_INTF_TYPE_CVBS;
    pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_CVBS].unIntf.stCVBS.u8Dac = DAC_CVBS;

    for (i = 0; i < HI_UNF_DISP_INTF_TYPE_BUTT; i++)
    {
        if ((i != HI_UNF_DISP_INTF_TYPE_YPBPR) && (i != HI_UNF_DISP_INTF_TYPE_CVBS))
        {
            pstDispParam->stIntf[i].enIntfType = HI_UNF_DISP_INTF_TYPE_BUTT;
        }
    }

    pstDispParam->stDispTiming = g_stDispTiming;

    pstDispParam->enPixelFormat    = HIGO_PF_8888;
    pstDispParam->u32VirtScreenWidth  = 1280;
    pstDispParam->u32VirtScreenHeight = 720;
    memset(&(pstDispParam->stDispOffset), 0, sizeof(pstDispParam->stDispOffset)); 

    return;
}

HI_VOID ADP_TransFomat(HI_UNF_ENC_FMT_E enSrcFmt, HI_UNF_ENC_FMT_E *penHdFmt, HI_UNF_ENC_FMT_E *penSdFmt)
{
    switch (enSrcFmt)
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

HI_S32 HI_ADP_DispInit(HI_UNF_PDM_DISP_PARAM_S *pstDispParam)
{
	HI_S32 Ret;
	HI_UNF_ENC_FMT_E HdFmt, SdFmt;

	if (HI_NULL == pstDispParam)
	{
		HI_ERR_LOADER("invalid input parameter.\n");
		return HI_FAILURE;
	}

	Ret = HI_UNF_DISP_Init();
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_UNF_DISP_Init err! Ret = %x\n", Ret);
		goto ERR0;
	}

	Ret  = HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY1, &(pstDispParam->stBgColor));
	Ret |= HI_UNF_DISP_SetBgColor(HI_UNF_DISPLAY0, &(pstDispParam->stBgColor));

	/*same source: get hd and sd format*/
	ADP_TransFomat(pstDispParam->enFormat, &HdFmt, &SdFmt);

	Ret |= HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY1, HdFmt);
	Ret |= HI_UNF_DISP_SetFormat(HI_UNF_DISPLAY0, SdFmt);

	/*set hd and sd interface*/
	HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY0, &(pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_CVBS]), 1);
	HI_UNF_DISP_AttachIntf(HI_UNF_DISPLAY1, &(pstDispParam->stIntf[HI_UNF_DISP_INTF_TYPE_YPBPR]), 1);

	Ret |= HI_UNF_DISP_SetBrightness(HI_UNF_DISPLAY1, pstDispParam->u32Brightness);
	Ret |= HI_UNF_DISP_SetContrast(HI_UNF_DISPLAY1, pstDispParam->u32Contrast);
	Ret |= HI_UNF_DISP_SetSaturation(HI_UNF_DISPLAY1, pstDispParam->u32Saturation);
	Ret |= HI_UNF_DISP_SetHuePlus(HI_UNF_DISPLAY1, pstDispParam->u32HuePlus);

	Ret |= HI_UNF_DISP_SetBrightness(HI_UNF_DISPLAY0, pstDispParam->u32Brightness);
	Ret |= HI_UNF_DISP_SetContrast(HI_UNF_DISPLAY0, pstDispParam->u32Contrast);
	Ret |= HI_UNF_DISP_SetSaturation(HI_UNF_DISPLAY0, pstDispParam->u32Saturation);
	Ret |= HI_UNF_DISP_SetHuePlus(HI_UNF_DISPLAY0, pstDispParam->u32HuePlus);

	/* set lcd timing */

	//Ret |= HI_UNF_DISP_SetCustomTiming(HI_UNF_DISPLAY1, &stDispParam.stDispTiming);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("set disp attr err! Ret = %x\n", Ret);
		goto ERR1;
	}

	Ret = HI_UNF_DISP_Attach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_UNF_DISP_Attach err! Ret = %x\n", Ret);
		goto ERR1;
	}

	Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY1);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_UNF_DISP_Open err! Ret = %x\n", Ret);
		goto ERR2;
	}

	Ret = HI_UNF_DISP_Open(HI_UNF_DISPLAY0);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_UNF_DISP_Open err! Ret = %x\n", Ret);
		goto ERR3;
	}

#ifdef HI_LOADER_APPLOADER
	Ret = HIADP_HDMI_Init(HI_UNF_HDMI_ID_0, HdFmt);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HIADP_HDMI_Init err! Ret = %x\n", Ret);
		goto ERR4;
	}
#endif

	return Ret;

#ifdef HI_LOADER_APPLOADER
ERR4:
	HIADP_HDMI_DeInit(HI_UNF_HDMI_ID_0);
#endif
ERR3:
	HI_UNF_DISP_Close(HI_UNF_DISPLAY1);
ERR2:
	HI_UNF_DISP_Detach(HI_UNF_DISPLAY0, HI_UNF_DISPLAY1);
ERR1:
	HI_UNF_DISP_DeInit();
ERR0:
	return Ret;
}

HI_S32 HI_ADP_GrcCreate(HI_UNF_PDM_DISP_PARAM_S *pstGrcParam, HI_HANDLE *phLayer, HI_HANDLE *phSurface)
{
	HI_S32 Ret;
	HIGO_LAYER_INFO_S stLayerInfo;
	HIGO_LAYER_E eLayerID = HIGO_LAYER_HD_0;

	if (HI_NULL == pstGrcParam)
	{
		HI_ERR_LOADER("invalid input parameter.\n");
		return HI_FAILURE;
	}

	Ret = HI_GO_Init();
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_GO_Init err! Ret = %x\n", Ret);
		return Ret;
	}

	Ret = HI_GO_GetLayerDefaultParam(eLayerID, &stLayerInfo);
  
    /* to self-adapt the base virtualScreen and loader display */
    stLayerInfo.ScreenHeight = pstGrcParam->u32VirtScreenHeight;
    stLayerInfo.ScreenWidth = pstGrcParam->u32VirtScreenWidth;
    stLayerInfo.CanvasHeight = pstGrcParam->u32VirtScreenHeight;
    stLayerInfo.CanvasWidth = pstGrcParam->u32VirtScreenWidth;
    stLayerInfo.DisplayHeight = pstGrcParam->u32VirtScreenHeight;
    stLayerInfo.DisplayWidth = pstGrcParam->u32VirtScreenWidth;

    stLayerInfo.PixelFormat = pstGrcParam->enPixelFormat;
    stLayerInfo.LayerFlushType = HIGO_LAYER_FLUSH_NORMAL;

	Ret = HI_GO_CreateLayer(&stLayerInfo, phLayer);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_GO_CreateLayer err! Ret = %x\n", Ret);
		HI_GO_Deinit();
		return Ret;
	}

	/*use single buffer, need not blit*/
	Ret = HI_GO_GetLayerSurface(*phLayer, phSurface);
	if (HI_SUCCESS != Ret)
	{
		HI_ERR_LOADER("HI_GO_GetLayerSurface err! Ret = %x\n", Ret);
		HI_GO_DestroyLayer(*phLayer);
		HI_GO_Deinit();
		return Ret;
	}

	return Ret;
}

HI_S32 Disp_Graphic_Init(HI_HANDLE *phLayer, HI_HANDLE *phSurface)
{
	HI_S32 s32Ret = HI_SUCCESS;
	HI_UNF_PDM_DISP_PARAM_S stDispParam;

	if ((HI_NULL == phLayer) || (HI_NULL == phSurface))
		return HI_FAILURE;

	memset(&stDispParam, 0, sizeof(stDispParam));

	s32Ret = HI_UNF_PDM_GetBaseParam(HI_UNF_PDM_BASEPARAM_DISP1, &stDispParam);
	if (HI_SUCCESS != s32Ret)
	{
		HI_INFO_LOADER("no found valid display parameter(0x%x), using default value!\n", s32Ret);
		GetDefDispParam(&stDispParam);
	}

	s32Ret = HI_ADP_DispInit(&stDispParam);
	if (HI_SUCCESS != s32Ret)
	{
		HI_ERR_LOADER("HI_ADP_DispInit failed, s32Ret = 0x%x\n", s32Ret);
		goto out;
	}

	s32Ret = HI_ADP_GrcCreate(&stDispParam, phLayer, phSurface);
	if (HI_SUCCESS != s32Ret)
	{
		HI_ERR_LOADER("HI_ADP_GrcCreate failed, s32Ret = 0x%x\n", s32Ret);
		goto out;
	}

out:
	return s32Ret;
}
