#=============DIR======================================================================
#SDK_DIR=${SAMPLE_DIR}/..
#PUB_DIR=${SDK_DIR}/pub
SDK_INC_DIR=${PUB_DIR}/include
SDK_STATIC_LIB_DIR=${PUB_DIR}/lib/static
SDK_SHARE_LIB_DIR=${PUB_DIR}/lib/share
#=============TOOL CHAINS===================================================================
AR=${CFG_HI_TOOLCHAINS_NAME}-ar
AS=${CFG_HI_TOOLCHAINS_NAME}-as
LD=${CFG_HI_TOOLCHAINS_NAME}-ld
CPP=${CFG_HI_TOOLCHAINS_NAME}-cpp
CC=${CFG_HI_TOOLCHAINS_NAME}-gcc
NM=${CFG_HI_TOOLCHAINS_NAME}-nm
STRIP=${CFG_HI_TOOLCHAINS_NAME}-strip
OBJCOPY=${CFG_HI_TOOLCHAINS_NAME}-objcopy
OBJDUMP=${CFG_HI_TOOLCHAINS_NAME}-objdump

#==============COMPILE TOOLS=================================================================
CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)-

#==============COMPILE OPTIONS================================================================
#3. export CFG_HI_SAMPLE_CFLAGS
CFG_HI_SAMPLE_CFLAGS :=

ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-hisiv200-linux)
    #CFG_HI_SAMPLE_CFLAGS+=-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
    #CFG_HI_SAMPLE_CFLAGS+=-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=neon
    CFG_HI_SAMPLE_CFLAGS+=-march=armv7-a -mcpu=cortex-a9
endif

ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-histbv300-linux)
ifeq (${CFG_HI_CHIP_TYPE},hi3798mv100)
CFG_HI_SAMPLE_CFLAGS += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=vfpv4-d16
else
ifeq (${CFG_HI_CHIP_TYPE},hi3796mv100)
CFG_HI_SAMPLE_CFLAGS += -mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=vfpv4-d16
else
CFG_HI_SAMPLE_CFLAGS += -march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16
endif
endif
endif

CFG_HI_SAMPLE_CFLAGS+= -D_GNU_SOURCE -Wall -O2 -g $(CFG_CFLAGS) -ffunction-sections -fdata-sections -Wl,--gc-sections
CFG_HI_SAMPLE_CFLAGS+= -DCHIP_TYPE_${CFG_HI_CHIP_TYPE} -DCFG_HI_SDK_VERSION=${CFG_HI_SDK_VERSION}
CFG_HI_SAMPLE_CFLAGS+= ${CFG_HI_BOARD_CONFIGS}

ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
CFG_HI_SAMPLE_CFLAGS += -DHI_HDMI_RX_INSIDE
endif

SYS_LIBS := -lpthread -lrt -lm -ldl

HI_LIBS := -lhi_common -lpng -lhigo -lhigoadp -ljpeg -lhi_resampler

HI_LIBS += -lhi_msp

ifeq ($(CFG_HI_HAEFFECT_BASE_SUPPORT),y)
HI_LIBS += -lhi_aef_base
endif

ifeq ($(CFG_HI_HAEFFECT_SRS_SUPPORT),y)
HI_LIBS += -lhi_aef_srs
endif

ifeq ($(CFG_HI_ZLIB_SUPPORT),y)
HI_LIBS += -lz
endif

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT),y)
HI_LIBS += -lfreetype
endif

ifeq ($(CFG_HI_PES_SUPPORT),y)
HI_LIBS += -lhi_pes
endif

ifeq ($(CFG_HI_CAPTION_SUBT_SUPPORT),y)
HI_LIBS += -lhi_subtitle
endif

ifeq ($(CFG_HI_CAPTION_SO_SUPPORT),y)
HI_LIBS += -lhi_so
endif

ifeq ($(CFG_HI_CAPTION_TTX_SUPPORT),y)
HI_LIBS += -lhi_ttx
endif

ifeq ($(CFG_HI_CAPTION_CC_SUPPORT),y)
HI_LIBS += -lhi_cc
endif

ifeq ($(CFG_HI_VP_SUPPORT),y)
HI_LIBS += -lhi_vp -lrtp
endif

ifeq ($(CFG_HI_PLAYER_SUPPORT),y)
HI_LIBS += -lhi_charsetMgr -lsubdec -lplayer
endif

COMMON_FILES := $(SAMPLE_DIR)/common/hi_adp_demux.o     \
                $(SAMPLE_DIR)/common/hi_psi_si.o        \
                $(SAMPLE_DIR)/common/hi_adp_data.o      \
                $(SAMPLE_DIR)/common/hi_adp_hdmi.o      \
                $(SAMPLE_DIR)/common/hi_adp_mpi.o       \
                $(SAMPLE_DIR)/common/hi_adp_search.o    \
                $(SAMPLE_DIR)/common/hi_filter.o        \
                $(SAMPLE_DIR)/common/search.o

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
COMMON_FILES += $(SAMPLE_DIR)/common/hi_adp_tuner.o
endif

ifeq ($(CFG_HI_PVR_SUPPORT),y)
COMMON_FILES += $(SAMPLE_DIR)/common/hi_adp_pvr.o
endif

AT := @
