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

ifeq ($(CFG_MSP_BUILDTYPE), y)
obj-m += sil9293/
obj-$(CFG_MSP_BUILDTYPE) += sil9293/
#obj-$(CFG_MSP_BUILDTYPE) += tvp5150/
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C sil9293

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
	$(AT)make -C sil9293 install

uninstall:
	$(AT)make -C sil9293 uninstall
