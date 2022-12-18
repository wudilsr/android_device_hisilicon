/**
 * ddr_training_ctl.c
 *
 * Copyright (c) 2009-2014, HiSilicon Technologies Co., Ltd.
 * All rights reserved.
 *
 * DDR training control.
 */
#include <ddr_interface.h>
#include "ddr_training_impl.h"

#ifdef DDR_SW_TRAINING_FUNC_PUBLIC
/**
 * ddr_sw_training_func
 * @ddrtr_result
 *
 *
 */
int ddr_sw_training_func(void *ddrtr_result)
{
	int result = 0;

	result  = ddr_wl_if();
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
#endif /* DDR_SW_TRAINING_FUNC_PUBLIC */

#if defined(DDR_HW_TRAINING_CONFIG) && defined(DDR_HW_TRAINING_FUNC_PUBLIC)
/**
 * ddr_hw_training_func
 * @void
 *
 *
 */
int ddr_hw_training_func(void)
{
	int result = 0;
	/* hardware training disable */
	if (ddr_training_check_bypass(DDR_BYPASS_HW_MASK))
		return 0;

	result  = ddr_hw_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);
#if DDR_PHY_NUM == 2
	result += ddr_hw_training(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1);
#endif

	return result;
}
#else
int ddr_hw_training_func(void)
{
	DDR_WARNING("Not support DDR HW training.");
	return 0;
}
#endif /* DDR_HW_TRAINING_CONFIG */

#if defined(DDR_MPR_TRAINING_CONFIG) && defined(DDR_MPR_TRAINING_FUNC_PUBLIC)
/**
 * ddr_mpr_training_func
 * @void
 *
 *
 */
int ddr_mpr_training_func(void)
{
	int result = 0;
	/* MPR training disable */
	if (ddr_training_check_bypass(DDR_BYPASS_MPR_MASK))
		return 0;

	result  = ddr_mpr_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);
#if DDR_PHY_NUM == 2
	result += ddr_mpr_training(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1);
#endif

	return result;
}
#else
int ddr_mpr_training_func(void)
{
	DDR_WARNING("Not support DDR MPR training.");
	return 0;
}
#endif /* DDR_MPR_TRAINING_CONFIG */

#if defined(DDR_WL_TRAINING_CONFIG) && defined(DDR_WL_FUNC_PUBLIC)
/**
 * ddr_wl_func
 * @void
 *
 *
 */
int ddr_wl_func(void)
{
	int result = 0;
	unsigned int auto_ref_timing;

	/* write leveling disable */
	if (ddr_training_check_bypass(DDR_BYPASS_WL_MASK))
		return 0;

	auto_ref_timing = REG_READ(DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
#if DDR_PHY_NUM == 2
	/* disable auto refresh*/
	REG_WRITE(auto_ref_timing & 0xfffff000,
			DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
	REG_WRITE(auto_ref_timing & 0xfffff000,
			DDR_REG_BASE_DMC1 + DDR_DMC_TIMING2);
	result  = ddr_write_leveling(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);
	result += ddr_write_leveling(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1);
	/* enable auto refresh*/
	REG_WRITE(auto_ref_timing, DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
	REG_WRITE(auto_ref_timing, DDR_REG_BASE_DMC1 + DDR_DMC_TIMING2);
#else
	/* disable auto refresh*/
	REG_WRITE(auto_ref_timing & 0xfffff000,
			DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
	result  = ddr_write_leveling(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);
	/* enable auto refresh*/
	REG_WRITE(auto_ref_timing, DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
#endif

	return result;
}
#else
int ddr_wl_func()
{
	DDR_WARNING("Not support DDR WL training.");
	return 0;
}
#endif /* DDR_WL_TRAINING_CONFIG */

#if defined(DDR_GATE_TRAINING_CONFIG) && defined(DDR_GATING_FUNC_PUBLIC)
/**
 * ddr_gating_func
 * @void
 *
 *
 */
int ddr_gating_func(void)
{
	int result = 0;
	unsigned int auto_ref_timing;
#if DDR_PHY_NUM == 2
	unsigned int ddr_rng_map0;
	unsigned int ddr_rng_map1;
#endif
	/* gate training disable */
	if (ddr_training_check_bypass(DDR_BYPASS_GATE_MASK)) {
		/* check hardware gating */
		if (REG_READ(DDR_REG_BASE_PHY0 + DDR_PHY_PHYINITSTATUS)
						& PHY_INITSTATUS_GT_MASK) {
			DDR_FATAL("hardware gating fail.");
			ddr_training_stat(DDR_ERR_HW_GATING);
			return -1;
		}

#if DDR_PHY_NUM == 2
		if (REG_READ(DDR_REG_BASE_PHY1 + DDR_PHY_PHYINITSTATUS)
						& PHY_INITSTATUS_GT_MASK) {
			DDR_FATAL("hardware gating fail.");
			ddr_training_stat(DDR_ERR_HW_GATING);
			return -1;
		}
#endif
		return 0;
	}

	ddr_ddrt_init(DDR_REG_BASE_DMC0, DDR_DDRT_MODE_GATE);

	auto_ref_timing = REG_READ(DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);

#if DDR_PHY_NUM == 2
	/* disable auto refresh*/
	REG_WRITE(auto_ref_timing & 0xfffff000,
			DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
	REG_WRITE(auto_ref_timing & 0xfffff000,
			DDR_REG_BASE_DMC1 + DDR_DMC_TIMING2);

	/*record the original value of AXI*/
	ddr_rng_map0 = REG_READ(DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	ddr_rng_map1 = REG_READ(DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);

	/*set ddrt link to DMC0*/
	REG_WRITE((ddr_rng_map0 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG0_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE((ddr_rng_map1 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG0_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
	ddr_gate_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);

	/*set ddrt link to DMC1*/
	REG_WRITE((ddr_rng_map0 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG1_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE((ddr_rng_map1 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG1_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
	ddr_gate_training(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1);

	/*backup to original value*/
	REG_WRITE(ddr_rng_map0, DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE(ddr_rng_map1, DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);

	/* enable auto refresh*/
	REG_WRITE(auto_ref_timing, DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
	REG_WRITE(auto_ref_timing, DDR_REG_BASE_DMC1 + DDR_DMC_TIMING2);
#else
	/* disable auto refresh*/
	REG_WRITE(auto_ref_timing & 0xfffff000,
				DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);

	result  = ddr_gate_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);

	/* enable auto refresh*/
	REG_WRITE(auto_ref_timing, DDR_REG_BASE_DMC0 + DDR_DMC_TIMING2);
#endif

	return result;
}
#else
int ddr_gating_func(void)
{
	DDR_WARNING("Not support DDR gate training.");
	return 0;
}
#endif /* DDR_GATE_TRAINING_CONFIG */

#ifdef DDR_DATAEYE_TRAINING_FUNC_PUBLIC
/**
 * ddr_dataeye_training_func
 * @ddrtr_result
 *
 *
 */
int ddr_dataeye_training_func(void *ddrtr_result)
{
	int result = 0;
#if DDR_PHY_NUM == 2
	unsigned int ddr_rng_map0;
	unsigned int ddr_rng_map1;
#endif
	/* dataeye training disable */
	if (ddr_training_check_bypass(DDR_BYPASS_DATAEYE_MASK))
		return 0;

	ddr_ddrt_init(DDR_REG_BASE_DMC0, DDR_DDRT_MODE_DATAEYE);

#if DDR_PHY_NUM == 2
	/*record the original value of AXI*/
	ddr_rng_map0 = REG_READ(DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	ddr_rng_map1 = REG_READ(DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);

	/*set ddrt link to DMC0*/
	REG_WRITE((ddr_rng_map0 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG0_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE((ddr_rng_map1 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG0_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
	result += ddr_dataeye_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0,
								ddrtr_result);

	/*set ddrt link to DMC1*/
	REG_WRITE((ddr_rng_map0 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG1_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE((ddr_rng_map1 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG1_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
	result += ddr_dataeye_training(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1,
								ddrtr_result);

	/*backup to original value*/
	REG_WRITE(ddr_rng_map0, DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE(ddr_rng_map1, DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
#else
	result  = ddr_dataeye_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0,
				ddrtr_result);
#endif

	return result;
}
#endif /* DDR_DATAEYE_TRAINING_FUNC_PUBLIC */

#if defined(DDR_VREF_TRAINING_CONFIG) && defined(DDR_VREF_TRAINING_FUNC_PUBLIC)
/**
 * ddr_vref_training_func
 * @void
 *
 *
 */
int ddr_vref_training_func(void *ddrtr_result)
{
	int result = 0;
#if DDR_PHY_NUM == 2
	unsigned int ddr_rng_map0;
	unsigned int ddr_rng_map1;
#endif
	/* vref training disable */
	if (ddr_training_check_bypass(DDR_BYPASS_VREF_MASK))
		return 0;

#if DDR_PHY_NUM == 2
	/*record the original value of AXI*/
	ddr_rng_map0 = REG_READ(DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	ddr_rng_map1 = REG_READ(DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);

	/*set ddrt link to DMC0*/
	REG_WRITE((ddr_rng_map0 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG0_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE((ddr_rng_map1 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG0_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
	result = ddr_vref_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0,
								ddrtr_result);

	/*set ddrt link to DMC1*/
	REG_WRITE((ddr_rng_map0 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG1_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE((ddr_rng_map1 & DDR_AXI_RNG_MASK) + DDR_AXI_RNG1_VAL,
					DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
	result = ddr_vref_training(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1,
								ddrtr_result);

	/*backup to original value*/
	REG_WRITE(ddr_rng_map0, DDR_REG_BASE_AXI + DDR_AXI_RNG0MAP);
	REG_WRITE(ddr_rng_map1, DDR_REG_BASE_AXI + DDR_AXI_RNG1MAP);
#else
	result = ddr_vref_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0,
								ddrtr_result);
#endif

	return result;
}
#else
int ddr_vref_training_func(void *ddrtr_result)
{
	DDR_WARNING("Not support DDR vref training.");
	return 0;
}
#endif /* DDR_VREF_TRAINING_CONFIG */

#if defined(DDR_AC_TRAINING_CONFIG) && defined(DDR_AC_TRAINING_FUNC_PUBLIC)
/**
 * ddr_ac_training_func
 * @void
 *
 *
 */
int ddr_ac_training_func(void)
{
	int result = 0;
	/* AC training disable */
	if (ddr_training_check_bypass(DDR_BYPASS_AC_MASK))
		return 0;

	result  = ddr_ac_training(DDR_REG_BASE_DMC0, DDR_REG_BASE_PHY0);
#if DDR_PHY_NUM == 2
	result += ddr_ac_training(DDR_REG_BASE_DMC1, DDR_REG_BASE_PHY1);
#endif

	return result;
}
#else
int ddr_ac_training_func(void)
{
	DDR_WARNING("Not support DDR AC training.");
	return 0;
}
#endif /* DDR_MPR_TRAINING_CONFIG */

/**
 * ddr_sw_training_if
 * @ddrtr_result
 *
 *
 */
int ddr_sw_training_if(void *ddrtr_result)
{
	return DDR_SW_TRAINING_FUNC(ddrtr_result);
}

/**
 * ddr_hw_training_if
 * @void
 *
 *
 */
int ddr_hw_training_if(void)
{
	return DDR_HW_TRAINING_FUNC();
}

/**
 * ddr_mpr_training_if
 * @void
 *
 *
 */
int ddr_mpr_training_if(void)
{
	return DDR_MPR_TRAINING_FUNC();
}

/**
 * ddr_wl_if
 * @void
 *
 *
 */
int ddr_wl_if(void)
{
	return DDR_WL_FUNC();
}

/**
 * ddr_gating_if
 * @void
 *
 *
 */
int ddr_gating_if(void)
{
	return DDR_GATING_FUNC();
}

/**
 * ddr_dataeye_training_if
 * @ddrtr_result
 *
 *
 */
int ddr_dataeye_training_if(void *ddrtr_result)
{
	return DDR_DATAEYE_TRAINING_FUNC(ddrtr_result);
}

/**
 * ddr_vref_training_if
 * @void
 *
 *
 */
int ddr_vref_training_if(void *ddrtr_result)
{
	return DDR_VREF_TRAINING_FUNC(ddrtr_result);
}

/**
 * ddr_ac_training_if
 * @void
 *
 *
 */
int ddr_ac_training_if(void)
{
	return DDR_AC_TRAINING_FUNC();
}
