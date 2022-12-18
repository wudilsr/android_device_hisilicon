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

PQ_DIR := $(PRODUCT_DIR)/driver/pq

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

CFLAGS  += -I$(PRODUCT_DIR)/driver/include
CFLAGS  += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS  += -I$(BOOT_DIR)/arch/arm/include
CFLAGS  += -I$(BOOT_DIR)/include
CFLAGS  += -D__PQ_PLATFORM_BOOT__

ifeq ($(CFG_HI_PQ_V1_0), y)
CFLAGS  += -DHI_PQ_VERSION_V1
OBJS    := $(PQ_DIR)/drv_pq.o
else ifeq ($(CFG_HI_PQ_V2_0), y)
CFLAGS  += -DHI_PQ_VERSION_V2
OBJS    := $(PQ_DIR)/pq_hal_comm.o $(PQ_DIR)/pq_hal_csc.o $(PQ_DIR)/pq_mng_csc.o $(PQ_DIR)/drv_pq.o
else ifeq ($(CFG_HI_PQ_V3_0), y)
CFLAGS  += -DHI_PQ_VERSION_V3
OBJS    := $(PQ_DIR)/pq_hal_comm.o $(PQ_DIR)/pq_hal_csc.o $(PQ_DIR)/pq_mng_csc.o $(PQ_DIR)/drv_pq.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
PQ_HAL_DIR := hi3798mv100
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a),)
PQ_HAL_DIR := hifone
endif

LIBS    := $(PQ_DIR)/libpq.a

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

prepare:
ifeq ($(CFG_HI_PQ_V2_0), y)
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v2_0/mng/pq_mng_csc.c $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v2_0/mng/pq_mng_csc.h $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v2_0/hal/pq_hal_csc.h $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v2_0/hal/pq_hal_csc.c $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v2_0/hal/pq_hal_comm.h $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v2_0/hal/pq_hal_comm.c $(PQ_DIR)/
else ifeq ($(CFG_HI_PQ_V3_0), y)
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v3_0/mng/pq_mng_csc.c $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v3_0/mng/pq_mng_csc.h $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v3_0/hal/$(PQ_HAL_DIR)/pq_hal_csc.h $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v3_0/hal/$(PQ_HAL_DIR)/pq_hal_csc.c $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v3_0/hal/common/pq_hal_comm.h $(PQ_DIR)/
	$(AT)cp -rf $(MSP_DIR)/drv/pq/pq_v3_0/hal/common/pq_hal_comm.c $(PQ_DIR)/
endif

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)

install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
