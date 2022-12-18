#include "ttml_parse.h"
#include "tinyxml.h"

#define ELEMENT_COUNT (pstProtocl->u32ParseData0)
#define KEYVP_COUT    (pstProtocl->u32ParseData1)
#define SUBNODE_COUNT (pstProtocl->u32ParseData2)

//#define DUBUG_PRINT

#define TIME_TO_MS(h, m, s, ms) (((h * 60 + m) * 60 + s) * 1000 + ms)

static HI_S32 _TTML_Count_XmlElemmentAttr(TiXmlElement* pElement,HI_SUB_PROTOCOL_S* pstProtocl)
{
    TiXmlAttribute* pAttrib = pElement->FirstAttribute();

    ELEMENT_COUNT++;
    while (pAttrib)
    {
        KEYVP_COUT++;
#ifdef DUBUG_PRINT
        printf( "  %02d    %-20s    %-30s", ELEMENT_COUNT, pAttrib->Name(), pAttrib->Value());
#endif

        pAttrib = pAttrib->Next();
    }

    if (pElement->GetText())
    {
#ifdef DUBUG_PRINT
        printf("     %s", pElement->GetText());
#endif
        SUBNODE_COUNT++;
    }

#ifdef DUBUG_PRINT
    printf("\n");
#endif

    return 0;
}

static HI_S64 _TTML_Get_TimeMs(const HI_CHAR* str)
{
    HI_S32 hour, minute, second, ms;
    HI_S64 timems = 0;
    HI_S32 ret;

    ret = sscanf(str, "%2d:%2d:%2d:%2d", &hour, &minute, &second, &ms);
    if (ret == 4) //格式begin="00:00:20:08"
    {
        if (ms > 30) //
        {
            HI_ERR_SUB("ms error check it:%d!", ms);
        }

        ms = (1000 * ms) / 30; //30 frames per second
        timems = TIME_TO_MS(hour, minute, second, ms);
    }
    else if (ret == 1) //格式begin="45.0s"
    {
        ret = sscanf(str, "%2d.%1ds", &second, &ms);
        if (ret == 2)
        {
            timems = TIME_TO_MS(0, 0, second, ms * 10);
        }
        else
        {
            HI_ERR_SUB("time format not correct!");
            return -1;
        }
    }
    else
    {
        HI_ERR_SUB("time format not correct:%d!", ret);
        return -1;
    }

    return timems;
}

static HI_S32 _TTML_Save_Keyvp(const HI_CHAR *name, const HI_CHAR* value, HI_S32 elecout, HI_SVR_SUB_KeyVP*     pstKeyVPBuf)
{
    HI_U32 namelen  = strlen(name) + 1;
    HI_U32 valuelen = strlen(value) + 1;

    if (namelen > pstKeyVPBuf->u32NameBufflen)
    {
        pstKeyVPBuf->ps8Name = (HI_CHAR*)realloc(pstKeyVPBuf->ps8Name, namelen);
        if (!pstKeyVPBuf->ps8Name)
        {
            HI_ERR_SUB("alloc failed!");
            return -1;
        }

        pstKeyVPBuf->u32NameBufflen = namelen;
    }

    if (valuelen > pstKeyVPBuf->u32ValueBufflen)
    {
        pstKeyVPBuf->ps8Value = (HI_CHAR*)realloc(pstKeyVPBuf->ps8Value, valuelen);
        if (!pstKeyVPBuf->ps8Value)
        {
            HI_ERR_SUB("alloc failed!");
            return -1;
        }

        pstKeyVPBuf->u32ValueBufflen = valuelen;
    }

    strncpy(pstKeyVPBuf->ps8Name, name, namelen);
    strncpy(pstKeyVPBuf->ps8Value, value, valuelen);
    pstKeyVPBuf->ps8Name[namelen - 1]   = '\0';
    pstKeyVPBuf->ps8Value[valuelen - 1] = '\0';
    pstKeyVPBuf->u32NameDatalen  = namelen;
    pstKeyVPBuf->u32ValueDatalen = valuelen;
    pstKeyVPBuf->u32ExtId = elecout;
    return 0;
}

static HI_S32 _TTML_Save_Subnode(const HI_CHAR *txt, HI_S64 startpts, HI_U32 duration, HI_S32 elecount,
                 HI_SVR_SUB_DATA_S*  pstSubNode)
{
    HI_U32 txtlen = strlen(txt) + 1;

    if (txtlen > pstSubNode->u32SubBuffLen)
    {
        pstSubNode->ps8SubtData = (char*)realloc(pstSubNode->ps8SubtData, txtlen);
        if (!pstSubNode->ps8SubtData)
        {
            HI_ERR_SUB("alloc failed!");
            return -1;
        }

        pstSubNode->u32SubBuffLen = txtlen;
    }
    strncpy(pstSubNode->ps8SubtData, txt, txtlen);
    pstSubNode->ps8SubtData[txtlen - 1] = '\0';
    pstSubNode->u32SubDataLen = txtlen;
    pstSubNode->s64PTS = startpts;
    pstSubNode->u32DurationMs = duration;
    pstSubNode->u32ExtId = elecount;
    return 0;
}

//调用该函数前至少需要确保保存node和键值对的数组大小是够用的
static HI_S32 _TTML_Prase_Save_Xml(TiXmlElement* pElement, HI_SUB_PROTOCOL_S* pstProtocl,HI_S64 s64PtsTmpMs)
{
    TiXmlAttribute* pAttrib = pElement->FirstAttribute();
    HI_S64 s64StartTimeMs = 0;
    HI_S64 s64EndTimeMs = 0;
    HI_S32 ret = 0;

    ELEMENT_COUNT++;

    if (pElement->GetText())
    {
        while (pAttrib)
        {
            if (strstr(pAttrib->Name(), "begin")) //开始时间
            {
                s64StartTimeMs = _TTML_Get_TimeMs(pAttrib->Value());
            }
            else if (strstr(pAttrib->Name(), "end"))
            {
                s64EndTimeMs = _TTML_Get_TimeMs(pAttrib->Value());
            }
            else
            {
                ret = _TTML_Save_Keyvp(pAttrib->Name(), pAttrib->Value(), ELEMENT_COUNT,
                                 &pstProtocl->stBuff.pstKeyVPBuf[pstProtocl->stBuff.u32VPDataNum]);
                if (ret != 0)
                {
                    HI_ERR_SUB("save key vp error!\n");
                    return ret;
                }

                pstProtocl->stBuff.u32VPDataNum++;
            }

            pAttrib = pAttrib->Next();
        }

        if ((s64StartTimeMs >= 0) && (s64EndTimeMs > 0) && (s64EndTimeMs > s64StartTimeMs)) //time stamp valid
        {
            ret = _TTML_Save_Subnode(pElement->GetText(), s64StartTimeMs + pstProtocl->s32PtsAdjustValue + s64PtsTmpMs,
                               s64EndTimeMs - s64StartTimeMs, ELEMENT_COUNT,
                               &pstProtocl->stBuff.pstNodeBuf[pstProtocl->stBuff.u32NodeDataNum]);
            if (ret != 0)
            {
                HI_ERR_SUB("save sub node failed!\n");
                return ret;
            }

            pstProtocl->stBuff.u32NodeDataNum++;
        }
        else
        {
            HI_ERR_SUB("time stamp not correct,start:%lld,end:%lld!\n", s64StartTimeMs, s64EndTimeMs);
            return ret;
        }
    }
    else
    {
        while (pAttrib)
        {
            ret = _TTML_Save_Keyvp(pAttrib->Name(), pAttrib->Value(), ELEMENT_COUNT,
                             &pstProtocl->stBuff.pstKeyVPBuf[pstProtocl->stBuff.u32VPDataNum]);
            if (ret != 0)
            {
                HI_ERR_SUB("save key vp error!");
                return ret;
            }

            pstProtocl->stBuff.u32VPDataNum++;

            pAttrib = pAttrib->Next();
        }
    }

    return 0;
}

static HI_S32 _TTML_Dump_Element(TiXmlElement *element, HI_SUB_PROTOCOL_S* pstProtocl, HI_S32 justcount,HI_S64 s64PtsAjustTimeMs)
{
    TiXmlElement* child;
    TiXmlElement* nextslibing;

    if (!element)
        return -1;

    child = element->FirstChildElement();
    nextslibing = element->NextSiblingElement();
    if (justcount) //只计数
    {
        _TTML_Count_XmlElemmentAttr(element,pstProtocl);
    }
    else
    {
        _TTML_Prase_Save_Xml(element, pstProtocl,s64PtsAjustTimeMs);
    }

    if (child)
    {
        _TTML_Dump_Element(child, pstProtocl, justcount,s64PtsAjustTimeMs);
    }

    if (nextslibing)
    {
        _TTML_Dump_Element(nextslibing, pstProtocl, justcount,s64PtsAjustTimeMs);
    }

    return 0;
}

//ttml解析要求调用这个函数前默认完整的xml文件数据已经准备好了
HI_S32 TTML_Parse(HI_SUB_PROTOCOL_S* pstProtocl,HI_S64 s64PtsAjustTimeMs)
{
    TiXmlDocument xmlfile;
    TiXmlElement *RootElement;
    HI_S32 ret = HI_SUCCESS;

    if (!pstProtocl)
    {
        HI_ERR_SUB("pointer is null!");
        return HI_FAILURE;
    }

    if (!pstProtocl->stBuff.u32OrgBufLen || !pstProtocl->stBuff.pu8OrgData)
    {
        HI_ERR_SUB("orginal data is invalid!");
        return HI_FAILURE;
    }


    xmlfile.Parse((const char*)pstProtocl->stBuff.pu8OrgData);
    if (!xmlfile.Error())
    {
        RootElement = xmlfile.RootElement();
        KEYVP_COUT = 0;
        SUBNODE_COUNT = 0;
        ELEMENT_COUNT = 0;
        ret = _TTML_Dump_Element(RootElement, pstProtocl, 1,s64PtsAjustTimeMs); //count the number first
        if (ret != HI_SUCCESS)
        {
            HI_ERR_SUB("call _TTML_Dump_Element failed!");
            return ret;
        }

        if (KEYVP_COUT > pstProtocl->stBuff.u32VPBufNum) //key vp buffer不够保存
        {
            pstProtocl->stBuff.pstKeyVPBuf = (HI_SVR_SUB_KeyVP*)realloc(pstProtocl->stBuff.pstKeyVPBuf, KEYVP_COUT
                                                                        * sizeof(HI_SVR_SUB_KeyVP));
            if (!pstProtocl->stBuff.pstKeyVPBuf)
            {
                HI_ERR_SUB("realloc buffer failed!");
                ret = HI_FAILURE;
                return ret;
            }

            memset(pstProtocl->stBuff.pstKeyVPBuf + pstProtocl->stBuff.u32VPBufNum * sizeof(HI_SVR_SUB_KeyVP), 0,
                   (KEYVP_COUT - pstProtocl->stBuff.u32VPBufNum) * sizeof(HI_SVR_SUB_KeyVP));
            pstProtocl->stBuff.u32VPBufNum = KEYVP_COUT;
        }

        if (SUBNODE_COUNT > pstProtocl->stBuff.u32NodeBufNum) //key vp buffer不够保存
        {
            pstProtocl->stBuff.pstNodeBuf = (HI_SVR_SUB_DATA_S*)realloc(pstProtocl->stBuff.pstNodeBuf, SUBNODE_COUNT
                                                                        * sizeof(HI_SVR_SUB_DATA_S));
            if (!pstProtocl->stBuff.pstNodeBuf)
            {
                HI_ERR_SUB("realloc buffer failed!");
                ret = HI_FAILURE;
                return ret;
            }

            memset(pstProtocl->stBuff.pstNodeBuf + pstProtocl->stBuff.u32NodeBufNum * sizeof(HI_SVR_SUB_DATA_S), 0,
                   (SUBNODE_COUNT - pstProtocl->stBuff.u32NodeBufNum) * sizeof(HI_SVR_SUB_DATA_S));
            pstProtocl->stBuff.u32NodeBufNum = SUBNODE_COUNT;
        }

        KEYVP_COUT = 0;
        SUBNODE_COUNT = 0;
        ELEMENT_COUNT = 0;
        pstProtocl->stBuff.u32NodeDataNum = 0;
        pstProtocl->stBuff.u32VPDataNum = 0;

        ret = _TTML_Dump_Element(RootElement, pstProtocl, 0,s64PtsAjustTimeMs); //count the number first
        if (ret != HI_SUCCESS)
        {
            HI_ERR_SUB("call _TTML_Dump_Element failed!");
            return ret;
        }
    }
    else
    {
        HI_ERR_SUB("prase xml file error!");
    }

    return ret;
}
