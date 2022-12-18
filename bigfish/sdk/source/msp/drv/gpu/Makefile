#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
        KERNEL_DIR := $(srctree)

        SDK_DIR := $(KERNEL_DIR)/../../..
    else
        SDK_DIR := $(CURDIR)/../../../..
    endif

include $(SDK_DIR)/base.mak
endif

#=======================================
#	local variable
#=======================================

ifeq ($(CFG_HI_GPU_MALI450_SUPPORT),y)
objects := mali4xx
else ifeq ($(CFG_HI_GPU_MALI400_SUPPORT),y)
objects := mali4xx
else ifeq ($(CFG_HI_GPU_MALI700_SUPPORT),y)
objects := mali700
else
$(error error: mali unknown)
endif

objects_clean       := ${addsuffix _clean,${objects}}
objects_install     := ${addsuffix _install,${objects}}
objects_uninstall   := ${addsuffix _uninstall,${objects}}

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)
KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

ifeq ($(CFG_MSP_BUILDTYPE), y)
obj-$(CFG_MSP_BUILDTYPE) += $(objects)/
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean install uninstall ${objects} ${objects_clean} ${objects_install} ${objects_uninstall}

all: ${objects}

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
ifeq ($(CFG_HI_GPU_MALI450_SUPPORT),y)
	@$(AT)cp -f $(CURDIR)/mali4xx/mali.ko $(MODULE_DIR)
else ifeq ($(CFG_HI_GPU_MALI400_SUPPORT),y)
	@$(AT)cp -f $(CURDIR)/mali4xx/mali.ko $(MODULE_DIR)
else ifeq ($(CFG_HI_GPU_MALI700_SUPPORT),y)
	@$(AT)cp -f $(CURDIR)/mali700/drivers/base/kds/kds.ko $(MODULE_DIR)
	@$(AT)cp -f $(CURDIR)/mali700/drivers/gpu/arm/midgard/mali_kbase.ko $(MODULE_DIR)
else
$(error error: mali unknown)
endif
endif

uninstall:
ifneq ($(CFG_MSP_BUILDTYPE),y)
ifeq ($(CFG_HI_GPU_MALI450_SUPPORT),y)
	$(AT)rm -rf $(MODULE_DIR)/mali.ko
else ifeq ($(CFG_HI_GPU_MALI400_SUPPORT),y)
	$(AT)rm -rf $(MODULE_DIR)/mali.ko
else ifeq ($(CFG_HI_GPU_MALI700_SUPPORT),y)
	$(AT)rm -rf $(MODULE_DIR)/kds.ko
	$(AT)rm -rf $(MODULE_DIR)/ump.ko
	$(AT)rm -rf $(MODULE_DIR)/mali_kbase.ko
else
$(error error: mali unknown)
endif
endif

${objects}:
	make -C $@

${objects_clean}:
	make -C ${patsubst %_clean,%,$@} clean

${objects_install}:
	make -C ${patsubst %_install,%,$@} install

${objects_uninstall}:
	make -C ${patsubst %_uninstall,%,$@} uninstall
