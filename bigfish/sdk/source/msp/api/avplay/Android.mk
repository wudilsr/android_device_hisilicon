ifeq ($(CFG_HI_MSP_BUILDIN),y)
LOCAL_CFLAGS  +=  -DHI_MSP_BUILDIN
endif

ifeq ($(CFG_HI_TVP_SUPPORT), y)
LOCAL_CFLAGS += -DHI_TVP_SUPPORT
endif

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
AVPLAY_DIR := avplay
LOCAL_SRC_FILES += $(AVPLAY_DIR)/mpi_avplay.c
LOCAL_SRC_FILES += $(AVPLAY_DIR)/unf_avplay.c
LOCAL_SRC_FILES += $(AVPLAY_DIR)/avplay_frc.c
endif
