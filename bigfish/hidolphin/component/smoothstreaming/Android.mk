LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libhi_smoothstreaming
LOCAL_MODULE_SUFFIX := .so
LOCAL_MULTILIB := both
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 21 ))" )))
LOCAL_SRC_FILES_32 := lib/libhi_smoothstreaming.so
LOCAL_SRC_FILES_64 := lib64/libhi_smoothstreaming.so
else
LOCAL_SRC_FILES := lib/libhi_smoothstreaming.so
endif
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_TAG := optional
include $(BUILD_PREBUILT)
