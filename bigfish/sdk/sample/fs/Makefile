################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

INCLUDE := -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common

LIB := -lpthread

################################################################################
image = sample_fs

SRC = $(wildcard *.c)

all: $(image)

$(image): $(SRC)
	@$(CC) -static  -o $@ $^  $(INCLUDE) $(LIB)

clean:
	@rm -fr $(image)

install:

uninstall:

