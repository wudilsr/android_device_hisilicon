LOCAL_PATH := $(call my-dir)

#################################sample_cc####################################
include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_cc
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
LOCAL_CFLAGS += -DHI_FRONTEND_SUPPORT
endif

LOCAL_SRC_FILES := sample_cc.c        \
                   sample_cc_out.c    \
                   sample_cc_data.c   \
                   sample_cc_xds.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/cc
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/cc/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common libhi_cc libskia

include $(BUILD_EXECUTABLE)

#################################sample_cc####################################
