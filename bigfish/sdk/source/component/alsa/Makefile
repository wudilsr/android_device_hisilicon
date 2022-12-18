#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

ALSA_DIR := $(COMPONENT_DIR)/alsa

#===============================================================================
# local variable
#===============================================================================

#===============================================================================
# rules
#===============================================================================
.PHONY : all clean install uninstall

all :
	$(AT)cd $(ALSA_DIR)/src;tar -zxf alsa_install.tar.gz;chmod 777 -R install;cd -
	$(AT)echo "tar -zxf alsa_install.tar.gz  done"
	$(AT)-cp -r $(ALSA_DIR)/src/install/include/* $(ALSA_DIR)/include
	$(AT)-cp -r $(ALSA_DIR)/src/install/usr/share/bluetooth/lib/* $(ALSA_DIR)/lib

clean:
	$(AT)rm -rf $(ALSA_DIR)/lib/*
	$(AT)rm -rf $(ALSA_DIR)/include/*
	$(AT)rm -rf $(ALSA_DIR)/src/install

install: all
	$(AT)mkdir -p $(INCLUDE_DIR)/alsa_bluez
	$(AT)mkdir -p $(SHARED_LIB_DIR)/alsa_bluez
	$(AT)-cp -rf $(ALSA_DIR)/src/install/include/* $(INCLUDE_DIR)/alsa_bluez
	$(AT)-cp -rf $(ALSA_DIR)/src/install/usr/share/bluetooth/lib/* $(SHARED_LIB_DIR)/alsa_bluez
	$(AT)mkdir -p $(ROOTFS_DIR)/etc && cp -rf $(ALSA_DIR)/src/install/etc/* $(ROOTFS_DIR)/etc
	$(AT)for aaa in $$(find $(ALSA_DIR)/src/install/usr/share/bluetooth/lib -name "*.a");do rm -rf $$aaa;done
	$(AT)mkdir -p $(ROOTFS_DIR)/usr && cp -rf $(ALSA_DIR)/src/install/usr/* $(ROOTFS_DIR)/usr

uninstall:
	$(AT)rm -rf $(ROOTFS_DIR)/etc/asound.conf
