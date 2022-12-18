################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../../..
include $(SDK_DIR)/base.mak
endif

################################################################################
PWD             := $(shell pwd)
HOST            := $(patsubst %-,%,$(CROSS_COMPILE))
FAT_LIB         := $(PWD)/lib
FAT_TOOLS       := $(PWD)/tools
FAT_INCLUDE     := $(PWD)/include
USR_BIN         := $(ROOTFS_DIR)/usr/bin

################################################################################
.PHONY: all clean install uninstall

all:

clean:

install: all
ifeq ($(CFG_HI_FAT_SUPPORT),y)
	$(AT)cp -rf $(FAT_LIB)/libhimount_gcc-4.4.1-vfp.so  $(SHARED_LIB_DIR)/libhimount.so
	$(AT)cp -rf $(FAT_LIB)/libhimount_gcc-4.4.1-vfp.a   $(STATIC_LIB_DIR)/libhimount.a
	$(AT)cp -rf $(FAT_INCLUDE)/*.h $(INCLUDE_DIR)
	$(AT)mkdir -p $(USR_BIN) && cp -rf $(FAT_TOOLS)/himount $(USR_BIN)/himount
ifdef CFG_HI_ADVCA_FUNCTION
ifneq ($(CFG_HI_ADVCA_FUNCTION), DEBUG))
	$(AT)test ! -f $(SHARED_LIB_DIR)/libhimount.so | rm -rvf $(SHARED_LIB_DIR)/libhimount.so
	$(AT)-cp -rvf $(FAT_LIB)/libhimount_gcc-4.4.1-vfp_ca.a $(STATIC_LIB_DIR)/libhimount.a
	$(AT)-cp -rvf $(FAT_INCLUDE)/*.h $(INCLUDE_DIR)
	$(AT)-cp -rvf $(FAT_TOOLS)/himount_ca $(ROOTFS_DIR)/bin/himount
endif
endif
endif

uninstall:
ifeq ($(CFG_HI_FAT_SUPPORT),y)
	$(AT)rm -rf $(USR_BIN)/himount $(SHARED_LIB_DIR)/libhimount.so $(STATIC_LIB_DIR)/libhimount.a $(INCLUDE_DIR)/himount_api.h
endif

