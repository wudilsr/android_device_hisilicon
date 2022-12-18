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
CFLAGS += -I${SDK_INC_DIR} -I$(SAMPLE_DIR)/common -I$(COMMON_DRV_INCLUDE)

COMMON_FILES  =   ../common/hi_adp_demux.o 	\
                  ../common/hi_psi_si.o 	\
                  ../common/hi_adp_data.o 	\
                  ../common/hi_adp_hdmi.o 	\
                  ../common/hi_adp_mpi.o 	\
                  ../common/hi_adp_search.o 	\
                  ../common/hi_filter.o 	\
                  ../common/search.o

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
COMMON_FILES += ../common/hi_adp_tuner.o
endif

LIBPATH = -L$(SDK_STATIC_LIB_DIR) -L$(SDK_SHARE_LIB_DIR)
LIB = -Wl,--start-group $(SYS_LIBS) $(HI_LIBS) -lhi_nagra -Wl,--end-group

image = sample_ca_getchipinfo sample_ca_r2rencrypt sample_ca_r2rcrypto  \
    sample_ca_tsplay sample_ca_scrplay sample_ca_opensecboot sample_ca_setjtag sample_ca_setmsid \
    sample_ca_setstbsn sample_ca_pvprogram_develop sample_ca_pvprogram_product 

ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
image +=    sample_ca_dvbplay
endif

#===============================================================================
# rules
#===============================================================================

.PHONY: all clean

all:${image}

%.o: %.c
	$(AT)$(CC) $(CFLAGS) -c -o $@ $^

sample_ca_getchipinfo: sample_ca_getchipinfo.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_r2rencrypt: sample_ca_r2rencrypt.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_r2rcrypto: sample_ca_r2rcrypto.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_dvbplay: sample_ca_dvbplay.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_tsplay: sample_ca_tsplay.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_scrplay: sample_ca_scrplay.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_opensecboot: sample_ca_opensecboot.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_setjtag: sample_ca_setjtag.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_setmsid: sample_ca_setmsid.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_setstbsn: sample_ca_setstbsn.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_pvprogram_develop: sample_ca_pvprogram_develop.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

sample_ca_pvprogram_product: sample_ca_pvprogram_product.o ${COMMON_FILES}
	$(AT)$(CC) -o $@ $^ ${LIBPATH} ${LIB}

clean:
	-$(AT)rm -f $(image)
	-$(AT)rm -f *.o