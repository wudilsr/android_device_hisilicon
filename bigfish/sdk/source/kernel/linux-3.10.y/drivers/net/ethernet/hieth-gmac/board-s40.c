/* suppose IO_ADDRESS cover all these address range */
#include <mach/cpu-info.h>

#define HIGMAC_SYSCTL_IOBASE	((void __iomem *)(IO_ADDRESS(0xF8A220CC)))
#define HIGMAC_FEPHY_CRG_CTRL	((void __iomem *)(IO_ADDRESS(0xF8A22120)))
#define HIGMAC_FEPHY_PHY_ADDR	((void __iomem *)(IO_ADDRESS(0xF8A20118)))
#define HIGMAC_FEPHY_SELECT	((void __iomem *)(IO_ADDRESS(0xF8A20008)))
#define HIGMAC_FEPHY_LDO_CTRL	((void __iomem *)(IO_ADDRESS(0xF8A20844)))
#define LDO_VSET_MASK		0xF
#define LDO_VSET_VAL		0x8
#define LDO_EN_OFFSET		4

#define HIGMAC_FWD_IOBASE		(IO_ADDRESS(0xF9842000))

#define HIGMAC_MAC0_IF_CTRL	((void __iomem *)(IO_ADDRESS(0xF984300C)))
#define HIGMAC_MAC1_IF_CTRL	((void __iomem *)(IO_ADDRESS(0xF9843010)))
#define HIGMAC_MAC2_IF_CTRL	((void __iomem *)(IO_ADDRESS(0xF8A222DC)))

#define HIGMAC_DUAL_MAC_CRF_ACK_TH	((void __iomem *)(IO_ADDRESS(0xF9843004)))
#define HIGMAC_THIRD_MAC_CRF_ACK_TH	((void __iomem *)(IO_ADDRESS(0xF9C33004)))

/* DEFAULT mac1's phy reset pin */
#define MAC1_PHY_RESET_BASE	((void __iomem *)(IO_ADDRESS(0xF8A22168)))
#define MAC1_PHY_RESET_BIT		1

#define EXT_PHY0_RST_BIT		12
#define EXT_PHY1_RST_BIT		13
#define EXT_PHY2_RST_BIT		16

void __iomem *soc_fwdctl_iobase(void)
{
	return (void __iomem *)HIGMAC_FWD_IOBASE;
}

void higmac_hw_mac_core_reset(struct higmac_netdev_local *ld)
{
	struct higmac_adapter *adapter = ld->adapter;
	unsigned int v = 0, index;
	unsigned long flags;

	spin_lock_irqsave(&adapter->lock, flags);

	/* TODO: enable clk here. fpga use fixed clk */
#ifndef CONFIG_S40_FPGA
	v = readl(HIGMAC_SYSCTL_IOBASE);
	if (get_chipid() == _HI3798CV100A || get_chipid() == _HI3798CV100
		|| get_chipid() == _HI3796CV100) {
		v &= ~(0xf << 12);//undo reset   enable clk
	} else {
		v |= 0x7f; /* enable clk, select DPLL */
	}
	writel((u32)v, HIGMAC_SYSCTL_IOBASE);
#endif
#if (CONFIG_GMAC_NUMS > 2)
	v = readl(HIGMAC_SYSCTL_IOBASE);
	v |= 0x73C0000;
	writel((u32)v, HIGMAC_SYSCTL_IOBASE);
#endif
	/* set reset bit */
	if (get_chipid() == _HI3798CV100A || get_chipid() == _HI3798CV100
		|| get_chipid() == _HI3796CV100) {
		index = ld->index + 12;/* 12--reset bit offset */
	}else {
		index = ld->index + 8;/* 8--reset bit offset */
	}
#if (CONFIG_GMAC_NUMS > 2)
	if (ld->index == 2)
		index = 22;
#endif
	v = readl((void __iomem *)HIGMAC_SYSCTL_IOBASE);
	if (ld->index < 2)
		v |= 0x5 << index;
	else
		v |= 0x3 << index;
	writel((u32)v, HIGMAC_SYSCTL_IOBASE);
	spin_unlock_irqrestore(&adapter->lock, flags);

	udelay(50);

	spin_lock_irqsave(&adapter->lock, flags);
	/* clear reset bit */
	v = readl(HIGMAC_SYSCTL_IOBASE);
	if (ld->index < 2)
		v &= ~(0x5 << index);
	else
		v &= ~(0x3 << index);
	writel((u32)v, HIGMAC_SYSCTL_IOBASE);

	spin_unlock_irqrestore(&adapter->lock, flags);
}

void higmac_set_macif(struct higmac_netdev_local *ld, int mode, int speed)
{
	struct higmac_adapter *adapter = ld->adapter;
	unsigned long flags;
	unsigned long v;

	/* enable change: port_mode */
	higmac_writel_bits(ld, 1, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);
	if (speed == 2)/* FIXME */
		speed = 5;/* 1000M */
	higmac_writel_bits(ld, speed, PORT_MODE, BITS_PORT_MODE);
	/* disable change: port_mode */
	higmac_writel_bits(ld, 0, MODE_CHANGE_EN, BIT_MODE_CHANGE_EN);

	spin_lock_irqsave(&adapter->lock, flags);
	/* soft reset mac_if */
	v = readl(HIGMAC_SYSCTL_IOBASE);
	if (ld->index < 2) {
		if (get_chipid() == _HI3798CV100A || get_chipid() == _HI3798CV100
				|| get_chipid() == _HI3796CV100) {
			v |= 1 << (ld->index + 14);/* bit14 for macif0 */
		} else { 
			v |= 1 << (ld->index + 10);/* bit10 for macif0 */
		}
	} else
		v |= 1 << 23;
	writel((u32)v, HIGMAC_SYSCTL_IOBASE);

	/* config mac_if */
	if (ld->index == 2)/* eth2 */
		writel((u32)mode, HIGMAC_MAC2_IF_CTRL);
	else if (ld->index == 1)/* eth1 */
		writel((u32)mode, HIGMAC_MAC1_IF_CTRL);
	else
		writel((u32)mode, HIGMAC_MAC0_IF_CTRL);

	/* undo reset */
	v = readl(HIGMAC_SYSCTL_IOBASE);
	if (ld->index < 2) {
		if (get_chipid() == _HI3798CV100A || get_chipid() == _HI3798CV100
				|| get_chipid() == _HI3796CV100) {
			v &= ~(1 << (ld->index + 14));
		} else {
			v &= ~(1 << (ld->index + 10));
		}
	} else
		v &= ~(1 << 23);
	writel((u32)v, HIGMAC_SYSCTL_IOBASE);
	spin_unlock_irqrestore(&adapter->lock, flags);
}

#ifdef CONFIG_S40_FPGA
void higmac_hw_internal_fephy_reset(struct higmac_adapter *adapter) {}
#else
void higmac_hw_internal_fephy_reset(struct higmac_adapter *adapter)
{
	unsigned int v = 0;
	unsigned long flags;

	writel(0, HIGMAC_FEPHY_CRG_CTRL);/* disable clk */

	v = readl(HIGMAC_FEPHY_SELECT);
	if ((v & (1 << 8)) != 0)
		return;/* if not use fephy, leave it's clk disabled */

	v = readl(HIGMAC_FEPHY_LDO_CTRL);
	/* set internal FEPHY LDO_VSET value */
	v = (v & ~LDO_VSET_MASK) | LDO_VSET_VAL;
#ifdef CONFIG_ARCH_HIFONE
	/* enalbe internal FEPHY LDO_EN for hifone_b02 */
	v |= (0x1 << LDO_EN_OFFSET);
#endif
	writel(v, HIGMAC_FEPHY_LDO_CTRL);/* LDO output 1.1V */

	spin_lock_irqsave(&adapter->lock, flags);
	/* suppose internal phy can only be used as mac0's phy */
	writel((u32)higmac_board_info[0].phy_addr, HIGMAC_FEPHY_PHY_ADDR);

	v = readl(HIGMAC_FEPHY_CRG_CTRL);
	v |= 0x1; /* use 25MHz clock, enable clk */
	writel((u32)v, HIGMAC_FEPHY_CRG_CTRL);
	spin_unlock_irqrestore(&adapter->lock, flags);

	udelay(10);

	spin_lock_irqsave(&adapter->lock, flags);
	v = readl(HIGMAC_FEPHY_CRG_CTRL);
	v |= (0x1 << 4); /* set reset bit */
	writel((u32)v, HIGMAC_FEPHY_CRG_CTRL);
	spin_unlock_irqrestore(&adapter->lock, flags);

	udelay(10);

	spin_lock_irqsave(&adapter->lock, flags);
	v = readl(HIGMAC_FEPHY_CRG_CTRL);
	v &= ~(0x1 << 4); /* clear reset bit */
	writel((u32)v, HIGMAC_FEPHY_CRG_CTRL);
	spin_unlock_irqrestore(&adapter->lock, flags);

	msleep(20); /* delay at least 15ms for MDIO operation */
}
#endif

void higmac_hw_external_phy_reset(void)
{
	u32 v;

#ifdef CONFIG_ARCH_HIFONE
	/* HIFONE use CRG register to reset phy */
	v = readl(HIGMAC_SYSCTL_IOBASE);
	/* RST_BIT, write 0 to reset phy, write 1 to cancel reset */
	v &= ~(1 << EXT_PHY0_RST_BIT | 1 << EXT_PHY1_RST_BIT |
			1 << EXT_PHY2_RST_BIT);
	writel(v, HIGMAC_SYSCTL_IOBASE);

	/* delay some time to ensure reset ok,
	 * this depends on PHY hardware feature
	 */
	msleep(20);

	v = readl(HIGMAC_SYSCTL_IOBASE);
	/* write 1 to cancel reset */
	v |= (1 << EXT_PHY0_RST_BIT | 1 << EXT_PHY1_RST_BIT |
			1 << EXT_PHY2_RST_BIT);
	writel(v, HIGMAC_SYSCTL_IOBASE);

	/* delay some time to ensure later MDIO access */
	msleep(10);
#endif

	v = readl(MAC1_PHY_RESET_BASE);
	v |= 1 << MAC1_PHY_RESET_BIT;
	writel(v, MAC1_PHY_RESET_BASE);

	msleep(20);

	/* then, cancel reset, and should delay 200ms */
	v &= ~(1 << MAC1_PHY_RESET_BIT);
	writel(v, MAC1_PHY_RESET_BASE);

	msleep(20);
	v |=  1 << MAC1_PHY_RESET_BIT;
	writel(v, MAC1_PHY_RESET_BASE);

	/* use gpio to control mac0's phy reset */
#ifdef CONFIG_MAC0_PHY_GPIO_RESET
	/* config gpip[x] dir to output */
	v = readb(CONFIG_MAC0_PHY_RESET_GPIO_BASE + 0x400);
	v |= (1 << CONFIG_MAC0_PHY_RESET_GPIO_BIT);
	writeb(v, CONFIG_MAC0_PHY_RESET_GPIO_BASE + 0x400);

	/* gpiox[x] set to reset, then delay 200ms */
	writeb(CONFIG_MAC0_PHY_RESET_GPIO_DATA
			<< CONFIG_MAC0_PHY_RESET_GPIO_BIT,
			CONFIG_MAC0_PHY_RESET_GPIO_BASE +
			(4 << CONFIG_MAC0_PHY_RESET_GPIO_BIT));
	msleep(20);
	/* then,cancel reset,and should delay 200ms */
	writeb((!CONFIG_MAC0_PHY_RESET_GPIO_DATA)
			<< CONFIG_MAC0_PHY_RESET_GPIO_BIT,
			CONFIG_MAC0_PHY_RESET_GPIO_BASE +
			(4 << CONFIG_MAC0_PHY_RESET_GPIO_BIT));
	msleep(20);
	writeb(CONFIG_MAC0_PHY_RESET_GPIO_DATA
			<< CONFIG_MAC0_PHY_RESET_GPIO_BIT,
			CONFIG_MAC0_PHY_RESET_GPIO_BASE +
			(4 << CONFIG_MAC0_PHY_RESET_GPIO_BIT));
#endif

	/* use gpio to control mac1's phy reset */
#ifdef CONFIG_MAC1_PHY_GPIO_RESET
	/* config gpip[x] dir to output */
	v = readb(CONFIG_MAC1_PHY_RESET_GPIO_BASE + 0x400);
	v |= (1 << CONFIG_MAC1_PHY_RESET_GPIO_BIT);
	writeb(v, CONFIG_MAC1_PHY_RESET_GPIO_BASE + 0x400);

	/* gpiox[x] set to reset, then delay 200ms */
	writeb(CONFIG_MAC1_PHY_RESET_GPIO_DATA
			<< CONFIG_MAC1_PHY_RESET_GPIO_BIT,
			CONFIG_MAC1_PHY_RESET_GPIO_BASE +
			(4 << CONFIG_MAC1_PHY_RESET_GPIO_BIT));
	msleep(20);
	/* then,cancel reset,and should delay 200ms */
	writeb((!CONFIG_MAC1_PHY_RESET_GPIO_DATA)
			<< CONFIG_MAC1_PHY_RESET_GPIO_BIT,
			CONFIG_MAC1_PHY_RESET_GPIO_BASE +
			(4 << CONFIG_MAC1_PHY_RESET_GPIO_BIT));
	msleep(20);
	writeb(CONFIG_MAC1_PHY_RESET_GPIO_DATA
			<< CONFIG_MAC1_PHY_RESET_GPIO_BIT,
			CONFIG_MAC1_PHY_RESET_GPIO_BASE +
			(4 << CONFIG_MAC1_PHY_RESET_GPIO_BIT));
#endif
	/* add some delay in case mdio cann't access now! */
	msleep(30);
}

void higmac_hw_all_clk_disable(void)
{
	writel(0, HIGMAC_SYSCTL_IOBASE);/* gmac clk disable */
	writel(0, HIGMAC_FEPHY_CRG_CTRL);/* inside fephy clk disable */
}

void higmac_hw_all_clk_enable(void)
{
	u32 v = 0;

	v = readl(HIGMAC_FEPHY_CRG_CTRL);
	v |= 0x1;
	writel(v, HIGMAC_FEPHY_CRG_CTRL);/* inside fephy clk enable */

	v = readl(HIGMAC_SYSCTL_IOBASE);
	v |= 0x7f;
	writel(v, HIGMAC_SYSCTL_IOBASE);/* gmac clk enable */
}
