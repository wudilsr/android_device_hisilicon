LOCAL_PATH:= $(call my-dir)
####################################################################################

include $(CLEAR_VARS)

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE:= libhiaoservice
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES:= \
  HiAoService.cpp\
  IHiAoService.cpp
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
  libbinder \
  libutils\
  libcutils\
  libhi_common\
  libhi_msp\
  libmedia

LOCAL_C_INCLUDES :=$(LOCAL_PATH)\
        $(LOCAL_PATH)/../../../sdk/source/common/include\
        $(LOCAL_PATH)/../../../sdk/source/msp/include \
        $(LOCAL_PATH)/../../../sdk/source/msp/api/include\
        $(LOCAL_PATH)/../../../sdk/source/msp/drv/include\
        $(TOP)/framework/av/include/media

include $(BUILD_SHARED_LIBRARY)

###################################################################################

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libhiaoserviceclient
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= \
  HiAoServiceClient.cpp \
  IHiAoService.cpp

LOCAL_SHARED_LIBRARIES := \
  libutils \
  libcutils \
  libbinder
LOCAL_C_INCLUDES :=$(LOCAL_PATH)
include $(BUILD_SHARED_LIBRARY)

####################################################################################

