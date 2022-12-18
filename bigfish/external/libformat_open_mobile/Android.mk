LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

ifeq ($(PRODUCT_TARGET),shcmcc)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libformat_open
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../ffmpeg_mobile \
    $(LOCAL_PATH)/../ffmpeg_mobile/libavformat \
    $(LOCAL_PATH)/../ffmpeg_mobile/libavutil \
    $(LOCAL_PATH)/../libudf \
    $(LOCAL_PATH)/../libclientadp

LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := $(CFG_CFLAGS)
LOCAL_CFLAGS += -DANDROID_VERSION
LOCAL_LDFLAGS += -ldl
LOCAL_SHARED_LIBRARIES := libutils liblog libcutils libavformat libavutil libavcodec libclientadp
LOCAL_SRC_FILES := \
    svr_iso_dec.c \
    svr_udf_protocol.c \
    svr_allformat.c \
    hls.c \
    hls_read.c \
    hls_key_decrypt.c \
    http.c \
    tcp.c

include $(BUILD_SHARED_LIBRARY)
endif
