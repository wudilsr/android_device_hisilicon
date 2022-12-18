LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libhimediaplayer_jni
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
BUILD_BD := true

LOCAL_C_INCLUDES := \
    $(JNI_H_INCLUDE) \
    $(call include-path-for, graphics corecg) \
    $(TOP)/frameworks/base/core/jni \
    $(TOP)/device/hisilicon/bigfish/hidolphin/component/player_mobile/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/common/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/component/ha_codec/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/component/subtoutput/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/msp/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/msp/api/include \
    $(TOP)/external/freetype/include \
    $(TOP)/external/harfbuzz/src \
    $(TOP)/external/harfbuzz/contrib \
    $(TOP)/external/libxml2/include \
    $(TOP)/external/icu4c/common \
    $(TOP)/frameworks/native/include/ \
    $(TOP)/frameworks/av/include/media/ \
    $(TOP)/frameworks/av/media/libmedia \

LOCAL_C_INCLUDES += bionic
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../hal

LOCAL_SRC_FILES := com_hisilicon_android_mediaplayer_himediaplayer.cpp \
       HiMediaPlayerManage.cpp

LOCAL_SHARED_LIBRARIES := libandroid_runtime \
              libnativehelper \
              libutils \
              libcutils \
              libbinder \
              libhiplayer_adapter \

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
