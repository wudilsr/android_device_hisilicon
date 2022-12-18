#前面带点表示该脚本中的所有设置在之后的编译过程中有效
. ./Kbuild
#/*====================================================================
#确认dfb依赖的库是否编译 -n表示紧接着后面显示
#/*====================================================================
echo ""
echo "====================================================================================="
echo -n "The pub/libs whether have exist libs of jpeg/png/freetype/zlib:(1)no (2)yes:"
read ifcompiled
echo "====================================================================================="
echo ""
if [ $ifcompiled = "1" ]
  then
    exit 0
fi

echo "====================================================================================="
echo -n "please select the process type:(1)multi (2)single:"
read processtype
echo -n "please select the compile type:(1)debug (2)release:"
read compiletype
echo "====================================================================================="
echo ""

export CC=${CROSS}-gcc
export CXX=${CROSS}-g++
export ARCH=arm

ROOT_DIR=$PWD

INSTALL_DIR=$ROOT_DIR/directfb
SDK_LIB_DIR=$ROOT_DIR/../../../pub/lib/
SAMPLE_DIR=$ROOT_DIR/sample

USER_CFLAGS="-DPNG_ACCELERATION -DLIBPNG14"
JPEG_CFLAGS="-DJPEG_LITTLE_ENDIAN"

mkdir -p $INSTALL_DIR/
mkdir -p $INSTALL_DIR/lib
mkdir -p $INSTALL_DIR/bin
mkdir -p $INSTALL_DIR/include

export CPPFLAGS="-I${INSTALL_DIR}/include -I${ROOT_DIR}/../../../pub/include -I${ROOT_DIR}/../../../pub/include/freetype2 -I${ROOT_DIR}/../../../source/msp/drv/include/ -I${ROOT_DIR}/../../../source/msp/api/include/ -I${ROOT_DIR}/../../../source/msp/api/png/release/include -I${SDK_MSP_DIR}/api/png/libpng-1.4.0 -I${SDK_MSP_DIR}/api/jpeg/jpeg6b/include -I${SDK_MSP_DIR}/include"
export LDFLAGS="-L${INSTALL_DIR}/lib -L${SDK_LIB_DIR}/share -L${SDK_LIB_DIR}/static"
export LIBS="-ljpeg -lpng -lfreetype -lhi_msp -lhi_common -lrt -lm -lz -lstdc++ -lpthread -ldl -lhi_msp  -lpthread -ldl"
export CFLAGS="$USER_CFLAGS $EXTRA_FLAGS $JPEG_CFLAGS $CFG_HI_KEYLED"
export CXXFLAGS="$USER_CFLAGS $EXTRA_FLAGS $JPEG_CFLAGS $CFG_HI_KEYLED"

export LIBJPEG=libjpeg
#obg
export LIBPNG_CFLAGS=-I${SDK_LIB_DIR}/include
export LIBPNG_LIBS=-lpng
#freetype
export FREETYPE_CFLAGS=-I${SDK_LIB_DIR}/include/freetype2 
export FREETYPE_LIBS=-lfreetype

#/*====================================================================
#compile dfb lib
#/*====================================================================
if [ ${BUILD_DIRECTFB} = "1" ]
   then
   
   if [ $processtype = "1" ]
      then
        cp $ROOT_DIR/linux-fusion-9.0.2/linux/include/linux $INSTALL_DIR/include -rf
        cd $ROOT_DIR/linux-fusion-9.0.2/
        make clean;make
        cp $ROOT_DIR/linux-fusion-9.0.2/linux/drivers/char/fusion/fusion.ko $INSTALL_DIR/lib -rf
        protype=enable
      else
        protype=disable
   fi

   if [ $compiletype = "1" ]
      then
        comtype=enable
      else
        comtype=disable
   fi
	cd $ROOT_DIR/DirectFB-1.6.1/
	./configure --host=$CROSS --prefix=$INSTALL_DIR --build=x86 --$protype-multi --enable-freetype  --$comtype-debug --with-gfxdrivers=tde --with-inputdrivers=keyboard,linuxinput,lirc,ps2mouse \
 --without-setsockopt --disable-osx --disable-x11 --disable-x11vdpau --disable-mmx --disable-sse --disable-vnc --disable-mesa --disable-devmem  --disable-pnm --disable-mpeg2 --disable-bmp
	make install
fi

#/*====================================================================
#compile dfb example
#/*====================================================================

if [ ${BUILD_DIRECTFB_EXAMPLE} = "1" ]
   then
      export PKG_CONFIG_PATH=$INSTALL_DIR/lib/pkgconfig
      cd $ROOT_DIR/DirectFB-examples-1.6.0
      ./configure --host=$CROSS --prefix=$SAMPLE_DIR
      make install
fi

#/*====================================================================
#compile dfb tests
#/*====================================================================
if [ ${BUILD_DIRECTFB_TEST} = "1" ]
   then
   	export PKG_CONFIG_PATH=$INSTALL_DIR/lib/pkgconfig
	cd $ROOT_DIR/DirectFB-1.6.1/tests/
	make clean;
	make;
	make install
fi
