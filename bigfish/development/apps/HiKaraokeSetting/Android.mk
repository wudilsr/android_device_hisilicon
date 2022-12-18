LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_JAVA_LIBRARIES := HiKaraokTools-javalib
LOCAL_STATIC_JAVA_LIBRARIES += HiKaraokTools-android-support-v4

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_JAVA_LIBRARIES :=

LOCAL_JNI_SHARED_LIBRARIES := libandroid_runtime

LOCAL_PACKAGE_NAME := HiKaraokTools

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

LOCAL_CERTIFICATE := platform

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)

include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := HiKaraokTools-javalib:libs/javalib.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiKaraokTools-android-support-v4:libs/android-support-v4.jar

LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)
