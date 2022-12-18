/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_vo.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2009/12/17
  Description   :
  History       :
  1.Date        : 2009/12/17
    Author      : w58735
    Modification: Created file

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <linux/types.h>

#include "hi_drv_video.h"
#include "hi_drv_disp.h"
#include "hi_mpi_win.h"
#include "drv_win_ioctl.h"

#include "hi_mpi_avplay.h"
#include "hi_error_mpi.h"
#include "hi_drv_struct.h"
//#include "drv_vdec_ext.h"

#include "drv_venc_ext.h"
#include "win_ratio.h"

HI_VOID InitCompressor(HI_VOID);

int decompress(unsigned char *pData, int DataLen, int Width, int Height, int stride_luma, int stride_chrome, unsigned char *pFrame);

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif


static HI_S32           g_VoDevFd = -1;
static const HI_CHAR    g_VoDevName[] = "/dev/"UMAP_DEVNAME_VO;
static pthread_mutex_t  g_VoMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_VO_LOCK()     (void)pthread_mutex_lock(&g_VoMutex);
#define HI_VO_UNLOCK()   (void)pthread_mutex_unlock(&g_VoMutex);

#define CHECK_VO_INIT()\
do{\
    HI_VO_LOCK();\
    if (g_VoDevFd < 0)\
    {\
        HI_ERR_WIN("VO is not init.\n");\
        HI_VO_UNLOCK();\
        return HI_ERR_VO_NO_INIT;\
    }\
    HI_VO_UNLOCK();\
}while(0)


HI_S32 HI_MPI_WIN_Init(HI_VOID)
{
    struct stat st;

    HI_VO_LOCK();

    if (g_VoDevFd > 0)
    {
        HI_VO_UNLOCK();
        return HI_SUCCESS;
    }
    
    if (HI_FAILURE == stat(g_VoDevName, &st))
    {
        HI_FATAL_WIN("VO is not exist.\n");
        HI_VO_UNLOCK();
        return HI_ERR_VO_DEV_NOT_EXIST;
    }

    if (!S_ISCHR (st.st_mode))
    {
        HI_FATAL_WIN("VO is not device.\n");
        HI_VO_UNLOCK();
        return HI_ERR_VO_NOT_DEV_FILE;
    }

    g_VoDevFd = open(g_VoDevName, O_RDWR|O_NONBLOCK, 0);

    if (g_VoDevFd < 0)
    {
        HI_FATAL_WIN("open VO err.\n");
        HI_VO_UNLOCK();
        return HI_ERR_VO_DEV_OPEN_ERR;
    }

    HI_VO_UNLOCK();

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_DeInit(HI_VOID)
{
    HI_S32 Ret;

    HI_VO_LOCK();

    if (g_VoDevFd < 0)
    {
        HI_VO_UNLOCK();
        return HI_SUCCESS;
    }

    Ret = close(g_VoDevFd);

    if(HI_SUCCESS != Ret)
    {
        HI_FATAL_WIN("DeInit VO err.\n");
        HI_VO_UNLOCK();
        return HI_ERR_VO_DEV_CLOSE_ERR;
    }

    g_VoDevFd = -1;

    HI_VO_UNLOCK();

    return HI_SUCCESS;
}


HI_S32 HI_MPI_WIN_Create(const HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWindow)
{
    HI_S32           Ret;
    WIN_CREATE_S  VoWinCreate;

    if (!pWinAttr)
    {
        HI_ERR_WIN("para pWinAttr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (!phWindow)
    {
        HI_ERR_WIN("para phWindow is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (pWinAttr->enDisp >= HI_DRV_DISPLAY_BUTT
        && pWinAttr->bVirtual == HI_FALSE)
    {
        HI_ERR_WIN("para pWinAttr->enVo is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enAspectCvrs is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    memcpy(&VoWinCreate.WinAttr, pWinAttr, sizeof(HI_DRV_WIN_ATTR_S));
    VoWinCreate.bVirtScreen = HI_TRUE;

    Ret = ioctl(g_VoDevFd, CMD_WIN_CREATE, &VoWinCreate);
    if (Ret != HI_SUCCESS)
    {
		HI_ERR_WIN("  HI_MPI_WIN_Create failed.\n");
        return Ret;
    }

    *phWindow = VoWinCreate.hWindow;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Create_Ext(const HI_DRV_WIN_ATTR_S *pWinAttr, HI_HANDLE *phWindow, HI_BOOL bVirtScreen)
{
    HI_S32           Ret;
    WIN_CREATE_S  VoWinCreate;

    if (!pWinAttr)
    {
        HI_ERR_WIN("para pWinAttr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (!phWindow)
    {
        HI_ERR_WIN("para phWindow is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    if (pWinAttr->enDisp >= HI_DRV_DISPLAY_BUTT
        && pWinAttr->bVirtual == HI_FALSE)
    {
        HI_ERR_WIN("para pWinAttr->enVo is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (pWinAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enAspectCvrs is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();
    
    memcpy(&VoWinCreate.WinAttr, pWinAttr, sizeof(HI_DRV_WIN_ATTR_S));
    VoWinCreate.bVirtScreen = bVirtScreen;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_CREATE, &VoWinCreate);
    if (Ret != HI_SUCCESS)
    {
		HI_ERR_WIN("  HI_MPI_WIN_Create failed.\n");
        return Ret;
    }

    *phWindow = VoWinCreate.hWindow;

    return HI_SUCCESS;
}


HI_S32 HI_MPI_WIN_Destroy(HI_HANDLE hWindow)
{
    HI_S32      Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_DESTROY, &hWindow);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetInfo(HI_HANDLE hWin, HI_DRV_WIN_INFO_S * pstInfo)
{
    HI_S32 Ret; 
    WIN_PRIV_INFO_S WinPriv;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }
    CHECK_VO_INIT();
	
    WinPriv.hWindow = hWin;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_INFO, &WinPriv);
	if (!Ret)
	{
		*pstInfo = WinPriv.stPrivInfo;
	}
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetPlayInfo(HI_HANDLE hWin, HI_DRV_WIN_PLAY_INFO_S * pstInfo)
{
    HI_S32 Ret; 
    WIN_PLAY_INFO_S WinPlay;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }
    CHECK_VO_INIT();
	
    WinPlay.hWindow = hWin;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_PLAY_INFO, &WinPlay);
	if (!Ret)
	{
		*pstInfo = WinPlay.stPlayInfo;
	}
    
    return Ret;
}


HI_S32 HI_MPI_WIN_SetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc)
{
    HI_S32 Ret; 
    WIN_SOURCE_S VoWinAttach;

    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }
    CHECK_VO_INIT();
	
    VoWinAttach.hWindow = hWin;
    VoWinAttach.stSrc   = *pstSrc;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_SOURCE, &VoWinAttach);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetSource(HI_HANDLE hWin, HI_DRV_WIN_SRC_INFO_S *pstSrc)
{

    return HI_FAILURE;
}





HI_S32 HI_MPI_WIN_SetEnable(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    HI_S32            Ret;
    WIN_ENABLE_S   VoWinEnable;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if ((bEnable != HI_TRUE)
      &&(bEnable != HI_FALSE)
       )
    {
        HI_ERR_WIN("para bEnable is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinEnable.hWindow = hWindow;
    VoWinEnable.bEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ENABLE, &VoWinEnable);
    
    return Ret;
}


HI_S32 HI_MPI_VO_SetMainWindowEnable(HI_HANDLE hWindow, HI_BOOL bEnable)
{

    return HI_FAILURE;
}


HI_S32 HI_MPI_WIN_GetEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable)
{
    HI_S32            Ret;
    WIN_ENABLE_S   VoWinEnable;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pbEnable)
    {
        HI_ERR_WIN("para pbEnable is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinEnable.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ENABLE, &VoWinEnable);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *pbEnable = VoWinEnable.bEnable;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_VO_GetMainWindowEnable(HI_HANDLE hWindow, HI_BOOL *pbEnable)
{


    return HI_FAILURE;
}


HI_S32 HI_MPI_VO_GetWindowsVirtual(HI_HANDLE hWindow, HI_BOOL *pbVirutal)
{


    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_AcquireFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32              Ret;
    WIN_FRAME_S      VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pFrameinfo)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }
    
    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_VIR_ACQUIRE, &VoWinFrame);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    
    memcpy(pFrameinfo, &(VoWinFrame.stFrame), sizeof(HI_DRV_VIDEO_FRAME_S));

    return HI_SUCCESS;

}

HI_S32 HI_MPI_WIN_ReleaseFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrameinfo)
{
    HI_S32              Ret;
    WIN_FRAME_S      VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }
    
    CHECK_VO_INIT();
    
    VoWinFrame.hWindow = hWindow;
	VoWinFrame.stFrame = *pFrameinfo;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_VIR_RELEASE, &VoWinFrame);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetAttr(HI_HANDLE hWindow, const HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_S32           Ret;
    WIN_CREATE_S  VoWinCreate;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pWinAttr)
    {
        HI_ERR_WIN("para pWinAttr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }


    if (pWinAttr->enARCvrs >= HI_DRV_ASP_RAT_MODE_BUTT)
    {
        HI_ERR_WIN("para pWinAttr->enAspectCvrs is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinCreate.hWindow = hWindow;
    memcpy(&VoWinCreate.WinAttr, pWinAttr, sizeof(HI_DRV_WIN_ATTR_S));

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ATTR, &VoWinCreate);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetAttr(HI_HANDLE hWindow, HI_DRV_WIN_ATTR_S *pWinAttr)
{
    HI_S32           Ret;
    WIN_CREATE_S  VoWinCreate;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pWinAttr)
    {
        HI_ERR_WIN("para pWinAttr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinCreate.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ATTR, &VoWinCreate);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    memcpy(pWinAttr, &VoWinCreate.WinAttr, sizeof(HI_DRV_WIN_ATTR_S));

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetZorder(HI_HANDLE hWindow, HI_DRV_DISP_ZORDER_E enZFlag)
{
    HI_S32            Ret;
    WIN_ZORDER_S   VoWinZorder;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (enZFlag >= HI_DRV_DISP_ZORDER_BUTT)
    {
        HI_ERR_WIN("para enZFlag is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinZorder.hWindow = hWindow;
    VoWinZorder.eZFlag = enZFlag;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ZORDER, &VoWinZorder);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetZorder(HI_HANDLE hWindow, HI_U32 *pu32Zorder)
{
    HI_S32            Ret;
    WIN_ORDER_S   VoWinOrder;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pu32Zorder)
    {
        HI_ERR_WIN("para SrcHandle is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinOrder.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ORDER, &VoWinOrder);
    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }

    *pu32Zorder = VoWinOrder.Order;

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Attach(HI_HANDLE hWindow, HI_HANDLE hSrc)
{
#if 0
    HI_S32                  Ret;
    WIN_SOURCE_S         VoWinAttach;
    HI_HANDLE               hVdec;
    HI_HANDLE               hSync;
    HI_UNF_AVPLAY_ATTR_S    AvplayAttr;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!hSrc)
    {
        HI_ERR_WIN("para hSrc is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    if(HI_ID_VI == ((hSrc&0xff0000)>>16))
    {
        VoWinAttach.ModId = HI_ID_VI;
    }
    else if(HI_ID_AVPLAY == ((hSrc&0xff0000)>>16))
    {
        Ret = HI_MPI_AVPLAY_GetAttr(hSrc, HI_UNF_AVPLAY_ATTR_ID_STREAM_MODE, &AvplayAttr);
        if (HI_SUCCESS != Ret)
        {        
            return HI_ERR_VO_INVALID_PARA;
        }
        
        VoWinAttach.ModId = HI_ID_AVPLAY;
    }
    else
    {
        return HI_ERR_VO_INVALID_PARA;
    }
    
    if (HI_ID_AVPLAY == VoWinAttach.ModId)
    {
        Ret = HI_MPI_AVPLAY_GetSyncVdecHandle(hSrc, &hVdec, &hSync);
        if (Ret != HI_SUCCESS)
        {
            HI_ERR_AVPLAY("call HI_MPI_AVPLAY_GetVdecHandle failed.\n");
            return Ret;
        }
        VoWinAttach.hSrc = hVdec;
        VoWinAttach.hSync = hSync;
    }
    else
    {
        VoWinAttach.hSrc = hSrc;
    }

    
    VoWinAttach.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_SOURCE, &VoWinAttach);

    if (Ret != HI_SUCCESS)
    {
        return Ret;
    }
    
    if (HI_ID_AVPLAY == VoWinAttach.ModId)
    {
        Ret = HI_MPI_AVPLAY_AttachWindow(hSrc, hWindow);
        if (Ret != HI_SUCCESS) 
        {
            HI_ERR_WIN("call HI_MPI_AVPLAY_AttachWindow failed.\n");
            (HI_VOID)ioctl(g_VoDevFd, CMD_VO_WIN_DETACH, &VoWinAttach);
            return Ret;
        }
    }
#endif

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Detach(HI_HANDLE hWindow, HI_HANDLE hSrc)
{
    
    return HI_FAILURE;
}

HI_S32 HI_MPI_VO_SetWindowRatio(HI_HANDLE hWindow, HI_U32 u32WinRatio)
{

    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_Freeze(HI_HANDLE hWindow, HI_BOOL bEnable, HI_DRV_WIN_SWITCH_E enWinFreezeMode)
{
    HI_S32           Ret;
    WIN_FREEZE_S  VoWinFreeze;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if ((bEnable != HI_TRUE)
      &&(bEnable != HI_FALSE)
       )
    {
        HI_ERR_WIN("para bEnable is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    if (enWinFreezeMode >= HI_DRV_WIN_SWITCH_BUTT)
    {
        HI_ERR_WIN("para enWinFreezeMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinFreeze.hWindow = hWindow;
    VoWinFreeze.bEnable = bEnable;
    VoWinFreeze.eMode   = enWinFreezeMode;

    Ret = ioctl(g_VoDevFd, CMD_WIN_FREEZE, &VoWinFreeze);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetFreezeStat(HI_HANDLE hWindow, HI_BOOL *bEnable, HI_DRV_WIN_SWITCH_E *enWinFreezeMode)
{
    HI_S32           Ret;
    WIN_FREEZE_S    stWinFreeze;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }
    
    if ((!bEnable) || (!enWinFreezeMode))
    {
        HI_ERR_WIN("param ptr is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    stWinFreeze.hWindow = hWindow;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_FREEZE_STATUS, &stWinFreeze);
    if (Ret == HI_SUCCESS)
    {    
        *bEnable = stWinFreeze.bEnable;
        *enWinFreezeMode = stWinFreeze.eMode;
    }
    
    return Ret;
}

HI_S32 HI_MPI_WIN_SetFieldMode(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    
    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_SendFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32             Ret;
    WIN_FRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrame is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinFrame.hWindow  = hWindow;
	VoWinFrame.stFrame = *pFrame;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SEND_FRAME, &VoWinFrame);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_DequeueFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32  Ret;
    WIN_FRAME_S VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_DQ_FRAME, &VoWinFrame);
    if (!Ret)
    {
		*pFrame = VoWinFrame.stFrame;
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_QueueSyncFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame,HI_U32 *pu32FenceFd)
{
    HI_S32             Ret;
    WIN_SYNCFRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }
	
	if (!pu32FenceFd)
    {
        HI_ERR_WIN("para pu32FenceFd is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }
	
    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;
	VoWinFrame.stFrame = *pFrame;
	VoWinFrame.u32FenceFd = 0xffffffff;

	Ret = ioctl(g_VoDevFd, CMD_WIN_QUSYNC_FRAME, &VoWinFrame);
	if (!Ret)
	{
		*pu32FenceFd = VoWinFrame.u32FenceFd;
	}

    return Ret;
}
HI_S32 HI_MPI_WIN_QueueFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32             Ret;
    WIN_FRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;
	VoWinFrame.stFrame = *pFrame;


	Ret = ioctl(g_VoDevFd, CMD_WIN_QU_FRAME, &VoWinFrame);

    return Ret;
}

HI_S32 HI_MPI_WIN_QueueUselessFrame(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pFrame)
{
    HI_S32             Ret;
    WIN_FRAME_S     VoWinFrame;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pFrame)
    {
        HI_ERR_WIN("para pFrameinfo is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinFrame.hWindow = hWindow;
	VoWinFrame.stFrame = *pFrame;
	
    Ret = ioctl(g_VoDevFd, CMD_WIN_QU_ULSFRAME, &VoWinFrame);

    return Ret;
}


HI_S32 HI_MPI_WIN_Reset(HI_HANDLE hWindow, HI_DRV_WIN_SWITCH_E enWinFreezeMode)
{
    WIN_RESET_S   VoWinReset;
    HI_S32 Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (enWinFreezeMode >= HI_DRV_WIN_SWITCH_BUTT)
    {
        HI_ERR_WIN("para enWinFreezeMode is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinReset.hWindow = hWindow;
    VoWinReset.eMode = enWinFreezeMode;

    Ret = ioctl(g_VoDevFd, CMD_WIN_RESET, &VoWinReset);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_Pause(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    WIN_PAUSE_S   VoWinPause;
    HI_S32           Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if ((bEnable != HI_TRUE)
      &&(bEnable != HI_FALSE)
       )
    {
        HI_ERR_WIN("para bEnable is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();

    VoWinPause.hWindow = hWindow;
    VoWinPause.bEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_PAUSE, &VoWinPause);
    
    return Ret;
}


HI_S32 HI_MPI_VO_GetWindowDelay(HI_HANDLE hWindow, HI_DRV_WIN_PLAY_INFO_S *pDelay)
{
    WIN_PLAY_INFO_S   VoWinDelay;
    HI_S32 Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    if (!pDelay)
    {
        HI_ERR_WIN("para pDelay is null.\n");
        return HI_ERR_VO_NULL_PTR;
    }

    CHECK_VO_INIT();

    VoWinDelay.hWindow = hWindow;

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_PLAY_INFO, &VoWinDelay);
    if (!Ret)
    {
        *pDelay = VoWinDelay.stPlayInfo;
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_SetStepMode(HI_HANDLE hWindow, HI_BOOL bStepMode)
{
    HI_S32              Ret;
    WIN_STEP_MODE_S  WinStepMode;
    
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    WinStepMode.hWindow = hWindow;
    WinStepMode.bStep = bStepMode;

    Ret = ioctl(g_VoDevFd, CMD_WIN_STEP_MODE, &WinStepMode);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_SetStepPlay(HI_HANDLE hWindow)
{
    HI_S32      Ret;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_STEP_PLAY, &hWindow);
    
    return Ret;
}

HI_S32 HI_MPI_VO_DisableDieMode(HI_HANDLE hWindow)
{
    return HI_FAILURE;
}

HI_S32 HI_MPI_WIN_SetExtBuffer(HI_HANDLE hWindow, HI_DRV_VIDEO_BUFFER_POOL_S* pstBufAttr)
{
    HI_S32      Ret;
//    HI_S32      s32Index;
    WIN_BUF_POOL_S  bufferAttr;
	
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    bufferAttr.hwin = hWindow;
    bufferAttr.stBufPool = *pstBufAttr;

    Ret = ioctl(g_VoDevFd, CMD_WIN_VIR_EXTERNBUF, &bufferAttr);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_SetQuickOutput(HI_HANDLE hWindow, HI_BOOL bEnable)
{
    WIN_SET_QUICK_S stQuickOutputAttr;
    HI_S32      Ret = HI_FAILURE;

    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    stQuickOutputAttr.hWindow = hWindow;
    stQuickOutputAttr.bQuickEnable = bEnable;

    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_QUICK, &stQuickOutputAttr);
    
    return Ret;
}

HI_S32 HI_MPI_WIN_GetQuickOutputStatus(HI_HANDLE hWindow, HI_BOOL *bQuickOutputEnable)
{
    WIN_SET_QUICK_S stQuickOutputAttr;
    HI_S32      Ret = HI_FAILURE;
    
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();    
    stQuickOutputAttr.hWindow = hWindow;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_QUICK, &stQuickOutputAttr);
    if (Ret == HI_SUCCESS)
    {
        *bQuickOutputEnable = stQuickOutputAttr.bQuickEnable;
    }
    
    return Ret;    
}

HI_S32 HI_MPI_VO_UseDNRFrame(HI_HANDLE hWindow, HI_BOOL bEnable)
{ 
    return HI_FAILURE;
}


HI_S32 HI_MPI_VO_CapturePictureExt(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pstCapPicture)
{
    HI_S32            Ret = HI_SUCCESS;
    WIN_CAPTURE_S     VoWinCapture;    
    HI_U32          datalen = 0, i = 0, y_stride = 0, height = 0;
    HI_UCHAR        *DecompressOutBuf = HI_NULL, *DecompressInBuf = HI_NULL;
    HI_UCHAR        *Inptr = HI_NULL, *Outptr = HI_NULL;
    
    CHECK_VO_INIT();           
    if ((HI_INVALID_HANDLE == hWindow) || (!pstCapPicture))
    {          
        HI_ERR_WIN(" invalid param.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }
    
    /*first,  we get a frame from the window.*/
    VoWinCapture.hWindow = hWindow;    
    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_START, &VoWinCapture);        
    if (Ret != HI_SUCCESS) 
        return Ret;
    
    y_stride = VoWinCapture.CapPicture.stBufAddr[0].u32Stride_Y;    
       
    height = VoWinCapture.CapPicture.u32Height; 
    
    DecompressOutBuf = (HI_UCHAR *)(HI_MMAP(VoWinCapture.driver_supply_addr.startPhyAddr,
                                                VoWinCapture.driver_supply_addr.length));
    
    if ( HI_DRV_PIX_FMT_NV21 == VoWinCapture.CapPicture.ePixFormat) 
        datalen = height * y_stride * 3 / 2;
    else 
        datalen = height * y_stride * 2;
    
    DecompressInBuf =(HI_UCHAR *)(HI_MMAP(VoWinCapture.CapPicture.stBufAddr[0].u32PhyAddr_Y, datalen));

    /*third  step, we make a decompress or simple copy from driver-vpss frame to user frame.*/
    Inptr = DecompressInBuf; 
    Outptr = DecompressOutBuf;
    
    if ( (HI_NULL ==Inptr) ||(HI_NULL ==Outptr) 
          ||(0 == y_stride))                  
        return HI_FAILURE;

    for(i = 0 ; i < datalen / y_stride; i++) 
    {
        memcpy(Outptr, Inptr, y_stride);
        Inptr += y_stride;
        Outptr += y_stride;
    }
      
    if (HI_SUCCESS != HI_MUNMAP((void*)DecompressInBuf)) 
    {
        HI_ERR_WIN("decompress buffer unmap fail\r\n");
        (HI_VOID)HI_MUNMAP((void*)DecompressOutBuf);
        goto release;
    }
    
    if (HI_SUCCESS != HI_MUNMAP((void*)DecompressOutBuf))
    {
        HI_ERR_WIN("decompress buffer unmap fail\r\n");
        goto release;
    }
    
release:    

    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_RELEASE, &VoWinCapture);
    if (Ret != HI_SUCCESS) 
        return Ret;
    
    *pstCapPicture = VoWinCapture.CapPicture;    
    /*FIXME: we should know how the 3d will be dealed with*/
    pstCapPicture->stBufAddr[0].u32PhyAddr_Y = VoWinCapture.driver_supply_addr.startPhyAddr;        
    pstCapPicture->stBufAddr[1].u32PhyAddr_Y = VoWinCapture.driver_supply_addr.startPhyAddr;
      
    pstCapPicture->stBufAddr[0].u32PhyAddr_C = 
        pstCapPicture->stBufAddr[0].u32PhyAddr_Y +
        height * y_stride ;
    pstCapPicture->stBufAddr[1].u32PhyAddr_C = 
        pstCapPicture->stBufAddr[1].u32PhyAddr_Y +
        height * y_stride ;
    return HI_SUCCESS;
}


HI_S32 HI_MPI_WIN_CapturePicture(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pstCapPicture)
{
    HI_S32            Ret = HI_SUCCESS;
    
    Ret = HI_MPI_VO_CapturePictureExt(hWindow, pstCapPicture);    
    return Ret;	
}


HI_S32 HI_MPI_WIN_CapturePictureRelease(HI_HANDLE hWindow, HI_DRV_VIDEO_FRAME_S *pstCapPicture)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_CAPTURE_S   VoWinRls;
    
    CHECK_VO_INIT();
    if ((HI_INVALID_HANDLE == hWindow) || (!pstCapPicture))
    {
        HI_ERR_WIN("invalid  param.\n");    
        return HI_ERR_VO_INVALID_PARA; 
    }
    
    VoWinRls.hWindow = hWindow;
    VoWinRls.CapPicture = *pstCapPicture;
    VoWinRls.driver_supply_addr.startPhyAddr = pstCapPicture->stBufAddr[0].u32PhyAddr_Y;
    
    Ret = ioctl(g_VoDevFd, CMD_VO_WIN_CAPTURE_FREE, &VoWinRls);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_CapturePictureRelease fail (INVALID_PARA)\r\n");
        return Ret;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetRotation(HI_HANDLE hWindow, HI_DRV_ROT_ANGLE_E enRotation)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_ROTATION_S  VoWinRotation;
    VoWinRotation.hWindow = hWindow;
    VoWinRotation.enRotation = enRotation;
    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_ROTATION, &VoWinRotation);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_SetRotation fail \r\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GetRotation(HI_HANDLE hWindow, HI_DRV_ROT_ANGLE_E *penRotation)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_ROTATION_S  VoWinRotation;
    VoWinRotation.hWindow = hWindow;
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_ROTATION, &VoWinRotation);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_GetRotation fail \r\n");
        return Ret;
    }
    *penRotation = VoWinRotation.enRotation;
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_SetFlip(HI_HANDLE hWindow, HI_BOOL bHoriFlip, HI_BOOL bVertFlip)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_FLIP_S  VoWinFlip;
    VoWinFlip.hWindow = hWindow;
    VoWinFlip.bHoriFlip = bHoriFlip;
    VoWinFlip.bVertFlip = bVertFlip;
    Ret = ioctl(g_VoDevFd, CMD_WIN_SET_FLIP, &VoWinFlip);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_SetFlip fail \r\n");
        return Ret;
    }
    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GetFlip(HI_HANDLE hWindow, HI_BOOL *pbHoriFlip, HI_BOOL *pbVertFlip)
{
    HI_S32          Ret = HI_SUCCESS;
    WIN_FLIP_S  VoWinFlip;
    VoWinFlip.hWindow = hWindow;
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_FLIP, &VoWinFlip);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_GetRotation fail \r\n");
        return Ret;
    }
    *pbHoriFlip = VoWinFlip.bHoriFlip;
    *pbVertFlip = VoWinFlip.bVertFlip;
    return HI_SUCCESS;
}

#if 0
HI_S32 HI_MPI_VO_SetWindowExtAttr(HI_HANDLE hWindow, VO_WIN_EXTATTR_E detType, HI_BOOL bEnable)
{
    HI_S32      Ret;
    VO_WIN_DETECT_S stDetType;
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }

    CHECK_VO_INIT();
    stDetType.hWindow = hWindow;
    stDetType.detType = detType;
    stDetType.bEnable = bEnable;
    Ret = ioctl(g_VoDevFd, CMD_VO_SET_DET_MODE, &stDetType);

    return Ret;
}

HI_S32 HI_MPI_VO_GetWindowExtAttr(HI_HANDLE hWindow, VO_WIN_EXTATTR_E detType, HI_BOOL *bEnable)
{
    HI_S32      Ret;
    VO_WIN_DETECT_S stDetType;
    if (HI_INVALID_HANDLE == hWindow)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA;
    }
    CHECK_VO_INIT();

    stDetType.hWindow = hWindow;
    stDetType.detType = detType;
    Ret = ioctl(g_VoDevFd, CMD_VO_GET_DET_MODE, &stDetType);
    *bEnable = stDetType.bEnable;

    return Ret;
}
#endif

HI_S32 HI_MPI_WIN_Suspend(HI_VOID)
{
    HI_U32 u32Value = 0x88888888;
    HI_S32 Ret;

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_SUSPEND, &u32Value);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_Suspend failed\n");
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_Resume(HI_VOID)
{
    HI_U32 u32Value = 0x88888888;
    HI_S32 Ret;

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_RESUM, &u32Value);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_Resume failed\n");
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_WIN_GetHandle(WIN_GET_HANDLE_S *pstWinHandle)
{
    HI_S32 Ret;

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_HANDLE, pstWinHandle);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_GetHandle failed\n");
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_GetWinParam(HI_HANDLE hWin, HI_DRV_WIN_INTF_S *pstWinIntf)
{
    HI_S32      Ret;
    WIN_INTF_S stWinIntf;
    
    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_INTF, &stWinIntf);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_AttachSink failed\n");
    }
    else
    {
       
        pstWinIntf->pfAcqFrame = stWinIntf.pfAcqFrame;
        pstWinIntf->pfRlsFrame = stWinIntf.pfRlsFrame;
        pstWinIntf->pfSetWinAttr = stWinIntf.pfSetWinAttr;
    }

    return Ret;
}


HI_S32 HI_MPI_WIN_AttachWinSink(HI_HANDLE hWin, HI_HANDLE hSink)
{
    HI_S32      Ret;
    WIN_ATTACH_S stAttach;
    
    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    stAttach.enType = ATTACH_TYPE_SINK;
    stAttach.hWindow = hWin;
    stAttach.hMutual = hSink;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_ATTACH, &stAttach);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_AttachSink failed\n");
    }

    return Ret;
}

HI_S32 HI_MPI_WIN_DetachWinSink(HI_HANDLE hWin, HI_HANDLE hSink)
{
    HI_S32      Ret;
    WIN_ATTACH_S stAttach;
    
    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    stAttach.enType = ATTACH_TYPE_SINK;
    stAttach.hWindow = hWin;
    stAttach.hMutual = hSink;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_DETACH, &stAttach);
    if (Ret != HI_SUCCESS)
    {
        HI_ERR_WIN("HI_MPI_WIN_DetachSink failed\n");
    }

    return Ret;
}


HI_S32 HI_MPI_WIN_GetLatestFrameInfo(HI_HANDLE hWin, HI_DRV_VIDEO_FRAME_S  *frame_info)
{
    HI_S32      Ret; 
    WIN_FRAME_S frame_struct;
    
    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    frame_struct.hWindow = hWin;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_LATESTFRAME_INFO, &frame_struct);
    if (Ret != HI_SUCCESS)
    {
		HI_ERR_WIN("get latest frame info failed\n");
		return Ret;
    }

    *frame_info  = frame_struct.stFrame;   
    return Ret;
}

HI_S32 HI_MPI_WIN_GetUnloadTimes(HI_HANDLE hWin, HI_U32 *pu32Time)
{
    HI_S32      Ret; 
    WIN_UNLOAD_S stWinUnload;
    
    if (HI_INVALID_HANDLE == hWin)
    {
        HI_ERR_WIN("para hWindow is invalid.\n");
        return HI_ERR_VO_INVALID_PARA; 
    }

    CHECK_VO_INIT();

    stWinUnload.hWindow = hWin;
    
    Ret = ioctl(g_VoDevFd, CMD_WIN_GET_UNLOAD, &stWinUnload);
    if (Ret != HI_SUCCESS)
    {
		HI_ERR_WIN("get latest frame info failed\n");
		return Ret;
    }

    *pu32Time  = stWinUnload.u32Times;   
    return Ret;
}

static HI_S32 MPI_WIN_GetVdecAbility(HI_CHIP_TYPE_E enChipType,
                    HI_U32 *pu32WidthMax,
                    HI_U32 *pu32HeightMax)
{
    HI_S32 s32Ret = HI_SUCCESS;

    if (HI_CHIP_TYPE_HI3798M == enChipType)
    {
        *pu32WidthMax = 3840;
        *pu32HeightMax = 2160;

        s32Ret = HI_SUCCESS;
    }
    else
    {
        HI_ERR_WIN("Invalid ChipType %d\n", enChipType);
        s32Ret = HI_FAILURE;
    }

    return s32Ret;
}

HI_S32 HI_MPI_WIN_CalMediaRect(HI_CHIP_TYPE_E enChipType,
                              HI_RECT_S stStreamRect,
                              HI_RECT_S *pstMediaRect)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32OriW = 0,u32OriH = 0;
    HI_U32 u32DstW = 0,u32DstH = 0;
    HI_U32 u32WidthLevel = 0, u32HeightLevel = 0;

    u32OriW = (HI_U32)stStreamRect.s32Width;
    u32OriH = (HI_U32)stStreamRect.s32Height;

    s32Ret = MPI_WIN_GetVdecAbility(enChipType,&u32WidthLevel,&u32HeightLevel);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_WIN("Can't get Width/Height Level\n");
        return s32Ret;
    }

    if(u32OriW < u32WidthLevel && u32OriH < u32HeightLevel)
    {
        u32DstW = u32OriW;
        u32DstH = u32OriH;
    }
    else
    {
        HI_U32 u32RatioW;
        HI_U32 u32RatioH;
        HI_U32 u32TmpH;
        HI_U32 u32TmpW;

		if (u32OriW >= u32WidthLevel && u32OriH >= u32HeightLevel)
		{
			u32DstW = u32WidthLevel;	
			u32DstH = u32HeightLevel;
		}
		else
		{
			u32RatioW = u32OriW*2048/u32WidthLevel;
			u32RatioH = u32OriH*2048/u32HeightLevel;

			if (u32RatioW > u32RatioH)
			{
				u32TmpW = u32OriW*2048/u32RatioW;
				u32TmpH = u32OriH*2048/u32RatioW;
			}
			else
			{
				u32TmpW = u32OriW*2048/u32RatioH;
				u32TmpH = u32OriH*2048/u32RatioH;
			}

			u32TmpW = u32TmpW & 0xfffffffe;
			u32TmpH = u32TmpH & 0xfffffffc;

			u32DstW = u32TmpW;
			u32DstH = u32TmpH;
		}
    }

    pstMediaRect->s32Height = (HI_S32)u32DstH;
    pstMediaRect->s32Width = (HI_S32)u32DstW;

    return s32Ret;
}

HI_S32 HI_MPI_WIN_CalAspectRegion(HI_MPI_WIN_RATIO_PARA_S stInPara,HI_RECT_S *pstRevisedRect)
{
	HI_S32 s32Ret;

	ALG_RATIO_OUT_PARA_S stOutPara;
	ALG_RATIO_IN_PARA_S stInRatioPara;

	stInRatioPara.SrcImgH = stInPara.SrcImgH;
	stInRatioPara.SrcImgW = stInPara.SrcImgW;
	stInRatioPara.DeviceWidth = stInPara.DeviceWidth;
	stInRatioPara.DeviceHeight = stInPara.DeviceHeight;
	stInRatioPara.eAspMode = stInPara.eAspMode;
	stInRatioPara.stOutWnd = stInPara.stOutWnd;
	stInRatioPara.stInWnd = stInPara.stInWnd;

	if (stInRatioPara.stInWnd.s32Width != stInRatioPara.SrcImgW
		|| stInRatioPara.stInWnd.s32Height != stInRatioPara.SrcImgH)
	{
		stInRatioPara.AspectWidth = 
			stInPara.AspectWidth*stInPara.SrcImgW/stInPara.stInWnd.s32Width;	
		stInRatioPara.AspectHeight =
			stInPara.AspectHeight*stInPara.SrcImgH/stInPara.stInWnd.s32Height;

		stInRatioPara.SrcImgW = stInPara.stInWnd.s32Width;
		stInRatioPara.SrcImgH = stInPara.stInWnd.s32Height;
	}
	else
	{
		stInRatioPara.AspectWidth = stInPara.AspectWidth;
		stInRatioPara.AspectHeight = stInPara.AspectHeight;
	}

	stInRatioPara.stScreen = stInPara.stScreen;
	stInRatioPara.stUsrAsp.bUserDefAspectRatio = HI_FALSE;

	if (stInPara.eAspMode == HI_DRV_ASP_RAT_MODE_FULL)
	{
		stOutPara.stOutWnd.s32X = stInPara.stOutWnd.s32X;
		stOutPara.stOutWnd.s32Y = stInPara.stOutWnd.s32Y;
		stOutPara.stOutWnd.s32Width = stInPara.stOutWnd.s32Width;
		stOutPara.stOutWnd.s32Height = stInPara.stOutWnd.s32Height;
	}
	else if (stInPara.eAspMode == HI_DRV_ASP_RAT_MODE_LETTERBOX)
	{
		s32Ret = WIN_RATIO_GetAspCfg(&stOutPara,&stInRatioPara);
		if (s32Ret != HI_SUCCESS)
		{
			HI_FATAL_WIN("GetAspCfg Failed\n");
		}
	}
	else
	{
		stOutPara.stOutWnd.s32X = stInPara.stOutWnd.s32X;
		stOutPara.stOutWnd.s32Y = stInPara.stOutWnd.s32Y;
		stOutPara.stOutWnd.s32Width = stInPara.stOutWnd.s32Width;
		stOutPara.stOutWnd.s32Height = stInPara.stOutWnd.s32Height;
		HI_FATAL_WIN("Invalid aspect mode %d\n",stInPara.eAspMode);	
	}

	pstRevisedRect->s32X = stOutPara.stOutWnd.s32X;
	pstRevisedRect->s32Y = stOutPara.stOutWnd.s32Y;
	pstRevisedRect->s32Width = stOutPara.stOutWnd.s32Width;
	pstRevisedRect->s32Height  = stOutPara.stOutWnd.s32Height;

	return HI_SUCCESS;	
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

