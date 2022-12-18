LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_JAVA_LIBRARIES := HiErrorReport-activation
LOCAL_STATIC_JAVA_LIBRARIES += HiErrorReport-additionnal
LOCAL_STATIC_JAVA_LIBRARIES += HiErrorReport-android-support-v4
LOCAL_STATIC_JAVA_LIBRARIES += HiErrorReport-mail
LOCAL_STATIC_JAVA_LIBRARIES += HiErrorReport-zip4j_1.3.1
LOCAL_STATIC_JAVA_LIBRARIES += HiErrorReport-smtp-1.4.5

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_JNI_SHARED_LIBRARIES := libandroid_runtime

LOCAL_PACKAGE_NAME := HiErrorReport

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_STATIC_JAVA_LIBRARIES += HiSysManager
LOCAL_CERTIFICATE := platform

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)

include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := HiErrorReport-activation:libs/activation.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiErrorReport-additionnal:libs/additionnal.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiErrorReport-android-support-v4:libs/android-support-v4.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiErrorReport-mail:libs/mail.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiErrorReport-zip4j_1.3.1:libs/zip4j_1.3.1.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiErrorReport-smtp-1.4.5:libs/smtp-1.4.5.jar
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

include $(call all-makefiles-under,$(LOCAL_PATH))
