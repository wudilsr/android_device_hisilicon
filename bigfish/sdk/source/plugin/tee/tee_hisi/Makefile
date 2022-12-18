#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
.EXPORT_ALL_VARIABLES:
_CURDIR = $(if $(CURDIR),$(CURDIR),$(PWD))
SDK_DIR := $(_CURDIR)/../../../..
include $(SDK_DIR)/base.mak
endif

export IMAGE_DIR
export STATIC_LIB_DIR
export ROOTBOX_DIR
export LIB_DIR
export SHARED_LIB_DIR
export BIN_DIR
export MSP_UNF_INCLUDE

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#       variable
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

objects += libteec trustedcore

objects_clean:=${addsuffix _clean,${objects}}
objects_install:=${addsuffix _install,${objects}}
objects_uninstall:=${addsuffix _uninstall,${objects}}

ifeq (${obj},)
depends:=$(objects)
else
depends:=${obj}
endif
depends_clean:=$(addsuffix _clean,${depends})
depends_install:=$(addsuffix _install,${depends})
depends_uninstall:=$(addsuffix _uninstall,${depends})

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#	rules
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#==================================================================
#                          all
#==================================================================
.PHONY: all clean install uninstall
all:    ${depends}

clean:  ${depends_clean}

install:${depends_install}

uninstall:${depends_uninstall}

#==================================================================
#                          modules
#==================================================================
.PHONY: ${objects} ${objects_clean} ${objects_install} ${objects_uninstall}

${objects}:
	make -C $@ all

${objects_clean}:
	make -C $(patsubst %_clean,%,$@) clean

${objects_install}:
	make -C $(patsubst %_install,%,$@) install

${objects_uninstall}:
	make -C $(patsubst %_uninstall,%,$@) uninstall

