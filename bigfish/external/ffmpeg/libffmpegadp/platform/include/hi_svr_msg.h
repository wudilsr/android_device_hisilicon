#ifndef __HI_SVR_MSG_H__
#define __HI_SVR_MSG_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

HI_S32 FFMPEG_MSG_Init(HI_HANDLE *pstHdl, HI_VOID *pArgs, HI_S32 s32MsgSize);

HI_S32 FFMPEG_MSG_DeInit(HI_HANDLE handle);

HI_S32 FFMPEG_MSG_ReadMsg(HI_HANDLE handle, HI_VOID *pBuf, long type);

HI_S32 FFMPEG_MSG_WriteMsg(HI_HANDLE handle, HI_VOID *pBuf);

HI_S32 FFMPEG_BUFFER_Init(HI_HANDLE *pstHdl, HI_S32 s32Size);

HI_S32 FFMPEG_BUFFER_CHK_Addr(HI_HANDLE pstHdl, HI_U8 * u8Addr);

HI_U8* FFMPEG_BUFFER_Alloc(HI_HANDLE pstHdl, HI_S32 s32Size);

HI_S32 FFMPEG_BUFFER_Free(HI_HANDLE pstHdl, HI_U8 * u8Addr, HI_S32 s32Size);

HI_S32 FFMPEG_BUFFER_DeInit(HI_HANDLE pstHdl);

HI_U8* FFMPEG_BUFFER_GetFirstAddr(HI_HANDLE pstHdl);

HI_U8* FFMPEG_BUFFER_GetLastAddr(HI_HANDLE pstHdl);

HI_S32 FFMPEG_BUFFER_reset(HI_HANDLE pstHdl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_SVR_MSG_H__ */
