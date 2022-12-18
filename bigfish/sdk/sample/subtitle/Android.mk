LOCAL_PATH := $(call my-dir)

#################################sample_subtitle####################################
include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_MODULE := sample_subtitle
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_CFLAGS += -DSTREAM_TYPE_SCTE_82H

LOCAL_SRC_FILES := ../common/hi_adp_demux.c   \
                   ../common/hi_psi_si.c   \
                   ../common/hi_adp_data.c   \
                   ../common/hi_adp_hdmi.c   \
                   ../common/hi_adp_mpi.c   \
                   ../common/hi_adp_search.c   \
                   ../common/hi_filter.c   \
                   ../common/search.c   \
                   ../common/hi_adp_pvr.c   \
                   ../common/hi_adp_osd.cpp  \
                   ../common/OsdManager.cpp   \
                   sample_subtitle.c        \
                   sample_subtitle_data.c      \
                   sample_subtitle_out.c

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
LOCAL_SRC_FILES += ../common/hi_adp_tuner.c

LOCAL_CFLAGS += -DHI_FRONTEND_SUPPORT
endif

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/subtitle
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/subtitle/include
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/subtoutput/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

ifeq ($(strip $(BUILDIN_HISI_GPU_MIDGARD)),true)
HISI_GPU_DIR := midgard
else ifeq ($(strip $(BUILDIN_HISI_GPU)),true)
HISI_GPU_DIR := utgard
endif
LOCAL_C_INCLUDES += $(TOP)/external/skia/include/core
LOCAL_C_INCLUDES += $(TOP)/external/skia/include/images
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/hardware/gpu/android/gralloc
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/hardware/gpu/$(HISI_GPU_DIR)/android/gralloc
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/msp/api/tde/include

LOCAL_SHARED_LIBRARIES := libcutils libutils libhi_common libhi_msp libhi_subtitle libhi_so libskia libui libgui libdl

include $(BUILD_EXECUTABLE)

#################################sample_subtitle####################################
