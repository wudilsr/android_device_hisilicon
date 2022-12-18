
说明
1.本工具是CASignTool.exe签名工具的linux版本，当前功能在完善。
2.本工具使用cfg文本导入配置信息(文件名可更改)
3.目前支持五种使用方式
  1>secureSignTool.exe 0 Signboot_config.cfg 由Signboot_config.cfg读入
    chiptype,key file,cfg.bin,msid,version id,inputdir,outputdir 等信息,签
    名镜像生成在outputdir
  2>secureSignTool.exe 1 merge_config.cfg  由merge_config.cfg读入
    chiptype, 已签名 bin 文件,inputdir,outputdir 等信息,合成final boot生成在outputdir
  3>secureSignTool.exe 2 common_config.cfg  common_config.cfg读入
    rsa签名私钥，待签名文件，签名后的文件名，是否分段签名,inputdir,outputdir 等信息,签名镜像在outputdir目录
    说明： SignCommon_config.cfg中参数SectionSize，如果为0，则不分段签名；如果分段签名，则设置此值为分段大小，
           例如按1MB大小分段签名，请设置SectionSize=0x100000.
  4>secureSignTool.exe 3 special_config.cfg  非boot镜像special方式签名。
    由special_config.cfg读入rsa签名私钥，待签名文件，签名后的文件名，CustomerData数据,InputFileDir,OutputFileDir 等信息,
    签名后镜像放在OutputFileDir目录
    说明： special_config.cfg中虽有参数SectionSize，HeaderSize、RSALength、HashMode等，但暂时只支持默认的.  
           其中ImageNumber参数为需要签名的镜像数，增加一个签名镜像，增加ImageXXX，PartitionSizeXXX和SignImageXXX。XXX为索引数，依次增加。         
  5>secureSignTool.exe 4 crypto_config.cfg  非boot镜像加密和解密。
    crypto_config.cfg读入rsa签名私钥文件、AES Key和IV向量，待签名文件，签名后的文件名，InputFileDir,OutputFileDir 等信息,
    加密后镜像放在OutputFileDir参数设置的目录。
    说明： 需要根据需要配置crypto_config.cfg中的参数，比如AES加密，一定需要配置加密算法Algorithm，加密模式Mode，加密私钥Key，和IV向量.  
           支持批量加密或者加密。ImageNumber参数为需要加解密的镜像数，需要与实际的镜像数一致，否则会报错。
           增加一个签名镜像，增加Input1XXX和OutputXXX参数，分别代表输入和输出，XXX为索引数，依次增加。         
   
           
4.输入文件，输出文件名可在cfg文件里面配置
5.boot镜像签名时，支持的芯片包括Hi3716MV300,Hi3716CV200,Hi3719MV100,Hi3719CV100,可在cfg文件中配置，非boot镜像其他与芯片无关。
6.cfg文件自动去除以#开头得注释行
7.其他问题请另外咨询
