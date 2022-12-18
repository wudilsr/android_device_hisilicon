################################################################################
#  Copyright (C) 2014 Hisilicon STB Development Dept
#  All rights reserved.
#  Create by zyxing
#
################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../../..
include $(SDK_DIR)/base.mak
endif

HOST            := $(patsubst %-,%,$(CROSS_COMPILE))
EXFAT_DIR       ?= $(COMPONENT_DIR)/exfat
PREFIX          ?= $(shell pwd)/rootfs
BUILD_DIR       := $(shell pwd)/tmp
STRIP           := $(CROSS_COMPILE)strip
EXFAT_UTILS     := exfat-utils-0.9.7
FUSE_EXFAT      := fuse-exfat-0.9.7
LIBFUSE         := fuse-2.9.3

exFAT-utils-tgt :=  usr/sbin/dumpexfat  \
                    usr/sbin/exfatfsck  \
                    usr/sbin/exfatlabel \
                    usr/sbin/mkexfatfs

exFAT_fuse_tgt  := usr/sbin/mount.exfat-fuse

TARGET := $(addprefix $(BUILD_DIR)/, $(exFAT-utils-tgt) $(exFAT_fuse_tgt))

USR_SBIN_DIR := $(ROOTFS_DIR)/usr/sbin

install: all
	$(AT)mkdir -p $(USR_SBIN_DIR)
	$(AT)cp -rf $(PREFIX)/usr/sbin/exfatfsck $(USR_SBIN_DIR)/fsck.exfat
	$(AT)cp -rf $(PREFIX)/usr/sbin/mkexfatfs $(USR_SBIN_DIR)/mkfs.exfat
	$(AT)cp -rf $(PREFIX)/usr/sbin/dumpexfat $(USR_SBIN_DIR)/dump.exfat
	$(AT)cp -rf $(PREFIX)/usr/sbin/mount.exfat-fuse $(USR_SBIN_DIR)/mount.exfat

all: exfat

exfat: fuse-exfat exfat-utils
	$(AT)test -d $(PREFIX)/usr/sbin || mkdir -p $(PREFIX)/usr/sbin
	$(foreach file, $(TARGET), $(STRIP) $(file);)
	$(foreach file, $(TARGET), install -v -t $(PREFIX)/usr/sbin $(file);)

################################################################################
fuse-exfat: $(BUILD_DIR)/lib/libfuse.a $(BUILD_DIR)/$(FUSE_EXFAT)/tar
	cd $(BUILD_DIR)/$(FUSE_EXFAT) && \
		make -j 16 CROSS_COMPILE=$(CROSS_COMPILE) FUSE_PATH="$(BUILD_DIR)" && \
		make install CROSS_COMPILE=$(CROSS_COMPILE) PREFIX=$(BUILD_DIR) && \
	cd -

exfat-utils: $(BUILD_DIR)/$(EXFAT_UTILS)/tar
	cd $(BUILD_DIR)/$(EXFAT_UTILS) && \
		make -j 16 CROSS_COMPILE=$(CROSS_COMPILE) && \
		make install CROSS_COMPILE=$(CROSS_COMPILE) PREFIX=$(BUILD_DIR) && \
	cd -

$(BUILD_DIR)/lib/libfuse.a: $(BUILD_DIR)/$(LIBFUSE)/tar
	cd $(BUILD_DIR)/$(LIBFUSE) && \
		./configure --host=$(HOST) --prefix=$(BUILD_DIR) --enable-static=yes\
			CFLAGS="-DGLIBC_VERSION" DESTDIR=$(BUILD_DIR) \
			MOUNT_FUSE_PATH=$(BUILD_DIR)/sbin \
			INIT_D_PATH=$(BUILD_DIR)/etc/init.d \
			UDEV_RULES_PATH=$(BUILD_DIR)/etc/udev/rules.d && \
		make -j 16 && \
		make install && \
	cd -

$(BUILD_DIR)/$(FUSE_EXFAT)/tar:
	$(AT)test -d $(BUILD_DIR) || mkdir -p $(BUILD_DIR)
	$(AT)tar -xf $(notdir $(@:/tar=)).tar.gz -C $(BUILD_DIR)
	$(AT)touch $@
	$(AT)cp -fv Makefile.fuse-exfat $(BUILD_DIR)/$(FUSE_EXFAT)/Makefile

$(BUILD_DIR)/$(EXFAT_UTILS)/tar:
	$(AT)test -d $(BUILD_DIR) || mkdir -p $(BUILD_DIR)
	$(AT)tar -xf $(notdir $(@:/tar=)).tar.gz -C $(BUILD_DIR)
	$(AT)touch $@
	$(AT)cp -fv Makefile.exfat-utils $(BUILD_DIR)/$(EXFAT_UTILS)/Makefile

$(BUILD_DIR)/$(LIBFUSE)/tar:
	$(AT)test -d $(BUILD_DIR) || mkdir -p $(BUILD_DIR)
	$(AT)tar -xf $(notdir $(@:/tar=)).tar.gz -C $(BUILD_DIR)
	$(AT)touch $@

clean:
	$(AT)rm -rf $(BUILD_DIR) $(PREFIX)

uninstall:
	$(AT)rm -rf $(USR_SBIN_DIR)/fsck.exfat $(USR_SBIN_DIR)/mkfs.exfat \
                $(USR_SBIN_DIR)/dump.exfat $(USR_SBIN_DIR)/mount.exfat

################################################################################
.PHONY: all clean install uninstall
################################################################################