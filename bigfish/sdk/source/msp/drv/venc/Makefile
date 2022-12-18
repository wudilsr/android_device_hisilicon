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

ifeq ($(CFG_HI_CPU_ARCH),arm64)
ARCH=$(CFG_HI_CPU_ARCH)
else
ARCH=arm
endif

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

ifeq ($(CFG_HI_CHIP_TYPE),hi3716cv200)
EXTRA_CFLAGS += -D__VENC_3716CV200_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3716mv400)
EXTRA_CFLAGS += -D__VENC_3716CV200_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3719cv100)
EXTRA_CFLAGS += -D__VENC_3716CV200_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3718cv100)
EXTRA_CFLAGS += -D__VENC_3716CV200_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3718mv100)
EXTRA_CFLAGS += -D__VENC_3716CV200_CONFIG__  -D__VENC_3719MV100_CONFIG__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3719mv100)
EXTRA_CFLAGS += -D__VENC_3716CV200_CONFIG__  -D__VENC_3719MV100_CONFIG__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3751v100)
EXTRA_CFLAGS += -D__VENC_S5V100_CONFIG__
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3751v100b)
EXTRA_CFLAGS += -D__VENC_S5V100_CONFIG__
endif

ifeq  ($(CFG_HI_CHIP_TYPE),hi3796cv100)
EXTRA_CFLAGS += -D__VENC_S5V100_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq  ($(CFG_HI_CHIP_TYPE),hi3798cv100)
EXTRA_CFLAGS += -D__VENC_S5V100_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq  ($(CFG_HI_CHIP_TYPE),hi3798mv100)
EXTRA_CFLAGS += -D__VENC_98M_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq  ($(CFG_HI_CHIP_TYPE),hi3796mv100)
EXTRA_CFLAGS += -D__VENC_98M_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq  ($(CFG_HI_CHIP_TYPE),hi3798cv200_a)
EXTRA_CFLAGS += -D__VENC_98M_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

ifeq  ($(CFG_HI_CHIP_TYPE),hi3716mv420)
EXTRA_CFLAGS += -D__VENC_98M_CONFIG__
EXTRA_CFLAGS += -D__VENC_SUPPORT_JPGE__
endif

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/venc                   \
                -I$(MSP_DIR)/drv/venc                   \
                -I$(MSP_DIR)/drv/jpge/include           \
                -I$(MSP_DIR)/api/jpge/include

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

MOD_NAME := hi_venc

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   :=  drv_venc_osal.o      \
                    drv_venc_intf.o      \
                    drv_venc.o           \
                    drv_venc_efl.o       \
                    drv_omxvenc.o        \
                    drv_omxvenc_efl.o    \
                    drv_venc_buf_mng.o   \
                    drv_venc_queue_mng.o \
                    drv_venc_proc.o      \
                    hal_venc.o

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(LINUX_DIR) ARCH=$(ARCH) CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/
endif

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

