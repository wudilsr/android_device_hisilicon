LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= $(sort $(call all-c-files-under, library))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES :=  libcutils

LOCAL_CFLAGS := -D_FILE_OFFSET_BITS=64 -Wall -W -Wdeclaration-after-statement
LOCAL_CFLAGS += -O2 -fPIC

LOCAL_MODULE:= libpolarssl
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)
