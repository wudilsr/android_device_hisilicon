LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libxbmc_adapter

LOCAL_C_INCLUDES +=  \
    $(SDK_DIR)/source/common/include \
    $(SDK_DIR)/source/component/subtoutput/include \
    $(SDK_DIR)/source/msp/include \
    $(HISI_PLATFORM_PATH)/hidolphin/component/player/include \
    $(HISI_PLATFORM_PATH)/frameworks/netshare/libs/ \
    $(HISI_PLATFORM_PATH)/frameworks/himediaplayer/hal \
    $(TOP)/external/freetype/include \
    $(TOP)/external/harfbuzz/src     \
    $(TOP)/external/harfbuzz/contrib \
    $(TOP)/external/libxml2/include \
    $(TOP)/external/icu4c/common \
    $(TOP)/frameworks/av/include/media \
    $(TOP)/frameworks/av/media/libmedia \

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES += \
    IHiPlayer.cpp

LOCAL_STATIC_LIBRARIES := libnetshare_client

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libcutils \
    libutils \
    libplayer \
    libhiplayer_adapter \

include $(BUILD_SHARED_LIBRARY)