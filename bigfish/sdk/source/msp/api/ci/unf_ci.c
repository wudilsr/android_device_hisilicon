/**********************************************************************

  Copyright (C), 2004-2014, Hisilicon Tech. Co., Ltd.

 ***********************************************************************
  File Name     : unf_ci.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2014/01/17
  Description   : 
  History       :
  1.Date        : 2014/01/17
    Author      : z00268517
    Modification: Created file
***********************************************************************/
#include "hi_mpi_ci.h"

HI_S32 HI_UNF_CI_Init(HI_VOID)
{
    return HI_MPI_CI_Init();
}

HI_S32 HI_UNF_CI_DeInit(HI_VOID)
{
    return HI_MPI_CI_DeInit();
}

HI_S32 HI_UNF_CI_Open(HI_UNF_CI_PORT_E enCIPort)
{
    CHECK_CIPORT_VALID(enCIPort);

    return HI_MPI_CI_Open(enCIPort);
}

HI_S32 HI_UNF_CI_Close(HI_UNF_CI_PORT_E enCIPort)
{
    CHECK_CIPORT_VALID(enCIPort);

    return HI_MPI_CI_Close(enCIPort);
}

HI_S32 HI_UNF_CI_PCCD_Open(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_Open(enCIPort, enCardId);
}

HI_S32 HI_UNF_CI_PCCD_Close(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_Close(enCIPort, enCardId);
}

HI_S32 HI_UNF_CI_SetAttr(HI_UNF_CI_PORT_E enCIPort, const HI_UNF_CI_ATTR_S *pstCIAttr)
{
    CHECK_CIPORT_VALID(enCIPort);
    
    return HI_MPI_CI_SetAttr(enCIPort, pstCIAttr);
}

HI_S32 HI_UNF_CI_GetAttr(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_ATTR_S *pstCIAttr)
{
    CHECK_CIPORT_VALID(enCIPort);
    
    return HI_MPI_CI_GetAttr(enCIPort, pstCIAttr);
}

HI_S32 HI_UNF_CI_PCCD_CtrlPower(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                                HI_UNF_CI_PCCD_CTRLPOWER_E enCtrlPower)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);
    
    if (enCtrlPower >= HI_UNF_CI_PCCD_CTRLPOWER_BUFF)
    {
        HI_ERR_CI("Invalid enCtrlPower.\n");
        return HI_ERR_CI_INVALID_PARA;
    }
    
    return HI_MPI_CI_PCCD_CtrlPower(enCIPort, enCardId, enCtrlPower);
}

HI_S32 HI_UNF_CI_PCCD_Reset(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_Reset(enCIPort, enCardId);
}

HI_S32 HI_UNF_CI_PCCD_IsReady(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                              HI_UNF_CI_PCCD_READY_E_PTR penCardReady)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_IsReady(enCIPort, enCardId, penCardReady);
}

HI_S32 HI_UNF_CI_PCCD_Detect(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                             HI_UNF_CI_PCCD_STATUS_E_PTR penCardStatus)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_Detect(enCIPort, enCardId, penCardStatus);
}

HI_S32 HI_UNF_CI_PCCD_SetAccessMode(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                                    HI_UNF_CI_PCCD_ACCESSMODE_E enAccessMode)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);
    
    if (enAccessMode >= HI_UNF_CI_PCCD_ACCESS_BUTT)
    {
        HI_ERR_CI("Invalid enAccessMode.\n");
        return HI_ERR_CI_INVALID_PARA;
    }

    return HI_MPI_CI_PCCD_SetAccessMode(enCIPort, enCardId, enAccessMode);
}

HI_S32 HI_UNF_CI_PCCD_GetStatus(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                                HI_UNF_CI_PCCD_STATUS_BIT_E enStatus, HI_U8 *pu8Value)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);
    
    if (enStatus >= HI_UNF_CI_PCCD_STATUS_BIT_BUTT)
    {
        HI_ERR_CI("Invalid enStatus.\n");
        return HI_ERR_CI_INVALID_PARA;
    }

    return HI_MPI_CI_PCCD_GetStatus(enCIPort, enCardId, enStatus, pu8Value);
}

HI_S32 HI_UNF_CI_PCCD_IORead(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                             HI_U8 *pu8Buffer, HI_U32 *pu32ReadLen)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_IORead(enCIPort, enCardId, pu8Buffer, pu32ReadLen);
}

HI_S32 HI_UNF_CI_PCCD_IOWrite(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                              HI_U8 *pu8Buffer, HI_U32 u32WriteLen, HI_U32 *pu32WriteOKLen)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_IOWrite(enCIPort, enCardId, pu8Buffer, 
        u32WriteLen, pu32WriteOKLen);
}

HI_S32 HI_UNF_CI_PCCD_CheckCIS(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_CheckCIS(enCIPort, enCardId);
}

HI_S32 HI_UNF_CI_PCCD_WriteCOR(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_WriteCOR(enCIPort, enCardId);
}

HI_S32 HI_UNF_CI_PCCD_IOReset(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    return HI_MPI_CI_PCCD_IOReset(enCIPort, enCardId);
}

HI_S32 HI_UNF_CI_PCCD_NegBufferSize(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                                    HI_U16 *pu16BufferSize)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);
    return HI_MPI_CI_PCCD_NegBufferSize(enCIPort, enCardId, pu16BufferSize);
}

HI_S32 HI_UNF_CI_PCCD_TSCtrl(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId,
                             HI_UNF_CI_PCCD_TSCTRL_E enCMD, HI_UNF_CI_PCCD_TSCTRL_PARAM_U *pParam)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);

    if (enCMD >= HI_UNF_CI_PCCD_TSCTRL_BUTT)
    {
        HI_ERR_CI("Invalid enCMD.\n");
        return HI_ERR_CI_INVALID_PARA;
    }

    return HI_MPI_CI_PCCD_TSCtrl(enCIPort, enCardId, enCMD, pParam);
}

HI_S32 HI_UNF_CI_PCCD_GetCIS(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId, HI_U8 *pu8CisBuffer, HI_U32 *pu32CisLen)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);
    
    return HI_MPI_CI_PCCD_GetCIS(enCIPort, enCardId, pu8CisBuffer, pu32CisLen);
}


HI_S32 HI_UNF_CI_PCCD_WriteCOREx(HI_UNF_CI_PORT_E enCIPort, HI_UNF_CI_PCCD_E enCardId, HI_U16 u16Addr, HI_U8 u8Data)
{
    CHECK_CIPORT_VALID(enCIPort);
    CHECK_PCCD_VALID(enCardId);
    
    return HI_MPI_CI_PCCD_WriteCOREx(enCIPort, enCardId, u16Addr, u8Data);
}

