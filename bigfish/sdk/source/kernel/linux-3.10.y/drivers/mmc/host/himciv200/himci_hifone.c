#define SDIO_REG_BASE_CRG               IO_ADDRESS(0xF8A22000)
#define SD_LDO_BASE_CRG                 IO_ADDRESS(0xF8A2011c)

/* SDIO REG */
#define PERI_CRG39               0x9C
#define PERI_CRG40               0xA0
#define PERI_CRG163              0x28C
#define REG_EMMC_PERI_CRG            PERI_CRG40
#define REG_SDCARD_PERI_CRG          PERI_CRG39
#define REG_SDIO_PERI_CRG            PERI_CRG163

#define SDIO_DRV_PS_MASK             (0x7 << 16)
#define SDIO_SAP_PS_MASK             (0x7 << 12)
#define SDIO_CLK_MASK                (0x7 << 8)

#define SDIO_CLK_MODE                (0x1 << 19)

#define SDIO_DRV_PS_0_0              (0b000 << 16)
#define SDIO_DRV_PS_45_22DOT5        (0b001 << 16)
#define SDIO_DRV_PS_90_45            (0b010 << 16)
#define SDIO_DRV_PS_135_67DOT5       (0b011 << 16)
#define SDIO_DRV_PS_180_90           (0b100 << 16)
#define SDIO_DRV_PS_225_112DOT5      (0b101 << 16)
#define SDIO_DRV_PS_270_145          (0b110 << 16)
#define SDIO_DRV_PS_315_167DOT5      (0b111 << 16)

#define SDIO_SAP_PS_0_0              (0b000 << 12)
#define SDIO_SAP_PS_45_22DOT5        (0b001 << 12)
#define SDIO_SAP_PS_90_45            (0b010 << 12)
#define SDIO_SAP_PS_135_67DOT5       (0b011 << 12)
#define SDIO_SAP_PS_180_90           (0b100 << 12)
#define SDIO_SAP_PS_225_112DOT5      (0b101 << 12)
#define SDIO_SAP_PS_270_145          (0b110 << 12)
#define SDIO_SAP_PS_315_167DOT5      (0b111 << 12)

#define SDIO_CLK_75M               (0b000 << 8)
#define SDIO_CLK_100M              (0b001 << 8)
#define SDIO_CLK_50M               (0b010 << 8)
#define SDIO_CLK_25M               (0b011 << 8)
#define SDIO_CLK_200M              (0b100 << 8)
#define SDIO_CLK_150M              (0b101 << 8)

#define SDIO_SRST_REQ                  (0x1 << 4)
#define SDIO_CKEN                      (0x1 << 1)
#define SDIO_BUS_CKEN                  (0x1 << 0)


static void hi_mci_sys_ctrl_init(struct himci_host *host,
				 resource_size_t host_crg_addr)
{
	unsigned int tmp_reg;

	if ((SDIO_REG_BASE_CRG + PERI_CRG39) == (unsigned int)host_crg_addr) {
		/* enable SDIO clock */
		tmp_reg = himci_readl(host_crg_addr);

		tmp_reg &= ~SDIO_CLK_MASK;
		tmp_reg &= ~SDIO_DRV_PS_MASK;
		tmp_reg &= ~SDIO_SAP_PS_MASK;
		tmp_reg |= SDIO_CLK_100M | SDIO_DRV_PS_135_67DOT5
			| SDIO_SAP_PS_90_45;
		himci_writel(tmp_reg, host_crg_addr);

		/* SDIO soft reset */
		tmp_reg = himci_readl(host_crg_addr);
		tmp_reg |= SDIO_SRST_REQ;
		himci_writel(tmp_reg, host_crg_addr);
		udelay(1000);
		tmp_reg &= ~SDIO_SRST_REQ;
		tmp_reg |= SDIO_CKEN | SDIO_BUS_CKEN;
		himci_writel(tmp_reg, host_crg_addr);
		return;

	}

	if ((SDIO_REG_BASE_CRG + PERI_CRG40) == (unsigned int)host_crg_addr) {

		/* SDIO clock phase */
		tmp_reg = himci_readl(host_crg_addr);
		tmp_reg &= ~SDIO_CLK_MASK;
		tmp_reg |= SDIO_CLK_100M;
		himci_writel(tmp_reg, host_crg_addr);

		/* SDIO soft reset */
		tmp_reg |= SDIO_SRST_REQ;
		himci_writel(tmp_reg, host_crg_addr);
		udelay(1000);
		tmp_reg &= ~SDIO_SRST_REQ;
		tmp_reg |= SDIO_CKEN | SDIO_BUS_CKEN;
		himci_writel(tmp_reg, host_crg_addr);
		return;
	}

	if ((SDIO_REG_BASE_CRG + PERI_CRG163) == (unsigned int)host_crg_addr) {

		/* SDIO clock phase */
		tmp_reg = himci_readl(host_crg_addr);
		tmp_reg &= ~SDIO_CLK_MASK;
		tmp_reg |= SDIO_CLK_100M;
		himci_writel(tmp_reg, host_crg_addr);

		/* SDIO soft reset */
		tmp_reg |= SDIO_SRST_REQ;
		himci_writel(tmp_reg, host_crg_addr);
		udelay(1000);
		tmp_reg &= ~SDIO_SRST_REQ;
		tmp_reg |= SDIO_CKEN | SDIO_BUS_CKEN;
		himci_writel(tmp_reg, host_crg_addr);
		return;
	}

	return;
}

static void hi_mci_sys_ctrl_suspend(struct himci_host *host,
				    resource_size_t host_crg_addr)
{
	unsigned int tmp_reg;

	if ((SDIO_REG_BASE_CRG + PERI_CRG39) == (unsigned int)host_crg_addr) {
		tmp_reg = himci_readl(host_crg_addr);
		tmp_reg |= SDIO_SRST_REQ;
		himci_writel(tmp_reg, host_crg_addr);
		udelay(1000);
		tmp_reg &= ~(SDIO_CKEN | SDIO_BUS_CKEN);
		himci_writel(tmp_reg, host_crg_addr);
		return;

	}

	if ((SDIO_REG_BASE_CRG + PERI_CRG40) == (unsigned int)host_crg_addr) {
		tmp_reg = himci_readl(host_crg_addr);
		tmp_reg |= SDIO_SRST_REQ;
		himci_writel(tmp_reg, host_crg_addr);
		udelay(1000);
		tmp_reg &= ~(SDIO_CKEN | SDIO_BUS_CKEN);
		himci_writel(tmp_reg, host_crg_addr);
		return;
	}

	if ((SDIO_REG_BASE_CRG + PERI_CRG163) == (unsigned int)host_crg_addr) {
		tmp_reg = himci_readl(host_crg_addr);
		tmp_reg |= SDIO_SRST_REQ;
		himci_writel(tmp_reg, host_crg_addr);
		udelay(1000);
		tmp_reg &= ~(SDIO_CKEN | SDIO_BUS_CKEN);
		himci_writel(tmp_reg, host_crg_addr);
		return;
	}
}

static void himci_ldo_config(unsigned int flag, resource_size_t host_crg_addr)
{
	unsigned int tmp_reg; 

	if ((SDIO_REG_BASE_CRG + PERI_CRG39) == (unsigned int)host_crg_addr) {
		if (flag == 0) {
			/* 3.3v output */
			tmp_reg = himci_readl(SD_LDO_BASE_CRG);
			tmp_reg &= ~0x700000;
			tmp_reg |= 0x600000;
			himci_writel(tmp_reg, SD_LDO_BASE_CRG);
		} else {
			/* 1.8v output */
			tmp_reg = himci_readl(SD_LDO_BASE_CRG);
			tmp_reg &= ~0x700000;
			tmp_reg |= 0x200000;
			himci_writel(tmp_reg, SD_LDO_BASE_CRG);
		}
	} 

	if ((SDIO_REG_BASE_CRG + PERI_CRG163) == (unsigned int)host_crg_addr) {
		if (flag == 0) {
			/* 3.3v output */
			tmp_reg = himci_readl(SD_LDO_BASE_CRG);
			tmp_reg &= ~0x70;
			tmp_reg |= 0x60;
			himci_writel(tmp_reg, SD_LDO_BASE_CRG);
		} else {
			/* 1.8v output */
			tmp_reg = himci_readl(SD_LDO_BASE_CRG);
			tmp_reg &= ~0x70;
			tmp_reg |= 0x20;
			himci_writel(tmp_reg, SD_LDO_BASE_CRG);
		}
	}

}
