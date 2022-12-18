LOCAL_PATH := $(call my-dir)

ifneq ($(BOARD_HAVE_BLUETOOTH_RTK_SOURCECODE),true)

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_AUTOPAIR),true)
include $(CLEAR_VARS)
LOCAL_MODULE    := BluetoothRTKAutoPairService
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES := BluetoothRTKAutoPairService.apk
LOCAL_CERTIFICATE := platform
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := APPS
include $(BUILD_PREBUILT) 
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_3DD),true)
include $(CLEAR_VARS)
LOCAL_MODULE    := Bluetooth3ddService
LOCAL_MODULE_SUFFIX := .apk
LOCAL_SRC_FILES := Bluetooth3ddService.apk
LOCAL_CERTIFICATE := platform
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := APPS
LOCAL_REQUIRED_MODULES := rtkbt.feature.3dd.xml
include $(BUILD_PREBUILT) 
endif

endif


