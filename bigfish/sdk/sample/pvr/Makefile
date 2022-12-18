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

# -share or -static
LD_FLAGS :=

LIB = -Wl,--start-group $(LD_FLAGS) $(SYS_LIBS) -lc $(HI_LIBS) -Wl,--end-group

COMMON_SRC := $(patsubst %.o, %.c, $(COMMON_FILES))

PVR                 := sample_pvr.c
PVR_PLAY            := sample_pvr_play.c
PVR_MULTIFILE_PLAY  := sample_pvr_multifile_play.c
PVR_REC             := sample_pvr_rec.c
PVR_REC_ALL         := sample_pvr_rec_allts.c
PVR_TIMESHIFT       := sample_pvr_timeshift.c
PVR_ETH_TIMESHIFT   := sample_pvr_eth_timeshift.c
PVR_DEMO            := sample_pvr_demo.c

TARGETS := $(basename $(PVR) $(PVR_PLAY) $(PVR_MULTIFILE_PLAY) $(PVR_REC) $(PVR_REC_ALL) $(PVR_TIMESHIFT) $(PVR_ETH_TIMESHIFT) $(PVR_DEMO))

#===============================================================================
# rules
#===============================================================================
.PHONY:  all clean install uninstall

all: $(TARGETS)

clean:
	-rm -f *.o
	-rm -f $(TARGETS)

install:
uninstall:

$(TARGETS):%:%.c
	@echo "compiling $@..."
	$(AT)$(CC) -o $@ $(CFLAGS) $(COMMON_SRC) $< $(LIBPATH) $(LIB)
