#include "sre_typedef.h"
#include "sre_debug.h"
#include "debug.h"
#include "secure_mem_cfg.h"

#include <secure_mem.h>
#include <sec_mmz.h>

extern int smmu_init(void);
void platform_init_later(void)
{
#if defined(WITH_HISI_SEC_MMZ)	
	void  *zone =NULL;
	unsigned long zone_size = 0;
	unsigned long zone_start = NULL;
#endif

	uart_printf("Start system security config!\n");
	if (0 == sys_security_config())
	      uart_printf("System Security Config... OK!\n");
	else
	      uart_printf("[\33[31mWARNNING\33[0m]System Security Config... \33[31mFAILED\33[0m!\n");

	random_delay(); /* for security */
	if (0 != GET_BITS_SHIFT(sec_mem_readl(SEC_BYPASS), _SEC_BYPASS_BITS, _SEC_BYPASS_SHIFT)) {
		uart_printf_func("[%s][%d] SEC_BYPASS check fail \n", __func__, __LINE__);
		sec_sys_reset();
	}
	
	random_delay(); /* for security */
	if (1 != GET_BITS_SHIFT(sec_mem_readl(TZASC_SEC_LOCK_REG), 1, _SEC_BOOT_LOCK_SHIFT)) {
		uart_printf_func("[%s][%d] TZASC_SEC_LOCK_REG check fail\n", __func__, __LINE__);
		sec_sys_reset();
	}
	

#if defined(WITH_HISI_SMMU)
	/* init smmu reg    */
	smmu_init();

#endif

#if defined(WITH_HISI_SEC_MMZ)	
	/* init mmz */
	zone_start = (unsigned long)sec_mem_get_zone_range(SEC_MMZ_MEM, &zone_size);
	ASSERT(zone_start, "Invalid SEC-MMZ address!\n");
	ASSERT(zone_size, "Invalid SEC-MMZ size!\n");
	zone = new_zone("SEC-MMZ", zone_start, zone_size, SECURE_MEM);
	ASSERT(zone, "Create SEC-MMZ failed!\n");
	uart_printf("Create SEC-MMZ(0x%X, 0x%X) success!\n", zone_start, zone_size);
#endif	
}
