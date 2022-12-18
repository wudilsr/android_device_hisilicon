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

ifeq ($(CFG_HI_APPLOADER_SUPPORT),y)
CFLAGS += -DHI_LOADER_APPLOADER
endif

LIBPATH = -L$(SDK_SHARE_LIB_DIR) -L$(SDK_STATIC_LIB_DIR) 

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
ifneq ($(CFG_HI_ADVCA_TYPE), NAGRA)
LIB = -Wl,--start-group -lrt -lpthread -lm -ldl -ljpeg -lhi_msp -lhiloader -lhi_common -Wl,--end-group
else
LIB = -Wl,--start-group -lrt -lpthread -lm -ldl -lhi_nagra -ljpeg -lhi_msp -lhiloader -lhi_common -Wl,--end-group
endif
else
LIB = -Wl,--start-group -ldl -lm -lrt -ljpeg -lpthread -lhi_msp -lhiloader -lhi_common -Wl,--end-group
endif

APP = sample_loader
OBJS = sample_loader.o

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:$(APP)

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

$(APP): $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)

clean:
	-$(AT)rm -f $(OBJS)
	-$(AT)rm -f $(APP)

install:

uninstall:
