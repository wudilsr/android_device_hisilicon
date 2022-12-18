#!/bin/sh
##--disable-decoder=h264 \
##--disable-decoder=h264_vdpau
PREBUILT=D:/android-ndk-r7b/toolchains/arm-linux-androideabi-4.4.3/prebuilt/windows
PLATFORM=D:/android-ndk-r7b/platforms/android-14/arch-arm
CONFIG_FOR_EMULATOR=0
CONFIG_FOR_XOOM=0
CONFIG_FOR_A9=1
if [ $CONFIG_FOR_EMULATOR -eq 1 ]
then
./configure --target-os=linux \
--arch=arm \
--enable-static \
--enable-version3 \
--enable-gpl \
--enable-nonfree \
--enable-network \
--enable-memalign-hack \
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
--disable-shared \
--disable-asm \
--disable-yasm \
--enable-cross-compile \
--cross-prefix=arm-linux-androideabi- \
--cc=$PREBUILT/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/bin/arm-linux-androideabi- \
--sysroot=$PLATFORM \
--sysinclude=$PLATFORM/usr/include \
--nm=$PREBUILT/bin/arm-linux-androideabi-nm \
--extra-cflags=" -O3 -fPIC -DANDROID" \
--extra-ldflags="-Wl,-T,$PREBUILT/arm-linux-androideabi/lib/ldscripts/armelf_linux_eabi.x -Wl,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtbegin.o $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtend.o -lc -lm -ldl"
else
if [ $CONFIG_FOR_XOOM -eq 1 ]
then
./configure --target-os=linux \
--arch=armv7-a \
--enable-static \
--enable-version3 \
--enable-gpl \
--enable-nonfree \
--enable-network \
--enable-memalign-hack \
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
--cross-prefix=arm-linux-androideabi- \
--cc=$PREBUILT/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/bin/arm-linux-androideabi- \
--sysroot=$PLATFORM \
--sysinclude=$PLATFORM/usr/include \
--nm=$PREBUILT/bin/arm-linux-androideabi-nm \
--extra-cflags=" -march=armv7-a -mtune=cortex-a9 -O3 -mfloat-abi=softfp -mfpu=vfp -DHAVE_NEON=1 -fPIC -DANDROID" \
--extra-ldflags="-Wl,-T,$PREBUILT/arm-linux-androideabi/lib/ldscripts/armelf_linux_eabi.x -Wl,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtbegin.o $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtend.o -lc -lm -ldl"
else
if [ $CONFIG_FOR_A9 -eq 1 ]
then
./configure --target-os=linux \
--arch=armv7-a \
--enable-static \
--enable-version3 \
--enable-gpl \
--enable-nonfree \
--enable-network \
--enable-memalign-hack \
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
--cross-prefix=arm-linux-androideabi- \
--cc=$PREBUILT/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/bin/arm-linux-androideabi- \
--sysroot=$PLATFORM \
--sysinclude=$PLATFORM/usr/include \
--nm=$PREBUILT/bin/arm-linux-androideabi-nm \
--extra-cflags=" -O3 -march=armv7-a -mtune=cortex-a9 -mfpu=neon -ffast-math -mfloat-abi=softfp -ftree-vectorize -mvectorize-with-neon-quad -fsingle-precision-constant -mlong-calls -fstrict-aliasing -fprefetch-loop-arrays -fPIC -DANDROID" \
--extra-ldflags="-Wl,-T,$PREBUILT/arm-linux-androideabi/lib/ldscripts/armelf_linux_eabi.x -Wl,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtbegin.o $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtend.o -lc -lm -ldl"
else
./configure --target-os=linux \
--arch=armv7-a \
--enable-static \
--enable-version3 \
--enable-gpl \
--enable-nonfree \
--enable-network \
--enable-memalign-hack \
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
--cross-prefix=arm-linux-androideabi- \
--cc=$PREBUILT/bin/arm-linux-androideabi-gcc \
--cross-prefix=$PREBUILT/bin/arm-linux-androideabi- \
--sysroot=$PLATFORM \
--sysinclude=$PLATFORM/usr/include \
--nm=$PREBUILT/bin/arm-linux-androideabi-nm \
--extra-cflags=" -O3 -march=armv7-a -mtune=cortex-a8 -mfpu=neon -ffast-math -mfloat-abi=softfp -ftree-vectorize -mvectorize-with-neon-quad -fsingle-precision-constant -mlong-calls -fstrict-aliasing -fprefetch-loop-arrays -fPIC -DANDROID" \
--extra-ldflags="-Wl,-T,$PREBUILT/arm-linux-androideabi/lib/ldscripts/armelf_linux_eabi.x -Wl,-rpath-link=$PLATFORM/usr/lib -L$PLATFORM/usr/lib -nostdlib $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtbegin.o $PREBUILT/lib/gcc/arm-linux-androideabi/4.4.3/crtend.o -lc -lm -ldl"
fi
fi
fi