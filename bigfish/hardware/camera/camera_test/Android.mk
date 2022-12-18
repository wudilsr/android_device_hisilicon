###############################################################################
BUILD_CAMERA_DRIVER_TEST := false
ifeq ($(BUILD_CAMERA_DRIVER_TEST), true)
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)


LOCAL_C_INCLUDES +=

LOCAL_SRC_FILES := CameraDriverTest.cpp

LOCAL_SHARED_LIBRARIES := liblog

LOCAL_MODULE := camera_driver_test
LOCAL_MODULE_TAGS := eng

include $(BUILD_EXECUTABLE)
endif
###############################################################################

