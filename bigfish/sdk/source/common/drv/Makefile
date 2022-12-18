###############################################################################
# export variables
###############################################################################
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../..
    endif

include $(SDK_DIR)/base.mak
endif

###############################################################################
# local variables
###############################################################################

## header search path

EXTRA_CFLAGS += -I$(COMMON_DIR)/include \
                -I$(COMMON_DIR)/api/include \
                -I$(COMMON_DIR)/drv/include \
                -I$(COMMON_DIR)/api/log \
                -I$(COMMON_DIR)/api/stat \
                -I$(COMMON_DIR)/api/sys \
                -I$(COMMON_DIR)/api/mmz \
                -I$(COMMON_DIR)/drv/module \
                -I$(COMMON_DIR)/drv/mem \
                -I$(COMMON_DIR)/drv/log \
                -I$(COMMON_DIR)/drv/mmz \
                -I$(COMMON_DIR)/api/mem \
                -I$(MSP_DIR)/drv/include \
                -I$(MSP_DIR)/api/include \
                -I$(MSP_DIR)/api/tde/include \
                -I$(MSP_DIR)/include \
                -I$(LINUX_DIR)/include/uapi/linux

ifdef CFG_HI_LOG_LEVEL
EXTRA_CFLAGS += -DCFG_HI_LOG_LEVEL=$(CFG_HI_LOG_LEVEL)
else
EXTRA_CFLAGS += -DCFG_HI_LOG_LEVEL=1
endif

ifeq (y,$(CFG_HI_LOG_NETWORK_SUPPORT))
EXTRA_CFLAGS += -DLOG_NETWORK_SUPPORT
endif

ifeq (y,$(CFG_HI_LOG_UDISK_SUPPORT))
EXTRA_CFLAGS += -DLOG_UDISK_SUPPORT
endif

ifeq (y,$(CFG_HI_MEMMGR_SUPPORT))
EXTRA_CFLAGS += -DCMN_MMGR_SUPPORT
endif

EXTRA_CFLAGS += $(CFG_HI_KMOD_CFLAGS)

MOD_NAME_CMN   := hi_common
MOD_NAME_MMZ   := hi_mmz
MOD_NAME_MEDIA := hi_media

$(MOD_NAME_CMN)-y := sys/drv_base_ext_k.o  \
               sys/drv_sys_ext_k.o   \
               dev/drv_dev_ext_k.o   \
               stat/drv_stat_ext_k.o \
               proc/drv_proc_ext_k.o \
               log/drv_log_ext_k.o

$(MOD_NAME_CMN)-y +=    sys/drv_base_ext.o          \
                        sys/drv_sys_ext.o           \
                        sys/drv_reg_common.o        \
                        stat/drv_stat_ext.o         \
                        mem/drv_mutils.o            \
                        module/drv_module_ext.o     \
                        file/drv_file_ext.o         \
                        proc/drv_proc_ext.o         \
                        log/drv_log_ext.o           \
                        memdev/drv_memdev.o         \
                        userproc/drv_userproc.o     \
                        osal/drv_osal.o

$(MOD_NAME_MEDIA)-y := himedia/himedia_base.o  \
                       himedia/himedia.o

ifeq ($(CFG_HI_MEMMGR_SUPPORT),y)
$(MOD_NAME_CMN)-y += mem/drv_mmgr_ext.o mem/drv_mem_ext.o
endif

ifeq (y,$(CFG_HI_TEST_SUPPORT))
EXTRA_CFLAGS += -DCMN_TEST_SUPPORTED
$(MOD_NAME_CMN)-y += test/drv_test_ext.o
endif

$(MOD_NAME_MMZ)-y := mmz/drv_mmz_ext_k.o  \
                    mmz/drv_mmz_intf.o

ifeq ($(CFG_HI_MMZ_V2_SUPPORT),y)
EXTRA_CFLAGS      += -DMMZ_V2_SUPPORT
$(MOD_NAME_MMZ)-y += mmz/drv_mmz_userdev_v2.o mmz/drv_media_mem_v2.o
else
$(MOD_NAME_MMZ)-y += mmz/drv_mmz_userdev.o mmz/drv_media_mem.o
endif

DEPENDS := $(patsubst %.o, %.d, $($(MOD_NAME_MEDIA)-y))
DEPENDS += $(patsubst %.o, %.d, $($(MOD_NAME_MMZ)-y))
DEPENDS += $(patsubst %.o, %.d, $($(MOD_NAME_CMN)-y))

###############################################################################
obj-$(CFG_MSP_BUILDTYPE) += $(MOD_NAME_MEDIA).o $(MOD_NAME_MMZ).o $(MOD_NAME_CMN).o

###############################################################################

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

###############################################################################
#   rules
###############################################################################
.PHONY: all clean install uninstall

all:
	$(AT)make ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- -C $(LINUX_DIR)  M=`pwd` modules
	$(AT)$(STRIP) --strip-unneeded $(MOD_NAME_CMN).ko

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: all
	$(AT)cp -f $(MOD_NAME_CMN).ko $(MODULE_DIR)/
	$(AT)cp -f $(MOD_NAME_MMZ).ko $(MODULE_DIR)/
	$(AT)cp -f $(MOD_NAME_MEDIA).ko $(MODULE_DIR)/

uninstall:
	$(AT)rm -f $(MODULE_DIR)/$(MOD_NAME_CMN).ko
	$(AT)rm -f $(MODULE_DIR)/$(MOD_NAME_MMZ).ko
	$(AT)rm -f $(MODULE_DIR)/$(MOD_NAME_MEDIA).ko

