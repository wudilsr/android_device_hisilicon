
/**************************************************************************************************
Copyright (C), 1988-2009, Huawei Tech. Co., Ltd.

 File name       : HME_commontype.h
 Author: [SuiShankun 00133284]      Version: 1.00       Date:[2009-2-11 13:42:49]
 Description     : Huawei media engine common type definition, 
                   appoint extern interface and kinds of data type in engine system
 Others          :
 Function List   :
      1: ...
History         :
        Date            Author                  ver         Modification

**************************************************************************************************/

#ifndef _HME_COMMONTYPE_H_
#define  _HME_COMMONTYPE_H_

/**************************************************************************************************/
// platform ralative macro definition
#define OS_TYPE_LINUX         1
#define OS_TYPE_WINDOWS  2


// Common includes
#if(OS_TYPE_LINUX == OS_TYPE)
#include <linux/string.h> //linux
#include <linux/module.h>//linux
#include <linux/kernel.h>//linux
#include <linux/init.h>//linux
#include <linux/version.h>//linux
#else
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#endif

//#include <math.h>
//#include <linux/stdarg.h> //be included in vsprintf.c
//#include <stdarg.h> //be included in vsprintf.c
/**************************************************************************************************/

// OS detection

//#if defined (WIN32) || defined (_WIN32) || defined (__WIN32__) || defined (__NT__)
// #define HME_OS_WIN32
//#else
// #error "Unknown OS"
//#endif // OS detection

/**************************************************************************************************/

// Compiler detection

/**************************************************************************************************/

// Architecture detection

/**************************************************************************************************/





// Export/Import definitions
#if(OS_TYPE_LINUX == OS_TYPE)
#define HME_EXPORT_SYMBOL
#define HME_IMPORT_SYMBOL
#define HME_FASTCALL
#define HME_CDECL
#define HME_STDCALL
#define HME_METHOD_CALL_TYPE
#else
#define HME_EXPORT_SYMBOL
#define HME_IMPORT_SYMBOL
#define HME_CDECL                  __cdecl
#define HME_STDCALL                __stdcall
#define HME_METHOD_CALL_TYPE       __cdecl
#endif//(OS_TYPE_LINUX == OS_TYPE)

//add by tianweifeng 2010.3.22: add HME_STATIC definition
//define HME_STATIC
#if defined (_HME_UT)
 #define HME_STATIC
#else
 #define HME_STATIC static
#endif

#define HME_PROC_FREQ 24000

/**************************************************************************************************/

// define HME_CPLUSPLUS

#ifndef EXTERN_C
 #ifdef __cplusplus
  #define EXTERN_C                  extern "C"
 #else
  #define EXTERN_C                  extern
 #endif // __cplusplus
#endif // EXTERN_C

#ifdef __cplusplus
 #define HME_CPLUSPLUS
 #define HME_EXTERN_C               extern "C"
 #define HME_EXTERN_C_BEGIN         extern "C" {
 #define HME_EXTERN_C_END           }
#else
 #define HME_EXTERN_C               extern
 #define HME_EXTERN_C_BEGIN
 #define HME_EXTERN_C_END
#endif // __cplusplus

#ifdef __cplusplus
 #define HME_INLINE                 inline
 #define HME_STATIC_INLINE          static inline
#endif // __cplusplus

/**************************************************************************************************/

#define HME_PACK_BEGIN(v)           //pack(v)
#define HME_PACK_END()              //pack()

/**************************************************************************************************/

// Common types

//#if defined (_MSC_VER)
//#include <stddef.h>

typedef signed char                 int8;
typedef signed short                int16;
typedef int                         int32;
typedef unsigned char               uint8;
typedef unsigned short              uint16;
typedef unsigned int                uint32;
typedef signed long long            int64;
//typedef unsigned long long          uint64;
//typedef float                       float32;
//typedef double                      float64;

typedef size_t                      usizet;
typedef int64                       fpost; 


 //#define HME_ALIGN(arg, val)        __declspec(align(val)) arg

 #define INT8_MIN                   (-128)
 #define INT8_MAX                   127
 #define UINT8_MAX                  255
 #define INT16_MIN                  (-32768)
 #define INT16_MAX                  32767
 #define UINT16_MAX                 65535
 #define INT32_MIN                  (int32)(-2147483647 - 1)
 #define INT32_MAX                  2147483647
 #define UINT32_MAX                 4294967295U

 #define INT32_C(v)                 (v)
 #define UINT32_C(v)                (v)
 //#define INT64_C(v)                 (v ## i64)
 //#define UINT64_C(v)                (v ## ui64)
 //#define INTMAX_C(v)                INT64_C(v)
// #define UINTMAX_C(v)               UINT64_C(v)

 #define FMT64                      "I64"


typedef unsigned char   tPureBool;          // MSVC 6 using 1 byte to represent bool

 #ifdef __cplusplus
typedef   bool tBool;
 #else
typedef   tPureBool tBool;
  #define false                     0
  #define true                      1
 #endif // __cplusplus

 #ifndef OUT
  #define                           OUT
 #endif

//#endif  // defined(_MSC_VER)

#ifndef NULL
 #define NULL                       0
#endif

typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef void *HANDLE;




#endif  // _HME_COMMONTYPE_H_

/**************************************************************************************************
    End of File
**************************************************************************************************/
