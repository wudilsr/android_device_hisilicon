LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
       hash.c

LOCAL_C_INCLUDES := \
       $(LOCAL_PATH)/ \
       external/openssl/include

LOCAL_STATIC_LIBRARIES := libcrypto_static

LOCAL_MODULE := hash_tool
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_HOST_EXECUTABLE)
