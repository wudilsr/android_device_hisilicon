LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

PREBUILT_STATIC_MODULE_NAMES := libhigo libhigoadp
ALL_DEFAULT_INSTALLED_MODULES += $(PREBUILT_STATIC_MODULE_NAMES)

LOCAL_PREBUILT_LIBS := lib/loader/libhigo.a  lib/loader/libhigoadp.a
LOCAL_STATIC_LIBRARIES := libhigo libhigoadp

include $(BUILD_MULTI_PREBUILT)
