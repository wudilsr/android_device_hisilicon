#----------------------------------------------------------------------
# Compile Linux Kernel
#----------------------------------------------------------------------
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def
SECUREOS_OUT := $(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/SECUREOS_OBJ
SECUREOS_IMAGE :=

ANDROID_SECUREOS_FLAGS := CFG_TVP_MEM_${HISILICON_TEE_MEM}=y CFG_HI_TVP_MEM_LAYOUT=${HISILICON_TEE_MEM}
SECUREOS_OBJ_prepare:
	mkdir -p $(SECUREOS_OUT)
	mkdir -p $(EMMC_PRODUCT_OUT)

$(SECUREOS_IMAGE):SECUREOS_OBJ_prepare
	cd $(SDK_DIR);$(MAKE) tee O=$(SECUREOS_OUT) $(ANDROID_SECUREOS_FLAGS) \
	SDK_CFGFILE=$(SDK_CFGFILE);cd -
