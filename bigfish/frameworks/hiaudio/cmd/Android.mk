LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
          main_hiaoservice.cpp
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
          libbinder\
          libhiaoservice\
          libutils\
          libhardware_legacy \
          libhi_common \
          libhi_msp \
          liblog

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../libs \
                    $(LOCAL_PATH)/../../../sdk/source/common/include\
                    $(LOCAL_PATH)/../../../sdk/source/msp/include \
                    $(LOCAL_PATH)/../../../sdk/source/msp/api/include\
                    $(LOCAL_PATH)/../../../sdk/source/msp/drv/include
LOCAL_MODULE := hiaoservice
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
include $(BUILD_EXECUTABLE)
