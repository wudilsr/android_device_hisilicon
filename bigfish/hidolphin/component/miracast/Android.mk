LOCAL_PATH:= $(call my-dir)

miracast_modules := \
    source \
    android/packages/apps/Miracast \
    hdcp \
    hal
include $(call all-named-subdir-makefiles, $(miracast_modules))
