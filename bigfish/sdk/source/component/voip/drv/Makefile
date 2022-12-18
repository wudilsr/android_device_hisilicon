#=======================================
#	export variable
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)
    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../..
    endif

include $(SDK_DIR)/base.mak
endif

DRV_DIR=$(SDK_DIR)/source/component/voip/drv
#=======================================
#	local variable
#=======================================
KO_NAME := $(wildcard $(CFG_HI_KERNEL_CFG)/aud_adp/*.ko)
KO_NAME += $(wildcard $(CFG_HI_KERNEL_CFG)/hme/*.ko)

MODULE_KO := $(addprefix $(MODULE_DIR)/, $(notdir $(KO_NAME)))

#=================================================================
#	  rules
#=================================================================

.PHONY: all clean install uninstall

all:
	    	
clean:
	
install:
	@cp $(CFG_HI_KERNEL_CFG)/aud_adp/*.ko $(MODULE_DIR)/
	@cp $(CFG_HI_KERNEL_CFG)/hme/*.ko $(MODULE_DIR)/
	
uninstall:
	@rm -rf $(MODULE_KO)


