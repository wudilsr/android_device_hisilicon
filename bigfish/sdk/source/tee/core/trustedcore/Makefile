#by fangjian00208632 2015-03-13

#====================================================================================
#                   export
#====================================================================================
.EXPORT_ALL_VARIABLES:
include trustedcore.mk


###########################################################
# platform definition
###########################################################
TARGET_IMG = $(OUT)/trustedcore.img

##########################################################
# build all
##########################################################
.PHONY : all build packimg clean
.PHONY : drivers       platform       internal_tasks
.PHONY : drivers_clean platform_clean internal_tasks_clean

all: packimg
packimg: platform internal_tasks


ifneq ($(strip $(CONFIG_TRUSTEDCORE_RELEASE)),true)
platform:  drivers
platform_clean: drivers_clean
endif


clean:platform_clean internal_tasks_clean
	$(RM) -rf $(TARGET_IMG)
	$(RM) -rf $(OUT)
	$(RM) -rf $(TOOLCHAINS_DIR)/gcc
	$(RM) -rf $(TRUSTEDCORE_DIR)/tools/elf_extract

$(TOOLCHAINS_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(TOOLCHAINS_PACKAGE) -C $(TOOLCHAINS_DIR)
	@touch $@

##########################################################
# 1. build internal_tasks
##########################################################
internal_tasks:$(TOOLCHAINS_DIR)/gcc/tar
	$(MAKE) -C internal_tasks/ all
internal_tasks_clean:
	$(MAKE) -C internal_tasks/ clean

##########################################################
# 2. build drivers
##########################################################
drivers:$(TOOLCHAINS_DIR)/gcc/tar
	$(MAKE) -C drivers/ all
drivers_clean:
	$(MAKE) -C drivers/ clean

##########################################################
# 3. build platform
##########################################################
platform:$(TOOLCHAINS_DIR)/gcc/tar
	$(MAKE) -C platform/ all
platform_clean:
	$(MAKE) -C platform/ clean

##########################################################
# 6. packimg
##########################################################
#disable by default 
SUPPORT_TEST_TA := 0
SUPPORT_SEC_MMZ := 0
SUPPORT_VFMW := 0
SUPPORT_SMMU := 0
SUPPORT_HISI_TEST :=0
SUPPORT_DMX := 0
SUPPORT_PVR := 0
SUPPORT_HDMI := 0
SUPPORT_WIDEVINE := 0
SUPPORT_PLAYREADY := 0
SUPPORT_HISI_DEMO := 0
SUPPORT_HISI_VDP :=0
SUPPORT_VMX_ULTRA := 0
SUPPORT_VMX_ULTRA_VMXTAC_TEST := 0
SUPPORT_VMX_ULTRA_ITAC_TEST := 0
SUPPORT_VPSS := 0
SUPPORT_HISI_DRM := 0

ifeq ($(strip $(WITH_TEST_TA)), true)
SUPPORT_TEST_TA := 1
endif

#get config form platform.mk
ifeq ($(strip $(WITH_HISI_SEC_MMZ)), true)
SUPPORT_SEC_MMZ := 1
endif

ifeq ($(strip $(WITH_HISI_VFMW)), true)
SUPPORT_VFMW := 1
endif

ifeq ($(strip $(WITH_HISI_SMMU)), true)
SUPPORT_SMMU := 1
endif

ifeq ($(strip $(WITH_HISI_TEST)), true)
SUPPORT_HISI_TEST :=1
endif

ifeq ($(strip $(WITH_HISI_DMX)), true)
SUPPORT_DMX := 1
endif

ifeq ($(strip $(WITH_HISI_PVR)), true)
SUPPORT_PVR := 1
endif

ifeq ($(strip $(WITH_HISI_SEC_HDMI)), true)
SUPPORT_HDMI := 1
endif

ifeq ($(strip $(WITH_HISI_WIDEVINE)), true)
SUPPORT_WIDEVINE := 1
endif

ifeq ($(strip $(WITH_HISI_PLAYREADY)), true)
SUPPORT_PLAYREADY := 1
endif

ifeq ($(strip $(WITH_HISI_DEMO)), true)
SUPPORT_HISI_DEMO := 1
endif

ifeq ($(strip $(WITH_HISI_VDP)), true)
SUPPORT_HISI_VDP := 1
endif

ifeq ($(strip $(WITH_COMPONENT_VMX_ULTRA)), true)
SUPPORT_VMX_ULTRA := 1
endif

ifeq ($(strip $(WITH_COMPONENT_VMX_ULTRA_VMXTAC_TEST)), true)
SUPPORT_VMX_ULTRA_VMXTAC_TEST := 1
endif
ifeq ($(strip $(WITH_COMPONENT_VMX_ULTRA_ITAC_TEST)), true)
SUPPORT_VMX_ULTRA_ITAC_TEST := 1
endif

ifeq ($(strip $(WITH_HISI_VPSS)), true)
SUPPORT_VPSS := 1
endif

ifeq ($(strip $(WITH_HISI_DRM)), true)
SUPPORT_HISI_DRM := 1
endif

packimg:
	chmod 777 ./packimg_linux.sh
	@./packimg_linux.sh $(TRUSTEDCORE_TEXT_BASE) \
			    $(PLATFORM_DIR_NAME) \
			    $(OUT) \
			    $(SUPPORT_TEST_TA) \
			    $(SUPPORT_SEC_MMZ) \
			    $(SUPPORT_VFMW) \
			    $(SUPPORT_SMMU) \
			    $(SUPPORT_HISI_TEST) \
			    $(SUPPORT_DMX)	\
			    $(SUPPORT_PVR)	\
			    $(SUPPORT_HDMI)	\
			    $(SUPPORT_WIDEVINE) \
			    $(SUPPORT_HISI_DEMO) \
			    $(SUPPORT_HISI_VDP) \
			    $(SUPPORT_VMX_ULTRA) \
			    $(SUPPORT_VMX_ULTRA_VMXTAC_TEST) \
			    $(SUPPORT_VMX_ULTRA_ITAC_TEST) \
			    $(SUPPORT_VPSS) \
			   $(SUPPORT_HISI_DRM) \
			    $(SUPPORT_PLAYREADY)
	@echo "Make $(TARGET_IMG) Success!"

