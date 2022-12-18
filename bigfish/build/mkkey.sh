#!/bin/sh

HISI_KEY_DIRECTORY=$ANDROID_BUILD_TOP/device/hisilicon/$TARGET_PRODUCT/security
DEV_TOOLS_DIRECTORY=$ANDROID_BUILD_TOP/development/tools
HISI_OTA_SECURITY=$ANDROID_BUILD_TOP/device/hisilicon/bigfish/upgrade/ota/security
if [ ! -d $HISI_KEY_DIRECTORY ]; then
    mkdir -p $HISI_KEY_DIRECTORY
fi

AUTH='/C=CN/ST=Guangdong/L=Shenzhen/O=Android/OU=Android/CN=Android/emailAddress=android@android.com'

function getAuthInfo()
{
    if [ "$1" ] ; then
        AUTH=$1
    else
        echo "Warning: No input parameter, so the default authentication info will be used!"
    fi
}

getAuthInfo $1
sh $DEV_TOOLS_DIRECTORY/make_key $HISI_KEY_DIRECTORY/releasekey $AUTH
sh $DEV_TOOLS_DIRECTORY/make_key $HISI_KEY_DIRECTORY/media $AUTH
sh $DEV_TOOLS_DIRECTORY/make_key $HISI_KEY_DIRECTORY/platform $AUTH
sh $DEV_TOOLS_DIRECTORY/make_key $HISI_KEY_DIRECTORY/shared $AUTH
echo "Security Update Ota Key!"
rm -rf $HISI_OTA_SECURITY/*
cp -avf $HISI_KEY_DIRECTORY/media.pk8 $HISI_OTA_SECURITY/media.pk8
cp -avf $HISI_KEY_DIRECTORY/media.x509.pem $HISI_OTA_SECURITY/media.x509.pem
cp -avf $HISI_KEY_DIRECTORY/platform.pk8 $HISI_OTA_SECURITY/platform.pk8
cp -avf $HISI_KEY_DIRECTORY/platform.x509.pem $HISI_OTA_SECURITY/platform.x509.pem
cp -avf $HISI_KEY_DIRECTORY/shared.pk8 $HISI_OTA_SECURITY/shared.pk8
cp -avf $HISI_KEY_DIRECTORY/shared.x509.pem $HISI_OTA_SECURITY/shared.x509.pem
cp -avf $HISI_KEY_DIRECTORY/releasekey.pk8 $HISI_OTA_SECURITY/testkey.pk8
cp -avf $HISI_KEY_DIRECTORY/releasekey.x509.pem $HISI_OTA_SECURITY/testkey.x509.pem
