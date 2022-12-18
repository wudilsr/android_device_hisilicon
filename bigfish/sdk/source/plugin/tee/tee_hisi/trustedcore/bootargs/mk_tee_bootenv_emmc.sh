#!/bin/sh


MKBOOTARGS=$1
CHIP_TYPE=$2
MEM_LAYOUT=$3
MEM_SIZE=$4
MMZ_SIZE=$5
TRSTCORE_LOADADDR=$6
BOOTARGS_SIZE=$7
((BOOTARGS_SIZE=$BOOTARGS_SIZE));
BOOTARGS_SIZE=`expr $BOOTARGS_SIZE / 1024`;


INPUT_FILE=bootargs_${CHIP_TYPE}_${MEM_LAYOUT}.txt

touch $INPUT_FILE

echo "baudrate=115200" >$INPUT_FILE
echo "ethaddr=00:00:00:00:00:00" >>$INPUT_FILE
echo "ipaddr=192.168.1.10" >>$INPUT_FILE
echo "netmask=255.255.255.0" >>$INPUT_FILE
echo "gatewayip=192.168.1.1" >>$INPUT_FILE
echo "serverip=192.168.1.1" >>$INPUT_FILE
echo "bootdelay=0" >>$INPUT_FILE
echo "bootargs=mem="${MEM_SIZE}" mmz=ddr,0,0,"${MMZ_SIZE}" console=ttyAMA0,115200 root=/dev/mmcblk0p7 rootfstype=ext4 rootwait blkdevparts=mmcblk0:1M(boot),4M(baseparam),4M(pqparam),4M(logo),8M(trustedcore),8M(kernel),96M(rootfs),-(others)" >>$INPUT_FILE
echo "bootcmd=mmc read 0 "${TRSTCORE_LOADADDR}" 0x6800 0x4000;bootm "${TRSTCORE_LOADADDR}";mmc read 0 0x1FFFFC0 0xA800 0x4000;bootm 0x1FFFFC0" >>$INPUT_FILE
echo "stdin=serial" >>$INPUT_FILE
echo "stdout=serial" >>$INPUT_FILE
echo "stderr=serial" >>$INPUT_FILE

#cat $INPUT_FILE

${MKBOOTARGS} -r $INPUT_FILE -o bootargs_${CHIP_TYPE}_${MEM_LAYOUT}.bin -s ${BOOTARGS_SIZE}

rm -f $INPUT_FILE
