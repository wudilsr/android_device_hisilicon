/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfv2bO4a86Ra1cP5w/R608AW9MyvBFsCSDo8GzQMC4Jhtu/zShyENpjFzntvB+
qu9VLVUuS72cjjzhdOcAh1AoFu2SPGQB4KwicF18WNq5NI0cDY7LEW0tooizyBT2JeFNH9sI
KviE/AH+Ps+ustOoxRf6M0PZcPuC4ZQmkxW2lAwyFDNezh6MRbQZRBKuIA/q6A==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : drv_adsp_intf_k.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/04/17
  Description   :
  History       :
  1.Date        : 2013/04/17
    Author      : zgjie
    Modification: Created file

******************************************************************************/

/******************************* Include Files *******************************/

/* Sys headers */
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <mach/hardware.h>

/* Unf headers */
#include "hi_error_mpi.h"
#include "hi_reg_common.h"

/* Drv headers */
#include "drv_adsp_private.h"
#include "drv_adsp_ext.h"
#include "hi_audsp_common.h"
#include "hi_audsp_aoe.h"
#include "hi_audsp_aflt.h"

#ifdef HI_SND_DSP_HW_SUPPORT

/*kfile operation*/
 #include "kfile_ops_func.h"
 #include "dsp_elf_func.h"
 #include <asm/cacheflush.h>
#endif
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

/***************************** Macro Definition ******************************/
#if defined (HI_SND_AOE_SWSIMULATE_SUPPORT)
extern HI_S32 AOE_SwEngineCreate(HI_VOID);
extern HI_S32 AOE_SwEngineDestory(HI_VOID);
#endif

#if defined (HI_SND_AFLT_SWSIMULATE_SUPPORT)
extern HI_S32 AFLT_SwEngineCreate(HI_VOID);
extern HI_S32 AFLT_SwEngineDestory(HI_VOID);
#endif

#define ADSP_NAME "HI_ADSP"


#ifdef HI_SND_DSP_HW_SUPPORT
 #define ADSP_ELF_USE_ARRAY //defaule config
//#define ADSP_ELF_USE_FILE
 #define ADSP_ELFNAME "/mnt/HWAOE"

 #define AOE_COMBUFFER_ADDR_ALIGN (32)
 #define ELF_MAXLENGTH (2 * 1024 * 1024)
 #define WAITING_LOOP 10
#endif

#define ADSP_PROC_SUPPORT
/*************************** Structure Definition ****************************/

/* Global parameter */
typedef struct
{
    atomic_t                atmOpenCnt;     /* Open times */
    HI_BOOL                 bReady;         /* Init flag */
    ADSP_REGISTER_PARAM_S*  pstProcParam;   /* ADSP Proc functions */

    ADSP_EXPORT_FUNC_S stExtFunc;      /* ADSP extenal functions */
    ADSP_SETTINGS_S stADSPSetting;
} ADSP_GLOBAL_PARAM_S;

static volatile S_ADSP_CHN_REGS_TYPE *        g_pADSPSysCrg = NULL;

#ifdef ADSP_PROC_SUPPORT
static HI_U32 g_u32AoeRegAddr = 0;
static HI_U32 g_u32AfltRegAddr = 0;
#endif

/***************************** Global Definition *****************************/

/***************************** Static Definition *****************************/
#ifdef HI_SND_DSP_HW_SUPPORT
static ADSP_AOESYS_CMD_RET_E  ADSP_AOE_Ack(HI_VOID)
{
    volatile HI_U32 loop = 0;
    U_ADSP_CTRL          ADSP_SYSCTRL;

    for (loop = 0; loop < 100; loop++)
    {
        //udelay(1000);
        msleep(1);
        ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
        if (ADSP_SYSCTRL.bits.aoe_cmd_done)
        {
            return (ADSP_AOESYS_CMD_RET_E)ADSP_SYSCTRL.bits.aoe_cmd_return_value;
        }
    }

    return ADSP_AOE_CMD_ERR_TIMEOUT;
}

static HI_S32 ADSP_AOE_SetCmd(ADSP_AOESYS_CMD_E newcmd)
{
    ADSP_AOESYS_CMD_RET_E Ack;
    U_ADSP_CTRL          ADSP_SYSCTRL;
    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;

    switch (newcmd)
    {
    case ADSP_AOE_CMD_START:
        ADSP_SYSCTRL.bits.aoe_cmd = ADSP_AOE_CMD_START;
        break;

    case ADSP_AOE_CMD_STOP:
        ADSP_SYSCTRL.bits.aoe_cmd = ADSP_AOE_CMD_STOP;
        break;

    default:

        //HI_WARN_AO("ADSP_AOE unknow Cmd(0x%x)",newcmd);
        return HI_SUCCESS;
    }

    ADSP_SYSCTRL.bits.aoe_cmd_done = 0;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 =  ADSP_SYSCTRL.u32;

    Ack = ADSP_AOE_Ack();
    if (ADSP_AOE_CMD_DONE != Ack)
    {
        HI_ERR_ADSP("\nADSP_AOE SetCmd(0x%x) failed(0x%x)", newcmd, Ack);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static ADSP_AFLTSYS_CMD_RET_E  ADSP_AFLT_Ack(HI_VOID)
{
    volatile HI_U32 loop = 0;
    U_ADSP_CTRL          ADSP_SYSCTRL;

    for (loop = 0; loop < 100; loop++)
    {
        //udelay(1000);
        msleep(1);
        ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
        if (ADSP_SYSCTRL.bits.aflt_cmd_done)
        {
            return (ADSP_AFLTSYS_CMD_RET_E)ADSP_SYSCTRL.bits.aflt_cmd_return_value;
        }
    }

    return ADSP_AFLT_CMD_ERR_TIMEOUT;
}

static HI_S32 ADSP_AFLT_SetCmd(ADSP_AFLTSYS_CMD_E newcmd)
{
    ADSP_AFLTSYS_CMD_RET_E Ack;
    U_ADSP_CTRL          ADSP_SYSCTRL;
    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;

    switch (newcmd)
    {
    case ADSP_AFLT_CMD_START:
        ADSP_SYSCTRL.bits.aflt_cmd = ADSP_AFLT_CMD_START;
        break;

    case ADSP_AFLT_CMD_STOP:
        ADSP_SYSCTRL.bits.aflt_cmd = ADSP_AFLT_CMD_STOP;
        break;

    default:

        //HI_WARN_AO("ADSP_AOE unknow Cmd(0x%x)",newcmd);
        return HI_SUCCESS;
    }

    ADSP_SYSCTRL.bits.aflt_cmd_done = 0;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 =  ADSP_SYSCTRL.u32;

    Ack = ADSP_AFLT_Ack();
    if (ADSP_AFLT_CMD_DONE != Ack)
    {
        HI_ERR_ADSP("\nADSP_AFLT SetCmd(0x%x) failed(0x%x)", newcmd, Ack);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static ADSP_SYSCOM_CMD_RET_E  ADSP_SYS_Ack(HI_VOID)
{
    volatile HI_U32 loop = 0;
    U_ADSP_CTRL          ADSP_SYSCTRL;

    for (loop = 0; loop < 100; loop++)
    {
        //udelay(1000);
        msleep(1);
        ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
        if (ADSP_SYSCTRL.bits.sys_cmd_done)
        {
            return (ADSP_SYSCOM_CMD_RET_E)ADSP_SYSCTRL.bits.sys_cmd_return_value;
        }
    }

    return ADSP_SYSCOM_CMD_ERR_TIMEOUT;
}

static HI_S32 ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_E newcmd, HI_BOOL bBlock)
{
    ADSP_AOESYS_CMD_RET_E Ack;
    U_ADSP_CTRL          ADSP_SYSCTRL;

    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;

    switch (newcmd)
    {
    case ADSP_SYSCOM_CMD_START:
        ADSP_SYSCTRL.bits.sys_cmd = ADSP_SYSCOM_CMD_START;
        break;

    case ADSP_SYSCOM_CMD_STOP:
        ADSP_SYSCTRL.bits.sys_cmd = ADSP_SYSCOM_CMD_STOP;
        break;

    default:

        //HI_WARN_AO("ADSP_AOE unknow Cmd(0x%x)",newcmd);
        return HI_SUCCESS;
    }

    ADSP_SYSCTRL.bits.sys_cmd_done = 0;
    g_pADSPSysCrg->ADSP_SYSCTRL.u32 =  ADSP_SYSCTRL.u32;
    if (HI_TRUE == bBlock)
    {
        Ack = ADSP_SYS_Ack();
        if (ADSP_SYSCOM_CMD_DONE != Ack)
        {
            HI_ERR_ADSP("\nADSP_SYS SetCmd(0x%x) failed(0x%x)\n", newcmd, Ack);
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

#endif

static HI_S32 ADSP_LoadFirmware(ADSP_CODEID_E u32DspCodeId)
{
    HI_S32 sRet = HI_FAILURE;

    switch (u32DspCodeId)
    {
    case ADSP_CODE_AOE:
#if defined (HI_SND_AOE_SWSIMULATE_SUPPORT)
        sRet = AOE_SwEngineCreate();
#else
        sRet = ADSP_AOE_SetCmd(ADSP_AOE_CMD_START);
#endif
        break;

    case ADSP_CODE_AFLT:
#if defined (HI_SND_AFLT_SWSIMULATE_SUPPORT)
        sRet = AFLT_SwEngineCreate();
#else
        sRet = ADSP_AFLT_SetCmd(ADSP_AFLT_CMD_START);
#endif
        break;

    default:
        HI_ERR_ADSP("dont support DspCode(%d)\n", u32DspCodeId);
        break;
    }

    return sRet;
}

static HI_S32 ADSP_UnLoadFirmware(ADSP_CODEID_E u32DspCodeId)
{
    HI_S32 sRet = HI_SUCCESS;

    switch (u32DspCodeId)
    {
    case ADSP_CODE_AOE:
#if defined (HI_SND_AOE_SWSIMULATE_SUPPORT)
        sRet = AOE_SwEngineDestory();
#else
        sRet = ADSP_AOE_SetCmd(ADSP_AOE_CMD_STOP);
#endif
        break;

     case ADSP_CODE_AFLT:
#if defined (HI_SND_AOE_SWSIMULATE_SUPPORT)
        sRet = AFLT_SwEngineDestory();
#else
        sRet = ADSP_AFLT_SetCmd(ADSP_AFLT_CMD_STOP);
#endif
        break;

    default:
        HI_WARN_ADSP("dont support DspCode(%d)\n", u32DspCodeId);
        break;
    }

    return sRet;
}

static HI_S32 ADSP_GetFirmwareInfo(ADSP_CODEID_E u32DspCodeId, ADSP_FIRMWARE_INFO_S* pstFrm)
{
    if ((HI_NULL == pstFrm))
    {
        HI_ERR_ADSP("Bad param!\n");
        return HI_FAILURE;
    }

    // todo

    return HI_SUCCESS;
}

static HI_S32 ADSP_GetAoeFwmInfo(ADSP_CODEID_E u32DspCodeId, ADSP_FIRMWARE_AOE_INFO_S* pstInfo)
{
    HI_S32 Ret = HI_SUCCESS;

    switch (u32DspCodeId)
    {
    case ADSP_CODE_AOE:
#if defined (HI_SND_AOE_SWSIMULATE_SUPPORT)
        pstInfo->bAoeSwFlag = HI_TRUE;
#else
        pstInfo->bAoeSwFlag = HI_FALSE;
#endif
        break;
    default:
        HI_ERR_ADSP("dont support DspCode(%d)\n", u32DspCodeId);
        Ret= HI_FAILURE;
        break;
    }

    return Ret;
}

static ADSP_GLOBAL_PARAM_S s_stAdspDrv =
{
    .atmOpenCnt                    = ATOMIC_INIT(0),
    .bReady                        = HI_FALSE,

    /*
        .stDefCfg =
        {
            .enType         = HI_UNF_VCODEC_TYPE_H264,
            .enMode         = HI_UNF_VCODEC_MODE_NORMAL,
            .u32ErrCover    = 100,
            .bOrderOutput   = 0,
            .u32Priority    = 15
        },
     */
    .pstProcParam                  = HI_NULL,

    //.pDmxFunc = HI_NULL,
    //.pVfmwFunc = HI_NULL,
    //.pfnWatermark = HI_NULL,
    .stExtFunc                     =
    {
        .pfnADSP_LoadFirmware      = ADSP_LoadFirmware,
        .pfnADSP_UnLoadFirmware    = ADSP_UnLoadFirmware,
        .pfnADSP_GetFirmwareInfo   = ADSP_GetFirmwareInfo,
        .pfnADSP_GetAoeFwmInfo     = ADSP_GetAoeFwmInfo,
        .pfnADSP_DrvResume         = ADSP_DRV_Resume,
        .pfnADSP_DrvSuspend        = ADSP_DRV_Suspend,
    }
};

/*********************************** Code ************************************/
#ifdef HI_SND_DSP_HW_SUPPORT

 #if defined ADSP_ELF_USE_ARRAY
HI_UCHAR dsp_elf_array[] = {
  #include "firmware/hififw.dat"
};
 #endif

static HI_S32 Dsp_LoadElf(HI_VOID)
{
    HI_UCHAR *pcELFBuf = HI_NULL;
    pcELFBuf = HI_VMALLOC(ADSP_ID_AOE, ELF_MAXLENGTH);
    if(HI_NULL == pcELFBuf)
    {
        HI_FATAL_ADSP("pcELFBuf HI_VMALLOC fail\n");
        return HI_FAILURE;
    }
    memset((HI_VOID*)pcELFBuf, 0, ELF_MAXLENGTH);

 #ifdef  ADSP_ELF_USE_FILE
    //1. read elf file
    struct file *fpELF;
    HI_U32 u32readsize = 0;
    fpELF = kfile_open(ADSP_ELFNAME, O_RDONLY, 0);
    if (HI_NULL == fpELF)
    {
        HI_FATAL_ADSP("ELF file %s open fail\n", ADSP_ELFNAME);
        HI_VFREE(ADSP_ID_AOE, pcELFBuf);
        return HI_FAILURE;
    }

    u32readsize = kfile_read(pcELFBuf, ELF_MAXLENGTH, fpELF);
    if (u32readsize <= 0)
    {
        HI_FATAL_ADSP("ELF file  read fail\n");
        kfile_close(fpELF);
        HI_VFREE(ADSP_ID_AOE, pcELFBuf);
        return -EACCES;
    }

    kfile_close(fpELF);
    HI_INFO_ADSP("Read ELF file size 0x%x \n", u32readsize);

 #elif defined ADSP_ELF_USE_ARRAY
    memcpy(pcELFBuf, dsp_elf_array, sizeof(dsp_elf_array));
    HI_INFO_ADSP("Read ELF array size 0x%x \n", sizeof(dsp_elf_array));
 #endif

    //2. load elf file
    //copy elf to reg and ddr
    CopyELFSection(pcELFBuf);

    //flush cache to ddr (all size)
    __cpuc_flush_dcache_area(phys_to_virt(DSP_DDR_CODE_BASEADDR), DSP_DDR_CODE_MAXSIZE);
    outer_flush_range(DSP_DDR_CODE_BASEADDR, DSP_DDR_CODE_MAXSIZE);

    //check elf copyed right
    if (CheckELFPaser(pcELFBuf) == HI_FAILURE)
    {
        HI_FATAL_ADSP("ELF Load  fail\n");
        HI_VFREE(ADSP_ID_AOE, pcELFBuf);
        return HI_FAILURE;
    }

    HI_VFREE(ADSP_ID_AOE, pcELFBuf);

    return HI_SUCCESS;
}

static HI_S32 Dsp_ResetBoot(HI_VOID)
{
    U_PERI_CRG52 uTmpVal1;
    HI_S32 s32Ret;
    //remap reg

#if    defined(CHIP_TYPE_hi3751v100)    \
    || defined(CHIP_TYPE_hi3796cv100)   \
    || defined(CHIP_TYPE_hi3798cv100)
    U_DSP_CTRL  uTmpVal;
    //3. reset dsp
    uTmpVal.u32 = g_pstRegPeri->DSP_CTRL.u32;

#ifdef ADSP_SELLECT_DSP0
    uTmpVal.bits.peri_wdg1_en_dsp0 = 0;
    uTmpVal.bits.peri_ocdhaltonreset_dsp0 = 0;
 #if 1  //boot from bootreg
    uTmpVal.bits.peri_statvectorsel_dsp0 = 0;
 #else //boot from ddr
    uTmpVal.bits.peri_statvectorsel_dsp0 = 1;
 #endif
    uTmpVal.bits.peri_runstall_dsp0 = 0;
#endif

#ifdef ADSP_SELLECT_DSP1
    uTmpVal.bits.peri_wdg1_en_dsp1 = 0;
    uTmpVal.bits.peri_ocdhaltonreset_dsp1 = 0;

 #if 1  //boot from bootreg
    uTmpVal.bits.peri_statvectorsel_dsp1 = 0;
 #else //boot from ddr
    uTmpVal.bits.peri_statvectorsel_dsp1 = 1;
 #endif
    uTmpVal.bits.peri_runstall_dsp1 = 0;
#endif

    g_pstRegPeri->DSP_CTRL.u32 = uTmpVal.u32;

#ifdef ADSP_SELLECT_DSP0
    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp_clk_sel = 1;           //300M
    uTmpVal1.bits.dsp0_cken = 1;            //dsp0 clk enable
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp0_srst_req = 1;          //dsp0 bus sreset
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp0_srst_req = 0;
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;
#endif

#ifdef ADSP_SELLECT_DSP1
    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    //uTmpVal1.u32 = 0x77;
    uTmpVal1.bits.dsp_clk_sel = 1;           //S5 300M
//    uTmpVal1.bits.dsp0_cken = 1;                  //dsp0 clk enable   //s5 use dsp1 with big cache
    uTmpVal1.bits.dsp1_cken = 1;            //dsp1 clk enable
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp1_srst_req = 1;     //dsp1 bus sreset
//    uTmpVal1.bits.dsp0_srst_req = 1;          //dsp0 bus sreset
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp1_srst_req = 0;
//    uTmpVal1.bits.dsp0_srst_req = 0;
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;
#endif
#else  //#if defined CHIP_TYPE_hi3751v100
    U_DSP0_CTRL  uTmpVal;
        //3. reset dsp
    uTmpVal.u32 = g_pstRegPeri->DSP0_CTRL.u32;
    uTmpVal.bits.wdg1_en_dsp0 = 0;
    uTmpVal.bits.ocdhaltonreset_dsp0 = 0;

 #if 1  //boot from bootreg
    uTmpVal.bits.statvectorsel_dsp0 = 0;
 #else //boot from ddr
    uTmpVal.bits.statvectorsel_dsp0 = 1;
 #endif
    uTmpVal.bits.runstall_dsp0 = 0;
    g_pstRegPeri->DSP0_CTRL.u32 = uTmpVal.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;

    uTmpVal1.u32 = 0x77;
    uTmpVal1.bits.dsp_clk_sel = 0;  //345.6M
    //uTmpVal1..bits.dsp_cken = 1;
    uTmpVal1.bits.dsp0_cken = 1;   //dsp0 clk enable
    //uTmpVal1.bits.dsp1_cken = 0;   //dsp1 clk disable
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp_srst_req  = 1;  //dsp bus sreset
    uTmpVal1.bits.dsp0_srst_req = 1;   //dsp0 sreset
    //uTmpVal1.bits.dsp1_srst_req = 1;   //dsp0 sreset
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;

    uTmpVal1.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal1.bits.dsp_srst_req  = 0;
    uTmpVal1.bits.dsp0_srst_req = 0;
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal1.u32;
#endif  //#if defined CHIP_TYPE_hi3751v100

    //4. check dsp running
 #if 1
     s32Ret = ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_START, HI_TRUE);
     if (HI_SUCCESS != s32Ret)
     {
         HI_FATAL_ADSP("Dsp start  fail: 0x%x!\n", s32Ret);
         return s32Ret;
     }
 #else
    HI_INFO_ADSP("u32RunningFlagVirtAddr=0x%x  \n", u32RunningFlagVirtAddr);
    pdsp0_running_flag_addr = (HI_U32 *)u32RunningFlagVirtAddr;

    if (HI_NULL == pdsp0_running_flag_addr)
    {
        HI_FATAL_ADSP("IoRemap Dsp0 Running Flag addr  fail\n");
        return HI_FAILURE;
    }

    while (0 == u32RunFlagCheck)
    {
        u32WaitingLoop++;
        if (*pdsp0_running_flag_addr != AOE_RUNNING_FLAG)
        {
            if (u32WaitingLoop == WAITING_LOOP)
            {
                HI_FATAL_ADSP("Dsp0 Start TimeOut \n");
                break;
            }
            else
            {
                udelay(1000);
            }
        }
        else
        {
            u32RunFlagCheck = 1;
        }
    }

    if (0 != u32RunFlagCheck)
    {
        HI_INFO_ADSP("Dsp0 running, And The Value 0x%x \n", *(volatile HI_U32 *)pdsp0_running_flag_addr);
    }
    else
    {
        HI_FATAL_ADSP("Dsp0 running Failed  \n");
        return HI_FAILURE;
    }
 #endif

    return HI_SUCCESS;
}

#endif

HI_S32 ADSP_DRV_Open(struct inode *inode, struct file  *filp)
{
    if (atomic_inc_return(&s_stAdspDrv.atmOpenCnt) == 1)
    {}

    return HI_SUCCESS;
}

HI_S32 ADSP_DRV_Release(struct inode *inode, struct file  *filp)
{
    /* Not the last close, only close the channel match with the 'filp' */
    if (atomic_dec_return(&s_stAdspDrv.atmOpenCnt) != 0)
    {}
    /* Last close */
    else
    {}

    return HI_SUCCESS;
}

#if defined (HI_SND_AOE_SWSIMULATE_SUPPORT)

#define  ADSP_DEBUG_PROC
#ifdef ADSP_DEBUG_PROC

HI_VOID ADSP_Debug_Proc(HI_U32 u32DebugId, HI_U32 u32DebugVal)
{
    if(DSP_DEBUG_REG_NUM <= u32DebugId)
    {
        return;
    }

    if(HI_NULL == g_pADSPSysCrg)
    {
        return;
    }

    g_pADSPSysCrg->ADSP_DEBUG[u32DebugId] = u32DebugVal;

    return;
}
#endif

#endif

#ifdef ADSP_PROC_SUPPORT
const HI_U32 ADSP_AOE_RateProc(HI_U32 u32Rate)
{
    HI_U32 g_u32RateTab[] =
    {
      8000,
      11025,
      12000,
      16000,
      22050,
      24000,
      32000,
      44100,
      48000,
      88200,
      96000,
      176400,
      192000,
    };

    if (u32Rate < sizeof(g_u32RateTab)/sizeof(g_u32RateTab[0]))
    {
        return g_u32RateTab[u32Rate];
    }

    return 0;
}

const HI_U32  ADSP_AOE_ChProc(HI_U32 ch)
{
    switch (ch)
    {
    case 0x00:
        return 1;
    case 0x01:
        return 2;
    case 0x03:
        return 8;
    default:
        return 0;
    }
}

const HI_U32  ADSP_AOE_WidthProc(HI_U32 width)
{
    switch (width)
    {
    case 0x00:
        return 8;
    case 0x01:
        return 16;
    case 0x02:
        return 24;
    default:
        return 0;
    }
}

const HI_CHAR *  ADSP_AOE_StatusName(HI_U32 u32Cmd, HI_U32 u32Done)
{
    const HI_CHAR *apcName[4] =
    {
        "start",
        "stop",
        "pause",
        "flush",
    };

    if(u32Done == 0 || u32Cmd >= 4)
    {
        return "invalid";
    }

    return apcName[u32Cmd];
}

const HI_CHAR *ADSP_AFLT_CmdName(AFLT_CMD_E enCmd)
{
    const HI_CHAR *apcName[AFLT_CMD_BUTT] =
    {
        "Create",
        "Destroy",
        "Start",
        "Stop",
        "SetParam",
        "GetParam",
        "SetConfig",
        "GetConfig",
        "RestoreSetting",
        "StoreSetting",
        "InitInbuf",
        "DeInitInbuf",
        "InitOutbuf",
        "DeInitOutbuf",
    };

    if (enCmd < AFLT_CMD_BUTT)
    {
        return apcName[enCmd];
    }

    return "UnknownCmd";
}

const HI_CHAR *ADSP_AFLT_CompName(AFLT_COMPONENT_ID_E enComp)
{
    const HI_CHAR *apcName[AFLT_BUTT] =
    {
        "BaseEffect",
        "SRS3DEffect",
        "DolbyDV258",
        "DDPDecode",
        "TrueHDDecode",
        "DTSHDDecode",
        "PcmDecode",
        "MP3Decode",
        "MP3XADecode",
        "DTSHDXADecode"
    };

    if (enComp < AFLT_BUTT)
    {
        return apcName[enComp];
    }

    return "UnknownComp";
}

const HI_U32 ADSP_BufUsedSizeProc(HI_U32 u32Size, HI_U32 u32ReadPtr, HI_U32 u32WritePtr)
{
    if(u32ReadPtr <= u32WritePtr)
    {
        return u32WritePtr - u32ReadPtr;
    }
    else
    {
        return u32Size - (u32ReadPtr - u32WritePtr);
    }
}

const HI_U32 ADSP_BufUsedPercProc(HI_U32 u32Size, HI_U32 u32UsedSize)
{
    if(0 == u32Size)
    {
        return 0;
    }
    else
    {
        return u32UsedSize * 100 / u32Size;
    }
}

const HI_U32 ADSP_BufLatencyMsProc(HI_U32 u32UsedSize, HI_U32 u32FrameSize, HI_U32 u32Rate)
{
    if(0 == u32FrameSize || 0 == u32Rate)
    {
        return 0;
    }
    else
    {
        return (u32UsedSize / u32FrameSize) * 1000 / u32Rate;
    }
}
const HI_U32 ADSP_FrameSizeProc(HI_U32 u32BitWidth, HI_U32 u32Channel)
{
    if(16 == u32BitWidth)
    {
        return u32Channel * sizeof(HI_S16);
    }
    else
    {
        return u32Channel * sizeof(HI_S32);
    }
}
static HI_VOID ADSP_AOE_Proc(struct seq_file *p, HI_VOID *v)
{
    HI_U32 i;
    HI_U32 j = 0;
    S_AOE_REGS_TYPE   *pComReg;
    S_MIXER_REGS_TYPE *pEneReg;
    S_AIP_REGS_TYPE   *pAipReg;
    S_AOP_REGS_TYPE   *pAopReg;
    HI_U32* pRptr;
    HI_U32* pWptr;
    HI_U32 u32UsedSize = 0, u32FrameSize = 0, u32AipId = AOE_MAX_AIP_NUM, u32AopId = 0;
#ifdef HI_SND_TIMER_CAST
    S_CAST_REGS_TYPE   *pCastReg;
    HI_U32 tmp = 0;
#endif

    PROC_PRINT( p, "\n---------------------------------  AOE Status  -------------------------------------------\n");

    pComReg =  (S_AOE_REGS_TYPE *)g_u32AoeRegAddr;
    PROC_PRINT( p,
            "CommonStatus   :ExecuteTimeOutCnt(%d), ScheduleTimeOutCnt(%d)\n",
             pComReg->AOE_STATUS1.bits.excute_timeout_cnt, pComReg->AOE_STATUS1.bits.schedule_timeout_cnt);

    for(i = 0; i < AOE_MAX_ENGINE_NUM; i++)
    {
        pEneReg = (S_MIXER_REGS_TYPE *)(g_u32AoeRegAddr + AOE_ENGINE_REG_OFFSET + i * sizeof(S_MIXER_REGS_TYPE));
        if((pEneReg->ENGINE_CTRL.bits.cmd == 0 || pEneReg->ENGINE_CTRL.bits.cmd == 2)  //when start or pause, proc
            && pEneReg->ENGINE_CTRL.bits.cmd_done == 1)
        {
            PROC_PRINT( p,
                        "ENGINE(%d)   :Status(%s), Format(%s), Rate(%d), Ch(%d), Width(%d), AefMask(0x%x)\n",
                         i,
                         ADSP_AOE_StatusName(pEneReg->ENGINE_CTRL.bits.cmd, pEneReg->ENGINE_CTRL.bits.cmd_done),
                         pEneReg->ENGINE_ATTR.bits.format == 0 ? "pcm" : "iec61937",
                         ADSP_AOE_RateProc(pEneReg->ENGINE_ATTR.bits.fs),
                         ADSP_AOE_ChProc(pEneReg->ENGINE_ATTR.bits.ch),
                         ADSP_AOE_WidthProc(pEneReg->ENGINE_ATTR.bits.precision),
                         pEneReg->ENGINE_ATT_AEF.bits.aef_att_ena);

            for (j = 0; j < AOE_MAX_AIP_NUM; j++)
            {
                if((pEneReg->ENGINE_MIX_SRC.bits.aip_fifo_ena) & (1L<<j))
                {
                    pAipReg = (S_AIP_REGS_TYPE *)(g_u32AoeRegAddr + AOE_AIP_REG_OFFSET + j * sizeof(S_AIP_REGS_TYPE));
                    PROC_PRINT( p,
                                "Aip(%d)      :Status(%s), Mute(%s), Vol(%ddB/%ddB), ChMode(%d)\n",
                                 j,
                                 ADSP_AOE_StatusName(pAipReg->AIP_CTRL.bits.cmd, pAipReg->AIP_CTRL.bits.cmd_done),
                                 (0 == pAipReg->AIP_EXT_CTRL.bits.mute) ? "Off" : "On",
                                 (HI_S32)(pAipReg->AIP_EXT_CTRL.bits.volume_l) - 0x79,
                                 (HI_S32)(pAipReg->AIP_EXT_CTRL.bits.volume_r) - 0x79,
                                          pAipReg->AIP_EXT_CTRL.bits.channel_mode);
                    if (pAipReg->AIP_FIFO_ATTR.bits.fifo_bypass == 1)
                    {
                        u32AipId = j;
                    }
                    if(1 == pAipReg->AIP_BUF_SIZE.bits.buff_flag)
                    {
#ifdef HI_SND_DSP_HW_SUPPORT
                        pRptr = (HI_U32*)IO_ADDRESS(pAipReg->AIP_BUF_RPTR);
                        pWptr = (HI_U32*)IO_ADDRESS(pAipReg->AIP_BUF_WPTR);
#else
                        pRptr = (HI_U32*)pAipReg->AIP_BUF_RPTR;
                        pWptr = (HI_U32*)pAipReg->AIP_BUF_WPTR;
#endif
                    }
                    else
                    {
                        pRptr = (HI_U32 *)(&pAipReg->AIP_BUF_RPTR);
                        pWptr = (HI_U32 *)(&pAipReg->AIP_BUF_WPTR);
                    }
                    u32UsedSize = ADSP_BufUsedSizeProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, *pRptr, *pWptr);
                    u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAipReg->AIP_BUFF_ATTR.bits.aip_precision), ADSP_AOE_ChProc(pAipReg->AIP_BUFF_ATTR.bits.aip_ch));
                    PROC_PRINT( p,
                                "            :Buff Format(%s), Rate(%.6d), Ch(%d), Width(%d), Addr(0x%.8x), Size/Used/Latency(0x%.6x/%d%%/%dms), Rptr/Wptr(0x%.6x/0x%.6x)\n",
                                 (0 == pAipReg->AIP_BUFF_ATTR.bits.aip_format) ? "pcm" : "iec61937",
                                 ADSP_AOE_RateProc(pAipReg->AIP_BUFF_ATTR.bits.aip_fs),
                                 ADSP_AOE_ChProc(pAipReg->AIP_BUFF_ATTR.bits.aip_ch),
                                 ADSP_AOE_WidthProc(pAipReg->AIP_BUFF_ATTR.bits.aip_precision),
                                 pAipReg->AIP_BUF_ADDR,
                                 pAipReg->AIP_BUF_SIZE.bits.buff_size,
                                 ADSP_BufUsedPercProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, u32UsedSize),
                                 ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAipReg->AIP_BUFF_ATTR.bits.aip_fs)),
                                 *pRptr,
                                 *pWptr);
                    u32UsedSize = ADSP_BufUsedSizeProc(pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_size, pAipReg->AIP_FIFO_RPTR, pAipReg->AIP_FIFO_WPTR);
                    u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_precision), ADSP_AOE_ChProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_ch));
                    PROC_PRINT( p,
                                "            :Fifo Format(%s), Rate(%.6d), Ch(%d), Width(%d), Addr(0x%.8x), Size/Used/Latency/Underflow(0x%.4x/%d%%/%dms/%d), Rptr/Wptr(0x%.4x/0x%.4x)\n",
                                 (0 == pAipReg->AIP_FIFO_ATTR.bits.fifo_format) ? "pcm" : "iec61937",
                                 ADSP_AOE_RateProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_fs),
                                 ADSP_AOE_ChProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_ch),
                                 ADSP_AOE_WidthProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_precision),
                                 pAipReg->AIP_FIFO_ADDR,
                                 pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_size,
                                 ADSP_BufUsedPercProc(pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_size, u32UsedSize),
                                 ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAipReg->AIP_FIFO_ATTR.bits.fifo_fs)),
                                 pAipReg->AIP_FIFO_SIZE.bits.aip_fifo_underflow_cnt,
                                 pAipReg->AIP_FIFO_RPTR,
                                 pAipReg->AIP_FIFO_WPTR);
                }
            }
            for (j = 0; j < AOE_MAX_AOP_NUM; j++)
            {
                if((pEneReg->ENGINE_ROU_DST.bits.aop_buf_ena) & (1L<<j))
                {
                    pAopReg = (S_AOP_REGS_TYPE *)(g_u32AoeRegAddr + AOE_AOP_REG_OFFSET + j * sizeof(S_AOP_REGS_TYPE));
#ifdef HI_SND_TIMER_CAST
                    if(pAopReg->AOP_BUFF_ATTR.bits.buf_priority == HI_FALSE)
                    {
                    PROC_PRINT( p,
                            "Aop(%d,Cast) :Status(%s), AefBypass(%s), Vol(%ddB/%ddB), Mute(%s), Latency(%dms)\n",
                                 j,
                                 ADSP_AOE_StatusName(pAopReg->AOP_CTRL.bits.cmd, pAopReg->AOP_CTRL.bits.cmd_done),
                             (0 == pAopReg->AOP_CTRL.bits.ena_aef_bypass) ? "Off" : "On",
                             (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_l) - 0x79,
                             (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_l) - 0x79,
                             (0 == pAopReg->AOP_EXT_CTRL.bits.mute) ? "Off" : "On",
                             pAopReg->AOP_BUFF_ATTR.bits.buf_latency);
                    }
                    else
#endif
                    {
                        PROC_PRINT( p,
                                    "Aop(%d)      :Status(%s), AefBypass(%s), Vol(%ddB/%ddB), mute(%s), Latency(%dms)\n",
                                     j,
                                     ADSP_AOE_StatusName(pAopReg->AOP_CTRL.bits.cmd, pAopReg->AOP_CTRL.bits.cmd_done),
                                     (0 == pAopReg->AOP_CTRL.bits.ena_aef_bypass) ? "Off" : "On",
                                     (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_l) - 0x79,
                                     (HI_S32)(pAopReg->AOP_EXT_CTRL.bits.volume_r) - 0x79,
                                     (0 == pAopReg->AOP_EXT_CTRL.bits.mute) ? "Off" : "On",
                                     pAopReg->AOP_BUFF_ATTR.bits.buf_latency);
                    }
                    if(1 == pAopReg->AOP_BUF_SIZE.bits.buff_flag)
                    {
#ifdef HI_SND_DSP_HW_SUPPORT
                        pRptr = (HI_U32*)IO_ADDRESS(pAopReg->AOP_BUF_RPTR);
                        pWptr = (HI_U32*)IO_ADDRESS(pAopReg->AOP_BUF_WPTR);
#else
                        pRptr = (HI_U32*)pAopReg->AOP_BUF_RPTR;
                        pWptr = (HI_U32*)pAopReg->AOP_BUF_WPTR;
#endif
                    }
                    else  //Aop is Cast
                    {
                        pRptr = (HI_U32 *)(&pAopReg->AOP_BUF_RPTR);
                        pWptr = (HI_U32 *)(&pAopReg->AOP_BUF_WPTR);
                    }
                    u32UsedSize = ADSP_BufUsedSizeProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, *pRptr, *pWptr);
                    u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision), ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch));
                    PROC_PRINT( p,
                            "            :Buff Format(%s), Rate(%.6d), Ch(%d), Width(%d), Addr(0x%.8x), Size/Used/Latency(0x%.4x/%d%%/%dms), Rptr/Wptr(0x%.4x/0x%.4x)\n",
                                 pAopReg->AOP_BUFF_ATTR.bits.buf_format == 0 ? "pcm" : "iec61937",
                                 ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs),
                                 ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch),
                             ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision),
                             pAopReg->AOP_BUF_ADDR,
                             pAopReg->AOP_BUF_SIZE.bits.buff_size,
                             ADSP_BufUsedPercProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, u32UsedSize),
                             ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs)),
                             *pRptr,
                             *pWptr
                             );
#ifdef HI_SND_TIMER_CAST
                    if(pAopReg->AOP_BUFF_ATTR.bits.buf_priority == HI_FALSE)//Aop is Cast
                    {
                        for (tmp = 0; tmp < AOE_MAX_CAST_NUM; tmp++)
                        {
                            pCastReg = (S_CAST_REGS_TYPE *)(g_u32AoeRegAddr + AOE_CAST_REG_OFFSET + tmp * sizeof(S_CAST_REGS_TYPE));
                            if(pCastReg->CAST_ATTR == j)
                            {
                                PROC_PRINT( p,
                                            "            :BuffWritCnt(Total/Nomal/AddMute)(%.6u/%.6u/%.6u), BuffOverWriteCnt(%.6u)\n",
                                            pCastReg->CAST_BUF_WRITETOTAL_CNT,
                                            pCastReg->CAST_BUF_WRITEOK_CNT,
                                            pCastReg->CAST_BUF_WRITEMUTE_CNT,
                                            pCastReg->CAST_BUF_OVERWRITE_CNT);

                                u32UsedSize = ADSP_BufUsedSizeProc(pCastReg->CAST_FIFO_SIZE, pCastReg->CAST_FIFO_RPTR, pCastReg->CAST_FIFO_WPTR);
                                PROC_PRINT( p,
                                            "            :FIFO Size/Used/Latency(0x%.4x/%d%%/%dms), Rptr/Wptr(0x%.4x/0x%.4x), FIFOWrite(Try/OK)(%.6u/%.6u), ForceFIFOReadCnt(%.6u)\n",
                                             pCastReg->CAST_FIFO_SIZE,
                                            ADSP_BufUsedPercProc(pCastReg->CAST_FIFO_SIZE, u32UsedSize),
                                            ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs)),
                                             pCastReg->CAST_FIFO_RPTR,
                                            pCastReg->CAST_FIFO_WPTR,

                                            pCastReg->CAST_FIFO_TRY_CNT,
                                            pCastReg->CAST_FIFO_OK_CNT,
                                            pCastReg->CAST_FIFO_FORCE_READ_CNT);
                            }

                        }
                    }
#endif

                }
            }
            PROC_PRINT( p, "\n");
        }
    }
	
	    if (u32AipId != AOE_MAX_AIP_NUM)
    {
        pAipReg = (S_AIP_REGS_TYPE *)(g_u32AoeRegAddr + AOE_AIP_REG_OFFSET + u32AipId * sizeof(S_AIP_REGS_TYPE));
        if(1 == pAipReg->AIP_BUF_SIZE.bits.buff_flag)
        {
#ifdef HI_SND_DSP_HW_SUPPORT
            pRptr = (HI_U32*)IO_ADDRESS(pAipReg->AIP_BUF_RPTR);
            pWptr = (HI_U32*)IO_ADDRESS(pAipReg->AIP_BUF_WPTR);
#else
            pRptr = (HI_U32*)pAipReg->AIP_BUF_RPTR;
            pWptr = (HI_U32*)pAipReg->AIP_BUF_WPTR;
#endif
        }
        else
        {
            pRptr = (HI_U32 *)(&pAipReg->AIP_BUF_RPTR);
            pWptr = (HI_U32 *)(&pAipReg->AIP_BUF_WPTR);
        }
        u32UsedSize = ADSP_BufUsedSizeProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, *pRptr, *pWptr);
        u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAipReg->AIP_BUFF_ATTR.bits.aip_precision), ADSP_AOE_ChProc(pAipReg->AIP_BUFF_ATTR.bits.aip_ch));
        PROC_PRINT( p,
                    "Karaoke     :Aip(%d), Size/Used/Latency(0x%.6x/%d%%/%dms)\n",
                    u32AipId,
                    pAipReg->AIP_BUF_SIZE.bits.buff_size,
                    ADSP_BufUsedPercProc(pAipReg->AIP_BUF_SIZE.bits.buff_size, u32UsedSize),
                    ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAipReg->AIP_BUFF_ATTR.bits.aip_fs))
                    );
        pAopReg = (S_AOP_REGS_TYPE *)(g_u32AoeRegAddr + AOE_AOP_REG_OFFSET + u32AopId * sizeof(S_AOP_REGS_TYPE));
        if(1 == pAopReg->AOP_BUF_SIZE.bits.buff_flag)
        {
#ifdef HI_SND_DSP_HW_SUPPORT
            pRptr = (HI_U32*)IO_ADDRESS(pAopReg->AOP_BUF_RPTR);
            pWptr = (HI_U32*)IO_ADDRESS(pAopReg->AOP_BUF_WPTR);
#else
            pRptr = (HI_U32*)pAopReg->AOP_BUF_RPTR;
            pWptr = (HI_U32*)pAopReg->AOP_BUF_WPTR;
#endif
        }
        else  //Aop is Cast
        {
            pRptr = (HI_U32 *)(&pAopReg->AOP_BUF_RPTR);
            pWptr = (HI_U32 *)(&pAopReg->AOP_BUF_WPTR);
        }
        u32UsedSize = ADSP_BufUsedSizeProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, *pRptr, *pWptr);
        u32FrameSize = ADSP_FrameSizeProc(ADSP_AOE_WidthProc(pAopReg->AOP_BUFF_ATTR.bits.buf_precision), ADSP_AOE_ChProc(pAopReg->AOP_BUFF_ATTR.bits.buf_ch));
        PROC_PRINT( p,
                    "            :Aop(%d), Size/Used/Latency(0x%.4x/%d%%/%dms)\n",
                    u32AopId,
                    pAopReg->AOP_BUF_SIZE.bits.buff_size,
                    ADSP_BufUsedPercProc(pAopReg->AOP_BUF_SIZE.bits.buff_size, u32UsedSize),
                    ADSP_BufLatencyMsProc(u32UsedSize, u32FrameSize, ADSP_AOE_RateProc(pAopReg->AOP_BUFF_ATTR.bits.buf_fs))
                     );
    }


    return;
}
#if defined(CHIP_TYPE_hi3751v100)
static HI_VOID ADSP_AFLT_Proc(struct seq_file *p, HI_VOID *v)
{
    HI_U32 i;
    S_AFLT_REGS_TYPE *pAfltReg;
    S_AFLT_COM_ATTR  *pAfltComReg;

    PROC_PRINT( p, "\n---------------------------------  AFLT Status  ------------------------------------------\n");

    pAfltComReg = (S_AFLT_COM_ATTR  *)g_u32AfltRegAddr;

    PROC_PRINT( p,
            "ComStatus  :ExecuteTimeOutCnt(%d)\n",
             pAfltComReg->AFLT_STATUS0.bits.timeout_cnt);

    PROC_PRINT( p, "\n");

    for(i = 0; i < AFLT_MAX_CHAN_NUM; i++)
    {
        pAfltReg = (S_AFLT_REGS_TYPE *)(g_u32AfltRegAddr + AFLT_CHN_REG_OFFSET + i * sizeof(S_AFLT_REGS_TYPE));
        if(pAfltReg->ATTR.bits.use_flag)  //aflt be created //TODO
        {
            PROC_PRINT( p,
                        "AFLT(%d) :Type(%s), CompName(%s), Status(%s), MsgPoolAddr(0x%x), MsgPoolSize(0x%x)\n",
                         i,
                         (pAfltReg->ATTR.bits.master_flag == 0)?"slave":"master",
                         ADSP_AFLT_CompName(pAfltReg->ATTR.bits.filter_id),
                         (pAfltReg->ATTR.bits.status == 0)?"stop":"start",
                         pAfltReg->MSGPOOL_ADDR,
                         pAfltReg->ATTR.bits.msgpool_size);

            PROC_PRINT( p,
                        "        :SettingIndex(0x%x), SettingSize(0x%x), CmdType(%s), CmdStatus(%s), CmdRetVal(%d)\n",
                         pAfltReg->CTRL.bits.param_index,
                         pAfltReg->CTRL.bits.param_wordsize,
                         ADSP_AFLT_CmdName((AFLT_CMD_E)pAfltReg->CTRL.bits.cmd),
                         (pAfltReg->CTRL.bits.cmd_done==1)?"done":"no done",
                         pAfltReg->CTRL.bits.cmd_return_value);
            if(pAfltReg->ATTR.bits.master_flag == 1)
            {
                PROC_PRINT( p,
                            "        :PtsBoundary(0x%x), InbufAddr(0x%x), InbufSize/Used(0x%x/%d%%), InbufRptr/Wptr(0x%x/0x%x), StreamReadPos(0x%x)\n",
                             pAfltReg->IPBUF_BOUNDARY,
                             pAfltReg->IP_BUF_ADDR,
                             pAfltReg->IP_BUF_SIZE.bits.inbuff_size,
                             ADSP_BufUsedPercProc(pAfltReg->IP_BUF_SIZE.bits.inbuff_size, ADSP_BufUsedSizeProc(pAfltReg->IP_BUF_SIZE.bits.inbuff_size, pAfltReg->IP_BUF_RPTR, pAfltReg->IP_BUF_WPTR)),
                             pAfltReg->IP_BUF_RPTR,
                             pAfltReg->IP_BUF_WPTR,
                             pAfltReg->READPOS);
                PROC_PRINT( p,
                            "        :InfifoAddr(0x%x), InfifoSize(0x%x), InfifoRptr(0x%x), InfifoBytesLeft(0x%x)\n",
                             pAfltReg->IP_FIFO_ADDR,
                             pAfltReg->IP_FIFO_SIZE,
                             pAfltReg->IP_FIFO_RPTR,
                             pAfltReg->IP_FIFO_BYTES);
                PROC_PRINT( p,
                            "        :OutbufAddr(0x%x), OutbufPeriodSize(0x%x), OutbufPeriodNum(0x%x), OutbufRidx/Widx(0x%x(%d)/0x%x(%d))\n",
                             pAfltReg->OP_BUF_ADDR,
                             pAfltReg->OP_BUF_SIZE.bits.periond_size,
                             pAfltReg->OP_BUF_SIZE.bits.periond_num,
                             pAfltReg->OP_BUF_RIDX.bits.periond_read_idx,
                             pAfltReg->OP_BUF_RIDX.bits.periond_read_wrap,
                             pAfltReg->OP_BUF_WIDX.bits.periond_write_idx,
                             pAfltReg->OP_BUF_WIDX.bits.periond_write_wrap);
            }
            PROC_PRINT( p,
                        "        :TryCnt(%d), FrameCnt(%d), ErrFrameCnt(%d), ExcuteTimeOutCnt(%d), ScheduleTimeOutCnt(%d)\n",
                         pAfltReg->TRY_EXE_CNT,
                         pAfltReg->STATUS0.bits.frame_cnt,
                         pAfltReg->STATUS0.bits.frame_err_cnt,
                         pAfltReg->TIMEOUT.bits.exe_timeout_cnt,
                         pAfltReg->TIMEOUT.bits.sche_timeout_cnt);
            PROC_PRINT( p, "\n");
        }
    }

    return;
}
#endif
static HI_VOID ADSP_COM_Proc(struct seq_file *p, HI_VOID *v)
{
    HI_U32 j;

    PROC_PRINT( p, "\n---------------------------------  Common Status  ------------------------------------------\n");
    PROC_PRINT( p, "DebugValue     :");
    for(j = 0; j < DSP_DEBUG_REG_NUM; j++)
    {
        PROC_PRINT( p,
                    "Debug%d(0x%x/%d)",
                     j,
                     g_pADSPSysCrg->ADSP_DEBUG[j],
                     g_pADSPSysCrg->ADSP_DEBUG[j]);
        if((j + 1) % 4)  //a line 4 reg
        {
            PROC_PRINT( p, ", ");
        }
        else
        {
            PROC_PRINT( p, "\n                ");
        }
    }
    PROC_PRINT( p, "\n");
    return;
}
HI_S32 ADSP_DRV_ReadProc(struct seq_file *p, HI_VOID *v)
{
    ADSP_AOE_Proc(p, v);
#if defined(CHIP_TYPE_hi3751v100)
    ADSP_AFLT_Proc(p, v);
#endif
    ADSP_COM_Proc(p, v);
    return HI_SUCCESS;
    }

HI_S32 ADSP_DRV_WriteProc(struct file * file,
                                   const char __user * buf, size_t count, loff_t *ppos)
{
    return count;
}
#endif

HI_S32 ADSP_DRV_RegisterProc(ADSP_REGISTER_PARAM_S *pstParam)
{
#ifdef ADSP_PROC_SUPPORT
    // todo
    HI_CHAR aszBuf[16];
    DRV_PROC_ITEM_S*  pProcItem;

    /* Check parameters */
    if (HI_NULL == pstParam)
    {
        return HI_FAILURE;
    }

    s_stAdspDrv.pstProcParam = pstParam;

    /* Create proc */
    snprintf(aszBuf, sizeof(aszBuf), "*adsp");
    pProcItem = HI_DRV_PROC_AddModule(aszBuf, HI_NULL, HI_NULL);
    if (!pProcItem)
    {
        HI_FATAL_ADSP("Create adsp proc entry fail!\n");
        return HI_FAILURE;
    }

    /* Set functions */
    pProcItem->read  = s_stAdspDrv.pstProcParam->pfnReadProc;
    pProcItem->write = s_stAdspDrv.pstProcParam->pfnWriteProc;
#endif
    return HI_SUCCESS;
}

HI_VOID ADSP_DRV_UnregisterProc(HI_VOID)
{
#ifdef ADSP_PROC_SUPPORT
    // todo
    HI_CHAR aszBuf[16];

    snprintf(aszBuf, sizeof(aszBuf), "*adsp");
    HI_DRV_PROC_RemoveModule(aszBuf);
    /* Unregister */

    /* Clear param */
    s_stAdspDrv.pstProcParam = HI_NULL;
#endif
    return;
}

HI_S32 ADSP_HW_PowerOn(HI_VOID)
{
#ifdef HI_SND_DSP_HW_SUPPORT
    HI_S32 s32Ret;
    U_ADSP_CTRL          ADSP_SYSCTRL;

    ADSP_SYSCTRL.u32 = g_pADSPSysCrg->ADSP_SYSCTRL.u32;
    ADSP_SYSCTRL.u32 = 0;
    ADSP_SYSCTRL.bits.sys_cmd_done = 1;
    ADSP_SYSCTRL.bits.aoe_cmd_done = 1;
    ADSP_SYSCTRL.bits.aflt_cmd_done = 1;

    g_pADSPSysCrg->ADSP_SYSCTRL.u32 =  ADSP_SYSCTRL.u32;
    //HI_FATAL_ADSP("AdspCtrlReg: 0x%x!\n", g_pADSPSysCrg->ADSP_CtrlReg.u32);

    s32Ret = Dsp_LoadElf();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("Dsp load Elf  fail: 0x%x!\n", s32Ret);
        return s32Ret;
    }

    s32Ret = Dsp_ResetBoot();
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("Dsp Boot  fail: 0x%x!\n", s32Ret);
        return s32Ret;
    }

#endif


    return HI_SUCCESS;
}

HI_VOID ADSP_HW_PowerOff(HI_VOID)
{
#ifdef HI_SND_DSP_HW_SUPPORT
    U_PERI_CRG52 uTmpVal;
    uTmpVal.u32 = g_pstRegCrg->PERI_CRG52.u32;
    uTmpVal.bits.dsp0_srst_req = 1;   //dsp0 sreset
    uTmpVal.bits.dsp0_cken = 0;   //dsp0 clk disable
    g_pstRegCrg->PERI_CRG52.u32 = uTmpVal.u32;

    ADSP_SYS_SetCmd(ADSP_SYSCOM_CMD_STOP, HI_FALSE);

#endif
}

static HI_VOID ADSP_GetSettings(HI_VOID)
{
}

static HI_VOID ADSP_RestoreSettings(HI_VOID)
{
}

HI_S32 ADSP_DRV_Suspend(PM_BASEDEV_S *pdev, pm_message_t state)
{
    ADSP_GetSettings();
    ADSP_HW_PowerOff();

    // todo
    HI_PRINT("ADSP suspend OK\n");
    return HI_SUCCESS;
}
HI_S32 HI_DRV_ADSP_Init(HI_VOID)
{
    return ADSP_DRV_Init();
}

HI_VOID HI_DRV_ADSP_DeInit(HI_VOID)
{
    ADSP_DRV_Exit();
}

HI_S32 ADSP_DRV_Resume(PM_BASEDEV_S *pdev)
{
    ADSP_RestoreSettings();
    if (HI_SUCCESS != ADSP_HW_PowerOn())
    {
        HI_FATAL_ADSP("Resume ADSP_HW_PowerOn fail \n");
        return HI_FAILURE;
    }

    // todo
    HI_PRINT("ADSP resume OK\n");
    return HI_SUCCESS;
}

HI_S32 ADSP_DRV_Init(HI_VOID)
{
    HI_S32 s32Ret;

    s32Ret = HI_DRV_MODULE_Register(HI_ID_ADSP, ADSP_NAME, (HI_VOID*)&s_stAdspDrv.stExtFunc);
    if (HI_SUCCESS != s32Ret)
    {
        HI_FATAL_ADSP("Reg module fail:%#x!\n", s32Ret);
        return s32Ret;
    }
        g_pADSPSysCrg = (volatile S_ADSP_CHN_REGS_TYPE * )ioremap_nocache(DSP0_SHARESRAM_CHAN0_BASEADDR, sizeof(S_ADSP_CHN_REGS_TYPE));

#ifdef ADSP_PROC_SUPPORT
    g_u32AoeRegAddr = (HI_U32 )ioremap_nocache(AOE_COM_REG_BASE, AOE_REG_LENGTH);
    g_u32AfltRegAddr = (HI_U32 )ioremap_nocache(AFLT_COM_REG_BASE, AFLT_REG_LENGTH);
#endif

    if (HI_SUCCESS != ADSP_HW_PowerOn())
    {
        HI_FATAL_ADSP("ADSP_HW_PowerOn fail \n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_VOID ADSP_DRV_Exit(HI_VOID)
{
    ADSP_HW_PowerOff();

#ifdef ADSP_PROC_SUPPORT
    if(g_u32AoeRegAddr)
        iounmap((HI_VOID*)g_u32AoeRegAddr);
    if(g_u32AfltRegAddr)
        iounmap((HI_VOID*)g_u32AfltRegAddr);
#endif

    if(g_pADSPSysCrg)
        iounmap((HI_VOID*)g_pADSPSysCrg);

    HI_DRV_MODULE_UnRegister(HI_ID_ADSP);

    return;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* End of #ifdef __cplusplus */
