# 
# Copyright (C) 2010 ARM Limited. All rights reserved.
# 
# Copyright (C) 2008 The Android Open Source Project
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

LOCAL_PATH := $(call my-dir)


# HAL module implemenation, not prelinked and stored in
# hw/<OVERLAY_HARDWARE_MODULE_ID>.<ro.product.board>.so
include $(CLEAR_VARS)

include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_MODULE := gralloc.bigfish
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional

# Mali-200/300/400MP DDK
MALI_DDK_PATH := $(HISI_PLATFORM_PATH)/hardware/gpu/driver
#SHARED_MEM_LIBS := libUMP
SHARED_MEM_LIBS := libion libhardware
LOCAL_SHARED_LIBRARIES := liblog libcutils libGLESv1_CM $(SHARED_MEM_LIBS) liboverlay

LOCAL_C_INCLUDES := system/core/include/ $(MALI_DDK_PATH)/include \
	$(HISI_PLATFORM_PATH)/hidolphin/external/liboverlay \
	$(HISI_PLATFORM_PATH)/external/liboverlay \
	$(COMMON_DIR)/include

LOCAL_CFLAGS := -DLOG_TAG=\"gralloc\" -DGRALLOC_32_BITS -DPLATFORM_SDK_VERSION=$(PLATFORM_SDK_VERSION) 
LOCAL_CFLAGS += -DCHIP_TYPE_${CFG_HI_CHIP_TYPE} -DOVERLAY -DSUPPORT_LEGACY_FORMAT

LOCAL_SRC_FILES := \
	gralloc_module.cpp \
	alloc_device.cpp \
	framebuffer_device.cpp \
	gralloc_hisilicon_adp.cpp

include $(BUILD_SHARED_LIBRARY)
