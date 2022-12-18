ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../..
    endif

include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_IR_TYPE_STD), y)
IR_DIR := ir_std
endif

ifeq ($(CFG_HI_IR_TYPE_S2), y)
IR_DIR := ir_s2
endif

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
IR_DIR := lirc
endif

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
obj-m += $(IR_DIR)/
else
    ifeq ($(CFG_MSP_BUILDTYPE),y)
    obj-$(CFG_MSP_BUILDTYPE) += $(IR_DIR)/
    endif
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean install uninstall

all:    
	$(AT)make -C $(IR_DIR) all

clean:
	$(AT)make -C $(IR_DIR) clean
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install:
	$(AT)make -C $(IR_DIR) install

uninstall:
	$(AT)make -C $(IR_DIR) uninstall   
