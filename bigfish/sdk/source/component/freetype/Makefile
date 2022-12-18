#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

TARGET := freetype-2.3.12
#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  $(CFG_HI_CFLAGS)

##当高安选项打开时，由于高安要求SDK api不编译静态库，所以SDK顶层Makefile中把-fPIC去掉了，但对于字体库来说，希望能使用动态库，所以要编译时要通过此判断增加-fPIC
ifneq ($(findstring -fPIC, $(CFG_HI_CFLAGS)), -fPIC)
CFLAGS += -fPIC
endif

LIBS := lib$(TARGET)


INSTALL_DIR = $(SDK_DIR)/source/component/freetype/release
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
	-tar -xvf freetype-2.3.12.tar.gz
	chmod 777 freetype-2.3.12/builds/unix -R
	cd $(TARGET);sh ./configure --host=$(CFG_HI_TOOLCHAINS_NAME) --enable-shared --enable-static CFLAGS="$(FLAGS_TMP)" prefix=$(INSTALL_DIR);make install
ifndef CFG_HI_ADVCA_FUNCTION
	$(AT)cp -ralf   release/lib/lib*.a       lib/$(CFG_HI_TOOLCHAINS_NAME)/
endif
	$(AT)cp -ralf   release/lib/lib*.so*     lib/$(CFG_HI_TOOLCHAINS_NAME)/
	$(AT)cp -rf  release/include/*     include/
	#rm -rf $(TARGET)
	rm -rf release

install:compile
	#tar -zxvf lib/$(CFG_HI_TOOLCHAINS_NAME).tar.gz -C lib/
ifndef CFG_HI_ADVCA_FUNCTION
	$(AT)cp -ralf 	lib/$(CFG_HI_TOOLCHAINS_NAME)/lib*.a  	$(STATIC_LIB_DIR)/
endif
	$(AT)cp -ralf  	lib/$(CFG_HI_TOOLCHAINS_NAME)/lib*.so* 	$(SHARED_LIB_DIR)/
	$(AT)cp -rf  include/*     $(INCLUDE_DIR)/
	rm -rf lib/$(CFG_HI_TOOLCHAINS_NAME)

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/*freetype*.a
	$(AT)rm -rf $(SHARED_LIB_DIR)/*freetype*.so*
	rm -rf $(INCLUDE_DIR)/*freetype* 
	rm -rf $(INCLUDE_DIR)/ft2build.h 

