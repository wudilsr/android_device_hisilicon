#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../../..
    endif

include $(SDK_DIR)/base.mak
endif

TARGET := pq
VERSION := pq_v3_0
MOD_NAME := hi_$(TARGET)

obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME).o

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), CHIP_TYPE_hi3798cv200_a),)
HAL_DIR := hifone
$(MOD_NAME)-y :=  mng/pq_mng_dbdr.o  
$(MOD_NAME)-y +=  hal/$(HAL_DIR)/pq_hal_hsharpen.o
$(MOD_NAME)-y +=  mng/pq_mng_hsharpen.o       
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE),  hi3796mv100 hi3798mv100),)
HAL_DIR := hi3798mv100
$(MOD_NAME)-y :=  mng/pq_mng_dbdr_98m.o  
$(MOD_NAME)-y +=  mng/pq_mng_sharpen.o
endif
#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

EXTRA_CFLAGS += -I$(COMMON_UNF_INCLUDE)                 \
                -I$(COMMON_API_INCLUDE)                 \
                -I$(COMMON_DRV_INCLUDE)                 \
                -I$(MSP_UNF_INCLUDE)                    \
                -I$(MSP_API_INCLUDE)                    \
                -I$(MSP_DRV_INCLUDE)                    \
                -I$(MSP_DRV_REG_INCLUDE)                \
                -I$(MSP_DIR)/api/$(TARGET)/include      \
                -I$(MSP_DIR)/api/higo/include           \
                -I$(MSP_DIR)/drv/$(TARGET)/$(VERSION)/mng   \
                -I$(MSP_DIR)/drv/$(TARGET)/$(VERSION)/hal/$(HAL_DIR)   \
		-I$(MSP_DIR)/drv/$(TARGET)/$(VERSION)/hal/common  \
                -I$(MSP_DIR)/drv/$(TARGET)/$(VERSION)

KBUILD_EXTRA_SYMBOLS += $(COMMON_DIR)/drv/Module.symvers



$(MOD_NAME)-y +=    drv_pq_intf.o               \
                    drv_pq.o                    \
		    hal/common/pq_hal_comm.o               \
                    hal/$(HAL_DIR)/pq_hal_acm.o            \
                    hal/$(HAL_DIR)/pq_hal_acm_convert.o    \
                    hal/$(HAL_DIR)/pq_hal_csc.o            \
                    hal/$(HAL_DIR)/pq_hal_dci.o            \
                    hal/$(HAL_DIR)/pq_hal_dei.o            \
                    hal/$(HAL_DIR)/pq_hal_sharpen.o        \
                    hal/$(HAL_DIR)/pq_hal_dbdr.o           \
                    hal/$(HAL_DIR)/pq_hal_zme.o            \
                    hal/$(HAL_DIR)/pq_hal_fmd.o            \
                    hal/$(HAL_DIR)/pq_hal_sr.o             \
                    mng/pq_mng_acm.o            \
                    mng/pq_mng_csc.o            \
                    mng/pq_mng_dci.o            \
                    mng/pq_mng_dei.o            \
                    mng/pq_mng_scaler.o         \
                    mng/pq_mng_pq_table.o       \
                    mng/pq_mng_ua.o             \
                    mng/pq_mng_zme.o            \
                    mng/pq_mng_ifmd.o           \
                    mng/pq_mng_sr.o

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#===============================================================================
#   rules
#===============================================================================
.PHONY: prepare unprepare all clean install uninstall

all:
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
ifneq ($(CFG_MSP_BUILDTYPE),y)
	$(AT)cp -f $(CURDIR)/$(MOD_NAME).ko $(MODULE_DIR)/
endif

uninstall:
	$(AT)rm -rf $(MODULE_DIR)/$(MOD_NAME).ko

