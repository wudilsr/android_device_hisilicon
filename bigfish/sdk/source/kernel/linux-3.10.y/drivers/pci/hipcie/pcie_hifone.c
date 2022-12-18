
#include "pcie_hifone.h"

struct pcie_iatu pcie0_iatu_table[] = {
		{
			.viewport	= 0,
			.region_ctrl_1  = 0x00000004,
			.region_ctrl_2  = 0x80000000,
			.lbar           = PCIE0_MEMIO_BASE+0x100000,//0xE4100000
			.ubar           = 0x0,
			.lar            = PCIE0_MEMIO_BASE+0x100000+0xFFFFF,//0xE41FFFFF
			.ltar           = 0x01000000,
			.utar           = 0x00000000,
		},
		{
			.viewport       = 1,
			.region_ctrl_1  = 0x00000000, 
			.region_ctrl_2  = 0x80000000,
			.lbar           = PCIE0_BASE_ADDR_PHYS,//0xE0000000
			.ubar           = 0x0,
			.lar            = PCIE0_BASE_ADDR_PHYS+PCIE_BASE_ADDR_SIZE/2-0x1,//0xE1FFFFFF
			//PCIe Loopback Mode Should set  .ltar to DDR address,example:0x02000000
		#if defined (PCIE0_LOCAL_LOOPBACK_EN) ||defined (PCIE0_REMOTE_LOOPBACK_EN)
			.ltar		   =0x02000000,
		#else
			.ltar           = PCIE0_BASE_ADDR_PHYS,
		#endif
			.utar           = 0x00000000,
		},
		{
			.viewport       = 2,
			.region_ctrl_1  = 0x00000002,
			.region_ctrl_2  = 0x80000000,
			.lbar           = PCIE0_BASE_ADDR_PHYS+PCIE_BASE_ADDR_SIZE/2,//0xE2000000
			.ubar           = 0x0,
			.lar            = PCIE0_MEMIO_BASE - 1,//0xE3FFFFFF
			.ltar           = PCIE0_BASE_ADDR_PHYS+PCIE_BASE_ADDR_SIZE/2,//0xE2000000
			.utar           = 0x00000000,
		},
};

struct pcie_iatu pcie1_iatu_table[] = {
		{
			.viewport	= 0,
			.region_ctrl_1  = 0x00000004,
			.region_ctrl_2  = 0x80000000,
			.lbar           = PCIE1_MEMIO_BASE+0x300000,//0xEC100000
			.ubar           = 0x0,
			.lar            = PCIE1_MEMIO_BASE+0x300000+0xFFFFF,//0xEC1FFFFF
			.ltar           = 0x01000000,
			.utar           = 0x00000000,
		},
		{
			.viewport       = 1,
			.region_ctrl_1  = 0x00000000, 
			.region_ctrl_2  = 0x80000000,
			.lbar           = PCIE1_BASE_ADDR_PHYS,//0xE8000000
			.ubar           = 0x0,
			.lar            = PCIE1_BASE_ADDR_PHYS+0x1FFFFFF,//0xE9FFFFFF
			//PCIe Loopback Mode Should set  .ltar to DDR address,example:0x02000000
		#if defined (PCIE1_LOCAL_LOOPBACK_EN) ||defined (PCIE1_REMOTE_LOOPBACK_EN)
			.ltar		   =0x02000000,
		#else
			.ltar           = PCIE1_BASE_ADDR_PHYS,
		#endif
			.utar           = 0x00000000,
		},
		{
			.viewport       = 2,
			.region_ctrl_1  = 0x00000002,
			.region_ctrl_2  = 0x80000000,
			.lbar           =PCIE1_BASE_ADDR_PHYS+PCIE_BASE_ADDR_SIZE/2,//0xEA000000
			.ubar           = 0x0,
			.lar            = PCIE1_MEMIO_BASE - 1,//0xEBFFFFFF
			.ltar           = PCIE1_BASE_ADDR_PHYS+PCIE_BASE_ADDR_SIZE/2,//0xEA000000
			.utar           = 0x00000000,
		},
};

void config_controller_iatu_table(int controller, struct pci_sys_data *sys)
{
	int i;
	void *dbi_base_0 = NULL;
	void *dbi_base_1 =NULL;
	struct pcie_iatu *p_table;
	unsigned int val;

	int table_size = 0;

#ifdef CONFIG_PCIE0_SEL
	if (controller == pcie_controller_0) {
		dbi_base_0 = ioremap_nocache(DBI_BASE_ADDR_0, 0x1000);
		if (!dbi_base_0) {
			pcie_error("Cannot map dbi base for pcie0");
			return;
		}

		p_table = pcie0_iatu_table;
		table_size = ARRAY_SIZE(pcie0_iatu_table);

	}
#endif

#ifdef CONFIG_PCIE1_SEL
	if (controller == pcie_controller_1) {
		//int ctl1_lbar_offset = 0;
		//int controller_bus = sys->busnr;

		dbi_base_1 = ioremap_nocache(DBI_BASE_ADDR_1, 0x1000);
		if (!dbi_base_1) {
			pcie_error("Cannot map dbi base for pcie0");
			return;
		}

		p_table = pcie1_iatu_table;
		table_size = ARRAY_SIZE(pcie1_iatu_table);
/*
		ctl1_lbar_offset = (controller_bus + 1) << 20;

		p_table->lbar |= ctl1_lbar_offset;
		p_table->lar |= ctl1_lbar_offset;

		ctl1_lbar_offset = (controller_bus + 2) << 20;
		(p_table + 1)->lbar |= ctl1_lbar_offset;
*/
	}
#endif
	if ((controller != pcie_controller_0)
			&& (controller != pcie_controller_1)) {
		pcie_error("Invalid pcie controller number!");
		return;
	}

	if ((NULL == dbi_base_0)&&(controller == pcie_controller_0)) {
		pcie_error("PCIe db_base_0 is NULL!");
		return;
	}
#ifdef CONFIG_PCIE1_SEL
	if ((NULL == dbi_base_1)&&(controller == pcie_controller_1)) {
		pcie_error("PCIe db_base_1 is NULL!");
		return;
	}
#endif
	if(controller == pcie_controller_0){
		//select PCIe0 for reg
		val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL0);
		val |= (1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL0);
		
		val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL1);
		val |= (1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL1);

		for (i = 0; i < table_size; i++) {
			writel((p_table + i)->viewport, dbi_base_0 + 0x700 + 0x200);
			writel((p_table + i)->lbar, dbi_base_0 + 0x700 + 0x20c);
			writel((p_table + i)->ubar, dbi_base_0 + 0x700 + 0x210);
			writel((p_table + i)->lar, dbi_base_0 + 0x700 + 0x214);
			writel((p_table + i)->ltar, dbi_base_0 + 0x700 + 0x218);
			writel((p_table + i)->utar, dbi_base_0 + 0x700 + 0x21c);
			writel((p_table + i)->region_ctrl_1,
					dbi_base_0 + 0x700 + 0x204);
			writel((p_table + i)->region_ctrl_2,
					dbi_base_0 + 0x700 + 0x208);
		}

		udelay(1000);
		iounmap(dbi_base_0);
		dbi_base_0 = NULL;
		
		//select PCIe0 for mem
		val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL0);
		val &= ~(1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL0);
		
		val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL1);
		val &= ~(1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL1);
	}
#ifdef CONFIG_PCIE1_SEL
	if(controller == pcie_controller_1){
		//select PCIe1 for reg
		val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL0);
		val |= (1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL0);
		
		val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL1);
		val |= (1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL1);

		for (i = 0; i < table_size; i++) {
			writel((p_table + i)->viewport, dbi_base_1 + 0x700 + 0x200);
			writel((p_table + i)->lbar, dbi_base_1 + 0x700 + 0x20c);
			writel((p_table + i)->ubar, dbi_base_1 + 0x700 + 0x210);
			writel((p_table + i)->lar, dbi_base_1 + 0x700 + 0x214);
			writel((p_table + i)->ltar, dbi_base_1 + 0x700 + 0x218);
			writel((p_table + i)->utar, dbi_base_1 + 0x700 + 0x21c);
			writel((p_table + i)->region_ctrl_1,
					dbi_base_1 + 0x700 + 0x204);
			writel((p_table + i)->region_ctrl_2,
					dbi_base_1 + 0x700 + 0x208);
		}

		udelay(1000);
		iounmap(dbi_base_1);
		dbi_base_1 = NULL;
		
		//select PCIe1 for mem
		val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL0);
		val &= ~(1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL0);
		
		val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL1);
		val &= ~(1 << pcie_bit_reg_dev_ctrl);
		writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL1);
	}
#endif
}

static inline int pcie_check_link_status(struct pcie_info *info)
{
	int val;
	udelay(2000);
	if(info->controller==pcie_controller_0)
		val = readl(pcie0_sys_base_virt + PCIE_SYS_STAT0);
	if(info->controller==pcie_controller_1)
		val = readl(pcie1_sys_base_virt + PCIE_SYS_STAT0);
	return ((val & (1 << pcie0_xmlh_link_up))
			&& (val & (1 << pcie0_rdlh_link_up))) ? 1 : 0;
}
static void nano_register_write(u32 nano_testwrite_addr,u32 nano_testwrite_value,u32 comboPHY_num)
{
	unsigned int tmp_val;
	void __iomem *PERI_COMBOPHY_CFG_ADDR, *PERI_COMBOPHY_STATE_ADDR;
	if(1==comboPHY_num)
	{
		PERI_COMBOPHY_CFG_ADDR=PERI_COMBPHY1_CFG;
		PERI_COMBOPHY_STATE_ADDR=PERI_COMBPHY1_STATE;
	}
	if(3==comboPHY_num)
	{
		PERI_COMBOPHY_CFG_ADDR=PERI_COMBPHY3_CFG;
		PERI_COMBOPHY_STATE_ADDR=PERI_COMBPHY3_STATE;
	}
	tmp_val=readl(PERI_COMBOPHY_CFG_ADDR);
	msleep(10);
	tmp_val &=~(nano_test_addr);
	tmp_val &=~(nano_test_data);
	tmp_val |=(nano_testwrite_addr<<12);
	tmp_val |=(nano_testwrite_value<<20);
	writel(tmp_val,PERI_COMBOPHY_CFG_ADDR);
	msleep(10);

	tmp_val=readl(PERI_COMBOPHY_CFG_ADDR);
	tmp_val |=nano_test_write;
	writel(tmp_val,PERI_COMBOPHY_CFG_ADDR);
	msleep(10);
//	printk("Nano ComboPHY(%s):addr(%#x),value(%#x)\n",__FUNCTION__,nano_testwrite_addr,nano_testwrite_value);
	tmp_val=readl(PERI_COMBOPHY_CFG_ADDR);
	tmp_val &=~(nano_test_write);
	writel(tmp_val,PERI_COMBOPHY_CFG_ADDR);
	msleep(10);
}
static void nano_tx_margin_pcie(int margin_value,int comboPHY_num)
{
	int tmp_val;
	void __iomem *PERI_COMBOPHY_CFG_ADDR, *PERI_COMBOPHY_STATE_ADDR;
	if(1==comboPHY_num)
	{
		PERI_COMBOPHY_CFG_ADDR=PERI_COMBPHY1_CFG;
		PERI_COMBOPHY_STATE_ADDR=PERI_COMBPHY1_STATE;
	}
	if(3==comboPHY_num)
	{
		PERI_COMBOPHY_CFG_ADDR=PERI_COMBPHY3_CFG;
		PERI_COMBOPHY_STATE_ADDR=PERI_COMBPHY3_STATE;
	}
	tmp_val = readl(PERI_COMBOPHY_CFG_ADDR);
	tmp_val |=bypass_pciectrl_analog;
	writel(tmp_val, PERI_COMBOPHY_CFG_ADDR);
	msleep(10);
	
	tmp_val = readl(PERI_COMBOPHY_CFG_ADDR);
	tmp_val &=~(nano_tx_margin);
	tmp_val |=margin_value<<8;
	writel(tmp_val, PERI_COMBOPHY_CFG_ADDR);
	msleep(10);
}

static void nano_tx_deemp_pcie(int deemp_value,int comboPHY_num)
{
	int tmp_val;
	void __iomem *PERI_COMBOPHY_CFG_ADDR, *PERI_COMBOPHY_STATE_ADDR;
	if(1==comboPHY_num)
	{
		PERI_COMBOPHY_CFG_ADDR=PERI_COMBPHY1_CFG;
		PERI_COMBOPHY_STATE_ADDR=PERI_COMBPHY1_STATE;
	}
	if(3==comboPHY_num)
	{
		PERI_COMBOPHY_CFG_ADDR=PERI_COMBPHY3_CFG;
		PERI_COMBOPHY_STATE_ADDR=PERI_COMBPHY3_STATE;
	}
	tmp_val = readl(PERI_COMBOPHY_CFG_ADDR);
	tmp_val |=bypass_pciectrl_analog;
	writel(tmp_val, PERI_COMBOPHY_CFG_ADDR);
	msleep(10);

	tmp_val = readl(PERI_COMBOPHY_CFG_ADDR);
	tmp_val &=~(nano_tx_deemp);
	tmp_val |=deemp_value<<5;
	writel(tmp_val, PERI_COMBOPHY_CFG_ADDR);
	msleep(10);
}
static void pcie_phy_init(void)
{
	int tmp_val;
#ifdef CONFIG_S40_FPGA
	//no FPGA Test
#else
	//Asic Nano PHY
	//Config Nano ComboPHY1 to PCIe mode
	tmp_val = readl(PERI_CTRL);
	tmp_val &= ~pcie_usb3_sata3_sel_combphy1;
	writel(tmp_val, PERI_CTRL);
	msleep(10);
	
	//Config Nano ComboPHY1 enable 8B10B
	tmp_val = readl(PERI_COMBPHY1_CFG);
	tmp_val &=~nano_bypass_codec;
	writel(tmp_val, PERI_COMBPHY1_CFG);
	msleep(10);
	
	//reset Nano ComboPHY1
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val|combphy1_srst_req, CRG_BASE+PERI_CRG98);
	msleep(10);

	//close Nano ComboPHY1 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy1_ref_cken;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//Config Nano ComboPHY1 refclk
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy1_refclk_sel;
	tmp_val |=0x0<<9;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//open Nano ComboPHY1 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val |=combphy1_ref_cken;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//release reset Nano ComboPHY1
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val&(~combphy1_srst_req), CRG_BASE+PERI_CRG98);
	msleep(10);
	//SSC off
	nano_register_write(0x2, 0x8, 0x1);
	//TX_MARGIN 1100mV
	nano_tx_margin_pcie(0x1,0x1);
	//TX_DEEMP -3.5dB
	nano_tx_deemp_pcie(0x1,0x1);
	//TX_SWING_COMP
//	nano_register_write(0xb, 0x0, 0x1);
	//DOUBLE_PI_CURRETN&DOUBLE_PI_CMP_CURRENT
	nano_register_write(0xd,0xe,0x1);
//	nano_register_write(0xa,0x1,0x1);
	//SPLIT_CP_DIS
	nano_register_write(0xc,0x9,0x1);
#ifdef PCIe1_CONFIG
	//Config Nano ComboPHY3 to PCIe mode
	tmp_val = readl(PERI_CTRL);
	tmp_val &= ~pcie_usb3_sata3_sel_combphy3;
	writel(tmp_val, PERI_CTRL);
	msleep(10);

	//Config Nano ComboPHY2 enable 8B10B
	tmp_val = readl(PERI_COMBPHY3_CFG);
	tmp_val &=~nano_bypass_codec;
	writel(tmp_val, PERI_COMBPHY3_CFG);
	msleep(10);
	
	//reset Nano ComboPHY3
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val|combphy3_srst_req, CRG_BASE+PERI_CRG98);
	msleep(10);

	//close Nano ComboPHY3 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy3_ref_cken;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//Config Nano ComboPHY3 refclk
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy3_refclk_sel;
	tmp_val |=0x0<<17;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//open Nano ComboPHY3 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val |=combphy3_ref_cken;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);

	//release reset Nano ComboPHY3
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy3_srst_req;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
	//SSC off
	nano_register_write(0x2, 0x8, 0x3);
	//TX_MARGIN 1100mV
	nano_tx_margin_pcie(0x1,0x3);
	//TX_DEEMP -3.5dB
	nano_tx_deemp_pcie(0x1,0x3);
	//TX_SWING_COMP
//	nano_register_write(0xb, 0x0, 0x3);
	//DOUBLE_PI_CURRETN&DOUBLE_PI_CMP_CURRENT
	nano_register_write(0xd,0xe,0x3);	
//	nano_register_write(0xa,0x1,0x3);	
	//SPLIT_CP_DIS
	nano_register_write(0xc,0x9,0x3);
#endif

#endif
}
static void pcie_phy_deinit(void)
{
	int tmp_val;
#ifdef CONFIG_S40_FPGA
	//no FPGA Test
#else
	//reset Nano ComboPHY1
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val|combphy1_srst_req, CRG_BASE+PERI_CRG98);
	msleep(10);

	//close Nano ComboPHY1 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy1_ref_cken;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
	
	//Config Nano ComboPHY1 refclk
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy1_refclk_sel;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
#ifdef PCIe1_CONFIG
	//reset Nano ComboPHY3
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	writel(tmp_val|combphy3_srst_req, CRG_BASE+PERI_CRG98);
	msleep(10);

	//close Nano ComboPHY3 cken
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy3_ref_cken;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
	
	//Config Nano ComboPHY3 refclk
	tmp_val=readl(CRG_BASE+PERI_CRG98);
	tmp_val &=~combphy3_refclk_sel;
	writel(tmp_val, CRG_BASE+PERI_CRG98);
	msleep(10);
#endif

#endif
}

static int pcie_sys_init(unsigned int mode_sel)
{
	unsigned int val;
	u32 i=0;

	pcie_phy_init();
	//Output EP clock
	val = readl(PERI_COMBPHY1_CFG);
	val |= (clkref_out_oen);
	writel(val, PERI_COMBPHY1_CFG);
	msleep(10);
	//select PCIe0 for reg
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL0);
	val |= (1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL0);
	msleep(10);
	
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL1);
	val |= (1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL1);
	msleep(10);
	
	// Disable PCIe0
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL7);
	val &= (~(1 << pcie0_app_ltssm_enable));
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL7);
	msleep(10);
	
	//Open PCIe0 Controller clk
	val = readl(CRG_BASE + PERI_CRG99);
	val |= (1 << pcie0_bus_cken) 
		| (1 << pcie0_pipe_cken)
		| (1 << pcie0_aux_cken)
		| (1 << pcie0_sys_cken);
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);
	
	// PCIe0 RC work mode
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL0);
	val &= (~(0xf << pcie_slv_device_type));
	val |= (PCIE_WM_RC << pcie_slv_device_type);
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL0);
	msleep(10);
	
	//Reset PCIe0 Controller
	val = readl(CRG_BASE + PERI_CRG99);
	val |= (1 << pcie0_bus_srst_req)
		|(1<<pcie0_sys_srst_req)
		|(1<<pcie0_srst_req);
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);

	// PCIe0 Retreat from the reset state
	val = readl(CRG_BASE + PERI_CRG99);
	val &= ~((1 << pcie0_bus_srst_req)
		|(1<<pcie0_sys_srst_req)
		|(1<<pcie0_srst_req));
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);

	if ((mode_sel & PCIE0_MODE_SEL) == PCIE0_MODE_SEL) {
		void *dbi_base_0 = ioremap_nocache(DBI_BASE_ADDR_0, 0x1000);
		if (!dbi_base_0) {
			pcie_error("Cannot map dbi base for pcie0");
			return -EIO;
		}
	
#ifdef PCIE0_LOCAL_LOOPBACK_EN
		//PCIe0 set to  local lookback
		val = readl(dbi_base_0 + 0x8b8);
		val |= (1<<31);
		writel(val, dbi_base_0 + 0x8b8);
		msleep(10);
		val = readl(dbi_base_0 + 0x710);
		val |= (1<<2);
		writel(val, dbi_base_0 + 0x710);
		msleep(10);
#endif

#ifdef PCIE0_REMOTE_LOOPBACK_EN
		//PCIe0 set to  remote lookback
		val = readl(dbi_base_0 + 0x710);
		val |= (1<<2);
		writel(val, dbi_base_0 + 0x710);
		msleep(10);
#endif

		// Set PCIe0 controller class code to be PCI-PCI bridge device
		val = readl(dbi_base_0 + 0x8);
		val &= ~(0xffffff00);
		val |= (0x60400<<8);
		writel(val, dbi_base_0 + 0x8);
		msleep(10);
		//Direct speed change
		val = readl(dbi_base_0 + 0x80c);
		val |= (1<<17);
		writel(val, dbi_base_0 + 0x80c);
		msleep(10);

		iounmap(dbi_base_0);
		dbi_base_0 = NULL;
	}
	//Enable PCIe0 
	if (mode_sel & PCIE0_MODE_SEL) {
		val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL7);
		val |= (1 << pcie0_app_ltssm_enable);
		writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL7);
//		msleep(10);
	}
//	msleep(1);
	do{
		if(((readl(pcie0_sys_base_virt + PCIE_SYS_STAT0)&(1 << pcie0_xmlh_link_up))==(1<<pcie0_xmlh_link_up))
			&& ((readl(pcie0_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_rdlh_link_up))==(1<<pcie0_rdlh_link_up))
			&& ((readl(pcie0_sys_base_virt + PCIE_SYS_STAT4)&0x3f)==0x11))
			break;
		udelay(10);
		i++;
	}while(i<1000);
	printk("PCIe0 Link up time %u*10us\n",i);
	if(((readl(pcie0_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_xmlh_link_up))==(1<<pcie0_xmlh_link_up))
			&& ((readl(pcie0_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_rdlh_link_up))==(1<<pcie0_rdlh_link_up))
			&& ((readl(pcie0_sys_base_virt + PCIE_SYS_STAT4)&0x3f)==0x11))
		printk("PCI Express0 Link up to Gen%d\n",((readl(pcie0_sys_base_virt+PCIE_SYS_STAT4)&(1<<6))==(1<<6))?2:1);
	else
		printk("PCI Express0 Link down\n");
	{
		void *dbi_base_0  = 0;
		unsigned int val;
		if (mode_sel & PCIE0_MODE_SEL) {
			dbi_base_0 = ioremap_nocache(DBI_BASE_ADDR_0, 0x1000);
			if (!dbi_base_0)
				return -EIO;

			val = readl(dbi_base_0 + 0x4);
			val |= 7;
			writel(val, dbi_base_0 + 0x4);
			msleep(10);
			iounmap(dbi_base_0);
		}
	}

	//PCIe0 select for mem 
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL0);
	val &= ~(1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL0);
	msleep(10);
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL1);
	val &= ~(1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL1);
	msleep(10);

#ifdef PCIe1_CONFIG		
	//select PCIe1 for reg
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL0);
	val |= (1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL0);
	msleep(10);
	
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL1);
	val |= (1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL1);
	msleep(10);
	
	// Disable PCIe1
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL7);
	val &= (~(1 << pcie0_app_ltssm_enable));
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL7);
	msleep(10);
	
	//Open PCIe1 Controller clk
	val = readl(CRG_BASE + PERI_CRG99);
	val |= (1 << pcie1_bus_cken) 
		| (1 << pcie1_pipe_cken)
		| (1 << pcie1_aux_cken)
		| (1 << pcie1_sys_cken);
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);
	
	// PCIe1 RC work mode
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL0);
	val &= (~(0xf << pcie_slv_device_type));
	val |= (PCIE_WM_RC << pcie_slv_device_type);
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL0);
	msleep(10);
	
	//Reset PCIe1 Controller
	val = readl(CRG_BASE + PERI_CRG99);
	val |= (1 << pcie1_bus_srst_req)
		|(1<<pcie1_sys_srst_req)
		|(1<<pcie1_srst_req);
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);

	// PCIe1 Retreat from the reset state
	val = readl(CRG_BASE + PERI_CRG99);
	val &= ~((1 << pcie1_bus_srst_req)
		|(1<<pcie1_sys_srst_req)
		|(1<<pcie1_srst_req));
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);

	if ((mode_sel & PCIE1_MODE_SEL) == PCIE1_MODE_SEL) {
		void *dbi_base_1 = ioremap_nocache(DBI_BASE_ADDR_1, 0x1000);
		if (!dbi_base_1) {
			pcie_error("Cannot map dbi base for pcie0");
			return -EIO;
		}
	
#ifdef PCIE1_LOCAL_LOOPBACK_EN
		//PCIe1 set to  local lookback
		val = readl(dbi_base_1 + 0x8b8);
		val |= (1<<31);
		writel(val, dbi_base_1 + 0x8b8);
		msleep(10);
		val = readl(dbi_base_1 + 0x710);
		val |= (1<<2);
		writel(val, dbi_base_1 + 0x710);
		msleep(10);
#endif

#ifdef PCIE1_REMOTE_LOOPBACK_EN
		//PCIe1 set to  remote lookback
		val = readl(dbi_base_1 + 0x710);
		val |= (1<<2);
		writel(val, dbi_base_1 + 0x710);
		msleep(10);
#endif

		// Set PCIe1 controller class code to be PCI-PCI bridge device
		val = readl(dbi_base_1 + 0x8);
		val &= ~(0xffffff00);
		val |= (0x60400<<8);
		writel(val, dbi_base_1 + 0x8);
		msleep(10);
		
		//Direct speed change
		val = readl(dbi_base_1 + 0x80c);
		val |= (1<<17);
		writel(val, dbi_base_1 + 0x80c);
		msleep(10);

		iounmap(dbi_base_1);
		dbi_base_1 = NULL;
	}

	//Enable PCIe1 
	if (mode_sel & PCIE1_MODE_SEL) {
		val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL7);
		val |= (1 << pcie0_app_ltssm_enable);
		writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL7);
	//	msleep(10);
	}
	i=0;
	do{
		if(((readl(pcie1_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_xmlh_link_up))==(1<<pcie0_xmlh_link_up))
			&& ((readl(pcie1_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_rdlh_link_up))==(1<<pcie0_rdlh_link_up))
			&& ((readl(pcie1_sys_base_virt + PCIE_SYS_STAT4)&0x3f)==0x11))
			break;
		udelay(10);
		i++;
	}while(i<1000);
	printk("PCIe1 Link up time %u*10us\n",i);
	if(((readl(pcie1_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_xmlh_link_up))==(1<<pcie0_xmlh_link_up))
			&& ((readl(pcie1_sys_base_virt + PCIE_SYS_STAT0) & (1 << pcie0_rdlh_link_up))==(1<<pcie0_rdlh_link_up))
			&& ((readl(pcie1_sys_base_virt + PCIE_SYS_STAT4)&0x3f)==0x11))
		printk("PCI Express1 Link up to Gen%d\n",((readl(pcie1_sys_base_virt+PCIE_SYS_STAT4)&(1<<6))==(1<<6))?2:1);
	else
		printk("PCI Express1 Link down\n");
	{
		void *dbi_base_1  = 0;
		unsigned int val;
		if (mode_sel & PCIE1_MODE_SEL) {
			dbi_base_1 = ioremap_nocache(DBI_BASE_ADDR_1, 0x1000);
			if (!dbi_base_1)
				return -EIO;

			val = readl(dbi_base_1 + 0x4);
			val |= 7;
			writel(val, dbi_base_1 + 0x4);
			msleep(10);
			iounmap(dbi_base_1);
		}
	}

	//PCIe1 select for mem 
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL0);
	val &= ~(1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL0);
	msleep(10);
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL1);
	val &= ~(1 << pcie_bit_reg_dev_ctrl);
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL1);
	msleep(10);
#endif
	return 0;
}
EXPORT_SYMBOL(pcie_sys_init);

#ifdef CONFIG_PM
int hisi_pcie_plat_driver_suspend(struct platform_device *dev, pm_message_t state)
{
	unsigned int val;

	//Diasble PCIe
	val = readl(pcie0_sys_base_virt + PCIE_SYS_CTRL7);
	val &= (~(1 << pcie0_app_ltssm_enable));
	writel(val, pcie0_sys_base_virt + PCIE_SYS_CTRL7);
	msleep(10);
	
	//reset PCIe0 Controller
	val = readl(CRG_BASE + PERI_CRG99);
	val |= (1 << pcie0_bus_srst_req)
		|(1<<pcie0_sys_srst_req)
		|(1<<pcie0_srst_req);
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);

	//close PCIe0 Controller clk
	val = readl(CRG_BASE + PERI_CRG99);
	val &= ~((1 << pcie0_bus_cken)
	|(1 << pcie0_sys_cken)
	|(1 << pcie0_pipe_cken)
	|(1 << pcie0_aux_cken));
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);
#ifdef PCIe1_CONFIG
	//Diasble PCIe
	val = readl(pcie1_sys_base_virt + PCIE_SYS_CTRL7);
	val &= (~(1 << pcie0_app_ltssm_enable));
	writel(val, pcie1_sys_base_virt + PCIE_SYS_CTRL7);
	msleep(10);
	
	//reset PCIe1 Controller
	val = readl(CRG_BASE + PERI_CRG99);
	val |= (1 << pcie1_bus_srst_req)
		|(1<<pcie1_sys_srst_req)
		|(1<<pcie1_srst_req);
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);

	//close PCIe1 Controller clk
	val = readl(CRG_BASE + PERI_CRG99);
	val &= ~((1 << pcie1_bus_cken)
	|(1 << pcie1_sys_cken)
	|(1 << pcie1_pipe_cken)
	|(1 << pcie1_aux_cken));
	writel(val, CRG_BASE + PERI_CRG99);
	msleep(10);
#endif
	
	//close EP clock
	val = readl(PERI_COMBPHY1_CFG);
	val &= ~(clkref_out_oen);
	writel(val, PERI_COMBPHY1_CFG);
	msleep(10);
	pcie_phy_deinit();
	
	return 0;
}

int hisi_pcie_plat_driver_resume(struct platform_device *pdev)
{
	return pcie_sys_init(hisi_pcie_mode_sel);
}

#if 0
const struct dev_pm_ops hisi_pcie_pm_ops = {
	.suspend = NULL,
	.suspend_noirq = hisi_pcie_plat_driver_suspend,
	.resume = NULL,
	.resume_noirq = hisi_pcie_plat_driver_resume
};

#define HISI_PCIE_PM_OPS (&hisi_pcie_pm_ops)
#endif
#else
#define HISI_PCIE_PM_OPS NULL
#endif


