################################################################################
#    ./scripts/Makefile
#    Create By CaiZhiYong
#    2011.06.19
################################################################################
PREFIX         ?= $(shell pwd)/rootfs
CROSS_COMPILE         := \
	$(if $(CROSS_COMPILE),$(CROSS_COMPILE),arm-hisiv200-linux-)
#CONFIG_MINI_ROOTFS    ?=n
CONFIG_LIBCPP_SUPPORT := \
	$(if $(CFG_HI_LIBCPP_SUPPORT),$(CFG_HI_LIBCPP_SUPPORT),n)
CONFIG_BUSYBOX_MDEV   := \
	$(if $(CONFIG_BUSYBOX_MDEV),$(CONFIG_BUSYBOX_MDEV),n)
CONFIG_BUSYBOX_UDEV   := \
	$(if $(CONFIG_BUSYBOX_UDEV),$(CONFIG_BUSYBOX_UDEV),y)
CONFIG_ETH_SUPPORT    := \
	$(if $(CONFIG_ETH_SUPPORT),$(CONFIG_ETH_SUPPORT),y)

HOST           := $(patsubst %-,%,$(CROSS_COMPILE))
################################################################################
include ../config.mk

INIT_SCRIPT    := etc/init.d/S99init

ROOTFS         := bin boot dev home lib var/run sys tmp opt proc nfsroot etc \
	mnt root share sbin usr/bin usr/sbin usr/lib usr/local/bin usr/share  \
	usr/local

TARGETS        := $(INIT_SCRIPT) $(ROOTFS) init
#	dev/console dev/ttyS000 dev/ttyAMA1 dev/ttyAMA0

################################################################################

all: $(addprefix $(PREFIX)/,$(TARGETS))

$(addprefix $(PREFIX)/,$(ROOTFS)):
ifeq ($(CFG_HI_LOADER_TYPE),OS)
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	@tar -xjf ./rootfs.tar.bz2 -C $(PREFIX)/../
	@tar -xjf ./rootfs_scripts.tar.bz2 -C $(PREFIX)/../
	@tar -xjf ./rootfs_scripts_loader.tar.bz2 -C $(PREFIX)/../
else
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	@tar -xjf ./rootfs.tar.bz2 -C $(PREFIX)/../
	@tar -xjf ./rootfs_scripts.tar.bz2 -C $(PREFIX)/../
#TODO: XXX
ifeq ($(findstring fpga,$(CFG_HI_BOOT_REG_NAME)), fpga)
	@tar -xjf ./libs/$(HOST)-fpga.tar.bz2 -C $(PREFIX)
else
	@tar -xjf ./libs/$(HOST).tar.bz2 -C $(PREFIX)
endif
ifneq ($(CONFIG_LIBCPP_SUPPORT),y)
	rm -rf $(PREFIX)/lib/*c++.so*
endif

ifneq ($(CONFIG_BUSYBOX_UDEV),y)
	@rm -rf $(PREFIX)/etc/udev
	@rm -rf $(PREFIX)/etc/init.d/S01udev
ifeq ($(CONFIG_BUSYBOX_MDEV),y)
	@tar -xjf rootfs_scripts_mdev.tar.bz2 -C $(PREFIX)/../
endif
endif

ifneq ($(CONFIG_ETH_SUPPORT),y)
	@rm -rf $(PREFIX)/etc/protocols
	@rm -rf $(PREFIX)/etc/services
	@rm -rf $(PREFIX)/etc/init.d/S80network
	@rm -rf $(PREFIX)/usr/share/udhcpc
endif
endif

$(PREFIX)/$(INIT_SCRIPT):
	@test -d $(@D) || mkdir -p $(@D)
	@(echo '#!/bin/sh'; \
		echo -e '# This file auto create by makefile\n'; \
		echo -e "echo \"Compile file system used $(CROSS_COMPILE)\""; \
		echo "echo \"`date +"%F %X"` (`echo ${USER}`@`uname -n`)\""; \
		echo 'mkdir -p /lib/modules/`uname -r`'; \
		echo -e ${CONFIG_ROOTFS_CMD}; \
	) > $@
	@chmod +xr $@

#${PREFIX}/dev/console \
#${PREFIX}/dev/ttyS000 \
#${PREFIX}/dev/ttyAMA1 \
#${PREFIX}/dev/ttyAMA0:
#	@test -d $(@D) || mkdir -p $(@D)
#	mknod ${PREFIX}/dev/ttyAMA0 c 204 64
#	mknod ${PREFIX}/dev/ttyAMA1 c 204 65
#	mknod ${PREFIX}/dev/ttyS000 c 204 64
#	mknod ${PREFIX}/dev/console c 5 1

$(PREFIX)/init:
	@cd ${PREFIX} && \
		ln -fs sbin/init init && \
	cd -

################################################################################

clean:
	@(for ix in $(TARGETS); do \
		if [ -d $(PREFIX)/$$ix ]; then ( \
			test ! -z "$$(ls -A ${PREFIX}/$${ix})" || \
				rm -rf $(PREFIX)/$$ix; \
		) else ( \
			test ! -e $(PREFIX)/$$ix || \
				rm -rf $(PREFIX)/$$ix; \
		) fi \
	done)

menuconfig:
	@echo "not support"

distclean: clean

install:
	@echo "not support"

################################################################################
.PHONY: clean menuconfig distclean install
################################################################################
