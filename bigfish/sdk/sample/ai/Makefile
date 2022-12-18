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

APP = sample_ai sample_ai_aenc sample_ai_ao sample_ai_ao_tianlai
OBJS = ai.o ai_aenc.o ai_ao.o ai_ao_tianlai.o $(COMMON_FILES) 

ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
APP += sample_ai_ao_slic
OBJS += ai_ao_slic.o
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

sample_ai: ai.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_ai_aenc: ai_aenc.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_ai_ao: ai_ao.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
sample_ai_ao_tianlai: ai_ao_tianlai.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
	
ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
sample_ai_ao_slic: ai_ao_slic.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
endif	
clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
