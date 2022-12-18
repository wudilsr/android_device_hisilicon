#!/bin/bash

##########################################################################
#-------  configurable parameters --------
key_file=supposition
id_name=

nosign_file_dir="$OUT/Emmc"
other_subarea_file="kernel.img bootargs.bin apploader.bin trustedcore.img"
sign_file_dir_flash=${nosign_file_dir}
sign_file_dir_upgrade="${nosign_file_dir}/upgrade"
##########################################################################
##########################################################################

sh_dir="$(pwd)"
sh_lib="${sh_dir}/hisi_lib"

##########################################################################
#------- fastboot configurable parameters --------
boot_subarea_file="fastboot.bin advca_programmer.bin"
board_CFG_file=$(grep "EMMC_BOOT_CFG_NAME" ${ANDROID_BUILD_TOP}/device/hisilicon/${TARGET_PRODUCT}/BoardConfig.mk | awk '{print $3}')
hisi_sdk_path="${sh_dir}/../../sdk"
x86_tool_dir="${hisi_sdk_path}/pub/advca_image"
tool_sign_name="ca_sign_tool"
##########################################################################
##########################################################################

create_signature_sh="${sh_dir}/create_signature.sh"
boot_subarea_signature="${sh_lib}/boot_subarea_signature.sh"
vmx_sh_temp_dir="${sh_dir}/vmx_sh_temp_dir"
Align16="${sh_dir}/Align16.c"
MAKE_HASH="${sh_dir}/sha256/sha256self.c"
sample_ca_vmx_merge="${hisi_sdk_path}/sample/advca/sample_ca_vmx_appsignsimulator.c"
copy_lib_to_shatable ()
{
	echo "copy third-party lib to shatable"
#	cp $OUT/system/lib/libsysutils.so ${sh_dir}/shatable/
}

init_user ()
{
	if [ ! -d ${sign_file_dir_flash} -o ! -d ${sign_file_dir_upgrade} ]
	then
		mkdir -p "${sign_file_dir_flash}"
		mkdir -p "${sign_file_dir_upgrade}"
	fi

	mkdir -p ${vmx_sh_temp_dir}
	mkdir -p ${sh_dir}/shatable
	copy_lib_to_shatable
	if [ ! -f "${sh_dir}/MAKE_HASH" ]
	then
		gcc ${MAKE_HASH} -o ${sh_dir}/sha256self
		strip  ${sh_dir}/sha256self
	fi

	if [ ! -f "${sh_dir}/Align16" ]
	then
		gcc ${Align16} -o ${sh_dir}/Align16
		strip  ${sh_dir}/Align16
	fi

	if [ ! -f "${sh_dir}/sample_ca_vmx_merge" ]
	then
		gcc  ${sample_ca_vmx_merge} \
			-o ${sh_dir}/sample_ca_vmx_merge
		strip  ${sh_dir}/sample_ca_vmx_merge
	fi
}

software_signature ()
{
	mode=${2}
	if [ ${mode} -eq 0 ]
	then
		sign_file_dir="${sign_file_dir_flash}"
	elif [ ${mode} -eq 1 ]
	then
		sign_file_dir="${sign_file_dir_upgrade}"
	fi

	file_to_sign=${nosign_file_dir}/${1}
	signature_file=${vmx_sh_temp_dir}/$(echo "${1}" |awk -F "." '{print $1}')_sign.$(echo "${1}" |awk -F "." '{print $2}')
	signed_file=${vmx_sh_temp_dir}/$(echo "${1}" |awk -F "." '{print $1}')_encrypt.$(echo "${1}" |awk -F "." '{print $2}')
	final_signature_file=${sign_file_dir}/$(echo "${1}" |awk -F "." '{print $1}')_signature.$(echo "${1}" |awk -F "." '{print $2}')
	final_signature_head=${sign_file_dir}/$(echo "${1}" |awk -F "." '{print $1}')_head.$(echo "${1}" |awk -F "." '{print $2}')
	length_of_file=`stat -c %s ${file_to_sign}`
	length_of_signing=${length_of_file}

	Align=`expr 16 - $[ ${length_of_file} % 16 ]`
	if [ ${Align} -ne 16 ]
	then
		echo "start image_16Align ... "
		echo "Align_length=$Align"
		cp -f ${file_to_sign} ${vmx_sh_temp_dir}/${1}
		file_to_sign=${vmx_sh_temp_dir}/${1}
		${sh_dir}/Align16 ${file_to_sign} $Align
	fi

	source ${create_signature_sh} ${length_of_file} ${length_of_signing} ${file_to_sign} ${signature_file} ${signed_file} ${key_file} ${mode} ${id_name}

	${sh_dir}/sample_ca_vmx_merge ${signed_file} ${signature_file} ${final_signature_head} ${final_signature_file}
	rm -rf  ${final_signature_head}
}

init_user
if [ -z $1 ]
then
	for device in ${other_subarea_file}
	do
		## "mode" is  0:flash, 1:upgrade
		software_signature ${device} 0
		software_signature ${device} 1
	done

	if [ -d "${sh_lib}" ]
	then
		pushd ${sh_lib}
		source ${boot_subarea_signature}
		popd
	fi
	${sh_dir}/sha256self ${nosign_file_dir}/system.squashfs
	mv shatable.squashfs ${nosign_file_dir}/
	software_signature shatable.squashfs 0
	software_signature shatable.squashfs 1
elif [ "$1" = "fastboot.bin" -o "$1" = "advca_programmer.bin" ]
then
	pushd ${sh_lib}
	if [ -d "${sh_lib}" ]
	then
		source ${boot_subarea_signature}
	else
		echo " no find \"${sh_lib}\" , exit !"
	fi
	popd
elif [ "$1" = "hash" ]
then
	if [ -z $2 ]
	then
		echo "make hash key, default file : ${nosign_file_dir}/system.squashfs"
		${sh_dir}/sha256self ${nosign_file_dir}/system.squashfs
	else
		echo "make hash key, file = ${2}"
		${sh_dir}/sha256self ${nosign_file_dir}/$2
	fi
	mv shatable.squashfs ${nosign_file_dir}/
	software_signature shatable.squashfs 0
	software_signature shatable.squashfs 1
else
	software_signature ${1} 0
	software_signature ${1} 1
fi

rm -rf ${sh_dir}/Align16
rm -rf ${sh_dir}/sample_ca_vmx_merge
rm -rf ${sh_dir}/sha256self
rm -rf ${vmx_sh_temp_dir}
