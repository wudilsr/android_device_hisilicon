LOCAL_PATH := $(call my-dir)
SAMPLE_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

define first_makefile_under
    $(wildcard $(addsuffix /Android.mk, $(addprefix $(SAMPLE_PATH)/,$(1))))
endef

# don't compile: dolby seperateoutput higo wifi vp gpu 3dtv
SAMPLE_MODULE := common esplay ao tsplay es_ts_switch ipplay mosaic pip log memdev userproc cgms \
          capture hdmi_tsplay fb tde \
          gpio ir e2prom i2c  \
          otp flash uart network fs cipher snapshot pwm edid video_test pq playready

ifneq ($(PRODUCT_TARGET),shcmcc)
ifneq ($(VMX_ADVANCED_SUPPORT),true)
ifneq ($(HISILICON_TEE),true)
SAMPLE_MODULE += pmoc
endif
endif
endif

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_MODULE += tuner demux dvbplay psi iframe_dec uti1201 factory_detect
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
SAMPLE_MODULE += pvr
endif
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
SAMPLE_MODULE += keyled
endif

ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
SAMPLE_MODULE += ci
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
SAMPLE_MODULE += hdcpkey
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
SAMPLE_MODULE += aenc
endif

ifeq ($(CFG_HI_SND_CAST_SUPPORT),y)
SAMPLE_MODULE += audiocast
endif

ifeq ($(CFG_HI_AI_SUPPORT),y)
SAMPLE_MODULE += ai
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
SAMPLE_MODULE += voip
endif

ifeq ($(CFG_HI_KARAOKE_SUPPORT),y)
SAMPLE_MODULE += karaoke
endif

ifeq ($(CFG_HI_RESAMPLER_QUALITY_LINEAR),y)
SAMPLE_MODULE += resampler
endif

#ifeq ($(CFG_HI_LOADER_SUPPORT),y)
SAMPLE_MODULE += loader
#endif

ifeq ($(CFG_HI_MCE_SUPPORT),y)
SAMPLE_MODULE += mce
endif

ifeq ($(CFG_HI_PES_SUPPORT),y)
SAMPLE_MODULE += pesplay
endif

ifeq ($(CFG_HI_SCI_SUPPORT),y)
SAMPLE_MODULE += sci
endif

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
SAMPLE_MODULE += wdg
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
ifeq ($(CFG_HI_VENC_SUPPORT),y)
SAMPLE_MODULE += transcode
SAMPLE_MODULE += avcast
endif
endif

ifeq ($(CFG_HI_VI_SUPPORT),y)
SAMPLE_MODULE += vi
SAMPLE_MODULE += hdmi_rx
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
SAMPLE_MODULE += venc
endif
ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
SAMPLE_MODULE += localplay
endif

ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
SAMPLE_MODULE += cc
endif

ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
SAMPLE_MODULE += teletext
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
SAMPLE_MODULE += subtitle
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifneq ($(CFG_HI_ADVCA_TYPE), NAGRA)
SAMPLE_MODULE += advca
else
SAMPLE_MODULE += nagra
endif
endif

include $(call first_makefile_under, $(SAMPLE_MODULE))
