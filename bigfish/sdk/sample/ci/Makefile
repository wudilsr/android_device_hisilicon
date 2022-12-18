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
			
ifeq ($(CFG_HI_CI_DEV_CIMAX),y)
CFLAGS += -DHI_CI_DEV_CIMAX
endif
ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
CFLAGS += -DHI_CI_DEV_CIMAXPLUS
endif
ifeq ($(CFG_HI_CI_DEV_HICI),y)
CFLAGS += -DHI_CI_DEV_HICI
endif

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

APP = sample_ci
APP2 = sample_ci_dvbplay
APP3 = sample_ci_tsplay

OBJS = sample_ci.o
OBJS2 = sample_ci_dvbplay.o stack/ci_stack.o $(COMMON_FILES)
OBJS3 = sample_ci_tsplay.o stack/ci_stack.o $(COMMON_FILES)

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

install:

uninstall:

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

