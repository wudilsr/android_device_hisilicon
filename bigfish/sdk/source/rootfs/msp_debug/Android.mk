LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := msp_debug
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"

LOCAL_C_INCLUDES := $(COMMON_DIR)/api
LOCAL_C_INCLUDES += $(COMMON_DIR)/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/log
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/mmz
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/mem
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/memdev
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/module
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/drv/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/include

CMN_DIR=../../common
LOCAL_SRC_FILES := msp_debug.c losys.c \
	$(CMN_DIR)/api/log/mpi_log.c \
	$(CMN_DIR)/api/sys/hi_common.c \
	$(CMN_DIR)/api/mem/mpi_memmap.c \
	$(CMN_DIR)/api/mem/mpi_mutils.c \
	$(CMN_DIR)/api/mem/mpi_mmgr.c \
	$(CMN_DIR)/api/module/mpi_module.c \
	$(CMN_DIR)/api/stat/mpi_stat.c \
	$(CMN_DIR)/api/mmz/mpi_mmz.c \
	$(CMN_DIR)/api/mem/mpi_mem.c \
	$(CMN_DIR)/api/memdev/mpi_memdev.c \
	$(CMN_DIR)/api/userproc/mpi_userproc.c \
	$(CMN_DIR)/api/osal/hi_osal.c

LOCAL_SHARED_LIBRARIES := libcutils libdl

include $(BUILD_EXECUTABLE)
