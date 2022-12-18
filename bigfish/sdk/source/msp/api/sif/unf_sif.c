/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : unf_tvd.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/12/11
  Description   : 
  History       :
  1.Date        : 2013/12/11
    Author      : m00196336 z0040717
    Modification: Created file
******************************************************************************/

#ifdef __cplusplus
 #if __cplusplus
    extern "C" {
 #endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_unf_sif.h"
#include "hi_mpi_sif.h"

HI_S32 HI_UNF_SIF_MapBasicAudioStandard(HI_UNF_SIF_STANDARD_TYPE_E enOriginalStandard,
                                           HI_UNF_SIF_STANDARD_TYPE_E *penBasicStandard)
{
    return HI_MPI_SIF_MapBasicAudioStandard(enOriginalStandard, penBasicStandard);
}

HI_S32 HI_UNF_SIF_Init(HI_VOID)
{
    return HI_MPI_SIF_Init();
}

HI_S32 HI_UNF_SIF_DeInit(HI_VOID)
{
    return HI_MPI_SIF_DeInit();
}

HI_S32 HI_UNF_SIF_Open(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OPENPARMS_S *pstOpenPara)
{
    return HI_MPI_SIF_Open(enSIf, pstOpenPara);
}

HI_S32 HI_UNF_SIF_Close(HI_UNF_SIF_ID_E enSIf)
{
    return HI_MPI_SIF_Close(enSIf);
}

HI_S32 HI_UNF_SIF_SetAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr)
{
    return HI_MPI_SIF_SetAttr(enSIf, pstSifAttr);
}
    
HI_S32 HI_UNF_SIF_GetDefaultAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr)
{    
    return HI_MPI_SIF_GetDefaultAttr(enSIf, pstSifAttr); 
}

HI_S32 HI_UNF_SIF_GetAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr)
{
    return HI_MPI_SIF_GetAttr(enSIf, pstSifAttr);
}

HI_S32 HI_UNF_SIF_Start(HI_UNF_SIF_ID_E enSIf)
{
    return HI_MPI_SIF_Start(enSIf);
}

HI_S32 HI_UNF_SIF_Stop(HI_UNF_SIF_ID_E enSIf)
{
    return HI_MPI_SIF_Stop(enSIf);
}

HI_S32 HI_UNF_SIF_SetStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E enSifStandard)
{
    return HI_MPI_SIF_SetStandard(enSIf, enSifStandard);
}

HI_S32 HI_UNF_SIF_StartAutoStandardDetection(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_SYSCTL_E enSifDetCtl)
{
    return HI_MPI_SIF_StartAutoStandardDetection(enSIf, enSifDetCtl);
}

HI_S32 HI_UNF_SIF_GetDetectComplete(HI_UNF_SIF_ID_E enSIf, HI_BOOL *pbAsdComplete)
{
    return HI_MPI_SIF_GetDetectComplete(enSIf, pbAsdComplete);
}

HI_S32 HI_UNF_SIF_GetUserSettingStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E *penSifStandard)
{
    return HI_MPI_SIF_GetUserSettingStandard(enSIf, penSifStandard);
}

HI_S32 HI_UNF_SIF_GetAutoDetectStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E *penSifAutoStandard)
{
    return HI_MPI_SIF_GetAutoDetectStandard(enSIf, penSifAutoStandard);
}

HI_S32 HI_UNF_SIF_SetSoundMode(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OUTMODE_E enSifOutmode)
{
    return HI_MPI_SIF_SetSoundMode(enSIf, enSifOutmode);
}

HI_S32 HI_UNF_SIF_GetSoundMode(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_AAOS_MODE_E *penSifOutmode)
{
    return HI_MPI_SIF_GetSoundMode(enSIf, penSifOutmode);
}

HI_S32 HI_UNF_SIF_SetOverDeviation(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OVER_DEVIATION_E enOverDeviation)
{
    return HI_MPI_SIF_SetOverDeviation(enSIf, enOverDeviation);
}

HI_S32 HI_UNF_SIF_SetCarriShift(HI_UNF_SIF_ID_E enSIf, HI_U32 u32CarriShift)
{
    return HI_MPI_SIF_SetCarriShift(enSIf, u32CarriShift);
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

