#trustedcore mk file
#created by h00206996

LOCAL_CFLAGS += -DOS_STB_HiS40V200
# add by h00211444
# originally, two CC switch in four makefiles,
# now, both in this file
WITH_K3V2PRO_CCTEST = true
WITH_CC_DRIVER = false
WITH_STB_CIPHER_DRIVER =true
#ifeq ($(WITH_STB_CIPHER_DRIVER), false)
#TRUSTEDCORE_TEXT_BASE = 0x2cf01000
#TRUSTEDCORE_TASK_BASE = 0x2bf00000
#else
CFG_HI_TVP_MEM_LAYOUT ?= 1G
CONFIG_MEM_LAYOUT := $(CFG_HI_TVP_MEM_LAYOUT)
$(info CONFIG_MEM_LAYOUT=$(CONFIG_MEM_LAYOUT))

ifeq ($(CONFIG_MEM_LAYOUT),2G)
TRUSTEDCORE_TEXT_BASE = 0x6D001000
TRUSTEDCORE_TASK_BASE = 0x6B000000
MEM_SIZE = 1712M
MMZ_SIZE = 600M
endif

ifeq ($(CONFIG_MEM_LAYOUT),1G)
TRUSTEDCORE_TEXT_BASE = 0x2D001000
TRUSTEDCORE_TASK_BASE = 0x2B000000
MEM_SIZE = 688M
MMZ_SIZE = 380M
endif

#endif
#selection of SECURE_TESTSUITE: none, RTOSck_UT, RTOSck_IT, RTOSck_PT
SECURE_TESTSUITE = none
#SECURE_TESTSUITE = RTOSck_UT
#SECURE_TESTSUITE = RTOSck_IT

###########################################################
# definition
###########################################################
TRUSTEDCORE_DIR=$(shell pwd)
TOOLCHAINS_DIR=$(TRUSTEDCORE_DIR)/toolchains
CROSS_COMPILE1=$(TOOLCHAINS_DIR)/gcc/linux-x86/arm/arm-eabi-4.7/bin/arm-eabi-
CROSS_COMPILE2=$(TOOLCHAINS_DIR)/gcc/linux-x86/arm/arm-linux-androideabi-4.7/bin/arm-linux-androideabi-

MAKE       =make
AR1        =$(CROSS_COMPILE1)ar
CC1        =$(CROSS_COMPILE1)gcc
LD1        =$(CROSS_COMPILE1)ld
OBJCOPY1   =$(CROSS_COMPILE1)objcopy
AR2        =$(CROSS_COMPILE2)ar
CC2        =$(CROSS_COMPILE2)gcc
LD2        =$(CROSS_COMPILE2)ld
OBJCOPY2   =$(CROSS_COMPILE2)objcopy
CFLAGS     =
LDFLAGS    =
RM         =-rm -f
MKDIR      =-mkdir -p
COPY       =cp
OUT        =${TRUSTEDCORE_DIR}/release/out
