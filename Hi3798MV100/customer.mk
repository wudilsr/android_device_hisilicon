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

#Setup SecurityL1
HISILICON_SECURITY_L1 := false

#Setup SecurityL2
HISILICON_SECURITY_L2 := false
HISILICON_SECURITY_L2_COMMON_MODE_SIGN := false

#Setup SecurityL3
HISILICON_SECURITY_L3 := false

#Quick Boot Support
BOARD_QBSUPPORT := false

#enable wallpaper or not in 512M
PRODUCT_PROPERTY_OVERRIDES += \
    persist.low_ram.wp.enable=false

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

#if thirdparty dhcp service is needed to obtain ip, please set this property true
# default value is false
PRODUCT_PROPERTY_OVERRIDES += \
    ro.thirdparty.dhcp=false

# smart_suspend, deep_launcher, deep_restart, deep_resume;
PRODUCT_PROPERTY_OVERRIDES += \
     persist.suspend.mode=deep_restart

# Output format adaption for 2D streams
# false -> disable; true -> enable
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.video.adaptformat=false

# Whether CVBS is enabled or not when HDMI is plugged in
ifeq ($(strip $(PRODUCT_TARGET)), telecom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.cvbs.and.hdmi=true
else ifeq ($(strip $(PRODUCT_TARGET)), unicom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.cvbs.and.hdmi=true
else
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.cvbs.and.hdmi=false
endif

# Whether display format self-adaption is enabled or not when HDMI is plugged in
# 0 -> disable; 1 -> enable
ifeq ($(strip $(PRODUCT_TARGET)), telecom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.optimalfmt.enable=0
else ifeq ($(strip $(PRODUCT_TARGET)), unicom)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.optimalfmt.enable=0
else ifeq ($(strip $(PRODUCT_TARGET)), shcmcc)
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.optimalfmt.enable=0
else
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.optimalfmt.enable=1
endif

# Preferential display format: native, i50hz, p50hz, i60hz or p60hz
# persist.sys.optimalfmt.perfer is valid only if persist.sys.optimalfmt.enable=1
PRODUCT_PROPERTY_OVERRIDES += \
    persist.sys.optimalfmt.perfer=native
