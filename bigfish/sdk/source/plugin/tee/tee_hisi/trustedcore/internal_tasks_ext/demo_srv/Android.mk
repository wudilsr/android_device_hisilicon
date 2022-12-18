LOCAL_PATH:= $(call my-dir)
include      $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := -O2 -W -Wall -fno-omit-frame-pointer

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/QA-TZService/inc \
    $(LOCAL_PATH)/QA-TZService/inc_common \
    ${LOCAL_PATH}/../../include/TZInfra_API \
    ${LOCAL_PATH}/../../include/TZInfra_API/Tools \
    $(LOCAL_PATH)/../../include/TZInfra_API/VOS_API

LOCAL_SRC_FILES := \
         demo_task.c

LOCAL_MODULE:= task_demo

trustedcore.img: $(LOCAL_MODULE)

LOCAL_MODULE_PATH := $(PRODUCT_OUT)
#LOCAL_STATIC_LIBRARIES := libtee

LOCAL_CC := arm-eabi-gcc
LOCAL_MODULE_TAGS := optional


TRUSTEDCORE_ELF_MAIN_ENTRY_PATH :=$(LOCAL_PATH)/../elf_main_entry.o
include $(LOCAL_PATH)/../../../trustedcore/task_executable.mk
$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS += -r -d --strip-debug --whole-archive $(TRUSTEDCORE_ELF_MAIN_ENTRY_PATH) --no-whole-archive
