#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../../../..

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
CFLAGS  +=  -I$(CURDIR)/../../include               \
            -I$(CURDIR)/../../../../drv/omxvdec     \
            -I$(CURDIR)/../../../../drv/vfmw/vfmw_v4.0

CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(COMMON_DRV_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(MSP_DRV_INCLUDE)                    

LIBS := libOMX.hisi.video.decoder

OBJS := omx_event_queue.o omx_vdec.o omx_drv_ctx.o

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(OBJS)
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)$(CC) -shared -o $(LIBS).so $^
endif

clean: uninstall
	$(AT)rm -rf $(OBJS)
	$(AT)rm -rf $(LIBS).so

install: all
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -f  $(LIBS).so          $(EXTERN_LIB_DIR)/
endif

uninstall:
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)rm -rf $(EXTERN_LIB_DIR)/$(LIBS).so
endif

%.o : %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

