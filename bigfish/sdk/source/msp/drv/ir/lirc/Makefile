#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../../..
    endif

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
LIRC := lirc-0.8.7

.PHONY: all clean install uninstall

all:
	$(AT)([ -d $(LIRC) ] || tar xf $(LIRC).tar.gz)
	$(AT)chmod u+x $(LIRC)/hiconfigure $(LIRC)/configure
	$(AT)(cd $(LIRC) && ./hiconfigure $(CC) $(KERNEL_DIR)/$(CFG_HI_KERNEL_VERSION) NO && make ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- && cd -)

clean:
	$(AT)rm -rf $(LIRC)

install: all
	$(AT)cp -rf $(LIRC)/drivers/lirc_dev/lirc_dev.ko        $(MODULE_DIR)/
	$(AT)cp -rf $(LIRC)/drivers/lirc_serial/lirc_serial.ko  $(MODULE_DIR)/
	$(AT)$(STRIP) $(LIRC)/daemons/lircd
	$(AT)$(STRIP) $(LIRC)/daemons/irrecord
	$(AT)$(STRIP) $(LIRC)/tools/irw
	$(AT)$(STRIP) $(LIRC)/tools/mode2
	$(AT)mkdir -p $(ROOTFS_DIR)/usr/bin && cp -rf $(LIRC)/daemons/lircd     $(ROOTFS_DIR)/usr/bin
	$(AT)mkdir -p $(ROOTFS_DIR)/usr/bin && cp -rf $(LIRC)/daemons/irrecord  $(ROOTFS_DIR)/usr/bin
	$(AT)mkdir -p $(ROOTFS_DIR)/etc && cp -rf $(LIRC)/remotes/hisilicon/lircd.conf $(ROOTFS_DIR)/etc

uninstall: clean
	$(AT)rm -f $(MODULE_DIR)/lirc_dev.ko
	$(AT)rm -f $(MODULE_DIR)/lirc_serial.ko
	$(AT)rm -f $(ROOTFS_DIR)/usr/bin/lircd $(ROOTFS_DIR)/usr/bin/irrecord $(ROOTFS_DIR)/usr/etc/lircd.conf
