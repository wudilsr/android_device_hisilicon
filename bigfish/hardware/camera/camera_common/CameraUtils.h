/*
 **************************************************************************************
 *       Filename:  CameraUtils.h
 *    Description:  CameraUtils header file
 *
 *        Version:  1.0
 *        Created:  2011-05-16 09:04:04
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERAUTILS_H_INCLUDED
#define CAMERAUTILS_H_INCLUDED

#include <sys/syscall.h>
#include <utils/Timers.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define CAMERA_EVENT_LOGI(x, ...) ALOGI("[%s] "x, "CAMERA_EVENT", ##__VA_ARGS__)
#define CAMERA_EVENT_LOGE(x, ...) ALOGE("[%s] "x, "CAMERA_EVENT", ##__VA_ARGS__)
#define CAMERA_EVENT_LOGW(x, ...) ALOGW("[%s] "x, "CAMERA_EVENT", ##__VA_ARGS__)
#define CAMERA_PARAM_LOGI(x, ...) ALOGI("[%s] "x, "CAMERA_PARAM", ##__VA_ARGS__)
#define CAMERA_PARAM_LOGW(x, ...) ALOGW("[%s] "x, "CAMERA_PARAM", ##__VA_ARGS__)
#define CAMERA_PARAM_LOGE(x, ...) ALOGE("[%s] "x, "CAMERA_PARAM", ##__VA_ARGS__)

#define CAMERA_HAL_LOGV(x, ...) ALOGV("[%s] "x, "CAMERA_HAL", ##__VA_ARGS__)
#define CAMERA_HAL_LOGI(x, ...) ALOGI("[%s] "x, "CAMERA_HAL", ##__VA_ARGS__)
#define CAMERA_HAL_LOGD(x, ...) ALOGD("[%s] "x, "CAMERA_HAL", ##__VA_ARGS__)
#define CAMERA_HAL_LOGW(x, ...) ALOGW("[%s] "x, "CAMERA_HAL", ##__VA_ARGS__)
#define CAMERA_HAL_LOGE(x, ...) ALOGE("[%s] "x, "CAMERA_HAL", ##__VA_ARGS__)

#define CAMERA_DELETE(ptr)          \
    do                              \
    {                               \
        if(ptr)                     \
        {                           \
            delete ptr;             \
            ptr = NULL;             \
        }                           \
    }while(0)

#define CAMERA_DELETE_ARRAY(ptr)    \
    do                              \
    {                               \
        if(ptr)                     \
        {                           \
            delete []ptr;           \
            ptr = NULL;             \
        }                           \
    }while(0)

#define CAMERA_FREE(ptr)            \
    do                              \
    {                               \
        if(ptr)                     \
        {                           \
            free(ptr);              \
            ptr = NULL;             \
        }                           \
    }while(0)


namespace android {

int     convertFormat2V4L2Format(const char *format);

int     convertFormat2SurfaceFormat(int format);

int     getPixelDepth(int foramt);

pid_t   getCurrentThreadId();

unsigned long   measureTime(nsecs_t start, nsecs_t stop);

}; // namespace android

#endif /*CAMERAUTILS_H_INCLUDED*/

/********************************* END ***********************************************/
