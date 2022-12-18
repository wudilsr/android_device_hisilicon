ifneq ($(CFG_HI_LOADER_APPLOADER),y)
ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
WDG_DIR := wdg
LOCAL_SRC_FILES += $(WDG_DIR)/unf_wdg.c
endif
endif
