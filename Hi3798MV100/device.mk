#
# Copyright 2014 The Android Open Source Project
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

include device/hisilicon/$(TARGET_PRODUCT)/customer.mk

#HiPlayer graphic output
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.graphic=true

#HiPlayer: video frame counts to be played before underrun while seeked
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.vfcnt=0

#HiPlayer: for vo switch channel freeze
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.hiplayer.vo.freeze=false

#wifi disguise
    persist.ethernet.wifidisguise=true

#ethernet switch
PRODUCT_PROPERTY_OVERRIDES += \
    persist.ethernet.on=true

# open 2D drawing
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.ui.hw=true

#setup UI density
PRODUCT_PROPERTY_OVERRIDES += \
     ro.sf.lcd_density=240

UEVENTD_TYPE_NAME := default

PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=demo

PRODUCT_PROPERTY_FOR_DRM_SERVICE := true
ifeq ($(strip $(PRODUCT_PROPERTY_FOR_DRM_SERVICE)), true)
# add drm enable property for PlayReady/Widevine
PRODUCT_PROPERTY_OVERRIDES += \
    drm.service.enabled=true
else
PRODUCT_PROPERTY_OVERRIDES += \
    drm.service.enabled=false
endif

PRODUCT_PROPERTY_FOR_DRM_CLIENT := true
ifeq ($(strip $(PRODUCT_PROPERTY_FOR_DRM_CLIENT)), true)
# add drm enable property for PlayReady/Widevine
PRODUCT_PROPERTY_OVERRIDES += \
    drm.client.enabled=true
else
PRODUCT_PROPERTY_OVERRIDES += \
    drm.client.enabled=false
endif

# Configure Widevine Stream Cache Size for HD content
PRODUCT_PROPERTY_OVERRIDES += \
    ro.com.widevine.cachesize=16777216

# widevine debug fuse
PRODUCT_PROPERTY_OVERRIDES += \
    drm.widevine.debug=false

PRODUCT_PROPERTY_OVERRIDES += \
    ro.laterscan.enable=true

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
    ro.lockscreen.disable.default=false

# Disable hardware menu key
PRODUCT_PROPERTY_OVERRIDES += \
    qemu.hw.mainkeys=0

# MediaScanner
PRODUCT_PROPERTY_OVERRIDES += \
    ro.mediaScanner.enable=true

# DEFAULT STORAGE
PRODUCT_PROPERTY_OVERRIDES += \
    ro.defaultStorage.enable=true

# DLNA&Skyplay Toast
PRODUCT_PROPERTY_OVERRIDES += \
    ro.toastshow.enable=false

# support sdcardfs
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sdcardfs.support=true
    
#fuse
HISI_FUSE_SDCARD := true
PRODUCT_PROPERTY_OVERRIDES += \
    ro.fuse.support=true

# Dobly DMA Certification
PRODUCT_PROPERTY_OVERRIDES += \
    ro.dolby.dmacert.enable=true

# Dobly IPTV Certification
PRODUCT_PROPERTY_OVERRIDES += \
    ro.dolby.iptvcert.enable=true

# Dobly DVB Certification
PRODUCT_PROPERTY_OVERRIDES += \
    ro.dolby.dvbcert.enable=true

# add release version
PRODUCT_PROPERTY_OVERRIDES += \
    gsm.version.baseband=HiSTBAndroidV600R001C00SPC065

PRODUCT_PROPERTY_OVERRIDES += \
    hibrowser.default.fullscreen=true

#samba status
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.samba.status=true

#for karaoke
PRODUCT_PROPERTY_OVERRIDES += \
    persist.karaoke.enable=true

#for media soft detector
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.softdetector.enable=false

# Screen orientation: landscape or portrait
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.screenorientation=landscape

# enable PowerControl
PRODUCT_PROPERTY_OVERRIDES += \
    ro.pmqos.enable=true

# set hisi omx output to overlay
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.codec.overlay=false

# patch name
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.patch=SPC060+patch15

PRODUCT_PACKAGES += \
     libandroid_qb

# enable Widevine drm
PRODUCT_PACKAGES += \
    libteec \
    libdrmutil \
    libHiDrmEngine \
    libwvcipher \
    libdrmclientplugin \
    libwvmcipherplugin \
    com.google.widevine.software.drm.xml \
    com.google.widevine.software.drm \
    libdrmwvmplugin libwvm libdrmdecrypt  \
    libWVStreamControlAPI_L$(BOARD_WIDEVINE_OEMCRYPTO_LEVEL) \
    libwvdrm_L$(BOARD_WIDEVINE_OEMCRYPTO_LEVEL)


PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.wifi.xml:system/etc/permissions/android.hardware.wifi.xml \
    frameworks/native/data/etc/android.hardware.wifi.direct.xml:system/etc/permissions/android.hardware.wifi.direct.xml \
    frameworks/native/data/etc/android.hardware.usb.accessory.xml:system/etc/permissions/android.hardware.usb.accessory.xml \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.usb.host.xml:system/etc/permissions/android.hardware.usb.host.xml


PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/init.${UEVENTD_TYPE_NAME}.rc:root/init.rc \
    device/hisilicon/bigfish/etc/init.hidolphin.rc:root/init.hidolphin.rc \
    device/hisilicon/bigfish/etc/ueventd.bigfish.${UEVENTD_TYPE_NAME}.rc:root/ueventd.bigfish.rc \
    device/hisilicon/bigfish/etc/media_codecs.xml:/system/etc/media_codecs.xml \
    device/hisilicon/bigfish/etc/media_profiles.xml:/system/etc/media_profiles.xml \
    device/hisilicon/bigfish/etc/tablet_core_hardware.xml:system/etc/permissions/tablet_core_hardware.xml

PRODUCT_COPY_FILES += \
    device/hisilicon/${CHIPNAME}/rootdir/etc/root/init.bigfish.rc:root/init.bigfish.rc \
    device/hisilicon/${CHIPNAME}/rootdir/etc/init.bigfish.sh:system/etc/init.bigfish.sh

# audio
PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/audio_policy.conf:system/etc/audio_policy.conf \
    device/hisilicon/bigfish/etc/asound.conf:system/etc/asound.conf \
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
    device/hisilicon/bigfish/etc/wifi/p2p_supplicant.conf:system/etc/wifi/p2p_supplicant.conf \
    device/hisilicon/bigfish/etc/wifi/iperf:system/bin/iperf \
    device/hisilicon/bigfish/etc/wifi/iwlist:system/bin/iwlist \
    device/hisilicon/bigfish/etc/wifi/iwpriv:system/bin/iwpriv \
    device/hisilicon/bigfish/etc/wifi/iwconfig:system/bin/iwconfig \
    device/hisilicon/bigfish/etc/wifi/76x2_supplicant:system/bin/76x2_supplicant


PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/restore:system/etc/restore \
    device/hisilicon/bigfish/etc/exitfastplay:system/etc/exitfastplay \
    device/hisilicon/bigfish/etc/security_l2_num:system/etc/security_l2_num
    
PRODUCT_COPY_FILES += \
    frameworks/base/cmds/preload/preloadclass.jar:system/framework/preloadclass.jar

PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/frameworks/fastbootoptimize/prebuilt/ZygoteOptimize.jar:system/framework/ZygoteOptimize.jar

PRODUCT_AAPT_PREF_CONFIG := xhdpi

PRODUCT_CHARACTERISTICS := tablet

# for ethernet and pppoe frameworks compile
FRAMEWORKS_BASE_SUBDIRS += \
    $(addsuffix /java, \
        pppoe\
        ethernet\
        g3\
    )

$(call inherit-product, frameworks/native/build/tablet-dalvik-heap.mk)
