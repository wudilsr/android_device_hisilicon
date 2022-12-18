LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call find-other-java-files, java)



LOCAL_NO_STANDARD_LIBRARIES := true
LOCAL_JAVA_LIBRARIES := framework core ext
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE := HiDVDInfo
LOCAL_MODULE_CLASS := JAVA_LIBRARIES
LOCAL_PROGUARD_ENABLED := disabled
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_STATIC_JAVA_LIBRARY)

include $(call first-makefiles-under,$(LOCAL_PATH))
