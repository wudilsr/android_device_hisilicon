ifeq ($(strip $(PRODUCT_TARGET)), demo)
else
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_STATIC_JAVA_LIBRARIES += DisplaySetting
LOCAL_STATIC_JAVA_LIBRARIES += SampleATC
LOCAL_STATIC_JAVA_LIBRARIES += HiSysManager
LOCAL_CERTIFICATE := platform
LOCAL_PACKAGE_NAME := HardwareTest
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_PROGUARD_FLAG_FILES := proguard.cfg
LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)
endif
