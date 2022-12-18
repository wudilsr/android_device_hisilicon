LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

VOIP_ROOT_DIR:=device/hisilicon/bigfish
#SDK_DIR:= $(ROOT_DIR)/sdk/s
EXT_DIR:= $(VOIP_ROOT_DIR)/external
COMMON_DIR  := $(SDK_DIR)/source/common
VOIP_DIR := $(SDK_DIR)/source/component/voip
ALSA_DIR := $(EXT_DIR)/alsa-lib

LOCAL_MODULE := libhi_voip
LOCAL_ARM_MODE := arm
LOCAL_PRELINK_MODULE := false
LOCAL_C_INCLUDES += \
		$(LOCAL_PATH)/include \
		$(LOCAL_PATH)/src \
		$(VOIP_DIR)/include  \
		$(VOIP_DIR)/drv/include \
		$(VOIP_DIR)/drv/hme/inc \
		$(COMMON_DIR)/include \
		$(COMMON_DIR)/drv/include \
		$(COMMON_DIR)/api/include  \
		$(ALSA_DIR)/include/ \

LOCAL_CFLAGS += -D_POSIX_C_SOURCE -Wall -O2 -g $(CFG_CFLAGS) $(USER_CFLAGS)

API_DIR := .
LOCAL_SRC_FILES := $(API_DIR)/unf/hi_unf_voip.c
LOCAL_SRC_FILES += $(API_DIR)/hme/mpi_voip_hme.c
LOCAL_SRC_FILES += $(API_DIR)/hme/msg_trace.c

LOCAL_SRC_FILES += $(API_DIR)/aud_adp/mpi_aud_adp.c


LOCAL_SHARED_LIBRARIES := liblog libcutils libasound libhi_common libhi_msp
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
