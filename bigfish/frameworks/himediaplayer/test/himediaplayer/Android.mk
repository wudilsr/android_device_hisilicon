LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES:= \
        HiMediaPlayerTest.cpp \

LOCAL_C_INCLUDES += \
        bionic \
        bionic/libstdc++/include \
        external/gtest/include \
        external/stlport/stlport \
        hardware \
        device/hisilicon/bigfish/hardware/gpu/android/gralloc \
        device/hisilicon/bigfish/frameworks/himediaplayer/hal \

LOCAL_C_INCLUDES += \
    $(SDK_DIR)/source/common/include \
    $(SDK_DIR)/source/component/ha_codec/include \
    $(SDK_DIR)/source/component/subtoutput/include \
    $(SDK_DIR)/source/msp/include \
    $(SDK_DIR)/source/msp/api/include \
    $(SDK_DIR)/source/msp/drv/include \
    $(SDK_DIR)/source/component/subtitle/include/ \
    $(HISI_PLATFORM_PATH)/hidolphin/component/player/include \
    $(HISI_PLATFORM_PATH)/hidolphin/component/charset/include \
    $(HISI_PLATFORM_PATH)/frameworks/hidisplaymanager/libs/ \
    $(HISI_PLATFORM_PATH)/frameworks/hidisplaymanager/hal/ \
    $(TOP)/external/harfbuzz/src     \
    $(TOP)/external/harfbuzz/contrib \
    $(TOP)/external/freetype/include \
    $(TOP)/external/libxml2/include \
    $(TOP)/external/icu4c/common \
    $(TOP)/frameworks/native/include \
    $(TOP)/frameworks/av/include/media \
    $(TOP)/frameworks/av/media/libmedia \
    $(TOP)/external/skia/include/core \

LOCAL_SHARED_LIBRARIES := \
        libcutils libstlport liblog libutils \
        libgui libbinder \
        libhiplayer_adapter

#LOCAL_STATIC_LIBRARIES := \
#        libgtest \
#        libgtest_main

LOCAL_MODULE:= himediaplayer

LOCAL_MODULE_TAGS := test
include $(BUILD_EXECUTABLE)
