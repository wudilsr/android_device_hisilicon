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


#===============================================================================
#   rules
#===============================================================================
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
RX_NAME=hdmirx2.0
endif

obj-m += $(RX_NAME)/
obj-$(CFG_MSP_BUILDTYPE) += $(RX_NAME)/

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(RX_NAME)

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
	$(AT)make -C $(RX_NAME) install

uninstall:
	$(AT)make -C $(RX_NAME) uninstall



