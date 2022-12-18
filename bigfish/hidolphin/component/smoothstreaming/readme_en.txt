HiSmoothstreaming compilation instructions£º

Requirements£º
1.Get SSPK license from Microsoft,Mroe info: http://www.microsoft.com/en-us/mediaplatform/sspk.aspx.
2.playready device certificate(Optional, needed by playready function)£¬including 4 files(priv.dat£¬ zgpriv.dat£¬ bgroupcert.dat£¬ devcerttemplate.dat).
3.playready lib.include(libhi_playready.so,libhi_playready_protect.so,libplayreadyplugin.so).
4.Get SmoothStreaming release lib from hisilicon.

Compiling:
1.Make sure PRODUCT_PROPERTY_FOR_DRM_SERVICE:=true/PRODUCT_PROPERTY_FOR_DRM_CLIENT:=true in ./device/hisilicon/Hi37xxxxx/device.mk.

Instruction:
1.playready module is readied.(reference readme in ./device/hisilicon/bigfish/framework/playready).
2.Push SmoothStreaming release lib(get from hisilicon) to /system/lib.
3.reboot.
