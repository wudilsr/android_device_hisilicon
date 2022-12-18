LOCAL_PATH := $(call my-dir)

include $(SDK_DIR)/Android.def
include $(LOCAL_PATH)/cfg.mak

component_modules :=

ifeq ($(CFG_HI_DRM_SUPPORT),y)
component_modules += component/drm
endif

ifeq ($(CFG_HI_BASE_SUPPORT),y)
component_modules += component/base
endif

ifeq ($(CFG_HI_ANDROID_ICS),y)
ifeq ($(CFG_HI_ICONV_SUPPORT),y)
component_modules += external/iconv
endif
endif

ifeq ($(CFG_HI_COMMON_SUPPORT),y)
component_modules += component/common
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
ifeq ($(CFG_HI_DTVSTACK_SUPPORT),y)
component_modules += component/dtvstack
ifeq ($(CFG_HI_DTVAPPFRM_SUPPORT),y)
component_modules += component/dtvappfrm
endif
endif
endif
endif

ifeq ($(CFG_HI_CHARSET_SUPPORT),y)
component_modules += component/charset
endif

ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
ifneq ($(PRODUCT_TARGET),shcmcc)
component_modules += component/player
else
component_modules += component/player_mobile
endif
component_modules += component/libudf
endif

ifeq ($(CFG_HI_FFMPEG_SUPPORT),y)
component_modules += external/ffmpeg
component_modules += external/libclientadp
component_modules += external/libflac
component_modules += component/hisub
endif

ifeq ($(CFG_HI_LIBDASH_SUPPORT),y)
component_modules += external/libdash
component_modules += external/libxml2
endif

ifeq ($(CFG_HI_EXTRACTORADP_SUPPORT),y)
component_modules += component/plugin_extractor
endif
ifeq ($(CFG_HI_DRMENGINE_SUPPORT),y)
component_modules += component/drmengine
endif

ifeq ($(CFG_HI_DLNA_SUPPORT),y)
component_modules += component/hidlna/android
component_modules += component/hidlna/source
endif

ifeq ($(CFG_HI_MULTISCREEN_SUPPORT),y)
component_modules += component/himultiscreen
endif

ifeq ($(CFG_HI_TRANSCODER_SUPPORT),y)
component_modules += component/hitranscoder
endif

ifeq ($(CFG_HI_SKYPLAY_SUPPORT),y)
component_modules += component/skyplay/android
component_modules += component/skyplay/source
endif

ifeq ($(CFG_HI_MIRACAST_SUPPORT),y)
component_modules += component/miracast
endif

ifeq ($(CFG_HI_BROWSER_SUPPORT),y)
component_modules += component/browser
endif

ifeq ($(CFG_HI_MULTIROOM_SUPPORT),y)
component_modules += component/multiroom
endif

ifeq ($(CFG_HI_SMOOTHSTREAMING_SUPPORT),y)
component_modules += component/smoothstreaming
endif
include $(call all-named-subdir-makefiles,$(component_modules))
