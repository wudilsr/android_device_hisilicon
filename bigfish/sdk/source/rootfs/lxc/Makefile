################################################################################
# PREFIX        - rootfs path
# CROSS_COMPILE - cross compile tools
################################################################################
PREFIX         ?= $(shell pwd)/rootfs
CROSS_COMPILE  ?= arm-hisiv200-linux-

################################################################################
BUILD_DIR      := $(shell pwd)/tmp
HOST           := $(patsubst %-,%,$(CROSS_COMPILE))
STRIP          := $(CROSS_COMPILE)strip
LIBCAP         := libcap-2.22
ATTR           := attr-2.4.46
LXC            := lxc-0.9.0

################################################################################

all: 
	mkdir -p $(BUILD_DIR)
	# build lxc tools
	make $(LXC)
	# create lxc config and fs
	scripts/lxc_create.sh -n stb 
	# install lxc startup script
	cp scripts/S99lxc $(PREFIX)/etc/init.d

################################################################################

$(LXC):$(LIBCAP)
	@tar xzf $(LXC).tar.gz -C $(BUILD_DIR)
	@scripts/do_patch.sh $(BUILD_DIR)/$(LXC) patches/
	cd $(BUILD_DIR)/$(LXC) && \
	./configure --host=$(HOST) --prefix=/usr --with-log-path=/tmp \
	CFLAGS="-I$(BUILD_DIR)/$(LIBCAP)/libcap/include" LDFLAGS="-L$(BUILD_DIR)/$(LIBCAP)/libcap" && \
	make && \
	make DESTDIR=$(BUILD_DIR)/install install
	@rm -rf $(BUILD_DIR)/install/usr/lib/pkgconfig && \
		rm -rf $(BUILD_DIR)/install/usr/share/man && \
		rm -rf $(BUILD_DIR)/install/usr/include 
	@cp -ar $(BUILD_DIR)/install/* $(PREFIX)/

$(ATTR):
	@tar xjf $(ATTR).tar.bz2 -C $(BUILD_DIR)
	cd $(BUILD_DIR)/$(ATTR) && \
	./configure --host=$(HOST) --disable-shared && \
	make 

$(LIBCAP):$(ATTR)
	@tar xzf $(LIBCAP).tar.gz -C $(BUILD_DIR)
	cd $(BUILD_DIR)/$(LIBCAP) && \
	make CC=$(CROSS_COMPILE)gcc BUILD_CC=gcc LDFLAGS+="-L$(BUILD_DIR)/$(ATTR)/libattr/.libs/  -lattr"
	cp -a $(BUILD_DIR)/$(LIBCAP)/libcap/libcap.so* $(PREFIX)/usr/lib

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rf $(BUILD_DIR)

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean distclean install
################################################################################

