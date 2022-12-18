#
# Automatically generated make config: don't edit
# SDK version: KERNELVERSION
# Fri Mar 20 14:23:41 2015
#

#
# Base
#
# CFG_LINUX_PRODUCT is not set
CFG_ANDROID_PRODUCT=y
CFG_PRODUCT_TYPE=android
# CFG_HI3716CV200 is not set
# CFG_HI3716MV400 is not set
# CFG_HI3718CV100 is not set
# CFG_HI3718MV100 is not set
# CFG_HI3719CV100 is not set
# CFG_HI3719MV100 is not set
# CFG_HI3796CV100 is not set
# CFG_HI3798CV100 is not set
CFG_HI3798MV100=y
# CFG_HI3796MV100 is not set
# CFG_HI3798CV200_A is not set
CFG_HI_CHIP_TYPE=hi3798mv100
CFG_ARM_HISIV200_LINUX=y
# CFG_ARM_HISTBV300_LINUX is not set
CFG_HI_TOOLCHAINS_NAME=arm-hisiv200-linux
# CFG_HI_LOADER_SUPPORT is not set
# CFG_HI_OPTM_SIZE_SUPPORT is not set

#
# Board
#

#
# Ethernet Config
#
CFG_HI_ETH_SUPPORT=y

#
# Flash Config
#
CFG_HI_NAND_SUPPORT=y
CFG_HI_NAND_BLOCK_SIZE=0x200000
CFG_HI_NAND_PAGE_SIZE=8k
CFG_HI_NAND_ECC_TYPE=48bit
CFG_HI_EMMC_SUPPORT=y

#
# Demux Config
#

#
# IF Config
#
CFG_HI_IF_TYPE=parallel_nosync_188
CFG_HI_IF_BIT_SELECTOR=0

#
# TSI Config
#
CFG_HI_TSI_NUMBER=4

#
# TSI0 Config
#
CFG_HI_TSI0_TYPE=parallel_nosync_188
CFG_HI_TSI0_CLK_PHASE_REVERSE=1
CFG_HI_TSI0_BIT_SELECTOR=0

#
# TSI1 Config
#
CFG_HI_TSI1_TYPE=parallel_nosync_188
CFG_HI_TSI1_CLK_PHASE_REVERSE=1
CFG_HI_TSI1_BIT_SELECTOR=0

#
# TSI2 Config
#
CFG_HI_TSI2_TYPE=parallel_nosync_188
CFG_HI_TSI2_CLK_PHASE_REVERSE=1
CFG_HI_TSI2_BIT_SELECTOR=0

#
# TSI3 Config
#
CFG_HI_TSI3_TYPE=parallel_nosync_188
CFG_HI_TSI3_CLK_PHASE_REVERSE=1
CFG_HI_TSI3_BIT_SELECTOR=0

#
# TSI4 Config
#
CFG_HI_TSI4_TYPE=parallel_nosync_188
CFG_HI_TSI4_CLK_PHASE_REVERSE=1
CFG_HI_TSI4_BIT_SELECTOR=0

#
# TSI5 Config
#
CFG_HI_TSI5_TYPE=parallel_nosync_188
CFG_HI_TSI5_CLK_PHASE_REVERSE=1
CFG_HI_TSI5_BIT_SELECTOR=0

#
# TSO Config
#
CFG_HI_TSO_NUMBER=2

#
# TSO0 Config
#
CFG_HI_TSO0_CLK_100M=y
# CFG_HI_TSO0_CLK_150M is not set
# CFG_HI_TSO0_CLK_1200M is not set
# CFG_HI_TSO0_CLK_1500M is not set
CFG_HI_TSO0_CLK_MODE_NORMAL=y
# CFG_HI_TSO0_CLK_MODE_JITTER is not set
CFG_HI_TSO0_VALID_ACTIVE_OUTPUT=y
# CFG_HI_TSO0_VALID_ACTIVE_HIGH is not set
CFG_HI_TSO0_SERIAL=y
# CFG_HI_TSO0_PARALLEL is not set
CFG_HI_TSO0_SERIAL_BIT_0=y
# CFG_HI_TSO0_SERIAL_BIT_7 is not set

#
# TSO1 Config
#
CFG_HI_TSO1_CLK_100M=y
# CFG_HI_TSO1_CLK_150M is not set
# CFG_HI_TSO1_CLK_1200M is not set
# CFG_HI_TSO1_CLK_1500M is not set
CFG_HI_TSO1_CLK_MODE_NORMAL=y
# CFG_HI_TSO1_CLK_MODE_JITTER is not set
CFG_HI_TSO1_VALID_ACTIVE_OUTPUT=y
# CFG_HI_TSO1_VALID_ACTIVE_HIGH is not set
CFG_HI_TSO1_SERIAL=y
# CFG_HI_TSO1_PARALLEL is not set
CFG_HI_TSO1_SERIAL_BIT_0=y
# CFG_HI_TSO1_SERIAL_BIT_7 is not set

#
# Keyled Config
#
# CFG_HI_KEYLED_74HC164_SELECT is not set
CFG_HI_KEYLED_CT1642_SELECT=y
# CFG_HI_KEYLED_PT6961_SELECT is not set
# CFG_HI_KEYLED_PT6964_SELECT is not set
# CFG_HI_KEYLED_FD650_SELECT is not set
# CFG_HI_GPIO_LIGHT_SUPPORT is not set

#
# PowerManagement Config
#
# CFG_HI_PMU_DEVICE_SELECT is not set
CFG_HI_SND_MUTECTL_SUPPORT=y
CFG_HI_SND_MUTECTL_GPIO=0x23
CFG_HI_SND_MUTECTL_LEVEL=0
# CFG_HI_SND_AMP_SUPPORT is not set

#
# Video DAC Config
#
CFG_HI_DAC_CVBS=0
CFG_HI_DAC_YPBPR_Y=1
CFG_HI_DAC_YPBPR_PB=2
CFG_HI_DAC_YPBPR_PR=3

#
# Boot Regfile Config
#
CFG_HI_BOOT_REG_NAME=hi3798mdmo1d_hi3798mv100_ddr3_2gbyte_8bitx4_4layers_emmc.reg

#
# Boot
#
CFG_HI_UBOOT_SUPPORT=y
# CFG_HI_MINIBOOT_SUPPORT is not set
# CFG_HI_FORCE_ENV_TO_MEDIA is not set
CFG_HI_BOOT_ENV_STARTADDR=0x100000
CFG_HI_BOOT_ENV_SIZE=0x10000
CFG_HI_BOOT_ENV_RANGE=0x10000
# CFG_HI_BOOT_ENV_BAK_SUPPORT is not set
# CFG_HI_BOOT_COMPRESSED is not set
# CFG_HI_BENCH_SUPPORT is not set
CFG_HI_BOOT_USB_SUPPORT=y

#
# Build Product Code in Boot
#
CFG_HI_BUILD_WITH_PRODUCT=y
CFG_HI_BUILD_WITH_ANDROID=y
CFG_HI_BUILD_WITH_KEYLED=y
# CFG_HI_BUILD_WITH_IR is not set
# CFG_HI_BUILD_WITH_HDMI_EDID is not set

#
# Kernel
#
CFG_LINUX-3.10.y=y
CFG_HI_KERNEL_VERSION=linux-3.10.y
CFG_HI_KERNEL_CFG=hi3798mv100_android_defconfig
# CFG_HI_FS_BUILDIN is not set
CFG_HI_MSP_BUILDIN=y

#
# Rootfs
#

#
# Board Tools Config
#
CFG_HI_TOOL_UDEV_SUPPORT=y
CFG_HI_TOOL_DOSFS_SUPPORT=y
# CFG_HI_TOOL_E2FSPROGS_SUPPORT is not set
CFG_HI_TOOL_FILECAP_SUPPORT=y
# CFG_HI_TOOL_GDB_SUPPORT is not set
# CFG_HI_TOOL_IPTABLES_SUPPORT is not set
# CFG_HI_TOOL_MTDUTILS_SUPPORT is not set
CFG_HI_TOOL_REG_SUPPORT=y
# CFG_HI_TOOL_REG_UART_SUPPORT is not set
# CFG_HI_TOOL_TOP_SUPPORT is not set
CFG_HI_TOOL_PPPD_SUPPORT=y
# CFG_HI_TOOL_MIITOOLS_SUPPORT is not set
# CFG_HI_TOOL_IPERF_SUPPORT is not set
CFG_HI_TOOL_MSP_DEBUG_SUPPORT=y
CFG_HI_TOOL_PQ_DEBUG_SUPPORT=y
# CFG_HI_TOOL_SOC_SERVER is not set
# CFG_HI_LXC_CONTAINER_SUPPORT is not set
# CFG_HI_TOOL_SYSSTAT_SUPPORT is not set
# CFG_HI_TOOL_MEMTESTER_SUPPORT is not set

#
# Busybox Config
#
CFG_BUSYBOX_1.16.1=y
# CFG_BUSYBOX_1.22.1 is not set
CFG_HI_BUSYBOX_CFG_NAME=glibc.config
CFG_HI_LIBCPP_SUPPORT=y

#
# File System Config
#
CFG_HI_ROOTFS_STRIP=y
CFG_HI_ROOTFS_INSTALL_SHARED_LIBS=y
CFG_HI_ROOTFS_CRAMFS=y
CFG_HI_ROOTFS_YAFFS=y
CFG_HI_ROOTFS_SQUASHFS=y
# CFG_HI_ROOTFS_EXT4 is not set
CFG_HI_ROOTFS_UBIIMG=y
CFG_HI_UBI_PARTITION_SIZE=96M

#
# Common
#
CFG_HI_LOG_SUPPORT=y
CFG_HI_LOG_LEVEL=4
CFG_HI_LOG_NETWORK_SUPPORT=y
CFG_HI_LOG_UDISK_SUPPORT=y
# CFG_HI_MMZ_V2_SUPPORT is not set
# CFG_HI_MEMMGR_SUPPORT is not set
CFG_HI_PROC_SUPPORT=y

#
# Component
#
# CFG_HI_ADVCA_SUPPORT is not set
CFG_HI_ZLIB_SUPPORT=y
# CFG_HI_FAT_SUPPORT is not set
CFG_HI_NTFS_SUPPORT=y
CFG_HI_NTFS_MODULE_SUPPORT=y
# CFG_HI_NTFS_TOOLS_SUPPORT is not set
CFG_HI_EXFAT_SUPPORT=y
CFG_HI_3G_SUPPORT=y
# CFG_HI_ALSA_SUPPORT is not set
# CFG_HI_BLUETOOTH_SUPPORT is not set
CFG_HI_KARAOKE_SUPPORT=y

#
# HACODEC Config
#
CFG_HI_HACODEC_MP3DECODE_SUPPORT=y
CFG_HI_HACODEC_AACDECODE_SUPPORT=y
CFG_HI_HACODEC_AACENCODE_SUPPORT=y
CFG_HI_HACODEC_AC3PASSTHROUGH_SUPPORT=y
CFG_HI_HACODEC_AMRNBCODEC_SUPPORT=y
CFG_HI_HACODEC_AMRWBCODEC_SUPPORT=y
CFG_HI_HACODEC_BLURAYLPCMDECODE_SUPPORT=y
CFG_HI_HACODEC_COOKDECODE_SUPPORT=y
CFG_HI_HACODEC_DRADECODE_SUPPORT=y
CFG_HI_HACODEC_DTSPASSTHROUGH_SUPPORT=y
CFG_HI_HACODEC_G711CODEC_SUPPORT=y
CFG_HI_HACODEC_G722CODEC_SUPPORT=y
CFG_HI_HACODEC_MP2DECODE_SUPPORT=y
CFG_HI_HACODEC_PCMDECODE_SUPPORT=y
CFG_HI_HACODEC_TRUEHDPASSTHROUGH_SUPPORT=y
CFG_HI_HACODEC_WMADECODE_SUPPORT=y
CFG_HI_HACODEC_PCMDECODE_HW_SUPPORT=y
CFG_HI_HACODEC_MP3DECODE_HW_SUPPORT=y
CFG_HI_HACODEC_DTSM6DECODE_SUPPORT=y

#
# HAEFFECT Config
#
# CFG_HI_HAEFFECT_BASE_SUPPORT is not set
CFG_HI_VP_SUPPORT=y
CFG_HI_PES_SUPPORT=y

#
# Caption Config
#
CFG_HI_CAPTION_SUBT_SUPPORT=y
CFG_HI_CAPTION_TTX_SUPPORT=y
CFG_HI_CAPTION_SO_SUPPORT=y
CFG_HI_CAPTION_CC_SUPPORT=y
# CFG_HI_CURL_SUPPORT is not set

#
# Msp
#

#
# DEMUX Config
#
CFG_HI_DEMUX_POOLBUF_SIZE=0x80000

#
# Audio Config
#
CFG_HI_SND_ALSA_AO_SUPPORT=y
CFG_HI_AI_SUPPORT=y
CFG_HI_SND_ALSA_AI_SUPPORT=y
# CFG_HI_SND_ALSA_I2S_ONLY_SUPPORT is not set
# CFG_HI_SND_ALSA_HDMI_ONLY_SUPPORT is not set
CFG_HI_ADEC_MAX_INSTANCE=8
# CFG_HI_ADEC_AUDSPECTRUM_SUPPORT is not set
# CFG_HI_SND_SMARTVOLUME_SUPPORT is not set
# CFG_HI_SND_VIRTUALCHN_SUPPORT is not set
# CFG_HI_RESAMPLER_QUALITY_LINEAR is not set
CFG_HI_AENC_SUPPORT=y
# CFG_HI_SND_SIF_SUPPORT is not set
# CFG_HI_ADAC_SUPPORT is not set
# CFG_HI_ALSA_TVL320_KERNEL_SUPPORT is not set

#
# Video Decoder Config
#

#
# Video Memory Config In 512M DDR
#
# CFG_HI_VIDEO_PRE_CAP_1080P_IN_512 is not set
CFG_HI_VIDEO_PRE_CAP_MVC_IN_512=y
# CFG_HI_VIDEO_PRE_CAP_2160P_IN_512 is not set
# CFG_HI_VIDEO_PRE_CAP_4K_IN_512 is not set
CFG_HI_VIDEO_MAX_REF_FRAME_NUM_IN_512=7
CFG_HI_VIDEO_MAX_DISP_FRAME_NUM_IN_512=2
CFG_HI_VIDEO_SCD_BUF_SIZE_IN_512=10
CFG_HI_VIDEO_MAX_VDH_BUF_IN_512=110

#
# Video Memory Config In 1024M DDR
#
# CFG_HI_VIDEO_PRE_CAP_1080P_IN_1024 is not set
# CFG_HI_VIDEO_PRE_CAP_MVC_IN_1024 is not set
# CFG_HI_VIDEO_PRE_CAP_2160P_IN_1024 is not set
CFG_HI_VIDEO_PRE_CAP_4K_IN_1024=y
CFG_HI_VIDEO_MAX_REF_FRAME_NUM_IN_1024=5
CFG_HI_VIDEO_MAX_DISP_FRAME_NUM_IN_1024=4
CFG_HI_VIDEO_SCD_BUF_SIZE_IN_1024=20
CFG_HI_VIDEO_MAX_VDH_BUF_IN_1024=180

#
# Video Memory Config In 2048M DDR
#
# CFG_HI_VIDEO_PRE_CAP_1080P_IN_2048 is not set
# CFG_HI_VIDEO_PRE_CAP_MVC_IN_2048 is not set
# CFG_HI_VIDEO_PRE_CAP_2160P_IN_2048 is not set
CFG_HI_VIDEO_PRE_CAP_4K_IN_2048=y
CFG_HI_VIDEO_MAX_REF_FRAME_NUM_IN_2048=6
CFG_HI_VIDEO_MAX_DISP_FRAME_NUM_IN_2048=6
CFG_HI_VIDEO_SCD_BUF_SIZE_IN_2048=30
CFG_HI_VIDEO_MAX_VDH_BUF_IN_2048=250
CFG_HI_VDEC_DEINTERLACE_SUPPORT=y
CFG_HI_VDEC_SVDEC_SUPPORT=y
CFG_HI_VDEC_REG_CODEC_SUPPORT=y
CFG_HI_VDEC_MJPEG_SUPPORT=y
CFG_HI_VDEC_USERDATA_CC_SUPPORT=y
CFG_HI_VDEC_USERDATA_CC_BUFSIZE=0xC000
CFG_HI_VDEC_DFS_SUPPORT=y

#
# VO Config
#
CFG_HI_VIDEO_BUFF_DEMO=y
# CFG_HI_VIDEO_BUFF_TYPE0 is not set
# CFG_HI_DISP_USE_QPLL_SOLELY is not set
CFG_HI_DISP_TTX_INBUFFERSIZE=0x4000
CFG_HI_DISP_CC_INBUFFERSIZE=0x4000
CFG_HI_PQ_V3_0=y
# CFG_HI_DISP_VIRT_OFFSET_EFFECT_WHEN_FULLSCREEN is not set

#
# VPSS Config
#
CFG_HI_VPSS_MAX_BUFFER_NUMB=6

#
# HDMI Config
#
CFG_HI_HDMI_SUPPORT_1_4=y
CFG_HI_HDMI_SUPPORT_HDCP=y
CFG_HI_HDMI_SUPPORT_CEC=y
# CFG_HI_HDMI_SUPPORT_DEBUG is not set
CFG_HI_HDMI_DEBUG_MEM_SIZE=0x80000

#
# Graphic Config
#
CFG_LIB_JPEG_VERSION_6B=y
# CFG_LIB_JPEG_VERSION_9A is not set
CFG_HI_LIB_JPEG_VERSION=libjpeg-6b
CFG_LIB_PNG_VERSION_1.4.0=y
# CFG_LIB_PNG_VERSION_1.6.16 is not set
CFG_HI_LIB_PNG_VERSION=libpng-1.4.0
CFG_HIFB_STEREO3D_SUPPORT=y
# CFG_HIFB_COMPRESSION_SUPPORT is not set
# CFG_HIFB_SCROLLTEXT_SUPPORT is not set
# CFG_HIFB_CURSOR_SUPPORT is not set
CFG_HI_PNG_DECODER_SUPPORT=y
CFG_HI_FREETYPE_FONT_SUPPORT=y
CFG_HI_TDE_CSCTMPBUFFER_SIZE=0x0
CFG_HI_JPEG6B_STREAMBUFFER_SIZE=0x100000
CFG_HI_HD0_FB_VRAM_SIZE=7200
CFG_HI_HD1_FB_VRAM_SIZE=0
CFG_HI_HD2_FB_VRAM_SIZE=0
CFG_HI_SD0_FB_VRAM_SIZE=0

#
# GPU Config
#
CFG_HI_GPU=y
CFG_HI_GPU_MALI450_SUPPORT=y
# CFG_HI_GPU_DEBUG is not set
CFG_HI_GPU_PROFILING=y
# CFG_HI_GPU_INTERNAL_PROFILING is not set
CFG_HI_GPU_MAX_SHARE_MEM_SIZE=0x20000000
# CFG_EGL_HIGO is not set
CFG_EGL_FB=y
# CFG_EGL_DFB is not set
CFG_HI_EGL_TYPE=fb

#
# IR Config
#
# CFG_HI_IR_TYPE_S2 is not set
CFG_HI_IR_TYPE_STD=y
# CFG_HI_IR_TYPE_LIRC is not set

#
# Keyled Config
#
CFG_HI_KEYLED_SUPPORT=y
CFG_HI_KEYLED_74HC164_SUPPORT=y
CFG_HI_KEYLED_CT1642_SUPPORT=y
# CFG_HI_KEYLED_CT1642_GPIO_MODE is not set
CFG_HI_KEYLED_PT6961_SUPPORT=y
CFG_HI_KEYLED_PT6961_CLOCK_GPIO=0x2a
CFG_HI_KEYLED_PT6961_STB_GPIO=0x2b
CFG_HI_KEYLED_PT6961_DIN_GPIO=0x2c
CFG_HI_KEYLED_PT6961_DOUT_GPIO=0x2d
CFG_HI_KEYLED_PT6964_SUPPORT=y
CFG_HI_KEYLED_PT6964_CLOCK_GPIO=0x2a
CFG_HI_KEYLED_PT6964_STB_GPIO=0x2b
CFG_HI_KEYLED_PT6964_DINOUT_GPIO=0x2c
CFG_HI_KEYLED_FD650_SUPPORT=y
CFG_HI_KEYLED_FD650_CLOCK_GPIO=0x2b
CFG_HI_KEYLED_FD650_DINOUT_GPIO=0x2d

#
# PowerManagement Config
#
CFG_HI_DVFS_CPU_SUPPORT=y
CFG_HI_DVFS_CORE_SUPPORT=y
CFG_HI_DVFS_GPU_SUPPORT=y
CFG_HI_AVS_SUPPORT=y
# CFG_HI_DONGLE_CONFIG is not set
# CFG_HI_PM_POWERUP_MODE1_SUPPORT is not set
CFG_HI_TEMP_CTRL_CONFIG=y
CFG_HI_TEMP_CTRL_DOWN_THRESHOLD=0xd5
CFG_HI_TEMP_CTRL_UP_THRESHOLD=0xc8
CFG_HI_TEMP_CTRL_REBOOT_THRESHOLD=0xea
CFG_HI_MCE_SUPPORT=y

#
# SCI Config
#
CFG_HI_GPIOI2C_SUPPORT=y
CFG_HI_VI_SUPPORT=y
# CFG_HI_VI_BT656_HIGH8 is not set
CFG_HI_VENC_SUPPORT=y

#
# Pvr Config
#
CFG_HI_PVR_SUPPORT=y
# CFG_HI_PVR_L2_CACHE_SUPPORT is not set
# CFG_HI_SPI_BUS_SUPPORT is not set

#
# CI/CI+ Config
#
# CFG_HI_CIPLUS_SUPPORT is not set
