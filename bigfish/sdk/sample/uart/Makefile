################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

################################################################################
all:
	$(AT)$(CC) uarttest.c -o uarttest -static
	$(AT)chmod 777 uarttest

clean:
	$(AT)rm -rf uarttest

install:

uninstall:

