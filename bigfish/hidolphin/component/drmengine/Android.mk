LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := lib/libHiDrmEngine.so
LOCAL_MODULE := libHiDrmEngine
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX:= .so
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := lib/libwvcipher.so
LOCAL_MODULE := libwvcipher
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX:= .so
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := lib/libdrmclientplugin.so
LOCAL_MODULE := libdrmclientplugin
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/drm
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX:= .so
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_SRC_FILES := lib/libwvmcipherplugin.so
LOCAL_MODULE := libwvmcipherplugin
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib/drm
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) <= 20 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX:= .so
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)
