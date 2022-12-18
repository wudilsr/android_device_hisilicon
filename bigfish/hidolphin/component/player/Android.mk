LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)

#LOCAL_PREBUILT_LIBS := lib/libplayer.so \
#	lib/libformat.so \
#	lib/libsubdec.so \
#	lib/libavutil.so \
#	lib/libswscale.so \
#	lib/libtlsadp.so \
#	lib/libavcodec.so \
#	lib/libavformat.so \
#	lib/libffmpegformat.so \
#	lib/libHA.AUDIO.FFMPEG_ADEC.decode.so \
#	lib/libHA.AUDIO.FFMPEG_WMAPRO.decode.so

LOCAL_MODULES_NAME := libplayer  \
	libformat 	\
	libsubdec	\
	libavutil	\
	libswscale	\
	libtlsadp	\
	libavcodec	\
	libavformat	\
	libffmpegformat	\
	libHA.AUDIO.FFMPEG_ADEC.decode	\
	libHV.VIDEO.FFMPEG_VDEC.decode \
	libcachedprotocol \
	libhiplayer_utils

ifeq (STB, $(findstring STB,$(CFG_PRODUCT_LINE)))
LOCAL_MODULES_NAME += libHA.AUDIO.FFMPEG_WMAPRO.decode
endif

define addprefixsuffix_so_list
$(addprefix lib/, $(addsuffix .so, $(1)))
endef

LOCAL_PREBUILT_LIBS := $(call addprefixsuffix_so_list,$(LOCAL_MODULES_NAME))
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULES_NAME)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)
