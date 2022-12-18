#!/bin/bash
set -ex
#########################################################################
## return error code
#########################################################################
E_INVAL=22 #Invalid param
E_NOENT=2  #File or directory that does not exist
E_ACCES=13 #Access denied

BASE_DIR=$(dirname $(pwd))
HIDOLPHIN_DIR=$(basename $(pwd))

source  ${BASE_DIR}/${HIDOLPHIN_DIR}/cfg.mak

#######################################
##config components
######################################

component_list=""
reserved_component_list=""

if [ "$CFG_HI_BASE_SUPPORT" == "y" ];then
component_list+="component/base "
else
reserved_component_list+="component/base "
fi

if [ "$CFG_HI_DLNA_SUPPORT" == "y" ];then
component_list+="component/hidlna "
else
reserved_component_list+="component/hidlna "
fi

if [ "$CFG_HI_SKYPLAY_SUPPORT" == "y" ];then
component_list+="component/skyplay "
else
reserved_component_list+="component/skyplay "
fi

if [ "$CFG_HI_MULTISCREEN_SUPPORT" == "y" ];then
component_list+="component/himultiscreen "
else
reserved_component_list+="component/himultiscreen "
fi

if [ "$CFG_HI_MIRACAST_SUPPORT" == "y" ];then
component_list+="component/miracast "
else
reserved_component_list+="component/miracast "
fi

if [ "$CFG_HI_TRANSCODER_SUPPORT" == "y" ];then
component_list+="component/hitranscoder "
else
reserved_component_list+="component/hitranscoder "
fi

if [ "$CFG_HI_PLAYER_SUPPORT" == "y" ];then
component_list+="component/player "
else
reserved_component_list+="component/player "
fi

if [ "$CFG_HI_CHARSET_SUPPORT" == "y" ];then
component_list+="component/charset "
else
reserved_component_list+="component/charset "
fi

if [ "$CFG_HI_DRMENGINE_SUPPORT" == "y" ];then
component_list+="component/drmengine "
else
reserved_component_list+="component/drmengine "
fi

if [ "$CFG_HI_DTVAPPFRM_SUPPORT" == "y" ];then
component_list+="component/dtvappfrm "
else
reserved_component_list+="component/dtvappfrm "
fi

if [ "$CFG_HI_DTVSTACK_SUPPORT" == "y" ];then
component_list+="component/dtvstack "
else
reserved_component_list+="component/dtvstack "
fi

if [ "$CFG_HI_COMMON_SUPPORT" == "y" ];then
component_list+="component/common "
else
reserved_component_list+="component/common "
fi

if [ "$CFG_HI_BROWSER_SUPPORT" == "y" ];then
component_list+="component/browser "
else
reserved_component_list+="component/browser "
fi

###############################################
##config third-party lib
##############################################
thirdparty_list=""
reserved_thirdparty_list=""

if [ "$CFG_HI_ICONV_SUPPORT" == "y" ];then
thirdparty_list+="external/iconv "
else
reserved_thirdparty_list+="external/iconv "
fi

if [ "$CFG_HI_FFMPEG_SUPPORT" == "y" ];then
thirdparty_list+="external/ffmpeg "
else
reserved_thirdparty_list+="external/ffmpeg "
fi

if [ "$CFG_HI_LIBBLURAY_SUPPORT" == "y" ];then
thirdparty_list+="external/libbluray "
else
reserved_thirdparty_list+="external/libbluray "
fi

if [ "$CFG_HI_DVD_SUPPORT" == "y" ];then
thirdparty_list+="external/libdvd "
else
reserved_thirdparty_list+="external/libdvd "
fi

if [ "$CFG_HI_LIBDVD_PROTOCOL_SUPPORT" == "y" ];then
thirdparty_list+="external/libdvd_protocol "
else
reserved_thirdparty_list+="external/libdvd_protocol "
fi

if [ "$CFG_HI_LIBUPNP_SUPPORT" == "y" ];then
thirdparty_list+="external/libupnp "
else
reserved_thirdparty_list+="external/libupnp "
fi

if [ "$CFG_HI_BONJOUR_SUPPORT" == "y" ];then
thirdparty_list+="external/bonjour "
else
reserved_thirdparty_list+="external/bonjour "
fi

if [ "$CFG_HI_LIBDAAP_SUPPORT" == "y" ];then
thirdparty_list+="external/libdaap "
else
reserved_thirdparty_list+="external/libdaap "
fi

if [ "$CFG_HI_PLIST_SUPPORT" == "y" ];then
thirdparty_list+="external/plist "
else
reserved_thirdparty_list+="external/plist "
fi

if [ "$CFG_HI_CURL_SUPPORT" == "y" ];then
thirdparty_list+="external/curl "
else
reserved_thirdparty_list+="external/curl "
fi

if [ "$CFG_HI_CLINK_SUPPORT" == "y" ];then
thirdparty_list+="external/clink "
else
reserved_thirdparty_list+="external/clink "
fi

if [ "$CFG_HI_HTTPSERVER_SUPPORT" == "y" ];then
thirdparty_list+="external/http_server "
else
reserved_thirdparty_list+="external/http_server "
fi

if [ "$CFG_HI_OPENSSL_SUPPORT" == "y" ];then
thirdparty_list+="external/openssl "
else
reserved_thirdparty_list+="external/openssl "
fi

if [ "$CFG_HI_RTPRTCPPARSE_SUPPORT" == "y" ];then
thirdparty_list+="external/rtp_rtcp_parse "
else
reserved_thirdparty_list+="external/rtp_rtcp_parse "
fi

if [ "$CFG_HI_RTSPSERVER_SUPPORT" == "y" ];then
thirdparty_list+="external/rtsp_server "
else
reserved_thirdparty_list+="external/rtsp_server "
fi

#################################################
if [ "$CFG_HI_HIGV_SUPPORT" == "y" ];then
component_list+="component/higv "
else
reserved_component_list+="component/higv "
fi

if [ "$CFG_HI_MULTIROOM_CLIENT_SUPPORT" == "y" ];then
component_list+="component/multiroom/client "
else
reserved_component_list+="component/multiroom/client "
fi

if [ "$CFG_HI_SMOOTHSTREAMING_SUPPORT" == "y" ];then
component_list+="component/smoothstreaming "
else
reserved_component_list+="component/smoothstreaming "
fi

reserved_component_list+="component/player_3720x "

################################################
################################################
if [ "$CFG_HI_XWINDOW_SUPPORT" == "y" ];then
thirdparty_list+="external/xwindow "
else
reserved_thirdparty_list+="external/xwindow "
fi

if [ "$CFG_HI_LIBANDROIDBEAN_SUPPORT" == "y" ];then
thirdparty_list+="external/libandroid_bean "
else
reserved_thirdparty_list+="external/libandroid_bean "
fi

if [ "$CFG_HI_GSTREAMER_SUPPORT" == "y" ];then
thirdparty_list+="external/gstreamer "
else
reserved_thirdparty_list+="external/gstreamer "
fi

if [ "$CFG_HI_LIBFLAC_SUPPORT" == "y" ];then
thirdparty_list+="external/libflac "
else
reserved_thirdparty_list+="external/libflac "
fi

if [ "$CFG_HI_LIBCLIENTADP_SUPPORT" == "y" ];then
thirdparty_list+="external/libclientadp "
else
reserved_thirdparty_list+="external/libclientadp "
fi

reserved_thirdparty_list+="external/ffmpeg-mini "

reserved_thirdparty_list+="external/libbluray-0.2.2 "

###############################################


function rm_reserved_components()
{
	if [ $# -lt 1 ]; then
	    echo "Please input reserved components path"
	else
        cd ${BASE_DIR}/${HIDOLPHIN_DIR}
	    for componentDir in $@ ; do
		    echo "rm ${componentDir}"
		    rm -rf ${componentDir}
	    done
	fi
}

function rm_reserved_thirdparty()
{
	if [ $# -lt 1 ]; then
        echo "Please input reserved thirdparty path"
    else
        cd ${BASE_DIR}/${HIDOLPHIN_DIR}
        for thirdpartyDir in $@ ; do
            echo "rm ${thirdpartyDir}"
            rm -fr ${thirdpartyDir}
        done
	fi
}

function rm_menuconfig()
{
    cd ${BASE_DIR}/${HIDOLPHIN_DIR}
	rm -rf ./build/tools
	rm -rf ./build/scripts
	rm -rf Makefile
}

function prepare_build_files()
{
    cd ${BASE_DIR}/${HIDOLPHIN_DIR}

    if [ "$CFG_HI_LINUX_PRODUCT" == "y" ]; then
       rm Android.* -rf
	   mv Makefile.orig Makefile
	else
	   rm Makefile.* -rf
	fi

# 	rm hidolphin_release.sh -rf
#    rm build/release -rf

#	rm sample -rf
	rm test -rf
}

echo "hidolphin release begin (source version)"

cd ${BASE_DIR}/${HIDOLPHIN_DIR}

rm_reserved_components ${reserved_component_list}

rm_reserved_thirdparty ${reserved_thirdparty_list}

rm_menuconfig

prepare_build_files

echo "hidolphin release end (source version)"
