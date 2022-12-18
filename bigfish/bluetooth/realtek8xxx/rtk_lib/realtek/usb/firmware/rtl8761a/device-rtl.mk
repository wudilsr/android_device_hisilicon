RTK_BT_FIRMWARE_DIR := rtl8761a
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)u_fw:system/etc/firmware/rtl8761au_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)u8192ee_fw:system/etc/firmware/rtl8761au8192ee_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)u8812ae_fw:system/etc/firmware/rtl8761au8812ae_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)w8192eu_fw:system/etc/firmware/rtl8761aw8192eu_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_config:system/etc/firmware/rtl8761a_config \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)w8192eu_config:system/etc/firmware/rtl8761aw8192eu_config
