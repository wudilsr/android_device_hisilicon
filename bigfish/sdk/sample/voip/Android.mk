LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
#include $(SDK_DIR)/Android.def

VOIP_DIR:=$(SDK_DIR)/source/component/voip
LOCAL_MODULE := sample_voip
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
#LOCAL_CFLAGS += -L$(SDK_SHARE_LIB_DIR)/alsa_bluez

LOCAL_SRC_FILES := voip.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(VOIP_DIR)/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_voip \
                          libhi_common libhi_msp libhi_sample_common libasound

include $(BUILD_EXECUTABLE)
