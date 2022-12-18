#include "sre_debug.h"
#include "secure_mem_cfg.h"
#include "sre_hwi.h"
#include "sre_securemmu.h"

#define read_reg(addr, val)   ((val) = (*(volatile unsigned int *)(addr)))
#define write_reg(addr, val)  ((*(volatile unsigned int *)(addr)) = (val))
#define SEC_MEM_ASSERT(X) \
	if (!(X)) { \
		sec_mem_printf("Sec mem assert: ""%s"", file %s, line %d", #X, __FILE__, __LINE__); \
		while(1); \
	}

#ifdef CONFIG_SYS_MEM_1G
#include "secure_regions_cfg_1G.c"
#endif

#ifdef CONFIG_SYS_MEM_2G
#include "secure_regions_cfg_2G.c"
#endif

#ifdef CONFIG_SYS_MEM_512M
#include "secure_regions_cfg_512M.c"
#endif

static int size2regvalue(unsigned long long size)
{
	unsigned int size_field = 0;

	for (size_field = 0; (1 << size_field) < MAX_DDR_LEN; size_field++) {
		if (size == (1 << size_field)) {
			break;
		}
	}

	SEC_MEM_ASSERT(MAX_DDR_LEN != (1 << size_field));

	if (MAX_DDR_LEN == (1 << size_field)) {
		return -1;
	} else {
		return (int)(size_field - 1);
	}
}

static void en_security_inv(int port_base)
{
	union tzasc_sec_security_inv_reg tzasc_sec_inv;

	tzasc_sec_inv.u32 = 0;
	read_reg(port_base + SEC_INVERSION_EN_REG, tzasc_sec_inv.u32);
	tzasc_sec_inv.bits.sec_inv_en = 1;
	write_reg(port_base + SEC_INVERSION_EN_REG, tzasc_sec_inv.u32);
}

static void en_ddr_port(unsigned int port_base)
{
	union tzasc_sec_action_reg action;

	action.u32 = 0;
	read_reg(port_base + SEC_ACTION_REG, action.u32);
	action.bits.sta_ckg_apb = 1;
	action.bits.int_enable =1;
	write_reg(port_base + SEC_ACTION_REG, action.u32);
}

static void set_master_type(unsigned int port_base, unsigned int type)
{
	union tzasc_sec_master_type_reg reg;

	reg.u32 = 0;
	read_reg(port_base + SEC_MASTER_TYPE_REG, reg.u32);
	reg.bits.master_type = type;
	write_reg(port_base + SEC_MASTER_TYPE_REG, reg.u32);
}

static void lockdown_port(unsigned int port_base)
{
	union tzasc_sec_lockdown_range_reg lockdown_range;
	union tzasc_sec_lockdown_sel_reg lockdownsel;
	union tzasc_sec_lockdown_sel_reg lock_check;

	lockdown_range.u32 = 0;
	read_reg(port_base + SEC_LOCKDOWN_RANGE_REG, lockdown_range.u32);
	lockdown_range.bits.lockdown_regions = 0xF;//(1 << sizeof(lockdown_range.bits.lockdown_regions)) - 1;//0x7;
	lockdown_range.bits.lockdown_enable = 1;
	write_reg(port_base + SEC_LOCKDOWN_RANGE_REG, lockdown_range.u32);

	lockdownsel.u32 = 0;
	read_reg(port_base + SEC_LOCKDOWN_SEL_REG, lockdownsel.u32);
	lockdownsel.bits.region_register = 1;
	lockdownsel.bits.security_inv = 1;
	lockdownsel.bits.security_bypass = 1;
	lockdownsel.bits.master_type = 1;
	write_reg(port_base + SEC_LOCKDOWN_SEL_REG, lockdownsel.u32);
	
	random_delay(); /* check register again for security */
	read_reg(port_base + SEC_LOCKDOWN_SEL_REG, lock_check.u32);
	if (lockdownsel.u32 != lock_check.u32) {
		uart_printf_func("[%s][%d] SEC_LOCKDOWN_RANGE_REG check faile \n", __func__, __LINE__);
		sec_sys_reset();
	}	
}

static unsigned int get_nr_regions(unsigned int port_base)
{
	union tzasc_sec_cfg_reg sec_cfg;

	read_reg(port_base + SEC_CONFIG_REG, sec_cfg.u32);
	return sec_cfg.bits.nr_of_regions;
}

static int ddr_port_config(unsigned int port, unsigned int master_type, struct tzascregion region[MAX_REGIONS])
{
	int i = 0;

	union tzasc_sec_security_bypass_reg bypass;
	union tzasc_region_attr_reg attr;
	union tzasc_region_setup_low_reg region_setup_low;
	unsigned long long size = 0;
	unsigned int port_base = 0;
	unsigned int nr_regions = 0;

	port_base = MDDRC_PORT_BASE_ADDR(port);

	nr_regions = get_nr_regions(port_base);
	SEC_MEM_ASSERT(nr_regions <= MAX_REGIONS);

	/* Enable port */
	en_ddr_port(port_base);

	/* Enable security inversion */
	en_security_inv(port_base);

	/* Set the master type */
	set_master_type(port_base, master_type);

	for (i = 0; i < nr_regions; i++) {
		if (0 == region[i].en)
		      continue;

		region_setup_low.u32 = 0;
		read_reg((port_base + SEC_REGION_SETUP_LOW_REG(i)), region_setup_low.u32);
		region_setup_low.bits.base_address_low = (region[i].base >> 15);
		write_reg((port_base + SEC_REGION_SETUP_LOW_REG(i)), region_setup_low.u32);

		attr.u32 = 0;
		read_reg((port_base + SET_REGION_ATTRIBUTES(i)), attr.u32);

		attr.bits.en = region[i].en;
		attr.bits.subregion_disable = 0;
		attr.bits.sp = region[i].sp;

		if (0 != i) {
			size = size2regvalue(region[i].size);
			attr.bits.size = size;
		}
		write_reg((port_base + SET_REGION_ATTRIBUTES(i)), attr.u32);
		sec_mem_dbginfo("config region %d: en=%d, base=0x%x, size=0x%x, sp=0x%x\n",
			i, region[i].en, region[i].base, region[i].size, region[i].sp);
	}

	/*Set bypass */
	bypass.u32 = 0;
	read_reg((port_base + SEC_BYPASS_REG), bypass.u32);
	bypass.bits.bypass = 0;
	write_reg((port_base + SEC_BYPASS_REG), bypass.u32);
	
	random_delay(); /* check register again for security */
	read_reg((port_base + SEC_BYPASS_REG), bypass.u32);
	if (0 != bypass.bits.bypass) {
		uart_printf_func("[%s][%d] SEC_BYPASS_REG check faile \n", __func__, __LINE__);
		sec_sys_reset();
	}	

	/* Lock down port */
	lockdown_port(port_base);

	return 0;
}

static int config_ddr_zone(void)
{
	int ret = 0;
	unsigned int i = 0;

	for (i = 0; i < sizeof(ports) / sizeof(ports[0]); i++) {
		ret = ddr_port_config(i, ports[i].master_type, ports[i].regions);
		if (ret) {
			sec_mem_printf("TZASC%d configure failed!\n", i);
			return ret;
		}
		sec_mem_printf("TZASC%d configure success!\n", i);
	}

	return 0;
}

static int config_module_attr(void)
{
	union tzpc_attr_ctrl0_reg secattrctrl;
	union tzpc_misc_ctrl_reg secmiscctrl;
	union tzpc_tzasc_sec_lock_reg seclock;

	/* Enanble security timer, timer8~9 for hi3798mx */
	secattrctrl.u32 = 0xffffffff;
	secattrctrl.bits.timer_sec = 0;
    secattrctrl.bits.sha = 0;
	write_reg(SEC_ATTR_CTRL_0_REG, secattrctrl.u32);

	/* Lock down ddrc */
	secmiscctrl.u32 = 0;
	read_reg(SEC_MISC_CTRL_REG, secmiscctrl.u32);
	secmiscctrl.bits.ddrc_dmc_lock = 0x1;
	secmiscctrl.bits.ddrc_phy_lock = 0x1;
	secmiscctrl.bits.ddrc_rbc_lock = 0x1;
	write_reg(SEC_MISC_CTRL_REG, secmiscctrl.u32);

	/* Lock down port tzasc config */
	seclock.u32 = 0;
	read_reg(TZASC_SEC_LOCK_REG, seclock.u32);
	seclock.bits.sec_boot_lock = 1;
	write_reg(TZASC_SEC_LOCK_REG, seclock.u32);

	return 0;
}

#define INT_SECURE                  0x0
char *port_mod_str[] = {
	"CPU",
	"OTP/KeyLadder/Cipher/PVR/SDIO/ETH/USB2OTG/USB2HOST/USB3/NANDC/DMAC",
	"AIAO/VDP/HDMITX",
	"DDRT/JPGD0/BPD/PGD/VEDU/JPGE",
	"VDH/TDE",
	"VPSS0",
	"GPU",
	NULL
};

static void dump_reg(char *phyaddr, unsigned int size)
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
	char *port_base = 0;
	int i;
	union tzasc_sec_int_status_reg int_status;
	union tzasc_sec_fail_addr_low_reg fault_addr;
	union tzasc_fail_status_reg fault_status;
	union tzasc_sec_fail_id_reg  fault_id;

	sec_mem_printf("------------------------TZPC Reg------------------------\n");
	dump_reg(TZPC_BASE_ADDR, 0x40);
	uart_printf_func("\n");
	sec_mem_printf("--------------------------------------------------------\n");

	for (i = 0; i < sizeof(ports) / sizeof(ports[0]); i++) {
		sec_mem_printf("--------------------------------------------------------\n");
		port_base = MDDRC_PORT_BASE_ADDR(i);
		read_reg(port_base + SEC_FAIL_STATUS_REG, fault_status.u32);
		read_reg(port_base + SEC_FAIL_ID_REG, fault_id.u32);
		read_reg(port_base + SEC_FAIL_ADDRESS_LOW_REG, fault_addr.u32);
		sec_mem_printf("Port: 0x%X (%s)\n", i, port_mod_str[i]);
		sec_mem_printf("Fault Addr: 0x%X\n", fault_addr.u32);
		sec_mem_printf("Fault ID: 0x%X\n", fault_id.u32);
		sec_mem_printf("Access Type: %s\n", fault_status.bits.fail_acc_type?"write":"read");
		sec_mem_printf("Access World: %s\n", fault_status.bits.fail_nonsec?"Nonsecure":"Secure");
		sec_mem_printf("Privileged Mode: %s\n", fault_status.bits.fail_privil?"Privileged":"Unprivileged");
		sec_mem_printf("Fault More than one times: %s\n", int_status.bits.overrun?"Yes":"No");
		sec_mem_printf("---------------------Port TZASC Reg---------------------\n");
		dump_reg(port_base, 0x310);
		uart_printf_func("\n");
	}

	return SRE_OK;
}

unsigned int tzasc_int_handle(unsigned int arg)
{
	char *port_base = 0;
	int i;
	union tzasc_sec_int_status_reg int_status;
	union tzasc_sec_fail_addr_low_reg fault_addr;
	union tzasc_fail_status_reg fault_status;
	union tzasc_sec_fail_id_reg  fault_id;

	sec_mem_printf("------------------------------------------------------------------\n");
	sec_mem_printf("Warning: Unauthorized read/write operation detected!!\n");

	for (i = 0; i < sizeof(ports) / sizeof(ports[0]); i++) {
		port_base = MDDRC_PORT_BASE_ADDR(i);
		read_reg(port_base + SEC_INT_STATUS_REG, int_status.u32);
		if (int_status.bits.status) {
			write_reg(port_base + SEC_INT_CLEAR_REG, 0x12345678);
			read_reg(port_base + SEC_FAIL_STATUS_REG, fault_status.u32);
			read_reg(port_base + SEC_FAIL_ID_REG, fault_id.u32);
			read_reg(port_base + SEC_FAIL_ADDRESS_LOW_REG, fault_addr.u32);
			sec_mem_printf("Port: 0x%X (%s)\n", i, port_mod_str[i]);
			sec_mem_printf("Fault Addr: 0x%X\n", fault_addr.u32);
			sec_mem_printf("Fault ID: 0x%X\n", fault_id.u32);
			sec_mem_printf("Access Type: %s\n", fault_status.bits.fail_acc_type?"write":"read");
			sec_mem_printf("Access World: %s\n", fault_status.bits.fail_nonsec?"Nonsecure":"Secure");
			sec_mem_printf("Privileged Mode: %s\n", fault_status.bits.fail_privil?"Privileged":"Unprivileged");
			sec_mem_printf("Fault More than one times: %s\n", int_status.bits.overrun?"Yes":"No");
			sec_mem_printf("---------------------Port TZASC Reg---------------------\n");
			dump_reg(port_base, 0x310);
		}
	}

	uart_printf_func("\n");
	sec_mem_printf("------------------------TZPC Reg------------------------\n");
	dump_reg(TZPC_BASE_ADDR, 0x40);
	uart_printf_func("\n");
	sec_mem_printf("------------------------------------------------------------------\n");

	//dump_secmem_reg();
	return SRE_OK;
}

int register_interrupt(void)
{
	unsigned int ret;

	sec_mem_printf("Create tzasc interrupt handle.\n");
	/*create intrrupt id:15*/
	ret = SRE_HwiCreate(110, 0xa0, INT_SECURE, tzasc_int_handle, 111);
	if (ret != SRE_OK) {
		sec_mem_printf("Failed to create tzasc interrupt!\n");
		goto err;
	}

	sec_mem_printf("Enable the tzasc interrupt.\n", __func__, __LINE__);
	ret = SRE_HwiEnable(110);
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
	unsigned int rng_ctrl = 0;
	
	read_reg(SC_RNG_DATA_CTRL, rng_ctrl);

    if ((0x01 == (rng_ctrl & 0x03)) || (0x0 == (rng_ctrl & 0x03)))
    {
        rng_ctrl &= 0xfffffffc;
        rng_ctrl |= 0x03;
		write_reg(SC_RNG_DATA_CTRL, rng_ctrl);
        asm("nop");
    }
	
	for (i = 0; i < 0x10000; i++) {
		asm("nop");
		asm("nop");
		read_reg(SC_RNG_DATA_CNT, rng_stat);
		if((rng_stat & 0xFF) > 0) {
			read_reg(SC_RNG_DATA_VAL, rng_value);
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
	write_reg(SC_SYSRES_REG, 0x12345678);
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
	unsigned int virt_addr = (unsigned int)&rand_num;
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

	/* double check DDR whether roolback */
	if (ddr_rollback_check()) {
		uart_printf_func("[%s][%d]DDR may be rollback. Check again\n", __func__, __LINE__);
		if (ddr_rollback_check()) {
			uart_printf_func("[%s][%d]DDR rollback, reset now\n", __func__, __LINE__);
			sec_sys_reset();
		}
	}

	random_delay();
	sec_mem_printf("TZASC config start...\n");
	ret = config_ddr_zone();
	if (ret < 0) {
		sec_mem_printf("Fail to config ddr zones!!\n");
		return -1;
	}

	random_delay();
	sec_mem_printf("TZPC config start...\n");
	ret = config_module_attr();
	if (ret < 0) {
		sec_mem_printf("Fail to config module attributes!!\n");
		return -1;
	}

#if 0 /* only for debug */
	sec_mem_printf("Register TZASC interrupt...\n");
	ret = register_interrupt();
	if (ret < 0)
		return -1;
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

