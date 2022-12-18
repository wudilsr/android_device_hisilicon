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
    2013-02-19   h00206996       created
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

#ifndef _MONITOR_H
#define _MONITOR_H
/*registers*/

#include "sre_board.h"

#define SEC_SUSPEND_FLAG           0xF800FFF0
#define REG_BASE_A9PER             0xFC000000
#define A9_GLB_TIMER_BASE          0xFC000200
#define REG_BASE_L2CC              0xFC100000

#define MASTER_SR_BACK_PHY_ADDR    REG_BASE_SCTRL+0x308
#define SECURAM_CODE_READY_FLAG    REG_BASE_SCTRL+0x330

#define REG_BASE_PCTRL             0xFCA09000
#define REG_BASE_PMCTRL            0xFCA08000

#define REG_BASE_PMUSPI            0xFCC00000
#define DDR_CTRLOR_BASE            0xFCD00000
#define REG_BASE_DMAC              0xFCD02000

/*used in suspend process*/
#define SCXTALCTRL_CFG_VAL         (0x1FFFFF00)
#define TIM64_Ctl                  (0x8)
#define AXI_CONF_BASE               0x820

/*SCR register bits*/
#define SCR_NS_BIT                       0x01    /*; Non-Secure (NS) bit*/
#define SCR_IRQ_BIT                      0x02    /*; IRQ bit*/
#define SCR_FIQ_BIT                      0x04    /*; FIQ bit*/
#define SCR_EA_BIT                       0x08    /*; EA  bit*/
#define SCR_FW_BIT                       0x10    /*; F   Bit writable (FW) bit*/
#define SCR_AW_BIT                       0x20    /*; A   Bit writable (AW) bit*/

#endif
