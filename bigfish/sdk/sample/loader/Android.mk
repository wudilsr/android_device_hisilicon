LOCAL_PATH := $(call my-dir)

ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE:= sample_loader
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_CFLAGS += -DHI_LOADER_APPLOADER

LOCAL_SRC_FILES:= sample_loader.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/loader/api/include

LOCAL_SHARED_LIBRARIES := libcutils libhiloader libhi_common libhi_msp

include $(BUILD_EXECUTABLE)

endif
