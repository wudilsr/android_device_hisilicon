LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES := main.c
LOCAL_SRC_FILES += vinput_interface/android_vinput_inter.c
LOCAL_SRC_FILES += driver_interface/keyled.c
LOCAL_SRC_FILES += key_pars/key_pars.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/driver_interface \
                    $(LOCAL_PATH)/key_pars \
                    $(LOCAL_PATH)/vinput_interface \
                    $(TOP)/external/libxml2/include \
                    $(TOP)/external/icu4c/common \
                    $(MSP_DRV_INCLUDE) \
                    $(MSP_UNF_INCLUDE) \
                    $(COMMON_UNF_INCLUDE)

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SHARED_LIBRARIES :=libutils libicuuc libhi_common libhi_msp
LOCAL_STATIC_LIBRARIES :=libxml2
LOCAL_MODULE:= frontPanel
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
#LOCAL_MODULE_PATH:= $(LOCAL_PATH)
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:=key_pars/frontPanel.xml
LOCAL_MODULE:= frontPanel.xml
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_ETC)
include $(BUILD_PREBUILT)
