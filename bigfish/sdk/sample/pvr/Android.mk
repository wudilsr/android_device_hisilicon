LOCAL_PATH := $(call my-dir)

#######################sample_pvr########################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)

#######################sample_pvr_rec_allts########################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr_rec_allts
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr_rec_allts.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)

#######################sample_pvr_multifile_play########################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr_multifile_play
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr_multifile_play.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)

#######################sample_pvr_timeshift########################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr_timeshift
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr_timeshift.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)

#######################sample_pvr_play########################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr_play
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr_play.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)


#######################sample_pvr_rec########################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr_rec
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr_rec.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)

#######################sample_pvr_eth_timeshift########################
include $(CLEAR_VARS)
include $(SDK_DIR)/$(SDK_CFGFILE)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_pvr_eth_timeshift
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_SRC_FILES := sample_pvr_eth_timeshift.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include

LOCAL_SHARED_LIBRARIES := libcutils libhi_common libhi_msp libhi_sample_common

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libfreetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
LOCAL_SHARED_LIBRARIES += libz
endif

include $(BUILD_EXECUTABLE)