ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
CI_DIR := ci
LOCAL_SRC_FILES += $(CI_DIR)/mpi_ci.c
LOCAL_SRC_FILES += $(CI_DIR)/unf_ci.c
endif