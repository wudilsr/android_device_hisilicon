################################################################################
#    x86/src/libcap-ng
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
AR=ar
CPP=cpp
LD=ld
RANLIB=ranlib
NM=nm
STRIP=strip

################################################################################
LIBATTR_PATH=$(PREFIX)/attr-2.4.46
FILECAP_PATH=$(PREFIX)/libcap-ng-0.6.5

################################################################################

all: filecap

libattr:
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	@tar xzf attr-2.4.46.src.tar.gz -C $(PREFIX)
	@-mkdir -p $(LIBATTR_PATH)/INSTALL_DIR
	cd $(LIBATTR_PATH) && \
	 ./configure --prefix=$(LIBATTR_PATH)/INSTALL_DIR && \
	 make && make install-dev && \
	cd -

filecap: libattr
	@test -d $(PREFIX) || mkdir -p $(PREFIX)
	@tar xzf libcap-ng_0.6.5.orig.tar.gz -C $(PREFIX)
	@-mkdir -p $(FILECAP_PATH)/INSTALL_DIR
	cd $(FILECAP_PATH) && \
	CFLAGS="-I$(LIBATTR_PATH)/INSTALL_DIR/include -g -O2" \
	    ./configure --prefix=/usr --disable-shared --without-python && \
	make && \
	make DESTDIR=$(FILECAP_PATH)/INSTALL_DIR install && \
	cd -

################################################################################

clean:
	-rm -rf $(FILECAP_PATH)
	-rm -rf $(LIBATTR_PATH)

distclean: clean

################################################################################
.PHONY: clean distclean all
################################################################################
