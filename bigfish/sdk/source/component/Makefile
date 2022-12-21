#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#       variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
objects:= ha_codec hifat 

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
objects += freetype
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
objects += zlib
endif

ifeq ($(CFG_HI_ALSA_SUPPORT),y)
objects += alsa
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
objects += usbphone voip
endif

ifeq ($(CFG_HI_SND_AFLT_SUPPORT),y)
objects += ha_effect
endif

ifeq ($(CFG_HI_KARAOKE_SUPPORT),y)
objects += karaoke
endif

ifeq ($(CFG_HI_PES_SUPPORT),y)
objects += hipes
endif

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
objects += advca
endif

ifeq ($(CFG_HI_CURL_SUPPORT),y)
objects += curl
endif

ifeq ($(CFG_HI_DIRECTFB_SUPPORT),y)
objects += directfb
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
objects += subtitle
endif

ifeq ($(CFG_HI_CAPTION_SO_SUPPORT),y)
objects += subtoutput
endif

ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
objects += teletext
endif

ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
objects += cc
endif

ifeq ($(CFG_HI_WIFI_SUPPORT),y)
objects += wifi
endif

ifeq ($(CFG_HI_3G_SUPPORT),y)
objects += 3g
endif

ifeq ($(CFG_HI_NTFS_SUPPORT),y)
objects += ntfs
endif

ifeq ($(CFG_HI_VP_SUPPORT),y)
objects += vp
endif

ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
objects += hiplayer
endif

ifneq ($(CFG_HI_DLNA_SUPPORT)_$(CFG_HI_TRANSCODER_SUPPORT),_)
objects += component_common
endif

ifeq ($(CFG_HI_DLNA_SUPPORT),y)
objects += hidlna
endif

ifeq ($(CFG_HI_TRANSCODER_SUPPORT),y)
objects += hitranscoder
endif

ifeq ($(CFG_HI_EXFAT_SUPPORT),y)
objects += exfat
endif

ifeq ($(CFG_HI_PLAYREADY_SUPPORT),y)
objects += playready
endif

objects_clean:=$(addsuffix _clean,$(objects))
objects_install:=$(addsuffix _install,$(objects))
objects_uninstall:=$(addsuffix _uninstall,$(objects))

depends := $(obj)
ifeq ($(depends),)
depends += $(objects)
endif
depends_clean       := $(addsuffix _clean,$(depends))
depends_install     := $(addsuffix _install,$(depends))
depends_uninstall   := $(addsuffix _uninstall,$(depends))

ifeq ($(obj),)
else ifeq ($(obj), loader)
    depends             += loader
    depends_clean       += loader_clean
    depends_install     += loader_install
    depends_uninstall   += loader_uninstall
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall
all: $(depends)

clean: $(depends_clean)

install: $(depends_install)

uninstall: $(depends_uninstall)

#==================================================================
#                          modules
#==================================================================
.PHONY: $(objects) $(objects_clean) $(objects_install) $(objects_uninstall)

$(objects):
	make -C $@ all

$(objects_clean):
	make -C $(patsubst %_clean,%,$@) clean

$(objects_install):
	make -C $(patsubst %_install,%,$@) install

$(objects_uninstall):
	make -C $(patsubst %_uninstall,%,$@) uninstall

loader: $(if $(findstring $(CFG_HI_FREETYPE_FONT_SUPPORT),y),freetype,) $(if $(findstring $(CFG_HI_CURL_SUPPORT),y),curl,)
	$(AT)make -C loader all

loader_clean:
	$(AT)make -C loader clean

loader_install: $(if $(findstring $(CFG_HI_FREETYPE_FONT_SUPPORT),y),freetype_install,) $(if $(findstring $(CFG_HI_CURL_SUPPORT),y),curl_install,)
	$(AT)make -C loader install

loader_uninstall:
	$(AT)make -C loader uninstall

