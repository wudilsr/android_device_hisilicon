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

APP     := sample_vp_usbcam
APP2    := sample_vp_vi

OBJS    := sample_vp_usbcam.o $(COMMON_FILES)
OBJS2   := sample_vp_vi.o $(COMMON_FILES) $(SAMPLE_DIR)/common/hi_adp_hdmi_rx.o

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(APP) $(APP2)

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(APP2): $(OBJS2)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(OBJS2)
	-$(AT)rm -f $(APP)
	-$(AT)rm -f $(APP2)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

install:

uninstall:
