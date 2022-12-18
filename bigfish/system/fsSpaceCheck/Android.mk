LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
    fsSpaceCheck.c

LOCAL_SHARED_LIBRARIES := \
	libcutils

LOCAL_MODULE:= fsSpaceCheck
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_EXECUTABLE)
