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

MCE_UPDATE      := sample_mce_update
MCE_UPDATE_OBJS := sample_mce_update.o $(COMMON_FILES)

MCE_TRANS       := sample_mce_trans
MCE_TRANS_OBJS  := sample_mce_trans.o $(COMMON_FILES)

TARGETS := $(MCE_UPDATE)

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
TARGETS += $(MCE_TRANS)
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(TARGETS)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(MCE_UPDATE): $(MCE_UPDATE_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(MCE_TRANS): $(MCE_TRANS_OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(MCE_UPDATE) $(MCE_UPDATE_OBJS)
	-$(AT)rm -f $(MCE_TRANS) $(MCE_TRANS_OBJS)

install:

uninstall:
