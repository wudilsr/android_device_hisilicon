ifeq ($(TARGET_ARCH),arm)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= \
            pppoe.c \
            ppp.c \
            common.c \
            discovery.c \
            debug.c \
            if.c

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH) \
        $(LOCAL_PATH)/libevent/

LOCAL_CFLAGS := -g '-DVERSION=3.11'  '-DPPPOE_PATH="/system/bin/pppoe"' '-DPPPD_PATH="/system/bin/pppd"'

LOCAL_MODULE := pppoe

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_EXECUTABLE)

endif
