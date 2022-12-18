###############################################################################
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES += device/hisilicon/bigfish/hardware/camera/camera_common

LOCAL_SRC_FILES := CapabilityManager.cpp

LOCAL_SHARED_LIBRARIES :=

LOCAL_STATIC_LIBRARIES :=

LOCAL_MODULE := libcamera_capability_manager

LOCAL_MODULE_TAGS := optional
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_STATIC_LIBRARY)
###############################################################################
