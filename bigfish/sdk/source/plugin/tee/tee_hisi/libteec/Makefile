
#by fangjian00208632 2015-03-13


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


ifeq ($(CFG_HI_TVP_SUPPORT), y)
LOCAL_CFLAGS += -DHI_TVP_SUPPORT
endif

##########################################################
# CFLAGS definition
##########################################################
CFLAGS += -Os -Wall -fPIC -march=armv7-a -mthumb

##########################################################
# project objects
##########################################################

ifeq ($(CFG_HI_TZINFRA_ENABLE), y)
LIB_OBJ := $(ROOT)/src/tee_client_api.o \
                   $(ROOT)/src/tee_client_storage_api.o \
                   $(ROOT)/src/tee_client_app_load.o \
                   $(ROOT)/src/tee_client_random_api.o \
                   $(ROOT)/src/tee_client_time_api.o \
                   $(ROOT)/src/DxTzClientAPI.o
else
LIB_OBJ := $(ROOT)/src/tee_client_api.o \
                   $(ROOT)/src/tee_client_storage_api.o \
                   $(ROOT)/src/tee_client_app_load.o \
                   $(ROOT)/src/tee_client_random_api.o \
                   $(ROOT)/src/tee_client_time_api.o \
		   $(ROOT)/sec_mmz/src/sec_mmz.o
endif

ALL_OBJ += $(LIB_OBJ)

LOCAL_C_INCLUDES := -I$(ROOT)/inc \
                    -I$(ROOT)/sec_mmz/inc

CFLAGS += $(LOCAL_C_INCLUDES)
CFLAGS += $(LOCAL_CFLAGS)

LDFLAGS +=

LIB_OUT_DIR = $(ROOT)/bin
TARGET_STATIC_LIB = $(LIB_OUT_DIR)/libteec.a
TARGET_SHARED_LIB = $(LIB_OUT_DIR)/libteec.so
TARGET_SLIB_OUT_DIR = $(STATIC_LIB_DIR)
TARGET_DLIB_OUT_DIR = $(SHARED_LIB_DIR)

##########################################################
# build
##########################################################
.PHONY : all clean libteec test  libteec_clean test_clean

all: libteec test

clean:libteec_clean test_clean

install: all
	$(COPY) $(TARGET_STATIC_LIB) $(TARGET_SLIB_OUT_DIR)
	$(COPY) $(TARGET_SHARED_LIB) $(TARGET_DLIB_OUT_DIR)

uninstall:
	$(RM) $(TARGET_SLIB_OUT_DIR)/$(notdir $(TARGET_STATIC_LIB))
	$(RM) $(TARGET_DLIB_OUT_DIR)/$(notdir $(TARGET_SHARED_LIB))
	$(RM) $(ROOTBOX_DIR)/lib/$(notdir $(TARGET_STATIC_LIB))
	$(RM) $(ROOTBOX_DIR)/lib/$(notdir $(TARGET_SHARED_LIB))

##########################################################
# build libteec
##########################################################
libteec: $(ALL_OBJ)
	@echo $(ALL_OBJ)
	@test -d $(LIB_OUT_DIR) || mkdir $(LIB_OUT_DIR)
	$(CC) $(LDFLAGS) -shared -o $(TARGET_SHARED_LIB) $(ALL_OBJ)
	$(AR) -rc -o $(TARGET_STATIC_LIB) $(ALL_OBJ)
	@echo "Make $(TARGET_STATIC_LIB) $(TARGET_SHARED_LIB) Success!"

libteec_clean:
	$(RM) $(TARGET_SHARED_LIB)
	$(RM) $(TARGET_STATIC_LIB)
	$(RM) $(ALL_OBJ)

%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

##########################################################
# build teecd
##########################################################
TEECD_OBJ = $(ROOT)/src/tee_agent.o

$(ROOT)/src/tee_agent.o:$(ROOT)/src/tee_agent.c
	$(CC) -c $(CFLAGS) -DK3V3_FPGA_OR_STB $< -o $@

teecd:$(TEECD_OBJ)
	$(CC) -static -o $(ROOT)/bin/teecd $(ROOT)/src/tee_agent.o -lpthread

teecd_clean:
	rm -f $(ROOT)/bin/teecd

##########################################################
# build test
##########################################################
test: teecd
	make -C $(ROOT)/test/ all

test_install:
	make -C $(ROOT)/test/ install

test_uninstall:
	make -C $(ROOT)/test/ uninstall

test_clean: teecd_clean
	make -C $(ROOT)/test/ clean

