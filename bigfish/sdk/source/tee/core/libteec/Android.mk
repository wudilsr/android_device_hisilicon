LOCAL_PATH:= $(call my-dir)

#############################
## libteec.so
#############################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE_TAGS := optional
LOCAL_SRC_FILES := src/tee_client_api.c \
                   src/tee_client_storage_api.c \
                   src/tee_client_app_load.c \
                   src/tee_client_random_api.c \
                   src/dx_client_api.c \
                   src/tee_client_time_api.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
LOCAL_SRC_FILES +=  sec_mmz/src/sec_mmz.c
LOCAL_C_INCLUDES += $(LOCAL_PATH)/sec_mmz/inc
endif

LOCAL_SHARED_LIBRARIES := libcutils
ifeq ($(strip $(CFG_ANDROID_AOSP)),y)
LOCAL_CFLAGS += -Wno-int-conversion
endif

LOCAL_MODULE:= libteec
LOCAL_CFLAGS += -Wlong-long -Wformat -Wpointer-arith
LOCAL_MULTILIB := both

include $(BUILD_SHARED_LIBRARY)

##################################################
#STB-Config Trusted Storage Path
##################################################
CFG_TEE_STORAGE_DIR ?= /securestore/

#############################
## teecd
#############################
include $(CLEAR_VARS)
#add by q00209673 for bootloaderlockstatus
#WITH_K3V3_FPGA=true
ifeq ($(strip $(WITH_K3V3_FPGA)), true)
LOCAL_CFLAGS += -DK3V3_FPGA
endif
#ifeq ($(RPMB_FEATURE_ENABLED),true)
#LOCAL_CFLAGS += -DTEE_SUPPORT_RPMB_DEVICE
#endif
######for hisi
LOCAL_CFLAGS += -DCFG_TEE_STORAGE_DIR=\"$(CFG_TEE_STORAGE_DIR)\"
LOCAL_CFLAGS += -D_ANDROID_PLATFORM_HISI
LOCAL_CFLAGS += -Wno-int-conversion

LOCAL_MODULE_TAGS:= optional
LOCAL_SRC_FILES:= src/tee_agent.c \
                  src/tee_nv_info.c \
		  src/tee_get_app_cert.c \
		  src/tee_ca_daemon.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc \
		    $(LOCAL_PATH)/../../../../external/libxml2/include/libxml \
		    $(LOCAL_PATH)/../../../../external/libxml2/include \
                    $(LOCAL_PATH)/../../../../external/openssl/include/ \
		    $(LOCAL_PATH)/../../../../external/icu/icu4c/source/common/
LOCAL_MODULE:= teecd
# teecd is used in recovery: must be static.
#LOCAL_FORCE_STATIC_EXECUTABLE := true
#LOCAL_MODULE_PATH := $(TARGET_ROOT_OUT_SBIN)
#LOCAL_UNSTRIPPED_PATH := $(TARGET_ROOT_OUT_SBIN_UNSTRIPPED)

#LOCAL_STATIC_LIBRARIES := libxml2 libc libm libcutils liblog libicuuc_static libcrypto_static
#ifneq ($(strip $(WITH_K3V3_FPGA)), true)
#LOCAL_STATIC_LIBRARIES += libnve
#endif
LOCAL_SHARED_LIBRARIES := liblog libcutils

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= src/tlogcat.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tlogcat
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

# invoke Android.mk files in subdirs
#include $(call all-makefiles-under,$(LOCAL_PATH))

