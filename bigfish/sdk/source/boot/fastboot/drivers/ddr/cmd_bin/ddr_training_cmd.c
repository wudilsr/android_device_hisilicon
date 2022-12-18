/**
 * ddr_training_cmd.c
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * DDR training command implement.
 */
#include <stdarg.h>
#include <ddr_interface.h>
#include "ddr_training_impl.h"

extern void uart_early_puts(const char *s);
extern void uart_early_put_hex(int hex);
extern void uart_early_putc(int chr);

/* ddr training cmd result */
static struct ddr_training_result_st ddrt_result_sram;
static int ddr_training_addr_start;
static int ddr_training_addr_end;
static int ddr_print_level = DDR_LOG_ERROR;

#ifdef DDR_TRAINING_LOG_CONFIG
/**
 * ddr_training_log
 * @func
 * @level
 * @fmt
 *
 * Log ddr training info.
 */
void ddr_training_log(const char *func, int level, const char *fmt, ...)
{
	va_list args;

	if (ddr_print_level > level)
		return;

	uart_early_putc('[');
	switch (level) {
	case DDR_LOG_INFO:
		uart_early_puts("INFO");
		 break;
	case DDR_LOG_DEBUG:
		uart_early_puts("DEBUG");
		break;
	case DDR_LOG_WARNING:
		 uart_early_puts("WARNING");
		break;
	case DDR_LOG_ERROR:
		uart_early_puts("ERROR");
		break;
	case DDR_LOG_FATAL:
		uart_early_puts("FATAL");
		break;
	default:
		break;
	}
	uart_early_putc(']');
	uart_early_putc('[');
	uart_early_puts(func);
	uart_early_putc(']');

	va_start(args, fmt);
	while ('\0' != *fmt) {
		if ('%' != *fmt) {
			uart_early_putc(*fmt);
		} else {
			fmt++;
			switch (*fmt) {
			case 'x':
			case 'X':
				uart_early_puts("0x");
				uart_early_put_hex(va_arg(args, int));
				break;
			default:
				uart_early_putc('%');
				uart_early_putc(*fmt);
				break;
			} /* switch */
		}
		fmt++;
	} /* while */
	va_end(args);
	uart_early_puts("\r\n");
}
#endif

/**
 * ddr_training_result_init
 * @void
 *
 * Inint ddr training cmd result.
 */
static void ddr_training_result_init(void)
{
	ddrt_result_sram.ddrtr_data[0].base_dmc = DDR_REG_BASE_DMC0;
	ddrt_result_sram.ddrtr_data[0].base_phy = DDR_REG_BASE_PHY0;
	ddrt_result_sram.ddrtr_data[0].byte_num
		= ddr_phy_get_byte_num(DDR_REG_BASE_DMC0);
#if DDR_PHY_NUM == 2
	ddrt_result_sram.ddrtr_data[1].base_dmc = DDR_REG_BASE_DMC1;
	ddrt_result_sram.ddrtr_data[1].base_phy = DDR_REG_BASE_PHY1;
	ddrt_result_sram.ddrtr_data[1].byte_num
		= ddr_phy_get_byte_num(DDR_REG_BASE_DMC1);
#endif
}

/**
 * ddr_result_data_save
 * @ddrtr_result
 * @training
 * @mode
 *
 * Save ddr training cmd result.
 */
void ddr_result_data_save(void *ddrtr_result,
			struct training_data *training, unsigned int mode)
{
	int index = 0;
	int i;
	struct ddr_training_result_st *result_st
		= (struct ddr_training_result_st *)ddrtr_result;
	struct ddr_training_data_st *data;

	for (i = 0; i < DDR_SUPPORT_PHY_MAX; i++) {
		if (result_st->ddrtr_data[i].base_dmc == training->base_dmc) {
			index = i;
			break;
		}
	}

	data = &result_st->ddrtr_data[index];

	if (DDR_MODE_READ == mode) {
		for (i = 0; i < training->ddr_byte_num << 3; i++) {
			data->rd_bit_result[i] = training->ddr_bit_result[i];
			data->rd_bit_best[i]   = training->ddr_bit_best[i];
		}
	data->rd_win_sum  = training->ddr_win_sum;
	} else {
		for (i = 0; i < training->ddr_byte_num << 3; i++) {
			data->wr_bit_result[i] = training->ddr_bit_result[i];
			data->wr_bit_best[i]   = training->ddr_bit_best[i];
		}
		data->wr_win_sum  = training->ddr_win_sum;
	}

}

/**
 * ddr_ddrt_get_test_addr
 * @void
 *
 * Get DDRT test addrress.
 */
int ddr_ddrt_get_test_addr(void)
{
	if (ddr_training_addr_start < DDRT_CFG_TEST_ADDR_CMD
	&&	ddr_training_addr_end > DDRT_CFG_TEST_ADDR_CMD) {
		return DDRT_CFG_TEST_ADDR_CMD;
	} else {
		DDR_ERROR("DDRT test address[%x] out of range[%x, %x].",
				DDRT_CFG_TEST_ADDR_CMD,
				ddr_training_addr_start,
				ddr_training_addr_end);
		return ddr_training_addr_start;
	}
}

/**
 * ddr_sw_training_without_wl
 * @ddrtr_result
 *
 * Do DDR sofeware(Gate/Dataeye/Vref) training without Write Leveling.
 * Write Leveling only support training once.
 */
static int ddr_sw_training_without_wl(void *ddrtr_result)
{
	int result = 0;

	result += ddr_dataeye_training_if(ddrtr_result);

	if (result && !ddr_training_check_bypass(DDR_BYPASS_HW_MASK)) {
		result  = ddr_hw_training_if();
		result += ddr_dataeye_training_if(ddrtr_result);
	}

	if (result && !ddr_training_check_bypass(DDR_BYPASS_MPR_MASK)) {
		result  = ddr_mpr_training_if();
		result += ddr_dataeye_training_if(ddrtr_result);
	}

	result += ddr_gating_if();
	result += ddr_vref_training_if(ddrtr_result);
	return result;
}

/**
 * ddr_training_cmd_entry
 * @cmd_st
 *
 * DDR training command entry. Call by cmd_ddr_handle().
 */
struct ddr_training_result_st *ddr_training_cmd_entry(
		struct ddr_cmd_st *cmd_st)
{
	int result = 0;

	ddr_training_addr_start = cmd_st->start;
	ddr_training_addr_end   = cmd_st->start + cmd_st->length;
	ddr_print_level         = cmd_st->level;

	DDR_DEBUG("DDR training command entry. Sysctl[%x = %x]",
		(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG),
		REG_READ(DDR_REG_BASE_SYSCTRL + SYSCTRL_DDR_TRAINING_CFG));

	ddr_training_result_init();

	switch (cmd_st->cmd) {
	case DDR_TRAINING_CMD_SW:
		result = ddr_sw_training_if((void *)&ddrt_result_sram);
		break;
	case DDR_TRAINING_CMD_DATAEYE:
		result = ddr_dataeye_training_if((void *)&ddrt_result_sram);
		break;
	case DDR_TRAINING_CMD_HW:
		result = ddr_hw_training_if();
		break;
	case DDR_TRAINING_CMD_MPR:
		result = ddr_mpr_training_if();
		break;
	case DDR_TRAINING_CMD_WL:
		result = ddr_wl_if();
		break;
	case DDR_TRAINING_CMD_GATE:
		result = ddr_gating_if();
		break;
	case DDR_TRAINING_CMD_VREF:
		result = ddr_vref_training_if((void *)&ddrt_result_sram);
		break;
	case DDR_TRAINING_CMD_AC:
		result = ddr_ac_training_if();
		break;
	case DDR_TRAINING_CMD_SW_NO_WL:
		result = ddr_sw_training_without_wl((void *)&ddrt_result_sram);
		break;
	default:
		result = -1;
		break;
	}

	if (!result)
		return &ddrt_result_sram;
	else
		return 0;
}
