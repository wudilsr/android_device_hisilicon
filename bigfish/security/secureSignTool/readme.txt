
˵��
1.��������CASignTool.exeǩ�����ߵ�linux�汾����ǰ���������ơ�
2.������ʹ��cfg�ı�����������Ϣ(�ļ����ɸ���)
3.Ŀǰ֧������ʹ�÷�ʽ
  1>secureSignTool.exe 0 Signboot_config.cfg ��Signboot_config.cfg����
    chiptype,key file,cfg.bin,msid,version id,inputdir,outputdir ����Ϣ,ǩ
    ������������outputdir
  2>secureSignTool.exe 1 merge_config.cfg  ��merge_config.cfg����
    chiptype, ��ǩ�� bin �ļ�,inputdir,outputdir ����Ϣ,�ϳ�final boot������outputdir
  3>secureSignTool.exe 2 common_config.cfg  common_config.cfg����
    rsaǩ��˽Կ����ǩ���ļ���ǩ������ļ������Ƿ�ֶ�ǩ��,inputdir,outputdir ����Ϣ,ǩ��������outputdirĿ¼
    ˵���� SignCommon_config.cfg�в���SectionSize�����Ϊ0���򲻷ֶ�ǩ��������ֶ�ǩ���������ô�ֵΪ�ֶδ�С��
           ���簴1MB��С�ֶ�ǩ����������SectionSize=0x100000.
  4>secureSignTool.exe 3 special_config.cfg  ��boot����special��ʽǩ����
    ��special_config.cfg����rsaǩ��˽Կ����ǩ���ļ���ǩ������ļ�����CustomerData����,InputFileDir,OutputFileDir ����Ϣ,
    ǩ���������OutputFileDirĿ¼
    ˵���� special_config.cfg�����в���SectionSize��HeaderSize��RSALength��HashMode�ȣ�����ʱֻ֧��Ĭ�ϵ�.  
           ����ImageNumber����Ϊ��Ҫǩ���ľ�����������һ��ǩ����������ImageXXX��PartitionSizeXXX��SignImageXXX��XXXΪ���������������ӡ�         
  5>secureSignTool.exe 4 crypto_config.cfg  ��boot������ܺͽ��ܡ�
    crypto_config.cfg����rsaǩ��˽Կ�ļ���AES Key��IV��������ǩ���ļ���ǩ������ļ�����InputFileDir,OutputFileDir ����Ϣ,
    ���ܺ������OutputFileDir�������õ�Ŀ¼��
    ˵���� ��Ҫ������Ҫ����crypto_config.cfg�еĲ���������AES���ܣ�һ����Ҫ���ü����㷨Algorithm������ģʽMode������˽ԿKey����IV����.  
           ֧���������ܻ��߼��ܡ�ImageNumber����Ϊ��Ҫ�ӽ��ܵľ���������Ҫ��ʵ�ʵľ�����һ�£�����ᱨ��
           ����һ��ǩ����������Input1XXX��OutputXXX�������ֱ��������������XXXΪ���������������ӡ�         
   
           
4.�����ļ�������ļ�������cfg�ļ���������
5.boot����ǩ��ʱ��֧�ֵ�оƬ����Hi3716MV300,Hi3716CV200,Hi3719MV100,Hi3719CV100,����cfg�ļ������ã���boot����������оƬ�޹ء�
6.cfg�ļ��Զ�ȥ����#��ͷ��ע����
7.����������������ѯ
