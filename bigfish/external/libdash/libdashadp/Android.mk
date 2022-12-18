LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/../Android.def
include external/stlport/libstlport.mk

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libdashadp
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libdash libavformat libavutil libavcodec
LOCAL_SHARED_LIBRARIES += libstlport

HISUB_SUPPORT := true

LOCAL_C_INCLUDES += $(LOCAL_PATH) \
                    $(LOCAL_PATH)/Decoder \
                    $(LOCAL_PATH)/Managers \
                    $(LOCAL_PATH)/libdashframework/Adaptation \
                    $(LOCAL_PATH)/libdashframework/Buffer \
                    $(LOCAL_PATH)/libdashframework/Input \
                    $(LOCAL_PATH)/libdashframework/MPD \
                    $(LOCAL_PATH)/libdashframework/Protable

LOCAL_C_INCLUDES += $(LIBDASH_INCLUDE)
LOCAL_C_INCLUDES += $(LIBCURL_INCLUDE)
LOCAL_C_INCLUDES += $(FFMPEG_INCLUDE)

LOCAL_CPPFLAGS := $(CPPFLAGS)

CPP_FILE_LIST := $(wildcard $(LOCAL_PATH)/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/Decoder/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/Managers/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/libdashframework/Adaptation/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/libdashframework/Buffer/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/libdashframework/Input/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/libdashframework/MPD/*.cpp) \
                 $(wildcard $(LOCAL_PATH)/libdashframework/Protable/*.cpp)

ifdef HISUB_SUPPORT
LOCAL_C_INCLUDES += $(HISUB_DIR)/include
LOCAL_CPPFLAGS += -DHISUB_SUPPORT
LOCAL_SHARED_LIBRARIES += libhi_subparse
endif

LOCAL_SRC_FILES := $(CPP_FILE_LIST:$(LOCAL_PATH)/%=%)

include $(BUILD_SHARED_LIBRARY)
