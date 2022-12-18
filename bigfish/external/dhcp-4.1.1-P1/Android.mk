LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES :=  \
					$(sort $(call all-c-files-under, common))
LOCAL_C_INCLUDES := \
					$(LOCAL_PATH)/includes
LOCAL_CFLAGS := \
				-DLOCALSTATEDIR=\"/data/misc/dhcp/dhclient6.leases\" \
				-D__clang__ \
				-U_FORTIFY_SOURCE \
				-D__linux
LOCAL_MODULE = libdhcp
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES := libc libcutils
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES :=  \
					$(sort $(call all-c-files-under, minires))
LOCAL_C_INCLUDES := \
					$(LOCAL_PATH)/includes
LOCAL_CFLAGS := \
				-DMINIRES_LIB \
				-DHMAC_MD5
LOCAL_MODULE = libres
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES := libc libcutils
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES :=  \
					$(sort $(call all-c-files-under, dst))
LOCAL_C_INCLUDES := \
					$(LOCAL_PATH)/includes
LOCAL_CFLAGS := \
				-DMINIRES_LIB \
				-DHMAC_MD5
LOCAL_MODULE = libdst
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES := libc libcutils
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES :=  \
					$(sort $(call all-c-files-under, omapip))
LOCAL_C_INCLUDES := \
					$(LOCAL_PATH)/includes
LOCAL_CFLAGS := \
				-DHAVE_CONFIG_H
LOCAL_MODULE = libomapi
LOCAL_MODULE_TAGS = optional
LOCAL_SHARED_LIBRARIES := libc libcutils
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES :=  \
					client/dhclient.c \
					client/clparse.c \
					client/dhc6.c
#					$(sort $(call all-c-files-under, omapip)) \
					$(sort $(call all-c-files-under, dst)) \
					$(sort $(call all-c-files-under, minires)) \
					$(sort $(call all-c-files-under, common))
LOCAL_C_INCLUDES := \
					$(LOCAL_PATH)/includes
LOCAL_CFLAGS := \
				-DHAVE_CONFIG_H \
				-D_PATH_DHCLIENT_SCRIPT=\"/system/etc/dhclient-script\" \
				-DCLIENT_PATH=\"/system/bin\" \
				-D_PATH_DHCLIENT6_PID=\"/data/misc/dhcp/dhclient6.pid\" \
				-DLOCALSTATEDIR=\"/data/misc/dhcp/dhclient6.leases\"
LOCAL_MODULE = dhclient
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS = optional
LOCAL_STATIC_LIBRARIES := libdhcp libres libomapi libdst
LOCAL_SHARED_LIBRARIES :=libc libcutils
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_MODULE := dhclient-script
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc
LOCAL_SRC_FILES :=  client/scripts/dhclient-script
include $(BUILD_PREBUILT)
