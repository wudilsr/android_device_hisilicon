/******************************************************************************
Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
******************************************************************************
File Name     : hi_svr_debug.h
Version       : Initial Draft
Author        : Hisilicon multimedia software group
Created       : 2005/4/23
Last Modified :
Description   : Common debugging macro definition
Function List :
History       :
******************************************************************************/
#ifndef __HI_SVR_DEBUG_H__
#define __HI_SVR_DEBUG_H__


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "hi_debug.h"
#include "hi_common.h"
#include "hi_unf_version.h"
#include "hi_log.h"
#include "logformat.h"

#if defined(HI_LOG_SUPPORT) && (0 == HI_LOG_SUPPORT)
#undef SVR_DEBUG
#else
#define SVR_DEBUG
#endif


#ifdef __OS_LINUX__
#include <stdio.h>
#define SVR_PRINT SVR_LOG_INFO
#define SVR_PANIC SVR_LOG_ERROR
#endif /* end of __OS_LINUX__ */

/*************************** Structure Definition ****************************/

/**Just only for fatal level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define SVR_TRACE_LEVEL_FATAL    (0)
/**Just only for error level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define SVR_TRACE_LEVEL_ERROR    (1)
/**Just only for warning level print. */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define SVR_TRACE_LEVEL_WARN     (2)
/**Just only for info level print.    */   /**CNcomment: Ϊ�˴�ӡ��Ϣ������ƶ��ĺ��ӡ���� */
#define SVR_TRACE_LEVEL_INFO     (3)
/**Just only for debug level print.   */   /**CNcomment: Ϊ�˴�ӡ������Ϣ���ƶ��ĺ��ӡ���� */
#define SVR_TRACE_LEVEL_DBG      (4)

#ifndef SVR_LOG_LEVEL
#define SVR_LOG_LEVEL        (SVR_TRACE_LEVEL_DBG)
#endif

#ifdef SVR_DEBUG
#define SVR_TRACE(level, module_id, fmt...) \
do{ \
SVR_LogOut(level, (HI_MOD_ID_E)module_id, (HI_U8*)__FUNCTION__,__LINE__,fmt);\
}while(0)

#define HILOG_FIT_SVRLOG(level,enoErrno,fmt...)\
do{ \
SVR_HiLogOut(__THIS_LOG_MOD_ID,(HI_MOD_ID_E)MODULE_ID,level,enoErrno,__FILE__,__FUNCTION__,__LINE__,fmt);\
 }while(0)


#define SVR_ASSERT(expr)                                     \
    do{                                                     \
        if (!(expr)) {                                      \
            SVR_PANIC("\nASSERT failed at:\n  >File name: %s\n  >Function : %s\n  >Line No. : %d\n  >Condition: %s\n", \
                __FILE__,__FUNCTION__, __LINE__, #expr);    \
        }                                                   \
    }while(0)


#define SVR_ASSERT_RET(expr)                                     \
    do{                                                         \
        if (!(expr)) {                                          \
            SVR_PRINT("\n<%s %d>: ASSERT Failure{" #expr "}\n",  \
                          __FUNCTION__, __LINE__);              \
            return HI_FAILURE;                                  \
        }                                                       \
    }while(0)

#define SVR_SET_LOGLEVEL_BYID(ID, LEVEL) \
do{ \
SVR_Set_LogLevel_ById(ID, LEVEL);\
}while(0)


#define SVR_SET_LOGLEVEL_BYNAME(NAME, LEVEL) \
do{ \
SVR_Set_LogLevel_ByName(NAME, LEVEL);\
}while(0)


/**Supported for debug output to serial/network/u-disk. */
/**CNcomment: ����ģ����Ҫ�������º�������������Ϣ������������ڡ����ڡ�U�̴洢�� */
#if defined(ANDROID) && (UNF_VERSION_CODE == UNF_VERSION(3, 0))
#include <utils/Log.h>
#define SVR_TRACE_INFO( module_id, fmt...)  LOGV(fmt)
#define SVR_TRACE_DEBUG(  module_id, fmt...)  LOGD(fmt)
#define SVR_TRACE_WARN( module_id, fmt...)  LOGI(fmt)
#define SVR_TRACE_ERROR(  module_id, fmt...)  LOGE(fmt)
#define SVR_TRACE_FATAL(module_id, fmt...)  LOGE(fmt)
//#endif
#else

/**Just only reserve the fatal level output. */
/**CNcomment: �������������ĵ�����Ϣ */
#if (SVR_LOG_LEVEL == SVR_TRACE_LEVEL_FATAL)
#define SVR_TRACE_FATAL(module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_FATAL,    module_id, fmt)
#define SVR_TRACE_ERROR(  module_id, fmt...)
#define SVR_TRACE_WARN( module_id, fmt...)
#define SVR_TRACE_INFO( module_id, fmt...)
#define SVR_TRACE_DEBUG(  module_id, fmt...)
/**Just only reserve the fatal/error level output. */
/**CNcomment: �������������ĺʹ��󼶱�ĵ�����Ϣ */
#elif (SVR_LOG_LEVEL == SVR_TRACE_LEVEL_ERROR)
#define SVR_TRACE_FATAL(module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_FATAL,    module_id, fmt)
#define SVR_TRACE_ERROR(  module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_ERROR,    module_id, fmt)
#define SVR_TRACE_WARN( module_id, fmt...)
#define SVR_TRACE_INFO( module_id, fmt...)
#define SVR_TRACE_DEBUG(  module_id, fmt...)
/**Just only reserve the fatal/error/warning level output. */
/**CNcomment: �������������ġ�����ġ����漶��ĵ�����Ϣ */
#elif (SVR_LOG_LEVEL == SVR_TRACE_LEVEL_WARN)
#define SVR_TRACE_FATAL(module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_FATAL,    module_id, fmt)
#define SVR_TRACE_ERROR(  module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_ERROR,    module_id, fmt)
#define SVR_TRACE_WARN( module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_WARN,     module_id, fmt)
#define SVR_TRACE_INFO( module_id, fmt...)
#define SVR_TRACE_DEBUG(  module_id, fmt...)
/**Just only reserve the fatal/error/warning/info level output. */
/**CNcomment: �������������ġ�����ġ��������Ϣ����ĵ�����Ϣ */
#elif (SVR_LOG_LEVEL == SVR_TRACE_LEVEL_INFO)
#define SVR_TRACE_FATAL(module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_FATAL,    module_id, fmt)
#define SVR_TRACE_ERROR(  module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_ERROR,    module_id, fmt)
#define SVR_TRACE_WARN( module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_WARN,     module_id, fmt)
#define SVR_TRACE_INFO( module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_INFO,     module_id, fmt)
#define SVR_TRACE_DEBUG(  module_id, fmt...)
#else
/**Reserve all the levels output. */
/**CNcomment: �������м��������Ϣ */
#define SVR_TRACE_FATAL(module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_FATAL,    module_id, fmt)
#define SVR_TRACE_ERROR(  module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_ERROR,    module_id, fmt)
#define SVR_TRACE_WARN( module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_WARN,     module_id, fmt)
#define SVR_TRACE_INFO( module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_INFO,     module_id, fmt)
#define SVR_TRACE_DEBUG(  module_id, fmt...)   SVR_TRACE(SVR_TRACE_LEVEL_DBG,      module_id, fmt)
#endif

#endif

#else
#define SVR_TRACE_FATAL(module_id, fmt...)
#define SVR_TRACE_ERROR(  module_id, fmt...)
#define SVR_TRACE_WARN( module_id, fmt...)
#define SVR_TRACE_INFO( module_id, fmt...)
#define SVR_TRACE_DEBUG(  module_id, fmt...)
#define SVR_TRACE(level, module_id, fmt...)
#define SVR_ASSERT(expr)
#define SVR_ASSERT_RET(expr)
#define HILOG_FIT_SVRLOG(level ,enoErrno,fmt...)
#define SVR_SET_LOGLEVEL_BYNAME(NAME, LEVEL)
#define SVR_SET_LOGLEVEL_BYID(ID, LEVEL)
#endif /* endif HI_DEBUG */

#define MKSTR(exp) # exp
#define MKMARCOTOSTR(exp) MKSTR(exp)
#define VERSION_STRING ("SDK_VERSION:["MKMARCOTOSTR(SDK_VERSION)"] Build Time:["__DATE__", "__TIME__"]")


/**Initialize a user module.*/
/**CNcomment: �û�ģ���ʼ�� */

#define SVR_MODULE_DECLARE(MODULE_NAME)\
    static HI_U32 g_u32ModuleId = 0xffffffff;\
    static HI_S32 __attribute__((constructor(200))) init_module_id() \
    {\
       return Module_Init(&g_u32ModuleId,MODULE_NAME); \
    } \
    static HI_S32 __attribute__((destructor(200))) deinit_module_id() \
    { \
         return Module_Uninit(g_u32ModuleId); \
    }


/**Defines a user module ID.*/
/**CNcomment: �û�ģ��ID�궨�� */
#define MODULE_ID (g_u32ModuleId)

/**Defines the command of the user module different level log print.*/
/**CNcomment: �û�ģ����־����궨�� */
#define SVR_LOG_FATAL(pszFormat...)  SVR_TRACE_FATAL(MODULE_ID,pszFormat)
#define SVR_LOG_ERROR(pszFormat...)  SVR_TRACE_ERROR(MODULE_ID,pszFormat)
#define SVR_LOG_WARN(pszFormat...)   SVR_TRACE_WARN(MODULE_ID,pszFormat)
#define SVR_LOG_INFO(pszFormat...)    SVR_TRACE_INFO(MODULE_ID,pszFormat)
#define SVR_LOG_DEBUG(pszFormat...)  SVR_TRACE_DEBUG(MODULE_ID,pszFormat)



/**Defines the memory allocate and free command used by user module.*/
/**CNcomment: �û�ģ���ڴ����궨�� */
#define SVR_MALLOC(u32Size)               HI_MEM_Malloc(MODULE_ID, u32Size)
#define SVR_FREE(pMemAddr)                HI_MEM_Free(MODULE_ID, pMemAddr)
#define SVR_CALLOC(u32MemBlock, u32Size)  HI_MEM_Calloc(MODULE_ID, u32MemBlock, u32Size)
#define SVR_REALLOC(pMemAddr, u32Size)    HI_MEM_Realloc(MODULE_ID, pMemAddr, u32Size)



/*-----------------------------------------------------------------
�����ж�
-----------------------------------------------------------------*/
//�����������
#define SVR_LOG_CHK_PARA( val  )           \
        do                                                      \
        {                                                       \
            if ((val))                                          \
            {                                                   \
                SVR_LOG_ERROR("Invalid Parameter"); \
                return HI_FAILURE;                                    \
            };                                                   \
        } while (0)

/*-----------------------------------------------------------------*/
// �������ֵ��������ԣ����ظ�ָ�������� , valҪд����������ж�
#define SVR_LOG_CHK_RETURN_ERR(val, ret )                            \
            do                                                      \
            {                                                       \
                if ((val))                                          \
                {                                                   \
                    SVR_LOG_ERROR("");                       \
                    return ret;                                    \
                }                                                   \
            } while (0)

/*-----------------------------------------------------------------*/
// �������ֵ��������ԣ���ӡ������Ϣ, valҪд����������ж�
#define SVR_LOG_CHK_PRINT_ERR(val, ret)                  \
do                                                      \
{                                                       \
    if ((val))                                          \
    {                                                   \
        SVR_LOG_ERROR("");                    \
    }                                                   \
} while (0)

/*-----------------------------------------------------------------*/

/* ���funcִ��ʧ�ܣ�ֻ��ӡ������Ϣ�������� */
#define SVR_LOG_DOFUNC( func )                            \
            do{                                         \
                HI_S32 s32Ret = 0 ;                        \
                s32Ret = func ;                            \
                if(s32Ret != HI_SUCCESS)                   \
                {                                        \
                    SVR_LOG_ERROR("%s fail:%d" , #func, s32Ret);           \
                };                                       \
            }while(0)

/*-----------------------------------------------------------------*/
 /* ���funcִ��ʧ�ܣ���ֱ�ӷ��ر��������ķ���ֵ */
#define SVR_LOG_DOFUNC_RETURN( func )                            \
                    do{                                         \
                        HI_S32 s32Ret = 0 ;                        \
                        s32Ret = func ;                            \
                        if(s32Ret != HI_SUCCESS)                   \
                        {                                        \
                            SVR_LOG_ERROR("%s fail:%d" , #func, s32Ret);          \
                            return s32Ret;                        \
                        };                                       \
                    }while(0)


/*-----------------------------------------------------------------*/
/* ���funcִ��ʧ�ܣ��򷵻�ָ���Ĵ����� */
#define SVR_LOG_DOFUNC_RETURN_ERR( func ,err)                            \
                    do{                                         \
                        HI_S32 s32Ret = 0 ;                        \
                        s32Ret = func ;                            \
                        if(s32Ret != HI_SUCCESS)                   \
                        {                                        \
                            SVR_LOG_ERROR("%s fail:%d" , #func, s32Ret);          \
                            return err;                        \
                        };                                       \
                    }while(0)
/*-----------------------------------------------------------------*/
/* ���funcִ��ʧ�ܣ��򷵻�void */
#define SVR_LOG_DOFUNC_RETURN_VOID(func)                 \
                do{\
                    HI_S32 s32Ret = func;                  \
                    if(s32Ret != HI_SUCCESS)               \
                    { \
                        SVR_LOG_ERROR("%s fail:%d" , #func, s32Ret);    \
                        return ;                        \
                    }                                   \
                }while(0)
/*-----------------------------------------------------------------*/

#define SVR_LOG_DOFUNC_GOTO(func, errhandle) \
    do{\
        HI_S32 s32Ret = func;\
        if (s32Ret != HI_SUCCESS )\
        {\
            SVR_LOG_ERROR("%s fail:%d\n", #func, s32Ret);\
            goto errhandle;\
        }\
    }while(0)


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __HI_DEBUG_H__ */
