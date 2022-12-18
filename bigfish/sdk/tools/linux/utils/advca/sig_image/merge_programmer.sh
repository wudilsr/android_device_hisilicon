#!/bin/bash

CHIP_NAME=$1
BOOT_PATH=$2

function usage()
{
   echo "Usage:"
   echo "    device/hisilicon/bigfish/security/vmx/tool/merge_programmer.sh CHIP_NAME PROGRAMMER_PATH"
   echo "    for example : CHIP_NAME is Hi3798CV200, advca_programmer.bin is located at out/target/product/Hi3798CV200/Emmc/"
   echo "    device/hisilicon/bigfish/security/vmx/tool/merge_programmer.sh Hi3798CV200 out/target/product/Hi3798CV200/Emmc/"
   echo ""
   exit
}

if [ $# != 2 ];then
   usage
fi

OBJ_VMX_PATH=out/target/product/OBJVMX
mkdir -p ${OBJ_VMX_PATH}

cp -arf device/hisilicon/bigfish/security/vmx/tool/KeyArea_ToSTBM.bin  ${OBJ_VMX_PATH}
cp -arf device/hisilicon/bigfish/security/vmx/tool/KeyAreaSign_ToSTBM.bin  ${OBJ_VMX_PATH}


./device/hisilicon/bigfish/sdk/tools/linux/utils/advca/CASignTool_Linux/64bit/bin/CASignTool 0 device/hisilicon/bigfish/security/vmx/tool/${CHIP_NAME}_Signprogrammer_config.cfg -k device/hisilicon/bigfish/security/vmx/rsakey -r ${BOOT_PATH} -o ${OBJ_VMX_PATH}

./device/hisilicon/bigfish/sdk/tools/linux/utils/advca/CASignTool_Linux/64bit/bin/CASignTool 1 device/hisilicon/bigfish/security/vmx/tool/${CHIP_NAME}_merge_config.cfg -r ${OBJ_VMX_PATH} -o ${OBJ_VMX_PATH}

cp -arf ${OBJ_VMX_PATH}/FinalBoot.bin ${BOOT_PATH}/signed_advca_programmer.bin

rm -rf ${OBJ_VMX_PATH}

