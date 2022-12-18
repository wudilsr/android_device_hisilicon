LOCAL_PATH := $(call my-dir)
LOCAL_PATH_TMP := $(LOCAL_PATH)
include $(CLEAR_VARS)

# Call these makefiles sequentially according to proper dependencies
#==========================================================================
# Compile browser for corresponding browser
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
#    include $(LOCAL_PATH_TMP)/KitKat/Android.mk
else
    include $(LOCAL_PATH_TMP)/JellyBean/Android.mk
endif
#==========================================================================
