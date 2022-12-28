MAKEBOOTARGS := $(BUILD_OUT_EXECUTABLES)/mkbootargs$(BUILD_EXECUTABLE_SUFFIX)
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME).txt

EMMC_BOOTARGS := $(EMMC_PRODUCT_OUT)/bootargs.bin

$(EMMC_BOOTARGS): $(MAKEBOOTARGS) $(EMMC_SRCFILE)
	echo "emmc bootargs build ..."
	$(hide) mkdir -p $(PRODUCT_OUT)
	$(hide) mkdir -p $(EMMC_PRODUCT_OUT)
	$(hide) cp -r $(TOP)/$(EMMC_SRCFILE) $(PRODUCT_OUT)/bootargs_emmc.txt
	$(MAKEBOOTARGS) -r $(TOP)/$(EMMC_SRCFILE) -o $(EMMC_BOOTARGS) -s 64

ALL_DEFAULT_INSTALLED_MODULES += $(EMMC_BOOTARGS)

.PHONY: bootargs $(EMMC_BOOTARGS)
bootargs: $(EMMC_BOOTARGS)

