LOCAL_PATH:= $(call my-dir)

#############################
## libteec.so
#############################
include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

ifeq ($(CFG_HI_TVP_SUPPORT), y)
LOCAL_CFLAGS += -DHI_TVP_SUPPORT
endif

ifeq ($(CFG_HI_TZINFRA_ENABLE), y)
LOCAL_SRC_FILES := src/tee_client_api.c \
                   src/tee_client_storage_api.c \
                   src/tee_client_app_load.c \
                   src/tee_client_random_api.c \
                   src/tee_client_time_api.c \
                   src/DxTzClientAPI.c
#                  src/dx_client_api.c
else
LOCAL_SRC_FILES := src/tee_client_api.c \
                   src/tee_client_storage_api.c \
                   src/tee_client_app_load.c \
                   src/tee_client_random_api.c \
                   src/tee_client_time_api.c \
                   sec_mmz/src/sec_mmz.c
endif
LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc  \
		    $(LOCAL_PATH)/sec_mmz/inc \
                    $(MSP_UNF_INCLUDE) \
                    $(COMMON_UNF_INCLUDE) \
                    $(TVP_DIR)/trustedcore/include/HS_API
LOCAL_MODULE:= libteec
LOCAL_SHARED_LIBRARIES := liblog 
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif

include $(BUILD_SHARED_LIBRARY)

#############################
## teecd
#############################
include $(CLEAR_VARS)
#add by q00209673 for bootloaderlockstatus
WITH_K3V3_FPGA_OR_STB=true
ifeq ($(strip $(WITH_K3V3_FPGA_OR_STB)), true)
LOCAL_CFLAGS += -DK3V3_FPGA_OR_STB
endif
LOCAL_SRC_FILES:= src/tee_agent.c \
                  src/tee_nv_info.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/inc
LOCAL_MODULE:= teecd
ifeq ($(strip $(WITH_K3V3_FPGA_OR_STB)), true)
LOCAL_SHARED_LIBRARIES := libcutils
else
LOCAL_SHARED_LIBRARIES := libcutils libnve
endif
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
include $(BUILD_EXECUTABLE)

# invoke Android.mk files in subdirs
include $(call all-makefiles-under,$(LOCAL_PATH))
