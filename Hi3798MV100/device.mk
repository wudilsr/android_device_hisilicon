
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

#Product usage selection, possible values are: shcmcc/telecom/unicom/ott/dvb/demo
#shcmcc stands for the ShangHai Mobile video base mode.
#telecom stands for the China Telecom centralized procurement mode.
#unicom stands for the China Unicom centralized procurement mode.
#ott stands for OTT or the China Mobile provincial procurement mode.
#dvb stands for dvb version.
#Please modify here before compilation

PRODUCT_TARGET := ott
ifdef PRODUCT_TARGET

ifeq ($(strip $(PRODUCT_TARGET)), ott)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=ott
endif

ifeq ($(strip $(PRODUCT_TARGET)), shcmcc)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=shcmcc
endif

ifeq ($(strip $(PRODUCT_TARGET)), telecom)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=telecom
endif

ifeq ($(strip $(PRODUCT_TARGET)), unicom)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=unicom
endif

ifeq ($(strip $(PRODUCT_TARGET)), dvb)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=dvb
endif

ifeq ($(strip $(PRODUCT_TARGET)), demo)
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=demo
endif

else
PRODUCT_TARGET := ott
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.target=ott
endif

BOARD_QBSUPPORT := false

ifdef BOARD_QBSUPPORT
ifeq ($(strip $(BOARD_QBSUPPORT)),true)
# isFirstBoot
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.firstboot.flag=true
# FastBoot
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.qb.flag=true

# quickboot enable
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.qb.enable=true

PRODUCT_COPY_FILES += \
    device/hisilicon/bigfish/etc/snapshot:root/sbin/snapshot \
    device/hisilicon/bigfish/etc/andsnap:root/sbin/andsnap

endif
endif

#set video output rate for telecom and unicom, defalt 4:3
ifeq ($(strip $(PRODUCT_TARGET)),telecom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.video.cvrs= 1
else ifeq ($(strip $(PRODUCT_TARGET)),unicom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.video.cvrs= 1
else
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.video.cvrs= 0
endif

#setup SecurityL2

HISILICON_SECURITY_L2 := false

ifeq ($(strip $(HISILICON_SECURITY_L2)),true)
PRODUCT_DEFAULT_DEV_CERTIFICATE := \
    device/hisilicon/${CHIPNAME}/security/releasekey
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hs.security.l1.enable=true
endif
PRODUCT_PROPERTY_OVERRIDES += \
    ro.thirdparty.dhcp=false

#setup UI density
ifeq ($(strip $(PRODUCT_TARGET)),shcmcc)
PRODUCT_PROPERTY_OVERRIDES += \
     ro.sf.lcd_density=160
else ifeq ($(strip $(PRODUCT_TARGET)),telecom)
PRODUCT_PROPERTY_OVERRIDES += \
     ro.sf.lcd_density=160
else ifeq ($(strip $(PRODUCT_TARGET)),unicom)
PRODUCT_PROPERTY_OVERRIDES += \
     ro.sf.lcd_density=160
else
PRODUCT_PROPERTY_OVERRIDES += \
     ro.sf.lcd_density=240
endif

PRODUCT_PROPERTY_FOR_DRM_SERVICE:=true
ifeq ($(strip $(PRODUCT_PROPERTY_FOR_DRM_SERVICE)),true)
# add drm enable property for PlayReady/Widevine
PRODUCT_PROPERTY_OVERRIDES += drm.service.enabled=true
else
PRODUCT_PROPERTY_OVERRIDES += drm.service.enabled=false
endif

PRODUCT_PROPERTY_FOR_DRM_CLIENT:=false
ifeq ($(strip $(PRODUCT_PROPERTY_FOR_DRM_CLIENT)),true)
# add drm enable property for PlayReady/Widevine
PRODUCT_PROPERTY_OVERRIDES += drm.client.enabled=true
else
PRODUCT_PROPERTY_OVERRIDES += drm.client.enabled=false
endif

# Configure Widevine Stream Cache Size for HD content
PRODUCT_PROPERTY_OVERRIDES += ro.com.widevine.cachesize=16777216

# widevine debug fuse
PRODUCT_PROPERTY_OVERRIDES += drm.widevine.debug=false

# enable Widevine drm
PRODUCT_PACKAGES += com.google.widevine.software.drm.xml \
					com.google.widevine.software.drm \
					libdrmwvmplugin libwvm libdrmdecrypt  \
					libWVStreamControlAPI_L$(BOARD_WIDEVINE_OEMCRYPTO_LEVEL) \
					libwvdrm_L$(BOARD_WIDEVINE_OEMCRYPTO_LEVEL)

#HiPlayer graphic output
ifeq ($(strip $(PRODUCT_TARGET)),shcmcc)
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.graphic=false
else
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.graphic=true
endif

#HiPlayer fast switch channel mode, false for fast switch
ifeq ($(strip $(PRODUCT_TARGET)),telecom)
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.nostatic=true
else ifeq ($(strip $(PRODUCT_TARGET)),unicom)
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.nostatic=true
else
PRODUCT_PROPERTY_OVERRIDES += \
    service.media.hiplayer.nostatic=false
endif

$(call inherit-product, device/hisilicon/bigfish/build/device_common.mk)
