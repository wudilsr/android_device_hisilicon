ifneq ($(CFG_HI_LOADER_APPLOADER),y)
VDEC_DIR := vdec

ifeq ($(CFG_HI_TEE_SUPPORT),y)
LOCAL_CFLAGS += -DHI_TEE_SUPPORT
endif
ifeq (y,$(CFG_HI_VDEC_REG_CODEC_SUPPORT))
LOCAL_CFLAGS += -DHI_VDEC_REG_CODEC_SUPPORT=1
else
LOCAL_CFLAGS += -DHI_VDEC_REG_CODEC_SUPPORT=0
endif

ifeq (y,$(CFG_HI_VDEC_USERDATA_CC_SUPPORT))
LOCAL_CFLAGS += -DHI_VDEC_USERDATA_CC_SUPPORT=1

ifneq (,$(CFG_HI_VDEC_USERDATA_CC_BUFSIZE))
LOCAL_CFLAGS += -DHI_VDEC_USERDATA_CC_BUFSIZE=$(CFG_HI_VDEC_USERDATA_CC_BUFSIZE)
else
LOCAL_CFLAGS += -DHI_VDEC_USERDATA_CC_BUFSIZE=0xC000
endif

else
LOCAL_CFLAGS += -DHI_VDEC_USERDATA_CC_SUPPORT=0
endif

ifeq (y,$(CFG_HI_VDEC_VPU_SUPPORT))
LOCAL_CFLAGS += -DHI_VDEC_VPU_SUPPORT=1
else
LOCAL_CFLAGS += -DHI_VDEC_VPU_SUPPORT=0
endif
ifeq (y,$(CFG_HI_VDEC_MJPEG_SUPPORT))
LOCAL_CFLAGS += -DHI_VDEC_MJPEG_SUPPORT=1
LOCAL_SRC_FILES += $(VDEC_DIR)/mpi_vdec_mjpeg.c
else
LOCAL_CFLAGS += -DHI_VDEC_MJPEG_SUPPORT=0
endif

ifeq (y,$(CFG_HI_VDEC_DFS_SUPPORT))
LOCAL_CFLAGS += -DHI_VDEC_DFS_SUPPORT=1
else
LOCAL_CFLAGS += -DHI_VDEC_DFS_SUPPORT=0
endif

#===============================================================================
# 512M ddr memory config flags
#===============================================================================
ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_1080P_IN_512))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_512=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_512=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_MVC_IN_512))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_512=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_512=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_2160P_IN_512))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_512=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_512=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_4K_IN_512))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_512=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_512=0
endif

#===============================================================================
# 768M ddr memory config flags
#===============================================================================
ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_1080P_IN_768))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_768=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_768=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_MVC_IN_768))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_768=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_768=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_2160P_IN_768))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_768=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_768=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_4K_IN_768))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_768=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_768=0
endif
#===============================================================================
# 1024M ddr memory config flags
#===============================================================================
ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_1080P_IN_1024))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_1024=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_1024=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_MVC_IN_1024))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_1024=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_1024=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_2160P_IN_1024))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_1024=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_1024=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_4K_IN_1024))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_1024=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_1024=0
endif

#===============================================================================
# 2048M ddr memory config flags
#===============================================================================
ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_1080P_IN_2048))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_2048=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_1080P_IN_2048=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_MVC_IN_2048))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_2048=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_MVC_IN_2048=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_2160P_IN_2048))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_2048=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_2160P_IN_2048=0
endif

ifeq (y, $(CFG_HI_VIDEO_PRE_CAP_4K_IN_2048))
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_2048=1
else
LOCAL_CFLAGS += -DHI_VIDEO_PRE_CAP_4K_IN_2048=0
endif

#===============================================================================
# memory config end
#===============================================================================

LOCAL_SRC_FILES += $(VDEC_DIR)/hi_codec.c
LOCAL_SRC_FILES += $(VDEC_DIR)/mpi_vdec_adapter.c
LOCAL_SRC_FILES += $(VDEC_DIR)/mpi_vdec.c
ifeq (y,$(CFG_HI_VDEC_VPU_SUPPORT))
LOCAL_SRC_FILES += $(VDEC_DIR)/mpi_vdec_vpu.c
endif
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/vfmw/vfmw_v4.0
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/vdec
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpeg/inc/inc_6b_android/
LOCAL_C_INCLUDES += $(MSP_DIR)/api/jpeg/inc/inc_hard

endif
