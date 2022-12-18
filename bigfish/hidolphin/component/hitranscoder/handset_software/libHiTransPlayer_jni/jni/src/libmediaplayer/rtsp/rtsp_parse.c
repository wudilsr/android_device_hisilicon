#include "rtsp_client.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hies_proto.h"
#include "HiMLoger.h"

#define TAG "Rtsp_parse"

/*获取sdp(session description protocol)中字段类型*/
/*get the sdp attribute key type*/
 void RTSP_Attribute_ParseStype(U8* pStrParsechr,RTSP_PARSE_ATTRIBUTE_S *struAttribute)
{
      switch(*pStrParsechr)
            {
                case 'v':
                     struAttribute->eStype= SDP_V;
                     break;
               case 'o':
                    struAttribute->eStype = SDP_O;
                    break;
               case 's':
                    struAttribute->eStype = SDP_S;
                    break;
               case 'c':
                     struAttribute->eStype= SDP_C;
                    break;
               case 't':
                     struAttribute->eStype= SDP_T;
                   break;
               case 'm':
                   struAttribute->eStype= SDP_M;
                   break;
              case 'a':
                    struAttribute->eStype = SDP_A;
                   break;
              default:
                     struAttribute->eStype = OTHER;
            }
}

/*解析"key=value"模式属性*/
/*parse pattern "key=value"*/
void RTSP_Parse_SingleLine(U8 *strParseAddr,S32 s32Addrlen,
                                        RTSP_PARSE_UTIL_S* self,S32* ParseIndex)
{
        U8             strAddr[128];
        U8*             pstrIndex;
        U8*             pstrAddrStart;
        S32             s32CopyAddrLen;
        RTSP_PARSE_ATTRIBUTE_S* pstruAttribute;
        pstruAttribute = self->struAttribute+ *ParseIndex;
       memset(strAddr,0,sizeof(strAddr));
    memcpy(strAddr,strParseAddr,s32Addrlen);
        strAddr[s32Addrlen] = 0;
        if(!strchr(strAddr,'='))
        {
            MMLOGI(TAG,"RTSP_Parse_SingleLine not support str is %s\n",strAddr);
            return ;
        }
        if(NULL == (pstrIndex = strchr(strAddr,':')))
        {
                pstrIndex = strchr(strAddr,'=');
                pstrIndex--;
                memcpy(pstruAttribute->strKey,strAddr, pstrIndex - strAddr + 1);
                pstruAttribute->strKey[pstrIndex - strAddr+1] = 0;
        }
        else
        {
                pstrAddrStart = strchr(strAddr,'=');
                pstrAddrStart++;
                pstrIndex = strchr(strAddr,':');
                pstrIndex--;
                memcpy(pstruAttribute->strKey,pstrAddrStart,pstrIndex - pstrAddrStart);
                 pstruAttribute->strKey[pstrIndex - pstrAddrStart] = 0;
        }
        pstrIndex+= 2;
        s32CopyAddrLen = strAddr+s32Addrlen - pstrIndex;
        if(s32CopyAddrLen >64)
        {
            MMLOGI(TAG,"Value is %s\n",pstrIndex);
            //sleep(10);
        }
        memcpy(  pstruAttribute->strValue,pstrIndex,s32CopyAddrLen);
          pstruAttribute->strValue[s32CopyAddrLen] = 0;

        return;
}

/*解析字串中的所有属性集，包括sdp解析*/
/* pare all the attributes lines, include sdp */
S32 RTSP_Attribute_Parse(U8* strParseArg,S32* RTSPStatus,RTSP_PARSE_UTIL_S* self)
{
    int        i;
    U8*     pStrParseArg;
    U8*     pStrParseTmp;
    U8*     pStrParsechr;
    U8*     pStrParseFocus;
    S32      s32RtspStatus;
    S32      s32StrParseLen = 0;
    S32      s32StrCompLen = 0;
    S32      S32LastAttributeNum = 0;
    S32       s32StrTotalLen = strlen(strParseArg);

    pStrParseArg = strParseArg;

    if(NULL == (pStrParseTmp = strstr(pStrParseArg,"RTSP/1.0")))
    {
        MMLOGI(TAG,"RTSP Response String error\n");
        return ERR_RTSP_PARAMETER;
    }

    pStrParseTmp += strlen("RTSP/1.0");
    s32RtspStatus = atoi(pStrParseTmp);
    MMLOGI(TAG,"the RTSP status is %d\n",s32RtspStatus);
    *RTSPStatus = s32RtspStatus;
    self->s32AttbriNum = 0;

    if(NULL != (pStrParseTmp = strstr(pStrParseArg,"Content-Length:")))
    {
        pStrParseTmp += strlen("Content-Length:");
        s32StrParseLen = atoi(pStrParseTmp);
        MMLOGI(TAG,"the RTSP Len is %d\n",s32StrParseLen);
    }
    pStrParseTmp = strstr(pStrParseArg,"\r\n");
    pStrParseTmp += 2;
    s32StrCompLen = pStrParseTmp - pStrParseArg;
    while(s32StrCompLen < s32StrTotalLen && pStrParseArg[s32StrCompLen] != '\0')
    {
        RTSP_PARSE_ATTRIBUTE_S *pstruAttribute;
        pstruAttribute = self->struAttribute+S32LastAttributeNum;
        if((NULL != (pStrParsechr = strchr(pStrParseTmp,':')) )&& (pStrParsechr < strstr(pStrParseTmp,"\r\n")))
        {
            MMLOGI(TAG,"Base Attribute\t");
            pstruAttribute->eStype = BASE;
            memcpy(pstruAttribute->strKey,pStrParseTmp,pStrParsechr -pStrParseTmp);
            pstruAttribute->strKey[pStrParsechr -pStrParseTmp] = '\0';
            MMLOGI(TAG,"Key:%s\t",pstruAttribute->strKey);
            pStrParseTmp = strstr(pStrParseTmp,"\r\n");
            pStrParsechr++;
            memcpy(pstruAttribute->strValue,pStrParsechr,pStrParseTmp - pStrParsechr);
            pstruAttribute->strValue[pStrParseTmp - pStrParsechr] = '\0';
            MMLOGI(TAG,"Value:%s\n", pstruAttribute->strValue);
            S32LastAttributeNum ++;
            self->s32AttbriNum++;
            pStrParseTmp += strlen("\r\n");
            if(0 == memcmp(pStrParseTmp,"\r\n",2))
                pStrParseTmp += strlen("\r\n");
            s32StrCompLen = pStrParseTmp - pStrParseArg;
            continue;
        }
        RTSP_Attribute_ParseStype(pStrParseTmp,pstruAttribute);
        pStrParseFocus = strstr(pStrParseTmp,"\r\n");
        if(!pStrParseFocus)
        {
            MMLOGI(TAG,"already end, remain str: %s \n", pStrParseTmp);
            break;
        }
        RTSP_Parse_SingleLine(pStrParseTmp,(pStrParseFocus-pStrParseTmp),self,&S32LastAttributeNum);
        MMLOGI(TAG,"Key:%s\t",pstruAttribute->strKey);
        MMLOGI(TAG,"Value:%s\n",pstruAttribute->strValue);
        pStrParseFocus += strlen("\r\n");
        pStrParseTmp = strstr(pStrParseTmp,"\r\n");
        if(!pStrParseTmp)
        {
            MMLOGI(TAG,"already end, remain str: %s \n", pStrParseTmp);
            break;
        }
        pStrParseTmp +=  strlen("\r\n");
         if(0 == memcmp(pStrParseTmp,"\r\n",2))
                pStrParseTmp += strlen("\r\n");
        s32StrCompLen = pStrParseTmp -pStrParseArg;
        S32LastAttributeNum++;
        self->s32AttbriNum++;
    }
    return SUCCESS;
}
