LOCAL_PATH:= $(call my-dir)
include $(LOCAL_PATH)/../../cfg.mak

DRM_SOURCE_PATH := $(LOCAL_PATH)/source
DRM_SAMPLE_PATH := $(LOCAL_PATH)/sample

-include $(DRM_SOURCE_PATH)/util/Android.mk
-include $(DRM_SOURCE_PATH)/emptydrm/Android.mk
ifeq ($(CFG_HI_HDCP_SUPPORT),y)
-include $(DRM_SOURCE_PATH)/hdcp/Android.mk
-include $(DRM_SAMPLE_PATH)/hdcp/Android.mk
endif

ifeq ($(CFG_HI_PLAYREADY_SUPPORT),y)
-include $(DRM_SOURCE_PATH)/playready/Android.mk
-include $(DRM_SAMPLE_PATH)/playready/Android.mk
endif

ifeq ($(CFG_HI_WIDEVINE_SUPPORT),y)
-include $(DRM_SOURCE_PATH)/widevine/Android.mk
-include $(DRM_SAMPLE_PATH)/widevine/Android.mk
endif

ifeq ($(CFG_HI_MARLIN_SUPPORT),y)
-include $(DRM_SOURCE_PATH)/marlin/Android.mk
-include $(DRM_SAMPLE_PATH)/marlin/Android.mk
endif
