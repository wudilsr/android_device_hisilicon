/*
 * hisilicon Management Routines
 *
 * Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
 */

#ifndef __ARCH_ARM_MACH_HI_DVFS_H
#define __ARCH_ARM_MACH_HI_DVFS_H

#ifndef PMC_BASE
#define PMC_BASE    IO_ADDRESS(0xF8A23000)
#endif

#define PERI_PMC6   (PMC_BASE + 0x18)
#define PERI_PMC7   (PMC_BASE + 0x1C)
#define PERI_PMC8   (PMC_BASE + 0x20)
#define PERI_PMC9   (PMC_BASE + 0x24)
#define PERI_PMC10  (PMC_BASE + 0x28)
#define PERI_PMC12  (PMC_BASE + 0x30)

#define PERI_PMC22  (PMC_BASE + 0x58)
#define PERI_PMC23  (PMC_BASE + 0x5c)
#define PERI_PMC24  (PMC_BASE + 0x60)
#define PERI_PMC25  (PMC_BASE + 0x64)
#define PERI_PMC26  (PMC_BASE + 0x68)
#define PERI_PMC29  (PMC_BASE + 0x74)
#define PERI_PMC31  (PMC_BASE + 0x7c)
#define PERI_PMC32  (PMC_BASE + 0x80)
#define PERI_PMC30  (PMC_BASE + 0x78)
#define PERI_PMC33  (PMC_BASE + 0x84)

#define PWM_DUTY_MASK 0xffff0000
#define PWM_PERIOD_MASK 0xffff
#define PWM_CPU_ENABLE_BIT 0x0
#define PWM_CORE_ENABLE_BIT 0x2
#define HPM_PC_RECORED_MASK 0x3ff

int hi_device_scale(struct device *target_dev,unsigned long old_freq,unsigned long new_freq);
void do_avs(void);

#endif
