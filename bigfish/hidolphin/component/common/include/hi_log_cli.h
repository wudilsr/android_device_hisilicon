/***********************************************************************************
*             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
******************************************************************************
* FileName: hi_log_cli.h
* Description:LOG与CLI接口
*
* History:
* Version  Date        Author     DefectNum  Description
* 1.0      2009/03/19  l111160    NULL       Create this file.
***********************************************************************************/

#ifndef __HI_LOG_CLI_H__
#define __HI_LOG_CLI_H__


#include <string.h>
#include "hi_type.h"
#include "hi_debug.h"
//#include "hi_ref_errno.h"
#include "hi_log.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */



/***************************** Macro Definition ******************************/

/*-----------------------------------------------------------------
以下数据中使用这一组宏:
    1、函数HI_LOG_SetDefaultFormat中的参数u32Format
    2、HI_LOG_MOD_CONTROL_BLOCK_S中的u32Format
-----------------------------------------------------------------*/
#define HI_LOG_OUTPUT_FMT_NONE      0x0         /* 不输出 */
#define HI_LOG_OUTPUT_FMT_DEFAULT   0x1         /* 默认 */
#define HI_LOG_OUTPUT_FMT_YEAR      0x2         /* 年 */
#define HI_LOG_OUTPUT_FMT_MONTH     0x4         /* 月 */
#define HI_LOG_OUTPUT_FMT_DAY       0x8         /* 日 */
#define HI_LOG_OUTPUT_FMT_HOUR      0x10        /* 时 */
#define HI_LOG_OUTPUT_FMT_MIN       0x20        /* 分 */
#define HI_LOG_OUTPUT_FMT_SEC       0x40        /* 秒 */
#define HI_LOG_OUTPUT_FMT_MSEC      0x80        /* 毫秒 */
#define HI_LOG_OUTPUT_FMT_MODID     0x100       /* 模块ID */
#define HI_LOG_OUTPUT_FMT_MODNAME   0x200       /* 模块名 */
#define HI_LOG_OUTPUT_FMT_ERRLEVEL  0x400       /* 错误级别号 */
#define HI_LOG_OUTPUT_FMT_ERRNAME   0x800       /* 错误级别名 */
#define HI_LOG_OUTPUT_FMT_ERRNO     0x1000      /* 错误号 */
#define HI_LOG_OUTPUT_FMT_ERRINFO   0x2000      /* 错误信息 */
#define HI_LOG_OUTPUT_FMT_PATH      0x4000      /* 程序全路径名 */
#define HI_LOG_OUTPUT_FMT_FILE      0x8000      /* 程序文件名 */
#define HI_LOG_OUTPUT_FMT_FUNC      0x10000     /* 函数名 */
#define HI_LOG_OUTPUT_FMT_LINENO    0x20000     /* 行号 */
#define HI_LOG_OUTPUT_FMT_USER      0x40000     /* 用户信息 */
#define HI_LOG_OUTPUT_FMT_ALL (0                                                \
          | HI_LOG_OUTPUT_FMT_YEAR                                              \
          | HI_LOG_OUTPUT_FMT_MONTH                                             \
          | HI_LOG_OUTPUT_FMT_DAY                                               \
          | HI_LOG_OUTPUT_FMT_HOUR                                              \
          | HI_LOG_OUTPUT_FMT_MIN                                               \
          | HI_LOG_OUTPUT_FMT_SEC                                               \
          | HI_LOG_OUTPUT_FMT_MSEC                                              \
          | HI_LOG_OUTPUT_FMT_MODID                                             \
          | HI_LOG_OUTPUT_FMT_MODNAME                                           \
          | HI_LOG_OUTPUT_FMT_ERRLEVEL                                          \
          | HI_LOG_OUTPUT_FMT_ERRNAME                                           \
          | HI_LOG_OUTPUT_FMT_ERRNO                                             \
          | HI_LOG_OUTPUT_FMT_ERRINFO                                           \
          | HI_LOG_OUTPUT_FMT_PATH                                              \
          | HI_LOG_OUTPUT_FMT_FILE                                              \
          | HI_LOG_OUTPUT_FMT_FUNC                                              \
          | HI_LOG_OUTPUT_FMT_LINENO                                            \
          | HI_LOG_OUTPUT_FMT_USER                                              \
        )

/*-----------------------------------------------------------------
以下数据中使用这一组宏:
    1、函数HI_LOG_SetOutputMode中的参数u32OutputMode
    2、HI_LOG_MOD_CONTROL_BLOCK_S中的u32OutputMode
-----------------------------------------------------------------*/
#define HI_LOG_OUTPUT_MODE_NONE     0x1         /* 不输出 */
#define HI_LOG_OUTPUT_MODE_DEFAULT  0x2         /* 默认 */
#define HI_LOG_OUTPUT_MODE_COM      0x4         /* 串口 */
#define HI_LOG_OUTPUT_MODE_TELNET   0x8         /* telnet */
#define HI_LOG_OUTPUT_MODE_FILE     0x10        /* 指定的文件 */
#define HI_LOG_OUTPUT_MODE_PROTOCOL 0x20        /* 指定的协议 */

struct hiLOG_MOD_CONTROL_BLOCK_S;
struct hiLOG_OUTPUT_INFO_S;

/* 日志输出回调函数 */
typedef HI_ERRNO (*LOG_OUTPUT_CALLBACK_FN_PTR)(struct hiLOG_OUTPUT_INFO_S *);

/* 模块日志控制块*/
typedef struct hiLOG_MOD_CONTROL_BLOCK_S
{
    HI_BOOL bAllowOutput[HI_ERR_LEVEL_BUTT];  /* 是否允许输出 */
    HI_U32 u32Format;                           /* 使用默认格式函数时的格式控制 */
    HI_U32 u32OutputMode;                       /* 输出模式 */
    HI_CHAR *pszOutputName;                     /* 输出目标名 */
    LOG_OUTPUT_CALLBACK_FN_PTR pfnOutputCallback;/* 回调函数 */
    HI_BOOL bGetTime;                           /* 是否需要取时间 */
    HI_BOOL bGetMsec;                           /* 是否需要取毫秒 */
    HI_BOOL bColor;                             /* 显示彩色 */
    HI_BOOL bPad1;                              /* 填充 */
} HI_LOG_MOD_CONTROL_BLOCK_S;

/* 输出原始信息 */
typedef struct hiLOG_OUTPUT_INFO_S
{
    HI_S32  s32Year;                            /* 年 */
    HI_S32  s32Month;                           /* 月 */
    HI_S32  s32Day;                             /* 日 */
    HI_S32  s32Hour;                            /* 时 */
    HI_S32  s32Min;                             /* 分 */
    HI_S32  s32Sec;                             /* 秒 */
    HI_S32  s32Msec;                            /* 毫秒 */
    HI_U32 u32ModID;                            /* 模块ID */
    HI_ERR_LEVEL_E enErrLevel;                  /* 错误级别号 */
    HI_ERRNO enoErrno;                          /* 错误号 */
    HI_S32 s32ProgramLineNo;                    /* 行号 */
    HI_U32 u32Pad;                              /* 填充 */
    const HI_CHAR * pszPathName;                /* 程序全路径名 */
    const HI_CHAR * pszProgramName;             /* 程序文件名 */
    const HI_CHAR * pszFunctionName;            /* 函数名 */
    const HI_CHAR * pszUserInfo;                /* 用户信息 */
    HI_CHAR * pszPrintData;                     /* 打印日志数据 */
    HI_CHAR * pszPad1;                          /* 填充 */
    HI_LOG_MOD_CONTROL_BLOCK_S stMCB;           /* 模块控制块 */
} HI_LOG_OUTPUT_INFO_S;

#ifndef HI_ADVCA_FUNCTION_RELEASE


/*-----------------------------------------------------------------
以下是一批用于检查变量合法性的宏
-----------------------------------------------------------------*/

/* 检查BOOL变量合法性*/
#define HI_LOG_BOOL_CHECK(vol, enoErrno)                                        \
    do {                                                                        \
        if (!(HI_TRUE == (vol) || HI_FALSE == (vol)))                           \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_BOOL_ASSERT(vol)                                                 \
        HI_ASSERT(HI_TRUE == (vol) || HI_FALSE == (vol))

/* 检查指针合法性*/
#define HI_LOG_POINTER_CHECK(vol, enoErrno)                                     \
    do {                                                                        \
        if (!(HI_NULL != (vol)))                                                \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_POINTER_ASSERT(vol)                                              \
        HI_ASSERT(HI_NULL != (vol))

/* 检查模块ID合法性*/
#define HI_LOG_MODID_CHECK(enModID, enoErrno)                                   \
    do {                                                                        \
        if (!((HI_U32)(enModID) < (HI_U32)HI_MOD_MAX_NUM))                    \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_MODID_ASSERT(enModID)                                            \
        HI_ASSERT((HI_U32)(enModID) < (HI_U32)HI_MOD_MAX_NUM)

/* 检查错误级别合法性*/
#define HI_LOG_ERRLEVEL_CHECK(enErrLevel, enoErrno)                             \
    do {                                                                        \
        if (!((HI_U32)(enErrLevel) < (HI_U32)HI_ERR_LEVEL_BUTT))              \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_ERRLEVEL_ASSERT(enErrLevel)                                      \
        HI_ASSERT((HI_U32)(enErrLevel) < (HI_U32)HI_ERR_LEVEL_BUTT)

/* 检查输出模式合法性*/
#define HI_LOG_OUTPUT_MODE_CHECK(mode, name, enoErrno)                          \
    do {                                                                        \
        if ( ((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_FILE) &&                      \
             ((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_PROTOCOL) )                   \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
        if ( (HI_NULL == (name)) &&                                             \
             (((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_FILE) ||                     \
              ((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_PROTOCOL)) )                 \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_OUTPUT_MODE_ASSERT(mode, name)                                   \
    HI_ASSERT(!(((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_FILE) &&                   \
                ((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_PROTOCOL)));               \
    HI_ASSERT(!( (HI_NULL == (name)) &&                                         \
         (((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_FILE) ||                         \
          ((HI_U32)(mode) & HI_LOG_OUTPUT_MODE_PROTOCOL)) ))


/* 以下几个宏可在格式函数中使用 */
/* HI_LOG_OUTPUT_VOLUME用于输出一个值 */
#undef  HI_LOG_OUTPUT_VOLUME
#define HI_LOG_OUTPUT_VOLUME(vol_type, format_str, vol, buf, buf_size, len, format, has_vol) \
    do                                                                          \
    {                                                                           \
        if ( ((format) & (HI_U32)(vol_type)) && (((buf_size)-1u)-(len) > 1u) )  \
        {                                                                       \
            (HI_VOID)HI_SNPRINTF((buf)+(len),                                   \
                (HI_U32)(((buf_size)-1u)-(len)), (const HI_CHAR *)(format_str), \
                (vol));                                                         \
            (buf)[(buf_size)-1u] = 0;                                           \
            (len) += (HI_U32)strlen((buf)+(len));                               \
            (has_vol) = HI_TRUE;                                                \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
/* HI_LOG_OUTPUT_SPACE用于输出一个间隔符 */
#undef HI_LOG_OUTPUT_SPACE
#define HI_LOG_OUTPUT_SPACE(vol_type, space, buf, buf_size, len, format, has_vol)  \
    do                                                                          \
    {                                                                           \
        if ( ((format) & (HI_U32)(vol_type)) && (HI_TRUE == (has_vol)) &&       \
             (((buf_size)-1u)-(len) > 1u) )                                     \
        {                                                                       \
            (buf)[(len)++] = (HI_CHAR)(space);                                  \
            (buf)[(len)] = 0;                                                   \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
/* HI_LOG_OUTPUT_SP_VOL用于输出一个间隔符和一个值 */
#undef HI_LOG_OUTPUT_SP_VOL
#define HI_LOG_OUTPUT_SP_VOL(vol_type, space, format_str, vol, buf, buf_size, len, format, has_vol) \
    HI_LOG_OUTPUT_SPACE((vol_type), (space), (buf), (buf_size), (len), (format), (has_vol)); \
    HI_LOG_OUTPUT_VOLUME((vol_type), (format_str), (vol), (buf), (buf_size), (len), (format), (has_vol))


/******************************* API declaration *****************************/

/***********************************************************************************
* Function:     HI_LOG_SetCallbackFunction
* Description:  设置日志回调函数
* Input:    u32ModID:模块ID号
*           pfnCallbackFunction:回调函数
*               HI_NULL:表示设置成默认的函数HI_LOG_DefaultCallback
* Output:   无
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_SetCallbackFunction(HI_U32 u32ModID, LOG_OUTPUT_CALLBACK_FN_PTR pfnCallbackFunction);

/***********************************************************************************
* Function:     HI_LOG_DefaultCallback
* Description:  默认的输出回调格式
* Input:    pstInfo:   输入
* Output:   pstInfo
* Return:   HI_SUCCESS: success
***********************************************************************************/
HI_ERRNO HI_LOG_DefaultCallback(HI_LOG_OUTPUT_INFO_S *pstInfo);

/***********************************************************************************
* Function:     HI_LOG_SetOutputFormat
* Description:  设置输出格式
* Input:    u32ModID:模块ID号
*           u32Format:指定输出格式
* Output:   无
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_SetOutputFormat(HI_U32 u32ModID, HI_U32 u32Format);


/***********************************************************************************
* Function:     HI_LOG_SetOutputMode
* Description:  设置输出模式
* Input:    u32ModID:模块ID号
*           u32OutputMode:指定输出模式
*           pszOutputName:指定的文件名或者协议名
* Output:   无
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_SetOutputMode(HI_U32 u32ModID, HI_U32 u32OutputMode,
            HI_CHAR *pszOutputName);


/***********************************************************************************
* Function:     HI_LOG_SetOutputColor
* Description:  设置输出彩色
* Input:    u32ModID:模块ID号
*           bColor:指定是否打开彩色
* Output:   无
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_SetOutputColor(HI_U32 u32ModID, HI_BOOL bColor);


/***********************************************************************************
* Function:     HI_LOG_SetGetTimeMsec
* Description:  设置是否取时间和毫秒
* Input:    u32ModID:模块ID号
*           bGetTime:取日期和时间(精确到秒)
*           bGetMsec:取毫秒,如果bGetTime为HI_FALSE则bGetMsec必定为HI_FALSE
* Output:   无
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_SetGetTimeMsec(HI_U32 u32ModID, HI_BOOL bGetTime, HI_BOOL bGetMsec);


/***********************************************************************************
* Function:     HI_LOG_GetModCB
* Description:  获得一个模块的控制块参数
* Input:    u32ModID:模块ID号
* Output:   pstCB:返回结果
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_GetModCB(HI_U32 u32ModID, HI_LOG_MOD_CONTROL_BLOCK_S *pstCB);

/***********************************************************************************
* Function:     HI_LOG_SaveSetup
* Description:  保存一个模块的设置参数,包括以下函数设置的参数:
*                   HI_LOG_SetAllowOutput
*                   HI_LOG_SetCallbackFunction
*                   HI_LOG_SetOutputFormat
*                   HI_LOG_SetOutputMode
* Input:    u32ModID:模块ID号
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_SaveSetup(HI_U32 u32ModID);

/***********************************************************************************
* Function:     HI_LOG_RestoreSetup
* Description:  回复一个模块通过HI_LOG_SaveSetup保存的设置参数
* Input:    u32ModID:模块ID号
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:参数错误
*           HI_LOG_EINTER: 内部错误
*           HI_LOG_ENOTINIT:未初始化
***********************************************************************************/
HI_ERRNO HI_LOG_RestoreSetup(HI_U32 u32ModID);

/***********************************************************************************
* Function:     HI_LOG_LockOutput
* Description:  加锁输出
* Input:    bLock:HI_TRUE:一定会加锁
                HI_FALSE:是否加锁由HI_LOG_SetOutputSequence控制
* Output:
* Return:   锁成功返回HI_TRUE
***********************************************************************************/
HI_BOOL HI_LOG_LockOutput(HI_BOOL bLock);

/***********************************************************************************
* Function:     HI_LOG_UnlockOutput
* Description:  解锁输出
* Input:    bLock:
* Output:
* Return:
***********************************************************************************/
HI_VOID HI_LOG_UnlockOutput(HI_BOOL bLock);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_LOG_CLI_H__ */
