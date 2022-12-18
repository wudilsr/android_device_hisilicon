#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..

include $(SDK_DIR)/base.mak
endif


#===============================================================================
# standard jpeg dir
#===============================================================================
TARGET := jpeg
#===============================================================================
# local variable
#===============================================================================
LIBS := libjpeg

ifeq ($(CFG_LIB_JPEG_VERSION_6B),y)
LIB_VER := 6b
else ifeq ($(CFG_LIB_JPEG_VERSION_9A),y)
LIB_VER := 9a
endif

HEADER_FILES := $(MSP_DIR)/api/$(TARGET)/inc/inc_${LIB_VER}/jpeglib.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/inc/inc_${LIB_VER}/jmorecfg.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/inc/inc_${LIB_VER}/jerror.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/inc/inc_${LIB_VER}/jconfig.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/inc/inc_hard/hi_jpeg_api.h


#===============================================================================
# rules  use -a to copy with the link lib
#===============================================================================
.PHONY: all clean install uninstall

all: $(LIBS)

clean:
	$(AT)cd src && make -f Makefile-$(LIB_VER) clean
	$(AT)rm -rf src/$(LIBS)*.so src/$(LIBS)*.a

install: all
	$(AT)cp -af  src/$(LIBS)*.a           $(STATIC_LIB_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -af  src/$(LIBS)*.so          $(SHARED_LIB_DIR)/
endif
	$(AT)cp -f  $(HEADER_FILES)           $(INCLUDE_DIR)/

uninstall:
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS)*.a $(SHARED_LIB_DIR)/$(LIBS)*.so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

$(LIBS):
	$(AT)rm -rf src/$(LIBS)*.a src/$(LIBS)*.so
	$(AT)cd src && make -f Makefile-$(LIB_VER)
