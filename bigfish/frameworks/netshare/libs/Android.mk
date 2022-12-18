LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE:= libnetshare_service
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_SRC_FILES:= \
	HiNSService.cpp\
	IHiNSService.cpp

LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
	libbinder \
	libutils \
	libcutils \
	libNSShare

LOCAL_C_INCLUDES :=$(LOCAL_PATH) \
	$(LOCAL_PATH)/../hal

include $(BUILD_SHARED_LIBRARY)

####################################################################################

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libnetshare_client
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES:= \
	HiNSClient.cpp \
	IHiNSService.cpp

LOCAL_SHARED_LIBRARIES := \
	libutils \
	libcutils \
	libbinder

LOCAL_C_INCLUDES :=$(LOCAL_PATH)
include $(BUILD_SHARED_LIBRARY)

