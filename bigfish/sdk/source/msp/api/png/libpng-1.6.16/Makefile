PNG_CURDIR = $(shell pwd)

#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../../..

include $(SDK_DIR)/cfg.mak
include $(SDK_DIR)/base.mak
endif

TARGET := png
INSTALL_DIR = $(MSP_DIR)/api/$(TARGET)/release
#===============================================================================
# local variable
#===============================================================================
CFLAGS   =  -funroll-loops
CFLAGS  +=  -I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(COMMON_DRV_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
            -I$(MSP_API_INCLUDE)                    \
            -I$(MSP_DRV_INCLUDE)                    \
            -I$(MSP_DIR)/api/$(TARGET)/include      \
            -I$(MSP_DIR)/drv/$(TARGET)/include      \
            -I$(MSP_DIR)/api/jpeg/grc_cmm_inc

CFLAGS  +=  -I${COMPONENT_DIR}/zlib/release/include \
            -I$(MSP_DIR)/drv/include                \
            -I${COMPONENT_DIR}/freetype/release/include

CFLAGS  +=  $(CFG_HI_CFLAGS)
CFLAGS  +=  -DCONFIG_GFX_STB_SDK
CFLAGS  +=  -DHIPNG_ACCELERATE
CFLAGS  +=  -DHIPNG_MMZ
CFLAGS  +=  -DPNG_NO_STRING
CFLAGS  +=  -DHIGFX_COMMON

ZLIBLIB = ${COMPONENT_DIR}/zlib/release/lib
ZLIBINC = ${COMPONENT_DIR}/zlib/release/include
#===============================================================================
# toolchain
#===============================================================================
AR_RC  = ar rc
LN_SF  = ln -sf
RANLIB = ranlib

LIBNAME = libpng16
PNGMAJ  = 16
RELEASE = 16

# Shared library names:
LIBSO    = $(LIBNAME).so
LIBSOMAJ = $(LIBNAME).so.$(PNGMAJ)
LIBSOREL = $(LIBSOMAJ).$(RELEASE)
OLDSO    = libpng.so

# Utilities:
MKDIR_P=mkdir -p
CP=cp
RM_F=/bin/rm -f

# where "make install" puts libpng16.a, libpng16.so*,
# libpng16/png.h, libpng16/pngconf.h, and libpng16/pnglibconf.h
# Prefix must be a full pathname.
prefix      = ${INSTALL_DIR}
exec_prefix = $(prefix)

ALIGN=

# for i386:
#ALIGN=-malign-loops=2 -malign-functions=2

WARNMORE = -Wwrite-strings -Wpointer-arith -Wshadow            \
	   -Wmissing-declarations -Wtraditional -Wcast-align   \
   	   -Wstrict-prototypes -Wmissing-prototypes

# for pgcc version 2.95.1, -O3 is buggy; don't use it.
CPPFLAGS  = -I$(ZLIBINC) # -DPNG_DEBUG=5
LDFLAGS   = -L. -Wl,-rpath,. -L$(ZLIBLIB) -Wl,-rpath,$(ZLIBLIB) -lpng16 -lz -lm
LDFLAGS_A = -L$(ZLIBLIB) -Wl,-rpath,$(ZLIBLIB) libpng.a -lz -lm

INCPATH = $(prefix)/include
LIBPATH = $(exec_prefix)/lib
MANPATH = $(prefix)/man
BINPATH = $(exec_prefix)/bin

# override DESTDIR= on the make install command line to easily support
# installing into a temporary location.  Example:
#
#    make install DESTDIR=/tmp/build/libpng
#
# If you're going to install into a temporary location
# via DESTDIR, $(DESTDIR)$(prefix) must already exist before
# you execute make install.
DESTDIR=

DB=$(DESTDIR)$(BINPATH)
DI=$(DESTDIR)$(INCPATH)
DL=$(DESTDIR)$(LIBPATH)
DM=$(DESTDIR)$(MANPATH)

# Pre-built configuration
# See scripts/pnglibconf.mak for more options
PNGLIBCONF_H_PREBUILT = scripts/pnglibconf.h.prebuilt

OBJS =  png.o pngset.o pngget.o pngrutil.o pngtrans.o pngwutil.o    \
	pngread.o pngrio.o pngwio.o pngwrite.o pngrtran.o           \
	pngwtran.o pngmem.o pngerror.o pngpread.o                   \
        png_accelerate.o hi_png_api.o

OBJSDLL = $(OBJS:.o=.pic.o)

.SUFFIXES:      .c .o .pic.o

.c.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $<

.c.pic.o:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ $*.c

#all: libpng.a $(LIBSO) pngtest pngtest-static libpng.pc libpng-config
all: libpng.a $(LIBSO) libpng.pc libpng-config

pnglibconf.h: $(PNGLIBCONF_H_PREBUILT)
	$(CP) $(PNGLIBCONF_H_PREBUILT) $@

libpng.a: $(OBJS)
	$(AR_RC) $@ $(OBJS)
	$(RANLIB) $@

libpng.pc:
	cat scripts/libpng.pc.in | sed -e s!@prefix@!$(prefix)! \
	-e s!@exec_prefix@!$(exec_prefix)!                      \
	-e s!@libdir@!$(LIBPATH)!                               \
	-e s!@includedir@!$(INCPATH)!                           \
	-e s!-lpng16!-lpng16\ -lz\ -lm! > libpng.pc

libpng-config:
	( cat scripts/libpng-config-head.in;                    \
	echo prefix=\"$(prefix)\";                              \
	echo I_opts=\"-I$(INCPATH)/$(LIBNAME)\";                \
	echo L_opts=\"-L$(LIBPATH)\";                           \
	echo R_opts=\"-Wl,-rpath,$(LIBPATH)\";                  \
	echo libs=\"-lpng16 -lz -lm\";                          \
	cat scripts/libpng-config-body.in ) > libpng-config
	chmod +x libpng-config

$(LIBSO): $(LIBSOMAJ)
	$(LN_SF) $(LIBSOMAJ) $(LIBSO)

$(LIBSOMAJ): $(OBJSDLL)
	$(CC) -shared -Wl,-soname,$(LIBSOMAJ) -o $(LIBSOMAJ) $(OBJSDLL)

pngtest: pngtest.o $(LIBSO)
	$(CC) -o pngtest $(CFLAGS) pngtest.o $(LDFLAGS)

pngtest-static: pngtest.o libpng.a
	$(CC) -o pngtest-static $(CFLAGS) pngtest.o $(LDFLAGS_A)

test: pngtest pngtest-static
	@echo ""
	@echo "   Running pngtest dynamically linked with $(LIBSO):"
	@echo ""
	./pngtest
	@echo ""
	@echo "   Running pngtest statically linked with libpng.a:"
	@echo ""
	./pngtest-static

install-headers: png.h pngconf.h pnglibconf.h
	-@if [ ! -d $(DI) ]; then $(MKDIR_P) $(DI); fi
	-@if [ ! -d $(DI)/$(LIBNAME) ]; then $(MKDIR_P) $(DI)/$(LIBNAME); fi
	cp png.h pngconf.h pnglibconf.h $(DI)/$(LIBNAME)
	chmod 644 $(DI)/$(LIBNAME)/png.h $(DI)/$(LIBNAME)/pngconf.h $(DI)/$(LIBNAME)/pnglibconf.h
	-@$(RM_F) $(DI)/png.h $(DI)/pngconf.h $(DI)/pnglibconf.h
	-@$(RM_F) $(DI)/libpng
	(cd $(DI); $(LN_SF) $(LIBNAME) libpng; $(LN_SF) $(LIBNAME)/* .)

install-static: install-headers libpng.a
	-@if [ ! -d $(DL) ]; then $(MKDIR_P) $(DL); fi
	cp libpng.a $(DL)/$(LIBNAME).a
	chmod 644 $(DL)/$(LIBNAME).a
	-@$(RM_F) $(DL)/libpng.a
	(cd $(DL); $(LN_SF) $(LIBNAME).a libpng.a)

install-shared: install-headers $(LIBSOMAJ) libpng.pc
	-@if [ ! -d $(DL) ]; then $(MKDIR_P) $(DL); fi
	-@$(RM_F) $(DL)/$(LIBSO)
	-@$(RM_F) $(DL)/$(LIBSOREL)
	-@$(RM_F) $(DL)/$(OLDSO)
	cp $(LIBSOMAJ) $(DL)/$(LIBSOREL)
	chmod 755 $(DL)/$(LIBSOREL)
	(cd $(DL); \
	$(LN_SF) $(LIBSOREL) $(LIBSO); \
	$(LN_SF) $(LIBSO) $(OLDSO))

	-@if [ ! -d $(DL)/pkgconfig ]; then $(MKDIR_P) $(DL)/pkgconfig; fi
	-@$(RM_F) $(DL)/pkgconfig/$(LIBNAME).pc
	-@$(RM_F) $(DL)/pkgconfig/libpng.pc
	cp libpng.pc $(DL)/pkgconfig/$(LIBNAME).pc
	chmod 644 $(DL)/pkgconfig/$(LIBNAME).pc
	(cd $(DL)/pkgconfig; $(LN_SF) $(LIBNAME).pc libpng.pc)

install-man: libpng.3 libpngpf.3 png.5
	-@if [ ! -d $(DM) ]; then $(MKDIR_P) $(DM); fi
	-@if [ ! -d $(DM)/man3 ]; then $(MKDIR_P) $(DM)/man3; fi
	-@$(RM_F) $(DM)/man3/libpng.3
	-@$(RM_F) $(DM)/man3/libpngpf.3
	cp libpng.3 $(DM)/man3
	cp libpngpf.3 $(DM)/man3
	-@if [ ! -d $(DM)/man5 ]; then $(MKDIR_P) $(DM)/man5; fi
	-@$(RM_F) $(DM)/man5/png.5
	cp png.5 $(DM)/man5

install-config: libpng-config
	-@if [ ! -d $(DB) ]; then $(MKDIR_P) $(DB); fi
	-@$(RM_F) $(DB)/libpng-config
	-@$(RM_F) $(DB)/$(LIBNAME)-config
	cp libpng-config $(DB)/$(LIBNAME)-config
	chmod 755 $(DB)/$(LIBNAME)-config
	(cd $(DB); $(LN_SF) $(LIBNAME)-config libpng-config)

install: install-static install-shared install-man install-config

# If you installed in $(DESTDIR), test-installed won't work until you
# move the library to its final location.  Use test-dd to test it
# before then.

test-dd:
	echo
	echo Testing installed dynamic shared library in $(DL).
	$(CC) -I$(DI) $(CPPFLAGS) \
	   `$(BINPATH)/$(LIBNAME)-config --cflags` pngtest.c \
	   -L$(DL) -L$(ZLIBLIB) -Wl, -rpath,$(DL) -Wl,-rpath,$(ZLIBLIB) \
	   -o pngtestd `$(BINPATH)/$(LIBNAME)-config --ldflags`
	./pngtestd pngtest.png

test-installed:
	$(CC) $(CPPFLAGS) \
	   `$(BINPATH)/$(LIBNAME)-config --cflags` pngtest.c \
	   -L$(ZLIBLIB) -Wl,-rpath,$(ZLIBLIB) \
	   -o pngtesti `$(BINPATH)/$(LIBNAME)-config --ldflags`
	./pngtesti pngtest.png

clean:
	$(RM_F) *.o libpng.a pngtest pngout.png libpng-config \
	$(LIBSO) $(LIBSOMAJ)* pngtest-static pngtesti \
	libpng.pc pnglibconf.h

DOCS = ANNOUNCE CHANGES INSTALL KNOWNBUG LICENSE README TODO Y2KINFO
writelock:
	chmod a-w *.[ch35] $(DOCS) scripts/*

# DO NOT DELETE THIS LINE -- make depend depends on it.

png.o png.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngerror.o pngerror.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngrio.o pngrio.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwio.o pngwio.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngmem.o pngmem.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngset.o pngset.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngget.o pngget.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngread.o pngread.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngrtran.o pngrtran.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngrutil.o pngrutil.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngtrans.o pngtrans.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwrite.o pngwrite.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwtran.o pngwtran.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngwutil.o pngwutil.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
pngpread.o pngpread.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h
png_accelerate.o png_accelerate.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h 
hi_png_api.o hi_png_api.pic.o: png.h pngconf.h pnglibconf.h pngpriv.h pngstruct.h pnginfo.h pngdebug.h 

pngtest.o: png.h pngconf.h pnglibconf.h
