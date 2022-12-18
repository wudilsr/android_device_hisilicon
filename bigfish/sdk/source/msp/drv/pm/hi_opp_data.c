/*
 * HI OPP table definitions.
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
 */
#include <linux/module.h>
#include "hi_opp_data.h"
#include "hi_drv_pmoc.h"

/*
 * Structures containing HI voltage supported and various
 * voltage dependent data for each VDD.
 */
static struct hi_opp_def __initdata hi_opp_def_list[] = {
    /*OPP_INITIALIZER(true,  400000, HI_VDD_MPU_OPP1_UV),*/
    OPP_INITIALIZER(true,  600000, HI_VDD_MPU_OPP2_UV),
    /*OPP_INITIALIZER(true,  800000, HI_VDD_MPU_OPP3_UV),*/
    OPP_INITIALIZER(true, 1000000, HI_VDD_MPU_OPP4_UV),
    OPP_INITIALIZER(true, 1200000, HI_VDD_MPU_OPP5_UV),
#if    defined(CHIP_TYPE_hi3798cv100)   \
    || defined(CHIP_TYPE_hi3796cv100)   \
	|| defined(CHIP_TYPE_hi3798mv100)   \
	|| defined(CHIP_TYPE_hi3796mv100)   \
	|| defined(CHIP_TYPE_hi3798cv200_a)
    OPP_INITIALIZER(true, 1500000, HI_VDD_MPU_OPP6_UV),
#endif
};

/**
 * hi_opp_init() - initialize hi opp table
 */
int __init hi_opp_init(void)
{
    int r = -ENODEV;

    HI_INFO_PM("enter %s\n", __FUNCTION__);

    r = hi_init_opp_table(hi_opp_def_list,
                          ARRAY_SIZE(hi_opp_def_list));

    return r;
}

#if 0
#ifndef MODULE
device_initcall(hi_opp_init);
#endif
#endif
