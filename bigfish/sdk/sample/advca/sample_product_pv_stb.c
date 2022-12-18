/**
\file
\brief r2r hardware cryption
\copyright Shenzhen Hisilicon Co., Ltd.
\version draft
\author f00172091
\date 2013-1-22
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include "hi_type.h"
#include "hi_common.h"
#include "hi_unf_advca.h"
#include "hi_unf_ecs.h"
#include "sample_ca_common.h"

/***************************** Macro Definition ******************************/
#define MAX_OTP_SIZE    0x800

/*************************** Structure Definition ****************************/

typedef struct{
    HI_CHAR name[32];
    HI_U32  datavalue;
}HI_OTP_PV_STRUCT_S;

/********************** Global Variable declaration **************************/

typedef enum hiADVCA_PV_TYPE_E
{
    MSID = 0, 
    Version_ID,
    
    boot_mode_sel,
    bootsel_ctrl,
    
    link_prt_disable,
    ts_csa2_hardonly_en,
    ts_sp_hardonly_en,
    ts_csa3_hardonly_en,
	tskl_csa3_disable,
    dcas_kl_disable,
    misc_kl_disable,
    gg_kl_disable,

    runtime_check_en,
    ddr_wakeup_disable,
    wakeup_ddr_check_en,
    version_id_check_en,
    bl_msid_check_en,

    jtag_prt_mode,
    jtag_r_disable,

    /*Followed items should be set carefully and in the final*/
    bload_dec_en,
    self_boot_disable,
    SCS_activation,
    
    otp_globle_lock_en,    /*Should be set at last, otherwise the OTP can not be writed*/

    HI_UNF_ADVCA_PV_TYPE_BUTT
}HI_ADVCA_PV_TYPE_E;

HI_OTP_PV_STRUCT_S stDefaultPV[HI_UNF_ADVCA_PV_TYPE_BUTT]={

    /*DATA Configuration*/
    {"MSID",            0x0},
    {"Version_ID",    0x0},

    /* Lockable fuses Configuration*/
    {"boot_mode_sel",      0x0},
    {"bootsel_ctrl",           0x0},   /*setted with boot_mode_sel together */
    
    {"link_prt_disable",         0x0},
    {"ts_csa2_hardonly_en", 0x0},
    {"ts_sp_hardonly_en",     0x0},
    {"ts_csa3_hardonly_en", 0x0},
	{"tskl_csa3_disable", 0x0},
    {"dcas_kl_disable",     0x0},
    {"misc_kl_disable",     0x0},
    {"gg_kl_disable",     0x0},
        
    {"runtime_check_en",  0x0},
    {"ddr_wakeup_disable",  0x0},
    {"wakeup_ddr_check_en",  0x0},
    {"version_id_check_en",     0x0},
    {"bl_msid_check_en",        0x0},

    /* OneWay Configuration*/
    {"jtag_prt_mode",    0x0},
    {"jtag_r_disable",        0x0},

    /* Lockable fuses Configuration*/
    {"bload_dec_en",           0x0},
    {"self_boot_disable",      0x0},
    /* OneWay Configuration*/
    {"SCS_activation",      0x0},  
    
    /* Lockable fuses Configuration*/
    {"otp_globle_lock_en", 0x0}        /*Should be set at last, otherwise the OTP can not be writed*/
};

extern HI_S32 HI_UNF_ADVCA_DisableLinkProtection(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_LockSPHardCW(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_LockCSA3HardCW(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_DisableDCasKl(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_EnableRuntimeCheck(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_DisableDDRWakeup(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_EnableDDRWakeupCheck(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_DisableJtagRead(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_LockGlobalOTP(HI_VOID);
extern HI_S32 HI_UNF_ADVCA_GetCSA3HardCWStat(HI_BOOL *pbLock);
extern HI_S32 HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_TYPE_E enType, HI_U8 *pu8ParamIn, HI_U32 u32ParamLen);
extern HI_S32 HI_UNF_ADVCA_OtpRead(HI_U32 Addr, HI_U32 *pValue);
/******************************* API declaration *****************************/
HI_S32 SetPVItemValue(HI_OTP_PV_STRUCT_S *pstPVcfg)
{
    HI_U32 num = sizeof(stDefaultPV)/sizeof(HI_OTP_PV_STRUCT_S);
    HI_U32 i;
    
    HI_DEBUG_ADVCA("%-32s  0x%x\n", pstPVcfg->name, pstPVcfg->datavalue);
    for(i=0; i<num; i++)
    {
        if(0==strncmp(pstPVcfg->name, stDefaultPV[i].name, strlen(stDefaultPV[i].name)))
        {
            stDefaultPV[i].datavalue = pstPVcfg->datavalue;
            return HI_SUCCESS;
        }
    }
    return HI_FAILURE;
}

HI_S32 GetOTPItemValue(FILE * fp_pv_out)
{
    HI_U32 num = sizeof(stDefaultPV)/sizeof(HI_OTP_PV_STRUCT_S);
    HI_OTP_PV_STRUCT_S   *pstPVItem;
    HI_U32 i;
    HI_S32 ret = HI_SUCCESS;
    
    for(i=0; i<num; i++)
    {
        pstPVItem = &stDefaultPV[i];
        if(0==strncmp(pstPVItem->name, "MSID", 4))
        {
            HI_U8 u8MarketId[4];
            ret = HI_UNF_ADVCA_GetMarketId(u8MarketId);
            pstPVItem->datavalue = (u8MarketId[0]<<24)|(u8MarketId[1]<<16)|(u8MarketId[2]<<8)|u8MarketId[3];
        }
        else if(0==strncmp(pstPVItem->name, "Version_ID", 10))
        {
            HI_U8 u8VersionId[4];
            ret = HI_UNF_ADVCA_GetVersionId(u8VersionId);
            pstPVItem->datavalue = (u8VersionId[0]<<24)|(u8VersionId[1]<<16)|(u8VersionId[2]<<8)|u8VersionId[3];
        }
        else if(0==strncmp(pstPVItem->name, "boot_mode_sel", 13))
        {
            HI_BOOL bSecEnable;
            ret = HI_UNF_ADVCA_GetSecBootStat(&bSecEnable, (HI_UNF_ADVCA_FLASH_TYPE_E *) &pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "bootsel_ctrl", 11))
        {
        }
        else if(0==strncmp(pstPVItem->name, "link_prt_disable", 16))
        {
        }
        else if(0==strncmp(pstPVItem->name, "ts_csa2_hardonly_en", 19))
        {
            ret = HI_UNF_ADVCA_GetHardCwSelStat((HI_BOOL *) &pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "ts_sp_hardonly_en", 17))
        {
        }
        else if(0==strncmp(pstPVItem->name, "ts_csa3_hardonly_en", 19))
        {
            ret = HI_UNF_ADVCA_GetCSA3HardCWStat((HI_BOOL *) &pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "tskl_csa3_disable", 16))
        {
        }
        else if(0==strncmp(pstPVItem->name, "misc_kl_disable", 18))
        {
        }
        else if(0==strncmp(pstPVItem->name, "gg_kl_disable", 19))
        {
        }
        else if(0==strncmp(pstPVItem->name, "dcas_kl_disable", 15))
        {
        }
        else if(0==strncmp(pstPVItem->name, "runtime_check_en", 16))
        {
        }
        else if(0==strncmp(pstPVItem->name, "ddr_wakeup_disable", 18))
        {
        }
        else if(0==strncmp(pstPVItem->name, "wakeup_ddr_check_en", 19))
        {
        }
        else if(0==strncmp(pstPVItem->name, "version_id_check_en", 19))
        {
            ret = HI_UNF_ADVCA_GetVersionCheckStat(&pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "bl_msid_check_en", 16))
        {
            ret = HI_UNF_ADVCA_GetBootMSIDCheckStat(&pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "jtag_prt_mode", 13))
        {
            ret = HI_UNF_ADVCA_GetJtagMode((HI_UNF_ADVCA_JTAG_MODE_E *) &pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "jtag_r_disable", 14))
        {
        }
        else if(0==strncmp(pstPVItem->name, "bload_dec_en", 12))
        {
            ret = HI_UNF_ADVCA_GetBootDecEnStat(&pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "self_boot_disable", 17))
        {
            ret = HI_UNF_ADVCA_GetSelfBootStat((HI_BOOL *) &pstPVItem->datavalue);
        }
        else if(0==strncmp(pstPVItem->name, "SCS_activation", 14))
        {
            HI_UNF_ADVCA_FLASH_TYPE_E enFlashType;
            ret = HI_UNF_ADVCA_GetSecBootStat((HI_BOOL *) &pstPVItem->datavalue, &enFlashType);
        }
        else if(0==strncmp(pstPVItem->name, "otp_globle_lock_en", 18))
        {
        }
        else
        {
            HI_DEBUG_ADVCA("Unknown PV Item ---->  %s\n", pstPVItem->name);
        }
        
        if(HI_SUCCESS != ret) 
        {
            HI_DEBUG_ADVCA("Get %s  value failed\n", pstPVItem->name);
        }
        else if(fp_pv_out)
        {
            fprintf(fp_pv_out, "%-32s  0x%x\n", pstPVItem->name, pstPVItem->datavalue);
        }
        else
        {
            HI_DEBUG_ADVCA("%-32s  0x%x\n", pstPVItem->name, pstPVItem->datavalue);
        }
    }

    if(fp_pv_out)
    {
        fprintf(fp_pv_out, "\n***************************************\n");
    }
    else
    {
        HI_DEBUG_ADVCA("\n***************************************\n");
    }

    return ret;
}


HI_S32 GetOTPValue(FILE * fp_pv_out)
{
    HI_S32 ret = HI_SUCCESS;
    HI_U32 *buf = HI_NULL;
    HI_U32 i;
	     
    buf = (HI_U32*)malloc(MAX_OTP_SIZE);
    if(HI_NULL == buf)
    {
        HI_DEBUG_ADVCA("malloc buffer error!\n");
        ret = HI_FAILURE;
        goto EXIT_CLOSE;
    }
    memset(buf, 0, MAX_OTP_SIZE / 4);
    
    for(i = 0; i < MAX_OTP_SIZE / 4; i++)
    {
        ret = HI_UNF_ADVCA_OtpRead(i * 4, buf + i);
		if(ret != HI_SUCCESS)
		{
			HI_DEBUG_ADVCA("Read OTP error!\n");
			goto EXIT_CLOSE;
		}
    }
    
    if(HI_NULL != fp_pv_out)
    {
//        fwrite(buf,1,MAX_OTP_SIZE,fp_pv_out);
        for(i = 0; i < MAX_OTP_SIZE / 4; i++)
        {
            if(0 == (i % 4))
            {
                fprintf(fp_pv_out, "\n%03x:  ", i);
            }
            if(0 == (i%4))
            {
                fprintf(fp_pv_out, " ");
            }
            fprintf(fp_pv_out, "%08x ", buf[i]);
        }
    }
    else
    {
        for(i = 0; i < MAX_OTP_SIZE / 4; i++)
        {
            if(0 == (i % 4))
            {
                printf("\n%03x:  ", i);
            }
            if(0 == (i % 4))
            {
                printf(" ");
            }
            printf("%08x ", buf[i]);
        }
    }

EXIT_CLOSE:    

    if(HI_NULL != buf)
    {
        free(buf);
    }
    return ret;
}


HI_S32 SetOTPValue(HI_VOID)
{
    HI_U32 num = sizeof(stDefaultPV)/sizeof(HI_OTP_PV_STRUCT_S);
    HI_OTP_PV_STRUCT_S   *pstPVItem;
    HI_U32 i;
    HI_S32 ret = HI_SUCCESS;
    
    for(i=0; i<num; i++)
    {
        pstPVItem = &stDefaultPV[i];
        switch(i)
        {
            case MSID:
                if(0==strncmp(pstPVItem->name, "MSID", 4))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        HI_U8 u8MarketId[4];
                        u8MarketId[0] = (pstPVItem->datavalue >> 24) & 0xFF;
                        u8MarketId[1] = (pstPVItem->datavalue >> 16) & 0xFF;
                        u8MarketId[2] = (pstPVItem->datavalue >> 8) & 0xFF;
                        u8MarketId[3] = pstPVItem->datavalue & 0xFF;
                        ret = HI_UNF_ADVCA_SetMarketId(u8MarketId);
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case Version_ID:
                if(0==strncmp(pstPVItem->name, "Version_ID", 10))
                {
                    HI_U8 u8VersionId[4];
                    u8VersionId[0] = (pstPVItem->datavalue >> 24) & 0xFF;
                    u8VersionId[1] = (pstPVItem->datavalue >> 16) & 0xFF;
                    u8VersionId[2] = (pstPVItem->datavalue >> 8) & 0xFF;
                    u8VersionId[3] = pstPVItem->datavalue & 0xFF;
                    ret = HI_UNF_ADVCA_SetVersionId(u8VersionId);
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case boot_mode_sel:
            case bootsel_ctrl:
                if((0==strncmp(pstPVItem->name, "boot_mode_sel", 13))||(0==strncmp(pstPVItem->name, "bootsel_ctrl", 12)))
                {
                    if((stDefaultPV[boot_mode_sel].datavalue != 0)||(stDefaultPV[bootsel_ctrl].datavalue != 0))
                    {
                        ret = HI_UNF_ADVCA_SetFlashTypeEx((HI_UNF_ADVCA_FLASH_TYPE_E)stDefaultPV[boot_mode_sel].datavalue);
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case link_prt_disable:
                if(0==strncmp(pstPVItem->name, "link_prt_disable", 16))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_DisableLinkProtection();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;
            
            case ts_csa2_hardonly_en:
                if(0==strncmp(pstPVItem->name, "ts_csa2_hardonly_en", 19))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_LockHardCwSel();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case ts_sp_hardonly_en:
                if(0==strncmp(pstPVItem->name, "ts_sp_hardonly_en", 17))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_LockSPHardCW();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case ts_csa3_hardonly_en:
                if(0==strncmp(pstPVItem->name, "ts_csa3_hardonly_en", 19))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_LockCSA3HardCW();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case tskl_csa3_disable:
                if(0==strncmp(pstPVItem->name, "tskl_csa3_disable", 17))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_TSKL_CSA3_DISABLE, NULL, 0);
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case misc_kl_disable:
                if(0==strncmp(pstPVItem->name, "misc_kl_disable", 15))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_MISC_KL_DISABLE, NULL, 0);
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case gg_kl_disable:
                if(0==strncmp(pstPVItem->name, "gg_kl_disable", 13))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_ConfigLockFlag(HI_UNF_ADVCA_LOCK_GG_KL_DISABLE, NULL, 0);
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case dcas_kl_disable:
                if(0==strncmp(pstPVItem->name, "dcas_kl_disable", 15))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_DisableDCasKl();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case runtime_check_en:
                if(0==strncmp(pstPVItem->name, "runtime_check_en", 16))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_EnableRuntimeCheck();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case ddr_wakeup_disable:
                if(0==strncmp(pstPVItem->name, "ddr_wakeup_disable", 18))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_DisableDDRWakeup();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case wakeup_ddr_check_en:
                if(0==strncmp(pstPVItem->name, "wakeup_ddr_check_en", 19))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_EnableDDRWakeupCheck();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case version_id_check_en:
                if(0==strncmp(pstPVItem->name, "version_id_check_en", 19))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_EnableVersionCheck();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case bl_msid_check_en:
                if(0==strncmp(pstPVItem->name, "bl_msid_check_en", 16))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_EnableBootMSIDCheck();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case jtag_prt_mode:
                if(0==strncmp(pstPVItem->name, "jtag_prt_mode", 13))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_SetJtagMode((HI_UNF_ADVCA_JTAG_MODE_E)pstPVItem->datavalue);
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case jtag_r_disable:
                if(0==strncmp(pstPVItem->name, "jtag_r_disable", 14))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_DisableJtagRead();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case bload_dec_en:
                if(0==strncmp(pstPVItem->name, "bload_dec_en", 12))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_LockBootDecEn();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case self_boot_disable:
                if(0==strncmp(pstPVItem->name, "self_boot_disable", 17))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_DisableSelfBoot();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case SCS_activation:
                if(0==strncmp(pstPVItem->name, "SCS_activation", 14))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_EnableSecBootEx();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            case otp_globle_lock_en:
                if(0==strncmp(pstPVItem->name, "otp_globle_lock_en", 18))
                {
                    if(pstPVItem->datavalue != 0)
                    {
                        ret = HI_UNF_ADVCA_LockGlobalOTP();
                    }
                }
                else
                {
                    HI_DEBUG_ADVCA("Invalid item, index [%d],  name [%s]\n", i, pstPVItem->name);
                }
            break;

            default:
                HI_DEBUG_ADVCA("Unknown PV Item ---->  %s\n", pstPVItem->name);
            break;
        }
        
        if(HI_SUCCESS != ret) 
        {
            HI_DEBUG_ADVCA("Set %s  to 0x%x failed\n", pstPVItem->name, pstPVItem->datavalue);
        }
    }

    return ret;
}

HI_S32 main(HI_S32 argc,HI_CHAR **argv)
{
    HI_S32 Ret = HI_SUCCESS;

    FILE * fp_pv_in = HI_NULL;
    FILE * fp_pv_out = HI_NULL;
    HI_CHAR *pFileNamePVCfg = HI_NULL;
    HI_CHAR *pFileNamePVOut = HI_NULL;
    HI_OTP_PV_STRUCT_S stPVCustomerCfg;
    HI_U32 operationmode = 0;
    HI_S32 count;

    if(argc < 3)
    {
        printf("Usage: ./product_pv_stb 0 pv_out   ----> get pv value\n");
        printf("Usage: ./product_pv_stb 1 pv_cfg [pv_out]   ---->  set pv value\n");
        return HI_FAILURE;
    }

    operationmode = strtol(argv[1],NULL,0);
    
    if(0 == operationmode)
    {
        pFileNamePVOut  = argv[2];
    }
    else
    {
        pFileNamePVCfg  = argv[2];
        if(argc > 3)
        {
            pFileNamePVOut  = argv[3];
        }
    }

    if(HI_NULL != pFileNamePVCfg)
    {
        fp_pv_in = fopen(pFileNamePVCfg,"rb");
        if(!fp_pv_in)
        {
            HI_DEBUG_ADVCA("open file %s error!\n", pFileNamePVCfg);
            Ret = HI_FAILURE;
            goto EXIT_CLOSE_FILE;
        }
    }

    if(HI_NULL != pFileNamePVOut)
    {
        fp_pv_out = fopen(pFileNamePVOut,"w");
        if(!fp_pv_out)
        {
            HI_DEBUG_ADVCA("open file %s error!\n",pFileNamePVOut);
            Ret = HI_FAILURE;
            goto EXIT_CLOSE_FILE;
        }
    }

    if(HI_NULL != fp_pv_in)
    {
        HI_DEBUG_ADVCA("\n*********** Get customer PV config list***********\n");
        while(1)
        {
            count = fscanf(fp_pv_in, "%32s %16x", stPVCustomerCfg.name, &stPVCustomerCfg.datavalue);
            if(count <= 0)
            {
                //HI_DEBUG_ADVCA("Read to end of the file\n");
                break;
            }
            Ret = SetPVItemValue(&stPVCustomerCfg);
        }    
    }

    Ret = HI_UNF_ADVCA_Init();
    if(HI_SUCCESS != Ret)
    {
        HI_DEBUG_ADVCA("call HI_UNF_ADVCA_Init() failed, ret=0x%x\n", Ret);
    }

    if(0 != operationmode)
    {
        HI_DEBUG_ADVCA("\n********  SET OTP VALUE *********\n");
        Ret = SetOTPValue();
    }

    {
        HI_DEBUG_ADVCA("\n********  GET OTP VALUE *********\n");
        Ret = GetOTPItemValue(fp_pv_out);
        Ret = GetOTPValue(fp_pv_out);
    }

    HI_UNF_ADVCA_DeInit();

    EXIT_CLOSE_FILE:
    if(HI_NULL != fp_pv_in)
    {
        fclose(fp_pv_in);
    }
    if(HI_NULL != fp_pv_out)
    {
        fclose(fp_pv_out);
    }

    HI_DEBUG_ADVCA("\r\n************ Set/Get PV List End, Ret=0x%x *************\n\n", Ret);
    
    return Ret;
}


