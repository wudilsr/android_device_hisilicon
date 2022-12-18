#! /bin/sh

CA_NAME=$1
CHIP_TYPE=$2
SDK_DIR=$3
IMAGE_DIR=$4
BOOT_REG_NAME=$5
BOOT_DIR=${SDK_DIR}/source/boot
ADVCA_SIGN_CFG_NAME=${BOOT_REG_NAME/reg/cfg}
CA_TOOL_DIR=${SDK_DIR}/tools/linux/utils/advca
VMX_SIGN_TOOL_DIR=${CA_TOOL_DIR}/vmx
VMX_3RD_FLAG=$6

if [ ! $6 ] ; then
    VMX_3RD_FLAG=n
fi

function prepare ()
{	
	cp -afr ${IMAGE_DIR}/*.bin ./SignInput/
	find ${IMAGE_DIR} -maxdepth 1 -name rootfs* | xargs -r cp -t ./SignInput/
	cp -afr ${IMAGE_DIR}/trustedcore.img ./SignInput/
	cp ${BOOT_DIR}/sysreg/${ADVCA_SIGN_CFG_NAME} ./SignInput/
	uname -a | grep -rnw "x86_64" > /dev/null
	if [ 0 -eq $? ] ; then 
		cp ${SDK_DIR}/tools/linux/utils/advca/CASignTool_Linux/64bit/bin/CASignTool ./
		#cp -rf ${SDK_DIR}/tools/linux/utils/advca/CASignTool_Linux/64bit/bin/bin_CASignTool ./
	else
		cp ${SDK_DIR}/tools/linux/utils/advca/CASignTool_Linux/32bit/bin/CASignTool ./
		#cp -rf ${SDK_DIR}/tools/linux/utils/advca/CASignTool_Linux/32bit/bin/bin_CASignTool ./
	fi	
	chmod a+x ./*
	chmod a+x ${VMX_SIGN_TOOL_DIR}/vmxBuild.sh	
}

function sig_image ()
{
	if [ $CA_NAME == "CONAX" ]; then
		./sig.sh conax ${CHIP_TYPE} ${ADVCA_SIGN_CFG_NAME}
		cp ./SignOutput/*.sig ${IMAGE_DIR}/
		cp ./SignOutput/FinalBoot.bin ${IMAGE_DIR}/
	fi
	
	if [ $CA_NAME == "VERIMATRIX" ]; then
	
		if [ $VMX_3RD_FLAG == "y" ]; then
			if [ -e ./SignInput/miniboot.bin ] ; then
				mv ./SignInput/miniboot.bin ./SignInput/fastboot-burn.bin
        			./vmx_3rd_sign_boot.sh ${CHIP_TYPE} ${ADVCA_SIGN_CFG_NAME}
		                if [ -e ./MergeOutput/advca_programmer.sig ] && [ -e ./MergeOutput/FinalBoot.bin ] ; then
		        		cp ./MergeOutput/advca_programmer.sig ${IMAGE_DIR}/
		        		cp ./MergeOutput/FinalBoot.bin ${IMAGE_DIR}/
		        	fi        			
        		fi
        		
        		./vmx_3rd_sign_noboot.sh all_image ${SDK_DIR} ${CA_TOOL_DIR}/sig_image
		else
			if [ -e ./SignInput/miniboot.bin ] ; then
				mv ./SignInput/miniboot.bin ./SignInput/fastboot-burn.bin		    
			    	./sign_boot.sh vmx ${CHIP_TYPE} ${ADVCA_SIGN_CFG_NAME}
			else
				echo " miniboot.bin is not exist ! can not sig the boot"
			fi
					    
			
	    		cd ${VMX_SIGN_TOOL_DIR}
	    			./vmxBuild.sh all_image ${SDK_DIR} ${CA_TOOL_DIR}/sig_image
	    		cd -
			if [ -e ./SignOutput/advca_programmer.sig ] && [ -e ./SignOutput/FinalBoot.bin ] ; then
				cp ./SignOutput/advca_programmer.sig ${IMAGE_DIR}/
				cp ./SignOutput/FinalBoot.bin ${IMAGE_DIR}/
			fi
		fi

		cp ./SignOutput/vmx_flash/* ${IMAGE_DIR}/
	fi
}

rm -fr ./SignOutput
prepare
sig_image






