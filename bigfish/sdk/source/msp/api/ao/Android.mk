ifneq ($(CFG_HI_LOADER_APPLOADER),y)
AO_DIR := ao
LOCAL_SRC_FILES += $(AO_DIR)/unf_sound.c
LOCAL_SRC_FILES += $(AO_DIR)/mpi_ao.c
LOCAL_SRC_FILES += $(AO_DIR)/mpi_lowlatency.c
LOCAL_SRC_FILES += $(AO_DIR)/mpi_vir.c
LOCAL_SRC_FILES += $(AO_DIR)/mpi_aef.c

ifeq ($(CFG_HI_AI_SUPPORT),y)
LOCAL_CFLAGS += -DHI_SOUND_AI_SUPPORT
endif

LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DRV_INCLUDE)/../adsp/adsp_v1_1/include
ifeq ($(CFG_HI_HAEFFECT_BASE_SUPPORT),y)
LOCAL_CFLAGS += -DHI_HAEFFECT_BASE_SUPPORT
endif

ifeq ($(CFG_HI_HAEFFECT_SRS_SUPPORT),y)
LOCAL_CFLAGS += -DHI_HAEFFECT_SRS_SUPPORT
endif

ifeq ($(CFG_HI_SND_SMARTVOLUME_SUPPORT),y)
LOCAL_CFLAGS += -DHI_SMARTVOLUME_SUPPORT
LOCAL_LDFLAGS += $(LOCAL_PATH)/$(AO_DIR)/smartvol/libsmartvol.a
endif
endif
