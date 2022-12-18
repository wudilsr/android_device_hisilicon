/*******************************************************************************
* All rights reserved, Copyright (C) huawei LIMITED 2012
*------------------------------------------------------------------------------
* File Name   : sre_cache_l2x0.h
* Description : PL310, l2cache
* Platform    :
* Author      :
* Version     : 1.0
* Date        :
* Notes       :
*
*------------------------------------------------------------------------------
* Modifications:
*   Date         Author          Modifications
    2013-02-21   h00206996       created
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

#ifndef _SRE_CACHE_L2X0_H
#define _SRE_CACHE_L2X0_H

#define L2X0_CACHE_ID                   0x000
#define L2X0_CACHE_TYPE                 0x004
#define L2X0_CTRL                       0x100
#define L2X0_AUX_CTRL                   0x104
#define L2X0_TAG_LATENCY_CTRL           0x108
#define L2X0_DATA_LATENCY_CTRL          0x10C
#define L2X0_EVENT_CNT_CTRL             0x200
#define L2X0_EVENT_CNT1_CFG             0x204
#define L2X0_EVENT_CNT0_CFG             0x208
#define L2X0_EVENT_CNT1_VAL             0x20C
#define L2X0_EVENT_CNT0_VAL             0x210
#define L2X0_INTR_MASK                  0x214
#define L2X0_MASKED_INTR_STAT           0x218
#define L2X0_RAW_INTR_STAT              0x21C
#define L2X0_INTR_CLEAR                 0x220
#define L2X0_CACHE_SYNC                 0x730
#define L2X0_DUMMY_REG                  0x740
#define L2X0_INV_LINE_PA                0x770
#define L2X0_INV_WAY                    0x77C
#define L2X0_CLEAN_LINE_PA              0x7B0
#define L2X0_CLEAN_LINE_IDX             0x7B8
#define L2X0_CLEAN_WAY                  0x7BC
#define L2X0_CLEAN_INV_LINE_PA          0x7F0
#define L2X0_CLEAN_INV_LINE_IDX         0x7F8
#define L2X0_CLEAN_INV_WAY              0x7FC
#define L2X0_LOCKDOWN_WAY_D             0x900
#define L2X0_LOCKDOWN_WAY_I             0x904
#define L2X0_TEST_OPERATION             0xF00
#define L2X0_LINE_DATA                  0xF10
#define L2X0_LINE_TAG                   0xF30
#define L2X0_DEBUG_CTRL                 0xF40
#define L2X0_PREFETCH_CTRL              0xF60
#define L2X0_POWER_CTRL                 0xF80
#define L2X0_DYNAMIC_CLK_GATING_EN    (1 << 1)
#define L2X0_STNDBY_MODE_EN           (1 << 0)

/* Registers shifts and masks */
#define L2X0_CACHE_ID_REV_MASK          (0x3f)
#define L2X0_CACHE_ID_PART_MASK         (0xf << 6)
#define L2X0_CACHE_ID_PART_L210         (1 << 6)
#define L2X0_CACHE_ID_PART_L310         (3 << 6)
#define L2X0_AUX_CTRL_MASK                      0xc0000fff
#define L2X0_AUX_CTRL_ASSOCIATIVITY_SHIFT       16
#define L2X0_AUX_CTRL_WAY_SIZE_SHIFT            17
#define L2X0_AUX_CTRL_WAY_SIZE_MASK             (0x7 << 17)
#define L2X0_AUX_CTRL_SHARE_OVERRIDE_SHIFT      22
#define L2X0_AUX_CTRL_NS_LOCKDOWN_SHIFT         26
#define L2X0_AUX_CTRL_NS_INT_CTRL_SHIFT         27
#define L2X0_AUX_CTRL_DATA_PREFETCH_SHIFT       28
#define L2X0_AUX_CTRL_INSTR_PREFETCH_SHIFT      29
#define L2X0_AUX_CTRL_EARLY_BRESP_SHIFT         30
#ifdef STB_CIPHER_DRIVER
#define REG_BASE_L2CC 0xF8A10000
#else
#define REG_BASE_L2CC 0xFC100000
#endif
#define CACHE_LINE_SIZE		32

#endif
