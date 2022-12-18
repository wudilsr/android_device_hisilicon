LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libhi_sample_common
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
ifeq ($(strip $(PLATFORM_VERSION)), 5.0)
LOCAL_CFLAGS +=
else
LOCAL_CFLAGS += -DANDROID44
endif

ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
LOCAL_CFLAGS += -DHI_HDMI_RX_INSIDE
endif

ifeq ($(CFG_HI_AI_SUPPORT),y)
LOCAL_CFLAGS += -DHI_AUDIO_AI_SUPPORT
endif

LOCAL_SRC_FILES :=  hi_adp_demux.c      \
                    hi_psi_si.c         \
                    hi_adp_data.c       \
                    hi_adp_hdmi.c       \
                    hi_adp_hdmi_rx.c    \
                    hi_adp_mpi.c        \
                    hi_adp_search.c     \
                    hi_filter.c         \
                    search.c            \
                    hi_adp_osd.cpp      \
                    OsdManager.cpp

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
LOCAL_SRC_FILES +=  hi_adp_tuner.c
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
LOCAL_SRC_FILES +=  hi_adp_pvr.c
endif
endif

ifeq ($(strip $(BUILDIN_HISI_GPU_MIDGARD)),true)
HISI_GPU_DIR := midgard
else ifeq ($(strip $(BUILDIN_HISI_GPU)),true)
HISI_GPU_DIR := utgard
endif
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_C_INCLUDES += $(TOP)/external/skia/include/core
LOCAL_C_INCLUDES += $(TOP)/external/skia/include/images
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/hardware/gpu/android/gralloc
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/hardware/gpu/$(HISI_GPU_DIR)/android/gralloc
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/msp/api/tde/include

LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_msp libskia libui libgui libdl

include $(BUILD_SHARED_LIBRARY)
