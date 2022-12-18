
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
###########################################################
ROOT      =.


##########################################################
# build
##########################################################
.PHONY : all clean tzarch tzarch_clean

ifneq ($(strip $(CONFIG_TRUSTEDCORE_RELEASE)),true)
ALL_TARGET := tzarch
ALL_CLEAN  := tzarch_clean
else
ALL_TARGET :=
ALL_CLEAN  :=
endif

all: $(ALL_TARGET)
	$(MAKE) -C $(ROOT)/$(PLATFORM_DIR_NAME)/ all
	
clean: $(ALL_CLEAN)
	$(MAKE) -C $(ROOT)/$(PLATFORM_DIR_NAME)/ clean
	
tzarch:
	$(MAKE) -C $(ROOT)/tzarch/ all

tzarch_clean:
	 $(MAKE) -C $(ROOT)/tzarch/ clean
