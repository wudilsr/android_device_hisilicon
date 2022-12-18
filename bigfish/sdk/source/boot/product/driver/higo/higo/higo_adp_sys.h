/**
 \file
 \brief POSIX adaptive layer
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author s37678
 \date 2008-5-19
 */

#ifndef __HIGO_POSIX_H__
#define __HIGO_POSIX_H__

/* add include here */
#include "exports.h"


#ifdef __cplusplus
extern "C" {
#endif

/***************************** Macro Definition ******************************/

#define HIGO_MemSet memset
#define HIGO_MemCopy memcpy
#define HIGO_MemCmp memcmp
#define HIGO_Strncmp strncmp
#if 0
 #define HIGO_Printf(format, arg...)   printf(## arg)
#else
#define HIGO_Printf(format, arg...)  
#endif

//#define HIGO_ADP_ASSERT(cond) if (!(cond)) { printf("assert failed\n");}
#define HIGO_ADP_ASSERT(cond) 

#define HIGO_ADP_LOG(level, str, args...)

//#define HIGO_ADP_SetError(errno) printf( " ERR: %x\n", (HI_U32)errno)
#define HIGO_ADP_SetError(errno) 

#if 0
#define BM_TRACE(fmt, args... )\
 do { \
            printf("%s(): Line %d : "fmt, __FUNCTION__,  __LINE__ , ##args);\
    } while (0)
#else
#define BM_TRACE(fmt, args... )
#endif
/*************************** Structure Definition ****************************/


/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/


#ifdef __cplusplus
}
#endif
#endif /* __HIGO_POSIX_H__ */
