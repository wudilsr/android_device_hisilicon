LOCAL_PATH := $(call my-dir)

# RealTek Bluetooth private configuration table
ifeq ($(BOARD_HAVE_BLUETOOTH_RTK),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_3DD),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_3DD
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_AUTOPAIR),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_AUTOPAIR
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_VR),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_VR
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_SCO),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_SCO
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_POWERON),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_POWERON
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_HEARTBEAT),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_HEARTBEAT
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_COEX),true)
rtkbt_bdroid_CFLAGS += -DBLUETOOTH_RTK_COEX
endif

ifeq ($(PLATFORM_VERSION), 4.3)
rtkbt_bdroid_CFLAGS += -DANDROID_43
endif

endif

# Setup bdroid local make variables for handling configuration
ifneq ($(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR),)
  bdroid_C_INCLUDES := $(BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR)
  bdroid_CFLAGS := -DHAS_BDROID_BUILDCFG $(rtkbt_bdroid_CFLAGS)
else
  bdroid_C_INCLUDES :=
  bdroid_CFLAGS := -DHAS_NO_BDROID_BUILDCFG $(rtkbt_bdroid_CFLAGS)
endif

include $(call all-subdir-makefiles)

# Cleanup our locals
bdroid_C_INCLUDES :=
bdroid_CFLAGS :=
