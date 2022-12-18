#include <stdio.h>
#include <stdlib.h>
#include "hi_svr_subprase.h"

int main(int argc, char *argv[])
{
    int ret = -1;
    HI_HANDLE hSub;
    FILE* pFile;
    size_t readlen;
    HI_U8* pData;
    HI_SVR_SUB_PARAM_S stSubParam;
    HI_SVR_SUB_DATA_S* pstSubNodeBuf = HI_NULL;
    HI_SVR_SUB_KeyVP* pstSubKeyVpBuf = HI_NULL;
    HI_U32 u32NodeNum;
    HI_U32 u32KeyVpNum;
    int i;
    int loop;

    if (argc < 2)
    {
        printf("usage: ./ttmltest xxx.xml zzz.xml");
        return ret;
    }

    for (loop = 1; loop < argc; loop++)
    {
        pFile = fopen(argv[loop], "rb");
        if (!pFile)
        {
            printf(">>> open file %s error\n", argv[1]);
            return ret;
        }

        ret = HI_SVR_SUB_Parse_Init();
        if (ret != HI_SUCCESS)
        {
            printf(">>> HI_SVR_SUB_Parse_Init ret failed:%x\n", ret);
            fclose(pFile);
            return ret;
        }

        stSubParam.eSubType  = HI_SVR_SUB_TYPE_TTML;
        stSubParam.pfnReadCb = HI_NULL;
        stSubParam.pfnSeekCb = HI_NULL;
        stSubParam.s32PtsAdjustValue = 0;
        stSubParam.u32UserData = 0;
        ret = HI_SVR_SUB_Parse_Create(&stSubParam, &hSub);
        if (ret != HI_SUCCESS)
        {
            printf(">>> HI_SVR_SUB_Parse_Create ret failed:%x\n", ret);
            HI_SVR_SUB_Parse_DeInit();
            fclose(pFile);
            return ret;
        }

        pData = malloc(1000);

        do
        {
            readlen = fread(pData, 1, 1000, pFile);
            if (readlen > 0)
            {
                ret = HI_SVR_SUB_Parse_SendData(hSub, pData, readlen);
                if (ret != HI_SUCCESS)
                {
                    printf(">>> HI_SVR_SUB_Parse_SendData failed:%x\n", ret);
                }
            }
        } while (readlen > 0);

        ret = HI_SVR_SUB_Parse_ReadSubNodes(hSub,0, &pstSubNodeBuf, &u32NodeNum, &pstSubKeyVpBuf, &u32KeyVpNum);
        if (ret != HI_SUCCESS)
        {
            printf(">>> HI_SVR_SUB_Parse_ReadSubNodes ret failed:%x\n", ret);
            goto exit;
        }

        printf("\n---------------file:%s Node Number:%d,KeyVP number:%d------------\n\n",argv[loop], u32NodeNum, u32KeyVpNum);
        if (u32NodeNum)
        {
            printf( "node id:   pts:     duration:     text:\n");
            if ((u32NodeNum > 0) && (pstSubNodeBuf != HI_NULL))
            {
                for (i = 0; i < u32NodeNum; i++)
                {
                    printf("     %02d    %06lld    %04d         %s\n", pstSubNodeBuf[i].u32ExtId, pstSubNodeBuf[i].s64PTS,
                           pstSubNodeBuf[i].u32DurationMs, pstSubNodeBuf[i].ps8SubtData);
                }
            }
        }

        printf("\n");
        if (u32KeyVpNum)
        {
            printf( "keyvp id:    name:                  value:\n");
            if ((u32KeyVpNum > 0) && (pstSubKeyVpBuf != HI_NULL))
            {
                for (i = 0; i < u32KeyVpNum; i++)
                {
                    printf("     %02d      %-20s   %s\n", pstSubKeyVpBuf[i].u32ExtId, pstSubKeyVpBuf[i].ps8Name,
                           pstSubKeyVpBuf[i].ps8Value);
                }
            }
        }
        fclose(pFile);
    }

exit:
    HI_SVR_SUB_Parse_Destroy(hSub);
    HI_SVR_SUB_Parse_DeInit();
    free(pData);

    return ret;
}
