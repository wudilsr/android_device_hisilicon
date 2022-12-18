LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
            mxml-attr.c mxml-entity.c mxml-file.c mxml-get.c \
            mxml-index.c mxml-node.c mxml-search.c mxml-set.c \
            mxml-private.c mxml-string.c

LOCAL_SHARED_LIBRARIES := \
    libcutils liblog

LOCAL_C_INCLUDES := \
    system/core/include/netutils \
    $(LOCAL_PATH)/

LOCAL_CFLAGS := -D_THREAD_SAFE -D_REENTRANT -fPIC -g
LOCAL_LDLIBS := -lpthread

LOCAL_MODULE:= libmxml

include $(BUILD_SHARED_LIBRARY)