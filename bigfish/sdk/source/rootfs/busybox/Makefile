################################################################################
#    ./busybox/Makefile
#    Create By CaiZhiYong
#    2011.06.19
################################################################################
# PREFIX        - rootfs path
# CROSS_COMPILE - cross compile tools
################################################################################
PREFIX              ?= $(shell pwd)/rootfs
CROSS_COMPILE       ?= arm-hisiv200-linux-

CONFIG_CA_RELEASE   ?= n
#CONFIG_MINI_ROOTFS  ?= n

################################################################################
BUILD_DIR      := $(shell pwd)/tmp
HOST           := glibc
STRIP          := $(CROSS_COMPILE)strip

ifeq (${CROSS_COMPILE},arm-histbv300-linux-)
BUSYBOX        := busybox-1.24.1
endif
ifeq (${CROSS_COMPILE},arm-histbv310-linux-)
BUSYBOX        := busybox-1.24.1
endif
ifeq (${CROSS_COMPILE},arm-hisiv200-linux-)
BUSYBOX        := busybox-1.16.1
endif

BUSYBOX_CONFIG := $(shell pwd)/$(BUSYBOX).config
TARGETS        := bin/busybox bin/busybox.cap 

MKFLAGS        += CONFIG_CROSS_COMPILER_PREFIX=$(CROSS_COMPILE)
	
################################################################################

# CONFIG_FILE-$(CONFIG_CA_RELEASE)  := $(HOST)_ca.config
# CONFIG_FILE-$(CONFIG_MINI_ROOTFS) += $(HOST)_mini.config


 # check busybox config. you should NOT set CONFIG_CA_RELEASE=y and 
 # CONFIG_MINI_ROOTFS=y at the same time!!

# MULTI_CONFIG_FILE := $(word 2,$(CONFIG_FILE))
# $(if $(MULTI_CONFIG_FILE),\
	# $(error config error: select multi busybox config file.),)


# CONFIG_FILE := $(if $(CONFIG_FILE-y),$(CONFIG_FILE-y),$(HOST).config)

CONFIG_BUSYBOX_NAME := \
	$(if $(CFG_HI_BUSYBOX_CFG_NAME),$(CFG_HI_BUSYBOX_CFG_NAME),$(HOST).config)

MKFLAGS += CONFIG_BUSYBOX_NAME=$(CONFIG_BUSYBOX_NAME)

ifdef CFG_HI_ADVCA_FUNCTION
ifndef CFG_HI_LOADER_APPLOADER
CONFIG_BUSYBOX_USER_NAME := \
	$(if $(CFG_HI_BUSYBOX_CFG_USER_NAME),$(CFG_HI_BUSYBOX_CFG_USER_NAME),$(HOST).config)

MKFLAGS += CONFIG_BUSYBOX_USER_NAME=$(CONFIG_BUSYBOX_USER_NAME)
MKFLAGS += CONFIG_CA_RELEASE=$(CFG_ADVCA_FUNCTION)
endif
endif

   
CONFIG_USER_FILE := \
	$(if $(CONFIG_BUSYBOX_USER_NAME),$(CONFIG_BUSYBOX_USER_NAME),$(HOST).config)

CONFIG_USER_ROOTFS_PATH = $(PREFIX)/home/stb
   
compile_busybox = $1

clean_busybox  = $(cd $(BUILD_DIR)/$(BUSYBOX)/ && \
         make $(MKFLAGS) clean) 


################################################################
ifeq ($(CONFIG_CA_RELEASE),y)
all: $(PREFIX)/home/stb/bin/busybox  $(PREFIX)/bin/busybox
else
all: $(PREFIX)/bin/busybox 
endif

#+++++++++++compile common user busybox (located in /home/stb/bin)+++++++++++++
$(PREFIX)/home/stb/bin/busybox: \
    $(BUILD_DIR)/$(BUSYBOX)/tar
	cd $(BUILD_DIR)/$(BUSYBOX)/ && \
	make $(MKFLAGS) CONFIG_PREFIX=$(CONFIG_USER_ROOTFS_PATH) clean && \
	cd -
	cp -fv $(call compile_busybox, $(BUSYBOX_CONFIG)/$(CONFIG_USER_FILE)) \
		$(BUILD_DIR)/$(BUSYBOX)/.config
	cd $(BUILD_DIR)/$(BUSYBOX)/ && \
	make $(MKFLAGS) CONFIG_PREFIX=$(CONFIG_USER_ROOTFS_PATH) -j 16 && \
	make $(MKFLAGS) CONFIG_PREFIX=$(CONFIG_USER_ROOTFS_PATH) install


#+++++++++++compile root directory busybox (located in /bin)+++++++++++++
$(PREFIX)/bin/busybox: \
    $(BUILD_DIR)/$(BUSYBOX)/tar
	cd $(BUILD_DIR)/$(BUSYBOX)/ && \
	make $(MKFLAGS) CONFIG_PREFIX=$(PREFIX) clean && \
	cd -
	cp -fv $(call compile_busybox, $(BUSYBOX_CONFIG)/$(CONFIG_BUSYBOX_NAME)) \
		$(BUILD_DIR)/$(BUSYBOX)/.config
	cd $(BUILD_DIR)/$(BUSYBOX)/ && \
	make $(MKFLAGS) CONFIG_PREFIX=$(PREFIX) -j 16 && \
	make $(MKFLAGS) CONFIG_PREFIX=$(PREFIX) install

 
   
###############################################################################

$(BUILD_DIR)/%/tar:
	test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rvf $(BUILD_DIR)
	@(for ix in $$(find ${PREFIX}/* -lname "*/busybox" 2>/dev/null) \
		$$(find ${PREFIX}/* -lname "busybox" 2>/dev/null); do \
		rm -rfv $$ix; \
	done )
	@(for ix in $(TARGETS); do \
		test ! -e $(PREFIX)/$$ix || rm -rfv $(PREFIX)/$$ix; \
	done )

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################

