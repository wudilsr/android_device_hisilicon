/***********************************************************************************
*             Copyright 2009 - 2050, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
******************************************************************************
* FileName: hi_log_cli.h
* Description:LOG��CLI�ӿ�
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
����������ʹ����һ���:
    1������HI_LOG_SetDefaultFormat�еĲ���u32Format
    2��HI_LOG_MOD_CONTROL_BLOCK_S�е�u32Format
-----------------------------------------------------------------*/
#define HI_LOG_OUTPUT_FMT_NONE      0x0         /* ����� */
#define HI_LOG_OUTPUT_FMT_DEFAULT   0x1         /* Ĭ�� */
#define HI_LOG_OUTPUT_FMT_YEAR      0x2         /* �� */
#define HI_LOG_OUTPUT_FMT_MONTH     0x4         /* �� */
#define HI_LOG_OUTPUT_FMT_DAY       0x8         /* �� */
#define HI_LOG_OUTPUT_FMT_HOUR      0x10        /* ʱ */
#define HI_LOG_OUTPUT_FMT_MIN       0x20        /* �� */
#define HI_LOG_OUTPUT_FMT_SEC       0x40        /* �� */
#define HI_LOG_OUTPUT_FMT_MSEC      0x80        /* ���� */
#define HI_LOG_OUTPUT_FMT_MODID     0x100       /* ģ��ID */
#define HI_LOG_OUTPUT_FMT_MODNAME   0x200       /* ģ���� */
#define HI_LOG_OUTPUT_FMT_ERRLEVEL  0x400       /* ���󼶱�� */
#define HI_LOG_OUTPUT_FMT_ERRNAME   0x800       /* ���󼶱��� */
#define HI_LOG_OUTPUT_FMT_ERRNO     0x1000      /* ����� */
#define HI_LOG_OUTPUT_FMT_ERRINFO   0x2000      /* ������Ϣ */
#define HI_LOG_OUTPUT_FMT_PATH      0x4000      /* ����ȫ·���� */
#define HI_LOG_OUTPUT_FMT_FILE      0x8000      /* �����ļ��� */
#define HI_LOG_OUTPUT_FMT_FUNC      0x10000     /* ������ */
#define HI_LOG_OUTPUT_FMT_LINENO    0x20000     /* �к� */
#define HI_LOG_OUTPUT_FMT_USER      0x40000     /* �û���Ϣ */
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
����������ʹ����һ���:
    1������HI_LOG_SetOutputMode�еĲ���u32OutputMode
    2��HI_LOG_MOD_CONTROL_BLOCK_S�е�u32OutputMode
-----------------------------------------------------------------*/
#define HI_LOG_OUTPUT_MODE_NONE     0x1         /* ����� */
#define HI_LOG_OUTPUT_MODE_DEFAULT  0x2         /* Ĭ�� */
#define HI_LOG_OUTPUT_MODE_COM      0x4         /* ���� */
#define HI_LOG_OUTPUT_MODE_TELNET   0x8         /* telnet */
#define HI_LOG_OUTPUT_MODE_FILE     0x10        /* ָ�����ļ� */
#define HI_LOG_OUTPUT_MODE_PROTOCOL 0x20        /* ָ����Э�� */

struct hiLOG_MOD_CONTROL_BLOCK_S;
struct hiLOG_OUTPUT_INFO_S;

/* ��־����ص����� */
typedef HI_ERRNO (*LOG_OUTPUT_CALLBACK_FN_PTR)(struct hiLOG_OUTPUT_INFO_S *);

/* ģ����־���ƿ�*/
typedef struct hiLOG_MOD_CONTROL_BLOCK_S
{
    HI_BOOL bAllowOutput[HI_ERR_LEVEL_BUTT];  /* �Ƿ�������� */
    HI_U32 u32Format;                           /* ʹ��Ĭ�ϸ�ʽ����ʱ�ĸ�ʽ���� */
    HI_U32 u32OutputMode;                       /* ���ģʽ */
    HI_CHAR *pszOutputName;                     /* ���Ŀ���� */
    LOG_OUTPUT_CALLBACK_FN_PTR pfnOutputCallback;/* �ص����� */
    HI_BOOL bGetTime;                           /* �Ƿ���Ҫȡʱ�� */
    HI_BOOL bGetMsec;                           /* �Ƿ���Ҫȡ���� */
    HI_BOOL bColor;                             /* ��ʾ��ɫ */
    HI_BOOL bPad1;                              /* ��� */
} HI_LOG_MOD_CONTROL_BLOCK_S;

/* ���ԭʼ��Ϣ */
typedef struct hiLOG_OUTPUT_INFO_S
{
    HI_S32  s32Year;                            /* �� */
    HI_S32  s32Month;                           /* �� */
    HI_S32  s32Day;                             /* �� */
    HI_S32  s32Hour;                            /* ʱ */
    HI_S32  s32Min;                             /* �� */
    HI_S32  s32Sec;                             /* �� */
    HI_S32  s32Msec;                            /* ���� */
    HI_U32 u32ModID;                            /* ģ��ID */
    HI_ERR_LEVEL_E enErrLevel;                  /* ���󼶱�� */
    HI_ERRNO enoErrno;                          /* ����� */
    HI_S32 s32ProgramLineNo;                    /* �к� */
    HI_U32 u32Pad;                              /* ��� */
    const HI_CHAR * pszPathName;                /* ����ȫ·���� */
    const HI_CHAR * pszProgramName;             /* �����ļ��� */
    const HI_CHAR * pszFunctionName;            /* ������ */
    const HI_CHAR * pszUserInfo;                /* �û���Ϣ */
    HI_CHAR * pszPrintData;                     /* ��ӡ��־���� */
    HI_CHAR * pszPad1;                          /* ��� */
    HI_LOG_MOD_CONTROL_BLOCK_S stMCB;           /* ģ����ƿ� */
} HI_LOG_OUTPUT_INFO_S;

#ifndef HI_ADVCA_FUNCTION_RELEASE


/*-----------------------------------------------------------------
������һ�����ڼ������Ϸ��Եĺ�
-----------------------------------------------------------------*/

/* ���BOOL�����Ϸ���*/
#define HI_LOG_BOOL_CHECK(vol, enoErrno)                                        \
    do {                                                                        \
        if (!(HI_TRUE == (vol) || HI_FALSE == (vol)))                           \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_BOOL_ASSERT(vol)                                                 \
        HI_ASSERT(HI_TRUE == (vol) || HI_FALSE == (vol))

/* ���ָ��Ϸ���*/
#define HI_LOG_POINTER_CHECK(vol, enoErrno)                                     \
    do {                                                                        \
        if (!(HI_NULL != (vol)))                                                \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_POINTER_ASSERT(vol)                                              \
        HI_ASSERT(HI_NULL != (vol))

/* ���ģ��ID�Ϸ���*/
#define HI_LOG_MODID_CHECK(enModID, enoErrno)                                   \
    do {                                                                        \
        if (!((HI_U32)(enModID) < (HI_U32)HI_MOD_MAX_NUM))                    \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_MODID_ASSERT(enModID)                                            \
        HI_ASSERT((HI_U32)(enModID) < (HI_U32)HI_MOD_MAX_NUM)

/* �����󼶱�Ϸ���*/
#define HI_LOG_ERRLEVEL_CHECK(enErrLevel, enoErrno)                             \
    do {                                                                        \
        if (!((HI_U32)(enErrLevel) < (HI_U32)HI_ERR_LEVEL_BUTT))              \
        {                                                                       \
            return (enoErrno);                                                  \
        }                                                                       \
    } while HI_LOG_DO_WHILE_ZERO
#define HI_LOG_ERRLEVEL_ASSERT(enErrLevel)                                      \
        HI_ASSERT((HI_U32)(enErrLevel) < (HI_U32)HI_ERR_LEVEL_BUTT)

/* ������ģʽ�Ϸ���*/
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


/* ���¼�������ڸ�ʽ������ʹ�� */
/* HI_LOG_OUTPUT_VOLUME�������һ��ֵ */
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
/* HI_LOG_OUTPUT_SPACE�������һ������� */
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
/* HI_LOG_OUTPUT_SP_VOL�������һ���������һ��ֵ */
#undef HI_LOG_OUTPUT_SP_VOL
#define HI_LOG_OUTPUT_SP_VOL(vol_type, space, format_str, vol, buf, buf_size, len, format, has_vol) \
    HI_LOG_OUTPUT_SPACE((vol_type), (space), (buf), (buf_size), (len), (format), (has_vol)); \
    HI_LOG_OUTPUT_VOLUME((vol_type), (format_str), (vol), (buf), (buf_size), (len), (format), (has_vol))


/******************************* API declaration *****************************/

/***********************************************************************************
* Function:     HI_LOG_SetCallbackFunction
* Description:  ������־�ص�����
* Input:    u32ModID:ģ��ID��
*           pfnCallbackFunction:�ص�����
*               HI_NULL:��ʾ���ó�Ĭ�ϵĺ���HI_LOG_DefaultCallback
* Output:   ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_SetCallbackFunction(HI_U32 u32ModID, LOG_OUTPUT_CALLBACK_FN_PTR pfnCallbackFunction);

/***********************************************************************************
* Function:     HI_LOG_DefaultCallback
* Description:  Ĭ�ϵ�����ص���ʽ
* Input:    pstInfo:   ����
* Output:   pstInfo
* Return:   HI_SUCCESS: success
***********************************************************************************/
HI_ERRNO HI_LOG_DefaultCallback(HI_LOG_OUTPUT_INFO_S *pstInfo);

/***********************************************************************************
* Function:     HI_LOG_SetOutputFormat
* Description:  ���������ʽ
* Input:    u32ModID:ģ��ID��
*           u32Format:ָ�������ʽ
* Output:   ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_SetOutputFormat(HI_U32 u32ModID, HI_U32 u32Format);


/***********************************************************************************
* Function:     HI_LOG_SetOutputMode
* Description:  �������ģʽ
* Input:    u32ModID:ģ��ID��
*           u32OutputMode:ָ�����ģʽ
*           pszOutputName:ָ�����ļ�������Э����
* Output:   ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_SetOutputMode(HI_U32 u32ModID, HI_U32 u32OutputMode,
            HI_CHAR *pszOutputName);


/***********************************************************************************
* Function:     HI_LOG_SetOutputColor
* Description:  ���������ɫ
* Input:    u32ModID:ģ��ID��
*           bColor:ָ���Ƿ�򿪲�ɫ
* Output:   ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_SetOutputColor(HI_U32 u32ModID, HI_BOOL bColor);


/***********************************************************************************
* Function:     HI_LOG_SetGetTimeMsec
* Description:  �����Ƿ�ȡʱ��ͺ���
* Input:    u32ModID:ģ��ID��
*           bGetTime:ȡ���ں�ʱ��(��ȷ����)
*           bGetMsec:ȡ����,���bGetTimeΪHI_FALSE��bGetMsec�ض�ΪHI_FALSE
* Output:   ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_SetGetTimeMsec(HI_U32 u32ModID, HI_BOOL bGetTime, HI_BOOL bGetMsec);


/***********************************************************************************
* Function:     HI_LOG_GetModCB
* Description:  ���һ��ģ��Ŀ��ƿ����
* Input:    u32ModID:ģ��ID��
* Output:   pstCB:���ؽ��
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_GetModCB(HI_U32 u32ModID, HI_LOG_MOD_CONTROL_BLOCK_S *pstCB);

/***********************************************************************************
* Function:     HI_LOG_SaveSetup
* Description:  ����һ��ģ������ò���,�������º������õĲ���:
*                   HI_LOG_SetAllowOutput
*                   HI_LOG_SetCallbackFunction
*                   HI_LOG_SetOutputFormat
*                   HI_LOG_SetOutputMode
* Input:    u32ModID:ģ��ID��
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_SaveSetup(HI_U32 u32ModID);

/***********************************************************************************
* Function:     HI_LOG_RestoreSetup
* Description:  �ظ�һ��ģ��ͨ��HI_LOG_SaveSetup��������ò���
* Input:    u32ModID:ģ��ID��
* Output:
* Return:   HI_SUCCESS: success
*           HI_LOG_EINVAL:��������
*           HI_LOG_EINTER: �ڲ�����
*           HI_LOG_ENOTINIT:δ��ʼ��
***********************************************************************************/
HI_ERRNO HI_LOG_RestoreSetup(HI_U32 u32ModID);

/***********************************************************************************
* Function:     HI_LOG_LockOutput
* Description:  �������
* Input:    bLock:HI_TRUE:һ�������
                HI_FALSE:�Ƿ������HI_LOG_SetOutputSequence����
* Output:
* Return:   ���ɹ�����HI_TRUE
***********************************************************************************/
HI_BOOL HI_LOG_LockOutput(HI_BOOL bLock);

/***********************************************************************************
* Function:     HI_LOG_UnlockOutput
* Description:  �������
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
