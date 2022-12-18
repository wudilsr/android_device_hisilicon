#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

TARGET := zlib-1.2.8
#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  $(CFG_HI_CFLAGS)


LIBS := lib$(TARGET)


INSTALL_DIR = $(SDK_DIR)/source/component/zlib/release
FLAGS_TMP=$(subst -c , ,$(CFLAGS)) 
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall compile

all:
clean:
compile: 
	mkdir -p release
	mkdir -p lib/$(CFG_HI_TOOLCHAINS_NAME)
	tar -xvf zlib-1.2.8.tar.gz
	cd $(TARGET); CC=$(CFG_HI_TOOLCHAINS_NAME)-gcc AR=$(CFG_HI_TOOLCHAINS_NAME)-ar RANLIB=$(CFG_HI_TOOLCHAINS_NAME)-ranlib CFLAGS="$(FLAGS_TMP)" sh ./configure --prefix=$(INSTALL_DIR);make install
ifndef CFG_HI_ADVCA_FUNCTION
	$(AT)cp -rf     release/lib/lib*.a       lib/$(CFG_HI_TOOLCHAINS_NAME)/
endif
	$(AT)cp -ralf   release/lib/lib*.so*     lib/$(CFG_HI_TOOLCHAINS_NAME)/
	$(AT)cp -rf  release/include/*     include
	cd lib; tar -zcf $(CFG_HI_TOOLCHAINS_NAME).tar.gz $(CFG_HI_TOOLCHAINS_NAME)
	rm -rf $(TARGET) 
	rm -rf release

install:compile
	#tar -zxvf lib/$(CFG_HI_TOOLCHAINS_NAME).tar.gz -C lib/
ifndef CFG_HI_ADVCA_FUNCTION
	$(AT)cp -rf 	lib/$(CFG_HI_TOOLCHAINS_NAME)/lib*.a  	$(STATIC_LIB_DIR)/
endif
	$(AT)cp -ralf  	lib/$(CFG_HI_TOOLCHAINS_NAME)/lib*.so* 	$(SHARED_LIB_DIR)/
	$(AT)cp -rf  include/*     $(INCLUDE_DIR)/
	rm -rf lib/$(CFG_HI_TOOLCHAINS_NAME)

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/libz*.a
	$(AT)rm -rf $(SHARED_LIB_DIR)/libz*.so*
	rm -rf $(INCLUDE_DIR)/zlib.h 
	rm -rf $(INCLUDE_DIR)/zconf.h 

