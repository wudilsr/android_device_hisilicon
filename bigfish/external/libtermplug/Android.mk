LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_TAGS := optional

HAVE_TERM_FILE := $(shell test -f  $(LOCAL_PATH)/lib/libtermplug.so && echo yes)

ifeq ($(HAVE_TERM_FILE),yes)

$(warning build formal termplug)
LOCAL_SRC_PRELIBS := libtermplug
LOCAL_MODULES_NAME := $(LOCAL_SRC_PRELIBS)
LOCAL_PREBUILT_LIBS := lib/libtermplug.so
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
include $(BUILD_MULTI_PREBUILT)

else

ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
else
LOCAL_32_BIT_ONLY := true
endif
$(warning build test termplug)
LOCAL_MODULE := libtermplug
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := termplug.c
include $(BUILD_SHARED_LIBRARY)

endif