#!/bin/sh
PREBUILT=/root/android-ndk-r4/build/prebuilt/linux-x86/arm-eabi-4.4.0
PLATFORM=/root/android-ndk-r4/build/platforms/android-8/arch-arm

./configure --target-os=linux \
--arch=arm \
--enable-version3 \
--enable-gpl \
--enable-nonfree \
--enable-network \
--disable-debug \
--disable-ffmpeg \
--disable-ffplay \
--disable-ffserver \
--disable-ffprobe \
--disable-encoders \
--disable-muxers \
--disable-devices \
--disable-avfilter \
--disable-avdevice \
--disable-zlib \
--enable-cross-compile \
--cc=$PREBUILT/bin/arm-eabi-gcc \
--cross-prefix=$PREBUILT/bin/arm-eabi- \
--sysroot=$PLATFORM \
--sysinclude=$PLATFORM/usr/include \
--nm=$PREBUILT/bin/arm-eabi-nm \
--extra-cflags="-fPIC -DANDROID" \
--enable-static \
--disable-shared \
--disable-asm \
--disable-yasm \
--enable-neon \
--enable-armv5te \
--extra-ldflags="-Wl,-T,$PREBUILT/arm-eabi/lib/ldscripts/armelf.x -Wl,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib $PREBUILT/lib/gcc/arm-eabi/4.4.0/crtbegin.o $PREBUILT/lib/gcc/arm-eabi/4.4.0/crtend.o -lc -lm -ldl"
