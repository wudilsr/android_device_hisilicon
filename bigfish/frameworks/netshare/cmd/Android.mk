LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
          main_netshare.cpp
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
          libbinder\
          libnetshare_service\
          libutils\
          liblog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libs
LOCAL_MODULE := netshared
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_EXECUTABLE)
