#===============================================================================
# for apploader only
#===============================================================================
CFLAGS += -I$(COMMON_UNF_INCLUDE)
CFLAGS += -I$(MSP_UNF_INCLUDE)
CFLAGS += -I$(PUB_DIR)/include
CFLAGS += -I$(COMMON_DIR)/api/flash/include 
CFLAGS += -I$(COMPONENT_DIR)/curl/include
CFLAGS += -I$(COMPONENT_DIR)/loader/app/ca/

ROOTBOXHOME_DIR := $(SDK_DIR)/pub/rootbox/home
ROOTBOXHOME_EXIST := $(shell if [ -d $(ROOTBOXHOME_DIR) ]; then echo "exist"; else echo "notexist"; fi;)

LOADER_SRC += hi_adp_osd.c \
              crc32.c


LD_FLAGS += -Wl,--start-group
ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
ifneq ($(CFG_HI_ADVCA_TYPE), VERIMATRIX)
ifeq ($(CFG_HI_ADVCA_TYPE), NAGRA)
CFLAGS += -I$(COMPONENT_DIR)/loader/app/ca/nasc/include
LIBPATH += -L$(COMPONENT_DIR)/loader/app/ca/nasc/api
LD_FLAGS += -lrt -lpthread -ldl -lm  -l:libhi_common.a -l:libhigo.a -lfreetype -lz -l:libpng.a -l:libhigoadp.a -l:libjpeg.a -lhi_ssd -lhi_ca_ssd -l:libhi_nagra.a \
		-lhi_msp

else
CFLAGS += -I$(COMPONENT_DIR)/loader/app/ca/cx/include
LD_FLAGS += -lrt -lpthread -ldl -lm  -l:libhi_common.a -l:libhigo.a -lfreetype -lz -l:libpng.a -l:libhigoadp.a -l:libjpeg.a -lhi_ca_ssd \
		-lhi_msp 
endif
else
CFLAGS += -I$(COMPONENT_DIR)/loader/app/ca/vmx/include
LD_FLAGS += -lrt -lpthread -ldl -lm  -l:libhi_common.a -l:libhigo.a -lfreetype -lz -l:libpng.a -l:libhigoadp.a -l:libjpeg.a -lhi_vmx_loader_verify -lhi_ca_ssd \
		-lhi_msp
LIBPATH += -L$(COMPONENT_DIR)/loader/app/ca/vmx/vmx_loader_verify_lib/
endif
LIBPATH += -L$(COMPONENT_DIR)/loader/app/ca/

else

LD_FLAGS += -lrt -lpthread -ldl -lm -l:libhi_common.a -l:libhigo.a -lfreetype -lz -l:libpng.a -l:libhigoadp.a -l:libjpeg.a \
		-lhi_msp
endif

ifeq ($(CFG_HI_CURL_SUPPORT), y)
LD_FLAGS += -l:libcurl.a
endif

LD_FLAGS += -Wl,--end-group

LIBPATH += -L$(STATIC_LIB_DIR) -L$(SHARED_LIB_DIR)

image = loader

.PHONY: all install clean ca ca_clean

all: $(image)

$(image): $(LOADER_SRC)
ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
	$(AT)make -C $(COMPONENT_DIR)/loader/app/ca
endif
	$(CC) -o $@ $^ $(CFLAGS) $(LIBPATH) $(LD_FLAGS) 
	$(STRIP) $@

install: all
	mkdir -p release
	-$(AT)cp -rvf $(CURDIR)/$(image) release
	-$(AT)cp -rvf $(CURDIR)/res release
	-$(AT)cd release; find . -name .svn | xargs rm -Rf; cd -
ifeq ($(ROOTBOXHOME_EXIST), exist)
ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
	-$(AT)$(SCP) -rvf $(CURDIR)/$(image) $(ROOTBOXHOME_DIR)
	-$(AT)$(SCP) -rvf $(CURDIR)/res $(ROOTBOXHOME_DIR)
else
	-$(AT)cp -rvf $(CURDIR)/$(image) $(ROOTBOXHOME_DIR)
	-$(AT)cp -rvf $(CURDIR)/res $(ROOTBOXHOME_DIR)
endif
endif

clean:
ifeq ($(CFG_HI_ADVCA_SUPPORT), y)
	$(AT)make -C $(COMPONENT_DIR)/loader/app/ca clean
endif
	$(AT)rm -rf *.o $(image) release

uninstall: clean
	


	
