/***********************************************************************************
*             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
******************************************************************************
* FileName: hi_log.h
* Description:S2项目公共日志头文件
*
* History:
* Version  Date        Author                               DefectNum  Description
* 1.0      2009/03/19  Hisilicon STB Step-2 software group  NULL       Create this file.
***********************************************************************************/

#ifndef __HI_LOG_H__
#define __HI_LOG_H__

#include <stdarg.h>
#include <stdlib.h>     /*lint -esym(766, stdlib.h) */

#include "hi_type.h"
#include "hi_ref_mod.h"
#include "hi_ref_errno.h"
#include "svr_debug.h"
#include "logformat.h"


#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif /* __cplusplus */
#endif  /* __cplusplus */

/***************************** Macro Definition ******************************/

/*-----------------------------------------------------------------
如果是调试版本，则应当在Makefile中定义宏LOG_DEBUG_ENABLE
-----------------------------------------------------------------*/

#define HI_LOG_DO_WHILE_ZERO /*lint -e(717) */ (0)

/* 定义5个等级*/
typedef enum hiERR_LEVEL_E
{
    HI_ERR_LEVEL_FATAL = 0,      /* just for compatibility with previous version */
    HI_ERR_LEVEL_ERROR,      /* error conditions                             */
    HI_ERR_LEVEL_WARN,
    HI_ERR_LEVEL_INFO,       /* informational                                */
    HI_ERR_LEVEL_DEBUG,  /* debug-level                                  */
    HI_ERR_LEVEL_BUTT
} HI_ERR_LEVEL_E;


/*-----------------------------------------------------------------
无模块的日志输出宏:
HI_LOG_DEBUG、HI_LOG_INFO一般用于调试，没有错误码，
HI_LOG_ERROR和HI_LOG_FATAL一般用于日志，有错误码
HI_LOG_OUTOUTF通用于所有情况
-----------------------------------------------------------------*/
#if HI_OS_TYPE == HI_OS_LINUX

 #ifndef     __THIS_LOG_MOD_ID
  #define      __THIS_LOG_MOD_ID HI_MOD_ID_NULL
 #endif

 #ifndef HI_ADVCA_FUNCTION_RELEASE

//通用输出信息函数
  #define HI_LOG_OUTPUTF(enErrLevel, enoErrno, pszFormat...) \
    (HI_VOID)HI_LOG_Outputf(__THIS_LOG_MOD_ID, (enErrLevel), (enoErrno), \
                            __FILE__, __FUNCTION__, __LINE__, pszFormat)
 #else/*DISCARD_DEBUG_INFO*/
  #define HI_LOG_OUTPUTF(enErrLevel, enoErrno, pszFormat...)
 #endif/*DISCARD_DEBUG_INFO*/



 #ifndef DISCARD_DEBUG_INFO
  #define HI_LOG_DEBUG(pszFormat...)  HILOG_FIT_SVRLOG(HI_ERR_LEVEL_DEBUG,HI_SUCCESS,pszFormat)
  #define HI_LOG_INFO(pszFormat...)   HILOG_FIT_SVRLOG(HI_ERR_LEVEL_INFO,HI_SUCCESS,pszFormat)
  #define HI_LOG_ERROR( pszFormat...) HILOG_FIT_SVRLOG(HI_ERR_LEVEL_ERROR,HI_FAILURE,pszFormat)
 #else
  #define HI_LOG_DEBUG(pszFormat...)
  #define HI_LOG_INFO(pszFormat...)
  #define HI_LOG_ERROR( pszFormat...)
 #endif

 // 错误信息输出，带指定错误码
 #define HI_LOG_ERROR_NO( error_no, pszFormat...)\
  HILOG_FIT_SVRLOG(HI_ERR_LEVEL_ERROR,error_no,pszFormat)


// 致命错误信息输出，带指定错误码
 #define HI_LOG_FATAL(error_no, pszFormat...) \
    HILOG_FIT_SVRLOG(HI_ERR_LEVEL_FATAL,error_no,pszFormat)


#endif /* HI_OS_TYPE == HI_OS_LINUX */

#if HI_OS_TYPE == HI_OS_WIN32

 #define HI_LOG_SAVE_AUTO_DATA \
    HI_LOG_SaveAutoData((HI_CHAR *)__FILE__, (HI_CHAR *)__FUNCTION__, __LINE__)
 #define HI_LOG_AUTO_DATA_CREATE \
    HI_CHAR * pszProgramFileName;                                        \
    HI_CHAR *pszProgramFunctionName;                                    \
    HI_S32 s32ProgramLineNo;                                           \
    HI_LOG_GetAutoData(&pszProgramFileName, \
                       &pszProgramFunctionName, &s32ProgramLineNo)
 #define HI_LOG_AUTO_DATA_CALL \
    pszProgramFileName, \
    pszProgramFunctionName, \
    s32ProgramLineNo
 #define HI_LOG_IMPLEMENT(mod_id, level_no, err_no) \
    va_list vaListArgs;                                                     \
    HI_ERRNO enoLocalErrno;                                                 \
    HI_LOG_AUTO_DATA_CREATE;                                                \
    vaListArgs = 0;                                                         \
    va_start(vaListArgs, pszFormat);                                        \
    enoLocalErrno = HI_LOG_OutputValist((mod_id), (level_no), \
                                        (err_no), HI_LOG_AUTO_DATA_CALL, pszFormat, &vaListArgs);           \
    va_end(vaListArgs);                                                     \
    (HI_VOID)__FUNCTION__;                                                  \
    return enoLocalErrno
 #define HI_LOG_DEBUG_IMPLEMENT(mod_id) \
    HI_LOG_IMPLEMENT((mod_id), HI_ERR_LEVEL_DEBUG, HI_SUCCESS)
 #define HI_LOG_INFO_IMPLEMENT(mod_id) \
    HI_LOG_IMPLEMENT((mod_id), HI_ERR_LEVEL_INFO, HI_SUCCESS)
 #define HI_LOG_ERROR_IMPLEMENT(mod_id) \
    HI_LOG_IMPLEMENT((mod_id), HI_ERR_LEVEL_ERROR, enoErrno)
 #define HI_LOG_FATAL_IMPLEMENT(mod_id) \
    HI_LOG_IMPLEMENT((mod_id), HI_ERR_LEVEL_FATAL, enoErrno)
 #undef  HI_LOG_DEBUG       /* for pclint */
 #undef  HI_LOG_INFO        /* for pclint */
 #undef  HI_LOG_ERROR       /* for pclint */
 #undef  HI_LOG_FATAL       /* for pclint */
 #define HI_LOG_DEBUG HI_LOG_SAVE_AUTO_DATA; (HI_VOID)HI_LOG_DEBUG_Func
 #define HI_LOG_INFO HI_LOG_SAVE_AUTO_DATA; (HI_VOID)HI_LOG_INFO_Func
 #define HI_LOG_ERROR HI_LOG_SAVE_AUTO_DATA; (HI_VOID)HI_LOG_ERROR_Func
 #define HI_LOG_FATAL HI_LOG_SAVE_AUTO_DATA; (HI_VOID) HI_LOG_FATAL_Func
HI_ERRNO    HI_LOG_OUTOUTF_Func(HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno, const HI_CHAR * pszFormat, ...);
HI_ERRNO    HI_LOG_DEBUG_Func(const HI_CHAR * pszFormat, ...);
HI_ERRNO    HI_LOG_INFO_Func(const HI_CHAR * pszFormat, ...);
HI_ERRNO    HI_LOG_ERROR_Func(HI_ERRNO enoErrno, const HI_CHAR * pszFormat, ...);
HI_ERRNO    HI_LOG_FATAL_Func(HI_ERRNO enoErrno, const HI_CHAR * pszFormat, ...);

#endif /* HI_OS_TYPE == HI_OS_WIN32 */

/*-----------------------------------------------------------------
如果使用VC6则在每个函数前面进行如下定义
#ifdef HI_LOG_FUNCTION_HAND
#undef  __FUNCTION__
#define __FUNCTION__ "函数名"
#endif
-----------------------------------------------------------------*/
#if HI_OS_TYPE == HI_OS_WIN32
 #ifndef HI_LOG_FUNCTION_HAND
  #define HI_LOG_FUNCTION_HAND 1

/*lint -esym(750, __FUNCTION__) */

//#undef  __FUNCTION__
//#define __FUNCTION__        ""
 #endif
#endif

/*-----------------------------------------------------------------
适配基本函数
-----------------------------------------------------------------*/
#undef  HI_INLINE
#if HI_OS_TYPE == HI_OS_WIN32
 #define HI_INLINE __inline
 #define HI_VSNPRINTF _vsnprintf
 #define HI_SNPRINTF _snprintf
#else
 #define HI_INLINE inline
 #define HI_VSNPRINTF vsnprintf
 #define HI_SNPRINTF snprintf
#endif

#if 0 /* asy tmp, previously defined in hi_common.h */

/*-----------------------------------------------------------------
断言
-----------------------------------------------------------------*/
 #define HI_ASSERT_ENABLE 1
 #ifndef HI_ASSERT/*avoid warning*/
  #ifdef  HI_ASSERT_ENABLE
   #define HI_ASSERT(expr) \
    do {                                                                        \
        if (!(expr))                                                            \
        {                                                                       \
            HI_LOG_FATAL(HI_FAILURE, "Assert error!");                          \
            exit(HI_FAILURE);                                                   \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
  #else
   #define HI_ASSERT(expr)
  #endif
 #endif

#endif

/*-----------------------------------------------------------------
错误判断
-----------------------------------------------------------------*/
#define HI_LOG_CHK_RETURN( val  ) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HI_LOG_OUTPUTF( HI_ERR_LEVEL_ERROR, HI_EINVAL, ""); \
            return;                                    \
        };                                                   \
    } while (0)

//函数参数检查
#define HI_LOG_CHK_PARA( val  ) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HI_LOG_OUTPUTF( HI_ERR_LEVEL_ERROR, HI_EINVAL, ""); \
            return HI_EINVAL;                                    \
        };                                                   \
    } while (0)

/*-----------------------------------------------------------------*/

// 检查期望值，如果不对，返回该指定错误码 , val要写错误情况的判断
#define HI_LOG_CHK_RETURN_ERR(val, ret ) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HI_LOG_ERROR_NO(  ret, "");                       \
            return ret;                                    \
        }                                                   \
    } while (0)

/*-----------------------------------------------------------------*/

// 检查期望值，如果不对，打印错误信息, val要写错误情况的判断
#define HI_LOG_CHK_PRINT_ERR(val, ret) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HI_LOG_ERROR_NO(  ret, "");                    \
        }                                                   \
    } while (0)

/*-----------------------------------------------------------------*/

/* 如果func执行失败，只打印出错信息，不返回 */
#define HI_LOG_DOFUNC( func ) \
    do {                                         \
        HI_S32 ret = 0;                        \
        ret = func;                            \
        if (ret != HI_SUCCESS)                   \
        {                                        \
            HI_LOG_ERROR_NO(  ret, "CALL %s", # func);           \
        };                                       \
    } while (0)

/*-----------------------------------------------------------------*/
/* 如果func执行失败，则直接返回被调函数的返回值 */
#define HI_LOG_DOFUNC_RETURN( func ) \
    do {                                         \
        HI_S32 ret = 0;                        \
        ret = func;                            \
        if (ret != HI_SUCCESS)                   \
        {                                        \
            HI_LOG_ERROR_NO(  ret, "CALL %s", # func);          \
            return ret;                        \
        };                                       \
    } while (0)

/*-----------------------------------------------------------------*/
/* 如果func执行失败，则返回指定的错误码 */
#define HI_LOG_DOFUNC_RETURN_ERR( func, err) \
    do {                                         \
        HI_S32 ret = 0;                        \
        ret = func;                            \
        if (ret != HI_SUCCESS)                   \
        {                                        \
            HI_LOG_ERROR_NO(  ret, "CALL %s", # func);          \
            return err;                        \
        };                                       \
    } while (0)

/*-----------------------------------------------------------------*/
/* 如果func执行失败，则返回void */
#define HI_LOG_DOFUNC_RETURN_VOID(func) \
    do {\
        HI_S32 ret = func;                  \
        if (ret != HI_SUCCESS)               \
        { \
            HI_LOG_ERROR_NO(  ret, "CALL %s", # func);    \
            return;                        \
        }                                   \
    } while (0)

/*-----------------------------------------------------------------*/

#define HI_LOG_DOFUNC_GOTO(func, errhandle) \
    do {\
        HI_S32 s32Ret = func; \
        if (s32Ret != HI_SUCCESS)\
        {\
            HI_LOG_ERROR("%s fail:0x%x, line:%d\n", # func, s32Ret, __LINE__); \
            goto errhandle; \
        } \
    } while (0)

/*-----------------------------------------------------------------*/
/*****************************************************************************/

/* 每条日志的最大字节数 */
#define HI_LOG_SIZE_MAX 256

/******************************* API declaration *****************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE

/***********************************************************************************
* Function:     HI_LOG_Init
* Description:  初始化日志功能
* Input:
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_ENORES : 资源不够，初始化失败
*           HI_LOG_EACCES: 访问资源权限有问题
*           HI_LOG_EINTER: 内部错误
***********************************************************************************/
HI_ERRNO        HI_LOG_Init();

/***********************************************************************************
* Function:     HI_LOG_DeInit
* Description:  去初始化日志功能
* Input:
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EACCES: 访问资源权限有问题
*           HI_LOG_EINTER: 内部错误
***********************************************************************************/
HI_ERRNO        HI_LOG_DeInit();

/***********************************************************************************
* Function:     HI_LOG_Outputf
* Description:  输出日志
* Input:    u32ModID:模块ID号
            enErrLevel:错误码级别
            enoErrno:错误码
            pszProgramFileName:出错的源代码程序文件名
            pszProgramFunctionName:出错的源代码程序函数名
            s32ProgramLineNo:出错的源代码行号
            pszFormat:输出日志字符串格式，用法与printf相同
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EUNALLOW:这个模块的这个级别错误码目前处于屏蔽之中，不允许输出
*           HI_LOG_EACCES:输出权限问题
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_Outputf(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                               const HI_CHAR * pszProgramFileName, const HI_CHAR * pszProgramFunctionName,
                               HI_S32 s32ProgramLineNo,
                               const HI_CHAR * pszFormat,
                               ...);

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_OutputfAuto
* Description:  输出日志
* Input:    u32ModID:   模块ID号
            enErrLevel: 错误码级别
            enoErrno:   错误码
            pszFormat:输出日志字符串格式，用法与printf相同
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EUNALLOW:这个模块的这个级别错误码目前处于屏蔽之中，不允许输出
*           HI_LOG_EACCES:输出权限问题
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputfAuto(HI_U32 u32ModID,
                                   HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                   const HI_CHAR * pszFormat, ...);
 #endif

/***********************************************************************************
* Function:     HI_LOG_OutputValist
* Description:  输出日志
* Input:    u32ModID:   模块ID号
            enErrLevel: 错误码级别
            enoErrno:   错误码
            pszProgramFileName:出错的源代码程序文件名
            pszProgramFunctionName:出错的源代码程序函数名
            s32ProgramLineNo:出错的源代码行号
            pszFormat:输出日志字符串格式，用法与printf相同
            aListArgs:输出日志变参
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EUNALLOW:这个模块的这个级别错误码目前处于屏蔽之中，不允许输出
*           HI_LOG_EACCES:输出权限问题
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputValist(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                    const HI_CHAR * pszProgramFileName, const HI_CHAR * pszProgramFunctionName,
                                    HI_S32 s32ProgramLineNo, const HI_CHAR * pszFormat, va_list *pvaListArgs);

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_OutputValistAuto
* Description:  输出日志
* Input:    u32ModID:   模块ID号
            enErrLevel: 错误码级别
            enoErrno:   错误码
            pszFormat:输出日志字符串格式，用法与printf相同
            aListArgs:输出日志变参
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EUNALLOW:这个模块的这个级别错误码目前处于屏蔽之中，不允许输出
*           HI_LOG_EACCES:输出权限问题
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputValistAuto(HI_U32 u32ModID,
                                        HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                        const HI_CHAR * pszFormat, va_list *pvaListArgs);
 #endif

/***********************************************************************************
* Function:     HI_LOG_OutputString
* Description:  输出日志
* Input:    u32ModID:   模块ID号
            enErrLevel: 错误码级别
            enoErrno:   错误码
            pszProgramFileName:出错的源代码程序文件名
            pszProgramFunctionName:出错的源代码程序函数名
            s32ProgramLineNo:出错的源代码行号
            pszOutputString:输出串信息
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EUNALLOW:这个模块的这个级别错误码目前处于屏蔽之中，不允许输出
*           HI_LOG_EACCES:输出权限问题
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputString(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                    const HI_CHAR * pszProgramFileName, const HI_CHAR * pszProgramFunctionName,
                                    HI_S32 s32ProgramLineNo, const HI_CHAR * pszOutputString);

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_OutputStringAuto
* Description:  输出日志
* Input:    u32ModID:   模块ID号
            enErrLevel: 错误码级别
            enoErrno:   错误码
            pszOutputString:输出串信息
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EUNALLOW:这个模块的这个级别错误码目前处于屏蔽之中，不允许输出
*           HI_LOG_EACCES:输出权限问题
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputStringAuto(HI_U32 u32ModID,
                                        HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                        const HI_CHAR * pszOutputString);

 #endif

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_SaveAutoData
* Description:  保存自动数据
* Input:    pszFileName:文件名
*           pszFunction:函数名
*           s32Line:行号
*           u32Flag2:标志2
*           u32Flag1:标志1
* Output:
* Return:
***********************************************************************************/
HI_VOID            HI_LOG_SaveAutoData(HI_CHAR *pszFileName, HI_CHAR *pszFunction, HI_S32 s32Line);

/***********************************************************************************
* Function:     HI_LOG_SaveAutoData
* Description:  保存自动数据
* Input:
* Output:   ppszFileName:文件名
*           ppszFunction:函数名
*           ps32Line:行号
* Return:
***********************************************************************************/
HI_VOID            HI_LOG_GetAutoData(HI_CHAR **ppszFileName, HI_CHAR **ppszFunction, HI_S32 *ps32Line);

 #endif

/***********************************************************************************
* Function:     HI_LOG_AllowOutput
* Description:  查询是否允许输出日志
* Input:    u32ModID:模块ID号
            enErrLevel:错误码级别
* Output:
* Return:   HI_TRUE:可以输出日志
*           HI_FALSE :不允许输出日志或发生错误
***********************************************************************************/
HI_BOOL            HI_LOG_AllowOutput(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel);

/***********************************************************************************
* Function:     HI_LOG_SetOutputSequence
* Description:  设置输出日志是否按照顺序进行
* Input:    bSequence:HI_TRUE:确保按顺序输出
                HI_FALSE:不确保按顺序输出
* Output:
* Return:
* Other:确保按顺序输出将降低性能
***********************************************************************************/
HI_VOID            HI_LOG_SetOutputSequence(HI_BOOL bSequence);

HI_VOID            HI_LOG_OutputTime(const HI_CHAR * pszOutputString);
HI_VOID            HI_LOG_OutputTimeStart(const HI_CHAR * pszOutputString);

/***********************************************************************************
* Function:     HI_LOG_GetErrString
* Description:  Get the error string by error code
* Input:        s32ErrNo: error code
* Return:       error string if not found return "UNDEF_ERRSTR"
***********************************************************************************/
const HI_CHAR * HI_LOG_GetErrString(HI_S32 s32ErrNo );

/***********************************************************************************
* Function:     HI_LOG_SetAllowOutput
* Description:  设置是否允许输出日志
* Input:    u32ModID:模块ID号
            enErrLevel:错误码级别
            bAllow:是否允许输出
* Output:   无
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO        HI_LOG_SetAllowOutput(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel,
                                      HI_BOOL bAllow);
#endif
#ifdef __cplusplus
 #if __cplusplus
}
 #endif /* __cplusplus */
#endif  /* __cplusplus */

#endif /*__HI_LOG_H__*/
