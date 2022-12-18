ifeq ($(strip $(PRODUCT_TARGET)), demo)
else
LOCAL_PATH:= $(call my-dir)
include $(SDK_DIR)/Android.def
#ifeq ($(CFG_HI_TVP_SUPPORT),y)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := DrmAssist-Recommended
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_CERTIFICATE := media

include $(BUILD_PACKAGE)

# Use the following include to make our test apk.
include $(call all-makefiles-under,$(LOCAL_PATH))
#endif
endif
