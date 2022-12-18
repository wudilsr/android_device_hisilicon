#include "sre_debug.h"
#include "secure_mem_cfg.h"
#include "sre_hwi.h"

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

static int size2regvalue(unsigned long long size)
{
	unsigned int size_field = 0;

	for (size_field = 0; (unsigned long long)(1ULL << size_field) < MAX_DDR_LEN; size_field++) {
		if (size == (unsigned long long)(1ULL << size_field)) {
			break;
		}
	}

	if (MAX_DDR_LEN == (unsigned long long)(1ULL << size_field)) {
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

	lockdown_range.u32 = 0;
	read_reg(port_base + SEC_LOCKDOWN_RANGE_REG, lockdown_range.u32);
	lockdown_range.bits.lockdown_regions = 0xF;//(1 << sizeof(lockdown_range.bits.lockdown_regions)) - 1;//0x7;
	sec_mem_printf("----lockdown_range.bits.lockdown_regions=%d\n", lockdown_range.bits.lockdown_regions);
	lockdown_range.bits.lockdown_enable = 1;
	write_reg(port_base + SEC_LOCKDOWN_RANGE_REG, lockdown_range.u32);

	lockdownsel.u32 = 0;
	read_reg(port_base + SEC_LOCKDOWN_SEL_REG, lockdownsel.u32);
	lockdownsel.bits.region_register = 1;
	lockdownsel.bits.security_inv = 1;
	lockdownsel.bits.security_bypass = 1;
	lockdownsel.bits.master_type = 1;
	write_reg(port_base + SEC_LOCKDOWN_SEL_REG, lockdownsel.u32);
}

static unsigned int get_nr_regions(unsigned int port_base)
{
	union tzasc_sec_cfg_reg sec_cfg;

	read_reg(port_base + SEC_CONFIG_REG, sec_cfg.u32);
	sec_mem_printf("nr_of_regions = %d\n", sec_cfg.bits.nr_of_regions);
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

		size = size2regvalue(region[i].size);
		attr.u32 = 0;
		read_reg((port_base + SET_REGION_ATTRIBUTES(i)), attr.u32);
		attr.bits.en = region[i].en;
		attr.bits.size = size;
		attr.bits.sp = region[i].sp;
		attr.bits.subregion_disable = 0;
		write_reg((port_base + SET_REGION_ATTRIBUTES(i)), attr.u32);
		//sec_mem_dbginfo("config region %d: en=%d, base=0x%x, size=0x%x, sp=0x%x\n",
		//	i, region[i].en, region[i].base, region[i].size, region[i].sp);
	}

	/*Set bypass */
	bypass.u32 = 0;
	read_reg((port_base + SEC_BYPASS_REG), bypass.u32);
	bypass.bits.bypass = 0;
	write_reg((port_base + SEC_BYPASS_REG), bypass.u32);

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
			sec_mem_dbginfo("TZASC%d configure failed!\n", i);
			return ret;
		}
		sec_mem_dbginfo("TZASC%d configure success!\n", i);
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

int sys_security_config(void)
{
	int ret = 0;
	ret = config_ddr_zone();
	if (ret < 0) {
		sec_mem_printf("Fail to config ddr zones!!\n");
		return -1;
	}

	ret = config_module_attr();
	if (ret < 0) {
		sec_mem_printf("Fail to config module attributes!!\n");
		return -1;
	}

	ret = register_interrupt();
	if (ret < 0)
		return -1;

	return 0;
}

