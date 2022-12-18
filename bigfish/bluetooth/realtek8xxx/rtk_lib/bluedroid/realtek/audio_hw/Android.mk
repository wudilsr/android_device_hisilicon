LOCAL_PATH := $(call my-dir)


ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_VR),true)
# audio.vohog.default.so
include $(CLEAR_VARS)

LOCAL_SRC_FILES := audio_vohog_hw.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_SHARED_LIBRARIES := liblog libcutils

LOCAL_MODULE := audio.vohog.default

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_MODULE_TAGS := optional

#LOCAL_CFLAGS += $(rtk_local_CFLAGS) -Wno-unused-parameter

LOCAL_REQUIRED_MODULES := rtkbt.feature.vr.xml

include $(BUILD_SHARED_LIBRARY)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_SCO),true)
# audio.sco.default.so
include $(CLEAR_VARS)

LOCAL_SRC_FILES := audio_sco_hw.c

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include/

LOCAL_SHARED_LIBRARIES := liblog libcutils

LOCAL_MODULE := audio.sco.default

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += $(rtk_local_CFLAGS) -Wno-unused-parameter

include $(BUILD_SHARED_LIBRARY)
endif

