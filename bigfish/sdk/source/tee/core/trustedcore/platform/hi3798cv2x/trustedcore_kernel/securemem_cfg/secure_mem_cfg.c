#include "stdint.h"
#include "sre_debug.h"
#include "secure_mem_cfg.h"
#include "sre_hwi.h"
#include "sre_base.h"
#include "secure_mem.h"
#include "sre_securemmu.h"

#define SECTION_MASK  0xFFF00000
/* -------------------------------------------------------- */

#define RTOS_RGN_SIZE               ((TRUSTEDCORE_MEM_SIZE) * 1024 * 1024)
#define RTOS_RGN_START              (TEXT_BASE & SECTION_MASK)  /* 0x1E000000 */

#define SEC_MMZ_RGN_SIZE            ((TRUSTEDCORE_SEC_MMZ_MEM_SIZE) * 1024 * 1024)
#define SEC_MMZ_RGN_START           (RTOS_RGN_START - SEC_MMZ_RGN_SIZE)  /* 0x1E000000 - 0x02000000 */


#define SEC_SMMU_PAGETABLE_SIZE		(TRUSTEDCORE_SEC_SMMU_PAGETABLE_SIZE * 1024 * 1024)
#define SEC_SMMU_PAGETABLE_START	(SEC_MMZ_RGN_START - SEC_SMMU_PAGETABLE_SIZE)

#if defined(WITH_ARMV8_SUPPORT)
#define ATF_RGN_SIZE            (ATF_MEM_SIZE*1024*1024)
#define ATF_RGN_START           (SEC_SMMU_PAGETABLE_START - ATF_RGN_SIZE)
#endif

/* the size of smmu read/write mem when lack of smmu pagetable must be 0x100 aligned, and _RGN_ALIGN
 * is 0x10000(64k) is enough. And the _RGN_ALIGN is the smallest size of range.
 */
#define SEC_SMMU_RW_ERR_SIZE	(_RGN_ALIGN)
#if defined(WITH_ARMV8_SUPPORT)
#define SEC_SMMU_RW_ERR_START	(ATF_RGN_START - _RGN_ALIGN)
#else
#define SEC_SMMU_RW_ERR_START	(SEC_SMMU_PAGETABLE_START - _RGN_ALIGN)
#endif

#define SHARE_RGN_START             (0)
#define SHARE_RGN_SIZE              (SEC_SMMU_RW_ERR_START - _RGN_ALIGN * 2)

#define _SEC_MID_CFG                (1UL<<_SEC_MID_CPU_SHIFT)
#define _SEC_MASTER_TYPE_CFG        (1UL<<_SEC_MID_CPU_SHIFT)

#define _SEC_MMZ_MID_CFG            ((1UL<<_SEC_MID_CPU_SHIFT) | (1UL<<_SEC_MID_CIPHER_SHIFT) | (1UL<<_SEC_MID_SHA_SEC_SHIFT))

#define _SEC_SMMU_MID_CFG	(0xffffffff)

#define SEC_MEM_ASSERT(X) \
	if (!(X)) { \
		sec_mem_printf("Sec mem assert: ""%s"", file %s, line %d", #X, __FILE__, __LINE__); \
		while(1); \
	}

/* -------------------------------------------------------- */
#if defined(WITH_HI3798CV2X_PLATFORM)
char *master_str[] = {
/*  0 */	"CPU",
/*  1 */	"GPU",
/*  2 */	"MCU",
/*  3 */	"SHA_SEC",
/*  4 */	"SHA_NON_SEC",
/*  5 */	"Cipher",
/*  6 */	"SDIO0/SDIO1/EMMC/FMC",
/*  7 */	"PCIE/SATA/USB3.0",
/*  8 */	"USB2.0",
/*  9 */	"DDRT",
/* 10 */	"JPGD",
/* 11 */	"Invalid",
/* 12 */	"JPGE",
/* 13 */	"VEDU",
/* 14 */	"PGD",
/* 15 */	"TDE",
/* 16 */	"VDP",
/* 17 */	"Invalid",
/* 18 */	"AIAO",
/* 19 */	"Invalid",
/* 20 */	"VDH",
/* 21 */	"Invalid",
/* 22 */	"Invalid",
/* 23 */	"PASTC",
/* 24 */	"Invalid",
/* 25 */	"Invalid",
/* 26 */	"HWC",
/* 27 */	"Invalid",
/* 28 */	"VPSS",
/* 29 */	"Invalid",
/* 30 */	"PVR",
/* 31 */	"GSF",
};
#else
#error "You SHOULD define the master_str array to convert the master id to master name!!"
#endif

struct tzascregion regions[MAX_REGIONS] = {
	/* region 0 */
	{.en = 1,.sp = NONE_RIGHT},
	/* region 1 */
	{.en = 1,.base = RTOS_RGN_START, .size = RTOS_RGN_SIZE, .sp = SECURE_RIGHT, .mid_en = 1, .mid_w = _SEC_MID_CFG, .mid_r = _SEC_MID_CFG},
	/* region 2 */
	{.en = 1,.base = SEC_MMZ_RGN_START, .size = SEC_MMZ_RGN_SIZE, .sp = SECURE_RIGHT, .mid_en = 1, .mid_w = _SEC_MMZ_MID_CFG, .mid_r = _SEC_MMZ_MID_CFG},
	/*region 3*/
	{.en = 1,.base = SEC_SMMU_PAGETABLE_START, .size = SEC_SMMU_PAGETABLE_SIZE, .sp = SECURE_RIGHT, .mid_en = 1, .mid_w = _SEC_SMMU_MID_CFG, .mid_r = _SEC_SMMU_MID_CFG},
	/*region 4*/
	{.en = 1,.base = SEC_SMMU_RW_ERR_START, .size = SEC_SMMU_RW_ERR_SIZE, .sp = SECURE_RIGHT, .mid_en = 1, .mid_w = _SEC_SMMU_MID_CFG, .mid_r = _SEC_SMMU_MID_CFG},
#if defined(WITH_ARMV8_SUPPORT)
    /*region 5*/
	{.en = 1,.base = ATF_RGN_START, .size = ATF_RGN_SIZE, .sp = SECURE_RIGHT, .mid_en = 1, .mid_w = _SEC_MID_CFG, .mid_r = _SEC_MID_CFG},
#endif
};

static struct tzasc_share_region share_region = {
	.en = 1,
	.base = SHARE_RGN_START,
	.size = SHARE_RGN_SIZE,
	.master_type0 = _SEC_MASTER_TYPE_CFG,
};

/* -------------------------------------------------------- */
static uint32_t read_bits(uint64_t addr, uint32_t shift, uint32_t bits)
{
	uint32_t reg_val = sec_mem_readl((uint32_t)addr);
	return GET_BITS_SHIFT(reg_val, bits, shift);
}

static void write_bits(uint64_t addr, uint32_t value, uint32_t shift, uint32_t bits)
{
	uint32_t reg_val = sec_mem_readl((uint32_t)addr);
	reg_val &= ~(BITS_SHIFT_MASK(bits, shift));
	reg_val |= BITS_SHIFT_VAL(value, bits, shift);
	sec_mem_writel(reg_val, (uint32_t)addr);
}

static void set_bit(uint64_t addr, uint32_t shift)
{
	write_bits(addr, 1, shift, 1);
}

static void clear_bit(uint64_t addr, uint32_t shift)
{
	write_bits(addr, 0, shift, 1);
}

static uint32_t read_bit(uint64_t addr, uint32_t shift)
{
	return read_bits(addr, shift, 1);
}

static uint32_t size2regvalue(uint64_t size)
{
	uint32_t size_field = 0;

	for (size_field = 0; (uint64_t)(1ULL << size_field) < MAX_DDR_LEN; size_field++) {
		if (size == (uint64_t)(1ULL << size_field)) {
			break;
		}
	}

	SEC_MEM_ASSERT(MAX_DDR_LEN > (uint64_t)(1ULL << size_field));
	return (size_field - 1);
}

/* -------------------------------------------------------- */
void *sec_mem_get_zone_range(int zone, unsigned long *size)
{
	char *addr = NULL;
	unsigned long zone_size;

	switch(zone) {
		case NON_SEC_OS_MEM:
			addr = SHARE_RGN_START;
			zone_size = SHARE_RGN_SIZE;
			break;
		case SEC_OS_MEM:
			addr = RTOS_RGN_START;
			zone_size = RTOS_RGN_SIZE;
			break;
		case SEC_MMZ_MEM:
			addr = SEC_MMZ_RGN_START;
			zone_size = SEC_MMZ_RGN_SIZE;
			break;
		case NON_SEC_MMZ_MEM:
			/* not support non secure mmz */
			addr = NULL;
			zone_size = 0;
			break;
		default:
			addr = NULL;
			zone_size = 0;
			break;
	};

	if (size)
		*size = zone_size;

	return addr;
}

void sec_mem_get_smmu_rw_err_range(unsigned long *start, unsigned long *size)
{
	*start = SEC_SMMU_RW_ERR_START;
	*size = SEC_SMMU_RW_ERR_SIZE;
}

void sec_mem_get_smmu_pgtbl_range(unsigned long *start, unsigned long *size)
{
	*start = SEC_SMMU_PAGETABLE_START;
	*size = SEC_SMMU_PAGETABLE_SIZE;
}

static int tzasc_regions_cfg(void)
{
	int i;
	/* Config the reserve regions */
	for(i = 0; i < (sizeof(regions)/sizeof(regions[0])); i++) {
		if (!(regions[i].en))
			continue;

		/* Config region0 */
		if (0 == i) {
			clear_bit(SET_RGN_ATTR(i), _SEC_RGN_MID_EN_SHIFT);
			set_bit(SET_RGN_ATTR(i), _SEC_RGN_SEC_INV_SHIFT);
			write_bits(SET_RGN_ATTR(i), regions[i].sp, _SEC_RGN_SP_SHIFT, _SEC_RGN_SP_BITS);
			set_bit(SEC_RGN_MAP(i), _SEC_RGN_EN_SHIFT);
			continue;
		}

		SEC_MEM_ASSERT(regions[i].base < (regions[i].base + regions[i].size));
		SEC_MEM_ASSERT(regions[i].base < (regions[i].base + _RGN_ALIGN));
		SEC_MEM_ASSERT(regions[i].size < MAX_DDR_LEN);
		/* Set region base addr */
		write_bits(SEC_RGN_MAP(i), (uint32_t)((regions[i].base + _RGN_ALIGN - 1)>>_RGN_ALIGN_SHIFT),
				_SEC_RGN_BASE_ADDR_SHIFT, _SEC_RGN_BASE_ADDR_BITS);
		/* Set region size, TODO: to check if the region size must be 64KB*2^n !! */
		write_bits(SEC_RGN_MAP(i), size2regvalue(regions[i].size), _SEC_RGN_SIZE_SHIFT, _SEC_RGN_SIZE_BITS);
		/* Enable region sec inv */
		set_bit(SET_RGN_ATTR(i), _SEC_RGN_SEC_INV_SHIFT);
		write_bits(SET_RGN_ATTR(i), regions[i].sp, _SEC_RGN_SP_SHIFT, _SEC_RGN_SP_BITS);
		/* If mid match needed, set the mid_w and mid_r reg */
		if (regions[i].mid_en) {
			set_bit(SET_RGN_ATTR(i), _SEC_RGN_MID_EN_SHIFT);
			sec_mem_writel(regions[i].mid_w, SET_RGN_MID_W(i));
			sec_mem_writel(regions[i].mid_r, SET_RGN_MID_R(i));
		}

		/* Enable region */
		set_bit(SEC_RGN_MAP(i), _SEC_RGN_EN_SHIFT);
	}
	/* Config the master type for reserve regions */
	sec_mem_writel(_SEC_MASTER_TYPE_CFG, SEC_MASTER_TYPE_RSV);

	/* Config the share region */
	if (share_region.en) {
		uint64_t base, size;
		base = (share_region.base + _RGN_ALIGN - 1)&(~((1ULL<<_RGN_ALIGN_SHIFT) - 1));
		size = (share_region.size + _RGN_ALIGN - 1)&(~((1ULL<<_RGN_ALIGN_SHIFT) - 1));
		SEC_MEM_ASSERT(base < (base + size));
		SEC_MEM_ASSERT(base < (base + _RGN_ALIGN));
		SEC_MEM_ASSERT(size < MAX_DDR_LEN);
		write_bits(SEC_SHARE_RGN_START, base, _SEC_SHARE_RGN_START_SHIFT, _SEC_SHARE_RGN_START_BITS);
		write_bits(SEC_SHARE_RGN_END, base + size, _SEC_SHARE_RGN_END_SHIFT, _SEC_SHARE_RGN_END_BITS);
		/* Config the master type for share region */
		sec_mem_writel(share_region.master_type0, SEC_MASTER_TYPE_SHARE);
		set_bit(SEC_SHARE_RGN_EN, _SEC_SHARE_RGN_EN_SHIFT);
	}
}

static int tzasc_config(void)
{

	uint32_t lockdown_sel;

	tzasc_regions_cfg();
	random_delay(); /* for security */
	tzasc_regions_cfg(); /* security: double set for special config */

	/* Not bypass TZASC */
	write_bits(SEC_BYPASS, 0, _SEC_BYPASS_SHIFT, _SEC_BYPASS_BITS);
	random_delay(); /* for security */
	if (0 != read_bits(SEC_BYPASS, _SEC_BYPASS_SHIFT, _SEC_BYPASS_BITS)) {
		uart_printf_func("[%s][%d] SEC_BYPASS check fail \n", __func__, __LINE__);
		sec_sys_reset();
	}

	/* Set the lockdown selection */
	lockdown_sel = sec_mem_readl(SEC_LOCKDOWN_SEL);
	lockdown_sel |= _SEC_LOCKDOWN_SEL_CFG;
	sec_mem_writel(lockdown_sel, SEC_LOCKDOWN_SEL);
	random_delay(); /* for security */
	if (lockdown_sel != sec_mem_readl(SEC_LOCKDOWN_SEL)) {
		uart_printf_func("[%s][%d] SEC_LOCKDOWN_SEL check fail \n", __func__, __LINE__);
		sec_sys_reset();
	}

	return 0;
}

static int tzpc_config(void)
{

	/* Enanble security timer, TODO: to be checked */
	sec_mem_writel(0xFFF9FFFF, SEC_ATTR_CTRL_0_REG);

#if 0
    /* c51 will operate the ddrc, so can't lock it here */
	/* Lock down ddrc, TODO: to be checked*/
	sec_mem_writel(0x1F, SEC_DDRC_CTRL_REG);
#endif

	sec_mem_writel(0x1, SEC_MISC_CTRL_REG);

	/* Lock down tzasc/tzpc config */
	set_bit(TZASC_SEC_LOCK_REG, _SEC_BOOT_LOCK_SHIFT);

	random_delay(); /* for security */
	if (1 != read_bit(TZASC_SEC_LOCK_REG, _SEC_BOOT_LOCK_SHIFT)) {
		uart_printf_func("[%s][%d] TZASC_SEC_LOCK_REG check fail\n", __func__, __LINE__);
		sec_sys_reset();
	}

	return 0;
}

static void dump_reg(char *phyaddr, uint32_t size)
{
	char *p = 0;

	if (phyaddr == NULL) {
		sec_mem_printf("%s:Invalid addr!\n", __func__);
		return;
	}

	p = phyaddr;
	while (p < (phyaddr + size)) {
		if (!((p - phyaddr) % 16) && ((p - phyaddr) != 0)) {
			uart_printf_func("\n");
			sec_mem_printf("0x%X: %X ", p, *((unsigned int *)p));
		} else if ((p - phyaddr) == 0) {
			sec_mem_printf("0x%X: %X ", p, *((unsigned int *)p));
		} else
			uart_printf_func("%X ", *((unsigned int *)p));

		p+=4;
	}
}
unsigned int dump_secmem_reg(void)
{
#if 0
	sec_mem_printf("------------------------TZPC Reg------------------------\n");
	dump_reg((char *)TZPC_BASE_ADDR, 0x40);
	uart_printf_func("\n");

	sec_mem_printf("------------------------TZASC Reg-----------------------\n");
	dump_reg((char *)TZASC_BASE_ADDR, 0x320);
	uart_printf_func("\n");
#endif
	return SRE_OK;
}

static int tzasc_interrupt_handle(int arg)
{
	uint32_t int_status, mid, cmdid, access_type, ns, privilege, overrun;
	uint32_t fault_addr_low, fault_addr_high;
	uint32_t share_fail_status;

	sec_mem_printf("------------------------------------------------------------------\n");
	sec_mem_printf("Warning: Unauthorized read/write operation detected!!\n");

#ifdef SEC_MEM_SELFTEST
	int_status = 1;
#else
	int_status = read_bits(SEC_INT_STATUS, _SEC_INT_STATUS_SHIFT, _SEC_INT_STATUS_BITS);
#endif

	if (int_status) {
		fault_addr_low = read_bits(SEC_FAIL_ADDRESS_LOW, _SEC_FAIL_CMD_ADDR_LOW_SHIFT, _SEC_FAIL_CMD_ADDR_BITS);
		fault_addr_high = read_bits(SEC_FAIL_STATUS, _SEC_FAIL_CMD_ADDR_HIGH_SHIFT, _SEC_FAIL_CMD_ADDR_HIGH_BITS);
		mid = read_bits(SEC_FAIL_ID, _SEC_FAIL_CMD_MID_SHIFT, _SEC_FAIL_CMD_MID_BITS);
		cmdid = read_bits(SEC_FAIL_ID, _SEC_FAIL_CMD_ID_SHIFT, _SEC_FAIL_CMD_ID_BITS);
		access_type = read_bits(SEC_FAIL_STATUS, _SEC_FAIL_CMD_ACC_TYPE_SHIFT, _SEC_FAIL_CMD_ACC_TYPE_BITS);
		ns = read_bits(SEC_FAIL_STATUS, _SEC_FAIL_CMD_NS_SHIFT, _SEC_FAIL_CMD_NS_BITS);
		privilege = read_bits(SEC_FAIL_STATUS, _SEC_FAIL_CMD_PRVLG_SHIFT, _SEC_FAIL_CMD_PRVLG_BITS);
		overrun = read_bits(SEC_INT_STATUS, _SEC_INT_OVERRUN_SHIFT, _SEC_INT_OVERRUN_BITS);

		sec_mem_printf("Fault Access Addr(Reserve Region): 0x%X%X\n", fault_addr_high, fault_addr_low);
		sec_mem_printf("Fault CMD ID: 0x%X\n", cmdid);
#ifdef SEC_MEM_SELFTEST
		for (mid = 0;mid < sizeof(master_str)/sizeof(master_str[0]);mid++)
#endif
		sec_mem_printf("Fault Master ID: 0x%X (%s)\n", mid, (mid >= sizeof(master_str)/sizeof(master_str[0]))? "Invalid" : master_str[mid]);
		sec_mem_printf("Fault Access Type: %s\n", access_type ? "write" : "read");
		sec_mem_printf("Fault Access From: %s World\n", ns ? "Nonsecure" : "Secure");
		sec_mem_printf("Fault Privileged Mode (Only valid for CPU): %s\n", privilege ? "Privileged" : "Unprivileged");
		sec_mem_printf("Fault More than one times: %s\n", overrun ? "Yes" : "No");
	}

#ifdef SEC_MEM_SELFTEST
	share_fail_status = 1;
#else
	share_fail_status = read_bits(SEC_SHARE_RGN_FAIL_CMD_STATUS, _SEC_SHARE_RGN_FAIL_STATUS_SHIFT, _SEC_SHARE_RGN_FAIL_STATUS_BITS);
#endif
	if (share_fail_status) {
		fault_addr_low = sec_mem_readl(SEC_SHARE_RGN_FAIL_CMD_ADDR);
		mid = read_bits(SEC_SHARE_RGN_FAIL_ID, _SEC_SHARE_RGN_FAIL_MID_SHIFT, _SEC_SHARE_RGN_FAIL_MID_BITS);
		cmdid = read_bits(SEC_SHARE_RGN_FAIL_ID, _SEC_SHARE_RGN_FAIL_CMDID_SHIFT, _SEC_SHARE_RGN_FAIL_CMDID_BITS);

		sec_mem_printf("Fault Access Addr(Share Region): 0x%X\n", fault_addr_low);
		sec_mem_printf("Fault CMD ID: 0x%X\n", cmdid);
#ifdef SEC_MEM_SELFTEST
		for (mid = 0;mid < sizeof(master_str)/sizeof(master_str[0]);mid++)
#endif
		sec_mem_printf("Fault Master ID: 0x%X (%s)\n", mid, (mid >= sizeof(master_str)/sizeof(master_str[0]))? "Invalid" : master_str[mid]);
		/* clear interrupt*/
		write_bits(SEC_SHARE_RGN_FAIL_CMD_STATUS, 1, _SEC_SHARE_RGN_FAIL_STATUS_SHIFT, _SEC_SHARE_RGN_FAIL_STATUS_BITS);
	}

	sec_mem_writel(0x12345678, SEC_INT_CLEAR); /* clear interrupt*/

	dump_secmem_reg();
	sec_mem_printf("------------------------------------------------------------------\n");
	return SRE_OK;
}

static int tzasc_interrupt_register(void)
{
	unsigned int ret;

	sec_mem_printf("Create tzasc interrupt handle.\n");
	/*create intrrupt id:15*/
	ret = SRE_HwiCreate(SEC_TZASC_ERR_IRQ, 0xa0, 0, (HWI_PROC_FUNC)tzasc_interrupt_handle, 0);
	if (ret != SRE_OK) {
		sec_mem_printf("Failed to create tzasc interrupt!\n");
		goto err;
	}

	sec_mem_printf("Enable the tzasc interrupt.\n");
	ret = SRE_HwiEnable(SEC_TZASC_ERR_IRQ);
	if (ret != SRE_OK) {
		sec_mem_printf("Failed to enable tzasc interrupt!\n");
		goto err;
	}

	return 0;
err:
	return -1;
}

unsigned int sec_get_rng(unsigned int *num)
{
	unsigned int i = 0;
	unsigned int rng_value = 0x4B693C87;
	unsigned int rng_stat;

	sec_mem_writel(0xA, SC_RNG_DATA_CTRL);
	for (i = 0; i < 0x10000; i++) {/* 约10ms */
		asm("nop");
		asm("nop");
		rng_stat = sec_mem_readl(SC_RNG_DATA_CNT);
		if(((rng_stat >> 8) & 0x3F) > 0) {
			rng_value = sec_mem_readl(SC_RNG_DATA_VAL);
			break;
		}
	}

	if (i >= 0x10000) {
		uart_printf_func("[%s][%d]get rng time out.\n", __func__, __LINE__);
		return -1;
	}

	if ((0 == rng_value) || (0xffffffff == rng_value) || (0x4B693C87 == rng_value)) {
		uart_printf_func("[%s][%d]get rng failed.\n", __func__, __LINE__);
		return -1;
	}

	*num = rng_value;
	return 0;
}

/* random number < 0x4000, delay about 500us*/
void random_delay(void)
{
	volatile unsigned int loop = 0xffffffff;

	sec_get_rng(&loop);
	loop = loop & 0x3fff;
	while(loop--) {
		asm("nop");
	}
}

void sec_sys_reset(void)
{
	/* write any value to sysres will reboot */
	sec_mem_writel(0x12345678, SC_SYSRES_REG);
	while(1);
}

/**
 * ddr_rollback_check
 * @void
 *
 * 单板物理上是1G DDR，烧个2G内存配置的安全OS，tzasc 会配置[0x7E000000,0x80000000]为
 * 安全内存。因为DDR 回卷，实际安全OS 运行在[0x3E000000, 0x40000000]。因此可以通过
 * 访问0x3E000000获取0x7E000000的内容，为避免安全内存泄露，需要检查安全OS是否运行
 * 在卷绕的地址上。tzasc会配置可访问空间，即往后的回卷地址[0xBE000000,0xC0000000]不可
 * 访问，所以不用检查。
 */
static int ddr_rollback_check(void)
{
	unsigned int rand_num;
	unsigned int virt_addr = &rand_num;
	unsigned int phys_addr = virt_to_phys(virt_addr);
	int ret;

	if (sec_get_rng(&rand_num))
		return -1;

	v7_dma_flush_range(virt_addr, virt_addr + sizeof(int) - 1);

	uart_printf("[%s][%d]phys_addr[0x%x] virt_addr[0x%x] val[0x%x]\n",
		__func__, __LINE__, phys_addr, virt_addr, *((unsigned int *)virt_addr));

	while (phys_addr > DDR_SIZE_MIN) {
		phys_addr -= DDR_SIZE_MIN;
		ret = SRE_mem_remap(phys_addr, sizeof(int), &virt_addr, secure, non_cache);
		if (ret) {
			uart_printf_func("[%s][%d]mmap fail.\n", __func__, __LINE__);
			return -1;
		}

		uart_printf("[%s][%d]phys_addr[0x%x] virt_addr[0x%x] val[0x%x]\n",
			__func__, __LINE__, phys_addr, virt_addr, *((unsigned int *)virt_addr));
		if (rand_num == *((unsigned int *)virt_addr)) {
			SRE_mem_unmap(virt_addr, sizeof(int));
			return -1;
		}
		SRE_mem_unmap(virt_addr, sizeof(int));
	}
	return 0;
}

int sys_security_config(void)
{
	int ret = 0;
#if 0
	uart_printf_func("-----------------------------------------------------------\n");
	uart_printf_func("TEE Mem Layout:\n");
	uart_printf_func("Firmware                  0x%X - 0x%X, 0x%X\n", ATF_RGN_START, ATF_RGN_START + ATF_RGN_SIZE, ATF_RGN_SIZE);
	uart_printf_func("Secure SMMU ERR Bin       0x%X - 0x%X, 0x%X\n", SEC_SMMU_RW_ERR_START, SEC_SMMU_RW_ERR_START + SEC_SMMU_RW_ERR_SIZE, SEC_SMMU_RW_ERR_SIZE);
	uart_printf_func("Secure SMMU Pagetable     0x%X - 0x%X, 0x%X\n", SEC_SMMU_PAGETABLE_START,  SEC_SMMU_PAGETABLE_START + SEC_SMMU_PAGETABLE_SIZE, SEC_SMMU_PAGETABLE_SIZE);
	uart_printf_func("Secure MMZ                0x%X - 0x%X, 0x%X\n", SEC_MMZ_RGN_START, SEC_MMZ_RGN_START + SEC_MMZ_RGN_SIZE, SEC_MMZ_RGN_SIZE);
	uart_printf_func("Secure OS                 0x%X - 0x%X, 0x%X\n", RTOS_RGN_START, RTOS_RGN_START + RTOS_RGN_SIZE, RTOS_RGN_SIZE);
	uart_printf_func("-----------------------------------------------------------\n");
#endif
	/* double check DDR whether roolback */
	if (ddr_rollback_check()) {
		uart_printf_func("[%s][%d]DDR may be rollback. Check again\n", __func__, __LINE__);
		if (ddr_rollback_check()) {
			uart_printf_func("[%s][%d]DDR rollback, reset now\n", __func__, __LINE__);
			sec_sys_reset();
		}
	}

	random_delay();
	ret = tzasc_config();
	if (ret < 0) {
		sec_mem_printf("Fail to config tzasc!!\n");
		return -1;
	}

	random_delay();
	ret = tzpc_config();
	if (ret < 0) {
		sec_mem_printf("Fail to config tzpc!!\n");
		return -1;
	}
#if 0
	ret = tzasc_interrupt_register();
	if (ret < 0)
		return -1;
#endif

#ifdef SEC_MEM_DEBUG
	dump_secmem_reg();
#endif
	return 0;
}

unsigned int initSecureContentPath(unsigned int addr, unsigned int size)
{
	uart_printf_func("%s ERROR: We SHOULD NOT run this function!!!\n", __func__);
	while(1);
	return 0;
}

unsigned int terminateSecureContentPath(unsigned int addr, unsigned int size)
{
	uart_printf_func("%s ERROR: We SHOULD NOT run this function!!!\n", __func__);
	while(1);
	return 0;
}

unsigned int isSecureContentMemory(unsigned int addr, unsigned int size)
{
	uart_printf_func("%s ERROR: We SHOULD NOT run this function!!!\n", __func__);
	while(1);
	return 0;
}

