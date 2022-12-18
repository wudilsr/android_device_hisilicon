JPEG_SAMPLE=$(shell pwd)

#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)

CFLAGS +=   -I$(SDK_INC_DIR)                     \
	    -I$(JPEG_SAMPLE)/../inc              \
	    -I$(MSP_DIR)/api/jpeg/grc_cmm_inc    \
	    -I$(MSP_DIR)/api/jpeg/inc/inc_test   \
	    -I$(MSP_DIR)/drv/jpeg/include        \
	    -I$(COMMON_DIR)/include              \
            -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

COMMON_SRC := $(patsubst %.o, %.c, $(COMMON_FILES))

SRC = $(wildcard *.c)

ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
SRC := $(filter-out dec_virmem_crop_lines.c, $(SRC))
SRC := $(filter-out dec_virmem_crop_phymem.c, $(SRC))
SRC := $(filter-out dec_virmem_crop_virmem.c, $(SRC))
endif

CFLAGS += -DCONFIG_HI_SDK_JPEG_VERSION
CFLAGS += -DCONFIG_GFX_STB_SDK


APP= $(SRC:%.c=%)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(APP)

$(APP):  %: %.c
	$(AT)$(CC) -o $@  $< $(COMMON_SRC) $(LIBPATH) $(LIB) $(CFLAGS)
clean:
	-$(AT)rm -f $(APP)
install:
	$(AT)cp -rf $(APP) $(JPEG_SAMPLE)/../exe
uninstall:

