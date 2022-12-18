LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
        ../../examples/libbluray_test.c \
        ../../util/logging.c \

LOCAL_C_INCLUDES += \
        $(LOCAL_PATH)/../.. \

LOCAL_CPPFLAGS := -DHI_BLURAY_EXTENSION

LOCAL_SHARED_LIBRARIES := \
        libbluray_ex \

LOCAL_MODULE:= test-libbluray

LOCAL_MODULE_TAGS := test
include $(BUILD_EXECUTABLE)