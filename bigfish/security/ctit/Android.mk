LOCAL_PATH := $(call my-dir)

ifeq ($(HISILICON_SECURITY_L2),true)
include $(CLEAR_VARS)
PREBUILT_STATIC_MODULE_NAMES := libhi_ctit_release libhi_ctit_debug
ALL_DEFAULT_INSTALLED_MODULES += $(PREBUILT_STATIC_MODULE_NAMES)
LOCAL_PREBUILT_LIBS := lib/libhi_ctit_release.a lib/libhi_ctit_debug.a 
LOCAL_STATIC_LIBRARIES := libhi_ctit_release libhi_ctit_debug 
include $(BUILD_MULTI_PREBUILT)
endif
