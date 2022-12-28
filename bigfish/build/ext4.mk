# ---------------------------------------------------------------------
# EXT4 Images Begin
# ---------------------------------------------------------------------

include $(CLEAR_VARS)
EXT4_IMG :=ext4img
MAKE_EXT4FS_TOOLS := $(HOST_OUT_EXECUTABLES)/make_ext4fs
$(EXT4_IMG):$(INSTALLED_SYSTEMIMAGE) $(INSTALLED_USERDATAIMAGE_TARGET) $(INSTALLED_CACHEIMAGE_TARGET)
	mkdir -p $(TARGET_OUT_PRIVATE)
	$(MAKE_EXT4FS_TOOLS) -s -l $(BOARD_PRIVATEIMAGE_PARTITION_SIZE) -a private $(INSTALLED_PRIVATEIMAGE_TARGET) $(TARGET_OUT_PRIVATE)
	cp -r $(PRODUCT_OUT)/system.img $(EMMC_PRODUCT_OUT)/system.ext4
	cp -r $(PRODUCT_OUT)/userdata.img $(EMMC_PRODUCT_OUT)/userdata.ext4
	cp -r $(PRODUCT_OUT)/cache.img $(EMMC_PRODUCT_OUT)/cache.ext4
	cp -r $(PRODUCT_OUT)/private.img $(EMMC_PRODUCT_OUT)/private.ext4
.PHONY: ext4fs
ext4fs: $(EXT4_IMG)
# ---------------------------------------------------------------------
# EXT4 Images end
# ---------------------------------------------------------------------
