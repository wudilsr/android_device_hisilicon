LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libhi_subtitle
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

CURDIR := .
LOCAL_SRC_FILES := $(CURDIR)/src/hi_unf_subt.c
LOCAL_SRC_FILES += $(CURDIR)/src/subtitle_data.c
LOCAL_SRC_FILES += $(CURDIR)/src/subtitle_parse.c
LOCAL_SRC_FILES += $(CURDIR)/src/scte_subt_data.c
LOCAL_SRC_FILES += $(CURDIR)/src/scte_subt_display.c
LOCAL_SRC_FILES += $(CURDIR)/src/scte_subt_parse.c

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES := libcutils libutils libdl libhi_common

include $(BUILD_SHARED_LIBRARY)
