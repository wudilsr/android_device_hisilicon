#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

include $(SDK_DIR)/sample/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS  += -I$(SDK_DIR)/source/msp/api/omx/include
CFLAGS  += -I$(SDK_DIR)/source/common/include 

ifeq ($(CFG_HI_TVP_SUPPORT), y)
CFLAGS += -DHI_TVP_SUPPORT
CFLAGS += -I$(TVP_DIR)/libteec/inc/
HI_TVP_LIBS += -lteec
endif

LIBPATH  = -L$(SDK_DIR)/pub/lib/extern
LIBPATH += -L${SDK_DIR}/pub/lib/share

LIB  = -Wl,--start-group -lpthread -ldl -lOMX_Core  $(HI_TVP_LIBS)  -lhi_common -Wl,--end-group

APP  = sample_omxvdec
OBJS = sample_omxvdec.o sample_queue.o sample_tidx.o

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(APP): ${OBJS}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

clean:
	-$(AT)rm -f ${OBJS}
	-$(AT)rm -f $(APP)
	
install:

uninstall:
