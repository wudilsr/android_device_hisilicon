
#by fangjian00208632 2015-03-13

###########################################################
# platform definition
###########################################################
ROOT      =.


##########################################################
# build
##########################################################
.PHONY : all clean
.PHONY : rtosck       globaltask         drivers        ta
.PHONY : rtosck_clean globaltask_clean   drivers_clean  ta_clean


all:rtosck globaltask ta 
clean:rtosck_clean globaltask_clean ta_clean


##########################################################
# 1. build rtosck
##########################################################
rtosck:drivers
	$(MAKE) -C trustedcore_kernel/ all
rtosck_clean:drivers_clean
	$(MAKE) -C trustedcore_kernel/ clean

##########################################################
# 2. build globaltask
##########################################################
globaltask:
	$(MAKE) -C TEE_ext/ all
globaltask_clean:
	$(MAKE) -C TEE_ext/ clean

##########################################################
# 3. build libstbdrv.a
##########################################################	
drivers:
	$(MAKE) -C $(HI_TEE_DRV_DIR) all
drivers_clean:
	$(MAKE) -C $(HI_TEE_DRV_DIR) clean

##########################################################
# 4. build ta
##########################################################	
ta:rtosck globaltask
	$(MAKE) -C $(HI_TEE_TA_DIR) all
ta_clean:rtosck_clean globaltask_clean
	$(MAKE) -C $(HI_TEE_TA_DIR) clean
