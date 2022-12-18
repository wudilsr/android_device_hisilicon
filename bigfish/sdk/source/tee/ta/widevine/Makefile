
###########################################################
# platform definition
###########################################################
ROOT      =.
LOCAL_CFLAGS =
LOCAL_ASFLAGS =
LOCAL_CFLAGS += ${TRUSTEDCORE_LOCAL_CFLAGS}
LOCAL_ASFLAGS += ${TRUSTEDCORE_LOCAL_ASFLAGS}

LOCAL_CFLAGS += -O2 -fstrict-aliasing -funswitch-loops -fno-short-enums -W -Wall -mfloat-abi=softfp -mfpu=neon -fno-omit-frame-pointer -fstack-protector-all -Wstack-protector -MD 

LOCAL_C_INCLUDES := \
    -I$(HI_TEE_OS_DIR)/trustedcore/include/TEE \
    -I$(HI_TEE_OS_DIR)/trustedcore/include/kernel \
    -I$(HI_TEE_OS_DIR)/trustedcore/platform/${PLATFORM_DIR_NAME}/TEE_ext \
    -I$(HI_TEE_API_DIR)/include \
    -I$(HI_TEE_API_DIR)/mem/include \
    -I$(ROOT)/../../../../source/common/include \
    -I$(ROOT)/../../../../source/common/api/include \
    -I$(ROOT)/../../../../source/msp/include \
    -I$(ROOT)/provision \
    -I$(ROOT)/task_modular_wv/crypto \
    -I$(ROOT)/task_modular_wv/ \
    -I$(ROOT)/task_widevine \
    -I$(ROOT)/task_widevine/hal \
    -I$(ROOT)/hal/include \
    -I$(ROOT)/hal/stb/tee \
    -I$(ROOT)

LOCAL_SRC_FILES :=  $(ROOT)/task_widevine_tzserver.o \
			$(ROOT)/task_widevine/task_widevine.o \
			$(ROOT)/task_widevine/task_wv_tzserver.o \
			$(ROOT)/task_widevine/widevine_hal.o \
			$(ROOT)/task_widevine/hal/hi_cipher.o \
			$(ROOT)/task_widevine/hal/wvcrc.o \
			$(ROOT)/task_modular_wv/task_modular_wv_tzserver.o \
			$(ROOT)/task_modular_wv/hi_crypto.o \
			$(ROOT)/task_modular_wv/hi_oem_engine_mock.o \
			$(ROOT)/task_modular_wv/hi_oem_keybox_mock.o \
			$(ROOT)/task_modular_wv/hi_oem_key_mock.o \
			$(ROOT)/task_modular_wv/hi_oem_mock.o \
			$(ROOT)/task_modular_wv/hi_oem_usage_table_mock.o \
			$(ROOT)/task_modular_wv/hi_oem_wvcrc.o \
			$(ROOT)/task_modular_wv/hi_wv_util.o \
			$(ROOT)/task_modular_wv/crypto/aes.o \
			$(ROOT)/task_modular_wv/crypto/asn1parse.o \
			$(ROOT)/task_modular_wv/crypto/bignum.o \
			$(ROOT)/task_modular_wv/crypto/cmac.o \
			$(ROOT)/task_modular_wv/crypto/md.o \
			$(ROOT)/task_modular_wv/crypto/md_wrap.o \
			$(ROOT)/task_modular_wv/crypto/oid.o \
			$(ROOT)/task_modular_wv/crypto/pkparse.o \
			$(ROOT)/task_modular_wv/crypto/rsa.o \
			$(ROOT)/task_modular_wv/crypto/sha1.o \
			$(ROOT)/task_modular_wv/crypto/sha256.o \
			$(ROOT)/provision/widevine_provision.o \
			$(ROOT)/provision/tea_decrypt.o \
			$(ROOT)/hal/stb/tee/hi_halwvcipher.o \
			$(ROOT)/hal/stb/tee/hi_halwvotp.o

LOCAL_MODULE:= $(OUT)/task_wv_server.elf


TRUSTEDCORE_ELF_MAIN_ENTRY_PATH := $(TRUSTEDCORE_DIR)/release/internal_tasks/elf_main_entry.o

ALL_OBJ = $(LOCAL_SRC_FILES)
LOCAL_OUT = $(OUT)/internal_tasks/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))

CFLAGS += $(LOCAL_CFLAGS) $(LOCAL_C_INCLUDES) $(TRUSTEDCORE_LOCAL_CFLAGS)
LDFLAGS += -r -d --strip-debug --whole-archive  -T $(TA_LINK_SCRIPT) $(TRUSTEDCORE_ELF_MAIN_ENTRY_PATH) --no-whole-archive


##########################################################
# build demo_task1
##########################################################
.PHONY : all prepare clean
ifeq ($(strip $(CONFIG_TRUSTEDCORE_RELEASE)), )
all: prepare $(ALL_OBJ)
	@echo $(ALL_OUT_OBJ)
	$(LD1) $(LDFLAGS) -o $(LOCAL_MODULE) $(ALL_OUT_OBJ) `$(CC1) -mthumb-interwork -print-libgcc-file-name`
	@echo "Make $(LOCAL_MODULE) Success!"
else
all:
	cp $(TRUSTEDCORE_RELEASE_DIR)/$(PLATFORM_DIR_NAME)/$(CFG_HI_TVP_MEM_LAYOUT)/$(notdir $(LOCAL_MODULE)) $(LOCAL_MODULE)
	@echo "Make $(LOCAL_MODULE) Success!"
endif
	
prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))
clean:
	$(RM) $(LOCAL_MODULE) $(ALL_OUT_OBJ) $(ALL_OBJ)

%.o : %.c | prepare
	$(CC1) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

