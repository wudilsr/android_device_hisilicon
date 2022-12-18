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
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

COMMON_SRC := $(patsubst %.o, %.c, $(COMMON_FILES))

SRC = $(wildcard *.c)

#========================================================================
ifeq ($(CFG_HIFB_SCROLLTEXT_SUPPORT), )
SRC := $(filter-out sample_scrolltext.c, $(SRC))
endif

ifeq ($(CFG_HIFB_CURSOR_SUPPORT), )
SRC := $(filter-out sample_cursorck.c, $(SRC))
endif

ifeq ($(CFG_HI_FREETYPE_FONT_SUPPORT), )
SRC := $(filter-out sample_text.c, $(SRC))
endif

ifeq ($(CFG_HIFB_STEREO3D_SUPPORT), )
SRC := $(filter-out sample_stereo.c, $(SRC))
endif
#=======================================================================

APP= $(SRC:%.c=%)


#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(APP) 

$(APP):  %: %.c
	$(AT)$(CC) -o $@  $< $(COMMON_SRC) $(LIBPATH) $(LIB) $(CFLAGS)

clean:
	-$(AT)rm -f $(APP)

install:

uninstall:

