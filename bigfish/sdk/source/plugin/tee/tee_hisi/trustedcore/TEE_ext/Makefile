
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
###########################################################
ROOT      =.



################################################
## cd driver config
#################################################
ifeq ($(strip $(WITH_STB_CIPHER_DRIVER)),true)
LOCAL_CFLAGS += -DSTB_CIPHER_DRIVER
endif

PATH01 = -I${ROOT}/../include
PATH02 = -I${ROOT}/../include_tee_ext/libc
PATH03 = -I${ROOT}/../include_tee_ext/tee
PATH04 = -I${ROOT}/../include_tee_ext/tee_initlib
PATH05 = -I${ROOT}/../include_kernel
PATH06 = -I${ROOT}/../thirdparty/cipher_code -I${ROOT}/api/cipher -I${ROOT}/api/include -I$(MSP_UNF_INCLUDE)
PATH07 = -I${ROOT}/../include/TZInfra_API
PATH08 = -I${ROOT}/../include/TZInfra_API/Tools
PATH09 = -I${ROOT}/../include/TZInfra_API/VOS_API
PATH10 = -I${ROOT}/../include_kernel/config
PATH11 = -I${ROOT}/../include_kernel/ph
PATH12 = -I$(ROOT)/../trustedcore_kernel/syscalls_ext
PATH13 = -I$(ROOT)/../thirdparty/cipher_code \
         -I$(ROOT)/../thirdparty/cipher_code/sha \
         -I$(ROOT)/../thirdparty/cipher_code/rsa \
         -I$(ROOT)/../thirdparty/cipher_code/tee/include

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
	$(ROOT)/symbol/tee_symbol.o
#################################################
## TZInfra Api
#################################################
DZ_TZINFRA_API = \
    $(ROOT)/TZInfra_API/DxTzServiceAPI.o \
    $(ROOT)/TZInfra_API/DxTzServiceCryptoAPI.o \
    $(ROOT)/TZInfra_API/DxTzServiceSfs.o \
    $(ROOT)/TZInfra_API/stub.o
SYSCALLS_EXT_SRC = \
	$(ROOT)/../trustedcore_kernel/syscalls_ext/sre_syscalls_ext.o

MMZ_SRC = \
	mmz/hi_mmz.o
CIPHER_SRC = \
	api/cipher/tz_unf_cipher.o

LIB_SRCS = \
$(SYMBOL_SRC) \
$(DZ_TZINFRA_API) \
$(MMZ_SRC) \
$(CIPHER_SRC) \
$(SYSCALLS_EXT_SRC)

#LOCAL_ARM_MODE := arm

GLOBALTASK_TEXT_BASE = 0

LOCAL_CFLAGS += -O2 -g -fPIC -fno-omit-frame-pointer
#LOCAL_CFLAGS += -O2 -g -W -Wall
LOCAL_CFLAGS += -march=armv7-a

LOCAL_MODULE_ELF:= $(OUT)/globaltask.img.elf
LOCAL_MODULE:= $(OUT)/globaltask.img

TARGET_GLOBALTASK_LINK_SCRIPT := $(ROOT)/link.ld


GLOBALTASK_LIB_PATH = $(TRUSTEDCORE_DIR)/release/internal_tasks/libtee.a
GLOBALTASK_O = $(TRUSTEDCORE_DIR)/release/internal_tasks/global_task.o


##########################################################
# project path definition
##########################################################
ALL_OBJ = $(LIB_SRCS)
LOCAL_OUT = $(OUT)/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))

CFLAGS += $(INCLUDE)
CFLAGS += $(LOCAL_CFLAGS)

LDFLAGS := --script $(TARGET_GLOBALTASK_LINK_SCRIPT) \
		-pie --section-start .globaltask=$(GLOBALTASK_TEXT_BASE)  \
		-Map $(LOCAL_OUT)/globaltask.map --whole-archive $(GLOBALTASK_O) $(GLOBALTASK_LIB_PATH) --no-whole-archive



##########################################################
# build globaltask.img
##########################################################
.PHONY : all prepare clean

all:prepare $(ALL_OBJ)
	@echo $(ALL_OBJ)
	$(LD2) $(LDFLAGS) -o $(LOCAL_MODULE_ELF) $(ALL_OUT_OBJ) `$(CC2) -mthumb-interwork -print-libgcc-file-name`
	$(OBJCOPY2) -O binary $(LOCAL_MODULE_ELF) $(LOCAL_MODULE)
	@echo "Make $(LOCAL_MODULE) Success!"

prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))
clean:
	$(RM) -rf $(LOCAL_MODULE) $(LOCAL_MODULE_ELF) $(ALL_OUT_OBJ) $(dir $(ALL_OUT_OBJ)) $(ALL_OBJ) $(LOCAL_OUT)/globaltask.map

%.o : %.c
	$(CC2) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

%.o : %.S
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

%.o : %.s
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@



