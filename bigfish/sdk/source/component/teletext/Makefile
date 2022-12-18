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
LIBS := libhi_ttx

HEADER_FILES := $(CURDIR)/include/hi_unf_ttx.h

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:

clean:

install: all
ifdef CFG_HI_ADVCA_FUNCTION
	$(AT)cp -f ./lib/$(CFG_HI_TOOLCHAINS_NAME)/$(LIBS)_advca.a  $(STATIC_LIB_DIR)/$(LIBS).a
else
	$(AT)cp -f ./lib/$(CFG_HI_TOOLCHAINS_NAME)/$(LIBS).a        $(STATIC_LIB_DIR)/
	$(AT)cp -f ./lib/$(CFG_HI_TOOLCHAINS_NAME)/$(LIBS).so       $(SHARED_LIB_DIR)/
endif
	$(AT)cp -f  $(HEADER_FILES)     $(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS).a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS).so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

