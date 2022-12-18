#===============================================================================
# export variable
#===============================================================================
include $(SDK_DIR)/base.mak

#===============================================================================
# local variables
#===============================================================================
EXTRA_CFLAGS += -I$(FUSION_DIR)/linux/drivers/char/fusion        \
                -I$(FUSION_DIR)/linux/drivers/char/fusion        \
                -I$(FUSION_DIR)/linux/drivers/char/fusion/multi  \
                -I$(FUSION_DIR)/linux/drivers/char/fusion/single \
                -I$(FUSION_DIR)/linux/include/linux              \
                -I$(FUSION_DIR)/linux/include                    \
                -DFUSION_CALL_INTERRUPTIBLE

ifeq ($(CFG_HI_DIRECTFB_DEBUG_SUPPORT),y)
        EXTRA_CFLAGS += -DFUSION_DEBUG_SKIRMISH_DEADLOCK -DFUSION_ENABLE_DEBUG
        EXTRA_CFLAGS += -DONE_ENABLE_DEBUG
endif

ifeq ($(CFG_HI_CPU_ARCH),arm64)
EXTRA_CFLAGS += -DFUSION_DEAL_WITH_WARNING
endif

ifeq ($(shell test -e $(LINUX_DIR)/include/linux/config.h && echo yes),yes)
EXTRA_CFLAGS += -DHAVE_LINUX_CONFIG_H
endif

#$(error $(EXTRA_CFLAGS))

#================================================================================
#select the complie file
#================================================================================
MOD_NAME := fusion

obj-m += $(MOD_NAME).o

# fusion.ko
$(MOD_NAME)-y := linux/drivers/char/fusion/call.o             \
                 linux/drivers/char/fusion/entries.o          \
                 linux/drivers/char/fusion/fifo.o             \
                 linux/drivers/char/fusion/fusiondev.o        \
                 linux/drivers/char/fusion/fusionee.o         \
                 linux/drivers/char/fusion/list.o             \
                 linux/drivers/char/fusion/property.o         \
                 linux/drivers/char/fusion/reactor.o          \
                 linux/drivers/char/fusion/ref.o              \
                 linux/drivers/char/fusion/skirmish.o         \
                 linux/drivers/char/fusion/shmpool.o

$(MOD_NAME)-y += linux/drivers/char/fusion/single/fusioncore_impl.o  \
                 linux/drivers/char/fusion/debug.o                   \
                 linux/drivers/char/fusion/hash.o

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"
#===============================================================================
# rules
#===============================================================================
.PHONY: all clean

all:
	$(AT)make -C $(LINUX_DIR) ARCH=arm CROSS_COMPILE=$(CFG_HI_TOOLCHAINS_NAME)- M=$(CURDIR) modules

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf
