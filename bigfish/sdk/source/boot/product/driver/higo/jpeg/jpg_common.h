/***********************************************************************************
 *             Copyright 2006 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: jpg_common.h
 * Description: 
 *
 * History:
 * Version   Date             Author     DefectNum    Description
 * main\1    2008-03-27       d37024                  Create this file.
 ***********************************************************************************/

#ifndef  _JPG_COMMON_H_
#define  _JPG_COMMON_H_

#include "higo_common.h"
#include "hi_api_mmz.h"

#ifndef  JPG_OS_BOOT
#define JPG_OS_BOOT
#endif

#ifndef JPG_OS_BOOT
#include <time.h>
#ifndef  WIN32
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <semaphore.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <pthread.h>
//#include <assert.h>
#else
#include "ut.h"
#endif
#endif

#include "hi_type.h"
#include "hi_jpg_errcode.h"
#include "hi_jpg_type.h"

#define X5_JPEG
//#define POS()   {printf("function %s  line %d\n", __FUNCTION__, __LINE__);}
#ifdef  X5_JPEG
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#ifndef JPG_OS_BOOT
typedef sem_t VCOS_sem_t;
typedef struct timeval VCOS_timeval_s;
typedef struct timezone VCOS_timezone_s;
typedef FILE VCOS_FILE;
#else
typedef int VCOS_sem_t;
#endif


#define VCOS_sem_init //sem_init
#define VCOS_sem_destroy //sem_destroy
#define VCOS_sem_post //sem_post
#define VCOS_sem_wait //sem_wait
#define VCOS_printf printf
#define VCOS_memset memset
#define VCOS_malloc malloc
#define VCOS_free free
//#define VCOS_gettimeofday gettimeofday
//#define VCOS_fopen fopen
//#define VCOS_fclose fclose
//#define VCOS_fseek fseek
//#define VCOS_ftell ftell
//#define VCOS_SEEK_END SEEK_END
//#define VCOS_SEEK_CUR SEEK_CUR
//#define VCOS_SEEK_SET SEEK_SET
//#define VCOS_fread fread
//#define VCOS_fwrite fwrite
//#define VCOS_ferror ferror
//#define VCOS_feof feof
#define VCOS_memcpy memcpy

#if 0
#define VCOS_access access
#define VCOS_open open
#define VCOS_close close
#define VCOS_ioctl ioctl
#define VCOS_mmap mmap
#define VCOS_pthread_t pthread_t
#define VCOS_pthread_create pthread_create
#define VCOS_pthread_join pthread_join
#define VCOS_usleep usleep
#endif

#define DEFAULT_HANDLE 0x7FFFFFF1  
#define INVALID_HANDLE 0x0         

#if defined(CHIP_TYPE_hi3796cv100_a) || defined(CHIP_TYPE_hi3796cv100) || defined(CHIP_TYPE_hi3798cv100_a) || defined(CHIP_TYPE_hi3798cv100)
/* accelerator register address */
#define JPEG_HW_ADDRESS 0xFF300000
#else
#define JPEG_HW_ADDRESS 0xf8c40000
#endif

//#define assert(x)  //{if(!(x)) VCOS_printf("assert failed @line %d @%s\n",__LINE__,__FILE__); }

#define STATIC_FUNC   static

#define NULLPTR_CHECK(Ptr) \
do{\
    if(HI_NULL == Ptr)\
    {\
        return HI_ERR_JPG_PTR_NULL;\
    }\
}while(0)

#if 1
#define JPG_CHECK_HANDLE(x)         \
do                                              \
{                                               \
    if (NULL == (x))    \
    {                                                       \
        return  HI_ERR_JPG_INVALID_HANDLE;\
    }                                           \
}while(0)

#define JPG_CHECK_NULLPTR(p)            \
do                                                  \
{                                               \
    if (NULL == (p))                \
    {                                               \
        return HI_ERR_JPG_PTR_NULL; \
    }                                           \
}while(0);

#define JPG_CHECK_ENUM(Par, Butt)           \
do                                                  \
{                                               \
    if ((Butt) <= (Par))                   \
    {                                               \
        return HI_ERR_JPG_INVALID_PARA;          \
    }                                           \
}while(0);

#define JPG_CHECK_LEN(Len)          \
do                                                  \
{                                               \
    if (0 == (Len))                    \
    {                                               \
        return HI_ERR_JPG_INVALID_PARA;          \
    }                                           \
}while(0);


#define JPG_ASSERT_HANDLE(x)            \
do                                                  \
{                                                 \
    assert(NULL != (x));                         \
}while(0)

#define JPG_ASSERT_NULLPTR(x)            \
do                                                  \
{                                                 \
    assert(NULL != (x));                         \
}while(0)
#endif

/*FMW ÄÚ´æ¹ÜÀí*/
typedef struct hiJPG_MEM_S
{
    HI_VOID* 	pVirtAddr;
    HI_U32 	PhysAddr;
    HI_U32     	Total;
    HI_U32 	Offset;
} JPG_MEM_S;

typedef struct hiJPGDEC_CTRL_S
{
 	JPG_MEM_S s_DecMem;
	JPG_MEM_S s_ParseMem;
	JPG_MEM_S s_HDecMem;
	JPG_MEM_S s_SDecMem;
	JPG_MEM_S s_ExifMem;
	JPG_MEM_S s_Jpg6bMem;
}JPGDEC_CTRL_S;

#ifdef X5_JPEG
#define MMB_TAG  "others"
#else
#define MMB_TAG  "jpeg"
#endif

#if 1
HI_VOID*  JPGFMW_Alloc(JPG_MEM_S* pstMem, HI_U32 Size);
HI_VOID JPGFMW_Free(JPG_MEM_S* pstMem);
HI_VOID JPGFMW_MemReset(JPG_MEM_S* pstMem, HI_U32  RsvSize);
HI_VOID* JPGFMW_MemGet(JPG_MEM_S* pstMem, HI_U32  Size);

extern JPGDEC_CTRL_S s_DecCtrlMem;
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif  /* __cplusplus */
#endif  /* __cplusplus */

#endif /* _JPG_COMMON_H_*/



