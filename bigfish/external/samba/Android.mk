LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

CODEPATH := $(LOCAL_PATH)/codepages

TARGET_SAMBA_CONF_DIR := $(TARGET_OUT)/samba/codepages
TARGET_SAMBA_BIN_DIR := $(TARGET_OUT)/bin
TARGET_SAMBA_LIB_DIR := $(TARGET_OUT)/lib
LOCAL_SAMBA_DIR  := $(CODEPATH)

copy_conf_from :=   \
	lowcase.dat     \
	upcase.dat      \
	valid.dat       \
	CP850.so        \
	CP437.so

copy_bin_from := \
    smbd         \
    nmbd         \
    nmblookup    \
    smbclient    \
    smbpasswd

copy_lib_from :=     \
    libtalloc.so     \
    libtdb.so        \
    libwbclient.so

copy_conf_to   := $(addprefix $(TARGET_SAMBA_CONF_DIR)/,$(copy_conf_from))
copy_conf_from := $(addprefix $(LOCAL_SAMBA_DIR)/,$(copy_conf_from))

copy_bin_to   := $(addprefix $(TARGET_SAMBA_BIN_DIR)/,$(copy_bin_from))
copy_bin_from := $(addprefix $(LOCAL_SAMBA_DIR)/,$(copy_bin_from))

copy_lib_to   := $(addprefix $(TARGET_SAMBA_LIB_DIR)/,$(copy_lib_from))
copy_lib_from := $(addprefix $(LOCAL_SAMBA_DIR)/,$(copy_lib_from))

$(copy_conf_to) : $(TARGET_SAMBA_CONF_DIR)/% : $(LOCAL_SAMBA_DIR)/% | $(ACP)
	$(transform-prebuilt-to-target)

$(copy_bin_to) : $(TARGET_SAMBA_BIN_DIR)/% : $(LOCAL_SAMBA_DIR)/% | $(ACP)
	$(transform-prebuilt-to-target)

$(copy_lib_to) : $(TARGET_SAMBA_LIB_DIR)/% : $(LOCAL_SAMBA_DIR)/% | $(ACP)
	$(transform-prebuilt-to-target)

ALL_DEFAULT_INSTALLED_MODULES += $(copy_conf_to)
ALL_DEFAULT_INSTALLED_MODULES += $(copy_bin_to)
ALL_DEFAULT_INSTALLED_MODULES += $(copy_lib_to)
