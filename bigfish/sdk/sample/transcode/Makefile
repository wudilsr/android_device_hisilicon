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

TS_TRANSCODE        := sample_ts_transcode
TS_TRANSCODE_OBJS   := ts_transcode.o $(COMMON_FILES)

DVB_TRANSCODE       := sample_dvb_transcode
DVB_TRANSCODE_OBJS  := dvb_transcode.o $(COMMON_FILES)

TARGETS := $(TS_TRANSCODE)

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
TARGETS += $(DVB_TRANSCODE)
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(TARGETS)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(DVB_TRANSCODE): $(DVB_TRANSCODE_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(TS_TRANSCODE): $(TS_TRANSCODE_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(TS_TRANSCODE) $(TS_TRANSCODE_OBJS)
	-$(AT)rm -f $(DVB_TRANSCODE) $(DVB_TRANSCODE_OBJS) 

install:

uninstall:
