
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
########################################################### 
ROOT      =.


#ROOT:= $(call my-dir)
#include      $(CLEAR_VARS)

#LOCAL_ARM_MODE := arm

LOCAL_CFLAGS := -O2 -W -Wall -fno-omit-frame-pointer


LOCAL_C_INCLUDES := \
    -I$(ROOT)/../../include \
    -I$(ROOT)/QA-TZService/inc \
    -I$(ROOT)/QA-TZService/inc_common \
    -I$(ROOT)/../../include/TZInfra_API \
    -I$(ROOT)/../../include/TZInfra_API/Tools \
    -I$(ROOT)/../../include/TZInfra_API/VOS_API

LOCAL_SRC_FILES := \
    QA-TZService/src/QATestTA.o \
    QA-TZService/src/QaCallbackSequence.o \
    QA-TZService/src/QaTestMemory.o \
    QA-TZService/src/QaTestParamCheck.o \
    QA-TZService/src/QA_TZ_Service.o \
    QA-TZService/src/QaTestMemory_Ex.o \
    QA-TZService/src/QaUtils.o \
    QA-TZService/src/QaTestSecureContentPath.o \
    QA-TZService/src/QaTestCrypto.o \
    QA-TZService/src/QaTestCryptoRSA.o \
    QA-TZService/src/QaTestDeviceStatus.o \
    QA-TZService/src/QaTestSecureStorage.o \
    QA-TZService/src/QATestCrypto_Ex.o \
    QA-TZService/src/QaTestDeviceKeys.o \
    QA-TZService/src/QaTestSfsSw.o
#    QA-TZService/src/Qualcomm/security_stream_checker.o


LOCAL_MODULE:= $(OUT)/task_QA_TZService.elf

#trustedcore.img: $(LOCAL_MODULE)

#LOCAL_MODULE_PATH := $(PRODUCT_OUT)
#LOCAL_STATIC_LIBRARIES := libtee

#LOCAL_CC := arm-eabi-gcc
#LOCAL_MODULE_TAGS := optional


TRUSTEDCORE_ELF_MAIN_ENTRY_PATH :=$(ROOT)/../elf_main_entry.o
#include $(ROOT)/../../../trustedcore/task_executable.mk
#$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS += -r -d --strip-debug --whole-archive $(TRUSTEDCORE_ELF_MAIN_ENTRY_PATH) --no-whole-archive

ALL_OBJ = $(LOCAL_SRC_FILES)
LOCAL_OUT = $(OUT)/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))

CFLAGS += $(LOCAL_CFLAGS) $(LOCAL_C_INCLUDES)
LDFLAGS += -r -d --strip-debug --whole-archive $(TRUSTEDCORE_ELF_MAIN_ENTRY_PATH) --no-whole-archive

#LIBCOMPILER = $(ROOT)/../../release/libcompiler_rt-extras.a

##########################################################
# build demo_task1
##########################################################
.PHONY : all prepare clean
all: prepare $(ALL_OBJ)
	@echo $(ALL_OBJ)
	$(LD1) $(LDFLAGS) -o $(LOCAL_MODULE) $(ALL_OUT_OBJ) `$(CC1) -mthumb-interwork -print-libgcc-file-name`
	@echo "Make $(LOCAL_MODULE) Success!"
prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))	
clean:
	$(RM) $(LOCAL_MODULE) $(ALL_OUT_OBJ) $(ALL_OBJ)

%.o : %.c
	$(CC1) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@
	
