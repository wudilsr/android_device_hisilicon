MAKEBOOTARGS := $(BUILD_OUT_EXECUTABLES)/mkbootargs$(BUILD_EXECUTABLE_SUFFIX)

ifeq ($(SUPPORT_SDCARDFS),true)
	ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)
	EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-sdcardfs-emmc-loader.txt
	else
	ifeq ($(strip $(HISILICON_SECURITY)),true)
	EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-sdcardfs-emmc-spca.txt
	else
	EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-sdcardfs-emmc.txt
	endif
	endif
else
ifeq ($(strip $(HISILICON_TEE)),true)
ifeq ($(strip $(VMX_ADVANCED_SUPPORT)),true)
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-tee-vmx.txt
else
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-tee.txt
endif
else
ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)
ifeq ($(strip $(VMX_ADVANCED_SUPPORT)),true)
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-vmx.txt
else
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-loader.txt
endif
else
ifeq ($(strip $(HISILICON_SECURITY)),true)
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-spca.txt
else
ifeq ($(strip $(SUPPORT_REMOTE_RECOVERY)),true)
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc-recovery.txt
else
EMMC_SRCFILE := device/hisilicon/$(CHIPNAME)/etc/bootargs_$(CHIPNAME)-emmc.txt
endif
endif
endif
endif
endif
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

