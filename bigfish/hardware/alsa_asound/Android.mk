# hardware/libaudio-alsa/Android.mk
#
# Copyright 2008 Wind River Systems
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS := -D_POSIX_SOURCE

LOCAL_C_INCLUDES += $(HISI_PLATFORM_PATH)/external/alsa-lib/include
LOCAL_C_INCLUDES += hardware/libhardware_legacy/include

LOCAL_SRC_FILES := \
      AudioHardwareALSA.cpp \
      AudioStreamOutALSA.cpp \
      AudioStreamInALSA.cpp \
      ALSAStreamOps.cpp \
      ALSAMixer.cpp \
      ALSAControl.cpp
LOCAL_MODULE := audio.primary.bigfish
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE_TAGS := optional
LOCAL_STATIC_LIBRARIES := libmedia_helper
LOCAL_WHOLE_STATIC_LIBRARIES := libaudiohw_legacy
LOCAL_SHARED_LIBRARIES := \
  libcutils \
  libutils \
  libmedia \
  libhardware \
  libhardware_legacy \
  libasound
include $(BUILD_SHARED_LIBRARY)
#
#alsa.default.so
#
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_CFLAGS := -D_POSIX_SOURCE -Wno-multichar
LOCAL_C_INCLUDES += $(HISI_PLATFORM_PATH)/external/alsa-lib/include
LOCAL_SRC_FILES:= alsa_default.cpp
LOCAL_SHARED_LIBRARIES := \
	libasound	\
	libcutils	\
	liblog
LOCAL_MODULE := alsa.default
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
include $(BUILD_SHARED_LIBRARY)
