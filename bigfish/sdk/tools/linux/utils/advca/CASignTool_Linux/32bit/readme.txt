
˵��
1.��������CASignTool.exeǩ�����ߵ�linux�汾
2.������ʹ��cfg�ı�����������Ϣ(�ļ����ɸ���)
3.Ŀǰ���߲�֧�ָ���·���д��ڿո�
4.ʹ�÷�ʽ���£�

  1>./CASignTool 0 ../cfg/Signboot_config.cfg
  ��ǩ��Key�����������Key�ļ�·��������д��Root_private_key_file��External_public_key_file��BootFile�Ķ���֮һ�����߻��ǩ��Key����BootFile�����������fastboot.bin����keyarea.bin
  ������ROOT_RSA_Private_Key������external priv key��external pub key��������������ľ���ǩ�����Լ�key���ľ���
  
  ǩ��������
  ��Signboot_config.cfg����chiptype,key file,cfg.bin,msid,version,inputdir,outputdir ����Ϣ��ǩ������������OutputFileDir�������õ�Ŀ¼��
  ����-k -b -r -o��ѡ�����ö�Ӧ��key�ļ���boot���Դ�ļ�������ļ���·��

  2>./CASignTool 1 ../cfg/merge_config.cfg
  �ϲ������ļ�Ϊ���յ�boot
  ��merge_config.cfg����chiptype, ��ǩ�� bin �ļ�,inputdir,outputdir ����Ϣ���ϳ�final boot������OutputFileDir�������õ�Ŀ¼��
  ���� -r -o��ѡ�����ö�Ӧ��Դ�ļ�������ļ���·��

  3>./CASignTool 2 ../cfg/common_config.cfg
  ��boot����common��ʽǩ����
  ��common_config.cfg����rsaǩ��˽Կ����ǩ���ļ���ǩ������ļ������Ƿ�ֶ�ǩ��,inputdir,outputdir ����Ϣ,ǩ��������OutputFileDir�������õ�Ŀ¼��
    ˵���� SignCommon_config.cfg�в���SectionSize�����Ϊ0���򲻷ֶ�ǩ��������ֶ�ǩ���������ô�ֵΪ�ֶδ�С��
           ���簴1MB��С�ֶ�ǩ����������SectionSize=1.
  ����-k -r -o��ѡ�����ö�Ӧ��key�ļ���Դ�ļ�������ļ���·��

  4>./CASignTool 3 ../cfg/special_config.cfg  
  ��boot����special��ʽǩ����
  ��special_config.cfg����rsaǩ��˽Կ����ǩ���ļ���ǩ������ļ�����CustomerData����,InputFileDir,OutputFileDir ����Ϣ��ǩ���������OutputFileDirĿ¼
    ˵���� special_config.cfg�����в���SectionSize��HeaderSize��RSALength��HashMode�ȣ�����ʱֻ֧��Ĭ�ϵ�.  
           ����ImageNumber����Ϊ��Ҫǩ���ľ�����������һ��ǩ����������ImageXXX��PartitionSizeXXX��SignImageXXX��XXXΪ���������������ӡ�   
  ����-k -r -o��ѡ�����ö�Ӧ��key�ļ���Դ�ļ�������ļ���·��
      
  5>./CASignTool 4 ../cfg/crypto_config.cfg
  ��boot������ܺͽ��ܡ�
  ��crypto_config.cfg����rsaǩ��˽Կ�ļ���AES Key��IV��������ǩ���ļ���ǩ������ļ�����InputFileDir,OutputFileDir ����Ϣ�����ܺ������OutputFileDir�������õ�Ŀ¼��
    ˵���� ��Ҫ������Ҫ����crypto_config.cfg�еĲ���������AES���ܣ�һ����Ҫ���ü����㷨Algorithm������ģʽMode������˽ԿKey����IV����.  
           ֧���������ܻ��߽��ܡ�ImageNumber����Ϊ��Ҫ�ӽ��ܵľ���������Ҫ��ʵ�ʵľ�����һ�£�����ᱨ��
           ����һ��ǩ����������InputXXX��OutputXXX�������ֱ��������������XXXΪ���������������ӡ�

  6>./CASignTool 5 ../cfg/VMXSignCrypto_config.cfg -K keyFilePath -R srcFilePath -O destFilePath

  VMXǩ�����ܾ���
  ��VMXSignCrypto_config.cfg����ǩ���㷨��ģʽ��AES Key��IV��������Ϣ����������ָ��key�ļ���Դ�ļ���Ŀ���ļ���·������ǩ�����ܡ�
    ˵���� ��Ҫ������Ҫ����VMXSignCrypto_config.cfg�еĲ���������AES���ܣ�һ����Ҫ���ü����㷨Algorithm������ģʽMode������˽ԿKey����IV����.  

  7>./CASignTool 6 ../cfg/special_crypto_config.cfg
  ��boot����special��ʽǩ������
  ��special_crypto_config.cfg����rsaǩ��˽Կ�ļ���ǩ���㷨��AES Key��IV��������ǩ���ļ���ǩ������ļ�����InputFileDir,OutputFileDir����Ϣ�����ܺ������OutputFileDir�������õ�Ŀ¼��
    ˵���� ��Ҫ������Ҫ����special_crypto_config.cfg�еĲ���������AES���ܣ�һ����Ҫ���ü����㷨Algorithm������ģʽMode������˽ԿKey����IV����.  
           ֧����������ImageNumber����Ϊ��Ҫ�ӽ��ܵľ���������Ҫ��ʵ�ʵľ�����һ�£�����ᱨ��
           ����һ��ǩ����������InputXXX��OutputXXX�������ֱ��������������XXXΪ���������������ӡ� 
  ����-k -r -o��ѡ�����ö�Ӧ��key�ļ���Դ�ļ�������ļ���·��

  8>./CASignTool 7 ../cfg/verifyboot.cfg
  ��֤Finalboot��
  ��verifyboot.cfg����Finalboot����root pub key��msid��version��msidmask��versionmask���Ƿ�Ϊ���ܾ��񡢼�����Կ����Ϣ����֤FinalBoot�Ƿ�Ϊ��ȷ���ɡ�

  9>./CASignTool 8 eValue keyDestPath
  ����RSA��Կ��
  ��������eValue���Լ���Կ����Ŀ¼keyDestPath����������Կ���ɵ���Կ����Ŀ¼

  10>./CASignTool 9 RSAPubKeyPath RSAPriKeyPath AESKeyPath DdrInitPath UBootPath OutputFilePath
  ����ƥ��Hi3519V101��Boot��
  ����rsa��Կ��rsa˽Կ��aes��Կ��ddrinit�������ļ�·����uboot�������ļ�·���Լ�����������ļ�·���������������յ�boot�ļ���
aes��Կ��֧��txt��ʽ����Ҫ�ǺϷ���ʮ����������16�ֽڣ�32�ַ�������������0x��ͷ������Կ����16�ֽڻ��ȡǰ16�ֽڽ��д���
   
   
           
4.�����ļ�������ļ�������cfg�ļ���������
5.boot����ǩ��ʱ��֧�ֵ�оƬ����Hi3798CV200,Hi3716MV300,Hi3716CV200,Hi3719MV100,Hi3719CV100,Hi3796CV100,Hi3798CV100,Hi3798MV100,Hi3716MV420,Hi3716MV410,Hi3110EV500,Hi3796MV100,����cfg�ļ������ã���boot����������оƬ�޹ء�
6.cfg�ļ��Զ�ȥ����#��ͷ��ע����
7.����������������ѯ
