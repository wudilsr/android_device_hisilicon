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
CFLAGS += -I$(SDK_INC_DIR) -I$(SAMPLE_DIR)/common -I$(MSP_DRV_INCLUDE)

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

APP = sample_hdmi_rx
OBJS = sample_hdmi_rx.o $(COMMON_FILES) $(SAMPLE_DIR)/common/hi_adp_hdmi_rx.o

TARGETS := $(APP)

APP2 = sample_audio_hdmirx
OBJS2 = sample_audio_hdmirx.o $(COMMON_FILES)

ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
TARGETS += $(APP2)
endif

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(TARGETS)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(APP2): $(OBJS2)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP) 
	-$(AT)rm -f $(OBJS2)	
	-$(AT)rm -f $(APP2)

install:

uninstall:
