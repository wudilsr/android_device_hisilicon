include $(CLEAR_VARS)
CHIP_TABLE              := $(CHIPNAME)-sdcardfs-emmc.xml	
CHIP_TABLE_PATH         := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_BASEPARAM_PATH := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_LOGO_PATH      := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/
PREBUILT_FASTPLAY_PATH  := $(TOP)/device/hisilicon/$(CHIPNAME)/prebuilts/

EMMC_CHIP_TABLE := $(EMMC_PRODUCT_OUT)/$(CHIP_TABLE)
$(EMMC_CHIP_TABLE) : $(EMMC_PRODUCT_OUT)/% : $(CHIP_TABLE_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

EMMC_PREBUILT_BASEPARAM_IMG := $(EMMC_PRODUCT_OUT)/baseparam.img
$(EMMC_PREBUILT_BASEPARAM_IMG) : $(EMMC_PRODUCT_OUT)/% : $(PREBUILT_BASEPARAM_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

EMMC_PREBUILT_LOGO_IMG := $(EMMC_PRODUCT_OUT)/logo.img
$(EMMC_PREBUILT_LOGO_IMG) : $(EMMC_PRODUCT_OUT)/% : $(PREBUILT_LOGO_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

EMMC_PREBUILT_FASTPLAY_IMG := $(EMMC_PRODUCT_OUT)/fastplay.img
$(EMMC_PREBUILT_FASTPLAY_IMG) : $(EMMC_PRODUCT_OUT)/% : $(PREBUILT_FASTPLAY_PATH)/% | $(ACP)
	$(transform-prebuilt-to-target)

EMMC_PREBUILT_IMG := $(EMMC_CHIP_TABLE) \
		$(EMMC_PREBUILT_BASEPARAM_IMG) \
		$(EMMC_PREBUILT_LOGO_IMG) \
		$(EMMC_PREBUILT_FASTPLAY_IMG)

$(EMMC_PREBUILT_IMG) : $(EMMC_CHIP_TABLE) $(EMMC_PREBUILT_BASEPARAM_IMG) $(EMMC_PREBUILT_LOGO_IMG) $(EMMC_PREBUILT_FASTPLAY_IMG)

.PHONY: prebuilt-emmc
prebuilt-emmc:$(EMMC_PREBUILT_IMG)

#----------------------------------------------------------------------
# hiboot
#----------------------------------------------------------------------
include $(CLEAR_VARS)

EMMC_HIBOOT_IMG := fastboot-burn-emmc.bin
EMMC_HIBOOT_OBJ := $(TARGET_OUT_INTERMEDIATES)/EMMC_HIBOOT_OBJ
EMMC_BOOT_ANDROID_CFG := $(HISI_SDK_ANDROID_CFG)

emmc_fastboot_prepare:
	mkdir -p $(EMMC_HIBOOT_OBJ)
	mkdir -p $(EMMC_PRODUCT_OUT)

$(EMMC_HIBOOT_IMG): emmc_fastboot_prepare
	cp $(SDK_DIR)/$(SDK_CFG_DIR)/$(EMMC_BOOT_ANDROID_CFG) $(EMMC_HIBOOT_OBJ);\
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG); \
	sed -i '/CFG_HI_APPLOADER_SUPPORT/,1d' $(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG); \
	if [ "$(SUPPORT_REMOTE_RECOVERY)" = "true" ]; then \
	sed -i -e '/# CFG_HI_BUILD_WITH_IR /a\CFG_HI_BUILD_WITH_IR = y' -e '/# CFG_HI_BUILD_WITH_IR/d' \
	$(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG); \
	fi
	if [ -n "$(EMMC_BOOT_REG_NAME)" ]; then \
	sed -i s/CFG_HI_BOOT_REG_NAME=.*/CFG_HI_BOOT_REG_NAME=${EMMC_BOOT_REG_NAME}/ $(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(EMMC_BOOT_ENV_STARTADDR)" ];then \
	sed -i s/CFG_HI_BOOT_ENV_STARTADDR=.*/CFG_HI_BOOT_ENV_STARTADDR=${EMMC_BOOT_ENV_STARTADDR}/ $(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(EMMC_BOOT_ENV_SIZE)" ];then \
	sed -i s/CFG_HI_BOOT_ENV_SIZE=.*/CFG_HI_BOOT_ENV_SIZE=${EMMC_BOOT_ENV_SIZE}/ $(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(EMMC_BOOT_ENV_RANGE)" ]; then \
	sed -i s/CFG_HI_BOOT_ENV_RANGE=.*/CFG_HI_BOOT_ENV_RANGE=${EMMC_BOOT_ENV_RANGE}/ $(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	cd $(SDK_DIR);$(MAKE) hiboot O=$(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ) \
	SDK_CFGFILE=../../../../$(EMMC_HIBOOT_OBJ)/$(EMMC_BOOT_ANDROID_CFG);\
	if [ -f "$(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ)/miniboot.bin" ]; then \
	cp -avf $(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ)/miniboot.bin $(ANDROID_BUILD_TOP)/$(EMMC_PRODUCT_OUT)/fastboot.bin ;\
	elif [ -f "$(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ)/fastboot-burn.bin" ]; then \
	cp -avf $(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ)/fastboot-burn.bin $(ANDROID_BUILD_TOP)/$(EMMC_PRODUCT_OUT)/fastboot.bin ; \
	else \
	exit; \
	fi
	if [ -f "$(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ)/advca_programmer.bin" ]; then \
	cp -avf $(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ)/advca_programmer.bin $(ANDROID_BUILD_TOP)/$(EMMC_PRODUCT_OUT)/advca_programmer.bin;\
	fi



.PHONY: hiboot-emmc
hiboot-emmc: $(EMMC_HIBOOT_IMG)

#----------------------------------------------------------------------
EMMC_BOOT_ANDROID_CFG := $(HISI_SDK_ANDROID_CFG)

emmc_fastboot_prepare_2:
	mkdir -p $(EMMC_HIBOOT_OBJ_2)
	mkdir -p $(EMMC_PRODUCT_OUT)

$(EMMC_HIBOOT_IMG_2): emmc_fastboot_prepare_2
	cp $(SDK_DIR)/$(SDK_CFG_DIR)/$(EMMC_BOOT_ANDROID_CFG) $(EMMC_HIBOOT_OBJ_2);\
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(EMMC_HIBOOT_OBJ_2)/$(EMMC_BOOT_ANDROID_CFG); \
	sed -i '/CFG_HI_APPLOADER_SUPPORT/,1d' $(EMMC_HIBOOT_OBJ_2)/$(EMMC_BOOT_ANDROID_CFG); \
	if [ -n "$(EMMC_BOOT_ENV_STARTADDR)" ];then \
	sed -i s/CFG_HI_BOOT_ENV_STARTADDR=.*/CFG_HI_BOOT_ENV_STARTADDR=${EMMC_BOOT_ENV_STARTADDR}/ $(EMMC_HIBOOT_OBJ_2)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(EMMC_BOOT_ENV_SIZE)" ];then \
	sed -i s/CFG_HI_BOOT_ENV_SIZE=.*/CFG_HI_BOOT_ENV_SIZE=${EMMC_BOOT_ENV_SIZE}/ $(EMMC_HIBOOT_OBJ_2)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	if [ -n "$(EMMC_BOOT_ENV_RANGE)" ]; then \
	sed -i s/CFG_HI_BOOT_ENV_RANGE=.*/CFG_HI_BOOT_ENV_RANGE=${EMMC_BOOT_ENV_RANGE}/ $(EMMC_HIBOOT_OBJ_2)/$(EMMC_BOOT_ANDROID_CFG);\
	fi
	cd $(SDK_DIR);$(MAKE) hiboot O=$(ANDROID_BUILD_TOP)/$(EMMC_HIBOOT_OBJ_2) \
	SDK_CFGFILE=../../../../$(EMMC_HIBOOT_OBJ_2)/$(EMMC_BOOT_ANDROID_CFG);

.PHONY: hiboot-emmc-2
hiboot-emmc-2: $(EMMC_HIBOOT_IMG_2)
#----------------------------------------------------------------------
# hiboot END
#
