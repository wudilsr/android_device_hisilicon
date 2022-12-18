#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===================================================================
#DirectFB Version
#==================================================================
DIRECTFB := DirectFB-1.6.1
FUSION   := linux-fusion-9.0.2
DFB_SAMPLE := DirectFB-examples-1.6.0

ifeq ($(CFG_HI_DIRECTFB_MULTI_SUPPORT),y)
protype=enable
else
protype=disable
endif

ifeq ($(CFG_HI_DIRECTFB_DEBUG_SUPPORT),y)
comtype=enable
else
comtype=disable
endif

#===============================================================================
# local variable
#===============================================================================
INSTALL_DIR := $(CURDIR)/directfb

TARGETS := directfb
ifeq ($(CFG_HI_DIRECTFB_MULTI_SUPPORT),y)
TARGETS += fusion
endif
TARGETS += directfb_example

#====================================================================
#jpeg
#====================================================================
ifeq ($(CFG_LIB_JPEG_VERSION_6B),y)
JPEG_SOFT_INC_DIR := $(MSP_DIR)/api/jpeg/inc/inc_6b
else
JPEG_SOFT_INC_DIR := $(MSP_DIR)/api/jpeg/inc/inc_9a
endif

LIBJPEG=-ljpeg -lhi_common -lhi_msp

#====================================================================
#png
#====================================================================
PNG_SOFT_INC_DIR := $(MSP_DIR)/api/png/libpng-1.6.25

LIBPNG_CFLAGS=-I$(INCLUDE_DIR)
LIBPNG_LIBS=-lpng -lz -lhi_common

#====================================================================
#freetype
#====================================================================
FREETYPE_CFLAGS=-I$(COMPONENT_DIR)/freetype/include/freetype2 \
                -I$(COMPONENT_DIR)/freetype/include
FREETYPE_LIBS=-lfreetype

#=====================================================================================
#export env
#=====================================================================================
INCLUDES := \
            -I$(INSTALL_DIR)/include                \
            -I$(INCLUDE_DIR)                        \
            -I$(JPEG_SOFT_INC_DIR)                  \
            -I$(PNG_SOFT_INC_DIR)                   \
            -I$(MSP_DIR)/api/jpeg/inc/inc_hard      \
            -I$(MSP_DIR)/png/release/include        \
            -I$(MSP_DIR)/api/png/include            \
            -I$(COMPONENT_DIR)/zlib/include         \
            -I$(COMPONENT_DIR)/directfb/include/include_9.0.2

LDFLAGS := -L$(INSTALL_DIR)/lib -L$(SHARED_LIB_DIR)

CPPFLAGS := $(INCLUDES)

#===================================================================
#CFLAGS
#==================================================================
ifneq ($(CFG_HI_KEYLED_74HC164_SUPPORT),)
CFLAGS := -DCFG_HI_KEYLED_74HC164_SUPPORT
endif

ifneq ($(CFG_HI_KEYLED_CT1642_SUPPORT),)
CFLAGS += -DCFG_HI_KEYLED_CT1642_SUPPORT
endif

ifneq ($(CFG_HI_KEYLED_PT6961_SUPPORT),)
CFLAGS += -DCFG_HI_KEYLED_PT6961_SUPPORT
endif

ifneq ($(CFG_HI_KEYLED_PT6964_SUPPORT),)
CFLAGS += -DCFG_HI_KEYLED_PT6964_SUPPORT
endif

EXTRA_FLAGS :=

CFLAGS += $(EXTRA_FLAGS)

ifeq ($(CFG_HI_DIRECTFB_CA_SUPPORT),y)
CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE -DCONFIG_SUPPORT_CA_RELEASE
endif
CFLAGS += -DPNG_ACCELERATION -DLIBPNG14

CXXFLAGS := -fno-rtti $(CFLAGS)
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean directfb fusion directfb_example

all: $(TARGETS)

clean:
	$(AT)rm -rf $(INSTALL_DIR)
	$(AT)rm -rf $(CURDIR)/sample

directfb:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)cd $(DIRECTFB) && sh ./configure --host=$(CFG_HI_TOOLCHAINS_NAME) --prefix=$(INSTALL_DIR) --build=x86 --$(protype)-multi --enable-freetype --$(comtype)-debug --with-gfxdrivers=tde --with-inputdrivers=keyboard,linuxinput,lirc,ps2mouse --without-setsockopt --without-tools --without-tests --disable-osx --disable-x11 --disable-x11vdpau --disable-mmx --disable-sse --disable-vnc --disable-mesa --disable-devmem  --disable-pnm --disable-imlib2 --disable-mpeg2 --disable-bmp --disable-jpeg2000 --disable-video4linux --disable-linotype --disable-svg CFLAGS="$(CFLAGS)" LIBJPEG="$(LIBJPEG)" LIBPNG_CFLAGS="$(LIBPNG_CFLAGS)" LIBPNG_LIBS="$(LIBPNG_LIBS)" FREETYPE_CFLAGS="$(FREETYPE_CFLAGS)" FREETYPE_LIBS="$(FREETYPE_LIBS)" INCLUDES="$(INCLUDES)" LDFLAGS="$(LDFLAGS)" CPPFLAGS="$(CPPFLAGS)" CXXFLAGS="$(CXXFLAGS)" CC=$(CFG_HI_TOOLCHAINS_NAME)-gcc CPP=$(CFG_HI_TOOLCHAINS_NAME)-cpp AR=$(CFG_HI_TOOLCHAINS_NAME)-ar AS=$(CFG_HI_TOOLCHAINS_NAME)-as LD=$(CFG_HI_TOOLCHAINS_NAME)-ld NM=$(CFG_HI_TOOLCHAINS_NAME)-nm STRIP=$(CFG_HI_TOOLCHAINS_NAME)-strip OBJDUMP=$(CFG_HI_TOOLCHAINS_NAME)-objdump
	$(AT)cd $(DIRECTFB) && make install

fusion:
	$(AT)test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	$(AT)cp -rf $(FUSION)/linux/drivers/char/fusion/debug.h  $(FUSION)/linux/drivers/char/fusion/single 
	$(AT)make -C $(FUSION) SDK_DIR=$(SDK_DIR) FUSION_DIR=$(CURDIR)/$(FUSION)
	$(AT)cp -rf $(FUSION)/fusion.ko $(INSTALL_DIR)/lib

directfb_example:
	$(AT)test -d $(CURDIR)/sample/bin || mkdir -p $(CURDIR)/sample/bin
	$(AT)test -d $(CURDIR)/sample/share/directfb-examples/fonts || mkdir -p  $(CURDIR)/sample/share/directfb-examples/fonts
	$(AT)find $(DFB_SAMPLE) -name "*.c" | xargs cp -t $(CURDIR)/sample/bin
	$(AT)find $(DFB_SAMPLE) -name "*.h" | xargs cp -t $(CURDIR)/sample/bin
	$(AT)cp -rf ${DFB_SAMPLE}/res               $(CURDIR)/sample/share/directfb-examples/
	$(AT)cp -rf ${DFB_SAMPLE}/data/*            $(CURDIR)/sample/share/directfb-examples/
	$(AT)cp -rf ${DFB_SAMPLE}/data/df_neo/*     $(CURDIR)/sample/share/directfb-examples/
	$(AT)mv $(CURDIR)/sample/share/directfb-examples/decker.dgiff  $(CURDIR)/sample/share/directfb-examples/fonts
	$(AT)mv $(CURDIR)/sample/share/directfb-examples/decker.ttf    $(CURDIR)/sample/share/directfb-examples/fonts
	$(AT)find $(CURDIR)/sample/share/directfb-examples -name "Makefile*" | xargs rm -rf
	$(AT)rm -rf $(CURDIR)/sample/share/directfb-examples/df_neo
	$(AT)cp -rf $(DFB_SAMPLE)/Makefile $(CURDIR)/sample/bin
	$(AT)cp -rf $(DFB_SAMPLE)/sample_rules.mak  $(CURDIR)/sample/bin
	$(AT)make -C $(CURDIR)/sample/bin
	$(AT)rm -rf $(CURDIR)/sample/bin/*.c
	$(AT)rm -rf $(CURDIR)/sample/bin/*.h
	$(AT)rm -rf $(CURDIR)/sample/bin/*.o
