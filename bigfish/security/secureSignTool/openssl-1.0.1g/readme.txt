openssl密码算法相关的开源软件.

openssl-1.0.1g_hisi.tar.gz为在openssl 1.0.1g原始代码基础上，进行了修改之后，适配海思产品的openssl代码。


Openssl使用方法如下：

1. 编译Linux服务器上可以使用的openssl库，需要配置为：
./Configure linux-elf-arm -DB_ENDIAN 
./make

清除结果：
./make clean
而且，需要注意Makefile中CROSS_COMPILE需要配置为空。

2. 编译Linux SDK中可以使用的openssl库，需要配置为：
#./Configure linux-elf-arm -DB_ENDIAN
# make

清除结果：
# make clean
需要注意的是，在配置之前CROSS_COMPILE需要配置为arm-hisiv200-linux-
