#ifndef TELETEXT_UTILS_H__
#define TELETEXT_UTILS_H__

#include "teletext_def.h"

#ifdef __cplusplus
extern "C" {
#endif

HI_S32 TTX_PesQueue_Init(TTX_SEGMENT_QUEUE_S* pstQueue, const HI_U8* pszBufAddr, HI_U32 u32BufLen);

HI_S32 TTX_PesQueue_En(TTX_SEGMENT_QUEUE_S* pstQueue, TTX_SEGMENT_S* pSegment);

HI_S32 TTX_PesQueue_De(TTX_SEGMENT_QUEUE_S* pstQueue, TTX_SEGMENT_S* pSegment);

HI_S32 TTX_PesQueue_Reset(TTX_SEGMENT_QUEUE_S* pstQueue, const HI_U8* pszBufAddr, HI_U32 u32BufLen);

HI_S32 TTX_PesQueue_IsMemTensity(TTX_SEGMENT_QUEUE_S* pstQueue);

#ifdef __cplusplus
}
#endif

#endif
