LOCAL_PATH:= $(call my-dir)

# the library
# ============================================================

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(call find-other-java-files, java)

LOCAL_MODULE:= qb

#LOCAL_JAVA_LIBRARIES := android.policy conscrypt telephony-common

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_PROGUARD_FLAG_FILES := proguard.flags

include $(BUILD_JAVA_LIBRARY)

include $(BUILD_DROIDDOC)

ifeq ($(strip $(TARGET_BUILD_VARIANT)),eng)
-include $(LOCAL_PATH)/prebuilt/eng/Android.mk
endif
ifeq ($(strip $(TARGET_BUILD_VARIANT)),user)
-include $(LOCAL_PATH)/prebuilt/user/Android.mk
endif
