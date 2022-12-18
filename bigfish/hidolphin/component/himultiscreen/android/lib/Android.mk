LOCAL_PATH := $(my-dir)

ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 21 ))" )))
# backup default target out
TARGET_OUT_INTERMEDIATES_BAK := $(TARGET_OUT_INTERMEDIATES)
TARGET_OUT_INTERMEDIATE_LIBRARIES_BAK := $(TARGET_OUT_INTERMEDIATE_LIBRARIES)
TARGET_OUT_SHARED_LIBRARIES_BAK := $(TARGET_OUT_SHARED_LIBRARIES)
# change to 32bit target out
ifeq (arm64,$(TARGET_ARCH))
TARGET_OUT_INTERMEDIATES := $(PRODUCT_OUT)/obj_arm
else
TARGET_OUT_INTERMEDIATES := $(PRODUCT_OUT)/obj
endif
TARGET_OUT_INTERMEDIATE_LIBRARIES := $(TARGET_OUT_INTERMEDIATES)/lib
TARGET_OUT_SHARED_LIBRARIES := $(PRODUCT_OUT)/system/lib
endif

############################## libHiMultiScreen.jar begin ##############################
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 23 ))" )))
# Use classes.jack in Android6.0 or higher
else
include $(CLEAR_VARS)

LOCAL_MODULE := libHiMultiScreen

LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_STATIC_JAVA_LIBRARIES := multiscreenlib

include $(BUILD_STATIC_JAVA_LIBRARY)
endif
############################### libHiMultiScreen end ###############################


############################## libVIME.jar begin ##############################
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 23 ))" )))
# Use classes.jack in Android6.0 or higher
else
include $(CLEAR_VARS)

LOCAL_MODULE := libVIME

LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled

LOCAL_SRC_FILES := $(call all-subdir-java-files)

LOCAL_STATIC_JAVA_LIBRARIES := multiscreenvimelib

include $(BUILD_STATIC_JAVA_LIBRARY)
endif
############################### libVIME.jar end ###############################


############################## *.so *.jar begin ##############################
include $(CLEAR_VARS)

LOCAL_PREMODULE_SO := libmultiscreendevice libHME_Video_HomeNetwork libvime_jni libremote_server_jni libremote_data_processor

ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) < 21 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PREMODULE_SO)
endif

ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 23 ))" )))
# jack compile
LOCAL_STATIC_JACK_LIBRARIES := libHiMultiScreen libVIME
$(call multi-prebuilt-jack-libs, $(LOCAL_STATIC_JACK_LIBRARIES))
else
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := multiscreenlib:libHiMultiScreenForHost.jar
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES += multiscreenvimelib:libVIMEForHost.jar
endif

LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS := optional

define addprefixsuffix_so_list
$(addprefix , $(addsuffix .so, $(1)))
endef

LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list, $(LOCAL_PREMODULE_SO))

include $(BUILD_MULTI_PREBUILT)
############################### *.so *.jar end ###############################


############################## sensors.bigfish.so begin ##############################
# gsensor
ifeq ($(strip $(ENHANCE_APPLICATION_COMPATIBILITY)), true)
# Do not build gsensor in CTS.
else
include $(CLEAR_VARS)

LOCAL_MODULE := sensors.bigfish

LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS:= optional

$(shell mkdir -p $(TARGET_OUT)/lib/hw)
$(shell cp -rf $(LOCAL_PATH)/sensors.bigfish.so $(TARGET_OUT)/lib/hw/sensors.bigfish.so)

ifeq (true, $(TARGET_SUPPORTS_64_BIT_APPS))
$(shell mkdir -p $(TARGET_OUT)/lib64/hw)
$(shell cp -rf $(LOCAL_PATH)/sensors.bigfish.so.64 $(TARGET_OUT)/lib64/hw/sensors.bigfish.so)
endif

include $(BUILD_PHONY_PACKAGES)
endif
############################### sensors.bigfish.so end ###############################

# resume default target out
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 21 ))" )))
include $(CLEAR_VARS)
TARGET_OUT_INTERMEDIATES := $(TARGET_OUT_INTERMEDIATES_BAK)
TARGET_OUT_INTERMEDIATE_LIBRARIES := $(TARGET_OUT_INTERMEDIATE_LIBRARIES_BAK)
TARGET_OUT_SHARED_LIBRARIES := $(TARGET_OUT_SHARED_LIBRARIES_BAK)
include $(BUILD_MULTI_PREBUILT)
endif
