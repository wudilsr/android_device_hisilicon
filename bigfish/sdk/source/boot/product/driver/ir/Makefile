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

CFLAGS   += -I$(PRODUCT_DIR)/driver/include
CFLAGS   += -I$(SDK_DIR)/source/common/include
CFLAGS   += -I$(BOOT_DIR)/include

LIBS     := libir.a

#OBJS += drv_ir.o
#OBJS += sample_test_ir.o
OBJS += cmd_ir.o	\
	nec.o		\
	rc6.o		\
	sony.o		\
	timer.o		\
	credit.o	\
	ir_drv.o	\
	ir_protocol_entry.o	\
	ir_protocols_descript.o	\
	ir_utils.o	\
	rc5.o	\
	tc9012.o
#===============================================================================
# rules
#===============================================================================

.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS)

install: all

uninstall:

$(LIBS): $(OBJS)
	$(AT)$(AR) -rc $@ $^
