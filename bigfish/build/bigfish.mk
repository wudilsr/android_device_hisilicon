INSTALLED_BOOTIMAGE_TARGET :=$(PRODUCT_OUT)/boot.img
INSTALLED_RAMDISK_TARGET := $(PRODUCT_OUT)/ramdisk.img
INSTALLED_USERDATAIMAGE_TARGET := $(PRODUCT_OUT)/userdata.img
INSTALLED_SYSTEMIMAGE := $(PRODUCT_OUT)/system.img
INSTALLED_CACHEIMAGE_TARGET := $(PRODUCT_OUT)/cache.img
INSTALLED_SDCARDIMAGE_TARGET := $(PRODUCT_OUT)/sdcard.img
INSTALLED_PRIVATEIMAGE_TARGET := $(PRODUCT_OUT)/private.img
ifeq ($(strip $(SUPPORT_REMOTE_RECOVERY)),true)
INSTALLED_BACKUPIMAGE_TARGET := $(PRODUCT_OUT)/backup.img
endif
ifeq ($(strip $(HISILICON_TEE)),true)
INSTALLED_SECURESTOREIMAGE_TARGET := $(PRODUCT_OUT)/securestore.img
endif

TARGET_OUT_SDCARD:=$(PRODUCT_OUT)/sdcard
ifeq ($(strip $(SUPPORT_REMOTE_RECOVERY)),true)
TARGET_OUT_BACKUP:=$(PRODUCT_OUT)/backup
endif
TARGET_OUT_PRIVATE:=$(PRODUCT_OUT)/private
EMMC_PRODUCT_OUT := $(PRODUCT_OUT)/Emmc
ifeq ($(strip $(HISILICON_TEE)),true)
TARGET_OUT_SECURESTORE:=$(PRODUCT_OUT)/securestore
endif
UPDATE_TOOLS :=$(HOST_OUT_EXECUTABLES)/bsdiff \
               $(HOST_OUT_EXECUTABLES)/fs_config

ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
RELEASE_PEM_KEY := $(shell test -f device/hisilicon/${CHIPNAME}/security/releasekey.x509.pem && echo yes)
ifeq ($(RELEASE_PEM_KEY),yes)
$(warning device/hisilicon/${CHIPNAME}/security/releasekey.x509.pem have exist!)
else
$(error device/hisilicon/${CHIPNAME}/security/releasekey.x509.pem does not exist!)
endif

ifneq ($(strip $(HISILICON_SECURITY_L3)),true)
RELEASE_PK8_KEY := $(shell test -f device/hisilicon/${CHIPNAME}/security/releasekey.pk8 && echo yes)
ifeq ($(RELEASE_PK8_KEY),yes)
$(warning device/hisilicon/${CHIPNAME}/security/releasekey.pk8 have exist!)
else
$(error device/hisilicon/${CHIPNAME}/security/releasekey.pk8 does not exist!)
endif

ROOT_PRIV_KEY := $(shell test -f device/hisilicon/${CHIPNAME}/security/root_rsa_priv.txt && echo yes)
ifeq ($(ROOT_PRIV_KEY),yes)
$(warning device/hisilicon/${CHIPNAME}/security/root_rsa_priv.txt have exist!)
else
$(error device/hisilicon/${CHIPNAME}/security/root_rsa_priv.txt do not exist!)
endif

EXTERN_PRIV_KEY := $(shell test -f device/hisilicon/${CHIPNAME}/security/extern_rsa_priv.txt && echo yes)
ifeq ($(EXTERN_PRIV_KEY),yes)
$(warning device/hisilicon/${CHIPNAME}/security/extern_rsa_priv.txt have exist!)
else
$(error device/hisilicon/${CHIPNAME}/security/extern_rsa_priv.txt do not exist!)
endif

EXTERN_PUB_KEY := $(shell test -f device/hisilicon/${CHIPNAME}/security/extern_rsa_pub.txt && echo yes)
ifeq ($(EXTERN_PUB_KEY),yes)
$(warning device/hisilicon/${CHIPNAME}/security/extern_rsa_pub.txt have exist!)
else
$(error device/hisilicon/${CHIPNAME}/security/extern_rsa_pub.txt do not exist!)
endif

SECURITY_PRODUCTION_OUT := $(PRODUCT_OUT)/Security_L2/PRODUCTION
SECURITY_MAINTAIN_OUT := $(PRODUCT_OUT)/Security_L2/MAINTAIN
L2_EMMC_PRODUCTION_OUT :=  $(PRODUCT_OUT)/Security_L2/PRODUCTION
L2_EMMC_MAINTAIN_OUT := $(PRODUCT_OUT)/Security_L2/MAINTAIN
endif
endif

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
# Audio Update zip
-include device/hisilicon/bigfish/build/audio.mk
# bootargs
-include device/hisilicon/bigfish/build/bootargs.mk
# hipro
-include device/hisilicon/bigfish/build/hipro.mk
# security
ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
ifneq ($(strip $(HISILICON_SECURITY_L3)),true)
-include device/hisilicon/bigfish/build/security.mk
endif
endif
-include device/hisilicon/bigfish/build/secureos.mk

# hiboot
.PHONY: hiboot
hiboot: $(EMMC_HIBOOT_IMG)
# updatezip
.PHONY: updatezip
ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
ifneq ($(strip $(HISILICON_SECURITY_L3)),true)
updatezip: $(EMMC_SECURITY_UPDATE_PACKAGE)
else
updatezip: $(EMMC_UPDATE_PACKAGE)
endif
else
updatezip: $(EMMC_UPDATE_PACKAGE)
endif
# prebuilt
.PHONY:prebuilt
prebuilt: $(EMMC_PREBUILT_IMG)
#----------------------------------------------------------------------
# Full Compile
#----------------------------------------------------------------------

RECORVERY_OR_APPLOADER_TARGET := recoveryimg updatezip

.PHONY: bigfish
bigfish: prebuilt hiboot secureos kernel ubifs ext4fs $(RECORVERY_OR_APPLOADER_TARGET)
ifdef BOARD_QBSUPPORT
ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
ifneq ($(strip $(HISILICON_SECURITY_L3)),true)
	$(hide) rm  -rf $(EMMC_PRODUCT_OUT)
endif
endif
endif
#----------------------------------------------------------------------
# Full Compile End
#----------------------------------------------------------------------

