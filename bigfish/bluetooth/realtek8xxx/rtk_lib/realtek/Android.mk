LOCAL_PATH := $(call my-dir)

#include $(call all-subdir-makefiles)
driver_modules := \
    setbtmacaddr \
    uart \
    usb


include $(call all-named-subdir-makefiles,$(driver_modules))
