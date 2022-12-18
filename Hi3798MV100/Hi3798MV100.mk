$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base.mk)

CHIPNAME := Hi3798MV100
PRODUCT_NAME := Hi3798MV100
PRODUCT_DEVICE := Hi3798MV100
PRODUCT_BRAND := HiSTBAndroidV5
PRODUCT_MODEL := Hi3798MV100
PRODUCT_MANUFACTURER := Hisilicon
BOARD_BLUETOOTH_DEVICE_REALTEK := y

$(call inherit-product, device/hisilicon/Hi3798MV100/device.mk)

ifeq ($(BOARD_BLUETOOTH_DEVICE_REALTEK),y)
$(call inherit-product, device/hisilicon/bigfish/bluetooth/realtek8xxx/rtk_lib/lib/rtkbt.mk)
endif
