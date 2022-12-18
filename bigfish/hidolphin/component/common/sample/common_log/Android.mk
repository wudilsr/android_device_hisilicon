LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
ifeq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
LOCAL_32_BIT_ONLY :=true
endif

include $(SDK_DIR)/Android.def

LOCAL_MODULE:= sample_commonlog
ifneq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_commonlog.c

LOCAL_C_INCLUDES := $(SDK_DIR)/source/common/include/
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/hidolphin/component/common/include/
LOCAL_C_INCLUDES += $(SDK_DIR)/source/msp/include/

LOCAL_SHARED_LIBRARIES := libhi_common libhi_component_common libutils


include $(BUILD_EXECUTABLE)



include $(CLEAR_VARS)
ifeq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
LOCAL_32_BIT_ONLY :=true
endif
include $(SDK_DIR)/Android.def

LOCAL_MODULE:= samplehi_commonlog
ifneq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := samplehi_commonlog.c

LOCAL_C_INCLUDES := $(SDK_DIR)/source/common/include/
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/hidolphin/component/common/include/
LOCAL_C_INCLUDES += $(SDK_DIR)/source/msp/include/

LOCAL_SHARED_LIBRARIES := libhi_common libhi_component_common libutils


include $(BUILD_EXECUTABLE)
