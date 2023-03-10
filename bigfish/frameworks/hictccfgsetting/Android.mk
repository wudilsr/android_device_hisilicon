LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call find-other-java-files,com)
LOCAL_NO_STANDARD_LIBRARIES := true
LOCAL_JAVA_LIBRARIES := framework core ext

LOCAL_MODULE_TAGS := optional


LOCAL_MODULE := CTCCfgSetting
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := JAVA_LIBRARIES
LOCAL_STATIC_JAVA_LIBRARIES += HiAoService
LOCAL_STATIC_JAVA_LIBRARIES += DisplaySetting
LOCAL_STATIC_JAVA_LIBRARIES += HiSysManager

include $(BUILD_STATIC_JAVA_LIBRARY)
include $(CLEAR_VARS)
include $(BUILD_MULTI_PREBUILT)
include $(call all-makefiles-under,$(LOCAL_PATH))
