LOCAL_PATH:= $(call my-dir)
include $(SDK_DIR)/Android.def

ifeq ($(CFG_HI_VP_SUPPORT),y)
ifeq ($(CFG_HI_VOIP_SUPPORT),y)
include $(CLEAR_VARS)
LOCAL_CERTIFICATE := platform
LOCAL_MODULE_TAGS := optional
#LOCAL_STATIC_JAVA_LIBRARIES := android-commonamv

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := VideoPhone
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_CERTIFICATE := platform

LOCAL_STATIC_JAVA_LIBRARIES := PhonePlayer
LOCAL_OVERRIDES_PACKAGES := platform
LOCAL_PROGUARD_ENABLED := disabled

#LOCAL_PROGUARD_FLAGS := -include $(LOCAL_PATH)/proguard.flags

include $(BUILD_PACKAGE)

# Use the folloing include to make our test apk.
#include $(call all-makefiles-under,$(LOCAL_PATH))
include $(call first-makefiles-under,$(LOCAL_PATH))
endif
endif