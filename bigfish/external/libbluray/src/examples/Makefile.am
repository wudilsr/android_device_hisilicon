SET_FEATURES = -D_ISOC99_SOURCE -D_POSIX_C_SOURCE=200112L -D_REENTRANT
SET_INCLUDES = -I$(top_srcdir) -I$(top_srcdir)/src -I$(top_srcdir)/src/file -I$(top_srcdir)/src/libbluray/bdnav

AM_CFLAGS = -std=c99 $(SET_FEATURES) $(SET_INCLUDES)

if USING_EXAMPLES

noinst_PROGRAMS=bdsplice mpls_dump clpi_dump index_dump mobj_dump sound_dump \
    libbluray_test list_titles hdmv_test
bin_PROGRAMS=bd_info

BLURAY_LIB = $(top_builddir)/src/libbluray.la

if USING_BDJAVA
  AM_CFLAGS += @BDJAVA_CFLAGS@
endif

bdsplice_SOURCES = \
	bdsplice.c util.c util.h

bdsplice_LDADD = $(BLURAY_LIB)

mpls_dump_SOURCES = \
	mpls_dump.c util.c util.h \
	../util/bits.c \
	../util/strutl.c \
	../util/logging.c \
	../file/file_posix.c \
	../file/dir_posix.c \
	../libbluray/bdnav/extdata_parse.c \
	../libbluray/bdnav/mpls_parse.c \
	../libbluray/bdnav/clpi_parse.c \
	../libbluray/bdnav/navigation.c

clpi_dump_SOURCES = \
	clpi_dump.c util.c util.h \
	../util/bits.c \
	../util/logging.c \
	../file/file_posix.c \
	../libbluray/bdnav/extdata_parse.c \
	../libbluray/bdnav/clpi_parse.c

sound_dump_SOURCES = \
	sound_dump.c \
	../util/bits.c \
	../util/logging.c \
	../file/file_posix.c \
	../libbluray/bdnav/sound_parse.c

index_dump_SOURCES = \
	index_dump.c \
	../util/bits.c \
	../util/logging.c \
	../file/file_posix.c \
	../libbluray/bdnav/index_parse.c

mobj_dump_SOURCES = \
	mobj_dump.c \
	../util/bits.c \
	../util/logging.c \
	../file/file_posix.c \
	../libbluray/hdmv/mobj_parse.c \
	../libbluray/hdmv/mobj_print.c

libbluray_test_SOURCES = \
	libbluray_test.c ../util/logging.c

libbluray_test_LDADD = $(BLURAY_LIB)

hdmv_test_SOURCES = \
	hdmv_test.c

hdmv_test_LDADD = $(BLURAY_LIB)

list_titles_SOURCES = \
	list_titles.c ../util/logging.c

list_titles_LDADD = $(BLURAY_LIB)

bd_info_SOURCES = \
	bd_info.c

bd_info_LDADD = $(BLURAY_LIB)

if USING_BDJAVA
noinst_PROGRAMS+= bdj_test
bdj_test_SOURCES = bdj_test.c
bdj_test_LDADD = $(BLURAY_LIB)
endif

endif
