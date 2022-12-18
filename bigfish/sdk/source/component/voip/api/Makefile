#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..

include $(SDK_DIR)/base.mak
endif

VOIP_DIR = $(SDK_DIR)/source/component/voip
ALSA_DIR = $(SDK_DIR)/source/component/alsa
BLUETOOTH_DIR = $(SDK_DIR)/source/component/bluetooth
#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(COMMON_DRV_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(MSP_DRV_INCLUDE)                    \
            -I$(VOIP_DIR)/include  \
            -I$(VOIP_DIR)/api/include  \
            -I$(VOIP_DIR)/drv/include \
            -I$(VOIP_DIR)/drv/hme/inc \
            -I$(ALSA_DIR)/include/alsa \
	    -I$(ALSA_DIR)/hi_api \
	    -I$(ALSA_DIR)/include \
		-I$(BLUETOOTH_DIR)/include/alsa \
	    -I$(BLUETOOTH_DIR)/hi_api \
	    -I$(BLUETOOTH_DIR)/include 

LIBS := libhi_voip
        
OBJS := $(VOIP_DIR)/api/unf/hi_unf_voip.o   \
        $(VOIP_DIR)/api/hme/mpi_voip_hme.o  \
        $(VOIP_DIR)/api/hme/msg_trace.o

HEADER_FILES := $(VOIP_DIR)/include/hi_unf_voip.h   \
                $(VOIP_DIR)/include/hi_error_voip.h

ifeq (y,$(CFG_HI_ALSA_SUPPORT))
OBJS += $(VOIP_DIR)/api/aud_adp/mpi_aud_adp.o
else
OBJS += $(VOIP_DIR)/api/aud_adp/mpi_aud_adp_no_alsa.o
endif
#===============================================================================
# rules
#===============================================================================
.PHONY : all clean install uninstall

all : $(LIBS)

clean:
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS).a
	$(AT)rm -rf $(LIBS).so

install:all
	$(AT)cp -f  $(LIBS).a           $(STATIC_LIB_DIR)/
	$(AT)cp -f  $(LIBS).so          $(SHARED_LIB_DIR)/
	$(AT)cp -f  $(HEADER_FILES)     $(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS).a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS).so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

$(LIBS) : $(OBJS)
	$(AT)$(AR) -rsv $@.a $^
	$(AT)$(CC) -shared -o $@.so $^ -L$(ALSA_DIR)/lib  -lasound



