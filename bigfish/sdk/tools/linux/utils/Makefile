#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(shell pwd)/../../..
include $(SDK_DIR)/base.mak
endif

#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
O                      ?= $(CURDIR)
SERVER_UNTILS_INSTALL   = $(O)
SERVER_UNTILS_DIR       = $(CURDIR)
SERVER_UNTILS_NONE	= 

export CC       := gcc
SCP              = $(SERVER_UNTILS_INSTALL)/cp
SRM              = $(SERVER_UNTILS_INSTALL)/rm
MKCRAMFS         = $(SERVER_UNTILS_INSTALL)/mkfs.cramfs
MKEXT2FS         = $(SERVER_UNTILS_INSTALL)/genext2fs
MKEXT4FS         = $(SERVER_UNTILS_INSTALL)/make_ext4fs
SIMG2IMG         = $(SERVER_UNTILS_INSTALL)/simg2img
E2FSCK           = $(SERVER_UNTILS_INSTALL)/e2fsck
TUNE2FS          = $(SERVER_UNTILS_INSTALL)/tune2fs
MKSQUASHFS       = $(SERVER_UNTILS_INSTALL)/mksquashfs
MKJFFS2          = $(SERVER_UNTILS_INSTALL)/mkfs.jffs2
ifeq ($(CFG_HI_CHIP_TYPE),hi3716cv200es)
MKYAFFS2IMAGENAME= mkyaffs2image504
else
MKYAFFS2IMAGENAME= mkyaffs2image610
endif
MKYAFFS          = $(SERVER_UNTILS_INSTALL)/$(MKYAFFS2IMAGENAME)
FILECAP          = $(SERVER_UNTILS_INSTALL)/filecap
MKBOOTARGS       = $(SERVER_UNTILS_INSTALL)/mkbootargs
MKUBIFS          = $(SERVER_UNTILS_INSTALL)/mkfs.ubifs
UBINIZE          = $(SERVER_UNTILS_INSTALL)/ubinize
MKUBIIMG         = $(SERVER_UNTILS_INSTALL)/mkubiimg.sh
LZMA             = $(SERVER_UNTILS_INSTALL)/lzma
MKIMAGE          = $(SERVER_UNTILS_INSTALL)/mkimage

ifeq ($(CFG_PRODUCT_TYPE), linux)
TOOLS_LIST := $(MKUBIIMG) $(MKBOOTARGS) $(MKIMAGE) $(FILECAP) $(MKUBIFS) $(UBINIZE) $(LZMA) $(SCP) \
    $(SRM) $(MKCRAMFS) $(MKEXT2FS) $(MKEXT4FS) $(SIMG2IMG) $(E2FSCK) $(TUNE2FS) $(MKSQUASHFS) $(MKJFFS2) $(MKYAFFS) 
else ifeq ($(CFG_PRODUCT_TYPE), android)
TOOLS_LIST := $(MKUBIIMG) $(MKUBIFS) $(UBINIZE) $(MKSQUASHFS)
endif

#-------------------------------------------
PHONY := all clean install uninstall

ifndef HIFLASH_NONE
all: tools_chown
	@echo "nothing to do !"

clean: tools_clean
	@rm -rfv $(TOOLS_LIST)

distclean: clean

tools_clean:
	-(cd $(SERVER_UNTILS_DIR)/mtd-utils;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/mtd-utils distclean;cd -)
	-(cd $(SERVER_UNTILS_DIR)/mkimage-tool;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/mkimage-tool distclean;cd -)
	-(cd $(SERVER_UNTILS_DIR)/libcap-ng;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/libcap-ng distclean;cd -)
	-(cd $(SERVER_UNTILS_DIR)/squashfs4.2; make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/squashfs4.2 distclean;cd -) 
ifeq ($(CFG_PRODUCT_TYPE), linux)
	make -j1 -C $(SERVER_UNTILS_DIR)/mkyaffs2image PREFIX=$(SERVER_UNTILS_INSTALL)/mkyaffs2image distclean
	make -j1 -C $(SERVER_UNTILS_DIR)/mkbootargs-tool PREFIX=$(SERVER_UNTILS_INSTALL)/mkbootargs-tool distclean
	-(cd $(SERVER_UNTILS_DIR)/genext2fs-1.4.1;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/genext2fs-1.4.1 distclean;cd -)
	-(cd $(SERVER_UNTILS_DIR)/e2fsprogs_x86;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/e2fsprogs_x86 distclean;cd -)
	-(cd $(SERVER_UNTILS_DIR)/ext4_utils;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/ext4_utils distclean;cd -)
	-(cd $(SERVER_UNTILS_DIR)/util-linux;make -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/util-linux distclean;cd -)
endif
	@echo "make $@ over !"

tools_all:
	@test -d $(SERVER_UNTILS_INSTALL) || mkdir -p $(SERVER_UNTILS_INSTALL)	
	test -f $(MKUBIFS) -a -f $(UBINIZE) -a -f $(MKUBIIMG) || make  -j1 mkmtdutils_tool
	test -f $(MKIMAGE) || make  -j1 mkimage_tool
	test -f $(FILECAP) || make  -j1 mkfilecap_tool
	test -f $(MKSQUASHFS) -a -f $(LZMA) || make  -j1 mksquashfs_tool
ifeq ($(CFG_PRODUCT_TYPE), linux)
	test -f $(MKYAFFS) || make  -j1 mkyaffs_tool
	test -f $(MKEXT2FS) || make  -j1 mkgenext2fs_tool
	test -f $(MKEXT4FS) || make  -j1 mkgenext4fs_tool
	test -f $(TUNE2FS) || make  -j1 mktune2fs_tool
	test -f $(E2FSCK) || make  -j1 mke2fsck_tool
	test -f $(MKBOOTARGS) || make  -j1 mkbootargs_tool
	test -f $(MKJFFS2) || make  -j1 mkjffs2_tool
	test -f $(MKCRAMFS) || make  -j1 mkcramfs_tool
endif

mkyaffs_tool:
	make  -j1 -C $(SERVER_UNTILS_DIR)/mkyaffs2image PREFIX=$(SERVER_UNTILS_INSTALL)/mkyaffs2image
	@cp -rvf $(SERVER_UNTILS_INSTALL)/mkyaffs2image/tmp/mkyaffs2image.300_301_504_610/$(MKYAFFS2IMAGENAME) $(SERVER_UNTILS_INSTALL)

mksquashfs_tool:
	cd $(SERVER_UNTILS_DIR)/squashfs4.2;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/squashfs4.2;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/squashfs4.2/mksquashfs  $(SERVER_UNTILS_INSTALL)
	-cp -rvf $(SERVER_UNTILS_INSTALL)/squashfs4.2/lzma $(SERVER_UNTILS_INSTALL)

mkgenext2fs_tool:
	cd $(SERVER_UNTILS_DIR)/genext2fs-1.4.1;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/genext2fs-1.4.1;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/genext2fs-1.4.1/bin/genext2fs  $(SERVER_UNTILS_INSTALL)

mkgenext4fs_tool:
	cd $(SERVER_UNTILS_DIR)/ext4_utils;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/ext4_utils;cd -
	cp -rvf $(SERVER_UNTILS_INSTALL)/ext4_utils/bin/make_ext4fs  $(SERVER_UNTILS_INSTALL)
	cp -rvf $(SERVER_UNTILS_INSTALL)/ext4_utils/bin/simg2img  $(SERVER_UNTILS_INSTALL)

mke2fsck_tool:
	cd $(SERVER_UNTILS_DIR)/e2fsprogs_x86;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/e2fsprogs_x86;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/e2fsprogs_x86/e2fsprogs-1.41.11/e2fsck/e2fsck.static  $(E2FSCK)

mktune2fs_tool:
	cd $(SERVER_UNTILS_DIR)/e2fsprogs_x86;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/e2fsprogs_x86;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/e2fsprogs_x86/e2fsprogs-1.41.11/misc/tune2fs.static  $(TUNE2FS)

mkbootargs_tool:
	make -C $(SERVER_UNTILS_DIR)/mkbootargs-tool  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/mkbootargs-tool
	-cp -rvf $(SERVER_UNTILS_INSTALL)/mkbootargs-tool/mkbootargs $(SERVER_UNTILS_INSTALL)

mkmtdutils_tool:
	cd  $(SERVER_UNTILS_DIR)/mtd-utils;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/mtd-utils;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/mtd-utils/mkfs.ubifs $(SERVER_UNTILS_INSTALL)
	-cp -rvf $(SERVER_UNTILS_INSTALL)/mtd-utils/ubinize $(SERVER_UNTILS_INSTALL)
	-cp -rvf $(SERVER_UNTILS_INSTALL)/mtd-utils/mkubiimg.sh $(SERVER_UNTILS_INSTALL)

mkjffs2_tool:
	cd  $(SERVER_UNTILS_DIR)/mtd-utils;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/mtd-utils;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/mtd-utils/mkfs.jffs2 $(SERVER_UNTILS_INSTALL)

mkfilecap_tool:
	cd $(SERVER_UNTILS_DIR)/libcap-ng;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/libcap-ng;cd -
	@-cp -rvf $(SERVER_UNTILS_INSTALL)/libcap-ng/libcap-ng-0.6.5/INSTALL_DIR/usr/bin/filecap $(SERVER_UNTILS_INSTALL)

mkcramfs_tool:
	cd $(SERVER_UNTILS_DIR)/util-linux;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/util-linux;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/util-linux/mkfs.cramfs $(SERVER_UNTILS_INSTALL)

mkimage_tool:
	cd $(SERVER_UNTILS_DIR)/mkimage-tool;make  -j1 PREFIX=$(SERVER_UNTILS_INSTALL)/mkimage-tool;cd -
	-cp -rvf $(SERVER_UNTILS_INSTALL)/mkimage-tool/mkimage $(SERVER_UNTILS_INSTALL)

tools_chown: tools_all
#	define a special super cp and rm
	@-cp -fv `which cp` $(SCP) &&  chmod +s $(SCP) 
	@-cp -fv `which rm` $(SRM) &&  chmod +s $(SRM)
ifdef CFG_HI_ADVCA_FUNCTION
	for TOOL in $(TOOLS_LIST);do \
	chown 0:0 $$TOOL; \
	chmod +x $$TOOL; \
	chmod +s $$TOOL; \
	done
else
	for TOOL in $(TOOLS_LIST);do \
	chmod +x $$TOOL; \
	chmod +s $$TOOL; \
	if [ $(USER) = "root" ];then \
		chown $(USER):$(USER) $$TOOL; \
	fi; \
	done
endif

	
install: tools_chown
	@echo "make $@ over !"

uninstall:
	-rm -rf $(TOOLS_LIST)
	@echo "make $@ over !"
	
else
all:
	@echo "make $@ over !"
clean:
	@echo "make $@ over !"
install: 
	@echo "make $@ over !"
uninstall:
	@echo "make $@ over !"

endif
	
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
