###############################################################################
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := InfraredClient.cpp \
                   InfraredService.cpp \
                   IInfraredInterface.cpp

LOCAL_SHARED_LIBRARIES := libui libutils libcutils libbinder libandroid_runtime
LOCAL_MODULE_TAGS := eng
LOCAL_MODULE := libinfrared
LOCAL_MODULE_TAGS := optional
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_SHARED_LIBRARY)

###############################################################################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
LOCAL_SRC_FILES := ir_user.cpp \
                   InfraredService.cpp \
                   IInfraredInterface.cpp

ifeq ($(strip $(CFG_HI_IR_TYPE_STD)),y)
LOCAL_SRC_FILES += ir_interface/android_ir_inter_std.c
endif

ifeq ($(strip $(CFG_HI_IR_TYPE_S2)),y)
LOCAL_SRC_FILES += ir_interface/android_ir_inter.c
endif



LOCAL_SRC_FILES += vinput_interface/android_vinput_inter.c
LOCAL_SRC_FILES += key_pars/key_pars.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/ \
                    $(LOCAL_PATH)/ir_interface \
                    $(LOCAL_PATH)/key_pars \
                    $(LOCAL_PATH)/vinput_interface \
                    $(TOP)/external/libxml2/include \
                    $(TOP)/external/icu4c/common \
                    $(MSP_DRV_INCLUDE) \
                    $(MSP_UNF_INCLUDE) \
                    $(COMMON_UNF_INCLUDE)

LOCAL_CFLAGS := $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_CFLAGS += -D$(CHIPNAME)
LOCAL_SHARED_LIBRARIES := libutils libicuuc libcutils libbinder
LOCAL_SHARED_LIBRARIES += libhi_common libhi_msp
LOCAL_STATIC_LIBRARIES := libxml2
LOCAL_MODULE := android_ir_user
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_PM_POWERUP_MODE1_SUPPORT),y)
LOCAL_CFLAGS += -DMCU
endif
#LOCAL_MODULE_PATH := $(LOCAL_PATH)
include $(BUILD_EXECUTABLE)
###############################################################################

###############################################################################
include $(CLEAR_VARS)
LOCAL_SRC_FILES := key_pars/key.xml
LOCAL_MODULE := key.xml
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_PATH := $(TARGET_OUT_ETC)
include $(BUILD_PREBUILT)
###############################################################################
