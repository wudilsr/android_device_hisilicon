HiSmoothstreaming组件编译说明：

组件的依赖：
1.从微软获取SSPK授权，具体参考http://www.microsoft.com/en-us/mediaplatform/sspk.aspx；
3. playready设备证书（可选的，运行时playready功能需要），包括4个文件(priv.dat， zgpriv.dat， bgroupcert.dat， devcerttemplate.dat)；
4.playready库。包括（libhi_playready.so,libhi_playready_protect.so,libplayreadyplugin.so），用法参考playready 《readme.txt》；
5.从海思获取SmoothStreaming release lib；

编译:
 确保./device/hisilicon/Hi37xxxxx/device.mk中PRODUCT_PROPERTY_FOR_DRM_SERVICE:=true/PRODUCT_PROPERTY_FOR_DRM_CLIENT:=true；
 
使用说明：
1.将PlayReady模块准备好（参考./device/hisilicon/bigfish/framework/playready中的readme.txt）；
2.将从海思获取的SmoothStreaming release lib放入 /system/lib目录；
3.重启；

