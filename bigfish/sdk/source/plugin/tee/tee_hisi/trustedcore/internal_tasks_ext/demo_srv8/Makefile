
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
###########################################################
ROOT      =.



LOCAL_CFLAGS := -O2 -W -Wall -fno-omit-frame-pointer

LOCAL_C_INCLUDES := \
    -I$(ROOT)/../../include \
    -I$(ROOT)/../QA-TZService/inc \
    -I$(ROOT)/../QA-TZService/inc_common \
    -I$(ROOT)/../../../include/TZInfra_API \
    -I$(ROOT)/../../../include/TZInfra_API/Tools \
    -I$(ROOT)/../../../include/TZInfra_API/VOS_API

LOCAL_SRC_FILES :=  $(ROOT)/demo_task8.o

LOCAL_MODULE:= $(OUT)/demo_task8.elf




TRUSTEDCORE_ELF_MAIN_ENTRY_PATH :=$(ROOT)/../elf_main_entry.o

ALL_OBJ = $(LOCAL_SRC_FILES)

LOCAL_OUT = $(OUT)/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))

CFLAGS += $(LOCAL_CFLAGS) $(LOCAL_C_INCLUDES)
LDFLAGS += -r -d --strip-debug --whole-archive $(TRUSTEDCORE_ELF_MAIN_ENTRY_PATH) --no-whole-archive


##########################################################
# build demo_task1
##########################################################
.PHONY : all prepare clean
all: prepare $(ALL_OBJ)
	@echo $(ALL_OUT_OBJ)
	$(LD1) $(LDFLAGS) -o $(LOCAL_MODULE) $(ALL_OUT_OBJ) `$(CC1) -mthumb-interwork -print-libgcc-file-name`
	@echo "Make $(LOCAL_MODULE) Success!"
prepare:
	$(MKDIR) $(foreach VAR,$(ALL_OUT_OBJ),$(dir $(VAR)))
clean:
	$(RM) $(LOCAL_MODULE) $(ALL_OUT_OBJ) $(ALL_OBJ)

%.o : %.c
	$(CC1) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

