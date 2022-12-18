/*
 * OpenVirtualization:
 * For additional details and support contact developer@sierraware.com.
 * Additional documentation can be found at www.openvirtualization.org
 *
 * Copyright (C) 2011 SierraWare
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * secure timer declarations.
 */

#ifndef __SECURE_TIMER_H__
#define __SECURE_TIMER_H__

#include "sre_base.h"
#include "sre_board.h"
#include "sre_ticktimer.h"

#ifdef OS_STB_HiS40V200
#define FREE_RUNNING_FIQ_NUMBLER         60
#define TICK_TIMER_FIQ_NUMBLER               60

#define CLOCK_RATE       (24*1000*1000)

/*for map, if use 0xF8002000 abort*/
//#define TIMER0_BASE     0xFC800000
#define TIMER0_BASE     0xF8002000
#define TIMER1_BASE     0xF8A29000
#define TIMER2_BASE     0xF8A29000
#define TIMER3_BASE     0xF8A2A000
#define TIMER4_BASE     0xF8A81000
#else
#define FREE_RUNNING_FIQ_NUMBLER     34
#define TICK_TIMER_FIQ_NUMBLER          35

#define CLOCK_RATE       32768

#define TIMER0_BASE     0xFC800000
#define TIMER1_BASE     0xFC801000
#define TIMER2_BASE     0xFCA01000
#define TIMER3_BASE     0xFCA02000
#define TIMER4_BASE     0xFCA03000
#endif

#define TIMER_COUNT_MAX	    0xFFFFFFFF

#define SCCTRL_TIMEREN0SEL_TIMCLK   (1 << 15)
#define SCCTRL_TIMEREN1SEL_TIMCLK   (1 << 17)
#define SCCTRL_TIMEREN2SEL_TIMCLK   (1 << 19)
#define SCCTRL_TIMEREN3SEL_TIMCLK   (1 << 21)
#define SCCTRL_TIMEREN4SEL_TIMCLK   (1 << 0)
#define SCCTRL_TIMEREN5SEL_TIMCLK   (1 << 2)
#define SCCTRL_TIMEREN6SEL_TIMCLK   (1 << 4)
#define SCCTRL_TIMEREN7SEL_TIMCLK   (1 << 6)
#define SCCTRL_TIMEREN8SEL_TIMCLK   (1 << 8)
#define SCCTRL_TIMEREN9SEL_TIMCLK   (1 << 10)

#ifdef OS_STB_HiS40V200
#define FREE_RUNNING_TIMER_BASE     TIMER4_BASE
#define TICK_TIMER_BASE                      TIMER4_BASE
#else
#define FREE_RUNNING_TIMER_BASE     TIMER1_BASE
#define TICK_TIMER_BASE                      TIMER1_BASE
#endif

#define TIMER_LOAD      0x00
#define TIMER_VALUE     0x04
#define TIMER_CTRL      0x08
#define TIMER_CTRL_ONESHOT  (1 << 0)
#define TIMER_CTRL_32BIT    (1 << 1)
#define TIMER_CTRL_DIV1     (0 << 2)
#define TIMER_CTRL_DIV16    (1 << 2)
#define TIMER_CTRL_DIV256   (2 << 2)
#define TIMER_CTRL_IE       (1 << 5)    /* Interrupt Enable (versatile only) */
#define TIMER_CTRL_PERIODIC (1 << 6)
#define TIMER_CTRL_ENABLE   (1 << 7)

#define TIMER_GT_CLK_TIMER1  (1 << 3)
#define TIMER_GT_PCLK_TIMER1 (1 << 2)

#define TIMER_INTCLR        0x0c
#define TIMER_RIS       0x10
#define TIMER_MIS       0x14
#define TIMER_BGLOAD        0x18

/**
* @brief
*/
enum timer_mode{
    MODE_FREE_RUNNING,
    MODE_PERIODIC,
    MODE_ONESHOT
};

VOID SRE_TimerInit(VOID);
VOID SRE_TimerInitForSR(VOID);
UINT32 SRE_ReadFreeRunningCntr(VOID);
VOID SRE_TriggerTick(UINT64 usecs);
VOID SRE_Clockcycles2timeval(UINT32 clockcycles, INT32 *pSec, INT32 *pNsec);
VOID SRE_SecureTimerInit(UINT32 timer_base, UINT8 timer_module_index);
VOID SRE_SecureTimerClearirq(UINT32 timer_base, UINT32 timer_module_index);
VOID SRE_SecureTimerDisable(UINT32 timer_base, UINT32 timer_module_index);
VOID SRE_SecurePeripTimerEnable(VOID);
VOID SRE_SecureTimerEnable(UINT32 timer_base, UINT32 timer_module_index);
UINT32 SRE_SecureTimerReadMis(UINT32 timer_base, UINT32 tim_mod_index);
UINT32 SRE_SecureTimerReadRis(UINT32 timer_base, UINT32 tim_mod_index);
VOID SRE_SecureSetTimer(UINT32 timer_base, UINT32 tim_mod_index, UINT32 mode, UINT32 usecs);
UINT32 SRE_SecureReadTimer(UINT32 timer_base, UINT32 tim_mod_index);
VOID SRE_FreeRunningfiqhandler(UINT32 uwHwiNum);
VOID SRE_OneShotfiqhandler(UINT32 uwHwiNum);
UINT64 SRE_Timeval2clockcycles(timeval_t *time);
VOID SRE_EnableTimer(VOID);

#endif /* __VE_RS1_TIMER_H__ */

