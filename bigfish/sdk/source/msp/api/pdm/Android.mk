PDM_DIR := pdm
LOCAL_SRC_FILES += $(PDM_DIR)/unf_pdm.c
LOCAL_SRC_FILES += $(PDM_DIR)/mpi_pdm.c
LOCAL_SRC_FILES += $(PDM_DIR)/db/hi_db.c
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/ha_codec/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/higo/include
LOCAL_C_INCLUDES += $(MSP_DIR)/api/pdm/db
