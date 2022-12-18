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

ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
SECURITY_FLAGS := CONFIG_SUPPORT_CA=y CONFIG_CA_WARKUP_CHECK=y
SECURITY_CFLAGS := "-DCONFIG_SUPPORT_CA -DCONFIG_CA_WARKUP_CHECK"
SECURITY_AFLAGS := "-DCONFIG_SUPPORT_CA -DCONFIG_CA_WARKUP_CHECK"
else
SECURITY_FLAGS :=
SECURITY_CFLAGS :=
SECURITY_AFLAGS :=
endif

kernel_prepare:
	mkdir -p $(KERNEL_OUT)
	mkdir -p $(EMMC_PRODUCT_OUT)
	mkdir -p $(NAND_PRODUCT_OUT)
	mkdir -p $(TARGET_OUT_SHARED_LIBRARIES)/modules
	$(MAKE) -C $(HISI_KERNEL_SOURCE) $(SECURITY_FLAGS) CFLAGS_KERNEL=$(SECURITY_CFLAGS) AFLAGS_KERNEL=$(SECURITY_AFLAGS) distclean
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
	$(ANDROID_KERNEL_CONFIG) $(SECURITY_FLAGS) CFLAGS_KERNEL=$(SECURITY_CFLAGS) AFLAGS_KERNEL=$(SECURITY_AFLAGS); \
	fi

kernel_menuconfig: kernel_config
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(KERNEL_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- menuconfig

ifeq ($(RAMDISK_ENABLE),false)
$(KERNEL_IMAGE): kernel_config $(INSTALLED_RAMDISK_TARGET) | $(ACP)
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(KERNEL_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- $(MSP_FLAG) \
		CONFIG_INITRAMFS_SOURCE=$(ANDROID_BUILD_TOP)/$(TARGET_ROOT_OUT) \
		$(SECURITY_FLAGS) CFLAGS_KERNEL=$(SECURITY_CFLAGS) AFLAGS_KERNEL=$(SECURITY_AFLAGS) \
		-j 4 uImage modules
	$(hide) cp -avf $(KERNEL_OUT)/arch/arm/boot/uImage $@
	$(hide) chmod a+r $@
	$(hide) echo SECURITY_FLAGS=$(SECURITY_FLAGS) CFLAGS_KERNEL=$(SECURITY_CFLAGS) AFLAGS_KERNEL=$(SECURITY_AFLAGS)
	cp -avf $@ $(NAND_PRODUCT_OUT)
	cp -avf $@ $(EMMC_PRODUCT_OUT)
else
$(KERNEL_IMAGE): kernel_config $(INSTALLED_RAMDISK_TARGET) | $(ACP)
	$(MAKE) -C $(HISI_KERNEL_SOURCE) O=$(ANDROID_BUILD_TOP)/$(KERNEL_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- $(MSP_FLAG) \
		$(SECURITY_FLAGS) CFLAGS_KERNEL=$(SECURITY_CFLAGS) AFLAGS_KERNEL=$(SECURITY_AFLAGS) \
		-j 4 uImage modules
	$(hide) echo SECURITY_FLAGS=$(SECURITY_FLAGS) CFLAGS_KERNEL=$(SECURITY_CFLAGS) AFLAGS_KERNEL=$(SECURITY_AFLAGS)
	cp -avf $(KERNEL_OUT)/arch/arm/boot/uImage $(PRODUCT_OUT)/kernel
endif

ifneq ($(findstring $(TARGET_PRODUCT), Hi3716CV200 Hi3719CV100 Hi3718CV100),)
	$(hide) echo "####################### copy modules $(TARGET_PRODUCT)"
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ohci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ehci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/ata/libahci.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/ata/libahci.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
else ifneq ($(findstring $(TARGET_PRODUCT), Hi3796CV100 Hi3798CV100 Hi3798MV100 Hi3796MV100 Hi3798MV100_A),)
	$(hide) echo "####################### copy modules $(TARGET_PRODUCT)"
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ohci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ehci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/xhci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
else
	$(hide) echo "####################### copy modules $(TARGET_PRODUCT)"
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ohci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
	$(hide) cp -avf $(KERNEL_OUT)/drivers/usb/host/ehci-hcd.ko $(TARGET_OUT_SHARED_LIBRARIES)/modules/
endif

ifeq ($(RAMDISK_ENABLE),false)
.PHONY: kernel $(KERNEL_IMAGE)
kernel: $(KERNEL_IMAGE)
else
.PHONY: kernel $(KERNEL_IMAGE) $(INSTALLED_BOOTIMAGE_TARGET)
$(INSTALLED_KERNEL_TARGET): $(KERNEL_IMAGE)
kernel: $(INSTALLED_BOOTIMAGE_TARGET)
	cp -avf $(INSTALLED_BOOTIMAGE_TARGET) $(NAND_PRODUCT_OUT)/kernel.img
	cp -avf $(INSTALLED_BOOTIMAGE_TARGET) $(EMMC_PRODUCT_OUT)/kernel.img
endif


#----------------------------------------------------------------------
# Linux Kernel End
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Update Wifi Drivers
#----------------------------------------------------------------------
wifi: $(KERNEL_IAMGE)
	$(MAKE) -j1 -C $(SDK_DIR)/source/component/wifi/drv/android_driver \
		KERNEL_VERSION=$(HISI_LINUX_KERNEL) \
		ANDROID_PRODUCT_OUT=$(ANDROID_BUILD_TOP)/$(PRODUCT_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE) \
		CONFIG_RT3070_SUPPORT=$(BOARD_WLAN_DEVICE_RT3070) \
		CONFIG_RT5370_SUPPORT=$(BOARD_WLAN_DEVICE_RT5370) \
		CONFIG_RT5372_SUPPORT=$(BOARD_WLAN_DEVICE_RT5372) \
		CONFIG_RT5572_SUPPORT=$(BOARD_WLAN_DEVICE_RT5572) \
		CONFIG_MT7601U_SUPPORT=$(BOARD_WLAN_DEVICE_MT7601U) \
		CONFIG_AR9271_SUPPORT=$(BOARD_WLAN_DEVICE_AR9271) \
		CONFIG_AR9374_SUPPORT=$(BOARD_WLAN_DEVICE_AR9374) \
		CONFIG_QCA1021G_SUPPORT=$(BOARD_WLAN_DEVICE_QCA1021G) \
		CONFIG_QCA1021X_SUPPORT=$(BOARD_WLAN_DEVICE_QCA1021X) \
		CONFIG_RTL8188CUS_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8188CUS) \
		CONFIG_RTL8192CU_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8192CU) \
		CONFIG_RTL8188EUS_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8188EUS) \
		CONFIG_RTL8188ETV_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8188ETV) \
		CONFIG_RTL8192DU_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8192DU) \
		CONFIG_RTL8192EU_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8192EU) \
		CONFIG_RTL8812AU_SUPPORT=$(BOARD_WLAN_DEVICE_RTL8812AU) \
		CONFIG_RTL8723BU_SUPPORT=$(BOARD_BLUETOOTH_WIFI_DEVICE_RTL8723BU)
ALL_DEFAULT_INSTALLED_MODULES += wifi
.PHONY: wifi
wifi: kernel
#----------------------------------------------------------------------
# Update Wifi Drivers END
#----------------------------------------------------------------------

#----------------------------------------------------------------------
# Make Bluetooth Drivers
#----------------------------------------------------------------------
BLUETOOTH_DIR := $(SDK_DIR)
ifeq ($(BOARD_BLUETOOTH_DEVICE_BCM20705),y)
   ifeq ($(BOARD_BLUETOOTH_DEVICE_CSR8510),y)
   $(error only one bluetooth could be built at the same time)
   endif
   ifeq ($(BOARD_BLUETOOTH_DEVICE_REALTEK),y)
   $(error only one bluetooth could be built at the same time)
   endif
else
 ifeq ($(BOARD_BLUETOOTH_DEVICE_CSR8510),y)
   ifeq ($(BOARD_BLUETOOTH_REALTEK),y)
   $(error only one bluetooth could be built at the same time)
   endif
 endif
endif
ifeq ($(BOARD_BLUETOOTH_DEVICE_REALTEK),y)
BLUETOOTH_DIR := $(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/bluetooth/realtek8xxx/driver
endif

ifeq ($(BOARD_BLUETOOTH_DEVICE_BCM20705),y)
BLUETOOTH_DIR := $(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/bluetooth/bcm20705/driver
endif

ifeq ($(BOARD_BLUETOOTH_DEVICE_CSR8510),y)
BLUETOOTH_DIR := $(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/bluetooth/csr8510/driver
endif



ifeq ($(BOARD_HAVE_BLUETOOTH),true)
bluetooth: $(KERNEL_IAMGE)
	$(MAKE) -j1 -C $(BLUETOOTH_DIR) \
                ARCH=arm CROSS_COMPILE=arm-hisiv200-linux- \
		KERNEL_VERSION=$(HISI_LINUX_KERNEL) \
		CHIPNAME=$(CHIPNAME) \
		ANDROID_PRODUCT_OUT=$(ANDROID_BUILD_TOP)/$(PRODUCT_OUT) \
		SDK_CFGFILE=$(SDK_CFGFILE)

ALL_DEFAULT_INSTALLED_MODULES += bluetooth
endif

.PHONY: bluetooth
bluetooth: kernel
#----------------------------------------------------------------------
# Make Bluetooth Drivers END
#---------------------------------------------------------------------
