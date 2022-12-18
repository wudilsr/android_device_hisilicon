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

TS_CAST         := sample_ts_cast
TS_CAST_OBJS    := ts_cast.o $(COMMON_FILES)

DVB_CAST        := sample_dvb_cast
DVB_CAST_OBJS   := dvb_cast.o $(COMMON_FILES)

TARGETS := $(TS_CAST)

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
TARGETS += $(DVB_CAST)
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(TARGETS)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(DVB_CAST): $(DVB_CAST_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(TS_CAST): $(TS_CAST_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(DVB_CAST) $(DVB_CAST_OBJS)
	-$(AT)rm -f $(TS_CAST) $(TS_CAST_OBJS)

install:

uninstall:
