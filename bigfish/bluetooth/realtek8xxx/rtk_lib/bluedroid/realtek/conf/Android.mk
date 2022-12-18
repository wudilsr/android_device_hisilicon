LOCAL_PATH := $(call my-dir)

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_3DD),true)
include $(CLEAR_VARS)

LOCAL_MODULE := rtkbt.feature.3dd.xml

LOCAL_MODULE_CLASS := ETC

LOCAL_MODULE_PATH := $(TARGET_OUT)/etc/permissions

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(LOCAL_MODULE)

include $(BUILD_PREBUILT)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_VR),true)
include $(CLEAR_VARS)

LOCAL_MODULE := rtkbt.feature.vr.xml

LOCAL_MODULE_CLASS := ETC

LOCAL_MODULE_PATH := $(TARGET_OUT)/etc/permissions

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(LOCAL_MODULE)

include $(BUILD_PREBUILT)
endif
