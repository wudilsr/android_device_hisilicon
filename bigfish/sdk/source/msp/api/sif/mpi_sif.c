/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : mpi_tvd.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/19
  Description   : 
  History       :
  1.Date        : 2013/11/19
    Author      : w00184692 t00202585
    Modification: Created file
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_mpi_sif.h"
#include "drv_sif_ioctl.h"
#include "hi_drv_struct.h"
#include "hi_module.h"

#ifdef __cplusplus
 #if __cplusplus
    extern "C" {
 #endif
#endif /* __cplusplus */

static HI_S32 g_s32SifDevFd = -1;
static const HI_CHAR g_SifDevName[] = "/dev/" UMAP_DEVNAME_SIF;

static pthread_mutex_t g_SifMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_SIF_LOCK() (HI_VOID)pthread_mutex_lock(&g_SifMutex);
#define HI_SIF_UNLOCK() (HI_VOID)pthread_mutex_unlock(&g_SifMutex); 

#define CHECK_SIF_INIT() \
do {\
    HI_SIF_LOCK(); \
    if (g_s32SifDevFd < 0)\
    {\
        HI_SIF_UNLOCK(); \
        HI_ERR_SIF("Please Init firstly.\n");\
        return HI_FAILURE; \
    } \
    HI_SIF_UNLOCK(); \
} while (0)

#define CHECK_SIF_NULL_PTR(ptr) \
do {\
    if (NULL == (ptr))\
    {\
        HI_ERR_SIF("PTR('%s') is NULL.\n", # ptr); \
        return HI_FAILURE; \
    } \
} while (0)

#define CHECK_SIF_ID_INVALID(ID) \
    do {\
        if (ID != HI_UNF_SIF_ID_0)\
        {\
            HI_ERR_SIF("Please Input Valid ID.\n");\
            return HI_FAILURE; \
        } \
    } while (0)



HI_S32 HI_MPI_SIF_MapBasicAudioStandard(HI_UNF_SIF_STANDARD_TYPE_E enOriginalStandard,
                                    HI_UNF_SIF_STANDARD_TYPE_E *penBasicStandard)
{    
    HI_S32 s32Ret = HI_SUCCESS;

    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(penBasicStandard);    

    switch (enOriginalStandard)
    {
        case HI_UNF_SIF_STANDARD_BG:
        case HI_UNF_SIF_STANDARD_BG_A2:
        case HI_UNF_SIF_STANDARD_BG_NICAM:
            *penBasicStandard = HI_UNF_SIF_STANDARD_BG;
            break;
        case HI_UNF_SIF_STANDARD_I:
            *penBasicStandard = HI_UNF_SIF_STANDARD_I;
            break;            
        case HI_UNF_SIF_STANDARD_DK:
        case HI_UNF_SIF_STANDARD_DK1_A2:
        case HI_UNF_SIF_STANDARD_DK2_A2:
        case HI_UNF_SIF_STANDARD_DK3_A2:
        case HI_UNF_SIF_STANDARD_DK_NICAM:
            *penBasicStandard = HI_UNF_SIF_STANDARD_DK;
            break;        
        case HI_UNF_SIF_STANDARD_L:
            *penBasicStandard = HI_UNF_SIF_STANDARD_L;
            break;  
        case HI_UNF_SIF_STANDARD_M:
        case HI_UNF_SIF_STANDARD_M_BTSC:
        case HI_UNF_SIF_STANDARD_M_A2:
        case HI_UNF_SIF_STANDARD_M_EIA_J:
            *penBasicStandard = HI_UNF_SIF_STANDARD_M;
            break;    
        default:
            break;          
    }

    return s32Ret;    
}

HI_S32 HI_MPI_SIF_Init(HI_VOID)
{

    if (g_s32SifDevFd < 0)
    {
        g_s32SifDevFd = open(g_SifDevName, O_RDWR, 0);
        if (g_s32SifDevFd < 0)    
        {
            HI_FATAL_SIF("OpenSIFDevice err\n");
            g_s32SifDevFd = -1;
            return HI_FAILURE;
        }
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_DeInit(HI_VOID)
{
    HI_SIF_LOCK();

    if (g_s32SifDevFd < 0)
    {
        HI_SIF_UNLOCK();
        return HI_SUCCESS;
    }

    close(g_s32SifDevFd);
    g_s32SifDevFd = -1;
    HI_SIF_UNLOCK();
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_Open(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OPENPARMS_S *pstOpenPara)
{
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_OPEN_PARAM_S stOpenParam;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(pstOpenPara);
    CHECK_SIF_ID_INVALID(enSIf);

    stOpenParam.enSifId = enSIf;
    memcpy(&stOpenParam.stSifOpenParam, pstOpenPara, sizeof(HI_UNF_SIF_OPENPARMS_S));
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_OPEN, &stOpenParam);        
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_Close(HI_UNF_SIF_ID_E enSIf)
{    
    HI_S32  s32Ret    = HI_FAILURE;
    
    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_CLOSE, &enSIf);        
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_SetAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr)
{
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_ATTR_S stAttr;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(pstSifAttr);
    CHECK_SIF_ID_INVALID(enSIf);

    if ((pstSifAttr->bAutoMute != HI_FALSE) && (pstSifAttr->bAutoMute != HI_TRUE))
    {
        HI_ERR_SIF("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        printf("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if ((pstSifAttr->enOutMode >= HI_UNF_SIF_OUTMODE_BUTT))
    {
        HI_ERR_SIF("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        printf("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }

    if ((pstSifAttr->enFreqThreshold >= HI_UNF_SIF_FREQ_ERR_THRESHOLD_BUTT) )
    {
        HI_ERR_SIF("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        printf("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }    

    if ((pstSifAttr->u32PrescaleLevel > 0xff)
        ||(pstSifAttr->u32CarriMgntudeThreshold > 0xff)
        ||(pstSifAttr->u32CarriFMQualThreshold > 0xff)
        ||(pstSifAttr->u32CarriAMNoiseThreshold > 0xff)
        ||(pstSifAttr->u32CarriNICAMNoiseThreshold > 0xff))
    {
        HI_ERR_SIF("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        HI_ERR_SIF("[%s] is invalid parameter.[%d]\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }    

    stAttr.enSifId = enSIf;
    memcpy(&stAttr.stSifAttr, pstSifAttr, sizeof(HI_UNF_SIF_ATTR_S));   
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_ATTR, &stAttr);         
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_GetDefaultAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr)
{
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(pstSifAttr);
    CHECK_SIF_ID_INVALID(enSIf);

    /* ??¨¨?SIF¨º?D?¦Ì?¨¦¨¨?? */
    pstSifAttr->bAutoMute                   = HI_FALSE;
    pstSifAttr->u32PrescaleLevel            = 0;                /*=0?a¡Á??¡¥¦Ì¡Â?¨²¡ê??????a¨º??¡¥¨¦¨¨???¦Ì*/
    pstSifAttr->enOutMode                   = HI_UNF_SIF_OUTMODE_NICAM_FORCED_MONO;    
    pstSifAttr->enFreqThreshold             = HI_UNF_SIF_FREQ_ERR_THRESHOLD_50K;
    pstSifAttr->u32CarriMgntudeThreshold    = 0x19;
    pstSifAttr->u32CarriFMQualThreshold     = 0x1a;
    pstSifAttr->u32CarriAMNoiseThreshold    = 0x09;
    pstSifAttr->u32CarriNICAMNoiseThreshold = 0x1e;   
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_GetAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr)
{
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_ATTR_S stAttr;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(pstSifAttr);
    CHECK_SIF_ID_INVALID(enSIf);

    stAttr.enSifId = enSIf;
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_GET_ATTR, &stAttr);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    memcpy(pstSifAttr, &stAttr.stSifAttr, sizeof(HI_UNF_SIF_ATTR_S));
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_Start(HI_UNF_SIF_ID_E enSIf)
{ 
    HI_S32  s32Ret    = HI_FAILURE;

    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_START, &enSIf);      
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_Stop(HI_UNF_SIF_ID_E enSIf)
{
    HI_S32  s32Ret    = HI_FAILURE;

    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_STOP, &enSIf);     
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_SetStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E enSifStandard)
{
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_STANDARD_TYPE_S stStand;
    
    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);

    if (enSifStandard >= HI_UNF_SIF_STANDARD_NOTSTANDARD)
    {
        return HI_FAILURE;
    }

    stStand.enSifId = enSIf;
    stStand.enStand = enSifStandard;
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_STANDDARD, &stStand);     
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_StartAutoStandardDetection(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_SYSCTL_E enSifDetCtl)
{    
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_SYSCTL_S stSysCtl;
    
    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);

    if (enSifDetCtl >= HI_UNF_SIF_SYSCTL_BUTT)
    {
        return HI_FAILURE;
    }

    stSysCtl.enSifId  = enSIf;
    stSysCtl.enSysCtl = enSifDetCtl;
    
//    printf("enSifDetCtl = %d, __FUNCTION__ = %s, __LINE__ = %d\n\r", enSifDetCtl, __FUNCTION__, __LINE__);

    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_START_ASD, &stSysCtl);     
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n\r", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_GetDetectComplete(HI_UNF_SIF_ID_E enSIf, HI_BOOL *pbAsdComplete)
{
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_ASD_COMPLETE_S stAsdComplete;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(pbAsdComplete);
    CHECK_SIF_ID_INVALID(enSIf);
    
    stAsdComplete.enSifId = enSIf;
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_GET_ASD_CMPL, &stAsdComplete);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    
//    printf("stAsdComplete.bAsdComplete = %d, __FUNCTION__ = %s, __LINE__ = %d\n\r", stAsdComplete.bAsdComplete, __FUNCTION__, __LINE__);
    
    *pbAsdComplete = stAsdComplete.bAsdComplete;
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_GetUserSettingStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E *penSifStandard)
{
    SIF_STANDARD_TYPE_S stStandard;
    HI_S32  s32Ret    = HI_FAILURE;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(penSifStandard);
    CHECK_SIF_ID_INVALID(enSIf);

    stStandard.enSifId = enSIf;
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_GET_STANDARD, &stStandard);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    *penSifStandard = stStandard.enStand;
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_GetAutoDetectStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E *penSifAutoStandard)
{
    SIF_STANDARD_TYPE_S stStandard;
    HI_S32  s32Ret    = HI_FAILURE;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(penSifAutoStandard);
    CHECK_SIF_ID_INVALID(enSIf);

    stStandard.enSifId = enSIf;    
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_GET_ASD_RESULT, &stStandard);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }

//    printf("stStandard.enStand = %d, __FUNCTION__ = %s, __LINE__ = %d\n", stStandard.enStand, __FUNCTION__, __LINE__);
    
    *penSifAutoStandard = stStandard.enStand;
    
    return HI_SUCCESS;
}


HI_S32 HI_MPI_SIF_SetSoundMode(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OUTMODE_E enSifOutmode)
{    
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_OUTMODE_S stOutMode;
    
    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);

    if (enSifOutmode >= HI_UNF_SIF_OUTMODE_BUTT)
    {
        return HI_FAILURE;
    }

    stOutMode.enSifId   = enSIf;
    stOutMode.enOutMode = enSifOutmode;

    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_OUTMODE, &stOutMode);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

HI_S32 HI_MPI_SIF_GetSoundMode(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_AAOS_MODE_E *penSifAAOSmode)
{
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_AAOS_MODE_S stAAOSMode;
    
    CHECK_SIF_INIT();
    CHECK_SIF_NULL_PTR(penSifAAOSmode);
    CHECK_SIF_ID_INVALID(enSIf);

    stAAOSMode.enSifId = enSIf;
    
    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_GET_OUTMODE, &stAAOSMode);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    *penSifAAOSmode = stAAOSMode.enAAOSMode;
//    printf("*penSifAAOSmode = %d, __FUNCTION__ = %s, __LINE__ = %d\n\r", *penSifAAOSmode, __FUNCTION__, __LINE__);
    
    return HI_SUCCESS;
}


HI_S32 HI_MPI_SIF_SetOverDeviation(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OVER_DEVIATION_E enOverDeviation)
{    
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_OVER_DEVIATION_S stOverMod;
    
    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);

    if (enOverDeviation >= HI_UNF_SIF_OVER_DEVIATION_BUTT)
    {
        return HI_FAILURE;
    }

    stOverMod.enSifId    = enSIf;

    switch (enOverDeviation)
    {
        case HI_UNF_SIF_OVER_DEVIATION_50K:        
            stOverMod.enOverMode = SIF_OVER_DEVIATION_50K;
            break;
        case HI_UNF_SIF_OVER_DEVIATION_100K:
            stOverMod.enOverMode = SIF_OVER_DEVIATION_100K;
            break;  
        case HI_UNF_SIF_OVER_DEVIATION_200K:
            stOverMod.enOverMode = SIF_OVER_DEVIATION_200K;
            break;
        case HI_UNF_SIF_OVER_DEVIATION_384K:
            stOverMod.enOverMode = SIF_OVER_DEVIATION_384K;
            break;  
        case HI_UNF_SIF_OVER_DEVIATION_540K:
            stOverMod.enOverMode = SIF_OVER_DEVIATION_540K;
            break;
        default:            
            stOverMod.enOverMode = SIF_OVER_DEVIATION_384K;
            break;
        
    }

    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_OVER_DEV, &stOverMod);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}


HI_S32 HI_MPI_SIF_SetCarriShift(HI_UNF_SIF_ID_E enSIf, HI_U32 u32CarriShift)
{    
    HI_S32  s32Ret    = HI_FAILURE;
    SIF_CARRISHIFT_S stCarriShift;
    
    CHECK_SIF_INIT();
    CHECK_SIF_ID_INVALID(enSIf);

    stCarriShift.enSifId    = enSIf;
    stCarriShift.u32CarriShift = u32CarriShift;

    if (u32CarriShift > 0xffff)
    {        
        HI_ERR_SIF("[%s] is invalid parameter.\n", __FUNCTION__);
        printf("[%s] is invalid parameter.\n", __FUNCTION__);
        return HI_FAILURE;
    }

    s32Ret = ioctl(g_s32SifDevFd, CMD_SIF_SET_CARRI_SHIFT, &stCarriShift);
    if (s32Ret != HI_SUCCESS)
    {
        HI_ERR_SIF("[%s] is return err.\n", __FUNCTION__);
        return HI_FAILURE;
    }
    
    return HI_SUCCESS;
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

