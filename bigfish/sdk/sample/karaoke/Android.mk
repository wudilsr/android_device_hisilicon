LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES := karaoke.c

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
	libutils\
	libhi_common \
	libhi_msp \
	liblog \
	libasound \
	libhi_karaoke \
	libhi_sample_common \
	libhi_common


LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/karaoke/include
LOCAL_C_INCLUDES += $(SAMPLE_DIR)/common
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include

LOCAL_MODULE := sample_karaoke
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_EXECUTABLE)
