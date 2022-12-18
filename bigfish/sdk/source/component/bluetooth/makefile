#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../../..
include $(SDK_DIR)/base.mak
endif

BLUETOOTH_DIR = $(COMPONENT_DIR)/bluetooth
BLUEZ_API_DIR = $(BLUETOOTH_DIR)/hi_api

#===============================================================================
# local variable
#===============================================================================

#===============================================================================
# rules
#===============================================================================
.PHONY : all clean install uninstall

all :
	$(AT)cd $(BLUETOOTH_DIR)/src;tar -zxf bluez_install.tar.gz;chmod 777 -R install;cd -
	$(AT)echo "tar -zxf bluez_install.tar.gz  done"
	$(AT)mkdir -p $(BLUETOOTH_DIR)/include && cp -rf $(BLUETOOTH_DIR)/src/install/include/* $(BLUETOOTH_DIR)/include
	$(AT)mkdir -p $(BLUETOOTH_DIR)/lib && cp -rf $(BLUETOOTH_DIR)/src/install/usr/share/bluetooth/lib/* $(BLUETOOTH_DIR)/lib
	$(AT)make -C $(BLUEZ_API_DIR)

clean:
	$(AT)make -C $(BLUEZ_API_DIR) clean
	$(AT)rm -rf $(BLUETOOTH_DIR)/lib/*
	$(AT)rm -rf $(BLUETOOTH_DIR)/include/*
	$(AT)rm -rf $(BLUETOOTH_DIR)/src/install

install: all
	$(AT)make -C $(BLUEZ_API_DIR) install
	$(AT)mkdir -p $(INCLUDE_DIR)/alsa_bluez
	$(AT)mkdir -p $(SHARED_LIB_DIR)/alsa_bluez
	$(AT)cp -rf $(BLUETOOTH_DIR)/src/install/include/* $(INCLUDE_DIR)/alsa_bluez
	$(AT)cp -rf $(BLUETOOTH_DIR)/src/install/usr/share/bluetooth/lib/* $(SHARED_LIB_DIR)/alsa_bluez
	$(AT)mkdir -p $(ROOTFS_DIR)/etc && cp -rf $(BLUETOOTH_DIR)/src/install/etc/* $(ROOTFS_DIR)/etc
	$(AT)cp -rf $(BLUETOOTH_DIR)/src/install/kmod/* $(MODULE_DIR)
	$(AT)for aaa in $$(find $(BLUETOOTH_DIR)/src/install/usr/share/bluetooth/lib -name "*.a");do rm -rf $$aaa;done
	$(AT)mkdir -p $(ROOTFS_DIR)/usr && cp -rf $(BLUETOOTH_DIR)/src/install/usr/* $(ROOTFS_DIR)/usr

uninstall:
	$(AT)make -C $(BLUEZ_API_DIR) uninstall
	$(AT)rm -rf $(INCLUDE_DIR)/alsa_bluez
	$(AT)rm -rf $(SHARED_LIB_DIR)/alsa_bluez
	$(AT)rm -rf $(MODULE_DIR)/bluetoothd_server $(MODULE_DIR)/bluez_init
	$(AT)rm -rf $(ROOTFS_DIR)/etc/asound.conf $(ROOTFS_DIR)/etc/bluez_init \
                $(ROOTFS_DIR)/etc/group $(ROOTFS_DIR)/etc/passwd
