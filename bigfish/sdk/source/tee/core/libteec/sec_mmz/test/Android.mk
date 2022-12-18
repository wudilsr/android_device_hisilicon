LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_sec_mmz.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc \
		   $(LOCAL_PATH)/../../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= test_sec_mmz
ifeq ($(CFG_HI_TEE_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
