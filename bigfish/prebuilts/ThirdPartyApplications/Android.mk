LOCAL_PATH := $(call my-dir)

define all-apps-under
$(shell find $(1) -name "*.apk" -exec basename {} \; )
endef

include $(call all-makefiles-under, $(LOCAL_PATH))
