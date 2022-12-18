LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := \
         $(call all-subdir-java-files)

LOCAL_PACKAGE_NAME := HiPinyinIME
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_PROGUARD_ENABLED := disabled

LOCAL_JNI_SHARED_LIBRARIES := libjni_remoteime

LOCAL_STATIC_JAVA_LIBRARIES := com.hisilicon.android.inputmethod.remote.lib


LOCAL_CERTIFICATE := shared
LOCAL_REQUIRED_MODULES := libjni_remoteime
# Make sure our dictionary file is not compressed, so we can read it with
# a raw file descriptor.
LOCAL_AAPT_FLAGS := -0 .dat


include $(BUILD_PACKAGE)

MY_PATH := $(LOCAL_PATH)
include $(MY_PATH)/jni/Android.mk
include $(MY_PATH)/lib/Android.mk
