/**
 \file drm.h
 \brief
 \author HiSilicon Technologies Co., Ltd.
 \date 2012-2022
 \version 1.0
 \author z00187490
 \date 2012-10-27
 */

#ifndef DRM_H_
#define DRM_H_

#include "avformat.h"
#include "asf.h"

//------------------------------------------------------------------------------
#define NEW(type) (type*)av_malloc(sizeof(type))
#define FREE(ptr) if (ptr) av_free(ptr)
#define MEMSET(p, size) av_memset(p, 0, size)

#if defined (ANDROID_VERSION)
#include <utils/Log.h> //for LOGX
#define LOG_TAG "DRM"
#else
#define LOGE(fmt, ...) av_log(NULL, AV_LOG_ERROR, fmt"\n", ##__VA_ARGS__)
#define LOGI(fmt, ...) av_log(NULL, AV_LOG_INFO, fmt"\n", ##__VA_ARGS__)
#define LOGD(fmt, ...) av_log(NULL, AV_LOG_DEBUG, fmt"\n", ##__VA_ARGS__)
#endif
#define CHECK(cond, action, fmt, ...)\
    if (cond) {\
        av_log(NULL, AV_LOG_ERROR, "Check {"#cond"} fail at [%s,%d], we will {"#action"}, msg:"#fmt"\n",\
            __FILE__, __LINE__, ##__VA_ARGS__);\
        action;\
    }
/*return value of all interface*/
enum {
    DRM_NOERR       = 0,
    DRM_ERROR       = -1,
    DRM_NOMEM       = AVERROR(ENOMEM),
    DRM_INVALID     = AVERROR(EINVAL),
};
/*Define commands for control methods*/
enum {
    CMD_GET_HANDLE,
};

/*status code of drm*/
enum {
    STATUS_OK,
    STATUS_INVALID,
    STATUS_NOTOPEN,
    STATUS_NORIGHTS,
};
//------------------------------------------------------------------------------

typedef struct tagDRMFormat
{
    AVFormatContext*            enc_ctx;
    void*                       priv;
    int                         status;
    AVInputFormat*              iformat;
    /*member methods*/
    int (*decrypt)(struct tagDRMFormat* drm, AVPacket* pkt);
    int (*control)(struct tagDRMFormat* drm, int cmd, void* arg);
    int (*seek)(struct tagDRMFormat* drm, int stream_index,
                         int64_t timestamp, int flags);
    void (*destroy)(struct tagDRMFormat* drm);
} DRMFormat;

/*decrypt input data*/
static inline int drm_decrypt(DRMFormat* drm, AVPacket* pkt) {
    if (drm && drm->decrypt)
        return drm->decrypt(drm, pkt);
    return DRM_ERROR;
}

/*Extend interface for operate DRM engine*/
static inline int drm_control(DRMFormat* drm, int cmd, void* arg)
{
    if (drm && drm->control)
        return drm->control(drm, cmd, arg);
    return DRM_ERROR;
}

static inline int drm_seek(struct tagDRMFormat* drm, int stream_index,
                         int64_t timestamp, int flags)
{
    if (drm && drm->seek)
        return drm->seek(drm, stream_index, timestamp, flags);
    return DRM_ERROR;
}

/*Destroy this DRM context*/
static inline void drm_destroy(DRMFormat* drm)
{
    if (drm && drm->destroy)
        return drm->destroy(drm);
    return;
}

/*init drm to playready object*/
int drm_init(DRMFormat* drm, void* arg);

int g_wmdrm_decrypt(void* data, int size);

#endif /* DRM_H_ */
