LOCAL_PATH := $(call my-dir)

# Copy HandsetForMultiScreen.apk for GuideView.
include $(CLEAR_VARS)
LOCAL_MODULE := HandsetForMultiScreen
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := HandsetForMultiScreen.apk
LOCAL_MODULE_CLASS := APPS
LOCAL_MODULE_SUFFIX := $(COMMON_ANDROID_PACKAGE_SUFFIX)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(TARGET_OUT)/media/
LOCAL_CERTIFICATE := PRESIGNED
include $(BUILD_PREBUILT)
