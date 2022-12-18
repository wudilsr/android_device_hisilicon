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

IP_MOSAIC       := sample_ip_mosaic
IP_MOSAIC_OBJS  := ip_mosaic.o $(COMMON_FILES)

TS_MOSAIC       := sample_ts_mosaic
TS_MOSAIC_OBJS  := ts_mosaic.o $(COMMON_FILES)

DVB_MOSAIC      := sample_dvb_mosaic
DVB_MOSAIC_OBJS := dvb_mosaic.o $(COMMON_FILES)

TARGETS := $(IP_MOSAIC) $(TS_MOSAIC)

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
TARGETS += $(DVB_MOSAIC)
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(TARGETS)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(DVB_MOSAIC): $(DVB_MOSAIC_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(IP_MOSAIC): $(IP_MOSAIC_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(TS_MOSAIC): $(TS_MOSAIC_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	$(AT)rm -f $(IP_MOSAIC) $(IP_MOSAIC_OBJS)
	$(AT)rm -f $(TS_MOSAIC) $(TS_MOSAIC_OBJS)
	$(AT)rm -f $(DVB_MOSAIC) $(DVB_MOSAIC_OBJS)

install:

uninstall:
