#include <linux/init.h>
#include <linux/timer.h>
#include <linux/ktime.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <linux/spinlock.h>
#include <asm/byteorder.h>
#include <linux/io.h>
#include <asm/system.h>
#include <asm/unaligned.h>
#include <mach/cpu-info.h>
#include <mach/hardware.h>

#define PERI_CRG46                      __io_address(0xF8A22000 + 0xb8)
#define USB2_BUS_CKEN                   (1<<0)
#define USB2_OHCI48M_CKEN               (1<<1)
#define USB2_OHCI12M_CKEN               (1<<2)
#define USB2_OTG_UTMI_CKEN              (1<<3)
#define USB2_HST_PHY_CKEN               (1<<4)
#define USB2_UTMI0_CKEN                 (1<<5)
#define USB2_BUS_SRST_REQ               (1<<12)
#define USB2_UTMI0_SRST_REQ             (1<<13)
#define USB2_HST_PHY_SYST_REQ           (1<<16)
#define USB2_OTG_PHY_SYST_REQ           (1<<17)
#define USB2_CLK48_SEL                  (1<<20)

#define PERI_CRG102                     __io_address(0xF8A22000 + 0x198)
#define USB2_BUS_CKEN1                  (1<<0)
#define USB2_OHCI48M_CKEN1              (1<<1)
#define USB2_OHCI12M_CKEN1              (1<<2)
#define USB2_HST_PHY_CKEN1              (1<<4)
#define USB2_UTMI0_CKEN1                (1<<5)
#define USB2_BUS_SRST_REQ1              (1<<12)
#define USB2_UTMI0_SRST_REQ1            (1<<14)
#define USB2_HST_PHY_SYST_REQ1          (1<<16)
#define USB2_CLK48_SEL1                 (1<<20)

#define PERI_CRG47                      __io_address(0xF8A22000 + 0xbc)
#define USB2_PHY01_REF_CKEN             (1 << 0)
#define USB2_PHY2_REF_CKEN              (1 << 2)
#define USB2_PHY3_REF_CKEN              (1 << 3)
#define USB2_PHY01_SRST_REQ             (1 << 4)
#define USB2_PHY2_SRST_REQ              (1 << 6)
#define USB2_PHY3_SRST_REQ              (1 << 7)
#define USB2_PHY01_SRST_TREQ0           (1 << 8)
#define USB2_PHY01_SRST_TREQ1           (1 << 9)
#define USB2_PHY2_SRST_TREQ             (1 << 10)
#define USB2_PHY3_SRST_TREQ             (1 << 11)
#define USB2_PHY01_REFCLK_SEL           (1 << 12)
#define USB2_PHY2_REFCLK_SEL            (1 << 14)
#define USB2_PHY3_REFCLK_SEL            (1 << 15)

#define PERI_USB0                       __io_address(0xF8A20000 + 0x120)
#define PERI_USB1                       __io_address(0xF8A20000 + 0x124)
#define PERI_USB3                       __io_address(0xF8A20000 + 0x12c)
#define PERI_USB4                       __io_address(0xF8A20000 + 0x130)

#define TEST_WRDATA                     (0xc)
#define TEST_ADDR                       (0x6 << 8)
#define TEST_WREN                       (1 << 13)
#define TEST_CLK                        (1 << 14)
#define TEST_RSTN                       (1 << 15)

#define WORDINTERFACE                   (1 << 0)
#define ULPI_BYPASS_EN_PORT0            (1 << 3)
#define SS_BURST16_EN                   (1 << 9)

static atomic_t dev_open_cnt = {
	.counter = 0,
};

static atomic_t dev_open_cnt1 = {
	.counter = 0,
};

void hiusb_start_hcd_hifone(resource_size_t host_addr)
{
	int reg;

	if (CONFIG_HIUSB_EHCI1_IOBASE == host_addr ||
			CONFIG_HIUSB_OHCI1_IOBASE == host_addr) {
		if (atomic_add_return(1, &dev_open_cnt1) == 1) {

			/*controller bus/utmi/roothub reset*/
			reg = readl(PERI_CRG102);
			reg |= (USB2_BUS_SRST_REQ1 //12th bit
				| USB2_UTMI0_SRST_REQ1 //14th bit
				| USB2_HST_PHY_SYST_REQ1);//16th bit
			writel(reg, PERI_CRG102);
			udelay(200);

			/* phy por/utmi reset */
			reg = readl(PERI_CRG47);
			reg |= (USB2_PHY2_SRST_REQ
				| USB2_PHY2_SRST_TREQ);
			writel(reg, PERI_CRG47);
			udelay(200);

#ifdef CONFIG_HIFONE_FPGA
			reg = readl(PERI_USB4);
			reg &= ~ULPI_BYPASS_EN_PORT0;     /* port2:ulpi */
			reg &= ~(WORDINTERFACE);         /*  port2 : 8bit*/
			reg &= ~(SS_BURST16_EN);
			writel(reg, PERI_USB4);
			udelay(100);
#else
			reg = readl(PERI_USB4);
			reg |= ULPI_BYPASS_EN_PORT0;  /* 1 ports utmi */
			reg &= ~(WORDINTERFACE);      /* 8bit */
			reg &= ~(SS_BURST16_EN);      /* 16 bit burst disable */
			writel(reg, PERI_USB4);
			udelay(100);
#endif

			/* open ref clk */
			reg = readl(PERI_CRG47);
			reg |= (USB2_PHY2_REF_CKEN);
			writel(reg, PERI_CRG47);
			udelay(300);

			/* cancel phy power on reset */
			reg = readl(PERI_CRG47);
			reg &= ~(USB2_PHY2_SRST_REQ);
			writel(reg, PERI_CRG47);
			udelay(500);

			/* config clk output */
			reg = TEST_WRDATA|TEST_ADDR|TEST_WREN|TEST_RSTN;
			writel(reg, PERI_USB1);
			reg = TEST_WRDATA|TEST_ADDR|TEST_WREN|TEST_RSTN|TEST_CLK;
			writel(reg, PERI_USB1);
			reg = TEST_WRDATA|TEST_ADDR|TEST_WREN|TEST_RSTN;
			writel(reg, PERI_USB1);
			udelay(50);

#ifdef CONFIG_HIFONE_FPGA
			mdelay(1);
#else
			mdelay(10);
#endif

			/* 1port PHY¡ê?HS pre-emphasize 000 */
  			writel(0xa018, PERI_USB1);
  			udelay(10);
  			writel(0xe018, PERI_USB1);
			udelay(10);
			writel(0xa018, PERI_USB1);
			udelay(50);
			
			/* 1port PHY¡ê?squelch trigger point 175mV */
  			writel(0xa16e, PERI_USB1);
  			udelay(10);
  			writel(0xe16e, PERI_USB1);
			udelay(10);
			writel(0xa16e, PERI_USB1);
			udelay(50);
			
			/* 1port PHY¡ê?Rcomp=200mV¡ê?Vref=425mV */
  			writel(0xa532, PERI_USB1);
  			udelay(10);
  			writel(0xe532, PERI_USB1);
			udelay(10);
			writel(0xa532, PERI_USB1);
			udelay(50);
			
			writel(0xa703, PERI_USB1);
  			udelay(10);
  			writel(0xe703, PERI_USB1);
			udelay(10);
			writel(0xa703, PERI_USB1);
			udelay(50);

			/* 1port PHY¡ê?Icomp=212mV */
  			writel(0xaabb, PERI_USB1);
  			udelay(10);
  			writel(0xeabb, PERI_USB1);
			udelay(10);
			writel(0xaabb, PERI_USB1);
			udelay(50);
			
			/* cancel phy utmi port reset */
			reg = readl(PERI_CRG47);
			reg &= ~(USB2_PHY2_SRST_TREQ);
			writel(reg, PERI_CRG47);
			udelay(300);

			/* open control clk  */
			reg = readl(PERI_CRG102);
			reg |= (USB2_BUS_CKEN1
				| USB2_OHCI48M_CKEN1
				| USB2_OHCI12M_CKEN1
				| USB2_HST_PHY_CKEN1
				| USB2_UTMI0_CKEN1);
			writel(reg, PERI_CRG102);
			udelay(200);

			/* cancel controller reset */
			reg = readl(PERI_CRG102);
			reg &= ~(USB2_BUS_SRST_REQ1
				| USB2_UTMI0_SRST_REQ1
				| USB2_HST_PHY_SYST_REQ1);
			writel(reg, PERI_CRG102);
			udelay(200);
		}

	} else if (CONFIG_HIUSB_EHCI_IOBASE == host_addr ||
			CONFIG_HIUSB_OHCI_IOBASE == host_addr
#ifdef CONFIG_HIUSBUDC_REG_BASE_ADDRESS
			|| CONFIG_HIUSBUDC_REG_BASE_ADDRESS == host_addr
#endif
			) {
		if (atomic_add_return(1, &dev_open_cnt) == 1) {

			/* controller bus/utmi/roothub reset */
			reg = readl(PERI_CRG46);
			reg |= (USB2_BUS_SRST_REQ
				| USB2_UTMI0_SRST_REQ
				| USB2_HST_PHY_SYST_REQ
				| USB2_OTG_PHY_SYST_REQ);
			writel(reg, PERI_CRG46);

			/* phy por/utmi reset enable */
			reg = readl(PERI_CRG47);
			reg |= (USB2_PHY01_SRST_REQ
				| USB2_PHY01_SRST_TREQ0);
			writel(reg, PERI_CRG47);
			udelay(200);

#ifdef CONFIG_HIFONE_FPGA 
			reg = readl(PERI_USB3);
			reg &= ~ULPI_BYPASS_EN_PORT0;     /* port0/port1:ulpi */
			reg &= ~(WORDINTERFACE);          /*  port0 : 8bit*/
			reg &= ~(SS_BURST16_EN);
			writel(reg, PERI_USB3);
			udelay(100);
#else
			reg = readl(PERI_USB3);
			reg |= ULPI_BYPASS_EN_PORT0;  /* 2 ports utmi */
			reg &= ~(WORDINTERFACE);      /* 8bit */
			reg &= ~(SS_BURST16_EN);      /* 16 bit burst disable */
			writel(reg, PERI_USB3);
			udelay(100);
#endif

			/* open PHY Ref Clock */
			reg = readl(PERI_CRG47);
			reg |= (USB2_PHY01_REF_CKEN);
			writel(reg, PERI_CRG47);
			udelay(300);

			/* cancel power on reset */
			reg = readl(PERI_CRG47);
			reg &= ~(USB2_PHY01_SRST_REQ);
			writel(reg, PERI_CRG47);
			udelay(500);

			/* config clk output */    
			reg = TEST_WRDATA|TEST_ADDR|TEST_WREN|TEST_RSTN;
			writel(reg, PERI_USB0);
			reg = TEST_WRDATA|TEST_ADDR|TEST_WREN|TEST_RSTN|TEST_CLK;
			writel(reg, PERI_USB0);
			reg = TEST_WRDATA|TEST_ADDR|TEST_WREN|TEST_RSTN;
			writel(reg, PERI_USB0);
			udelay(50);

#ifdef CONFIG_HIFONE_FPGA
			mdelay(1);
#else
			mdelay(10);
#endif
			/* 2port PHY¡ê?HS pre-emphasize¡ê?000 */
  			writel(0xa018, PERI_USB0);
  			udelay(10);
  			writel(0xe018, PERI_USB0);
			udelay(10);
			writel(0xa018, PERI_USB0);
			udelay(50);

			writel(0xb018, PERI_USB0);
  			udelay(10);
  			writel(0xf018, PERI_USB0);
			udelay(10);
			writel(0xb018, PERI_USB0);
			udelay(50);

			/* 2port PHY¡ê?squelch trigger point 175mV */
  			writel(0xa16e, PERI_USB0);
  			udelay(10);
  			writel(0xe16e, PERI_USB0);
			udelay(10);
			writel(0xa16e, PERI_USB0);
			udelay(50);

			writel(0xb16e, PERI_USB0);
  			udelay(10);
  			writel(0xf16e, PERI_USB0);
			udelay(10);
			writel(0xb16e, PERI_USB0);
			udelay(50);

			/* 2port PHY¡ê?Rcomp=187mV¡ê?Vref=425mV */
  			writel(0xa5b2, PERI_USB0);
  			udelay(10);
  			writel(0xe5b2, PERI_USB0);
			udelay(10);
			writel(0xa5b2, PERI_USB0);
			udelay(50);

			writel(0xb5b2, PERI_USB0);
  			udelay(10);
  			writel(0xf5b2, PERI_USB0);
			udelay(10);
			writel(0xb5b2, PERI_USB0);
			udelay(50);

			writel(0xa703, PERI_USB0);
  			udelay(10);
  			writel(0xe703, PERI_USB0);
			udelay(10);
			writel(0xa703, PERI_USB0);
			udelay(50);

			writel(0xb703, PERI_USB0);
  			udelay(10);
  			writel(0xf703, PERI_USB0);
			udelay(10);
			writel(0xb703, PERI_USB0);
			udelay(50);

			/* 2port PHY¡ê?Icomp=187mV */
  			writel(0xaa3b, PERI_USB0);
  			udelay(10);
  			writel(0xea3b, PERI_USB0);
			udelay(10);
			writel(0xaa3b, PERI_USB0);
			udelay(50);

			writel(0xba3b, PERI_USB0);
  			udelay(10);
  			writel(0xfa3b, PERI_USB0);
			udelay(10);
			writel(0xba3b, PERI_USB0);
			udelay(50);
			
			/* cancel phy utmi  reset */
			reg = readl(PERI_CRG47);
			reg &= ~(USB2_PHY01_SRST_TREQ0);
			writel(reg, PERI_CRG47);
			udelay(300);

			/* open controller clk */
			reg = readl(PERI_CRG46);
			reg |= (USB2_BUS_CKEN
				| USB2_OHCI48M_CKEN
				| USB2_OHCI12M_CKEN
				| USB2_OTG_UTMI_CKEN
				| USB2_HST_PHY_CKEN
				| USB2_UTMI0_CKEN);
			writel(reg, PERI_CRG46);
			udelay(200);

			/* cancel control reset */
			reg = readl(PERI_CRG46);
			reg &= ~(USB2_BUS_SRST_REQ
				| USB2_UTMI0_SRST_REQ
				| USB2_HST_PHY_SYST_REQ
				| USB2_OTG_PHY_SYST_REQ);
			writel(reg, PERI_CRG46);
			udelay(200);
		}
	}
	return;
}

void hiusb_stop_hcd_hifone(resource_size_t host_addr)
{
	int reg;

	if (CONFIG_HIUSB_EHCI1_IOBASE == host_addr ||
			CONFIG_HIUSB_OHCI1_IOBASE == host_addr) {
		if (atomic_sub_return(1, &dev_open_cnt1) == 0) {

			reg = readl(PERI_CRG102);
			reg |= (USB2_BUS_SRST_REQ1
				| USB2_UTMI0_SRST_REQ1
				| USB2_HST_PHY_SYST_REQ1);
			writel(reg, PERI_CRG102);
			udelay(200);

			reg = readl(PERI_CRG47);
			reg |= (USB2_PHY2_SRST_REQ
				| USB2_PHY2_SRST_TREQ);
			writel(reg, PERI_CRG47);

			udelay(100);
		}
	} else if (CONFIG_HIUSB_EHCI_IOBASE == host_addr ||
			CONFIG_HIUSB_OHCI_IOBASE == host_addr
#ifdef CONFIG_HIUSBUDC_REG_BASE_ADDRESS
			|| CONFIG_HIUSBUDC_REG_BASE_ADDRESS == host_addr
#endif
			) {

		if (atomic_sub_return(1, &dev_open_cnt) == 0) {
			reg = readl(PERI_CRG46);
			reg |= (USB2_BUS_SRST_REQ
				| USB2_UTMI0_SRST_REQ
				| USB2_HST_PHY_SYST_REQ);
			writel(reg, PERI_CRG46);
			udelay(200);

			reg = readl(PERI_CRG47);
			reg |= (USB2_PHY01_SRST_REQ
				| USB2_PHY01_SRST_TREQ0);
			writel(reg, PERI_CRG47);
			udelay(100);
		}
	}
}
