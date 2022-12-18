功能：
     演示voip基本功能。
     
依赖：
     使用sample前，需要确保插入voip相关驱动。
     Android版本：
       1)需要打开对应SDK配置文件的CFG_HI_VOIP_SUPPORT宏,重编译整个系统。
       2)需要在系统启动脚本里面添加 insmod /system/lib/modules/voip_hme.ko
                                 insmod /system/lib/modules/hi_aud_adp.ko
用法：

对于打开ALSA功能：
     1)在LD_LIBRARY_PATH定义中增加ALSA及蓝牙库路径/usr/share/bluetooth/lib/
     	 export LD_LIBRARY_PATH="/usr/share/bluetooth/lib/:$LD_LIBRARY_PATH"

     2)执行./sample_voip para 
       	 para : 功能选择，0--Normal,1--Play Announcement
            	 Normal : 用于两单板对接，测试基本通话功能。
            	 Play Announcement : 音乐文件本端播放，适合确认音频设备是否工作正常。

       示例：./sample_voip 1, 测试音乐文件本端播放到耳机的功能。

     3) 按照提示依次输入 Source IP(本端), Dest IP(远端)，格式192.168.1.1。
     
     4) 按照提示依次输入输入设备和输出设备的编号，如 0 0。
        
     5) 运行中按照提示输入相应字符，sample程序分别执行以下动作：
        'q' : 退出voip sample程序。
        'r' : 继续下一个 创建/销毁 VOIP通道 循环测试。
        's' : 选择音频设备。   
        
对于没有打开ALSA功能：

     1)执行./sample_voip para1 para2 
       	 para1 : 音频设备选择, 0--SIO(SLIC/ACI31),1--BLUETOOTH,2--USB MIC+HIAO 3--USB PHONE,4--SOUND CARD
       	 para2 : 功能选择，0--Normal,1--Play Announcement
            	 Normal : 用于两单板对接，测试基本通话功能。
            	 Play Announcement : 音乐文件本端播放，适合确认音频设备是否工作正常。

       示例：./sample_voip 1 1, 测试音乐文件本端播放到蓝牙耳机的功能。

     2) 按照提示依次输入 Source IP(本端), Dest IP(远端)，格式192.168.1.1。
        
     3) 运行中按照提示输入相应字符，sample程序分别执行以下动作：
        'q' : 退出voip sample程序。
        'r' : 继续下一个 创建/销毁 VOIP通道 循环测试。
        's' : 选择音频设备。        

注意：
    1、 该sample使用默认参数演示voip的基本功能，需要修改voip的默认参数请自行在软件中设置。

    2、 可根据自己的需要更改软件中以下参数的默认设置：

	static HI_U8   u8SrcIp[4] = {10,85,180,91};  // Source IP
	static HI_U8   u8DstIp[4] = {10,85,180,95};  // Dest IP
	static HI_U16  u16VoipSrcPort = 8100;        // Voip source port
	static HI_U16  u16VoipDstPort = 8100;        // Voip dest port
	static HI_CHAR cFileName[64]="/mnt/play/love1999.wav";  // The default audio file for play announcement .

    3、 若本端和远端的IP地址和端口号设置为相同，网络适配层将自动环回输入的音频数据，适用于测试除网络收发外的VOIP模块及音频设备功能是否正常。

    4、 该sample默认使用的SIO音频设备为电话机(SLIC), 若要更改为使用 耳机＋MIC方式(ACI31)，需更换对应扣板。
    
    	1) 若是需要支持slic模式，打开sample\common\hi_adp_mpi.h文件顶部的定义
	   #define SLIC_AUDIO_DEVICE_ENABLE
	2) 若是需要支持mic和耳机模式，打开该位置的定义
	   #define TLV320_AUDIO_DEVICE_ENABLE
	
	注意：
          1) Slic模式 和mic/耳机模式 只能二选一，不可以同时支持，更改定义后务必删除sample\voip目录下的执行文件sample_voip再编译。
          2) 若要单独测试SLIC设备是否正常，请执行aiao sample，有音频环回功能，对着话机说话，能在听筒听到自己说话的声音。
    
    