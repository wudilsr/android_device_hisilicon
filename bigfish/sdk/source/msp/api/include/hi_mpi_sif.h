/******************************************************************************

  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_mpi_tvd.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2013/11/19
  Description   : 
  History       :
  1.Date        : 2013/11/19
    Author      : w00184692
    Modification: Created file
******************************************************************************/
#ifndef __HI_MPI_SIF_H__
#define __HI_MPI_SIF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_unf_sif.h"

HI_S32    HI_MPI_SIF_MapBasicAudioStandard(HI_UNF_SIF_STANDARD_TYPE_E enOriginalStandard,
                                           HI_UNF_SIF_STANDARD_TYPE_E *penBasicStandard);
HI_S32    HI_MPI_SIF_Init(HI_VOID);
HI_S32    HI_MPI_SIF_DeInit(HI_VOID);
HI_S32    HI_MPI_SIF_Open(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OPENPARMS_S *pstOpenPara);
HI_S32    HI_MPI_SIF_Close(HI_UNF_SIF_ID_E enSIf);
HI_S32    HI_MPI_SIF_GetDefaultAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr);
HI_S32    HI_MPI_SIF_SetAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr);
HI_S32    HI_MPI_SIF_GetAttr(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_ATTR_S *pstSifAttr);
HI_S32    HI_MPI_SIF_Start(HI_UNF_SIF_ID_E enSIf);
HI_S32    HI_MPI_SIF_Stop(HI_UNF_SIF_ID_E enSIf);
HI_S32    HI_MPI_SIF_SetStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E enSifStandard);
HI_S32    HI_MPI_SIF_StartAutoStandardDetection(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_SYSCTL_E enSifDetCtl);
HI_S32    HI_MPI_SIF_GetDetectComplete(HI_UNF_SIF_ID_E enSIf, HI_BOOL *pbAsdComplete);
HI_S32    HI_MPI_SIF_GetUserSettingStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E *penSifStandard);
HI_S32    HI_MPI_SIF_GetAutoDetectStandard(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_STANDARD_TYPE_E *penSifAutoStandard);
HI_S32    HI_MPI_SIF_SetSoundMode(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OUTMODE_E enSifOutmode);
HI_S32    HI_MPI_SIF_GetSoundMode(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_AAOS_MODE_E *penSifAAOSmode);
HI_S32    HI_MPI_SIF_SetOverDeviation(HI_UNF_SIF_ID_E enSIf, HI_UNF_SIF_OVER_DEVIATION_E enOverDeviation);
HI_S32    HI_MPI_SIF_SetCarriShift(HI_UNF_SIF_ID_E enSIf, HI_U32 u32CarriShift);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

