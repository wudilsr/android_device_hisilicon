LOCAL_PATH := $(call my-dir)

#################################sample_cc####################################
include $(CLEAR_VARS)

$(shell mkdir -p $(TARGET_OUT)/ttx)

$(shell cp -r $(LOCAL_PATH)/res/font0.bin $(TARGET_OUT)/ttx/)

include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_teletext
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
LOCAL_CFLAGS += -DHI_FRONTEND_SUPPORT
endif

LOCAL_SRC_FILES := sample_ts_ttx.c        \
                   sample_teletext_font.c      \
                   sample_teletext_out.c        \
                   sample_ttx_port.c            \
                   sample_teletext_msg.c          

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/teletext
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/teletext/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common libhi_ttx

include $(BUILD_EXECUTABLE)

#################################sample_cc####################################
