/**
 * ddr_cmd_ctl.c
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * DDR training command control.
 */

#include <common.h>
#include <ddr_interface.h>
#include "ddr_training_impl.h"

#if PHY_DQ_BDL_LEVEL == 32
#define PRINT_DATAEYE_WIN(dq_num, range, dqs, dq, win) \
	do {\
		printf("%-4d", dq_num);\
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) {\
			if (k >= (range >> DDR_DATAEYE_RESULT_BIT)\
				&& k <= (range & DDR_DATAEYE_RESULT_MASK)) {\
				printf("%-3s", "-");\
			} else {\
				printf("%-3s", "X");\
			} \
		} \
		printf(" 0x%08x  0x%-4x%-4d%-4d\n", range, dqs, dq, win); \
	} while (0)

#define PRINT_DATAEYE_TITLE() \
	do { \
		printf("%-4s", "DQ"); \
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) { \
			printf("%-3d", k); \
		} \
		printf(" %-10s  %-6s%-4s%-4s\n", \
			"RANGE", "DQS", "DQ", "WIN"); \
	} while (0)
#else
#define PRINT_DATAEYE_WIN(dq_num, range, dqs, dq, win) \
	do {\
		printf("%-4d", dq_num); \
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) { \
			if (k >= (range >> DDR_DATAEYE_RESULT_BIT)\
				&& k <= (range & DDR_DATAEYE_RESULT_MASK)) {\
				printf("%-1s", "-"); \
			} else {\
				printf("%-1s", "X"); \
			} \
		} \
		printf(" 0x%08x  0x%-4x%-4d%-4d\n", range, dqs, dq, win); \
	} while (0)

#define PRINT_DATAEYE_TITLE() \
	do { \
		printf("%-4s", "DQ");\
		for (k = 0; k < PHY_DQ_BDL_LEVEL; k++) { \
			if (0 == k % 4) \
				printf("%-4d", k); \
		} \
		printf(" %-10s  %-6s%-4s%-4s\n", \
			"RANGE", "DQS", "DQ", "WIN"); \
	} while (0)
#endif

extern char ddr_training_cmd_start[];  /* DDR training code start address */
extern char ddr_training_cmd_end[];    /* DDR training code end address */

/**
 * ddr_training_reg_read_phy
 * @base_dmc
 * @base_phy
 * @ddr_reg
 * @arr_index
 *
 * Read DDR training register per PHY.
 */
static void ddr_training_reg_read_phy(unsigned int base_dmc,
		unsigned int base_phy, struct ddr_training_reg_st *ddr_reg,
		unsigned int arr_index)
{
	int byte_num;
	int index = 0;
	int i;

	byte_num = ((REG_READ(base_dmc + DDR_DMC_CFG_DDRMODE)
			>> DMC_MEM_WIDTH_BIT) & DMC_MEM_WIDTH_MASK) << 1;

	index    = arr_index;

	if ((DDR_TRAINING_REG_MAX - index) < DDR_TRAINING_REG_NUM) {
		printf("Not enough space. Free[%d] Need[%d]",
				(DDR_TRAINING_REG_MAX - index),
				DDR_TRAINING_REG_NUM);
		return;
	}

	/* WDQS */
	for (i = 0; i < byte_num; i++) {
		sprintf(ddr_reg->reg[index].name, "WDQS Byte%d", i);
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXWDQSDLY(i);
	}

	/* WDQ Phase */
	for (i = 0; i < byte_num; i++) {
		sprintf(ddr_reg->reg[index].name, "WDQ Phase Byte%d", i);
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNWDQDLY(i);
	}

	/* WDQ BDL */
	for (i = 0; i < byte_num; i++) {
		/* DQ0-DQ3 */
		sprintf(ddr_reg->reg[index].name,
			"WDQ BDL DQ%d-DQ%d", (i << 3), ((i << 3) + 3));
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNWDQNBDL0(i);
		/* DQ4-DQ7 */
		sprintf(ddr_reg->reg[index].name,
			"WDQ BDL DQ%d-DQ%d", ((i << 3) + 4), ((i << 3) + 7));
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNWDQNBDL1(i);
	}

	/* WDM */
	for (i = 0; i < byte_num; i++) {
		sprintf(ddr_reg->reg[index].name, "WDM Byte%d", i);
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNWDQNBDL2(i);
	}

	/* Write DO/DOS OE */
	for (i = 0; i < byte_num; i++) {
		sprintf(ddr_reg->reg[index].name, "Write DQ/DQS OE Byte%d", i);
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNOEBDL(i);
	}

	/* RDQS */
	for (i = 0; i < byte_num; i++) {
		sprintf(ddr_reg->reg[index].name, "RDQS Byte%d", i);
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNRDQSDLY(i);
	}

	/* RDQ BDL */
	for (i = 0; i < byte_num; i++) {
		/* DQ0-DQ3 */
		sprintf(ddr_reg->reg[index].name,
			"RDQ BDL DQ%d-DQ%d", (i << 3), ((i << 3) + 3));
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNRDQNBDL0(i);
		/* DQ4-DQ7 */
		sprintf(ddr_reg->reg[index].name,
			"RDQ BDL DQ%d-DQ%d", ((i << 3) + 4), ((i << 3) + 7));
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNRDQNBDL1(i);
	}

	/* Gate */
	for (i = 0; i < byte_num; i++) {
		sprintf(ddr_reg->reg[index].name, "Gate Byte%d", i);
		ddr_reg->reg[index++].addr = base_phy + DDR_PHY_DXNRDQSGDLY(i);
	}

	/* AC CS */
	sprintf(ddr_reg->reg[index].name, "CS");
	ddr_reg->reg[index++].addr = base_phy + DDR_PHY_ACCMDBDL2;

	/* AC CLK */
	sprintf(ddr_reg->reg[index].name, "CLK");
	ddr_reg->reg[index++].addr = base_phy + DDR_PHY_ACPHYCTL7;

	/* read register */
	for (i = 0; i < index; i++) {
		if (0 == ddr_reg->reg[i].addr)
			break;

		ddr_reg->reg[i].val = REG_READ(ddr_reg->reg[i].addr);
	}
}

/**
 * ddr_training_reg_read
 * @ddr_reg
 *
 * Read DDR training register.
 */
static void ddr_training_reg_read(struct ddr_training_reg_st *ddr_reg)
{
	int i;

	/* init */
	for (i = 0; i < DDR_TRAINING_REG_MAX; i++)
		ddr_reg->reg[i].addr = 0;

	ddr_training_reg_read_phy(DDR_REG_BASE_DMC0,
		DDR_REG_BASE_PHY0, ddr_reg, 0);
#if DDR_PHY_NUM == 2
	ddr_training_reg_read_phy(DDR_REG_BASE_DMC1,
		DDR_REG_BASE_PHY1, ddr_reg, DDR_TRAINING_REG_NUM);
#endif
}

/**
 * ddr_cmd_result_print
 * @ddrtr_data
 *
 *
 */
static int ddr_cmd_result_print(struct ddr_training_data_st *ddrtr_data)
{
	unsigned int i, k, j;
	unsigned int dq_num, dqs, dq, win;

	printf("Write window of prebit-deskew:\n");
	printf("--------------------------------------------------------\n");
	PRINT_DATAEYE_TITLE();
	for (j = 0; j < ddrtr_data->byte_num; j++) {
		dqs = (REG_READ(ddrtr_data->base_phy + DDR_PHY_DXNWDQDLY(j))
				>> PHY_WDQ_PHASE_BIT) & PHY_WDQ_PHASE_MASK;
		for (i = 0; i < DDR_PHY_BIT_NUM; i++) {
			dq_num = j * DDR_PHY_BIT_NUM + i;
			win = ddrtr_data->wr_bit_best[dq_num]
				>> DDR_DATAEYE_RESULT_BIT;
			dq =  ddrtr_data->wr_bit_best[dq_num]
				& DDR_DATAEYE_RESULT_MASK;
			PRINT_DATAEYE_WIN(dq_num,
					ddrtr_data->wr_bit_result[dq_num],
					dqs, dq, win);
		}
	}
	printf("--------------------------------------------------------\n\n");

	printf("Read window of prebit-deskew:\n");
	printf("--------------------------------------------------------\n");
	PRINT_DATAEYE_TITLE();
	for (j = 0; j < ddrtr_data->byte_num; j++) {
		dqs = REG_READ(ddrtr_data->base_phy + DDR_PHY_DXNRDQSDLY(j))
				& PHY_RDQS_BDL_MASK;
		for (i = 0; i < DDR_PHY_BIT_NUM; i++) {
			dq_num = j * DDR_PHY_BIT_NUM + i;
			win = ddrtr_data->rd_bit_best[dq_num]
				>> DDR_DATAEYE_RESULT_BIT;
			dq =  ddrtr_data->rd_bit_best[dq_num]
				& DDR_DATAEYE_RESULT_MASK;
			PRINT_DATAEYE_WIN(dq_num,
					ddrtr_data->rd_bit_result[dq_num],
					dqs, dq, win);
		}
	}
	printf("--------------------------------------------------------\n");

	printf("DRAM vref training: [0x%08x = 0x%08x]. Total WIN: %d.\n",
		   0, 0, ddrtr_data->wr_win_sum); /* TODO: DRAM register */

	printf("HOST vref training: [0x%08x = 0x%08x]. Total WIN: %d.\n",
			(ddrtr_data->base_phy + DDR_PHY_IOCTL2),
			REG_READ(ddrtr_data->base_phy + DDR_PHY_IOCTL2),
			ddrtr_data->rd_win_sum);

	return 0;
}

/**
 * ddr_cmd_result_display
 * @ddrtr_result
 *
 */
void ddr_cmd_result_display(struct ddr_training_result_st *ddrtr_result)
{
	int i;

	for (i = 0; i < DDR_PHY_NUM; i++) {
		if (2 == DDR_PHY_NUM)
			printf("\r\n[PHY%d]:\r\n", i);
		ddr_cmd_result_print(&ddrtr_result->ddrtr_data[i]);
	}
}

/**
 * ddr_reg_result_display
 * @ddr_reg
 *
 * Display DDR training register.
 */
void ddr_reg_result_display(struct ddr_training_reg_st *ddr_reg)
{
	int i;

	ddr_training_reg_read(ddr_reg);

	printf("\r\nDDR training register:\r\n");
	for (i = 0; i < DDR_TRAINING_REG_MAX; i++) {
		if (0 == i && 2 == DDR_PHY_NUM)
			printf("[PHY0]:\r\n");

		if (0 == ddr_reg->reg[i].addr)
			break;

		ddr_reg->reg[i].val = REG_READ(ddr_reg->reg[i].addr);
		printf("[0x%08x = 0x%08x] %-32s", ddr_reg->reg[i].addr,
				ddr_reg->reg[i].val, ddr_reg->reg[i].name);

		if (i % 2)
			printf("\r\n");

		if ((DDR_TRAINING_REG_NUM - 1) == i && 2 == DDR_PHY_NUM)
			printf("\r\n[PHY1]:\r\n");
	}

	printf("\r\n");
}

/**
 * ddr_cmd_get_entry
 * @void
 *
 * Get DDR training command function entry address.
 */
void *ddr_cmd_get_entry(void)
{
	char *src_ptr = 0;
	char *dst_ptr;
	unsigned int length = 0;

	src_ptr = ddr_training_cmd_start;
	dst_ptr = (char *)(DDR_TRAINING_RUN_STACK);
	length  = ddr_training_cmd_end - src_ptr;

	if (!src_ptr || !length) {
		printf("DDR training is unsupport.\n");
		return 0;
	}

	printf("SRAM address[0x%x] code address[0x%x] Size[%d]byte\n",
			(unsigned int)dst_ptr,
			(unsigned int)src_ptr, length);

	ddr_cmd_prepare_copy();
	memcpy(dst_ptr, src_ptr, length);
	return (void *) dst_ptr;
}

#ifdef CONFIG_DDR_TRAINING_BOOTENV
/**
 * ddr_cmd_result_dump
 * @result:
 * @flags
 *
 * Dump DDR training register value.
 */
char *ddr_cmd_result_dump(struct ddr_training_reg_st *ddr_reg, char flags)
{
	int i;
	char *ptr;
	/* 22 = strlen("0xffffffff=0xffffffff\n") */
	static char buf[(DDR_TRAINING_REG_MAX * 22) + 1] = {0};

	ddr_training_reg_read(ddr_reg);

	ptr = buf;
	buf[0] = '\0';
	for (i = 0;
		i < DDR_TRAINING_REG_MAX && (ptr - buf) < sizeof(buf); i++) {
		if (0 == ddr_reg->reg[i].addr)
			break;

		ptr += sprintf(ptr, "0x%08x=0x%08x%c",
				ddr_reg->reg[i].addr,
				ddr_reg->reg[i].val, flags);
	}

	return buf;
}
#endif
