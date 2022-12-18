ifeq ($(strip $(CHIPNAME)),Hi3798MV100)
LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE := vold.emmc.fstab
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc
$(warning echo $(TARGET_HAVE_APPLOADER))
ifeq ($(SUPPORT_SDCARDFS),true)
	ifeq ($(TARGET_HAVE_APPLOADER),true)
		LOCAL_SRC_FILES := vold.sdcardfs.emmc.loader.fstab
	else
		LOCAL_SRC_FILES := vold.sdcardfs.emmc.fstab
	endif
else
	ifeq ($(TARGET_HAVE_APPLOADER),true)
		ifeq ($(VMX_ADVANCED_SUPPORT),true)
			LOCAL_SRC_FILES := vold.emmc.fstab
		else
			LOCAL_SRC_FILES := vold.emmc.loader.fstab
		endif
	else
		LOCAL_SRC_FILES := vold.emmc.fstab
	endif
endif
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := vold.fstab
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc
ifeq ($(SUPPORT_SDCARDFS),true)
LOCAL_SRC_FILES := vold.sdcardfs.fstab
else
LOCAL_SRC_FILES := vold.fstab
endif
include $(BUILD_PREBUILT)

include $(CLEAR_VARS)
LOCAL_MODULE := limitApplications.xml
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := ETC
LOCAL_MODULE_PATH := $(TARGET_OUT)/etc
LOCAL_SRC_FILES := limitApplications.xml
include $(BUILD_PREBUILT)
endif
