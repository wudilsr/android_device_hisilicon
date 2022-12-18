#ifndef _HI_ADP_H_
#define _HI_ADP_H_

#include "hi_type.h"

#define HIAPI_RUN(api, ret) \
    do {\
        HI_S32 errCode; \
        errCode = api; \
        if (errCode != 0)\
        {\
            ret |= errCode; \
            PRINT_SMP("\033[0;31m" "[Function: %s line: %d] %s failed ret = 0x%x \n" "\033[0m", __FUNCTION__, __LINE__ , # api, errCode); \
        } \
    } while (0)

#define HIAPI_RUN_RETURN(api) \
    do {\
        HI_S32 errCode; \
        errCode = api; \
        if (errCode != 0)\
        {\
            PRINT_SMP("\033[0;31m" "[Function: %s line: %d] %s failed ret = 0x%x \n" "\033[0m",  __FUNCTION__, __LINE__ , #api, errCode); \
            return HI_FAILURE; \
        } \
    } while (0)

#define HIAPI_RUN_RETURN_FN(api, fn) \
    do {\
        HI_S32 errCode; \
        errCode = api; \
        if (errCode != 0)\
        {\
            PRINT_SMP("\033[0;31m" "[Function: %s line: %d] %s failed ret = 0x%x \n" "\033[0m",  __FUNCTION__, __LINE__ , #api, errCode); \
            fn; \
            return HI_FAILURE; \
        } \
    } while (0)

#define HIAPI_ERR_PRINTF(ret) \
    do {\
        printf("\033[0;31m" " [Function: %s line: %d]  ret = 0x%x \n" "\033[0m", __FUNCTION__, __LINE__ , ret); \
    }while(0)\


#define PRINT_SMP(fmt...)   printf(fmt)

#define SAMPLE_RUN(api, ret) \
    do{ \
        HI_S32 l_ret = api; \
        if (l_ret != HI_SUCCESS) \
        { \
            PRINT_SMP("run %s failed, ERRNO:%#x.\n", #api, l_ret); \
        } \
        else\
        {\
        /*printf("sample %s: run %s ok.\n", __FUNCTION__, #api);}*/   \
        }\
        ret = l_ret;\
    }while(0)


#define SAMPLE_CheckNullPTR(pointer)                    \
    do                                                  \
    {                                                   \
        if (NULL == pointer)                            \
        {                                               \
            PRINT_SMP("%s failed:NULL Pointer in Line:%d!\n", __FUNCTION__, __LINE__);\
            return HI_FAILURE; \
        }                      \
    }while(0)


#endif
