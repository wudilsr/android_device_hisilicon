LOCAL_PATH := $(call my-dir)

###############################################
## libsysmanager jni
###############################################
include $(CLEAR_VARS)

LOCAL_MODULE := libsysmangerservice_jni
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -DANDROID_NDK
LOCAL_SRC_FILES := \
  com_hisilicon_android_hisysmanagerservice.cpp
LOCAL_LDLIBS := -ldl -llog
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) \
$(LOCAL_PATH)/../libs
LOCAL_SHARED_LIBRARIES := \
  libandroid_runtime \
  libbinder \
  libutils \
  libcutils \
  libhisysmanagerclient
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

###############################################
