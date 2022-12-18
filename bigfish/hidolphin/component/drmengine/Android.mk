LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
#LOCAL_PREBUILT_LIBS := lib/libHiDrmEngine.so
LOCAL_MODULES_NAME := libHiDrmEngine

define addprefixsuffix_so_list
$(addprefix lib/, $(addsuffix .so, $(1)))
endef

LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list,$(LOCAL_MODULES_NAME))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

