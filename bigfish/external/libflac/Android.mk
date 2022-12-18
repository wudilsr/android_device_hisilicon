LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libflac_ex
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_CFLAGS += -DANDROID_VERSION -DHAVE_LROUND
LOCAL_SHARED_LIBRARIES := liblog libutils libdl $(common_SHARED_LIBRARIES) libicuuc
#LOCAL_STATIC_LIBRARIES := libxml2

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/include \
    $(LOCAL_PATH)/src/libFLAC/include/

LOCAL_MODULE_TAGS:= eng
LOCAL_SRC_FILES := src/libFLAC/bitmath.c \
		src/libFLAC/bitreader.c \
		src/libFLAC/bitwriter.c \
		src/libFLAC/cpu.c \
		src/libFLAC/crc.c \
		src/libFLAC/fixed.c \
		src/libFLAC/float.c \
		src/libFLAC/format.c \
		src/libFLAC/lpc.c \
		src/libFLAC/md5.c \
		src/libFLAC/memory.c \
		src/libFLAC/metadata_iterators.c \
		src/libFLAC/metadata_object.c \
		src/libFLAC/stream_decoder.c \
		src/libFLAC/stream_encoder.c \
		src/libFLAC/stream_encoder_framing.c \
		src/libFLAC/window.c

include $(BUILD_SHARED_LIBRARY)

