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
VPSS_DIR := $(MSP_DIR)/drv/vpss

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
		-I$(KERNEL_DIR)/linux-3.10.y/drivers/hisilicon/sec_mmz

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

ifdef CFG_HI_VPSS_MAX_BUFFER_NUMB
EXTRA_CFLAGS += -DHI_VPSS_MAX_BUFFER_NUMB=$(CFG_HI_VPSS_MAX_BUFFER_NUMB)
else
EXTRA_CFLAGS += -DHI_VPSS_MAX_BUFFER_NUMB=10
endif

MOD_NAME := hi_vpss

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

#DRIVER_PATH := $(CURDIR)/vpss_v1_0

#FULL_PATH_DRV_SRCS := $(wildcard $(DRIVER_PATH)/*.c)
#FULL_PATH_DRV_SRCS := $(filter-out %.mod.c, $(FULL_PATH_DRV_SRCS))

#ODRV_OBJS  := $(patsubst %.c,%.o,$(FULL_PATH_DRV_SRCS))

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
    EXTRA_CFLAGS += -DHI_VPSS_DRV_VER_CV200
    DRIVER_PATH := $(CURDIR)/vpss_v1_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
    DRIVER_PATH := $(CURDIR)/vpss_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3798cv200_a hi3716mv410 hi3716mv420),)
    EXTRA_CFLAGS += -I$(VPSS_DIR)/vpss_v3_0/                    \
                    -I$(VPSS_DIR)/vpss_v3_0/hal                 \
                    -I$(VPSS_DIR)/vpss_v3_0/hal/hi3798mv100     \
                    -I$(VPSS_DIR)/vpss_v3_0/hal/hifoneb02       \
                    -I$(VPSS_DIR)/vpss_v3_0/hal/hi3716mv410     \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in             \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in/hi3798mv100 \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in/hifoneb02   \
                    -I$(VPSS_DIR)/vpss_v3_0/vpss_in/hi3716mv410 \
                    -I$(VPSS_DIR)/vpss_v3_0/alg
    DRIVER_PATH := $(CURDIR)/vpss_v3_0
endif

ifeq ($(DRIVER_PATH), $(CURDIR)/vpss_v1_0)
$(MOD_NAME)-y   :=  vpss_v1_0/vpss_osal.o               \
                    vpss_v1_0/vpss_alg_zme_intf.o       \
                    vpss_v1_0/vpss_alg_fmd_intf.o       \
                    vpss_v1_0/vpss_info.o               \
                    vpss_v1_0/vpss_alg_ratio.o          \
                    vpss_v1_0/vpss_alg_sharp.o          \
                    vpss_v1_0/vpss_alg_csc.o            \
                    vpss_v1_0/vpss_alg_dnr.o            \
                    vpss_v1_0/vpss_alg_rwzb.o           \
                    vpss_v1_0/vpss_alg.o                \
                    vpss_v1_0/vpss_fb.o                 \
                    vpss_v1_0/vpss_instance.o           \
                    vpss_v1_0/vpss_ctrl.o               \
                    vpss_v1_0/drv_vpss_intf_k.o         \
                    vpss_v1_0/vpss_alg_dei_intf.o       \
                    vpss_v1_0/vpss_reg_cv200.o          \
                    vpss_v1_0/vpss_hal_cv200.o

ALG_SRCS := $(wildcard $(VPSS_DIR)/vpss_v1_0/alg/vpss_alg_zme.c)

ifneq ($(ALG_SRCS),)
    $(MOD_NAME)-y += vpss_v1_0/alg/vpss_alg_zme.o
    $(MOD_NAME)-y += vpss_v1_0/alg/vpss_alg_fmd.o
else
    ifdef CFG_HI_ADVCA_FUNCTION
        ALG_DIR := vpss_v1_0/alg/$(CFG_HI_TOOLCHAINS_NAME)_advca
    else
        ALG_DIR := vpss_v1_0/alg/$(CFG_HI_TOOLCHAINS_NAME)
    endif

    $(MOD_NAME)-y += $(ALG_DIR)/vpss_alg_zme.o
    $(MOD_NAME)-y += $(ALG_DIR)/vpss_alg_fmd.o
endif
endif

ifeq ($(DRIVER_PATH), $(CURDIR)/vpss_v2_0)
$(MOD_NAME)-y   :=  vpss_v2_0/vpss_osal.o \
                    vpss_v2_0/vpss_info.o\
                    vpss_v2_0/vpss_fb.o \
                    vpss_v2_0/vpss_wbc.o \
                    vpss_v2_0/vpss_src.o \
                    vpss_v2_0/vpss_sttinf.o\
                    vpss_v2_0/vpss_alg_ratio.o\
                    vpss_v2_0/vpss_alg_rwzb.o\
                    vpss_v2_0/vpss_rwzb.o\
                    vpss_v2_0/vpss_instance.o\
                    vpss_v2_0/vpss_ctrl.o\
                    vpss_v2_0/vpss_alg_scd.o\
                    vpss_v2_0/drv_vpss_intf_k.o \
                    vpss_v2_0/vpss_reg_s5v100.o \
                    vpss_v2_0/vpss_hal_s5v100.o
endif

ifeq ($(DRIVER_PATH), $(CURDIR)/vpss_v3_0)
$(MOD_NAME)-y   :=  vpss_v3_0/vpss_osal.o \
                    vpss_v3_0/vpss_info.o\
                    vpss_v3_0/vpss_fb.o \
                    vpss_v3_0/vpss_wbc.o \
                    vpss_v3_0/vpss_in/vpss_src.o \
                    vpss_v3_0/vpss_his.o \
                    vpss_v3_0/vpss_sttinf.o \
                    vpss_v3_0/vpss_in/vpss_img.o \
                    vpss_v3_0/alg/vpss_alg_ratio.o \
                    vpss_v3_0/alg/vpss_alg_rwzb.o \
                    vpss_v3_0/alg/vpss_alg_scd.o\
                    vpss_v3_0/vpss_rwzb.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
$(MOD_NAME)-y   +=  \
            vpss_v3_0/hal/hi3798mv100/vpss_reg_3798m.o \
            vpss_v3_0/hal/hi3798mv100/vpss_hal_3798m.o \
            vpss_v3_0/vpss_in/hi3798mv100/vpss_in_3798mv100.o \
            vpss_v3_0/vpss_instance.o\
            vpss_v3_0/vpss_ctrl.o\
            vpss_v3_0/drv_vpss_intf_k.o \
            vpss_v3_0/vpss_trans_fb.o
endif

ifeq ($(CFG_HI_CHIP_TYPE), hi3798cv200_a)
$(MOD_NAME)-y   +=  \
            vpss_v3_0/hal/hifoneb02/vpss_reg_hifoneb02.o \
            vpss_v3_0/hal/hifoneb02/vpss_hal_hifoneb02.o  \
            vpss_v3_0/vpss_in/hifoneb02/vpss_in_hifoneb02.o \
            vpss_v3_0/vpss_instance.o\
            vpss_v3_0/vpss_ctrl.o\
            vpss_v3_0/drv_vpss_intf_k.o \
            vpss_v3_0/vpss_trans_fb.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
$(MOD_NAME)-y   +=  \
            vpss_v3_0/hal/hi3716mv410/vpss_reg_3716mv410.o \
            vpss_v3_0/hal/hi3716mv410/vpss_hal_3716mv410.o \
            vpss_v3_0/vpss_in/hi3716mv410/vpss_in_3716mv410.o \
            vpss_v3_0/vpss_instance.o\
            vpss_v3_0/vpss_ctrl.o\
            vpss_v3_0/drv_vpss_intf_k.o \
            vpss_v3_0/vpss_trans_fb.o
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

