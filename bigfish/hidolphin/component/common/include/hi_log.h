/***********************************************************************************
*             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
******************************************************************************
* FileName: hi_log.h
* Description:S2��Ŀ������־ͷ�ļ�
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
����ǵ��԰汾����Ӧ����Makefile�ж����LOG_DEBUG_ENABLE
-----------------------------------------------------------------*/

#define HI_LOG_DO_WHILE_ZERO /*lint -e(717) */ (0)

/* ����5���ȼ�*/
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
��ģ�����־�����:
HI_LOG_DEBUG��HI_LOG_INFOһ�����ڵ��ԣ�û�д����룬
HI_LOG_ERROR��HI_LOG_FATALһ��������־���д�����
HI_LOG_OUTOUTFͨ�����������
-----------------------------------------------------------------*/
#if HI_OS_TYPE == HI_OS_LINUX

 #ifndef     __THIS_LOG_MOD_ID
  #define      __THIS_LOG_MOD_ID HI_MOD_ID_NULL
 #endif

 #ifndef HI_ADVCA_FUNCTION_RELEASE

//ͨ�������Ϣ����
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

 // ������Ϣ�������ָ��������
 #define HI_LOG_ERROR_NO( error_no, pszFormat...)\
  HILOG_FIT_SVRLOG(HI_ERR_LEVEL_ERROR,error_no,pszFormat)


// ����������Ϣ�������ָ��������
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
���ʹ��VC6����ÿ������ǰ��������¶���
#ifdef HI_LOG_FUNCTION_HAND
#undef  __FUNCTION__
#define __FUNCTION__ "������"
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
�����������
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
����
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
�����ж�
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

//�����������
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

// �������ֵ��������ԣ����ظ�ָ�������� , valҪд����������ж�
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

// �������ֵ��������ԣ���ӡ������Ϣ, valҪд����������ж�
#define HI_LOG_CHK_PRINT_ERR(val, ret) \
    do                                                      \
    {                                                       \
        if ((val))                                          \
        {                                                   \
            HI_LOG_ERROR_NO(  ret, "");                    \
        }                                                   \
    } while (0)

/*-----------------------------------------------------------------*/

/* ���funcִ��ʧ�ܣ�ֻ��ӡ������Ϣ�������� */
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
/* ���funcִ��ʧ�ܣ���ֱ�ӷ��ر��������ķ���ֵ */
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
/* ���funcִ��ʧ�ܣ��򷵻�ָ���Ĵ����� */
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
/* ���funcִ��ʧ�ܣ��򷵻�void */
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

/* ÿ����־������ֽ��� */
#define HI_LOG_SIZE_MAX 256

/******************************* API declaration *****************************/
#ifndef HI_ADVCA_FUNCTION_RELEASE

/***********************************************************************************
* Function:     HI_LOG_Init
* Description:  ��ʼ����־����
* Input:
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_ENORES : ��Դ��������ʼ��ʧ��
*           HI_LOG_EACCES: ������ԴȨ��������
*           HI_LOG_EINTER: �ڲ�����
***********************************************************************************/
HI_ERRNO        HI_LOG_Init();

/***********************************************************************************
* Function:     HI_LOG_DeInit
* Description:  ȥ��ʼ����־����
* Input:
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EACCES: ������ԴȨ��������
*           HI_LOG_EINTER: �ڲ�����
***********************************************************************************/
HI_ERRNO        HI_LOG_DeInit();

/***********************************************************************************
* Function:     HI_LOG_Outputf
* Description:  �����־
* Input:    u32ModID:ģ��ID��
            enErrLevel:�����뼶��
            enoErrno:������
            pszProgramFileName:�����Դ��������ļ���
            pszProgramFunctionName:�����Դ�����������
            s32ProgramLineNo:�����Դ�����к�
            pszFormat:�����־�ַ�����ʽ���÷���printf��ͬ
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EUNALLOW:���ģ���������������Ŀǰ��������֮�У����������
*           HI_LOG_EACCES:���Ȩ������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO        HI_LOG_Outputf(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                               const HI_CHAR * pszProgramFileName, const HI_CHAR * pszProgramFunctionName,
                               HI_S32 s32ProgramLineNo,
                               const HI_CHAR * pszFormat,
                               ...);

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_OutputfAuto
* Description:  �����־
* Input:    u32ModID:   ģ��ID��
            enErrLevel: �����뼶��
            enoErrno:   ������
            pszFormat:�����־�ַ�����ʽ���÷���printf��ͬ
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EUNALLOW:���ģ���������������Ŀǰ��������֮�У����������
*           HI_LOG_EACCES:���Ȩ������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputfAuto(HI_U32 u32ModID,
                                   HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                   const HI_CHAR * pszFormat, ...);
 #endif

/***********************************************************************************
* Function:     HI_LOG_OutputValist
* Description:  �����־
* Input:    u32ModID:   ģ��ID��
            enErrLevel: �����뼶��
            enoErrno:   ������
            pszProgramFileName:�����Դ��������ļ���
            pszProgramFunctionName:�����Դ�����������
            s32ProgramLineNo:�����Դ�����к�
            pszFormat:�����־�ַ�����ʽ���÷���printf��ͬ
            aListArgs:�����־���
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EUNALLOW:���ģ���������������Ŀǰ��������֮�У����������
*           HI_LOG_EACCES:���Ȩ������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputValist(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                    const HI_CHAR * pszProgramFileName, const HI_CHAR * pszProgramFunctionName,
                                    HI_S32 s32ProgramLineNo, const HI_CHAR * pszFormat, va_list *pvaListArgs);

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_OutputValistAuto
* Description:  �����־
* Input:    u32ModID:   ģ��ID��
            enErrLevel: �����뼶��
            enoErrno:   ������
            pszFormat:�����־�ַ�����ʽ���÷���printf��ͬ
            aListArgs:�����־���
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EUNALLOW:���ģ���������������Ŀǰ��������֮�У����������
*           HI_LOG_EACCES:���Ȩ������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputValistAuto(HI_U32 u32ModID,
                                        HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                        const HI_CHAR * pszFormat, va_list *pvaListArgs);
 #endif

/***********************************************************************************
* Function:     HI_LOG_OutputString
* Description:  �����־
* Input:    u32ModID:   ģ��ID��
            enErrLevel: �����뼶��
            enoErrno:   ������
            pszProgramFileName:�����Դ��������ļ���
            pszProgramFunctionName:�����Դ�����������
            s32ProgramLineNo:�����Դ�����к�
            pszOutputString:�������Ϣ
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EUNALLOW:���ģ���������������Ŀǰ��������֮�У����������
*           HI_LOG_EACCES:���Ȩ������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputString(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                    const HI_CHAR * pszProgramFileName, const HI_CHAR * pszProgramFunctionName,
                                    HI_S32 s32ProgramLineNo, const HI_CHAR * pszOutputString);

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_OutputStringAuto
* Description:  �����־
* Input:    u32ModID:   ģ��ID��
            enErrLevel: �����뼶��
            enoErrno:   ������
            pszOutputString:�������Ϣ
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EUNALLOW:���ģ���������������Ŀǰ��������֮�У����������
*           HI_LOG_EACCES:���Ȩ������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO        HI_LOG_OutputStringAuto(HI_U32 u32ModID,
                                        HI_ERR_LEVEL_E enErrLevel, HI_ERRNO enoErrno,
                                        const HI_CHAR * pszOutputString);

 #endif

 #if HI_OS_TYPE == HI_OS_WIN32

/***********************************************************************************
* Function:     HI_LOG_SaveAutoData
* Description:  �����Զ�����
* Input:    pszFileName:�ļ���
*           pszFunction:������
*           s32Line:�к�
*           u32Flag2:��־2
*           u32Flag1:��־1
* Output:
* Return:
***********************************************************************************/
HI_VOID            HI_LOG_SaveAutoData(HI_CHAR *pszFileName, HI_CHAR *pszFunction, HI_S32 s32Line);

/***********************************************************************************
* Function:     HI_LOG_SaveAutoData
* Description:  �����Զ�����
* Input:
* Output:   ppszFileName:�ļ���
*           ppszFunction:������
*           ps32Line:�к�
* Return:
***********************************************************************************/
HI_VOID            HI_LOG_GetAutoData(HI_CHAR **ppszFileName, HI_CHAR **ppszFunction, HI_S32 *ps32Line);

 #endif

/***********************************************************************************
* Function:     HI_LOG_AllowOutput
* Description:  ��ѯ�Ƿ����������־
* Input:    u32ModID:ģ��ID��
            enErrLevel:�����뼶��
* Output:
* Return:   HI_TRUE:���������־
*           HI_FALSE :�����������־��������
***********************************************************************************/
HI_BOOL            HI_LOG_AllowOutput(HI_U32 u32ModID, HI_ERR_LEVEL_E enErrLevel);

/***********************************************************************************
* Function:     HI_LOG_SetOutputSequence
* Description:  ���������־�Ƿ���˳�����
* Input:    bSequence:HI_TRUE:ȷ����˳�����
                HI_FALSE:��ȷ����˳�����
* Output:
* Return:
* Other:ȷ����˳���������������
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
* Description:  �����Ƿ����������־
* Input:    u32ModID:ģ��ID��
            enErrLevel:�����뼶��
            bAllow:�Ƿ��������
* Output:   ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
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
