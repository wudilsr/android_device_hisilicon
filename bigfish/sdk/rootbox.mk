#===============================================================================
# local variables
#===============================================================================
#MKNOD := $(shell which mknod)
#CHMOD := $(shell which chmod)
#CHOWN := $(shell which chown)

#===============================================================================
# rule
#===============================================================================
.PHONY: mkload rootbox_compose rootbox_strip rootbox_chmod

mkload:
	make -C $(SCRIPTS_DIR) load_install

rmload:
	make -C $(SCRIPTS_DIR) load_uninstall

rootbox_compose: mkload
ifdef CFG_HI_ADVCA_FUNCTION
	-$(AT)chmod 777 -R $(ROOTBOX_DIR)
endif

	-$(AT)$(SRM) -rf $(ROOTBOX_DIR)
	-$(AT)cp -rf $(ROOTFS_DIR) $(ROOTBOX_DIR)
	-$(AT)cp -rf $(MODULE_DIR) $(ROOTBOX_DIR)
ifeq ($(CFG_HI_ROOTFS_INSTALL_SHARED_LIBS),y)
	-$(AT)cp -rf $(SHARED_LIB_DIR)/*.so*    $(ROOTBOX_DIR)/usr/lib
	-$(AT)cp -rf $(EXTERN_LIB_DIR)/*.so*    $(ROOTBOX_DIR)/usr/lib
	-$(AT)cp -rf $(EXTERN_LIB_DIR)/higo-adp $(ROOTBOX_DIR)/usr/lib
endif
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	-$(AT)cp -rf $(COMPONENT_DIR)/loader/app/release/*   $(ROOTBOX_DIR)/home
ifeq ($(CFG_HI_LOADER_LOG_DISABLE),y)
	$(AT)if [ -f $(ROOTBOX_DIR)/etc/profile ]; then \
		echo "sleep 3" >> $(ROOTBOX_DIR)/etc/profile; \
		echo "cd /home && ./loader 1>/dev/null 2>&1" >> $(ROOTBOX_DIR)/etc/profile; \
		echo "reboot 1>/dev/null 2>&1" >> $(ROOTBOX_DIR)/etc/profile; \
	fi
else
	$(AT)if [ -f $(ROOTBOX_DIR)/etc/profile ]; then \
		echo "sleep 3" >> $(ROOTBOX_DIR)/etc/profile; \
		echo "cd /home && ./loader" >> $(ROOTBOX_DIR)/etc/profile; \
		echo "reboot 1>/dev/null 2>&1" >> $(ROOTBOX_DIR)/etc/profile; \
	fi
endif	
endif
	-$(AT)mknod $(ROOTBOX_DIR)/dev/console c 5 1
	-$(AT)mknod $(ROOTBOX_DIR)/dev/ttyAMA0 c 204 64
	-$(AT)mknod $(ROOTBOX_DIR)/dev/ttyAMA1 c 204 65
	-$(AT)mknod $(ROOTBOX_DIR)/dev/ttyS000 c 204 64
ifdef CFG_HI_ADVCA_FUNCTION
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	$(AT)test -d $(ROOTFS_SRC_DIR)/scripts/hica_etc/loader_etc || tar xzf $(ROOTFS_SRC_DIR)/scripts/hica_etc/loader_etc.tar.gz -C $(ROOTFS_SRC_DIR)/scripts/hica_etc/
	$(ROOTFS_SRC_DIR)/scripts/hica_etc/loader_etc/MakeCALoaderRootfs.sh $(SDK_DIR)
else
	$(AT)test -d $(ROOTFS_SRC_DIR)/scripts/hica_etc/system_etc || tar xzf $(ROOTFS_SRC_DIR)/scripts/hica_etc/system_etc.tar.gz -C $(ROOTFS_SRC_DIR)/scripts/hica_etc/
	$(ROOTFS_SRC_DIR)/scripts/hica_etc/system_etc/MakeCASystemRootfs.sh $(SDK_DIR) $(CFG_HI_ADVCA_FUNCTION)
endif
endif

#++++++++++++++++++++++++++++++++++++++++++++++++++++
rootbox_strip: rootbox_compose
ifeq ($(CFG_HI_ROOTFS_STRIP), y)
	-$(AT)find $(ROOTBOX_DIR)/bin/ $(ROOTBOX_DIR)/lib/ $(ROOTBOX_DIR)/sbin/ $(ROOTBOX_DIR)/usr/ | xargs $(STRIP) 2> /dev/null
	-$(AT)find $(ROOTBOX_DIR)/bin/ $(ROOTBOX_DIR)/lib/ $(ROOTBOX_DIR)/sbin/ $(ROOTBOX_DIR)/usr/ | xargs $(STRIP) -R .note -R .comment 2> /dev/null
ifdef CFG_HI_ADVCA_FUNCTION
	-$(AT)find $(ROOTBOX_DIR)/home/stb/bin/ $(ROOTBOX_DIR)/home/stb/lib/ $(ROOTBOX_DIR)/home/stb/usr/ | xargs $(STRIP) 2> /dev/null
	-$(AT)find $(ROOTBOX_DIR)/home/stb/bin/ $(ROOTBOX_DIR)/home/stb/lib/ $(ROOTBOX_DIR)/home/stb/usr/ | xargs $(STRIP) -R .note -R .comment 2> /dev/null
endif
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++
rootbox_chmod: rootbox_strip
ifndef CFG_HI_ADVCA_FUNCTION
##¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡ÁFor NO CA¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á
	-$(AT)chmod -R 755 $(ROOTBOX_DIR)/bin
	-$(AT)chmod -R 755 $(ROOTBOX_DIR)/sbin
	-$(AT)chmod -R 755 $(ROOTBOX_DIR)/usr/bin
	-$(AT)chmod -R 755 $(ROOTBOX_DIR)/usr/sbin
	-$(AT)chmod -R 755 $(ROOTBOX_DIR)/lib
	-$(AT)chmod -R 755 $(ROOTBOX_DIR)/usr/lib
else
##¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡ÁFor CA¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á¡Á
ifeq ($(CFG_HI_LOADER_APPLOADER),y)
	# change owner by root
	-$(AT)chown -R root:root $(ROOTBOX_DIR)
	-$(AT)chmod -R 0755 $(ROOTBOX_DIR)

	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/bin
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/boot
	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/dev
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/etc
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home

	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/lib
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/usr/lib/*
	-$(AT)$(SRM) $(ROOTBOX_DIR)/opt -rf
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/root
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/sbin
	-$(AT)$(SRM) $(ROOTBOX_DIR)/share -rf
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/usr
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/var
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/kmod

	-$(AT)chmod -R 0600 $(ROOTBOX_DIR)/mnt
	-$(AT)chmod -R 0600 $(ROOTBOX_DIR)/proc
	-$(AT)chmod -R 0600 $(ROOTBOX_DIR)/sys
	-$(AT)chmod -R 0600 $(ROOTBOX_DIR)/tmp

	-$(AT)chmod 0444 $(ROOTBOX_DIR)/etc/passwd
	-$(AT)chmod 0444 $(ROOTBOX_DIR)/etc/group
	-$(AT)chmod 0400 $(ROOTBOX_DIR)/etc/fstab
	-$(AT)chmod 0444 $(ROOTBOX_DIR)/etc/gshadow
	-$(AT)chmod 0400 $(ROOTBOX_DIR)/etc/inittab
	-$(AT)chmod 0400 $(ROOTBOX_DIR)/etc/shadow

	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/etc/init.d
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/rcS
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/S90modules

	-$(AT)chmod 0500 $(ROOTBOX_DIR)/kmod/load

else
    # change owner by root
	-$(AT)chown -R root:root $(ROOTBOX_DIR)
    # stb user&group id is same as 1000
	-$(AT)chown -R 1000:1000 $(ROOTBOX_DIR)/home/stb

	-$(AT)chmod -R 0755 $(ROOTBOX_DIR)/*

	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/bin
	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/boot
	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/dev
	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/etc
	-$(AT)chmod -R 0755 $(ROOTBOX_DIR)/home
	-$(AT)chmod -R 0700 $(ROOTBOX_DIR)/home/stb

	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/lib
	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/lib/*
	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/usr/lib/*
	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/root
	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/sbin
	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/usr
	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/var
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/kmod

	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/bin/*
	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/usr/bin/*
	-$(AT)chmod -R 0555 $(ROOTBOX_DIR)/sbin/*

	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/var/
	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/mnt
	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/proc
	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/sys

	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home/stb/lib
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home/stb/usr/lib
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home/stb/bin
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home/stb/usr/sbin

	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/home/stb/dev
	-$(AT)chmod -R 0660 $(ROOTBOX_DIR)/home/stb/mnt
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home/stb/usr
	-$(AT)chmod -R 0500 $(ROOTBOX_DIR)/home/stb/var
	-$(AT)chmod -R 0600 $(ROOTBOX_DIR)/home/stb/proc
	-$(AT)chmod -R 0600 $(ROOTBOX_DIR)/home/stb/sys

	-$(AT)chmod 0444 $(ROOTBOX_DIR)/etc/passwd
	-$(AT)chmod 0444 $(ROOTBOX_DIR)/etc/group
	-$(AT)chmod 0400 $(ROOTBOX_DIR)/etc/fstab
	-$(AT)chmod 0444 $(ROOTBOX_DIR)/etc/gshadow
	-$(AT)chmod 0400 $(ROOTBOX_DIR)/etc/inittab
	-$(AT)chmod 0400 $(ROOTBOX_DIR)/etc/shadow

	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/etc/init.d
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/rcS
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/S01udev
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/S89remount-root
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/S90modules
	-$(AT)chmod 0550 $(ROOTBOX_DIR)/etc/init.d/S99Application

	-$(AT)chmod -R 0550 $(ROOTBOX_DIR)/etc/udev

	-$(AT)chmod -R 0400 $(ROOTBOX_DIR)/kmod/
	-$(AT)chmod 0500 $(ROOTBOX_DIR)/kmod/load

    ######################################################################################
    # Note:strip or chown will destory file's capabilities attr,so we need set necessary #
    # capabilities after strip and chown.                                                #
    ######################################################################################
    # add cap for sandbox
	@if [ -e $(ROOTBOX_DIR)/bin/sandbox ]; then \
		$(FILECAP) $(ROOTBOX_DIR)/bin/sandbox sys_chroot; \
	fi

    # add cap for user application. Here take the sample_dvbplay for example
	@if [ -e $(ROOTBOX_DIR)/home/stb/sample_dvbplay ]; then \
		-$(AT)$(FILECAP) $(ROOTBOX_DIR)/home/stb/sample_dvbplay sys_rawio; \
	fi
endif
endif


