ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a hi3798cv200 hi3716mv410 hi3716mv420),)
DEMUX_DIR := demux/demux_v1
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/demux/demux_v1
else
DEMUX_DIR := demux/demux_v2
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/demux/demux_v2
endif

LOCAL_SRC_FILES += $(DEMUX_DIR)/mpi_demux.c
LOCAL_SRC_FILES += $(DEMUX_DIR)/unf_demux.c
LOCAL_SRC_FILES += $(DEMUX_DIR)/mpi_descrambler.c
LOCAL_SRC_FILES += $(DEMUX_DIR)/unf_descrambler.c
