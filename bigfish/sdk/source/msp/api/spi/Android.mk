ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
AVPLAY_DIR := spi
LOCAL_SRC_FILES += $(AVPLAY_DIR)/unf_spi.c
endif
