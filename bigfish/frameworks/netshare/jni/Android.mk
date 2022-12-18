LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libnetshare_jni
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -DANDROID_NDK
LOCAL_SRC_FILES := \
	sambaClient.cpp \
	sambaServer.cpp \
	smbtree.cpp \
	Samba.cpp \
	nfsClient.cpp

LOCAL_LDLIBS := -ldl -llog
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) \
					$(LOCAL_PATH) \
					$(LOCAL_PATH)/../libs  \
					external/stlport/stlport \
					bionic

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libutils \
	libbinder \
	libnetshare_client

LOCAL_STATIC_LIBRARIES := libstlport_static

LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
