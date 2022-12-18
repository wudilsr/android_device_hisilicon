LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-subdir-java-files) \
    src/com/android/smart/terminal/iptv/aidl/ServiceSettingsInfoAidl.aidl

LOCAL_STATIC_JAVA_LIBRARIES := HiAoService
LOCAL_STATIC_JAVA_LIBRARIES += DisplaySetting
LOCAL_STATIC_JAVA_LIBRARIES += HiSysManager

LOCAL_PACKAGE_NAME := ServiceSettings
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_CERTIFICATE := platform
LOCAL_PROGUARD_ENABLED := disabled
include $(BUILD_PACKAGE)

