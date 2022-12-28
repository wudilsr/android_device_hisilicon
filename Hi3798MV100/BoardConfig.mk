#
# Copyright 2014 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#


# SDK configure
HISI_SDK_ANDROID_CFG := hi3798mdmo_hi3798mv100_android_cfg.mak
HISI_SDK_RECOVERY_CFG := hi3798mdmo_hi3798mv100_android_recovery_cfg.mak
SDK_CFG_DIR := configs/hi3798mv100
SDK_CFGFILE := $(SDK_CFG_DIR)/$(HISI_SDK_ANDROID_CFG)

# Kernel configure
RAMDISK_ENABLE := true
ANDROID_KERNEL_CONFIG := hi3798mv100_android_defconfig
RECOVERY_KERNEL_CONFIG := hi3798mv100_android_recovery_defconfig

# emmc fastboot configure
EMMC_BOOT_CFG_NAME := hi3798mdmo1g_hi3798mv100_ddr3_1gbyte_16bitx2_4layers_emmc.cfg
EMMC_BOOT_REG_NAME := hi3798mdmo1g_hi3798mv100_ddr3_1gbyte_16bitx2_4layers_emmc.reg
EMMC_BOOT_ENV_STARTADDR :=0x100000
EMMC_BOOT_ENV_SIZE=0x10000
EMMC_BOOT_ENV_RANGE=0x10000

#
# ext4 file system configure
# the ext4 file system just use in the eMMC
#
TARGET_USERIMAGES_USE_EXT4 := true
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 838860800
BOARD_USERDATAIMAGE_PARTITION_SIZE := 1912602624
BOARD_CACHEIMAGE_PARTITION_SIZE := 524288000
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_PRIVATEIMAGE_PARTITION_SIZE := 52428800
BOARD_FLASH_BLOCK_SIZE := 4096

# Enable WiFi Only module used in the board.
BOARD_WLAN_DEVICE_RTL8188FTV := y

################################################################################
##  Stable configuration definitions
################################################################################

# The generic product target doesn't have any hardware-specific pieces.
TARGET_NO_BOOTLOADER := true
TARGET_NO_KERNEL := false
BOARD_KERNEL_BASE :=0x3000000
BOARD_KERNEL_PAGESIZE :=16384
TARGET_NO_RECOVERY := true
TARGET_NO_RADIOIMAGE := true
TARGET_ARCH := arm

TARGET_ARCH_VARIANT := armv7-a-neon
TARGET_CPU_VARIANT := cortex-a9
TARGET_CPU_ABI := armeabi-v7a
TARGET_CPU_ABI2 := armeabi
ARCH_ARM_HAVE_TLS_REGISTER := true

BOARD_USES_GENERIC_AUDIO := true

# no hardware camera
USE_CAMERA_STUB := true

# Build OpenGLES emulation guest and host libraries
#BUILD_EMULATOR_OPENGL := true

# Build and enable the OpenGL ES View renderer. When running on the emulator,
# the GLES renderer disables itself if host GL acceleration isn't available.
USE_OPENGL_RENDERER := true

# Buildin Hisilicon GPU gralloc and GPU libraries.
BUILDIN_HISI_GPU := true

# Buildin Hisilicon NDK extensions
BUILDIN_HISI_EXT := true

# Configure buildin Hisilicon smp
TARGET_CPU_SMP := true

# Disable use system/core/rootdir/init.rc
# HiSilicon use device/hisilicon/bigfish/etc/init.rc
TARGET_PROVIDES_INIT_RC := true

# Configure Board Platform name
TARGET_BOARD_PLATFORM := bigfish
TARGET_BOOTLOADER_BOARD_NAME := bigfish

# Define Hisilicon platform path.
HISI_PLATFORM_PATH := device/hisilicon/bigfish
# Define Hisilicon sdk path.
SDK_DIR := $(HISI_PLATFORM_PATH)/sdk
# Define sdk boot table configures directory
SDK_BOOTCFG_DIR := $(SDK_DIR)/source/boot/sysreg
# Configure Hisilicon Linux Kernel Version
HISI_LINUX_KERNEL := linux-3.10.y
# Define Hisilicon linux kernel source path.
HISI_KERNEL_SOURCE := $(SDK_DIR)/source/kernel/$(HISI_LINUX_KERNEL)

# wpa_supplicant and hostapd build configuration
# wpa_supplicant is used for WiFi STA, hostapd is used for WiFi SoftAP
WPA_SUPPLICANT_VERSION := VER_0_8_X
BOARD_WPA_SUPPLICANT_DRIVER := NL80211
BOARD_WPA_SUPPLICANT_PRIVATE_LIB := lib_driver_cmd_bcmdhd
BOARD_HOSTAPD_DRIVER := NL80211
BOARD_HOSTAPD_PRIVATE_LIB := lib_driver_cmd_bcmdhd
BOARD_WLAN_DEVICE := bcmdhd

# Set /system/bin/sh to mksh, not ash, to test the transition.
TARGET_SHELL := mksh
INTERGRATE_THIRDPARTY_APP := true
SUPPORT_IPV6 := true

# widevine Level setting
BOARD_WIDEVINE_OEMCRYPTO_LEVEL := 3
