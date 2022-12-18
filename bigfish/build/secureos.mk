#----------------------------------------------------------------------
# Compile Linux Kernel
#----------------------------------------------------------------------
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
SECUREOS_OUT := $(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/SECUREOS_OBJ
ifeq ($(strip $(HISILICON_TEE)),true)
SECUREOS_IMAGE := $(SECUREOS_OUT)/trustedcore.img
else
SECUREOS_IMAGE :=
endif

ANDROID_SECUREOS_FLAGS := CFG_TVP_MEM_${HISILICON_TEE_MEM}=y CFG_HI_TVP_MEM_LAYOUT=${HISILICON_TEE_MEM}
SECUREOS_OBJ_prepare:
	mkdir -p $(SECUREOS_OUT)
	mkdir -p $(EMMC_PRODUCT_OUT)
	mkdir -p $(NAND_PRODUCT_OUT)

$(SECUREOS_IMAGE):SECUREOS_OBJ_prepare
	cd $(SDK_DIR);$(MAKE) tee O=$(SECUREOS_OUT) $(ANDROID_SECUREOS_FLAGS) \
	SDK_CFGFILE=$(SDK_CFGFILE);cd -

ifeq ($(strip $(HISILICON_TEE)),true)
.PHONY: secureos $(SECUREOS_IMAGE)
secureos: $(SECUREOS_IMAGE)
	cp -avf $(SECUREOS_IMAGE) $(PRODUCT_OUT)
	cp -avf $(SECUREOS_IMAGE) $(EMMC_PRODUCT_OUT)
	cp -avf $(SECUREOS_IMAGE) $(NAND_PRODUCT_OUT)

#	$(hide) mkdir -p $(SECURE_OBJ_DIR)
#	$(hide) chmod a+x $(SDK_LINUX_SIGN_TOOL_DIR)/CASignTool
#	$(hide) $(SDK_LINUX_SIGN_TOOL_DIR)/CASignTool 3 $(SECURE_CONFIG_DIR)/special_trustedcore_CV200_config.cfg -k $(SECURE_RSA_KEY_DIR) -r $(SECURE_INPUT_DIR) -o $(SECURE_OBJ_DIR)
#	$(hide) cp -arv $(SECURE_OBJ_DIR)/trustedcore.img $(SECURE_OUTPUT_DIR)/trustedcore.img
else
.PHONY: secureos
secureos:
	@echo "Please Set HISILICON_TEE= true"
endif
