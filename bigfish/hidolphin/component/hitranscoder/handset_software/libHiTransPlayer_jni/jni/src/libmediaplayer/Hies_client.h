
#ifndef __HIES_CLIENT__
#define __HIES_CLIENT__

#include "Hies_proto.h"

#define NOPTS_VALUE          INT64_C(0x8000000000000000)

#ifdef __cplusplus
extern "C" {
#endif

int HI_HIES_Init_Codec(AVCodecContext** pVideoCtx, AVCodecContext** pAudioCtx);

int HI_HIES_DeInit_Codec(AVCodecContext* pVideoCtx, AVCodecContext* pAudioCtx);
int HI_HIES_decodeVideo(AVCodecContext *pCtx, void *outdata, int *outdata_size, AVPacket *avpkt);
int HI_HIES_decodeAudio(AVCodecContext *pCtx, void *outdata, int *outdata_size, AVPacket *avpkt);
void* HI_HIES_av_malloc(int size);
void HI_HIES_av_free(void* ptr);
void HI_HIES_init_packet(AVPacket *pkt);

int HI_HIES_try_decode_stream(void);
#ifdef __cplusplus
}
#endif
#endif
