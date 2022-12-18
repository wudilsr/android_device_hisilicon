#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += -I$(SDK_INC_DIR)
CFLAGS += -DCHIP_TYPE_${CFG_HI_CHIP_TYPE}

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

image = sample_encryptHdcpKey

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(image)

sample_encryptHdcpKey: sample_encryptHdcpKey.c
	@echo "compiling $@..."
	@$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LIB)

clean:
	-@rm -f $(image)

install:

uninstall:

