#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/types.h>
#include <mach/hardware.h>

#include "xhci.h"
#include "hiusb.h"

MODULE_LICENSE("Dual MIT/GPL");

#define PERI_CRG44                    __io_address(0xf8a22000 + 0xb0)
#define USB3_VCC_SRST_REQ1            (0x1<<28)
#define USB3_BUS_GM_CKEN1             (0x1<<22)
#define USB3_BUS_GS_CKEN1             (0x1<<21)
#define USB3_UTMI_CKEN1               (0x1<<20)
#define USB3_PIPE_CKEN1               (0x1<<19)
#define USB3_SUSPEND_CKEN1            (0x1<<18)
#define USB3_REF_CKEN1                (0x1<<17)
#define USB3_BUS_CKEN1                (0x1<<16)

#define USB3_VCC_SRST_REQ             (0x1<<12)
#define USB3_BUS_GM_CKEN              (0x1<<6)
#define USB3_BUS_GS_CKEN              (0x1<<5)
#define USB3_UTMI_CKEN                (0x1<<4)
#define USB3_PIPE_CKEN                (0x1<<3)
#define USB3_SUSPEND_CKEN             (0x1<<2)
#define USB3_REF_CKEN                 (0x1<<1)
#define USB3_BUS_CKEN                 (0x1<<0)

#define PERI_CRG47                    __io_address(0xF8A22000 + 0xbc)
#define USB2_PHY01_REF_CKEN           (1 << 0)
#define USB2_PHY2_REF_CKEN            (1 << 2)
#define USB2_PHY3_REF_CKEN            (1 << 3)
#define USB2_PHY01_SRST_REQ           (1 << 4)
#define USB2_PHY2_SRST_REQ            (1 << 6)
#define USB2_PHY3_SRST_REQ            (1 << 7)
#define USB2_PHY01_SRST_TREQ0         (1 << 8)
#define USB2_PHY01_SRST_TREQ1         (1 << 9)
#define USB2_PHY2_SRST_TREQ           (1 << 10)
#define USB2_PHY3_SRST_TREQ           (1 << 11)
#define USB2_PHY01_REFCLK_SEL         (1 << 12)
#define USB2_PHY2_REFCLK_SEL          (1 << 14)
#define USB2_PHY3_REFCLK_SEL          (1 << 15)

#define PERI_CRG98                    __io_address(0xF8A22000 + 0x188)
#define COMBPHY0_REF_CKEN             (1 << 0)
#define COMBPHY0_SRST_REQ             (1 << 4)
#define COMBPHY1_REF_CKEN             (1 << 8)
#define COMBPHY1_SRST_REQ             (1 << 12)

#define PERI_CTRL                     __io_address(0xF8A20000 + 0x8)
#define COMBPHY1_USB3_SEL0            (1 << 12)
#define COMBPHY1_USB3_SEL1            (1 << 11)

#define PERI_USB2                     __io_address(0xF8A20000 + 0x128)

#define GTXTHRCFG                     0xc108
#define GRXTHRCFG                     0xc10c
#define REG_GCTL                      0xc110
#define REG_GUSB2PHYCFG0              0xC200
#define REG_GUSB3PIPECTL0             0xc2c0

#define BIT_UTMI_ULPI                 (0x1<<4)
#define BIT_UTMI_8_16                 (0x1<<3)
#define PCS_SSP_SOFT_RESET            (0x1<<31)

 #define USB3_DEEMPHASIS              (0x1 << 2)
 #define USB3_DEEMPHASIS_MASK         (0x3 << 1)

extern void hiusb_start_hcd_hifone(resource_size_t host_addr);
extern void hiusb_stop_hcd_hifone(resource_size_t host_addr);

void hiusb3_start_hcd(void __iomem *base)
{
	unsigned int reg;

	/* open clk and cancel reset */
	if (__io_address(CONFIG_HIUSB_XHCI_IOBASE) == base) {
		/* init usb2 phy */
		hiusb_start_hcd_hifone(CONFIG_HIUSB_EHCI_IOBASE);

		/* cancel 2p phy utmi reset1 */
		reg = readl(PERI_CRG47);
		reg &= ~(USB2_PHY01_SRST_TREQ1);
		writel(reg, PERI_CRG47);
		msleep(1);

		/* open combphy0 cken */
		reg = readl(PERI_CRG98);
		reg |= (COMBPHY0_REF_CKEN);
		writel(reg, PERI_CRG98);
		msleep(1);
		
		/* cancel combphy0 POR */
		reg = readl(PERI_CRG98);
		reg &= ~(COMBPHY0_SRST_REQ);
		writel(reg, PERI_CRG98);
		msleep(5);

		/* open u3 ctrl0 cken */
		reg = readl(PERI_CRG44);
		reg |= (USB3_BUS_GM_CKEN
			| USB3_BUS_GS_CKEN
			| USB3_UTMI_CKEN
			| USB3_PIPE_CKEN
			| USB3_SUSPEND_CKEN
			| USB3_REF_CKEN
			| USB3_BUS_CKEN);
		writel(reg, PERI_CRG44);
		msleep(100);

		/* cancel u3 ctrl0 reset */
		reg = readl(PERI_CRG44);
		reg &= ~(USB3_VCC_SRST_REQ);
		writel(reg, PERI_CRG44);
		msleep(100);
		
	} else if (__io_address(CONFIG_HIUSB_XHCI1_IOBASE) == base) {
	
		/* select U3 COMBPHY1 mode */
		reg = readl(PERI_CTRL);
		reg |= (COMBPHY1_USB3_SEL1);
		writel(reg, PERI_CTRL);
		msleep(1);

		/* cancel 1p phy POR */
		reg = readl(PERI_CRG47);
		reg &= ~(USB2_PHY3_SRST_REQ);
		writel(reg, PERI_CRG47);
		msleep(1);

		/* config 1p phy clk */
		writel(0xa60c, PERI_USB2);
		writel(0xe60c, PERI_USB2);
		writel(0xa60c, PERI_USB2);
		msleep(10);

		/* cancel 1p phy utmi reset */
		reg = readl(PERI_CRG47);
		reg &= ~(USB2_PHY3_SRST_TREQ);
		writel(reg, PERI_CRG47);
		msleep(1);
		
		/* open combphy1 cken */
		reg = readl(PERI_CRG98);
		reg |= (COMBPHY1_REF_CKEN);
		writel(reg, PERI_CRG98);
		msleep(1);

		/* cancel combphy1 POR */
		reg = readl(PERI_CRG98);
		reg &= ~(COMBPHY1_SRST_REQ);
		writel(reg, PERI_CRG98);
		msleep(5);

		reg = readl(PERI_CRG44);
		reg |= (USB3_BUS_GM_CKEN1
			| USB3_BUS_GS_CKEN1
			| USB3_UTMI_CKEN1
			| USB3_PIPE_CKEN1
			| USB3_SUSPEND_CKEN1
			| USB3_REF_CKEN1
			| USB3_BUS_CKEN1);
		writel(reg, PERI_CRG44);
		msleep(100);

		/* cancel u3 ctrl1 reset */
		reg = readl(PERI_CRG44);
		reg &= ~(USB3_VCC_SRST_REQ1);
		writel(reg, PERI_CRG44);
		msleep(100);
	}

	reg = readl(base + REG_GUSB3PIPECTL0);
	reg |= PCS_SSP_SOFT_RESET;
	writel(reg, base + REG_GUSB3PIPECTL0);

#ifdef CONFIG_HIFONE_FPGA
	/* configure for TMT, utmi 16bit interface */
	reg = readl(base + REG_GUSB2PHYCFG0);
	reg &= ~(0xf<<10);
	reg |= (0x9<<10);
	reg &= ~BIT_UTMI_8_16;
	reg &= ~(0x1<<6);       //disable suspend
	reg |= (0x1<<4);      //select ulpi
	writel(reg, base + REG_GUSB2PHYCFG0);
	wmb();
	msleep(20);
#else
	/* USB2 PHY chose ulpi 8bit interface */
	reg = readl(base + REG_GUSB2PHYCFG0);
	reg &= ~BIT_UTMI_ULPI;
	reg &= ~(BIT_UTMI_8_16);
	writel(reg, base + REG_GUSB2PHYCFG0);
	wmb();
	msleep(20);
#endif

	reg = readl(base + REG_GCTL);
	reg &= ~(0x3<<12);
	reg |= (0x1<<12);      //[13:12] 01: Host; 10: Device; 11: OTG
	writel(reg, base + REG_GCTL);

	reg = readl(base + REG_GUSB3PIPECTL0);
	reg &= ~PCS_SSP_SOFT_RESET;
	reg &= ~(0x1<<17);       //disable suspend
	reg &= ~USB3_DEEMPHASIS_MASK;     //0db  de-emphasis
	reg |= USB3_DEEMPHASIS; 
	writel(reg, base + REG_GUSB3PIPECTL0);
	msleep(100);

	writel(0x23100000, base + GTXTHRCFG);
	writel(0x23100000, base + GRXTHRCFG);
	msleep(20);
}

EXPORT_SYMBOL(hiusb3_start_hcd);

void hiusb3_stop_hcd(void __iomem *base)
{
	unsigned int reg;

	if (__io_address(CONFIG_HIUSB_XHCI_IOBASE) == base) {

		hiusb_stop_hcd_hifone(CONFIG_HIUSB_EHCI_IOBASE);

		reg = readl(PERI_CRG44);
		reg |= USB3_VCC_SRST_REQ;
		writel(reg, PERI_CRG44);
	
		reg = readl(PERI_CRG47);
		reg |= USB2_PHY01_SRST_TREQ1;
		writel(reg, PERI_CRG47);
		
		reg = readl(PERI_CRG98);
		reg |= COMBPHY0_SRST_REQ;
		writel(reg, PERI_CRG98);
		
		msleep(500);
		
	} else if (__io_address(CONFIG_HIUSB_XHCI1_IOBASE) == base) {
		reg = readl(PERI_CRG44);
		reg |= USB3_VCC_SRST_REQ1;
		writel(reg, PERI_CRG44);
	
		reg = readl(PERI_CRG47);
		reg |= USB2_PHY3_SRST_REQ;
		reg |= USB2_PHY3_SRST_TREQ;
		writel(reg, PERI_CRG47);

		reg = readl(PERI_CRG98);
		reg |= COMBPHY1_SRST_REQ;
		writel(reg, PERI_CRG98);

		msleep(500);
	}
}

EXPORT_SYMBOL(hiusb3_stop_hcd);