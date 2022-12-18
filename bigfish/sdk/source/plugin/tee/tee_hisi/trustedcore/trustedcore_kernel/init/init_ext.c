#include <drv_cipher_intf.h>
#include <sre_securemmu.h>
#include <sre_debug.h>
#include <secure_mem.h>
#include <hi_mmz.h>
#include "debug.h"

extern int sys_security_config(void);
void *sec_mmz_zone = NULL;
void *nonsec_mmz_zone = NULL;

void init_ext(void)
{
	void  *zone =NULL;	
	unsigned long zone_size = 0;
	unsigned long zone_start = NULL;

	if (0 == sys_security_config())
		cprintf("System Security Config... OK!\n");
	else
		cprintf("[\33[31mWARNNING\33[0m]System Security Config... \33[31mFAILED\33[0m!\n");

	
	zone_start = (unsigned long)sec_mem_get_zone_range(SEC_MMZ_MEM, &zone_size);
	ASSERT(zone_start, "Invalid SEC-MMZ address!\n");
	ASSERT(zone_size, "Invalid SEC-MMZ size!\n");
	zone = new_zone("SEC-MMZ", zone_start, zone_size, SECURE_MEM);
	ASSERT(zone, "Create SEC-MMZ failed!\n");
	cprintf("Create SEC-MMZ success!\n");

	zone_size = 0;
	zone_start = NULL;
	zone_start = (unsigned long)sec_mem_get_zone_range(NON_SEC_MMZ_MEM, &zone_size);
	ASSERT(zone_start, "Invalid NONSEC-MMZ address!\n");
	ASSERT(zone_size, "Invalid NONSEC-MMZ size!\n");
	zone = new_zone("NONSEC-MMZ", zone_start, zone_size, NON_SECURE_MEM);
	cprintf("Create NONSEC-MMZ success!\n");

	struct cpu_section desc;
	UINT32 *pgd=secure_page_table;
	desc.dom = SECURE_ACCESS_DOMAIN;
	desc.ap = PRIV_RW_USR_NO;
	desc.xn = L1_EXECUTE_NEVER;
	desc.tex = 0x0;
	desc.c = 0x0;
	desc.b = 0x1;
	desc.ns = 0;
	desc.ng = 0;
	desc.s = 0;

	/*Porting cipher to TrustedCore STB begin*/
	desc.va =  0xF8A00000;
	desc.pa =  0xF8A00000;
	(VOID)map_section_entry(pgd, &desc, 0);
	uart_printf("===map cipher registers 2 ==== addr[%p] === === = !!!\n", desc.pa);

	/*Porting cipher to TrustedCore STB begin*/
	desc.va =  0xF9A00000;
	desc.pa =  0xF9A00000;
	(VOID)map_section_entry(pgd, &desc, 0);
	uart_printf("===map cipher registers 2 ==== addr[%p] === === = !!!\n", desc.pa);

	desc.va =  0xF8000000;
	desc.pa =  0xF8000000;
	(VOID)map_section_entry(pgd, &desc, 0);
	uart_printf("===map cipher rng registers 2 ==== addr[0xF8000000] === === = !!!\n");
	cipher_drv_modInit();
	/* vfmw system registers */
	desc.va =  0xF8A22000;
	desc.pa =  0xF8A22000;
	(VOID)map_section_entry(pgd, &desc, 0);
	uart_printf("===map vfmw system registers ==== addr[0xF8A22000] === === = !!!\n");
	/* vfmw vdm registers */
	desc.va =  0xF8C30000;
	desc.pa =  0xf8c30000;
	(VOID)map_section_entry(pgd, &desc, 0);
	uart_printf("===map vfmw vdm registers ==== addr[0xF8C30000] === === = !!!\n");
	/* vfmw scd registers */
	desc.va =  0xF8C3C000;
	desc.pa =  0xF8C3C000;
	(VOID)map_section_entry(pgd, &desc, 0);
	uart_printf("===map vfmw scd registers 2 ==== addr[0xF8C3C000] === === = !!!\n");

}
