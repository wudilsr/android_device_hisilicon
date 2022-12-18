LOCAL_PATH:= $(call my-dir)

############################## MultiScreenServer.apk begin ##############################
include $(CLEAR_VARS)

LOCAL_PACKAGE_NAME := MultiScreenServer

ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) < 21 ))" )))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_PACKAGE_NAME)
endif

ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) >= 23 ))" )))
LOCAL_JAVA_LIBRARIES := org.apache.http.legacy
endif

LOCAL_MULTILIB := 32
LOCAL_MODULE_TAGS := optional
LOCAL_PROGUARD_ENABLED := disabled
LOCAL_CERTIFICATE := platform

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_STATIC_JAVA_LIBRARIES  := libHiMultiScreen

LOCAL_JNI_SHARED_LIBRARIES := libmultiscreendevice
LOCAL_JNI_SHARED_LIBRARIES += libupnp libixml libthreadutil libvime_jni
LOCAL_JNI_SHARED_LIBRARIES += libremote_data_processor libremote_server_jni

include $(BUILD_PACKAGE)
############################### MultiScreenServer.apk end ###############################
