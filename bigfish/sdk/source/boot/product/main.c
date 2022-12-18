/******************************************************************************
 *    Copyright (c) 2009-2012 by Hisi.
 *    All rights reserved.
 * ***
 *    Create by Czyong. 2012-09-07
 *
******************************************************************************/

#include <uboot.h>
#include "hi_type.h"
#include "hi_unf_disp.h"
#include "hi_drv_pdm.h"
#include "hi_drv_pq.h"
#include "hi_boot_logo.h"
#include "hi_boot_adp.h"
#include "schedule.h"
#include "hi_common.h"
#include "hi_unf_otp.h"

#ifdef HI_ADVCA_FUNCTION_RELEASE
#include "ca_pub.h"
#endif

#ifdef HI_ADVCA_TYPE_NAGRA
extern HI_VOID HI_NASC_SBP_Process(HI_VOID);
#endif

extern int Android_Qb_CheckRemote(void);

#define IO_ADDRESS(addr) (addr)

/******************************************************************************/
static HI_HANDLE                   g_hSurface;
static HI_HANDLE                   g_hLayer;
static HI_BOOL                     g_bDisplayInit = HI_FALSE;
static HI_DISP_PARAM_S             g_stDispParam0;
static HI_DISP_PARAM_S             g_stDispParam1;

/*logo and loader both need call this function, but we only need init display once*/
HI_S32 PRODUCT_DisplayInit(HI_HANDLE *phLayer, HI_HANDLE *phSurface)
{
    HI_S32 Ret;

    if ((HI_NULL == phLayer) || (HI_NULL == phSurface))
    {
        return HI_FAILURE;
    }

    if (g_bDisplayInit)
    {
        *phLayer   = g_hLayer;
        *phSurface = g_hSurface;
        return HI_SUCCESS;
    }

    Ret = HI_ADP_DispInit();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_ADP_DispInit err! Ret = %x\n", Ret);
        return Ret;
    }

    Ret = HI_ADP_GrcCreate(g_stDispParam1.enPixelFormat, phLayer, phSurface, HIGO_LAYER_HD_1);
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_MCE("HI_ADP_GrcCreate err! Ret = %x\n", Ret);
        return Ret;
    }

    g_bDisplayInit = HI_TRUE;

    g_hLayer = *phLayer;
    g_hSurface = *phSurface;

    return Ret;
}

HI_S32 Logo_Main(HI_BOOL bNeedFastplay)
{
    HI_S32                      Ret;
    HI_LOGO_PARAM_S             stLogoParam;
    HI_U32                      u32LogoDataAddr;
#ifdef HI_MCE_SUPPORT
    HI_MCE_PARAM_S              stMceParam;
    HI_U32                      u32PlayDataAddr;
#endif
    HI_HANDLE                   hLayer;
    HI_HANDLE                   hLayerSurface;
    HI_HANDLE                   hDecSurface = HI_INVALID_HANDLE;
    HIGO_BLTOPT_S               pBlitOpt = {0};

    Ret = HI_DRV_PDM_GetDispParam(HI_UNF_DISPLAY0, &g_stDispParam0);
    Ret |= HI_DRV_PDM_GetDispParam(HI_UNF_DISPLAY1, &g_stDispParam1);
    if(HI_SUCCESS != Ret)
    {
        HI_INFO_MCE("HI_PDM_GetGrcParam err! Ret = %x\n", Ret);
        return Ret;
    }

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    HI_UNF_HDMI_Init();

    if (g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI &&
        g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].unIntf.enHdmi == HI_UNF_HDMI_ID_0){
        HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, g_stDispParam1.enFormat);
    }
#endif

    Ret = HI_DRV_PDM_GetLogoParam(&stLogoParam);
    /*if logo is open*/
    if (HI_SUCCESS == Ret && 1 == stLogoParam.u32CheckFlag)
    {
        /*we only init display when logo is open*/
        Ret = PRODUCT_DisplayInit(&hLayer, &hLayerSurface);
        if(HI_SUCCESS != Ret)
        {
            HI_INFO_MCE("PRODUCT_DisplayInit err! Ret = %x\n", Ret);
            return Ret;
        }

        Ret = HI_DRV_PDM_GetLogoData(stLogoParam.u32LogoLen, &u32LogoDataAddr);

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
        if (g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI &&
            g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].unIntf.enHdmi == HI_UNF_HDMI_ID_0){
            HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, g_stDispParam1.enFormat);
        }
#endif

        if(HI_SUCCESS == Ret)
        {
            Ret = HI_LOGO_DecImg(stLogoParam, u32LogoDataAddr, &hDecSurface);
            if(HI_SUCCESS != Ret)
            {
                HI_INFO_MCE("HI_LOGO_DecImg err! Ret = %x\n", Ret);
                goto FREE_SURFACE;
            }

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
            if (g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI &&
                g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].unIntf.enHdmi == HI_UNF_HDMI_ID_0){
                HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, g_stDispParam1.enFormat);
            }
#endif
            pBlitOpt.EnableScale = HI_TRUE;
            Ret = HI_GO_Blit(hDecSurface, NULL, hLayerSurface, NULL, &pBlitOpt);
            if(HI_SUCCESS != Ret)
            {
                HI_INFO_MCE("HI_GO_Blit err! Ret = %x\n", Ret);
                goto FREE_SURFACE;
            }

            Ret = HI_GO_RefreshLayer(hLayer, NULL);
            if(HI_SUCCESS != Ret)
            {
                HI_INFO_MCE("HI_GO_RefreshLayer err! Ret = %x\n", Ret);
                goto FREE_SURFACE;
            }

#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
            if (g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].enIntfType == HI_UNF_DISP_INTF_TYPE_HDMI &&
                g_stDispParam1.stIntf[HI_UNF_DISP_INTF_TYPE_HDMI].unIntf.enHdmi == HI_UNF_HDMI_ID_0){
                HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0, g_stDispParam1.enFormat);
            }
#endif

            //non-homologous
            if (g_stDispParam0.enSrcDisp != HI_UNF_DISPLAY1)
            {
                HI_HANDLE                   hLayer0;
                HI_HANDLE                   hLayerSurface0;

                Ret = HI_ADP_GrcCreate(g_stDispParam0.enPixelFormat, &hLayer0, &hLayerSurface0, HIGO_LAYER_SD_1);
                if (HI_SUCCESS != Ret)
                {
                    HI_INFO_MCE("Create SD Layer failure! Ret = %x\n", Ret);
                    goto FREE_SURFACE;
                }

                pBlitOpt.EnableScale = HI_TRUE;
                Ret = HI_GO_Blit(hDecSurface, NULL, hLayerSurface0, NULL, &pBlitOpt);
                if(HI_SUCCESS != Ret)
                {
                    HI_INFO_MCE("HI_GO_Blit err! Ret = %x\n", Ret);
                    goto FREE_SURFACE;
                }

                Ret = HI_GO_RefreshLayer(hLayer0, NULL);
                if(HI_SUCCESS != Ret)
                {
                    HI_INFO_MCE("HI_GO_RefreshLayer err! Ret = %x\n", Ret);
                }
            }

FREE_SURFACE:
            if (HI_INVALID_HANDLE != hDecSurface)
            {
                HI_GO_FreeSurface(hDecSurface);
            }
        }
    }

#ifdef HI_MCE_SUPPORT
    if (bNeedFastplay)
    {
        Ret = HI_DRV_PDM_GetMceParam(&stMceParam);
        if (HI_SUCCESS == Ret && 1 == stMceParam.u32CheckFlag)
        {
            if (0 != stMceParam.u32PlayDataLen)
            {
                Ret = HI_DRV_PDM_GetMceData(stMceParam.u32PlayDataLen, &u32PlayDataAddr);
            }
        }
    }
#endif

    HI_INFO_MCE("boot logo show!!!\n");

    return Ret;
}

HI_VOID SetLogLevel(HI_VOID)
{

#ifndef HI_ADVCA_FUNCTION_RELEASE

    HI_CHAR         *pLogLevel = HI_NULL;
    HI_U32          LogLevel = 1;
    HI_CHAR         aszEnvName[64];
    HI_S32          i;
    const HI_CHAR   *pszName;

    HI_LOG_Init();

    pLogLevel = getenv("loglevel");
    if (HI_NULL == pLogLevel)
    {
        HI_LOG_SetLevel(HI_ID_BUTT, 0);
    }
    else
    {
        LogLevel = simple_strtoul_2(pLogLevel, NULL, 10);
        if (LogLevel > HI_TRACE_LEVEL_DBG)
        {
            HI_LOG_SetLevel(HI_ID_BUTT, 0);
        }
        else
        {
            HI_LOG_SetLevel(HI_ID_BUTT, LogLevel);
        }
    }

    for (i=0; i<HI_ID_BUTT; i++)
    {
        pszName = HI_LOG_GetModuleName(i);
        if ((HI_NULL != pszName) && (strlen(pszName) > 0))
        {
            HI_OSAL_Snprintf(aszEnvName, sizeof(aszEnvName), "loglevel-%s", pszName, sizeof(aszEnvName));
            pLogLevel = getenv(aszEnvName);
            if (HI_NULL != pLogLevel)
            {
                LogLevel = simple_strtoul_2(pLogLevel, NULL, 10);
                if (LogLevel > HI_TRACE_LEVEL_DBG)
                {
                    LogLevel = 0;
                }
                HI_LOG_SetLevel(i, LogLevel);
            }
        }
    }

#endif
    return;
}

#ifdef HI_ADVCA_TYPE_VERIMATRIX
extern HI_S32 HI_CA_AuthenticateEntry_VMX(HI_VOID);
#endif

HI_S32 product_init(HI_VOID)
{
#if defined(CHIP_TYPE_hi3798mv100) || defined(CHIP_TYPE_hi3796mv100)
    HI_OTP_LockIdWord();

#ifdef HI_BOOT_IR_SUPPORT
    register_hibernate_cancel(Android_Qb_CheckRemote);
#endif
#endif

    return HI_SUCCESS;
}

#ifdef CHIP_TYPE_hi3798cv200_a
#define MCI_REG_BASE       ((0xF9A00000))
#define CHAN0_CIPHER_DOUT1  (MCI_REG_BASE + 0x00)
#define CHAN0_CIPHER_DOUT2  (MCI_REG_BASE + 0x04)
#define CHAN0_CIPHER_DOUT3  (MCI_REG_BASE + 0x08)
#define CHAN0_CIPHER_DOUT4  (MCI_REG_BASE + 0x0c)
#define HDCP_MODE_CTRL      (MCI_REG_BASE + 0x0820)
#define SEC_CHN_CFG         (MCI_REG_BASE + 0x0824)
#define CHAN0_CIPHER_CTRL   (MCI_REG_BASE + 0x1000)
#define CHAN0_CIPHER_IVIN   (MCI_REG_BASE + 0x1004)
#define CHAN0_CIPHER_DIN1   (MCI_REG_BASE + 0x1014)
#define CHAN0_CIPHER_DIN2   (MCI_REG_BASE + 0x1018)
#define CHAN0_CIPHER_DIN3   (MCI_REG_BASE + 0x101c)
#define CHAN0_CIPHER_DIN4   (MCI_REG_BASE + 0x1020)
#define CHAN0_CFG           (MCI_REG_BASE + 0x1410)

#define  CRG_BASE_ADDR_PHY  ((0xF8A22000))
#define  MCI_SOFT_RESET_REG (CRG_BASE_ADDR_PHY + 0xC0)

#define  WRITE_MCI_REG(Addr, Value) ((*(volatile HI_U32 *)(Addr)) = (Value))
#define  READ_MCI_REG(Addr)         (*(volatile HI_U32 *)(Addr))

void CipherWriteData(HI_U32 addr, HI_U32 *au32Val)
{
    HI_U32 i;

    for(i=0; i<4; i++)
    {
        WRITE_MCI_REG(addr+i*4,au32Val[i]);
    }
}

void CipherReadData(HI_U32 addr, HI_U32 *au32Val)
{
    HI_U32 i;

    for(i=0; i<4; i++)
    {
        au32Val[i] = READ_MCI_REG(addr+i*4);
    }
}

HI_S32 CipherHdcpKeyInit(HI_U8 *pu8HpcpKey)
{
    HI_S32  ret;
    HI_U32  i;
    HI_U32  j;
    HI_U32  u32Value;
    HI_U32  u32Key[32][4];

    //printf("------ 0xf8ce0028=0x%x ------\n", READ_MCI_REG(0xf8ce0028));

    /*Cipher soft reset*/
    u32Value = READ_MCI_REG(MCI_SOFT_RESET_REG);
    u32Value |= 0x00200;
    WRITE_MCI_REG(MCI_SOFT_RESET_REG,u32Value);
    udelay(20*1000);
    u32Value &= ~0x00200;
    WRITE_MCI_REG(MCI_SOFT_RESET_REG,u32Value);
    udelay(20*1000);

    /*channl 0 secure*/
    //u32Value = 0x01;
    //WRITE_MCI_REG(SEC_CHN_CFG, u32Value);

    /*Set mode*/
    u32Value = 0x1;
    WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

    /*Hdcp key encrypt*/
    for (i = 0; i < 32; i++)
    {
        /*Set input data*/
        u32Key[i][0] = (pu8HpcpKey[16*i+3]<<24)|(pu8HpcpKey[16*i+2]<<16)|(pu8HpcpKey[16*i+1]<<8)|((pu8HpcpKey[16*i]<<0));
        u32Key[i][1] = (pu8HpcpKey[16*i+7]<<24)|(pu8HpcpKey[16*i+6]<<16)|(pu8HpcpKey[16*i+5]<<8)|((pu8HpcpKey[16*i+4]<<0));
        u32Key[i][2] = (pu8HpcpKey[16*i+11]<<24)|(pu8HpcpKey[16*i+10]<<16)|(pu8HpcpKey[16*i+9]<<8)|((pu8HpcpKey[16*i+8]<<0));
        u32Key[i][3] = (pu8HpcpKey[16*i+15]<<24)|(pu8HpcpKey[16*i+14]<<16)|(pu8HpcpKey[16*i+13]<<8)|((pu8HpcpKey[16*i+12]<<0));
        CipherWriteData(CHAN0_CIPHER_DIN1, u32Key[i]);

        /*Set ctrl*/
        if (i == 0)
        {
            u32Value = 0x122;
            memset(u32Key[0], 0, 16);
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt
            CipherWriteData(CHAN0_CIPHER_IVIN, u32Key[0]);
        }
        else
        {
            u32Value = 0x22;
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt
        }

        /*start encrypt*/
        u32Value = 0x01;
        WRITE_MCI_REG(CHAN0_CFG, u32Value);

        /*Wait encrypt end*/
        u32Value = READ_MCI_REG(CHAN0_CFG);
        while (u32Value & 0x02)
        {
            u32Value = READ_MCI_REG(CHAN0_CFG);
        }

        /*Get result*/
        CipherReadData(CHAN0_CIPHER_DOUT1, u32Key[i]);
		
#if 0
        printf("u32Key[%02d]: ", i);
        for(j=0; j<4; j++)
        {
            printf("%08x ", u32Key[i][j]);
        }
        printf("\n");
#endif
    }

    u32Value = 0x1;
    WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

    /*Hdcp key decrypt*/
    for (i = 0; i < 32; i++)
    {
        /*Set input data*/
        CipherWriteData(CHAN0_CIPHER_DIN1, u32Key[i]);

        /*Set ctrl*/
        if(i == 0)
        {
            u32Value = 0x123;
            memset(u32Key[0], 0, 16);
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt
            CipherWriteData(CHAN0_CIPHER_IVIN, u32Key[0]);
        }
        else
        {
            u32Value = 0x23;
            WRITE_MCI_REG(CHAN0_CIPHER_CTRL, u32Value);//aes-cbc, encrypt
        }

        /*start decrypt*/
        u32Value = 0x01;
        WRITE_MCI_REG(CHAN0_CFG, u32Value);//start decrypt

        /*Wait decrypt end*/
        u32Value = READ_MCI_REG(CHAN0_CFG);
        while(u32Value & 0x02)
        {
            u32Value = READ_MCI_REG(CHAN0_CFG);
        }
    }

    u32Value = 0x2;
    WRITE_MCI_REG(HDCP_MODE_CTRL, u32Value);//use otp hdcp root key

#if 0
    WRITE_MCI_REG(0xF8A2210c, 0x433f);
    udelay(20 * 1000);
    WRITE_MCI_REG(0xF8A2210c, 0x403f);
    udelay(1000);

    printf("\n\n0xf8ce0028=0x%x\n", READ_MCI_REG(0xf8ce0028));
#endif

    return HI_SUCCESS;
}

static HI_U8 Keys[512] = {0};
#endif

int fastapp_entry(int argc, char *argv[])
{
    HI_S32 Ret = HI_SUCCESS;

#ifdef CHIP_TYPE_hi3798cv200_a
    Keys[510] = 0x00;
    Keys[511] = 0xff;

    printf("----- Keys[510]=0x%x -----\n\n", Keys[510]);
    
    CipherHdcpKeyInit(Keys);
#endif

    SetLogLevel();

    HI_PRINT("\nSDK Version: %s\n\n", SDK_VERSION_STRING);

#ifdef HI_PM_POWERUP_MODE1_SUPPORT
    boot_suspend();
#endif

    HI_PQ_Init();

#ifdef HI_HDMI_EDID_SUPPORT
    Ret = HI_UNF_HDMI_SetBaseParamByEDID();
    if(HI_SUCCESS != Ret)
    {
        HI_INFO_PRINT(HI_ID_SYS, "SetBaseParamByEDID err! Ret = %x\n", Ret);
    }
#endif

#ifdef HI_ADVCA_TYPE_NAGRA
    HI_NASC_SBP_Process();
    return 0;
#endif

#ifndef  HI_ADVCA_FUNCTION_RELEASE
    Logo_Main(HI_TRUE);
#endif

    HI_DRV_PDM_SetTagData();

#ifdef HI_ADVCA_TYPE_VERIMATRIX
    HI_CA_AuthenticateEntry_VMX();
#else
#ifdef  HI_ADVCA_FUNCTION_RELEASE
    HI_CA_AuthenticateEntry();
#endif
#endif

#ifndef HI_MINIBOOT_SUPPORT
#if defined(CONFIG_BOOTROM_SUPPORT)
    selfboot_init();

#ifdef HI_ADVCA_USB_BURN_KEY
    Android_Security_WriteRSAKey();
#endif

    selfboot_from_udisk(NULL);
#endif
#endif

#ifdef HI_ANDROID_BOOT_SUPPORT
    Android_Main();
#endif

#ifndef HI_ADVCA_SUPPORT
#ifdef HI_LOADER_SUPPORT
    Loader_Main();
#else
    HI_INFO_PRINT(HI_ID_SYS, "not support hisi loader!\n");
#endif
#endif

#ifdef HI_ADVCA_SUPPORT
    c51_loadCode();
#endif

    return 0;
}
