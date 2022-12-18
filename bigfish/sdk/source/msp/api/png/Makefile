#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..

include $(SDK_DIR)/base.mak
endif

TARGET := png
#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  $(CFG_HI_CFLAGS)

CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(COMMON_DRV_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(MSP_DRV_INCLUDE)                    \
            -I$(MSP_DIR)/api/$(TARGET)/include      \
            -I$(MSP_DIR)/drv/$(TARGET)/include      \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc

CFLAGS += -DCONFIG_GFX_STB_SDK

LIBS := libhi_$(TARGET)


INSTALL_DIR = $(MSP_DIR)/api/$(TARGET)/release
FLAGS_TMP=$(subst -c , ,$(CFLAGS))

ifdef CFG_HI_STATIC_LIB_ONLY
ENABLE_LIB_MODE = --enable-shared=no
#CFLAGS += -fPIC
endif


LIB_VER = 1.4.0

ifeq ($(CFG_HI_LIB_PNG_VERSION),libpng-1.6.16)
LIB_VER = 1.6.16
PNG_LIBS        :=  -lhi_common -lrt -lpthread -lm
PNG_LDFLAGS     :=  -L$(STATIC_LIB_DIR)

PNG_CPPFLAGS    :=  -I$(COMPONENT_DIR)/zlib/release/include     \
                    -I$(COMPONENT_DIR)/freetype/release/include \
                    -I$(MSP_DIR)/drv/$(TARGET)/include          \
                    -I$(MSP_DIR)/drv/include

FLAGS_TMP += -DHIPNG_ACCELERATE -DHIPNG_MMZ -DPNG_NO_STRING -DHIGFX_COMMON
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install mod_install uninstall

all:
	mkdir -p release
ifeq ($(CFG_HI_LIB_PNG_VERSION),libpng-1.4.0)
	cd libpng-$(LIB_VER);sh ./configure --host=$(CFG_HI_TOOLCHAINS_NAME) $(ENABLE_LIB_MODE) CFLAGS="$(FLAGS_TMP)" CPPFLAGS="$(PNG_CPPFLAGS)" LIBS="$(PNG_LIBS)" LDFLAGS="$(PNG_LDFLAGS)" prefix=$(INSTALL_DIR);make install
else
	make -C libpng-$(LIB_VER) install
	cd $(INSTALL_DIR)/lib;rm libpng16.so.16;ln -s libpng16.so  libpng16.so.16
endif
	rm -rf $(INSTALL_DIR)/man
	rm -rf $(INSTALL_DIR)/share
	rm -rf $(INSTALL_DIR)/bin
	rm -rf $(INSTALL_DIR)/include/libpng
	$(AT)cp -ralf   $(MSP_DIR)/api/$(TARGET)/include/hi_png_config.h $(INSTALL_DIR)/include/

clean:
ifeq ($(CFG_HI_LIB_PNG_VERSION),libpng-1.4.0)
	cd libpng-$(LIB_VER);sh ./configure --host=$(CFG_HI_TOOLCHAINS_NAME) $(ENABLE_LIB_MODE) CFLAGS="$(FLAGS_TMP)" CPPFLAGS="$(PNG_CPPFLAGS)" LIBS="$(PNG_LIBS)" LDFLAGS="$(PNG_LDFLAGS)" prefix=$(INSTALL_DIR);make clean
	rm -rf libpng-$(LIB_VER)/Makefile
else
	make -C libpng-$(LIB_VER) clean
endif
	rm -rf release
	rm -rf libpng-$(LIB_VER)/.deps
	rm -rf libpng-$(LIB_VER)/config.log
	rm -rf libpng-$(LIB_VER)/config.status
	rm -rf libpng-$(LIB_VER)/libpng.pc
	rm -rf libpng-$(LIB_VER)/libpng-config
	rm -rf libpng-$(LIB_VER)/libtool

install: all
	$(AT)cp -ralf 	$(INSTALL_DIR)/lib/libpng*.a  	$(STATIC_LIB_DIR)/
	$(AT)cp -ralf 	$(INSTALL_DIR)/lib/pkgconfig  	$(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -ralf  	$(INSTALL_DIR)/lib/libpng*.so* 	$(SHARED_LIB_DIR)/
	$(AT)cp -ralf 	$(INSTALL_DIR)/lib/pkgconfig  	$(SHARED_LIB_DIR)/
endif
	$(AT)cp -rf  $(INSTALL_DIR)/include/*     $(INCLUDE_DIR)/

mod_install: install

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/*png*.a
	$(AT)rm -rf $(STATIC_LIB_DIR)/pkgconfig
	$(AT)rm -rf $(SHARED_LIB_DIR)/*png*.so*
	$(AT)rm -rf $(SHARED_LIB_DIR)/pkgconfig
	rm -rf $(INCLUDE_DIR)/*png*

