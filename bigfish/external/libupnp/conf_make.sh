#./configure --disable-samples --disable-debug --host=arm-hisiv200-linux
#all: make_sh repair_libtool
all: make_sh
.PHONY: make_sh
make_sh:
	./configure_linux --disable-samples --enable-debug CFLAGS="-W -Wall -D_LARGEFILE64_SOURCE=1 -D_REENTRANT -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64 -O3 " --host=arm-hisiv200-linux

#repair_libtool:make_sh
#	cp   ./libtool  libtool.err
#	sed -i s///g ./libtool
