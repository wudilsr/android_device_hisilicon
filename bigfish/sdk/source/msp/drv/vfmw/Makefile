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
VFMW_DIR = vfmw_v4.0

ifeq ($(CFG_MSP_BUILDTYPE), y)
obj-$(CFG_MSP_BUILDTYPE) += vfmw_v4.0/

ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
obj-$(CFG_MSP_BUILDTYPE) += softlib/
endif
endif

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)make -C $(VFMW_DIR)/ all
endif
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
	$(AT)make -C softlib/ all
endif

clean:
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)make -C $(VFMW_DIR)/ clean
endif
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
	$(AT)make -C softlib/ clean
endif

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)make -C $(VFMW_DIR)/ install
endif
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
	$(AT)make -C softlib/ install
endif

uninstall:
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)make -C $(VFMW_DIR)/ uninstall
endif
ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
	$(AT)make -C softlib/ uninstall
endif

