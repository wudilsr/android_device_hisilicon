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

ifeq ($(CFG_HI_ALSA_SUPPORT),y)
LIBPATH += -L$(SDK_SHARE_LIB_DIR)/alsa_bluez
CFLAGS += -I$(SDK_INC_DIR)/alsa_bluez
endif

ifeq ($(CFG_HI_BLUETOOTH_SUPPORT),y)
LIBPATH += -L$(SDK_SHARE_LIB_DIR)/alsa_bluez
CFLAGS += -I$(SDK_INC_DIR)/alsa_bluez
endif
DEP_LIBS := $(HI_LIBS)
DEP_LIBS += -lhi_usbphone -lhi_voip
DEP_LIBS += -lasound

LIB = -Wl,--start-group $(SYS_LIBS) $(DEP_LIBS) -Wl,--end-group

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

ifeq ($(CFG_HI_ALSA_SUPPORT),y)

APP = sample_voip  sample_serial

OBJS = voip.o  serial.o $(COMMON_FILES)

all: $(APP)

sample_voip: voip.o $(COMMON_FILES)
	@$(CC) -o $@ $^  $(CFG_INC) $(LIBPATH) $(LIB)

sample_serial: serial.o
	@$(CC) -o $@ $^  $(CFG_INC) $(LIBPATH) $(LIB)

else

APP = sample_voip
OBJS = voip_noalsa.o $(COMMON_FILES)

all: $(APP)

sample_voip: voip_noalsa.o $(COMMON_FILES)
	@$(CC) -o $@ $^  $(CFG_INC) $(LIBPATH) $(LIB)

endif

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:



