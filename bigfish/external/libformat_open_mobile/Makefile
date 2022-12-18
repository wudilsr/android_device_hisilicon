######################TOOL CHAINS#########################
ifndef CFG_HI_TOOLCHAINS_NAME
CFG_HI_TOOLCHAINS_NAME   := arm-hisiv200-linux
endif
CROSS_COMPILE :=$(CFG_HI_TOOLCHAINS_NAME)-

export AR=${CFG_HI_TOOLCHAINS_NAME}-ar
export LD=${CFG_HI_TOOLCHAINS_NAME}-ld
export CPP=${CFG_HI_TOOLCHAINS_NAME}-cpp
export CC=${CFG_HI_TOOLCHAINS_NAME}-gcc
export STRIP=${CFG_HI_TOOLCHAINS_NAME}-strip

#########################################################
SO_LIB_FILE := libformat_open.so
FFMPEG_PATH :=../ffmpeg

CFLAGS:= -Wall -O3 -fPIC -Dav_restrict= -DLPCMHTTP_NOTSUPPORT
FO_OBJS := svr_allformat.o hls.o hls_key_decrypt.o hls_read.o http.o tcp.o
FFMPEG_LIBS:= -ldl -lavformat -lavcodec -lavutil
#../../libflac/include/FLAC/ for cue play
FO_INCLUDE := -I. -I$(FFMPEG_PATH) -I$(FFMPEG_PATH)/libavformat/ -I$(FFMPEG_PATH)/libffmpegadp/platform/include/

ifeq ($(HIDOL_PLATFORM),HiSTBLinuxV100R001)
FO_INCLUDE += -I$(FFMPEG_PATH)/libffmpegadp/platform/include/ver_v100r001/
CFLAGS += -DUDF_NOTSUPPORT
ifeq ($(CFG_HI_PLAYER_NORMAL_SUPPORT),y)
CFLAGS += -DNO_LOG -DHTTPSEX_NOTSUPPORT -DHTTPPROXY_NOTSUPPORT -DLPCMHTTP_NOTSUPPORT
endif
ifeq ($(CFG_HI_PLAYER_FULL_SUPPORT),y)
FFMPEG_LIBS += -ltlsadp -lssl -lcrypto
endif
endif

ifeq ($(HIDOL_PLATFORM),HiSTBLinuxV100R002)
FO_OBJS += svr_iso_dec.o svr_udf_protocol.o
FO_INCLUDE += -I$(FFMPEG_PATH)/libffmpegadp/platform/include/ver_v100r002/ -I$(FFMPEG_PATH)/libffmpegadp/libudf
ifeq ($(CFG_HI_PLAYER_FULL_SUPPORT),y)
FFMPEG_LIBS += -ltlsadp -lssl -lcrypto
endif
endif

ifeq ($(HIDOL_PLATFORM),HiSTBLinuxV100R004)
FO_INCLUDE += -I$(FFMPEG_PATH)/libffmpegadp/platform/include/ver_v100r004/
CFLAGS += -DUDF_NOTSUPPORT
ifeq ($(CFG_HI_PLAYER_NORMAL_SUPPORT),y)
CFLAGS += -DNO_LOG -DHTTPSEX_NOTSUPPORT -DHTTPPROXY_NOTSUPPORT -DLPCMHTTP_NOTSUPPORT
endif
ifeq ($(CFG_HI_PLAYER_FULL_SUPPORT),y)
FFMPEG_LIBS += -ltlsadp -lssl -lcrypto
endif
endif

CFLAGS += $(FO_INCLUDE)

FFMPEG_LIB_PATH += -L$(FFMPEG_PATH)/libavformat/
FFMPEG_LIB_PATH += -L$(FFMPEG_PATH)/libavutil/
FFMPEG_LIB_PATH += -L$(FFMPEG_PATH)/libavcodec/
FFMPEG_LIB_PATH += -L$(FFMPEG_PATH)/libswscale/
FFMPEG_LIB_PATH += -L$(FFMPEG_PATH)/libffmpegadp/libtlsadp/
FFMPEG_LIB_PATH += -L$(FFMPEG_PATH)/libffmpegadp/platform/lib/$(CROSS_COMPILE)

all: install
obj:$(FO_OBJS)

install:obj
	$(CC) $(CFLAGS) -shared -o $(SO_LIB_FILE) $(FO_OBJS) $(FFMPEG_LIBS) $(FFMPEG_LIB_PATH)
	cp $(SO_LIB_FILE) $(FFMPEG_PATH)/libffmpegadp/platform/lib/$(CROSS_COMPILE)/ -vf

clean:
	-rm *.o
	-rm $(SO_LIB_FILE)


