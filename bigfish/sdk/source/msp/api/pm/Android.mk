ifneq ($(CFG_HI_LOADER_APPLOADER),y)
PM_DIR := pm

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
LOCAL_CFLAGS += -DHI_KEYLED_SUPPORT
endif

LOCAL_SRC_FILES += $(PM_DIR)/unf_pmoc.c
LOCAL_SRC_FILES += $(PM_DIR)/pmoc_usb_wakeup.c
endif
