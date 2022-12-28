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

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base.mk)

# Set those variables here to overwrite the inherited values.
CHIPNAME := Hi3798MV100
PRODUCT_NAME := Hi3798MV100
PRODUCT_DEVICE := Hi3798MV100
PRODUCT_BRAND := HiSTBAndroidV5
PRODUCT_MODEL := Hi3798MV100
PRODUCT_MANUFACTURER := Hisilicon

# Correct bootanimation size for the screen
TARGET_SCREEN_HEIGHT := 1920
TARGET_SCREEN_WIDTH := 1080

# Inherit from Hi3798MV100 device
$(call inherit-product, device/hisilicon/Hi3798MV100/device.mk)
