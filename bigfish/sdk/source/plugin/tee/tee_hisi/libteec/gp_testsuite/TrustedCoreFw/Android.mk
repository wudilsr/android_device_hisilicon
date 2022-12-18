LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= TTA_TCF.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= TTA_TCF
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= TTA_TCF_SingleInstanceTA.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= TTA_TCF_SingleInstaceTA
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= TTA_TCF_MultipleInstanceTA.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= TTA_TCF_MultipleInstanceTA
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
