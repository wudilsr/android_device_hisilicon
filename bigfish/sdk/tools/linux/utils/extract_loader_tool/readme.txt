�ű�ʹ�÷�����
   patch_for_miniboot_apploader.sh  HiSTBAndroidV600R001C00SPC061
   �ű�ִ����Ϻ������Ŀ¼��sdk_for_miniboot_apploader

���뷽����
����sdk_for_miniboot_apploaderĿ¼����hi3798mv100оƬΪ��

һ. ����miniboot
1.   ���ƶ�Ӧ�������ļ��� cp configs/hi3798mv100/hi3798mdmo_hi3798mv100_android_vmx_cfg.mak  cfg.mak
2.   make distclean; make hiboot_install -j
3.   ������ɵ�minibootӳ��λ��pub/image/miniboot.bin

��. ����apploader
1.  ���ƶ�Ӧ�������ļ��� cp configs/hi3798mv100/hi3798mdmo_hi3798mv100_apploader_vmx_cfg.mak  cfg.mak
2.  make distclean;make build -j
3.  ������ɵ�apploaderӳ��λ��pub/image/apploader.bin
