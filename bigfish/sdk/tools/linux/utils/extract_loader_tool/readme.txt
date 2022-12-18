脚本使用方法：
   patch_for_miniboot_apploader.sh  HiSTBAndroidV600R001C00SPC061
   脚本执行完毕后会生成目录：sdk_for_miniboot_apploader

编译方法：
进入sdk_for_miniboot_apploader目录，以hi3798mv100芯片为例

一. 编译miniboot
1.   复制对应的配置文件： cp configs/hi3798mv100/hi3798mdmo_hi3798mv100_android_vmx_cfg.mak  cfg.mak
2.   make distclean; make hiboot_install -j
3.   编译完成的miniboot映像位于pub/image/miniboot.bin

二. 编译apploader
1.  复制对应的配置文件： cp configs/hi3798mv100/hi3798mdmo_hi3798mv100_apploader_vmx_cfg.mak  cfg.mak
2.  make distclean;make build -j
3.  编译完成的apploader映像位于pub/image/apploader.bin
