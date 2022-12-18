LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_PACKAGE_NAME := Miracast
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
LOCAL_PROGUARD_ENABLED := disabled
LOCAL_SRC_FILES := $(call all-java-files-under, src)
LOCAL_CERTIFICATE := platform
LOCAL_OVERRIDES_PACKAGES := platform
include $(BUILD_PACKAGE)


include $(CLEAR_VARS)
LOCAL_PREMODULE_SO := libsink_jni libhiwfd_bean libhiwfd libsinkplayer libDxHdcp libhihal_miracast libhihdcp_adp
define addprefixsuffix_so_list
$(addprefix libs/, $(addsuffix .so, $(1)))
endef
LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list, $(LOCAL_PREMODULE_SO))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PREMODULE_SO)
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

-include $(LOCAL_PATH)/libs/hdcpprovision/Android.mk
