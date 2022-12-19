LOCAL_PATH := $(call my-dir)

COMPONENT_MODULE := ha_codec hifat resampler playready

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
COMPONENT_MODULE += freetype 
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
COMPONENT_MODULE += zlib
endif

ifeq ($(CFG_HI_ALSA_SUPPORT),y)
COMPONENT_MODULE += alsa
endif

ifeq ($(CFG_HI_SND_AFLT_SUPPORT),y)
objects += ha_effect
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
COMPONENT_MODULE += voip
endif

ifeq ($(CFG_HI_KARAOKE_SUPPORT),y)
COMPONENT_MODULE += karaoke
endif

ifeq ($(CFG_HI_PES_SUPPORT),y)
COMPONENT_MODULE += hipes
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
COMPONENT_MODULE += advca
endif

ifeq ($(CFG_HI_CURL_SUPPORT),y)
COMPONENT_MODULE += curl
endif
#ifeq ($(CFG_HI_LOADER_SUPPORT),y)
COMPONENT_MODULE += loader
#endif

ifeq ($(CFG_HI_DIRECTFB_SUPPORT),y)
COMPONENT_MODULE += directfb
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
COMPONENT_MODULE += subtitle
endif
ifeq ($(CFG_HI_CAPTION_SO_SUPPORT),y)
COMPONENT_MODULE += subtoutput
endif
ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
COMPONENT_MODULE += teletext
endif
ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
COMPONENT_MODULE += cc
endif

#ifeq ($(CFG_HI_WIFI_SUPPORT),y)
COMPONENT_MODULE += wifi
#endif

ifeq ($(CFG_HI_3G_SUPPORT),y)
COMPONENT_MODULE += 3g
endif

ifeq ($(CFG_HI_NTFS_SUPPORT),y)
COMPONENT_MODULE += ntfs 
endif

ifeq ($(CFG_HI_VP_SUPPORT),y)
COMPONENT_MODULE += vp 
endif
ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
COMPONENT_MODULE += hiplayer 
endif

ifeq ($(CFG_HI_EXFAT_SUPPORT),y)
COMPONENT_MODULE += exfat
endif

include $(call all-named-subdir-makefiles,$(COMPONENT_MODULE))
