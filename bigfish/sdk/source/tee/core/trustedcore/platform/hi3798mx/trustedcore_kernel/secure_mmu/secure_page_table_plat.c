#include "sre_securemmu.h"
#include "sre_taskmem.h"
#include "platform.h"

secure_mmu_config platform_config[] = {
	/* TODO: XXX */
	/* TODO:  */
	{((TEXT_BASE) - 0x100000), 0x100000, DUMP_DDR, {PRIV_RW_USR_RW, 1, 1, 1, L1_EXECUTE_ALLOW, L1_EXECUTE_NEVER, 1}, 0, 0},

    /* Trustedcore RAM:TA MEM (25M) */
    {TASK_BASE, TRUSTEDCORE_TA_RUN_MEM_SIZE<<TASK_MEM_SHIFT, TASK_MEM_LOAD_ADDRESS, {PRIV_RW_USR_NO, 1, 1, 1, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 1}, 0, 0},

	 /* GIC/TZASC/TZPC */
	{0xF8A00000, 0x100000, 0xF8A00000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},

	/* UART0 */
    	//0, 1, 0 represent tex, b, c: non-cacheable
    	{0xF8B00000, 0x100000, 0xF8B00000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
    	{0xF8A00000, 0x100000, 0xF8A00000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
    	{0xF9A00000, 0x100000, 0xF9A00000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
    	{0xF8000000, 0x100000, 0xF8000000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
        /* vfmw system registers */
        {0xF8A22000, 0x100000, 0xF8A22000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
        /* vfmw vdm registers */
        {0xF8C30000, 0x100000, 0xF8C30000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
        /* vfmw scd registers */
        {0xF8C3C000, 0x100000, 0xF8C3C000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
        /* vdp */
        {0xF8CC0000, 0x100000, 0xF8CC0000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
        /* vpss */
        {0xF8CB0000, 0x100000, 0xF8CB0000, {PRIV_RW_USR_NO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
	    /*SRAM registers*/
    	{0xFFF00000, 0x100000, 0xFFF00000, {PRIV_RW_USR_RW, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
		
		/* DEMUX */
		{0xF9C00000, 0x10000, 0xF9C00000, {PRIV_RW_USR_RO, 0, 1, 0, L1_EXECUTE_NEVER, L1_EXECUTE_NEVER, 0}, 0, 0},
};

UINT32 platform_config_items = sizeof(platform_config)/sizeof(secure_mmu_config);
