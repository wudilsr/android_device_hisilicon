#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_CFLAGS)
CFLAGS += -I$(COMMON_DIR)/include
CFLAGS += -I$(MSP_DIR)/include
CFLAGS += -I$(CURDIR)/include
CFLAGS += -DVER_V1R2

source := $(CURDIR)/src/hi_unf_ttx.c
source += $(CURDIR)/src/teletext_data.c
source += $(CURDIR)/src/teletext_mem.c
source += $(CURDIR)/src/teletext_parse.c
source += $(CURDIR)/src/teletext_recv.c
source += $(CURDIR)/src/teletext_showpage.c
source += $(CURDIR)/src/teletext_utils.c

OBJS := $(source:.c=.o)
LIBS := libhi_ttx

HEADER_FILES := $(CURDIR)/include/hi_unf_ttx.h

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall $(LIBS)

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS) $(LIBS).a $(LIBS).so

install: all
	$(AT)cp -af $(LIBS).a           $(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -af $(LIBS).so          $(SHARED_LIB_DIR)/
endif
	$(AT)cp -f  $(HEADER_FILES)     $(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS).a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS).so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

$(LIBS) : $(OBJS)
	$(AT)$(AR) -rc -o $@.a $^
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)$(CC) -shared -o $@.so $^
endif

%.o : %.c
	$(AT)$(CC) $(CFLAGS) -c $^ -o "$(CURDIR)/src/$(*F).o"

