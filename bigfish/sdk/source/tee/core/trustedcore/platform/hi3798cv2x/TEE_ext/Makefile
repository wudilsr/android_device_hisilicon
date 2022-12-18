
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
###########################################################
ROOT      =.
LOCAL_CFLAGS =
LOCAL_ASFLAGS =
LOCAL_CFLAGS += ${TRUSTEDCORE_LOCAL_CFLAGS}
LOCAL_ASFLAGS += ${TRUSTEDCORE_LOCAL_ASFLAGS}

ifeq ($(WITH_TUI_SUPPORT),true)
LOCAL_CFLAGS += -DTEE_SUPPORT_TUI
ifeq ($(strip $(TRUSTEDCORE_ASFLAG_SET)), true)
LOCAL_ASFLAGS += -DTEE_SUPPORT_TUI
endif
endif

INCLUDE :=  -I$(ROOT) \
            -I$(TRUSTEDCORE_DIR)/include/TEE \
            -I$(TRUSTEDCORE_DIR)/include/kernel \
            -I$(TRUSTEDCORE_DIR)/include/TEE/tui \
            -I$(ROOT)/../trustedcore_kernel/syscalls_ext

#################################################
## export symbol
#################################################
SYMBOL_SRC = \
	tee_symbol_ext.o
SYSCALLS_EXT_SRC = \
	sre_syscalls_ext.o
TEE_CONFIG_SRC= \
	tee_config.o
TEE_RPMB_EXT_SRC = \
        tee_rpmb_ext.o
TEE_STD_PRINTF_SRC = \
		vsprintf.o
		
TEE_EXT_SRC = \
	asm_mem/memmove.o \
	asm_mem/memcpy.o \
	tee_external_api.o

LIB_SRCS = \
$(SYMBOL_SRC) \
$(SYSCALLS_EXT_SRC) \
$(TEE_CONFIG_SRC) \
$(TEE_RPMB_EXT_SRC) \
$(TEE_STD_PRINTF_SRC) \
$(TEE_EXT_SRC)

INCLUDE += -I$(HI_TEE_API_DIR)/include
INCLUDE += -I$(HI_TEE_DRV_DIR)/include
INCLUDE += -I$(HI_TEE_API_DIR)/mem/include
INCLUDE += -I$(HI_TEE_DRV_DIR)/cipher
INCLUDE += -I$(HI_TEE_DRV_DIR)/cipher/rsa
INCLUDE += -I$(HI_TEE_DRV_DIR)/cipher/tee/include
INCLUDE += -I$(HI_TEE_DRV_DIR)/timer
INCLUDE += -I$(HI_TEE_API_DIR)/hdmi

ifeq ($(strip $(WITH_HISI_CIPHER)), true)
LIB_SRCS += $(HI_TEE_API_DIR)/cipher/hi_tee_cipher.o
endif

ifeq ($(WITH_HISI_VDP), true)
INCLUDE += -I$(HI_TEE_DRV_DIR)/vdp
LIB_SRCS += \
	$(HI_TEE_API_DIR)/vdp/hi_tee_vdp.o 
endif

ifeq ($(WITH_HISI_SEC_MMZ), true)
LIB_SRCS += $(HI_TEE_API_DIR)/mem/hi_tee_mmz.o 
endif

ifeq ($(WITH_HISI_SMMU), true)
LIB_SRCS += $(HI_TEE_API_DIR)/mem/hi_tee_mem.o 
endif


ifeq ($(WITH_HISI_SEC_HDMI), true)
LIB_SRCS += \
	$(HI_TEE_API_DIR)/hdmi/hi_tee_hdmi.o \
	$(HI_TEE_API_DIR)/hdmi/tee_hdmi.o

endif

ifeq ($(strip $(WITH_HISI_DMX)), true)
INCLUDE += -I$(HI_TEE_API_DIR)/demux -I$(HI_TEE_DRV_DIR)/demux
LIB_SRCS += \
        $(HI_TEE_API_DIR)/demux/tee_descrambler.o \
        $(HI_TEE_API_DIR)/demux/tee_scrambler.o \
        $(HI_TEE_API_DIR)/demux/tee_demux_utils.o
endif

ifeq ($(strip $(WITH_HISI_PVR)), true)
INCLUDE += -I$(HI_TEE_DRV_DIR)/pvr
INCLUDE += -I$(HI_TEE_API_DIR)/pvr
LIB_SRCS += \
        $(HI_TEE_API_DIR)/pvr/tee_pvr_utils.o 
endif
ifeq ($(WITH_HISI_OTP), true)
LIB_SRCS += $(HI_TEE_API_DIR)/otp/hi_tee_otp.o
endif

ifeq ($(WITH_HISI_ADVCA), true)
LIB_SRCS += $(HI_TEE_API_DIR)/advca/hi_tee_advca.o
endif
GLOBALTASK_TEXT_BASE = 0

#LOCAL_CFLAGS += -O2 -g -fPIC
LOCAL_CFLAGS += -O2 -fPIC
#LOCAL_CFLAGS += -O2 -g -W -Wall
LOCAL_CFLAGS += -march=armv7-a

LOCAL_C_INCLUDES := $(INCLUDE)
LOCAL_SRC_FILES := 	$(LIB_SRCS)

#################################################
## import libs
#################################################
TARGET_GLOBALTASK_LINK_SCRIPT := $(ROOT)/link.ld
GLOBALTASK_LIB_PATH = $(TRUSTEDCORE_DIR)/release/internal_tasks/libtee.a
GLOBALTASK_TUI_PATH += $(TRUSTEDCORE_DIR)/release/internal_tasks/libtui.a
GLOBALTASK_O = $(TRUSTEDCORE_DIR)/release/internal_tasks/global_task.o



#include $(TRUSTEDCORE_BUILD_RAW_EXECUTABLE)
# add for enum size may different in different toolchain
LOCAL_CFLAGS += -fno-short-enums -fno-exceptions -fno-unwind-tables
LOCAL_ASFLAGS += -fno-short-enums -fno-exceptions -fno-unwind-tables


CFLAGS += $(LOCAL_C_INCLUDES)
CFLAGS += $(LOCAL_CFLAGS)
#LDFLAGS += $(LOCAL_LDFLAGS)

LOCAL_MODULE_ELF:= $(OUT)/globaltask.img.elf
LOCAL_MODULE:= $(OUT)/globaltask.img


##########################################################
# project path definition
##########################################################
ALL_OBJ = $(LOCAL_SRC_FILES)
LOCAL_OUT = $(OUT)/platform/$(PLATFORM_DIR_NAME)/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))

LDFLAGS := --script $(TARGET_GLOBALTASK_LINK_SCRIPT) \
		-pie --section-start .globaltask=$(GLOBALTASK_TEXT_BASE) \
		-Map $(LOCAL_OUT)/globaltask.map

ifeq ($(WITH_TUI_SUPPORT),true)
LDFLAGS += --whole-archive $(GLOBALTASK_O) $(GLOBALTASK_LIB_PATH) $(GLOBALTASK_TUI_PATH) --no-whole-archive
else
LDFLAGS += --whole-archive $(GLOBALTASK_O) $(GLOBALTASK_LIB_PATH) --no-whole-archive
endif

##########################################################
# build globaltask.img
##########################################################
.PHONY : all prepare clean
all: $(ALL_OBJ)
	@echo $(ALL_OBJ)
	$(LD2) $(LDFLAGS) -o $(LOCAL_MODULE_ELF) $(ALL_OUT_OBJ) `$(CC2) -mthumb-interwork -print-libgcc-file-name`
	$(OBJCOPY2) -O binary $(LOCAL_MODULE_ELF) $(LOCAL_MODULE)
	@echo "Make $(LOCAL_MODULE) Success!"

$(ALL_OBJ): prepare

prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))

clean:
	$(RM) -rf $(LOCAL_MODULE) $(LOCAL_MODULE_ELF) $(ALL_OUT_OBJ) $(dir $(ALL_OUT_OBJ)) $(ALL_OBJ) $(LOCAL_OUT)/globaltask.map

%.o : %.c | prepare
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

%.o : %.S | prepare
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

%.o : %.s | prepare
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@



