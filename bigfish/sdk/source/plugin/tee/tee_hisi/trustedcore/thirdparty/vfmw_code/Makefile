
#by chenwangmei 2015-06-9

###########################################################
# platform definition
###########################################################
ROOT      =..

ifeq ($(strip $(WITH_STB_CIPHER_DRIVER)), true)
LOCAL_CFLAGS += -DSTB_CIPHER_DRIVER
TARGET_RTOSCK_LINK_SCRIPT := $(ROOT)/trustedcore_STB.ld
else
TARGET_RTOSCK_LINK_SCRIPT := $(ROOT)/trustedcore.ld
endif

LOCAL_CFLAGS += -DTASK_ADDR=$(TRUSTEDCORE_TASK_BASE)
LOCAL_ASFLAGS += -DTASK_ADDR=$(TRUSTEDCORE_TASK_BASE)
################################################
## test config
#################################################
ifeq ($(SECURE_TESTSUITE),RTOSck_UT)
LOCAL_CFLAGS += -DTESTSUITE_RTOSck_UT
WITH_MONITOR_TEST := false
endif
ifeq ($(SECURE_TESTSUITE),RTOSck_PT)
LOCAL_CFLAGS += -DTESTSUITE_RTOSck_PT
endif
ifeq ($(SECURE_TESTSUITE),RTOSck_IT)
LOCAL_CFLAGS += -DTESTSUITE_RTOSck_IT
endif

WITH_DEBUG_EXTERN := false
ifeq ($(WITH_DEBUG_EXTERN), true)
LOCAL_CFLAGS += -DDEBUG_EXTERN
LOCAL_CFLAGS += -DDEBUG_SWITCH
endif

ifeq ($(CONFIG_MEM_LAYOUT),1G)
LOCAL_CFLAGS += -DCONFIG_SYS_MEM_1G
endif

ifeq ($(CONFIG_MEM_LAYOUT),2G)
LOCAL_CFLAGS += -DCONFIG_SYS_MEM_2G
endif


################################################
## include path
#################################################
PATH10 = -I$(ROOT)/../thirdparty/mmz
PATH11 = -I$(ROOT)/../TEE_ext/mmz
PATH_VFMW = -I$(ROOT)/../thirdparty/vfmw_code

ifdef COMMON_DRV_INCLUDE
PATH_SDK_COMMON = -I$(COMMON_DRV_INCLUDE)
else
PATH_SDK_COMMON = -I$(ROOT)/../../../../../common/drv/include
endif

#################################################
## include patch
#################################################
INCLUDE := \
$(PATH010) \
$(PATH011) \
$(PATH_VFMW)\
$(PATH_SDK_COMMON)



#################################################
## build script
#################################################


LOCAL_CFLAGS += -O2 -g -W -Wall -fno-omit-frame-pointer

LOCAL_CFLAGS += -march=armv7-a

LOCAL_ASFLAGS += -march=armv7-a

include $(ROOT)/vfmw_code/vfmw_release.cfg

LOCAL_SRC_FILES := $(vfmw_obj_list)

VFMW_LIB := ./libsec_vfmw.a

TRUSTEDCORE_LIB_PATH = $(TRUSTEDCORE_DIR)/release/trustedcore_lib/libtrustedcore.a



##########################################################
# project path definition
##########################################################
ALL_OBJ = $(vfmw_obj_list)
LOCAL_OUT = $(OUT)/thirdparty/$(notdir $(CURDIR))
ALL_OUT_OBJ = $(foreach VAR,$(ALL_OBJ),$(addprefix $(LOCAL_OUT)/,$(VAR)))


CFLAGS += $(INCLUDE)
CFLAGS += $(LOCAL_CFLAGS)

##########################################################
# build rtosck.img
##########################################################
.PHONY : all clean

all : $(VFMW_LIB)

$(VFMW_LIB) : $(ALL_OBJ)
	$(AR) -r $(VFMW_LIB) $(ALL_OUT_OBJ)

clean:
	$(RM) $(VFMW_LIB) $(ALL_OUT_OBJ) $(ALL_OBJ)

%.o : %.c
	$(CC2) -c $(CFLAGS) $< -o $(LOCAL_OUT)/$@

%.o : %.S
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

%.o : %.s
	$(CC2) $(CFLAGS) -c  $< -o $(LOCAL_OUT)/$@

