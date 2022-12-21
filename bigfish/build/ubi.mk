LOCAL_PATH := $(call my-dir)

#----------------------------------------------------------------------
# Generate UBI Images
#----------------------------------------------------------------------

include $(CLEAR_VARS)

UBI_IMG := ubi
TOOLS_OUT := $(TARGET_OUT_INTERMEDIATES)/TOOLS_OBJ

#just for rename for data to userdata
TARGET_OUT_USERDATA:=$(PRODUCT_OUT)/userdata

# mkubiimg.sh copy
UBISH_DST := $(HOST_OUT_EXECUTABLES)/mkubiimg.sh
UBISH_SRC := $(LOCAL_PATH)/mkubiimg.sh
$(UBISH_DST):$(UBISH_SRC) | $(ACP)
	$(transform-prebuilt-to-target)
	$(hide) chmod a+x $@

# ubitools mkfs.ubifs ,ubinize copy
UBITOOLS_NIZE := $(TOOLS_OUT)/ubinize
UBITOOLS_MKFS := $(TOOLS_OUT)/mkfs.ubifs

UBITOOLS_DST :=$(HOST_OUT_EXECUTABLES)/ubinize \
               $(HOST_OUT_EXECUTABLES)/mkfs.ubifs

SQUASHFS_IMG := squash
TOOLS_OUT := $(TARGET_OUT_INTERMEDIATES)/TOOLS_OBJ
SQUASHFS_OUT := $(PRODUCT_OUT)/SQUASHFS
SQUASHFS_OUT_SYSTEM := $(SQUASHFS_OUT)/system.squashfs
MKSQUASHFS :=$(HOST_OUT_EXECUTABLES)/mksquashfs

$(UBITOOLS_MKFS):
	@echo "Build target Hisilicon tools: $@"
	mkdir -p $(TOOLS_OUT)
	cd $(ANDROID_BUILD_TOP)/$(SDK_DIR); $(MAKE) tools_install O=$(ANDROID_BUILD_TOP)/$(TOOLS_OUT) SDK_CFGFILE=$(SDK_CFGFILE);

$(UBITOOLS_NIZE): $(UBITOOLS_MKFS)

$(UBITOOLS_DST) : $(HOST_OUT_EXECUTABLES)/% : $(TOOLS_OUT)/% | $(ACP)
	$(transform-prebuilt-to-target)
	$(hide) chmod a+x $@

ifeq ($(SUPPORT_SDCARDFS),true)
define make_ubi_core
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT) $(1) $(2);\
	cp -rf $(TARGET_OUT_DATA) $(TARGET_OUT_USERDATA);\
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT_USERDATA) $(1) $(2);\
	rm -rf $(TARGET_OUT_USERDATA);\
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT_CACHE) $(1) $(2)
endef
else
define make_ubi_core
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT) $(1) $(2);\
	cp -rf $(TARGET_OUT_DATA) $(TARGET_OUT_USERDATA);\
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT_USERDATA) $(1) $(2);\
	rm -rf $(TARGET_OUT_USERDATA);\
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT_CACHE) $(1) $(2);\
	$(UBISH_DST) $(HOST_OUT_EXECUTABLES) $(TARGET_OUT_SDCARD) $(1) $(2)
endef
endif

define make_ubi_img
	for page_block_size in $(1); do \
		echo "Page_Block_Size=$$page_block_size";\
		PAGE_SIZE_UBI=`echo $${page_block_size} | sed 's/_.*//'`; \
		BLOCK_SIZE_UBI=`echo $${page_block_size} | sed 's/.*_//'`; \
		$(call make_ubi_core,$$PAGE_SIZE_UBI,$$BLOCK_SIZE_UBI);\
	done
endef

$(UBI_IMG):$(INSTALLED_SYSTEMIMAGE) $(INSTALLED_USERDATAIMAGE_TARGET) $(INSTALLED_CACHEIMAGE_TARGET) $(UBITOOLS_DST) $(UBISH_DST)
	$(call make_ubi_img,$(PAGE_BLOCK_SIZE))

.PHONY: ubifs
ubifs: $(UBI_IMG)

#----------------------------------------------------------------------
# UBI Images End
#----------------------------------------------------------------------
