################################################################################
#    ./gdb/Makefile
#    Create By CaiZhiYong
#    2012.07.28
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
ifeq (${CROSS_COMPILE},arm-histbv300-linux-)
GDB            := gdb-7.8.1
else
GDB            := gdb-6.8
endif
NCURSES        := ncurses-5.7
TARGETS        := bin/gdbserver bin/gdb

################################################################################

all: $(addprefix $(PREFIX)/,$(TARGETS))

$(PREFIX)/%: $(BUILD_DIR)/%
	@test -d $(@D) || mkdir -p $(@D)
	@install -v -t $(dir $@) $<

$(addprefix $(BUILD_DIR)/,$(TARGETS)): \
    $(BUILD_DIR)/lib/libncurses.a \
    $(BUILD_DIR)/$(GDB)/tar
	cd $(BUILD_DIR)/$(GDB) && \
		./configure --target=$(HOST) --host=$(HOST) \
			--prefix=$(BUILD_DIR) --disable-tui \
			CFLAGS="-g -O2" \
			LDFLAGS="-L$(BUILD_DIR)/lib" && \
		make -j 16 && \
		make install && \
	cd -

$(BUILD_DIR)/lib/libncurses.a: $(BUILD_DIR)/$(NCURSES)/tar
	cd $(BUILD_DIR)/$(NCURSES) && \
		./configure --host=$(HOST) --without-ada --prefix=$(BUILD_DIR) && \
		make -j 16   && \
		make install && \
	cd -

################################################################################

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rf $(BUILD_DIR)
	@(for ix in $(TARGETS); do \
		test ! -e $(PREFIX)/$$ix || rm -rvf $(PREFIX)/$$ix; \
	done)

menuconfig:
	@echo "not support"

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################

