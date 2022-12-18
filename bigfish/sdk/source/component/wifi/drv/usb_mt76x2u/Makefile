#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../../../../..
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
BUILD_DIR  := $(shell pwd)/tmp
ifneq ($(ANDROID_BUILD),y)
INSTALL_DIR := $(MODULE_DIR)
CFG_INSTALL_DIR := $(ROOTFS_DIR)/etc/Wireless/RT2870STA
else
INSTALL_DIR := $(ANDROID_PRODUCT_OUT)/system/lib/modules
BIN_INSTALL_DIR := $(ANDROID_PRODUCT_OUT)/system/etc/firmware
PREALLOC_INSTALL_DIR := $(ANDROID_PRODUCT_OUT)/system/lib/modules/mtprealloc76x2Usta.ko
CFG_INSTALL_DIR := $(ANDROID_PRODUCT_OUT)/system/etc/Wireless/RT2870STA
endif

MODULE_SRC := mt76x2u_MP1.9
MODULE := mt7662u_sta.ko mtprealloc.ko
MODULE_PATH := $(BUILD_DIR)/$(MODULE_SRC)/os/linux/mt7662u_sta.ko
PREALLOC_MODULE_PATH := $(BUILD_DIR)/$(MODULE_SRC)/os/linux/mtprealloc.ko
MODULE_CFG := MT76x2STA.dat mt7662_patch_e3_hdr.bin mt7662_firmware_e3_tvbox.bin
MODULE_CFG_PATH := $(BUILD_DIR)/$(MODULE_SRC)/conf/MT76x2STA.dat
MODULE_BIN_PATH := $(BUILD_DIR)/$(MODULE_SRC)/mcu/bin/mt7662_patch_e3_hdr.bin \
                   $(BUILD_DIR)/$(MODULE_SRC)/mcu/bin/mt7662_firmware_e3_tvbox.bin

BUILD_MODULES = $(patsubst %,%_build,${MODULE_SRC})
UNINSTALL_MODULES = $(patsubst %,%_uninstall,${MODULE})

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall
all: $(BUILD_MODULES)

clean:
	@rm -rf $(BUILD_DIR)

install: all
	@test -d $(INSTALL_DIR) || mkdir -p $(INSTALL_DIR)
	@cp -v $(MODULE_PATH) $(INSTALL_DIR)/
	@cp -v $(PREALLOC_MODULE_PATH) $(PREALLOC_INSTALL_DIR)
	@test -d $(CFG_INSTALL_DIR) || mkdir -p $(CFG_INSTALL_DIR)
	@cp -v $(MODULE_CFG_PATH) $(CFG_INSTALL_DIR)/
	@test -d $(BIN_INSTALL_DIR) || mkdir -p $(BIN_INSTALL_DIR)
	@cp -v $(MODULE_BIN_PATH) $(BIN_INSTALL_DIR)/

uninstall: $(UNINSTALL_MODULES)
	@rm -f $(CFG_INSTALL_DIR)/$(MODULE_CFG)

#==================================================================
#                          modules
#==================================================================
%_build: $(BUILD_DIR)
	@echo -e "\033[31m""Build $(patsubst %_build,%,$@) ...""\033[00m"
	@test -d $(BUILD_DIR)/$(patsubst %_build,%,$@) \
		|| tar -zxf $(patsubst %_build,%,$@).tar.gz -C $(BUILD_DIR)
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) LINUX_SRC=$(LINUX_DIR) \
		-C $(BUILD_DIR)/$(patsubst %_build,%,$@)

$(BUILD_DIR):
	@test -d $(BUILD_DIR) || mkdir -p $(BUILD_DIR)

%_uninstall:
	@rm -f $(INSTALL_DIR)/$(patsubst %_uninstall,%,$@)
