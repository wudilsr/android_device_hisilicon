LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= gpio-led


LOCAL_CFLAGS += -D$(CHIPNAME)

LOCAL_SRC_FILES := gpio-led.cpp

LOCAL_C_INCLUDES := \
        $(TOP)/device/hisilicon/bigfish/sdk/source/common/include \
        $(TOP)/device/hisilicon/bigfish/sdk/source/msp/include



LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_EXECUTABLE)


