LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(BUILD_MULTI_PREBUILT)

include $(call first-makefiles-under,$(LOCAL_PATH))
