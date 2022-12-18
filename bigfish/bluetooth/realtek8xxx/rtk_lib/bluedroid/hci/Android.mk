LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        src/bt_hci_bdroid.c \
        src/lpm.c \
        src/bt_hw.c \
        src/btsnoop.c \
        src/utils.c

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK),true)
LOCAL_SRC_FILES += \
        src/bt_list.c
endif

ifeq ($(BLUETOOTH_HCI_USE_MCT),true)

LOCAL_CFLAGS := -DHCI_USE_MCT

LOCAL_SRC_FILES += \
        src/hci_mct.c \
        src/userial_mct.c

else
ifeq ($(BLUETOOTH_HCI_USE_RTK_H5),true)

LOCAL_CFLAGS := -DHCI_USE_RTK_H5

LOCAL_SRC_FILES += \
       src/hci_h5.c \
       src/userial.c \
       src/bt_skbuff.c

else
LOCAL_SRC_FILES += \
        src/hci_h4.c \
        src/userial.c
endif

endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_HEARTBEAT),true)
LOCAL_CFLAGS += -DBLUETOOTH_RTK_HEARTBEAT
LOCAL_SRC_FILES += \
        src/poll.c
endif

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/include \
        $(LOCAL_PATH)/../utils/include

LOCAL_SHARED_LIBRARIES := \
        libcutils \
        liblog \
        libdl \
        libbt-utils

LOCAL_MODULE := libbt-hci
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := SHARED_LIBRARIES

include $(BUILD_SHARED_LIBRARY)
