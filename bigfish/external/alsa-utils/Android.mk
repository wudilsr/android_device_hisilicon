
#ifeq ($(strip $(BOARD_USES_ALSA_AUDIO)),true)
#ifeq ($(strip $(BUILD_WITH_ALSA_UTILS)),true)

LOCAL_PATH:= $(call my-dir)

#
# Build aplay command
#

include $(CLEAR_VARS)

LOCAL_CFLAGS := \
	-fPIC -D_POSIX_SOURCE \
	-DALSA_CONFIG_DIR=\"/system/usr/share/alsa\" \
	-DALSA_PLUGIN_DIR=\"/system/usr/lib/alsa-lib\" \
	-DALSA_DEVICE_DIRECTORY=\"/dev/snd/\"

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH)/include \
	$(LOCAL_PATH)/android \
	$(HISI_PLATFORM_PATH)/external/alsa-lib/include

LOCAL_SRC_FILES := \
	aplay/aplay.c

LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := alsa_aplay
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
#LOCAL_MODULE_TAGS := eng
LOCAL_SHARED_LIBRARIES := \
	libasound \
	libc

include $(BUILD_EXECUTABLE)
