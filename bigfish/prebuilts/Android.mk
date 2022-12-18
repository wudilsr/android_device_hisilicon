LOCAL_PATH := $(call my-dir)
GPLAY_LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := Vendor_0001_Product_0001.kl
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/usr/keylayout
LOCAL_SRC_FILES := Vendor_0001_Product_0001.kl
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := Vendor_060a_Product_1000.kl
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/usr/keylayout
LOCAL_SRC_FILES := Vendor_060a_Product_1000.kl
include $(BUILD_PREBUILT)
include $(CLEAR_VARS)
LOCAL_MODULE := busybox
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := busybox
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAG := optional
include $(BUILD_PREBUILT)

ifeq ($(strip $(PRODUCT_TARGET)), shcmcc)
include $(CLEAR_VARS)
LOCAL_MODULE := bootanimation.zip
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/media
LOCAL_SRC_FILES := bootanimation_chinamobile.zip
include $(BUILD_PREBUILT)
else
ifeq ($(strip $(PRODUCT_TARGET)), demo)
include $(CLEAR_VARS)
LOCAL_MODULE := bootanimation.zip
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/media
LOCAL_SRC_FILES := bootanimation_1080p.zip
include $(BUILD_PREBUILT)
endif
endif

ifeq ($(BOARD_QBSUPPORT),true)
include $(CLEAR_VARS)
LOCAL_MODULE := quickboot.zip
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/media
LOCAL_SRC_FILES := quickboot.zip
include $(BUILD_PREBUILT)
endif

include $(CLEAR_VARS)
LOCAL_MODULE := networkprovider.xml
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc
LOCAL_SRC_FILES := networkprovider.xml
include $(BUILD_PREBUILT)

############################samba#####################################
include $(CLEAR_VARS)
LOCAL_MODULE := samba_quick_search
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := samba_quick_search
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAG := optional
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := libsamba_quick_search.so
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/lib
LOCAL_SRC_FILES := libsamba_quick_search.so
include $(BUILD_PREBUILT)
############################btools#####################################
include $(CLEAR_VARS)
LOCAL_MODULE := btools
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := btools
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAG := optional

HISI_BTOOLS := himc himd himd.l himm
HISI_SYMLINKS := $(addprefix $(TARGET_OUT)/bin/,$(HISI_BTOOLS))
$(HISI_SYMLINKS): HISIBTOOLS_BINARY := $(LOCAL_PATH)/btools
$(HISI_SYMLINKS): $(LOCAL_INSTALLED_MODULE) $(LOCAL_PATH)/Android.mk
	@echo "Copy: $@ -> $(HISIBTOOLS_BINARY)"
	@mkdir -p $(dir $@)
	@rm -rf $@
	$(hide) cp -rvf $(HISIBTOOLS_BINARY) $@

ALL_DEFAULT_INSTALLED_MODULES += $(HISI_SYMLINKS)
ALL_MODULES.$(LOCAL_MODULE).INSTALLED := \
	$(ALL_MODULES.$(LOCAL_MODULE).INSTALLED) $(HISI_SYMLINKS)

include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := keyfunction.xml
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc
LOCAL_SRC_FILES := keyfunction.xml
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := smbtree
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_SRC_FILES := smbtree
LOCAL_MODULE_CLASS := EXECUTABLES
LOCAL_MODULE_TAG := optional
include $(BUILD_PREBUILT)

include $(LOCAL_PATH)/nfsClient/Android.mk \
        $(LOCAL_PATH)/enforce/Android.mk

-include $(LOCAL_PATH)/ThirdPartyApplications/Android.mk
-include $(GPLAY_LOCAL_PATH)/googleplay/Android.mk
