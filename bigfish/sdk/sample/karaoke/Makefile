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
CFLAGS += -I$(SDK_INC_DIR) \
    -I$(SAMPLE_DIR)/common \
	-I$(SDK_DIR)/pub/include

LIBPATH = \
	-L$(SDK_STATIC_LIB_DIR) \
	-L$(SDK_SHARE_LIB_DIR) \
	-L$(SDK_DIR)/pub/lib/share \
	-L$(SDK_DIR)/pub/lib/share/alsa_bluez

LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -lhi_karaoke -lasound -Wl,--end-group

APP = sample_karaoke
OBJS = karaoke.o $(COMMON_FILES)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
