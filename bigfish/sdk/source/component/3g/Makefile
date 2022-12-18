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
HI3G_DIR := $(SOURCE_DIR)/component/3g

CFLAGS  +=  $(CFG_HI_CFLAGS)
CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)     \
            -I$(COMMON_API_INCLUDE)     \
            -I$(HI3G_DIR)/include       \
            -I$(HI3G_DIR)/src

LIBS := libhi_3g

OBJS := $(HI3G_DIR)/src/hi_3g_intf.o \
        $(HI3G_DIR)/src/3g_intf.o \
        $(HI3G_DIR)/src/3g_ids.o

HEADER_FILES := $(HI3G_DIR)/include/hi_3g_intf.h

#===============================================================================
# rules
#===============================================================================
.PHONY : all clean install uninstall $(LIBS)

all: $(LIBS)

clean:
	$(AT)rm -rf $(OBJS) $(LIBS).a $(LIBS).so

install: all
	$(AT)cp -f  $(LIBS).a           $(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -f  $(LIBS).so          $(SHARED_LIB_DIR)/
endif
	$(AT)cp -f  $(HEADER_FILES)     $(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS).a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS).so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

$(LIBS) : $(OBJS)
	$(AT)$(AR) -rsv $@.a $^
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)$(CC) -shared -o $@.so $^
endif

