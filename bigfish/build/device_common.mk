
#
# Copyright (C) 2011 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
PRODUCT_AAPT_PREF_CONFIG := xhdpi

PRODUCT_CHARACTERISTICS := tablet

ifeq ($(strip $(PRODUCT_TARGET)), telecom)
UEVENTD_TYPE_NAME := telecom
else ifeq ($(strip $(PRODUCT_TARGET)), shcmcc)
UEVENTD_TYPE_NAME := mobile
else
UEVENTD_TYPE_NAME := default
endif

PRODUCT_COPY_FILES := \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml

PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/init.${UEVENTD_TYPE_NAME}.rc:root/init.rc \
    device/hisilicon/bigfish/etc/init.hidolphin.rc:root/init.hidolphin.rc \
    device/hisilicon/bigfish/etc/ueventd.bigfish.${UEVENTD_TYPE_NAME}.rc:root/ueventd.bigfish.rc \
    device/hisilicon/bigfish/etc/media_codecs.xml:/system/etc/media_codecs.xml \
    device/hisilicon/bigfish/etc/media_profiles.xml:/system/etc/media_profiles.xml \
    device/hisilicon/bigfish/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml \

PRODUCT_COPY_FILES += \
    device/hisilicon/${CHIPNAME}/etc/init.${CHIPNAME}.rc:root/init.bigfish.rc \
    device/hisilicon/${CHIPNAME}/etc/init.${CHIPNAME}.sh:system/etc/init.bigfish.sh

# audio
PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/audio_policy.conf:system/etc/audio_policy.conf\
    device/hisilicon/bigfish/etc/asound.conf:system/etc/asound.conf\
	device/hisilicon/bigfish/etc/alsa.conf:system/usr/share/alsa/alsa.conf

# pppoe
PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/pppoe/ppp.conf:system/etc/ppp/ppp.conf \
    device/hisilicon/bigfish/etc/pppoe/ppp.connect:system/etc/ppp/ppp.connect \
    device/hisilicon/bigfish/etc/pppoe/ppp.disconnect:system/etc/ppp/ppp.disconnect

# Wifi
PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/wifi/dhcpcd.conf:system/etc/dhcpcd/dhcpcd.conf \
    device/hisilicon/bigfish/etc/wifi/wpa_supplicant.conf:system/etc/wifi/wpa_supplicant.conf \
    device/hisilicon/bigfish/etc/wifi/p2p_supplicant.conf:system/etc/wifi/p2p_supplicant.conf


PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/restore:system/etc/restore


PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0

# For application to get the OpenGL ES version
PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version=131072

# When set to TRUE this flag sets EGL_SWAP_BEHAVIOR_PRESERVED_BIT in eglSwapBuffers 
# which will end up preserving the whole frame causing a significant increase in memory bandwidth and decrease in performance
PRODUCT_PROPERTY_OVERRIDES += \
    debug.hwui.render_dirty_regions=false

# set ro.kernel.android.checkjni false for apk compatibility
PRODUCT_PROPERTY_OVERRIDES += \
    ro.kernel.android.checkjni=false

# Disable lockscreen by default
PRODUCT_PROPERTY_OVERRIDES += \
    ro.lockscreen.disable.default=true

# Disable hardware menu key
PRODUCT_PROPERTY_OVERRIDES += \
    qemu.hw.mainkeys=0

# MediaScanner
PRODUCT_PROPERTY_OVERRIDES += \
    ro.mediaScanner.enable=false

# DEFAULT STORAGE
PRODUCT_PROPERTY_OVERRIDES += \
    ro.defaultStorage.enable=false

# DLNA&Skyplay Toast
PRODUCT_PROPERTY_OVERRIDES += \
    ro.toastshow.enable=false

# fuse
PRODUCT_PROPERTY_OVERRIDES += \
    ro.fuse.support=false

# Whether CVBS is enabled or not when HDMI is plugged in
ifeq ($(strip $(PRODUCT_TARGET)), telecom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.cvbs.and.hdmi=true
else
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.cvbs.and.hdmi=false
endif

# Dobly DMA Certification
PRODUCT_PROPERTY_OVERRIDES += \
    ro.dolby.dmacert.enable=false

# Dobly IPTV Certification
PRODUCT_PROPERTY_OVERRIDES += \
    ro.dolby.iptvcert.enable=false

# Dobly DVB Certification
PRODUCT_PROPERTY_OVERRIDES += \
    ro.dolby.dvbcert.enable=false

# add release version
PRODUCT_PROPERTY_OVERRIDES += \
    gsm.version.baseband=HiSTBAndroidV600R001C00SPC060

# open 2D drawing
ifeq ($(PRODUCT_TARGET),shcmcc)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.ui.hw=false
else
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.ui.hw=true
endif
# pmqos config
PRODUCT_PROPERTY_OVERRIDES += \
    ro.pmqos.enable=true

ifneq ($(strip $(BOARD_QBSUPPORT)),true)
PRODUCT_PROPERTY_OVERRIDES += \
	ro.laterscan.enable=true
endif

ifeq ($(PRODUCT_TARGET),shcmcc)
#hiplayer graphic output
PRODUCT_PROPERTY_OVERRIDES += \
	service.media.hiplayer.graphic=false
endif

PRODUCT_PROPERTY_OVERRIDES += \
        hibrowser.default.fullscreen=true

#samba status
PRODUCT_PROPERTY_OVERRIDES += \
        persist.sys.samba.status=true

#for karaoke
PRODUCT_PROPERTY_OVERRIDES += \
persist.karaoke.enable=true

ifeq ($(PRODUCT_TARGET),shcmcc)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.media.timeshift=1
PRODUCT_PROPERTY_OVERRIDES += \
    client.apk.name= wasu.app
PRODUCT_PROPERTY_OVERRIDES += \
    sys.settings.support=1
PRODUCT_PROPERTY_OVERRIDES += \
    sys.settings.support.net.flags=7
PRODUCT_PROPERTY_OVERRIDES += \
    sys.deepdiagnose.support=1
#TimeZone
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.timezone=Asia/Shanghai
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.video.cvrs=0
endif

# for ethernet and pppoe frameworks compile
FRAMEWORKS_BASE_SUBDIRS += \
    $(addsuffix /java, \
        pppoe\
        ethernet\
        g3\
    )

PRODUCT_PACKAGES += \
     libandroid_qb

# Screen orientation: landscape or portrait
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.screenorientation=landscape

# set  suspend type
PRODUCT_PROPERTY_OVERRIDES += \
    service.suspend.type=0
# Security
HISILICON_SECURITY_L1 := false
ifdef HISILICON_SECURITY_L1
ifeq ($(HISILICON_SECURITY_L1),true)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hs.security.l1.enable=$(HISILICON_SECURITY_L1)
ifneq (,$(wildcard device/hisilicon/${CHIPNAME}/security/releasekey.x509.pem))
ifneq (,$(wildcard device/hisilicon/${CHIPNAME}/security/releasekey.pk8))
PRODUCT_DEFAULT_DEV_CERTIFICATE := \
    device/hisilicon/${CHIPNAME}/security/releasekey
else
$(warning device/hisilicon/${CHIPNAME}/security/releasekey.pk8 does not exist!)
endif
else
$(warning device/hisilicon/${CHIPNAME}/security/releasekey.x509.pem does not exist!)
endif
endif
endif

$(call inherit-product, frameworks/native/build/tablet-dalvik-heap.mk)
