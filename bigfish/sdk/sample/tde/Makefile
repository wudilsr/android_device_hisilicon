#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

include $(SAMPLE_DIR)/base.mak

CFG_INC += $(CFG_HI_SAMPLE_CFLAGS)
SRC = $(wildcard *.c)
APP= $(SRC:%.c=%)

OTHERSRC= src/tde_common.c
COMMON_SRC := $(patsubst %.o, %.c, $(COMMON_FILES))

INCDIR = src
CFG_INC += -I$(INCDIR) \
	   -I$(SDK_INC_DIR) \
	   -I$(SAMPLE_DIR)/common

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -Wl,--end-group

.PHONY: all clean install uninstall
all: $(APP)
$(APP): %: %.c
	@$(QUIET) $(CC) -o $@ $< $(COMMON_SRC) $(OTHERSRC) $(CFG_INC) $(LIBPATH) $(LIB)

clean:
	-@rm -f $(APP)

install:

uninstall:

