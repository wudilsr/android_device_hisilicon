#by fangjian00208632 2015-03-13

#====================================================================================
#                   export
#====================================================================================
.EXPORT_ALL_VARIABLES:
include trustedcore.mk

ifeq ($(CONFIG_MEM_LAYOUT),1G)
LOCAL_CFLAGS += -DCONFIG_SYS_MEM_1G
endif

ifeq ($(CONFIG_MEM_LAYOUT),2G)
LOCAL_CFLAGS += -DCONFIG_SYS_MEM_2G
endif

###########################################################
# platform definition
###########################################################
TARGET_IMG = $(OUT)/trustedcore.img
TARGET_IMG_INSTALL_DIR = $(IMAGE_DIR)

##########################################################
# build all
##########################################################
.PHONY : all build packimg clean rtosck globaltask internal_tasks_ext rtosck_clean globaltask_clean internal_tasks_ext_clean xml

all: packimg bootenv xml
packimg: rtosck globaltask internal_tasks_ext
clean: rtosck_clean globaltask_clean internal_tasks_ext_clean bootenv_clean xml_clean
	$(RM) $(TARGET_IMG)
	$(RM) -rf $(OUT)
	$(RM) -rf $(TOOLCHAINS_DIR)/gcc

install: all
	@echo "Install $(TARGET_IMG_INSTALL_DIR)"
	$(COPY) $(TARGET_IMG) $(TARGET_IMG_INSTALL_DIR)

uninstall:
	@echo "Uninstall $(TARGET_IMG_INSTALL_DIR)/$(notdir $(TARGET_IMG))"
	$(RM) $(TARGET_IMG_INSTALL_DIR)/$(notdir $(TARGET_IMG))

$(TOOLCHAINS_DIR)/%/tar:
	@test -d $(@D) || mkdir -p $(@D)
	cd $(TOOLCHAINS_DIR);\
	tar -xjf $(notdir $(@:/tar=)).tar.bz2 -C $(TOOLCHAINS_DIR);\
	cd -
	@touch $@

##########################################################
# 1. build rtosck
##########################################################
rtosck:$(TOOLCHAINS_DIR)/gcc/tar
	$(MAKE) -C trustedcore_kernel/ all
rtosck_clean:
	$(MAKE) -C trustedcore_kernel/ clean

##########################################################
# 2. build globaltask
##########################################################
globaltask:$(TOOLCHAINS_DIR)/gcc/tar
	$(MAKE) -C TEE_ext/ all
globaltask_clean:
	$(MAKE) -C TEE_ext/ clean

##########################################################
# 3. build internal_tasks_ext
##########################################################
internal_tasks_ext:$(TOOLCHAINS_DIR)/gcc/tar
	$(MAKE) -C internal_tasks_ext/ all
internal_tasks_ext_clean:
	$(MAKE) -C internal_tasks_ext/ clean

##########################################################
# 4. packimg
##########################################################
packimg:
	@./packimg.sh $(TRUSTEDCORE_TEXT_BASE)>/dev/null $(OUT)>/dev/null
	@echo "Make $(TARGET_IMG) Success!"

##########################################################
# 5.create bootenv
##########################################################
bootenv:
	@cd ./bootargs;\
	./mk_tee_bootenv_emmc.sh ${SERVER_UNTILS_DIR}/mkbootargs ${CFG_HI_CHIP_TYPE} ${CFG_HI_TVP_MEM_LAYOUT} $(MEM_SIZE) $(MMZ_SIZE) ${TRUSTEDCORE_TASK_BASE} ${CFG_HI_BOOT_ENV_SIZE};\
	cp bootargs_${CFG_HI_CHIP_TYPE}_${CFG_HI_TVP_MEM_LAYOUT}.bin $(IMAGE_DIR)/bootargs_${CFG_HI_CHIP_TYPE}_tvp_emmc.bin;\
	cd -;

bootenv_clean:
	rm -f bootargs_${CFG_HI_CHIP_TYPE}_${CFG_HI_TVP_MEM_LAYOUT}.bin
	rm -f $(IMAGE_DIR)/bootargs_tvp_${CFG_HI_CHIP_TYPE}.bin

##########################################################
# 6. create xml
##########################################################
xml:
	cd ./xml;\
	./mk_xml_emmc.sh ${CFG_HI_CHIP_TYPE};\
	cp partitions_${CFG_HI_CHIP_TYPE}_emmc.xml $(IMAGE_DIR)/partitions_${CFG_HI_CHIP_TYPE}_tvp_emmc.xml;\
	cd -;

xml_clean:
	rm -f partitions_${CFG_HI_CHIP_TYPE}_emmc.xml
	rm -f $(IMAGE_DIR)/partitions_${CFG_HI_CHIP_TYPE}_tvp_emmc.xml

