#include "hi_svr_subparse.h"
#include "subparse.h"

HI_S32 HI_SVR_SUB_Parse_Init(HI_VOID)
{
    return SUB_Parse_Init();
}

HI_S32 HI_SVR_SUB_Parse_DeInit(HI_VOID)
{
    return SUB_Parse_DeInit();
}

HI_S32 HI_SVR_SUB_Parse_Create(HI_SVR_SUB_PARAM_S *pstSubParam, HI_HANDLE *phSub)
{
    return SUB_Parse_Create(pstSubParam, phSub);
}

HI_S32 HI_SVR_SUB_Parse_Destroy(HI_HANDLE hSub)
{
    return SUB_Parse_Destroy(hSub);
}

HI_S32 HI_SVR_SUB_Parse_Reset(HI_HANDLE hSub)
{
    return SUB_Parse_Reset(hSub);
}

HI_S32 HI_SVR_SUB_Parse_ReadSubNodes(HI_HANDLE hSub,HI_S64 s64PtsAjustTimeMs,  HI_SVR_SUB_DATA_S **pstSubNodeBuf,
                                     HI_U32 *pu32NodeNum,
                                     HI_SVR_SUB_KeyVP** pstSubKeyVpBuf,
                                     HI_U32* pu32KeyVpNum)
{
    return SUB_Parse_ReadSubNodes(hSub,s64PtsAjustTimeMs, pstSubNodeBuf, pu32NodeNum, pstSubKeyVpBuf, pu32KeyVpNum);
}

HI_S32 HI_SVR_SUB_Parse_SendData(HI_HANDLE hSub, HI_U8* pData, HI_U32 u32DataLen)
{
    return SUB_Parse_SendData(hSub, pData, u32DataLen);
}

HI_S32 HI_SVR_SUB_Parse_QuickQuitRequest (HI_HANDLE hSub)
{
    return SUB_Parse_QuickQuitRequest(hSub);
}
