# ---------------------------------------------------------------------
# EXT4 Images Begin
# ---------------------------------------------------------------------

include $(CLEAR_VARS)
EXT4_IMG :=ext4img
MAKE_EXT4FS_TOOLS := $(HOST_OUT_EXECUTABLES)/make_ext4fs
$(EXT4_IMG):$(INSTALLED_SYSTEMIMAGE) $(INSTALLED_USERDATAIMAGE_TARGET) $(INSTALLED_CACHEIMAGE_TARGET)
ifeq ($(SUPPORT_SDCARDFS),true)
	mkdir -p $(TARGET_OUT_PRIVATE)
	$(MAKE_EXT4FS_TOOLS) -s -l $(BOARD_PRIVATEIMAGE_PARTITION_SIZE) -a private $(INSTALLED_PRIVATEIMAGE_TARGET) $(TARGET_OUT_PRIVATE)
	cp -r $(PRODUCT_OUT)/system.img $(EMMC_PRODUCT_OUT)/system.ext4
	cp -r $(PRODUCT_OUT)/userdata.img $(EMMC_PRODUCT_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(EMMC_PRODUCT_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/private.img $(EMMC_PRODUCT_OUT)/private.ext4
ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
ifneq ($(strip $(HISILICON_SECURITY_L3)),true)
	cp -r $(PRODUCT_OUT)/userdata.img $(SECURITY_PRODUCTION_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(SECURITY_PRODUCTION_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/userdata.img $(SECURITY_MAINTAIN_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(SECURITY_MAINTAIN_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/private.img $(SECURITY_MAINTAIN_OUT)/private.ext4
endif
endif
else
	mkdir -p $(TARGET_OUT_SDCARD)
	mkdir -p $(TARGET_OUT_PRIVATE)
ifeq ($(strip $(SUPPORT_REMOTE_RECOVERY)), true)
	mkdir -p $(TARGET_OUT_BACKUP)
	$(MAKE_EXT4FS_TOOLS) -s -l $(BOARD_BACKUPIMAGE_PARTITION_SIZE) -a backup $(INSTALLED_BACKUPIMAGE_TARGET) $(TARGET_OUT_BACKUP)
endif

	$(MAKE_EXT4FS_TOOLS) -s -l $(BOARD_SDCARDIMAGE_PARTITION_SIZE) -a sdcard $(INSTALLED_SDCARDIMAGE_TARGET) $(TARGET_OUT_SDCARD)
	$(MAKE_EXT4FS_TOOLS) -s -l $(BOARD_PRIVATEIMAGE_PARTITION_SIZE) -a private $(INSTALLED_PRIVATEIMAGE_TARGET) $(TARGET_OUT_PRIVATE)
	cp -r $(PRODUCT_OUT)/system.img $(EMMC_PRODUCT_OUT)/system.ext4
	cp -r $(PRODUCT_OUT)/userdata.img $(EMMC_PRODUCT_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(EMMC_PRODUCT_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/sdcard.img $(EMMC_PRODUCT_OUT)/sdcard.ext4
	cp -r $(PRODUCT_OUT)/private.img $(EMMC_PRODUCT_OUT)/private.ext4
ifeq ($(strip $(SUPPORT_REMOTE_RECOVERY)), true)
	cp -r $(PRODUCT_OUT)/backup.img $(EMMC_PRODUCT_OUT)/backup.ext4
endif
ifeq ($(strip $(HISILICON_TEE)),true)
	mkdir -p $(TARGET_OUT_SECURESTORE)
	$(MAKE_EXT4FS_TOOLS) -s -l $(BOARD_SECURESTORE_PARTITION_SIZE) -a securestore  $(INSTALLED_SECURESTOREIMAGE_TARGET) $(TARGET_OUT_SECURESTORE)
	cp -r $(PRODUCT_OUT)/securestore.img $(EMMC_PRODUCT_OUT)/securestore.ext4
endif
ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
ifneq ($(strip $(HISILICON_SECURITY_L3)),true)
	cp -r $(PRODUCT_OUT)/userdata.img $(SECURITY_PRODUCTION_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(SECURITY_PRODUCTION_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/sdcard.img $(SECURITY_PRODUCTION_OUT)/sdcard.ext4
	cp -r $(PRODUCT_OUT)/userdata.img $(SECURITY_MAINTAIN_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(SECURITY_MAINTAIN_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/sdcard.img $(SECURITY_MAINTAIN_OUT)/sdcard.ext4
	cp -r $(PRODUCT_OUT)/private.img $(SECURITY_MAINTAIN_OUT)/private.ext4
ifeq ($(strip $(SUPPORT_REMOTE_RECOVERY)), true)
	cp -r $(PRODUCT_OUT)/backup.img $(SECURITY_MAINTAIN_OUT)/backup.ext4
endif
endif
endif
endif
.PHONY: ext4fs
ext4fs: $(EXT4_IMG)
# ---------------------------------------------------------------------
# EXT4 Images end
# ---------------------------------------------------------------------
