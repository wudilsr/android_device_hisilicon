LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES := \
    hi_drm_util.c

LOCAL_C_INCLUDES := \
    bionic \
    frameworks/av/include \
    frameworks/native/include

LOCAL_C_INCLUDES += $(SDK_DIR)/source/common/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/msp/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/tee/core/libteec/inc
LOCAL_C_INCLUDES += $(SDK_DIR)/source/common/api/include

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    liblog \
    libstagefright_foundation \
    libutils \
    libhi_msp \
    libhi_common \
    libteec \

LOCAL_MODULE := libdrmutil

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
