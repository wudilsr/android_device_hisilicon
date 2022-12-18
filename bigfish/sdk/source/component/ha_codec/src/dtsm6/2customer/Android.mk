LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE:= libdtshd_decoder_wrap

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -DANDROID_NDK

LOCAL_CFLAGS += -g3 -O2  -c -D__LINUX_ARM_ARCH__=5 -march=armv5te -mtune=arm9tdmi -mlittle-endian 

LOCAL_ARM_MODE := arm

LOCAL_LDFLAGS := -Wl,--no-fatal-warnings
LOCAL_LDFLAGS += $(LOCAL_PATH)/lib/libdtshd-decoder.a


LOCAL_C_INCLUDES := \
				 $(LOCAL_PATH) \
				 $(LOCAL_PATH)/include

					
LOCAL_SRC_FILES := libdtshd_wrap.c


LOCAL_SHARED_LIBRARIES := \
	libutils\
	libcutils


LOCAL_PRELINK_MODULE := false

include $(BUILD_SHARED_LIBRARY)

