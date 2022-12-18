LOCAL_PATH := $(call my-dir)

#
# VeriMatrix lib
#
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)


#
# libclientadp
#
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libclientadp
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_CFLAGS := -DANDROID_VERSION
LOCAL_SHARED_LIBRARIES = liblog libutils
LOCAL_C_INCLUDES := $(LOCAL_PATH)/
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := libclientadp.cpp

include $(BUILD_SHARED_LIBRARY)

