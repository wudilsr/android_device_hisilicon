#!/system/bin/sh
ETHERNETON=`getprop persist.ethernet.on`
case $ETHERNETON in
 true)
  busybox ifconfig eth0 up
  ;;
 *)
  ;;
 esac

date -s 20140101
QBENABLE=`getprop persist.sys.qb.enable`
case $QBENABLE in
 true)
  ;;
 *)
  setprop sys.insmod.ko 1
  ;;
 esac

#DVFS
echo 0 > /sys/module/mali/parameters/mali_dvfs_enable
echo 432000 1200 >/proc/msp/pm_gpu


echo "\n\nWelcome to HiAndroid\n\n" > /dev/kmsg
LOW_RAM=`getprop ro.config.low_ram`
case $LOW_RAM in
 true)
  echo "\n\nenter low_ram mode\n\n" > /dev/kmsg
  echo 104857600 > /sys/block/zram0/disksize
  mkswap /dev/block/zram0
  swapon /dev/block/zram0
  #modules(memopt): Enable KSM in low ram device
  echo 1 > /sys/kernel/mm/ksm/run
  echo 300 > /sys/kernel/mm/ksm/sleep_millisecs
  ;;
 *)
  ;;
 esac
 
