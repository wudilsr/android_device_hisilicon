LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../libs


LOCAL_SHARED_LIBRARIES := \
    libnetutils \
	libcutils \
    libhi_msp

LOCAL_SRC_FILES:= \
	netShareHal.cpp


LOCAL_MODULE:= libNSShare
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)
