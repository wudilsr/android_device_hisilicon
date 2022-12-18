LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(sort $(call all-c-files-under))
LOCAL_SRC_FILES += com_hisilicon_android_networkupgrade_activity_BuildNumber.cpp

LOCAL_C_INCLUDES := \
	$(TOP)/device/hisilicon/bigfish/sdk/source/common/include \
	$(TOP)/device/hisilicon/bigfish/sdk/source/common/api/flash/include


LOCAL_SHARED_LIBRARIES := \
	libcutils \
	libhi_common

LOCAL_MODULE := libSDKVersion

include $(BUILD_SHARED_LIBRARY)
