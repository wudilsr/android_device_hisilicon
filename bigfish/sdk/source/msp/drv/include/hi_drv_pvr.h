/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_drv_pvr.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/21
  Description   :
  History       :
  1.Date        : 2009/12/21
    Author      : w58735
    Modification: Created file

******************************************************************************/
#ifndef __HI_DRV_PVR_H__
#define __HI_DRV_PVR_H__

#include "hi_unf_pvr.h"
#include "hi_mpi_pvr.h"

/* definition of max play channel */
#define PVR_PLAY_MAX_CHN_NUM           5 

/* definition of max record channel */
#define PVR_REC_MAX_CHN_NUM            10 
#define PVR_REC_START_NUM               PVR_PLAY_MAX_CHN_NUM

#define CMD_PVR_INIT_PLAY               _IOR(HI_ID_PVR, 0x01, HI_U32)
#define CMD_PVR_CREATE_PLAY_CHN         _IOR(HI_ID_PVR, 0x02, HI_U32)
#define CMD_PVR_DESTROY_PLAY_CHN        _IOW(HI_ID_PVR, 0x03, HI_U32)

#define CMD_PVR_INIT_REC                _IOR(HI_ID_PVR, 0x11, HI_U32)
#define CMD_PVR_CREATE_REC_CHN          _IOR(HI_ID_PVR, 0x12, HI_U32)
#define CMD_PVR_DESTROY_REC_CHN         _IOW(HI_ID_PVR, 0x13, HI_U32)


#endif
