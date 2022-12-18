LOCAL_PATH := $(call my-dir)

###############################sample_dvb_cast#################################
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_dvb_cast
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := dvb_cast.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
LOCAL_CFLAGS += -DHI_KEYLED_SUPPORT
endif

include $(BUILD_EXECUTABLE)
endif

###############################sample_ts_cast#################################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_ts_cast
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := ts_cast.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common \
                          libhi_msp libhi_sample_common

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
LOCAL_CFLAGS += -DHI_KEYLED_SUPPORT
endif

include $(BUILD_EXECUTABLE)


