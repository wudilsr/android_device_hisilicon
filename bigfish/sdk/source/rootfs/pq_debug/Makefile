SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak


PREFIX ?= $(CURDIR)/../../rootfs

COMMON_DIR=$(SDK_DIR)/source/common

LIB = -Wl,--start-group -lpthread -lm -Wl,--end-group
LIBPATH  = -L$(COMMON_DIR)/api
INCLUDE  = -I$(COMMON_DIR)/include
INCLUDE  += -I$(COMMON_DIR)/api/flash/include
INCLUDE  += -I$(COMMON_DIR)/../msp/include
INCLUDE  += -I$(COMMON_DIR)/../msp/api/include
INCLUDE  += -I$(COMMON_DIR)/../msp/drv/include
INCLUDE  += -I$(COMMON_DIR)/api/log
INCLUDE  += -I$(COMMON_DIR)/api/mmz
INCLUDE  += -I$(COMMON_DIR)/api/mem
INCLUDE  += -I$(COMMON_DIR)/api/memdev
INCLUDE  += -I$(COMMON_DIR)/api/module
INCLUDE  += -I$(COMMON_DIR)/api/include
INCLUDE  += -I$(COMMON_DIR)/drv/include
CFLAGS += $(CFG_HI_CFLAGS) $(INCLUDE)

OBJS := \
	$(COMMON_DIR)/api/log/mpi_log.o \
	$(COMMON_DIR)/api/sys/hi_common.o \
	$(COMMON_DIR)/api/flash/src/hi_flash.o \
	$(COMMON_DIR)/api/flash/src/emmc_raw.o \
	$(COMMON_DIR)/api/flash/src/nand_raw.o \
	$(COMMON_DIR)/api/flash/src/spi_raw.o \
	$(COMMON_DIR)/api/flash/src/cmdline_parts.o \
	$(COMMON_DIR)/api/flash/src/nand.o \
	$(COMMON_DIR)/api/mem/mpi_memmap.o \
	$(COMMON_DIR)/api/mem/mpi_mutils.o \
	$(COMMON_DIR)/api/mem/mpi_mmgr.o \
	$(COMMON_DIR)/api/module/mpi_module.o \
	$(COMMON_DIR)/api/stat/mpi_stat.o \
	$(COMMON_DIR)/api/mmz/mpi_mmz.o \
	$(COMMON_DIR)/api/mem/mpi_mem.o \
	$(COMMON_DIR)/api/memdev/mpi_memdev.o \
	$(COMMON_DIR)/api/userproc/mpi_userproc.o \
	$(COMMON_DIR)/api/osal/hi_osal.o

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716cv200 hi3716mv400 hi3718cv100 hi3719cv100 hi3718mv100 hi3719mv100),)
OBJS += pq_v1_0/pq_debug.o pq_v1_0/pq_parse.o pq_v1_0/pq_comm.o
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200_a),)
OBJS += pq_v2_0/pq_debug.o pq_v2_0/pq_parse.o pq_v2_0/pq_comm.o
OBJS += $(SDK_DIR)/source/msp/api/pq/pq_v2_0/mpi_pq.o
endif

all: pq_debug 

pq_debug: $(OBJS)
	$(AT)$(CC) -o $@ $^ $(LIBPATH) $(LIB)
	$(AT)cp $@ $(PREFIX)/usr/bin/$@

clean:
	$(AT)rm -rf pq_debug
	$(AT)find ./ -name "*.o" | xargs rm -rf
