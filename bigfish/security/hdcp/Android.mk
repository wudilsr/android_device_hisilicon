LOCAL_PATH:= $(call my-dir)
WFD_SRC_DIR := $(LOCAL_PATH)/../../source

include $(CLEAR_VARS)
LOCAL_PREBUILT_LIBS := lib/libhihdcp_tool.a 
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libhihdcp.so
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)
LOCAL_SRC_FILES := lib/libhihdcp.so
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_MODULE := sample_hdcp_burn
LOCAL_MODULE_TAGS := optional
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := sample/sample_hdcp_burn.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/util
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/common/include/
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/frameworks/hisysmanager/libs
LOCAL_C_INCLUDES += $(TOP)/system/core/include/
LOCAL_C_INCLUDES += $(TOP)/external/stlport/stlport
LOCAL_C_INCLUDES += $(TOP)/bionic/libstdc++
LOCAL_C_INCLUDES += $(TOP)/bionic
LOCAL_SHARED_LIBRARIES += libhi_component_common
LOCAL_SHARED_LIBRARIES += libhi_common libhi_msp libc liblog
LOCAL_SHARED_LIBRARIES += libcrypto

LOCAL_SHARED_LIBRARIES += libcutils libutils 
LOCAL_SHARED_LIBRARIES += libhisysmanagerclient
LOCAL_STATIC_LIBRARIES += libhihdcp_tool
LOCAL_SHARED_LIBRARIES += libstlport
include $(BUILD_EXECUTABLE)
