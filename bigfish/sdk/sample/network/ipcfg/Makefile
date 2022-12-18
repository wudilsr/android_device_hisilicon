ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR     := $(shell pwd)/../../..

include $(SDK_DIR)/base.mak
endif

LIB         := -lhi_common -lpthread
INCLUDE     := -I"$(COMMON_DIR)/include" -I"$(SAMPLE_DIR)/common"
################################################################################
CROSS_COMPILE         := \
	$(if $(CROSS_COMPILE),$(CROSS_COMPILE),arm-hisiv200-linux-)

CC    ?= $(CROSS_COMPILE)gcc

################################################################################

image = sample_ipcfg

all:$(image)

$(image): sample_ipcfg.c hi_api_eth.c
	@$(CC) -static  -o $@ $^  -I"$(MSP_DIR)/include" \
		$(INCLUDE) -L$(STATIC_LIB_DIR) $(LIB)
  
clean:
	-@rm -f $(image)
	
