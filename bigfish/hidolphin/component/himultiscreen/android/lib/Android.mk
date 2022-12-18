LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_MODULE := libHiMultiScreen
LOCAL_STATIC_JAVA_LIBRARIES := multiscreenlib
LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled
include $(BUILD_STATIC_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_MODULE := libVIME
LOCAL_STATIC_JAVA_LIBRARIES := multiscreenvimelib
LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled
include $(BUILD_STATIC_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := multiscreenlib:libHiMultiScreenForHost.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += multiscreenvimelib:libVIMEForHost.jar
LOCAL_PREMODULE_SO := libmultiscreendevice \
                       libvime_jni \
                       libremote_server_jni \
                       libremote_data_processor

define addprefixsuffix_so_list
$(addprefix , $(addsuffix .so, $(1)))
endef

LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list, $(LOCAL_PREMODULE_SO))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PREMODULE_SO)

LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)

# gsensor
include $(CLEAR_VARS)
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_SRC_FILES := sensors.bigfish.so
LOCAL_MODULE :=  sensors.bigfish
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_CLASS := SHARED_LIBRARIES
LOCAL_MODULE_SUFFIX:= .so
LOCAL_MODULE_TAGS := optional
include $(BUILD_PREBUILT)

# xc-gamepad-driver
ifeq ($(strip $(PRODUCT_TARGET)), demo)

include $(CLEAR_VARS)
LOCAL_MODULES_NAME := usb-driver
LOCAL_PREBUILT_EXECUTABLES := usb-driver
LOCAL_MODULE_TAGS := optional
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
include $(BUILD_MULTI_PREBUILT)
endif
