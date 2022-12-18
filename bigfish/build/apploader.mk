#----------------------------------------------------------------------
# Compile Loader
#----------------------------------------------------------------------
include $(CLEAR_VARS)

#ifeq ($(strip $(TARGET_HAVE_APPLOADER)),true)

APPLOADER_IMG := apploader.bin
APPLOADER_OBJ := $(TARGET_OUT_INTERMEDIATES)/APPLOADER_OBJ

apploader_prepare:
	mkdir -p $(APPLOADER_OBJ)
	rm -rf $(APPLOADER_OBJ)/*
	mkdir -p $(NAND_PRODUCT_OUT)
	mkdir -p $(EMMC_PRODUCT_OUT)
	cp -arf $(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/sdk $(APPLOADER_OBJ)/
 
$(APPLOADER_IMG): apploader_prepare
	cd $(APPLOADER_OBJ)/sdk/ && make build SDK_CFGFILE=$(SDK_CFG_DIR)/$(APPLOADER_CFG)
	cp -arvf $(APPLOADER_OBJ)/sdk/pub/image/apploader.bin $(ANDROID_BUILD_TOP)/$(NAND_PRODUCT_OUT)/
	cp -arvf $(APPLOADER_OBJ)/sdk/pub/image/apploader.bin $(ANDROID_BUILD_TOP)/$(EMMC_PRODUCT_OUT)/

.PHONY:apploader
apploader: $(APPLOADER_IMG)
#endif
#----------------------------------------------------------------------
# Loader End
#----------------------------------------------------------------------
