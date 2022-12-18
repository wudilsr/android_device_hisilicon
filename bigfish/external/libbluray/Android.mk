LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libbluray_ex
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_CFLAGS += -std=c99 -D_ISOC99_SOURCE -D_POSIX_C_SOURCE=200809L -D_REENTRANT -DHAVE_CONFIG_H -DHI_BLURAY_EXTENSION -DANDROID_VERSION
LOCAL_SHARED_LIBRARIES := libz liblog libutils libdl $(common_SHARED_LIBRARIES) libicuuc
LOCAL_STATIC_LIBRARIES := libxml2

LOCAL_C_INCLUDES :=     \
    $(LOCAL_PATH)       \
    $(LOCAL_PATH)/src   \
    $(LOCAL_PATH)/src/libbluray/bdnav   \
    external/zlib       \
	external/libxml2/include \
	external/icu4c/common \

LOCAL_MODULE_TAGS:= eng
LOCAL_SRC_FILES := src/file/dir_posix.c \
		   src/file/dl_posix.c \
		   src/file/file_posix.c \
		   src/file/filesystem.c \
		   src/libbluray/register.c \
		   src/libbluray/bluray.c \
		   $(sort $(call all-c-files-under, src/hibluray)) \
		   $(sort $(call all-c-files-under, src/libbluray/bdnav)) \
		   $(sort $(call all-c-files-under, src/libbluray/decoders)) \
		   $(sort $(call all-c-files-under, src/libbluray/hdmv)) \
		   $(sort $(call all-c-files-under, src/util))

include $(BUILD_SHARED_LIBRARY)
