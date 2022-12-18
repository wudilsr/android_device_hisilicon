ifeq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
PNG_MODULE_MAKEFILES := $(call all-named-subdir-makefiles, libpng_for_5.0)
else
PNG_MODULE_MAKEFILES := $(call all-named-subdir-makefiles, libpng)
endif

LOCAL_PATH := $(call my-dir)

########## shared lib
include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libhi_png
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_CFLAGS += -DCONFIG_GFX_STB_SDK

LOCAL_SRC_FILES := $(sort $(call all-c-files-under, ./libpng-1.4.0))

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/png/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpeg/grc_cmm_inc

LOCAL_SHARED_LIBRARIES := libcutils libutils libdl libhi_common libz

include $(BUILD_SHARED_LIBRARY)

########## static lib
include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libhi_png
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_CFLAGS += -DCONFIG_GFX_STB_SDK

LOCAL_SRC_FILES := $(sort $(call all-c-files-under, ./libpng-1.4.0))

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/png/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpeg/grc_cmm_inc

LOCAL_SHARED_LIBRARIES := libcutils libutils libdl libhi_common libz

include $(BUILD_STATIC_LIBRARY)

include $(PNG_MODULE_MAKEFILES)