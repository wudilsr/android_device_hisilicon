#=======================================
#   export varibale
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

#=======================================
#   local varibale
#=======================================
ADSP_DRV_DIR := $(MSP_DIR)/drv/adsp/adsp_v1_1

CFLAGS  +=  $(CFG_HI_CFLAGS)

CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(COMMON_DRV_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(MSP_DRV_INCLUDE)                    \
            -I$(MSP_DIR)/api/adec                   \
            -I$(MSP_DIR)/api/ci                     \
            -I$(MSP_DIR)/api/vo                     \
            -I$(MSP_DIR)/api/pdm/db                 \
            -I$(MSP_DIR)/api/pvr/include            \
            -I$(MSP_DIR)/api/mce/db                 \
            -I$(MSP_DIR)/drv/mce                    \
            -I$(MSP_DIR)/api/higo/include           \
            -I$(MSP_DIR)/api/jpeg/inc/inc_6b        \
            -I$(MSP_DIR)/api/jpeg/inc/inc_hard      \
            -I$(MSP_DIR)/api/jpge/include           \
            -I$(MSP_DIR)/drv/jpge/include           \
            -I$(MSP_DIR)/api/tde/include            \
            -I$(MSP_DIR)/drv/tde/include            \
            -I$(MSP_DIR)/api/ao                     \
            -I$(ADSP_DRV_DIR)/include               \
            -I$(ADSP_DRV_DIR)/include/comp          \
            -I$(MSP_DIR)/api/vpu/vpuapi             \
            -I$(MSP_DIR)/drv/vfmw/vfmw_v4.0         \
            -I$(MSP_DIR)/drv/vdec                   \
            -I$(MSP_DIR)/drv/pq                     \
            -I$(MSP_DIR)/drv/pq/mng                 \
            -I$(MSP_DIR)/drv/pq/hal                 \
            -I$(COMPONENT_DIR)/ha_codec/include     \
            -I$(COMPONENT_DIR)/ha_effect/include

MSP_LIBNAME     := libhi_msp
MSP_STATIC_LIB  := $(MSP_LIBNAME).a
MSP_SHARE_LIB   := $(MSP_LIBNAME).so

#--------------- HDMI ------------------
ifeq ($(CFG_HI_HDMI_SUPPORT_1_4),y)
HDMI_TARGET := hdmi_1_4
else ifeq ($(CFG_HI_HDMI_SUPPORT_2_0),y)
HDMI_TARGET := hdmi_2_0
endif

CFLAGS  += -I$(MSP_DIR)/drv/hdmi/$(HDMI_TARGET)
CFLAGS  += -DCONFIG_HDMI_STB_SDK

MSP_OBJS := hdmi/$(HDMI_TARGET)/mpi_hdmi.o         \
            hdmi/$(HDMI_TARGET)/unf_hdmi.o

#--------------- hdmirx -------------------
ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
CFLAGS  += -DHI_HDMI_RX_INSIDE

MSP_OBJS += hdmirx/mpi_hdmirx.o     \
            hdmirx/unf_hdmirx.o
endif

#--------------- GPIO ------------------
MSP_OBJS += gpio/unf_gpio.o

#--------------- VO ------------------
MSP_OBJS += vo/unf_vo.o         \
            vo/unf_display.o    \
            vo/unf_edid.o       \
            vo/mpi_win.o        \
            vo/mpi_disp_tran.o  \
            vo/mpi_disp.o       \
            vo/win_ratio.o       \
            vo/mpi_edid.o

#--------------- PDM ------------------
MSP_OBJS += pdm/unf_pdm.o pdm/mpi_pdm.o pdm/db/hi_db.o

#--------------- CIPHER ------------------
MSP_OBJS += cipher/unf_cipher.o
MSP_OBJS += cipher/mpi_cipher.o

#--------------- ADVCA ------------------
CFLAGS += -DSDK_SECURITY_ARCH_VERSION_V3

MSP_OBJS += advca/unf_advca.o

#--------------- PWM ------------------
MSP_OBJS += pwm/unf_pwm.o

#--------------- I2C ------------------
MSP_OBJS += i2c/unf_i2c.o

#--------------- FRONTEND ------------------
ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
MSP_OBJS += frontend/unf_tuner.o

ifeq ($(CFG_HI_DISEQC_SUPPORT),y)
CFLAGS += -DDISEQC_SUPPORT

MSP_OBJS += frontend/unf_diseqc.o
MSP_OBJS += frontend/unf_unicable.o
endif
endif

#--------------- IR ------------------
ifeq ($(CFG_HI_IR_TYPE_STD),y)
MSP_OBJS += ir/unf_ir_std.o
endif

ifeq ($(CFG_HI_IR_TYPE_S2),y)
MSP_OBJS += ir/unf_ir.o
endif

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
MSP_OBJS += ir/unf_ir_lirc.o
endif

#--------------- SPI ------------------
ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
MSP_OBJS += spi/unf_spi.o
endif

#--------------- DEMUX ------------------
include demux/Makefile

#--------------- TDE ------------------
MSP_OBJS += tde/src/unf_tde.o

#--------------- JPGE ------------------
MSP_OBJS += jpge/src/unf_jpge.o

#--------------- OTP ------------------
MSP_OBJS += otp/unf_otp.o otp/otp/mpi_otp.o

#--------------- PM ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFLAGS += -DHI_KEYLED_SUPPORT
endif

MSP_OBJS += pm/unf_pmoc.o pm/pmoc_usb_wakeup.o
endif

#--------------- AVPLAY ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(CFG_HI_MSP_BUILDIN),y)
CFLAGS += -DHI_MSP_BUILDIN
endif

MSP_OBJS += avplay/mpi_avplay.o     \
            avplay/unf_avplay.o     \
            avplay/avplay_frc.o
endif

#--------------- PVR ------------------
ifeq ($(CFG_HI_PVR_SUPPORT),y)
CFLAGS += -D_GNU_SOURCE -D_XOPEN_SOURCE=600
CFLAGS += -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64

ifeq ($(CFG_HI_PVR_L2_CACHE_SUPPORT),y)
CFLAGS += -DHI_PVR_L2_CACHE_SUPPORT
endif

ifdef CFG_HI_ADVCA_FUNCTION
SMOOTH_OBJS := $(shell [ -e pvr/lib/$(CFG_HI_TOOLCHAINS_NAME)/libhi_pvrsmooth_advca.a ] && cd pvr && $(AR) -x lib/$(CFG_HI_TOOLCHAINS_NAME)/libhi_pvrsmooth_advca.a && echo hi_pvr_smooth_ctrl.o)
else
SMOOTH_OBJS := $(shell [ -e pvr/lib/$(CFG_HI_TOOLCHAINS_NAME)/libhi_pvrsmooth.a ] && cd pvr && $(AR) -x lib/$(CFG_HI_TOOLCHAINS_NAME)/libhi_pvrsmooth.a && echo hi_pvr_smooth_ctrl.o)
endif

MSP_OBJS += pvr/hi_pvr_fifo.o           \
            pvr/hi_pvr_index.o          \
            pvr/hi_pvr_intf.o           \
            pvr/hi_pvr_play_ctrl.o      \
            pvr/hi_pvr_rec_ctrl.o       \
            pvr/hi_pvr_smooth_ctrl.o    \
            pvr/unf_pvr.o
endif

#--------------- SYNC ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
MSP_OBJS += sync/mpi_sync.o
endif

#--------------- AO ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(CFG_HI_AI_SUPPORT),y)
CFLAGS += -DHI_SOUND_AI_SUPPORT
endif

ifeq ($(CFG_HI_HAEFFECT_BASE_SUPPORT),y)
CFLAGS += -DHI_HAEFFECT_BASE_SUPPORT
endif

ifeq ($(CFG_HI_HAEFFECT_SRS_SUPPORT),y)
CFLAGS += -DHI_HAEFFECT_SRS_SUPPORT
endif

ifeq ($(CFG_HI_SND_SMARTVOLUME_SUPPORT),y)
CFLAGS += -DHI_SMARTVOLUME_SUPPORT
endif

MSP_OBJS += ao/unf_sound.o  \
            ao/mpi_ao.o     \
            ao/mpi_aef.o    \
            ao/mpi_vir.o    \
			ao/mpi_lowlatency.o

SMARTVOL_OBJS := $(shell cd ao/smartvol && $(AR) -x libsmartvol.a && echo *.o)

MSP_OBJS += $(addprefix ao/smartvol/, $(SMARTVOL_OBJS))
endif

#--------------- ADEC ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
CFLAGS += -DHI_ADEC_MAX_INSTANCE=$(CFG_HI_ADEC_MAX_INSTANCE)
CFLAGS += -DHI_ADEC_OUTPUTBUF_FRAMENUM=$(CFG_HI_ADEC_OUTPUTBUF_FRAMENUM)

ifdef CFG_HI_ADVCA_FUNCTION
IMPLE_OBJS := $(shell [ -e adec/lib/libhi_adecimple_advca.a ] && cd adec && $(AR) -x lib/libhi_adecimple_advca.a && echo mpi_adec_imple.o)
else
IMPLE_OBJS := $(shell [ -e adec/lib/libhi_adecimple.a ] && cd adec && $(AR) -x lib/libhi_adecimple.a && echo mpi_adec_imple.o)
endif

MSP_OBJS += adec/mpi_adec.o         \
            adec/mpi_adec_core.o    \
            adec/mpi_adec_imple.o

ifeq ($(CFG_HI_ADEC_AUDSPECTRUM_SUPPORT),y)
CFLAGS +=-DHI_ADEC_AUDSPECTRUM_SUPPORT

MSP_OBJS += adec/mpi_adec_waveform.o
endif
endif

#--------------- VDEC ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)

ifeq ($(CFG_HI_VDEC_MJPEG_SUPPORT),y)
CFLAGS += -DHI_VDEC_MJPEG_SUPPORT=1
else
CFLAGS += -DHI_VDEC_MJPEG_SUPPORT=0
endif

ifeq ($(CFG_HI_VDEC_REG_CODEC_SUPPORT),y)
CFLAGS += -DHI_VDEC_REG_CODEC_SUPPORT=1
else
CFLAGS += -DHI_VDEC_REG_CODEC_SUPPORT=0
endif

ifeq ($(CFG_HI_VDEC_USERDATA_CC_SUPPORT),y)
CFLAGS += -DHI_VDEC_USERDATA_CC_SUPPORT=1

ifneq ($(CFG_HI_VDEC_USERDATA_CC_BUFSIZE),)
CFLAGS += -DHI_VDEC_USERDATA_CC_BUFSIZE=$(CFG_HI_VDEC_USERDATA_CC_BUFSIZE)
else
CFLAGS += -DHI_VDEC_USERDATA_CC_BUFSIZE=0xC000
endif
else
CFLAGS += -DHI_VDEC_USERDATA_CC_SUPPORT=0
endif

ifeq ($(CFG_HI_VDEC_VPU_SUPPORT),y)
CFLAGS += -DHI_VDEC_VPU_SUPPORT=1
else
CFLAGS += -DHI_VDEC_VPU_SUPPORT=0
endif

ifeq ($(CFG_HI_VDEC_DFS_SUPPORT),y)
CFLAGS += -DHI_VDEC_DFS_SUPPORT=1
else
CFLAGS += -DHI_VDEC_DFS_SUPPORT=0
endif

MSP_OBJS += vdec/hi_codec.o         \
            vdec/mpi_vdec_adapter.o \
            vdec/mpi_vdec.o

ifeq ($(CFG_HI_VDEC_MJPEG_SUPPORT),y)
MSP_OBJS += vdec/mpi_vdec_mjpeg.o
endif

ifeq ($(CFG_HI_VDEC_VPU_SUPPORT),y)
MSP_OBJS += vdec/mpi_vdec_vpu.o
endif

endif

#--------------- WDG ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
MSP_OBJS += wdg/unf_wdg.o
endif
endif

#--------------- VPU ------------------
ifeq ($(CFG_HI_VDEC_VPU_SUPPORT),y)
CFLAGS  +=  -Dlinux
CFLAGS  +=  -I$(MSP_DIR)/api/vpu/vdi/linux/driver    \
            -I$(MSP_DIR)/api/vpu/vpuapi              \
            -I$(MSP_DIR)/api/vpu/vpuapi/coda9        \
            -I$(MSP_DIR)/api/vpu/vpuapi/wave4

MSP_OBJS += vpu/vdi/mm.o               \
            vpu/vdi/linux/vdi.o        \
            vpu/vdi/linux/vdi_osal.o   \
            vpu/vpuapi/product.o       \
            vpu/vpuapi/vpuapi.o        \
            vpu/vpuapi/vpuapifunc.o    \
            vpu/vpuapi/coda9/coda9.o   \
            vpu/vpuapi/wave4/wave4.o
endif

#--------------- MCE ------------------
ifneq ($(CFG_HI_LOADER_APPLOADER),y)
MSP_OBJS += mce/unf_mce.o
endif

#--------------- AI ------------------
ifeq ($(CFG_HI_AI_SUPPORT),y)
MSP_OBJS += ai/unf_ai.o  ai/mpi_ai.o
endif

#--------------- KEYLED ------------------
ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
MSP_OBJS += keyled/unf_keyled.o
endif

#--------------- AENC ------------------
ifeq ($(CFG_HI_AENC_SUPPORT),y)
ifeq ($(CFG_HI_AI_SUPPORT),y)
CFLAGS += -DHI_AENC_AI_SUPPORT
endif

MSP_OBJS += aenc/unf_aenc.o         \
            aenc/mpi_aenc.o         \
            aenc/mpi_aenc_core.o    \
            aenc/mpi_aenc_lsrc.o
endif

#--------------- CI ------------------
ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
MSP_OBJS += ci/unf_ci.o
MSP_OBJS += ci/mpi_ci.o
endif

#--------------- HDCP ------------------
ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
MSP_OBJS += hdcp/unf_hdcp.o
endif

#--------------- SCI ------------------
ifeq ($(CFG_HI_SCI_SUPPORT),y)
MSP_OBJS += sci/unf_sci.o
endif

#--------------- VI ------------------
ifeq ($(CFG_HI_VI_SUPPORT),y)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3718cv100 hi3719cv100),)
CFLAGS += -DHI_VI_REAL_SUPPORT
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
CFLAGS += -DHI_VI_REAL_SUPPORT
CFLAGS += -DHI_HDMI_RX_SUPPORT
endif
endif

MSP_OBJS += vi/mpi_vi.o  vi/unf_vi.o
endif

#--------------- VENC ------------------
ifeq ($(CFG_HI_VENC_SUPPORT),y)
MSP_OBJS += venc/mpi_venc.o  venc/unf_venc.o
endif

#--------------- PQ ------------------
ifeq ($(CFG_HI_PQ_V1_0),y)
MSP_OBJS += pq/pq_v1_0/unf_pq.o   \
            pq/pq_v1_0/mpi_pq.o   \
            pq/pq_v1_0/mpi_pq_tran.o
endif

ifeq ($(CFG_HI_PQ_V2_0),y)
MSP_OBJS += pq/pq_v2_0/mpi_pq.o   \
            pq/pq_v2_0/unf_pq.o
endif

ifeq ($(CFG_HI_PQ_V3_0),y)
MSP_OBJS += pq/pq_v2_0/mpi_pq.o   \
            pq/pq_v2_0/unf_pq.o
endif
#-------------------------------------

objects := jpeg png higo

ifneq ($(CFG_HI_LOADER_APPLOADER),y)
objects += omx
endif

ifeq ($(CFG_HI_GPU),y)
objects += gpu
endif

objects_clean       := $(addsuffix _clean, $(objects))
objects_install     := $(addsuffix _install, $(objects))
objects_uninstall   := $(addsuffix _uninstall, $(objects))

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#     rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
PHONY := all clean install uninstall

all: $(objects) msp_lib

clean: $(objects_clean) msp_lib_clean

install: $(objects_install) msp_lib_install

uninstall: $(objects_uninstall) msp_lib_uninstall

PHONY += $(objects) $(objects_clean) $(objects_install) $(objects_uninstall)

$(objects):
	$(AT)make -C $@

$(objects_clean):
	$(AT)make -C $(patsubst %_clean,%,$@) clean

$(objects_install):
	$(AT)make -C $(patsubst %_install,%,$@) install

$(objects_uninstall):
	$(AT)make -C $(patsubst %_uninstall,%,$@) uninstall

PHONY += msp_lib msp_lib_clean msp_lib_install msp_lib_uninstall

$(MSP_STATIC_LIB): $(MSP_OBJS)
	$(AT)$(AR) -rs $@ $(MSP_OBJS)

$(MSP_SHARE_LIB): $(MSP_OBJS)
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)$(CC) -shared -o $@ $(MSP_OBJS)
endif

msp_lib : $(MSP_STATIC_LIB) $(MSP_SHARE_LIB)

msp_lib_clean:
	$(AT)rm -rf $(MSP_OBJS) $(MSP_STATIC_LIB) $(MSP_SHARE_LIB)

msp_lib_install: msp_lib
	$(AT)cp -f  $(MSP_STATIC_LIB)   $(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -f  $(MSP_SHARE_LIB)    $(SHARED_LIB_DIR)/
endif

msp_lib_uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(MSP_STATIC_LIB) $(SHARED_LIB_DIR)/$(MSP_SHARE_LIB)

PHONY += target target_clean target_install target_uninstall

target: $(if $(findstring $(DIR), $(objects)), $(DIR), msp_lib)

target_clean: $(if $(findstring $(DIR), $(objects)), $(DIR)_clean, msp_lib_clean)

target_install: $(if $(findstring $(DIR), $(objects)), $(DIR)_install, msp_lib_install)

target_uninstall: $(if $(findstring $(DIR), $(objects)), $(DIR)_uninstall, msp_lib_uninstall)

%.o: %.c
	$(AT)echo "  CC      $@"
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

.PHONY: $(PHONY)
