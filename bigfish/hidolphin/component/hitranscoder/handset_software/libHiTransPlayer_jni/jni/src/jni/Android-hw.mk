LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_CFLAGS := -D__STDC_CONSTANT_MACROS
include $(LOCAL_PATH)/../utils.mk
WITH_CONVERTOR := false
WITH_PLAYER := true

ifeq ($(WITH_PLAYER),true)
LOCAL_CFLAGS += -DBUILD_WITH_PLAYER
endif

ifeq ($(WITH_CONVERTOR),true)
LOCAL_CFLAGS += -DBUILD_WITH_CONVERTOR
endif

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../libffmpeg \
    $(LOCAL_PATH)/../libmediaplayer \
    $(LOCAL_PATH)/../include/android

LOCAL_SRC_FILES := \
        onLoad.cpp


ifeq ($(WITH_CONVERTOR),true)
LOCAL_SRC_FILES += \
    com_media_ffmpeg_FFMpeg.c \
    com_media_ffmpeg_FFMpegAVFrame.cpp \
    com_media_ffmpeg_FFMpegAVInputFormat.c \
    com_media_ffmpeg_FFMpegAVRational.c \
    com_media_ffmpeg_FFMpegAVFormatContext.c \
    com_media_ffmpeg_FFMpegAVCodecContext.cpp \
    com_media_ffmpeg_FFMpegUtils.cpp \
    ../libffmpeg/cmdutils.c
endif

ifeq ($(WITH_PLAYER),true)
LOCAL_SRC_FILES += \
    com_media_ffmpeg_FFMpegPlayer.cpp
#com_media_ffmpeg_android_FFMpegPlayerAndroid.cpp
endif

###ifeq ($(IN_NDK),true)
###LOCAL_LDLIBS := -L/root/android-ndk-r4/build/platforms/android-8/arch-arm/usr/lib -llog
###else
###LOCAL_PRELINK_MODULE := false
###LOCAL_SHARED_LIBRARIES := liblog
####endif
####LOCAL_SHARED_LIBRARIES := libjniaudio libjnivideo

LOCAL_PRELINK_MODULE := false

LOCAL_LDLIBS := -llog -L$(LOCAL_PATH)/../../bin/ndk/local/armeabi -lbinder -lmedia -lstagefright -lutils

##LOCAL_SHARED_LIBRARIES := libbinder libmedia libskia  libstagefright libsurfaceflinger_client libutils
##LOCAL_SHARED_LIBRARIES := libutils


LOCAL_STATIC_LIBRARIES := libmediaplayer libavformat libHWAHStreaming libavcodec libavutil libpostproc libswscale libavfilter libSoundTempo libsf libyuv2rgb_neon
##LOCAL_STATIC_LIBRARIES := libmediaplayer libavformat libHWAHStreaming libavcodec libavutil libpostproc libswscale libavfilter

LOCAL_MODULE := libtest1_jni
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)
