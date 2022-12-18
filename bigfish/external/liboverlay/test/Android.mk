LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	overlay_test.cpp

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libutils \
    libui \
    libhardware \
    liboverlay

LOCAL_C_INCLUDES += \
    hardware/libhardware/modules/gralloc \
    device/hisilicon/bigfish/hardware/gpu/android/gralloc \
    frameworks/native/include/ui \
    frameworks/native/include \
    system/core/include/ \
    $(LOCAL_PATH)/../

LOCAL_MODULE:= test-overlay

LOCAL_MODULE_TAGS := optional

include $(BUILD_EXECUTABLE)