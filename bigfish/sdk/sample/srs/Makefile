#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../../
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_SAMPLE_CFLAGS)
CFLAGS += -I$(SDK_INC_DIR) -I$(MSP_DRV_INCLUDE) -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) --end-group 

APP = sample_srsaudioplay sample_srsmaster sample_srsaiao sample_baseaiao sample_srs_base_aiao
OBJS = srsaudioplay.o srsmaster.o srsaiao.o baseaiao.o srs_base_aiao.o$(COMMON_FILES)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

sample_srsaudioplay: srsaudioplay.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
	
sample_srsmaster: srsmaster.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_srsaiao: srsaiao.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_baseaiao: baseaiao.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

sample_srs_base_aiao: srs_base_aiao.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
