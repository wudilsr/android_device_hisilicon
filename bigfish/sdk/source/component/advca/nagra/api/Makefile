#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../../..
include $(SDK_DIR)/base.mak
endif

SDK_SECURITY_ARCH_VERSION=SDK_SECURITY_ARCH_VERSION_V3

CFLAGS += -D$(SDK_SECURITY_ARCH_VERSION)

#===============================================================================
# local variable
#===============================================================================
CFLAGS += $(CFG_HI_CFLAGS)
CFLAGS += $(CFG_CFLAGS)

CFLAGS += -I$(ADVCA_TYPE_DIR)/include					\
			-I$(MSP_UNF_INCLUDE)                    	\
			-I$(MSP_API_INCLUDE)						\
			-I$(MSP_DRV_INCLUDE)						\
	  		-I$(COMMON_UNF_INCLUDE)						\
	  		-I$(COMMON_DRV_INCLUDE)						\
	  		-I$(COMMON_API_INCLUDE)						\
			-I$(ADVCA_COMMON_SRC_DIR)/drv/include		\
	  		-I$(ADVCA_COMMON_SRC_DIR)/include			\
			-I$(ADVCA_COMMON_DIR)/drv/include			\
	  		-I$(ADVCA_COMMON_DIR)/include				\
	  		-I$(ADVCA_DIR)/nagra/include                \
	  		-I$(MSP_DRV_INCLUDE)/../advca/ca_otp/ca_otpv200

HEADER_FOLDER := $(ADVCA_DIR)/$(ADVCA_TYPE_DIR)/include

LIBS := libhi_$(CFG_ADVCA_PATH_NAME)

OBJS=$(patsubst %.c,%.o,$(wildcard ./*.c))

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all: $(LIBS)

$(LIBS) : $(OBJS)
	$(AT)$(AR) -rc -o $@.a $^
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)$(CC) -shared -o $@.so $^
endif

install: all
	$(AT)cp -f  $(LIBS).a 							$(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -f  $(LIBS).so         					$(SHARED_LIB_DIR)/
endif
	$(AT)cp -f  $(HEADER_FOLDER)/nocs_csd.h 					$(INCLUDE_DIR)/
	$(AT)cp -f  $(HEADER_FOLDER)/nocs_csd_impl.h				$(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS).a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS).so
	$(AT)rm -rf $(INCLUDE_DIR)/nocs_csd_impl.h
	$(AT)rm -rf $(INCLUDE_DIR)/nocs_csd.h

clean:
	$(AT)rm -rf  $(LIBS).a
	$(AT)rm -rf  $(LIBS).so
	$(AT)rm -rf  *.o
