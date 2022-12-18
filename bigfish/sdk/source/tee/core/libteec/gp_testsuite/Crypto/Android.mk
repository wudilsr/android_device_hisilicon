LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= TTA_Internal_API_Crypto.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tta_crypto
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
