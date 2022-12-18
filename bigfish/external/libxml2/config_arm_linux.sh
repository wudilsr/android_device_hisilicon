#!/bin/sh
./configure CC=arm-hisiv200-linux-gcc CFLAGS='-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16 -O2' --host=arm-linux --prefix=$PWD/_install --without-python --disable-static --with-history --without-iconv --without-zlib
