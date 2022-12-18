#=======================================
#	export variable
#=======================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
    ifneq ($(KERNELRELEASE),)
    KERNEL_DIR := $(srctree)

    SDK_DIR := $(KERNEL_DIR)/../../..
    else
    SDK_DIR := $(CURDIR)/../../../..
    endif

include $(SDK_DIR)/base.mak
endif

#=======================================
#	local variable
#=======================================
ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
objects := slic
endif

ifeq ($(CFG_HI_ADAC_TVL320AIC31_SUPPORT),y)
objects := tlv320aic31
endif

objects_clean       := $(addsuffix _clean, $(objects))
objects_install     := $(addsuffix _install, $(objects))
objects_uninstall   := $(addsuffix _uninstall, $(objects))

ifeq ($(CFG_MSP_BUILDTYPE),y)
obj-$(CFG_MSP_BUILDTYPE) += $(addsuffix /, $(objects))
endif

REMOVED_FILES := "*.o" "*.ko" "*.order" "*.symvers" "*.mod" "*.mod.*" "*.cmd" ".tmp_versions" "modules.builtin"

#=================================================================
#	  rules
#=================================================================
.PHONY: all clean install uninstall $(objects) $(objects_clean) $(objects_install) $(objects_uninstall)

all:    $(objects)

clean:
	$(AT)find ./ -name "*.d" $(foreach file, $(REMOVED_FILES), -o -name $(file)) | xargs rm -rf

install: $(objects_install)

uninstall: $(objects_uninstall)

$(objects):
	make -C $@

$(objects_clean):
	make -C $(patsubst %_clean,%,$@) clean

$(objects_install):
	make -C $(patsubst %_install,%,$@) install

$(objects_uninstall):
	make -C $(patsubst %_uninstall,%,$@) uninstall
