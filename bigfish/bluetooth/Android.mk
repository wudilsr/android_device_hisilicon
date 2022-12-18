include $(CLEAR_VARS)

ifeq ($(BOARD_BLUETOOTH_DEVICE_BCM20705),y)
include $(HISI_PLATFORM_PATH)/bluetooth/bcm20705/lib/Android.mk
endif

ifeq ($(BOARD_BLUETOOTH_DEVICE_REALTEK),y)
include $(HISI_PLATFORM_PATH)/bluetooth/realtek8xxx/rtk_lib/Android.mk
endif
