RTK_BT_FIRMWARE_DIR := rtl8723b
PRODUCT_COPY_FILES += \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_fw:system/etc/firmware/rtl8723b_fw \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)_config:system/etc/firmware/rtl8723b_config \
	$(LOCAL_PATH)/$(RTK_BT_FIRMWARE_DIR)u_config:system/etc/firmware/rtl8723bu_config
