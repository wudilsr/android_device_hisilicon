LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULES_NAME := libmsc

define addsuffix_so_list
$(addsuffix .so, $(1))
endef

LOCAL_PREBUILT_LIBS := $(call addsuffix_so_list,$(LOCAL_MODULES_NAME))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)
