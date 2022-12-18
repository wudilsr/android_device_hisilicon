#!/bin/sh

CHIP_TYPE=$1

XML_FILE=partitions_${CHIP_TYPE}_emmc.xml


echo "<?xml version=\"1.0\" encoding=\"GB2312\" ?>" >$XML_FILE
echo "<Partition_Info>" >>$XML_FILE
echo "<Part Sel=\"1\" PartitionName=\"fastboot\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"0\" Length=\"512K\" SelectFile=\"fastboot-burn.bin\"/>" >>$XML_FILE
echo "<Part Sel=\"1\" PartitionName=\"bootargs\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"512K\" Length=\"64K\" SelectFile=\"bootargs_"${CHIP_TYPE}"_tvp_emmc.bin\"/>" >>$XML_FILE
echo "<Part Sel=\"0\" PartitionName=\"baseparam\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"1M\" Length=\"4M\" SelectFile=\"\"/>" >>$XML_FILE
echo "<Part Sel=\"1\" PartitionName=\"pqparam\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"5M\" Length=\"4M\" SelectFile=\"pq_param_"${CHIP_TYPE}".bin\"/>" >>$XML_FILE
echo "<Part Sel=\"0\" PartitionName=\"logo\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"9M\" Length=\"4M\" SelectFile=\"\"/>" >>$XML_FILE
echo "<Part Sel=\"1\" PartitionName=\"trustedcore\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"13M\" Length=\"8M\" SelectFile=\"trustedcore.img\"/>" >>$XML_FILE
echo "<Part Sel=\"1\" PartitionName=\"kernel\" FlashType=\"emmc\" FileSystem=\"none\" Start=\"21M\" Length=\"8M\" SelectFile=\"hi_kernel.bin\"/>" >>$XML_FILE
echo "<Part Sel=\"1\" PartitionName=\"rootfs\" FlashType=\"emmc\" FileSystem=\"ext3/4\" Start=\"29M\" Length=\"96M\" SelectFile=\"rootfs_96M.ext4\"/>" >>$XML_FILE
echo "</Partition_Info>" >>$XML_FILE



