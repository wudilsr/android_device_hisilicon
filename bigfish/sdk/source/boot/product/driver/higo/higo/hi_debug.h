/***********************************************************************************
 *             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: hi_debug.h
 * Description: debugÍ·ÎÄ¼þ
 *
 * History:
 * Version   Date             Author     DefectNum    Description
 * main\1    2008-03-27       d37024                  Create this file.
 ***********************************************************************************/

#ifndef  _JPG_DEBUG_H_
#define  _JPG_DEBUG_H_

#include "hi_type.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#if 0
typedef enum hiLOG_ERRLEVEL_E
{
    HI_LOG_LEVEL_DEBUG   = 0,               /* debug-level                                  */
    HI_LOG_LEVEL_INFO ,                     /* informational                                */
    HI_LOG_LEVEL_NOTICE,                    /* normal but significant condition             */
    HI_LOG_LEVEL_WARNING,                   /* warning conditions                           */
    HI_LOG_LEVEL_ERROR,                     /* error conditions                             */
    HI_LOG_LEVEL_CRIT,                      /* critical conditions                          */
    HI_LOG_LEVEL_ALERT,                     /* action must be taken immediately             */
    HI_LOG_LEVEL_FATAL,                     /* just for compatibility with previous version */
    HI_LOG_LEVEL_BUTT
} LOG_ERRLEVEL_E;
#endif

#define JPEG 0x6

#ifdef HIGO_DEBUG
#define HI_TRACE( level, module, fmt, args... ) \
do { \
		 printf( "%s Line %d Function %s(): ", __FILE__,  __LINE__, __FUNCTION__);\
		 printf(fmt, ##args); \
} while (0)
#else
#define HI_TRACE
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /* _JPG_DEBUG_H_*/



