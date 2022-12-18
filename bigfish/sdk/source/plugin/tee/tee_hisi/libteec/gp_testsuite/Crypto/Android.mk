LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= TTA_Crypto_test.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= TTA_Crypto
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)