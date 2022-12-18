################################################################################
#    ./Makefile
#    Create By CaiZhiYong
#    2011.06.19
#
######################export val################################################
#  CFG_HI_KERNEL_VERSION
#  CFG_HI_KERNEL_CFG
#  CROSS_COMPILE
#######################inside val###############################################
#  PREFIX
#  CROSS_COMPILE
#  OUTPUT_DIR
#  KERNEL
#  OUTPUT_DIR
#  KERNEL_CONFIG

ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../..
include $(SDK_DIR)/base.mak
endif

PREFIX          := $(shell pwd)
OUTPUT_DIR      := $(PUB_DIR)
KERNEL          := $(CFG_HI_KERNEL_VERSION)
KERNEL_CONFIG   := $(CFG_HI_KERNEL_CFG)

CFG_MSP  := $(CFG_HI_MSP_BUILDIN)
CFG_FS_BUILDIN := $(CFG_HI_FS_BUILDIN)

SATA_SUPPORT := y

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv400 hi3718mv100 hi3719mv100 hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100),)
SATA_SUPPORT := n
endif

################################################################################

BUILD_DIR        := $(shell pwd)/$(KERNEL)

################################################################################

KERNEL_PATCH_DIR ?= $(shell pwd)/$(KERNEL).patch

ifdef CFG_HI_ADVCA_FUNCTION
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
INITRAMFS_SOURCE = $(shell pwd)/initramfs.cpio.gz
endif
else
INITRAMFS_SOURCE = $(ROOTBOX_DIR)
endif

###############################################################################
# TVP Config                                                                  #
###############################################################################
ifeq ($(CFG_HI_TVP_SUPPORT),y)
SECURITY_FLAGS := CONFIG_SUPPORT_CA=y CONFIG_CA_RUNTIME_CHECK=y CONFIG_CA_WARKUP_CHECK=y CONFIG_SECURE_EXTENSION=y CONFIG_TEE_DRIVER=y
SECURITY_CFLAGS := "-DCONFIG_SUPPORT_CA -DCONFIG_CA_RUNTIME_CHECK -DCONFIG_CA_WARKUP_CHECK -DCONFIG_SECURE_EXTENSION -DCONFIG_TEE_DRIVER"
SECURITY_AFLAGS := "-DCONFIG_SUPPORT_CA -DCONFIG_CA_RUNTIME_CHECK -DCONFIG_CA_WARKUP_CHECK -DCONFIG_SECURE_EXTENSION -DCONFIG_TEE_DRIVER"

EXTRA_FLAGS_KERNEL+=$(SECURITY_FLAGS)
CFLAGS_KERNEL+=$(SECURITY_CFLAGS)
AFLAGS_KERNEL+=$(SECURITY_AFLAGS)
endif
###############################################################################

all: $(PREFIX)/hi_kernel.bin

$(PREFIX)/hi_kernel.bin: $(BUILD_DIR)/arch/arm/boot/uImage
	cp -fv $(BUILD_DIR)/arch/arm/boot/uImage $@

$(BUILD_DIR)/arch/arm/boot/uImage: prepare
	make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		CONFIG_MSP=$(CFG_MSP) \
		CONFIG_ADVCA=$(CFG_ADVCA) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) AFLAGS_KERNEL=$(AFLAGS_KERNEL) uImage
	make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		CONFIG_MSP=$(CFG_MSP) \
		CONFIG_ADVCA=$(CFG_ADVCA) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) AFLAGS_KERNEL=$(AFLAGS_KERNEL) modules

menuconfig: prepare
	make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		CONFIG_MSP=$(CFG_MSP) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) AFLAGS_KERNEL=$(AFLAGS_KERNEL) menuconfig

$(BUILD_DIR)/tar:
	@test -f $@ || test ! -f $(notdir $(@:/tar=)).tar.bz2 || tar -xjf $(notdir $(@:/tar=)).tar.bz2
	@rm -f $(BUILD_DIR)/.config
	@test ! -d $(KERNEL_PATCH_DIR) || cp -rf $(KERNEL_PATCH_DIR)/* $(BUILD_DIR)/
	@cp -fv $(BUILD_DIR)/include/linux/vinput.h $(MSP_DIR)/drv/include/hi_drv_vinput.h
	@touch $@

prepare: $(BUILD_DIR)/tar
ifeq ($(CFG_HI_MSP_BUILDIN),y)
	$(AT)(cd $(LINUX_DIR)/drivers && rm -rf common && ln -s $(COMMON_DIR)/drv ./common && cd -)
	$(AT)(cd $(LINUX_DIR)/drivers && rm -rf msp && ln -s $(MSP_DIR)/drv ./msp && cd -)
endif
	make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) AFLAGS_KERNEL=$(AFLAGS_KERNEL) $(KERNEL_CONFIG)

install: all
	@cp -fv $(PREFIX)/hi_kernel.bin $(OUTPUT_DIR)/image
	@test -d $(OUTPUT_DIR)/kmod/usb || mkdir -p $(OUTPUT_DIR)/kmod/usb
	-@cp -fv $(BUILD_DIR)/drivers/usb/host/*.ko $(OUTPUT_DIR)/kmod/usb
ifeq ($(SATA_SUPPORT),y)
	@test -d $(OUTPUT_DIR)/kmod/sata || mkdir -p $(OUTPUT_DIR)/kmod/sata
	-@cp -fv $(BUILD_DIR)/drivers/ata/*.ko $(OUTPUT_DIR)/kmod/sata
endif

ifdef CFG_HI_ADVCA_FUNCTION
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
$(INITRAMFS_SOURCE): force
	@rm -f $(INITRAMFS_SOURCE)
	@cd $(ROOTBOX_DIR) && \
            find . | cpio -o -H newc | gzip > $(INITRAMFS_SOURCE) && \
        cd -

force: ;

endif
endif

fs_buildin: prepare $(INITRAMFS_SOURCE)
	make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		CONFIG_MSP=$(CFG_MSP) \
		CONFIG_ADVCA=$(CFG_ADVCA) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) \
		AFLAGS_KERNEL=$(AFLAGS_KERNEL) \
		CONFIG_CC_OPTIMIZE_FOR_SIZE=$(CONFIG_CC_OPTIMIZE_FOR_SIZE) \
		CONFIG_INITRAMFS_SOURCE=$(INITRAMFS_SOURCE) \
		uImage
	@cp -fv $(BUILD_DIR)/arch/arm/boot/uImage $(PREFIX)/hi_kernel.bin
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	@cp -fv $(PREFIX)/hi_kernel.bin $(OUTPUT_DIR)/image/apploader.bin
	@rm -rf $(OUTPUT_DIR)/image/hi_kernel.bin
else
	@cp -fv $(PREFIX)/hi_kernel.bin $(OUTPUT_DIR)/image/
endif

uninstall:
	-@rm -rf $(OUTPUT_DIR)/kmod/usb/*.ko
	-@rm -rf $(OUTPUT_DIR)/kmod/sata/*.ko
	-@rm -rf $(OUTPUT_DIR)/image/hi_kernel.bin
	-@rm -rf $(OUTPUT_DIR)/image/apploader.bin

################################################################################

distclean: clean
	@test ! -d $(BUILD_DIR) || make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) \
		AFLAGS_KERNEL=$(AFLAGS_KERNEL) distclean

clean:
	@test ! -d $(BUILD_DIR) || test ! -f $(shell pwd)/$(KERNEL).tar.bz2 \
		|| test ! -d $(KERNEL_PATCH_DIR) || rm -rf $(BUILD_DIR)
	@test ! -d $(BUILD_DIR) || make -C $(BUILD_DIR) ARCH=arm \
		CROSS_COMPILE=$(CROSS_COMPILE) \
		$(EXTRA_FLAGS_KERNEL) \
		CFLAGS_KERNEL=$(CFLAGS_KERNEL) \
		AFLAGS_KERNEL=$(AFLAGS_KERNEL) clean
	@test ! -f $(PREFIX)/hi_kernel.bin || rm -rf  $(PREFIX)/hi_kernel.bin
ifdef CFG_HI_ADVCA_FUNCTION
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	@test ! -f $(INITRAMFS_SOURCE) || rm -f $(INITRAMFS_SOURCE)
endif
endif

################################################################################
.PHONY: clean distclean prepare
################################################################################
