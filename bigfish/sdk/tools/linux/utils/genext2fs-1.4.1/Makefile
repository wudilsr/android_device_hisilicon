###############################################################################
#    x86/src/genext2fs-1.4.1
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
BIN_DIR        :=$(PREFIX)/bin

###############################################################################
all:
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	tar zxf genext2fs-1.4.1.tar.gz -C $(PREFIX)
	test -d $(BIN_DIR)|| mkdir -p $(BIN_DIR)
	cd $(PREFIX)/genext2fs-1.4.1; \
	    ./configure;make;cp genext2fs $(BIN_DIR); \
	cd -

clean:
	rm -rf $(PREFIX)/genext2fs-1.4.1
	rm -rf $(PREFIX)/bin

distclean: clean

###############################################################################
.PHONY: clean distclean all
###############################################################################
