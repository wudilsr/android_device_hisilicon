#!/bin/bash

CHIP_NAME=$1
CFG_FILE=$2

function usage()
{
   echo "Usage:"
   exit
}

SIGN_TOOL=./CASignTool
KEY_AREA_DIR=./KeyArea
MERGE_INPUT_DIR=./MergeIntput
MERGE_OUTPUT_DIR=./MergeOutput
#remove old files!
rm -fr ./MergeOutput

function process_cfg_file ()
{
	local advca_cfgfile=$1
	local chip=$2
	local cfg_file=$3

	if [ $chip == "hi3716mv310" ] || [ $chip == "hi3110ev500" ] ; then
		chip=Hi3716CV200
	elif [ $chip == "hi3716mv410" ] || [ $chip == "hi3716mv420" ] ; then
		chip=Hi3716MV410
	fi

	chmod +w $advca_cfgfile
	cp $advca_cfgfile $advca_cfgfile.bak
	sed 's/^Chip_Type=.*/Chip_Type='$chip'/g'  $advca_cfgfile.bak > $advca_cfgfile
	sed 's/^CFG=.*/CFG='$cfg_file'/g'  $advca_cfgfile.bak > $advca_cfgfile
#	rm -f $advca_cfgfile.bak
}



# advca programmer:
echo -e "sign advca programmer"

cp vmx_3rd_sign_programmer.cfg  Signboot_config.cfg

if [ -f ./SignInput/advca_programmer.bin ];then
	process_cfg_file Signboot_config.cfg $CHIP_NAME $CFG_FILE
	$SIGN_TOOL 0 Signboot_config.cfg
	cp $KEY_AREA_DIR/KeyArea.bin ./MergeInput/
	cp $KEY_AREA_DIR/KeyAreaSign.bin ./MergeInput/
	$SIGN_TOOL 1 merge_config.cfg
	if [ $? -eq 0 ];then
		mv ./MergeOutput/FinalBoot.bin ./MergeOutput/advca_programmer.sig
	else
		echo -e "sign advca programmer fail!"
	fi
else
	echo -e "./SignInput/advca_programmer.bin is not exist!"
fi


# sig boot
echo -e "sign boot image!"
cp vmx_3rd_sign_boot.cfg Signboot_config.cfg 

if [ -f ./SignInput/fastboot-burn.bin ];then
	process_cfg_file Signboot_config.cfg $CHIP_NAME $CFG_FILE
	$SIGN_TOOL 0 Signboot_config.cfg
	cp $KEY_AREA_DIR/KeyArea.bin ./MergeInput/
	cp $KEY_AREA_DIR/KeyAreaSign.bin ./MergeInput/
	$SIGN_TOOL 1 merge_config.cfg
else
	echo -e "./SignInput/fastboot-burn.bin is not exist!"
fi