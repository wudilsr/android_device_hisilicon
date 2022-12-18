LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := pq_debug
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(CFG_HI_CFLAGS)
LOCAL_CFLAGS += -DLOG_TAG=\"$(LOCAL_MODULE)\"
LOCAL_CFLAGS += -DLOG_NDEBUG=0

LOCAL_C_INCLUDES := $(COMMON_DIR)/api
LOCAL_C_INCLUDES += $(COMMON_DIR)/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/flash/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/../msp/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/../msp/api/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/../msp/drv/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/log
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/mmz
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/mem
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/memdev
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/module
LOCAL_C_INCLUDES += $(COMMON_DIR)/api/include
LOCAL_C_INCLUDES += $(COMMON_DIR)/drv/include

CMN_DIR=../../common
LOCAL_SRC_FILES := \
	$(CMN_DIR)/api/log/mpi_log.c \
	$(CMN_DIR)/api/sys/hi_common.c \
	$(CMN_DIR)/api/flash/src/hi_flash.c \
	$(CMN_DIR)/api/flash/src/emmc_raw.c \
	$(CMN_DIR)/api/flash/src/nand_raw.c \
	$(CMN_DIR)/api/flash/src/spi_raw.c \
	$(CMN_DIR)/api/flash/src/cmdline_parts.c \
	$(CMN_DIR)/api/flash/src/nand.c \
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
	
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
LOCAL_SRC_FILES += pq_v1_0/pq_debug.c pq_v1_0/pq_parse.c pq_v1_0/pq_comm.c
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200_a hi3716mv410 hi3716mv420),)
LOCAL_SRC_FILES += pq_v2_0/pq_debug.c pq_v2_0/pq_parse.c pq_v2_0/pq_comm.c
PQ_API_DIR=../../msp/api/pq/pq_v2_0
LOCAL_SRC_FILES += $(PQ_API_DIR)/mpi_pq.c
endif

LOCAL_SHARED_LIBRARIES := libcutils libdl

include $(BUILD_EXECUTABLE)
