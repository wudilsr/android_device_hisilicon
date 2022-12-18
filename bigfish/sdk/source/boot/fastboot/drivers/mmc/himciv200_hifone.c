
#include <asm/arch/platform.h>

extern void udelay(unsigned long usec);


static void hi_mci_sys_init(void)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");

	/* eMMC clock phase */
	tmp_reg = himci_readl(REG_BASE_CRG + REG_EMMC_PERI_CRG);
	tmp_reg &= ~SDIO_CLK_MASK;
	tmp_reg |= SDIO_CLK_100M;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_EMMC_PERI_CRG);

	/* eMMC soft reset */
	tmp_reg |= SDIO_SRST_REQ;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_EMMC_PERI_CRG);
	udelay(1000);
	tmp_reg &= ~SDIO_SRST_REQ;
	tmp_reg |= SDIO_CKEN | SDIO_BUS_CKEN;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_EMMC_PERI_CRG);
	
	udelay(1000);
}
