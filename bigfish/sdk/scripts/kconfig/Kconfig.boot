#+++++++++++++++++++++++++++++++++++++++++++++++++++
choice
	prompt "Boot Type"
	default HI_UBOOT_SUPPORT

config  HI_UBOOT_SUPPORT
	bool "uboot"
	depends on (ANDROID_PRODUCT || !HI_ADVCA_SUPPORT)
config  HI_MINIBOOT_SUPPORT
	bool "miniboot"
endchoice

menuconfig HI_FORCE_ENV_TO_MEDIA
	bool "Force Envionment variables to Nand/SPI Flash/eMMC"
	default n
	depends on HI_UBOOT_SUPPORT
	help
	  This option enables forcing envionment variables to Nand/SPI Flash/eMMC.
	  if not enabled, the envionment variables are saved to the boot media, that is to say,
	  if the boot is burnt to SPI Flash, the envionment variables are saved to SPI Flash.
	  The media for choosing:
		Nand
		SPI Flash
		eMMC

source "scripts/kconfig/Kconfig.env.media"

config HI_BOOT_ENV_STARTADDR
	hex "Envioronment Variables Partition Start Address"
	default 0x80000
	help
	  The start address of the partition you want to save your envioronment variables.

config HI_BOOT_ENV_SIZE
	hex "Envioronment Variables Partition Size"
	default 0x2000
	help
	  The size of the partition you want to save your envioronment variables.

config HI_BOOT_ENV_RANGE
	hex "Envioronment Variables Partition Read/Write Range"
	default HI_BOOT_ENV_SIZE
	help
	  When read/write environment variables,if there are bad blocks,
	  this indicates the size driver should skip.Default value set to
	  be the size of envioronment variables partition size, usually one
	  block.Only useful for nand.

config HI_BOOT_ENV_BAK_SUPPORT
	bool "Bakup Envioronment support"
	default y
	help
	  The bakup Envioronment support. When read and check Envioronment failed,
	  we should try bakup Envioronment.

config HI_BOOT_ENV_STARTADDR_BAKUP
	hex "Bakup envioronment Variables Partition Start Address"
	depends on HI_BOOT_ENV_BAK_SUPPORT
	default HI_BOOT_ENV_STARTADDR
	help
	  The start address of the partition you want to save your BAKUP envioronment variables.

config HI_BOOT_COMPRESSED
	bool "Build Compressed Boot Image"
	default n
	help
	  Say y here if you want to build compressed boot image. The compressed
	  boot image is smaller.

config HI_BENCH_SUPPORT
	bool "Support HiBench"
	default n
	depends on HI_UBOOT_SUPPORT
	help
	  HiBench is a tool which can test your cpu. You can run HiBench with "run" command in boot command line.
	  Say y here if you want to run HiBench.

config HI_BOOT_USB_SUPPORT
	bool "Support Usb Drivers"
	default n if (HI3716CV200 || HI3716MV400 || HI3718CV100 || HI3719CV100 || HI3718MV100 || HI3719MV100 || HI3798CV100 || HI3796CV100)
	default y if (HI3798MV100 || HI3796MV100 || HI3798CV200_A)
	depends on HI_UBOOT_SUPPORT
	help
	  Say y here if you want to support usb for boot.

menu "Build Product Code in Boot"
config HI_BUILD_WITH_PRODUCT
	bool "Build Product Code in Boot"
	default n
	help
	  This option enables you to build product directory in boot. Final
	  fastboot-burn.bin/miniboot.bin contains product. If you set to n here, product
	  will not build with Boot, there will generate another bin file,
	  which can be run up by "bootapp (addr)" cmd.

source "scripts/kconfig/Kconfig.bootloader"

menuconfig HI_BUILD_WITH_FRONTEND
	bool "Build Frontend Code in Boot"
	depends on HI_BUILD_WITH_PRODUCT && HI_BOOTLOADER_SUPPORT
	default n

config HI_BOOT_DISEQC_SUPPORT
	depends on HI_BUILD_WITH_FRONTEND
	bool "DISEQC Support"
	default n

menu "Tuner Used in Boot"
	depends on HI_BUILD_WITH_FRONTEND

config  HI_BOOT_TUNER_TYPE_ALPS_TDAE
	depends on HI_BUILD_WITH_FRONTEND
	bool "ALPS_TDAE Support"
	default y

config  HI_BOOT_TUNER_TYPE_TDCC
	depends on HI_BUILD_WITH_FRONTEND
	bool "TDCC Support"
	default y

config  HI_BOOT_TUNER_TYPE_TDA18250
	depends on HI_BUILD_WITH_FRONTEND
	bool "TDA18250 Support"
	default y
	
config  HI_BOOT_TUNER_TYPE_TDA18250B
	depends on HI_BUILD_WITH_FRONTEND
	bool "TDA18250B Support"
	default y
	
config  HI_BOOT_TUNER_TYPE_SI2147
	depends on HI_BUILD_WITH_FRONTEND
	bool "SI2147 Support"
	default y	

config  HI_BOOT_TUNER_TYPE_TMX7070X
	depends on HI_BUILD_WITH_FRONTEND
	bool "TMX7070X Support"
	default y

config  HI_BOOT_TUNER_TYPE_R820C
	depends on HI_BUILD_WITH_FRONTEND
	bool "R820C Support"
	default y

config  HI_BOOT_TUNER_TYPE_MXL203
	depends on HI_BUILD_WITH_FRONTEND
	bool "MXL203 Support"
	default y

config  HI_BOOT_TUNER_TYPE_AV2011
	depends on HI_BUILD_WITH_FRONTEND
	bool "AV2011 Support"
	default y

config  HI_BOOT_TUNER_TYPE_SHARP7903
	depends on HI_BUILD_WITH_FRONTEND
	bool "SHARP7903 Support"
	default y

config  HI_BOOT_TUNER_TYPE_MXL603
	depends on HI_BUILD_WITH_FRONTEND
	bool "MXL603 Support"
	default y

endmenu

menu "Demod Used in Boot"
	depends on HI_BUILD_WITH_FRONTEND

config  HI_BOOT_DEMOD_TYPE_HI3130I
	depends on HI_BUILD_WITH_FRONTEND
	bool "HI3130_INSIDE Support"
	default y

config  HI_BOOT_DEMOD_TYPE_HI3136
	depends on HI_BUILD_WITH_FRONTEND
	bool "HI3136 Support"
	default y

endmenu

menu "LNB Chip Used in Boot"
	depends on HI_BUILD_WITH_FRONTEND

config  HI_BOOT_LNB_CTRL_ISL9492
	depends on HI_BUILD_WITH_FRONTEND
	bool "ISL9492 Support"
	default n

config  HI_BOOT_LNB_CTRL_MPS8125
	depends on HI_BUILD_WITH_FRONTEND
	bool "MPS8125 Support"
	default n
endmenu

config  HI_BUILD_WITH_DEMUX
	bool "Build DEMUX in Boot"
	depends on HI_BUILD_WITH_PRODUCT && HI_BOOTLOADER_SUPPORT
	default n

config  HI_BUILD_WITH_ANDROID
	bool "Build ANDROID Partion in Boot"
	depends on HI_BUILD_WITH_PRODUCT
	default n

config HI_BUILD_WITH_KEYLED
	bool "Build Keyled in Boot"
	depends on HI_BUILD_WITH_PRODUCT && (HI_KEYLED_74HC164_SUPPORT || HI_KEYLED_CT1642_SUPPORT || HI_KEYLED_PT6961_SUPPORT || HI_KEYLED_PT6964_SUPPORT || HI_KEYLED_FD650_SUPPORT) || HI_KEYLED_GPIOKEY_SUPPORT
	default y

config HI_BUILD_WITH_IR
	bool "Build IR in Boot"
	depends on HI_BUILD_WITH_PRODUCT
	default n

config HI_BUILD_WITH_HDMI_EDID
	bool "Build EDID in Boot"
	depends on HI_BUILD_WITH_PRODUCT && (HI3716CV200 || HI3716MV400 || HI3718CV100 || HI3719CV100 || HI3718MV100 || HI3719MV100)
	default n

endmenu

