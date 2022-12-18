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
LIB_VER = 6b

#===============================================================================
# local variable
#===============================================================================
LIBS := libjpeg


ifeq (${CFG_HI_LIB_JPEG_VERSION},libjpeg-9a)
LIB_VER = 9a
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
	$(AT)cp src/Makefile-${LIB_VER} src/Makefile
	make -C src clean
	$(AT)rm -rf src/$(LIBS)*.so
	$(AT)rm -rf src/$(LIBS)*.a
install: all
	$(AT)cp src/Makefile-${LIB_VER} src/Makefile
	$(AT)cp -f  src/$(LIBS)*.a            $(STATIC_LIB_DIR)/  -a
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -f  src/$(LIBS)*.so           $(SHARED_LIB_DIR)/  -a
endif	
	$(AT)cp -f  $(HEADER_FILES)           $(INCLUDE_DIR)/

uninstall:
	$(AT)cp src/Makefile-${LIB_VER} src/Makefile
	$(AT)rm -rf $(STATIC_LIB_DIR)/$(LIBS)*.a
	$(AT)rm -rf $(SHARED_LIB_DIR)/$(LIBS)*.so
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

$(LIBS) :
	$(AT)cp src/Makefile-${LIB_VER} src/Makefile
	$(AT)rm -rf src/$(LIBS)*.a
	$(AT)rm -rf src/$(LIBS)*.so 
	make -C src
