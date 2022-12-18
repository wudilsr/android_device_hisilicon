################################################################################
#
#  Copyright (C) 2014 Hisilicon Technologies Co., Ltd.  All rights reserved. 
#
#  This program is confidential and proprietary to Hisilicon Technologies Co., Ltd.
#  (Hisilicon), and may not be copied, reproduced, modified, disclosed to
#  others, published or used, in whole or in part, without the express prior
#  written permission of Hisilicon.
#
#  Create By CaiZhiyong 2014.09.13
#
################################################################################
PREFIX         ?= $(shell pwd)/rootfs
CROSS_COMPILE  ?= arm-hisiv200-linux-

################################################################################
BUILD_DIR      := $(shell pwd)/tmp
HOST           := $(patsubst %-,%,$(CROSS_COMPILE))
STRIP          := $(CROSS_COMPILE)strip
ifeq (${CROSS_COMPILE},arm-histbv300-linux-)
COREUTILS      := coreutils-8.18
else
COREUTILS      := coreutils-8.5
endif
TARGETS        := bin/sandbox

################################################################################
all: $(addprefix $(PREFIX)/,$(TARGETS))

$(PREFIX)/%: $(BUILD_DIR)/%
	test -d $(@D) || mkdir -p $(@D)
	cp -fv $(BUILD_DIR)/bin/chroot $@

################################################################################
$(addprefix $(BUILD_DIR)/,$(TARGETS)): \
    $(BUILD_DIR)/$(COREUTILS)/build_finish
	@

$(BUILD_DIR)/$(COREUTILS)/build_finish: \
    $(BUILD_DIR)/$(COREUTILS)/tar
	cd $(<D) && ./configure --prefix=$(BUILD_DIR) --host=$(HOST) --enable-no-install-program=stdbuf LDFLAGS="-static -pthread"
	make -C $(<D) -j
	make -C $(<D) install
	@touch $@

################################################################################

$(BUILD_DIR)/%/tar:
	test -d $(@D) || mkdir -p $(@D)
	tar -xf $(notdir $(@:/tar=)).tar.* -C $(@D)/../
	@touch $@

################################################################################

clean:
	@rm -rf $(BUILD_DIR)

menuconfig:
	@echo "not support"

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################
