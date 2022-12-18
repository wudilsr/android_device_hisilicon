LOCAL_PATH:= $(call my-dir)
include      $(CLEAR_VARS)
include $(LOCAL_PATH)/../../trustedcore/trustedcore.mk

################################################
## cd driver config
#################################################
ifeq ($(strip $(WITH_STB_CIPHER_DRIVER)),true)
LOCAL_CFLAGS += -DSTB_CIPHER_DRIVER
endif

SDK_DIR := $(LOCAL_PATH)/../../../../..
SOURCE_DIR=$(SDK_DIR)/source
MSP_DIR=${SOURCE_DIR}/msp
MSP_UNF_INCLUDE=${MSP_DIR}/include

PATH01 = ${LOCAL_PATH}/../include
PATH02 = ${LOCAL_PATH}/../include_tee_ext/libc
PATH03 = ${LOCAL_PATH}/../include_tee_ext/tee
PATH04 = ${LOCAL_PATH}/../include_tee_ext/tee_initlib
PATH05 = ${LOCAL_PATH}/../include_kernel
PATH06 = ${LOCAL_PATH}/../thirdparty/cipher_code ${LOCAL_PATH}/api/cipher ${LOCAL_PATH}/api/include $(MSP_UNF_INCLUDE) 
PATH07 = ${LOCAL_PATH}/../include/TZInfra_API
PATH08 = ${LOCAL_PATH}/../include/TZInfra_API/Tools
PATH09 = ${LOCAL_PATH}/../include/TZInfra_API/VOS_API
PATH10 = ${LOCAL_PATH}/../include_kernel/config
PATH11 = ${LOCAL_PATH}/../include_kernel/ph
PATH12 = $(LOCAL_PATH)/../trustedcore_kernel/syscalls_ext

PATH13 = $(LOCAL_PATH)/../thirdparty/cipher_code \
	 $(LOCAL_PATH)/../thirdparty/cipher_code/sha \
	 $(LOCAL_PATH)/../thirdparty/cipher_code/rsa \
	 $(LOCAL_PATH)/../thirdparty/cipher_code/tee/include

INCLUDE := \
$(PATH01) \
$(PATH02) \
$(PATH03) \
$(PATH04) \
$(PATH05) \
$(PATH06) \
$(PATH07) \
$(PATH08) \
$(PATH09) \
$(PATH10) \
$(PATH12) \
$(PATH11) \
$(PATH13)
#################################################
## export symbol
#################################################
SYMBOL_SRC = \
	symbol/tee_symbol.c
#################################################
## TZInfra Api
#################################################
DZ_TZINFRA_API = \
    TZInfra_API/DxTzServiceAPI.c \
    TZInfra_API/DxTzServiceCryptoAPI.c \
    TZInfra_API/DxTzServiceSfs.c \
    TZInfra_API/stub.c
MMZ_SRC = \
	mmz/hi_mmz.c
CIPHER_SRC = \
	api/cipher/tz_unf_cipher.c
SYSCALLS_EXT_SRC = \
	../trustedcore_kernel/syscalls_ext/sre_syscalls_ext.S

LIB_SRCS = \
$(SYMBOL_SRC) \
$(DZ_TZINFRA_API) \
$(MMZ_SRC) \
$(CIPHER_SRC) \
$(SYSCALLS_EXT_SRC)

LOCAL_ARM_MODE := arm

GLOBALTASK_TEXT_BASE = 0

LOCAL_CFLAGS += -O2 -g -fPIC -fno-omit-frame-pointer
#LOCAL_CFLAGS += -O2 -g -W -Wall
LOCAL_CFLAGS += -march=armv7-a

LOCAL_C_INCLUDES := $(INCLUDE)

LOCAL_SRC_FILES := \
	$(LIB_SRCS)

LOCAL_MODULE:= globaltask.img
LOCAL_MODULE_PATH := $(PRODUCT_OUT)

LOCAL_MODULE_TAGS := optional
TARGET_GLOBALTASK_LINK_SCRIPT := $(LOCAL_PATH)/link.ld

HAVE_TRUSTEDCORE_SRC_PATH := $(wildcard $(LOCAL_PATH)/../../trustedcore_src/Android.mk)
SYSTEM_STATIC_LIB_PATH = $(PRODUCT_OUT)/obj/STATIC_LIBRARIES
ifneq ($(HAVE_TRUSTEDCORE_SRC_PATH),)
GLOBALTASK_LIB_PATH = $(SYSTEM_STATIC_LIB_PATH)/libtee_intermediates/libtee.a
GLOBALTASK_O= $(SYSTEM_STATIC_LIB_PATH)/global_task_o_intermediates/global_task.o
else
GLOBALTASK_LIB_PATH = $(LOCAL_PATH)/../release/internal_tasks/libtee.a
GLOBALTASK_O = $(LOCAL_PATH)/../release/internal_tasks/global_task.o
endif
include $(BUILD_RAW_EXECUTABLE)

$(LOCAL_BUILT_MODULE) : PRIVATE_LINK_SCRIPT := $(TARGET_GLOBALTASK_LINK_SCRIPT)
$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS := -pie --section-start .globaltask=$(GLOBALTASK_TEXT_BASE)  -Map globaltask.map
$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS += --whole-archive $(GLOBALTASK_O) $(GLOBALTASK_LIB_PATH) --no-whole-archive

