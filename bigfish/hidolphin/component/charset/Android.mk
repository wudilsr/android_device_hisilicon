LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
#LOCAL_PREBUILT_LIBS := lib/libcharset.so \
#	lib/libcharsetMgr.so
LOCAL_MODULES_NAME := libcharset  libcharsetMgr

define addprefixsuffix_so_list
$(addprefix lib/, $(addsuffix .so, $(1)))
endef

LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list,$(LOCAL_MODULES_NAME))
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)
