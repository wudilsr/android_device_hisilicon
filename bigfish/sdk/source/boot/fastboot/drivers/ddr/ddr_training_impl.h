/**
 * ddr_training_impl.h
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * DDR training implement define.
 */

#ifndef __ASSEMBLY__

#include "ddr_training_custom.h"
#include "ddr_training_internal_config.h"

/*******DMC register*********************************************/
#ifndef DDR_REG_BASE_DMC0
/* [CUSTOM] DMC0 register base address */
#define DDR_REG_BASE_DMC0                 0xf8a38000
#endif
#ifndef DDR_REG_BASE_DMC1
/* [CUSTOM] DMC1 register base address */
#define DDR_REG_BASE_DMC1                 0xf8a39000
#endif
/*******PHY register*********************************************/
#ifndef DDR_PHY_NUM
/* [CUSTOM] the number of PHY */
#define DDR_PHY_NUM                       2
#endif
#ifndef DDR_REG_BASE_PHY0
/* [CUSTOM] PHY0 register base address */
#define DDR_REG_BASE_PHY0                 0xf8a3c000
#endif
#ifndef DDR_REG_BASE_PHY1
/* [CUSTOM] PHY1 register base address */
#define DDR_REG_BASE_PHY1                 0xf8a3e000
#endif
/*******DDRT register*********************************************/
#ifndef DDR_REG_BASE_DDRT
#define DDR_REG_BASE_DDRT                 0xf8a50000
#endif
/*******AXI register*********************************************/
#ifndef DDR_REG_BASE_AXI
#define DDR_REG_BASE_AXI                  0xf8a30000
#endif

/****** ddr training sysctrl control register ********************************/
#ifndef DDR_REG_BASE_SYSCTRL
/* [CUSTOM] ddr training control */
#define DDR_REG_BASE_SYSCTRL              0xf8000000
#endif
#ifndef SYSCTRL_DDRT_PATTERN
/* [CUSTOM] ddrt reversed data */
#define SYSCTRL_DDRT_PATTERN              0xa0
#endif
#ifndef SYSCTRL_DDR_TRAINING_CFG
/* [CUSTOM] ddr training item */
#define SYSCTRL_DDR_TRAINING_CFG          0xd0
#endif
#ifndef SYSCTRL_DDR_TRAINING_STAT
/* [CUSTOM] ddr training stat */
#define SYSCTRL_DDR_TRAINING_STAT         0x9c
#endif

/* Write leveling. [4]=1:Disable */
#define DDR_BYPASS_WL_MASK                0x10
/* Gate training. [8]=1:Disable */
#define DDR_BYPASS_GATE_MASK              0x100
/* Dataeye training. [16]=1:Disable */
#define DDR_BYPASS_DATAEYE_MASK           0x10000
/* Hardware read deskew training. [20]=1:Disable */
#define DDR_BYPASS_HW_MASK                0x100000
/* MPR training. [21]=1:Disable */
#define DDR_BYPASS_MPR_MASK               0x200000
/* AC training. [22]=1:Disable */
#define DDR_BYPASS_AC_MASK                0x400000
/* HOST_VREF. [24]=1:Disable */
#define DDR_BYPASS_VREF_MASK              0x1000000
/* Dataeye adjust. [28]=1:Disable */
#define DDR_BYPASS_DATAEYE_ADJ_MASK       0x10000000

/****** common define **********************************************/
/* special ddrt need special read and write register */
#ifdef DDR_DDRT_SPECIAL_CONFIG
#define DDRT_REG_READ(addr)        ddr_ddrt_read(addr)
#define DDRT_REG_WRITE(val, addr)  ddr_ddrt_write(val, addr)
#else
#define DDRT_REG_READ(addr)        (*(volatile unsigned int *)(addr))
#define DDRT_REG_WRITE(val, addr)  ((*(volatile unsigned *) (addr)) = (val))
#endif

#define DDR_MODE_READ                     (1 << 0)
#define DDR_MODE_WRITE                    (1 << 1)

#define DDR_FIND_DQ_BOTH                  (1 << 0) /* find a valid value*/
/* x is valid, (x-1) is invalid*/
#define DDR_FIND_DQ_LEFT                  (1 << 1)
/* x is valid, (x+1) is invalid*/
#define DDR_FIND_DQ_RIGHT                 (1 << 2)

#define DDR_VREF_VAL_MAX                  (0x1f)        /* 78.75%*VDDIO */
#define DDR_VREF_VAL_MIN                  (0x0)         /* 40.00%*VDDIO */

#define DDR_PHY_BYTE_MAX                  4
#define DDR_PHY_BIT_NUM                   8
/* support max bit 32*/
#define DDR_PHY_BIT_MAX                   (DDR_PHY_BYTE_MAX * DDR_PHY_BIT_NUM)
#define DDR_PHY_REG_DQ_NUM                4  /* one register has 4 DQ BDL */

#define DDR_TRUE                          1
#define DDR_FALSE                         0

#define DDR_WIN_MIDDLE                    (1 << 0)
#define DDR_WIN_LEFT                      (1 << 1)
#define DDR_WIN_RIGHT                     (1 << 2)

#define DDR_DELAY_PHASE                   1
#define DDR_DELAY_BDL                     2

/* Dateeye window number. More bigger more slower when Vref training. */
#define DDR_DATAEYE_WIN_NUM               8
/* Dataeye DQ deskew times for best result. More bigger more slower. */
#define DDR_LOOP_TIMES_LMT                1
/* Compare times when find best vref value. More bigger more slower. */
#define DDR_VREF_COMPARE_TIMES            2

#define DDR_DATAEYE_RESULT_MASK           0xffff
#define DDR_DATAEYE_RESULT_BIT            16

#define DDR_WL_BDL_STEP                   2 /* wl bdl step */
#define DDR_GATE_BDL_STEP                 2 /* gate bdl step */
#define DDR_RDDQS_BDL_STEP                1 /* RDDQS bdl step */

#define DDR_DDRT_MODE_GATE                (1 << 0)
#define DDR_DDRT_MODE_DATAEYE             (1 << 1)

#define DDR_CHECK_TYPE_DDRT               (1 << 0)
#define DDR_CHECK_TYPE_MPR                (1 << 1)

#define DDR_MPR_BYTE_MASK                 0xff
#define DDR_MPR_BIT_MASK                  0x1
#define DDR_MPR_BYTE_BIT                  16          /* 16 bit (2 byte) */

#define DDR_PHY_AC_TEST_VAL0              0x0
#define DDR_PHY_AC_TEST_VAL1              0xffffffff
#define DDR_PHY_AC_TEST_VAL2              0x55555555
#define DDR_PHY_AC_TEST_VAL3              0xaaaaaaaa

/*******log define ***********************************************/
#if defined(DDR_TRAINING_CMD) && defined(DDR_TRAINING_LOG_CONFIG)
#define DDR_INFO(fmt...)     ddr_training_log(__func__, DDR_LOG_INFO, fmt)
#define DDR_DEBUG(fmt...)    ddr_training_log(__func__, DDR_LOG_DEBUG, fmt)
#define DDR_WARNING(fmt...)  ddr_training_log(__func__, DDR_LOG_WARNING, fmt)
#define DDR_ERROR(fmt...)    ddr_training_log(__func__, DDR_LOG_ERROR, fmt)
#define DDR_FATAL(fmt...)    ddr_training_log(__func__, DDR_LOG_FATAL, fmt)
#else
#define DDR_INFO(fmt...)
#define DDR_DEBUG(fmt...)
#define DDR_WARNING(fmt...)
#define DDR_ERROR(fmt...)
#define DDR_FATAL(fmt...)
#endif /* DDR_TRAINING_CMD && DDR_TRAINING_LOG_CONFIG */

/* [13:0] Error type */
/* 0x00000001 Write Leveling error */
#define DDR_ERR_WL                        (1 << 0)
/* 0x00000002 Hardware Gatining error */
#define DDR_ERR_HW_GATING                 (1 << 1)
/* 0x00000004 Sofeware Gatining error */
#define DDR_ERR_GATING                    (1 << 2)
/* 0x00000008 DDRT test time out */
#define DDR_ERR_DDRT_TIME_OUT             (1 << 3)
/* 0x00000010 Hardware read dataeye error */
#define DDR_ERR_HW_RD_DATAEYE			  (1 << 4)
/* 0x00000020 MPR error */
#define DDR_ERR_MPR                       (1 << 5)


/* [15:14] Error phy */
/* 0x00004000 PHY0 training error */
#define DDR_ERR_PHY0                      (14 << 0)
/* 0x00008000 PHY1 training error */
#define DDR_ERR_PHY1                      (15 << 0)

/* [31:24] Error byte */
#define DDR_ERR_WL_BYTE_BIT               28  /* [31:28] Byte0-3 WL error */
#define DDR_ERR_GATE_BYTE_BIT             24  /* [27:24] Byte0-3 Gate error */

/**
 * 0x10000001 : Byte0 Write Leveling training error
 * 0x20000001 : Byte1 Write Leveling training error
 * 0x40000001 : Byte2 Write Leveling training error
 * 0x80000001 : Byte3 Write Leveling training error
 * 0x01000004 : Byte0 Gate trainng error
 * 0x02000004 : Byte1 Gate trainng error
 * 0x04000004 : Byte2 Gate trainng error
 * 0x08000004 : Byte3 Gate trainng error
 */

/*******data define*********************************************/
struct training_data {
	unsigned short int ddr_byte_num;
	unsigned int base_phy;
	unsigned int base_dmc;
	unsigned int ddrt_reversed_data;
	unsigned int dq_check_type;
	unsigned int ddr_bit_result[DDR_PHY_BIT_MAX];
	unsigned int ddr_bit_best[DDR_PHY_BIT_MAX];
	unsigned int ddr_win_sum;
};

struct ddr_delay_st {
	unsigned int phase[DDR_PHY_BYTE_MAX];
	unsigned int bdl[DDR_PHY_BYTE_MAX];
};


/*******function interface define*********************************************/
#ifndef DDR_SW_TRAINING_FUNC
#define DDR_SW_TRAINING_FUNC_PUBLIC
#define DDR_SW_TRAINING_FUNC        ddr_sw_training_func
#endif
#ifndef DDR_HW_TRAINING_FUNC
#define DDR_HW_TRAINING_FUNC_PUBLIC
#define DDR_HW_TRAINING_FUNC        ddr_hw_training_func
#endif
#ifndef DDR_MPR_TRAINING_FUNC
#define DDR_MPR_TRAINING_FUNC_PUBLIC
#define DDR_MPR_TRAINING_FUNC       ddr_mpr_training_func
#endif
#ifndef DDR_WL_FUNC
#define DDR_WL_FUNC_PUBLIC
#define DDR_WL_FUNC                 ddr_wl_func
#endif
#ifndef DDR_GATING_FUNC
#define DDR_GATING_FUNC_PUBLIC
#define DDR_GATING_FUNC             ddr_gating_func
#endif
#ifndef DDR_DATAEYE_TRAINING_FUNC
#define DDR_DATAEYE_TRAINING_FUNC_PUBLIC
#define DDR_DATAEYE_TRAINING_FUNC   ddr_dataeye_training_func
#endif
#ifndef DDR_VREF_TRAINING_FUNC
#define DDR_VREF_TRAINING_FUNC_PUBLIC
#define DDR_VREF_TRAINING_FUNC      ddr_vref_training_func
#endif
#ifndef DDR_AC_TRAINING_FUNC
#define DDR_AC_TRAINING_FUNC_PUBLIC
#define DDR_AC_TRAINING_FUNC        ddr_ac_training_func
#endif
/*******function define*********************************************/
int ddr_sw_training_func(void *ddrtr_result);
int ddr_hw_training_func(void);
int ddr_mpr_training_func(void);
int ddr_wl_func(void);
int ddr_gating_func(void);
int ddr_dataeye_training_func(void *ddrtr_result);
int ddr_vref_training_func(void *ddrtr_result);
int ddr_ac_training_func(void);

void ddr_phy_cfg_update(unsigned int base_phy);
void ddr_phy_set_dq_bdl(unsigned int base_phy, unsigned int deskew_value,
	unsigned int bytenum, unsigned int dqindex, unsigned int mode);
int ddr_hw_training(unsigned int base_dmc, unsigned int base_phy);
int ddr_mpr_check(unsigned int base_dmc, unsigned int byte_index,
	int dq_index);
int ddr_mpr_training(unsigned int base_dmc, unsigned int base_phy);
int ddr_write_leveling(unsigned int base_dmc, unsigned int base_phy);
int ddr_gate_training(unsigned int base_dmc, unsigned int base_phy);
int ddr_dataeye_training(unsigned int base_dmc, unsigned int base_phy,
	void *ddrtr_result);
int ddr_vref_training(unsigned int base_dmc, unsigned int base_phy,
	void *ddrtr_result);
int ddr_dataeye_deskew(struct training_data *training,
	unsigned int byte_index,  unsigned int mode);
void ddr_adjust_dataeye(struct training_data *training,
	unsigned int mode);
void ddr_result_data_save(void *ddrtr_result,
	struct training_data *training, unsigned int mode);
int ddr_ddrt_get_test_addr(void);
int ddr_ddrt_test(unsigned int mask, int byte, int dq);
int ddr_dataeye_check_dq(const struct training_data *training,
	unsigned int byte_index, unsigned int dq_index);
void ddr_ddrt_init(unsigned int base_dmc, unsigned int mode);
int ddr_training_check_bypass(unsigned int mask);
void ddr_training_log(const char *func, int level, const char *fmt, ...);
void ddr_training_stat(unsigned int val);
unsigned int ddr_phy_get_byte_num(unsigned int base_dmc);
void ddr_ddrt_prepare(void);

#endif /* __ASSEMBLY__ */
