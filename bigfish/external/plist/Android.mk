# libplist Android.mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libplist
LOCAL_32_BIT_ONLY := true
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := -U__VFP_FP__ -D__ANDROID_LINUX

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/include \
        $(LOCAL_PATH)/libcnary/include \
        external/libxml2/include \
        external/icu4c/common \
        external/icu/icu4c/source/common

include external/stlport/libstlport.mk

LOCAL_SRC_FILES := \
    src/Array.cpp \
    src/Boolean.cpp \
    src/Data.cpp \
    src/Date.cpp \
    src/Dictionary.cpp \
    src/Integer.cpp \
    src/Node.cpp \
    src/Real.cpp \
    src/String.cpp \
    src/Structure.cpp \
    src/base64.c \
    src/bplist.c \
    src/bytearray.c \
    src/hashtable.c \
    src/plist.c \
    src/ptrarray.c \
    src/xplist.c \
    libcnary/list.c \
    libcnary/node.c \
    libcnary/node_list.c \
    libcnary/node_iterator.c \
    plutil/plutil.c

LOCAL_SHARED_LIBRARIES := libstlport libicuuc libutils

LOCAL_STATIC_LIBRARIES := libxml2

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := plist_read
LOCAL_32_BIT_ONLY := true
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_SRC_FILES := test/plist_test.c
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libicuuc libutils
LOCAL_STATIC_LIBRARIES := libplist libxml2
include $(BUILD_EXECUTABLE)
