LOCAL_PATH:= $(call my-dir)
TRUSTED_CORE_PATH:=$(call my-dir)


include      $(CLEAR_VARS)

include $(LOCAL_PATH)/trustedcore.mk

LOCAL_MODULE := trustedcore.img
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_PATH := $(PRODUCT_OUT)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

trustedcore.img: rtosck.img globaltask.img
	@echo "Install: Package $(PRODUCT_OUT)/trustedcore.img"
	$(shell  $(TRUSTED_CORE_PATH)/packimg.sh $(TRUSTEDCORE_TEXT_BASE)>/dev/null)
	mkdir -p $(PRODUCT_OUT)/Emmc/
	mkdir -p $(PRODUCT_OUT)/Nand/
	mkdir -p $(PRODUCT_OUT)/Security_L2/MAINTAIN
	cp -avf $(PRODUCT_OUT)/$@ $(PRODUCT_OUT)/Emmc/
	cp -avf $(PRODUCT_OUT)/$@ $(PRODUCT_OUT)/Nand/
	cp -avf $(PRODUCT_OUT)/$@ $(PRODUCT_OUT)/Security_L2/MAINTAIN


include $(BUILD_RAW_EXECUTABLE)
include $(call all-makefiles-under,$(LOCAL_PATH))
