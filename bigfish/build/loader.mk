#----------------------------------------------------------------------
# Compile Loader
#----------------------------------------------------------------------
include $(CLEAR_VARS)
TARGET_LOADER_ROOT_OUT=$(PRODUCT_OUT)/loader_root
LOADER_OUT := $(TARGET_OUT_INTERMEDIATES)/LOADER_OBJ
LOADER_IMAGE := $(LOADER_OUT)/loader.img

recovery_root_for_loader: \
		$(INSTALLED_RAMDISK_TARGET) \
		$(RECOVERY_BINARY) \
		$(RECOVERY_INITRC) \
		$(RECOVERY_BUILD_PROP) \
		$(RECOVERY_RESOURCES_DEPS) \
		$(RECOVERY_FSTAB)
	@echo ----- Making recovery image ------
	$(hide) rm -rf $(TARGET_RECOVERY_OUT)
	$(hide) mkdir -p $(TARGET_RECOVERY_OUT)
	$(hide) mkdir -p $(TARGET_RECOVERY_ROOT_OUT)/etc
	$(hide) mkdir -p $(TARGET_RECOVERY_ROOT_OUT)/tmp
	$(hide) cp -a $(TARGET_ROOT_OUT) $(TARGET_RECOVERY_OUT)
	$(hide) rm -f $(TARGET_RECOVERY_ROOT_OUT)/init*.rc
	$(hide) rm -f $(TARGET_RECOVERY_ROOT_OUT)/ueventd.goldfish.rc
	$(hide) cp -a $(RECOVERY_INITRC) $(TARGET_RECOVERY_ROOT_OUT)/
	$(hide) cp -a $(RECOVERY_BINARY) $(TARGET_RECOVERY_ROOT_OUT)/sbin/
	$(hide) cp -a $(RECOVERY_RESOURCES_COMMON) $(TARGET_RECOVERY_ROOT_OUT)/
	$(hide) $(foreach item,$(RECOVERY_RESOURCES_PRIVATE), \
	  cp -af $(item) $(TARGET_RECOVERY_ROOT_OUT)/)
	$(hide) $(foreach item,$(RECOVERY_FSTAB), \
	  cp -f $(item) $(TARGET_RECOVERY_ROOT_OUT)/etc/recovery.fstab)
	$(hide) cat $(INSTALLED_DEFAULT_PROP_TARGET) $(RECOVERY_BUILD_PROP) \
	        > $(TARGET_RECOVERY_ROOT_OUT)/default.prop

loader_root: recovery_root_for_loader
	$(hide) rm  -rf $(TARGET_LOADER_ROOT_OUT)
	$(hide) mkdir -p $(TARGET_LOADER_ROOT_OUT)
	$(hide) cp  -af $(PRODUCT_OUT)/recovery/root/* $(TARGET_LOADER_ROOT_OUT)/
	$(hide) cp   $(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/upgrade/loader/etc/init.rc $(TARGET_LOADER_ROOT_OUT)/
	$(hide) cp   $(PRODUCT_OUT)/system/bin/busybox  $(TARGET_LOADER_ROOT_OUT)/sbin/
	$(hide) cp   $(PRODUCT_OUT)/system/bin/loader_recovery  $(TARGET_LOADER_ROOT_OUT)/sbin/
	$(hide) rm  -r $(TARGET_LOADER_ROOT_OUT)/sbin/recovery
	
loader_prepare: loader_root
	mkdir -p $(LOADER_OUT)
	$(MAKE) -C $(HISI_KERNEL_SOURCE) distclean
	echo "build loader config: KERNEL_CONFIG=$(ANDROID_KERNEL_CONFIG)"
	cd $(SDK_DIR);$(MAKE) linux_prepare SDK_CFGFILE=$(SDK_CFGFILE); cd -;
	
loader_config: loader_prepare
	if [ -f $(LOADER_OUT)/.config ]; then \
	echo "Attention:$(LOADER_OUT)/.config exist"; \
	echo "make loader_config: Nothing to be done!"; \
	else \
	$(MAKE) -C $(HISI_KERNEL_SOURCE) \
	SDK_CFGFILE=$(SDK_CFGFILE) \
	O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/LOADER_OBJ \
	ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- \
	$(ANDROID_KERNEL_CONFIG); \
	fi
	
loader_menuconfig: loader_config
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/LOADER_OBJ \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- menuconfig
		
$(LOADER_IMAGE): loader_config $(INSTALLED_RAMDISK_TARGET) | $(ACP)
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/LOADER_OBJ \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- \
		CONFIG_MSP=y \
		CONFIG_INITRAMFS_SOURCE=$(ANDROID_BUILD_TOP)/$(TARGET_LOADER_ROOT_OUT) \
		-j 128 uImage
	$(hide) cp -avf $(LOADER_OUT)/arch/arm/boot/uImage $@
	$(hide) chmod a+r $@
	cp -avf $@ $(EMMC_PRODUCT_OUT)
.PHONY: loaderimg $(LOADER_IMAGE)
loaderimg: $(LOADER_IMAGE)
#----------------------------------------------------------------------
# Loader End
#----------------------------------------------------------------------
