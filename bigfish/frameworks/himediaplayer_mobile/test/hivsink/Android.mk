LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES:= \
        ../../hal/HiVSink.cpp \
        HiVSinkTest.cpp \

LOCAL_C_INCLUDES += \
        bionic \
        bionic/libstdc++/include \
        external/gtest/include \
        external/stlport/stlport \
        hardware \
        device/hisilicon/bigfish/hardware/gpu/android/gralloc \
        device/hisilicon/bigfish/frameworks/himediaplayer/hal \
        $(HISI_PLATFORM_PATH)/hidolphin/component/player/include \
        $(COMMON_UNF_INCLUDE)  \

LOCAL_SHARED_LIBRARIES := \
        libcutils libstlport liblog libutils \
        libgui libbinder libui

LOCAL_STATIC_LIBRARIES := \
        libgtest \
        libgtest_main

LOCAL_MODULE:= test-hivsink

LOCAL_MODULE_TAGS := test
include $(BUILD_EXECUTABLE)
