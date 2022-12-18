#include "subparse.h"
#include "ttml_parse.h"
#include "sub_transcode.h"

HI_SUB_PROTOCOL_S subProtocol[MAX_SUB_PARSE_NUM];

static HI_U32 u32InitFlag = 0;

#define SubCheckInitFlag() \
    do {  \
        if (u32InitFlag == 0) \
        {                                  \
            HI_ERR_SUB("[%s,line:%d]sub parase not init yet.\n",__FUNCTION__,__LINE__); \
            return HI_FAILURE;  \
        } \
    } while (0)

#define SubCheckPointer(p) \
    do {  \
        if (HI_NULL == p)\
        {\
            HI_ERR_SUB("[%s,line:%d]pointer parameter is NULL.\n",__FUNCTION__,__LINE__); \
            return HI_FAILURE; \
        } \
    } while (0)

#define SubCheckHandle(h) \
    do {  \
        if (h >= MAX_SUB_PARSE_NUM)\
        {\
            HI_ERR_SUB("[%s,line:%d],invalid handle number:%d.\n",__FUNCTION__,__LINE__,h); \
            return HI_FAILURE; \
        } \
    } while (0)

#define SUB_LOCK(h) \
    do {                                        \
        (void)pthread_mutex_lock(&(h));        \
    } while (0)

#define SUB_UNLOCK(h) \
    do {                                        \
        (void)pthread_mutex_unlock(&(h));      \
    } while (0)

HI_S32 SUB_Parse_Init(HI_VOID)
{
    HI_U32 i;

    if (u32InitFlag)
    {
        return HI_SUCCESS;
    }

#if defined (SUB_TRANSCODE_SUPPORT)
    if (sub_transcode_init() != HI_SUCCESS)
    {
        HI_ERR_SUB("sub_transcode_init failed!\n.\n");
        return HI_FAILURE;
    }
#endif

    memset(subProtocol, 0, MAX_SUB_PARSE_NUM * sizeof(HI_SUB_PROTOCOL_S));
    for (i = 0; i < MAX_SUB_PARSE_NUM; i++)
    {
        pthread_mutex_init(&(subProtocol[i].stSubMutex), NULL);
    }

    u32InitFlag = 1;
    return HI_SUCCESS;
}

HI_S32 SUB_Parse_DeInit(HI_VOID)
{
    HI_U32 i;

    SubCheckInitFlag();
    u32InitFlag = 0;
    for (i = 0; i < MAX_SUB_PARSE_NUM; i++)
    {
        pthread_mutex_destroy(&(subProtocol[i].stSubMutex));
    }

#if defined (SUB_TRANSCODE_SUPPORT)
    sub_transcode_deinit();
#endif

    return HI_SUCCESS;
}

HI_S32 SUB_Parse_Create(HI_SVR_SUB_PARAM_S *pstSubParam, HI_HANDLE *phSub)
{
    HI_U32 i;
    HI_SUB_PROTOCOL_S* pstProtocol;

    SubCheckPointer(pstSubParam);
    SubCheckPointer(phSub);
    SubCheckInitFlag();

    if (pstSubParam->eSubType >= HI_SVR_SUB_TYPE_BUTT)
    {
        //do not surpport subtitle type
        HI_ERR_SUB("do not surpport subtitle type:%d\n.\n", pstSubParam->eSubType);
        return HI_FAILURE;
    }

    for (i = 0; i < MAX_SUB_PARSE_NUM; i++)
    {
        if (!subProtocol[i].u32UseFlag)
        {
            break;
        }
    }

    if (i >= MAX_SUB_PARSE_NUM)
    {
        HI_ERR_SUB("the sub num is max:%d\n", MAX_SUB_PARSE_NUM);
        return HI_FAILURE;
    }

    pstProtocol = &subProtocol[i];
    SUB_LOCK(pstProtocol->stSubMutex);

    switch (pstSubParam->eSubType)
    {
    case  HI_SVR_SUB_TYPE_TTML:
        pstProtocol->pfnParseCb = (HI_SUB_PRASE_FN)TTML_Parse;
        if (pstProtocol->pfnReadCb)
        {
            HI_ERR_SUB("ttml do not surport read data in callback!\n");
            SUB_UNLOCK(pstProtocol->stSubMutex);
            return HI_FAILURE;
        }

        break;
    default:
        pstProtocol->pfnParseCb = HI_NULL;
    }

    if (!pstProtocol->pfnParseCb)
    {
        HI_ERR_SUB("parase function is null!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    pstProtocol->stBuff.pu8OrgData  = malloc(DEFAULT_ORG_BUF_LEN); //预先分配原始数据buffer
    pstProtocol->stBuff.pstKeyVPBuf = malloc(DEFAULT_KEY_VP_NUM * sizeof(HI_SVR_SUB_KeyVP)); //预分配键值对数组
    pstProtocol->stBuff.pstNodeBuf = malloc(DEFAULT_NODE_NUM * sizeof(HI_SVR_SUB_DATA_S));
    if ((pstProtocol->stBuff.pu8OrgData == HI_NULL) || (pstProtocol->stBuff.pstKeyVPBuf == HI_NULL)
        || pstProtocol->stBuff.pstNodeBuf  == HI_NULL)
    {
        if (pstProtocol->stBuff.pu8OrgData)
        {
            free(pstProtocol->stBuff.pu8OrgData);
            pstProtocol->stBuff.pu8OrgData = HI_NULL;
        }

        if (pstProtocol->stBuff.pstKeyVPBuf)
        {
            free(pstProtocol->stBuff.pstKeyVPBuf);
            pstProtocol->stBuff.pstKeyVPBuf = HI_NULL;
        }

        if (pstProtocol->stBuff.pstNodeBuf)
        {
            free(pstProtocol->stBuff.pstNodeBuf);
            pstProtocol->stBuff.pstNodeBuf = HI_NULL;
        }

        HI_ERR_SUB("malloc buffer failed!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    pstProtocol->stBuff.u32OrgBufLen  = DEFAULT_ORG_BUF_LEN;
    pstProtocol->stBuff.u32OrgDataLen = 0;
    pstProtocol->stBuff.u32VPBufNum  = DEFAULT_KEY_VP_NUM;
    pstProtocol->stBuff.u32VPDataNum = 0;
    memset(pstProtocol->stBuff.pstKeyVPBuf, 0, DEFAULT_KEY_VP_NUM * sizeof(HI_SVR_SUB_KeyVP));
    pstProtocol->stBuff.u32NodeBufNum  = DEFAULT_NODE_NUM;
    pstProtocol->stBuff.u32NodeDataNum = 0;
    memset(pstProtocol->stBuff.pstNodeBuf, 0, DEFAULT_NODE_NUM * sizeof(HI_SVR_SUB_DATA_S));
    pstProtocol->eSubType    = pstSubParam->eSubType;
    pstProtocol->pfnReadCb   = pstSubParam->pfnReadCb;
    pstProtocol->pfnSeekCb   = pstSubParam->pfnSeekCb;
    pstProtocol->u32UserData = pstSubParam->u32UserData;
    pstProtocol->s32PtsAdjustValue = pstSubParam->s32PtsAdjustValue;
    pstProtocol->u32UseFlag  = 1;
    pstProtocol->u32QuitFlag = 0;
    *phSub = i;
    SUB_UNLOCK(pstProtocol->stSubMutex);
    return HI_SUCCESS;
}

HI_S32 SUB_Parse_Destroy(HI_HANDLE hSub)
{
    HI_SUB_PROTOCOL_S* pstProtocol;
    HI_U32 i;

    SubCheckHandle(hSub);
    SubCheckInitFlag();
    pstProtocol = &subProtocol[hSub];
    SUB_LOCK(pstProtocol->stSubMutex);
    if (!pstProtocol->u32UseFlag)
    {
        HI_ERR_SUB("protocol not in use!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }
    if (pstProtocol->stBuff.pu8OrgData) //free org data buffer
    {
        free(pstProtocol->stBuff.pu8OrgData);
    }

    if (pstProtocol->stBuff.pstNodeBuf) //free node data buffer
    {
        for (i = 0; i < pstProtocol->stBuff.u32NodeBufNum; i++)
        {
            if (pstProtocol->stBuff.pstNodeBuf[i].ps8SubtData)
            {
                free(pstProtocol->stBuff.pstNodeBuf[i].ps8SubtData);
            }
        }

        free(pstProtocol->stBuff.pstNodeBuf);
    }

    if (pstProtocol->stBuff.pstKeyVPBuf) //free key vp data buffer
    {
        for (i = 0; i < pstProtocol->stBuff.u32VPBufNum; i++)
        {
            if (pstProtocol->stBuff.pstKeyVPBuf[i].ps8Name)
            {
                free(pstProtocol->stBuff.pstKeyVPBuf[i].ps8Name);
            }

            if (pstProtocol->stBuff.pstKeyVPBuf[i].ps8Value)
            {
                free(pstProtocol->stBuff.pstKeyVPBuf[i].ps8Value);
            }
        }

        free(pstProtocol->stBuff.pstKeyVPBuf);
    }

    pstProtocol->eSubType    = HI_SVR_SUB_TYPE_BUTT;
    pstProtocol->pfnReadCb   = NULL;
    pstProtocol->pfnSeekCb   = NULL;
    pstProtocol->u32UserData = 0;
    pstProtocol->s32PtsAdjustValue = 0;
    pstProtocol->u32UseFlag = 0;
    SUB_UNLOCK(pstProtocol->stSubMutex);
    return HI_SUCCESS;
}

static HI_VOID replace_br(HI_U8* pData, HI_U32 u32DataLen)//replace "<br/>" as " /n   "
{
    HI_CHAR* br = "<br/>";
    HI_CHAR* p = HI_NULL;

    while(1)
    {
        p = strstr((char*)pData,br);

        if (p && ((HI_U32)(p + 5) < (HI_U32)(pData + u32DataLen)))
        {
            p[0] = ' ';
            p[1] = '//';
            p[2] = 'n';
            p[3] = ' ';
            p[4] = ' ';
        }
        else
        {
            return;
        }
    }

}

HI_S32 SUB_Parse_SendData(HI_HANDLE hSub, HI_U8* pData, HI_U32 u32DataLen)
{
    HI_SUB_PROTOCOL_S* pstProtocol;

    SubCheckHandle(hSub);
    SubCheckInitFlag();
    SubCheckPointer(pData);
    pstProtocol = &subProtocol[hSub];

    SUB_LOCK(pstProtocol->stSubMutex);
    if (!pstProtocol->u32UseFlag)
    {
        HI_ERR_SUB("protocol not in use!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    if (!u32DataLen)
    {
        HI_ERR_SUB("copy len is zero!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    if (pstProtocol->pfnReadCb) //如果有读数据回调则改接口无效
    {
        HI_ERR_SUB("do not insert data when read callback is valid!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }
    replace_br(pData,u32DataLen);

    if ((pstProtocol->stBuff.u32OrgDataLen + u32DataLen) > pstProtocol->stBuff.u32OrgBufLen)
    {
        //buffer不够，remalloc
        pstProtocol->stBuff.pu8OrgData = realloc(pstProtocol->stBuff.pu8OrgData, pstProtocol->stBuff.u32OrgDataLen
                                                 + u32DataLen);
        if (HI_NULL == pstProtocol->stBuff.pu8OrgData)
        {
            pstProtocol->stBuff.u32OrgDataLen = 0;
            pstProtocol->stBuff.u32OrgBufLen = 0;
            HI_ERR_SUB("remalloc size:%d failed!\n", pstProtocol->stBuff.u32OrgDataLen + u32DataLen);
            SUB_UNLOCK(pstProtocol->stSubMutex);
            return HI_FAILURE;
        }

        pstProtocol->stBuff.u32OrgBufLen = pstProtocol->stBuff.u32OrgDataLen + u32DataLen;
    }

    memcpy(pstProtocol->stBuff.pu8OrgData + pstProtocol->stBuff.u32OrgDataLen, pData, u32DataLen);
    pstProtocol->stBuff.u32OrgDataLen += u32DataLen;
    SUB_UNLOCK(pstProtocol->stSubMutex);
    return HI_SUCCESS;
}

HI_S32 SUB_Parse_Reset(HI_HANDLE hSub)
{
    HI_SUB_PROTOCOL_S* pstProtocol;

    SubCheckHandle(hSub);
    SubCheckInitFlag();
    pstProtocol = &subProtocol[hSub];

    SUB_LOCK(pstProtocol->stSubMutex);
    if (!pstProtocol->u32UseFlag)
    {
        HI_ERR_SUB("protocol not in use!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    pstProtocol->stBuff.u32OrgDataLen = 0;
    SUB_UNLOCK(pstProtocol->stSubMutex);
    return HI_SUCCESS;
}

HI_S32 SUB_Parse_ReadSubNodes(HI_HANDLE hSub, HI_S64 s64PtsAjustTimeMs, HI_SVR_SUB_DATA_S** pstSubNode,
                                 HI_U32* pu32NodeNum,
                                 HI_SVR_SUB_KeyVP** pstSubKeyVpBuf,
                                 HI_U32* pu32KeyVpNum)
{
    HI_SUB_PROTOCOL_S* pstProtocol;
    HI_S32 ret;

    SubCheckHandle(hSub);
    SubCheckInitFlag();
    SubCheckPointer(pu32NodeNum);
    SubCheckPointer(pu32KeyVpNum);

    pstProtocol = &subProtocol[hSub];

    SUB_LOCK(pstProtocol->stSubMutex);
    if (!pstProtocol->u32UseFlag)
    {
        HI_ERR_SUB("protocol not in use!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    if (!pstProtocol->pfnReadCb && !pstProtocol->stBuff.u32OrgDataLen) //没有回调且没有数据
    {
        HI_ERR_SUB("no data here!\n");
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }

    if (pstProtocol->stBuff.u32OrgDataLen != 0)
    {
        //if the data is not utf8,transcode here.Use api sub_transcode_data.
    }

    ret = pstProtocol->pfnParseCb((HI_VOID*)pstProtocol,s64PtsAjustTimeMs);
    if (ret == HI_SUCCESS)
    {
        *pstSubNode     = pstProtocol->stBuff.pstNodeBuf;
        *pu32NodeNum   = pstProtocol->stBuff.u32NodeDataNum;
        *pstSubKeyVpBuf = pstProtocol->stBuff.pstKeyVPBuf;
        *pu32KeyVpNum  = pstProtocol->stBuff.u32VPDataNum;
    }
    else
    {
        HI_ERR_SUB("prase data failed:%x!\n", ret);
        *pu32NodeNum  = 0;
        *pu32KeyVpNum = 0;
        pstProtocol->stBuff.u32OrgDataLen = 0;
        SUB_UNLOCK(pstProtocol->stSubMutex);
        return HI_FAILURE;
    }
    pstProtocol->stBuff.u32OrgDataLen = 0;
    SUB_UNLOCK(pstProtocol->stSubMutex);
    return HI_SUCCESS;
}

//do not use mutex here
HI_S32 SUB_Parse_QuickQuitRequest(HI_HANDLE hSub)
{
    HI_SUB_PROTOCOL_S* pstProtocol;

    SubCheckHandle(hSub);
    SubCheckInitFlag();
    pstProtocol = &subProtocol[hSub];
    if (!pstProtocol->u32UseFlag)
    {
        HI_ERR_SUB("protocol not in use!\n");
        return HI_FAILURE;
    }

    pstProtocol->u32QuitFlag = 1;
    return HI_SUCCESS;
}
