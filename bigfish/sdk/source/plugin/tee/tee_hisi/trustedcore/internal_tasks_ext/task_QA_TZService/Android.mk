LOCAL_PATH:= $(call my-dir)
include      $(CLEAR_VARS)

LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := -O2 -W -Wall

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../../include \
    $(LOCAL_PATH)/QA-TZService/inc \
    $(LOCAL_PATH)/QA-TZService/inc_common \
    ${LOCAL_PATH}/../../include/TZInfra_API \
    ${LOCAL_PATH}/../../include/TZInfra_API/Tools \
    $(LOCAL_PATH)/../../include/TZInfra_API/VOS_API

LOCAL_SRC_FILES := \
    QA-TZService/src/QATestTA.c \
    QA-TZService/src/QaCallbackSequence.c \
    QA-TZService/src/QaTestMemory.c \
    QA-TZService/src/QaTestParamCheck.c \
    QA-TZService/src/QA_TZ_Service.c \
    QA-TZService/src/QaTestMemory_Ex.c \
    QA-TZService/src/QaUtils.c \
    QA-TZService/src/QaTestSecureContentPath.c \
    QA-TZService/src/QaTestCrypto.c \
    QA-TZService/src/QaTestCryptoRSA.c \
    QA-TZService/src/QaTestDeviceStatus.c \
    QA-TZService/src/QaTestSecureStorage.c \
    QA-TZService/src/QATestCrypto_Ex.c \
    QA-TZService/src/QaTestDeviceKeys.c \
    QA-TZService/src/QaTestSfsSw.c
#    QA-TZService/src/Qualcomm/security_stream_checker.c


LOCAL_MODULE :=task_QA_TZService

trustedcore.img: $(LOCAL_MODULE)

LOCAL_MODULE_PATH := $(PRODUCT_OUT)

#LOCAL_STATIC_LIBRARIES := libtee

LOCAL_CC := arm-eabi-gcc
LOCAL_MODULE_TAGS := optional
TRUSTEDCORE_ELF_MAIN_ENTRY_PATH :=$(LOCAL_PATH)/../elf_main_entry.o
include $(LOCAL_PATH)/../../../trustedcore/task_executable.mk
$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS += -r -d --strip-debug --whole-archive $(TRUSTEDCORE_ELF_MAIN_ENTRY_PATH) --no-whole-archive
