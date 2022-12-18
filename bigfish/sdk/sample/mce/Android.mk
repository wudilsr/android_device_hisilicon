LOCAL_PATH := $(call my-dir)

############################sample_mce_update############################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_mce_update
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_mce_update.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include

LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)

############################sample_mce_trans############################
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
  
LOCAL_MODULE := sample_mce_trans
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
  
LOCAL_MODULE_TAGS := optional
  
LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
  
LOCAL_SRC_FILES := sample_mce_trans.c
  
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
  
LOCAL_SHARED_LIBRARIES := liblog libcutils libdl libm libhi_common libhi_msp libhi_sample_common
  
ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif
  
ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)
endif
