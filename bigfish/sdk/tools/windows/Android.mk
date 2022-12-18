LOCAL_PATH := $(call my-dir)

define fine-hitool-under
$(shell find $(1) -name "HiTool*.zip" -exec basename {} \; )
endef

include $(CLEAR_VARS)
HITOOL_NAME := $(call fine-hitool-under, $(LOCAL_PATH)/HiTool )
TOOLS_DST_FILE := $(PRODUCT_OUT)/$(HITOOL_NAME)
TOOLS_SRC_FILE := $(LOCAL_PATH)/HiTool/$(HITOOL_NAME)

$(TOOLS_DST_FILE): $(TOOLS_SRC_FILE) | $(ACP)
	@echo "install Hisilicon tools ..."
	@mkdir -p $(dir $@)
	$(ACP) -fvp "$(TOOLS_SRC_FILE)" "$(TOOLS_DST_FILE)"

ALL_DEFAULT_INSTALLED_MODULES += $(TOOLS_DST_FILE)
