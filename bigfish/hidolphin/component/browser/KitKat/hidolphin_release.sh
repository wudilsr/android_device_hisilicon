#!/bin/bash
set -ex

#########################################################################
## return error code
#########################################################################
E_INVAL=22 #Invalid param
E_NOENT=2  #File or directory that does not exist
E_ACCES=13 #Access denied

function abs_dir()
{
	if [ -d $1 ] ; then
		cd $1; pwd; cd - > /dev/null
	else
		echo $1
	fi
}

BASE_DIR=$1
HIDOLPHIN_DIR=$2
HIDOLPHIN_OUT_DIR=$3

# Android.mk  app
dir_remove_src_files="${BASE_DIR}/${HIDOLPHIN_DIR}/component/browser/KitKat/app "

# Remove source code
function remove_src_files() {
    if [ $# -lt 1 ]; then
	echo "Please input the files for deleting"
	exit ${E_INVAL}
	fi

	for ff in $@ ; do
	if [ -d ${ff} -o -f ${ff} ];then
		echo "rm -rf ${ff}"
		rm -rf ${ff}
	fi
	done
}

echo -e "\033[0;32;1mHiBrowser release begin!\033[0m"

# Remove all Android.mk
cd ${BASE_DIR}/${HIDOLPHIN_DIR}/component/browser/KitKat/
find . -maxdepth 2 -name "Android.mk" | xargs rm -rfv {}

# Anything special
#cd ${BASE_DIR}/${HIDOLPHIN_DIR}/component/browser/
#ls | grep -v app | xargs rm -rf

remove_src_files ${dir_remove_src_files}

# Android.mk.rel is left, rename it to release makefile!
mv Android.mk.rel Android.mk

# Copy apk here!
#browser_apk="${HIDOLPHIN_OUT_DIR}/system/app/Browser++.apk "
#cp ${browser_apk} .
rm Android.mk

echo -e "\033[0;32;1mHiBrowser release end!\033[0m"
