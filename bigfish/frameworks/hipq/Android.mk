LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call find-other-java-files, java)
LOCAL_SRC_FILES += java/com/hisilicon/android/IPQManager.aidl

LOCAL_NO_STANDARD_LIBRARIES := true
LOCAL_JAVA_LIBRARIES := framework
LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := PQSetting
LOCAL_PROGUARD_ENABLED := disabled

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := JAVA_LIBRARIES
include $(BUILD_STATIC_JAVA_LIBRARY)

include $(call first-makefiles-under,$(LOCAL_PATH))
