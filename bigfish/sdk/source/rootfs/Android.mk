LOCAL_PATH := $(call my-dir)

ROOTFS_MODULE := msp_debug
ROOTFS_MODULE += pq_debug

include $(call all-named-subdir-makefiles,$(ROOTFS_MODULE))
