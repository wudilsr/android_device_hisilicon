ifneq (,$(findstring Hi379,$(CHIPNAME)))

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_JAVA_LIBRARIES := HiPQTools-javalib
LOCAL_STATIC_JAVA_LIBRARIES += HiPQTools-android-support-v4
LOCAL_STATIC_JAVA_LIBRARIES += PQSetting

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_JAVA_LIBRARIES :=

LOCAL_JNI_SHARED_LIBRARIES := libandroid_runtime

LOCAL_PACKAGE_NAME := HiPQTools

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

LOCAL_CERTIFICATE := platform

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)

include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := HiPQTools-javalib:libs/javalib.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiPQTools-android-support-v4:libs/android-support-v4.jar

LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

include $(call all-makefiles-under,$(LOCAL_PATH))

endif
