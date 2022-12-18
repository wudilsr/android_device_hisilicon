################################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

INCLUDE := -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common \
	   -I$(SDK_DIR)/source/plugin/tee/tee_hisi/libteec/inc \
	   -I$(SDK_DIR)/source/plugin/tee/tee_hisi/libteec/sec_mmz/inc


LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)

LIB := -Wl,--start-group -lteec -Wl,--end-group

################################################################################
image = sample_secmmz sample_tee

all: $(image)

sample_secmmz: sample_secmmz.c
	$(AT)$(CC) -o $@ $^  $(INCLUDE) $(LIBPATH) $(LIB)

sample_tee: sample_tee.c
	$(AT)$(CC) -o $@ $^  $(INCLUDE) $(LIBPATH) $(LIB)


clean:
	$(AT)rm -f $(image)

install:

uninstall:

