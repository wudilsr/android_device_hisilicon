ifndef HIDOL_DIR
HIDRM_DIR := $(PWD)
else
HIDRM_DIR := $(HIDOL_DIR)/component/drmengine
endif

export HIDRM_DEP_LIBDIR := $(HIDRM_DIR)/out/pub/lib
export HIDRM_DEP_INCDIR := $(HIDRM_DIR)/out/pub/include

######################TOOL CHAINS#########################
ifndef CFG_HI_TOOLCHAINS_NAME
CFG_HI_TOOLCHAINS_NAME   := arm-hisiv200-linux
endif

export AR=${CFG_HI_TOOLCHAINS_NAME}-ar
export LD=${CFG_HI_TOOLCHAINS_NAME}-ld
export CPP=${CFG_HI_TOOLCHAINS_NAME}-cpp
export CC=${CFG_HI_TOOLCHAINS_NAME}-gcc
export STRIP=${CFG_HI_TOOLCHAINS_NAME}-strip

######################CFLAGS#############################
HIDRM_INC := $(HIDRM_DIR)/include

CFLAGS := -march=armv7-a -mcpu=cortex-a9
CFLAGS += -O2 -Wall
CFLAGS += -I$(HIDRM_INC)/
#export CFG_HI_ADVCA_FUNCTION := y
ifdef CFG_HI_ADVCA_FUNCTION
CFLAGS += -DHI_ADVCA_FUNCTION_RELEASE
endif

export CFLAGS

######################LOCAL VAR#########################
LIBHIDRM := libHidrm
PLUGINS  := plugins

.PHONY: prepare all clean install $(LIBHIDRM) $(PLUGINS)

all: prepare $(LIBHIDRM) $(PLUGINS)
clean: $(LIBHIDRM)_clean $(PLUGINS)_clean
	-rm $(HIDRM_DEP_LIBDIR)/libHiDrmEngine.so
	-rm $(HIDRM_DEP_LIBDIR)/libHiplayreadyEngine.so
	-rm $(HIDRM_DEP_LIBDIR)/libpassthru.so

install: prepare $(LIBHIDRM)_install $(PLUGINS)_install
	cp $(HIDRM_INC)/hi_drm_*.h $(HIDRM_DEP_INCDIR)/ -vf

prepare:
	mkdir -p $(HIDRM_DEP_LIBDIR)
	mkdir -p $(HIDRM_DEP_INCDIR)

$(LIBHIDRM):
	make -C $(LIBHIDRM)

$(PLUGINS):
	make -C $(PLUGINS)

$(LIBHIDRM)_clean:
	make -C $(LIBHIDRM) clean

$(PLUGINS)_clean:
	make -C $(PLUGINS) clean

$(LIBHIDRM)_install:
	make -C $(LIBHIDRM) install

$(PLUGINS)_install:
	make -C $(PLUGINS) install

