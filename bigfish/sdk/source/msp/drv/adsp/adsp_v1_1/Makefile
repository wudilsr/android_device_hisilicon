#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../../..
    endif

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variables
#===============================================================================
ADSP_DRV_INCLUDE    := $(MSP_DIR)/drv/adsp/adsp_v1_1/include
ADSP_DRV_INCLUDE_1  := $(MSP_DIR)/drv/adsp/adsp_v1_1/include/comp
HA_CODEC_INCLUDE    := $(COMPONENT_DIR)/ha_codec/include
HA_EFFECT_INCLUDE   := $(COMPONENT_DIR)/ha_effect/include

#===============================================================================
# Tensilica Audio Lib
#===============================================================================
#ADSP_XA_INCLUDE    =$(SDK_DIR)/source/msp/drv/adsp/adsp_v1_1/hifi/component/external/xtensa/include
#ADSP_XA_MP3DEC_INC =$(SDK_DIR)/source/msp/drv/adsp/adsp_v1_1/hifi/component/external/xtensa/mp3_dec/ulibxa_mp3_dec/include

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(ADSP_DRV_INCLUDE)                   \
                -I$(HA_CODEC_INCLUDE)                   \
                -I$(HA_EFFECT_INCLUDE)                  \
                -I$(ADSP_XA_INCLUDE)                    \
                -I$(ADSP_XA_MP3DEC_INC)                 \
                -I$(ADSP_DRV_INCLUDE_1)

##just for TQE test for hw aoe
#CFG_TQE_FOR_SND_AOE_HW_SUPPORT = Y

ifeq ($(CFG_HI_SND_AOE_HW_SUPPORT),y)
#CFG_DSP_COMPILER_SUPPORT = y
endif

ifneq ($(CFG_HI_SND_AOE_HW_SUPPORT),y)
#simulate support

HIFIDIR := ./hifi

EXTRA_CFLAGS +=  \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/common/include \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/aoe/include \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/aflt/include \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/aoe/src/include \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/component/codec/iapcm_dec \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/component/codec/iamp3_dec \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/component/effect/base_effect\
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1

ifeq ($(CFG_TQE_FOR_SND_AOE_HW_SUPPORT),y)
EXTRA_CFLAGS +=  \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/component/external/xtensa/resampler/ulibxa_resampler/include/resampler \
		-I$(MSP_DIR)/drv/adsp/adsp_v1_1/$(HIFIDIR)/component/external/xtensa/include
endif

EXTRA_CFLAGS += -DHI_SND_AOE_SWSIMULATE_SUPPORT
EXTRA_CFLAGS += -DHI_SND_AFLT_SWSIMULATE_SUPPORT
else
EXTRA_CFLAGS += -DHI_SND_DSP_HW_SUPPORT
endif

EXTRA_CFLAGS += -DINTERLEAVED_OUTPUT

EXTRA_CFLAGS += -DPCM_DECODER_SUPPORT
#only use debug for mp3 decoder
#EXTRA_CFLAGS += -DMP3_DECODER_SUPPORT
EXTRA_CFLAGS += -DBASE_EFFECT_SUPPORT
EXTRA_CFLAGS += -DHI_SND_TIMER_CAST

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100 hi3798mv100 hi3796mv100),)
LSP_HIFI = RD4_HIFI3_3_LSP
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100),)
EXTRA_CFLAGS += -DADSP_SELLECT_DSP1
LSP_HIFI = RD5_HIFI3_3_LSP
endif

ifeq ($(CFG_HI_CHIP_TYPE),hi3751v100)
#EXTRA_CFLAGS += -DADSP_SELLECT_DSP0
#LSP_HIFI = RD5_HIFI3_4_LSP
EXTRA_CFLAGS += -DADSP_SELLECT_DSP1
LSP_HIFI = RD5_HIFI3_3_LSP
endif

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers

MOD_NAME := hi_adsp

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

$(MOD_NAME)-y   := drv_adsp_intf.o \
		   drv_adsp.o


ifneq ($(CFG_HI_SND_AOE_HW_SUPPORT),y)
#simulate support
$(MOD_NAME)-y += $(HIFIDIR)/common/linear/linear.o
$(MOD_NAME)-y += $(HIFIDIR)/common/mem/dsp_mem.o
ifeq ($(CFG_TQE_FOR_SND_AOE_HW_SUPPORT),y)
$(MOD_NAME)-y += $(HIFIDIR)/component/resampler/xa_resampler_error_handler.o
$(MOD_NAME)-y += $(HIFIDIR)/component/resampler/xa_resampler.o
endif
$(MOD_NAME)-y += $(HIFIDIR)/common/resampler/resample_rom.o
$(MOD_NAME)-y += $(HIFIDIR)/common/resampler/resample.o
$(MOD_NAME)-y += $(HIFIDIR)/common/util/dsp_util.o
$(MOD_NAME)-y += $(HIFIDIR)/common/ringbuf/dsp_ringbuf.o
$(MOD_NAME)-y += $(HIFIDIR)/common/basicop/basicop.o
$(MOD_NAME)-y += $(HIFIDIR)/common/timer/system_timer.o

$(MOD_NAME)-y += $(HIFIDIR)/sw_main.o
$(MOD_NAME)-y += $(HIFIDIR)/aoe/src/aop/aoe_aop.o
$(MOD_NAME)-y += $(HIFIDIR)/aoe/src/aop/aoe_cast.o
$(MOD_NAME)-y += $(HIFIDIR)/aoe/src/aip/aoe_aip.o
$(MOD_NAME)-y += $(HIFIDIR)/aoe/src/engine/aoe_engine.o
$(MOD_NAME)-y += $(HIFIDIR)/aoe/src/aoe_main.o
$(MOD_NAME)-y += $(HIFIDIR)/aoe/src/aoe_reg.o

$(MOD_NAME)-y += $(HIFIDIR)/aflt/src/aflt_main.o
$(MOD_NAME)-y += $(HIFIDIR)/aflt/src/aflt_func.o
$(MOD_NAME)-y += $(HIFIDIR)/component/codec/iapcm_dec/iapcm_dec.o
$(MOD_NAME)-y += $(HIFIDIR)/component/codec/iapcm_dec/iapcm_dec_comp.o

#only use debug for mp3 decoder
#$(MOD_NAME)-y+= $(HIFIDIR)/component/codec/iamp3_dec/comp_mp3dec_wrap.o       \
                $(HIFIDIR)/component/codec/iamp3_dec/mp3_decoder.o            \
                $(HIFIDIR)/component/codec/iamp3_dec/bits_op.o                \
                $(HIFIDIR)/component/codec/iamp3_dec/dct_core.o               \
                $(HIFIDIR)/component/codec/iamp3_dec/memory_op.o              \
                $(HIFIDIR)/component/codec/iamp3_dec/dequant.o                \
                $(HIFIDIR)/component/codec/iamp3_dec/huffman.o                \
                $(HIFIDIR)/component/codec/iamp3_dec/huffman_rom.o            \
                $(HIFIDIR)/component/codec/iamp3_dec/dec_layer12_sample.o     \
                $(HIFIDIR)/component/codec/iamp3_dec/imdct.o                  \
                $(HIFIDIR)/component/codec/iamp3_dec/mp3_rom.o                \
                $(HIFIDIR)/component/codec/iamp3_dec/data_decode.o            \
                $(HIFIDIR)/component/codec/iamp3_dec/stereo.o                 \
                $(HIFIDIR)/component/codec/iamp3_dec/synthesis.o              \
                $(HIFIDIR)/component/codec/iamp3_dec/trig_rom.o               \
                $(HIFIDIR)/component/codec/iamp3_dec/armgcc/asmpoly_gcc.o

$(MOD_NAME)-y+= $(HIFIDIR)/component/effect/base_effect/base_effect_comp.o \
                $(HIFIDIR)/component/effect/base_effect/base_effect_volume.o

else
$(MOD_NAME)-y += kfile_ops_func.o dsp_elf_func.o
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: all clean install uninstall

all:
ifeq ($(CFG_DSP_COMPILER_SUPPORT),y)
	xt-make -C ./hifi/build/ -f makefile_hifi3_dsp1 all	 -j
	./hifi/build/pcm2dat ./hifi/build/HIFI3_S5_DSP1SEL0 firmware/hififw.dat
endif
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf
ifeq ($(CFG_DSP_COMPILER_SUPPORT),y)
	xt-make -C ./hifi/build/ -f makefile_hifi3_dsp1 clean
endif

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/
endif

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

