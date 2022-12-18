################################################################################
#    ./sysstat/Makefile
#    Create By CaiZhiYong
#    2012.07.15
################################################################################
PREFIX         ?= $(shell pwd)/rootfs
CROSS_COMPILE  ?= arm-hisiv200-linux-

################################################################################
BUILD_DIR      := $(shell pwd)/tmp
HOST           := $(patsubst %-,%,$(CROSS_COMPILE))
STRIP          := $(CROSS_COMPILE)strip
SYSSTAT        := sysstat-10.0.5
TARGETS        := sbin/mpstat sbin/sar sbin/iostat sbin/sadc sbin/sadf

################################################################################

all: $(addprefix $(PREFIX)/,$(TARGETS))

$(PREFIX)/sbin/%: $(BUILD_DIR)/$(SYSSTAT)/%
	@test -d $(@D) || mkdir -p $(@D)
	@install -vs -t $(@D) --strip-program=$(STRIP) $<

$(addprefix $(BUILD_DIR)/$(SYSSTAT)/,$(notdir $(TARGETS))): \
    $(BUILD_DIR)/$(SYSSTAT)/tar
	cd $(BUILD_DIR)/$(SYSSTAT) && \
		./configure --host=$(HOST) --prefix=$(BUILD_DIR) \
			--exec-prefix=$(BUILD_DIR) CFLAGS="-static" && \
		make -j 16 && \
	cd -

################################################################################

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xf $(notdir $(@:/tar=)).tar.* -C $(BUILD_DIR)
	@touch $@

################################################################################

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(TARGETS)

menuconfig:
	@echo "not support"

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################

