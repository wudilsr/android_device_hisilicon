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

DVB_PIP         := sample_dvb_pip
DVB_PIP_OBJS    := sample_dvb_pip.o $(COMMON_FILES)

TS_PIP          := sample_ts_pip
TS_PIP_OBJS     := sample_ts_pip.o $(COMMON_FILES)

TARGETS := $(TS_PIP)

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
TARGETS += $(DVB_PIP)
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(TARGETS)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(DVB_PIP): $(DVB_PIP_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(TS_PIP): $(TS_PIP_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(TS_PIP) $(TS_PIP_OBJS)
	-$(AT)rm -f $(DVB_PIP) $(DVB_PIP_OBJS)

install:

uninstall:
