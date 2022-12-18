LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libhi_3g

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
HI3G_DIR := .
LOCAL_SRC_FILES := \
        $(HI3G_DIR)/src/hi_3g_intf.c    \
	$(HI3G_DIR)/src/3g_intf.c  \
	$(HI3G_DIR)/src/3g_ids.c  

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/src
LOCAL_C_INCLUDES += $(SDK_DIR)/../../../../system/core/include/
LOCAL_SHARED_LIBRARIES := libcutils libutils libdl libhi_common liblog

include $(BUILD_SHARED_LIBRARY)
