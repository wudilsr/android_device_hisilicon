LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

HIDOLPHIN_PATH ?= $(HISI_PLATFORM_PATH)/hidolphin
PLAYER_PATH ?= $(HIDOLPHIN_PATH)/component/player_stb

LOCAL_CFLAGS += -DUNIT_TEST

LOCAL_C_INCLUDES += \
        bionic \
        bionic/libstdc++/include \
        external/gtest/include \
        external/stlport/stlport \
        $(PLAYER_PATH)/include \
        $(COMMON_UNF_INCLUDE)

LOCAL_SRC_FILES:= \
        LogTest.cpp \

LOCAL_SHARED_LIBRARIES := \
        libcutils libstlport libutils libhiplayer_utils

LOCAL_STATIC_LIBRARIES := \
        libgtest \
        libgtest_main

LOCAL_MODULE:= test-log

LOCAL_MODULE_TAGS := test

include $(BUILD_EXECUTABLE)
