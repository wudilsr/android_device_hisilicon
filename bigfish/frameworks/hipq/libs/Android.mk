############################## libpqclient #######################################
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES:= \
    PQClient.cpp \
    IPQService.cpp

LOCAL_SHARED_LIBRARIES := \
    libui \
    libutils \
    libcutils \
    libbinder

LOCAL_MODULE := libpqclient
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)

############################# libpqservice #####################################
include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES:= \
    PQService.cpp\
    IPQService.cpp

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
    libbinder \
    libutils\
    libcutils\
	libpqhal

LOCAL_C_INCLUDES := \
					$(LOCAL_PATH)/../../../sdk/source/msp/include \
					$(LOCAL_PATH)/../../../sdk/source/common/include \
					$(LOCAL_PATH)/../hal

LOCAL_MODULE:= libpqservice
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)

