ifeq ($(strip $(PRODUCT_TARGET)), demo)

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional
LOCAL_STATIC_JAVA_LIBRARIES := \
    android-common \
    guava \
    android-support-v13 \
    android-support-v4 \
    static-zxingcore \
    SDKInvoke\

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := HiInstructions

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)

LOCAL_OVERRIDES_PACKAGES := platform
LOCAL_CERTIFICATE := platform

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)

include $(call all-makefiles-under,$(LOCAL_PATH))

include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := static-zxingcore:libs/ZXingCore.jar
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)
endif
