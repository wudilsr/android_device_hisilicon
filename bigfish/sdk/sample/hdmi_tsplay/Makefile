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

APP1 = sample_hdmi_tsplay
OBJS1 = hdmi_tsplay.o hdmi_test_cmd.o $(COMMON_FILES)

APP2 = sample_hdmi_subplug
OBJS2 = hdmi_subplug.o $(COMMON_FILES)

APP3 = sample_hdmi_cec
OBJS3 = hdmi_cec.o hdmi_test_cmd.o $(COMMON_FILES)

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP1) $(APP2) $(APP3)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(APP1): $(OBJS1)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

$(APP2): $(OBJS2)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
	
$(APP3): $(OBJS3)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS1)
	-$(AT)rm -f $(APP1)
	-$(AT)rm -f $(OBJS2)
	-$(AT)rm -f $(APP2)
	-$(AT)rm -f $(OBJS3)
	-$(AT)rm -f $(APP3)

install:

uninstall:
