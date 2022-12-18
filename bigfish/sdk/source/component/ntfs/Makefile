################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../../..
include $(SDK_DIR)/base.mak
endif

NTFS_DIR := $(COMPONENT_DIR)/ntfs
NTFS_MODULE_NAME ?= $(if $(findstring _dbg_, $(CFG_HI_KERNEL_CFG)),tntfs.ko,tntfs_$(CFG_HI_KERNEL_CFG).ko)

.PHONY: all clean install uninstall

all:

clean:

install: all
ifeq ($(CFG_HI_NTFS_TOOLS_SUPPORT),y)
	$(AT)mkdir -p $(ROOTFS_DIR)/bin
	$(AT)cp -f $(NTFS_DIR)/tools/mkntfs $(ROOTFS_DIR)/bin
	$(AT)cp -f $(NTFS_DIR)/tools/ntfsck $(ROOTFS_DIR)/bin
endif
ifeq ($(CFG_HI_NTFS_MODULE_SUPPORT),y)
	$(AT)cp -f $(NTFS_DIR)/$(CFG_HI_KERNEL_VERSION)/$(NTFS_MODULE_NAME)  $(MODULE_DIR)/tntfs.ko
endif

uninstall:
ifeq ($(CFG_HI_NTFS_TOOLS_SUPPORT),y)
	$(AT)rm -rf $(ROOTFS_DIR)/bin/mkntfs $(ROOTFS_DIR)/bin/ntfsck
endif
ifeq ($(CFG_HI_NTFS_MODULE_SUPPORT),y)
	$(AT)rm -rf $(MODULE_DIR)/tntfs.ko
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


