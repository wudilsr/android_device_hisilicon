ifeq ($(CFG_HI_VENC_SUPPORT),y)
VENC_DIR := venc
LOCAL_SRC_FILES += $(VENC_DIR)/mpi_venc.c
LOCAL_SRC_FILES += $(VENC_DIR)/unf_venc.c
endif
