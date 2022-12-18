#===============================================================================
# export variable
#===============================================================================
SDK_DIR := $(CURDIR)/../..

include $(SDK_DIR)/cfg.mak
include $(SDK_DIR)/sample/base.mak

#===============================================================================
# local variable
#===============================================================================
CFLAGS  += -I$(SDK_DIR)/source/msp/api/omx/include
CFLAGS  += -I$(SDK_DIR)/source/common/include 

LIBPATH  = -L$(SDK_DIR)/pub/lib/extern
LIBPATH += -L${SDK_DIR}/pub/lib/share

LIB = -Wl,--start-group -lpthread -ldl -lOMX_Core -lOMX.hisi.video.encoder -lhi_common  -lrt -lm -Wl,--end-group
		  
APP = sample_omxvenc           
OBJS = omx_venc_test.o queue.o

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
