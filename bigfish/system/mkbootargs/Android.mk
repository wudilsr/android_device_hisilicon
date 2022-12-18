LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
	mkbootargs.c

LOCAL_CFLAGS =   -O2 -Wall

LOCAL_C_INCLUDES :=

LOCAL_STATIC_LIBRARIES := libz

LOCAL_MODULE := mkbootargs

include $(BUILD_HOST_EXECUTABLE)
