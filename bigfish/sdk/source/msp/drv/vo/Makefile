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
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DIR)/api/higo/include           \
                -I$(MSP_DIR)/api/vo

#EXTRA_CFLAGS += -DHI_DISP_TTX_SUPPORT  -DHI_DISP_CC_SUPPORT  -DHI_DISP_WSS_SUPPORT   -DHI_VO_SINGLE_VIDEO_SUPPORT
EXTRA_CFLAGS += -DHI_DISP_BUILD_FULL  -D__DISP_PLATFORM_SDK__ -D__DISP_D0_FOLLOW_D1__ -D__DISP_SELF_START__

ifeq ($(CFG_HI_DISP_USE_QPLL_SOLELY), y)
EXTRA_CFLAGS += -DHI_DISP_DOUBLE_HD_SUPPORT
endif

ifeq ($(CFG_HIFB_CURSOR_SUPPORT), y)
EXTRA_CFLAGS += -DHI_GFX_USE_G3
endif

ifeq ($(CFG_HI_DISP_TTX_SUPPORT), y)
EXTRA_CFLAGS += -DHI_DISP_TTX_SUPPORT
endif

#ifeq ($(CFG_HI_DISP_CC_SUPPORT), y)
#EXTRA_CFLAGS += -DHI_DISP_CC_SUPPORT
#endif

#ifeq ($(CFG_HI_DISP_WSS_SUPPORT), y)
#EXTRA_CFLAGS += -DHI_DISP_WSS_SUPPORT
#endif

ifeq ($(CFG_HI_DISP_G1_ATTACH_HD_SUPPORT), y)
EXTRA_CFLAGS += -DHI_DISP_ATTACH_OSD_SUPPORT
endif

ifeq ($(CFG_HI_DISP_CSC_MODE_RGB), y)
EXTRA_CFLAGS += -DHI_DISP_MODE_TC
endif

ifeq ($(CFG_HI_VO_WRAP_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_WRAP_SUPPORT
endif

ifeq ($(CFG_HI_DISP_CGMS_SUPPORT), y)
EXTRA_CFLAGS += -DHI_DISP_CGMS_SUPPORT
endif

ifeq ($(CFG_HI_DISP_LCD_SUPPORT), y)
EXTRA_CFLAGS += -DHI_DISP_LCD_SUPPORT
endif

ifeq ($(CFG_HI_VO_MOSAIC_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_MOSAIC_SUPPORT
endif

ifeq ($(CFG_HI_VO_SINGLE_VIDEO_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_SINGLE_VIDEO_SUPPORT
endif

ifeq ($(CFG_HI_VO_STILLFRAME_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_STILLFRAME_SUPPORT
endif

ifeq ($(CFG_HI_VO_DUMPFRAME_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_DUMPFRAME_SUPPORT
endif

ifeq ($(CFG_HI_VO_MOSAIC_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_MOSAIC_SUPPORT
endif

EXTRA_CFLAGS += -DHI_VO_SHARPNESS_SUPPORT

ifeq ($(CFG_HI_VDEC_DEINTERLACE_SUPPORT), y)
EXTRA_CFLAGS += -DHI_VO_HD_VIDEO_DO_DEI
endif

ifeq ($(CFG_HI_VIDEO_BUFF_TYPE0), y)
EXTRA_CFLAGS += -DHI_VIDEO_BUFF_TYPE0
endif

ifeq ($(CFG_HI_DISP_VIRT_OFFSET_EFFECT_WHEN_FULLSCREEN), y)
EXTRA_CFLAGS += -DHI_VO_OFFSET_EFFECTIVE_WHEN_WIN_FULL
endif

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

#EXTRA_CFLAGS += -Os
STRIP=$(CFG_HI_TOOLCHAINS_NAME)-strip

MOD_NAME := hi_vou

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

VO_DIR := $(shell cd $(MSP_DIR)/drv/vo && pwd)

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
HAL_DIR := cv200
VO_VER := vdp_v1_0
endif


ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
HAL_DIR := mv410
VO_VER := vdp_v3_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
HAL_DIR := s5v100
VO_VER := vdp_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a),)
HAL_DIR := hi3798cv200_a
EXTRA_CFLAGS += -I$(COMMON_DRV_INCLUDE)/hi3798cv200_a/
EXTRA_CFLAGS += -DCHIP_HIFONEB02
#EXTRA_CFLAGS += -DFPGA_HIFONEB02
VO_VER := vdp_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
HAL_DIR := 3798m
VO_VER := vdp_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3798cv200_a hi3716mv420),)
ifeq ($(CFG_ANDROID_PRODUCT),y)
ifneq ($(CFG_HI_LOADER_SUPPORT),y)
EXTRA_CFLAGS += -I$(LINUX_DIR)/drivers/staging/android
EXTRA_CFLAGS += -DHI_VO_WIN_SYNC_SUPPORT
endif
endif
endif

ifeq ($(CFG_ANDROID_PRODUCT),y)
EXTRA_CFLAGS += -DHI_VO_DISP_ISOLATED_FMT_SUPPORT
endif

EXTRA_CFLAGS += -I$(VO_DIR)/$(VO_VER)                   \
                -I$(VO_DIR)/$(VO_VER)/include           \
                -I$(VO_DIR)/$(VO_VER)/alg               \
                -I$(VO_DIR)/$(VO_VER)/com               \
                -I$(VO_DIR)/$(VO_VER)/drv               \
                -I$(VO_DIR)/$(VO_VER)/hal/common        \
                -I$(VO_DIR)/$(VO_VER)/hal/$(HAL_DIR)

VO_SRCS := $(wildcard $(VO_DIR)/$(VO_VER)/hal/common/*.c)
VO_SRCS += $(wildcard $(VO_DIR)/$(VO_VER)/hal/$(HAL_DIR)/*.c)
VO_SRCS += $(wildcard $(VO_DIR)/$(VO_VER)/alg/*.c)
VO_SRCS += $(wildcard $(VO_DIR)/$(VO_VER)/*.c)
VO_SRCS += $(wildcard $(VO_DIR)/$(VO_VER)/com/*.c)
VO_SRCS += $(wildcard $(VO_DIR)/$(VO_VER)/drv/*.c)

VO_SRCS := $(filter-out %.mod.c, $(VO_SRCS))

VO_OBJS := $(patsubst $(VO_DIR)/%.c, %.o, $(VO_SRCS))

ifeq ($(VO_VER), vdp_v1_0)
ifeq ($(findstring $(VO_VER)/alg/drv_disp_alg_zme.o, $(VO_OBJS)),)
ifdef CFG_HI_ADVCA_FUNCTION
VO_OBJS += $(VO_VER)/alg/$(CFG_HI_TOOLCHAINS_NAME)/drv_disp_alg_zme_advca.o
else
VO_OBJS += $(VO_VER)/alg/$(CFG_HI_TOOLCHAINS_NAME)/drv_disp_alg_zme.o
endif
endif
endif

$(MOD_NAME)-y = $(VO_OBJS)

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules
	$(AT)$(STRIP)  --strip-unneeded $(VO_DIR)/hi_vou.ko

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/
endif

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

