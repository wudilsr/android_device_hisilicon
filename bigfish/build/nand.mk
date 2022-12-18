include $(CLEAR_VARS)

ifeq ($(SUPPORT_SDCARDFS),true)
	ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)
	CHIP_TABLE := $(CHIPNAME)-sdcardfs-nand-loader.xml
	else
	CHIP_TABLE := $(CHIPNAME)-sdcardfs-nand.xml
	endif
else
ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)
ifeq ($(strip $(VMX_ADVANCED_SUPPORT)),true)
ifeq ($(strip $(HISILICON_TEE)),true)
CHIP_TABLE := $(CHIPNAME)-nand-tee-vmx.xml
else
CHIP_TABLE := $(CHIPNAME)-nand-vmx.xml
endif
else
CHIP_TABLE := $(CHIPNAME)-nand-loader.xml
endif
else
CHIP_TABLE := $(CHIPNAME)-nand.xml
endif
endif
CHIP_TABLE_PATH         := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/

ifeq ($(strip $(PRODUCT_TARGET)), shcmcc)
PREBUILT_BASEPARAM_PATH := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/mobile
PREBUILT_LOGO_PATH      := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/mobile
PREBUILT_FASTPLAY_PATH  := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/mobile
else ifeq ($(strip $(PRODUCT_TARGET)), telecom)
PREBUILT_BASEPARAM_PATH := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/telecom
PREBUILT_LOGO_PATH      := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_FASTPLAY_PATH  := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
else ifeq ($(strip $(PRODUCT_TARGET)), unicom)
PREBUILT_BASEPARAM_PATH := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/unicom
PREBUILT_LOGO_PATH      := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_FASTPLAY_PATH  := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
else
PREBUILT_BASEPARAM_PATH := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_LOGO_PATH      := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_FASTPLAY_PATH  := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
endif

NAND_CHIP_TABLE := $(NAND_PRODUCT_OUT)/$(CHIP_TABLE)
$(NAND_CHIP_TABLE) : $(NAND_PRODUCT_OUT)/% : $(CHIP_TABLE_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

NAND_PREBUILT_BASEPARAM_IMG := $(NAND_PRODUCT_OUT)/baseparam.img
$(NAND_PREBUILT_BASEPARAM_IMG) : $(NAND_PRODUCT_OUT)/% : $(PREBUILT_BASEPARAM_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

NAND_PREBUILT_LOGO_IMG := $(NAND_PRODUCT_OUT)/logo.img
$(NAND_PREBUILT_LOGO_IMG) : $(NAND_PRODUCT_OUT)/% : $(PREBUILT_LOGO_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

NAND_PREBUILT_FASTPLAY_IMG := $(NAND_PRODUCT_OUT)/fastplay.img
$(NAND_PREBUILT_FASTPLAY_IMG) : $(NAND_PRODUCT_OUT)/% : $(PREBUILT_FASTPLAY_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

NAND_PREBUILT_IMG := $(NAND_CHIP_TABLE) \
		$(NAND_PREBUILT_BASEPARAM_IMG) \
		$(NAND_PREBUILT_LOGO_IMG) \
		$(NAND_PREBUILT_FASTPLAY_IMG)

$(NAND_PREBUILT_IMG) : $(NAND_CHIP_TABLE) $(NAND_PREBUILT_BASEPARAM_IMG) $(NAND_PREBUILT_LOGO_IMG) $(NAND_PREBUILT_FASTPLAY_IMG)

.PHONY:prebuilt-nand
prebuilt-nand:$(NAND_PREBUILT_IMG)

#----------------------------------------------------------------------
# hiboot
#----------------------------------------------------------------------
include $(CLEAR_VARS)

NAND_HIBOOT_IMG := fastboot-burn-nand.bin
NAND_HIBOOT_OBJ := $(TARGET_OUT_INTERMEDIATES)/NAND_HIBOOT_OBJ

ifeq ($(strip $(VMX_ADVANCED_SUPPORT)),true)
NAND_BOOT_ANDROID_CFG := $(HISI_SDK_ANDROID_VMX_CFG)
else
NAND_BOOT_ANDROID_CFG := $(HISI_SDK_ANDROID_CFG)
endif

nand_fastboot_prepare:
	mkdir -p $(NAND_HIBOOT_OBJ)
	mkdir -p $(NAND_PRODUCT_OUT)

$(NAND_HIBOOT_IMG): nand_fastboot_prepare
	cp $(SDK_DIR)/$(SDK_CFG_DIR)/$(NAND_BOOT_ANDROID_CFG) $(NAND_HIBOOT_OBJ);\
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG); \
	sed -i '/CFG_HI_APPLOADER_SUPPORT/,1d' $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG); \
	if [ "$(TARGET_HAVE_APPLOADER)" = "true" ]; then \
	sed -i '/Ethernet/i\\CFG_HI_LOADER_SUPPORT=y\
CFG_HI_APPLOADER_SUPPORT=y' $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG); \
	fi
	if [ -n "$(NAND_BOOT_REG_NAME)" ]; then \
	sed -i s/CFG_HI_BOOT_REG_NAME=.*/CFG_HI_BOOT_REG_NAME=${NAND_BOOT_REG_NAME}/ $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(NAND_BOOT_ENV_STARTADDR)" ];then \
	sed -i s/CFG_HI_BOOT_ENV_STARTADDR=.*/CFG_HI_BOOT_ENV_STARTADDR=${NAND_BOOT_ENV_STARTADDR}/ $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(NAND_BOOT_ENV_SIZE)" ];then \
	sed -i s/CFG_HI_BOOT_ENV_SIZE=.*/CFG_HI_BOOT_ENV_SIZE=${NAND_BOOT_ENV_SIZE}/ $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(NAND_BOOT_ENV_RANGE)" ]; then \
	sed -i s/CFG_HI_BOOT_ENV_RANGE=.*/CFG_HI_BOOT_ENV_RANGE=${NAND_BOOT_ENV_RANGE}/ $(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG);\
	fi
	cd $(SDK_DIR);$(MAKE) hiboot O=$(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ) \
	SDK_CFGFILE=../../../../$(NAND_HIBOOT_OBJ)/$(NAND_BOOT_ANDROID_CFG);\
	if [ -f "$(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ)/miniboot.bin" ]; then \
	cp -avf $(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ)/miniboot.bin $(ANDROID_BUILD_TOP)/$(NAND_PRODUCT_OUT)/fastboot.bin ; \
	elif [ -f "$(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ)/fastboot-burn.bin" ]; then \
	cp -avf $(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ)/fastboot-burn.bin $(ANDROID_BUILD_TOP)/$(NAND_PRODUCT_OUT)/fastboot.bin ; \
	else \
	exit ;\
	fi
	if [ -f "$(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ)/advca_programmer.bin" ]; then \
	cp -avf $(ANDROID_BUILD_TOP)/$(NAND_HIBOOT_OBJ)/advca_programmer.bin $(ANDROID_BUILD_TOP)/$(NAND_PRODUCT_OUT)/advca_programmer.bin; \
	fi


.PHONY: hiboot-nand
hiboot-nand: $(NAND_HIBOOT_IMG)
#----------------------------------------------------------------------
# hiboot END
#


#----------------------------------------------------------------------
# Generate The Update Package
# 1: nand update.zip
#----------------------------------------------------------------------

include $(CLEAR_VARS)

NAND_UPDATE_PACKAGE :=$(NAND_PRODUCT_OUT)/update.zip

$(NAND_UPDATE_PACKAGE): $(INSTALLED_SYSTEMIMAGE) $(INSTALLED_USERDATAIMAGE_TARGET) $(KERNEL_IMAGE) $(RECOVERY_IMAGE) $(NAND_PREBUILT_IMG) $(NAND_HIBOOT_IMG) $(UPDATE_TOOLS)
	@echo ----- Making update package ------
	$(hide) rm -rf $(NAND_PRODUCT_OUT)/update
	$(hide) mkdir -p $(NAND_PRODUCT_OUT)/update
	$(hide) mkdir -p $(NAND_PRODUCT_OUT)/update/file
	$(hide) mkdir -p $(NAND_PRODUCT_OUT)/update/file/META
	$(hide) cp -af $(call include-path-for, recovery)/etc/recovery.fstab $(NAND_PRODUCT_OUT)/update/file/META/recovery.fstab
	$(hide) cp -a $(PRODUCT_OUT)/bootargs_nand.txt $(NAND_PRODUCT_OUT)/update/file/META/bootargs.txt
	$(hide) cp -a $(NAND_PRODUCT_OUT)/fastboot.bin $(NAND_PRODUCT_OUT)/update/file/fastboot.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/recovery.img $(NAND_PRODUCT_OUT)/update/file/recovery.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/baseparam.img $(NAND_PRODUCT_OUT)/update/file/baseparam.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/logo.img $(NAND_PRODUCT_OUT)/update/file/logo.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/fastplay.img $(NAND_PRODUCT_OUT)/update/file/fastplay.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/bootargs.bin $(NAND_PRODUCT_OUT)/update/file/bootargs.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/pq_param.bin $(NAND_PRODUCT_OUT)/update/file/pq_param.img
	$(hide) cp -a $(NAND_PRODUCT_OUT)/kernel.img $(NAND_PRODUCT_OUT)/update/file/boot.img
	$(hide) mkdir -p $(NAND_PRODUCT_OUT)/update/file/META-INF/com/google/android
	$(hide) mkdir -p $(NAND_PRODUCT_OUT)/update/file/META-INF/com/android
	sed -n 's/ro.build.fingerprint/post-build/p' $(PRODUCT_OUT)/system/build.prop  > $(NAND_PRODUCT_OUT)/update/file/META-INF/com/android/metadata
	$(hide) cp -a $(PRODUCT_OUT)/system/bin/updater $(NAND_PRODUCT_OUT)/update/file/META-INF/com/google/android/update-binary
	$(hide) cp -af $(PRODUCT_OUT)/system $(NAND_PRODUCT_OUT)/update/file/system
	$(hide) cp -af $(PRODUCT_OUT)/data $(NAND_PRODUCT_OUT)/update/file/userdata
	$(hide) cp -a $(call include-path-for, recovery)/etc/META-INF/com/google/android/updater-script-by-file $(NAND_PRODUCT_OUT)/update/file/META-INF/com/google/android/updater-script
	$(hide) echo "recovery_api_version=$(RECOVERY_API_VERSION)" >$(NAND_PRODUCT_OUT)/update/file/META/misc_info.txt
	$(hide) echo "fstab_version=$(RECOVERY_FSTAB_VERSION)" >> $(NAND_PRODUCT_OUT)/update/file/META/misc_info.txt
	$(hide) (cd $(NAND_PRODUCT_OUT)/update/file && zip -qry ../sor_update.zip .)
	zipinfo -1 $(NAND_PRODUCT_OUT)/update/sor_update.zip | awk '/^system\// {print}' | $(HOST_OUT_EXECUTABLES)/fs_config > $(NAND_PRODUCT_OUT)/update/file/META/filesystem_config.txt
	$(hide) (cd $(NAND_PRODUCT_OUT)/update/file && zip -q ../sor_update.zip META/*)
	java -jar $(SIGNAPK_JAR) -w  $(DEFAULT_SYSTEM_DEV_CERTIFICATE).x509.pem $(DEFAULT_SYSTEM_DEV_CERTIFICATE).pk8 $(NAND_PRODUCT_OUT)/update/sor_update.zip $(NAND_PRODUCT_OUT)/update/update.zip
	$(hide) cp -a $(NAND_PRODUCT_OUT)/update/update.zip  $(NAND_PRODUCT_OUT)/
	$(hide) rm -rf $(NAND_PRODUCT_OUT)/update
	@echo ----- Made update package: $@ --------


.PHONY: updatezip-nand
updatezip-nand: $(NAND_UPDATE_PACKAGE)

#----------------------------------------------------------------------
# Generate The Update Package End
#----------------------------------------------------------------------
