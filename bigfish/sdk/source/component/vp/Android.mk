LOCAL_PATH := $(call my-dir)

VP_MODULE := rtp src

include $(call all-named-subdir-makefiles,$(VP_MODULE))
