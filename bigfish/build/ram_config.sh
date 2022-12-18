#!/bin/bash

#HISI_PRODUCT_NAME=$TARGET_PRODUCT
declare -l HISI_PRODUCT_NAME HISI_PRODUCT_ANDROID
HISI_PRODUCT_NAME=${TARGET_PRODUCT}
HISI_PRODUCT_ANDROID=${TARGET_PRODUCT}_android

TARGET_BOARD_CONFIG=$ANDROID_BUILD_TOP/device/hisilicon/$TARGET_PRODUCT/BoardConfig.mk
#echo $TARGET_BOARD_CONFIG

#HISI_SDK_ANDROID_CFG=$(grep -nR "HISI_SDK_ANDROID_CFG :=" device/hisilicon/Hi3716CV200/BoardConfig.mk | awk '{print $3}')
#HISI_SDK_ANDROID_CFG=$(grep -R "HISI_SDK_ANDROID_CFG[[:space:]]*:=" $TARGET_BOARD_CONFIG)
#HISI_SDK_ANDROID_CFG=${HISI_SDK_ANDROID_CFG#*:=[[:space:]]*}
#echo $HISI_SDK_ANDROID_CFG

#HISI_SDK_RECOVERY_CFG=$(grep -nR "HISI_SDK_RECOVERY_CFG[[:space:]]*:=" $TARGET_BOARD_CONFIG)
#HISI_SDK_RECOVERY_CFG=${HISI_SDK_RECOVERY_CFG#*:=[[:space:]]*}
#echo $HISI_SDK_RECOVERY_CFG

#ANDROID_KERNEL_CONFIG=$(grep -nR "ANDROID_KERNEL_CONFIG[[:space:]]*:=" $TARGET_BOARD_CONFIG)
#ANDROID_KERNEL_CONFIG=${ANDROID_KERNEL_CONFIG#*=}
#echo $ANDROID_KERNEL_CONFIG

#RECOVERY_KERNEL_CONFIG=$(grep -nR "RECOVERY_KERNEL_CONFIG[[:space:]]*:=" $TARGET_BOARD_CONFIG)
#RECOVERY_KERNEL_CONFIG=${RECOVERY_KERNEL_CONFIG#*=}
#echo $RECOVERY_KERNEL_CONFIG

function configSDK()
{
    local SDK_CFG HISI_SDK_CFG_PATH
    HISI_SDK_CFG_PATH=$ANDROID_BUILD_TOP/device/hisilicon/bigfish/sdk/configs/$HISI_PRODUCT_NAME
    SDK_CFG=$(find $HISI_SDK_CFG_PATH -name "*$HISI_PRODUCT_ANDROID*")
    echo $SDK_CFG

    echo "change sdk config, set $1, frame buffer is $2"
    sed -i "s/CFG_HI_VDEC_2160P_BUFFER_SIZE=y/\# CFG_HI_VDEC_2160P_BUFFER_SIZE is not set/g" $SDK_CFG
    sed -i "s/CFG_HI_VDEC_MVC_BUFFER_SIZE=y/\# CFG_HI_VDEC_MVC_BUFFER_SIZE is not set/g" $SDK_CFG
    sed -i "s/CFG_HI_VDEC_2_1080P_BUFFER_SIZE=y/\# CFG_HI_VDEC_2_1080P_BUFFER_SIZE is not set/g" $SDK_CFG
    sed -i "s/CFG_HI_VDEC_1080P_BUFFER_SIZE=y/\# CFG_HI_VDEC_1080P_BUFFER_SIZE is not set/g" $SDK_CFG
    #sed -i "s/CFG_HI_VDEC_PRE_FRAMEBUFFER=86/CFG_HI_VDEC_PRE_FRAMEBUFFER=113/g" $SDK_CFG
    #sed -i "s/CFG_HI_VDEC_PRE_FRAMEBUFFER=40/CFG_HI_VDEC_PRE_FRAMEBUFFER=113/g" $SDK_CFG

    sed -i "s/\# $1 is not set/$1=y/g" $SDK_CFG
    #sed -i "s/CFG_HI_VDEC_PRE_FRAMEBUFFER=113/CFG_HI_VDEC_PRE_FRAMEBUFFER=$2/g" $SDK_CFG
}

function configKernel()
{
    local KERNEL_CFG
    HISI_KERNEL_CFG_PATH=$ANDROID_BUILD_TOP/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs
    KERNEL_CFG=$(find $HISI_KERNEL_CFG_PATH -name "*$HISI_PRODUCT_ANDROID*")
    echo $KERNEL_CFG

    echo "set MMZ to $1MB"
    sed -i "s/CONFIG_MMZ_PARAM=\"ddr,0,0,[1-9][0-9][0-9]M\"/CONFIG_MMZ_PARAM=\"ddr,0,0,$1M\"/g" $KERNEL_CFG
    #sed -i "s/CONFIG_MMZ_PARAM=\"ddr,0,0,220M\"/CONFIG_MMZ_PARAM=\"ddr,0,0,320M\"/g" $KERNEL_CFG
    #sed -i "s/CONFIG_MMZ_PARAM=\"ddr,0,0,320M\"/CONFIG_MMZ_PARAM=\"ddr,0,0,$1M\"/g" $KERNEL_CFG
}

function configBootArgs()
{
    local BOOT_ARGS_CFG
    HISI_BOOT_ARGS_CFG_PATH=$ANDROID_BUILD_TOP/device/hisilicon/$TARGET_PRODUCT/etc
    BOOT_ARGS_CFG=$(find $HISI_BOOT_ARGS_CFG_PATH -name "bootargs_$TARGET_PRODUCT-*")
    echo $BOOT_ARGS_CFG
    
    echo "set bootargs to $1"
    sed -i "s/bootargs=mem=512M/bootargs=mem=1G/g" $BOOT_ARGS_CFG
    sed -i "s/bootargs=mem=1G/bootargs=mem=$1/g" $BOOT_ARGS_CFG
}

function configOutOfMemory()
{
    local HISI_BIGFISH_CFG=$ANDROID_BUILD_TOP/device/hisilicon/bigfish/build/device_common.mk
    local OOM_MINFREE_CFG=$ANDROID_BUILD_TOP/frameworks/base/core/res/res/values/config.xml
    #local OOM_MINFREE_CFG=$ANDROID_BUILD_TOP/frameworks/base/services/java/com/android/server/am/ProcessList.java
    
    case $1 in
        512)
            echo "set dalvik to $1"
            sed -i "s/tablet-512-dalvik-heap.mk/tablet-dalvik-heap.mk/g" $HISI_BIGFISH_CFG
            sed -i "s/tablet-dalvik-heap.mk/tablet-$1-dalvik-heap.mk/g" $HISI_BIGFISH_CFG

            #echo "change minfree in 20480, 20480, 28672"
            #sed -i "s/24576, 28672, 32768/20480, 20480, 28672/g" $OOM_MINFREE_CFG
            #sed -i "s/float scale = scaleMem > scaleDisp/float scale = -1;\/\/scaleMem > scaleDisp/g" $OOM_MINFREE_CFG
            echo "change min_free_kbytes from -1 to 24576"
            sed -i "s/<integer name=\"config_lowMemoryKillerMinFreeKbytesAbsolute\">-1<\/integer>/<integer name=\"config_lowMemoryKillerMinFreeKbytesAbsolute\">24576<\/integer>/g" $OOM_MINFREE_CFG

            echo "change extra_free_kbytes from -1 to 636"
            sed -i "s/<integer name=\"config_extraFreeKbytesAbsolute\">-1<\/integer>/<integer name=\"config_extraFreeKbytesAbsolute\">636<\/integer>/g" $OOM_MINFREE_CFG
            ;;
        *)
            echo "set dalvik to null"
            sed -i "s/tablet-512-dalvik-heap.mk/tablet-dalvik-heap.mk/g" $HISI_BIGFISH_CFG

            echo "change min_free_kbytes from 24576 to -1"
            sed -i "s/<integer name=\"config_lowMemoryKillerMinFreeKbytesAbsolute\">24576<\/integer>/<integer name=\"config_lowMemoryKillerMinFreeKbytesAbsolute\">-1<\/integer>/g" $OOM_MINFREE_CFG

            echo "change extra_free_kbytes from 636 to -1"
            sed -i "s/<integer name=\"config_extraFreeKbytesAbsolute\">636<\/integer>/<integer name=\"config_extraFreeKbytesAbsolute\">-1<\/integer>/g" $OOM_MINFREE_CFG
            ;;
    esac
}

function show_help()
{
    echo "RAM config choices:"
    echo "512M              512MB RAM, 1080p + morris"
    echo "MVC               512MB RAM, MVC"
    echo "ALL               1G RAM, 2160p + morris"
    echo
}

function checkEnv()
{
    if [ -z "$ANDROID_BUILD_TOP" ] ; then
        echo "Please load build/envsetup.sh"
        exit
    fi
    
    if [ -z "$TARGET_PRODUCT" ] ; then
        echo "Please lunch TARGET_PRODUCT"
        exit
    fi

    echo "TARGET_PRODUCT=$TARGET_PRODUCT"
    echo $HISI_PRODUCT_NAME
    echo $HISI_PRODUCT_ANDROID
}

case $1 in
    512M)
        checkEnv
        echo "RAM Config: 512MB"
        configSDK CFG_HI_VDEC_1080P_BUFFER_SIZE 40
        configKernel 185
        configBootArgs 512M
        configOutOfMemory 512
        ;;
    MVC)
        checkEnv
        echo "RAM Config: 512MB + MVC"
        configSDK CFG_HI_VDEC_MVC_BUFFER_SIZE 86
        configKernel 240
        configBootArgs 512M
        configOutOfMemory 512
        ;;
    ALL)
        checkEnv
        echo "RAM Config: 1G+"
        configSDK CFG_HI_VDEC_2160P_BUFFER_SIZE 113
        configKernel 320
        configBootArgs 1G
        configOutOfMemory
        ;;
    *)
        show_help
        ;;
esac
