LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
LOCAL_MODULE    := CTCCfgSetting
LOCAL_SRC_FILES := \
Setting.c \
SettingUtils.c
include $(BUILD_SHARED_LIBRARY)
