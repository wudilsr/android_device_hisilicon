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

CFLAGS +=   -I$(SDK_INC_DIR)        \
            -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

APP     := dvb_demux
APP2    := filter_sample
APP3    := sample_demux_record

OBJS    := dvb_demux_sample.o $(COMMON_FILES)
OBJS2   := filter_sample.o $(COMMON_FILES)
OBJS3   := dvb_demux_record.o $(COMMON_FILES)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(APP) $(APP2) $(APP3)

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(APP2): $(OBJS2)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(APP3): $(OBJS3)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(OBJS2)
	-$(AT)rm -f $(OBJS3)
	-$(AT)rm -f $(APP)
	-$(AT)rm -f $(APP2)
	-$(AT)rm -f $(APP3)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

install:

uninstall:

