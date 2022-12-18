ifeq ($(CFG_HI_VI_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3718cv100 hi3719cv100),)
LOCAL_CFLAGS += -DHI_VI_REAL_SUPPORT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
LOCAL_CFLAGS += -DHI_VI_REAL_SUPPORT
LOCAL_CFLAGS += -DHI_HDMI_RX_SUPPORT
endif
endif

VI_DIR := vi
LOCAL_SRC_FILES += $(VI_DIR)/mpi_vi.c
LOCAL_SRC_FILES += $(VI_DIR)/unf_vi.c
endif
