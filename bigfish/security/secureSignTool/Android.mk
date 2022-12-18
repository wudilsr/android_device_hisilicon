LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
       src/crypto.c \
       src/sign_non_boot_image.c \
       src/sha2.c \
       src/adapter.c \
       secureSignTool.c

LOCAL_CFLAGS =   -static -Wall
ifeq ($(HOST_OS),linux)
LOCAL_LDLIBS += -ldl
endif

LOCAL_C_INCLUDES := \
       $(LOCAL_PATH)/ \
       $(LOCAL_PATH)/src \
       $(LOCAL_PATH)/openssl-1.0.1g/include

LOCAL_STATIC_LIBRARIES := libz
#LOCAL_STATIC_LIBRARIES += libcrypto
LOCAL_LDLIBS += -L$(LOCAL_PATH)/libs -lBootSign -lcrypto

LOCAL_MODULE := secureSignTool

include $(BUILD_HOST_EXECUTABLE)
-include $(LOCAL_PATH)/libs/Android.mk
