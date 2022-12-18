#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..
include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
EXTRA_CFLAGS += $(CFG_HI_CFLAGS)
EXTRA_CFLAGS += $(CFG_CFLAGS)
EXTRA_CFLAGS += -I$(KCOM_DIR)/drv/include          \
			-I$(KCOM_DIR)/include                   \
			-I$(ADVCA_TYPE_DIR)/drv/include         \
			-I$(KECS_DIR)/drv/include               \
			-I$(KECS_DIR)/include					\
			-I$(ADVCA_COMMON_DIR)/include               	\
			-I$(ADVCA_COMMON_DIR)/drv						\
			-I$(ADVCA_COMMON_DIR)/drv/V200					\
			-I$(ADVCA_COMMON_DIR)/drv/V300					\
			-I$(ADVCA_COMMON_DIR)/drv/ca_otp				\
			-I$(ADVCA_COMMON_DIR)/drv/ca_otp/ca_otpv100		\
			-I$(ADVCA_COMMON_DIR)/drv/ca_otp/ca_otpv200		\
			-I$(ADVCA_COMMON_SRC_DIR)/include             	\
			-I$(ADVCA_COMMON_SRC_DIR)/drv					\
			-I$(ADVCA_COMMON_SRC_DIR)/drv/V200				\
			-I$(ADVCA_COMMON_SRC_DIR)/drv/V300				\
			-I$(ADVCA_COMMON_SRC_DIR)/drv/ca_otp			\
			-I$(ADVCA_COMMON_SRC_DIR)/drv/ca_otp/ca_otpv100	\
			-I$(ADVCA_COMMON_SRC_DIR)/drv/ca_otp/ca_otpv200	\
			-I$(COMMON_UNF_INCLUDE)                 \
            -I$(COMMON_API_INCLUDE)                 \
            -I$(MSP_UNF_INCLUDE)                    \
			-I$(MSP_DRV_INCLUDE)					\
            -I$(MSP_API_INCLUDE)
	    
ifndef ADVCA_DIR
ADVCA_DIR = $(COMPONENT_DIR)/advca
endif

#===============================================================================
# rules
#===============================================================================
.PHONY : all clean api apiclean install uninstall release

all : api

api:
	$(AT)make -C api COMPILELIB_TOOLCHAINS_NAME=$(CFG_HI_TOOLCHAINS_NAME)

apiclean:
	$(AT)make -C api clean

install: all
	$(AT)make -C api install

uninstall: clean
	$(AT)make -C api uninstall

clean: apiclean

