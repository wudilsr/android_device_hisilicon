################################################################################
#    x86/src/squashfs
#    Create By CaiZhiYong
#    2011.01.16
################################################################################
# parameter
PREFIX         ?= $(shell pwd)

################################################################################
#
#  options below should be redefined here, don't use definitions in Makefile 
#  in SDK top dir.
#
CC=gcc
OBJDUMP=objdump
HOST=
CPP=
LD=
NM=

###############################################################################
BUILD_DIR      := $(PREFIX)/tmp
ZLIB           := $(shell pwd)/../zlib
ZLIB_INSTALL   := $(PREFIX)/../zlib
ZLIB_DIR       := $(ZLIB_INSTALL)/tmp
STRIP          := strip
SQUASHFS       := squashfs4.2
XZ             := xz-5.0.4
################################################################################

all: $(PREFIX)/mksquashfs $(PREFIX)/lzma

$(PREFIX)/mksquashfs: $(BUILD_DIR)/bin/mksquashfs
	@test -d $(@D) || mkdir -p $(@D)
	install -vs -t $(PREFIX) $<

$(PREFIX)/lzma: $(BUILD_DIR)/bin/lzma
	@test -d $(@D) || mkdir -p $(@D)
	install -vs -t $(PREFIX) $<

$(BUILD_DIR)/bin/mksquashfs: \
    $(BUILD_DIR)/lib/liblzma.a \
    $(ZLIB_DIR)/lib/libz.a    \
    $(BUILD_DIR)/$(SQUASHFS)/tar
	cd $(BUILD_DIR)/$(SQUASHFS) && \
		make EXTRA_CFLAGS="-I$(BUILD_DIR)/include" \
			LDFLAGS="-L$(BUILD_DIR)/lib" -j 16 && \
		make INSTALL_DIR=$(BUILD_DIR)/bin install && \
	cd -

$(BUILD_DIR)/bin/lzma $(BUILD_DIR)/lib/liblzma.a: \
    $(BUILD_DIR)/$(XZ)/tar
	cd $(BUILD_DIR)/$(XZ) && \
		./configure --prefix="$(BUILD_DIR)" --disable-shared && \
		make LDFLAGS="-L$(BUILD_DIR)/lib" -j 16 && \
		make INSTALL_DIR=$(BUILD_DIR)/bin install && \
	cd -

$(ZLIB_DIR)/lib/libz.a:
	@test -f $(ZLIB_DIR)/lib/libz.a || \
	make -C $(ZLIB) PREFIX=$(ZLIB_INSTALL)

###############################################################################

clean: zlib_clean
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)
	@test ! -e $(PREFIX)/mksquashfs || rm -rfv $(PREFIX)/mksquashfs
	@test ! -e $(PREFIX)/lzma || rm -rfv $(PREFIX)/lzma

zlib_clean:
	@test ! -d $(ZLIB_DIR) || \
	make -C $(ZLIB) PREFIX=$(ZLIB_INSTALL) distclean

distclean: clean

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

###############################################################################
.PHONY: clean distclean all
###############################################################################
