/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : monitor.S
* Description :
* Platform    :
* Author      :
* Version     : 1.0
* Date        :
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date         Author          Modifications
    2012-08-09   z00202529       created
                 l00209118       modified
    2012-12-12   z00206978       modified
    2013-02-19   h00206996       add monitor api,merge into RTOSck
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
#include "monitor.h"
#include "secure_extension.h"
#include "sre_cache_l2x0.h"
#ifdef MONITOR_TEST
    .equ MONITOR_TEST_DEF, 1
#endif
    .text
    .include  "sre_asm_macro.ph"

    .global SMC_Handler

    .extern osuart_printf_secure
    .extern suspend_task
    .extern dma_cfg_resume
    .extern change_to_ns

/*
; ------------------------------------------------------------
; Secure Monitor
; ------------------------------------------------------------
*/
.align 5

SMC_Handler:
/*h00206996 modify begin*/
    cmp r0, #MAPI_SUSPEND_TASK
    beq suspend_task

    /*l2 cache APIs*/
    cmp r0, #MAPI_L2CACHE_POWER
    beq mapi_l2x0_powercontrol

    cmp r0, #MAPI_L2CACHE_SR
    beq mapi_l2x0_suspend_resume
    /*l2 cache APIs end*/

    cmp r0, #MAPI_SECURERAM_S
    beq mapi_scram_store

    cmp r0, #MAPI_SECURERAM_R
    beq mapi_scram_restore
#if 0
    cmp r0, #MAPI_SECURERAM_C
    beq mapi_scram_slave_code_copy
#endif
    cmp r0, #MAPI_DMA_CFG_RESUME
    beq dma_cfg_resume

    cmp r0, #MAPI_FIRST_SWITCH
    beq mapi_first_switch

    /*world switch API*/

    //wait for framework open these code
    push    {r7}
    ldr r7, =params_stack
    stmia   r7, {r0-r3}
    pop     {r7}

    cmp r0, #MAPI_TZ_API
    /*CALL_TRUSTZONE_API*/
    beq tz_api
    cmp r0, #MAPI_RET_FROM_SECURE
    /*RET_FROM_SECURE_API*/
    beq ret_from_secure_api

    /*DTS: for SR back to kernel for monitor, l00202565 add begin */
    cmp r0, #MAPI_SR_BACK_TO_NS
    beq mapi_suspend_change_to_ns
    /*DTS: for SR back to kernel for monitor, l00202565 add end */
/*h00206996 modify end*/


