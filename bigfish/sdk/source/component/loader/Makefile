ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../../../
include $(SDK_DIR)/base.mak
endif

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C api all
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C app all
endif

clean:
	$(AT)make -C api clean
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C app clean
endif

install:
	$(AT)make -C api install
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C app install
endif

uninstall:
	$(AT)make -C api uninstall
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)make -C app uninstall
endif


