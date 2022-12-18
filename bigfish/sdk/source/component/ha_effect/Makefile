#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../..

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================

ifneq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)), -DHI_ADVCA_FUNCTION_RELEASE)
CFLAGS += -DCFG_HA_LOG_LEVEL=1
else
export CA_FUNCTION_RELEASE:=YES
endif

CUR= ./

#HEADER_FILES := $(shell pwd)/include/hi_snd_effect.h 

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall ${objects} ${objects_clean} 
	
all:     

	    	
clean: 


install:all
ifeq ($(CFG_HI_HAEFFECT_BASE_SUPPORT),y)
	$(AT)cp -f $(shell pwd)/lib/$(CFG_HI_TOOLCHAINS_NAME)/libhi_aef_base.so $(SHARED_LIB_DIR)/
	$(AT)cp -f  $(shell pwd)/include/hi_aef_base.h     $(INCLUDE_DIR)/
endif
ifeq ($(CFG_HI_HAEFFECT_SRS_SUPPORT),y)
	$(AT)cp -f $(shell pwd)/lib/$(CFG_HI_TOOLCHAINS_NAME)/libHA.AUDIO.SRS.effect.auth.so $(EXTERN_LIB_DIR)/
	$(AT)cp -f $(shell pwd)/lib/$(CFG_HI_TOOLCHAINS_NAME)/libhi_aef_srs.so $(SHARED_LIB_DIR)/
	$(AT)cp -f  $(shell pwd)/include/hi_aef_srs.h     	 $(INCLUDE_DIR)/
endif
uninstall:
ifeq ($(CFG_HI_HAEFFECT_BASE_SUPPORT),y)
	$(AT)rm -rf $(SHARED_LIB_DIR)/libhi_aef_base.so
	$(AT)rm -rf $(INCLUDE_DIR)/hi_aef_base.h
endif
ifeq ($(CFG_HI_HAEFFECT_SRS_SUPPORT),y)
	$(AT)rm -rf $(EXTERN_LIB_DIR)/libHA.AUDIO.SRS.effect.auth.so
	$(AT)rm -rf $(SHARED_LIB_DIR)/libhi_aef_srs.so
	$(AT)rm -rf $(INCLUDE_DIR)/hi_aef_srs.h
endif
	
${objects}:
	make -C $@

${objects_clean}:
	make -C ${patsubst %_clean,%,$@} clean


