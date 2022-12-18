/******************************************************************************
*              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: unf_gfx2d.c
* Description: Graphic 2D engine API declaration.
*
* History:
* Version   Date         Author     DefectNum    Description
* main\1    2013-08-02              NULL         Create this file.
*******************************************************************************/
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "hi_gfx2d_api.h"
#include "hi_gfx2d_errcode.h"
#include "drv_gfx2d_ioctl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/

/* device path */
static const HI_CHAR *gs_pszGFX2DDevPath = "/dev/hi_gfx2d";

/* device lock */
static pthread_mutex_t gs_GFX2DDevMutex = PTHREAD_MUTEX_INITIALIZER;

/* device description symbol */
static HI_S32 gs_s32GFX2DDevFd = -1;

/* device quoted count */
static HI_U32 gs_u32GFX2DDevRef = 0;

/* check dev id is invalid or not */
#define GFX2D_CHECK_DEVID(enDevId) do \
    {\
        if (enDevId >= HI_GFX2D_DEV_ID_BUTT)\
        {\
            return HI_ERR_GFX2D_INVALID_DEVID;\
        }\
    }while(0)

/* check dev is opened or not */
#define GFX2D_CHECK_DEVSTATE() do \
    {\
        pthread_mutex_lock(&gs_GFX2DDevMutex);\
        if (-1 == gs_s32GFX2DDevFd)\
        {\
            pthread_mutex_unlock(&gs_GFX2DDevMutex); \
            return HI_ERR_GFX2D_DEV_NOT_OPEN; \
        } \
        pthread_mutex_unlock(&gs_GFX2DDevMutex); \
    } while (0)


HI_S32 HI_GFX2D_Open(const HI_GFX2D_DEV_ID_E enDevId)
{
    HI_S32 s32Ret;

    GFX2D_CHECK_DEVID(enDevId);
    
    s32Ret = pthread_mutex_lock(&gs_GFX2DDevMutex);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_ERR_GFX2D_SYS;
    }

    /* device opened, return afrer adding ref */
    if (gs_s32GFX2DDevFd != -1)
    {
        gs_u32GFX2DDevRef++;
        pthread_mutex_unlock(&gs_GFX2DDevMutex);
        return HI_SUCCESS;
    }

    gs_s32GFX2DDevFd = open(gs_pszGFX2DDevPath, O_RDWR, 0);
    if (-1 == gs_s32GFX2DDevFd)
    {
        pthread_mutex_unlock(&gs_GFX2DDevMutex);

        return HI_ERR_GFX2D_DEV_PERMISSION;
    }

    gs_u32GFX2DDevRef++;

    pthread_mutex_unlock(&gs_GFX2DDevMutex);

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_Close(const HI_GFX2D_DEV_ID_E enDevId)
{
    HI_S32 s32Ret;

    s32Ret = pthread_mutex_lock(&gs_GFX2DDevMutex);
    if (HI_SUCCESS != s32Ret)
    {
        return HI_ERR_GFX2D_SYS;
    }

    /* device is not open,return */
    if (-1 == gs_s32GFX2DDevFd)
    {
        pthread_mutex_unlock(&gs_GFX2DDevMutex);
        return HI_SUCCESS;
    }

    if (--gs_u32GFX2DDevRef == 0)
    {
        GFX2D_WAITALLDONE_CMD_S stCmd;

        memset(&stCmd, 0, sizeof(stCmd));

        /*Before close dev, wait all task done!*/
        stCmd.enDevId = enDevId;
        ioctl(gs_s32GFX2DDevFd, GFX2D_WATIALLDONE, &stCmd);
                
        close(gs_s32GFX2DDevFd);
        gs_s32GFX2DDevFd = -1;
        pthread_mutex_unlock(&gs_GFX2DDevMutex);

        return HI_SUCCESS;
    }

    pthread_mutex_unlock(&gs_GFX2DDevMutex);

    return HI_SUCCESS;
}

/*缩放时，输入宽度，高度大于等于2.*/
HI_S32 HI_GFX2D_ComposeSync(const HI_GFX2D_DEV_ID_E enDevId,
                            HI_GFX2D_COMPOSE_LIST_S *pstComposeList, 
                            HI_GFX2D_SURFACE_S *pstDst,
                            const HI_U32 u32Timeout)
{
    HI_S32 s32Ret;
    GFX2D_COMPOSE_CMD_S stCmd;

    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();

    memset(&stCmd, 0, sizeof(stCmd));

    stCmd.enDevId = enDevId;
    stCmd.pstComposeList = pstComposeList;
    stCmd.pstDst = pstDst;
    stCmd.u32Timeout = u32Timeout;
    stCmd.bSync = HI_TRUE;
    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_COMPOSE, &stCmd);
    if (s32Ret < 0)
    {
        return s32Ret;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_ComposeAsync(const HI_GFX2D_DEV_ID_E enDevId, 
                             HI_GFX2D_COMPOSE_LIST_S *pstComposeList, 
                             HI_GFX2D_SURFACE_S *pstDst)
{
    HI_S32 s32Ret;
    GFX2D_COMPOSE_CMD_S stCmd;

    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();

    memset(&stCmd, 0, sizeof(stCmd));

    stCmd.enDevId = enDevId;
    stCmd.pstComposeList = pstComposeList;
    stCmd.pstDst = pstDst;
    stCmd.bSync = HI_FALSE;
    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_COMPOSE, &stCmd);
    if (s32Ret < 0)
    {
        return s32Ret;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_WaitAllDone(const HI_GFX2D_DEV_ID_E enDevId, const HI_U32 u32TimeOut)
{
    HI_S32 s32Ret;
    GFX2D_WAITALLDONE_CMD_S stCmd;

    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();

    memset(&stCmd, 0, sizeof(stCmd));

    stCmd.enDevId = enDevId;
    stCmd.u32Timeout = u32TimeOut;
    s32Ret = ioctl(gs_s32GFX2DDevFd, GFX2D_WATIALLDONE, &stCmd);
    if (s32Ret < 0)
    {
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_GetCmpSurfaceSize(const HI_GFX2D_DEV_ID_E enDevId,
                                  const HI_U32 u32Width, const HI_U32 u32Height, 
                                  const HI_GFX2D_FMT_E enFmt, HI_U32 *pu32Size)
{
    HI_U32 u32Stride;

    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();
    
    if (HI_NULL == pu32Size)
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    if (HI_GFX2D_FMT_ARGB8888 != enFmt)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }

    if ((u32Width < 1) || (u32Width > 2560)
        || (u32Height < 1) || (u32Height > 1600))
    {
        return HI_ERR_GFX2D_INVALID_SURFACE_RESO;
    }

    if (u32Width & 0x1)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }

    u32Stride = ((u32Width * 2 + 0xff) & 0xffffff00);

    *pu32Size = u32Stride * u32Height  + ((u32Stride / 256 + 0xf) & 0xfffffff0) * u32Height;
    *pu32Size *= 2;

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_GetCmpSurfaceStride(const HI_GFX2D_DEV_ID_E enDevId,
                                    const HI_U32 u32Width, const HI_GFX2D_FMT_E enFmt,
                                    HI_U32 *pu32Stride)
{
    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();
    
    if (HI_NULL == pu32Stride)
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    if (HI_GFX2D_FMT_ARGB8888 != enFmt)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }
    
    if ((u32Width < 1) || (u32Width > 2560))
    {
        return HI_ERR_GFX2D_INVALID_SURFACE_RESO;
    }

    if (u32Width & 0x1)
    {
        return HI_ERR_GFX2D_UNSUPPORT;
    }
    
    *pu32Stride = ((u32Width * 2 + 0xff) & 0xffffff00);
    
    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_GetSurfaceDefaultParam(const HI_GFX2D_DEV_ID_E enDevId,
                                       HI_GFX2D_SURFACE_S *pstSurface)
{
    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();
    
    if (HI_NULL == pstSurface)
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    memset(pstSurface, 0, sizeof(HI_GFX2D_SURFACE_S));

    return HI_SUCCESS;
}

HI_S32 HI_GFX2D_GetOptDefaultParam(const HI_GFX2D_DEV_ID_E enDevId,
                                   HI_GFX2D_COMPOSE_OPT_S *pstOpt)
{
    GFX2D_CHECK_DEVID(enDevId);
    
    GFX2D_CHECK_DEVSTATE();

    if (HI_NULL == pstOpt)
    {
        return HI_ERR_GFX2D_NULL_PTR;
    }

    memset(pstOpt, 0, sizeof(HI_GFX2D_COMPOSE_OPT_S));

    return HI_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif  /*__cplusplus*/
#endif  /*__cplusplus*/
