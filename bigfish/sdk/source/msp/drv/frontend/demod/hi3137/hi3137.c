/***********************************************************************************
*              Copyright 2012 - 2013, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi3137.c
* Description:
*
* History:
* Version   Date             Author     DefectNum        Description
* main\1    2013-09-22   w00203631    NULL                Create this file.
***********************************************************************************/

#include <linux/delay.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/time.h>
#include <linux/module.h>
#include <asm/io.h>
#include <linux/kthread.h>

#include "drv_demod.h"
#include "hi_type.h"
#include "hi_drv_i2c.h"
#include "hi_drv_gpio.h"
#include "hi_debug.h"
#include "hi_error_mpi.h"
//#include " hi_unf_ecs_type.h"
#include "hi_drv_proc.h"
#include "hi_drv_sys.h"

#include "hi_type.h"
#include "hi_debug.h"
#include "mxl603.h"
#include "mxl608.h"
#include "silabs.h"
#include "R836.h"
#include "tda182i5a.h"
#include "si2144.h"

typedef enum tagHI3137_LOCK_FLAG_E
{
    AGC_LOCK_FLAG = 0,
    SYNC_LOCK_FLAG,
    SYNC_PRE_LOCK_FLAG,
    SIG_T2_LOCK_FLAG,
    TPS_T_LOCK_FLAG,
    FEC_LOCK_FLAG,
    RESERVED_LOCK_2,
    RESERVED_LOCK_3
} HI3137_LOCK_FLAG_E;

#define     hi3137_abs(value)       ((value >=0)?(value):(-value))

extern TUNER_ATTR s_stSatTunerResumeInfo[];

static HI_UNF_TUNER_DEV_TYPE_E g_stTunerType;
static HI_U32                  g_stXtalClk = 24000;
static HI_U8 g_stI2cChannel;

static HI_S32 tuner_init(HI_U32 u32TunerPort)
{
    HI_S32 s32Ret;

    switch(g_stTunerType)
    {
        case HI_UNF_TUNER_DEV_TYPE_MXL603:
			break;
	#ifdef TUNER_DEV_TYPE_MXL608
        case HI_UNF_TUNER_DEV_TYPE_MXL608:
            s32Ret = mxl608_init_tuner(u32TunerPort);
            break;
	#endif		
    #ifdef TUNER_DEV_TYPE_SI2147
        case HI_UNF_TUNER_DEV_TYPE_SI2147:
            //s32Ret = Si2147_Tune_DTV_Initial(u32TunerPort);
            break;
    #endif
    #ifdef TUNER_DEV_TYPE_RAFAEL836
        case HI_UNF_TUNER_DEV_TYPE_RAFAEL836:
            s32Ret = R840_Init();
            break;
    #endif
	#ifdef TUNER_DEV_TYPE_TDA182I5A
		case HI_UNF_TUNER_DEV_TYPE_TDA182I5A:
			s32Ret = tda182i5a_init_tuner(u32TunerPort);
			break;
	#endif
	#ifdef TUNER_DEV_TYPE_SI2144
		case HI_UNF_TUNER_DEV_TYPE_SI2144:
			s32Ret = si2144_init_tuner(u32TunerPort,g_stI2cChannel);
			break;
	#endif
        default:
            HI_ERR_TUNER("tuner init error.\n");
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 tuner_set_freq(HI_U32 u32TunerPort,HI_U32 u32Frequency,HI_U32 u32BandWidth,HI_U32 u32DVBMode)
{
    HI_S32 s32Ret;

    switch(g_stTunerType)
    {
    
	#ifdef TUNER_DEV_TYPE_MXL603
        case HI_UNF_TUNER_DEV_TYPE_MXL603:
			g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth = u32BandWidth;
            s32Ret=mxl603_set_tuner(u32TunerPort,g_stI2cChannel,u32Frequency);
            if(HI_FAILURE == s32Ret)
            {
                HI_ERR_TUNER("mxl603 set tuner error.\n");
                return HI_FAILURE;
            }
            break;
	#endif	
	#ifdef TUNER_DEV_TYPE_MXL608
			case HI_UNF_TUNER_DEV_TYPE_MXL608:
			g_stTunerOps[u32TunerPort].stCurrPara.unSRBW.u32BandWidth = u32BandWidth;
            s32Ret=mxl608_set_tuner(u32TunerPort,g_stI2cChannel,u32Frequency);
            if(HI_FAILURE == s32Ret)
            {
                HI_ERR_TUNER("mxl608 set tuner error.\n");
                return HI_FAILURE;
            }
            break;
	#endif		
    #ifdef TUNER_DEV_TYPE_SI2147
        case HI_UNF_TUNER_DEV_TYPE_SI2147:
            //s32Ret=Si2147_Tune_DTV_Demo(u32TunerPort,u32Frequency*1000,u32BandWidth);
            break;
    #endif
    #ifdef TUNER_DEV_TYPE_RAFAEL836
        case HI_UNF_TUNER_DEV_TYPE_RAFAEL836:
            R840_set_tuner(u32TunerPort,u32Frequency,u32BandWidth,u32DVBMode);
            break;
    #endif
	#ifdef TUNER_DEV_TYPE_TDA182I5A
		case HI_UNF_TUNER_DEV_TYPE_TDA182I5A:
			tda182i5a_set_tuner(u32TunerPort,u32Frequency*1000, u32BandWidth);
			break;
	#endif
	#ifdef TUNER_DEV_TYPE_SI2144
		case HI_UNF_TUNER_DEV_TYPE_SI2144:
			si2144_set_tuner(u32TunerPort,u32Frequency*1000, u32BandWidth);
			break;
	#endif
        default:
            HI_ERR_TUNER("tuner set freq error.\n");
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}

static HI_S32 demod_clock_out_reset(HI_U32 u32TunerPort)
{
    HI_U8 u8RegData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_IO_CTRL4, &u8RegData);
    u8RegData = u8RegData & 0xFB;
    u8RegData = (u8RegData & 0xE7) | (3<<3);
    qam_write_byte(u32TunerPort, Hi3137_IO_CTRL4, u8RegData);

    qam_read_byte(u32TunerPort, Hi3137_SDR_CTRL, &u8RegData);
    u8RegData = u8RegData & 0xFE;
    qam_write_byte(u32TunerPort, Hi3137_SDR_CTRL, u8RegData);
    tuner_mdelay(100);
    u8RegData = u8RegData | 0x1;
    qam_write_byte(u32TunerPort, Hi3137_SDR_CTRL, u8RegData);
    return HI_SUCCESS;
}

static HI_S32 demod_change_demod_clk(HI_U32 u32TunerPort, HI_U32 u32DemodClkKHz, HI_U32 u32AdcClkKHz)
{
    HI_U32 u32DemoDiv = 0;
    HI_U8  u8DemoDivInt = 0,u8DemoDivFh = 0,u8DemoDivFl = 0;
    HI_U8  u8ClkAdcL = 0,u8ClkAdcM = 0,u8ClkDemL = 0,u8ClkDemM = 0,u8ClkDemH = 0;
    HI_U8  u8InitData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(g_stXtalClk == 0)
    {
        HI_ERR_TUNER("g_stXtalClk is 0.\n");
        return HI_FAILURE;
    }

    //dem clk freq оƬȱʡֵ��64MHz
    u32DemoDiv = u32DemodClkKHz * 12 * 4096 / g_stXtalClk;
    u8DemoDivInt = u32DemoDiv / 4096;
    u8DemoDivFh = (u32DemoDiv / 256) % 16;
    u8DemoDivFl = u32DemoDiv % 256;

    //switch i2c to the xo clk
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8InitData);
    u8InitData = u8InitData & 0xFE;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);
    tuner_mdelay(5);
    //power down PLL0
    qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8InitData);
    u8InitData = u8InitData | 0x10;
    qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8InitData);

    //set pll0
    qam_write_byte(u32TunerPort,Hi3137_PLL0_FBDIV,u8DemoDivInt);
    qam_write_byte(u32TunerPort,Hi3137_PLL0_FRAC_L,u8DemoDivFl);
    qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8InitData);
    u8InitData = (u8InitData & 0xF0) | u8DemoDivFh;
    qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8InitData);

    //power up the pll
    qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8InitData);
    u8InitData = u8InitData & 0xEF;
    qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8InitData);

    //delay 5ms,waiting PLL lock
    tuner_mdelay(5);

    //switch i2c to the clk demo
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8InitData);
    u8InitData = u8InitData | 0x01;//u8InitData & 0xEF;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);

    //adc clk freq оƬȱʡֵ��32MHz
    switch(u32DemodClkKHz / u32AdcClkKHz)
    {
        case 1:
            qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL0, &u8InitData);
            u8InitData = (u8InitData & 0xC0) | 0x03;
            qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL0, u8InitData);
            break;
        case 2:
        default:
            qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL0, &u8InitData);
            u8InitData = (u8InitData & 0xC0) | 0x01;
            qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL0, u8InitData);
            break;
    }

    u8ClkAdcL = u32AdcClkKHz % 256;
    u8ClkAdcM = u32AdcClkKHz / 256;
    qam_write_byte(u32TunerPort,Hi3137_CLK_ADC_L,u8ClkAdcL);
    qam_write_byte(u32TunerPort,Hi3137_CLK_ADC_M,u8ClkAdcM);

    //reset adc ip
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8InitData);
    u8InitData = u8InitData & 0xBF;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);
    u8InitData = u8InitData | 0x40;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);

    //power up the adc,set into the work mode
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL3,&u8InitData);
    u8InitData = u8InitData | 0x30;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL3,u8InitData);
    tuner_mdelay(5);

    //demo clk
    u8ClkDemL = u32DemodClkKHz % 256;
    u8ClkDemM = (u32DemodClkKHz / 256) % 256;
    u8ClkDemH = (u32DemodClkKHz / 65536) & 0x03;

    qam_write_byte(u32TunerPort,Hi3137_CLK_DEMO_L,u8ClkDemL);
    qam_write_byte(u32TunerPort,Hi3137_CLK_DEMO_M,u8ClkDemM);
    qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8InitData);
    u8InitData = (u8InitData & 0xCF) | (u8ClkDemH << 4);
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);

    return HI_SUCCESS;
}

/*1.����IIC ͸���ĺ���  2.IQ  ��ת���� 3.TS  disable   enable����    4.����ANT_POWER������ƺ���5.����ʱ�ӻ�ͨ������ƺ���  6.*/
//��bit1��д0��д1������ȸ�λ
static HI_S32 hi3137_hot_reset(HI_U32 u32TunerPort)
{
    HI_U32  u32Dly = 8;
    HI_U8   u8InitData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8InitData);
    u8InitData = (u8InitData & 0xFC) | 0x01;
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);
    tuner_mdelay(u32Dly);
    u8InitData = (u8InitData & 0xFC) | 0x03;
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);

    return HI_SUCCESS;
}

HI_VOID hi3137_sdram_check(HI_U32 u32TunerPort)
{
    HI_U8 u8InitData = 0, u8BistRdy, u8BistOk = 0;
    HI_U8 i;

    qam_read_byte(u32TunerPort, Hi3137_SDR_CTRL, &u8InitData);
    u8InitData = u8InitData & 0xFD;   //winbond sdram
    qam_write_byte(u32TunerPort, Hi3137_SDR_CTRL, u8InitData);

    //set bist mode
    qam_read_byte(u32TunerPort, Hi3137_BIST_MODE_STATUS, &u8InitData);
    u8InitData = (u8InitData & 0xF0) | 0x05;
    qam_write_byte(u32TunerPort, Hi3137_BIST_MODE_STATUS, u8InitData);
    u8InitData = 0x1;
    qam_write_byte(u32TunerPort, Hi3137_SDRAM_BIST, u8InitData);
    //reset the bist module
    qam_read_byte(u32TunerPort, Hi3137_RSTN_CTRL, &u8InitData);
    u8InitData = (u8InitData & 0xFC) | 0x1;
    qam_write_byte(u32TunerPort, Hi3137_RSTN_CTRL, u8InitData);
    u8InitData = (u8InitData & 0xFC) | 0x3;
    qam_write_byte(u32TunerPort, Hi3137_RSTN_CTRL, u8InitData);

    for(i=0;i<20;i++)
    {
        qam_read_byte(u32TunerPort, Hi3137_BIST_MODE_STATUS, &u8InitData);
        u8BistRdy = (u8InitData >> 5) & 0x01;
        if(u8BistRdy == 1)
        {
            u8BistOk = (u8InitData >> 4) & 0x01;
            break;
        }
        //delay 5ms
        tuner_mdelay(5);
    }

    if( u8BistOk != 1)
    {
        //bist fail,change sdram
        qam_read_byte(u32TunerPort, Hi3137_SDR_CTRL, &u8InitData);
        u8InitData = u8InitData | 0x02;  //etron sdram
        qam_write_byte(u32TunerPort, Hi3137_SDR_CTRL, u8InitData);
    }
    //disable the bist
    qam_read_byte(u32TunerPort, Hi3137_BIST_MODE_STATUS, &u8InitData);
    u8InitData = (u8InitData & 0xF0);
    qam_write_byte(u32TunerPort, Hi3137_BIST_MODE_STATUS, u8InitData);
}
#if 0
static HI_S32 hi3137_get_chip_id(HI_U32 u32TunerPort,HI_U16 u16ChipID)
{
    HI_U8 u8ChipID[2] = {0};
    HI_U32 u32Return = HI_SUCCESS;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_CHIP_ID_H, &u8ChipID[0]);
    qam_read_byte(u32TunerPort, Hi3137_CHIP_ID_L, &u8ChipID[1]);
    u16ChipID = 0;

    /*** if get chip id success,chip id = 0x3137 ***/
    u16ChipID = (u8ChipID[0]<<8) + u8ChipID[1];
    if(u16ChipID != 0x3137)
    {
        return HI_FAILURE;
    }

    return u32Return;
}
#endif
static HI_S32 hi3137_get_lock_flag(HI_U32 u32TunerPort, HI3137_LOCK_FLAG_E stLockFlag)
{
    HI_U8 u8LockFlag = 0;
    HI_U8 u8Mask;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_LOCK_FLAG, &u8LockFlag);

    switch(stLockFlag)
    {
        case AGC_LOCK_FLAG:             u8Mask = 0x01;      break;
        case SYNC_LOCK_FLAG:            u8Mask = 0x02;      break;
        case SYNC_PRE_LOCK_FLAG:        u8Mask = 0x04;      break;
        case SIG_T2_LOCK_FLAG:          u8Mask = 0x08;      break;
        case TPS_T_LOCK_FLAG:           u8Mask = 0x10;      break;
        case FEC_LOCK_FLAG:             u8Mask = 0x20;      break;
        default:                        u8Mask = 0x0;       break;
    }

    if(u8LockFlag & u8Mask)
    {
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }
}

HI_S32 hi3137_init(HI_U32 u32TunerPort, HI_U8 enI2cChannel, HI_UNF_TUNER_DEV_TYPE_E enTunerDevType )
{
    HI_U8 u8InitData = 0;

    g_stI2cChannel = enI2cChannel;
    g_stTunerType = enTunerDevType;

    //cold reset
    qam_read_byte(u32TunerPort, Hi3137_RSTN_CTRL, &u8InitData);
    u8InitData = (u8InitData & 0xFC);
    qam_write_byte(u32TunerPort, Hi3137_RSTN_CTRL, u8InitData);
    tuner_mdelay(10);
    u8InitData = (u8InitData & 0xFC) | 0x03;
    qam_write_byte(u32TunerPort, Hi3137_RSTN_CTRL, u8InitData);

    return HI_SUCCESS;
}

HI_S32 hi3137_set_ter_attr(HI_U32 u32TunerPort, HI_UNF_TUNER_TER_ATTR_S *pstTerTunerAttr)
{
    HI_U32 u32ClkDemoKhz,u32ClkFecKhz,u32ClkIfKhz,u32ClkAdcKhz; /* ��λKHz */
    HI_U32 u32DemoDiv,u32FecDiv;
    HI_U8 u8DemoDivInt,u8DemoDivFh,u8DemoDivFl,u8FecDivInt,u8FecDivFh,u8FecDivFl;
    HI_U8 u8ClkDemH,u8ClkDemM,u8ClkDemL,u8ClkFecH,u8ClkFecM,u8ClkFecL,u8ClkAdcM,u8ClkAdcL,u8ClkIfH,u8ClkIfL;
    HI_U8 u8InitData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == pstTerTunerAttr)
    {
        return HI_FAILURE;
    }

    g_stXtalClk = pstTerTunerAttr->u32DemodClk;
    u32ClkDemoKhz = 60000;
    u32ClkFecKhz = 150000;
    u32ClkAdcKhz = 30000;

	switch(g_stTunerType)
	{
		case HI_UNF_TUNER_DEV_TYPE_TDA182I5A:
		case HI_UNF_TUNER_DEV_TYPE_SI2144:
			u32ClkIfKhz = 5000;
			break;
		default:
			u32ClkIfKhz = 5380;
			break;
	}

    /***
    **** symtem clock freq config ******
                                    ***/
    //dem clk freq оƬȱʡֵ��64MHz
    u32DemoDiv = u32ClkDemoKhz * 12 * 4096 / g_stXtalClk;
    u8DemoDivInt = u32DemoDiv / 4096;
    u8DemoDivFh = (u32DemoDiv / 256) % 16;
    u8DemoDivFl = u32DemoDiv % 256;
    u32FecDiv = u32ClkFecKhz * 4 *4096 / g_stXtalClk;
    u8FecDivInt = u32FecDiv / 4096;
    u8FecDivFh = (u32FecDiv / 256) % 16;
    u8FecDivFl = u32FecDiv % 256;

    //switch i2c to the xo clk
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8InitData);
    u8InitData = u8InitData & 0xFE;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);
    tuner_mdelay(5);
    //power down PLL0
    qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8InitData);
    u8InitData = u8InitData | 0x10;
    qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8InitData);

    //power down PLL1
    qam_read_byte(u32TunerPort,Hi3137_PLL1_PD,&u8InitData);
    u8InitData = u8InitData | 0x10;
    qam_write_byte(u32TunerPort,Hi3137_PLL1_PD,u8InitData);

    //set pll0
    qam_write_byte(u32TunerPort,Hi3137_PLL0_FBDIV,u8DemoDivInt);
    qam_write_byte(u32TunerPort,Hi3137_PLL0_FRAC_L,u8DemoDivFl);
    qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8InitData);
    u8InitData = (u8InitData & 0xF0) | u8DemoDivFh;
    qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8InitData);

    //set pll1
    qam_write_byte(u32TunerPort,Hi3137_PLL1_FBDIV,u8FecDivInt);
    qam_write_byte(u32TunerPort,Hi3137_PLL1_FRAC_L,u8FecDivFl);
    qam_read_byte(u32TunerPort,Hi3137_PLL1_PD,&u8InitData);
    u8InitData = (u8InitData & 0xF0) | u8FecDivFh;
    qam_write_byte(u32TunerPort,Hi3137_PLL1_PD,u8InitData);

    //power up the pll
    qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8InitData);
    u8InitData = u8InitData & 0xEF;
    qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8InitData);
    qam_read_byte(u32TunerPort,Hi3137_PLL1_PD,&u8InitData);
    u8InitData = u8InitData & 0xEF;
    qam_write_byte(u32TunerPort,Hi3137_PLL1_PD,u8InitData);

    //delay 5ms,waiting PLL lock
    tuner_mdelay(5);

    //switch i2c to the clk demo
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8InitData);
    u8InitData = u8InitData | 0x01;//u8InitData & 0xEF;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);

    //adc clk freq оƬȱʡֵ��32MHz
    switch(u32ClkDemoKhz / u32ClkAdcKhz)
    {
      /*  case 1:   //codecc, it is a fixed value: 60000/30000. can not reach. 
            qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL0, &u8InitData);
            u8InitData = (u8InitData & 0xC0) | 0x03;
            qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL0, u8InitData);
            break;*/
        case 2:
        default:
            qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL0, &u8InitData);
            u8InitData = (u8InitData & 0xC0) | 0x01;
            qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL0, u8InitData);
            break;
    }

    u8ClkAdcL = u32ClkAdcKhz % 256;
    u8ClkAdcM = u32ClkAdcKhz / 256;
    qam_write_byte(u32TunerPort,Hi3137_CLK_ADC_L,u8ClkAdcL);
    qam_write_byte(u32TunerPort,Hi3137_CLK_ADC_M,u8ClkAdcM);

    //reset adc ip
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8InitData);
    u8InitData = u8InitData & 0xBF;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);
    u8InitData = u8InitData | 0x40;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8InitData);

    //power up the adc,set into the work mode
    qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL3,&u8InitData);
    u8InitData = u8InitData | 0x30;
    qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL3,u8InitData);
    tuner_mdelay(5);

    //demo clk
    u8ClkDemL = u32ClkDemoKhz % 256;
    u8ClkDemM = (u32ClkDemoKhz / 256) % 256;
    u8ClkDemH = (u32ClkDemoKhz / 65536) & 0x03;

    qam_write_byte(u32TunerPort,Hi3137_CLK_DEMO_L,u8ClkDemL);
    qam_write_byte(u32TunerPort,Hi3137_CLK_DEMO_M,u8ClkDemM);
    qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8InitData);
    u8InitData = (u8InitData & 0xCF) | (u8ClkDemH << 4);
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);

    //fec clk
    u8ClkFecL = u32ClkFecKhz % 256;
    u8ClkFecM = (u32ClkFecKhz / 256) % 256;
    u8ClkFecH = (u32ClkFecKhz / 65536) & 0x03;

    qam_write_byte(u32TunerPort,Hi3137_CLK_FEC_L,u8ClkFecL);
    qam_write_byte(u32TunerPort,Hi3137_CLK_FEC_M,u8ClkFecM);
    qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8InitData);
    u8InitData = (u8InitData & 0x3F) | (u8ClkFecH << 6);
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);

    //IF freq
    u8ClkIfH = u32ClkIfKhz / 256;
    u8ClkIfL = u32ClkIfKhz % 256;
    qam_write_byte(u32TunerPort,Hi3137_IF_FREQ_L,u8ClkIfL);
    qam_write_byte(u32TunerPort,Hi3137_IF_FREQ_H,u8ClkIfH);

    //-------------demo��ʼ������----------------
    //agc goal
    u8InitData = 0x1c;
    qam_write_byte(u32TunerPort,Hi3137_AGC_GOAL,u8InitData);
    //agc speed
    u8InitData = 0x47;
    qam_write_byte(u32TunerPort,Hi3137_AGC_SPEED_BOUND,u8InitData);
    //p1_th
    qam_read_byte(u32TunerPort,Hi3137_P1_THRES,&u8InitData);
    u8InitData = (u8InitData & 0xC0) | 0x1D;
    qam_write_byte(u32TunerPort,Hi3137_P1_THRES,u8InitData);
    //fef_th
    u8InitData = 0x0c;
    qam_write_byte(u32TunerPort,Hi3137_FEF_TH,u8InitData);
    //cp_add_ena
    qam_read_byte(u32TunerPort,Hi3137_TS_0_SEL,&u8InitData);
    u8InitData = u8InitData  | 0xA0;
    qam_write_byte(u32TunerPort,Hi3137_TS_0_SEL,u8InitData);
    //tto
    qam_read_byte(u32TunerPort,Hi3137_OUTP_ISSY,&u8InitData);
    u8InitData = (u8InitData  &  0xC0) | 0x14;
    qam_write_byte(u32TunerPort,Hi3137_OUTP_ISSY,u8InitData);
    //iter num -- 32
    //u8InitData = 0xa4;
    //qam_write_byte(u32TunerPort,Hi3137_ITER_CTRL,u8InitData);
    //dagc ref
    u8InitData = 0x60;
    qam_write_byte(u32TunerPort,Hi3137_DAGC_REF,u8InitData);

    //L1 post iter num
    u8InitData = 0x20;
    qam_write_byte(u32TunerPort,Hi3137_ITER_NUM_POST,u8InitData);
    //L1 post cfg
    u8InitData = 0x40;
    qam_write_byte(u32TunerPort,Hi3137_SWITCH_DLY,u8InitData);
    u8InitData = 0x08;
    qam_write_byte(u32TunerPort,Hi3137_AUTO_DLY,u8InitData);
    //gate off
    u8InitData = 0x98;
    qam_write_byte(u32TunerPort,Hi3137_ITER_NUM,u8InitData);
    //c_thr_t2
    qam_read_byte(u32TunerPort,Hi3137_T2_CHK_CTRL,&u8InitData);
    u8InitData = (u8InitData & 0xFC) | 0x02;
    qam_write_byte(u32TunerPort,Hi3137_T2_CHK_CTRL,u8InitData);
    //c_pos_mod
    u8InitData = 0x78;
    qam_write_byte(u32TunerPort,Hi3137_P2_POS_MOD,u8InitData);
    //dagc speed
    u8InitData = 0x08;
    qam_write_byte(u32TunerPort,Hi3137_DAGC_SPEED,u8InitData);

    //cir threshold
    u8InitData = 0x00;
    qam_write_byte(u32TunerPort,Hi3137_ECHO_THRES,u8InitData);

    //iscr limit
    qam_read_byte(u32TunerPort,Hi3137_OUTP_LIMIT_EN,&u8InitData);
    u8InitData = u8InitData & 0xDF;
    qam_write_byte(u32TunerPort,Hi3137_OUTP_LIMIT_EN,u8InitData);
    //ts out rand
    qam_read_byte(u32TunerPort,Hi3137_OUTP_RAND,&u8InitData);
    u8InitData = u8InitData | 0x1;
    qam_write_byte(u32TunerPort,Hi3137_OUTP_RAND,u8InitData);

    qam_read_byte(u32TunerPort,0x66,&u8InitData);
    u8InitData = (u8InitData & 0xF3) | (0x1<<2);
    qam_write_byte(u32TunerPort,0x66,u8InitData);

    u8InitData = 0;
    qam_write_byte(u32TunerPort,Hi3137_IO_CTRL2,u8InitData);

    hi3137_sdram_check(u32TunerPort);

#if 0
    //ts init
    qam_read_byte(u32TunerPort,Hi3137_OUTP_TS_MODE,&u8InitData);
    if(pstTerAttr->enTSSerialPIN)
    {
        u8InitData = u8InitData | 0x04;
    }
    else
    {
        u8InitData = u8InitData & 0xFB;
    }
    //ʱ�ӱ���ѡ��
    if(pstTerAttr->enTSClkPolar)
    {
        u8InitData = u8InitData & 0xF7;
    }
    else
    {
        u8InitData = u8InitData | 0x08;
    }
    qam_write_byte(u32TunerPort,Hi3137_OUTP_TS_MODE,u8InitData);
    //�������ģʽ��ͬ���ֿ���ѡ��
    qam_read_byte(u32TunerPort,Hi3137_OUTP_MODE_SET,&u8InitData);
    if(pstTerAttr->enTSSyncHead)
    {
        u8InitData = u8InitData | 0x01;
    }
    else
    {
        u8InitData = u8InitData & 0xFE;
    }
    qam_write_byte(u32TunerPort,Hi3137_OUTP_MODE_SET,u8InitData);
#endif

    demod_clock_out_reset(u32TunerPort);
    tuner_mdelay(10);
    tuner_init(u32TunerPort);

    //------------�ȸ�λ��hot_rstn-------------------
    qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8InitData);
    u8InitData = (u8InitData & 0xFC) | 0x01;
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);
    u8InitData = (u8InitData & 0xFC) | 0x03;
    qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8InitData);

    return HI_SUCCESS;
}

HI_S32 hi3137_connect(HI_U32 u32TunerPort,TUNER_ACC_QAM_PARAMS_S *pstChannel)
{
    static HI_U32 stDemodClk = 60000;
    HI_U32 i,u32ChkTim = 50,u32SyncChk = 25,u32Return = HI_SUCCESS,u32DemodClk = 0;
    HI_S32 s32CarrOffset = 0,s32Fs = 0;
    HI_U8   u8CarrVal[2] = {0};
    HI_U8   u8BW        = 4;
    HI_U8   u8Thr       = 0;
    HI_U8   u8PosMod    = 0;
    HI_U8   u8InitData  = 0;
    HI_U8   u8RegData   = 0;
    HI_U8   u8RegData2  = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(HI_NULL == pstChannel)
    {
        return HI_FAILURE;
    }

    switch(pstChannel->u32Frequency)
    {
        case 842000:
        case 722000:
        case 778000:
        case 810000:
        case 658000:
            u32DemodClk = 61000;
            break;
        default:
            u32DemodClk = 60000;
            break;
    }

    if(stDemodClk != u32DemodClk)
    {
        stDemodClk = u32DemodClk;
        demod_change_demod_clk(u32TunerPort,stDemodClk, stDemodClk/2);
    }

    //receive bandwidth config
    switch(pstChannel->unSRBW.u32BandWidth)
    {
        case 8000:      u8BW = 0x4;     u8Thr = 2;      u8PosMod = 0x78;    s32Fs = 9143;   break;
        case 7000:      u8BW = 0x3;     u8Thr = 2;      u8PosMod = 0x78;    s32Fs = 8000;   break;
        case 6000:      u8BW = 0x2;     u8Thr = 3;      u8PosMod = 0x90;    s32Fs = 6857;   break;
        case 5000:      u8BW = 0x1;     u8Thr = 3;      u8PosMod = 0x90;    s32Fs = 5714;   break;
        case 1700:      u8BW = 0x0;     u8Thr = 3;      u8PosMod = 0x90;    s32Fs = 1845;   break;
        default:        u8BW = 0x4;     u8Thr = 2;      u8PosMod = 0x78;    s32Fs = 9143;   break;
    }
    qam_write_byte(u32TunerPort, Hi3137_BAND_WIDTH, (u8BW<<4));
    //c_thr_t2
    qam_read_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, &u8RegData);
    u8RegData = (u8RegData & 0xFC) | u8Thr;       //�ĳɻص�֮112us�ྶ��������
    qam_write_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, u8RegData);
    //c_pos_mod
    qam_write_byte(u32TunerPort, Hi3137_P2_POS_MOD, u8PosMod);

    qam_read_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, &u8RegData);
    u8RegData = u8RegData & 0x9F;
    if(pstChannel->u8DVBTMode)
    {
        u8RegData = u8RegData | (1 << 5);
    }
    qam_write_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, u8RegData);

    qam_read_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, &u8RegData);
    u8RegData = u8RegData & 0xCF;
    qam_read_byte(u32TunerPort, Hi3137_OUTP_ISSY, &u8RegData2);
    if(pstChannel->unTer.enDVBT2.enChannelAttr == HI_UNF_TUNER_TER_MODE_LITE)
    {
        u8RegData = u8RegData | (1 << 4);
        u8InitData = 0x0;
        //u32ChkTim = 80;
        u8RegData2 = 0x20;
    }
    else
    {
        u8InitData = 0x10;
    }
    qam_write_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, u8RegData);
    qam_write_byte(u32TunerPort, Hi3137_ECHO_THRES, u8InitData);
    qam_write_byte(u32TunerPort,Hi3137_OUTP_ISSY,u8RegData2);

    if(!(pstChannel->u8DVBTMode))   //��Ƶʱ����ʼ��plp����ʼ״̬��plp id�л��ŵ�setplpid�����в���
    {
        qam_read_byte(u32TunerPort,Hi3137_LOOP_BW,&u8InitData);
        u8InitData = u8InitData | 0x80;
        qam_write_byte(u32TunerPort,Hi3137_LOOP_BW,u8InitData);
        qam_read_byte(u32TunerPort,0x62,&u8InitData);
        u8InitData = u8InitData & 0xe7;
        qam_write_byte(u32TunerPort,0x62,u8InitData);

        qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
        u8RegData = u8RegData & 0xFD;
        qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);
        u8RegData = 0;
        qam_write_byte(u32TunerPort, Hi3137_PLP_ID0, u8RegData);
        u8RegData = 0x14;
        qam_write_byte(u32TunerPort, Hi3137_STATE_WAITS, u8RegData);
        //printk("<<<---DVB-T2.\n");
    }
    else
    {
        qam_read_byte(u32TunerPort,Hi3137_LOOP_BW,&u8InitData);
        u8InitData = u8InitData & 0x7f;
        qam_write_byte(u32TunerPort,Hi3137_LOOP_BW,u8InitData);
        qam_read_byte(u32TunerPort,0x62,&u8InitData);
        u8InitData = (u8InitData & 0xe7) | (0x2 << 3);
        qam_write_byte(u32TunerPort,0x62,u8InitData);

        if(pstChannel->unTer.enDVBT == HI_UNF_TUNER_TS_PRIORITY_LP)
        {
            qam_read_byte(u32TunerPort, Hi3137_AUTO_DLY, &u8RegData);
            u8RegData = u8RegData | 0x02;
            qam_write_byte(u32TunerPort, Hi3137_AUTO_DLY, u8RegData);
        }
        else
        {
            qam_read_byte(u32TunerPort, Hi3137_AUTO_DLY, &u8RegData);
            u8RegData = u8RegData & 0xFD;
            qam_write_byte(u32TunerPort, Hi3137_AUTO_DLY, u8RegData);
        }

        u8RegData = 0x16;
        qam_write_byte(u32TunerPort, Hi3137_STATE_WAITS, u8RegData);
        u32ChkTim = 25;
        u32SyncChk = 7;
        //printk("<<<---DVB-T.\n");
    }

    tuner_set_freq(u32TunerPort ,pstChannel->u32Frequency,pstChannel->unSRBW.u32BandWidth,pstChannel->u8DVBTMode);
    tuner_mdelay(20);   //???
    hi3137_hot_reset(u32TunerPort);

    //��ѯsync����
    for(i = 0;i < u32SyncChk;i++)
    {
        u32Return = hi3137_get_lock_flag(u32TunerPort, SYNC_LOCK_FLAG);

        if(u32Return == HI_SUCCESS)
        {
            break;
        }
        tuner_mdelay(20);   //??
    }

    if(i >= u32SyncChk)
    {
        HI_ERR_TUNER("hi3137 sync fail.\n");
        return HI_FAILURE;
    }

    //����tuner�ز�ƫ��
    qam_read_byte(u32TunerPort, Hi3137_CAR_OFFSET_L, &u8CarrVal[0]);
    qam_read_byte(u32TunerPort, Hi3137_CAR_OFFSET_H, &u8CarrVal[1]);
    s32CarrOffset = (u8CarrVal[1] << 8) + u8CarrVal[0];
    if(u8CarrVal[1] & 0x80)
    {
        s32CarrOffset = s32CarrOffset -65536;
    }
    s32CarrOffset = s32CarrOffset * s32Fs /(1<<18) ;   //unit KHz
    if(hi3137_abs(s32CarrOffset) > 100)//???
    {
        tuner_set_freq(u32TunerPort ,pstChannel->u32Frequency+s32CarrOffset,pstChannel->unSRBW.u32BandWidth,pstChannel->u8DVBTMode);
        hi3137_hot_reset(u32TunerPort);
    }

    //��ѯfec����
    for(i = 0;i < u32ChkTim;i++)
    {
        u32Return = hi3137_get_lock_flag(u32TunerPort, FEC_LOCK_FLAG);

        if(u32Return == HI_SUCCESS)
        {
            break;
        }
        tuner_mdelay(20);
    }

    if(i < u32ChkTim)
    {
    	/**config T/T2 auto searching,in case signal type changed from T to T2,or signal type changede from T2 to T**/
    	qam_read_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, &u8RegData);
		u8RegData = (u8RegData & 0x9F) | (2 << 5);
		qam_write_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, u8RegData);
        return HI_SUCCESS;
    }
    else
    {
        return HI_FAILURE;
    }

}

HI_S32 hi3137_get_status (HI_U32 u32TunerPort, HI_UNF_TUNER_LOCK_STATUS_E  *penTunerStatus)
{
    HI_U32 u32Return;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(HI_NULL == penTunerStatus)
    {
        return HI_FAILURE;
    }

    u32Return = hi3137_get_lock_flag(u32TunerPort,FEC_LOCK_FLAG);
    if(u32Return == HI_SUCCESS)
    {
        *penTunerStatus = HI_UNF_TUNER_SIGNAL_LOCKED;
    }
    else
    {
        *penTunerStatus = HI_UNF_TUNER_SIGNAL_DROPPED;
    }

    return HI_SUCCESS;
}

HI_VOID hi3137_read_tuner_registers(HI_U32 u32TunerPort, struct seq_file * p)
{
    HI_U8 i;
    HI_U8 u8Data = 0;

    PROC_PRINT(p,"  addr ");
    for(i = 0;i <= 0x0F;i++)
    {
        PROC_PRINT(p,"%2x ",i);
    }
    
    for(i = 0;i < 0xFF;i++)
    {
    	qam_read_byte(u32TunerPort, i, &u8Data);
    	if(i % 16 == 0)
    	{
    		PROC_PRINT(p,"\n %04x0:",i/16);
    	}
    	PROC_PRINT(p,"%2x ",u8Data);
    }
    PROC_PRINT(p,"\n");
}

HI_S32 hi3137_get_ber(HI_U32 u32TunerPort, HI_U32* pu32ber)
{
    HI_U32  u32N, u32M, u32FrameNum,u32ErrSum;
    HI_U8   u8Status[2];
    HI_U8   u8DVBT = 0;
    HI_U8   u8Parameter = 0;
    HI_U8   u8FecType, u8CodeRate;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(HI_NULL == pu32ber)
    {
        return HI_FAILURE;
    }

    memset(u8Status,0,sizeof(u8Status));
    qam_read_byte(u32TunerPort, Hi3137_FEC_BER_L, &u8Status[0]);
    qam_read_byte(u32TunerPort, Hi3137_FEC_BER_H, &u8Status[1]);
    //error sum
    u32ErrSum = (u8Status[1]<<8) | (u8Status[1]<<0);
    //frame num
    qam_read_byte(u32TunerPort, Hi3137_BER_CTRL, &u8Status[0]);
    u32FrameNum = (u8Status[0] & 0x70) >> 4;   //default = 3

    qam_read_byte(u32TunerPort, Hi3137_CHN_FFT_GI, &u8DVBT);
    if(u8DVBT & 0x80)
    {
        u32M = 204 * 8;
        switch(u32FrameNum)
        {
            case 0:     u32N = 16;          break;
            case 1:     u32N = 64;          break;
            case 2:     u32N = 256;         break;
            case 3:     u32N = 1024;        break;
            case 4:     u32N = 4096;        break;
            case 5:     u32N = 16384;       break;
            case 6:     u32N = 65536;       break;
            default:    u32N = 1024;        break;
        }
    }
    else
    {
        //FEC type and code rate
        qam_read_byte(u32TunerPort, Hi3137_PLP_PARAM, &u8Parameter);
        u8FecType = u8Parameter & 0x01;
        u8CodeRate = (u8Parameter >> 5) & 0x07;
        switch(u8CodeRate)
        {
            case 0:     u32N = (u8FecType == 1)?32400 : 7200;           break;
            case 1:     u32N = (u8FecType == 1)?38880 : 9720;           break;
            case 2:     u32N = (u8FecType == 1)?43200 : 10800;      break;
            case 3:     u32N = (u8FecType == 1)?48600 : 11800;      break;
            case 4:     u32N = (u8FecType == 1)?51840 : 12600;      break;
            case 5:     u32N = (u8FecType == 1)?54000 : 13320;      break;
            case 6:     u32N = 5400;                                    break;
            default:     u32N = 6480;                                    break;
            //default:    u32N = 32400;                                   break;
        }

        switch(u32FrameNum)
        {
            case 0:     u32M = (u8FecType == 1)?32 : 128;           break;
            case 1:     u32M = (u8FecType == 1)?64 : 256;           break;
            case 2:     u32M = (u8FecType == 1)?128 : 512;          break;
            case 3:     u32M = (u8FecType == 1)?256 : 1024;     break;
            case 4:     u32M = (u8FecType == 1)?512 : 2048;     break;
            case 5:     u32M = (u8FecType == 1)?1024 : 4096;        break;
            case 6:     u32M = (u8FecType == 1)?2048 : 8192;        break;
            default:    u32M = (u8FecType == 1)?4096 : 16384;       break;
        }
    }

	pu32ber[0] = 1000000000 / (u32N * u32M) * u32ErrSum;
	pu32ber[1] = 0;
    pu32ber[2] = 9;

    return HI_SUCCESS;
}

HI_S32 hi3137_get_snr(HI_U32 u32TunerPort, HI_U32* pu32SNR)
{
    HI_U8 u8Snr[2] = {0};
    HI_U32 u32CN;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(HI_NULL == pu32SNR)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_SNR_L, &u8Snr[0]);
    qam_read_byte(u32TunerPort, Hi3137_SNR_H, &u8Snr[1]);
    u32CN = u8Snr[1] * 256 + u8Snr[0];
    *pu32SNR = u32CN;

    return HI_SUCCESS;
}

HI_S32 hi3137_tp_scan(HI_U32 u32TunerPort,HI_UNF_TUNER_TER_SCAN_ATTR_S *pstScanAttr, HI_UNF_TUNER_TER_TPINFO_S *pstTpInfo)
{
    HI_UNF_TUNER_TER_TPINFO_S stScanResult;
    HI_U8 u8InitData = 0;
    HI_U8 u8RegData = 0;
    HI_U8 u8ChkTim = 30;
    HI_U8 u8NumPlp = 0;
    HI_U8 u8PlpId = 0;
    HI_U8 u8PlpGrpId = 0;
    HI_U8 u8PlpType = 0;
    HI_U8 i,j;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(HI_NULL== pstScanAttr)
    {
        return HI_FAILURE;
    }

    if(HI_NULL == pstTpInfo)
    {
        return HI_FAILURE;
    }

    memset(&stScanResult,0,sizeof(HI_UNF_TUNER_TER_TPINFO_S));

    if(pstScanAttr->bScanLite)
    {
        //scan base and lite
        qam_read_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, &u8InitData);
        u8InitData = (u8InitData & 0xCF) | (2 << 4);
        qam_write_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, u8InitData);
    }
    else
    {
        //only scan base,set u8ChkTim 15
        qam_read_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, &u8InitData);
        u8InitData = u8InitData & 0xCF;
        qam_write_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, u8InitData);

        u8ChkTim = 15;
    }

    switch(pstScanAttr->enScanMode)
    {
        case HI_UNF_TUNER_TER_SCAN_DVB_T2:
            qam_read_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, &u8InitData);
            u8InitData = u8InitData & 0x9F;
            qam_write_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, u8InitData);
            break;
        case HI_UNF_TUNER_TER_SCAN_DVB_T:
            qam_read_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, &u8InitData);
            u8InitData = (u8InitData & 0x9F) | (1 << 5);
            qam_write_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, u8InitData);

            //only scan dvb-t,set u8ChkTim 6
            u8ChkTim = 6;
            break;
        case HI_UNF_TUNER_TER_SCAN_DVB_T_T2_ALL:
            qam_read_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, &u8InitData);
            u8InitData = (u8InitData & 0x9F) | (2 << 5);
            qam_write_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, u8InitData);
            break;
        default:
            HI_ERR_TUNER("set scan attr error.\n");
            return HI_FAILURE;
    }

    //plp init
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8InitData);
    u8InitData = u8InitData & 0xFD;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8InitData);
    u8InitData = 0;
    qam_write_byte(u32TunerPort, Hi3137_PLP_ID0, u8InitData);

    //cfg tuner freq
    tuner_set_freq(u32TunerPort,pstScanAttr->u32Frequency,pstScanAttr->u32BandWidth,pstScanAttr->enScanMode);

    //cfg bandwidth
    switch(pstScanAttr->u32BandWidth)
    {
        case 1700:
            qam_read_byte(u32TunerPort, Hi3137_BAND_WIDTH, &u8InitData);
            u8InitData = u8InitData & 0x0F;
            qam_write_byte(u32TunerPort, Hi3137_BAND_WIDTH, u8InitData);
            break;
        case 5000:
            qam_read_byte(u32TunerPort, Hi3137_BAND_WIDTH, &u8InitData);
            u8InitData = (u8InitData & 0x0F) | (1 << 4);
            qam_write_byte(u32TunerPort, Hi3137_BAND_WIDTH, u8InitData);
            break;
        case 6000:
            qam_read_byte(u32TunerPort, Hi3137_BAND_WIDTH, &u8InitData);
            u8InitData = (u8InitData & 0x0F) | (2 << 4);
            qam_write_byte(u32TunerPort, Hi3137_BAND_WIDTH, u8InitData);
            break;
        case 7000:
            qam_read_byte(u32TunerPort, Hi3137_BAND_WIDTH, &u8InitData);
            u8InitData = (u8InitData & 0x0F) | (3 << 4);
            qam_write_byte(u32TunerPort, Hi3137_BAND_WIDTH, u8InitData);
            break;
        case 8000:
            qam_read_byte(u32TunerPort, Hi3137_BAND_WIDTH, &u8InitData);
            u8InitData = (u8InitData & 0x0F) | (4 << 4);
            qam_write_byte(u32TunerPort, Hi3137_BAND_WIDTH, u8InitData);
            break;
        default:
            HI_ERR_TUNER("bandwidth set err.\n");
            return HI_FAILURE;
    }

    hi3137_hot_reset(u32TunerPort);

    for(i=0;i<u8ChkTim;i++)
    {
        tuner_mdelay(50);
        qam_read_byte(u32TunerPort, LOCK_FLAG, &u8InitData);
        if(u8InitData & 0x18)
        {
            break;
        }
    }

    if(i == u8ChkTim)
    {
        HI_ERR_TUNER("scan fail.\n");
        return HI_FAILURE;
    }

    //query signal info and re-init u8ChkTim
    qam_read_byte(u32TunerPort, Hi3137_CHN_FFT_GI, &u8InitData);
    if(u8InitData & 0x80)  //dvb-t
    {
        u8ChkTim = 6;
        stScanResult.u8DVBTMode = 1;
    }
    else   //dvb-t2
    {
        stScanResult.u8DVBTMode = 0;
        qam_read_byte(u32TunerPort, Hi3137_P1_SIGNAL, &u8InitData);
        u8InitData = (u8InitData & 0x70) >> 4;
        switch(u8InitData)
        {
            case 0:
            case 1:   //base mode
                u8ChkTim = 8;
                stScanResult.enChannelAttr = HI_UNF_TUNER_TER_MODE_BASE;
                break;
            case 3:   //lite mode
            case 4:
                u8ChkTim = 25;
                stScanResult.enChannelAttr = HI_UNF_TUNER_TER_MODE_LITE;
                break;
            default:
                HI_ERR_TUNER("dvb-t2 mode fail.\n");
                return HI_FAILURE;
        }
    }

    for(i=0;i<u8ChkTim;i++)
    {
        tuner_mdelay(50);
        qam_read_byte(u32TunerPort, LOCK_FLAG, &u8InitData);
        if(u8InitData & 0x20)
        {
            //fec lock
            if(stScanResult.u8DVBTMode == 1)   //dvb-t
            {
                qam_read_byte(u32TunerPort, Hi3137_TPS_DVBT, &u8InitData);
                if(u8InitData & 0x30)  //�ֲ�ģʽ
                {
                    stScanResult.u8DVBTHier = 1;
                    stScanResult.u8ProgNum += 2;
                }
                else   //�Ƿֲ�ģʽ
                {
                    stScanResult.u8DVBTHier = 0;
                    stScanResult.u8ProgNum += 1;
                }
            }
            else   //dvb-t2
            {
                qam_read_byte(u32TunerPort, Hi3137_NUM_PLP, &u8NumPlp);
                qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8InitData);
                u8InitData = u8InitData | 0x1;
                qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8InitData);
                stScanResult.u8ProgNum += u8NumPlp;
                for(j=0;j<u8NumPlp;j++)
                {
                    qam_write_byte(u32TunerPort, Hi3137_PLP_ID0, j);
                    qam_read_byte(u32TunerPort, Hi3137_PLP_ID, &u8PlpId);
                    qam_read_byte(u32TunerPort, Hi3137_PLP_TYPE, &u8PlpType);
                    qam_read_byte(u32TunerPort, Hi3137_PLP_GRP_ID, &u8PlpGrpId);
                    stScanResult.enPlpAttr[j].u8PlpIndex = j;
                    stScanResult.enPlpAttr[j].u8PlpId = u8PlpId;
                    stScanResult.enPlpAttr[j].u8PlpGrpId = u8PlpGrpId;
                    u8PlpType = (u8PlpType & 0xe0) >> 5;
                    switch(u8PlpType)
                    {
                        case 0:
                            stScanResult.enPlpAttr[j].enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_COM;
                            break;
                        case 1:
                            stScanResult.enPlpAttr[j].enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_DAT1;
                            break;
                        case 2:
                            stScanResult.enPlpAttr[j].enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_DAT2;
                            break;
                        default:
                            HI_ERR_TUNER("plp type unknow.\n");
                            break;
                    }
                }

                if(pstScanAttr->bScanLite)
                {
                    qam_read_byte(u32TunerPort, Hi3137_P1_SIGNAL, &u8InitData);
                    qam_read_byte(u32TunerPort, Hi3137_PP_VERSION, &u8RegData);
                    if(((u8InitData & 0x01) == 1) && ((u8RegData & 0x0F) == 2))   //P1_SIGNAL[0]=1 && PP_VERSION[t2_version]=2
                    {
                        stScanResult.enChannelMode = HI_UNF_TUNER_TER_MIXED_CHANNEL;
                    }
                    else
                    {
                        stScanResult.enChannelMode = HI_UNF_TUNER_TER_PURE_CHANNEL;
                    }
                }
                else
                    stScanResult.enChannelMode = HI_UNF_TUNER_TER_PURE_CHANNEL;

            }

            break;
        }
    }

    if(i == u8ChkTim)
    {
        HI_ERR_TUNER("fec not lock!\n");
        return HI_FAILURE;
    }

    if((stScanResult.u8DVBTMode == 0) && (stScanResult.enChannelMode == HI_UNF_TUNER_TER_MIXED_CHANNEL))
    {
        qam_read_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, &u8InitData);
        u8InitData = u8InitData & 0x9F;
        qam_write_byte(u32TunerPort, Hi3137_MAN_RST_CTRL1, u8InitData);

        qam_read_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, &u8InitData);
        if(stScanResult.enChannelAttr == HI_UNF_TUNER_TER_MODE_BASE)
        {
            u8InitData = (u8InitData & 0xCF) | (1 << 4);
            u8ChkTim = 25;
        }
        else if(stScanResult.enChannelAttr == HI_UNF_TUNER_TER_MODE_LITE)
        {
            u8InitData = u8InitData & 0xCF;
            u8ChkTim = 8;
        }
        else
        {
            HI_ERR_TUNER("channel attr unknown.\n");
        }
        qam_write_byte(u32TunerPort, Hi3137_T2_CHK_CTRL, u8InitData);

        hi3137_hot_reset(u32TunerPort);
        for(i = 0;i < u8ChkTim;i++)
        {
            tuner_mdelay(50);
            qam_read_byte(u32TunerPort, LOCK_FLAG, &u8InitData);
            if(u8InitData & 0x08)
            {
                break;
            }
        }

        if(i == u8ChkTim)
        {
            HI_ERR_TUNER("dvb-t2 not lock!\n");
            return HI_FAILURE;
        }

        for(i = 0;i < u8ChkTim;i++)
        {
            tuner_mdelay(50);
            qam_read_byte(u32TunerPort, LOCK_FLAG, &u8InitData);
            if(u8InitData & 0x20)
            {
                break;
            }
        }

        if(i == u8ChkTim)
        {
            HI_ERR_TUNER("dvb-t2 fec not lock!\n");
            return HI_FAILURE;
        }

        qam_read_byte(u32TunerPort, Hi3137_NUM_PLP, &u8NumPlp);
        qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8InitData);
        u8InitData = u8InitData | 0x1;
        qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8InitData);
        for(i=0,j=stScanResult.u8ProgNum;i<u8NumPlp;i++,j++)
        {
            qam_write_byte(u32TunerPort, Hi3137_PLP_ID0, i);
            qam_read_byte(u32TunerPort, Hi3137_PLP_ID, &u8PlpId);
            qam_read_byte(u32TunerPort, Hi3137_PLP_TYPE, &u8PlpType);
            qam_read_byte(u32TunerPort, Hi3137_PLP_GRP_ID, &u8PlpGrpId);
            stScanResult.enPlpAttr[j].u8PlpId = u8PlpId;
            stScanResult.enPlpAttr[j].u8PlpGrpId = u8PlpGrpId;
            u8PlpType = (u8PlpType & 0xe0) >> 5;
            switch(u8PlpType)
            {
                case 0:
                    stScanResult.enPlpAttr[j].enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_COM;
                    break;
                case 1:
                    stScanResult.enPlpAttr[j].enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_DAT1;
                    break;
                case 2:
                    stScanResult.enPlpAttr[j].enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_DAT2;
                    break;
                default:
                    HI_ERR_TUNER("plp type unknow.\n");
                    break;
            }
        }
        stScanResult.u8ProgNum += u8NumPlp;
    }

    memcpy(pstTpInfo ,&stScanResult, sizeof(HI_UNF_TUNER_TER_TPINFO_S));

    return HI_SUCCESS;
}

HI_S32 hi3137_set_ts_type(HI_U32 u32TunerPort, HI_UNF_TUNER_OUPUT_MODE_E enTsType)
{
    HI_U8 u8InitData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_OUTP_TS_MODE, &u8InitData);
    switch (enTsType)
    {
        case HI_UNF_TUNER_OUTPUT_MODE_SERIAL:
            u8InitData = u8InitData & 0xFC;
            break;
        case HI_UNF_TUNER_OUTPUT_MODE_SERIAL_2BIT:
            u8InitData = u8InitData & 0xFE;
            u8InitData = u8InitData | 0x06;
            break;
        case HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A:
        default:
            u8InitData = u8InitData | 0x01;
            break;
    }

    //������Чʱ������ʱ��
    u8InitData = u8InitData | 0x10;

    qam_write_byte(u32TunerPort, Hi3137_OUTP_TS_MODE, u8InitData);

    return HI_SUCCESS;
}

HI_S32 hi3137_TS_out_enable(HI_U32 u32TunerPort)
{
    return HI_SUCCESS;
}

HI_S32 hi3137_TS_out_disable(HI_U32 u32TunerPort)
{
    return HI_SUCCESS;
}

HI_S32 hi3137_set_ts_out(HI_U32 u32TunerPort, HI_UNF_TUNER_TSOUT_SET_S *pstTSOut)
{
    HI_U8 u8Temp = 0, i;

    if(HI_NULL == pstTSOut)
    {
        return HI_FAILURE;
    }

    /* Check tuner port and init. */
    if (u32TunerPort >= TUNER_NUM)
    {
        HI_ERR_TUNER("Bad u32TunerPort\n");
        return HI_FAILURE;
    }

    for (i = 0; i < MAX_TS_LINE; i++)
    {
        if (HI_UNF_TUNER_OUTPUT_BUTT <= pstTSOut->enTSOutput[i])
        {
            HI_ERR_TUNER("Error pin define!\n");
            return HI_FAILURE;
        }
    }

    qam_read_byte(u32TunerPort, Hi3137_TS_0_SEL, &u8Temp);
    u8Temp = u8Temp & 0xf0;
    u8Temp = u8Temp | (pstTSOut->enTSOutput[0] & 0xf);
    qam_write_byte(u32TunerPort, Hi3137_TS_0_SEL, u8Temp);

    qam_write_byte(u32TunerPort, Hi3137_TS_A9_SEL, ((pstTSOut->enTSOutput[10]& 0xf)<<4) | pstTSOut->enTSOutput[9]);/*config ts_out_10&9bit*/
    qam_write_byte(u32TunerPort, Hi3137_TS_87_SEL, ((pstTSOut->enTSOutput[8]& 0xf)<<4) | pstTSOut->enTSOutput[7]);/*config ts_out_8&7bit*/
    qam_write_byte(u32TunerPort, Hi3137_TS_65_SEL, ((pstTSOut->enTSOutput[6]& 0xf)<<4) | pstTSOut->enTSOutput[5]);/*config ts_out_6&5bit*/
    qam_write_byte(u32TunerPort, Hi3137_TS_43_SEL, ((pstTSOut->enTSOutput[4]& 0xf)<<4) | pstTSOut->enTSOutput[3]);/*config ts_out_4&3bit*/
    qam_write_byte(u32TunerPort, Hi3137_TS_21_SEL, ((pstTSOut->enTSOutput[2]& 0xf)<<4) | pstTSOut->enTSOutput[1]);/*config ts_out_2&1bit*/

    s_stSatTunerResumeInfo[u32TunerPort].bSetTsOut = HI_TRUE;
    memcpy(&s_stSatTunerResumeInfo[u32TunerPort].stTsOut, pstTSOut, sizeof(HI_UNF_TUNER_TSOUT_SET_S));

    return HI_SUCCESS;
}


HI_S32 hi3137_get_signal_strength(HI_U32 u32TunerPort, HI_U32* pu32SignalStrength)
{
    HI_U32 u32Agc_Ctrl,u32AgcPow;
    HI_U8  u8AgcRd[2] = {0, 0};

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == pu32SignalStrength)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_AGC_CTRL_L,&u8AgcRd[0]);
    qam_read_byte(u32TunerPort, Hi3137_AGC_CTRL_H,&u8AgcRd[1]);
    u32Agc_Ctrl = (u8AgcRd[0] & 0x0F) + u8AgcRd[1] * 16;

    if(u32Agc_Ctrl >= 3200)
        u32AgcPow = 0;
    else if(u32Agc_Ctrl <= 640)
        u32AgcPow = 99;
    else
        u32AgcPow = 124 - u32Agc_Ctrl*80/2048;

    pu32SignalStrength[1] = u32AgcPow;

    return HI_SUCCESS;
}

HI_S32 hi3137_config_i2c_out(HI_U32 u32TunerPort)
{
    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    (HI_VOID)qam_write_byte(u32TunerPort, 0x2d,1);

    return HI_SUCCESS;
}

HI_S32 hi3137_config_i2c_close(HI_U32 u32TunerPort)
{
	HI_U8 u8temp;
    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    (HI_VOID)qam_read_byte(u32TunerPort, 0x2c,&u8temp);

    return HI_SUCCESS;
}

HI_S32 hi3137_get_signal_info(HI_U32 u32TunerPort, HI_UNF_TUNER_SIGNALINFO_S *pstInfo)
{
    HI_S32  S32Ret;
    HI_U8   u8Register0 = 0;
    HI_U8   u8Register1 = 0;
    HI_U8   u8Register2 = 0;
    HI_U8   u8Status    = 0;
    HI_U8   u8DVBT,u8Grd,u8FFT,u8Cons,u8CR,u8Hier,u8CrL,u8BW,u8FEC,u8Rotation;
    HI_U8   u8PLP_Type,u8PP;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(HI_NULL == pstInfo)
    {
        return HI_FAILURE;
    }

    S32Ret = hi3137_get_lock_flag(u32TunerPort, FEC_LOCK_FLAG);
    if (HI_SUCCESS != S32Ret)
    {
        HI_ERR_TUNER("hi3137 not locked\n");
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_CHN_FFT_GI, &u8Status);
    u8DVBT = u8Status & 0x80;
    if (u8DVBT)
    {
        pstInfo->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;

        qam_read_byte(u32TunerPort, Hi3137_TPS_DVBT, &u8Register0);  //{mod,hier,indepth,cod}
        qam_read_byte(u32TunerPort, Hi3137_CHN_FFT_GI, &u8Register1);  //{dvbt,spec,fft_size,gi_mode}
        qam_read_byte(u32TunerPort, Hi3137_CODE_RATE_DVBT, &u8Register2);
        u8Grd = (u8Register1 & 0x3);
        u8Cons = (u8Register0 & 0xc0) >> 6;
        u8FFT = (u8Register1 & 0x38) >> 3;
        u8CR = (u8Register0 &0x7);
        u8Hier = (u8Register0 & 0x30) >> 4;
        u8CrL = (u8Register2 & 0x7);

        switch (u8Grd)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_32;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_16;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_8;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_4;
                break;
        }

        switch (u8Cons)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QPSK;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QAM_16;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QAM_64;
                break;
        }

        switch (u8FFT)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_1K;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_2K;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_4K;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_8K;
                break;
        }

        switch (u8CR)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_1_2;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_2_3;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_3_4;
                break;
            case 3:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_5_6;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_7_8;
                break;
        }

        switch (u8Hier)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enHierMod = HI_UNF_TUNER_FE_HIERARCHY_NO;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enHierMod = HI_UNF_TUNER_FE_HIERARCHY_ALHPA1;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enHierMod = HI_UNF_TUNER_FE_HIERARCHY_ALHPA2;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enHierMod = HI_UNF_TUNER_FE_HIERARCHY_ALHPA4;
                break;
        }

        switch (u8CrL)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enLowPriFECRate = HI_UNF_TUNER_FE_FEC_1_2;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enLowPriFECRate = HI_UNF_TUNER_FE_FEC_2_3;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enLowPriFECRate = HI_UNF_TUNER_FE_FEC_3_4;
                break;
            case 3:
                pstInfo->unSignalInfo.stTer.enLowPriFECRate = HI_UNF_TUNER_FE_FEC_5_6;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enLowPriFECRate = HI_UNF_TUNER_FE_FEC_7_8;
                break;
        }
    }
    else
    {
        pstInfo->enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;

        qam_read_byte(u32TunerPort, Hi3137_TPS, &u8Register0);  //{mod,hier,indepth,cod}
        u8Grd = (u8Register0 & 0x1c) >> 2;
        u8BW = (u8Register0 & 0x20) >>5;
        switch (u8Grd)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_32;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_16;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_8;
                break;
            case 3:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_4;
                break;
            case 4:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_1_128;
                break;
            case 5:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_19_128;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enGuardIntv = HI_UNF_TUNER_FE_GUARD_INTV_19_256;
                break;
        }

        if (u8BW)
        {
             pstInfo->unSignalInfo.stTer.enCarrierMode = HI_UNF_TUNER_TER_EXTEND_CARRIER;
        }
        else
        {
            pstInfo->unSignalInfo.stTer.enCarrierMode = HI_UNF_TUNER_TER_NORMAL_CARRIER;
        }

        qam_read_byte(u32TunerPort, Hi3137_CHN_FFT_GI, &u8Register1);  //{dvbt,spec,fft_size,gi_mode}
        u8FFT = (u8Register1 & 0x38) >> 3;
        switch (u8FFT)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_1K;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_2K;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_4K;
                break;
            case 3:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_8K;
                break;
            case 4:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_16K;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enFFTMode = HI_UNF_TUNER_FE_FFT_32K;
                break;
        }

        qam_read_byte(u32TunerPort, Hi3137_PLP_PARAM, &u8Register0);
        u8CR = (u8Register0 &0xe0) >> 5;
        u8FEC = (u8Register0 & 0x1);
        u8Rotation = (u8Register0 &0x2) >>1;
        u8Cons = (u8Register0 & 0x1c) >> 2;
        if (u8Rotation)
        {
            pstInfo->unSignalInfo.stTer.enConstellationMode = HI_UNF_TUNER_CONSTELLATION_ROTATION;
        }
        else
        {
            pstInfo->unSignalInfo.stTer.enConstellationMode = HI_UNF_TUNER_CONSTELLATION_STANDARD;
        }

        if (u8FEC)
        {
            pstInfo->unSignalInfo.stTer.enFECFrameMode = HI_UNF_TUNER_TER_FEC_FRAME_NORMAL;
        }
        else
        {
            pstInfo->unSignalInfo.stTer.enFECFrameMode = HI_UNF_TUNER_TER_FEC_FRAME_SHORT;
        }

        switch (u8Cons)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QPSK;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QAM_16;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QAM_64;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enModType = HI_UNF_MOD_TYPE_QAM_256;
                break;
        }

        switch (u8CR)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_1_2;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_3_5;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_2_3;
                break;
            case 3:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_3_4;
                break;
            case 4:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_4_5;
                break;
            case 5:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_5_6;
                break;
            case 6:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_1_3;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enFECRate = HI_UNF_TUNER_FE_FEC_2_5;
                break;
        }

        qam_read_byte(u32TunerPort, Hi3137_PLP_TYPE, &u8Register0);
        u8PLP_Type = (u8Register0 & 0xe0) >> 5;
        switch (u8PLP_Type)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enPLPType = HI_UNF_TUNER_T2_PLP_TYPE_COM;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enPLPType = HI_UNF_TUNER_T2_PLP_TYPE_DAT1;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enPLPType = HI_UNF_TUNER_T2_PLP_TYPE_DAT2;
                break;
        }

        qam_read_byte(u32TunerPort, Hi3137_PP_VERSION, &u8Register0);
        u8PP = (u8Register0 & 0xf0) >> 4;
        switch (u8PP)
        {
            case 0:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP1;
                break;
            case 1:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP2;
                break;
            case 2:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP3;
                break;
            case 3:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP4;
                break;
            case 4:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP5;
                break;
            case 5:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP6;
                break;
            case 6:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP7;
                break;
            default:
                pstInfo->unSignalInfo.stTer.enPilotPattern = HI_UNF_TUNER_T2_PILOT_PATTERN_PP8;
                break;
        }
    }
    return HI_SUCCESS;
}

HI_S32 hi3137_setplpid(HI_U32 u32TunerPort, HI_U8 u8PLpId, HI_U32 u32Mode)
{
    HI_U8   u8PlpNum    = 0;
    HI_U8   u8DataPlpId = 0;
    HI_U8   u8RegData   = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if (u32Mode > 1)
    {
        return HI_FAILURE;
    }

    //plp��ģʽ
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData | 0x1;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);
    qam_read_byte(u32TunerPort, Hi3137_NUM_PLP, &u8PlpNum);

    if (u8PLpId < u8PlpNum )
    {
        u8DataPlpId = u8PLpId;
    }
    else
    {
        u8DataPlpId = 0;
    }

    qam_write_byte(u32TunerPort, Hi3137_PLP_ID0, u8DataPlpId);

    if (!u32Mode)   //�����л�plpģʽʱ������Ҫhot reset
    {
        qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
        u8RegData = u8RegData & 0xFE;
        qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);
        hi3137_hot_reset(u32TunerPort);
    }

    return HI_SUCCESS;
}

HI_S32 hi3137_set_common_plp_id(HI_U32 u32TunerPort, HI_U8 u8PLpId)
{
    HI_U8   u8PlpNum    = 0;
    HI_U8   u8ComPlpId  = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_NUM_PLP, &u8PlpNum);
    if (u8PLpId < u8PlpNum)
    {
        u8ComPlpId = u8PLpId;
    }
    else
    {
        u8ComPlpId = 0;
    }

    qam_write_byte(u32TunerPort, Hi3137_PLP_ID1, u8ComPlpId);

    return HI_SUCCESS;
}

HI_S32 hi3137_set_common_plp_combination(HI_U32 u32TunerPort, HI_U8 u8ComPlpEna)
{
    HI_U8 u8InitData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if(u8ComPlpEna > 1)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8InitData);
    u8InitData = (u8InitData & 0xFD) | (u8ComPlpEna << 1);
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8InitData);

    return HI_SUCCESS;
}

HI_S32 hi3137_get_freq_symb_offset(HI_U32 u32TunerPort, HI_U32 * pu32Freq, HI_U32 * pu32Symb)
{
    HI_U16  u16Err  = 0;
    HI_U16  u16Fs   = 0;
    HI_U8   u8Status[2] = {0, 0};
    HI_U8   u8BW    = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == pu32Freq)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == pu32Symb)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_BAND_WIDTH, &u8BW);
    u8BW = (u8BW >> 4);

    qam_read_byte(u32TunerPort, Hi3137_CAR_OFFSET_L, &u8Status[0]);
    qam_read_byte(u32TunerPort, Hi3137_CAR_OFFSET_H, &u8Status[1]);
    u16Err = u8Status[1] * 256 + u8Status[0];

    switch(u8BW)
    {
        case 0:     u16Fs = 1845;       break;
        case 1:     u16Fs = 5714;       break;
        case 2:     u16Fs = 6857;       break;
        case 3:     u16Fs = 8000;       break;
        case 4:     u16Fs = 9143;       break;
        default:    u16Fs = 9143;       break;
    }

    *pu32Freq = (u16Err << 16) + u16Fs;

    //��ȡ���������洢
    qam_read_byte(u32TunerPort, Hi3137_TIM_LOOP_L, &u8Status[0]);
    qam_read_byte(u32TunerPort, Hi3137_TIM_LOOP_H, &u8Status[1]);
    u16Err = u8Status[1] * 256 + u8Status[0];
    qam_read_byte(u32TunerPort, Hi3137_TIM_OFFSET, &u8Status[0]);
    *pu32Symb = (u16Err << 16) + u8Status[0];

    return HI_SUCCESS;
}

HI_VOID hi3137_connect_timeout(HI_U32 u32ConnectTimeout)
{
    return;
}

HI_S32 hi3137_get_plp_num(HI_U32 u32TunerPort, HI_U8 *pu8PLPNum)
{
    HI_U8   u8MumPlp    = 0;
    HI_U8   u8RegData   = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == pu8PLPNum)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData | 0x01;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    qam_read_byte(u32TunerPort, Hi3137_NUM_PLP, &u8MumPlp);

    //close the plp read mode
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData & 0xFE;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    *pu8PLPNum = u8MumPlp;

    return HI_SUCCESS;
}

HI_S32 hi3137_get_current_plp_type(HI_U32 u32TunerPort, HI_UNF_TUNER_T2_PLP_TYPE_E *pstPLPType)
{
    HI_UNF_TUNER_T2_PLP_TYPE_E enPlpType;
    HI_U8   u8PlpType   = 0;
    HI_U8   u8RegData   = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    if (HI_NULL == pstPLPType)
    {
        return HI_FAILURE;
    }

    //qam_read_byte(u32TunerPort, Hi3137_NUM_PLP, &u8NumPlp);
    //open the plp read mode,only read the plp parameter,do not change the plp being processed by the demod
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData | 0x01;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    qam_read_byte(u32TunerPort, Hi3137_PLP_TYPE, &u8RegData);
    u8PlpType = (u8RegData & 0xe0) >> 5;
    if(u8PlpType == 0)
    {
        enPlpType = HI_UNF_TUNER_T2_PLP_TYPE_COM;
    }
    else if(u8PlpType == 1)
    {
        u8PlpType = HI_UNF_TUNER_T2_PLP_TYPE_DAT1;
    }
    else
    {
        u8PlpType = HI_UNF_TUNER_T2_PLP_TYPE_DAT2;
    }

    //close the plp read mode
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData & 0xFE;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    *pstPLPType = u8PlpType;

    return HI_SUCCESS;
}

HI_S32 hi3137_get_plp_id(HI_U32 u32TunerPort, HI_U8 *u8PlpId)
{
    HI_U8   u8DataPlpId = 0;
    HI_U8   u8RegData   = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData | 0x01;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    qam_read_byte(u32TunerPort, Hi3137_PLP_ID, &u8DataPlpId);

    //close the plp read mode
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData & 0xFE;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    *u8PlpId = u8DataPlpId;

    return HI_SUCCESS;
}

HI_S32 hi3137_get_plp_group_id(HI_U32 u32TunerPort, HI_U8 *u8GrpPlpId)
{
    HI_U8   u8PlpGrp    = 0;
    HI_U8   u8RegData   = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData | 0x01;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    qam_read_byte(u32TunerPort, Hi3137_PLP_GRP_ID, &u8PlpGrp);

    //close the plp read mode
    qam_read_byte(u32TunerPort, Hi3137_PLP_CTRL, &u8RegData);
    u8RegData = u8RegData & 0xFE;
    qam_write_byte(u32TunerPort, Hi3137_PLP_CTRL, u8RegData);

    *u8GrpPlpId = u8PlpGrp;

    return HI_SUCCESS;
}

HI_S32 hi3137_set_antena_power(HI_U32 u32TunerPort, HI_UNF_TUNER_TER_ANTENNA_POWER_E enPower)
{
    HI_U8 u8RegData = 0;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    qam_read_byte(u32TunerPort, Hi3137_IO_CTRL4, &u8RegData);
    u8RegData = u8RegData & 0xFD;
    u8RegData = (u8RegData & 0x3F) | (3<<6);

    switch(enPower)
    {
        case HI_UNF_TUNER_TER_ANTENNA_POWER_OFF:
            u8RegData = u8RegData & 0xDF;
            break;
        case HI_UNF_TUNER_TER_ANTENNA_POWER_ON:
            u8RegData = u8RegData | 0x20;
            break;
        default:
            HI_ERR_TUNER("antena power value err.\n");
            return HI_FAILURE;
    }
    qam_write_byte(u32TunerPort, Hi3137_IO_CTRL4, u8RegData);

    return HI_SUCCESS;
}

HI_S32 hi3137_standby(HI_U32 u32TunerPort, HI_U32 u32Status)
{
    HI_U8 u8RegData = 0;
    HI_UNF_TUNER_DEMOD_STATUS_E enStatus;

    if (u32TunerPort >= TUNER_NUM)
    {
        return HI_FAILURE;
    }

    enStatus = (HI_UNF_TUNER_DEMOD_STATUS_E)u32Status;

    switch(enStatus)
    {
        case HI_UNF_TUNER_DEMODE_WAKE_UP:
            //power up PLL0
            qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8RegData);
            u8RegData = u8RegData & 0xEF;
            qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8RegData);

            //power up PLL1
            qam_read_byte(u32TunerPort,Hi3137_PLL1_PD,&u8RegData);
            u8RegData = u8RegData & 0xEF;
            qam_write_byte(u32TunerPort,Hi3137_PLL1_PD,u8RegData);

            //switch i2c from xo to pll
            qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8RegData);
            u8RegData = u8RegData | 0x1;
            qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8RegData);

            //realse hi3137 from hot reset
            qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8RegData);
            u8RegData = (u8RegData & 0xFC) | 0x03;
            qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8RegData);
            break;
        case HI_UNF_TUNER_DEMODE_STANDBY:
            //enable hi3137 into hot reset
            qam_read_byte(u32TunerPort,Hi3137_RSTN_CTRL,&u8RegData);
            u8RegData = (u8RegData & 0xFC) | 0x01;
            qam_write_byte(u32TunerPort,Hi3137_RSTN_CTRL,u8RegData);

            //switch i2c from pll to xo
            qam_read_byte(u32TunerPort,Hi3137_ADC_CTRL1,&u8RegData);
            u8RegData = u8RegData & 0xFE;
            qam_write_byte(u32TunerPort,Hi3137_ADC_CTRL1,u8RegData);

            //power down PLL0
            qam_read_byte(u32TunerPort,Hi3137_PLL0_PD,&u8RegData);
            u8RegData = u8RegData | 0x10;
            qam_write_byte(u32TunerPort,Hi3137_PLL0_PD,u8RegData);

            //power down PLL1
            qam_read_byte(u32TunerPort,Hi3137_PLL1_PD,&u8RegData);
            u8RegData = u8RegData | 0x10;
            qam_write_byte(u32TunerPort,Hi3137_PLL1_PD,u8RegData);
            break;
        default:
            HI_ERR_TUNER("demode status err.\n");
            return HI_FAILURE;
    }

    return HI_SUCCESS;
}


