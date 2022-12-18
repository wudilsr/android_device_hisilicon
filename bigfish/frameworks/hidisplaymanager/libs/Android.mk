LOCAL_PATH:= $(call my-dir)
####################################################################################

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES:= \
    DisplayService.cpp\
    IDisplayService.cpp
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils\
    libcutils\
    libui\
    libandroid_runtime \
    libhardware
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../hal \
    $(TOP)/framework/native/services/surfaceflinger \
    $(TOP)/hardware/libhardware/include \
    $(TOP)/hardware/libhardware/include/hardware \
    $(TOP)/hardware/libhardware/modules/gralloc \

LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/msp/drv/hifb/include
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/common/include
LOCAL_MODULE:= libhidisplayservice
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_SHARED_LIBRARY)

###################################################################################

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= \
    DisplayClient.cpp \
    IDisplayService.cpp

LOCAL_SHARED_LIBRARIES := \
    libui \
    libutils \
    libcutils \
    libbinder
LOCAL_MODULE := libhidisplayclient
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_SHARED_LIBRARY)

####################################################################################

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= \
    display_test_app.cpp \
    IDisplayService.cpp

LOCAL_SHARED_LIBRARIES := \
    libui \
    libutils \
    libcutils \
    libbinder \
    libhidisplayclient

LOCAL_C_INCLUDES :=  \
    $(LOCAL_PATH)/../../include/gui
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= disptest
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_EXECUTABLE)
