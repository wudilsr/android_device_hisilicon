ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
KEYLED_DIR := keyled
LOCAL_SRC_FILES += $(KEYLED_DIR)/unf_keyled.c
endif
