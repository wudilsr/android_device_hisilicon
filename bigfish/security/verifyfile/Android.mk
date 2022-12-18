LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES := verifytool.c
LOCAL_SRC_FILES += rsa.c
LOCAL_SRC_FILES += bignum.c
LOCAL_SRC_FILES += hash256.c
LOCAL_SRC_FILES += hash1.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/msp/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/common/include

LOCAL_MODULE:= libhiverifytool

LOCAL_MULTILIB := 32

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_LIBRARIES += libhi_msp libhi_common

include $(BUILD_STATIC_LIBRARY)