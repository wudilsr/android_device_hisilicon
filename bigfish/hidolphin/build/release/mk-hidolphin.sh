#!/bin/bash

function config()
{
	echo "### Build menuconfig ###"
	make SDK_PATH=$SDK_PATH tools

	echo "### Launch menuconfig ###"
	make SDK_PATH=$SDK_PATH menuconfig
}

function build()
{
	source ./cfg.mak
	if [ $CFG_HI_LINUX_PRODUCT != 'y' ]
	then
		echo "Product configuration is not LINUX!"
		return
	fi
	
	echo "# Build HiDolphin ###"
	make SDK_PATH=$SDK_PATH build
}

function publish()
{
	if [ -d "out/debug" ] || [ -d out/release ]
	then
		echo "# Build HiDolphin ###"
		make SDK_PATH=$SDK_PATH publish
	else
		echo "Please build first!"
	fi
}

# Arguments
SDK_PATH=$1
if [ -z $SDK_PATH ]
then
	echo "Usage: $0 <SDK_PATH>"
	exit 1
fi

cat << EOF
*** please enter your choise:(1-4) ***
(1) Configuration
(2) Build
(3) Publish
(4) Exit
EOF
read -p "Now select to: " input
case $input in 
1) config;;
2) build;;
3) publish;;
4) exit;;
esac
