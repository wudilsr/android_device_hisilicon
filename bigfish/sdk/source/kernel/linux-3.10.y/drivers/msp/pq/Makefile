ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../..
    endif

include $(SDK_DIR)/base.mak
endif

ifeq ($(CFG_HI_PQ_V1_0),y)
PQ_DIR := pq_v1_0
endif

ifeq ($(CFG_HI_PQ_V2_0),y)
PQ_DIR := pq_v2_0
endif

ifeq ($(CFG_HI_PQ_V3_0),y)
PQ_DIR := pq_v3_0
endif

ifeq ($(CFG_MSP_BUILDTYPE),y)
obj-$(CFG_MSP_BUILDTYPE) += $(PQ_DIR)/
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#=================================================================
#     rules
#=================================================================
.PHONY: all clean install uninstall

all:
	$(AT)make -C $(PQ_DIR) all

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install:
	$(AT)make -C $(PQ_DIR) install

uninstall:
	$(AT)make -C $(PQ_DIR) uninstall

