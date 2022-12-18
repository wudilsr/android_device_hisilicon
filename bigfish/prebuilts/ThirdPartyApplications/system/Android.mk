LOCAL_PATH := $(call my-dir)
ifeq ($(strip $(INTERGRATE_THIRDPARTY_APP)),true)
include $(CLEAR_VARS)

define mult-prebuilt-system-apps
$(foreach t,$(1), \
  $(eval include $(CLEAR_VARS)) \
  $(eval LOCAL_MODULE_TAGS := optional) \
  $(eval LOCAL_MODULE := $(t)) \
  $(eval ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)) \
  $(eval LOCAL_MODULE_CLASS := PRESET_APPS) \
  $(eval LOCAL_SRC_FILES := $(t)) \
  $(eval LOCAL_MODULE_PATH := $(TARGET_OUT_APPS)) \
  $(eval include $(BUILD_PREBUILT)) \
)
endef

PREBUILT_APPS := $(call all-apps-under, $(LOCAL_PATH))

$(call mult-prebuilt-system-apps, $(PREBUILT_APPS))

######################################################################################
define all-libs-under
$(shell cd $(1);find . -name "*.so"; )
endef

define get-lib-names
$(shell find $(1) -name "*.so" -exec basename {} \; | sed "s/\.so//g")
endef

include $(CLEAR_VARS)
LOCAL_MODULE_LIB := $(call get-lib-names, $(LOCAL_PATH))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE_LIB)
LOCAL_PREBUILT_LIBS := $(call all-libs-under, $(LOCAL_PATH))
include $(BUILD_MULTI_PREBUILT)
endif
