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

ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFLAGS += -DHI_KEYLED_SUPPORT
endif


LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -lpthread -Wl,--end-group

APP_SRC = fbc_mosaic.c fbc_xswitch.c
APP = $(patsubst %.c,sample_%,$(APP_SRC))
OBJS = $(patsubst %.c,%.o,$(APP_SRC))

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)  

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

sample_%:%.o $(COMMON_FILES)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
