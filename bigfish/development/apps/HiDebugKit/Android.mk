ifeq ($(strip $(PRODUCT_TARGET)), demo)
else
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_JNI_SHARED_LIBRARIES := libandroid_runtime

LOCAL_PACKAGE_NAME := HiDebugKit

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_STATIC_JAVA_LIBRARIES += HiSysManager
LOCAL_CERTIFICATE := platform

LOCAL_PROGUARD_ENABLED := disabled

include $(BUILD_PACKAGE)
include $(call all-makefiles-under,$(LOCAL_PATH))
endif
