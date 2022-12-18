/******************************************************************************

  Copyright (C), 2011-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hal_advca_v300.c
  Version       : Initial Draft
  Author        : Hisilicon hisecurity team
  Created       : 
  Last Modified :
  Description   : 
  Function List :
  History       :

******************************************************************************/
#include "drv_advca_internal.h"
#include "drv_advca_external.h"

#define ADVCA_MAGIC_NUM1 (0xa843dcad)
#define ADVCA_MAGIC_NUM2 (0x12f02456)

CA_KEYLADDER_INFO_S g_CSA2Info = {0};
CA_KEYLADDER_INFO_S g_CSA3Info = {0};
CA_KEYLADDER_INFO_S g_R2RInfo  = {0};
CA_KEYLADDER_INFO_S g_SPInfo   = {0};
CA_KEYLADDER_INFO_S g_MiscInfo = {0};
CA_KEYLADDER_INFO_S g_DCASInfo = {0};
CA_KEYLADDER_INFO_S g_TAInfo   = {0};
CA_KEYLADDER_INFO_S g_GDRMInfo = {0};

static HI_BOOL g_IsSWPKKeyLadderOpen = HI_FALSE;

HI_U32 HAL_ADVCA_V300_Open(HI_VOID)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKLadder = HI_UNF_ADVCA_KEYLADDER_BUTT;
    
    memset(&g_CSA2Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_CSA2Info.OpenFlag = HI_TRUE;
    g_CSA2Info.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    (HI_VOID)HAL_ADVCA_V300_GetCWLadderLevel(&enKLadder);
    g_CSA2Info.MaxLevel = enKLadder + 1;
	
    memset(&g_CSA3Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_CSA3Info.OpenFlag = HI_TRUE;
    g_CSA3Info.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    (HI_VOID)HAL_ADVCA_V300_GetCSA3LadderLevel(&enKLadder);
    g_CSA3Info.MaxLevel = enKLadder + 1;
    
    memset(&g_R2RInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_R2RInfo.OpenFlag = HI_TRUE;
    g_R2RInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    (HI_VOID)HAL_ADVCA_V300_GetR2RLadderLevel(&enKLadder);
    g_R2RInfo.MaxLevel = enKLadder + 1;
    
    memset(&g_SPInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_SPInfo.OpenFlag = HI_FALSE;
    g_SPInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_SPInfo.enDscMode = HI_UNF_ADVCA_SP_DSC_MODE_PAYLOAD_AES_CBC_IDSA;
    (HI_VOID)HAL_ADVCA_V300_GetSPLadderLevel(&enKLadder);
    g_SPInfo.MaxLevel = enKLadder + 1;
    
    memset(&g_MiscInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_MiscInfo.OpenFlag = HI_FALSE;
    g_MiscInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    (HI_VOID)HAL_ADVCA_V300_GetMiscKlLevel(&enKLadder);
    g_MiscInfo.MaxLevel = enKLadder + 1;
    
    memset(&g_DCASInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_DCASInfo.OpenFlag = HI_FALSE;
    g_DCASInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_DCASInfo.MaxLevel = 0x03;

    memset(&g_TAInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_TAInfo.OpenFlag = HI_FALSE;
    g_TAInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    g_TAInfo.MaxLevel = 0x03;    //Fixed to 3 level in Transformation Algorithm keyladder

    memset(&g_GDRMInfo, 0x0, sizeof (CA_KEYLADDER_INFO_S));
    g_GDRMInfo.OpenFlag = HI_FALSE;
    g_GDRMInfo.MaxLevel = 0x03;
    
    return HI_SUCCESS;
}

HI_U32 HAL_ADVCA_V300_Close(HI_VOID)
{
    memset(&g_CSA2Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_CSA3Info, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_R2RInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_SPInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_MiscInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_DCASInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_TAInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    memset(&g_GDRMInfo, 0, sizeof(CA_KEYLADDER_INFO_S));

    return HI_SUCCESS;
}

static HI_S32 HAL_ADVCA_V300_WaitStat(HI_VOID)
{
    HI_U32 cnt = 0;
    CA_V300_CA_STATE_U CAStatus;
    HI_S32 errState = 0;
    
    /* wait for KeyLadder calc done */
    // corform one value when test, about 500
    while (cnt < 50)
    {
        CAStatus.u32 = 0;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        if (CAStatus.bits.klad_busy == 0)
        {
            HI_INFO_CA("ca_decrypted finished, cnt:%d\n", cnt);
            break;
        }
        ca_msleep(10);
        cnt++;
    }

    if (cnt >= 50)
    {
        HI_ERR_CA("\n Error CA handle too long !!!!!!!!!!! \n");
        return HI_FAILURE;      /* time out */
    }

    /* not support 'last_key_not_rdy' */
    errState = CAStatus.bits.err_state;
    return errState;
}


HI_S32 HAL_ADVCA_V300_StatHardCwSel(HI_U32 *pu32Lock)
{
    HI_S32 Ret = HI_SUCCESS;
    
    if (pu32Lock == NULL)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    //Get the OTP bit "ts_csa2_hardonly_en"
    Ret = DRV_CA_OTP_V200_GetTSCsa2HardonlyEn(pu32Lock);

    return Ret;
}


HI_S32 HAL_ADVCA_V300_StatR2RHardKey(HI_U32 *pu32Lock)
{
    if (pu32Lock == NULL)
    {
        return HI_ERR_CA_INVALID_PARA;
    }
    //R2R decryption ladder lock.
    //*pbLock = g_pCaReg->CaCtrlProc.Bits.R2rHKeyLock;
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_StatTdesLock(HI_U32 *pu32Lock)
{
    if (pu32Lock == NULL)
    {
        return HI_ERR_CA_INVALID_PARA;
    }
    //Whether to lock the multicipher to enable it to use the TDES rather than the DES.
    //*pbLock = g_pCaReg->CaCtrlProc.Bits.TdesLock;
    return HI_SUCCESS;    
}

HI_S32 HAL_ADVCA_V300_SetCWLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;
    
    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetCSA2LadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_CSA2Info.MaxLevel = enSel;
    }
    
    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetCWLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetCSA2LadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;
    
    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetR2RLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;
    
    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetR2RLadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_R2RInfo.MaxLevel = enSel;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetR2RLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetR2RLadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;
    
    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetSPLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;
    
    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetSPLadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_SPInfo.MaxLevel = enSel;
    }
    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetSPLadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetSPLadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;
    
    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetCSA3LadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;
    
    if ((enSel != HI_UNF_ADVCA_KEYLADDER_LEV3) && (enSel != HI_UNF_ADVCA_KEYLADDER_LEV2))
    {
        HI_ERR_CA("CW ladder err, sel = %d ! \n", enSel);
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyLevel = (CA_OTP_KEY_LEVEL_E)enSel;
    Ret = DRV_CA_OTP_V200_SetCSA3LadderLevel(enKeyLevel);
    if(Ret == HI_SUCCESS)
    {
        g_CSA3Info.MaxLevel = enSel;
    }    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetCSA3LadderLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_OTP_KEY_LEVEL_E enKeyLevel;

    if (NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetCSA3LadderLevel(&enKeyLevel);
    *penSel = (HI_UNF_ADVCA_KEYLADDER_LEV_E)enKeyLevel;
    
    return Ret;
}


HI_S32 HAL_ADVCA_V300_SetCWAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E type)
{
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid CSA2 Keyladder Algorithm (%d)!\n", type);
        return HI_ERR_CA_INVALID_PARA;
    }    
    g_CSA2Info.Alg = type;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetCWAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *pAlgType)
{
    if(pAlgType == NULL)
    {
        HI_ERR_CA("pAlgType: NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }
    *pAlgType = g_CSA2Info.Alg;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetCSA3Algorithm(HI_UNF_ADVCA_ALG_TYPE_E type)
{
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid CSA3 Keyladder Algorithm (%d)!\n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
	g_CSA3Info.Alg = type;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetCSA3Algorithm(HI_UNF_ADVCA_ALG_TYPE_E *pAlgType)
{
    if(pAlgType == NULL)
    {
        HI_ERR_CA("pAlgType: NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    *pAlgType = g_CSA3Info.Alg;
    return HI_SUCCESS;
}


HI_S32 HAL_ADVCA_V300_SetR2RAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E type)
{
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("R2R Algorithm Error = %d ! \n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_R2RInfo.Alg = type;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetR2RAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *type)
{
    *type = g_R2RInfo.Alg;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetSPAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid SP Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_SPInfo.Alg = enType;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSPAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    *penType = g_SPInfo.Alg;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetMiscAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid Misc Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_MiscInfo.Alg = enType;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetMiscAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    if( NULL == penType)
    {
        HI_ERR_CA("Invalid param ,NULL pointer !\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    *penType = g_MiscInfo.Alg;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E enSel)
{
    HI_U32 Ret = HI_SUCCESS;
    Ret = DRV_CA_OTP_V200_SetMiscKlLevel(enSel);
    if(Ret == HI_SUCCESS)
    {
        g_MiscInfo.MaxLevel = enSel;
    }
    return Ret;
}

HI_S32 HAL_ADVCA_V300_GetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    if(NULL == penSel)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    return DRV_CA_OTP_V200_GetMiscKlLevel(penSel);
}

HI_S32 HAL_ADVCA_V300_SetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E eDscMode)
{
    if (eDscMode >= HI_UNF_ADVCA_SP_DSC_MODE_BUTT)
    {
        HI_ERR_CA("Invaild SP Dsc Mode (%d )!\n", eDscMode);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_SPInfo.enDscMode = eDscMode;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSPDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *penType)
{
    *penType = g_SPInfo.enDscMode;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetMiscDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E eDscMode)
{
    if (eDscMode >= HI_UNF_ADVCA_SP_DSC_MODE_BUTT)
    {
        HI_ERR_CA("Invaild SP Dsc Mode (%d )!\n", eDscMode);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_MiscInfo.enDscMode = eDscMode;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetMiscDscMode(HI_UNF_ADVCA_SP_DSC_MODE_E *penType)
{
    *penType = g_MiscInfo.enDscMode;
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptCw(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bEvenOrOdd)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CSA2_CTRL_U      CSA2Ctrl;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLev;
    
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_GetCWLadderLevel(&enKeyladderLev);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CW ladder level.\n");
        return HI_FAILURE;
    }

    //(1)	�ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //For Irdeto MSR2.2 chipset
    {
        HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV3, pu32DataIn, 16);        
    }
    else
    {    
        /*2  put DVB_RootKey��CK2��to CA register(DATA input) */
        //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    }
    
    //(3)	���üĴ���CSA2_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    CSA2Ctrl.u32 = 0;
    CSA2Ctrl.bits.dsc_mode = 0;
    CSA2Ctrl.bits.level_sel = enLevel;
    CSA2Ctrl.bits.tdes_aes_sel = g_CSA2Info.Alg;
    CSA2Ctrl.bits.EvenOrOdd = bEvenOrOdd;  //0����ǰ��ż��Կ��1����ǰ������Կ
    CSA2Ctrl.bits.key_addr = AddrID & 0x7F; //Demux DescambleKey ID
    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //last level
    {
        CSA2Ctrl.bits.ta_kl_flag = 1; //for Irdeto MSR2.2
    }
    DRV_ADVCA_WriteReg(CA_V300_CSA2_CTRL, CSA2Ctrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (DVB_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("Cw key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }
    DRV_ADVCA_Wait(100);
#if 0
    //����Ľ���鿴�м����Ĵ���KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_KEY_DOUT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }    
#endif

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);
        memcpy(g_CSA2Info.SessionKey[enLevel], pu32DataIn, 16);
        g_CSA2Info.SessionKey_sec[enLevel] = tv.tv_sec;

        g_CSA2Info.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        
        //0����ǰ��ż��Կ��1����ǰ������Կ
        if(g_CSA2Info.MaxLevel == (enLevel + 1))
        {
            if(bEvenOrOdd == 0x00)
            {
                memcpy(g_CSA2Info.LastEvenKey, pu32DataIn, 16);
                g_CSA2Info.LastEvenKey_secTime = tv.tv_sec;
            }
            else
            {
                memcpy(g_CSA2Info.LastOddKey, pu32DataIn, 16);
                g_CSA2Info.LastOddKey_secTime = tv.tv_sec;
            }
        }
    }
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptCsa3(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bEvenOrOdd)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CSA3_CTRL_U CSA3Ctrl;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLev;

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_GetCSA3LadderLevel(&enKeyladderLev);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CW ladder level.\n");
        return HI_FAILURE;
    }    
    
    //(1)	�ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    
    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //For Irdeto MSR2.2
    {
        HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV3, pu32DataIn, 16);        
    }
    else
    {
        /*2  put DVB_RootKey��CK2��to CA register(DATA input) */
        //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    }
    
    //(3)	���üĴ���CSA3_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    CSA3Ctrl.u32 = 0;
    CSA3Ctrl.bits.dsc_mode = 0x10;
    CSA3Ctrl.bits.level_sel = enLevel;
    CSA3Ctrl.bits.tdes_aes_sel = g_CSA3Info.Alg;
    CSA3Ctrl.bits.EvenOrOdd = bEvenOrOdd;
    CSA3Ctrl.bits.key_addr = AddrID & 0x7F; //Demux DescambleKey ID
    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //last level
    {
        CSA3Ctrl.bits.ta_kl_flag = 1; //for Irdeto MSR2.2
    }    
    DRV_ADVCA_WriteReg(CA_V300_CSA3_CTRL, CSA3Ctrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (DVB_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("CSA3 key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }
    DRV_ADVCA_Wait(100);
#if 0
    //����Ľ���鿴�м����Ĵ���KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_KEY_DOUT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }    
#endif

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);
        memcpy(g_CSA3Info.SessionKey[enLevel], pu32DataIn, 16);
        g_CSA3Info.SessionKey_sec[enLevel] = tv.tv_sec;
        
        g_CSA3Info.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        
        //0����ǰ��ż��Կ��1����ǰ������Կ
        if(g_CSA3Info.MaxLevel == (enLevel + 1))
        {
            if(bEvenOrOdd == 0x00)
            {
                memcpy(g_CSA3Info.LastEvenKey, pu32DataIn, 16);
                g_CSA3Info.LastEvenKey_secTime = tv.tv_sec;
            }
            else
            {
                memcpy(g_CSA3Info.LastOddKey, pu32DataIn, 16);
                g_CSA3Info.LastOddKey_secTime = tv.tv_sec;
            }
        }
    }
    
    return HI_SUCCESS;
}


HI_S32 HAL_ADVCA_V300_CryptR2R(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bIsDeCrypt)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_R2R_CTRL_U R2RCtrl;

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    if(g_IsSWPKKeyLadderOpen)
    {
        HAL_ADVCA_V300_DecryptSWPK(pu32DataIn, AddrID);
        return HI_SUCCESS;
    }
    
    //(1)	�ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /*2  put DVB_RootKey��CK2��to CA register(DATA input) */
    //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    //(3)	���üĴ���R2R_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    R2RCtrl.u32 = 0;
    R2RCtrl.bits.level_sel = enLevel;
    R2RCtrl.bits.mc_alg_sel = 0;//Multicipher Algorithm. default setting
    R2RCtrl.bits.tdes_aes_sel = g_R2RInfo.Alg;
    R2RCtrl.bits.key_addr = AddrID & 0xFF; //Demux DescambleKey ID
    DRV_ADVCA_WriteReg(CA_V300_R2R_CTRL, R2RCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0 
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (R2R_SP_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("R2R key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }
    DRV_ADVCA_Wait(100);
#if 0
    //����Ľ���鿴�м����Ĵ���KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_KEY_DOUT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }    
#endif

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);
        memcpy(g_R2RInfo.SessionKey[enLevel], pu32DataIn, 16);
        g_R2RInfo.SessionKey_sec[enLevel] = tv.tv_sec;

        g_R2RInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        
    }
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptSP(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
								HI_U32 *pu32DataIn,
								HI_U32 AddrID,
								HI_BOOL bEvenOrOdd,
								DRV_ADVCA_CA_TARGET_E enCwTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_SP_CTRL_U unSPCtrl;
    HI_U32 u32KlStatus = 0;
    CA_OTP_VENDOR_TYPE_E enCaVendorType = CA_OTP_VENDOR_NONE;   
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKeyladderLev;

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    Ret = DRV_CA_OTP_V200_GetVendorId(&enCaVendorType);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CA vendor ID.\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_GetSPLadderLevel(&enKeyladderLev);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_CA("Failed to get the CW ladder level.\n");
        return HI_FAILURE;
    }
    
    //(1)	�ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        u32KlStatus = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        HI_ERR_CA("Keyladder is busy now! Keyladder status: 0x%08x\n", u32KlStatus);
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel) //For Irdeto MSR2.2
    {
        HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV3, pu32DataIn, 16);        
    }
    else
    {
        /*2  put SPE_RootKey��CK2��to CA register(DATA input) */
        //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    }
    
    //(3)	���üĴ���SP_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    unSPCtrl.u32 = 0;
	if(HI_UNF_ADVCA_KEYLADDER_LEV5 == enLevel)
	{
		unSPCtrl.bits.level_sel_5 = 1;
	}
	else
	{
		unSPCtrl.bits.level_sel = enLevel;
	}

    unSPCtrl.bits.tdes_aes_sel = g_SPInfo.Alg;
	if(enCwTarget == DRV_ADVCA_CA_TARGET_DEMUX)
    {
	    if (0 == (g_SPInfo.enDscMode & 0x4000))
	    {
	        unSPCtrl.bits.raw_mode = 0;          //payloadģʽ
	        unSPCtrl.bits.key_addr = ((AddrID & 0x7F) << 1) + bEvenOrOdd; //Demux DescambleKey ID + even_or_odd
	        unSPCtrl.bits.dsc_mode = g_SPInfo.enDscMode;  //set demux DscMode
	    }
	    else
	    {
	        unSPCtrl.bits.raw_mode = 1;          //rawģʽ
	        unSPCtrl.bits.key_addr = AddrID & 0xFF; //multicipher channel ID    
	    }
	}
	else
	{
        unSPCtrl.bits.raw_mode = 1;          //rawģʽ
        unSPCtrl.bits.key_addr = AddrID & 0xFF; //multicipher channel ID 		
	}
	
    if (enCaVendorType == CA_OTP_VENDOR_IRDETO && g_TAInfo.OpenFlag == HI_TRUE
        && enKeyladderLev == enLevel)
    {
        unSPCtrl.bits.ta_kl_flag = 1; //for Irdeto MSR2.2
    }	
    
    DRV_ADVCA_WriteReg(CA_V300_SP_CTRL, unSPCtrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0 
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (R2R_SP_SYMMETRIC_KEY_ERROR == Ret)
    {
        HI_ERR_CA("SP key ladder error: symmetric key usage\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }
    DRV_ADVCA_Wait(100);
#if 0
    //����Ľ���鿴�м����Ĵ���KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_KEY_DOUT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }    
#endif

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);
        memcpy(g_SPInfo.SessionKey[enLevel], pu32DataIn, 16);
        g_SPInfo.SessionKey_sec[enLevel] = tv.tv_sec;

        g_SPInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
                
        //0����ǰ��ż��Կ��1����ǰ������Կ
        if(g_SPInfo.MaxLevel == (enLevel + 1))
        {
            if(bEvenOrOdd == 0x00)
            {
                memcpy(g_SPInfo.LastEvenKey, pu32DataIn, 16);
                g_SPInfo.LastEvenKey_secTime = tv.tv_sec;
            }
            else
            {
                memcpy(g_SPInfo.LastOddKey, pu32DataIn, 16);
                g_SPInfo.LastOddKey_secTime = tv.tv_sec;
            }
        }
    }
   
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptLpk(HI_U32 *pEncryptLpk)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_LP_CTRL_U LPCtrl;
    
    /* Only use in Conax CA
       Use R2R Root Key as the top key.
       Set First Level LPK protect key, Algorithm:TDES
       After decramble, result same in parameter�Ĵ�����	0x50~0x5C
    */

    /* 0.if support to LPK */
    
    
    /* para check*/
    if (HI_NULL == pEncryptLpk)
    {
       HI_ERR_CA("HI_NULL == pEncryptLpk\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will not be changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /*2  put DVB_RootKey��CK2��to CA register(DATA input) */
    //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
    //printk("ca_DecryptLpk:0x%x, 0x%x, 0x%x, 0x%x\n", pEncryptLpk[0], pEncryptLpk[1], pEncryptLpk[2], pEncryptLpk[3]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pEncryptLpk[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pEncryptLpk[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pEncryptLpk[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pEncryptLpk[3]);
    
    //(3)	���üĴ���LP_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    LPCtrl.u32 = 0;
    LPCtrl.bits.level_sel = 0x00;//00����ǰ��1���Ự��Կ
    DRV_ADVCA_WriteReg(CA_V300_LP_CTRL, LPCtrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (Ret > 0)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
#if 0
    //����Ľ���鿴�м����Ĵ���KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_KEY_DOUT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }    
#endif
    return HI_SUCCESS;
}

#if 0
struct timeval time_1, time_2, time_3, time_4;
HI_U32 data1, data2, data3, data4;
struct timeval si_time_now(void)
{
    struct timeval tv;
#ifdef __USER_LEVEL__    
    gettimeofday(&tv, NULL);
#else
    do_gettimeofday(&tv);
#endif    
    return tv;
}
#endif

HI_S32 HAL_ADVCA_V300_DecryptLPKProtectData(HI_U32 *pEncryptData,HI_U32 *pClearData)
{
    HI_U32 index;
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_LP_CTRL_U      LPCtrl;
    
    /*  Only use in Conax CA
        Use R2R Root Key as the top key.
        Set Second Level LPK protect key, Algorithm:TDES
        Must invoke after DecryptLpk.
        Use parameter�Ĵ�����	0x50~0x5C as the key, Algorithm:TDES
        Input is pEncryptData, Output is pClearData
    */

    if ((HI_NULL == pEncryptData) || (HI_NULL == pClearData))
    {
       HI_ERR_CA("HI_NULL == pEncryptData, pClearData\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will not be changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /*2  put R2R_RootKey��CK2��to CA register(DATA input) */
    //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
    //printk("DecryptLPKPrtotectData:0x%x, 0x%x\n", pEncryptData[0], pEncryptData[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pEncryptData[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pEncryptData[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pEncryptData[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, (pEncryptData[1] + 1));
    //(3)	���üĴ���LP_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    LPCtrl.u32 = 0;
    LPCtrl.bits.level_sel = 0x01;//01����ǰ��2���Ự��Կ    
    DRV_ADVCA_WriteReg(CA_V300_LP_CTRL, LPCtrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0    
    Ret = HAL_ADVCA_V300_WaitStat();
    if (Ret > 0)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
  
    for(index = 0; index < 8; index +=4)//Data Result is 128bit(16Bytes) data
    {
        pClearData[(index / 4)] = DRV_ADVCA_ReadReg(CA_V300_LP_PARAMETER_BASE + index);
    }
    
#if 0
    //����Ľ���鿴�м����Ĵ���CA_V300_LP_PARAMETER_BASE 0x50~0x5C
    {
        HI_U32 Temp;
        printk("Debug DecryptLPKPrtotectData LP_PARAMETER out\n");
        for(index = 0; index < 8; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_LP_PARAMETER_BASE + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }
#endif
    return HI_SUCCESS;
}

HI_S32 HAL_DAVCA_V300_EncryptDevicekey(HI_U32 *pDeviceKey, HI_U32 *pEncryptDeviceKey)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_GDRM_CTRL_U unGDRMCtrl;
    CA_V300_CONFIG_STATE_U unConfigStatus;


    if (HI_NULL == pDeviceKey || HI_NULL == pEncryptDeviceKey)
    {
       HI_ERR_CA("HI_NULL == pDataIn || HI_NULL == pEncryptDeviceKey\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
    
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pDeviceKey[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pDeviceKey[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pDeviceKey[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pDeviceKey[3]);

    unGDRMCtrl.u32 = 0;
    unGDRMCtrl.bits.level_sel = 0x0;
    unGDRMCtrl.bits.decryption = 0;

    DRV_ADVCA_WriteReg(CA_V300_GDRM_CTRL, unGDRMCtrl.u32); /* CAStatus.bits.klad_busy will be set to 1 */

    /* Now Wait, until CAStatus.bits.klad_busy == 0 */
    Ret = HAL_ADVCA_V300_WaitStat();
    if(HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    pEncryptDeviceKey[0] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST0);
    pEncryptDeviceKey[1] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST1);
    pEncryptDeviceKey[2] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST2);
    pEncryptDeviceKey[3] = DRV_ADVCA_ReadReg(CA_V300_GDRM_ENC_REST3);

    //Just to store it for /proc message
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);

        memcpy(g_GDRMInfo.SessionKey[0], (HI_U8 *)pDeviceKey, 16);
        memcpy(g_GDRMInfo.SessionKey[1], (HI_U8 *)pEncryptDeviceKey, 16);
        g_GDRMInfo.SessionKey_sec[0] = tv.tv_sec;
        g_GDRMInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_GDRM_CTRL);  
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_EncryptSwpk(HI_U32 *pClearSwpk,HI_U32 *pEncryptSwpk)
{
    HI_U32 index;
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    
    /* Key Ladder internal use TDES.
    Just Need to input data. */

    if ((HI_NULL == pClearSwpk) || (HI_NULL == pClearSwpk))
    {
       HI_ERR_CA("HI_NULL == pClearSwpk, pClearSwpk\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /*2  put R2R_RootKey��CK2��to CA register(DATA input) */
    //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pClearSwpk[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pClearSwpk[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pClearSwpk[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pClearSwpk[3]);
    
    //(3)	���üĴ���BL_CTRL_ENC��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�    
    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_ENC, 0x01);//0x1c Set Register

    Ret = HAL_ADVCA_V300_WaitStat();
    if (Ret > 0)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    for(index = 0; index < 16; index += 4) //Data Result is 128bit(16Bytes) data
    {
        pEncryptSwpk[(index / 4)] = DRV_ADVCA_ReadReg(CA_V300_BLK_ENC_RSLT + index);
    }
#if 0
    {
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = DRV_ADVCA_ReadReg(CA_V300_BLK_ENC_RSLT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }    
#endif
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DCASOpen(HI_UNF_CIPHER_ALG_E enAlg)
{
    if(g_DCASInfo.OpenFlag == HI_TRUE)
    {
        g_DCASInfo.Alg = (HI_UNF_ADVCA_ALG_TYPE_E)enAlg;     //History reason!
        return HI_SUCCESS;
    }
    g_DCASInfo.OpenFlag = HI_TRUE;
    g_DCASInfo.Alg      = (HI_UNF_ADVCA_ALG_TYPE_E)enAlg;  //History reason!
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DCASClose(HI_VOID)
{
    if(g_DCASInfo.OpenFlag == HI_TRUE)
    {
        g_DCASInfo.OpenFlag = HI_FALSE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptDCAS(HI_U32 enLevel, HI_U32 *pu32DataIn, HI_U32 AddrID, HI_BOOL bEvenOrOdd, HI_U32 *pDataOut, HI_UNF_ADVCA_CA_TARGET_E enKlTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_DCAS_CTRL_U DCASCtrl;

    if(g_DCASInfo.OpenFlag != HI_TRUE)
    {
        HI_ERR_CA("Error: DCAS is not Open\n");
        return HI_FAILURE;
    }

    /* para check*/
    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    HI_INFO_CA("input: 0x%08x %08x %08x %08x\n", pu32DataIn[0], pu32DataIn[1], pu32DataIn[2], pu32DataIn[3]);
    /*2  put EncryptData to CA register(DATA input) */
    //(2)	���üĴ���CA_DIN0��CA_DIN1��CA_DIN2��CA_DIN3�����ǽ���(����)���������ݡ�
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    
    //(3)	���üĴ���DCAS_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    DCASCtrl.u32 = 0;
    DCASCtrl.bits.dsc_code_mc_alg_sel = 0;
    DCASCtrl.bits.level_sel = enLevel;
    if(enLevel == 0x04) //To Demux:0100����ǰ�ǵ�3���Ự��Կ,payloadģʽSP��Կ��
    {
        if(enKlTarget == HI_UNF_ADVCA_CA_TARGET_DEMUX)
        {
            //���õ�3����Կ�Ļ�����������Ϊ0x04: 0100����ǰ�ǵ�3���Ự��Կ
            //0100����ǰ�ǵ�3���Ự��Կ,payloadģʽSP��Կ��
        	DCASCtrl.bits.level_sel = 0x04;
            DCASCtrl.bits.even_or_odd = bEvenOrOdd;  //Odd/Even Key
        	/* Demux DescambleKey ID + even_or_odd */
            DCASCtrl.bits.key_addr = AddrID & 0x7F; //Demux DescambleKey ID        	
        }
        else
        {
            //0101����ǰ�ǵ�3���Ự��Կ,rawģʽSP��Կ��
        	DCASCtrl.bits.level_sel = 0x05;
        	/* multicipher channel ID */
            DCASCtrl.bits.key_addr = AddrID & 0xFF; //Demux DescambleKey ID             	
        }
    }
    else if(enLevel == 0x05)  //To R2R,0101����ǰ�ǵ�3���Ự��Կ,rawģʽSP��Կ��
    {
        //R2R��0011����ǰ�ǵ�3���Ự��Կ,R2R��Կ
    	DCASCtrl.bits.level_sel = 0x05;
    	/* multicipher channel ID */
    	DCASCtrl.bits.even_or_odd = (AddrID & 0x01);
        DCASCtrl.bits.key_addr = (AddrID >> 1) & 0xFF;  
    }

    if(g_DCASInfo.Alg == (HI_UNF_ADVCA_ALG_TYPE_E)HI_UNF_CIPHER_ALG_3DES)  //History reason!
    {
        DCASCtrl.bits.tdes_aes_sel = 0;//0:tdes, 1:aes
    }
    else
    {
        DCASCtrl.bits.tdes_aes_sel = 1;//0:tdes, 1:aes
    }

    DRV_ADVCA_WriteReg(CA_V300_DCAS_CTRL, DCASCtrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (DCAS_KL_DISABLE_ERROR == Ret)
    {
        HI_ERR_CA("DCAS key ladder error: dcas_kl_disable error\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {    
        unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
        return HI_FAILURE;
    }
    
    if(DCASCtrl.bits.level_sel == 0x09) //DCAS reply DA-nonce
    {
        if (HI_NULL == pDataOut)
        {
           HI_ERR_CA("HI_NULL == pDataOut\n");
           return HI_ERR_CA_INVALID_PARA;
        }        
        pDataOut[0] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE);
        pDataOut[1] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE+4);
        pDataOut[2] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE+8);
        pDataOut[3] = DRV_ADVCA_ReadReg(CA_V300_DA_NOUCE+12);
    }

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);

        memcpy(g_DCASInfo.SessionKey[enLevel], (HI_U8 *)pu32DataIn, 16);
        g_DCASInfo.SessionKey_sec[enLevel] = tv.tv_sec;
        //printk("DCAS enLevel:%d\n", enLevel);
        g_DCASInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        
        //0����ǰ��ż��Կ��1����ǰ������Կ
        if ((g_DCASInfo.MaxLevel == (enLevel + 1))
        || (enLevel == 0x04) || (enLevel == 0x05))
        {
            if(bEvenOrOdd == 0x00)
            {
                memcpy(g_DCASInfo.LastEvenKey, pu32DataIn, 16);
                g_DCASInfo.LastEvenKey_secTime = tv.tv_sec;
            }
            else
            {
                memcpy(g_DCASInfo.LastOddKey, pu32DataIn, 16);
                g_DCASInfo.LastOddKey_secTime = tv.tv_sec;
            }
        }
    }
   
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SWPKKeyLadderOpen(void)
{
    g_IsSWPKKeyLadderOpen = HI_TRUE;  
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SWPKKeyLadderClose(void)
{
    g_IsSWPKKeyLadderOpen = HI_FALSE;    
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptSWPK(HI_U32 *pu32DataIn,HI_U32 AddrID)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    
    /* Key Ladder internal use TDES.
       Just Need to input data. */

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pClearSwpk, pClearSwpk\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    
    /* Config GDRM_CTRL, and then CA_STATE.klad_busy would be set */
    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_DEC, (AddrID & 0x3F) << 8);//0x1c Set Register
/*    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_DEC, 0x01);*/  //0x1c Set Register

    Ret = HAL_ADVCA_V300_WaitStat();
    if (Ret > 0)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_CryptGDRM(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,
                        HI_U32 *pu32DataIn,
                        HI_U32 AddrID,
                        HI_BOOL bIsDeCrypt,
                        HI_UNF_ADVCA_CA_TARGET_E enKlTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_GDRM_CTRL_U unGDRMCtrl;

    HI_U32 looptime = 0;

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /*
        'level_sel: '�Ự��Կ����������
        00����ǰ��1���Ự��Կ��AES ECB
        01����ǰ��2���Ự��Կ��AES ECB
        10����ǰ��3���Ự��Կbyte0~byte15��AES CBC
        11����ǰ��3���Ự��Կ��byte16~byte31��AES CBC��
    */
   if(enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3)
   {
    //do 2 times
    //index 0: level_sel = 3;select pu32DataIn 0~15; 
    //index 0: level_sel = 4;select pu32DataIn 16~31;
    looptime = 2;
   }
   else if( (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV1) || (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2) )
   {
    //do one time
    looptime =1;
   }
   else
   {
     looptime = 0;
     return HI_FAILURE;
   }

   while(looptime > 0)
   {
   
        /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
           The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
        unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
        if(unConfigStatus.bits.st_vld != 1)
        {
            HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
            return HI_FAILURE;
        }

        Ret = HAL_ADVCA_V300_WaitStat();
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Keyladder is busy now!\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }
        if( (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3) && (looptime == 1) )
        {
            /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[4]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[5]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[6]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[7]);
        }
        else
        {
            /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
            DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
        }

        /* Config GDRM_CTRL, and then CA_STATE.klad_busy would be set */
        unGDRMCtrl.u32 = 0;
        if(enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3)
        {
            if(looptime == 2)
            {
                unGDRMCtrl.bits.level_sel = 0x02;
            }
            else  //loop == 1;
            {
                unGDRMCtrl.bits.level_sel = 0x03;
            }
        }
        else
        {
            unGDRMCtrl.bits.level_sel = enLevel;
        }
        /* defaultTarget : Multicipher Algorithm. */
        unGDRMCtrl.bits.target_sel = enKlTarget;
        unGDRMCtrl.bits.decryption = bIsDeCrypt;

    	if (HI_UNF_ADVCA_CA_TARGET_MULTICIPHER == enKlTarget)        
        {
        	/* multicipher channel ID */
            unGDRMCtrl.bits.even_or_odd = (AddrID & 0x7F) & 0x01; // first 1 bit
            unGDRMCtrl.bits.key_addr = (AddrID & 0x7F) >> 1;      // last 7 bits
        }
        else
        {
            unGDRMCtrl.bits.key_addr = AddrID & 0xFF;
        }
    
        DRV_ADVCA_WriteReg(CA_V300_GDRM_CTRL, unGDRMCtrl.u32); /* CAStatus.bits.klad_busy will be set to 1 */
  
        /* Now Wait, until CAStatus.bits.klad_busy == 0 */
        Ret = HAL_ADVCA_V300_WaitStat();
        if(HI_SUCCESS != Ret)
        {
            HI_ERR_CA("Key ladder timeout\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }

        DRV_ADVCA_Wait(100);

        if(looptime > 0)
        {
            looptime --;
        }
   }

    //Just to store it for /proc message
    if(enLevel < 4)
    {
        g_GDRMInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_GDRM_CTRL);  

        struct timeval tv = {0};
        do_gettimeofday(&tv);
        if ((enLevel == HI_UNF_ADVCA_KEYLADDER_LEV1) || (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2))
        {
            memcpy(g_GDRMInfo.SessionKey[enLevel], (HI_U8 *)pu32DataIn, 16);
            g_GDRMInfo.SessionKey_sec[enLevel] = tv.tv_sec;

        }
        else if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV3)
        {
            HI_U32 GG_Flag = 0;
            memcpy(g_GDRMInfo.SessionKey[enLevel], (HI_U8 *)pu32DataIn, 32);

            g_GDRMInfo.SessionKey_sec[enLevel] = tv.tv_sec;
            GG_Flag = DRV_ADVCA_ReadReg(CA_V300_GDRM_FLAG);

            memcpy(g_GDRMInfo.GG_Flag, &GG_Flag, 4);
        }
    }
  
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetGDRMFlag(HI_U32 *pGDRMFlag)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;

    if (HI_NULL == pGDRMFlag)
    {
       HI_ERR_CA("HI_NULL == pGDRMFlag\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    pGDRMFlag[0] = DRV_ADVCA_ReadReg(CA_V300_GDRM_FLAG);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecryptMisc(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel, 
                            HI_U32 *pu32DataIn,
                            HI_U32 AddrID,
                            HI_BOOL bEvenOrOdd,
                            DRV_ADVCA_CA_TARGET_E enCwTarget)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_MISC_CTRL_U unMiscCtrl;

    if (HI_NULL == pu32DataIn)
    {
       HI_ERR_CA("HI_NULL == pDataIn\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if(unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);
    
    /* Config GDRM_CTRL, and then CA_STATE.klad_busy would be set */
    unMiscCtrl.u32 = 0;
    if(enLevel == HI_UNF_ADVCA_KEYLADDER_LEV5)
    {
        unMiscCtrl.bits.level_sel_5 = 1;
    }
    else
    {
        unMiscCtrl.bits.level_sel = enLevel;
    }
    unMiscCtrl.bits.tdes_aes_sel = g_MiscInfo.Alg;
    unMiscCtrl.bits.target_sel = enCwTarget;
    if (0 == unMiscCtrl.bits.target_sel)
    {
        /* Demux DescambleKey ID + even_or_odd */
        unMiscCtrl.bits.key_addr = ((AddrID & 0x7F) << 1) + bEvenOrOdd;
        unMiscCtrl.bits.dsc_mode = g_MiscInfo.enDscMode;  //set demux DscMode
    }
    else
    {
        /* multicipher channel ID */
        unMiscCtrl.bits.key_addr = AddrID & 0xFF;
    }
  
    /* CAStatus.bits.klad_busy will be set to 1 */
    DRV_ADVCA_WriteReg(CA_V300_MISC_CTRL, unMiscCtrl.u32);
    
    /* Now Wait until CAStatus.bits.klad_busy == 0 */
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("Key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (MISC_KL_LEVEL_ERROR == Ret)
    {
        HI_ERR_CA("MISC key ladder error: keyladder level is 2 in otp, but start 3rd level actually.\n");
        return HI_FAILURE;
    }
    else if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }

    DRV_ADVCA_Wait(100);
#if 0
    //����Ľ���鿴�м����Ĵ���KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printk("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = ca_read_reg(CA_V300_KEY_DOUT + index);
            printk("%08x " , Temp);
        }
        printk("\n");
    }
#endif

    //Just to store it for /proc message
    if(enLevel < 16)
    {
        struct timeval tv = {0};
        do_gettimeofday(&tv);
        memcpy(g_MiscInfo.SessionKey[enLevel], pu32DataIn, 16);
        g_MiscInfo.SessionKey_sec[enLevel] = tv.tv_sec;
        
        g_MiscInfo.Keyladder_Ready = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        
        //0����ǰ��ż��Կ��1����ǰ������Կ
        if(g_MiscInfo.MaxLevel == (enLevel + 1))
        {
            if(bEvenOrOdd == 0x00)
            {
                memcpy(g_MiscInfo.LastEvenKey, pu32DataIn, 16);
                g_MiscInfo.LastEvenKey_secTime = tv.tv_sec;
            }
            else
            {
                memcpy(g_MiscInfo.LastOddKey, pu32DataIn, 16);
                g_MiscInfo.LastOddKey_secTime = tv.tv_sec;
            }
        }
    }
   
    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetSecretKeyChecksumFlag(HI_U32 *pu32Checksum)
{
    HI_UNF_ADVCA_CHECKSUM_FLAG_U unChecksum;

    if( NULL == pu32Checksum)
    {
        HI_ERR_CA("ERROR! Null pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    unChecksum.u32 = 0;
    unChecksum.u32 = DRV_ADVCA_ReadReg(CA_V300_CHECKSUM_FLAG);
    *pu32Checksum = unChecksum.u32;

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_GetCAStates(HI_U32 *pu32State)
{
    if(NULL == pu32State)
    {
        HI_ERR_CA("ERROR! Null pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    DRV_ADVCA_WriteReg(CA_V300_CA_STATE, *pu32State);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_ResetOTP(HI_VOID)
{
    OTP_V200_CRG_CTRL_U OtpV200CrgCtrl;

    OtpV200CrgCtrl.u32 = 0;

    /*Set the reset value of OTP: 0xF8A220C0 bit[10]*/
    OtpV200CrgCtrl.u32 = DRV_ADVCA_ReadReg(OTP_V200_CRG_ADDR);
    OtpV200CrgCtrl.bits.otp_srst_req = 1;
    DRV_ADVCA_WriteReg(OTP_V200_CRG_ADDR, OtpV200CrgCtrl.u32);

    ca_msleep(1);

    OtpV200CrgCtrl.bits.otp_srst_req = 0;
    DRV_ADVCA_WriteReg(OTP_V200_CRG_ADDR, OtpV200CrgCtrl.u32);
	return HI_SUCCESS;
}


static HI_S32 HAL_ADVCA_ProcGetRegInfo2(HI_U32 *pu32Debug)
{
    HI_U32 u32Addr = 0;

    if ( NULL == pu32Debug )
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    u32Addr = ca_io_address(REG_SYS_GEN24);
    *pu32Debug = DRV_ADVCA_SysReadReg(u32Addr);

    return HI_SUCCESS;
}

static HI_S32 HAL_ADVCA_ProcGetRegInfo1(HI_U32 u32ChipID, HI_U32 *pu32Debug)
{
    HI_U32 wdata[4];
    CA_V300_JTAGKEY0 s_jtagkey0;
    CA_V300_JTAGKEY1 s_jtagkey1;
    HI_U32 u32Addr = 0;

    if ( NULL == pu32Debug )
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    memset(wdata, 0, sizeof(HI_U32) * 4);
    s_jtagkey0.u32 = 0;
    s_jtagkey1.u32 = 0;

	s_jtagkey0.bits.data31 = (u32ChipID&(0x1<<14))>>14;
	s_jtagkey0.bits.data30 = (u32ChipID&(0x1<<20))>>20;
	s_jtagkey0.bits.data29 = (u32ChipID&(0x1<<2))>>2;
	s_jtagkey0.bits.data28 = (u32ChipID&(0x1<<29))>>29;

	s_jtagkey0.bits.data27 = (u32ChipID&(0x1<<4))>>4;
	s_jtagkey0.bits.data26 = (u32ChipID&(0x1<<19))>>19;
	s_jtagkey0.bits.data25 = (u32ChipID&(0x1<<6))>>6;
	s_jtagkey0.bits.data24 = (u32ChipID&(0x1<<16))>>16;

	s_jtagkey0.bits.data23 = (u32ChipID&(0x1<<22))>>22;
	s_jtagkey0.bits.data22 = (u32ChipID&(0x1<<26))>>26;
	s_jtagkey0.bits.data21 = (u32ChipID&(0x1<<10))>>10;
	s_jtagkey0.bits.data20 = (u32ChipID&(0x1<<1))>>1;

	s_jtagkey0.bits.data19 = (u32ChipID&(0x1<<12))>>12;
	s_jtagkey0.bits.data18 = (u32ChipID&(0x1<<24))>>24;
	s_jtagkey0.bits.data17 = (u32ChipID&(0x1<<0))>>0;
	s_jtagkey0.bits.data16 = (u32ChipID&(0x1<<15))>>15;

	s_jtagkey0.bits.data15 = (u32ChipID&(0x1<<7))>>7;
	s_jtagkey0.bits.data14 = (u32ChipID&(0x1<<31))>>31;
	s_jtagkey0.bits.data13 = (u32ChipID&(0x1<<18))>>18;
	s_jtagkey0.bits.data12 = (u32ChipID&(0x1<<27))>>27;

	s_jtagkey0.bits.data11 = (u32ChipID&(0x1<<11))>>11;
	s_jtagkey0.bits.data10 = (u32ChipID&(0x1<<21))>>21;
	s_jtagkey0.bits.data09 = (u32ChipID&(0x1<<8))>>8;
	s_jtagkey0.bits.data08 = (u32ChipID&(0x1<<23))>>23;

	s_jtagkey0.bits.data07 = (u32ChipID&(0x1<<13))>>13;
	s_jtagkey0.bits.data06 = (u32ChipID&(0x1<<25))>>25;
	s_jtagkey0.bits.data05 = (u32ChipID&(0x1<<9))>>9;
	s_jtagkey0.bits.data04 = (u32ChipID&(0x1<<5))>>5;

	s_jtagkey0.bits.data03 = (u32ChipID&(0x1<<28))>>28;
	s_jtagkey0.bits.data02 = (u32ChipID&(0x1<<3))>>3;
	s_jtagkey0.bits.data01 = (u32ChipID&(0x1<<30))>>30;
	s_jtagkey0.bits.data00 = (u32ChipID&(0x1<<17))>>17;

	wdata[0]=s_jtagkey0.u32;

	s_jtagkey1.bits.data03 = (wdata[0]&(0xff<<6))>>6;
	s_jtagkey1.bits.data02 = (wdata[0]&(0xff<<17))>>17;
	s_jtagkey1.bits.data01 = (wdata[0]&(0xff<<22))>>22;
	s_jtagkey1.bits.data00 = (wdata[0]&(0xff<<2))>>2;

	wdata[1] = s_jtagkey1.u32;
	wdata[2] = ADVCA_MAGIC_NUM1 ^ s_jtagkey0.u32;
	wdata[3] = ADVCA_MAGIC_NUM2 ^ s_jtagkey1.u32;

    u32Addr = ca_io_address(CA_OTP_V200_SECCPUJTAGKEY0);
    (HI_VOID)DRV_ADVCA_SysWriteReg(u32Addr, wdata[3]);
    u32Addr = ca_io_address(CA_OTP_V200_SECCPUJTAGKEY1);
    (HI_VOID)DRV_ADVCA_SysWriteReg(u32Addr, ~wdata[2]);
    u32Addr = ca_io_address(CA_OTP_V200_SECCPUJTAGKEY2);
    (HI_VOID)DRV_ADVCA_SysWriteReg(u32Addr, ~wdata[1]);
    u32Addr = ca_io_address(CA_OTP_V200_SECCPUJTAGKEY3);
    (HI_VOID)DRV_ADVCA_SysWriteReg(u32Addr, wdata[0]);

    pu32Debug[0] = 0;
    u32Addr = ca_io_address(CA_OTP_V200_DEBUG00);
    pu32Debug[0] = DRV_ADVCA_SysReadReg(u32Addr);

    pu32Debug[1] = 0;
    u32Addr = ca_io_address(CA_OTP_V200_DEBUG11);
    pu32Debug[1] = DRV_ADVCA_SysReadReg(u32Addr);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_ProcGetReginfo(HI_U32 au32RegInfo[3])
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 u32ChipID = 0;

    if ( NULL == au32RegInfo )
    {
        HI_ERR_CA("Invalid param, NULL pointer!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    ret = DRV_ADVCA_V300_Ioctl(CMD_CA_GET_CHIPID, &u32ChipID);
    if(HI_SUCCESS != ret)
    {
        HI_ERR_CA("Get chipid failed! \n");
        return ret;
    }

    (HI_VOID)HAL_ADVCA_ProcGetRegInfo1(u32ChipID, au32RegInfo);
    (HI_VOID)HAL_ADVCA_ProcGetRegInfo2(&au32RegInfo[2]);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_CryptHCA(HI_U32 AddrID)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CAUK_CTRL_U unCaukCtrl;

    //(1)   �ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    //(3)   ���üĴ���CAUK_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    unCaukCtrl.u32 = 0;
    unCaukCtrl.bits.key_addr = AddrID & 0xFF;
    DRV_ADVCA_WriteReg(CA_V300_CAUK_CTRL, unCaukCtrl.u32); //CAStatus.bits.klad_busy will be set to 1

    //Now Wait until CAStatus.bits.klad_busy == 0 
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    else if (HI_SUCCESS != Ret)
    {
        return HI_FAILURE;
    }
    DRV_ADVCA_Wait(100);

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_DecTAKeyLadder(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel, HI_U32 *pu32InData, HI_U32 u32InDataLen)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_TA_CTRL_U unTaCtrl;
    HI_U32 u32Loop, u32Count;

    if (HI_NULL == pu32InData)
    {
       HI_ERR_CA("HI_NULL == pu32InData\n");
       return HI_ERR_CA_INVALID_PARA;
    }

    /* Read CONIFG_STATE.st_vld first, we can operate registers once CONIFG_STATE.st_vld set to 1. 
       The value of CONIFG_STATE.st_vld will be not changed when powered on after it set to 1. */
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_CA("Keyladder is busy now!\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
   
    u32Count = u32InDataLen / 16;
    for (u32Loop = 0; u32Loop < u32Count; u32Loop++)
    {
        /* Config the input data for crypto : CA_DIN0, CA_DIN1, CA_DIN2, CA_DIN3 */
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32InData[0 + u32Loop * 4]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32InData[1 + u32Loop * 4]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32InData[2 + u32Loop * 4]);
        DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32InData[3 + u32Loop * 4]);

        /* Config TA_CTRL, and then CA_STATE.klad_busy would be set */
        unTaCtrl.u32 = 0;
        unTaCtrl.bits.level_sel = enLevel;

        if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2)
        {
            unTaCtrl.bits.dec_lut_alg_sel = HI_UNF_ADVCA_ALG_TYPE_AES;
        }
        
        if (enLevel == HI_UNF_ADVCA_KEYLADDER_LEV2 && ((u32Loop + 1) == u32Count))
        {
            unTaCtrl.bits.last_time = 1; //last time, should set it to 1.
        }
        else
        {
            unTaCtrl.bits.last_time = 0;
        }
        unTaCtrl.bits.lut_alg_sel = g_TAInfo.Alg;

        /* CAStatus.bits.klad_busy will be set to 1 */
        DRV_ADVCA_WriteReg(CA_V300_TA_KL_CTRL, unTaCtrl.u32);
        
        /* Now Wait until CAStatus.bits.klad_busy == 0 */
        Ret = HAL_ADVCA_V300_WaitStat();
        if (HI_FAILURE == Ret)
        {
            HI_ERR_CA("Key ladder timeout\n");
            return HI_ERR_CA_WAIT_TIMEOUT;
        }

        DRV_ADVCA_Wait(100);
    }

    return HI_SUCCESS;
}

HI_S32 HAL_ADVCA_V300_SetTaAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid TA Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_TAInfo.Alg = enType;
    
    return HI_SUCCESS;
}
HI_S32 HAL_ADVCA_V300_SetKeyladderAttr(CA_KEYLADDER_ATTR_S *pstKeyladderAttr)
{
    HI_UNF_ADVCA_KEYLADDER_TYPE_E            enKeyladderType;
    HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_E       enCsa2KeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_E       enCsa3KeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_E        enR2RKeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_LP_ATTR_E         enLPKeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_SP_ATTR_E         enSPKeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_E       enMiscKeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_TA_ATTR_E         enTaKeyladderAttr;
    HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_E       enGDRMKeyladderAttr;
    HI_UNF_ADVCA_ALG_TYPE_E                  enKeyladderAlg;
    HI_UNF_ADVCA_SP_DSC_MODE_E               enSPDscMode;
    HI_UNF_ADVCA_KEYLADDER_LEV_E             enKeyladderLevel;
    CA_CRYPTPM_S stCryptParam;
    CA_LOADLPK_S stLoadLpk;
    HI_S32 Ret = HI_SUCCESS;
    HI_U8 *pu8TmpBuf = NULL;
    HI_U32 u32TmpBufLen;

    if(pstKeyladderAttr == NULL)
    {
        HI_ERR_CA("Invalid param, pstKeyladderAttr = NULL\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    enKeyladderType = pstKeyladderAttr->enKeyLadderType;
    switch(enKeyladderType)
    {
    case HI_UNF_ADVCA_KEYLADDER_CSA2:

        enCsa2KeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.enCsa2KlAttr;
        if(enCsa2KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_ALG)
        {
            enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.enAlgType;
            Ret = HAL_ADVCA_V300_SetCWAlgorithm(enKeyladderAlg);
        }
        else if(enCsa2KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA2_ATTR_SESSION_KEY)
        {
            stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.enStage;
            memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA2KlAttr.u8SessionKey, 16);
            Ret = HAL_ADVCA_V300_DecryptCw(stCryptParam.ladder, stCryptParam.pDin, 0, 0);            
        }
        else
        {
            HI_ERR_CA("Invalid keyladder attribute, enCsa2KeyladderAttr = %d\n", enCsa2KeyladderAttr);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;

    case HI_UNF_ADVCA_KEYLADDER_CSA3:

        enCsa3KeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.enCsa3KlAttr;
        if(enCsa3KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_ALG)
        {
            enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.enAlgType;
            Ret = HAL_ADVCA_V300_SetCSA3Algorithm(enKeyladderAlg);
        }
        else if(enCsa3KeyladderAttr == HI_UNF_ADVCA_KEYLADDER_CSA3_ATTR_SESSION_KEY)
        {
            stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.enStage;
            memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stCSA3KlAttr.u8SessionKey, 16);
            Ret = HAL_ADVCA_V300_DecryptCsa3(stCryptParam.ladder, stCryptParam.pDin, 0, 0);            
        }
        else
        {
            HI_ERR_CA("Invalid keyladder attribute, enCsa3KeyladderAttr = %d\n", enCsa3KeyladderAttr);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;

    case HI_UNF_ADVCA_KEYLADDER_R2R:

        enR2RKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.enR2RKlAttr;
        if(enR2RKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_ALG)
        {
            enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.enAlgType;
            Ret = HAL_ADVCA_V300_SetR2RAlgorithm(enKeyladderAlg);
        }
        else if(enR2RKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_R2R_ATTR_SESSION_KEY)
        {
            stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.enStage;
            memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stR2RKlAttr.u8SessionKey, 16);
            Ret = HAL_ADVCA_V300_CryptR2R(stCryptParam.ladder, stCryptParam.pDin, 0, 1);         
        }
        else
        {
            HI_ERR_CA("Invalid keyladder attribute, enR2RKeyladderAttr = %d\n", enR2RKeyladderAttr);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;

    case HI_UNF_ADVCA_KEYLADDER_SP:

        enSPKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enSPKlAttr;
        if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ALG)
        {
            enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enAlgType;
            Ret = HAL_ADVCA_V300_SetSPAlgorithm(enKeyladderAlg);
        }
        else if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_SESSION_KEY)
        {
            stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enStage;
            memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.u8SessionKey, 16);
            Ret = HAL_ADVCA_V300_DecryptSP(stCryptParam.ladder, stCryptParam.pDin, 0, 0, 0);
        }
        else if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_DSC_MODE)
        {
            enSPDscMode =  pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enDscMode;
            Ret = HAL_ADVCA_V300_SetSPDscMode(enSPDscMode);            
        }
        else if(enSPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_SP_ATTR_ENABLE)
        {
            g_SPInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.bEnable;
        }
        else
        {
            HI_ERR_CA("Invalid keyladder attribute, enR2RKeyladderAttr = %d\n", enSPKeyladderAttr);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;

    case HI_UNF_ADVCA_KEYLADDER_MISC:

        enMiscKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enMiscKlAttr;
        if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ALG)
        {
            enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enAlgType;
            Ret = HAL_ADVCA_V300_SetMiscAlgorithm(enKeyladderAlg);
        }
        else if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_SESSION_KEY)
        {
            stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.enStage;
            memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.u8SessionKey, 16);
            Ret = HAL_ADVCA_V300_DecryptMisc(stCryptParam.ladder, stCryptParam.pDin, 0, 0, 0);
        }
        else if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_DSC_MODE)
        {
            enSPDscMode =  pstKeyladderAttr->stKeyladderAttr.unKlAttr.stSPKlAttr.enDscMode;
            Ret = HAL_ADVCA_V300_SetMiscDscMode(enSPDscMode);            
        }
        else if(enMiscKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_MISC_ATTR_ENABLE)
        {
            g_MiscInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stMiscKlAttr.bEnable;
        }
        else
        {
            HI_ERR_CA("Invalid keyladder attribute, enMiscKeyladderAttr = %d\n", enMiscKeyladderAttr);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;

    case HI_UNF_ADVCA_KEYLADDER_LP:

        enLPKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stLpKlAttr.enLPKlAttr;
         if(enLPKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_LP_ATTR_LOAD_LPK)
         {
             memcpy(stLoadLpk.EncryptLpk, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stLpKlAttr.u8Lpk, 16);
             /* Decrypt LPK */
             Ret = HAL_ADVCA_V300_DecryptLpk(stLoadLpk.EncryptLpk);
         }
         else
         {
             HI_ERR_CA("Invalid keyladder attribute, enLPKeyladderAttr = %d\n", enLPKeyladderAttr);
             Ret = HI_ERR_CA_INVALID_PARA;
         }
         break;

    case HI_UNF_ADVCA_KEYLADDER_TA:
        enTaKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enTAKlAttr;
        if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ENABLE)
        {
            g_TAInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.bEnable;
        }
        else if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_ALG)
        {
            enKeyladderAlg = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enAlgType;
            Ret = HAL_ADVCA_V300_SetTaAlgorithm(enKeyladderAlg);
        }
        else if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_SESSION_KEY)
        {
            stCryptParam.ladder = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enStage;
            memcpy(stCryptParam.pDin, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.au8SessionKey, 16);
            Ret = HAL_ADVCA_V300_DecTAKeyLadder(stCryptParam.ladder, stCryptParam.pDin, 16);
        }
        else if (enTaKeyladderAttr == HI_UNF_ADVCA_KEYLADDER_TA_ATTR_LOAD_TRANDATA)
        {
            enKeyladderLevel = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.enStage;
            pu8TmpBuf = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.pu8TranData;
            u32TmpBufLen = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stTAKlAttr.u32TranDataLen;
            Ret = HAL_ADVCA_V300_DecTAKeyLadder(enKeyladderLevel, (HI_U32*)pu8TmpBuf, u32TmpBufLen);
        }
        else
        {
            HI_ERR_CA("Invalid keyladder attribute, enTaKeyladderAttr = %d\n", enTaKeyladderAttr);
            Ret = HI_ERR_CA_INVALID_PARA;
        }
        break;
        case HI_UNF_ADVCA_KEYLADDER_GDRM:
        {
            HI_U32 u32SessionKey[8] = {0};
            HI_U32 u32Output[4]     = {0};
            HI_U32 u32KeyAddr       = 0;
            
            enGDRMKeyladderAttr = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.enGDRMKlAttr;
            if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENABLE == enGDRMKeyladderAttr)
            {
                g_GDRMInfo.OpenFlag = pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.bEnable;
            }
            else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_ENCRYPT == enGDRMKeyladderAttr)
            {
                memcpy(u32SessionKey, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8SessionKey, 16);
                Ret = HAL_DAVCA_V300_EncryptDevicekey(u32SessionKey,
                                                      u32Output);
                memcpy(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8Output, u32Output, 16);
            }
            else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_SESSION_KEY == enGDRMKeyladderAttr)
            {
                if (HI_UNF_ADVCA_KEYLADDER_LEV3 == pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.enStage)
                {
                    memcpy(u32SessionKey, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8SessionKey, 32);
                    u32KeyAddr = HI_HANDLE_GET_CHNID(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.hCipherHandle);
                }
                else
                {
                    memcpy(u32SessionKey, pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8SessionKey, 16);
                    u32KeyAddr = 0;
                }
                Ret = HAL_ADVCA_V300_CryptGDRM(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.enStage, u32SessionKey, u32KeyAddr, 1, 1);
            }
            else if (HI_UNF_ADVCA_KEYLADDER_GDRM_ATTR_GETFLAG == enGDRMKeyladderAttr)
            {
                Ret = HAL_ADVCA_V300_GetGDRMFlag(u32Output);
                memcpy(pstKeyladderAttr->stKeyladderAttr.unKlAttr.stGDRMAttr.au8Output, u32Output, 4);
            }
            else
            {
                HI_ERR_CA("Invalid keyladder attribute, enGDRMKeyladderAttr = %d\n", enGDRMKeyladderAttr);                
            }
        }
        break;
    default:
        
        HI_ERR_CA("Invalid keyladder type, enKeyladderType = %d\n", enKeyladderType);
        Ret = HI_ERR_CA_INVALID_PARA;
        break;
    }

    return Ret;
}

HI_S32 HAL_ADVCA_V300_GenChipConfCmac(HI_U8 *pu8ChipConfBitm, HI_U8 *pu8ChipConfCmac)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CFG_CBC_MAC_U unCfgCbcMacCtrl;

    //(1)	�ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, *((HI_U32*)pu8ChipConfBitm + 0));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, *((HI_U32*)pu8ChipConfBitm + 1));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, *((HI_U32*)pu8ChipConfBitm + 2));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, *((HI_U32*)pu8ChipConfBitm + 3));
    
    //(2)	���üĴ���CFG_CBC_MAC��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    unCfgCbcMacCtrl.u32 = 0;
    unCfgCbcMacCtrl.bits.start = 1;
    DRV_ADVCA_WriteReg(CA_V300_CFG_CMAC_CTRL, unCfgCbcMacCtrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }
    DRV_ADVCA_Wait(100);

    *(HI_U32*)pu8ChipConfCmac = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT);
    *(HI_U32*)(pu8ChipConfCmac + 0x04) = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT  + 0x04);
    *(HI_U32*)(pu8ChipConfCmac + 0x08) = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT + 0x08);
    *(HI_U32*)(pu8ChipConfCmac + 0x0C) = DRV_ADVCA_ReadReg(CA_V300_CFG_CMAC_OUT + 0x0C);  

    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetIrdetoCsa3ActCode(HI_U8 *pu8Csa3ActCode)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    CA_V300_CFG_IVRK_CTRL_U unCfgIvRkCtrl;

    //(1)	�ȶ��Ĵ���CONIFG_STATE.st_vld��ֻ����ֵΪ1ʱ��ca�ļĴ���ֵ������Ч�ģ����ܶԼĴ���������
    //һ��CONIFG_STATE.st_vld���֮�󣬻�һֱ���֡�ֻ���ϵ�֮���ѯһ�Ρ�
    unConfigStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CONFIG_STATE);
    if (unConfigStatus.bits.st_vld != 1)
    {
        HI_ERR_CA("Error: ConfigStatus.bits.st_vld != 1\n");
        return HI_FAILURE;
    }

    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, *(HI_U32*)pu8Csa3ActCode);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, *((HI_U32*)pu8Csa3ActCode + 1));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, *((HI_U32*)pu8Csa3ActCode + 2));
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, *((HI_U32*)pu8Csa3ActCode + 3));
    
    //(2)	���üĴ���CFG_IVRK_CTRL��֮���߼����������㣬�߼�ͬʱ��CA_STATE.klad_busy�ø�
    unCfgIvRkCtrl.u32 = 0;
    unCfgIvRkCtrl.bits.alg_sel = g_CSA3Info.Alg;
    DRV_ADVCA_WriteReg(CA_V300_IVRK_CTRL, unCfgIvRkCtrl.u32); //CAStatus.bits.klad_busy will be set to 1
    
    //Now Wait until CAStatus.bits.klad_busy == 0
    Ret = HAL_ADVCA_V300_WaitStat();
    if (HI_FAILURE == Ret)
    {
        HI_ERR_CA("key ladder timeout\n");
        return HI_ERR_CA_WAIT_TIMEOUT;
    }

    DRV_ADVCA_Wait(100);
    return Ret;
}

HI_S32 HAL_ADVCA_V300_SetCavendorOpt(CA_VENDOR_OPT_S *pstCavendorOpt)
{
    HI_S32 Ret = HI_SUCCESS;
    HI_UNF_ADVCA_VENDORID_E enCaVendor;
    HI_UNF_ADVCA_CA_VENDOR_OPT_E enCaVendorOpt;
    HI_U8 *pu8TmpBuf = NULL;

    enCaVendor = pstCavendorOpt->enCaVendor;
    enCaVendorOpt = pstCavendorOpt->stCaVendorOpt.enCaVendorOpt;
    switch(enCaVendor)
    {
    case HI_UNF_ADVCA_IRDETO:

        if (enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_CHIP_CONF_CMAC)
        {            
            Ret = HAL_ADVCA_V300_GenChipConfCmac(pstCavendorOpt->stCaVendorOpt.unCaVendorOpt.stIrdetoChipConfCmac.au8ChipConfBitm,
                                                                                                        pstCavendorOpt->stCaVendorOpt.unCaVendorOpt.stIrdetoChipConfCmac.au8ChipConfCmac);
        }
        else if (enCaVendorOpt == HI_UNF_ADVCA_CA_VENDOR_OPT_IRDETO_ACTIVATION_CODE)
        {
            pu8TmpBuf = pstCavendorOpt->stCaVendorOpt.unCaVendorOpt.stIrdetoCsa3ActCode.au8CSA3ActCode;
            Ret = HAL_ADVCA_V300_SetIrdetoCsa3ActCode(pu8TmpBuf);
        }
        else
        {
            HI_ERR_CA("Invalid CA vendor attribute, enCaVendorOpt = %d\n", enCaVendorOpt);
            Ret = HI_ERR_CA_INVALID_PARA;
        }       
        break;

    default:
        HI_ERR_CA("Invalid CA vendor type, enCaVendor = %d\n", enCaVendor);
        break;
    }
    
    return Ret;
}

