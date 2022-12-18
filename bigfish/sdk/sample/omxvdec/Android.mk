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

# ---------------------------------------------------------------------------------
#			Make the apps-test (mm-vdec-omx-test)
# ---------------------------------------------------------------------------------
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE_TAGS		:= eng
LOCAL_MODULE			:= sample_omxvdec
LOCAL_CFLAGS			:= -pthread -ldl
LOCAL_C_INCLUDES		:= $(SDK_DIR)/source/msp/api/omx/include
LOCAL_C_INCLUDES		+= $(SDK_DIR)/source/common/include 
LOCAL_SHARED_LIBRARIES	:= libutils libOMX_Core libOMX.hisi.video.decoder libbinder libhi_common

LOCAL_SRC_FILES         := sample_omxvdec.c sample_queue.c sample_tidx.c

ifeq ($(CFG_HI_TEE_SUPPORT), y)
LOCAL_CFLAGS += -DHI_OMX_TEE_SUPPORT
LOCAL_CFLAGS += -DHI_TEE_SUPPORT

LOCAL_C_INCLUDES += $(HI_TEE_OS_DIR)/libteec/inc/
LOCAL_C_INCLUDES += $(COMMON_API_INCLUDE)/
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/mmz/
LOCAL_SHARED_LIBRARIES += libteec
endif

include $(BUILD_EXECUTABLE)
