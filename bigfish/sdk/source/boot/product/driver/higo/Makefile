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
BOOT_DIR  := $(SDK_DIR)/source/boot/miniboot
else
BOOT_DIR  := $(SDK_DIR)/source/boot/fastboot
endif

ifneq ($(O),)
PRODUCT_DIR := $(O)/product
else
PRODUCT_DIR := $(BOOT_DIR)/../product
endif

HIGO_DIR = .
HIFB_DIR = hifb

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



#===============================================================================
# higo include self
#===============================================================================
CFLAGS   += -I$(HIGO_DIR)/higo                        \
            -I$(HIGO_DIR)/tde                         \
            -I$(HIGO_DIR)/bmp                         \
            -I$(HIGO_DIR)/jpeg                        \
	    -I$(HIGO_DIR)/common                      \
            -I$(HIGO_DIR)/hifb                        \
            -I$(HIGO_DIR)/hifb/adp                    \
            -I$(HIGO_DIR)/hifb/adp/include            \
            -I$(HIGO_DIR)/hifb/adp/platform/include   \
            -I$(HIGO_DIR)/hifb/adp/platform/src       \
            -I$(PRODUCT_DIR)/driver/include           \
            -I$(PRODUCT_DIR)/driver/include_inc

CFLAGS   += -I$(BOOT_DIR)/include
CFLAGS   += -I$(BOOT_DIR)/include/linux/mtd

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3719cv100 hi3718cv100 hi3719mv100 hi3718mv100),)
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v1_0/adp
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v1_0/drv
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200_a),)
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v2_0/adp
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v2_0/drv
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v3_0/adp
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v3_0/drv
endif

CFLAGS   += -DHI_BUILD_IN_BOOT        \
            -DHIGO_BMP_SUPPORT        \
            -DHIGO_CODE_CUT           \
            -D__DISP_PLATFORM_BOOT__

#===============================================================================
# higo need src file
#===============================================================================
SRC     := $(wildcard $(HIGO_DIR)/higo/*.c)
SRC     += $(wildcard $(HIGO_DIR)/tde/*.c)
SRC     += $(wildcard $(HIGO_DIR)/jpeg/*.c)
SRC     += $(wildcard $(HIGO_DIR)/bmp/*.c)
SRC     += $(wildcard $(HIGO_DIR)/common/*.c)
SRC     +=  $(HIFB_DIR)/adp/platform/src/optm_hifb.c     \
            $(HIFB_DIR)/adp/platform/src/optm_hal.c      \
            $(HIFB_DIR)/adp/platform/src/optm_alg_csc.c  \
            $(HIFB_DIR)/adp/platform/src/optm_alg_gzme.c \
            $(HIFB_DIR)/adp/platform/src/optm_alg_gsharp.c


HIFB_HAL_DIR  := cv200
HIFB_PLAT_SRC := platform/src

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
HIFB_HAL_DIR  := hi3798cv100
HIFB_PLAT_SRC := platform
else
SRC += $(HIFB_DIR)/adp/platform/src/hifb_wbc.c
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a hi3798cv200),)
HIFB_HAL_DIR:=hi3798cv200
CFLAGS += -DCONFIG_JPEG_SET_SAMPLEFACTOR
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv410 hi3716mv420),)
CFLAGS += -DCONFIG_JPEG_SET_SAMPLEFACTOR
CFLAGS += -DCONFIG_JPEG_DRI_SUPPORT
endif


S_SRC := 

ifeq ($(wildcard $(MSP_DIR)/drv/hifb/adp/platform/alg/$(patsubst %-,%,$(CROSS_COMPILE))/*.S),)
SRC   += $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.c
else
S_SRC += $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.S
endif

OBJS := $(SRC:%.c=%.o)

ifneq ($(S_SRC),)
OBJS += $(S_SRC:%.S=%.o)
endif

#===============================================================================
# lib file name
#===============================================================================
LIBS := $(HIGO_DIR)/libhigo.a


#===============================================================================
# rules
#===============================================================================

.PHONY: all prepare clean install uninstall $(LIBS)


all: $(LIBS) 

prepare:
	$(AT)-test -e $(HIFB_DIR)/adp/platform/src || mkdir -p $(HIFB_DIR)/adp/platform/src
	$(AT)-test -e $(HIFB_DIR)/adp/platform/include || mkdir -p $(HIFB_DIR)/adp/platform/include
	$(AT)-test -f $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.h \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/platform/alg/*.c $(MSP_DIR)/drv/hifb/adp/platform/alg/*.h $(HIFB_DIR)/adp/platform/src
	$(AT)-test -f $(HIFB_DIR)/adp/platform/src/optm_hal.c \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/platform/$(HIFB_HAL_DIR)/*.c $(MSP_DIR)/drv/hifb/adp/platform/$(HIFB_HAL_DIR)/*.h $(HIFB_DIR)/adp/platform/src
	$(AT)-test -f $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.S \
|| test ! -f $(MSP_DIR)/drv/hifb/adp/platform/alg/$(patsubst %-,%,$(CROSS_COMPILE))/optm_alg_zme_coef.S \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/platform/alg/$(patsubst %-,%,$(CROSS_COMPILE))/*.S $(HIFB_DIR)/adp/platform/src
	$(AT)-test -f $(HIFB_DIR)/adp/platform/include/optm_hifb.h \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/platform/inc/*.h $(HIFB_DIR)/adp/platform/include
	$(AT)-test -f $(HIFB_DIR)/adp/platform/include/hifb_config.h \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/inc/hifb_config.h  $(HIFB_DIR)/adp/platform/include
	$(AT)-test -f $(HIFB_DIR)/adp/platform/src/hifb_wbc.c \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/${HIFB_PLAT_SRC}/*.c   $(HIFB_DIR)/adp/platform/src
	$(AT)-test -f $(HIFB_DIR)/adp/platform/include//hifb_wbc.h \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/inc/hifb_wbc.h $(HIFB_DIR)/adp/platform/include
	
clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf $(HIFB_DIR)/adp/platform/src
	$(AT)rm -rf $(HIFB_DIR)/adp/platform/include

install: all

uninstall:

$(LIBS):$(OBJS)
	$(AR) -rc $@ $^
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(HIFB_DIR)/adp/platform/src
	$(AT)rm -rf $(HIFB_DIR)/adp/platform/include
%.o:%.c
	$(AT)$(CC) $(CFLAGS) -c $^ -o $@
ifneq ($(S_SRC),)
$(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.o: $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.S
	$(AT)$(CC) $(CFLAGS) -c $^ -o $@
endif
