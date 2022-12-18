/*
 * Copyright (c) (2014 - ...) Device Chipset Source Algorithm and Chipset Platform Development Dept
 * Hisilicon. All rights reserved.
 *
 * File:    decoder.h
 *
 * Purpose: omxvdec decoder interface
 *
 * Author:  yangyichang 00226912
 *
 * Date:    26, 11, 2014
 *
 */

#ifndef __DECODER_H__
#define __DECODER_H__


#include "channel.h"


#define LAST_FRAME_BUF_ID           (0xFFFFFFEE)
#define LAST_FRAME_BUF_SIZE         (20)


HI_S32 decoder_init(HI_VOID);

HI_S32 decoder_exit(HI_VOID);

HI_S32 decoder_create_inst(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_DRV_CFG *pdrv_cfg);

HI_S32 decoder_release_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_start_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_stop_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_reset_inst(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_reset_inst_with_option(OMXVDEC_CHAN_CTX *pchan);

HI_S32 decoder_clear_stream(OMXVDEC_CHAN_CTX *pchan);

#endif

