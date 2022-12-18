LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libhi_netutils
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -DANDROID_NDK
LOCAL_SRC_FILES := \
    com_hisilicon_android_networkutils.cpp
LOCAL_LDLIBS := -ldl -llog
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) \
$(LOCAL_PATH)/../libs
LOCAL_SHARED_LIBRARIES := \
  libandroid_runtime \
  libbinder \
  libutils \
  libcutils \
  libnetutils
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)
