################################################################################
#    x86/src/e2fsprogs
#    Create By
#    2011.01.16
###############################################################################
# parameter
PREFIX         ?= $(shell pwd)

###############################################################################
#
#  options below should be redefined here, don't use definitions in Makefile 
#  in SDK top dir.
#
CC=gcc
AR=ar
CPP=cpp
LD=ld
RANLIB=ranlib
NM=nm
STRIP=strip

###############################################################################
INST=$(PREFIX)/e2fsprogs-1.41.11/inst

###############################################################################

all:
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	tar xzf e2fsprogs-1.41.11.tar.gz -C $(PREFIX)
	mkdir $(INST) -p
	cd $(PREFIX)/e2fsprogs-1.41.11; \
		./configure >/dev/null;make >/dev/null; \
		make  -C misc mke2fs.static; \
		make -C misc tune2fs.static; \
		make -C e2fsck e2fsck.static; \
	cd -
clean:
	rm $(PREFIX)/e2fsprogs-1.41.11 -rf

distclean: clean
 
###############################################################################
.PHONY: clean distclean all
###############################################################################
