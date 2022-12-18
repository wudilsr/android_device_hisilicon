LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

#
# component hitranscoder libraries
#
include $(CLEAR_VARS)
LOCAL_PREMODULE_SO := \
        libhi_transcoder \
        libhi_protocol \
        libhi_muxer \
        libprotocol_local \
        libmuxer_es \

define addprefixsuffix_so_list
$(addprefix libs/, $(addsuffix .so, $(1)))
endef

LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list, $(LOCAL_PREMODULE_SO))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PREMODULE_SO)

LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := sample_transcoder_tsplay
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_muxer libhi_transcoder libhi_protocol libhi_msp libhi_sample_common
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/component/ha_codec/include
LOCAL_C_INCLUDES += $(SDK_DIR)/sample/common
LOCAL_C_INCLUDES += $(SDK_DIR)/source/msp/drv/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_SRC_FILES := samples/sample_transcoder_tsplay.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := sample_transcoder_dvbplayer
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_muxer libhi_transcoder libhi_protocol libhi_msp libhi_sample_common
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/component/ha_codec/include
LOCAL_C_INCLUDES += $(SDK_DIR)/sample/common
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_SRC_FILES := samples/sample_transcoder_dvbplayer.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
endif

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := sample_transcoder_pipplayer
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_muxer libhi_transcoder libhi_protocol libhi_msp libhi_sample_common
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/component/ha_codec/include
LOCAL_C_INCLUDES += $(SDK_DIR)/sample/common
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_SRC_FILES := samples/sample_transcoder_pipplayer.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
endif

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := sample_transcoder_osdplayer
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_muxer libhi_transcoder libhi_protocol libhi_msp libhi_sample_common
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/component/ha_codec/include
LOCAL_C_INCLUDES += $(SDK_DIR)/sample/common
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_SRC_FILES := samples/sample_transcoder_osdplayer.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := sample_transcoder_hlsplayer
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_muxer libhi_transcoder libhi_protocol libhi_msp libhi_sample_common
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(SDK_DIR)/source/component/ha_codec/include
LOCAL_C_INCLUDES += $(SDK_DIR)/sample/common
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_SRC_FILES := samples/sample_transcoder_hlsplayer.c
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)