LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
ifeq (5.0,$(findstring 5.0,$(PLATFORM_VERSION)))
LOCAL_32_BIT_ONLY :=true
endif

LOCAL_MODULE_TAGS := optional


LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := sample_log

LOCAL_STATIC_JAVA_LIBRARIES := SvrLog

ifeq (4.2,$(findstring 4.2,$(PLATFORM_VERSION)))
LOCAL_STATIC_JAVA_LIBRARIES += HiMediaPlayer
endif

LOCAL_CERTIFICATE := platform

LOCAL_OVERRIDES_PACKAGES := platform

LOCAL_PROGUARD_ENABLED := disabled

ifneq (5.0,$(findstring 5.0,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
endif


include $(BUILD_PACKAGE)
