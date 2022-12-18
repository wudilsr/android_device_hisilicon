#----------------------------------------------------------------------
# hipro-nand
#----------------------------------------------------------------------
include $(CLEAR_VARS)

NAND_HIPRO_IMG := program-nand.bin
NAND_HIPRO_OBJ := $(TARGET_OUT_INTERMEDIATES)/NAND_HIPRO_OBJ

nand_hipro_prepare:
	mkdir -p $(NAND_HIPRO_OBJ)
	mkdir -p $(NAND_PRODUCT_OUT)
	cp $(SDK_DIR)/$(SDK_CFGFILE) $(NAND_HIPRO_OBJ); \
    if [ -n "$(NAND_BOOT_REG_NAME)" ]; then \
        sed -i s/CFG_HI_BOOT_REG_NAME=.*/CFG_HI_BOOT_REG_NAME=${NAND_BOOT_REG_NAME}/ $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	if [ -n "$(NAND_BOOT_ENV_STARTADDR)" ];then \
        sed -i s/CFG_HI_BOOT_ENV_STARTADDR=.*/CFG_HI_BOOT_ENV_STARTADDR=${NAND_BOOT_ENV_STARTADDR}/ $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	if [ -n "$(NAND_BOOT_ENV_SIZE)" ];then \
        sed -i s/CFG_HI_BOOT_ENV_SIZE=.*/CFG_HI_BOOT_ENV_SIZE=${NAND_BOOT_ENV_SIZE}/ $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	if [ -n "$(NAND_BOOT_ENV_RANGE)" ]; then \
        sed -i s/CFG_HI_BOOT_ENV_RANGE=.*/CFG_HI_BOOT_ENV_RANGE=${NAND_BOOT_ENV_RANGE}/ $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_APPLOADER_SUPPORT/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOTLOADER_SUPPORT/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOT_USB_SUPPORT/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_LOADER_BOOTLOADER/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOTLOADER_MODE_USB/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOTLOADER_USB_PROTOCOL_HISI_FILE/,1d' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
	sed -i '/Boot/i\\CFG_HI_LOADER_SUPPORT=y\
CFG_HI_BOOTLOADER_SUPPORT=y\
CFG_HI_BOOT_USB_SUPPORT=y\
CFG_HI_LOADER_BOOTLOADER=y\
CFG_HI_BOOTLOADER_MODE_USB=y\
CFG_HI_BOOTLOADER_USB_PROTOCOL_HISI_FILE=y' $(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \

$(NAND_HIPRO_IMG): nand_hipro_prepare
	cd $(SDK_DIR);$(MAKE) hiboot O=$(ANDROID_BUILD_TOP)/$(NAND_HIPRO_OBJ) \
	SDK_CFGFILE=../../../../$(NAND_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
	cp -arf $(ANDROID_BUILD_TOP)/$(SDK_DIR)/tools/windows/HiPro-serial $(ANDROID_BUILD_TOP)/$(NAND_PRODUCT_OUT)/
	cp -avf $(ANDROID_BUILD_TOP)/$(NAND_HIPRO_OBJ)/fastboot-burn.bin $(ANDROID_BUILD_TOP)/$(NAND_PRODUCT_OUT)/HiPro-serial/program.bin

.PHONY: hipro-nand
hipro-nand: $(NAND_HIPRO_IMG)
#----------------------------------------------------------------------
# hipro-nand END
#

#----------------------------------------------------------------------
# hipro-emmc
#----------------------------------------------------------------------
include $(CLEAR_VARS)

EMMC_HIPRO_IMG := program-emmc.bin
EMMC_HIPRO_OBJ := $(TARGET_OUT_INTERMEDIATES)/EMMC_HIPRO_OBJ

emmc_hipro_prepare:
	mkdir -p $(EMMC_HIPRO_OBJ)
	mkdir -p $(EMMC_PRODUCT_OUT)
	cp $(SDK_DIR)/$(SDK_CFGFILE) $(EMMC_HIPRO_OBJ);\
    if [ -n "$(EMMC_BOOT_REG_NAME)" ]; then \
    sed -i s/CFG_HI_BOOT_REG_NAME=.*/CFG_HI_BOOT_REG_NAME=${EMMC_BOOT_REG_NAME}/ $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	if [ -n "$(EMMC_BOOT_ENV_STARTADDR)" ];then \
    sed -i s/CFG_HI_BOOT_ENV_STARTADDR=.*/CFG_HI_BOOT_ENV_STARTADDR=${EMMC_BOOT_ENV_STARTADDR}/ $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	if [ -n "$(EMMC_BOOT_ENV_SIZE)" ];then \
    sed -i s/CFG_HI_BOOT_ENV_SIZE=.*/CFG_HI_BOOT_ENV_SIZE=${EMMC_BOOT_ENV_SIZE}/ $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	if [ -n "$(EMMC_BOOT_ENV_RANGE)" ]; then \
    sed -i s/CFG_HI_BOOT_ENV_RANGE=.*/CFG_HI_BOOT_ENV_RANGE=${EMMC_BOOT_ENV_RANGE}/ $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
    fi
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_APPLOADER_SUPPORT/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
	sed -i '/CFG_HI_LOADER_SUPPORT/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOTLOADER_SUPPORT/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOT_USB_SUPPORT/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_LOADER_BOOTLOADER/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOTLOADER_MODE_USB/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
    sed -i '/CFG_HI_BOOTLOADER_USB_PROTOCOL_HISI_FILE/,1d' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \
	sed -i '/Boot/i\\CFG_HI_LOADER_SUPPORT=y\
CFG_HI_BOOTLOADER_SUPPORT=y\
CFG_HI_BOOT_USB_SUPPORT=y\
CFG_HI_LOADER_BOOTLOADER=y\
CFG_HI_BOOTLOADER_MODE_USB=y\
CFG_HI_BOOTLOADER_USB_PROTOCOL_HISI_FILE=y' $(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG); \

ifneq ($(NAND_HIPRO_IMG),)
$(EMMC_HIPRO_IMG): emmc_hipro_prepare $(NAND_HIPRO_IMG)
else
$(EMMC_HIPRO_IMG): emmc_hipro_prepare
endif
	cd $(SDK_DIR);$(MAKE) hiboot O=$(ANDROID_BUILD_TOP)/$(EMMC_HIPRO_OBJ) \
	SDK_CFGFILE=../../../../$(EMMC_HIPRO_OBJ)/$(HISI_SDK_ANDROID_CFG);\
	cp -arf $(ANDROID_BUILD_TOP)/$(SDK_DIR)/tools/windows/HiPro-serial $(ANDROID_BUILD_TOP)/$(EMMC_PRODUCT_OUT)/
	cp -avf $(ANDROID_BUILD_TOP)/$(EMMC_HIPRO_OBJ)/fastboot-burn.bin $(ANDROID_BUILD_TOP)/$(EMMC_PRODUCT_OUT)/HiPro-serial/program.bin
.PHONY: hipro-emmc
hipro-emmc: $(EMMC_HIPRO_IMG)
#----------------------------------------------------------------------
# hipro-emmc END
#

# hiboot
.PHONY: hipro
hipro: $(NAND_HIPRO_IMG) $(EMMC_HIPRO_IMG)

