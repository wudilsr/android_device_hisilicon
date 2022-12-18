LOCAL_PATH := $(call my-dir)

include $(SDK_DIR)/Android.def

ifeq ($(CFG_HI_VP_SUPPORT),y)
ifeq ($(CFG_HI_VOIP_SUPPORT),y)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call find-other-java-files, java)

LOCAL_NO_STANDARD_LIBRARIES := true
LOCAL_JAVA_LIBRARIES := framework core ext
LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := PhonePlayer
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := JAVA_LIBRARIES
LOCAL_PROGUARD_ENABLED := disabled
include $(BUILD_STATIC_JAVA_LIBRARY)

include $(CLEAR_VARS)
include $(BUILD_MULTI_PREBUILT)

include $(call first-makefiles-under,$(LOCAL_PATH))

endif
endif
