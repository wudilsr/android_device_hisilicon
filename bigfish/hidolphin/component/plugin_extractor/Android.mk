LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libextrator_adp
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_CFLAGS += -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION)
LOCAL_CFLAGS += -DANDROID_VERSION

LOCAL_SRC_FILES +=  \
    extrator_adp/svr_extrator_adp.cpp

LOCAL_SHARED_LIBRARIES :=       \
    libbinder                   \
    libcutils                   \
    libdl                       \
    libgui                      \
    libmedia                    \
    libutils                    \
    libstagefright              \
    libdrmframework             \
    libhi_common                \
    libstagefright_foundation   \

LOCAL_C_INCLUDES +=         \
    $(LOCAL_PATH)/extrator_adp \
    $(TOP)/frameworks/av/include/media \
    $(TOP)/frameworks/av/include/drm \
    $(TOP)/frameworks/av/media/libstagefright \
    $(TOP)/frameworks/native/include/media/openmax \
    $(TOP)/external/freetype/include \
    $(TOP)/external/libxml2/include \
    $(TOP)/external/icu4c/common \
    $(TOP)/frameworks/native/include \
    $(TOP)/$(SDK_DIR)/source/common/include \
    $(TOP)/external/skia/include/core \
    $(TOP)/device/hisilicon/bigfish/hidolphin/component/player/include


HISMOOTHSTREAMINGPLAYER_DRM_ENABLE := true
ifeq ($(HISMOOTHSTREAMINGPLAYER_DRM_ENABLE),true)
LOCAL_CFLAGS += -DHISMOOTHSTREAMINGPLAYER_DRM_ENABLE

LOCAL_C_INCLUDES +=  \
        $(TOP)/device/hisilicon/bigfish/hidolphin/component/smoothstreaming/inc \
        $(TOP)/$(SDK_DIR)/source/msp/include \

LOCAL_SHARED_LIBRARIES += \
        libhi_smoothstreaming
endif

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

#################################extractor_demux###################################
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := libextrator_demux
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif

LOCAL_SRC_FILES +=  \
    demux/svr_extractor.c

LOCAL_SHARED_LIBRARIES :=       \
    libbinder                   \
    libcutils                   \
    libdl                       \
    libgui                      \
    libmedia                    \
    libutils                    \
    libstagefright              \
    libextrator_adp

LOCAL_C_INCLUDES +=         \
    $(LOCAL_PATH)/extrator_adp \
    $(TOP)/device/hisilicon/bigfish/hidolphin/component/player/include

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

#################################test_extractor####################################
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := sample_test_extractor
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_SRC_FILES := sample_test.c
LOCAL_SHARED_LIBRARIES :=       \
    libextrator_adp

LOCAL_C_INCLUDES +=         \
    $(LOCAL_PATH)/extrator_adp \
    $(TOP)/frameworks/av/include/media \
    $(TOP)/external/freetype/include \
    $(TOP)/external/libxml2/include \
    $(TOP)/external/icu4c/common \
    $(TOP)/frameworks/native/include \
    $(TOP)/external/skia/include/core \
    $(TOP)/device/hisilicon/bigfish/hidolphin/component/player/include

include $(BUILD_EXECUTABLE)
