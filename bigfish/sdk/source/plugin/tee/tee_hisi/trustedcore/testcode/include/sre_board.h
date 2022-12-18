
#ifndef __SRE_BOARD_H__
#define __SRE_BOARD_H__

/*GIC address*/
#ifdef OS_STB_HiS40V200
#define GIC_IC_PHY_BASE (0xF8A02000)
#define GIC_ID_PHY_BASE (0xF8A01000)
#else
#define GIC_IC_PHY_BASE (0xFC000100)
#define GIC_ID_PHY_BASE (0xFC001000)
#endif

#define REG_BASE_SCTRL                  (0xFC802000)//SCTRL

#define write32(addr, val) (*(volatile unsigned int *)  (addr) = (val))
#define  read32(addr)      (*(volatile unsigned int *)  (addr))
#define write16(addr, val) (*(volatile unsigned short *)(addr) = (val))
#define  read16(addr)      (*(volatile unsigned short *)(addr))

 /* Distributor interface r,egisters */
#define GICD_CTL                     0x0
#define GICD_CTR                     0x4
#define GICD_SEC_BASE               0x80
#define GICD_SGI_SEC_BANK           0x80
#define GICD_PPI_SEC_BANK           0x82
#define GICD_SPI_SEC                0x84 //~0xFC
#define GICD_ENABLESET              0x100
#define GICD_PPI_ENABLESET         0x102
#define GICD_SPI_ENABLESET         0x104 //~0x17C
#define GICD_ENABLECLEAR            0x180
#define GICD_PENDINGSET             0x200
#define GICD_PENDINGCLEAR           0x280
#define GICD_ACTIVESET              0x300
#define GICD_ACTIVECLEAR            0x380
#define GICD_SGI_PRI               0x400
#define GICD_PPI_PRI               0x410
#define GICD_SPI_PRI               0x420 //~0x7FB
#define GICD_CPUS                   0x800
#define GICD_CONFIG                 0xC00
#define GICD_SPI_CONFIG            0xC08
#define GICD_SW                     0xF00
#define GICD_CPENDSGIR              0xF10
#define GICD_SPENDSGIR              0xF20

/* Physical CPU Interface registers */
#define GICC_CTL                     0x0
#define GICC_PRIMASK                 0x4
#define GICC_BP                      0x8
#define GICC_INTACK                  0xC
#define GICC_EOI                    0x10
#define GICC_RUNNINGPRI             0x14
#define GICC_HIGHESTPEND            0x18
#define GICC_DEACTIVATE             0x1000

#define SCCTRL	                 (REG_BASE_SCTRL + 0x000)
#define SCSYSSTAT	           (REG_BASE_SCTRL + 0x004)
#define SCITMCTRL	           (REG_BASE_SCTRL + 0x008)
#define SCIMSTAT	                 (REG_BASE_SCTRL + 0x00C)
#define SCXTALCTRL	           (REG_BASE_SCTRL + 0x010)
#define SCPLLSTAT	           (REG_BASE_SCTRL + 0x014)
#define SCPERTIMCTRL	     (REG_BASE_SCTRL + 0x018)
#define SCPEREN0	           (REG_BASE_SCTRL + 0x020)
#define SCPERDIS0	           (REG_BASE_SCTRL + 0x024)
#define SCPERCLKEN0	           (REG_BASE_SCTRL + 0x028)
#define SCPERSTAT0	           (REG_BASE_SCTRL + 0x02C)
#define SCPEREN1	           (REG_BASE_SCTRL + 0x030)
#define SCPERDIS1	           (REG_BASE_SCTRL + 0x034)
#define SCPERCLKEN1	           (REG_BASE_SCTRL + 0x038)
#define SCPERSTAT1             (REG_BASE_SCTRL + 0x03C)
#define SCPEREN2	           (REG_BASE_SCTRL + 0x040)
#define SCPERDIS2              (REG_BASE_SCTRL + 0x044)
#define SCPERCLKEN2            (REG_BASE_SCTRL + 0x048)
#define SCPERSTAT2             (REG_BASE_SCTRL + 0x04C)
#define SCPEREN3               (REG_BASE_SCTRL + 0x050)
#define SCPERDIS3              (REG_BASE_SCTRL + 0x054)
#define SCPERCLKEN3            (REG_BASE_SCTRL + 0x058)
#define SCPERSTAT3             (REG_BASE_SCTRL + 0x05C)
#define SCPEREN4               (REG_BASE_SCTRL + 0x060)
#define SCPERDIS4              (REG_BASE_SCTRL + 0x064)
#define SCPERCLKEN4            (REG_BASE_SCTRL + 0x068)
#define SCPERSTAT4             (REG_BASE_SCTRL + 0x06C)
#define SCPERRSTEN0	           (REG_BASE_SCTRL + 0x080)
#define SCPERRSTDIS0           (REG_BASE_SCTRL + 0x084)
#define SCPERRSTSTAT0          (REG_BASE_SCTRL + 0x088)
#define SCPERRSTEN1            (REG_BASE_SCTRL + 0x08C)
#define SCPERRSTDIS1	       (REG_BASE_SCTRL + 0x090)
#define SCPERRSTSTAT1	       (REG_BASE_SCTRL + 0x094)
#define SCPERRSTEN2	           (REG_BASE_SCTRL + 0x098)
#define SCPERRSTDIS2           (REG_BASE_SCTRL + 0x09C)

#define SCPERRSTSTAT2          (REG_BASE_SCTRL + 0x0A0)
#define SCPERRSTEN3            (REG_BASE_SCTRL + 0x0A4)
#define SCPERRSTDIS3           (REG_BASE_SCTRL + 0x0A8)
#define SCPERRSTSTAT3          (REG_BASE_SCTRL + 0x0AC)
#define SCPERRSTEN4            (REG_BASE_SCTRL + 0x0B0)
#define SCPERRSTDIS4           (REG_BASE_SCTRL + 0x0B4)
#define SCPERRSTSTAT4          (REG_BASE_SCTRL + 0x0B8)
#define SCISOEN                (REG_BASE_SCTRL + 0x0C0)
#define SCISODIS               (REG_BASE_SCTRL + 0x0C4)
#define SCISOSTAT              (REG_BASE_SCTRL + 0x0C8)
#define SCPERPWREN             (REG_BASE_SCTRL + 0x0D0)
#define SCPERPWRDIS            (REG_BASE_SCTRL + 0x0D4)
#define SCPERPWRSTAT           (REG_BASE_SCTRL + 0x0D8)
#define SCPERPWRACK            (REG_BASE_SCTRL + 0x0DC)
#define SCPERPWRDOWNTIME       (REG_BASE_SCTRL + 0x0E0)
#define SCCPUPWRDOWNTIME       (REG_BASE_SCTRL + 0x0E4)
#define SCPERPWRUPTIME         (REG_BASE_SCTRL + 0x0E8)
#define SCCPUPWRUPTIME         (REG_BASE_SCTRL + 0x0EC)
#define SCG3DLPCTRL            (REG_BASE_SCTRL + 0x0F0)
#define SCCPUCOREEN            (REG_BASE_SCTRL + 0x0F4)
#define SCCPUCOREDIS           (REG_BASE_SCTRL + 0x0F8)
#define SCCPUCORESTAT          (REG_BASE_SCTRL + 0x0FC)
#define SCCLKDIV0              (REG_BASE_SCTRL + 0x100)
#define SCCLKDIV1              (REG_BASE_SCTRL + 0x104)
#define SCCLKDIV2              (REG_BASE_SCTRL + 0x108)
#define SCCLKDIV3              (REG_BASE_SCTRL + 0x10C)
#define SCCLKDIV4              (REG_BASE_SCTRL + 0x110)
#define SCCLKDIV5              (REG_BASE_SCTRL + 0x114)
#define SCCLKDIV6              (REG_BASE_SCTRL + 0x118)
#define SCCLKDIV7              (REG_BASE_SCTRL + 0x11C)
#define SCCLKDIV8              (REG_BASE_SCTRL + 0x120)
#define SCCLKDIV9              (REG_BASE_SCTRL + 0x124)
#define SCCLKDIV10             (REG_BASE_SCTRL + 0x128)
#define SCCLKDIV11             (REG_BASE_SCTRL + 0x12C)
#define SCCLKDIV12             (REG_BASE_SCTRL + 0x130)
#define SCCLKDIV13             (REG_BASE_SCTRL + 0x134)
#define SCCLKDIV14             (REG_BASE_SCTRL + 0x138)
#define SCCLKDIV15             (REG_BASE_SCTRL + 0x13C)
#define SCCLKDIV16             (REG_BASE_SCTRL + 0x140)
#define SCCLKDIV17             (REG_BASE_SCTRL + 0x144)
#define SCCLKDIV18             (REG_BASE_SCTRL + 0x148)
#define SCCLKDIV19             (REG_BASE_SCTRL + 0x14C)
#define SCPERCTRL0             (REG_BASE_SCTRL + 0x200)
#define SCPERCTRL1             (REG_BASE_SCTRL + 0x204)
#define SCPERCTRL2             (REG_BASE_SCTRL + 0x208)
#define SCPERCTRL3             (REG_BASE_SCTRL + 0x20C)
#define SCPERCTRL4             (REG_BASE_SCTRL + 0x210)
#define SCPERCTRL5             (REG_BASE_SCTRL + 0x214)
#define SCPERCTRL6             (REG_BASE_SCTRL + 0x218)
#define SCDEEPSLEEPED          (REG_BASE_SCTRL + 0x300)
#define SCINNERRSTAT           (REG_BASE_SCTRL + 0x304)
#define SCSWADDR               (REG_BASE_SCTRL + 0x308)
#define SCDDRADDR              (REG_BASE_SCTRL + 0x30C)
#define SCDDRDATA              (REG_BASE_SCTRL + 0x310)
#define SCBAKDATA0             (REG_BASE_SCTRL + 0x314)
#define SCBAKDATA1             (REG_BASE_SCTRL + 0x318)
#define SCBAKDATA2             (REG_BASE_SCTRL + 0x31C)
#define SCBAKDATA3             (REG_BASE_SCTRL + 0x320)
#define SCBAKDATA4             (REG_BASE_SCTRL + 0x324)
#define SCBAKDATA5             (REG_BASE_SCTRL + 0x328)
#define SCBAKDATA6             (REG_BASE_SCTRL + 0x32C)
#define SCBAKDATA7             (REG_BASE_SCTRL + 0x330)
#define SCCPUCFG               (REG_BASE_SCTRL + 0x400)
#define SCCPUCLKOFF            (REG_BASE_SCTRL + 0x404)
#define SCCPUCLKGATE           (REG_BASE_SCTRL + 0x408)
#define SCCPUSTAT              (REG_BASE_SCTRL + 0x40C)
#define SCCPURSTEN             (REG_BASE_SCTRL + 0x410)
#define SCCPURSTDIS            (REG_BASE_SCTRL + 0x414)
#define SCCPURSTSTAT           (REG_BASE_SCTRL + 0x418)
#define SCSOCID0               (REG_BASE_SCTRL + 0xE00)











#endif /* __SRE_BOARD_H__ */
