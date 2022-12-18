
#include "iCunit.h"
#include "iCunit.inc"
#include "iCunit_config.h"
#include "sre_sys.h"

//#include <stdio.h>

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

iUINT32 iCunitAddSuit_F(iCHAR *suitName, iCHAR *pfileName)
{
    iUINT16 sIdx;
    if(iCunit_Init_Success)
    {
        return ICUNIT_UNINIT;
    }
    if(iCunit_Suit_Cnt == ICUNIT_SUIT_SIZE)
    {
        uart_printf("~~~~~~ Add Test-cases failed, please increace ICUNIT_SUITE_SIZE! ~~~~~~\n");

        iCunit_ErrLog_AddSuit++;
        return ICUNIT_SUIT_FULL;
    }

    if (_reboot_flag)
    {
        /*曾经复位过,检查是否为已添加的测试套*/
        for (sIdx = 0; (sIdx <= _reboot_suit_idx) && (0 != iCunit_SuitArray[sIdx].pcSuitID); sIdx++)
        {
            if (0 == strcmp(suitName, iCunit_SuitArray[sIdx].pcSuitID))
            {
                //已存在的套
                return sIdx;
            }
        }
    }

    sIdx = iCunit_Suit_Cnt;
    iCunit_SuitArray[sIdx].pcSuitID = suitName;
    iCunit_SuitArray[sIdx].pucFilename = pfileName;
    iCunit_SuitArray[sIdx].pstCaseList = (iCunit_CaseArray + iCunit_Case_Cnt);
    iCunit_Suit_Cnt++;
    return sIdx;
}

iUINT32 iCunitAddCase(iCHAR *caseName, CASE_FUNCTION caseFunc, iUINT32 suitID)
{
    iUINT16 sIdx;
    if(iCunit_Init_Success)
    {
        return ICUNIT_UNINIT;
    }
    sIdx = iCunit_Case_Cnt;
    if(sIdx == ICUNIT_CASE_SIZE)
    {
        uart_printf("~~~~~~ Add Test-cases failed, please increace ICUNIT_CASE_SIZE! ~~~~~~\n");

        iCunit_ErrLog_AddCase++;
        return ICUNIT_CASE_FULL;
    }

    if ((_reboot_flag) && (suitID <= _reboot_suit_idx))
    {
        return ICUNIT_SUCCESS; /*All cases of this suit has been added, skip it*/
    }

    iCunit_CaseArray[sIdx].pcCaseID = caseName;

    iCunit_CaseArray[sIdx].pstCaseFunc = caseFunc;
    iCunit_SuitArray[suitID].uwCaseCnt++;
    iCunit_Case_Cnt++;
    return ICUNIT_SUCCESS;
}

iUINT32 iCunitInit()
{
    if (0 == _reboot_flag)
    {
        iCunit_Init_Success = 0x0000;
        iCunit_Case_Cnt = 0x0000;
        iCunit_Suit_Cnt = 0x0000;
        iCunit_Case_Idx = 0;
        iCunit_Suit_Idx = 0;
        iCunit_Case_FailedCnt = 0;
        iCunit_Suit_FailedCnt = 0;
        iCunit_ErrLog_AddSuit = 0;
        iCunit_ErrLog_AddCase = 0;
        memset(iCunit_SuitArray, 0, sizeof(iCunit_SuitArray));
        memset(iCunit_CaseArray, 0, sizeof(iCunit_CaseArray));
    }
    return ICUNIT_SUCCESS;
}

iUINT32 iCunitRun_F(iUINT32 suitID)
{
    iUINT32        idx,sIdx;
    ICUNIT_CASE_S *psubCaseArray;
    ICUNIT_SUIT_S *pSuitItem;
    iUINT32        caseRet;
    char caseRetStr[10];

    if ((_reboot_flag) && (suitID < _reboot_suit_idx))
    {
        return ICUNIT_SUCCESS; /*This suit has been excuted, skip it*/
    }

    iCunit_Suit_Idx = suitID;
    pSuitItem = &iCunit_SuitArray[suitID];
    psubCaseArray = pSuitItem->pstCaseList;
    sIdx = pSuitItem->uwCaseCnt;

    for(idx = 0; idx < sIdx; idx++, psubCaseArray++)
    {
        if ((_reboot_flag) && (_reboot_suit_idx == suitID) && (idx < _reboot_case_idx))
        {
            continue; /*This case has been excuted, skip it*/
        }

        if ((_reboot_flag) && (_reboot_suit_idx == suitID) && (idx == _reboot_case_idx))
        {
            /*用例复位前被执行过,但没记录执行结果*/
        }
        else
        {
            iCunit_Case_Idx = idx;
            iCunit_errLineNo = ErrLineInitNo;
            iCunit_errCode = ErrCodeInit;
            caseRet = psubCaseArray->pstCaseFunc();
            snprintf(caseRetStr, 15, "[%x]",iCunit_errCode);
        }
        psubCaseArray->errLine = iCunit_errLineNo;
        psubCaseArray->retCode =  iCunit_errCode;
        if((ErrLineInitNo == iCunit_errLineNo) && (ErrCodeInit == iCunit_errCode))
        {
            pSuitItem->passCnt++;
            uart_printf("Core%d pass %s\n", SRE_GetCoreID(), psubCaseArray->pcCaseID);
        }
        else
        {
            pSuitItem->failCnt++;
            uart_printf("Core%d fail %s, ErrLineNo:%d, CaseRet:0x%08x\n", SRE_GetCoreID(), psubCaseArray->pcCaseID, iCunit_errLineNo, psubCaseArray->retCode);
            uart_printf("[z206978]err code[%s]\n",caseRetStr);
        }
    }
    iCunit_Case_Idx = 0;
    if(pSuitItem->failCnt > 0)
    {
        iCunit_Suit_FailedCnt++;
        iCunit_Case_FailedCnt += pSuitItem->failCnt;
    }
    return ICUNIT_SUCCESS;
}

iUINT32 iCunitRun(iUINT32 suitID)
{
    iUINT32 idx;
    if(iCunit_Init_Success)
    {
        return ICUNIT_UNINIT;
    }
    if(ICUNIT_SUIT_ALL == suitID)
    {
        for(idx = 0; idx < iCunit_Suit_Cnt; idx++)
        {
            iCunitRun_F(idx);
        }
        return ICUNIT_SUCCESS;
    }
    iCunitRun_F(suitID);

    return ICUNIT_SUCCESS;
}

#ifdef CI_SIM_TEST
iUINT32 iCunitPrintReport()
{
    iUINT32 idx,sIdx,sCnt;
    ICUNIT_CASE_S *psubCase;
    iCunit_errLineNo = ErrLineInitNo;
    iCunit_errCode = ErrCodeInit;
    if(iCunit_Init_Success)
    {
        return ICUNIT_UNINIT;
    }

    uart_printf("core %d:iCunit Summary Suit(%d:%d)  Case(%d:%d)  %s %s\n", SRE_GetCoreID(), iCunit_Suit_FailedCnt, iCunit_Suit_Cnt,
        iCunit_Case_FailedCnt, iCunit_Case_Cnt, __DATE__, __TIME__);
    for(sIdx = 0; sIdx < iCunit_Suit_Cnt; sIdx++)
    {
        sCnt = iCunit_SuitArray[sIdx].uwCaseCnt;
        uart_printf("core %d:iCunit Suit: %s(Passed:%d  Failed:%d  File:%s)\n", SRE_GetCoreID(), iCunit_SuitArray[sIdx].pcSuitID,
                iCunit_SuitArray[sIdx].passCnt, iCunit_SuitArray[sIdx].failCnt, iCunit_SuitArray[sIdx].pucFilename);
        psubCase = iCunit_SuitArray[sIdx].pstCaseList;

        for(idx = 0; idx < sCnt; idx++, psubCase++)
        {
            if((ErrCodeInit != psubCase->retCode) || (ErrLineInitNo != psubCase->errLine))
            {
                uart_printf("core %d:  [Failed] %s Errline: %d RetCode:0x%08X\n", SRE_GetCoreID(), psubCase->pcCaseID,
                psubCase->errLine, psubCase->retCode);
            }
            else
            {
                uart_printf("core %d:  [Passed] %s\n", SRE_GetCoreID(), psubCase->pcCaseID);
            }
        }
    }

    uart_printf("core %d:END:iCunit Summary Suit(%d:%d)  Case(%d:%d)  %s %s\n", SRE_GetCoreID(), iCunit_Suit_FailedCnt, iCunit_Suit_Cnt,
        iCunit_Case_FailedCnt, iCunit_Case_Cnt, __DATE__, __TIME__);
    return ICUNIT_SUCCESS;
}
#else
iUINT32 iCunitPrintReport()
{
    iUINT32 idx,sIdx,sCnt;
    ICUNIT_CASE_S *psubCase;
    iCunit_errLineNo = ErrLineInitNo;
    iCunit_errCode = ErrCodeInit;
    if(iCunit_Init_Success)
    {
        return ICUNIT_UNINIT;
    }

    uart_printf("iCunit Summary Suit(%d:%d)  Case(%d:%d)  %s %s\n", iCunit_Suit_FailedCnt, iCunit_Suit_Cnt,
        iCunit_Case_FailedCnt, iCunit_Case_Cnt, __DATE__, __TIME__);
    for(sIdx = 0; sIdx < iCunit_Suit_Cnt; sIdx++)
    {
        sCnt = iCunit_SuitArray[sIdx].uwCaseCnt;
        uart_printf("iCunit Suit: %s(Passed:%d  Failed:%d  File:%s)\n", iCunit_SuitArray[sIdx].pcSuitID,
                iCunit_SuitArray[sIdx].passCnt, iCunit_SuitArray[sIdx].failCnt, iCunit_SuitArray[sIdx].pucFilename);
        psubCase = iCunit_SuitArray[sIdx].pstCaseList;

        for(idx = 0; idx < sCnt; idx++, psubCase++)
        {
            if((ErrCodeInit != psubCase->retCode) || (ErrLineInitNo != psubCase->errLine))
            {
                uart_printf("  [Failed] %s Errline: %d RetCode:0x%08X\n",psubCase->pcCaseID,
                psubCase->errLine, psubCase->retCode);
            }
             #if((OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170)|| (OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
            #if 1 //CI上应用
            else
            {
                uart_printf("  [Passed] %s\n",psubCase->pcCaseID);
            }
            #endif
            #else
            #if 0 /*打印太多, PASS的不打*/
            else
            {
                uart_printf("  [Passed] %s\n",psubCase->pcCaseID);
            }
            #endif
            #endif
        }
    }

    uart_printf("END_iCunit Summary Suit(%d:%d)  Case(%d:%d)  %s %s\n", iCunit_Suit_FailedCnt, iCunit_Suit_Cnt,
        iCunit_Case_FailedCnt, iCunit_Case_Cnt, __DATE__, __TIME__);
    return ICUNIT_SUCCESS;

}
#endif

iUINT32 iCunitSaveReport(iCHAR *iCunitReportName)
{
    //FILE *freport;
    iUINT32 idx,sIdx,sCnt;
    ICUNIT_CASE_S *psubCase;
    if(iCunit_Init_Success)
    {
        return ICUNIT_UNINIT;
    }
    //freport = fopen(iCunitReportName,"wb+");
    /*if(freport == 0)
    {
        return ICUNIT_OPENFILE_FAILED;
    }*/
    /*
    <?xml version="1.0" encoding="gb2312"?>
    <?xml-stylesheet type="text/xsl" href="ci_report.xsl"?>
    <iCunitReport>
        <TestResult>Failed</TestResult>
        <iCunitSuit SuitName="CPUP_Test" file="../test/at/Mg_Cpup_TST.c" Count="3" Failed="0">
            <iCunitCase casename="Mg_Cpup_001" Result="0" retCode="0x00000000" errLine="0" />
            <iCunitCase casename="Mg_Cpup_002" Result="1" />
            <iCunitCase casename="Mg_Cpup_003" Result="1" />
        </iCunitSuit>
        <iCunitSuit SuitName="CPUP_Test" file="../test/at/Mg_Cpup_TST.c" Count="3" Failed="0">
            <iCunitCase casename="Mg_Cpup_001" Result="0" retCode="0x00000000" errLine="0" />
            <iCunitCase casename="Mg_Cpup_002" Result="1" />
            <iCunitCase casename="Mg_Cpup_003" Result="1" />
        </iCunitSuit>
    </iCunitReport>
    */
    uart_printf("<iCunitReport tr=\"%d\">\n", iCunit_Case_FailedCnt);
    uart_printf("  <iCunitSummary suitCnt=\"%d\" caseCnt=\"%d\" Count=\"%d\" Failed=\"%d\" Passed=\"%d\"/>\n", iCunit_Suit_Cnt, iCunit_Case_Cnt,iCunit_Case_Cnt,iCunit_Case_FailedCnt,(iCunit_Case_Cnt-iCunit_Case_FailedCnt));
    for(sIdx = 0; sIdx < iCunit_Suit_Cnt; sIdx++)
    {
        uart_printf("  <iCunitSuit SuitName=\"%s\" file=\"%s\" Count=\"%d\" Failed=\"%d\" Passed=\"%d\">\n",
                iCunit_SuitArray[sIdx].pcSuitID,
                iCunit_SuitArray[sIdx].pucFilename,
                iCunit_SuitArray[sIdx].uwCaseCnt,
                iCunit_SuitArray[sIdx].failCnt,
                iCunit_SuitArray[sIdx].passCnt);

        sCnt = iCunit_SuitArray[sIdx].uwCaseCnt;
        psubCase = iCunit_SuitArray[sIdx].pstCaseList;
        psubCase = iCunit_SuitArray[sIdx].pstCaseList;

        for(idx = 0; idx < sCnt; idx++, psubCase++)
        {
            if((ErrCodeInit != psubCase->retCode) || (ErrLineInitNo != psubCase->errLine))
            {
                uart_printf("    <iCunitCase casename=\"%s\" Result=\"0\" retCode=\"0x%08X\" errLine=\"%d\" />\n",
                        psubCase->pcCaseID,
                        psubCase->retCode,
                        psubCase->errLine);
            }
            else
            {
 //               uart_printf("    <iCunitCase casename=\"%s\" Result=\"1\" />\n",psubCase->pcCaseID);
            }
        }
        uart_printf("  </iCunitSuit>\n");
    }
    uart_printf("  <iCunitLog>%d Suit Add Failed, %d Cases Add Failed</iCunitLog>\n", iCunit_Suit_FailedCnt, iCunit_Case_FailedCnt);
    uart_printf("</iCunitReport>\n");
    //fclose(freport);
    return ICUNIT_SUCCESS;
}

iVOID iCunitPrintCurrentCase()
{
    ICUNIT_SUIT_S *pSuitItem = &iCunit_SuitArray[iCunit_Suit_Idx];
    ICUNIT_CASE_S *psubCaseArray;

    if (NULL != pSuitItem->pcSuitID)
    {
        if (NULL != pSuitItem->pstCaseList)
        {
            psubCaseArray = pSuitItem->pstCaseList + iCunit_Case_Idx;
            uart_printf( "\r\nCore %d rebooted  when excute Suit:%s, Case:%s\n",
                            SRE_GetCoreID(),
                            pSuitItem->pcSuitID,
                            psubCaseArray->pcCaseID);
            return;
        }
    }

    uart_printf( "\r\nCore %d rebooted when excute SuitIdx:%d, CaseIdx:%d",
                    SRE_GetCoreID(), iCunit_Suit_Idx, iCunit_Case_Idx);
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

