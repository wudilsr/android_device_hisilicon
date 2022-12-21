#!/bin/bash
###############################################################################
#
#  Ceate By Czyong
#
###############################################################################

function usage ()
{
	echo "Usage: ${selfname} toolspath Dir Pagesize Blocksize"
	echo "  toolspath     the path of mkfs.ubifs,ubinize:"
	echo "  Dir           the directory you want to make ubifs"
	echo "Example:"
	echo "  ${selfname} tools  system 4k 1M"
	echo ""
	exit 0
}
###############################################################################

function run ()
{
	local cmd=$1
	echo "${cmd}"
	msg=$(eval "${cmd}"); result=$?
	echo ${msg}
	[ ${result} == 0 ] || exit ${result}
}
###############################################################################

function hstrtol ()
{
	local hstr=$1
	local zoom=1
	local result=$(echo "${hstr}" | awk '{printf "%d",$0}')

	if [ "$(echo ${hstr} | grep -n '[Gg]')" == "1:${hstr}" ]; then
		zoom=1073741824
	elif [ "$(echo ${hstr} | grep -n '[Mm]')" == "1:${hstr}" ]; then
		zoom=1048576
	elif [ "$(echo ${hstr} | grep -n '[Kk]')" == "1:${hstr}" ]; then
		zoom=1024
	fi

	echo $((${result} * ${zoom}))
}
###############################################################################

selfname=$(basename $0)

if [ $# == 0 ]; then
	usage;
fi

if [ $# != 4 ]; then

	echo "need many parameters,$#"
	exit 1
fi

hpagesize=${3}
pagesize=$(hstrtol ${hpagesize})
hblocksize=${4}
blocksize=$(hstrtol ${hblocksize})
rootdir=$(echo $(echo "${2} " | sed 's/\/ //'))
hpartsize=$(echo 4g)
partsize=$(hstrtol ${hpartsize})


ubish_dir=$(echo $(echo "${1} " | sed 's/\/ //'))

if [ ! -d ${ubish_dir} ]; then
	echo "Directory ${ubish_dir} not exist."
	exit 1;
fi

if [ ! -d ${rootdir} ]; then
	echo "Warning Directory ${rootdir} not exist!"
	echo "We will just first create empty Directory ${rootdir} for generating ubiimg! after generating the ubiimg,we delete the empty path"
	mkdir -v ${rootdir}
	empty_path=YES
fi

LEB=$((${blocksize} - ${pagesize} * 2))
MAX_LEB_CNT=$((${partsize} / ${blocksize}))
###############################################################################

ubifsimg=${rootdir}.ubifs
ubiimg=${rootdir}_${hpagesize}_${hblocksize}.ubi
ubicfg=${rootdir}.ubicfg

MKUBIFS=${ubish_dir}/mkfs.ubifs
MKUBI=${ubish_dir}/ubinize

run "${MKUBIFS} -F -d ${rootdir} -m ${pagesize} -o ${ubifsimg} -e ${LEB} -c ${MAX_LEB_CNT}"

{
	echo "[ubifs-volumn]"
	echo "mode=ubi"
	echo "image=${ubifsimg}"
	echo "vol_id=0"
	echo "vol_type=dynamic"
	echo "vol_flags=autoresize"
	echo "vol_name=ubifs"
	echo ""

} > ${ubicfg}

run "${MKUBI} -o ${ubiimg} -m ${pagesize} -p ${blocksize} ${ubicfg}"

if [ -d ${rootdir} ];then
	if [ "$empty_path" = "YES" ];then
	echo "Delete the empty Directory ${rootdir} "
	rm -vrf ${rootdir}
	empty_path=NO
	fi
fi
echo "creat $ubiimg successfully!"
echo " "
rm -f ${ubifsimg} ${ubicfg}
