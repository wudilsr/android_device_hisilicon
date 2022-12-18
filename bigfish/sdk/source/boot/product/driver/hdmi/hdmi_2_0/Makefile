#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../../../../..
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

CFLAGS += -DHDMI_BUILD_IN_BOOT
CFLAGS += -DCONFIG_HDMI_STB_SDK

HAL := Hifone
HAL_DIR := hal/$(HAL)
CFLAGS   += -I$(PRODUCT_DIR)/driver/include
CFLAGS   += -I$(PRODUCT_DIR)/driver/include_inc
CFLAGS   += -I$(BOOT_DIR)/arch/arm/include
CFLAGS   += -I$(BOOT_DIR)/include
CFLAGS	 += -I$(SDK_DIR)/source/common/include
CFLAGS	 += -I$(PRODUCT_DIR)/logo/include
CFLAGS	 += -I$(PRODUCT_DIR)/driver/higo/include
CFLAGS	 += -I$(PRODUCT_DIR)/driver/hdmi/hdmi_2_0
CFLAGS	 += -I$(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/hal
CFLAGS	 += -I$(HAL_DIR)
CFLAGS	 += -I$(HAL_DIR)/driver
CFLAGS	 += -I$(HAL_DIR)/driver/common
CFLAGS	 += -I$(HAL_DIR)/driver/cra
CFLAGS	 += -I$(HAL_DIR)/driver/tx
CFLAGS	 += -I$(HAL_DIR)/driver/tx/tx_hdmi
CFLAGS	 += -I$(HAL_DIR)/driver/tx/videopath
CFLAGS	 += -I$(HAL_DIR)/library/log
CFLAGS	 += -I$(HAL_DIR)/library/malloc
CFLAGS	 += -I$(HAL_DIR)/library/obj
CFLAGS	 += -I$(HAL_DIR)/library/time
CFLAGS	 += -I$(HAL_DIR)/platform


LIBS    := ../libhdmi.a

OBJS    := boot_hdmi_intf.o
OBJS    += drv_hdmi_infoframe.o
OBJS    += $(HAL_DIR)/hdmi_hal.o		
OBJS    += $(HAL_DIR)/driver/common/si_drv_common.o \
		$(HAL_DIR)/driver/tx/si_drv_tx.o \
		$(HAL_DIR)/driver/tx/tx_hdmi/si_mod_tx_hdmi.o \
		$(HAL_DIR)/driver/tx/videopath/si_mod_videopath.o   \
		$(HAL_DIR)/driver/tx/videopath/si_mod_videopath_cra.o \
		$(HAL_DIR)/driver/cra/si_drv_cra.o	\
		$(HAL_DIR)/library/log/si_lib_log.o \
		$(HAL_DIR)/library/malloc/si_lib_malloc.o \
		$(HAL_DIR)/library/obj/si_lib_obj.o \
		$(HAL_DIR)/library/time/si_lib_time.o \
		$(HAL_DIR)/platform/platform.o \
		$(HAL_DIR)/platform/sii_time.o 									

#===============================================================================
# rules
#===============================================================================

.PHONY: all prepare clean install uninstall $(LIBS)

all: $(LIBS)

prepare:
	$(AT)cp -rf $(MSP_DIR)/drv/hdmi/hdmi_2_0/hal .
	$(AT)cp -rf $(MSP_DIR)/drv/hdmi/hdmi_2_0/drv_hdmi_infoframe.c .
	$(AT)cp -rf $(MSP_DIR)/drv/hdmi/hdmi_2_0/drv_hdmi_infoframe.h .
	$(AT)cp -rf $(MSP_DIR)/drv/hdmi/hdmi_2_0/drv_hdmi_common.h .
	$(AT)find  hal/ -name "*.o" |xargs rm -rf {}
clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/hal
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/drv_hdmi_infoframe.c 
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/drv_hdmi_infoframe.h 
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/drv_hdmi_common.h 
install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/hal
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/drv_hdmi_infoframe.c 
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/drv_hdmi_infoframe.h 
	$(AT)rm -rf $(PRODUCT_DIR)/driver/hdmi/hdmi_2_0/drv_hdmi_common.h 




