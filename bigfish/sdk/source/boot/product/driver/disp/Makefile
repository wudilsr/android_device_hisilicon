#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../../../..
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================

ifeq ($(CFG_HI_MINIBOOT_SUPPORT),y)
BOOT_DIR    := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR    := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

COMMON_DIR  := $(PRODUCT_DIR)/driver/common
DISP_DIR    := $(PRODUCT)/driver/disp

ifndef CFLAGS
include $(BOOT_DIR)/define.mak
export MKFLAGS

CC := $(CROSS_COMPILE)gcc

gccincdir := $(shell $(CC) -print-file-name=include)

CFLAGS := -g -Os -D__KERNEL__ -D__ARM__ -fno-strict-aliasing -fno-common -ffixed-r8 \
	  -nostdinc -isystem $(gccincdir) $(MKFLAGS) -I$(PRODUCT_DIR) \
	  -fno-builtin -ffreestanding  -pipe -marm  -mabi=aapcs-linux  \
	  -mno-thumb-interwork -march=armv7-a \
	  -Wall -Wstrict-prototypes -fno-stack-protector
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
HAL_DIR := cv200
DRIVER_PATH := vdp_v1_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
HAL_DIR := s5v100
DRIVER_PATH := vdp_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a),)
HAL_DIR := hi3798cv200_a
EXTRA_CFLAGS += -I$(COMMON_DRV_INCLUDE)/hi3798cv200_a/
INCLUDE_DIR := hi3798cv200_a
CFLAGS += -DCHIP_HIFONEB02
#CFLAGS += -DFPGA_HIFONEB02
DRIVER_PATH := vdp_v2_0
endif


ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
HAL_DIR := 3798m
DRIVER_PATH := vdp_v2_0
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3719cv100 hi3718mv100),)
INCLUDE_DIR := hi3716cv200
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3719mv100),)
INCLUDE_DIR := hi3719mv100
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3718cv100),)
INCLUDE_DIR := hi3718cv100
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
INCLUDE_DIR := hi3798mv100
endif

CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc/$(INCLUDE_DIR)
CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
#CFLAGS  += -I$(SDK_DIR)/source/common/include
CFLAGS  += -I$(SDK_DIR)/source/boot/product/driver/include
#CFLAGS  += -I$(SDK_DIR)/source/msp/drv/include
#CFLAGS  += -I$(SDK_DIR)/source/msp/include

CFLAGS  += -D__DISP_PLATFORM_BOOT__ -D__DISP_SELF_START__ -D__DISP_D0_FOLLOW_D1__

ifeq ($(CFG_HI_DISP_USE_QPLL_SOLELY), y)
CFLAGS += -DHI_DISP_DOUBLE_HD_SUPPORT
endif

ifeq ($(CFG_HIFB_CURSOR_SUPPORT), y)
EXTRA_CFLAGS += -DHI_GFX_USE_G3
endif

ifeq ($(CFG_HI_VIDEO_BUFF_TYPE0), y)
EXTRA_CFLAGS += -DHI_VIDEO_BUFF_TYPE0
endif

CFLAGS  += -I$(DISP_DIR)/$(DRIVER_PATH)/alg
CFLAGS  += -I$(DISP_DIR)/$(DRIVER_PATH)/com
CFLAGS  += -I$(DISP_DIR)/$(DRIVER_PATH)/drv
CFLAGS  += -I$(DISP_DIR)/$(DRIVER_PATH)/hal/common
CFLAGS  += -I$(DISP_DIR)/$(DRIVER_PATH)/hal/$(HAL_DIR)


LIBS    := libdisp.a
SRC     := $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/*.c)
SRC     += $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/alg/*.c)
SRC     += $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/alg/*.c)
SRC     += $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/com/*.c)
SRC     += $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/drv/*.c)
SRC     += $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/hal/common/*.c)
SRC     += $(wildcard $(DISP_DIR)/$(DRIVER_PATH)/hal/$(HAL_DIR)/*.c)

OBJS    := $(SRC:%.c=%.o) 


#===============================================================================
# rules
#===============================================================================

.PHONY: all clean install uninstall $(LIBS) prepare

all:  $(LIBS)
	

prepare:
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/alg || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/alg
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/com || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/com
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/drv || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/drv
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/hal/common || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/hal/common
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/hal/cv200 || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/hal/cv200
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/hal/hi3798cv200_a || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/hal/hi3798cv200_a
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/hal/s5v100 || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/hal/s5v100
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/hal/3798m_a || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/hal/3798m_a
	$(AT)-test -e $(DISP_DIR)/$(DRIVER_PATH)/hal/3798m || mkdir -p $(DISP_DIR)/$(DRIVER_PATH)/hal/3798m
	echo $(DISP_DIR)

ifeq ($(DRIVER_PATH), vdp_v1_0)
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/alg/drv_disp_alg_csc* $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/alg/drv_disp_alg_rgb2yuv* $(DISP_DIR)/$(DRIVER_PATH)/alg 
else
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_rwzb.h   $(DISP_DIR)/$(DRIVER_PATH)/hal/common
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_rwzb.c   $(DISP_DIR)/$(DRIVER_PATH)/hal/common
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/alg/drv_disp_alg_rgb2yuv* $(DISP_DIR)/$(DRIVER_PATH)/alg
endif

ifeq ($(DRIVER_PATH), vdp_v1_0)
	cp -rf $(MSP_DIR)/drv/vo/vdp_v1_0/drv/drv_mcvn* $(MSP_DIR)/drv/vo/vdp_v1_0/drv/drv_vbi* $(DISP_DIR)/vdp_v1_0/drv/
	cp -rf $(MSP_DIR)/drv/vo/vdp_v1_0/drv/drv_cgms*  $(MSP_DIR)/drv/vo/vdp_v1_0/drv/drv_cgms* $(DISP_DIR)/vdp_v1_0/drv/
endif

	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/com/drv_disp_osal* $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/com/drv_disp_com.h $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/com/drv_disp_version.h $(DISP_DIR)/$(DRIVER_PATH)/com
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/drv/drv_display* $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/drv/drv_disp_priv.h $(DISP_DIR)/$(DRIVER_PATH)/drv
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_da* $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_alg_struct.h $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_hal* \
$(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_hw* $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_intf* \
$(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/common/drv_disp_reg.h   $(DISP_DIR)/$(DRIVER_PATH)/hal/common
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/$(HAL_DIR)/*.h $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/hal/$(HAL_DIR)/*.c $(DISP_DIR)/$(DRIVER_PATH)/hal/$(HAL_DIR)
	cp -rf $(MSP_DIR)/drv/vo/$(DRIVER_PATH)/drv_disp_adp2unf.c $(DISP_DIR)/$(DRIVER_PATH)
	find . -name "*.o" -o -name "*.so" -o -name "*.a" |xargs rm -fr
	
clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf $(DISP_DIR)/$(DRIVER_PATH)/*
	
install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
