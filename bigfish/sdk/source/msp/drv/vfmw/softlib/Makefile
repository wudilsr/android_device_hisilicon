EXTRA_CFLAGS += -DENV_ARMLINUX_KERNEL

#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../../..
    endif

include $(SDK_DIR)/base.mak
endif
#===============================================================================
# export variables
#===============================================================================
########tmp value###############################
ifeq ($(CFG_HI_CPU_ARCH),arm64)
ARCH=$(CFG_HI_CPU_ARCH)
else
ARCH=arm
endif

ifeq ($(SRC_ROOT), )
export SRC_ROOT      := ${SOURCE_DIR}
endif

export MSP_DIR       := $(SRC_ROOT)/msp
export LINUXROOT     := $(LINUX_DIR)
KCOM_DIR      := $(SRC_ROOT)/common
VFMW_DIR      := $(MSP_DIR)/drv/vfmw/vfmw_v4.0
SDEC_KO_DIR   := $(MSP_DIR)/drv/vfmw/softlib
################################################
VFMW_INC_ROOT := $(SRC_ROOT)/msp/drv/vfmw/vfmw_v4.0

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
ifdef CFG_HI_ADVCA_FUNCTION
include $(VFMW_INC_ROOT)/firmware/product/Hi3716CV200_advca/HD_FULL_$(CFG_HI_TOOLCHAINS_NAME)/vfmw_make.cfg
else
include $(VFMW_INC_ROOT)/firmware/product/Hi3716CV200/HD_FULL_$(CFG_HI_TOOLCHAINS_NAME)/vfmw_make.cfg
endif
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
include $(VFMW_INC_ROOT)/firmware/product/Hi3798CV100/HD_FULL_$(CFG_HI_TOOLCHAINS_NAME)/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
include $(VFMW_INC_ROOT)/firmware/product/Hi3798MV100/HD_FULL_$(CFG_HI_TOOLCHAINS_NAME)/vfmw_make.cfg
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a),)
include $(VFMW_DIR)/firmware/product/Hi3798CV200/HD_FULL/vfmw_make.cfg
endif

export HWMEDIA_DIR = $(SDEC_KO_DIR)/hwmedia_v1.1

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(KCOM_DIR)/include
EXTRA_CFLAGS += -I$(KCOM_DIR)/drv/include
EXTRA_CFLAGS += -I$(KCOM_DIR)/api/include

EXTRA_CFLAGS += $(VFMW_CFLAGS)
EXTRA_CFLAGS += -I$(SDEC_KO_DIR)

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

####################################### objects #####################################
MOD_NAME := hi_svdec

ifeq ($(CFG_MSP_BUILDTYPE), y)
obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o
obj-$(CFG_MSP_BUILDTYPE) += hwmedia_v1.1/
else
obj-m += $(MOD_NAME).o
endif

#1. ko interface
hi_svdec-y += ./sdec_imedia_intf.o

# 2. soft decoder
hi_svdec-y += ./sdec_imedia.o
ifneq ($(CFG_MSP_BUILDTYPE), y)
hi_svdec-y += hwmedia.o
endif

# 3. dependence to VFMW
#hi_svdec-y += ../mem_manage.o
#hi_svdec-y += ../public.o
#hi_svdec-y += ../../../drv/linux_kernel/li_klib.o

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

all:
	$(AT)make -C $(HWMEDIA_DIR) ARCH=$(ARCH)
	$(AT)cp $(SDEC_KO_DIR)/hwmedia_v1.1/hwmedia.o $(SDEC_KO_DIR)/hwmedia.o
	$(AT)make -C $(LINUXROOT) ARCH=$(ARCH) CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(SDEC_KO_DIR) modules

clean:
	$(AT)make -C $(HWMEDIA_DIR) clean
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
	$(AT)cp -f $(MOD_NAME).ko $(MODULE_DIR)/

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko
