################################################################################
#    ./mii-tool/Makefile
#    Create By CaiZhiYong
#    2011.06.22
################################################################################
PREFIX         ?= $(shell pwd)/rootfs
CROSS_COMPILE  ?= arm-hisiv200-linux-

################################################################################
BUILD_DIR      := $(shell pwd)/tmp
HOST           := $(patsubst %-,%,$(CROSS_COMPILE))
STRIP          := $(CROSS_COMPILE)strip
MIITOOL        := mii-tool

################################################################################

all: $(PREFIX)/usr/local/bin/mii-tool

$(PREFIX)/usr/local/bin/mii-tool: $(BUILD_DIR)/$(MIITOOL)/mii-tool
	@test -d $(@D) || mkdir -p $(@D)
	@install -v -t $(@D) $<

$(BUILD_DIR)/$(MIITOOL)/mii-tool: $(BUILD_DIR)/$(MIITOOL)/tar
	cd $(BUILD_DIR)/$(MIITOOL) && \
		make CC=${CROSS_COMPILE}gcc LDFLAGS="-static" -j 16 && \
	cd -

################################################################################

$(BUILD_DIR)/%/tar:
	test -d $(@D) || mkdir -p $(@D)
	tar -xf $(notdir $(@:/tar=)).tar.* -C $(BUILD_DIR)
	@touch $@

################################################################################

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f $(PREFIX)/usr/local/bin/mii-tool

menuconfig:
	@echo "not support"

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################

