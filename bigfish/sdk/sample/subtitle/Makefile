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

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
CFLAGS += -DHI_FRONTEND_SUPPORT
endif

CFLAGS += -DSTREAM_TYPE_SCTE_82H

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)

LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

COMMON_SRC := $(patsubst %.o, %.c, $(COMMON_FILES)) sample_subtitle_data.c sample_subtitle_out.c

SUBTITLE := sample_subtitle
SUBTITLE_SRC := sample_subtitle.c

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(SUBTITLE)

clean:
	-$(AT)rm -f $(SUBTITLE)

install:

uninstall:

$(SUBTITLE):%:%.c
	$(AT)$(CC) -o $@ $(CFLAGS) $(COMMON_SRC) $< $(LIBPATH) $(LIB)
