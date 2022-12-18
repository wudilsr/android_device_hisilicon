#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/../..
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
objects :=  adac        \
            adec        \
            adsp        \
            aenc        \
            ai          \
            aiao        \
            ao          \
            aflt        \
            avplay      \
            ci          \
            cimaxplus   \
            cipher      \
            demux       \
            dmac        \
            frontend    \
            gpio        \
            gpu         \
            hdcp        \
            hdmi        \
            hdmirx      \
            hifb        \
            higo        \
            i2c         \
            ir          \
            jpeg        \
            jpge        \
            keyled      \
            mce         \
            ndpt        \
            omx         \
            omxvdec     \
            otp         \
            pdm         \
            pm          \
            png         \
            pvr         \
            sci         \
            spi         \
            sync        \
            tde         \
            vad         \
            vdec        \
            venc        \
            vfmw        \
            vpu         \
            vi          \
            vo          \
            pq          \
            vpss        \
            pwm         \
            wdg         \
            advca

objects_clean       := $(addsuffix _clean, $(objects))
objects_install     := $(addsuffix _install, $(objects))
objects_uninstall   := $(addsuffix _uninstall, $(objects))

depends := $(obj)
ifeq ($(depends),)
depends += drv
depends += api
endif

depends_clean       := $(addsuffix _clean, $(depends))
depends_install     := $(addsuffix _install, $(depends))
depends_uninstall   := $(addsuffix _uninstall, $(depends))

HEADER_FILES := $(wildcard $(MSP_UNF_INCLUDE)/*.h)          \
                $(MSP_DIR)/api/tde/include/hi_tde_api.h     \
                $(MSP_DIR)/api/tde/include/hi_tde_errcode.h \
                $(MSP_DIR)/api/tde/include/hi_tde_type.h    \
                $(MSP_DIR)/drv/hifb/include/hifb.h

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#   rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall

all: $(depends)

clean: $(depends_clean)

install: $(depends_install)

uninstall: $(depends_uninstall)

#==================================================================
#                          drv
#==================================================================
.PHONY: drv drv_clean drv_install drv_uninstall

drv:
	make -C drv all

drv_clean:
	make -C drv clean

drv_install:
	make -C drv install

drv_uninstall:
	make -C drv uninstall

#==================================================================
#                          api
#==================================================================
.PHONY: api api_clean api_install api_uninstall

api:
	$(AT)make -C api all

api_clean:
	$(AT)make -C api clean

api_install:
	$(AT)make -C api install
	$(AT)cp -f  $(HEADER_FILES)     $(INCLUDE_DIR)/

api_uninstall:
	$(AT)make -C api uninstall
	$(AT)rm -rf $(foreach file, $(HEADER_FILES), $(INCLUDE_DIR)/$(notdir $(file)))

#==================================================================
#                          modules
#==================================================================
.PHONY: $(objects) $(objects_clean) $(objects_install) $(objects_uninstall)

$(objects):
	$(AT)test ! -d drv/$@ || make -C drv/$@ all
	$(AT)test ! -d api/$@ || make -C api target DIR=$@

$(objects_clean):
	$(AT)test ! -d drv/$(patsubst %_clean,%,$@) || make -C drv/$(patsubst %_clean,%,$@) clean
	$(AT)test ! -d api/$(patsubst %_clean,%,$@) || make -C api target_clean DIR=$(patsubst %_clean,%,$@)

$(objects_install):
	$(AT)test ! -d drv/$(patsubst %_install,%,$@) || make -C drv/$(patsubst %_install,%,$@) install
	$(AT)test ! -d api/$(patsubst %_install,%,$@) || make -C api target_install DIR=$(patsubst %_install,%,$@)

$(objects_uninstall):
	$(AT)test ! -d drv/$(patsubst %_uninstall,%,$@) || make -C drv/$(patsubst %_uninstall,%,$@) uninstall
	$(AT)test ! -d api/$(patsubst %_uninstall,%,$@) || make -C api target_uninstall DIR=$(patsubst %_uninstall,%,$@)

