LOCAL_PATH := $(call my-dir)

# Setup bdroid local make variables for handling configuration
ifneq ($(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR),)
  bdroid_C_INCLUDES := $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)
  bdroid_CFLAGS := -DHAS_BDROID_BUILDCFG
else
  bdroid_C_INCLUDES :=
  bdroid_CFLAGS := -DHAS_NO_BDROID_BUILDCFG
endif

ifeq ($(BOARD_BLUETOOTH_DEVICE_CSR8510),y)
$(warning "CSR---------CSR---------CSR")
include $(call all-subdir-makefiles)
endif

# Cleanup our locals
bdroid_C_INCLUDES :=
bdroid_CFLaGS :=
