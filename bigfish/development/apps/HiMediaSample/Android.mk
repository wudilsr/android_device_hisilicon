LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := tests

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_STATIC_JAVA_LIBRARIES += HiMediaPlayer
LOCAL_STATIC_JAVA_LIBRARIES += DisplaySetting
LOCAL_PACKAGE_NAME := HiMediaSample

LOCAL_SDK_VERSION := current


include $(BUILD_PACKAGE)

include $(call all-makefiles-under,$(LOCAL_PATH))
