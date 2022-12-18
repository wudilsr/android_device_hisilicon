
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
###########################################################
ROOT      =$(TVP_DIR)/trustedcore/trustedcore_kernel

ifeq ($(strip $(WITH_STB_CIPHER_DRIVER)), true)
LOCAL_CFLAGS += -DSTB_CIPHER_DRIVER
TARGET_RTOSCK_LINK_SCRIPT := $(ROOT)/trustedcore_STB.ld
else
TARGET_RTOSCK_LINK_SCRIPT := $(ROOT)/trustedcore.ld
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

ifeq ($(CONFIG_MEM_LAYOUT),1G)
LOCAL_CFLAGS += -DCONFIG_SYS_MEM_1G
endif

ifeq ($(CONFIG_MEM_LAYOUT),2G)
LOCAL_CFLAGS += -DCONFIG_SYS_MEM_2G
endif

#SDK_DIR := $(ROOT)/../../../../..
#SOURCE_DIR=$(SDK_DIR)/source
#MSP_DIR=${SOURCE_DIR}/msp
#MSP_UNF_INCLUDE=${MSP_DIR}/include

################################################
## include path
#################################################
PATH00 = -I$(ROOT)/tzarch/include -I$(ROOT)/../include
ifeq ($(SECURE_TESTSUITE),RTOSck_UT)
PATH01 = -I$(ROOT)/../testcode/include
PATH02 = -I$(ROOT)/../testcode/iCunit
PATH03 = -I$(ROOT)/../testcode/UT_OLD/Test_Common/
endif
PATH04 = -I$(ROOT)/../include_kernel
PATH05 = -I$(ROOT)/../include_kernel/config
PATH06 = -I$(ROOT)/../include_kernel/ph
PATH07 = -I$(ROOT)/../thirdparty/cipher_code \
	   $(ROOT)/../thirdparty/cipher_code/rsa \
	   $(ROOT)/../thirdparty/cipher_code/tee/include 
PATH08 = -I$(ROOT)/syscalls_ext
PATH09 = -I$(MSP_UNF_INCLUDE) \
         -I$(ROOT)/../thirdparty/cipher_code/rsa \
         -I$(ROOT)/../thirdparty/cipher_code/tee/include
PATH10 = -I$(ROOT)/../thirdparty/mmz
PATH11 = -I$(ROOT)/../TEE_ext/mmz
PATH_VFMW = -I$(ROOT)/../thirdparty/vfmw_code
#COMMON_DRV_INCLUDE ?= -I$(ROOT)/../../../../../common/drv/include
ifdef COMMON_DRV_INCLUDE
PATH_SDK_COMMON = -I$(COMMON_DRV_INCLUDE)
else
PATH_SDK_COMMON = -I$(ROOT)/../../../../../common/drv/include
endif

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
$(PATH07) \
$(PATH08) \
$(PATH09) \
$(PATH010) \
$(PATH011) \
$(PATH_VFMW)\
$(PATH_SDK_COMMON)

#################################################
## tz arch code
#################################################
TZARCH_SRCS = \
$(ROOT)/tzarch/tzinit/sre_reset_vector.o \
$(ROOT)/tzarch/monitor/monitor_api.o
#tzarch/monitor/secondary_monitor.o
#tzarch/monitor/monitor.o
INIT_SRCS = \
$(ROOT)/init/init_ext.o
#init/securemem_cfg/secure_mem_cfg.o

SYSCALL_SRCS = $(ROOT)/syscalls_ext/sre_syscallDispatch_ext.o

CIPHER_SRCS = \
	$(ROOT)/../thirdparty/cipher_code/drv_cipher.o \
	$(ROOT)/../thirdparty/cipher_code/drv_cipher_intf.o \
	$(ROOT)/../thirdparty/cipher_code/hal_cipher.o \
	$(ROOT)/../thirdparty/cipher_code/rsa/drv_rsa.o \
	$(ROOT)/../thirdparty/cipher_code/rsa/drv_rsa_bignum.o \
	$(ROOT)/../thirdparty/cipher_code/rsa/drv_rsa_intf.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_aes.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_hmac.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_rsa.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_rsa_prim.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_hash.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_des.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_rsa_kg.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_rnd_rom.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_common_math.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_common_conv_endian.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_cipher_common.o \
	$(ROOT)/../thirdparty/cipher_code/tee/src/crys_rsa_build.o 	

SECMEM_SRCS = \
        $(ROOT)/../thirdparty/securemem_cfg/secure_mem_cfg.o
MMZ_SRCS = \
        $(ROOT)/../thirdparty/mmz/media-mem.o \
        $(ROOT)/../thirdparty/mmz/mmz_intf.o \
        $(ROOT)/../thirdparty/mmz/mmz-user.o

include $(ROOT)/../thirdparty/vfmw_code/vfmw.cfg
#VFMW_SRCS = $(vfmw_obj_list)

DEBUG_SRCS = $(ROOT)/../thirdparty/debug.o

ifeq ($(WITH_MONITOR_TEST), true)
TZARCH_SRCS += $(ROOT)/tzarch/monitor/monitor_test.o \
$(ROOT)/tzarch/monitor/monitor_test_asm.o
LOCAL_CFLAGS += -DMONITOR_TEST
INCLUDE += $(ROOT)/../testcode/include
endif

#################################################
## test suite code
#################################################
ifeq ($(SECURE_TESTSUITE),RTOSck_UT)
TEST_SRC = \
$(ROOT)/../testcode/UT_OLD/Test_Common/app_data_loacl.o \
$(ROOT)/../testcode/UT_OLD/Test_Common/app_data_sbishared.o \
$(ROOT)/../testcode/UT_OLD/Test_Common/app_data_shared.o \
$(ROOT)/../testcode/UT_OLD/Test_Common/osTest.o \
$(ROOT)/../testcode/UT_OLD/Test_Common/SRE_AppInit.o \
$(ROOT)/../testcode/UT_OLD/Test_Common/testlink.o \
$(ROOT)/../testcode/iCunit/iCunit.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_uni_hwi.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_uni_timer.o \
$(ROOT)/../testcode/UT_OLD/UT/sre_dispatch_test.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_err.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_srehunt.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_fsem.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_sem.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_msg.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_msg_init.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_msg_minor.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_swi.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_swi_init.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_swi_minor.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_task.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_task_init.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_task_minor.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_mem.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_mem_init.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_mem_minor.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_dynpoolmem.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_dynpoolmem_init.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_fscmem.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_sre_fscmem_init.o \
$(ROOT)/../testcode/UT_OLD/UT/ut_uni_cachemmu.o
endif

#################################################
## trustedcore src
#################################################
TRUSTEDCORE_SRCS = \
$(TEST_SRC) \
$(TZARCH_SRCS) \
$(INIT_SRCS) \
$(SYSCALL_SRCS) \
$(SECMEM_SRCS) \
$(MMZ_SRCS) \
$(CIPHER_SRCS) \
$(DEBUG_SRCS)
#$(VFMW_SRCS)


#################################################
## build script
#################################################


LOCAL_CFLAGS += -O2 -g -W -Wall -fno-omit-frame-pointer

LOCAL_CFLAGS += -march=armv7-a

LOCAL_ASFLAGS += -march=armv7-a


LOCAL_SRC_FILES := \
	$(TRUSTEDCORE_SRCS)

LOCAL_MODULE_ELF:= $(OUT)/rtosck.img.elf
LOCAL_MODULE:= $(OUT)/rtosck.img

TRUSTEDCORE_LIB_PATH = $(TRUSTEDCORE_DIR)/release/trustedcore_lib/libtrustedcore.a \
                       $(TRUSTEDCORE_DIR)/thirdparty/vfmw_code/libsec_vfmw.a



##########################################################
# project path definition
##########################################################
ALL_OBJ = $(TRUSTEDCORE_SRCS)
LOCAL_OUT = $(OUT)/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))


CFLAGS += $(INCLUDE)
CFLAGS += $(LOCAL_CFLAGS)

LDFLAGS := --script $(TARGET_RTOSCK_LINK_SCRIPT) \
		-Ttext $(TRUSTEDCORE_TEXT_BASE) -Map $(LOCAL_OUT)/rtosck.map \
		--whole-archive $(TRUSTEDCORE_LIB_PATH) --no-whole-archive

##########################################################
# build rtosck.img
##########################################################
.PHONY : all prepare clean

all : prepare $(ALL_OBJ)
	@echo $(ALL_OBJ)
	$(LD2) $(LDFLAGS) -o $(LOCAL_MODULE_ELF) $(ALL_OUT_OBJ) `$(CC2) -mthumb-interwork -print-libgcc-file-name`
	$(OBJCOPY2) -O binary $(LOCAL_MODULE_ELF) $(LOCAL_MODULE)
	@echo "Make $(LOCAL_MODULE) Success!"

prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))

clean:
	$(RM) $(LOCAL_MODULE) $(LOCAL_MODULE_ELF) $(ALL_OUT_OBJ) $(ALL_OBJ)

%.o : %.c
	$(CC2) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

%.o : %.S
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

%.o : %.s
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

