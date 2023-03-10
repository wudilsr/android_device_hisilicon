#----------------------------------------------------------------------
# Compile Linux Kernel
#----------------------------------------------------------------------
include $(CLEAR_VARS)
KERNEL_OUT := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ
KERNEL_IMAGE := $(KERNEL_OUT)/kernel.img

MSP_BUILTIN_KERNEL := $(shell grep "CFG_HI_MSP_BUILDIN" $(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/sdk/$(SDK_CFGFILE) |cut -d =  -f2 | tr -d ' ')

ifeq ($(MSP_BUILTIN_KERNEL),y)
MSP_FLAG := CONFIG_MSP=y
else
MSP_FLAG := 
endif

HI_EXTRA_FLAGS :=
HI_EXTRA_CFLAGS :=
HI_EXTRA_AFLAGS :=

kernel_prepare:
	mkdir -p $(KERNEL_OUT)
	mkdir -p $(EMMC_PRODUCT_OUT)
	mkdir -p $(TARGET_OUT_SHARED_LIBRARIES)/modules
	$(MAKE) -C $(HISI_KERNEL_SOURCE) $(HI_EXTRA_FLAGS) CFLAGS_KERNEL=$(HI_EXTRA_CFLAGS) AFLAGS_KERNEL=$(HI_EXTRA_AFLAGS) distclean
	echo "build kernel config: KERNEL_CONFIG=$(ANDROID_KERNEL_CONFIG)"
	cd $(SDK_DIR);$(MAKE) linux_prepare SDK_CFGFILE=$(SDK_CFGFILE); cd -;

kernel_config: kernel_prepare
	if [ -f $(KERNEL_OUT)/.config ]; then \
	echo "Attention:$(KERNEL_OUT)/.config exist"; \
	echo "make kernel_config: Nothing to be done!"; \
	else \
	$(MAKE) -C $(HISI_KERNEL_SOURCE) \
	SDK_CFGFILE=$(SDK_CFGFILE) \
	O=$(ANDROID_BUILD_TOP)/$(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ \
	ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- \
	$(ANDROID_KERNEL_CONFIG) $(HI_EXTRA_FLAGS) CFLAGS_KERNEL=$(HI_EXTRA_CFLAGS) AFLAGS_KERNEL=$(HI_EXTRA_AFLAGS); \
	fi

kernel_menuconfig: kernel_config
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(KERNEL_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- menuconfig

$(KERNEL_IMAGE): kernel_config $(INSTALLED_RAMDISK_TARGET) | $(ACP)
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(KERNEL_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- $(MSP_FLAG) \
		$(HI_EXTRA_FLAGS) CFLAGS_KERNEL=$(HI_EXTRA_CFLAGS) AFLAGS_KERNEL=$(HI_EXTRA_AFLAGS) \
		-j 4 uImage modules
	$(hide) echo HI_EXTRA_FLAGS=$(HI_EXTRA_FLAGS) CFLAGS_KERNEL=$(HI_EXTRA_CFLAGS) AFLAGS_KERNEL=$(HI_EXTRA_AFLAGS)
	cp -avf $(KERNEL_OUT)/arch/arm/boot/uImage $(PRODUCT_OUT)/kernel
	$(hide) echo "####################### copy modules $(TARGET_PRODUCT)"
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ohci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ehci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/xhci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/

.PHONY: kernel $(KERNEL_IMAGE) $(INSTALLED_BOOTIMAGE_TARGET)
$(INSTALLED_KERNEL_TARGET): $(KERNEL_IMAGE)
kernel: $(INSTALLED_BOOTIMAGE_TARGET)
	cp -avf $(INSTALLED_BOOTIMAGE_TARGET) $(EMMC_PRODUCT_OUT)/kernel.img


#----------------------------------------------------------------------
# Linux Kernel End
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Update Wifi Drivers
#----------------------------------------------------------------------
WIFI_CFG := \
	CFG_HI_WIFI_DEVICE_RTL8188FU=$(BOARD_WLAN_DEVICE_RTL8188FTV) \
	CFG_HI_WIFI_MODE_STA=y CFG_HI_WIFI_MODE_AP=y

wifi: $(KERNEL_IMAGE)
	$(MAKE) -j1 -C $(SDK_DIR)/source/component/wifi/drv \
		ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- \
		ROOTFS_DIR=$(ANDROID_BUILD_TOP)/$(PRODUCT_OUT) \
		LINUX_DIR=$(ANDROID_BUILD_TOP)/$(KERNEL_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) $(WIFI_CFG) ANDROID_BUILD=y install
	$(MAKE) -C $(SDK_DIR)/source/component/wifi/drv \
		SDK_CFGFILE=$(SDK_CFGFILE) $(WIFI_CFG) clean
ALL_DEFAULT_INSTALLED_MODULES += wifi
.PHONY: wifi
wifi: kernel
#----------------------------------------------------------------------
# Update Wifi Drivers END
#----------------------------------------------------------------------
