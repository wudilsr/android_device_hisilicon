/******************************************************************************

Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : cfg_nagra.h
Version       : Initial
Author        : Hisilicon hisecurity team
Created       : 2013-08-28
Last Modified :
Description   : 
Function List :
History       :
******************************************************************************/
#ifndef __CFG_NAGRA_H__
#define __CFG_NAGRA_H__

#include "hi_unf_common.h"
#include "hi_unf_avplay.h"
#include "hi_unf_sound.h"
#include "hi_unf_disp.h"
#include "hi_unf_vo.h"
#include "hi_unf_demux.h"
#include "hi_unf_hdmi.h"
#include "HA.AUDIO.MP3.decode.h"
#include "HA.AUDIO.MP2.decode.h"
#include "HA.AUDIO.AAC.decode.h"
#include "HA.AUDIO.DRA.decode.h"
#include "HA.AUDIO.PCM.decode.h"
#include "HA.AUDIO.WMA9STD.decode.h"
#include "HA.AUDIO.AMRNB.codec.h"
#include "hi_adp.h"
#include "hi_adp_audio.h"
#include "hi_adp_hdmi.h"
#include "hi_adp_boardcfg.h"
#include "hi_adp_mpi.h"
#include "hi_adp_tuner.h"

#define DSC_TUNER_FREQ 754
#define DSC_TUNER_SRATE 6875
#define DSC_TUNER_QAM 64
#define DSC_ENC_FMT HI_UNF_ENC_FMT_1080i_50
#ifndef DEFAULT_DVB_PORT
#define DEFAULT_DVB_PORT 0
#endif
#define SCR_STREAM_PATH  "/stream"

#ifdef  HI_ADVCA_FUNCTION_RELEASE
#define HI_DEBUG_NAGRA(format...)
#define HI_TRACE_LOG(format...)      printf(format)
#else
#define HI_DEBUG_NAGRA(format...)    printf(format)
#define HI_TRACE_LOG(format...)      printf(format)
#endif

#endif

