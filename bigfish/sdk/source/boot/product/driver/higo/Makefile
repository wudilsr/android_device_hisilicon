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
ifeq ($(O),)
PRODUCT_DIR  := $(BOOT_DIR)/../product
else
PRODUCT_DIR  := $(O)/product
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

CFLAGS   += -I$(PRODUCT_DIR)/driver/include
CFLAGS   += -I$(PRODUCT_DIR)/driver/include_inc

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3719cv100 hi3718cv100 hi3719mv100 hi3718mv100),)
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v1_0/adp
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v1_0/drv
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200_a),)
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v2_0/adp
CFLAGS   += -I$(PRODUCT_DIR)/driver/disp/vdp_v2_0/drv
endif

CFLAGS   += -I$(BOOT_DIR)/include
CFLAGS   += -I$(BOOT_DIR)/include/linux/mtd
CFLAGS   += -I$(HIGO_DIR)/higo
CFLAGS   += -I$(HIGO_DIR)/tde
CFLAGS   += -I$(HIGO_DIR)/jpeg
CFLAGS   += -I$(HIGO_DIR)/hifb
CFLAGS   += -I$(HIGO_DIR)/hifb/adp
CFLAGS   += -I$(HIGO_DIR)/hifb/adp/include
CFLAGS   += -I$(HIGO_DIR)/hifb/adp/platform/include
CFLAGS   += -I$(HIGO_DIR)/hifb/adp/platform/src
CFLAGS += -DHI_BUILD_IN_BOOT
CFLAGS += -DHIGO_BMP_SUPPORT
CFLAGS += -DHIGO_CODE_CUT
CFLAGS += -D__DISP_PLATFORM_BOOT__

LIBS     := $(HIGO_DIR)/libhigo.a
SRC      := $(wildcard $(HIGO_DIR)/higo/*.c)
SRC     += $(wildcard $(HIGO_DIR)/tde/*.c)
SRC     += $(wildcard $(HIGO_DIR)/jpeg/*.c)
#SRC     += $(wildcard $(HIGO_DIR)/hifb/*.c)

HIFB_HAL_DIR:=cv200

ifeq ($(CFG_HI_CHIP_TYPE),hi3796cv100)
HIFB_HAL_DIR:=hi3798cv100
endif
ifeq ($(CFG_HI_CHIP_TYPE),hi3798cv100)
HIFB_HAL_DIR:=hi3798cv100
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3798cv200_a)
HIFB_HAL_DIR:=hi3798cv200
CFLAGS += -DCONFIG_JPEG_SET_SAMPLEFACTOR
endif

SRC += $(HIFB_DIR)/adp/platform/src/optm_hifb.c \
        $(HIFB_DIR)/adp/platform/src/optm_hal.c \
        $(HIFB_DIR)/adp/platform/src/optm_alg_csc.c \
        $(HIFB_DIR)/adp/platform/src/optm_alg_gzme.c \
        $(HIFB_DIR)/adp/platform/src/optm_alg_gsharp.c
S_SRC := 

ifeq ($(wildcard $(MSP_DIR)/drv/hifb/adp/platform/alg/$(patsubst %-,%,$(CROSS_COMPILE))/*.S),)
SRC += $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.c
else
S_SRC += $(HIFB_DIR)/adp/platform/src/optm_alg_zme_coef.S
endif

OBJS := $(SRC:%.c=%.o)
ifneq ($(S_SRC),)
OBJS += $(S_SRC:%.S=%.o)
endif


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
|| cp -rf $(MSP_DIR)/drv/hifb/adp/platform/include/*.h $(HIFB_DIR)/adp/platform/include
	$(AT)-test -f $(HIFB_DIR)/adp/include/hifb_config.h \
|| cp -rf $(MSP_DIR)/drv/hifb/adp/include/hifb_config.h  $(HIFB_DIR)/adp/platform/include
	
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
