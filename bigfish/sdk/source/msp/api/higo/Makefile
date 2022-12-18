#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(shell cd $(CURDIR)/../../../.. && /bin/pwd)

include $(SDK_DIR)/base.mak
endif

#===============================================================================
# local variable
#===============================================================================
HIGO_DIR := $(shell pwd)

#===============================================================================
#real higo dir
#===============================================================================
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
  HIGO_GHFP_DIR := $(HIGO_DIR)/lib/loader/$(CFG_HI_TOOLCHAINS_NAME)
else
  ifeq ($(CFG_LIB_JPEG_VERSION_6B),y)
    HIGO_GHFP_DIR = $(HIGO_DIR)/lib/libjpeg-6b/$(CFG_HI_TOOLCHAINS_NAME)
  else
    HIGO_GHFP_DIR = $(HIGO_DIR)/lib/libjpeg-9a/$(CFG_HI_TOOLCHAINS_NAME)
  endif
endif

HEADER_FILES := $(HIGO_DIR)/include/hi_go_winc.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_text.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_surface.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_gdev.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_errno.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_encoder.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_decoder.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_cursor.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_comm.h
HEADER_FILES += $(HIGO_DIR)/include/hi_go_bliter.h
HEADER_FILES += $(HIGO_DIR)/include/hi_effect.h

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)test -d $(INCLUDE_DIR) || mkdir -p $(INCLUDE_DIR)
	$(AT)cp -rf $(HEADER_FILES) $(INCLUDE_DIR)/
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)test -d $(STATIC_LIB_DIR) || mkdir -p $(STATIC_LIB_DIR)
    ifeq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)),)
	$(AT)cp -rf $(HIGO_GHFP_DIR)/nca_lib/*.a        $(STATIC_LIB_DIR)/
    else
	$(AT)cp -rf $(HIGO_GHFP_DIR)/ca_lib/*.a         $(STATIC_LIB_DIR)/
    endif
else
	$(AT)test -d $(STATIC_LIB_DIR) || mkdir -p $(STATIC_LIB_DIR)
	$(AT)test -d $(SHARED_LIB_DIR) || mkdir -p $(SHARED_LIB_DIR)
	$(AT)test -d $(EXTERN_LIB_DIR) || mkdir -p $(EXTERN_LIB_DIR)
	$(AT)cp -rf $(HIGO_GHFP_DIR)/nca_lib/*.so       $(SHARED_LIB_DIR)/
	$(AT)cp -rf $(HIGO_GHFP_DIR)/higo-adp           $(EXTERN_LIB_DIR)/
    ifeq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)),)
	$(AT)cp -rf $(HIGO_GHFP_DIR)/nca_lib/*.a        $(STATIC_LIB_DIR)/
    else
	$(AT)cp -rf $(HIGO_GHFP_DIR)/ca_lib/*.a         $(STATIC_LIB_DIR)/
    endif
endif

clean:
	$(AT)rm -rf $(SHARED_LIB_DIR)/libhigo*.so
	$(AT)rm -rf $(SHARED_LIB_DIR)/libeffect.so
	$(AT)rm -rf $(EXTERN_LIB_DIR)/higo-adp
	$(AT)rm -rf $(STATIC_LIB_DIR)/libhigo*.a
	$(AT)rm -rf $(STATIC_LIB_DIR)/libeffect.a
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

install:all

uninstall:clean
