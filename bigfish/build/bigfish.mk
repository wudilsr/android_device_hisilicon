INSTALLED_BOOTIMAGE_TARGET :=$(PRODUCT_OUT)/boot.img
INSTALLED_RAMDISK_TARGET := $(PRODUCT_OUT)/ramdisk.img
INSTALLED_USERDATAIMAGE_TARGET := $(PRODUCT_OUT)/userdata.img
INSTALLED_SYSTEMIMAGE := $(PRODUCT_OUT)/system.img
INSTALLED_CACHEIMAGE_TARGET := $(PRODUCT_OUT)/cache.img
INSTALLED_SDCARDIMAGE_TARGET := $(PRODUCT_OUT)/sdcard.img
INSTALLED_PRIVATEIMAGE_TARGET := $(PRODUCT_OUT)/private.img

TARGET_OUT_SDCARD:=$(PRODUCT_OUT)/sdcard
TARGET_OUT_PRIVATE:=$(PRODUCT_OUT)/private
EMMC_PRODUCT_OUT := $(PRODUCT_OUT)/Emmc
UPDATE_TOOLS :=$(HOST_OUT_EXECUTABLES)/bsdiff \
               $(HOST_OUT_EXECUTABLES)/fs_config

# kernel
-include device/hisilicon/bigfish/build/kernel.mk
# loader
-include device/hisilicon/bigfish/build/loader.mk
# recovery
-include device/hisilicon/bigfish/build/recovery.mk
# ubi
-include device/hisilicon/bigfish/build/ubi.mk
# ext4
-include device/hisilicon/bigfish/build/ext4.mk
# emmc
-include device/hisilicon/bigfish/build/emmc.mk
# bootargs
-include device/hisilicon/bigfish/build/bootargs.mk
# hipro
-include device/hisilicon/bigfish/build/hipro.mk

# hiboot
.PHONY: hiboot
hiboot: $(EMMC_HIBOOT_IMG)
# prebuilt
.PHONY:prebuilt
prebuilt: $(EMMC_PREBUILT_IMG)
#----------------------------------------------------------------------
# Full Compile
#----------------------------------------------------------------------

RECORVERY_OR_APPLOADER_TARGET := recoveryimg

.PHONY: bigfish
bigfish: prebuilt hiboot kernel ubifs ext4fs $(RECORVERY_OR_APPLOADER_TARGET)
#----------------------------------------------------------------------
# Full Compile End
#----------------------------------------------------------------------

