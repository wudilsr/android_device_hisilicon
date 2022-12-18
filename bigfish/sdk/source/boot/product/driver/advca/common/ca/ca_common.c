/******************************************************************************

Copyright (C), 2005-2014, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : ca_common.c
Version       : Initial
Author        : Hisilicon hisecurity group
Created       : 2013-08-28
Last Modified :
Description   :  
Function List :
History       :
******************************************************************************/
#include "ca_reg.h"
#include "otp.h"
#include "ca_common.h"
#include "otp.h"
#include "hi_unf_otp.h"
#include "hi_unf_advca.h"

#define BOOT_FROM_OTP_BIT 		(1)
#define BOOT_FROM_CHIPSET_PIN 	(0)

static HI_UNF_ADVCA_ALG_TYPE_E g_R2RAlgType = HI_UNF_ADVCA_ALG_TYPE_TDES;
static HI_UNF_ADVCA_KEYLADDER_LEV_E g_R2RLadderSel = HI_UNF_ADVCA_KEYLADDER_LEV2;
HI_U32 DRV_ADVCA_ReadReg(HI_U32 addr);
HI_VOID DRV_ADVCA_WriteReg(HI_U32 addr, HI_U32 val);

/*========================interface of CAV300======================================*/
HI_VOID DRV_ADVCA_WriteReg(HI_U32 addr, HI_U32 val)
{
    ca_wtReg(addr, val);
	return;
}

HI_U32 DRV_ADVCA_ReadReg(HI_U32 addr)
{
	HI_U32 val;
    ca_rdReg(addr, val);
	return val;
}

HI_VOID DRV_ADVCA_Wait(HI_U32 us)
{
	udelay(us);
}

static HI_S32 HAL_ADVCA_V300_WaitStat(HI_VOID)
{
    HI_U32 cnt = 0;
    CA_V300_CA_STATE_U CAStatus;
    HI_S32 errState = 0;
    
    /* wait for KeyLadder calc done */
    // corform one value when test, about 500
    while (cnt < 1000)
    {
        CAStatus.u32 = 0;
        CAStatus.u32 = DRV_ADVCA_ReadReg(CA_V300_CA_STATE);
        if (CAStatus.bits.klad_busy == 0)
        {
            //HI_INFO_CA("ca_decrypted finished, cnt:%d\n", cnt);
            break;
        }
        udelay(1000);
        cnt++;
    }

    if (cnt >= 100)
    {
        HI_ERR_CA("\n Error CA handle too long !!!!!!!!!!! \n");
        return HI_FAILURE;      /* time out */
    }

    /* success */
    errState = CAStatus.bits.err_state; 
    return errState;
}

HI_S32 CA_GetR2RLadder(HI_UNF_ADVCA_KEYLADDER_LEV_E *penSel)
{
    HI_S32 Ret = HI_SUCCESS;

    CA_CheckPointer(penSel);
    Ret = OTP_GetR2RLadderLevel((OTP_KEY_LEVEL_E *)&g_R2RLadderSel);
    *penSel = g_R2RLadderSel;
    
    return Ret;
}
// limited, only aes
HI_S32 CA_SetR2RAlg(HI_UNF_ADVCA_ALG_TYPE_E type)
{
    if ((type != HI_UNF_ADVCA_ALG_TYPE_TDES) && (type != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("R2R Algorithm Error = %d ! \n", type);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_R2RAlgType = type;
    
    return HI_SUCCESS;
}
HI_S32 CA_CryptR2R(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel,HI_U32 *pu32DataIn,HI_U32 AddrID,HI_BOOL bIsDeCrypt)
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
    //(1)	先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
    //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
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

    /*2  put DVB_RootKey（CK2）to CA register(DATA input) */
    //(2)	配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pu32DataIn[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pu32DataIn[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pu32DataIn[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pu32DataIn[3]);

    //(3)	配置寄存器R2R_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
    R2RCtrl.u32 = 0;
    R2RCtrl.bits.level_sel = enLevel;
    R2RCtrl.bits.mc_alg_sel = 0;//Multicipher Algorithm. default setting
    R2RCtrl.bits.tdes_aes_sel = g_R2RAlgType;
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
    return HI_SUCCESS;
}

static CA_KEYLADDER_INFO_S g_MiscInfo = {0};

HI_U32 CA_GetMiscKlLevel(HI_UNF_ADVCA_KEYLADDER_LEV_E *penValue)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 addr = 0;
	HI_U32 u32Value = 0;
	OTP_INTERNAL_PV_1_U PV_1;

    if ( NULL == penValue)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    PV_1.u32 = 0;
    PV_1.u32 = HI_OTP_Read(addr);
    
    if( (0x00 == PV_1.bits.misc_lv_sel) && (0x00 == PV_1.bits.misc_lv_sel_2) )
    {
        *penValue = HI_UNF_ADVCA_KEYLADDER_LEV2;
    }
    else if( (0x01 == PV_1.bits.misc_lv_sel) && (0x00 == PV_1.bits.misc_lv_sel_2) )
    {
        *penValue = HI_UNF_ADVCA_KEYLADDER_LEV3;
    }
    else if( (0x00 == PV_1.bits.misc_lv_sel) && (0x01 == PV_1.bits.misc_lv_sel_2) )
    {
        *penValue = HI_UNF_ADVCA_KEYLADDER_LEV4;
    }
    else if( (0x01 == PV_1.bits.misc_lv_sel) && (0x01 == PV_1.bits.misc_lv_sel_2) )
    {
        *penValue = HI_UNF_ADVCA_KEYLADDER_LEV5;
    }

    return HI_SUCCESS;
}

HI_S32 CA_MISCKeyLadder_Open(HI_VOID)
{
	g_MiscInfo.OpenFlag = HI_TRUE;
}

HI_S32 CA_MISCKeyLadder_Close(HI_VOID)
{
	g_MiscInfo.OpenFlag = HI_FALSE;
}

HI_S32 CA_SetMiscAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E enType)
{
    if ((enType != HI_UNF_ADVCA_ALG_TYPE_TDES) && (enType != HI_UNF_ADVCA_ALG_TYPE_AES))
    {
        HI_ERR_CA("Invalid Misc Keyladder algorithm (%d)!\n", enType);
        return HI_ERR_CA_INVALID_PARA;
    }
    g_MiscInfo.Alg = enType;
    
    return HI_SUCCESS;
}

HI_S32 CA_V300_GetMiscAlgorithm(HI_UNF_ADVCA_ALG_TYPE_E *penType)
{
    if( NULL == penType)
    {
        HI_ERR_CA("Invalid param ,NULL pointer !\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    *penType = g_MiscInfo.Alg;
    
    return HI_SUCCESS;
}

HI_S32 CA_DecryptMisc(HI_UNF_ADVCA_KEYLADDER_LEV_E enLevel, 
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
    //计算的结果查看中间结果寄存器KEY_DOUT
    {
        HI_U32 index;
        HI_U32 Temp;
        printf("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = DRV_ADVCA_ReadReg(CA_V300_KEY_DOUT + index);
            printf("%08x " , Temp);
        }
        printf("\n");
    }
#endif

    return HI_SUCCESS;
}


HI_S32 CA_SetMISCSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key)
{
    HI_S32 ret = 0;

    CA_ASSERT(CA_DecryptMisc(enStage,pu8Key,0,0, 0),ret);

    return ret;
}

/* New UNF interface: HI_UNF_ADVCA_EncryptSwpk */
HI_S32 CA_EncryptSwpk(HI_U32 *pClearSwpk,HI_U32 *pEncryptSwpk)
{
    HI_U32 index;
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    
    /* Key Ladder internal use TDES.
    Just Need to input data. */

    if ((HI_NULL == pClearSwpk) || (HI_NULL == pEncryptSwpk))
    {
       HI_ERR_CA("HI_NULL == pClearSwpk, pEncryptSwpk\n");
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

    /*2  put DVB_RootKey（CK2）to CA register(DATA input) */
    //(2)	配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pClearSwpk[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pClearSwpk[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pClearSwpk[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pClearSwpk[3]);
    
    //(3)	配置寄存器BL_CTRL_ENC，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高    
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
        printf("Debug temporay Key out\n");
        for(index = 0; index < 16; index +=4)//Data Result is 128bit(16Bytes) data
        {
            Temp = DRV_ADVCA_ReadReg(CA_V300_BLK_ENC_RSLT + index);
            printf("%08x " , Temp);
        }
        printf("\n");
    }    
#endif
    return HI_SUCCESS;
}

/* Called by HAL_Cipher_SetKey */
HI_S32 CA_DecryptSwpk(HI_U32 AddrID, HI_U32 *pEncryptSwpk)
{
    HI_S32 Ret = HI_SUCCESS;
    CA_V300_CONFIG_STATE_U unConfigStatus;
    
    //Key Ladder internal use TDES.
    //Just Need to input data.
    /* para check*/
    if (HI_NULL == pEncryptSwpk)
    {
       HI_ERR_CA("HI_NULL == pEncryptSwpk\n");
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
    /*2  put EncryptData to CA register(DATA input) */
    //(2)	配置寄存器CA_DIN0，CA_DIN1，CA_DIN2，CA_DIN3，这是解密(加密)的输入数据。
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN0, pEncryptSwpk[0]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN1, pEncryptSwpk[1]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN2, pEncryptSwpk[2]);
    DRV_ADVCA_WriteReg(CA_V300_CA_DIN3, pEncryptSwpk[3]);
    
    //(3)	配置寄存器BL_CTRL_DEC，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高    
    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_DEC, (AddrID & 0x3F) << 8);//0x1c Set Register
//    DRV_ADVCA_WriteReg(CA_V300_BL_CTRL_DEC, 0x01);//0x1c Set Register    
    
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

    return HI_SUCCESS;
}

HI_S32 CA_CryptHCA(HI_U32 AddrID)
{
        HI_S32 Ret = HI_SUCCESS;
        CA_V300_CONFIG_STATE_U unConfigStatus;
        CA_V300_CAUK_CTRL_U unCaukCtrl;
    
        //(1)   先读寄存器CONIFG_STATE.st_vld，只有其值为1时，ca的寄存器值才是有效的，才能对寄存器操作。
        //一旦CONIFG_STATE.st_vld变高之后，会一直保持。只需上电之后查询一次。
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
    
        //(3)   配置寄存器CAUK_CTRL，之后逻辑会启动运算，逻辑同时把CA_STATE.klad_busy置高
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

/*========================interface of CA  Common======================================*/

HI_S32 CA_Init(HI_VOID)
{
    HI_UNF_ADVCA_KEYLADDER_LEV_E enKLadder = HI_UNF_ADVCA_KEYLADDER_BUTT;
    
    OTP_Init();

    CA_GetR2RLadder(&g_R2RLadderSel);

    memset(&g_MiscInfo, 0, sizeof(CA_KEYLADDER_INFO_S));
    g_MiscInfo.OpenFlag = HI_FALSE;
    g_MiscInfo.Alg = HI_UNF_ADVCA_ALG_TYPE_TDES;
    CA_GetMiscKlLevel(&enKLadder);
    g_MiscInfo.MaxLevel = enKLadder + 1;
    
    return HI_SUCCESS;
}

HI_S32 CA_DeInit(HI_VOID)
{
    OTP_DeInit();
    
    return HI_SUCCESS;
}

/* Called by HAL_Cipher_SetKey */
HI_S32 CA_DecryptCipher(HI_U32 AddrID, HI_U32 *pDataIn)
{
	HI_S32 ret = 0;

	if(HI_TRUE == g_MiscInfo.OpenFlag)
	{
		ret = CA_DecryptMisc(HI_UNF_ADVCA_KEYLADDER_LEV5, pDataIn, AddrID, 0, 1); //target : multi-cipher
	}
	else
	{
		ret = CA_CryptR2R(g_R2RLadderSel, pDataIn, AddrID, 1);		//target : multi-cipher
	}

	return ret;
}

/* New UNF interface: HI_UNF_ADVCA_SetR2RSessionKey */
HI_S32 CA_SetR2RSessionKey(HI_UNF_ADVCA_KEYLADDER_LEV_E enStage, HI_U8 *pu8Key)
{
    HI_S32 ret = 0;
    CA_CRYPTPM_S cryptPm;
    
    memset(&cryptPm, 0, sizeof(CA_CRYPTPM_S));
    cryptPm.ladder = enStage;
    memcpy(cryptPm.pDin, pu8Key, 16);

    CA_ASSERT(CA_CryptR2R(cryptPm.ladder,cryptPm.pDin,0,1),ret);

    return ret;
}

HI_S32 CA_GetBootMode(HI_UNF_ADVCA_FLASH_TYPE_E *penFlashType)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 bootMode = 0;

    if (NULL == penFlashType)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    bootMode = HI_OTP_Read(OTP_INTERNAL_PV_0);
    switch (bootMode & 0x03)
    {
        case 0x00:
		{
            *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_SPI;
            break;
		}
        case 0x01:
		{
            *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_NAND;
            break;
        }
        case 0x02:
		{
            *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_SD;
            break;
        }
        case 0x03:
		{
            *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_EMMC;
            break;
		}
        default:
		{
            *penFlashType = HI_UNF_ADVCA_FLASH_TYPE_BUTT;
            break;
		}
    }
    
    return ret;
}

static HI_S32 CA_SetBootMode(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType)
{
    HI_S32 ret = HI_SUCCESS;
    OTP_INTERNAL_PV_0_U PV_0;
    OTP_INTERNAL_PVLOCK_0_U PVLOCK_0;

    if (enFlashType >= HI_UNF_ADVCA_FLASH_TYPE_BUTT)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    PVLOCK_0.u32 = HI_OTP_Read(OTP_INTERNAL_PVLOCK_0);
    if ((1 == PVLOCK_0.bits.boot_mode_sel_1_lock) && (1 == PVLOCK_0.bits.boot_mode_sel_0_lock))
    {
        PV_0.u32 = HI_OTP_Read(OTP_INTERNAL_PV_0);
        if (enFlashType == ((PV_0.bits.boot_mode_sel_1 << 1) + PV_0.bits.boot_mode_sel_0))
        {
            /*if type has been set as the Boot Mode already, HI_SUCCESS should be returned*/
            return HI_SUCCESS;
        }
        else
        {
            /*if Boot Mode has been set, but it's not type, HI_ERR_CA_SETPARAM_AGAIN should be returned*/
            return HI_ERR_CA_SETPARAM_AGAIN;
        }
    }

    /*set boot mode*/
    PV_0.u32 = 0;
    switch (enFlashType)
    {
        case HI_UNF_ADVCA_FLASH_TYPE_SPI:
        {
            PV_0.bits.boot_mode_sel_1 = 0;
            PV_0.bits.boot_mode_sel_0 = 0;
            break;
		}    
        case HI_UNF_ADVCA_FLASH_TYPE_NAND:
		{
            PV_0.bits.boot_mode_sel_1 = 0;
            PV_0.bits.boot_mode_sel_0 = 1;
            break;
		}
        case HI_UNF_ADVCA_FLASH_TYPE_SD:
		{
            PV_0.bits.boot_mode_sel_1 = 1;
            PV_0.bits.boot_mode_sel_0 = 0;
            break;
		}
        case HI_UNF_ADVCA_FLASH_TYPE_EMMC:
		{
            PV_0.bits.boot_mode_sel_1 = 1;
            PV_0.bits.boot_mode_sel_0 = 1;
            break;
        }
        default:
		{
            HI_ERR_CA("Not supported flash type 0x%x!\n", enFlashType);
            return HI_ERR_CA_NOT_SUPPORT;
		}
    }

    ret = HI_OTP_Write(OTP_INTERNAL_PV_0, PV_0.u32);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Fail to write OTP!\n");
        return ret;
    }

    /*lock boot mode*/
    PVLOCK_0.u32 = 0;
    PVLOCK_0.bits.boot_mode_sel_0_lock = 1;
    PVLOCK_0.bits.boot_mode_sel_1_lock = 1;

    ret = HI_OTP_Write(OTP_INTERNAL_PVLOCK_0, PVLOCK_0.u32);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Fail to write OTP!\n");
        return ret;
    }

    return ret;
}

static HI_S32 CA_SetBootSelCtrl(HI_U32 u32BootSel)
{
    HI_S32 ret = HI_SUCCESS;
    OTP_INTERNAL_PV_1_U PV_1;
    OTP_INTERNAL_PVLOCK_1_U PVLOCK_1;

    if ((u32BootSel != BOOT_FROM_CHIPSET_PIN) && (u32BootSel != BOOT_FROM_OTP_BIT))
    {
    	HI_ERR_CA("Invalid param!\n");
        return HI_ERR_CA_INVALID_PARA;
    }

    PVLOCK_1.u32 = HI_OTP_Read(OTP_INTERNAL_PVLOCK_1);
    if (1 == PVLOCK_1.bits.bootsel_ctrl_lock)
    {
        PV_1.u32 = HI_OTP_Read(OTP_INTERNAL_PV_1);
        if (u32BootSel == PV_1.bits.bootsel_ctrl)
        {
            /* value already set to the right one, return HI_SUCCESS */
            return HI_SUCCESS;
        }
        else
        {
            /* set value to another value, return HI_ERR_CA_SETPARAM_AGAIN */
            return HI_ERR_CA_SETPARAM_AGAIN;
        }
    }

    /* set value */
    if (u32BootSel == 1)
    {
        PV_1.u32 = 0;
        PV_1.bits.bootsel_ctrl = 1;
        ret = HI_OTP_Write(OTP_INTERNAL_PV_1, PV_1.u32);
        if (HI_SUCCESS != ret)
        {
            HI_ERR_CA("Fail to write bootsel_ctrl!\n");
            return ret;
        }
    }
    
    /* lock value */
    PVLOCK_1.u32 = 0;
    PVLOCK_1.bits.bootsel_ctrl_lock = 1;
    ret = HI_OTP_Write(OTP_INTERNAL_PVLOCK_1, PVLOCK_1.u32);
    if (HI_SUCCESS != ret)
    {
        HI_ERR_CA("Fail to write bootsel_ctrl_lock!\n");
        return ret;
    }
    
    return ret;
}
HI_S32 CA_SetRSAKeyLockFlag(HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr)
{
    HI_S32 ret = HI_SUCCESS;
	HI_U32 u32Temp = 0;

	if(NULL == pstOtpFuseAttr)
	{
		return HI_ERR_CA_INVALID_PARA;
	}

	if(HI_TRUE == pstOtpFuseAttr->unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked)
	{
		u32Temp = HI_OTP_Read(OTP_INTERNAL_DATALOCK_1);
		if(1 == (u32Temp & 1))
		{
			return HI_SUCCESS;
		}

		u32Temp = u32Temp | 1;
		ret = HI_OTP_Write(OTP_INTERNAL_DATALOCK_1, u32Temp);
		if(HI_SUCCESS != ret)
		{
			HI_ERR_CA("Write rsa key lock flag failed, ret:0x%x\n", ret);
			return HI_ERR_CA_INVALID_PARA;
		}
	}

	return HI_SUCCESS;
}

HI_S32 CA_GetRSAKeyLockFlag(HI_UNF_ADVCA_OTP_ATTR_S *pstOtpFuseAttr)
{
    HI_S32 ret = HI_SUCCESS;
	HI_U8 u8Temp = 0;

	if(NULL == pstOtpFuseAttr)
	{
		return HI_ERR_CA_INVALID_PARA;
	}

	u8Temp = HI_OTP_ReadByte(OTP_INTERNAL_DATALOCK_1);
	if(0 == (u8Temp & 1))
	{
		pstOtpFuseAttr->unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_FALSE;
	}
	else
	{
		pstOtpFuseAttr->unOtpFuseAttr.stRSAKeyLockFlag.bIsLocked = HI_TRUE;
	}

	return HI_SUCCESS;
}

HI_S32 CA_EnableSCSActive(HI_UNF_ADVCA_FLASH_TYPE_E enFlashType)
{
    HI_S32 ret = HI_SUCCESS;
	OTP_ONE_WAY_0_U OneWay;
	OTP_INTERNAL_DATALOCK_0_U unDataLock;
    HI_U8 u8Temp = 0;
    HI_U8 u8ScsBak = 0;
	HI_BOOL bSCSActiveFlag = HI_FALSE;

    if (enFlashType >= HI_UNF_ADVCA_FLASH_TYPE_BUTT)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

	ret = CA_GetSCSActiveFlag(&bSCSActiveFlag);
	if(HI_SUCCESS != ret)
	{
		HI_ERR_CA("Get scs active flag failed.\n");
		return ret;
	}

	if(HI_TRUE == bSCSActiveFlag)
	{
		HI_ERR_CA("SCS has been already enabled before.\n");
		return HI_FAILURE;
	}

	/* write SCS_activation flag */
	OneWay.u32 = 0;
	OneWay.bits.SCS_activation = 1;
	ret = HI_OTP_Write(OTP_INTERNAL_ONEWAY_0, OneWay.u32);
	if(HI_SUCCESS != ret)
	{
		HI_ERR_CA("Write scs active flag failed, ret:0x%x.\n", ret);
		return ret;
	}

	/* write scs_en_bak_lock */
	unDataLock.u32 = 0;
	unDataLock.u32 = HI_OTP_Read(OTP_INTERNAL_DATALOCK_0);
	if(1 != unDataLock.bits.scs_en_bak_lock)
	{
		/* write scs_en_bak */
	    u8ScsBak = SCS_BAK_ENABLE;
		ret = HI_OTP_WriteByte(OTP_SCS_EN_BAK_ADDR, u8ScsBak);
		if(HI_SUCCESS != ret)
		{
			HI_ERR_CA("Write scs bak failed, ret:0x%x.\n", ret);
			return ret;
		}

		unDataLock.u32 = 0;
		unDataLock.bits.scs_en_bak_lock = 1;
		ret = HI_OTP_Write(OTP_INTERNAL_DATALOCK_0, unDataLock.u32);
		if(HI_SUCCESS != ret)
		{
			HI_ERR_CA("Write scs_en_bak_lock failed, ret:0x%x.\n", ret);
			return ret;
		}
	}

	/* write boot mode flash type */
	ret = CA_SetBootMode(enFlashType);
	if(HI_SUCCESS != ret)
	{
		HI_ERR_CA("Write boot mode failed, ret:0x%x, enFlashType:0x%x.\n", ret, enFlashType);
		return ret;
	}

	/* write bootsel_ctrl */
	ret = CA_SetBootSelCtrl(BOOT_FROM_OTP_BIT);
	if(HI_SUCCESS != ret)
	{
		HI_ERR_CA("Write bootsel_ctrl(1) failed, ret:0x%x\n", ret);
		return ret;
	}

	return HI_SUCCESS;
}

HI_S32 CA_GetSCSActiveFlag(HI_BOOL *pbSCSActiveFlag)
{
    HI_S32 ret = HI_SUCCESS;
    OTP_ONE_WAY_0_U OneWay_0;
    HI_U8 u8ScsBak = 0;

    if (NULL == pbSCSActiveFlag)
    {
        return HI_ERR_CA_INVALID_PARA;
    }

    OneWay_0.u32 = HI_OTP_Read(OTP_INTERNAL_ONEWAY_0);
    u8ScsBak = HI_OTP_ReadByte(OTP_SCS_EN_BAK_ADDR);

    if ((1 == OneWay_0.bits.SCS_activation) || (SCS_BAK_DISABLE != u8ScsBak))
    {
        *pbSCSActiveFlag = HI_TRUE;
    }
    else
    {
        *pbSCSActiveFlag = HI_FALSE;
    }
    
    return HI_SUCCESS;
}

