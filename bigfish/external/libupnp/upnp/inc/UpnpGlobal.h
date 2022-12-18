#ifndef UPNPGLOBAL_H
#define UPNPGLOBAL_H

/*lint -save -e* */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
/*lint -restore * */


#ifdef DLNA_SFT

void *SFT_malloc(size_t size);
void *SFT_realloc(void *ptr, size_t size);
void   SFT_free(void *ptr);
char * SFT_strdup(const char *s);


typedef void *  (*PTUpnpOsMalloc)
(
    size_t MsgSize
);

typedef void *  (*PTUpnpOsReAlloc)
(
    void *ptr,
    size_t MsgSize
);

typedef void  (*PTUpnpOsFree)
(
    void  *pMsg
);

typedef char *  (*PTUpnpOsStrdup)
(
        const char *s
);



/* structure for msg callback functions*/
typedef struct _UPNP_MSG_CALLBACK_FUNC_STRUCT
{
    /* Allocate Message */
    PTUpnpOsMalloc pfMallocMsg;

    /* free Message */
    PTUpnpOsFree pfFreeMsg;

    /* Send Message */
    PTUpnpOsReAlloc pfReAllocMsg;

    PTUpnpOsStrdup pfStrdup;

}UPNP_MSG_CALLBACK_FUNC_ST;


extern UPNP_MSG_CALLBACK_FUNC_ST    gUpnpMemCallBackFunc;


#define UPNP_MALLOC      (*(gUpnpMemCallBackFunc.pfMallocMsg))
#define UPNP_REALLOC     (*(gUpnpMemCallBackFunc.pfReAllocMsg))
#define UPNP_STRDUP      (*(gUpnpMemCallBackFunc.pfStrdup))
#define UPNP_FREE(ptr) \
{ \
    (*(gUpnpMemCallBackFunc.pfFreeMsg))(ptr); \
    (ptr) = NULL; \
} \


#else
#define UPNP_MALLOC     malloc
#define UPNP_REALLOC    realloc
#define UPNP_STRDUP     strdup

/*[r72104][Internal Review Comments Fix] As free of NULL doesn't have
    any efect so we will remove the NULL check */
#define UPNP_FREE(ptr)       \
{ \
    free((void *)ptr);\
    (ptr) = NULL; \
}


#endif


/*[r72104][Internal Review Comments Fix] End */
#define UPNP_ALLOCA     alloca

/*!
 * \file
 *
 * \brief Defines constants that for some reason are not defined on some systems.
 */

#if defined MYLIB_LARGEFILE_SENSITIVE && _FILE_OFFSET_BITS+0 != 64
    #if defined __GNUC__
        #warning libupnp requires largefile mode - use AC_SYS_LARGEFILE
    #else
        #error  libupnp requires largefile mode - use AC_SYS_LARGEFILE
    #endif
#endif

#ifdef WIN32
    /*
     * EXPORT_SPEC
     */
    #ifdef UPNP_STATIC_LIB
        #define EXPORT_SPEC
    #else /* UPNP_STATIC_LIB */
        #ifdef LIBUPNP_EXPORTS
            /*! set up declspec for dll export to make functions
             * visible to library users */
            #define EXPORT_SPEC __declspec(dllexport)
        #else /* LIBUPNP_EXPORTS */
            #define EXPORT_SPEC __declspec(dllimport)
        #endif /* LIBUPNP_EXPORTS */
    #endif /* UPNP_STATIC_LIB */

    /*
     * UPNP_INLINE
     * PRId64
     * PRIzu
     */
    #ifdef UPNP_USE_MSVCPP
        /* define some things the M$ VC++ doesn't know */
        #define UPNP_INLINE
        typedef __int64 int64_t;
        #define PRId64 "I64d"
        #define PRIzu "lu"
    #endif /* UPNP_USE_MSVCPP */

    #ifdef UPNP_USE_BCBPP
        /* define some things Borland Builder doesn't know */
        #define UPNP_INLINE inline
        typedef __int64 int64_t;
        #warning The Borland C compiler is probably broken on PRId64,
        #warning please someone provide a proper fix here
        #define PRId64 "I64d"
        #define PRIzu "zu"
    #endif /* UPNP_USE_BCBPP */

    #ifdef __GNUC__
        #define UPNP_INLINE inline
        /* Note with PRIzu that in the case of Mingw32, it's the MS C
         * runtime printf which ends up getting called, not the glibc
         * printf, so it genuinely doesn't have "zu"
         */
        #define PRIzu "lu"
    #endif /* __GNUC__ */
#else
    /*!
     * \brief Export functions on WIN32 DLLs.
     *
     * Every funtion that belongs to the library API must use this
     * definition upon declaration or it will not be exported on WIN32
     * DLLs.
     */
    #define EXPORT_SPEC

    /*!
     * \brief Declares an inline function.
     *
     * Surprisingly, there are some compilers that do not understand the
     * inline keyword. This definition makes the use of this keyword
     * portable to these systems.
     */
    #ifdef __STRICT_ANSI__
        #define UPNP_INLINE __inline__
    #else
        #define UPNP_INLINE inline
    #endif

    /*!
     * \brief Supply the PRId64 printf() macro.
     *
     * MSVC still does not know about this.
     */
    /* #define PRId64 PRId64 */

    /*!
     * \brief Supply the PRIzu printf() macro.
     *
     * This macro was invented so that we can live a little longer with
     * MSVC lack of C99. "z" is the correct printf() size specifier for
     * the size_t type.
     */
    #define PRIzu "zu"
#endif

/*
 * Defining this macro here gives some interesting information about unused
 * functions in the code. Of course, this should never go uncommented on a
 * release.
 */
/*#define inline*/


#ifdef DLNA_LINT
/*Following Assert definition is only for Lint Purpose - since Lint is not recognizing System Asset Defined in Assert.h
  If DLNA_LINT not defined (which is defined only in lint option file) system asset always will be used.*/


/*Define some string functions*/
extern char* strdup(const char *s);
extern size_t strlen(const char *s);
extern char* strtok_r(char *str, const char *delim, char **saveptr);
extern int snprintf(char *str, size_t size, const char *format,...);
extern int sprintf(char *str, const char *format,...);
extern void *alloca (size_t __size);


#define assert(_condition) \
{ \
    if (!(_condition)) \
    { \
        exit(0);\
    } \
}

#endif


#endif /* UPNPGLOBAL_H */
