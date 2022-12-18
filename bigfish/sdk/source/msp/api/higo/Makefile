HIGOLIB=$(shell pwd)

#===============================================================================
# export variable
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR ?= $(CURDIR)/../../../..

include $(SDK_DIR)/base.mak
endif

TARGET := higo


#===============================================================================
# local variable
#===============================================================================
HIGO_CHIP_VER = ghfp

ifeq ($(CFG_LIB_JPEG_VERSION_6B),y)
HIGO_STORE_LIB_VER = libjpeg6b_libpng1.4.0
else ifeq ($(CFG_LIB_JPEG_VERSION_9A),y)
HIGO_STORE_LIB_VER = libjpeg9a_libpng1.6.16
endif

ifeq ($(CFG_LIB_PNG_VERSION_1_6_16),y)
HIGO_STORE_LIB_VER = libjpeg9a_libpng1.6.16
endif

ifeq ($(CFG_HI_TOOLCHAINS_NAME),arm-hisiv200-linux)
HIGO_CHIP_VER = ghfp
endif

ifeq ($(CFG_HI_TOOLCHAINS_NAME),arm-histbv300-linux)
ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
HIGO_CHIP_VER = hisiv300_a7
else
HIGO_CHIP_VER = hisiv300_a9
endif
endif

#===============================================================================
#real higo dir
#===============================================================================
NEED_HIGO_GHFP_DIR := $(HIGOLIB)/store/higo_release_v1r2_$(HIGO_CHIP_VER)_$(HIGO_STORE_LIB_VER)

#===============================================================================
# local variable
#===============================================================================

HEADER_FILES := $(MSP_DIR)/api/$(TARGET)/include/hi_go_winc.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_text.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_surface.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_gdev.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_errno.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_encoder.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_decoder.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_cursor.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_comm.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_go_bliter.h
HEADER_FILES += $(MSP_DIR)/api/$(TARGET)/include/hi_effect.h

#===============================================================================
# rules
#===============================================================================
.PHONY: all clean install uninstall

all:
	$(AT)test -e $(HIGOLIB)/lib/higo-adp/decoder || mkdir -p $(HIGOLIB)/lib/higo-adp/decoder
	$(AT)test -e $(HIGOLIB)/lib/higo-adp/encoder || mkdir -p $(HIGOLIB)/lib/higo-adp/encoder
	$(AT)test -e $(HIGOLIB)/lib/higo-adp/font    || mkdir -p $(HIGOLIB)/lib/higo-adp/font
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/r_dynamic/*.so          $(HIGOLIB)/lib
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/r_dynamic/higo-adp/decoder/*.so $(HIGOLIB)/lib/higo-adp/decoder
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/r_dynamic/higo-adp/encoder/*.so $(HIGOLIB)/lib/higo-adp/encoder
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/r_dynamic/higo-adp/font/*.so $(HIGOLIB)/lib/higo-adp/font
	$(AT)test -e $(HIGOLIB)/lib/cut-obj || mkdir -p $(HIGOLIB)/lib/cut-obj
ifneq ($(findstring -DHI_ADVCA_FUNCTION_RELEASE, $(CFG_HI_CFLAGS)),)
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/ca_static/*.a         $(HIGOLIB)/lib
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/ca_static/cut-obj/*.o $(HIGOLIB)/lib/cut-obj
else
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/r_static/*.a         $(HIGOLIB)/lib
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/r_static/cut-obj/*.o $(HIGOLIB)/lib/cut-obj
endif
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/effect/lib/*.a       $(HIGOLIB)/lib
	$(AT)cp -a $(NEED_HIGO_GHFP_DIR)/effect/lib/*.so       $(HIGOLIB)/lib

clean:
	$(AT)rm -rf lib/*

install: all
	$(AT)if [ -z $(CFG_HI_PNG_DECODER_SUPPORT) ] ; then \
            rm -f  $(EXTERN_LIB_DIR)/higo-adp/decoder/libhigo_png.so; \
            $(AR) -r lib/libhigoadp.a lib/cut-obj/higoimageproviderdec_png.o; \
        fi
	$(AT)if [ -z $(CFG_HI_FREETYPE_FONT_SUPPORT) ] ; then \
            rm -f  $(EXTERN_LIB_DIR)/higo-adp/font/libhigo_freetype2.so; \
            $(AR) -r lib/libhigo.a lib/cut-obj/higofontprovider_freetype.o; \
	    fi
	$(AT)cp -rf  $(HEADER_FILES)     $(INCLUDE_DIR)/
ifndef CFG_HI_STATIC_LIB_ONLY
	$(AT)cp -rf  lib/*.so            $(SHARED_LIB_DIR)/
	$(AT)cp -rf  lib/higo-adp        $(EXTERN_LIB_DIR)/
endif
	$(AT)cp -rf  lib/*.a             $(STATIC_LIB_DIR)/

uninstall:
	$(AT)rm -rf $(SHARED_LIB_DIR)/libhigo*.so
	$(AT)rm -rf $(SHARED_LIB_DIR)/libeffect.so
	$(AT)rm -rf $(EXTERN_LIB_DIR)/higo-adp
	$(AT)rm -rf $(STATIC_LIB_DIR)/libhigo*.a
	$(AT)rm -rf $(STATIC_LIB_DIR)/libeffect.a
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))
