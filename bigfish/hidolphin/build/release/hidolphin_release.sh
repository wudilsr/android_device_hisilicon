#!/bin/bash
set -ex
#########################################################################
## return error code
#########################################################################
E_INVAL=22 #Invalid param
E_NOENT=2  #File or directory that does not exist
E_ACCES=13 #Access denied

#BASE_DIR=/home/guanjian/HiSTBAndroidV5/temp/bigfish_basic/release
#HIDOLPHIN_DIR=device/hisilicon/bigfish/hidolphin
#HIDOLPHIN_OUT_DIR=${BASE_DIR}/out/target/product/Hi3716CV200

function abs_dir()
{
    if [ -d $1 ] ; then
        cd $1; pwd; cd - > /dev/null
    else
        echo $1
    fi
}
#HIDOLPHIN_OUT_DIR=`abs_dir $3`

BASE_DIR=$1
HIDOLPHIN_DIR=$2
HIDOLPHIN_OUT_DIR=$3
CHIP_NAME=$4
BASE_NAME=$5

FRONTEND_NOT_SUPPORT1=Hi3798CV100
FRONTEND_NOT_SUPPORT2=Hi3798MV100
FRONTEND_NOT_SUPPORT3=Hi3798MV100_A

if [ "$CHIP_NAME" == "$FRONTEND_NOT_SUPPORT1" ]||[ "$CHIP_NAME" == "$FRONTEND_NOT_SUPPORT2" ]||[ "$CHIP_NAME" == "$FRONTEND_NOT_SUPPORT3" ];then
CFG_HI_FRONTEND_SUPPORT=n;
else
CFG_HI_FRONTEND_SUPPORT=y;
fi

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
component_list+="component/hidlna/android "
else
reserved_component_list+="component/hidlna "
fi

if [ "$CFG_HI_SKYPLAY_SUPPORT" == "y" ];then
component_list+="component/skyplay/android "
else
reserved_component_list+="component/skyplay "
fi

if [ "$CFG_HI_MULTISCREEN_SUPPORT" == "y" ];then
component_list+="component/himultiscreen/android "
else
reserved_component_list+="component/himultiscreen "
fi

if [ "$CFG_HI_MIRACAST_SUPPORT" == "y" ];then
component_list+="component/miracast "
else
reserved_component_list+="component/miracast "
fi

if [ "$CFG_HI_TRANSCODER_SUPPORT" == "y" ];then
component_list+="component/hitranscoder/android "
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
if [ "$CFG_HI_FRONTEND_SUPPORT" == "y" ];then
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
else
reserved_component_list+="component/dtvappfrm "
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

if [ "$CFG_HI_MULTIROOM_SUPPORT" == "y" ];then
component_list+="component/multiroom "
else
reserved_component_list+="component/multiroom "
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



function execute_release_sh()
{
    if [ $# -lt 1 ]; then
    echo "Please input the release sh path"
    exit ${E_INVAL}
    fi

    for releaseSh in $@ ; do
        echo "${releaseSh}/hidolphin_release.sh"
        cd ${BASE_DIR}/${HIDOLPHIN_DIR}
        source ${releaseSh}/hidolphin_release.sh ${BASE_DIR} ${HIDOLPHIN_DIR} ${HIDOLPHIN_OUT_DIR} ${CHIP_NAME} ${BASE_NAME}
    done
}

function rm_release_sh()
{
    if [ $# -lt 1 ]; then
        echo "Please input the release sh path"
        exit ${E_INVAL}
        fi

        cd ${BASE_DIR}/${HIDOLPHIN_DIR}
        for releaseSh in $@ ; do
                echo "rm -fr ${releaseSh}/hidolphin_release.sh"
                rm -fr ${releaseSh}/hidolphin_release.sh
        done
}

function bak_DTV()
{
         cd ${BASE_DIR}/${HIDOLPHIN_DIR}
         mkdir -p hidolphin_dtv/${HIDOLPHIN_DIR}/component
#         mkdir -p hidolphin_dtv/external
         cp -rf ./build hidolphin_dtv/${HIDOLPHIN_DIR}/
         mv ./component/dtvappfrm hidolphin_dtv/${HIDOLPHIN_DIR}/component/
         mv ./component/dtvstack hidolphin_dtv/${HIDOLPHIN_DIR}/component/
#         mv ./component/common hidolphin_dtv/component/
#         mv ./external/iconv hidolphin_dtv/external/
#         cp -f ./build/dtv_patch.sh hidolphin_dtv/
         mv ./build/release/dtv_readme.txt hidolphin_dtv/readme.txt
         find ./hidolphin_dtv -name ".git*" -type d | xargs rm -rf
#         today=`date "+%Y%m%d%H%M%S"`
         cd ${BASE_DIR}/${HIDOLPHIN_DIR}/hidolphin_dtv
         tar -czf ${BASE_DIR}/../${BASE_NAME}_dtv.tar.gz .
         #mv hidolphin_dtv_$today.tar.gz ${BASE_DIR}/..
         rm -rf ${BASE_DIR}/${HIDOLPHIN_DIR}/hidolphin_dtv

#         chmod 777 cfg.mak
#         sed -i 's/CFG_HI_COMMON_SUPPORT=y/#CFG_HI_COMMON_SUPPORT=y/g' cfg.mak
#         sed -i 's/CFG_HI_DTVSTACK_SUPPORT=y/#CFG_HI_DTVSTACK_SUPPORT=y/g' cfg.mak
#         sed -i 's/CFG_HI_DTVAPPFRM_SUPPORT=y/#CFG_HI_DTVAPPFRM_SUPPORT=y/g' cfg.mak

}

function prepare_external_files()
{
    cd ${BASE_DIR}/${HIDOLPHIN_DIR}

    rm -rf external/ffmpeg
    rm -rf external/libdvd
    rm -rf external/libdvd_protocol

    if [ "$CFG_HI_LINUX_PRODUCT" == "y" ]; then
       echo "linux version"
    else
       rm Makefile.* -rf
       rm -f ./Android.mk
       mv -v ./Android.mk.rel ./Android.mk
    fi

    rm hidolphin_debug.sh -rf
#    rm build/release -rf
#    rm sample -rf
    rm test -rf
}

function copy_external_files()
{
    echo "copy external src"

    mv -v external/* ${BASE_DIR}/device/hisilicon/bigfish/external
    rm -rf external
}

echo "hidolphin release begin"

cd ${BASE_DIR}/${HIDOLPHIN_DIR}

if [ "$CFG_STB_Android4_0_UNF3_0" == "y" ];then
rm_reserved_components ${reserved_component_list}
rm_reserved_thirdparty ${reserved_thirdparty_list}
rm_menuconfig

execute_release_sh ${component_list}
rm_release_sh ${component_list}

prepare_external_files

else
rm_reserved_components ${reserved_component_list}
rm_reserved_thirdparty ${reserved_thirdparty_list}
rm_menuconfig

execute_release_sh ${component_list}
rm_release_sh ${component_list}

if [ "$CFG_HI_FRONTEND_SUPPORT" == "y" ];then
if [ "$CFG_HI_DTVAPPFRM_SUPPORT" == "y" ];then
bak_DTV
fi
fi

prepare_external_files
copy_external_files
fi

echo "hidolphin release end"
