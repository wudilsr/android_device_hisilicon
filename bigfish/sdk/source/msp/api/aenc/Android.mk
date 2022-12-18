ifeq ($(CFG_HI_AENC_SUPPORT),y)
AENC_DIR := aenc
LOCAL_SRC_FILES += $(AENC_DIR)/mpi_aenc.c
LOCAL_SRC_FILES += $(AENC_DIR)/mpi_aenc_core.c
LOCAL_SRC_FILES += $(AENC_DIR)/mpi_aenc_lsrc.c
LOCAL_SRC_FILES += $(AENC_DIR)/unf_aenc.c

ifeq ($(CFG_HI_AI_SUPPORT),y)
LOCAL_CFLAGS += -DHI_AENC_AI_SUPPORT
endif

endif
