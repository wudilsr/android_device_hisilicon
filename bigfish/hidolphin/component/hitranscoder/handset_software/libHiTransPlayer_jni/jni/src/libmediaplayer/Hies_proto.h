
#ifndef __HIES_PROTO__
#define __HIES_PROTO__
#include "libavcodec/avcodec.h"
#include "hi_type.h"

#define MAX_AUDIO_BUF_NUM  40
#define MAX_VIDEO_BUF_NUM  15
typedef int BOOL;


#ifdef __cplusplus
extern "C" {
#endif
// 1 second of 48khz 32bit audio
#define MAX_AUDIO_FRAME_SIZE (10*1024)
#define MAX_VIDEO_FRAME_SIZE (320*1024)

void HI_HIES_log_set_callback(void (*callback)(void*, int, const char*, va_list));

int HI_HIES_Init_Proto(void);
int HI_HIES_DeInit_Proto(void);
void HI_HIES_Reset_mediaBuf(void);

int  HI_HIES_Connect(char* mUrl);

int HI_HIES_read_audio_stream(void* ptr, int* dataSize, int64_t* pts);

int HI_HIES_read_video_stream(void* ptr, int* dataSize, int64_t* pts, int* pType);

void* HI_HIES_get_VideoData(void* arg);

void* HI_HIES_get_AudioData(void* arg);

void HI_HIES_set_ResetFlag(BOOL bFlag);

int HI_HIES_GetParameterFrame(HI_U8* pSpsBuffer,int* spsLen,HI_U8* pPPSBuffer,int* ppsLen);

int HI_HIES_GetVideoHeight(void);

int HI_HIES_GetVideoWidth(void);

#ifdef __cplusplus
}
#endif
#endif
