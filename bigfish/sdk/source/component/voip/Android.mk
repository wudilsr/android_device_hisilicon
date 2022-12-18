LOCAL_PATH := $(call my-dir)
 
VOIP_MODULE := api drv

include $(call all-named-subdir-makefiles,$(VOIP_MODULE))
