#ifndef _SRE_ICUNIT_H
#define _SRE_ICUNIT_H

//#include <string.h>
//#include <stdio.h>

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

typedef unsigned short                                      iUINT16;
typedef unsigned int                                        iUINT32;
typedef signed short                                        iINT16;
typedef signed int                                          iINT32;
typedef char                                                iCHAR;
typedef void                                                iVOID;


#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/*���������Ϣ�кų�ʼֵ*/
#ifndef ErrLineInitNo
#define ErrLineInitNo 0xFEDC
#endif

/*���������Ϣ���ʼֵ*/
#ifndef ErrCodeInit
#define ErrCodeInit   0xCDEF
#endif

typedef iUINT32 (* CASE_FUNCTION)( void );

typedef struct
{
    iCHAR           *pcCaseID;
    CASE_FUNCTION    pstCaseFunc;
    iUINT32          retCode;
    iUINT32          errLine;
}ICUNIT_CASE_S;

typedef struct
{
    iUINT32        uwCaseCnt;
    iCHAR         *pcSuitID;
    iCHAR         *pucFilename;
    ICUNIT_CASE_S *pstCaseList;
    iUINT32        passCnt;
    iUINT32        failCnt;
}ICUNIT_SUIT_S;

extern iUINT32 iCunit_errLineNo;  /* �����к� */
extern iUINT32 iCunit_errCode;    /* ��¼������ */

/* ���δ��ʼ�� */
#define ICUNIT_UNINIT               0x0EF00000
/* ���ļ�ʧ�� */
#define ICUNIT_OPENFILE_FAILED      0x0EF00001
/* �����ڴ�ʧ�� */
#define ICUNIT_ALLOC_FAIL           0x0EF00002
/* �޿����� */
#define ICUNIT_SUIT_FULL            0x0EF00002
/* �������ʧ�� */
#define ICUNIT_CASE_FULL            0x0EF00003
/* ���в����� */
#define ICUNIT_SUIT_ALL             0x0EF0FFFF

/* �����ɹ� */
#define ICUNIT_SUCCESS              0x00000000

/**
 * ����param��value��ͬ�������κδ���
 */
#define ICUNIT_TRACK_EQUAL(param, value, retcode) \
    do{ \
    if((param) != (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
    }}while(0)

/**
 * ����param��value��ͬ�������κδ���
 */
#define ICUNIT_TRACK_NOT_EQUAL(param, value, retcode) \
    do{ \
    if((param) == (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
    }}while(0)

/**
 * ����param��value��ͬ����ͬ��return
 */
#define ICUNIT_ASSERT_EQUAL_VOID(param, value, retcode) \
    do{ \
    if((param) != (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return; \
    }}while(0)

/**
 * ����param��value��ͬ����ͬ��return
 */
#define ICUNIT_ASSERT_NOT_EQUAL_VOID(param, value, retcode) \
    do{ \
    if((param) == (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return; \
    }}while(0)
#define ICUNIT_ASSERT_EQUAL(param,value,retcode) \
    do{ \
    if((param) != (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return 1; \
    }}while(0)

#define ICUNIT_MC_ASSERT_EQUAL(paramArray, value, retcode) \
    do \
    { \
        unsigned int core; \
        unsigned int fail = 0; \
        SRE_WaitForAllCores(); \
        for (core = 0; core < SRE_GetMaxNumberOfCores(); core++) \
        { \
            if (core != SRE_GetCoreID()) \
            { \
                continue ;\
             } \
            if (paramArray[core] != value) \
                { \
                    iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
                    iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)paramArray[core] : iCunit_errCode; \
                    fail = 1; \
                    break; \
            } \
        } \
        SRE_WaitForAllCores(); \
        if (fail) return 1; \
    }while(0)

/**
 * ����param��value��ͬ����ͬ��return
 */
#define ICUNIT_ASSERT_NOT_EQUAL(param,value,retcode) \
    do{ \
    if((param) == (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return 1; \
    }}while(0)

#define ICUNIT_MC_ASSERT_NOT_EQUAL(paramArray, value, retcode) \
    do \
    { \
        unsigned int core; \
        unsigned int fail = 0; \
        SRE_WaitForAllCores(); \
        for (core = 0; core < SRE_GetMaxNumberOfCores(); core++) \
        { \
            if (core != SRE_GetCoreID()) \
            { \
                continue ;\
             } \
            if (paramArray[core] == value) \
                { \
                    iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
                    iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)paramArray[core] : iCunit_errCode; \
                    fail = 1; \
                    break; \
            } \
        } \
        SRE_WaitForAllCores(); \
        if (fail) return 1; \
    }while(0)

/**
 * ����str1��str2�ַ���������ͬ����ͬ��return
 */
#define ICUNIT_ASSERT_STRING_EQUAL(str1,str2,retcode) \
    do{ \
    if(strcmp(str1 , str2) != 0)\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return 1; \
    }}while(0)

/**
 * ����str1��str2�ַ���������ͬ����ͬ��return
 */
#define ICUNIT_ASSERT_STRING_EQUAL_VOID(str1,str2,retcode) \
    do{ \
    if(strcmp(str1 , str2) != 0)\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return; \
    }}while(0)


/**
 * ����str1��str2�ַ������ݲ�ͬ����ͬ��return
 */
#define ICUNIT_ASSERT_STRING_NOT_EQUAL(str1,str2,retcode) \
    do{ \
        if(strcmp(str1 , str2) == 0)\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        return 1; \
    }}while(0)

/**
 * �ж�param��value�Ƿ���ͬ����ͬ����ת��label��
 */
#define ICUNIT_GOTO_EQUAL(param,value,retcode,label) \
    do{ \
    if((param) != (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        goto label; \
    }}while(0)

#define ICUNIT_MC_GOTO_EQUAL(paramArray, value, retcode, label) \
    do \
    { \
        unsigned int core; \
        unsigned int fail = 0; \
        SRE_WaitForAllCores(); \
        for (core = 0; core < SRE_GetMaxNumberOfCores(); core++) \
        { \
            if (core != SRE_GetCoreID()) \
            { \
                continue ;\
             } \
            if (paramArray[core] != value) \
                { \
                    iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
                    iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)paramArray[core] : iCunit_errCode; \
                    fail = 1;  \
                    break; \
            } \
        } \
        SRE_WaitForAllCores(); \
        if (fail) goto label; \
    }while(0)

/**
 * �ж�param��value�Ƿ�ͬ����ͬ����ת��label��
 */
#define ICUNIT_GOTO_NOT_EQUAL(param,value,retcode,label) \
    do{ \
    if((param) == (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        goto label; \
    }}while(0)

#define ICUNIT_MC_GOTO_NOT_EQUAL(paramArray, value, retcode, label) \
    do \
    { \
        unsigned int core; \
        unsigned int fail = 0; \
        SRE_WaitForAllCores(); \
        for (core = 0; core < SRE_GetMaxNumberOfCores(); core++) \
        { \
            if (core != SRE_GetCoreID()) \
            { \
                continue ;\
             } \
            if (paramArray[core] == value) \
                { \
                    iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
                    iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)paramArray[core] : iCunit_errCode; \
                    fail = 1;  \
                    break; \
            } \
        } \
        SRE_WaitForAllCores(); \
        if (fail) goto label; \
    }while(0)

/**
 * �ж�str1��str2�Ƿ���ͬ����ͬ����ת��label��
 */
#define ICUNIT_GOTO_STRING_EQUAL(str1,str2,retcode,label) \
    do{ \
    if(strcmp(str1,str2) != 0)\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        goto label; \
    }}while(0)

/**
 * �ж�str1��str2�Ƿ�ͬ����ͬ����ת��label��
 */
#define ICUNIT_GOTO_STRING_NOT_EQUAL(str1,str2,retcode,label) \
    do{ \
    if(strcmp(str1,str2) == 0)\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        goto label; \
    }}while(0)

/* ��Ӳ����� */
extern iUINT32 iCunitAddSuit_F(iCHAR *suitName, iCHAR *pfileName);
#define iCunitAddSuit(suitName) iCunitAddSuit_F(suitName, __FILE__)
/* ��Ӳ������� */
extern iUINT32 iCunitAddCase(iCHAR *caseName, CASE_FUNCTION caseFunc, iUINT32 suitID);

/* ���в����ף�����Ϊ���µ�λ */
extern iUINT32 iCunitRun(iUINT32 suitID);
/* iCunit��ܳ�ʼ�� */
extern iUINT32 iCunitInit(void);
/* ���ֲ��Խ�� */
extern iUINT32 iCunitSaveReport(iCHAR *iCunitReportName);
/* ��ӡ���Խ�� */
extern iUINT32 iCunitPrintReport(void);

#define TEST_ADD_SUITE(uiSuiteId, suiteName) \
{\
    uiSuiteId = iCunitAddSuit(suiteName);\
    ICUNIT_ASSERT_NOT_EQUAL_VOID(uiSuiteId, ICUNIT_UNINIT, ICUNIT_UNINIT);\
    ICUNIT_ASSERT_NOT_EQUAL_VOID(uiSuiteId, ICUNIT_SUIT_FULL, ICUNIT_SUIT_FULL);\
}

#define TEST_ADD_CASE(casefunc, uiSuiteId, Label_RUN) \
{\
    iUINT32 uwRet = 1;\
    uwRet = iCunitAddCase(#casefunc, casefunc, uiSuiteId);\
    ICUNIT_GOTO_EQUAL(uwRet, ICUNIT_SUCCESS, uwRet, Label_RUN);\
}

#define TEST_RUN_SUITE(uiSuiteId) \
{\
    UINT32 uiRet;\
    uiRet = iCunitRun(uiSuiteId);\
    ICUNIT_ASSERT_NOT_EQUAL_VOID(uiRet, ICUNIT_UNINIT, ICUNIT_UNINIT);\
}

#ifdef __cplusplus
 #if __cplusplus
}
 #endif/* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_ICUNIT_H */

