
#=======================================
#	export variable
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../..
    endif

include $(SDK_DIR)/base.mak
endif

#=======================================
#	local variable
#======================================
JPGE_SUPPORT := y

ifeq ($(CFG_HI_CHIP_TYPE),hi3718mv100)
JPGE_SUPPORT := n
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3719mv100)
JPGE_SUPPORT := n
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3716mv410)
JPGE_SUPPORT := n
endif

objects := gpio ir pdm pq hdmi vo hifb tde jpeg 

ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
objects += hdmirx
endif

ifeq ($(CFG_HI_LOADER_RECOVERY),y)
objects += png
else
objects += i2c demux cipher otp advca
endif

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifneq ($(CFG_HI_LOADER_RECOVERY),y)
objects += sync adsp aiao aflt adec vfmw vdec vpss mce png pwm omxvdec pm

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
objects += wdg
endif

ifeq ($(JPGE_SUPPORT),y)
objects += jpge
endif

ifeq ($(CFG_ANDROID_PRODUCT),y)
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
objects += gfx2d
endif
endif
endif
endif

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
objects += frontend
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
objects += pvr
endif

ifeq ($(CFG_HI_GPU),y)
objects += gpu
endif

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
objects += keyled
endif

ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
objects += spi
endif

ifeq ($(CFG_HI_SCI_SUPPORT),y)
objects += sci
endif

ifeq ($(CFG_HI_AENC_SUPPORT),y)
objects += aenc
endif

ifeq ($(CFG_HI_VENC_SUPPORT),y)
objects += venc
endif

ifeq ($(CFG_HI_VDEC_VPU_SUPPORT),y)
objects += vpu
endif

ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
objects += ci
ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
objects += cimaxplus
endif
endif

ifeq ($(CFG_HI_SND_SIF_SUPPORT),y)
objects += sif
endif

ifeq ($(CFG_HI_SND_AMP_SUPPORT),y)
objects += amp
endif

ifeq ($(CFG_HI_VI_SUPPORT),y)
objects += vi
objects += vad
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
objects += ndpt
endif

ifeq ($(CFG_HI_ADAC_SUPPORT),y)
objects += adac
endif

ifeq ($(CFG_MSP_BUILDTYPE),y)
objects += base

obj-$(CFG_MSP_BUILDTYPE) += ${addsuffix /,${objects}}

objects :=

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
objects += ir
endif

endif



objects_clean:=${addsuffix _clean,${objects}}
objects_install:=${addsuffix _install,${objects}}
objects_uninstall:=${addsuffix _uninstall,${objects}}
objects_prepare:=${addsuffix _prepare,${objects}}


#=================================================================
#	  rules
#=================================================================

.PHONY: all clean install uninstall ${objects} ${objects_clean} ${objects_install} ${objects_uninstall} ${objects_prepare}

all: ${objects}

clean: ${objects_clean}
	$(AT)rm -rf  *.o
	$(AT)rm -rf  .*.o.cmd
	$(AT)rm -rf  modules.order modules.builtin

install: ${objects_install}

uninstall: ${objects_uninstall}

prepare: ${objects_prepare}

${objects}:
	make -C $@

${objects_clean}:
	make -C ${patsubst %_clean,%,$@} clean

${objects_install}:
	make -C ${patsubst %_install,%,$@} install

${objects_uninstall}:
	make -C ${patsubst %_uninstall,%,$@} uninstall

${objects_prepare}:
	@echo "prepare "$@

