/**
 \file
 \brief common info
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2008-2018
 \version draft
 \author s37678
 \date 2008-5-16
 */

#ifndef __HIGO_COMMOM_H__
#define __HIGO_COMMOM_H__

/* add include here */
#include "hi_go_comm.h"
#ifdef TEST_IN_ROOTBOX
#include "higo_memmng.h"
#include "adp_vmem.h"
#else
#include "higo_memory.h"
#endif
#include "higo_adp_sys.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RGB24
/***************************** Macro Definition ******************************/

#define IS_CLUT_FORMAT(p)          0// ((p) >= HIGO_PF_CLUT8 && (p) <=  HIGO_PF_CLUT4)
#define IS_ALPHA_FORMAT(p)         0// ((p) >= HIGO_PF_A1 && (p) <=  HIGO_PF_A8)
#define IS_YUV_FORMAT(p)            ((p) >= HIGO_PF_YUV400 && (p) <=  HIGO_PF_YUV444)
#define IS_RGB_FORMAT(p)            ((p) >= HIGO_PF_4444 && (p) <=  HIGO_PF_0888)


#define CHECK_NULLPTR(ptr) \
    if (HI_NULL == ptr) \
    { \
		return HIGO_ERR_NULLPTR; \
    }

#define IS_SRCRECT_IN_DSTRECT(pSrcRect, pDstRect) \
(   (pSrcRect->x >= pDstRect->x) && (pSrcRect->y >= pDstRect->y) \
&& ((pSrcRect->x + pSrcRect->w) <= (pDstRect->x + pDstRect->w))\
&&  ((pSrcRect->y + pSrcRect->h) <= (pDstRect->y + pDstRect->h)))

#define RGB32TO4444(c) \
    (((c & 0xf0000000) >> 16) | ((c & 0xf00000) >> 12) | ((c & 0xf000) >> 8) | ((c & 0xf0) >> 4))

#define RGB32TO1555(c) \
    (((c & 0x80000000) >> 16) | ((c & 0xf80000) >> 9) | ((c & 0xf800) >> 6) | ((c & 0xf8) >> 3))

#define RGB32TO565(c) \
    (((c & 0xf80000) >> 8) | ((c & 0xfc00) >> 5) | ((c & 0xf8) >> 3))

#define RGB32TO8565(c) \
    ((c & 0xff000000) >> 8 | ((c & 0xf80000) >> 8) | ((c & 0xfc00) >> 5) | ((c & 0xf8) >> 3))

#define RGB4444TO32(c) (((c & 0xf000) << 16) | \
                        ((c & 0x0f00) << 12) | \
                        ((c & 0x00f0) << 8) | \
                        ((c & 0x000f) << 4))

#define RGB0444TO32(c) (0xff000000 | ((c & 0x0f00) << 12) | \
                        ((c & 0x00f0) << 8) | \
                        ((c & 0x000f) << 4))

#define RGB565TO32(c) ((0xff000000 | (c & 0xf800) << 8) | \
                       ((c & 0x7e0) << 5) | \
                       ((c & 0x1f) << 3))
#define RGB8565TO32(c) (((c & 0x00ff0000)<<8) | ((c & 0xf800) << 8) | \
                       ((c & 0x7e0) << 5) | \
                       ((c & 0x1f) << 3))
                       
#define RGB555TO32(c) (0xff000000 | \
                       ((c & 0x7c00) << 9) | \
                       ((c & 0x3e0) << 6) | \
                       ((c & 0x1f) << 3))

#define RGB1555TO32(c) (((c & 0x8000) ? 0xff000000 : 0x0) | \
                        ((c & 0x7c00) << 9) | \
                        ((c & 0x3e0) << 6) | \
                        ((c & 0x1f) << 3))

/** use "HI_COLOR" get ARGB */
#define GetARGB(c, a, r, g, b) \
    do \
    {\
        (a) = ((c) >> 24) & 0xff; (r) = ((c) >> 16) & 0xff; (g) = ((c) >> 8) & 0xff; (b) = (c) & 0xff; \
    } while (0)

/** use "HI_COLOR" get ARGB */
#define GetRGB(c, r, g, b) \
    do \
    {\
        (r) = ((c) >> 16) & 0xff; (g) = ((c) >> 8) & 0xff; (b) = (c) & 0xff; \
    } while (0)
#ifdef TEST_IN_ROOTBOX
#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#else
#define HIGO_ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif
#define HIGO_MIN(x, y) (((x) > (y)) ? (y) : (x))
#define HIGO_MAX(x, y) (((x) > (y)) ? (x) : (y))

#define RECT2REGION(rect, region) do \
    {\
        (region).l = (rect).x; \
        (region).t = (rect).y; \
        (region).r = (((rect).x + (rect).w) - 1); \
        (region).b = (((rect).y + (rect).h) - 1); \
    } while (0)

#define REGION2RECT(rect, region) do \
    {\
        (rect).x = (region).l; \
        (rect).y = (region).t; \
        (rect).w = (((region).r - (region).l) + 1); \
        (rect).h = (((region).b - (region).t) + 1); \
    } while (0)
    
//#define _HIGO_DEBUG
#ifdef _HIGO_DEBUG
 #define HIGO_LOG_L(level, str, args...) HIGO_ADP_LOG(level, str, ## args)
 #define HIGO_LOG(str, args...) HIGO_ADP_LOG(HIGO_LOG_LEVEL_INFO, str, ## args)
 #define HIGO_SetError(errno) HIGO_ADP_SetError(errno)
 #define HIGO_ASSERT(cond) HIGO_ADP_ASSERT(cond)
 #define HIGO_ASSERT_EQUAL(actual, expect) HIGO_ASSERT((actual) == (expect))
 #define HIGO_ASSERT_NOTEQUAL(actual, expect) HIGO_ASSERT((actual) != (expect))
 #define HIGO_ERROR(Errno) printf("+++++ FILE: %s, LINE: %d, ret:%x\n", __FILE__, __LINE__, Errno);//HI_LogOut(HI_LOG_LEVEL_ERROR, , __FUNCTION__, __LINE__, HI_U8 *format, ...);
 #define HIGO_ERROR2(str...)        //HIGO_ADP_LOG(HIGO_LOG_LEVEL_NOTICE, " ERR: %x\n", (HI_U32)errno)
 #define HIGO_TRACE(str...)        //HIGO_ADP_LOG(HIGO_LOG_LEVEL_NOTICE, " ERR: %x\n", (HI_U32)errno)
#else
 #define HIGO_LOG(str, args...)
 #define HIGO_LOG_L(level, str, args...)
 #define HIGO_SetError(errno)
 #define HIGO_ASSERT(cond)
 #define HIGO_ASSERT_EQUAL(actual, expect) (HI_VOID)(actual)
 #define HIGO_ASSERT_NOTEQUAL(actual, expect) (HI_VOID)(actual)
 #define HIGO_ERROR(Errno) 
 #define HIGO_ERROR2(str...) 
 #define HIGO_TRACE(str...)        
#endif


#define ERR_CHKNEQ_RETURN(exp, value, label) \
    if ((exp) != (value)) return label

#define ERR_CHKEQ_RETURN(exp, value, label) \
    if ((exp) == (value)) return label

#define ERR_CHKNEQ_GOTO(exp, value, label) \
    if ((exp) != (value)) goto label

#define ERR_CHKEQ_GOTO(exp, value, label) \
    if ((exp) == (value)) goto label

#define UN_INIT_STATE 0 
#define CLEAR_INIT_STATE 1 
/*************************** Structure Definition ****************************/
typedef HI_U32 HIGO_HANDLE;
typedef HI_U32 DEC_HANDLE;
#ifndef TEST_IN_ROOTBOX
HI_S32  HIGO_GetRealRect(const HI_RECT* pSrcRect, const HI_RECT* pRect, HI_RECT* pRealRect);
#endif
/********************** Global Variable declaration **************************/

/******************************* API declaration *****************************/

#ifdef __cplusplus
}
#endif
#endif /* __HIGO_COMMOM_H__ */
