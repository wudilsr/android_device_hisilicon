LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

PQIMG_NAME := pq_param.bin
PQIMG_EMMC_DST_FILE := $(PRODUCT_OUT)/Emmc/pq_param.bin
PQIMG_SRC_FILE := $(LOCAL_PATH)/$(CFG_HI_CHIP_TYPE)/prebuilts/$(PQIMG_NAME)

$(PQIMG_EMMC_DST_FILE): $(PQIMG_SRC_FILE) | $(ACP)
	@echo "install Hisilicon Emmc PQ images ..."
	@mkdir -p $(dir $@)
	$(ACP) -fvp "$(PQIMG_SRC_FILE)" "$(PQIMG_EMMC_DST_FILE)"

pq_param: $(PQIMG_EMMC_DST_FILE)

CUSTOM_MODULES += pq_param
