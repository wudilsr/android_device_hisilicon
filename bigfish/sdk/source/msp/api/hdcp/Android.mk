ifeq ($(CFG_HI_HDMI_SUPPORT_HDCP),y)
HDCP_DIR := hdcp
LOCAL_SRC_FILES += $(HDCP_DIR)/unf_hdcp.c
endif
