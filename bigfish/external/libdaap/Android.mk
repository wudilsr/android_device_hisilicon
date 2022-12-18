# avahi Android.mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false


APP_STL := stlport_static
#STLPORT_FORCE_REBUILD := true
#APP_STL := gnustl_static
#APP_STL := stlport_shared

LOCAL_MODULE := libdaap
LOCAL_32_BIT_ONLY := true
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CPPFLAGS += -frtti

include external/stlport/libstlport.mk

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/include

LOCAL_SRC_FILES := \
    lib/chunk-info.cpp \
    lib/chunk.cpp \
    lib/container-chunk.cpp \
    lib/content-codes.cpp \
    lib/integer-chunk.cpp \
    lib/string-chunk.cpp \
    lib/version-chunk.cpp \
    lib/cxa_bad_cast.cpp

LOCAL_SHARED_LIBRARIES := libstlport libgabi++ libicuuc

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)


#include $(CLEAR_VARS)
#LOCAL_PRELINK_MODULE := false
#LOCAL_MODULE := daap_read
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
#LOCAL_MODULE_TAGS := optional

#include external/stlport/libstlport.mk

#LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/include

#LOCAL_SRC_FILES := \
        tests/chunk-read.cpp

#LOCAL_SHARED_LIBRARIES := libstlport libgabi++ libicuuc
#LOCAL_STATIC_LIBRARIES := libdaap

#include $(BUILD_EXECUTABLE)
#include $(call first-makefiles-under,$(LOCAL_PATH))
