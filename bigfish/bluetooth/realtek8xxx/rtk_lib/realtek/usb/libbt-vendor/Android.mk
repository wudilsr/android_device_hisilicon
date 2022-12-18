LOCAL_PATH := $(call my-dir)

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_IF), usb)
include $(CLEAR_VARS)

BDROID_DIR := $(TOP_DIR)device/hisilicon/bigfish/bluetooth/realtek8xxx/rtk_lib/bluedroid

LOCAL_SRC_FILES := \
        src/bt_vendor_rtk.c

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/include \
        $(BDROID_DIR)/hci/include \
        $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)/usb

LOCAL_SHARED_LIBRARIES := \
        libcutils

LOCAL_MODULE := libbt-vendor
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_OWNER := hci
LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)

include $(BUILD_SHARED_LIBRARY)

endif # BOARD_HAVE_BLUETOOTH_RTK
