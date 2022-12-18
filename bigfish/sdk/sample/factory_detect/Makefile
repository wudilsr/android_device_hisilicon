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
FV_BASE=$(shell pwd)
FV_SRC_DIR	= $(FV_BASE)/src
FV_CONF_DIR	= $(FV_BASE)/configs
FV_ADP_DIR	= $(FV_BASE)/adapter
FV_TARGET_DIR	= $(FV_BASE)/out
FV_INI_DIR	= $(FV_BASE)/ini
SAMPLE_COMM_DIR = $(FV_BASE)/../common

FV_LIB_NAME	= $(FV_TARGET_DIR)/libhifv.a
FV_EXE_NAME	= $(FV_TARGET_DIR)/hifv

FV_INCLUDE	= -I$(FV_BASE)/include -I$(FV_CONF_DIR) -I$(FV_ADP_DIR) -I$(FV_INI_DIR) -I$(FV_SRC_DIR)  -I$(SAMPLE_COMM_DIR)
VPATH		= $(FV_CONF_DIR) $(FV_ADP_DIR) $(FV_SRC_DIR) $(FV_INI_DIR) 
FV_SRCS		= $(foreach path,$(VPATH),$(wildcard $(path)/*.c))
FV_OBJS		= $(addprefix $(FV_TARGET_DIR)/, $(patsubst %.c,%.o,$(notdir $(FV_SRCS))))
FV_OBJS        += $(SAMPLE_COMM_DIR)/hi_adp_mpi.o \
		  $(SAMPLE_COMM_DIR)/hi_adp_search.o \
		  $(SAMPLE_COMM_DIR)/hi_adp_hdmi.o \
		  $(SAMPLE_COMM_DIR)/hi_adp_data.o \
		  $(SAMPLE_COMM_DIR)/hi_adp_demux.o

EXT_INCLUDE	= -I$(SDK_DIR)/pub/include

EXT_LIB_PATH 	= -L$(SDK_DIR)/pub/lib/static
EXT_LIB_PATH 	+= -L$(SDK_DIR)/pub/lib/share

LIBS := $(SYS_LIBS) $(HI_LIBS)

EXT_LIBS	= -Wl,--start-group $(LIBS) -Wl,--end-group

CFLAGS_ALL	= -O2 -Wall $(FV_INCLUDE) $(EXT_LIB_PATH) $(EXT_INCLUDE) $(EXT_LIBS) $(CFG_HI_SAMPLE_CFLAGS)

CFLAGS         := $(CFLAGS_ALL)

# KEY_LED define
ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
CFLAGS += -DHI_BUILD_WITH_KEYLED
    ifeq ($(CFG_HI_KEYLED_PT6964_SELECT),y)
    CFLAGS += -DHI_KEYLED_PT6964
    endif
    ifeq ($(CFG_HI_KEYLED_PT6961_SELECT),y)
    CFLAGS += -DHI_KEYLED_PT6961
    endif
    ifeq ($(CFG_HI_KEYLED_CT1642_SELECT),y)
    CFLAGS += -DHI_KEYLED_CT1642
    endif
    ifeq ($(CFG_HI_KEYLED_74HC164_SELECT),y)
    CFLAGS += -DHI_KEYLED_74HC164
    endif
    ifeq ($(CFG_HI_KEYLED_FD650_SELECT),y)
    CFLAGS += -DHI_KEYLED_FD650
    endif
endif

ifndef CFG_HI_ADVCA_FUNCTION
CFLAGS+= -static
endif

.PHONY: drivers prepare clean install uninstall

all: prepare drivers $(FV_OBJS) 
	@$(CC) $(FV_OBJS) $(CFLAGS) -o $(FV_EXE_NAME) 

prepare:
	mkdir -p $(FV_TARGET_DIR)

$(FV_TARGET_DIR)/%.o:%.c
	$(AT)$(CC) $(CFLAGS) -c  $< -o $@

drivers:
	$(AT)make -C drivers

clean:
	$(AT)rm -rf $(FV_OBJS) $(FV_TARGET_DIR)
	$(AT)make -C drivers clean

