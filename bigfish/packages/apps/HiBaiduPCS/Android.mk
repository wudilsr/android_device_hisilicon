ifeq ($(strip $(PRODUCT_TARGET)), demo)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_JAVA_LIBRARIES := HiBaiduPCS-Baidu-OAuth-SDK
LOCAL_STATIC_JAVA_LIBRARIES += HiBaiduPCS-Baidu-PCS-SDK
LOCAL_STATIC_JAVA_LIBRARIES += HiBaiduPCS-httpmime
LOCAL_STATIC_JAVA_LIBRARIES += HiBaiduPCS-android-support-v4

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_PACKAGE_NAME := HiBaiduPCS

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)



include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := HiBaiduPCS-Baidu-OAuth-SDK:libs/Baidu-OAuth-SDK-Android-G-2.0.0.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiBaiduPCS-Baidu-PCS-SDK:libs/Baidu-PCS-SDK-Android-L2-2.1.0.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiBaiduPCS-httpmime:libs/httpmime-4.2.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += HiBaiduPCS-android-support-v4:libs/android-support-v4.jar

LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

include $(call all-makefiles-under,$(LOCAL_PATH))
endif
