
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798cv200_a hi3798cv200 hi3716mv410 hi3716mv420),)
DEMUX_DRV_VER = demux_v1
else
DEMUX_DRV_VER = demux_v2
endif

CFLAGS += -I$(MSP_DIR)/drv/demux/$(DEMUX_DRV_VER)

MSP_OBJS += demux/$(DEMUX_DRV_VER)/mpi_demux.o           \
            demux/$(DEMUX_DRV_VER)/unf_demux.o           \
            demux/$(DEMUX_DRV_VER)/mpi_descrambler.o     \
            demux/$(DEMUX_DRV_VER)/unf_descrambler.o
