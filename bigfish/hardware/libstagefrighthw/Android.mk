LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := \
    HisiOMXPlugin.cpp

LOCAL_C_INCLUDES:= \
        frameworks/native/include/media/openmax \
        frameworks/native/include/media/hardware

LOCAL_SHARED_LIBRARIES :=       \
        libbinder               \
        libutils                \
        libcutils               \
        libui                   \
        libdl

LOCAL_MODULE := libstagefrighthw
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
