ifneq ($(CFG_HI_LOADER_APPLOADER),y)
MCE_DIR := mce
LOCAL_SRC_FILES += $(MCE_DIR)/unf_mce.c
LOCAL_C_INCLUDES += $(MSP_DIR)/drv/mce
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/mce/db
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
endif
