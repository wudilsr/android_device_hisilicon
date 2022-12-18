ifneq ($(CFG_HI_LOADER_APPLOADER),y)
SYNC_DIR := sync
LOCAL_SRC_FILES += $(SYNC_DIR)/mpi_sync.c
endif
