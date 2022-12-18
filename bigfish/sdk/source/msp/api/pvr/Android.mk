ifeq ($(CFG_HI_PVR_SUPPORT),y)
PVR_DIR := pvr
LOCAL_CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600
LOCAL_CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
LOCAL_SRC_FILES += $(PVR_DIR)/unf_pvr.c
LOCAL_SRC_FILES += $(PVR_DIR)/hi_pvr_fifo.c
LOCAL_SRC_FILES += $(PVR_DIR)/hi_pvr_index.c
LOCAL_SRC_FILES += $(PVR_DIR)/hi_pvr_intf.c
LOCAL_SRC_FILES += $(PVR_DIR)/hi_pvr_play_ctrl.c
LOCAL_SRC_FILES += $(PVR_DIR)/hi_pvr_rec_ctrl.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(PVR_DIR)/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpeg/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpge/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpegfmw/include
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/vdec
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpeg/include
LOCAL_LDFLAGS += $(LOCAL_PATH)/$(PVR_DIR)/lib/libhi_pvrsmooth.a
endif
