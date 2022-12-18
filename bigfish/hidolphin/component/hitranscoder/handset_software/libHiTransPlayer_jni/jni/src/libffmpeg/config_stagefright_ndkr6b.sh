#!/bin/sh
PREBUILT=/root/android-ndk-r6b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/linux-x86
PLATFORM=/root/android-ndk-r6b/platforms/android-8/arch-arm

./configure --target-os=linux \
--arch=arm \
--enable-version3 \
--enable-gpl \
--enable-nonfree \
--enable-network \
--enable-memalign-hack \
--enable-pthreads \
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
--disable-decoder=h264 \
--disable-decoder=h264_vdpau \
--enable-cross-compile \
--cc=$PREBUILT/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/bin/arm-linux-androideabi- \
--sysroot=$PLATFORM \
--sysinclude=$PLATFORM/usr/include \
--nm=$PREBUILT/bin/arm-linux-androideabi-nm \
--extra-cflags="-fPIC -DANDROID" \
--enable-static \
--disable-shared \
--disable-asm \
--disable-yasm \
--enable-neon \
--enable-armv5te \
--extra-ldflags="-Wl,-T,$PREBUILT/arm-linux-androideabi/lib/ldscripts/armelf_linux_eabi.x -Wl,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtbegin.o $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtend.o -lc -lm -ldl"
