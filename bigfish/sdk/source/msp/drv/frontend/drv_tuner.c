/***********************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: drv_tuner.c
 * Description:
 *
 * History:
 * Version   Date             Author       DefectNum    Description
 * main\1    2007-08-03   w54542      NULL            Create this file.
 * main\1    2007-11-10   w54542      NULL            modify this file.
 ***********************************************************************************/
//#include <linux/config.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include <linux/kthread.h>
#include <linux/delay.h>

#include "hi_type.h"

#include "drv_i2c_ext.h"
#include "hi_drv_file.h"

#include "drv_gpioi2c_ext.h"
#include "drv_gpio_ext.h"
#include "hi_drv_gpioi2c.h"
#include "hi_debug.h"


#include "hi_drv_stat.h"
#include "hi_drv_dev.h"
#include "hi_drv_reg.h"
#include "hi_kernel_adapt.h"
#include "hi_drv_proc.h"
#include "hi_drv_module.h"
#include "hi_drv_mmz.h"


#include "drv_tuner_ext.h"
#include "drv_tuner_ioctl.h"
#include "hi_drv_diseqc.h"
#include "drv_demod.h"

#include "cd1616.h"
#include "alps_tdae.h"
#include "tda18250.h"
#include "tda18250b.h"
#include "tmx7070x.h"
#include "mxl203.h"
#include "tdcc.h"
#include "xg_3bl.h"
#include "mt_2081.h"
#include "mxl603.h"
#include "mxl608.h"
#include "r_820c.h"
#include "si2147.h"
#include "av2011.h"
#include "av2018.h"
#include "sharp_qm1d1c004x.h"
#include "RDA5815.h"
#include "M88TS2022.h"
#include "tda182i5a.h"
#include "hi_unf_i2c.h"

#include "isl9492.h"
#include "mps8125.h"
#include "tda6651.h"

#define		MOTOR_STORE_POSITION_MAX_NUM			64

I2C_EXT_FUNC_S *s_tuner_pI2cFunc   = HI_NULL;
GPIO_EXT_FUNC_S *s_tuner_pGpioFunc = HI_NULL;
GPIO_I2C_EXT_FUNC_S *s_tuner_pGpioI2cFunc = HI_NULL;

HI_DECLARE_MUTEX(g_TunerMutex);
static atomic_t s_atomicTunerAvailble = ATOMIC_INIT(0);

static HI_U32 s_u32InsideQamPort = 0;
//static HI_U32 s_u32ResetGpioNo[TUNER_NUM] = {0};
static HI_U32 gs_u32MidFreq = 11700;

typedef struct
{
    HI_UNF_TUNER_FE_LNB_CONFIG_S    stLNBConfig;/* LNB configuration */
    HI_UNF_TUNER_FE_LNB_POWER_E     enLNBPower; /* LNB power */
    HI_UNF_TUNER_FE_POLARIZATION_E  enPolar;    /* LNB polarization */
    HI_UNF_TUNER_FE_LNB_22K_E       enLNB22K;   /* LNB 22K on or off */
    HI_UNF_TUNER_SWITCH_22K_E       enSwitch22K;
    HI_UNF_TUNER_SWITCH_TONEBURST_E enToneBurst;
} TUNER_STATUS_SAT_S;

static TUNER_STATUS_SAT_S s_stMCESatPara[TUNER_NUM];

TUNER_ATTR s_stSatTunerResumeInfo[TUNER_NUM] = {{0}, {0}, {0}, {0}, {0}};

HI_U32 s_u32ResetGpioNo[TUNER_NUM] = {0};
HI_U32 g_u32ResetCruGpioNo =0;
TUNER_OPS_S g_stTunerOps[TUNER_NUM] = {{0},{0},{0},{0},{0}};

HI_U32 g_xtal_clk_table[TUNER_NUM] = {XTAL_CLK, XTAL_CLK, XTAL_CLK, XTAL_CLK, XTAL_CLK};
HI_U32 g_demod_address[TUNER_NUM] = {QAM_PORT0_ADDR, QAM_PORT1_ADDR, QAM_PORT2_ADDR, QAM_PORT3_ADDR, QAM_PORT4_ADDR};
HI_U32 g_halftuner_address[TUNER_NUM] = {TUNER_PORT0_ADDR, TUNER_PORT1_ADDR, TUNER_PORT2_ADDR, TUNER_PORT3_ADDR, TUNER_PORT3_ADDR};

 HI_U32 u32Cgr57RegVal = 0;
 HI_U32 u32Cgr58RegVal = 0;
 HI_U32 u32QAMAddrRegVal = 0;
 HI_U32 u32TsCKRegVal = 0;
 HI_U32 g_u32CrgEnableFlag = 0;

static HI_UNF_TUNER_LOCK_STATUS_E s_enTunerStat[TUNER_NUM] =
{
    HI_UNF_TUNER_SIGNAL_DROPPED,
    HI_UNF_TUNER_SIGNAL_DROPPED,
    HI_UNF_TUNER_SIGNAL_DROPPED,
    HI_UNF_TUNER_SIGNAL_DROPPED,
    HI_UNF_TUNER_SIGNAL_DROPPED
};

HI_BOOL g_bLockFlag = HI_FALSE;
wait_queue_head_t g_QamSpecialProcessWQ;
static struct task_struct *pThread;

typedef union
{
	struct
	{
		HI_U32 Position1:	1;	/*bit[0]*/
		HI_U32 Position2:	1;	/*bit[1]*/
		HI_U32 Position3:	1;	/*bit[2]*/
		HI_U32 Position4:	1;
		HI_U32 Position5:	1;
		HI_U32 Position6:	1;
		HI_U32 Position7:	1;
		HI_U32 Position8:	1;
		HI_U32 Position9:	1;
		HI_U32 Position10:	1;
		HI_U32 Position11:	1;
		HI_U32 Position12:	1;
		HI_U32 Position13:	1;
		HI_U32 Position14:	1;
		HI_U32 Position15:	1;
		HI_U32 Position16:	1;
		HI_U32 Position17:	1;
		HI_U32 Position18:	1;
		HI_U32 Position19:	1;
		HI_U32 Position20:	1;
		HI_U32 Position21:	1;
		HI_U32 Position22:	1;
		HI_U32 Position23:	1;
		HI_U32 Position24:	1;
		HI_U32 Position25:	1;
		HI_U32 Position26:	1;
		HI_U32 Position27:	1;
		HI_U32 Position28:	1;
		HI_U32 Position29:	1;
		HI_U32 Position30:	1;
		HI_U32 Position31:	1;
		HI_U32 Position32:	1;
		HI_U32 Position33:	1;
		HI_U32 Position34:	1;
		HI_U32 Position35:	1;
		HI_U32 Position36:	1;
		HI_U32 Position37:	1;
		HI_U32 Position38:	1;
		HI_U32 Position39:	1;
		HI_U32 Position40:	1;
		HI_U32 Position41:	1;
		HI_U32 Position42:	1;
		HI_U32 Position43:	1;
		HI_U32 Position44:	1;
		HI_U32 Position45:	1;
		HI_U32 Position46:	1;
		HI_U32 Position47:	1;
		HI_U32 Position48:	1;
		HI_U32 Position49:	1;
		HI_U32 Position50:	1;
		HI_U32 Position51:	1;
		HI_U32 Position52:	1;
		HI_U32 Position53:	1;
		HI_U32 Position54:	1;
		HI_U32 Position55:	1;
		HI_U32 Position56:	1;
		HI_U32 Position57:	1;
		HI_U32 Position58:	1;
		HI_U32 Position59:	1;
		HI_U32 Position60:	1;
		HI_U32 Position61:	1;
		HI_U32 Position62:	1;
		HI_U32 Position63:	1;
		HI_U32 Position64:	1;        
        }bits;

	HI_U32 u32Flags[2];
}U32_MOTOR_FLAG;

typedef struct
{
    HI_UNF_TUNER_DISEQC_SWITCH4PORT_S stPort1_0;
    HI_UNF_TUNER_DISEQC_SWITCH16PORT_S stPort1_1;
	U32_MOTOR_FLAG						stMotorFlag;
	HI_S16								s16MotorPos;
	HI_S16								s16EastLimit;
	HI_S16								s16WestLimit;
	HI_S16								s16StorePos[MOTOR_STORE_POSITION_MAX_NUM];
} DISEQC_DRV_STATUS_S;

static DISEQC_DRV_STATUS_S s_stDiSEqCDrvStatus[TUNER_NUM] =
{
    {
        .stPort1_0 = 
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X, 
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H, 
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 = 
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X, 
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        },
        .stMotorFlag.u32Flags[0] = 0,
        .stMotorFlag.u32Flags[1] = 0,
        .s16MotorPos = 0,
        .s16EastLimit = 0,
        .s16WestLimit = 0,
        .s16StorePos = {0}
    },
    {
        .stPort1_0 = 
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X, 
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H, 
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 = 
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X, 
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        },
        .stMotorFlag.u32Flags[0] = 0,
        .stMotorFlag.u32Flags[1] = 0,
        .s16MotorPos = 0,
        .s16EastLimit = 0,
        .s16WestLimit = 0,
        .s16StorePos = {0}
    },
    {
        .stPort1_0 = 
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X, 
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H, 
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 = 
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X, 
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        },
        .stMotorFlag.u32Flags[0] = 0,
        .stMotorFlag.u32Flags[1] = 0,
        .s16MotorPos = 0,
        .s16EastLimit = 0,
        .s16WestLimit = 0,
        .s16StorePos = {0}
    }
};

/* check tuner port whether it's in valid range */
static HI_S32 tuner_check_port(HI_U32 u32TunerPort)
{
    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_VOID tuner_reset_diseqc(HI_VOID)
{
	HI_U32 i,j;

	for(i = 0;i < TUNER_NUM;i++)
	{
		s_stDiSEqCDrvStatus[i].stPort1_0.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
        s_stDiSEqCDrvStatus[i].stPort1_0.enPort = HI_UNF_TUNER_DISEQC_SWITCH_NONE;
        s_stDiSEqCDrvStatus[i].stPort1_0.enPolar = HI_UNF_TUNER_FE_POLARIZATION_H;
        s_stDiSEqCDrvStatus[i].stPort1_0.enLNB22K = HI_UNF_TUNER_FE_LNB_22K_OFF;

		s_stDiSEqCDrvStatus[i].stPort1_1.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
		s_stDiSEqCDrvStatus[i].stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_NONE;

		s_stDiSEqCDrvStatus[i].s16MotorPos = 0;
		s_stDiSEqCDrvStatus[i].s16EastLimit = 0;
		s_stDiSEqCDrvStatus[i].s16WestLimit = 0;
		s_stDiSEqCDrvStatus[i].stMotorFlag.u32Flags[0] = 0;
		s_stDiSEqCDrvStatus[i].stMotorFlag.u32Flags[1] = 0;

		for(j = 0;j < (sizeof(s_stDiSEqCDrvStatus[i].s16StorePos)/sizeof(HI_S16));j++)
		{
			s_stDiSEqCDrvStatus[i].s16StorePos[j] = 0;
		}
	}
}

static HI_S32 tuner_parse_diseqc_cmd(HI_UNF_TUNER_DISEQC_SENDMSG_S *pstDiseqcMsg, DISEQC_DRV_STATUS_S *pstDisec)
{
	HI_U32 u32SwitchPort = 0;
	HI_S16 s16MotorMove = 0;
	HI_U8  u8PosNum = 0;
	
	if((HI_NULL == pstDiseqcMsg) || (HI_NULL == pstDisec))
	{
		HI_ERR_TUNER("ptr is null.\n");
		return HI_FAILURE;
	}

	switch(pstDiseqcMsg->au8Msg[COMMAND_BYTE])
	{
		case CMD_WRITE_N0:
			u32SwitchPort = (pstDiseqcMsg->au8Msg[DATA_BYTE_0] >> 2) & 0x3;
			if(0 == u32SwitchPort)
				pstDisec->stPort1_0.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_1;
			else if(1 == u32SwitchPort)
				pstDisec->stPort1_0.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_2;
			else if(2 == u32SwitchPort)
				pstDisec->stPort1_0.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_3;
			else
				pstDisec->stPort1_0.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_4;

			break;
		case CMD_WRITE_N1:
			u32SwitchPort = pstDiseqcMsg->au8Msg[DATA_BYTE_0] & 0xF;
			if(0 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_1;
			else if(1 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_2;
			else if(2 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_3;
			else if(3 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_4;
			else if(4 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_5;
			else if(5 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_6;
			else if(6 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_7;
			else if(7 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_8;
			else if(8 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_9;
			else if(9 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_10;
			else if(10 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_11;
			else if(11 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_12;
			else if(12 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_13;
			else if(13 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_14;
			else if(14 == u32SwitchPort)
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_15;
			else
				pstDisec->stPort1_1.enPort = HI_UNF_TUNER_DISEQC_SWITCH_PORT_16;
				
			break;
		case CMD_DRIVE_EAST:
			s16MotorMove= 0xff - pstDiseqcMsg->au8Msg[DATA_BYTE_0] + 1;
			pstDisec->s16MotorPos +=  s16MotorMove;
			//printk("%s:s16MotorMove:%d,s16MotorPos:%d\n",__FUNCTION__,s16MotorMove,pstDisec->s16MotorPos);
			break;
		case CMD_DRIVE_WEST:
			s16MotorMove= 0xff - pstDiseqcMsg->au8Msg[DATA_BYTE_0] + 1;
			pstDisec->s16MotorPos -=  s16MotorMove;
			//printk("%s:s16MotorMove:%d,s16MotorPos:%d\n",__FUNCTION__,s16MotorMove,pstDisec->s16MotorPos);
			break;
		case CMD_LIMIT_E:
			pstDisec->s16EastLimit = 1;
			break;
		case CMD_LIMIT_W:
			pstDisec->s16WestLimit = 1;
			break;
		case CMD_LIMITS_OFF:
			pstDisec->s16EastLimit = pstDisec->s16WestLimit = 0;
			break;
		case CMD_RESET:
			tuner_reset_diseqc();
			break;
		case CMD_STORE_NN:
                    u8PosNum = pstDiseqcMsg->au8Msg[DATA_BYTE_0];
                    if((u8PosNum <= 31))
                    {
                        pstDisec->stMotorFlag.u32Flags[0] |= (1 << u8PosNum);
                    }
                    else if((u8PosNum > 31)&&(u8PosNum <= 63))
                    {
                        pstDisec->stMotorFlag.u32Flags[1] |= (1 << (u8PosNum - 32));
                    }
                    else
                    {
                        HI_ERR_TUNER("tuner motor position error,it should be less than 64.the current position:%d\n", u8PosNum);
						return HI_FAILURE;
                    }
                    pstDisec->s16StorePos[u8PosNum] = pstDisec->s16MotorPos;
                    break;
	}

    return HI_SUCCESS;
}

/* register tuner standard interface function */
HI_S32 tuner_select_type(HI_U32 u32TunerPort, HI_TunerAttr_S *pstTunerAttr,
                         HI_DemodAttr_S *pstDemodAttr, HI_U32 u32ResetGpioNo)
{
    HI_U8 u8DataTmp = 0;
    HI_U32 u32RegVal = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 u8ChipReset = 0;
#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)|| defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    U_PERI_CRG58 unTmpPeriCrg58;
    unTmpPeriCrg58.u32 = g_pstRegCrg->PERI_CRG58.u32;
#endif
    UNUSED(s32Ret);
    UNUSED(u32RegVal);
    UNUSED(u8DataTmp);
    UNUSED(u8ChipReset);

    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }
	
	g_stTunerOps[u32TunerPort].enSigType = pstTunerAttr->enSigType;
    g_stTunerOps[u32TunerPort].enTunerDevType = pstTunerAttr->enTunerDevType;
    g_stTunerOps[u32TunerPort].enDemodDevType = pstDemodAttr->enDemodDevType;
    s_u32ResetGpioNo[u32TunerPort] = u32ResetGpioNo;

    g_stTunerOps[u32TunerPort].u32TunerAddress = pstTunerAttr->u32TunerAddr;
    g_stTunerOps[u32TunerPort].u32DemodAddress = pstDemodAttr->u32DemodAddr;

    g_stTunerOps[u32TunerPort].recalculate_signal_strength = NULL;
    g_stTunerOps[u32TunerPort].manage_after_chipreset = NULL;
    g_stTunerOps[u32TunerPort].tuner_resume = NULL;

    g_u32ResetCruGpioNo =u32ResetGpioNo;

    switch (g_stTunerOps[u32TunerPort].enDemodDevType)
    {
#if defined(DEMOD_DEV_TYPE_HI3130)
        case HI_UNF_DEMOD_DEV_TYPE_3130E:
        {
            tuner_chip_reset(u32ResetGpioNo);
            qam_read_byte(u32TunerPort, MCTRL_1_ADDR, &u8DataTmp);

            if ((u8DataTmp >> 5) == 5)
            {
                hi3130v200_set_hard_reg_value(u32TunerPort);
                s_u32InsideQamPort = u32TunerPort;
                g_stTunerOps[u32TunerPort].tuner_connect = hi3130v200_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status = hi3130v200_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber = hi3130v200_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr = hi3130v200_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type = hi3130v200_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = hi3130v200_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc = hi3130v200_test_single_agc;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = hi3130v200_get_freq_symb_offset;
                g_stTunerOps[u32TunerPort].manage_after_chipreset = hi3130v200_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers = hi3130v200_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs = hi3130v200_get_rs;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout = hi3130v200_connect_timeout;
                g_stTunerOps[u32TunerPort].tuner_set_ts_out = hi3130v200_set_ts_out;
                HI_INFO_TUNER("tuner port %d's demod type is hi3130v200 outside\n", u32TunerPort);
            }
            else
            {
                s_u32InsideQamPort = u32TunerPort;
                g_stTunerOps[u32TunerPort].tuner_connect = hi3130_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status = hi3130_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber = hi3130_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr = hi3130_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type = hi3130_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = hi3130_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc = hi3130_test_single_agc;
                g_stTunerOps[u32TunerPort].manage_after_chipreset = hi3130_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers = hi3130_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs = hi3130_get_rs;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout = hi3130_connect_timeout;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = hi3130_get_freq_symb_offset;
                HI_INFO_TUNER("tuner port %d's demod type is hi3130 outside\n", u32TunerPort);
            }
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_X5HDQAM) || defined(DEMOD_DEV_TYPE_X5HDV2QAM)
        case HI_UNF_DEMOD_DEV_TYPE_3130I:
        {
            qam_read_byte(u32TunerPort, MCTRL_1_ADDR, &u8DataTmp);

            if ((u8DataTmp >> 5) == 1 || (u8DataTmp >> 5) == 3 || (u8DataTmp >> 5) == 4 || (u8DataTmp >> 5)  == 6 || (u8DataTmp >> 5)  == 7)
            {
                if((u8DataTmp >> 5) == 1)
                {
                    HI_INFO_TUNER("tuner port %d's demod type is x5hdqammv200 inside\n", u32TunerPort);
                }
                else if((u8DataTmp >> 5) == 3)
                {
                    HI_INFO_TUNER("tuner port %d's demod type is x5hdqammv300 inside\n", u32TunerPort);
                }
                else if((u8DataTmp >> 5) == 4)
                {
                    HI_INFO_TUNER("tuner port %d's demod type is s40v100qam inside\n", u32TunerPort);
                }
                else if((u8DataTmp >> 5) == 6)
                {
                    HI_INFO_TUNER("tuner port %d's demod type is s40v200qam inside\n", u32TunerPort);
                }
                else if((u8DataTmp >> 5) == 7)
                {
                    HI_INFO_TUNER("tuner port %d's demod type is hi3716cv200qam inside\n", u32TunerPort);
                }

                /*config adc clk 28.8MHz*/
#if defined (CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)
                /*config qamadc_clk_sel 28.8MHz,  PERI_CRG58[9:8]:00*/
                unTmpPeriCrg58.bits.qamadc_clk_sel = 0;//PERI_CRG58[9:8]:00
                /*config qamctrl_clk_sel 25MHz , PERI_CRG58[11:10]:00; \
                            config qamctrl_clk_div for the same frequence, PERI_CRG58[12]:0*/
                unTmpPeriCrg58.bits.qamctrl_clk_sel = 0;//PERI_CRG58[11:10]:00
                unTmpPeriCrg58.bits.qamctrl_clk_div = 0;//PERI_CRG58[12]:0
                g_pstRegCrg->PERI_CRG58.u32 = unTmpPeriCrg58.u32;
#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)

                 /*config qamadc_clk_sel 28.8MHz,  PERI_CRG58[9:7]:00*/
                unTmpPeriCrg58.bits.qamadc_clk_sel = 0x00;

                 /*config qamctrl_clk_sel 28.8MHz , PERI_CRG58[12:10]:00; \
                            config qamctrl_clk_div for the same frequence, PERI_CRG58[13]:0*/
                unTmpPeriCrg58.bits.qamctrl_clk_sel = 0x00;
                unTmpPeriCrg58.bits.qamctrl_clk_div = 0;

                g_pstRegCrg->PERI_CRG58.u32 = unTmpPeriCrg58.u32;
#endif

#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400) || defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
                g_stTunerOps[u32TunerPort].tuner_connect                = hi3716cv200_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status             = hi3716cv200_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber                = hi3716cv200_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr                = hi3716cv200_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type            = hi3716cv200_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength    = hi3716cv200_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc        = hi3716cv200_test_single_agc;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset   = hi3716cv200_get_freq_symb_offset;
                g_stTunerOps[u32TunerPort].manage_after_chipreset       = hi3716cv200_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers          = hi3716cv200_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs                 = hi3716cv200_get_rs;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout        = hi3716cv200_connect_timeout;
#endif
            }
            else
            {
#if defined(DEMOD_DEV_TYPE_X5HDQAM)
                s_u32InsideQamPort = u32TunerPort;
                g_stTunerOps[u32TunerPort].tuner_connect = x5hdqam_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status = x5hdqam_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber = x5hdqam_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr = x5hdqam_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type = x5hdqam_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = x5hdqam_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc = x5hdqam_test_single_agc;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = x5hdqam_get_freq_symb_offset;
                g_stTunerOps[u32TunerPort].manage_after_chipreset = x5hdqam_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers = x5hdqam_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs = x5hdqam_get_rs;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout = x5hdqam_connect_timeout;
                HI_INFO_TUNER("tuner port %d's demod type is x5hdqam inside\n", u32TunerPort);
#endif
            }

            break;
        }
#endif
#if defined(DEMOD_DEV_TYPE_J83B)
        case HI_UNF_DEMOD_DEV_TYPE_J83B:
        {
            tuner_chip_reset(u32ResetGpioNo);
            qam_read_byte(u32TunerPort, MCTRL_1_ADDR, &u8DataTmp);

            if((u8DataTmp >> 5) == 1)
            {
                HI_INFO_TUNER("tuner port %d's demod type is mv200qam_J83B\n", u32TunerPort);
            }
            else if((u8DataTmp >> 5) == 3)
            {
                HI_INFO_TUNER("tuner port %d's demod type is mv300qam_J83B\n", u32TunerPort);
            }
            else if((u8DataTmp >> 5) == 4)
            {
                HI_INFO_TUNER("tuner port %d's demod type is s40v100qam_j83b\n", u32TunerPort);
            }
            else if((u8DataTmp >> 5) == 5)
            {
                HI_INFO_TUNER("tuner port %d's demod type is hi3130v200qam_j83b\n", u32TunerPort);
            }
            else if((u8DataTmp >> 5) == 6)
            {
                HI_INFO_TUNER("tuner port %d's demod type is s40v200qam_j83b\n", u32TunerPort);
            }
            else if((u8DataTmp >> 5) == 7)
            {
                HI_INFO_TUNER("tuner port %d's demod type is hi3716cv200qam_j83b\n", u32TunerPort);
            }

            if((u8DataTmp >> 5) == 5)
            {
#if defined(DEMOD_DEV_TYPE_HI3130)
                hi3130j83b_set_hard_reg_value(u32TunerPort);

                g_stTunerOps[u32TunerPort].tuner_connect = hi3130j83b_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status = hi3130j83b_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber = hi3130j83b_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr = hi3130j83b_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type = hi3130j83b_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = hi3130j83b_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc = hi3130j83b_test_single_agc;
                g_stTunerOps[u32TunerPort].manage_after_chipreset = hi3130j83b_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers = hi3130j83b_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs = hi3130j83b_get_rs;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = hi3130j83b_get_freq_symb_offset;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout = hi3130j83b_connect_timeout;
                g_stTunerOps[u32TunerPort].tuner_set_ts_out = hi3130j83b_set_ts_out;

                HI_INFO_TUNER("tuner port %d's demod type is hi3130v200_j83b outside\n", u32TunerPort);
#endif
            }
            else
            {
                /*config adc clk 25MHz*/
#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)
                /*config qamadc_clk_sel 25MHz,  PERI_CRG58[9:8]:01*/
                unTmpPeriCrg58.bits.qamadc_clk_sel = 0x01;
                /*config qamctrl_clk_sel 25MHz , PERI_CRG58[11:10]:01; \
                    config qamctrl_clk_div for the same frequence, PERI_CRG58[12]:0*/
                unTmpPeriCrg58.bits.qamctrl_clk_sel = 0x01;
                unTmpPeriCrg58.bits.qamctrl_clk_div = 0;
                g_pstRegCrg->PERI_CRG58.u32 = unTmpPeriCrg58.u32;
#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
                /*config qamadc_clk_sel 25MHz,  PERI_CRG58[9:7]:00*/
                unTmpPeriCrg58.bits.qamadc_clk_sel = 0x01;

                /*config qamctrl_clk_sel 25MHz , PERI_CRG58[12:10]:00; \
                        config qamctrl_clk_div for the same frequence, PERI_CRG58[13]:0*/
                unTmpPeriCrg58.bits.qamctrl_clk_sel = 0x01;
                unTmpPeriCrg58.bits.qamctrl_clk_div = 0;

                g_pstRegCrg->PERI_CRG58.u32 = unTmpPeriCrg58.u32;
#endif
#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400) || defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
                g_stTunerOps[u32TunerPort].tuner_connect = hi3716cv200_j83b_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status = hi3716cv200_j83b_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber = hi3716cv200_j83b_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr = hi3716cv200_j83b_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type = hi3716cv200_j83b_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = hi3716cv200_j83b_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc = hi3716cv200_j83b_test_single_agc;
                g_stTunerOps[u32TunerPort].manage_after_chipreset = hi3716cv200_j83b_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers = hi3716cv200_j83b_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs = hi3716cv200_j83b_get_rs;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = hi3716cv200_j83b_get_freq_symb_offset;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout = hi3716cv200_j83b_connect_timeout;
                HI_INFO_TUNER("tuner port %d's demod type is j83b inside,demod Version:%d\n", u32TunerPort,(u8DataTmp >> 5));
#else
                g_stTunerOps[u32TunerPort].tuner_connect = j83b_connect;
                g_stTunerOps[u32TunerPort].tuner_get_status = j83b_get_status;
                g_stTunerOps[u32TunerPort].tuner_get_ber = j83b_get_ber;
                g_stTunerOps[u32TunerPort].tuner_get_snr = j83b_get_snr;
                g_stTunerOps[u32TunerPort].tuner_set_ts_type = j83b_set_ts_type;
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = j83b_get_signal_strength;
                g_stTunerOps[u32TunerPort].tuner_test_single_agc = j83b_test_single_agc;
                g_stTunerOps[u32TunerPort].manage_after_chipreset = j83b_manage_after_chipreset;
                g_stTunerOps[u32TunerPort].tuner_get_registers = j83b_get_registers;
                g_stTunerOps[u32TunerPort].tuner_get_rs = j83b_get_rs;
                g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = j83b_get_freq_symb_offset;
                g_stTunerOps[u32TunerPort].tuner_connect_timeout = j83b_connect_timeout;
                HI_INFO_TUNER("tuner port %d's demod type is j83b inside,demod Version:%d\n", u32TunerPort,(u8DataTmp >> 5));
#endif
            }
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_AVL6211)
        case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
        {
            u8ChipReset = 1;
            g_stTunerOps[u32TunerPort].tuner_init = avl6211_init;
            g_stTunerOps[u32TunerPort].tuner_set_sat_attr = avl6211_set_sat_attr;
            g_stTunerOps[u32TunerPort].tuner_connect = avl6211_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = avl6211_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = avl6211_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = avl6211_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = avl6211_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = avl6211_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = avl6211_get_signal_info;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = avl6211_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_blindscan_init   = avl6211_blindscan_init;
            g_stTunerOps[u32TunerPort].tuner_blindscan_action = avl6211_blindscan_action;
            g_stTunerOps[u32TunerPort].tuner_standby = avl6211_standby;
            g_stTunerOps[u32TunerPort].tuner_setfuncmode = avl6211_set_funcmode;
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_HI3136)
        case HI_UNF_DEMOD_DEV_TYPE_3136:
            u8ChipReset = 1;/*externel demod need chip reset, internel do not need.*/

        case HI_UNF_DEMOD_DEV_TYPE_3136I:
        {
            g_stTunerOps[u32TunerPort].tuner_init = hi3136_init;
            g_stTunerOps[u32TunerPort].tuner_set_sat_attr = hi3136_set_sat_attr;
            g_stTunerOps[u32TunerPort].tuner_connect = hi3136_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = hi3136_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = hi3136_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = hi3136_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = hi3136_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = hi3136_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = hi3136_get_signal_info;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = hi3136_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_blindscan_init   = hi3136_blindscan_init;
            g_stTunerOps[u32TunerPort].tuner_blindscan_action = hi3136_blindscan_action;
            /*g_stTunerOps[u32TunerPort].tuner_standby = hi3136_standby;
            g_stTunerOps[u32TunerPort].tuner_disable = hi3136_disable;*/
            g_stTunerOps[u32TunerPort].tuner_setfuncmode = hi3136_set_funcmode;
            g_stTunerOps[u32TunerPort].tuner_tp_verify = hi3136_tp_verify;
            g_stTunerOps[u32TunerPort].tuner_set_ts_out = hi3136_set_ts_out;
            g_stTunerOps[u32TunerPort].tuner_data_sample = hi3136_data_sample;
            g_stTunerOps[u32TunerPort].tuner_set_vcm_acm_stream = hi3136_set_isi_id;
            g_stTunerOps[u32TunerPort].tuner_get_vcm_acm_stream = hi3136_get_total_isi_number;
            g_stTunerOps[u32TunerPort].tuner_get_isi_id = hi3136_get_isi_id;
            g_stTunerOps[u32TunerPort].tuner_get_agc = hi3136_get_agc;
            g_stTunerOps[u32TunerPort].tuner_set_scramble = hi3136_set_scramble;
            g_stTunerOps[u32TunerPort].tuner_get_registers = hi3136_read_tuner_registers;
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_HI3137)
        case HI_UNF_DEMOD_DEV_TYPE_3137:
        {
            u8ChipReset = 1;/*externel demod need chip reset, internel do not need.*/
            g_stTunerOps[u32TunerPort].tuner_init = hi3137_init;
            g_stTunerOps[u32TunerPort].tuner_connect = hi3137_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = hi3137_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = hi3137_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = hi3137_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = hi3137_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = hi3137_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = hi3137_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = hi3137_get_signal_info;
            g_stTunerOps[u32TunerPort].tuner_setplpid = hi3137_setplpid;
            g_stTunerOps[u32TunerPort].tuner_terscan_action = hi3137_tp_scan;
            g_stTunerOps[u32TunerPort].tuner_set_common_plp_id = hi3137_set_common_plp_id;
            g_stTunerOps[u32TunerPort].tuner_set_common_plp_combination = hi3137_set_common_plp_combination;
            g_stTunerOps[u32TunerPort].tuner_get_plp_num = hi3137_get_plp_num;
            g_stTunerOps[u32TunerPort].tuner_get_current_plp_type = hi3137_get_current_plp_type;
            g_stTunerOps[u32TunerPort].tuner_get_plp_id = hi3137_get_plp_id;
            g_stTunerOps[u32TunerPort].tuner_get_group_plp_id = hi3137_get_plp_group_id;
            g_stTunerOps[u32TunerPort].tuner_connect_timeout = hi3137_connect_timeout;
            g_stTunerOps[u32TunerPort].tuner_set_ts_out = hi3137_set_ts_out;
            g_stTunerOps[u32TunerPort].tuner_set_ter_attr = hi3137_set_ter_attr;
            g_stTunerOps[u32TunerPort].tuner_set_antena_power =  hi3137_set_antena_power;
            g_stTunerOps[u32TunerPort].tuner_standby = hi3137_standby;
            g_stTunerOps[u32TunerPort].tuner_get_registers = hi3137_read_tuner_registers;
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_MXL101)
        case HI_UNF_DEMOD_DEV_TYPE_MXL101:
        {
            u8ChipReset = 1;
            g_stTunerOps[u32TunerPort].tuner_init = mxl101_init;
            g_stTunerOps[u32TunerPort].tuner_connect = mxl101_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = mxl101_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = mxl101_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = mxl101_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = mxl101_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = mxl101_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = mxl101_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = mxl101_get_signal_info;
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_MN88472)
        case HI_UNF_DEMOD_DEV_TYPE_MN88472:
        {
            u8ChipReset = 1;
            g_stTunerOps[u32TunerPort].tuner_init = MN88472_Init;
            g_stTunerOps[u32TunerPort].tuner_connect = MN88472_Connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = MN88472_GetStatus;
            g_stTunerOps[u32TunerPort].tuner_get_ber = MN88472_GetBer;
            g_stTunerOps[u32TunerPort].tuner_get_snr = MN88472_GetSnr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = MN88472_GetSignalStrength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = MN88472_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = MN88472_SetTsType;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = MN88472_get_signal_info;
            g_stTunerOps[u32TunerPort].tuner_setplpid = MN88472_setplpid;
            g_stTunerOps[u32TunerPort].tuner_get_plp_num = MN88472_get_plp_num;
            g_stTunerOps[u32TunerPort].tuner_get_current_plp_type = MN88472_get_current_plp_type;
            g_stTunerOps[u32TunerPort].tuner_connect_timeout = MN88472_connect_timeout;
            g_stTunerOps[u32TunerPort].tuner_get_group_plp_id = MN88472_get_plp_group_id;
            g_stTunerOps[u32TunerPort].tuner_get_plp_id = MN88472_get_plp_id;
            g_stTunerOps[u32TunerPort].tuner_set_common_plp_id = MN88472_set_common_plp_id;
            g_stTunerOps[u32TunerPort].tuner_set_common_plp_combination = MN88472_set_common_plp_combination;
			g_stTunerOps[u32TunerPort].tuner_set_ts_out =  MN88472_set_ts_out;
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_CXD2837)
        case HI_UNF_DEMOD_DEV_TYPE_CXD2837:
        {
            u8ChipReset = 1;
            g_stTunerOps[u32TunerPort].tuner_init = cxd2837_init;
            g_stTunerOps[u32TunerPort].tuner_connect = cxd2837_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = cxd2837_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = cxd2837_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = cxd2837_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = cxd2837_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = cxd2837_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = cxd2837_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = cxd2837_get_signal_info;
            g_stTunerOps[u32TunerPort].tuner_setplpid = cxd2837_setplpid;
            g_stTunerOps[u32TunerPort].tuner_get_plp_num = cxd2837_get_plp_num;
            g_stTunerOps[u32TunerPort].tuner_get_current_plp_type = cxd2837_get_current_plp_type;
            g_stTunerOps[u32TunerPort].tuner_connect_timeout = cxd2837_connect_timeout;
            break;
        }
#endif

#if defined(DEMOD_DEV_TYPE_IT9133)
        case HI_UNF_DEMOD_DEV_TYPE_IT9133:
        {
            u8ChipReset = 1;
            g_stTunerOps[u32TunerPort].tuner_init = it9133_init;
            g_stTunerOps[u32TunerPort].tuner_connect = it9133_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = it9133_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = it9133_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = it9133_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = it9133_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = it9133_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = it9133_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = it9133_get_signal_info;
            break;
        }
#endif
#if defined(DEMOD_DEV_TYPE_IT9170)
        case HI_UNF_DEMOD_DEV_TYPE_IT9170:
        {
            u8ChipReset = 1;
            //ptrTunerAttr = &stTerTunerAttr;
            //unEXTTunerAttr.stTerAttr = stTerTunerAttr;
            g_stTunerOps[u32TunerPort].tuner_init = it9170_init;
            g_stTunerOps[u32TunerPort].tuner_connect = it9170_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = it9170_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = it9170_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = it9170_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = it9170_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = it9170_get_freq_symb_offset;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = it9170_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_get_signal_info = it9170_get_signal_info;
            break;
        }
#endif
#if defined(DEMOD_DEV_TYPE_MXL254) || defined(DEMOD_DEV_TYPE_MXL214)
        case HI_UNF_DEMOD_DEV_TYPE_MXL254:
        case HI_UNF_DEMOD_DEV_TYPE_MXL214:
        {
			tuner_chip_reset(u32ResetGpioNo);
            g_stTunerOps[u32TunerPort].tuner_init = mxl254_init;
            g_stTunerOps[u32TunerPort].tuner_connect = mxl254_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = mxl254_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = mxl254_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = mxl254_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = mxl254_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = mxl254_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_connect_timeout =mxl254_connect_timeout;
            break;
        }
#endif
#if defined(DEMOD_DEV_TYPE_TDA18280)
        case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
        {
            g_stTunerOps[u32TunerPort].tuner_init = tda18280_init;
            g_stTunerOps[u32TunerPort].tuner_connect = tda18280_connect;
            g_stTunerOps[u32TunerPort].tuner_get_status = tda18280_get_status;
            g_stTunerOps[u32TunerPort].tuner_get_ber = tda18280_get_ber;
            g_stTunerOps[u32TunerPort].tuner_get_snr = tda18280_get_snr;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength  = tda18280_get_signal_strength;
            g_stTunerOps[u32TunerPort].tuner_set_ts_type = tda18280_set_ts_type;
            g_stTunerOps[u32TunerPort].tuner_connect_timeout = tda18280_connect_timeout;
            g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset = tda18280_get_freq_symb_offset;
            break;
        }
#endif
        default:
        {
            HI_ERR_TUNER("demod type error:%d",g_stTunerOps[u32TunerPort].enDemodDevType);
            return HI_FAILURE;
        }
    }

#if    defined(DEMOD_DEV_TYPE_IT9170)   \
    || defined(DEMOD_DEV_TYPE_IT9133)   \
    || defined(DEMOD_DEV_TYPE_MN88472)  \
    || defined(DEMOD_DEV_TYPE_MXL101)   \
    || defined(DEMOD_DEV_TYPE_HI3136)   \
    || defined(DEMOD_DEV_TYPE_HI3137)   \
    || defined(DEMOD_DEV_TYPE_AVL6211)  \
    || defined(DEMOD_DEV_TYPE_CXD2837)
    if (u8ChipReset)
    {
        tuner_chip_reset(u32ResetGpioNo);
    }
#endif

    /* Added begin:l00185424 2011-12-20 For AVL6211 */
    if (g_stTunerOps[u32TunerPort].tuner_init)
    {
        g_stTunerOps[u32TunerPort].tuner_init(u32TunerPort, g_stTunerOps[u32TunerPort].enI2cChannel, g_stTunerOps[u32TunerPort].enTunerDevType);
        //s_stTunerResumeInfo[u32TunerPort].unResumeData = unEXTTunerAttr;
    }
    /* Added begin:l00185424 2011-11-28 For AVL6211 */

    switch (g_stTunerOps[u32TunerPort].enTunerDevType)
    {
#if defined(TUNER_DEV_TYPE_CD1616)
        case HI_UNF_TUNER_DEV_TYPE_CD1616:
        {
            g_stTunerOps[u32TunerPort].set_tuner = cd1616_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is cd1616\n", u32TunerPort);
            break;
        }
#endif
#if defined(TUNER_DEV_TYPE_CD1616_LF_GIH_4)
        case HI_UNF_TUNER_DEV_TYPE_CD1616_DOUBLE:
        {
            g_stTunerOps[u32TunerPort].set_tuner = cd1616_double_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is cd1616_double\n", u32TunerPort);
            break;
        }
#endif
#if defined(TUNER_DEV_TYPE_ALPS_TDAE)
        case HI_UNF_TUNER_DEV_TYPE_ALPS_TDAE:
        {
            g_stTunerOps[u32TunerPort].set_tuner = alps_tdae_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is alps_tdae\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_TDA18250)
        case HI_UNF_TUNER_DEV_TYPE_TDA18250:
        {
            s32Ret = tda18250_init_tuner(u32TunerPort);
            if(HI_FAILURE == s32Ret)
            {
                HI_INFO_TUNER("tda18250 init error\n");
                return HI_FAILURE;
            }
            g_stTunerOps[u32TunerPort].set_tuner = tda18250_set_tuner;
            g_stTunerOps[u32TunerPort].tuner_resume = tda18250_tuner_resume;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength = tda18250_get_signal_strength;
            HI_INFO_TUNER("tuner port %d's halftuner type is tda18250\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_TMX7070X)
        case HI_UNF_TUNER_DEV_TYPE_TMX7070X:
        {
            g_stTunerOps[u32TunerPort].set_tuner = tmx7070x_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is tmx7070x\n", u32TunerPort);
            break;
        }
#endif
#if defined(TUNER_DEV_TYPE_TDCC)
        case HI_UNF_TUNER_DEV_TYPE_TDCC:
        {
            g_stTunerOps[u32TunerPort].set_tuner = tdcc_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is tdcc\n", u32TunerPort);
            break;
        }
#endif
#if defined(TUNER_DEV_TYPE_XG_3BL)
        case HI_UNF_TUNER_DEV_TYPE_XG_3BL:
        {
            g_stTunerOps[u32TunerPort].set_tuner = xg_3bl_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is xg3bl\n", u32TunerPort);
            break;
        }
#endif
#if defined(TUNER_DEV_TYPE_MT2081)
        case HI_UNF_TUNER_DEV_TYPE_MT2081:
        {
            g_stTunerOps[u32TunerPort].set_tuner = mt2081_set_tuner;
            g_stTunerOps[u32TunerPort].tuner_resume = mt2081_tuner_resume;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength = mt2081_get_signal_strength;
            HI_INFO_TUNER("tuner port %d's halftuner type is mt2081\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_R820C)
        case HI_UNF_TUNER_DEV_TYPE_R820C:
        {
            s32Ret = r820c_init_tuner(u32TunerPort);
            if(HI_FAILURE == s32Ret)
            {
                HI_INFO_TUNER("r820c_init_tuner error\n");
                return HI_FAILURE;
            }
            g_stTunerOps[u32TunerPort].set_tuner = r820c_set_tuner;
            g_stTunerOps[u32TunerPort].tuner_resume = r820c_tuner_resume;
            g_stTunerOps[u32TunerPort].recalculate_signal_strength = r820c_get_signal_strength;
            HI_INFO_TUNER("tuner port %d's halftuner type is r820c\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_MXL203)
        case HI_UNF_TUNER_DEV_TYPE_MXL203:
        {
            g_stTunerOps[u32TunerPort].set_tuner = mxl203_set_tuner;
            HI_INFO_TUNER("tuner port %d's halftuner type is mxl203\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_TDA18250B)
        case HI_UNF_TUNER_DEV_TYPE_TDA18250B:
        {
            s32Ret = tda18250b_init_tuner(u32TunerPort);
            if(HI_FAILURE == s32Ret)
            {
                HI_ERR_TUNER("tda18250B init error\n");
                return HI_FAILURE;
            }
            g_stTunerOps[u32TunerPort].set_tuner = tda18250b_set_tuner;
            g_stTunerOps[u32TunerPort].tuner_resume = tda18250b_tuner_resume;
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength = tda18250b_get_signal_strength;
            HI_INFO_TUNER("tuner port %d's halftuner type is tda18250B\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_si2147)
        case HI_UNF_TUNER_DEV_TYPE_SI2147:
            {
				s32Ret = si2147_init_tuner(u32TunerPort);
                if(HI_FAILURE == s32Ret)
                {
                    HI_ERR_TUNER("si2147 init error\n");
                    return HI_FAILURE;
                }
                g_stTunerOps[u32TunerPort].set_tuner = si2147_set_tuner;
                g_stTunerOps[u32TunerPort].tuner_resume = si2147_tuner_resume;
				g_stTunerOps[u32TunerPort].tuner_get_signal_strength = si2147_get_signal_strength;
                HI_INFO_TUNER("tuner port %d's halftuner type is si2147\n", u32TunerPort);
                break;
            }
#endif

#if defined(TUNER_DEV_TYPE_MXL608)
        case HI_UNF_TUNER_DEV_TYPE_MXL608:	
				s32Ret = mxl608_init_tuner(u32TunerPort);
	            if(HI_FAILURE == s32Ret)
	            {
	                HI_ERR_TUNER("mxl608 init error\n");
	                return HI_FAILURE;
	            }
                g_stTunerOps[u32TunerPort].set_tuner = mxl608_set_tuner;
                g_stTunerOps[u32TunerPort].tuner_resume = mxl608_tuner_resume;
				if(g_stTunerOps[u32TunerPort].enDemodDevType != HI_UNF_DEMOD_DEV_TYPE_3137) 
            	{
                	g_stTunerOps[u32TunerPort].tuner_get_signal_strength = mxl608_get_signal_strength;
				}
                HI_INFO_TUNER("tuner port %d's halftuner type is mxl608\n", u32TunerPort);
                break;
#endif


#if defined(TUNER_DEV_TYPE_AV2011)
        case HI_UNF_TUNER_DEV_TYPE_AV2011:
        {
#if defined(DEMOD_DEV_TYPE_HI3136)
            g_stTunerOps[u32TunerPort].set_tuner = av2011_set_tuner;
#endif
            HI_INFO_TUNER("tuner port %d's halftuner type is AV2011\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_AV2018)
        case HI_UNF_TUNER_DEV_TYPE_AV2018:
        {
#if defined(DEMOD_DEV_TYPE_HI3136)
            g_stTunerOps[u32TunerPort].set_tuner = av2018_set_tuner;
#endif
            HI_INFO_TUNER("tuner port %d's halftuner type is AV2018\n", u32TunerPort);
            break;
        }
#endif


#if defined(TUNER_DEV_TYPE_SHARP7903)
        case HI_UNF_TUNER_DEV_TYPE_SHARP7903:
        {
#if defined(DEMOD_DEV_TYPE_HI3136)
            g_stTunerOps[u32TunerPort].set_tuner = sharp7903_set_tuner;
#endif
            HI_INFO_TUNER("tuner port %d's halftuner type is SHARP7903\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_RDA5815)
        case HI_UNF_TUNER_DEV_TYPE_RDA5815:
        {
#if defined(DEMOD_DEV_TYPE_HI3136)
            g_stTunerOps[u32TunerPort].set_tuner = RDA5815_set_tuner;
#endif
            HI_INFO_TUNER("tuner port %d's halftuner type is RDA5815\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_M88TS2022)
        case HI_UNF_TUNER_DEV_TYPE_M88TS2022:
        {
#if defined(DEMOD_DEV_TYPE_HI3136)
            g_stTunerOps[u32TunerPort].set_tuner = M88TS2022_set_tuner;
#endif
            HI_INFO_TUNER("tuner port %d's halftuner type is M88TS2022\n", u32TunerPort);
            break;
        }
#endif

        case HI_UNF_TUNER_DEV_TYPE_MXL101:
        {
            HI_INFO_TUNER("tuner port %d's halftuner type is MXL101\n", u32TunerPort);
            break;
        }

#if defined(TUNER_DEV_TYPE_MXL603)
        case HI_UNF_TUNER_DEV_TYPE_MXL603:
        {
            g_stTunerOps[u32TunerPort].set_tuner = mxl603_set_tuner;
            g_stTunerOps[u32TunerPort].tuner_resume = mxl603_tuner_resume;
            if((g_stTunerOps[u32TunerPort].enDemodDevType != HI_UNF_DEMOD_DEV_TYPE_3137) && (g_stTunerOps[u32TunerPort].enDemodDevType != HI_UNF_DEMOD_DEV_TYPE_MN88472))
            {
                g_stTunerOps[u32TunerPort].tuner_get_signal_strength = mxl603_get_signal_strength;
            }

            HI_INFO_TUNER("tuner port %d's halftuner type is mxl603\n", u32TunerPort);
            break;
        }
#endif

#if defined(TUNER_DEV_TYPE_RAFAEL836)
        case HI_UNF_TUNER_DEV_TYPE_RAFAEL836:
        {
            break;
        }
#endif
#if defined(TUNER_DEV_TYPE_CXD2861)
        case HI_UNF_TUNER_DEV_TYPE_CXD2861:
        {
            HI_INFO_TUNER("DVB-T/T2 tuner CXD2861.\n");
            break;
        }
#endif
        case HI_UNF_TUNER_DEV_TYPE_IT9170:
        {
            HI_INFO_TUNER("tuner port %d's halftuner type is IT9170\n", u32TunerPort);
            break;
        }
        case HI_UNF_TUNER_DEV_TYPE_IT9133:
        {
            HI_INFO_TUNER("tuner port %d's halftuner type is IT9133\n", u32TunerPort);
            break;
        }
#if defined(TUNER_DEV_TYPE_TDA6651)
        case HI_UNF_TUNER_DEV_TYPE_TDA6651:
        {
            g_stTunerOps[u32TunerPort].set_tuner = tda6651_set_tuner;

            HI_INFO_TUNER("tuner port %d's halftuner type is tda6651\n", u32TunerPort);
            break;
        }
#endif
        case HI_UNF_TUNER_DEV_TYPE_MXL254:
        case HI_UNF_TUNER_DEV_TYPE_MXL214:
        {
            HI_INFO_TUNER("tuner port %d's halftuner type is MXL254\n", u32TunerPort);
            break;
        }
        case HI_UNF_TUNER_DEV_TYPE_TDA18280:
        {
            HI_INFO_TUNER("tuner port %d's halftuner type is TDA18280\n", u32TunerPort);
            break;
        }
#if defined(TUNER_DEV_TYPE_TDA182I5A)
		case HI_UNF_TUNER_DEV_TYPE_TDA182I5A:
			//g_stTunerOps[u32TunerPort].set_tuner = tda182i5a_set_tuner;
			HI_INFO_TUNER("tuner port %d's tuner type is tda182i5a\n", u32TunerPort);
			break;
#endif
#if defined(TUNER_DEV_TYPE_SI2144)
		case HI_UNF_TUNER_DEV_TYPE_SI2144:
			HI_INFO_TUNER("tuner port %d's tuner type is si2144\n", u32TunerPort);
			break;
#endif
        default:
        {
            //g_stTunerOps[u32TunerPort].set_tuner = cd1616_set_tuner;
            //HI_INFO_TUNER("tuner port %d's halftuner type(default) is cd1616\n", u32TunerPort);
            //break;
        }
    }

    return HI_SUCCESS;
}

HI_S32 tuner_set_sat_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr)
{
    s_stSatTunerResumeInfo[u32TunerPort].stSatTunerAttr = *pstSatTunerAttr;

    if (g_stTunerOps[u32TunerPort].tuner_set_sat_attr)
    {
        g_stTunerOps[u32TunerPort].tuner_set_sat_attr(u32TunerPort, pstSatTunerAttr);
    }

    /* For DVB-S/S2 demod, need configurate LNB control device */
    switch (g_stTunerOps[u32TunerPort].enDemodDevType)
    {
#if defined(DEMOD_DEV_TYPE_AVL6211)
        case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
            {
                g_stTunerOps[u32TunerPort].tuner_set_lnb_out = HI_NULL;
                g_stTunerOps[u32TunerPort].tuner_send_continuous_22K = avl6211_send_continuous_22K;
                g_stTunerOps[u32TunerPort].tuner_send_tone = avl6211_send_tone;
                g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg = avl6211_DiSEqC_send_msg;
                g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg = avl6211_DiSEqC_recv_msg;

                /* Which device send wave */
                switch (pstSatTunerAttr->enDiSEqCWave)
                {
                        /* Demod send wave, LNB control only supply power */
                    case HI_UNF_TUNER_DISEQCWAVE_NORMAL:
                    default:
                        {
                            switch (pstSatTunerAttr->enLNBCtrlDev)
                            {
#if defined(LNB_CTRL_MPS8125)
                                case HI_UNF_LNBCTRL_DEV_TYPE_MPS8125:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = mps8125_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = mps8125_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = mps8125_set_lnb_out;
                                    break;
#endif

#if defined(LNB_CTRL_ISL9492)
                                case HI_UNF_LNBCTRL_DEV_TYPE_ISL9492:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = isl9492_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = isl9492_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = isl9492_set_lnb_out;
                                    break;
#endif

                                case HI_UNF_LNBCTRL_DEV_TYPE_NONE:
                                default:
                                    HI_INFO_TUNER("LNB ctrl chiptype error!\n");
                                    return HI_FAILURE;
                            }

                            break;
                        }

                        /* LNB control device send wave */
                    case HI_UNF_TUNER_DISEQCWAVE_ENVELOPE:
                        {
                            switch (pstSatTunerAttr->enLNBCtrlDev)
                            {
#if defined(LNB_CTRL_MPS8125)
                                case HI_UNF_LNBCTRL_DEV_TYPE_MPS8125:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = mps8125_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = mps8125_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = mps8125_set_lnb_out;
                                    g_stTunerOps[u32TunerPort].tuner_send_continuous_22K = mps8125_send_continuous_22K;
                                    g_stTunerOps[u32TunerPort].tuner_send_tone = mps8125_send_tone;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg = mps8125_DiSEqC_send_msg;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg = mps8125_DiSEqC_recv_msg;
                                    break;
#endif

#if defined(LNB_CTRL_ISL9492)
                                case HI_UNF_LNBCTRL_DEV_TYPE_ISL9492:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = isl9492_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = isl9492_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = isl9492_set_lnb_out;
                                    g_stTunerOps[u32TunerPort].tuner_send_continuous_22K = isl9492_send_continuous_22K;
                                    g_stTunerOps[u32TunerPort].tuner_send_tone = isl9492_send_tone;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg = isl9492_DiSEqC_send_msg;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg = isl9492_DiSEqC_recv_msg;
                                    break;
#endif

                                case HI_UNF_LNBCTRL_DEV_TYPE_NONE:
                                default:
                                    HI_INFO_TUNER("LNB ctrl chiptype error!\n");
                                    return HI_FAILURE;
                            }

                            break;
                        }
                }

                break;
            }
#endif

#if defined(DEMOD_DEV_TYPE_HI3136)
        case HI_UNF_DEMOD_DEV_TYPE_3136:
        case HI_UNF_DEMOD_DEV_TYPE_3136I:
            {
                g_stTunerOps[u32TunerPort].tuner_set_lnb_out = HI_NULL;
                g_stTunerOps[u32TunerPort].tuner_send_continuous_22K = hi3136_send_continuous_22K;
                g_stTunerOps[u32TunerPort].tuner_send_tone = hi3136_send_tone;
                g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg = hi3136_DiSEqC_send_msg;
                /*g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg = hi3136_DiSEqC_recv_msg;*/

                /* Which device send wave */
                switch (pstSatTunerAttr->enDiSEqCWave)
                {
                        /* Demod send wave, LNB control only supply power */
                    case HI_UNF_TUNER_DISEQCWAVE_NORMAL:
                    default:
                        {
                            switch (pstSatTunerAttr->enLNBCtrlDev)
                            {
#if defined(LNB_CTRL_MPS8125)
                                case HI_UNF_LNBCTRL_DEV_TYPE_MPS8125:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = mps8125_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = mps8125_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = mps8125_set_lnb_out;
                                    break;
#endif

#if defined(LNB_CTRL_ISL9492)
                                case HI_UNF_LNBCTRL_DEV_TYPE_ISL9492:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = isl9492_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = isl9492_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = isl9492_set_lnb_out;
                                    break;
#endif

                                case HI_UNF_LNBCTRL_DEV_TYPE_NONE:
                                default:
                                    HI_INFO_TUNER("LNB ctrl chiptype error!\n");
                                    return HI_FAILURE;
                            }

                            break;
                        }

                        /* LNB control device send wave */
                    case HI_UNF_TUNER_DISEQCWAVE_ENVELOPE:
                        {
                            switch (pstSatTunerAttr->enLNBCtrlDev)
                            {
#if defined(LNB_CTRL_MPS8125)
                                case HI_UNF_LNBCTRL_DEV_TYPE_MPS8125:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = mps8125_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = mps8125_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = mps8125_set_lnb_out;
                                    g_stTunerOps[u32TunerPort].tuner_send_continuous_22K = mps8125_send_continuous_22K;
                                    g_stTunerOps[u32TunerPort].tuner_send_tone = mps8125_send_tone;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg = mps8125_DiSEqC_send_msg;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg = mps8125_DiSEqC_recv_msg;
                                    break;
#endif

#if defined(LNB_CTRL_ISL9492)
                                case HI_UNF_LNBCTRL_DEV_TYPE_ISL9492:
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init = isl9492_init;
                                    g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby = isl9492_standby;
                                    g_stTunerOps[u32TunerPort].tuner_set_lnb_out = isl9492_set_lnb_out;
                                    g_stTunerOps[u32TunerPort].tuner_send_continuous_22K = isl9492_send_continuous_22K;
                                    g_stTunerOps[u32TunerPort].tuner_send_tone = isl9492_send_tone;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg = isl9492_DiSEqC_send_msg;
                                    g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg = isl9492_DiSEqC_recv_msg;
                                    break;
#endif

                                case HI_UNF_LNBCTRL_DEV_TYPE_NONE:
                                default:
                                    HI_INFO_TUNER("LNB ctrl chiptype error!\n");
                                    return HI_FAILURE;
                            }

                            break;
                        }
                }

                break;
            }
#endif
        default:
            {
                HI_INFO_TUNER("Demod type error! Not sat demod!\n");
                return HI_FAILURE;
            }
    }
#if defined(DEMOD_DEV_TYPE_AVL6211) || defined(DEMOD_DEV_TYPE_HI3136)
    if (g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init)
    {
        g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_init(u32TunerPort,
                                                          g_stTunerOps[u32TunerPort].enI2cChannel,
                                                          pstSatTunerAttr->u16LNBDevAddress, g_stTunerOps[u32TunerPort].enDemodDevType);
    }
#endif
    return HI_SUCCESS;
}

HI_S32 tuner_set_ter_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_TER_ATTR_S *pstTerTunerAttr)
{
    HI_S32 s32Ret = 0;

    if (!g_stTunerOps[u32TunerPort].tuner_set_ter_attr) /* check if tuner set attr is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_ter_attr(u32TunerPort, pstTerTunerAttr);
    if (HI_SUCCESS == s32Ret)
    {
        memcpy(&s_stSatTunerResumeInfo[u32TunerPort].stTerTunerAttr, pstTerTunerAttr, sizeof(HI_UNF_TUNER_TER_ATTR_S));
    }

    return s32Ret;
}

HI_S32 tuner_select_i2c(HI_U32 u32TunerPort, HI_U8 enI2cChannel)
{
    if (enI2cChannel >= /*HI_UNF_I2C_CHANNEL_MAX*/16)
    {
        HI_INFO_TUNER( "invalid i2c channel: %d\n", enI2cChannel);
        return -EINVAL;
    }
    HI_INFO_TUNER("tuner port %d's i2c channel is %d\n", u32TunerPort, enI2cChannel);

    g_stTunerOps[u32TunerPort].enI2cChannel = enI2cChannel;

    return HI_SUCCESS;
}


HI_S32 tuner_osr_connect(PTR_TUNER_SIGNAL_S pstTunerSignal)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    HI_DRV_STAT_Event(STAT_EVENT_CONNECT, 0);

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerSignal->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "invalid tuner port: %d\n", u32TunerPort);
        return HI_FAILURE;
    }

	if (HI_UNF_DEMOD_DEV_TYPE_MXL254 != g_stTunerOps[u32TunerPort].enDemodDevType
		 && HI_UNF_DEMOD_DEV_TYPE_MXL214 != g_stTunerOps[u32TunerPort].enDemodDevType
		 && HI_UNF_DEMOD_DEV_TYPE_TDA18280 != g_stTunerOps[u32TunerPort].enDemodDevType)
	{
    	g_stTunerOps[u32TunerPort].enSigType = pstTunerSignal->enSigType;
	}
	
	g_stTunerOps[u32TunerPort].stCurrPara.u32Frequency = pstTunerSignal->stSignal.u32Frequency;
    g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32SymbolRate = pstTunerSignal->stSignal.unSRBW.u32SymbolRate;
    g_stTunerOps[u32TunerPort].stCurrPara.enQamType = pstTunerSignal->stSignal.enQamType;
    g_stTunerOps[u32TunerPort].stCurrPara.bSI = pstTunerSignal->stSignal.bSI;

    /* if tuner connect operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_connect) /* check if tuner conect is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return HI_FAILURE;
    }

    /* call tuner connect operation */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_connect(u32TunerPort, &(pstTunerSignal->stSignal));
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "\n tuner_connect failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}


HI_S32 tuner_osr_getstatus(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_status) /* check if tuner get status is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* get tuner lock status */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_status(u32TunerPort,
                                    (HI_UNF_TUNER_LOCK_STATUS_E *)&pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "\n tuner_get_status failed \n");
        return s32Ret;
    }

    s_enTunerStat[u32TunerPort] = pstTunerDataStr->u32Data;

    if (HI_UNF_TUNER_SIGNAL_LOCKED == pstTunerDataStr->u32Data)
    {
        HI_DRV_STAT_Event(STAT_EVENT_LOCKED, 0);
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_getsignalstrength(PTR_TUNER_DATABUF_S pstTunerDataBuf)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataBuf->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get singal strength operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_signal_strength) /* check if tuner get strength is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* call signal strength */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_signal_strength(u32TunerPort, pstTunerDataBuf->u32DataBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_get_signal_strength failed!\n");
    }

    return s32Ret;
}


HI_S32 tuner_osr_getber(PTR_TUNER_DATABUF_S pstTunerDataBuf)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataBuf->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get ber operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_ber) /* check if tuner get ber is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner get ber */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_ber(u32TunerPort, pstTunerDataBuf->u32DataBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_get_ber failed!\n");
    }

    return s32Ret;
}

HI_S32 tuner_osr_getsnr(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get snr operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_snr) /* check if tuner snr ber is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* get snr */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_snr(u32TunerPort, &pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_get_snr failed!\n");
    }

    return s32Ret;
}


HI_S32 tuner_osr_settstype(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_UNF_TUNER_OUPUT_MODE_E enTsType;
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "invalid tuner port: %d\n", u32TunerPort);
        return HI_FAILURE;
    }

    /* if tuner get snr operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_ts_type) /* check if tuner set ts type is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    enTsType = (HI_UNF_TUNER_OUPUT_MODE_E)pstTunerDataStr->u32Data;

    /* set ts type */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_ts_type(u32TunerPort, enTsType);
    if (HI_SUCCESS == s32Ret)
    {
        s_stSatTunerResumeInfo[u32TunerPort].enOutMode = enTsType;
    }

    return s32Ret;
}

HI_S32 tuner_osr_selecttype(PTR_TUNER_DATABUF_S pstTunerDataBuf)
{
    HI_TunerAttr_S *pstTuner_Attr = HI_NULL;
    HI_DemodAttr_S *pstDemod_Attr = HI_NULL;
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U32 u32ResetGpioNo = 0xFF;

    u32TunerPort = pstTunerDataBuf->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "invalid tuner port: %d\n", u32TunerPort);
        return HI_FAILURE;
    }

    pstTuner_Attr = (HI_TunerAttr_S *)pstTunerDataBuf->u32DataBuf[1];
    pstDemod_Attr = (HI_DemodAttr_S *)pstTunerDataBuf->u32DataBuf[0];
    u32ResetGpioNo = pstTunerDataBuf->u32DataBuf[2];

    /* Modified begin: l00185424, for outer demod configure, 2012-01-19 */
    /* in terms of g_tuner_type, register tuner service function */
    s32Ret = tuner_select_type(u32TunerPort, pstTuner_Attr, pstDemod_Attr, u32ResetGpioNo);
    /* Modified end: l00185424, for outer demod configure, 2012-01-19 */
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_select_type failed!\n");
    }

    return s32Ret;
}

HI_S32 tuner_osr_selecti2cchannel(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_U8 enI2cChannel = /*HI_UNF_I2C_CHANNEL_MAX*/16;

    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "invalid tuner port: %d\n", u32TunerPort);
        return HI_FAILURE;
    }

    enI2cChannel = (HI_U8)pstTunerDataStr->u32Data;
    if (HI_SUCCESS != tuner_select_i2c(u32TunerPort, enI2cChannel))
    {
        HI_INFO_TUNER( "tuner_select_i2c failed!\n");
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_test_single_agc(AGC_TEST_S *pstAgcTest)
{
    HI_U32 u32TunerPort = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstAgcTest->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner connect operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_test_single_agc) /* check if tuner conect is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }
    g_stTunerOps[u32TunerPort].tuner_test_single_agc( u32TunerPort, pstAgcTest );

    return HI_SUCCESS;
}

HI_S32 tuner_get_freq_symb_offset(TUNER_DATABUF_S *pstTunerDataBuf)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U8 u8DataTmp = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataBuf->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get freq and symb offset operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset) /* check if tuner get freq and symb offset is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner get freq and symb offset */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_freq_symb_offset(u32TunerPort,
            &pstTunerDataBuf->u32DataBuf[0], &pstTunerDataBuf->u32DataBuf[1]);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_get_freq_symb_offset failed!\n");
        return s32Ret;
    }

    switch (g_stTunerOps[u32TunerPort].enDemodDevType)
    {
    case HI_UNF_DEMOD_DEV_TYPE_3130I:
    case HI_UNF_DEMOD_DEV_TYPE_3130E:
    case HI_UNF_DEMOD_DEV_TYPE_J83B:
    s32Ret = qam_read_byte(u32TunerPort, BS_STAT_1_ADDR, &u8DataTmp);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "qam_read_byte BS_STAT_1_ADDR failed!\n");
        return s32Ret;
    }

    pstTunerDataBuf->u32DataBuf[2] = u8DataTmp;
        break;
        /* For avl6211, get offset in tuner_get_freq_symb_offset */
    case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
        break;

    case HI_UNF_DEMOD_DEV_TYPE_MXL101:
    case HI_UNF_DEMOD_DEV_TYPE_3136:
    case HI_UNF_DEMOD_DEV_TYPE_3136I:
        break;

    case HI_UNF_DEMOD_DEV_TYPE_MN88472:
    case HI_UNF_DEMOD_DEV_TYPE_IT9170:
    case HI_UNF_DEMOD_DEV_TYPE_IT9133:
        break;
    case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
        break;

    case HI_UNF_DEMOD_DEV_TYPE_NONE:
    case HI_UNF_DEMOD_DEV_TYPE_BUTT:
    default:
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_connect_timeout(TUNER_DATABUF_S *pstDataBuf)
{
    HI_U32 u32TunerPort = 0;
    HI_U32 u32TimeOut = 0;

    u32TimeOut = pstDataBuf->u32DataBuf[0];

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstDataBuf->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner_connect_timeout operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_connect_timeout) /* check if tuner_connect_timeout is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_connect_timeout */
    g_stTunerOps[u32TunerPort].tuner_connect_timeout(u32TimeOut);

    return HI_SUCCESS;
}

HI_S32 tuner_get_signal_info(TUNER_SIGNALINFO_S *pstSignal)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstSignal->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_signal_info) /* check if tuner get signal info is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_signal_info(u32TunerPort, &(pstSignal->stInfo));
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "tuner_get_signal_info failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_blindscan_init(TUNER_BLINDSCAN_S *pstBlindScan)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstBlindScan->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_blindscan_init) /* check if tuner get freq and symb offset is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_blindscan_init(u32TunerPort, &(pstBlindScan->stPara));
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_blindscan_init failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_blindscan_action(TUNER_BLINDSCAN_INFO_S *pstInfo)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstInfo->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_blindscan_action) /* check if tuner get freq and symb offset is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner blind scan */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_blindscan_action(u32TunerPort, pstInfo->pstPara);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_blindscan_action failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_terscan_action(TUNER_TERSCAN_INFO_S *pstInfo)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstInfo->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_terscan_action)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner blind scan */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_terscan_action(u32TunerPort, &(pstInfo->stScanPara.stTer), &(pstInfo->stScanPara.enTpInfo));
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_terscan_action failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_set_lnb_out(TUNER_LNB_OUT_S *pstLNBOut)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstLNBOut->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_ERR_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_lnb_out)
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_lnb_out(u32TunerPort, pstLNBOut->enOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "tuner_set_lnb_out failed!\n");
        return s32Ret;
    }

    s_stSatTunerResumeInfo[u32TunerPort].enLNBOut = pstLNBOut->enOut;
    return HI_SUCCESS;
}

HI_S32 tuner_send_continuous_22K(TUNER_DATA_S *pstLNB22K)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstLNB22K->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_send_continuous_22K)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_send_continuous_22K(u32TunerPort, pstLNB22K->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_send_continuous_22K failed!\n");
        return s32Ret;
    }
    s_stSatTunerResumeInfo[u32TunerPort].u32Continuous22K = pstLNB22K->u32Data;

    return HI_SUCCESS;
}

HI_S32 tuner_send_tone(TUNER_DATA_S *pstTone)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTone->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_send_tone)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_send_tone(u32TunerPort, pstTone->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_send_tone failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_DiSEqC_send_msg(TUNER_DISEQC_SENDMSG_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner unsupport DiSEqC, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg) /* check if tuner get freq and symb offset is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_DiSEqC_send_msg(u32TunerPort, &(pstPara->stSendMsg));
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_DiSEqC_send_msg failed!\n");
        return s32Ret;
    }
	
	s32Ret = tuner_parse_diseqc_cmd(&(pstPara->stSendMsg), &(s_stDiSEqCDrvStatus[u32TunerPort]));
	if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_parse_diseqc_cmd failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_DiSEqC_recv_msg(TUNER_DISEQC_RECVMSG_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner unsupport DiSEqC, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg) /* check if tuner get freq and symb offset is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_DiSEqC_recv_msg(u32TunerPort, pstPara->pstRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_DiSEqC_recv_msg failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_standby(TUNER_DATA_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_standby)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_standby(u32TunerPort, pstPara->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_standby failed!\n");
        return s32Ret;
    }

    /* If board has LNB control device, standby here */
    if (g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby)
    {
        s32Ret = g_stTunerOps[u32TunerPort].tuner_lnbctrl_dev_standby(u32TunerPort, pstPara->u32Data);
        if (HI_SUCCESS != s32Ret)
        {
            HI_INFO_TUNER( "tuner_standby failed!\n");
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}

#if 0
HI_S32 tuner_disable(TUNER_DATA_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_disable)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    s32Ret = g_stTunerOps[u32TunerPort].tuner_disable(u32TunerPort, pstPara->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_disable failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}
#endif

HI_S32 tuner_setfuncmode(TUNER_DATA_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    TUNER_FUNC_MODE_E enFuncMode;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner set func mode operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_setfuncmode)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    enFuncMode = pstPara->u32Data;
    s32Ret = g_stTunerOps[u32TunerPort].tuner_setfuncmode(u32TunerPort, enFuncMode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_setfuncmode failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_setplpid(TUNER_DATABUF_S *pstPara)
{
    HI_U32 u32TunerPort = 0,u32Mode = 0;
    HI_S32 s32Ret = 0;
    HI_U8 u8DataPlpId = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_INFO_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner set plp no operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_setplpid)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    u8DataPlpId = (HI_U8)(pstPara->u32DataBuf[0]);
    u32Mode = pstPara->u32DataBuf[1];
    s32Ret = g_stTunerOps[u32TunerPort].tuner_setplpid(u32TunerPort, u8DataPlpId,u32Mode);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_setplpid failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_set_common_plp_id(TUNER_DATA_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U8 u8ComPlpId = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_ERR_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner set plp no operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_common_plp_id)
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    u8ComPlpId = (pstPara->u32Data) & 0xFF;
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_common_plp_id(u32TunerPort, u8ComPlpId);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "tuner_set_common_plp_id failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_set_common_plp_combination(TUNER_DATA_S *pstPara)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U8 u8ComPlpEna = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstPara->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        HI_ERR_TUNER( "Invalid Tuner Port!\n");
        return HI_FAILURE;
    }

    /* if tuner set plp no operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_common_plp_combination)
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    u8ComPlpEna = (pstPara->u32Data) & 0xFF;
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_common_plp_combination(u32TunerPort, u8ComPlpEna);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "tuner_set_common_plp_combination failed!\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_getplpnum(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_plp_num) /* check if tuner get status is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* get tuner lock status */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_plp_num(u32TunerPort,
                                    (HI_U8 *)&pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "\n tuner_osr_getplpnum failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_getcurplptype(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_current_plp_type) /* check if tuner_get_current_plp_type is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_current_plp_type */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_current_plp_type(u32TunerPort,(HI_UNF_TUNER_T2_PLP_TYPE_E *)&pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "\n tuner_osr_getcurplptype failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_getplpid(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_plp_id) /* check if tuner_get_current_plp_type is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_current_plp_type */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_plp_id(u32TunerPort,(HI_U8 *)&pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "\n tuner_get_plp_id failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_getgroupplpid(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_group_plp_id) /* check if tuner_get_current_plp_type is supported */
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_current_plp_type */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_group_plp_id(u32TunerPort,(HI_U8 *)&pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "\n tuner_get_group_plp_id failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_setantennapower(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_antena_power) /* check if tuner_get_current_plp_type is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_set_ts_out */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_antena_power(u32TunerPort,
                                    (HI_UNF_TUNER_TER_ANTENNA_POWER_E)pstTunerDataStr->u32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_set_antena_power failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_settsout(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_ts_out) /* check if tuner_get_current_plp_type is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_set_ts_out */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_ts_out(u32TunerPort,
                                    (HI_UNF_TUNER_TSOUT_SET_S *)(pstTunerDataStr->u32Data));
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_get_status failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_tpverify(TUNER_TP_VERIFY_INFO_S *pstTunerTPVerifyInfo)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerTPVerifyInfo->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_tp_verify) /* check if tuner_get_current_plp_type is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_current_plp_type */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_tp_verify(u32TunerPort,
                                    &(pstTunerTPVerifyInfo->stTPVerifyPrm));
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_tp_verify failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 tuner_osr_setsatattr(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_UNF_TUNER_SAT_ATTR_S *pstSatAttr;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    pstSatAttr = (HI_UNF_TUNER_SAT_ATTR_S *)pstTunerDataStr->u32Data;

    s32Ret = tuner_set_sat_attr(u32TunerPort, pstSatAttr);
    /* Modified end: l00185424, for outer demod configure, 2012-01-19 */
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_select_type failed!\n");
    }

    return s32Ret;
}

HI_S32 tuner_osr_setterattr(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_UNF_TUNER_TER_ATTR_S *pstTerAttr;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    pstTerAttr = (HI_UNF_TUNER_TER_ATTR_S *)pstTunerDataStr->u32Data;

    s32Ret = tuner_set_ter_attr(u32TunerPort, pstTerAttr);
    /* Modified end: w00203631, for outer demod configure, 2014-02-21 */
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "tuner_osr_setterattr failed!\n");
    }

    return s32Ret;
}

HI_S32 tuner_osr_sampledata(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    TUNER_SAMPLE_DATA_PARAM_S *pstSampleParam = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    pstSampleParam = (TUNER_SAMPLE_DATA_PARAM_S *)(pstTunerDataStr->u32Data);

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_data_sample) /* check if tuner_get_current_plp_type is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_current_plp_type */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_data_sample(u32TunerPort, pstSampleParam->enDataSrc, pstSampleParam->u32DataLen, \
                                    pstSampleParam->pstData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_data_sample failed \n");
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 tuner_osr_select_stream(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U8  u8IsiID = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    u8IsiID = (HI_U8)pstTunerDataStr->u32Data;

    /* if tuner select vcm/acm stream is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_vcm_acm_stream) /* check if tuner_set_vcm_acm_stream is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_set_vcm_acm_stream */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_vcm_acm_stream(u32TunerPort, u8IsiID);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_set_vcm_acm_stream failed \n");
        return s32Ret;
    }

    return s32Ret;
}

HI_S32 tuner_osr_get_stream(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U32 u32TotalStream = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get vcm/acm operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_vcm_acm_stream) /* check if tuner_get_vcm_acm_stream is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_vcm_acm_stream */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_vcm_acm_stream(u32TunerPort, &u32TotalStream);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_get_vcm_acm_stream failed \n");
        return s32Ret;
    }

    pstTunerDataStr->u32Data = u32TotalStream;

    return s32Ret;
}

HI_S32 tuner_osr_get_isi_id(PTR_TUNER_DATABUF_S pstTunerDataBufStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U8  u8Stream = 0;
    HI_U8  u8IsiId = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataBufStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }
    u8Stream = (HI_U8)pstTunerDataBufStr->u32DataBuf[0];

    /* if tuner get isi id operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_isi_id) /* check if tuner_get_isi_id is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_vcm_acm_stream */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_isi_id(u32TunerPort, u8Stream, &u8IsiId);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_get_isi_id failed \n");
        return s32Ret;
    }

    pstTunerDataBufStr->u32DataBuf[1] = (HI_U32)u8IsiId;

    return s32Ret;
}

HI_S32 tuner_osr_get_agc(PTR_TUNER_DATABUF_S pstTunerDataBufStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U32 u32Freq;
    HI_U32 u32Agc;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataBufStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }
    u32Freq = pstTunerDataBufStr->u32DataBuf[0];

    /* if tuner get agc operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_get_agc) /* check if tuner_get_agc is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_tone */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_get_agc(u32TunerPort, u32Freq, &u32Agc );
    if (HI_SUCCESS != s32Ret)
    {
        //HI_ERR_TUNER( "\n tuner_get_agc failed \n");
        return s32Ret;
    }

    pstTunerDataBufStr->u32DataBuf[1] = u32Agc;

    return s32Ret;
}

HI_S32 tuner_osr_set_scramble(PTR_TUNER_DATA_S pstTunerDataStr)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;
    HI_U32 u32Value = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    u32TunerPort = pstTunerDataStr->u32Port;
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }
    u32Value = pstTunerDataStr->u32Data;

    /* if tuner get vcm/acm operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerPort].tuner_set_scramble) /* check if tuner_set_scramble is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_get_vcm_acm_stream */
    s32Ret = g_stTunerOps[u32TunerPort].tuner_set_scramble(u32TunerPort, u32Value);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_set_scramble failed \n");
        return s32Ret;
    }

    return s32Ret;
}
/*
 *    ioctl method.  enable user to contrl tuner
 *    parameter:
 *        TUNER_CONNECT_CMD:  tuner connect
 *        TUNER_GET_STATUS_CMD:  get the status of tuner
 *        TUNER_GET_SIGNALSTRENGTH_CMD:  get signal strength from tuner
 *        TUNER_GET_BER_CMD:   get BER from tuner
 *        TUNER_GET_SNR_CMD:   get SNR from tuner
 *        TUNER_SET_TSTYPE_CMD: set ts stream format
 *       TUNER_SELECT_TYPE_CMD: select tuner type
 *
 */
HI_S32 tuner_ioctl(struct inode *inode, struct file *file, HI_U32 cmd, HI_VOID *arg)
{
    HI_S32 s32Ret = HI_FAILURE;

    if (HI_NULL == arg)
    {
        HI_INFO_TUNER("copy data from user error: cmd=%d\n", _IOC_NR(cmd));
        return HI_FAILURE;
    }

    switch (cmd)
    {
        case TUNER_CONNECT_CMD:
        case TUNER_CONNECTUNBLOCK_CMD:
            {
                TUNER_SIGNAL_S *pstPara = (TUNER_SIGNAL_S *)arg;
                s32Ret = tuner_osr_connect(pstPara);
                break;
            }
        case TUNER_GET_STATUS_CMD:
            {
                TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
                s32Ret = tuner_osr_getstatus(pstPara);
                break;
            }
        case TUNER_GET_SIGNALSTRENGTH_CMD:
            {
                TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
                s32Ret = tuner_osr_getsignalstrength(pstPara);
                break;
            }
        case TUNER_GET_BER_CMD:
            {
                TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
                s32Ret = tuner_osr_getber(pstPara);
                break;
            }
        case TUNER_GET_SNR_CMD:
            {
                TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
                s32Ret = tuner_osr_getsnr(pstPara);
                break;
            }
        case TUNER_SET_TSTYPE_CMD:
            {
                TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
                s32Ret = tuner_osr_settstype(pstPara);
                break;
            }
        case TUNER_SELECT_TYPE_CMD:
            {
                TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
                s32Ret = tuner_osr_selecttype(pstPara);
                break;
            }
        case TUNER_SELECT_I2C_CMD:
            {
                TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
                s32Ret = tuner_osr_selecti2cchannel(pstPara);
                break;
            }
        case TUNER_TEST_SINGLE_AGC:
            {
                AGC_TEST_S *pstPara = (AGC_TEST_S *)arg;
                s32Ret = tuner_test_single_agc(pstPara);
                break;
            }
        case TUNER_GET_FREQ_SYMB_OFFSET:
            {
                TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
                s32Ret = tuner_get_freq_symb_offset(pstPara);
                break;
            }
        case TUNER_CONNECT_TIMEOUT_CMD:
            {
                TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
                s32Ret = tuner_osr_connect_timeout(pstPara);
                break;
            }
        case TUNER_GET_SIGANLINFO_CMD:
        {
            TUNER_SIGNALINFO_S *pstPara = (TUNER_SIGNALINFO_S *)arg;
            s32Ret = tuner_get_signal_info(pstPara);
            break;
        }
        case TUNER_BLINDSCAN_INIT_CMD:
        {
            TUNER_BLINDSCAN_S *pstPara = (TUNER_BLINDSCAN_S *)arg;
            s32Ret = tuner_blindscan_init(pstPara);
            break;
        }
        case TUNER_BLINDSCAN_ACTION_CMD:
        {
            TUNER_BLINDSCAN_INFO_S *pstPara = (TUNER_BLINDSCAN_INFO_S *)arg;
            s32Ret = tuner_blindscan_action(pstPara);
            break;
        }
        case TUNER_TERSCAN_ACTION_CMD:
        {
            TUNER_TERSCAN_INFO_S *pstPara = (TUNER_TERSCAN_INFO_S *)arg;
            s32Ret = tuner_terscan_action(pstPara);
            break;
        }
        case TUNER_SET_LNBOUT_CMD:
        {
            TUNER_LNB_OUT_S *pstPara = (TUNER_LNB_OUT_S *)arg;
            s32Ret = tuner_set_lnb_out(pstPara);
            break;
        }
        case TUNER_SEND_CONTINUOUS_22K_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_send_continuous_22K(pstPara);
            break;
        }
        case TUNER_SEND_TONE_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_send_tone(pstPara);
            break;
        }
        case TUNER_DISEQC_SEND_MSG_CMD:
        {
            TUNER_DISEQC_SENDMSG_S *pstPara = (TUNER_DISEQC_SENDMSG_S *)arg;
            s32Ret = tuner_DiSEqC_send_msg(pstPara);
            break;
        }
        case TUNER_DISEQC_RECV_MSG_CMD:
        {
            TUNER_DISEQC_RECVMSG_S *pstPara = (TUNER_DISEQC_RECVMSG_S *)arg;
            s32Ret = tuner_DiSEqC_recv_msg(pstPara);
            break;
        }
        case TUNER_STANDBY_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_standby(pstPara);
            break;
        }
        /*case TUNER_DISABLE_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_disable(pstPara);
            break;
        }*/
        case TUNER_SETFUNCMODE_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_setfuncmode(pstPara);
            break;
        }
        case TUNER_SETPLPNO_CMD:
        {
            TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
            s32Ret = tuner_setplpid(pstPara);
            break;
        }
        case TUNER_SET_COMMONPLP_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_set_common_plp_id(pstPara);
            break;
        }
        case TUNER_SET_COMMONPLP_COMBINATION_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_set_common_plp_combination(pstPara);
            break;
        }
        case TUNER_GETPLPNUM_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_getplpnum(pstPara);
            break;
        }
        case TUNER_GETCURPLPTYPE_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_getcurplptype(pstPara);
            break;
        }
        case TUNER_GET_PLP_ID_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_getplpid(pstPara);
            break;
        }
        case TUNER_GET_GROUP_PLP_ID_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_getgroupplpid(pstPara);
            break;
        }
        case TUNER_SET_ANTENNA_POWER_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_setantennapower(pstPara);
            break;
        }
        case TUNER_SETTSOUT_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_settsout(pstPara);
            break;
        }
        case TUNER_TPVERIFY_CMD:
        {
            TUNER_TP_VERIFY_INFO_S *pstPara = (TUNER_TP_VERIFY_INFO_S *)arg;
            s32Ret = tuner_osr_tpverify(pstPara);
            break;
        }
        case TUNER_SETDEMODATTR_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;

            if(HI_UNF_DEMOD_DEV_TYPE_3137 == g_stTunerOps[pstPara->u32Port].enDemodDevType)
            {
                s32Ret = tuner_osr_setterattr(pstPara);
            }
            else if(HI_UNF_DEMOD_DEV_TYPE_3136 == g_stTunerOps[pstPara->u32Port].enDemodDevType
                || HI_UNF_DEMOD_DEV_TYPE_3136I == g_stTunerOps[pstPara->u32Port].enDemodDevType
                || HI_UNF_DEMOD_DEV_TYPE_AVL6211 == g_stTunerOps[pstPara->u32Port].enDemodDevType)
            {
                s32Ret = tuner_osr_setsatattr(pstPara);
            }
            else
                s32Ret = HI_SUCCESS;
            break;
        }
        case TUNER_SAMPLE_DATA_CMD:
        {
            TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
            s32Ret = tuner_osr_sampledata(pstPara);
            break;
        }
		case TUNER_SET_ISI_ID_CMD:
		{
			TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
			s32Ret = tuner_osr_select_stream(pstPara);
			break;
		}
		case TUNER_GET_TOTAL_STREAM_CMD:
		{
			TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
			s32Ret = tuner_osr_get_stream(pstPara);
			break;
		}
		case TUNER_GET_ISI_ID_CMD:
		{
			TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
			s32Ret = tuner_osr_get_isi_id(pstPara);
			break;
		}
		case TUNER_SET_SCRAMBLE_CMD:
		{
			TUNER_DATA_S *pstPara = (TUNER_DATA_S *)arg;
			s32Ret = tuner_osr_set_scramble(pstPara);
			break;
		}
		case TUNER_GET_AGC:
        {
            TUNER_DATABUF_S *pstPara = (TUNER_DATABUF_S *)arg;
            s32Ret = tuner_osr_get_agc(pstPara);
            break;
        }
        default:
        {
            s32Ret= -EFAULT;
            break;
        }
    }
    return s32Ret;
}

long hi_tuner_ioctl(struct file *filp, HI_U32 cmd, unsigned long arg)
{
    HI_S32 s32Ret;

    s32Ret = down_interruptible(&g_TunerMutex);

    if (HI_TUNER_IOC_MAGIC != _IOC_TYPE(cmd))
    {
        up(&g_TunerMutex);
        return -ENOTTY;
    }

    s32Ret = HI_DRV_UserCopy(filp->f_dentry->d_inode, filp, cmd, arg, tuner_ioctl);
    up(&g_TunerMutex);
    return s32Ret;
}

HI_S32 hi3796c_enable_crg(void)
{
#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
     U_PERI_AGC_SEL unTmpPeriAGCSel;
     U_PERI_CRG57 unTmpPeriCrg57;
     U_PERI_CRG58 unTmpPeriCrg58;
     U_PERI_QAM    unTmpPeriQam;

   //ADC-DVB-C��
     unTmpPeriAGCSel.u32 = g_pstRegPeri->PERI_AGC_SEL.u32;
     unTmpPeriAGCSel.bits.peri_agc_rf_sel = 0;
     unTmpPeriAGCSel.bits.peri_agc_sel = 0x1;
     g_pstRegPeri->PERI_AGC_SEL.u32 = unTmpPeriAGCSel.u32;


     unTmpPeriCrg57.u32 = g_pstRegCrg->PERI_CRG57.u32;
     unTmpPeriCrg58.u32 = g_pstRegCrg->PERI_CRG58.u32;
     unTmpPeriQam.u32 = g_pstRegPeri->PERI_QAM.u32;
     {

     /*select QAM TSCLK source 150MHz,PERI_CRG57[19:18]:01 ; QAM TSCLK 16 div,PERI_CRG57[23:20] :0111,*/
    unTmpPeriCrg57.bits.qam_ts_clk_sel =  0x01;
    unTmpPeriCrg57.bits.qam_ts_clk_div =0x7;
     /*TS_CLK_OUT config  the opposite phase,PERI_CRG57[16]:1;*/
        /*ads_clk config the same phase,PERI_CRG57[17]:0*/
    unTmpPeriCrg57.bits.qam_tsout_pctrl = 0x1;
    unTmpPeriCrg57.bits.qam_adsclk_pctrl = 0;
     /*config qam_*_cken open, PERI_CRG57[6:0]:1111111*/
    unTmpPeriCrg57.bits.qam_2x_cken = 1;
    unTmpPeriCrg57.bits.qam_1x_cken = 1;

    unTmpPeriCrg57.bits.qam_j83b_cken = 1;
    unTmpPeriCrg57.bits.qam_j83ac_cken = 1;
    unTmpPeriCrg57.bits.qam_ads_cken = 1;

    unTmpPeriCrg57.bits.qam_ts_cken = 1;
    unTmpPeriCrg57.bits.qam_tsout_cken = 1;

    /*don't reset qam_ads_srst_req and qam_ts_srst_req, PERI_CRG57[13:12]:00*/
    unTmpPeriCrg57.bits.qam_ads_srst_req = 0;
    unTmpPeriCrg57.bits.qam_ts_srst_req = 0;
       /*don't reset qam_2x_srst_req and qam_1x_srst_req, PERI_CRG57[9:8]:00*/
    unTmpPeriCrg57.bits.qam_2x_srst_req = 0;
    unTmpPeriCrg57.bits.qam_1x_srst_req = 0;

    unTmpPeriCrg57.bits.qam2x_clk_sel = 0;
    /*config adc clk 28.8MHz*/

   /*qamadc_pctrlPERI_CRG58[14]:0*/
    unTmpPeriCrg58.bits.qamadc_pctrl = 0;
     /*config qamadc_clk_sel 28.8MHz,  PERI_CRG58[9:7]:00*/
    unTmpPeriCrg58.bits.qamadc_clk_sel = 0x00;

     /*config qamctrl_clk_sel 28.8MHz , PERI_CRG58[12:10]:00; \
                config qamctrl_clk_div for the same frequence, PERI_CRG58[13]:0*/
    unTmpPeriCrg58.bits.qamctrl_clk_sel = 0x00;
    unTmpPeriCrg58.bits.qamctrl_clk_div = 0;

    unTmpPeriQam.bits.peri_qamc_i2c_devaddr =0x50;
   }
    g_pstRegCrg->PERI_CRG57.u32 = unTmpPeriCrg57.u32;
    g_pstRegCrg->PERI_CRG58.u32 = unTmpPeriCrg58.u32;
    g_pstRegPeri->PERI_QAM.u32 = unTmpPeriQam.u32;
 #endif
    return 0;
}

HI_VOID hi3796c_enable_adc(HI_VOID)
{
#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    HI_U32 i=30;
    U_PERI_QAM_ADC0 unTmpPeriQamADC0;
    U_PERI_QAM_ADC1 unTmpPeriQamADC1;

    unTmpPeriQamADC0.u32 = g_pstRegPeri->PERI_QAM_ADC0.u32;
    unTmpPeriQamADC1.u32 = g_pstRegPeri->PERI_QAM_ADC1.u32;
    {
        unTmpPeriQamADC0.bits.peri_qamadc_selof = 0;

        /*ADC power down:PERI_QAM_ADC0[1:0]:00*/
        unTmpPeriQamADC0.bits.peri_qamadc_opm = 00;
        /*ADC i2c_resetz :0 */
        unTmpPeriQamADC1.bits.peri_qamadc_i2c_resetz = 0;
    }

    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;
    msleep(1);
    g_pstRegPeri->PERI_QAM_ADC1.u32 = unTmpPeriQamADC1.u32;
    msleep(1);

    /*ADC i2c_resetz :1 */
    unTmpPeriQamADC1.bits.peri_qamadc_i2c_resetz = 1;
    g_pstRegPeri->PERI_QAM_ADC1.u32 = unTmpPeriQamADC1.u32;
    msleep(1);
    {
        /*ADC Normal Operation:PERI_QAM_ADC0[1:0]:11*/
        unTmpPeriQamADC0.bits.peri_qamadc_opm = 3;
    }

    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;

    while (!g_pstRegPeri->PERI_QAM_ADC0.bits.peri_qamadc_adcrdy)
    {
        if (!i)
        {
            HI_ERR_TUNER( "ADC is not ready\n");
            break;
        }
        msleep(1);
        i--;
    }

    unTmpPeriQamADC1.bits.peri_qamadc_enavcmin = 0x1;
    unTmpPeriQamADC0.bits.peri_qamadc_selof        = 0x0;
    unTmpPeriQamADC0.bits.peri_qamadc_bctrl        = 0x9;
    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;
    g_pstRegPeri->PERI_QAM_ADC1.u32 = unTmpPeriQamADC1.u32;
#endif
}

HI_VOID hi3796c_disable_adc(HI_VOID)
{
#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    U_PERI_QAM_ADC0 unTmpPeriQamADC0;

    unTmpPeriQamADC0.u32 = g_pstRegPeri->PERI_QAM_ADC0.u32;
    {
        /*ADC power down:PERI_QAM_ADC0[1:0]:00*/
        unTmpPeriQamADC0.bits.peri_qamadc_opm = 00;
    }
    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;
#endif
}

HI_S32  hi3796c_disable_crg(void)
{
#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    U_PERI_CRG57 unTmpPeriCrg57;

    if (0 == g_u32CrgEnableFlag)
    {
          return 0;
    }

    g_u32CrgEnableFlag = 0;

    unTmpPeriCrg57.u32 = g_pstRegCrg->PERI_CRG57.u32;
    {
        /*config qam_*_cken open, PERI_CRG57[6:0]:0000000*/
        unTmpPeriCrg57.bits.qam_2x_cken = 0;
        unTmpPeriCrg57.bits.qam_1x_cken = 0;

        unTmpPeriCrg57.bits.qam_j83b_cken = 0;
        unTmpPeriCrg57.bits.qam_j83ac_cken = 0;
        unTmpPeriCrg57.bits.qam_ads_cken = 0;

        unTmpPeriCrg57.bits.qam_ts_cken = 0;
        unTmpPeriCrg57.bits.qam_tsout_cken = 0;
    }
    g_pstRegCrg->PERI_CRG57.u32 = unTmpPeriCrg57.u32;
#endif
    return 0;
}

static HI_VOID tuner_enable_crg(HI_VOID)
{
#if defined (CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)
     U_PERI_CRG57 unTmpPeriCrg57;
     U_PERI_CRG58 unTmpPeriCrg58;
     U_PERI_QAM    unTmpPeriQam;
#endif
    g_u32CrgEnableFlag = 1;

#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)
    unTmpPeriCrg57.u32 = g_pstRegCrg->PERI_CRG57.u32;
    unTmpPeriCrg58.u32 = g_pstRegCrg->PERI_CRG58.u32;
    unTmpPeriQam.u32 = g_pstRegPeri->PERI_QAM.u32;

    {
        /*select QAM TSCLK source 150MHz,PERI_CRG57[19:18]:01 ; QAM TSCLK 16 div,PERI_CRG57[23:20] :0111,*/
        unTmpPeriCrg57.bits.qam_ts_clk_sel =  0x01;
        unTmpPeriCrg57.bits.qam_ts_clk_div =0x7;
        /*TS_CLK_OUT config  the opposite phase,PERI_CRG57[16]:1;*/
        /*ads_clk config the same phase,PERI_CRG57[17]:0*/
        unTmpPeriCrg57.bits.qam_tsout_pctrl = 0x1;
        unTmpPeriCrg57.bits.qam_adsclk_pctrl = 0;
        /*config qam_*_cken open, PERI_CRG57[6:0]:1111111*/
        unTmpPeriCrg57.bits.qam_2x_cken = 1;
        unTmpPeriCrg57.bits.qam_1x_cken = 1;

        unTmpPeriCrg57.bits.qam_j83b_cken = 1;
        unTmpPeriCrg57.bits.qam_j83ac_cken = 1;
        unTmpPeriCrg57.bits.qam_ads_cken = 1;

        unTmpPeriCrg57.bits.qam_ts_cken = 1;
        unTmpPeriCrg57.bits.qam_tsout_cken = 1;

        /*don't reset qam_ads_srst_req and qam_ts_srst_req, PERI_CRG57[13:12]:00*/
        unTmpPeriCrg57.bits.qam_ads_srst_req = 0;
        unTmpPeriCrg57.bits.qam_ts_srst_req = 0;
        /*don't reset qam_2x_srst_req and qam_1x_srst_req, PERI_CRG57[9:8]:00*/
        unTmpPeriCrg57.bits.qam_2x_srst_req = 0;
        unTmpPeriCrg57.bits.qam_1x_srst_req = 0;

        /*config adc clk 28.8MHz*/
        /*config qamadc_clk_sel 28.8MHz,  PERI_CRG58[9:8]:00*/
        unTmpPeriCrg58.bits.qamadc_clk_sel = 0x00;

        /*config qamctrl_clk_sel 28.8MHz , PERI_CRG58[11:10]:00; \
            config qamctrl_clk_div for the same frequence, PERI_CRG58[12]:0*/
        unTmpPeriCrg58.bits.qamctrl_clk_sel = 0x00;
        unTmpPeriCrg58.bits.qamctrl_clk_div = 0;

        unTmpPeriQam.bits.qam_i2c_devaddr =0x50;
    }
    g_pstRegCrg->PERI_CRG57.u32 = unTmpPeriCrg57.u32;
    g_pstRegCrg->PERI_CRG58.u32 = unTmpPeriCrg58.u32;
    g_pstRegPeri->PERI_QAM.u32 = unTmpPeriQam.u32;

#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    hi3796c_enable_crg();
#endif
}

static HI_VOID tuner_disable_crg(HI_VOID)
{
#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)
    U_PERI_CRG57 unTmpPeriCrg57;
#endif

    if (0 == g_u32CrgEnableFlag)
    {
        return;
    }
    g_u32CrgEnableFlag = 0;

#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)
    unTmpPeriCrg57.u32 = g_pstRegCrg->PERI_CRG57.u32;
    {
     /*config qam_*_cken open, PERI_CRG57[6:0]:0000000*/
    unTmpPeriCrg57.bits.qam_2x_cken = 0;
    unTmpPeriCrg57.bits.qam_1x_cken = 0;

    unTmpPeriCrg57.bits.qam_j83b_cken = 0;
    unTmpPeriCrg57.bits.qam_j83ac_cken = 0;
    unTmpPeriCrg57.bits.qam_ads_cken = 0;

    unTmpPeriCrg57.bits.qam_ts_cken = 0;
    unTmpPeriCrg57.bits.qam_tsout_cken = 0;
    }
    g_pstRegCrg->PERI_CRG57.u32 = unTmpPeriCrg57.u32;
#endif

#if defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    hi3796c_disable_crg();
#endif
}


static HI_VOID tuner_enable_adc(HI_VOID)
{
#if defined (CHIP_TYPE_hi3716cv200)|| defined (CHIP_TYPE_hi3716mv400)
    HI_U32 i=30;
    U_PERI_QAM_ADC0 unTmpPeriQamADC0;
    U_PERI_QAM_ADC1 unTmpPeriQamADC1;

    unTmpPeriQamADC0.u32 = g_pstRegPeri->PERI_QAM_ADC0.u32;
    unTmpPeriQamADC1.u32 = g_pstRegPeri->PERI_QAM_ADC1.u32;
    {
      /*ADC power down:PERI_QAM_ADC0[1:0]:00*/
      unTmpPeriQamADC0.bits.opm = 00;
      /*ADC i2c_resetz :0 */
      unTmpPeriQamADC1.bits.i2c_resetz = 0;
    }
    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;
    msleep(1);
    g_pstRegPeri->PERI_QAM_ADC1.u32 = unTmpPeriQamADC1.u32;
    msleep(1);
     /*ADC i2c_resetz :1 */
    unTmpPeriQamADC1.bits.i2c_resetz = 1;
    g_pstRegPeri->PERI_QAM_ADC1.u32 = unTmpPeriQamADC1.u32;
    msleep(1);
    {
      /*ADC Normal Operation:PERI_QAM_ADC0[1:0]:11*/
      unTmpPeriQamADC0.bits.opm = 3;
    }

    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;

    while(!g_pstRegPeri->PERI_QAM_ADC0.bits.adcrdy)
    {
     if(!i)
     {
          HI_ERR_TUNER( "ADC is not ready\n");
          break;
     }
     msleep(1);
     i--;
    }
#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)
    hi3796c_enable_adc();
#endif

}

static HI_VOID tuner_disable_adc(HI_VOID)
{
#if defined(CHIP_TYPE_hi3716cv200) || defined(CHIP_TYPE_hi3716mv400)
    U_PERI_QAM_ADC0 unTmpPeriQamADC0;

    unTmpPeriQamADC0.u32 = g_pstRegPeri->PERI_QAM_ADC0.u32;
    {
      /*ADC power down:PERI_QAM_ADC0[1:0]:00*/
      unTmpPeriQamADC0.bits.opm = 00;

    }
    g_pstRegPeri->PERI_QAM_ADC0.u32 = unTmpPeriQamADC0.u32;

#elif defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100)

    hi3796c_disable_adc();

#endif
}

static HI_S32 tuner_geti2cFunc(HI_VOID)
{
   HI_S32 s32Ret  = 0;
   s_tuner_pI2cFunc = HI_NULL;

   s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_I2C, (HI_VOID**)&s_tuner_pI2cFunc);
   if ((HI_SUCCESS != s32Ret) || !s_tuner_pI2cFunc || !s_tuner_pI2cFunc->pfnI2cWrite || !s_tuner_pI2cFunc->pfnI2cRead || !s_tuner_pI2cFunc->pfnI2cReadDirectly ||!s_tuner_pI2cFunc->pfnI2cWriteNostop)
   {
       HI_FATAL_TUNER("I2C not found\n");
       return HI_FAILURE;
   }

   s_tuner_pGpioFunc = HI_NULL;
   s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_GPIO, (HI_VOID**)&s_tuner_pGpioFunc);
   if ((HI_SUCCESS != s32Ret) || !s_tuner_pGpioFunc || !s_tuner_pGpioFunc->pfnGpioDirSetBit || !s_tuner_pGpioFunc->pfnGpioWriteBit||!s_tuner_pGpioFunc->pfnGpioDirSetBit)
   {

       HI_FATAL_TUNER("GPIO not found\n");
       return HI_FAILURE;
   }

   s_tuner_pGpioI2cFunc = HI_NULL;

   s32Ret = HI_DRV_MODULE_GetFunction(HI_ID_GPIO_I2C, (HI_VOID**)&s_tuner_pGpioI2cFunc);
   if ((HI_SUCCESS != s32Ret) || !s_tuner_pGpioI2cFunc || !s_tuner_pGpioI2cFunc->pfnGpioI2cWriteExt|| !s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt || !s_tuner_pGpioI2cFunc->pfnGpioI2cReadExtDiRectly)
   {
       HI_FATAL_TUNER("GPIO_I2C not found\n");
       return HI_FAILURE;
   }

   return HI_SUCCESS;

}


HI_S32 tuner_suspend (PM_BASEDEV_S *pdev, pm_message_t state)
{
    tuner_disable_crg();
    tuner_disable_adc();
    HI_PRINT("TUNER suspend OK\n");
    return HI_SUCCESS;
}

HI_S32 tuner_resume(PM_BASEDEV_S *pdev)
{
    HI_S32  i = 0;
    HI_S32  Ret = 0;
    HI_U8   u8DataTmp = 0;

    tuner_enable_crg();
    tuner_enable_adc();

    Ret = tuner_geti2cFunc();
    if (HI_SUCCESS != Ret)
    {
        HI_ERR_TUNER("tuner_geti2cFunc err\n");
        return HI_FAILURE;
    }

    for (i = 0; i < TUNER_NUM; i++)
    {
        switch (g_stTunerOps[i].enDemodDevType)
        {
            case HI_UNF_DEMOD_DEV_TYPE_3130I:
            case HI_UNF_DEMOD_DEV_TYPE_J83B:
                if (g_stTunerOps[i].tuner_resume)
                {
                    g_stTunerOps[i].tuner_resume(i);
                }
                break;

        #ifdef DEMOD_DEV_TYPE_HI3130
            case HI_UNF_DEMOD_DEV_TYPE_3130E:
                tuner_chip_reset(s_u32ResetGpioNo[i]);
                if (g_stTunerOps[i].tuner_resume)
                {
                    g_stTunerOps[i].tuner_resume(i);
                }

                qam_read_byte(i, MCTRL_1_ADDR, &u8DataTmp);
                if ((u8DataTmp >> 5) == 5)
                {
                    hi3130v200_set_hard_reg_value(i);
                }
                break;
        #endif

		    case HI_UNF_DEMOD_DEV_TYPE_MXL254:
		    case HI_UNF_DEMOD_DEV_TYPE_MXL214:
		    case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
			    tuner_chip_reset(s_u32ResetGpioNo[i]);
			    if (g_stTunerOps[i].tuner_init)
			    {
			        g_stTunerOps[i].tuner_init(i, g_stTunerOps[i].enI2cChannel, g_stTunerOps[i].enTunerDevType);
			    }
			    break;

            case HI_UNF_DEMOD_DEV_TYPE_MN88472:
            case HI_UNF_DEMOD_DEV_TYPE_3136:
                tuner_chip_reset(s_u32ResetGpioNo[i]);

                if (g_stTunerOps[i].tuner_init)
                {
                    g_stTunerOps[i].tuner_init(i, g_stTunerOps[i].enI2cChannel, g_stTunerOps[i].enTunerDevType);
                }

                if (g_stTunerOps[i].tuner_set_sat_attr)
                {
                    g_stTunerOps[i].tuner_set_sat_attr(i, &(s_stSatTunerResumeInfo[i].stSatTunerAttr));
                }

                if (g_stTunerOps[i].tuner_set_ts_out)
                {
                    if (s_stSatTunerResumeInfo[i].bSetTsOut)
                    {
                        g_stTunerOps[i].tuner_set_ts_out(i, &(s_stSatTunerResumeInfo[i].stTsOut));
                    }
                }

                if (g_stTunerOps[i].tuner_lnbctrl_dev_init)
                {
                    g_stTunerOps[i].tuner_lnbctrl_dev_init(i, g_stTunerOps[i].enI2cChannel,
                                                                      s_stSatTunerResumeInfo[i].stSatTunerAttr.u16LNBDevAddress, g_stTunerOps[i].enDemodDevType);
                }

                if (g_stTunerOps[i].tuner_set_lnb_out)
                {
                    g_stTunerOps[i].tuner_set_lnb_out(i, s_stSatTunerResumeInfo[i].enLNBOut);
                }

                if (g_stTunerOps[i].tuner_send_continuous_22K)
                {
                    g_stTunerOps[i].tuner_send_continuous_22K(i, s_stSatTunerResumeInfo[i].u32Continuous22K);
                }

                break;

            case HI_UNF_DEMOD_DEV_TYPE_3137:
                tuner_chip_reset(s_u32ResetGpioNo[i]);

                if (g_stTunerOps[i].tuner_init)
                {
                    g_stTunerOps[i].tuner_init(i, g_stTunerOps[i].enI2cChannel, g_stTunerOps[i].enTunerDevType);
                }

                if (g_stTunerOps[i].tuner_set_ts_type)
                {
                    g_stTunerOps[i].tuner_set_ts_type(i, s_stSatTunerResumeInfo[i].enOutMode);
                }

                if (g_stTunerOps[i].tuner_set_ter_attr)
                {
                    g_stTunerOps[i].tuner_set_ter_attr(i, &(s_stSatTunerResumeInfo[i].stTerTunerAttr));
                }

                if (g_stTunerOps[i].tuner_set_ts_out)
                {
                    if (s_stSatTunerResumeInfo[i].bSetTsOut)
                    {
                        g_stTunerOps[i].tuner_set_ts_out(i, &(s_stSatTunerResumeInfo[i].stTsOut));
                    }
                }

                break;

            case HI_UNF_DEMOD_DEV_TYPE_3136I:
                if (g_stTunerOps[i].tuner_init)
                {
                    g_stTunerOps[i].tuner_init(i, g_stTunerOps[i].enI2cChannel, g_stTunerOps[i].enTunerDevType);
                }

                if (g_stTunerOps[i].tuner_set_sat_attr)
                {
                    g_stTunerOps[i].tuner_set_sat_attr(i, &(s_stSatTunerResumeInfo[i].stSatTunerAttr));
                }

                if (g_stTunerOps[i].tuner_lnbctrl_dev_init)
                {
                    g_stTunerOps[i].tuner_lnbctrl_dev_init(i, g_stTunerOps[i].enI2cChannel,
                                                                      s_stSatTunerResumeInfo[i].stSatTunerAttr.u16LNBDevAddress, g_stTunerOps[i].enDemodDevType);
                }

                if (g_stTunerOps[i].tuner_set_lnb_out)
                {
                    g_stTunerOps[i].tuner_set_lnb_out(i, s_stSatTunerResumeInfo[i].enLNBOut);
                }

                if (g_stTunerOps[i].tuner_send_continuous_22K)
                {
                    g_stTunerOps[i].tuner_send_continuous_22K(i, s_stSatTunerResumeInfo[i].u32Continuous22K);
                }

                break;

            default:
                break;
        }
    }

    for (i = 0; i < TUNER_NUM; i++)
    {
        if ((HI_UNF_TUNER_SIGNAL_LOCKED == s_enTunerStat[i]) && (g_stTunerOps[i].tuner_connect))
        {
            g_stTunerOps[i].tuner_connect(i, &g_stTunerOps[i].stCurrPara);
            HI_INFO_TUNER(" tuner port [%d] connected! \n", i);
        }
    }

    HI_PRINT("TUNER resume OK\n");
    return HI_SUCCESS;
}

HI_S32 tuner_proc_read_reg(struct seq_file * p, HI_VOID * v)
{
    HI_U32 u32TunerPort;

    PROC_PRINT(p,"---------Hisilicon TUNER Reg Info---------\n");

    for ( u32TunerPort = 0; u32TunerPort < TUNER_NUM; u32TunerPort++ )
    {
        if ( HI_NULL == g_stTunerOps[u32TunerPort].tuner_connect )
        {
            continue;
        }

        if (g_stTunerOps[u32TunerPort].tuner_get_registers)
        {
            g_stTunerOps[u32TunerPort].tuner_get_registers(u32TunerPort, p);
        }
    }
    return HI_SUCCESS;
}

HI_S32 tuner_proc_read(struct seq_file *p, HI_VOID *v)
{
    HI_U32 u32TunerPort;
    HI_U32 au32SignalStrength[3] = {0};
    HI_U32 au32Tmp[3] = {0};
    HI_U32 u32SNR = 0;
    HI_U32 u32Ber = 0;
    HI_U64 u64TmpBer = 0;
    HI_U32 au32Rs[3] = {0};
    HI_CHAR acQamType[8];
    HI_CHAR acTunerType[20];
    HI_CHAR acDemodType[20];
    HI_CHAR acTunerLock[10];
    HI_CHAR acFECType[10];
    HI_CHAR acFECRate[10];
    HI_CHAR acFFTMode[10];
    HI_CHAR acGI[10];
    HI_CHAR acHierAlpha[10];
    HI_CHAR acTSPrio[10];
    HI_CHAR acCCMMode[10];
	HI_CHAR acSignalType[10];
    HI_UNF_TUNER_LOCK_STATUS_E enTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
    HI_UNF_TUNER_SIGNALINFO_S stSignalInfo = {0};

    PROC_PRINT(p,"---------Hisilicon TUNER Info---------\n");
    PROC_PRINT(p,
            "Port: LockStat    I2CChannel	Signal    Frequency(KHz)    SymbRate    QamMode    DemodType    Demodaddr   TunerType    Tuneraddr\n");


    for ( u32TunerPort = 0; u32TunerPort < TUNER_NUM; u32TunerPort++ )
    {
        if ( HI_NULL == g_stTunerOps[u32TunerPort].tuner_connect )
        {
            continue;
        }

        /* init proc variable */
        enTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
        strncpy(acTunerLock, "unlocked", sizeof( acTunerLock ) );
        acTunerLock[sizeof( acTunerLock ) - 1] = '\0';

        strncpy(acQamType, "QAM_INVALID ", sizeof( acQamType ) );
        acQamType[sizeof( acQamType ) - 1] = '\0';

        u32SNR = 0;
        u32Ber = 0;
        au32SignalStrength[2] = 0;
        au32SignalStrength[1] = 0;
        au32SignalStrength[0] = 0;

        strncpy(acTunerType, "unknown TUNER", sizeof( acTunerType ) );
        acTunerType[sizeof( acTunerType ) - 1] = '\0';
        strncpy(acDemodType, "unknown demod", sizeof( acDemodType ) );
        acDemodType[sizeof( acDemodType ) - 1] = '\0';

        /* get proc info */
        if (g_stTunerOps[u32TunerPort].tuner_get_status)
        {
            g_stTunerOps[u32TunerPort].tuner_get_status(u32TunerPort, &enTunerStatus);
        }

        if ( HI_UNF_TUNER_SIGNAL_LOCKED == enTunerStatus )
        {
            strncpy(acTunerLock, "locked", sizeof( acTunerLock ) );
            acTunerLock[sizeof( acTunerLock ) - 1] = '\0';

            if (g_stTunerOps[u32TunerPort].tuner_get_signal_info)
            {
                g_stTunerOps[u32TunerPort].tuner_get_signal_info(u32TunerPort, &stSignalInfo);
            }
        }

        if (g_stTunerOps[u32TunerPort].tuner_get_ber)
        {
            g_stTunerOps[u32TunerPort].tuner_get_ber(u32TunerPort, au32Tmp);
        }
        if (g_stTunerOps[u32TunerPort].tuner_get_snr)
        {
            g_stTunerOps[u32TunerPort].tuner_get_snr(u32TunerPort, &u32SNR);
        }
        if (g_stTunerOps[u32TunerPort].tuner_get_signal_strength)
        {
            g_stTunerOps[u32TunerPort].tuner_get_signal_strength(u32TunerPort, au32SignalStrength);
        }

        if (   (HI_UNF_DEMOD_DEV_TYPE_3130I == g_stTunerOps[u32TunerPort].enDemodDevType)
            || (HI_UNF_DEMOD_DEV_TYPE_3130E == g_stTunerOps[u32TunerPort].enDemodDevType)
            || (HI_UNF_DEMOD_DEV_TYPE_J83B  == g_stTunerOps[u32TunerPort].enDemodDevType) )
        {
            u32Ber = (au32Tmp[0] << 16 | au32Tmp[1] << 8 | au32Tmp[2]);
            u64TmpBer = (HI_U64)u32Ber;
            u32Ber = (HI_U32)((u64TmpBer / 8) * 10000000 / (1 << 20));
            au32Tmp[0] = u32Ber;
            au32Tmp[1] = 0;
            au32Tmp[2] = 7;
        }
        if (HI_UNF_DEMOD_DEV_TYPE_MXL254== g_stTunerOps[u32TunerPort].enDemodDevType)
        {
            u32SNR = u32SNR /10;
        }

		switch(stSignalInfo.enSigType)
		{
			case HI_UNF_TUNER_SIG_TYPE_CAB:
				strncpy(acSignalType, "DVBC ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_SAT:
				strncpy(acSignalType, "SAT ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_DVB_T:
				strncpy(acSignalType, "DVBT ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
				strncpy(acSignalType, "DVBT2 ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
				strncpy(acSignalType, "ISDBT ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
				strncpy(acSignalType, "ATSCT ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_DTMB:
				strncpy(acSignalType, "DTMB ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			case HI_UNF_TUNER_SIG_TYPE_J83B:
				strncpy(acSignalType, "J83B ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
			default:
				strncpy(acSignalType, "Unknow ", sizeof( acSignalType ) );
        		acSignalType[sizeof( acSignalType ) - 1] = '\0';
				break;
		}

        /* Modulate type */
        switch (g_stTunerOps[u32TunerPort].enDemodDevType)
        {
            case HI_UNF_DEMOD_DEV_TYPE_NONE:
            case HI_UNF_DEMOD_DEV_TYPE_BUTT:
            default:
                break;

            /* For cable */
            case HI_UNF_DEMOD_DEV_TYPE_3130I:
            case HI_UNF_DEMOD_DEV_TYPE_3130E:
            case HI_UNF_DEMOD_DEV_TYPE_J83B:
            case HI_UNF_DEMOD_DEV_TYPE_MXL254:
            case HI_UNF_DEMOD_DEV_TYPE_MXL214:
                switch(g_stTunerOps[u32TunerPort].stCurrPara.enQamType)
                {
                    case QAM_TYPE_16:
                        strncpy(acQamType, "QAM_16 ", sizeof( acQamType ) );
                        break;
                    case QAM_TYPE_32:
                        strncpy(acQamType, "QAM_32 ", sizeof( acQamType ) );
                        break;
                    case QAM_TYPE_64:
                        strncpy(acQamType, "QAM_64 ", sizeof( acQamType ) );
                        break;
                    case QAM_TYPE_128:
                        strncpy(acQamType, "QAM_128", sizeof( acQamType ) );
                        break;
                    case QAM_TYPE_256:
                        strncpy(acQamType, "QAM_256", sizeof( acQamType ) );
                        break;
                    default :
                        strncpy(acQamType, "QAM_INVALID ", sizeof( acQamType ) );
                }
                break;

            /* For satellite */
            case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
            case HI_UNF_DEMOD_DEV_TYPE_3136:
            case HI_UNF_DEMOD_DEV_TYPE_3136I:
                switch (stSignalInfo.unSignalInfo.stSat.enModType)
                {
                case HI_UNF_MOD_TYPE_QPSK:
                    strncpy(acQamType, "QPSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_8PSK:
                    strncpy(acQamType, "8PSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_16APSK:
                    strncpy(acQamType, "16APSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_32APSK:
                    strncpy(acQamType, "32APSK", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_DEFAULT:
                case HI_UNF_MOD_TYPE_QAM_16:
                case HI_UNF_MOD_TYPE_QAM_32:
                case HI_UNF_MOD_TYPE_QAM_64:
                case HI_UNF_MOD_TYPE_QAM_128:
                case HI_UNF_MOD_TYPE_QAM_256:
                case HI_UNF_MOD_TYPE_QAM_512:
                default:
                    strncpy(acQamType, "QAM_INVALID ", sizeof(acQamType));
                }
                break;
			case HI_UNF_DEMOD_DEV_TYPE_3137:
				switch (stSignalInfo.unSignalInfo.stTer.enModType)
				{
					case HI_UNF_MOD_TYPE_QPSK:
	                    strncpy(acQamType, "QPSK ", sizeof(acQamType));
	                    break;
	                case HI_UNF_MOD_TYPE_QAM_16:
	                    strncpy(acQamType, "QAM_16 ", sizeof(acQamType));
	                    break;
	                case HI_UNF_MOD_TYPE_QAM_64:
	                    strncpy(acQamType, "QAM_64 ", sizeof(acQamType));
	                    break; 
					case HI_UNF_MOD_TYPE_QAM_256:
	                    strncpy(acQamType, "QAM_256 ", sizeof(acQamType));
	                    break; 
					default:
                    	strncpy(acQamType, "QAM_INVALID ", sizeof(acQamType));
						break;
				}
				break;
            /*for terrestrial*/
            case HI_UNF_DEMOD_DEV_TYPE_MXL101:
                switch (stSignalInfo.unSignalInfo.stTer.enModType)
                {
                case HI_UNF_MOD_TYPE_QPSK:
                    strncpy(acQamType, "QPSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_16:
                    strncpy(acQamType, "QAM_16 ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_64:
                    strncpy(acQamType, "QAM_64 ", sizeof(acQamType));
                    break;
                default:
                    strncpy(acQamType, "QAM_INVALID ", sizeof(acQamType));
                }
                break;

            case HI_UNF_DEMOD_DEV_TYPE_MN88472:
                switch (stSignalInfo.unSignalInfo.stTer.enModType)
                {
                case HI_UNF_MOD_TYPE_QPSK:
                    strncpy(acQamType, "QPSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_16:
                    strncpy(acQamType, "QAM_16 ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_64:
                    strncpy(acQamType, "QAM_64 ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_256:
                    strncpy(acQamType, "QAM_256 ", sizeof(acQamType));
                    break;
                default:
                    strncpy(acQamType, "QAM_INVALID ", sizeof(acQamType));
                }
                break;

            case HI_UNF_DEMOD_DEV_TYPE_IT9170:
                switch (stSignalInfo.unSignalInfo.stTer.enModType)
                {
                case HI_UNF_MOD_TYPE_QPSK:
                    strncpy(acQamType, "QPSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_DQPSK:
                    strncpy(acQamType, "DQPSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_16:
                    strncpy(acQamType, "QAM_16 ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_64:
                    strncpy(acQamType, "QAM_64 ", sizeof(acQamType));
                    break;
                default:
                    strncpy(acQamType, "QAM_INVALID ", sizeof(acQamType));
                }
                break;

            case HI_UNF_DEMOD_DEV_TYPE_IT9133:
                switch (stSignalInfo.unSignalInfo.stTer.enModType)
                {
                case HI_UNF_MOD_TYPE_QPSK:
                    strncpy(acQamType, "QPSK ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_16:
                    strncpy(acQamType, "QAM_16 ", sizeof(acQamType));
                    break;
                case HI_UNF_MOD_TYPE_QAM_64:
                    strncpy(acQamType, "QAM_64 ", sizeof(acQamType));
                    break;
                default:
                    strncpy(acQamType, "QAM_INVALID ", sizeof(acQamType));
                }
                break;
        }
        acQamType[sizeof( acQamType ) - 1] = '\0';

        switch( g_stTunerOps[u32TunerPort].enDemodDevType )
        {
            case HI_UNF_DEMOD_DEV_TYPE_3130I:
                strncpy(acDemodType, "3130_inside", sizeof( acDemodType ) );
                break;

            case HI_UNF_DEMOD_DEV_TYPE_3130E:
                strncpy(acDemodType, "3130_outside", sizeof( acDemodType ) );
                break;
            case HI_UNF_DEMOD_DEV_TYPE_J83B:
                strncpy(acDemodType, "j83b", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
                strncpy(acDemodType, "avl6211", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_MXL101:
                strncpy(acDemodType, "mxl101", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_MN88472:
                strncpy(acDemodType, "mn88472", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_IT9170:
                strncpy(acDemodType, "it9170", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_IT9133:
                strncpy(acDemodType, "it9133", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_3136:
                strncpy(acDemodType, "hi3136e", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_3136I:
                strncpy(acDemodType, "hi3136i", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_CXD2837:
                strncpy(acDemodType, "cxd2837", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_3137:
                strncpy(acDemodType, "hi3137", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_MXL254:
                strncpy(acDemodType, "mxl254", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_MXL214:
                strncpy(acDemodType, "mxl214", sizeof(acDemodType));
                break;
            case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
                strncpy(acDemodType, "tda18280", sizeof(acDemodType));
                break;
            default:
                strncpy(acDemodType, "unknown demod", sizeof( acDemodType ) );
                break;
        }
        acDemodType[sizeof( acDemodType ) - 1] = '\0';

        switch(g_stTunerOps[u32TunerPort].enTunerDevType)
        {
            case HI_UNF_TUNER_DEV_TYPE_CD1616:
                strncpy(acTunerType, "CD1616", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_CD1616_DOUBLE:
                strncpy(acTunerType, "CD1616_DOUBLE", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_ALPS_TDAE:
                strncpy(acTunerType, "ALPS_TDAE", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_TDCC:
                strncpy(acTunerType, "TDCC", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_TDA18250:
                strncpy(acTunerType, "TDA18250", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_TDA18250B:
                strncpy(acTunerType, "TDA18250B", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_TMX7070X:
                strncpy(acTunerType, "TMX7070X", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_XG_3BL:
                strncpy(acTunerType, "XG_3BL", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_MT2081:
                strncpy(acTunerType, "MT2081", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_R820C:
                strncpy(acTunerType, "R820C", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_MXL203:
                strncpy(acTunerType, "MXL203", sizeof( acTunerType ) );
                break;
            case HI_UNF_TUNER_DEV_TYPE_AV2011:
                strncpy(acTunerType, "AV2011", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_AV2018:
                strncpy(acTunerType, "AV2018", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_SHARP7903:
                strncpy(acTunerType, "SHARP7903", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_M88TS2022:
                strncpy(acTunerType, "M88TS2022", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_RDA5815:
                strncpy(acTunerType, "RDA5815", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_MXL101:
                strncpy(acTunerType, "MXL101", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_MXL603:
                strncpy(acTunerType, "MXL603", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_IT9170:
                strncpy(acTunerType, "IT9170", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_IT9133:
                strncpy(acTunerType, "IT9133", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_TDA6651:
                strncpy(acTunerType, "TDA6651", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_MXL254:
                strncpy(acTunerType, "MXL254", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_MXL214:
                strncpy(acTunerType, "MXL214", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_CXD2861:
                strncpy(acTunerType, "cxd2861", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_SI2147:
                strncpy(acTunerType, "si2147", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_RAFAEL836:
                strncpy(acTunerType, "Rafael836", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_MXL608:
                strncpy(acTunerType, "MXL608", sizeof(acTunerType));
                break;
            case HI_UNF_TUNER_DEV_TYPE_TDA18280:
                strncpy(acTunerType, "TDA18280", sizeof(acTunerType));
                break;
			case HI_UNF_TUNER_DEV_TYPE_TDA182I5A:
				strncpy(acTunerType, "TDA182I5A", sizeof(acTunerType));
				break;
			case HI_UNF_TUNER_DEV_TYPE_SI2144:
				strncpy(acTunerType, "SI2144", sizeof(acTunerType));
				break;
            default :
                strncpy(acTunerType, "unknown TUNER", sizeof( acTunerType ) );
                break;
        }
        acTunerType[sizeof( acTunerType ) - 1] = '\0';

        PROC_PRINT(p,
                " %d:   %s     %5d   	%s    %8d   %13d	%7s    %s      0x%02x  %12s      0x%02x\n",
                u32TunerPort,
                acTunerLock,
                g_stTunerOps[u32TunerPort].enI2cChannel,
                acSignalType,
                g_stTunerOps[u32TunerPort].stCurrPara.u32Frequency,
                        g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32SymbolRate,
                acQamType,
                acDemodType,
                g_stTunerOps[u32TunerPort].u32DemodAddress,
                acTunerType,
                g_stTunerOps[u32TunerPort].u32TunerAddress
                );

        PROC_PRINT(p, "\nBER:%d.%d*(E-%d),  SNR:%d,  SignalStrength:%d\n", au32Tmp[0], au32Tmp[1], au32Tmp[2], u32SNR, au32SignalStrength[1]);

        if (g_stTunerOps[u32TunerPort].tuner_get_rs)
        {
            g_stTunerOps[u32TunerPort].tuner_get_rs(u32TunerPort, au32Rs);
            PROC_PRINT(p, "\nall_rs_package:%-d,  corrected_rs_package:%d,  error_rs_package:%d\n\n", au32Rs[0],
                       au32Rs[1], au32Rs[2]);
        }

        /* For DVB-S/S2, print FEC type and rate */
        if (HI_UNF_TUNER_SIG_TYPE_SAT == stSignalInfo.enSigType)
        {
            switch (stSignalInfo.unSignalInfo.stSat.enSATType)
            {
            case HI_UNF_TUNER_FE_DVBS:
                strncpy(acFECType, "DVBS", sizeof(acFECType));
                break;
            case HI_UNF_TUNER_FE_DVBS2:
                strncpy(acFECType, "DVBS2", sizeof(acFECType));
                break;
            case HI_UNF_TUNER_FE_DIRECTV:
                strncpy(acFECType, "DIRECTV", sizeof(acFECType));
                break;
            case HI_UNF_TUNER_FE_BUTT:
            default:
                strncpy(acFECType, "Unknown", sizeof(acFECType));
                break;
            }

            switch (stSignalInfo.unSignalInfo.stSat.enFECRate)
            {
            case HI_UNF_TUNER_FE_FEC_1_2:
                strncpy(acFECRate, "1/2", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_1_3:
                strncpy(acFECRate, "1/3", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_2_3:
                strncpy(acFECRate, "2/3", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_3_4:
                strncpy(acFECRate, "3/4", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_4_5:
                strncpy(acFECRate, "4/5", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_5_6:
                strncpy(acFECRate, "5/6", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_6_7:
                strncpy(acFECRate, "6/7", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_7_8:
                strncpy(acFECRate, "7/8", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_8_9:
                strncpy(acFECRate, "8/9", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_9_10:
                strncpy(acFECRate, "9/10", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_1_4:
                strncpy(acFECRate, "1/4", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_2_5:
                strncpy(acFECRate, "2/5", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_3_5:
                strncpy(acFECRate, "3/5", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FECRATE_BUTT:
            case HI_UNF_TUNER_FE_FEC_AUTO:
            default:
                strncpy(acFECRate, "AUTO", sizeof(acFECRate));
                break;
            }

            PROC_PRINT(p, "\nFEC type:%s,  FEC rate:%s\n", acFECType, acFECRate);

			if(HI_UNF_DEMOD_DEV_TYPE_3136 == g_stTunerOps[u32TunerPort].enDemodDevType)
			{
	            switch(stSignalInfo.unSignalInfo.stSat.enCodeModulation)
	            {
	                case HI_UNF_TUNER_CODE_MODULATION_VCM_ACM:
	                    strncpy(acCCMMode, "VCM/ACM", sizeof(acCCMMode));
	                    break;
	                case HI_UNF_TUNER_CODE_MODULATION_MULTISTREAM:
	                    strncpy(acCCMMode, "MultiStream", sizeof(acCCMMode));
	                    break;
	                case HI_UNF_TUNER_CODE_MODULATION_CCM:
	                default:
	                    strncpy(acCCMMode, "CCM", sizeof(acCCMMode));
	                    break;
	            }

	            p = PROC_PRINT(p, "\nCode and Modulation:%s\n", acCCMMode);
			}
        }

        /* For DVB-T/T2, print FEC type and rate */
        if (HI_UNF_TUNER_SIG_TYPE_DVB_T <= stSignalInfo.enSigType
            && HI_UNF_TUNER_SIG_TYPE_DTMB >= stSignalInfo.enSigType)
        {
            switch (stSignalInfo.unSignalInfo.stTer.enFECRate)
            {
            case HI_UNF_TUNER_FE_FEC_1_2:
                strncpy(acFECRate, "1/2", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_2_3:
                strncpy(acFECRate, "1/2", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_3_4:
                strncpy(acFECRate, "3/4", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_3_5:
                strncpy(acFECRate, "3/5", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_5_6:
                strncpy(acFECRate, "5/6", sizeof(acFECRate));
                break;
            case HI_UNF_TUNER_FE_FEC_7_8:
                strncpy(acFECRate, "7/8", sizeof(acFECRate));
                break;
            default:
                strncpy(acFECRate, "INVALID", sizeof(acFECRate));
                break;
            }

            switch (stSignalInfo.unSignalInfo.stTer.enFFTMode)
            {
            case HI_UNF_TUNER_FE_FFT_1K:
                strncpy(acFFTMode, "1K", sizeof(acFFTMode));
                break;
            case HI_UNF_TUNER_FE_FFT_2K:
                strncpy(acFFTMode, "2K", sizeof(acFFTMode));
                break;
            case HI_UNF_TUNER_FE_FFT_4K:
                strncpy(acFFTMode, "4K", sizeof(acFFTMode));
                break;
            case HI_UNF_TUNER_FE_FFT_8K:
                strncpy(acFFTMode, "8K", sizeof(acFFTMode));
                break;
            case HI_UNF_TUNER_FE_FFT_16K:
                strncpy(acFFTMode, "16K", sizeof(acFFTMode));
                break;
            case HI_UNF_TUNER_FE_FFT_32K:
                strncpy(acFFTMode, "32K", sizeof(acFFTMode));
                break;
            default:
                strncpy(acFFTMode, "INVALID", sizeof(acFFTMode));
                break;
            }

            switch (stSignalInfo.unSignalInfo.stTer.enGuardIntv)
            {
            case HI_UNF_TUNER_FE_GUARD_INTV_1_128:
                strncpy(acGI, "1/128", sizeof(acGI));
                break;
            case HI_UNF_TUNER_FE_GUARD_INTV_1_32:
                strncpy(acGI, "1/32", sizeof(acGI));
                break;
            case HI_UNF_TUNER_FE_GUARD_INTV_1_16:
                strncpy(acGI, "1/16", sizeof(acGI));
                break;
            case HI_UNF_TUNER_FE_GUARD_INTV_1_8:
                strncpy(acGI, "1/8", sizeof(acGI));
                break;
            case HI_UNF_TUNER_FE_GUARD_INTV_1_4:
                strncpy(acGI, "1/4", sizeof(acGI));
                break;
            case HI_UNF_TUNER_FE_GUARD_INTV_19_128:
                strncpy(acGI, "19/128", sizeof(acGI));
                break;
            case HI_UNF_TUNER_FE_GUARD_INTV_19_256:
                strncpy(acGI, "19/256", sizeof(acGI));
                break;
            default:
                strncpy(acGI, "INVALID", sizeof(acGI));
                break;
            }

            switch (stSignalInfo.unSignalInfo.stTer.enHierMod)
            {
            case HI_UNF_TUNER_FE_HIERARCHY_NO:
                strncpy(acHierAlpha, "NONE", sizeof(acHierAlpha));
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA1:
                strncpy(acHierAlpha, "alpha1", sizeof(acHierAlpha));
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA2:
                strncpy(acHierAlpha, "alpha2", sizeof(acHierAlpha));
                break;
            case HI_UNF_TUNER_FE_HIERARCHY_ALHPA4:
                strncpy(acHierAlpha, "alpha4", sizeof(acHierAlpha));
                break;
            default:
                strncpy(acHierAlpha, "INVALID", sizeof(acHierAlpha));
                break;
            }

            switch (stSignalInfo.unSignalInfo.stTer.enTsPriority)
            {
            case HI_UNF_TUNER_TS_PRIORITY_NONE:
                strncpy(acTSPrio, "NONE", sizeof(acTSPrio));
                break;
            case HI_UNF_TUNER_TS_PRIORITY_HP:
                strncpy(acTSPrio, "HP", sizeof(acTSPrio));
                break;
            case HI_UNF_TUNER_TS_PRIORITY_LP:
                strncpy(acTSPrio, "LP", sizeof(acTSPrio));
                break;
            default:
                strncpy(acTSPrio, "INVALID", sizeof(acTSPrio));
                break;
            }

            PROC_PRINT(p, "\nFEC rate:%s, FFT Mode:%s, GI: %s, HierMod: %s, TSPrio: %s\n", acFECRate, acFFTMode, acGI, acHierAlpha, acTSPrio);
        }
    }

    return HI_SUCCESS;
}

HI_S32 tuner_proc_read_diseqc(struct seq_file *p, HI_VOID *v)
{
	HI_U32 i,j,k = 0;
	HI_CHAR acMotorPosition[20];
	HI_CHAR acEastLimit[20];
	HI_CHAR acWestLimit[20];
	HI_CHAR acStorePos[MOTOR_STORE_POSITION_MAX_NUM][20];
	HI_CHAR acSwitchPort0[8];
	HI_CHAR acSwitchPort1[8];
	PROC_PRINT(p,"---------Hisilicon TUNER DiSEqC Info---------\n");
	PROC_PRINT(p,
	            "Port :Switch1.0    Switch1.1	MotorMoveStep	EastLimit	WestLimit\n");

	for(i = 0;i < TUNER_NUM;i++)
	{
		strncpy(acSwitchPort1, "none", sizeof( acSwitchPort1 ) );
		if((HI_UNF_TUNER_SIG_TYPE_SAT != g_stTunerOps[i].enSigType) || (HI_NULL == g_stTunerOps[i].tuner_DiSEqC_send_msg))
		{
			continue;
		}
		
		switch(s_stDiSEqCDrvStatus[i].stPort1_0.enPort)
		{
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_1:
				strncpy(acSwitchPort0, "Port1", sizeof( acSwitchPort0 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_2:
				strncpy(acSwitchPort0, "Port2", sizeof( acSwitchPort0 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_3:
				strncpy(acSwitchPort0, "Port3", sizeof( acSwitchPort0 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_4:
				strncpy(acSwitchPort0, "Port4", sizeof( acSwitchPort0 ) );
				break;
			default:
				strncpy(acSwitchPort0, "disable", sizeof( acSwitchPort0 ) );
				break;
		}

		switch(s_stDiSEqCDrvStatus[i].stPort1_1.enPort)
		{
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_1:
				strncpy(acSwitchPort1, "Port1", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_2:
				strncpy(acSwitchPort1, "Port2", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_3:
				strncpy(acSwitchPort1, "Port3", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_4:
				strncpy(acSwitchPort1, "Port4", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_5:
				strncpy(acSwitchPort1, "Port5", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_6:
				strncpy(acSwitchPort1, "Port6", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_7:
				strncpy(acSwitchPort1, "Port7", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_8:
				strncpy(acSwitchPort1, "Port8", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_9:
				strncpy(acSwitchPort1, "Port9", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_10:
				strncpy(acSwitchPort1, "Port10", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_11:
				strncpy(acSwitchPort1, "Port11", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_12:
				strncpy(acSwitchPort1, "Port12", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_13:
				strncpy(acSwitchPort1, "Port13", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_14:
				strncpy(acSwitchPort1, "Port14", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_15:
				strncpy(acSwitchPort1, "Port15", sizeof( acSwitchPort1 ) );
				break;
			case HI_UNF_TUNER_DISEQC_SWITCH_PORT_16:
				strncpy(acSwitchPort1, "Port16", sizeof( acSwitchPort1 ) );
				break;
			default:
				strncpy(acSwitchPort1, "disable", sizeof( acSwitchPort1 ) );
				break;
		}
		snprintf(acMotorPosition,sizeof(acMotorPosition),"%d step",s_stDiSEqCDrvStatus[i].s16MotorPos);
		if(s_stDiSEqCDrvStatus[i].s16EastLimit)
		{  
                strncpy(acEastLimit, "enable", sizeof( acEastLimit ) );
		}
		else
		{
                strncpy(acEastLimit, "disable", sizeof( acEastLimit ) );
		}

		if(s_stDiSEqCDrvStatus[i].s16WestLimit)
		{
                strncpy(acWestLimit, "enable", sizeof( acWestLimit ) );
             }
		else
		{
                strncpy(acWestLimit, "disable", sizeof( acWestLimit ) );
		}

		PROC_PRINT(p,
	            "%4d  %9s    %9s	%13s	%9s	%9s\n\n",i,acSwitchPort0,acSwitchPort1,acMotorPosition,acEastLimit,acWestLimit);

		k = 0;
		for(j = 0;j < MOTOR_STORE_POSITION_MAX_NUM;j++)
		{
		       if (j <= 31)
                    {      
                        if (s_stDiSEqCDrvStatus[i].stMotorFlag.u32Flags[0] & (1 << j))
                        {
                            snprintf(acStorePos[k],20,"Pos%d ",j+1);
                            k++;
                            if (0 == (k % 4))
                            {
                                PROC_PRINT(p,"%s	%s	%s	%s\n",acStorePos[k-4],acStorePos[k-3],acStorePos[k-2],acStorePos[k-1]);
                            }
                        }
                    }
                    else
                    {
                        if (s_stDiSEqCDrvStatus[i].stMotorFlag.u32Flags[1] & (1 << (j - 32)))
                        {
                            snprintf(acStorePos[k],20,"Pos%d ",j+1);
                            k++;
                            if (0 == (k % 4))
                            {
                                PROC_PRINT(p,"%s	%s	%s	%s\n",acStorePos[k-4],acStorePos[k-3],acStorePos[k-2],acStorePos[k-1]);
                            }
                        }                    
                    }
                    if ((j == MOTOR_STORE_POSITION_MAX_NUM - 1) && (k % 4))
                    {
                    	if (0 == ((k-1)%4))
                    	{
                    		PROC_PRINT(p,"%s\n",acStorePos[k-1]);
                    	}
                    	else if (0 == ((k-2)%4))
                    	{
                    		PROC_PRINT(p,"%s	%s\n",acStorePos[k-2],acStorePos[k-1]);
                    	}
                    	else
                    	{
                    		PROC_PRINT(p,"%s	%s	%s\n",acStorePos[k-3],acStorePos[k-2],acStorePos[k-1]);
                    	}
                    }
		}
	}

	return HI_SUCCESS;
}

#if defined (CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)
/*RAM_SIZE * 32BIT*/
#define  RAM_SIZE  8192

HI_VOID  PsisiPrintBuf(HI_U8* pu8Buf, HI_U32 u32Len)
{
    struct file *file_filp = NULL;
    mm_segment_t old_fs;

    if(file_filp== NULL)
    {
        file_filp = filp_open("collect_data.bin", O_RDWR | O_CREAT, 0644);
    }
    if((file_filp== NULL) ||(IS_ERR(file_filp)))
    {
        HI_ERR_TUNER("error occured while opening file collect_data.bin, exiting...\n");
        return;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    file_filp->f_op->write(file_filp, (char *)pu8Buf, u32Len, &file_filp->f_pos);
    set_fs(old_fs);
    HI_INFO_TUNER("file is closing !\n");
   // if(file_filp != NULL)
    //{
        filp_close(file_filp, NULL);
        file_filp= NULL;
    //}
     HI_INFO_TUNER("file end !\n");
     return;
}

HI_S32 qam_ram_collect_data(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
    HI_U8 u8RegVal = 0;
    HI_U32 u32DataType = 0;
    HI_U32 u32Flag = 0;
    HI_CHAR string[64] = {0};
    HI_PCHAR p   = NULL;
    HI_PCHAR pcDataBuf = NULL;
    HI_S32 s32Ret = HI_SUCCESS;

    if (0 == count)
    {
        return -EINVAL;
    }

    if (count >= sizeof(string))
    {
        return -E2BIG;
    }

    if (copy_from_user(string, buf, count - 1))
    {
        return -EFAULT;
    }

    p = string;

    pcDataBuf = (HI_PCHAR)kmalloc(sizeof(char)*RAM_SIZE*4,GFP_KERNEL);
    if(NULL == pcDataBuf)
    {
        HI_ERR_TUNER("kmalloc failed\n");

        return HI_FAILURE;
    }

    u32Flag = (HI_U32)simple_strtoul(p, &p, 10);
    u32DataType = (HI_U32)simple_strtoul(p+1, &p, 10);

    HI_INFO_TUNER("count = %d\n,u32Flag = %d\n, u32DataType = %d\n",count, u32Flag, u32DataType);

    /*collect data type*/
    if((4 == count || 3 == count))
    {
        //disable auto_reset
        qam_write_bit(s_u32InsideQamPort, MCTRL_6_ADDR, 6, 0); /*disable*/
        switch(u32DataType)
        {
            case(0):
            {
                HI_INFO_TUNER("TR loop filter output data\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = u8RegVal & (~(0x7 << 4));
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(1):
            {
                HI_INFO_TUNER("CR loop filter output data\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x1 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(2):
            {
                HI_INFO_TUNER("CR status data\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x2 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(3):
            {
                HI_INFO_TUNER("CR PED data\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x3 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(4):
            {
                HI_INFO_TUNER("before hard judge,after filter phase\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x4 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(5):
            {
                HI_INFO_TUNER("DFE and FFE data\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x5 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(6):
            {
                HI_INFO_TUNER("MF data\n");
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x6 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            case(7):
            {
                qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
                u8RegVal = (u8RegVal & (~(0x7 << 4))) | (0x7 << 4);
                qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
                break;
            }
            default:
            {
                HI_INFO_TUNER("collect data type error\n");
                break;
            }
        }

        /*write enable*/
        qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, &u8RegVal);
        /*select RAM collect data*/
        if(1 == u32Flag)
        {
            HI_INFO_TUNER("u32Flag = %d\n", u32Flag);
            u8RegVal = u8RegVal | (1 << 5) ;
        }
        else if(0 == u32Flag)
        {
            u8RegVal = u8RegVal & ( ~(1 << 5)) ;
        }
        else
        {
            HI_INFO_TUNER("select reg2ram_j83b_sel error\n");
        }
        /*disable ram read*/
        u8RegVal = u8RegVal & (~(1 << 6));
        /*enable ram write*/
        u8RegVal = u8RegVal & (~(1 << 7));
        qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, u8RegVal);
        qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, &u8RegVal);
        u8RegVal = u8RegVal | (1 << 7);
        qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, u8RegVal);
     //enable autoreset
        qam_write_bit(s_u32InsideQamPort, MCTRL_6_ADDR, 6, 1);
    }

    /*read stauts*/
    else if(1 == count)
    {
        //disable autoreset
        qam_write_bit(s_u32InsideQamPort, MCTRL_6_ADDR, 6, 0);
        qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
        HI_INFO_TUNER("*************read stauts = 0x%x\n",u8RegVal);
        if(u8RegVal & 0x1)
        {
            HI_INFO_TUNER("reading RAM\n");
            qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, &u8RegVal);
            u8RegVal = u8RegVal | (0x1 << 6);
            qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, u8RegVal);


            if(HI_STD_I2C_NUM >g_stTunerOps[s_u32InsideQamPort].enI2cChannel)
            {
                s32Ret = s_tuner_pI2cFunc->pfnI2cRead(g_stTunerOps[s_u32InsideQamPort].enI2cChannel,
                     g_stTunerOps[s_u32InsideQamPort].u32DemodAddress, 0x00, 1, pcDataBuf, RAM_SIZE*4);
                if(HI_SUCCESS != s32Ret)
                {
                     kfree(pcDataBuf);
                     pcDataBuf = NULL;
                     return s32Ret;
                }
            }
            else
            {
                s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(g_stTunerOps[s_u32InsideQamPort].enI2cChannel,
                     g_stTunerOps[s_u32InsideQamPort].u32DemodAddress, 0x00, 1, pcDataBuf, RAM_SIZE*4);
                if(HI_SUCCESS != s32Ret)
                {
                     kfree(pcDataBuf);
                     pcDataBuf = NULL;
                     return s32Ret;
                }
            }

            if(HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("HI_I2C_Read fail\n");
                kfree(pcDataBuf);
                pcDataBuf = NULL;
          //enable autoreset
                qam_write_bit(s_u32InsideQamPort, MCTRL_6_ADDR, 6, 1);

                return HI_FAILURE;
            }


            /*clean read flag and select RAM flag*/
            qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, &u8RegVal);
            u8RegVal = u8RegVal & (~(0x7 << 5));
            qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_0_ADDR, u8RegVal);
            qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
            u8RegVal = u8RegVal & (~0x1);
            qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);

            /*save data to file*/
            PsisiPrintBuf(pcDataBuf, RAM_SIZE*4);
        }
        else
        {
            HI_WARN_TUNER("status 0\n");
        }

     //enable autoreset
        qam_write_bit(s_u32InsideQamPort, MCTRL_6_ADDR, 6, 1);
    }

    /*force to write read status*/
    else if(2 == count)
    {
        qam_read_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, &u8RegVal);
        u8RegVal = u8RegVal | 0x1;
        qam_write_byte(s_u32InsideQamPort, DATA_COLLECT_1_ADDR, u8RegVal);
    }
    else
    {
        HI_ERR_TUNER("parameter error\n");
    }
    kfree(pcDataBuf);
    pcDataBuf = NULL;
    return count;
}

//ADC COLLECT
#define TUNER_FILE_NAME_LEN   (256)

#define HI_QTC_BASE                     IO_ADDRESS(0xF8A60000)
#define QTC_WRITE_REG(offset, value)    (*(volatile HI_U32*)((HI_U32)(HI_QTC_BASE) + (offset)) = (value))
#define QTC_READ_REG(offset)            (*(volatile HI_U32*)((HI_U32)(HI_QTC_BASE) + (offset)))


static struct semaphore s_qtcSemaphore;

HI_S32 adc_collect_data(struct file * file, const char __user * buf, size_t count, loff_t *ppos)
{
    HI_U32 u32RegVal = 0;
    HI_U32 u32BufSize = 0;
    HI_U32 u32TunerPort = 0;
    HI_CHAR string[64] = {0};
    HI_PCHAR p   = NULL;

    HI_S32 s32Ret = HI_SUCCESS;
    HI_S32                  s32WriteLen = 0;
    HI_U32                  u32loop = 0;
    HI_CHAR                 FileName[TUNER_FILE_NAME_LEN] = {0};
    MMZ_BUFFER_S            MmzBuf;
    static struct file         *TunerADCHandle  = HI_NULL;
    struct tm now;
    U_PERI_CRG56    unTmpPeriCrg56;

    if (0 == count)
    {
        return -EINVAL;
    }

    if (count >= sizeof(string))
    {
        return -E2BIG;
    }

    if (copy_from_user(string, buf, count - 1))
    {
        return -EFAULT;
    }

    p = string;

    u32TunerPort = (HI_U32)simple_strtoul(p, &p, 10);
    u32BufSize = (HI_U32)simple_strtoul(p+1, &p, 10);

    if (u32TunerPort >= TUNER_NUM)
    {
        HI_ERR_TUNER("The Tuner Port id is error[%d]!\n", u32TunerPort);

        return HI_FAILURE;
    }

    if ((u32BufSize <= 0) || (u32BufSize >= 100))
    {
        HI_ERR_TUNER("The buffer size is error!\n");

        return HI_FAILURE;
    }

    HI_INFO_TUNER("TunerPort=%d, BufSize=%d\n", u32TunerPort, u32BufSize);

    if (HI_SUCCESS != HI_DRV_MMZ_AllocAndMap("tuner_adcbuf", MMZ_OTHERS, u32BufSize * 1024 * 1024, 0, &MmzBuf))
    {
        HI_ERR_TUNER("memory allocate failed\n");

        return HI_ERR_TUNER_FAILED_ALLOC_MEM;
    }

    /*collect start */

    /* QAM ADC CLK OPEN,*/
    unTmpPeriCrg56.u32 = g_pstRegCrg->PERI_CRG56.u32;
    unTmpPeriCrg56.bits.qtc_clk_pctrl = 0x0;
    unTmpPeriCrg56.bits.qtc_srst_req=  0x00;

    unTmpPeriCrg56.bits.qtc_bus_cken =  0x01;
    unTmpPeriCrg56.bits.qtc_cken =  0x01;
    g_pstRegCrg->PERI_CRG56.u32 = unTmpPeriCrg56.u32;

    /*buf addr*/
    QTC_WRITE_REG(0x48,MmzBuf.u32StartPhyAddr);
    QTC_WRITE_REG(0x4C,MmzBuf.u32StartPhyAddr + u32BufSize * 1024 * 1024);

    u32RegVal = QTC_READ_REG(0x48);
    u32RegVal = QTC_READ_REG(0x4c);
    QTC_WRITE_REG(0x40,0x43);
    u32RegVal = QTC_READ_REG(0x40);
    u32loop = 0;
    do
    {
       u32loop ++;
       u32RegVal = QTC_READ_REG(0x44);
       if(u32loop > (100 * u32BufSize ))
       {
          HI_ERR_TUNER("qtc time is too long\n");
          //goto exit;
          HI_DRV_MMZ_UnmapAndRelease(&MmzBuf);

          return HI_FAILURE;
       }
       msleep(10);

    }while(!(u32RegVal&0x1));

    // file

    // HI_DRV_MMZ_UnmapAndRelease(&MmzBuf);

    s32Ret = HI_DRV_FILE_GetStorePath(FileName, TUNER_FILE_NAME_LEN);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("get path failed\n");
        goto exit;
    }

    if (HI_NULL != TunerADCHandle)
    {
        HI_ERR_TUNER("already started\n");
        goto exit;
    }
    time_to_tm(get_seconds(), 0, &now);
    snprintf(FileName, sizeof(FileName),"%s/qtc_%u-%02u_%02u_%02u.bin", FileName, u32TunerPort, now.tm_hour, now.tm_min, now.tm_sec);

    sema_init(&s_qtcSemaphore, 1);

    for(u32loop = 0;u32loop < u32BufSize *4*64;u32loop++ )
    {
        TunerADCHandle = HI_DRV_FILE_Open(FileName, 1);
        if (!TunerADCHandle)
        {
            HI_ERR_TUNER("open %s error\n", FileName);
            goto exit;
        }
       s32WriteLen = HI_DRV_FILE_Write(TunerADCHandle, (HI_S8*)MmzBuf.u32StartVirAddr+(u32loop*4*1024), 4 * 1024);
       if(s32WriteLen != 4 * 1024)
       {
           HI_ERR_TUNER(" Write file error[%s]\n", FileName);

           goto exit;
       }
        if(TunerADCHandle)
        {
           HI_DRV_FILE_Close(TunerADCHandle);
           TunerADCHandle = HI_NULL;
        }
    }

    HI_DRV_MMZ_UnmapAndRelease(&MmzBuf);

    return count;

exit:
    HI_DRV_MMZ_UnmapAndRelease(&MmzBuf);

    return HI_FAILURE;
}

#endif

HI_S32 hi_tuner_open(struct inode *inode, struct file *filp)
{
    HI_S32    Ret = 0;
    Ret =down_interruptible(&g_TunerMutex);
    if (atomic_inc_return(&s_atomicTunerAvailble) == 1)
    {
        tuner_enable_crg();
        tuner_enable_adc();
        Ret = tuner_geti2cFunc();
        if (HI_SUCCESS != Ret)
        {
            HI_ERR_TUNER("tuner_geti2cFunc err\n");
            //return HI_FAILURE;
        }
    }

    up(&g_TunerMutex);
    return Ret;
}

HI_S32 hi_tuner_release(struct inode *inode, struct file *filp)
{

   HI_S32    Ret = 0;
   Ret =down_interruptible(&g_TunerMutex);

   if (atomic_dec_return(&s_atomicTunerAvailble) == 0)
   {

       tuner_disable_crg();
       tuner_disable_adc();
   }
    up(&g_TunerMutex);

    return HI_SUCCESS;
}

HI_VOID reset_special_process_flag(HI_BOOL flag)
{
    g_bLockFlag = flag;
    return;
}

HI_S32 x5hdqam_special_process(void * arg)
{
    HI_U8 u8LockRegVal = 0;
    HI_U32 u32TunerPort = 0;

    while (!kthread_should_stop())
    {
        wait_event_interruptible_timeout( g_QamSpecialProcessWQ, g_bLockFlag, msecs_to_jiffies( 100 ) );

        if ( g_bLockFlag )
        {
            msleep_interruptible( 150 );

            qam_read_byte(s_u32InsideQamPort, MCTRL_11_ADDR, &u8LockRegVal);
            if ( 0xf8 != u8LockRegVal )
            {
                if ( QAM_TYPE_256 == g_stTunerOps[u32TunerPort].u32CurrQamMode )
                {
                    qam_write_byte(s_u32InsideQamPort, EQU_CTRL_3_ADDR, 0x45);
                }

                /* reset eq */
                qam_write_byte(s_u32InsideQamPort, MCTRL_1_ADDR, 0x08);
                qam_write_byte(s_u32InsideQamPort, MCTRL_1_ADDR, 0x00);

                qam_write_byte(s_u32InsideQamPort, DEPHASE_CTRL_ADDR, 0x0b);

            }
            else
            {
                if ( QAM_TYPE_256 == g_stTunerOps[u32TunerPort].u32CurrQamMode )
                {
                    qam_write_byte(s_u32InsideQamPort, EQU_CTRL_3_ADDR, 0x33);
                }
                qam_write_byte(s_u32InsideQamPort, DEPHASE_CTRL_ADDR, 0x0b);
                g_bLockFlag = HI_FALSE;
            }
        }
    }

    return 0;
}

#define TUNER_NAME  "HI_TUNER"

static TUNER_EXPORT_FUNC_S s_TunerExportFuncs =
{
    .pfnTunerSuspend    = tuner_suspend,
    .pfnTunerResume     = tuner_resume
};

HI_S32 HI_DRV_TUNER_Init(HI_VOID)
{
    HI_S32  ret;
    HI_U32  i;

    ret = HI_DRV_MODULE_Register(HI_ID_TUNER, TUNER_NAME, (HI_VOID*)&s_TunerExportFuncs);
    if (HI_SUCCESS != ret)
    {
        HI_FATAL_TUNER("HI_DRV_MODULE_Register failed\n");

        return ret;
    }

   // tuner_enable_crg();

    g_stTunerOps[0].u32TunerAddress = TUNER_PORT0_ADDR;
    g_stTunerOps[1].u32TunerAddress = TUNER_PORT1_ADDR;
    g_stTunerOps[2].u32TunerAddress = TUNER_PORT2_ADDR;
    g_stTunerOps[3].u32TunerAddress = TUNER_PORT3_ADDR;
    g_stTunerOps[4].u32TunerAddress = TUNER_PORT4_ADDR;

    g_stTunerOps[0].u32DemodAddress = QAM_PORT0_ADDR;
    g_stTunerOps[1].u32DemodAddress = QAM_PORT1_ADDR;
    g_stTunerOps[2].u32DemodAddress = QAM_PORT2_ADDR;
    g_stTunerOps[3].u32DemodAddress = QAM_PORT3_ADDR;
    g_stTunerOps[4].u32DemodAddress = QAM_PORT4_ADDR;
    /* init all tuner ops as none operation */
    for (i = 0; i < TUNER_NUM; i++)
    {
        g_stTunerOps[i].u32XtalClk = XTAL_CLK;
        g_stTunerOps[i].u32CurrQamMode = QAM_TYPE_64;
        g_stTunerOps[i].u8AdcType = QAM_AD_INSIDE;
        g_stTunerOps[i].u8AgcOutputSel = QAM_AGC_CMOS_OUTPUT;
        g_stTunerOps[i].u8AdcDataFmt = 1;
        g_stTunerOps[i].enTsType = HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A;

        g_stTunerOps[i].tuner_connect = NULL;
        g_stTunerOps[i].tuner_get_status = NULL;
        g_stTunerOps[i].tuner_get_ber = NULL;
        g_stTunerOps[i].tuner_get_snr = NULL;
        g_stTunerOps[i].tuner_get_signal_strength = NULL;
        g_stTunerOps[i].tuner_get_snr = NULL;
        g_stTunerOps[i].tuner_set_ts_type = NULL;
        g_stTunerOps[i].set_tuner   = NULL;
        g_stTunerOps[i].tuner_test_single_agc = NULL;
        g_stTunerOps[i].enI2cChannel = i;
        g_stTunerOps[i].tuner_resume = NULL;
        g_stTunerOps[i].tuner_get_rs = NULL;
        g_stTunerOps[i].tuner_get_registers = NULL;
        g_stTunerOps[i].tuner_connect_timeout = NULL;

        /* Added begin:l00185424 2011-11-28 For DVB-S/S2 */
        g_stTunerOps[i].tuner_init = NULL;
        g_stTunerOps[i].tuner_set_sat_attr = NULL;
        g_stTunerOps[i].tuner_get_signal_info = NULL;
        g_stTunerOps[i].tuner_blindscan_init   = NULL;
        g_stTunerOps[i].tuner_blindscan_action = NULL;
        g_stTunerOps[i].tuner_lnbctrl_dev_init = NULL;
        g_stTunerOps[i].tuner_lnbctrl_dev_standby = NULL;
        g_stTunerOps[i].tuner_set_lnb_out = NULL;
        g_stTunerOps[i].tuner_send_continuous_22K = NULL;
        g_stTunerOps[i].tuner_send_tone = NULL;
        g_stTunerOps[i].tuner_DiSEqC_send_msg = NULL;
        g_stTunerOps[i].tuner_DiSEqC_recv_msg = NULL;
        g_stTunerOps[i].tuner_setfuncmode = NULL;
        g_stTunerOps[i].tuner_setplpid = NULL;
        g_stTunerOps[i].tuner_standby = NULL;
        g_stTunerOps[i].tuner_tp_verify = NULL;
        g_stTunerOps[i].tuner_set_ts_out = NULL;
        g_stTunerOps[i].tuner_data_sample = NULL;
        /* Added end:l00185424 2011-11-28 For DVB-S/S2 */

        s_stSatTunerResumeInfo[i].bSetTsOut = HI_FALSE;
    }

    init_waitqueue_head(&g_QamSpecialProcessWQ);
    pThread = kthread_create(x5hdqam_special_process, NULL, "x5hdqam_sop");
    wake_up_process(pThread);

    return HI_SUCCESS;
}

HI_VOID  HI_DRV_TUNER_DeInit(HI_VOID)
{
    kthread_stop(pThread);

    return;
}

/*
 * config to decide if i2c can be switch to control tuner
 */
HI_VOID qam_config_i2c_out(HI_U32 u32TunerPort, HI_BOOL bTuner)
{
    if (bTuner)
    {
        (HI_VOID)qam_write_bit(u32TunerPort, MCTRL_7_ADDR, 7, 1); /*set I2C_repeater_en 1*/
    }
}


HI_S32 tuner_i2c_receive_data(HI_U32 u32I2cChannel, HI_U8 u8DevAddress, PTR_TUNER_I2C_DATA_S pstDataStruct)
{
    HI_U32  u32I2cNo = 0;
    HI_U32  u32DevAddr = 0;
    HI_U32  u32RegAddr = 0;
    HI_U32  u32RegNum = 0;
    HI_U32  u32DataLen = 0;
    HI_U8   *pu8Data = NULL;
    HI_S32  s32Ret = HI_SUCCESS;

    u32I2cNo = u32I2cChannel;
    if (HI_I2C_MAX_NUM_USER < u32I2cNo)
    {
        return HI_FAILURE;
    }

    u32DevAddr = u8DevAddress;
	
	if(pstDataStruct->u32SendLength == 2)
		u32RegAddr = (pstDataStruct->pu8SendBuf[0]<<8)+pstDataStruct->pu8SendBuf[1];
	else if(pstDataStruct->u32SendLength == 3)
		u32RegAddr = (pstDataStruct->pu8SendBuf[0]<<16)+(pstDataStruct->pu8SendBuf[1]<<8)+pstDataStruct->pu8SendBuf[2];
	else if(pstDataStruct->u32SendLength == 4)
		u32RegAddr = (pstDataStruct->pu8SendBuf[0]<<24)+(pstDataStruct->pu8SendBuf[1]<<16)+(pstDataStruct->pu8SendBuf[2]<<8)+pstDataStruct->pu8SendBuf[3];
	else
    	u32RegAddr = *(pstDataStruct->pu8SendBuf);
    
	u32RegNum = pstDataStruct->u32SendLength;

    u32DataLen = pstDataStruct->u32ReceiveLength;
    pu8Data = pstDataStruct->pu8ReceiveBuf;
#if defined (CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)
    if(HI_STD_I2C_NUM > u32I2cNo)
    {
        //s32Ret = HI_DRV_I2C_Read(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        s32Ret = s_tuner_pI2cFunc->pfnI2cRead(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);

        if(HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
    }
    else
    {
        //s32Ret = HI_DRV_GPIOI2C_ReadExt(u32I2cNo, (HI_U8)u32DevAddr, (HI_U8)u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        s32Ret =  s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        if(HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
    }
#else
    if(HI_STD_I2C_NUM > u32I2cNo)
    {
        //s32Ret = HI_DRV_I2C_Read(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        s32Ret = s_tuner_pI2cFunc->pfnI2cRead(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        if(HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
    }
    else
    {
        //s32Ret = HI_DRV_GPIOI2C_ReadExt(u32I2cNo, (HI_U8)u32DevAddr, (HI_U8)u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        s32Ret =  s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
        if(HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
    }
#endif

    return HI_SUCCESS;
}



HI_S32 tuner_i2c_receive_data_si(HI_U32 u32I2cChannel, HI_U8 u8DevAddress, PTR_TUNER_I2C_DATA_S pstDataStruct)
{
    HI_U32  u32I2cNo = 0;
    HI_U32  u32DevAddr = 0;
    HI_U32  u32RegAddr = 0;
    HI_U32  u32RegNum = 0;
    HI_U32  u32DataLen = 0;
    HI_U8   *pu8Data = NULL;
    HI_S32  s32Ret = HI_SUCCESS;

    u32I2cNo = u32I2cChannel;
    if (HI_I2C_MAX_NUM_USER < u32I2cNo)
    {
        return HI_FAILURE;
    }

    u32DevAddr = u8DevAddress;
    u32RegAddr = *(pstDataStruct->pu8SendBuf);
    u32RegNum = pstDataStruct->u32SendLength;

    u32DataLen = pstDataStruct->u32ReceiveLength;
    pu8Data = pstDataStruct->pu8ReceiveBuf;
	
	if(HI_STD_I2C_NUM > u32I2cNo)
	{
		//s32Ret = HI_DRV_I2C_Read(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
		s32Ret = HI_DRV_I2C_Read_SiLabs(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);

		if(HI_SUCCESS != s32Ret)
		{
			return s32Ret;
		}
	}
	else
	{
		//s32Ret = HI_DRV_GPIOI2C_ReadExt(u32I2cNo, (HI_U8)u32DevAddr, (HI_U8)u32RegAddr, u32RegNum, pu8Data, u32DataLen);
		s32Ret =  s_tuner_pGpioI2cFunc->pfnGpioI2cReadExt(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pu8Data, u32DataLen);
		if(HI_SUCCESS != s32Ret)
		{
			return s32Ret;
		}
	}

    return HI_SUCCESS;
}

HI_S32 qam_read_byte(HI_U32 u32TunerPort, HI_U8 u8RegAddr, HI_U8 *pu8RegVal)
{
    TUNER_I2C_DATA_S stI2cDataStr = {0};
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 au8ReceData[1] = {0};
    HI_U8 au8SendData[1] = {0};

    if (HI_NULL == pu8RegVal)
    {
        HI_ERR_TUNER("pointer is null\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (u32TunerPort >= TUNER_NUM)
    {
       HI_ERR_TUNER("invalid parameter TunerPort:%d\n", u32TunerPort);
       return HI_FAILURE;
    }

    au8SendData[0] = u8RegAddr;

    stI2cDataStr.pu8ReceiveBuf      = au8ReceData;
    stI2cDataStr.u32ReceiveLength   = 1;
    stI2cDataStr.pu8SendBuf         = au8SendData;
    stI2cDataStr.u32SendLength      = 1;

    if (HI_UNF_DEMOD_DEV_TYPE_3136I == g_stTunerOps[u32TunerPort].enDemodDevType)
    {
        //printk("%s, %d, HI3136I_I2C_CHAN = %d, %x\n", __func__, __LINE__, HI3136I_I2C_CHAN, g_stTunerOps[u32TunerPort].u32DemodAddress);
        s32Ret = tuner_i2c_receive_data(HI3136I_I2C_CHAN,
            g_stTunerOps[u32TunerPort].u32DemodAddress, &stI2cDataStr);
    }
    else
    {
        s32Ret = tuner_i2c_receive_data(g_stTunerOps[u32TunerPort].enI2cChannel,
            g_stTunerOps[u32TunerPort].u32DemodAddress, &stI2cDataStr);
    }
    if (HI_SUCCESS == s32Ret)
    {
        *pu8RegVal = au8ReceData[0];
    }

    return s32Ret;
}

HI_S32 qam_read_bit(HI_U32 u32TunerPort, HI_U8 u8RegAddr, HI_U8 u8BitNum, HI_U8 *pu8BitVal)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8  u8Tmp = 0;

    if (HI_NULL == pu8BitVal)
    {
        HI_INFO_TUNER( "pointer(pu8BitVal) is null\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Ret = qam_read_byte(u32TunerPort, u8RegAddr, &u8Tmp);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if ((1 << u8BitNum) == (u8Tmp & (1 << u8BitNum)))
    {
        *pu8BitVal = 1;
    }
    else
    {
        *pu8BitVal = 0;
    }

    return HI_SUCCESS;
}


HI_S32 tuner_i2c_send_data(HI_U32 u32I2cChannel, HI_U8 u8DevAddress, PTR_TUNER_I2C_DATA_S pstDataStruct)
{
    HI_U32  u32I2cNo = 0;
    HI_U32  u32DevAddr = 0;
    HI_U32  u32RegAddr = 0;
    HI_U32  u32DataLen = 0;
    HI_U32  u32RegNum = 0;
    HI_U8   *pData = NULL;
    HI_S32  s32Ret = HI_SUCCESS;

    u32I2cNo = u32I2cChannel;
    if (HI_I2C_MAX_NUM_USER < u32I2cNo)
    {
        return HI_FAILURE;
    }

    u32DevAddr = u8DevAddress;
    u32RegAddr = *(pstDataStruct->pu8SendBuf);
    u32RegNum  = 1;

    pData      = pstDataStruct->pu8SendBuf + 1;
    u32DataLen = pstDataStruct->u32SendLength - 1;

    if (u32I2cNo < HI_STD_I2C_NUM)
    {
        s32Ret = s_tuner_pI2cFunc->pfnI2cWrite(u32I2cNo, (HI_U8)u32DevAddr, u32RegAddr, u32RegNum, pData, u32DataLen);
    }
    else
    {
        s32Ret = s_tuner_pGpioI2cFunc->pfnGpioI2cWriteExt(u32I2cNo,(HI_U8)u32DevAddr, (HI_U8)u32RegAddr, u32RegNum, pData, u32DataLen);
    }

    return s32Ret;
}

HI_VOID tuner_mdelay(HI_U32 u32MS)
{
    ktime_t wait;
    HI_U64 u64ns;
    u64ns = (HI_U64)u32MS * 1000000;

    wait = ns_to_ktime(u64ns);//ns
    set_current_state(TASK_UNINTERRUPTIBLE);
    schedule_hrtimeout(&wait, HRTIMER_MODE_REL);
}

HI_S32 qam_write_byte(HI_U32 u32TunerPort, HI_U8 u8RegAddr, HI_U8 u8RegVal)
{
    TUNER_I2C_DATA_S stI2cDataStr = {0};
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8 au8SendData[2] = {0};

    if (u32TunerPort >= TUNER_NUM)
    {
       HI_ERR_TUNER("invalid parameter TunerPort:%d\n", u32TunerPort);
       return HI_FAILURE;
    }

    au8SendData[0] = u8RegAddr;
    au8SendData[1] = u8RegVal;

    stI2cDataStr.pu8ReceiveBuf = HI_NULL;
    stI2cDataStr.u32ReceiveLength = 0;
    stI2cDataStr.pu8SendBuf = au8SendData;
    stI2cDataStr.u32SendLength = 2;

    if (HI_UNF_DEMOD_DEV_TYPE_3136I == g_stTunerOps[u32TunerPort].enDemodDevType)
    {
        //printk("%s, %d, HI3136I_I2C_CHAN = %d, %x\n", __func__, __LINE__, HI3136I_I2C_CHAN, g_stTunerOps[u32TunerPort].u32DemodAddress);
        s32Ret = tuner_i2c_send_data(HI3136I_I2C_CHAN,
            g_stTunerOps[u32TunerPort].u32DemodAddress, &stI2cDataStr);
    }
    else
    {
        s32Ret = tuner_i2c_send_data(g_stTunerOps[u32TunerPort].enI2cChannel,
            g_stTunerOps[u32TunerPort].u32DemodAddress, &stI2cDataStr);
    }

    return s32Ret;
}

HI_S32 qam_write_bit(HI_U32 u32TunerPort, HI_U8 u8RegAddr, HI_U8 u8BitNum, HI_U8 u8BitVal)
{
    HI_U8  u8Data  = 0;
    HI_S32 s32Ret = HI_SUCCESS;

    if (u8BitVal > 1)
    {
        HI_INFO_TUNER( "invalid parameter(u8BitVal>1):%d\n", u8BitVal);
        return HI_FAILURE;
    }

    if (u8BitNum > 7)
    {
        HI_INFO_TUNER( "invalid parameter(u8BitNum>7):%d\n", u8BitNum);
        return HI_FAILURE;
    }

    s32Ret = qam_read_byte(u32TunerPort, u8RegAddr, &u8Data);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    if (u8BitVal)
    {
        u8Data |= (1 << u8BitNum);
    }
    else
    {
        u8Data &= ~(1 << u8BitNum);
    }

    s32Ret = qam_write_byte(u32TunerPort, u8RegAddr, u8Data);

    return s32Ret;
}

#if 0
HI_S32 tuner_base_ioctl(unsigned int cmd, HI_VOID *arg)
{
    HI_S32 s32Ret;

    if (HI_NULL == arg)
    {
        HI_INFO_TUNER("data(arg) error: cmd=%d\n", cmd);
        return HI_FAILURE;
    }

    s32Ret = down_interruptible(&g_TunerMutex);
    switch (cmd)
    {
        case TUNER_CONNECT_CMD:
            {
                s32Ret = tuner_osr_connect((TUNER_SIGNAL_S *)arg);
                break;
            }
        case TUNER_GET_STATUS_CMD:
            {
                s32Ret = tuner_osr_getstatus((TUNER_DATA_S *)arg);
                break;
            }
        case TUNER_SELECT_TYPE_CMD:
            {
                s32Ret = tuner_osr_selecttype((TUNER_DATABUF_S *)arg);
                break;
            }
        case TUNER_SELECT_I2C_CMD:
            {
                s32Ret = tuner_osr_selecti2cchannel((TUNER_DATA_S *)arg);
                break;
            }
        case TUNER_SET_TSTYPE_CMD:
            {
                s32Ret = tuner_osr_settstype((TUNER_DATA_S *)arg);
                break;
            }
        case TUNER_CONNECT_TIMEOUT_CMD:
            {
                s32Ret = tuner_osr_connect_timeout((TUNER_DATABUF_S *)arg);
                break;
            }

        default:
            {
                HI_INFO_TUNER(" Invalid Ioctl command: 0x%x\n", cmd);
                up(&g_TunerMutex);
                return -ENOIOCTLCMD;
            }
    }

    up(&g_TunerMutex);
    return s32Ret;
}
#endif

HI_S32 tuner_chip_reset(HI_U32 u32ResetGpioNo)
{
    HI_U32 u32Ret = HI_FAILURE;
    u32Ret  = s_tuner_pGpioFunc->pfnGpioDirSetBit(u32ResetGpioNo, HI_FALSE);
    u32Ret |= s_tuner_pGpioFunc->pfnGpioWriteBit(u32ResetGpioNo, 0);
    msleep(100);
    u32Ret |= s_tuner_pGpioFunc->pfnGpioWriteBit(u32ResetGpioNo, 1);
    if (HI_SUCCESS != u32Ret)
    {
        HI_INFO_TUNER("Demod reset failed !\n");
        return u32Ret;
    }

    msleep(50);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_SetLNBPower(HI_U32 u32TunerId, HI_UNF_TUNER_FE_LNB_POWER_E enLNBPower)
{
    TUNER_LNB_OUT_S stLNBOut;
    HI_S32 s32Ret;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_FE_LNB_POWER_BUTT <= enLNBPower)
    {
        HI_ERR_TUNER("Input parameter(pstLNB) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stLNBOut.u32Port = u32TunerId;

    switch (enLNBPower)
    {
    case HI_UNF_TUNER_FE_LNB_POWER_ON:
        stLNBOut.enOut = TUNER_LNB_OUT_18V;
        break;

    case HI_UNF_TUNER_FE_LNB_POWER_ENHANCED:
        stLNBOut.enOut = TUNER_LNB_OUT_19V;
        break;

    case HI_UNF_TUNER_FE_LNB_POWER_OFF:
        stLNBOut.enOut = TUNER_LNB_OUT_0V;
        break;

    default:
        return HI_ERR_TUNER_INVALID_PARA;
    }

    s32Ret = down_interruptible(&g_TunerMutex);
    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerId].tuner_set_lnb_out)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        up(&g_TunerMutex);
        return HI_FAILURE;
    }

    s32Ret = g_stTunerOps[u32TunerId].tuner_set_lnb_out(u32TunerId, stLNBOut.enOut);
    up(&g_TunerMutex);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_set_lnb_out failed!\n");
        return s32Ret;
    }

    s_stMCESatPara[u32TunerId].enLNBPower = enLNBPower;

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_GetLNBPower(HI_U32 u32TunerId, HI_UNF_TUNER_FE_LNB_POWER_E *enLNBPower)
{
    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == enLNBPower)
    {
        HI_ERR_TUNER("Input parameter(enLNBPower) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    *enLNBPower = s_stMCESatPara[u32TunerId].enLNBPower;
    return HI_SUCCESS;
}

typedef struct
{
    HI_UNF_TUNER_DISEQC_SWITCH4PORT_S stPort1_0;
    HI_UNF_TUNER_DISEQC_SWITCH16PORT_S stPort1_1;
} DISEQC_STATUS_S;

static HI_UNF_TUNER_SWITCH_22K_E s_enSwitch22K[TUNER_NUM] =
{
    HI_UNF_TUNER_SWITCH_22K_NONE,
    HI_UNF_TUNER_SWITCH_22K_NONE,
    HI_UNF_TUNER_SWITCH_22K_NONE,
    HI_UNF_TUNER_SWITCH_22K_NONE,
    HI_UNF_TUNER_SWITCH_22K_NONE
};

static DISEQC_STATUS_S s_stDiSEqCStatus[TUNER_NUM] =
{
    {
        .stPort1_0 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H,
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        }
    },
    {
        .stPort1_0 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H,
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        }
    },
    {
        .stPort1_0 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H,
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        }
    },
    {
        .stPort1_0 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H,
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        }
    },
    {
        .stPort1_0 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE,
            HI_UNF_TUNER_FE_POLARIZATION_H,
            HI_UNF_TUNER_FE_LNB_22K_OFF
        },
        .stPort1_1 =
        {
            HI_UNF_TUNER_DISEQC_LEVEL_1_X,
            HI_UNF_TUNER_DISEQC_SWITCH_NONE
        }
    }
};

static HI_S32 TUNER_DISEQC_Send22K(HI_U32 u32TunerId, HI_BOOL bStatus)
{
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = bStatus ? 1 : 0;

    s32Ret = down_interruptible(&g_TunerMutex);
    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerId].tuner_send_continuous_22K)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        up(&g_TunerMutex);
        return HI_FAILURE;
    }

    s32Ret = g_stTunerOps[u32TunerId].tuner_send_continuous_22K(u32TunerId, stTunerData.u32Data);
    up(&g_TunerMutex);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set continuous 22K fail.\n");
        return HI_ERR_TUNER_FAILED_DISEQC;
    }

    return HI_SUCCESS;
}

static HI_S32 TUNER_DISEQC_Stop22K(HI_U32 u32TunerId)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = TUNER_DISEQC_Send22K(u32TunerId, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Stop 22K fail.\n");
        return HI_ERR_TUNER_FAILED_SWITCH;
    }

    return HI_SUCCESS;
}

static HI_S32 TUNER_DISEQC_Resume22K(HI_U32 u32TunerId)
{
    /* Resume */
    if (HI_UNF_TUNER_SWITCH_22K_22 == s_enSwitch22K[u32TunerId])
    {
        return TUNER_DISEQC_Send22K(u32TunerId, HI_TRUE);
    }
    else
    {
        return HI_SUCCESS;
    }
}

HI_S32 HI_DRV_TUNER_Switch22K(HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_22K_E enPort)
{
    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_SWITCH_22K_BUTT <= enPort)
    {
        HI_ERR_TUNER("Input parameter(enPort) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Save */
    s_enSwitch22K[u32TunerId] = enPort;

    if (HI_UNF_TUNER_SWITCH_22K_0 == enPort)
    {
        return TUNER_DISEQC_Send22K(u32TunerId, HI_FALSE);
    }
    else if (HI_UNF_TUNER_SWITCH_22K_22 == enPort)
    {
        return TUNER_DISEQC_Send22K(u32TunerId, HI_TRUE);
    }
    else
    {
        return HI_SUCCESS;
    }
}

#define DISEQC_DELAY_TIME_MS (15)

HI_S32 TUNER_DISEQC_SendRecvMessage(HI_U32 u32TunerId,
                                           const HI_UNF_TUNER_DISEQC_SENDMSG_S * pstSendMsg,
                                           HI_UNF_TUNER_DISEQC_RECVMSG_S * pstRecvMsg)
{
    TUNER_DISEQC_SENDMSG_S stSend;
    TUNER_DISEQC_RECVMSG_S stRecv;
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RepeatTimes;
    HI_U32 u32RepeatTime = 0;
    HI_BOOL bSendTone = HI_FALSE;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstSendMsg)
    {
        HI_ERR_TUNER("Input parameter(pstSendMsg) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstSendMsg->enLevel)
    {
        HI_ERR_TUNER("Input parameter(enLevel) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_SWITCH_TONEBURST_BUTT <= pstSendMsg->enToneBurst)
    {
        HI_ERR_TUNER("Input parameter(enToneBurst) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_DISEQC_MSG_MAX_LENGTH < pstSendMsg->u8Length)
    {
        HI_ERR_TUNER("Input parameter(u8Length) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_DISEQC_MAX_REPEAT_TIMES < pstSendMsg->u8RepeatTimes)
    {
        HI_ERR_TUNER("Input parameter(u8RepeatTimes) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* pstRecvMsg can be NULL */

    /* Handle tone burst */
    stTunerData.u32Port = u32TunerId;
    switch (pstSendMsg->enToneBurst)
    {
    case HI_UNF_TUNER_SWITCH_TONEBURST_NONE:
        bSendTone = HI_FALSE;
        break;

    case HI_UNF_TUNER_SWITCH_TONEBURST_0:
        bSendTone = HI_TRUE;
        stTunerData.u32Data = 0;
        break;

    case HI_UNF_TUNER_SWITCH_TONEBURST_1:
        bSendTone = HI_TRUE;
        stTunerData.u32Data = 1;
        break;
    default:
        HI_ERR_TUNER("Input parameter invalid!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Stop continuous 22K */
    (HI_VOID)TUNER_DISEQC_Stop22K(u32TunerId);
    msleep(DISEQC_DELAY_TIME_MS);

    /* Send command */
    stSend.u32Port = u32TunerId;
    stSend.stSendMsg = *pstSendMsg;
    u32RepeatTimes = pstSendMsg->u8RepeatTimes;
    //while (/*u32RepeatTimes >= 0*/1)
    for(;;)
    {
        /* Handle repeat */
        if (u32RepeatTime == 1)
        {
            stSend.stSendMsg.au8Msg[0] += 1;
        }

        /* Send command */
        s32Ret = down_interruptible(&g_TunerMutex);
        /* if tuner unsupport DiSEqC, return fault */
        if (!g_stTunerOps[u32TunerId].tuner_DiSEqC_send_msg) /* check if tuner get freq and symb offset is supported */
        {
            HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
            up(&g_TunerMutex);
            return HI_FAILURE;
        }

        s32Ret = g_stTunerOps[u32TunerId].tuner_DiSEqC_send_msg(u32TunerId, &(stSend.stSendMsg));
        up(&g_TunerMutex);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Send DiSEqC message fail.\n");
            return HI_ERR_TUNER_FAILED_DISEQC;
        }

        /* After send command, delay 15ms */
        msleep(DISEQC_DELAY_TIME_MS);

        /* Send tone */
        if (bSendTone)
        {
            /* if tuner blind scan operation is not setted, return fault */
            s32Ret = down_interruptible(&g_TunerMutex);
            if (!g_stTunerOps[u32TunerId].tuner_send_tone)
            {
                HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
                up(&g_TunerMutex);
                return HI_FAILURE;
            }

            s32Ret = g_stTunerOps[u32TunerId].tuner_send_tone(u32TunerId, stTunerData.u32Data);
            up(&g_TunerMutex);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Send tone fail.\n");
                return HI_ERR_TUNER_FAILED_DISEQC;
            }

            /* After send tone, delay 15ms */
            msleep(DISEQC_DELAY_TIME_MS);
        }

        if (u32RepeatTimes == 0)
        {
            break;
        }

        u32RepeatTimes--;
        u32RepeatTime++;
    }

    /* Recv msessage */
    stRecv.u32Port = u32TunerId;
    stRecv.pstRecvMsg = pstRecvMsg;
    if (HI_NULL != pstRecvMsg)
    {
        if (HI_UNF_TUNER_DISEQC_LEVEL_2_X == pstSendMsg->enLevel)
        {
            /* if tuner unsupport DiSEqC, return fault */
            s32Ret = down_interruptible(&g_TunerMutex);
            if (!g_stTunerOps[u32TunerId].tuner_DiSEqC_recv_msg) /* check if tuner get freq and symb offset is supported */
            {
                HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
                up(&g_TunerMutex);
                return HI_FAILURE;
            }

            s32Ret = g_stTunerOps[u32TunerId].tuner_DiSEqC_recv_msg(u32TunerId, stRecv.pstRecvMsg);
            up(&g_TunerMutex);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Recv DiSEqC message fail.\n");
                return HI_ERR_TUNER_FAILED_DISEQC;
            }

            msleep(DISEQC_DELAY_TIME_MS);
        }
        else
        {
            stRecv.pstRecvMsg->enStatus = HI_UNF_TUNER_DISEQC_RECV_UNSUPPORT;
            stRecv.pstRecvMsg->u8Length = 0;
        }
    }

    (HI_VOID)TUNER_DISEQC_Resume22K(u32TunerId);

    return HI_SUCCESS;
}

static HI_S32 DISEQC_SendCmd1_0(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_SWITCH4PORT_S* pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    //HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_S32 s32Ret;
    HI_U8 u8PortGroupBits;
    HI_U8 u8CMD;
    HI_U8 u8Framing;
    HI_U8 u8Polar;
    HI_U8 u8LOFreq;

    /* Polarization */
    if ((HI_UNF_TUNER_FE_POLARIZATION_V == pstPara->enPolar)
       || (HI_UNF_TUNER_FE_POLARIZATION_R == pstPara->enPolar))
    {
        u8Polar = POLARISATION_V;
    }
    else
    {
        u8Polar = POLARISATION_H;
    }

    /* LO, 22K */
    u8LOFreq = (HI_UNF_TUNER_FE_LNB_22K_ON == pstPara->enLNB22K) ? LO_FREQUENCY_H : LO_FREQUENCY_L;

    /* Init parameter */
    memset(&stSendMsg, 0, sizeof(stSendMsg));
    //memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    stSendMsg.enLevel = pstPara->enLevel;
    //stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 4;
    stSendMsg.u8RepeatTimes = 0;

    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;

    /* Send WRITE N0(0x38) command */
    u8PortGroupBits = PORT_GROUP_CLR_BITS | (((HI_U8)(pstPara->enPort - 1)) << 2) | u8Polar | u8LOFreq;
    u8CMD = CMD_WRITE_N0;
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_ANY_LNB_SW_SMATV, u8CMD, &u8PortGroupBits, 1);

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send WRITE N0 fail.\n");
        return s32Ret;
    }

    /* If support level 2.x, handle received message here. */

    return HI_SUCCESS;
}

static HI_S32 DISEQC_SendCmd1_1(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_SWITCH16PORT_S* pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    //HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_S32 s32Ret;
    HI_U8 u8PortGroupBits;
    HI_U8 u8CMD;
    HI_U8 u8Framing;

    /* Init parameter */
    memset(&stSendMsg, 0, sizeof(stSendMsg));
    //memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    stSendMsg.enLevel = pstPara->enLevel;
    //stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 4;
    stSendMsg.u8RepeatTimes = 0;

    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;

    /* Send WRITE N1(0x39) command */
    u8PortGroupBits = PORT_GROUP_CLR_BITS | (pstPara->enPort - 1);
    u8CMD = CMD_WRITE_N1;
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_ANY_LNB_SW_SMATV, u8CMD, &u8PortGroupBits, 1);

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send WRITE N1 fail.\n");
        return s32Ret;
    }

    /* If support level 2.x, handle received message here. */

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_DISEQC_Switch4Port(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_SWITCH4PORT_S* pstPara)
{
    HI_S32 s32Ret;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_DISEQC_SWITCH_PORT_5 <= pstPara->enPort)
    {
        HI_ERR_TUNER("Switch port invalid: %d\n", pstPara->enPort);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Save port parameter */
    s_stDiSEqCStatus[u32TunerId].stPort1_0 = *pstPara;

    /* If NONE, only save. */
    if (HI_UNF_TUNER_DISEQC_SWITCH_NONE == pstPara->enPort)
    {
        return HI_SUCCESS;
    }

    /* If use 4port device, other parameter must be valid. */
    if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= pstPara->enPolar)
    {
        HI_ERR_TUNER("Polarization invalid: %d\n", pstPara->enPolar);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_LNB_22K_BUTT <= pstPara->enLNB22K)
    {
        HI_ERR_TUNER("LNB 22K invalid: %d\n", pstPara->enLNB22K);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Switch 1.0 */
    s32Ret = DISEQC_SendCmd1_0(u32TunerId, pstPara);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send cmd 1.0 fail.\n");
        return s32Ret;
    }

    /*
     * If has switch 1.1, set it here.
     * Support Tuner - DiSEqC1.0 - DiSEqC1.1 - Other switch - LNB cascaded.
     */
    if (HI_UNF_TUNER_DISEQC_SWITCH_NONE != s_stDiSEqCStatus[u32TunerId].stPort1_1.enPort)
    {
        msleep(DISEQC_DELAY_BETWEEN_CMD_MS);
        s32Ret = DISEQC_SendCmd1_1(u32TunerId, &(s_stDiSEqCStatus[u32TunerId].stPort1_1));
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Send cmd 1.1 fail.\n");
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_DISEQC_Switch16Port(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_SWITCH16PORT_S* pstPara)
{
    HI_S32 s32Ret;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_DISEQC_SWITCH_PORT_BUTT <= pstPara->enPort)
    {
        HI_ERR_TUNER("Switch port invalid: %d\n", pstPara->enPort);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Save port parameter */
    s_stDiSEqCStatus[u32TunerId].stPort1_1 = *pstPara;

    /* If NONE, return. */
    if (HI_UNF_TUNER_DISEQC_SWITCH_NONE == pstPara->enPort)
    {
        return HI_SUCCESS;
    }

    /* If have 1.0 switch, set if first */
    if (HI_UNF_TUNER_DISEQC_SWITCH_NONE != s_stDiSEqCStatus[u32TunerId].stPort1_0.enPort)
    {
        s32Ret = DISEQC_SendCmd1_0(u32TunerId, &(s_stDiSEqCStatus[u32TunerId].stPort1_0));
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Send cmd 1.0 fail.\n");
            return s32Ret;
        }

        msleep(DISEQC_DELAY_BETWEEN_CMD_MS);
    }

    /* Switch 1.1 */
    s32Ret = DISEQC_SendCmd1_1(u32TunerId, pstPara);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send cmd 1.1 fail.\n");
        return s32Ret;
    }

    /*
     * If have 1.0 switch, repeat.
     * Support Tuner - DiSEqC1.1 - DiSEqC1.0 - Other switch - LNB cascaded.
     */
    if (HI_UNF_TUNER_DISEQC_SWITCH_NONE != s_stDiSEqCStatus[u32TunerId].stPort1_0.enPort)
    {
        msleep(DISEQC_DELAY_BETWEEN_CMD_MS);
        s32Ret = DISEQC_SendCmd1_0(u32TunerId, &(s_stDiSEqCStatus[u32TunerId].stPort1_0));
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Send cmd 1.0 fail.\n");
            return s32Ret;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_DISEQC_StorePos(HI_U32 u32TunerId,const HI_UNF_TUNER_DISEQC_POSITION_S *pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;
    HI_U8 u8Pos;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (DISEQC_MAX_MOTOR_PISITION < pstPara->u32Pos)
    {
        HI_ERR_TUNER("Input parameter(pstPara->u32Pos) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    u8Pos = (HI_U8)pstPara->u32Pos;

    stSendMsg.enLevel = pstPara->enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER, CMD_STORE_NN, &u8Pos, 1);
    stSendMsg.u8Length = 4;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send Store N fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_GotoPos(HI_U32 u32TunerId,const HI_UNF_TUNER_DISEQC_POSITION_S *pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;
    HI_U8 u8Pos;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (pstPara->u32Pos > DISEQC_MAX_MOTOR_PISITION)
    {
        HI_ERR_TUNER("Input parameter(pstPara->u32Pos) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    u8Pos = (HI_U8)pstPara->u32Pos;

    stSendMsg.enLevel = pstPara->enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER, CMD_GOTO_NN, &u8Pos, 1);
    stSendMsg.u8Length = 4;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send Goto N fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_SetLimit(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_LIMIT_S* pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;
    HI_U8 u8CMD;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_DISEQC_LIMIT_BUTT <= pstPara->enLimit)
    {
        HI_ERR_TUNER("Input parameter(pstPara->enLimit) invalid: %d\n", pstPara->enLimit);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    switch (pstPara->enLimit)
    {
    case HI_UNF_TUNER_DISEQC_LIMIT_OFF:
    default:
        u8CMD = CMD_LIMITS_OFF;
        break;

    case HI_UNF_TUNER_DISEQC_LIMIT_EAST:
        u8CMD = CMD_LIMIT_E;
        break;

    case HI_UNF_TUNER_DISEQC_LIMIT_WEST:
        u8CMD = CMD_LIMIT_W;
        break;
    }

    stSendMsg.enLevel = pstPara->enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER, u8CMD);
    stSendMsg.u8Length = 3;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send limit cmd fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_Move(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_MOVE_S* pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;
    HI_U8 u8CMD;
    HI_U8 u8Value;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_DISEQC_MOVE_DIR_BUTT <= pstPara->enDir)
    {
        HI_ERR_TUNER("Input parameter(pstPara->enDir) invalid, %d\n", pstPara->enDir);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_DISEQC_MOVE_TYPE_BUTT <= pstPara->enType)
    {
        HI_ERR_TUNER("Input parameter(pstPara->enType) invalid, %d\n", pstPara->enType);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;

    /* Direction */
    switch (pstPara->enDir)
    {
    case HI_UNF_TUNER_DISEQC_MOVE_DIR_EAST:
    case HI_UNF_TUNER_DISEQC_MOVE_DIR_BUTT:
    default:
        u8CMD = CMD_DRIVE_EAST;
        break;

    case HI_UNF_TUNER_DISEQC_MOVE_DIR_WEST:
        u8CMD = CMD_DRIVE_WEST;
        break;
    }

    /* Value */
    switch (pstPara->enType)
    {
    case HI_UNF_TUNER_DISEQC_MOVE_STEP_SLOW:
    case HI_UNF_TUNER_DISEQC_MOVE_TYPE_BUTT:
    default:
        u8Value = 0xff;
        break;

    case HI_UNF_TUNER_DISEQC_MOVE_STEP_FAST:
        u8Value = 0xfb;
        break;

    case HI_UNF_TUNER_DISEQC_MOVE_CONTINUE:
        u8Value = 0x00;
        break;
    }

    stSendMsg.enLevel = pstPara->enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER, u8CMD, &u8Value, 1);
    stSendMsg.u8Length = 4;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send drive cmd fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_Stop(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;

    stSendMsg.enLevel = enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER, CMD_HALT);
    stSendMsg.u8Length = 3;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send halt fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_Recalculate(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_RECALCULATE_S* pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    stSendMsg.enLevel = pstPara->enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER,
                                                CMD_SET_POSNS, &(pstPara->u8Para1), 3);
    stSendMsg.u8Length = 6;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send Set Posns fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_CalcAngular(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_USALS_PARA_S* pstPara)
{
#if 0
    HI_U8 u8Byte1 = 0;
    HI_U8 u8Byte2 = 0;
    HI_U8 u8RotateAngle;
    HI_U8 u8Fractional;
    HI_U16 u16Long;
    HI_U16 u16Lat;
    HI_U16 u16SatLong;
    HI_DOUBLE dSatAngle;
    HI_DOUBLE dLongitude;
    HI_DOUBLE dLatitude;
    HI_DOUBLE dT1;
    HI_DOUBLE dT2;
    HI_DOUBLE dT3;
    HI_DOUBLE dT4;
    HI_DOUBLE dTemp;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (pstPara->u16LocalLongitude > 2*MAX_LONGITUDE)
    {
        HI_ERR_TUNER("Input parameter(pstPara->u16LocalLongitude) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (pstPara->u16LocalLatitude > 2*MAX_LATITUDE)
    {
        HI_ERR_TUNER("Input parameter(pstPara->u16LocalLatitude) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (pstPara->u16SatLongitude > 2*MAX_LONGITUDE)
    {
        HI_ERR_TUNER("Input parameter(pstPara->u16SatLongitude) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Convert angle */
    u16Long = pstPara->u16LocalLongitude;
    u16Lat = pstPara->u16LocalLatitude;
    u16SatLong = pstPara->u16SatLongitude;
    dLongitude = ((u16Long < MAX_LONGITUDE) ? u16Long : -(2*MAX_LONGITUDE - u16Long)) / ANGLE_MULTIPLE;
    dLatitude = ((u16Lat < MAX_LATITUDE) ? u16Lat : -(2*MAX_LATITUDE - u16Lat)) / ANGLE_MULTIPLE;
    dSatAngle = ((u16SatLong < MAX_LONGITUDE) ? u16SatLong : -(2*MAX_LONGITUDE - u16SatLong)) / ANGLE_MULTIPLE;

    HI_ERR_TUNER("dLongitude=%f, dLatitude=%f, dSatAngle=%f\n", dLongitude, dLatitude, dSatAngle);

    dTemp = dSatAngle - dLongitude;
    dT1 = USALS_CONST_1 * cosf((PI * ABS(dTemp) / USALS_CONST_2));
    dT1 = (HI_DOUBLE) sqrtf(USALS_CONST_1 - dT1);
    dT1 = dT1 * dT1;
    dT2 = USALS_CONST_3 * sinf((PI * dLatitude / USALS_CONST_2));
    dT2 = dT2 * dT2;
    dT3 = (HI_DOUBLE) sqrtf(USALS_CONST_4 - dT2);
    dT3 = (HI_DOUBLE) dT3 * sinf((PI * ABS (dTemp) / USALS_CONST_2));
    dT3 = dT3 * dT3;
    dT3 = (HI_DOUBLE) sqrtf((dT2 + dT3));
    dT3 = (asinf(dT3/USALS_CONST_3) * USALS_CONST_2) / PI;
    dT3 = (HI_DOUBLE) sqrtf(USALS_CONST_5 - (USALS_CONST_6 * cosf((PI * dT3 / USALS_CONST_2))));
    dT4 = (HI_DOUBLE) sqrtf(USALS_CONST_5 - (USALS_CONST_6 * cosf((PI * dLatitude / USALS_CONST_2))));
    dT4 = (acosf(((dT3 * dT3) + (dT4 * dT4) - dT1) / (2.0 * dT3 * dT4)) * USALS_CONST_2) / PI;

    /* Handle negative case */
    if (((dSatAngle < dLongitude) && (dLatitude >= 0)) || ((dSatAngle > dLongitude) && (dLatitude < 0)))
    {
        dT4 = -dT4;
    }

    u8RotateAngle = (HI_U8) ABS(dT4);
    u8Fractional = (HI_U8)((ABS(dT4) - (double) u8RotateAngle) * ANGLE_MULTIPLE);

    /* Handle the first nibble */
    u8Byte1 = ((dT4 < 0) ? 0xD0 : 0xE0) | (u8RotateAngle >> 4);
    u8Byte2 = (u8RotateAngle & 0xF) << 4;

    /* According to section 3.10 of <positioner_appli_notice.pdf> */
    switch (u8Fractional)
    {
    case 0:
        u8Byte2 |= 0x0;
        break;
    case 1:
        u8Byte2 |= 0x2;
        break;
    case 2:
        u8Byte2 |= 0x3;
        break;
    case 3:
        u8Byte2 |= 0x5;
        break;
    case 4:
        u8Byte2 |= 0x6;
        break;
    case 5:
        u8Byte2 |= 0x8;
        break;
    case 6:
        u8Byte2 |= 0xA;
        break;
    case 7:
        u8Byte2 |= 0xB;
        break;
    case 8:
        u8Byte2 |= 0xD;
        break;
    case 9:
        u8Byte2 |= 0xE;
        break;
    default:
        u8Byte2 |= 0x0;
        break;
    }

    pstPara->u16Angular  = 0;
    pstPara->u16Angular |= (HI_U16)u8Byte1 << 8;
    pstPara->u16Angular |= u8Byte2;
#endif
    return HI_SUCCESS;

}

HI_S32 HI_DRV_TUNER_DISEQC_GotoAngular(HI_U32 u32TunerId, const HI_UNF_TUNER_DISEQC_USALS_ANGULAR_S* pstPara)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;
    HI_U8 u8Value[2];

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstPara->enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", pstPara->enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (pstPara->enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;

    stSendMsg.enLevel = pstPara->enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    u8Value[0] = (HI_U8)(pstPara->u16Angular>>8);
    u8Value[1] = (HI_U8)(pstPara->u16Angular);
    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, u8Framing, DEVICE_AZIMUTH_POSITIONER, CMD_GOTO_XX, u8Value, 2);
    stSendMsg.u8Length = 5;
    stSendMsg.u8RepeatTimes = 0;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send Goto XX fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_Reset(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    stSendMsg.enLevel = enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD(stSendMsg.au8Msg, u8Framing, DEVICE_ANY, CMD_RESET);
    stSendMsg.u8Length = 3;
    stSendMsg.u8RepeatTimes = 2;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("DiSEqC reset fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_Standby(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    stSendMsg.enLevel = enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD(stSendMsg.au8Msg, u8Framing, DEVICE_ANY, CMD_STANDBY);
    stSendMsg.u8Length = 3;
    stSendMsg.u8RepeatTimes = 2;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send standby fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_DISEQC_WakeUp(HI_U32 u32TunerId, HI_UNF_TUNER_DISEQC_LEVEL_E enLevel)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_UNF_TUNER_DISEQC_RECVMSG_S stRecvMsg;
    HI_U32 s32Ret;
    HI_U8 u8Framing;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= enLevel)
    {
        HI_ERR_TUNER("DiSEqC level invalid: %d\n", enLevel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    memset(&stSendMsg, 0, sizeof(stSendMsg));
    memset(&stRecvMsg, 0, sizeof(stRecvMsg));
    u8Framing = (enLevel == HI_UNF_TUNER_DISEQC_LEVEL_2_X) ? MASTER_REPLY_FIRST : MASTER_NOREPLY_FIRST;
    stSendMsg.enLevel = enLevel;
    stSendMsg.enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    FORMAT_DISEQC_CMD(stSendMsg.au8Msg, u8Framing, DEVICE_ANY, CMD_POWER_ON);
    stSendMsg.u8Length = 3;
    stSendMsg.u8RepeatTimes = 2;

    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, &stRecvMsg);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send power on fail.\n");
        return s32Ret;
    }

    /* TODO: If level 2.x, handle received message here. */

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_GetDeftAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr )
{
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_SetAttr(HI_U32  u32tunerId , const HI_UNF_TUNER_ATTR_S *pstTunerAttr )
{
    HI_S32 s32Ret = 0;
    TUNER_DATA_S stTunerData = {0};
    TUNER_DATABUF_S stDataBuf = {0};
    HI_TunerAttr_S stTuner_Attr = {0};
    HI_DemodAttr_S stDemod_Attr = {0};

    if(TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstConnectPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    stTunerData.u32Port = u32tunerId;
    stTunerData.u32Data = (HI_U32)pstTunerAttr->enI2cChannel;

    s32Ret = down_interruptible(&g_TunerMutex);

    s32Ret = tuner_osr_selecti2cchannel(&stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("tuner_osr_selecti2cchannel err.\n");
        up(&g_TunerMutex);
        return HI_FAILURE;
    }

    stDataBuf.u32Port = u32tunerId;	
	stTuner_Attr.enSigType = pstTunerAttr->enSigType;
    stTuner_Attr.enTunerDevType = pstTunerAttr->enTunerDevType;
    stTuner_Attr.u32TunerAddr = pstTunerAttr->u32TunerAddr;
    stDemod_Attr.enDemodDevType = pstTunerAttr->enDemodDevType;
    stDemod_Attr.u32DemodAddr = pstTunerAttr->u32DemodAddr;
    stDataBuf.u32DataBuf[0] = (HI_U32)&stDemod_Attr;
    stDataBuf.u32DataBuf[1] = (HI_U32)&stTuner_Attr;
    stDataBuf.u32DataBuf[2] = pstTunerAttr->u32ResetGpioNo;

    s32Ret = tuner_osr_selecttype(&stDataBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("tuner_osr_selecttype err.\n");
        up(&g_TunerMutex);
        return HI_FAILURE;
    }

    stTunerData.u32Port = u32tunerId;
    stTunerData.u32Data = pstTunerAttr->enOutputMode;

    s32Ret = tuner_osr_settstype(&stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("tuner_osr_settstype err \n");
        up(&g_TunerMutex);
        return HI_FAILURE;
    }

    up(&g_TunerMutex);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_SetSatAttr(HI_U32   u32tunerId , const HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr)
{
    HI_S32 s32Ret;

    if(TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId)invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstSatTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr)invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_RFAGC_BUTT <= pstSatTunerAttr->enRFAGC)
    {
        HI_ERR_TUNER("Input parameter(enRFAGC)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_IQSPECTRUM_BUTT <= pstSatTunerAttr->enIQSpectrum)
    {
        HI_ERR_TUNER("Input parameter(enIQSpectrum)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TSCLK_POLAR_BUTT <= pstSatTunerAttr->enTSClkPolar)
    {
        HI_ERR_TUNER("Input parameter(enTSClkPolar)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TS_FORMAT_BUTT <= pstSatTunerAttr->enTSFormat)
    {
        HI_ERR_TUNER("Input parameter(enTSFormat)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TS_SERIAL_PIN_BUTT <= pstSatTunerAttr->enTSSerialPIN)
    {
        HI_ERR_TUNER("Input parameter(enTSSerialPIN)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_DISEQCWAVE_BUTT <= pstSatTunerAttr->enDiSEqCWave)
    {
        HI_ERR_TUNER("Input parameter(enDiSEqCWave)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_LNBCTRL_DEV_TYPE_BUTT <= pstSatTunerAttr->enLNBCtrlDev)
    {
        HI_ERR_TUNER("Input parameter(enLNBCtrlDev)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    s32Ret = down_interruptible(&g_TunerMutex);
    s32Ret = tuner_set_sat_attr(u32tunerId, (HI_UNF_TUNER_SAT_ATTR_S *)pstSatTunerAttr);
    up(&g_TunerMutex);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner TUNER_SETDEMODATTR_CMD error\n");
        return HI_ERR_TUNER_FAILED_SETSATATTR;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_SetTsOut(HI_U32 u32tunerId, HI_UNF_TUNER_TSOUT_SET_S *stTsOut)
{
    HI_U32 u32TunerPort = 0;
    HI_S32 s32Ret = 0;

    /* get tuner port  number and if tuner port is not supported , return fault */
    if (HI_SUCCESS != tuner_check_port(u32TunerPort))
    {
        return HI_FAILURE;
    }

    /* if tuner get status operation is not setted, return fault */
    if (!g_stTunerOps[u32tunerId].tuner_set_ts_out) /* check if tuner_get_current_plp_type is supported */
    {
        HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
        return -EFAULT;
    }

    /* tuner_set_ts_out */
    s32Ret = g_stTunerOps[u32tunerId].tuner_set_ts_out(u32TunerPort,stTsOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER( "\n tuner_get_status failed \n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_Open (HI_U32    u32tunerId)
{
    HI_S32 s32Ret = 0;
    tuner_enable_crg();
    tuner_enable_adc();
    s32Ret = tuner_geti2cFunc();
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("tuner_geti2cFunc err\n");
        return HI_FAILURE;
    }
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_Close(HI_U32    u32tunerId)
{
    tuner_disable_crg();
    tuner_disable_adc();
    return HI_SUCCESS;
}

#if 0
HI_S32 HI_DRV_TUNER_Connect(HI_U32  u32tunerId , const HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara,HI_U32 u32TimeOut)
{
    TUNER_ACC_QAM_PARAMS_S tunerPara = {0};
    TUNER_SIGNAL_S tunerSignal = {0};
    TUNER_DATA_S tunerData = {0};
    HI_U32 u32TimeSpan = 0;
    HI_S32 s32Ret = 0;

    if(TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstConnectPara)
    {
        HI_ERR_TUNER("Input parameter(pstConnectPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    tunerPara.u32Frequency  = pstConnectPara->unConnectPara.stCab.u32Freq;
    tunerPara.unSRBW.u32SymbolRate = pstConnectPara->unConnectPara.stCab.u32SymbolRate;
    tunerPara.bSI = pstConnectPara->unConnectPara.stCab.bReverse;
    switch (pstConnectPara->unConnectPara.stCab.enModType)
    {
    case HI_UNF_MOD_TYPE_QAM_16:
        tunerPara.enQamType = QAM_TYPE_16;
        break;
    case HI_UNF_MOD_TYPE_QAM_32:
        tunerPara.enQamType = QAM_TYPE_32;
        break;
    case HI_UNF_MOD_TYPE_QAM_64:
    default:
        tunerPara.enQamType = QAM_TYPE_64;
        break;
    case HI_UNF_MOD_TYPE_QAM_128:
        tunerPara.enQamType = QAM_TYPE_128;
        break;
    case HI_UNF_MOD_TYPE_QAM_256:
        tunerPara.enQamType = QAM_TYPE_256;
        break;
    }

    if ((tunerPara.u32Frequency < 45000) || (tunerPara.u32Frequency > 858000))
    {
        HI_ERR_TUNER("Input parameter(pSignal.u32frequency) invalid freq = %d\n", tunerPara.u32Frequency);
        return HI_FAILURE;
    }

    if ((tunerPara.unSRBW.u32SymbolRate < 2600000) || (tunerPara.unSRBW.u32SymbolRate > 7200000))
    {
        HI_ERR_TUNER("Input parameter(pSignal.u32symbolRate = %d) invalid, \n", tunerPara.unSRBW.u32SymbolRate);
        return HI_FAILURE;
    }

    if ((0 != tunerPara.bSI) && (1 != tunerPara.bSI))
    {
        HI_ERR_TUNER("Input parameter(pSignal.u32bSI) error\n");

        //return -1;
    }

    tunerSignal.u32Port  = u32tunerId;
    tunerSignal.stSignal = tunerPara;
    s32Ret = tuner_osr_connect(&tunerSignal);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("tuner_osr_connect err\n");
        return HI_FAILURE;
    }

    if (0 == u32TimeOut)
    {
        return 0;
    }

    tunerData.u32Data = 0;
    tunerData.u32Port = u32tunerId;
    while (u32TimeSpan < u32TimeOut)
    {
        s32Ret = down_interruptible(&g_TunerMutex);
        s32Ret = tuner_osr_getstatus(&tunerData);
        up(&g_TunerMutex);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("tuner_ioctl TUNER_GET_STATUS_CMD err\n");
            return -1;
        }

        HI_ERR_TUNER("tuner_ioctl TUNER_GET_STATUS_CMD ok\n");
        if (HI_UNF_TUNER_SIGNAL_LOCKED == tunerData.u32Data)
        {
            return HI_SUCCESS;
        }
        else
        {
            msleep(50);
            u32TimeSpan += 50;
        }
    }

    HI_ERR_TUNER("connect time out\n");
    return HI_FAILURE;
}
#endif


#define SAT_C_MIN_KHZ (3000000)
#define SAT_C_MAX_KHZ (4200000)
#define SAT_KU_MIN_KHZ (10600000)
#define SAT_KU_MAX_KHZ (12750000)
#define SAT_DOWNLINK_FREQ_KU_MID (11700)
#define SAT_SYMBOLRATE_MAX (60000000)//(45000000)

HI_S32 HI_DRV_TUNER_SetLNBConfig( HI_U32 u32TunerId, const HI_UNF_TUNER_FE_LNB_CONFIG_S *pstLNB)
{
    HI_S32 s32Ret = 0;

    if (TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstLNB)
    {
        HI_ERR_TUNER("Input parameter(pstLNB) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_FE_LNB_TYPE_BUTT <= pstLNB->enLNBType)
    {
        HI_ERR_TUNER("Input parameter(pstLNB->enLNBType) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_LNB_BAND_BUTT <= pstLNB->enLNBBand)
    {
        HI_ERR_TUNER("Input parameter(pstLNB->enLNBBand) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNB->enLNBType)
    {
        if (pstLNB->u32LowLO != pstLNB->u32HighLO)
        {
            HI_ERR_TUNER("Input parameter invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }

    if (pstLNB->u32LowLO > pstLNB->u32HighLO)
    {
        HI_ERR_TUNER("Input parameter invalid, lowLO is bigger than highLO\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_LNB_BAND_C == pstLNB->enLNBBand)
    {
        if ((pstLNB->u32LowLO > 7500) || (pstLNB->u32HighLO > 7500))
        {
            HI_ERR_TUNER("Invalid LO freq\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }
    else
    {
        if ((pstLNB->u32LowLO <= 7500) || (pstLNB->u32HighLO <= 7500))
        {
            HI_ERR_TUNER("Invalid LO freq\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }

    s32Ret = down_interruptible(&g_TunerMutex);
    s_stMCESatPara[u32TunerId].stLNBConfig = *pstLNB;
    up(&g_TunerMutex);

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_GetLNBConfig( HI_U32 u32TunerId, HI_UNF_TUNER_FE_LNB_CONFIG_S *pstLNB)
{
    if (HI_NULL == pstLNB)
    {
        HI_ERR_TUNER("Input parameter(pstLNB) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    memcpy(pstLNB,&s_stMCESatPara[u32TunerId].stLNBConfig,sizeof(HI_UNF_TUNER_FE_LNB_CONFIG_S));
    return HI_SUCCESS;
}

/* Convert downlink frequency to IF, calculate LNB 22K status synchronously, for connect */
/*Downlink freq dominates the course, i.e, the freq band is decided by the downlink freq*/
static HI_VOID TUNER_DownlinkFreqToIF(HI_UNF_TUNER_FE_LNB_CONFIG_S* pstLNBConfig,
                                      HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_U32 u32DownlinkFreq,
                                      HI_U32* pu32IF, HI_UNF_TUNER_FE_LNB_22K_E *penLNB22K)
{
    /* Default */
    if (HI_NULL != penLNB22K)
    {
        *penLNB22K = HI_UNF_TUNER_FE_LNB_22K_OFF;
    }

    if ((SAT_C_MIN_KHZ <= u32DownlinkFreq)
            && (SAT_C_MAX_KHZ >= u32DownlinkFreq))
    {
        pstLNBConfig->enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_C;
    }
    else if ((SAT_KU_MIN_KHZ <= u32DownlinkFreq)
            && (SAT_KU_MAX_KHZ >= u32DownlinkFreq))
    {
        pstLNBConfig->enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_KU;
    }
    else
    {
        HI_ERR_TUNER("Error freq!\n");
        return;
    }

    switch (pstLNBConfig->enLNBBand)
    {
        /* C band, IF = LO - downlink frequency */
    case HI_UNF_TUNER_FE_LNB_BAND_C:
        /* Single LO */
        if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNBConfig->enLNBType)
           || (pstLNBConfig->u32HighLO == pstLNBConfig->u32LowLO))
        {
            *pu32IF = pstLNBConfig->u32LowLO * 1000 - u32DownlinkFreq;
        }
        /* Dual LO */
        else
        {
            /* V/R polarization, use high LO */
            if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
            {
                *pu32IF = pstLNBConfig->u32HighLO * 1000 - u32DownlinkFreq;
            }
            /* H/L polarization, use low LO */
            else
            {
                *pu32IF = pstLNBConfig->u32LowLO * 1000 - u32DownlinkFreq;
            }
        }

        break;

    /* Ku band, IF = downlink frequency - LO */
    case HI_UNF_TUNER_FE_LNB_BAND_KU:

        /* Single LO */
        if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNBConfig->enLNBType)
           || (pstLNBConfig->u32HighLO == pstLNBConfig->u32LowLO))
        {
            *pu32IF = u32DownlinkFreq - pstLNBConfig->u32LowLO * 1000;
        }
        /* Dual LO */
        else
        {
            /* downlink frequency >= 11700MHz, use high LO */
            if ((u32DownlinkFreq >= SAT_DOWNLINK_FREQ_KU_MID * 1000))
            {
                *pu32IF = u32DownlinkFreq - pstLNBConfig->u32HighLO * 1000;

                /* Ku dual LO LNB use 22K select high LO */
                if (HI_NULL != penLNB22K)
                {
                    *penLNB22K = HI_UNF_TUNER_FE_LNB_22K_ON;
                }
            }
            /* downlink frequency < 11700MHz, use low LO */
            else
            {
                *pu32IF = u32DownlinkFreq - pstLNBConfig->u32LowLO * 1000;
            }
        }

        break;

    default:
        break;
    }
}

static HI_S32 TUNER_SetLNBOutAnd22K(HI_U32 u32TunerId,
                                    HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_UNF_TUNER_FE_LNB_22K_E enLNB22K)
{
    TUNER_LNB_OUT_S stLNBOut;
    HI_S32 s32Ret;

    s32Ret = down_interruptible(&g_TunerMutex);
    switch (s_stMCESatPara[u32TunerId].enLNBPower)
    {
    /* 0V */
    case HI_UNF_TUNER_FE_LNB_POWER_OFF:
        stLNBOut.enOut = TUNER_LNB_OUT_0V;
        break;

    /* 13V/18V */
    case HI_UNF_TUNER_FE_LNB_POWER_ON:
        if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
        {
            stLNBOut.enOut = TUNER_LNB_OUT_13V;
        }
        else
        {
            stLNBOut.enOut = TUNER_LNB_OUT_18V;
        }

        break;

        /* 14V/19V */
    case HI_UNF_TUNER_FE_LNB_POWER_ENHANCED:
        if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
        {
            stLNBOut.enOut = TUNER_LNB_OUT_14V;
        }
        else
        {
            stLNBOut.enOut = TUNER_LNB_OUT_19V;
        }
        break;

    default:
        up(&g_TunerMutex);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stLNBOut.u32Port = u32TunerId;
    /* if tuner blind scan operation is not setted, return fault */
    if (!g_stTunerOps[u32TunerId].tuner_set_lnb_out)
    {
        HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
        up(&g_TunerMutex);
        return HI_FAILURE;
    }

    s32Ret = g_stTunerOps[u32TunerId].tuner_set_lnb_out(u32TunerId, stLNBOut.enOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_INFO_TUNER( "tuner_set_lnb_out failed!\n");
        up(&g_TunerMutex);
        return s32Ret;
    }

    /* Save polarization status */
    s_stMCESatPara[u32TunerId].enPolar = enPolar;

    /* 22K signal control. If LNB power off, can't send 22K signal. */
    if (HI_UNF_TUNER_FE_LNB_POWER_OFF != s_stMCESatPara[u32TunerId].enLNBPower)
    {
        /* If has 22K switch, 22K controlled by switch.
           If hasn't 22K switch, 22K controlled by tuner lock or blind scan.
         */
        if (HI_UNF_TUNER_SWITCH_22K_NONE == s_stMCESatPara[u32TunerId].enSwitch22K)
        {
            /* if tuner blind scan operation is not setted, return fault */
            if (!g_stTunerOps[u32TunerId].tuner_send_continuous_22K)
            {
                HI_INFO_TUNER( "tuner service function ptr is NULL!\n");
                up(&g_TunerMutex);
                return HI_FAILURE;
            }

            s32Ret = g_stTunerOps[u32TunerId].tuner_send_continuous_22K(u32TunerId, enLNB22K);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Set continuous 22K fail.\n");
                up(&g_TunerMutex);
                return HI_ERR_TUNER_FAILED_LNBCTRL;
            }
        }
    }

    /* Save polarization status */
    s_stMCESatPara[u32TunerId].enLNB22K = enLNB22K;
    up(&g_TunerMutex);
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_Connect(HI_U32  u32tunerId , const HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara,HI_U32 u32TimeOut)
{
    HI_S32 s32Ret = 0;
    HI_U32 u32TimeSpan = 0;
    TUNER_ACC_QAM_PARAMS_S stSignal = {0};
    HI_UNF_TUNER_LOCK_STATUS_E enTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
    HI_UNF_TUNER_FE_LNB_22K_E enLNB22K;
    HI_U32 u32Bit0Value, u32Bit7Value, u32Value = 0x1, u32New;
    HI_U32 i, u32N;

    if (HI_SUCCESS != tuner_check_port(u32tunerId))
    {
        HI_ERR_TUNER( "invalid tuner port: %d\n", u32tunerId);
        return HI_FAILURE;
    }

    /* Cable and J83B*/
    if ((HI_UNF_TUNER_SIG_TYPE_CAB == pstConnectPara->enSigType) || (HI_UNF_TUNER_SIG_TYPE_J83B== pstConnectPara->enSigType))
    {
        stSignal.u32Frequency = pstConnectPara->unConnectPara.stCab.u32Freq;
        stSignal.unSRBW.u32SymbolRate = pstConnectPara->unConnectPara.stCab.u32SymbolRate;
        stSignal.bSI = pstConnectPara->unConnectPara.stCab.bReverse;

        switch(pstConnectPara->unConnectPara.stCab.enModType)
        {
            case HI_UNF_MOD_TYPE_QAM_16:
                stSignal.enQamType = QAM_TYPE_16;
                 break;

            case HI_UNF_MOD_TYPE_QAM_32:
                stSignal.enQamType = QAM_TYPE_32;
                 break;

            case HI_UNF_MOD_TYPE_QAM_64:
            case HI_UNF_MOD_TYPE_DEFAULT:
                stSignal.enQamType = QAM_TYPE_64;
                 break;

            case HI_UNF_MOD_TYPE_QAM_128:
                stSignal.enQamType = QAM_TYPE_128;
                 break;

            case HI_UNF_MOD_TYPE_QAM_256:
                stSignal.enQamType = QAM_TYPE_256;
                 break;
            default:
                HI_ERR_TUNER("Tuner HI_UNF_SET_eqamType error:%d\n",pstConnectPara->unConnectPara.stCab.enModType);
                return HI_FAILURE;
        }

        /* if tuner connect operation is not setted, return fault */
        s32Ret = down_interruptible(&g_TunerMutex);
        if (!g_stTunerOps[u32tunerId].tuner_connect) /* check if tuner conect is supported */
        {
            HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
            up(&g_TunerMutex);
            return HI_FAILURE;
        }

        /* call tuner connect operation */
        s32Ret = g_stTunerOps[u32tunerId].tuner_connect(u32tunerId, &stSignal);
        up(&g_TunerMutex);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER( "\n tuner_connect failed \n");
            return s32Ret;
        }

        while (u32TimeSpan < u32TimeOut)
        {
            s32Ret = down_interruptible(&g_TunerMutex);
            if (g_stTunerOps[u32tunerId].tuner_get_status) /* check if tuner get status is supported */
            {
                /* get tuner lock status */
                s32Ret = g_stTunerOps[u32tunerId].tuner_get_status(u32tunerId, &enTunerStatus);
                up(&g_TunerMutex);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_TUNER( "\n tuner_get_status failed \n");
                    return s32Ret;
                }
            }

            if(HI_UNF_TUNER_SIGNAL_LOCKED == enTunerStatus)
            {
                return HI_SUCCESS;
            }
            else
            {
                mdelay(10);
                u32TimeSpan += 10;
            }
        }

    }
    /* Satellite */
    else if (HI_UNF_TUNER_SIG_TYPE_SAT == pstConnectPara->enSigType)
    {
        if (!((SAT_C_MIN_KHZ <= pstConnectPara->unConnectPara.stSat.u32Freq)
                && (SAT_C_MAX_KHZ >= pstConnectPara->unConnectPara.stSat.u32Freq))
            && !((SAT_KU_MIN_KHZ <= pstConnectPara->unConnectPara.stSat.u32Freq)
                && (SAT_KU_MAX_KHZ >= pstConnectPara->unConnectPara.stSat.u32Freq)))
        {
            HI_ERR_TUNER("Input parameter(u32Freq) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.u32Freq);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (SAT_SYMBOLRATE_MAX < pstConnectPara->unConnectPara.stSat.u32SymbolRate)
        {
            HI_ERR_TUNER("Input parameter(u32SymbolRate) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.u32SymbolRate);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= pstConnectPara->unConnectPara.stSat.enPolar)
        {
            HI_ERR_TUNER("Input parameter(enPolar) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.enPolar);
            return HI_ERR_TUNER_INVALID_PARA;

        }

        /* Convert downlink frequency to IF */
        TUNER_DownlinkFreqToIF(&(s_stMCESatPara[u32tunerId].stLNBConfig), pstConnectPara->unConnectPara.stSat.enPolar,
                               pstConnectPara->unConnectPara.stSat.u32Freq, &(stSignal.u32Frequency), &enLNB22K);

        stSignal.unSRBW.u32SymbolRate = pstConnectPara->unConnectPara.stSat.u32SymbolRate;
        stSignal.enPolar = pstConnectPara->unConnectPara.stSat.enPolar;

        u32N = pstConnectPara->unConnectPara.stSat.u32ScrambleValue;
        for(i = 0;i < u32N;i++)
        {
            u32Bit0Value = u32Value & 0x1;
            u32Bit7Value = (u32Value >> 7) & 0x1;
            u32New = (u32Bit0Value + u32Bit7Value) % 2;
            u32Value = (u32Value >> 1) | (u32New << 17);
        }

        stSignal.u23ScrambleCode = u32Value;

         /* LNB power and 22K signal switch */
        s32Ret = TUNER_SetLNBOutAnd22K(u32tunerId, pstConnectPara->unConnectPara.stSat.enPolar, enLNB22K);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("TUNER_SetLNBOutAnd22K fail.\n");
        }

        /* if tuner connect operation is not setted, return fault */
        s32Ret = down_interruptible(&g_TunerMutex);
        if (!g_stTunerOps[u32tunerId].tuner_connect) /* check if tuner conect is supported */
        {
            HI_ERR_TUNER( "tuner service function ptr is NULL!\n");
            up(&g_TunerMutex);
            return HI_FAILURE;
        }

        /* call tuner connect operation */
        s32Ret = g_stTunerOps[u32tunerId].tuner_connect(u32tunerId, &stSignal);
        up(&g_TunerMutex);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER( "\n tuner_connect failed \n");
            return s32Ret;
        }

        if (0 == u32TimeOut)
        {
            return HI_SUCCESS;
        }

        while (u32TimeSpan < u32TimeOut)
        {
            s32Ret = down_interruptible(&g_TunerMutex);
            if (g_stTunerOps[u32tunerId].tuner_get_status) /* check if tuner get status is supported */
            {
                /* get tuner lock status */
                s32Ret = g_stTunerOps[u32tunerId].tuner_get_status(u32tunerId, &enTunerStatus);
                up(&g_TunerMutex);
                if (HI_SUCCESS != s32Ret)
                {
                    HI_ERR_TUNER( "\n tuner_get_status failed \n");
                    return s32Ret;
                }
            }

            if (HI_UNF_TUNER_SIGNAL_LOCKED == enTunerStatus)
            {
                HI_ERR_TUNER("Tuner LOCKED!\n");
                return HI_SUCCESS;
            }
            else
            {
                mdelay(10);
                u32TimeSpan += 10;
            }
        }

        return HI_SUCCESS;
    }

    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_GetStatus(HI_U32    u32tunerId , HI_UNF_TUNER_STATUS_S  *pstTunerStatus)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TUNER_DATA_S stTunerDataStr;

    if(HI_NULL == pstTunerStatus)
    {
        return -EFAULT;
    }

    memset(&stTunerDataStr, 0, sizeof(stTunerDataStr));

    stTunerDataStr.u32Port = u32tunerId;

    s32Ret = tuner_osr_getstatus(&stTunerDataStr);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    pstTunerStatus->enLockStatus = stTunerDataStr.u32Data;

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_GetBer(HI_U32  u32tunerId , HI_U32 *pu32ber)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TUNER_DATABUF_S stTunerDataBuf;

    if(HI_NULL == pu32ber)
    {
        return -EFAULT;
    }

    memset(&stTunerDataBuf, 0, sizeof(stTunerDataBuf));

    stTunerDataBuf.u32Port = u32tunerId;

    s32Ret = tuner_osr_getber(&stTunerDataBuf);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    memcpy(pu32ber, stTunerDataBuf.u32DataBuf, sizeof(stTunerDataBuf.u32DataBuf));

    /*u32Ber = (stTunerDataBuf.u32DataBuf[0] << 16) | (stTunerDataBuf.u32DataBuf[1] << 8) | (stTunerDataBuf.u32DataBuf[2]);
    u64ResultBer = u64Ber;
    do_div(u64ResultBer, u32base);*/

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_GetRs(HI_U32  u32tunerId , HI_U32 *pu32Rs)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if(HI_NULL == pu32Rs)
    {
        return -EFAULT;
    }

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_GetSnr(HI_U32  u32tunerId , HI_U32 *pu32Snr)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TUNER_DATA_S stTunerDataStr;

    if(HI_NULL == pu32Snr)
    {
        return -EFAULT;
    }

    memset(&stTunerDataStr, 0, sizeof(stTunerDataStr));
    stTunerDataStr.u32Port = u32tunerId;
    s32Ret = tuner_osr_getsnr(&stTunerDataStr);
    if(HI_SUCCESS != s32Ret)
    {
        return HI_FAILURE;
    }
    *pu32Snr = stTunerDataStr.u32Data;

    return s32Ret;
}
HI_S32 HI_DRV_TUNER_GetRssi(HI_U32  u32tunerId , HI_U32 *pu32Rssi)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TUNER_DATABUF_S stTunerDataBuf;

    if(HI_NULL == pu32Rssi)
    {
        return -EFAULT;
    }

    memset(&stTunerDataBuf, 0, sizeof(TUNER_DATABUF_S));
    stTunerDataBuf.u32Port = u32tunerId;

    s32Ret = tuner_osr_getsignalstrength(&stTunerDataBuf);
    memcpy(pu32Rssi, stTunerDataBuf.u32DataBuf, sizeof(stTunerDataBuf.u32DataBuf));

    return s32Ret;
}
HI_S32 HI_DRV_TUNER_GetFreqSymbOffset(HI_U32  u32tunerId , HI_U32 *pu32Offset)
{
    HI_S32 s32Ret = HI_SUCCESS;
    TUNER_DATABUF_S stTunerData;

    if(HI_NULL == pu32Offset)
    {
        return -EFAULT;
    }

    memset(&stTunerData, 0, sizeof(stTunerData));
    stTunerData.u32Port = u32tunerId;

    s32Ret = tuner_get_freq_symb_offset(&stTunerData);
    memcpy(pu32Offset, stTunerData.u32DataBuf, sizeof(stTunerData.u32DataBuf));

    return s32Ret;
}

HI_S32 HI_DRV_TUNER_SetLnbOut(HI_U32  u32tunerId ,int LnbPower)
{
    HI_S32 s32Ret = 0;
    TUNER_LNB_OUT_S stLnbOut = {0};

    if (HI_SUCCESS != tuner_check_port(u32tunerId))
    {
        HI_ERR_TUNER( "invalid tuner port: %d\n", u32tunerId);
        return HI_FAILURE;
    }

    stLnbOut.u32Port = u32tunerId;
    switch(LnbPower)
    {
        case 13:
            stLnbOut.enOut = TUNER_LNB_OUT_13V;
            break;
        case 14:
            stLnbOut.enOut = TUNER_LNB_OUT_14V;
            break;
        case 18:
            stLnbOut.enOut = TUNER_LNB_OUT_18V;
            break;
        case 19:
            stLnbOut.enOut = TUNER_LNB_OUT_19V;
            break;
        default:
            break;
    }

    s32Ret = tuner_set_lnb_out(&stLnbOut);
    return s32Ret;
}

HI_S32 HI_DRV_TUNER_SetSwitchFreq(HI_U32 u32SwitchFreq)
{
    gs_u32MidFreq = u32SwitchFreq;
    return HI_SUCCESS;
}

HI_S32 HI_DRV_TUNER_GetSwitchFreq(HI_U32 *u32SwitchFreq)
{
    *u32SwitchFreq= gs_u32MidFreq;
    return HI_SUCCESS;
}


HI_S32 HI_DRV_TUNER_SetLoopthrough(HI_U32  u32tunerId)
{
    HI_S32 s32Ret = HI_SUCCESS;
#if defined(TUNER_DEV_TYPE_AV2011)
    s32Ret = av2011_set_loopthrough(u32tunerId);
#endif
    return s32Ret;
}

HI_S32 HI_DRV_TUNER_CancelLoopthrough(HI_U32  u32tunerId)
{
    HI_S32 s32Ret = HI_SUCCESS;
#if defined(TUNER_DEV_TYPE_AV2011)
    s32Ret = av2011_cancel_loopthrough(u32tunerId);
#endif
    return s32Ret;
}

#ifndef MODULE
EXPORT_SYMBOL(hi_tuner_open);
EXPORT_SYMBOL(hi_tuner_ioctl);
EXPORT_SYMBOL(hi_tuner_release);
EXPORT_SYMBOL(tuner_suspend);
EXPORT_SYMBOL(tuner_resume);
EXPORT_SYMBOL(tuner_proc_read);
EXPORT_SYMBOL(tuner_proc_read_reg);
#else
/*not as parameter in the kernel temporarily*/
module_param_array(g_xtal_clk_table,uint,NULL,S_IRUGO);
module_param_array(g_demod_address,uint,NULL,S_IRUGO);
module_param_array(g_halftuner_address,uint,NULL,S_IRUGO);
#endif

EXPORT_SYMBOL(HI_DRV_TUNER_Init);
EXPORT_SYMBOL(HI_DRV_TUNER_DeInit);

EXPORT_SYMBOL(HI_DRV_TUNER_GetDeftAttr);
EXPORT_SYMBOL(HI_DRV_TUNER_SetAttr);
EXPORT_SYMBOL(HI_DRV_TUNER_SetSatAttr);

EXPORT_SYMBOL(HI_DRV_TUNER_Open);
EXPORT_SYMBOL(HI_DRV_TUNER_Close);

EXPORT_SYMBOL(HI_DRV_TUNER_Connect);
EXPORT_SYMBOL(HI_DRV_TUNER_GetStatus);
EXPORT_SYMBOL(HI_DRV_TUNER_GetBer);
EXPORT_SYMBOL(HI_DRV_TUNER_GetRs);
EXPORT_SYMBOL(HI_DRV_TUNER_GetSnr);
EXPORT_SYMBOL(HI_DRV_TUNER_GetRssi);
EXPORT_SYMBOL(HI_DRV_TUNER_GetFreqSymbOffset);
EXPORT_SYMBOL(HI_DRV_TUNER_SetLnbOut);

#if defined (CHIP_TYPE_hi3716cv200) || defined (CHIP_TYPE_hi3716mv400)
EXPORT_SYMBOL(qam_ram_collect_data);
#endif

EXPORT_SYMBOL(HI_DRV_TUNER_SetLNBConfig);
EXPORT_SYMBOL(HI_DRV_TUNER_GetLNBConfig);
EXPORT_SYMBOL(HI_DRV_TUNER_SetLNBPower);
EXPORT_SYMBOL(HI_DRV_TUNER_GetLNBPower);
EXPORT_SYMBOL(HI_DRV_TUNER_SetSwitchFreq);
EXPORT_SYMBOL(HI_DRV_TUNER_GetSwitchFreq);
EXPORT_SYMBOL(HI_DRV_TUNER_SetLoopthrough);
EXPORT_SYMBOL(HI_DRV_TUNER_CancelLoopthrough);
EXPORT_SYMBOL(HI_DRV_TUNER_Switch22K);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Switch4Port);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Switch16Port);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_StorePos);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_GotoPos);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_SetLimit);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Move);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Stop);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Recalculate);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_CalcAngular);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_GotoAngular);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Reset);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_Standby);
EXPORT_SYMBOL(HI_DRV_TUNER_DISEQC_WakeUp);
EXPORT_SYMBOL(HI_DRV_TUNER_SetTsOut);

