/**
 * ddr_training_boot.c
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * Special function for ddr training when power up.
 */

#include "ddr_training_impl.h"
#include <ddr_interface.h>

/**
 * ddr_result_data_save
 * @ddrtr_result
 * @training
 * @mode
 *
 * Save DDR tarining result.
 */
void ddr_result_data_save(void *ddrtr_result,
		struct training_data *training, unsigned int mode)
{
	/* nothing to do when ddr training on power up */
}

/**
 * ddr_ddrt_get_test_addr
 * @void
 *
 * Get DDRT test address.
 */
int ddr_ddrt_get_test_addr(void)
{
	return DDRT_CFG_TEST_ADDR_BOOT;
}
