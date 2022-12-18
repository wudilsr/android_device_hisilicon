#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)
CFLAGS += -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common

objects :=  esplay ao tsplay es_ts_switch ipplay mosaic pip log memdev userproc cgms \
            mce capture hdmi_tsplay fb higo tde jpeg \
            gpio pmoc ir e2prom i2c \
            otp flash uart network fs cipher snapshot 3dtv pwm edid video_test pq

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
objects += tuner demux dvbplay fullband psi iframe_dec dolby seperateoutput uti1201 factory_detect
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
objects += pvr
endif
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
objects += keyled
endif

ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
objects += ci
endif

ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
objects += hdcpkey
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
objects += aenc
endif

ifeq ($(CFG_HI_SND_CAST_SUPPORT),y)
objects += audiocast
endif

ifeq ($(CFG_HI_AI_SUPPORT),y)
CFLAGS += -DHI_AUDIO_AI_SUPPORT
objects += ai
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
objects += voip
endif

ifeq ($(CFG_HI_KARAOKE_SUPPORT),y)
objects += karaoke
endif

ifeq ($(CFG_HI_RESAMPLER_QUALITY_LINEAR),y)
objects += resampler
endif

ifeq ($(CFG_HI_LOADER_SUPPORT),y)
objects += loader
endif

ifeq ($(CFG_HI_WIFI_SUPPORT),y)
objects += wifi
endif

ifeq ($(CFG_HI_3G_SUPPORT),y)
objects += 3g
endif

ifeq ($(CFG_HI_GPU),y)
#objects += gpu
endif

ifeq ($(CFG_HI_PES_SUPPORT),y)
objects += pesplay
endif

ifeq ($(CFG_HI_SCI_SUPPORT),y)
objects += sci
endif

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
objects += wdg
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
ifeq ($(CFG_HI_VENC_SUPPORT),y)
objects += transcode
objects += avcast
endif
endif

ifeq ($(CFG_HI_VI_SUPPORT),y)
CFLAGS += -I$(MSP_DIR)/drv/include

objects += vi
ifeq ($(CFG_HI_VENC_SUPPORT),y)
ifneq ($(CFG_HI_VO_SINGLE_VIDEO_SUPPORT),y)
objects += vi_venc
ifeq ($(CFG_HI_VP_SUPPORT),y)
objects += vp
endif
endif
endif
ifeq ($(CFG_HI_AI_SUPPORT),y)
objects += hdmi_rx
endif
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
objects += venc
endif

ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
objects += localplay
endif

ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
objects += cc
endif

ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
objects += teletext
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
objects += subtitle
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifneq ($(CFG_HI_ADVCA_TYPE), NAGRA)
objects += advca
else
objects += nagra
endif
endif

ifeq ($(CFG_HI_HAEFFECT_SRS_SUPPORT),y)
objects += srs
endif

ifeq ($(CFG_HI_DLNA_SUPPORT),y)
objects += hidlna
endif

ifeq ($(CFG_HI_BLUETOOTH_SUPPORT),y)
objects += castbluetooth
endif

ifeq ($(CFG_HI_TRANSCODER_SUPPORT),y)
objects += hitranscoder
endif

ifeq ($(CFG_HI_PLAYREADY_SUPPORT),y)
objects += playready
endif

objects_clean := $(addsuffix _clean, $(objects))

ifeq ($(obj),)
depends := $(objects)
else
depends := $(obj)
endif

depends_clean := $(addsuffix _clean, $(depends))

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean $(objects) $(objects_clean)

all: $(depends)

clean: $(depends_clean)

$(objects): common
	$(AT)make -C $@

$(objects_clean):
	$(AT)make -C $(patsubst %_clean, %, $@) clean

common: $(COMMON_FILES) $(if $(findstring $(CFG_HI_VI_SUPPORT),y),$(SAMPLE_DIR)/common/hi_adp_hdmi_rx.o,)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

