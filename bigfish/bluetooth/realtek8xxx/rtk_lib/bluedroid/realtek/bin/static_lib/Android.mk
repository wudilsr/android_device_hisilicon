LOCAL_PATH := $(call my-dir)

ifneq ($(BOARD_HAVE_BLUETOOTH_RTK_SOURCECODE),true)

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_VR),true)
include $(CLEAR_VARS) 
$(call add-prebuilt-files, STATIC_LIBRARIES, libbt-rtk_vr.a)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_SCO),true)
include $(CLEAR_VARS) 
$(call add-prebuilt-files, STATIC_LIBRARIES, libbt-rtk_sco.a)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_AUTOPAIR),true)
include $(CLEAR_VARS) 
$(call add-prebuilt-files, STATIC_LIBRARIES, libbt-rtk_autopair.a)
endif

ifeq ($(BOARD_HAVE_BLUETOOTH_RTK_POWERON),true)
include $(CLEAR_VARS)
$(call add-prebuilt-files, STATIC_LIBRARIES, libbt-rtk_virtual_hid.a)
endif

endif

