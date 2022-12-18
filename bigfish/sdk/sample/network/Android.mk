LOCAL_PATH := $(call my-dir)

NETWORK_SAMPLE_MODULE := ipcfg socket

include $(call all-named-subdir-makefiles,$(NETWORK_SAMPLE_MODULE))
