#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define IN
#define OUT

typedef struct{
    void *(*init)(IN int flags);
    int (*read)(IN void *handle, IN unsigned char *buf, IN int size);
    int (*ready)(IN void *handle);
    int (*exit)(IN void *handle);
}wiptv_callback;

extern "C" {
#include "vformat.h"
#include "aformat.h"
}

#define TRICKMODE_NONE       0x00
#define TRICKMODE_I          0x01
#define TRICKMODE_FFFB       0x02

typedef struct{
    unsigned short    pid;//pid
    int               nVideoWidth;//视频宽度
    int               nVideoHeight;//视频高度
    int               nFrameRate;//帧率
    vformat_t         vFmt;//视频格式
    unsigned long     cFmt;//编码格式
}VIDEO_PARA_T, *PVIDEO_PARA_T;

typedef struct{
    unsigned short     pid;//pid
    int                nChannels;//声道数
    int                nSampleRate;//采样率
    aformat_t          aFmt;//音频格式
    int                nExtraSize;
    unsigned char*     pExtraData;
}AUDIO_PARA_T, *PAUDIO_PARA_T;

#endif
