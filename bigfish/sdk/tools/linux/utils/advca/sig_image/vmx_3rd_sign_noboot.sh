#! /bin/sh
if [ $# -ne 3 ]
then
	echo -e "usage: ./vmx_3rd_sign_noboot.sh [image_file | all_image] sdk_dir advca_image_dir"
	echo -e "image_file: bootargs.bin hi_kernel.bin rootfs.squashfs apploader.bin"
	echo -e "all_image: should be defined at config.mk, which is located at root directory of 'tools/linux/utils/vmx'"
	exit 1
fi

key_file=
id_name=

sdk_dir=$2
advca_image_dir=$3
sign_output_dir="${advca_image_dir}/SignOutput"
sign_input_dir="${advca_image_dir}/SignInput"
sign_output_flash_dir="${sign_output_dir}/vmx_flash"
sign_output_upgrade_dir="${sign_output_dir}/vmx_upgrade"
SIGN_KEY_FILE="${sign_input_dir}/integration_rsa_pri.txt"
SIGN_NOBOOT_CFG="./vmx_3rd_SignNonBootImage.cfg"
vmx_init ()
{
	if [ ! -d ${sign_output_flash_dir} -o ! -d ${sign_output_upgrade_dir} ]
	then
		mkdir -p "${sign_output_flash_dir}"
		mkdir -p "${sign_output_upgrade_dir}"
	fi

	if [ ! -d ${sign_output_dir} ]
	then
		mkdir -p "${sign_output_dir}"
	fi
}

software_signature ()
{
	mode=${2}
	if [ ${mode} -eq 0 ]
	then
		sign_file_dir="${sign_output_flash_dir}"
	elif [ ${mode} -eq 1 ]
	then
		sign_file_dir="${sign_output_upgrade_dir}"
	fi

	file_to_sign=${sign_input_dir}/${1}
	if [ ! -f "${file_to_sign}" ]
	then
		echo -e "no find file:'${file_to_sign}'"
		return 1
	fi

	final_signature_file=${sign_file_dir}/$(echo "${1}" |awk -F "." '{print $1}')_signature.$(echo "${1}" |awk -F "." '{print $2}')
    echo -e "SIGN_KEY_FILE:'${SIGN_KEY_FILE}'"
    echo -e "SIGN_NOBOOT_CFG:'${SIGN_NOBOOT_CFG}'"
    echo -e "file_to_sign:'${file_to_sign}'"    
    echo -e "final_signature_file:'${final_signature_file}'"        
    ./CASignTool 5 $SIGN_NOBOOT_CFG -K $SIGN_KEY_FILE -R $file_to_sign -O $final_signature_file
	return 0
}

vmx_deinit ()
{
	exit 1
}


vmx_init
if [ "$1" = "all_image" ]
then
	echo -e "************** start vmx signing **************"
	all_image_list="$(cat config.mk | awk -F "=" '{print $2}')"
	echo "image_list: ${all_image_list}"
	for device in ${all_image_list}
	do
		if [ -f "${sign_input_dir}/${device}" ]
		then
			## "mode" is defined by verimatrix, which means 0:flash, 1:upgrade
			software_signature ${device} 0
			software_signature ${device} 1
			echo "sign ${device} success!"
		else
			echo "file: ${sign_input_dir}/${device} not exist!"			
		fi
	done
	tree ${sign_output_flash_dir}
	tree ${sign_output_upgrade_dir}
	echo -e "************** end vmx signing **************\n"
	vmx_deinit
elif [ "$1" = "clean" ]
then
	if [ -d ${sign_output_flash_dir} ]
	then
		rm -rf ${sign_output_flash_dir}
	fi

	if [ -d ${sign_output_upgrade_dir} ]
	then
		rm -rf ${sign_output_upgrade_dir}
	fi

	vmx_deinit
else
	echo -e "************** start vmx signing **************"
	software_signature ${1} 0;
	if [ $? -ne 0 ]
	then
		echo -e "sign file:'${1}' failed"
		echo -e "************** end vmx signing **************\n"
		vmx_deinit
	fi

	software_signature ${1} 1
	if [ $? -ne 0 ]
	then
		echo -e "sign file:${1} failed"
		echo -e "************** end vmx signing **************\n"
		vmx_deinit
	fi

	echo "sign ${1} success!"
	tree ${sign_output_flash_dir}
	tree ${sign_output_upgrade_dir}
	echo -e "************** end vmx signing **************\n"

	vmx_deinit
fi

