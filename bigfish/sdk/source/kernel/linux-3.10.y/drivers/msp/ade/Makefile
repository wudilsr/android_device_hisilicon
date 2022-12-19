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
# local variables
#===============================================================================
ADSP_DRV_INCLUDE = $(MSP_DRV_INCLUDE)/adsp

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(ADSP_DRV_INCLUDE)                   \
                -I$(MSP_DRV_INCLUDE)

EXTRA_CFLAGS += -DHI_ADE_PROC_SUPPORT

MOD_NAME := hi_ade

ifeq ($(CFG_HI_MSP_BUILDIN), y)
obj-y += $(MOD_NAME).o
else
obj-m += $(MOD_NAME).o
endif

$(MOD_NAME)-y   :=  drv_ade_intf.o  \
                    drv_ade.o       \
                    hal_ade.o

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install:
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

