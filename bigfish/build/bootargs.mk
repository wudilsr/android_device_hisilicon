MAKEBOOTARGS := $(BUILD_OUT_EXECUTABLES)/mkbootargs$(BUILD_EXECUTABLE_SUFFIX)

ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)
NAND_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-nand-loader.txt
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-loader.txt
else
ifeq ($(strip $(HISILICON_SECURITY)),true)
NAND_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-nand-spca.txt
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-spca.txt
else
NAND_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-nand.txt
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc.txt
endif
endif
NAND_BOOTARGS := $(NAND_PRODUCT_OUT)/bootargs.bin
EMMC_BOOTARGS := $(EMMC_PRODUCT_OUT)/bootargs.bin

$(NAND_BOOTARGS): $(MAKEBOOTARGS) $(NAND_SRCFILE)
	echo "nand bootargs build ..."
	$(hide) mkdir -p $(PRODUCT_OUT)
	$(hide) mkdir -p $(NAND_PRODUCT_OUT)
	$(hide) cp -r $(TOP)/$(NAND_SRCFILE) $(PRODUCT_OUT)/bootargs_nand.txt
	$(MAKEBOOTARGS) -r $(TOP)/$(NAND_SRCFILE) -o $(NAND_BOOTARGS) -s 64

$(EMMC_BOOTARGS): $(MAKEBOOTARGS) $(EMMC_SRCFILE)
	echo "emmc bootargs build ..."
	$(hide) mkdir -p $(PRODUCT_OUT)
	$(hide) mkdir -p $(EMMC_PRODUCT_OUT)
	$(hide) cp -r $(TOP)/$(EMMC_SRCFILE) $(PRODUCT_OUT)/bootargs_emmc.txt
	$(MAKEBOOTARGS) -r $(TOP)/$(EMMC_SRCFILE) -o $(EMMC_BOOTARGS) -s 64

ALL_DEFAULT_INSTALLED_MODULES += $(NAND_BOOTARGS) $(EMMC_BOOTARGS)

.PHONY: bootargs $(NAND_BOOTARGS) $(EMMC_BOOTARGS)
bootargs: $(NAND_BOOTARGS) $(EMMC_BOOTARGS)

