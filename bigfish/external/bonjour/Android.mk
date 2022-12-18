# Bonjour Android.mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE := libbonjour
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_32_BIT_ONLY := true
LOCAL_CFLAGS := -D_GNU_SOURCE -DNOT_HAVE_SA_LEN -DUSES_NETLINK -DHAVE_LINUX -DTARGET_OS_LINUX -fno-strict-aliasing -DMDNS_ONLYSYSTEMTASK=1 -O0 -UNDEBUG -D__ANDROID_LINUX
#LOCAL_CFLAGS += -DMDNS_DEBUGMSGS=2

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/mDNSCore \
		$(LOCAL_PATH)/mDNSHisi \
		$(LOCAL_PATH)/mDNSPosix \
		$(LOCAL_PATH)/mDNSShared


LOCAL_SRC_FILES := \
	mDNSCore/DNSCommon.c \
	mDNSCore/DNSDigest.c \
	mDNSCore/mDNS.c \
	mDNSCore/uDNS.c \
	mDNSHisi/hisidns.c \
	mDNSPosix/mDNSPosix.c \
	mDNSPosix/mDNSUNP.c \
	mDNSShared/GenLinkedList.c \
	mDNSShared/PlatformCommon.c \
	mDNSShared/mDNSDebug.c

#include $(BUILD_SHARED_LIBRARY)
include $(BUILD_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_PRELINK_MODULE := false
#LOCAL_MODULE := Responder
#ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
#LOCAL_MODULE_TAGS := optional
#LOCAL_CFLAGS := -O0 -UNDEBUG
#
#LOCAL_C_INCLUDES += \
#        $(LOCAL_PATH)/mDNSCore \
#		$(LOCAL_PATH)/mDNSPosix \
#		$(LOCAL_PATH)/mDNSShared
#
#LOCAL_SRC_FILES := \
#	mDNSPosix/Responder.c
#
##LOCAL_SHARED_LIBRARIES := libstlport libgabi++ libicuuc
#LOCAL_SHARED_LIBRARIES := libcutils
#LOCAL_STATIC_LIBRARIES := libbonjour
#
#include $(BUILD_EXECUTABLE)
