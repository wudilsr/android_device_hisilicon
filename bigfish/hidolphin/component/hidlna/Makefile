TARGET := hidlna
PUB_INC_DIR := $(PUB_DIR)/$(TARGET)/include
PUB_LIB_DIR := $(PUB_DIR)/$(TARGET)/lib/${CFG_HI_TOOLCHAINS_NAME}-$(VERSION)
PUB_SRC_DIR := $(PUB_DIR)/$(TARGET)/src
PUB_SAMPLE_DIR := $(PUB_DIR)/$(TARGET)/sample
#######################################################
#.PHONY:clean all upnp vppdlna conf_upnp upnp_clean  vppdlna_clean conf_upnp_clean
.PHONY:clean all upnp hidlna upnp_clean hidlna_clean publish_target test test_clean
#all:  upnp vppdlna
all:  upnp hidlna dtcp hidtcp sample sample_with_player

upnp:
	chmod a+x $(HIDOLPHIN_DIR)/external/libupnp/conf_make.sh
	make -C $(HIDOLPHIN_DIR)/external/libupnp/ -f conf_make.sh
	make -C $(HIDOLPHIN_DIR)/external/libupnp
#	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/upnp/inc/* $(OUT_INC_DIR)
#	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/ixml/inc/* $(OUT_INC_DIR)
#	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/threadutil/inc/* $(OUT_INC_DIR)
	cp -rfl $(HIDOLPHIN_DIR)/external/libupnp/upnp/.libs/*.so* $(OUT_LIB_DIR)
	cp -rfl $(HIDOLPHIN_DIR)/external/libupnp/ixml/.libs/*.so* $(OUT_LIB_DIR)
	cp -rfl $(HIDOLPHIN_DIR)/external/libupnp/threadutil/.libs/*.so* $(OUT_LIB_DIR)
	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/upnp/.libs/*.a $(OUT_LIB_DIR)
	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/ixml/.libs/*.a $(OUT_LIB_DIR)
	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/threadutil/.libs/*.a $(OUT_LIB_DIR)
dtcp:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source/dtcp

hidtcp:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source/hidtcp

hidlna:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source

sample:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/linux/SDK/sample/sample_dlna

sample_with_player:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/linux/SDK/sample/sample_dlna_with_player

test:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/test

test_clean:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/test clean

#clean: upnp_clean vppdlna_clean
clean: upnp_clean hidlna_clean dtcp_clean hidtcp_clean sample_clean

upnp_clean:
	make -C $(HIDOLPHIN_DIR)/external/libupnp clean

dtcp_clean:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source/dtcp clean

hidtcp_clean:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source/hidtcp clean

hidlna_clean:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source clean

sample_clean:
	make -C $(HIDOLPHIN_DIR)/component/hidlna/linux/SDK/sample/sample_dlna clean

publish_target_prepare:
	mkdir -p $(PUB_INC_DIR)
	mkdir -p $(PUB_LIB_DIR)

publish_target:publish_target_prepare
	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/threadutil/.libs/{*.a,*so*} $(PUB_LIB_DIR)
	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/upnp/.libs/{*.a,*so*} $(PUB_LIB_DIR)
	cp -rf $(HIDOLPHIN_DIR)/external/libupnp/ixml/.libs/{*.a,*so*} $(PUB_LIB_DIR)
#sample
	cp -rf $(HIDOLPHIN_DIR)/component/hidlna/linux/SDK/sample/sample_dlna/{Makefile,sample} $(PUB_DIR)/$(TARGET)/
	sed -i '/dtcp/d'            $(PUB_DIR)/$(TARGET)/sample/Makefile ###don't publish dtcp
	sed -i '/sample_with_dtcp/d' $(PUB_DIR)/$(TARGET)/Makefile ###don't publish dtcp
	make -C $(HIDOLPHIN_DIR)/component/hidlna/source publish
	find $(PUB_DIR)/$(TARGET) -name sample_dm? -o -name sample_dms_dmr_dmp |xargs rm
#	cp -af $(OUT_LIB_DIR)/*dtcp* $(PUB_LIB_DIR)
#sample_with_player
	rsync -a $(HIDOLPHIN_DIR)/component/hidlna/linux/SDK/sample/sample_dlna_with_player $(FAE_DIR)/$(TARGET)/
	sed -i '/dtcp/d'            $(FAE_DIR)/$(TARGET)/sample_dlna_with_player/sample/Makefile ###don't publish dtcp
	find $(FAE_DIR)/$(TARGET) -name sample_dm? -o -name sample_dms_dmr_dmp |xargs rm
	cd $(FAE_DIR)/$(TARGET)&& tar czf sample_dlna_with_player.tgz sample_dlna_with_player && rm -rf sample_dlna_with_player
