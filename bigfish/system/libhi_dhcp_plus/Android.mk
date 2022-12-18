LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= hi_dhcp_plus.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += device/hisilicon/bigfish/external/polarssl-1.3.7/include

LOCAL_SHARED_LIBRARIES := libpolarssl libcutils

LOCAL_MODULE:= libhi_dhcp_plus
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)
