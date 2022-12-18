LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
ifeq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
LOCAL_32_BIT_ONLY :=true
endif

LOCAL_SRC_FILES := $(call all-java-files-under, ./)

LOCAL_JAVA_LIBRARIES := framework core ext

LOCAL_MODULE := SvrLog

ifneq (5.,$(findstring 5.,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif

LOCAL_MODULE_TAGS := optional

#LOCAL_JAVA_RESOURCE_DIRS := core/res pregenerated/res

#LOCAL_NO_EMMA_INSTRUMENT := true

LOCAL_PROGUARD_ENABLED := disabled


include $(BUILD_STATIC_JAVA_LIBRARY)
