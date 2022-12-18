LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libca_update
LOCAL_CFLAGS := -lpthread -Wall -lhi_common
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/ctit/src/update/alg
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../common/api/flash/include
LOCAL_SRC_FILES  := $(sort $(call all-c-files-under, ctit/src/update/alg))
LOCAL_SRC_FILES  += ctit/src/update/auth/auth.c
LOCAL_STATIC_LIBRARIES := libhi_msp libhi_common libc liblog
include $(BUILD_STATIC_LIBRARY)

ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libhi_nagra
LOCAL_CFLAGS := -lpthread -Wall -lhi_common
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_API_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/nagra/include
LOCAL_CFLAGS += -DSDK_SECURITY_ARCH_VERSION_V3
LOCAL_SRC_FILES  := nagra/api/nocs_csd.c
LOCAL_SHARED_LIBRARIES := libhi_msp libhi_common libc liblog
include $(BUILD_SHARED_LIBRARY)
endif
