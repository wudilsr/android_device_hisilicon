#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)
CFLAGS += -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

APP = sample_sif sample_switch sample_sif_i2s_mixer
OBJS = sif_aiao.o adec_ai_sif_switch.o sif_aiao_mixer.o $(COMMON_FILES)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

sample_sif: sif_aiao.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_switch: adec_ai_sif_switch.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_sif_i2s_mixer: sif_aiao_mixer.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
