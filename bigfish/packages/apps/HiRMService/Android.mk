LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
#LOCAL_STATIC_JAVA_LIBRARIES := android-commonamv

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := HiRMService
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

LOCAL_CERTIFICATE := platform

LOCAL_OVERRIDES_PACKAGES := platform

LOCAL_STATIC_JAVA_LIBRARIES += NetShare
LOCAL_STATIC_JAVA_LIBRARIES += HiAoService
LOCAL_STATIC_JAVA_LIBRARIES += SDKInvoke
LOCAL_STATIC_JAVA_LIBRARIES += DisplaySetting
LOCAL_STATIC_JAVA_LIBRARIES += HiSysManager
LOCAL_PROGUARD_ENABLED := disabled

#LOCAL_PROGUARD_FLAGS := -include $(LOCAL_PATH)/proguard.flags

include $(BUILD_PACKAGE)

# Use the folloing include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))
