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

/*定义错误信息行号初始值*/
#ifndef ErrLineInitNo
#define ErrLineInitNo 0xFEDC
#endif

/*定义错误信息码初始值*/
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

extern iUINT32 iCunit_errLineNo;  /* 错误行号 */
extern iUINT32 iCunit_errCode;    /* 记录错误码 */

/* 框架未初始化 */
#define ICUNIT_UNINIT               0x0EF00000
/* 打开文件失败 */
#define ICUNIT_OPENFILE_FAILED      0x0EF00001
/* 申请内存失败 */
#define ICUNIT_ALLOC_FAIL           0x0EF00002
/* 无空闲套 */
#define ICUNIT_SUIT_FULL            0x0EF00002
/* 添加用例失败 */
#define ICUNIT_CASE_FULL            0x0EF00003
/* 所有测试套 */
#define ICUNIT_SUIT_ALL             0x0EF0FFFF

/* 操作成功 */
#define ICUNIT_SUCCESS              0x00000000

/**
 * 跟踪param和value不同，不做任何处理
 */
#define ICUNIT_TRACK_EQUAL(param, value, retcode) \
    do{ \
    if((param) != (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
    }}while(0)

/**
 * 跟踪param和value相同，不做任何处理
 */
#define ICUNIT_TRACK_NOT_EQUAL(param, value, retcode) \
    do{ \
    if((param) == (value))\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
    }}while(0)

/**
 * 断言param和value相同，不同则return
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
 * 断言param和value不同，相同则return
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
 * 断言param和value不同，相同则return
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
 * 断言str1和str2字符串内容相同，不同则return
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
 * 断言str1和str2字符串内容相同，不同则return
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
 * 断言str1和str2字符串内容不同，相同则return
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
 * 判断param和value是否相同，不同则跳转到label处
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
 * 判断param和value是否不同，相同则跳转到label处
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
 * 判断str1和str2是否相同，不同则跳转到label处
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
 * 判断str1和str2是否不同，相同则跳转到label处
 */
#define ICUNIT_GOTO_STRING_NOT_EQUAL(str1,str2,retcode,label) \
    do{ \
    if(strcmp(str1,str2) == 0)\
    { \
        iCunit_errLineNo = (iCunit_errLineNo == ErrLineInitNo)? __LINE__ : iCunit_errLineNo; \
        iCunit_errCode = (iCunit_errCode == ErrCodeInit)? (iUINT32)retcode : iCunit_errCode; \
        goto label; \
    }}while(0)

/* 添加测试套 */
extern iUINT32 iCunitAddSuit_F(iCHAR *suitName, iCHAR *pfileName);
#define iCunitAddSuit(suitName) iCunitAddSuit_F(suitName, __FILE__)
/* 添加测试用例 */
extern iUINT32 iCunitAddCase(iCHAR *caseName, CASE_FUNCTION caseFunc, iUINT32 suitID);

/* 运行测试套，以套为最新单位 */
extern iUINT32 iCunitRun(iUINT32 suitID);
/* iCunit框架初始化 */
extern iUINT32 iCunitInit(void);
/* 保持测试结果 */
extern iUINT32 iCunitSaveReport(iCHAR *iCunitReportName);
/* 打印测试结果 */
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

