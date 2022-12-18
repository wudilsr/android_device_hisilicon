ifeq ($(BUILDIN_HISI_GPU),true)
LOCAL_PATH := $(call my-dir)
COMMON_MODULES := \
    android/gralloc \
    driver \
    prebuilts

include $(call all-named-subdir-makefiles,$(COMMON_MODULES))
endif
