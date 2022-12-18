#ifndef __TIMER_PLAT_H__
#define __TIMER_PLAT_H__

//#define TIMER_COUNT_MAX	    0xFFFFFFFF

#define TIMER01_BASE     0xF8008000  //time01 for secure os   (timer1 0xF8008020 can not write )
#define TIMER23_BASE     0xF8009000  //timer23 for secure os(Do not power off)

#define TIMER01_IRQ      (60)
#define TIMER23_IRQ      (52)

#define TIMER_CLK_RATE  (24 * 1000 * 1000)  /* 24MHZ */

#define FREE_RUNNING_TIMER_BASE     TIMER01_BASE
#define TICK_TIMER_BASE             TIMER23_BASE

#define FREE_RUNNING_TIMER_NUM    (0)
#define TICK_TIMER_NUM (0)


#define FREE_RUNNING_FIQ_NUMBLER     TIMER01_IRQ
#define TICK_TIMER_FIQ_NUMBLER       TIMER23_IRQ


/*NMI watchdog*/
#define WDT_FIQ_NUMBLER    84 /* TODO */
//Secure RTC1
#define SECURE_RTC_FIQ_NUMBLER    87 /* TODO */
//NMI watchdog
#define SGI_DUMP_NUMBLER   0xB /* TODO */

//SPI number to call normal world tc_notify_func
#define SPI_NUM_FOR_NOTIFY  (75)   /* TODO: 43 + 32 */

#if 1
/*For K3V3 FPGA*/
#define TIMER_SECU_EN          (1<<16)  /* TODO: not support set timer sec */
#endif

/*Timer01、Timer23、Timer45、Timer67使能端强制拉高的硬件使能配置。*/
//#define TIME_FORCE_HIGH        (1<<8)

#if 0
#define SCCTRL_TIMEREN0SEL_TIMCLK   (1 << 15)
#define SCCTRL_TIMEREN1SEL_TIMCLK   (1 << 17)
#define SCCTRL_TIMEREN2SEL_TIMCLK   (1 << 19)
#define SCCTRL_TIMEREN3SEL_TIMCLK   (1 << 21)
#define SCCTRL_TIMEREN4SEL_TIMCLK   (1 << 0)
#define SCCTRL_TIMEREN5SEL_TIMCLK   (1 << 2)
#define SCCTRL_TIMEREN6SEL_TIMCLK   (1 << 4)
#define SCCTRL_TIMEREN7SEL_TIMCLK   (1 << 6)
#define PTCRL_TIMEEREN8SEL_TIMCLK   (1 << 0)
#define PTCRL_TIMEEREN9SEL_TIMCLK   (1 << 2)
#define PTCRL_TIMEEREN10SEL_TIMCLK   (1 << 4)
#define PTCRL_TIMEEREN11SEL_TIMCLK   (1 << 6)
#define PTCRL_TIMEEREN12SEL_TIMCLK   (1 << 8)
#define PTCRL_TIMEEREN13SEL_TIMCLK   (1 << 10)
#define PTCRL_TIMEEREN14SEL_TIMCLK   (1 << 12)
#define PTCRL_TIMEEREN15SEL_TIMCLK   (1 << 14)
#endif

#define TIMER_LOAD      0x00
#define TIMER_VALUE     0x04
#define TIMER_CTRL      0x08

#define TIMER_LOAD_HIGH      0x20
#define TIMER_VALUE_HIGH     0x24
#define TIMER_BGLOAD_HIGH    0x38

#define TIMER_CTRL_ONESHOT  (1 << 0)
#define TIMER_CTRL_32BIT    (0 << 1)   /*[1] 0:32bit 1:64bit */
#define TIMER_CTRL_DIV1     (0 << 2)
#define TIMER_CTRL_DIV16    (1 << 2)
#define TIMER_CTRL_DIV256   (2 << 2)
#define TIMER_CTRL_IE       (1 << 5)    /* Interrupt Enable (versatile only) */
#define TIMER_CTRL_PERIODIC (1 << 6)
#define TIMER_CTRL_ENABLE   (1 << 7)

#define TIMER_GT_CLK_TIMER1  (1 << 3)
#define TIMER_GT_PCLK_TIMER1 (1 << 2)
//#define TIMER_GT_CLK_TIMER6  (1 << 3)
#define TIMER_GT_PCLK_TIMER6 (1 << 24)


#define TIMER_INTCLR        0x0c
#define TIMER_RIS       0x10
#define TIMER_MIS       0x14
#define TIMER_BGLOAD        0x18

#endif /* __TIMER_PLAT_H__ */

