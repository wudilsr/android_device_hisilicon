#!/bin/bash
set -ex

BASE_DIR=$(pwd)
CHIPNAME=${TARGET_PRODUCT}

if [ $0 != "./device/hisilicon/bigfish/build/kernel_module.sh" ]; then
	echo "usage: ./device/hisilicon/bigfish/build/kernel_module.sh"
	exit 1
fi

HISI_SDK_ANDROID_CFG=` grep "HISI_SDK_ANDROID_CFG "  $BASE_DIR/device/hisilicon/$CHIPNAME/BoardConfig.mk |cut -d =  -f2 | tr -d ' '`
ANDROID_KERNEL_CONFIG=`grep "ANDROID_KERNEL_CONFIG " $BASE_DIR/device/hisilicon/$CHIPNAME/BoardConfig.mk |cut -d =  -f2 | tr -d ' '`
HISI_SDK_CFG_DIR=`grep "SDK_CFG_DIR "  $BASE_DIR/device/hisilicon/$CHIPNAME/BoardConfig.mk |cut -d =  -f2 | tr -d ' ' `

###################################################
# 1) close kernel buildin config
# 2) close mce options
# 3) update sdk kernel configs as android
# BoardConfig configs
###################################################
sed -i 's/^.*CFG_HI_MSP_BUILDIN=y.*/\#CFG_HI_MSP_BUILDIN=n/g' $BASE_DIR/device/hisilicon/bigfish/sdk/$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
sed -i 's/^.*CFG_HI_MCE_SUPPORT=y.*/\#CFG_HI_MCE_SUPPORT=n/g' $BASE_DIR/device/hisilicon/bigfish/sdk/$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
sed -i "s/^.*CFG_HI_KERNEL_CFG.*/\CFG_HI_KERNEL_CFG=$ANDROID_KERNEL_CONFIG/g" $BASE_DIR/device/hisilicon/bigfish/sdk/$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
sed -i "s/^.*depends += api/\#depends += api/g" $BASE_DIR/device/hisilicon/bigfish/sdk/source/msp/Makefile

cd $BASE_DIR/device/hisilicon/bigfish/sdk
make linux          SDK_CFGFILE=$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
echo "@@@@@ make linux!"
make common_install SDK_CFGFILE=$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
echo "@@@@@ make common_install!"
make linux_prepare    SDK_CFGFILE=$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
echo "@@@@@ make linux_prepare!"
make msp_install    SDK_CFGFILE=$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
echo "@@@@@ make msp_install!"
make mkload         SDK_CFGFILE=$HISI_SDK_CFG_DIR/$HISI_SDK_ANDROID_CFG
echo "@@@@@ make mkload!"

mkdir -p $BASE_DIR/out/target/product/$CHIPNAME/system/lib/modules
cp -arvf $BASE_DIR/device/hisilicon/bigfish/sdk/pub/kmod/*.ko $BASE_DIR/out/target/product/$CHIPNAME/system/lib/modules
cp -arvf $BASE_DIR/device/hisilicon/bigfish/sdk/pub/kmod/load $BASE_DIR/out/target/product/$CHIPNAME/system/lib/modules
cp -arvf $BASE_DIR/device/hisilicon/bigfish/sdk/pub/kmod/unload $BASE_DIR/out/target/product/$CHIPNAME/system/lib/modules
chmod a+x $BASE_DIR/out/target/product/$CHIPNAME/system/lib/modules/load
chmod a+x $BASE_DIR/out/target/product/$CHIPNAME/system/lib/modules/unload

CHECKINIT_BIGFISH=`grep "cd /system/lib/modules; source ./load; cd -" $BASE_DIR/device/hisilicon/$CHIPNAME/etc/init.$CHIPNAME.sh | tr -d ' '`

if [[ $CHECKINIT_BIGFISH != "" ]]; then
	echo "kernel_module prepare finish!";
	exit 0
else
	echo "cd /system/lib/modules; source ./load; cd -" >> $BASE_DIR/device/hisilicon/$CHIPNAME/etc/init.$CHIPNAME.sh;
	mkdir -p $BASE_DIR/out/target/product/$CHIPNAME/system/etc/;
	cp -arvf $BASE_DIR/device/hisilicon/$CHIPNAME/etc/init.$CHIPNAME.sh $BASE_DIR/out/target/product/$CHIPNAME/system/etc/init.bigfish.sh;
fi

echo "running kernel_module.sh finish !"
