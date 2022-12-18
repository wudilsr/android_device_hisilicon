LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES := \
    hiemptydrm.cpp \
    emptycpy.c


LOCAL_C_INCLUDES := \
    bionic \
    frameworks/av/include \
    frameworks/native/include

LOCAL_C_INCLUDES += $(SDK_DIR)/source/common/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/msp/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/tee/core/libteec/inc
LOCAL_C_INCLUDES += $(SDK_DIR)/source/common/api/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../util

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    liblog \
    libstagefright_foundation \
    libutils \
    libhi_msp \
    libhi_common \
    libteec \
    libdrmutil \


LOCAL_MODULE := libemptydrmplugin

LOCAL_MULTILIB := 32
LOCAL_CFLAGS += -Wlong-long -Wformat -Wpointer-arith
$(warning $(PLATFORM_VERSION))
ifeq "5." "$(findstring 5.,$(PLATFORM_VERSION))"
LOCAL_CFLAGS  := -DANDROID_5_X
endif

LOCAL_MODULE_PATH := $(TARGET_OUT_VENDOR_SHARED_LIBRARIES)/mediadrm

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
