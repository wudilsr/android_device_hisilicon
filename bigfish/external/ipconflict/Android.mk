LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= ipconflict.c

LOCAL_SHARED_LIBRARIES := \
    liblog

LOCAL_C_INCLUDES := \
    system/core/include/netutils

LOCAL_CFLAGS := -O2

LOCAL_MODULE:= ipconflict
LOCAL_SHARED_LIBRARIES := libcutils
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_EXECUTABLE)
