LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

define mult-prebuilt-data-apps
$(foreach t,$(1), \
  $(eval include $(CLEAR_VARS)) \
  $(eval LOCAL_MODULE_TAGS := optional) \
  $(eval LOCAL_MODULE := $(t)) \
  $(eval ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)) \
  $(eval LOCAL_MODULE_CLASS := PRESET_APPS) \
  $(eval LOCAL_SRC_FILES := $(t)) \
  $(eval LOCAL_MODULE_PATH := $(TARGET_OUT_DATA_APPS)) \
  $(eval include $(BUILD_PREBUILT)) \
)
endef

PREBUILT_APPS := $(call all-apps-under, $(LOCAL_PATH))

$(call mult-prebuilt-data-apps, $(PREBUILT_APPS))
