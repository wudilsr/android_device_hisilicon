LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
    hash.c

LOCAL_CFLAGS =   -static -Wall
ifeq ($(HOST_OS),linux)
LOCAL_LDLIBS += -ldl
endif

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/ \
    $(HISI_PLATFORM_PATH)/security/secureSignTool/openssl-1.0.1g/include

LOCAL_STATIC_LIBRARIES := libz
LOCAL_LDLIBS += -L$(HISI_PLATFORM_PATH)/security/secureSignTool/libs -lcrypto

LOCAL_MODULE := hash_tool
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_HOST_EXECUTABLE)
