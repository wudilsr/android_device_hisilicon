BOARD_HAVE_BLUETOOTH := true
BOARD_HAVE_BLUETOOTH_RTK := true
BOARD_HAVE_BLUETOOTH_RTK_SOURCECODE := false
BOARD_HAVE_BLUETOOTH_RTK_3DD := false
BOARD_HAVE_BLUETOOTH_RTK_VR := false
BOARD_HAVE_BLUETOOTH_RTK_AUTOPAIR := false
BOARD_HAVE_BLUETOOTH_RTK_SCO := false
BOARD_HAVE_BLUETOOTH_RTK_POWERON := false
BOARD_HAVE_BLUETOOTH_RTK_HEARTBEAT := false
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(LOCAL_PATH)

BOARD_HAVE_BLUETOOTH_RTK_IF := usb
BLUETOOTH_HCI_USE_RTK_H5 := false

PRODUCT_PACKAGES += \
    Bluetooth \
    audio.a2dp.default \
    BluetoothMpTest \
    rtlbtmp

PRODUCT_COPY_FILES += \
        frameworks/native/data/etc/android.hardware.bluetooth.xml:system/etc/permissions/android.hardware.bluetooth.xml \
        frameworks/native/data/etc/android.hardware.bluetooth_le.xml:system/etc/permissions/android.hardware.bluetooth_le.xml \
        $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)/rtkbt_virtual_hid.kl:system/usr/keylayout/rtkbt_virtual_hid.kl

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_3DD), true)
PRODUCT_PACKAGES += \
    Bluetooth3ddService
endif
ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_AUTOPAIR), true)
PRODUCT_PACKAGES += \
    BluetoothRTKAutoPairService
endif
ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_VR), true)
PRODUCT_PACKAGES += \
    audio.vohog.default
PRODUCT_PACKAGES += \
    SpeechService \
    Xiri \
    XiriIme \
    XiriVideo
endif
ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_SCO), true)
PRODUCT_PACKAGES += \
    audio.sco.default
endif
ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_IF), usb)
#$(call inherit-product, hardware/realtek/bt/usb/firmware/rtl8723a/device-rtl.mk)
#$(call inherit-product, hardware/realtek/bt/usb/firmware/rtl8723b/device-rtl.mk)
#$(call inherit-product, hardware/realtek/bt/usb/firmware/rtl8761a/device-rtl.mk)
#$(call inherit-product, hardware/realtek/bt/usb/firmware/rtl8821a/device-rtl.mk)
$(call inherit-product, $(LOCAL_PATH)/../realtek/usb/firmware/rtl8723a/device-rtl.mk)
$(call inherit-product, $(LOCAL_PATH)/../realtek/usb/firmware/rtl8723b/device-rtl.mk)
$(call inherit-product, $(LOCAL_PATH)/../realtek/usb/firmware/rtl8761a/device-rtl.mk)
$(call inherit-product, $(LOCAL_PATH)/../realtek/usb/firmware/rtl8821a/device-rtl.mk)
PRODUCT_COPY_FILES += \
        $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)/usb/init.rtkbt.rc:init.rtkbt.rc
endif
ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_IF), uart)
$(call inherit-product, hardware/realtek/bt/uart/firmware/rtlbtfw_cfg.mk)
#$(call inherit-product, $(LOCAL_PATH)/../realtek/uart/firmware/rtlbtfw_cfg.mk)
PRODUCT_COPY_FILES += \
        $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)/uart/init.rtkbt.rc:init.rtkbt.rc
endif
