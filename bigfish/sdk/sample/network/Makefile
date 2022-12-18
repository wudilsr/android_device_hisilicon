ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../..

include $(SDK_DIR)/base.mak
endif
include $(SAMPLE_DIR)/base.mak

################################################################################
CROSS_COMPILE         := \
	$(if $(CROSS_COMPILE),$(CROSS_COMPILE),arm-hisiv200-linux-)

CC    ?= $(CROSS_COMPILE)gcc

PWD         := $(shell pwd)
IPCFG_DIR   := $(PWD)/ipcfg
SOCKET_DIR  := $(PWD)/socket
################################################################################

all: sample_ipcfg sample_socket

sample_ipcfg:
	make -C $(IPCFG_DIR)

sample_socket:
	make -C $(SOCKET_DIR)

clean:
	make -C $(IPCFG_DIR)  clean
	make -C $(SOCKET_DIR) clean

install:

uninstall:

