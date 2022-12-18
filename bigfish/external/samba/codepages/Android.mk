MYPATH := device/hisilicon/bigfish/external/samba/codepages

TARGET_ALSA_CONF_DIR := $(TARGET_OUT)/samba/codepages
LOCAL_ALSA_CONF_DIR  := $(MYPATH)/

copy_from := \
	lowcase.dat \
	upcase.dat \
	valid.dat \
	CP850.so \
	CP437.so


copy_to   := $(addprefix $(TARGET_ALSA_CONF_DIR)/,$(copy_from))
copy_from := $(addprefix $(LOCAL_ALSA_CONF_DIR)/,$(copy_from))

$(copy_to) : $(TARGET_ALSA_CONF_DIR)/% : $(LOCAL_ALSA_CONF_DIR)/% | $(ACP)
	$(transform-prebuilt-to-target)

ALL_DEFAULT_INSTALLED_MODULES += $(copy_to)

#PRODUCT_COPY_FILES := \
#		$(MYPATH)/lowcase.dat:system/samba/codepages/lowcase.dat \
#		$(MYPATH)/upcase.dat:system/samba/codepages/upcase.dat \
#		$(MYPATH)/valid.dat:system/samba/codepages/valid.dat \
#		$(MYPATH)/CP850.so:system/samba/codepages/CP850.so \
#		$(MYPATH)/CP437.so:system/samba/codepages/CP437.so
