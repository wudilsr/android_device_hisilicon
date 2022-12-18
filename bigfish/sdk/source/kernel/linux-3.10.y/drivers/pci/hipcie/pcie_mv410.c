
#include "pcie_mv410.h"

#if (defined(CONFIG_S40_FPGA))
#include "drv_i2c.c"
#include "hi_drv_i2c.h"
#define PCIE_I2C_PORT	0
#define PCIE_PHY_ADDR	0x7c
#define PCIE_RST_ADDR	0x78
#endif

struct pcie_iatu pcie0_iatu_table[] = {
		{
			.viewport	= 0,
			.region_ctrl_1  = 0x00000004,
			.region_ctrl_2  = 0x80000000,
			.lbar           = 0xD0100000,//0xF0100000,
			.ubar           = 0x0,
			.lar            = 0xD01FFFFF,//0xF01FFFFF,
			.ltar           = 0x01000000,
			.utar           = 0x00000000,
		},
		{
			.viewport       = 1,
			.region_ctrl_1  = 0x00000000, //5,
			.region_ctrl_2  = 0x80000000,
			.lbar           = 0xC0000000,//0xF0000000,
			.ubar           = 0x0,
			.lar            = 0xC77FFFFF,//0x0000FFFF,//0xF77FFFFF,
			//PCIe Loopback Mode Should set  .ltar to DDR address,example:0x02000000
		#if defined (PCIE_LOCAL_LOOPBACK_EN) ||defined (PCIE_REMOTE_LOOPBACK_EN)
			.ltar		   =0x02000000,
		#else
			.ltar           = 0xC0000000,
		#endif
			.utar           = 0x00000000,
		},
		{
			.viewport       = 2,
			.region_ctrl_1  = 0x00000002,
			.region_ctrl_2  = 0x80000000,
			.lbar           = 0xC7800000,//0xF0000000 + 0x7800000,
			.ubar           = 0x0,
			.lar            = 0xC8000000 - 1,//0xF8000000 - 1,
			.ltar           = 0xC7800000,
			.utar           = 0x00000000,
		},
};

void config_controller_iatu_table(int controller, struct pci_sys_data *sys)
{
	int i;
	void *dbi_base = NULL;
	struct pcie_iatu *p_table;
	unsigned int val;

	int table_size = 0;

#ifdef CONFIG_PCIE0_SEL
	if (controller == pcie_controller_0) {
		dbi_base = ioremap_nocache(DBI_BASE_ADDR_0, 0x1000);
		if (!dbi_base) {
			pcie_error("Cannot map dbi base for pcie0");
			return;
		}

		p_table = pcie0_iatu_table;
		table_size = ARRAY_SIZE(pcie0_iatu_table);

	}
#endif

#ifdef CONFIG_PCIE1_SEL
	if (controller == pcie_controller_1) {
		int ctl1_lbar_offset = 0;
		int controller_bus = sys->busnr;

		dbi_base = ioremap_nocache(DBI_BASE_ADDR_1, 0x1000);
		if (!dbi_base) {
			pcie_error("Cannot map dbi base for pcie0");
			return;
		}

		p_table = pcie1_iatu_table;
		table_size = ARRAY_SIZE(pcie1_iatu_table);

		ctl1_lbar_offset = (controller_bus + 1) << 20;

		p_table->lbar |= ctl1_lbar_offset;
		p_table->lar |= ctl1_lbar_offset;

		ctl1_lbar_offset = (controller_bus + 2) << 20;
		(p_table + 1)->lbar |= ctl1_lbar_offset;

	}
#endif
	if ((controller != pcie_controller_0)
			&& (controller != pcie_controller_1)) {
		pcie_error("Invalid pcie controller number!");
		return;
	}

	if (NULL == dbi_base) {
		pcie_error("PCIe db_base is NULL!");
		return;
	}
	
	/* select for reg */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL0);
	val |= (1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL0);
	
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL1);
	val |= (1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL1);

	for (i = 0; i < table_size; i++) {
		writel((p_table + i)->viewport, dbi_base + 0x700 + 0x200);
		writel((p_table + i)->lbar, dbi_base + 0x700 + 0x20c);
		writel((p_table + i)->ubar, dbi_base + 0x700 + 0x210);
		writel((p_table + i)->lar, dbi_base + 0x700 + 0x214);
		writel((p_table + i)->ltar, dbi_base + 0x700 + 0x218);
		writel((p_table + i)->utar, dbi_base + 0x700 + 0x21c);
		writel((p_table + i)->region_ctrl_1,
				dbi_base + 0x700 + 0x204);
		writel((p_table + i)->region_ctrl_2,
				dbi_base + 0x700 + 0x208);
	}

	udelay(1000);
	iounmap(dbi_base);
	dbi_base = NULL;
	
	/* select for mem */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL0);
	val &= ~(1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL0);
	
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL1);
	val &= ~(1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL1);
}

static inline int pcie_check_link_status(struct pcie_info *info)
{
	int val;

	udelay(2000);
	val = readl(pcie_sys_base_virt + PCIE_SYS_STAT0);
	return ((val & (1 << PCIE_XMLH_LINK_UP))
			&& (val & (1 << PCIE_RDLH_LINK_UP))) ? 1 : 0;
}


static void pcie_phy_init(void)
{
	int val;
	volatile void __iomem *peri_ctrl = (void __iomem*)IO_ADDRESS(0xf8a20008);
	void __iomem *crg_base = (void __iomem *)ioremap_nocache(PERI_CRG_BASE, 0x1000);
#if 0
#ifdef CONFIG_S40_FPGA
//FPGA Inno PHY
	int timeout = 0;
	unsigned char data[2];
	unsigned char rdata[2];
	//release por_n
	val = readl(crg_base + PERI_CRG98);
	val &= ~(1 << 5);
	writel(val, crg_base + PERI_CRG98);
	//PHY reset from CRG
	val = readl(crg_base + PERI_CRG99);
	val |= 1 << 8;
	writel(val, crg_base + PERI_CRG99);
	
	HI_DRV_I2C_Init();

	/*According to Inno:pipe_rate = 2'b11£¬pipe_databuswidth = 2'b00*/
	val = readl(__io_address(0xf8a20050));
	val |= (0x1 << 8);
	writel(val, __io_address(0xf8a20050));
	
	val = readl(__io_address(0xf8a20054));
	val |= (0x1 << 30);
	writel(val, __io_address(0xf8a20054));

	val = readl(__io_address(0xf8a20054));
	val &= ~(0x3 << 28);
	writel(val, __io_address(0xf8a20054));
	//rx_data 
	val = readl(__io_address(0xf8a20050));
	val |= (0x1 << 6);
	val &=~(0x1<<5);
	val &=~ (0x1<<4);
	writel(val, __io_address(0xf8a20050));
	
	val = readl(__io_address(0xf8a20050));
	printk("===0xf8a20050 = %#x.\n", val);
	val = readl(__io_address(0xf8a20054));
	printk("===0xf8a20054 = %#x.\n", val);

	/*Wifi Reset*/
	val = readl(__io_address(0xf8a20054));
	val |= (0x1 << 17);
	writel(val, __io_address(0xf8a20054));
	
	val = readl(__io_address(0xf8a20054));
	printk("===0xf8a20054 = %#x.\n", val);
	/*Step1:por_n*/
	//reset por_n	
	val = readl(crg_base + PERI_CRG98);
	val |= (1 << 5);
	writel(val, crg_base + PERI_CRG98);
	//release por_n
	val = readl(crg_base + PERI_CRG98);
	val &= ~(1 << 5);
	writel(val, crg_base + PERI_CRG98);
	/* step3: configuring pcie phy register */
	data[0] = 0x32;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x47, 1, data, 1);
	data[0] = 0x10;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x48, 1, data, 1);
	data[0] = 0x32;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x0a, 1, data, 1);
	data[0] = 0x19;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x3d, 1, data, 1);

	HI_DRV_I2C_Read(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x3d, 1, rdata, 1);
	printk("addr:%#x, write %#x, read %#x.\n", 0x3d, data[0], rdata[0]);

	/* step4: PCIe Gen1 */
	data[0] = 0x02;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x08, 1, data, 1);
	data[0] = 0x02;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x0c, 1, data, 1);

	HI_DRV_I2C_Read(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x0c, 1, rdata, 1);
	printk("addr:%#x, write %#x, read %#x.\n", 0x0c, data[0], rdata[0]);

	/* step5: analog TX */
	data[0] = 0x0f;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x22, 1, data, 1);
	data[0] = 0x0f;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x26, 1, data, 1);
	data[0] = 0xfc;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x27, 1, data, 1);
	data[0] = 0x00;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x28, 1, data, 1);

	HI_DRV_I2C_Read(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x28, 1, rdata, 1);
	printk("addr:%#x, write %#x, read %#x.\n", 0x28, data[0], rdata[0]);

	/* step6: analog RX */
	data[0] = 0x1b;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x39, 1, data, 1);
	data[0] = 0x24;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x36, 1, data, 1);
	data[0] = 0x2c;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x16, 1, data, 1);
	data[0] = 0x1f;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x17, 1, data, 1);
	data[0] = 0x00;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x18, 1, data, 1);
	data[0] = 0x3f;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x19, 1, data, 1);

	HI_DRV_I2C_Read(PCIE_I2C_PORT, PCIE_PHY_ADDR, 0x19, 1, rdata, 1);
	printk("addr:%#x, write %#x, read %#x.\n", 0x19, data[0], rdata[0]);

	/* step7: soft reset PHY */
	data[0] = 0xc7;
	HI_DRV_I2C_Write(PCIE_I2C_PORT, PCIE_RST_ADDR, 0x00, 1, data, 1);

	HI_DRV_I2C_Read(PCIE_I2C_PORT, PCIE_RST_ADDR, 0x00, 1, rdata, 1);
	printk("addr:%#x, write %#x, read %#x.\n", 0x00, data[0], rdata[0]);

	//PHY reset from PCIe Controller
	val = readl(crg_base + PERI_CRG99);
	val &= ~(1 << 8);
	writel(val, crg_base + PERI_CRG99);

	do {
		val = readl(__io_address(0xf9860110));
		val &= (1<<28);
		msleep(20);
		timeout++;
	} while (val && (timeout < 20));

	printk("bit28 = %d.\n", !!val);

	HI_DRV_I2C_DeInit();
#else
	//Asic Nano PHY
	/*PCIe PWREN PIN MUX*/
	writel(0x1, (void __iomem *)IO_ADDRESS(0xF8A21038));
	msleep(10);
		
	/* Power on PWREN */
	val = readl(peri_ctrl);
	val |= 1<<10;
	writel(val, peri_ctrl);
	msleep(10);

	/*Config Nano ComboPHY to PCIe mode*/
	val = readl(peri_ctrl);
	val &= ~(1<<11);
	val&= ~(1<<12);
	writel(val, peri_ctrl);
	msleep(10);

	/*Config ComboPHY IP don't isolate*/
	val = readl(peri_ctrl);
	val &= ~(1<<25);
	writel(val, peri_ctrl);
	msleep(10);
		
	/*Config Nano ComboPHY clock and reset ComboPHY*/
	writel(0x33, crg_base + PERI_CRG98);
	msleep(10);
	writel(0x3, crg_base + PERI_CRG98);
	msleep(10);

	/*Output EP clock*/
	val = readl((void __iomem *)IO_ADDRESS(0xF8A20858));
	val &= ~(1<<0);
	writel(val, (void __iomem *)IO_ADDRESS(0xF8A20858));
	msleep(10);
	iounmap(crg_base);
#endif
#endif
}
EXPORT_SYMBOL(pcie_phy_init);
static int pcie_sys_init(unsigned int mode_sel)
{
	unsigned int val;

	void *crg_base = (void *)ioremap_nocache(PERI_CRG_BASE, 0x1000);
	if (!crg_base)
		return -EIO;
	pcie_phy_init();
	/* select for reg */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL0);
	val |= (1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL0);

	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL1);
	val |= (1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL1);

	/*
	 * Disable PCIE
	 */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL7);
	val &= (~(1 << PCIE0_APP_LTSSM_ENBALE));
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL7);

	/*
	 * Enable clk
	 */
	val = readl(crg_base + PERI_CRG99);
	val |= ((1 << PCIE_BUS_CKEN) | (1 << PCIE_PIPE_CKEN)
			| (1 << PCIE_AUX_CKEN)|(PCIE_SYS_CKEN));
	writel(val, crg_base + PERI_CRG99);
	
	/*
	 * PCIE RC work mode
	 */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL0);
	val &= (~(0xf << PCIE_DEVICE_TYPE));
	val |= (PCIE_WM_RC << PCIE_DEVICE_TYPE);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL0);

	/*
	 * Reset
	 */
	val = readl(crg_base + PERI_CRG99);
	val |= (1 << PCIE_BUS_SRST_REQ);
	writel(val, crg_base + PERI_CRG99);
	

	/*
	 * Retreat from the reset state
	 */
	udelay(500);
	val = readl(crg_base + PERI_CRG99);
	val &= ~(1 << PCIE_BUS_SRST_REQ);
	writel(val, crg_base + PERI_CRG99);

	if ((mode_sel & PCIE0_MODE_SEL) == PCIE0_MODE_SEL) {
		void *dbi_base = ioremap_nocache(DBI_BASE_ADDR_0, 0x1000);
		if (!dbi_base) {
			pcie_error("Cannot map dbi base for pcie0");
			return -EIO;
		}
	
#ifdef PCIE_LOCAL_LOOPBACK_EN
		/* set to  local lookback */
		val = readl(dbi_base + 0x8b8);
		val |= (1<<31);
		writel(val, dbi_base + 0x8b8);
		val = readl(dbi_base + 0x710);
		val |= (1<<2);
		writel(val, dbi_base + 0x710);
#endif

#ifdef PCIE_REMOTE_LOOPBACK_EN
		/* set to  remote lookback */
		val = readl(dbi_base + 0x710);
		val |= (1<<2);
		writel(val, dbi_base + 0x710);
#endif
		/*
		 * Set PCIE controller class code to be PCI-PCI bridge device
		 */
		val = readl(dbi_base + 0x8);
		val &= ~(0xffffff00);
		val |= (0x60400<<8);
		writel(val, dbi_base + 0x8);

		udelay(1000);
		iounmap(dbi_base);
		dbi_base = NULL;
	}

	/*
	 * Enable PCIE
	 */
	if (mode_sel & PCIE0_MODE_SEL) {
		val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL7);
		val |= (1 << PCIE0_APP_LTSSM_ENBALE);
		writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL7);
	}
	msleep(100);
/*	if((readl(pcie_sys_base_virt + PCIE_SYS_STAT0)&(1 << PCIE_XMLH_LINK_UP))
		&&readl(pcie_sys_base_virt + PCIE_SYS_STAT0)&(1 << PCIE_RDLH_LINK_UP))
		printk("PCI Express Link up\n");
	else
		printk("PCI Express Link down\n");*/
	udelay(1000);
	{
		void *dbi_base  = 0;
		unsigned int val;
		if (mode_sel & PCIE0_MODE_SEL) {
			dbi_base = ioremap_nocache(DBI_BASE_ADDR_0, 0x1000);
			if (!dbi_base)
				return -EIO;

			val = readl(dbi_base + 0x4);
			val |= 7;
			writel(val, dbi_base + 0x4);

			iounmap(dbi_base);
		}
	}

	/* select for mem */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL0);
	val &= ~(1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL0);

	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL1);
	val &= ~(1 << PCIE_BIT_REG_DEV_CTRL);
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL1);
	iounmap(crg_base);
	return 0;
}
EXPORT_SYMBOL(pcie_sys_init);

#ifdef CONFIG_PM
int hisi_pcie_plat_driver_suspend(struct platform_device *dev, pm_message_t state)
{
	void *crg_base = (void *)IO_ADDRESS(REG_BASE_CRG);
	unsigned int val;

	/*
	 * Disable PCIE
	 */
	val = readl(pcie_sys_base_virt + PCIE_SYS_CTRL7);
	val &= (~(1 << PCIE0_APP_LTSSM_ENBALE));
	writel(val, pcie_sys_base_virt + PCIE_SYS_CTRL7);

	/*
	 * Reset
	 */
	val = readl(crg_base + PERI_CRG99);
	val |= (1 << PCIE_BUS_SRST_REQ);
	writel(val, crg_base + PERI_CRG99);

	udelay(1000);

	/*
	 * Disable clk
	 */
	val = readl(crg_base + PERI_CRG99);
	val &= (~(1 << PCIE_BUS_CKEN));
	val &= (~(1 << PCIE_SYS_CKEN));
	val &= (~(1 << PCIE_PIPE_CKEN));
	val &= (~(1 << PCIE_AUX_CKEN));
	writel(val, crg_base + PERI_CRG99);

	udelay(1000);
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


