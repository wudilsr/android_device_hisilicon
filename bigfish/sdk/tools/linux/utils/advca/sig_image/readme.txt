
һ��ʹ��˵��
1.��������CASignTool.exeǩ�����ߵ�linux�汾����ǰ���������ơ�
2.������ʹ��cfg�ı�����������Ϣ(�ļ����ɸ���)
3.Ŀǰ֧������ʹ�÷�ʽ
  1>Linux_CA_Boot_Sign.exe 0 Signboot_config.cfg ��Signboot_config.cfg����
    chiptype,key file,cfg.bin,msid,version id,inputdir,outputdir ����Ϣ,ǩ
    ������������outputdir
  2>Linux_CA_Boot_Sign.exe 1 merge_config.cfg  ��merge_config.cfg����
    chiptype, ��ǩ�� bin �ļ�,inputdir,outputdir ����Ϣ,�ϳ�final boot������outputdir
  3>Linux_CA_Boot_Sign.exe 2 common_config.cfg  common_config.cfg����
    rsaǩ��˽Կ����ǩ���ļ���ǩ������ļ������Ƿ�ֶ�ǩ��,inputdir,outputdir ����Ϣ,ǩ��������outputdirĿ¼
    ˵���� SignCommon_config.cfg�в���SectionSize�����Ϊ0���򲻷ֶ�ǩ��������ֶ�ǩ���������ô�ֵΪ�ֶδ�С��
           ���簴1MB��С�ֶ�ǩ����������SectionSize=0x100000.
  4>Linux_CA_Boot_Sign.exe 3 special_config.cfg  ��boot����special��ʽǩ����
    ��special_config.cfg����rsaǩ��˽Կ����ǩ���ļ���ǩ������ļ�����CustomerData����,InputFileDir,OutputFileDir ����Ϣ,
    ǩ���������OutputFileDirĿ¼
    ˵���� special_config.cfg�����в���SectionSize��HeaderSize��RSALength��HashMode�ȣ�����ʱֻ֧��Ĭ�ϵ�.  
           ����ImageNumber����Ϊ��Ҫǩ���ľ�����������һ��ǩ����������ImageXXX��PartitionSizeXXX��SignImageXXX��XXXΪ���������������ӡ�         
  5>Linux_CA_Boot_Sign.exe 4 crypto_config.cfg  ��boot������ܺͽ��ܡ�
    crypto_config.cfg����rsaǩ��˽Կ�ļ���AES Key��IV��������ǩ���ļ���ǩ������ļ�����InputFileDir,OutputFileDir ����Ϣ,
    ���ܺ������OutputFileDir�������õ�Ŀ¼��
    ˵���� ��Ҫ������Ҫ����crypto_config.cfg�еĲ���������AES���ܣ�һ����Ҫ���ü����㷨Algorithm������ģʽMode������˽ԿKey����IV����.  
           ֧���������ܻ��߼��ܡ�ImageNumber����Ϊ��Ҫ�ӽ��ܵľ���������Ҫ��ʵ�ʵľ�����һ�£�����ᱨ��
           ����һ��ǩ����������Input1XXX��OutputXXX�������ֱ��������������XXXΪ���������������ӡ�         
   				 
           
4.�����ļ�������ļ�������cfg�ļ���������
5.boot����ǩ��ʱ��֧�ֵ�оƬ����Hi3716MV300,Hi3716CV200,Hi3719MV100,Hi3719CV100,Hi3796CV100,Hi3798CV100,Hi3798MV100,Hi3716MV420,Hi3716MV410,Hi3110EV500,Hi3796MV100,����cfg�ļ������ã���boot����������оƬ�޹ء�
6.cfg�ļ��Զ�ȥ����#��ͷ��ע����
7.����������������ѯ

��������˵��
    1. ������ʹ�ÿ�Դopenssl v1.0.1g�汾��������汾����������Щ�޸����䣬
       Դ���Ϊopenssl-1.0.1g_hisi.tar.gz���Ѿ������libcrypto.a����ѷ���opensslĿ¼�С�
    2. opensslԴ�����ѹ�� tar -zxvf openssl-1.0.1g_hisi.tar.gz
       ����opensslԴ����ο���ѹ��Ŀ¼�е�readme.txt�ļ���
    3. ���ɿ�ִ�г���Linux_CA_Boot_Sign�ķ�����
	   3.1 32λLinux������ƽ̨��
	        ����1����32λ������ƽ̨�ϣ��ο�openssl-1.0.1g_hisi.tar.gz�е�readme.txt����������
			       libcrypto.a����������libcrypto.a������Ŀ¼Linux_CA_Boot_Sign_VX.X.X.X/openssl/libcrypto.a
			����2���ڸ�Ŀ¼ִ�У�make PLATFORM=32 (�� make PLATFORM=32 clean)
	   3.2 64λ����������ֱ���ڸ�Ŀ¼ִ�У�
	   		��ֱ���ڸ�Ŀ¼ִ�У�make (�� make clean)
	   		
����ע������
		1. ����CA����Ҫ����ܹ����ڰ�˻�����CA��˾��ɣ����SDK�к����ǩ�����߲��������ܾ�����Ҫ���sample/advca/�µ�sample��ɾ���ļ�����д��
		2. �����߿���Ϊ���������ʹ�ã��������裺
			a. ����SDK���ɸ߰����񣬽�pub/image������SignInput��
			b. ����apploader��stbid���񣬲�������SignInputĿ¼��
			c. ִ��sig.sh ca_type chiptype cfg_file������ǩ������
		3. �����Ҫ�滻root rsa key����external rsa	key����Ҫ�޸������ļ���
			�滻������������SignInputĿ¼��mv410_conax_integration_rsa_*.txt�ǲ�����ѡ�õ�external rsa key���滻external rsa keyʱ�ڹ���Ŀ¼����mv410_conax_integration_rsa_*.txt
			��������������Ӧ�ĵط��滻��������Ҫ��external rsakey��
			������SignInputĿ¼��rsa_root_*.txt�ǲ�����ѡ�õ�root rsa key���滻����ͬexternal rsa key��
