#!/system/bin/sh
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
echo 400000 > /sys/module/mali/parameters/mali_dvfs_max_freqency

echo "\n\nWelcome to HiAndroid\n\n" > /dev/kmsg
LOW_RAM=`getprop ro.config.low_ram`
case $LOW_RAM in
 true)
  echo "\n\nenter 512M low_ram mode\n\n" > /dev/kmsg
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

# Forced standby restart function
sleep 3;
echo 0x1 0x1 > /proc/msp/pm
