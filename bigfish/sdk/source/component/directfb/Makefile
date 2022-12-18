
.PHONY:all install clean

#SRC_DIR=$(shell pwd)

ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..
include $(SDK_DIR)/base.mak
endif

#===================================================================
#Front Board LED KEY TYPE
#==================================================================
ifneq ($(CFG_HI_KEYLED_74HC164_SUPPORT),)
CFG_HI_KEYLED=-DCFG_HI_KEYLED_74HC164_SUPPORT
endif

ifneq ($(CFG_HI_KEYLED_CT1642_SUPPORT),)
CFG_HI_KEYLED=-DCFG_HI_KEYLED_CT1642_SUPPORT
endif

ifneq ($(CFG_HI_KEYLED_PT6961_SUPPORT),)
CFG_HI_KEYLED=-DCFG_HI_KEYLED_PT6961_SUPPORT
endif

ifneq ($(CFG_HI_KEYLED_PT6964_SUPPORT),)
CFG_HI_KEYLED=-DCFG_HI_KEYLED_PT6964_SUPPORT
endif

#===================================================================
#for char exchange
#==================================================================
ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-hisiv200-linux)
    EXTRA_FLAGS=\"-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16\"
endif

ifeq (${CFG_HI_TOOLCHAINS_NAME},arm-histbv300-linux)
EXTRA_FLAGS = \"-march=armv7-a -mcpu=cortex-a9 -mfloat-abi=softfp -mfpu=vfpv3-d16\"
ifeq (${CFG_HI_CHIP_TYPE},hi3798mv100)
EXTRA_FLAGS = \"-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=vfpv4-d16\"
endif
ifeq (${CFG_HI_CHIP_TYPE},hi3796mv100)
EXTRA_FLAGS = \"-mcpu=cortex-a7 -mfloat-abi=softfp -mfpu=vfpv4-d16\"
endif
endif

#EXTRA_FLAGS=$(CFG_HI_CFLAGS)

CROSS=${CFG_HI_TOOLCHAINS_NAME}
CROSS_COMPILE=${CFG_HI_TOOLCHAINS_NAME}-
ARCH=arm

.PHONY: all dfb_lib dfb_example dfb_test
all:
	@echo "BUILD_DIRECTFB=1">Kbuild
	@echo "BUILD_DIRECTFB_EXAMPLE=1">>Kbuild
	@echo "BUILD_DIRECTFB_TEST=0">>Kbuild
	@echo CROSS=${CROSS}>>Kbuild
	@echo CROSS_COMPILE=${CROSS_COMPILE}>>Kbuild
	@echo ARCH=${ARCH}>>Kbuild
	@echo CFG_HI_KEYLED=${CFG_HI_KEYLED}>>Kbuild
	@echo EXTRA_FLAGS=${EXTRA_FLAGS}>>Kbuild
	@sh ci.sh
	@rm Kbuild
dfb_lib:
	@echo "BUILD_DIRECTFB=1">Kbuild
	@echo "BUILD_DIRECTFB_EXAMPLE=0">>Kbuild
	@echo "BUILD_DIRECTFB_TEST=0">>Kbuild
	@echo CROSS=${CROSS}>>Kbuild
	@echo CROSS_COMPILE=${CROSS_COMPILE}>>Kbuild
	@echo ARCH=${ARCH}>>Kbuild
	@echo CFG_HI_KEYLED=${CFG_HI_KEYLED}>>Kbuild
	@echo EXTRA_FLAGS=${EXTRA_FLAGS}>>Kbuild
	@sh ci.sh
	@rm Kbuild
dfb_example:
	@echo "BUILD_DIRECTFB=0">Kbuild
	@echo "BUILD_DIRECTFB_EXAMPLE=1">>Kbuild
	@echo "BUILD_DIRECTFB_TEST=0">>Kbuild
	@echo CROSS=${CROSS}>>Kbuild
	@echo CROSS_COMPILE=${CROSS_COMPILE}>>Kbuild
	@echo CFG_HI_KEYLED=${CFG_HI_KEYLED}>>Kbuild
	@echo ARCH=${ARCH}>>Kbuild
	@echo EXTRA_FLAGS=${EXTRA_FLAGS}>>Kbuild
	@sh ci.sh
	@rm Kbuild
dfb_test:
	@echo "BUILD_DIRECTFB=0">Kbuild
	@echo "BUILD_DIRECTFB_EXAMPLE=0">>Kbuild
	@echo "BUILD_DIRECTFB_TEST=1">>Kbuild
	@echo CROSS=${CROSS}>>Kbuild
	@echo CFG_HI_KEYLED=${CFG_HI_KEYLED}>>Kbuild
	@echo EXTRA_FLAGS=${EXTRA_FLAGS}>>Kbuild
	@sh ci.sh
	@rm Kbuild
.PHONY: install dfb_lib_install dfb_example_install dfb_test_install
install:
	make -C DirectFB-1.6.1 install
	make -C DirectFB-examples-1.6.0 install
dfb_lib_install:
	make -C DirectFB-1.6.1 install
dfb_example_install:
	make -C DirectFB-examples-1.6.0 install
dfb_test_install:
	make -C DirectFB-1.6.1/tests install

.PHONY: clean dfb_lib_clean dfb_example_clean dfb_test_clean
clean:
	make -C DirectFB-1.6.1 clean
	make -C DirectFB-examples-1.6.0 clean
	@rm directfb -rf
	@rm sample -rf
dfb_lib_clean:
	make -C DirectFB-1.6.1 clean
dfb_example_clean:
	make -C DirectFB-examples-1.6.0 clean
	rm sample -rf
dfb_test_clean:
	make -C DirectFB-1.6.1/tests clean
