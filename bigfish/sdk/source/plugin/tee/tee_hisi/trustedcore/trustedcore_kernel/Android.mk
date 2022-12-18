LOCAL_PATH:= $(call my-dir)

include      $(CLEAR_VARS)
include $(LOCAL_PATH)/../trustedcore.mk

ifeq ($(strip $(WITH_STB_CIPHER_DRIVER)), true)
LOCAL_CFLAGS += -DSTB_CIPHER_DRIVER
TARGET_RTOSCK_LINK_SCRIPT := $(LOCAL_PATH)/trustedcore_STB.ld
else
TARGET_RTOSCK_LINK_SCRIPT := $(LOCAL_PATH)/trustedcore.ld
endif

LOCAL_CFLAGS += -DTASK_ADDR=$(TRUSTEDCORE_TASK_BASE)
LOCAL_ASFLAGS += -DTASK_ADDR=$(TRUSTEDCORE_TASK_BASE)
################################################
## test config
#################################################
ifeq ($(SECURE_TESTSUITE),RTOSck_UT)
LOCAL_CFLAGS += -DTESTSUITE_RTOSck_UT
WITH_MONITOR_TEST := false
endif
ifeq ($(SECURE_TESTSUITE),RTOSck_PT)
LOCAL_CFLAGS += -DTESTSUITE_RTOSck_PT
endif
ifeq ($(SECURE_TESTSUITE),RTOSck_IT)
LOCAL_CFLAGS += -DTESTSUITE_RTOSck_IT
endif

WITH_DEBUG_EXTERN := false
ifeq ($(WITH_DEBUG_EXTERN), true)
LOCAL_CFLAGS += -DDEBUG_EXTERN
LOCAL_CFLAGS += -DDEBUG_SWITCH
endif
################################################
## include path
#################################################
SDK_DIR := $(LOCAL_PATH)/../../../../..
SOURCE_DIR=$(SDK_DIR)/source
MSP_DIR=${SOURCE_DIR}/msp
MSP_UNF_INCLUDE=${MSP_DIR}/include

PATH00 = $(LOCAL_PATH)/tzarch/include
ifeq ($(SECURE_TESTSUITE),RTOSck_UT)
PATH01 = $(LOCAL_PATH)/../testcode/include
PATH02 = $(LOCAL_PATH)/../testcode/iCunit
PATH03 = $(LOCAL_PATH)/../testcode/UT_OLD/Test_Common/
endif
PATH04 = $(LOCAL_PATH)/../include_kernel
PATH05 = ${LOCAL_PATH}/../include_kernel/config
PATH06 = ${LOCAL_PATH}/../include_kernel/ph
PATH07 = $(LOCAL_PATH)/../thirdparty/cipher_code \
	 $(LOCAL_PATH)/../thirdparty/cipher_code/sha \
	 $(LOCAL_PATH)/../thirdparty/cipher_code/rsa \
	 $(LOCAL_PATH)/../thirdparty/cipher_code/tee/include
PATH08 = $(LOCAL_PATH)/syscalls_ext
PATH_DRIVER_COMMON = $(LOCAL_PATH)/../TEE_ext/api/include
PATH09 = $(MSP_UNF_INCLUDE) 

#################################################
## include patch
#################################################
INCLUDE := \
$(PATH00) \
$(PATH01) \
$(PATH02) \
$(PATH03) \
$(PATH05) \
$(PATH04) \
$(PATH06) \
$(PATH08) \
$(PATH07) \
$(PATH09) \
$(PATH_DRIVER_COMMON) 

#################################################
## tz arch code
#################################################
TZARCH_SRCS = \
tzarch/tzinit/sre_reset_vector.S \
tzarch/monitor/monitor_api.S
#tzarch/monitor/secondary_monitor.S
#tzarch/monitor/monitor.S
INIT_SRCS = \
init/init_ext.c
CIPHER_SRCS = \
	../thirdparty/cipher_code/drv_cipher.c \
	../thirdparty/cipher_code/drv_cipher_intf.c \
	../thirdparty/cipher_code/hal_cipher.c \
	../thirdparty/cipher_code/rsa/drv_rsa.c \
	../thirdparty/cipher_code/rsa/drv_rsa_bignum.c \
	../thirdparty/cipher_code/rsa/drv_rsa_intf.c \
	../thirdparty/cipher_code/tee/src/crys_aes.c \
	../thirdparty/cipher_code/tee/src/crys_hmac.c \
	../thirdparty/cipher_code/tee/src/crys_rsa.c \
	../thirdparty/cipher_code/tee/src/crys_rsa_prim.c \
	../thirdparty/cipher_code/tee/src/crys_hash.c \
	../thirdparty/cipher_code/tee/src/crys_des.c \
	../thirdparty/cipher_code/tee/src/crys_rsa_kg.c \
	../thirdparty/cipher_code/tee/src/crys_rnd_rom.c \
	../thirdparty/cipher_code/tee/src/crys_common_math.c \
	../thirdparty/cipher_code/tee/src/crys_common_conv_endian.c \
	../thirdparty/cipher_code/tee/src/crys_cipher_common.c \
	../thirdparty/cipher_code/tee/src/crys_rsa_build.c \
	syscalls_ext/sre_syscallDispatch_ext.c

SECMEM_SRCS = \
        ../thirdparty/securemem_cfg/secure_mem_cfg.c

MMZ_SRCS = \
        ../thirdparty/mmz/media-mem.c \
        ../thirdparty/mmz/mmz_intf.c \
        ../thirdparty/mmz/mmz-user.c

ifeq ($(WITH_MONITOR_TEST), true)
TZARCH_SRCS += tzarch/monitor/monitor_test.c \
tzarch/monitor/monitor_test_asm.S
LOCAL_CFLAGS += -DMONITOR_TEST
INCLUDE += $(LOCAL_PATH)/../testcode/include
endif

#################################################
## test suite code
#################################################
ifeq ($(SECURE_TESTSUITE),RTOSck_UT)
TEST_SRC = \
../testcode/UT_OLD/Test_Common/app_data_loacl.c \
../testcode/UT_OLD/Test_Common/app_data_sbishared.c \
../testcode/UT_OLD/Test_Common/app_data_shared.c \
../testcode/UT_OLD/Test_Common/osTest.c \
../testcode/UT_OLD/Test_Common/SRE_AppInit.c \
../testcode/UT_OLD/Test_Common/testlink.o \
../testcode/iCunit/iCunit.c \
../testcode/UT_OLD/UT/ut_uni_hwi.c \
../testcode/UT_OLD/UT/ut_uni_timer.c \
../testcode/UT_OLD/UT/sre_dispatch_test.s \
../testcode/UT_OLD/UT/ut_sre_err.c \
../testcode/UT_OLD/UT/ut_srehunt.c \
../testcode/UT_OLD/UT/ut_sre_fsem.c \
../testcode/UT_OLD/UT/ut_sre_sem.c \
../testcode/UT_OLD/UT/ut_sre_msg.c \
../testcode/UT_OLD/UT/ut_sre_msg_init.c \
../testcode/UT_OLD/UT/ut_sre_msg_minor.c \
../testcode/UT_OLD/UT/ut_sre_swi.c \
../testcode/UT_OLD/UT/ut_sre_swi_init.c \
../testcode/UT_OLD/UT/ut_sre_swi_minor.c \
../testcode/UT_OLD/UT/ut_sre_task.c \
../testcode/UT_OLD/UT/ut_sre_task_init.c \
../testcode/UT_OLD/UT/ut_sre_task_minor.c \
../testcode/UT_OLD/UT/ut_sre_mem.c \
../testcode/UT_OLD/UT/ut_sre_mem_init.c \
../testcode/UT_OLD/UT/ut_sre_mem_minor.c \
../testcode/UT_OLD/UT/ut_sre_dynpoolmem.c \
../testcode/UT_OLD/UT/ut_sre_dynpoolmem_init.c \
../testcode/UT_OLD/UT/ut_sre_fscmem.c \
../testcode/UT_OLD/UT/ut_sre_fscmem_init.c \
../testcode/UT_OLD/UT/ut_uni_cachemmu.c
endif

#################################################
## trustedcore src
#################################################
TRUSTEDCORE_SRCS = \
$(TEST_SRC) \
$(TZARCH_SRCS)\
$(INIT_SRCS) \
$(CIPHER_SRCS) \
$(SECMEM_SRCS) \
$(MMZ_SRCS)

#################################################
## build script
#################################################
include $(LOCAL_PATH)/../trustedcore.mk

LOCAL_ARM_MODE := arm

LOCAL_CFLAGS += -O2 -g -W -Wall -fno-omit-frame-pointer

LOCAL_CFLAGS += -march=armv7-a

LOCAL_ASFLAGS += -march=armv7-a

LOCAL_C_INCLUDES := $(INCLUDE)

LOCAL_SRC_FILES := \
	$(TRUSTEDCORE_SRCS)

LOCAL_MODULE:= rtosck.img
LOCAL_MODULE_PATH := $(PRODUCT_OUT)

HAVE_TRUSTEDCORE_SRC_PATH := $(wildcard $(LOCAL_PATH)/../../trustedcore_src/Android.mk)

#ifneq ($(HAVE_TRUSTEDCORE_SRC_PATH),)
#LOCAL_STATIC_LIBRARIES := libtrustedcore
#endif

LOCAL_MODULE_TAGS := optional

#SYSTEM_STATIC_LIB_PATH = out//target/product/k3v2oem1/obj/STATIC_LIBRARIES
SYSTEM_STATIC_LIB_PATH = $(PRODUCT_OUT)/obj/STATIC_LIBRARIES

ifneq ($(HAVE_TRUSTEDCORE_SRC_PATH),)
TRUSTEDCORE_LIB_PATH = $(SYSTEM_STATIC_LIB_PATH)/libtrustedcore_intermediates/libtrustedcore.a
else
TRUSTEDCORE_LIB_PATH = $(LOCAL_PATH)/../release/trustedcore_lib/libtrustedcore.a
endif



include $(BUILD_RAW_EXECUTABLE)
$(LOCAL_BUILT_MODULE) : PRIVATE_LINK_SCRIPT := $(TARGET_RTOSCK_LINK_SCRIPT)
$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS := -Ttext $(TRUSTEDCORE_TEXT_BASE) -Map rtosck.map

$(LOCAL_BUILT_MODULE) : PRIVATE_RAW_EXECUTABLE_LDFLAGS += --whole-archive $(TRUSTEDCORE_LIB_PATH) --no-whole-archive

#ifeq ($(HAVE_TRUSTEDCORE_SRC_PATH),)
#$(LOCAL_BUILT_MODULE) :PRIVATE_ALL_STATIC_LIBRARIES := $(LOCAL_PATH)/trustedcore_lib/trustedcorelib.a
#endif

ifeq ($(strip $(WITH_CC_DRIVER)), true)
$(LOCAL_BUILT_MODULE) :PRIVATE_ALL_STATIC_LIBRARIES += $(LOCAL_PATH)/../thirdparty/ccdriver_lib/libdx_cc7.a
endif

#include $(call all-makefiles-under,$(LOCAL_PATH))
