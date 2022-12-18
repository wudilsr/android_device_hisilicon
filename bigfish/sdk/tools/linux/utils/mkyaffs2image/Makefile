################################################################################
#    x86/src/mkyaffs2image
#    Create By 
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
STRIP          := strip
MKYAFFS2IMAGE  := mkyaffs2image.300_301_504_610
################################################################################

all: \
    $(BUILD_DIR)/$(MKYAFFS2IMAGE)/tar
	cd $(BUILD_DIR)/$(MKYAFFS2IMAGE) && \
		make && \
	cd -

################################################################################

clean:
	@test ! -d $(BUILD_DIR) || rm -rfv $(BUILD_DIR)

distclean: clean

$(BUILD_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(BUILD_DIR)
	@touch $@

################################################################################
.PHONY: clean distclean all
################################################################################
