LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/../Android.def
include external/stlport/libstlport.mk

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libdash
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_LIBRARIES := libxml2_ex libcurl
LOCAL_SHARED_LIBRARIES := libstlport liblog

LOCAL_CPPFLAGS := $(CPPFLAGS)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LIBCURL_INCLUDE)
LOCAL_C_INCLUDES += $(LIBXML2_INCLUDE)

CPP_FILE_LIST := $(wildcard $(LOCAL_PATH)/source/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/helpers/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/manager/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/metrics/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/mpd/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/network/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/portable/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/source/xml/*.cpp)

LOCAL_SRC_FILES := $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)