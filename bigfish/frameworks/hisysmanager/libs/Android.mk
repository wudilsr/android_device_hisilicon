LOCAL_PATH:= $(call my-dir)
####################################################################################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE:= libhisysmanagerservice
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES:= \
    HiSysManagerService.cpp \
    IHiSysManagerService.cpp \
    sysmanager.c \
    mtdutils.c \
    hiRecovery.c \
    flashInfo.c \
    hinetutils.c
LOCAL_MODULE_TAGS := optional
LOCAL_SHARED_LIBRARIES := \
    libsysmanager_chipio    \
    libbinder \
    libutils\
    libcutils\
    libui\
    libnetutils \
    libhi_common \
    libhi_msp \
    libskia \
    libhi_sample_common

LOCAL_C_INCLUDES := \
    $(TOP)/framework/native/services/surfaceflinger \
    $(TOP)/hardware/libhardware/include \
    $(TOP)/hardware/libhardware/include/hardware \
    $(TOP)/hardware/libhardware/modules/gralloc \
LOCAL_C_INCLUDES := \
    $(TOP)/device/hisilicon/bigfish/sdk/source/common/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/common/api/flash/include \
    $(TOP)/device/hisilicon/bigfish/sdk/source/msp/include\
    $(TOP)/device/hisilicon/bigfish/sdk/source/msp/api/higo/include \
    $(TOP)/external/skia/include/core
ifeq ($(VMX_ADVANCED_SUPPORT),true)
LOCAL_CFLAGS += -DVMX_ADVANCED_SUPPORT
LOCAL_SHARED_LIBRARIES += \
    libhiloader
LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/component/loader/api/include
endif

LOCAL_C_INCLUDES += $(TOP)/device/hisilicon/bigfish/sdk/source/msp/drv/hifb/include \
                    $(TOP)/device/hisilicon/bigfish/sdk/sample/common

include $(BUILD_SHARED_LIBRARY)

###################################################################################

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libhisysmanagerclient
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES:= \
    HiSysManagerClient.cpp \
    IHiSysManagerService.cpp

LOCAL_SHARED_LIBRARIES := \
    libui \
    libutils \
    libcutils \
    libbinder
LOCAL_C_INCLUDES :=$(LOCAL_PATH)
include $(BUILD_SHARED_LIBRARY)

####################################################################################
