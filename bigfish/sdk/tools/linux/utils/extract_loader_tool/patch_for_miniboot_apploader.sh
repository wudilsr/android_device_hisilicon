#!/bin/sh

if [ $# -ne 1 ] ; then
    echo -e "usage: $0 sdk_dir"
    echo -e "        for example: $0 ../HiSTBAndroidV600R001C00SPC061"
    exit 1
fi

SDK_DIR=$1

alias cp=cp

cp -rvf $SDK_DIR/device/hisilicon/bigfish/sdk -drf ./sdk_for_miniboot_apploader

#CFG_FILE="configs/hi3796mv100/hi3796mdmo1a_hi3796mv100_android_vmx_cfg.mak "
CFG_FILE="configs/hi3798mv100/hi3798mdmo_hi3798mv100_android_vmx_cfg.mak "

for i in $CFG_FILE
do
sed -i 's/# CFG_HI_LOADER_SUPPORT is not set/CFG_HI_LOADER_SUPPORT=y/' ./sdk_for_miniboot_apploader/$i
sed -i '/CFG_HI_APPLOADER_SUPPORT=y/,1d' ./sdk_for_miniboot_apploader/$i
sed -i '/CFG_HI_LOADER_SUPPORT/a \CFG_HI_APPLOADER_SUPPORT=y' ./sdk_for_miniboot_apploader/$i
done
