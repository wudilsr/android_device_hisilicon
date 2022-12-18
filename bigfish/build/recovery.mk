#----------------------------------------------------------------------
# Compile Recovery Kernel
#----------------------------------------------------------------------

# If neither TARGET_NO_KERNEL nor TARGET_NO_RECOVERY are false
ifeq (,$(filter false, $(TARGET_NO_RECOVERY) $(BUILD_TINY_ANDROID)))
include $(CLEAR_VARS)

RECOVERY_OUT := $(TARGET_OUT_INTERMEDIATES)/RECOVERY_OBJ
RECOVERY_IMAGE := $(RECOVERY_OUT)/recovery.img

RECOVERY_INITRC := $(call include-path-for, recovery)/etc/init.rc
RECOVERY_BUILD_PROP := $(TARGET_OUT)/build.prop
RECOVERY_BINARY := $(call intermediates-dir-for,EXECUTABLES,recovery)/recovery
RECOVERY_RESOURCES_COMMON := $(call include-path-for, recovery)/res
RECOVERY_RESOURCES_PRIVATE := $(strip $(wildcard $(TARGET_DEVICE_DIR)/recovery/res))
RECOVERY_RESOURCES_DEPS := $(shell find $(RECOVERY_RESOURCES_COMMON) \
  $(RECOVERY_RESOURCES_PRIVATE) -type f)
RECOVERY_FSTAB := $(call include-path-for, recovery)/etc/recovery.fstab
RECOVERY_EMMC_FSTAB := $(call include-path-for, recovery)/etc/recovery.emmc.fstab


recovery_prepare:
	mkdir -p $(RECOVERY_OUT)
	mkdir -p $(EMMC_PRODUCT_OUT)
	mkdir -p $(NAND_PRODUCT_OUT)
	$(MAKE) -C $(HISI_KERNEL_SOURCE) distclean
	echo "build recovery config: KERNEL_CONFIG=$(RECOVERY_KERNEL_CONFIG)"
	cd $(SDK_DIR);$(MAKE) linux_prepare SDK_CFGFILE=$(SDK_CFG_DIR)/$(HISI_SDK_RECOVERY_CFG); cd -;

recovery_config: recovery_prepare
	if [ -f $(RECOVERY_OUT)/.config ]; then \
	echo "Attention:$(RECOVERY_OUT)/.config exist"; \
	echo "make recovery_config: Nothing to be done!"; \
	else \
	$(MAKE) -C $(HISI_KERNEL_SOURCE) \
	SDK_CFGFILE=$(SDK_CFG_DIR)/$(HISI_SDK_RECOVERY_CFG) \
	O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/RECOVERY_OBJ \
	ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- \
	$(RECOVERY_KERNEL_CONFIG); \
	fi

recovery_menuconfig: recovery_config
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/RECOVERY_OBJ \
		SDK_CFGFILE=$(SDK_CFG_DIR)/$(HISI_SDK_RECOVERY_CFG) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- menuconfig

RECOVERY_INSTALL_KEYS := \
    $(call intermediates-dir-for,PACKAGING,recovery_keys)/keys
RECOVERY_DUMPKEY_JAR := $(HOST_OUT_JAVA_LIBRARIES)/dumpkey.jar

DEFAULT_PUBLIC_KEYS := $(DEFAULT_SYSTEM_DEV_CERTIFICATE).x509.pem

$(RECOVERY_INSTALL_KEYS): PRIVATE_PUBLIC_KEYS := $(DEFAULT_PUBLIC_KEYS)
$(RECOVERY_INSTALL_KEYS): recovery_extra_keys := $(patsubst %,%.x509.pem,$(PRODUCT_EXTRA_RECOVERY_KEYS))
$(RECOVERY_INSTALL_KEYS): $(DEFAULT_PUBLIC_KEYS) $(RECOVERY_DUMPKEY_JAR) $(recovery_extra_keys)
	@echo "DumpPublicKey: $@ <= $(PRIVATE_PUBLIC_KEYS) $(extra_keys)"
	@rm -rf $@
	@mkdir -p $(dir $@)
	@echo "recovery_extra_keys :$(recovery_extra_keys)"
	@echo "PRIVATE_PUBLIC_KEYS :$(PRIVATE_PUBLIC_KEYS)"
	java -jar $(RECOVERY_DUMPKEY_JAR) $(PRIVATE_PUBLIC_KEYS) $(recovery_extra_keys) > $@

$(RECOVERY_IMAGE): \
		recovery_config \
		$(INSTALLED_RAMDISK_TARGET) \
		$(RECOVERY_BINARY) \
		$(RECOVERY_INITRC) \
		$(RECOVERY_BUILD_PROP) \
		$(RECOVERY_RESOURCES_DEPS) \
		$(RECOVERY_FSTAB) \
		$(RECOVERY_EMMC_FSTAB) \
		$(RECOVERY_INSTALL_KEYS)
	@echo ----- Making recovery image ------
	$(hide) rm -rf $(TARGET_RECOVERY_OUT)
	$(hide) mkdir -p $(TARGET_RECOVERY_OUT)
	$(hide) mkdir -p $(TARGET_RECOVERY_ROOT_OUT)/etc
	$(hide) mkdir -p $(TARGET_RECOVERY_ROOT_OUT)/tmp
	$(hide) cp -a $(TARGET_ROOT_OUT) $(TARGET_RECOVERY_OUT)
	$(hide) rm -f $(TARGET_RECOVERY_ROOT_OUT)/file_contexts
	$(hide) rm -f $(TARGET_RECOVERY_ROOT_OUT)/init*.rc
	$(hide) rm -f $(TARGET_RECOVERY_ROOT_OUT)/ueventd.goldfish.rc
	$(hide) cp -a $(RECOVERY_INITRC) $(TARGET_RECOVERY_ROOT_OUT)/
	$(hide) cp -a $(RECOVERY_BINARY) $(TARGET_RECOVERY_ROOT_OUT)/sbin/
	$(hide) cp -a $(RECOVERY_RESOURCES_COMMON) $(TARGET_RECOVERY_ROOT_OUT)/
	$(hide) cp -a $(RECOVERY_INSTALL_KEYS) $(TARGET_RECOVERY_ROOT_OUT)/res
	$(hide) $(foreach item,$(RECOVERY_RESOURCES_PRIVATE), \
	  cp -af $(item) $(TARGET_RECOVERY_ROOT_OUT)/)
	$(hide) $(foreach item,$(RECOVERY_FSTAB), \
	  cp -f $(item) $(TARGET_RECOVERY_ROOT_OUT)/etc/recovery.fstab)
	$(hide) $(foreach item,$(RECOVERY_EMMC_FSTAB), \
	  cp -f $(item) $(TARGET_RECOVERY_ROOT_OUT)/etc/recovery.emmc.fstab)
	$(hide) cat $(INSTALLED_DEFAULT_PROP_TARGET) $(RECOVERY_BUILD_PROP) \
	        > $(TARGET_RECOVERY_ROOT_OUT)/default.prop
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/RECOVERY_OBJ \
		SDK_CFGFILE=$(SDK_CFG_DIR)/$(HISI_SDK_RECOVERY_CFG) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- \
		CONFIG_MSP=y \
		CONFIG_INITRAMFS_SOURCE=$(ANDROID_BUILD_TOP)/$(TARGET_RECOVERY_ROOT_OUT) \
		-j 128 uImage
	$(hide) cp -avf $(RECOVERY_OUT)/arch/arm/boot/uImage $@
	$(hide) chmod a+r $@
	cp -avf $@ $(NAND_PRODUCT_OUT)
	cp -avf $@ $(EMMC_PRODUCT_OUT)

endif

.PHONY: recoveryimg $(RECOVERY_IMAGE)
recoveryimg: $(RECOVERY_IMAGE)

#----------------------------------------------------------------------
# Recovery Kernel End
#----------------------------------------------------------------------
