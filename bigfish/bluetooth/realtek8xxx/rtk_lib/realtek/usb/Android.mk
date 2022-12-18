LOCAL_PATH := $(call my-dir)

driver_modules := \
	firmware \
	libbt-vendor

include $(call all-named-subdir-makefiles,$(driver_modules))
