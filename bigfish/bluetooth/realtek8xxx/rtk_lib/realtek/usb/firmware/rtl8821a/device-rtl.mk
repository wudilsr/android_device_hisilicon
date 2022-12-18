RTK_BT_FIRMWARE_DIR := rtl8821a
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_fw:system/etc/firmware/rtl8821a_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_config:system/etc/firmware/rtl8821a_config