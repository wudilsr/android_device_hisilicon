/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : monitor.h
* Description : for monitor code, and suspend_task
* Platform    :
* Author      :
* Version     : 1.0
* Date        :
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date         Author          Modifications
    2012-08-15   z00206978       create
    2013-02-19   l00209118       modify
*******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
*******************************************************************************/
#ifndef SECUREINIT_H
#define SECUREINIT_H

#define HISI_TZPC     0xFCA00000
#define SECRAMCFG     0xFCA00000
#define DECPORT0STAT  0xFCA00800
#define DECPORT0SET   0xFCA00804
#define DECPORT0CLR   0xFCA00808
#define DECPORT1STAT  0xFCA0080C
#define DECPORT1SET   0xFCA00810
#define DECPORT1CLR   0xFCA00814
#define DECPORT2STAT  0xFCA00818
#define DECPORT2SET   0xFCA0081C
#define DECPORT2CLR   0xFCA00820

#define ALL_SECURE    0x00000000
#define ALL_UNSECURE  0xFFFFFFFF


#define UART_SECURE   0x1f0000
#define UART_UNSECURE 0x0

#define write32(addr, val) (*(volatile unsigned int *)(addr) = (val))
#define read32(addr) (*(volatile unsigned int *)(addr))
/*GIC address*/
#ifdef OS_STB_HiS40V200
//#define GIC_IC_PHY_BASE (0xF8A00100)
#define GIC_IC_PHY_BASE (0xF8A02000)
#define GIC_ID_PHY_BASE (0xF8A01000)
#else
#define GIC_IC_PHY_BASE (0xFC000100)
#define GIC_ID_PHY_BASE (0xFC001000)
#endif
/* Distributor interface registers */
#define GICD_CTL                     0x0
#define GICD_CTR                     0x4
#define GICD_SEC                    0x80
#define GICD_ENABLESET             0x100
#define GICD_ENABLECLEAR           0x180
#define GICD_PENDINGSET            0x200
#define GICD_PENDINGCLEAR          0x280
#define GICD_ACTIVESET             0x300
#define GICD_ACTIVECLEAR           0x380
#define GICD_PRI                   0x400
#define GICD_CPUS                  0x800
#define GICD_CONFIG                0xC00
#define GICD_SW                    0xF00
#define GICD_CPENDSGIR             0xF10
#define GICD_SPENDSGIR             0xF20

/* Physical CPU Interface registers */
#define GICC_CTL                     0x0
#define GICC_PRIMASK                 0x4
#define GICC_BP                      0x8
#define GICC_INTACK                  0xC
#define GICC_EOI                    0x10
#define GICC_RUNNINGPRI             0x14
#define GICC_HIGHESTPEND            0x18
#define GICC_DEACTIVATE             0x1000

/*DMA interface registers*/
#define REG_BASE_DMAC              (0xFCD02000)
#define AXI_CONF_BASE               0x820
#define DMAC_GLB_REG_SEC            0x694

/*SCU registers*/
#ifdef OS_STB_HiS40V200
#define REG_BASE_SCU               (0xF8A00000)
#else
#define REG_BASE_SCU               (0xFC000000)
#endif
#define SCU_CTL                     0x50
#define SCU_NONSEC_CTL              0x54

extern int UART_SecureSetting_test(int* org);

extern void TZPC_init(void);

extern unsigned gic_int_num(void);

extern void setup_early_GIC_nonsecure(void);

extern void SCU_init();

extern void DMA_init();


#endif
