LOCAL_PATH := $(call my-dir)

# libbt-rtk_virtual_hid.a
include $(CLEAR_VARS)

LOCAL_SRC_FILES := virtual_hid/rtkbt_virtual_hid.c

LOCAL_C_INCLUDES := $(rtk_local_C_INCLUDES)

LOCAL_CFLAGS += $(rtk_local_CFLAGS)

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libc
LOCAL_MODULE := libbt-rtk_virtual_hid

include $(BUILD_STATIC_LIBRARY)

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_VR),true)
include $(CLEAR_VARS)
# libbt-rtk_vr.a
LOCAL_SRC_FILES:= \
        rtk_adpcm_voice.c \
        rtk_msbc_voice.c \
        rtkbt_ifly_voice.c \
        ../codecs/msbc/sbc.c \
        ../adpcm/libadpcm.c \
        ../adpcm/dvi_adpcm.c

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../include \
        $(LOCAL_PATH)/../codecs/msbc \
        $(LOCAL_PATH)/../adpcm \
        $(rtk_local_C_INCLUDES)

LOCAL_CFLAGS += $(rtk_local_CFLAGS) -Wno-error=unused-parameter

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libc
LOCAL_MODULE:= libbt-rtk_vr

include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_SCO),true)
# libbt-rtk_ui.a
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        btui/btui.c \
        ../codecs/msbc/sbc.c

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../codecs/msbc \
        $(LOCAL_PATH)/../include \
        $(rtk_local_C_INCLUDES)

LOCAL_CFLAGS += $(rtk_local_CFLAGS)

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libc
LOCAL_MODULE := libbt-rtk_ui

include $(BUILD_STATIC_LIBRARY)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_AUTOPAIR),true)
# libbt-rtk_autopair.a
include $(CLEAR_VARS)

LOCAL_SRC_FILES := autopair/rtk_autopair.c

LOCAL_C_INCLUDES := $(rtk_local_C_INCLUDES)

LOCAL_CFLAGS += $(rtk_local_CFLAGS)

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := libcutils libc
LOCAL_MODULE := libbt-rtk_autopair

include $(BUILD_STATIC_LIBRARY)
endif

