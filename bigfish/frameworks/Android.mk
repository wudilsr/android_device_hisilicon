LOCAL_PATH := $(call my-dir)

driver_modules := \
    sampleatc \
    hinetworkutils \
    hibdinfo      \
    hidvdinfo     \
    hidisplaymanager \
    netshare      \
    hianilib      \
    sdkinvoke   \
    flashInfo    \
    hikaraoke \
    hisysmanager \
    fastbootoptimize \
    qb \
    audio_nodelay \
    himediaplayer \
    hipq

include $(call all-named-subdir-makefiles,$(driver_modules))
