
#by fangjian00208632 2015-03-13
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

###########################################################
# platform definition
###########################################################
MAKE      =make
AR        =$(CROSS_COMPILE)ar
LD        =$(CROSS_COMPILE)ld
CC        =$(CROSS_COMPILE)gcc
CPP       =$(CROSS_COMPILE)g++
RM        =rm -f
COPY      =cp
ROOT      =$(shell pwd)

#Config Trusted Storage Path must end with '/'
CFG_TEE_STORAGE_DIR ?= /root/

#############################
## libteec.so
#############################
LOCAL_SRC_FILES := src/tee_client_api.o \
                   src/tee_client_storage_api.o \
                   src/tee_client_app_load.o \
                   src/tee_client_random_api.o \
                   src/tee_client_time_api.o

LOCAL_C_INCLUDES := -I$(ROOT)/inc
                    
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100 hi3716dv100),)
LOCAL_SRC_FILES += sec_mmz/src/sec_mmz.o
LOCAL_C_INCLUDES += -I$(ROOT)/sec_mmz/inc
endif

##########################################################
# CFLAGS definition
##########################################################
CFLAGS += -Os -Wall -fPIC
ifeq ($(CFG_HI_CPU_ARCH), arm)
CFLAGS += -march=armv7-a -mthumb
endif
CFLAGS += $(LOCAL_C_INCLUDES)
CFLAGS += $(LOCAL_CFLAGS)

ifeq ($(O),)
ifeq ($(firstword $(subst -, ,$(CROSS_COMPILE))),aarch64)
OUT_DIR := $(HI_OUT_DIR)/obj64/$(subst $(SDK_DIR)/,,$(CURDIR))/

TARGET_SLIB_OUT_DIR = $(HI_STATIC_LIB64_DIR)
TARGET_DLIB_OUT_DIR = $(HI_SHARED_LIB64_DIR)
else
OUT_DIR := $(HI_OUT_DIR)/obj/$(subst $(SDK_DIR)/,,$(CURDIR))/

TARGET_SLIB_OUT_DIR = $(HI_STATIC_LIB_DIR)
TARGET_DLIB_OUT_DIR = $(HI_SHARED_LIB_DIR)
endif
else
OUT_DIR := ${O}
TARGET_SLIB_OUT_DIR = $(HI_STATIC_LIB_DIR)
TARGET_DLIB_OUT_DIR = $(HI_SHARED_LIB_DIR)
endif
ALL_OBJ := $(addprefix $(OUT_DIR),$(LOCAL_SRC_FILES))

LDFLAGS +=

LIB_NAME := libteec

##########################################################
# build
##########################################################
.PHONY : all clean libteec teecd test libteec_clean teecd_clean test_clean

all: teecd libteec
	test -d $(TARGET_SLIB_OUT_DIR) || mkdir -p $(TARGET_SLIB_OUT_DIR)
	$(COPY) $(OUT_DIR)$(LIB_NAME).a $(TARGET_SLIB_OUT_DIR)/
	test -d $(TARGET_DLIB_OUT_DIR) || mkdir -p $(TARGET_DLIB_OUT_DIR)
	$(COPY) $(OUT_DIR)$(LIB_NAME).so $(TARGET_DLIB_OUT_DIR)/

test: libteec

clean: libteec_clean teecd_clean test_clean
	$(RM) $(TARGET_SLIB_OUT_DIR)/$(LIB_NAME).a $(TARGET_DLIB_OUT_DIR)/$(LIB_NAME).so

##########################################################
# 1. build libteec
##########################################################
libteec: $(ALL_OBJ)
	$(CC) $(LDFLAGS) -shared -o $(OUT_DIR)$(LIB_NAME).so $(ALL_OBJ)
	$(AR) -rc -o $(OUT_DIR)$(LIB_NAME).a $(ALL_OBJ)
	@echo "Make $(LIB_NAME) Success!"

libteec_clean:
	$(RM) $(OUT_DIR)$(LIB_NAME)* $(ALL_OBJ)

$(OUT_DIR)%.o : %.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) $< -o $@

##########################################################
# build test
##########################################################
test: libteec
	make -C $(ROOT)/test/ all

test_install:
	make -C $(ROOT)/test/ install

test_uninstall:
	make -C $(ROOT)/test/ uninstall

test_clean:
	make -C $(ROOT)/test/ clean
#############################
## 2. build teecd
#############################
#add by q00209673 for bootloaderlockstatus
WITH_K3V3_FPGA=false
ifeq ($(strip $(WITH_K3V3_FPGA)), true)
TEECD_CFLAGS += -DK3V3_FPGA
endif
RPMB_FEATURE_ENABLED=false
ifeq ($(RPMB_FEATURE_ENABLED),true)
TEECD_CFLAGS += -DTEE_SUPPORT_RPMB_DEVICE
endif

#TEECD_SRC_FILES := src/tee_agent.o
#                  src/tee_nv_info.o
#		  src/tee_get_app_cert.c \
#		  src/tee_ca_daemon.c
TEECD_C_INCLUDES := -I$(ROOT)/inc
#		    $(LOCAL_PATH)/../../../../external/libxml2/include/libxml \
#		    $(LOCAL_PATH)/../../../../external/libxml2/include \
#                    $(LOCAL_PATH)/../../../../external/openssl/include/ \
#		    $(LOCAL_PATH)/../../../../external/icu/icu4c/source/common/

#LOCAL_STATIC_LIBRARIES := libxml2 libc libm libcutils liblog libicuuc_static libcrypto_static
#ifneq ($(strip $(WITH_K3V3_FPGA)), true)
#LOCAL_STATIC_LIBRARIES += libnve
#endif
TEECD_CFLAGS += $(TEECD_C_INCLUDES)
TEECD_CFLAGS += -Os -Wall
ifeq ($(CFG_HI_CPU_ARCH), arm)
TEECD_CFLAGS += -march=armv7-a -mthumb
endif
TEECD_CFLAGS += -DCFG_TEE_STORAGE_DIR=\"$(CFG_TEE_STORAGE_DIR)\"

TEECD_OBJ = $(addprefix $(OUT_DIR),src/tee_agent.o src/tee_ca_daemon.o src/tee_get_app_cert.o)
TEECD_EXE = $(OUT_DIR)teecd

teecd: $(TEECD_OBJ)
	$(CC) -static -o $(TEECD_EXE) $(TEECD_OBJ) -lpthread

teecd_clean:
	$(RM) $(TEECD_EXE) $(TEECD_OBJ)

$(TEECD_OBJ): $(OUT_DIR)%.o : %.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	$(CC) -c $(TEECD_CFLAGS) $< -o $@

