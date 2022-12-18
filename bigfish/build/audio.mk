include $(CLEAR_VARS)

AUDIO_DIR=$(ANDROID_BUILD_TOP)/device/hisilicon/bigfish/frameworks/hiaudio/

UPDATE_DTS := $(PRODUCT_OUT)/update-dolby_dts.zip
$(UPDATE_DTS) : $(INSTALLED_SYSTEMIMAGE)
	$(hide) mkdir -p $(PRODUCT_OUT)/update-dolby
	$(hide) cp -a $(ANDROID_BUILD_TOP)/out/host/linux-x86/framework/signapk.jar $(PRODUCT_OUT)/update-dolby
	$(hide) cp -a $(ANDROID_BUILD_TOP)/build/target/product/security/testkey.x509.pem $(PRODUCT_OUT)/update-dolby
	$(hide) cp -a $(ANDROID_BUILD_TOP)/build/target/product/security/testkey.pk8 $(PRODUCT_OUT)/update-dolby
	$(hide) mkdir -p $(PRODUCT_OUT)/update-dolby/file/system/lib
	$(hide) mkdir -p $(PRODUCT_OUT)/update-dolby/file/META-INF/com/google/android
	$(hide) cp -a $(PRODUCT_OUT)/system/bin/updater $(PRODUCT_OUT)/update-dolby/file/META-INF/com/google/android/update-binary
	$(hide) cp -a $(PRODUCT_OUT)/system/lib/libHA.AUDIO.DOLBYPLUS.decode.so $(PRODUCT_OUT)/update-dolby/file/system/lib
	$(hide) cp -a $(PRODUCT_OUT)/system/lib/libHA.AUDIO.DTSHD.decode.so $(PRODUCT_OUT)/update-dolby/file/system/lib
	$(hide) cp -a $(PRODUCT_OUT)/system/lib/libHA.AUDIO.DOLBYTRUEHD.decode.so $(PRODUCT_OUT)/update-dolby/file/system/lib
	$(hide) cp -a $(call include-path-for, recovery)/etc/META-INF/com/google/android/updater-script-for-dolby $(PRODUCT_OUT)/update-dolby/file/META-INF/com/google/android/updater-script
	$(hide) cd $(PRODUCT_OUT)/update-dolby/file && zip -qry sor_update.zip  META-INF/ system
	$(hide) cp -a $(PRODUCT_OUT)/update-dolby/file/sor_update.zip $(PRODUCT_OUT)/update-dolby/
	$(hide) cd $(PRODUCT_OUT)/update-dolby && java -jar signapk.jar  -w  testkey.x509.pem  testkey.pk8 sor_update.zip update-dolby_dts.zip
	$(hide) cp -a $(PRODUCT_OUT)/update-dolby/update-dolby_dts.zip  $(PRODUCT_OUT)/
	$(hide) rm -r $(PRODUCT_OUT)/update-dolby
	$(hide) echo "################# update dolby ##################"

include $(CLEAR_VARS)

UPDATE_AUDIO := $(PRODUCT_OUT)/update-audiolib.zip
$(UPDATE_AUDIO) : $(INSTALLED_SYSTEMIMAGE)
	$(hide) mkdir -p $(PRODUCT_OUT)/update-audio
	$(hide) cp -a $(ANDROID_BUILD_TOP)/out/host/linux-x86/framework/signapk.jar $(PRODUCT_OUT)/update-audio
	$(hide) cp -a $(ANDROID_BUILD_TOP)/build/target/product/security/testkey.x509.pem $(PRODUCT_OUT)/update-audio
	$(hide) cp -a $(ANDROID_BUILD_TOP)/build/target/product/security/testkey.pk8 $(PRODUCT_OUT)/update-audio
	$(hide) mkdir -p $(PRODUCT_OUT)/update-audio/file/system/lib
	$(hide) mkdir -p $(PRODUCT_OUT)/update-audio/file/META-INF/com/google/android
	$(hide) cp -a $(PRODUCT_OUT)/system/bin/updater $(PRODUCT_OUT)/update-audio/file/META-INF/com/google/android/update-binary
	$(hide) cp -a $(PRODUCT_OUT)/system/lib/libHA* $(PRODUCT_OUT)/update-audio/file/system/lib
	$(hide) rm -r $(PRODUCT_OUT)/update-audio/file/system/lib/libHA.AUDIO.DTSM6.decode.so
	$(hide) rm -r $(PRODUCT_OUT)/update-audio/file/system/lib/libHA.AUDIO.DOLBYPLUS.decode.so
	$(hide) rm -r $(PRODUCT_OUT)/update-audio/file/system/lib/libHA.AUDIO.DTSHD.decode.so
	$(hide) rm -r $(PRODUCT_OUT)/update-audio/file/system/lib/libHA.AUDIO.DOLBYTRUEHD.decode.so
	$(hide) cp -a $(call include-path-for, recovery)/etc/META-INF/com/google/android/updater-script-for-audio $(PRODUCT_OUT)/update-audio/file/META-INF/com/google/android/updater-script
	$(hide) cd $(PRODUCT_OUT)/update-audio/file && zip -qry sor_update.zip  META-INF/ system
	$(hide) cp -a $(PRODUCT_OUT)/update-audio/file/sor_update.zip $(PRODUCT_OUT)/update-audio/
	$(hide) cd $(PRODUCT_OUT)/update-audio && java -jar signapk.jar  -w  testkey.x509.pem  testkey.pk8 sor_update.zip update-audiolib.zip
	$(hide) cp -a $(PRODUCT_OUT)/update-audio/update-audiolib.zip  $(PRODUCT_OUT)/
	$(hide) rm -r $(PRODUCT_OUT)/update-audio
	$(hide) echo "################# update audio ##################"

include $(CLEAR_VARS)

UPDATE_DTSM6 := $(PRODUCT_OUT)/update-dtsm6.zip
$(UPDATE_DTSM6) : $(INSTALLED_SYSTEMIMAGE)
	$(hide) mkdir -p $(PRODUCT_OUT)/update-dtsm6
	$(hide) cp -a $(ANDROID_BUILD_TOP)/out/host/linux-x86/framework/signapk.jar $(PRODUCT_OUT)/update-dtsm6
	$(hide) cp -a $(ANDROID_BUILD_TOP)/build/target/product/security/testkey.x509.pem $(PRODUCT_OUT)/update-dtsm6
	$(hide) cp -a $(ANDROID_BUILD_TOP)/build/target/product/security/testkey.pk8 $(PRODUCT_OUT)/update-dtsm6
	$(hide) mkdir -p $(PRODUCT_OUT)/update-dtsm6/file/system/lib
	$(hide) mkdir -p $(PRODUCT_OUT)/update-dtsm6/file/META-INF/com/google/android
	$(hide) cp -a $(PRODUCT_OUT)/system/bin/updater $(PRODUCT_OUT)/update-dtsm6/file/META-INF/com/google/android/update-binary
	$(hide) cp -a $(PRODUCT_OUT)/system/lib/libHA.AUDIO.DTSM6.decode.so $(PRODUCT_OUT)/update-dtsm6/file/system/lib
	$(hide) cp -a $(call include-path-for, recovery)/etc/META-INF/com/google/android/updater-script-for-audio $(PRODUCT_OUT)/update-dtsm6/file/META-INF/com/google/android/updater-script
	$(hide) cd $(PRODUCT_OUT)/update-dtsm6/file && zip -qry sor_update.zip  META-INF/ system
	$(hide) cp -a $(PRODUCT_OUT)/update-dtsm6/file/sor_update.zip $(PRODUCT_OUT)/update-dtsm6/
	$(hide) cd $(PRODUCT_OUT)/update-dtsm6 && java -jar signapk.jar  -w  testkey.x509.pem  testkey.pk8 sor_update.zip update-dtsm6.zip
	$(hide) cp -a $(PRODUCT_OUT)/update-dtsm6/update-dtsm6.zip  $(PRODUCT_OUT)/
	$(hide) rm -r $(PRODUCT_OUT)/update-dtsm6
	$(hide) echo "################# update dtsm6 ##################"	
	
.PHONY: update-audio
update-audio: $(UPDATE_DTS) $(UPDATE_AUDIO) $(UPDATE_DTSM6)
