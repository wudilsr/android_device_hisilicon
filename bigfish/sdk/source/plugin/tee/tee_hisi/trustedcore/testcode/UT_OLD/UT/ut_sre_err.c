 /**
 * @file:
 *
 * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * @description£º
 */
#include "iCunit.h"
#include "sre_config.h"
#include "sre_mem.h"
#include "sre_sys.h"

//#include "sre_sync.ph"
#include "sre_hunt.h"
#include "app_data_common.h"
#include "sre_buildef.h"
#include "osTest.h"
#include "sre_errno.h"
#include "sre_err.ph"
#include "sre_task.h"
#if (OS_CPU_TYPE == OS_SD6182)
#include "sre_platform.ph"
#elif (OS_CPU_TYPE == OS_SD6181 || OS_CPU_TYPE == OS_SD6108)
#include "sre_asm.ph"
#endif

#define OS_EXCCAUSE_FATALERROR                              72
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
extern  UINT32 g_uwNum[OS_SYS_CORE_MAX_NUM];
extern  USER_ERR_FUNC_S      g_stUserErrFunc;
extern  CDA_INFO_S  *g_pstCdaInfoAddr;
#define NORMAL_ERROR   SRE_ERRNO_OS_ERROR(0x10,0x11)
#define NORMAL_ERROR2   SRE_ERRNO_OS_ERROR(0x11,0x22)
#define NORMAL_ERROR3   SRE_ERRNO_OS_ERROR(0x12,0x23)

#define FATAL_ERROR    SRE_ERRNO_OS_FATAL(0x07,0x11)

/**
*-@test  UT_SRE_ErrRegHook_001
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID errorHook(CHAR    *pcFileName,
                             UINT32   uwLineNo,
                             UINT32   uwErrorNo,
                             UINT32   uwParaLen,
                             VOID     *pPara)
{
    g_uwNum[SRE_GetCoreID()] ++;
    return;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_001()
{
    SRE_ERRORHANDLE_FUNC  pfnHookTemp;

    pfnHookTemp = g_stUserErrFunc.pfnHook;

    SRE_ErrRegHook(errorHook);
    ICUNIT_ASSERT_EQUAL(g_stUserErrFunc.pfnHook, errorHook, g_stUserErrFunc.pfnHook);

    SRE_ErrRegHook(NULL);
    ICUNIT_ASSERT_EQUAL(g_stUserErrFunc.pfnHook, NULL, g_stUserErrFunc.pfnHook);

    g_stUserErrFunc.pfnHook = pfnHookTemp;
    return SRE_OK;
}


/**
*-@test  UT_SRE_ErrRegHook_002
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_002()
{
    UINT32 uwRet;
    CHAR *pcFileName;
    UINT32 uwPara;
    SRE_ERRORHANDLE_FUNC  pfnHookTemp;

    pfnHookTemp = g_stUserErrFunc.pfnHook;

    g_uwNum[SRE_GetCoreID()] = 0;
    pcFileName = "a.c";

    SRE_ErrRegHook(errorHook);

    uwRet = SRE_ErrHandle(pcFileName,1,SRE_ERRNO_OS_ERROR(1,1),4,&uwPara);

    g_stUserErrFunc.pfnHook = pfnHookTemp;

    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 1, g_uwNum[SRE_GetCoreID()]);


    return SRE_OK;
}

/**
*-@test  ut_SRE_CdaInfoGet_003
*-@tspec  CDA·ÖÇøÐÅÏ¢»ñÈ¡º¯Êý²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_CdaInfoGet_003( )
{
    UINT32 i;
    CDA_PT_INFO_S stCdaPtInfo[0x20];

    memset(&stCdaPtInfo[0],0, (0x20 * sizeof(CDA_PT_INFO_S)));

    SRE_CdaInfoGet(stCdaPtInfo);
    for(i = 0; i< 10; i++)
    {
        uart_printf("cda inf is index:%d ,addr:0x%x ,size:0x%x \n", i, stCdaPtInfo[i].uwAddr,stCdaPtInfo[i].uwSize);
    }
}


/**
*-@test  UT_SRE_ErrRegHook_004
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ pfile=NULL
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_SRE_ErrRegHook_004_hook(CHAR    *pcFileName,
                                                 UINT32   uwLineNo,
                                                 UINT32   uwErrorNo,
                                                 UINT32   uwParaLen,
                                                 VOID     *pPara)
{
    g_uwNum[SRE_GetCoreID()] = 1;
    ICUNIT_ASSERT_STRING_EQUAL_VOID(pcFileName, "UT_SRE_Err", pcFileName);
    ICUNIT_ASSERT_EQUAL_VOID(uwLineNo, 1, uwLineNo);
    ICUNIT_ASSERT_EQUAL_VOID(uwErrorNo, 0x1234, uwErrorNo);
    ICUNIT_ASSERT_EQUAL_VOID(uwParaLen, 4, uwParaLen);
    *(UINT32*)pPara = 0x5678;


    return;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_004()
{
    UINT32 uwRet;
    UINT32 uwPara = 0;
    SRE_ERRORHANDLE_FUNC  pfnHookTemp;

    pfnHookTemp = g_stUserErrFunc.pfnHook;

    SRE_ErrRegHook(UT_SRE_ErrRegHook_004_hook);

    g_uwNum[SRE_GetCoreID()] = 0;

    uwRet = SRE_ErrHandle("UT_SRE_Err",1,0x1234,4,&uwPara);


    g_stUserErrFunc.pfnHook = pfnHookTemp;

    ICUNIT_ASSERT_EQUAL(uwPara, 0x5678, uwPara);

    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 1, g_uwNum[SRE_GetCoreID()]);

    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrRegHook_005
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ uwPara=NULL
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_005()
{
    UINT32 uwRet;

    g_uwNum[SRE_GetCoreID()] = 0;

    uwRet = SRE_ErrHandle(NULL,1,SRE_ERRNO_OS_ERROR(1,1),4,NULL);

    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 0, g_uwNum[SRE_GetCoreID()]);

    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrRegHook_006
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_006()
{
    g_uwNum[SRE_GetCoreID()] = 0;
    SRE_ErrRegHook(errorHook);

    OS_REPORT_ERROR(NORMAL_ERROR);

    SRE_ErrRegHook(NULL);

    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 1, g_uwNum[SRE_GetCoreID()]);

    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrRegHook_007
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_007()
{

    g_uwNum[SRE_GetCoreID()] = 0;

    OS_REPORT_ERROR(NORMAL_ERROR);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 0, g_uwNum[SRE_GetCoreID()]);

    SRE_ErrRegHook(errorHook);

    OS_REPORT_ERROR(NORMAL_ERROR);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 1, g_uwNum[SRE_GetCoreID()]);

    OS_REPORT_ERROR(NORMAL_ERROR);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 2, g_uwNum[SRE_GetCoreID()]);

    SRE_ErrRegHook(NULL);

    OS_REPORT_ERROR(NORMAL_ERROR);
    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 2, g_uwNum[SRE_GetCoreID()]);

    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrRegHook_008
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_SRE_ErrRegHook_008_hook(CHAR    *pcFileName,
                                                 UINT32   uwLineNo,
                                                 UINT32   uwErrorNo,
                                                 UINT32   uwParaLen,
                                                 VOID     *pPara)
{
    ICUNIT_ASSERT_STRING_EQUAL_VOID(pcFileName, "os_unspecific_file", pcFileName);
    ICUNIT_ASSERT_EQUAL_VOID(uwLineNo, OS_ERR_MAGIC_WORD, uwLineNo);
    ICUNIT_ASSERT_EQUAL_VOID(uwErrorNo, NORMAL_ERROR, uwErrorNo);
    ICUNIT_ASSERT_EQUAL_VOID(uwParaLen, 0, uwParaLen);
    ICUNIT_ASSERT_EQUAL_VOID(pPara, NULL, pPara);
    g_uwNum[SRE_GetCoreID()]++;


    return;
}

OS_SEC_TEXT_UT UINT32 UT_SRE_ErrRegHook_008()
{
    g_uwNum[SRE_GetCoreID()] = 0;
    SRE_ErrRegHook(UT_SRE_ErrRegHook_008_hook);

    OS_REPORT_ERROR(NORMAL_ERROR);

    SRE_ErrRegHook(NULL);

    ICUNIT_ASSERT_EQUAL(g_uwNum[SRE_GetCoreID()], 1, g_uwNum[SRE_GetCoreID()]);

    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_001
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT VOID UT_SRE_ErrHandle_clear()
{
    g_pstCdaInfoAddr->uwRecordIndex = 0;
    memset(g_pstCdaInfoAddr->astErrInfo, 0 , (OS_ERR_RECORD_NUM * sizeof(ERR_INFO_S)));
}

OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_001()
{
    UT_SRE_ErrHandle_clear();

    OS_REPORT_ERROR(NORMAL_ERROR);

    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->uwRecordIndex, 1, g_pstCdaInfoAddr->uwRecordIndex);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo, NORMAL_ERROR, g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo, 0, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);

    UT_SRE_ErrHandle_clear();

    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_002
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_002()
{

    OS_REPORT_ERROR(1);
    OS_REPORT_ERROR(2);
    OS_REPORT_ERROR(3);

    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->uwRecordIndex, 3, g_pstCdaInfoAddr->uwRecordIndex);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo, 1, g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo, 2, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[2].uwErrorNo, 3, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[3].uwErrorNo, 0, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);

    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_003
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_003()
{

    OS_REPORT_ERROR(1);
    OS_REPORT_ERROR(2);
    OS_REPORT_ERROR(3);
    OS_REPORT_ERROR(4);
    OS_REPORT_ERROR(5);
    OS_REPORT_ERROR(6);
    OS_REPORT_ERROR(7);
    OS_REPORT_ERROR(8);
    OS_REPORT_ERROR(9);

    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->uwRecordIndex, 1, g_pstCdaInfoAddr->uwRecordIndex);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo, 1, g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo, 2, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[2].uwErrorNo, 3, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[3].uwErrorNo, 4, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[4].uwErrorNo, 5, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[5].uwErrorNo, 6, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[6].uwErrorNo, 7, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[7].uwErrorNo, 8, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[8].uwErrorNo, 9, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);

    if(9 == OS_ERR_RECORD_NUM)
    {
        OS_REPORT_ERROR(10);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->uwRecordIndex, 2, g_pstCdaInfoAddr->uwRecordIndex);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo, 1, g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo, 10, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);

        OS_REPORT_ERROR(11);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->uwRecordIndex, 3, g_pstCdaInfoAddr->uwRecordIndex);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo, 1, g_pstCdaInfoAddr->astErrInfo[0].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo, 10, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[2].uwErrorNo, 11, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[3].uwErrorNo, 4, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[4].uwErrorNo, 5, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[5].uwErrorNo, 6, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[6].uwErrorNo, 7, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[7].uwErrorNo, 8, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
        ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->astErrInfo[8].uwErrorNo, 9, g_pstCdaInfoAddr->astErrInfo[1].uwErrorNo);
    }
    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_004
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_004()
{
    UINT16 usLoop;
    UINT32 uwLastErrIndex;
    UINT32 uwLastErrNo;

    for(usLoop = 0; usLoop < 1; usLoop++)
    {
        OS_REPORT_ERROR(0xab+usLoop);
    }

    if((1 == g_pstCdaInfoAddr->uwRecordIndex)
       && (0 != g_pstCdaInfoAddr->astErrInfo[OS_ERR_RECORD_NUM - 1].uwErrorNo))
    {
        uwLastErrIndex = OS_ERR_RECORD_NUM - 1;
    }
    else
    {
        uwLastErrIndex = g_pstCdaInfoAddr->uwRecordIndex - 1;
    }

    uwLastErrNo = g_pstCdaInfoAddr->astErrInfo[uwLastErrIndex].uwErrorNo;

    ICUNIT_ASSERT_EQUAL(uwLastErrNo, 0xab+(usLoop-1), uwLastErrNo);


    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_005
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_005()
{
    UINT16 usLoop;
    UINT32 uwLastErrIndex;
    UINT32 uwLastErrNo;

    for(usLoop = 0; usLoop < 6; usLoop++)
    {
        OS_REPORT_ERROR(0xab+usLoop);
    }

    if((1 == g_pstCdaInfoAddr->uwRecordIndex)
       && (0 != g_pstCdaInfoAddr->astErrInfo[OS_ERR_RECORD_NUM - 1].uwErrorNo))
    {
        uwLastErrIndex = OS_ERR_RECORD_NUM - 1;
    }
    else
    {
        uwLastErrIndex = g_pstCdaInfoAddr->uwRecordIndex - 1;
    }

    uwLastErrNo = g_pstCdaInfoAddr->astErrInfo[uwLastErrIndex].uwErrorNo;

    ICUNIT_ASSERT_EQUAL(uwLastErrNo, 0xab+(usLoop-1), uwLastErrNo);

    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_006
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_006()
{
    UINT16 usLoop;
    UINT32 uwLastErrIndex;
    UINT32 uwLastErrNo;

    for(usLoop = 0; usLoop < OS_ERR_RECORD_NUM; usLoop++)
    {
        OS_REPORT_ERROR(0xab+usLoop);
    }

    if((1 == g_pstCdaInfoAddr->uwRecordIndex)
       && (0 != g_pstCdaInfoAddr->astErrInfo[OS_ERR_RECORD_NUM - 1].uwErrorNo))
    {
        uwLastErrIndex = OS_ERR_RECORD_NUM - 1;
    }
    else
    {
        uwLastErrIndex = g_pstCdaInfoAddr->uwRecordIndex - 1;
    }

    uwLastErrNo = g_pstCdaInfoAddr->astErrInfo[uwLastErrIndex].uwErrorNo;

    ICUNIT_ASSERT_EQUAL(uwLastErrNo, 0xab+(usLoop-1), uwLastErrNo);

    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_007
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_007()
{
    UINT16 usLoop;
    UINT32 uwLastErrIndex;
    UINT32 uwLastErrNo;

    for(usLoop = 0; usLoop < 12; usLoop++)
    {
        OS_REPORT_ERROR(0xab+usLoop);
    }

    if((1 == g_pstCdaInfoAddr->uwRecordIndex)
       && (0 != g_pstCdaInfoAddr->astErrInfo[OS_ERR_RECORD_NUM - 1].uwErrorNo))
    {
        uwLastErrIndex = OS_ERR_RECORD_NUM - 1;
    }
    else
    {
        uwLastErrIndex = g_pstCdaInfoAddr->uwRecordIndex - 1;
    }

    uwLastErrNo = g_pstCdaInfoAddr->astErrInfo[uwLastErrIndex].uwErrorNo;

    ICUNIT_ASSERT_EQUAL(uwLastErrNo, 0xab+(usLoop-1), uwLastErrNo);

    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_008
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_008()
{
    UINT16 usLoop;
    UINT32 uwLastErrIndex;
    UINT32 uwLastErrNo;

    for(usLoop = 0; usLoop < 11; usLoop++)
    {
        OS_REPORT_ERROR(NORMAL_ERROR);
    }
    OS_REPORT_ERROR(FATAL_ERROR);

    if((1 == g_pstCdaInfoAddr->uwRecordIndex)
       && (0 != g_pstCdaInfoAddr->astErrInfo[OS_ERR_RECORD_NUM - 1].uwErrorNo))
    {
        uwLastErrIndex = OS_ERR_RECORD_NUM - 1;
    }
    else
    {
        uwLastErrIndex = g_pstCdaInfoAddr->uwRecordIndex - 1;
    }

    uwLastErrNo = g_pstCdaInfoAddr->astErrInfo[uwLastErrIndex].uwErrorNo;

    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->ucExcFlag, OS_EXCCAUSE_FATALERROR, g_pstCdaInfoAddr->ucExcFlag);
    ICUNIT_ASSERT_EQUAL(uwLastErrNo, FATAL_ERROR, uwLastErrNo);

    g_pstCdaInfoAddr->ucExcFlag = 0xFF;

    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}

/**
*-@test  UT_SRE_ErrHandle_009
*-@tspec  ´íÎó¼ÇÂ¼Ä£¿éUT²âÊÔ
*-@ttitle
*-@tprecon
*-@tbrief
*-@texpect
*-@tprior  1
*-@tremark
*/
OS_SEC_TEXT_UT UINT32 UT_SRE_ErrHandle_009()
{
    UINT16 usLoop;
    UINT32 uwLastErrIndex;
    UINT32 uwLastErrNo;

    OS_REPORT_ERROR(NORMAL_ERROR);

    __SRE_TaskDelay(2);

    for(usLoop = 0; usLoop < 7; usLoop++)
    {
        OS_REPORT_ERROR(NORMAL_ERROR2);
        __SRE_TaskDelay(2);
    }

    OS_REPORT_ERROR(NORMAL_ERROR3);
    __SRE_TaskDelay(2);

    OS_REPORT_ERROR(NORMAL_ERROR3);
    __SRE_TaskDelay(2);

    OS_REPORT_ERROR(FATAL_ERROR);

    if((1 == g_pstCdaInfoAddr->uwRecordIndex)
       && (0 != g_pstCdaInfoAddr->astErrInfo[OS_ERR_RECORD_NUM - 1].uwErrorNo))
    {
        uwLastErrIndex = OS_ERR_RECORD_NUM - 1;
    }
    else
    {
        uwLastErrIndex = g_pstCdaInfoAddr->uwRecordIndex - 1;
    }

    uwLastErrNo = g_pstCdaInfoAddr->astErrInfo[uwLastErrIndex].uwErrorNo;

    ICUNIT_ASSERT_EQUAL(g_pstCdaInfoAddr->ucExcFlag, OS_EXCCAUSE_FATALERROR, g_pstCdaInfoAddr->ucExcFlag);
    ICUNIT_ASSERT_EQUAL(uwLastErrNo, FATAL_ERROR, uwLastErrNo);

    g_pstCdaInfoAddr->ucExcFlag = 0xFF;

    UT_SRE_ErrHandle_clear();
    return SRE_OK;
}


/* Èë¿Ú²âÊÔÌ×  */
OS_SEC_TEXT_UT VOID UT_SRE_err(void)
{
    UINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_err");

    TEST_ADD_CASE(UT_SRE_ErrRegHook_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrRegHook_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_CdaInfoGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrRegHook_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrRegHook_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrRegHook_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrRegHook_007, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrRegHook_008, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_004, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_005, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_006, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_ErrHandle_007, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_ErrHandle_008, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_ErrHandle_009, uiSuiteId, Label_RUN);

Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             