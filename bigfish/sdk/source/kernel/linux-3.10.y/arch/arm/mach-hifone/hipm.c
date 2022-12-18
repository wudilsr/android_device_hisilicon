#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <asm/memory.h>
#include <mach/early-debug.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <linux/syscalls.h>
#include <asm/mach/time.h>
#include <linux/slab.h>
#include <asm/hardware/arm_timer.h>
#include <linux/kmemleak.h>
#include <linux/device.h>
#include <linux/irqchip/arm-gic.h>
#include <mach/sram.h>
#include <mach/hardware.h>

void __iomem *hi_sc_virtbase  = NULL;
void __iomem *hi_crg_virtbase = NULL;
void __iomem *hi_scu_virtbase = NULL;
void __iomem *hi_mcu_virtbase = NULL;
void __iomem *hi_mcu_ctrl_virt     = NULL;
void __iomem *hi_standby_flag_virt = NULL;

/*ddr address for save cpu context*/
extern unsigned int hi_pm_ddrbase;
extern unsigned int hi_pm_phybase;
#define PM_CTX_BUF_SIZE  (1024) /*size of saved context*/

unsigned long saved_interrupt_mask[128];
unsigned long saved_cpu_target_mask[128];
asmlinkage void hi_pm_sleep(void);

extern void __iomem *hifone_gic_cpu_base_addr;
static void __iomem *gic_dist_virt_base_addr = IOMEM(CFG_GIC_DIST_BASE);

#ifdef CONFIG_CA_WARKUP_CHECK
extern unsigned int _ddr_wakeup_check_code_begin;
extern unsigned int _ddr_wakeup_check_code_end;
extern unsigned int hi_sram_virtbase;

unsigned int ddr_wakeup_check_code[] = {
	0xEA000006,0xE59FF034,0xE59FF034,0xE59FF034,0xE59FF034,0xE59FF034,0xE59FF034,0xE59FF034,
	0xE59F0034,0xE1A0D000,0xEE111F10,0xE3C11B06,0xE3C11007,0xEE011F10,0xEB0000FE,0xEAFFFFFE,
	0xEAFFFFFE,0xEAFFFFFE,0xEAFFFFFE,0xEAFFFFFE,0xEAFFFFFE,0xEAFFFFFE,0xEAFFFFFE,0xFFFF0E00,
	0xEB000000,0xEB00001C,0xE28F002C,0xE8900C00,0xE08AA000,0xE08BB000,0xE24A7001,0xE15A000B,
	0x1A000000,0xEB000014,0xE8BA000F,0xE24FE018,0xE3130001,0x1047F003,0xE12FFF13,0x000009F0,
	0x00000A00,0xE3B03000,0xE3B04000,0xE3B05000,0xE3B06000,0xE2522010,0x28A10078,0x8AFFFFFC,
	0xE1B02E82,0x28A10030,0x45813000,0xE12FFF1E,0xF000B51F,0xBD1FECD6,0xBD10B510,0xEB00022F,
	0xE1A01002,0xFAFFFFF9,0xE59FC01C,0xE08CC00F,0xE31C0001,0x128FE00D,0x01A0E00F,0xE12FFF1C,
	0xE28FC001,0xE12FFF1C,0xFC7AF000,0x00000344,0xFAFFFFF0,0xEB000252,0xE92D4FFC,0xE1A03000,
	0xE1A04001,0xE1A07002,0xE1A01004,0xE1A0C004,0xE1A01004,0xE1A0E004,0xE1A01004,0xE1A05004,
	0xE1A01004,0xE1A06004,0xE1A01004,0xE1A08004,0xE1A01004,0xE1A09004,0xE1A01004,0xE58D4004,
	0xE1A01004,0xE58D4000,0xE1A02007,0xE2477001,0xE1A00003,0xE0877003,0xE320F000,0xE1A0A003,
	0xE283B008,0xE88B0360,0xE8835000,0xE59DB004,0xE583B018,0xE59DB000,0xE5A3B01C,0xE2833004,
	0xE1530007,0xCA000000,0xEAFFFFF3,0xE8BD8FFC,0xE1A02000,0xE1A01002,0xEA000000,0xE2811001,
	0xE5D10000,0xE3500000,0x1AFFFFFB,0xE0410002,0xE12FFF1E,0xE92D4070,0xE1A03000,0xE1A04001,
	0xEA000001,0xE4D45001,0xE4C35001,0xE1B05002,0xE2422001,0x1AFFFFFA,0xE8BD8070,0xE92D41F0,
	0xE24DD030,0xE1A04000,0xE3A02030,0xE28F1F5F,0xE1A0000D,0xEB0001C2,0xE1A0000D,0xEBFFFFE3,
	0xE1A05000,0xE1A07004,0xE3A08401,0xE3A06000,0xEA000004,0xE1A02005,0xE1A0100D,0xE1A00006,
	0xEBFFFFE3,0xE0866008,0xE1560007,0x3AFFFFF8,0xE28DD030,0xE8BD81F0,0xE92D4070,0xE3A02000,
	0xE5923000,0xE3A04000,0xE3A05000,0xE59F014C,0xE5900000,0xE3500000,0x0A000002,0xE59F013C,
	0xE5900000,0xE8BD8070,0xE2821401,0xEA00000C,0xE59F012C,0xE5820000,0xE5914000,0xE1A00080,
	0xE5820000,0xE5915000,0xE1540005,0x0A000003,0xE0410002,0xE59F6104,0xE5860000,0xEA000003,
	0xE2811401,0xE2820102,0xE1510000,0x9AFFFFEF,0xE320F000,0xE5823000,0xE59F00E0,0xE5900000,
	0xEAFFFFE7,0xE92D4FF8,0xE59F40D8,0xE5945060,0xE7E20255,0xE280600B,0xE2050007,0xE2807008,
	0xE7E00455,0xE2800001,0xE1A08100,0xE3A0A000,0xE59FB0B4,0xEBFFFFCF,0xE58D0000,0xE3A01000,
	0xE1A00001,0xE59D2000,0xEBFFFF7A,0xE3A00000,0xE1C41000,0xE5810004,0xE3A09801,0xE320F000,
	0xE2490001,0xE1B09000,0x1AFFFFFC,0xE3A00001,0xE59F1070,0xE5810004,0xE8BD8FF8,0xE3A01001,
	0xE59F2060,0xE5821000,0xEA000005,0xE59F1054,0xE5910294,0xE2001001,0xE3510001,0x1A000000,
	0xEA000000,0xEAFFFFF8,0xE320F000,0xE12FFF1E,0x23232323,0x69736968,0x6F63696C,0x6F6C206E,
	0x6F702077,0x20726577,0x65646F6D,0x6D617220,0x756C6620,0x66206873,0x2367616C,0x00232323,
	0xFFFF0A9C,0xA9A9A9A9,0xF8A31000,0x12345678,0xE3A0333E,0xE5932EE0,0xE2423565,0xE2533C02,
	0x1A000008,0xE3500000,0x0A000001,0xE3A03003,0xE5C03000,0xE3510000,0x0A00000D,0xE3A03C02,
	0xE1C130B0,0xEA00000A,0xE59F31F8,0xE1520003,0x1A000007,0xE3500000,0x0A000001,0xE3A03002,
	0xE5C03000,0xE3510000,0x0A000001,0xE3A03C02,0xE1C130B0,0xE12FFF1E,0xE92D4FF0,0xE24DD024,
	0xE3A05001,0xE3A00000,0xE58D0020,0xE3A0A000,0xE1A0100D,0xE28D0004,0xEBFFFFDC,0xE1DD00B0,
	0xE3500C02,0x1A000002,0xE5DD0004,0xE3500003,0x0A000005,0xE1DD00B0,0xE3500C02,0x1A000052,
	0xE5DD0004,0xE3500002,0x1A00004F,0xE59F0178,0xE5906080,0xE7E08256,0xE5906084,0xE7E07C56,
	0xE590612C,0xE206A0FF,0xE3580001,0x1A000004,0xE35A0001,0x1A000002,0xEBFFFF89,0xEBFFFFA6,
	0xEA000048,0xE3570001,0x1A000046,0xE59F013C,0xE590B000,0xE5900004,0xE58D0020,0xE59F0130,
	0xE59000C4,0xE3800010,0xE59F1124,0xE58100C4,0xE3A04FFA,0xE320F000,0xE1B00004,0xE2444001,
	0x1AFFFFFC,0xE59F0108,0xE59000C4,0xE3C00010,0xE59F10FC,0xE58100C4,0xE28D201C,0xE28D1020,
	0xE3A00000,0xEB00003D,0xE3A04000,0xEA000003,0xE1A0000B,0xE59D1020,0xEB000059,0xE2844001,
	0xE1540005,0x3AFFFFF9,0xE59D0020,0xE59D101C,0xEB00007F,0xE28D1008,0xE3A00000,0xEB0000C9,
	0xE59F00AC,0xE59000C4,0xE3800010,0xE59F10A0,0xE58100C4,0xE3A04FFA,0xE320F000,0xE1B00004,
	0xE2444001,0x1AFFFFFC,0xE59F0084,0xE59000C4,0xE3C00010,0xE59F1078,0xE58100C4,0xE3A01000,
	0xE59D0008,0xE5010100,0xE59D000C,0xE50100FC,0xE59D0010,0xE50100F8,0xE59D0014,0xE50100F4,
	0xE59D0018,0xE50100F0,0xEA000006,0xE59F0038,0xE5906084,0xE7E098D6,0xE3590001,0x1A000001,
	0xEBFFFF3F,0xEBFFFF5C,0xE3A00001,0xE59F1024,0xE5810000,0xE59F0020,0xE3A0133E,0xE58100BC,
	0xE320F000,0xEAFFFFFE,0x37160200,0xF8AB0000,0xF840D000,0xF8A22000,0xF840F000,0x80510001,
	0xE92D40F0,0xE5916000,0xE3C66003,0xE5816000,0xE5916000,0xE2866048,0xE3C6303F,0xE5916000,
	0xE206403F,0xE3540038,0x2A000001,0xE2646037,0xEA000000,0xE2646077,0xE5826000,0xE320F000,
	0xE59F62B8,0xE5966008,0xE3160001,0x0AFFFFFB,0xE59F62A8,0xE5863000,0xE3A06000,0xE59F729C,
	0xE5876004,0xE1C76006,0xE596500C,0xE3C55006,0xE1856080,0xE587600C,0xE3A06001,0xE5876010,
	0xE8BD80F0,0xE92D4010,0xE3A02000,0xE59F326C,0xE593300C,0xE3C33001,0xE59F4260,0xE584300C,
	0xE320F000,0xE59F3254,0xE5933008,0xE3130008,0x0AFFFFFB,0xE59F3244,0xE5830014,0xE5831018,
	0xE0822001,0xE320F000,0xE59F3230,0xE5933020,0xE1530002,0x1AFFFFFB,0xE8BD8010,0xE92D4070,
	0xE1A02000,0xE59F5214,0xE595500C,0xE3855001,0xE59F6208,0xE586500C,0xE1A01121,0xE3A03000,
	0xEA000008,0xE7924103,0xE320F000,0xE59F51EC,0xE5955008,0xE3150008,0x0AFFFFFB,0xE59F51DC,
	0xE585401C,0xE2833001,0xE1530001,0x3AFFFFF4,0xE8BD8070,0xE92D403C,0xE1A0500D,0xE3A02000,
	0xE1A03002,0xE885000C,0xE320F000,0xE59F31AC,0xE5933008,0xE3130008,0x0AFFFFFB,0xE59F319C,
	0xE593300C,0xE3833001,0xE59F5190,0xE585300C,0xE3A04000,0xEA000005,0xE1A03180,0xE2645007,
	0xE1A05185,0xE1A03533,0xE7CD3004,0xE2844001,0xE3540008,0x3AFFFFF7,0xE320F000,0xE59F315C,
	0xE5933008,0xE3130008,0x0AFFFFFB,0xE3A02080,0xE59F3148,0xE583201C,0xE3A04003,0xEA000008,
	0xE320F000,0xE59F3134,0xE5933008,0xE3130008,0x0AFFFFFB,0xE3A03000,0xE59F5120,0xE585301C,
	0xE2844004,0xE1540001,0x3AFFFFF4,0xE320F000,0xE59F3108,0xE5933008,0xE3130008,0x0AFFFFFB,
	0xE5DD3003,0xE1A03C03,0xE5DD5002,0xE1833805,0xE5DD5001,0xE1833405,0xE5DD5000,0xE1832005,
	0xE59F30D8,0xE583201C,0xE320F000,0xE59F30CC,0xE5933008,0xE3130008,0x0AFFFFFB,0xE5DD3007,
	0xE1A03C03,0xE5DD5006,0xE1833805,0xE5DD5005,0xE1833405,0xE5DD5004,0xE1832005,0xE59F309C,
	0xE583201C,0xE8BD803C,0xE92D4070,0xE3500000,0x1A000001,0xE3A05014,0xEA000000,0xE3A05020,
	0xE1A04005,0xE320F000,0xE59F5070,0xE5955008,0xE3150001,0x0AFFFFFB,0xE59F5060,0xE5955008,
	0xE31500F0,0x0A000002,0xE3A050EE,0xE5C15000,0xE8BD8070,0xE3A03000,0xEA00000D,0xE28354FA,
	0xE245585F,0xE5952030,0xE7C12003,0xE7E75452,0xE2836001,0xE7C15006,0xE7E75852,0xE2836002,
	0xE7C15006,0xE1A05C22,0xE2836003,0xE7C15006,0xE2833004,0xE1530004,0x3AFFFFEF,0xEAFFFFEB,
	0xF9A10000,0xE92D41F0,0xE2522020,0x3A00000B,0xE3520080,0x3A000005,0xF5D1F080,0xE8B151F8,
	0xE2422020,0xE3520080,0xE8A051F8,0x2AFFFFF9,0xE8B151F8,0xE2522020,0xE8A051F8,0x2AFFFFFB,
	0xE1B0CE02,0x28B15018,0x28A05018,0x48B10018,0x48A00018,0xE8BD41F0,0xE1B0CF02,0x24913004,
	0x24803004,0x012FFF1E,0xE1B02F82,0x20D130B2,0x44D12001,0x20C030B2,0x44C02001,0xE12FFF1E,
	0xE1A0500E,0xEB00002B,0xE1A0E005,0xE1B05000,0xE1A0100D,0xE1A0300A,0xE3C00007,0xE1A0D000,
	0xE28DD060,0xE92D4020,0xEB00000F,0xE8BD4020,0xE3A06000,0xE3A07000,0xE3A08000,0xE3A0B000,
	0xE3C11007,0xE1A0C005,0xE8AC09C0,0xE8AC09C0,0xE8AC09C0,0xE8AC09C0,0xE1A0D001,0xE12FFF1E,
	0xF3AF0004,0x00208000,0xEB82F7FF,0xE92D4000,0xE3A00016,0xE24DD014,0xE1A0100D,0xE28D2004,
	0xE5812000,0xEF123456,0xE59D0004,0xE3500000,0x059F001C,0x02800007,0x03C00007,0xE59D100C,
	0xE59D2008,0xE59D3010,0xE28DD014,0xE8BD8000,0x0000002C,0xFFFF0B00,0xE59F0000,0xE12FFF1E,
	0xFFFF0AA0,0xE59F100C,0xE3A00018,0xEF123456,0xE12FFF1E,0x00000008,0x00020026,0xE12FFF1E,
	0xE3A00403,0xEEE10A10,0xE12FFF1E,0xFFFF0AA0,0xFFFF0AA0,0x00000060,0xFFFF00A4,0x00000000,
};
#endif /* CONFIG_CA_WARKUP_CHECK */

static int hi_pm_save_gic(void)
{
	unsigned int max_irq, i;
	unsigned int intack;

	/* disable gic dist */
	writel(0, gic_dist_virt_base_addr + GIC_DIST_CTRL);

	/*
	 * Find out how many interrupts are supported.
	 */
	max_irq = readl(gic_dist_virt_base_addr + GIC_DIST_CTR) & 0x1f;
	max_irq = (max_irq + 1) * 32;

	/*
	 * The GIC only supports up to 1020 interrupt sources.
	 * Limit this to either the architected maximum, or the
	 * platform maximum.
	 */
	max_irq = max_t(unsigned int, max_irq, max(1020, NR_IRQS));

	/* save Dist target */
	for (i = 32; i < max_irq; i += 4) {
		saved_cpu_target_mask[i / 4] =
		    readl(gic_dist_virt_base_addr + GIC_DIST_TARGET + i * 4 / 4);
	}

	/* save mask irq */
	for (i = 0; i < max_irq; i += 32) {
		saved_interrupt_mask[i / 32] =
		    readl(gic_dist_virt_base_addr + GIC_DIST_ENABLE_SET +
			  i * 4 / 32);
	}

	/* clear all interrupt */
	for (i = 0; i < max_irq; i += 32) {
		writel(0xffffffff,
		       gic_dist_virt_base_addr + GIC_DIST_ENABLE_CLEAR + i * 4 / 32);
	}

	/* read INT_ACK in CPU interface, until result is 1023 */
	for (i = 0; i < max_irq; i++) {
		intack = readl(hifone_gic_cpu_base_addr + 0x0c);
		if (1023 == intack) {
			break;
		}
		writel(intack, hifone_gic_cpu_base_addr + 0x10);
	}

#if 0   /* comment off wakeup intr, cause we will go directly to deepsleep */
	/* enable softinterrupt mask */
	writel(0xffff, gic_dist_virt_base_addr + GIC_DIST_ENABLE_SET);

	/* enable KPC/TBC/RTC interrupt */
	writel(GET_IRQ_BIT(IRQ_KPC) | GET_IRQ_BIT(IRQ_TBC) |
	       GET_IRQ_BIT(IRQ_RTC),
	       gic_dist_virt_base_addr + GIC_DIST_ENABLE_SET + 4);

	writel(0, gic_dist_virt_base_addr + GIC_DIST_ENABLE_SET + 8);

	/* enable all gpio interrupt */
	writel(0x3fffff, gic_dist_virt_base_addr + GIC_DIST_ENABLE_SET + 0xc);
#endif

	return 0;
}

static int hi_pm_retore_gic(void)
{
	unsigned int max_irq, i;

	/* PRINT OUT the GIC Status */
	unsigned int irq_status[5];

	for (i = 0; i < 5; i++) {
		irq_status[i] = readl(gic_dist_virt_base_addr + 0xd00 + i * 4);
	}

	writel(0, gic_dist_virt_base_addr + GIC_DIST_CTRL);
	writel(0, hifone_gic_cpu_base_addr + GIC_CPU_CTRL);

	/*
	 * Find out how many interrupts are supported.
	 */
	max_irq = readl(gic_dist_virt_base_addr + GIC_DIST_CTR) & 0x1f;
	max_irq = (max_irq + 1) * 32;

	/*
	 * The GIC only supports up to 1020 interrupt sources.
	 * Limit this to either the architected maximum, or the
	 * platform maximum.
	 */
	max_irq = max_t(unsigned int, max_irq, max(1020, NR_IRQS));

	/*
	 * Set all global interrupts to be level triggered, active low.
	 */
	for (i = 32; i < max_irq; i += 16) {
		writel(0, gic_dist_virt_base_addr + GIC_DIST_CONFIG + i * 4 / 16);
	}

	/*
	 * Set all global interrupts to this CPU only.
	 */
	for (i = 32; i < max_irq; i += 4) {
		writel(saved_cpu_target_mask[i / 4],
		       gic_dist_virt_base_addr + GIC_DIST_TARGET + i * 4 / 4);
	}

	/*
	 * Set priority on all interrupts.
	 */
	for (i = 0; i < max_irq; i += 4) {
		writel(0xa0a0a0a0,
		       gic_dist_virt_base_addr + GIC_DIST_PRI + i * 4 / 4);
	}

	/*
	 * Disable all interrupts.
	 */
	for (i = 0; i < max_irq; i += 32) {
		writel(0xffffffff,
		       gic_dist_virt_base_addr + GIC_DIST_ENABLE_CLEAR + i * 4 / 32);
	}

	for (i = 0; i < max_irq; i += 32) {
		writel(saved_interrupt_mask[i / 32], gic_dist_virt_base_addr +
		       GIC_DIST_ENABLE_SET + i * 4 / 32);
	}

	writel(1, gic_dist_virt_base_addr + GIC_DIST_CTRL);

	/* set the BASE priority 0xf0 */
	writel(0xf0, hifone_gic_cpu_base_addr + GIC_CPU_PRIMASK);

	writel(1, hifone_gic_cpu_base_addr + GIC_CPU_CTRL);

	return 0;
}
/*****************************************************************************/

static int hi_pm_suspend(void)
{
	/* int ret = 0; */
	unsigned long flage = 0;

	/* disable irq */
	local_irq_save(flage);

	/* save gic */
	hi_pm_save_gic();

	/*save & disable l2 cache */
#ifdef CONFIG_CACHE_L2X0
	hi_pm_disable_l2cache();
#endif

	sram_suspend();

	hi_pm_sleep();

	sram_resume();

	/*restore & enable l2 cache */
#ifdef CONFIG_CACHE_L2X0
	hi_pm_enable_l2cache();
#endif

	/* restore gic */
	hi_pm_retore_gic();

	/* enable irq */
	local_irq_restore(flage);

	return 0;
}

#ifdef CONFIG_PM_HIBERNATE
void hi_pm_hibernate_suspend (void)
{
	/* save gic */
	hi_pm_save_gic();

	/*save & disable l2 cache */
#ifdef CONFIG_CACHE_L2X0
	hi_pm_disable_l2cache();
#endif

	sram_suspend();


}

void hi_pm_hibernate_resume (void)
{
	sram_resume();

	/*restore & enable l2 cache */
#ifdef CONFIG_CACHE_L2X0
	hi_pm_enable_l2cache();
#endif

	/* restore gic */
	hi_pm_retore_gic();
   
}

#endif


static int hi_pm_enter(suspend_state_t state)
{
	int ret = 0;
	switch (state) {
	case PM_SUSPEND_STANDBY:
	case PM_SUSPEND_MEM:
		ret = hi_pm_suspend();
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

int hi_pm_valid(suspend_state_t state)
{
	return 1;
}

static const struct platform_suspend_ops hi_pm_ops = {
	.enter = hi_pm_enter,
	.valid = hi_pm_valid,
};
/*****************************************************************************/

static int __init hi_pm_init(void)
{
	hi_sc_virtbase = (void __iomem *)IO_ADDRESS(REG_BASE_SCTL);
	hi_crg_virtbase = (void __iomem *)IO_ADDRESS(REG_BASE_CRG);
	hi_mcu_virtbase = (void __iomem *)ioremap_nocache(REG_BASE_MCU, 0x10000);
	hi_mcu_ctrl_virt = hi_mcu_virtbase + 0xF000;
	hi_standby_flag_virt = hi_mcu_virtbase + 0x7520;

	hi_pm_ddrbase =
	    (unsigned int)kzalloc((PM_CTX_BUF_SIZE), GFP_DMA | GFP_KERNEL);
	hi_pm_phybase = __pa(hi_pm_ddrbase);
	/*
	 * Because hi_pm_ddrbase is saved in .text of hi_pm_sleep.S, the kmemleak,
	 * which not check the .text, reports a mem leak here ,
	 * so we suppress kmemleak messages.
	 */
	kmemleak_not_leak((void *)hi_pm_ddrbase);

	suspend_set_ops(&hi_pm_ops);

#ifdef CONFIG_CA_WARKUP_CHECK
	hi_sram_virtbase = (unsigned int)ioremap_nocache(SRAM_BASE_ADDRESS, sizeof(ddr_wakeup_check_code));
	_ddr_wakeup_check_code_begin =
	    (unsigned int)kzalloc(sizeof(ddr_wakeup_check_code), GFP_DMA | GFP_KERNEL);
	/*
	 * Because _ddr_wakeup_check_code_begin is saved in .text of hi_pm_sleep.S, the kmemleak,
	 * which not check the .text, reports a mem leak here ,
	 * so we suppress kmemleak messages.
	 */
	kmemleak_not_leak((void *)_ddr_wakeup_check_code_begin);
	
	memcpy((void*)_ddr_wakeup_check_code_begin, ddr_wakeup_check_code, sizeof(ddr_wakeup_check_code));
	_ddr_wakeup_check_code_end = _ddr_wakeup_check_code_begin + sizeof(ddr_wakeup_check_code);	
#endif	/* CONFIG_CA_WARKUP_CHECK */
	return 0;
}

module_init(hi_pm_init);
