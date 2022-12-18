目的：1.提供手动烧写IPTV 芯片安全启动数据到OTP的工具write_otp实现。
      2.提供IPTV工厂生产芯片安全启动数据烧录api及sample。
命令：1. write_otp key.txt
      2. write_scs
注意：1. 请确保运行sample时已经加载相关驱动(hi_cipher.ko、hi_otp.ko、hi_advca.ko）。
      2. write_otp后会将otp区锁定，无法再次写入，所以在此之前执行 write_flash key.txt，完成IN数据烧写。
      3. 使用IPTV工厂生产芯片安全启动数据烧录api接口HI_UNF_ADVCA_SetSCSData后会将otp区锁定，无法再次写入，
         所以在此之前调用IPTV业务安全数据api接口HI_UNF_ADVCA_SetCTITData，完成IN数据烧写。
      4. 烧写IPTV业务安全数据的手动工具write_flash和api、库libhi_ctit.a均不开源。

      如果对sample使用有疑问，请联系海思FAE。




