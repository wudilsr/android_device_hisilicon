#ifndef __HI_MLOGER_H__
#define __HI_MLOGER_H__

#include <android/log.h>


#define  MMLOGI(TAG, ...)   __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)

#define  MMLOGD(TAG, ...)   __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

#define  MMLOGE(TAG, ...)   __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)

#define  MMLOGW(TAG, ...)   __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)

#define  MMLOGV(TAG, ...)   __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)

#endif
