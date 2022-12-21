#!/bin/bash

ChipName=UnknowChip
cd ${ANDROID_BUILD_TOP}
if [ "$TARGET_PRODUCT" == "Hi3716CV200" ]; then
	ChipName=hi3716cv200
elif [ "$TARGET_PRODUCT" == "Hi3719CV100" ]; then
	ChipName=hi3719cv100
elif [ "$TARGET_PRODUCT" == "Hi3719MV100" ]; then
	ChipName=hi3719mv100
elif [ "$TARGET_PRODUCT" == "Hi3716MV400" ]; then
	ChipName=hi3716mv400
else
	echo "Sorry, $TARGET_PRODUCT isn't supported! "
	exit 1
fi

HISI_SDK_ANDROID_CFG=` grep "HISI_SDK_ANDROID_CFG "  ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/BoardConfig.mk |cut -d =  -f2 | tr -d ' '`
sed -i '/^.*CFG_HI_ADVCA_SUPPORT is not set*/c\CFG_HI_ADVCA_SUPPORT=y\nCFG_ADVCA_OTHER=y\nCFG_HI_ADVCA_TYPE=OTHER' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/configs/$ChipName/$HISI_SDK_ANDROID_CFG
sed -i '/^.*# CFG_HI_BOOT_COMPRESSED is not set*/c\CFG_HI_BOOT_COMPRESSED=y' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/configs/$ChipName/$HISI_SDK_ANDROID_CFG
sed -i 's/^.*ext4@system.*/\    mount ext4 ext4@system \/system ro rro/g' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/etc/init.rc
sed -i 's/20M(misc),500M(system)/20M(misc),4M(systemsign),500M(system)/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/etc/bootargs_$TARGET_PRODUCT-emmc.txt
sed -i 's/mtd13\/mtdblock13 Ubifs=ubi3_0/mtd14\/mtdblock14 Ubifs=ubi3_0/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/etc/vold.fstab
sed -i 's/mmcblk0p16/mmcblk0p17/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/etc/vold.emmc.fstab

sed -i '/PartitionName="systemsign"/d' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/prebuilts/$TARGET_PRODUCT-emmc.xml
sed -i '/PartitionName="misc"/a<Part Sel="1" PartitionName="systemsign" FlashType="emmc" FileSystem="none" Start="210M" Length="4M" SelectFile=""/>' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/prebuilts/$TARGET_PRODUCT-emmc.xml
sed -i 's/Start="210M" Length="500M"/Start="214M" Length="500M"/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/prebuilts/$TARGET_PRODUCT-emmc.xml
sed -i 's/Start="710M" Length="1024M"/Start="714M" Length="1024M"/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/prebuilts/$TARGET_PRODUCT-emmc.xml
sed -i 's/Start="1734M" Length="100M"/Start="1738M" Length="100M"/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/prebuilts/$TARGET_PRODUCT-emmc.xml
sed -i 's/Start="1834M" Length="-"/Start="1838M" Length="-"/g' ${ANDROID_BUILD_TOP}/device/hisilicon/$TARGET_PRODUCT/prebuilts/$TARGET_PRODUCT-emmc.xml

sed -i '/update\/update.zip /a\\t$(hide) cp -a $(EMMC_PRODUCT_OUT)/update/file/META-INF.zip  $(EMMC_PRODUCT_OUT)/' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/build/emmc.mk
sed -i '/update\/update.zip /a\\t$(hide) (cd $(EMMC_PRODUCT_OUT)/update/file && zip -ry META-INF.zip META-INF/*)' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/build/emmc.mk
sed -i '/update\/update.zip /a\\t$(hide) cp -a $(TOPDIR)bootable/recovery/etc/META-INF/com/google/android/updater-script-ca-emmc $(EMMC_PRODUCT_OUT)/update/file/META-INF/com/google/android/updater-script' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/build/emmc.mk
sed -i '/update\/update.zip /d' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/build/emmc.mk

CFG_HI_CHIP_TYPE=` grep "CFG_HI_CHIP_TYPE"  ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/configs/$ChipName/$HISI_SDK_ANDROID_CFG |cut -d =  -f2 | tr -d ' '`
sed -i '/CONFIG_CA_RUNTIME_CHECK/d' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_defconfig
sed -i '/CONFIG_CA_WARKUP_CHECK/d' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_defconfig
sed -i 's/^.*CONFIG_SUPPORT_CA is not set*/CONFIG_SUPPORT_CA=y/g' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_defconfig
sed -i '/^.*CONFIG_DSP_RUN_MEM_SIZE*/a\CONFIG_CA_RUNTIME_CHECK=y\nCONFIG_CA_WARKUP_CHECK=y' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_defconfig

sed -i '/CONFIG_CA_RUNTIME_CHECK/d' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_dbg_defconfig
sed -i '/CONFIG_CA_WARKUP_CHECK/d' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_dbg_defconfig
sed -i 's/^.*CONFIG_SUPPORT_CA is not set*/CONFIG_SUPPORT_CA=y/g' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_dbg_defconfig
sed -i '/^.*CONFIG_DSP_RUN_MEM_SIZE*/a\CONFIG_CA_RUNTIME_CHECK=y\nCONFIG_CA_WARKUP_CHECK=y' ${ANDROID_BUILD_TOP}/device/hisilicon/bigfish/sdk/source/kernel/linux-3.10.y/arch/arm/configs/${CFG_HI_CHIP_TYPE}_android_dbg_defconfig

